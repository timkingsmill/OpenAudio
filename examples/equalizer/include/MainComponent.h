#pragma once

// CMake builds don't use an AppConfig.h, so it's safe to include juce module headers
// directly. If you need to remain compatible with Projucer-generated builds, and
// have called `juce_generate_juce_header(<thisTarget>)` in your CMakeLists.txt,
// you could `#include <JuceHeader.h>` here instead, to make all your module headers visible.
#include <JuceHeader.h>
#include "DebugComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent final : 
    public juce::ApplicationCommandTarget,
    public juce::Component,
    public juce::MenuBarModel
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    enum CommandIDs
    {
        audioSetupCommandID = 1,
        exitAppCommandID
    };

    //==============================================================================
private:
    void showDialogWindow();


    // Inherited via ApplicationCommandTarget
    ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands(juce::Array<juce::CommandID>& commands) override;
    void getCommandInfo(juce::CommandID commandID, juce::ApplicationCommandInfo& result) override;
    bool perform(const InvocationInfo& info) override;

    // Inherited via MenuBarModel
    juce::StringArray getMenuBarNames() override;
    juce::PopupMenu getMenuForIndex(int menuIndex, const juce::String& menuName) override;
    void menuItemSelected(int menuItemID, int menuIndex) override;

    // Inherited via Component
    void lookAndFeelChanged() override;

private:
    //==============================================================================
    juce::ApplicationProperties _applicationProperties;
    juce::AudioDeviceManager _audioDeviceManager;

    std::unique_ptr<DebugComponent> _debugComponent;
    std::unique_ptr<juce::MenuBarComponent> _menuBarComponent;

    juce::ApplicationCommandManager _commandManager;
    juce::Component::SafePointer<juce::DialogWindow> _dialogWindow;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
