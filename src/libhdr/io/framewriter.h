/*
 * This file is a part of LibHDR package.
 * ----------------------------------------------------------------------
 * Copyright (C) 2011 Davide Anastasia
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * ----------------------------------------------------------------------
 */

#ifndef LIBHDR_FRAMEWRITER_H
#define LIBHDR_FRAMEWRITER_H

#include <string>
#include <boost/utility.hpp>

#include "libhdr_dlldefines.h"
#include "libhdr/settings.h"
#include "libhdr/coreobject.h"

namespace LibHDR
{
class Frame; // forward declaration

//! \class FrameWrite
//! \brief Defines an interface for object that write Frame into a file
class LIBHDR_API FrameWriter:
        public CoreObject,
        public boost::noncopyable
{
public:
    FrameWriter();
    virtual ~FrameWriter();

    virtual void open(std::string filename) = 0;
    virtual bool writeFrame(const Frame& frame, const Settings& settings) = 0;
    virtual void close() = 0;

    virtual bool isOpen() = 0;
};

}

#endif // FRAMEWRITER_H
