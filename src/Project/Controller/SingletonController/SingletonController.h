#ifndef SRC_CONTROLLER_SINGLETONCONTROLLER_SINGLETONCONTROLLER_H
#define SRC_CONTROLLER_SINGLETONCONTROLLER_SINGLETONCONTROLLER_H

#include "../Controller/Controller.h"

namespace s21 {

class SingletonController {
 public:
  static Controller* getInstance(Facade* facade);

 private:
  static Controller* instance;
  SingletonController() {}
  ~SingletonController();
};

}  // namespace s21

#endif  // SRC_CONTROLLER_SINGLETONCONTROLLER_SINGLETONCONTROLLER_H
