#include <gtest/gtest.h>

#include "../Project/Model/Facade/Facade.h"

static const double radians = M_PI / 180.0;

TEST(Viewer, test_pars1) {
  s21::Facade facade;
  facade.newObject("Objects/cube.obj");

  EXPECT_EQ(facade.getVertexesSize() / 3, 8);
  EXPECT_EQ(facade.getFacetsSize(), 12);
  EXPECT_EQ(facade.getPolygonsSize(), 72);

  std::vector<double> expected_vert = {
      -0.500000, -0.500000, 0.500000,  0.500000, -0.500000, 0.500000,
      -0.500000, 0.500000,  0.500000,  0.500000, 0.500000,  0.500000,
      -0.500000, 0.500000,  -0.500000, 0.500000, 0.500000,  -0.500000,
      -0.500000, -0.500000, -0.500000, 0.500000, -0.500000, -0.500000};
  EXPECT_EQ(expected_vert, facade.getVertexes());

  std::vector<unsigned> expected_poly = {
      0, 1, 0, 2, 1, 2, 2, 1, 2, 3, 1, 3, 2, 3, 2, 4, 3, 4, 4, 3, 4, 5, 3, 5,
      4, 5, 4, 6, 5, 6, 6, 5, 6, 7, 5, 7, 6, 7, 6, 0, 7, 0, 0, 7, 0, 1, 7, 1,
      1, 7, 1, 3, 7, 3, 3, 7, 3, 5, 7, 5, 6, 0, 6, 4, 0, 4, 4, 0, 4, 2, 0, 2};
  EXPECT_EQ(expected_poly, facade.getPolygons());
}

TEST(Viewer, test_affine1) {
  s21::Facade facade1;
  facade1.newObject("Objects/cube.obj");
  s21::Facade facade2;
  facade2.newObject("Objects/cube.obj");

  facade2.moveX(5);

  EXPECT_EQ(facade1.getVertexesSize(), facade2.getVertexesSize());
  EXPECT_EQ(facade1.getFacetsSize(), facade2.getFacetsSize());
  EXPECT_EQ(facade1.getPolygonsSize(), facade2.getPolygonsSize());

  std::vector<double> expected = facade1.getVertexes();
  for (int i = 0; i < (int)expected.size(); i += 3) expected.at(i) += 5;
  EXPECT_EQ(expected, facade2.getVertexes());
}

TEST(Viewer, test_affine2) {
  s21::Facade facade1;
  facade1.newObject("Objects/cube.obj");
  s21::Facade facade2;
  facade2.newObject("Objects/cube.obj");

  facade2.moveY(-0.75);

  EXPECT_EQ(facade1.getVertexesSize(), facade2.getVertexesSize());
  EXPECT_EQ(facade1.getFacetsSize(), facade2.getFacetsSize());
  EXPECT_EQ(facade1.getPolygonsSize(), facade2.getPolygonsSize());

  std::vector<double> expected = facade1.getVertexes();
  for (int i = 1; i < (int)expected.size(); i += 3) expected.at(i) -= 0.75;
  EXPECT_EQ(expected, facade2.getVertexes());
}

TEST(Viewer, test_affine3) {
  s21::Facade facade1;
  facade1.newObject("Objects/cube.obj");
  s21::Facade facade2;
  facade2.newObject("Objects/cube.obj");

  facade2.moveZ(0.33);

  EXPECT_EQ(facade1.getVertexesSize(), facade2.getVertexesSize());
  EXPECT_EQ(facade1.getFacetsSize(), facade2.getFacetsSize());
  EXPECT_EQ(facade1.getPolygonsSize(), facade2.getPolygonsSize());

  std::vector<double> expected = facade1.getVertexes();
  for (int i = 2; i < (int)expected.size(); i += 3) expected.at(i) += 0.33;
  EXPECT_EQ(expected, facade2.getVertexes());
}

TEST(Viewer, test_affine4) {
  s21::Facade facade1;
  facade1.newObject("Objects/cube.obj");
  s21::Facade facade2;
  facade2.newObject("Objects/cube.obj");

  facade2.rotationX(75, 60);
  double angle = 15 * radians;

  EXPECT_EQ(facade1.getVertexesSize(), facade2.getVertexesSize());
  EXPECT_EQ(facade1.getFacetsSize(), facade2.getFacetsSize());
  EXPECT_EQ(facade1.getPolygonsSize(), facade2.getPolygonsSize());

  std::vector<double> expected = facade1.getVertexes();
  for (int i = 0; i < (int)expected.size(); i += 3) {
    double temp_y = expected.at(i + 1);
    double temp_z = expected.at(i + 2);
    expected.at(i + 1) = cos(angle) * temp_y + sin(angle) * temp_z;
    expected.at(i + 2) = -sin(angle) * temp_y + cos(angle) * temp_z;
  }
  std::vector<double> actual = facade2.getVertexes();

  for (int i = 0; i < facade1.getVertexesSize(); ++i)
    EXPECT_DOUBLE_EQ(expected.at(i), actual.at(i));
}

TEST(Viewer, test_affine5) {
  s21::Facade facade1;
  facade1.newObject("Objects/cube.obj");
  s21::Facade facade2;
  facade2.newObject("Objects/cube.obj");

  facade2.rotationY(60, 0);
  double angle = 60 * radians;

  EXPECT_EQ(facade1.getVertexesSize(), facade2.getVertexesSize());
  EXPECT_EQ(facade1.getFacetsSize(), facade2.getFacetsSize());
  EXPECT_EQ(facade1.getPolygonsSize(), facade2.getPolygonsSize());

  std::vector<double> expected = facade1.getVertexes();
  for (int i = 0; i < (int)expected.size(); i += 3) {
    double temp_x = expected.at(i);
    double temp_z = expected.at(i + 2);
    expected.at(i) = cos(angle) * temp_x - sin(angle) * temp_z;
    expected.at(i + 2) = sin(angle) * temp_x + cos(angle) * temp_z;
  }
  std::vector<double> actual = facade2.getVertexes();

  for (int i = 0; i < facade1.getVertexesSize(); ++i)
    EXPECT_DOUBLE_EQ(expected.at(i), actual.at(i));
}

TEST(Viewer, test_affine6) {
  s21::Facade facade1;
  facade1.newObject("Objects/cube.obj");
  s21::Facade facade2;
  facade2.newObject("Objects/cube.obj");

  facade2.rotationZ(94, 30);
  double angle = 64 * radians;

  EXPECT_EQ(facade1.getVertexesSize(), facade2.getVertexesSize());
  EXPECT_EQ(facade1.getFacetsSize(), facade2.getFacetsSize());
  EXPECT_EQ(facade1.getPolygonsSize(), facade2.getPolygonsSize());

  std::vector<double> expected = facade1.getVertexes();
  for (int i = 0; i < (int)expected.size(); i += 3) {
    double temp_x = expected.at(i);
    double temp_y = expected.at(i + 1);
    expected.at(i) = cos(angle) * temp_x + sin(angle) * temp_y;
    expected.at(i + 1) = -sin(angle) * temp_x + cos(angle) * temp_y;
  }
  std::vector<double> actual = facade2.getVertexes();

  for (int i = 0; i < facade1.getVertexesSize(); ++i)
    EXPECT_DOUBLE_EQ(expected.at(i), actual.at(i));
}

TEST(Viewer, test_affine7) {
  s21::Facade facade1;
  facade1.newObject("Objects/cube.obj");
  s21::Facade facade2;
  facade2.newObject("Objects/cube.obj");

  facade2.scaleX(0.5);

  EXPECT_EQ(facade1.getVertexesSize(), facade2.getVertexesSize());
  EXPECT_EQ(facade1.getFacetsSize(), facade2.getFacetsSize());
  EXPECT_EQ(facade1.getPolygonsSize(), facade2.getPolygonsSize());

  std::vector<double> expected = facade1.getVertexes();
  for (int i = 0; i < (int)expected.size(); i += 3) expected.at(i) *= 0.5;
  EXPECT_EQ(expected, facade2.getVertexes());
}

TEST(Viewer, test_affine8) {
  s21::Facade facade1;
  facade1.newObject("Objects/cube.obj");
  s21::Facade facade2;
  facade2.newObject("Objects/cube.obj");

  facade2.scaleY(5);

  EXPECT_EQ(facade1.getVertexesSize(), facade2.getVertexesSize());
  EXPECT_EQ(facade1.getFacetsSize(), facade2.getFacetsSize());
  EXPECT_EQ(facade1.getPolygonsSize(), facade2.getPolygonsSize());

  std::vector<double> expected = facade1.getVertexes();
  for (int i = 1; i < (int)expected.size(); i += 3) expected.at(i) *= 5;
  EXPECT_EQ(expected, facade2.getVertexes());
}

TEST(Viewer, test_affine9) {
  s21::Facade facade1;
  facade1.newObject("Objects/cube.obj");
  s21::Facade facade2;
  facade2.newObject("Objects/cube.obj");

  facade2.scaleZ(1.25);

  EXPECT_EQ(facade1.getVertexesSize(), facade2.getVertexesSize());
  EXPECT_EQ(facade1.getFacetsSize(), facade2.getFacetsSize());
  EXPECT_EQ(facade1.getPolygonsSize(), facade2.getPolygonsSize());

  std::vector<double> expected = facade1.getVertexes();
  for (int i = 2; i < (int)expected.size(); i += 3) expected.at(i) *= 1.25;
  EXPECT_EQ(expected, facade2.getVertexes());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
