#include "character.h"

character::character()
{
    //ctor
}

character::~character()
{
    //dtor
}

bool character::isDead()
{
    if (hp <= 0)
    {
        return true;
    }
    return false;
}

float character::getHp()
{
    return hp;
}

float character::getTotalHp()
{
    return totalhp;
}

std::string character::getName()
{
    return name;
}

int short character::getLvl()
{
    return level;
}

void character::setHp(float hpr)
{
    hp = hpr;
}

void character::setTotalHp(float totalhpr)
{
    totalhp = totalhpr;
}

void character::setName(std::string namer)
{
     name = namer;
}

void character::setLvl(int short levelr)
{
    level = levelr;
}

void character::addHp(float hpr)
{
    hp += hpr;
}

void character::addTotalHp(float totalhpr)
{
    totalhp += totalhpr;
}

void character::addLvl(int short levelr)
{
    level += levelr;
}

void character::rmHp(float hpr)
{
    hp -= hpr;
}

void character::rmTotalHp(float totalhpr)
{
    totalhp -= totalhpr;
}

void character::rmLvl(int short levelr)
{
    level -= levelr;
}
