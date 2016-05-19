#ifndef crosshair_h__
#define crosshair_h__

#include "objectbase.h"

class CrossHair : public AbstractObjectBase
{
public:  
  CrossHair(const QVector3D& dimension, const QVector3D& bounding);
  ~CrossHair();

  void highlight(bool on=true);
  virtual const QVector3D& translate(const QVector3D& vec);

protected:
  virtual void createGeometry();
  virtual void draw();

  // the dimensions (edge length of x, y, z)  
  bool _highlighted;
  float _movingspeed;
  float _halfx;
  float _halfy;
  float _halfz;

  float _halfBoundingx;
  float _halfBoundingy;
  float _halfBoundingz; 
  
};



#endif // crosshair_h__
