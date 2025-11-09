#include "EqualizerEditor.h"

EqualizerEditor::EqualizerEditor(EqualizerProcessor& processor)
    :   juce::AudioProcessorEditor(processor),
        _processor(processor)
{
    setSize(600, 400);

    for (size_t i = 0; i < 5; ++i)
    {
        auto* bandEditor = _bandEditors.add(new BandEditor(i, _processor));
        addAndMakeVisible(bandEditor);
    }

    _frame.setText(TRANS("Output"));
    addAndMakeVisible(_frame);

}

EqualizerEditor::~EqualizerEditor()
{
}

// ------------------------------------------------------------------------------------
void EqualizerEditor::paint(juce::Graphics& graphics) 
{ 
    const auto inputColour = juce::Colours::greenyellow;
    const auto outputColour = juce::Colours::indianred;

    juce::Graphics::ScopedSaveState state(graphics);

    graphics.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void EqualizerEditor::resized()
{ 
    auto plotFrame = getLocalBounds().reduced(3, 3);

    _frame.setBounds(plotFrame);
}

// ------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------

EqualizerEditor::BandEditor::BandEditor(size_t i, EqualizerProcessor& processor)
    :   _processor(processor)
{
    _frame.setText("Hello From a Band Editor");

    addAndMakeVisible(_frame);
}

// ------------------------------------------------------------------------------------

void EqualizerEditor::BandEditor::resized()
{
    auto bounds = getLocalBounds();
    _frame.setBounds(bounds);
}

// ------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------


