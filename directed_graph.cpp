#pragma once
#include "directed_graph.hpp"

using namespace std;

// Define all your methods down here (or move them up into the header, but be careful you don't double up). If you want to move this into another file, you can, but you should #include the file here.
// Although these are just the same names copied from above, you may find a few more clues in the full method headers.
// Note also that C++ is sensitive to the order you declare and define things in - you have to have it available before you use it.

//A constructor for directed_graph. The graph should start empty.
template <typename T>
directed_graph<T>::directed_graph() 
{
	adj_matrix;
	numEdges = 0;
	vertices;
}

//A destructor. Depending on how you do things, this may not be necessary.
template <typename T> 
directed_graph<T>::~directed_graph() 
{
	//Implement later
}

//Print matrix function, needed for testing purposes.
template <typename T> 
void directed_graph<T>::print_matrix() {
	//Standard pattern for printing 2D array
	//Print x axis
	cout << "  | ";
	for (int i=0; i<vertices.size(); i++) {
		cout << i << " ";
	}
	cout << endl;
	
	//Print divider to make it look nicer
	for (int i=0; i<vertices.size(); i++) {
		cout << "==";
	}
	cout << "===" << endl;
	
	//Print rows with respective weights
	for (int i = 0; i < adj_matrix.size(); i++) {
		cout << vertices[i].id << " | ";
		for (int j = 0; j < adj_matrix[i].size(); j++) {
			cout << adj_matrix[i][j] << " ";
		}
		cout << endl;
	}
}

//Returns true if the given vertex is in the graph, false otherwise.
template <typename T>
bool directed_graph<T>::contains(const int& u_id) const
{ 
	//Very basic for loop that checks for duplicate ids, if true then the vertex exists in the graph.
	for (vertex<T> v : vertices) {
		if (v.id == u_id) {
			return true;
		}
	}
	return false;
}

//Returns true if the first vertex is adjacent to the second, false otherwise.
template <typename T>
bool directed_graph<T>::adjacent(const int& u_id, const int& v_id) const
{
	//First check if u and v exist in our graph
	if (contains(u_id) && contains(v_id)) {
		return (adj_matrix[u_id][v_id] > 0); 
		//If 0, there is no edge, if > 0 there is edge with weight.
	}
	else {
		return false;
	}
}

//Adds the passed in vertex to the graph (with no edges).
template <typename T>
void directed_graph<T>::add_vertex(const vertex<T>& u)
{
	//Make sure vertex with that id is not already in the graph, avoiding duplicates
	if (!contains(u.id)) {
		//id should be the index of the element in the vector (i.e. "A" is index 0)
		vertices.push_back(u); //Add the vertex to the vertices list
		vector<int> vertexRow;

		//Initialise this new row with zeros
		//Also add zeros to all other rows that already exist
		//DEBUG cout << "Amt Vertices: " << vertices.size() << endl;

		//Build correct amt of zeros depending on current graph size.
		for (int i = 0; i < vertices.size(); i++) {
			vertexRow.push_back(0);
		}

		adj_matrix.push_back(vertexRow); //Push back to vector row (from)
		
		/* Need to append zeros to the previous rows (excluding the one
		 * we just added) in order to maintain a square matrix. */
		for (int i = 0; i < adj_matrix.size() - 1; i++) {
			//DEBUGcout << "Pushing zero at index " << i << endl;
			adj_matrix[i].push_back(0); 
		}

		cout << "Added vertex id: " << u.id << " weight: " << u.weight << endl;
	}
	else {
		cout << "Vertex already exists in graph, cannot add identical vertex." << endl;
	}
}

//Adds a weighted edge from the first vertex to the second.
template <typename T>
void directed_graph<T>::add_edge(const int& u_id, const int& v_id, const T& weight)
{
	//Check if the vertices exist in the graph before adding an edge.
	if (!contains(u_id) || !contains(v_id)) {
		cout << "One of the vertices does not exist in the graph, cannot add edge." << endl;
		return; //End the function if either one of the vertices don't exist in the graph.
	}
	//Weight must be > 0 as 0 indicates no edge and we cant have negative weights
	if (weight <= 0) {
		return; //End function
	}
	//Don't want self-loops in the graph, end function if u.id and v.id are same
	if (u_id == v_id) {
		cout << "No self-loops allowed in graph." << endl;
		return; //End function
	}
	/*u is refered to as the 'from' vertex and v is the 'to' vertex, this is a directed graph
	 *so this distinction is important.
	 *The vertex ids are the indexes in the 2d array */
	if (adj_matrix[u_id][v_id] == 0) { //Only add edge if none exists
		adj_matrix[u_id][v_id] = weight; //Weighted graph
		numEdges++; //Increment edges
	}
	else {
		cout << "Edge already exists between " << u_id << " and " << v_id << endl;
	}
}

//Removes the given vertex. Should also clear any incident edges.
template <typename T>
void directed_graph<T>::remove_vertex(const int& u_id)
{
	if (!contains(u_id)) {
		return; //End function if vertex doesn't exist.
	}
	
	//Debugging
	cout << "Removing vertex id: " << u_id << " weight: " << vertices[u_id].weight << endl;
	
	/* Before we remove the vertex, calc number of edges that 	*
	 * will be removed in order to update numEdges. This needs	*
	 * to be done before removing the vertex.							*/
	size_t numAffectedEdges = degree(u_id); //Use size_t for consistency
	
	//Need to remove the column for that vertex first.
	for (int i = 0; i < adj_matrix.size(); i++) {
		if (i > u_id) { 	/* Need to update vertex ids for those vertices	*
								 * greater than the one being removed.				*/
			vertices[i].id--;
		}
		//Remove associated column for vertex
		adj_matrix[i].erase(adj_matrix[i].begin() + u_id);
	}
	
	/*	Following line deletes the row not column.							*
	 *	Should remove the vertex from the adj_matrix which also holds	*
	 *	the respective weights and **from** relationships. 				*/
	adj_matrix.erase(adj_matrix.begin() + u_id); 
	
	vertices.erase(vertices.begin() + u_id); //Remove same vertex from vertices list
	
	/* Should be able to use numEdges -= degree(u_id) as we just	* 
	 * erased the whole vertex and all its associated edges.			*
	 * No reason other than preference to put this at the end.		*/
	numEdges -= numAffectedEdges;
}

//Removes the edge between the two vertices, if it exists.
template <typename T>
void directed_graph<T>::remove_edge(const int& u_id, const int& v_id) 
{
	//Check if the vertices exist in the graph before adding an edge.
	if (!contains(u_id) || !contains(v_id)) {
		cout << "One of the vertices does not exist in the graph, cannot add edge." << endl;
		return; //End the function if either one of the vertices don't exist in the graph.
	}
	//Don't want self-loops in the graph, end function if u_id and v_id are same
	if (u_id == v_id) {
		cout << "No self-loops allowed in graph." << endl;
		return; //End function
	}
	adj_matrix[u_id][v_id] = 0; //Zeroing the relationship "removes" the edge
	numEdges--;
}

//Returns number of edges coming in to a vertex.
template <typename T>
size_t directed_graph<T>::in_degree(const int& u_id) const 
{ 
	size_t inDegree = 0;
	/* Check corresponding column of u_id for any non-zero weights.			*
	 * This should give us the in-degree as the column represents the "in"	*
	 * or "to" direction of the relationship between vertices in the graph.	*/
	for (int i = 0; i < adj_matrix.size(); i++) {
		if (adj_matrix[i][u_id] > 0) inDegree++;	//Simply increment indegree on non-zero weight
	}
	return inDegree; 
}

//Returns the number of edges leaving a vertex.
template <typename T>
size_t directed_graph<T>::out_degree(const int& u_id) const 
{ 
	size_t outDegree = 0;
	/* Check corresponding row of u_id for any non-zero weights.				*
	 * This should give us the out-degree as the row represents the "out"		*
	 * or "from" direction of the relationship between vertices in the graph.	*/
	for (int i = 0; i < adj_matrix[u_id].size(); i++) {
		if (adj_matrix[u_id][i] > 0) outDegree++;	//Simply increment out-degree on non-zero weight
	}
	return outDegree; 
}

//Returns the degree of the vertex (both in edges and out edges).
template <typename T>
size_t directed_graph<T>::degree(const int& u_id) const 
{ 
	//Total degree should be sum of in and out degrees
	return in_degree(u_id) + out_degree(u_id); 
}

//Returns the total number of vertices in the graph.
template <typename T>
size_t directed_graph<T>::num_vertices() const
{ 
	return vertices.size(); //adj_matrix.size() also works
}

//Returns the total number of edges in the graph.
template <typename T>
size_t directed_graph<T>::num_edges() const
{ 
	return numEdges; 
}

//Returns a vector containing all the vertices.
template <typename T>
vector<vertex<T>> directed_graph<T>::get_vertices() { 
	// Luckily, I keep track of all vertices in a separate vector "vertices"
	return vertices; 
}

//Returns a vector containing all the vertices reachable from the given vertex. 
//The vertex is not considered a neighbour of itself.
template <typename T>
vector<vertex<T>> directed_graph<T>::get_neighbours(const int& u_id) 
{ 
	vector<vertex<T>> neighbours;
	
	/* Just check the row of the given vertex in the matrix.				*
	 * If >0, there is a direct path to that vertex, add it to the vector.	*/
	for(int i=0; i < adj_matrix[u_id].size(); i++) {
		if (adj_matrix[u_id][i] > 0) neighbours.push_back(vertices[i]);
	}
	
	//To test, num of neighbours should be == to out_degree
	//Following output is very useful for testing.
	cout << "Neighbours of " << u_id << ": {";
	for (auto v : neighbours) {
		 cout << v.id << ", ";
	}
	cout << "}." << endl;
	
	return neighbours; 
}

// Returns a vector containing all the second_order_neighbours (i.e., neighbours of neighbours) 
// of the given vertex. A vector cannot be considered a second_order_neighbor of itself.
template <typename T>
vector<vertex<T>> directed_graph<T>::get_second_order_neighbors(const int& u_id) 
{ 
	vector<vertex<T>> second_order_neighbours;
	
	/* Should accomplish this by running neighbours function on every neighbour of u_id.*/
	vector<vertex<T>> firstNeighbours;
	firstNeighbours = get_neighbours(u_id);
	
	for (auto v : firstNeighbours) {
		vector<vertex<T>> neighbourNeighbours = get_neighbours(v.id);
		//Need to make sure the second order aren't same as original vertex
		for (auto v : neighbourNeighbours) {
			if (v.id != u_id) {
				second_order_neighbours.push_back(v);
			}
		}
	}
	

	//Following output is very useful for testing.
	
	cout << "Second order neighbours of " << u_id << ": {";
	for (auto v : second_order_neighbours) {
		 cout << v.id << ", ";
	}
	cout << "}." << endl;
	
	return second_order_neighbours; 
}

//Returns true if the second vertex is reachable from the first 
//(can you follow a path of out-edges to get from the first to the second?). Returns false otherwise.
template <typename T>
bool directed_graph<T>::reachable(const int& u_id, const int& v_id) const 
{ 
	
	return false; 
}

// Return true if the graph contains cycles (there is a path from any vertices directly/indirectly to itself), false otherwise.
template <typename T>
bool directed_graph<T>::contian_cycles() const 
{ 

	return false; 
}

//Returns the vertices of the graph in the order they are visited in by a 
//depth-first traversal starting at the given vertex.
template <typename T>
vector<vertex<T>> directed_graph<T>::depth_first(const int& u_id) 
{ 
	return vector<vertex<T>>(); 
}

template <typename T>
vector<vertex<T>> directed_graph<T>::breadth_first(const int& u_id) { return vector<vertex<T>>(); }

template <typename T>
directed_graph<T> directed_graph<T>::out_tree(const int& u_id) { return directed_graph<vertex<T>>(); }

template <typename T>
vector<vertex<T>> directed_graph<T>::pre_order_traversal(const int& u_id, directed_graph<T>& mst) { return vector<vertex<T>>(); }

template <typename T>
vector<vertex<T>> directed_graph<T>::in_order_traversal(const int& u_id, directed_graph<T>& mst) { return vector<vertex<T>>(); }

template <typename T>
vector<vertex<T>> directed_graph<T>::post_order_traversal(const int& u_id, directed_graph<T>& mst) { return vector<vertex<T>>(); }

template <typename T>
vector<vertex<T>> directed_graph<T>::significance_sorting() { return vector<vertex<T>>(); }
