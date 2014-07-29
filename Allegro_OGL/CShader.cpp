#include "CShader.h"


CShader::CShader()
{
    bLoaded = false;
}


CShader::~CShader()
{
}


bool CShader::loadShader(std::string sFile, int a_iType)
{
    FILE *fp;
    fopen_s(&fp, sFile.c_str(), "rt");
    if (!fp)
        return false;

    //Get all lines from a file

    std::vector<std::string> sLines;
    char sLine[255];
    while (fgets(sLine, 255, fp))
        sLines.push_back(sLine);
    fclose(fp);

    const char** sProgram = new const char*[ESZ(sLines)];
    FOR(i, ESZ(sLines))
        sProgram[i] = sLines[i].c_str();

    uiShader = glCreateShader(a_iType);

    glShaderSource(uiShader, ESZ(sLines), sProgram, NULL);
    glCompileShader(uiShader);

    delete [] sProgram;

    int iCompilationStatus;
    glGetShaderiv(uiShader, GL_COMPILE_STATUS, &iCompilationStatus);

    if (iCompilationStatus == GL_FALSE)
        return false;
    iType = a_iType;
    bLoaded = true;

    return true;
}


void CShader::deleteShader()
{
    if (!isLoaded())
        return;

    bLoaded = false;
    glDeleteShader(uiShader);
}


bool CShader::isLoaded()
{
    return bLoaded;
}


UINT CShader::getShaderID()
{
    return uiShader;
}




CShaderProgram::CShaderProgram()
{
    bLinked = false;
}

void CShaderProgram::CreateProgram()
{
    uiProgram = glCreateProgram();
}

/*-----------------------------------------------

Name:	AddShaderToProgram

Params:	sShader - shader to add

Result:	Adds a shader (like source file) to
a program, but only compiled one.

/*---------------------------------------------*/

bool CShaderProgram::AddShaderToProgram(CShader* shShader)
{
    if (!shShader->isLoaded())return false;

    glAttachShader(uiProgram, shShader->getShaderID());

    return true;
}

/*-----------------------------------------------

Name:	LinkProgram

Params:	none

Result:	Performs final linkage of OpenGL program.

/*---------------------------------------------*/

bool CShaderProgram::LinkProgram()
{
    glLinkProgram(uiProgram);
    int iLinkStatus;
    glGetProgramiv(uiProgram, GL_LINK_STATUS, &iLinkStatus);
    bLinked = iLinkStatus == GL_TRUE;
    return bLinked;
}

/*-----------------------------------------------

Name:	DeleteProgram

Params:	none

Result:	Deletes program and frees memory on GPU.

/*---------------------------------------------*/

void CShaderProgram::DeleteProgram()
{
    if (!bLinked)return;
    bLinked = false;
    glDeleteProgram(uiProgram);
}

/*-----------------------------------------------

Name:	UseProgram

Params:	none

Result:	Tells OpenGL to use this program.

/*---------------------------------------------*/

void CShaderProgram::UseProgram()
{
    if (bLinked)glUseProgram(uiProgram);
}