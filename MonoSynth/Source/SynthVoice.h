/*
  ==============================================================================

    SynthVoice.h
    Created: 5 Feb 2024 10:30:11am
    Author:  Matthew

  ==============================================================================
*/

#pragma once

#include "SynthVoice.h"

class SynthVoice : public juce::SynthesiserVoice {
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
private:

};