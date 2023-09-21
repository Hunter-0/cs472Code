#pragma once
#include <vector>
#include <utility>
template <class N>
class Graph {
public:
	Graph() {};
	Graph(std::vector<N> nodes, std::vector<std::pair<N, N>> edges) {};
	~Graph() {};

	bool adjacent(N x, N y);
	std::vector<N> neighbors(N x);
	void addNode(N x);
	void addEdge(N x, N y);
	void deleteEdge(N x, N y);     
    void deleteNode(N x, N y);     
    
};