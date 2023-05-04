/*
  ==============================================================================

    DeckGUI.h
    Created: 1 Aug 2022 12:46:39am
    Author:  Julie Song

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"


//==============================================================================
/*
*/
class DeckGUI    : public Component,
                   public Button::Listener, 
                   public Slider::Listener,
                   public FileDragAndDropTarget
{
public:
    //accessing the DJAudiPlayer through constructor 
    DeckGUI(DJAudioPlayer* player);
    ~DeckGUI();

    void paint (juce::Graphics&) override;
    void resized() override;

    /** implement Button::Listener */
    void buttonClicked (Button *) override;

    /** implement Slider::Listener */
    void sliderValueChanged (Slider *slider) override;
    
    bool isInterestedInFileDrag(const StringArray&files) override ;
    void filesDropped(const StringArray&files,int x, int y) override;
    
private:
    FileChooser fChooser{"Select a file..."};

    TextButton playButton{"PLAY"};
    TextButton stopButton{"STOP"};
    TextButton loadButton{"LOAD"};
  
    Slider volSlider;
    Slider speedSlider;
    Slider posSlider;
    
    DJAudioPlayer* player;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
