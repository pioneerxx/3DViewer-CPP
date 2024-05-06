#ifndef SRC_PROJECT_MODEL_PARSER_PARSER_H_
#define SRC_PROJECT_MODEL_PARSER_PARSER_H_

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "../Figure/Figure.h"

namespace s21 {

class Parser {
 public:
  Parser() {}
  bool parse(Figure& figure, const std::string& fileName);

 private:
  void parseVertexes(Figure& figure, const std::string& line);
  void parseFacets(Figure& figure, const std::string& line);
  void parsePolygons(Figure& figure);
  double maxCoordinate(Figure& figure, int k);
  double compareMax(double a, double b);
};

}  // namespace s21

#endif  // SRC_PROJECT_MODEL_PARSER_PARSER_H_
