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

    addAndMakeVisible(ursynth);
    ursynth.setText("Ursyth", juce::NotificationType::dontSendNotification);

    addAndMakeVisible(knobRandomizer);
    knobRandomizer.setButtonText("Random");
    knobRandomizer.onClick = [this] {
        setControllerFlagsFalse();
        audioProcessor.randomizeControllerValues();

        audioProcessor.setMoogfr(audioProcessor.moogFreq1);
        moogfrSlider.setValue(audioProcessor.moogFreq1);

        audioProcessor.setMoogfr2(audioProcessor.moogFreq2);
        moogfrSlider2.setValue(audioProcessor.moogFreq2);

        audioProcessor.setMoogRes(audioProcessor.moogRes1);
        moogResSlider.setValue(audioProcessor.moogRes1);

        audioProcessor.setMoogRes2(audioProcessor.moogRes2);
        moogResSlider2.setValue(audioProcessor.moogRes2);
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
    addAndMakeVisible(frequencyLabel);
    frequencyLabel.setText("Frequency", juce::NotificationType::dontSendNotification);
    frequencyLabel.attachToComponent(&frequencySlider, true);

    // Gain
    addAndMakeVisible(gainSlider);
    gainSlider.setRange(0.0, 1.0);
    gainSlider.setValue(0.5);
    gainSlider.onValueChange = [this] {
        audioProcessor.setGain(gainSlider.getValue());
        };
    addAndMakeVisible(gainLabel);
    gainLabel.setText("Gain", juce::NotificationType::dontSendNotification);
    gainLabel.attachToComponent(&gainSlider, true);

    // Moog Filter 1
    addAndMakeVisible(moogfrSlider);
    moogfrSlider.setLookAndFeel(&reverbLookAndFeel);
    moogfrSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    //moogfrSlider.setRotaryParameters(juce::MathConstants<float>::pi, juce::MathConstants<float>::pi * 2.99, false);
    moogfrSlider.setRange(200.0, 4000.0, (4000.0 - 200.0) / 127.0);
    moogfrSlider.setValue(200.0);
    moogfrSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, controlTextBoxWidth, 20);
    moogfrSlider.setNumDecimalPlacesToDisplay(2);
    moogfrSlider.onValueChange = [this] {
        audioProcessor.setMoogfr(moogfrSlider.getValue());
        setControllerFlagsFalse();
        };
    //addAndMakeVisible(moogfrLabel);
    moogfrLabel.toFront(true);
    moogfrLabel.setText("Frequency 1", juce::NotificationType::dontSendNotification);
    moogfrLabel.setFont(Algerian);

    // Moog Filter 2
    addAndMakeVisible(moogfrSlider2);
    moogfrSlider2.setLookAndFeel(&reverbLookAndFeel);
    moogfrSlider2.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    //moogfrSlider2.setRotaryParameters(juce::MathConstants<float>::pi, juce::MathConstants<float>::pi * 2.99, false);
    moogfrSlider2.setRange(200.0, 4000.0);
    moogfrSlider2.setValue(2000.0);
    moogfrSlider2.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, controlTextBoxWidth, 20);
    moogfrSlider2.setNumDecimalPlacesToDisplay(2);
    moogfrSlider2.onValueChange = [this] {
        audioProcessor.setMoogfr2(moogfrSlider2.getValue());
        setControllerFlagsFalse();
        };
    //addAndMakeVisible(moogfrLabel2);
    moogfrLabel2.setText("Frequency 2", juce::NotificationType::dontSendNotification);
    moogfrLabel2.setFont(Algerian);

    // Moog Res 1
    addAndMakeVisible(moogResSlider);
    moogResSlider.setLookAndFeel(&reverbLookAndFeel);
    moogResSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    //moogResSlider.setRotaryParameters(juce::MathConstants<float>::pi, juce::MathConstants<float>::pi * 2.99, false);
    moogResSlider.setRange(0.0, 1.0);
    moogResSlider.setValue(0.7);
    moogResSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, controlTextBoxWidth, 20);
    moogResSlider.setNumDecimalPlacesToDisplay(2);
    moogResSlider.onValueChange = [this] {
        audioProcessor.setMoogRes(moogResSlider.getValue());
        setControllerFlagsFalse();
        };
    //addAndMakeVisible(moogResLabel);
    moogResLabel.setText("Resonance 1", juce::NotificationType::dontSendNotification);
    moogResLabel.setFont(Algerian);

    // Moog Res 2
    addAndMakeVisible(moogResSlider2);
    moogResSlider2.setLookAndFeel(&reverbLookAndFeel);
    moogResSlider2.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    //moogResSlider2.setRotaryParameters(juce::MathConstants<float>::pi, juce::MathConstants<float>::pi * 2.99, false);
    moogResSlider2.setRange(0.0, 1.0);
    moogResSlider2.setValue(0.5);
    moogResSlider2.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, controlTextBoxWidth, 20);
    moogResSlider2.setNumDecimalPlacesToDisplay(2);
    moogResSlider2.onValueChange = [this] {
        audioProcessor.setMoogRes(moogResSlider2.getValue());
        setControllerFlagsFalse();
        };
    //addAndMakeVisible(moogResLabel2);
    moogResLabel2.setText("Resonance 2", juce::NotificationType::dontSendNotification);
    moogResLabel2.setFont(Algerian);

    // Reverb Component
    addAndMakeVisible(reverbComponent);
    reverbValueChange();
}

MonoSynthAudioProcessorEditor::~MonoSynthAudioProcessorEditor()
{
    moogfrSlider.setLookAndFeel(nullptr);
    moogfrSlider2.setLookAndFeel(nullptr);
    moogResSlider.setLookAndFeel(nullptr);
    moogResSlider2.setLookAndFeel(nullptr);
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

    ursynth.setBounds(0, 0, 30, 30);
  
    moogfrSlider.setBounds(leftOffset, topOffset, mainControlSize, mainControlSize);
    moogfrLabel.setBounds(moogfrSlider.getBounds().getX(), moogfrSlider.getBounds().getY() - 30, 100, 25);
    
    moogfrSlider2.setBounds(leftOffset + 120, topOffset, mainControlSize, mainControlSize);
    moogfrLabel2.setBounds(moogfrSlider2.getBounds().getX() + 35, moogfrSlider2.getBounds().getY() - 30, 100, 25);
    
    moogResSlider.setBounds(leftOffset + 240, topOffset, mainControlSize, mainControlSize);
    moogResLabel.setBounds(moogResSlider.getBounds().getX(), moogResSlider.getBounds().getY() - 30, 100, 25);
    
    moogResSlider2.setBounds(leftOffset + 360, topOffset, mainControlSize, mainControlSize);
    moogResLabel2.setBounds(moogResSlider2.getBounds().getX() + 35, moogResSlider2.getBounds().getY() - 30, 100, 25);

    reverbComponent.setBounds(0, 200, 500, 250);

    knobRandomizer.setBounds(200, 470, 100, 30);

    ursynth.setBounds(0, 0, 200, 200);

}

void MonoSynthAudioProcessorEditor::timerCallback()
{
    if (audioProcessor.controllerFlagFreq1) {
        audioProcessor.moogFreq1 = audioProcessor.controllerValueFreq1 * (3800.0 / 127.0) + 200;
        moogfrSlider.setValue(audioProcessor.moogFreq1);
    }
    
    if (audioProcessor.controllerFlagFreq2)
    {
        audioProcessor.moogFreq2 = audioProcessor.controllerValueFreq2 * (3800.0 / 127.0) + 200;
        moogfrSlider2.setValue(audioProcessor.moogFreq2);
    }
    
    if (audioProcessor.controllerFlagRes1)
    {
        audioProcessor.moogRes1 = audioProcessor.controllerValueRes1 / 127.0;
        moogResSlider.setValue(audioProcessor.moogRes1);
    }
    
    if (audioProcessor.controllerFlagRes2)
    {
        audioProcessor.moogRes2 = audioProcessor.controllerValueRes2 / 127.0;
        moogResSlider2.setValue(audioProcessor.moogRes2);
    }
}


void MonoSynthAudioProcessorEditor::setControllerFlagsFalse()
{
    audioProcessor.controllerFlagFreq1 = false;
    audioProcessor.controllerFlagFreq2 = false;
    audioProcessor.controllerFlagRes1 = false;
    audioProcessor.controllerFlagRes2 = false;
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