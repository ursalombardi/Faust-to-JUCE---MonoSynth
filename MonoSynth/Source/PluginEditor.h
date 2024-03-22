/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MyLookAndFeel.h"
#include "UI/MoogFilterComponent.h"
#include "UI/ReverbComponent.h"


//==============================================================================
/**
*/
class MonoSynthAudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Timer
{
public:
    MonoSynthAudioProcessorEditor (MonoSynthAudioProcessor&);
    ~MonoSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void reverbValueChange();
    void moogFilterValueChange();
   
private:
    ReverbComponent reverbComponent;
    MoogFilterComponent moogFilterComponent;

    // Sliders and Buttons
    juce::Slider frequencySlider; 
    juce::Slider gainSlider;
    juce::ToggleButton onOffButton;
    juce::TextButton knobRandomizer;

    juce::Slider attackSlider;
    juce::Slider releaseSlider;
    juce::Slider tremSlider;

    // Images
    juce::Image backgroundImage;

    void timerCallback() final;

    void setControllerFlagsFalse();

    ReverbLookAndFeel reverbLookAndFeel;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MonoSynthAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MonoSynthAudioProcessorEditor)
};
