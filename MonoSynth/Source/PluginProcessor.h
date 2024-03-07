/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class dsp;
class MapUI;

//==============================================================================
/**
*/
class MonoSynthAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    MonoSynthAudioProcessor();
    ~MonoSynthAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================
    void setFreq(float freq);
    void setGain(float gain);
    void setCutoff(float cutoff);
    void setGate(bool gate);
    void setMoogfr(float fr);
    void setMoogfr2(float fr2);
    void setMoogRes(float res);
    void setMoogRes2(float res2);

    int noteNumber;
    double pitchWheelValue = 8192.0;
    double noteNumberInHertz;
   
    int currentNoteNumber;
    double currentNoteInHertz = 300.0;

    double pitchWheelMultiplier = 1;
    double sustainPedalMulitplier = 1;
    
    double controllerValueFreq1 = 200;
    double controllerValueFreq2= 2000;
    double controllerValueRes1 = 0.5;
    double controllerValueRes2 = 0.7;
    bool controllerFlagFreq1 = false;
    bool controllerFlagFreq2 = false;
    bool controllerFlagRes1 = false;
    bool controllerFlagRes2 = false;
    
    int noteOnMessages = 0;
    bool releaseResourcesFlag = false;

private:
    MapUI* fUI;
    dsp* fDSP;
    float** outputs; // double array (one dimension for audio channels and one for audio samples/buffers)

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MonoSynthAudioProcessor)
};
