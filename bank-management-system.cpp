//                   -- HEADER FILE --

#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;

//                  -- CLASS ACCOUNT--

class account
{
	int acno;
	char name[50];
	int deposit;
	char type;
public:
	void create_account();	        //this function is used to get data from user.
	void show_account() const;      //this function is used to show data on screen.
	void modify();	                //this function is used to add new data.
	void dep(int);           	//this function is used to accept amount and add to balance amount.
	void draw(int);         	//this function is used to accept amount and subtract from balance amount.
	void report() const;	        //this function is used to show data in tabular format.
	int retacno() const;	        //this function is used to return account number.
	int retdeposit() const;   	//this function is used to return balance amount.
	char rettype() const;    	//this function is used to return type of account.
};                        
                           //here class ends.

void account::create_account()
{
	cout<<"\nEnter The account No. : ";
	cin>>acno;
	cout<<"\n\nEnter The Name of account Holder : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter Type of account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
	cin>>deposit;
	cout<<"\n\n\nAccount Created..";
}

void account::show_account() const
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<deposit;
}


void account::modify()
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nModify Type of Account : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nModify Balance amount : ";
	cin>>deposit;
}

	
void account::dep(int x)
{
	deposit+=x;
}
	
void account::draw(int x)
{
	deposit-=x;
}
	
void account::report() const
{
	cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}
	
int account::retacno() const
{
	return acno;
}

int account::retdeposit() const
{
	return deposit;
}

char account::rettype() const
{
	return type;
}

//       	--Function Declaration--

void write_account();	                  //this function is used to write record in binary file.
void display_sp(int);	                  //this function is used to display account details given .by user
void modify_account(int);	          //this function is used to modify record of file.
void delete_account(int);	          //this function is used to delete record of file.
void display_all();		          //this function is used to display all account details.
void deposit_withdraw(int, int);          //this function is used to desposit/withdraw amount for given account.
void intro();	                          //this function is used to show introductory screen.


//    	        --PROGRAM MAIN FUNCTION--

int main()
{
	char ch;
	int num;
	intro();
	do
	{
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t 1. NEW ACCOUNT";
		cout<<"\n\n\t 2. DEPOSIT AMOUNT";
		cout<<"\n\n\t 3. WITHDRAW AMOUNT";
		cout<<"\n\n\t 4. BALANCE ENQUIRY";
		cout<<"\n\n\t 5. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t 6. CLOSE AN ACCOUNT";
		cout<<"\n\n\t 7. MODIFY AN ACCOUNT";
		cout<<"\n\n\t 8. EXIT";
		cout<<"\n\n\t Select Your Option (1-8) ";
		cin>>ch;
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4': 
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			delete_account(num);
			break;
		 case '7':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			modify_account(num);
			break;
		 case '8':
			cout<<"\n\n\t pleasure helping you....Thanks user for using bank's facility";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
    }while(ch!='8');
	return 0;
}


//    	          --FUNCTION USED TO WRITE INTO FILE--

void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}


//    	          --FUNCTION USED TO READ INTO FILE--

void display_sp(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";
    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
    inFile.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";
}


//    	        --FUNCTION USED TO MODIFY CONTENT INTO FILE--

void modify_account(int n)
{
	bool found=false;
	account ac;
	fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open...Press any Key.";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
		    File.write(reinterpret_cast<char *> (&ac), sizeof(account));
		    cout<<"\n\n\t Record Updated";
		    found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n No Record Found ";
}


//    	           --FUNCTION USED TO DELETE CONTENT FROM FILE--


void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open... Press any Key.";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
    inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tYour Record is Deleted ..";
}


//    	         --FUNCTION USED TO DISPLAY DEPOSIT LIST--

void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open...Press any Key.";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"____________________________________________________\n";
	cout<<"A/c no.-      NAME-           Type-  Balance\n";
	cout<<"____________________________________________________\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
	ac.report();
	}
	inFile.close();
}


//    	       --FUNCTION TO DEPOSIT AND WITHDROW AMOuNT--

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open...Press any Key.";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSIT AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amt;
				ac.dep(amt);
			}
		    if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount need to withdraw";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Insufficient balance";
				else
					ac.draw(amt);
		      }
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=true;
	       }
         }
    File.close();
	if(found==false)
		cout<<"\n\nNo Record Found ";
}


//                -- FUNCTION OF INTRODUCTION--

void intro()
{
	cout<<"\n\n\n\t BANK MANAGEMENT SYSTEM";
	cout<<"\n\n\n\nPROJECT DONE BY :- HRITIK MISHRA";
	cin.get();
}


//    			    --END--
