#ifndef GRAPH_H
#define GRAPH_H

#include <cstddef>
#include <fstream>
#include <memory>
#include <vector>
#include <utility>
#include <unordered_map>
#include <string>
#include <iostream>

#include "media.h"
#include "movie.h"
#include "show.h"

using namespace std;

struct Node {
	string name;
	vector<pair<string, double>> edges;
};

class Graph {

private: 
    //Adjacency list: maps each genre to a vector of pairs (connected genre and weigth)
    unordered_map<string, vector<pair< string, double>>> adjacencyList;

    unordered_map<string,vector<shared_ptr<Media>>> genreMedia;

    friend void saveGraphToBinary(const Graph &graph, const string &filename);
    friend void loadGraphFromBinary(Graph& graph, const string& filename);

public:
    //Add an edge between to genres with a given weigth
    void addEdge(const string genre1, const string genre2, const double weight){
        adjacencyList[genre1].emplace_back(genre2, weight);
        adjacencyList[genre2].emplace_back(genre1, weight);
    }
    //returns a vector of neighbors 
    const vector<pair<string, double>>& getNeighbors(const string& genre) const {
        return adjacencyList.at(genre);
    }

    //Modify weigths of the edges
    void modifyEdges(const string& genre1, const string& genre2, double newWeight) {
        bool modified = false;
	//modify edges for node
        for(auto& neighbor: adjacencyList[genre1]){
            if (neighbor.first == genre2){
                neighbor.second = newWeight;
                modified = true;
                break;
            }
        }
	//modify edges of neighbor nodes 
        for (auto& neighbor: adjacencyList[genre2]){
            if (neighbor.first == genre1){
                neighbor.second = newWeight;
                modified = true;
                break;
            }
        }
        if(!modified){
            cout << "Edge between " << genre1 << " and " << genre2 << " not found." << endl;
        }
    }
    //returns the weight of a specified edge
    double getWeight(const string& genre1, const string& genre2) const {
        auto it = adjacencyList.find(genre1);
        if (it != adjacencyList.end()){
            const auto& neighbors = it->second;
            for (const auto& neighbor: neighbors){
                if (neighbor.first == genre2){
                    return neighbor.second;
                }
            }
        }
        return -1;
    }
    //prints the existing graph to the console
    void printGraph() const {
        for (const auto& node : adjacencyList) {
            const string& genre = node.first;
            const auto& neighbors = node.second;
            cout << "Genre: " << genre << "\n";
            for (const auto& neighbor : neighbors){
                cout << "Connected to: " << neighbor.first << " with weight " << neighbor.second;
            } 
        }
    }
    //adds new entry to the vector storing the movies belonging to the genre
    void addMediaToGenre(const shared_ptr<Media>& media){
	    for (const string& genre : media->getGenres()) {
		    genreMedia[genre].push_back(media);
	    }
    }
    //return a vector containing pointers to the genreMedia vector of specified genre
    vector<shared_ptr<Media>> getMediaByGenre(const string& genre) const {
        auto it = genreMedia.find(genre);
        if (it != genreMedia.end()){
            return it->second;
        } else {
            return {};
        }
    }

    void  saveToBinary(const string& filename) {
	    ofstream outFile(filename, ios::binary);
	    size_t nodeCount = node.size()
	    outFile.write(reinterpret_cast<char*>(&nodeCount), sizeof(nodeCount));

	    for (const auto& nodePair : nodes) {

	    }
    }
};

#endif // GRAPH_H
