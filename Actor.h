#ifndef ACTOR_H_
#define ACTOR_H_

#include <random>
#include "GraphObject.h"

class StudentWorld;
class Actor: public GraphObject
{
public:
    Actor(StudentWorld* world, int imageID, int startX, int startY, int dir): GraphObject(imageID, startX, startY, dir), m_world(world), life(true), m_health(0){
    }
    virtual void doSomething();
    virtual void back(){}
    virtual void steal(){
    }
    virtual void stolen(){}
    bool fire();
    bool obstacle(int x, int y);
    virtual bool pickup(){
        return true;
    };
    bool alive(){
        return life;
    }
    void die(){
        life = false;
    }
    virtual bool blocksstuff(){
        return false;
    }
    virtual bool isstolen(){
        return false;
    }
    virtual bool fillable(){
        return false;
    }
    virtual bool ispushable(){
        return false;
    }
    virtual bool isprojectile(){
        return false;
    }
    virtual bool obtainable(){
        return false;
    }
    virtual bool wincon(){
        return false;
    }
    virtual bool cansteal(){
        return false;
    }
    virtual bool portal(){
        return false;
    }
    virtual bool isenemy(){
        return false;
    }
    bool obstruction(int x, int y);
    int gethealth(){
        return m_health;
    }
    void setpeas(int peas){
        m_peas = peas;
    }
    virtual void damage(){
        sethealth(gethealth() - 2);
    }
    int getpeas(){
        return m_peas;
    }
    void sethealth(int num){
        m_health = num;
    }
    bool isValidPos(int x, int y);
    StudentWorld* getWorld(){
        return m_world;
    }
private:
    StudentWorld* m_world;
    bool life;
    int m_health;
    int m_peas;
};
class Avatar: public Actor
{
public:
    Avatar(StudentWorld* a, int imageID, int startX, int startY, int dir): Actor(a, IID_PLAYER, startX, startY, 0){
        setpeas(20);
        sethealth(20);
        setVisible(true);
    }
    void damage();
private:
};
class Wall: public Actor
{
public:
    Wall(StudentWorld* a, int imageID, int startX, int startY, int dir): Actor(a, imageID, startX, startY, dir){
        setVisible(true);
    }
    bool blocksstuff(){
        return true;
    }
    void doSomething();
};
class Pea: public Actor
{
public:
    Pea(StudentWorld* a, int imageID, int startX, int startY, int dir): Actor(a, imageID, startX, startY, dir), m_first(1){
        setVisible(true);
    }
    bool isprojectile(){
        return true;
    }
    void change(){
        m_first = 0;
    }
    bool isfirst(){
        if(m_first == 0){
            return false;
        }
        return true;
    }
    void doSomething();
private:
    int m_first;
};
class Marble: public Actor
{
public:
    Marble(StudentWorld* a, int imageID, int startX, int startY, int dir): Actor(a, imageID, startX, startY, dir){
        sethealth(10);
        setVisible(true);
    }
    bool ispushable(){
        return true;
    }
    void doSomething();
    void peaCollision();
    void push();
};
class Exit: public Actor
{
public:
    Exit(StudentWorld* a, int imageID, int startX, int startY, int dir): Actor(a, imageID, startX, startY, dir){
        setVisible(false);
    }
    bool portal(){
        return true;
    }
    void doSomething();
};
class Pit: public Actor
{
public:
    Pit(StudentWorld* a, int imageID, int startX, int startY, int dir): Actor(a, imageID, startX, startY, dir){
        setVisible(true);
    }
    void doSomething();
    bool fillable(){
        return true;
    }
};
class Crystal: public Actor
{
public:
    Crystal(StudentWorld* a, int imageID, int startX, int startY, int dir): Actor(a, imageID, startX, startY, dir){
        setVisible(true);
    }
    void doSomething();
    bool wincon(){
        return true;
    }
    
};
class Goodie: public Actor{
public:
    Goodie(StudentWorld* a, int imageID, int startX, int startY, int dir): Actor(a, imageID, startX, startY, dir){
        setVisible(true);
        m_stolen = false;
    }
    bool obtainable(){
        return true;
    }
    void stolen(){
        m_stolen = true;
    }
    void back(){
        m_stolen = false;
    }
    bool isstolen(){
        return m_stolen;
    }
private:
    bool m_stolen;
};
class ExtraLifeGoodie: public Goodie
{
public:
    ExtraLifeGoodie(StudentWorld* a, int imageID, int startX, int startY, int dir): Goodie(a, imageID, startX, startY, dir){
    }
    void doSomething();
};
class RestoreHealthGoodie: public Goodie
{
public:
    RestoreHealthGoodie(StudentWorld* a, int imageID, int startX, int startY, int dir): Goodie(a, imageID, startX, startY, dir){
    }
    void doSomething();
};
class AmmoGoodie: public Goodie
{
public:
    AmmoGoodie(StudentWorld* a, int imageID, int startX, int startY, int dir): Goodie(a, imageID, startX, startY, dir){
    }
    void doSomething();
};
class Robot: public Actor
{
public:
    Robot(StudentWorld* a, int imageID, int startX, int startY, int dir): Actor(a, imageID, startX, startY, dir), m_ticks(1){
        setVisible(true);
        
    }
    bool isenemy(){
        return true;
    }
    void updateticks(){
        m_ticks++;
    }
    int trackticks(){
        return m_ticks;
    }
    int getticks();
private:
    int m_ticks;
};
class RageBot: public Robot
{
public:
    RageBot(StudentWorld* a, int imageID, int startX, int startY, int dir): Robot(a, imageID, startX, startY, dir){
        sethealth(10);
    }
    void damage();
    void doSomething();
};
class HorizontalRageBot: public RageBot
{
public:
    HorizontalRageBot(StudentWorld* a, int imageID, int startX, int startY, int dir): RageBot(a, imageID, startX, startY, dir){
    }    
};
class VerticalRageBot: public RageBot
{
public:
    VerticalRageBot(StudentWorld* a, int imageID, int startX, int startY, int dir): RageBot(a, imageID, startX, startY, dir){
    }
};
class ThiefBot: public Robot
{
public:
    ThiefBot(StudentWorld* a, int imageID, int startX, int startY, int dir): Robot(a, imageID, startX, startY, dir), m_available(true), m_counter(0){
        sethealth(5);
        dbt = (rand()%6)+1;
    }
    void damage();
    void doSomething();
    void setptr(Actor* a){
        g = a;
    }
    bool cansteal(){
        return true;
    }
    bool pickup(){
        return m_available;
    }
    void steal(){
        m_available = false;
    }
    bool invector(std::vector<int> c, int n);
    int randdirection(std::vector<int> c);

    int getdbt(){
        return dbt;
    }
    void incdbt(){
        dbt++;
    }
    void setdbt(int n){
        dbt = n;
    }
    int getcounter(){
        return m_counter;
    }
    void setcounter(int n){
        m_counter = n;
    }
    void inccount(){
        m_counter++;
    }
    Actor* getptr(){
        return g;
    }
    
private:
    Actor* g;
    int dbt;
    bool m_available;
    int m_counter;
};
class MeanThiefBot: public ThiefBot
{
public:
    MeanThiefBot(StudentWorld* a, int imageID, int startX, int startY, int dir): ThiefBot(a, imageID, startX, startY, dir){
        sethealth(8);
    }
    bool cansteal(){
        return true;
    }
    void damage();
    void doSomething();
};
class ThiefBotFactory: public Actor
{
public:
    ThiefBotFactory(StudentWorld* a, bool ismean, int imageID, int startX, int startY, int dir): Actor(a, imageID, startX, startY, dir){
        setVisible(true);
        mean = ismean;
    }
    void doSomething();
    bool blocksstuff(){
        return true;
    }
private:
    bool mean;
};

#endif // ACTOR_H_
