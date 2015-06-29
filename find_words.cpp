#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

set<pair<int, int> > blockers;

const int kUp = 0;
const int kDown = 1;
const int kLeft = 2;
const int kRight = 4;

bool search(vector<vector<char> >& board, int row, int col,
            const string& word, int index);

void addBlock(int row, int col) {
    blockers.insert(pair<int, int>(row, col));
}

void clearBlock(int row, int col) {
    set<pair<int, int> >::iterator it = blockers.find(pair<int, int>(row, col));
    blockers.erase(it);
}

void clearBlocks() {
    blockers.clear();
}

bool block(int row, int col) {
    return blockers.find(pair<int, int>(row, col)) != blockers.end();
}

bool match(char c1, char c2) {
    return c1 == c2;
}

bool searchAround(vector<vector<char> >& board, int row, int col,
                  const string& word, int index, int direction) {
    int dstRow = row;
    int dstCol = col;
    if (direction == kUp) {
        dstRow = row - 1;
    } else if (direction == kDown) {
        dstRow = row + 1;
    } else if (direction == kLeft) {
        dstCol = col - 1;
    } else {
        dstCol = col + 1;
    }

    if (!block(dstRow, dstCol) && match(board[dstRow][dstCol], word[index])) {
        addBlock(dstRow, dstCol);
        if (search(board, dstRow, dstCol, word, index + 1)) {
            return true;
        } else {
            clearBlock(dstRow, dstCol);
        }
    }

    return false;
}

bool search(vector<vector<char> >& board, int row, int col,
            const string& word, int index) {
    if (index == word.length()) {
        return true;
    }

    if (row - 1 >= 0) {
        if (searchAround(board, row, col, word, index, kUp)) {
            return true;
        }
    }

    if (row + 1 < board.size()) {
        if (searchAround(board, row, col, word, index, kDown)) {
            return true;
        }
    }

    if (col - 1 >= 0) {
        if (searchAround(board, row, col, word, index, kLeft)) {
            return true;
        }
    }

    if (col + 1 <= board[row].size()) {
        if (searchAround(board, row, col, word, index, kRight)) {
            return true;
        }
    }

    return false;
}

bool exist(vector<vector<char> >& board, string word) {
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            if (match(board[i][j], word[0])) {
                addBlock(i, j);
                if (search(board, i, j, word, 1)) {
                    clearBlocks();
                    return true;
                }
                clearBlock(i, j);
            }
        }
    }

    clearBlocks();
    return false;
}

int main(int argc, char* argv[])
{
    vector<char> row1, row2, row3;
    row1.push_back('A');
    row1.push_back('B');
    row1.push_back('C');
    row1.push_back('E');

    row2.push_back('S');
    row2.push_back('F');
    row2.push_back('C');
    row2.push_back('S');

    row3.push_back('A');
    row3.push_back('D');
    row3.push_back('E');
    row3.push_back('E');

    vector<vector<char> > rows;
    rows.push_back(row1);
    rows.push_back(row2);
    rows.push_back(row3);

    std::cout << exist(rows, "ABCCED") << std::endl;
    std::cout << exist(rows, "SEE") << std::endl;
    std::cout << exist(rows, "ABCB") << std::endl;

    return 0;
}
