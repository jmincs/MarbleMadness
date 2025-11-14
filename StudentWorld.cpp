#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <vector>
#include <sstream>  // defines the type std::ostringstream

using namespace std;

GameWorld* createStudentWorld(string assetPath) 
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

Actor* StudentWorld::findGoodie(Actor* c, int x, int y){
    vector<Actor*>:: iterator it;
    for(int i = 0; i < v.size(); i++){
        it = v.begin() + i;
        if((*it)->getX() == x && (*it)->getY() == y && (*it)->obtainable()){
            return *it;
        }
    }
    return nullptr;
}


Actor* StudentWorld::findactor(Actor* c, int x, int y){
    vector<Actor*>:: iterator it;
    for(int i = 0; i < v.size(); i++){
        it = v.begin() + i;
        if((*it)->getX() == x && (*it)->getY() == y && (*it) != c){
            return *it;
        }
    }
    return nullptr;
}
Actor* StudentWorld::findThieves(Actor* c, int x, int y){
    vector<Actor*>:: iterator it;
    for(int i = 0; i < v.size(); i++){
        it = v.begin() + i;
        // skip actors that cannot steal
        if (!(*it)->cansteal()) continue;
        if((*it)->getX() == x && (*it)->getY() == y && (*it) != c){
            return *it;
        }
    }
    return nullptr;
}


bool StudentWorld::hasplayer(Actor* b, int x, int y){
    if(a->getX() == x && a->getY() == y){
        return true;
    }
    return false;
}

bool StudentWorld::hasactor(Actor* a, int x, int y){
    vector<Actor*>:: iterator it;
    for(int i = 0; i < v.size(); i++){
        it = v.begin() + i;
        if((*it)->getX() == x && (*it)->getY() == y && (*it) != a){
            return true;
        }
    }
    return false;
}


bool StudentWorld::pcollision(Actor* b, int x, int y){
    vector<Actor*>:: iterator it;
    for(int i = 0; i < v.size(); i++){
        it = v.begin() + i;
        if((*it)->getX() == x && (*it)->getY() == y && (*it) != a){
            if((*it)->isenemy() || (*it)->ispushable() || (*it)->blocksstuff()){
                return true;
            }
            else if(hasplayer(b, x, y)){
                return true;
            }        }
    }
    return false;
}

Actor* StudentWorld::pactor(Actor* c, int x, int y){
    vector<Actor*>:: iterator it;
    for(int i = 0; i < v.size(); i++){
        it = v.begin() + i;
        if((*it)->getX() == x && (*it)->getY() == y && (*it) != a){
            if((*it)->isenemy() || (*it)->ispushable() || (*it)->blocksstuff()){
                return *it;
            }
            else if(hasplayer(c, x, y)){
                return *it;
            }
        }
    }
    return 0;
}

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath), level(false), nCrystals(0), bonus(1000)
{
    a = nullptr;
}

void StudentWorld::addactor(Actor* a){
    v.push_back(a);
}

void StudentWorld::deleteactor(Actor* a){
    vector<Actor*>:: iterator it;
    for(int i = 0; i < v.size();){
        it = v.begin()+i;
        if(*it == a){
            delete a;
            v.erase(it);
        }
        else{
            i++;
        }
    }
}

int StudentWorld::init()
{
    newlevel();
    bonus = 1000;
    updatecrystals(-numcrystals());
    int n = getLevel();
    if(n == 100){
        return GWSTATUS_PLAYER_WON;
    }
    ostringstream oss;
    if(n < 10){
        oss << "level0" << n << ".txt";
    }
    else{
        oss << "level" << n << ".txt";
    }
    string s = oss.str();
    Level lev(assetPath());
    Level::LoadResult result = lev.loadLevel(s);
    if(result == Level::load_fail_file_not_found){
        return GWSTATUS_PLAYER_WON;
    }
    else if(result == Level::load_fail_bad_format){
        return GWSTATUS_LEVEL_ERROR;
    }
    else if(result == Level::load_success){
        for(int i = 0; i <= 14; i++){
            for(int j = 0; j <= 14; j++){
                Level::MazeEntry item = lev.getContentsOf(i,j);
                if(item == Level::player){
                    a = new Avatar(this, IID_PLAYER, i, j, 0);
                   /* Actor *a = new Avatar(this, IID_PLAYER, y, x, 0);
                    v.push_back(a);*/
                }
                if(item == Level::wall){
                    Actor* w = new Wall(this, IID_WALL, i, j, -1);
                    v.push_back(w);
                }
                if(item == Level::marble){
                    v.push_back(new Marble(this, IID_MARBLE, i, j, -1));
                }
                if(item == Level::pit){
                    v.push_back(new Pit(this, IID_PIT, i, j, -1));
                }
                if(item == Level::crystal){
                    v.push_back(new Crystal(this, IID_CRYSTAL, i, j, -1));
                    updatecrystals(1);
                }
                if(item == Level::exit){
                    v.push_back(new Exit(this, IID_EXIT, i, j, -1));
                }
                if(item == Level::extra_life){
                    v.push_back(new ExtraLifeGoodie(this, IID_EXTRA_LIFE, i, j, -1));
                }
                if(item == Level::restore_health){
                    v.push_back(new RestoreHealthGoodie(this, IID_RESTORE_HEALTH, i, j, -1));
                }
                if(item == Level::ammo){
                    v.push_back(new AmmoGoodie(this, IID_AMMO, i, j, -1));
                }
                if(item == Level::horiz_ragebot){
                    v.push_back(new HorizontalRageBot(this, IID_RAGEBOT, i, j, 0));
                }
                if(item == Level::vert_ragebot){
                    v.push_back(new VerticalRageBot(this, IID_RAGEBOT, i, j, 270));
                }
                if(item == Level::thiefbot_factory){
                    v.push_back(new ThiefBotFactory(this, false, IID_ROBOT_FACTORY, i, j, -1));
                }
                if(item == Level::mean_thiefbot_factory){
                    v.push_back(new ThiefBotFactory(this, true, IID_ROBOT_FACTORY, i, j, -1));
                }
                
            }
        }
        }
    return GWSTATUS_CONTINUE_GAME;

}

int StudentWorld::move()
{
    setdisplaytext();
    // This code is here merely to allow the game to build, run, and terminate after typing q
    a->doSomething();
    if(bonus != 0){
        bonus--;
    }
    vector<Actor*>:: iterator it;
    int size = v.size();
    for(int i = 0; i != size; i++){
        it = v.begin() + i;
        if((*it)->alive() == true){
            (*it)->doSomething();
        }
    }
    removedead();
    if(a->gethealth() <= 0){
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    else if(level){
        increaseScore(bonus);
        return GWSTATUS_FINISHED_LEVEL;
    }
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::removedead(){
    vector<Actor*>:: iterator it;
    for(int i = 0; i < v.size();){
        it = v.begin() + i;
        if((*it)->alive() == false){
            delete *it;
            v.erase(it);
        }
        else{
            i++;
        }
    }
}

void StudentWorld::cleanUp()
{
    if (v.size() == 0) return;
    delete a;
    for(Actor* ab:v){
        delete ab;
    }
    v.clear();
}



void StudentWorld::complete(){
    vector<Actor*>:: iterator it;
    for(int i = 0; i < v.size(); i++){
        it = v.begin() + i;
        if((*it)->portal()){
            (*it)->setVisible(true);
        }
    }
}

void StudentWorld::setdisplaytext(){
    int score = getScore();
    int level = getLevel();
    int score1 = score;
    ostringstream os;
    int digits = 0;
    while(score1 != 0){
        score1 = score1/10;
        digits++;
    }
    os << "Score: ";
    if(score == 0){
        os << "000000";
    }
    else{
        for(int i = digits; i < 7; i++){
            os << "0";
        }
    }
    os << score;
    if(level < 10){
        os << "  Level: 0" << level;
    }
    else{
        os << "  Level: " << level;
    }
    if(getLives() < 10){
        os << "  Lives:  " << getLives();
    }
    else{
        os << "  Lives: " << getLives();
    }
    if(a->gethealth() == 20){
        os << "  Health: " << a->gethealth()*10/2 << "%";
    }
    else{
        os << "  Health:  " << a->gethealth()*10/2 << "%";
    }
    if(a->getpeas() > 10){
        os << "  Ammo:  " << a->getpeas();
    }
    else{
        os << "  Ammo:   " << a->getpeas();
    }
    int bonus1 = bonus;
    digits = 0;
    while(bonus1 != 0){
        bonus1 = bonus1/10;
        digits++;
    }
    os << "  Bonus: ";
    if(digits == 4){
        os << bonus;
    }
    else if(digits == 3){
        os << " " << bonus;
    }
    else if(digits == 2){
        os << "  " << bonus;
    }
    else if(digits == 1){
        os << "   " << bonus;
    }
    else if(digits == 0){
        os << "   " << "0";
    }
    string s = os.str();

    setGameStatText(s);
}

void StudentWorld::playerdamage(){
    a->sethealth(gethealth() - 2);
    if(a->gethealth() != 0){
        playSound(SOUND_PLAYER_IMPACT);
    }
    else{
        playSound(SOUND_PLAYER_DIE);
        a->die();
    }
}
