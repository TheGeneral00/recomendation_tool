#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "new_graph.h"
#include <vector>
#include <string>
#include "movie.h"
#include "show.h"

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
    SECTION("adding and modifying edges"){
        graph.addEdge("action", "comdey", 0.3);
        graph.addEdge("action", "romance", 0.5);
        graph.addEdge("comedy", "romance");
        REQUIRE(graph.hasEdge("action", "romance", 0.5) == true);
        REQUIRE(graph.hasEdge("action", "comedy", 0.3) == true);
        REQUIRE(graph.hasEdge("comedy", "romance", 0) == true);
        REQUIRE(graph.getWeight("action", "romance") == 0.5)
        graph.modifyEdge("action", "romance", 0.45);
        REQUIRE(graph.hasEdge("action", "romance", 0.45));
    }
    SECTION("removing Edges"){
        graph.removeEdge("action", "comedy");
        REQUIRE(graph.hasEdge("action", "comedy") == false);
    }
    SECTION("adding and removing Media to a Node"){
        Movie movieObj("The Jungle Book", {"children", "adventure"}, 105);
        Show showObj("The Office", {"sitcom", "comedy", "mockumentary"}, 4468, 188);
    }
}

