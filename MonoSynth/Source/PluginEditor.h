/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MonoSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    MonoSynthAudioProcessorEditor (MonoSynthAudioProcessor&);
    ~MonoSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
   
private:

    juce::Slider frequencySlider; 
    juce::Slider gainSlider;
    juce::Slider cutoffSlider;
    juce::ToggleButton onOffButton;
    juce::MouseListener* mouse;

    juce::Label frequencyLabel;
    juce::Label gainLabel;
    juce::Label cutoffLabel;
    juce::Label onOffLabel;


    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MonoSynthAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MonoSynthAudioProcessorEditor)
};
