#ifdef linux
#pragma once
#include <vector>
#include <SDL_mixer.h>

class SDL2Music
{
public:
    SDL2Music();

    void addMusic(const char* path);
    void playMusic(const int which);
    void Play_Pause();

private:
    std::vector<Mix_Music*> m_MusicBank;
    bool m_Paused = false;
    bool m_Playing = false;
};
#endif
