/*
  ==============================================================================

    SynthVoice.cpp
    Created: 5 Feb 2024 10:30:11am
    Author:  Matthew

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return true;
}
void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{

}
void SynthVoice::stopNote(float velocity, bool allowTailOff)
{

}