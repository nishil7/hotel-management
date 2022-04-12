#include <bits/stdc++.h>
#include <conio.h>
using namespace std;

class address
{
public:
    string city;
    long long int contact;
};

class Employee
{
    string name;
    string id;
    address add;
    string department;
    Employee *left;
    Employee *right;

public:
    friend void printList(Employee *temp);
    friend void findEmp(Employee *root);
    friend Employee *addEmp(Employee *root);
    friend void insert(Employee *root, Employee *New);
    friend Employee *search(Employee *root, string id_key);
    friend Employee *deleteNode(Employee *root, string key);
    friend int checkID(string id);
    friend int checkContact(long long int n);
    friend void writeTree(Employee *root);
    friend Employee *makeTree(ifstream &file);
};

int checkID(string id)
{
    if (id.size() != 8) 
    {
        cout << "\n\t\t\t Not enough characters entered!";
        return 0;
    }
    return 1;
}

int checkContact(long long int n)
{
    int digit = 0;     
    while (n != 0) 
    {
        n /= 10; 
        digit++;     
    }
    if (digit == 10) 
        return 1;
    else 
        return 0;
}

Employee *addEmp(Employee *root)
{
    Employee *p, *temp;
    p = new Employee();
    cout << "\n\t\t\t Enter the name of Employee : ";
    fflush(stdin);
    getline(cin, p->name);

    while (1)
    {
        cout << "\t\t\t Enter the id of Employee : ";
        cin >> p->id;
        int k = checkID(p->id);
        if (k == 0)
        {
            cout << "\t\t\t Please enter valid ID!\n";
        }
        else
        {
            temp = search(root, p->id);
            if (temp == NULL)
                break;
            else
            {
                cout << "\t\t\t The user with above id already exists.\n";
            }
        }
    }
    cout << "\t\t\t Enter the address of Employee :\n";
    cout << "\t\t\t City :";
    cin >> p->add.city;

    do
    {
        cout << "\t\t\t Enter the Contact Number :";
        fflush(stdin);
        cin >> p->add.contact;
        if (checkContact(p->add.contact))
            break;
        else
            cout << "\t\t\t Contact Number should be 10-digit number.\n";
    } while (1);
    cout << "\t\t\t Enter the Department :";
    fflush(stdin);
    getline(cin, p->department);
    fflush(stdin);

    p->left = NULL;
    p->right = NULL;
    return p;
}

void insert(Employee *root, Employee *New)
{
    int difference = root->id.compare(New->id);
    if (difference > 0)
    {
        if (root->left == NULL)
            root->left = New;
        else
            insert(root->left, New);
    }
    else if (difference < 0)
    {
        if (root->right == NULL)
            root->right = New;
        else
            insert(root->right, New);
    }
}

Employee *search(Employee *root, string id_key)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (root->id == id_key)
    {
        return root;
    }
    else if (root->id < id_key)
    {
        return search(root->right, id_key);
    }
    else
    {
        return search(root->left, id_key);
    }
}

Employee *deleteNode(Employee *root, string key)
{
    //base case
    if (root == NULL)
    {
        return NULL;
    }

    //rec case
    if (root->id == key)
    {
        if (root->left == NULL && root->right == NULL)
        {
            return NULL;
        }
        else if (root->left != NULL && root->right != NULL)
        {
            auto temp = root->left;
            while (temp->right)
                temp = temp->right;
            swap(temp->name, root->name);
            swap(temp->id, root->id);
            swap(temp->add, root->add);
            swap(temp->department, root->department);
            root->left = deleteNode(root->left, key);
        }
        else
        {
            return (root->right != NULL ? root->right : root->left);
        }
    }
    else if (root->id > key)
    {
        root->left = deleteNode(root->left, key);
    }
    else
    {
        root->right = deleteNode(root->right, key);
    }

    return root;
}

void findEmp(Employee *root)
{
    Employee *temp;
    string id_key;
    cout<<"\n\t\t\t Enter the id of the Employee : "; 
    fflush(stdin);
    cin >> id_key;                            
    int k = checkID(id_key);                  
    if (k == 0)                               
        cout << "\n\t\t\t Please enter valid ID!"; 
    else                                      
    {
        temp = search(root, id_key); 
        if (temp == NULL)            
        {
            cout << "\n\t\t\t Employee doesn't exist in the system!";
        }
        else 
        {
            cout << "\n\t\t\t        Employee details"; 
            cout << "\n\t\t------------------------------------------\n";
            cout << "\n\t\t\t  Name          : " << temp->name;
            cout << "\n\t\t\t  ID            : " << temp->id;
            cout << "\n\t\t\t  City          : " << temp->add.city;
            cout << "\n\t\t\t  Contact       : " << temp->add.contact;
            cout << "\n\t\t\t  Department    : " << temp->department;
        }
    }
}

void printList(Employee *temp)
{
    if (temp != NULL)
    {
     printList(temp->left);
        cout << "\n\t\t------------------------------------------\n";
        cout << "\n\t\t\t  Name          : " << temp->name;
        cout << "\n\t\t\t  ID            : " << temp->id;
        cout << "\n\t\t\t  City          : " << temp->add.city;
        cout << "\n\t\t\t  Contact       : " << temp->add.contact;
        cout << "\n\t\t\t  Department    : " << temp->department;
     printList(temp->right);
    }
}

void fileOut(Employee *root)
{
    ofstream file("empdets.txt", ios_base::trunc);
    file.close();
    writeTree(root);
}

void writeTree(Employee *root)
{
    if (root == NULL)
    {
        return;
    }

    //Preorder Traversal
    ofstream file("empdets.txt", ios_base::app);
    file << root->name << "\n";
    file << root->id << "\n";
    file << root->add.city << "\n";
    file << root->add.contact << "\n";
    file << root->department << "\n";
    if (root->left)
    {
        file.put('1');
    }
    else
    {
        file.put('0');
    }
    if (root->right)
    {
        file.put('1');
    }
    else
    {
        file.put('0');
    }
    file << '\n';
    file.close();
    writeTree(root->left);
    writeTree(root->right);
}

Employee *makeTree(ifstream &file)
{
    //base case
    if (file.eof() != 0)
    {
        return NULL;
    }

    //rec case
    else
    {
        Employee *root = new Employee();
        getline(file, root->name);
        getline(file, root->id);
        getline(file, root->add.city);
        file>>root->add.contact;
        char c;
        file.get(c);
        getline(file, root->department);
        char l;
        l = file.get();
        char r;
        r = file.get();
        file.get(c);
        if (l == '1')
        {
            root->left = makeTree(file);
        }
        else
        {
            root->left = NULL;
        }
        if (r == '1')
        {
            root->right = makeTree(file);
        }
        else
        {
            root->right = NULL;
        }
        return root;
    }
}

Employee *fileIn()
{
    Employee *root = NULL;
    ifstream file("empdets.txt");
    root = makeTree(file);
    file.close();
    return root;
}
int mainemp()
{
    cout<<"\n\n\n\n\n";
    cout<<"\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n";
    cout<<"\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
    cout<<"\n\t\t\t        =                  WELCOME                  =";
    cout<<"\n\t\t\t        =                    TO                     =";
    cout<<"\n\t\t\t        =                  EMPLOYEE                 =";
    cout<<"\n\t\t\t        =                 MANAGEMENT                =";
    cout<<"\n\t\t\t        =                   SYSTEM                  =";
    cout<<"\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
    cout<<"\n\n\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n";
    cout<<"\n\n\n\t\t\t Enter any key to continue.....";
    getch();
    system("cls");

    cout<<"\n\t\t\t----------------------------------------------------------------------------";

    Employee *root, *New, *parent, *temp;
    root = NULL;
    root = fileIn();
    string id_key;

    while (1)
    {
        int n;
        cout<<"\n\t\t\t     EMPLOYEE MENU  \n";
        cout<<"\n\t\t\t 1 : Add an Employee";
        cout<<"\n\t\t\t 2 : Delete an Employee";
        cout<<"\n\t\t\t 3 : Display the Existing list";
        cout<<"\n\t\t\t 4 : View Employee detail";
        cout<<"\n\t\t\t 0 : exit the program";
        cout<<"\n\n\t\t\t   Enter your choice : ";

        cin >> n;

        switch (n)
        {

        case 1:
            if (root == NULL)
                root = addEmp(root);
            else
            {
                New = addEmp(root);
                insert(root, New);
            }
            cout<<"\n\t\t\t Employee successfully added in the System!";
            break;

        case 2:
            if (root == NULL)
            {
                cout << "\n\t\t\t Employee Doesn't Exist in the System! ";
            }
            else
            {
                cout << "\n\t\t\t Enter the id of Employee you wish to delete : ";
                fflush(stdin);
                cin >> id_key;
                int k = checkID(id_key);
                if (k == 0)
                    cout << "\n\t\t\t Please enter valid ID";
                else
                {
                    root = deleteNode(root, id_key);
                    cout << "\n\t\t\t Deletion Successful!";
                }
            }
            break;

        case 3:
            if (root == NULL)
                cout << "\n\t\t\t Employee Doesn't Exist in the System! ";
            else
            {
                cout << "\n\t\t\t Employee details are as follows :";
                cout << "\n\t*******************************************************";
             printList(root);
            }
            break;

        case 4:
            if (root == NULL)
            {
                cout << "\n\t\t\t No Record created yet!";
                break;
            }
            else
            {
                findEmp(root);
            }
            break;

        case 0:
            fileOut(root);
            return 0;
            break;
        default:
            fflush(stdin);
        }

        cout<<"\n-----------------------------------------------------------------------\n";
    }

    return 0;
}