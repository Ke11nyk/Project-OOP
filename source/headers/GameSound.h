#pragma once
#include <array>
#include <SFML/Audio.hpp>
#include "AssetManager.h"

class GameSound;

/**
* \brief This is the class to change game sound state
*/
class SoundState {
protected:
    GameSound* context_; ///< Game sound whose state will change

public:
    virtual ~SoundState() {}

    void setContext(GameSound* context) {
        context_ = context;
    }

    virtual void play(int index) = 0;
    virtual void stop(int index) = 0;
    virtual void onOffSound(bool onOff) = 0;
    virtual void allStop() = 0;
};

/**
* \brief This is the class to control game sound
*/
class GameSound {
private:
    
    SoundState* state_; ///< State of the game sound

public:
    std::array<sf::Sound, 6> GSound; ///< Array with all sounds
    GameSound();
    ~GameSound();

    void play(int index);
    void stop(int index);
    void onOffSound(bool onOff);
    void allStop();

    void setState(SoundState* state);
};

/**
* \brief State in which sound could be played
*/
class PlayingState : public SoundState {
public:
    void play(int index) override;
    void stop(int index) override;
    void onOffSound(bool onOff) override;
    void allStop() override;
};

/**
* \brief State in which sound couldn't be played
*/
class StoppedState : public SoundState {
public:
    void play(int index) override;
    void stop(int index) override;
    void onOffSound(bool onOff) override;
    void allStop() override;
};