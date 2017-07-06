#ifndef GLSL_H
#define GLSL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>

#include "settings.h"

/* GLSL Compiler & API :3 */
/* Check functions headers for usage */

#define SHADER_NULL 0

typedef struct Shader{      // Simple structure for loading & using shaders
    GLuint vertexShader;    // Vertex shader
    GLuint fragmentShader;  // Fragment shader
    GLuint program;         // Program (attached with both shaders)
}Shader;

/* ----------------------------- MAIN FUNCTIONS ----------------------------- */
/* CREATE SHADER */
/* arguments: directory to vertex and fragment shader files */
/* return: Shader structure with both shaders and program attached */
Shader *createShader(char *vertex, char *fragment);

/* USE SHADER */
/* arguments: Shader structure */
void useShader(Shader *shader);

/* FREE SHADER */
/* arguments: Shader structure */
void freeShader(Shader *shader);
/* ----------------------------- MAIN FUNCTIONS ----------------------------- */

#endif
