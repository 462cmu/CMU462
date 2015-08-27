#ifndef CSD462_VIEWPORT_H
#define CSD462_VIEWPORT_H

#include "glew.h"

namespace CSD462 {

/**
 * Draws buffered image data on screen.
 * The viewport currently draws a textured quad that fills up the
 * context, with no respect to aspect ratio, etc. Need to make it
 * respect certain constrains.
 */
class Viewport {
 public:

  /**
   * Constructor.
   */
  Viewport();

  /**
   * Destructor.
   */
  ~Viewport();

  /**
   * Bind the viewport to a bitmap buffer.
   * @param buffer buffer that holds the bitmap pixels
   * @param w width of the bitmap
   * @param h height of the bitmap
   * @return 0 if successful
   *        -1 if failed
   */
  int bind(char *buffer, size_t w, size_t h);

  /**
   * Update the viewport.
   */    
  void update();

private:

  size_t w, h;

  void *pixels;

  GLuint vertex_buffer;
  GLuint uv_buffer;

  GLuint texture;
  GLuint textureID;

  GLuint program;

  GLuint compile_shaders();

  GLuint make_buffer( GLenum target, 
                      GLsizei buffer_size,
                      const void *buffer_data );

  GLuint make_texture_rgb( void* pixel_buffer, 
                           unsigned int width, 
                           unsigned int height );

  GLuint make_texture_rgba( void* pixel_buffer, 
                            unsigned int width, 
                            unsigned int height );

  void update_texture_rgb( GLuint textureID,
                           void* pixel_buffer, 
                           unsigned int width, 
                           unsigned int height );

  void update_texture_rgba( GLuint textureID,
                            void* pixel_buffer, 
                            unsigned int width, 
                            unsigned int height );
};

}; // namespace CSD462

#endif // CSD462_VIEWPORT_H