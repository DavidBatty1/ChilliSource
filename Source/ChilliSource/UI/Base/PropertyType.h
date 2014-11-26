//
//  PropertyType.h
//  Chilli Source
//  Created by Scott Downie on 25/07/2014.
//
//  The MIT License (MIT)
//
//  Copyright (c) 2014 Tag Games Limited
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#ifndef _CHILLISOURCE_UI_BASE_PROPERTYTYPE_H_
#define _CHILLISOURCE_UI_BASE_PROPERTYTYPE_H_

#include <ChilliSource/ChilliSource.h>

namespace ChilliSource
{
	namespace UI
	{
        //----------------------------------------------------------------------------------------
        /// The supported property types for widgets
        ///
        /// @author S Downie
        //----------------------------------------------------------------------------------------
        enum class PropertyType
        {
            k_unknown,
            k_bool,
            k_int,
            k_float,
            k_string,
            k_vec2,
            k_vec3,
            k_vec4,
            k_colour,
            k_alignmentAnchor,
            k_sizePolicy,
            k_storageLocation,
            k_drawableDesc,
            k_layoutDesc
        };
        //----------------------------------------------------------------------------------------
        /// Convert the string type to internal property type
        ///
        /// @author S Downie
        ///
        /// @param Type string
        ///
        /// @return Property type
        //----------------------------------------------------------------------------------------
        PropertyType ParsePropertyType(const std::string& in_type);
	}
}

#endif
