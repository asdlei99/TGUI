/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2017 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef TGUI_SLIDER_RENDERER_HPP
#define TGUI_SLIDER_RENDERER_HPP


#include <TGUI/Renderers/WidgetRenderer.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    class TGUI_API SliderRenderer : public WidgetRenderer
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        SliderRenderer() = default;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        SliderRenderer(std::shared_ptr<RendererData> data)
        {
            setData(data);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the borders
        ///
        /// @param borders  Size of the borders
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBorders(const Borders& borders);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the size of the borders
        ///
        /// @return border size
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Borders getBorders() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the color of the track
        ///
        /// @param color  The new track color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTrackColor(Color color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the color of the track
        ///
        /// @return Track color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Color getTrackColor() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the color of the track in hover state (when the mouse is on top of it)
        ///
        /// @param color  The new hover track color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTrackColorHover(Color color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the color of the track in hover state (when the mouse is on top of it)
        ///
        /// @return Hover track color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Color getTrackColorHover() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the color of the thumb
        ///
        /// @param color  The new thumb color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setThumbColor(Color color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the color of the thumb
        ///
        /// @return Thumb color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Color getThumbColor() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the color of the thumb in hover state (when the mouse is on top of it)
        ///
        /// @param color  The new hover thumb color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setThumbColorHover(Color color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the color of the thumb in hover state (when the mouse is on top of it)
        ///
        /// @return Hover thumb color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Color getThumbColorHover() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the color of the borders
        ///
        /// @param color  New border color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBorderColor(Color color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the color of the borders
        ///
        /// @return Border color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Color getBorderColor() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the color of the borders in the hover state (when the mouse is on top of the slider)
        ///
        /// @param color  New border color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBorderColorHover(Color color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the color of the borders in the hover state (when the mouse is on top of the slider)
        ///
        /// @return Border color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Color getBorderColorHover() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the image of the track
        ///
        /// @param texture  The new track texture
        ///
        /// When this image and the thumb image are set, then the track and thumb color property will be ignored.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextureTrack(const Texture& texture);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the image of the track
        ///
        /// @return Track texture
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Texture& getTextureTrack() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the image of the track that is displayed when the mouse is on top of it
        ///
        /// @param texture  The new hover track texture
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextureTrackHover(const Texture& texture);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the image of the track that is displayed when the mouse is on top of it
        ///
        /// @return Hover track texture
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Texture& getTextureTrackHover() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the image of the thumb
        ///
        /// @param texture  The new thumb texture
        ///
        /// When this image and the track image are set, then the track and thumb color property will be ignored.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextureThumb(const Texture& texture);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the image of the thumb
        ///
        /// @return Thumb texture
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Texture& getTextureThumb() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the image of the thumb that is displayed when the mouse is on top of it
        ///
        /// @param texture  The new hover thumb texture
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextureThumbHover(const Texture& texture);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the image of the thumb that is displayed when the mouse is on top of it
        ///
        /// @return Hover thumb texture
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Texture& getTextureThumbHover() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_SLIDER_RENDERER_HPP
