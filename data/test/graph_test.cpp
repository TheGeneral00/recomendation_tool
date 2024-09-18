#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "new_graph.h"
#include <vector>
#include <string>

TEST_CASE("Graph is being tested", "[graph]") {
    
    Graph graph;

    std::vector<std::string> genres = {"action", "comedy", "romance"};

    SECTION("adding nodes") {
        // Add nodes to the graph
        for (const std::string& genre : genres) {
            graph.addNode(genre);  // Assuming addNode is a method in the Graph class
        }

        // Check if the nodes were added correctly
        for (const std::string& genre : genres) {
            REQUIRE(graph.hasNode(genre));  // Assuming hasNode is a method that checks for node existence
        }
    }
}

