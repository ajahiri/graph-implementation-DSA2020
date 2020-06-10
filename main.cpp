#include "directed_graph.hpp"

int main() {
    
	directed_graph<int> g;
	//Vertex indexes start from 0, following visual representation from 
	//assessment description A=0, B=1, etc
	vertex<int> va = vertex<int>(0, 800);		//A
	vertex<int> vb = vertex<int>(1, 3000);		//B
	vertex<int> vc = vertex<int>(2, 400);		//C
	vertex<int> vd = vertex<int>(3, 710);		//D
	vertex<int> ve = vertex<int>(4, 221);		//E
	vertex<int> vf = vertex<int>(5, 865);		//E

	g.add_vertex(va);
	g.add_vertex(vb);
	g.add_vertex(vc);
	g.add_vertex(vd);
	g.add_vertex(ve);
	g.add_vertex(vf);

	//g.print_matrix();
	
	g.add_edge(0, 1, 6);
	g.add_edge(0, 2, 9);
	g.add_edge(1, 4, 3);
	g.add_edge(2, 3, 4);
	g.add_edge(3, 2, 7);
	g.add_edge(3, 0, 1);
	g.add_edge(3, 4, 5);
	g.add_edge(1, 5, 2);
	//g.add_edge(4, 0, 5);
	

	cout << "Printing with " << g.num_edges() << " edges  and " << g.num_vertices() << " vertices:" << endl;
	g.print_matrix();
	
	//Test Delete
	/*
	g.remove_vertex(0); //After this remove, 0 now corresponds to B not A and IDs are decremented accordingly.	
	
	g.remove_vertex(2);
	cout << "Printing with " << g.num_edges() << " edges  and " << g.num_vertices() << " vertices:" << endl;
	g.print_matrix();
	*/
	cout << "(0) should have in-degree of " << g.in_degree(0) << endl;
	cout << "(0) should have out-degree of " << g.out_degree(0) << endl;
	cout << "(0) should have total degree of " << g.degree(0) << endl;
	
	cout << "Neighbours of (A)=> ";
	for (auto v : g.get_neighbours(0)) {
		cout << "(" << v.id << ") ";
	}
	cout << endl;
	
	cout << "Second Neighbours of (A)=> ";
	for (auto v : g.get_second_order_neighbours(0)) {
		cout << "(" << v.id << ") ";
	}
	cout << endl;
	
	cout << "DFS Results: " << endl;
	for (auto v : g.depth_first(0)) {
		cout << "(" << v.id << ") -> ";
	}
	cout << "X" << endl;
	
	cout << "BFS Results: " << endl;
	for (auto v : g.breadth_first(0)) {
		cout << "(" << v.id << ") -> ";
	}
	cout << "X" << endl;
	
	//Test Reachable
	cout << "(A) reachable (A)? " << g.reachable(4,4) << endl;

	//Test Cyclic
	cout << "Graph cyclic? " << g.contain_cycles() << endl;

	cout << "-------------- PRINTING MST DATA --------------" << endl;
	directed_graph<int> mst_tree = g.out_tree(0);
	mst_tree.print_matrix();

	cout << endl;

	cout << "SIGNIFICANCE SORT Results: (ID, POPULARITY)" << endl;
	for (auto v : g.significance_sorting()) {
		cout << "(" << v.id << ", " << v.popularity << ") -> ";
	}
	cout << "X" << endl;

	cout << endl;

	cout << "PRE_ORDER Results: (ID, WEIGHT)" << endl;
	
	for (auto v : g.pre_order_traversal(mst_tree.get_vertex(0).id, mst_tree)) {
		cout << "(" << v.id << ", " << v.weight << ") -> ";
	}
	cout << "X" << endl;

	cout << endl;

	cout << "IN_ORDER Results: (ID, WEIGHT)" << endl;
	for (auto v : g.in_order_traversal(mst_tree.get_vertex(0).id, mst_tree)) {
		cout << "(" << v.id << ", " << v.weight << ") -> ";
	}
	cout << "X" << endl;

	cout << endl;

	cout << "POST_ORDER Results: (ID, WEIGHT)" << endl;
	for (auto v : g.post_order_traversal(mst_tree.get_vertex(0).id, mst_tree)) {
		cout << "(" << v.id << ", " << v.weight << ") -> ";
	}
	cout << "X" << endl;

	cout << "----------- STOP PRINTING MST DATA ------------" << endl;

	cout << "----------- END MAIN OUTPUT ------------" << endl;
}

/*Main 2*/
/*
* A main function for you to build and run your
* own tests with.
* This file is not part of the marking, so you
* can do anything you want here.
*/
#include <iostream>

#include "directed_graph_algorithms.cpp"

int main() {
	directed_graph<int> g;
	//Vertex indexes start from 0, following visual representation from 
	//assessment description A=0, B=1, etc
	vertex<int> va = vertex<int>(0, 800);        //A
    vertex<int> vb = vertex<int>(1, 300);        //B
    vertex<int> vc = vertex<int>(2, 400);        //C
    vertex<int> vd = vertex<int>(3, 710);        //D
    vertex<int> ve = vertex<int>(4, 221);        //E
 
    g.add_vertex(va);
    g.add_vertex(vb);
    g.add_vertex(vc);
    g.add_vertex(vd);
    g.add_vertex(ve); 
 
    g.add_edge(va.id, vb.id, 600); //A-B 6
    g.add_edge(va.id, vc.id, 900); //A-C 9
    g.add_edge(vb.id, ve.id, 3000); //B-E 3
    g.add_edge(vc.id, vd.id, 4000); //C-D 4
    g.add_edge(vd.id, va.id, 1); //D-A 1
    g.add_edge(vd.id, vc.id, 700); //D-C 7
    g.add_edge(vd.id, ve.id, 500); //D-E 5
	
    g.print_matrix();

    cout << "Short path A-B" << endl;
	
	for (auto v : shortest_path(g, va.id, vb.id)) {
		cout << "(" << v.id << ", " << v.weight << ") ";
	}
	cout << endl;

	cout << "SCCs" << endl;
	strongly_connected_components(g);

    cout << "Low cost delivery from A: " << low_cost_delivery(g, va.id) << endl;
    cout << "Low cost delivery from B: " << low_cost_delivery(g, vb.id) << endl;
    cout << "Low cost delivery from C: " << low_cost_delivery(g, vc.id) << endl;
    cout << "Low cost delivery from D: " << low_cost_delivery(g, vd.id) << endl;
    cout << "Low cost delivery from E: " << low_cost_delivery(g, ve.id) << endl;
}