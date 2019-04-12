#include "kruskal.h"

void Graph::insert( edge e )
{
	graph[e.cost] = e;
	cost += e.cost;
}


void Graph::print( )
{
	for( map<int,edge>::iterator it = graph.begin(); it != graph.end(); ++it )
	{
		cout<<"("<<it->second.num1<<","<<it->second.num2<<")"<<" ";
	}
	cout<<endl;
}

int DisjSets::find( int x )
{
	if( S.count(x) == 0 )
	{
		S[x] = -1;
		components += 1;
		return x;
	}
	else
	{
		if( S[x]<0 )
		{
			return x;
		}
		else
		{
			return find(S[x]);
		}
	}
}

void DisjSets::unionSets( int root1, int root2 )
{
	if( root1 == root2 )
	{
		cycle = true;
	}
	else
	{
		S[root2] = root1;
		components -= 1;
	}
}


void MinHeap::insert( edge e )
{
	heap.push_back(e);
	percolateUp(heap.size( )-1);
}

edge MinHeap::pop( )
{
	edge min = heap[0];
	heap[0] = heap.back();
	heap.pop_back( );	
	percolateDown(0);
	return min;
}

int MinHeap::size( )
{
	return heap.size( );
}

void MinHeap::percolateUp( int n )
{
	while( n > 0 && heap[n].cost < heap[parent(n)].cost )
	{
		swap(n,parent(n));
	}
}

void MinHeap::percolateDown( int n )
{
	while( rchild(n) < heap.size() && (heap[n].cost > heap[lchild(n)].cost || heap[n].cost > heap[rchild(n)].cost) )
	{
		if( heap[lchild(n)].cost < heap[rchild(n)].cost )
		{
			swap(n,lchild(n));
		}
		else
		{
			swap(n,rchild(n));
		}
	}
}

void MinHeap::swap( int n1, int n2 )
{
	edge temp = heap[n1];
	heap[n1] = heap[n2];
	heap[n2] = temp;
}

int MinHeap::lchild( int n )
{
	return 2*n+1;
}

int MinHeap::rchild( int n )
{
	return 2*n+2;
}

int MinHeap::parent( int n )
{
	return (n-1)/2;
}

void MinPathTree::buildTree( Graph G )
{
	for( map<int,edge>::iterator it = G.graph.begin(); it != G.graph.end(); ++it )
	{
		vertecies[it->second.num1][it->second.num2] = it->second.cost;
		vertecies[it->second.num2][it->second.num1] = it->second.cost;
	}	
}

void MinPathTree::findPath( int start, int end )
{
 	vector<int>init = {start};
 	node a = make_tuple(start, 0, init);
 	S.insert(a);
 	a = make_tuple(end, 10000000000, init);
 	bin[end] = a;

 	while( !S.empty( ) && get<1>(*S.begin( )) < get<1>(bin[end]) )
	  {
	        set<node, CompareCost>::iterator it = S.begin( );
		int curr_node = get<0>(*it);
		int prev_node = start;
		
		if( curr_node != start )
		  {
		    vector<int> prev_path = get<2>(bin[curr_node]);
		    prev_node = prev_path[prev_path.size()-2];
		  }
 	     
 		//go through connecting nodes
 		for( map<int,int>::iterator map_it = vertecies[curr_node].begin( ); map_it != vertecies[curr_node].end( ); map_it++ )
 		{
      			//don't go backwards
 			if( map_it->first != prev_node )
 			{
 				//new node discovered
 				if( map_it->first != end && bin.count(map_it->first) == 0 )
 				{
 					vector<int>node_path = get<2>(*it);
 					node_path.push_back(map_it->first);
 					a = make_tuple(map_it->first, get<1>(*it)+map_it->second, node_path);
 					bin[map_it->first] = a;
 					S.insert(a);
 				}
 				//shorter path discovered
 				else if( get<1>(bin[map_it->first]) > get<1>(*it)+map_it->second )
 				{
 					S.erase(bin[map_it->first]);
 					vector<int>node_path = get<2>(*it);
 					node_path.push_back(map_it->first);
 					a = make_tuple(map_it->first, get<1>(*it)+map_it->second, node_path);
 					bin[map_it->first] = a;
 					S.insert(a);
 				}
 				//do nothing if path is longer
 			}
 		}
		S.erase(it);
 	}

 	vector<int> shortest_path = get<2>(bin[end]);
 	for( int i = 0; i < shortest_path.size( ); i++ )
 	{
 		cout<<shortest_path[i]<<" ";
 	}
 	cout<<endl;
}
