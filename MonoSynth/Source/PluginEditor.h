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
class MonoSynthAudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Timer
{
public:
    MonoSynthAudioProcessorEditor (MonoSynthAudioProcessor&);
    ~MonoSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
   
private:
    // Sliders and Buttons
    juce::Slider frequencySlider; 
    juce::Slider gainSlider;
    juce::ToggleButton onOffButton;
    juce::Slider moogfrSlider;
    juce::Slider moogfrSlider2;
    juce::Slider moogResSlider;
    juce::Slider moogResSlider2;

    // Labels
    juce::Label frequencyLabel;
    juce::Label gainLabel;
    juce::Label onOffLabel;
    juce::Label moogfrLabel;
    juce::Label moogfrLabel2;
    juce::Label moogResLabel;
    juce::Label moogResLabel2;

    juce::Image backgroundImage;

    void timerCallback() final;

    void setControllerFlagsFalse();

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MonoSynthAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MonoSynthAudioProcessorEditor)
};
