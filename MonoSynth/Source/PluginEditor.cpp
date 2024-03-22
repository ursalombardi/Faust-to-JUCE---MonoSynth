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
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(800, 500);
    startTimer(100);

    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::fogwall_png, BinaryData::fogwall_pngSize);
    juce::Font Algerian("Algerian", 20.f, 0);
    juce::Font AgencyFB("Agency FB", 20.f, 0);
  
    int controlTextBoxWidth = 80;

    addAndMakeVisible(knobRandomizer);
    knobRandomizer.setButtonText("Random");
    knobRandomizer.onClick = [this] {
        setControllerFlagsFalse();
        audioProcessor.randomizeControllerValues();

        //audioProcessor.setMainfr(audioProcessor.moogFreq1);
        //moogfrSlider.setValue(audioProcessor.moogFreq1);

        audioProcessor.setSquarefr(audioProcessor.moogFreq2);
        //moogfrSlider2.setValue(audioProcessor.moogFreq2);

        audioProcessor.setMainres(audioProcessor.moogRes1);
        //moogResSlider.setValue(audioProcessor.moogRes1);

        audioProcessor.setSquareres(audioProcessor.moogRes2);
        //moogResSlider2.setValue(audioProcessor.moogRes2);
        };

    // Freqency 
    addAndMakeVisible(frequencySlider);
    frequencySlider.setRange(50.0, 5000.0, 29.92);
    frequencySlider.setNumDecimalPlacesToDisplay(2);
    frequencySlider.setSkewFactorFromMidPoint(500.0);
    frequencySlider.setValue(200);
    frequencySlider.onValueChange = [this] {
        audioProcessor.setFreq(frequencySlider.getValue());
        };

    // Gain
    addAndMakeVisible(gainSlider);
    gainSlider.setRange(0.0, 1.0);
    gainSlider.setValue(0.5);
    gainSlider.onValueChange = [this] {
        audioProcessor.setGain(gainSlider.getValue());
        };

    // Moog Filter Component
    addAndMakeVisible(moogFilterComponent);
    moogFilterValueChange();

    // Reverb Component
    addAndMakeVisible(reverbComponent);
    reverbValueChange();

    // AR Sliders
    addAndMakeVisible(attackSlider);
    attackSlider.setRange(0.01, 7.0);
    attackSlider.setValue(0.01);
    attackSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    attackSlider.onValueChange = [this] {
        audioProcessor.setAttack(attackSlider.getValue());
        };

    addAndMakeVisible(releaseSlider);
    releaseSlider.setRange(0.01, 5.0);
    releaseSlider.setValue(0.01);
    releaseSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    releaseSlider.onValueChange = [this] {
        audioProcessor.setRelease(releaseSlider.getValue());
        };

    // Tremelo Slider
    addAndMakeVisible(tremSlider);
    tremSlider.setRange(0.0, 6.0);
    tremSlider.setValue(0.0);
    tremSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    tremSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    tremSlider.onValueChange = [this] {

        audioProcessor.setTremeloRate(tremSlider.getValue());
        if (tremSlider.getValue() > 0.0)
            audioProcessor.setTremeloGate(true);
        else
            audioProcessor.setTremeloGate(false);
        };   
}

MonoSynthAudioProcessorEditor::~MonoSynthAudioProcessorEditor()
{
    knobRandomizer.setLookAndFeel(nullptr);
}

//==============================================================================
void MonoSynthAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)

    // King Giles  

    g.drawImageAt(backgroundImage, 0, 0);

    juce::Rectangle<int> bounds = getLocalBounds();

    // Define the colors for the sunset gradient
    juce::Colour color1 = juce::Colour::fromFloatRGBA(0.1f, 0.1f, 0.2f, 1.0f); // Dark navy blue
    juce::Colour color2 = juce::Colour::fromFloatRGBA(0.2f, 0.2f, 0.3f, 0.9f); // Light gray

    // Create a LinearGradient object for the gradient
    juce::ColourGradient gradient(color1, 0, 0, color2, 0, static_cast<float>(bounds.getHeight()), false);

    // Fill the background with the gradient
    g.setGradientFill(gradient);
    //g.fillRect(bounds);

}

void MonoSynthAudioProcessorEditor::resized()
{
    int leftOffset = 20; 
    int topOffset = 45;
    int mainControlSize = 100;

    moogFilterComponent.setBounds(0, 100, 400, 400);
    reverbComponent.setBounds(300, 0, 500, 350);
    attackSlider.setBounds(300, 380, 200, 20);
    releaseSlider.setBounds(300, 430, 200, 20);
    tremSlider.setBounds(550, 375, 30, 100);

    knobRandomizer.setBounds(700, 470, 100, 30);
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