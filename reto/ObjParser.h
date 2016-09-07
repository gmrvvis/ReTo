/*
 * Copyright (c) 2014-2016 GMRV/URJC.
 *
 * Authors: Cristian Rodríguez Bernal
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

#ifndef __RETO_OBJPARSER__
#define __RETO_OBJPARSER__

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>

namespace reto {
	struct Model {
		std::vector<float> vertices;
		std::vector<float> normals;
		std::vector<int> indices;
		std::vector<float> texCoords;
		std::vector<float> tangents;
		std::vector<float> bitangents;
	};
	class ObjParser
	{
	public:
		ObjParser( void );
		Model loadObj(std::string filename, bool calculateTang = false,
			bool calculateBitang = false);
	protected:
		/*
			Load all file content
			@param std::string filename
			@return std::string
		*/
		std::string loadFile(std::string filename);
		/*
			Split string by character separator
			@param string line
			@param char c
			@return std::vector<std::string>
		*/
		std::vector<std::string> split(const std::string& s, char c);
		bool isNumeric(const std::string& input);
		bool isFloat(std::string& myString);
		std::vector<float> splitLineToFloats(std::string& line);
		std::string trim(std::string str);
		std::vector<int> splitFace(std::string& line);
	};
}

#endif /* __RETO_OBJPARSER__ */
