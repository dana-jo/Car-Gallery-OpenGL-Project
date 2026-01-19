#define MINIAUDIO_IMPLEMENTATION
#include "AudioSystem.h"
#include <iostream>

ma_engine AudioSystem::engine;
ma_sound AudioSystem::music;
bool AudioSystem::musicInitialized = false;

void AudioSystem::init()
{
    ma_engine_init(nullptr, &engine);
}

void AudioSystem::shutdown()
{
    if (musicInitialized)
        ma_sound_uninit(&music);

    ma_engine_uninit(&engine);
}

void AudioSystem::playSound(const std::string& path)
{
    ma_engine_play_sound(&engine, path.c_str(), nullptr);
}

void AudioSystem::playMusic(const std::string& path, bool loop)
{
    if (musicInitialized)
        ma_sound_uninit(&music); // stop previous music

    if (ma_sound_init_from_file(
        &engine,
        path.c_str(),
        loop ? MA_SOUND_FLAG_LOOPING : 0,
        nullptr,
        nullptr,
        &music
    ) != MA_SUCCESS)
    {
        std::cerr << "Failed to load music: " << path << std::endl;
        return;
    }

    musicInitialized = true;
    ma_sound_start(&music);
}

void AudioSystem::stopMusic()
{
    if (musicInitialized)
        ma_sound_stop(&music);
}

