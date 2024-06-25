#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

class food
{
public:
    char food_name[100];
    int code, cook_time, stoke;
    long int price;
    int enable;
};

class human
{
public:
    char name[30], lastname[60], dadname[30];
    long int code;
    long int mojodi;
    int boss, enable;
    long long int pass;
};

class Date
{
public:
    int day, month, year;
};

istream &operator>>(istream &x, Date &a)
{
    cout << "\n Enter year:";
    cin >> a.year;
    cout << "\n Enter month:";
    cin >> a.month;
    cout << "\n Enter day:";
    cin >> a.day;

    return x;
}

istream &operator<<(istream &x, Date &a)
{
    cout << endl
         << a.year << "-" << a.month << "-" << a.day << endl;
    return x;
}

class SellData
{
public:
    char name[100];
    Date tarikh;
    long int price, costumer_code;
    long int code;
    bool deleted;
};

istream &operator>>(istream &x, food &a)
{
    cout << "\n Enter name:";
    cin >> a.food_name;
    cout << "\n Enter time take to cook:";
    cin >> a.cook_time;
    cout << "\n Enter price:";
    cin >> a.price;
    cout << "\n Enter stoke:";
    cin >> a.stoke;
    a.enable = 1;
    return x;
}

ostream &operator<<(ostream &x, food a)
{
    cout << endl;
    cout << "         food name : " << a.food_name << endl;
    cout << "      time to cook : " << a.cook_time << endl;
    cout << "             price : " << a.price << endl;
    cout << "             stoke : " << a.stoke << endl;
    cout << "        is aviable : " << a.enable << endl;
    cout << "              code : " << a.code << endl;
    return x;
}

istream &operator>>(istream &x, human &a)
{
    cout << "\n Enter name:";
    cin >> a.name;
    cout << "\n Enter lastname:";
    cin >> a.lastname;
    cout << "\n Enter father name:";
    cin >> a.dadname;
    cout << "\n Enter password:";
    cin >> a.pass;
    cout << "\n Enter mojodi : ";
    cin >> a.mojodi;
    cout << "\n Enter 1 if you are an admin and 0 if you are not :";
    cin >> a.boss;
    a.enable = 1;

    return x;
}

ostream &operator<<(ostream &x, human a)
{
    cout << endl;
    cout << "       Code : " << a.code << endl;
    cout << " First Name : " << a.name << endl;
    cout << "  Last Name : " << a.lastname << endl;
    cout << "Father Name : " << a.dadname << endl;
    cout << "      Found : " << a.mojodi << endl;
    cout << "   Password : " << a.pass << endl;
    cout << "    Is Boss : " << a.boss << endl;
    cout << "  Is Enable : " << bool(a.enable);
    cout << endl;

    return x;
}

ostream &operator<<(ostream &x, SellData a)
{
    cout << "     username : " << a.costumer_code << endl;
    cout << "    food name : " << a.name << endl;
    cout << "        price : " << a.price << endl;
    cout << "         date : " << a.tarikh.year << "-" << a.tarikh.month << "-" << a.tarikh.day << endl;
    cout << "   order-code : " << a.code << endl;
    return x;
}

int filesize(char filename[]) // check if file exist, find the size of file
{
    ifstream X;
    int size;
    X.open(filename, ios::in | ios::binary);
    if (!X.is_open())
    {
        return 0;
    }
    else
    {
        X.seekg(0, ios::end);
        size = X.tellg();
        X.close();
        return size;
    }
}

void sabt_food()
{
    food ghaza;
    ofstream F("ghazaha.txt", ios::app | ios::binary);
    long int counter = 3000 + (((long int)F.tellp()) / sizeof(food));
    cin >> ghaza;
    ghaza.code = counter + 1;
    F.write((char *)&ghaza, sizeof(food));
    F.close();
}

void viraiesh_food()
{
    long int code_food;
    food ghaza, ghaza_in;
    cout << "\n\n [-] FOOD-CODE : \n";
    cin >> code_food;
    int pos = (code_food - 3001) * sizeof(food);
    fstream F("ghazaha.txt", ios::out | ios::in | ios::binary);
    F.seekg(pos, ios::beg);
    F.read((char *)&ghaza, sizeof(food));
    if (ghaza.enable)
    {
        cout << " [i] FOOD INFORMATION " << code_food << " :\n"
             << ghaza;
        cout << "\n [i] NEW INFORMATION " << code_food << " :\n";
        cin >> ghaza_in;
        ghaza_in.code = ghaza.code;
        F.seekg(pos, ios::beg);
        F.write((char *)&ghaza_in, sizeof(food));
        cout << "\n [i] FOOD INFOMATION " << code_food << "CHANGE SUCCESSFULLY. :) \n";
    }
    else
    {
        cout << "\n [!] ghaza hazf shode ya vojod nadarad . . .\n";
    }
    F.close();
}

void hazf_food()
{
    long int code_food;
    food ghaza;
    cout << " [-] FOOD CODE : \n";
    cin >> code_food;
    int pos = (code_food - 3001) * sizeof(food);
    fstream C("ghazaha.txt", ios::out | ios::in | ios::binary);
    C.seekg(pos, ios::beg);
    C.read((char *)&ghaza, sizeof(food));
    if (ghaza.enable)
    {
        ghaza.enable = 0;
        C.seekg(pos, ios::beg);
        C.write((char *)&ghaza, sizeof(food));
        cout << "\n [i] FOOD " << code_food << " IS DELETED . . . \n";
    }
    else
    {
        cout << "\n [!] ALLREADY DELETED . . .\n";
    }
    C.close();
}

void khandan_food()
{
    ifstream Y("ghazaha.txt", ios::in | ios::binary);
    food ghaza;
    Y.read((char *)&ghaza, sizeof(food));
    while (Y.eof() != true)
    {
        if (ghaza.enable)
        {
            cout << ghaza;
            cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        }
        Y.read((char *)&ghaza, sizeof(food));
    }
    Y.close();
}

food search_food(char ghaza_in[])
{
    int flag = 0;
    food ghaza;

    ifstream Y("ghazaha.txt", ios::in | ios::binary);
    Y.read((char *)&ghaza, sizeof(food));

    while (Y.eof() != true)
    {

        if (strcmp(ghaza_in, ghaza.food_name) == 0)
        {
            flag = 1;
            break;
        }
        Y.read((char *)&ghaza, sizeof(food));
    }
    Y.close();

    if (flag == 0)
    {
        ghaza.code = 0;
        return ghaza;
    }
    else
    {
        return ghaza;
    }
}

void sabte_ensan()
{
    human ensan;
    cin >> ensan;
    fstream C("clinets.txt", ios::app | ios::in | ios::binary);

    C.seekp(0, ios::end);
    long int counter = 4000 + (((long int)C.tellp()) / sizeof(human));
    ensan.code = counter + 1;

    C.write((char *)&ensan, sizeof(human));
    C.close();
}

void hazf_ensan()
{
    long int code_user;
    human ensan;
    cout << " [-] USERNAME : \n";
    cin >> code_user;
    int pos = (code_user - 4001) * sizeof(human);
    fstream C("clinets.txt", ios::out | ios::in | ios::binary);
    C.seekg(pos, ios::beg);
    C.read((char *)&ensan, sizeof(human));
    if (ensan.enable)
    {
        ensan.enable = 0;
        C.seekg(pos, ios::beg);
        C.write((char *)&ensan, sizeof(human));
        cout << "\n [i] CLINTE " << code_user << " DELETED . . . \n";
    }
    else
    {
        cout << "\n [!] ALLREADY DELETED.\n";
    }
    C.close();
}

void namayesh_sabad(long int username)
{
    cout << "\n\n";
    ifstream Y("forosh.txt", ios::binary);
    SellData fish;
    Y.read((char *)&fish, sizeof(SellData));
    while (Y.eof() != true)
    {
        if (fish.costumer_code == username)
        {
            if(fish.deleted== false)
            {
                cout << fish;
                cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
            }
        }
        Y.read((char *)&fish, sizeof(SellData));
    }
    Y.close();
}

void viraiesh_ensan()
{
    long int code_user;
    human ensan, ensan_in;
    cout << " [-] USERNAME : \n";
    cin >> code_user;
    int pos = (code_user - 4001) * sizeof(human);
    fstream C("clinets.txt", ios::out | ios::in | ios::binary);
    C.seekg(pos, ios::beg);
    C.read((char *)&ensan, sizeof(human));
    if (ensan.enable)
    {
        cout << "[i] INFORMATION " << code_user << " :\n"
             << ensan;
        cout << "\n [i] NEW INFORMATION " << code_user << " :\n";
        cin >> ensan_in;
        ensan_in.code = ensan.code;
        C.seekg(pos, ios::beg);
        C.write((char *)&ensan_in, sizeof(human));
        cout << "\n [i] CLINET INFORAMTION WITH USERNAME " << code_user << " CHANGE SUCCESSFULLY. :) \n";
    }
    else
    {
        cout << "\n [!] CLIENT DOSENT EXIST. :( \n";
    }
    C.close();
}

void sabte_forosh(long int coustumer_c, food ghaza, Date today)
{
    SellData fish_forosh;
    fish_forosh.code = (3000 + (filesize("forosh.txt") / sizeof(SellData)));
    strcpy(fish_forosh.name, ghaza.food_name);
    fish_forosh.costumer_code = coustumer_c;
    fish_forosh.tarikh.year = today.year;
    fish_forosh.tarikh.month = today.month;
    fish_forosh.tarikh.day = today.day;
    fish_forosh.price = ghaza.price;
    fish_forosh.deleted = false;
    fstream Y("forosh.txt", ios::in | ios::app | ios::binary);
    Y.write( (char *) &fish_forosh, sizeof(SellData) );
    Y.close();
}

void khandan_ensan()
{
    ifstream Y("clinets.txt", ios::in);
    human ensan;
    Y.read((char *)&ensan, sizeof(ensan));
    while (Y.eof() != true)
    {
        if (ensan.enable)
        {
            cout << ensan;
            cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        }

        Y.read((char *)&ensan, sizeof(ensan));
    }
    Y.close();
}

void print_tarkoneshha()
{
    ifstream Y("forosh.txt", ios::in);
    SellData fish;
    Y.read((char *)&fish, sizeof(SellData));
    while (Y.eof() != true)
    {
        cout << fish;
        Y.read((char *)&fish, sizeof(SellData));
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
             << endl;
    }
    Y.close();
}

void print_tarakonesh_limited()
{
    Date tarikh_start, tarikh_end;
    cout << endl
         << "FROM : ";
    cin >> tarikh_start;
    cout << endl
         << "UNITL : ";
    cin >> tarikh_end;

    SellData thing;
    fstream fish("forosh.txt", ios::in);
    fish.read((char *)&thing, sizeof(SellData));
    cout << "PAST ORDER : " << endl;
    while (fish.eof() != true)
    {
        if ((tarikh_start.year <= thing.tarikh.year) && (thing.tarikh.year <= tarikh_end.year))
        {
            if ((tarikh_start.month <= thing.tarikh.month) && (thing.tarikh.month <= tarikh_end.month))
            {
                if ((tarikh_start.day <= thing.tarikh.day) && (thing.tarikh.day <= tarikh_end.day))
                {
                    cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                         << endl;
                    cout << thing;
                }
            }
        }
        fish.read((char *)&thing, sizeof(SellData));
    }
    fish.close();
}

int vorod(long int code_user)
{
    long int password;
    human ensan;
    ifstream Y("clinets.txt", ios::in);
    Y.read((char *)&ensan, sizeof(ensan));
    while (Y.eof() != true)
    {
        if (ensan.enable)
        {
            if (code_user == ensan.code)
            {
                cout << "\n \t [-] USERNAME FOUND . . .\n\n [-] ENTER PASSWORD :";
                cin >> password;
                if (ensan.pass == password)
                {
                    cout << "\n\n [i] LOADING . . ."
                         << "\n WELCOME MR/MRS " << ensan.name << endl;
                    if (ensan.boss == 1)
                    {
                        return 2; // karbar admin = 2
                    }
                    return 1; // karbar normal = 1
                }
                else
                {
                    cout << "\n [!] WRONG PASSWORD . . .\n";
                    return 0;
                }
            }
        }
        Y.read((char *)&ensan, sizeof(ensan));
    }
    Y.close();
    cout << "\n\n [!] COULDNT FIND ENTERED USERNAME . . .";
    return 0;
}

void taghir_mojodi(long int price, long int user_code, int opr)
{
    human ensan;
    int pos = (user_code - 4001) * sizeof(human);
    fstream C("clinets.txt", ios::out | ios::in | ios::binary);
    C.seekg(pos, ios::beg);
    C.read((char *)&ensan, sizeof(human));
    if (opr == 1)
    { // age ezafe bood
        ensan.mojodi = ensan.mojodi + price;
    }
    else
    { // age menha bood
        ensan.mojodi = ensan.mojodi - price;
    }
    C.seekg(pos, ios::beg);
    C.write((char *)&ensan, sizeof(human));
}

long int mojodi_f(long int user_code)
{
    human ensan;
    int pos = (user_code - 4001) * sizeof(human);
    fstream C("clinets.txt", ios::in | ios::binary);
    C.seekg(pos, ios::beg);
    C.read((char *)&ensan, sizeof(human));
    C.close();
    return ensan.mojodi;
}

void food_stock()
{
    ifstream Y("ghazaha.txt", ios::in | ios::binary);
    food ghaza;
    Y.read((char *)&ghaza, sizeof(food));
    cout << "\n\nfood name << ============= >> stock\n";
    while (Y.eof() != true)
    {
        if (ghaza.enable)
        {
            cout << endl
                 << ghaza.food_name << " << ============= >> " << ghaza.stoke << endl;
        }
        Y.read((char *)&ghaza, sizeof(food));
    }
    Y.close();
}

void sefaresh(Date today, long int karbar)
{
    long int time_to_cook = 0;
    long int price = 0;
    fstream F("ghazaha.txt", ios::out | ios::in | ios::binary);
    
    do
    {
        cout << "\n\n\t***** FOODS : ***** : \n";
        long int mojodi_clinet = mojodi_f(karbar);

        khandan_food();

        cout << "\n [i] YOUR FOUND : " << mojodi_clinet << endl;
        cout << "\n [i] AT THE END ENTER ZERO \n";
        cout << "\n [i] ENTER FOOD-CODE : ";
        long int choice;
        cin >> choice;
        if (!choice)
        {
            break;
        }
        food ghaza;
        long int pos = (choice - 3001) * sizeof(food);
        F.seekg(pos, ios::beg);
        F.read((char *)&ghaza, sizeof(food));
        if (ghaza.enable)
        {
            if (mojodi_clinet > ghaza.price)
            {
                ghaza.stoke = ghaza.stoke - 1;
                time_to_cook += ghaza.cook_time;
                price += ghaza.price;

                taghir_mojodi(ghaza.price, karbar, 2);
                sabte_forosh(karbar, ghaza, today);

                F.seekg(pos, ios::beg);
                F.write((char *)&ghaza, sizeof(food));

                cout << "\n\n [i] ORDER WITH FOOD-CODE : " << ghaza.code << " HAS REGISTERED. :)";
            }
            else
            {
                cout << "\n\n [w]  YOUR CASH FOR FOOD '" << ghaza.food_name << "' IS NOT ENOUGH. :(";
            }
        }
        else
        {
            cout << "\n\n [w] FOOD HAS BEEN DELETED OR NOT AVIABLE . . .\n";
        }
    } while (true);
    cout << "\n [i] YOUR WAITING TIME : " << time_to_cook << endl;
    cout << "\n [i] THE FINAL COST OF ORDER : " << price;
}

void increase_stoke(long int food_code, int tedad)
{
    food ghaza;
    int pos = (food_code - 3001) * sizeof(food);
    fstream C("ghazaha.txt", ios::out | ios::in | ios::binary);
    C.seekg(pos, ios::beg);
    C.read((char *)&ghaza, sizeof(food));
    if (ghaza.enable)
    {
        ghaza.stoke += tedad;
        C.seekg(pos, ios::beg);
        C.write((char *)&ghaza, sizeof(food));
        cout << "\n [i] STOKE FOR FOOD " << food_code << " INCREASED SUCCESSFULLY. :) \n";
    }
    else
    {
        cout << "\n [!] FOOD DOSENT EXIST. :( \n";
    }
    C.close();
}

void cansel_order(long int code_karbar)
{
    long int code_sefaresh;
    bool flag;
    SellData fish;
    cout << "\n [-] ORDER CODE : \n";
    cin >> code_sefaresh;
    int pos = (code_sefaresh - 3000) * sizeof(SellData);
    fstream F("forosh.txt", ios::out | ios::in | ios::binary);
    if(F.is_open() == false)
    {
        cout<<"\n [!] error in opening !";
        return;
    }
    F.seekg(pos, ios::beg);
    F.read((char *)&fish, sizeof(human));
    int file_size = filesize("forosh.txt");
    if (pos < file_size)
    {
        if (fish.deleted == false)
        {
            fish.deleted = true;
            F.seekg(pos, ios::beg);
            F.write((char *)&fish, sizeof(SellData));
            taghir_mojodi(fish.price,code_karbar,1);
            cout<<"\n [i] ORDER WITH CODE "<<code_sefaresh<<" CANSELED. ";
        }
        else
        {
            cout << "\n [!] ORDER ALLREADY CANSELED. :( \n";
        }
    }
    else
    {
        cout << "\n ORDER DOSENT EXSIT. :| \n";
    }
    F.close();
}

int main(void)
{
    Date TODAY;
    long int code_user;
    int choice;
    cout << " TODAY IS :\n";
    cin >> TODAY;
    cout << "\n\n\t *** WELCOME TO 'FOUR' RESTURANT *** \n\n";
    cout << "\n [-] MEMBERSHIP CODE : ";
    cin >> code_user;

    int karbar = vorod(code_user);

    if (karbar == 2)
    { // karbar admin
        do
        {
            cout << "\n * admin menu :\n";
            cout << "\n  1 - NEW FOOD REGISTRATION";
            cout << "\n  2 - SHOW ALL FOOD";
            cout << "\n  3 - CLIENT REGISTRATION";
            cout << "\n  4 - SHOW ALL CLINETS";
            cout << "\n  5 - FOOD SEARCH";
            cout << "\n  6 - DELETE CLINET";
            cout << "\n  7 - EDIT CLINET";
            cout << "\n  8 - EDIT FOOD";
            cout << "\n  9 - DELETE FOOD";
            cout << "\n 10 - PRINT ALL PAST ORDERS";
            cout << "\n 11 - PRINT ALL PAST ORDERS WITH DATE LIMIT";
            cout << "\n 12 - PRINT FOOD STOCK";
            cout << "\n 13 - INCREASE STOKE";
            cout << "\n  0 - EXIT";
            cout << "\n ***  Enter your choice:";
            cin >> choice;
            switch (choice)
            {
            case 1:
            {
                cout << "\n  1 - NEW FOOD REGISTRATION";
                sabt_food();
            }
            break;
            case 2:
            {
                cout << "\n  2 - SHOW ALL FOOD";
                khandan_food();
            }
            break;
            case 3:
            {
                cout << "\n  3 - CLIENT REGISTRATION";
                sabte_ensan();
            }
            break;
            case 4:
            {
                cout << "\n  4 - SHOW ALL CLINETS";
                khandan_ensan();
            }
            break;
            case 5:
            {
                char ghaza_in[100];
                cout << "\n  5 - FOOD SEARCH" << endl;
                cout << endl
                     << "\n [-] Enter Name of The Food : ";
                cin >> ghaza_in;
                food result = search_food(ghaza_in);
                if (result.code == 0)
                {
                    cout << "\n [!] Cant Find Entered Food .";
                }
                else
                {
                    cout << "\n [i] FOOD FOUNDED :\n";
                    cout << result;
                }
            }
            break;
            case 6:
            {
                cout << "\n  6 - DELETE CLINET";
                hazf_ensan();
            }
            break;
            case 7:
            {
                cout << "\n  7 - EDIT CLINET";
                viraiesh_ensan();
            }
            break;
            case 8:
            {
                cout << "\n  8 - EDIT FOOD";
                viraiesh_food();
            }
            break;
            case 9:
            {
                cout << "\n  9 - DELETE FOOD";
                hazf_food();
            }
            break;
            case 10:
            {
                cout << "\n 10 - PRINT ALL PAST ORDERS" << endl;
                print_tarkoneshha();
            }
            break;
            case 11:
            {

                cout << "\n 11 - PRINT ALL PAST ORDERS WITH DATE LIMIT";
                print_tarakonesh_limited();
            }
            break;
            case 12:
            {
                cout << "\n 12 - PRINT FOOD STOCK";
                food_stock();
            }
            break;
            case 13:
            {
                cout << "\n 13 - INCREASE STOKE";
                long int FOOD_CODE;
                int TEDAD;
                cout << "\n\n [-] FOOD-CODE YOU WANNA RAISE THE STOKE : ";
                cin >> FOOD_CODE;
                cout << "\n [-] HOW MUCH YOU WANNA INCEASE IT : ";
                cin >> TEDAD;
                increase_stoke(FOOD_CODE, TEDAD);
            }
            break;
            case 0:
            {
            }
            break;
            default:
            {
                cout << "\n [!] Wrong Choice. Try again.";
            }
            }
            cout << "\n\n\n\n\n\n\n\n\n\n";
        } while (choice != 0);
    }
    else if (karbar == 1)
    { // karbar normal
        do
        {
            cout << "\n * clinet menu :";
            cout << "\n  1 - SHOW AVIABLE FOOD";
            cout << "\n  2 - FOOD SEARCH";
            cout << "\n  3 - ORDER";
            cout << "\n  4 - PAST ORDER";
            cout << "\n  5 - CANSEL ORDER";
            cout << "\n  6 - SHOW FOUND";
            cout << "\n  0 - Exit";
            cout << "\n ***  Enter your choice:";
            cin >> choice;
            switch (choice)
            {
            case 1:
            {
                cout << "\n  1 - SHOW AVIABLE FOOD" << endl;
                khandan_food();
            }
            break;
            case 2:
            {
                cout << "\n  2 - FOOD SEARCH" << endl;
                char ghaza_in[100];
                cout << "\n [-] Enter Name of The Food : ";
                cin >> ghaza_in;
                food result = search_food(ghaza_in);
                if (result.code == 0)
                {
                    cout << "\n [!] Cant Find Entered Food .";
                }
                else
                {
                    cout << "\n [i] FOOD FOUNDED :\n";
                    cout << result;
                }
            }
            break;
            case 3:
            {
                cout << "\n  3 - ORDER" << endl;
                sefaresh(TODAY, code_user);
            }
            break;
            case 4:
            {
                cout << "\n  4 - PAST ORDER";
                namayesh_sabad(code_user);
            }
            break;
            case 5:
            {
                cout << "\n  5 - CANSEL ORDER";
                cansel_order(code_user);
            }
            break;
            case 6:
            {
                cout<< "\n  6 - SHOW FOUND";
                cout<<" [i] found : "<<mojodi_f(code_user);
            }
            break;
            case 0:
            {
            }
            break;
            default:
            {
                cout << "\n [!] Wrong Choice. Try again.";
            }
            }
            cout << "\n\n\n\n\n\n\n\n\n\n";
        } while (choice != 0);
    }
    return 0;
}
