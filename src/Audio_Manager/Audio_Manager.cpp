#include "src/Audio_Manager/Audio_Manager.hpp"

AudioManager::AudioManager() {
    playerJumpSound = LoadSound("src/assets/sounds/phaserUp3.ogg");
    collectableSound = LoadSound("src/assets/sounds/powerUp9.ogg");
    
}

AudioManager::~AudioManager() {
    UnloadSound(playerJumpSound);
}

void AudioManager::PlayJumpSound() {
    SetSoundVolume(playerJumpSound, 1.0f);
    PlaySound(playerJumpSound);
}

void AudioManager::PlayCollectableSound() {
    SetSoundVolume(collectableSound, 1.0f);
    PlaySound(collectableSound);
}