// Library de tuong tac voi X Serverxfix
#include <X11/Xlib.h>
#include <X11/extensions/shape.h>
#include <X11/extensions/Xfixes.h>

// Libray OpenGL de giup de dang cho viec ve tren cua so
#include <GL/gl.h>
#include <GL/glx.h>

#include <string.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
// Library de tuong tac voi IO input

#include "main.h"

#define DODAI_CUASO 800
#define DORONG_CUASO 600

typedef GLXContext(*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

int main(int argc, char **argv){
  Display *display;
  display = XOpenDisplay(NULL);
  int screen = DefaultScreen(display);

  Window cuaso_chinh;

  // Khoi tao boi canh cua X11 
  XGCValues thuoc_tinh;

	// Tao cua so
  XVisualInfo *thuoctinh_hoatanh;
	GLint        visual_attributes[5] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, None };

	thuoctinh_hoatanh = glXChooseVisual(display,screen, visual_attributes);

	XSetWindowAttributes thuoctinh_cuaso;
	thuoctinh_cuaso.border_pixel = BlackPixel(display, screen);
	thuoctinh_cuaso.background_pixel = WhitePixel(display, screen);
	thuoctinh_cuaso.override_redirect = True;
	thuoctinh_cuaso.colormap = XCreateColormap(display, RootWindow(display, screen), thuoctinh_hoatanh->visual, AllocNone);
	thuoctinh_cuaso.event_mask = ButtonPressMask|KeyPressMask|ExposureMask;
	cuaso_chinh = XCreateWindow(display, RootWindow(display, screen), 0, 0, DODAI_CUASO, DORONG_CUASO, 0, thuoctinh_hoatanh->depth, InputOutput, thuoctinh_hoatanh->visual, CWBackPixel | CWColormap | CWBorderPixel | CWEventMask, &thuoctinh_cuaso);
  
  // Hien thi cua so
  XClearWindow(display, cuaso_chinh);
	XMapRaised(display, cuaso_chinh);

  // Xu ly thao tac thoat cua so
	Atom atomWmDeleteWindow = XInternAtom(display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(display, cuaso_chinh, &atomWmDeleteWindow, 1);

  GLXContext boicanh_gl;
  boicanh_gl = glXCreateContext(display, thuoctinh_hoatanh,NULL,GL_TRUE);

	if (!glXIsDirect (display, boicanh_gl)) {
		std::cout << "Indirect GLX rendering context obtained\n";
	}
	else {
		std::cout << "Direct GLX rendering context obtained\n";
	}
  
  glXMakeCurrent(display, cuaso_chinh, boicanh_gl);

  XEvent hoat_dong;
  // Xu ly cac hoat dong o cua so
  char text[10];
  KeySym nut_an;
  int i;
  int hoan_thanh = 0;
	while (hoan_thanh == 0) {
    XNextEvent(display, &hoat_dong);
    switch(hoat_dong.type){
      case Expose: 
        if (hoat_dong.xexpose.count == 0){
          printf("hello");
        }
      break;
      case ButtonPress: 
        // Mouse Input
        // XFillRectangle(hoat_dong.xbutton.display, hoat_dong.xbutton.window, boi_canh, hoat_dong.xbutton.x, hoat_dong.xbutton.y, 10, 10);
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_QUADS);
            glColor3f(1.0f, 0.0f, 0.0f); // Red color
            glVertex2f(-0.5f, -0.5f);
            glVertex2f( 0.5f, -0.5f);
            glVertex2f( 0.5f,  0.5f);
            glVertex2f(-0.5f,  0.5f);
        glEnd();
        
        // Hoan tat viec render
        glXSwapBuffers(display, cuaso_chinh);
      break;
      case KeyPress:
        // Key Input
        i = XLookupString(&hoat_dong.xkey, text, 10, &nut_an, 0);
        if(i==1 && text[0]=='q') hoan_thanh = 1;
        break;
      case DestroyNotify:
      break;
    }
	}

  // Don dep OpenGL
	glXDestroyContext(display, boicanh_gl);
  
  // Don dep X11
  // XFreeGC(display, boi_canh);
  XDestroyWindow(display, cuaso_chinh);
  XCloseDisplay(display);

  return 0;
}


void doc_thongtin(int argc, char **argv){
  printf("argc: %d \n", argc);
  for (int i=1; i<argc; i++){
    if (!(strcmp(argv[i], "-c"))){
      if (i+1<argc){
        printf("arg cho color: %s \n", argv[i+1]);
      }
    }
  }
}


static bool isExtensionSupported(const char *extList, const char *extension) {
	return strstr(extList, extension) != 0;
}

void Render() {
	glColor3f(  1.0f,  0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
		glVertex3f( 0.0f, -1.0f, 0.0f);
		glVertex3f(-1.0f,  1.0f, 0.0f);
		glVertex3f( 1.0f,  1.0f, 0.0f);
	glEnd();

	glClear(GL_COLOR_BUFFER_BIT);
}
