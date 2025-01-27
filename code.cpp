/*
*****************************
Author: MD. Naiem Islam Nahid
No copyright for this code.
Link: https://github.com/naiem-nahid/Mobile-Banking-System-with--Cplusplsu.git
*****************************
*/

#include<iostream>
#include<vector>
#include<fstream>
using namespace std;

int usedAC=0;

void showMenu( );
void CreateAC( );
void SendMoney( );
void SendMoney_nonBaki( );
void CashIn( );
void CashOut( );
void PayBill( );
void MyBaki( );
void ShowALL( );
void PIN_reset( );
void  Exit( );
long long MobileINPUT( );
int PIN_INPUT( );
int NumberSearch( long long );
 
class User
{
    string name,address,DOB;
    long long MobileNO, NID;
    int PIN;

public:

    void setUser( string nam, string adres, string dob, long long mobile, long long nid, int pin) ;
    bool checkPin( int pin);
    bool mobileCheck ( long long mob);
    void showUser( );
    bool resetCheck( string nam, string addr, string dob, long long nid);
    void fshow( );
    void set_newPIN( int pin)
    { PIN=pin; }

};


class TNX
{
    double amount;
    string TNXtype;
    long long MobileNO;

public:

    void setTnx( double amount, int n, long long mob);
    void getTnx( );
    void fgetTnx( );

};


class Account
{
    double Balance=0;
    User UserInfo;
    vector < TNX > TNXhistory;
    int tnxhis=0;

public:
    
    void set_UserInfo( string name, string address, string dob, long long mobile, long long nid, int pin);
    bool mobile_Check( long long mob );
    bool check_PIN( int pin );
    void showInfo( );
    bool check_Balance( double taka);
    void set_Balance( double balance );
    void show_Balance( );
    bool chek_Reset( string name, string address,string dob, long long mob);
    void set_new_PIN( int pin);
    void fshowInfo();
    void set_Tnx( double amount, int n, long long mob );
    void get_Tnx( );
    void fTNX( int j );
};


vector< Account > accounts;


int main()
{


    int choice;
    bool loop=true;

    while( loop )
    {
        showMenu( );
        cin>>choice;

        switch(choice)
        {
        case 1:
            CreateAC();
            break;

        case 2:
            SendMoney();
            break;

        case 3:
            SendMoney_nonBaki();
            break;

        case 4:
            CashIn();
            break;

        case 5:
            CashOut();
            break;

        case 6:
            PayBill();
            break;

        case 7:
            MyBaki();
            break;

        case 8:
            ShowALL();
            break;

        case 9:
            PIN_reset();
            break;

        case 0:
            Exit( );
            return 0;
            break;

        default:
            cout<<"You have entered a wrong Number Please Try Again\n";
            break;
        }
    }



    return 0;
}

void showMenu( )
{
    cout<<"\n------------------------------------------------------------------------------------------------------------";
    cout<<"\n\t\t\t\t\t\t BAKI Banking System";
    cout<<"\n------------------------------------------------------------------------------------------------------------";
    cout<<"\n\n\t\t WELCOME TO BAKI";

    cout<<"\n**************MENU**************\n";
    cout<<"\n1. Open a new Account";
    cout<<"\n2. Send Money";
    cout<<"\n3. Send Money to NON-Baki Number";
    cout<<"\n4. Cash IN";
    cout<<"\n5. Cash Out";
    cout<<"\n6. Pay Bill";
    cout<<"\n7. My BAKI";
    cout<<"\n8. Show Number of User";
    cout<<"\n9. PIN Reset";
    cout<<"\n0. Exit";
    cout<<"\n*********************************";
    cout<<"\n\t Please choose any option from 0-9:\t";
    cout<<"\nchoice: ";
}
void CreateAC( )
{
    string name, address, dob;
    long long Mobile, NID;
    int pin;

    cout<<"Pleas Enter Your name please"<<endl;
    cin.ignore();
    getline( cin,name);

    cout<<"Please Enter your address"<<endl;
    getline(cin,  address);

    cout<<"Please Enter your phone number"<<endl;
    Mobile=MobileINPUT(  );


    cout<<"Please Enter you NID number"<<endl;
    cin>>NID;

    cout<<"Enter Your date of birth"<<endl;
    cin.ignore();
    getline(cin, dob);
    pin= PIN_INPUT( );


    //setting new user && increasing the user number
    Account temp;
    temp.set_UserInfo( name, address, dob, Mobile, NID, pin );
    accounts.push_back(temp);
    usedAC++;

}


void SendMoney( )
{
    bool loop=true;
    int i,j, pin;
    long long mob,mob2;
    do
    {

        cout<<"Enter Your Mobile Number"<<endl;
        cin>>mob;
        i= NumberSearch( mob);

        if( i==-1)
        {
            cout<<"Your Entered Number is wrong"<<endl;
            cout<<"Try with another number"<<endl;

        }
        else
        {
            loop=false;
        }
    }
    while( loop );

    loop=true;

    do
    {

        cout<<"Enter your pin number"<<endl;
        cin>>pin;
        if( accounts[i].check_PIN(pin))
        {
            loop=false;
        }
        else
        {

            cout<<"Your Entered PIN is wrong"<<endl;
            cout<<"Please Try again"<<endl;
        }
    }
    while( loop );

    do
    {

        cout<<"Enter Receiver  Mobile Number"<<endl;
        cin>>mob2;
        j= NumberSearch( mob2);

        if( j==-1 )
        {
            cout<<"Your Entered Number is wrong"<<endl;
            cout<<"Try with another number"<<endl;

        }
        else if( j==i)
        {
            cout<<"You have entered your own mobile number"<<endl;
            cout<<"You can't send money to your own account"<<endl;
            cout<<"Try with another number"<<endl;
        }
        else
        {
            loop=false;
        }
    }
    while( loop );


    loop=true;
    double balance;
    do
    {
        cout<<"Enter the amount you want to send money"<<endl;
        cin>>balance;

        if( accounts[i].check_Balance(balance))
            loop=false;
        else
        {
            cout<<"Your balance is insufficient"<<endl;
            cout<<"Please try to enter amount that is less than or equal to your balance"<<endl;
        }
    }
    while( loop);

    accounts[i].set_Balance(-balance);
    accounts[j].set_Balance(balance);
    accounts[i].set_Tnx( -balance,1,mob2);
    accounts[j].set_Tnx( balance, 1, mob);
    cout<<"Your send money is successful"<<endl;


}


void SendMoney_nonBaki( )
{
    bool loop=true;
    int i,j, pin;
    long long mob,mob2;
    do
    {

        cout<<"Enter Your Mobile Number"<<endl;
        cin>>mob;
        i= NumberSearch( mob);

        if( i==-1)
        {
            cout<<"Your Entered Number is wrong"<<endl;
            cout<<"Try with another number"<<endl;

        }
        else
        {
            loop=false;
        }
    }
    while( loop );

    loop=true;

    do
    {

        cout<<"Enter your pin number"<<endl;
        cin>>pin;
        if( accounts[i].check_PIN(pin))
        {
            loop=false;
        }
        else
        {

            cout<<"Your Entered PIN is wrong"<<endl;
            cout<<"Please Try again"<<endl;
        }
    }
    while( loop );

    do
    {

        cout<<"Enter Receiver  Mobile Number"<<endl;
        cin>>mob2;
        j= NumberSearch( mob2);

        if( j!=-1)
        {
            cout<<"Your Entered Number is a \"BAKI\" number"<<endl;
            cout<<"Try with another number"<<endl;

        }
        else
        {
            loop=false;
        }
    }
    while( loop );


    loop=true;
    double balance;
    do
    {
        cout<<"Enter the amount you want to send money"<<endl;
        cin>>balance;

        if( accounts[i].check_Balance(balance))
            loop=false;
        else
        {
            cout<<"Your balance is insufficient"<<endl;
            cout<<"Please try to enter amount that is less than or equal to your balance"<<endl;
        }
    }
    while( loop);

    accounts[i].set_Balance(-balance);
    accounts[i].set_Tnx( -balance, 3, mob2 );
    cout<<"Your send money is successful"<<endl;

}
void CashIn( )
{
    bool loop=true;
    int i,j, pin;
    long long mob,mob2;
    double amount;
    do
    {

        cout<<"Enter Your Mobile Number"<<endl;
        cin>>mob;
        i= NumberSearch( mob);

        if( i==-1)
        {
            cout<<"Your Entered Number is wrong"<<endl;
            cout<<"Try with another number"<<endl;

        }
        else
        {
            loop=false;
        }
    }
    while( loop );

    loop=true;

    do
    {

        cout<<"Enter your pin number"<<endl;
        cin>>pin;
        if( accounts[i].check_PIN(pin))
        {
            loop=false;
        }
        else
        {

            cout<<"Your Entered PIN is wrong"<<endl;
            cout<<"Please Try again"<<endl;
        }
    }
    while(loop);
    cout<<"Enter the amount you want to Cash IN."<<endl;
    cin>>amount;


    loop=true;

    while(loop)
    {
    	int pin;
    	cout<<"Enter the manager PIN number to Cash IN"<<endl;
    	cin>>pin;
    	if( pin==54896)
    		loop=false;
    	else
    	{
    		cout<<"manager PIN number is wrong. Please try again"<<endl;
    		cout<<"Please Try Again"<<endl;
    	}
    }
    accounts[i].set_Balance( amount);
    accounts[i].set_Tnx( amount, 2, 1000000001);
    cout<<"Your Cash IN is successful."<<endl;

}
void CashOut()
{

    bool loop=true;
    int i,j, pin;
    long long mob,mob2;
    do
    {

        cout<<"Enter Your Mobile Number"<<endl;
        cin>>mob;
        i= NumberSearch( mob);

        if( i==-1)
        {
            cout<<"Your Entered Number is wrong"<<endl;
            cout<<"Try with another number"<<endl;

        }
        else
        {
            loop=false;
        }
    }
    while( loop );

    loop=true;

    do
    {

        cout<<"Enter your pin number"<<endl;
        cin>>pin;
        if( accounts[i].check_PIN(pin))
        {
            loop=false;
        }
        else
        {

            cout<<"Your Entered PIN is wrong"<<endl;
            cout<<"Please Try again"<<endl;
        }
    }
    while( loop );

    do
    {

        cout<<"Enter Agent  Mobile Number"<<endl;
        cin>>mob2;
        j= NumberSearch( mob2);

        if( j!=-1)
        {
            cout<<"Your Entered Number is a \"BAKI\" number"<<endl;
            cout<<"Try with another number"<<endl;

        }
        else
        {
            loop=false;
        }
    }
    while( loop );


    loop=true;
    double balance;
    do
    {
        cout<<"Enter the amount you want to Cash Out"<<endl;
        cin>>balance;

        if( accounts[i].check_Balance(balance))
            loop=false;
        else
        {
            cout<<"Your balance is insufficient"<<endl;
            cout<<"Please try to enter amount that is less than or equal to your balance"<<endl;
        }
    }
    while( loop);

    accounts[i].set_Balance(-balance);
    accounts[i].set_Tnx( -balance, 4, mob2 );
    cout<<"Your Cash Out is successful"<<endl;

}
void PayBill( )
{

bool loop=true;
    int i,j, pin;
    long long mob,mob2;
    do
    {

        cout<<"Enter Your Mobile Number"<<endl;
        cin>>mob;
        i= NumberSearch( mob);

        if( i==-1)
        {
            cout<<"Your Entered Number is wrong"<<endl;
            cout<<"Try with another number"<<endl;

        }
        else
        {
            loop=false;
        }
    }
    while( loop );

    loop=true;

    do
    {

        cout<<"Enter your pin number"<<endl;
        cin>>pin;
        if( accounts[i].check_PIN(pin))
        {
            loop=false;
        }
        else
        {

            cout<<"Your Entered PIN is wrong"<<endl;
            cout<<"Please Try again"<<endl;
        }
    }while(loop);

    cout<<" Which Bill Do you want to pay"<<endl;
    cout<<"1. Electricity"<<endl<<"2. Gash"<<endl<<"3. WASA"<<endl  ;
    int option;
    cin>>option;
    cout<<"Enter Your User NO to pay bill."<<endl;
    cin>>option;
    cout<<"Enter the month of payong bill( MM/YYYY)."<<endl;
    cin>>option;
    cout<<"Enter the amount of bill"<<endl;
    double amount;
    cin>>amount;
    loop=true;
   
    	if( accounts[i].check_Balance(amount))
    		{
    			accounts[i].set_Balance(-amount);
    			accounts[i].set_Tnx(-amount, 5, 10000001 );
    			cout<<"Your Pay Bill is successful"<<endl;
    		}
    	else
    	{
    		cout<<"You balance is insufficient"<<endl;
    		cout<<"Please Cash IN and try again later"<<endl;
    	}
    

}

void MyBaki( )
{

    bool loop=true;
    int i, pin,option;
    long long mob;


    do
    {
        cout<<"1. Check Balance"<<endl;
        cout<<"2. See User Information."<<endl;
        cout<<"3. Get Your TNX history."<<endl;
        cout<<"Select a option from 1-3"<<endl;
        cin>>option;
        if( option <0 && option>3)
        {
            cout<<"You entered a wrong number."<<endl;
            cout<<"Please try again."<<endl;
        }
        else
            loop=false;
    }
    while(loop);



    do
    {

        cout<<"Enter Your Mobile Number"<<endl;
        cin>>mob;
        i= NumberSearch( mob);

        if( i==-1)
        {
            cout<<"Your Entered Number is wrong"<<endl;
            cout<<"Try with another number"<<endl;

        }
        else
        {
            loop=false;
        }
    }
    while( loop );

    loop=true;

    do
    {

        cout<<"Enter your pin number"<<endl;
        cin>>pin;
        if( accounts[i].check_PIN(pin))
        {
            loop=false;
        }
        else
        {

            cout<<"Your Entered PIN is wrong"<<endl;
            cout<<"Please Try again"<<endl;
        }
    }
    while( loop );

    if( option==2)
        accounts[i].showInfo( );
    else if( option==1 )
        accounts[i].show_Balance();
    else
        accounts[i].get_Tnx( );
}
void ShowALL( )
{
    int option;
    cout<<"1. See the total number of user."<<endl;
    cout<<"2. See All the users information."<<endl;
    cout<<"3. See Transaction history in file."<<endl;
    cin>>option;
    if( option==1)
        cout<<"Total Users : "<<usedAC<<endl;
    else if( option==2)
    {
        ofstream out;
        out.open("UserList.txt",ios::app);
        for(int i=0; i<usedAC ; i++)
        {
            accounts[i].fshowInfo();
        }
    }
    else
    {

        for(int i=0; i<usedAC; i++)
            accounts[i].fTNX(i);
    }
}

void PIN_reset( )
{
    bool loop=true;
    int i,j, pin;
    long long mob,mob2;
    double amount;
    do
    {

        cout<<"Enter Your Mobile Number"<<endl;
        cin>>mob;
        i= NumberSearch( mob);

        if( i==-1)
        {
            cout<<"Your Entered Number is wrong"<<endl;
            cout<<"Try with another number"<<endl;

        }
        else
        {
            loop=false;
        }
    }
    while( loop );


    string name, address, dob;
    long long NID;
    cout<<"Enter Your Name."<<endl;
    cin.ignore();
    getline(cin, name);
    cout<<"Enter Your Address."<<endl;
    getline(cin, address);
    cout<<"Enter Your NID number."<<endl;
    cin>>NID;
    cout<<"Enter your birth date."<<endl;
    cin.ignore();
    getline(cin, dob);

    if( accounts[i].chek_Reset( name,address, dob, NID))
    {
        pin=PIN_INPUT();
        accounts[i].set_new_PIN(pin);
    }
    else
        cout<<"Your Provided Informations is wrong"<<endl;
}

void Exit( )
{
    cout<<"\nThank YOU for suing \"BAKI\" banking system."<<endl;
}

int PIN_INPUT( ) // function to take input of 4 digits pin number, and non- repetitive
{



    int a,b,c,d,pin;
    bool loop=true;

    while( loop )
    {
        loop=false;
        cout<<"Please Enter a four digit number to set your PIN"<<endl;
        cin>>pin;

        if( pin>9999 || pin<1000)
        {
            cout<<"You have not a entered a four digit pin"<<endl;
            cout<<"Please enter a for digit number to set pin"<<endl;
            loop=true;
            continue;
        }

        a=pin;
        d=a%10;
        a/=10;
        c=a%10;
        a/=10;
        b=a%10;
        a/=10;

        if( a==b || a==c || a==d || b==c || b==d || c==d )
        {
            cout<<"Please enter non-repeatative number"<<endl<<
                "Your pin should be contain different digit"<<endl;
            loop=true;
            continue ;
        }
    }

    return pin;
}

long long MobileINPUT( )  // function to take mobile number input checking that there is not match two number in list
{
    long long mob;
    bool loop=true;;

    while( loop)
    {
        loop=false;
        cin>>mob;

        for(int i=0; i<usedAC; i++)
            if( accounts[i].mobile_Check(mob))
            {
                loop=true;
                cout<<"Your Entered Number is already registered"<<endl;
                cout<<"Please Enter another number and try again"<<endl;
                cout<<"Enter Mobile NO"<<endl;
            }
    }

    return mob;

}

int NumberSearch( long long mob )
{
    for( int i=0; i< usedAC; i++)
    {
        if( accounts[i].mobile_Check( mob))
            return i;
    }
    return -1;
}



void Account::set_UserInfo( string name, string address, string dob, long long mobile, long long nid, int pin)
{
    UserInfo.setUser( name, address, dob, mobile, nid, pin) ;
}



bool Account::mobile_Check( long long mob)
{
    if( UserInfo.mobileCheck(mob))
        return true;
    else
        return false;
}

bool Account::check_PIN( int pin )
{
    if( UserInfo.checkPin(pin))
        return true;
    else
        return false;
}


void User::setUser( string nam, string adres, string dob, long long mobile, long long nid, int pin)
{
    name=nam;
    address=adres;
    DOB=dob;
    MobileNO=mobile;
    NID=nid;
    PIN=pin;
}


bool User::mobileCheck( long long mob )
{
    if( mob==MobileNO)
        return true;
    else
        return false;
}


bool User::checkPin( int pin)
{
    if( PIN==pin)
        return true;
    else
        return false;
}


void Account::showInfo( )
{
    UserInfo.showUser( );
}

bool Account::check_Balance( double taka)
{
    if( taka <=Balance && taka>=0)
        return true;
    else
        return false;
}


void Account::show_Balance( )
{
    cout<<"Your Balance is : "<<Balance<<endl;
}

void Account::set_Balance( double balance )
{
    Balance+=balance;
}


bool Account::chek_Reset( string name, string address,string dob, long long nid)
{
    if(UserInfo.resetCheck( name, address, dob, nid))
        return true;
    else
        return false;
}
bool User::resetCheck( string nam, string addr, string dob, long long nid)
{
    if( name!= nam)
        return false;
    if( addr!=address)
        return false;
    if( DOB!=dob)
        return false;
    if( NID!=nid)
        return false;
    return true;
}
void Account::set_new_PIN( int pin)
{
    UserInfo.set_newPIN(pin);
}

void Account::fshowInfo()
{
    UserInfo.fshow( );
}


void User::showUser( )
{
    cout<<"Name    : "<<name<<endl;
    cout<<"Address : "<<address<<endl;
    cout<<"Mobile  : "<<MobileNO<<endl;
    cout<<"NID     : "<<NID<<endl;
    cout<<"DOB     : "<<DOB<<endl;
}




void User::fshow()
{
    ofstream out;
    out.open("UserInformationList.txt",ios::app);
    out<<"Name    : "<<name<<endl;
    out<<"Address : "<<address<<endl;
    out<<"Mobile  : "<<MobileNO<<endl;
    out<<"NID     : "<<NID<<endl;
    out<<"DOB     : "<<DOB<<endl;
    out<<"*********************************************"<<endl<<endl;
}
void Account::set_Tnx(  double amount, int n, long long mob )
{
    TNX temptnx;
    temptnx.setTnx( amount, n, mob);
    TNXhistory.push_back(temptnx);
    tnxhis++;
}
void TNX::setTnx( double amount, int n, long long mob)
{

    this->amount= amount;
    if( n==1)
        TNXtype="Send Money";
    else if( n==2 )
        TNXtype="Cash IN";
    else if ( n==3 )
        TNXtype="Non-Baki Send Money";
    else if( n==4)
        TNXtype="Cash Out";
    else if( n==5)
    	TNXtype="Pay Bill";
    MobileNO=mob;

}

void Account::get_Tnx( )
{
    for( int i=0; i< tnxhis ; i++)
        TNXhistory[i].getTnx();
}

void Account::fTNX( int j)
{

    for( int i=0; i< tnxhis ; i++)
        TNXhistory[i].fgetTnx( );
}
void TNX::getTnx( )
{
    cout<<"Amount : "<<amount<<endl;
    cout<<"Tnx Type : "<<TNXtype<<endl;
    cout<<"Destination : "<<MobileNO<<endl;

    cout<<"*********************************\n"<<endl;
}

void TNX::fgetTnx( )
{
    ofstream outnx;
    outnx.open("TNX_History.txt",ios::app);

    outnx<<"Amount : "<<amount<<endl;
    outnx<<"Tnx Type : "<<TNXtype<<endl;
    outnx<<"Destination : "<<MobileNO<<endl;
    outnx<<"*************************************\n"<<endl;
}
