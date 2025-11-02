find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

if (SPARTICLE_BUILD_SHARED)
    add_library (SparticleEngineLib SHARED
        "src/GameObject.cpp"
        "src/InputManager.cpp"
        "src/ResourceManager.cpp"
        "src/ResourceManagerTypes.h"
        "src/SDLState.h"
        "src/SparticleEngine.cpp"
        "src/Component.cpp"
        "src/AnimationComponent.cpp"
        "src/SpriteComponent.cpp"
        "src/EngineInternalUtils.h"
    )
else()
    add_library (SparticleEngineLib STATIC
        "src/GameObject.cpp"
        "src/InputManager.cpp"
        "src/ResourceManager.cpp"
        "src/ResourceManagerTypes.h"
        "src/SDLState.h"
        "src/SparticleEngine.cpp"
        "src/Component.cpp"
        "src/AnimationComponent.cpp"
        "src/SpriteComponent.cpp"
        "src/EngineInternalUtils.h"
    )
endif()

if(SPARTICLE_BUILD_SHARED)
    target_compile_definitions(SparticleEngineLib 
        PRIVATE 
            SparticleEngineLib_EXPORTS 
            SPARTICLE_BUILD_SHARED
    )
endif()

set_target_properties(SparticleEngineLib PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(SparticleEngineLib 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/external
)

target_link_libraries(SparticleEngineLib 
    PUBLIC 
        SDL3::SDL3 
        SDL3_image::SDL3_image
)