// Copyright (c) 2007  Max-Planck-Institute Saarbruecken (Germany).
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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.3/STL_Extension/include/CGAL/type_traits.h $
// $Id: type_traits.h 0698f79 2017-10-20T23:34:14+02:00 Sébastien Loriot
// SPDX-License-Identifier: LGPL-3.0+
//
// Author(s)     : Andreas Meyer

#ifndef CGAL_TYPE_TRAITS_H
#define CGAL_TYPE_TRAITS_H

#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/mpl/or.hpp>

namespace CGAL {

template< class Base, class Derived >
struct is_same_or_derived :
  public ::boost::mpl::or_<
    ::boost::is_same< Base, Derived >,
    ::boost::is_base_and_derived< Base, Derived >
  >::type
{};

}

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS) && !defined(BOOST_NO_0X_HDR_TYPE_TRAITS)
#include <type_traits>
namespace CGAL {
namespace cpp11{
  using std::is_enum;
} }
#else
#include <boost/type_traits/is_enum.hpp>
namespace CGAL {
namespace cpp11 {
  using boost::is_enum;
}
}
#endif

#endif // CGAL_TYPE_TRAITS_H
