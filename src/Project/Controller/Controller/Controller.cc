#include "Controller.h"

s21::Controller::Controller(Facade* facade) { facade_ = facade; }

bool s21::Controller::newObject(const std::string& fileName) {
  try {
    return facade_->newObject(fileName);
  } catch (const std::invalid_argument& ia) {
  }
}

void s21::Controller::restoreDefault() { facade_->restoreDefault(); }

void s21::Controller::moveX(double value) { facade_->moveX(value); }

void s21::Controller::moveY(double value) { facade_->moveY(value); }

void s21::Controller::moveZ(double value) { facade_->moveZ(value); }

void s21::Controller::rotationX(double new_angle, double old_angle) {
  facade_->rotationX(new_angle, old_angle);
}

void s21::Controller::rotationY(double new_angle, double old_angle) {
  facade_->rotationY(new_angle, old_angle);
}

void s21::Controller::rotationZ(double new_angle, double old_angle) {
  facade_->rotationZ(new_angle, old_angle);
}

void s21::Controller::scaleX(double value) { facade_->scaleX(value); }

void s21::Controller::scaleY(double value) { facade_->scaleY(value); }

void s21::Controller::scaleZ(double value) { facade_->scaleZ(value); }

int s21::Controller::getVertexesSize() { return facade_->getVertexesSize(); }

int s21::Controller::getFacetsSize() { return facade_->getFacetsSize(); }

int s21::Controller::getPolygonsSize() { return facade_->getPolygonsSize(); }

std::vector<double> s21::Controller::getVertexes() {
  return facade_->getVertexes();
}

std::vector<std::vector<unsigned> > s21::Controller::getFacets() {
  return facade_->getFacets();
}

std::vector<unsigned> s21::Controller::getPolygons() {
  return facade_->getPolygons();
}

double s21::Controller::getMaxC() { return facade_->getMaxC(); }

void s21::Controller::clearFigure() { facade_->clearFigure(); }

s21::Memento* s21::Controller::saveMemento(
    std::string fileName, bool projection,
    std::tuple<int, int> verticesSettings, std::tuple<bool, int> edgesSettings,
    std::tuple<std::string, std::string, std::string> colorPalette) {
  return facade_->saveMemento(fileName, projection, verticesSettings,
                              edgesSettings, colorPalette);
}

s21::Memento* s21::Controller::reinstateMemento(int mementoNumber) {
  return facade_->reinstateMemento(mementoNumber);
}

void s21::Controller::saveConfig() { facade_->saveConfig(); }

std::list<s21::Memento*>* s21::Controller::restoreConfig() {
  return facade_->restoreConfig();
}

bool s21::Controller::checkConfig() { return facade_->checkConfig(); }

int s21::Controller::getScreenNumb() { return facade_->getScreenNumb(); }
void s21::Controller::incScreenNumb() { facade_->incScreenNumb(); }
