cmake_minimum_required(VERSION 3.23)

project(Myproject CXX)

include(FetchContent)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 5.5
)

FetchContent_MakeAvailable(raylib)

# ALLE .cpp Dateien hier auflisten
add_executable(MyProgram 
    src/main.cpp
    src/map.cpp
    src/globals.cpp
    src/player.cpp
    src/bomb.cpp
    src/cam.cpp
    src/Ui.cpp
    src/textures.cpp
    src/item.cpp
    src/wall.cpp
    src/mine.cpp
    src/remoteBomb.cpp
)

target_link_libraries(MyProgram PRIVATE raylib)
target_include_directories(MyProgram PRIVATE ${raylib_SOURCE_DIR}/src)

# Arbeitsverzeichnis auf Projektroot setzen (funktioniert in VS/VS Code)
set_target_properties(MyProgram PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

# Assets automatisch in den Build-Ordner kopieren
add_custom_command(TARGET MyProgram POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:MyProgram>/img
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/img/player1.png
        $<TARGET_FILE_DIR:MyProgram>/img/player1.png
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/img/player2.png
        $<TARGET_FILE_DIR:MyProgram>/img/player2.png

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/img/player1win.png
        $<TARGET_FILE_DIR:MyProgram>/img/player1win.png
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/img/player2win.png
        $<TARGET_FILE_DIR:MyProgram>/img/player2win.png

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/img/bomb.png
        $<TARGET_FILE_DIR:MyProgram>/img/bomb.png

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/img/bedrock.png
        $<TARGET_FILE_DIR:MyProgram>/img/bedrock.png

    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        ${CMAKE_SOURCE_DIR}/src/img/stone.png
        $<TARGET_FILE_DIR:MyProgram>/img/stone.png

    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        ${CMAKE_SOURCE_DIR}/src/img/BombUpgrade.png
        $<TARGET_FILE_DIR:MyProgram>/img/BombUpgrade.png

    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        ${CMAKE_SOURCE_DIR}/src/img/BpombCount.png
        $<TARGET_FILE_DIR:MyProgram>/img/BpombCount.png
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        ${CMAKE_SOURCE_DIR}/src/img/mine.png
        $<TARGET_FILE_DIR:MyProgram>/img/mine.png
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        ${CMAKE_SOURCE_DIR}/src/img/remotebombdetonator.png
        $<TARGET_FILE_DIR:MyProgram>/img/remotebombdetonator.png
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        ${CMAKE_SOURCE_DIR}/src/img/remotebomb.png
        $<TARGET_FILE_DIR:MyProgram>/img/remotebomb.png
    
)