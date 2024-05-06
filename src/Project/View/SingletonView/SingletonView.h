#ifndef SRC_VIEW_SINGLETONVIEW_SINGLETONVIEW_H
#define SRC_VIEW_SINGLETONVIEW_SINGLETONVIEW_H

#include "../MainWindow/mainwindow.h"

namespace s21 {

class SingletonView {
 public:
  static MainWindow* getInstance(Controller* controller);

 private:
  static MainWindow* instance;
  SingletonView() {}
  ~SingletonView();
};

}  // namespace s21

#endif  // SRC_VIEW_SINGLETONVIEW_SINGLETONVIEW_H
