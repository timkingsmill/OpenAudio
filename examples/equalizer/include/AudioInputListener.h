#pragma once

#include <JuceHeader.h>

class AudioInputListener final : public juce::AudioIODeviceCallback
{ 
public:
    AudioInputListener();
    ~AudioInputListener() override;

    void start(const juce::File& file);
    void stop();

private:
    void audioDeviceIOCallbackWithContext(const float* const* inputChannelData,
        int numInputChannels,
        float* const* outputChannelData,
        int numOutputChannels,
        int numSamples,
        const juce::AudioIODeviceCallbackContext& context) override;
    
    void audioDeviceAboutToStart(juce::AudioIODevice* device) override;
    void audioDeviceStopped() override;

private:
    // Create the thread that will write our audio data to a stream.
    juce::TimeSliceThread _backgroundThread{ "Audio Listener Thread" };
    std::unique_ptr<juce::AudioFormatWriter::ThreadedWriter> threadedWriter; // the FIFO used to buffer the incoming data

};