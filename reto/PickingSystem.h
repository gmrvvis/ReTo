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
#ifndef __RETO__PICKING_SYSTEM__
#define __RETO__PICKING_SYSTEM__

#include <vector>
#include "ProgramShader.h"

#include <vector>
#include <set>
#include "ProgramShader.h"
#include "Camera.h"
#include "Pickable.h"

#include <reto/api.h>

namespace reto
{
  typedef struct {
    int x;
    int y;
  } Point;
  // TODO: Usar eigen

  class PickingSystem
  {
  public:
    RETO_API
    PickingSystem( reto::Camera* camera );
    virtual ~PickingSystem( );

    RETO_API
    void AddObject( Pickable * p );
    RETO_API
    void RemoveObject( Pickable * p );
    RETO_API
    void Clear( void );

    /**
     * Method to find front object in a specific point
     * @param point: Point
     * @return int: Indice that is visible
     */
    RETO_API
    int click( Point point );


    /**
     * Method to find front object in a specific area
     * @param minPoint: minPoint
     * @param maxPoint: maxPoint
     * @return std::set<unsigned int> Indices that objects are visibles
     */
    RETO_API
    std::set<unsigned int> area( Point minPoint, Point maxPoint );

    protected:
      reto::ProgramShader _program;
      std::set< Pickable* > _objects;
      reto::Camera* _camera;
      
      virtual std::string getVertexCode( );
  };
}

#endif // __RETO__PICKING_SYSTEM__
