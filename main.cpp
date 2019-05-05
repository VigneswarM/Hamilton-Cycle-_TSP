/*
 * COMP 6651 PA#1: Vigneswar Mourouguessin 40057918
 *
 */

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;
int min_cost = 100000;

//Storing values to vector pair
void getInput(int ver, int edge, fstream& input, vector<pair<int, int> > adj[])
{
    int start = 0;
    int end = 0;
    int weight = 0;

    for (int i = 0; i < edge; i++) {
        input >> start;
        input >> end;
        input >> weight;

        adj[start].push_back(make_pair(end, weight));
        adj[end].push_back(make_pair(start, weight));
    }
}

//Finding cost from source to destination
int findval(int src, int des, vector<pair<int, int> > adj[])
{
    int val = 0;

    for (vector<pair<int, int> >::const_iterator iter = adj[src].begin();
         iter != adj[src].end();
         ++iter) {
        if (des == iter->first) {
            val = iter->second;
            break;
        }
    }

    return val;
}

//finding cost of given hamilton path
int find_cost(int arr[], int vertices, vector<pair<int, int> > adj[])
{
    int index = 0;
    int sum = 0;
    int cost = 0;
    int start, end = 0;

    for (int index = 0; index < vertices - 1; index++) {

        start = arr[0];
        end = arr[vertices - 1];

        if (sum == 0) {
            sum = findval(start, end, adj);
        }

        sum = sum + findval(arr[index], arr[index + 1], adj);

        cost = sum;
    }

    return cost;
}


void rotate(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Finding all hamiltionian path
int find_cycles(int* arr, int start, int end, vector<pair<int, int> > adj[])
{

    int cost = 0;

    if (start == end) {
        cost = find_cost(arr, end + 1, adj);
        if (cost < ::min_cost) {
            ::min_cost = cost;
        }
    }

    int i;
    for (i = start; i <= end; i++) {
        rotate((arr + i), (arr + start));
        find_cycles(arr, start + 1, end, adj);
        rotate((arr + i), (arr + start));
    }

    return ::min_cost;
}

int main(int argc, char* argv[])
{

    if (argc != 3) {
        cout << "Error: Incorrect number of arguments!!!" << endl;
        return -1;
    }

    fstream input(argv[1]);
    ofstream output(argv[2]);

    /* fstream input("input.txt");
    ofstream output("output.txt");*/

    if (!input) {
        cout << "Error: Cannot open input file!!!" << endl;
        return -1;
    }

    if (!output) {
        cout << "Error: Cannot open output file (Permission issue?) !!!" << endl;
        return -1;
    }

    int no_of_Sets;
    input >> no_of_Sets;

    for (int i = 0; i < no_of_Sets; ++i) {
        ::min_cost = 100000;

        int vertices;
        input >> vertices;

        int edges;
        input >> edges;

        vector<pair<int, int> > adj[vertices];
        getInput(vertices, edges, input, adj);

        int permute_arr[vertices];
        int cost_min = 0;

        for (int index = 0; index < vertices; index++) {
            permute_arr[index] = index;
        }

        cost_min = find_cycles(permute_arr, 0, vertices - 1, adj);
        output << cost_min << "\n";
    }

    input.close();
    output.close();
}
