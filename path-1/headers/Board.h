#pragma once

#include <iostream>
#include <vector>

class Tile {
private:
    bool merged;
    int value;
public:
    Tile() { this->value = 0; this->merged = false; };
    Tile(int value) { this->value = value; this->merged = false; };

    int getValue() { return this->value; };

    bool isEmpty() { return this->value == 0; };
    bool isMerged() { return this->merged; };
    void setMerged(bool merged) { this->merged = merged; };

    bool operator==(Tile& other) { return this->value == other.value; };
    Tile& operator *=(int magnitude) { this->value *= magnitude; return *this; };

    friend std::ostream& operator<<(std::ostream& co, Tile& tile) { co << tile.value; return co; };
    friend int& operator+=(int& value, Tile& tile) { value += tile.value; return value; };
    // friend int& operator=(int& value, Tile& tile) { value = tile.value; return value; };
};

class Board {
private:
    int width;
    Tile** board;
    bool initialized;
    int lastMove;

    static const int numStartingTiles = 2;

public:
    Board();
    ~Board();

    void setWidth(int width) { this->width = width; };
    void setLastMove(int lastMove) { this->lastMove = lastMove; };

    int getWidth() const { return this->width; };
    int getLastMove() const { return this->lastMove; };


    void initialize();
    void wipe();
    void seed();
    void destroy();
    void reset();

    void manualSet(int x1, int y1, int val1, int x2, int y2, int val2);

    float* flatten() const;

    std::vector<int*> getAvailableCells();

    void addPiece(int x, int y);
    bool addPieceManual(int x, int y, int value);
    void addRandomTile();

    std::pair<bool, int> shift(int dir);
    std::pair<int, int> findShiftDestination(int x, int y, std::pair<int, int> vec);

    std::pair<int, int> getVector(int dir);
    void getXTraversals(std::pair<int, int> vec, int* traversals);
    void getYTraversals(std::pair<int, int> vec, int* traversals);
    bool coordsInBounds(std::pair<int, int> vec);
    bool slotOccupied(std::pair<int, int> vec);

    bool slotsAvailable();
    bool matchesPossible();

    Board& operator=(const Board& other);

    friend std::ostream& operator<<(std::ostream& out, const Board& board);
};