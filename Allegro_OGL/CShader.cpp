#include "CShader.h"


CShader::CShader()
{
}


CShader::~CShader()
{
}


bool CShader::loadShader(std::string sFile, int a_iType)
{
    FILE* fp = fopen(sFile.c_str(), "rt");
    if (!fp)
        return false;

    //Get all lines from a file

    vector<std::string> sLines;
    char sLine[255];
    while (fgets(sLine, 255, fp))
        sLines.push_back(sLine);
    fclose(fp);

    const char** sProgram = new const char*[ESZ(sLines)];

    return true;
}


void CShader::deleteShader()
{
}


bool CShader::isLoaded()
{
    return false;
}


UINT CShader::getShaderID()
{
    return 0;
}


// ID of shader
UINT CShader::uiShader()
{
    return 0;
}


// GL_VERTEX_SHADER, GL_FRAGMENT_SHADER...
int CShader::iType()
{
    return 0;
}


// Whether shader was loaded and compiled
bool CShader::bLoaded()
{
    return false;
}
