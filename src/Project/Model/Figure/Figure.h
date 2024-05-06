#ifndef SRC_PROJECT_MODEL_FIGURE_FIGURE_H
#define SRC_PROJECT_MODEL_FIGURE_FIGURE_H

#include <iostream>
#include <vector>

namespace s21 {

class Figure {
 public:
  Figure() {}

  int getVertexesSize();
  int getFacetsSize();
  int getFacetsSizeAt(int k);
  int getPolygonsSize();
  double getVertexesValue(size_t index);
  unsigned getFacetsValue(size_t index, size_t jndex);
  std::vector<double> getVertexes();
  std::vector<std::vector<unsigned> > getFacets();
  std::vector<unsigned> getPolygons();
  double getMaxC();
  void setVertex(size_t index, double value);
  void setMaxC(double value);
  void addVertex(double value);
  void addFacet(std::vector<unsigned>& facet);
  void addPolygon(unsigned value);

  void clearFigure();

 private:
  std::vector<double> vertexes_;
  std::vector<std::vector<unsigned> > facets_;
  std::vector<unsigned> polygons_;
  double maxC_;
};

}  // namespace s21
#endif  // SRC_PROJECT_MODEL_FIGURE_FIGURE_H
