#include "kruskal.h"
#include <sstream>

void buildGraph( Graph &G, DisjSets &D, MinHeap &M )
{
	while( M.size( )!=0 ){
		edge e = M.pop( );
		int r1 = D.find(e.num1);
		int r2 = D.find(e.num2);
		if( r1 != r2 )
		{
			D.unionSets(r1,r2);
			G.insert(e);
		}
	}
}


int main(int argc, char const *argv[])
{

	Graph mst;
	DisjSets comps;
	MinHeap edge_heap;
	MinPathTree mpt;
	string line;
	string command;
	vector<int> items;
	edge A;
	int r1, r2;

	do{
		getline(cin, line);
		stringstream ss(line);
		ss >> command;

		if( command == "BID")
		{
			for( string string_items; ss>>string_items; )
			{
				items.push_back(stoi(string_items));
			}

			A.update(items[0],items[1],items[2]);
			edge_heap.insert(A);
			items.clear( );
		}

		else if( command == "MANDATORY" )
		{
			for( string string_items; ss>>string_items; )
			{
				items.push_back(stoi(string_items));
			}

			A.update(items[0],items[1],items[2]);
			mst.insert(A);
			r1 = comps.find(A.num1);
			r2 = comps.find(A.num2);
			comps.unionSets(r1,r2);
			items.clear( );
		}

		else if( command == "COST?" )
		{
			buildGraph(mst, comps, edge_heap);
			cout<<mst.cost<<endl;
		}

		else if( command == "COMPONENTS?" )
		{
			buildGraph(mst, comps, edge_heap);
			cout<<comps.components<<endl;
		}

		else if( command == "CYCLE?" )
		{
			buildGraph(mst, comps, edge_heap);
			if( comps.cycle )
				cout<<"YES"<<endl;
			else
				cout<<"NO"<<endl;
		}

		else if( command == "LIST?" )
		{
			buildGraph(mst, comps, edge_heap);
			mst.print( );
		}

		else if( command == "SHORTEST_PATH?" )
		{
			for( string string_items; ss>>string_items; )
			{
				items.push_back(stoi(string_items));
			}
			buildGraph(mst, comps, edge_heap);
			mpt.buildTree(mst);
			mpt.findPath(items[0],items[1]);

			items.clear( );
		}
	


	}while(command != "END");
	return 0;
}

