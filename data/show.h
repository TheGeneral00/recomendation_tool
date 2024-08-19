#ifndef SHOW_H
#define SHOW_H

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
        Show(const string& title, const vector<string>& genres, double length)
            :Movie(title, genres), length(length), numberOfEpisodes(numberOfEpisodes) {}    	

        double getLength() const {return length;}

        int getNumberOfEpisodes() const {return numberOfEpisodes;}
}
#endif