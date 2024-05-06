#include "SingletonModel.h"

s21::Facade* s21::SingletonModel::instance = nullptr;

s21::Facade* s21::SingletonModel::getInstance() {
  if (instance == nullptr) {
    instance = new Facade();
  }
  return instance;
}

s21::SingletonModel::~SingletonModel() { delete instance; }
