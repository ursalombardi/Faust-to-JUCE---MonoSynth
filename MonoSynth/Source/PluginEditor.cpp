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
    setSize(800, 130);

    addAndMakeVisible(frequencySlider);
    frequencySlider.setRange(50.0, 5000.0, 0.01);
    frequencySlider.setNumDecimalPlacesToDisplay(2);
    frequencySlider.setSkewFactorFromMidPoint(500.0);
    frequencySlider.setValue(400);
    frequencySlider.onValueChange = [this] {
        audioProcessor.setFreq(frequencySlider.getValue());  

    };

    addAndMakeVisible(frequencyLabel);
    frequencyLabel.setText("Frequency", juce::NotificationType::dontSendNotification);
    frequencyLabel.attachToComponent(&frequencySlider, true);

    addAndMakeVisible(gainSlider);
    gainSlider.setRange(0.0, 1.0);
    gainSlider.setValue(0.5);
    gainSlider.onValueChange = [this] {
        audioProcessor.setGain(gainSlider.getValue());
    };

    addAndMakeVisible(gainLabel);
    gainLabel.setText("Gain", juce::NotificationType::dontSendNotification);
    gainLabel.attachToComponent(&gainSlider, true);

    addAndMakeVisible(cutoffSlider);
    cutoffSlider.setRange(50.0, 10000.0);
    cutoffSlider.setValue(5000.0);
    cutoffSlider.onValueChange = [this] {
        audioProcessor.setCutoff(cutoffSlider.getValue());
    };

    addAndMakeVisible(cutoffLabel);
    cutoffLabel.setText("Cutoff", juce::NotificationType::dontSendNotification);
    cutoffLabel.attachToComponent(&cutoffSlider, true);

    addAndMakeVisible(onOffButton);
    onOffButton.setTriggeredOnMouseDown(true);
    onOffButton.onClick= [this] {
        audioProcessor.setGate(onOffButton.getToggleState());
    };

    addAndMakeVisible(onOffLabel);
    onOffLabel.setText("On/Off", juce::NotificationType::dontSendNotification);
    onOffLabel.attachToComponent(&onOffButton, true);

    addAndMakeVisible(gainSlider);
    gainSlider.setRange(0.0, 1.0);
    gainSlider.setValue(0.5);
    gainSlider.onValueChange = [this] {
        audioProcessor.setGain(gainSlider.getValue());
    };

    addAndMakeVisible(gainLabel);
    gainLabel.setText("Gain", juce::NotificationType::dontSendNotification);
    gainLabel.attachToComponent(&gainSlider, true);
}

MonoSynthAudioProcessorEditor::~MonoSynthAudioProcessorEditor()
{
}

//==============================================================================
void MonoSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
}

void MonoSynthAudioProcessorEditor::resized()
{
    const int sliderLeft = 80;
    frequencySlider.setBounds(sliderLeft, 10, getWidth() - sliderLeft - 20, 20);
    gainSlider.setBounds(sliderLeft, 40, getWidth() - sliderLeft - 20, 20);
    cutoffSlider.setBounds(sliderLeft, 70, getWidth() - sliderLeft - 20, 20);
    onOffButton.setBounds(sliderLeft, 100, getWidth() - sliderLeft - 20, 20);
}
