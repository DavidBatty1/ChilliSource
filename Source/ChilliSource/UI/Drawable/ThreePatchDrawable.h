//
//  ThreePatchDrawable.h
//  Chilli Source
//  Created by Scott Downie on 24/07/2014.
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


#ifndef _CHILLISOURCE_UI_DRAWABLE_THREEPATCHDRAWABLE_H_
#define _CHILLISOURCE_UI_DRAWABLE_THREEPATCHDRAWABLE_H_

#include <ChilliSource/ChilliSource.h>
#include <ChilliSource/Core/Base/Colour.h>
#include <ChilliSource/Core/Math/Vector2.h>
#include <ChilliSource/Rendering/Texture/TextureAtlas.h>
#include <ChilliSource/Rendering/Texture/UVs.h>
#include <ChilliSource/UI/Drawable/Drawable.h>

#include <array>
#include <functional>

namespace ChilliSource
{
    namespace UI
    {
        //----------------------------------------------------------------------------------------
        /// Interface for rendering widget with a texture and UVs as a 3 patch either horizontally
        /// or vertically. This allows the widget to be scaled in one direction without distorting the edges.
        /// The patches are specified by percentage insets from the edges of the widget
        ///
        /// The centre patch should be designed to stretch horizontally or vertically.
        ///
        /// @author S Downie
        //----------------------------------------------------------------------------------------
        class ThreePatchDrawable final : public Drawable
        {
        public:
            CS_DECLARE_NAMEDTYPE(ThreePatchDrawable);
            
            static const u32 k_numPatches = 3;
            //----------------------------------------------------------------------------------------
            /// The type of the 3-patch i.e. horizontal or vertical
            ///
            /// @author S Downie
            //----------------------------------------------------------------------------------------
            enum class Direction
            {
                k_horizontal,
                k_vertical
            };
            //----------------------------------------------------------------------------------------
            /// Allows querying of whether or not the component implements the interface associated
            /// with the given interface Id.  Typically this wont be called directly, instead the
            /// templated version IsA<Interface>() should be used.
            ///
            /// @author Ian Copland
            ///
            /// @param The interface Id.
            ///
            /// @return Whether the object implements the given interface.
            //----------------------------------------------------------------------------------------
            bool IsA(Core::InterfaceIDType in_interfaceId) const override;
            //----------------------------------------------------------------------------------------
            /// Set the texture that should be used in subsequent draws
            ///
            /// @author S Downie
            ///
            /// @param Texture
            //----------------------------------------------------------------------------------------
            void SetTexture(const Rendering::TextureCSPtr& in_texture) override;
            //----------------------------------------------------------------------------------------
            /// Set the texture atlas that should be used in subsequent draws.
            ///
            /// @author S Downie
            ///
            /// @param Texture atlas
            //----------------------------------------------------------------------------------------
            void SetTextureAtlas(const Rendering::TextureAtlasCSPtr& in_atlas) override;
            //----------------------------------------------------------------------------------------
            /// Set the texture atlas frame Id that should be used in subsequent draws.
            ///
            /// NOTE: An atlas must have been set prior to calling this
            ///
            /// @author S Downie
            ///
            /// @param Frame Id
            //----------------------------------------------------------------------------------------
            void SetTextureAtlasId(const std::string& in_atlasId) override;
            //----------------------------------------------------------------------------------------
            /// Set the UVs that should be used in subsequent draws. UVs are relative to the
            /// frame and not the overall atlas
            ///
            /// @author S Downie
            ///
            /// @param Rectangle containing U, V, S, T
            //----------------------------------------------------------------------------------------
            void SetUVs(const Rendering::UVs& in_UVs) override;
            //----------------------------------------------------------------------------------------
            /// Sets the colour of the drawable. The final colour of the drawable takes into account
            /// the owning widgets colour and this colour.
            ///
            /// @author Ian Copland
            ///
            /// @param The colour.
            //----------------------------------------------------------------------------------------
            void SetColour(const Core::Colour& in_colour) override;
            //----------------------------------------------------------------------------------------
            /// Set the UV insets that should be used to create the patches. Insets are from the edge
            /// and therefore no negative numbers need to be specified for right and bottom insets.
            ///
            /// NOTE: Insets must compliment each other i.e. left and right cannot sum to more than 1.0
            /// as they would overlap and insets cannot be zero or less.
            ///
            /// @author S Downie
            ///
            /// @param Left inset if horizontal 3-patch bottom inset if vertical 3-patch (as normalised fraction 0 - 1)
            /// @param Right inset if horizontal 3-patch top inset if vertical 3-patch (as normalised fraction 0 - 1)
            //----------------------------------------------------------------------------------------
            void SetInsets(f32 in_leftOrBottom, f32 in_rightOrTop);
            //----------------------------------------------------------------------------------------
            /// @author S Downie
            ///
            /// @return The preferred size that the drawable wishes to de drawn at based on the
            /// texture size
            //----------------------------------------------------------------------------------------
            Core::Vector2 GetPreferredSize() const override;
            //----------------------------------------------------------------------------------------
            /// Render the widget using the canvas renderer. The widget has is rendered using the
            /// set texture and UVs.
            ///
            /// @author S Downie
            ///
            /// @param Renderer
            /// @param Absolute screen transform
            /// @param Asbolute screen size
            /// @param Absolute colour
            //----------------------------------------------------------------------------------------
            void Draw(Rendering::CanvasRenderer* in_renderer, const Core::Matrix3& in_transform, const Core::Vector2& in_absSize, const Core::Colour& in_absColour) override;
            
        private:
            friend class ThreePatchDrawableDef;
            
            //----------------------------------------------------------------------------------------
            /// Calculates the UVs for each patch.
            ///
            /// @author S Downie
            ///
            /// @param Image frame
            /// @param Left inset if horizontal 3-patch bottom inset if vertical 3-patch (as normalised fraction 0 - 1)
            /// @param Right inset if horizontal 3-patch top inset if vertical 3-patch (as normalised fraction 0 - 1)
            ///
            /// @return UVs for each patch
            //----------------------------------------------------------------------------------------
            using CalculateUVsDelegate = std::function<std::array<Rendering::UVs, k_numPatches>(const Rendering::TextureAtlas::Frame&, f32, f32)>;
            //----------------------------------------------------------------------------------------
            /// Calculates the sizes for each patch.
            ///
            /// @author S Downie
            ///
            /// @param Widget absolute size
            /// @param Image frame
            /// @param Left inset if horizontal 3-patch bottom inset if vertical 3-patch (as normalised fraction 0 - 1)
            /// @param Right inset if horizontal 3-patch top inset if vertical 3-patch (as normalised fraction 0 - 1)
            ///
            /// @return Size for each patch
            //----------------------------------------------------------------------------------------
            using CalculateSizesDelegate = std::function<std::array<Core::Vector2, k_numPatches>(const Core::Vector2&, const Rendering::TextureAtlas::Frame&, f32, f32)>;
            //----------------------------------------------------------------------------------------
            /// Calculates the local space positions for each patch.
            ///
            /// @author S Downie
            ///
            /// @param Widget absolute size
            /// @param Patch sizes
            ///
            /// @return Positions for each patch
            //----------------------------------------------------------------------------------------
            using CalculatePositionsDelegate = std::function<std::array<Core::Vector2, k_numPatches>(const Core::Vector2&, const std::array<Core::Vector2, k_numPatches>&)>;
            //----------------------------------------------------------------------------------------
            /// Calculate the offset for the patches that will position them as if they still had
            /// their cropped space
            ///
            /// @author S Downie
            ///
            /// @param Widget absolute size
            /// @param Image frame
            /// @param Left inset if horizontal 3-patch bottom inset if vertical 3-patch (as normalised fraction 0 - 1)
            /// @param Right inset if horizontal 3-patch top inset if vertical 3-patch (as normalised fraction 0 - 1)
            ///
            /// @return Offset from top left
            //----------------------------------------------------------------------------------------
            using CalculateOffsetDelegate = std::function<Core::Vector2(const Core::Vector2&, const Rendering::TextureAtlas::Frame&, f32, f32)>;
            //----------------------------------------------------------------------------------------
            /// Constructor
            ///
            /// @author Ian Copland
            ///
            /// @param The texture.
            /// @param The direction the drawable will stretch.
            /// @param The left inset if a horizontal 3-patch or the bottom inset if a vertical
            /// 3-patch. This should be provided as a normalised fraction, 0.0 - 1.0.
            /// @param The right inset if a horizontal 3-patch or the top inset if a vertical 3-patch.
            /// This should be provided as a normalised fraction, 0.0 - 1.0.
            //----------------------------------------------------------------------------------------
            ThreePatchDrawable(const Rendering::TextureCSPtr& in_texture, Direction in_direction, f32 in_leftOrBottom, f32 in_rightOrTop);
            //----------------------------------------------------------------------------------------
            /// Constructor
            ///
            /// @author Ian Copland
            ///
            /// @param The texture.
            /// @param The texture atlas.
            /// @param The atlas id.
            /// @param The direction the drawable will stretch.
            /// @param The left inset if a horizontal 3-patch or the bottom inset if a vertical
            /// 3-patch. This should be provided as a normalised fraction, 0.0 - 1.0.
            /// @param The right inset if a horizontal 3-patch or the top inset if a vertical 3-patch.
            /// This should be provided as a normalised fraction, 0.0 - 1.0.
            //----------------------------------------------------------------------------------------
            ThreePatchDrawable(const Rendering::TextureCSPtr& in_texture, const Rendering::TextureAtlasCSPtr& in_atlas, const std::string& in_atlasId, Direction in_direction, f32 in_leftOrBottom, f32 in_rightOrTop);
            
            CalculateUVsDelegate m_uvCalculationDelegate;
            CalculateSizesDelegate m_sizeCalculationDelegate;
            CalculatePositionsDelegate m_positionCalculationDelegate;
            CalculateOffsetDelegate m_offsetCalculationDelegate;
            
            Rendering::TextureCSPtr m_texture;
            Rendering::TextureAtlasCSPtr m_atlas;
            Rendering::TextureAtlas::Frame m_atlasFrame;
            Rendering::UVs m_uvs;
            std::string m_atlasId;
            Core::Colour m_colour;
            
            std::array<Rendering::UVs, k_numPatches> m_cachedUvs;
            std::array<Core::Vector2, k_numPatches> m_cachedSizes;
            std::array<Core::Vector2, k_numPatches> m_cachedPositions;
            Core::Vector2 m_cachedOffsetTL;
            Core::Vector2 m_cachedWidgetSize;
            
            f32 m_leftOrBottomInset = 0.01f;
            f32 m_rightOrTopInset = 0.01f;
            
            bool m_isPatchCatchValid = false;
        };
    }
}

#endif