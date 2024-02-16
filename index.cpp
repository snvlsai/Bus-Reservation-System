#include <iostream>
#include <string.h>
#include <cstdlib>
using namespace std;
int p = 0;
int c=0;
class Portal
{
    char busn[5], driver[10], arrival[5], depart[5], from[10], to[10], date[20], seat[8][4][10];

public:
    void install();
    int allotment();
    void empty();
    void show();
    void avail(int a,string b);
    void position(int i);
} bus[10];
void Portal::install()
{
temp:
    cout<<"Enter the Date: ";
    cin>>bus[p].date;
    cout << "\nEnter bus no: ";
    cin >> bus[p].busn;
    int n;
    for (n = 0; n < p; n++)
    {
        if (strcmp(bus[n].busn, bus[p].busn) == 0)
        {
            cout << "Bus Already exists!!" << endl;
            goto temp;
        }
    }
    cout << "\nEnter Driver's name: ";
    cin >> bus[p].driver;
    cout << "\nFrom: \t\t\t";
    cin >> bus[p].from;
    cout << "\nTo: \t\t\t";
    cin >> bus[p].to;
    cout << "\nArrival time: ";
    cin >> bus[p].arrival;
    cout << "\nDeparture: ";
    cin >> bus[p].depart;
    bus[p].empty();
    p++;
}
int Portal::allotment()
{
    if (p == 0)
    {
        cout << "There are no busses available!!" << endl;
        return 0;
    }
    system("clear");
top:
    int seat;
    char number[5],temp[20];
    cout<<"Press 0 to cancel booking!!"<<endl;
    cout<<"Date: ";
    cin>>temp;
    if(strcmp(temp,"0")==0)
     return 0;
    bus[p].avail(1,temp);
    int n;
    for (n = 0; n <= p; n++)
    {
        if (strcmp(bus[n].date, temp) == 0)
            break;
    }
    while (n <= p)
    {
        bus[n].show();
        cout << "\nSeat Number: ";
        cin >> seat;
        if (seat > 32)
            cout << "\nThere are only 32 seats available in this bus.";
        else
        {
            if (strcmp(bus[n].seat[seat / 4][(seat % 4) - 1], "Empty") == 0)
            {
                cout << "Enter passanger's name: ";
                cin >> bus[n].seat[seat / 4][(seat % 4) - 1];
                break;
            }
            else
                cout << "The seat no. is already reserved.\n";
        }
    }
    if (n > p)
    {
        cout << "There are no busses available in this date!!\n\n";
        goto top;
    }
    return 1;
}
void Portal::empty()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
            strcpy(bus[p].seat[i][j], "Empty");
    }
}
void Portal::show()
{
    if (p == 0)
    {
        cout << "There are no busses available!!" << endl;
        return;
    }
    int n;
    char number[5];
    cout << "Enter bus no: ";
    cin >> number;
    for (n = 0; n < p; n++)
    {
        if (strcmp(bus[n].busn, number) == 0)
            break;
    }
    while (n <= p)
    {
        cout << "Bus no: \t" << bus[n].busn
             << "\nDriver: \t" << bus[n].driver << "\t\tArrival time: \t"
             << bus[n].arrival << "\tDeparture time:" << bus[n].depart
             << "\nFrom: \t\t" << bus[n].from << "\t\tTo: \t\t" << bus[n].to << "\n";
        bus[0].position(n);
        int a = 1;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                a++;
                if (strcmp(bus[n].seat[i][j], "Empty") != 0)
                    cout << "The seat no " << (a - 1) << " is reserved for " << bus[n].seat[i][j] << "." << endl;
            }
        }
        break;
    }
    if (n > p)
    {
        cout << "Enter correct bus no: \n\n";
    }
}
void Portal::position(int l)
{
    int s = 0;
    p = 0;
    for (int i = 0; i < 8; i++)
    {
        cout << "\n";
        for (int j = 0; j < 4; j++)
        {
            s++;
            if (strcmp(bus[l].seat[i][j], "Empty") == 0)
            {
                cout.width(5);
                cout.fill(' ');
                cout << s << ".";
                cout.width(10);
                cout.fill(' ');
                cout << bus[l].seat[i][j];
                p++;
            }
            else
            {
                cout.width(5);
                cout.fill(' ');
                cout << s << ".";
                cout.width(10);
                cout.fill(' ');
                cout << bus[l].seat[i][j];
            }
        }
    }
    cout << "\n\nThere are " << p << " seats empty in Bus No: " << bus[l].busn << endl;
}
void Portal::avail(int flag=0,string x=" ")
{
    if (c == 0)
    {
        cout << "There are no busses available!!" << endl;
        return;
    }
    cout<<"\t\t\tAvailable busses!!!"<<endl;
    if(flag==1)
    {
        for (int i = 0; i < c; i++)
        {
            if(bus[i].date==x)
            {
            cout << "Bus no: \t" << bus[i].busn << "\nDriver: \t" << bus[i].driver
                << "\t\tArrival time: \t" << bus[i].arrival << "\tDeparture Time: \t"
                << bus[i].depart << "\nFrom: \t\t" << bus[i].from << "\t\tTo: \t\t\t"
                << bus[i].to << "\n\n";
            }
        }
        
    }
    else{
    for (int i = 0; i < c; i++)
    {
        cout << "Bus no: \t" << bus[i].busn << "\nDriver: \t" << bus[i].driver
             << "\t\tArrival time: \t" << bus[i].arrival << "\tDeparture Time: \t"
             << bus[i].depart << "\nFrom: \t\t" << bus[i].from << "\t\tTo: \t\t\t"
             << bus[i].to << "\n\n";
    }
    }
}
int main(){
    system("clear");
    int ch;
    while (1)
    {
    welcome:
        system("clear");
        cout << "\t\t\t SHS Bus Booking Service\n\n"
             << endl;
        cout << "1-Admin Login" << endl;
        cout << "2-User Login" << endl;
        cout << "3-Exit" << endl;
        cout << "\nEnter Your Choice-";
        cin >> ch;
        switch (ch)
        {
        case 1:
            system("clear");
            while (1)
            {
                cout << "\t\t\t\tAdministration Portal\n\n"
                     << endl;
                cout << "1-Add Bus" << endl;
                cout << "2-Show Seats" << endl;
                cout << "3-Available Buses" << endl;
                cout << "4-Sign Out" << endl;
                cout << "\nEnter Your Choice-";
                int choice;
                cin >> choice;
                switch (choice)
                {
                case 1:
                    system("clear");
                    bus[p].install();
                    system("clear");
                    cout << "Bus Details added Sucessfully!!" << endl;
                    c++;
                    break;
                case 2:
                    bus[0].show();
                    break;
                case 3:
                    bus[p].avail(0," ");
                    break;
                case 4:
                    goto welcome;
                    break;
                }
            }
            break;
        case 2:
            system("clear");
            while (1)
            {
                cout << "\t\t\tUser Portal\n\n"<< endl;
                cout << "1-Book Bus Ticket" << endl;
                cout << "2-Available Buses" << endl;
                cout << "3-Sign Out" << endl;
                cout << "Enter Your Choice-";
                int choice, k;
                cin >> choice;
                switch (choice)
                {
                case 1:
                    k = bus[p].allotment();
                    if (k){
                        system("clear");
                        cout << "Seat Booked Sucessfully!!" << endl;
                    }
                    else
                     cout<<"Booking cancalled!!"<<endl;
                    break;
                case 2:
                    bus[p].avail(0," ");
                    break;
                case 3:
                    goto welcome;
                    break;
                }
            }
            break;
        case 3:
            system("clear");
            cout << "\t\t\tThank you!!!";
            exit(0);
            break;
        }
    }
    return 0;
}