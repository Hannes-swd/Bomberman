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
    src/HealingPotion.cpp
)

target_link_libraries(MyProgram PRIVATE raylib)
target_include_directories(MyProgram PRIVATE ${raylib_SOURCE_DIR}/src)

# Arbeitsverzeichnis auf Projektroot setzen (funktioniert in VS/VS Code)
set_target_properties(MyProgram PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

# ─────────────────────────────────────────────────────────────
# EXPORT ORDNER FÜR VERTEILUNG
# ─────────────────────────────────────────────────────────────

set(EXPORT_DIR "${CMAKE_SOURCE_DIR}/export")
set(EXPORT_BIN_DIR "${EXPORT_DIR}")

# Custom Target für den Export-Ordner
add_custom_target(ExportGame ALL
    COMMENT "Erstelle Export-Ordner mit Spiel und Assets"
)

# 1. Export-Ordner erstellen
add_custom_command(TARGET ExportGame PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${EXPORT_BIN_DIR}"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${EXPORT_BIN_DIR}/img"
)

# 2. Kopiere die fertige EXE nach dem Bauen
add_custom_command(TARGET MyProgram POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:MyProgram>
        "${EXPORT_BIN_DIR}/$<TARGET_FILE_NAME:MyProgram>"
)

# 3. Kopiere alle Bilder in den Export-Ordner
add_custom_command(TARGET ExportGame POST_BUILD
    # Bilder kopieren
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/img/player1.png
        "${EXPORT_BIN_DIR}/img/player1.png"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/img/player2.png
        "${EXPORT_BIN_DIR}/img/player2.png"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/img/player1win.png
        "${EXPORT_BIN_DIR}/img/player1win.png"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/img/player2win.png
        "${EXPORT_BIN_DIR}/img/player2win.png"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/img/bomb.png
        "${EXPORT_BIN_DIR}/img/bomb.png"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/img/bedrock.png
        "${EXPORT_BIN_DIR}/img/bedrock.png"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        ${CMAKE_SOURCE_DIR}/src/img/stone.png
        "${EXPORT_BIN_DIR}/img/stone.png"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        ${CMAKE_SOURCE_DIR}/src/img/BombUpgrade.png
        "${EXPORT_BIN_DIR}/img/BombUpgrade.png"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        ${CMAKE_SOURCE_DIR}/src/img/BpombCount.png
        "${EXPORT_BIN_DIR}/img/BpombCount.png"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        ${CMAKE_SOURCE_DIR}/src/img/mine.png
        "${EXPORT_BIN_DIR}/img/mine.png"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        ${CMAKE_SOURCE_DIR}/src/img/remotebombdetonator.png
        "${EXPORT_BIN_DIR}/img/remotebombdetonator.png"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        ${CMAKE_SOURCE_DIR}/src/img/remotebomb.png
        "${EXPORT_BIN_DIR}/img/remotebomb.png"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        ${CMAKE_SOURCE_DIR}/src/img/HealingPotion.png
        "${EXPORT_BIN_DIR}/img/HealingPotion.png"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        ${CMAKE_SOURCE_DIR}/src/img/gost.png
        "${EXPORT_BIN_DIR}/img/gost.png"
)

# Stelle sicher, dass ExportGame nach MyProgram ausgeführt wird
add_dependencies(ExportGame MyProgram)

# Optional: Lösche den Export-Ordner vor jedem Build (für saubere Exporte)
# add_custom_command(TARGET ExportGame PRE_BUILD
#     COMMAND ${CMAKE_COMMAND} -E remove_directory "${EXPORT_DIR}"
# )

# ─────────────────────────────────────────────────────────────
# Bestehende POST_BUILD Befehle für den normalen Build-Ordner
# ─────────────────────────────────────────────────────────────

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
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        ${CMAKE_SOURCE_DIR}/src/img/HealingPotion.png
        $<TARGET_FILE_DIR:MyProgram>/img/HealingPotion.png
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        ${CMAKE_SOURCE_DIR}/src/img/gost.png
        $<TARGET_FILE_DIR:MyProgram>/img/gost.png
)