cmake_minimum_required(VERSION 3.10)
project(tethys_keyboard_control)

# Find Gazebo
find_package(gz-sim REQUIRED)

# Find required Gazebo components
find_package(gz-plugin REQUIRED)
find_package(gz-sim7 REQUIRED)
find_package(gz-physics7 REQUIRED)
find_package(gz-math7 REQUIRED)
find_package(gz-transport13 REQUIRED)
find_package(sdf14 REQUIRED)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create the fluid drag system plugin
add_library(fluid_drag_system SHARED src/fluid_drag_system.cpp)
target_link_libraries(fluid_drag_system 
  gz-sim7::gz-sim7
  gz-plugin12::gz-plugin12
  gz-physics7::gz-physics7
  gz-math7::gz-math7
  gz-transport13::gz-transport13
  sdf14::sdf14
)

# Install the plugin
install(TARGETS fluid_drag_system
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

# Set environment variable for Gazebo to find our plugins
set(ENV{GZ_SIM_SYSTEM_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/build:$ENV{GZ_SIM_SYSTEM_PATH}")
set(ENV{LD_LIBRARY_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/build:$ENV{LD_LIBRARY_PATH}")