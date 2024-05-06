#include "Facade.h"

s21::Memento* s21::Facade::saveMemento(
    std::string fileName, bool projection,
    std::tuple<int, int> verticesSettings, std::tuple<bool, int> edgesSettings,
    std::tuple<std::string, std::string, std::string> colorPalette) {
  Memento* tmp = new (std::nothrow) Memento(
      fileName, projection, verticesSettings, edgesSettings, colorPalette);
  Memento* res = nullptr;
  if (!tmp) {
    return res;
  }
  res = tmp;
  history_.push_front(tmp);
  if (history_.size() > 6) {
    tmp = history_.back();
    history_.pop_back();
    delete tmp;
  }
  return res;
}

void s21::Facade::saveConfig() {
  std::ofstream myfile("../../../../Settings/settings.config");
  char projection = '0';
  if (myfile.is_open()) {
    myfile << std::to_string(screenNumb_) + '\n';
    for (std::list<Memento*>::reverse_iterator it = history_.rbegin();
         it != history_.rend(); it++) {
      projection = (*it)->projection_ ? '1' : '0';
      myfile << (*it)->fileName_ + ' ' + projection + ' ' +
                    std::to_string(std::get<0>((*it)->verticesSettings_)) +
                    ' ' +
                    std::to_string(std::get<1>((*it)->verticesSettings_)) +
                    ' ' + std::to_string(std::get<0>((*it)->edgesSettings_)) +
                    ' ' + std::to_string(std::get<1>((*it)->edgesSettings_)) +
                    ' ' + std::get<0>((*it)->colorPalette_) + ' ' +
                    std::get<1>((*it)->colorPalette_) + ' ' +
                    std::get<2>((*it)->colorPalette_) + '\n';
    }
    myfile.close();
  }
}

std::list<s21::Memento*>* s21::Facade::restoreConfig() {
  std::ifstream myfile("../../../../Settings/settings.config");
  std::string line;
  std::istringstream iss;
  std::string fileName, color1, color2, color3;
  bool Projection, edgesType;
  int screenNumb = 0;
  int verticesType, verticesSize, edgesSize;
  if (myfile.is_open()) {
    std::getline(myfile, line);
    iss = std::istringstream(line);
    if (iss >> screenNumb) {
      screenNumb_ = screenNumb;
    }
    while (std::getline(myfile, line)) {
      iss = std::istringstream(line);
      if (iss >> fileName >> Projection >> verticesType >> verticesSize >>
          edgesType >> edgesSize >> color1 >> color2 >> color3) {
        saveMemento(fileName, Projection,
                    std::tuple<int, int>(verticesType, verticesSize),
                    std::tuple<bool, int>(edgesType, edgesSize),
                    std::tuple<std::string, std::string, std::string>(
                        color1, color2, color3));
      }
    }
    myfile.close();
  }
  return &history_;
}

bool s21::Facade::checkConfig() {
  bool res = false;
  std::ifstream myfile;
  char c = 0;
  int n = 0;
  myfile.open("../../../../Settings/settings.config");
  if (myfile.is_open()) {
    while (myfile.get(c)) {
      n++;
    }
    myfile.close();
  }
  if (n > 0) {
    res = true;
  }
  return res;
}

s21::Facade::~Facade() {
  for (auto i : history_) {
    delete i;
  }
}

void s21::Facade::restoreDefault() { figure_ = figureCopy_; }

s21::Memento* s21::Facade::reinstateMemento(int mementoNumber) {
  std::list<Memento*>::iterator it = std::next(history_.begin(), mementoNumber);
  return *it;
}

bool s21::Facade::newObject(const std::string& fileName) {
  bool res = parser_.parse(figure_, fileName);
  if (res) {
    figureCopy_ = figure_;
  }
  return res;
}

void s21::Facade::moveX(double value) { affine_.move(figure_, value, kX); }

void s21::Facade::moveY(double value) { affine_.move(figure_, value, kY); }

void s21::Facade::moveZ(double value) { affine_.move(figure_, value, kZ); }

void s21::Facade::rotationX(double new_angle, double old_angle) {
  affine_.rotation(figure_, new_angle, old_angle, kX);
}

void s21::Facade::rotationY(double new_angle, double old_angle) {
  affine_.rotation(figure_, new_angle, old_angle, kY);
}

void s21::Facade::rotationZ(double new_angle, double old_angle) {
  affine_.rotation(figure_, new_angle, old_angle, kZ);
}

void s21::Facade::scaleX(double value) { affine_.scale(figure_, value, kX); }

void s21::Facade::scaleY(double value) { affine_.scale(figure_, value, kY); }

void s21::Facade::scaleZ(double value) { affine_.scale(figure_, value, kZ); }

int s21::Facade::getVertexesSize() { return figure_.getVertexesSize(); }
int s21::Facade::getFacetsSize() { return figure_.getFacetsSize(); }
int s21::Facade::getPolygonsSize() { return figure_.getPolygonsSize(); }
std::vector<double> s21::Facade::getVertexes() { return figure_.getVertexes(); }
std::vector<std::vector<unsigned> > s21::Facade::getFacets() {
  return figure_.getFacets();
}
std::vector<unsigned> s21::Facade::getPolygons() {
  return figure_.getPolygons();
}

double s21::Facade::getMaxC() { return figure_.getMaxC(); }

void s21::Facade::clearFigure() { figure_.clearFigure(); }

int s21::Facade::getScreenNumb() { return screenNumb_; }

void s21::Facade::incScreenNumb() { screenNumb_++; }
