// Copyright (c) 2006-2008 Fernando Luis Cacciola Carballal. All rights reserved.
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

// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.3/Straight_skeleton_2/include/CGAL/create_straight_skeleton_from_polygon_with_holes_2.h $
// $Id: create_straight_skeleton_from_polygon_with_holes_2.h 599e201 2018-01-18T14:08:08+00:00 Andreas Fabri
// SPDX-License-Identifier: GPL-3.0+
//
// Author(s)     : Fernando Cacciola <fernando_cacciola@ciudad.com.ar>
//
#ifndef CGAL_CREATE_STRAIGHT_SKELETON_FROM_POLYGON_WITH_HOLES_2_H
#define CGAL_CREATE_STRAIGHT_SKELETON_FROM_POLYGON_WITH_HOLES_2_H

#include <CGAL/license/Straight_skeleton_2.h>

#include <CGAL/disable_warnings.h>

#include <CGAL/create_straight_skeleton_2.h>
#include <CGAL/Polygon_with_holes_2.h>

namespace CGAL {

template<class K, class C>
boost::shared_ptr< Straight_skeleton_2<K> >
inline
create_interior_straight_skeleton_2 ( Polygon_with_holes_2<K,C> const& aPolyWithHoles )
{
  return create_interior_straight_skeleton_2(aPolyWithHoles.outer_boundary().vertices_begin()
                                            ,aPolyWithHoles.outer_boundary().vertices_end  ()
                                            ,aPolyWithHoles.holes_begin   ()
                                            ,aPolyWithHoles.holes_end     ()
                                            ,K()
                                            );
}

} // end namespace CGAL

#include <CGAL/enable_warnings.h>

#endif // CGAL_STRAIGHT_SKELETON_BUILDER_2_H //
// EOF //
