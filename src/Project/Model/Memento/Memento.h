#ifndef SRC_PROJECT_MODEL_MEMENTO_MEMENTO_H_
#define SRC_PROJECT_MODEL_MEMENTO_MEMENTO_H_

#include <tuple>

#include "../Figure/Figure.h"

namespace s21 {

class Memento {
 public:
  Memento() {}
  Memento(std::string fileName, bool projection,
          std::tuple<int, int> verticesSettings,
          std::tuple<bool, int> edgesSettings,
          std::tuple<std::string, std::string, std::string> colorPalette);
  friend class Model;
  std::string fileName_;
  bool projection_;
  std::tuple<int, int> verticesSettings_;
  std::tuple<bool, int> edgesSettings_;
  std::tuple<std::string, std::string, std::string> colorPalette_;
};

}  // namespace s21

#endif  // SRC_PROJECT_MODEL_MEMENTO_MEMENTO_H
