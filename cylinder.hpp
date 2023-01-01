#ifndef CYLINDER_H
#define CYLINDER_H

#include <array>
#include "objectbase.hpp"
#include "gtfm.hpp"

namespace qbRT
{
	class Cylinder : public ObjectBase
	{
		public:
			// Default constructor.
			Cylinder();
			
			// Override the destructor.
			virtual ~Cylinder() override;
			
			// Override the function to test for intersections.
			virtual bool TestIntersection(const qbRT::Ray &castRay, qbVector<double> &intPoint,
										  qbVector<double> &localNormal, qbVector<double> &localColor) override;
	};
}

#endif


