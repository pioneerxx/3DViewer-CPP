#include <QApplication>

#include "Controller/SingletonController/SingletonController.h"
#include "Model/SingletonModel/SingletonModel.h"
#include "View/SingletonView/SingletonView.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::SingletonView::getInstance(
      s21::SingletonController::getInstance(s21::SingletonModel::getInstance()))
      ->show();
  return a.exec();
}
