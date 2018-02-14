//
//  Graphics.cpp
//  Clarity Engine
//
//  Created by Galal Hassan on 2018-02-12.
//  Copyright © 2018 The Pixel Crushers. All rights reserved.
//

#include "Graphics.hpp"


///////////////////////////////////////////////////////////////////////
//
// triangles.cpp
//
///////////////////////////////////////////////////////////////////////

#include "stdlib.h"
#include <iostream>

#include <glew.h>
#include "time.h"
#include <glm.hpp>
#include <matrix_transform.hpp>
#include <GLUT/GLUT.h>
#include <LoadShaders.h>

#define X_AXIS glm::vec3(1,0,0)
#define Y_AXIS glm::vec3(0,1,0)
#define Z_AXIS glm::vec3(0,0,1)

GLuint gVAO;
GLuint MatrixID;
glm::mat4 MVP;
glm::mat4 View;
glm::mat4 Projection;

glm::vec3 currentCamPos;
glm::vec3 currentCamVel;

int frame=0,currentTime,timebase=0;
float deltaTime = 0;
bool keyStates[256] = {}; // Create an array of boolean values of length 256 (0-255)
void init(void){
    //keyStates = false;
    //Specifying the name of vertex and fragment shaders.
    ShaderInfo shaders[] = {
        { GL_VERTEX_SHADER, "triangles.vert" },
        { GL_FRAGMENT_SHADER, "triangles.frag" },
        { GL_NONE, NULL }
    };
    
    //Loading and compiling shaders
    GLuint program = LoadShaders(shaders);
    glUseProgram(program);    //My Pipeline is set up
    
    //Generating two buffers, one is used to store the coordinates of the vertices
    //The other one is not used. Just wanted to show that we can allocate as many as buffers, some of which might left unused.
    glGenVertexArrays(1, &gVAO);
    glBindVertexArray(gVAO);
    
    // Get a handle for our "MVP" uniform
    MatrixID = glGetUniformLocation(program, "MVP");
    
    // Projection matrix : 45∞ Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    // Or, for an ortho camera :
    //Projection = glm::ortho(-1.0f,1.0f,-1.0f,1.0f,0.0f,100.0f); // In world coordinates
    
    currentCamPos = glm::vec3(3.0f,3.0f,4.0f);
    currentCamVel = glm::vec3(0.0f);
    
    // Camera matrix
    View = glm::lookAt(
                       currentCamPos, // Camera is at (4,3,3), in World Space
                       glm::vec3(0,0,0), // and looks at the origin
                       glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                       );
    
    float cube_verticies[] = {
        // front
        -0.45, -0.45,  0.45,
        0.45, -0.45,  0.45,
        0.45,  0.45,  0.45,
        -0.45,  0.45,  0.45,
        // back
        -0.45, -0.45, -0.45,
        0.45, -0.45, -0.45,
        0.45,  0.45, -0.45,
        -0.45,  0.45, -0.45,
    };
    GLuint cubeVerticies_vbo = 0;
    glGenBuffers(1, &cubeVerticies_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVerticies_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_verticies), cube_verticies, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    
    float cube_colors[] = {
        // front colors
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0,
        1.0, 1.0, 1.0,
        // back colors
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0,
        1.0, 1.0, 1.0,
    };
    GLuint cube_colors_vbo = 0;
    glGenBuffers(1, &cube_colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, cube_colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);
    
    GLushort cube_index_array[] = {
        // front
        0, 1, 2,
        2, 3, 0,
        // top
        1, 5, 6,
        6, 2, 1,
        // back
        7, 6, 5,
        5, 4, 7,
        // bottom
        4, 0, 3,
        3, 7, 4,
        // left
        4, 5, 1,
        1, 0, 4,
        // right
        3, 2, 6,
        6, 7, 3,
    };
    GLuint ibo_cube_elements;
    glGenBuffers(1, &ibo_cube_elements);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_index_array), cube_index_array, GL_STATIC_DRAW);
}

void keyDown(unsigned char key, int x, int y){
    keyStates[key] = true; // Set the state of the current key to pressed
}

void keyUp(unsigned char key, int x, int y){
    keyStates[key] = false; // Release the state of the current key to pressed
}

void keyOperations (void) {
    float cameraSpeed = 10.0f;
    if (keyStates['w']) { // If the 'w' key has been pressed
        currentCamPos.z -= cameraSpeed * (deltaTime);
    }
    if (keyStates['s']) { // If the 's' key has been pressed
        currentCamPos.z += cameraSpeed * (deltaTime);
    }
    if (keyStates['a']) { // If the 'a' key has been pressed
        currentCamPos.x -= cameraSpeed * (deltaTime);
    }
    if (keyStates['d']) { // If the 'd' key has been pressed
        currentCamPos.x += cameraSpeed * (deltaTime);
    }
    if (keyStates['r']) { // If the 'r' key has been pressed
        currentCamPos.y += cameraSpeed * (deltaTime);
    }
    if (keyStates['f']) { // If the 'f' key has been pressed
        currentCamPos.y -= cameraSpeed * (deltaTime);
    }
    View = glm::lookAt(
                       currentCamPos, // Camera is at (4,3,3), in World Space
                       glm::vec3(0,0,0), // and looks at the origin
                       glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                       );
}

void keyboardFun(unsigned char key, int x, int y){
    float cameraSpeed = 10.0f;
    switch(key) {
        case 'w':
            // call a function
            currentCamPos.z -= cameraSpeed * (deltaTime);
            std::cout<<deltaTime<<std::endl;
            break;
        case 's':
            currentCamPos.z += cameraSpeed * (deltaTime);
            // call a function
            break;
        case 'a':
            currentCamPos.x -= cameraSpeed * (deltaTime);
            // call a function
            break;
        case 'd':
            currentCamPos.x += cameraSpeed * (deltaTime);
            // call a function
            break;
        case 'r':
            currentCamPos.y += cameraSpeed * (deltaTime);
            // call a function
            break;
        case 'f':
            currentCamPos.y -= cameraSpeed * (deltaTime);
            // call a function
            break;
            
        default:
            break;
    }
    
}

void transformObject(glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 translation){
    glm::mat4 Model;
    Model = glm::mat4(1.0f);
    Model = glm::translate(Model, translation);
    Model = glm::rotate(Model, glm::radians(rotationAngle), rotationAxis);
    Model = glm::scale(Model, scale);
    
    MVP = Projection * View * Model;
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
}

//---------------------------------------------------------------------
//
// display
//
void display(void){
    keyOperations();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.5f, 0.9f, 0.0f);
    
    //    transformObject(glm::vec3( 1,1,1), X_AXIS + Y_AXIS + Z_AXIS, 0, glm::vec3(0.0f,0,0.0f));
    transformObject(glm::vec3(5.0f,0.1f,5.0f), X_AXIS + Y_AXIS + Z_AXIS, 0, glm::vec3(0.0f,-2.0f,0.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
    
    float angle = glutGet(GLUT_ELAPSED_TIME) / 1000.0 * -45;  // 45° per second
    transformObject(glm::vec3(0.5f), X_AXIS + Y_AXIS + Z_AXIS, angle, glm::vec3(0.0f,-0.45f,0.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
    
    angle = glutGet(GLUT_ELAPSED_TIME) / 1000.0 * 45;  // 45° per second
    transformObject(glm::vec3(0.5f), X_AXIS + Y_AXIS + Z_AXIS, angle, glm::vec3(0.0f,0.45f,0.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
    
    glutSwapBuffers();
    deltaTime = (glutGet(GLUT_ELAPSED_TIME) - currentTime)/1000.0f;
    currentTime = glutGet(GLUT_ELAPSED_TIME);
}

void idle(){
    
}

void Timer(int id){
    glutPostRedisplay();
    glutTimerFunc(15, Timer, 0);
}

//---------------------------------------------------------------------
//
// main
//
//int main(int argc, char** argv){
//    
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_RGBA | GLUT_3_2_CORE_PROFILE | GLUT_DOUBLE | GLUT_DEPTH);
//    
//    glutInitWindowSize(1024, 768);
//    glutInitWindowPosition(0, 0);
//    glutCreateWindow("Hello World");
//    
//    glewExperimental = true;
//    glewInit();    //Initializes the glew and prepares the drawing pipeline.
//    
//    glEnable(GL_CULL_FACE); // cull face
//    glCullFace(GL_BACK); // cull back face
//    glFrontFace(GL_CCW); // GL_CCW for counter clock-wise
//    glEnable(GL_DEPTH_TEST);
//    init();
//    
//    glutTimerFunc(15, Timer, 0);
//    
//    glutDisplayFunc(display);
//    
//    //glutKeyboardFunc(keyboardFun);
//    glutKeyboardFunc(keyDown);
//    glutKeyboardUpFunc(keyUp);
//    
//    glutIdleFunc(idle);
//    
//    glutMainLoop();
//}




