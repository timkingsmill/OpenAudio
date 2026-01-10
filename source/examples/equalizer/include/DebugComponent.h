#pragma once
#include <JuceHeader.h>

class DebugComponent : public juce::Component
{
    public:
        DebugComponent(juce::AudioDeviceManager&, juce::ApplicationProperties&);
        ~DebugComponent() override;
    
        void paint(juce::Graphics& g) override
        {
        }

        void resized() override
        {
            // Handle component resizing if needed
        }

    private:
        juce::ApplicationProperties& _applicationProperties;
        juce::AudioDeviceManager& _audioDeviceManager;

        juce::TextButton _playSoundButton{ "Play Sound" };
};