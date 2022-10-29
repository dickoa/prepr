// Copyright (c) 2009  INRIA Sophia-Antipolis (France).
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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.3/STL_Extension/include/CGAL/Location_policy.h $
// $Id: Location_policy.h 0698f79 2017-10-20T23:34:14+02:00 Sébastien Loriot
// SPDX-License-Identifier: LGPL-3.0+
//
// Author(s)     : Sylvain Pion

#ifndef CGAL_LOCATION_POLICY_H
#define CGAL_LOCATION_POLICY_H

#include <CGAL/Complexity_tags.h>

namespace CGAL {

// A policy to select the complexity of point location of a data-structure.

template < typename Tag >
struct Location_policy {};

typedef Location_policy<Fast>     Fast_location;
typedef Location_policy<Compact>  Compact_location;

} // namespace CGAL

#endif // CGAL_LOCATION_POLICY_H
