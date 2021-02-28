#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#define INSERT_EDGE(g, bv, ev, wv) \
	e.start = bv;  \
	e.end = ev;    \
	e.weight = wv; \
	GraphInsertEdge(g, e);

int main(void) {

	Graph *g = GraphInit(0, 7);
	GraphInsertNode(g, 'A');
	GraphInsertNode(g, 'B');
	GraphInsertNode(g, 'C');
	GraphInsertNode(g, 'D');
	GraphInsertNode(g, 'E');
	GraphInsertNode(g, 'F');
	GraphInsertNode(g, 'G');

	Edge e;
	INSERT_EDGE(g, 'A', 'B', 50);
	INSERT_EDGE(g, 'A', 'C', 60);
	INSERT_EDGE(g, 'B', 'D', 65);
	INSERT_EDGE(g, 'B', 'E', 40);
	INSERT_EDGE(g, 'C', 'D', 52);
	INSERT_EDGE(g, 'C', 'G', 45);
	INSERT_EDGE(g, 'D', 'E', 50);
	INSERT_EDGE(g, 'D', 'F', 30);
	INSERT_EDGE(g, 'D', 'G', 42);
	INSERT_EDGE(g, 'E', 'F', 70);

	
	GraphShow(g);

	printf("深度优先序列: ");
	DFSTravel(g);
	printf("广度优先序列: ");
	BFSTravel(g);
	printf("连通分量为: ");
	CalcConnectedComponent(g);

	GraphDestroy(g);

	return 0;
}