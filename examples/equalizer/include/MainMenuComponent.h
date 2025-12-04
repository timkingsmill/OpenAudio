#pragma once

#include "JuceHeader.h"
#include "MainMenuModel.h"

//==============================================================================
class MainMenuComponent final : public juce::Component,
                        //public juce::ApplicationCommandTarget,
                        public juce::MenuBarModel
{
public:
    //==============================================================================
    /** A list of the commands that this demo responds to. */
    enum CommandIDs
    {
        outerColourRed = 1,
        outerColourGreen,
        outerColourBlue,
        innerColourRed,
        innerColourGreen,
        innerColourBlue
    };

    //==============================================================================
    MainMenuComponent()
    {
        menuBar.reset (new juce::MenuBarComponent(this));
        addAndMakeVisible (menuBar.get());
        setApplicationCommandManagerToWatch(&commandManager);
        //commandManager.registerAllCommandsForTarget(this);

        // this ensures that commands invoked on the DemoRunner application are correctly
        // forwarded to this demo
        //commandManager.setFirstCommandTarget (this);
        commandManager.setFirstCommandTarget(&outerCommandTarget);

        // this lets the command manager use keypresses that arrive in our window to send out commands
        addKeyListener (commandManager.getKeyMappings());

        addAndMakeVisible (outerCommandTarget);

        setWantsKeyboardFocus (true);

        setSize (500, 500);
    }

    ~MainMenuComponent() override
    {
       #if JUCE_MAC
        MenuBarModel::setMacMainMenu (nullptr);
       #endif

        commandManager.setFirstCommandTarget (nullptr);
    }

    void resized() override
    {
        auto b = getLocalBounds();

        menuBar->setBounds (b.removeFromTop (juce::LookAndFeel::getDefaultLookAndFeel()
                                                               .getDefaultMenuBarHeight()));
        outerCommandTarget.setBounds (b);
    }

    //==============================================================================
    
    juce::StringArray getMenuBarNames() override
    {
        return { "Outer Colour", "Inner Colour" };
    }

    juce::PopupMenu getMenuForIndex (int menuIndex, const juce::String&) override
    {
        juce::PopupMenu menu;

        if (menuIndex == 0)
        {
            menu.addCommandItem (&commandManager, CommandIDs::outerColourRed);
            menu.addCommandItem (&commandManager, CommandIDs::outerColourGreen);
            menu.addCommandItem (&commandManager, CommandIDs::outerColourBlue);
        }
        else if (menuIndex == 1)
        {
            menu.addCommandItem (&commandManager, CommandIDs::innerColourRed);
            menu.addCommandItem (&commandManager, CommandIDs::innerColourGreen);
            menu.addCommandItem (&commandManager, CommandIDs::innerColourBlue);
        }

        return menu;
    }

    void menuItemSelected (int, int ) override {}

    //==============================================================================
    // The following methods implement the ApplicationCommandTarget interface, allowing
    // this window to publish a set of actions it can perform, and which can be mapped
    // onto menus, keypresses, etc.

    /**********************
    ApplicationCommandTarget* getNextCommandTarget() override
    {
        return &outerCommandTarget;
    }

    void getAllCommands (juce::Array<juce::CommandID>&) override
    {
    }

    void getCommandInfo (juce::CommandID, juce::ApplicationCommandInfo& ) override
    {
    }

    bool perform (const InvocationInfo&) override
    {
        return true;
    }
    **********************/


private:
   #if JUCE_DEMO_RUNNER
    ApplicationCommandManager& commandManager = getGlobalCommandManager();
   #else
    juce::ApplicationCommandManager commandManager;
   #endif

    std::unique_ptr<juce::MenuBarComponent> menuBar;
    MainMenuModel _menuModel;

    //==============================================================================
    /**
        Command messages that aren't handled in the main component will be passed
        to this class to respond to.
    */
    class OuterCommandTarget final : public Component,
                                     public juce::ApplicationCommandTarget
    {
    public:
        OuterCommandTarget (juce::ApplicationCommandManager& m)
            : commandManager (m),
              innerCommandTarget (commandManager)
        {
            commandManager.registerAllCommandsForTarget (this);

            addAndMakeVisible (innerCommandTarget);
        }

        void resized() override
        {
            innerCommandTarget.setBounds (getLocalBounds().reduced (50));
        }

        void paint (juce::Graphics& g) override
        {
            g.fillAll (currentColour);
        }

        //==============================================================================
        ApplicationCommandTarget* getNextCommandTarget() override
        {
            return &innerCommandTarget;
        }

        void getAllCommands (juce::Array<juce::CommandID>& c) override
        {
            juce::Array<juce::CommandID> commands { CommandIDs::outerColourRed,
                                                    CommandIDs::outerColourGreen,
                                                    CommandIDs::outerColourBlue };

            c.addArray (commands);
        }

        void getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result) override
        {
            switch (commandID)
            {
                case CommandIDs::outerColourRed:
                    result.setInfo ("Red", "Sets the outer colour to red", "Outer", 0);
                    result.setTicked (currentColour == juce::Colours::red);
                    result.addDefaultKeypress ('r', juce::ModifierKeys::commandModifier);
                    break;
                case CommandIDs::outerColourGreen:
                    result.setInfo ("Green", "Sets the outer colour to green", "Outer", 0);
                    result.setTicked (currentColour == juce::Colours::green);
                    result.addDefaultKeypress ('g', juce::ModifierKeys::commandModifier);
                    break;
                case CommandIDs::outerColourBlue:
                    result.setInfo ("Blue", "Sets the outer colour to blue", "Outer", 0);
                    result.setTicked (currentColour == juce::Colours::blue);
                    result.addDefaultKeypress ('b', juce::ModifierKeys::commandModifier);
                    break;
                default:
                    break;
            }
        }

        bool perform (const InvocationInfo& info) override
        {
            switch (info.commandID)
            {
                case CommandIDs::outerColourRed:
                    currentColour = juce::Colours::red;
                    break;
                case CommandIDs::outerColourGreen:
                    currentColour = juce::Colours::green;
                    break;
                case CommandIDs::outerColourBlue:
                    currentColour = juce::Colours::blue;
                    break;
                default:
                    return false;
            }

            repaint();
            return true;
        }

    private:
        //==============================================================================
        /**
            Command messages that aren't handled in the OuterCommandTarget will be passed
            to this class to respond to.
        */
        struct InnerCommandTarget final : public Component,
                                          public ApplicationCommandTarget
        {
            InnerCommandTarget (juce::ApplicationCommandManager& m)
                : commandManager (m)
            {
                commandManager.registerAllCommandsForTarget (this);
            }

            void paint (juce::Graphics& g) override
            {
                g.fillAll (currentColour);
            }

            //==============================================================================
            ApplicationCommandTarget* getNextCommandTarget() override
            {
                // this will return the next parent component that is an ApplicationCommandTarget
                return findFirstTargetParentComponent();
            }

            void getAllCommands (juce::Array<juce::CommandID>& c) override
            {
                juce::Array<juce::CommandID> commands { CommandIDs::innerColourRed,
                                                        CommandIDs::innerColourGreen,
                                                        CommandIDs::innerColourBlue };

                c.addArray (commands);
            }

            void getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result) override
            {
                switch (commandID)
                {
                    case CommandIDs::innerColourRed:
                        result.setInfo ("Red", "Sets the inner colour to red", "Inner", 0);
                        result.setTicked (currentColour == juce::Colours::red);
                        result.addDefaultKeypress ('r', juce::ModifierKeys::commandModifier | juce::ModifierKeys::shiftModifier);
                        break;
                    case CommandIDs::innerColourGreen:
                        result.setInfo ("Green", "Sets the inner colour to green", "Inner", 0);
                        result.setTicked (currentColour == juce::Colours::green);
                        result.addDefaultKeypress ('g', juce::ModifierKeys::commandModifier | juce::ModifierKeys::shiftModifier);
                        break;
                    case CommandIDs::innerColourBlue:
                        result.setInfo ("Blue", "Sets the inner colour to blue", "Inner", 0);
                        result.setTicked (currentColour == juce::Colours::blue);
                        result.addDefaultKeypress ('b', juce::ModifierKeys::commandModifier | juce::ModifierKeys::shiftModifier);
                        break;
                    default:
                        break;
                }
            }

            bool perform (const InvocationInfo& info) override
            {
                switch (info.commandID)
                {
                    case CommandIDs::innerColourRed:
                        currentColour = juce::Colours::red;
                        break;
                    case CommandIDs::innerColourGreen:
                        currentColour = juce::Colours::green;
                        break;
                    case CommandIDs::innerColourBlue:
                        currentColour = juce::Colours::blue;
                        break;
                    default:
                        return false;
                }

                repaint();
                return true;
            }

            juce::ApplicationCommandManager& commandManager;

            juce::Colour currentColour { juce::Colours::blue };
        };

        juce::ApplicationCommandManager& commandManager;
        InnerCommandTarget innerCommandTarget;

        juce::Colour currentColour { juce::Colours::red };
    };

    OuterCommandTarget outerCommandTarget { commandManager };

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainMenuComponent)
};
