#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm> //For using "sort()"
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
	int pos; //Vertex position in adj_matrix, initialised on add_vertex()
	int popularity; //Total of vertex weight (number of followers) and 
					//how many times they were liked by other vertices. Calculated during sort.
	bool nullVertex; //Bool to be used to indicate a nullVertex, useful for MST traversal functions

	/*For use with Tarjan's algorithm*/
	vector<vertex<T>> dfn;

	vertex(int v_id, T v_weight) : id(v_id), weight(v_weight) { // constructor
		popularity = 0;
		nullVertex = false;
	}

	// add more functions here if you need to
	/* For use with std::sort() function to sort vertices by weight. */
	bool operator > (const vertex<T>& v) const 
	{
		return (popularity > v.popularity); /* Decreasing sort by weight. */
	}
};

/*
	graph_edge class
*/
/* We need an edge struct only for purposes of MST function. */
template <typename T>
struct graph_edge {	
	
	int from_id; /* ID of vertex where the edge starts. */
	int to_id; /* ID of vertex where the edge ends */
	T weight; /* Weight of edge, maintain the use of temaplate */
	
	
	graph_edge(int from_id, int to_id, T weight) : from_id(from_id), 
	to_id(to_id), weight(weight) { // constructor

	}

	/* Implementing the greater operator for graph_edge in order to use	*
	 * std::sort() on the vector of graph_edge. 						*/
	bool operator > (const graph_edge& edge) const
    {
        return (weight > edge.weight);
    }
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
	
	vector<vector<T>> get_matrix();

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
	void inOrderUtil(vector<vertex<T>>&, const vertex<T>&, directed_graph<T>&);

	vector<vertex<T>> post_order_traversal(const int&, directed_graph<T>&); // returns the vertices in ther visitig order of a post-order traversal of the minimum spanning tree starting at the given vertex.
	void postOrderUtil(vector<vertex<T>>&, const vertex<T>&, directed_graph<T>&);

	vector<vertex<T>> significance_sorting(); // Return a vector containing a sorted list of the vertices in descending order of their significance.
};

// Define all your methods down here (or move them up into the header, but be careful you don't double up). If you want to move this into another file, you can, but you should #include the file here.
// Although these are just the same names copied from above, you may find a few more clues in the full method headers.
// Note also that C++ is sensitive to the order you declare and define things in - you have to have it available before you use it.

/* Needed for access in directed_graph_alogithms */
template <typename T> 
vector<vector<T>> directed_graph<T>::get_matrix() {
	return adj_matrix;
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
		//DEBUG cout << "Vertex already exists in graph, cannot add identical vertex." << endl;
		return;
	}

	/* Create a "mapped" vertex to be pushed with the right .pos in accordance to the pre-existing matrix. 	*
	 * This was added as I did not take into account that IDs could be different to the vertex's position. 	*/
	vertex<T> mappedU = u; //Copy the vertex with id, weight, position
	mappedU.pos = vertices.size(); //Set position to correct place for proper representation in both vertices vector and adj_matrix
	vertices.push_back(mappedU); //Add the vertex to the vertices list
	
	/* Initialise a vertex's row with 0s, in the context of the adj_matrix, we are initialising the vertex's row	*
	 * with no relationships/edges. 																				*/
	vector<T> vertexRow(vertices.size(), 0);
	adj_matrix.push_back(vertexRow); //Push the new row to the adj_matrix, essentially adding the vertex to the matrix.
	
	/* Need to append zeros to the previous rows (EXcluding the one	*
	 * we just added) in order to maintain a square matrix. 		*/
	for (int i = 0; i < adj_matrix.size() - 1; i++) {
		//DEBUGcout << "Pushing zero at index " << i << endl;
		adj_matrix[i].push_back(0); 
	} 
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

	//DEBUG cout << "Removing vertex id: " << u_id << " weight: " << vertices[u_id].weight << endl;
	
	/* Before we remove the vertex, calc number of edges that 	*
	 * will be removed in order to update numEdges. This needs	*
	 * to be done before removing the vertex.					*/
	numEdges -= degree(posU);

	vertices.erase(vertices.begin() + posU); //Remove vertex from vertices list

	/*	Following line delete the row not column from the adj_matrix. */
	adj_matrix.erase(adj_matrix.begin() + posU);

	/* Update vertex positions for those vertices greater than the one being removed as well as *
	 * zeroing the associated column 'to' of the vertex from the adj_matrix.					*/
	for (int i = 0; i < adj_matrix.size(); i++) {
		//Remove associated column for vertex
		adj_matrix[i].erase(adj_matrix[i].begin() + posU);
		//Update vertex positions as vector size has changed
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
	numEdges--; //Decrement numEdges to reflect the change.
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
	//Could be slightly faster by combining the two loops into one.
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
	return numEdges; //I'm keeping track of this so it is easy to return
}

//Returns a vector containing all the vertices.
template <typename T>
vector<vertex<T>> directed_graph<T>::get_vertices() { 
	// I keep track of all vertices in a separate vector "vertices"
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
	/*DEBUG
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
	
	/* In worst case would take n^2 time if all vertices are connected to all vertices but in most cases, 	*
	 * the number of neighbours and second neighbours should be some subset of n. 							*/
	for (auto v : firstNeighbours) {
		vector<vertex<T>> secondNeighbours = get_neighbours(v.id); //Get neighbours of neighbours
		for (auto u : secondNeighbours) {
			//Check if vertex already exists in second_order_neighbours using vector_conains()
			//A vertex cannot be considered a second_order_neighbour of itself and there must be no duplicates
			if ((u.id != u_id) && !vector_contains(second_order_neighbours, u.id)) second_order_neighbours.push_back(u);
		}
	}

	/*DEBUG
	cout << second_order_neighbours.size() << " second order neighbours of " << u_id << ": {";
	for (auto v : second_order_neighbours) {
		 cout << v.id << ", ";
	}
	cout << "}." << endl;
	*/

	return second_order_neighbours; 
}

//Returns true if the second vertex is reachable from the first (can you follow a path of out-edges to get from the first to the second?).
template <typename T>
bool directed_graph<T>::reachable(const int& u_id, const int& v_id) 
{
	return vector_contains(depth_first(u_id), v_id); //Use depth first search to determine reachability
}

// Return true if the graph contains cycles (there is a path from any vertices directly/indirectly to itself), false otherwise.
template <typename T>
bool directed_graph<T>::contain_cycles() 
{ 
	/* Main idea is to use DFS to get all the possible vertices that can have a "back edge" to any other vertex. If a back edge	*
	 * exists, there must be a cycle in the graph.																				*/
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

//Returns a spanning tree of the graph starting at the given vertex using the out-edges. This means every vertex in the tree is reachable from the root.
template <typename T>
directed_graph<T> directed_graph<T>::out_tree(const int& u_id) 
{ 
	/* Using kruskal's "other" algorithm (reverse-delete) in order to get MST. */
	
	/* We will store weights here so we can sort them (decreasing). */
	vector<graph_edge<T>> edges_list; 

	/* Make copy of the graph before we do reverse-delete */
	directed_graph<T> mst_tree;
	mst_tree.numEdges = numEdges;
	mst_tree.adj_matrix = adj_matrix;
	mst_tree.vertices = vertices;

	/* Build our graph_edges vector by looping through the matrix. 							*
	 * If we wanted to optimize for time complexity > space complexity,						*
	 * I could've used another class member vector to keep track of all the edges. 			*
	 * Although, this approach would cause increased time complexity for add/remove edge.	*/
	for(auto v : vertices) 
	{
		for (int i = 0; i<adj_matrix[v.pos].size(); i++) 
		{
			T edgeWeight = adj_matrix[v.pos][i];
			if (edgeWeight > 0) {
				graph_edge<T> edge(v.id, vertices[i].id, edgeWeight);
				edges_list.push_back(edge);
			}
		}
	}

	/* First important step in reverse-delete, sort the edges by weight (decreasing order). */
	sort(edges_list.begin(), edges_list.end(), greater<graph_edge<T>>()); 

	/* Next part is to iterate over all the edges and delete one by one as long as they don't cause				*
	 * the graph to become disconnected.	 																	*/
	for (int i=0; i < edges_list.size(); i++) {
		/* (MST RULE) WHEN |E'|=|V'|-1 BREAK 														*
		 * Not strictly needed as further deletions will cause disconnected graph, 					*
		 * but this can reduce time complexity of the function as it will stop when we have an MST	*/
		if (edges_list.size() == mst_tree.vertices.size()-1) break;
		/* Remove the edge, then check if connected using DFS, if the search returns less vectors than there are in
		 * original graph then the graph has become disconnected due to deletion, put it back and move to next edge, otherwise
		 * the deletion has caused graph to remain connected therefore we can decrement the i and move to next edge. */
		graph_edge<T> deletedEdge = edges_list[i]; /* Save this edge in case it causes  */
		mst_tree.remove_edge(edges_list[i].from_id, edges_list[i].to_id); /* Remove the edge in the graph */

		vector<vertex<T>> dfsResult = mst_tree.depth_first(u_id);

		if (dfsResult.size() == mst_tree.vertices.size()) //Check if graph is connected
		{
			/* After this if, we know that the graph is NOT disconnected, we can proceed with deletion from list. */
			edges_list.erase(edges_list.begin() + i);
			i--; /* Need to decrement i as vector size has changed. */
		} else {
			/* Put the edge back in the graph if it has caused a disconnected graph. 	*
			 * And do NOT delete the edge from our list. 								*/
			mst_tree.add_edge(deletedEdge.from_id, deletedEdge.to_id, deletedEdge.weight); 
		}
	} 

	return mst_tree; /* Return the results */
}

// returns the vertices in the visiting order of a pre-order traversal of the minimum spanning tree starting at the given vertex.
template <typename T>
vector<vertex<T>> directed_graph<T>::pre_order_traversal(const int& u_id, directed_graph<T>& mst) 
{ 
	/* Implemented using iterative approach. I want to get a mix of implementations to gain an understanding	*
	 * of how both work. If this was not the case, I would use recursive implementation for all since they 		*
	 * so short and easier to write.																			*/
	 
	/* Neighbours of vertex of id u_id should be the "left" and "right" children respectively.	*
	 * We can iterate over this using the pre_order iterative algorithm from wk6 lecture slides.*/
	vector<vertex<T>> pre_order_result; //Initialise the results vector to be pushed to.
	
	stack<vertex<T>> s; //Initialise the stack

	vertex<T>* current = new vertex<T>(0,0); //A pointer type was used to implement this as we can't equate a vertex to 'null'.
	*current = mst.get_vertex(u_id); //Must be in MST context not the directed_graph
	
	while (current != nullptr) {
		//DEBUG cout << "Current vertex in pre_order (" << current->id << ") " << endl;
		pre_order_result.push_back(*current); //Visit Current
		vector<vertex<T>> vertexChildren = mst.get_neighbours(current->id);
		/* vertexChildren[0] should be "left" and vertexChildren[1] should be right child.	*
		 * Number of neighbours(children) of a vertex in MST should not be more than 		*
		 * 2 for every vertex. 																*/
		if (vertexChildren.size() > 1) s.push(vertexChildren[1]); 	//Equivalent: if current.rightChild() != null
		if (vertexChildren.size() >= 1) s.push(vertexChildren[0]); 	//Equivalent: if current.leftChild() != null
		if (s.size() == 0) { //To avoid segmentation fault, on end, set current to nullptr
			current = nullptr;
		} else { //Otherwise, continue as normal
			//Below two lines are equivalent to "current = stack.pop()"
			*current = s.top();
			s.pop();
		}
	}
	
	delete current; //Delete "current" from heap as we initialised it using 'new'.

	return pre_order_result; //Return results
}

// returns the vertices in the visiting order of an in-order traversal of the minimum spanning tree starting at the given vertex.
template <typename T>
vector<vertex<T>> directed_graph<T>::in_order_traversal(const int& u_id, directed_graph<T>& mst) 
{ 
	vector<vertex<T>> in_order_results; //Initialise vector to store our results.

	inOrderUtil(in_order_results, mst.get_vertex(u_id), mst); //Needed in separate function to be able to keep results using recursion.

	return in_order_results; //Return results
}
template <typename T>
void directed_graph<T>::inOrderUtil(vector<vertex<T>>& results, const vertex<T>& n, directed_graph<T>& mst) 
{ 
	/* Note: In the lecture slides the code tries to equate a vertex to "null", this cannot be done literally		*
	 * as the vertex can never be null because of its type. My solution is to have a type of vertex that can be 	*
	 * created in which it can be classified as a null vertex that can be checked. This required a bit more code	*	
	 * but is still essentially identical in implementation compared to the recursion code in the lecture slides.	*/

	/* Avoid code duplication by creating the nullV beforehand. */
	vertex<T> nullV(0,0); //Create a fresh vertex
	nullV.nullVertex = true; //Make it a null vertex

	if (n.nullVertex) { 
		return; //Do nothing if we are at a nullVertex, i.e. the child vertex did not exist in this case.
	} else {
		vector<vertex<T>> vertexChildren = mst.get_neighbours(n.id);
		//Need to use if statements to make sure we don't get segmentation errors (in case a vertex has only a left child or no children).
		
		//If left child exists do recursion with normal vertex, otherwise pass with a nullvertrex.
		if (vertexChildren.size() >= 1) { // Greater than or equal meaning AT LEAST the left child exists
			inOrderUtil(results, vertexChildren[0], mst); //Trigger recursion with left child
		} else {
			/* Left child doesn't exist but still need to pass nullvertex to be consistent with algorithm pattern. */
			inOrderUtil(results, nullV, mst); //Trigger recursion with null vertex.
		}

		results.push_back(n); //inOrder required push_back BETWEEN ifs.

		//If right child exists do recursion with normal vertex, otherwise pass with a nullvertrex.
		if (vertexChildren.size() > 1) { // Greater than means the right child MUST exists (as well as left).
			inOrderUtil(results, vertexChildren[1], mst); //Trigger recursion with right child
		} else {
			/* Right child doesn't exist but still need to pass nullvertex to be consistent with algorithm pattern. */
			inOrderUtil(results, nullV, mst); //Trigger recursion with null vertex.
		};
	}
}

// returns the vertices in ther visitig order of a post-order traversal of the minimum spanning tree starting at the given vertex.
template <typename T>
vector<vertex<T>> directed_graph<T>::post_order_traversal(const int& u_id, directed_graph<T>& mst) 
{ 
	vector<vertex<T>> post_order_results; //Initialise vector to store our results.

	postOrderUtil(post_order_results, mst.get_vertex(u_id), mst); //Needed in separate function to be able to keep results using recursion.

	return post_order_results; //Return results
}
template <typename T>
void directed_graph<T>::postOrderUtil(vector<vertex<T>>& results, const vertex<T>& n, directed_graph<T>& mst) 
{ 
	/* Note: In the lecture slides the code tries to equate a vertex to "null", this cannot be done literally		*
	 * as the vertex can never be null because of its type. My solution is to have a type of vertex that can be 	*
	 * created in which it can be classified as a null vertex that can be checked. This required a bit more code	*	
	 * but is still essentially identical in implementation compared to the recursion code in the lecture slides.	*/

	/* Avoid code duplication by creating the nullV beforehand. */
	vertex<T> nullV(0,0); //Create a fresh vertex
	nullV.nullVertex = true; //Make it a null vertex

	if (n.nullVertex) { 
		return; //Do nothing if we are at a nullVertex, i.e. the child vertex did not exist in this case.
	} else {
		vector<vertex<T>> vertexChildren = mst.get_neighbours(n.id);
		//Need to use if statements to make sure we don't get segmentation errors (in case a vertex has only a left child or no children).
		
		//If left child exists do recursion with normal vertex, otherwise pass with a nullvertrex.
		if (vertexChildren.size() >= 1) { // Greater than or equal meaning AT LEAST the left child exists
			postOrderUtil(results, vertexChildren[0], mst); //Trigger recursion with left child
		} else {
			/* Left child doesn't exist but still need to pass nullvertex to be consistent with algorithm pattern. */
			postOrderUtil(results, nullV, mst); //Trigger recursion with null vertex.
		}

		//If right child exists do recursion with normal vertex, otherwise pass with a nullvertrex.
		if (vertexChildren.size() > 1) { // Greater than means the right child MUST exists (as well as left).
			postOrderUtil(results, vertexChildren[1], mst); //Trigger recursion with right child
		} else {
			/* Right child doesn't exist but still need to pass nullvertex to be consistent with algorithm pattern. */
			postOrderUtil(results, nullV, mst); //Trigger recursion with null vertex.
		};
		
		results.push_back(n); //Only different part of postOrder is to have the push_back at after both ifs.
	}
}

// Return a vector containing a sorted list of the vertices in descending order of their significance.
template <typename T>
vector<vertex<T>> directed_graph<T>::significance_sorting() 
{ 
	vector<vertex<T>> sortedVertices = vertices; /* Make a copy of the vertices vector to be sorted. */

	/* Calculate the popularity of each vertex (twitter user) by summing how many times the user was liked and their follower count.
	 * This will be summed against vertex weight (amt of followers) and will provide, in my opinion,
	 * a decent means to rank users based on "popularity". */
	
	for (int i = 0; i < sortedVertices.size(); i++) {
		double popularityCount = 0;
		for (int j=0; j<adj_matrix[i].size(); j++) {
			/* This is the to column for every vertex, this means this is the number of times any	*
			 * particular vertex (user) has liked this particular vertex (user).					*/
			popularityCount += (double)adj_matrix[j][i];
		}
		sortedVertices[i].popularity = (sortedVertices[i].weight + popularityCount);
	}

	/* See greater operator function definition in vertex class, it essentially will compare vertex popularity	*
	 * and sort in decreasing order using what was just calculated above. 										*/
	sort(sortedVertices.begin(), sortedVertices.end(), greater<vertex<T>>());  /* Sort by vertex popularity using <algrithm> library. */

	return sortedVertices; 
}

#endif