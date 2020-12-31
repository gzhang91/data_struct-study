#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
	本文件主要使用邻接链表来实现图
*/

#define Vectex char

enum graph_type_s {
	DAG, // 有向图
	UDG, // 无向图
};

typedef enum graph_type_s GraphType;

struct link_node_s {
	int idx;
	int weight;
	struct link_node_s *next;
};

typedef struct link_node_s LinkNode;

struct node_s {
	Vectex d;
	LinkNode *link;
};

typedef struct node_s Node;

struct edge_s {
	Vectex start;
	Vectex end;
	int weight;
};

typedef struct edge_s Edge;

struct graph_s {
	GraphType type;
	Node *inode;
	int max_of_nodes; // 节点个数最大值
	int num_of_nodes;  // 节点个数
	int num_of_edges;  // 边的个数
};

typedef struct graph_s Graph; 

// 操作函数
Graph* GraphInit(int is_dag, size_t size);
int GraphInsertNode(Graph *g, Vectex v);
int GraphInsertEdge(Graph *g, Edge e);

void GraphDestroy(Graph *g);

int GraphGetNodeIndex(Graph *g, Vectex v);
Vectex GraphGetNodeByIndex(Graph *g, int index);

void GraphShow(Graph *g);

#endif // !_GRAPH_H_
