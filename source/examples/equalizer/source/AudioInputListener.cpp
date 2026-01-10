#include "AudioInputListener.h"

AudioInputListener::AudioInputListener()
{
    _backgroundThread.startThread();

}

AudioInputListener::~AudioInputListener()
{
    stop();
}

void AudioInputListener::audioDeviceIOCallbackWithContext(const float* const* inputChannelData, int numInputChannels, float* const* outputChannelData, int numOutputChannels, int numSamples, const juce::AudioIODeviceCallbackContext& context)
{
    // Process incoming audio data from inputChannelData
    // For example, you could copy input to output or perform analysis
    // Clear the output buffers to avoid unwanted noise
    for (int i = 0; i < numOutputChannels; ++i)
    {
        if (outputChannelData[i] != nullptr)
            juce::FloatVectorOperations::clear(outputChannelData[i], numSamples);
    }
}

void AudioInputListener::audioDeviceAboutToStart(juce::AudioIODevice* device)
{
    // Prepare for audio processing, e.g., allocate buffers
}

void AudioInputListener::audioDeviceStopped()
{
    // Clean up resources when the audio device stops
}

void AudioInputListener::start(const juce::File& file)
{
    // Implement recording logic here, e.g., open file for writing audio data}
    stop();
}

void AudioInputListener::stop()
{

}

