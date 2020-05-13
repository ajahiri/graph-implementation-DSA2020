#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include<iostream>
#include<string>
#include<vector>
#include<queue>
// include more libraries here if you need to

using namespace std; // the standard namespace are here just in case.

/*
	the vertex class
*/
template <typename T>
class vertex {

public:
	int id; // unique identifer for each vertex
	T weight; // int, double, char, string, ...
	int pos; 

	vertex(int v_id, T v_weight) : id(v_id), weight(v_weight) { // constructor
	}

	// add more functions here if you need to
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
	void print_matrix(); //Only for testing
	
	vertex<T> get_vertex(const int& u_id); //Defined by me, used to get vertex by id
	bool vector_contains(const vector<vertex<T>>&, const int&); //Defined by me, used to know if a vector contains a particular vertex.

	bool contains(const int&) const; //Returns true if the graph contains the given vertex_id, false otherwise.
	bool adjacent(const int&, const int&); //Returns true if the first vertex is adjacent to the second, false otherwise.

	void add_vertex(const vertex<T>&); //Adds the passed in vertex to the graph (with no edges).
	void add_edge(const int&, const int&, const T&); //Adds a weighted edge from the first vertex to the second.

	void remove_vertex(const int&); //Removes the given vertex. Should also clear any incident edges.
	void remove_edge(const int&, const int&); //Removes the edge between the two vertices, if it exists.

	size_t in_degree(const int&); //Returns number of edges coming in to a vertex.
	size_t out_degree(const int&); //Returns the number of edges leaving a vertex.
	size_t degree(const int&); //Returns the degree of the vertex (both in edges and out edges).

	size_t num_vertices() const; //Returns the total number of vertices in the graph.
	size_t num_edges() const; //Returns the total number of edges in the graph.

	vector<vertex<T>> get_vertices(); //Returns a vector containing all the vertices.
	vector<vertex<T>> get_neighbours(const int&); //Returns a vector containing all the vertices reachable from the given vertex. The vertex is not considered a neighbour of itself.
	vector<vertex<T>> get_second_order_neighbours(const int&); // Returns a vector containing all the second_order_neighbours (i.e., neighbours of neighbours) of the given vertex.
															  // A vector cannot be considered a second_order_neighbour of itself.
	bool reachable(const int&, const int&); //Returns true if the second vertex is reachable from the first (can you follow a path of out-edges to get from the first to the second?). Returns false otherwise.
	bool contain_cycles(); // Return true if the graph contains cycles (there is a path from any vertices directly/indirectly to itself), false otherwise.

	vector<vertex<T>> depth_first(const int&); //Returns the vertices of the graph in the order they are visited in by a depth-first traversal starting at the given vertex.	
	void DFSUtil(bool*, vector<vertex<T>>&, const vertex<T>&);

	vector<vertex<T>> breadth_first(const int&); //Returns the vertices of the graph in the order they are visisted in by a breadth-first traversal starting at the given vertex.

	directed_graph<T> out_tree(const int&); //Returns a spanning tree of the graph starting at the given vertex using the out-edges. This means every vertex in the tree is reachable from the root.

	vector<vertex<T>> pre_order_traversal(const int&, directed_graph<T>&); // returns the vertices in the visiting order of a pre-order traversal of the minimum spanning tree starting at the given vertex.
	vector<vertex<T>> in_order_traversal(const int&, directed_graph<T>&); // returns the vertices in the visiting order of an in-order traversal of the minimum spanning tree starting at the given vertex.
	vector<vertex<T>> post_order_traversal(const int&, directed_graph<T>&); // returns the vertices in ther visitig order of a post-order traversal of the minimum spanning tree starting at the given vertex.

	vector<vertex<T>> significance_sorting(); // Return a vector containing a sorted list of the vertices in descending order of their significance.

};

// Define all your methods down here (or move them up into the header, but be careful you don't double up). If you want to move this into another file, you can, but you should #include the file here.
// Although these are just the same names copied from above, you may find a few more clues in the full method headers.
// Note also that C++ is sensitive to the order you declare and define things in - you have to have it available before you use it.

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

//Defined by Arian, used to get the vertex object based on id
template <typename T> 
vertex<T> directed_graph<T>::get_vertex(const int& u_id) 
{
	for (int i=0; i<vertices.size(); i++) {
		if (u_id == vertices[i].id) {
			return vertices[i];
		}
	}
	return vertices[0];
} 

//Defined by me, used to check wheter a vector contains a particular vertex
template <typename T> 
bool directed_graph<T>::vector_contains(const vector<vertex<T>>& vector, const int& u_id)
{
	for (auto v : vector) {
		if (v.id == u_id) {
			return true;
		}
	}
	return false;
}

//A constructor for directed_graph. The graph should start empty.
template <typename T>
directed_graph<T>::directed_graph() 
{
	numEdges = 0;
}

//A destructor. Depending on how you do things, this may not be necessary.
template <typename T> 
directed_graph<T>::~directed_graph() 
{
	//Implement later
}

//Returns true if the given vertex is in the graph, false otherwise.
template <typename T>
bool directed_graph<T>::contains(const int& u_id) const
{ 
	//Very basic for loop that checks for ids, if true then the vertex exists in the graph.
	for (auto v : vertices) {
		if (v.id == u_id) {
			return true;
		}
	}
	return false;
}

//Returns true if the first vertex is adjacent to the second, false otherwise.
template <typename T>
bool directed_graph<T>::adjacent(const int& u_id, const int& v_id)
{
	// Get positions of the vectors
	int posU = get_vertex(u_id).pos;
	int posV = get_vertex(v_id).pos;
	//First check if u and v exist in our graph
	if (contains(u_id) && contains(v_id)) {
		return (adj_matrix[posU][posV] > 0); 
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
	if (contains(u.id)) {
		//cout << "Vertex already exists in graph, cannot add identical vertex." << endl;
		return;
	}

	vertex<T> mappedU = u; //id, weight, position
	mappedU.pos = vertices.size();

	//id should be the index of the element in the vector (i.e. "A" is index 0)
	vertices.push_back(mappedU); //Add the vertex to the vertices list
	
	//Initialise this new row with zeros
	vector<T> vertexRow;
	
	//DEBUG cout << "Amt Vertices: " << vertices.size() << endl;

	//Build correct amt of zeros depending on current graph size.
	for (int i = 0; i < vertices.size(); i++) {
		vertexRow.push_back(0);
	}

	adj_matrix.push_back(vertexRow); //Push back to vector row (from)
	
	/* Need to append zeros to the previous rows (excluding the one	*
	 * we just added) in order to maintain a square matrix. 		*/
	 //Also add zeros to all other rows that already exist
	for (int i = 0; i < adj_matrix.size() - 1; i++) {
		//DEBUGcout << "Pushing zero at index " << i << endl;
		adj_matrix[i].push_back(0); 
	} 
	//cout << "Added vertex id: " << u.id << " weight: " << u.weight << endl;
}

//Adds a weighted edge from the first vertex to the second.
template <typename T>
void directed_graph<T>::add_edge(const int& u_id, const int& v_id, const T& weight)
{
	//Check if the vertices exist in the graph before adding an edge.
	if (!contains(u_id) || !contains(v_id)) {
		//cout << "One of the vertices does not exist in the graph, cannot add edge." << endl;
		return; //End the function if either one of the vertices don't exist in the graph.
	}
	//Weight must be > 0 as 0 indicates no edge and we cant have negative weights
	if (weight <= 0) {
		return; //End function
	}
	//Don't want self-loops in the graph, end function if u.id and v.id are same
	if (u_id == v_id) {
		//cout << "No self-loops allowed in graph." << endl;
		return; //End function
	}

	// Get positions of the vectors
	int posU = get_vertex(u_id).pos;
	int posV = get_vertex(v_id).pos;
	/*u is refered to as the 'from' vertex and v is the 'to' vertex, this is a directed graph
	 *so this distinction is important.
	 *The vertex ids are the indexes in the 2d array */
	if (adj_matrix[posU][posV] == 0) { //Only add edge if none exists
		adj_matrix[posU][posV] = weight; //Weighted graph
		numEdges++; //Increment edges
	}
	else {
		//cout << "Edge already exists between " << u_id << " and " << v_id << endl;
		return;
	}
}

//Removes the given vertex. Should also clear any incident edges.
template <typename T>
void directed_graph<T>::remove_vertex(const int& u_id)
{
	if (!contains(u_id)) {
		return; //End function if vertex doesn't exist.
	}
	
	//Get pos of vertex from id
	int posU = get_vertex(u_id).pos;

	//Debugging
	//cout << "Removing vertex id: " << u_id << " weight: " << vertices[u_id].weight << endl;
	
	/* Before we remove the vertex, calc number of edges that 	*
	 * will be removed in order to update numEdges. This needs	*
	 * to be done before removing the vertex.							*/
	numEdges -= degree(posU);
	vertices.erase(vertices.begin() + posU); //Remove vertex from vertices list

	/*	Following line deletes the row not column.							*
	 *	Should remove the vertex from the adj_matrix which also holds	*
	 *	the respective weights and **from** relationships. 				*/
	adj_matrix.erase(adj_matrix.begin() + posU);

	//Need to remove the corresponding column for that vertex first.
	/* Also update vertex ids for those vertices		*
	 * greater than the one being removed.				*/
	for (int i = 0; i < adj_matrix.size(); i++) {
		//Remove associated column for vertex
		adj_matrix[i].erase(adj_matrix[i].begin() + posU);
		//Update vertex positions as vector has changed
		if (i >= posU) vertices[i].pos--;
	}
}

//Removes the edge between the two vertices, if it exists.
template <typename T>
void directed_graph<T>::remove_edge(const int& u_id, const int& v_id) 
{
	//Check if the vertices exist in the graph before adding an edge.
	if (!contains(u_id) || !contains(v_id)) {
		//cout << "One of the vertices does not exist in the graph, cannot add edge." << endl;
		return; //End the function if either one of the vertices don't exist in the graph.
	}

	//Don't want self-loops in the graph, end function if u_id and v_id are same
	if (u_id == v_id) {
		//cout << "No self-loops allowed in graph." << endl;
		return; //End function
	}

	// Get positions of the vectors
	int posU = get_vertex(u_id).pos;
	int posV = get_vertex(v_id).pos;
	adj_matrix[posU][posV] = 0; //Zeroing the relationship "removes" the edge
	numEdges--;
}

//Returns number of edges coming in to a vertex.
template <typename T>
size_t directed_graph<T>::in_degree(const int& u_id) 
{ 
	// Get position of the vector
	int posU = get_vertex(u_id).pos;

	size_t inDegree = 0;
	/* Check corresponding column of u_id for any non-zero weights.			*
	 * This should give us the in-degree as the column represents the "in"	*
	 * or "to" direction of the relationship between vertices in the graph.	*/
	for (int i = 0; i < adj_matrix.size(); i++) {
		if (adj_matrix[i][posU] > 0) inDegree++;	//Simply increment indegree on non-zero weight
	}
	return inDegree; 
}

//Returns the number of edges leaving a vertex.
template <typename T>
size_t directed_graph<T>::out_degree(const int& u_id) 
{ 
	// Get position of the vector
	int posU = get_vertex(u_id).pos;

	size_t outDegree = 0;
	/* Check corresponding row of u_id for any non-zero weights.				*
	 * This should give us the out-degree as the row represents the "out"		*
	 * or "from" direction of the relationship between vertices in the graph.	*/
	for (int i = 0; i < adj_matrix[posU].size(); i++) {
		if (adj_matrix[posU][i] != 0) outDegree++;	//Simply increment out-degree on non-zero weight
	}
	return outDegree; 
}

//Returns the degree of the vertex (both in edges and out edges).
template <typename T>
size_t directed_graph<T>::degree(const int& u_id) 
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
	// Get position of the vector
	int posU = get_vertex(u_id).pos;
	
	/* Just check the row of the given vertex in the matrix.				*
	 * If >0, there is a direct path to that vertex, add it to the vector.	*/
	for(int i=0; i < adj_matrix[posU].size(); i++) {
		if (adj_matrix[posU][i] != 0) neighbours.push_back(vertices[i]);
	}
	
	//To test, good note: num of neighbours should be == to out_degree
	//Following output is very useful for testing.
	/*
	cout << "Neighbours of " << u_id << ": {";
	for (auto v : neighbours) {
		 cout << v.id << ", ";
	}
	cout << "}." << endl;
	*/
	return neighbours; 
}

// Returns a vector containing all the second_order_neighbours (i.e., neighbours of neighbours) 
// of the given vertex. A vertex cannot be considered a second_order_neighbour of itself.
template <typename T>
vector<vertex<T>> directed_graph<T>::get_second_order_neighbours(const int& u_id) 
{ 
	vector<vertex<T>> second_order_neighbours;
	
	/* Should accomplish this by running neighbours function on every neighbour of u_id.*/
	vector<vertex<T>> firstNeighbours;
	firstNeighbours = get_neighbours(u_id);
	
	for (auto v : firstNeighbours) {
		vector<vertex<T>> secondNeighbours = get_neighbours(v.id); //Get neighbours of neighbours
		for (auto u : secondNeighbours) {
			//Check if vertex already exists in second_order_neighbours using vector_conains()
			//A vertex cannot be considered a second_order_neighbour of itself and there must be no duplicates
			if ((u.id != u_id) && !vector_contains(second_order_neighbours, u.id)) second_order_neighbours.push_back(u);
		}
	}

	//Following output is useful for testing.
	/*
	cout << second_order_neighbours.size() << " second order neighbours of " << u_id << ": {";
	for (auto v : second_order_neighbours) {
		 cout << v.id << ", ";
	}
	cout << "}." << endl;
	*/
	return second_order_neighbours; 
}

//Returns true if the second vertex is reachable from the first (can you follow a path of out-edges to get from the first to the second?). 
//Returns false otherwise.
template <typename T>
bool directed_graph<T>::reachable(const int& u_id, const int& v_id) 
{
	return vector_contains(depth_first(u_id), v_id);
}

// Return true if the graph contains cycles (there is a path from any vertices directly/indirectly to itself), false otherwise.
template <typename T>
bool directed_graph<T>::contain_cycles() 
{ 
	for (auto v : vertices) {
		vector<vertex<T>> DFSResult = depth_first(v.id);
		/*At this point we need to check for back edges for every vertex in DFSResult, we can do this by looping through the	*
		 *results and checking if they have an edge from itself to the original vertex.											*/
		 for(auto u : DFSResult) {
			 if(adj_matrix[u.pos][v.pos] > 0) return true; //Return true if back edge exists, this means there is a cycle.
		 }
	}
	return false; 
}

//Returns the vertices of the graph in the order they are visited in by a depth-first traversal starting at the given vertex.
template <typename T>
vector<vertex<T>> directed_graph<T>::depth_first(const int& u_id) 
{ 
	/* Implemented using recursive implementation explained in lecture slides. 			*
	 * Using searchResults for visited as I already have a vector_contains() function.	*/
	vector<vertex<T>> searchResult; //Our output
	bool visited[vertices.size()] = { false }; //Use array of bool to mark visited (initialise to false)

	DFSUtil(visited, searchResult, get_vertex(u_id)); //Start the actualy depth first search and recursion
	return searchResult; // Return the result of traversal
}
template <typename T>
void directed_graph<T>::DFSUtil(bool* visited, vector<vertex<T>>& searchResult, const vertex<T>& v) 
{
	searchResult.push_back(v); 	//Visit v
	visited[v.pos] = true;		//Mark v as visited

	for (auto u : get_neighbours(v.id)) {
		if (!visited[u.pos]) {
			DFSUtil(visited, searchResult, u); //Recursive call
		}
	}
}

//Returns the vertices of the graph in the order they are visisted in by a breadth-first traversal starting at the given vertex.
template <typename T>
vector<vertex<T>> directed_graph<T>::breadth_first(const int& u_id) 
{ 
	/* Implemented using iterative implementation explained in lecture slides. 			*/
	vector<vertex<T>> searchResult; //The result of traversal
	queue<vertex<T>> unprocessed; //Unprocessed queue
	bool visited[vertices.size()] = { false };  //Use array of bool to mark visited (initialise to false)
												//Since each vertex has a pos member, we can use that in visited array.

	unprocessed.push(get_vertex(u_id)); //Push starting vertex

	while (!unprocessed.empty()) {
		vertex<T> u = unprocessed.front();
		unprocessed.pop();
		if(!visited[u.pos]) { //Avoid duplicates in results
			searchResult.push_back(u);
		}
		visited[u.pos] = true;
		for (auto v : get_neighbours(u.id)) {
			if (!visited[v.pos]){
				unprocessed.push(v);
			}
		}
	}
	return searchResult; 
}


template <typename T>
directed_graph<T> directed_graph<T>::out_tree(const int& u_id) { return directed_graph<T>(); }

template <typename T>
vector<vertex<T>> directed_graph<T>::pre_order_traversal(const int& u_id, directed_graph<T>& mst) { return vector<vertex<T>>(); }

template <typename T>
vector<vertex<T>> directed_graph<T>::in_order_traversal(const int& u_id, directed_graph<T>& mst) { return vector<vertex<T>>(); }

template <typename T>
vector<vertex<T>> directed_graph<T>::post_order_traversal(const int& u_id, directed_graph<T>& mst) { return vector<vertex<T>>(); }

template <typename T>
vector<vertex<T>> directed_graph<T>::significance_sorting() { return vector<vertex<T>>(); }

#endif