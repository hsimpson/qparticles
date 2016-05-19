// qt includes
#include <QtCore/QTimer>
#include <QtGui/QMouseEvent>
#include <QtCore/QDebug>

// local includes
#include "glwidget.h"

ParticleGLWidget::ParticleGLWidget(const QGLFormat& format, QWidget * parent)
  :QGLWidget(format, parent),
  _bShowFrameRate(true),
  _frames(0),
  _lasttime(0),
  _timebase(0),
  _fps(0.0f),
  _uiParticleCount(0U),
  _fGravity(0.0f),
  _fParticleSize(0.0f),
  _fParticleOpacity(0.0f),
  _fMouseForce(0.0f),
  _bForceActive(false),
  _fMouseLocationX(0.0f),
  _fMouseLocationY(0.0f),
  _vboPositions(QGLBuffer(QGLBuffer::VertexBuffer)),
  _vboVelocity(QGLBuffer(QGLBuffer::VertexBuffer)),
  _clBufferPositions(NULL),
  _clBufferVelocity(NULL),
  _colorSpeed(0.5f),
  _colorMin(0.1f),
  _colorMax(0.6f),  
  _trackball(0.01f, QVector3D(0, 1, 0), TrackBall::Sphere),
  _bKeyLeftPressed(false),
  _bKeyRightPressed(false),
  _bKeyForwardPressed(false),
  _bKeyBackwardPressed(false),
  _bKeyUpPressed(false),
  _bKeyDownPressed(false),
  _viewTranslationVec(0.0f, 0.0f, -10.0f), // initial translation
  _BoundingBox(QVector3D(8.0f, 5.0f, 5.0f)),
  _CrossHair(QVector3D(1.0f, 1.0f, 1.0f), QVector3D(8.0f, 5.0f, 5.0f))
{
 
  _shaderProjectionMatrixLocation[0] = 0;
  _shaderProjectionMatrixLocation[1] = 0;
  
  _shaderViewMatrixLocation[0] = 0;
  _shaderViewMatrixLocation[1] = 0;

  _shaderVertexLocation[0] =0;
  _shaderVertexLocation[1] =0;

  _shaderColorLocation[0] = 0;
  _shaderColorLocation[1] = 0;

  _particleColor.setRedF(_colorMax);
  _particleColor.setGreenF(_colorMin);
  _particleColor.setBlueF(_colorMin);
  _particleColor.setAlphaF(_fParticleOpacity);

  const QVector3D dimension(8.0f, 5.0f, 5.0f);
  _f4BoundingBox.s[0] = dimension.x();
  _f4BoundingBox.s[1] = dimension.y();
  _f4BoundingBox.s[2] = dimension.z();
  _f4BoundingBox.s[3] = 0.0f;

  _f4ForcePosition.s[0] = 0.0f;
  _f4ForcePosition.s[1] = 0.0f;
  _f4ForcePosition.s[2] = 0.0f;
  _f4ForcePosition.s[3] = 0.0f;


  

  // focus handling
  setFocusPolicy(Qt::StrongFocus);


  // render timer
  QTimer* timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
  // 15ms is low enough (1/60s = 60 Hz = 16,66 ms)
  timer->start(0);
}

ParticleGLWidget::~ParticleGLWidget()
{
  destroyVBOs();
}

void ParticleGLWidget::initializeGL()
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  // shader
  QGLShader vertexShader0(QGLShader::Vertex, this);
  if(!vertexShader0.compileSourceFile(":/shaders/boundingbox.vert"))
    qCritical() << "ERROR adding shader ':/shaders/boundingbox.vert': " << vertexShader0.log();

  QGLShader vertexShader1(QGLShader::Vertex, this);
  if(!vertexShader1.compileSourceFile(":/shaders/particle.vert"))
    qCritical() << "ERROR adding shader ':/shaders/particle.vert': " << vertexShader1.log();

  QGLShader geometryShader(QGLShader::Geometry, this);
  if(!geometryShader.compileSourceFile(":/shaders/particle_cube.geom"))
    qCritical() << "ERROR adding shader ':/shaders/particle_cube.geom': " << geometryShader.log();

  QGLShader fragmentShader0(QGLShader::Fragment, this);
  if(!fragmentShader0.compileSourceFile(":/shaders/boundingbox.frag"))
    qCritical() << "ERROR adding shader ':/shaders/boundingbox.frag': " << fragmentShader0.log();

  QGLShader fragmentShader1(QGLShader::Fragment, this);
  if(!fragmentShader1.compileSourceFile(":/shaders/particle.frag"))
    qCritical() << "ERROR adding shader ':/shaders/particle.frag': " << fragmentShader1.log();

  _shaderProgram[0].addShader(&vertexShader0);
  _shaderProgram[0].addShader(&fragmentShader0);

  /*
  _shaderProgram[1].addShader(&vertexShader1);
  _shaderProgram[1].addShader(&geometryShader);
  _shaderProgram[1].addShader(&fragmentShader1);
  */
  _shaderProgram[1].addShader(&vertexShader0);  
  _shaderProgram[1].addShader(&fragmentShader0);

  if(!_shaderProgram[0].link())
    qCritical() << "ERROR link shader program: " << _shaderProgram[0].log();
  if(!_shaderProgram[1].link())
    qCritical() << "ERROR link shader program: " << _shaderProgram[1].log();

  
  _shaderProjectionMatrixLocation[0] = _shaderProgram[0].uniformLocation("projectionMatrix");
  _shaderViewMatrixLocation[0]       = _shaderProgram[0].uniformLocation("viewMatrix");
  _shaderModelMatrixLocation[0]      = _shaderProgram[0].uniformLocation("modelViewMatrix");
  _shaderVertexLocation[0]           = _shaderProgram[0].attributeLocation("vertex");
  _shaderColorLocation[0]            = _shaderProgram[0].attributeLocation("color");

  _shaderProjectionMatrixLocation[1] = _shaderProgram[1].uniformLocation("projectionMatrix");
  _shaderViewMatrixLocation[1]       = _shaderProgram[1].uniformLocation("viewMatrix");
  _shaderModelMatrixLocation[1]      = _shaderProgram[1].uniformLocation("modelViewMatrix");
  _shaderVertexLocation[1]           = _shaderProgram[1].attributeLocation("vertex");
  _shaderColorLocation[1]            = _shaderProgram[1].attributeLocation("color");

  QMatrix4x4 m;
 
  // set identity matrices
  _shaderProgram[0].bind();
  _shaderProgram[0].setUniformValue(_shaderProjectionMatrixLocation[0], m);
  _shaderProgram[0].setUniformValue(_shaderViewMatrixLocation[0], m);
  _shaderProgram[0].setUniformValue(_shaderModelMatrixLocation[0], m);
  _shaderProgram[0].release();

  
  _shaderProgram[1].bind();
  _shaderProgram[1].setUniformValue(_shaderProjectionMatrixLocation[1], m);
  _shaderProgram[1].setUniformValue(_shaderViewMatrixLocation[1], m);
  _shaderProgram[1].setUniformValue(_shaderModelMatrixLocation[1], m);
  _shaderProgram[1].release();
  

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  glEnable(GL_LINE_SMOOTH);

  // create the objects
  _BoundingBox.create(&_shaderProgram[0]);
  _CrossHair.create(&_shaderProgram[0]);
  
  // init OpenCL stuff
  initializeCL();
}

void ParticleGLWidget::resizeGL( int w, int h )
{
  if(h == 0)
    h = 1;
  glViewport(0, 0, w, h);

  
  // set the projection matrix
  // first make it identity and then calculate the new projection matrix
  _projectionMatrix.setToIdentity();
  _projectionMatrix.perspective(60.0f, (float)w/float(h), 0.1f, 100.0f);

  // set the projection matrix every time it changes (when resizing the QGLWidget)
  _shaderProgram[0].bind();
  _shaderProgram[0].setUniformValue(_shaderProjectionMatrixLocation[0], _projectionMatrix);
  _shaderProgram[0].release();

  _shaderProgram[1].bind();
  _shaderProgram[1].setUniformValue(_shaderProjectionMatrixLocation[1], _projectionMatrix);
  _shaderProgram[1].release();

  // TODO: do i need really a call on resize? Maybe the kernel resize code 
  // could be omitted completely?
  runKernel(F_RESIZE);
}

void ParticleGLWidget::paintGL()
{
  int framebegin = _frameBase.elapsed();
  runKernel(F_UPDATE);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  
  // set up the view matrix
  QMatrix4x4 viewMatrix;
  viewMatrix.translate(_viewTranslationVec);
  viewMatrix.rotate(_viewRotationQuat);

  _shaderProgram[0].bind();
  _shaderProgram[0].setUniformValue(_shaderViewMatrixLocation[0], viewMatrix);
  _shaderProgram[0].release();

  _shaderProgram[1].bind();
  _shaderProgram[1].setUniformValue(_shaderViewMatrixLocation[1], viewMatrix);
  _shaderProgram[1].release();

  // render the other objects
  _BoundingBox.render();

  // do cross hair moving stuff before render it
  QVector3D movevector;
  if(_bKeyLeftPressed   && !_bKeyRightPressed) movevector.setX(-1.0f);
  if(_bKeyRightPressed  && !_bKeyLeftPressed)  movevector.setX( 1.0f);

  if(_bKeyForwardPressed   && !_bKeyBackwardPressed) movevector.setZ(-1.0f);
  if(_bKeyBackwardPressed  && !_bKeyForwardPressed)  movevector.setZ( 1.0f);

  if(_bKeyUpPressed    && !_bKeyDownPressed) movevector.setY( 1.0f);
  if(_bKeyDownPressed  && !_bKeyUpPressed)   movevector.setY(-1.0f);
  
  QVector3D newmovevector = _CrossHair.translate(movevector);
  if(!newmovevector.isNull())
  {
    _f4ForcePosition.s[0] = newmovevector.x();
    _f4ForcePosition.s[1] = newmovevector.y();
    _f4ForcePosition.s[2] = newmovevector.z();
  }

  _CrossHair.render();

  // draw the particles
  drawParticles();

  // frame rate display
  int frameend = _frameBase.elapsed();
  int duration = frameend-framebegin;
  _timebase +=duration;  
  if(_timebase >= 1000) // calculate every second only
  {
    _fps = 1000.0f/(float)(duration);    
    _timebase = 0;
  }
  if(_bShowFrameRate && _fps > 0)
  {
    /*
    qglColor(Qt::white);
    renderText(5,10, QString("FPS: ")+QString::number(_fps));
    */
    QString strFps = QString("qParticles - FPS: %1").arg(_fps, 0, 'f',2);
    parentWidget()->setWindowTitle(strFps);
  }

  
  GLenum error=glGetError();
  if(error)
  {
    QString errstr = QString::fromAscii((const char*)(gluErrorString(error)));
    qWarning() << errstr;
  }
}

void ParticleGLWidget::initializeCL()
{
  // create the OpenCL Context (with OpenGL interop in this case)
  if(!_clContext.create())
    qFatal("Could not create the OpenCL context");

  // create a program
  _clProgram = _clContext.buildProgramFromSourceFile(":/clkernels/particle_kernel.cl");
  // create the kernel
  _clKernel = _clProgram.createKernel("particle_kernel");

  _frameBase.start();
  createVBOs();
}

void ParticleGLWidget::setProperties( const QHash<SettingsDock::Property, QVariant>& properties )
{
  unsigned int newParticleCount = properties[SettingsDock::ParticleCount]   .value<unsigned int>();
  
  // first call
  if(_uiParticleCount == 0)
    _uiParticleCount = newParticleCount;

  // if the new count of particles, different from the old one, then reinitialize the VBOs
  if(_uiParticleCount != newParticleCount)
  {
    _uiParticleCount = newParticleCount;
    createVBOs();
  }  
  _fGravity         = properties[SettingsDock::Gravity]         .value<float>();
  _fParticleSize    = properties[SettingsDock::ParticleSize]    .value<float>();
  _fParticleOpacity = properties[SettingsDock::ParticleOpacity] .value<float>();
  _fMouseForce      = properties[SettingsDock::Force]      .value<float>();
}

void ParticleGLWidget::runKernel( int function )
{
  
  float deltatime = (float)(_frameBase.elapsed() - _lasttime)/ 1000.0f;
  _lasttime = _frameBase.elapsed();
  
  // ensure OpenGL is finished
  glFinish();
  _clKernel.setArg( 2, function);
  _clKernel.setArg( 3, _uiParticleCount);
  _clKernel.setArg( 4, deltatime);
  _clKernel.setArg( 5, (const void*)&_f4BoundingBox, sizeof(cl_float4));
  _clKernel.setArg( 6, _fGravity);
  _clKernel.setArg( 7, _bForceActive);
  _clKernel.setArg( 8, _fMouseForce);
  _clKernel.setArg( 9, (const void*)&_f4ForcePosition, sizeof(cl_float4));


  // map OpenGL position VBO
  _clContext.acquire(*_clBufferPositions).waitForFinished();
  _clContext.acquire(*_clBufferVelocity).waitForFinished();

  // run kernel
  _clKernel.setGlobalWorkSize(_uiParticleCount);
  _clKernel.run().waitForFinished();

  // release the VBOs
  _clContext.release(*_clBufferPositions).waitForFinished();
  _clContext.release(*_clBufferVelocity).waitForFinished();
  
}

void ParticleGLWidget::createVBOs()
{
  
  // first check if we have to destroy them
  destroyVBOs();
  int size = _uiParticleCount * 4 * sizeof(float);
  _vboPositions.create();
  _vboPositions.bind();
  _vboPositions.setUsagePattern(QGLBuffer::DynamicDraw);
  _vboPositions.allocate(size);
  //_vboPositions.release(); this makes later draws crashing

  
  _vboVelocity.create();
  _vboVelocity.bind();
  _vboVelocity.setUsagePattern(QGLBuffer::DynamicDraw);
  _vboVelocity.allocate(size);
  //_vboVelocity.release();  this makes later draws crashing


  // now create the OpenCL buffer objects
  _clBufferPositions = new QCLBuffer(_clContext.createGLBuffer(&_vboPositions, QCLMemoryObject::ReadWrite));
  _clBufferVelocity  = new QCLBuffer(_clContext.createGLBuffer(&_vboVelocity,  QCLMemoryObject::ReadWrite));

  // setting the buffer objects as the first 2 kernel args
  _clKernel.setArg(0, *_clBufferPositions);
  _clKernel.setArg(1, *_clBufferVelocity);

  runKernel(F_INIT);
}

void ParticleGLWidget::destroyVBOs()
{
  // check if they are created and then destroy them
  if(_vboPositions.isCreated() && _vboVelocity.isCreated())
  {
    if(_clBufferPositions && _clBufferVelocity)
    {
      delete _clBufferPositions;
      _clBufferPositions = 0;
      delete _clBufferVelocity;
      _clBufferVelocity = 0;
    }    
    _vboPositions.destroy();
    _vboVelocity.destroy();
  }
}

void ParticleGLWidget::mouseMoveEvent( QMouseEvent * event )
{
  if(event->buttons() & Qt::LeftButton)
  {
    _trackball.move(pixelPosToViewPos(event->posF()), QQuaternion());    
    _viewRotationQuat = _trackball.rotation();    
    event->accept();
  }
  else
  {
    _trackball.release(pixelPosToViewPos(event->posF()), QQuaternion());
  }
}

void ParticleGLWidget::mousePressEvent( QMouseEvent * event )
{
  if(event->button() & Qt::LeftButton)
  {
    _trackball.push(pixelPosToViewPos(event->posF()), QQuaternion());
    event->accept();
  }
}

void ParticleGLWidget::mouseReleaseEvent( QMouseEvent * event )
{
  if(event->button() & Qt::LeftButton)
  {
    _trackball.release(pixelPosToViewPos(event->posF()), QQuaternion());    
    event->accept();
  }
}

void ParticleGLWidget::wheelEvent( QWheelEvent * event )
{
  float delta = (float)event->delta()/200;
  _viewTranslationVec += QVector3D(0.0f, 0.0f, delta);  
}

void ParticleGLWidget::modifyColor()
{
  float red   = _particleColor.redF();
  float green = _particleColor.greenF();
  float blue  = _particleColor.blueF();

  static unsigned int state		= 0;	//holds which state we are in
  switch(state) {							// (R, G, B)
  case(0):								//(High, Increasing, Low)
    green  += _colorSpeed*1.0f/255.0f;
    if(green >= _colorMax)
    {
      state = 1;
      green = _colorMax;
    }
    break;
  case(1):								//(Decreasing, High, Low)
    red  -= _colorSpeed*1.0f/255.0f;
    if(red <= _colorMin)
    {
      state = 2;
      red = _colorMin;
    }
    break;
  case(2):								//(Low, High, Increasing)
    blue  += _colorSpeed*1.0f/255.0f;
    if(blue >= _colorMax)
    {
      state = 3;
      blue = _colorMax;
    }
    break;
  case(3):								//(Low, Decreasing, High)
    green  -= _colorSpeed*1.0f/255.0f;
    if(green <= _colorMin)
    {
      state = 4;
      green = _colorMin;
    }
    break;
  case(4):								//(Increasing, Low, High)
    red  += _colorSpeed*1.0f/255.0f;
    if(red >= _colorMax)
    {
      state = 5;
      red = _colorMax;
    }
    break;
  case(5):								//(High, Low, Decreasing)
    blue  -= _colorSpeed*1.0f/255.0f;
    if(blue <= _colorMin)
    {
      state = 0;
      blue = _colorMin;
    }
    break;
  } 

  _particleColor.setRedF(red);
  _particleColor.setGreenF(green);
  _particleColor.setBlueF(blue);
  _particleColor.setAlphaF(_fParticleOpacity);
}

QPointF ParticleGLWidget::pixelPosToViewPos( const QPointF& p )
{
  return QPointF(2.0 * float(p.x()) / width() - 1.0,
                 1.0 - 2.0 * float(p.y()) / height());
}

void ParticleGLWidget::keyPressEvent(QKeyEvent *event)
{
  
  switch(event->key())
  {
    case Qt::Key_Space:
      _bForceActive = true;
      _CrossHair.highlight(true);
      break;
    case Qt::Key_A:
      _bKeyLeftPressed = true;
      break;
    case Qt::Key_D:
      _bKeyRightPressed = true;
      break;
    case Qt::Key_W:
      _bKeyForwardPressed = true;
      break;
    case Qt::Key_S:
      _bKeyBackwardPressed = true;
      break;
    case Qt::Key_PageUp:
      _bKeyUpPressed = true;
      break;
    case Qt::Key_PageDown:
      _bKeyDownPressed = true;
      break;
  }
}

void ParticleGLWidget::keyReleaseEvent(QKeyEvent *event)
{
  switch(event->key())
  {
  case Qt::Key_Space:
    _bForceActive = false;
    _CrossHair.highlight(false);
    break;
  case Qt::Key_A:
    _bKeyLeftPressed = false;
    break;
  case Qt::Key_D:
    _bKeyRightPressed = false;
    break;
  case Qt::Key_W:
    _bKeyForwardPressed = false;
    break;
  case Qt::Key_S:
    _bKeyBackwardPressed = false;
    break;
  case Qt::Key_PageUp:
    _bKeyUpPressed = false;
    break;
  case Qt::Key_PageDown:
    _bKeyDownPressed = false;
    break;
  }
}

void ParticleGLWidget::drawParticles()
{
  // set identity matrix
  _shaderProgram[1].bind();


  _shaderProgram[1].setUniformValue(_shaderModelMatrixLocation[1], QMatrix4x4());

  
  _vboPositions.bind();
  
  glPointSize(_fParticleSize);
  modifyColor();
  
  _particleColor.setAlphaF(_fParticleOpacity);

  _shaderProgram[1].enableAttributeArray(_shaderVertexLocation[1]);
  _shaderProgram[1].setAttributeBuffer(_shaderVertexLocation[1], GL_FLOAT, 
                                    0, 3, 4*sizeof(float));
  _shaderProgram[1].setAttributeValue(_shaderColorLocation[1], _particleColor);
  
  glDrawArrays(GL_POINTS, 0, _uiParticleCount);
  
  
  _shaderProgram[1].disableAttributeArray(_shaderVertexLocation[1]);
  _vboPositions.release();
  _shaderProgram[1].release();
}
