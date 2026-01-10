#include "AudioInputDebugView.h"

AudioInputDebugView::AudioInputDebugView(
    juce::AudioDeviceManager& adm,
    juce::ApplicationProperties& settings) :
    _audioDeviceManager(adm),
    _applicationProperties(settings)
{
    _audioInputListener = std::make_unique<AudioInputListener>();

    _liveAudioScroller = std::make_unique<LiveScrollingAudioDisplay>();;
    addAndMakeVisible(_liveAudioScroller.get());
    _liveAudioScroller->setBounds(200, 10, 400, 300);

    addAndMakeVisible(_startInputListenerButton);
    _startInputListenerButton.setBounds(10, 10, 180, 24);
    _startInputListenerButton.onClick = [this]()
        {
            _audioDeviceManager.addAudioCallback(_liveAudioScroller.get());
            _audioDeviceManager.addAudioCallback(_audioInputListener.get());


            _audioInputListener->start(juce::File());
        };


    addAndMakeVisible(_stopInputListenerButton);
    _stopInputListenerButton.setBounds(10, 50, 180, 24);
    _stopInputListenerButton.onClick = [this]()
        {
            _audioInputListener->stop();


            _audioDeviceManager.removeAudioCallback(_audioInputListener.get());
            _audioDeviceManager.removeAudioCallback(_liveAudioScroller.get());
        };
}

AudioInputDebugView::~AudioInputDebugView()
{
    _audioDeviceManager.removeAudioCallback(_audioInputListener.get());
    _audioDeviceManager.removeAudioCallback(_liveAudioScroller.get());

}