// Copyright (c) 2010 GeometryFactory (France).
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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.3/Intersections_3/include/CGAL/Intersections_3/Bbox_3_Iso_cuboid_3.h $
// $Id: Bbox_3_Iso_cuboid_3.h 1622410 2018-05-17T11:52:58+01:00 Andreas Fabri
// SPDX-License-Identifier: LGPL-3.0+
//
//
// Author(s)     : Sebastien Loriot
//

#ifndef CGAL_INTERSECTIONS_3_BBOX_3_ISO_CUBOID_3_H
#define CGAL_INTERSECTIONS_3_BBOX_3_ISO_CUBOID_3_H

#include <CGAL/Bbox_3.h>
#include <CGAL/Iso_cuboid_3.h>

#include <CGAL/Intersections_3/internal/Bbox_3_Iso_cuboid_3_do_intersect.h>

namespace CGAL {

template<typename K>
bool do_intersect(const CGAL::Bbox_3& a,
                  const Iso_cuboid_3<K>& b) {
  return K().do_intersect_3_object()(a, b);
}

template<typename K>
bool do_intersect(const Iso_cuboid_3<K>& a,
                  const CGAL::Bbox_3& b) {
  return K().do_intersect_3_object()(b, a);
}

} // namespace CGAL

#endif // CGAL_INTERSECTIONS_3_BBOX_3_ISO_CUBOID_3_H
