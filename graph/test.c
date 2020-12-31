#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(void) {

	Graph *g = GraphInit(0, 5);
	GraphInsertNode(g, 'A');
	GraphInsertNode(g, 'B');
	GraphInsertNode(g, 'C');
	GraphInsertNode(g, 'D');
	GraphInsertNode(g, 'E');

	Edge e = { 'A', 'B', 1 };
	GraphInsertEdge(g, e);

	e.start = 'A';
	e.end = 'C';
	e.weight = 1;
	GraphInsertEdge(g, e);

	e.start = 'A';
	e.end = 'D';
	e.weight = 1;
	GraphInsertEdge(g, e);

	e.start = 'A';
	e.end = 'E';
	e.weight = 1;
	GraphInsertEdge(g, e);

	e.start = 'B';
	e.end = 'C';
	e.weight = 1;
	GraphInsertEdge(g, e);

	e.start = 'C';
	e.end = 'D';
	e.weight = 1;
	GraphInsertEdge(g, e);

	e.start = 'D';
	e.end = 'E';
	e.weight = 1;
	GraphInsertEdge(g, e);
	GraphShow(g);
	GraphDestroy(g);

	return 0;
}