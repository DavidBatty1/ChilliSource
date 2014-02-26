/*
 *  TwitterAuthenticationActivity.h
 *  moFlow
 *
 *  Created by Robert Henning on 09/05/2012.
 *  Copyright (c) 2012 Tag Games. All rights reserved.
 *
 */

#ifndef _MO_FLO_SOCIAL_TWITTER_TWITTER_AUTHENTICATION_ACTIVITY_H_
#define _MO_FLO_SOCIAL_TWITTER_TWITTER_AUTHENTICATION_ACTIVITY_H_

#include <ChilliSource/ChilliSource.h>
#include <ChilliSource/Core/Base/Activity.h>
#include <ChilliSource/Core/Base/FastDelegate.h>
#include <ChilliSource/Core/Event/GenericEvent.h>

namespace ChilliSource
{
	namespace Social
	{
		class TwitterAuthenticationActivity : public Core::IActivity
		{
		public:
			DECLARE_NAMED_INTERFACE(TwitterAuthenticationActivity);
			
            static IActivity* CreateTwitterAuthenticationActivity();
            
			struct AuthenticationPINResult
			{
				std::string strPIN;	// PIN entered by user
			};
			
			typedef fastdelegate::FastDelegate1<const AuthenticationPINResult&> AuthenticationPINResultDelegate;
			
			//--------------------------------------------------------------
			/// Is A
			///
			/// @param Interface ID
			/// @param Whether activity is of given type
			//--------------------------------------------------------------
			bool IsA(Core::InterfaceIDType inID) const;
			//-----------------------------------------------
			/// Present
			/// 
			/// Starts the activity by presenting a view with
			/// a 'busy, please wait' message
			//-----------------------------------------------
			virtual void Present() = 0;
			//-----------------------------------------------
			/// Presents the authorise URL
			/// 
			/// Set the URL received from Twitter to visit
			/// in order to see PIN
			///
			/// @param URL
			//-----------------------------------------------
			virtual void PresentURL(const std::string& instrURL) = 0;
			//-----------------------------------------------
			/// Save PIN
			/// 
			/// Saves the PIN entered by the user
			///
			/// @param PIN entered by user
			//-----------------------------------------------
			virtual bool SavePIN(const std::string& instrPIN) = 0;
			//-----------------------------------------------
			/// Dismiss
			/// 
			/// Dismiss the web view interface
			//-----------------------------------------------
			virtual void Dismiss() = 0;
			//-----------------------------------------------
			/// Get Dismissed Event 
			///
			/// @return Event triggered when activity is
			/// dismissed
			//-----------------------------------------------
			Core::IEvent<Core::ActivityDismissedEvent>& GetDismissedEvent();
			//-----------------------------------------------
			/// Set Authentication PIN Result Delegate
			///
			/// Sets the delegate to trigger when the user
			/// confirms PIN entry
			//-----------------------------------------------
			void SetAuthenticationPINResultDelegate(const ChilliSource::Social::TwitterAuthenticationActivity::AuthenticationPINResultDelegate inCallback);
		
		protected:
			Core::CEvent1<Core::ActivityDismissedEvent>                                             mOnDismissedEvent;
			ChilliSource::Social::TwitterAuthenticationActivity::AuthenticationPINResultDelegate	mOnPINResultDelegate;
			std::string																		mstrURL;
			std::string																		mstrPIN;
		};
	}
}

#endif
