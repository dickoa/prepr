// Copyright (c) 2000  
// Utrecht University (The Netherlands),
// ETH Zurich (Switzerland),
// INRIA Sophia-Antipolis (France),
// Max-Planck-Institute Saarbruecken (Germany),
// and Tel-Aviv University (Israel).  All rights reserved. 
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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.3/Intersections_2/include/CGAL/Intersections_2/Circle_2_Circle_2.h $
// $Id: Circle_2_Circle_2.h ab0ca8a 2019-05-17T12:15:48+02:00 Mael Rouxel-Labbé
// SPDX-License-Identifier: LGPL-3.0+
// 
//
// Author(s)     : Geert-Jan Giezeman

#ifndef CGAL_INTERSECTIONS_2_CIRCLE_2_CIRCLE_2_H
#define CGAL_INTERSECTIONS_2_CIRCLE_2_CIRCLE_2_H

#include <CGAL/Circle_2.h>
#include <CGAL/squared_distance_2_1.h>

#include <CGAL/Intersection_traits_2.h>

namespace CGAL {
namespace Intersections {
namespace internal {

template <class K>
bool do_intersect(const typename K::Circle_2 & circ1,
                  const typename K::Circle_2& circ2,
                  const K&)
{
  typedef typename K::FT FT;

  FT sr1 = circ1.squared_radius();
  FT sr2 = circ2.squared_radius();
  FT squared_dist = squared_distance(circ1.center(), circ2.center());
  FT temp = sr1+sr2-squared_dist;

  return !(FT(4)*sr1*sr2 < temp*temp);
}

} // namespace internal
} // namespace Intersections

CGAL_DO_INTERSECT_FUNCTION_SELF(Circle_2, 2)

} // namespace CGAL

#endif
