/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <iostream>

//==============================================================================
MonoSynthAudioProcessorEditor::MonoSynthAudioProcessorEditor(MonoSynthAudioProcessor& p)
    : AudioProcessorEditor(&p), 
    audioProcessor(p),
    presetComponent(p.getPresetManager())
{
    setSize(800, 500);
    startTimer(100);

    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    constructionImage = juce::ImageCache::getFromMemory(BinaryData::construction_png, BinaryData::construction_pngSize);

    // Moog Filter Component
    addAndMakeVisible(moogFilterComponent);
    moogFilterValueChange();
    connectAttachment(frMainAttachment, audioProcessor.apvts, "FRMAIN", moogFilterComponent.frMainSlider);
    connectAttachment(resMainAttachment, audioProcessor.apvts, "RESMAIN", moogFilterComponent.resMainSlider);
    connectAttachment(indexSquareAttachment, audioProcessor.apvts, "INDEXSQUARE", moogFilterComponent.indexSquareSlider);
    connectAttachment(indexSawAttachment, audioProcessor.apvts, "INDEXSAW", moogFilterComponent.indexSawSlider);
    connectAttachment(indexPulseAttachment, audioProcessor.apvts, "INDEXPULSE", moogFilterComponent.indexPulseSlider);
    connectAttachment(frSquareAttachment, audioProcessor.apvts, "FREQSQUARE", moogFilterComponent.frSquareSlider);
    connectAttachment(frSawAttachment, audioProcessor.apvts, "FREQSAW", moogFilterComponent.frSawSlider);
    connectAttachment(frPulseAttachment, audioProcessor.apvts, "FREQPULSE", moogFilterComponent.frPulseSlider);
    connectAttachment(resSquareAttachment, audioProcessor.apvts, "RESSQUARE", moogFilterComponent.resSquareSlider);
    connectAttachment(resSawAttachment, audioProcessor.apvts, "RESSAW", moogFilterComponent.resSawSlider);
    connectAttachment(resPulseAttachment, audioProcessor.apvts, "RESPULSE", moogFilterComponent.resPulseSlider);

    // Reverb Component
    addAndMakeVisible(reverbComponent);
    reverbValueChange();
    connectAttachment(dtAttachment, audioProcessor.apvts, "DT", reverbComponent.dtSlider);
    connectAttachment(sizeAttachment, audioProcessor.apvts, "SIZE", reverbComponent.sizeSlider);
    connectAttachment(earlyDiffAttachment, audioProcessor.apvts, "EARLYDIFF", reverbComponent.earlyDiffSlider);
    connectAttachment(feedbackAttachment, audioProcessor.apvts, "FEEDBACK", reverbComponent.feedbackSlider);
    connectAttachment(modDepthAttachment, audioProcessor.apvts, "MODDEPTH", reverbComponent.modDepthSlider);
    connectAttachment(modFreqAttachment, audioProcessor.apvts, "MODFREQ", reverbComponent.modFreqSlider);
    connectAttachment(dryWetMixAttachment, audioProcessor.apvts, "DRYWETMIX", reverbComponent.dryWetMixSlider);

    // AR Sliders
    addAndMakeVisible(attackSlider);
    attackSlider.setRange(0.01, 7.0);
    attackSlider.setValue(0.01);
    attackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    attackSlider.setColour(juce::Slider::trackColourId,juce::Colours::indianred);
    attackSlider.setNumDecimalPlacesToDisplay(2);
    attackSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 20, 20);
    attackSlider.onValueChange = [this] {
        audioProcessor.setAttack(attackSlider.getValue());
        };
    addAndMakeVisible(attackLabel);
    attackLabel.setText("Attack", juce::NotificationType::dontSendNotification);
    attackLabel.setJustificationType(juce::Justification::centredLeft);
    connectAttachment(attackAttachment, audioProcessor.apvts, "ATTACK", attackSlider);

    addAndMakeVisible(releaseSlider);
    releaseSlider.setRange(0.01, 5.0);
    releaseSlider.setValue(0.01);
    releaseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    releaseSlider.setColour(juce::Slider::trackColourId, juce::Colours::darkslateblue);
    releaseSlider.setNumDecimalPlacesToDisplay(2);
    releaseSlider.onValueChange = [this] {
        audioProcessor.setRelease(releaseSlider.getValue());
        };
    addAndMakeVisible(releaseLabel);
    releaseLabel.setText("Release", juce::NotificationType::dontSendNotification);
    releaseLabel.setJustificationType(juce::Justification::centredLeft);
    connectAttachment(releaseAttachment, audioProcessor.apvts, "RELEASE", releaseSlider);

    // Tremelo Slider
    addAndMakeVisible(tremSlider);
    tremSlider.setRange(0.0, 6.0);
    tremSlider.setValue(0.0);
    tremSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    tremSlider.setColour(juce::Slider::trackColourId, juce::Colours::darkgreen);
    tremSlider.setNumDecimalPlacesToDisplay(2);
    tremSlider.onValueChange = [this] {
        audioProcessor.setTremeloRate(tremSlider.getValue());
        if (tremSlider.getValue() > 0.0)
            audioProcessor.setTremeloGate(true);
        else
            audioProcessor.setTremeloGate(false);
        };   
    addAndMakeVisible(tremLabel);
    tremLabel.setText("Trem", juce::NotificationType::dontSendNotification);
    tremLabel.setJustificationType(juce::Justification::centredTop);
    connectAttachment(tremeloAttachment, audioProcessor.apvts, "TREMELO", tremSlider);

    // Preset 
    addAndMakeVisible(presetComponent);
}

MonoSynthAudioProcessorEditor::~MonoSynthAudioProcessorEditor()
{
    knobRandomizer.setLookAndFeel(nullptr);
}

//==============================================================================
void MonoSynthAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.drawImageAt(backgroundImage, 0, 0);
    //g.drawImageAt(constructionImage, 800 - 126, 500 -149);
}

void MonoSynthAudioProcessorEditor::resized()
{
    int leftOffset = 20; 
    int topOffset = 45;
    int mainControlSize = 100;

    moogFilterComponent.setBounds(0, 100, 300, 400);
    reverbComponent.setBounds(300, 45-40, 500, 350);
    presetComponent.setBounds(652, 339, 133, 154);
    
    attackSlider.setBounds(310, 360, 200, 30);
    attackLabel.setBounds(attackSlider.getX(), attackSlider.getY() + attackSlider.getHeight(), 200, 20);
    
    releaseSlider.setBounds(310, 420, 200, 30);
    releaseLabel.setBounds(releaseSlider.getX(), releaseSlider.getY() + releaseSlider.getHeight(), 200, 20);
    
    tremSlider.setBounds(560, 360, 60, 90);
    tremLabel.setBounds(tremSlider.getX(), tremSlider.getY() + tremSlider.getHeight(), 60, 20);
}

void MonoSynthAudioProcessorEditor::timerCallback()
{
}


void MonoSynthAudioProcessorEditor::setControllerFlagsFalse()
{
}

void MonoSynthAudioProcessorEditor::moogFilterValueChange()
{
    moogFilterComponent.frMainSlider.onValueChange = [this] {
        audioProcessor.setMainfr(moogFilterComponent.frMainSlider.getValue());
        };

    moogFilterComponent.resMainSlider.onValueChange = [this] {
        audioProcessor.setMainres(moogFilterComponent.resMainSlider.getValue());
        };

    moogFilterComponent.indexSquareSlider.onValueChange = [this] {
        audioProcessor.setSquareindex(moogFilterComponent.indexSquareSlider.getValue());
        };

    moogFilterComponent.indexSawSlider.onValueChange = [this] {
        audioProcessor.setSawindex(moogFilterComponent.indexSawSlider.getValue());
        };

    moogFilterComponent.indexPulseSlider.onValueChange = [this] {
        audioProcessor.setPulseindex(moogFilterComponent.indexPulseSlider.getValue());
        };

    moogFilterComponent.frSquareSlider.onValueChange = [this] {
        audioProcessor.setSquarefr(moogFilterComponent.frSquareSlider.getValue());
        };

    moogFilterComponent.frSawSlider.onValueChange = [this] {
        audioProcessor.setSawfr(moogFilterComponent.frSawSlider.getValue());
        };

    moogFilterComponent.frPulseSlider.onValueChange = [this] {
        audioProcessor.setPulsefr(moogFilterComponent.frPulseSlider.getValue());
        };

    moogFilterComponent.resSquareSlider.onValueChange = [this] {
        audioProcessor.setSquareres(moogFilterComponent.resSquareSlider.getValue());
        };

    moogFilterComponent.resSawSlider.onValueChange = [this] {
        audioProcessor.setSawres(moogFilterComponent.resSawSlider.getValue());
        };

    moogFilterComponent.resPulseSlider.onValueChange = [this] {
        audioProcessor.setPulseres(moogFilterComponent.resPulseSlider.getValue());
        };
}

void MonoSynthAudioProcessorEditor::reverbValueChange()
{
    reverbComponent.dtSlider.onValueChange = [this] {
        audioProcessor.setReverberationTime(reverbComponent.dtSlider.getValue());
        };

    reverbComponent.dampSlider.onValueChange = [this] {
        audioProcessor.setDamp(reverbComponent.dampSlider.getValue());
        };

    reverbComponent.sizeSlider.onValueChange = [this] {
        audioProcessor.setRoomSize(reverbComponent.sizeSlider.getValue());
        };

    reverbComponent.earlyDiffSlider.onValueChange = [this] {
        audioProcessor.setEarlyDiff(reverbComponent.earlyDiffSlider.getValue());
        };

    reverbComponent.feedbackSlider.onValueChange = [this] {
        audioProcessor.setFeedback(reverbComponent.feedbackSlider.getValue());
        };

    reverbComponent.modDepthSlider.onValueChange = [this] {
        audioProcessor.setReverbModDepth(reverbComponent.modDepthSlider.getValue());
        };

    reverbComponent.modFreqSlider.onValueChange = [this] {
        audioProcessor.setReverbModFreq(reverbComponent.modFreqSlider.getValue());
        };

    reverbComponent.dryWetMixSlider.onValueChange = [this] {
        audioProcessor.setReverbWetDry(reverbComponent.dryWetMixSlider.getValue());
        };

}

void MonoSynthAudioProcessorEditor::connectAttachment(std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment, juce::AudioProcessorValueTreeState& apvts,
    juce::String paramID, juce::Slider& slider)
{
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramID, slider);
}