find_package(SDL3 REQUIRED)

add_executable (SparticleEngine "SparticleEngine.cpp" "SparticleEngine.h"  "main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SparticleEngine PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(SparticleEngine PRIVATE SDL3::SDL3)