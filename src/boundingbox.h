#ifndef boundingbox_h__
#define boundingbox_h__

#include "objectbase.h"

class BoundingBox : public AbstractObjectBase
{
public:
  BoundingBox(const QVector3D& dimensions);
  virtual ~BoundingBox();
  

  

protected:  
  virtual void createGeometry();
  virtual void draw();
    
  // the dimensions (edge length of x, y, z)
  QVector3D _dimensions;
  
};
#endif // boundingbox_h__