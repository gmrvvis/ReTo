/*
 * Copyright (c) 2014-2016 GMRV/URJC.
 *
 * Authors: Cristian Rodriguez Bernal (crodriguez)
 *
 * This file is part of ReTo <https://gitlab.gmrv.es/nsviz/ReTo>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include "ProgramShader.h"
#include <fstream>
#include <iostream>

namespace reto
{
  ProgramShader::ProgramShader(void) 
  {
    _program = -1;
    _attrsList.clear();
    _uniformList.clear();
    _uboList.clear();
    #ifdef RETO_SUBPROGRAMS
      _subprograms.clear();
    #endif
    _shaders.clear();

    #ifdef RETO_OCC_QUERY
      // Occlusion query object
      glGenQueries(1, &_occQuery);
    #endif
  }

  ProgramShader::~ProgramShader(void) 
  {
    destroy();
  }

  bool ProgramShader::loadFromText(const std::string& vsSource, const std::string& fsSource) 
  {
    return (loadFromText(vsSource, GL_VERTEX_SHADER) && loadFromText(fsSource, GL_FRAGMENT_SHADER));
  }

  bool ProgramShader::loadFromText(const std::string& source, GLenum type) 
  {
    // Create and compile shader
    GLuint shader;
    shader = glCreateShader(type);
    const char *c_str = source.c_str();
    glShaderSource(shader, 1, &c_str, NULL);

    GLint status;
    glCompileShader(shader);
    glGetShaderiv (shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) 
    {
      GLint infoLogLength;        
      glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &infoLogLength);
      GLchar *infoLog= new GLchar[infoLogLength];
      glGetShaderInfoLog (shader, infoLogLength, NULL, infoLog);
      std::cerr << "Compile log: " << infoLog << std::endl;
      delete [] infoLog;
      return false;
    }

    // Add to shaders in use
    _shaders.push_back(shader);
    return true;
  }

  bool ProgramShader::loadFromTextVS(const std::string& source) 
  {
    return loadFromText(source, GL_VERTEX_SHADER);
  }

  bool ProgramShader::loadFromTextFS(const std::string& source) 
  {
    return loadFromText(source, GL_FRAGMENT_SHADER);
  }

  #ifdef RETO_GEOMETRY_SHADERS
    bool ProgramShader::loadFromTextGS(const std::string& source) 
    {
      return loadFromText(source, GL_GEOMETRY_SHADER);
    }
  #endif

  #ifdef RETO_TESSELATION_SHADERS
    bool ProgramShader::loadFromTextTES(const std::string& source) 
    {
      return loadFromText(source, GL_TESS_EVALUATION_SHADER);
    }

    bool ProgramShader::loadFromTextTCS(const std::string& source) 
    {
      return loadFromText(source, GL_TESS_CONTROL_SHADER);
    }
  #endif

  #ifdef RETO_COMPUTE_SHADERS 
    bool ProgramShader::loadFromTextCS(const std::string& source) 
    {
      return loadFromText(source, GL_COMPUTE_SHADER);
    }
  #endif

  bool ProgramShader::load(const std::string& fileName, GLenum type) 
  {
    unsigned int fileLen;

    // Load file
    std::ifstream file;
    file.open(fileName.c_str(), std::ios::in);
    if (!file) 
    {
      std::cout << "File " << fileName << " not found" << std::endl;
      return false;
    }

    // File length
    file.seekg(0, std::ios::end);
    fileLen = int(file.tellg());
    file.seekg(std::ios::beg);

    // Read the file
    char *source = new char[fileLen + 1];

    int i = 0;
    while (file.good()) 
    {
      source[i] = char(file.get());
      if (!file.eof()) i++;
      else fileLen = i;
    }
    source[fileLen] = '\0';
    file.close();

    // Create and compile shader
    GLuint shader;
    shader = glCreateShader(type);
    glShaderSource(shader, 1, (const GLchar **) &source, (const GLint *) &fileLen);

    GLint status;
    glCompileShader(shader);
    glGetShaderiv (shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) 
    {
      GLint infoLogLength;        
      glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &infoLogLength);
      GLchar *infoLog= new GLchar[infoLogLength];
      glGetShaderInfoLog (shader, infoLogLength, NULL, infoLog);
      std::cerr << "Compile log ("<< fileName << "): " << infoLog << std::endl;
      delete [] infoLog;
      return false;
    }
    delete source;

    // Add to shaders in use
    _shaders.push_back(shader);
    return true;
  }

  bool ProgramShader::load(const std::string& vsFile, const std::string& fsFile) 
  {
    return (load(vsFile, GL_VERTEX_SHADER) && load(fsFile, GL_FRAGMENT_SHADER));
  }

  bool ProgramShader::loadVS(const std::string& file) 
  {
    return load(file, GL_VERTEX_SHADER);
  }

  bool ProgramShader::loadFS(const std::string& file) 
  {
    return load(file, GL_FRAGMENT_SHADER);
  }

  #ifdef RETO_GEOMETRY_SHADERS
    bool ProgramShader::loadGS(const std::string& file) 
    {
      return load(file, GL_GEOMETRY_SHADER);
    }
  #endif

  #ifdef RETO_TESSELATION_SHADERS
    bool ProgramShader::loadTES(const std::string& file) 
    {
      return load(file, GL_TESS_EVALUATION_SHADER);
    }

    bool ProgramShader::loadTCS(const std::string& file) 
    {
      return load(file, GL_TESS_CONTROL_SHADER);
    }
  #endif

  #ifdef RETO_COMPUTE_SHADERS 
    bool ProgramShader::loadCS(const std::string& file) 
    {
      return load(file, GL_COMPUTE_SHADER);
    }
  #endif

  void ProgramShader::destroy() 
  {
    _program = -1;
    _attrsList.clear();
    _uniformList.clear();
    _uboList.clear();

    #ifdef RETO_SUBPROGRAMS
      _subprograms.clear();
    #endif
    _shaders.clear();
    GLuint size = _shaders.size();
    for(GLuint i = 0; i < size; i++) 
    {
      if(_shaders[i] != 0) 
      {
        glDetachShader(_program, _shaders[i]);
      }
    }
    glDeleteProgram(_program);
  }

  void ProgramShader::create() 
  {
    _program = glCreateProgram();
    GLuint size = _shaders.size();
    for(GLuint i = 0; i < size; i++) 
    {
      if(_shaders[i] != 0) 
      {
        glAttachShader(_program, _shaders[i]);
      }
    }
  }

  bool ProgramShader::link() 
  {
    // link and check whether the program links fine
    GLint status;
    glLinkProgram (_program);
    glGetProgramiv (_program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) 
    {
      GLint infoLogLength;
      
      glGetProgramiv (_program, GL_INFO_LOG_LENGTH, &infoLogLength);
      GLchar *infoLog = new GLchar[infoLogLength];
      glGetProgramInfoLog (_program, infoLogLength, NULL, infoLog);
      std::cerr << "Link log: " << infoLog << std::endl;
      delete [] infoLog;
      return false;
    }
    return true;
  }

  void ProgramShader::use() 
  {
    glUseProgram(_program);
  }

  void ProgramShader::unuse() 
  {
    glUseProgram(-1);
  }

  bool ProgramShader::compile_and_link() 
  {
    create();
    return link();
  } 
   
  GLuint ProgramShader::program() 
  { 
    return _program; 
  } 

  void ProgramShader::addAttribute(const std::string& attr) 
  {
    _attrsList[attr] = glGetAttribLocation(_program, attr.c_str());
  }

  void ProgramShader::addAttributes(const std::vector<char*> attrs) 
  {
    for(auto& a: attrs) 
    {
      addAttribute(a);
    }
  }

  void ProgramShader::addUniform(const std::string& uniform_name) 
  {
    _uniformList[uniform_name] = glGetUniformLocation(_program, uniform_name.c_str());
  }

  void ProgramShader::addUniforms(const std::vector<char*> uniforms) 
  {
    for(auto& u: uniforms) 
    {
      addUniform(u);
    }
  }

  void ProgramShader::addUbo(const std::string& ubo_name) 
  {
    _uboList[ubo_name] = glGetUniformBlockIndex(_program, ubo_name.c_str());
  }

  #ifdef RETO_SUBPROGRAMS
    void ProgramShader::addSubroutine(const std::string& name, GLenum shaderType) 
    {
      GLuint idx = glGetSubroutineIndex(_program, shaderType, name.c_str());
      auto sub = SubProgram(name.c_str(), idx);
      _subprograms.insert(std::pair<GLenum, SubProgram>(shaderType, sub));
    }
  #endif

  void ProgramShader::bindAttribute(const std::string& attr, GLuint index) 
  {
    glBindAttribLocation(_program, index, attr.c_str());
  }

  GLuint ProgramShader::attribute(const std::string& attr) 
  {
    return _attrsList[attr];
  }

  GLuint ProgramShader::operator ()(const std::string& attr) 
  {
    return  attribute(attr);
  }

  GLuint ProgramShader::uniform(const std::string& uniform_name) 
  {
    return _uniformList[uniform_name];
  }

  GLuint ProgramShader::operator [](const std::string& attr) 
  {
    return  uniform(attr);
  }

  GLuint ProgramShader::ubo(const std::string& _ubo) 
  {
    return _uboList[_ubo];
  }

  #ifdef RETO_SUBPROGRAMS
    GLuint ProgramShader::subprogram(const std::string& name, GLenum shaderType) 
    {
      // TODO: http://www.cplusplus.com/reference/map/multimap/equal_range/
      std::multimap<GLenum, SubProgram>::iterator v = _subprograms.find(shaderType);
      int number = _subprograms.count(shaderType);
      for(int i = 0; i < number; i++) 
      {
        if((*v).second.name == name) 
        {
          return (*v).second.index;
        }
        v++;
      }
      std::cerr << "Subroutine not found" << std::endl;
      return -1;
    }
  #endif

  void ProgramShader::bindUniform(const std::string& unif, GLuint idx) 
  {
    if(_uniformList.find(unif) == _uniformList.end()) 
    {
      _uniformList[unif] = idx;
    } 
    else 
    {
      std::cerr << "Uniform exist" << std::endl;
    }
  }

  void ProgramShader::sendUniform(const std::string& uniform_name, float x, float y, float z) 
  {
    GLint loc = uniform(uniform_name);
    glUniform3f(loc, x, y, z);
  }

  void ProgramShader::sendUniform2v(const std::string& uniform_name, const std::vector< float > & v) 
  {
    GLint loc = uniform(uniform_name);
    glUniform2fv(loc, 1, v.data( ));
  }

  void ProgramShader::sendUniform3v(const std::string& uniform_name, const std::vector< float > & v) 
  {
    GLint loc = uniform(uniform_name);
    glUniform3fv(loc, 1, v.data( ));
  }

  void ProgramShader::sendUniform4v(const std::string& uniform_name, const std::vector< float > & v) 
  {
    GLint loc = uniform(uniform_name);
    glUniform4fv(loc, 1,v.data( ));
  }

  void ProgramShader::sendUniform4m(const std::string& uniform_name, 
    const std::vector< float > & m, GLboolean inverse) 
  {
    GLint loc = uniform(uniform_name);
    glUniformMatrix4fv(loc, 1, inverse, m.data( ));
  }

  void ProgramShader::sendUniform3m(const std::string& uniform_name, const std::vector< float > & m) 
  {
    GLint loc = uniform(uniform_name);
    glUniformMatrix3fv(loc, 1, GL_FALSE, m.data( ));
  }

  void ProgramShader::sendUniformf(const std::string& uniform_name, GLfloat val) 
  {
    GLint loc = uniform(uniform_name);
    glUniform1f(loc, val);
  }

  void ProgramShader::sendUniformi(const std::string& uniform_name, GLint val) 
  {
    GLint loc = uniform(uniform_name);
    glUniform1i(loc, val);
  }

  void ProgramShader::sendUniformb(const std::string& uniform_name, GLboolean val) 
  {
    GLint loc = uniform(uniform_name);
    glUniform1i(loc, val);
  }

  void ProgramShader::sendUniformu(const std::string& uniform_name, GLuint val) 
  {
    GLint loc = uniform(uniform_name);
    glUniform1ui(loc, val);
  }

  #ifdef RETO_SUBPROGRAMS
    void ProgramShader::activeSubprogram(const std::string& name, GLenum shaderType) 
    {
      // TODO: http://www.cplusplus.com/reference/map/multimap/equal_range/
      std::multimap<GLenum, SubProgram>::iterator v = _subprograms.find(shaderType);
      int number = _subprograms.count(shaderType);
      for(int i = 0; i < number; i++) 
      {
        if((*v).second.name == name) 
        {
          glUniformSubroutinesuiv(shaderType, 1, &(*v).second.index);
          return;
        }
        v++;
      }
      std::cerr << "Subroutine not found" << std::endl;
    }
  #endif

  #ifdef RETO_COMPUTE_SHADERS
    void ProgramShader::launchComputeWork(GLuint nGx, GLuint nGy, GLuint nGz) 
    {
      glDispatchCompute(nGx, nGy, nGz);
    }
  #endif

  #ifdef RETO_TESSELATION_SHADERS

    GLuint ProgramShader::getPatchVertices() 
    {
      GLint n;
      glGetIntegerv(GL_PATCH_VERTICES, &n);
      return n;
    }
    GLfloat ProgramShader::getInnerLevel() 
    {
      GLfloat l;
      glGetFloatv(GL_PATCH_DEFAULT_INNER_LEVEL, &l);
      return l;
    }
    GLfloat ProgramShader::getOuterLevel() 
    {
      GLfloat l;
      glGetFloatv(GL_PATCH_DEFAULT_OUTER_LEVEL, &l);
      return l;
    }

    void ProgramShader::setPatchVertices(GLuint n) 
    {
      glPatchParameteri(GL_PATCH_VERTICES, n);
    }
    void ProgramShader::setInnerLevel(GLfloat l) 
    {
      glPatchParameterfv(GL_PATCH_DEFAULT_INNER_LEVEL, &l);
    }
    void ProgramShader::setOuterLevel(GLfloat l) 
    {
      glPatchParameterfv(GL_PATCH_DEFAULT_OUTER_LEVEL, &l);
    }
  #endif

  #ifdef RETO_OCC_QUERY
    bool ProgramShader::occlusionQuery(std::function<void()> renderFunc) 
    {
      // Disable writing to the color buffer and depth buffer. 
      // We just wanna check if they would be rendered, not actually render them
      glColorMask(false, false, false, false);
      glDepthMask(GL_FALSE);
      glBeginQuery(GL_SAMPLES_PASSED, _occQuery);
      renderFunc();
      glEndQuery(GL_SAMPLES_PASSED);
      GLint samplesPassed = 0;
      glGetQueryObjectiv(_occQuery, GL_QUERY_RESULT, &samplesPassed);
      // Re-enable writing to color buffer and depth buffer
      glColorMask(true, true, true, true);
      glDepthMask(GL_TRUE);
      return samplesPassed > 0;
    }
  #endif

  #ifdef RETO_GEOMETRY_SHADERS
    void ProgramShader::setGeometryMaxOutput(GLuint o) 
    {
      glProgramParameteri(_program, GL_GEOMETRY_VERTICES_OUT, o);
    }
    void ProgramShader::setGeometryInputType(GLuint i) 
    {
      glProgramParameteri(_program, GL_GEOMETRY_INPUT_TYPE, i);
    }
    void ProgramShader::setGeometryOutputType(GLuint o) 
    {
      glProgramParameteri(_program, GL_GEOMETRY_OUTPUT_TYPE, o);
    }

    GLint ProgramShader::getGeometryMaxOutput() 
    {
      GLint o;
      glGetProgramiv(_program, GL_GEOMETRY_VERTICES_OUT, &o);
      return o;
    }

    GLint ProgramShader::getGeometryInputType() 
    {
      GLint o;
      glGetProgramiv(_program, GL_GEOMETRY_INPUT_TYPE, &o);
      return o;
    }

    GLint ProgramShader::getGeometryOutputType() 
    {
      GLint o;
      glGetProgramiv(_program, GL_GEOMETRY_OUTPUT_TYPE, &o);
      return o;
    }
  #endif
}