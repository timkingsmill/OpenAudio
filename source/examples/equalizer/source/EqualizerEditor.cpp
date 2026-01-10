#include "EqualizerEditor.h"

EqualizerEditor::EqualizerEditor(EqualizerProcessor& processor)
    :   juce::AudioProcessorEditor(processor),
        _processor(processor)
{
    // Create edtor controls for each equalizer band
    for (size_t i = 0; i < 5; ++i)
    {
        auto* bandEditor = _bandEditors.add(new BandEditor(i, _processor));
        addAndMakeVisible(bandEditor);
    }

    // Create the output level controls.
    _outputControlFrame.setText(TRANS("Output"));
    _outputControlFrame.setTextLabelPosition(juce::Justification::centred);

    
    addAndMakeVisible(_outputControlFrame);


    // Initialize the size of the equalizer editor.
    auto size = getLocalBounds();
    setResizable(true, true);
    setSize(size.getHeight(), size.getWidth());
    setResizeLimits(800, 450, 2990, 1800);

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

    graphics.drawRoundedRectangle(_plotFrame.toFloat(), 5, 2);
}

void EqualizerEditor::resized()
{ 
    _plotFrame = getLocalBounds().reduced(3, 3);

    // Resize the band editor controls.
    auto bandSpace = _plotFrame.removeFromBottom(getHeight() / 2);
    auto bandEditorWidth = juce::roundToInt(bandSpace.getWidth()) / (_bandEditors.size() + 1);
    for (auto* bandEditor : _bandEditors)
    {
        bandEditor->setBounds(bandSpace.removeFromLeft(bandEditorWidth));
    }
    
    // Resize the output level control frame.
    _outputControlFrame.setBounds(bandSpace.removeFromTop(bandSpace.getHeight() / 2));
}

// ------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------

EqualizerEditor::BandEditor::BandEditor(size_t index, EqualizerProcessor& processor)
    :   _processor(processor),
        _index(index)
{
    _frame.setText("A Band");
    _frame.setTextLabelPosition(juce::Justification::centred);
    //_frame.setColour(juce::GroupComponent::textColourId, processor.getBandColour(index));
    //_frame.setColour(juce::GroupComponent::outlineColourId, processor.getBandColour(index));
    _frame.setColour(juce::GroupComponent::textColourId, juce::Colours::red);
    _frame.setColour(juce::GroupComponent::outlineColourId, juce::Colours::green);
    addAndMakeVisible(_frame);

    addAndMakeVisible(_filterType);

    addAndMakeVisible(_frequency);
}

// ------------------------------------------------------------------------------------

void EqualizerEditor::BandEditor::resized()
{
    auto bounds = getLocalBounds();
    _frame.setBounds(bounds);

    bounds.reduce(10, 20);
    _filterType.setBounds(bounds.removeFromTop(20));

    auto freqBounds = bounds.removeFromBottom(bounds.getHeight() * 2 / 3);
    _frequency.setBounds(freqBounds.withTop(freqBounds.getY() + 10));

}

// ------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------


