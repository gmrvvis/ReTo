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
    _attrsList.clear( );
    _uniformList.clear( );
    _uboList.clear( );
    #ifdef RETO_SUBPROGRAMS
      _subprograms.clear( );
    #endif
    _shaders.clear( );

    #ifdef RETO_OCC_QUERY
      // Occlusion query object
      glGenQueries(1, &_occQuery);
    #endif
  }

  ProgramShader::~ProgramShader(void)
  {
    destroy( );
  }

  bool ProgramShader::loadFromText( const std::string& vsSource,
                                    const std::string& fsSource )
  {
    return ( loadFromText( vsSource, GL_VERTEX_SHADER ) &&
             loadFromText( fsSource, GL_FRAGMENT_SHADER ));
  }

  bool ProgramShader::loadFromText( const std::string& source, GLenum type )
  {
    // Create and compile shader
    GLuint shader;
    shader = glCreateShader( type );
    const char* cStr = source.c_str( );
    glShaderSource(shader, 1, &cStr, nullptr );

    GLint status;
    glCompileShader( shader );
    glGetShaderiv( shader, GL_COMPILE_STATUS, &status );
    if (status == GL_FALSE )
    {
      GLint infoLogLength;
      glGetShaderiv ( shader, GL_INFO_LOG_LENGTH, &infoLogLength );
      GLchar* infoLog = new GLchar[infoLogLength];
      glGetShaderInfoLog( shader, infoLogLength, nullptr, infoLog );
      std::cerr << "Compile log: " << infoLog << std::endl;
      delete [] infoLog;
      return false;
    }

    // Add to shaders in use
    _shaders.push_back(shader);
    return true;
  }

  bool ProgramShader::loadVertexShaderFromText( const std::string& source )
  {
    return loadFromText( source, GL_VERTEX_SHADER );
  }

  bool ProgramShader::loadFragmentShaderFromText( const std::string& source )
  {
    return loadFromText( source, GL_FRAGMENT_SHADER );
  }

  #ifdef RETO_GEOMETRY_SHADERS
    bool ProgramShader::loadGeometryShaderFromText( const std::string& source )
    {
      return loadFromText( source, GL_GEOMETRY_SHADER );
    }
  #endif

  #ifdef RETO_TESSELATION_SHADERS
    bool ProgramShader::loadTesselationEvaluationShaderFromText( const std::string& source )
    {
      return loadFromText( source, GL_TESS_EVALUATION_SHADER );
    }

    bool ProgramShader::loadTesselationControlShaderFromText( const std::string& source )
    {
      return loadFromText(source, GL_TESS_CONTROL_SHADER);
    }
  #endif

  #ifdef RETO_COMPUTE_SHADERS
    bool ProgramShader::loadComputeShaderFromText( const std::string& source )
    {
      return loadFromText( source, GL_COMPUTE_SHADER );
    }
  #endif

  bool ProgramShader::load( const std::string& fileName, GLenum type )
  {
    unsigned int fileLen;

    // Load file
    std::ifstream file;
    file.open( fileName.c_str( ), std::ios::in );
    if ( !file )
    {
      std::cout << "File " << fileName << " not found" << std::endl;
      return false;
    }

    // File length
    file.seekg( 0, std::ios::end );
    fileLen = int( file.tellg( ));
    file.seekg( std::ios::beg );

    // Read the file
    char* source = new char[fileLen + 1];

    int i = 0;
    while (file.good( ))
    {
      source[i] = char( file.get( ));
      if ( !file.eof( )) i++;
      else fileLen = i;
    }
    source[fileLen] = '\0';
    file.close( );

    // Create and compile shader
    GLuint shader;
    shader = glCreateShader( type );
    glShaderSource( shader, 1, ( const GLchar** ) &source,
                    ( const GLint* ) &fileLen );

    GLint status;
    glCompileShader( shader );
    glGetShaderiv ( shader, GL_COMPILE_STATUS, &status );
    if ( status == GL_FALSE )
    {
      GLint infoLogLength;
      glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &infoLogLength );
      GLchar *infoLog= new GLchar[infoLogLength];
      glGetShaderInfoLog( shader, infoLogLength, nullptr, infoLog );
      std::cerr << "Compile log ("<< fileName << "): " << infoLog << std::endl;
      delete [] infoLog;
      return false;
    }
    delete source;

    // Add to shaders in use
    _shaders.push_back( shader );
    return true;
  }

  bool ProgramShader::load(const std::string& vsFile, const std::string& fsFile)
  {
    return ( load( vsFile, GL_VERTEX_SHADER) &&
             load( fsFile, GL_FRAGMENT_SHADER ));
  }

  bool ProgramShader::loadVertexShader( const std::string& file )
  {
    return load( file, GL_VERTEX_SHADER );
  }

  bool ProgramShader::loadFragmentShader(const std::string& file)
  {
    return load( file, GL_FRAGMENT_SHADER );
  }

  #ifdef RETO_GEOMETRY_SHADERS
    bool ProgramShader::loadGeometryShader( const std::string& file )
    {
      return load( file, GL_GEOMETRY_SHADER );
    }
  #endif

  #ifdef RETO_TESSELATION_SHADERS
    bool ProgramShader::loadTesselationEvaluationShader( const std::string& file )
    {
      return load( file, GL_TESS_EVALUATION_SHADER );
    }

    bool ProgramShader::loadTesselationControlShader( const std::string& file )
    {
      return load( file, GL_TESS_CONTROL_SHADER );
    }
  #endif

  #ifdef RETO_COMPUTE_SHADERS
    bool ProgramShader::loadComputeShader( const std::string& file )
    {
      return load( file, GL_COMPUTE_SHADER );
    }
  #endif

  void ProgramShader::destroy( void )
  {
    _program = -1;
    _attrsList.clear( );
    _uniformList.clear( );
    _uboList.clear( );

    #ifdef RETO_SUBPROGRAMS
      _subprograms.clear( );
    #endif
    _shaders.clear( );
    size_t size = _shaders.size( );
    for( size_t i = 0; i < size; ++i )
    {
      if( _shaders[i] != 0 )
      {
        glDetachShader( _program, _shaders[i] );
      }
    }
    glDeleteProgram( _program );
  }

  void ProgramShader::create( void )
  {
    _program = glCreateProgram( );
    size_t size = _shaders.size( );
    for( size_t i = 0; i < size; i++ )
    {
      if( _shaders[i] != 0 )
      {
        glAttachShader( _program, _shaders[i] );
      }
    }
  }

  bool ProgramShader::link( void )
  {
    // link and check whether the program links fine
    GLint status;
    glLinkProgram( _program );
    glGetProgramiv( _program, GL_LINK_STATUS, &status );
    if ( status == GL_FALSE )
    {
      GLint infoLogLength;

      glGetProgramiv( _program, GL_INFO_LOG_LENGTH, &infoLogLength );
      GLchar* infoLog = new GLchar[infoLogLength];
      glGetProgramInfoLog( _program, infoLogLength, nullptr, infoLog );
      std::cerr << "Link log: " << infoLog << std::endl;
      delete [] infoLog;
      return false;
    }
    return true;
  }

  void ProgramShader::use( void )
  {
    glUseProgram(_program);
  }

  void ProgramShader::unuse( void )
  {
    glUseProgram( -1 );
  }

  bool ProgramShader::compileAndLink( void )
  {
    create( );
    return link( );
  }

  GLuint ProgramShader::program( void )
  {
    return _program;
  }

  void ProgramShader::addAttribute( const std::string& attr )
  {
    _attrsList[attr] = glGetAttribLocation(_program, attr.c_str( ));
  }

  void ProgramShader::addAttributes( const std::vector<char*> attrs )
  {
    for( auto& a: attrs )
    {
      addAttribute(a);
    }
  }

  void ProgramShader::addUniform(const std::string& uniformName)
  {
    _uniformList[uniformName] =
      glGetUniformLocation( _program, uniformName.c_str( ));
  }

  void ProgramShader::addUniforms(const std::vector<char*> uniforms)
  {
    for( auto& u: uniforms )
    {
      addUniform(u);
    }
  }

  void ProgramShader::addUbo( const std::string& uboName )
  {
    _uboList[uboName] = glGetUniformBlockIndex( _program, uboName.c_str( ));
  }

  #ifdef RETO_SUBPROGRAMS
    void ProgramShader::addSubroutine( const std::string& name,
                                       GLenum shaderType )
    {
      GLuint idx = glGetSubroutineIndex( _program, shaderType, name.c_str( ));
      auto sub = SubProgram( name.c_str( ), idx );
      _subprograms.insert(std::pair<GLenum, SubProgram>(shaderType, sub));
    }
  #endif

  void ProgramShader::bindAttribute( const std::string& attr, GLuint index )
  {
    glBindAttribLocation( _program, index, attr.c_str( ));
  }

  GLuint ProgramShader::attribute( const std::string& attr )
  {
    return _attrsList[attr];
  }

  GLuint ProgramShader::operator( )(const std::string& attr )
  {
    return  attribute(attr);
  }

  GLuint ProgramShader::uniform( const std::string& uniformName )
  {
    return _uniformList[uniformName];
  }

  GLuint ProgramShader::operator []( const std::string& attr )
  {
    return  uniform( attr );
  }

  GLuint ProgramShader::ubo(const std::string& _ubo)
  {
    return _uboList[_ubo];
  }

  #ifdef RETO_SUBPROGRAMS
    GLuint ProgramShader::subprogram( const std::string& name,
                                      GLenum shaderType )
    {
      std::pair<std::multimap<GLenum, SubProgram>::iterator, std::multimap<GLenum, SubProgram>::iterator> ret;
      ret = _subprograms.equal_range( shaderType );
      for( std::multimap<GLenum, SubProgram>::iterator it = ret.first; it != ret.second; it++ ) {
        if(it->second.name == name) {
          return it->second.index;
        }
      }
      std::cerr << "Subroutine not found" << std::endl;
      return -1;
    }
  #endif

  void ProgramShader::bindUniform( const std::string& unif,
                                   GLuint idx )
  {
    if( _uniformList.find(unif) == _uniformList.end( ))
    {
      _uniformList[unif] = idx;
    }
    else
    {
      std::cerr << "Uniform exist" << std::endl;
    }
  }

  void ProgramShader::sendUniform( const std::string& uniformName,
                                   float x, float y, float z )
  {
    GLint loc = uniform( uniformName );
    glUniform3f(loc, x, y, z );
  }

  void ProgramShader::sendUniform2v( const std::string& uniformName,
                                     const std::vector< float > & v )
  {
    GLint loc = uniform( uniformName );
    glUniform2fv( loc, 1, v.data( ));
  }

  void ProgramShader::sendUniform3v( const std::string& uniformName,
                                     const std::vector< float >& v)
  {
    GLint loc = uniform( uniformName );
    glUniform3fv( loc, 1, v.data( ));
  }

  void ProgramShader::sendUniform4v( const std::string& uniformName,
                                     const std::vector< float > & v )
  {
    GLint loc = uniform( uniformName );
    glUniform4fv(loc, 1,v.data( ));
  }

  void ProgramShader::sendUniform4m(const std::string& uniformName,
    const std::vector< float > & m, GLboolean inverse)
  {
    GLint loc = uniform( uniformName );
    glUniformMatrix4fv(loc, 1, inverse, m.data( ));
  }

  void ProgramShader::sendUniform3m( const std::string& uniformName,
                                     const std::vector< float > & m )
  {
    GLint loc = uniform( uniformName );
    glUniformMatrix3fv(loc, 1, GL_FALSE, m.data( ));
  }

  void ProgramShader::sendUniformf( const std::string& uniformName,
                                    GLfloat val )
  {
    GLint loc = uniform( uniformName );
    glUniform1f( loc, val );
  }

  void ProgramShader::sendUniformi( const std::string& uniformName, GLint val )
  {
    GLint loc = uniform( uniformName );
    glUniform1i( loc, val );
  }

  void ProgramShader::sendUniformb( const std::string& uniformName,
                                    GLboolean val)
  {
    GLint loc = uniform( uniformName );
    glUniform1i( loc, val );
  }

  void ProgramShader::sendUniformu( const std::string& uniformName, GLuint val )
  {
    GLint loc = uniform( uniformName );
    glUniform1ui( loc, val );
  }

  #ifdef RETO_SUBPROGRAMS
    void ProgramShader::activeSubprogram( const std::string& name,
                                          GLenum shaderType )
    {
      std::pair<std::multimap<GLenum, SubProgram>::iterator, std::multimap<GLenum, SubProgram>::iterator> ret;
      ret = _subprograms.equal_range( shaderType );
      for( std::multimap<GLenum, SubProgram>::iterator it = ret.first; it != ret.second; it++ ) {
        if(it->second.name == name) {
          glUniformSubroutinesuiv( shaderType, 1, &it->second.index );
          return;
        }
      }
      std::cerr << "Subroutine not found" << std::endl;
    }
  #endif

  #ifdef RETO_COMPUTE_SHADERS
    void ProgramShader::launchComputeWork( GLuint numGroupX, GLuint numGroupY, 
      GLuint numGroupZ )
    {
      glDispatchCompute( numGroupX, numGroupY, numGroupZ );
    }
  #endif

  #ifdef RETO_TESSELATION_SHADERS

    GLuint ProgramShader::getPatchVertices( void )
    {
      GLint n;
      glGetIntegerv( GL_PATCH_VERTICES, &n );
      return n;
    }
    GLfloat ProgramShader::getInnerLevel( void )
    {
      GLfloat l;
      glGetFloatv( GL_PATCH_DEFAULT_INNER_LEVEL, &l );
      return l;
    }
    GLfloat ProgramShader::getOuterLevel( void )
    {
      GLfloat l;
      glGetFloatv( GL_PATCH_DEFAULT_OUTER_LEVEL, &l );
      return l;
    }

    void ProgramShader::setPatchVertices( GLuint n )
    {
      glPatchParameteri( GL_PATCH_VERTICES, n );
    }
    void ProgramShader::setInnerLevel( GLfloat l )
    {
      glPatchParameterfv( GL_PATCH_DEFAULT_INNER_LEVEL, &l );
    }
    void ProgramShader::setOuterLevel( GLfloat l )
    {
      glPatchParameterfv( GL_PATCH_DEFAULT_OUTER_LEVEL, &l );
    }
  #endif

  #ifdef RETO_OCC_QUERY
    bool ProgramShader::occlusionQuery( std::function<void( )> renderFunc )
    {
      // Disable writing to the color buffer and depth buffer.
      // We just wanna check if they would be rendered, not actually render them
      glColorMask( false, false, false, false );
      glDepthMask( GL_FALSE );
      glBeginQuery( GL_SAMPLES_PASSED, _occQuery );
      renderFunc( );
      glEndQuery( GL_SAMPLES_PASSED );
      GLint samplesPassed = 0;
      glGetQueryObjectiv( _occQuery, GL_QUERY_RESULT, &samplesPassed );
      // Re-enable writing to color buffer and depth buffer
      glColorMask( true, true, true, true );
      glDepthMask( GL_TRUE );
      return samplesPassed > 0;
    }
  #endif

  #ifdef RETO_GEOMETRY_SHADERS
    void ProgramShader::setGeometryMaxOutput( GLuint maxOutput )
    {
      glProgramParameteri( _program, GL_GEOMETRY_VERTICES_OUT, maxOutput );
    }
    void ProgramShader::setGeometryInputType( GLuint inputType )
    {
      glProgramParameteri( _program, GL_GEOMETRY_INPUT_TYPE, inputType );
    }
    void ProgramShader::setGeometryOutputType( GLuint outputType )
    {
      glProgramParameteri( _program, GL_GEOMETRY_OUTPUT_TYPE, outputType );
    }

    GLint ProgramShader::getGeometryMaxOutput( void )
    {
      GLint maxOutput;
      glGetProgramiv( _program, GL_GEOMETRY_VERTICES_OUT, &maxOutput );
      return maxOutput;
    }

    GLint ProgramShader::getGeometryInputType( void )
    {
      GLint inputType;
      glGetProgramiv( _program, GL_GEOMETRY_INPUT_TYPE, &inputType );
      return inputType;
    }

    GLint ProgramShader::getGeometryOutputType( void )
    {
      GLint outputType;
      glGetProgramiv( _program, GL_GEOMETRY_OUTPUT_TYPE, &outputType );
      return outputType;
    }
  #endif
}
