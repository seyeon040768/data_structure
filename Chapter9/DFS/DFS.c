#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50

typedef struct
{
	int size;
	int adjMat[MAX_VERTICES][MAX_VERTICES];
} Graph;

Graph* Create()
{
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	if (graph == NULL)
	{
		exit(1);
	}

	graph->size = 0;

	for (int r = 0; r < MAX_VERTICES; ++r)
	{
		for (int c = 0; c < MAX_VERTICES; ++c)
		{
			graph->adjMat[r][c] = 0;
		}
	}

	return graph;
}

int IsEmpty(Graph* graph)
{
	return graph->size == 0;
}

int IsFull(Graph* graph)
{
	return graph->size == MAX_VERTICES;
}

void InsertVertex(Graph* graph)
{
	if (IsFull(graph))
	{
		return;
	}

	++(graph->size);
}

void DeleteVertex(Graph* graph, int vertex)
{
	if ((vertex < 0) || (vertex >= graph->size))
	{
		return;
	}

	for (int r = vertex + 1; r < graph->size; ++r)
	{
		for (int c = 0; c < vertex; ++c)
		{
			graph->adjMat[r - 1][c] = graph->adjMat[r][c];
		}
	}

	for (int c = vertex + 1; c < graph->size; ++c)
	{
		for (int r = 0; r < vertex; ++r)
		{
			graph->adjMat[r][c - 1] = graph->adjMat[r][c];
		}
	}

	for (int r = vertex + 1; r < graph->size; ++r)
	{
		for (int c = vertex + 1; c < graph->size; ++c)
		{
			graph->adjMat[r - 1][c - 1] = graph->adjMat[r][c];
		}
	}

	--(graph->size);
}

void InsertEdge(Graph* graph, int start, int end)
{
	if ((start < 0) || (start >= graph->size) || (end < 0) || (end >= graph->size))
	{
		return;
	}

	graph->adjMat[start][end] = 1;
	graph->adjMat[end][start] = 1;
}

void DeleteEdge(Graph* graph, int start, int end)
{
	if ((start < 0) || (start >= graph->size) || (end < 0) || (end >= graph->size))
	{
		return;
	}

	graph->adjMat[start][end] = 0;
	graph->adjMat[end][start] = 0;
}

void DFS(Graph* graph, int startVertex)
{
	static int visited[MAX_VERTICES] = { 0, };

	visited[startVertex] = 1;
	printf("%d -> ", startVertex);

	for (int i = 0; i < graph->size; ++i)
	{
		if (graph->adjMat[startVertex][i] && !visited[i])
		{
			DFS(graph, i);
		}
	}
}

int main(void)
{
	Graph* graph = Create();
	InsertVertex(graph);
	InsertVertex(graph);
	InsertVertex(graph);
	InsertVertex(graph);

	InsertEdge(graph, 0, 1);
	InsertEdge(graph, 0, 2);
	InsertEdge(graph, 0, 3);
	InsertEdge(graph, 1, 3);

	DFS(graph, 0);

	free(graph);

	return 0;
}