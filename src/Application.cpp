#include <sstream>
#include <GL/glew.h> // or glad (understand opengl version to use the right functions (loading library))
#include <GLFW/glfw3.h> // create a screen instance
#include <iostream>
#include <fstream>

#include <string>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

// Callback when the window is resized
static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
static void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(void)
{

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSwapInterval(1);
    {
        if (glewInit() != GLEW_OK) {
            std::cout << "Error initializing GLEW" << std::endl;
        }

        float positions[] = {
        // positions        // colors
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f // top
        };


        unsigned int indices[] = { // index buffer (Order of drawing the vertices)
            0,1,2
        };


        // vertex array (define layout once instead of manually on each draw call)
        VertexArray va;

        VertexBuffer vb(positions, sizeof(positions));
        VertexBufferLayout layout; // understand this (setup of vertex buffer: stride, types etc.)
        layout.Push<float>(3); // # of vertices (x,y,z)?
        layout.Push<float>(3); // # of color (r,g,b)?

        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, sizeof(indices));

        ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
        std::cout << source.VertexSource << std::endl;
        std::cout << source.FragmentSource << std::endl;
        unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
        glUseProgram(shader);

        

        // lock in setup, prevent later code from changing bindings
        glBindVertexArray(0);
        glUseProgram(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        float r = 0.0f;
        const float COLOR_CHANGE_FREQ = 0.005f;
        float increment = COLOR_CHANGE_FREQ;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) // per frame
        {
            processInput(window);

            /* Render here */
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //set a background color
            glClear(GL_COLOR_BUFFER_BIT); // clear previous frames color buffer


            // define uniform to comminucate cpu var. to gpu var.
            /*int location = glGetUniformLocation(shader, "ourColor");
            ASSERT(location != -1);*/
            glUseProgram(shader);
            
            //GLCall(glUniform4f(location, r, 0.2f, 1.0f, 1.0f)); // triangle colors

            va.Bind();
            ib.Bind();

            //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe
            //GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr)); # of vertices
            GLCall(glDrawArrays(GL_TRIANGLES, 0, 3)); // if not using index buffer

            // flashing 
            /*if (r > 1.0f)
                increment = -COLOR_CHANGE_FREQ;
            else if (r < 0.0f)
                increment = COLOR_CHANGE_FREQ;
            r += increment;*/

            /* Swap front and back buffers */
            glfwSwapBuffers(window);
            /* Poll for and process events */
            glfwPollEvents();
        }

        glDeleteProgram(shader);
    }

    glfwTerminate();
    return 0;
}