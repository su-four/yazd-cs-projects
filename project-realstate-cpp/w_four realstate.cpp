#include <iostream>
#include <fstream>
using namespace std;

// function that check if file exist or not

bool exists(char a[])
{
    fstream foo(a, ios::in);
    if (foo.good())
    {
        foo.close();
        return true;
    }
    else
    {
        foo.close();
        return false;
    }
}

// function that return size of file
int filesize(char filename[])
{
    ifstream X;
    int size;
    X.open(filename, ios::in);
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

// class date
class Date
{
public:
    int day, month, year;
};

// cin operator for date
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

// cout operator for date
ostream &operator<<(ostream &x, Date &a)
{
    cout << a.year
         << " / "
         << a.month
         << " / "
         << a.day;
    return x;
}

bool operator<=(Date a, Date b)
{
    // a <= b
    if (a.year < b.year)
    {
        return true;
    }
    else if (a.year == b.year)
    {
        if (a.month < b.month)
        {
            return true;
        }
        else if (a.month == b.month)
        {
            if (a.day <= b.day)
            {
                return true;
            }
        }
    }
    return false;
}

// class melk
class melk
{
protected:
    // type = 1 -> Aparteman, type = 2 -> Vila, type = 3 -> Zamin
    int type;
    bool foroshi;
    bool elevator;
    int metrazh;
    int tedad_otagh;
    int tabghe;
    long long int price;

public:
    int melk_id;
    bool enable;
    bool avaible;
    friend istream &operator>>(istream &in, melk &a);
    friend ostream &operator<<(ostream &f2, melk &a);
    friend bool operator==(const melk &one, const melk &two);
    friend void foroosh(Date Today);
    friend void jostejo_melk();
    void virayesh_melk();
};

// id genrator for client
int melk_id_maker()
{
    fstream C("melkha.txt", ios::in);
    C.seekg(0, ios::end);
    int a = C.tellg();
    C.close();

    int b = sizeof(melk);
    int counter = 4000 + (a / b);
    return counter + 1;
}

// cin oprator for class melk
istream &operator>>(istream &in, melk &a)
{
    cout << " model melk ra entekhab konid : \n\t | 1-Apartman\n\t | 2-Villa\n\t | 3-Zamin \n\t   :";
    cin >> a.type;
    a.enable = 1;
    a.avaible = 1;
    if (a.type == 1)
    {
        cout << endl
             << "                Type : Aparteman";
        cout << endl
             << "             Metrazh : ";
        cin >> a.metrazh;
        cout << endl
             << "Aya baray Forosh ast : ";
        cin >> a.foroshi;
        cout << endl
             << "   Aya Asansor Darad : ";
        cin >> a.elevator;
        cout << endl
             << "    Tabghe Chand ast : ";
        cin >> a.tabghe;
        cout << endl
             << "         Tedad Otagh : ";
        cin >> a.tedad_otagh;
        cout << endl
             << "             Gheimat : ";
        cin >> a.price;
    }
    else if (a.type == 2)
    {
        cout << endl
             << "          Type : Villa";
        cout << endl
             << "       Metrazh : ";
        cin >> a.metrazh;
        cout << "Aya baray Forosh ast : ";
        cin >> a.foroshi;
        cout << "         Tedad Otagh : ";
        cin >> a.tedad_otagh;
        cout << "             Gheimat : ";
        cin >> a.price;
        a.tabghe = 0;
        a.elevator = 0;
    }
    else
    {
        cout << endl
             << "       Type : Zamin";
        cout << endl
             << "    Metrazh : ";
        cin >> a.metrazh;
        cout << endl
             << "    Gheimat : ";
        cin >> a.price;
        a.tabghe = 0;
        a.tedad_otagh = 0;
        a.foroshi = 1;
        a.elevator = 0;
    }
    return in;
}

// cout oprator for class melk
ostream &operator<<(ostream &f2, melk &a)
{
    cout << "\n+-----------------------------------------";
    cout << "\n                ID : " << a.melk_id;
    if (a.type == 1)
    {
        cout << endl
             << "              Type : Aparteman";
        cout << endl
             << "           Metrazh : ";
        cout << a.metrazh;
        cout << endl
             << "     Baraye Forosh : ";
        if(a.foroshi == 1){
        	cout<<"true";
		}else{
			cout<<"false";
		}
        cout << endl
             << "           Asansor : ";
        cout << (a.elevator == 1);
        cout << endl
             << "            Tabghe : ";
        cout << a.tabghe;
        cout << endl
             << "       Tedad Otagh : ";
        cout << a.tedad_otagh;
        cout << endl
             << "           Gheimat : ";
        cout << a.price;
    }
    else if (a.type == 2)
    {
        cout << endl
             << "            Type : Villa";
        cout << endl
             << "         Metrazh : ";
        cout << a.metrazh;
        cout << endl
             << "   Baraye Forosh : ";
        cout << (a.foroshi == 1);
        cout << endl
             << "     Tedad Otagh : ";
        cout << a.tedad_otagh;
        cout << endl
             << "         Gheimat : ";
        cout << a.price;
    }
    else
    {
        cout << endl
             << "              Type : Zamin";
        cout << endl
             << "           Metrazh : ";
        cout << a.metrazh;
        cout << endl
             << "           Gheimat : ";
        cout << a.price;
    }
    cout << "\n+-----------------------------------------" << endl;
    return f2;
}

// equal operator for melk
bool operator==(const melk &one, const melk &two)
{
    bool a = (one.type == two.type);
    bool b = (one.foroshi == two.foroshi);
    bool c = (one.elevator == two.elevator);
    bool d = (one.metrazh == two.metrazh);
    bool e = (one.tedad_otagh == two.tedad_otagh);
    bool h = (one.tabghe == two.tabghe);
    bool g = (one.price == two.price);
    if (((a && b) && ((c && d) && (e && h))) && g)
        return true;
    return false;
}

void ezafe_melk()
{
    melk foo;
    cin >> foo;
    foo.melk_id = melk_id_maker();
    fstream C;
    if (exists("melkha.txt"))
    {
        C.open("melkha.txt", ios::app);
    }
    else
    {
        C.open("melkha.txt", ios::out);
    }
    C.write((char *)&foo, sizeof(melk));
    C.close();
}

void hazf_melk()
{
    int id;
    melk temp;
    cout << " Code melk ra vared konid : ";
    cin >> id;
    int pos = (id - 4001) * sizeof(melk);
    fstream C("melkha.txt", ios::out | ios::in);
    C.seekg(pos, ios::beg);
    C.read((char *)&temp, sizeof(melk));

    if (temp.enable && temp.melk_id == id)
    {
        temp.enable = 0;
        C.seekg(pos, ios::beg);
        C.write((char *)&temp, sizeof(melk));
        cout << "\n [i] Melk " << id << " hazf shod. . . \n";
    }
    else
    {
        cout << "\n [!] Ghablan hazf shode.\n";
    }
    C.close();
}

void namayesh_melk()
{
    melk foo;

    ifstream Y("melkha.txt", ios::in);
    Y.read((char *)&foo, sizeof(melk));
    while (Y.eof() != true)
    {
        if (foo.enable && foo.avaible)
        {
            cout << foo;
            cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        }
        Y.read((char *)&foo, sizeof(melk));
    }
    Y.close();
}

void jostejo_melk()
{
    melk looking_for, temp;
    cout << "\n Etelat ra vared konid : \n";
    cin >> looking_for;
    fstream C("melkha.txt", ios::in);
    C.read((char *)&temp, sizeof(melk));
    while (!C.eof())
    {

        if ((temp.type == looking_for.type) && temp.enable)
        {

            if ((temp == looking_for) && temp.avaible)
            {
                cout << "Melk peida shod :";
                cout << temp;
                return;
            }
        }
        C.read((char *)&temp, sizeof(melk));
    }
    C.close();
    cout << "\n [!] peida nashod.";
}

void melk::virayesh_melk()
{
    int id;
    melk temp;
    cout << "\n Code melk ra vared konid : ";
    cin >> id;
    int pos = (id - 4001) * sizeof(melk);

    fstream C("melkha.txt", ios::out | ios::in);
    C.seekg(pos, ios::beg);
    C.read((char *)&temp, sizeof(melk));

    if (temp.enable && temp.avaible)
    {
        cout << endl
             << ">>>> etelat ghabli :\n";
        cout << temp;
        cout << endl
             << ">>>> Etelat jadid ra vard konid : \n";
        cin >> temp;
        C.seekg(pos, ios::beg);
        C.write((char *)&temp, sizeof(melk));
        cout << "\n[i] Melk " << id << " taghir yaft. . . \n";
    }
    else
    {
        cout << "\n [!] Ghablan hazf shode ast.\n";
    }
    C.close();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// client class
class moshtari
{
protected:
    char name[30], lastname[60], dadname[30];
    Date birthday;
    char phone_number[14];

public:
    int id;
    int enable;
    friend istream &operator>>(istream &x, moshtari &a);
    friend ostream &operator<<(ostream &x, moshtari a);
    void viraiesh_moshtari();
    friend void foroosh(Date Today);
};

// id genrator for client
int moshtari_id_maker()
{
    int b = sizeof(moshtari);
    int counter = 4000 + (filesize("moshtari.txt") / b);
    return counter + 1;
}

// cin moshtari
istream &operator>>(istream &x, moshtari &a)
{
    cout << "\n Enter name:";
    cin >> a.name;
    cout << "\n Enter lastname :";
    cin >> a.lastname;
    cout << "\n Enter father name :";
    cin >> a.dadname;
    cout << "\n Enter phone number : ";
    cin >> a.phone_number;
    cout << "\n Enter birthday :";
    cin >> a.birthday;
    a.enable = 1;
    return x;
}

// cout moshtari
ostream &operator<<(ostream &x, moshtari a)
{

    cout << endl;
    cout << "       Code : " << a.id << endl;
    cout << " First Name : " << a.name << endl;
    cout << "  Last Name : " << a.lastname << endl;
    cout << "Father Name : " << a.dadname << endl;
    cout << "   Birthday : " << a.birthday << endl;
    cout << endl;

    return x;
}

// client registering
void sabte_moshtari()
{
    moshtari foo;
    ofstream C;

    cin >> foo;
    foo.id = moshtari_id_maker();
	C.open("moshtari.txt",ios::app);
    C.write((char *)&foo, sizeof(moshtari));
    C.close();

    cout << "\n moshtari ba code : " << foo.id << endl;
}

// removing client
void hazf_moshtari()
{
    int id;
    moshtari temp;
    cout << "\n [-] CODE : ";
    cin >> id;

    fstream C("moshtari.txt", ios::out | ios::in);
    C.read((char *)&temp, sizeof(moshtari));
	while(!C.eof()){
    	if (temp.enable, temp.id == id )
    	{
	        temp.enable = 0;
	        int a = C.tellg();
	        int b = sizeof(temp);
	        int pos =  a- b;
	        C.seekg(pos , ios::beg);
	        C.write((char *)&temp, sizeof(temp));
	        C.close();
	        cout << "\n [i] moshtari " << id << " DELETED . . . \n";
	        return;
    	}
    	C.read((char *)&temp, sizeof(moshtari));
    }
    cout << "\n [!] ghablan hazf shode.\n";
    C.close();
}

// editing client
void moshtari::viraiesh_moshtari()
{
    int code_user;
    moshtari info,info2;
    cout << "\n [-] Code karbar : \n";
    cin >> code_user;

    int pos = (code_user - 4001) * sizeof(moshtari);

    fstream C("moshtari.txt", ios::out | ios::in);

    C.seekg(pos, ios::beg);
    C.read((char *)&info2, sizeof(moshtari));

    if (info.enable)
    {
        cout << ">>>> etelat moshtari " << code_user << " :\n"
             << info2;
        cout << "\n>>>> etelat jadid " << code_user << " :\n";
        cin >> info;
        info.id = info2.id;

        C.seekg(pos, ios::beg);
        C.write((char *)&info, sizeof(moshtari));

        cout << "\n [i] etelat moshtari " << code_user << " taghir kard. :) \n";
    }
    else
    {
        cout << "\n [!] moshtari vojod nadarad. :( \n";
    }
    C.close();
}

// searching client
void jostejo_moshtari()
{
    int id;
    moshtari foo;
    cout << "\n Code moshtari ra vared konid : ";
    cin >> id;

    fstream C("moshtari.txt", ios::in);
    C.read((char *)&foo, sizeof(foo));

    while(!C.eof()){
    	if (foo.enable && foo.id == id)
	    {
	        cout << foo;
	        C.close();
	        return;
	    }	
	    C.read((char *)&foo, sizeof(foo));
	}
    cout << "\n[!] hazf shode ast.\n";
    C.close();
}

// print all client
void namayesh_moshtari()
{
    moshtari foo;
    fstream Y;
    
    Y.open("moshtari.txt", ios::in);
    Y.read((char *)&foo, sizeof(foo));
    
    while (!Y.eof())
    {
        if (foo.enable == 1)
        {
            cout << foo;
            cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        }
        Y.read((char *)&foo, sizeof(foo));
    }
    Y.close();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// class report
class gozaresh
{
public:
    int id_kharidar;
    bool kharid;
    Date tarikh_kharid;
    Date tarikh_payan;
    melk property;

    void gozersh_bedon_limit_ejare();
    void gozersh_bedon_limit_kharid();
    void gozersh_ba_limit_kharid();
    void gozersh_ba_limit_ejare();
    friend void foroosh(Date Today);
};

// cout operator for gozaresh class
ostream &operator<<(ostream &x, gozaresh &a)
{
    cout << endl;
    cout << "+------------------------------------------" << endl;
    cout << "|        Kharidar : " << a.id_kharidar << endl;
    cout << "|   Tarikh kharid : " << a.tarikh_kharid << endl;
    if (a.kharid == 1){
    	cout << "| Kharid ya ejare : " <<  "kharid" << endl;
	}else{
		cout << "| Kharid ya ejare : " <<  "ejare" << endl;
	}
    cout << "|            Melk : " << a.property;
    cout << endl;
    return x;
}

// report all past order
void gozaresh::gozersh_bedon_limit_ejare()
{
    gozaresh report;

    fstream log("log.txt", ios::in);
    log.read((char *)&report, sizeof(gozaresh));
    while (!log.eof())
    {
        if (0 == report.kharid)
        {
            cout << report;
            cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        }
        log.read((char *)&report, sizeof(gozaresh));
    }
    log.close();
}

void gozaresh::gozersh_bedon_limit_kharid()
{
    gozaresh report;

    fstream log("log.txt", ios::in);
    log.read((char *)&report, sizeof(gozaresh));
    while (!log.eof())
    {
        if (1 == report.kharid)
        {
            cout << report;
            cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        }
        log.read((char *)&report, sizeof(gozaresh));
    }
    log.close();
}

// report past orders with time limit
void gozaresh::gozersh_ba_limit_kharid()
{
    int id;

    gozaresh thing;
    int id1 ,id2;

    cout << "\n AZ : ";
    cin >> id1;

    cout << "\n TA : ";
    cin >> id2;

    fstream fish("log.txt", ios::in);
    fish.read((char *)&thing, sizeof(gozaresh));
    cout << "kharid haye ghabli : " << endl;
    while (fish.eof() != true){

        if ((id1 <= thing.id_kharidar) && ((thing.id_kharidar <= id2) && (thing.kharid==1)))
            {
                cout << thing;
                cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            }

        fish.read((char *)&thing, sizeof(gozaresh));
    }

    fish.close();
}

void gozaresh::gozersh_ba_limit_ejare()
{
    int id;

    gozaresh thing;
    Date tarikh_shoro, tarikh_payan;

    cout << "\n AZ : ";
    cin >> tarikh_shoro;

    cout << "\n TA : ";
    cin >> tarikh_payan;

    fstream fish("log.txt", ios::in);
    fish.read((char *)&thing, sizeof(gozaresh));

    cout << "ejare haye ghabli : " << endl;
    while (fish.eof() != true){

        if ((tarikh_shoro <= thing.tarikh_kharid) && ((thing.tarikh_kharid <= tarikh_payan) && (thing.kharid == 0)))
        {
            cout << thing;
            cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        }

        fish.read((char *)&thing, sizeof(gozaresh));
    }

    fish.close();
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void foroosh(Date Today)
{
    int id, id_melk;
    bool choice;
    melk foo;
    gozaresh bar;
    moshtari csmtr;

    cout << "\nID Kharidar ra vared konid : ";
    cin >> id;
    namayesh_melk();
    cout << "\nID melk mored nazar ra vared konid : ";
    cin >> id_melk;

    int pos = (id_melk - 4001) * sizeof(melk);

    fstream properties("melkha.txt", ios::out | ios::in);
    properties.seekg(pos, ios::beg);
    properties.read((char *)&foo, sizeof(melk));
	
    if (foo.enable && foo.avaible)
    {
        cout << "[i] Etelat melk : \n"
             << foo;

        if (!foo.foroshi)
        {
            cout << endl
                 << "in ghardad ta che zamani etebar darad : ";
            cin >> bar.tarikh_payan;
        }else{
            bar.tarikh_payan = Today;
        }

        cout << "\n[i] Aya motmaen hastid (0 or 1): ";
        cin >> choice;

        if (choice==1)
        {

            // Write modified property to melk.txt
            foo.avaible = 0;
            properties.seekg(pos, ios::beg);
            properties.write((char *)&foo, sizeof(melk));
            properties.close();

            // Saving report for log
            bar.id_kharidar = id;
            bar.kharid = foo.foroshi;
            bar.tarikh_kharid = Today;
            bar.property = foo;

            // writing report in log.txt
            fstream log;
            if (exists("log.txt"))
            {
                log.open("log.txt", ios::app);
            }
            else
            {
                log.open("log.txt", ios::out);
            }
            log.write((char *)&bar, sizeof(gozaresh));
            log.close();

            cout << "Amaliat ba mofaghiat anjam shod, Melk kharidari shod !";
        }
        else
        {

            cout << "Amaliat motovaghef shod !";
        }
    }
    else
    {
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// menu about realstate and their function
void menu_melk()
{
    int choice;
    melk a;
    do
    {
        cout << "\n  * - AMALIAT MELK \n";
        cout << "\n  1 - SABTE MELK JADID";
        cout << "\n  2 - NAMAYESH HAMEY MELKHA";
        cout << "\n  3 - VIRAIESH MELK";
        cout << "\n  4 - JOSTEJO MELK";
        cout << "\n  5 - HAZF MELK";
        cout << "\n  0 - BACK";
        cout << "\n ***  Enter your choice:";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            system("CLS");
            cout << "\n  1 - SABTE MELK JADID";
            ezafe_melk();
        }
        break;
        case 2:
        {
            system("CLS");
            cout << "\n  2 - NAMAYESH HAMEY MELKHA";
            namayesh_melk();
        }
        break;
        case 3:
        {
            system("CLS");
            cout << "\n  3 - VIRAIESH MELK";
            a.virayesh_melk();
        }
        break;
        case 4:
        {
            system("CLS");
            cout << "\n  4 - JOSTEJO MELK";
            jostejo_melk();
        }
        break;
        case 5:
        {
            system("CLS");
            cout << "\n  5 - HAZF MELK";
            hazf_melk();
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

// menu about clinets and their function
void menu_moshtari()
{
    int choice;
    moshtari b;
    do
    {
        cout << "\n  * - AMALIAT MOSHTARI \n";
        cout << "\n  1 - SABTE MOSHTARI";
        cout << "\n  2 - NAMAYESH HAMEY MOSHTARIHA";
        cout << "\n  3 - VIRAYESH MOSHTARI";
        cout << "\n  4 - JOSTEJO MOSHTARI";
        cout << "\n  5 - HAZF MOSHTARI";
        cout << "\n  0 - BACK";
        cout << "\n ***  Enter your choice:";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            system("CLS");
            cout << "\n  5 - SABTE MOSHTARI" << endl;
            sabte_moshtari();
        }
        break;
        case 2:
        {
            system("CLS");
            cout << "\n  6 - NAMAYESH HAMEY MOSHTARIHA";
            namayesh_moshtari();
        }
        break;
        case 3:
        {
            system("CLS");
            cout << "\n  7 - VIRAYESH MOSHTARI";
            b.viraiesh_moshtari();
        }
        break;
        case 4:
        {
            system("CLS");
            cout << "\n  8 - JOSTEJO MOSHTARI";
            jostejo_moshtari();
        }
        break;
        case 5:
        {
            system("CLS");
            cout << "\n 10 - HAZF MOSHTARI";
            hazf_moshtari();
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

// menu about sell/rent and thier reports
void menu_gozaresh(Date TODAY)
{
    int choice;
    gozaresh c;
    do
    {
        cout << "\n * - AMALIAT KHARID VA GOZARESH HA\n";
        cout << "\n 1 - CHAP HAMEY GOZARESH HAYE KHARID";
        cout << "\n 2 - CHAP HAMEY GOZARESH HAYE EJARE";
        cout << "\n 3 - CHAP GOZARESH HAYE KHARID DAR MAHDODE ZAMANI MOSHKHAS";
        cout << "\n 4 - CHAP GOZARESH HAYE EJARE DAR MAHDODE ZAMANI MOSHKHAS";
        cout << "\n 5 - FOROOSH MELK";
        cout << "\n 0 - BACK";
        cout << "\n ***  Enter your choice:";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            system("CLS");
            cout << "\n 1 - CHAP HAMEY GOZARESH HAYE KHARID";
            c.gozersh_bedon_limit_kharid();
        }
        break;
        case 2:
        {
            system("CLS");
            cout << "\n 2 - CHAP HAMEY GOZARESH HAYE EJARE";
            c.gozersh_bedon_limit_ejare();
        }
        break;
        case 3:
        {
            system("CLS");
            cout << "\n 3 - CHAP GOZARESH HAYE KHARID DAR MAHDODE ZAMANI MOSHKHAS";
            c.gozersh_ba_limit_kharid();
        }
        break;
        case 4:
        {
            system("CLS");
            cout << "\n 4 - CHAP GOZARESH HAYE EJARE DAR MAHDODE ZAMANI MOSHKHAS";
            c.gozersh_ba_limit_ejare();
        }
        break;
        case 5:
        {
            system("CLS");
            cout << "\n 5 - FOROOSH MELK";
            foroosh(TODAY);
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

void main_menu()
{
    Date TODAY;
    int choice;
    cout << " TODAY IS :\n";
    cin >> TODAY;

    do
    {
        system("CLS");
        cout << "\n\n\t *** WELCOME TO 'FOUR' RealEstate *** \n\n";
        cout << "\n  1 - AMALIAT MELK";
        cout << "\n  2 - AMALIAT MOSHTARI";
        cout << "\n  3 - AMALIAT KHARID VA GOZARESH HA";
        cout << "\n  0 - EXIT";
        cout << "\n ***  Enter your choice:";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            system("CLS");
            menu_melk();
        }
        break;
        case 2:
        {
            system("CLS");
            menu_moshtari();
        }
        break;
        case 3:
        {
            system("CLS");
            menu_gozaresh(TODAY);
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

int main()
{
    main_menu();
    return 0;
}