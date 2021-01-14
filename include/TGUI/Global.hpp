/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2021 Bruno Van de Velde (vdv_b@tgui.eu)
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

#ifndef TGUI_GLOBAL_HPP
#define TGUI_GLOBAL_HPP

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TGUI/Config.hpp>
#include <TGUI/Exception.hpp>
#include <TGUI/Duration.hpp>
#include <TGUI/Font.hpp>
#include <cstdint>
#include <string>
#include <memory>

#ifdef TGUI_DEBUG
    #include <iostream>
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// Namespace that contains all TGUI functions and classes
namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Sets the default text size for all widgets created after calling the function
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API void setGlobalTextSize(unsigned int textSize);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves the default text size used for all new widgets
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API unsigned int getGlobalTextSize();


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Sets the double-click time for the mouse
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API void setDoubleClickTime(Duration duration);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves the double-click time for the mouse
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API Duration getDoubleClickTime();


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Sets a new resource path
    ///
    /// This pathname is placed in front of every filename that is used to load a resource.
    ///
    /// @param path  New resource path
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API void setResourcePath(const String& path);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Returns the resource path
    ///
    /// This pathname is placed in front of every filename that is used to load a resource.
    ///
    /// @return The current resource path
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API const String& getResourcePath();


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Changes the blink rate of the cursor in edit fields such as EditBox and TextArea
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API void setEditCursorBlinkRate(Duration blinkRate);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Returns the blink rate of the cursor in edit fields such as EditBox and TextArea
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API Duration getEditCursorBlinkRate();


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Opens a file and reads its contents into memory
    ///
    /// @param filename  Path to the file to read
    /// @param fileSize  Size of the file, to be filled in by this function if loading succeeds (untouched on failure)
    ///
    /// @return Bytes read from the file, or nullptr if loading failed
    ///
    /// On android, the file will be read using the asset manager if a relative filename is passed.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::unique_ptr<std::uint8_t[]> readFileToMemory(const String& filename, std::size_t& fileSize);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_GLOBAL_HPP

