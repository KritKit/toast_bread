#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <direct.h>
#include <Windows.h>
using namespace std;
void Readdata();
void Bread();

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
int ID, Cnum = 0, OrderID, SSumtotal = 0;
bool cjp;
string Pid[100] = {};
string Pname[100] = {};
string PpriceS[100] = {};
string Punit[100] = {};
string Tid[100] = {};
string Tname[100] = {};
string Tprice[100] = {};
int Tunit[100] = {};
string btop[100][3] = {};
int corder[3] = {};

struct Product
{
    int id;
    string name;
    string priceS;
    string unit;
};

/*struct Orders
{
    int OrderIds;
    int OrderQl;
    int OrderPid;
    int Orderflour;
    string OrderSize;
    int OrderQ;
    int OrderTT;
    int Orderwday;
    int Orderday;
    int Ordermount;
    int Orderyear;
    string Ordertime;
};*/
void Productlist()
{
    int iunit;
    Product pd;
    ifstream read;
    read.open("C:/Pungping/product.txt");
    int x = 0;
    // cout << "+==========================================+" << endl;
    // cout << ": ID :         Name         : Price : Unit :" << endl;
    // cout << "+------------------------------------------+" << endl;
    while (!read.eof())
    {
        string strid;
        read >> pd.id;
        read.ignore();
        getline(read, pd.name);
        read >> pd.priceS;
        read >> pd.unit;

        strid = to_string(pd.id);
        stringstream pp;
        pp << pd.unit;
        pp >> iunit;

        Tid[x] = strid;
        Tname[x] = pd.name;
        Tprice[x] = pd.priceS;
        Tunit[x] = iunit;
        // cout << right << ":" << setw(3) << Tid[x] << " : " << setw(20) << Tname[x] << " : " << setw(5) << Tprice[x] << " :" << setw(5) << Tunit[x] << " :" << endl;
        x++;
        // cout << pd.name << endl;
    }
    // cout << "+=========================================+" << endl;
    read.close();
}

void Selecttopping()
{
    system("CLS");
    Productlist();
    // int slp, intid, no, intkS, intkM, intkL, intnS, intnM, intnL, intsum, intPS, intPM, intPL, Noa;
    // int stopping, tkiM, tkiL, tniS, tniM, tniL, Qt = 0, chks, quan, conselect, flour;
    int topids,chtop,tno,cn = 0,chid = 0,bd = 0;
    string Sizes, topid;
    char maxnum[50];
    bool ckp = false, cks = false, ckt = false, ckc = false, checkcha = false;
    bool checktop = false,checknext = false,checktt = false;
    do
    {
        cout << "+==========================================+" << endl;
        cout << ": ID :         Name         : Price : Unit :" << endl;
        cout << "+------------------------------------------+" << endl;
        for (int j = 0; j < 100; j++)
        {
            if(Tid[j] != "\0"){
                cout << right << ":" << setw(3) << Tid[j] << " : " << setw(20) << Tname[j] << " : " << setw(5) << Tprice[j] << " :" << setw(5) << Tunit[j] << " :" << endl;
            }
        }
        cout << "+=========================================+" << endl;
        do
        {
            do
            {
                cout << "Enter Toppingid : ";
                cin >> topid;
                for (int o = 0; o < topid.size(); o++)
                {
                    maxnum[o] = topid[o];
                    if (int(maxnum[o]) < 48 || int(maxnum[o]) > 57)
                    {
                        checkcha = false;
                        break;
                    }
                    else
                    {
                        checkcha = true;
                    }
                }
                stringstream dd;
                dd << topid;
                dd >> topids;
                if (checkcha == true)
                {
                    for (int i = 0; i < 100; i++)
                    {
                        stringstream ff;
                        ff << Tid[i];
                        ff >> chtop;
                        if(topids != chtop){
                            ckp = false;
                        }else{
                            tno = i;
                            chid = 1;
                            ckp = true;
                            break;
                        }
                    }
                    if(chid == 1){
                        if(Tunit[tno] == 0){
                            SetConsoleTextAttribute(h,4);
                            cout << Tname[tno] << " Out of Stock" << endl;
                            SetConsoleTextAttribute(h,7);
                            ckp = false;
                        }else{
                            Tunit[tno] =  Tunit[tno] - 1;
                            ckp = true;
                        }
                    }
                }
            } while (ckp == false);
            if(chid == 1){
            char checknextx;
            if(cn < 2){
                cout << cn + 1 << ". " << Tname[tno] << endl;
                cout << "Next Topping (y/n) : "; 
                cin >> checknextx;
                if(checknextx == 'y'){
                    btop[bd][cn] = Tid[tno];
                    corder[bd] = cn+1;
                    cn++;
                    checktt = false;
                }else if(checknextx == 'n'){
                    btop[bd][cn] = Tid[tno];
                     corder[bd] = cn+1;
                    cn++;
                    checktt = true;
                }
            }else if(cn < 3){
                cout << cn << ". " << Tname[tno] << endl;
                cout << "Confirm (y/n) : "; 
                cin >> checknextx;
                if(checknextx == 'y'){
                    btop[bd][cn] = Tid[tno];
                    corder[bd] = cn+1;
                    cn++;
                    checktt = true;
                }else if(checknextx == 'n'){
                    for (int d = 0; d < cn; d++)
                    {
                        btop[bd][d] = {};
                    }
                    cn = 0;
                    checktt = false;
                }
            }
            }
            chid = 0;
        } while (checktt == false);
        system("CLS");
        int coutd,anum,ar,cra;
        for (int e = 0; e < bd+1; e++)
        {
            cout << "+===================================+" << endl;
            cout << ": ID :         Name         : Price :" << endl;
            cout << "+-----------------------------------+" << endl;
            for (int v = 0; v < corder[e]; v++)
            {
                stringstream aa;
                aa << btop[e][v];
                aa >> anum;
                for (int l = 0; l < 100; l++)
                {
                    stringstream gh;
                    gh << Tid[l];
                    gh >> ar;
                    if(anum == ar){
                        cra = l;
                        break;
                    }
                }
                cout << right << ":" << setw(3) << Tid[cra] << " : " << setw(20) << Tname[cra] << " : " << setw(5) << Tprice[cra] << " :" << endl;
            }
            cout << "+===================================+" << endl;
        }
        bd++;
        cn = 0;
    } while (checktop == false);
    
}

void Topping()
{
    cout << endl;
    int conselect;
    char can, con;
    Selecttopping();
    bool ckc = false;
    do{
        if(Cnum == 2){
            cout << endl;
            cout << "1.ViewOrder" << endl;
            cout << "2.CancelOrder" << endl;
            cout << "3.ConfirmOrder" << endl;
            cout << "Enter Select : ";
            cin >> conselect;
            if(conselect == 1){

            }else if(conselect == 2){

            }else if(conselect == 3){
            }else{
                ckc = false;
            }
        }else{
            cout << endl;
            cout << "1.Next Topping" << endl;
            cout << "2.Confirm" << endl;
            cout << "Enter Select : ";
            cin >> conselect;
            if(conselect == 1){
                Cnum += 1;
                Topping();
            }else if(conselect == 2){
                Bread();
            }
        }
    } while (ckc == false);
}


void Orderbread()
{
    bool check = false;
    do
    {
        cout << "NotToast OR Toast (N/T)" << endl;
        cout << "Exit (X)" << endl;
        char option;
        string ad_pass;
        cout << "Enter option : ";
        cin >> option;
        if (option == 'N' || option == 'n')
        {
            Topping();

            check = true;
        }
        else if (option == 'T' || option == 't')
        {
            Topping();


            check = true;
        }
        else if (option == 'X' || option == 'x')
        {
            check = true;
        }
        else
        {
            check = false;
        }
    } while (check == false);
}

void Addproduct()
{
    Product pd;
    cout << "Enter toping name : ";
    cin.get();
    getline(cin, pd.name);
    cout << "Enter toping price : ";
    cin >> pd.priceS;
    cout << "Enter toping unit : ";
    cin >> pd.unit;
    ID++;

    ofstream write;
    write.open("C:/Pungping/product.txt", ios::app);
    write << "\n"
          << ID;
    write << "\n"
          << pd.name;
    write << "\n"
          << pd.priceS;
    write << "\n"
          << pd.unit;
    write.close();
    write.open("C:/Pungping/id.txt");
    write << ID;
    write.close();
    cout << "Data save to file" << endl;
}

void print(Product s)
{
    cout << right << ":" << setw(3) << s.id << " : " << setw(20) << s.name << " : " << setw(5) << s.priceS << " :" << setw(5) << s.unit << "  :" << endl;
}


void Bread()
{
    int conselect;
    char can, con;
    Orderbread();
    bool checkbread = false;
    do{
            cout << "1.Select Next Bread" << endl;
            // cout << "2.ViewOrder" << endl;
            // cout << "3.CancelOrder" << endl;
            // cout << "4.ConfirmOrder" << endl;
            cout << "Enter Select : ";
            cin >> conselect;
            if(conselect == 1){              
                system("CLS");
                checkbread = true;
                Bread();
                
            }else if(conselect == 2){
                system("CLS");
                checkbread = true;
            }
       } while (checkbread == false);
}

void Readdata()
{
    int x = 0;
    Product pd;
    ifstream read;
    read.open("C:/Pungping/product.txt");
    cout << "+===========================================+" << endl;
    cout << ": ID :         Name         : Price : Unit  :" << endl;
    cout << "+-------------------------------------------+" << endl;
    while (!read.eof())
    {
        read >> pd.id;
        read.ignore();
        getline(read, pd.name);
        read >> pd.priceS;
        read >> pd.unit;
        print(pd);
    }
    cout << "+===========================================+" << endl;
    read.close();

}

int searchData()
{
    int id;
    cout << "Enter id you want to search : ";
    cin >> id;
    Product pd;
    ifstream read;
    read.open("C:/Pungping/product.txt");
    while (!read.eof())
    {
        read >> pd.id;
        read.ignore();
        getline(read, pd.name);
        read >> pd.priceS;
        read >> pd.unit;
        if (pd.id == id)
        {
            cout << "+===========================================+" << endl;
            cout << ": ID :         Name         : Price : Unit  :" << endl;
            cout << "+-------------------------------------------+" << endl;
            print(pd);
            cout << "+===========================================+" << endl;
            return id;
        }
    }
}

void Updatedata()
{
    int id = searchData();
    cout << "You want to update record (y/n) : ";
    char choice;
    cin >> choice;
    if (choice == 'y')
    {
        Product newData;
        cout << "Enter new product name : ";
        cin.get();
        getline(cin, newData.name);
        cout << "Enter price : ";
        cin >> newData.priceS;
        cout << "Enter unit : ";
        cin >> newData.unit;
        Product pd;
        ofstream tempFile;
        tempFile.open("C:/Pungping/temp.txt");
        ifstream read;
        read.open("C:/Pungping/product.txt");
        while (!read.eof())
        {
            read >> pd.id;
            read.ignore();
            getline(read, pd.name);
            read >> pd.priceS;
            read >> pd.unit;
            if (pd.id != id)
            {
                tempFile << "\n"
                         << pd.id;
                tempFile << "\n"
                         << pd.name;
                tempFile << "\n"
                         << pd.priceS;
                tempFile << "\n"
                         << pd.unit;
            }
            else
            {
                tempFile << "\n"
                         << pd.id;
                tempFile << "\n"
                         << newData.name;
                tempFile << "\n"
                         << newData.priceS;
                tempFile << "\n"
                         << newData.unit;
            }
        }
        read.close();
        tempFile.close();
        remove("C:/Pungping/product.txt");
        rename("C:/Pungping/temp.txt", "C:/Pungping/product.txt");
        cout << "Data updated successfuly" << endl;
    }
    else
    {
        cout << "Record not deleted" << endl;
    }
}

void deleteData()
{
    int id = searchData();
    cout << "You want to delete record (y/n) : ";
    char choice;
    cin >> choice;
    if (choice == 'y')
    {
        Product pd;
        ofstream tempFile;
        tempFile.open("C:/Pungping/temp.txt");
        ifstream read;
        read.open("C:/Pungping/product.txt");
        while (!read.eof())
        {
            read >> pd.id;
            read.ignore();
            getline(read, pd.name);
            read >> pd.priceS;
            read >> pd.unit;
            if (pd.id != id)
            {
                tempFile << "\n"
                         << pd.id;
                tempFile << "\n"
                         << pd.name;
                tempFile << "\n"
                         << pd.priceS;
                tempFile << "\n"
                         << pd.unit;
            }
        }
        read.close();
        tempFile.close();
        remove("C:/Pungping/product.txt");
        rename("C:/Pungping/temp.txt", "C:/Pungping/product.txt");
        cout << "Data deleted successfuly" << endl;
    }
    else
    {
        cout << "Record not deleted" << endl;
    }
}

/*void datetime()
{
    time_t nows;
    struct tm datelc;
    nows = time(NULL);
    datelc = *localtime(&nows);
    cout << datelc.tm_mday << "/" << datelc.tm_mon + 1 << "/" << datelc.tm_year + 1900 << endl;
    cout << datelc.tm_hour << ":" << datelc.tm_min << ":" << datelc.tm_sec;
}*/

void Checkfile()
{
    ifstream read;
    read.open("C:/Pungping/id.txt");
    if (!read.fail())
    {
        read >> ID;
    }
    else
    {
        ID = 0;
    }
    read.close();
}

void admin()
{
    Checkfile();
    bool check = false;
    do
    {
        cout << "1.ADD" << endl;
        cout << "2.Check" << endl;
        cout << "3.Update" << endl;
        cout << "4.Delete" << endl;
        cout << "5.Exit" << endl;
        int option;
        cout << "Enter option : ";
        cin >> option;
        if (option == 1)
        {
            system("CLS");
            Addproduct();
            check = false;
        }
        else if (option == 2)
        {
            system("CLS");
            Readdata();
            check = false;
        }
        else if (option == 3)
        {
            system("CLS");
            Updatedata();
            system("CLS");
            check = false;
        }
        else if (option == 4)
        {
            system("CLS");
            deleteData();
            system("CLS");
            check = false;
        }
        else if (option == 5)
        {
            check = true;
        }
        else
        {
            system("CLS");
            check = false;
        }
    } while (check == false);
    system("CLS");
}

void Creatfile()
{
    mkdir("C:/Pungping");
    ofstream pidfile("C:/Pungping/id.txt");
    pidfile << "6";
    pidfile.close();
    /*ofstream oidfile("C:/Pungping/orderid.txt");
    oidfile << "0";
    oidfile.close();*/
    ofstream productfile("C:/Pungping/product.txt");
    productfile << "\n"
                << "1";
    productfile << "\n"
                << "Sugar";
    productfile << "\n"
                << "5";
    productfile << "\n"
                << "100";

    productfile << "\n"
                << "2";
    productfile << "\n"
                << "Chocolate";
    productfile << "\n"
                << "5";
    productfile << "\n"
                << "100";

    productfile << "\n"
                << "3";
    productfile << "\n"
                << "";
    productfile << "\n"
                << "5";
    productfile << "\n"
                << "100";

    productfile << "\n"
                << "4";
    productfile << "\n"
                << "";
    productfile << "\n"
                << "5";
    productfile << "\n"
                << "100";

    productfile << "\n"
                << "5";
    productfile << "\n"
                << "";
    productfile << "\n"
                << "5";
    productfile << "\n"
                << "100";

    productfile << "\n"
                << "6";
    productfile << "\n"
                << "";
    productfile << "\n"
                << "5";
    productfile << "\n"
                << "100";
    productfile.close();
    /*ofstream orderfile("C:/Pungping/order.txt");
    orderfile.close();*/
    ofstream openfile("C:/Pungping/open.dll");
    openfile.close();
}

void select()
{
    bool check = false;
    do
    {
        cout << "1.Buy" << endl;
        cout << "2.For employee" << endl;
        cout << "3.Exit" << endl;
        int option;
        string ad_pass;
        cout << "Enter option : ";
        cin >> option;
        if (option == 1)
        {
            system("CLS");
            Bread();

            check = false;
        }
        else if (option == 2)
        {
            system("CLS");
            cout << "Enter password: ";
            cin >> ad_pass;
            if (ad_pass == "admin1234")
            {
                system("CLS");
                admin();
            }
            else
            {
                system("CLS");
                cout << "Wrong password!" << endl;
            }
            check = false;
        }
        else if (option == 3)
        {
            check = true;
        }
        else
        {
            check = false;
        }
    } while (check == false);
}

int main()
{
    ofstream myfile;
    myfile.open("C:/Pungping/open.dll");
    if (myfile)
    {
        select();
    }
    else
    {
        Creatfile();
        select();
    }
}