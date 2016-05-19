#include "objectbase.h"


AbstractObjectBase::AbstractObjectBase()
  : _shaderProgram(NULL),
    _VBO(QGLBuffer::VertexBuffer),
    _IBO(QGLBuffer::IndexBuffer),
    _shaderVertexLocation(0),
    _shaderColorLocation(0),
    _shaderModelViewMatrixLocation(0)
{

}

AbstractObjectBase::~AbstractObjectBase()
{

}

/*!
 * \brief
 * Translates the object
 * 
 * \param vec
 * The Vector for the translation
 */
const QVector3D& AbstractObjectBase::translate( const QVector3D& vec )
{
  return _translationVec += vec;
}

/*!
 * \brief
 * Rotates the object
 * 
 * \param quat
 * The Quaternion for the rotation
 */
void AbstractObjectBase::rotate( const QQuaternion& quat )
{
  _rotationQuat = quat;
}


/*!
 * \brief
 * Render the object
 * 
 * The base class do basic matrix stuff:
 * set model view matrix to identity and do translation and rotation
 * if you need to manipulate the model matrix internally you have
 * to do this in the draw function
 */
void AbstractObjectBase::render()
{
  draw_internal();
}

/*!
 * \brief
 * Setup additional shader stuff, base class implementation does nothing
 */
void AbstractObjectBase::setupShader()
{
  
}

void AbstractObjectBase::create( QGLShaderProgram* shaderProgram )
{
  _shaderProgram = shaderProgram;
  // setup the shader location variables
  setupShader_internal();
  // create the geometry
  createGeometry();

  // setup the buffers after geometry generation
  _VBO.create();
  _IBO.create();

  _VBO.bind();
  _IBO.bind();

  _VBO.setUsagePattern(QGLBuffer::StaticDraw);
  _IBO.setUsagePattern(QGLBuffer::StaticDraw);

  _VBO.allocate(_vertices.data(), sizeof(Vertex)*_vertices.size());
  _IBO.allocate(_verticexIndices.data(), sizeof(GLushort)*_verticexIndices.size());
}

/*!
 * \brief
 * Add a vertex to the array
 */
void AbstractObjectBase::addVertex( const Vertex &v )
{
  _vertices.append(v);
}

/*!
 * \brief
 * Add an index the the array
 */
void AbstractObjectBase::addIndex( const GLushort i )
{
  _verticexIndices.append(i);
}

void AbstractObjectBase::setupShader_internal()
{
  _shaderProgram->bind();
  _shaderVertexLocation          = _shaderProgram->attributeLocation("vertex");
  _shaderColorLocation           = _shaderProgram->attributeLocation("color");
  _shaderModelViewMatrixLocation = _shaderProgram->uniformLocation("modelViewMatrix");
  setupShader();
  _shaderProgram->release();
}

/*!
 * \brief
 * Returns the VBO buffer
 */
QGLBuffer& AbstractObjectBase::bufferVBO()
{
  return _VBO;
}

/*!
 * \brief
 * Returns the IBO buffer 
 */
QGLBuffer& AbstractObjectBase::bufferIBO()
{
  return _IBO;
}

/*!
 * \brief
 * Returns the Shader Program 
 */
QGLShaderProgram* AbstractObjectBase::shader()
{
  return _shaderProgram;
}

/*!
 * \brief
 * Returns the shader location of the vertex
 */
GLuint AbstractObjectBase::vertexLocation()
{
  return _shaderVertexLocation;
}

/*!
 * \brief
 * Returns the shader location of the color
 */
GLuint AbstractObjectBase::colorLocation()
{
  return _shaderColorLocation;
}

/*!
 * \brief
 * Returns count of vertices
 */
GLushort AbstractObjectBase::indexCount()
{
  return _verticexIndices.size();
}

void AbstractObjectBase::draw_internal()
{
  _shaderProgram->bind();
  _modelViewMatrix.setToIdentity();
  _modelViewMatrix.translate(_translationVec);
  _modelViewMatrix.rotate(_rotationQuat);

  // set the Model View Matrix into the shader
  _shaderProgram->setUniformValue(_shaderModelViewMatrixLocation, _modelViewMatrix);
  draw();
  _shaderProgram->release();
}


/*!
 * \brief
 * Draw of the object
 * 
 * \throws <exception class>
 * Description of criteria for throwing this exception.
 * 
 * Base class implementation does nothing
 */
void AbstractObjectBase::draw()
{

}

const QMatrix4x4& AbstractObjectBase::modelMatrix() const
{
  return _modelViewMatrix;
}