#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "deck.h"
#include "player.h"
#include "ScoreSystem.h"

class Game
{
private:
    static Game *instance;
    Deck *deck = Deck::getInstance();
    std::vector <Player> players;
    std::unordered_map <std::string, int> f;
    Player* currPlayer;

    ///Constructor privat pentru a preveni instantierea directa
    Game() : currPlayer(nullptr) {
        resetGame();
    }
public:

    ///Metoda statica pentru a obtine instanta unica a jocului
    static Game* getInstance() {
        if (instance == nullptr) {
            instance = new Game();
        }
        return instance;
    }

    ///Prevenirea copierei si a atribuiri instantei
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    ///Functie de resetare a pachetului si a jucatorului
    void resetGame();

    ///Functie de start a jocului
    void start();

    ///Nivelul 1
    bool level1();

    ///Nivelul 2
    bool level2();

    ///Nivelul 3
    bool level3();

    ///Nivelul 4
    bool level4();

};
