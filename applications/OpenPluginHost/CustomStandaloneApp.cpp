#include "CustomStandaloneApp.h"

CustomStandaloneApp::CustomStandaloneApp()
{
    juce::PropertiesFile::Options options;

    options.applicationName = _appName;
    options.filenameSuffix = ".settings";
    options.osxLibrarySubFolder = "Application Support";
    #if JUCE_LINUX || JUCE_BSD
        options.folderName = "~/.config";
    #else
        options.folderName = "";
    #endif
    _appProperties.setStorageParameters(options);
}

juce::StandaloneFilterWindow* CustomStandaloneApp::createWindow()
{
    #ifdef JucePlugin_PreferredChannelConfigurations
        StandalonePluginHolder::PluginInOuts channels[] = { JucePlugin_PreferredChannelConfigurations };
    #endif
    
    return new juce::StandaloneFilterWindow(
            getApplicationName(),
            juce::LookAndFeel::getDefaultLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId),
            _appProperties.getUserSettings(),
            false, {}, nullptr
            #ifdef JucePlugin_PreferredChannelConfigurations
                , juce::Array<StandalonePluginHolder::PluginInOuts>(channels, juce::numElementsInArray(channels))
            #else
                , {}
            #endif
            #if JUCE_DONT_AUTO_OPEN_MIDI_DEVICES_ON_MOBILE
                , false
            #endif
        );
}

void CustomStandaloneApp::initialise(const juce::String& commandLine)
{
    _mainWindow.reset(createWindow());
    #if JUCE_STANDALONE_FILTER_WINDOW_USE_KIOSK_MODE
        juce::Desktop::getInstance().setKioskModeComponent(_mainWindow.get(), false);
    #endif
    _mainWindow->setVisible(true);
}

void CustomStandaloneApp::systemRequestedQuit()
{
    if (_mainWindow != nullptr) {
        _mainWindow->pluginHolder->savePluginState();
    }

    if (juce::ModalComponentManager::getInstance()->cancelAllModalComponents())
    {
        juce::Timer::callAfterDelay(100, []()
            {
                if (auto app = JUCEApplicationBase::getInstance())
                    app->systemRequestedQuit();
            });
    }
    else
    {
        quit();
    }
}
