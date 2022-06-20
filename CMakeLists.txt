cmake_minimum_required(VERSION 3.22.2)

project(Raycaster)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/raycaster.cpp
)

add_subdirectory(ext/glfw)
add_subdirectory(ext/glm)

target_include_directories(${PROJECT_NAME}
    PRIVATE ext/glfw/include
    PRIVATE ext/glm/glm
)

target_link_directories(${PROJECT_NAME}
    PUBLIC ext/glfw/src
    PUBLIC ext/glm
)

if (WIN32)
    target_link_libraries(${PROJECT_NAME}
        glfw3
        glm
        opengl32
        gdi32
    )
endif ()

if (UNIX)
    target_link_libraries(${PROJECT_NAME}
        glfw
        glm
        GL
    )
endif ()