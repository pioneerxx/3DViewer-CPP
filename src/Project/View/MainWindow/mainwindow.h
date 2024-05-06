#ifndef SRC_VIEW_MAINWINDOW_MAINWINDOW_H
#define SRC_VIEW_MAINWINDOW_MAINWINDOW_H

#include <stdlib.h>

#include <QBuffer>
#include <QCloseEvent>
#include <QColor>
#include <QColorDialog>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QImage>
#include <QMainWindow>
#include <QMessageBox>
#include <QMovie>
#include <QSettings>
#include <QTimer>
#include <cstring>
#include <fstream>
#include <string>

#include "../GLWidget/glwidget.h"
#include "qgifimage.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(Controller *controller, QWidget *parent = nullptr);
  ~MainWindow();

 private:
  void connectionSetup();
  void openFile();
  void rotateX(int value);
  void rotateY(int value);
  void rotateZ(int value);
  void translateX(int value);
  void translateY(int value);
  void translateZ(int value);
  void translateXManually(int value);
  void translateYManually(int value);
  void translateZManually(int value);
  void rotateXManually(int value);
  void rotateYManually(int value);
  void rotateZManually(int value);
  void scale(int value);
  void scaleManually(int value);
  void projectionPerspective();
  void projectionOrthogonal();
  void verticesTypeChange(int index);
  void verticesSizeChange(int index);
  void verticesSizeChangeManually(int value);
  void edgesTypeChange(int index);
  void edgesSizeChange(int index);
  void edgesSizeChangeManually(int value);
  void backgroundColorChange();
  void edgesColorChange();
  void verticesColorChange();
  void defaultSettings();
  Memento *saveMemento();
  void reinstateMemento(int mementoNumber);
  void historyHandler(Memento *mem);
  void closeEvent(QCloseEvent *event) override;
  void restoreConfig();
  bool checkConfig();
  void saveImage();
  void recordGif();
  void timerAction();
  void setLabel(QString fileName, QString name, QString verticesSize,
                QString facetsSize);
  void setFrame(QString bg, QString vertices, QString edges);
  void setColor(QString bg, QString vertices, QString edges);

 private:
  Ui::MainWindow *ui_;
  s21::Controller *controller_;
  QString configFile_;
  void connectSetup();
  std::list<QAction *> history_;
  QImage gifImage[50];
  QTimer timer;
  QGifImage *gif;
  int giftime = 0;
};

}  // namespace s21

#endif  // SRC_VIEW_MAINWINDOW_MAINWINDOW_H
