//
//  FacebookPostSystem.h
//  Chilli Source
//  Created by Robert Henning on 03/05/2012.
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

#ifndef _CHILLISOURCE_PLATFORM_ANDROID_SOCIAL_FACEBOOK_FACEBOOKPOSTSYSTEM_H_
#define _CHILLISOURCE_PLATFORM_ANDROID_SOCIAL_FACEBOOK_FACEBOOKPOSTSYSTEM_H_

#include <ChilliSource/ChilliSource.h>
#include <CSBackend/Platform/Android/Social/Facebook/FacebookJavaInterface.h>
#include <ChilliSource/Social/Facebook/FacebookPostSystem.h>

namespace CSBackend
{
	namespace Android
	{
		//----------------------------------------------------
		/// Class for posting messages and request
		/// to the Facebook wall via the Android Facebook SDK.
		///
		/// User must be authenticated prior to posting
		///
		/// @author R Henning
		//----------------------------------------------------
		class FacebookPostSystem final : public CSSocial::FacebookPostSystem
		{
		public:

			CS_DECLARE_NAMEDTYPE(FacebookPostSystem);

			//----------------------------------------------------
            /// @author R Henning
            ///
            /// @param Interface ID to compare
            ///
            /// @return Whether the object has the same interface ID
            //----------------------------------------------------
			bool IsA(CSCore::InterfaceIDType in_interfaceId) const override;
            //----------------------------------------------------
            /// Called when the system is created allocating any
			/// resources
            ///
            /// @author S Downie
            //----------------------------------------------------
            void OnInit() override;
			//----------------------------------------------------
            /// Post the wall of the user specified in the post
            /// description. If no user is specified then post
            /// to the wall of the currently authenticated user.
            ///
            /// User must be authenticated
            ///
            /// Note: For the time being only one post can
            /// happen at a time
            ///
            /// @author R Henning
            ///
            /// @param Post description
            /// @param Connection to result delegate
            //----------------------------------------------------
            void Post(const PostDesc& in_desc, PostResultDelegate::Connection&& in_delegateConnection) override;
            //---------------------------------------------------
            /// Send a request to a group of friends using the
            /// Android Facebook SDK
            ///
            /// User must be authenticated
            ///
            /// Note: For the time being only one request can
            /// happen at a time
            ///
            /// @author A Mackie
            ///
            /// @param Request description
            /// @param Connection to result delegate
            //---------------------------------------------------
            void SendRequest(const RequestDesc& in_desc, PostResultDelegate::Connection&& in_delegateConnection) override;

            //---Internal functions called by the JNI
            //---------------------------------------------------
            /// Called by JNI when the Facebook SDK has
            /// finished posting to the wall
            ///
            /// @author R Henning
            ///
            /// @param Result
            //---------------------------------------------------
			void OnPostToFeedComplete(PostResult in_result);
            //---------------------------------------------------
            /// Called by JNI when the Facebook SDK has
            /// finished requesting.
            ///
            /// @author A Mackie
            ///
            /// @param Result
            //---------------------------------------------------
			void OnPostRequestComplete(PostResult in_result);
            //----------------------------------------------------
            /// Called when the system is destroyed freeing any
			/// resources
            ///
            /// @author S Downie
            //----------------------------------------------------
            void OnDestroy() override;

		private:
			friend CSSocial::FacebookPostSystemUPtr CSSocial::FacebookPostSystem::Create(CSSocial::FacebookAuthenticationSystem* in_authSystem);
            //----------------------------------------------------
            /// Private constructor to force the use of the
            /// factory method.
            ///
            /// @author Ian Copland
            ///
            /// @param The facebook authentication system.
            //----------------------------------------------------
            FacebookPostSystem(CSSocial::FacebookAuthenticationSystem* in_authSystem);

		private:

			FacebookJavaInterfaceSPtr m_javaInterface;
			CSSocial::FacebookAuthenticationSystem* m_authSystem;
            PostResultDelegate::Connection m_postCompleteDelegateConnection;
            PostResultDelegate::Connection m_requestCompleteDelegateConnection;
		};
	}
}

#endif

#endif
