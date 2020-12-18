#include "MyGamble.h"
#include <utility>

MyGamble::~MyGamble()
{
}

void MyGamble::MakePrediction(std::string user_name, int prediction)
{
	mp_players.insert(make_pair(user_name, prediction));
}

void MyGamble::NameWinner()
{

}
