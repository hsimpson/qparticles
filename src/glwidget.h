#ifndef glwidget_h__
#define glwidget_h__

// qt includes
#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLBuffer>
#include <QtOpenGL/QGLShaderProgram>
#include <QtCore/QTime>
#include <QtCore/QPointF>

// qt-opencl
#include "qclcontextgl.h"

// local includes
#include "settings.h"
#include "trackball.h"
#include "boundingbox.h"
#include "crosshair.h"



#define F_INIT   0
#define F_UPDATE 1
#define F_RESIZE 2

class ParticleGLWidget : public QGLWidget
{
  Q_OBJECT;
public: 
  ParticleGLWidget(const QGLFormat& format, QWidget * parent = 0);
  ~ParticleGLWidget();

public slots:
  void setProperties(const QHash<SettingsDock::Property, QVariant>& properties);

protected:
  virtual void initializeGL();
  virtual void resizeGL(int w, int h);
  virtual void paintGL();
  virtual void mouseMoveEvent ( QMouseEvent * event );
  virtual void mousePressEvent ( QMouseEvent * event );
  virtual void mouseReleaseEvent ( QMouseEvent * event );
  virtual void wheelEvent ( QWheelEvent * event );
  virtual void keyPressEvent ( QKeyEvent * event );
  virtual void keyReleaseEvent( QKeyEvent * event );

private:
  //void calcFps();
  void createVBOs();
  void destroyVBOs();
  void initializeCL();
  void runKernel(int function);
  void modifyColor();
  

  void drawParticles();
  QPointF pixelPosToViewPos(const QPointF& p);


  bool      _bShowFrameRate;
  int       _frames;
  int       _lasttime;
  int       _timebase;
  float     _fps;


  QTime     _frameBase;





  QCLContextGL _clContext;
  QCLProgram   _clProgram;
  QCLKernel    _clKernel;

  // properties
  unsigned int  _uiParticleCount;
  float         _fGravity;
  float         _fParticleSize;
  float         _fParticleOpacity;
  float         _fMouseForce;
  bool          _bForceActive;
  float         _fMouseLocationX;
  float         _fMouseLocationY;


  // the VBOs
  QGLBuffer _vboPositions;
  QGLBuffer _vboVelocity;
  QCLBuffer* _clBufferPositions;
  QCLBuffer* _clBufferVelocity;

  // color properties
  float         _colorSpeed;
  float         _colorMin;
  float         _colorMax;
  QColor        _particleColor;

  // translation  
  cl_float4   _f4BoundingBox;
  TrackBall   _trackball;

  cl_float4 _f4ForcePosition;

  // keys
  bool _bKeyLeftPressed;
  bool _bKeyRightPressed;
  bool _bKeyForwardPressed;
  bool _bKeyBackwardPressed;
  bool _bKeyUpPressed;
  bool _bKeyDownPressed;

  // shader
  // matrices
  QMatrix4x4 _projectionMatrix;
  QVector3D _viewTranslationVec;
  QQuaternion _viewRotationQuat;
  
  QGLShaderProgram _shaderProgram[2];
  /* shader location variables */
  // the projection matrix
  int _shaderProjectionMatrixLocation[2];
  // the view matrix
  int _shaderViewMatrixLocation[2];
  // the model matrix location;
  int _shaderModelMatrixLocation[2];
  // the vertex
  int _shaderVertexLocation[2];
  // the color
  int _shaderColorLocation[2];
  BoundingBox _BoundingBox;
  CrossHair _CrossHair;
};
#endif // glwidget_h__
