#pragma once

#include <JuceHeader.h>
#include "AudioInputListener.h"
#include "LiveScrollingAudioDisplay.h"

class AudioInputDebugView : public juce::Component
{
public:
    AudioInputDebugView(juce::AudioDeviceManager&, juce::ApplicationProperties&);
    ~AudioInputDebugView() override;

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
    
    std::unique_ptr<AudioInputListener> _audioInputListener;
    std::unique_ptr<LiveScrollingAudioDisplay> _liveAudioScroller;


    juce::TextButton _startInputListenerButton{ "Start Audio Input Listener" };
    juce::TextButton _stopInputListenerButton{ "Stop Audio Input Listener" };
};