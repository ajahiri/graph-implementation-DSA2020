#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <array>
#include <list>
#include <forward_list>
#include <deque>
#include <map>
#include <cstddef>
#include <string>
#include <utility>
#include <algorithm>
#include <limits>
#include <optional>
#include <exception>
#include <stdexcept>
#include <math.h>

#include "directed_graph.hpp"

using namespace std;

/*
 * Computes the shortest distance from u to v in graph g.
 * The shortest path corresponds to a sequence of vertices starting from u and ends at v,
 * which has the smallest total weight of edges among all possible paths from u to v.
 */
template <typename T>
vector<vertex<T>> shortest_path(directed_graph<T> g, int u_id, int v_id) {

	/*Don't bother doing anything if the target vertex isn't reachable*/
	if (!g.reachable(u_id, v_id)) {
		vector<vertex<T>> empty_path;
		return empty_path;
	}

	vertex<T> u = g.get_vertex(u_id); /* Vertex from */
	vertex<T> v = g.get_vertex(v_id); /* Vertex to */
	vertex<T> current_vertex = u; /* Set current vertex to u */

	vector<vertex<T>> vertices = g.get_vertices(); /*Helper to avoid having to get vertices so many times*/
	vector<vector<T>> matrix = g.get_matrix(); /*Needed as matrix is a private member*/

	T distance[vertices.size()]; /*Distances table, 1 entry for each vertex*/
	fill_n(distance, vertices.size(), numeric_limits<T>::max()); /* Set all distances to "infinity" */
	distance[u.pos] = 0; /* Set distance for u to 0 */

	int previous[vertices.size()]; /* Table of previous node's ids */
	fill_n(previous, vertices.size(), -1); /*Set all prev nodes to "undefined"*/

	vector<vertex<T>> unvisited = vertices; /*Mark all vertices as unvisited*/

	while (g.vector_contains(unvisited, v.id) && (unvisited.size() != 0)) {
		vector<vertex<T>> curr_neighbours = g.get_neighbours(current_vertex.id);
		for (vertex<T> neighbour : curr_neighbours) {
			/*For each UNVISITED neighbour of the current vertex*/
			if (g.vector_contains(unvisited, neighbour.id)) {
				/*Compare the distance of each neighbour to the distance of
				 *current plus the edge weight of the edge joining them*/
				T distance_current_plus_edge = distance[current_vertex.pos] + matrix[current_vertex.pos][neighbour.pos];
				if (distance_current_plus_edge < distance[neighbour.pos]) {
					/* distance of alternative route is smaller, update distance */
					distance[neighbour.pos] = distance_current_plus_edge;
					previous[neighbour.pos] = current_vertex.id;
				} /*Don't need to worry about else case as distance doesn't change if that's the case*/
			}
		}

		/* Mark current vertex at visited */
		for (int i = 0; i < unvisited.size(); i++) {
			if (unvisited[i].id == current_vertex.id) {
				unvisited.erase(unvisited.begin() + i);
				break;
			}
		}

		/*Get unvisited vertex with smallest tentative distance */
		T min_distance = numeric_limits<T>::max(); /*Start with large distance*/
		vertex<T> min_vertex = u; /*Start with something*/
		if (unvisited.size() > 0) {
			for (int i = 0; i < unvisited.size(); i++) {
				if (distance[unvisited[i].pos] < min_distance) {
					min_distance = distance[unvisited[i].pos];
					min_vertex = unvisited[i];
				}
			}
		}

		current_vertex = min_vertex; /* Set minimum as current */
	}

	/* Dijkstra's ends here but we need the path between u and v */

	/* Get the shortest path by looping through vertex ids in "previous" table. */
	int prev_id = v.id;

	vector<vertex<T>> shortest_path; /*Results stored here*/

	while (prev_id != u.id && (shortest_path.size() <= vertices.size())) {
		/*-1 in previous denotes that no previous node exists*/
		vertex<T> previous_vertex = g.get_vertex(prev_id);
		if (previous[previous_vertex.pos] != -1) {
			shortest_path.push_back(previous_vertex); /*Push back the vertex with that id*/
		}
		else {
			shortest_path.push_back(previous_vertex);
			break;
		}
		prev_id = previous[previous_vertex.pos]; /*Update previous id to the node before previous*/
	}
	/* Will get to last node "u" and end, push this back as its included in path. */
	shortest_path.push_back(u);

	/* Reverse the vector to get correct path order */
	reverse(shortest_path.begin(), shortest_path.end());

	return shortest_path; /*Return result*/
}

/*
 * A helper function to gind SCCs using Tarjan's algorithm.
 * This function requires many references to the position of the vertices, as such
 * it will run solely using position integers of u & v.
 */
template <typename T>
void scc_util(directed_graph<T>& g, int u_pos, int disc[], int low[],
	stack<int>* connected_ancestors, bool stack_member[],
	vector<vector<vertex<T>>>& scc_results)
{
	//Use of static integer variable as time must be kept track of for all iterations of scc_util
	static int time = 0;

	vector<vertex<T>> vertices = g.get_vertices(); /*For reference when pushing back vertices to results.*/

	disc[u_pos] = low[u_pos] = ++time;
	connected_ancestors->push(u_pos);
	stack_member[u_pos] = true;

	//Get the adjacency matrix
	auto adj_matrix = g.get_matrix();

	//Iterate through all vertices adjacent to the current vertex (u_pos)
	for (int v_pos = 0; v_pos < adj_matrix[u_pos].size(); v_pos++)
	{
		//Must only iterate over adjacent vertices to u, if not the case, skip iteration
		if (adj_matrix[u_pos][v_pos] == 0) continue;

		//Below is only executed for adjacent vertices to u

		//If v has not been visited yet, recursively call SCC on it
		if (disc[v_pos] == -1)
		{
			scc_util(g, v_pos, disc, low, connected_ancestors, stack_member, scc_results);

			//Check if subtree rooted with v has a connection to one of the ancestors of u
			low[u_pos] = min(low[u_pos], low[v_pos]);
		}

		//Update the low value of u only if i is still in stack
		else if (stack_member[v_pos] == true) low[u_pos] = min(low[u_pos], disc[v_pos]);
	}

	/*
	 * At this point, a head node was found.
	 * In this section of code, the program builds the vector for a single
	 * SCC and pushes that vector to the vector of vectors result "scc_result"
	 * This in turn gives us all SCCs in the graph.
	 */

	int w_pos = 0; //Used to store the position popped from the stack
	if (low[u_pos] == disc[u_pos])
	{
		vector<vertex<T>> scc_vector;
		while (connected_ancestors->top() != u_pos)
		{
			w_pos = (int)connected_ancestors->top(); //Save the top of the stack as it will be popped later
			scc_vector.push_back(vertices[w_pos]); //Push back the vertex to its results vectors
			stack_member[w_pos] = false; //Element is getting popped therefore update the array
			connected_ancestors->pop(); //Pop the top of the stack
		}
		w_pos = (int)connected_ancestors->top(); //Save the top of the stack as it will be popped later
		scc_vector.push_back(vertices[w_pos]); //Push back the final vertex
		scc_results.push_back(scc_vector); //Pushback this iterations whole vector of results to total results
		stack_member[w_pos] = false; //Element is getting popped therefore update the array
		connected_ancestors->pop(); //Pop the top of the stack
	}
}


/*
 * Computes the strongly connected components of the graph.
 * A strongly connected component is a subset of the vertices
 * such that for every pair u, v of vertices in the subset,
 * v is reachable from u and u is reachable from v.
 */
template <typename T>
vector<vector<vertex<T>>> strongly_connected_components(directed_graph<T> g) {
	int vertices_size = g.get_vertices().size(); /*Helper to avoid having to get vertices so many times*/
	vector<vector<vertex<T>>> scc_results;

	int* disc = new int[vertices_size]; //Discovery times of visited vertices in SCC
	int* low = new int[vertices_size]; //Earliest visited vertex that can be reached from subtree rooted with current vertex
	stack<int>* connected_ancestors = new stack<int>(); //Stack to store connected ancestors
	bool* stack_member = new bool[vertices_size]; //bool array to check whether a vertex is in the stack

	//Initialize the above arrays with zeros
	for (int i = 0; i < vertices_size; i++) {
		disc[i] = -1; //Initialise all discovery times to -1
		low[i] = -1; //Initialise all vertex positions to -1 
		stack_member[i] = false; //No vertex positions in the stack, initialise whole array to false
	}

	/*
	 * Call the helper function to find all the SCCs rooted by every vertex in the graph.
	 */
	for (int u_pos = 0; u_pos < vertices_size; u_pos++) {
		if (disc[u_pos] == -1) scc_util(g, u_pos, disc, low, connected_ancestors, stack_member, scc_results);
	}

	return scc_results;
}

/*
 * Computes a topological ordering of the vertices.
 * For every vertex u in the order, and any of its
 * neighbours v, v appears later in the order than u.
 * You will be given a DAG as the argument.
 */
template <typename T>
vector<vertex<T>> topological_sort(directed_graph<T> g) {
	/*
	 * Implementing topological sort using Kahn's algorithm.
	 */
	vector<vertex<T>> vertices = g.get_vertices(); //Reference to vertices (private member)
	vector<vertex<T>> topo_order; //Store the result here, vertices sorted topologically

	set<int> vertices_no_incoming; //Using a set of vertex ids, actual vertices can be accessed using g.get_vertex(u.id)
	for (auto u : vertices) {
		if (g.in_degree(u.id) == 0) vertices_no_incoming.insert(u.id);
	}

	while (!vertices_no_incoming.empty()) {
		/*
		 * Algorithm desc doesn't specify needing to take a certain element
		 * from the set. Just take whatever's at the beginning.
		 */
		vertex<T> v = g.get_vertex(*vertices_no_incoming.begin()); //Get the vertex given by id
		vertices_no_incoming.erase(vertices_no_incoming.begin()); //Remove the element we just assigned to v
		topo_order.push_back(v); //Push to results
		for (auto neighbour : g.get_neighbours(v.id)) {
			g.remove_edge(v.id, neighbour.id); //Remove edge from graph

			//Add neighbour vertex to set if it has no incoming edges
			if (g.in_degree(neighbour.id) == 0) vertices_no_incoming.insert(neighbour.id);
		}
	}

	return topo_order;
}

/*
 * Computes the lowest cost-per-person for delivery over the graph.
 * u is the source vertex, which send deliveries to all other vertices.
 * vertices denote cities; vertex weights denote cities' population;
 * edge weights denote the fixed delivery cost between cities, which is irrelevant to
 * the amount of goods being delivered.
 */
template <typename T>
T low_cost_delivery(directed_graph<T> g, int u_id) {
	/*
	 * Using the out_tree() function from assignment 1, I implemented reverse-delete algorithm to get ans MST.
	 * The resulting MST output will allow me to just sum all edge weights and vertex weights to get the lowest cost-per-person.
	 */

	directed_graph<T> mst = g.out_tree(u_id);         //Need access to the MST
	vector<vertex<T>> vertices = mst.get_vertices();  //Vertices reference
	vector<vector<T>> adj_matrix = mst.get_matrix();  //Matrix reference (for access to edge weights)

	double edge_weight_total = 0;
	double vertex_weight_total = 0;

	//Sum all the edge weights of the mst for vertices reachable by root (u_id) essentially giving us the optimal (minimum) cost to all other nodes.
	for (auto v : vertices) {
		if (!mst.reachable(u_id, v.id)) continue; //Only add edge if the vertex is reachable from root (u_id)
		for (int i = 0; i < adj_matrix[v.pos].size(); i++) {
			edge_weight_total += (double)adj_matrix[v.pos][i]; //Sum edge weights (no need to check for 0/non weights as it wont affect sum)
		}
		if (v.id != u_id) vertex_weight_total += (double)v.weight; //Sum edge weights excluding source vertex weight
	}

	if (vertex_weight_total == 0) {
		return 0; //Avoid dividing by 0 for vertices that have no out_edges
	}
	else {
		/*
		 * Return the result, I used round() to properly round the result as in some cases,
		 * the integer division would cause a number that should be rounded up to be rounded down.
		 * Hence, it would be more correct to use round().
		 */
		return round(edge_weight_total / vertex_weight_total); 
	}
}
