// Copyright (c) 2005 Rijksuniversiteit Groningen (Netherlands)
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org).
// You can redistribute it and/or modify it under the terms of the GNU
// General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.3/Skin_surface_3/include/CGAL/Marching_tetrahedra_observer_default_3.h $
// $Id: Marching_tetrahedra_observer_default_3.h ee57fc2 2017-10-21T01:03:14+02:00 Sébastien Loriot
// SPDX-License-Identifier: GPL-3.0+
//
//
// Author(s)     : Nico Kruithof <Nico@cs.rug.nl>

#ifndef CGAL_MARCHING_TETRAHEDRA_OBSERVER_DEFAULT_3_H
#define CGAL_MARCHING_TETRAHEDRA_OBSERVER_DEFAULT_3_H

#include <CGAL/license/Skin_surface_3.h>


#include <CGAL/basic.h>

namespace CGAL {

template <class Vertex_iterator, class Cell_iterator, class Polyhedron_3>
class Marching_tetrahedra_observer_default_3
{
public:
  typedef Polyhedron_3                        Polyhedron;

  typedef Cell_iterator                       T_Cell_iterator;
  typedef typename Polyhedron::Vertex_handle  Polyhedron_vertex_handle;
  typedef typename Polyhedron::Facet_handle   Polyhedron_facet_handle;

  Marching_tetrahedra_observer_default_3() { }
  Marching_tetrahedra_observer_default_3(const Marching_tetrahedra_observer_default_3&) { }

  void after_vertex_insertion(T_Cell_iterator, int, int, Polyhedron_vertex_handle) { }
  void after_facet_insertion(T_Cell_iterator, Polyhedron_facet_handle) { }
};

} //namespace CGAL

#endif // CGAL_MARCHING_TETRAHEDRA_OBSERVER_DEFAULT_3_H
