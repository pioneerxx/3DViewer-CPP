#ifndef SRC_PROJECT_MODEL_FACADE_H_
#define SRC_PROJECT_MODEL_FACADE_H_

#include <list>
#include <string>

#include "../Affine/Affine.h"
#include "../Figure/Figure.h"
#include "../Memento/Memento.h"
#include "../Parser/Parser.h"

namespace s21 {

class Facade {
 public:
  Facade() {}
  ~Facade();
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
  double getMaxC();
  std::vector<double> getVertexes();
  std::vector<std::vector<unsigned> > getFacets();
  std::vector<unsigned> getPolygons();
  int getScreenNumb();
  void incScreenNumb();

  void clearFigure();
  Memento* saveMemento(
      std::string fileName, bool projection,
      std::tuple<int, int> vertiesSettings, std::tuple<bool, int> edgesSettings,
      std::tuple<std::string, std::string, std::string> colorPalette);
  Memento* reinstateMemento(int mementoNumber);
  void saveConfig();
  std::list<Memento*>* restoreConfig();
  bool checkConfig();

 private:
  Figure figure_;
  Figure figureCopy_;
  Affine affine_;
  Parser parser_;
  std::list<Memento*> history_;
  int screenNumb_ = 0;
};

}  // namespace s21

#endif  // SRC_PROJECT_MODEL_FACADE_H_
