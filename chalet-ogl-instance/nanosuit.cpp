

// Std. Includes
#include <string>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include <SOIL.h>

// Properties
GLuint screenWidth = 1920, screenHeight = 1080;

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void Do_Movement();

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
GLfloat lastTime= 0.0f;

// The MAIN function, from here we start our application and run our Game loop
int main()
{
    // Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", nullptr, nullptr); // Windowed
    glfwMakeContextCurrent(window);

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // Options
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initialize GLEW to setup the OpenGL Function pointers
    glewExperimental = GL_TRUE;
    glewInit();

    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // Setup some OpenGL options
    glEnable(GL_DEPTH_TEST);

    // Setup and compile our shaders
    Shader shader("./Shaders/model_loading.vs", "./Shaders/model_loading.frag");

    // Load models
//    Model ourModel("models/Nanosuit2/nanosuit2.3ds");
//    Model ourModel("models/Nanosuit2/nanosuit2.obj");
//    Model ourModel("models/mg-27/mg-27/mg-27.obj");
    Model ourModel("models/chalet/chalet.3ds");
    // Draw in wireframe
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
GLuint amount = 99;
glm::mat4* modelMatrices;
modelMatrices = new glm::mat4[amount];
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 0.0f,  5.0f,  0.0f),
        glm::vec3( 0.0f,  10.0f,  0.0f),
        glm::vec3( 0.0f,  15.0f,  0.0f),
        glm::vec3( 0.0f,  20.0f,  0.0f),
        glm::vec3( 0.0f,  25.0f,  0.0f),
        glm::vec3( 0.0f,  -5.0f,  0.0f),
        glm::vec3( 0.0f,  -10.0f,  0.0f),
        glm::vec3( 0.0f,  -15.0f,  0.0f),
        glm::vec3( 0.0f,  -20.0f,  0.0f),
        glm::vec3( 0.0f,  -25.0f,  0.0f),

        glm::vec3(-5.0f,  0.0f,  0.0f),
        glm::vec3(-5.0f,  5.0f,  0.0f),
        glm::vec3(-5.0f,  10.0f,  0.0f),
        glm::vec3(-5.0f,  15.0f,  0.0f),
        glm::vec3(-5.0f,  20.0f,  0.0f),
        glm::vec3(-5.0f,  25.0f,  0.0f),
        glm::vec3(-5.0f,  -5.0f,  0.0f),
        glm::vec3(-5.0f,  -10.0f,  0.0f),
        glm::vec3(-5.0f,  -15.0f,  0.0f),
        glm::vec3(-5.0f,  -20.0f,  0.0f),
        glm::vec3(-5.0f,  -25.0f,  0.0f),

        glm::vec3(5.0f,  0.0f,  0.0f),
        glm::vec3(5.0f,  5.0f,  0.0f),
        glm::vec3(5.0f,  10.0f,  0.0f),
        glm::vec3(5.0f,  15.0f,  0.0f),
        glm::vec3(5.0f,  20.0f,  0.0f),
        glm::vec3(5.0f,  25.0f,  0.0f),
        glm::vec3(5.0f,  -5.0f,  0.0f),
        glm::vec3(5.0f,  -10.0f,  0.0f),
        glm::vec3(5.0f,  -15.0f,  0.0f),
        glm::vec3(5.0f,  -20.0f,  0.0f),
        glm::vec3(5.0f,  -25.0f,  0.0f),

        glm::vec3( 10.0f,  0.0f,  0.0f),
        glm::vec3( 10.0f,  5.0f,  0.0f),
        glm::vec3( 10.0f,  10.0f,  0.0f),
        glm::vec3( 10.0f,  15.0f,  0.0f),
        glm::vec3( 10.0f,  20.0f,  0.0f),
        glm::vec3( 10.0f,  25.0f,  0.0f),
        glm::vec3( 10.0f,  -5.0f,  0.0f),
        glm::vec3( 10.0f,  -10.0f,  0.0f),
        glm::vec3( 10.0f,  -15.0f,  0.0f),
        glm::vec3( 10.0f,  -20.0f,  0.0f),
        glm::vec3( 10.0f,  -25.0f,  0.0f),

        glm::vec3(-10.0f,  0.0f,  0.0f),
        glm::vec3(-10.0f,  5.0f,  0.0f),
        glm::vec3(-10.0f,  10.0f,  0.0f),
        glm::vec3(-10.0f,  15.0f,  0.0f),
        glm::vec3(-10.0f,  20.0f,  0.0f),
        glm::vec3(-10.0f,  25.0f,  0.0f),
        glm::vec3(-10.0f,  -5.0f,  0.0f),
        glm::vec3(-10.0f,  -10.0f,  0.0f),
        glm::vec3(-10.0f,  -15.0f,  0.0f),
        glm::vec3(-10.0f,  -20.0f,  0.0f),
        glm::vec3(-10.0f,  -25.0f,  0.0f),

        glm::vec3(15.0f,  0.0f,  0.0f),
        glm::vec3(15.0f,  5.0f,  0.0f),
        glm::vec3(15.0f,  10.0f,  0.0f),
        glm::vec3(15.0f,  15.0f,  0.0f),
        glm::vec3(15.0f,  20.0f,  0.0f),
        glm::vec3(15.0f,  25.0f,  0.0f),
        glm::vec3(15.0f,  -5.0f,  0.0f),
        glm::vec3(15.0f,  -10.0f,  0.0f),
        glm::vec3(15.0f,  -15.0f,  0.0f),
        glm::vec3(15.0f,  -20.0f,  0.0f),
        glm::vec3(15.0f,  -25.0f,  0.0f),

        glm::vec3(-15.0f,  0.0f,  0.0f),
        glm::vec3(-15.0f,  5.0f,  0.0f),
        glm::vec3(-15.0f,  10.0f,  0.0f),
        glm::vec3(-15.0f,  15.0f,  0.0f),
        glm::vec3(-15.0f,  20.0f,  0.0f),
        glm::vec3(-15.0f,  25.0f,  0.0f),
        glm::vec3(-15.0f,  -5.0f,  0.0f),
        glm::vec3(-15.0f,  -10.0f,  0.0f),
        glm::vec3(-15.0f,  -15.0f,  0.0f),
        glm::vec3(-15.0f,  -20.0f,  0.0f),
        glm::vec3(-15.0f,  -25.0f,  0.0f),

        glm::vec3(20.0f,  0.0f,  0.0f),
        glm::vec3(20.0f,  5.0f,  0.0f),
        glm::vec3(20.0f,  10.0f,  0.0f),
        glm::vec3(20.0f,  15.0f,  0.0f),
        glm::vec3(20.0f,  20.0f,  0.0f),
        glm::vec3(20.0f,  25.0f,  0.0f),
        glm::vec3(20.0f,  -5.0f,  0.0f),
        glm::vec3(20.0f,  -10.0f,  0.0f),
        glm::vec3(20.0f,  -15.0f,  0.0f),
        glm::vec3(20.0f,  -20.0f,  0.0f),
        glm::vec3(20.0f,  -25.0f,  0.0f),

        glm::vec3(-20.0f,  0.0f,  0.0f),
        glm::vec3(-20.0f,  5.0f,  0.0f),
        glm::vec3(-20.0f,  10.0f,  0.0f),
        glm::vec3(-20.0f,  15.0f,  0.0f),
        glm::vec3(-20.0f,  20.0f,  0.0f),
        glm::vec3(-20.0f,  25.0f,  0.0f),
        glm::vec3(-20.0f,  -5.0f,  0.0f),
        glm::vec3(-20.0f,  -10.0f,  0.0f),
        glm::vec3(-20.0f,  -15.0f,  0.0f),
        glm::vec3(-20.0f,  -20.0f,  0.0f),
        glm::vec3(-20.0f,  -25.0f,  0.0f),

    };
#if 0
    glm::vec3 modelPositions[121];
    GLuint row = 11, column = 11, index = 0;
    for (GLuint i = -5; i < 6; i++)
    {
	for (GLuint j = -5; j < 6; j++) 
	{
	    modelPositions[index] = glm::vec3( i*5.0f, j*5.0f, 0.0f);
	    modelMatrices[index] = glm::translate(modelMatrices[index], modelPositions[index]);
	    index ++ ;
	}
    }
#else
    for (GLuint i = 0; i < amount; i++ )
    	modelMatrices[i] = glm::translate(modelMatrices[i], cubePositions[i]);
#endif
    long count = 0;
    // Game loop
    while(!glfwWindowShouldClose(window))
    {	
	GLfloat angle = (GLfloat)glfwGetTime() * 0.0001f;
	for (GLuint i = 0; i < amount; i++)
	{
	    modelMatrices[i] = glm::rotate(modelMatrices[i], angle, glm::vec3(0.0f, 0.0f, 1.0f));
	}
	for (GLuint i = 0; i < ourModel.meshes.size(); i++)
	{
	    GLuint VAO =  ourModel.meshes[i].VAO;
	    GLuint buffer;
	    glBindVertexArray(VAO);
	    glGenBuffers(1, &buffer);
	    glBindBuffer(GL_ARRAY_BUFFER, buffer);
	    glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);
	            // Set attribute pointers for matrix (4 times vec4)
            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)0);
            glEnableVertexAttribArray(4);
            glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(sizeof(glm::vec4)));
            glEnableVertexAttribArray(5);
            glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(2 * sizeof(glm::vec4)));
            glEnableVertexAttribArray(6);
            glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(3 * sizeof(glm::vec4)));

            glVertexAttribDivisor(3, 1);
            glVertexAttribDivisor(4, 1);
            glVertexAttribDivisor(5, 1);
            glVertexAttribDivisor(6, 1);
    
            glBindVertexArray(0);
	}
	    
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
	if ( count++ % 100 == 0 ) {
            printf("fps: %f\n", 100.0f/(currentFrame - lastTime));	
	    lastTime = currentFrame;
	}
        // Check and call events
        glfwPollEvents();
        Do_Movement();

        // Clear the colorbuffer
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();   // <-- Don't forget this one!
        // Transformation matrices
        glm::mat4 projection = glm::perspective(camera.Zoom, (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Draw the loaded model
	for (GLuint i = 0;  i < ourModel.meshes.size(); i++) 
	{
            //glBindTexture(GL_TEXTURE_2D, ourModel.textures_loaded[i].id);
            glBindTexture(GL_TEXTURE_2D, ourModel.meshes[i].textures[0].id);
            glBindVertexArray(ourModel.meshes[i].VAO);
            glDrawElementsInstanced(GL_TRIANGLES, ourModel.meshes[i].vertices.size(), GL_UNSIGNED_INT, 0, amount);
            glBindVertexArray(0);
	    glBindTexture(GL_TEXTURE_2D, 0);
	}
        // Swap the buffers
        glfwSwapBuffers(window);
    }
    delete[] modelMatrices;
    glfwTerminate();
    return 0;
}

#pragma region "User input"

// Moves/alters the camera positions based on user input
void Do_Movement()
{
    // Camera controls
    if(keys[GLFW_KEY_W])
        camera.ProcessKeyboard(FORWARD, deltaTime*10);
    if(keys[GLFW_KEY_S])
        camera.ProcessKeyboard(BACKWARD, deltaTime*10);
    if(keys[GLFW_KEY_A])
        camera.ProcessKeyboard(LEFT, deltaTime*10);
    if(keys[GLFW_KEY_D])
        camera.ProcessKeyboard(RIGHT, deltaTime*10);
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if(action == GLFW_PRESS)
        keys[key] = true;
    else if(action == GLFW_RELEASE)
        keys[key] = false;	
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos; 
    
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}	

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

#pragma endregion


