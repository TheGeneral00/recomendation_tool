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

#import "media.h"
#import "movie.h"
#import "show.h"

using namespace std;

struct Node {
	string name;
	vector<pair<string, double>> edges;
	list<Media> mediaList;
};

class Graph {
private:
    unordered_map<string, Node> nodes;

public:

    void addNode(const string& nodeName) {
        if(nodes.find(nodeName) == nodes.end()) {
            nodes[nodeName] = Node{nodeName, {}, {}};
        }
    } 
    
    void addEdge(const string& from, const string& to, double weight) {
        addNode(from);
        addNode(to);
        nodes[from].edges.push_back(make_pair(to, weight));
        nodes[to].edges.push_back(make_pair(from, weight));
    }

    void addMedia(const string& nodeName, const Media& media) {
        if(nodes.find(nodeName) != nodes.end()) {
            nodes[nodeName].mediaList.push_back(media);
        } else {
            cerr << "Node " << nodeName << " does not exist." << endl;
        }
    }

    void displayGraph() const {
        for(const auto& pair : nodes) {
            const Node& node = pair.second;
            cout << "Node: " << node.name << endl;

            cout << "Edges: " << endl;
            for(const auto& edge : node.edges) {
                cout << " -> " << edge.first << "(weight: " << edge.second << ")" << endl;
            }
            cout << "Media count: " << node.mediaList.size() << endl;
            cout << endl;
        }
    }

    void modifyEdge(const string& genre1, const string& genre2, double newWeight) {
        if(nodes.find(genre1) != nodes.end() && nodes.find(genre2) != nodes.end()) {
            auto& edges = nodes[genre1].edges;
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

            auto& edgesGenre2 = nodes[genre2].edges;
            bool edgesExistsGenre2 = false;
            for (auto& edge : edgesGenre2) {
                if (edge.first == genre1) {
                    edge.second = newWeight;
                    break;
                }
            }
            if(!edgesExistsGenre2) {
                edgesGenre2.push_back(make_pair(genre1, newWeight));
            }

        } else {
            cerr << "One or both of the nodes do not exist." << endl;
        }
    }

    void removeEdge(const string& genre1, const string& genre2) {
        if(nodes.find(genre1) != nodes.end()) {
            auto& edgesGenre1 = nodes[genre1].edges;
            auto itGenre1 = find_if(edgesGenre1.begin(), edgesGenre1.end(), [&genre2](const pair<string, double>& edge) {return edge.first == genre2; });
            if(itGenre1 != edgesGenre1.end()) {
                edgesGenre1.erase(itGenre1);
            } else {
                cerr << "Edge from " << genre1 << " to " << genre2 << " does not exist." << endl;
            }
        }

        if(nodes.find(genre2) != nodes.end()) {
            auto& edgesGenre2 = nodes[genre2].edges;
            auto itGenre2 = find_if(edgesGenre2.begin(), edgesGenre2.end(), [&genre1](const pair<string, double>& edge) {return edge.first == genre1; });
            if(itGenre2 != edgesGenre2.end()) {
                edgesGenre2.erase(itGenre2);
            } else {
                cerr << "Edge from " << genre2 << " to " << genre1 << " does not exist." << endl;
            }
        }
    }
};



#endif //NEW_GRAPH_H
