//Implementation of Bookshop Management System using C++
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<string>
#include<dos.h>
#include<conio.h>
#include<windows.h>
using namespace std;
void write(void);
void display(void);
void flgenerate(void);
class login{
	int attempt;
	public:
		login(){			//constructor declaration and definition
			attempt = 1;
		}
		void log();
		void mainmenu();
};
class bookshop{
	public:
		int bookID;
		char name[20];
		char auth[20];
		float price;
		int quant;
		void modbook();
		void sell();
		virtual void disp(){}		//virtual functions(polymorphism)
};
class data:public bookshop{
		friend void uprice(data, char*);		//friend function
		friend void uquant(data, char*);
	public:
		data(){}		//constructor
		data(char*);	//constructor overloading
		void input();
		void disp();
		void getsearch();
		void search(int);
		void search(char *);
		bool operator ==(char *);			//operator overloading
};
class bill{
	public:
		char name[20];
		char auth[20];
		float price;
		float sprice;
};
bool data::operator ==(char *nam){		//operator overloading definition
	if(strcmp(name,nam) == 0)
		return true;
	else
		return false;
}
template <class bill>		//function template
int Generate(bill b){
	system("CLS");
	cout<<"\n\t\t\t\t\t\tABC BOOKSHOP";
	cout<<"\n--------------------------------------------------------------------------------------------------------------------";
	cout<<"\n\t\t\t\t\t\t    BILL";
	cout<<"\n--------------------------------------------------------------------------------------------------------------------";
	cout<<"\n\t\t\tBook name: "<<b.name;
	cout<<"\n\t\t\tBook author: "<<b.auth;
	cout<<"\n\t\t\tTotal amount: "<<b.sprice;
	cout<<"\n--------------------------------------------------------------------------------------------------------------------";
	cout<<"\n\n\n\t\t\t\t\t\t\t\t\t\t\t\tCustomer signature";
	cout<<"\n\t\t\tThank you....!!!!";
	cout<<"\n\t\t\tVisit Again";
	cout<<"\n\t\t\tHappy Reading";
	cout<<"\n\t\t\tContact: 0123456789";
	cout<<"\n\t\t\tEmail: abc.bookshop@gmail.com";
	getch();
	return 0;
}
data::data(char *nam){			//constructor definition
	ifstream ifp; int found = 0;
	ofstream ofp; data c;
	ifp.open("Book", ios::binary);
	ofp.open("Book1", ios::binary);
	while(ifp.read((char *)&c, sizeof(c)) != NULL){
		if(strcmp(c.name,nam) != 0)
			ofp.write((char *)&c, sizeof(c));
		else
			found = 1;
	}
	ofp.close(); ifp.close();
	if(found == 0)
		cout<<"\nRecord not deleted";
	else
		cout<<"\nRecord deleted";
	remove("Book");
	rename("Book1","Book");
}
void login::log(){
	int i,f;
	l: system("CLS");
	cout<<"\n\n";
	cout<<"\n********************************************************************************************************************";
	cout<<"\n\n\n\t\t\t\t\t\tBOOKSHOP MANAGEMENT SYSTEM";
	cout<<"\n\n\n********************************************************************************************************************";
	char pass[11] = {"admin@1234"}, pass1[11], ch;
	if(attempt <= 3){
		cout<<"\n\n\t\tEnter the password: ";
		ch = getch();
		i = 0;
		while (ch!=13)
		{
			if(ch!=8 && ch!=13){
			putch('*');
			pass1[i]=ch;
			i++;
			ch=getch();
			}
		}
		pass1[i] = '\0';
		if(strcmp(pass1,pass) == 0)
		{
			cout<<"\n\n\t\tCorrect password...";
			cout<<"\n\n\t\tLoading database";
			for(f = 0; f < 3; f++){
				cout<<"."; Sleep(500);
			}
			cout<<"\n\n\t\tLoading mainmenu";
			for(f = 0; f < 5; f++){
				cout<<"."; Sleep(500);
			}
			mainmenu();
		}
		else{
			attempt++;
			cout<<"\nInvalid password";
			goto l;
		}
	}
	if(attempt == 4){
		cout<<"\nYour limit has ended";
		cout<<"\nThank you for trying";
	}
	getch();
}
void login::mainmenu(){
	bookshop b;
	data da;
	int ch;
	char d, nam[20];
	system("CLS");
	cout<<"\n MENU \n 1. Add book \n 2. Modify the database \n 3. Sell book \n 4. Generate bill \n 5. Display database \n 6. Search a book \n 7. Delete from database \n 8. Exit";
	cout<<"\n Enter your choice...";
	cin>>ch;
	switch(ch){
		case 1:
			write();
			break;
		case 2:
			b.modbook();
			break;
		case 3:
			b.sell();
			break;
		case 4:
			flgenerate();
			system("CLS");
			break;
		case 5:
			display();
						break;
        case 6:
            da.getsearch();
            break;
		case 7:{
			cout<<"\nEnter name: "; 
			cin>>nam;
			data a(nam);
			break;
		}
		case 8:
			exit(0);
			break;
		default:
			cout<<"\nInvalid option, Try again";
			Sleep(1000);
			mainmenu();
			break;
	}
	cout<<"\n Do you want to perform more operations?";
	cin>>d;
	if(d == 'y')
		mainmenu();
	else
		exit(0);
	getch();
}
void write(){		//file input
	ofstream fp;
	fp.open("Book", ios::binary | ios::app);
	data b;
	b.input();
	fp.write((char *)&b, sizeof(b));
	fp.close();
}
void display(){		//file output
	bookshop *b;
	data B;
	b = &B;	
	b->disp();
}
void bookshop::modbook(){
	int c;
	char nam[20];
	data d;
	cout<<"\nEnter book: "; cin>>nam;
	cout<<"\nWhat do you want to change?";
	cout<<"\n1. Book price \n2. Book quantity";
	cout<<"\nEnter your choice: ";cin>>c;
	switch(c){
		case 1:
			uprice(d, nam);
			break;
		case 2:
			uquant(d, nam);
			break;
		default:
			cout<<"\nInvalid option.";
			break;
	}
}
void uprice(data d, char *nam){
	fstream fp; int found = 0;
	fp.open("Book", ios::binary | ios::in | ios::out);
	while(fp.read((char *)&d, sizeof(d)) != NULL){
		if(d == nam){			//calling operator overloading
			double loc=(-1*sizeof(d));
			fp.seekp(loc, ios::cur);
			cout<<"\nEnter new price: "; cin>>d.price;
			fp.write((char *)&d, sizeof(d));
			found = 1;
			break;
		}
	}
	fp.close();
	if(found == 0)
		cout<<"\nRecord not updated";
	else{
		cout<<"\nRecord updated";
		cout<<"\nName: "<<d.name<<"\nAuthor: "<<d.auth<<"\nPrice: "<<d.price<<"\nQuantity: "<<d.quant;
	}
}
void uquant(data d, char *nam){
	fstream fp; int found = 0;
	fp.open("Book", ios::binary | ios::in | ios::out);
	while(fp.read((char *)&d, sizeof(d)) != NULL){
		if(d == nam){
			double loc=(-1*sizeof(d));
			fp.seekp(loc, ios::cur);
			cout<<"\nEnter new quantity: "; cin>>d.quant;
			fp.write((char *)&d, sizeof(d));
			found = 1;
			break;
		}
	}
	fp.close();
	if(found == 0)
		cout<<"\nRecord not updated";
	else{
		cout<<"\nRecord updated";
		cout<<"\nName: "<<d.name<<"\nAuthor: "<<d.auth<<"\nPrice: "<<d.price<<"\nQuantity: "<<d.quant;
	}
}
void bookshop::sell(){
	fstream fp;	int n, found = 0;
	data d;		char nam[20];
	float sprice;	bill b;
	fp.open("Book", ios::binary | ios::in | ios::out);
	cout<<"\nEnter book name to sell: ";		cin>>nam;
	cout<<"\nEnter quantity of book: ";		cin>>n;
	while(fp.read((char *)&d, sizeof(d)) != NULL){
		if(d == nam){
			double loc = (-1 * sizeof(d));
			fp.seekp(loc, ios::cur);
			d.quant = d.quant - n;
			b.sprice = d.price * n;
			fp.write((char *)&d, sizeof(d));
			found = 1;
			break;
		}
	}
	fp.close();
	if(found == 0)
		cout<<"\nBook not sold";
	else{
		cout<<"\nBook sold";
		Sleep(1000);
		strcpy(b.name, d.name);
		strcpy(b.auth, d.auth);
		Generate(b);		//calling function template
		system("CLS");
	}
}
void data::disp(){
	ifstream f;
	f.open("Book", ios::binary);
	data B;
	while(f.read((char *)&B, sizeof(B)) != NULL){
    	cout<<"\n\t"<<B.bookID<<"\t"<<B.name<<"\t"<<B.auth<<"\t"<<B.price<<"\t"<<B.quant;
	}
	f.close();
}
void data::getsearch(){
	int e, ID;
	char bname[20];
	system("CLS");
		cout<<"\n How to search: \n 1. By book ID \n 2. By book name";
		cin>>e;
		switch(e){
			case 1:
			    cout<<"\nEnter the book ID to search: ";
			    cin>>ID;
                search(ID);
				break;
			case 2:
			    cout<<"\nEnter the book name to search: ";
			    cin>>bname;
				search(bname);
				break;
			default:
				cout<<"\n Invalid option";
				break;
    }
}
void data::search(int ID){
    data d;
    int found = 0;
    ifstream f;
    system("CLS");
    f.open("Book", ios::binary);
    while(f.read((char *)&d, sizeof(d)) != NULL){
        if(d.bookID == ID){
            found = 1;
            break;
        }
    }
    if(found == 0)
        cout<<"\nThe record not found";
    else{
        cout<<"\nRecord found";
        cout<<"\nDetails are: ";
        cout<<"\nName: "<<d.name<<"\nAuthor: "<<d.auth<<"\nPrice: "<<d.price<<"\nQuantity: "<<d.quant;
    }
}
void data::search(char *bname){
	data b;
	ifstream f;
	int found = 0;
	system("CLS");
	f.open("Book", ios::binary);
	while(f.read((char *)&b, sizeof(b)) != NULL){
		if(strcmp(b.name,bname) == 0){
			found = 1;
			break;
		}
	}
	if(found == 0)
		cout<<"\nRecord not found";
	else{
		cout<<"\nRecord found";
		cout<<"\nDetails are: ";
		cout<<"\nName: "<<b.name<<"\nAuthor: "<<b.auth<<"\nPrice: "<<b.price<<"\nQuantity: "<<b.quant;
	}
}
void flgenerate(){
	ifstream fp;
	bill b;	data d;
	int found = 0;
	char nam[20];
	cout<<"\nEnter book name: ";	cin>>nam;
	cout<<"\nEnter total price: ";	cin>>b.sprice;
	fp.open("Book", ios::binary);
	while(fp.read((char *)&d, sizeof(d)) != NULL){
		if(d == nam){
			found = 1;
			break;
		}
	}
	fp.close();
	if(found == 0)
		cout<<"\nBill not made";
	else{
		strcpy(b.name, d.name);
		strcpy(b.auth, d.auth);
		Generate(b);
	}
}
void data::input(){
	a:	cout<<"\n Enter book ID: ";
		cin>>bookID;
		try{						//exception handling
			if(bookID < 1)
				throw bookID;
		}
		catch(int bookID){
			cout<<"\nInvalid ID, try again";
			goto a;
		}
		cout<<"\n Enter book name: ";
		cin>>name;
		cout<<"\n Enter book author: ";
		cin>>auth;
		cout<<"\n Enter book price: ";
		cin>>price;
		cout<<"\n Enter quantity of this book: ";
		cin>>quant;
}
int main(){
	login l;
	l.log();
	return 0;
}
