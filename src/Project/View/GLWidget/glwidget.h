#ifndef SRC_VIEW_GLWIDGET_GLWIDGET_H
#define SRC_VIEW_GLWIDGET_GLWIDGET_H

#define GL_SILENCE_DEPRECATION

#include <stdlib.h>

#include <QColor>
#include <QColorDialog>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QMainWindow>
#include <QOpenGLWidget>
#include <QPushButton>
#include <QSettings>
#include <QTimer>
#include <algorithm>
#include <cstring>

#include "../../Controller/Controller/Controller.h"

namespace s21 {

class GLWidget : public QOpenGLWidget {
  Q_OBJECT
 public:
  GLWidget(QWidget *parent = nullptr);
  ~GLWidget();
  void initSettings();
  Controller *controller_;
  void initController(Controller *controller);
  void newObject(const std::string &fileName);

  void setBackgroundColor(QColor color);
  void setVerticesColor(QColor color);
  void setEdgesColor(QColor color);
  void setProjectionMode(int value);
  void setVerticesType(int value);
  void setEdgesType(int value);
  void setVerticesSize(int value);
  void setEdgesSize(int value);

  QColor getBackgroundColor();
  QColor getVerticesColor();
  QColor getEdgesColor();
  int getProjectionMode();
  int getVerticesType();
  int getEdgesType();
  int getVerticesSize();
  int getEdgesSize();

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private:
  void setupProjection();
  void setupVertices();
  void setupEdges();

  QColor backgroundColor_;
  QColor edgesColor_;
  QColor verticesColor_;
  int projectionMode_;
  int verticesType_;
  int edgesType_;
  int verticesSize_;
  int edgesSize_;
};

}  // namespace s21

#endif  // SRC_VIEW_GLWIDGET_GLWIDGET_H
