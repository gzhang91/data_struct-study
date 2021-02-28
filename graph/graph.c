#include "graph.h"
#include "queue.h"
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

//---------------------------------------------
// 获取邻接点
LinkNode* GetStartNeiborNode(Graph *g, int index) {
	LinkNode *begin = NULL;
	if (g->inode[index].link) {
		begin = g->inode[index].link;
	}
	return begin;
}

void GetNextNeiborNode(Graph *g, LinkNode *prev, LinkNode **next) {
	*next = NULL;
	if (prev && prev->next) {
		*next = prev->next;
	}
}

void DFS_handler(Graph *g, int index, int *visit) {
	if (!g) {
		return;
	}

	if (visit[index] != 1) {
		printf("%c->", GraphGetNodeByIndex(g, index));
		visit[index] = 1;
	}

	LinkNode *start = GetStartNeiborNode(g, index);
	LinkNode *next = NULL;
	while (start) {
		if (visit[start->idx] != 1) {
			printf("%c->", GraphGetNodeByIndex(g, start->idx));
			visit[start->idx] = 1;
			DFS_handler(g, start->idx, visit);
		}
		
		GetNextNeiborNode(g, start, &next);
		start = next;
	}
}

// 计算连通分量
void CalcConnectedComponent(Graph *g) {
	if (!g) {
		return;
	}

	int *visit = (int *)malloc(g->num_of_nodes * sizeof(int));
	if (visit == NULL) {
		return;
	}
	memset(visit, 0x0, g->num_of_nodes * sizeof(int));

	int count = 0; // 计算连通分量
	for (int i = 0; i < g->num_of_nodes; i++) {
		if (!visit[i]) {
			count++;
			DFS_handler(g, i, visit);
			printf("Nil\n");
		}
	}

	
}

void DFSTravel(Graph *g) {
	if (!g) {
		return;
	}

	int *visit = (int *)malloc(g->num_of_nodes * sizeof(int));
	if (visit == NULL) {
		return;
	}
	memset(visit, 0x0, g->num_of_nodes * sizeof(int));

	for (int i = 0; i < g->num_of_nodes; ++i) {
		if (!visit[i]) {
			DFS_handler(g, i, visit);
			printf("Nil\n");
		}
	}
	
	
}

// 深度优先
void DFS(Graph *g, Vectex start_v) {
	if (!g) {
		return;
	}

	int idx = GraphGetNodeIndex(g, start_v);
	if (idx == -1) {
		return;
	}

	int *visit = (int *)malloc(g->num_of_nodes * sizeof(int));
	if (visit == NULL) {
		return;
	}
	memset(visit, 0x0, g->num_of_nodes * sizeof(int));

	DFS_handler(g, idx, visit);

	printf("Nil\n");
}

void BFS_handler(Graph *g, int index, int *visit) {
	if (!g) {
		return;
	}

	if (visit[index] != 1) {
		printf("%c->", GraphGetNodeByIndex(g, index));
		visit[index] = 1;
	}

	Queue *queue = QueueCreate(sizeof(LinkNode *), g->num_of_nodes);
	LinkNode *node = (LinkNode *)malloc(sizeof(LinkNode *));
	node->idx = index;
	node->next = g->inode[index].link;
	node->weight = 1;
	QueueEn(queue, &node);

	LinkNode *start = NULL;
	LinkNode *next = NULL;
	while (!QueueEmpty(queue)) {
		QueueDe(queue, &start);
	
		start = GetStartNeiborNode(g, start->idx);
		while (start) {
			if (visit[start->idx] != 1) {
				printf("%c->", GraphGetNodeByIndex(g, start->idx));
				QueueEn(queue, &start);
				visit[start->idx] = 1;
			}
			
			GetNextNeiborNode(g, start, &next);
			start = next;
		}
	}

	free(node);
	QueueRelease(queue);
}

// 广度遍历，全图
void BFSTravel(Graph *g) {
	if (!g) {
		return;
	}

	int *visit = (int *)malloc(g->num_of_nodes * sizeof(int));
	if (visit == NULL) {
		return;
	}
	memset(visit, 0x0, g->num_of_nodes * sizeof(int));

	for (int i = 0; i < g->num_of_nodes; ++i) {
		if (!visit[i]) {
			BFS_handler(g, i, visit);
			printf("Nil\n");
		}
	}
	
	
}

// 广度优先
void BFS(Graph *g, Vectex start_v) {
	if (!g) {
		return;
	}

	int idx = GraphGetNodeIndex(g, start_v);
	if (idx == -1) {
		return;
	}

	int *visit = (int *)malloc(g->num_of_nodes * sizeof(int));
	if (visit == NULL) {
		return;
	}
	memset(visit, 0x0, g->num_of_nodes * sizeof(int));

	BFS_handler(g, idx, visit);
	printf("Nil\n");
}