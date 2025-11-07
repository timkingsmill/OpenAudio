#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setOpaque(true);

    audioSetupComp.reset(new juce::AudioDeviceSelectorComponent(audioDeviceManager,
        0, 256, 0, 256, true, true, true, false));
    addAndMakeVisible(audioSetupComp.get());

    addAndMakeVisible(diagnosticsBox);
    diagnosticsBox.setMultiLine(true);
    diagnosticsBox.setReturnKeyStartsNewLine(true);
    diagnosticsBox.setReadOnly(true);
    diagnosticsBox.setScrollbarsShown(true);
    diagnosticsBox.setCaretVisible(false);
    diagnosticsBox.setPopupMenuEnabled(true);

    audioDeviceManager.addChangeListener(this);

    logMessage("Audio device diagnostics:\n");

    setSize(600, 440);
}

MainComponent::~MainComponent()
{
    audioDeviceManager.removeChangeListener(this);
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

    auto r = getLocalBounds().reduced(4);
    audioSetupComp->setBounds(r.removeFromTop(proportionOfHeight(0.65f)));
    diagnosticsBox.setBounds(r);
}

// --------------------------------------------------------------------------

void MainComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    dumpDeviceInfo();
}

void MainComponent::lookAndFeelChanged()
{
    diagnosticsBox.applyFontToAllText(diagnosticsBox.getFont());
}
