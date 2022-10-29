// Copyright (c) 2009 INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; either version 3 of the License,
// or (at your option) any later version.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.3/Mesher_level/include/CGAL/Mesh_optimization_return_code.h $
// $Id: Mesh_optimization_return_code.h 0698f79 2017-10-20T23:34:14+02:00 Sébastien Loriot
// SPDX-License-Identifier: LGPL-3.0+
//
//
// Author(s)     : Stephane Tayeb
//
//******************************************************************************
// File Description : 
//******************************************************************************

#ifndef CGAL_MESH_OPTIMIZATION_RETURN_CODE_H
#define CGAL_MESH_OPTIMIZATION_RETURN_CODE_H

namespace CGAL {

enum Mesh_optimization_return_code
{
  MESH_OPTIMIZATION_UNKNOWN_ERROR=-1,
  BOUND_REACHED=0,
  TIME_LIMIT_REACHED,
  CANT_IMPROVE_ANYMORE,
  CONVERGENCE_REACHED,
  MAX_ITERATION_NUMBER_REACHED,
  ALL_VERTICES_FROZEN
};


} //namespace CGAL

#endif // CGAL_MESH_OPTIMIZATION_RETURN_CODE_H
