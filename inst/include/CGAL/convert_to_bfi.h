// Copyright (c) 2006-2009 Max-Planck-Institute Saarbruecken (Germany),
// INRIA Sophia-Antipolis (France).
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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.3/Interval_support/include/CGAL/convert_to_bfi.h $
// $Id: convert_to_bfi.h 0698f79 2017-10-20T23:34:14+02:00 Sébastien Loriot
// SPDX-License-Identifier: LGPL-3.0+
//
// Author(s)     : Michael Hemmer   <hemmer@mpi-inf.mpg.de>



#ifndef CGAL_CONVERT_TO_BFI_H
#define CGAL_CONVERT_TO_BFI_H

#include <CGAL/basic.h>
#include <CGAL/Get_arithmetic_kernel.h>
#include <CGAL/Cache.h>

namespace CGAL {

template <class NTX>
typename Get_arithmetic_kernel<NTX>::Arithmetic_kernel::Bigfloat_interval
convert_to_bfi(const NTX& x) {
    typedef typename Get_arithmetic_kernel<NTX>::Arithmetic_kernel AK;
    typedef typename AK::Bigfloat_interval BFI; 
    typedef CGAL::Coercion_traits<NTX,BFI> CT;
    return typename CT::Cast()(x);
}

} //namespace CGAL 

#endif // CGAL_CONVERT_TO_BFI_H
