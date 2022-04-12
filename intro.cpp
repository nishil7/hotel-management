#include <bits/stdc++.h>
#include "schedule.cpp"
#include "employee1.cpp"
#include "booking_rooms.cpp"
#include "restaurant.cpp"
#include <fstream>

using namespace std;
int main()
{
    cout<<"\n\n\n\n\n";
    cout<<"\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n";
    cout<<"\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
    cout<<"\n\t\t\t        =                  WELCOME                  =";
    cout<<"\n\t\t\t        =                    TO                     =";
    cout<<"\n\t\t\t        =                   HOTEL                   =";
    cout<<"\n\t\t\t        =                 MANAGEMENT                =";
    cout<<"\n\t\t\t        =                   SYSTEM                  =";
    cout<<"\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
    cout<<"\n\n\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n";
    cout<<"\n\n\n\t\t\t Enter any key to continue.....";
    getch();
    system("cls");

    printf("\n\t\t\t----------------------------------------------------------------------------");

    while (1)
    {
        int n;
        cout<<"\n\t\t\t     MAIN MENU  \n";
        cout<<"\n\t\t\t 1 : Manage Employees";
        cout<<"\n\t\t\t 2 : Manage Bookings";
        cout<<"\n\t\t\t 3 : Manage Activity Schedule";
        cout<<"\n\t\t\t 4 : Manage Restaurant";
        cout<<"\n\t\t\t 0 : Exit the program";
        cout<<"\n\n\t\t\t   Enter your choice : ";

        cin >> n;

        switch (n)
        {

        case 1:
            mainemp();
            break;

        case 2:
            mainges();
            break;

        case 3:
            mainsch();
            break;

        case 4:
            mainres();
            break;

        case 0:
            cout<<"\n\n\n\n\n";
            cout<<"\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n";
            cout<<"\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
            cout<<"\n\t\t\t        =                Thank you                  =";
            cout<<"\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
            cout<<"\n\n\t\t\t**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n";
            exit(0);
            break;
        default:
            cout<<"\n\t\t\t   Wrong Input\n\t\t\t  :( \n\t\t\t  Try again\n\n";
            fflush(stdin);
        }
    }
    cout<<"\n-----------------------------------------------------------------------\n";
return 0;
}