#include <cmath>

#include <iostream>
#include <vector>

#include "cli.h"
#include "game.h"
#include "gameObjs.h"
#include "maths.h"
#include "owlFuncs.h"

unsigned int World::genTargetID() {
    static unsigned int s_id{0};
    return s_id++;
}

double Artillery::calcLevelDistance(double shotVelocity) {
    double radElev = deg2Rad(m_degElevation);
    // 2 * vnet^2 * sin(theta) * cos(theta) / g
    return std::abs(2 * (shotVelocity*shotVelocity) * std::sin(radElev) * std::cos(radElev) / 9.81);
}

Artillery::Artillery(double degHeading, double degElevation, double maxRotSpeed, double maxElevSpeed)
    : m_degBearing(rotateThrough(degHeading, 0, 360)), m_degElevation(clamp(degElevation, 0, 90)),
      m_maxRotSpeed(noLessThan(maxRotSpeed, 0)), m_maxElevSpeed(noLessThan(maxElevSpeed, 0)) {};

Artillery::Artillery(double maxRotSpeed, double maxElevSpeed) : Artillery(0.0, 0.0, maxRotSpeed, maxElevSpeed) {};

void Artillery::rotateBy(double degrees) {
    m_degBearing = rotateThrough(m_degBearing + degrees, 0, 360);
}

void Artillery::changeElevBy(double degrees) {
    m_degElevation = clamp(m_degElevation + degrees, 0, 90);
}

Point Artillery::shoot(double shotVelocity) {
    double distance = calcLevelDistance(shotVelocity);
    // Convert the bearing to trig degrees for math to be right
    // Further, convert degrees to radians as that's what cmath uses
    double radHead = deg2Rad(bear2deg(m_degBearing));
    double x = distance * std::cos(radHead);
    double y = distance * std::sin(radHead);
    return Point(x, y);
}

void Game::recordHits(const Point& shot) {
    unsigned int size = gameMap.getTargetAmt();
    for (unsigned int i = 0u; i < size; ++i) {
        Target t = gameMap.getTarget(i);
        if (t.getHP() > 0 && t.doesThisHitMe(shot)) {
            points += t.getPoints();
            t.changeHP(-100);
        }
    }
    gameMap.recordShot(shot);
}

bool Game::processCommands(const std::string& in) {
    std::vector<std::string> args = splitStr(trim(in), " ");
    if (args.empty())
        return false;
    if (args[0] == "exit")
        return true;
    if (args[0] == "artinfo") {
        printInfo();
    } else if (args[0] == "shothist") {
        printShotHist();
    } else if (args[0] == "targets") {
        printTargets();
    } else if (args[0] == "rotate") {
        art.rotateBy(std::stod(args[1]));
    } else if (args[0] == "elevate") {
        art.changeElevBy(std::stod(args[1]));
    } else if (args[0] == "shoot") {
        Point shot = art.shoot(std::stod(args[1]));
        std::cout << "Shot landed @ " << shot << std::endl;
        recordHits(shot);
    }
    return false;
}

void Game::startGame() {
    std::string in;
    bool done = false;
    printInfo();
    while(!done) {
        in = getInput();
        done = processCommands(in);
    }
}

void Game::printInfo() const {
    std::cout << "All Info:" << std::endl;
    printArtBearing();
    printArtElevation();
    printRotSpeed();
    printElevSpeed();
    printPoints();
}

void Game::printPoints() const {
    std::cout << "Points: " << points << std::endl;
}

void Game::printArtBearing() const {
    std::cout << "Current Bearing: " << art.getBearing() << "°\n";
}

void Game::printArtElevation() const {
    std::cout << "Current Elevation: " << art.getDegsElevation() << "°\n";
}

void Game::printRotSpeed() const {
    std::cout << "Rotational speed: " << art.getRotSpeed() << "°/second\n";
}

void Game::printElevSpeed() const {
    std::cout << "Elevation speed: " << art.getElevSpeed() << "°/second\n";
}

void Game::printShotHist() const {
    std::cout << "Shot History:\n";
    for (size_t i = 0; i < gameMap.getShotsAmt(); ++i) {
        std::cout << gameMap.getShot(i) << std::endl;
    }
}

void Game::printTargets() const {
    std::cout << "Targets:\n";
    for (size_t i = 0; i < gameMap.getTargetAmt(); ++i) {
        Target targ = gameMap.getTarget(i);
        std::cout << targ.getPos();
        if (targ.getHP() > 0)
            std::cout << " " << targ.getHP() << " HP\n";
        else
            std::cout << " DESTROYED\n";
    }
}
