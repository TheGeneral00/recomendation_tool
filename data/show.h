#ifndef SHOW_H
#define SHOW_H

#include "movie.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Show: public Movie {

    private:
        int numberOfEpisodes;

    public:
        //Constructor
        Show(const string& title, const vector<string>& genres, double length, int numberOfEpisodes)
            : Movie(title, genres, length), numberOfEpisodes(numberOfEpisodes) {}    	

    int getNumberOfEpisodes() const {return numberOfEpisodes;}

	void setNumberOfEpisodes(int newNumberOfEpisodes) { numberOfEpisodes = newNumberOfEpisodes; }

	void printDetails() const override {
		Movie::printDetails();//call base class printDetails
		cout << "Number of Episodes: " << numberOfEpisodes << endl;
	}
};

#endif //SHOW_H 
