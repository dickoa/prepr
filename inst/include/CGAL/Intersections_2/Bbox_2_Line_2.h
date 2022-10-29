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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.3/Intersections_2/include/CGAL/Intersections_2/Bbox_2_Line_2.h $
// $Id: Bbox_2_Line_2.h 38afb85 2019-05-20T10:42:08+02:00 Mael Rouxel-Labbé
// SPDX-License-Identifier: LGPL-3.0+
// 
//
// Author(s)     : Geert-Jan Giezeman

#ifndef CGAL_INTERSECTIONS_2_BBOX_2_LINE_2_H
#define CGAL_INTERSECTIONS_2_BBOX_2_LINE_2_H

#include <CGAL/Bbox_2.h>
#include <CGAL/Line_2.h>

#include <CGAL/Intersections_2/Iso_rectangle_2_Line_2.h>

namespace CGAL {
namespace Intersections {
namespace internal {

template <class K>
bool do_intersect(const typename K::Line_2& line,
                  const CGAL::Bbox_2& bbox,
                  const K& k)
{
  typedef typename K::Iso_rectangle_2                                   Iso_rectangle_2;
  return Intersections::internal::do_intersect(line, Iso_rectangle_2(bbox), k);
}

template <class K>
bool do_intersect(const CGAL::Bbox_2& bbox,
                  const typename K::Line_2& line,
                  const K& k)
{
  return Intersections::internal::do_intersect(line, bbox, k);
}

} // namespace internal
} // namespace Intersections

template<typename K>
bool do_intersect(const CGAL::Bbox_2& bbox, const Line_2<K>& line)
{
  return K().do_intersect_2_object()(bbox, line);
}

template<typename K>
bool do_intersect(const Line_2<K>& line, const CGAL::Bbox_2& bbox)
{
  return K().do_intersect_2_object()(line, bbox);
}

} // namespace CGAL

#endif // CGAL_INTERSECTIONS_2_BBOX_2_LINE_2_H
