#pragma once

#include <JuceHeader.h>
#include "../PresetManager.h"

//==============================================================================
/*
*/
class PresetComponent  : public juce::Component, juce::Button::Listener, juce::ComboBox::Listener
{
public:
    PresetComponent(PresetManager& pm) : presetManager(pm)
    {
        configureButton(saveButton, "Save");
        configureButton(deleteButton, "Delete");
        configureButton(previousPresetButton, "<");
        configureButton(nextPresetButton, ">");

        presetList.setTextWhenNothingSelected(" -- ");
        presetList.setMouseCursor(juce::MouseCursor::PointingHandCursor);
        addAndMakeVisible(presetList);
        presetList.addListener(this);

        loadPresetList();
    }

    ~PresetComponent() override
    {
        saveButton.removeListener(this);
        deleteButton.removeListener(this);
        previousPresetButton.removeListener(this);
        nextPresetButton.removeListener(this);
        presetList.removeListener(this);
    }

    void paint (juce::Graphics& g) override
    {
        g.setColour(juce::Colours::grey);
        g.drawRect(getLocalBounds(), 1);
    }

    void resized() override
    {
        saveButton.setBounds(0, 0, 133, 154/2);
        presetList.setBounds(0, 154 / 2, 133, 154 / 2);
    }

private:

    void buttonClicked(juce::Button* button) override
    {
        // Save Button
        if (button == &saveButton)
        {
            fileChooser = std::make_unique<juce::FileChooser>(
                "Please enter the name of the preset to Save",
                PresetManager::defaultDirectory,
                "*." + PresetManager::extension
            );
            fileChooser->launchAsync(juce::FileBrowserComponent::saveMode, [&](const juce::FileChooser& chooser)
                {
                    const auto resultFile = chooser.getResult();
                    presetManager.savePreset(resultFile.getFileNameWithoutExtension());
                    loadPresetList();
                });
        }
        // Previous Button
        if (button == &previousPresetButton)
        {
            const auto index = presetManager.loadPreviousPreset();
            presetList.setSelectedItemIndex(index, juce::NotificationType::dontSendNotification);
        }
        // Next Button
        if (button == &nextPresetButton)
        {
            const auto index = presetManager.loadNextPreset();
            presetList.setSelectedItemIndex(index, juce::NotificationType::dontSendNotification);
        }
        // Delete Button
        if (button == &deleteButton)
        {
            presetManager.deletePreset(presetManager.getCurrentPreset());
            loadPresetList();
        }
    }

    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override
    {
        if (comboBoxThatHasChanged == &presetList)
        {
            presetManager.loadPreset(presetList.getItemText(presetList.getSelectedItemIndex()));
        }
    }

    void configureButton(juce::Button& button, const juce::String& buttonText)
    {
        button.setButtonText(buttonText);
        button.setMouseCursor(juce::MouseCursor::PointingHandCursor);
        addAndMakeVisible(button);
        button.addListener(this);
    }

    void loadPresetList()
    {
        presetList.clear(juce::NotificationType::dontSendNotification);
        const auto allPresets = presetManager.getAllPresets();
        const auto currentPreset = presetManager.getCurrentPreset();
        presetList.addItemList(allPresets, 1);
        presetList.setSelectedItemIndex(allPresets.indexOf(currentPreset), juce::NotificationType::dontSendNotification);
    }

    PresetManager& presetManager;
    juce::TextButton saveButton, deleteButton, previousPresetButton, nextPresetButton;
    juce::ComboBox presetList;
    std::unique_ptr<juce::FileChooser> fileChooser;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetComponent)
};
