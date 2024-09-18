#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "new_graph.h"
#include <vector>

Test_Case("Graph is being tested", "[graph]") {
    
    Graph graph;

    REQUIRE(typeof(graph) == Graph);

    vector<string> genres = {"action", "comedy", "romance"}
    
    for (string genre : genres){
        graph.addNode(genre)
    }
    for (string genre : genres){
        REQUIRE(graph.nodes.find(genre) != nodes.end())
    }
}



