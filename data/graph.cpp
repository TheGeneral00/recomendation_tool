#include <vector>
#include <utility>
#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;

class Graph {

public: 
    //Adjacency list: maps each genre to a vector of pairs (connected genre and weigth)
    unordered_map<string, vector<pair< string, double>>> adjacencyList;

    //Add an edge to the between  to genres with a givenweigth
    void addEdge(const string genre1, const string genre2, const double weigth){
        adjacencyList[genre1].emplace_back(genre2, weigth)
        adjacencyList[genre2].emplace_back(genre1, weigth)
    }

    const vector<pair<string, double>> &  getNeighbors(const string& genre) const {
        return adjacencyList.at(genre)
    }

    //Modify weigths of the edges
    void modifyEdges(const string& genre1, const string& genre2, double newWeigth) {
        bool modified = false

        for(auto& neighbor: adjacencyList[genre1]){
            if (neighbor.first == genre2){
                neighbor.second = newWeight;
                modified = true;
                break;
            }
        }
        for (auto& neighbor: adjacencyList[genre2]){
            if (neighbor.second == genre1){
                neighbor.second = newWeight;
                modified = true;
                break;
            }
        }

        if(!modified){
            cout << "Edge between " << genre1 << " and " << genre2 << " not found." << endl;
        }
    }

    void printGraph() const {
        for (const auto& node : adjacencyList) {
            const string& genre = node.first;
            const auto& neighbors = node.second;
            cout << "Genre: " << genre << "\n";
            for (const auto& neighbor : neighbors){
                cout << "Connected to: " << neighbor.first << "with weight" << neigbor.second;
            } 
        }
    }
}
