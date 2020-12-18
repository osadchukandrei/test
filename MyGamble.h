#pragma once
#include <string>
#include <map>
#include <time.h>
#include <stdlib.h>

class MyGamble {
public:
    MyGamble() {
        srand(time(NULL));
        number = rand();
    };
    ~MyGamble();
    void MakePrediction(std::string user_name, int prediction);
    void NameWinner();
private:
    int  number = 0;
    std::multimap<std::string, int> mp_players;
};
