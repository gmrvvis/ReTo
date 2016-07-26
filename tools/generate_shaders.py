#!/usr/bin/python

from optparse import OptionParser
import sys, getopt
import os, re
from string import Template

tmpl = """#ifndef $header
#define $header

namespace $namespace
{
$tmpl
};

#endif /* $header */
"""

def first_lower(s):
  if len(s) == 0:
    return s
  else:
    return s[0].lower() + s[1:]

def rchop(str_, ending):
  if str_.endswith(ending):
    return str_[:-len(ending)]
  return str_

set_vars = set()

def recreateFile( path ):
  list = []
  for root, subdirectory, files in os.walk( path ):
    for file in files:
      list += read_file( root, file, path, False )
  del list[-1]
  set_vars.clear( )
  return list

def read_file( root, file, path, import_file ):
  list = []
  if not import_file and file[0] == "_":
    return []
  var_name = os.path.relpath( os.path.join( root, file ), path ).replace( "\\", "_" )       # Get parent directory name. "" if directory as path
  var_name = rchop( var_name, ".glsl" ).replace( ".", "_" ).replace( " ", "_ ")               # Remove ".glsl" and replace "." and " " to "_"
  content = []

  try:
    f = open( os.path.join(root, file ) )
    for line in f:
      v = re.match(r'#include\(\"(.+?)\"\)', line)
      if not v is None:
        content += read_file( root, v.group(1), path, True )
      else:
        content.append( line.rstrip( '\n' ) )
    f.close( )
  except IOError as e:
    print("'" + file + "' not found")
    return []

  content = '\\n"\n  "'.join( content )
  if not import_file:
    var_name = first_lower( var_name )
    if var_name in set_vars:
      #raise ValueError("Var_name exist") 
      print var_name + " repeated ..."
      return []
    set_vars.add( var_name )
    list.append( "  static const char* " + var_name + " = " )
    list.append( '"' + content + '";' )
    list.append( "\n\n" )
  else:
    list.append( content + "\\n" )
  return list

def parse_cli( ):
  parser = OptionParser( )
  parser.add_option("-d", "--declaration", dest="declaration",
                    help="Header declaration (without H)")
  parser.add_option("-n", "--namespace", dest="namespace",
                    help="header namespace")
  parser.add_option("-r", "--route",  dest="route", default=".",
                    help="sources directory")
  parser.add_option("-f", "--file",  dest="fileOutput", default="exit.h",
                    help="file output")

  ( options, args ) = parser.parse_args( )
  defaults = vars( parser.get_default_values( ) )
  optionsdict = vars( options )

  all_none = False        
  for k, v in optionsdict.items( ):
    if v is None and defaults.get( k ) is None:
      all_none = True


  if all_none:
    print 'python generate_shaders.py -r "route" -n "namespace" -d "RETO" -f "file.h"'
    parser.print_help( )
    sys.exit( )
  return optionsdict

if __name__ == "__main__":
  opts = parse_cli( )
  src = Template( tmpl )
  
  list = recreateFile( opts["route"] )

  str_ = ''.join(str(x) for x in list) 

  header = opts["declaration"] + "_H"

  d = { 
    "tmpl": str_, 
    "namespace": opts["namespace"], 
    "header" : header.upper( ) 
  }
  code = src.substitute( d )

  file = open(opts["fileOutput"], "w")
  file.write( code )
  file.close( )
  print "FINISH"