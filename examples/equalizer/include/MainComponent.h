#pragma once

// CMake builds don't use an AppConfig.h, so it's safe to include juce module headers
// directly. If you need to remain compatible with Projucer-generated builds, and
// have called `juce_generate_juce_header(<thisTarget>)` in your CMakeLists.txt,
// you could `#include <JuceHeader.h>` here instead, to make all your module headers visible.
#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent final : public juce::Component,
                            public juce::ChangeListener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    //==============================================================================
private:
    void logMessage(const juce::String& m)
    {
        diagnosticsBox.moveCaretToEnd();
        diagnosticsBox.insertTextAtCaret(m + juce::newLine);
    }

    void dumpDeviceInfo()
    {
        logMessage("--------------------------------------");
        logMessage("Current audio device type: " + (audioDeviceManager.getCurrentDeviceTypeObject() != nullptr
            ? audioDeviceManager.getCurrentDeviceTypeObject()->getTypeName()
            : "<none>"));

        if (juce::AudioIODevice* device = audioDeviceManager.getCurrentAudioDevice())
        {
            logMessage("Current audio device: " + device->getName().quoted());
            logMessage("Sample rate: " + juce::String(device->getCurrentSampleRate()) + " Hz");
            logMessage("Block size: " + juce::String(device->getCurrentBufferSizeSamples()) + " samples");
            logMessage("Output Latency: " + juce::String(device->getOutputLatencyInSamples()) + " samples");
            logMessage("Input Latency: " + juce::String(device->getInputLatencyInSamples()) + " samples");
            logMessage("Bit depth: " + juce::String(device->getCurrentBitDepth()));
            logMessage("Input channel names: " + device->getInputChannelNames().joinIntoString(", "));
            //logMessage("Active input channels: " + getListOfActiveBits(device->getActiveInputChannels()));
            logMessage("Output channel names: " + device->getOutputChannelNames().joinIntoString(", "));
            //logMessage("Active output channels: " + getListOfActiveBits(device->getActiveOutputChannels()));
        }
        else
        {
            logMessage("No audio device open");
        }
    }

    // Inherited via ChangeListener
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
    void lookAndFeelChanged() override;

private:
    //==============================================================================
    // Your private member variables go here...
    juce::AudioDeviceManager audioDeviceManager;
    std::unique_ptr<juce::AudioDeviceSelectorComponent> audioSetupComp;
    juce::TextEditor diagnosticsBox;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
