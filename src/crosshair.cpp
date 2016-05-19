#include "crosshair.h"

CrossHair::CrossHair( const QVector3D& dimension, const QVector3D& bounding)
  :AbstractObjectBase(),
   _highlighted(false),
   _movingspeed(0.1f)   
{
  _halfx = dimension.x()/2;
  _halfy = dimension.y()/2;
  _halfz = dimension.z()/2;

  _halfBoundingx = bounding.x()/2;
  _halfBoundingy = bounding.y()/2;
  _halfBoundingz = bounding.z()/2;
}

CrossHair::~CrossHair()
{

}

void CrossHair::highlight( bool on/*=true*/ )
{
  _highlighted = on;
}

void CrossHair::createGeometry()
{
  // x axis
  addVertex(Vertex(-_halfx, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f));
  addVertex(Vertex( _halfx, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f));

  // y axis
  addVertex(Vertex(0.0f, -_halfy, 0.0f,  0.0f, 1.0f, 0.0f));
  addVertex(Vertex(0.0f,  _halfy, 0.0f,  0.0f, 1.0f, 0.0f));

  // z axis
  addVertex(Vertex(0.0f, 0.0f, -_halfz,  0.0f, 0.0f, 1.0f));
  addVertex(Vertex(0.0f, 0.0f,  _halfz,  0.0f, 0.0f, 1.0f));

  addIndex(0);  addIndex(1);
  addIndex(2);  addIndex(3);
  addIndex(4);  addIndex(5);
}

void CrossHair::draw()
{
  // get current line width
  GLfloat fLineWidthSave = 1.0f;
  glGetFloatv(GL_LINE_WIDTH, &fLineWidthSave);

  // set line with to 5 if highlighted is on
  if(_highlighted)
    glLineWidth(5.0f);

  // bind the buffers
  bufferVBO().bind();
  bufferIBO().bind();

  // enable the shader attributes (our buffers)  
  shader()->enableAttributeArray(vertexLocation());
  shader()->enableAttributeArray(colorLocation());

  // set our buffers into shader
  shader()->setAttributeBuffer(vertexLocation(), GL_FLOAT, 0, 3, sizeof(Vertex));
  shader()->setAttributeBuffer(colorLocation(),  GL_FLOAT, 12, 4, sizeof(Vertex));


  // draw primitives
  glDrawElements(GL_LINES, indexCount(), GL_UNSIGNED_SHORT, 0);


  // disable the shader attributes (our buffers)
  shader()->disableAttributeArray(vertexLocation());
  shader()->disableAttributeArray(colorLocation());

  bufferVBO().release();
  bufferIBO().release();

  // set back
  if(_highlighted)
    glLineWidth(fLineWidthSave);
}


/*!
 * \brief
 * Translates the object
 * 
 * \param vec
 * The vector with the translation coordinates
 * 
 * \returns
 * Returns the new absolute vector after the translation
 * 
 * This overwrite checks for collision on the bounding box
 * 
 */
const QVector3D& CrossHair::translate( const QVector3D& vec )
{
  // return the original translation vector if the given translation 
  // vector is a null vector
  if(vec.isNull())
    return _translationVec;

  // create a copy of the given translation vector
  QVector3D moving = vec;

  // first normalize the vector
  moving.normalize();

  // multiply with the speed factor
  moving *= _movingspeed;

  QVector3D tempPosition = _translationVec + moving;

  // -x bounds
  if( tempPosition.x() <= -_halfBoundingx ) 
  {
    _translationVec.setX(-_halfBoundingx);
    moving.setX(0.0f);
  }
  // x bounds
  if( tempPosition.x() >=  _halfBoundingx ) 
  {
    _translationVec.setX( _halfBoundingx);
    moving.setX(0.0f);
  }
  // -y bounds
  if( tempPosition.y() <= -_halfBoundingy ) 
  {
    _translationVec.setY(-_halfBoundingy);
    moving.setY(0.0f);
  }
  // y bound
  if( tempPosition.y() >=  _halfBoundingy ) 
  {
    _translationVec.setY( _halfBoundingy);
    moving.setY(0.0f);
  }
  // -z bounds
  if( tempPosition.z() <= -_halfBoundingz ) 
  {
    _translationVec.setZ(-_halfBoundingz);
    moving.setZ(0.0f);
  }
  // z bounds
  if( tempPosition.z() >=  _halfBoundingz ) 
  {
    _translationVec.setZ( _halfBoundingz);
    moving.setZ(0.0f);
  }

  // add the moving to the translation vector and return the new position
  return _translationVec += moving;
}
