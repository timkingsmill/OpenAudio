#include "DebugComponent.h"


DebugComponent::DebugComponent(juce::AudioDeviceManager& adm, 
                               juce::ApplicationProperties& settings) :
    _audiodeviceManager(adm),
    _applicationProperties(settings)
{
    juce::PropertiesFile::Options options;
    options.applicationName = "CapabilityInquiryDemo";
    options.filenameSuffix = "settings";
    options.osxLibrarySubFolder = "Application Support";
    _applicationProperties.setStorageParameters(options);

    addAndMakeVisible(_playSoundButton);
    _playSoundButton.setBounds(10, 10, 120, 30);
    _playSoundButton.onClick = [this]() 
    {
        juce::AudioSourcePlayer audioSourcePlayer;
        juce::ToneGeneratorAudioSource toneSource;
        toneSource.setFrequency(440.0); // A4
        toneSource.setAmplitude(1.0f);  // Max volume. I don't know the range??
        audioSourcePlayer.setSource(&toneSource);

        _audiodeviceManager.addAudioCallback(&audioSourcePlayer);
        juce::Thread::sleep(2000); // Play sound for 500ms
        _audiodeviceManager.removeAudioCallback(&audioSourcePlayer);

        audioSourcePlayer.setSource(nullptr);
    };
}

DebugComponent::~DebugComponent()
{
    auto xmlState = _audiodeviceManager.createStateXml();
    if (xmlState != nullptr)
    {
        juce::PropertiesFile* userSettings = _applicationProperties.getUserSettings();
        if (userSettings != nullptr)
        {
            userSettings->setValue("audioDeviceState", xmlState->toString());
            userSettings->saveIfNeeded();
        }
    }
}