#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include <ament_index_cpp/get_package_share_directory.hpp>

void read_file(const std::filesystem::path & path) {
  std::ifstream fin;
  fin.open(path.string(), std::ifstream::in);

  std::string line;
  std::getline(fin, line);
  std::cout << path.filename() << ": " << line << "\n";
}

int main() {
  const auto foo_path = ament_index_cpp::get_package_share_directory("foo");
  const auto bar_path = ament_index_cpp::get_package_share_directory("bar");

  std::filesystem::path foo_fs_path{foo_path};
  std::filesystem::path bar_fs_path{bar_path};

  read_file(foo_fs_path / "foo.txt");
  read_file(bar_fs_path / "bar.txt");

    /* expected output
$ bazel run //examples/hydroelastic:xxx_dep_two_packages
"foo.txt": this is foo.txt
"bar.txt": this is bar.txt
  */
}
