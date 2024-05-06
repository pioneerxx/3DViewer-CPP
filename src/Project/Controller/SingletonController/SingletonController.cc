#include "SingletonController.h"

s21::Controller* s21::SingletonController::instance = nullptr;

s21::Controller* s21::SingletonController::getInstance(Facade* facade) {
  if (instance == nullptr) {
    instance = new Controller(facade);
  }
  return instance;
};

s21::SingletonController::~SingletonController() { delete instance; }