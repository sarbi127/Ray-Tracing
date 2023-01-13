#include "box.hpp"
#include "../qbutils.hpp"
#include <cmath>

qbRT::Box::Box()
{

}

qbRT::Box::~Box()
{

}

// Function to test for intersections.
bool qbRT::Box:: TestIntersection(const qbRT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor)
{
	if (!m_isVisible)
		return false;
	
	// Copy the ray and apply the backwards transform.
	qbRT::Ray bckRay = m_transformMatrix.Apply(castRay, qbRT::BCKTFORM);
	
	// Extract values of a.
	double ax = bckRay.m_point1.GetElement(0);
	double ay = bckRay.m_point1.GetElement(1);
	double az = bckRay.m_point1.GetElement(2);
	
	// Extract the value of k.
	qbVector<double> k = bckRay.m_lab; //diraction of bckRay
	k.Normalize();
	double kx = k.GetElement(0);
	double ky = k.GetElement(1);
	double kz = k.GetElement(2);
		
	// Test for intersections with each plane (side of the box).
	// Top and bottom.
	if (!CloseEnough(kz, 0.0)) //test the parallel
	{
		t[0] = (az - 1.0) / -kz;
		t[1] = (az + 1.0) / -kz;
		u[0] = ax + kx * t[0];
		v[0] = ay + ky * t[0];
		u[1] = ax + kx * t[1];
		v[1] = ay + ky * t[1];
	}
	else
	{
		t[0] = 100e6;
		t[1] = 100e6;
		u[0] = 0.0;
		v[0] = 0.0;
		u[1] = 0.0;
		v[1] = 0.0;
	}
	
	// Left and right.
	if (!CloseEnough(kx, 0.0)) //test the parallel
	{
		t[2] = (ax + 1.0) / -kx;
		t[3] = (ax - 1.0) / -kx;
		u[2] = az + kz * t[2];
		v[2] = ay + ky * t[2];
		u[3] = az + kz * t[3];
		v[3] = ay + ky * t[3];
	}
	else
	{
		t[2] = 100e6;
		t[3] = 100e6;
		u[2] = 0.0;
		v[2] = 0.0;
		u[3] = 0.0;
		v[3] = 0.0;		
	}
	
	// Front and back.
	if (!CloseEnough(ky, 0.0)) //test the parallel
	{
		t[4] = (ay + 1.0) / -ky;
		t[5] = (ay - 1.0) / -ky;
		u[4] = ax + kx * t[4];
		v[4] = az + kz * t[4];
		u[5] = ax + kx * t[5];
		v[5] = az + kz * t[5];
	}
	else
	{
		t[4] = 100e6;
		t[5] = 100e6;
		u[4] = 0.0;
		v[4] = 0.0;
		u[5] = 0.0;
		v[5] = 0.0;		
	}
	
	// Find the index of the smallest non-negative value of t.
	double finalU = 0.0;
	double finalV = 0.0;
	double finalT = 100e6;
	int finalIndex = 0;
	bool validIntersection = false;
	for (int i=0; i<6; ++i)
	{
		if ((t[i] < finalT) && (t[i] > 0.0) && (abs(u[i]) <= 1.0) && (abs(v[i]) <= 1.0))
		{
			finalT = t[i];
			finalIndex = i;
			finalU = u[i];
			finalV = v[i];
			validIntersection = true;
		}
	}
	
	if (validIntersection)
	{
		// Compute the point of intersection.
		qbVector<double> poi = bckRay.m_point1 + finalT * k; //line equation l=a+tk
	
		// Compute the normal vector
		qbVector<double> normalVector	{3};
		switch (finalIndex)
		{
			case 0:
				normalVector = std::vector<double>{0.0, 0.0, 1.0}; // Down.
				break;
				
			case 1:
				normalVector = std::vector<double>{0.0, 0.0, -1.0}; // Up.
				break;
				
			case 2:
				normalVector = std::vector<double>{-1.0, 0.0, 0.0}; // Left.
				break;
				
			case 3:
				normalVector = std::vector<double>{1.0, 0.0, 0.0}; // Right.
				break;
				
			case 4:
				normalVector = std::vector<double>{0.0, -1.0, 0.0}; // Backwards (towards the camera).
				break;
				
			case 5:
				normalVector = std::vector<double>{0.0, 1.0, 0.0}; // Forwards (away from the camera).
				break;
				
		}
		
		// Transform the intersection point back into world coordinates.
        
        intPoint = m_transformMatrix.Apply(poi, qbRT::FWDTFORM);
		//hitData.poi = m_transformMatrix.Apply(poi, qbRT::FWDTFORM);
			
		// Transform the normal vector.
        localNormal = m_transformMatrix.ApplyNorm(normalVector);
		localNormal.Normalize();
		//hitData.normal = m_transformMatrix.ApplyNorm(normalVector);
		//hitData.normal.Normalize();
			
		// Return the base color.
        localColor = m_baseColor;
		//hitData.color = m_baseColor;
					
		// Store the (u,v) coordinates for possible later use.
		m_uvCoords.SetElement(0, finalU);
		m_uvCoords.SetElement(1, finalV);
		//ComputeUV(poi, m_uvCoords);
		//hitData.uvCoords = m_uvCoords;
		
		// Return a reference to this object.
		//hitData.hitObject = std::make_shared<qbRT::ObjectBase> (*this);			
		
		return true;
	}
	else
	{
		return false;
	}


}
