#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <vector>
#include "gameObjs.h"

class World {
private:
    std::vector<Point> shots;
    std::vector<Target> targets;

    // Generate a unique ID for every target as needed via static u_int
    unsigned int genTargetID();

public:
    World() : shots(), targets() {};

    void recordShot(const Point& c) {
        shots.push_back(c);
    }

    void addTarget(const Target& toAdd) {
        targets.push_back(toAdd);
    }

    void removeTarget(unsigned int index) {
        targets.erase(targets.begin() + index);
    }

    unsigned int getTargetAmt() const {
        return targets.size();
    }

    Target getTarget(unsigned int index) const {
        return targets[index];
    }

    unsigned int getShotsAmt() const {
        return shots.size();
    }

    Point getShot(unsigned int index) const {
        return shots[index];
    }
};

class Artillery {
private:
    double m_degBearing;
    double m_degElevation;
    double m_maxRotSpeed;
    double m_maxElevSpeed;

    /* Calculates the distance of a shot based on the assumption that the shot is fired
    * and landed on the same elevation. Velocity is provided for the user, while the
    * the direction and firing angle is taken from the artillery's state */
    double calcLevelDistance(double shotVelocity);

public:
    /* = Constructor for every member variable =
    * DegHeading - compass heading; DegElevation firing angle; maxRotSpeed & maxElevSpeed - deg/s */
    Artillery(double degHeading, double degElevation, double maxRotSpeed, double maxElevSpeed);
    // Constructs heading and firing angle at 0. Rotation speed is set by user.
    Artillery(double maxRotSpeed, double maxElevSpeed);

    // Changes heading by the given input: -360 to 360 degrees. When North is passed, it rotates through.
    void rotateBy(double degrees);

    // Changes elevation by the given input. Cannot go below 0 or beyond 90 degrees.
    void changeElevBy(double degrees);

    double getBearing () const {
        return m_degBearing;
    }

    double getDegsElevation() const {
        return m_degElevation;
    }

    double getRotSpeed() const {
        return m_maxRotSpeed;
    }

    double getElevSpeed() const {
        return m_maxElevSpeed;
    }

    // Calculates the landing point of the shot and returns the coordinates
    Point shoot(double shotVelocity);
};


class Game {
private:
    int points;
    World gameMap;
    Artillery art;

    /* Checks if any targets are hit. If hit, points are added and health is subtracted
    * All shots, whether hit or not, are added to shot history.*/
    void recordHits(const Point& shot);

    // Returns a bool. True - exit, otherwise false and Processes the commands entered in the terminal
    bool processCommands(const std::string& in);

public:
    Game(double maxRotSpeed, double maxElevSpeed)
        : points(0), gameMap(), art(maxRotSpeed, maxElevSpeed) {};
    Game() : Game(20, 10) {};

    // Starts the main game loop
    void startGame();

    // Prints all information regarding the artillery
    void printInfo() const;

    // Prints players' points
    void printPoints() const;

    // Prints the bearing of the artillery's cannon
    void printArtBearing() const;

    // Prints the firing angle of the artillery's cannon
    void printArtElevation() const;

    // Prints the rotation speed of the cannon in deg/s
    void printRotSpeed() const;

    // Prints the elevation speed of the cannon in deg/s
    void printElevSpeed() const;

    // Prints shot history as a list
    void printShotHist() const;

    // Prints game targets as a list along with their status
    void printTargets() const;
};

#endif
