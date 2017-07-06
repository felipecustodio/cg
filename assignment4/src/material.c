#include "../includes/material.h"

/* --------------------------- STRUCTURE HANDLING --------------------------- */
/* CREATE MATERIAL */
/* return: blank Material */
Material *createMaterial(){
    Material *mat = (Material *) malloc(sizeof(Material));

    mat->diffuse = (GLfloat *) malloc(sizeof(GLfloat) * 4);
    mat->diffuse[0] = 0.0f;
    mat->diffuse[1] = 0.0f;
    mat->diffuse[2] = 0.0f;
    mat->diffuse[3] = 0.0f;

    mat->specular = (GLfloat *) malloc(sizeof(GLfloat) * 4);
    mat->specular[0] = 0.0f;
    mat->specular[1] = 0.0f;
    mat->specular[2] = 0.0f;
    mat->specular[3] = 0.0f;

    mat->emission = (GLfloat *) malloc(sizeof(GLfloat) * 4);
    mat->emission[0] = 0.0f;
    mat->emission[1] = 0.0f;
    mat->emission[2] = 0.0f;
    mat->emission[3] = 0.0f;

    mat->shininess = 0;

    return mat;
}

/* FREE MATERIAL */
/* arguments: Material structure */
void freeMaterial(Material *mat){
    if(mat == NULL) return;
    else{
        free(mat->diffuse);
        free(mat->specular);
        free(mat->emission);
        free(mat);
    }
}
/* --------------------------- STRUCTURE HANDLING --------------------------- */

/* --------------------------- GETTERS & SETTERS ---------------------------- */
/* SET MATERIAL FUNCTIONS */
/* arguments: Material structure and respective values */
void setMaterialDiffuse(Material *mat, GLfloat r, GLfloat g, GLfloat b, GLfloat a){
    if(mat == NULL) return;
    mat->diffuse[0] = r;
    mat->diffuse[1] = g;
    mat->diffuse[2] = b;
    mat->diffuse[3] = a;
}

void setMaterialSpecular(Material *mat, GLfloat r, GLfloat g, GLfloat b, GLfloat a){
    if(mat == NULL) return;
    mat->specular[0] = r;
    mat->specular[1] = g;
    mat->specular[2] = b;
    mat->specular[3] = a;
}

void setMaterialEmission(Material *mat, GLfloat r, GLfloat g, GLfloat b, GLfloat a){
    if(mat == NULL) return;
    mat->emission[0] = r;
    mat->emission[1] = g;
    mat->emission[2] = b;
    mat->emission[3] = a;
}

void setMaterialShininess(Material *mat, GLint shininess){
    if(mat == NULL) return;
    mat->shininess = shininess;
}
/* --------------------------- GETTERS & SETTERS ---------------------------- */

/* ------------------------------- RENDERING -------------------------------- */
/* USE MATERIAL */
/* arguments: Material structure */
void useMaterial(Material *mat){
    glEnable(GL_COLOR_MATERIAL);

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat->specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat->emission);
    glMateriali(GL_FRONT, GL_SHININESS, mat->shininess);
}
/* ------------------------------- RENDERING -------------------------------- */
