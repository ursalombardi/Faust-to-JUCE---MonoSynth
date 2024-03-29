/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/MyLookAndFeel.h"
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
    void connectAttachment(std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment, juce::AudioProcessorValueTreeState& apvts,
        juce::String paramID, juce::Slider& slider);
   
private:
    ReverbComponent reverbComponent;
    MoogFilterComponent moogFilterComponent;

    // Sliders and Buttons
    juce::Slider frequencySlider; 
    juce::Slider gainSlider;
    juce::ToggleButton onOffButton;
    juce::TextButton knobRandomizer;

    // Sliders
    juce::Slider attackSlider;
    juce::Slider releaseSlider;
    juce::Slider tremSlider;

    // Labels
    juce::Label attackLabel;
    juce::Label releaseLabel;
    juce::Label tremLabel;

    // Images
    juce::Image backgroundImage;
    juce::Image constructionImage;

    void timerCallback() final;
    void setControllerFlagsFalse();

    ReverbLookAndFeel reverbLookAndFeel;

    // APVTS Attachment
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    // Moog Filters
    std::unique_ptr<Attachment> frMainAttachment;
    std::unique_ptr<Attachment> resMainAttachment;
    std::unique_ptr<Attachment> indexSquareAttachment;
    std::unique_ptr<Attachment> indexSawAttachment;
    std::unique_ptr<Attachment> indexPulseAttachment;
    std::unique_ptr<Attachment> frSquareAttachment;
    std::unique_ptr<Attachment> frSawAttachment;
    std::unique_ptr<Attachment> frPulseAttachment;
    std::unique_ptr<Attachment> resSquareAttachment;
    std::unique_ptr<Attachment> resSawAttachment;
    std::unique_ptr<Attachment> resPulseAttachment;
    // Reverb 
    // AR
    std::unique_ptr<Attachment> attackAttachment;
    std::unique_ptr<Attachment> releaseAttachment;
    // Other
    std::unique_ptr<Attachment> tremeloAttachment;


    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MonoSynthAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MonoSynthAudioProcessorEditor)
};
