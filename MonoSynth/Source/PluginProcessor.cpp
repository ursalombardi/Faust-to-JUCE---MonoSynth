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
#include <random>

//==============================================================================
MonoSynthAudioProcessor::MonoSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    )
#endif
{   
}

MonoSynthAudioProcessor::~MonoSynthAudioProcessor()
{
}

// Basic
void MonoSynthAudioProcessor::setFreq(float freq) { fUI->setParamValue("freq", freq); }
void MonoSynthAudioProcessor::setGain(float gain) { fUI->setParamValue("gain", gain); }
void MonoSynthAudioProcessor::setGate(bool gate) { fUI->setParamValue("gate", gate ? 1: 0); }

// Moog VCF
void MonoSynthAudioProcessor::setMainfr(float fr) { fUI->setParamValue("fr", fr); }
void MonoSynthAudioProcessor::setMainres(float res) { fUI->setParamValue("res", res); }
void MonoSynthAudioProcessor::setSquarefr(float fr2) { fUI->setParamValue("fr2", fr2); }
void MonoSynthAudioProcessor::setSquareres(float res2) { fUI->setParamValue("res2", res2); }
void MonoSynthAudioProcessor::setSawfr(float fr3) { fUI->setParamValue("fr3", fr3); }
void MonoSynthAudioProcessor::setSawres(float res3) { fUI->setParamValue("res3", res3); }
void MonoSynthAudioProcessor::setPulsefr(float fr4) { fUI->setParamValue("fr4", fr4); }
void MonoSynthAudioProcessor::setPulseres(float res4) { fUI->setParamValue("res4", res4); }
void MonoSynthAudioProcessor::setSquareindex(float index) { fUI->setParamValue("index", index); }
void MonoSynthAudioProcessor::setSawindex(float index2) { fUI->setParamValue("index2", index2); }
void MonoSynthAudioProcessor::setPulseindex(float index3) { fUI->setParamValue("index3", index3); }

// Reverb 
void MonoSynthAudioProcessor::setReverberationTime(float dt) { fUI->setParamValue("dt", dt); }
void MonoSynthAudioProcessor::setDamp(float damp) { fUI->setParamValue("damp", damp); }
void MonoSynthAudioProcessor::setRoomSize(float size) { fUI->setParamValue("size", size); }
void MonoSynthAudioProcessor::setEarlyDiff(float earlydiff){ fUI->setParamValue("earlydiff", earlydiff); }
void MonoSynthAudioProcessor::setFeedback(float feedback) { fUI->setParamValue("feedback", feedback); }
void MonoSynthAudioProcessor::setReverbModDepth(float moddepth){ fUI->setParamValue("moddepth", moddepth); }
void MonoSynthAudioProcessor::setReverbModFreq(float modfreq){ fUI->setParamValue("modfreq", modfreq); }
void MonoSynthAudioProcessor::setReverbWetDry(float wetdrymix){ fUI->setParamValue("wetdrymix", wetdrymix); }

// AR 
void MonoSynthAudioProcessor::setAttack(float attack) { fUI->setParamValue("attack", attack); }
void MonoSynthAudioProcessor::setRelease(float release) { fUI->setParamValue("release", release); }

// Tremelo
void MonoSynthAudioProcessor::setTremeloRate(float trem) { fUI->setParamValue("trem", trem); }
void MonoSynthAudioProcessor::setTremeloGate(bool gate) { fUI->setParamValue("select", gate); }

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
    // If this is called twice, as it may be in juce_audio_plugin_client_vst3.cpp, removing an instance of the plugin
    // will crash the DAW. The nullptr check worked for all the pointers except outputs**
    // So now there is a flag that checks if releaseResources has been called already. 

    if (releaseResourcesFlag == false) {
        if (fDSP != nullptr) {
            delete fDSP;
            fDSP = nullptr;
        }

        if (fUI != nullptr) {
            delete fUI;
            fUI = nullptr;
        }

        for (int channel = 0; channel < 2; ++channel) {
            if (outputs[channel] != nullptr) {
                delete[] outputs[channel];
                outputs[channel] = nullptr;
            }
        }

        delete[] outputs;
    }

    releaseResourcesFlag = true;
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
       
        if (message.isController()) {
            DBG(message.getControllerNumber() << " " << message.getControllerValue());
            
            if (message.getControllerNumber() == 74)
            {
                controllerValueFreq1 = message.getControllerValue();
                controllerFlagFreq1 = true;
            }
            if (message.getControllerNumber() == 71)
            {
                controllerValueFreq2 = message.getControllerValue();
                controllerFlagFreq2 = true;
            }
            if (message.getControllerNumber() == 20)
            {
                controllerValueRes1 = message.getControllerValue();
                controllerFlagRes1 = true;
            }
            if (message.getControllerNumber() == 21)
            {
                controllerValueRes2 = message.getControllerValue();
                controllerFlagRes2 = true;
            }
        }

        if (message.isNoteOff())
        {
            if (message.getNoteNumber() == currentNoteNumber)
                setGate(false);
        }

        if (message.isNoteOn())
        {
            setGate(false);
            noteNumber = message.getNoteNumber();
            noteNumberInHertz = message.getMidiNoteInHertz(noteNumber);
            int velocity = message.getVelocity();
            DBG("Note On: Note Number = " << noteNumber << ", Velocity = " << velocity);
            setGate(true);
            currentNoteNumber = noteNumber;
            currentNoteInHertz = noteNumberInHertz;
        }

       if (message.isPitchWheel()) {
            
            if (message.getPitchWheelValue() > 8192) {
                double x = message.getPitchWheelValue();
                pitchWheelMultiplier = ( (1.0 / 8191) * (x - 8192) + 1);
            }
            if (message.getPitchWheelValue() <= 8192) {
                pitchWheelMultiplier = ((0.5 / 8192) * message.getPitchWheelValue() + 0.5);
            }
       }

       if (message.isSustainPedalOff()) {
           sustainPedalMulitplier = 4;
       }

       if (message.isSustainPedalOn()) {
           sustainPedalMulitplier = 1;
       }

    }

    setFreq(currentNoteInHertz * pitchWheelMultiplier * sustainPedalMulitplier);

    for (int channel = 0; channel < totalNumOutputChannels; ++channel) {
        for (int i = 0; i < buffer.getNumSamples(); i++) {
            *buffer.getWritePointer(channel, i) = outputs[channel][i];
        }
    }
}

void MonoSynthAudioProcessor::randomizeControllerValues()
{
    moogFreq1 = getRandomDoubleInRange(200.0, 4000.0);
    moogFreq2 = getRandomDoubleInRange(200.0, 4000.0);
    moogRes1 = getRandomDoubleInRange(0.0, 1.0);
    moogRes2 = getRandomDoubleInRange(0.0, 1.0);
}

double MonoSynthAudioProcessor::getRandomDoubleInRange(double min, double max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(min, max);
    return dis(gen);
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

