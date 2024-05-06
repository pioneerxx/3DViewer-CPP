#ifndef SRC_PROJECT_MODEL_SINGLETONMODEL_SINGLETONMODEL_H
#define SRC_PROJECT_MODEL_SINGLETONMODEL_SINGLETONMODEL_H

#include "../Facade/Facade.h"

namespace s21 {

class SingletonModel {
 public:
  static Facade* getInstance();

 private:
  static Facade* instance;
  SingletonModel() {}
  ~SingletonModel();
};

}  // namespace s21

#endif  // SRC_PROJECT_MODEL_SINGLETONMODEL_SINGLETONMODEL_H
