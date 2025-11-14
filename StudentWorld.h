#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include "Actor.h"
#include <vector>
#include <string>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
using namespace std;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    void removedead();
    void setdisplaytext();
    int numcrystals(){ return nCrystals;}
    void playerdamage();
    bool completion(){ return level; }
    void setdone(){ level = true; }
    void newlevel() { level = false; }
    void updatepeas(int num){ a->setpeas(num);}
    int getpeas(){ return a->getpeas();}
    bool pcollision(Actor* b, int x, int y);
    Actor* pactor(Actor* c, int x, int y);
    void updatecrystals(int num){ nCrystals = nCrystals + num; }
    void updatehealth(int num){ a->sethealth(num);}
    int gethealth(){return a->gethealth();}
    void complete();
    void addactor(Actor *a);
    void deleteactor(Actor *a);
    bool hasactor(Actor* a, int x, int y);
    bool hasplayer(Actor* b, int x, int y);
    Actor* findactor(Actor* c, int x, int y);
    Actor* findThieves(Actor* c, int x, int y);
    Actor* findGoodie(Actor* c, int x, int y);

private:
    int bonus;
    bool level;
    int nCrystals;
    Avatar* a;
    vector<Actor*> v;
};

#endif // STUDENTWORLD_H_
