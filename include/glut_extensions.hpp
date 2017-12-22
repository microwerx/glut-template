// GLUT Template
//
// Copyright(c) 2017 Jonathan Metzgar
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef FLUXIONS_GLUT_EXTENSIONS_HPP
#define FLUXIONS_GLUT_EXTENSIONS_HPP

#define GLEW_STATIC
#include <GL/glew.h>
#ifdef WIN32
#include <GL/wglew.h>
#endif
#include <GL/freeglut.h>
#include <string>

GLenum glutGetBaseType(GLenum type);
GLint glutGetTypeComponents(GLenum type);
GLsizei glutGetSizeOfType(GLenum type);
GLsizei glutGetSizeOfBaseType(GLenum type);

extern GLint g_MaxCombinedTextureUnits;
extern std::string g_CurrentDebugMessage;

void glutSetErrorMessage(const char *filename, int line, const char *format, ...);
void glutSetDefaultErrorMessage();
GLint glutSetActiveTexture(GLint unit);
bool glutBindDefaultTextureAndSampler(GLenum target);
bool glutBindTextureAndSampler(GLint unit, GLenum target, GLuint texture, GLuint sampler);
bool glutBindTexture(GLint unit, GLenum target, GLuint texture);
bool glutBindSampler(GLint unit, GLuint sampler);
bool glutDebugBindTexture(GLenum target, GLuint texture);

void glutBitmapString(void *font, const char *string);
void glutStrokeString(void *font, const char *string);

enum GLUT_JUSTIFICATION {
	LEFT,
	RIGHT,
	CENTER
};

// justification: LEFT = 0, RIGHT = 1, CENTER = 2
void glutPrintString9x15(double x, double y, double screenWidth, int justification, const char *format, ...);

// justification: LEFT = 0, RIGHT = 1, CENTER = 2
void glutPrintBitmapStringJustified(double x, double y, double screenWidth, int justification, void *font, const char *format, ...);
// justification: LEFT = 0, RIGHT = 1, CENTER = 2
void glutPrintStrokeStringJustified(double x, double y, double screenWidth, int justification, void *font, const char *format, ...);

void glutThreeAxis(float length);
void glutSixAxis(float length);
void glutWireFrustumf(float *m, float scale = 0.1f);
void glutWireFrustumd(double *m);
void glutCamera(double fov, float r, float g, float b, float zfar, float *inverseCameraMatrix, float *projectionMatrix);

void glutTestLitSolidTeapotScene(double fovy, double aspect);

void glutEnvironmentCube(GLfloat size, GLuint cubeMapTexId);
void glutCubeMap(GLdouble x, GLdouble y, GLdouble z, GLdouble size, GLint vloc, GLint tloc);
void glutUnwrappedCubeMap(GLuint x, GLuint y, GLuint size, GLint vloc, GLint tloc);


namespace GT
{
	int HTML5NameToKey(const std::string & key);
	const char *KeyToHTML5Name(char c);
	const char *SpecialKeyToHTML5Name(int key);

} // namespace GT

#endif
