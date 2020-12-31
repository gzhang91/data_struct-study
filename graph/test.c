#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#define INSERT_EDGE(g, bv, ev, wv) \
	e.start = bv;  \
	e.end = ev;    \
	e.weight = wv; \
	GraphInsertEdge(g, e);

int main(void) {

	Graph *g = GraphInit(0, 5);
	GraphInsertNode(g, 'A');
	GraphInsertNode(g, 'B');
	GraphInsertNode(g, 'C');
	GraphInsertNode(g, 'D');
	GraphInsertNode(g, 'E');

	Edge e = { 'A', 'B', 1 };
	GraphInsertEdge(g, e);
	INSERT_EDGE(g, 'A', 'C', 1);
	INSERT_EDGE(g, 'A', 'D', 1);
	INSERT_EDGE(g, 'A', 'E', 1);
	INSERT_EDGE(g, 'B', 'C', 1);
	INSERT_EDGE(g, 'C', 'D', 1);
	INSERT_EDGE(g, 'D', 'E', 1);

	GraphShow(g);
	GraphDestroy(g);

	return 0;
}