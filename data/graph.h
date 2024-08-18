#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;

class Graph {

private: 
    //Adjacency list: maps each genre to a vector of pairs (connected genre and weigth)
    unordered_map<string, vector<pair< string, double>>> adjacencyList;

public:
    //Add an edge to the between  to genres with a givenweigth
    void addEdge(const string genre1, const string genre2, const double weight){
        adjacencyList[genre1].emplace_back(genre2, weight);
        adjacencyList[genre2].emplace_back(genre1, weight);
    }

    const vector<pair<string, double>>& getNeighbors(const string& genre) const {
        return adjacencyList.at(genre);
    }

    //Modify weigths of the edges
    void modifyEdges(const string& genre1, const string& genre2, double newWeight) {
        bool modified = false;

        for(auto& neighbor: adjacencyList[genre1]){
            if (neighbor.first == genre2){
                neighbor.second = newWeight;
                modified = true;
                break;
            }
        }
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

    void getWeight(const string& genre1, const string& genre2) const {
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
};

#endif // GRAPH_H
