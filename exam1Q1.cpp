#pragma once
#include "graph.hpp"
#include <map>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
using namespace std;

template <class N>
class AdjListGraph : public Graph<N> {
private:
    using Edges = list<pair<N, N>>;
    map<N, Edges> vertexMap;

public:
    AdjListGraph() : Graph<N>() { }

    AdjListGraph(const AdjListGraph &other) : Graph<N>() {
        vertexMap = other.vertexMap;
    }

    AdjListGraph& operator= (const AdjListGraph &source) {
        vertexMap = source.vertexMap;
        return *this;
    }

    AdjListGraph(vector<N> newNodes, vector<pair<N, N>> newEdges) : Graph<N>(newNodes, newEdges) {
        for (const N &node : newNodes) {
            vertexMap[node] = Edges();
        }
        for (const auto &edge : newEdges) {
            addEdge(edge.first, edge.second);
        }
    }

    ~AdjListGraph() { }

    bool adjacent(N x, N y) {
        if (vertexMap.find(x) == vertexMap.end() || vertexMap.find(y) == vertexMap.end()) {
            return false; 
        }

        const Edges &edges = vertexMap.at(x);
        for (const pair<N, N> &edge : edges) {
            if (edge.first == y || edge.second == y) {
                return true;
            }
        }

        return false;
    }

    vector<N> neighbors(N x) {
        vector<N> nodes;
        if (vertexMap.find(x) == vertexMap.end()) {
            return nodes; 
        }

        const Edges &edges = vertexMap.at(x);
        for (const pair<N, N> &edge : edges) {
            if (edge.first != x) {
                nodes.push_back(edge.first);
            }
            if (edge.second != x) {
                nodes.push_back(edge.second);
            }
        }
        return nodes;
    }

    void addNode(N node) {
        if (vertexMap.find(node) == vertexMap.end()) {
            vertexMap[node] = Edges();
        }
    }

    void deleteNode(N x) {
        if (vertexMap.find(x) != vertexMap.end()) {
            for (auto &entry : vertexMap) {
                N node = entry.first;
                Edges &edges = entry.second;
                edges.remove_if([&](const pair<N, N> &edge) {
                    return edge.first == x || edge.second == x;
                });
            }
            vertexMap.erase(x);
        }
    }

    void addEdge(N x, N y) {
        if (vertexMap.find(x) != vertexMap.end() && vertexMap.find(y) != vertexMap.end()) {
            pair<N, N> forwardEdge = make_pair(x, y);
            pair<N, N> backwardEdge = make_pair(y, x);
            vertexMap[x].push_back(forwardEdge);
            vertexMap[y].push_back(backwardEdge);
        }
    }

    void deleteEdge(N x, N y) {
        if (vertexMap.find(x) != vertexMap.end() && vertexMap.find(y) != vertexMap.end()) {
            pair<N, N> forwardEdge = make_pair(x, y);
            pair<N, N> backwardEdge = make_pair(y, x);
            vertexMap[x].remove(forwardEdge);
            vertexMap[y].remove(backwardEdge);
        }
    }

    
};