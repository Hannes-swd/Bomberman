cmake_minimum_required(VERSION 3.23)

project(Myproject CXX)

include(FetchContent)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 5.5
)

FetchContent_MakeAvailable(raylib)

# Alle .cpp Dateien automatisch finden
file(GLOB SOURCES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(MyProgram ${SOURCES})

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
)

# 2. Kopiere die fertige EXE nach dem Bauen in den Export-Ordner
add_custom_command(TARGET MyProgram POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:MyProgram>
        "${EXPORT_BIN_DIR}/$<TARGET_FILE_NAME:MyProgram>"
)

# 3. Kopiere den kompletten img-Ordner in den Export-Ordner
add_custom_command(TARGET ExportGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/src/img"
        "${EXPORT_BIN_DIR}/img"
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

# Kopiere den kompletten img-Ordner in den Build-Ordner
add_custom_command(TARGET MyProgram POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/src/img"
        "$<TARGET_FILE_DIR:MyProgram>/img"
)