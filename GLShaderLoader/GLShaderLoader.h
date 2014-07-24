#pragma once

#include "GLShader.h"
#include "Resource.h"
#include "TextFileLoader.h"

#include <cassert>

// this class is in this file because it's only used in defining how shaders are loaded
class GLShaderLoadParams {
public:

  GLShaderLoadParams (const std::string &vertex_shader_filename, const std::string &fragment_shader_filename)
    :
    m_vertex_shader_filename(vertex_shader_filename),
    m_fragment_shader_filename(fragment_shader_filename)
  { }

  const std::string &VertexShaderFilename () const { return m_vertex_shader_filename; }
  const std::string &FragmentShaderFilename () const { return m_fragment_shader_filename; }

private:

  std::string m_vertex_shader_filename;
  std::string m_fragment_shader_filename;
};

// Template specialization of ResourceLoader<GLShaderLoadParams> which defines how to load such a resource.
template <>
struct ResourceLoader<GLShaderLoadParams> {
  static const bool exists = true;
  static std::shared_ptr<GLShaderLoadParams> LoadResource (const std::string &name, ResourceManager<GLShaderLoadParams> &calling_manager) {
    // We have a predefined set of shader programs, each of which consist of a vertex 
    // shader source filename and a fragment shader source filename.  If the requested
    // name didn't match any of the available, throw an error.

    // TODO: implement lookup using a JSON file which has these mappings -- this would allow
    // a user to add/modify asset paths without having to recompile.

    // NOTE: these ones are just from Freeform, and will go away once the real solution is implemented.
    if (name == "skybox") { 
      return std::make_shared<GLShaderLoadParams>("sky-vert.glsl", "sky-frag.glsl");
    } else if (name == "screen") {
      return std::make_shared<GLShaderLoadParams>("passthrough-vert.glsl", "screen-frag.glsl");
    } else if (name == "bloom") {
      return std::make_shared<GLShaderLoadParams>("passthrough-vert.glsl", "bloom-frag.glsl");
    } else if (name == "menu_preview") {
      return std::make_shared<GLShaderLoadParams>("passthrough-vert.glsl", "previews-frag.glsl");
    } else if (name == "mesh") {
      return std::make_shared<GLShaderLoadParams>("material-vert.glsl", "material-frag.glsl");
    } else if (name == "brush") {
      return std::make_shared<GLShaderLoadParams>("brush-vert.glsl", "material-frag.glsl");
    } else if (name == "wireframe") {
      return std::make_shared<GLShaderLoadParams>("material-vert.glsl", "wireframe-frag.glsl");
    } else if (name == "dummy") {
      return std::make_shared<GLShaderLoadParams>("dummy-vert.glsl", "dummy-frag.glsl");
    } else {
      throw std::domain_error("no resource \"" + name + "\" found for type GLShaderLoadParams");
    }
  }
};

// Template specialization of ResourceLoader<GLShader> which defines how to load such a resource.
template <>
struct ResourceLoader<GLShader> {
  static const bool exists = true;
  static std::shared_ptr<GLShader> LoadResource (const std::string &name, ResourceManager<GLShader> &calling_manager) {
    if (name == "dummy") {
      std::string vertex_shader_source(
        "void main () {\n"
        "    gl_Position = ftransform();\n"
        "    gl_FrontColor = gl_Color;\n"
        "}\n"
      );
      std::string fragment_shader_source(
        "void main () {\n"
        "    gl_FragColor = vec4(1.0, 0.2, 0.3, 1.0);\n"
        "}\n"
      );
      return std::make_shared<GLShader>(vertex_shader_source, fragment_shader_source);
    } else {
      // Load the params for the requested shader program.
      auto params = Resource<GLShaderLoadParams>(name);
      assert(bool(params) && "resource was not loaded correctly");
      // Load the source files.
      auto vertex_shader_source = Resource<TextFile>(params->VertexShaderFilename());
      auto fragment_shader_source = Resource<TextFile>(params->FragmentShaderFilename());
      return std::make_shared<GLShader>(vertex_shader_source->Contents(), fragment_shader_source->Contents());
    }
  }
};
