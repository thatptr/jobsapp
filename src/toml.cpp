#pragma once

#include <memory>
#include <optional>
#include <string>

#include <sys/stat.h>
#include <toml.hpp>

#include "../lib/filesystem.hpp"
#include <toml/parser.hpp>
#include <unistd.h>

enum config_status {
  fresh,
  modified,
};

class config {
private:
  enum config_status config_status;
  std::string config_file_path;

  const bool path_exists(const std::string &path) {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
  }

  const inline bool file_exists(const std::string &name) {
    return (access(name.c_str(), F_OK) != -1);
  }

public:
  config(const std::string &home_dir,
         const std::optional<std::string> &config_file_path) {
    if (config_file_path.has_value()) {
      this->config_file_path = config_file_path.value();
    } else {
      this->config_file_path = "/home/" + home_dir + "/.config/jobsapp";
    }
  }

  void make_config_dir() {
    if (!path_exists(this->config_file_path)) {
      mkdir(this->config_file_path.c_str(), 0700);
      this->config_status = config_status::fresh;
    } else {
      this->config_status = config_status::modified;
    }
  }

  const bool populate_config() {
    if (this->config_status == config_status::modified ||
        file_exists(this->config_file_path + "config.toml")) {
      return 1;
    }

    std::unique_ptr<jobs::file> temp = std::make_unique<jobs::file>(
        this->config_file_path + "config.toml", jobs::permissions::all);

    temp->create_file("autogen = true\n");
    return 0;
  }

  const std::string get_opt(const std::string &opt) {
    auto data = toml::parse(this->config_file_path);
    const std::string o = toml::find_or<std::string>(data, opt, "none");
    return o;
  }

  void add_opt(const std::string &opt, const std::string &val) {
    auto data = toml::parse(this->config_file_path);
    data[opt] = val;
  }

  bool make_opt_default(const std::string &opt) {
    auto data = toml::parse(this->config_file_path);

    if (data.contains(opt)) {
      data[opt] = "";
      return false;
    }

    return true;
  }
};
