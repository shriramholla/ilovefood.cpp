#include<conio.h>
#include<fstream.h>
#include<iostream.h>
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<process.h>
void login_window();
void select_restaurant();
void create_restaurant();

fstream f1;

class account
{ public:
  char acc_name[20];
  char city[10];
  char address[50];
  char contact[11];
  char pword[20];

	 void input();
	 void output();
};

class restaurant
{ public:
 char res_name[20];
  char item_name[20];
  float price;
  float amount;
  restaurant()
  {
	 amount=0;
  }


 void input();
 };

 void bill();


  void restaurant::input()
	{  int n;
	  cout<<"Enter the name of the restaurant";
	  gets(res_name) ;

	  cout<<"Enter Item Name and Price\n";
		 gets(item_name);
		 cout<<"Enter the price"<<endl;
		 cin>>price;
	}



 void create_account()
 {

	  f1.open("acc.dat",ios::binary|ios::app);
	  account a;
		  a.input();
		  f1.write((char*)&a,sizeof(a));
		  cout<<"Account created"<<endl;
		  login_window();
		  f1.close();
  }


 void account::input()
{   clrscr();
	account a;
	fstream f1("acc.dat",ios::binary|ios::in);
	X:
	f1.seekg(0,ios::beg);
	cout<<"Enter the account name"<<endl;
	gets(acc_name);
	while(f1.read((char*)&a,sizeof(a)))
	 {
	  if(strcmpi(acc_name,a.acc_name)==0)
		{
		 cout<<"Username Taken, Enter Another one\n";
		 goto X;
		}
	  }

	cout<<"Enter your city (Max 10 Characters)"<<endl;
  gets(city);
  cout<<"Enter your address"<<endl;
  gets(address);
  cout<<"Enter the contact number"<<endl;
  gets(contact);
  cout<<"Enter the password"<<endl;
  gets(pword);
  f1.close();
  }

  void account::output()
	{
	clrscr();
	gotoxy(30,5);
	cout<<"Account Name: -"<<acc_name<<endl;
	gotoxy(30,6);
	cout<<"City: "<<city<<endl;
	gotoxy(30,7);
  cout<<"Address: "<<address<<endl;

	gotoxy(30,8);
   cout<<"Contact Number: "<<contact<<endl;
	}

 void login_window()
 {
 char user_check[20];
	  int ch;
	  int check=0,check1;
	  char pass_check[20];
		clrscr();

		do{
			A:
			cout<<"1.Create new account"<<endl;
			cout<<"2.Log in as admin"<<endl;
			cout<<"3.Order"<<endl;
			cout<<"4.Exit "<<endl;
			cin>>check1;

				switch(check1)
					{

					case 1:
							 create_account();
							 break;


					case 2:
							 cout<<"Enter the admin password"<<endl;
							 gets(pass_check);

							 if(strcmpi(pass_check,"admin")==0)
								create_restaurant();
							 else
								cout<<"Incorrect Password"<<endl;
							 goto A;
							 break;

					 case 3:
							  select_restaurant();
							  break;
					 case 4:
								exit(0);
								break;
				  }
			  }
		while(check1<=3);
		 }



	 void select_restaurant()
	 {
	 clrscr();
	 int n=1;
	 int i,qty;
	 char rest_check[20];
	 char items_check[20];
	 int chk=-1;
	 fstream f;
	 restaurant r;

	 char res_check[20];
	 c:
    clrscr();
	 chk=-1;
	 f.open("res.dat",ios::binary|ios::in);
	 cout<<"The restaurants available are"<<endl;
	  f.read((char*)&r,sizeof(r));
	  strcpy(res_check,r.res_name);
	  f.seekg(0,ios::beg);
	  cout<<n<<"."<<r.res_name<<"\n";
	 while(f.read((char*)&r,sizeof(r)))
	 {
		if(strcmpi(r.res_name,res_check)!=0)
		{ n++;
		  cout<<n<<"."<<r.res_name<<"\n";

		  strcpy(res_check,r.res_name);
		}
	 }
    n=1;

		 f.close();

		  start:
        //f.seekg(0,ios::beg);
		  cout<<"Enter the name of the respective restaurant"<<endl;
		  gets(rest_check);

		  cin.sync();
		  f.open("res.dat",ios::binary|ios::in);

			  while(f.read((char*)&r,sizeof(r)))
				  {
				 d:
				 if(strcmpi(r.res_name,rest_check)==0)
					{   chk++;
							 cout<<r.item_name<<endl;
							 cout<<r.price<<endl;
					 }



				 }
					 if(chk==-1)
				 {
				 cout<<"Name doesn't exist"<<endl;   f.close();
				 goto start;
				 }

		  f.close();

			  f.open("res.dat",ios::binary|ios::in);
			  f1.open("bill.dat",ios::binary|ios::app);
				int p=-1;

				cout<<"Enter the name of the item you want"<<endl;
				gets(items_check);

			  while(f.read((char*)&r,sizeof(r)))
				 {
					  if(strcmpi(r.item_name,items_check)==0)
						 {
						  cout<<"Enter the quantity of the item"<<endl;
						  cin>>qty;
						  r.amount=r.price*qty;
						 f1.write((char*)&r,sizeof(r));
						 cout<<"Item added to cart"<<endl;

						 p++;
						 }


				  }
				  f.close();
						 f1.close();
				  if(p==-1)
				  {
					cout<<"Item doesn't exist"<<endl;
					 goto d;
					}


				  cout<<"Enter 1. to order more items"<<endl;
				  cout<<"Enter 2. to proceed to billing"<<endl;
				  cin>>i;

					if(i==1)
					{
					 f.seekg(0,ios::beg);
					 goto c;
					}

					 else
					 {
						f.close();
						f1.close();
						bill();
					 }
				  }


         void line(){
				  cout<<"-------------------------------------------------------------------------------"<<endl;
				  }


		  void bill()
		  {
			char chk[30];
			fstream f("bill.dat",ios::in|ios::binary);
			restaurant r;

			 f1.open("acc.dat",ios::in|ios::binary);
			 account a;

			  float  total;
			  m:
			  cout<<"Enter your account name for delivery details"<<endl;
			  gets(chk);
			  int ab=-1;
		  while(f1.read((char*)&a,sizeof(a)))
		  {
				 if(strcmpi(a.acc_name,chk)==0)
				 { ab++;
					 G:
					 cout<<"Enter Password\n";
					 gets(chk);
					 if(strcmp(a.pword,chk)==0)
						a.output();
					  else
					  {cout<<"Re-enter Password\n";
							goto G;
					  }
				 }
		  }
				 if(ab==-1)
				 {
				 cout<<"Account doesn't exist"<<endl;
				 f1.seekg(0,ios::beg);
				 goto m;
				 }

				gotoxy(1,2);
			  line();

			  gotoxy(30,4);
			  cout<<"GRUBHUB ORDERS LIMITED";

			  gotoxy(20,9);
			  cout<<"The items you have ordered are given below";

			  gotoxy(1,10);
			  line();

			  gotoxy(5,11);
			  cout<<"No.";

			  gotoxy(10,11);
			  cout<<"Item";

			  gotoxy(30,11);
			  cout<<"Price";

			  gotoxy(40,11);
			  cout<<"Qty";

			  gotoxy(50,11);
			  cout<<"Amount";




			  int n=1;
			  int l=12;

			 while(f.read((char*)&r,sizeof(r)))
				{
				gotoxy(5,l);
				cout<<n<<".";

			  gotoxy(10,l);
			  cout<<r.item_name;

			  gotoxy(30,l);
			  cout<<r.price;

			  gotoxy(40,l);
			  cout<<r.amount/r.price;

			  gotoxy(50,l);
			  cout<<r.amount;


				total = total + r.amount;
				n++;
				l++;
				}

			gotoxy(1,l+1);
			line();


			gotoxy(38,l+2);
			cout<<"Total Amount:"<<total<<endl;


			gotoxy(1,l+3);
			line();

			gotoxy(20,l+4);
			cout<<"Your order has been placed and will reach you in 44 mins";

			gotoxy(30,l+5);
			cout<<"Thank you for ordering"<<endl;

			cout<<"press any key to exit"<<endl;

			getch();
			exit(0);
			f.close();
			remove("bill.dat");
		  }

	 void create_restaurant()
  {
	 restaurant r;
	 char ch='y';
	  int n;
	  fstream f("res.dat",ios::binary|ios::app);
	  cout<<"enter the restaurant details"<<endl;

	  B:
	 r.input();
	 f.write((char*)&r,sizeof(r));
	 cout<<"do you want to continue(y-yes,n-no)"<<endl;
	 cin>>ch;
	 if(ch=='y')
	 goto B;

	 else if(ch=='n')
	 { f.close();
	 login_window();
	 }

	 }


  int main()
	  {
		int i;
		login_window();
		return 0;
		}

