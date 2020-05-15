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

	cout << "SIGNIFICANCE SORT Results: (ID, WEIGHT)" << endl;
	for (auto v : g.significance_sorting()) {
		cout << "(" << v.id << ", " << v.weight << ") -> ";
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

	/*
	directed_graph<double> g1;

	vertex<double> v0(0, 0.25); 
	vertex<double> v1(1, 1.41);
	vertex<double> v2(2, 2.32);
	vertex<double> v3(3, 3.66);
	vertex<double> v4(4, 4.12);

	g1.add_vertex(v0);
	g1.add_vertex(v1);
	g1.add_vertex(v2);
	g1.add_vertex(v3);
	g1.add_vertex(v4);

    g1.add_edge(0, 2, 10);
	g1.add_edge(0, 3, 20);
	g1.add_edge(2, 0, 30);
	g1.add_edge(2, 4, 40);
	g1.add_edge(4, 0, 50);
	g1.add_edge(3, 4, 60);
    
	cout << "all 2nd-order neighbours of 0: ";
	vector<vertex<double>> second_neighbour_list0 = g1.get_second_order_neighbours(0);
	for (vertex<double> snb : second_neighbour_list0) {
	 	cout << "(" << snb.id << ", " << snb.weight << ") ";
	}
	cout << endl;

    cout << "all 2nd-order neighbours of 1: ";
	vector<vertex<double>> second_neighbour_list1 = g1.get_second_order_neighbours(1);
	for (vertex<double> snb : second_neighbour_list1) {
	 	cout << "(" << snb.id << ", " << snb.weight << ") ";
	}
	cout << endl;

    cout << "all 2nd-order neighbours of 2: ";
	vector<vertex<double>> second_neighbour_list2 = g1.get_second_order_neighbours(2);
	for (vertex<double> snb : second_neighbour_list2) {
	 	cout << "(" << snb.id << ", " << snb.weight << ") ";
	}
	cout << endl;

    cout << "all 2nd-order neighbours of 3: ";
	vector<vertex<double>> second_neighbour_list3 = g1.get_second_order_neighbours(3);
	for (vertex<double> snb : second_neighbour_list3) {
	 	cout << "(" << snb.id << ", " << snb.weight << ") ";
	}
	cout << endl;
	*/
}