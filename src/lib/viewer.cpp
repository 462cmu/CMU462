#include "viewer.h"

#include <stdio.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

#include "glew.h"

#include "console.h"

using namespace std;
using namespace chrono;

#define DEFAULT_W 960
#define DEFAULT_H 640

namespace CSD462 {

// HDPI display
bool Viewer::HDPI;

// framecount & related timeers
int Viewer::framecount;
time_point<system_clock> Viewer::sys_last; 
time_point<system_clock> Viewer::sys_curr; 

// draw toggles
bool Viewer::showInfo = true;
bool Viewer::showZoom = false;

// window properties
GLFWwindow* Viewer::window;
size_t Viewer::buffer_w;
size_t Viewer::buffer_h;

// cursor properties
GLFWcursor* Viewer::cursor;
double Viewer::cursorX;
double Viewer::cursorY;

// user space renderer
Renderer* Viewer::renderer; 

// on-screen display
OSDText* Viewer::osd_text;
int Viewer::line_id_renderer;
int Viewer::line_id_framerate;

Viewer::Viewer() {

}

Viewer::~Viewer() {

  glfwDestroyWindow(window);
  glfwTerminate();
  
  // free resources
  delete renderer;
  delete osd_text;
}


void Viewer::init() {

  // initialize glfw
  glfwSetErrorCallback( err_callback );
  if( !glfwInit() ) {
    out_err("Error: could not initialize GLFW!");
    exit( 1 );
  }

  // create window
  string title = renderer ? "CSD462: " + renderer->name() : "CSD462";
  window = glfwCreateWindow( DEFAULT_W, DEFAULT_H, title.c_str(), NULL, NULL );
  if (!window) {
    out_err("Error: could not create window!");
    glfwTerminate();
    exit( 1 );
  }

  // set context
  glfwMakeContextCurrent( window );
  glfwSwapInterval(1);

  // framebuffer event callbacks
  glfwSetFramebufferSizeCallback( window, resize_callback );
  
  // key event callbacks
  glfwSetKeyCallback( window, key_callback );
  
  // cursor event callbacks
  glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);
  glfwSetCursorPosCallback( window, cursor_callback );

  // wheel event callbacks
  glfwSetScrollCallback(window, scroll_callback);  
  
  // initialize glew
  if (glewInit() != GLEW_OK) {
    out_err("Error: could not initialize GLEW!");
    glfwTerminate();
    exit( 1 );
  }

  // enable alpha blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // initialize status OSD
  osd_text = new OSDText();
  if (osd_text->init() < 0) {
    out_err("Error: could not initialize on-screen display!");
    exit( 1 );
  }
  
  // initialize renderer if already set
  if (renderer) renderer->init();

  // resize components to current window size, get DPI
  resize_callback( window, DEFAULT_W, DEFAULT_H );
  if( buffer_w > DEFAULT_W ) HDPI = true;

  // add lines for renderer and fps
  line_id_renderer  = osd_text->add_line(-0.95,  0.90, "Renderer", 
                                          18, Color(0.15, 0.5, 0.15));
  line_id_framerate = osd_text->add_line(-0.98, -0.96, "Framerate", 
                                          14, Color(0.15, 0.5, 0.15));

}

void Viewer::start() {

  // start timer
  sys_last = system_clock::now();

  // run update loop
  while( !glfwWindowShouldClose( window ) ) {  
    update();
  }
}

void Viewer::set_renderer(Renderer *renderer) {
  this->renderer = renderer;
}

void Viewer::update() {
  
  // clear frame
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // run user renderer
  if (renderer) {
    renderer->render();
  }

  // draw info
  if( showInfo ) {
    drawInfo();        
  } 

  // swap buffers
  glfwSwapBuffers(window); 

  // poll events
  glfwPollEvents();
}


void Viewer::drawInfo() {

  // compute timers - fps is update every second
  sys_curr = system_clock::now();
  double elapsed = ((duration<double>) (sys_curr - sys_last)).count();
  if (elapsed >= 1.0f) {

    // update framecount OSD
    Color c = framecount < 20 ? Color(1.0, 0.35, 0.35) : Color(0.15, 0.5, 0.15);
    osd_text->set_color(line_id_framerate, c);
    string framerate_info = "Framerate: " + to_string(framecount) + " fps";
    osd_text->set_text(line_id_framerate, framerate_info);

    // reset timer and counter
    framecount = 0;
    sys_last = sys_curr; 

  } else {

    // increment framecount
    framecount++;
  
  }

  // udpate renderer OSD
  // TODO: This is done on every update and it shouldn't be!
  // The viewer should only update when the renderer needs to
  // update the info text. 
  if (renderer) {
    string renderer_info = renderer->info();
    osd_text->set_text(line_id_renderer, renderer_info);
  } else {
    string renderer_info = "No input renderer";
    osd_text->set_text(line_id_renderer, renderer_info);
  }

  // render OSD
  osd_text->render();

}

void Viewer::err_callback( int error, const char* description ) {
    out_err( "GLFW Error: " << description );
}

void Viewer::key_callback( GLFWwindow* window, 
                           int key, int scancode, int action, int mods ) {
  if( action == GLFW_PRESS ) {
    if( key == GLFW_KEY_ESCAPE ) { 
      glfwSetWindowShouldClose( window, true ); 
    } else if( key == GLFW_KEY_GRAVE_ACCENT ) { 
      showInfo = !showInfo; 
    } else {
      renderer->key_event(key);
    }
  }
}

void Viewer::resize_callback( GLFWwindow* window, int width, int height ) {

  // get framebuffer size
  int w, h; 
  glfwGetFramebufferSize(window, &w, &h );
    
  // update buffer size
  buffer_w = w; buffer_h = h;
  glViewport( 0, 0, buffer_w, buffer_h );

  // resize on-screen display
  osd_text->resize(buffer_w, buffer_h);

  // resize render if there is a user space renderer
  if (renderer) renderer->resize( buffer_w, buffer_h );  
}

void Viewer::cursor_callback( GLFWwindow* window, double xpos, double ypos ) {

  // forward pan event to renderer
  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
    if( HDPI ) {
      float pan_x = (2 * xpos - cursorX) / buffer_w;
      float pan_y = (2 * ypos - cursorY) / buffer_h;
      renderer->pan_event(pan_x, pan_y);
    } else {
      float pan_x = (xpos - cursorX) / buffer_w;
      float pan_y = (ypos - cursorY) / buffer_h;
      renderer->pan_event(pan_x, pan_y);
    }
  }

  if( HDPI ) {
    cursorX = 2*xpos;
    cursorY = 2*ypos;
  } else {
    cursorX = xpos;
    cursorY = ypos;
  }

}

void Viewer::scroll_callback( GLFWwindow* window, double xoffset, double yoffset) {

  // simple mouse wheel scrolls are in the y-axis
  float scale_factor = 0.1;
  renderer->zoom_event(1 + yoffset * scale_factor);

  // forward x-axis scrolls as pan events
  if( HDPI ) {
    renderer->pan_event(2 * xoffset, 0);
  } else {
    renderer->pan_event(-xoffset, 0);
  }

}

} // namespace CSD462

