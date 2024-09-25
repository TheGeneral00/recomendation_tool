#include <pybind11/pybind11.h>
#include <graph.h>

namespace py = pybind11; 

PYBIND11_MODULE(graph_module, m) {
    py::class_<Graph>(m, "Graph")
        .def(py::init<>())
        .def("addNode", &Graph::addNode)
        .def("modifyEdge", &Graph::modifyEdge)
        .def("removeEdge", &Graph::removeEdge)
        .def("getWeight", &Graph::getWeight)
        .def("addMediaToGenre", &Graph::addMediaToGenre)
        .def("removeMediaFromGenre", &Graph::removeMediaFromGenre)
        .def("getMediaFromGenre", &Graph::getMediaFromGenre);
}
