#version 330 core
out vec4 FragColor;

uniform vec4 ourColor;  // 在程序代码中设置此变量

void main()
{
    FragColor = ourColor;
}