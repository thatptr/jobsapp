#pragma once

#include <string>
#include <memory>
#include "../lib/toml.cpp"

class jobs_org {
private:
  std::string name;
  std::string org_dir;
  
public:
  jobs_org(const std::string &organization_name,
       const std::string &organization_directory) {
    this->name = organization_name;
    this->org_dir = organization_directory;
  }
};
