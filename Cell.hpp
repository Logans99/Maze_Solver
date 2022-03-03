//
// Created by Logan Santos on 2/1/22.
//

#ifndef PROJECT1_MAZE_CELL_HPP
#define PROJECT1_MAZE_CELL_HPP


class Cell {
public:
    Cell(int row, int col);

    // Getters
    int row();
    int column();
    bool wall();
    bool path();
    bool targetCell();
    bool isRead();
    // setter
    void setWall(bool);
    void setPath(bool);
    void setTargetCell(bool);
    void setIsRead(bool);

private:
    int _row, _column;     // To store row and column
    bool _wall, _path, _targetCell, _isRead;
};


#endif //PROJECT1_MAZE_CELL_HPP
