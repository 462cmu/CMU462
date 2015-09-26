#ifndef CMU462_RENDERER_H
#define CMU462_RENDERER_H

#include <stdio.h>
#include <string>

namespace CMU462 {

// MOUSE INPUTS //
#define MOUSE_LEFT     0
#define MOUSE_RIGHT    1
#define MOUSE_MIDDLE   2

// KEYBOARD INPUTS //
#define KEYBOARD_ENTER           257
#define KEYBOARD_TAB             258
#define KEYBOARD_BACKSPACE       259
#define KEYBOARD_INSERT          260
#define KEYBOARD_DELETE          261
#define KEYBOARD_RIGHT           262 
#define KEYBOARD_LEFT            263
#define KEYBOARD_DOWN            264
#define KEYBOARD_UP              265
#define KEYBOARD_PAGE_UP         266
#define KEYBOARD_PAGE_DOWN       267
#define KEYBOARD_PRINT_SCREEN    283

// EVENT TYPES //
#define EVENT_RELEASE  0
#define EVENT_PRESS    1
#define EVENT_REPEAT   2

// MODIFIERS //
#define MOD_SHIFT   0x0001
#define MOD_CTRL    0x0002
#define MOD_ALT     0x0004
#define MOD_SUPER   0x0008

/**
 * Abstract renderer definition.
 * The abstract class defines a general framework for user-space renderers.
 * User space renderers can have different routines for drawing, and the 
 * viewer will call the render function to display the output of user space 
 * renderers. The viewer will also forward events such as buffer resizes to 
 * the user space renderer for it to respond. It will also pass events that it 
 * does not know how to handle to the renderer so that the renderer can define
 * its own control keybindings, etc. 
 */
class Renderer {
 public:

  /**
   * Virtual Destructor.
   * Each renderer implementation should define its own destructor 
   * that takes care of freeing the resources that it uses. 
   */
  virtual ~Renderer( void ) { }

  /**
   * Initialize the renderer.
   * A renderer may have some initialization work to do before it is ready
   * to be used. The viewer will call the init function before using the 
   * renderer in drawing. 
   */
  virtual void init( void ) = 0;

  /**
   * Draw content.
   * Renderers are free to define their own routines for drawing to the 
   * context. The viewer calls this function on every frame update.
   */
  virtual void render( void ) = 0;

  /**
   * Respond to buffer resize.
   * The viewer will inform the renderer of a context resize by calling
   * this function. The renderer has complete freedom to handle resizing,
   * and a good renderer implementation should handle resizes properly. 
   * \param w The new width of the context
   * \param h The new height of the context
   */
  virtual void resize( size_t w, size_t h ) = 0;

 /**
   * Return a name for the renderer.
   * If the viewer has a renderer set at initialization, it will include 
   * the renderer name in the window title.
   */
  virtual std::string name( void ) = 0;

  /**
   * Return a brief description of the renderer.
   * Each renderer can define this differently. The viewer will use the 
   * returned value in the renderer section of its on-screen display.
   */
  virtual std::string info( void ) = 0;

  /**
   * Respond to cursor events.
   * The viewer itself does not really care about the cursor but it will take 
   * the GLFW cursor events and forward the ones that matter to  the renderer. 
   * The arguments are defined in screen space coordinates ( (0,0) at top
   * left corner of the window and (w,h) at the bottom right corner.
   * \param x the x coordinate of the cursor
   * \param y the y coordinate of the cursor
   */
  virtual void cursor_event( float x, float y ) { }

  /**
   * Respond to zoom event.
   * Like cursor events, the viewer itself does not care about the mouse wheel 
   * either, but it will take the GLFW wheel events and forward them directly 
   * to the renderer. 
   * \param offset_x Scroll offset in x direction
   * \param offset_y Scroll offset in y direction
   */
  virtual void scroll_event( float offset_x, float offset_y ) { }

  /**
   * Respond to mouse click event.
   * The viewer will always forward mouse click events to the renderer. 
   * \param key The key that spawned the event. The mapping between the
   *        key values and the mouse buttons are given by the macros defined
   *        at the top of this file.  
   * \param event The type of event. Possible values are 0, 1 and 2, which
   *        corresponds to the events defined in macros. 
   * \param mods if any modifier keys are held down at the time of the event
   *        modifiers are defined in macros.
   */
  virtual void mouse_event( int key, int event, unsigned char mods ) { }

  /**
   * Respond to keyboard event.
   * The viewer will always forward mouse key events to the renderer. 
   * \param key The key that spawned the event. ASCII numbers are used for
   *        letter characters. Non-letter keys are selectively supported 
   *        and are defined in macros.
   * \param event The type of event. Possible values are 0, 1 and 2, which
   *        corresponds to the events defined in macros. 
   * \param mods if any modifier keys are held down at the time of the event
   *        modifiers are defined in macros.
   */
  virtual void keyboard_event( int key, int event, unsigned char mods ) { }

  /**
   * Internal - 
   * The viewer will tell the renderer if the screen is in HDPI mode.
   */ 
  void use_hdpi_reneder_target() { use_hdpi = true; }

 protected:

  bool use_hdpi; ///< if the render target is using HIDPI

};

} // namespace CMU462

#endif // CMU462_RENDERER_H
