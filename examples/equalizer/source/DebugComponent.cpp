#include "DebugComponent.h"


DebugComponent::DebugComponent(juce::AudioDeviceManager& adm, 
                               juce::ApplicationProperties& settings) :
    _audioDeviceManager(adm),
    _applicationProperties(settings)
{
    addAndMakeVisible(_playSoundButton);
    _playSoundButton.setBounds(10, 10, 120, 30);
    _playSoundButton.onClick = [this]() 
    {
        juce::AudioSourcePlayer audioSourcePlayer;
        juce::ToneGeneratorAudioSource toneSource;
        toneSource.setFrequency(440.0); // A4
        toneSource.setAmplitude(1.0f);  // Max volume. I don't know the range??
        audioSourcePlayer.setSource(&toneSource);

        _audioDeviceManager.addAudioCallback(&audioSourcePlayer);
        juce::Thread::sleep(2000); // Play sound for 500ms
        _audioDeviceManager.removeAudioCallback(&audioSourcePlayer);

        audioSourcePlayer.setSource(nullptr);
    };
}

DebugComponent::~DebugComponent()
{
}