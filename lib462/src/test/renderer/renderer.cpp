#include <string>
#include <iostream>

#include "viewer.h"
#include "renderer.h"

using namespace std;
using namespace CSD462;

class TriRenderer : public Renderer {
 public:

  ~TriRenderer() { }

  string name() {
    return "Triangle Renderer";
  }

  string info() {
    return "I just draw a blue triangle";
  }

  void init() {
    return;
  }
  
  void render() {
    if (shoud_draw) {
      glBegin(GL_TRIANGLES);
      glColor3f(0.1, 0.2, 0.3);
      glVertex3f(0, 0, 0);
      glVertex3f(-1, 0, 0);
      glVertex3f(0, 1, 0);
      glEnd();
    }
  }

  void resize(size_t w, size_t h) {
    return;
  }

  void key_event(char key) {
    if (key == 'R') shoud_draw = !shoud_draw; 
    return;
  }
 
 private:

  bool shoud_draw;

};

int main( int argc, char** argv ) {

  // create viewer
  Viewer viewer = Viewer();

  // defined a user space renderer
  Renderer* renderer = new TriRenderer();

  // set user space renderer
  viewer.set_renderer(renderer);

  // start the viewer
  viewer.init();
  viewer.start();

  return 0;
}

