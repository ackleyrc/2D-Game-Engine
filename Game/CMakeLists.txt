find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

add_executable (
    MazeEaterGame 
    "main.cpp"
    "MazeEaterGame.h" 
    "MazeEaterGame.cpp"
    "PlayerController.h"
    "PlayerController.cpp"
    "GameConfig.h"
    "TileMap.h"
    "TileMap.cpp"
    "ETileType.h"
    "PelletManager.h" 
    "PelletManager.cpp"
    "GameEvents.h"
    "ScoreManager.h" 
    "ScoreManager.cpp"
    "EntityMovement.h" 
    "EntityMovement.cpp"
    "EDirection.h" 
    "IMovementController.h"
    "GhostController.h" 
    "GhostController.cpp"
    "EGhostPersonality.h"
    "AIBlackboard.h" 
    "AIBlackboard.cpp"
    "EGhostMode.h"
)

set_target_properties(
    MazeEaterGame PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(
    MazeEaterGame 
    PRIVATE 
        SparticleEngineLib
)

target_include_directories(
    MazeEaterGame
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_command(
    TARGET MazeEaterGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL3::SDL3>
        $<TARGET_FILE_DIR:MazeEaterGame>
)

add_custom_command(
    TARGET MazeEaterGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL3_image::SDL3_image>
        $<TARGET_FILE_DIR:MazeEaterGame>
)

add_custom_command(
    TARGET MazeEaterGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:MazeEaterGame>/assets"
    COMMENT "Copying assets to output directory..."
)