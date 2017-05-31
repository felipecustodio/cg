#ifndef OBJ_H
#define OBJ_H

#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include "settings.h"

/* ------- OBJ LOADER by meist3r-ed ------- */
/* FEATURES: 								*/
/*	-> Loads vertices, texture coordinates,	*/
/* 		faces and UV maps					*/
/*	-> Draws models vertices, edges, faces 	*/
/* 		and texture-mapped faces			*/
/* NOTES: 									*/
/* 	-> Currently supports triangle-faced 	*/
/*		objects only						*/
/*	-> Does not load vertex or face normals	*/

typedef struct Obj{
	GLfloat *v;
	GLfloat *vt;
	GLint *f;
	GLint *ft;

	int vcount;
	int vtcount;
	int fcount;
	int ftcount;

	GLuint texture;
} Obj;

/* ----------- Object Handling ----------- */
Obj *loadObj(char *fname);
void freeObj(Obj *obj);
/* --------------------------------------- */

/* ---------- Getters & Setters ---------- */
void setObjTexture(Obj *obj, GLuint texture);
/* --------------------------------------- */

/* -------------- Rendering -------------- */
void drawObjVertices(Obj *obj);
void drawObjWireframe(Obj *obj);
void drawObjSolid(Obj *obj);
void drawObjTextured(Obj *obj);
/* --------------------------------------- */

#endif
