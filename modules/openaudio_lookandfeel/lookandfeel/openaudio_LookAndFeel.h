#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class OpenAudio_LookAndFeel : public juce::LookAndFeel_V4
{
public:
    OpenAudio_LookAndFeel();
     


    void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
        float sliderPos, float minSliderPos, float maxSliderPos,
        juce::Slider::SliderStyle style, juce::Slider& slider) override;

private:

    void initialiseColours();
    //ColourScheme currentColourScheme;
   
};