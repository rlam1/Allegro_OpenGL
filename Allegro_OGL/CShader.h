#pragma once

#include "common_header.h"

// Wraps shader loading and compiling
class CShader {
public:
    CShader();
    ~CShader();

    bool loadShader(std::string sFile, int a_iType);
    void deleteShader();

    bool isLoaded();
    UINT getShaderID();
private:
    // ID of shader
    UINT uiShader;
    // GL_VERTEX_SHADER, GL_FRAGMENT_SHADER...
    int iType;
    // Whether shader was loaded and compiled
    bool bLoaded;
};


// Wraps shader program and makes its usage easy
class CShaderProgram {
public:
    void CreateProgram();
    void DeleteProgram();

    bool AddShaderToProgram(CShader* shShader);
    bool LinkProgram();

    void UseProgram();

    UINT GetProgramID();

    CShaderProgram();

private:
    UINT uiProgram; // ID of program
    bool bLinked; // Whether program was linked and is ready to use
};