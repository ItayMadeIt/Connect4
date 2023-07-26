/*
 * This file is part of Connect4 Game Solver <http://connect4.gamesolver.org>
 * Copyright (C) 2007 Pascal Pons <contact@gamesolver.org>
 *
 * Connect4 Game Solver is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * Connect4 Game Solver is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with Connect4 Game Solver. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * I just copied it to use it as a comprasion to my code, this code is not owned by me in any way 
 * I want to clarify it
 */

#ifndef POSITION_HPP
#define POSITION_HPP

#include <string>

class Position
{
public:

    static const int WIDTH = 7;  // width of the board
    static const int HEIGHT = 6; // height of the board

    static const int SIZE = WIDTH * HEIGHT; // height of the board
    
    bool canPlay(int col) const
    {
        return (mask & top_mask(col)) == 0;
    }


    void play(int col)
    {
        current_position ^= mask;
        mask |= mask + bottom_mask(col);
        moves++;
    }

    unsigned int play(std::string seq)
    {
        for (unsigned int i = 0; i < seq.size(); i++) {
            int col = seq[i] - '1';
            if (col < 0 || col >= Position::WIDTH || !canPlay(col) || isWinningMove(col)) return i; // invalid move
            play(col);
        }
        return seq.size();
    }

    bool isWinningMove(int col) const
    {
        uint64_t pos = current_position;
        pos |= (mask + bottom_mask(col)) & column_mask(col);
        return alignment(pos);
    }
    unsigned int nbMoves() const
    {
        return moves;
    }
    uint64_t key() const
    {
        return current_position + mask;
    }

    Position() : current_position{ 0 }, mask{ 0 }, moves{ 0 } {}
private:
    uint64_t current_position;
    uint64_t mask;
    unsigned int moves; 

    static bool alignment(uint64_t pos) {
        // horizontal 
        uint64_t m = pos & (pos >> (HEIGHT + 1));
        if (m & (m >> (2 * (HEIGHT + 1)))) return true;

        // diagonal 1
        m = pos & (pos >> HEIGHT);
        if (m & (m >> (2 * HEIGHT))) return true;

        // diagonal 2 
        m = pos & (pos >> (HEIGHT + 2));
        if (m & (m >> (2 * (HEIGHT + 2)))) return true;

        // vertical;
        m = pos & (pos >> 1);
        if (m & (m >> 2)) return true;

        return false;
    }

    // return a bitmask containg a single 1 corresponding to the top cel of a given column
    static uint64_t top_mask(int col) {
        return (UINT64_C(1) << (HEIGHT - 1)) << col * (HEIGHT + 1);
    }

    // return a bitmask containg a single 1 corresponding to the bottom cell of a given column
    static uint64_t bottom_mask(int col) {
        return UINT64_C(1) << col * (HEIGHT + 1);
    }

    // return a bitmask 1 on all the cells of a given column
    static uint64_t column_mask(int col) {
        return ((UINT64_C(1) << HEIGHT) - 1) << col * (HEIGHT + 1);
    }
};

#endif