#include "SingletonView.h"

s21::MainWindow* s21::SingletonView::instance = nullptr;

s21::MainWindow* s21::SingletonView::getInstance(Controller* controller) {
  if (instance == nullptr) {
    instance = new MainWindow(controller);
  }
  return instance;
}

s21::SingletonView::~SingletonView() { delete instance; }