#ifndef OBJ_H
#define OBJ_H

#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include "settings.h"

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
