#include "Scene.hpp"
#include "simplematerial.hpp"

using namespace std;

// The constructor.
qbRT::Scene::Scene()
{
    // Create some materials.
	auto testMaterial1 = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
    auto testMaterial2 = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	auto testMaterial3 = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	auto testMaterial4 = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	auto testMaterial5 = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	auto floorMaterial = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	
   // Setup the materials.
	testMaterial1 -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 1.0, 0.0}};
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
	floorMaterial -> m_reflectivity = 0.50;
	floorMaterial -> m_shininess = 10.0;

	// Configure the camera.
	m_camera.SetPosition( qbVector<double>{std::vector<double> {0.0, -10.0, -2.0}});
	m_camera.SetLookAt	( qbVector<double>{std::vector<double> {0.0, 0.0, 0.0}});
	m_camera.SetUp		( qbVector<double>{std::vector<double> {0.0, 0.0, 1.0}});
	m_camera.SetHorzSize(0.25);
	m_camera.SetAspect(16.0 / 9.0);
	m_camera.UpdateCameraGeometry();

	// Construct a test sphere.
	m_objectList.push_back(std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere()));
	m_objectList.push_back(std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere()));
	m_objectList.push_back(std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere()));
	m_objectList.push_back(std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere()));
	m_objectList.push_back(std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere()));

    // Construct a test plane.
	m_objectList.push_back(std::make_shared<qbRT::ObjPlane> (qbRT::ObjPlane()));
	//m_objectList.at(3) -> m_baseColor = qbVector<double>{std::vector<double> {0.5, 0.5, 0.5}};
	m_objectList.at(5) -> m_baseColor = qbVector<double>{std::vector<double> {0.5, 0.5, 0.5}};

	// Define a transform for the plane.
	qbRT::GTform planeMatrix;
	planeMatrix.SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0, 0.75}},
							 qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
							 qbVector<double>{std::vector<double>{4.0, 4.0, 1.0}});

	//m_objectList.at(3) -> SetTransformMatrix(planeMatrix);
	m_objectList.at(5) -> SetTransformMatrix(planeMatrix);


	// Modify the spheres.
    qbRT::GTform testMatrix1, testMatrix2, testMatrix3, testMatrix4, testMatrix5;
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
	m_objectList.at(4) -> SetTransformMatrix(testMatrix3);

	//m_objectList.at(0) -> SetTransformMatrix(testMatrix1);
	//m_objectList.at(1) -> SetTransformMatrix(testMatrix2);
	//m_objectList.at(2) -> SetTransformMatrix(testMatrix3);

    //m_objectList.at(0) -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 1.0, 0.0}}; //Yellow
	//m_objectList.at(1) -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.0, 1.0}}; //Purple
	//m_objectList.at(2) -> m_baseColor = qbVector<double>{std::vector<double>{0.0, 0.7, 1.0}}; //Aqua

   
	m_objectList.at(0) -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 1.0, 0.0}}; //Yellow
	m_objectList.at(1) -> m_baseColor = qbVector<double>{std::vector<double>{0.0, 1.0, 0.3}}; //Green
	m_objectList.at(2) -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.0, 0.0}}; //Red
	m_objectList.at(3) -> m_baseColor = qbVector<double>{std::vector<double>{0.7, 0.2, 0.7}}; //Bright Purple
	m_objectList.at(4) -> m_baseColor = qbVector<double>{std::vector<double>{0.0, 0.7, 1.0}}; //Aqua

	// Assign materials to objects.
	m_objectList.at(0) -> AssignMaterial(testMaterial1);
	m_objectList.at(1) -> AssignMaterial(testMaterial2);
	m_objectList.at(2) -> AssignMaterial(testMaterial3);
	m_objectList.at(3) -> AssignMaterial(testMaterial4);
	m_objectList.at(4) -> AssignMaterial(testMaterial5);
	m_objectList.at(5) -> AssignMaterial(floorMaterial);

	// Construct a test light.
	m_lightList.push_back(std::make_shared<qbRT::PointLight> (qbRT::PointLight()));
	m_lightList.at(0) -> m_location = qbVector<double> {std::vector<double> {5.0, -10.0, -5.0}};
	m_lightList.at(0) -> m_color = qbVector<double> {std::vector<double> {0.0, 0.0, 1.0}}; //blue

	m_lightList.push_back(std::make_shared<qbRT::PointLight> (qbRT::PointLight()));
	m_lightList.at(1) -> m_location = qbVector<double> {std::vector<double> {-5.0, -10.0, -5.0}}; 
	m_lightList.at(1) -> m_color = qbVector<double> {std::vector<double> {1.0, 0.0, 0.0}}; //red
	
	m_lightList.push_back(std::make_shared<qbRT::PointLight> (qbRT::PointLight()));
	m_lightList.at(2) -> m_location = qbVector<double> {std::vector<double> {0.0, -10.0, -5.0}};
	m_lightList.at(2) -> m_color = qbVector<double> {std::vector<double> {0.0, 1.0, 0.0}}; //green

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
		std::cout << "Processing line " << y << " of " << ySize << "." << std::endl;
		
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
			