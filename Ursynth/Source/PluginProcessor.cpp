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
    ), apvts(*this, nullptr, "Parameters", createParameters())
#endif
{   
    apvts.state.setProperty(PresetManager::presetNameProperty, "", nullptr);
    apvts.state.setProperty("version", ProjectInfo::versionString, nullptr);
    presetManager = std::make_unique<PresetManager>(apvts);
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
        }

        if (message.isNoteOff())
        {
            auto it = std::find(activeNoteNumbers.begin(), activeNoteNumbers.end(), message.getNoteNumber());
            if (it != activeNoteNumbers.end())
                activeNoteNumbers.erase(it);
            
            if (activeNoteNumbers.empty())
                setGate(false);
            else
            {
                noteNumber = activeNoteNumbers.back();
                noteNumberInHertz = message.getMidiNoteInHertz(noteNumber);
                currentNoteNumber = noteNumber;
                currentNoteInHertz = noteNumberInHertz;
            }
        }

        if (message.isNoteOn())
        {
            noteNumber = message.getNoteNumber();
            activeNoteNumbers.push_back(noteNumber);
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
    const auto state = apvts.copyState();
    const auto xml(state.createXml());
    copyXmlToBinary(*xml, destData);

}

void MonoSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    const auto xmlState = getXmlFromBinary(data, sizeInBytes);
    if (xmlState == nullptr)
        return;
    const auto newTree = juce::ValueTree::fromXml(*xmlState);
    apvts.replaceState(newTree);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MonoSynthAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout MonoSynthAudioProcessor::createParameters()
{
    return juce::AudioProcessorValueTreeState::ParameterLayout{
                // Moog Filters
                std::make_unique<juce::AudioParameterFloat>("FRMAIN", "Main Frequency", juce::NormalisableRange<float> { 200.0f, 4000.0f, 0.01f }, 500.0f),
                std::make_unique<juce::AudioParameterFloat>("RESMAIN", "Main Res", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01f }, 0.7f),
                std::make_unique<juce::AudioParameterFloat>("INDEXSQUARE", "Index Square", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01f}, 0.65f),
                std::make_unique<juce::AudioParameterFloat>("INDEXSAW", "Index Saw", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01f}, 0.95f),
                std::make_unique<juce::AudioParameterFloat>("INDEXPULSE", "Index Pulse", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01f}, 0.2f),
                std::make_unique<juce::AudioParameterFloat>("FREQSQUARE", "Freq Square", juce::NormalisableRange<float> { 200.0f, 4000.0f, 0.01f}, 2000.0f),
                std::make_unique<juce::AudioParameterFloat>("FREQSAW", "Freq Saw", juce::NormalisableRange<float> { 200.0f, 4000.0f, 0.01f}, 2000.0f),
                std::make_unique<juce::AudioParameterFloat>("FREQPULSE", "Freq Pulse", juce::NormalisableRange<float> { 200.0f, 4000.0f, 0.01f}, 2000.0f),
                std::make_unique<juce::AudioParameterFloat>("RESSQUARE", "Res Square", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01}, 0.05f),
                std::make_unique<juce::AudioParameterFloat>("RESSAW", "Res Saw", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01}, 0.05f),
                std::make_unique<juce::AudioParameterFloat>("RESPULSE", "Res Pulse", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01}, 0.05f),
                // Reverb 
                std::make_unique<juce::AudioParameterFloat>("DT", "Time", juce::NormalisableRange<float> { 0.1f, 60.0f, 0.01}, 0.01f),
                //std::make_unique<juce::AudioParameterFloat>("DAMP", "Damp", juce::NormalisableRange<float> { 0.1f, 60.0f, 0.01}, 0.01f),
                std::make_unique<juce::AudioParameterFloat>("SIZE", "Size", juce::NormalisableRange<float> { 1.0f, 3.0f, 0.01}, 0.5f),
                std::make_unique<juce::AudioParameterFloat>("EARLYDIFF", "Early Diff", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01}, 0.0f),
                std::make_unique<juce::AudioParameterFloat>("FEEDBACK", "Feedback", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01f}, 0.25f),
                std::make_unique<juce::AudioParameterFloat>("MODDEPTH", "Mod Depth", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01}, 0.0f),
                std::make_unique<juce::AudioParameterFloat>("MODFREQ", "Mod Freq", juce::NormalisableRange<float> { 0.0f, 10.0f, 0.01}, 1.0f),
                std::make_unique<juce::AudioParameterFloat>("DRYWETMIX", "Dry Wet Mix", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01}, 0.5f),
                // AR
                std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float> { 0.01f, 6.0f, 0.01}, 0.01f),
                std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float> { 0.1f, 6.0f, 0.01}, 0.01f),
                //// Tremelo
                std::make_unique<juce::AudioParameterFloat>("TREMELO", "Tremelo", juce::NormalisableRange<float> { 0.0f, 6.0f, 0.01}, 0.00f),
    };
}
