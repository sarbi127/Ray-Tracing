#include "Scene.hpp"
#include "simplematerial.hpp"
#include "simplerefractive.hpp"
#include "checker.hpp"
#include "image.hpp"

using namespace std;

// The constructor.
qbRT::Scene::Scene()
{
	// Configure the camera.
	m_camera.SetPosition(	qbVector<double>{std::vector<double> {2.0, -5.0, 0.50}});
	//m_camera.SetPosition(	qbVector<double>{std::vector<double> {0.0, -10.0, -2.0}});
	//m_camera.SetPosition( qbVector<double>{std::vector<double> {3.0, -5.0, -2.0}});
	m_camera.SetLookAt	( qbVector<double>{std::vector<double> {0.0, 0.0, 0.0}});
	m_camera.SetUp		( qbVector<double>{std::vector<double> {0.0, 0.0, 1.0}});
	//m_camera.SetHorzSize(0.25);
	//m_camera.SetHorzSize(0.85);
	m_camera.SetHorzSize(1.0);
	m_camera.SetAspect(16.0 / 9.0);
	//m_camera.SetAspect(1.0);
	m_camera.UpdateCameraGeometry();

	// Setup ambient lightling.
	qbRT::MaterialBase::m_ambientColor = std::vector<double>{1.0, 1.0, 1.0};
	qbRT::MaterialBase::m_ambientIntensity = 0.2;

	// Create some textures.
	auto floorTexture = std::make_shared<qbRT::Texture::Checker> (qbRT::Texture::Checker());
	auto sphereTexture = std::make_shared<qbRT::Texture::Checker> (qbRT::Texture::Checker());
	auto cylinderTexture = std::make_shared<qbRT::Texture::Checker> (qbRT::Texture::Checker());
	auto coneTexture = std::make_shared<qbRT::Texture::Checker> (qbRT::Texture::Checker());
	auto imageTexture = std::make_shared<qbRT::Texture::Image> (qbRT::Texture::Image());
	//auto coneTextureImage = std::make_shared<qbRT::Texture::Image> (qbRT::Texture::Image());

	// Setup the textures.
	floorTexture -> SetColor(qbVector<double>{std::vector<double>{0.50, 0.50, 0.50}}, qbVector<double>{std::vector<double>{0.8, 0.8, 0.2}});
	floorTexture -> SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0}},
								 0.0,
								 qbVector<double>{std::vector<double>{16.0, 16.0}} );
																
	sphereTexture -> SetColor(qbVector<double>{std::vector<double>{0.2, 0.2, 0.8}}, qbVector<double>{std::vector<double>{0.8, 0.8, 0.2}});
	sphereTexture -> SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0}},
								  0.0,
								  qbVector<double>{std::vector<double>{16.0, 16.0}} );
																	
	cylinderTexture -> SetColor(qbVector<double>{std::vector<double>{1.0, 0.0, 0.0}}, qbVector<double>{std::vector<double>{0.8, 0.8, 0.2}});
	cylinderTexture -> SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0}},
									0.0,
									qbVector<double>{std::vector<double>{4.0*M_PI, 4.0}} );
																		
	coneTexture -> SetColor(qbVector<double>{std::vector<double>{0.2, 0.2, 0.8}}, qbVector<double>{std::vector<double>{1.0, 0.5, 0.0}});
	coneTexture -> SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0}},
								0.0,
								qbVector<double>{std::vector<double>{8.0*(M_PI/2.0), 8.0}} );

    imageTexture -> LoadImage("bmp_24.bmp");
	imageTexture -> SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0}},
								 0.0,
								 qbVector<double>{std::vector<double>{1.0, 1.0}});

    // Create some materials.
	//auto testMaterial1 = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
    //auto testMaterial2 = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	//auto testMaterial3 = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	//auto testMaterial4 = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	//auto testMaterial5 = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	auto silverMetal = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	auto redMetal = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	auto goldMetal = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	auto blueDiffuse = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	auto yellowDiffuse = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	auto orangeDiffuse = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	auto floorMaterial = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	auto wallMaterial1 = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	auto wallMaterial2 = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	auto wallMaterial3 = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	auto imageMaterial = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	auto sphereMaterial = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	auto glassMaterial = std::make_shared<qbRT::SimpleRefractive> (qbRT::SimpleRefractive());

   // Setup the materials.
    silverMetal -> m_baseColor = qbVector<double>{std::vector<double>{0.5, 0.5, 0.8}};
	silverMetal -> m_reflectivity = 0.8;
	silverMetal -> m_shininess = 32.0;
	//silverMetal -> AssignTexture(coneTexture);
	
	goldMetal -> m_baseColor = qbVector<double>{std::vector<double>{0.96, 0.90, 0.34}};
	goldMetal -> m_reflectivity = 0.25;
	goldMetal -> m_shininess = 20.0;
	
	blueDiffuse -> m_baseColor = qbVector<double>{std::vector<double>{0.007, 0.8, 0.96}};
	blueDiffuse -> m_reflectivity = 0.8;
	blueDiffuse -> m_shininess = 32.0;
	
	
	yellowDiffuse -> m_baseColor = qbVector<double>{std::vector<double>{0.8, 0.8, 0.2}};
	yellowDiffuse -> m_reflectivity = 0.5;
	yellowDiffuse -> m_shininess = 5.0;
	
	orangeDiffuse -> m_baseColor = qbVector<double>{std::vector<double>{0.81, 0.39, 0.0}};
	orangeDiffuse -> m_reflectivity = 0.8;
	orangeDiffuse -> m_shininess = 32.0;
	orangeDiffuse -> AssignTexture(sphereTexture);
	

	redMetal -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.0, 0.0}};
	redMetal -> m_reflectivity = 0.5;
	redMetal -> m_shininess = 20.0;
	//redMetal -> AssignTexture(cylinderTexture);

	/*testMaterial1 -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 1.0, 0.0}};
	testMaterial1 -> m_reflectivity = 0.50;
	testMaterial1 -> m_shininess = 10.0;

	testMaterial2 -> m_baseColor = qbVector<double>{std::vector<double>{0.0, 1.0, 0.3}};
	testMaterial2 -> m_reflectivity = 0.50;
	testMaterial2 -> m_shininess = 10.0;
	
	testMaterial3 -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.0, 0.0}};
	testMaterial3 -> m_reflectivity = 0.50;
	testMaterial3 -> m_shininess = 10.0;

	testMaterial4 -> m_baseColor = qbVector<double>{std::vector<double>{0.7, 0.2, 0.7}};
	testMaterial4 -> m_reflectivity = 0.50;
	testMaterial4 -> m_shininess = 10.0;

	testMaterial5 -> m_baseColor = qbVector<double>{std::vector<double>{0.0, 0.7, 1.0}};
	testMaterial5 -> m_reflectivity = 0.50;
	testMaterial5 -> m_shininess = 10.0;

	floorMaterial -> m_baseColor = qbVector<double>{std::vector<double>{0.8, 0.6, 1.0}}; //Mauve
	floorMaterial -> m_reflectivity = 0.5;
	floorMaterial -> m_shininess = 0.0;*/

    
    floorMaterial -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 1.0, 1.0}};
	floorMaterial -> m_reflectivity = 0.25;
	floorMaterial -> m_shininess = 0.0;
	floorMaterial -> AssignTexture(floorTexture);

	wallMaterial1 -> m_baseColor = qbVector<double>{std::vector<double>{0.45, 0.32, 0.89}}; //purple
	wallMaterial1 -> m_reflectivity = 0.50;
	wallMaterial1 -> m_shininess = 8.0;


	wallMaterial2 -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.125, 0.125}};
	wallMaterial2 -> m_reflectivity = 0.50;
	wallMaterial2 -> m_shininess = 8.0;
	//wallMaterial2 -> AssignTexture(floorTexture);


    wallMaterial3 -> m_baseColor = qbVector<double>{std::vector<double>{0.86, 0.27, 0.49}}; //pink
	wallMaterial3 -> m_reflectivity = 0.50;
	wallMaterial3 -> m_shininess = 8.0;

	imageMaterial -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.125, 0.125}};
	imageMaterial -> m_reflectivity = 0.0;
	imageMaterial -> m_shininess = 0.0;
	imageMaterial -> AssignTexture(imageTexture);

	sphereMaterial -> m_baseColor = qbVector<double>{std::vector<double>{0.45, 0.32, 0.89}}; //purple
	sphereMaterial -> m_reflectivity = 0.8;
	sphereMaterial -> m_shininess = 32.0;

    glassMaterial -> m_baseColor = qbVector<double>{std::vector<double>{0.7, 0.7, 0.2}};
	glassMaterial -> m_reflectivity = 0.25;
	glassMaterial -> m_shininess = 32.0;
	glassMaterial -> m_translucency = 0.75;
	glassMaterial -> m_ior = 1.333;	//for water
	

	//create and setup objects.
	auto cone = std::make_shared<qbRT::Cone> (qbRT::Cone());
	cone -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{0.0, 0.0, -0.5}},
											 qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
											 qbVector<double>{std::vector<double>{1.0, 1.0, 2.0}}});
	cone -> AssignMaterial(silverMetal);
	
	/*auto leftSphere = std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere());
	leftSphere -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{1.0, -2.0, 0.5}},
												   qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
												   qbVector<double>{std::vector<double>{0.65, 0.5, 0.5}}});
	leftSphere -> AssignMaterial(blueDiffuse);*/
	
	auto rightSphere = std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere());
	rightSphere -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{1.5, 0.0, 0.0}},
												    qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
													qbVector<double>{std::vector<double>{1.0, 1.0, 1.0}}});
	rightSphere -> AssignMaterial(glassMaterial);

	auto rightSphere2 = std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere());
	rightSphere2 -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{0.0, 0.0, 0.50}},
												     qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
													 qbVector<double>{std::vector<double>{0.50, 0.50, 0.50}}});
	rightSphere2 -> AssignMaterial(glassMaterial);
	
	auto topSphere = std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere());
	topSphere -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{-2.0, -0.5, 0.25}},
												  qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
												  qbVector<double>{std::vector<double>{0.75, 0.75, 0.75}}});
	topSphere -> AssignMaterial(orangeDiffuse);

	auto Sphere1 = std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere());
	Sphere1 -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{-2.0, -1.25, -1.0}},
												     qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
												     qbVector<double>{std::vector<double>{0.75, 0.75, 0.75}}});
	Sphere1 -> AssignMaterial(blueDiffuse);

	auto Sphere2 = std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere());
	Sphere2 -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{-2.0, -2.0, 0.25}},
												     qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
												     qbVector<double>{std::vector<double>{0.75, 0.75, 0.75}}});
	Sphere2 -> AssignMaterial(orangeDiffuse);
	
	auto floor = std::make_shared<qbRT::ObjPlane> (qbRT::ObjPlane());
	floor -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}},
											  qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
											  qbVector<double>{std::vector<double>{16.0, 16.0, 1.0}}});
	floor -> AssignMaterial(floorMaterial);
	
	auto leftWall = std::make_shared<qbRT::ObjPlane> (qbRT::ObjPlane());
	leftWall -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{-4.0, 0.0, 0.0}},
										         qbVector<double>{std::vector<double>{0.0, -M_PI/2.0, -M_PI/2.0}},
												 qbVector<double>{std::vector<double>{16.0, 16.0, 1.0}}});
	leftWall -> AssignMaterial(wallMaterial1);
	//leftWall -> AssignMaterial(imageMaterial);
	
	auto backWall = std::make_shared<qbRT::ObjPlane> (qbRT::ObjPlane());
	backWall -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{0.0, 4.0, 0.0}},
												 qbVector<double>{std::vector<double>{-M_PI/2.0, 0.0, 0.0}},
												 qbVector<double>{std::vector<double>{16.0, 16.0, 1.0}}});
	backWall -> AssignMaterial(wallMaterial2);
	//backWall -> AssignMaterial(imageMaterial);

	auto rightWall = std::make_shared<qbRT::ObjPlane> (qbRT::ObjPlane());
	rightWall -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{4.0, 0.0, 0.0}},
												 qbVector<double>{std::vector<double>{0.0, -M_PI/2.0, -M_PI/2.0}},
												 qbVector<double>{std::vector<double>{16.0, 16.0, 1.0}}});
	rightWall -> AssignMaterial(wallMaterial3);
	//rightWall -> AssignMaterial(imageMaterial);
	
	/*auto cylinder1 = std::make_shared<qbRT::Cylinder> (qbRT::Cylinder());
	cylinder1 -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{-1.5, -2.0, 1.0}},
												  qbVector<double>{std::vector<double>{0.0, -M_PI/2.0, 0.0}},
												  qbVector<double>{std::vector<double>{0.25, 0.25, 1.0}}});
	cylinder1 -> AssignMaterial(goldMetal);*/
	
	auto cylinder2 = std::make_shared<qbRT::Cylinder> (qbRT::Cylinder());
	cylinder2 -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{-1.0, -2.0, 0.0}},
												  qbVector<double>{std::vector<double>{0.0, M_PI/5.0, 0.0}},
												  qbVector<double>{std::vector<double>{0.25, 0.25, 1.0}}});
	cylinder2 -> AssignMaterial(redMetal);
	
	/*auto cone2 = std::make_shared<qbRT::Cone> (qbRT::Cone());
	cone2 -> SetTransformMatrix(qbRT::GTform {qbVector<double>{std::vector<double>{0.0, -1.0, 0.0}},
											  qbVector<double>{std::vector<double>{M_PI/4.0, 0.0, 0.0}},
											  qbVector<double>{std::vector<double>{0.5, 0.5, 1.0}}});
	cone2 -> AssignMaterial(goldMetal); */

	auto imagePlane = std::make_shared<qbRT::ObjPlane> (qbRT::ObjPlane());
	imagePlane-> SetTransformMatrix(qbRT::GTform {	qbVector<double>{std::vector<double>{0.0, 3.0, 0.0}},
													qbVector<double>{std::vector<double>{-M_PI/3.0, 0.0, 0.0}},
													qbVector<double>{std::vector<double>{3.0, 10.0, 1.0}}});
	imagePlane -> AssignMaterial(imageMaterial);

    // Put the objects into the scene.
	//m_objectList.push_back(cone);
	//m_objectList.push_back(leftSphere);
	m_objectList.push_back(rightSphere);
	m_objectList.push_back(topSphere);
	m_objectList.push_back(floor);
	m_objectList.push_back(leftWall);
	m_objectList.push_back(backWall);
	m_objectList.push_back(rightWall);
	//m_objectList.push_back(cylinder1);
	//m_objectList.push_back(cylinder2);
	//m_objectList.push_back(cone2);
	m_objectList.push_back(imagePlane);
	m_objectList.push_back(Sphere1);
	m_objectList.push_back(Sphere2);
	m_objectList.push_back(rightSphere2);

	// Construct a test sphere.
	/*m_objectList.push_back(std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere()));
	m_objectList.push_back(std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere()));
	m_objectList.push_back(std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere()));
	m_objectList.push_back(std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere()));
	m_objectList.push_back(std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere()));*/

    // Construct a test plane.
	//m_objectList.push_back(std::make_shared<qbRT::ObjPlane> (qbRT::ObjPlane()));
	//m_objectList.at(3) -> m_baseColor = qbVector<double>{std::vector<double> {0.5, 0.5, 0.5}};
	//m_objectList.at(5) -> m_baseColor = qbVector<double>{std::vector<double> {0.5, 0.5, 0.5}};

	// Define a transform for the plane.
	/*qbRT::GTform planeMatrix;
	planeMatrix.SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0, 0.75}},
							 qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
							 qbVector<double>{std::vector<double>{4.0, 4.0, 1.0}});*/

	//m_objectList.at(3) -> SetTransformMatrix(planeMatrix);
	//m_objectList.at(5) -> SetTransformMatrix(planeMatrix);


	// Modify the spheres.
    /*qbRT::GTform testMatrix1, testMatrix2, testMatrix3, testMatrix4, testMatrix5;
	testMatrix1.SetTransform(qbVector<double>{std::vector<double>{-2.0, 2.0, 0.0}}, //translate
					         qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}}, //rotate
					         qbVector<double>{std::vector<double>{0.5, 0.5, 0.65}}); //scale

	testMatrix4.SetTransform(qbVector<double>{std::vector<double>{-1.75, 9.0, 0.0}}, 
					         qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}}, 
					         qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}}); 


    testMatrix2.SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
					         qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
					         qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}});

	testMatrix5.SetTransform(qbVector<double>{std::vector<double>{1.75, 9.0, 0.0}},
					         qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
					         qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}});

	
	testMatrix3.SetTransform(qbVector<double>{std::vector<double>{2.25, 2.0, 0.0}}, //translate
					         qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}}, //rotate
					         qbVector<double>{std::vector<double>{0.65, 0.5, 0.5}}); //scale
														
	
    m_objectList.at(0) -> SetTransformMatrix(testMatrix1);
	m_objectList.at(1) -> SetTransformMatrix(testMatrix4);
	m_objectList.at(2) -> SetTransformMatrix(testMatrix2);
	m_objectList.at(3) -> SetTransformMatrix(testMatrix5);
	m_objectList.at(4) -> SetTransformMatrix(testMatrix3);*/

	//m_objectList.at(0) -> SetTransformMatrix(testMatrix1);
	//m_objectList.at(1) -> SetTransformMatrix(testMatrix2);
	//m_objectList.at(2) -> SetTransformMatrix(testMatrix3);

    //m_objectList.at(0) -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 1.0, 0.0}}; //Yellow
	//m_objectList.at(1) -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.0, 1.0}}; //Purple
	//m_objectList.at(2) -> m_baseColor = qbVector<double>{std::vector<double>{0.0, 0.7, 1.0}}; //Aqua

   
	/*m_objectList.at(0) -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 1.0, 0.0}}; //Yellow
	m_objectList.at(1) -> m_baseColor = qbVector<double>{std::vector<double>{0.0, 1.0, 0.3}}; //Green
	m_objectList.at(2) -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.0, 0.0}}; //Red
	m_objectList.at(3) -> m_baseColor = qbVector<double>{std::vector<double>{0.7, 0.2, 0.7}}; //Bright Purple
	m_objectList.at(4) -> m_baseColor = qbVector<double>{std::vector<double>{0.0, 0.7, 1.0}}; //Aqua */

	// Assign materials to objects.
	/*m_objectList.at(0) -> AssignMaterial(testMaterial1);
	m_objectList.at(1) -> AssignMaterial(testMaterial2);
	m_objectList.at(2) -> AssignMaterial(testMaterial3);
	m_objectList.at(3) -> AssignMaterial(testMaterial4);
	m_objectList.at(4) -> AssignMaterial(testMaterial5);
	m_objectList.at(5) -> AssignMaterial(floorMaterial);*/

	// Construct a test light.
	/*m_lightList.push_back(std::make_shared<qbRT::PointLight> (qbRT::PointLight()));
	m_lightList.at(0) -> m_location = qbVector<double> {std::vector<double> {5.0, -10.0, -5.0}};
	m_lightList.at(0) -> m_color = qbVector<double> {std::vector<double> {0.0, 0.0, 1.0}}; //blue

	m_lightList.push_back(std::make_shared<qbRT::PointLight> (qbRT::PointLight()));
	m_lightList.at(1) -> m_location = qbVector<double> {std::vector<double> {-5.0, -10.0, -5.0}}; 
	m_lightList.at(1) -> m_color = qbVector<double> {std::vector<double> {1.0, 0.0, 0.0}}; //red
	
	m_lightList.push_back(std::make_shared<qbRT::PointLight> (qbRT::PointLight()));
	m_lightList.at(2) -> m_location = qbVector<double> {std::vector<double> {0.0, -10.0, -5.0}};
	m_lightList.at(2) -> m_color = qbVector<double> {std::vector<double> {0.0, 1.0, 0.0}}; //green */


    // Construct and setup the lights.
    m_lightList.push_back(std::make_shared<qbRT::PointLight> (qbRT::PointLight()));
	m_lightList.at(0) -> m_location = qbVector<double> {std::vector<double> {3.0, -10.0, -5.0}};
	m_lightList.at(0) -> m_color = qbVector<double> {std::vector<double> {1.0, 1.0, 1.0}};
	m_lightList.at(0) -> m_intensity = 4.0;
	
	m_lightList.push_back(std::make_shared<qbRT::PointLight> (qbRT::PointLight()));
	m_lightList.at(1) -> m_location = qbVector<double> {std::vector<double> {0.0, -10.0, -5.0}};
	m_lightList.at(1) -> m_color = qbVector<double> {std::vector<double> {1.0, 1.0, 1.0}};
	m_lightList.at(1) -> m_intensity = 2.0;


	// Construct and setup the lights.
	/*m_lightList.push_back(std::make_shared<qbRT::PointLight> (qbRT::PointLight()));
	m_lightList.at(0) -> m_location = qbVector<double> {std::vector<double> {3.0, -10.0, -5.0}};
	m_lightList.at(0) -> m_color = qbVector<double> {std::vector<double> {1.0, 1.0, 1.0}};
	
	m_lightList.push_back(std::make_shared<qbRT::PointLight> (qbRT::PointLight()));
	m_lightList.at(1) -> m_location = qbVector<double> {std::vector<double> {0.0, -10.0, -5.0}};
	m_lightList.at(1) -> m_color = qbVector<double> {std::vector<double> {1.0, 1.0, 1.0}};
	
	m_lightList.push_back(std::make_shared<qbRT::PointLight> (qbRT::PointLight()));
	m_lightList.at(2) -> m_location = qbVector<double> {std::vector<double> {-2.0, 2.0, 0.0}};
	m_lightList.at(2) -> m_color = qbVector<double> {std::vector<double> {1.0, 0.8, 0.8}};
	m_lightList.at(2) -> m_intensity = 0.5;
	
	m_lightList.push_back(std::make_shared<qbRT::PointLight> (qbRT::PointLight()));
	m_lightList.at(3) -> m_location = qbVector<double> {std::vector<double> {4.0, 2.0, 0.0}};
	m_lightList.at(3) -> m_color = qbVector<double> {std::vector<double> {1.0, 0.8, 0.8}};
	m_lightList.at(3) -> m_intensity = 0.5;	*/

}

// Function to perform the rendering.
bool qbRT::Scene::Render(qbImage &outputImage)
{
	// Get the dimensions of the output image.
	int xSize = outputImage.GetXSize();
	int ySize = outputImage.GetYSize();
	
	// Loop over each pixel in our image.
	qbRT::Ray cameraRay;
	qbVector<double> intPoint			(3);
	qbVector<double> localNormal	(3);
	qbVector<double> localColor		(3);
	double xFact = 1.0 / (static_cast<double>(xSize) / 2.0);
	double yFact = 1.0 / (static_cast<double>(ySize) / 2.0);
	double minDist = 1e6;
	double maxDist = 0.0;
	for (int y=0; y<ySize; ++y)
	{
		// Display progress.
		std::cout << "Processing line " << y << " of " << ySize << "." << " \r";
		std::cout.flush();
		
		for (int x=0; x<xSize; ++x)
		{
			// Normalize the x and y coordinates.
			double normX = (static_cast<double>(x) * xFact) - 1.0;
			double normY = (static_cast<double>(y) * yFact) - 1.0;
			
			// Generate the ray for this pixel.
			m_camera.GenerateRay(normX, normY, cameraRay);
			
			// Test for intersections with all objects in the scene.
			std::shared_ptr<qbRT::ObjectBase> closestObject;
			qbVector<double> closestIntPoint		{3};
			qbVector<double> closestLocalNormal	{3};
			qbVector<double> closestLocalColor	{3};
			bool intersectionFound = CastRay(cameraRay, closestObject, closestIntPoint, closestLocalNormal, closestLocalColor);
			
			/* Compute the illumination for the closest object, assuming that there
				was a valid intersection. */
			if (intersectionFound)
			{
				// Check if the object has a material.
				if (closestObject -> m_hasMaterial)
				{
					// Use the material to compute the color.
					qbRT::MaterialBase::m_reflectionRayCount = 0;
					qbVector<double> color = closestObject -> m_pMaterial -> ComputeColor(m_objectList, m_lightList,closestObject, closestIntPoint,
																						   closestLocalNormal, cameraRay);
					outputImage.SetPixel(x, y, color.GetElement(0), color.GetElement(1), color.GetElement(2));
				}
				else
				{
					// Use the basic method to compute the color.
					qbVector<double> matColor = qbRT::MaterialBase::ComputeDiffuseColor(m_objectList, m_lightList,
																						closestObject, closestIntPoint,
																						closestLocalNormal, closestObject->m_baseColor);
					outputImage.SetPixel(x, y, matColor.GetElement(0), matColor.GetElement(1), matColor.GetElement(2));
				}
			}
		}
	}

	std::cout << std::endl;
	return true;
}


bool qbRT::Scene::CastRay(qbRT::Ray &castRay, std::shared_ptr<qbRT::ObjectBase> &closestObject,
						  qbVector<double> &closestIntPoint, qbVector<double> &closestLocalNormal,
						  qbVector<double> &closestLocalColor)
{
    qbVector<double> intPoint		{3};
	qbVector<double> localNormal	{3};
	qbVector<double> localColor		{3};
	double minDist = 1e6;
	bool intersectionFound = false;
	for (auto currentObject : m_objectList)
	{
		bool validInt = currentObject -> TestIntersection(castRay, intPoint, localNormal, localColor);
		
		// If we have a valid intersection.
		if (validInt)
		{
			// Set the flag to indicate that we found an intersection.
			intersectionFound = true;
					
			// Compute the distance between the camera and the point of intersection.
			double dist = (intPoint - castRay.m_point1).norm();
					
			/* If this object is closer to the camera than any one that we have
				seen before, then store a reference to it. */
			if (dist < minDist)
			{
				minDist = dist;
				closestObject = currentObject;
				closestIntPoint = intPoint;
				closestLocalNormal = localNormal;
				closestLocalColor = localColor;
			}
		}
	}
	
	return intersectionFound;

}
			