/*
  ==============================================================================

    SynthSound.h
    Created: 5 Feb 2024 10:30:23am
    Author:  Matthew

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound {
public:
    bool appliesToNote(int midiNoteNumber) override { return true; }
    bool appliesToChannel(int midiNotChannel) override { return true; }
};