#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

class character
{
    public:

        int lx = 0;
        int ly = 0;
        int x = 0;
        int y = 0;

        bool isDead();
        float getHp();
        float getTotalHp();
        std::string getName();
        int short getLvl();

        void setHp(float hpr);
        void setTotalHp(float totalhpr);
        void setName(std::string namer);
        void setLvl(int short levelr);

        void addHp(float hpr);
        void addTotalHp(float totalhpr);
        void addLvl(int short levelr);

        void rmHp(float hpr);
        void rmTotalHp(float totalhpr);
        void rmLvl(int short levelr);

        void render(int cy, int cx);
        void erasel(int cy, int cx);

        void chmove(int x, int y);
        bool checkColl(int y, int x, int cy, int cx);

        character();
        ~character();

    protected:

        std::string name = "";
        float hp = 100;
        float totalhp = 100;
        int short level = 1;

    private:
};

#endif // CHARACTER_H
