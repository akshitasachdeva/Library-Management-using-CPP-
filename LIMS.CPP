#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<fstream.h>
#include<string.h>
#include<time.h>

int f=0;
int rec=0;

class book
{
		int book_id;
		char book_name[10];
		char author_name[10];
		char dept[4];
		int issue_status;
	public:
		void get_book()
		{
			cout<<"\n\n\n\t\t\tEnter book id\t\t:\t";
			cin>>book_id;
			cout<<"\n\n\t\t\tEnter book name\t\t:\t";
			cin>>book_name;
			cout<<"\n\n\t\t\tEnter dept name\t\t:\t";
			cin>>dept;
			cout<<"\n\n\t\t\tEnter author name\t:\t";
			cin>>author_name;
			issue_status=0;
		}
		void display_book()
		{
			cout<<"\n\n\n\n\n\n\t\t\tBook id\t\t:\t"<<book_id;
			cout<<"\n\n\t\t\tBook name\t:\t"<<book_name;
			cout<<"\n\n\t\t\tDept name\t\t:\t"<<dept;
			cout<<"\n\n\t\t\tAuthor name\t:\t"<<author_name;
			cout<<"\n\n\t\t\tIssue Status\t:\t"<<issue_status;
		}
		void modify_book()
		{
			cout<<"\n\n\n\t\t\tEnter new book id\t:\t";
			cin>>book_id;
			cout<<"\n\n\t\t\tEnter new book name\t:\t";
			cin>>book_name;
			cout<<"\n\n\t\t\tEnter new department name\t\t:\t";
			cin>>dept;
			cout<<"\n\n\t\t\tenter new  author name\t:\t";
			cin>>author_name;
			cout<<"\n\n\t\t\tEnter issue status\t:\t";
			cin>>issue_status;
		}
		int return_bid()
		{
			return book_id;
		}
		int return_issue()
		{
			return issue_status;
		}
		char * return_an()
		{
			return author_name;
		}
		char * return_dn()
		{
			return dept;
		}
};



class librarian
{
		int id;
		char name[20];
		char password[10];
		char ph_no[10];
		char address[20];
    public:
		char* return_psd()
		{
			return password;
		}
		int return_id()
		{
			return id;
		}
};



class reader
{
		int rid;
		char rname[20];
		char rpassword[10];
		char rph_no[10];
		char raddress[20];
    public:
		void get_record();
		char* return_psd()
		{
			 return rpassword;
		}
		int return_id()
		{
			return rid;
		}
};
void reader::get_record()
		{
			int i=0;
			cout<<"\n\n\n\t\t\tEnter your id\t:\t";
			cin>>rid;
			cout<<"\n\n\t\t\tEnter your name\t:\t";
			cin>>rname;
			cout<<"\n\n\t\t\tEnter your password(8 characters)\t:\t";
			while(i!=8)
			{
				rpassword[i]=getch();
				cout<<"*";
				i++;
			}
			rpassword[i]='\0';
			getch();
			cout<<"\n\n\n\t\t\tEnter your phone number\t:\t";
			cin>>rph_no;
			cout<<"\n\n\t\t\tEnter your address\t:\t";
			cin>>raddress;
		}



book b;


void add_book()
{
	fstream fp;
	char ch='y';
	if(f==0)
	{
	fp.open("book.dat",ios::out);
	f++;
	}
	else
	{
	fp.open("book.dat",ios::app);
	}
	do
	{
		clrscr();
		cout<<"\n\n\t\t-----------------Adding A Book-----------------";
		b.get_book();
		fp.write((char*)&b,sizeof(b));
		cout<<"\n\n\n\n\n\n\t\t\tBook Added..!!";
		cout<<"\n\n\n\n\n\n\t\tDo you wish to enter another record..??(y/n)\t:\t";
		cin>>ch;
	}
	while(ch=='y'||ch=='Y');
	fp.close();
}


void delete_book()
{
	int bid,cnt=0;
	ifstream ifs("book.dat",ios::in);
	ofstream ofs("temp.dat",ios::out);
	if(!ifs)
	cout<<"\n\n\n\n\n\t\t\tFile not found..!!";
	else
	{
		clrscr();
		cout<<"\n\n\t\t-----------------Deleting A Book-----------------";
		cout<<"\n\n\n\n\n\t\tEnter the book id of the book to be deleted\t:\t";
		cin>>bid;
		while(ifs.read((char*)&b,sizeof(b)))
		{
			if(b.return_bid()==bid)
			cnt++;
			if(b.return_bid()!=bid)
			{
				ofs.write((char*)&b,sizeof(b));
			}
		}
		if(cnt==0)
		cout<<"\n\n\n\n\n\t\t\t\t Record Not Found ";
		else
		cout<<"\n\n\n\n\n\t\t\t\tBook Deleted..!!";
		ofs.close();
		ifs.close();
	ifstream ifs("temp.dat",ios::in);
	ofstream ofs("book.dat",ios::out);
		while(ifs.read((char*)&b,sizeof(b)))
		{
			ofs.write((char*)&b,sizeof(b));
		}
		ofs.close();
		ifs.close();
		getch();
	}
}



void modify_book()
{       fstream fp;
	int bn;
	int found=0;
	clrscr();
	cout<<"\n\n\t\t-----------------Modifying A Record-----------------";
	cout<<"\n\n\n\n\t\tEnter the book id of the book to be modified\t:\t";
	cin>>bn;
	fp.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&b,sizeof(b)) && found==0)
	{
		if(b.return_bid()==bn)
		{
			found=1;
			b.modify_book();
			int pos=-1*sizeof(b);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&b,sizeof(b));
			cout<<"\n\n\n\n\n\t\t\t\tBook Modified..!!";
		}
	}

	fp.close();
	if(found==0)
		cout<<"\n\n\n\n\n\t\t\t\t Record Not Found ";
}


void view_all()
{
	int cnt=0;
	ifstream ifs("book.dat",ios::in);
	if(!ifs)
	cout<<"\n\n\n\n\n\t\t\t\tFile not found..!!";
	else
	{
		clrscr();
		cout<<"\n\n\t\t-----------------Dislaying all Books-----------------";
		while(ifs.read((char*)&b,sizeof(b))!=0)
		{
			b.display_book();
			cnt++;
		 }
		 if(cnt==0)
		 cout<<"\n\n\n\n\t\t\t\tEmpty Library..!!";
		getch();

	}
}


void search_book()
{
	int flag=0;
	int bno;
	ifstream ifs("book.dat",ios::in);
	if(!ifs)
	cout<<"\n\n\n\n\n\t\t\t\tFile not found..!!";
	else
	{
		clrscr();
		cout<<"\n\n\t\t------------------Searching A Book----------------";
		cout<<"\n\n\n\n\t\tEnter the book id of the book to be searched\t:\t";
		cin>>bno;
		while(ifs.read((char*)&b,sizeof(b)))
		{
			if(bno==b.return_bid())
			{
			flag++;
			cout<<"\n\n\n\n\n\t\t\t\tBook found..!!";
			b.display_book();
			getch();
			}
		}
	       if(flag==0)
	       {
	       cout<<"\n\n\n\n\n\t\t\t\tBook not found..!!";
	       getch();
	       }
	}
}

void search_author()
{
	int flag=0;
	char aname[10];
	ifstream ifs("book.dat",ios::in);
	if(!ifs)
	cout<<"\n\n\n\n\n\t\t\t\tFile not found..!!";
	else
	{
		clrscr();
		cout<<"\n\n\t\t------------------Search By Author----------------";
		cout<<"\n\n\n\n\t\tEnter the author name\t:\t";
		cin>>aname;
		while(ifs.read((char*)&b,sizeof(b)))
		{
			if(!strcmp(aname,b.return_an()))
			{
			flag++;
			cout<<"\n\n\n\n\n\t\t\t\tBook found..!!";
			b.display_book();
			getch();
			}
		}
	       if(flag==0)
	       {
	       cout<<"\n\n\n\n\n\t\t\t\tBook not found..!!";
	       getch();
	       }
	}
}
void search_dept()
{
	int flag=0;
	char dname[10];
	ifstream ifs("book.dat",ios::in);
	if(!ifs)
	cout<<"\n\n\n\n\n\t\t\t\tFile not found..!!";
	else
	{
		clrscr();
		cout<<"\n\n\t\t------------------Search By Stream----------------";
		cout<<"\n\n\n\n\t\tEnter the name of stream\t:\t";
		cin>>dname;
		while(ifs.read((char*)&b,sizeof(b)))
		{
			if(!strcmp(dname,b.return_dn()))
			{
			flag++;
			cout<<"\n\n\n\n\n\t\t\t\tBook found..!!";
			b.display_book();
			getch();
			}
		}
	       if(flag==0)
	       {
	       cout<<"\n\n\n\n\n\t\t\t\tBook not found..!!";
	       getch();
	       }
	}
}


void issue_book()
{
	int id;
	int r,flag=0;
	fstream ifs("book.dat",ios::in|ios::out);
	if(!ifs)
	cout<<"\n\n\n\n\n\t\t\t\tFile not found..!!";
	else
	{
		clrscr();
		cout<<"\n\n\t\t-----------------Issuing A Book-----------------";
		cout<<"\n\n\n\n\tEnter the id of book you wish to issue\t:\t";
		cin>>id;
		while(ifs.read((char*)&b,sizeof(b))&&flag==0)
		{
			if(id==b.return_bid())
			{
			flag++;
			if(b.return_issue()==0)
			{
				r=1;
				int loc=-1*sizeof(r);
				ifs.seekp(loc,ios::cur);
				ifs.write((char*)&r,sizeof(r));
				cout<<"\n\n\n\n\n\t\t\tBook Issued Successfully..!!";
				getch();
			}
			else
			{
				cout<<"\n\n\n\n\n\t\t\t\tBook Is Already Issued..";
				getch();
			}
			}
	       }
		       if(flag==0)
			 {
			 cout<<"\n\n\n\n\n\t\t\t\tBook Not Found";
			 getch();
			 }
	}
}


void deposit_book()
{
	fstream fp;
	int bid,r,days,fine=0;
	int flag=0;
	char c;
	clrscr();
	cout<<"\n\n\t\t-----------------Depositing A Book-----------------";
	cout<<"\n\n\n\n\n\t\tEnter the book id of the book to be deposited\t:\t";
	cin>>bid;
	fp.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&b,sizeof(b))&& flag==0)
		{
			   if(b.return_bid()==bid)
			{
				flag=1;
				if(b.return_issue()==1)
				{
				cout<<"\n\n\t\tEnter the no. of days you issued the book for:";
				cin>>days;
				if(days>14)
				{
				fine=(days-14)*5;
				cout<<"\n\n\t\tYour Fine\t:\t"<<fine;
				cout<<"\n\n\t\tHave you paid the fine..??[y/n]";
				cin>>c;
				if(c=='y')
				{
				r=0;
				int pos=-1*sizeof(r);
				fp.seekp(pos,ios::cur);
				fp.write((char*)&r,sizeof(r));
				cout<<"\n\n\n\n\n\t\t\t\t Book Deposited Successfully..!!";
				}
				else
				{
				cout<<"\n\n\t\tYour fine will be incremented by rs. 5/- per day..!!";
				cout<<"\n\n\t\tPay your fine and return the book..!!";
				}
				}
				else
				{
				r=0;
				int pos=-1*sizeof(r);
				fp.seekp(pos,ios::cur);
				fp.write((char*)&r,sizeof(r));
				cout<<"\n\n\n\n\n\t\t\t\t Book Deposited Successfully..!!";
				}
				}
				else
				cout<<"\n\n\n\n\n\t\t\t\t Book Has Alredy Been Deposited..!!";
				}
		}
		  if(flag==0)
		    cout<<"\n\n\n\n\n\t\t\t\tBook Not Found..!!";
			getch();
  fp.close();
  }

void lims_module();

reader r1;
void reader_registeration()
{
	fstream fp;
	char ch;
	if(rec==0)
	{
	fp.open("reader.dat",ios::out);
	rec++;
	}
	else
	fp.open("reader.dat",ios::app);
		do
		{
			clrscr();
			r1.get_record();
			fp.write((char*)&r1,sizeof(r1));
			cout<<"\n\n\t\tDo you wish to enter another record..??(y/n)\t:\t";
			cin>>ch;
		}
		while(ch=='y'||ch=='Y');
		fp.close();
}



void reader_module()
{
	 int ch;
	 clrscr();
	 do
	 {
	 clrscr();
		cout<<"\n\n\t\t====================READER VIEW==========================";
		cout<<"\n\n\n\n\n\n\t\t\t\t1.Search By Book Id";
		cout<<"\n\n\t\t\t\t2.Search By Author Name";
		cout<<"\n\n\t\t\t\t3.Search By Stream Name";
		cout<<"\n\n\t\t\t\t4.Issue A Book";
		cout<<"\n\n\t\t\t\t5.Deposit A Book";
		cout<<"\n\n\t\t\t\t6.Log Out";
		cout<<"\n\n\t\t\t\t7.Exit";
		cout<<"\n\n\t\t\t\tEnter your choice\t:\t";
		cin>>ch;

		switch(ch)
		{
			case 1:
			search_book();
			break;
			case 2:
			search_author();
			break;
			case 3:
			search_dept();
			break;
			case 4:
			issue_book();
			break;
			case 5:
			deposit_book();
			break;
			case 6:
			clrscr();
			gotoxy(25,20);
			cout<<"Thank You For Your Visit..!!";
			getch();
			clrscr();
			lims_module();
			break;
			case 7:
			exit(0);
			break;
		 }
	 }
while(ch!=7);
}



void reader_login()
{
	int id_r,flag=0,i=0;
	char psd_r[10];
	clrscr();
	cout<<"\n\n\n\n\n\t\t\tEnter the login id\t\t:\t";
	cin>>id_r;
	cout<<"\n\n\t\t\tEnter password(8 charcters)\t:\t";
	while(i!=8)
	{
		psd_r[i]=getch();
		cout<<"*";
		i++;
	}
	psd_r[i]='\0';
	getch();
	ifstream ifs("reader.dat",ios::in);
	if(!ifs)
	cout<<"\n\n\n\n\n\t\t\t\tFile not found..!!";
	else
	{
		 while(ifs.read((char*)&r1,sizeof(r1)))
		 {
			  if(id_r==r1.return_id())
			  {
				   flag++;
				   if(!strcmp(psd_r,r1.return_psd()))
				   {
					cout<<"\n\n\n\n\n\t\t\t\tYou Have Logged In Successfully..!!";
					getch();
					reader_module();
				   }
				   else
				   cout<<"\n\n\n\n\n\t\t\t\tIncorrect Password..!!";
				   getch();
				   clrscr();
			   }
		  }
		  if(flag==0)
		  cout<<"\n\n\n\n\n\t\t\t\tYou Are Not A Registered User";
		  getch();
	 }
}



librarian l;
void librarian_module()
{
	 int ch;
	 clrscr();
	 do
	 {
	   clrscr();
		cout<<"\n\n\t\t====================LIBRARIAN VIEW==========================";
		cout<<"\n\n\n\n\t\t\t\t1.Add A Book";
		cout<<"\n\n\t\t\t\t2.Delete A Book";
		cout<<"\n\n\t\t\t\t3.Modify A Book";
		cout<<"\n\n\t\t\t\t4.View All Books";
		cout<<"\n\n\t\t\t\t5.Log Out";
		cout<<"\n\n\t\t\t\t6.Exit";
		cout<<"\n\n\t\t\t\tEnter your choice\t:\t";
		cin>>ch;
	 switch(ch)
	 {
		case 1:
		add_book();
		break;
		case 2:
		delete_book();
		break;
		case 3:
		modify_book();
		break;
		case 4:
		view_all();
		break;
		case 5:
		clrscr();
		gotoxy(25,20);
		cout<<"Thank You For Your Visit..!!";
		getch();
		clrscr();
		lims_module();
		break;
		case 6:
		exit(0);
		break;
	 }
	 }
	 while(ch!=6);
}



void librarian_login()
{
	int i=0;
	char pass[10],uname[10],un[]="library",psd[]="password";
	clrscr();
	cout<<"\n\n\n\n\n\n\n\n\n\t\tEnter user id\t\t\t:\t";
	cin>>uname;
	cout<<"\n\n\t\tEnter password(8 characters)\t:\t";
	while(i!=8)
	{
		pass[i]=getch();
		cout<<"*";
		i++;
	}
	pass[i]='\0';
	getch();
	if(!strcmp(uname,un)&&!strcmp(pass,psd))
	{
		cout<<"\n\n\n\n\n\n\n\t\t\tYou Have Logged In Successfully..!!";
		getch();
		librarian_module();
	}
	else
		cout<<"\n\n\n\n\n\n\n\t\t\tIncorrect Username Or Password..!!";
		getch();
		librarian_login();
}
void lims_module()
{
	int ch;
	while(1)
	{
	clrscr();
	cout<<"\n\n\n\n\n    ====================WELCOME TO LIBRARY MANAGEMENT SYSTEM=================";
	cout<<"\n\n\n\n\t\t\t\t1.Librarian";
	cout<<"\n\n\t\t\t\t2.Existing user";
	cout<<"\n\n\t\t\t\t3.New user";
	cout<<"\n\n\t\t\t\t4.Exit";
	cout<<"\n\n\n\n\n\t\t\tEnter Your Choice\t:\t";
	cin>>ch;
	switch(ch)
	{
	case 1:
	librarian_login();
	break;
	case 2:
	reader_login();
	break;
	case 3:
	reader_registeration();
	break;
	case 4:
	exit(0);
	break;
	}
	}
}

void intro()
{
	clrscr();
	gotoxy(35,5);
	cout<<"CSE DEPARTMENT";
	gotoxy(25,8);
	cout<<"MANAV RACHNA COLLEGE OF ENGINEERING";
	gotoxy(35,18);
	cout<<"LIBRARY";
	gotoxy(34,21);
	cout<<"MANAGEMENT";
	gotoxy(35,24);
	cout<<"SYSTEM";
	gotoxy(35,34);
	cout<<"MADE BY:";
	gotoxy(32,36);
	cout<<"Akshita Sachdeva";
	gotoxy(32,38);
	cout<<"Akhil Dua";
	gotoxy(32,40);
	cout<<"Deepanshu Verma";
	getch();

}
void main()
{
	clrscr();
	intro();
	lims_module();
}






















