#pragma once
#include <vector>
#include <iostream>

class Matrix {
private:
    int rows;            // liczba wierszy
    int cols;            // liczba kolumn
    std::vector<std::vector<int>> data;    // wektor przechowujący macierz
    int occupied_fields;

public:
    // Konstruktor
    
    Matrix(int numRows, int numCols) : rows(numRows), cols(numCols) 
    {
        data.resize(rows, std::vector<int>(cols, 0));
        occupied_fields=0;
    }

    void setElement(int row, int col, int value);  
    int getElement(int row, int col);
    void print();

    bool isFull()
    {
        return occupied_fields==rows*cols;
    }

    int getRows() {
        return data.size();
    }

    int getCols() {
        return data[0].size();
    }
};




void Matrix::setElement(int row, int col, int value) {
        if (row >= 0 && row < rows && col >= 0 && col < cols) {

            if(data[row][col]==0 && value!=0)
            {
                occupied_fields++;
            }
            else if(data[row][col]!=0 && value==0)
            {
                occupied_fields--;
            }

            data[row][col] = value;
        } else {
            //std::cout << "Błąd: Nieprawidłowe indeksy wiersza lub kolumny!" << std::endl;
        }
    }

 int Matrix::getElement(int row, int col){
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            return data[row][col];
        } else {
            //std::cout << "Błąd: Nieprawidłowe indeksy wiersza lub kolumny!" << std::endl;
            return 0;  // Zwracamy zero w przypadku błędu
        }
    }

void Matrix::print(){
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

