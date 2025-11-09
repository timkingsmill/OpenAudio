#pragma once

#include "EqualizerProcessor.h"
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_opengl/juce_opengl.h>



class EqualizerEditor : public juce::AudioProcessorEditor
    //,
      //                  public juce::ChangeListener,
        //                public juce::Timer
{

public:
    EqualizerEditor(EqualizerProcessor& processor);
    ~EqualizerEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    // ---------------------------------------------------------------------------------

    class BandEditor : public juce::Component//,
                       //public juce::Button::Listener
    {
    public:
        BandEditor(size_t i, EqualizerProcessor& processor);

        void resized() override;

    private:
        EqualizerProcessor& _processor;
        juce::GroupComponent _frame;
    };

    // ----------------------------------------------------------------------------

private:
    #ifdef JUCE_OPENGL
        //juce::OpenGLContext _openGLContext;
    #endif

    EqualizerProcessor& _processor;

    juce::OwnedArray<BandEditor>  _bandEditors;
    juce::GroupComponent _frame;


};