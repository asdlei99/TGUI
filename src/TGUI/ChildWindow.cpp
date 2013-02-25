/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012 Bruno Van de Velde (vdv_b@tgui.eu)
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


#include <TGUI/Objects.hpp>
#include <TGUI/GroupObject.hpp>
#include <TGUI/ClickableObject.hpp>
#include <TGUI/Button.hpp>
#include <TGUI/Panel.hpp>
#include <TGUI/ChildWindow.hpp>

#include <SFML/OpenGL.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ChildWindow::ChildWindow() :
    m_TitleBarHeight   (0),
    m_LoadedPathname   (""),
    m_SplitImage       (false),
    m_Opacity          (255),
    m_DistanceToSide   (5),
    m_TitleAlignment   (TitleAlignmentCentered),
    m_BorderColor      (0, 0, 0),
    m_TextureTitleBar_L(NULL),
    m_TextureTitleBar_M(NULL),
    m_TextureTitleBar_R(NULL)
    {
        m_Callback.objectType = Type_ChildWindow;
        m_CloseButton = new tgui::Button();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ChildWindow::ChildWindow(const ChildWindow& childWindowToCopy) :
    GroupObject        (childWindowToCopy),
    ObjectBorders      (childWindowToCopy),
    m_BackgtoundTexture(childWindowToCopy.m_BackgroundTexture),
    m_TitleText        (childWindowToCopy.m_TitleText),
    m_TitleBarHeight   (childWindowToCopy.m_TitleBarHeight),
    m_LoadedPathname   (childWindowToCopy.m_LoadedPathname),
    m_SplitImage       (childWindowToCopy.m_SplitImage),
    m_DraggingPosition (childWindowToCopy.m_DraggingPosition),
    m_Opacity          (childWindowToCopy.m_Opacity),
    m_DistanceToSide   (childWindowToCopy.m_DistanceToSide),
    m_TitleAlignment   (childWindowToCopy.m_TitleAlignment),
    m_BorderColor      (childWindowToCopy.m_BorderColor)
    {
        // Copy the textures
        if (TGUI_TextureManager.copyTexture(childWindowToCopy.m_TextureTitleBar_L, m_TextureTitleBar_L))   m_SpriteTitleBar_L.setTexture(*m_TextureTitleBar_L);
        if (TGUI_TextureManager.copyTexture(childWindowToCopy.m_TextureTitleBar_M, m_TextureTitleBar_M))   m_SpriteTitleBar_M.setTexture(*m_TextureTitleBar_M);
        if (TGUI_TextureManager.copyTexture(childWindowToCopy.m_TextureTitleBar_R, m_TextureTitleBar_R))   m_SpriteTitleBar_R.setTexture(*m_TextureTitleBar_R);

        // Copy the button
        m_CloseButton = new tgui::Button(*childWindowToCopy.m_CloseButton);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ChildWindow::~ChildWindow()
    {
        if (m_TextureTitleBar_L != NULL)   TGUI_TextureManager.removeTexture(m_TextureTitleBar_L);
        if (m_TextureTitleBar_M != NULL)   TGUI_TextureManager.removeTexture(m_TextureTitleBar_M);
        if (m_TextureTitleBar_R != NULL)   TGUI_TextureManager.removeTexture(m_TextureTitleBar_R);

        delete m_CloseButton;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ChildWindow& ChildWindow::operator= (const ChildWindow& right)
    {
        // Make sure it is not the same object
        if (this != &right)
        {
            ChildWindow temp(right);
            this->GroupObject::operator=(right);
            this->ObjectBorders::operator=(right);

            // Delete the old close button
            delete m_CloseButton;

            std::swap(m_TitleText,         temp.m_TitleText);
            std::swap(m_TitleBarHeight,    temp.m_TitleBarHeight);
            std::swap(m_LoadedPathname,    temp.m_LoadedPathname);
            std::swap(m_SplitImage,        temp.m_SplitImage);
            std::swap(m_DraggingPosition,  temp.m_DraggingPosition);
            std::swap(m_Opacity,           temp.m_Opacity);
            std::swap(m_DistanceToSide,    temp.m_DistanceToSide);
            std::swap(m_TitleAlignment,    temp.m_TitleAlignment);
            std::swap(m_BorderColor,       temp.m_BorderColor);
            std::swap(m_TextureTitleBar_L, temp.m_TextureTitleBar_L);
            std::swap(m_TextureTitleBar_M, temp.m_TextureTitleBar_M);
            std::swap(m_TextureTitleBar_R, temp.m_TextureTitleBar_R);
            std::swap(m_SpriteTitleBar_L,  temp.m_SpriteTitleBar_L);
            std::swap(m_SpriteTitleBar_M,  temp.m_SpriteTitleBar_M);
            std::swap(m_SpriteTitleBar_R,  temp.m_SpriteTitleBar_R);
            std::swap(m_CloseButton,       temp.m_CloseButton);
        }

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ChildWindow* ChildWindow::clone()
    {
        return new ChildWindow(*this);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool ChildWindow::load(const std::string& pathname, float width, float height, const sf::Color& bkgColor)
    {
        // Until the loading succeeds, the child window will be marked as unloaded
        m_Loaded = false;

        // Make sure that the pathname isn't empty
        if (pathname.empty())
            return false;

        // Set the background color of the child window
        m_BackgroundColor = bkgColor;

        // Store the filename
        m_LoadedPathname = pathname;

        // Set the size of the child window
        m_Size.x = width;
        m_Size.y = height;

        // When the pathname does not end with a "/" then we will add it
        if (m_LoadedPathname[m_LoadedPathname.length()-1] != '/')
            m_LoadedPathname.push_back('/');

        // Open the info file
        InfoFileParser infoFile;
        if (infoFile.openFile(m_LoadedPathname + "info.txt") == false)
        {
            TGUI_OUTPUT("TGUI error: Failed to open " + m_LoadedPathname + "info.txt");
            return false;
        }

        std::string property;
        std::string value;

        // Set some default settings
        m_SplitImage = false;
        m_DistanceToSide = 5;
        std::string imageExtension = "png";

        // Read untill the end of the file
        while (infoFile.readProperty(property, value))
        {
            // Check what the property is
            if (property.compare("splitimage") == 0)
            {
                if ((value.compare("true") == 0) || (value.compare("1") == 0))
                {
                    /// TODO: Support SplitImage
                    TGUI_OUTPUT("TGUI fixme: SplitImage is not supported yet.");
//                    m_SplitImage = true;
                }
                else
                {
                    if ((value.compare("false") != 0) && (value.compare("0") != 0))
                        TGUI_OUTPUT("TGUI warning: Wrong value passed to SplitImage: \"" + value + "\".");
                }
            }
            else if (property.compare("extension") == 0)
            {
                imageExtension = value;
            }
            else if (property.compare("borders") == 0)
            {
                // Get the borders
                Vector4u borders;
                if (extractVector4u(value, borders))
                    setBorders(borders.x1, borders.x2, borders.x3, borders.x4);
            }
            else if (property.compare("distancetoside") == 0)
            {
                m_DistanceToSide = atoi(value.c_str());
            }
        }

        // Close the info file
        infoFile.closeFile();

        // Remove the textures when they were loaded before
        if (m_TextureTitleBar_L != NULL)   TGUI_TextureManager.removeTexture(m_TextureTitleBar_L);
        if (m_TextureTitleBar_M != NULL)   TGUI_TextureManager.removeTexture(m_TextureTitleBar_M);
        if (m_TextureTitleBar_R != NULL)   TGUI_TextureManager.removeTexture(m_TextureTitleBar_R);

        // Check if the title bar image is split
        if (m_SplitImage)
        {
            /// TODO: Support SplitImage
            return false;
        }
        else // The title bar image isn't split
        {
            // Load the required texture
            if ((TGUI_TextureManager.getTexture(m_LoadedPathname + "TitleBar." + imageExtension, m_TextureTitleBar_M)))
            {
                 m_SpriteTitleBar_M.setTexture(*m_TextureTitleBar_M, true);
                 m_TitleBarHeight = m_TextureTitleBar_M->getSize().y;
            }
            else
                return false;

            // Load the close button
            if (m_CloseButton->load(m_LoadedPathname + "/Close") == false)
                return false;
        }

        m_TitleText.setCharacterSize(m_TitleBarHeight * 8 / 10);

        // When there is no error we will return true
        return m_Loaded = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ChildWindow::setSize(float width, float height)
    {
        // A negative size is not allowed for this object
        if (width  < 0) width  = -width;
        if (height < 0) height = -height;

        // Set the size of the window
        m_Size.x = width;
        m_Size.y = height;

        // If there is a background texture then resize it
        if (m_BackgroundTexture)
            m_BackgroundSprite.setScale(m_Size.x / m_BackgroundTexture->getSize().x, m_Size.y / m_BackgroundTexture->getSize().y);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2f ChildWindow::getSize() const
    {
        return Vector2f(m_Size.x, m_Size.y);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::string ChildWindow::getLoadedPathname() const
    {
        return m_LoadedPathname;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ChildWindow::setBackgroundTexture(sf::Texture *const texture)
    {
        // Store the texture
        m_BackgroundTexture = texture;

        // Set the texture for the sprite
        if (m_BackgroundTexture)
        {
            m_BackgroundSprite.setTexture(*m_BackgroundTexture, true);
            m_BackgroundSprite.setScale(m_Size.x / m_BackgroundTexture->getSize().x, m_Size.y / m_BackgroundTexture->getSize().y);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::Texture* ChildWindow::getBackgroundTexture()
    {
        return m_BackgroundTexture;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ChildWindow::setTitlebarHeight(unsigned int height)
    {
        // Don't continue when the child window has not been loaded yet
        if (m_Loaded == false)
            return;

        // Remember the new title bar height
        m_TitleBarHeight = height;

        // Set the size of the close button
        m_CloseButton->setSize(static_cast<float>(height) / m_TextureTitleBar_M->getSize().y * m_CloseButton->getSize().x,
                               static_cast<float>(height) / m_TextureTitleBar_M->getSize().y * m_CloseButton->getSize().y);

        // Set the size of the text in the title bar
        m_TitleText.setCharacterSize(m_TitleBarHeight * 8 / 10);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int ChildWindow::getTitleBarHeight() const
    {
        return m_TitleBarHeight;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ChildWindow::setBackgroundColor(const sf::Color& backgroundColor)
    {
        m_BackgroundColor = backgroundColor;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const sf::Color& ChildWindow::getBackgroundColor() const
    {
        return m_BackgroundColor;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ChildWindow::setTransparency(unsigned char transparency)
    {
        // Store the new transparency
        m_Opacity = transparency;

        m_SpriteTitleBar_L.setColor(sf::Color(255, 255, 255, m_Opacity));
        m_SpriteTitleBar_M.setColor(sf::Color(255, 255, 255, m_Opacity));
        m_SpriteTitleBar_R.setColor(sf::Color(255, 255, 255, m_Opacity));

        m_CloseButton->m_SpriteNormal_L.setColor(sf::Color(255, 255, 255, m_Opacity));
        m_CloseButton->m_SpriteNormal_M.setColor(sf::Color(255, 255, 255, m_Opacity));
        m_CloseButton->m_SpriteNormal_R.setColor(sf::Color(255, 255, 255, m_Opacity));

        m_CloseButton->m_SpriteMouseHover_L.setColor(sf::Color(255, 255, 255, m_Opacity));
        m_CloseButton->m_SpriteMouseHover_M.setColor(sf::Color(255, 255, 255, m_Opacity));
        m_CloseButton->m_SpriteMouseHover_R.setColor(sf::Color(255, 255, 255, m_Opacity));

        m_CloseButton->m_SpriteMouseDown_L.setColor(sf::Color(255, 255, 255, m_Opacity));
        m_CloseButton->m_SpriteMouseDown_M.setColor(sf::Color(255, 255, 255, m_Opacity));
        m_CloseButton->m_SpriteMouseDown_R.setColor(sf::Color(255, 255, 255, m_Opacity));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned char ChildWindow::getTransparency() const
    {
        return m_Opacity;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ChildWindow::setTitle(const sf::String& title)
    {
        m_TitleText.setString(title);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const sf::String& ChildWindow::getTitle() const
    {
        return m_TitleText.getString();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ChildWindow::setTitleColor(const sf::Color& color)
    {
        m_TitleText.setColor(color);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const sf::Color& ChildWindow::getTitleColor() const
    {
        return m_TitleText.getColor();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ChildWindow::setBorderColor(const sf::Color& borderColor)
    {
        m_BorderColor = borderColor;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const sf::Color& ChildWindow::getBorderColor() const
    {
        return m_BorderColor;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ChildWindow::setBorders(unsigned int leftBorder, unsigned int topBorder, unsigned int rightBorder, unsigned int bottomBorder)
    {
        // Set the new border size
        m_LeftBorder   = leftBorder;
        m_TopBorder    = topBorder;
        m_RightBorder  = rightBorder;
        m_BottomBorder = bottomBorder;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ChildWindow::setDistanceToSide(unsigned int distanceToSide)
    {
        m_DistanceToSide = distanceToSide;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int ChildWindow::getDistanceToSide() const
    {
        return m_DistanceToSide;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ChildWindow::setTitleAlignment(TitleAlignment alignment)
    {
        m_TitleAlignment = alignment;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ChildWindow::TitleAlignment ChildWindow::getTitleAlignment() const
    {
        return m_TitleAlignment;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ChildWindow::destroy()
    {
        m_Parent->remove(this);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2f ChildWindow::getDisplaySize()
    {
        return m_Size;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool ChildWindow::mouseOnObject(float x, float y)
    {
        // Don't continue when the child window has not been loaded yet
        if (m_Loaded == false)
            return false;

        // Check if the mouse is on top of the title bar
        if (getTransform().transformRect(sf::FloatRect(0, 0, m_Size.x + m_LeftBorder + m_RightBorder, static_cast<float>(m_TitleBarHeight + m_TopBorder))).contains(x, y))
        {
            m_EventManager.mouseNotOnObject();
            return true;
        }
        else
        {
            // Check if the mouse is inside the child window
            if (getTransform().transformRect(sf::FloatRect(0, 0, m_Size.x + m_LeftBorder + m_RightBorder, m_Size.y + m_TopBorder + m_BottomBorder)).contains(x, y - m_TitleBarHeight))
                return true;
            else
            {
                if (m_MouseHover)
                    mouseLeftObject();

                // Tell the objects inside the child window that the mouse is no longer on top of them
                m_EventManager.mouseNotOnObject();
                m_MouseHover = false;
                return false;
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ChildWindow::initialize(tgui::Group *const parent)
    {
        m_Parent = parent;
        setGlobalFont(m_Parent->getGlobalFont());
        m_TitleText.setFont(m_Parent->getGlobalFont());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ChildWindow::handleEvent(sf::Event& event, float mouseX, float mouseY)
    {
        // Don't continue when the child window has not been loaded yet
        if (m_Loaded == false)
            return;

        // Check if something has to be done differently with the event
        if ((event.type == sf::Event::MouseMoved) || (event.type == sf::Event::MouseButtonPressed) || (event.type == sf::Event::MouseButtonReleased))
        {
            // Check if you are dragging the child window
            if ((event.type == sf::Event::MouseMoved) && (m_MouseDown == true))
            {
                // Move the child window
                Vector2f position = getPosition();
                setPosition(position.x + (mouseX - position.x - m_DraggingPosition.x), position.y + (mouseY - position.y - m_DraggingPosition.y));

                // Add the callback (if the user requested it)
                if (m_CallbackFunctions[Moved].empty() == false)
                {
                    m_Callback.trigger = Moved;
                    m_Callback.position = getPosition();
                    addCallback();
                }
            }

            // Move the childwindow to the front when clicking on it
            if (event.type == sf::Event::MouseButtonPressed)
            {
                m_Parent->focusObject(this);
                m_Parent->moveObjectToFront(this);
            }

            // Check if the mouse is on top of the title bar
            if (getTransform().transformRect(sf::FloatRect(0, 0, m_Size.x + m_LeftBorder + m_RightBorder, static_cast<float>(m_TitleBarHeight))).contains(mouseX, mouseY))
            {
                // Get the current position and scale
                Vector2f position = getPosition();
                Vector2f curScale = getScale();

                // Temporary set the close button to the correct position
                m_CloseButton->setPosition(position.x + ((m_Size.x + m_LeftBorder + m_RightBorder - m_DistanceToSide - m_CloseButton->getSize().x) * curScale.x), position.y + ((m_TitleBarHeight / 2.f) - (m_CloseButton->getSize().x / 2.f)) * curScale.y);

                // Set the scale of the close button
                m_CloseButton->setScale(curScale);

                // Call the correct function of the button
                if (event.type == sf::Event::MouseMoved)
                {
                    // Send the hover event to the close button
                    if (m_CloseButton->mouseOnObject(mouseX, mouseY))
                        m_CloseButton->mouseMoved(mouseX, mouseY);
                }
                else if (event.type == sf::Event::MouseButtonPressed)
                {
                    // Send the mouse press event to the close button
                    if (m_CloseButton->mouseOnObject(mouseX, mouseY))
                        m_CloseButton->leftMousePressed(mouseX, mouseY);
                    else
                    {
                        // The mouse went down on the title bar
                        m_MouseDown = true;

                        // Remember where we are dragging the title bar
                        m_DraggingPosition.x = mouseX - position.x;
                        m_DraggingPosition.y = mouseY - position.y;
                    }
                }
                else if (event.type == sf::Event::MouseButtonReleased)
                {
                     m_MouseDown = false;

                    // Check if the close button was clicked
                    if (m_CloseButton->m_MouseDown == true)
                    {
                        m_CloseButton->m_MouseDown = false;

                        // Check if the mouse is still on the close button
                        if (m_CloseButton->mouseOnObject(mouseX, mouseY))
                        {
                            // If a callback was requested then send it
                            if (m_CallbackFunctions[Closed].empty() == false)
                            {
                                m_Callback.trigger = Closed;
                                addCallback();
                            }
                            else // The user won't stop the closing, so destroy the window
                            {
                                destroy();
                                return;
                            }
                        }
                    }
                }

                // Reset the position and scale of the button
                m_CloseButton->setPosition(0, 0);
                m_CloseButton->setScale(1, 1);

                // Tell the objects that the mouse is no longer down
                m_EventManager.mouseNoLongerDown();
                return;
            }
            else // The mouse is not on top of the titlebar
            {
                // When the mouse went up then change the mouse down flag
                if (event.type == sf::Event::MouseButtonReleased)
                {
                    m_MouseDown = false;
                    m_CloseButton->mouseNoLongerDown();
                }

                // Check if the mouse is on top of the borders
                if ((getTransform().transformRect(sf::FloatRect(0, 0, m_Size.x + m_LeftBorder + m_RightBorder, m_Size.y + m_TopBorder + m_BottomBorder + m_TitleBarHeight)).contains(mouseX, mouseY))
                &&  (getTransform().transformRect(sf::FloatRect(static_cast<float>(m_LeftBorder), static_cast<float>(m_TitleBarHeight + m_TopBorder), m_Size.x, m_Size.y)).contains(mouseX, mouseY) == false))
                {
                    // If the mouse was released then tell the objects about it
                    if (event.type == sf::Event::MouseButtonReleased)
                        m_EventManager.mouseNoLongerDown();

                    // Don't send the event to the objects
                    return;
                }
            }
        }

        // Let the child window handle the rest
        GroupObject::handleEvent(event, mouseX - (m_LeftBorder * getScale().x), mouseY - ((m_TitleBarHeight + m_TopBorder) * getScale().y));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ChildWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // Don't draw when the child window wasn't created
        if (m_Loaded == false)
            return;

        // Get the current position and scale
        Vector2f position = getPosition();
        Vector2f curScale = getScale();

        // Calculate the scale factor of the view
        float scaleViewX = target.getSize().x / target.getView().getSize().x;
        float scaleViewY = target.getSize().y / target.getView().getSize().y;

        Vector2f viewPosition = (target.getView().getSize() / 2.f) - target.getView().getCenter();

        // Get the global position
        Vector2f topLeftPanelPosition = states.transform.transformPoint(position.x + (m_LeftBorder * curScale.x) + viewPosition.x,
                                                                        position.y + ((m_TitleBarHeight + m_TopBorder) * curScale.y) + viewPosition.y);
        Vector2f bottomRightPanelPosition = states.transform.transformPoint(position.x + ((m_Size.x + m_LeftBorder) * curScale.x) + viewPosition.x,
                                                                            position.y + ((m_TitleBarHeight + m_Size.y + m_TopBorder) * curScale.y) + viewPosition.y);
        Vector2f topLeftTitleBarPosition;
        Vector2f bottomRightTitleBarPosition;

        topLeftTitleBarPosition = states.transform.transformPoint(position.x + m_DistanceToSide + viewPosition.x,
                                                                  position.y + viewPosition.y);
        bottomRightTitleBarPosition = states.transform.transformPoint(position.x + ((m_Size.x + m_LeftBorder + m_RightBorder - (2*m_DistanceToSide) - m_CloseButton->getScaledSize().x) * curScale.x) + viewPosition.x,
                                                                      position.y + (m_TitleBarHeight * curScale.y) + viewPosition.y);

        // Adjust the transformation
        states.transform *= getTransform();

        sf::Transform oldTransform = states.transform;

        // Check if the title bar image is split
        if (m_SplitImage)
        {
            // Split image is not supported yet
            return;
        }
        else // The title bar image isn't split
        {
            // Scale the title bar
            states.transform.scale((m_Size.x + m_LeftBorder + m_RightBorder) / m_TextureTitleBar_M->getSize().x, static_cast<float>(m_TitleBarHeight) / m_TextureTitleBar_M->getSize().y);

            // Draw the title bar
            target.draw(m_SpriteTitleBar_M, states);

            // Undo the scaling
            states.transform.scale(static_cast<float>(m_TextureTitleBar_M->getSize().x) / (m_Size.x + m_LeftBorder + m_RightBorder), static_cast<float>(m_TextureTitleBar_M->getSize().y) / m_TitleBarHeight);
        }

        // Get the old clipping area
        GLint scissor[4];
        glGetIntegerv(GL_SCISSOR_BOX, scissor);

        // Check if there is a title
        if (m_TitleText.getString().isEmpty() == false)
        {
            // Calculate the clipping area
            GLint scissorLeft = TGUI_MAXIMUM(static_cast<GLint>(topLeftTitleBarPosition.x * scaleViewX), scissor[0]);
            GLint scissorTop = TGUI_MAXIMUM(static_cast<GLint>(topLeftTitleBarPosition.y * scaleViewY), static_cast<GLint>(target.getSize().y) - scissor[1] - scissor[3]);
            GLint scissorRight = TGUI_MINIMUM(static_cast<GLint>(bottomRightTitleBarPosition.x * scaleViewX), scissor[0] + scissor[2]);
            GLint scissorBottom = TGUI_MINIMUM(static_cast<GLint>(bottomRightTitleBarPosition.y * scaleViewY), static_cast<GLint>(target.getSize().y) - scissor[1]);

            // If the object outside the window then don't draw anything
            if (scissorRight < scissorLeft)
                scissorRight = scissorLeft;
            else if (scissorBottom < scissorTop)
                scissorTop = scissorBottom;

            // Set the clipping area
            glScissor(scissorLeft, target.getSize().y - scissorBottom, scissorRight - scissorLeft, scissorBottom - scissorTop);

            // Draw the text, depending on the alignment
            if (m_TitleAlignment == TitleAlignmentLeft)
            {
                states.transform.translate(static_cast<float>(m_DistanceToSide), 0);
                target.draw(m_TitleText, states);
                states.transform.translate(-static_cast<float>(m_DistanceToSide), 0);
            }
            else if (m_TitleAlignment == TitleAlignmentCentered)
            {
                states.transform.translate(m_DistanceToSide + (((m_Size.x + m_LeftBorder + m_RightBorder) - 3*m_DistanceToSide - m_CloseButton->getScaledSize().x - m_TitleText.getGlobalBounds().width) / 2.0f), 0);
                target.draw(m_TitleText, states);
                states.transform.translate(-(m_DistanceToSide + (((m_Size.x + m_LeftBorder + m_RightBorder) - 3*m_DistanceToSide - m_CloseButton->getScaledSize().x - m_TitleText.getGlobalBounds().width) / 2.0f)), 0);
            }
            else // if (m_TitleAlignment == TitleAlignmentRight)
            {
                states.transform.translate((m_Size.x + m_LeftBorder + m_RightBorder) - 2*m_DistanceToSide - m_CloseButton->getScaledSize().x - m_TitleText.getGlobalBounds().width, 0);
                target.draw(m_TitleText, states);
                states.transform.translate(-(m_Size.x + m_LeftBorder + m_RightBorder) + 2*m_DistanceToSide + m_CloseButton->getScaledSize().x + m_TitleText.getGlobalBounds().width, 0);
            }

            // Reset the old clipping area
            glScissor(scissor[0], scissor[1], scissor[2], scissor[3]);
        }

        // Move the close button to the correct position
        states.transform.translate((m_Size.x + m_LeftBorder + m_RightBorder) - m_DistanceToSide - m_CloseButton->getSize().x, (m_TitleBarHeight - m_CloseButton->getSize().y) / 2.f);

        // Draw the close button
        target.draw(*m_CloseButton, states);

        // Set the correct transformation
        states.transform = oldTransform.translate(0, static_cast<float>(m_TitleBarHeight));

        // Draw the borders
		sf::RectangleShape borders(Vector2f(m_Size.x + m_LeftBorder + m_RightBorder, m_Size.y + m_TopBorder + m_BottomBorder));
        borders.setFillColor(m_BorderColor);
        target.draw(borders, states);

        // Make room for the borders
        states.transform.translate(static_cast<float>(m_LeftBorder), static_cast<float>(m_TopBorder));

        // Draw the background
        if (m_BackgroundColor != sf::Color::Transparent)
        {
            sf::RectangleShape background(Vector2f(m_Size.x, m_Size.y));
            background.setFillColor(m_BackgroundColor);
            target.draw(background, states);
        }

        // Draw the background image if there is one
        if (m_BackgroundTexture != NULL)
            target.draw(m_BackgroundSprite, states);

        // Calculate the clipping area
        GLint scissorLeft = TGUI_MAXIMUM(static_cast<GLint>(topLeftPanelPosition.x * scaleViewX), scissor[0]);
        GLint scissorTop = TGUI_MAXIMUM(static_cast<GLint>(topLeftPanelPosition.y * scaleViewY), static_cast<GLint>(target.getSize().y) - scissor[1] - scissor[3]);
        GLint scissorRight = TGUI_MINIMUM(static_cast<GLint>(bottomRightPanelPosition.x * scaleViewX), scissor[0] + scissor[2]);
        GLint scissorBottom = TGUI_MINIMUM(static_cast<GLint>(bottomRightPanelPosition.y * scaleViewY), static_cast<GLint>(target.getSize().y) - scissor[1]);

        // If the object outside the window then don't draw anything
        if (scissorRight < scissorLeft)
            scissorRight = scissorLeft;
        else if (scissorBottom < scissorTop)
            scissorTop = scissorBottom;

        // Set the clipping area
        glScissor(scissorLeft, target.getSize().y - scissorBottom, scissorRight - scissorLeft, scissorBottom - scissorTop);

        // Draw the objects in the child window
        drawObjectGroup(&target, states);

        // Reset the old clipping area
        glScissor(scissor[0], scissor[1], scissor[2], scissor[3]);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
