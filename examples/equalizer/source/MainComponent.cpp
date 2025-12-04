#include "MainComponent.h"
#include <AudioSettingsComponent.h>

//==============================================================================
MainComponent::MainComponent()
{
    juce::PropertiesFile::Options options;
    options.applicationName = "CapabilityInquiryDemo";
    options.filenameSuffix = "settings";
    options.osxLibrarySubFolder = "Application Support";
    _applicationProperties.setStorageParameters(options);

    // Setup the command manager.
    setApplicationCommandManagerToWatch(&_commandManager);
    
    // Set this component to be the target for all commands.
    _commandManager.setFirstCommandTarget(this);

    // Register all commands that this target can perform.
    _commandManager.registerAllCommandsForTarget(this);
    addKeyListener(_commandManager.getKeyMappings());

    // Create and display the main menu.
    _menuBarComponent.reset(new juce::MenuBarComponent(this));
    addAndMakeVisible(_menuBarComponent.get());

    _debugComponent.reset(new DebugComponent(_audioDeviceManager, _applicationProperties));
    addAndMakeVisible(_debugComponent.get());

    setWantsKeyboardFocus(true);
    setOpaque(true);
    setSize(600, 440);

}

MainComponent::~MainComponent()
{
    _menuBarComponent->setModel(nullptr);
    _commandManager.setFirstCommandTarget(nullptr);
    //_mainMenuModel = nullptr;
    _debugComponent = nullptr;
}

//==============================================================================

void MainComponent::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill 
    // the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    auto bounds = getLocalBounds();
    {
        _menuBarComponent->setBounds(bounds.removeFromTop(juce::LookAndFeel::getDefaultLookAndFeel()
                                    .getDefaultMenuBarHeight()));
    }
    _debugComponent->setBounds(bounds);
    //_audioSettingsComponent.setBounds(bounds);
}

// --------------------------------------------------------------------------

//void MainComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
//{
//}

// --------------------------------------------------------------------------

void MainComponent::lookAndFeelChanged()
{
    //diagnosticsBox.applyFontToAllText(diagnosticsBox.getFont());
}

// --------------------------------------------------------------------------

void MainComponent::showDialogWindow()
{
    juce::String m;

    m << "Dialog Windows can be used to quickly show a component, usually blocking mouse input to other windows." 
        << juce::newLine
        << juce::newLine
        << "They can also be quickly closed with the escape key, try it now.";

    juce::DialogWindow::LaunchOptions options;
    
    // Create the content component to go inside the dialog window.
    AudioSettingsComponent* audioSettingsComponent = new AudioSettingsComponent(_audioDeviceManager);
    // The dialog takes ownership of the content component, so use setOwned().
    options.content.setOwned(audioSettingsComponent);
    options.dialogTitle = "Audio Settings";
    //options.dialogBackgroundColour = juce::Colour(0xff0e345a);
    options.escapeKeyTriggersCloseButton = true;
    //options.useNativeTitleBar = false;
    options.resizable = true;

    _dialogWindow = options.launchAsync();

    if (_dialogWindow != nullptr)
    {
        juce::Rectangle bounds = audioSettingsComponent->getBounds();
        _dialogWindow->centreAroundComponent(this, bounds.getWidth(), bounds.getHeight());
    }
}

// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
// Inherited via ApplicationCommandTarget

juce::ApplicationCommandTarget* MainComponent::getNextCommandTarget() {
    return nullptr;
};

// Inherited via ApplicationCommandTarget
// Return all commands that this ApplicationCommandTarget can perform.
void MainComponent::getAllCommands(juce::Array<juce::CommandID>& commands) {
    juce::Array<juce::CommandID> c {
        CommandIDs::audioSetupCommandID,
        CommandIDs::exitAppCommandID
    };
    commands.addArray(c);
}

// Inherited via ApplicationCommandTarget
void MainComponent::getCommandInfo(juce::CommandID commandID, juce::ApplicationCommandInfo& result) {
    switch (commandID)
    {
        case CommandIDs::audioSetupCommandID:
            result.setInfo("AudioSetup", "Displays the audio options window", "FileMenu", 0);
            result.addDefaultKeypress('a', juce::ModifierKeys::shiftModifier);
            break;
        case CommandIDs::exitAppCommandID:
            result.setInfo("Exit", "Exit the application", "FileMenu", 0);
            result.addDefaultKeypress('q', juce::ModifierKeys::shiftModifier);
            break;
        default:
            break;
    }
};

bool MainComponent::perform(const InvocationInfo& info) {
    switch (info.commandID)
    {
        case CommandIDs::audioSetupCommandID:
            showDialogWindow();
            //_audioSettingsComponent.showAudioSettingsDialog();
            break;
        case CommandIDs::exitAppCommandID:
            juce::JUCEApplication::getInstance()->systemRequestedQuit();
            break;
        default:
            break;
    }
    return true;
}

// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
// Inherited via MenuBarModel
juce::StringArray MainComponent::getMenuBarNames()
{
    return { "File", "Options", "Help"};
}

juce::PopupMenu MainComponent::getMenuForIndex(int menuIndex, const juce::String& menuName)
{
    juce::PopupMenu menu;

    if (menuIndex == 0) {
        menu.addCommandItem(&_commandManager, 1, "Audio");
        menu.addSeparator();
        menu.addCommandItem(&_commandManager, 2, "Exit");
    }
    return menu;
}

void MainComponent::menuItemSelected(int menuItemID, int menuIndex)
{
}
;

// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
