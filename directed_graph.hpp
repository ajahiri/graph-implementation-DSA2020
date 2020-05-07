#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include<iostream>
#include<string>
#include <vector>
// include more libraries here if you need to

using namespace std; //The standard namespace are here just in case.

/*
    the vertex class
*/
template <typename T>
class vertex {

public:
    int id;
    int weight;

    vertex(int x, T y) : id(x), weight(y) {}

    // Add more functions here if you need to
};

/*
    the graph class
*/
template <typename T>
class directed_graph {

private:
    //You will need to add some data members here
    //to actually represent the graph internally,
    //and keep track of whatever you need to.

    size_t numEdges; //Use size_t as unsigned integer to keep track of edges amount.
    vector< vector<T> > adj_matrix; //The adj_matrix to represent the relationships.
    vector< vertex<T> > vertices;	//List of vertices with their respective weights.
								//Number of vertices can be calculated using vertices.size()

public:

	directed_graph(); //A constructor for directed_graph. The graph should start empty.
	~directed_graph(); //A destructor. Depending on how you do things, this may not be necessary.

	void print_matrix();

	bool contains(const int&) const; //Returns true if the graph contains the given vertex_id, false otherwise.
	bool adjacent(const int&, const int&) const; //Returns true if the first vertex is adjacent to the second, false otherwise.

	void add_vertex(const vertex<T>&); //Adds the passed in vertex to the graph (with no edges).
	void add_edge(const int&, const int&, const T&); //Adds a weighted edge from the first vertex to the second.

	void remove_vertex(const int&); //Removes the given vertex. Should also clear any incident edges.
	void remove_edge(const int&, const int&); //Removes the edge between the two vertices, if it exists.

	size_t in_degree(const int&) const; //Returns number of edges coming in to a vertex.
	size_t out_degree(const int&) const; //Returns the number of edges leaving a vertex.
	size_t degree(const int&) const; //Returns the degree of the vertex (both in edges and out edges).

	size_t num_vertices() const; //Returns the total number of vertices in the graph.
	size_t num_edges() const; //Returns the total number of edges in the graph.

	vector<vertex<T>> get_vertices(); //Returns a vector containing all the vertices.
	vector<vertex<T>> get_neighbours(const int&); //Returns a vector containing all the vertices reachable from the given vertex. The vertex is not considered a neighbour of itself.
	vector<vertex<T>> get_second_order_neighbors(const int&); // Returns a vector containing all the second_order_neighbours (i.e., neighbours of neighbours) of the given vertex.
															  // A vector cannot be considered a second_order_neighbor of itself.
	bool reachable(const int&, const int&) const; //Returns true if the second vertex is reachable from the first (can you follow a path of out-edges to get from the first to the second?). Returns false otherwise.
	bool contian_cycles() const; // Return true if the graph contains cycles (there is a path from any vertices directly/indirectly to itself), false otherwise.

	vector<vertex<T>> depth_first(const int&); //Returns the vertices of the graph in the order they are visited in by a depth-first traversal starting at the given vertex.
	vector<vertex<T>> breadth_first(const int&); //Returns the vertices of the graph in the order they are visisted in by a breadth-first traversal starting at the given vertex.

	directed_graph<T> out_tree(const int&); //Returns a spanning tree of the graph starting at the given vertex using the out-edges. This means every vertex in the tree is reachable from the root.

	vector<vertex<T>> pre_order_traversal(const int&, directed_graph<T>&); // returns the vertices in the visiting order of a pre-order traversal of the minimum spanning tree starting at the given vertex.
	vector<vertex<T>> in_order_traversal(const int&, directed_graph<T>&); // returns the vertices in the visiting order of an in-order traversal of the minimum spanning tree starting at the given vertex.
	vector<vertex<T>> post_order_traversal(const int&, directed_graph<T>&); // returns the vertices in ther visitig order of a post-order traversal of the minimum spanning tree starting at the given vertex.

	vector<vertex<T>> significance_sorting(); // Return a vector containing a sorted list of the vertices in descending order of their significance.

};
#endif