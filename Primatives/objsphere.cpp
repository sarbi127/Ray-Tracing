#include "objsphere.hpp"
#include <cmath>

// The default constructor.
qbRT::ObjSphere::ObjSphere()
{

}

// The destructor.
qbRT::ObjSphere::~ObjSphere()
{

}

// Function to test for intersections.
bool qbRT::ObjSphere::TestIntersection(const qbRT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor)
{
	
	
	// Copy the ray and apply the backwards transform. Convert Ray from Worlds coordinate to local coordinate.
	qbRT::Ray bckRay = m_transformMatrix.Apply(castRay, qbRT::BCKTFORM);
	
	
	// Compute the values of a, b and c.
	qbVector<double> vhat = bckRay.m_lab;
	vhat.Normalize();
	 
	/* Note that a is equal to the squared magnitude of the
		direction of the cast ray. As this will be a unit vector,
		we can conclude that the value of 'a' will always be 1. */
	// a = 1.0;
	
	// Calculate b.
	double b = 2.0 * qbVector<double>::dot(bckRay.m_point1, vhat);
	
	// Calculate c.
	double c = qbVector<double>::dot(bckRay.m_point1, bckRay.m_point1) - 1.0;
	
	// Test whether we actually have an intersection.
	double intTest = (b*b) - 4.0 * c;
	
	qbVector<double> poi;
	if (intTest > 0.0)// have intersection
	{
		// Add shading
		double numSQRT = sqrtf(intTest); //sqr intersection
		double t1 = (-b + numSQRT) / 2.0;
		double t2 = (-b - numSQRT) / 2.0;
		
		/* If either t1 or t2 are negative, then at least part of the object is
			behind the camera and so we will ignore it. */
		if ((t1 < 0.0) && (t2 < 0.0))
		{
			return false;
		}
		else
		{
			// Determine which point of intersection was closest to the camera.
			/*if (t1 < t2)
			{
				poi = bckRay.m_point1 + (vhat * t1);
			}
			else
			{
				poi = bckRay.m_point1 + (vhat * t2);
			}*/

			// Determine which point of intersection was closest to the camera.
			if (t1 < t2)
			{
				if (t1 > 0.0)
				{
					poi = bckRay.m_point1 + (vhat * t1);
				}
				else
				{
					if (t2 > 0.0)
					{
						poi = bckRay.m_point1 + (vhat * t2);
					}
					else
					{
						return false;
					}
				}
			}
			else
			{
				if (t2 > 0.0)
				{
					poi = bckRay.m_point1 + (vhat * t2);
				}
				else
				{
					if (t1 > 0.0)
					{
						poi = bckRay.m_point1 + (vhat * t1);
					}
					else
					{
						return false;
					}
				}
			}

            // Transform the intersection point back into world coordinates.
			intPoint = m_transformMatrix.Apply(poi, qbRT::FWDTFORM);

			// Compute the local normal (easy for a sphere at the origin!).
			//qbVector<double> objOrigin = qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}}; // local coordinate.
			//qbVector<double> newObjOrigin = m_transformMatrix.Apply(objOrigin, qbRT::FWDTFORM); // world coordinate.


			// Compute the local normal (easy for a sphere at the origin!).
			//localNormal = intPoint - newObjOrigin;
			//localNormal.Normalize();

			qbVector<double> normalVector = poi;
			localNormal = m_transformMatrix.ApplyNorm(normalVector);
			localNormal.Normalize();

			// Return the base color.
			localColor = m_baseColor;

			// Compute and store (u,v) coordinates for possible later use.
			double x = poi.GetElement(0);
			double y = poi.GetElement(1);
			double z = poi.GetElement(2);
			double u = atan2(sqrtf(pow(x, 2.0) + pow(y, 2.0)), z);
			double v = atan2(y, x);
			
			//if (x < 0)
				//v += M_PI;

			//normaliaze between -1 and 1.	
			u /= M_PI;
			v /= M_PI;
			
			m_uvCoords.SetElement(0, u);
			m_uvCoords.SetElement(1, v);

		}
		
		return true;
	}
	else
	{
		return false;
	}
	
}

