#include "Scene.hpp"

using namespace std;

// The constructor.
qbRT::Scene::Scene()
{
	// Configure the camera.
	m_camera.SetPosition(	qbVector<double>{std::vector<double> {0.0, -10.0, 0.0}} );
	m_camera.SetLookAt	( qbVector<double>{std::vector<double> {0.0, 0.0, 0.0}} );
	m_camera.SetUp		( qbVector<double>{std::vector<double> {0.0, 0.0, 1.0}} );
	m_camera.SetHorzSize(0.25);
	m_camera.SetAspect(16.0 / 9.0);
	m_camera.UpdateCameraGeometry();

	// Construct a test sphere.
	m_objectList.push_back(std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere()));
	m_objectList.push_back(std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere()));
	m_objectList.push_back(std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere()));

	// Modify the spheres.
    qbRT::GTform testMatrix1, testMatrix2, testMatrix3;
	testMatrix1.SetTransform(	qbVector<double>{std::vector<double>{-1.5, 0.0, 0.0}}, //translate
					            qbVector<double>{std::vector<double>{1.0, 1.0, 1.0}}, //rotate
					            qbVector<double>{std::vector<double>{0.5, 0.5, 0.65}}); //scale


    testMatrix2.SetTransform(	qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
					            qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
					            qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}});
														
	testMatrix3.SetTransform(	qbVector<double>{std::vector<double>{1.5, 0.0, 0.0}},
					            qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
					            qbVector<double>{std::vector<double>{0.65, 0.5, 0.5}});

	
	m_objectList.at(0) -> SetTransformMatrix(testMatrix1);
	m_objectList.at(1) -> SetTransformMatrix(testMatrix2);
	m_objectList.at(2) -> SetTransformMatrix(testMatrix3);

    m_objectList.at(0) -> m_baseColor = qbVector<double>{std::vector<double>{255.0, 255.0, 0.0}}; //Yellow
	m_objectList.at(1) -> m_baseColor = qbVector<double>{std::vector<double>{255.0, 0.0, 255.0}}; //Purple
	m_objectList.at(2) -> m_baseColor = qbVector<double>{std::vector<double>{0.0, 191.0, 255.0}}; //Aqua

	// Construct a test light.
	m_lightList.push_back(std::make_shared<qbRT::PointLight> (qbRT::PointLight()));
	m_lightList.at(0) -> m_location = qbVector<double> {std::vector<double> {5.0, -10.0, -5.0}};
	m_lightList.at(0) -> m_color = qbVector<double> {std::vector<double> {255.0, 255.0, 255.0}};

}

// Function to perform the renderering.
bool qbRT::Scene::Render(qbImage &outputImage) 
{
	// Get the dimensions of the output image.
	int xSize = outputImage.GetXSize();
	int ySize = outputImage.GetYSize();
	
		// Create some colour variations.
		/*for (int x=0; x<xSize; ++x)
		{
			for (int y=0; y<ySize; ++y)
			{
				double red = (static_cast<double>(x)/static_cast<double>(xSize)) * 255.0;
				double green = (static_cast<double>(y)/static_cast<double>(ySize)) * 255.0;
				outputImage.SetPixel(x, y, red, green, 0.0);
			}
		}*/

	// Loop over each pixel in our image.
	qbRT::Ray cameraRay;
	qbVector<double> intPoint		(3);
	qbVector<double> localNormal	(3);
	qbVector<double> localColor		(3);
	double xFact = 1.0 / (static_cast<double>(xSize) / 2.0); //between 0-2
	double yFact = 1.0 / (static_cast<double>(ySize) / 2.0); //between 0-2
	double minDist = 1e6;
	double maxDist = 0.0;
	for (int x=0; x<xSize; ++x)
	{
		for (int y=0; y<ySize; ++y)
		{
			// Normalize the x and y coordinates.
			double normX = (static_cast<double>(x) * xFact) - 1.0; //between (-1)-1
			double normY = (static_cast<double>(y) * yFact) - 1.0; //between (-1)-1
			
			// Generate the ray for this pixel.
			m_camera.GenerateRay(normX, normY, cameraRay);
			
            // Test for intersections with all objects in the scene.
			for (auto currentObject : m_objectList)
			{
				bool validInt = currentObject -> TestIntersection(cameraRay, intPoint, localNormal, localColor);
				
				// If we have a valid intersection, change pixel color to red.
				if (validInt)
				{
					// Compute intensity of illumination.
					double intensity;
					qbVector<double> color {3};
					bool validIllum = false;
					for (auto currentLight : m_lightList)
					{
						validIllum = currentLight->ComputeIllumination(intPoint, localNormal, m_objectList, currentObject, color, intensity);
					}
				
					// Compute the distance between the camera and the point of intersection.
					double dist = (intPoint - cameraRay.m_point1).norm();
					if (dist > maxDist)
						maxDist = dist;
					
					if (dist < minDist)
						minDist = dist;
				
					//outputImage.SetPixel(x, y, 255.0 - ((dist - 9.0) / 0.94605) * 255.0, 0.0, 0.0);
					if (validIllum)
					{
						//outputImage.SetPixel(x, y, 255.0 * intensity, 0.0, 0.0);
						outputImage.SetPixel(x, y,	localColor.GetElement(0) * intensity,
										            localColor.GetElement(1) * intensity,
										            localColor.GetElement(2) * intensity);
					}
					else
					{   
						// Leave this pixel unchanged.
						//outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
					}
				}
			else
			{
				 // Leave this pixel unchanged.
				//outputImage.SetPixel(x, y, 0.0, 0.0, 0.0); // sent pixel to black
			}
		  }
		}
	}
	
	cout << "Minimum distance: " << minDist << endl;
	cout << "Maximum distance: " << maxDist << endl;	
	
	return true;
}
