#ifndef SRC_CONTROLLER_CONRTROLLER_H_
#define SRC_CONTROLLER_CONRTROLLER_H_

#include "../../Model/Facade/Facade.h"

namespace s21 {

class Controller {
 public:
  Controller() {}
  Controller(Facade* facade);

  bool newObject(const std::string& fileName);
  void moveX(double value);
  void moveY(double value);
  void moveZ(double value);
  void rotationX(double new_angle, double old_angle);
  void rotationY(double new_angle, double old_angle);
  void rotationZ(double new_angle, double old_angle);
  void scaleX(double value);
  void scaleY(double value);
  void scaleZ(double value);
  void restoreDefault();

  int getVertexesSize();
  int getFacetsSize();
  int getPolygonsSize();
  std::vector<double> getVertexes();
  std::vector<std::vector<unsigned> > getFacets();
  std::vector<unsigned> getPolygons();
  double getMaxC();

  void clearFigure();

  Memento* reinstateMemento(int mementoNumber);
  Memento* saveMemento(
      std::string fileName, bool projection,
      std::tuple<int, int> vertiesSettings, std::tuple<bool, int> edgesSettings,
      std::tuple<std::string, std::string, std::string> colorPalette);
  void saveConfig();
  std::list<Memento*>* restoreConfig();
  bool checkConfig();
  int getScreenNumb();
  void incScreenNumb();

 private:
  Facade* facade_;
};
}  // namespace s21

#endif  // SRC_CONTROLLER_CONRTROLLER_H_
