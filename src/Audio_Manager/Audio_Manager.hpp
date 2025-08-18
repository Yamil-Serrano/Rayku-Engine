#pragma once
#include "raylib.h"

class AudioManager {
public:
    Sound playerJumpSound;  
    Sound collectableSound;
    
    AudioManager();   
    ~AudioManager();  
    
    void PlayJumpSound(); 
    void PlayCollectableSound();
};