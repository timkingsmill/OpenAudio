#include "AudioSettingsComponent.h"

//==============================================================================
AudioSettingsComponent::AudioSettingsComponent(juce::AudioDeviceManager& audioDeviceManager) :
    _audioDeviceManager{ audioDeviceManager }
{
    setOpaque(true);

    audioSetupComp.reset(new juce::AudioDeviceSelectorComponent(_audioDeviceManager,
        1, 256, 1, 256, 
        false, //true, // Disable MIDI input options
        false, //true, // Disable MIDI output selector
        true, false));

    addAndMakeVisible(audioSetupComp.get());

    // Setup diagnostics text box
    addAndMakeVisible(diagnosticsBox);
    diagnosticsBox.setMultiLine(true);
    diagnosticsBox.setReturnKeyStartsNewLine(true);
    diagnosticsBox.setReadOnly(true);
    diagnosticsBox.setScrollbarsShown(true);
    diagnosticsBox.setCaretVisible(false);
    diagnosticsBox.setPopupMenuEnabled(true);

    _audioDeviceManager.addChangeListener(this);

    logMessage("Audio device diagnostics:\n");

    setSize(600, 440);
}

AudioSettingsComponent::~AudioSettingsComponent()
{
    _audioDeviceManager.removeChangeListener(this);
}

//==============================================================================
void AudioSettingsComponent::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill 
    // the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void AudioSettingsComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

    auto r = getLocalBounds().reduced(4);
    audioSetupComp->setBounds(r.removeFromTop(proportionOfHeight(0.65f)));
    diagnosticsBox.setBounds(r);
}

// --------------------------------------------------------------------------

void AudioSettingsComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    dumpDeviceInfo();
}

void AudioSettingsComponent::lookAndFeelChanged()
{
    diagnosticsBox.applyFontToAllText(diagnosticsBox.getFont());
}
