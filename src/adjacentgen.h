#ifndef ADJACENTGEN_H
#define ADJACENTGEN_H

#include "gamestate.h"
#include <iostream>
#include <utility>

bool onBoard(int row, int col)
{
    return row >= 0 && row < kBoardSize && col >= 0 && col < kBoardSize;
}

struct AdjacentGen
{
    explicit AdjacentGen(int row, int col):
        m_row(row),
        m_col(col)
    {
    }

    struct Iterator
    {
        const AdjacentGen* generator;
        int m_index;

        void operator++()
        {
            for(++m_index; m_index < 4; ++m_index)
            {   
                auto [row, col] = operator*();
                if (onBoard(row, col))
                {
                    break;
                }
            }
        }

        std::pair<int, int> operator*() const
        {
            constexpr int dx[] = { 1, -1, 0, 0 };
            constexpr int dy[] = { 0, 0, 1, -1 };
            int y = generator->m_row + dy[m_index];
            int x = generator->m_col + dx[m_index];

            return { y, x };
        }

        bool operator!=(const Iterator& it)
        {
            return m_index != it.m_index;
        }

    };

    Iterator begin() const
    {
        return {this, 0};
    }

    Iterator end() const
    {
        return {this, 4};
    }

    int m_row;
    int m_col;

};

#endif // ADJACENTGEN_H
