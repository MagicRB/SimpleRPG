#ifndef PLAYER_H
#define PLAYER_H

#include <character.h>


class player : public character
{
    public:

        player();
        ~player();

    protected:

        int short reqxp = 100;
        int short xp = 0;

    private:
};

#endif // PLAYER_H
