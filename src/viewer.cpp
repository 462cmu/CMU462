#include "viewer.h"

#include <stdio.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

#include "GL/glew.h"

#include "console.h"

using namespace std;
using namespace chrono;

#define DEFAULT_W 960
#define DEFAULT_H 640

namespace CMU462 {

// HDPI display
bool Viewer::HDPI;

// framecount & related timeers
int Viewer::framecount;
time_point<system_clock> Viewer::sys_last;
time_point<system_clock> Viewer::sys_curr;

// draw toggles
bool Viewer::showInfo = true;

// window properties
GLFWwindow *Viewer::window;
size_t Viewer::buffer_w;
size_t Viewer::buffer_h;

// user space application
Application *Viewer::application;

// on-screen display
OSDText *Viewer::osd_text;
int Viewer::line_id_application;
int Viewer::line_id_framerate;

Viewer::Viewer() {}

Viewer::~Viewer() {

  glfwDestroyWindow(window);
  glfwTerminate();

  // free resources
  delete application;
  delete osd_text;
}

void Viewer::init() {

  // initialize glfw
  glfwSetErrorCallback(err_callback);
  if (!glfwInit()) {
    out_err("Error: could not initialize GLFW!");
    exit(1);
  }

  // create window
  string title = application ? "CMU462: " + application->name() : "CMU462";
  glfwWindowHint(GLFW_SAMPLES, 4);
  window = glfwCreateWindow(DEFAULT_W, DEFAULT_H, title.c_str(), NULL, NULL);
  if (!window) {
    out_err("Error: could not create window!");
    glfwTerminate();
    exit(1);
  }

  // set context
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  // framebuffer event callbacks
  glfwSetFramebufferSizeCallback(window, resize_callback);

  // key event callbacks
  glfwSetKeyCallback(window, key_callback);

  // cursor event callbacks
  glfwSetCursorPosCallback(window, cursor_callback);

  // wheel event callbacks
  glfwSetScrollCallback(window, scroll_callback);

  // mouse button callbacks
  glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);
  glfwSetMouseButtonCallback(window, mouse_button_callback);

  // initialize glew
  if (glewInit() != GLEW_OK) {
    out_err("Error: could not initialize GLEW!");
    glfwTerminate();
    exit(1);
  }

  // enable alpha blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // resize components to current window size, get DPI
  glfwGetFramebufferSize(window, (int *)&buffer_w, (int *)&buffer_h);
  if (buffer_w > DEFAULT_W)
    HDPI = true;

  // initialize application if already set
  if (application) {
    if (HDPI)
      application->use_hdpi_reneder_target();
    application->init();
  }

  // initialize status OSD
  osd_text = new OSDText();
  if (osd_text->init(HDPI) < 0) {
    out_err("Error: could not initialize on-screen display!");
    exit(1);
  }

  // add lines for application and fps
  line_id_application = osd_text->add_line(-0.95, 0.90, "Application", 18,
                                           Color(0.15, 0.5, 0.15));
  line_id_framerate =
      osd_text->add_line(-0.98, -0.96, "Framerate", 14, Color(0.15, 0.5, 0.15));

  // resize elements to current size
  resize_callback(window, buffer_w, buffer_h);
}

void Viewer::start() {

  // start timer
  sys_last = system_clock::now();

  // run update loop
  while (!glfwWindowShouldClose(window)) {
    update();
  }
}

void Viewer::set_application(Application *application) {
  this->application = application;
}

void Viewer::update() {

  // clear frame
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // run user application
  if (application) {
    application->render();
  }

  // draw info
  if (showInfo) {
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
  double elapsed = ((duration<double>)(sys_curr - sys_last)).count();
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

  // udpate application OSD
  // TODO: This is done on every update and it shouldn't be!
  // The viewer should only update when the application needs to
  // update the info text.
  if (application) {
    string application_info = application->info();
    osd_text->set_text(line_id_application, application_info);
  } else {
    string application_info = "No input application";
    osd_text->set_text(line_id_application, application_info);
  }

  // render OSD
  osd_text->render();
}

void Viewer::err_callback(int error, const char *description) {
  out_err("GLFW Error: " << description);
}

void Viewer::resize_callback(GLFWwindow *window, int width, int height) {

  // get framebuffer size
  int w, h;
  glfwGetFramebufferSize(window, &w, &h);

  // update buffer size
  buffer_w = w;
  buffer_h = h;
  glViewport(0, 0, buffer_w, buffer_h);

  // resize on-screen display
  osd_text->resize(buffer_w, buffer_h);

  // resize user application, if it exists
  if (application)
    application->resize(buffer_w, buffer_h);
}

void Viewer::cursor_callback(GLFWwindow *window, double xpos, double ypos) {

  // forward pan event to application
  if (HDPI) {
    float cursor_x = 2 * xpos;
    float cursor_y = 2 * ypos;
    application->cursor_event(cursor_x, cursor_y);
  } else {
    float cursor_x = xpos;
    float cursor_y = ypos;
    application->cursor_event(cursor_x, cursor_y);
  }
}

void Viewer::scroll_callback(GLFWwindow *window, double xoffset,
                             double yoffset) {

  application->scroll_event(xoffset, yoffset);
}

void Viewer::mouse_button_callback(GLFWwindow *window, int button, int action,
                                   int mods) {

  application->mouse_event(button, action, mods);
}

void Viewer::key_callback(GLFWwindow *window, int key, int scancode, int action,
                          int mods) {

  if (action == GLFW_PRESS) {
    if (key == GLFW_KEY_ESCAPE) {
      glfwSetWindowShouldClose(window, true);
    } else if (key == GLFW_KEY_GRAVE_ACCENT) {
      showInfo = !showInfo;
    }
  }

  application->keyboard_event(key, action, mods);
}

} // namespace CMU462
