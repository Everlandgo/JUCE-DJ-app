/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 31 Jul 2022 11:04:00pm
    Author:  Julie Song

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class DJAudioPlayer: public AudioSource {
public:
    DJAudioPlayer();//constructor
    ~DJAudioPlayer();
    
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    
    
    void loadURL(URL audioURL);
    void setGain(double gain);
    void setPosition(double posInSecs);
    void setSpeed(double ratio);
    void setPositionRelative(double pos);//to get the length of the audio file
    
    void start();
    void stop();

private:
    AudioFormatManager formatManager;//to allow different formats of audiofile
    AudioTransportSource transportSource;//control the audiofile 
    std::unique_ptr<AudioFormatReaderSource> readerSource;//unique pointer
    
    ResamplingAudioSource resampleSource{&transportSource,false,2};
    //A type of AudioSource that takes an input source and changes its sample rate
    
    

};


