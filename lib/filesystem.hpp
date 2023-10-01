// Filesystem management
#pragma once

#include <fstream>
#include <ios>
#include <iostream>
#include <optional>
#include <string>

namespace jobs {
enum permissions {
  read,
  write,
  all,
};

struct file {
  std::string filename;
  enum permissions permisson;

  file(const std::string &filename, const enum permissions &permissions) {
    this->filename = filename;
    this->permisson = permissions;
  }

  const bool create_file(const std::optional<std::string> &text) {
    if (this->permisson == permissions::read)
      return 1;

    std::ofstream file;
    file.open(this->filename);

    if (text.has_value())
      file << text.value().c_str() << std::endl;

    file.close();

    return false;
  }

  enum file_operation_type {
    overwrite,
    append,
  };

  const bool add_to_file(const std::string &text, const bool &overwrite) {
    std::ofstream file;

    if (this->permisson == permissions::read)
      return false;

    if (!overwrite) {
      file.open(this->filename, std::ios_base::app);
      file << text << std::endl;
      return true;
    }

    file.open(this->filename, std::ios_base::app);
    file << text << std::endl;
    return true;
  }
};
} // namespace jobs::file
