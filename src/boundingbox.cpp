#include "boundingbox.h"




BoundingBox::BoundingBox(const QVector3D& dimensions)
  : AbstractObjectBase(),
   _dimensions(dimensions)
{

}

BoundingBox::~BoundingBox()
{ 
}


void BoundingBox::createGeometry()
{
  // create the vertices
  float halfx = _dimensions.x()/2;
  float halfy = _dimensions.y()/2;
  float halfz = _dimensions.z()/2;
  
  //unsigned int col = 0x55555555; // pure white and opaque
  /* the cube:
    

       v5-----------v6
      / |          / |
     /  |         /  |
    v2----------v1   |
    |   |        |   |
    |   |        |   |
    |  v4--------|--v7 
    | /          |  /
    |/           | /
    v3-----------v0


  */
  // front vertices:
  
  addVertex(Vertex( halfx, -halfy,  -halfz,  1.0f, 1.0f, 1.0f));
  addVertex(Vertex( halfx,  halfy,  -halfz,  1.0f, 1.0f, 1.0f));
  addVertex(Vertex(-halfx,  halfy,  -halfz,  1.0f, 1.0f, 1.0f));
  addVertex(Vertex(-halfx, -halfy,  -halfz,  1.0f, 1.0f, 1.0f));
                                                    
  // back vertices:                                               
  addVertex(Vertex(-halfx, -halfy, halfz,  1.0f, 1.0f, 1.0f));
  addVertex(Vertex(-halfx,  halfy, halfz,  1.0f, 1.0f, 1.0f));
  addVertex(Vertex( halfx,  halfy, halfz,  1.0f, 1.0f, 1.0f));
  addVertex(Vertex( halfx, -halfy, halfz,  1.0f, 1.0f, 1.0f));

  
  // create the indices for the lines
  // front
  addIndex(0);  addIndex(1);
  addIndex(1);  addIndex(2);
  addIndex(2);  addIndex(3);
  addIndex(3);  addIndex(0);

  // left
  addIndex(3);  addIndex(2);
  addIndex(2);  addIndex(5);
  addIndex(5);  addIndex(4);
  addIndex(4);  addIndex(3);

  // right
  addIndex(7);  addIndex(6);
  addIndex(6);  addIndex(1);
  addIndex(1);  addIndex(0);
  addIndex(0);  addIndex(7);

  // back
  addIndex(4);  addIndex(5);
  addIndex(5);  addIndex(6);
  addIndex(6);  addIndex(7);
  addIndex(7);  addIndex(4);
}


void BoundingBox::draw()
{  
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

  // release the buffers
  bufferVBO().release();
  bufferIBO().release();
}