#include<bits/stdc++.h>
using namespace std;

int pending_orders = 0;
unordered_map<int, bool> occupied_tables;

class Restuarant
{
	public:
	int table_no;
	int dish_no;
	string dish_name[5];
	int total_bill;
	Restuarant *next;

	Restuarant()
	{
		for (int i = 0; i<5; i++)
		dish_name[i]=" ";
		table_no = total_bill = 0;
		dish_no = 0;
		next = NULL;
	}

	int getorder()
	{
		cout << "\t\t\tEnter the following details: "<<endl;
		cout << "\t\t\tTable No: ";
		cin >> table_no;
		if (occupied_tables.count(table_no) == 0)
		{
			pair<int, bool> p(table_no, true);
			occupied_tables.insert(p);
		}
		else if (occupied_tables[table_no] == true)
		{
			cout << "\t\t\tTable occupied!" << endl;
			return 0;
		}
		else if (occupied_tables[table_no] == false)
		{
			occupied_tables[table_no] = true;
		}
		cout << "\t\t\tHow many dish you want to order?";
		cin >> dish_no;
		cout << "\t\t\tPlease place the order "<<endl;
		cout << "\t\t\tMENU"<<endl;
		cout << "\t\t\t1.Ice Cream\n\t\t\t2.Soft Drinks\n\t\t\t3.Burgers\n\t\t\t4.Soups\n\t\t\t5.Pasta\n\t\t\t6.Pizzas\n\n";
		for (int i = 0; i < dish_no; i++)
		{
			fflush(stdin);
			cout<<"\t\t\t";
			getline(cin,dish_name[i]);
			if (checkorder(&dish_name[i][0]) == 0)
			{
				cout << "\t\t\tThe dish you have ordered does not exist in the menu. Please Try Again!" << endl;
				i--;
			}
		}
		cout << "\t\t\tAmount to be paid by the Customer: " <<total_bill<<endl;
		return 1;
	}

	void displayorder(){

		cout << "\t\t\tTable No: " << table_no<<endl;
		cout << "\t\t\tNumber of dish ordered: "<<dish_no<<endl;
		cout <<"\t\t\tOrder Placed: "<<endl;
		for (int i=0; i < 5; i++)
		{
			if(dish_name[i]==" "){
				continue;
			}
			cout<<"\t\t\t";
			cout <<dish_name[i]<<endl;
		}
		cout << "\t\t\tAmount to be paid By the Customer: " << total_bill<<endl;
	}

	int checkorder(char *x)
	{
		if (strcmp(x, "Ice Cream") == 0)
			total_bill += 100;
		else if (strcmp(x, "Soft Drinks") == 0)
			total_bill += 150;
		else if (strcmp(x, "Burgers") == 0)
			total_bill += 200;
		else if (strcmp(x, "Soups") == 0)
			total_bill += 250;
		else if (strcmp(x, "Pasta") == 0)
			total_bill += 300;
		else if (strcmp(x, "Pizzas") == 0)
			total_bill += 400;
		else
			return 0;
		return 1;
	}

	int get_table_no()
	{
		return table_no;
	}
	friend void fileOut(Restuarant* front);
	friend void writeorders(Restuarant* front);
	friend Restuarant *makeorder(ifstream &file,Restuarant* &rear);
}; 

void insert_order(Restuarant* &front,Restuarant* &rear)
{
	Restuarant *p = new Restuarant;
	int i = p->getorder();
	if (i == 1)
	{
		pending_orders++;
		if (rear == NULL)
		{
			rear = p;
			front = p;
		}
		else
		{
			rear->next = p;
			rear = p;
		}
	}
	else
	{
		delete p;
		return;
	}
}

void delete_order(Restuarant* &front,Restuarant* &rear)
{
	int tablenu;
	if (rear != NULL)
	{
		cout << "\t\t\tWhich order would you like to remove? Please provide the table number: ";
		cin >> tablenu;
		Restuarant *p = front;
		Restuarant *q = front;
		if (occupied_tables.count(tablenu) == 0 || occupied_tables[tablenu] == false)
		{
			cout << "\t\t\tTable Already Unoccupied!"<<endl;
			return;
		}

		if (front->get_table_no() == tablenu)
		{
			front = front->next;
			p->displayorder();
		}
		else if (rear->get_table_no() == tablenu)
		{
			while (p->next != rear)
			{
				p = p->next;
			}
			p->next = NULL;
			rear->displayorder();
			rear = p;
		}
		else
		{
			while (p->get_table_no()!=tablenu)
			{
				q = p;
				p = p->next;
			}
			p->displayorder();
			cout << endl;
			q->next = p->next;
		}
		occupied_tables[tablenu] = false;
		pending_orders--;
	}
	else
		cout << "\t\t\tNo Orders have been placed yet. Try Again Later!"<<endl;
}

void show_order(Restuarant* &front)
{
	if (pending_orders != 0)
	{
		cout << "\t\t\tHere all the orders that have been placed: "<<endl;
		Restuarant *p = front;
		while (p != NULL)
		{
			p->displayorder();
			cout << endl;
			p = p->next;
		}
	}
	else
	{
		cout << "\t\t\tNo Orders have been placed yet."<<endl;
	}

}
void fileOUT(Restuarant *front)
{
    ofstream file("restuarant.txt", ios_base::trunc);
    file.close();
    writeorders(front);
}
void writeorders(Restuarant *front)
{
    //base case
    if (front == NULL)
    {
        return;
    }

    //rec case
    ofstream file("restuarant.txt", ios_base::app);
    file << front->table_no <<endl;
	file << front->dish_no<<endl;
	for (int i = 0; i <5; i++){
	file <<front->dish_name[i]<<endl;
		}
		file<<"\n";
	file << front->total_bill <<endl;

    file <<endl;
	if(front->next){
		file<<'T'<<endl;
	}
    file.close();
    writeorders(front->next);
}
Restuarant *makeorder(ifstream &file,Restuarant* &rear)
{
    //base case
    if (file.eof() != 0){
        return NULL;
    }

    //rec case
    else
    {
        Restuarant *front = new Restuarant();
        file>>front->table_no;
		if (occupied_tables.count(front->table_no) == 0)
		{
			pair<int, bool> p(front->table_no, true);
			occupied_tables.insert(p);
		}
		else if (occupied_tables[front->table_no] == true)
		{
			cout << "\t\t\tTable occupied!" << endl;
			return 0;
		}
		else if (occupied_tables[front->table_no] == false)
		{
			occupied_tables[front->table_no] = true;
		}
        file>>front->dish_no;
		char c;
		file.get(c);
		for (int i=0;i<5;i++){
		getline(file,front->dish_name[i]);
		}
		file>>front->total_bill;
		file.get(c);
		file.get(c);
		file.get(c);
		pending_orders++;
        if(c=='T'){
			front->next=makeorder(file,rear);
		}
		else{
			rear=front;
		}
        return front;
    }
}
Restuarant *fileIN(Restuarant* &rear)
{
    Restuarant *front = NULL;
    ifstream file("restuarant.txt");
    front = makeorder(file,rear);
    file.close();
    return front;
}
int mainres(){
	Restuarant* front=NULL;
	Restuarant*rear=NULL;
	front=fileIN(rear);
	cout<<"\n";
	int choice;
	cout << "\n\n\n\n\n";
    cout << "\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n";
    cout << "\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
    cout << "\n\t\t\t        =                  WELCOME                  =";
    cout << "\n\t\t\t        =                    TO                     =";
    cout << "\n\t\t\t        =                 RESTAURANT                =";
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
		cout<<"\t\t\t1.Place the order: \n";
		cout<<"\t\t\t2.Delete the order: \n";
		cout<<"\t\t\t3.Display the pending orders: \n";
		cout<<"\t\t\t4.Exit";
		cout<<"\n\n\t\t\tEnter your choice : ";
		cin >> choice;
		switch (choice)
		{
		case 1:
		insert_order(front,rear);
		break;
		case 2:
		delete_order(front,rear);
		break;
		case 3:
		show_order(front);
		break;
		case 4:
		fileOUT(front);
        return 0;
		break;	
		default:
		cout << "\t\t\tInvalid Choice";
		}
		cout << endl;
	}
}