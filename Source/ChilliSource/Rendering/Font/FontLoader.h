/*
 * File: FontLoader.h
 * Date: 26/10/2010 2010 
 * Description: Loads the glyphs and the texture for fonts and caches the data
 */

/*
 * Author: Scott Downie
 * Version: v 1.0
 * Copyright ©2010 Tag Games Limited - All rights reserved 
 */

#ifndef _MO_FLO_RENDERING_FONT_LOADER_H_
#define _MO_FLO_RENDERING_FONT_LOADER_H_

#include <ChilliSource/ChilliSource.h>
#include <ChilliSource/Core/Resource/ResourceProvider.h>

namespace ChilliSource
{
	namespace Rendering
	{
		class CFontLoader : public Core::IResourceProvider
		{
		public:

			virtual ~CFontLoader();
			
			//-------------------------------------------------------------------------
			/// Is A
			///
			/// @param Interface to compare
			/// @return Whether the object implements the given interface
			//-------------------------------------------------------------------------
			bool IsA(Core::InterfaceIDType inInterfaceID) const;
			//----------------------------------------------------------------------------
			/// Can Create Resource of Kind
			///
			/// @param Type to compare
			/// @return Whether the object can create a resource of given type
			//----------------------------------------------------------------------------
			bool CanCreateResourceOfKind(Core::InterfaceIDType inInterfaceID) const;
			//----------------------------------------------------------------------------
			/// Can Create Resource From File With Extension
			///
			/// @param Type to compare
			/// @param Extension to compare
			/// @return Whether the object can create a resource with the given extension
			//----------------------------------------------------------------------------
			bool CanCreateResourceFromFileWithExtension(const std::string& inExtension) const;
			
		private:
			
			//----------------------------------------------------------------------------
			/// Create Resource From File
			///
			/// Load the font from the external file
			///
            /// @param The storage location to load from
			/// @param Filename
			/// @param Out: Resource object
			/// @return Whether the resource was created successfully
			//----------------------------------------------------------------------------
			bool CreateResourceFromFile(Core::StorageLocation ineStorageLocation, const std::string& inFilePath, Core::ResourcePtr& outpResource);
            //----------------------------------------------------------------------------
			/// Has Kerning Info
			///
			/// Returns if the font being loaded has a kerning info file
			///
            /// @param The storage location to load from
			/// @param Filename of font
			/// @return Whether a kerning info file is found
			//----------------------------------------------------------------------------
            const bool HasKerningInfo(const Core::StorageLocation ineStorageLocation, const std::string& inFilePath) const;
            //----------------------------------------------------------------------------
			/// Load Kerning Info
			///
			/// Load the font kerning information from the external file
			///
            /// @param The storage location to load from
			/// @param Filename of font
			/// @param Pointer to font resource
			/// @return Whether the resource was created successfully
			//----------------------------------------------------------------------------
            bool LoadKerningInfo(Core::StorageLocation ineStorageLocation, const std::string& inFilePath, CFont* inpFont);
		};
	}
}

#endif
