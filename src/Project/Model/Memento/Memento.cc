#include "Memento.h"

s21::Memento::Memento(
    std::string fileName, bool projection,
    std::tuple<int, int> verticesSettings, std::tuple<bool, int> edgesSettings,
    std::tuple<std::string, std::string, std::string> colorPalette) {
  fileName_ = fileName;
  projection_ = projection;
  verticesSettings_ = verticesSettings;
  edgesSettings_ = edgesSettings;
  colorPalette_ = colorPalette;
}
