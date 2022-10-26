#include <iostream>

using namespace std;

struct Node
{
	int vertex;
	struct Node *next;
};

class List
{
private:
	struct Node* _head;
public:
	List(){
		_head = NULL;
	}
	void insert (int v)
	{
		struct Node *add = (Node*)malloc(sizeof(struct Node));
		add->vertex = v;
		add->next = _head;
		_head = add;
	}

	struct Node* getList()
	{
		return _head;
	}
};

class Graph
{
private:
	List* list;
	int size;

public:
	Graph(int n){
		list = new List[n];
		size = n;
	}

	void addEdge (int u, int v, int direct)
	{
		list[u].insert(v);
		if (direct)
			list[v].insert(u);
	}

	void addEdge (int u, int v)
	{
		list[u].insert(v);
		list[v].insert(u);
	}

	int getSize()
	{
		return size;
	}

	struct Node* getList (int pos)
	{
		return list[pos].getList();
	}
};

class DFS_Visit
{
private:
	Graph* graph;
	int* mark;
	int* discover;
	int* finish;
	int* parent;
	int time;
public:
	DFS_Visit(Graph* newG)
	{
		graph = newG;
		mark = new int[graph->getSize()];
		discover = new int[graph->getSize()];
		finish = new int[graph->getSize()];
		parent = new int[graph->getSize()];

		for (int i = 0; i < graph->getSize(); ++i)
		{
			mark[i] = discover[i] = finish[i] = 0;
			parent[i] = -1;
		}
		time = 0;
	}

	void VisitR (int u)
	{
		time++;
		mark[u]++;				// color = grey
		discover[u] = time;

		for (Node* v = graph->getList(u); v != NULL; v = v->next)
		{
			if (mark[v->vertex] == 0) 		// white
			{
				parent[v->vertex] = u;
				VisitR(v->vertex);
			}
		}

		time++;
		mark[u]++;				// color = black
		finish[u] = time;
	}

	void Visit()
	{
		for (int u = 1; u < graph->getSize(); ++u)
		{
			if (mark[u] == 0)
				VisitR(u);
		}
	}

	void Print()
	{
		cout << "vertex\tdiscover\tfinish\tparent\n";
		for (int i = 1; i < graph->getSize(); ++i)
		{
			printf("%d\t%d\t\t%d\t%d\n", i, discover[i], finish[i], parent[i]);
		}
	}
};

int main()
{
	Graph g(5);

	g.addEdge(1, 4);
	g.addEdge(2, 4);
	g.addEdge(1, 2);
	g.addEdge(2, 3);
	g.addEdge(3, 4);

	for (int u = 1; u <= 4; ++u)
	{
		cout << u << "->";
		for (Node* v = g.getList(u); v != NULL; v = v->next)
		{
			cout << v->vertex << "->";
		}
		cout << endl;
	}
	DFS_Visit test(&g);

	test.Visit();

	test.Print();
	return 0;
}