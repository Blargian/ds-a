cmake_minimum_required (VERSION 3.20)
project(
	"Algorithmic Toolbox - week 5" 
  VERSION 1.0 
  DESCRIPTION "Data Structures & Algorithms Course"
  LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 17)

set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message( STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()


# ----- begin target definitions ----- # 

add_executable(
  binary_search
  "1_binary_search/binary_search.cpp"
)

add_executable(
  binary_search_duplicates
  "2_binary_search_duplicates/binary_search.cpp"
) 

add_executable(
  majority_element
  "3_majority_element/majority_element.cpp"
)

add_executable(
  improving_quicksort
  "4_improving_quicksort/sorting.cpp"
)

add_executable(
  number_of_inversions
  "5_number_of_inversions/inversions.cpp"
)

add_executable(
  organizing_a_lottery
  "6_organizing_a_lottery/points_and_segments.cpp"
)
 
add_executable(
  closest
  "7_closest_points/closest.cpp"
)

# ----- end target definitions ----- #
