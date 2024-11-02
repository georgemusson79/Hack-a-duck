#ifndef A6A7ECD0_5844_4292_8838_DBC2157FBAE5
#define A6A7ECD0_5844_4292_8838_DBC2157FBAE5
// pls dont explode SDL_Mixer <3
#include <SDL_mixer.h>

#include <iostream>
#include <thread>
class Sound {
   private:
    Mix_Chunk* snd;
    std::string sndPath;
    int chnl = -1;
    int volume = 128;

   public:
    void loadSound(std::string sndPath) {
        snd = Mix_LoadWAV(sndPath.c_str());
        this->sndPath = sndPath;
        if (!snd) std::cerr << "Unable to load sound " + sndPath << "\n"
                            << Mix_GetError();
    }

    std::string getSoundPath() {
        return this->sndPath;
    }

    Sound(std::string path, bool playImmediately = false, int loops = 0) {
        this->loadSound(path);
        if (playImmediately) this->play(loops);
    }

    void deleteSound() {
        Mix_FreeChunk(snd);
    }

    void setVolume(int volume) {
        Mix_VolumeChunk(this->snd, volume);
        this->volume = volume;
    }

    int getVolume() {
        return this->volume;
    }

    ~Sound() {
        this->deleteSound();
    }

    void play(int loops = 0) {
        this->chnl = Mix_PlayChannel(-1, this->snd, loops);
    }

    void stop() {
        if (this->chnl == -1) return;
        Mix_HaltChannel(this->chnl);
        this->chnl = -1;
    }
};

#endif
