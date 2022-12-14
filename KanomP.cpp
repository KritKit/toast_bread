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
int ID, Oid, Cnum = 0, OrderID, SSumtotal = 0;
bool cjp;
string Pid[100] = {};
string Pname[100] = {};
string PpriceS[100] = {};
string Punit[100] = {};
string Tid[100] = {};
string Tname[100] = {};
string Tprice[100] = {};
string Ttype[100] = {};
int Tunit[100] = {};
string btop[100][3] = {};
int corder[100] = {};
int dbpung = 0, bd = 0, cn = 0;

struct Product
{
    int id;
    string name;
    string priceS;
    string unit;
};

struct Orders
{
    int OrderIds;
    int Orderpung;
    int Orderloop;
    int Ordertid;
};

void Productlist()
{
    int iunit;
    Product pd;
    ifstream read;
    read.open("C:/Pungping/product.txt");
    int x = 0;
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
        x++;
    }
    read.close();
}

void Selecttopping()
{
    system("CLS");
    int topids, chtop, tno, chid = 0, chkn = 0, chre;
    string Sizes, topid;
    char maxnum[50];
    bool ckp = false, cks = false, ckt = false, ckc = false, checkcha = false;
    bool checktop = false, checknext = false, checktt = false, chrep = false, chker = false, chop = false;
    cout << "#<============================================>#" << endl;
    cout << "| ID |     Topping Name     | Price |   Spoon  |" << endl;
    cout << "#<-------------------------------------------->#" << endl;
    for (int j = 0; j < 100; j++)
    {
        if (Tid[j] != "\0")
        {
            cout << right << "|" << setw(3) << Tid[j] << " | " << setw(20) << Tname[j] << " | " << setw(4) << Tprice[j] << ".-"
                 << "|" << setw(9) << Tunit[j] << " |" << endl;
        }
    }
    cout << "#<============================================>#" << endl;
    do
    {
        do
        {
            cout << "Enter ToppingID : ";
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
                    if (topids != chtop)
                    {
                        ckp = false;
                    }
                    else
                    {
                        tno = i;
                        chid = 1;
                        break;
                    }
                }
                if (chid == 1)
                {
                    for (int g = 0; g < 10; g++)
                    {
                        stringstream ee;
                        ee << btop[bd][g];
                        ee >> chre;
                        if (chre != topids)
                        {
                            chrep = true;
                        }
                        else
                        {
                            chid = 0;
                            chrep = false;
                            chker = true;
                            break;
                        }
                    }
                    if (chrep == false)
                    {
                        cout << Tname[tno] << " Repeated Topping" << endl;
                    }
                    if (chker == false)
                    {
                        if (Tunit[tno] == 0)
                        {
                            SetConsoleTextAttribute(h, 4);
                            cout << Tname[tno] << " Out of Stock" << endl;
                            SetConsoleTextAttribute(h, 7);
                            chid = 0;
                            ckp = false;
                        }
                        else
                        {
                            chid = 1;
                            Tunit[tno] = Tunit[tno] - 1;
                            ckp = true;
                        }
                    }
                }
            }
            chrep = false;
            chker = false;
        } while (ckp == false);
        chrep = false;
        chker = false;
        if (chid == 1)
        {
            chid = 0;
            do
            {
                char checknextx;
                if (cn < 2)
                {
                    cout << cn + 1 << ". " << Tname[tno] << endl;
                    cout << "More Topping? (y/n) : ";
                    cin >> checknextx;
                    if (checknextx == 'y')
                    {
                        btop[bd][cn] = Tid[tno];
                        corder[bd] = cn + 1;
                        dbpung = bd + 1;
                        cn++;
                        chop = false;
                        checktt = true;
                    }
                    else if (checknextx == 'n')
                    {
                        btop[bd][cn] = Tid[tno];
                        corder[bd] = cn + 1;
                        dbpung = bd + 1;
                        cn++;
                        chop = true;
                        checktt = true;
                    }
                    else
                    {
                        cn = 0;
                        chop = true;
                    }
                }
                else if (cn < 3)
                {
                    cout << cn + 1 << ". " << Tname[tno] << endl;
                    cout << "Confirm (y/n) : ";
                    cin >> checknextx;
                    if (checknextx == 'y')
                    {
                        btop[bd][cn] = Tid[tno];
                        corder[bd] = cn + 1;
                        dbpung = bd + 1;
                        cn++;
                        chop = true;
                        checktt = true;
                    }
                    else if (checknextx == 'n')
                    {
                        cout << bd << endl;
                        for (int d = 0; d < cn; d++)
                        {
                            btop[bd][d] = {};
                        }
                        chkn = true;
                        cn = 0;
                        dbpung = bd;
                        chop = true;
                        checktt = true;
                    }
                    else
                    {
                        cn = 0;
                        chop = false;
                    }
                }
            } while (checktt == false);
        }
    } while (chop == false);
    if (chkn == false)
    {
        bd++;
        cn = 0;
    }
    chkn = false;
}

void payment()
{
    int coutd, anum, ar, cra, sumtop = 0, tprices, pung = 0;
    for (int e = 0; e < dbpung; e++)
    {
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
                if (anum == ar)
                {
                    cra = l;
                    break;
                }
            }
            stringstream xx;
            xx << Tprice[cra];
            xx >> tprices;
            sumtop += tprices;
        }
    }
    pung = 10 * dbpung;
    cout << "|" << setw(18) << sumtop + pung << ".-" << setw(16) << "|" << endl;
}

void orderpung()
{
    int coutd, anum, ar, cra;
    for (int e = 0; e < dbpung; e++)
    {
        cout << "#<=================================>#" << endl;
        cout << "| ID |     Topping Name     | Price |" << endl;
        cout << "#<--------------------------------->#" << endl;
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
                if (anum == ar)
                {
                    cra = l;
                    break;
                }
            }
            cout << right << "|" << setw(3) << Tid[cra] << " | " << setw(20) << Tname[cra] << " | " << setw(4) << Tprice[cra] << ".-"
                 << "|" << endl;
        }
        cout << "#<=================================>#" << endl;
        if (Ttype[e] == "n")
        {
            cout << "|"  << " NotToast" << setw(19) << "|" << setw(7)  << " 10.-" << "|" << endl;
        }
        else
        {
            cout << "|"  << " Toast" << setw(22) << "|" << setw(7)  << " 10.-" << "|" << endl;
        }
        cout << "#<=================================>#" << endl;
    }
    payment();
    cout << "#<=================================>#" << endl;
}
void ordercancel()
{
    dbpung = 0;
    bd = 0;
    cn = 0;
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            btop[i][j] = {};
        }
    }
}

void updateorder(int &oid)
{
    // cout << oid << endl;
    string strid;
    int intunit;
    Product pd;
    string orid[100] = {};
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
        strid = to_string(pd.id);
        if (oid == pd.id)
        {
            stringstream p;
            p << pd.unit;
            p >> intunit;
            tempFile << "\n"
                     << pd.id;
            tempFile << "\n"
                     << pd.name;
            tempFile << "\n"
                     << pd.priceS;
            tempFile << "\n"
                     << intunit - 1;
        }
        else
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
}

void saveorder(int ordersid[], int topitaltol, int counttop)
{

    ifstream read;
    read.open("C:/Pungping/orderid.txt");
    if (!read.fail())
    {
        read >> Oid;
    }
    else
    {
        Oid = 0;
    }
    Oid++;
    read.close();
    ofstream write;
    write.open("C:/Pungping/order.txt", ios::app);
    write << "\n"
          << Oid;
    write << "\n"
          << topitaltol;
    write << "\n"
          << counttop;
    for (int i = 0; i < counttop; i++)
    {
        write << "\n"
              << ordersid[i];
    }
    write.close();
    write.open("C:/Pungping/orderid.txt");
    write << Oid;
    write.close();
    cout << "Data save to file" << endl;
}

void confirmorder()
{
    int coutd, anum, ar, cra, inttop, couttop = 0;
    ;
    int ordertid[100] = {};
    for (int e = 0; e < dbpung; e++)
    {
        for (int v = 0; v < corder[e]; v++)
        {
            stringstream tt;
            tt << btop[e][v];
            tt >> inttop;
            ordertid[couttop] = inttop;
            updateorder(inttop);
            couttop++;
        }
    }
    saveorder(ordertid, dbpung, couttop);
    ordercancel();
}

void Orderbread()
{
    Productlist();
    bool check = false;
    char conf;
    do
    {
        cout << "NotToast OR Toast (N/T)" << endl;
        if (bd == 0)
        {
            cout << "Exit (X)" << endl;
        }
        else
        {
            cout << "1. ViewOrder" << endl;
            cout << "2. CancelOrder" << endl;
            cout << "3. ConfirmOrder" << endl;
        }
        char option;
        string ad_pass, stroption;
        cout << "Enter option : ";
        cin >> option;
        stroption = option;
        if (bd == 0)
        {
            if (option == 'N' || option == 'n')
            {
                transform(stroption.begin(), stroption.end(), stroption.begin(), ::tolower);
                Ttype[bd] = option;
                Selecttopping();
                system("CLS");
                check = false;
            }
            else if (option == 'T' || option == 't')
            {
                Ttype[bd] = option;
                Selecttopping();
                system("CLS");
                check = false;
            }
            else if (option == 'X' || option == 'x')
            {
                check = true;
            }
            else
            {
                check = false;
            }
        }
        else
        {
            if (option == 'N' || option == 'n')
            {
                transform(stroption.begin(), stroption.end(), stroption.begin(), ::tolower);
                Ttype[bd] = option;
                Selecttopping();
                system("CLS");
                check = false;
            }
            else if (option == 'T' || option == 't')
            {
                Ttype[bd] = option;
                Selecttopping();
                system("CLS");
                check = false;
            }
            else if (option == '1')
            {
                system("CLS");
                orderpung();
                check = false;
            }
            else if (option == '2')
            {
                ordercancel();
                system("CLS");
                check = true;
            }
            else if (option == '3')
            {
                orderpung();
                cout << "Enter (y/n) : ";
                cin >> conf;
                if (conf == 'y')
                {
                    confirmorder();
                    system("CLS");
                    check = true;
                }
                else
                {
                    system("CLS");
                    check = false;
                }
            }
            else
            {
                check = false;
            }
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

void Readdata()
{
    int x = 0;
    Product pd;
    ifstream read;
    read.open("C:/Pungping/product.txt");
    cout << "#<============================================>#" << endl;
    cout << "| ID |     Topping Name     | Price |   Spoon  |" << endl;
    cout << "#<-------------------------------------------->#" << endl;
    while (!read.eof())
    {
        read >> pd.id;
        read.ignore();
        getline(read, pd.name);
        read >> pd.priceS;
        read >> pd.unit;
        print(pd);
    }
    cout << "#<============================================>#" << endl;
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
            cout << "#<============================================>#" << endl;
            cout << "| ID |     Topping Name     | Price |   Spoon  |" << endl;
            cout << "#<-------------------------------------------->#" << endl;
            print(pd);
            cout << "#<============================================>#" << endl;
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
        cout << "Record not updated" << endl;
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

void viewreportsum()
{
    Productlist();
    Orders od;
    int inttid, sum = 0, intp, tpung = 0, intpung, countar = 0;
    ifstream read;
    read.open("C:/Pungping/order.txt");
    while (!read.eof())
    {
        read >> od.OrderIds;
        read >> od.Orderpung;
        read >> od.Orderloop;
        stringstream ww;
        ww << od.Orderpung;
        ww >> intpung;
        tpung += intpung * 10;
        // cout << tpung << endl;
        for (int t = 0; t < 100; t++)
        {
            if (Tid[t] != "\0")
            {
                countar++;
            }
        }

        for (int i = 0; i < od.Orderloop; i++)
        {
            read >> od.Ordertid;
            // cout << od.Ordertid << " " << endl;
            for (int j = 0; j < countar; j++)
            {
                stringstream ss;
                ss << Tid[j];
                ss >> inttid;
                if (od.Ordertid == inttid)
                {
                    stringstream pp;
                    pp << Tprice[j];
                    pp >> intp;
                    sum += intp;
                }
            }
        }
    }
    read.close();
    cout << sum + tpung << endl;
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
        cout << "5.ReportSumtotal" << endl;
        cout << "6.Exit" << endl;
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
            system("CLS");
            viewreportsum();
            check = false;
        }
        else if (option == 6)
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
    ofstream oidfile("C:/Pungping/orderid.txt");
    oidfile << "0";
    oidfile.close();
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
                << "Raidow";
    productfile << "\n"
                << "5";
    productfile << "\n"
                << "100";

    productfile << "\n"
                << "4";
    productfile << "\n"
                << "DarkChocolate";
    productfile << "\n"
                << "5";
    productfile << "\n"
                << "100";

    productfile << "\n"
                << "5";
    productfile << "\n"
                << "JamOrange";
    productfile << "\n"
                << "5";
    productfile << "\n"
                << "100";

    productfile << "\n"
                << "6";
    productfile << "\n"
                << "Jamstrawbery";
    productfile << "\n"
                << "5";
    productfile << "\n"
                << "100";
    productfile.close();
    ofstream orderfile("C:/Pungping/order.txt");
    orderfile.close();
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
            Orderbread();

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