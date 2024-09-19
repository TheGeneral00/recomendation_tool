#ifndef NEW_GRAPH_H
#define NEW_GRAPH_H

#include <algorithm>
#include <list>
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
	vector<shared_ptr<Media>> mediaVector;
};

class Graph {
private:
    unordered_map<string, Node> nodes;

public:

    void addNode(const string& nodeName) {
        if(nodes.find(nodeName) == nodes.end()) {
            nodes[nodeName] = Node{nodeName, {}, {}};
            cout << "Added Node " << nodeName << " to the graph." << endl;
        }
    } 
    
    void addEdge(const string& genre1, const string& genre2, double weight = 0) {
        addNode(genre1);
        addNode(genre2);
        nodes.at(genre1).edges.push_back(make_pair(genre2, weight));
        nodes.at(genre2).edges.push_back(make_pair(genre1, weight));
        cout << "Added edge between " << genre1 << " and " << genre2 << " with weight " << weight << "." << endl;
    }

    void displayGraph() const {
        for(const auto& pair : nodes) {
            const Node& node = pair.second;
            cout << "Node: " << node.name << endl;

            cout << "Edges: " << endl;
            for(const auto& edge : node.edges) {
                cout << " -> " << edge.first << "(weight: " << edge.second << ")" << endl;
            }
            cout << "Media count: " << node.mediaVector.size() << endl;
            cout << endl;
        }
    }

    void modifyEdge(const string& genre1, const string& genre2, double newWeight) {
        if(nodes.find(genre1) != nodes.end() && nodes.find(genre2) != nodes.end()) {
            auto& edges = nodes.at(genre1).edges;
            bool edgeExistsGenre1 = false;
            for(auto& edge : edges) {
                if (edge.first == genre2) {
                    edge.second = newWeight;
                    edgeExistsGenre1 = true;
                    break;
                }
            }
            if(!edgeExistsGenre1) {
                edges.push_back(make_pair(genre2, newWeight));
            }

            auto& edgesGenre2 = nodes.at(genre2).edges;
            bool edgesExistsGenre2 = false;
            for (auto& edge : edgesGenre2) {
                if (edge.first == genre1) {
                    edge.second = newWeight;
                    edgesExistsGenre2 = true;
                    break;
                }
            }
            if(!edgesExistsGenre2) {
                edgesGenre2.push_back(make_pair(genre1, newWeight));
            }
            cout << "Modified edge between " << genre1 << " and " << genre2 << " to weight " << newWeight << " ." << endl;

        } else {
            cerr << "One or both of the nodes do not exist." << endl;
        }
    }

    void removeEdge(const string& genre1, const string& genre2) {
        if(nodes.find(genre1) != nodes.end()) {
            auto& edgesGenre1 = nodes.at(genre1).edges;
            auto itGenre1 = find_if(edgesGenre1.begin(), edgesGenre1.end(), [&genre2](const pair<string, double>& edge) {return edge.first == genre2; });
            if(itGenre1 != edgesGenre1.end()) {
                edgesGenre1.erase(itGenre1);
            } else {
                cerr << "Edge from " << genre1 << " to " << genre2 << " does not exist." << endl;
            }
        }

        if(nodes.find(genre2) != nodes.end()) {
            auto& edgesGenre2 = nodes.at(genre2).edges;
            auto itGenre2 = find_if(edgesGenre2.begin(), edgesGenre2.end(), [&genre1](const pair<string, double>& edge) {return edge.first == genre1; });
            if(itGenre2 != edgesGenre2.end()) {
                edgesGenre2.erase(itGenre2);
            } else {
                cerr << "Edge from " << genre2 << " to " << genre1 << " does not exist." << endl;
            }
        }
        cout << "Removed Edge between " << genre1 << " and " << genre2 << "." << endl;
    }

    double getWeight(const string& genre1, const string& genre2) {
        if (nodes.find(genre1) != nodes.end()) {
            auto& edges = nodes.at(genre1).edges;
            auto it = find_if(edges.begin(), edges.end(), [&genre2](const pair<string, double>& edge){
                return edge.first == genre2; 
            });
            if (it != edges.end()){
                return it->second;
            } else {
            cerr << "Edge between genre " << genre1 << " and " << genre2 << " was not found" << endl;
            return -1;
            }
        } else {
            cerr << "Node " << genre1 << " does not exist." << endl;
            return -1;
        }
    }

    void addMediaToGenre(const shared_ptr<Media>& media) {
        for (const string& genre : media->getGenres()) {
            // If the genre node doesn't exist, create it
            if (nodes.find(genre) == nodes.end()) {
                addNode(genre);
                cout << "Created new Node " << genre << "." << endl;
            }
        // Add the media to the genre's mediaVector
        nodes.at(genre).mediaVector.push_back(media);
        cout << "Added media " << media->getTitle() << " to " << genre << "." << endl;
        }
    }

    void removeMediaFromGenre(const shared_ptr<Media>& mediaToRemove) {
        // Loop through each genre that the media belongs to
        for (const string& genre : mediaToRemove->getGenres()) {
            // Check if the genre exists in the nodes map
            if (nodes.find(genre) != nodes.end()) {
                // Get a reference to the media vector for this genre
                vector<shared_ptr<Media>>& mediaVector = nodes.at(genre).mediaVector;

                // Iterate through the media vector to find the media to remove
                for (auto it = mediaVector.begin(); it != mediaVector.end();) {
                    // If the current media matches mediaToRemove, erase it from the vector
                    if (*it == mediaToRemove) {
                        it = mediaVector.erase(it);  // Erase and update the iterator
                        cout << "Removed media " << mediaToRemove->getTitle() << " from " << genre << "." << endl;
                    } else {
                        ++it;  // Only increment if no element was erased
                    }
                }
            }
        }
    }

    vector<shared_ptr<Media>> getMediaByGenre (const string& genre) const {
        if (nodes.find(genre) != nodes.end()){
            return nodes.at(genre).mediaVector;
        } else {
            cerr << "Node " << genre << " does not exist." << endl;
        }
    }

    bool hasNode(const string& genre) {
        if (nodes.find(genre) != nodes.end()){
            return true;
        }
        return false;
    }

    bool hasEdge(const string& genre1, const string& genre2, const double& weight) {
        if (hasNode(genre1) != true || hasNode(genre2) != true) {
            cerr << "Node " << genre1 << " and/or " << genre2 << " dont exist." << endl;
            return false;
        }
        auto& edges = nodes.at(genre1).edges;
        for(auto& edge : edges) {
            if (edge.first == genre2 && edge.second == weight) {
                return true;
            }
        }
        return false;
    }
};
#endif //NEW_GRAPH_H
