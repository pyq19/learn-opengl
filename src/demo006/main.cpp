// 使用两个着色器, 画两个不同颜色的三角形

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}";
const char *fragmentShaderYellowSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "FragColor = vec4(1.0f, 0.25f, 0.85f, 0.0f);\n" // TODO 这里是粉色 目前还搞不懂
    "}";
const char *fragmentShaderBlueSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "FragColor = vec4(1.0f, 0.85f, 0.0f, 0.0f);\n" // TODO 这里是黄色 目前还搞不懂
    "}";

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);

    int success;
    char infoLog[512];

    // 创建顶点着色器对象
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // 把着色器源码附加到着色器对象上并编译
    glCompileShader(vertexShader);

    // 创建编译片元着色器
    unsigned int fragmentShaderYellow, fragmentShaderBlue;
    fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderYellow, 1, &fragmentShaderYellowSource, NULL);
    glCompileShader(fragmentShaderYellow);
    fragmentShaderBlue = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderBlue, 1, &fragmentShaderBlueSource, NULL);
    glCompileShader(fragmentShaderBlue);

    // 着色器程序
    unsigned int shaderProgramYellow, shaderProgramBlue;
    shaderProgramYellow = glCreateProgram();
    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, fragmentShaderYellow);
    glLinkProgram(shaderProgramYellow);
    shaderProgramBlue = glCreateProgram();
    glAttachShader(shaderProgramBlue, vertexShader);
    glAttachShader(shaderProgramBlue, fragmentShaderBlue);
    glLinkProgram(shaderProgramBlue);

    // 两个三角形的顶点
    float vertices[] = {
        // 第一个三角形
        0.5f, 0.75f, 0.0f,
        0.25f, 0.25f, 0.0f,
        0.75f, 0.25f, 0.0f,
        // 第二个三角形
        -0.5f, -0.25f, 0.0f,
        -0.75f, -0.75f, 0.0f,
        -0.25f, -0.75f, 0.0f};

    // 把顶点数据存储在显存中, 用 VBO 顶点缓冲对象管理
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 创建 VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // 设置顶点属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 画第一个三角形
        glUseProgram(shaderProgramYellow);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // 画第二个三角形
        glUseProgram(shaderProgramBlue);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 3, 3); // 第一个 3 表示从数组缓存第 3 位开始画, 第二个 3 表示顶点个数

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 把着色器对象链接到程序对象之后 删除着色器对象
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderYellow);
    glDeleteShader(fragmentShaderBlue);

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgramYellow);
    glDeleteProgram(shaderProgramBlue);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}