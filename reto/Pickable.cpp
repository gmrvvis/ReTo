/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Cristian Rodríguez Bernal <cristian.rodriguez@urjc.es>
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

#include "Pickable.h"

namespace reto
{
  Pickable::Pickable( void )
  {}

  Pickable::~Pickable( void )
  {}

  unsigned int Pickable::sendId ( unsigned int currentOffset )
  {
    // sendUniform
    return currentOffset += _numIds;
  }
  void Pickable::setNumIDs ( int numIds )
  {
    _numIds = numIds;
  }  

  int Pickable::getId( void ) const
  {
    return _id;
  }

  void Pickable::setId( const int& id )
  {
    _id = id;
  }

};
