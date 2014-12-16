//
//  WidgetFactory.cpp
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


#include <ChilliSource/UI/Base/WidgetFactory.h>

#include <ChilliSource/Core/Base/Application.h>
#include <ChilliSource/Core/Delegate/MakeDelegate.h>
#include <ChilliSource/Core/Resource/ResourcePool.h>
#include <ChilliSource/Input/Pointer/PointerSystem.h>
#include <ChilliSource/Rendering/Base/AlignmentAnchors.h>
#include <ChilliSource/UI/Base/Component.h>
#include <ChilliSource/UI/Base/ComponentFactory.h>
#include <ChilliSource/UI/Base/Widget.h>
#include <ChilliSource/UI/Base/WidgetDef.h>
#include <ChilliSource/UI/Base/WidgetTemplate.h>
#include <ChilliSource/UI/Drawable/NinePatchDrawable.h>
#include <ChilliSource/UI/Drawable/StandardDrawable.h>
#include <ChilliSource/UI/Drawable/ThreePatchDrawable.h>
#include <ChilliSource/UI/Layout/GridLayout.h>
#include <ChilliSource/UI/Layout/HListLayout.h>
#include <ChilliSource/UI/Layout/LayoutType.h>
#include <ChilliSource/UI/Layout/VListLayout.h>

namespace ChilliSource
{
	namespace UI
	{
		CS_DEFINE_NAMEDTYPE(WidgetFactory);
        
        namespace
        {
            const std::string k_widgetKey = "Widget";
            const std::string k_highlightButtonKey = "HighlightButton";
            const std::string k_toggleButtonKey = "ToggleButton";
            const std::string k_verticalSliderKey = "VerticalSlider";
            const std::string k_horizontalSliderKey = "HorizontalSlider";
            const std::string k_horizontalProgressBarKey = "HorizontalProgressBar";
            const std::string k_verticalProgressBarKey = "VerticalProgressBar";
        }
        
        //---------------------------------------------------------------------------
        //---------------------------------------------------------------------------
        WidgetFactoryUPtr WidgetFactory::Create()
        {
            return WidgetFactoryUPtr(new WidgetFactory());
        }
        //---------------------------------------------------------------------------
        //---------------------------------------------------------------------------
		bool WidgetFactory::IsA(Core::InterfaceIDType in_interfaceId) const
        {
			return in_interfaceId == WidgetFactory::InterfaceID;
		}
        //---------------------------------------------------------------------------
        //---------------------------------------------------------------------------
        void WidgetFactory::OnInit()
        {
            m_componentFactory = Core::Application::Get()->GetSystem<ComponentFactory>();
            CS_ASSERT(m_componentFactory != nullptr, "WidgetFactory is missing required system: ComponentFactory");
            
            auto resPool = Core::Application::Get()->GetResourcePool();

            WidgetDefCSPtr widgetDef = resPool->LoadResource<WidgetDef>(Core::StorageLocation::k_chilliSource, "Widgets/Widget.csuidef");
            RegisterDefinition(widgetDef);
            
            WidgetDefCSPtr imageDef = resPool->LoadResource<WidgetDef>(Core::StorageLocation::k_chilliSource, "Widgets/Image.csuidef");
            RegisterDefinition(imageDef);
            
            WidgetDefCSPtr highlightButtonDef = resPool->LoadResource<WidgetDef>(Core::StorageLocation::k_chilliSource, "Widgets/HighlightButton.csuidef");
            RegisterDefinition(highlightButtonDef);
            
            WidgetDefCSPtr toggleButtonDef = resPool->LoadResource<WidgetDef>(Core::StorageLocation::k_chilliSource, "Widgets/ToggleButton.csuidef");
            RegisterDefinition(toggleButtonDef);
            
            WidgetDefCSPtr horizontalSliderDef = resPool->LoadResource<WidgetDef>(Core::StorageLocation::k_chilliSource, "Widgets/HorizontalSlider.csuidef");
            RegisterDefinition(horizontalSliderDef);
            
            WidgetDefCSPtr verticalSliderDef = resPool->LoadResource<WidgetDef>(Core::StorageLocation::k_chilliSource, "Widgets/VerticalSlider.csuidef");
            RegisterDefinition(verticalSliderDef);

            WidgetDefCSPtr horizontalProgressDef = resPool->LoadResource<WidgetDef>(Core::StorageLocation::k_chilliSource, "Widgets/HorizontalProgressBar.csuidef");
            RegisterDefinition(horizontalProgressDef);
            
            WidgetDefCSPtr verticalProgressDef = resPool->LoadResource<WidgetDef>(Core::StorageLocation::k_chilliSource, "Widgets/VerticalProgressBar.csuidef");
            RegisterDefinition(verticalProgressDef);
            
            WidgetDefCSPtr labelDef = resPool->LoadResource<WidgetDef>(Core::StorageLocation::k_chilliSource, "Widgets/Label.csuidef");
            RegisterDefinition(labelDef);
        }
        //---------------------------------------------------------------------------
        //---------------------------------------------------------------------------
        void WidgetFactory::RegisterDefinition(const WidgetDefCSPtr& in_def)
        {
            m_widgetDefNameMap.insert(std::make_pair(in_def->GetTypeName(), in_def));
        }
        //---------------------------------------------------------------------------
        //---------------------------------------------------------------------------
        WidgetDefCSPtr WidgetFactory::GetDefinition(const std::string& in_nameKey) const
        {
            auto it = m_widgetDefNameMap.find(in_nameKey);
            CS_ASSERT(it != m_widgetDefNameMap.end(), "No such widget def with name: " + in_nameKey);
            return it->second;
        }
        //---------------------------------------------------------------------------
        //---------------------------------------------------------------------------
        WidgetUPtr WidgetFactory::Create(const WidgetDefCSPtr& in_def) const
        {
            WidgetDesc desc(in_def->GetTypeName(), in_def->GetDefaultProperties(), std::vector<WidgetDesc>());
            
            return CreateRecursive(in_def, desc);
        }
        //---------------------------------------------------------------------------
        //---------------------------------------------------------------------------
        WidgetUPtr WidgetFactory::Create(const WidgetTemplateCSPtr& in_template) const
        {
            auto def = m_widgetDefNameMap.find(in_template->GetWidgetDesc().GetType())->second;
            CS_ASSERT(def != nullptr, "Invalid widget type in widget template: " + in_template->GetFilePath());
            
            return CreateRecursive(def, in_template->GetWidgetDesc());
        }
        //---------------------------------------------------------------------------
        //---------------------------------------------------------------------------
        WidgetUPtr WidgetFactory::CreateWidget() const
        {
            return Create(m_widgetDefNameMap.find(k_widgetKey)->second);
        }
        //---------------------------------------------------------------------------
        //---------------------------------------------------------------------------
        WidgetUPtr WidgetFactory::CreateHighlightButton() const
        {
            return Create(m_widgetDefNameMap.find(k_highlightButtonKey)->second);
        }
        //---------------------------------------------------------------------------
        //---------------------------------------------------------------------------
        WidgetUPtr WidgetFactory::CreateToggleButton() const
        {
            return Create(m_widgetDefNameMap.find(k_toggleButtonKey)->second);
        }
        //---------------------------------------------------------------------------
        //---------------------------------------------------------------------------
        WidgetUPtr WidgetFactory::CreateVerticalSlider() const
        {
            return Create(m_widgetDefNameMap.find(k_verticalSliderKey)->second);
        }
        //---------------------------------------------------------------------------
        //---------------------------------------------------------------------------
        WidgetUPtr WidgetFactory::CreateHorizontalSlider() const
        {
            return Create(m_widgetDefNameMap.find(k_horizontalSliderKey)->second);
        }
        //---------------------------------------------------------------------------
        //---------------------------------------------------------------------------
        WidgetUPtr WidgetFactory::CreateHorizontalProgressBar() const
        {
            return Create(m_widgetDefNameMap.find(k_horizontalProgressBarKey)->second);
        }
        //---------------------------------------------------------------------------
        //---------------------------------------------------------------------------
        WidgetUPtr WidgetFactory::CreateVerticalProgressBar() const
        {
            return Create(m_widgetDefNameMap.find(k_verticalProgressBarKey)->second);
        }
        //---------------------------------------------------------------------------
        //---------------------------------------------------------------------------
        WidgetUPtr WidgetFactory::CreateRecursive(const WidgetDefCSPtr& in_widgetDef, const WidgetDesc& in_widgetDesc) const
        {
            //create the components
            std::vector<ComponentUPtr> components;
            for (const auto& componentDesc : in_widgetDef->GetComponentDescs())
            {
                components.push_back(m_componentFactory->CreateComponent(componentDesc.GetType(), componentDesc.GetName(), componentDesc.GetProperties()));
            }
            
            //create the internal children
            std::vector<WidgetUPtr> internalChildren;
            for (const auto& internalChild : in_widgetDef->GetChildDescs())
            {
                auto def = m_widgetDefNameMap.find(internalChild.GetType())->second;
                CS_ASSERT(def != nullptr, "Invalid widget def type in internal child widget.");
                
                WidgetUPtr childWidget = CreateRecursive(def, internalChild);
                internalChildren.push_back(std::move(childWidget));
            }
            
            //create the widget.
            WidgetUPtr widget(new Widget(in_widgetDesc.GetProperties(), std::move(components), in_widgetDef->GetComponentPropertyLinks(), std::move(internalChildren), in_widgetDef->GetChildPropertyLinks()));
            
            //create and add the external children.
            for(const auto& childDesc : in_widgetDesc.GetChildDescs())
            {
                auto def = m_widgetDefNameMap.find(childDesc.GetType())->second;
                CS_ASSERT(def != nullptr, "Invalid widget def type in internal child widget.");
                
                WidgetSPtr childWidget = CreateRecursive(def, childDesc);
                widget->AddWidget(childWidget);
            }
            
            return widget;
        }
        //---------------------------------------------------------------------------
        //---------------------------------------------------------------------------
        void WidgetFactory::OnDestroy()
        {
            m_widgetDefNameMap.clear();
        }
	}
}
