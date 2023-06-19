#pragma once
#include <iostream>
#include <cmath>
#include "matrix.hpp"
#include <limits>

#define INFINITY_VALUE  1000000
#define NEG_INFINITY_VALUE  -1000000

class Game
{
private:
    int board_size;
    int recursion_depth;
    int count_to_win;
    Matrix game_board;
    int last_field;
    int last_row;
    int last_col;
public:
    Game(int size, int count, int depth) : game_board(size,size), count_to_win(count), recursion_depth(depth)
    {
        board_size = size;
        last_field=0;
    }
    void printGameBoard(int turn);

    void setX(int Row, int Col){game_board.setElement(Row,Col,1); last_field=1; last_row=Row; last_col=Col;};
    void setO(int Row, int Col){game_board.setElement(Row,Col,-1); last_field=-1; last_row=Row; last_col=Col;};

    bool ifBusy(int row, int col);
    int winCheck();
    int evaluateBoard(); 
    int minMax(int depth, int player, int alpha, int beta);
    void makeMove();



};

void Game::printGameBoard(int turn)
{
    char frame_char_x = char(196);
    char frame_char_y = char(179);
    char cross_char = char(197);
    char X_char = 'X';
    char O_char = 'O';
    char nothing_char = ' ';

    if(turn == 1){std::cout << " " << X_char << " ";}
    else if(turn == -1){std::cout << " " << O_char << " ";}
    else if(turn == 0){std::cout << "   ";}
    
    for(int i = 0; i < board_size; i++)
    {
        std::cout << frame_char_y<<" "<<i+1;
        if(i < 9){std::cout << " ";}
    }
    std::cout <<frame_char_y<<"\n"<<frame_char_x<<frame_char_x<<frame_char_x;
    for(int i = 0; i < board_size  ; i++)
    {
        std::cout << cross_char<< frame_char_x <<frame_char_x<<frame_char_x;
    }
    std::cout <<cross_char<<"\n";
    
    for(int row = 0; row < board_size; row++ )
    {   
        std::cout <<" " << row + 1;
        if(row < 9){std::cout << " ";}
        
        std::cout << frame_char_y;
        for(int col = 0; col < board_size; col++)
        {
           
            switch (game_board.getElement(row,col))
            {
            case -1:
                std::cout << " "<< O_char << " " << frame_char_y;
                break;

            case 0:
                std::cout << "   " << frame_char_y;
                break;

            case 1:
                std::cout << " "<< X_char << " " << frame_char_y;
                break;
            default:
                break;
            }


           
            
        }
        std::cout <<"\n" << frame_char_x <<frame_char_x<< frame_char_x;
    for(int i = 0; i < board_size  ; i++)
    {
        std::cout << cross_char<< frame_char_x <<frame_char_x<<frame_char_x;
    }
    std::cout <<cross_char<<"\n";
    

    }
    
    
}



bool Game::ifBusy(int row, int col)
{
    if(game_board.getElement(row,col) != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}




int Game::winCheck() {
    int rows = game_board.getRows();
    int cols = game_board.getCols();

    // Sprawdzenie wygranej w wierszach
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= cols - count_to_win; j++) {
            int sum = 0;
            for (int k = 0; k < count_to_win; k++) {
                sum += game_board.getElement(i, j + k);
            }
            if (sum == count_to_win) {
                return 1; // Wygrał X (krzyżyk)
            } else if (sum == -count_to_win) {
                return -1; // Wygrało O (kółko)
            }
        }
    }

    // Sprawdzenie wygranej w kolumnach
    for (int j = 0; j < cols; j++) {
        for (int i = 0; i <= rows - count_to_win; i++) {
            int sum = 0;
            for (int k = 0; k < count_to_win; k++) {
                sum += game_board.getElement(i + k, j);
            }
            if (sum == count_to_win) {
                return 1; // Wygrał X (krzyżyk)
            } else if (sum == -count_to_win) {
                return -1; // Wygrało O (kółko)
            }
        }
    }

    // Sprawdzenie wygranej na przekątnych
    for (int i = 0; i <= rows - count_to_win; i++) {
        for (int j = 0; j <= cols - count_to_win; j++) {
            int sum_1 = 0;
            int sum_2 = 0;
            for (int k = 0; k < count_to_win; k++) {
                sum_1 += game_board.getElement(i + k, j + k);
                sum_2 += game_board.getElement(i + k, j + count_to_win - 1 - k);
            }
            if (sum_1 == count_to_win || sum_2 == count_to_win) {
                return 1; // Wygrał X 
            } else if (sum_1 == -count_to_win || sum_2 == -count_to_win) {
                return -1; // Wygrało O 
            }
        }
    }

    return 0; 

}



int Game::evaluateBoard() {
    int rows=game_board.getRows();
    int cols=game_board.getCols();
    int win_value=last_field;

    int win_counter=1;

    

        for(int y=1;y<cols;y++)
        {
            if(game_board.getElement(last_row+y,last_col+y)==last_field)
            {
                win_counter++;
            }
            else
            {
                break;
            }
        }

        for(int y=1;y<cols;y++)
        {
            if(game_board.getElement(last_row-y,last_col-y)==last_field)
            {
                win_counter++;
            }
            else
            {
                break;
            }
        }


        if(win_counter>=count_to_win)
        {
            return win_value;
        }


    {
        win_counter=1;

        for(int y=1;y<cols;y++)
        {
            if(game_board.getElement(last_row+y,last_col-y)==last_field)
            {
                win_counter++;
            }
            else
            {
                break;
            }
        }

        for(int y=1;y<cols;y++)
        {
            if(game_board.getElement(last_row-y,last_col+y)==last_field)
            {
                win_counter++;
            }
            else
            {
                break;
            }
        }


        if(win_counter>=count_to_win)
        {
            return win_value;
        }


    }


    win_counter=1;

    

    for(int y=last_col-1;y>=0;y--)
    {

        if(game_board.getElement(last_row,y)==last_field)
        {
            win_counter++;
        }
        else
        {
            break;
        }

    }

    

    for(int y=last_col+1;y<rows;y++)
    {

        if(game_board.getElement(last_row,y)==last_field)
        {
            win_counter++;
        }
        else
        {
            break;
        }

    }

    if(win_counter>=count_to_win)
    {
        return win_value;
    }


     win_counter=1;

    

    for(int x=last_row-1;x>=0;x--)
    {

        if(game_board.getElement(x,last_col)==last_field)
        {
            win_counter++;
        }
        else
        {
            break;
        }

    }

    

    for(int x=last_row+1;x<rows;x++)
    {

        if(game_board.getElement(x,last_col)==last_field)
        {
            win_counter++;
        }
        else
        {
            break;
        }

    }

    if(win_counter>=count_to_win)
    {
        return win_value;
    }



    return 0;
}






int Game::minMax(int depth, int player, int alpha, int beta) {
    int result = evaluateBoard();
    if (result != 0 || depth == 0 || game_board.isFull()) {
        return result;
    }

    if (player == 1) {
        int bestScore = NEG_INFINITY_VALUE;
        for (int i = 0; i < board_size; i++) {
            for (int j = 0; j < board_size; j++) {
                if (!ifBusy(i, j)) {
                    setX(i, j);
                    bestScore = std::max(minMax(depth - 1, -player, alpha, beta),bestScore);
                    alpha=std::max(alpha,bestScore);
                    game_board.setElement(i, j, 0);
                    if (alpha>=beta) {
                        return alpha;
                    }
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = INFINITY_VALUE;
        for (int i = 0; i < board_size; i++) {
            for (int j = 0; j < board_size; j++) {
                if (!ifBusy(i, j)) {
                    setO(i, j);
                    bestScore = std::min(minMax(depth - 1, -player, alpha, beta),bestScore);
                    beta=std::min(bestScore,beta);
                    game_board.setElement(i, j, 0);
                    if (beta <= alpha) {
                        return beta;
                    }
                }
            }
        }
        return bestScore;
    }
}




void Game::makeMove() {
    int bestScore = INFINITY_VALUE;
    int bestRow = -1;
    int bestCol = -1;

    int alpha = NEG_INFINITY_VALUE;
    int beta = INFINITY_VALUE;

    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (!ifBusy(i, j)) {
                setO(i, j);
                int score = minMax(recursion_depth, 1, alpha, beta);
                if (score < bestScore) {
                    bestScore = score;
                    bestRow = i;
                    bestCol = j;
                }
                game_board.setElement(i, j, 0);
            }
        }
    }

    if (bestRow != -1 && bestCol != -1) {
        setO(bestRow, bestCol);
    }
}
