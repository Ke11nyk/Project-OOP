#pragma once
#include <array>
#include <SFML/Audio.hpp>
#include "AssetManager.h"

class GameSound;

class SoundState {
protected:
    GameSound* context_;

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

class GameSound {
private:
    
    SoundState* state_;

public:
    std::array<sf::Sound, 6> GSound;
    GameSound();
    ~GameSound();

    void play(int index);
    void stop(int index);
    void onOffSound(bool onOff);
    void allStop();

    void setState(SoundState* state);
};

class PlayingState : public SoundState {
public:
    void play(int index) override;
    void stop(int index) override;
    void onOffSound(bool onOff) override;
    void allStop() override;
};

class StoppedState : public SoundState {
public:
    void play(int index) override;
    void stop(int index) override;
    void onOffSound(bool onOff) override;
    void allStop() override;
};