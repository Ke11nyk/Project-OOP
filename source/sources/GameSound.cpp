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

void GameSound::play(int index) {
    state_->play(index);
}

void GameSound::stop(int index) {
    state_->stop(index);
}

void GameSound::onOffSound(bool onOff) {
    state_->onOffSound(onOff);
}

void GameSound::allStop() {
    state_->allStop();
}

void GameSound::setState(SoundState* state) {
    delete state_;
    state_ = state;
    state_->setContext(this);
}

void PlayingState::play(int index) {
    if (context_->GSound[index].getStatus() == sf::SoundSource::Status::Stopped) {
        context_->GSound[index].play();
    }
}

void PlayingState::stop(int index) {
    if (context_->GSound[index].getStatus() == sf::SoundSource::Status::Playing) {
        context_->GSound[index].stop();
    }
}

void PlayingState::onOffSound(bool onOff) {
    // No action needed for PlayingState
}

void PlayingState::allStop() {
    for (int i = 0; i < context_->GSound.size(); i++) {
        if (context_->GSound[i].getStatus() == sf::SoundSource::Status::Playing) {
            context_->GSound[i].stop();
        }
    }
}

void StoppedState::play(int index) {
    context_->GSound[index].play();
    context_->setState(new PlayingState());
}

void StoppedState::stop(int index) {
    // No action needed for StoppedState
}

void StoppedState::onOffSound(bool onOff) {
    if (onOff) {
        context_->setState(new PlayingState());
    }
}

void StoppedState::allStop() {
    // No action needed for StoppedState
}