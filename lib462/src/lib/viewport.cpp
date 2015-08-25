#include "Viewport.h"

#include <vector>

namespace CSD462 {

Viewport::Viewport() {

  // compile shaders
  program = compile_shaders();

  const GLfloat vertex_buffer_data[] = 
  {  
    -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f, 
     1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
     1.0f, -1.0f, 0.0f 
  };

  const GLfloat uv_buffer_data[] = 
  {
    0.0f, 1.0f,
    1.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,
    1.0f, 1.0f 
  };

  // make buffers
  vertex_buffer = make_buffer(
    GL_ARRAY_BUFFER,
    sizeof(vertex_buffer_data),
    vertex_buffer_data
  );

  uv_buffer = make_buffer(
    GL_ARRAY_BUFFER,
    sizeof(uv_buffer_data),
    uv_buffer_data
  );

}

Viewport::~Viewport() {

  glDeleteProgram  (program);
  glDeleteBuffers  (1, &vertex_buffer);
  glDeleteBuffers  (1, &uv_buffer);
  glDeleteTextures (1, &texture);

}


int Viewport::bind(char *buffer, size_t w, size_t h) {

  this->w = w;
  this->h = h;
  pixels  = buffer;

  texture = make_texture_rgb(pixels, w, h);
 
	return 0;
}

void Viewport::update() {

  glUseProgram(program);

  update_texture_rgb(texture, pixels, w, h);
  textureID = glGetUniformLocation(program, "texture_sampler");

  // bind texture
	glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(textureID, 0);

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glVertexAttribPointer(
    0,            // attribute 
    3,            // size 
    GL_FLOAT,     // type 
    GL_FALSE,     // normalized 
    0, 		        // stride 
    (void*)0 	   // array buffer offset 
	);

    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
    glVertexAttribPointer(
      1,            // attribute 
      2,            // size : U+V => 2 
      GL_FLOAT,     // type 
      GL_FALSE,     // normalized? 
      0,            // stride 
      (void*)0      // array buffer offset 
    );

	// draw triangles
	glDrawArrays(GL_TRIANGLES, 0, 3 * 2);
	glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);   
}


GLuint Viewport::compile_shaders() {

  // Create the shaders
  GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
  GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);

  const char *vert_shader_src = "#version 330 core"
  "\nlayout(location = 0) in vec3 vertex_position_modelspace;"
  "\nlayout(location = 1) in vec2 vertex_uv;"
  "\nout vec2 uv;"
  "\nvoid main() {"
  "\n    gl_Position = vec4(vertex_position_modelspace, 1);"
  "\n    uv = vertex_uv;"
  "\n}";

  const char *frag_shader_src = "#version 330 core"
  "\nin vec2 uv;"
  "\nout vec3 color;"
  "\nuniform sampler2D texture_sampler;"
  "\nvoid main() {"
  "\n    color = texture( texture_sampler, uv ).rgb;"
  "\n}";

  GLint result = GL_FALSE;
  int info_length;

  // Compile Vertex Shader
  glShaderSource(vert_shader, 1, &vert_shader_src, NULL);
  glCompileShader(vert_shader);

  // Check Vertex Shader
  glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &result);
  glGetShaderiv(vert_shader, GL_INFO_LOG_LENGTH, &info_length);
  if ( info_length > 0 ){
    std::vector<char> vert_shader_errmsg(info_length+1);
    glGetShaderInfoLog(vert_shader, info_length, NULL, &vert_shader_errmsg[0]);
    printf("%s\n", &vert_shader_errmsg[0]);
  }

  // Compile Fragment Shader
  glShaderSource(frag_shader, 1, &frag_shader_src, NULL);
  glCompileShader(frag_shader);

  // Check Fragment Shader
  glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &result);
  glGetShaderiv(frag_shader, GL_INFO_LOG_LENGTH, &info_length);
  if ( info_length > 0 ){
    std::vector<char> frag_shader_errmsg(info_length+1);
    glGetShaderInfoLog(frag_shader, info_length, NULL, &frag_shader_errmsg[0]);
    printf("%s\n", &frag_shader_errmsg[0]);
  }

  // Link the program
  GLuint program = glCreateProgram();
  glAttachShader(program, vert_shader);
  glAttachShader(program, frag_shader);
  glLinkProgram(program);

  // Check the program
  glGetProgramiv(program, GL_LINK_STATUS, &result);
  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_length);
  if ( info_length > 0 ){
    std::vector<char> program_errmsg(info_length+1);
    glGetProgramInfoLog(program, info_length, NULL, &program_errmsg[0]);
    printf("%s\n", &program_errmsg[0]);
  }

  glDetachShader(1, vert_shader);
  glDetachShader(1, frag_shader);
  glDeleteShader(vert_shader);
  glDeleteShader(frag_shader);

  return program;
}


GLuint Viewport::make_buffer(GLenum target,
                             GLsizei buffer_size,
                             const void *buffer_data) {
  GLuint buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(target, buffer);
  glBufferData(target, buffer_size, buffer_data, GL_STATIC_DRAW);
  return buffer;
}

GLuint Viewport::make_texture_rgb(void* pixel_buffer, 
                                  unsigned int width,
                                  unsigned int height) {

  // Create one OpenGL texture
  GLuint textureID;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);  
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 
               0, GL_RGB, GL_UNSIGNED_BYTE, pixel_buffer);

  // trilinear filtering
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
  glGenerateMipmap(GL_TEXTURE_2D);

  // Return the ID of the texture we just created
  return textureID;
}

GLuint Viewport::make_texture_rgba(void* pixel_buffer, 
                                   unsigned int width,
                                   unsigned int height) {

  // Create one OpenGL texture
  GLuint textureID;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);  
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 
               0, GL_RGBA, GL_UNSIGNED_BYTE, pixel_buffer);

  // trilinear filtering
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
  glGenerateMipmap(GL_TEXTURE_2D);

  // Return the ID of the texture we just created
  return textureID;
}


void Viewport::update_texture_rgb(GLuint textureID, 
                                  void* pixel_buffer, 
                                  unsigned int width,
                                  unsigned int height) {
  glBindTexture(GL_TEXTURE_2D, textureID);  
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 
               0, GL_RGB, GL_UNSIGNED_BYTE, pixel_buffer);
}


void Viewport::update_texture_rgba(GLuint textureID, 
                                   void* pixel_buffer, 
                                   unsigned int width,
                                   unsigned int height) {
  glBindTexture(GL_TEXTURE_2D, textureID);  
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 
               0, GL_RGBA, GL_UNSIGNED_BYTE, pixel_buffer);
}

}; // namespace CSD462
