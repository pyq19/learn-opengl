PROJECT(demo013)

FIND_PACKAGE(glfw3 REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)

SET(ROOT_DIR "../..")

SET(SOURCE_FILES main.cpp
    ${ROOT_DIR}/lib/glad.c 
    ${ROOT_DIR}/src/util/shader.cpp
    ${ROOT_DIR}/include/stb_image.cpp
)

ADD_EXECUTABLE(demo013 ${SOURCE_FILES})

TARGET_INCLUDE_DIRECTORIES(demo013
    PUBLIC 
        ${ROOT_DIR}/include
        ${ROOT_DIR}/src
)

TARGET_LINK_LIBRARIES(demo013 glfw)
TARGET_LINK_LIBRARIES(demo013 OpenGL::GL)
