#include <bits/stdc++.h>
#include <unordered_map>
#include <conio.h>
using namespace std;

class Node
{
public:
    string name;
    int colour;
    bool final;
    friend Node *makeNode(string Name);
};
Node *makeNode(string Name)
{
    Node *ptr = new Node();
    ptr->name = Name;
    ptr->colour = 0;
    ptr->final = false;
    return ptr;
}

bool nbrs(list<Node *> l, Node *x)
{
    bool flag = false;
    for (auto it : l)
    {
        if (it->colour == x->colour)
        {
            flag = true;
        }
    }
    return flag;
}

int colorGraph(unordered_map<Node *, list<Node *>> &m, vector<pair<Node *, list<Node *>>> &s)
{
    int c = 1;
    for (auto it : s)
    {
        if (it.first->colour != 0) //Node is already coloured
        {
            if (!nbrs(it.second, it.first)) //There is no class with neighbours
            {
                it.first->final = true;
                continue;
            }
            //There is class with nbrs
        }
        //It is uncoloured

        it.first->colour = c;
        for (auto x : m)
        {
            if (x.first->final == false)
            {
                if (find(it.second.begin(), it.second.end(), x.first) == it.second.end()) //Non neighbour
                {
                    if (x.first->colour == 0) //Non Coloured
                    {
                        x.first->colour = c;
                    }
                    else //Coloured
                    {
                        if (nbrs(x.second, x.first)) //If clash then recolour it
                        {
                            x.first->colour = c;
                        }
                        //If no clash with nbr, then let it be as it is.
                    }
                }
            }
        }
        it.first->final = true;
        c++;
    }
    return c - 1;
}
//Test
void print1(unordered_map<Node *, list<Node *>> &m)
{
    for (auto y : m)
    {
        cout<<"\t\t\t";
        cout << y.first->name << " -> ";
        for (auto z : y.second)
        {
            cout << z->name << " ";
        }
        cout << endl;
    }
}

void print(unordered_map<Node *, list<Node *>> &m, int c)
{
    vector<string> slot[c];
    for (int i = 1; i <= c; i++)
    {
        for (auto y : m)
        {
            if (y.first->colour == i)
            {
                slot[i - 1].push_back(y.first->name);
            }
        }
    }
    for (int i = 1; i <= c; i++)
    {
        cout<<"\t\t\t";
        cout << "Slot " << i << ":" << endl;
        cout<<"\t\t\t";
        for (int j = 0; j < slot[i - 1].size(); j++)
        {
            cout << slot[i - 1][j] << " ";
        }
        cout << endl;
    }
}

void addEdge(unordered_map<Node *, list<Node *>> &m, Node *x, Node *y)
{
    m[x].push_back(y);
    m[y].push_back(x);
}

bool cmp(pair<Node *, list<Node *>> &a, pair<Node *, list<Node *>> &b)
{
    if (a.second.size() >= b.second.size())
    {
        return true;
    }
    return false;
}

void sorting(vector<pair<Node *, list<Node *>>> &sorting, unordered_map<Node *, list<Node *>> &m)
{
    for (auto x : m)
    {
        sorting.push_back(x);
    }

    sort(sorting.begin(), sorting.end(), cmp);
}

int mainsch()
{
    unordered_map<Node *, list<Node *>> m;
    unordered_map<string, Node *> vertices;
    cout<<"\n\n\n\n\n";
    cout<<"\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n";
    cout<<"\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
    cout<<"\n\t\t\t        =                  WELCOME                  =";
    cout<<"\n\t\t\t        =                    TO                     =";
    cout<<"\n\t\t\t        =                 SCHEDULER                 =";
    cout<<"\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
    cout<<"\n\n\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n";
    cout<<"\n\n\n\t\t\t Enter any key to continue.....";
    getch();
    system("cls");

    printf("\n\t\t\t----------------------------------------------------------------------------\n");
    cout << "\t\t\tEnter the Number of Activities: ";
    int n;
    cin >> n;
    cout << "\t\t\tEnter the Name of Activities: " << endl;
    for (int i = 0; i < n; i++)
    {
        cout<<"\t\t\t";
        string temp;
        cin >> temp;
        vertices[temp] = makeNode(temp);
    }

    cout << "\t\t\tEnter Edge Pairs of Activities: " << endl;
    cout<<"\t\t\t";
    string temp1;
    cin >> temp1;
    while (temp1 != "Done")
    {
        cout<<"\t\t\t";
        string temp2;
        cin >> temp2;
        addEdge(m, vertices[temp1], vertices[temp2]);
        cin >> temp1;
    }

    cout<<endl;

    vector<pair<Node *, list<Node *>>> sorted;
    sorting(sorted, m);


    int total = colorGraph(m, sorted);
    cout<<"\t\t\tThe Schedule of the Activities is as follows -> \n";

    print(m, total);
    return 0;
}