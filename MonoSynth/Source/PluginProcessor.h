#pragma once

#include <JuceHeader.h>
#include <vector>
#include <algorithm>

class dsp;
class MapUI;

class MonoSynthAudioProcessor  : public juce::AudioProcessor
{
public:
    MonoSynthAudioProcessor();
    ~MonoSynthAudioProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    const juce::String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    // Basic Controls
    void setFreq(float freq);
    void setGain(float gain);
    void setGate(bool gate);
    
    // Moog Filter Controls
    void setMainfr(float fr);
    void setMainres(float res);
    void setSquarefr(float fr2);
    void setSquareres(float res2);
    void setSawfr(float fr3);
    void setSawres(float res3);
    void setPulsefr(float fr4);
    void setPulseres(float res4);
    void setSquareindex(float index);
    void setSawindex(float index2);
    void setPulseindex(float index3);

    // Reverb controls
    void setReverberationTime(float dt);
    void setDamp(float damp);
    void setRoomSize(float size);
    void setEarlyDiff(float earlydiff);
    void setFeedback(float feedback);
    void setReverbModDepth(float moddepth);
    void setReverbModFreq(float modfreq);
    void setReverbWetDry(float wetdrymix);
    
    // AR Controls
    void setAttack(float attack);
    void setRelease(float release);

    // Tremelo
    void setTremeloRate(float trem);
    void setTremeloGate(bool tremgate);

    // Midi
    int noteNumber;
    double pitchWheelValue = 8192.0;
    double noteNumberInHertz;
    int currentNoteNumber;
    double currentNoteInHertz = 300.0;
    double pitchWheelMultiplier = 1;
    double sustainPedalMulitplier = 1;
    std::vector<int> activeNoteNumbers;
    
    // Midi Controls for main knobs
    double moogFreq1 = 800.0;
    double moogFreq2 = 2000.0;
    double moogRes1 = 0.5;
    double moogRes2 = 0.7;
    double controllerValueFreq1 = 200.0;
    double controllerValueFreq2= 2000.0;
    double controllerValueRes1 = 0.5;
    double controllerValueRes2 = 0.7;
    bool controllerFlagFreq1 = false;
    bool controllerFlagFreq2 = false;
    bool controllerFlagRes1 = false;
    bool controllerFlagRes2 = false;
    void randomizeControllerValues();
    double getRandomDoubleInRange(double min, double max);
    
    // Prevents crashes
    bool releaseResourcesFlag = false;

private:
    MapUI* fUI;
    dsp* fDSP;
    float** outputs; // double array (one dimension for audio channels and one for audio samples/buffers)

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MonoSynthAudioProcessor)
};
