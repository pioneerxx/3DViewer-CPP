#include "Figure.h"

int s21::Figure::getVertexesSize() { return vertexes_.size(); }

int s21::Figure::getFacetsSize() { return facets_.size(); }

int s21::Figure::getFacetsSizeAt(int k) { return facets_.at(k).size(); }

int s21::Figure::getPolygonsSize() { return polygons_.size(); }

double s21::Figure::getVertexesValue(size_t index) {
  return vertexes_.at(index);
}

unsigned s21::Figure::getFacetsValue(size_t index, size_t jndex) {
  return facets_.at(index).at(jndex);
}

std::vector<double> s21::Figure::getVertexes() { return vertexes_; }
std::vector<std::vector<unsigned> > s21::Figure::getFacets() { return facets_; }
std::vector<unsigned> s21::Figure::getPolygons() { return polygons_; }

void s21::Figure::addVertex(double value) { vertexes_.push_back(value); }

void s21::Figure::addFacet(std::vector<unsigned>& facet) {
  facets_.push_back(facet);
}

void s21::Figure::addPolygon(unsigned value) { polygons_.push_back(value); }

double s21::Figure::getMaxC() { return maxC_; }

void s21::Figure::setVertex(size_t index, double value) {
  vertexes_.at(index) = value;
}

void s21::Figure::setMaxC(double value) { maxC_ = value; }

void s21::Figure::clearFigure() {
  vertexes_.clear();
  for (int i = 0; i < getFacetsSize(); ++i) {
    facets_.at(i).clear();
  };
  facets_.clear();
  polygons_.clear();
}
