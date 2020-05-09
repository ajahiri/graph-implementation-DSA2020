#include "directed_graph.cpp"

int main() {
	/*
	directed_graph<int> g;


	//Vertex indexes start from 0, following visual representation from 
	//assessment description A=0, B=1, etc
	vertex<int> va = vertex<int>(0, 800);		//A
	vertex<int> vb = vertex<int>(1, 3000);		//B
	vertex<int> vc = vertex<int>(2, 400);		//C
	vertex<int> vd = vertex<int>(3, 710);		//D
	vertex<int> ve = vertex<int>(4, 221);		//E

	g.add_vertex(va);
	g.add_vertex(vb);
	g.add_vertex(vc);
	g.add_vertex(vd);
	g.add_vertex(ve);

	g.print_matrix();

	g.add_edge(va.id, vb.id, 6); //A-B 6
	g.add_edge(va.id, vc.id, 9); //A-C 9
	g.add_edge(vb.id, ve.id, 3); //B-E 3
	g.add_edge(vc.id, vd.id, 4); //C-D 4
	g.add_edge(vd.id, va.id, 1); //D-A 1
	g.add_edge(vd.id, vc.id, 7); //D-C 7
	g.add_edge(vd.id, ve.id, 5); //D-E 5

	cout << "Printing with " << g.num_edges() << " edges  and " << g.num_vertices() << " vertices:" << endl;
	g.print_matrix();
	*/
	/* Test Delete
	g.remove_vertex(0); //After this remove, 0 now corresponds to B not A and IDs are decremented accordingly.	
	cout << "Printing with " << g.num_edges() << " edges  and " << g.num_vertices() << " vertices:" << endl;
	g.print_matrix();
	*/
	/*
	cout << "(3) should have in-degree of " << g.in_degree(3) << endl;
	cout << "(3) should have out-degree of " << g.out_degree(3) << endl;
	cout << "(3) should have total degree of " << g.degree(3) << endl;
	g.get_neighbours(0);
	g.get_second_order_neighbors(0);
	
	cin.get(); //Don't stop debugging
	*/
}