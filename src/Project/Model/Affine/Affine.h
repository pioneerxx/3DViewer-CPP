#ifndef SRC_PROJECT_MODEL_AFFINE_AFFINE_H_
#define SRC_PROJECT_MODEL_AFFINE_AFFINE_H_

#include <cmath>

#include "../Figure/Figure.h"

namespace s21 {

enum coordinates { kX, kY, kZ };

class Affine {
 public:
  Affine() {}
  void move(Figure& figure, double value, coordinates coordinate);
  void rotation(Figure& figure, double new_angle, double old_angle,
                coordinates coordinate);
  void scale(Figure& figure, double value, coordinates coordinate);
};

}  // namespace s21

#endif  //  SRC_PROJECT_MODEL_AFFINE_AFFINE_H_
