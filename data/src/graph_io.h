#ifndef GRAPH_IO_H
#define GRAPH_IO_H

#include "graph.h"
#include <cstddef>
#include <fstream>
#include <memory>

using namespace std;

void saveGraphToBinary(const Graph& graph, const string& filename) {
    ofstream file(filename, ios::binary);
    if(!file) {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }

    //write adjacency list
    size_t adjSize = graph.adjacencyList.size();
    file.write(reinterpret_cast<const char*>(&adjSize), sizeof(adjSize));
    for(const auto& entry : graph.adjacencyList) {
        size_t keySize = entry.first.size();
        file.write(reinterpret_cast<const char*>(&keySize), sizeof(keySize));
        file.write(entry.first.c_str(), keySize);

        size_t neighborSize = entry.second.size();
        file.write(reinterpret_cast<const char*>(&neighborSize), sizeof(neighborSize));
        for (const auto& neighbor : entry.second) {
            size_t neighborKeySize = neighbor.first.size();
            file.write(reinterpret_cast<const char*>(&neighborKeySize), sizeof(neighborKeySize));
            file.write(neighbor.first.c_str(), neighborKeySize);
            file.write(reinterpret_cast<const char*>(&neighbor.second), sizeof(neighbor.second));
        }
    }
    
    //Write Media data
    size_t mediaSize = graph.genreMedia.size();
    file.write(reinterpret_cast<const char*>(&mediaSize), sizeof(mediaSize));
    for (const auto& entry : graph.genreMedia) {
        size_t genreSize = entry.first.size();
        file.write(reinterpret_cast<const char*>(&genreSize), sizeof(genreSize));
        file.write(entry.first.c_str(), sizeof(genreSize));

        size_t mediaListSize = entry.second.size();
        file.write(reinterpret_cast<const char*>(&mediaListSize), sizeof(mediaListSize));
        for(const auto& media : entry.second) {
            //Serialize media objects
            const Movie* movie = dynamic_cast<const Movie*>(media.get());
            if(movie) {
                char type = 'M';
                file.write(&type, sizeof(type));
                size_t titleSize = movie->getTitle().size();
                file.write(reinterpret_cast<const char*>(&titleSize), sizeof(titleSize));
                file.write(movie->getTitle().c_str(), titleSize);
                size_t genreSize = movie->getGenres().size();
                file.write(reinterpret_cast<const char*>(&genreSize), sizeof(genreSize));
                for (const auto& genre : movie->getGenres()) {
                    size_t genreSize = genre.size();
                    file.write(reinterpret_cast<const char*>(&genreSize), sizeof(genreSize));
                    file.write(genre.c_str(), genreSize);
                }
                double length = movie->getLength();
                file.write(reinterpret_cast<const char*>(&length), sizeof(length));
            } else {
                const Show* show = dynamic_cast<const Show*>(media.get());
                if(show) {
                    char type = 'S';
                    file.write(&type, sizeof(type));
                    size_t titleSize = show->getTitle().size();
                    file.write(reinterpret_cast<const char*>(&titleSize), sizeof(titleSize));
                    file.write(show->getTitle().c_str(), titleSize);
                    size_t genreSize = show->getGenres().size();
                    file.write(reinterpret_cast<const char*>(&genreSize), sizeof(genreSize));
                    for (const auto& genre : show->getGenres()) {
                        size_t genreSize = genre.size();
                        file.write(reinterpret_cast<const char*>(&genreSize), sizeof(genreSize));
                        file.write(genre.c_str(), genreSize);
                    }
                    double length = show->getLength();
                    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
                    int episodes = show->getNumberOfEpisodes();
                    file.write(reinterpret_cast<const char*>(&episodes), sizeof(episodes));
                }
            }
        }
    }
};

void loadGraphFromBinary(Graph& graph, const string& filename) {
    ifstream file(filename, ios::binary);
    if(!file) {
        cerr << "Error opening file for reading: " << filename << endl;
        return;
    }

    //Read adjacency List 
    size_t adjSize;
    file.read(reinterpret_cast<char*>(&adjSize), sizeof(adjSize));
    for(size_t i=0; i< adjSize; ++i) {
        size_t keySize;
        file.read(reinterpret_cast<char*>(&keySize), sizeof(keySize));
        string genre(keySize, '\0');
        file.read(&genre[0], keySize);

        size_t neighborSize;
        file.read(reinterpret_cast<char*>(&neighborSize), sizeof(neighborSize));
        vector<pair<string, double>> neighbors;
        for (size_t j = 0; j < neighborSize; ++j) {
            size_t neighborKeySize;
            file.read(reinterpret_cast<char*>(&neighborKeySize), sizeof(neighborKeySize));
            string neighborGenre(neighborKeySize, '\0');
            file.read(&neighborGenre[0], neighborKeySize);
            double weight;
            file.read(reinterpret_cast<char*>(&weight), sizeof(weight));
            neighbors.emplace_back(neighborGenre, weight);
        }
        graph.adjacencyList[genre] = neighbors;
    }

    //Read Media data
    size_t mediaSize;
    file.read(reinterpret_cast<char*>(&mediaSize), sizeof(mediaSize));
    for(size_t i = 0; i < mediaSize; ++i) {
        size_t genreSize;
        file.read(reinterpret_cast<char*>(&genreSize), sizeof(genreSize));
        string genre(genreSize, '\0');
        file.read(&genre[0], genreSize);
    
        size_t mediaListSize;
        file.read(reinterpret_cast<char*>(&mediaListSize), sizeof(mediaListSize));
        for(size_t j = 0; j < mediaListSize; ++j) {" Tab settings
set tabstop=4       " Number of spaces that a <Tab> in the file counts for
set shiftwidth=4    " Number of spaces to use for each step of (auto)indent
set expandtab       " Convert tabs to spaces
set smarttab        " Makes tabbing smarter, will realize you have 4 vs 8
set autoindent      " Copy indent from current line when starting a new line
            char type;
            file.read(reinterpret_cast<char*>(&type), sizeof(type));
            size_t titleSize;
            file.read(reinterpret_cast<char*>(&titleSize), sizeof(titleSize));
            string title(titleSize, '\0');
            file.read(&title[0], titleSize);

            vector<string> genres;
            size_t genreSize;
            file.read(reinterpret_cast<char*>(&genreSize), sizeof(genreSize));
            for (size_t k=0; k<genreSize; ++k) {
                size_t genreSize;
                file.read(reinterpret_cast<char*>(&genreSize), sizeof(genreSize));
                string genre(genreSize, '\0');
                file.read(&genre[0], genreSize);
                genres.push_back(genre);
            }

            double length;
            file.read(reinterpret_cast<char*>(&length), sizeof(length));
            if (type == 'M') {
                graph.addMediaToGenre(make_shared<Movie>(title, genres, length));
            } else if (type == 'S') {
                int episodes;
                file.read(reinterpret_cast<char*>(&episodes), sizeof(episodes));
                graph.addMediaToGenre(make_shared<Show>(title, genres, length, episodes));
            }
        }
    }
};
#endif
