#include "../includes/glsl.h"

/* LOAD SOURCE */
/* arguments: source code filename */
/* return: string with the complete source code */
char *loadSource(char *fname){
    FILE *file = NULL;
    file = fopen(fname, "r");
    if(file == NULL){
        printf("Error loading \"%s\": file does not exist\n\n", fname);
        return NULL;
    }
    char *source = (char *) malloc(sizeof(char));
    char *buffer = (char *) malloc(sizeof(char));
    int cnt = 0;
    buffer[0] = ' ';

    while(!(feof(file))){
        fread(buffer, sizeof(char), 1, file);
        source[cnt] = buffer[0];
        cnt = cnt + 1;
        source = (char *) realloc(source, sizeof(char) * (cnt + 1));
    }
    source[cnt] = '\0';

    if(cnt == 0)
        free(source);

    free(buffer);
    fclose(file);
    return source;
}

/* SET SHADER SOURCE */
/* arguments: dest shader and source code */
void setShaderSource(GLuint shader, const char *source){
    glShaderSource(shader, 1, &source, NULL);
}

/* COMPILE SHADER */
/* arguments: shader type and filename */
/* return: compiled shader if success or SHADER_NULL if failed */
GLuint compileShader(GLuint type, char *fname){
    GLuint shader = glCreateShader(type);
    char *source = loadSource(fname);

    if(source == NULL){
        printf("Error loading shader \"%s\"\n\n", fname);
        return SHADER_NULL;
    }

    setShaderSource(shader, source);
    free(source);

    glCompileShader(shader);

    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(success == GL_FALSE){
        printf("Error compiling shader \"%s\":\n", fname);
        GLint logSize = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);

        char *errorLog = (char *) malloc(sizeof(char) * logSize);
        glGetShaderInfoLog(shader, logSize, &logSize, errorLog);

        printf("%s\n\n", errorLog);

        glDeleteShader(shader);
        return SHADER_NULL;
    }
    else{
        IF_DEBUG printf("Successfully compiled shader \"%s\"\n\n", fname);
        return shader;
    }
}

/* ----------------------------- MAIN FUNCTIONS ----------------------------- */
/* CREATE SHADER */
/* arguments: directory to vertex and fragment shader files */
/* return: Shader structure with both shaders and program attached */
Shader *createShader(char *vertex, char *fragment){
    if(vertex == NULL && fragment == NULL) return NULL;
    Shader *shader = (Shader *) malloc(sizeof(Shader));

    if(vertex != NULL)
        shader->vertexShader = compileShader(GL_VERTEX_SHADER, vertex);
    if(fragment != NULL)
        shader->fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragment);
    shader->program = glCreateProgram();

    if(shader->vertexShader != SHADER_NULL)
        glAttachShader(shader->program, shader->vertexShader);
    if(shader->vertexShader != SHADER_NULL)
        glAttachShader(shader->program, shader->fragmentShader);
    glLinkProgram(shader->program);

    return shader;
}

/* USE SHADER */
/* arguments: Shader structure */
void useShader(Shader *shader){
    glUseProgram(shader->program);
}

/* FREE SHADER */
/* arguments: Shader structure */
void freeShader(Shader *shader){
    if(shader == NULL) return;
    glDeleteShader(shader->vertexShader);
    glDeleteShader(shader->fragmentShader);
    glDeleteProgram(shader->program);
    free(shader);
}
/* ----------------------------- MAIN FUNCTIONS ----------------------------- */
