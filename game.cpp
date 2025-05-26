#include "game.h"
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <climits>
#include <string>
#include <climits>
#include <cstring>

Game* Game::instance = nullptr;

///Functie de resetare a pachetului si a jucatorului
void Game :: resetGame()
{
    deck -> reset();
    if (currPlayer != nullptr)
    {
        currPlayer -> incrementFails();
        currPlayer -> reset();
    }
}

///Functie de start a jocului
void Game :: start()
{
    currPlayer = nullptr;
    resetGame();
    deck -> reset();
    players.clear();

    std::cout<<"Introdu numarul de jucatori: \n";
    int nrPlayers;
    std::cin>>nrPlayers;
    if (nrPlayers < 1 and nrPlayers >=0)
        std::cout<<"Jocul trebuie sa contina minim 1 jucator\n";
    for (int i=0; i<nrPlayers; i++)
    {
        ///crearea unui jucator
        std::string name;
        std::cout<<"Nume jucatorul "<<i+1<<": ";
        std::cin>>name;

        Player p;
        if (f[name] == 0)
            p.setName(name),f[name] = 1;
        else
        {
            while (1)
            {
                std::cout<<"Numele a fost deja folosit. Numele nou: ";
                std::cin>>name;
                if (!f[name])
                {
                    p.setName(name);
                    f[name] = 1;
                    break;
                }
            }
        }


        players.push_back(p);

    }
    while (1)
    {
        std::cout<<"\nFiecare jucator trage cate o carte. Cel cu cartea ce mai mica va intra in corabie\n";

        int minim = 15, ind = -1;

        for (int i=0; i<nrPlayers; i++)
        {
            Card c = deck -> draw();
            players[i].addCard(c);

            std::cout<<players[i].getName()<<" a extras cartea: "<<c.toString()<<'\n';

            if (c.getValue() <= minim)
            {
                minim = c.getValue();
                currPlayer = &players[i];
                players[i].deleteCards();
            }
        }

        std::cout<<currPlayer -> getName()<<" a intrat in corabie!\n";

        bool won = false;
        while (!won)
        {
            if (!level1())
            {
                resetGame();
                continue;
            }

            if (!level2())
            {
                resetGame();
                continue;
            }

            if (!level3())
            {
                resetGame();
                continue;
            }

            if (!level4())
            {
                resetGame();
                continue;
            }
            won = true;
        }
        std::cout<<currPlayer -> getName()<<" a iesit din corabie dupa "<<currPlayer -> getFails()<<" incercari.\n";

        std::string raspuns;
        std::cout<<"\nVreti sa continuati jocul? (da/nu): ";
        std::cin>>raspuns;
        if (raspuns != "da" and raspuns != "DA" and raspuns != "Da")
            break;
    }
}

bool Game :: level1()
{
    std::string choise="";
    std::cout<<"\nNivelul 1: Ghiceste culoarea cartii: ";
    std::cin>>choise;

    /*while (choise!="red" or choise!="black")
    {
        std::cout<<"Culoare invalida! Introdu o culoare valida: ";
        std::cin>>choise;
        if (choise=="red" or choise=="black")
            break;
    }*/

    Card c = deck -> draw();
    currPlayer -> addCard(c);

    std::cout<<"Ai extras: "<<c.toString()<<" - "<<c.getColor() << '\n';

    if (choise == c.getColor())
    {
        currPlayer -> advanceLevel();
        return true;
    }

    std::cout<<"Ai gresit! - Esti in corabie de: "<<currPlayer -> getFails()<<" runde.\n";
    return false;
}

bool Game::level2()
{
    std::string choise;
    std::cout<<"\nNivelul 2: Mai mare sau mai mica decat cartea anterioara (mare/mic): ";
    std::cin>>choise;
    std::cin.ignore(INT_MAX, '\n');

    Card prev = currPlayer -> getCards()[currPlayer -> getCards().size() - 1];
    Card c = deck -> draw();
    currPlayer -> addCard(c);

    std::cout<<"Ai extras: "<<c.toString()<<"\n";

    if ((choise == "mare" and c.getValue() >= prev.getValue()) or (choise == "mic" and c.getValue() <= prev.getValue()))
    {
        currPlayer -> advanceLevel();
        return true;
    }

    std::cout<<"Ai gresit! - Esti in corabie de: "<<currPlayer -> getFails()<<" runde.\n";
    return false;
}

bool Game::level3()
{
    std::string choise;
    std::cout<<"\nNivelul 3: Intre sau in afara cartilor extrase (intre/afara): ";
    std::cin>>choise;
    std::cin.ignore(INT_MAX, '\n');

    /*while (choise!="mare" or choise!="mic")
    {
        std::cout<<"Alegere invalida! Introdu o alegere valida: ";
        std::cin>>choise;
        if (choise=="mare" or choise=="mic")
            break;
    }*/

    Card c1 = currPlayer -> getCards()[currPlayer -> getCards().size() - 2];
    Card c2 = currPlayer -> getCards()[currPlayer -> getCards().size() - 1];
    Card c = deck -> draw();

    int mi = std::min(c1.getValue(), c2.getValue());
    int ma = std::max(c1.getValue(), c2.getValue());
    std::cout<<mi<<" "<<ma<<'\n';
    int val = c.getValue();

    std::cout<<"Ai extras: "<<c.toString()<<"\n";

    if (choise == "afara" and ((1 < val and val < mi) or (val > ma and val < 15)))
    {
        currPlayer -> advanceLevel();
        return true;
    }
    else if (choise == "intre" and (mi < val and val < ma))
    {
        currPlayer -> advanceLevel();
        return true;
    }
    else
    {
        std::cout<<"Ai gresit! - Esti in corabie de: "<<currPlayer -> getFails()<<" runde.\n";
        return false;
    }
}

bool Game::level4()
{
    std::string choise;
    std::cout<<"\nNivelul 4: Ghiceste simbolul (Hearts, Diamonds, Clubs, Spade): ";
    std::cin>>choise;
    std::cin.ignore(INT_MAX, '\n');

    Card c = deck -> draw();

    std::cout<<"Ai extras: "<<c.toString()<<"\n";

    if (c.getSuit() == choise)
    {
        currPlayer -> advanceLevel();
        return true;
    }

    std::cout<<"Ai gresit! - Esti in corabie de: "<<currPlayer -> getFails()<<" runde.\n";
    return false;
}



