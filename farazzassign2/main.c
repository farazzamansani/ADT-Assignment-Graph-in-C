/*
Farazz
386070
*/
#include<stdio.h>
#include "graph.h"


main()
{
	int **dist; // VxV ints to   store shortest path distance
	int **next; // VxV ints to store shortest path data
	int *cent;  // V ints to store the centrality score for each verte


	Graph G;
	
	G.edges = (EdgeList *)malloc(sizeof(EdgeList *));
	int input = 0;
	FILE *filePtr;
	filePtr = fopen("input.txt", "r");
	fscanf(filePtr, "%d", &input);
	G.V = input;
	//printf("number of vertices/people %d \n", G.V);


	//malloc for arrays using G.V Graph vertices as size
	//dist = (int **)malloc(G.V * sizeof(int *));
	dist = malloc(G.V * sizeof *dist);
	
	for (int i = 0; i < G.V; i++)
	{
		dist[i] = malloc(G.V * sizeof *dist[i]);
	}
	
	for (int i = 0; i < G.V; i++)
	{
		for (int j = 0; j < G.V; j++)
		{
			dist[i][j] = 999;
		}
		
	}
	next = (int **)malloc(G.V * sizeof(int *));
	for (int i = 0; i < G.V; ++i)
	{
		next[i] = (int *)malloc(G.V * sizeof(int));
	}
	for (int i = 0; i < G.V; i++)
	{
		for (int j = 0; j < G.V; j++)
		{
			next[i][j] = 999;
		}
	}
	cent = (int *)malloc(G.V * sizeof(int));
	for (int j = 0; j < G.V; j++)
	{
		cent[j] = 0;
	}

	G.edges = (int *)malloc(G.V * sizeof(int));

	int x = 0;
	

	while (x < G.V)
	{
		int k = 0;
		int go = 0;

		fscanf(filePtr, "%d", &go);
		//printf("individual %d has %d contacts/edges\n",x, go);
		EdgeList listy;
		listy.head = NULL;


		while (k<go)
		{
			Edge edgey;
			int input;
			fscanf(filePtr, "%d", &input);
			edgey.to_vertex = input;
			dist[x][input] = 1;
			edgey.weight = 1;//seting weight to 1 always
			insert_at_front(&listy, edgey);
			k++;
		}
		G.edges[x] = listy;
		x++;
	}
	for (int i = 0; i < G.V; i++)
	{
		dist[i][i] = 0;//making distance from a node to itself 0
	}


	FloydShortestPath(dist,next, G.V, G);
	
	calccent(next, cent, G.V);

	//free all the memory
	for (int i = 0; i < G.V; i++)
	{
		free(dist[i]);
	}
	free(**dist);
	for (int i = 0; i < G.V; i++)
	{
		free(next[i]);
	}
	free(**next);
	
	free(*cent);
	
	free(G);


}


insert_at_front(EdgeList *self, Edge b) {
	EdgeNodePtr new_node = malloc(sizeof *new_node);
	new_node->edge = b;
	new_node->next = self->head;
	self->head = new_node;
}


FloydShortestPath(int **dist, int **next,int n, Graph g)
{

	for (int u = 0; u < g.V; u++)
	{
		EdgeNodePtr current = g.edges[u].head;
		
		while (current!=NULL)
		{
			dist[u][current->edge.to_vertex]=current->edge.weight;
			next[u][current->edge.to_vertex]=current->edge.to_vertex;
			current = current->next;
			
		}
		

	}
	for (int k = 0; k<n; k++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if ((dist[k][i] > dist[k][j] + dist[j][i]))
				{
					dist[k][i] = dist[k][j] + dist[j][i];
					next[k][i] = next[k][j];
				}
			}
		}

	}


}

int path(int **next, int u, int v, int topass)
{

	if (u == topass)
		return 0;
	if (u == v)
		return 0;

	while (u != v)
	{
		if (u == topass)
			return 1;
		u = next[u][v];
		
	}

	return 0;
}

calccent(int **next,int *cent,int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			
		for (int p = 0; p < n; p++)
		{
			cent[p] = cent[p] + path(next, i, j, p);
		}
		}
	}
	for (int p = 0; p < n; p++)
	{
		cent[p] = cent[p] / 2;
	}
	int max = 0;
	int position = 0;
	for (int i = 0; i < n; i++)
	{
		if (cent[i] > max)
		{
			max = cent[i];
			position = i;
		}
	}
	printf("Vertice %d : Score %d \n", position, max);
}





void print_list(EdgeList *self) {
	EdgeNodePtr current = self->head;
	int count = 0;

	while (current != NULL) {
		printf("is connected with %d \n", current->edge.to_vertex);
		count = count + current->edge.to_vertex;
		current = current->next;
	}
	printf("count is %d \n", count);
}




