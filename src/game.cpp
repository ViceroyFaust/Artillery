#include <cmath>

#include <iostream>
#include <vector>

#include "cli.h"
#include "game.h"
#include "gameObjs.h"
#include "maths.h"
#include "owlFuncs.h"

// Generate a unique ID for every target as needed via static u_int
unsigned int World::genTargetID() {
    static unsigned int s_id{0};
    return s_id++;
}

/* Calculates the distance of a shot based on the assumption that the shot is fired
 * and landed on the same elevation. Velocity is provided for the user, while the
 * the direction and firing angle is taken from the artillery's state */
double Artillery::calcLevelDistance(double shotVelocity) {
    double radElev = deg2Rad(m_degElevation);
    // 2 * vnet^2 * sin(theta) * cos(theta) / g
    return std::abs(2 * (shotVelocity*shotVelocity) * std::sin(radElev) * std::cos(radElev) / 9.81);
}

/* = Constructor for every member variable =
 * DegHeading - compass heading; DegElevation firing angle; maxRotSpeed & maxElevSpeed - deg/s */
Artillery::Artillery(double degHeading, double degElevation, double maxRotSpeed, double maxElevSpeed)
    : m_degBearing(rotateThrough(degHeading, 0, 360)), m_degElevation(clamp(degElevation, 0, 90)),
      m_maxRotSpeed(noLessThan(maxRotSpeed, 0)), m_maxElevSpeed(noLessThan(maxElevSpeed, 0)) {};
// Constructs heading and firing angle at 0. Rotation speed is set by user.
Artillery::Artillery(double maxRotSpeed, double maxElevSpeed) : Artillery(0.0, 0.0, maxRotSpeed, maxElevSpeed) {};

// Changes heading by the given input: -360 to 360 degrees. When North is passed, it rotates through.
void Artillery::rotateBy(double degrees) {
    m_degBearing = rotateThrough(m_degBearing + degrees, 0, 360);
}

// Changes elevation by the given input. Cannot go below 0 or beyond 90 degrees.
void Artillery::changeElevBy(double degrees) {
    m_degElevation = clamp(m_degElevation + degrees, 0, 90);
}

// Calculates the landing point of the shot and returns the coordinates
Point Artillery::shoot(double shotVelocity) {
    double distance = calcLevelDistance(shotVelocity);
    // Convert the bearing to trig degrees for math to be right
    // Further, convert degrees to radians as that's what cmath uses
    double radHead = deg2Rad(bear2deg(m_degBearing));
    double x = distance * std::cos(radHead);
    double y = distance * std::sin(radHead);
    return Point(x, y);
}

/* Checks if any targets are hit. If hit, points are added and health is subtracted
 * All shots, whether hit or not, are added to shot history.*/
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

// Processes the commands entered in the terminal. Returns true to exit.
bool Game::processCommands(const std::string& in) {
    std::vector<std::string> args = splitStr(trim(in), " ");
    if (args.empty())
        return false;
    if (args[0] == "exit")
        return true;
    if (args[0] == "help") {
        printHelp();
    } else if (args[0] == "artinfo") {
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
    } else if (args[0] == "aim") {
        std::cout << "Shot aimed @ " << art.shoot(std::stod(args[1])) << std::endl;
    }
    return false;
}

// Starts the main game loop
void Game::startGame() {
    std::string in;
    bool done = false;
    printInfo();
    while(!done) {
        in = getInput();
        done = processCommands(in);
    }
}

// Prints all of the command options
void Game::printHelp() const {
    std::cout << "artinfo - print artillery information\n"
    << "shothist - print shot history list\n"
    << "targets - print target list\n"
    << "rotate [deg] - rotate artillery by degrees\n"
    << "elevate [deg] - elevate firing angle by degrees\n"
    << "shoot [vel] - shoot with given velocity (m/s)\n"
    << "aim [vel] - predict shot with given velocity (m/s)\n"
    << "help - show this help screen\n"
    << "exit - exit the game\n";
}

// Prints all information regarding the artillery
void Game::printInfo() const {
    std::cout << "All Info:" << std::endl;
    printArtBearing();
    printArtElevation();
    printRotSpeed();
    printElevSpeed();
    printPoints();
}

// Prints players' points
void Game::printPoints() const {
    std::cout << "Points: " << points << std::endl;
}

// Prints the bearing of the artillery's cannon
void Game::printArtBearing() const {
    std::cout << "Current Bearing: " << art.getBearing() << "°\n";
}

// Prints the firing angle of the artillery's cannon
void Game::printArtElevation() const {
    std::cout << "Current Elevation: " << art.getDegsElevation() << "°\n";
}

// Prints the rotation speed of the cannon in deg/s
void Game::printRotSpeed() const {
    std::cout << "Rotational speed: " << art.getRotSpeed() << "°/second\n";
}

// Prints the elevation speed of the cannon in deg/s
void Game::printElevSpeed() const {
    std::cout << "Elevation speed: " << art.getElevSpeed() << "°/second\n";
}

// Prints shot history as a list
void Game::printShotHist() const {
    std::cout << "Shot History:\n";
    for (size_t i = 0; i < gameMap.getShotsAmt(); ++i) {
        std::cout << gameMap.getShot(i) << std::endl;
    }
}

// Prints game targets as a list along with their status
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
