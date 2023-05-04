/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 31 Jul 2022 11:04:00pm
    Author:  Julie Song

  ==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(){
    
}
DJAudioPlayer::~DJAudioPlayer()
{
    
}

void DJAudioPlayer::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    formatManager.registerBasicFormats();
    transportSource.prepareToPlay( samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay( samplesPerBlockExpected, sampleRate);
}
void DJAudioPlayer::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    resampleSource.getNextAudioBlock(bufferToFill);//called again and again
}
void DJAudioPlayer::releaseResources()
{
    transportSource.releaseResources();
    resampleSource.releaseResources();

}

void DJAudioPlayer::loadURL(URL audioURL)
{
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) // good file!
    {
        std::unique_ptr<AudioFormatReaderSource> newSource (new AudioFormatReaderSource (reader,
true));
        transportSource.setSource (newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset (newSource.release());
    }

}
void DJAudioPlayer::setGain(double gain)
{
    if(gain<0||gain>1.0)
    {
        std::cout<<"DJAudioPlayer::setGain gain should be between o and 1 "<<std::endl;
    }
    else{
        transportSource.setGain(gain);
    }
    
}
void DJAudioPlayer::setPosition(double posInSecs)
{
    
    transportSource.setPosition(posInSecs);
}
void DJAudioPlayer::setSpeed(double ratio)
{
    if(ratio<0||ratio>100.0)
    {
        std::cout<<"DJAudioPlayer::setSpeed ratio  should be between o and 100 "<<std::endl;
    }
    else{
        resampleSource.setResamplingRatio(ratio);
    }
}
void DJAudioPlayer::setPositionRelative(double pos)//to get the length of the audio file
{
    if(pos<0||pos>1.0)
    {
        std::cout<<"DJAudioPlayer::setPositionRelative pos  should be between o and 1 "<<std::endl;
    }
    else{
        double posInSecs = transportSource.getLengthInSeconds()*pos;
        setPosition( posInSecs);//setting the setPosition to the length of the audiofile 
    }
}

void DJAudioPlayer::start()
{
    transportSource.start();
}
void DJAudioPlayer::stop()
{
    transportSource.stop();
}
