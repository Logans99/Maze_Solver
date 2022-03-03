#include <iostream>
#include <fstream>
#include <vector>
#include "stack"
#include "Cell.hpp"

void Reader(int argc, char *argv[], std::vector<std::vector<Cell>> &grid) {

    std::fstream inputStream;
    inputStream.open(argv[1], std::ios::in);
    if(! inputStream.is_open()) {
        std::cout << "Unable to open" << argv[1] << std::endl;
        std::cout << "Terminating...\n";
        exit(2);
    }

    std::cout << "Looks like it was able to open file " << argv[1] << std::endl;
    char input;
    int countRow = 0;
    int countCol = 0;
    grid.push_back({});
    while( inputStream.get(input)) {
        if(input == '\n') {
            countRow++;
            countCol = 0;
            grid.push_back({});
        }
        if(input == '1') {
            Cell cell(countRow, countCol);
            cell.setWall(true);
            grid.at(countRow).push_back(cell);
            countCol++;
        }
        if(input == '0') {
            Cell cell(countRow, countCol);
            cell.setPath(true);
            grid.at(countRow).push_back(cell);
            countCol++;
        }
    }

/* reading input file
 * every char make a cell
 * go through each case wall cell or path cell
 * check if char is end line if is reset col and increment the row.
 * dont want to make a cell if the char is an end line.
 *
 * after this grid is made go through grid again find the target cell(boarder)
 */
}

void FindTargetCell(std::vector<std::vector<Cell>> &grid) {
    for (int i= 0; i < grid.size(); i++) {
        for (int j= 0; j < grid.at(0).size(); j++ ){
            if (i == 0 || i == grid.size() - 1) {       // top boarder or bottom boarder
                if(grid.at(i).at(j).path()) {
                    grid.at(i).at(j).setTargetCell(true);
                }
            }
            if (j == 0 || j == grid.at(0).size() - 1) {       // left boarder or right boarder?///
                if(grid.at(i).at(j).path()) {
                    grid.at(i).at(j).setTargetCell(true);
                }
            }
        }
    }
}

Cell GetStartCell(std::vector<std::vector<Cell>> &grid) {

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid.at(0).size(); j++) {
            if(grid.at(i).at(j).targetCell()) {
                grid.at(i).at(j).setIsRead(true);
                return grid.at(i).at(j);
            }
        }
    }
    return Cell(-1,-1);
}

bool AdjacentCell(Cell currentCell, std::vector<std::vector<Cell>> &grid) {
    if(currentCell.row() > 0) {
        if (grid.at(currentCell.row() - 1).at(currentCell.column()).path()) {   // Below
            if (!grid.at(currentCell.row() - 1).at(currentCell.column()).isRead())
                return true;
        }
    }

    if(currentCell.row() < grid.size() - 1) {
        if (grid.at(currentCell.row() + 1).at(currentCell.column()).path()) {   // Above?
            if (!grid.at(currentCell.row() + 1).at(currentCell.column()).isRead())
                return true;
        }
    }

    if(currentCell.column() > 0) {
        if (grid.at(currentCell.row()).at(currentCell.column() - 1).path()) {   // Left?
            if (!grid.at(currentCell.row()).at(currentCell.column() - 1).isRead())
                return true;
        }
    }

    if(currentCell.column() < grid.at(0).size() - 1) {
        if (grid.at(currentCell.row()).at(currentCell.column() + 1).path()) {   // Right?
            if (!grid.at(currentCell.row()).at(currentCell.column() + 1).isRead())
                return true;
        }
    }
    return false;
}

Cell RecallCell(Cell currentCell, std::vector<std::vector<Cell>> &grid) {

    if (currentCell.row() > 0) {
        if (grid.at(currentCell.row() - 1).at(currentCell.column()).path()) {   // Below
            if (!grid.at(currentCell.row() - 1).at(currentCell.column()).isRead()) {
                grid.at(currentCell.row() - 1).at(currentCell.column()).setIsRead(true);
                return (grid.at(currentCell.row() - 1).at(currentCell.column()));
            }
        }
    }

    if (currentCell.row() < grid.size() - 1) {
        if (grid.at(currentCell.row() + 1).at(currentCell.column()).path()) {   // Above?
            if (!grid.at(currentCell.row() + 1).at(currentCell.column()).isRead()) {
                grid.at(currentCell.row() + 1).at(currentCell.column()).setIsRead(true);
                return (grid.at(currentCell.row() + 1).at(currentCell.column()));
            }
        }
    }

    if (currentCell.column() > 0) {
        if (grid.at(currentCell.row()).at(currentCell.column() - 1).path()) {   // Left?
            if (!grid.at(currentCell.row()).at(currentCell.column() - 1).isRead()) {
                grid.at(currentCell.row()).at(currentCell.column() - 1).setIsRead(true);
                return (grid.at(currentCell.row()).at(currentCell.column() - 1));
            }
        }
    }
    if (currentCell.column() < grid.at(0).size() - 1) {
        if (grid.at(currentCell.row()).at(currentCell.column() + 1).path()) {   // Right?
            if (!grid.at(currentCell.row()).at(currentCell.column() + 1).isRead()) {
                grid.at(currentCell.row()).at(currentCell.column() + 1).setIsRead(true);
                return (grid.at(currentCell.row()).at(currentCell.column() + 1));
            }
        }
    }
}

std::stack<Cell> BackTracking(std::vector<std::vector<Cell>> &grid) {
    std::stack<Cell> myStack;
    myStack.push(GetStartCell(grid));

    while(! myStack.empty()) {
        //Cell top = myStack.top();

        if(! AdjacentCell(myStack.top(), grid)) {
            myStack.pop();
        }
        else {
            Cell collect = RecallCell(myStack.top(), grid);

            //collect.setIsRead(true);                    // already has been explored
            myStack.push(collect);                      // pushing cell collect on the stack

            if(collect.targetCell()) {
                break;
            }
        }
    }

    return myStack;
}
    /*
    push the start cell onto a stack
    while the stack is not empty do
        if there is no successor (adjacent cell) for the top element of the stack {
            pop the stack
    } else {
        let s be a cell that is adjacent to the
        one that is on top of the stack and has not been explored yet
        push s onto the stack
        mark s as used (explored)
        if s is the target, exit this loop
    }
    end-while
        if the stack is empty, there is no path from the start cell to the target cell
    otherwise, the stack contains the path, in the reverse order
     */

int main(int argc, char *argv[]) {
    if(argc != 2) {
        std::cout << "This app expects a single arg to be used as an input file\n";
        exit(1);
    }
    std::vector<std::vector<Cell>> grid;            // 2D vector of cells
    Reader(argc, argv, grid);
    FindTargetCell(grid);
    std::stack<Cell> myStack;
    myStack = BackTracking(grid);

    while(! myStack.empty()) {
        grid[myStack.top().row()][myStack.top().column()].setPath(false);
        myStack.pop();
    }

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j].wall()) {
                std::cout << "1";
            }
            else if (grid[i][j].path()) {
                std::cout << "0";
            }
            else
                std::cout << " ";
        }
        std::cout << "\n";
    }

}