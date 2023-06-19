#include<iostream>
#include <cstdlib> 
#include <ctime>
#include "matrix.hpp"
#include "game.hpp"
#include <chrono>


int main()
{
    int size, depth, count;
    int x, y;
    std::cout << "Podaj rozmiar planszy, ilosc znakow w rzedzie do wygranej oraz glebokosc rekurencji: \n";
    std::cin >> size >> count >> depth;
    while(size < 2)
    {
        std::cout << "Wielkosc planszy musi byc conajmniej 2!!!\nPodaj ten parametr jeszcze raz!\n";
        std::cin >> size;
    }
    while(count > size)
    {
        std::cout << "ilosc znakow w rzedzie do wygranej nie moze byc wieksza od wielkosci planszy!!!\nPodaj ten parametr jeszcze raz!\n";
        std::cin >> count;
    }
    while(count < 2)
    {
        std::cout << "ilosc znakow w rzedzie do wygranej musi wynosic conajmniej 2!!!\nPodaj ten parametr jeszcze raz!\n";
        std::cin >> count;
    }
    while(depth < 1)
    {
        std::cout << "Glebokosc rekurencji musi byc wieksza od 0\nPodaj ten parametr jeszcze raz!\n";
        std::cin >> depth;
    }

    Game plansza(size, count, depth);
    int turn, win = 0, rounds = 0;
    double last_O_move_time = 0;
    bool opponent_played = false;
    

    std::srand(std::time(nullptr));

    int randomNum = std::rand() % 2;
    turn = (randomNum == 0) ? -1 : 1;
    

    for (int i = 0; i < size * size; i++)
    {
        turn = turn * -1;

        system("cls");
        std::cout << "Warunki gry: " << std::endl;
        std::cout << "Rozmiar planszy: "<< size  << "\nilosc znakow w rzedzie do wygranej: "<< count << "\nglebokosc rekurencji: "<< depth << "\n"<<std::endl;
        if(opponent_played == true){
        std::cout << "Przeciwnik myslal przez: " << last_O_move_time  << "sekund\n"  << std::endl;
        }
        std::cout << "Tura nr: " << i + 1 << "\n\n" << std::endl;
        plansza.printGameBoard(turn);

        if (turn == -1)
        {
            auto start = std::chrono::high_resolution_clock::now();
            std::cout << "Przeciwnik mysli..." << std::endl;
            plansza.makeMove();
            opponent_played = true;
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            last_O_move_time = duration/1000000;
        }
        else
        {
            std::cout << "Ruch X\n" << "Podaj wiersz i kolumne:";
            std::cin >> x;
            if(x == 99)
            {
                std::cout << "Gra zostala przerwana w "<< i + 1 <<" turze"<< std::endl;
                exit(0);
            }
            std::cin >> y;

            while (plansza.ifBusy(x - 1, y - 1))
            {
                std::cout << "To miejsce jest juz zajete! Sprobuj jeszcze raz\n Podaj wiersz i kolumne: ";
                std::cin >> x >> y;
            }
            while (x > size || y > size || x < 1 || y < 1)
            {
                std::cout << "Nieprawidlowy wybor wiersza lub kolumny! Sprobuj jeszcze raz\n Podaj wiersz i kolumne: ";
                std::cin >> x >> y;
            }

            plansza.setX(x - 1, y - 1);
            opponent_played = false;
        }

        int check=plansza.evaluateBoard();
        
        if (check!=0)
        {
            win = check;
            break;
        }
        rounds = i+1;
    }
    system("cls");
    std::cout << "Warunki gry: " << std::endl;
        std::cout << "Rozmiar planszy: "<< size  << "\nilosc znakow w rzedzie do wygranej : "<< count << "\nglebokosc rekurencji : "<< depth << "\n"<<std::endl;
        if(opponent_played == true){
        std::cout << "Przeciwnik myslal przez: " << last_O_move_time  << "sekund\n"  << std::endl;
        }
        
    plansza.printGameBoard(0);
    if (win == 1)
    {
        std::cout << "Wygral krzyzyk w " << rounds << " turze!!!"  << std::endl;
    }
    if (win == 0)
    {
        std::cout << "Remis w " << rounds << " turze!!!"  << std::endl;
    }
    if (win == -1)
    {
        std::cout << "Wygralo kolko w " << rounds << " turze!!!"  << std::endl;
    }

    return 0;
}
