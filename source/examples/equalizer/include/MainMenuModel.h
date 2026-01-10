#pragma once

#include "JuceHeader.h" 

class MainMenuModel final : public juce::MenuBarModel   
{

private:
    enum CommandIDs
    {
        outerColourRed = 1,
        outerColourGreen,
        outerColourBlue,
        innerColourRed,
        innerColourGreen,
        innerColourBlue
    };

private:
    /** This method must return a list of the names of the menus. */
    juce::StringArray getMenuBarNames()
    {
        return { "Outer Colour", "Inner Colour" };
    };

    /** This should return the popup menu to display for a given top-level menu.

        @param topLevelMenuIndex    the index of the top-level menu to show
        @param menuName             the name of the top-level menu item to show
    */
    virtual juce::PopupMenu getMenuForIndex(int topLevelMenuIndex,
                                            const juce::String& menuName)
    { 
        juce::PopupMenu menu;

        if (topLevelMenuIndex == 0)
        {
            //menu.addCommandItem(&commandManager, CommandIDs::outerColourRed);
            //menu.addCommandItem(&commandManager, CommandIDs::outerColourGreen);
            //menu.addCommandItem(&commandManager, CommandIDs::outerColourBlue);
        }
        else if (topLevelMenuIndex == 1)
        {
            //menu.addCommandItem(&commandManager, CommandIDs::innerColourRed);
            //menu.addCommandItem(&commandManager, CommandIDs::innerColourGreen);
            //menu.addCommandItem(&commandManager, CommandIDs::innerColourBlue);
        }

        return menu;
    };

    /** This is called when a menu item has been clicked on.

        @param menuItemID           the item ID of the PopupMenu item that was selected
        @param topLevelMenuIndex    the index of the top-level menu from which the item was
                                    chosen (just in case you've used duplicate ID numbers
                                    on more than one of the popup menus)
    */
    virtual void menuItemSelected(int menuItemID,
        int topLevelMenuIndex)
    {
    };

    //juce::ApplicationCommandManager commandManager;

};
