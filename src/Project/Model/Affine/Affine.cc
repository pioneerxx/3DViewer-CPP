#include "Affine.h"

void s21::Affine::move(Figure& figure, double value, coordinates coordinate) {
  for (int i = coordinate; i < figure.getVertexesSize(); i += 3) {
    figure.setVertex(i, figure.getVertexesValue(i) + value);
  }
}

void s21::Affine::rotation(Figure& figure, double new_angle, double old_angle,
                           coordinates coordinate) {
  double temp_x(0.0);
  double temp_y(0.0);
  double temp_z(0.0);

  static const double radians(M_PI / 180.0);
  new_angle *= radians;
  old_angle *= radians;

  for (int i = 0; i < figure.getVertexesSize(); i += 3) {
    if (coordinate == kX) {
      temp_y = figure.getVertexesValue(i + 1);
      temp_z = figure.getVertexesValue(i + 2);
      figure.setVertex(i + 1, cos(new_angle - old_angle) * temp_y +
                                  sin(new_angle - old_angle) * temp_z);
      figure.setVertex(i + 2, -sin(new_angle - old_angle) * temp_y +
                                  cos(new_angle - old_angle) * temp_z);
    } else if (coordinate == kY) {
      temp_x = figure.getVertexesValue(i);
      temp_z = figure.getVertexesValue(i + 2);
      figure.setVertex(i, cos(new_angle - old_angle) * temp_x -
                              sin(new_angle - old_angle) * temp_z);
      figure.setVertex(i + 2, sin(new_angle - old_angle) * temp_x +
                                  cos(new_angle - old_angle) * temp_z);
    } else if (coordinate == kZ) {
      temp_x = figure.getVertexesValue(i);
      temp_y = figure.getVertexesValue(i + 1);
      figure.setVertex(i, cos(new_angle - old_angle) * temp_x +
                              sin(new_angle - old_angle) * temp_y);
      figure.setVertex(i + 1, -sin(new_angle - old_angle) * temp_x +
                                  cos(new_angle - old_angle) * temp_y);
    }
  }
}

void s21::Affine::scale(Figure& figure, double value, coordinates coordinate) {
  static const double eps = 0.001;
  if (value > eps) {
    for (int i = coordinate; i < figure.getVertexesSize(); i += 3) {
      figure.setVertex(i, figure.getVertexesValue(i) * value);
    }
  }
}
