#include <iostream>
#define size 4
#define max 1000
using namespace std;

// Stores info about the weight of edges in graph and between which two vertices is the edge present
class weight_info
{
    int weight;
    int u, v;

public:
    weight_info()
    {
        weight = 0;
        u = -1;
        v = -1;
    }

    void put(int w, int u1, int v1)
    {
        weight = w;
        u = u1;
        v = v1;
    }

    friend void insertionSort(weight_info arr[], int n);
    friend class Graph;
};

void insertionSort(weight_info arr[], int n)
{
    int i, j;
    weight_info key;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j].weight > key.weight)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = key;
    }
}

// Stores the info of each vertex as to which other vertices it is connected
class Node_info
{
    int connected[size];
    int visited_by[size];

public:
    Node_info()
    {
        for (int i = 0; i < size; i++)
        {
            connected[i] = -1;
            visited_by[i] = 0;
        }
    }

    void connect(int u)
    {
        connected[u] = 1;
    }

    friend class Graph;
};

// Graph using Adjacency Matrix
class Graph
{
    int adj_mat[size][size];
    int edge_no;

public:
    Graph()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                adj_mat[i][j] = 0;
            }
        }

        edge_no = 0;
    }

    void insert()
    {
        cout << "Insert adjacency matrix values for graph : " << endl;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j <= i; j++)
            {
                cout << "Enter weights for vertex " << i << " to vertex " << j << " : ";
                cin >> adj_mat[i][j];
                adj_mat[j][i] = adj_mat[i][j];
                if (adj_mat[i][j] > 0)
                {
                    edge_no += 1;
                }
            }
            cout << endl;
        }

        cout << "The adjacency matrix is : " << endl;
        print(adj_mat);
    }

    void print(int arr[size][size])
    {
        cout << "_|";
        for (int i = 0; i < size; i++)
        {
            cout << i << "  ";
        }

        cout << endl;

        for (int i = 0; i < size; i++)
        {
            cout << i << "  |";
            for (int j = 0; j < size; j++)
            {
                cout << arr[i][j] << "  ";
            }
            cout << endl;
        }
    }

    void prims()
    {
        int weight[size], from[size];
        int visited[size];
        int spanning_tree[size][size];
        int min_cost = 0;

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                spanning_tree[i][j] = 0;
            }
        }

        for (int i = 0; i < size; i++)
        {
            visited[i] = 0;
            if (adj_mat[0][i] == 0)
            {
                weight[i] = max;
            }
            else
            {
                weight[i] = adj_mat[0][i];
            }

            from[i] = 0;
        }

        visited[0] = 1;
        cout << "Visited vertex : " << 0 << endl;

        int cost = 0;
        int edges = size - 1;
        int min_vertex_distance = max;
        int v, u;

        while (edges > 0)
        {
            min_vertex_distance = max;

            for (int i = 1; i < size; i++)
            {
                if (visited[i] == 0 && min_vertex_distance > weight[i])
                {
                    v = i;
                    min_vertex_distance = weight[i];
                }
            }

            u = from[v];
            spanning_tree[u][v] = weight[v];
            spanning_tree[v][u] = weight[v];
            min_cost += weight[v];

            edges = edges - 1;
            visited[v] = 1;
            cout << "Visited vertex : " << v << endl;

            for (int i = 1; i < size; i++)
            {
                if (visited[i] == 0 && adj_mat[i][v] != 0 && weight[i] > adj_mat[i][v])
                {
                    weight[i] = adj_mat[i][v];
                    from[i] = v;
                }
            }
        }

        cout << "\nThe Spanning tree matrix is : \n"
             << endl;

        print(spanning_tree);

        cout << "\nThe min cost is : " << min_cost << endl;
    }

    void kruskals()
    {
        Node_info N[size];
        weight_info W[edge_no];
        int kruskals_tree[size][size];
        int edges = size - 1;
        int min_cost = 0;

        int x = 0;

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                kruskals_tree[i][j] = 0;
            }
        }

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j <= i; j++)
            {
                if (adj_mat[i][j] != 0)
                {
                    W[x].put(adj_mat[i][j], i, j);
                    N[i].connect(j);
                    N[j].connect(i);
                    x++;
                }
            }
        }

        insertionSort(W, edge_no);

        int i = 0;
        int u, v;
        bool check;
        while (edges > 0)
        {
            u = W[i].u;
            v = W[i].v;
            check = false;
            for (int i = 0; i < size; i++)
            {
                if (N[u].connected[i] == 1 && N[v].connected[i] == 1 && (N[i].visited_by[u] == 1 && N[i].visited_by[v] == 1))
                {
                    check = true;
                    break;
                }
            }

            if (check == false)
            {
                kruskals_tree[u][v] = W[i].weight;
                kruskals_tree[v][u] = W[i].weight;
                N[u].visited_by[v] = 1;
                N[v].visited_by[u] = 1;
                edges = edges - 1;
                min_cost += W[i].weight;
            }

            i++;
        }

        cout << "\nThe Kruskals Spanning tree matrix is : \n"
             << endl;

        print(kruskals_tree);

        cout << "\nThe min cost is : " << min_cost << endl;
    }
};

int main()
{
    Graph g1;
    g1.insert();
    cout << endl;

    cout << endl;
    g1.prims();

    cout << endl;
    g1.kruskals();

    return 0;
}