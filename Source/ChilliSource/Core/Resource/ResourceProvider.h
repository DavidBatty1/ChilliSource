/*
 *  ResourceProvider.h
 *  MoFlow
 *
 *  Created by Tag Games on 30/09/2010.
 *  Copyright 2010 Tag Games. All rights reserved.
 *
 */

#ifndef _MOFLO_CORE_RESOURCEPROVIDER_H_
#define _MOFLO_CORE_RESOURCEPROVIDER_H_

#include <ChilliSource/ChilliSource.h>
#include <ChilliSource/Core/System/System.h>
#include <ChilliSource/Core/Base/QueryableInterface.h>
#include <ChilliSource/Core/Resource/Resource.h>
#include <ChilliSource/Core/File/FileSystem.h>

namespace ChilliSource
{
	namespace Core
	{
		/// ResourceProvider defines an interface for systems which produce resource objects from files
		class ResourceProvider : public System
		{
		public:
			virtual ~ResourceProvider(){}
			DECLARE_NAMED_INTERFACE(ResourceProvider);
			virtual bool CanCreateResourceOfKind(InterfaceIDType inInterfaceID) const = 0;
			virtual bool CanCreateResourceFromFileWithExtension(const std::string & inExtension) const = 0;
			
			//---Filepath is relative to the resources directory - either the documents or the package
			virtual bool CreateResourceFromFile(StorageLocation ineStorageLocation, const std::string & inFilePath, ResourceSPtr& outpResource) = 0;
			virtual bool AsyncCreateResourceFromFile(StorageLocation ineStorageLocation, const std::string & inFilePath, ResourceSPtr& outpResource)
            {
                CS_LOG_WARNING("No implementation for AsyncCreateResourceFromFile"); 
                return false;
            };
			virtual bool StreamResourceFromFile(StorageLocation ineStorageLocation, const std::string & inFilePath, ResourceSPtr& outpResource)
            {
                CS_LOG_WARNING("No implementation for StreamResourceFromFile"); 
                return false;
            }
			

		};
	}	
}

#endif