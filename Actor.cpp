#include "Actor.h"
#include "StudentWorld.h"
#include <vector>
#include <list>
#include <random>
#include <string>

bool Actor::isValidPos(int x, int y){
    if(x < 0 || x > 14){
        return false;
    }
    if(y < 0 || y > 14){
        return false;
    }
    if(getWorld()->hasactor(this, x,y) == true){
        Actor *a;
        a = getWorld()->findactor(this,x,y);
        if(a->blocksstuff() == true){
            return false;
        }
    }
    return true;
}

void Actor::doSomething(){
    int val;
    if(getWorld()->getKey(val) == true){
        if(val == KEY_PRESS_SPACE){
            if(getpeas() > 0){
                setpeas(getpeas()-1);
                if(getDirection() == left){
                    getWorld()->addactor(new Pea(getWorld(), IID_PEA, getX()-1, getY(), getDirection()));
                    getWorld()->playSound(SOUND_PLAYER_FIRE);
                }
                else if(getDirection() == right){
                    getWorld()->addactor(new Pea(getWorld(), IID_PEA, getX()+1, getY(), getDirection()));
                    getWorld()->playSound(SOUND_PLAYER_FIRE);
                }
                else if(getDirection() == up){
                    getWorld()->addactor(new Pea(getWorld(), IID_PEA, getX(), getY()+1, getDirection()));
                    getWorld()->playSound(SOUND_PLAYER_FIRE);
                }
                else if(getDirection() == down){
                    getWorld()->addactor(new Pea(getWorld(), IID_PEA, getX(), getY()-1, getDirection()));
                    getWorld()->playSound(SOUND_PLAYER_FIRE);
                    
                }
            }
        }

        else if(val == KEY_PRESS_LEFT){
            setDirection(left);
            // if only valid pos, consider move
            if (!isValidPos(getX()-1, getY())) return;
            if(getWorld()->hasactor(this, getX()-1, getY())){
                Actor* a;
                a = getWorld()->findactor(this, getX()-1, getY());
                if((a->ispushable() == true)){
                    if(getWorld()->hasactor(a, a->getX()-1, a->getY()) == true){
                        Actor *b = getWorld()->findactor(a, a->getX()-1, a->getY());
                        if(b->fillable() == true){
                            a->moveTo(a->getX()-1, a->getY());
                        }
                        else{
                            return;
                        }
                    }
                    else{
                        a->moveTo(a->getX()-1, a->getY());
                    }
                }
                else if(a->wincon() == true || a->portal() == true || a->obtainable() == true){
                }
                else{
                    return;
                }
            }
            moveTo(getX()-1, getY());
            
        }
        else if(val == KEY_PRESS_DOWN){
            setDirection(down);
            if(!isValidPos(getX(), getY()-1)) return;
            if(getWorld()->hasactor(this, getX(), getY()-1)){
                Actor* a;
                a = getWorld()->findactor(this, getX(), getY()-1);
                if((a->ispushable() == true && a->isValidPos(a->getX(), a->getY()-1))){
                    if(getWorld()->hasactor(a, a->getX(), a->getY()-1) == true){
                        Actor *b = getWorld()->findactor(a, a->getX(), a->getY()-1);
                        if(b->fillable() == true){
                            a->moveTo(a->getX(), a->getY()-1);
                        }
                        else{
                            return;
                        }
                    }
                    else{
                        a->moveTo(a->getX(), a->getY()-1);
                    }
                }
                else if(a->wincon() == true || a->portal() == true || a->obtainable() == true){
                }
                else{
                    return;
                }
            }
            moveTo(getX(), getY()-1);
        }
        else if(val == KEY_PRESS_RIGHT){
            setDirection(right);
            if(!isValidPos(getX()+1, getY())) return;
            if(getWorld()->hasactor(this, getX()+1, getY())){
                Actor* a;
                a = getWorld()->findactor(this, getX()+1, getY());
                if((a->ispushable() == true && a->isValidPos(a->getX()+1, a->getY()))){
                    if(getWorld()->hasactor(a, a->getX()+1, a->getY()) == true){
                        Actor *b = getWorld()->findactor(a, a->getX()+1, a->getY());
                        if(b->fillable() == true){
                            a->moveTo(a->getX()+1, a->getY());
                        }
                        else{
                            return;
                        }
                    }

                    else{
                        a->moveTo(a->getX()+1, a->getY());
                    }
                }
                else if(a->wincon() == true || a->portal() == true || a->obtainable() == true){
                }
                else{
                    return;
                }
            }
            moveTo(getX()+1, getY());
        }
        else if(val == KEY_PRESS_UP){
            setDirection(up);
            if(!isValidPos(getX(), getY()+1)) return;
            if(getWorld()->hasactor(this, getX(), getY()+1)){
                Actor* a;
                a = getWorld()->findactor(this, getX(), getY()+1);
                if((a->ispushable() == true && a->isValidPos(a->getX(), a->getY()+1))){
                    if(getWorld()->hasactor(a, a->getX(), a->getY()+1) == true){
                        Actor *b = getWorld()->findactor(a, a->getX(), a->getY()+1);
                        if(b->fillable() == true){
                            a->moveTo(a->getX(), a->getY()+1);
                        }
                        else{
                            return;
                        }
                    }
                    else{
                        a->moveTo(a->getX(), a->getY()+1);
                    }
                }
                else if(a->wincon() == true || a->portal() == true || a->obtainable() == true){
                }
                else{
                    return;
                }
            }
            moveTo(getX(), getY()+1);
        }
        else if(val == KEY_PRESS_ESCAPE){
            sethealth(-1);
            getWorld()->playSound(SOUND_PLAYER_DIE);
            return;
        }
        
    }
}

void Avatar::damage(){
    getWorld()->playerdamage();
}

void Wall::doSomething(){
    return;
}

void Marble::doSomething(){
    return;
}

void Marble::peaCollision(){
    sethealth(gethealth() - 2);
    if(gethealth() == 0){
        die();
    }
}


void Pea::doSomething(){
    if(alive() == false){
        return;
    }
    if(isfirst()){
        change();
        return;
    }
    Actor *a;
    if(getWorld()->pcollision(this, getX(), getY()) || getWorld()->hasplayer(this, getX(), getY())){
        if(getWorld()->hasplayer(this, getX(), getY())){
            getWorld()->playerdamage();
            die();
        }
        else{
            a = getWorld()->pactor(this, getX(), getY());
            if(a->ispushable() || a->isenemy()){
                a->damage();
                if(a->gethealth() <= 0){
                    a->die();
                }
                die();
            }
            else if(a->blocksstuff()){
                die();
            }
        }
    }

    if(alive()){
        if(getDirection() == 0){
            moveTo(getX()+1, getY());
        }
        else if(getDirection() == 90){
            moveTo(getX(), getY()+1);
        }
        else if(getDirection() == 180){
            moveTo(getX()-1, getY());
        }
        else if(getDirection() == 270){
            moveTo(getX(), getY()-1);
        }
    Actor *b;
    if(getWorld()->pcollision(this, getX(), getY()) == true || getWorld()->hasplayer(this, getX(), getY())){
        if(getWorld()->hasplayer(this, getX(), getY())){
            getWorld()->playerdamage();
            die();
        }
        else{
            b = getWorld()->pactor(this, getX(), getY());
            if(b->ispushable() || b->isenemy()){
                b->damage();
                if(b->gethealth() <= 0){
                    b->die();
                }
                die();
            }
            else if(b->blocksstuff()){
                die();
            }
        }
    }

    }
       
    
}

void Pit::doSomething(){
    if(alive() == false){
        return;
    }
    Actor *a;
    if(getWorld()->hasactor(this, getX(), getY())){
        a = getWorld()->findactor(this, getX(), getY());
        if(a->ispushable()){
            die();
            a->die();
            getWorld()->deleteactor(a);
            getWorld()->deleteactor(this);

        }
    }
}



void Crystal::doSomething(){
    if(alive() == false){
        return;
    }
    if(getWorld()->hasplayer(this, getX(), getY())){
            getWorld()->increaseScore(50);
            die();
            getWorld()->playSound(SOUND_GOT_GOODIE);
            getWorld()->updatecrystals(-1);
    }
    
    
}

void Exit::doSomething(){
    if(getWorld()->numcrystals() == 0){
        getWorld()->complete();
    }
    if(getWorld()->hasplayer(this, getX(), getY()) && isVisible() == true){
        getWorld()->playSound(SOUND_FINISHED_LEVEL);
        getWorld()->increaseScore(2000);
        getWorld()->setdone();
    }
}

void ExtraLifeGoodie::doSomething(){
    if(alive() == false){
        return;
    }
    if(getWorld()->hasplayer(this, getX(), getY()) == true && !isstolen()){
        getWorld()->increaseScore(1000);
        die();
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->incLives();
    }
}

void RestoreHealthGoodie::doSomething(){
    if(alive() == false){
        return;
    }
    if(getWorld()->hasplayer(this, getX(), getY()) == true && !isstolen()){
        getWorld()->increaseScore(500);
        die();
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->updatehealth(20);
    }
}

void AmmoGoodie::doSomething(){
    if(alive() == false){
        return;
    }
    if(getWorld()->hasplayer(this, getX(), getY()) == true && !isstolen()){
        getWorld()->increaseScore(100);
        die();
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->updatepeas(getWorld()->getpeas()+20);
    }

}

void RageBot::damage(){
    sethealth(gethealth() - 2);
    if(gethealth() > 0){
        getWorld()->playSound(SOUND_ROBOT_IMPACT);
    }
    else{
        die();
        getWorld()->playSound(SOUND_ROBOT_DIE);
        getWorld()->increaseScore(100);
    }
}

int Robot::getticks(){
    int ticks = (28 - getWorld()->getLevel())/4;
    if(ticks < 3){
        ticks = 3;
    }
    return ticks;
}



void RageBot::doSomething(){
    if(!alive()){
        return;
    }
    if(trackticks()%getticks() != 1){
        updateticks();
        return;
    }
    if(fire()){
        if(getDirection() == left){
            getWorld()->addactor(new Pea(getWorld(), IID_PEA, getX()-1, getY(), getDirection()));
            getWorld()->playSound(SOUND_ENEMY_FIRE);
        }
        else if(getDirection() == right){
            getWorld()->addactor(new Pea(getWorld(), IID_PEA, getX()+1, getY(), getDirection()));
            getWorld()->playSound(SOUND_ENEMY_FIRE);
        }
        else if(getDirection() == up){
            getWorld()->addactor(new Pea(getWorld(), IID_PEA, getX(), getY()+1, getDirection()));
            getWorld()->playSound(SOUND_ENEMY_FIRE);
        }
        else if(getDirection() == down){
            getWorld()->addactor(new Pea(getWorld(), IID_PEA, getX(), getY()-1, getDirection()));
            getWorld()->playSound(SOUND_ENEMY_FIRE);

        }
        updateticks();
        return;
    }
    updateticks();
    if(getDirection() == left){
        if(getWorld()->hasactor(this, getX()-1, getY())){
            Actor *a = getWorld()->findactor(this, getX()-1, getY());
            if(a->ispushable() || a->blocksstuff() || a->isenemy() || a->fillable()){
                setDirection(right);
                return;
            }
            else if(getWorld()->hasplayer(this, getX()-1, getY())){
                setDirection(right);
                return;
            }
        }
        moveTo(getX()-1, getY());

    }
    else if(getDirection() == right){
        if(getWorld()->hasactor(this, getX()+1, getY())){
            Actor *a = getWorld()->findactor(this, getX()+1, getY());
            if(a->ispushable() || a->blocksstuff() || a->isenemy() || a->fillable()){
                setDirection(left);
                return;
            }
            else if(getWorld()->hasplayer(this, getX()+1, getY())){
                setDirection(left);
                return;
            }
        }
        moveTo(getX()+1, getY());
    }
    else if(getDirection() == down){
        if(getWorld()->hasactor(this, getX(), getY()-1)){
            Actor *a = getWorld()->findactor(this, getX(), getY()-1);
            if(a->ispushable() || a->blocksstuff() || a->isenemy() || a->fillable()){
                setDirection(up);
                return;
            }
            else if(getWorld()->hasplayer(this, getX(), getY()-1)){
                setDirection(up);
                return;
            }
        }
        moveTo(getX(), getY()-1);
    }
    else if(getDirection() == up){
        if(getWorld()->hasactor(this, getX(), getY()+1)){
            Actor *a = getWorld()->findactor(this, getX(), getY()+1);
            if(a->ispushable() || a->blocksstuff() || a->isenemy() || a->fillable()){
                setDirection(down);
                return;
            }
            else if(getWorld()->hasplayer(this, getX(), getY()+1)){
                setDirection(down);
                return;
            }
        }
        moveTo(getX(), getY()+1);
    }
}

bool Actor::fire(){
    if(getDirection() == 0 || getDirection() == 180){
        for(int i = 0; i < VIEW_WIDTH; i++){
            if(getWorld()->hasplayer(this, i, getY()) && obstacle(i, getY())){
                return true;
            }
        }

    }
    else{
        for(int j = 0; j < VIEW_HEIGHT; j++){
            if(getWorld()->hasplayer(this, getX(), j) && obstacle(getX(), j)){
                return true;
            }
        }
    }
    return false;
}

bool Actor::obstacle(int x, int y){
    int y1;
    int y2;
    int x1;
    int x2;
    if(x == getX()){
        if(y < getY()){
            if(getDirection() == up){
                return false;
            }
            y1 = y;
            y2 = getY();
        }
        else{
            if(getDirection() == down){
                return false;
            }
            y1 = getY();
            y2 = y;
        }
        for(int i = y1; i < y2; i++){
            if(getWorld()->hasactor(this, x, i)){
                Actor* a = getWorld()->findactor(this, x, i);
                if(a->blocksstuff() || a->ispushable() || a->isenemy()){
                    return false;
                }
            }
        }
        return true;
    }
    if(x < getX()){
        if(getDirection() == right){
            return false;
        }
        x1 = x;
        x2 = getX();
    }
    else{
        if(getDirection() == left){
            return false;
        }
        x1 = getX();
        x2 = x;
    }
    for(int i = x1; i < x2; i++){
        if(getWorld()->hasactor(this, i, y)){
            Actor* a = getWorld()->findactor(this, i, y);
            if(a->blocksstuff() || a->ispushable() || a->isenemy()){
                return false;
            }
        }
    }
    return true;
}


void ThiefBot::doSomething(){
    updateticks();
    if(alive() == false){
        return;
    }
    if(trackticks()%getticks() != 1){
        return;
    }
    Actor *a;
    if(getWorld()->hasactor(this, getX(), getY())){
        a = getWorld()->findGoodie(this, getX(), getY());
        if(a != nullptr && a->obtainable() && pickup() && a->isstolen() == false){
            int steal = rand()%10+1;
            if(steal == 1){
                this->steal();
                a->stolen();
                getWorld()->playSound(SOUND_ROBOT_MUNCH);
                a->setVisible(false);
                setptr(a);
            }
        }
    }
    if(m_counter != dbt){
        if(getDirection() == left){
            if(!obstruction(getX()-1, getY())){
                moveTo(getX()-1, getY());
                m_counter++;
                return;
            }
        }
        else if(getDirection() == right){
            if(!obstruction(getX()+1, getY())){
                moveTo(getX()+1, getY());
                m_counter++;
                return;
            }
        }
        else if(getDirection() == up){
            if(!obstruction(getX(), getY()+1)){
                moveTo(getX(), getY()+1);
                m_counter++;
                return;
            }
        }
        else if(getDirection() == down){
            if(!obstruction(getX(), getY()-1)){
                moveTo(getX(), getY()-1);
                m_counter++;
                return;
            }
        }
    }
    m_counter = 0;
    vector<int> c;
    dbt = rand()%6+1;
    int randdir = (rand()%4)*90;
    c.push_back(randdir);
    if(randdir == 0){
        if(!obstruction(getX()+1, getY())){
            setDirection(right);
                return;
        }
        else{
            int n = randdirection(c);
            if(n != -1){
                setDirection(n);}
                        else{
                            setDirection(randdir);
                            return;
                        }
                    }
                    }
                else if(randdir == 90){
                    if(!obstruction(getX(), getY()+1)){
                        setDirection(up);
                        return;
                    }
                    else{
                        int n = randdirection(c);
                        if(n != -1){
                            setDirection(n);
                        }
                        else{
                            setDirection(randdir);
                            return;
                        }
                    }
                    }
                else if(randdir == 180){
                    if(!obstruction(getX()-1, getY())){
                        setDirection(left);
                        return;
                    }
                    else{
                        int n = randdirection(c);
                        if(n != -1){
                            setDirection(n);
                        }
                        else{
                            setDirection(randdir);
                            return;
                        }
                    }
                    }
                else if(randdir == 270){
                    if(!obstruction(getX(), getY()-1)){
                        setDirection(down);
                        return;
                    }
                    else{
                        int n = randdirection(c);
                        if(n != -1){
                            setDirection(n);
                        }
                        else{
                            setDirection(randdir);
                            return;
                        }
                    }
                    }
            }

bool Actor::obstruction(int x, int y){
    if(getWorld()->hasplayer(this, x, y)){
        return true;
    }
    Actor *d;
        if(getWorld()->hasactor(this, x, y)){
            d = getWorld()->findactor(this, x, y);
            if(d->blocksstuff() || d->ispushable() || d->fillable() || d->isenemy() || d->cansteal()){
                return true;
            }
            d = getWorld()->findThieves(this, x, y);
            if(d != nullptr && d->cansteal()){
                return true;
            }
        }
    return false;
}

int ThiefBot::randdirection(vector<int> c){
    bool found = false;
    while(found == false){
        if(c.size() == 4){
            break;
        }
        int randd = (rand()%4)*90;
        if(invector(c, randd) == false){
            c.push_back(randd);
            if(randd == 0){
                if(obstruction(getX() + 1, getY()) == false){
                    return randd;
                }
            }
            else if(randd == 90){
                if(obstruction(getX(), getY()+1) == false){
                    return randd;
                }
            }
            else if(randd == 180){
                if(obstruction(getX()-1, getY()) == false){
                    return randd;
                }
            }
            else if(randd == 270){
                if(obstruction(getX(), getY()-1) == false){
                    return randd;
                }
            }
        }
    }
    return -1;
}

bool ThiefBot::invector(std::vector<int> c, int n){
    vector<int>:: iterator it;
    for(int i = 0; i < c.size(); i++){
        it = c.begin() + i;
        if(*(it) == n){
            return true;
        }
    }
    return false;
}

void ThiefBot::damage(){
    sethealth(gethealth()-2);
    if(gethealth() > 0){
        getWorld()->playSound(SOUND_ROBOT_IMPACT);
    }
    else{
        int x = getX();
        int y = getY();
        die();
        getWorld()->playSound(SOUND_ROBOT_DIE);
        getWorld()->increaseScore(10);
        if(!pickup()){
            g->back();
            g->moveTo(x, y);
            g->setVisible(true);
        }
    }
}

void MeanThiefBot::damage(){
    sethealth(gethealth()-2);
    if(gethealth() > 0){
        getWorld()->playSound(SOUND_ROBOT_IMPACT);
    }
    else{
        int x = getX();
        int y = getY();
        die();
        getWorld()->playSound(SOUND_ROBOT_DIE);
        getWorld()->increaseScore(20);
        if(!pickup()){
            getptr()->back();
            getptr()->moveTo(x, y);
            getptr()->setVisible(true);
        }
    }
}



void MeanThiefBot::doSomething(){
    if(alive() == false){
        return;
    }
    if(trackticks()%getticks() != 1){
        updateticks();
        return;
    }
    if(fire()){
        if(getDirection() == left){
            getWorld()->addactor(new Pea(getWorld(), IID_PEA, getX()-1, getY(), getDirection()));
            getWorld()->playSound(SOUND_ENEMY_FIRE);
        }
        else if(getDirection() == right){
            getWorld()->addactor(new Pea(getWorld(), IID_PEA, getX()+1, getY(), getDirection()));
            getWorld()->playSound(SOUND_ENEMY_FIRE);
        }
        else if(getDirection() == up){
            getWorld()->addactor(new Pea(getWorld(), IID_PEA, getX(), getY()+1, getDirection()));
            getWorld()->playSound(SOUND_ENEMY_FIRE);
        }
        else if(getDirection() == down){
            getWorld()->addactor(new Pea(getWorld(), IID_PEA, getX(), getY()-1, getDirection()));
            getWorld()->playSound(SOUND_ENEMY_FIRE);

        }
        updateticks();
        return;
    }
    Actor *a;
    if(getWorld()->hasactor(this, getX(), getY())){
        a = getWorld()->findGoodie(this, getX(), getY());
        if(a != nullptr && a->obtainable() && pickup() && a->isstolen() == false){
            int steal = rand()%10+1;
            if(steal == 1){
                this->steal();
                a->stolen();
                getWorld()->playSound(SOUND_ROBOT_MUNCH);
                a->setVisible(false);
                setptr(a);
            }
        }
    }
    if(getcounter() != getdbt()){
        updateticks();
        if(getDirection() == left){
            if(!obstruction(getX()-1, getY())){
                moveTo(getX()-1, getY());
                inccount();
                return;
            }
        }
        else if(getDirection() == right){
            if(!obstruction(getX()+1, getY())){
                moveTo(getX()+1, getY());
                inccount();
                return;
            }
        }
        else if(getDirection() == up){
            if(!obstruction(getX(), getY()+1)){
                moveTo(getX(), getY()+1);
                inccount();
                return;
            }
        }
        else if(getDirection() == down){
            if(!obstruction(getX(), getY()-1)){
                moveTo(getX(), getY()-1);
                inccount();
                return;
            }
        }
    }
    
    setcounter(0);
    vector<int> c;
    setdbt(rand()%6+1);
    int randdir = (rand()%4)*90;
    c.push_back(randdir);
    updateticks();
    if(randdir == 0){
        if(!obstruction(getX()+1, getY())){
            setDirection(right);
                return;
        }
        else{
            int n = randdirection(c);
            if(n != -1){
                setDirection(n);}
                        else{
                            setDirection(randdir);
                            return;
                        }
                    }
                    }
                else if(randdir == 90){
                    if(!obstruction(getX(), getY()+1)){
                        setDirection(up);
                        return;
                    }
                    else{
                        int n = randdirection(c);
                        if(n != -1){
                            setDirection(n);
                        }
                        else{
                            setDirection(randdir);
                            return;
                        }
                    }
                    }
                else if(randdir == 180){
                    if(!obstruction(getX()-1, getY())){
                        setDirection(left);
                        return;
                    }
                    else{
                        int n = randdirection(c);
                        if(n != -1){
                            setDirection(n);
                        }
                        else{
                            setDirection(randdir);
                            return;
                        }
                    }
                    }
                else if(randdir == 270){
                    if(!obstruction(getX(), getY()-1)){
                        setDirection(down);
                        return;
                    }
                    else{
                        int n = randdirection(c);
                        if(n != -1){
                            setDirection(n);
                        }
                        else{
                            setDirection(randdir);
                            return;
                        }
                    }
                    }
            }
    
    
void ThiefBotFactory::doSomething(){
    int count = 0;
    for(int i = getX()-3; i < getX()+3; i++){
        for(int j = getY()-3; j < getY()+3; j++){
            Actor *a;
            a = getWorld()->findThieves(this, i, j);
            if (a == nullptr) continue;
            if(a->cansteal() == true){
                count++;
            }
        }
    }
    if(count < 3){
        Actor *b;
        if(getWorld()->hasactor(this, getX(), getY())){
            b = getWorld()->findThieves(this, getX(), getY());
            if(b != nullptr && b->cansteal() == false){
                int random = (rand()%50);
                if(random == 0){
                    if(mean == false){
                        getWorld()->addactor(new ThiefBot(getWorld(), IID_THIEFBOT, getX(), getY(), 0));
                        getWorld()->playSound(SOUND_ROBOT_BORN);
                    }
                    else{
                        getWorld()->addactor(new MeanThiefBot(getWorld(), IID_THIEFBOT, getX(), getY(), 0));
                        getWorld()->playSound(SOUND_ROBOT_BORN);

                    }
                }
            }
            return;
        }
        else{
            int random = (rand()%50);
            if(random == 0){
                if(mean == false){
                    getWorld()->addactor(new ThiefBot(getWorld(), IID_THIEFBOT, getX(), getY(), 0));
                    getWorld()->playSound(SOUND_ROBOT_BORN);

                }
                else{
                    getWorld()->addactor(new MeanThiefBot(getWorld(), IID_THIEFBOT, getX(), getY(), 0));
                    getWorld()->playSound(SOUND_ROBOT_BORN);

                }
                return;
            }
        }
    }
}

    
    

    



