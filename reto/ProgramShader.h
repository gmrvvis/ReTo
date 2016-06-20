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

/***
 * TODO:
 *  -glDispatchComputeIndirect(GLintptr indirect);
 *  -TransformFeedback in vertex and geometry shaders
 *  -Check dont used uniforms
 *  -Methods to get tess and geom I/O
 */

#ifndef __RETO__PROGRAM_SHADER__
#define __RETO__PROGRAM_SHADER__

#include <map>
#include <map>
#include <string>
#include <vector>

//OpenGL
#ifndef SKIP_GLEW_INCLUDE
#include <GL/glew.h>
#endif
#ifdef Darwin
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#define RETO_GEOMETRY_SHADERS
#define RETO_COMPUTE_SHADERS
#define RETO_TESSELATION_SHADERS
#define RETO_SUBPROGRAMS
#define RETO_OCC_QUERY

#ifdef RETO_OCC_QUERY
  #include <functional>
#endif

namespace reto
{

  class ProgramShader
  {
  public:
    ProgramShader(void);
    ~ProgramShader( void);

    void destroy( );

    bool load( const std::string& vsFile, const std::string& fsFile );
    bool load( const std::string& file, GLenum type );
    bool loadVS( const std::string& file );
    bool loadFS( const std::string& file );
  #ifdef RETO_GEOMETRY_SHADERS
    bool loadGS( const std::string& file );
  #endif
  #ifdef RETO_TESSELATION_SHADERS
    bool loadTES( const std::string& file );
    bool loadTCS( const std::string& file );
  #endif
  #ifdef RETO_COMPUTE_SHADERS
    bool loadCS( const std::string& file );
  #endif
    bool loadFromText( const std::string& vsSource,
                       const std::string& fsSource );
    bool loadFromText( const std::string& source, GLenum type );
    bool loadFromTextVS( const std::string& source );
    bool loadFromTextFS( const std::string& source );
  #ifdef RETO_GEOMETRY_SHADERS
    bool loadFromTextGS( const std::string& source );
  #endif
  #ifdef RETO_TESSELATION_SHADERS
    bool loadFromTextTES( const std::string& source );
    bool loadFromTextTCS( const std::string& source );
  #endif
  #ifdef RETO_COMPUTE_SHADERS
    bool loadFromTextCS( const std::string& source );
  #endif

    bool compileAndLink( void );
    GLuint program( void );

    void use( void );
    void unuse( void );

    void addAttribute( const std::string& attr );
    void addAttributes( const std::vector<char*> attrs );
    void bindAttribute( const std::string& attr, GLuint index );
    void addUniform( const std::string& uniform );
    void addUniforms( const std::vector<char*> uniforms );
    void bindUniform( const std::string& uniform, GLuint index );
    void addUbo( const std::string& _ubo );

    #ifdef RETO_SUBPROGRAMS
      void addSubroutine( const std::string& name, GLenum shaderType );
    #endif

    GLuint attribute( const std::string& _attr );
    GLuint uniform( const std::string& _unif );
    GLuint ubo( const std::string& _ubo );
    GLuint subprogram( const std::string& name, GLenum shaderType );
    GLuint operator( )( const std::string& _attr );
    GLuint operator[]( const std::string& _unif );

    void sendUniformb( const std::string& uniform, GLboolean val );
    void sendUniformi( const std::string& uniform, GLint val );
    void sendUniformu( const std::string& uniform, GLuint val );
    void sendUniformf( const std::string& uniform, GLfloat val );

    void sendUniform( const std::string& uniform, float x, float y, float z );
    void sendUniform2v( const std::string& uniform,
                        const std::vector< float > & v );
    void sendUniform3v( const std::string& uniform,
                        const std::vector< float > & v );
    void sendUniform4v( const std::string& uniform,
                        const std::vector< float > & v );
    void sendUniform3m( const std::string& uniform,
                        const std::vector< float > & m );
    void sendUniform4m( const std::string& uniform,
                        const std::vector< float > & m,
                        GLboolean inverse = GL_FALSE );

    #ifdef RETO_SUBPROGRAMS
      void activeSubprogram( const std::string& name, GLenum shaderType );
    #endif

    #ifdef RETO_OCC_QUERY
      bool occlusionQuery( std::function<void( )> renderFunc );
    #endif

    #ifdef RETO_COMPUTE_SHADERS
      void launchComputeWork( GLuint nGx, GLuint nGy, GLuint nGz );
    #endif
    #ifdef RETO_TESSELATION_SHADERS
      GLuint getPatchVertices( void );
      GLfloat getInnerLevel( void );
      GLfloat getOuterLevel( void );

      void setPatchVertices( GLuint n );
      void setInnerLevel( GLfloat l );
      void setOuterLevel( GLfloat l );
    #endif
    #ifdef RETO_GEOMETRY_SHADERS
      GLint getGeometryMaxOutput( void );
      GLint getGeometryInputType( void );
      GLint getGeometryOutputType( void );

      void setGeometryMaxOutput( GLuint o );
      void setGeometryInputType( GLuint i );
      void setGeometryOutputType( GLuint o );
    #endif
  protected:
    void create( void );
    bool link( void );

    GLuint _program;
    std::map<std::string, GLuint> _attrsList;
    std::map<std::string, GLuint> _uniformList;
    std::map<std::string, GLuint> _uboList;

    #ifdef RETO_SUBPROGRAMS
      typedef struct SubProgram
      {
        const char* name;
        GLuint index;
        SubProgram( const char* n, GLuint i )
        {
          this->name = n;
          this->index = i;
        }
      } SubProgram;
      std::multimap<GLenum, SubProgram> _subprograms;
    #endif
    std::vector<GLuint> _shaders;

    #ifdef RETO_OCC_QUERY
      GLuint _occQuery;
    #endif
  };
}
#endif // __RETO__PROGRAM_SHADER__
