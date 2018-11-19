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


#define _STDCALL_SUPPORTED
#include <cstdio>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <regex>
#include <glut_extensions.hpp>

#ifndef WIN32
#define APIENTRY
#endif

using namespace std;

void PrintString9x15(float x, float y, int justification, const char *format, ...);
void PrintBitmapStringJustified(float x, float y, int justification, void *font, const char *format, ...);
void PrintStrokeStringJustified(float x, float y, int justification, void *font, const char *format, ...);
void RenderOpenGL11TestScene();
void RenderCheckerboard();

struct Configuration
{
};

const char *g_windowTitle = "GLUT Template";
int g_displayMode = GLUT_DOUBLE | GLUT_STENCIL | GLUT_RGBA | GLUT_DEPTH;// | GLUT_MULTISAMPLE | GLUT_SRGB;// | GLUT_BORDERLESS;
int g_screenWidth = 1280;
int g_screenHeight = 720;
bool g_OpenGLCoreProfileOnly = false;
bool g_UseDebugProfile = true;
bool g_printDebugMessages = false;
double g_Fps = 0;
double g_aspectRatio = (double)g_screenWidth / (double)g_screenHeight;
int g_mouseDX = 0;
int g_mouseDY = 0;
int g_mouseX = 0;
int g_mouseY = 0;
int g_mouseButtons = 0;
int g_mouseInWindow = false;
int g_windowVisible = false;
int g_joystickButtonMask = 0;
int g_joystickX = 0;
int g_joystickY = 0;
int g_joystickZ = 0;
int g_joystickPollInterval = 16;
int g_timer1millis = 0;
int g_timer2millis = 0;
int g_timer3millis = 0;
int g_timer4millis = 0;
int g_timer1value = 0;
int g_timer2value = 0;
int g_timer3value = 0;
int g_timer4value = 0;
int g_frameCount = 0;
bool g_DisableScreensaver = true;
bool g_willResetErrorCountAfterFrame = false;
int g_errorCount = 0;
double g_updateInterval = 0.01666667f;
double g_renderInterval = 0.01666667f;
double g_Fov = 45.0;
double g_zNear = 0.01;
double g_zFar = 100.0;
int g_keyMap[256] = { 0 };
int g_specialKeyMap[256] = { 0 };
map<string, bool> g_htmlkeys;
vector<string> g_args;

double g_distance = -10.0;
double xrot = 0.0;
double yrot = 0.0;

void APIENTRY glutTemplateDebugFunc(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const GLvoid* userParam);

void ParseCommandLine();
void InitMenu();
void OnInit();
void OnKill();
void OnUpdate(double deltaTime);
void OnRender();
void OnRenderOverlay();

void OnMouseEnter();
void OnMouseLeave();

void Set2DViewport();
void Set3DViewport();

void InitGLUTTemplate(int argc, char **argv);

int main(int argc, char **argv)
{
	bool showVersion = false;
	for (int i = 0; i < argc; i++) {
		string option = argv[i];
		if (option == "-v" || option == "--version")
		{
			showVersion = true;
		}
		if (option == "-g" || option == "--debug")
		{
			g_printDebugMessages = true;
		}
	}

	if (showVersion)
	{
		cout << "GLUT Template by Jonathan Metzgar\nCopyright (C) 2017 Jonathan Metzgar\n\n";
	}

	InitGLUTTemplate(argc, argv);
	ParseCommandLine();
	InitMenu();
	OnInit();
	glutMainLoop();
	OnKill();
	
	return 0;
}


// ParseCommandLine()
// This function is called prior to the OnInit() initialization call of the
// application.
void ParseCommandLine()
{
	for (auto arg = g_args.begin(); arg != g_args.end(); arg++)
	{
		// do something with the arguments...
	}
}


// InitMenu()
void InitMenu()
{
	// Initialize menu entries here
}


// OnInit()
// This function is called prior to the main loop of the application.
// OpenGL is already initialized prior to this call.
//
void OnInit()
{
	glewInit();

#ifdef USE_MULTISAMPLING
	glEnable(GL_MULTISAMPLE);
#endif
	glDebugMessageCallback((GLDEBUGPROC)glutTemplateDebugFunc, NULL);
	glEnable(GL_DEBUG_OUTPUT);

	const char *versionString = (char *)glGetString(GL_VERSION);
	const char *vendorString = (char *)glGetString(GL_VENDOR);
	const char *rendererString = (char *)glGetString(GL_RENDERER);
	const char *extensionsString = (char *)glGetString(GL_EXTENSIONS);

	bool showglextension = false;
	for (auto arg = g_args.begin(); arg != g_args.end(); arg++) {
		if (*arg == "--glextensions") {
			showglextension = true;
		}
	}

	cout << "GL_RENDERER: " << rendererString << endl;
	cout << "GL_VERSION:  " << versionString << endl;
	cout << "GL_VENDOR:   " << vendorString << endl;
	if (showglextension)
	{
		cout << "GL_EXTENSIONS: " << extensionsString << endl;
	}

	GLint maxUniformBufferBindings;

	glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &maxUniformBufferBindings);
	cout << "GL_MAX_UNIFORM_BUFFER_BINDINGS: "<< maxUniformBufferBindings << endl;

	glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT_ARB, GL_NICEST);
#ifdef GL_FRAGMENT_SHADER_DERIVATIVE_HINT_OES
	glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT_OES, GL_NICEST);
#endif
}


// OnKill()
// This gets called after the GLUT main loop finishes
//
void OnKill()
{

}


// OnUpdate(deltaTime)
// This function is called during the main loop of the application.
//
void OnUpdate(double deltaTime)
{
	xrot += 35 * deltaTime;
	yrot += 35 * deltaTime;

#ifdef WIN32
	if (g_DisableScreensaver)
	{
		INPUT input;
		ZeroMemory(&input, sizeof(INPUT));
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_MOVE;
		SendInput(1, &input, sizeof(INPUT));
	}
	Sleep(0);
#elif _POSIX_VERSION
	usleep(0);
#endif

	glutPostRedisplay();
}


void OnRender()
{
	if (!g_OpenGLCoreProfileOnly)
	{
		RenderOpenGL11TestScene();
	}
}


void OnRenderOverlay()
{
	glutSetErrorMessage(__FILE__, __LINE__, "%s", __FUNCTION__);
}


void OnWindowVisible()
{

}


void OnWindowHidden()
{
}


void OnMouseEnter()
{
}


void OnMouseLeave()
{

}


void OnKeyDown(const string & key, int keymod)
{
	// Use g_htmlkeys["keyname"]
	// Special Keys: F1, F2, ..., F12, Ctrl, Alt, Shift, Enter, 
	cout << key << " pressed" << endl;
}


void OnKeyUp(const string & key, int keymod)
{
	// Use g_htmlkeys["keyname"]

	cout << key << " released" << endl;
	if (key == "Escape")
	{
		glutLeaveMainLoop();
	}
}


void OnMouseMove(int x, int y, int dx, int dy)
{
}


void OnMouseButtonDown(int button)
{
}


void OnMouseButtonUp(int button)
{
}


void Set2DViewport()
{
	if (!g_OpenGLCoreProfileOnly)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, g_screenWidth, g_screenHeight, 0);
		glMatrixMode(GL_MODELVIEW);
	}
}


void Set3DViewport()
{
	if (!g_OpenGLCoreProfileOnly)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(g_Fov, g_aspectRatio, g_zNear, g_zFar);
		glMatrixMode(GL_MODELVIEW);
	}
}



void display();
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void keyboardup(unsigned char key, int x, int y);
void special(int key, int x, int y);
void specialup(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void passive(int x, int y);
void entry(int state);
void visibility(int state);
void idle();
void timer1(int value);
void timer2(int value);
void timer3(int value);
void timer4(int value);
void menu(int state);
void menustatus(int state, int x, int y);
void windowstatus(int state);
void joystick(unsigned int buttonMask, int x, int y, int z);


void InitGLUTTemplate(int argc, char **argv)
{

#ifdef WIN32
	SetProcessDPIAware();
#endif

	for (int i = 0; i < argc; i++)
	{
		g_args.push_back(argv[i]);
	}

	glutInit(&argc, argv);
#ifdef USE_MULTISAMPLING
	glutSetOption(GLUT_MULTISAMPLE, 4);
#endif
	glutInitDisplayMode(g_displayMode);
	glutInitWindowSize(g_screenWidth, g_screenHeight);
	if (g_UseDebugProfile)
	{
		glutInitContextFlags(GLUT_DEBUG);
	}
	if (g_OpenGLCoreProfileOnly)
	{
		glutInitContextProfile(GLUT_CORE_PROFILE);
	}
	else
	{
		glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	}

	glutCreateWindow(g_windowTitle);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardup);
	glutSpecialFunc(special);
	glutSpecialUpFunc(specialup);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(passive);
	glutEntryFunc(entry);
	glutIdleFunc(idle);
	if (g_timer1millis != 0) glutTimerFunc(g_timer1millis, timer1, g_timer1value);
	if (g_timer2millis != 0) glutTimerFunc(g_timer2millis, timer2, g_timer2value);
	if (g_timer3millis != 0) glutTimerFunc(g_timer3millis, timer3, g_timer3value);
	if (g_timer4millis != 0) glutTimerFunc(g_timer4millis, timer4, g_timer4value);
	glutMenuStateFunc(menu);
	glutMenuStatusFunc(menustatus);
	// glutVisibilityFunc(visibility); use only if glutWindowStatusFunc is not available
	glutWindowStatusFunc(windowstatus);
	glutJoystickFunc(joystick, g_joystickPollInterval);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
}


void display()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glViewport(0, 0, g_screenWidth, g_screenHeight);
	glLoadIdentity();
	Set3DViewport();
	OnRender();

	glViewport(0, 0, g_screenWidth, g_screenHeight);
	glLoadIdentity();
	Set2DViewport();
	OnRenderOverlay();

	if (g_displayMode & GLUT_DOUBLE)
	{
		glutSwapBuffers();
	}
	g_frameCount++;
	if (g_willResetErrorCountAfterFrame)
	{
		g_errorCount = 0;
	}
}


void reshape(int width, int height)
{
	g_aspectRatio = (double)width / (double)height;
	g_screenWidth = width;
	g_screenHeight = height;
	glViewport(0, 0, width, height);
}


void keyboard(unsigned char key, int x, int y)
{
	string keyName = GT::KeyToHTML5Name(key);
	g_keyMap[key] = 1;
	g_htmlkeys[keyName] = true;

	OnKeyDown(keyName, glutGetModifiers());
}


void keyboardup(unsigned char key, int x, int y)
{
	string keyName = GT::KeyToHTML5Name(key);
	g_keyMap[key] = 0;
	g_htmlkeys[keyName] = false;

	OnKeyUp(keyName, glutGetModifiers());
}


void special(int key, int x, int y)
{
	string keyName = GT::SpecialKeyToHTML5Name(key);
	g_specialKeyMap[key] = 1;
	g_htmlkeys[keyName] = true;

	OnKeyDown(keyName, glutGetModifiers());
}


void specialup(int key, int x, int y)
{
	string keyName = GT::SpecialKeyToHTML5Name(key);
	g_specialKeyMap[key] = 0;
	g_htmlkeys[keyName] = false;

	OnKeyUp(keyName, glutGetModifiers());
}


void mouse(int button, int state, int x, int y)
{
	int buttonMask = 1 << button;
	if (state == GLUT_UP)
	{
		g_mouseButtons &= ~buttonMask;
	}
	else
	{
		g_mouseButtons |= buttonMask;
	}
	g_mouseDX = x - g_mouseX;
	g_mouseDY = x - g_mouseY;
	g_mouseX = x;
	g_mouseY = y;

	OnMouseMove(g_mouseX, g_mouseY, g_mouseDX, g_mouseDY);
	if (state == GLUT_DOWN)
	{
		OnMouseButtonDown(button);
	}
	else if (state == GLUT_UP)
	{
		OnMouseButtonUp(button);
	}
}


void motion(int x, int y)
{
	g_mouseDX = x - g_mouseX;
	g_mouseDY = x - g_mouseY;
	g_mouseX = x;
	g_mouseY = y;
}


void passive(int x, int y)
{
	g_mouseDX = x - g_mouseX;
	g_mouseDY = x - g_mouseY;
	g_mouseX = x;
	g_mouseY = y;
}


void entry(int state)
{
	if (state == GLUT_ENTERED)
	{
		g_mouseInWindow = true;
		OnMouseEnter();
	}
	else
	{
		g_mouseInWindow = false;
		OnMouseLeave();
	}
}


void visibility(int state)
{
	if (state == GLUT_VISIBLE)
	{
		g_windowVisible = true;
		OnWindowVisible();
	}
	else if (state == GLUT_NOT_VISIBLE)
	{
		g_windowVisible = false;
		OnWindowHidden();
	}
}


void idle()
{
	static double time0 = 0, time1 = 0;
	static double renderdt = 0;
	static double updatedt = 0;
	static int fps_count = 0;
	static double fps0 = 0, fps1 = 0;

	time0 = time1;
	time1 = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	renderdt += time1 - time0;
	updatedt += time1 - time0;

	if (fps_count == 20)
	{
		fps0 = fps1;
		fps1 = time1;
		fps_count = 0;
	}

	g_Fps = 20.0 / (fps1 - fps0);

	if (updatedt > g_updateInterval)
	{
		OnUpdate(updatedt);
		updatedt = 0;
	}

	if (renderdt > g_renderInterval)
	{
		fps_count++;
		glutPostRedisplay();
		renderdt = 0;
	}
}


void timer1(int value)
{
}


void timer2(int value)
{
}


void timer3(int value)
{
}


void timer4(int value)
{
}


void menu(int state)
{
}


void menustatus(int state, int x, int y)
{
}


void windowstatus(int state)
{
	switch (state)
	{
	case GLUT_HIDDEN:
	case GLUT_FULLY_COVERED:
		g_windowVisible = false;
		OnWindowHidden();
		break;
	case GLUT_PARTIALLY_RETAINED:
	case GLUT_FULLY_RETAINED:
		g_windowVisible = true;
		OnWindowVisible();
		break;
	}
}


void joystick(unsigned int buttonMask, int x, int y, int z)
{
	g_joystickButtonMask = buttonMask;
	g_joystickX = x;
	g_joystickY = y;
	g_joystickZ = z;
}


// -- EXTRA FUNCTIONS ------------------------------------------------


void PrintString9x15(float x, float y, int justification, const char *format, ...)
{
	char buffer[256];

	va_list va;
	va_start(va, format);
#ifdef __STDC_SECURE_LIB__
	vsnprintf_s(buffer, sizeof(buffer), sizeof(buffer) - 1, format, va);
#else
	vsnprintf(buffer, 100, format, va);
#endif
	va_end(va);

	PrintBitmapStringJustified(x, y, justification, GLUT_BITMAP_9_BY_15, buffer);
}


void PrintBitmapStringJustified(float x, float y, int justification, void *font, const char *format, ...)
{
	char buffer[256];
	int pixelWidthOfString;

	va_list va;
	va_start(va, format);
#ifdef __STDC_SECURE_LIB__
	vsnprintf_s(buffer, sizeof(buffer), sizeof(buffer) - 1, format, va);
#else
	vsnprintf(buffer, 100, format, va);
#endif
	va_end(va);

	pixelWidthOfString = glutBitmapLength(font, (const unsigned char *)buffer);

	if (justification == LEFT)
	{
		// left justified
		glRasterPos2f(x, y);
	}
	else if (justification == RIGHT)
	{
		// right justified
		glRasterPos2f((GLfloat)(g_screenWidth - pixelWidthOfString), (GLfloat)y);
	}
	else if (justification == CENTER)
	{
		glRasterPos2f((GLfloat)(g_screenWidth - pixelWidthOfString) / 2.0f, (GLfloat)y);
	}

	glutBitmapString(font, buffer);
}


void PrintStrokeStringJustified(float x, float y, int justification, void *font, const char *format, ...)
{
	char buffer[2048];
	int pixelWidthOfString;

	va_list va;
	va_start(va, format);
#ifdef __STDC_SECURE_LIB__
	vsnprintf_s(buffer, sizeof(buffer), 2048, format, va);
#else
	vsnprintf(buffer, 2048, format, va);
#endif
	va_end(va);

	pixelWidthOfString = glutStrokeLength(font, (const unsigned char *)buffer);

	if (justification == LEFT)
	{
		// left justified
		glRasterPos2f(x, y);
	}
	else if (justification == RIGHT)
	{
		// right justified
		glRasterPos2f((float)(g_screenWidth - pixelWidthOfString), (float)y);
	}
	else if (justification == CENTER)
	{
		glRasterPos2f((float)(g_screenWidth - pixelWidthOfString) / 2.0f, (float)y);
	}

	glutStrokeString(font, buffer);
}


void APIENTRY glutTemplateDebugFunc(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const GLvoid* userParam)
{
	if (!g_printDebugMessages)
		return;
	if (id == 131185) return;

	ostringstream ostr;
	ostr << "(" << g_CurrentDebugMessage << ") ";
	ostr << "frame: " << g_frameCount;
	ostr << " error: " << g_errorCount++;
	ostr << " id: " << id;

	ostr << " severity: ";
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_LOW: ostr << "LOW"; break;
	case GL_DEBUG_SEVERITY_MEDIUM: ostr << "MEDIUM"; break;
	case GL_DEBUG_SEVERITY_HIGH: ostr << "HIGH"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: ostr << "NOTIFICATION"; break;
	default: ostr << severity; break;
	}

	ostr << " source: ";
	switch (source)
	{
	case GL_DEBUG_SOURCE_API: ostr << "API"; break;
	case GL_DEBUG_SOURCE_APPLICATION: ostr << "APPLICATION"; break;
	case GL_DEBUG_SOURCE_OTHER: ostr << "OTHER"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: ostr << "SHADER COMPILER"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY: ostr << "THIRD PARTY"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM: ostr << "WINDOW SYSTEM"; break;
	default: ostr << type;  break;
	}

	ostr << " type: ";
	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR: ostr << "ERROR"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: ostr << "DEPRECATED BEHAVIOR"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: ostr << "UNDEFINED BEHAVIOR"; break;
	case GL_DEBUG_TYPE_PORTABILITY: ostr << "PORTABILITY"; break;
	case GL_DEBUG_TYPE_PERFORMANCE: ostr << "PERFORMANCE"; break;
	case GL_DEBUG_TYPE_MARKER: ostr << "MARKER"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP: ostr << "PUSH GROUP"; break;
	case GL_DEBUG_TYPE_POP_GROUP: ostr << "POP GROUP"; break;
	case GL_DEBUG_TYPE_OTHER: ostr << "OTHER"; break;
	default: ostr << type; break;
	}

	cerr << ostr.str() << endl;
	string m = message;
	istringstream istr(m);
	string line;
	while (getline(istr, line))
	{
		cerr << "> " << line << endl;
	}
}


void RenderCheckerboard()
{
	for (int i = -4; i < 4; i++)
	{
		for (int j = -4; j < 4; j++)
		{
			glNormal3f(0, 1, 0);
			if ((j % 2 && i % 2) || j == i || (!(j % 2) && !(i % 2)))
				glColor3f(.7f, .7f, .7f);
			else
				glColor3f(.3f, .3f, .3f);
			glRectf(2.0f * i, 2.0f * j, 2.0f * (i + 1), 2.0f * (j + 1));
		}
	}
}


void RenderOpenGL11TestScene()
{
	glColor3f(0.8f, 0.3f, 0.2f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	glColor3f(0, 0, 1);
	glPushMatrix();
	glLoadIdentity();

	// Camera Matrix
	glTranslatef(0, 0, -20 - g_distance);
	glRotatef(yrot, 0.0, 1.0, 0.0);
	glutSolidTeapot(1.0);
	glPopMatrix();

	glColor3f(1, 0, 0);
	glLoadIdentity();
	glTranslatef(0, -4, -20 - g_distance);
	//glLoadMatrixf(invCamera.m);
	glTranslatef(0, -4, 0);
	glRotatef(-90, 1, 0, 0);
	glRectf(-1, -1, 1, 1);

	RenderCheckerboard();

	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
}