
#define GLEW_STATIC

#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include"Renderer.h"
#include"Vbo.h"
#include"Ibo.h"
#include"Vao.h"
#include"Shader.h"
#include"VertexBufferLayout.h"
#include<iostream>
#include"Texture.h"
#include"vendor/glm/glm.hpp"
#include"vendor/glm/gtc/matrix_transform.hpp"
#include"vendor/glm/gtc/type_ptr.hpp"
#include "Camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);


// settings
const unsigned int SCR_WIDTH = 960;
const unsigned int SCR_HEIGHT = 540;
// camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 300.0f);
Camera camera(cameraPos);
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if(glewInit()!=GLEW_OK)
        std::cout<<"ERROR !"<<std::endl;


    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);


    float positions[] = {
      // Positions         // Normals           // Texture Coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f, // Vertex 0 (front)
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f, // Vertex 1 (front)
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f, // Vertex 2 (front)
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f, // Vertex 3 (front)

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f, // Vertex 4 (back)
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f, // Vertex 5 (back)
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f, // Vertex 6 (back)
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f, // Vertex 7 (back)

        // Left face normals
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f, // Vertex 8 (left)
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f, // Vertex 9 (left)
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f, // Vertex 10 (left)
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f, // Vertex 11 (left)

        // Right face normals
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f, // Vertex 12 (right)
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f, // Vertex 13 (right)
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f, // Vertex 14 (right)
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f, // Vertex 15 (right)

        // Top face normals
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f, // Vertex 16 (top)
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f, // Vertex 17 (top)
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f, // Vertex 18 (top)
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f, // Vertex 19 (top)

        // Bottom face normals
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f, // Vertex 20 (bottom)
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f, // Vertex 21 (bottom)
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f, // Vertex 22 (bottom)
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f  // Vertex 23 (bottom)

};

// Index buffer reste inchangé
unsigned int indices[] = {
     // Front face
    0, 1, 2,
    0, 2, 3,

    // Back face
    4, 5, 6,
    4, 6, 7,

    // Left face
    8, 9, 10,
    8, 10, 11,

    // Right face
    12, 13, 14,
    12, 14, 15,

    // Top face
    16, 17, 18,
    16, 18, 19,

    // Bottom face
    20, 21, 22,
    20, 22, 23,
};
    //  glEnable(GL_BLEND);
    //  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    //Vbo;
    Vbo vb = Vbo(positions,6 * 4 * 3 * 3 * 2 * sizeof(float));

    //vao
    Vao va;
    VertexBufferLayout layout;
    layout.Push(3, GL_FLOAT);
    layout.Push(3, GL_FLOAT);
    layout.Push(2, GL_FLOAT);
    va.addBuffer(vb, layout);

    Ibo ib = Ibo(indices, 12*3);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(100., 100., 100.));
    model = glm::rotate(model,glm::radians(0.0f),glm::vec3(0.0f,1.0f,0.0f));
    model = glm::rotate(model,glm::radians(10.0f),glm::vec3(1.0f,0.0f,0.0f));
    //glViewport(0.0f,0.0f,960.0f,540.0f);


    glm::mat4 proj = glm::mat4(1.0f);
    //proj = glm::ortho(0.0f,960.0f,0.0f,540.0f,-300.0f,300.0f);
    proj = glm::perspective(glm::radians(45.0f), 960.0f/540.0f, 0.1f, 1000.0f);

    glm::mat4 view = glm::mat4(1.0f);
    //view = glm::translate(glm::mat4(1.0f),-cameraPos);

    glm::vec4 lightColor(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos(0.0f,0.0f, 150.0f);



    Shader lightShader("../res/shaders/LightVertex.shader","../res/shaders/LightFragment.shader");
    lightShader.Bind();
    lightShader.SetUniform4f("lightColor",lightColor[0],lightColor[1],lightColor[2],lightColor[3]);


    Shader shader("../res/shaders/Vertex.shader","../res/shaders/Fragment.shader");
    shader.Bind();
    shader.SetUniform4f("u_Color",1.0f, 1.0f, 1.0f,1.0f);
    shader.SetUniform4f("lightColor",lightColor[0],lightColor[1],lightColor[2],1.0f);
    shader.SetUniform3f("lightPos", lightPos[0],lightPos[1],lightPos[2]);

    Texture textureDiff("../res/textures/container.png");
    Texture textureSpec("../res/textures/container_specular.png");

    shader.SetUniform1i("material.diffuse", 0);
    shader.SetUniform1i("material.specular",1);
    textureDiff.Bind(0);
    textureSpec.Bind(1);

    //shader.SetUniform3f("material.ambient", 0.24f, 	0.19f, 	0.07f);
    shader.SetUniform3f("material.specular",0.5f, 0.5f, 0.5f);
    shader.SetUniform1f("material.shininess", 2.0f * 128.0f);

    shader.SetUniform3f("light.ambient", 0.2f, 0.2f, 0.2f);
    shader.SetUniform3f("light.diffuse",  0.5f, 0.5f, 0.5f); // darken diffuse light a bit
    shader.SetUniform3f("light.specular", 1.0f, 1.0f, 1.0f);



    ///shader.SetUniform1i("u_Texture",0);
    glEnable(GL_DEPTH_TEST);
    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();

    Renderer renderer;

    float r = 0.0f;
    float rot = 0.5f;
    float inc = 0.01f;
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();

        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);


        glm::mat4 view;
        view = camera.GetViewMatrix();
        proj = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);

        //premier carré
        {
            model = glm::rotate(model,glm::radians(rot),glm::vec3(0.5f,1.0f,0.3f));


            glm::mat4 mvp = proj * view * model;

            shader.Bind();
            shader.SetUniform3f("viewPos", camera.Position[0],-camera.Position[1],camera.Position[2]);

            shader.SetUniformMat4f("u_MVP", mvp);
            shader.SetUniformMat4f("u_Model", model);
            shader.SetUniformMat4f("u_View", view);
            shader.SetUniformMat4f("u_Proj", proj);

            renderer.Draw(va,ib,shader);

        }

        // // 2eme carré
        // {
        //     glm::mat4 model = glm::translate(glm::mat4(1.0f),glm::vec3(0.0f,-300.0f,0.0f));
        //     model = glm::scale(model, glm::vec3(700., 10., 700.));
        //     model = glm::rotate(model,glm::radians(-40.0f),glm::vec3(1.0f,0.0f,0.0f));

        //     glm::mat4 mvp = proj * view * model;

        //     shader.Bind();
        //     shader.SetUniformMat4f("u_MVP", mvp);
        //     shader.SetUniformMat4f("u_Model", model);
        //     shader.SetUniformMat4f("u_View", view);
        //     shader.SetUniformMat4f("u_Proj", proj);

        //     renderer.Draw(va,ib,shader);

        // }
        // carré light
        {

            glm::mat4 model = glm::translate(glm::mat4(1.0f),lightPos);
            model = glm::scale(model, glm::vec3(5., 5., 5.));
            model = glm::rotate(model,glm::radians(30.0f),glm::vec3(1.0f,1.0f,0.0f));

            glm::mat4 mvp = proj * view * model;

            lightShader.Bind();
            lightShader.SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(va,ib,lightShader);

        }


        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
