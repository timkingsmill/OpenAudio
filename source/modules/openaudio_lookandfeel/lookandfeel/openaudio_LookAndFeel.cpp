#include "openaudio_LookAndFeel.h"



OpenAudio_LookAndFeel::OpenAudio_LookAndFeel()
{

    initialiseColours();
}

void OpenAudio_LookAndFeel::drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, juce::Slider::SliderStyle style, juce::Slider& slider)
{
    juce::LookAndFeel_V4::drawLinearSlider(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
}


void OpenAudio_LookAndFeel::initialiseColours()
{
}
