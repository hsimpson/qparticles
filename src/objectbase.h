#ifndef objectbase_h__
#define objectbase_h__

#include <QVarLengthArray>
#include <QGLBuffer>
#include <QVector3D>
#include <QMatrix4x4>
#include <QQuaternion>

#include <QGLShaderProgram>


/*!
 * \brief
 * Abstract base class for OpenGL objects
 */
class AbstractObjectBase
{
public:
  AbstractObjectBase();
  virtual ~AbstractObjectBase();

  // create the object (automatically setup the shader variables and call
  
  void create(QGLShaderProgram* shaderProgram);
  virtual const QVector3D& translate(const QVector3D& vec);
  void rotate(const QQuaternion& quat);
  void render();
  const QMatrix4x4& modelMatrix() const;

protected:
  // vertex
  struct Vertex
  {   
    // position
    GLfloat x,y,z;
    // color
    GLfloat r,g,b,a;
    Vertex() 
      : x(0.0f), y(0.0f), z(0.0f), 
      r(0.0f), g(0.0f), b(0.0f), a(1.0f)
    {};
    Vertex(GLfloat x, GLfloat y, GLfloat z, 
      GLfloat r, GLfloat g, GLfloat b, GLfloat a=1.0f ) 
      : x(x), y(y), z(z), 
      r(r), g(g), b(b), a(a)
    {};
  };
  void addVertex(const Vertex &v);
  void addIndex(const GLushort i);

  GLushort indexCount();

  virtual void createGeometry()=0;
  virtual void draw();
  virtual void setupShader();

  QGLBuffer& bufferVBO();
  QGLBuffer& bufferIBO();
  QGLShaderProgram* shader();
  GLuint vertexLocation();
  GLuint colorLocation();

  // the model matrix
  QMatrix4x4  _modelViewMatrix;
  // the rotation quaternion
  QQuaternion _rotationQuat;
  // the translation vector
  QVector3D   _translationVec;

private:
  void setupShader_internal();
  void draw_internal();

  // the shader program
  QGLShaderProgram* _shaderProgram;
  // the VBO with vertex data and color data
  QGLBuffer _VBO;
  // the IBO with indices to the vertices for the object
  QGLBuffer _IBO;  

  /* shader location variables */
  // the shader location for the vertex
  GLuint _shaderVertexLocation;
  // the shader location for the color
  GLuint _shaderColorLocation;
  // the model view matrix location
  GLuint _shaderModelViewMatrixLocation;
  // the array of vertices
  QVarLengthArray<Vertex>   _vertices;
  // the array of vertex indices
  QVarLengthArray<GLushort> _verticexIndices;
};

#endif // objectbase_h__
