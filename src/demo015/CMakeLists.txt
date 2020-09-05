PROJECT(demo015)

FIND_PACKAGE(glfw3 REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)

SET(ROOT_DIR "../..")

SET(SOURCE_FILES main.cpp
    ${ROOT_DIR}/lib/glad.c 
    ${ROOT_DIR}/src/util/shader.cpp
    ${ROOT_DIR}/include/stb_image.cpp
)

ADD_EXECUTABLE(demo015 ${SOURCE_FILES})

TARGET_INCLUDE_DIRECTORIES(demo015
    PUBLIC 
        ${ROOT_DIR}/include
        ${ROOT_DIR}/src
)

TARGET_LINK_LIBRARIES(demo015 glfw)
TARGET_LINK_LIBRARIES(demo015 OpenGL::GL)
