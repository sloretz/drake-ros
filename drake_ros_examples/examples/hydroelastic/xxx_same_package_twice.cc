#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include <ament_index_cpp/get_package_share_directory.hpp>

void read_file(const std::filesystem::path & path) {
  if (!std::filesystem::exists(path)) {
    std::cout << "No such file: " << path.filename()  << "\n";
    return;
  }

  std::ifstream fin;
  fin.open(path.string(), std::ifstream::in);

  std::string line;
  std::getline(fin, line);
  std::cout << path.filename() << ": " << line << "\n";
}

int main() {
  const auto foo_path = ament_index_cpp::get_package_share_directory("foo");

  std::filesystem::path foo_fs_path{foo_path};;

  read_file(foo_fs_path / "foo.txt");
  read_file(foo_fs_path / "foo_again.txt");

    /* expected output?

I'm surprised by this one.
I would have thought bazel would complain that two rules generated
the same file in a runfiles set (the same file being the package marker
for the package foo)

$ bazel run //examples/hydroelastic:xxx_same_package_twice
"foo.txt": this is foo.txt
"foo_again.txt": this is foo_again.txt


Not surprised by this one.
The `foo` path is determined to be in the first ament prefix,
but foo_again.txt exists in the second prefix.

$ bazel run //examples/hydroelastic:xxx_same_package_twice_unique_prefix
"foo.txt": this is foo.txt
No such file: "foo_again.txt"
  */
}
