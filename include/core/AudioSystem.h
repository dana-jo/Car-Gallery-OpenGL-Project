#pragma once
#include "miniaudio.h"
#include <string>
#include <unordered_map>

class AudioSystem
{
public:
    static void init();
    static void shutdown();

    // Basic sound
    static void playSound(const std::string& path);

    // Music (looping)
    static void playMusic(const std::string& path, bool loop = true);

    // Control music
    static void stopMusic();
    //static void pauseMusic();
    //static void resumeMusic();

private:
    static ma_engine engine;

    // Persistent music sound
    static ma_sound music;
    static bool musicInitialized;
};
