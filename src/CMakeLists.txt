# Generic test that uses conan libs
add_executable(lexicographic_subset lexicographic_subset.cpp)
target_link_libraries(lexicographic_subset PRIVATE
  project_options
  project_warnings
  CONAN_PKG::docopt.cpp
  CONAN_PKG::fmt
  CONAN_PKG::spdlog
)
#add_executable(sub_perm sub_perm.cpp)
#target_link_libraries(sub_perm PRIVATE
#  project_options
#  project_warnings
#  CONAN_PKG::docopt.cpp
#  CONAN_PKG::fmt
#  CONAN_PKG::spdlog
#)
add_executable(sum_composition sum_composition.cpp)
target_link_libraries(sum_composition PRIVATE
  project_options
  project_warnings
  CONAN_PKG::docopt.cpp
  CONAN_PKG::fmt
  CONAN_PKG::spdlog
  span
)
add_executable(sum_partition sum_partition.cpp)
target_link_libraries(sum_partition PRIVATE
  project_options
  project_warnings
  CONAN_PKG::docopt.cpp
  CONAN_PKG::fmt
  CONAN_PKG::spdlog
  span
)
add_executable(small_prime small_prime.cpp)
target_link_libraries(small_prime PRIVATE
  project_options
  project_warnings
  CONAN_PKG::docopt.cpp
  CONAN_PKG::fmt
  CONAN_PKG::spdlog
)
add_executable(num_set_bits num_set_bits.cpp)
target_link_libraries(num_set_bits PRIVATE
  project_options
  project_warnings
  CONAN_PKG::docopt.cpp
  CONAN_PKG::fmt
  CONAN_PKG::spdlog
)
add_executable(set_partitions set_partitions.cpp)
target_link_libraries(set_partitions PRIVATE
  project_options
  project_warnings
  CONAN_PKG::docopt.cpp
  CONAN_PKG::fmt
  CONAN_PKG::spdlog
)
