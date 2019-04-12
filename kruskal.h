#ifndef KRUSKAL_H
#define KRUSKAL_H

using namespace std;

#include <vector>
#include <string>
#include <utility>
#include <map>
#include <iostream>
#include <tuple>
#include <set>

struct edge
{

	void update( int n1, int n2, int c )
	{
		int min;
		int max;
		if( n1>n2 )
		{
			max = n1;
			min = n2;
		}
		else
		{
			max = n2;
			min = n1;
		}
		num1 = min;
		num2 = max;
		cost = c;
	}

	int num1;
	int num2;
	int cost;

};

class Graph
{

	public:

		void insert( edge e );
		void print( );

		int cost = 0;
		map<int,edge> graph;

};

class DisjSets
{

	public:

		int find( int x );
		void unionSets( int root1, int root2 );

		bool cycle = false;
		int components = 0;

	private:

		map<int, int> S;

};



class MinHeap
{

	public:

		void insert( edge e );
		edge pop( );
		int size( );
		
	private:

		void percolateUp( int n );
		void percolateDown( int n );
		void swap( int n1, int n2 );
		int lchild( int n );
		int rchild( int n );
		int parent( int n );

		vector<edge> heap;

};

// for dijstra's algorithm. 1st element is node number, second is the cumulative cost, third is the path
typedef tuple<int, int, vector<int> > node;


class CompareCost
{
	public:
		bool operator( )( node n1, node n2 )
		{
			return get<1>(n1) < get<1>(n2);
		}
};

class MinPathTree
{

	public:

		void buildTree( Graph G );
		void findPath( int start, int end );


	private:

		set<node, CompareCost> S;
		map<int, map<int,int> > vertecies;
		map<int, node> bin;

};

#endif
