#include "Parser.h"

bool s21::Parser::parse(Figure &figure, const std::string &fileName) {
  bool res = 0;
  figure.clearFigure();
  std::ifstream file(fileName);
  if (file.is_open()) {
    res = 1;
    if (fileName.length() <= 4 ||
        fileName.substr(fileName.length() - 4) != ".obj") {
      throw std::runtime_error("File is not object file");
    }
    if (!file.is_open()) {
      throw std::runtime_error("Failed to open file");
    }
    std::string line;
    while (std::getline(file, line)) {
      if (line.substr(0, 2) == "v ") {
        parseVertexes(figure, line);
      } else if (line.substr(0, 2) == "f ") {
        parseFacets(figure, line);
      }
    }
    parsePolygons(figure);
    figure.setMaxC(compareMax(
        maxCoordinate(figure, 0),
        compareMax(maxCoordinate(figure, 1), maxCoordinate(figure, 2))));
  }
  return res;
}

void s21::Parser::parseVertexes(Figure &figure, const std::string &line) {
  std::stringstream ss(line.substr(2));
  std::string token;
  while (ss >> token) {
    figure.addVertex(std::stod(token));
  }
}

void s21::Parser::parseFacets(Figure &figure, const std::string &line) {
  std::stringstream ss(line.substr(2));
  std::string token;
  std::vector<unsigned> polygon;
  while (ss >> token) {
    size_t slashPos = token.find('/');
    if (slashPos != std::string::npos) {
      polygon.push_back(std::stoul(token.substr(0, slashPos)));
    } else {
      polygon.push_back(std::stoul(token));
    }
  }
  figure.addFacet(polygon);
}

void s21::Parser::parsePolygons(Figure &figure) {
  for (int k = 0; k < figure.getFacetsSize(); k++) {
    for (int i = 0; i < figure.getFacetsSizeAt(k) - 1; i++) {
      for (int j = i + 1; j < figure.getFacetsSizeAt(k); j++) {
        figure.addPolygon(figure.getFacetsValue(k, i) - 1);
        figure.addPolygon(figure.getFacetsValue(k, j) - 1);
      }
    }
  }
}

double s21::Parser::maxCoordinate(Figure &figure, int k) {
  if (figure.getVertexesSize() == 0) {
    return 0;
  }
  double max = figure.getVertexes()[0];
  for (int i = 0; i < (figure.getVertexesSize() / 3); i++) {
    if (figure.getVertexesValue(i * 3 + k) > max) {
      max = figure.getVertexesValue(i * 3 + k);
    }
  }
  return max;
}

double s21::Parser::compareMax(double a, double b) { return ((a > b) ? a : b); }
