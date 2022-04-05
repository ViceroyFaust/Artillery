#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <vector>
#include "gameObjs.h"

class World {
private:
    std::vector<Point> shots;
    std::vector<Target> targets;

    unsigned int genTargetID();

public:
    World() : shots(), targets() {};

    void recordShot(const Point& c) { shots.push_back(c); }

    void addTarget(const Target& toAdd) { targets.push_back(toAdd); }

    void removeTarget(unsigned int index) { targets.erase(targets.begin() + index); }

    unsigned int getTargetAmt() const { return targets.size(); }

    Target getTarget(unsigned int index) const { return targets[index]; }

    unsigned int getShotsAmt() const { return shots.size(); }

    Point getShot(unsigned int index) const { return shots[index]; }
};

class Artillery {
private:
    double m_degBearing;
    double m_degElevation;
    double m_maxRotSpeed;
    double m_maxElevSpeed;

    double calcLevelDistance(double shotVelocity);

public:
    Artillery(double degHeading, double degElevation, double maxRotSpeed, double maxElevSpeed);
    Artillery(double maxRotSpeed, double maxElevSpeed);

    void rotateBy(double degrees);

    void changeElevBy(double degrees);

    double getBearing () const { return m_degBearing; }

    double getDegsElevation() const { return m_degElevation; }

    double getRotSpeed() const { return m_maxRotSpeed; }

    double getElevSpeed() const { return m_maxElevSpeed; }

    Point shoot(double shotVelocity);
};


class Game {
private:
    int points;
    World gameMap;
    Artillery art;

    void recordHits(const Point& shot);

    // Returns a bool. True - exit, otherwise false
    bool processCommands(const std::string& in);

public:
    Game(double maxRotSpeed, double maxElevSpeed)
        : points(0), gameMap(), art(maxRotSpeed, maxElevSpeed) {};
    Game() : Game(20, 10) {};

    void startGame();

    void printInfo() const;

    void printPoints() const;

    void printArtBearing() const;

    void printArtElevation() const;

    void printRotSpeed() const;

    void printElevSpeed() const;

    void printShotHist() const;

    void printTargets() const;
};

#endif
