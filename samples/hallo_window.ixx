//
// Created by PETROS on 10/09/2024.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

export module hallo_window;

namespace hallo_window_sample {
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void processInput(GLFWwindow *window);
    int execute();
    
    export int execute()
    {
        // inti glfw
        glfwInit();

        // init open gl version to 3.3
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        // use the core profile
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


        // create a window
        GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
        if (window == nullptr)
        {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
    

        // make the window part of the current render context
        glfwMakeContextCurrent(window);

        // initialize glad so we can have it ready
        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        // add a callback in case we resize the window
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // define the open gl view port
        // where does it start and what are its dimensions
        glViewport(0, 0, 800, 600);

        // while our current window stays open
        while(!glfwWindowShouldClose(window))
        {
            processInput(window);

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // draw stuff by switching buffers
            glfwSwapBuffers(window);

            // poll for events
            glfwPollEvents();
        
        }

        // terminate glfw
        glfwTerminate();
        return 0;
    }


    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void processInput(GLFWwindow *window) {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }
}