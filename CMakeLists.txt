cmake_minimum_required(VERSION 4.0)
project(mini-football)
# --- Local FreeGLUT paths (relative to project) ---
set(FREEGLUT_DIR "${CMAKE_SOURCE_DIR}/external/freeglut")

include_directories(${FREEGLUT_DIR}/include)
link_directories(${FREEGLUT_DIR}/lib)

# --- Find OpenGL (Windows built-in) ---
find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(mini-football src/main.cpp
        src/entities/Player.cpp
        include/entities/Player.h
        src/entities/Field.cpp
        include/entities/Field.h
        src/entities/DBox.cpp
        include/entities/DBox.h
        src/entities/GoalPost.cpp
        include/entities/GoalPost.h
        src/entities/Ball.cpp
        include/entities/Ball.h
        src/entities/Scoreboard.cpp
        include/entities/Scoreboard.h
)
# --- Link OpenGL + FreeGLUT ---
target_link_libraries(mini-football
        ${OPENGL_LIBRARIES}
        freeglut.dll.a
)
