#include <memory>
#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "graph.h"
#include <vector>
#include <string>
#include "movie.h"
#include "show.h"

TEST_CASE("Graph is being tested", "[graph]") {
    
    Graph graph; 

        std::vector<std::string> genres = {"action", "comedy", "romance"};
        // Add nodes to the graph
        for (const std::string& genre : genres) {
            graph.addNode(genre);  
        }

        // Check if the nodes were added correctly
        for (const std::string& genre : genres) {
            REQUIRE(graph.hasNode(genre));  
        }
        graph.displayGraph();
        graph.modifyEdge("action", "comedy", 0.3);
        graph.modifyEdge("action", "romance", 0.5);
        graph.modifyEdge("comedy", "romance");
        REQUIRE(graph.hasEdge("action", "romance", 0.5) == true);
        REQUIRE(graph.hasEdge("action", "comedy", 0.3) == true);
        REQUIRE(graph.hasEdge("comedy", "romance", 0) == true);
        REQUIRE(graph.getWeight("action", "romance") == 0.5);
        graph.modifyEdge("action", "romance", 0.45);
        REQUIRE(graph.hasEdge("action", "romance", 0.45));
        graph.removeEdge("action", "comedy");
        REQUIRE(graph.hasNode("action") == true);
        REQUIRE(graph.hasNode("comedy") == true);
        REQUIRE(graph.hasEdge("action", "comedy", 0) == false);
    
        Movie movieObj("The Jungle Book", {"children", "adventure"}, 105);
        Show showObj("The Office", {"sitcom", "comedy", "mockumentary"}, 4468, 188);

        graph.addMediaToGenre(std::make_shared<Movie>(movieObj));
        graph.addMediaToGenre(std::make_shared<Show>(showObj));

        graph.displayGraph();
        cout << endl;
        cout << endl;

        REQUIRE(graph.hasNode("children") == true);
        REQUIRE(graph.hasNode("sitcom") == true);

        graph.removeMediaFromGenre(std::make_shared<Movie>(movieObj));
        graph.removeMediaFromGenre(std::make_shared<Show>(showObj));

        graph.displayGraph();
    }

