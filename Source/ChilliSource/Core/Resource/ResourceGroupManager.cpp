/*
 * File: ResourceGroupManager.cpp
 * Date: 11/11/2010 2010 
 * Description: 
 */

/*
 * Author: Scott Downie
 * Version: v 1.0
 * Copyright ©2010 Tag Games Limited - All rights reserved 
 */

#include <ChilliSource/Core/Resource/ResourceGroupManager.h>
#include <ChilliSource/Core/Resource/ResourceManager.h>
#include <ChilliSource/Core/Resource/ResourceManagerDispenser.h>
#include <ChilliSource/Core/String/StringUtils.h>
#include <ChilliSource/Core/Image/Image.h>
#include <ChilliSource/Core/Base/Application.h>

#include <unordered_map>
#include <vector>

namespace ChilliSource
{
	namespace Core
	{
		//-----------------------------------------------------
		/// Constructor
		///
		/// Default
		//-----------------------------------------------------
		IResourceGroupManager::IResourceGroupManager(CResourceManagerDispenser* inpResMgrDispenser) 
		: mpResMgrDispenser(inpResMgrDispenser)
		{

		}
		//-----------------------------------------------------
		/// Create Group
		///
		/// Create a new resource group with the given name
		/// @param Group name (must be unique)
		/// @param Folder directory that houses resources
		//-----------------------------------------------------
		void IResourceGroupManager::CreateGroup(const std::string& instrGroupName, const std::string& instrDirectory)
		{
			MapStringToResourceGroupItr pExistingResource = mMapNameToResourceGroup.find(instrGroupName);
			
			//Check the pool to see if this resource group already exists
			if(pExistingResource == mMapNameToResourceGroup.end()) 
			{
				CS_DEBUG_LOG("Creating resource group " + instrGroupName + " for directory " + instrDirectory);
				ResourceGroupPtr pGroup(new CResourceGroup());
				pGroup->mstrDirectory = instrDirectory;
				
				mMapNameToResourceGroup.insert(std::make_pair(instrGroupName, pGroup));
				return;
			} 
			
			//Duplicate resource group
			CS_ERROR_LOG("Resource group " + instrGroupName + " with directory " + instrDirectory + " cannot be created as it already exists");
		}
		//-----------------------------------------------------
		/// Load Group
		///
		/// Load the resources inside the given groups 
		/// directory. This will load them into the relative
		/// resource managers resource pool
		//-----------------------------------------------------
		void IResourceGroupManager::LoadGroup(const std::string& instrGroupName)
		{
			MapStringToResourceGroupItr pExistingResource = mMapNameToResourceGroup.find(instrGroupName);
			
			//Check the pool to see if this resource group already exists
			if(pExistingResource == mMapNameToResourceGroup.end()) 
			{
				CS_ERROR_LOG("Loading resource group " + instrGroupName + " cannot be found");
				return;
			} 
			
			//Check we don't load twice!
			if(pExistingResource->second->meCurrentStatus == CResourceGroup::Status::k_notLoaded)
			{
				CS_DEBUG_LOG("Loading resource group " + instrGroupName + "...");
				//Get the file names within that directory
				std::vector<std::string> FileNames;
				CApplication::GetFileSystemPtr()->GetFileNamesInDirectory(StorageLocation::k_package, pExistingResource->second->mstrDirectory, true, FileNames);
				
				//Load this bad boy. 
				for(std::vector<std::string>::const_iterator it = FileNames.begin(); it != FileNames.end(); ++it)
				{
					std::string strName;
					std::string strExtension;
					
					//Get the extension of each file in the directory.
					CStringUtils::SplitBaseFilename((*it), strName, strExtension);
					
					//Do we have a resource manager that can handle this?
					IResourceManager* pResMgr = mpResMgrDispenser->GetResourceManagerForExtension(strExtension);
					
					if(!pResMgr)
					{
						CS_ERROR_LOG("Cannot load file  " + (*it) + " in resource group " + instrGroupName);
						continue;
					}
					
					//Lock 'n' load. Tell the resource manager to load the resource into it's cache!
					//Now they can be accesed via the resource manager with no loading time
					//We should also track the resource and it's owning manager so that we can free the resource later
					pExistingResource->second->mResources.push_back(pResMgr->GetResourceFromFile(StorageLocation::k_package, *it));
				}
				
				//Flag this loaded
				pExistingResource->second->meCurrentStatus = CResourceGroup::Status::k_loaded;
				CS_DEBUG_LOG("Loading resource group " + instrGroupName + " complete\n");
			}
		}
		//-----------------------------------------------------
		/// Unload Group
		///
		/// Free the resources inside the given groups 
		/// directory but hold on to the group.
		//-----------------------------------------------------
		void IResourceGroupManager::UnloadGroup(const std::string& instrGroupName)
		{
			MapStringToResourceGroupItr pExistingResource = mMapNameToResourceGroup.find(instrGroupName);
			
			//Check the pool to see if this resource group already exists
			if(pExistingResource != mMapNameToResourceGroup.end()) 
			{
				CS_DEBUG_LOG("Unloading resource group " + instrGroupName);
				pExistingResource->second->meCurrentStatus = CResourceGroup::Status::k_notLoaded;
				
				//Tell the resource manager to unload the object from it's cache
				for(std::vector<ResourcePtr>::iterator it = pExistingResource->second->mResources.begin(); it != pExistingResource->second->mResources.end(); ++it)
				{
					(*it)->Release();
				}
				
				pExistingResource->second->mResources.clear();
				return;
			} 
			
			CS_ERROR_LOG("Unloading resource group " + instrGroupName + " cannot be found");			
		}
		//-----------------------------------------------------
		/// Destroy Group
		///
		/// Free the resources inside the given groups 
		/// directory and remove the group from the set
		//-----------------------------------------------------
		void IResourceGroupManager::DestroyGroup(const std::string& instrGroupName)
		{
			MapStringToResourceGroupItr pExistingResource = mMapNameToResourceGroup.find(instrGroupName);
			
			//Check the pool to see if this resource group already exists
			if(pExistingResource != mMapNameToResourceGroup.end()) 
			{
				UnloadGroup(instrGroupName);
				CS_DEBUG_LOG("Destroying resource group " + instrGroupName);
				mMapNameToResourceGroup.erase(pExistingResource);
				return;
			} 
			
			CS_ERROR_LOG("Destroying resource group " + instrGroupName + " cannot be found");
		}
		//-----------------------------------------------------
		/// Invalidate Cache
		///
		/// The system will let us know that all our groups 
		/// resources have been freed. We will need to load 
		/// them again on request
		//-----------------------------------------------------
		void IResourceGroupManager::InvalidateCache()
		{
			for(MapStringToResourceGroupItr it = mMapNameToResourceGroup.begin(); it != mMapNameToResourceGroup.end(); ++it)
			{
				it->second->meCurrentStatus = CResourceGroup::Status::k_notLoaded;
				it->second->mResources.clear();
			}
		}
		//-----------------------------------------------------
		/// Unload All 
		///
		/// Free all the resources for our groups. 
		//-----------------------------------------------------
		void IResourceGroupManager::UnloadAll()
		{
			for(MapStringToResourceGroupItr it = mMapNameToResourceGroup.begin(); it != mMapNameToResourceGroup.end(); ++it)
			{
				it->second->meCurrentStatus = CResourceGroup::Status::k_notLoaded;
				//Tell the resource manager to let it go!
				for(std::vector<ResourcePtr>::iterator jt = it->second->mResources.begin(); jt != it->second->mResources.end(); ++jt)
				{
					(*jt)->Release();
				}
				
				it->second->mResources.clear();
			}
		}
		//-----------------------------------------------------
		/// Destroy All 
		///
		/// Free all the resources for our groups and remove
		/// the groups from the set
		//-----------------------------------------------------
		void IResourceGroupManager::DestroyAll()
		{
			UnloadAll();
			mMapNameToResourceGroup.clear();
		}
		//-----------------------------------------------------
		/// Destructor
		///
		//-----------------------------------------------------
		IResourceGroupManager::~IResourceGroupManager()
		{
			DestroyAll();
		}
	}
}

