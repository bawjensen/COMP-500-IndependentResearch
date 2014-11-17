#include "../headers/GameController.h"
#include "../headers/GameTreeManager.h"
#include "../headers/NetManager.h"

#include <iostream>
#include <chrono>

using namespace std;

GameController::GameController() {
    this->reset();
}

void GameController::reset() {
    this->numMoves = 0;
}

bool GameController::movesAvailable() {
    return this->board.slotsAvailable() || this->board.matchesPossible();
}

bool GameController::gameEnded() {
    return !this->movesAvailable();
}

void GameController::start() {
    int numGenerations = 100;
    int numNets = 40;
    int score;
    int avgScore;

    // NeuralNet* nets = new NeuralNet[numNets];
    NetManager mgr(numNets);

    long start = chrono::system_clock::now().time_since_epoch().count();
    srand(start);

    this->board.initialize();
    this->board.seed();

    for (int i = 0; i < numGenerations; ++i) {
        avgScore = 0;
        for (int j = 0; j < numNets; ++j) {
            this->board.reset();
            score = this->runGameWithNet(mgr[j]);
            mgr.keepScore(score, j);
            // cout << "Net (" << &mgr[j] << ") scored: " << score << endl;
            avgScore += score;
        }
        cout << "Nets of generation " << i << " averaged: " << (float)avgScore / numNets << endl;
        mgr.selectAndMutateSurvivors();
    }

    long end = chrono::system_clock::now().time_since_epoch().count();

    float numSec = (end - start) / (float)1000000;
    cout << this->numMoves << " moves in " << numSec << " sec (" << (int)(this->numMoves / numSec) << " moves per second)" << endl;
}

// void GameController::runGame() {
//     for (int i = 0; i < this->numStartingTiles; i++)
//         this->board.addRandomTile();

//     int direction = -1;

//     while ( !this->gameEnded() ) {
//         if (this->handleCommand(direction)) {
//             ++this->numMoves;
//             this->board.addRandomTile();
//         }

//         direction = rand() % 4;
//     }
// }

int GameController::runGameWithNet(NeuralNet& net) {
    for (int i = 0; i < this->numStartingTiles; i++)
        this->board.addRandomTile();

    int direction;
    int score = 0;
    float netOutput;
    bool success;
    pair<bool, int> result;

    direction = GameTreeManager::determineBestMove(board, net);

    while ( !this->gameEnded() ) {
        result = this->handleCommand(direction);
        success = result.first;

        if (success) {
            score += result.second;

            ++this->numMoves;
            this->board.addRandomTile();

            // netOutput = net.run(this->board.flatten());

            direction = GameTreeManager::determineBestMove(board, net);

            // direction = (((int)netOutput) * 4) % 4;
            // cout << "Net returned " << netOutput << endl;
            // cout << "Input was " << direction << endl;
            // cout << "Board was:" << endl << this->board << endl;
        }
        else { // If board can't make an effective move, make a random one for it
            // cout << "Resorting to random movement" << endl;
            cout << "Board tried a bad direction: " << direction << endl;
            cout << this->board << endl;
            exit(1);
            direction = rand() % 4;
        }
    }

    return score;
}

pair<bool, int> GameController::handleCommand(int& direction) {
    pair<bool, int> result;

    if (direction < 4 && direction >= 0) {
        result = this->board.shift(direction);
    }

    return result;
}