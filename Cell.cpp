//
// Created by Logan Santos on 2/1/22.
//

#include "Cell.hpp"

Cell::Cell(int row, int col) {
    _row = row;
    _column = col;

    setWall(false);
    setPath(false);
    setTargetCell(false);
    setIsRead(false);
}

// Accessor functions
int Cell::row() {
    return _row;
}

int Cell::column() {
    return _column;

}
bool Cell::wall() {
    return _wall;
}
bool Cell::path() {
    return _path;
}

bool Cell::targetCell() {
    return _targetCell;
}

bool Cell::isRead() {
    return _isRead;
}

void Cell::setWall(bool value) {
    _wall = value;
}

void Cell::setPath(bool value) {
    _path = value;
}

void Cell::setTargetCell(bool value) {
    _targetCell = value;
}

void Cell::setIsRead(bool value) {
    _isRead = value;
}