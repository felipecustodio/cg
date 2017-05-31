#include "../includes/obj.h"

void freeObj(Obj *obj){
    if(obj == NULL) return;
    if(obj->v) free(obj->v);
    if(obj->vt) free(obj->vt);
    if(obj->f) free(obj->f);
    free(obj);
}

void insertV(Obj *obj, GLfloat x, GLfloat y, GLfloat z){
    obj->v = (GLfloat *) realloc(obj->v, sizeof(GLfloat) * 3 * (obj->vcount + 1));
    obj->v[obj->vcount * 3] = x;
    obj->v[obj->vcount * 3 + 1] = y;
    obj->v[obj->vcount * 3 + 2] = z;
    obj->vcount += 1;
}

void insertVt(Obj *obj, GLfloat x, GLfloat y){
    obj->vt = (GLfloat *) realloc(obj->vt, sizeof(GLfloat) * 2 * (obj->vtcount + 1));
    obj->vt[obj->vtcount * 2] = x;
    obj->vt[obj->vtcount * 2 + 1] = y;
    obj->vtcount += 1;
}

void insertF(Obj *obj, GLfloat x, GLfloat y, GLfloat z){
    obj->f = (GLint *) realloc(obj->f, sizeof(GLint) * 3 * (obj->fcount + 1));
    obj->f[obj->fcount * 3] = x;
    obj->f[obj->fcount * 3 + 1] = y;
    obj->f[obj->fcount * 3 + 2] = z;
    obj->fcount += 1;
}

void insertFt(Obj *obj, GLfloat x, GLfloat y, GLfloat z){
    obj->ft = (GLint *) realloc(obj->ft, sizeof(GLint) * 3 * (obj->ftcount + 1));
    obj->ft[obj->ftcount * 3] = x;
    obj->ft[obj->ftcount * 3 + 1] = y;
    obj->ft[obj->ftcount * 3 + 2] = z;
    obj->ftcount += 1;
}

Obj *loadObj(char *fname){
    FILE *file = NULL;
    file = fopen(fname, "r");
    if(file == NULL){
        printf("Error loading \"%s\": file does not exist\n", fname);
        return NULL;
    }

    Obj *obj = (Obj *) malloc(sizeof(Obj));

    obj->v = (GLfloat *) malloc(sizeof(GLfloat) * 3);
    obj->vt = (GLfloat *) malloc(sizeof(GLfloat) * 2);
    obj->f = (GLint *) malloc(sizeof(GLint) * 3);
    obj->ft = (GLint *) malloc(sizeof(GLint) * 3);

    obj->vcount = 0;
    obj->vtcount = 0;
    obj->fcount = 0;
    obj->ftcount = 0;

    GLfloat vx = 0, vy = 0, vz = 0;
    GLfloat vtx = 0, vty = 0, vtz = 0;
    GLfloat vnx = 0, vny = 0, vnz = 0;

    int read = 0;
    char ch = ' ';
    long int offA = 0, offB = 0;

    /* READ VERTICES */
    while(!(feof(file))){
        read = fscanf(file, "%c %f %f %f", &ch, &vx, &vy, &vz);
        if(read == 4 && ch == 'v'){
            insertV(obj, vx, vy, vz);
        }
    }
    IF_DEBUG printf("vcount: %d\n", obj->vcount);

    if(obj->vcount == 0){
        free(obj->v);
        free(obj);
        return NULL;
    }

    fseek(file, 0, SEEK_SET);
    /* READ VERTICES TEXTURE COORDINATES */
    while(!(feof(file))){
        read = fscanf(file, "%ct %f %f", &ch, &vtx, &vty);
        if(read == 3 && ch == 'v'){
            insertVt(obj, vtx, vty);
        }
    }
    IF_DEBUG printf("vtcount: %d\n", obj->vtcount);

    if(obj->vtcount == 0)
        free(obj->vt);

    fseek(file, 0, SEEK_SET);
    /* READ FACES */
    while(!(feof(file))){
        offA = ftell(file);
        read = fscanf(file, "%c %f/%f/%f %f/%f/%f %f/%f/%f", &ch, &vx, &vtx, &vnx,
                                                &vy, &vty, &vny,
                                                &vz, &vtz, &vnz);
        offB = ftell(file);
        if(read == 10 && ch == 'f'){
            insertF(obj, vx, vy, vz);
            insertFt(obj, vtx, vty, vtz);
        }
        fseek(file, offA - offB, SEEK_CUR);
        offA = ftell(file);
        read = fscanf(file, "%c %f//%f %f//%f %f//%f", &ch, &vx, &vnx, &vy, &vny, &vz, &vnz);
        offB = ftell(file);
        if(read == 7 && ch == 'f'){
            insertF(obj, vx, vy, vz);
        }
        fseek(file, offA - offB, SEEK_CUR);
        offA = ftell(file);
        read = fscanf(file, "%c %f/%f %f/%f %f/%f", &ch, &vx, &vtx, &vy, &vty, &vz, &vtz);
        offB = ftell(file);
        if(read == 7 && ch == 'f'){
            insertF(obj, vx, vy, vz);
            insertFt(obj, vtx, vty, vtz);
        }
        fseek(file, offA - offB, SEEK_CUR);
        offA = ftell(file);
        read = fscanf(file, "%c %f %f %f", &ch, &vx, &vy, &vz);
        offB = ftell(file);
        if(read == 3 && ch == 'f'){
            insertF(obj, vx, vy, vz);
        }
    }
    IF_DEBUG printf("fcount: %d\n", obj->fcount);

    if(obj->fcount == 0){
        free(obj->f);
        free(obj->ft);
    }

    fclose(file);
    return obj;
}

void setObjTexture(Obj *obj, GLuint texture){
    if(obj == NULL) return;

    obj->texture = texture;
}

void drawObjVertices(Obj *obj){
    if(obj == NULL) return;

    glPointSize(5);

    int i = 0;
    for(i = 0; i < obj->vcount; i++){
        glBegin(GL_POINTS);
            glVertex3f(obj->v[i * 3], obj->v[i * 3 + 1], obj->v[i * 3 + 2]);
        glEnd();
    }
}

void drawObjWireframe(Obj *obj){
    if(obj == NULL) return;
    if(obj->f == NULL) return;

    glLineWidth(2);

    int i = 0, v1 = 0, v2 = 0, v3 = 0;
    for(i = 0; i < obj->fcount; i++){
        v1 = obj->f[i * 3] - 1;
        v2 = obj->f[i * 3 + 1] - 1;
        v3 = obj->f[i * 3 + 2] - 1;
        glBegin(GL_LINE_LOOP);
            glVertex3f(obj->v[v1 * 3], obj->v[v1 * 3 + 1], obj->v[v1 * 3 + 2]);
            glVertex3f(obj->v[v2 * 3], obj->v[v2 * 3 + 1], obj->v[v2 * 3 + 2]);
            glVertex3f(obj->v[v3 * 3], obj->v[v3 * 3 + 1], obj->v[v3 * 3 + 2]);
        glEnd();
    }
}

void drawObjSolid(Obj *obj){
    if(obj == NULL) return;
    if(obj->f == NULL) return;

    int i = 0, v1 = 0, v2 = 0, v3 = 0;
    for(i = 0; i < obj->fcount; i++){
        v1 = obj->f[i * 3] - 1;
        v2 = obj->f[i * 3 + 1] - 1;
        v3 = obj->f[i * 3 + 2] - 1;
        glBegin(GL_TRIANGLES);
            glVertex3f(obj->v[v1 * 3], obj->v[v1 * 3 + 1], obj->v[v1 * 3 + 2]);
            glVertex3f(obj->v[v2 * 3], obj->v[v2 * 3 + 1], obj->v[v2 * 3 + 2]);
            glVertex3f(obj->v[v3 * 3], obj->v[v3 * 3 + 1], obj->v[v3 * 3 + 2]);
        glEnd();
    }
}

void drawObjTextured(Obj *obj){
    if(obj == NULL) return;
    if(obj->vt == NULL) return;
    if(obj->f == NULL) return;
    if(obj->ft == NULL) return;

    glBindTexture(GL_TEXTURE_2D, obj->texture);
    glEnable(GL_TEXTURE_2D);

    int i = 0, v1 = 0, v2 = 0, v3 = 0, vt1 = 0, vt2 = 0, vt3 = 0;
    for(i = 0; i < obj->fcount; i++){
        v1 = obj->f[i * 3] - 1;
        v2 = obj->f[i * 3 + 1] - 1;
        v3 = obj->f[i * 3 + 2] - 1;
        vt1 = obj->ft[i * 3] - 1;
        vt2 = obj->ft[i * 3 + 1] - 1;
        vt3 = obj->ft[i * 3 + 2] - 1;
        glBegin(GL_TRIANGLES);
            glTexCoord2f(obj->vt[vt1 * 2], obj->vt[vt1 * 2 + 1]);
            glVertex3f(obj->v[v1 * 3], obj->v[v1 * 3 + 1], obj->v[v1 * 3 + 2]);
            glTexCoord2f(obj->vt[vt2 * 2], obj->vt[vt2 * 2 + 1]);
            glVertex3f(obj->v[v2 * 3], obj->v[v2 * 3 + 1], obj->v[v2 * 3 + 2]);
            glTexCoord2f(obj->vt[vt3 * 2], obj->vt[vt3 * 2 + 1]);
            glVertex3f(obj->v[v3 * 3], obj->v[v3 * 3 + 1], obj->v[v3 * 3 + 2]);
        glEnd();
    }

    glDisable(GL_TEXTURE_2D);
}
