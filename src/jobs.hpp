#pragma once

#include <string>
class jobs {
private:
  std::string name;
  std::string org_dir;

public:
  jobs(const std::string &organization_name,
       const std::string &organization_directory) {
    this->name = organization_name;
    this->org_dir = organization_directory;
  }
};
