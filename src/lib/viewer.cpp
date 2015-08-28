#include "viewer.h"

#include <stdio.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

#include "GLEW/glew.h"

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

  // set event callbacks
  glfwSetKeyCallback( window, key_callback );
  glfwSetFramebufferSizeCallback( window, resize_callback );
  glfwSetCursorPosCallback( window, cursor_callback );

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

  // draw zoom
  if( showZoom ) {
    drawZoom();
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

void Viewer::drawZoom() {
  // size (in pixels) of region of interest
  const size_t regionSize = 32;
  
  // relative size of zoom window
  size_t zoomFactor = 16;
  
  // compute zoom factor---the zoom window should never cover
  // more than half of the framebuffer, horizontally or vertically
  size_t bufferSize = min( buffer_w, buffer_h );
  if( regionSize*zoomFactor > bufferSize/2 ) {
    zoomFactor = (bufferSize/2)/regionSize;
  }
  size_t zoomSize = regionSize * zoomFactor;

  // adjust the cursor coordinates so that the region of
  // interest never goes outside the bounds of the framebuffer
  size_t cX = max( regionSize/2, min( buffer_w-regionSize/2-1, (size_t) cursorX ));
  size_t cY = max( regionSize/2, min( buffer_h-regionSize/2-1, buffer_h - (size_t) cursorY ));

  // grab pixels from the region of interest
  vector<unsigned char> windowPixels( 3*regionSize*regionSize );
  glReadPixels( cX - regionSize/2,
                cY - regionSize/2,
                regionSize,
                regionSize,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                &windowPixels[0] );

  // upsample by the zoom factor, highlighting pixel boundaries
  vector<unsigned char> zoomPixels( 3*zoomSize*zoomSize );
  unsigned char* wp = &windowPixels[0];
  // outer loop over pixels in region of interest
  for( int y = 0; y < regionSize; y++ ) {
   int y0 = y*zoomFactor;
   for( int x = 0; x < regionSize; x++ ) {
      int x0 = x*zoomFactor;
      unsigned char* zp = &zoomPixels[ ( x0 + y0*zoomSize )*3 ];
      // inner loop over upsampled block
      for( int j = 0; j < zoomFactor; j++ ) {
        for( int i = 0; i < zoomFactor; i++ ) {
          for( int k = 0; k < 3; k++ ) {
            // highlight pixel boundaries
            if( i == 0 || j == 0 ) {
              const float s = .3;
              zp[k] = (int)( (1.-2.*s)*wp[k] + s*255. );
            } else {
              zp[k] = wp[k];
            }
          }
          zp += 3;
        }
        zp += 3*( zoomSize - zoomFactor );
      }
      wp += 3;
    }
  }

  // copy pixels to the screen using OpenGL
  glMatrixMode( GL_PROJECTION ); glPushMatrix(); glLoadIdentity(); glOrtho( 0, buffer_w, 0, buffer_h, 0.01, 1000. );
  glMatrixMode( GL_MODELVIEW  ); glPushMatrix(); glLoadIdentity(); glTranslated( 0., 0., -1. );
  
  glRasterPos2i( buffer_w-zoomSize, buffer_h-zoomSize );
  // Or maybe hover zoom?
  //glRasterPos2i( cursorX-zoomSize/2, (buffer_h-cursorY)-zoomSize/2 );
  
  glDrawPixels( zoomSize, zoomSize, GL_RGB, GL_UNSIGNED_BYTE, &zoomPixels[0] );
  glMatrixMode( GL_PROJECTION ); glPopMatrix();
  glMatrixMode( GL_MODELVIEW ); glPopMatrix();
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
  // The renderer needs to be able to inform the viewer about
  // an info update. And into string should only be set on such
  // occations.
  if (renderer) {
    string renderer_info = renderer->info();
    osd_text->set_text(line_id_renderer, renderer_info);
  } else {
    string renderer_info = "No input renderer";
    osd_text->set_text(line_id_renderer, renderer_info);
  }

  // render OSD
  osd_text->render();

//    if( renderer.getRenderMethod() == rasterizeSoftware )
//    {
//     Text::draw( 20, buffer_h-40, "RENDERER: software rasterizer" );
//    }
//    if( renderer.getRenderMethod() == rasterizeOpenGL )
//    {
//     Text::draw( 20, buffer_h-40, "RENDERER: OpenGL" );
//    }
//    if( renderer.getRenderMethod() == rasterizeDifference )
//    {
//     Text::draw( 20, buffer_h-40, "RENDERER: (difference)" );
//
//     int errorCount = renderer.getErrorCount();
//     char errorCountString[1024];
//     if( errorCount == 1 )
//     {
//        sprintf( errorCountString, "%d pixel differs", errorCount );
//     }
//     else
//     {
//        sprintf( errorCountString, "%d pixels differ", errorCount );
//     }
//     glColor3f( 1., .3, .3 );
//     Text::draw( 20, buffer_h-80, errorCountString );
//    }
//
//    glMatrixMode( GL_PROJECTION ); glPopMatrix();
//    glMatrixMode( GL_MODELVIEW ); glPopMatrix();
}

void Viewer::err_callback( int error, const char* description ) {
    out_err( "GLFW Error: " << description );
}

void Viewer::key_callback( GLFWwindow* window, 
                           int key, int scancode, int action, int mods ) {
  if( action == GLFW_PRESS ) {
    if( key == GLFW_KEY_ESCAPE ) { 
      glfwSetWindowShouldClose( window, true ); 
    } else if( key == 'Z' ) { 
      showZoom = !showZoom; 
    } else if( key == 'I' ) { 
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
  if( HDPI ) {
    cursorX = 2*xpos;
    cursorY = 2*ypos;
  } else {
    cursorX = xpos;
    cursorY = ypos;
  }
}

} // namespace CSD462

