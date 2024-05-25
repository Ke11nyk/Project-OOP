#include "..//headers/GameSound.h"

GameSound::GameSound() {
    std::array<std::string, 6> namefilebuf{ "D:/Uni materials/2 course/OOP/Project OOP/source/sounds/menu.mp3", 
                                            "D:/Uni materials/2 course/OOP/Project OOP/source/sounds/submenu.mp3",
                                            "D:/Uni materials/2 course/OOP/Project OOP/source/sounds/game.mp3", 
                                            "D:/Uni materials/2 course/OOP/Project OOP/source/sounds/z.wav",
                                            "D:/Uni materials/2 course/OOP/Project OOP/source/sounds/svs.wav", 
                                            "D:/Uni materials/2 course/OOP/Project OOP/source/sounds/sh.wav" };

    for (int i = 0; i < 6; i++) {
        GSound[i].setBuffer(AssetManager::GetSoundBuffer(namefilebuf[i]));
        if (i < 3) GSound[i].setLoop(true);
    }

    state_ = new StoppedState();
    state_->setContext(this);
}

GameSound::~GameSound() {
    delete state_;
}

/**
* \brief The method that play sound due to state
*/
void GameSound::play(int index) {
    state_->play(index);
}

/**
* \brief The method that stops sound due to state
*/
void GameSound::stop(int index) {
    state_->stop(index);
}

/**
* \brief The method that changes state of the sound
*/
void GameSound::onOffSound(bool onOff) {
    state_->onOffSound(onOff);
}

/**
* \brief The method that stops all sounds
*/
void GameSound::allStop() {
    state_->allStop();
}

/**
* \brief The method that sets state of the sound
*/
void GameSound::setState(SoundState* state) {
    delete state_;
    state_ = state;
    state_->setContext(this);
}

/**
* \brief The method that plays sound
*/
void PlayingState::play(int index) {
    if (context_->GSound[index].getStatus() == sf::SoundSource::Status::Stopped) {
        context_->GSound[index].play();
    }
}

/**
* \brief The method that stops sound
*/
void PlayingState::stop(int index) {
    if (context_->GSound[index].getStatus() == sf::SoundSource::Status::Playing) {
        context_->GSound[index].stop();
    }
}

/**
* \brief No action needed for PlayingState
*/
void PlayingState::onOffSound(bool onOff) {}

/**
* \brief The method that stops all sounds
*/
void PlayingState::allStop() {
    for (int i = 0; i < context_->GSound.size(); i++) {
        if (context_->GSound[i].getStatus() == sf::SoundSource::Status::Playing) {
            context_->GSound[i].stop();
        }
    }
}

/**
* \brief The method that plays sound
*/
void StoppedState::play(int index) {
    context_->GSound[index].play();
    context_->setState(new PlayingState());
}

/**
* \brief No action needed for StoppedState
*/
void StoppedState::stop(int index) {}

/**
* \brief The method that changes state of the sound to playing
*/
void StoppedState::onOffSound(bool onOff) {
    if (onOff) {
        context_->setState(new PlayingState());
    }
}

/**
* \brief No action needed for StoppedState
*/
void StoppedState::allStop() {}