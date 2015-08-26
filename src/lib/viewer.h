#ifndef CSD462_VIEWER_H
#define CSD462_VIEWER_H

#include "renderer.h"
#include "osdtext.h"

#include <chrono>
#include <GLFW/glfw3.h>

namespace CSD462 {

/**
 * Provides window display and event handling routines. 
 * A user application may draw to the window's context by providing
 * a user space renderer. The viewer manages other display components
 * such as the zoom views, text OSD, etc. It also takes care of window 
 * event handling and passing, through which the renderer may interact 
 * with user inputs. 
 */
class Viewer {
 public:

  /**
   * Constructor.
   * Creates a new viewer with the default title (CSD462).
   */
  Viewer();

  /** 
   * Constructor.
   * Creates a new viweer with the given title.
   */
  Viewer(const char* title);

  /**
   * Destructor.
   * Destroys the viewer instance and frees memory.
   * Note that this does not change the user space renderer.
   */
  ~Viewer();

  /**
   * Initialize the viewer.
   * This will open up a window and install all the event handlers
   * and make the viewer ready for drawing.
   */
  void init();
  
  /**
   * Start the drawing loop of the viewer.
   * Once called this will block until the viewer is close.
   */
  void start();

  /**
   * Set a user space renderer.
   * The viewer will use the given user space renderer in drawing.
   * \param renderer The user space renderer to use in the viewer.
   */
  void set_renderer(Renderer *renderer);

 private:

  /**
   * Main update loop.
   */
  static void update();
    
  /**
   * Draw information view.
   */
  static void drawInfo();

  /**
   * Draw zoom view.
   */
  static void drawZoom();

  // window event callbacks
  static void err_callback( int error, const char* description );
  static void key_callback( GLFWwindow* window, int key, int scancode, int action, int mods );
  static void resize_callback( GLFWwindow* window, int width, int height );
  static void cursor_callback( GLFWwindow* window, double xpos, double ypos );

  // HDPI display
  static bool HDPI;

  // framerate related timeers
  static int framecount; 
  static std::chrono::time_point<std::chrono::system_clock> sys_last; 
  static std::chrono::time_point<std::chrono::system_clock> sys_curr; 

  // draw toggles
  static bool showZoom;
  static bool showInfo;

  // window properties
  static GLFWwindow* window;
  static size_t buffer_w;
  static size_t buffer_h;

  // cursor properties
  static GLFWcursor* cursor;
  static double cursorX;
  static double cursorY;

  // user space renderer
  static Renderer* renderer; 

  // on-screen display
  static OSDText* osd_text;
  static int line_id_renderer;
  static int line_id_framerate;


}; // class Viewer

} // namespace CSD462

#endif // CSD462_VIEWER_H
