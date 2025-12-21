#pragma once

#include <JuceHeader.h>
#include "ParametricEqualiserProcessor.h"

class ParametricEqualiserEditor : 
    public juce::AudioProcessorEditor,
    public juce::ChangeListener,
    public juce::Timer
{
public:
    ParametricEqualiserEditor(ParametricEqualiserProcessor& audioProcessor);
    ~ParametricEqualiserEditor() override;

    void paint(juce::Graphics& g) override;
    void resized() override;
    void changeListenerCallback(juce::ChangeBroadcaster* sender) override;
    void timerCallback() override;
    void updateFrequencyResponses(); 
    
    void mouseDown(const juce::MouseEvent& e) override;
    void mouseMove(const juce::MouseEvent& e) override;
    void mouseDrag(const juce::MouseEvent& e) override;
    void mouseDoubleClick(const juce::MouseEvent& e) override;
private:
    static float getPositionForFrequency(float freq);
    static float getFrequencyForPosition(float pos);
    static float getPositionForGain(float gain, float top, float bottom);
    static float getGainForPosition(float pos, float top, float bottom);

    class BandEditor : public juce::Component,
                       public juce::Button::Listener
    {
    public:
        BandEditor(size_t index, ParametricEqualiserProcessor& audioProcessor);
        void resized() override;
        void updateControls(ParametricEqualiserProcessor::FilterType type);
        void updateSoloState(bool isSolo);
        void setFrequency(float frequency);
        void setGain(float gain);
        void setType(int type);
        void buttonClicked(juce::Button* b) override;

        juce::Path frequencyResponse;

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BandEditor)

        ParametricEqualiserProcessor& _audioProcessor;
        size_t _index;

        juce::GroupComponent _frame;
        juce::ComboBox _filterTypeComboBox;

        juce::Slider _frequencySlider { 
            juce::Slider::RotaryHorizontalVerticalDrag, 
            juce::Slider::TextBoxBelow 
        };
        juce::Slider _quality { 
            juce::Slider::RotaryHorizontalVerticalDrag, 
            juce::Slider::TextBoxBelow 
        };
        juce::Slider _gain { 
            juce::Slider::RotaryHorizontalVerticalDrag, 
            juce::Slider::TextBoxBelow 
        };
        juce::TextButton _solo { 
            TRANS("S") 
        };
        juce::TextButton _activate {
            TRANS("A") 
        };
        juce::OwnedArray<juce::AudioProcessorValueTreeState::ComboBoxAttachment> _boxAttachments;
        juce::OwnedArray<juce::AudioProcessorValueTreeState::SliderAttachment> _attachments;
        juce::OwnedArray<juce::AudioProcessorValueTreeState::ButtonAttachment> _buttonAttachments;
    };

private:
    ParametricEqualiserProcessor& _audioProcessor;
    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ParametricEqualiserEditor)

    juce::OwnedArray<BandEditor> _bandEditors;
    int _draggingBand = -1;
    bool _draggingGain = false;

    juce::GroupComponent _outputFrame;
    juce::Slider _outputGain { 
        juce::Slider::RotaryHorizontalVerticalDrag, 
        juce::Slider::TextBoxBelow 
    };

    juce::Rectangle<int> _plotFrame;
    juce::Rectangle<int> _brandingFrame;
    juce::OwnedArray<juce::AudioProcessorValueTreeState::SliderAttachment> _attachments;
    juce::SharedResourcePointer<juce::TooltipWindow> _tooltipWindow;

    juce::Path _frequencyResponsePath;
    juce::Path _analyserPath;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ParametricEqualiserEditor)

};