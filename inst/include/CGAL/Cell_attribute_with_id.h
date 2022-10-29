// Copyright (c) 2017 CNRS and LIRIS' Establishments (France).
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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14.3/Combinatorial_map/include/CGAL/Cell_attribute_with_id.h $
// $Id: Cell_attribute_with_id.h 0698f79 2017-10-20T23:34:14+02:00 Sébastien Loriot
// SPDX-License-Identifier: LGPL-3.0+
//
// Author(s)     : Guillaume Damiand <guillaume.damiand@liris.cnrs.fr>
//
#ifndef CGAL_CELL_ATTRIBUTE_WITH_ID_H
#define CGAL_CELL_ATTRIBUTE_WITH_ID_H 1

#include <CGAL/Cell_attribute.h>
namespace CGAL {

  template <class, class, class, class>
  class Compact_container;

  template <class, class>
  class Concurrent_compact_container;

  namespace internal {

  template<class, class>
  struct Init_id;

  } // end namespace internal

  // A cell attribute with an id, when Info_!=void
  template <class Refs, class Info_=void, class Tag_=Tag_true,
            class OnMerge=Null_functor,
            class OnSplit=Null_functor>
  class Cell_attribute_with_id: public Cell_attribute
      <Refs, Info_, Tag_, OnMerge, OnSplit, Tag_true>
  {
    template <class, class, class, class>
    friend class Compact_container;

    template <class, class>
    friend class Concurrent_compact_container;

  protected:
    /// Default contructor.
    Cell_attribute_with_id()
    {}

    /// Contructor with an info in parameter.
    Cell_attribute_with_id(const Info_& ainfo) :
      Cell_attribute<Refs, Info_, Tag_, OnMerge, OnSplit, Tag_true>(ainfo)
    {}
  };

  /// Specialization when Info==void.
  template <class Refs, class Tag_, class OnMerge, class OnSplit>
  class Cell_attribute_with_id<Refs, void, Tag_, OnMerge, OnSplit>:
      public Cell_attribute<Refs, void, Tag_, OnMerge, OnSplit, Tag_true>
  {
    template <class, class, class, class>
    friend class Compact_container;

    template <class, class>
    friend class Concurrent_compact_container;

  protected:
    /// Default contructor.
    Cell_attribute_with_id()
    {}
  };

} // namespace CGAL

#endif // CGAL_CELL_ATTRIBUTE_WITH_ID_H //
// EOF //
