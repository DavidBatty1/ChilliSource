//
//  DeviceButtonSystem.h
//  Chilli Source
//  Created by Ian Copland on 16/05/2014.
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

#ifdef CS_TARGETPLATFORM_ANDROID

#ifndef _CHILLISOURCE_BACKEND_PLATFORM_ANDROID_INPUT_DEVICEBUTTONS_DEVICEBUTTONSYSTEM_H_
#define _CHILLISOURCE_BACKEND_PLATFORM_ANDROID_INPUT_DEVICEBUTTONS_DEVICEBUTTONSYSTEM_H_

#include <ChilliSource/ChilliSource.h>
#include <ChilliSource/Backend/Platform/Android/ForwardDeclarations.h>
#include <ChilliSource/Input/DeviceButtons/DeviceButtonSystem.h>

namespace ChilliSource
{
	namespace Android
	{
        //------------------------------------------------------------
        /// The Android backend implementation of the Device Button System.
        ///
        /// @author I Copland
        //------------------------------------------------------------
		class DeviceButtonSystem final : public Input::DeviceButtonSystem
		{
		public:
            CS_DECLARE_NAMEDTYPE(DeviceButtonSystem);
            //----------------------------------------------------
			/// Queries whether or not this system implements the
            /// interface with the given ID.
            ///
            /// @author I Copland
            ///
            /// @param The interface Id.
            ///
			/// @return Whether or not the interface is implemented.
			//----------------------------------------------------
            bool IsA(Core::InterfaceIDType in_interfaceId) const override;
            //----------------------------------------------------
			/// @author I Copland
            ///
            /// @return An event that will be called whenever a
            /// device button is pressed.
			//----------------------------------------------------
            Core::IConnectableEvent<TriggeredDelegate>& GetTriggeredEvent() override;
		private:
            friend Input::DeviceButtonSystemUPtr Input::DeviceButtonSystem::Create();
            
            //----------------------------------------------------
			/// Constructor. Declared private to force the use of
            /// the factory method.
            ///
            /// @author I Copland
			//----------------------------------------------------
			DeviceButtonSystem() = default;
            //------------------------------------------------
            /// Initialisation method called at a time when
            /// all App Systems have been created. System
            /// initialisation occurs in the order they were
            /// created.
            ///
            /// @author I Copland
            //------------------------------------------------
            void OnInit() override;
            //------------------------------------------------
            /// Called when a device button is triggered.
            ///
            /// @author I Copland
            ///
            /// @param An integer representing the triggered
            /// button.
            //------------------------------------------------
            void OnTriggered(s32 in_button);
            //------------------------------------------------
            /// Called when the application is being destroyed.
            /// This should be used to cleanup memory and
            /// references to other systems. System destruction
            /// occurs in the reverse order to which they
            /// were created
            ///
            /// @author I Copland
            //------------------------------------------------
            void OnDestroy() override;

            Core::Event<TriggeredDelegate> m_triggeredEvent;
            DeviceButtonJavaInterfaceSPtr m_javaInterface;
		};
	}
}

#endif

#endif