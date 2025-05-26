#pragma once
#include <vector>
#include <string>
#include "card.h"

class Deck
{
private:
    static Deck* instance;
    std::vector <Card> cards;

    /// Constructor privat
    Deck()
    {
        reset();
    }
public:

    ///Metoda statica pentru a obtine instanta unica a pachetului de carti
    static Deck* getInstance() {
        if (instance == nullptr) {
            instance = new Deck();
        }
        return instance;
    }

    ///Prevenirea copierei si a atribuiri instantei
    Deck(const Deck&) = delete;
    Deck& operator=(const Deck&) = delete;

    ///Functie de restare a pachetului de carti
    void reset();

    ///Functie pentru afisarea pachetului
    void showCards();

    ///Functie de amestecare a cartilor
    void shuffle();

    ///Functie de alegere a unei carti random din pachet
    Card draw();
};
