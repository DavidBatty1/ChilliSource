//
//  EmailComposer.h
//  Chilli Source
//  Created by Stuart McGaw on 09/06/2011.
//
//  The MIT License (MIT)
//
//  Copyright (c) 2011 Tag Games Limited
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

#import <ChilliSource/ChilliSource.h>
#import <ChilliSource/Backend/Platform/iOS/ForwardDeclarations.h>
#import <ChilliSource/Social/Communications/EmailComposer.h>

#import <MessageUI/MessageUI.h>

@class EmailComposerDelegate;

namespace ChilliSource
{
	namespace iOS
    {
        //-------------------------------------------------------------
        /// The iOS backend for the email composition state system.
        ///
        /// @author S McGaw
        //-------------------------------------------------------------
        class EmailComposer final : public Social::EmailComposer
		{
		public:
            CS_DECLARE_NAMEDTYPE(EmailComposer);
            //-------------------------------------------------------
			/// Queries whether or not this system implements the
            /// interface with the given Id.
			///
            /// @author S McGaw
            ///
			/// @param The interface Id.
			/// @return Whether system is of given type.
			//-------------------------------------------------------
			bool IsA(Core::InterfaceIDType in_interfaceId) const override;
            //-------------------------------------------------------
            /// Displays the email activity with the given recipients,
            /// subject and contents.
            ///
            /// @author S Downie
            ///
            /// @param A list of recipients.
            /// @param The subject.
            /// @param The body of the email.
            /// @param The format of the body of the email.
            /// @param The callback describing the result of the email.
            //-------------------------------------------------------
			void Present(const std::vector<Core::UTF8String>& in_recipientAddresses, const Core::UTF8String& in_subject, const Core::UTF8String& in_contents, ContentFormat in_contentFormat,
                         const SendResultDelegate& in_callback) override;
            //-------------------------------------------------------
            /// Displays the email activity with the given recipients,
            /// subject and contents, and adds a list of attachments
            /// to the email.
            ///
            /// @author I Copland
            ///
            /// @param A list of recipients.
            /// @param The subject.
            /// @param The body of the email.
            /// @param The format of the body of the email.
            /// @param The attachment.
            /// @param The callback describing the result of the email.
            //-------------------------------------------------------
            void PresentWithAttachment(const std::vector<Core::UTF8String>& in_recipientAddresses, const Core::UTF8String& in_subject, const Core::UTF8String& in_contents, ContentFormat in_contentFormat,
                                       const Attachment& in_attachment, const SendResultDelegate & in_callback) override;
            //-------------------------------------------------------
            /// Dismisses the activity if it is currently displayed.
            ///
            /// @author S Downie
            //-------------------------------------------------------
			void Dismiss() override;
            //-------------------------------------------------------
            /// Called when the result is received from the email
            /// composition view controller. This is for internal
            /// use and should not be called manually by the user.
            ///
            /// @author I Copland
            //-------------------------------------------------------
			void OnResult(MFMailComposeViewController* in_viewController, MFMailComposeResult in_result);
		private:
            friend Social::EmailComposerUPtr Social::EmailComposer::Create();
            
            //-------------------------------------------------------
            /// This checks whether or not the current iOS device
            /// supports email. This should always be checked before
            /// creating an instance of the class.
            ///
            /// @author S McGaw
            //-------------------------------------------------------
            static bool IsSupportedByDevice();
            //----------------------------------------------------
            /// Private constructor to force the use of the
            /// factory method.
            ///
            /// @author I Copland
            //----------------------------------------------------
            EmailComposer();
            //------------------------------------------------------
            /// Called when the the owning state is initialised.
            ///
            /// @author I Copland
            //------------------------------------------------------
            void OnInit() override;
            //----------------------------------------------------
            /// Cleans up the email composer and sets it back to
            /// a state where it is ready to be presented again.
            ///
            /// @author I Copland
            //----------------------------------------------------
            void Cleanup();
            //------------------------------------------------------
            /// Called when the the owning state is destroyed.
            ///
            /// @author I Copland
            //------------------------------------------------------
            void OnDestroy() override;
            
            bool m_isPresented;
            SendResultDelegate m_resultDelegate;
			EmailComposerDelegate* m_emailComposerDelegate;
			MFMailComposeViewController* m_viewController;
		};
		 
	}
}