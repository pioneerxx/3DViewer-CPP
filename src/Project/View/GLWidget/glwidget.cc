#include "glwidget.h"

s21::GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) {
  initSettings();
}

s21::GLWidget::~GLWidget() { controller_->clearFigure(); }

void s21::GLWidget::initController(Controller *controller) {
  controller_ = controller;
}

void s21::GLWidget::newObject(const std::string &fileName) {
  controller_->newObject(fileName);
}

void s21::GLWidget::initSettings() {
  setBackgroundColor(QColor::fromRgb(0, 0, 0));
  setVerticesColor(QColor::fromRgb(255, 255, 255));
  setEdgesColor(QColor::fromRgb(255, 255, 255));
  setProjectionMode(0);
  setVerticesType(2);
  setEdgesType(0);
  setVerticesSize(1);
  setEdgesSize(1);
}

void s21::GLWidget::initializeGL() {
  setupProjection();
  glEnable(GL_DEPTH_TEST);
}

void s21::GLWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
}

void s21::GLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  setupProjection();
  glVertexPointer(3, GL_DOUBLE, 0, controller_->getVertexes().data());
  setupEdges();
  setupVertices();
  update();
}

void s21::GLWidget::setupProjection() {
  double maxC = 0.00001 + controller_->getMaxC();
  if (getProjectionMode() == 0) {
    glOrtho(-maxC * 1.1, maxC * 1.1, -maxC * 1.1, maxC * 1.1, -maxC * 1.1,
            maxC * 5);
  } else if (getProjectionMode() == 1) {
    double fov = 60.0 * M_PI / 180;
    double heapHeight = maxC / (2 * tan(fov / 2));
    glFrustum(-maxC, maxC, -maxC, maxC, heapHeight, heapHeight * 20);
    glTranslated(0, 0, -heapHeight * 3);
  }
}

void s21::GLWidget::setupVertices() {
  if (getVerticesType() != 2) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3d(getVerticesColor().redF(), getVerticesColor().greenF(),
              getVerticesColor().blueF());
    if (getVerticesType() == 0) {
      glEnable(GL_POINT_SMOOTH);
      glDrawArrays(GL_POINTS, 0, controller_->getVertexesSize() / 3);
      glDisable(GL_POINT_SMOOTH);
    } else if (getVerticesType() == 1) {
      glDrawArrays(GL_POINTS, 0, controller_->getVertexesSize() / 3);
    }
    glDisable(GL_POINT_SMOOTH);
    glPointSize(getVerticesSize());
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void s21::GLWidget::setupEdges() {
  glEnableClientState(GL_VERTEX_ARRAY);
  glClearColor(getBackgroundColor().redF(), getBackgroundColor().greenF(),
               getBackgroundColor().blueF(), getBackgroundColor().alphaF());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLineWidth(10);
  glColor3f(getEdgesColor().redF(), getEdgesColor().greenF(),
            getEdgesColor().blueF());
  if (getEdgesType() == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(10, 0x3333);
  } else if (getEdgesType() == 0) {
    glDisable(GL_LINE_STIPPLE);
  }
  glLineWidth(getEdgesSize());
  glDrawElements(GL_LINES, controller_->getPolygonsSize(), GL_UNSIGNED_INT,
                 controller_->getPolygons().data());
  glDisableClientState(GL_VERTEX_ARRAY);
}

void s21::GLWidget::setBackgroundColor(QColor color) {
  backgroundColor_ = color;
}
void s21::GLWidget::setVerticesColor(QColor color) { verticesColor_ = color; }
void s21::GLWidget::setEdgesColor(QColor color) { edgesColor_ = color; }
void s21::GLWidget::setProjectionMode(int value) { projectionMode_ = value; }
void s21::GLWidget::setVerticesType(int value) { verticesType_ = value; }
void s21::GLWidget::setEdgesType(int value) { edgesType_ = value; }
void s21::GLWidget::setVerticesSize(int value) { verticesSize_ = value; }
void s21::GLWidget::setEdgesSize(int value) { edgesSize_ = value; }
QColor s21::GLWidget::getBackgroundColor() { return backgroundColor_; }
QColor s21::GLWidget::getVerticesColor() { return verticesColor_; }
QColor s21::GLWidget::getEdgesColor() { return edgesColor_; }
int s21::GLWidget::getProjectionMode() { return projectionMode_; }
int s21::GLWidget::getVerticesType() { return verticesType_; }
int s21::GLWidget::getEdgesType() { return edgesType_; }
int s21::GLWidget::getVerticesSize() { return verticesSize_; }
int s21::GLWidget::getEdgesSize() { return edgesSize_; }
