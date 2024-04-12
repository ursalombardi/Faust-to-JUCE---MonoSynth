/*
  ==============================================================================

    MoogFilterComponent.h
    Created: 15 Mar 2024 3:25:46pm
    Author:  Matthew

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MyLookAndFeel.h"

//==============================================================================
/*
*/
class MoogFilterComponent  : public juce::Component
{
public:
    MoogFilterComponent()
    {
        createKnob(frMainSlider, 200, 200, 4000, 0.01);
        createKnob(resMainSlider, 0.70, 0, 1.00, 0.01);
        createKnob(indexSquareSlider, 0.65, 0.0, 1.0, 0.01);
        createKnob(indexSawSlider, 0.95, 0.0, 1.0, 0.01);
        createKnob(indexPulseSlider, 0.2, 0.0, 1.0, 0.01);
        createKnob(frSquareSlider, 2000, 200, 4000, 0.01);
        createKnob(frSawSlider, 2000, 200, 4000, 0.01);
        createKnob(frPulseSlider, 2000, 200, 4000, 0.01);
        createKnob(resSquareSlider, 0.05, 0, 1, 0.01);
        createKnob(resSawSlider, 0.05, 0, 1, 0.01);
        createKnob(resPulseSlider, 0.05, 0, 1, 0.01);
    }


    ~MoogFilterComponent() override
    {
        frMainSlider.setLookAndFeel(nullptr);
        resMainSlider.setLookAndFeel(nullptr);
        indexSquareSlider.setLookAndFeel(nullptr);
        indexSawSlider.setLookAndFeel(nullptr);
        indexPulseSlider.setLookAndFeel(nullptr);
        frSquareSlider.setLookAndFeel(nullptr);
        frSawSlider.setLookAndFeel(nullptr);
        frPulseSlider.setLookAndFeel(nullptr);
        resSquareSlider.setLookAndFeel(nullptr);
        resSawSlider.setLookAndFeel(nullptr);
        resPulseSlider.setLookAndFeel(nullptr);
    }

    void paint (juce::Graphics& g) override
    {
        g.setColour (juce::Colours::grey);
        //g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    }

    void resized() override
    {
        frMainSlider.setBounds(97 - 125/2, 1, 125, 125);
        resMainSlider.setBounds(150 + 10, 76, 55, 55);

        float smallKnobSize = 45;
        float leftOffSet = 25;

        indexSquareSlider.setBounds(leftOffSet+10, 200, smallKnobSize+10, smallKnobSize+10);
        frSquareSlider.setBounds(leftOffSet+5+10, 275, smallKnobSize, smallKnobSize);
        resSquareSlider.setBounds(leftOffSet+10+10, 340, smallKnobSize - 10, smallKnobSize - 10);

        indexSawSlider.setBounds(leftOffSet + 90, 200, smallKnobSize+10, smallKnobSize + 10);
        frSawSlider.setBounds(leftOffSet + 95 , 275, smallKnobSize, smallKnobSize);
        resSawSlider.setBounds(leftOffSet + 100, 340, smallKnobSize - 10, smallKnobSize - 10);

        indexPulseSlider.setBounds(leftOffSet + 180 -10, 200, smallKnobSize + 10, smallKnobSize + 10);
        frPulseSlider.setBounds(leftOffSet + 185 - 10, 275, smallKnobSize, smallKnobSize);
        resPulseSlider.setBounds(leftOffSet + 190 - 10, 340, smallKnobSize - 10, smallKnobSize-10);

    }

    void createKnob(juce::Slider& slider, double initialValue, double minRange, double maxRange, double increment)
    {
        addAndMakeVisible(slider);
        slider.setLookAndFeel(&moogFilterLookAndFeel);
        slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        slider.setRange(minRange, maxRange, increment);
        slider.setValue(initialValue);
        slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    }

    void createKnob2(juce::Slider& slider, double initialValue, double minRange, double maxRange, double increment,
        juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attach)
    {
        addAndMakeVisible(slider);
        slider.setLookAndFeel(&moogFilterLookAndFeel);
        slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        slider.setRange(minRange, maxRange, increment);
        slider.setValue(initialValue);
        slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
        attach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);
    }

    juce::Slider frMainSlider;
    juce::Slider resMainSlider;

    juce::Slider indexSquareSlider;
    juce::Slider indexSawSlider;
    juce::Slider indexPulseSlider;
    
    juce::Slider frSquareSlider;
    juce::Slider frSawSlider;
    juce::Slider frPulseSlider;

    juce::Slider resSquareSlider;
    juce::Slider resSawSlider;
    juce::Slider resPulseSlider;

private:
    MoogFilterLookAndFeel moogFilterLookAndFeel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MoogFilterComponent)
};
