#ifndef MATERIAL_H
#define MATERIAL_H

#include <GL/glut.h>

typedef struct Material{
    GLfloat *diffuse;
    GLfloat *specular;
    GLfloat *emission;
    GLint shininess;
} Material;

/* ----------------------------- MAIN FUNCTIONS ----------------------------- */

/* --------------------------- STRUCTURE HANDLING --------------------------- */
/* CREATE MATERIAL */
/* return: blank Material */
Material *createMaterial();

/* FREE MATERIAL */
/* arguments: Material structure */
void freeMaterial(Material *mat);
/* --------------------------- STRUCTURE HANDLING --------------------------- */

/* --------------------------- GETTERS & SETTERS ---------------------------- */
/* SET MATERIAL FUNCTIONS */
/* arguments: Material structure and respective values */
void setMaterialDiffuse(Material *mat, GLfloat r, GLfloat g, GLfloat b, GLfloat a);
void setMaterialSpecular(Material *mat, GLfloat r, GLfloat g, GLfloat b, GLfloat a);
void setMaterialEmission(Material *mat, GLfloat r, GLfloat g, GLfloat b, GLfloat a);
void setMaterialShininess(Material *mat, GLint shininess);
/* --------------------------- GETTERS & SETTERS ---------------------------- */

/* ------------------------------- RENDERING -------------------------------- */
/* USE MATERIAL */
/* arguments: Material structure */
void useMaterial(Material *mat);
/* ------------------------------- RENDERING -------------------------------- */

/* ----------------------------- MAIN FUNCTIONS ----------------------------- */

#endif
