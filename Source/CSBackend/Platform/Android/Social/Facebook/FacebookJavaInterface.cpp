//
//  FacebookJavaInterface.cpp
//  Chilli Source
//  Created by Robert Henning on 01/05/2012.
//
//  The MIT License (MIT)
//
//  Copyright (c) 2012 Tag Games Limited
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

#ifdef CS_TARGETPLATFORM_ANDROID

#include <CSBackend/Platform/Android/Social/Facebook/FacebookJavaInterface.h>

#include <CSBackend/Platform/Android/Core/JNI/JavaInterfaceUtils.h>
#include <CSBackend/Platform/Android/Core/JNI/JavaInterfaceManager.h>
#include <CSBackend/Platform/Android/Social/Facebook/FacebookAuthenticationSystem.h>
#include <CSBackend/Platform/Android/Social/Facebook/FacebookPostSystem.h>
#include <ChilliSource/Core/Base/Application.h>
#include <ChilliSource/Core/Threading/TaskScheduler.h>

#include <jni.h>

CSBackend::Android::FacebookAuthenticationSystem* gpAndroidAuthSystem = nullptr;
CSBackend::Android::FacebookPostSystem* gpAndroidPostSystem = nullptr;

//function definitions
extern "C"
{
	void Java_com_chilliworks_chillisource_social_FacebookNativeInterface_OnAuthenticationComplete(JNIEnv* inpEnv, jobject inpThis, bool inbSuccess);
	void Java_com_chilliworks_chillisource_social_FacebookNativeInterface_OnReadAuthorisationComplete(JNIEnv* inpEnv, jobject inpThis, bool inbSuccess);
	void Java_com_chilliworks_chillisource_social_FacebookNativeInterface_OnWriteAuthorisationComplete(JNIEnv* inpEnv, jobject inpThis, bool inbSuccess);
	void Java_com_chilliworks_chillisource_social_FacebookNativeInterface_OnPostToFeedComplete(JNIEnv* inpEnv, jobject inpThis, s32 in_result);
	void Java_com_chilliworks_chillisource_social_FacebookNativeInterface_OnPostRequestComplete(JNIEnv* inpEnv, jobject inpThis, s32 in_result);
}

//------------------------------------------------------------
// (Java) OnAuthenticationComplete
//
// Calls when authentication has been achieved either through login or an existing session
//
// @param Java environment
// @param The java object calling the function
// @param The success of the authentication
//------------------------------------------------------------
void Java_com_chilliworks_chillisource_social_FacebookNativeInterface_OnAuthenticationComplete(JNIEnv* inpEnv, jobject inpThis, bool inbSuccess)
{
	if(gpAndroidAuthSystem)
	{
		CSCore::Application::Get()->GetTaskScheduler()->ScheduleMainThreadTask(std::bind(&CSBackend::Android::FacebookAuthenticationSystem::OnAuthenticationComplete, gpAndroidAuthSystem, inbSuccess));
	}
}
//------------------------------------------------------------
// (Java) OnReadAuthorisationComplete
//
// Calls when the read permissions have been authorised via facebook
//
// @param Java environment
// @param The java object calling the function
// @param The success of the authorised
//------------------------------------------------------------
void Java_com_chilliworks_chillisource_social_FacebookNativeInterface_OnReadAuthorisationComplete(JNIEnv* inpEnv, jobject inpThis, bool inbSuccess)
{
	if(gpAndroidAuthSystem)
	{
		CSCore::Application::Get()->GetTaskScheduler()->ScheduleMainThreadTask(std::bind(&CSBackend::Android::FacebookAuthenticationSystem::OnAuthoriseReadPermissionsComplete, gpAndroidAuthSystem, inbSuccess));
	}
}
//------------------------------------------------------------
// (Java) OnWriteAuthorisationComplete
//
// Calls when the write permissions have been authorised via facebook
//
// @param Java environment
// @param The java object calling the function
// @param The success of the authorised
//------------------------------------------------------------
void Java_com_chilliworks_chillisource_social_FacebookNativeInterface_OnWriteAuthorisationComplete(JNIEnv* inpEnv, jobject inpThis, bool inbSuccess)
{
	if(gpAndroidAuthSystem)
	{
		CSCore::Application::Get()->GetTaskScheduler()->ScheduleMainThreadTask(std::bind(&CSBackend::Android::FacebookAuthenticationSystem::OnAuthoriseWritePermissionsComplete, gpAndroidAuthSystem, inbSuccess));
	}
}
//------------------------------------------------------------
// (Java) OnPostToFeedComplete
//
// Calls when the results of the attempt to post to feed are received
//
// @param Java environment
// @param The java object calling the function
// @param The result of the authorised
//------------------------------------------------------------
void Java_com_chilliworks_chillisource_social_FacebookNativeInterface_OnPostToFeedComplete(JNIEnv* inpEnv, jobject inpThis, s32 in_result)
{
	if(gpAndroidPostSystem)
	{
		CSSocial::FacebookPostSystem::PostResult result = CSSocial::FacebookPostSystem::PostResult::k_failed;
		switch(in_result)
		{
		case 0:
			result = CSSocial::FacebookPostSystem::PostResult::k_success;
			break;
		case 1:
			result = CSSocial::FacebookPostSystem::PostResult::k_cancelled;
			break;
		default:
			result = CSSocial::FacebookPostSystem::PostResult::k_failed;
			break;
		}

		CSCore::Application::Get()->GetTaskScheduler()->ScheduleMainThreadTask(std::bind(&CSBackend::Android::FacebookPostSystem::OnPostToFeedComplete, gpAndroidPostSystem, result));
	}
}
//------------------------------------------------------------
// (Java) OnPostRequestComplete
//
// Calls when the results of the attempt to post a request are received
//
// @param Java environment
// @param The java object calling the function
// @param The result of the authorised
//------------------------------------------------------------
void Java_com_chilliworks_chillisource_social_FacebookNativeInterface_OnPostRequestComplete(JNIEnv* inpEnv, jobject inpThis, s32 in_result)
{
	if(gpAndroidPostSystem)
	{
		CSSocial::FacebookPostSystem::PostResult result = CSSocial::FacebookPostSystem::PostResult::k_failed;
		switch(in_result)
		{
		case 0:
			result = CSSocial::FacebookPostSystem::PostResult::k_success;
			break;
		case 1:
			result = CSSocial::FacebookPostSystem::PostResult::k_cancelled;
			break;
		default:
			result = CSSocial::FacebookPostSystem::PostResult::k_failed;
			break;
		}

		CSCore::Application::Get()->GetTaskScheduler()->ScheduleMainThreadTask(std::bind(&CSBackend::Android::FacebookPostSystem::OnPostRequestComplete, gpAndroidPostSystem, result));
	}
}


namespace CSBackend
{
	namespace Android
	{
		CS_DEFINE_NAMEDTYPE(FacebookJavaInterface);

		FacebookJavaInterface::FacebookJavaInterface()
		{
			CreateNativeInterface("com/chilliworks/chillisource/social/FacebookNativeInterface");

			CreateMethodReference("Authenticate", "([Ljava/lang/String;)V");
			CreateMethodReference("IsSignedIn", "()Z");
			CreateMethodReference("GetActiveToken", "()Ljava/lang/String;");
			CreateMethodReference("HasPermission", "(Ljava/lang/String;)Z");
			CreateMethodReference("AuthoriseReadPermissions", "([Ljava/lang/String;)V");
			CreateMethodReference("AuthoriseWritePermissions", "([Ljava/lang/String;)V");
			CreateMethodReference("SignOut", "()V");
			CreateMethodReference("MakePostToFeedRequest", "(Ljava/lang/String;[Ljava/lang/String;)V");
			CreateMethodReference("MakeRequestToUser", "([Ljava/lang/String;)V");
		}

		bool FacebookJavaInterface::IsA(CSCore::InterfaceIDType inInterfaceID) const
		{
			return inInterfaceID == FacebookJavaInterface::InterfaceID;
		}

		//--------------------------------------------------------------------------------------
		/// Set Authentication System
		///
		/// Used to callback into the auth system
		///
		/// @param Auth system
		//--------------------------------------------------------------------------------------
		void FacebookJavaInterface::SetAuthenticationSystem(FacebookAuthenticationSystem* inpAuthSystem)
		{
			gpAndroidAuthSystem = inpAuthSystem;
		}
		//--------------------------------------------------------------------------------------
		/// Set Post System
		///
		/// Used to callback into the post system
		///
		/// @param Post system
		//--------------------------------------------------------------------------------------
		void FacebookJavaInterface::SetPostSystem(FacebookPostSystem* inpPostSystem)
		{
			gpAndroidPostSystem = inpPostSystem;
		}
		//--------------------------------------------------------------------------------------
		/// Authenticate
		///
		/// Attempt to open an existing session or prompt the user to login if no
		/// session exists
		//--------------------------------------------------------------------------------------
		void FacebookJavaInterface::Authenticate(const std::vector<std::string>& inaReadPerms)
		{
			JNIEnv* pEnv = CSBackend::Android::JavaInterfaceManager::GetSingletonPtr()->GetJNIEnvironmentPtr();
			jstring jstrEmptyString = pEnv->NewStringUTF("");
			jclass jStringClass = pEnv->FindClass("java/lang/String");
	    	jobjectArray jaPermissions = pEnv->NewObjectArray(inaReadPerms.size(), jStringClass, jstrEmptyString);
	    	u32 udwPermissionCount = 0;
	    	for(std::vector<std::string>::const_iterator it = inaReadPerms.begin(); it != inaReadPerms.end(); ++it)
	    	{
	    		jstring jstrPermission = JavaInterfaceUtils::CreateJStringFromSTDString((*it));
	    		pEnv->SetObjectArrayElement(jaPermissions, udwPermissionCount, jstrPermission);
	    		pEnv->DeleteLocalRef(jstrPermission);
	    		++udwPermissionCount;
	    	}

	    	pEnv->CallVoidMethod(GetJavaObject(), GetMethodID("Authenticate"), jaPermissions);
	    	pEnv->DeleteLocalRef(jstrEmptyString);
	    	pEnv->DeleteLocalRef(jStringClass);
	    	pEnv->DeleteLocalRef(jaPermissions);
		}
		//--------------------------------------------------------------------------------------
		/// Is Signed In
		///
		/// @return Whether a session exists and is open
		//--------------------------------------------------------------------------------------
		bool FacebookJavaInterface::IsSignedIn()
		{
			JNIEnv* pEnv = CSBackend::Android::JavaInterfaceManager::GetSingletonPtr()->GetJNIEnvironmentPtr();
			return pEnv->CallBooleanMethod(GetJavaObject(), GetMethodID("IsSignedIn"));
		}
		//--------------------------------------------------------------------------------------
		/// Get Active Token
		///
		/// @return The access token of the active session
		//--------------------------------------------------------------------------------------
		std::string FacebookJavaInterface::GetActiveToken()
		{
			JNIEnv* pEnv = CSBackend::Android::JavaInterfaceManager::GetSingletonPtr()->GetJNIEnvironmentPtr();
			jstring jstrToken = (jstring)pEnv->CallObjectMethod(GetJavaObject(), GetMethodID("GetActiveToken"));
			std::string strToken = CSBackend::Android::JavaInterfaceUtils::CreateSTDStringFromJString(jstrToken);
			pEnv->DeleteLocalRef(jstrToken);
			return strToken;
		}
		//--------------------------------------------------------------------------------------
		/// Has Permission
		///
		/// @param Permission ID
	    /// @return Whether the current session user has given the permission
		//--------------------------------------------------------------------------------------
	    bool FacebookJavaInterface::HasPermission(const std::string& instrPermission)
	    {
			JNIEnv* pEnv = CSBackend::Android::JavaInterfaceManager::GetSingletonPtr()->GetJNIEnvironmentPtr();
			jstring jstrPermission = CSBackend::Android::JavaInterfaceUtils::CreateJStringFromSTDString(instrPermission);
			bool bHasPermission = pEnv->CallBooleanMethod(GetJavaObject(), GetMethodID("HasPermission"), jstrPermission);
			pEnv->DeleteLocalRef(jstrPermission);
			return bHasPermission;
	    }
		//--------------------------------------------------------------------------------------
		/// Authorise Read Permissions
		///
	    /// Prompt Facebook to ask the users to grant the given permissions.
	    /// Calls into native with the result
	    ///
		/// @param List of read permissions IDs
		//--------------------------------------------------------------------------------------
	    void FacebookJavaInterface::AuthoriseReadPermissions(const std::vector<std::string>& inaReadPerms)
	    {
	    	JNIEnv* pEnv = CSBackend::Android::JavaInterfaceManager::GetSingletonPtr()->GetJNIEnvironmentPtr();
			jstring jstrEmptyString = pEnv->NewStringUTF("");
			jclass jStringClass = pEnv->FindClass("java/lang/String");
	    	jobjectArray jaPermissions = pEnv->NewObjectArray(inaReadPerms.size(), jStringClass, jstrEmptyString);
	    	u32 udwPermissionCount = 0;
	    	for(std::vector<std::string>::const_iterator it = inaReadPerms.begin(); it != inaReadPerms.end(); ++it)
	    	{
	    		jstring jstrPermission = JavaInterfaceUtils::CreateJStringFromSTDString((*it));
	    		pEnv->SetObjectArrayElement(jaPermissions, udwPermissionCount, jstrPermission);
	    		pEnv->DeleteLocalRef(jstrPermission);
	    		++udwPermissionCount;
	    	}

	    	pEnv->CallVoidMethod(GetJavaObject(), GetMethodID("AuthoriseReadPermissions"), jaPermissions);
	    	pEnv->DeleteLocalRef(jstrEmptyString);
	    	pEnv->DeleteLocalRef(jStringClass);
	    	pEnv->DeleteLocalRef(jaPermissions);
	    }
		//--------------------------------------------------------------------------------------
		/// Authorise Write Permissions
		///
	    /// Prompt Facebook to ask the users to grant the given permissions.
	    /// Calls into native with the result
	    ///
		/// @param List of write permissions IDs
		//--------------------------------------------------------------------------------------
	    void FacebookJavaInterface::AuthoriseWritePermissions(const std::vector<std::string>& inaWritePerms)
	    {
	    	JNIEnv* pEnv = CSBackend::Android::JavaInterfaceManager::GetSingletonPtr()->GetJNIEnvironmentPtr();
			jstring jstrEmptyString = pEnv->NewStringUTF("");
			jclass jStringClass = pEnv->FindClass("java/lang/String");
	    	jobjectArray jaPermissions = pEnv->NewObjectArray(inaWritePerms.size(), jStringClass, jstrEmptyString);
	    	u32 udwPermissionCount = 0;
	    	for(std::vector<std::string>::const_iterator it = inaWritePerms.begin(); it != inaWritePerms.end(); ++it)
	    	{
	    		jstring jstrPermission = JavaInterfaceUtils::CreateJStringFromSTDString((*it));
	    		pEnv->SetObjectArrayElement(jaPermissions, udwPermissionCount, jstrPermission);
	    		pEnv->DeleteLocalRef(jstrPermission);
	    		++udwPermissionCount;
	    	}

	    	pEnv->CallVoidMethod(GetJavaObject(), GetMethodID("AuthoriseWritePermissions"), jaPermissions);
	    	pEnv->DeleteLocalRef(jstrEmptyString);
	    	pEnv->DeleteLocalRef(jStringClass);
	    	pEnv->DeleteLocalRef(jaPermissions);
	    }
		//--------------------------------------------------------------------------------------
		/// Sign Out
		///
	    /// If a session exists log the user out and destroy any cached tokens
		//--------------------------------------------------------------------------------------
	    void FacebookJavaInterface::SignOut()
	    {
			JNIEnv* pEnv = CSBackend::Android::JavaInterfaceManager::GetSingletonPtr()->GetJNIEnvironmentPtr();
			pEnv->CallVoidMethod(GetJavaObject(), GetMethodID("SignOut"));
	    }
		//--------------------------------------------------------------------------------------
		/// Try Post To Feed
		///
	    /// Attempt to make a Graph API request to post to feed with the following
	    /// path and key value array
		//--------------------------------------------------------------------------------------
	    void FacebookJavaInterface::TryPostToFeed(const std::string& instrGraphPath, const std::vector<std::string>& inaKeyValues)
	    {
	    	JNIEnv* pEnv = CSBackend::Android::JavaInterfaceManager::GetSingletonPtr()->GetJNIEnvironmentPtr();
			jstring jstrEmptyString = pEnv->NewStringUTF("");
			jclass jStringClass = pEnv->FindClass("java/lang/String");
	    	jobjectArray jaKeyValues = pEnv->NewObjectArray(inaKeyValues.size(), jStringClass, jstrEmptyString);
	    	u32 i = 0;
	    	for(std::vector<std::string>::const_iterator it = inaKeyValues.begin(); it != inaKeyValues.end(); ++it, ++i)
	    	{
	    		jstring jstrElement = JavaInterfaceUtils::CreateJStringFromSTDString((*it));
	    		pEnv->SetObjectArrayElement(jaKeyValues, i, jstrElement);
	    		pEnv->DeleteLocalRef(jstrElement);
	    	}

    		jstring jstrGraphPath = JavaInterfaceUtils::CreateJStringFromSTDString(instrGraphPath);
    		pEnv->CallVoidMethod(GetJavaObject(), GetMethodID("MakePostToFeedRequest"), jstrGraphPath, jaKeyValues);
	    	pEnv->DeleteLocalRef(jaKeyValues);
	    	pEnv->DeleteLocalRef(jstrGraphPath);
	    	pEnv->DeleteLocalRef(jStringClass);
	    	pEnv->DeleteLocalRef(jstrEmptyString);
	    }
		//--------------------------------------------------------------------------------------
		/// Try Post To Feed
		///
	    /// Attempt to make a Graph API request to post to feed with the following
	    /// path and key value array
		//--------------------------------------------------------------------------------------
	    void FacebookJavaInterface::TryPostRequest(const std::vector<std::string>& inaKeyValues)
	    {
	    	JNIEnv* pEnv = CSBackend::Android::JavaInterfaceManager::GetSingletonPtr()->GetJNIEnvironmentPtr();
			jstring jstrEmptyString = pEnv->NewStringUTF("");
			jclass jStringClass = pEnv->FindClass("java/lang/String");
	    	jobjectArray jaKeyValues = pEnv->NewObjectArray(inaKeyValues.size(), jStringClass, jstrEmptyString);
	    	u32 i = 0;
	    	for(std::vector<std::string>::const_iterator it = inaKeyValues.begin(); it != inaKeyValues.end(); ++it, ++i)
	    	{
	    		jstring jstrElement = JavaInterfaceUtils::CreateJStringFromSTDString((*it));
	    		pEnv->SetObjectArrayElement(jaKeyValues, i, jstrElement);
	    		pEnv->DeleteLocalRef(jstrElement);
	    	}

    		pEnv->CallVoidMethod(GetJavaObject(), GetMethodID("MakeRequestToUser"), jaKeyValues);
	    	pEnv->DeleteLocalRef(jaKeyValues);
	    	pEnv->DeleteLocalRef(jStringClass);
	    	pEnv->DeleteLocalRef(jstrEmptyString);
	    }
	}
}

#endif
