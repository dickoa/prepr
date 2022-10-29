// Copyright (C) 2018  GeometryFactory Sarl
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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.3/Installation/include/CGAL/Cartesian_converter_fwd.h $
// $Id: Cartesian_converter_fwd.h 8bc315c 2018-05-03T15:05:47+02:00 Sébastien Loriot
// SPDX-License-Identifier: LGPL-3.0+
//

#ifndef CGAL_CARTESIAN_CONVERTER_FWD_H
#define CGAL_CARTESIAN_CONVERTER_FWD_H

/// \file Cartesian_converter_fwd.h
/// Forward declarations of the `Cartesian_converter` class.

#ifndef DOXYGEN_RUNNING
namespace CGAL {

namespace internal {
template < typename K1, typename K2 >
struct Default_converter;
}//internal

template < class K1, class K2,
           class Converter = typename internal::Default_converter<K1, K2>::Type >
class Cartesian_converter;

} // CGAL
#endif

#endif /* CGAL_CARTESIAN_CONVERTER_FWD_H */


