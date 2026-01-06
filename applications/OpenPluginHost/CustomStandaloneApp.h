#pragma once

#include <JuceHeader.h>
#include "CustomStandaloneFilterWindow.h"

class CustomStandaloneApp : public juce::JUCEApplication
{
public:
    CustomStandaloneApp();

    void initialise(const juce::String& commandLine) override;
    
    void shutdown() override {
        _mainWindow = nullptr;
        _appProperties.saveIfNeeded();
    };

    void systemRequestedQuit() override;
    void anotherInstanceStarted(const juce::String& commandLine) override {};

    const juce::String getApplicationName() override {
        return ProjectInfo::projectName;
    };

    const juce::String getApplicationVersion() override {
        return ProjectInfo::versionString;  
    };
    
    bool moreThanOneInstanceAllowed() override {
        return true;
    };
    
protected:
    virtual juce::StandaloneFilterWindow* createWindow();

    juce::ApplicationProperties _appProperties;
    std::unique_ptr<juce::StandaloneFilterWindow> _mainWindow;

private:
    const juce::String _appName { ProjectInfo::projectName };
};