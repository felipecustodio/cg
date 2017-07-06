#ifndef OBJ_H
#define OBJ_H

#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include "material.h"
#include "settings.h"

/* Wavefront .OBJ Loader & API :3 */
/* Check functions headers for usage */

typedef struct Obj{		// Structure for OBJ files (normals not included)
	GLfloat *v;			// V = object vertices
	GLfloat *vt;		// Vt = object texture coordinates (UVMAP)
	GLfloat *vn;		// Vn = object normal coordinates (NORMALMAP)
	GLint *f;			// F = face vertices
	GLint *ft;			// Ft = face texture mapping
	GLint *fn;			// Ft = face texture mapping

	int vcount;			// V count
	int vtcount;		// Vt count
	int vncount;		// Vn count
	int fcount;			// F count
	int ftcount;		// Ft count
	int fncount;		// Ft count

	GLuint texture;		// Object texture
	Material *material;	// Object material
} Obj;

/* ----------------------------- MAIN FUNCTIONS ----------------------------- */

/* --------------------------- STRUCTURE HANDLING --------------------------- */
/* LOAD OBJ */
/* arguments: directory to object file */
/* return: Obj structure with loaded vectices or NULL */
Obj *loadObj(char *fname);

/* FREE OBJ */
/* arguments: Obj structure */
void freeObj(Obj *obj);
/* --------------------------- STRUCTURE HANDLING --------------------------- */

/* --------------------------- GETTERS & SETTERS ---------------------------- */
/* SET OBJ TEXTURE */
/* arguments: Obj structure and loaded texture */
void setObjTexture(Obj *obj, GLuint texture);

/* SET OBJ MATERIAL */
/* arguments: Obj structure and loaded material */
void setObjMaterial(Obj *obj, Material *material);
/* --------------------------- GETTERS & SETTERS ---------------------------- */

/* ------------------------------- RENDERING -------------------------------- */
/* DRAW OBJ FUNCTIONS */
/* arguments: Obj structure */
void drawObjVertices(Obj *obj);
void drawObjWireframe(Obj *obj);
void drawObjSolid(Obj *obj);
void drawObjTextured(Obj *obj);
/* ------------------------------- RENDERING -------------------------------- */

/* ----------------------------- MAIN FUNCTIONS ----------------------------- */

#endif
