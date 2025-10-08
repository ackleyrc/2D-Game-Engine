find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

add_executable (SparticleEngine "SparticleEngine.cpp" "SparticleEngine.h"  "main.cpp" "EngineConfig.h" "InputManager.h" "InputManager.cpp" "GameObject.h" "GameObject.cpp" "ResourceManager.h" "ResourceManager.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SparticleEngine PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(SparticleEngine PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)