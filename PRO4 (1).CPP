// START OF PROGRAM DECLARATION 

//HEADER FILES USED 

#include<fstream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>

// creating class student 	  
class student
{
	int cardno;
	char name[100];
	int Class;
	char idate[100][20];
	int bissued;
	char rdate[100][20];
       
	public:
	void issue_card()	//function to accept details to issue card 
	{
		cout<<"Name of the student: "<<endl;
		gets(name);
		cout<<"Class: "<<endl;
		cin>>Class;
		cout<<"Card Number: "<<endl;
		cin>>cardno;
		bissued=0;
	}	//end of issue_card
	void show() 	// function to display the details 
	{
		cout<<"Name : "<<name<<endl;
		cout<<" Class : "<<Class<<endl;
		cout<<"Card Number : "<<cardno<<endl;
		cout<<"Number of books issued : "<<bissued<<endl;
	}	//end of show
	void modify() 	//function to modify student details
	{
		cout<<"Card Number : "<<cardno<<endl;
		cout<<"Student Name : ";
		gets(name);
		cout<<"\nStudent Class : "<<Class<<endl;
	}	//end of modify 
	int getcardno() 	// function to return card number 
	{
		return cardno;
	}
         	void b_issue()	//function to update date of issue of book   
	{
		
                		cout<<"\nEnter the date:";
                		gets(idate[bissued]);
               		 bissued++;
	}
	void b_ret()	//function to update date of return of book 
	{
		cout<<"\nEnter the date:";
                		gets(rdate[bissued]);
	}
};	//end of class 

//creating class book 
class book
{
	int bnum;
 	char author[20], name[20], description[50], genre[20], status[20];
 
 	public:
	 
 	void add()		//function to enter details of book 
 	{
  	 	cout<<"\nBook number: ";
  	 	cin>>bnum;
 	 	cout<<"\nName of book: ";
	 	gets(name);
	 	cout<<"\nAuthor: ";
	 	gets(author);
 	 	cout<<"\nDescription: ";
	 	gets(description);
	 	cout<<"\nGenre: ";
	 	cin>>genre;
 	 	cout<<"\nStatus: Issued or Available: ";
 	 	cin>>status;
	 }
	
 	void update()	//function to update book record 
  	{
  		cout<<"\nBook number: ";
  		cin>>bnum;
  		cout<<"\nName of book: ";
  		gets(name);
  		cout<<"\nAuthor:";
  		gets(author);
  		cout<<"\nDescription:";
  		gets(description);
  		cout<<"\nGenre: ";
  		cin>>genre;
  		cout<<"\nStatus: ";
  		cin>>status;
 	}

	 void display()	// function to display details of books 
 	{
		cout<<"\n Book number: \t"<<bnum;
  		cout<<"\n Name: \t"<< name;
  		cout<<"\n Description \t"<<description;
  		cout<<"\n Genre \t"<<genre;
  		cout<<"\n Status \t"<<status<<endl;
 	}

	 int getbnum()	//function to return book number 
	{
		  return bnum;
 	}

	 void up_status(char s[20])	//function to update status of book 
 	{
	 	 strcpy(status,s);
 	}
};	//end of class 

book b;     //creating object of class book 
student s;  //creating object of class student 
fstream fobj1, fobj2;    


void addbook()	// function to add book record in text file  
{
	char ch;
	fobj1.open("Book.txt", ios::out);

	do
	{
	       	cout<<" \nNEW BOOK RECORD";
                		cout<<"\nEnter the details :";
		b.add();
		fobj1.write((char*)&b,sizeof(book));
		cout<<"\nDo you want to enter again";
		cin>>ch;
	}	//end of do-while loop
	while( ch=='y' || ch=='Y' );  	//condition of do while loop 
	fobj1.close();
}	//end of addbook 


void addstudent()	//function to add student record in text file  
{
	char ch;
	fobj1.open("Student.txt", ios::out);

	do
	{
				cout<<" \nNEW STUDENT RECORD"<<endl;
				cout<<"\nEnter the details :"<<endl;
		s.issue_card();
		fobj1.write((char*)&s , sizeof(s));
		cout<<"\nDo you want to enter again ";
		cin>>ch;
	}	//end of do-while loop
	while ( ch=='y'||ch=='Y');	//condition for do-while loop
	fobj1.close();
}	//end of addstudent


void displaybooks()	//function to display details of book from file
{
 	int n,ctr,i,m;
        	fobj1.open("Book.txt" , ios::in );
	cout<<"\nBOOK DETAILS";
        	ctr=0;

       	 cout<<"\nEnter the book number:";
	 cin>>n;
	 
	 while ( !fobj1.eof())
	 { 
	             	fobj1.read((char*)&b,sizeof(b));
             		m=b.getbnum();
		if(n==m)
		{
			b.display();
			ctr=1;
			break;
		}	//end of if 
	 }	//end of while loop 
        
	 fobj1.close();
	 if(ctr==0)
	{
		cout<<"Book not found";
	}	//end of if	
}	//end of displaybooks


void displaystudents()		//function to display details of student from file 
{
	cout<<"\nSTUDENT DETAILS";
	int ctr=0,n,m;
	cout<<"\nEnter the card number of the student:";
	cin>>n;
	fobj1.open("Student.txt" , ios::in);
	while (!fobj1.eof())
	{
	            	fobj1.read((char*)&s , sizeof(s));
            		m=s.getcardno();
		if(m==n)
		{
			s.show();
			ctr=1;break;
		}	//end of if 
	}	//end of while loop 
	fobj1.close();
	if(ctr==0)
	{
		cout<<"\n Student not found";
	}
}	//end of displaystudents


void update_book()		//function to update book record in file  
{
	int n, ctr=0,m;
	long pos;
	cout<<"\nUPDATE BOOK RECORD";
	cout<<"\nEnter the book number: ";
	cin>>n;
	fobj1.open("book.txt" , ios::in || ios::out);
	while(!fobj1.eof())
	{
	             	fobj1.read((char*)&b , sizeof(book));
		pos=fobj1.tellg();
             		m=b.getbnum();
		if( m==n)
		{
			b.display();
			cout<<"\nEnter the new details of the book : ";
			b.update();
			fobj1.seekg(pos);
			fobj1.write((char*)&b,sizeof(book));
			cout<<"RECORD UPDATED";
			ctr=1;break;
		}	//end of if
	}	//end of while loop
	fobj1.close();
	if( ctr==0)
	{
		cout<<"\nBook not found";
	}	//end of if 
}	//end of update_book


void update_student()		//function to update student record in file
{
	int n, ctr=0,m;
	long pos;
	cout<<"\nUPDATE STUDENT RECORD";
	cout<<"\nEnter the card number of the student:";
	cin>>n;
	fobj1.open("Student.txt",ios::in|ios::out);
	while(!fobj1.eof())
	{
            		fobj1.read((char*)&s,sizeof(student));
	    	pos=fobj1.tellg();
            		m=s.getcardno();
		if (m==n)
		{
			s.show();
			cout<<"\nEnter the new details of the student:";
			s.modify();
			fobj1.seekg(pos);
			fobj1.write((char*)&s,sizeof(s));
			cout<<"RECORD UPDATED";
			ctr=1;break;
		}		//end of if 
	}	//end of while loop 
	fobj1.close();
	if(ctr==0)
	{
		cout<<"\nStudent not found";
	}	//end of  if 
}	//end of update_student


void issuebook()	//function to issue book 
{
 	int ctr, count, n, bno,m;
 	ctr=count=0;
 	long pos;
 	fobj1.open("Student.txt",ios::in|ios::out);
 	fobj2.open("Book.txt",ios::in|ios::out);

	cout<<"\nEnter the card number of the student:";
 	cin>>n;

 	while(!fobj1.eof())
 	{
  		pos=fobj1.tellg();
  		fobj1.read((char*)&s, sizeof(s));
  		m=s.getcardno();
  		if(m==n)
  		{
   			s.b_issue();
   			fobj1.seekg(pos);
   			fobj1.write((char*)&s, sizeof(s));
   			ctr=1;
   			cout<<"\nStudent record updated";
   			break;
  		}	//end of if 
 	}	//end of while loop 

	cout<<"\nEnter the book number:";
 	cin>>bno;
 
 	while(!fobj2.eof())
 	{
  		pos=fobj2.tellg();
  		fobj2.read((char*)&b, sizeof(b));
  		m=b.getbnum();
  		if(m==bno)
  		{
   			b.up_status("Issued");
   			fobj2.seekg(pos);
   			fobj2.write((char*)&b, sizeof(b));
   			count=1;
   			cout<<"\nBook record updated";
   			break;
  		}	//end of if 
 	}	//end of while loop 
 
 	if(ctr==0)
  	cout<<"\nStudent not found";
 	if(count==0)
  	cout<<"\nBook not found:";
 	fobj1.close();
 	fobj2.close();
}	//end of issuebook

void returnbook() //function to return book
{
 	int ctr, count, n, bno,m;
 	ctr=count=0;
 	long pos;
 	fobj1.open("Student.txt",ios::in|ios::out);
 	fobj2.open("Book.txt",ios::in|ios::out);

 	cout<<"\nEnter the card number of the student:";
 	cin>>n;
 	while(!fobj1.eof())
 	{
  		pos=fobj1.tellg();
  		fobj1.read((char*)&s, sizeof(s));
  		m=s.getcardno();
  		if(m==n)
  		{
   			s.b_ret();
   			fobj1.seekg(pos);
   			fobj1.write((char*)&s, sizeof(s));
   			ctr=1;
   			cout<<"\nStudent record updated";
   			break;
  		}	//end of if 
 	}	//end of while loop 

	cout<<"\nEnter the book number:";
 	cin>>bno;
 	while(!fobj2.eof())
 	{
  		pos=fobj2.tellg();
  		fobj2.read((char*)&b, sizeof(b));
  		m=b.getbnum();
  		if(m==bno)
  		{
   			b.up_status("Available");
   			fobj2.seekg(pos);
   			fobj2.write((char*)&b, sizeof(b));
   			count=1;
   			cout<<"\nBook record updated";
   			break;
  		}	//end of if 
 	}	//end of while 
 
 	if(ctr==0)
  	cout<<"Student not found";
 	if(count==0)
  	cout<<"Book not found:";
 	fobj1.close();
 	fobj2.close();	
}	//end of returnbook


void student_op()	//function to create student menu 
{
 	clrscr();
 	int ch;

 	cout<<"\n STUDENT MENU:"<<endl;
 	cout<<"1) Add Student:"<<endl;
 	cout<<"2) Display Student(s):"<<endl;
 	cout<<"3) Update Student Record:"<<endl;
 	cout<<"Now enter your choice:";
 	cin>>ch;

 	switch(ch)
 	{
  		case 1: addstudent();
          		break;
  		case 2: displaystudents();
          		break;
  		case 3: update_student();
          		break;
  		default: cout<<"Invalid Option";
 	}	//end of switch 
}	//end of student_op

void book_op()	//function to create book menu 
{
 	clrscr();
 	int ch;

 	cout<<"\n BOOK MENU:"<<endl;
 	cout<<"1) Add Book:"<<endl;
 	cout<<"2) Display Book(s):"<<endl;
 	cout<<"3) Update Book Record:"<<endl;
 	cout<<"Now enter your choice:";
 	cin>>ch;

 	switch(ch)
 	{
  		case 1: addbook();
          		break;
  		case 2: displaybooks();
          		break;
  		case 3: update_book();
          		break;
  		default: cout<<"Invalid Option";
 	}	//end of switch
}	//end of book_op


void homepage()	//function to display main menu 
{
 	int ch;
 cout<<"\n******************************************************************************";
 cout<<"\n                      SCHOOL LIBRARY MANAGEMENT SYSTEM                        ";
 cout<<"\n******************************************************************************";

 cout<<"\n\n\nWELCOME";

 cout<<"\n MAIN MENU:"<<endl;
 cout<<"1) Issue book:"<<endl;
 cout<<"2) Book Submission:"<<endl;
 cout<<"3) Student Menu:"<<endl;
 cout<<"4) Book Menu:"<<endl;
 cout<<"Now enter your choice:";
 cin>>ch;

 	switch(ch)
 	{
  		case 1: issuebook();
          		break;
  		case 2: returnbook();
          		break;
  		case 3: student_op();
          		break;
  		case 4: book_op();
          		break;
  		default: cout<<"Invalid Option";
 	} 	//end of switch 
}	//end of homepage
 

void main()	//MAIN FUNCTION 
{
 	clrscr();
 	char ch;

 	do
 	{
  		homepage();
  		cout<<"Do you wish to continue(Y/N)?";
  		cin>>ch;

 	}while(ch=='y'||ch=='Y');

}	//end of main


// END OF PROGRAM

 

   
   
  


