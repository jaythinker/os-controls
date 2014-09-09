#include "stdafx.h"
#include "Config.h"

#include "autowiring/../contrib/json11/json11.hpp"
#include <fstream>
#include <sstream>

Config::Config(void) {
}

void Config::Save(const std::string& filename) const {
  std::ofstream outFile(filename);
  outFile << json11::Json(m_data).dump();;
}

void Config::Load(const std::string& filename) {
  std::string err;
  std::stringstream data;

  {
    std::ifstream inFile(filename);
    data << inFile.rdbuf();
  }
  
  m_data = json11::Json::parse(data.str(), err).object_items();
  if (!err.empty())
    throw std::runtime_error(std::string("Json parsing error:") + err);
}

std::chrono::microseconds Config::GetFrameRate() const {
  return std::chrono::microseconds(static_cast<long>(Get<double>("framerate")));
}