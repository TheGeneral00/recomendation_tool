#ifndef NEW_GRAPH_H
#define NEW_GRAPH_H

#import "media.h"
#import "movie.h"
#import "show.h"

#include <cstddef>
#include <fstream>
#include <memory>
#include <vector>
#include <utility>
#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;

struct Node {
	string name;
	vector<pair<string, double>> edges;
	list<Media> mediaList;
};

class Graph {
private:
	unordered_map<string, Node*> nodes;

	public:


};



#endif NEW_GRAPH_H
