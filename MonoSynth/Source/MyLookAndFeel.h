/*
  ==============================================================================

    MyLookAndFeel.h
    Created: 12 Mar 2024 10:49:53am
    Author:  Matthew

  ==============================================================================
*/

#pragma once
#include<JuceHeader.h>

class MyLookAndFeel : public juce::LookAndFeel_V4
{
public:
    MyLookAndFeel()
    {
        setColour(juce::Slider::thumbColourId, juce::Colours::red);
    }

    void drawButtonText(juce::Graphics& g, juce::TextButton& t, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
    {
        shouldDrawButtonAsDown = true;
        shouldDrawButtonAsHighlighted = true;
        juce::Font myFont("Algerian", 7.0f, 0);
        g.setFont(myFont);
    }

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override {
        auto radius = (float)juce::jmin(width / 2, height / 2) - 4.0f;
        auto centreX = (float)x + (float)width * 0.5f;
        auto centreY = (float)y + (float)height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        // fill
        juce::Colour center(0xFFfffed1);
        g.setColour(center);
        g.fillEllipse(rx, ry, rw, rw);

        // outline
        juce::Colour perim(0xFFefa959);
        g.setColour(perim);
        g.drawEllipse(rx, ry, rw, rw, 5.0f);
        juce::Path p;
        auto pointerLength = radius * 0.33f;
        auto pointerThickness = 4.0f;
        p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        
        p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));
        // pointer
        g.setColour(juce::Colours::black);
        g.fillPath(p);
    }
};