#ifndef MOVIE_H
#define MOVIE_H

#include <vector>
#include <iostream>
#include <string>
#include "media.h"

using namespace std;

class Movie : public Media{
private:
    vector<string> genres;
    double length; //length in hours

public:
    //Constructor
    Movie(const string& title, const vector<string>& genres, const double& length)
    : Media(title), genres(genres), length(length) {}

    vector<string> getGenres() const override { return genres; }

    double getLength() const { return length; }

    void setLength(double newLength) { length = newLength; }

    void printDetails() const override {
	    cout << "Movie: " << title << endl;
	    cout << "Genres: ";
	    for (const auto& genre : genres) {
		    cout << genre << " ";
	    }
	    cout << endl;
	    if (length > 0) {
		    cout << "Length: " << length << " hours" << endl;
	    }
    }
};
#endif
