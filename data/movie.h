#ifndef MOVIE_H
#define MOVIE_H

#include <vector>
#include <iostream>
#include <string>

using namespace std;

class movie
{
private:
    string title;
    vector<string> genres;

pubic:
    //Constructor
    Film(const string& title, const vector<string>& genres)
    : title(title), genres(genres) {}

    string getTitle() const {return title;}

    vector<string> getGenres() const {return genres; }

#endif
