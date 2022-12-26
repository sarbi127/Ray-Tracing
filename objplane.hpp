#ifndef OBJPLANE_H
#define OBJPLANE_H


#include "objectbase.hpp"
#include "gtfm.hpp"

namespace qbRT
{
   class ObjPlane : public ObjectBase
   {
  
   public:

        ObjPlane ();

        virtual ~ObjPlane() override;

        // Override the function to test for intersections.
        virtual bool TestIntersection(const qbRT::Ray &castRay, qbVector<double> &intPoin, 
        qbVector<double> &localNormal, qbVector<double> &localColor) override;
    
   private:
    

   };

}

#endif

