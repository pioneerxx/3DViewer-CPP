#include "mainwindow.h"

s21::MainWindow::MainWindow(Controller *controller, QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
  controller_ = controller;
  ui_->OGLWidget->initController(controller_);
  connectionSetup();
  setWindowTitle("3DViewer");
  if (checkConfig()) {
    restoreConfig();
  }
  ui_->pushButton_save->setEnabled(0);
  ui_->pushButton_record->setEnabled(0);
}

s21::MainWindow::~MainWindow() {
  delete ui_;
  for (auto i : history_) {
    delete i;
  }
}

void s21::MainWindow::connectionSetup() {
  connect(ui_->pushButton_open, &QPushButton::clicked, this,
          &s21::MainWindow::openFile);
  connect(ui_->scrollBar_translation_x, &QScrollBar::valueChanged, this,
          &s21::MainWindow::translateX);
  connect(ui_->scrollBar_translation_y, &QScrollBar::valueChanged, this,
          &s21::MainWindow::translateY);
  connect(ui_->scrollBar_translation_z, &QScrollBar::valueChanged, this,
          &s21::MainWindow::translateZ);
  connect(ui_->dial_x, &QDial::valueChanged, this, &s21::MainWindow::rotateX);
  connect(ui_->dial_y, &QDial::valueChanged, this, &s21::MainWindow::rotateY);
  connect(ui_->dial_z, &QDial::valueChanged, this, &s21::MainWindow::rotateZ);
  connect(ui_->spinBox_translation_x, &QSpinBox::valueChanged, this,
          &s21::MainWindow::translateXManually);
  connect(ui_->spinBox_translation_y, &QSpinBox::valueChanged, this,
          &s21::MainWindow::translateYManually);
  connect(ui_->spinBox_translation_z, &QSpinBox::valueChanged, this,
          &s21::MainWindow::translateZManually);
  connect(ui_->spinBox_rotate_x, &QSpinBox::valueChanged, this,
          &s21::MainWindow::rotateXManually);
  connect(ui_->spinBox_rotate_y, &QSpinBox::valueChanged, this,
          &s21::MainWindow::rotateYManually);
  connect(ui_->spinBox_rotate_z, &QSpinBox::valueChanged, this,
          &s21::MainWindow::rotateZManually);
  connect(ui_->rollBar_scale, &QScrollBar::valueChanged, this,
          &s21::MainWindow::scale);
  connect(ui_->spinBox_scale, &QSpinBox::valueChanged, this,
          &s21::MainWindow::scaleManually);
  connect(ui_->radioButton_perspective, &QRadioButton::pressed, this,
          &s21::MainWindow::projectionPerspective);
  connect(ui_->radioButton_orthogonal, &QRadioButton::pressed, this,
          &s21::MainWindow::projectionOrthogonal);
  connect(ui_->comboBox_vertices, &QComboBox::currentIndexChanged, this,
          &s21::MainWindow::verticesTypeChange);
  connect(ui_->scrollBar_vertices, &QScrollBar::valueChanged, this,
          &s21::MainWindow::verticesSizeChange);
  connect(ui_->spinBox_vertices, &QSpinBox::valueChanged, this,
          &s21::MainWindow::verticesSizeChangeManually);
  connect(ui_->comboBox_edges, &QComboBox::currentIndexChanged, this,
          &s21::MainWindow::edgesTypeChange);
  connect(ui_->scrollBar_edges, &QScrollBar::valueChanged, this,
          &s21::MainWindow::edgesSizeChange);
  connect(ui_->spinBox_edges, &QSpinBox::valueChanged, this,
          &s21::MainWindow::edgesSizeChangeManually);
  connect(ui_->pushButton_bg, &QPushButton::clicked, this,
          &s21::MainWindow::backgroundColorChange);
  connect(ui_->pushButton_vertices, &QPushButton::clicked, this,
          &s21::MainWindow::verticesColorChange);
  connect(ui_->pushButton_edges, &QPushButton::clicked, this,
          &s21::MainWindow::edgesColorChange);
  connect(ui_->pushButton_default, &QPushButton::clicked, this,
          &s21::MainWindow::defaultSettings);
  connect(ui_->pushButton_save, &QPushButton::clicked, this,
          &s21::MainWindow::saveImage);
  connect(ui_->pushButton_record, &QPushButton::clicked, this,
          &s21::MainWindow::recordGif);
  connect(&timer, &QTimer::timeout, this, &MainWindow::timerAction);
}

void s21::MainWindow::historyHandler(Memento *mem) {
  if (!mem) {
    return;
  }
  QAction *tmp =
      new (std::nothrow) QAction(QString::fromStdString(mem->fileName_), this);
  if (!tmp) {
    return;
  }
  history_.push_front(tmp);
  if (history_.size() > 5) {
    tmp = history_.back();
    history_.pop_back();
    delete tmp;
  }
  ui_->menuHistory->clear();
  std::list<QAction *>::iterator it = history_.begin();
  int i = 0;
  while (it != history_.end()) {
    disconnect(*it, &QAction::triggered, nullptr, nullptr);
    ui_->menuHistory->addAction(*it);
    connect(*it, &QAction::triggered, this, [=] { reinstateMemento(i); });
    ++it;
    i++;
  }
}

bool s21::MainWindow::checkConfig() { return controller_->checkConfig(); }

void s21::MainWindow::restoreConfig() {
  std::list<Memento *> *history = controller_->restoreConfig();
  for (auto i = history->rbegin(); i != history->rend(); ++i) {
    historyHandler(*i);
  }
}

void s21::MainWindow::openFile() {
  QFileDialog *fileDialog = new QFileDialog(this);
  if (fileDialog) {
    fileDialog->setDirectory("../../../..");
    fileDialog->setWindowTitle(tr("Choose .obj-file"));
    fileDialog->setNameFilter(tr("(*.obj)"));
    fileDialog->setViewMode(QFileDialog::Detail);
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    QStringList fileNames;
    if (fileDialog->exec()) {
      controller_->clearFigure();
      fileNames = fileDialog->selectedFiles();
      if (fileNames.size() > 0) {
        if (ui_->label_name_info->text().compare("Name: empty")) {
          historyHandler(saveMemento());
        }
        QString fileName = fileNames.at(0);
        if (!controller_->newObject(fileName.toStdString())) {
          QMessageBox::critical(this, "Error", "Unable open the file",
                                QMessageBox::Button::Ok);
        } else {
          ui_->pushButton_save->setEnabled(1);
          ui_->pushButton_record->setEnabled(1);
        }
        defaultSettings();
        setWindowTitle(fileName);
        setLabel(fileName, QFileInfo(fileName).fileName(),
                 QString::number(controller_->getVertexesSize() / 3),
                 QString::number(controller_->getFacetsSize()));
      }
    }
    delete fileDialog;
  }
}

void s21::MainWindow::translateXManually(int value) {
  double old_val = ui_->scrollBar_translation_x->value();
  ui_->scrollBar_translation_x->setValue(value);
  controller_->moveX((value - old_val) * ui_->rollBar_scale->value() / 1500);
  ui_->OGLWidget->update();
}

void s21::MainWindow::translateYManually(int value) {
  double old_val = ui_->scrollBar_translation_y->value();
  ui_->scrollBar_translation_y->setValue(value);
  controller_->moveY((value - old_val) * ui_->rollBar_scale->value() / 1500);
  ui_->OGLWidget->update();
}

void s21::MainWindow::translateZManually(int value) {
  double old_val = ui_->scrollBar_translation_z->value();
  ui_->scrollBar_translation_z->setValue(value);
  controller_->moveZ((value - old_val) * ui_->rollBar_scale->value() / 1500);
  ui_->OGLWidget->update();
}

void s21::MainWindow::rotateXManually(int value) {
  double old_val = ui_->dial_x->value();
  ui_->dial_x->setValue(value);
  controller_->rotationX(value, old_val);
  ui_->OGLWidget->update();
}

void s21::MainWindow::rotateYManually(int value) {
  double old_val = ui_->dial_y->value();
  ui_->dial_y->setValue(value);
  controller_->rotationY(value, old_val);
  ui_->OGLWidget->update();
}

void s21::MainWindow::rotateZManually(int value) {
  double old_val = ui_->dial_z->value();
  ui_->dial_z->setValue(value);
  controller_->rotationZ(value, old_val);
  ui_->OGLWidget->update();
}

void s21::MainWindow::translateX(int value) {
  double old_val = ui_->spinBox_translation_x->value();
  ui_->spinBox_translation_x->setValue(value);
  controller_->moveX((value - old_val) * ui_->rollBar_scale->value() / 1500);
  ui_->OGLWidget->update();
}

void s21::MainWindow::translateY(int value) {
  double old_val = ui_->spinBox_translation_y->value();
  ui_->spinBox_translation_y->setValue(value);
  controller_->moveY((value - old_val) * ui_->rollBar_scale->value() / 1500);
  ui_->OGLWidget->update();
}

void s21::MainWindow::translateZ(int value) {
  double old_val = ui_->spinBox_translation_z->value();
  ui_->spinBox_translation_z->setValue(value);
  controller_->moveZ((value - old_val) * ui_->rollBar_scale->value() / 1500);
  ui_->OGLWidget->update();
}

void s21::MainWindow::rotateX(int value) {
  double old_val = ui_->spinBox_rotate_x->value();
  ui_->spinBox_rotate_x->setValue(value);
  controller_->rotationX(value, old_val);
  ui_->OGLWidget->update();
}

void s21::MainWindow::rotateY(int value) {
  double old_val = ui_->spinBox_rotate_y->value();
  ui_->spinBox_rotate_y->setValue(value);
  controller_->rotationY(value, old_val);
  ui_->OGLWidget->update();
}

void s21::MainWindow::rotateZ(int value) {
  double old_val = ui_->spinBox_rotate_z->value();
  ui_->spinBox_rotate_z->setValue(value);
  controller_->rotationZ(value, old_val);
  ui_->OGLWidget->update();
}

void s21::MainWindow::scale(int value) {
  double val = (double)value / 100;
  double old_val = ui_->spinBox_scale->value() / 100.0;
  ui_->spinBox_scale->setValue(value);
  controller_->scaleX(val / old_val);
  controller_->scaleY(val / old_val);
  controller_->scaleZ(val / old_val);
  ui_->OGLWidget->update();
}

void s21::MainWindow::scaleManually(int value) {
  double val = (double)value / 100;
  double old_val = ui_->rollBar_scale->value() / 100.0;
  ui_->rollBar_scale->setValue(value);
  controller_->scaleX(val / old_val);
  controller_->scaleY(val / old_val);
  controller_->scaleZ(val / old_val);
  ui_->OGLWidget->update();
}

void s21::MainWindow::projectionPerspective() {
  ui_->OGLWidget->setProjectionMode(1);
  ui_->OGLWidget->update();
}

void s21::MainWindow::projectionOrthogonal() {
  ui_->OGLWidget->setProjectionMode(0);
  ui_->OGLWidget->update();
}

void s21::MainWindow::defaultSettings() {
  ui_->OGLWidget->initSettings();
  translateX(0);
  translateY(0);
  translateZ(0);
  rotateX(0);
  rotateY(0);
  rotateZ(0);
  verticesTypeChange(2);
  ui_->comboBox_vertices->setCurrentIndex(2);
  verticesSizeChange(0);
  edgesTypeChange(0);
  ui_->comboBox_edges->setCurrentIndex(0);
  edgesSizeChange(1);
  ui_->radioButton_orthogonal->setChecked(1);
  scale(100);
  setFrame("background-color: black", "background-color: white",
           "background-color: white");
  setColor(QColor::fromRgb(0, 0, 0).name(),
           QColor::fromRgb(255, 255, 255).name(),
           QColor::fromRgb(255, 255, 255).name());
  controller_->restoreDefault();
  ui_->OGLWidget->update();
}

void s21::MainWindow::verticesTypeChange(int index) {
  if (index == 0) {
    ui_->OGLWidget->setVerticesType(0);
    ui_->scrollBar_vertices->setMinimum(1);
    ui_->scrollBar_vertices->setMaximum(10);
    ui_->spinBox_vertices->setMinimum(1);
    ui_->spinBox_vertices->setMaximum(10);
  } else if (index == 1) {
    ui_->OGLWidget->setVerticesType(1);
    ui_->scrollBar_vertices->setMinimum(1);
    ui_->scrollBar_vertices->setMaximum(10);
    ui_->spinBox_vertices->setMinimum(1);
    ui_->spinBox_vertices->setMaximum(10);
  } else if (index == 2) {
    ui_->OGLWidget->setVerticesType(2);
    ui_->scrollBar_vertices->setMinimum(0);
    ui_->scrollBar_vertices->setMaximum(0);
    ui_->spinBox_vertices->setMinimum(0);
    ui_->spinBox_vertices->setMaximum(0);
  }
  ui_->OGLWidget->update();
}

void s21::MainWindow::edgesTypeChange(int index) {
  if (index == 0) {
    ui_->OGLWidget->setEdgesType(0);
    ui_->OGLWidget->setEdgesSize(ui_->scrollBar_edges->value());
  } else if (index == 1) {
    ui_->OGLWidget->setEdgesType(1);
    ui_->OGLWidget->setEdgesSize(ui_->scrollBar_edges->value());
  }
  ui_->OGLWidget->update();
}

void s21::MainWindow::verticesSizeChange(int value) {
  ui_->spinBox_vertices->setValue(value);
  ui_->OGLWidget->setVerticesSize(ui_->scrollBar_vertices->value());
  ui_->OGLWidget->update();
}

void s21::MainWindow::edgesSizeChange(int value) {
  ui_->spinBox_edges->setValue(value);
  ui_->OGLWidget->setEdgesSize(ui_->scrollBar_edges->value());
  ui_->OGLWidget->update();
}

void s21::MainWindow::verticesSizeChangeManually(int value) {
  ui_->scrollBar_vertices->setValue(value);
  ui_->OGLWidget->setVerticesSize(ui_->scrollBar_vertices->value());
  ui_->OGLWidget->update();
}

void s21::MainWindow::edgesSizeChangeManually(int value) {
  ui_->scrollBar_edges->setValue(value);
  ui_->OGLWidget->setEdgesSize(ui_->scrollBar_edges->value());
  ui_->OGLWidget->update();
}

void s21::MainWindow::backgroundColorChange() {
  QColorDialog dialog(this);
  QColor color = dialog.getColor(Qt::white, this, tr("Select color"));
  if (color.isValid()) {
    QString style = QString("background-color: %1").arg(color.name());
    ui_->frame_bg->setStyleSheet(style);
    ui_->OGLWidget->setBackgroundColor(color);
    ui_->OGLWidget->update();
  }
}

void s21::MainWindow::verticesColorChange() {
  QColorDialog dialog(this);
  QColor color = dialog.getColor(Qt::white, this, tr("Select color"));
  if (color.isValid()) {
    QString style = QString("background-color: %1").arg(color.name());
    ui_->frame_vertices->setStyleSheet(style);
    ui_->OGLWidget->setVerticesColor(color);
    ui_->OGLWidget->update();
  }
}

void s21::MainWindow::edgesColorChange() {
  QColorDialog dialog(this);
  QColor color = dialog.getColor(Qt::white, this, tr("Select color"));
  if (color.isValid()) {
    QString style = QString("background-color: %1").arg(color.name());
    ui_->frame_edges->setStyleSheet(style);
    ui_->OGLWidget->setEdgesColor(color);
    ui_->OGLWidget->update();
  }
}

s21::Memento *s21::MainWindow::saveMemento() {
  return controller_->saveMemento(
      ui_->label_path_info->text().toStdString().substr(
          ui_->label_path_info->text().toStdString().find(':') + 2),
      ui_->radioButton_perspective->isChecked(),
      std::tuple<int, int>(ui_->comboBox_vertices->currentIndex(),
                           ui_->spinBox_vertices->value()),
      std::tuple<bool, int>(ui_->comboBox_edges->currentIndex(),
                            ui_->spinBox_edges->value()),
      std::tuple<std::string, std::string, std::string>(
          ui_->frame_bg->palette().color(QPalette::Window).name().toStdString(),
          ui_->frame_vertices->palette()
              .color(QPalette::Window)
              .name()
              .toStdString(),
          ui_->frame_edges->palette()
              .color(QPalette::Window)
              .name()
              .toStdString()));
}

void s21::MainWindow::reinstateMemento(int mementoNumber) {
  Memento *mem = controller_->reinstateMemento(mementoNumber);
  if (mem) {
    if (ui_->label_name_info->text().compare("Name: empty")) {
      historyHandler(saveMemento());
    }
    if (!controller_->newObject(mem->fileName_)) {
      QMessageBox::critical(this, "Error", "Unable open the file",
                            QMessageBox::Button::Ok);
    } else {
      ui_->pushButton_save->setEnabled(1);
      ui_->pushButton_record->setEnabled(1);
    }
    defaultSettings();
    if (mem->projection_) {
      projectionPerspective();
    }
    verticesTypeChange(std::get<0>(mem->verticesSettings_));
    verticesSizeChange(std::get<1>(mem->verticesSettings_));
    edgesTypeChange(std::get<0>(mem->edgesSettings_));
    edgesSizeChange(std::get<1>(mem->edgesSettings_));
    setFrame(QString("background-color: %1")
                 .arg(QString::fromStdString(std::get<0>(mem->colorPalette_))),
             QString("background-color: %1")
                 .arg(QString::fromStdString(std::get<1>(mem->colorPalette_))),
             QString("background-color: %1")
                 .arg(QString::fromStdString(std::get<2>(mem->colorPalette_))));
    setColor(QString::fromStdString(std::get<0>(mem->colorPalette_)),
             QString::fromStdString(std::get<1>(mem->colorPalette_)),
             QString::fromStdString(std::get<2>(mem->colorPalette_)));
    setWindowTitle(QString::fromStdString(mem->fileName_));
    setLabel(QString::fromStdString(mem->fileName_),
             QFileInfo(QString::fromStdString(mem->fileName_)).fileName(),
             QString::number(controller_->getVertexesSize() / 3),
             QString::number(controller_->getFacetsSize()));
    ui_->OGLWidget->update();
  }
}

void s21::MainWindow::setLabel(QString fileName, QString name,
                               QString verticesSize, QString facetsSize) {
  ui_->label_path_info->setText("Full path: " + fileName);
  ui_->label_name_info->setText("Name: " + name);
  ui_->label_vertices_info->setText("Vertices: " + verticesSize);
  ui_->label_edges_info->setText("Edges: " + facetsSize);
}

void s21::MainWindow::setFrame(QString bg, QString vertices, QString edges) {
  ui_->frame_bg->setStyleSheet(bg);
  ui_->frame_vertices->setStyleSheet(vertices);
  ui_->frame_edges->setStyleSheet(edges);
}

void s21::MainWindow::setColor(QString bg, QString vertices, QString edges) {
  ui_->OGLWidget->setBackgroundColor(bg);
  ui_->OGLWidget->setVerticesColor(vertices);
  ui_->OGLWidget->setEdgesColor(edges);
}

void s21::MainWindow::closeEvent(QCloseEvent *event) {
  if (ui_->label_name_info->text().compare("Name: empty")) {
    historyHandler(saveMemento());
  }
  controller_->saveConfig();
  event->accept();
}

void s21::MainWindow::saveImage() {
  QString format = ui_->formatBox->currentText();
  QImage image = ui_->OGLWidget->grabFramebuffer();
  QString filePath = "../../../../Images/screenshot" +
                     QString::number(controller_->getScreenNumb()) + format;
  QString fm;
  if (format == ".jpeg") {
    fm = "JPG";
  } else {
    fm = "BMP";
  }
  if (!image.save(filePath, fm.toStdString().data(), 80)) {
    QMessageBox::critical(this, "Screenshot", "Not enough memory",
                          QMessageBox::Button::Ok);
  } else {
    QMessageBox::information(this, "Screenshot", "Screenshot saved",
                             QMessageBox::Button::Ok);
    controller_->incScreenNumb();
  }
}

void s21::MainWindow::recordGif() {
  timer.start(100);
  ui_->pushButton_record->setEnabled(0);
}

void s21::MainWindow::timerAction() {
  if (giftime < 50) {
    gifImage[giftime] = ui_->OGLWidget->grab().toImage();
    giftime++;
  } else {
    gif = new (std::nothrow) QGifImage;
    if (gif) {
      for (int i = 0; i < giftime; i++) {
        gif->addFrame(gifImage[i], 0);
      }
      if (!gif->save("../../../../Images/animation" +
                     QString::number(controller_->getScreenNumb()) + ".gif")) {
        QMessageBox::critical(this, "GIF", "Not enough memory",
                              QMessageBox::Button::Ok);
      } else {
        QMessageBox::information(this, "GIF", "GIF saved",
                                 QMessageBox::Button::Ok);
      }
    }
    timer.stop();
    ui_->pushButton_record->setEnabled(1);
    delete gif;
    giftime = 0;
  }
}
