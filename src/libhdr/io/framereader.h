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

#ifndef LIBHDR_ISTRATEGYREADER
#define LIBHDR_ISTRATEGYREADER

#include <string>

#include "libhdr_dlldefines.h"
#include "libhdr/io/iocommon.h"
#include "libhdr/coreobject.h"
//#include "libhdr/frame.h"
#include "libhdr/settings.h"

#include "libhdr/template/objectfactory.h"
#include "libhdr/template/singleton.h"

namespace LibHDR
{

class Frame;

namespace IO
{

class LIBHDR_API FrameReader: public CoreObject
{
public:
    FrameReader(); // cstr
    virtual ~FrameReader();

    virtual void open(std::string filename) = 0;
    virtual Frame* readFrame(const Settings& settings) = 0;
    virtual void close() = 0;

    virtual bool isOpen() = 0;
};

typedef Template::Singleton< Template::ObjectFactory<FrameReader, std::string> > FrameReaderFactory;

template<typename Type>
bool subscribe2factory()
{
    bool status = true;
    // get pointer to FrameReaderFactory
    FrameReaderFactory::HoldType& factory = FrameReaderFactory::instance();

    // every class subscribed to FrameReaderFactory must expose this method
    std::vector<std::string> id_ = Type::getID();

    for (std::vector<std::string>::size_type idx = 0; idx < id_.size(); ++idx)
    {
        if ( !factory.subscribe(id_[idx], LibHDR::Template::createInstance<FrameReader, Type>) )
            status = false;
    }
    return status;
}

#define REGISTER_FRAMEREADER(reader) \
    static bool factory_subscription##reader = subscribe2factory<reader>();


} // end namespace IO
} // end namespace LibHDR

#endif // LIBHDR_ISTRATEGYREADER
