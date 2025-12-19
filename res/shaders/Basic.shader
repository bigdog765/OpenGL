#shader vertex
#version 410 core
    
layout(location = 0) in vec3 aPos; // vertex attribute
layout(location = 1) in vec3 aColor;
out vec3 ourColor;

void main()
{
    gl_Position = vec4(aPos, 1.0); // we give a vec3 to vec4’s constructor
    ourColor = aColor;

};

#shader fragment
#version 410 core
// can receive input from vertex

out vec4 FragColor;

in vec3 ourColor;
    
void main()
{
    FragColor = vec4(ourColor, 1.0);

};

    