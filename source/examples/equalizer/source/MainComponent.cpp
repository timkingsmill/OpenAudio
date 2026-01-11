#include "MainComponent.h"
#include <AudioSettingsComponent.h>

//==============================================================================
/**
 * MainComponent constructor.
 *
 * Initializes application settings storage, command handling, key mappings, and UI child
 * components used by the example:
 *
 * - Configures persistent user settings via a juce::PropertiesFile::Options structure
 *   and applies them to the `_applicationProperties` member using
 *   `setStorageParameters`.
 * - Prepares command handling:
 *     - Registers this component as the target that the application's command manager watches
 *       via `setApplicationCommandManagerToWatch`.
 *     - Makes this object the first command target with `_commandManager.setFirstCommandTarget`.
 *     - Registers all commands that this target can perform with
 *       `_commandManager.registerAllCommandsForTarget`.
 *     - Installs the command manager's key mappings as a key listener so keyboard shortcuts
 *       are delivered to the command manager.
 * - Creates the top-level menu bar (`juce::MenuBarComponent`) and the debug panel
 *   (`DebugComponent`), taking ownership with `std::unique_ptr::reset` and making both
 *   visible using `addAndMakeVisible`.
 * - Sets basic component properties: requests keyboard focus, marks the component as
 *   opaque, and sets the initial window size.
 *
 * Notes:
 * - The dialog and other UI elements expect `_audioDeviceManager` and `_applicationProperties`
 *   to be valid members of this object.
 * - Ownership semantics:
 *     - `_menuBarComponent` and `_debugComponent` are managed by `std::unique_ptr`.
 *     - `_applicationProperties` retains the storage parameters and is used elsewhere to
 *       persist settings.
 */
MainComponent::MainComponent()
{
    _audioDeviceManager.reset(new juce::AudioDeviceManager());

    // Setup the application properties storage.
    juce::PropertiesFile::Options options;
    options.applicationName = "equalizer";
    options.folderName = "EvilAudio";
    options.filenameSuffix = "settings";
    options.osxLibrarySubFolder = "Application Support";
    _applicationProperties.setStorageParameters(options);

    juce::PropertiesFile* userSettings = _applicationProperties.getUserSettings();
    if (userSettings != nullptr)
    {
        //juce::xml
       juce::String deviceSettings =
            userSettings->getValue("AudioDeviceSettings");
       auto xmlState = juce::XmlDocument::parse(deviceSettings);

       // Initialize the audio device manager with the saved settings.
       // TODO: Handle the case where xmlState is nullptr or invalid.
       _audioDeviceManager->initialise(2, 2, xmlState.get(), false);

    }

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

    _audioInputDebugView.reset(new AudioInputDebugView(*_audioDeviceManager, _applicationProperties));
    addAndMakeVisible(_audioInputDebugView.get());

    //_debugComponent.reset(new DebugComponent(*_audioDeviceManager, _applicationProperties));
    //addAndMakeVisible(_debugComponent.get());

    setWantsKeyboardFocus(true);
    setOpaque(true);
    setSize(600, 440);

}

MainComponent::~MainComponent()
{
    _commandManager.setFirstCommandTarget(nullptr);

    _menuBarComponent->setModel(nullptr);
    //_mainMenuModel = nullptr;
    //_debugComponent = nullptr;
    _audioInputDebugView = nullptr;

    auto xmlState = _audioDeviceManager.get()->createStateXml();
    if (xmlState != nullptr)
    {
        juce::PropertiesFile* userSettings = _applicationProperties.getUserSettings();
        if (userSettings != nullptr)
        {
            userSettings->setValue("AudioDeviceSettings", xmlState->toString());
            userSettings->saveIfNeeded();
        }
    }
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
    //_debugComponent->setBounds(bounds);
    _audioInputDebugView->setBounds(bounds);
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
    AudioSettingsComponent* audioSettingsComponent = new AudioSettingsComponent(*_audioDeviceManager);
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
