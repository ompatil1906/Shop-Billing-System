#include<bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<stdio.h>
#include<process.h>
#include<conio.h>
using namespace std;
#define el "\n"
#define sp " "

class item
{
	int total,no;
	char itmname[50][50];
	int Qty[3];
	int price[3];
	int vat[3];
	int tprice[3];
	public:
		void input();
		void output();
		void sumoutput();
		void listout();
		void non(int x)
		{
			no=100;
			no+=x;
		}
};


void item::input()
{
	system("CLS");
	cout<<"\nEnter the number of items: ";
	cin>>total;
	for(int i=0;i<total;i++)
	{
		cout<<"\nEnter the name of Item "<<i+1<<":";
		cin>>itmname[i];
		cout<<"\nEnter the quantity: ";
		cin>>Qty[i];
		cout<<"\nEnter price of item: ";
		cin>>price[i];
		tprice[i]=Qty[i]*price[i];
		if(tprice[i]<=100)
		vat[i]=tprice[i]+0.03*tprice[i];
		else
		vat[i]=tprice[i]+0.12*tprice[i];
	}
	output();
}


void item::output()
{
	system("CLS");
	cout<<"Bill No: "<<no<"\n";
	cout<<"-------------------------------------------------------------------------------------------\n";
	cout<<"S.no\tName of item\tQuantity\tPrice\tToatal Price\n";
	for(int i=0;i<total;i++)
	{
		cout<<i+1<<".\t"<<itmname[i]<<"\t\t"<<Qty[i]<<"\t"<<price[i]<<"\t"<<tprice[i]<<"\n";
	}
	sumoutput();
}


void item::sumoutput()
{
	int tot=0,sum=0,qty=0,cash=0;
	for(int i=0;i<total;i++)
	{
		sum+=tprice[i];
		tot+=vat[i];
		qty+=Qty[i];
	}
	cout<<"Total: ";
	cout<<"\n--------------------------------------------------------------------------------------------";
	cout<<"\n\tQuantity: "<<qty<<"\t\tSum: "<<sum<<"\tWith Taxes: "<<tot;
	cout<<"\n--------------------------------------------------------------------------------------------";
pay:
	cout<<"\n\n\t\t\t*****PAYMENT DETAILS*****\n";
	cout<<"\n\t\t\tTotal cash given: ";
	cin>>cash;
	if(cash>=tot)
	cout<<"\n\t\t\tTotal cash repaid: "<<cash-tot<<"\n";
	else
	{
		cout<<"\n\t\t\tCash given is less than total amount!!!";
		goto pay;
	}
	cout<<"\n\t\t\t Payment Successfull   ";
}


void item::listout()
{
	cout<<"\nBill No.: "<<this->no<<"\n";
	cout<<"----------------------------------------------------------------------------------------------------\n";
	for(int i=0;i<total;i++)
	cout<<"Name: "<<this->itmname[i]<<" Qty: "<<this->Qty[i]<<" Price: "<<this->tprice[i]<<"\n";
	cout<<"-----------------------------------------------------------------------------------------------------\n";
}


bool passwords() {
    int i = 0;
    char ch, st[21], ch1[21] = {"0000"};

    cout << "\n\n\t\tEnter Password : ";
    while (1) {
        ch = getch();
        if (ch == 13) { 
            st[i] = '\0';
            break;
        } else if (ch == 8 && i > 0) {  
            i--;
            cout << "\b \b";
        } else {
            cout << "*";
            st[i] = ch;
            i++;
        }
    }

    for (i = 0; st[i] == ch1[i] && st[i] != '\0' && ch1[i] != '\0'; i++);
    if (st[i] == '\0' && ch1[i] == '\0')
        return true; 
    else
        return false; 
}


int main()
{
	cout<<"\n\n\t\t\t------------------------------------------";
	cout<<"\n\t\t\t\tSHOP BILLING MANAGEMENT SYSTEM";
	cout<<"\n\t\t\t------------------------------------------";
	bool a=passwords();
	if(!a)
	{
		for(int i=0;i<2;i++)
		{
			cout<<"\nWrong password";
			cout<<"\nYou have "<<2-i<<" attempts left";
			if(passwords())
			goto last;
			if(i==1)
			{
				cout<<"\n\n\n\t\t\t All attempts failed........";
				cout<<"\n\n\t\t\t Sorry, but you can't login";
				exit(0);
			}
		}
	}
	last:
		cout<<"\n\n";
	start:
		system("PAUSE");
		system("CLS");
		int opt;
		cout<<"\n\n\t\t\t------------------------------------------";
		cout<<"\n\t\t\t\tSHOP BILLING MANAGEMENT SYSTEM";
		cout<<"\n\t\t\t------------------------------------------";
		cout<<"\n\n\t\t\tWhat do you want to do?";
		cout<<"\n\t\t\t1.\tTo enter a new entry";
		cout<<"\n\t\t\t2.\tTo view previous entries";
		cout<<"\n\t\t\t3.\tExit";
		cout<<"\n\n Choose your option: ";
		cin>>opt;
		if(opt==1)
		{
			item it;
			ofstream outf("file.bin",ios::app|ios::binary);
			outf.seekp(0,ios::end);
			int x=outf.tellp()/sizeof(item);
			it.non(x);
			it.input();
			outf.write(reinterpret_cast<char *>(&it),sizeof(item));
			outf.close();
			goto start;
		}
		else if(opt==2)
		{
			system("CLS");
			item it1;
			ifstream intf("file.bin",ios::in|ios::binary);
			intf.seekg(0,ios::beg);
			if(!intf)
			cout<<"\n\t\tFile not found";
			else
			{
				cout<<"\n\t*****Sales Details*****\n\n";
				while(intf.read(reinterpret_cast<char *>(&it1),sizeof(item)))
				it1.listout();
			}
			intf.close();
			goto start;	
		}
		else if(opt==3)
		exit(0);
		else
		{
			cout<<"\n\t\tEnter correct option";
			goto start;
		}
}
