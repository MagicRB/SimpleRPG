#ifndef BLOCK_H
#define BLOCK_H


class block
{
    public:
        int x;
        int y;
        bool player_collide;

        block();
        ~block();

        void render(int cy, int cx);
        void setPos(int y, int x);

    protected:



    private:
};

#endif // BLOCK_H
