#include "graph.h"
#include <stdio.h>
#include <string.h>

Graph* GraphInit(int is_dag, size_t size) {
	Graph *g = (Graph *)malloc(sizeof(*g));
	if (!g) {
		printf("malloc Graph failed!\n");
		return NULL;
	}

	if (size == 0) {
		size = 8;
	}

	g->inode = (Node *)malloc(sizeof(*g->inode) * size);
	if (!g->inode) {
		printf("malloc inode failed!\n");
		return NULL;
	}

	memset(g->inode, 0x0, sizeof(*g->inode) * size);

	g->num_of_edges = 0;
	g->num_of_nodes = 0;
	g->max_of_nodes = size;
	g->type = (is_dag == 1 ? DAG : UDG);

	return g;
}

int GraphGetNodeIndex(Graph *g, Vectex v) {
	if (!g) {
		return -1;
	}

	for (int i = 0; i < g->num_of_nodes; ++i) {
		if (g->inode[i].d == v) {
			return i;
		}
	}

	return -1;
}

Vectex GraphGetNodeByIndex(Graph *g, int index) {
	if (!g) {
		return -1;
	}

	if (g->num_of_nodes - 1 < index) {
		return 'U';
	}

	return g->inode[index].d;
}

int GraphInsertNode(Graph *g, Vectex v) {
	if (!g) {
		return -1;
	}

	if (g->max_of_nodes < g->num_of_nodes) {
		printf("node is full, insert failed!\n");
		return -1;
	}

	g->inode[g->num_of_nodes].d = v;
	g->inode[g->num_of_nodes].link = NULL;
	g->num_of_nodes++;

	return 0;
}

int GraphInsertEdge(Graph *g, Edge e) {
	if (!g) {
		return -1;
	}

	int begin_idx = GraphGetNodeIndex(g, e.start);
	int end_idx = GraphGetNodeIndex(g, e.end);
	if (begin_idx == -1 || end_idx == -1) {
		printf("insert edge failed, invalid edge start[%c]->end[%d]\n", e.start, e.end);
		return -1;
	}

	LinkNode *tmp = (LinkNode *)malloc(sizeof(*tmp));
	if (!tmp) {
		printf("malloc LinkNode failed!\n");
		return -1;
	}

	tmp->idx = end_idx;
	tmp->weight = e.weight;
	tmp->next = NULL;

	LinkNode *first = g->inode[begin_idx].link;
	LinkNode *prev = first;
	while (first != NULL) {
		prev = first;
		first = first->next;
	}

	if (prev == NULL) {
		g->inode[begin_idx].link = tmp;
	} else {
		prev->next = tmp;
	}

	g->num_of_edges ++;

	if (g->type == UDG) { // 无向图
		LinkNode *tmp1 = (LinkNode *)malloc(sizeof(*tmp1));
		if (!tmp1) {
			printf("malloc LinkNode failed!\n");
			return -1;
		}

		tmp1->idx = begin_idx;
		tmp1->weight = e.weight;
		tmp1->next = NULL;

		first = g->inode[end_idx].link;
		prev = first;
		while (first != NULL) {
			prev = first;
			first = first->next;
		}

		if (prev == NULL) {
			g->inode[end_idx].link = tmp1;
		} else {
			prev->next = tmp1;
		}

		g->num_of_edges ++;
	} 

	return 0;
}

void GraphDestroy(Graph *g) {
	for (int i = 0; i < g->num_of_nodes; ++i) {
		LinkNode *first = g->inode[i].link;
		while (first) {
			g->inode[i].link = first->next;
			free(first);
			first = g->inode[i].link;
		}
	}
	
	free(g->inode);
	g->max_of_nodes = 0;
	g->num_of_edges = 0;
	g->num_of_nodes = 0;
}

void GraphShow(Graph *g) {

	for (int i = 0; i < g->num_of_nodes; ++i) {
		printf("%c", g->inode[i].d);
		LinkNode *first = g->inode[i].link;
		while (first) {
			Vectex v = GraphGetNodeByIndex(g, first->idx);
			printf("->%c(%d)", v, first->weight);
			first = first->next;
		}
		printf("->Nil \n");
	}

}