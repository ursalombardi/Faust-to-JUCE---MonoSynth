/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <iostream>

//==============================================================================
MonoSynthAudioProcessorEditor::MonoSynthAudioProcessorEditor (MonoSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(800, 240);

    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::gile_JPG, BinaryData::gile_JPGSize);

    // Freqency 
    addAndMakeVisible(frequencySlider);
    frequencySlider.setRange(50.0, 5000.0, 0.01);
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
    moogfrSlider.setRange(200.0, 4000.0);
    moogfrSlider.setValue(200.0);
    moogfrSlider.onValueChange = [this] {
        audioProcessor.setMoogfr(moogfrSlider.getValue());
    };
    addAndMakeVisible(moogfrLabel);
    moogfrLabel.setText("Moog fr", juce::NotificationType::dontSendNotification);
    moogfrLabel.attachToComponent(&moogfrSlider, true);

    // Moog Filter 2
    addAndMakeVisible(moogfrSlider2);
    moogfrSlider2.setRange(200.0, 4000.0);
    moogfrSlider2.setValue(2000.0);
    moogfrSlider2.onValueChange = [this] {
        audioProcessor.setMoogfr(moogfrSlider2.getValue());
        };
    addAndMakeVisible(moogfrLabel2);
    moogfrLabel2.setText("Moog fr2", juce::NotificationType::dontSendNotification);
    moogfrLabel2.attachToComponent(&moogfrSlider2, true);

    // Moog Res 1
    addAndMakeVisible(moogResSlider);
    moogResSlider.setRange(0.0, 1.0);
    moogResSlider.setValue(0.7);
    moogResSlider.onValueChange = [this] {
        audioProcessor.setMoogRes(moogResSlider.getValue());
        };
    addAndMakeVisible(moogResLabel);
    moogResLabel.setText("Moog Res", juce::NotificationType::dontSendNotification);
    moogResLabel.attachToComponent(&moogResSlider, true);

    // Moog Res 2
    addAndMakeVisible(moogResSlider2);
    moogResSlider2.setRange(0.0, 1.0);
    moogResSlider2.setValue(0.5);
    moogResSlider2.onValueChange = [this] {
        audioProcessor.setMoogRes(moogResSlider2.getValue());
        };
    addAndMakeVisible(moogResLabel2);
    moogResLabel2.setText("Moog Res", juce::NotificationType::dontSendNotification);
    moogResLabel2.attachToComponent(&moogResSlider2, true);

    // On/Off button
    addAndMakeVisible(onOffButton);
    onOffButton.setTriggeredOnMouseDown(true);
    onOffButton.setToggleState(audioProcessor.noteOnMessages != 0, juce::NotificationType::dontSendNotification);
    onOffButton.onClick= [this] {
        audioProcessor.setGate(onOffButton.getToggleState());
    };
    addAndMakeVisible(onOffLabel);
    onOffLabel.setText("On/Off", juce::NotificationType::dontSendNotification);
    onOffLabel.attachToComponent(&onOffButton, true);
}

MonoSynthAudioProcessorEditor::~MonoSynthAudioProcessorEditor()
{
}

//==============================================================================
void MonoSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.drawImageAt(backgroundImage, 20, -30);
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

   // g.setColour (juce::Colours::blue);
}

void MonoSynthAudioProcessorEditor::resized()
{
    const int sliderLeft = 80;
    frequencySlider.setBounds(sliderLeft, 10, getWidth() - sliderLeft - 20, 20);
    gainSlider.setBounds(sliderLeft, 40, getWidth() - sliderLeft - 20, 20);
    moogfrSlider.setBounds(sliderLeft, 70, getWidth() - sliderLeft - 20, 20);
    moogfrSlider2.setBounds(sliderLeft, 100, getWidth() - sliderLeft - 20, 20);
    moogResSlider.setBounds(sliderLeft, 130, getWidth() - sliderLeft - 20, 20);
    moogResSlider2.setBounds(sliderLeft, 160, getWidth() - sliderLeft - 20, 20);

    onOffButton.setBounds(sliderLeft, 190, getWidth() - sliderLeft - 20, 20);

    testLabel.setBounds(sliderLeft, 210, getWidth() - sliderLeft - 20, 20);
}
