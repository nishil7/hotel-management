#include <conio.h>
#include <bits/stdc++.h>


using namespace std;
unordered_map<int, bool> occupied_room;
class TrieNode
{
public:
    char data;
    TrieNode **children;
    bool isWord;
    string name;
    int age;
    long long int phone_number;
    string address;
    int room_no;
    TrieNode(char data)
    {
        this->data = data;
        children = new TrieNode *[26];
        for (int i = 0; i < 26; i++)
        {
            children[i] = NULL;
        }
        isWord = false;
        name = '\0';
        age = 0;
        phone_number = 0;
        address = '\0';
        room_no = 0;
    }
};

void insert(TrieNode *root, string word, string name, int age, long long int phone_number, string address, int room_no)
{
    if (word.length() == 0)
    {
        root->isWord = true;
        root->name = name;
        root->age = age;
        root->phone_number = phone_number;
        root->address = address;
        root->room_no = room_no;
        return;
    }
    int index = word[0] - 'a';
    TrieNode *child;
    if (root->children[index] == NULL)
    {
        child = new TrieNode(word[0]);
        root->children[index] = child;
    }
    else
    {
        child = root->children[index];
    }
    insert(child, word.substr(1), name, age, phone_number, address, room_no);
}

void search(TrieNode *root, string word)
{
    int index = word[0] - 'a';
    if (word.length() == 0)
    {
        if (root->isWord == false)
        {
            cout << "\t\t\tQuery Not Found" << endl;
        }
        else
        {
            cout << "\t\t\tRoom Number: " << root->room_no << endl;
            cout << "\t\t\tName of the guest: " << root->name << endl;
            cout << "\t\t\tAge of the guest: " << root->age << endl;
            cout << "\t\t\tPhone number: " << root->phone_number << endl;
            cout << "\t\t\tAddress: " << root->address << endl;
        }
        return;
    }
    if (root->children[index] == NULL)
    {
        cout << "\t\t\tQuery Not Found" << endl;
        return;
    }
    else
    {
        search(root->children[index], word.substr(1));
    }
}
void removeguest(TrieNode *root, string word)
{
    if (word.length() == 0)
    {
        root->isWord = false;
        cout << "\t\t\tQuery deleted successfully" << endl;
        return;
    }
    TrieNode *child;
    int index = word[0] - 'a';
    if (root->children[index] != NULL)
    {
        child = root->children[index];
    }
    else
    {
        cout << "\t\t\tQuery Not found" << endl;
        return;
    }
    removeguest(child, word.substr(1));
}
void print(TrieNode* root){
    if(root==NULL){
        return;
    }
    for(int i=0;i<26;i++){
        if(root->children[i]!=NULL){
            if(root->children[i]->isWord==true){
                cout<<"\t\t\t"<<root->children[i]->name<<" Room No.:"<<root->children[i]->room_no<<endl;
            }
            print(root->children[i]);
        }

    }
}
int check_contact(long long int n)
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

TrieNode *makedetails(ifstream &file, TrieNode *&root)
{
    //base case
    if (file.eof() != 0)
    {
        return NULL;
    }

    //rec case
    else
    {
        char c;
        int room_no;
        string name;
        int age;
        long long int phone_number;
        string address;
        file >> room_no;
        pair<int, bool> p(room_no, true);
        occupied_room.insert(p);
        file.get(c);
        getline(file, name);
        file >> age;
        file >> phone_number;
        file.get(c);
        getline(file, address);
        insert(root, name, name, age, phone_number, address, room_no);
        file.get(c);
        char d;
        file.get(d);
        file.get(c);
        if (d == 'T')
        {
            root = makedetails(file, root);
        }
        return root;
    }
}

void writedetails(TrieNode *root)
{
    if (root == NULL)
    {
        return;
    }
    ofstream file("guestdetails.txt", ios_base::app);
    for (int i = 0; i < 26; i++)
    {
        if (root->children[i] == NULL)
        {
            continue;
        }
        if (root->children[i]->isWord == true)
        {
            file << root->children[i]->room_no << endl;
            file << root->children[i]->name << endl;
            file << root->children[i]->age << endl;
            file << root->children[i]->phone_number << endl;
            file << root->children[i]->address << endl;
            file << endl;
            file << 'T' << endl;
            file.close();
        }
        writedetails(root->children[i]);
    }
}

TrieNode *filein()
{
    TrieNode *root = new TrieNode('\0');
    ifstream file("guestdetails.txt");
    root = makedetails(file, root);
    file.close();
    return root;
}
void fileout(TrieNode *root)
{
    ofstream file("guestdetails.txt", ios_base::trunc);
    file.close();
    writedetails(root);
}

int mainges()
{
    string name;
    int age;
    long long int phone_number;
    string address;
    int room_no;
    TrieNode *root = filein();
    cout << "\n\n\n\n\n";
    cout << "\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n";
    cout << "\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
    cout << "\n\t\t\t        =                  WELCOME                  =";
    cout << "\n\t\t\t        =                    TO                     =";
    cout << "\n\t\t\t        =                  BOOKING                  =";
    cout << "\n\t\t\t        =                 MANAGEMENT                =";
    cout << "\n\t\t\t        =                   SYSTEM                  =";
    cout << "\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
    cout << "\n\n\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n";
    cout << "\n\n\n\t\t\t Enter any key to continue.....";
    getch();
    system("cls");

    cout << "\n\t\t\t----------------------------------------------------------------------------\n";
    while (1)
    {
        int choice;
        cout << "\n\t\t\t    ROOM MENU  \n";
        cout << "\n\t\t\t1.Add Guest detail";
        cout << "\n\t\t\t2.Search Guest details";
        cout << "\n\t\t\t3.Delete Guest details";
        cout<<  "\n\t\t\t4.Print names in alphabetical order";
        cout << "\n\t\t\t5.Exit";
        cout<<"\n\n\t\t\tEnter your choice : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "\t\t\tEnter the room: ";
            cin >> room_no;
            if (occupied_room.count(room_no) == 0)
            {
                pair<int, bool> p(room_no, true);
                occupied_room.insert(p);
            }
            else if (occupied_room[room_no] == true)
            {
                cout << "\t\t\tRoom occupied" << endl;
                break;
            }
            else if (occupied_room[room_no] == false)
            {
                occupied_room[room_no] = true;
            }
            cout << "\t\t\tEnter the name: ";
            fflush(stdin);
            getline(cin, name);
            cout << "\t\t\tEnter the age: ";
            cin >> age;
            do{
            cout << "\t\t\tEnter the phone number: ";
            cin >> phone_number;
            if(check_contact(phone_number)){
            break;
            }
            else{
            cout << "\t\t\t Contact Number should be 10-digit number.\n";
            }
            }while(1);
            cout << "\t\t\tEnter the address: ";
            fflush(stdin);
            getline(cin, address);
            insert(root, name, name, age, phone_number, address, room_no);
            break;
        case 2:
            cout << "\t\t\tEnter room number: ";
            cin >> room_no;
            if (occupied_room.count(room_no) == 0 || occupied_room[room_no] == false)
            {
                cout << "\t\t\tRoom Already Unoccupied" << endl;
                break;
            }
            cout << "\t\t\tEnter the name of the guest: ";
            fflush(stdin);
            getline(cin, name);
            search(root, name);
            break;
        case 3:
            cout << "\t\t\tEnter room number: ";
            cin >> room_no;
            if (occupied_room.count(room_no) == 0 || occupied_room[room_no] == false)
            {
                cout << "\t\t\tRoom Already Unoccupied!" << endl;
                break;
            }
            cout << "\t\t\tEnter the name of the guest: ";
            fflush(stdin);
            getline(cin, name);
            removeguest(root, name);
            occupied_room[room_no]=false;
            break;
        case 4:
        print(root);
        break;
        case 5:
            fileout(root);
            return 0;
            break;
        default:
            cout << "\t\t\tInvalid Choice" << endl;
        }
    }
}