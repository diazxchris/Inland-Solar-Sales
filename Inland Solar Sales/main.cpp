//Christopher Diaz
//Solar Sales CIS 7 Project
//Prof Nguyen

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//function declarations/prototypes
void add_edge();
void print_graph();
void trip_permutations();
void efficient_route();
void city_adjacencies();
void matrices_map();

int main()
{
    //variable for user menu choice
    int choice;

    //menu loop
    do {
        string border(33, '*');

        cout << "Welcome to Solar Sales! Please select from the menu: "
            << "\n1) Possible trips from Riverside" // trip permutations / variations of the trip
            << "\n2) Most Efficient Route" // lowest weight / shortest path
            << "\n3) City Adjacencies" // edge adjacencies
            << "\n4) Distances Map" // weighted adjacencies matrix
            << "\n5) Exit Program" << endl;
        cin >> choice;

        if (choice == 1)
        {
            trip_permutations();          //function call for choice 1
        }
        else if (choice == 2)
        {
            cout << "\n";
            efficient_route();            //function call for choice 2
        }
        else if (choice == 3)
        {
            cout << "\n";
            city_adjacencies();           //function call for choice 3 
        }
        else if (choice == 4)
        {
            cout << "\n";
            matrices_map();             //function call for choice 4
        }
        else if (choice < 1 || choice > 5)      //invalid input catcher
        {
            cout << "\n" << border << "\n  Please enter a valid choice  \n" << border << "\n" << endl;
        }
            
    } while (choice != 5);              //exits loop, if user enters 5, program exits
    
    return 0;
}

//this data structure is used to store a vertex
struct Node // choice 4
{
    int val, cost;
    Node* next;
};

struct edge_weights // choice 4
{
    int starting, destination, weight;
};

struct graph_matrix // choice 4 
{
    //this allocates a new node of Adjacency list
    Node* getAdjListNode(int dest, int wgt, Node* head)
    {
        Node* newNode = new Node;
        newNode->val = dest;
        newNode->cost = wgt;
        // points the new node to current head
        newNode->next = head;

        return newNode;
    }

    int N; // number of nodes in the graph

public:
    //an array of pointers to Node to represent adjacency list
    Node** head;

    //Constructor
    graph_matrix(edge_weights edges[], int n, int N) 
    {
        // allocate memory
        head = new Node * [N]();
        this->N = N;

        // add edges to the directed graph
        for (int i = 0; i < N; i++)
            head[i] = nullptr;

        // 
        for (unsigned i = 0; i < n; i++)
        {
            int starting = edges[i].starting;
            int destination = edges[i].destination;
            int weight = edges[i].weight;
            Node* newNode = getAdjListNode(destination, weight, head[starting]);
            head[starting] = newNode;

            newNode = getAdjListNode(starting, weight, head[destination]);
            head[destination] = newNode;
        }
    }
    graph_matrix() 
    {
        for (int i = 0; i < N; i++)
            delete[] head[i];
            delete[] head;
    }
};

void printList(Node* ptr, int i)
{
    while (ptr != nullptr)
    {
        cout << " |" << i << " -> " << ptr->val << ", " << ptr->cost << " Mi.|  ";

        ptr = ptr->next;
    }
    cout << endl;
}

// used to organize the nodes
struct graph
{
    int vertices;
    struct node** adjacencies_list;     //** is used to store a pointer in node*
};

void add_edge(vector<int> adjacency[], int a, int b) // choice 3 used
{
    adjacency[a].push_back(b);
    adjacency[b].push_back(a);
}

void print_graph(vector<int> adjacency[], int Vertex) //choice 3 used
{
    for (int d = 1; d < Vertex; ++d) 
    {
        cout << d;
        for (auto x : adjacency[d])       //auto class is a variable that has a local lifetime
            cout << " <-> " << x;            
        printf("\n");
    }
}

//choice 1
void trip_permutations() //function to display the trip variations starting from the Riverside, the salesmans departure point
{
    string border(25, '*');
    cout << "\n" << border << "\n  Trip Variations from\n   company terminal\n" << border << "\nStarting From Riverside\n" << "\nLegend:" << "\n(1) Riverside" << "\n(2) Moreno Valley"
        << "\n(3) Perris" << "\n(4) Hemet\n" << endl;

    int integers[] = { 1, 2, 3, 4 };
    sort(integers, integers + 4);
    
    int i = 1;
    do {
        cout << "\n" << "(" << integers[0] << ") -> (" << integers[1] << ") -> (" << integers[2] << ") -> (" << integers[3] << ")";
        i++;
    } while (next_permutation(integers, integers + 4),(i < 7));

    cout << "\n\n";
}

//choice 2  
void efficient_route() //Implements discrete structure graph concept of the path with the least weight
{
    string border(25, '*');
    cout << border << "\n  Most Efficient Route\n" << border << "\nLegend:" << "\n(1) Riverside" << "\n(2) Moreno Valley"
        << "\n(3) Perris" << "\n(4) Hemet\n" << endl;

    cout << "(1) 16 mi.-> (2) 18 mi.-> (3) 30 mi.-> (4) 33 mi.-> (1)\n\n" << endl;
}

//choice 3
void city_adjacencies() //Displays adjacencies of each city
{   //to excersice adjacency structure.
    string border(25, '*');
    cout << border << "\n    City Adjacencies\n" << border << "\nLegend:" << "\n(1) Riverside" << "\n(2) Moreno Valley"
        << "\n(3) Perris" << "\n(4) Hemet\n" << endl;
    
    const int V = 5;
    vector<int> adj[V];
                         //city edges
    add_edge(adj, 1, 2);
    add_edge(adj, 1, 3);
    add_edge(adj, 1, 4);
    add_edge(adj, 2, 3);
    add_edge(adj, 2, 4);
    add_edge(adj, 3, 4);
    print_graph(adj, V);
    cout << "\n\n";
} 

//choice 4
void matrices_map() //Prints map of the matricies
{
    string border(25, '*');
    cout  << border << "\n    Distances Matrix\n" << border << "\nLegend:" << "\n(1) Riverside" << "\n(2) Moreno Valley"
        << "\n(3) Perris" << "\n(4) Hemet\n" << endl;

    edge_weights edges[] =
    {
        // starting edge, destination, weight (distance) (r, s, t)
        {1, 2, 16}, {1, 3, 24}, {1, 4, 33}, {2, 3, 18}, {2, 4, 26}, {3, 4, 30}
    };

    //Number of vertices
    int N = 5;

    //calculate number of edges
    int n = sizeof(edges) / sizeof(edges[0]);

    //construct graph
    graph_matrix graph(edges, n, N);

    //print adjacency list representation of graph
    for (int i = 1; i < N; i++)
    {        
        printList(graph.head[i], i);
    }

    cout << "\n\n";
} // //choice 4

//code end