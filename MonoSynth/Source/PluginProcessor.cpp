/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "FaustSynth.h"
#include <iostream>

//==============================================================================
MonoSynthAudioProcessor::MonoSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

MonoSynthAudioProcessor::~MonoSynthAudioProcessor()
{
}

void MonoSynthAudioProcessor::setFreq(float freq) { fUI->setParamValue("freq", freq); }

void MonoSynthAudioProcessor::setGain(float gain) { fUI->setParamValue("gain", gain); }

void MonoSynthAudioProcessor::setCutoff(float cutoff) { fUI->setParamValue("cutoff", cutoff); }

void MonoSynthAudioProcessor::setGate(bool gate) { fUI->setParamValue("gate", gate ? 1: 0); }

//==============================================================================
const juce::String MonoSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MonoSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MonoSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MonoSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MonoSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MonoSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MonoSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MonoSynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MonoSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void MonoSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MonoSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    fDSP = new mydsp();
    fDSP->init(sampleRate);
    fUI = new MapUI();
    fDSP->buildUserInterface(fUI);
    outputs = new float*[2];
    
    for (int channel = 0; channel < 2; ++channel) {
        outputs[channel] = new float[samplesPerBlock];
    }
}

void MonoSynthAudioProcessor::releaseResources()
{
    delete fDSP; 
    delete fUI;
    for (int channel = 0; channel < 2; ++channel) {
        delete[] outputs[channel];
    }
    delete[] outputs;
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MonoSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MonoSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    fDSP->compute(buffer.getNumSamples(), NULL, outputs);

    for (const auto metadata : midiMessages)
    {
        const auto message = metadata.getMessage();
        const auto timestamp = metadata.samplePosition;

        if (message.isNoteOn())
        {
            int noteNumber = message.getNoteNumber();
            int velocity = message.getVelocity();
            // Do something with the note-on message
            DBG("Note On: Note Number = " << noteNumber << ", Velocity = " << velocity);
            setGate(true);
            setFreq(message.getMidiNoteInHertz(noteNumber));
            noteOnMessages++;
        }
        
        if (message.isNoteOff())
        {
            noteOnMessages--;
        }

        if (noteOnMessages == 0) {
            setGate(false);
        }
    }

    for (int channel = 0; channel < totalNumOutputChannels; ++channel) {
        for (int i = 0; i < buffer.getNumSamples(); i++) {
            *buffer.getWritePointer(channel, i) = outputs[channel][i];
        }
    }

}

//==============================================================================
bool MonoSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MonoSynthAudioProcessor::createEditor()
{
    return new MonoSynthAudioProcessorEditor (*this);
}

//==============================================================================
void MonoSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MonoSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MonoSynthAudioProcessor();
}

