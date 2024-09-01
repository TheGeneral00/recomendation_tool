#ifndef SHOW_H
#define SHOW_H

#include "movie.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Show: public Movie {

    private:
        double length; //length in hours
        int numberOfEpisodes;

    public:
        //Constructor
        Show(const string& title, const vector<string>& genres, double length, int numberOfEpisodes)
            :Movie(title, genres), length(length), numberOfEpisodes(numberOfEpisodes) {}    	

        double getLength() const {return length;}

        int getNumberOfEpisodes() const {return numberOfEpisodes;}
};
#endif
