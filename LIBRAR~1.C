#include<stdio.h>
#include<conio.h>                   //contains delay(),getch(),gotoxy(),etc.
#include<stdlib.h>		    // contains exit();
#include<string.h>
#include<ctype.h>                   //contains toupper(), tolower(),etc
#include<dos.h>                     //contains _dos_getdate
#include<time.h>

#define RETURNTIME 15

//list of function prototype
void returnfunc(void);
void mainmenu(void);
void addbooks(void);
void deletebooks(void);
void editbooks(void);
void searchbooks(void);
void issuebooks(void);
void viewbooks(void);
void closeapplication(void);
int  getdata();
int  checkid(int);
int t(void);
void Password();
void issuerecord();
void addwish(void);
void deletewish(void);
void view_wish(void);
void wishlist();
int checksl(int);
//global files
FILE *fp,*ft,*fs;

//list of global variable
char catagories[30][30]={"Act-Adv","(A)bio","Fa-Fict","Non-Fict","Tech"};
int s;
char findbook;
char password[10]={"nmit"};


struct meroDate
{
    int mm,dd,yy;
};
struct books
{
    int id;
    char stname[20];
    char name[20];
    char Author[20];
    long contact;
    int count;
    char *cat;
    struct meroDate issued;
    struct meroDate duedate;
};
struct books a;
struct wish
{ char memname[20];
  char bookname[20][20];
  int serialno;	
};
struct wish b;
int main()

{
   Password();
   getch();
   return 0;

}
void mainmenu()
{      int i;
    clrscr();
	gotoxy(20,3);
	printf("MAIN MENU");
	gotoxy(20,5);
	printf("1. Add Books");
	gotoxy(20,7);
	printf("2. Delete books");
	gotoxy(20,9);
	printf("3. Search Books");
	gotoxy(20,11);
	printf("4. Issue Books");
	gotoxy(20,13);
	printf("5. View Book list");
	gotoxy(20,15);
	printf("6. Edit Book's Record");
	gotoxy(20,17);
	printf("7. Wishlist");
	gotoxy(20,19);
	printf("8. Close Application");
	gotoxy(20,21);
	t();
	gotoxy(20,23);
	printf("Enter your choice:");
	switch(getch())
	{
		case '1':
		addbooks();
		break;
	case '2':
		deletebooks();
		break;
		case '3':
		searchbooks();
	    break;
	case '4':
		issuebooks();
	    break;
	    case '5':
		viewbooks();
		break;
	    case '6':
		editbooks();
		break;
	    case '7': 
		clrscr();
		wishlist();
		  break;
	    case '8':
	    {
		clrscr();
		gotoxy(16,3);
		printf("Programmers....");
		gotoxy(16,4);
		printf("1. Spurthi L. \t\t (1NT14CS158)");
		gotoxy(16,7);
		printf("2. Sindhu R. Moktali\t(1NT14CS154)");
		gotoxy(16,10);
		printf("3. Suraksha J. \t(1NT14CS166)");
		gotoxy(16,13);
		printf("4. R. Prajwal  \t(Diploma-15CS19)");
		gotoxy(10,17);
		printf("With the unexplainable help of Mrs.Meenakshi");
		flushall();
		delay(10000);
		exit(0);
	    }
	    default:
		{
		gotoxy(10,23);
		printf("\aWrong Entry!!Please re-entered correct option");
		if(getch())
		mainmenu();
		}

    }
}
void addbooks(void)    //funtion that add books
{       int i;
	clrscr();
	gotoxy(20,7);
	printf("1.Action-Adventure");
	gotoxy(20,9);
	printf("2.(A)Biography");
	gotoxy(20,11);
	printf("3.Fantasy-Fiction");
	gotoxy(20,13);
	printf("4.Non-Fiction");
	gotoxy(20,15);
	printf("5.Technical");
	gotoxy(20,19);
	printf("6.Go to main menu");
	gotoxy(20,22);
	printf("Enter your choice:");
	scanf("%d",&s);
	if(s==6)

	mainmenu() ;
	clrscr();
	fp=fopen("Shadow.dat","ab+");
	if(getdata()==1)
	{
	a.cat=catagories[s-1];
	fseek(fp,0,SEEK_END);
	fwrite(&a,sizeof(a),1,fp);
	fclose(fp);
	gotoxy(21,14);
	printf("The record is sucessfully saved");
	gotoxy(21,15);
	printf("Save any more?(Y / N):");
	if(getch()=='n')
	    mainmenu();
	else
	    clrscr();
	    addbooks();
	}
}

void deletebooks()    //function that delete items from file fp
{   int d;
    char another='y';
    clrscr();
    while(another=='y')  //infinite loop
    {
	clrscr();
	gotoxy(10,5);
	printf("Enter the Book ID to  delete:");
	scanf("%d",&d);
	fp=fopen("Shadow.dat","rb+");
	rewind(fp);
	while(fread(&a,sizeof(a),1,fp)==1)
	{
	    if(a.id==d)
	    {
		gotoxy(10,7);
		printf("The book record is available");
		gotoxy(10,8);
		printf("Book name is %s",a.name);
		findbook='t';
	    }
	}
	if(findbook!='t')
	{
	    gotoxy(10,10);
	    printf("No record is found modify the search");
	    if(getch())
	    mainmenu();
	}
	if(findbook=='t' )
	{
	    gotoxy(10,9);
	    printf("Do you want to delete it?(Y/N):");
	    if(getch()=='y')
	    {
		ft=fopen("test.dat","wb+");  //temporary file for delete
		rewind(fp);
		while(fread(&a,sizeof(a),1,fp)==1)
		{
		    if(a.id!=d)
		    {
			fseek(ft,0,SEEK_CUR);
			fwrite(&a,sizeof(a),1,ft); //write all in tempory file except that
		    }                              //we want to delete
		}
		fclose(ft);
		fclose(fp);
		remove("Shadow.dat");
		rename("test.dat","Shadow.dat"); //copy all item from temporary file to fp except that
		fp=fopen("Shadow.dat","rb+");    //we want to delete
		if(findbook=='t')
		{
		    gotoxy(10,10);
		    printf("The record is sucessfully deleted");
		    gotoxy(10,11);
		    printf("Delete another record?(Y/N)");
		}
	}
	else
	mainmenu();
	fflush(stdin);
	another=getch();
	}
	}
    gotoxy(10,15);
    mainmenu();
}
void searchbooks()
{   int d;
    clrscr();
    printf("*****************************Search Books*********************************");
    gotoxy(20,10);
    printf("1. Search By ID");
    gotoxy(20,14);
    printf("2. Search By Name");
    gotoxy( 15,20);
    printf("Enter Your Choice");
    fp=fopen("Shadow.dat","rb+"); //open file for reading propose
    rewind(fp);   //move pointer at the begining of file
    switch(getch())
    {
	  case '1':
	{
	    clrscr();
	    gotoxy(25,4);
	    printf("****Search Books By Id****");
	    gotoxy(20,5);
	    printf("Enter the book id:");
	    scanf("%d",&d);
	    while(fread(&a,sizeof(a),1,fp)==1)
	    {
		if(a.id==d)
		{
		    gotoxy(20,7);
		    printf("The Book is available");
		    gotoxy(20,9);
		    printf("ID:%d",a.id);
		    gotoxy(20,10);
		    printf("Name:%s",a.name);
		    gotoxy(20,11);
		    printf("Author:%s ",a.Author);
		    gotoxy(20,12);
		    findbook='t';
		}

	    }
	    if(findbook!='t')  //checks whether conditiion enters inside loop or not
	    {
	    gotoxy(22,9);printf("\aNo Record Found");
	    }
	    gotoxy(20,17);
	    printf("Try another search?(Y/N)");
	    if(getch()=='y')
	    searchbooks();
	    else
	    mainmenu();
	    break;
	}
	case '2':
	{   int d=0;
	    char s[15];
	    clrscr();
	    gotoxy(25,4);
	    printf("****Search Books By Name****");
	    gotoxy(20,5);
	    printf("Enter Book Name:");
	    scanf("%s",s);
	    while(fread(&a,sizeof(a),1,fp)==1)
	    {
		if(strcmp(a.name,(s))==0) //checks whether a.name is equal to s or not
		{
		    gotoxy(20,7);
		    printf("The Book is available");
		    gotoxy(20,9);
		    printf("ID:%d",a.id);
		    gotoxy(20,10);
		    printf("Name:%s",a.name);
		    gotoxy(20,11);
		    printf("Author:%s",a.Author);
		    d++;
		}

	    }
	    if(d==0)
	    {
	    gotoxy(20,7);printf("\aNo Record Found");
	    }
	    gotoxy(20,10);
	    printf("Try another search?(Y/N)");
	    if(getch()=='y')
	    searchbooks();
	    else
	    mainmenu();
	    break;
	}
	default :
	getch();
	searchbooks();
    }
    fclose(fp);
}
void issuebooks(void)  //function that issue books from library
{
    int t;

    clrscr();
    printf("********************************ISSUE SECTION**************************");
    gotoxy(10,5);
    printf("1. Issue a Book");
    gotoxy(10,7);
    printf("2. View Issued Book");
    gotoxy(10,9);
    printf("3. Search Issued Book");
    gotoxy(10,11);
    printf("4. Remove Issued Book");
    gotoxy(10,14);
    printf("Enter a Choice:");
    switch(getch())
    {
	case '1':  //issue book
	{       int c=0;
		char another='y';
		clrscr();
		while(another=='y')
		{
			clrscr();
			gotoxy(15,4);
			printf("***Issue Book section***");
			gotoxy(10,6);
			printf("Enter the Book Id:");
			scanf("%d",&t);
			fp=fopen("Shadow.dat","rb");
			fs=fopen("Issue.dat","ab+");
			if(checkid(t)==0) //issues those which are present in library
			{    struct dosdate_t d; //for current date
			     gotoxy(10,8);
			     printf("The book record is available");
			     gotoxy(10,10);
			     printf("The name of book is %s",a.name);
			     gotoxy(10,11);
			     printf("Enter member name:");
			     scanf("%s",a.stname);
			     _dos_getdate(&d);
			     a.issued.dd=d.day;
			     a.issued.mm=d.month;
			     a.issued.yy=d.year;
			     gotoxy(10,12);
			     printf("Issued date=%d-%d-%d",a.issued.dd,a.issued.mm,a.issued.yy);
			     gotoxy(10,13);
			     printf("The BOOK of ID %d is issued",a.id);
			     a.duedate.dd=a.issued.dd+RETURNTIME;   //for return date
			     a.duedate.mm=a.issued.mm;
			     a.duedate.yy=a.issued.yy;
			     if(a.duedate.dd>30)
			     {
				 a.duedate.mm+=a.duedate.dd/30;
				 a.duedate.dd-=30;

			     }
			     if(a.duedate.mm>12)
			     {
				a.duedate.yy+=a.duedate.mm/12;
				a.duedate.mm-=12;

			     }
			     gotoxy(10,14);
			     printf("To be return:%d-%d-%d",a.duedate.dd,a.duedate.mm,a.duedate.yy);
			     fseek(fs,sizeof(a),SEEK_END);
			     fwrite(&a,sizeof(a),1,fs);
			     fclose(fs);
			     c=1;
			}
			if(c==0)
			{
			gotoxy(10,11);
			printf("No record found");
			}
			gotoxy(10,15);
			printf("Issue any more(Y/N):");
			fflush(stdin);
			another=getche();
			fclose(fp);
		}

		break;
	}
	case '2':  //show issued book list
	{
		int j=4;
		clrscr();
		printf("*******************************Issued book list*******************************\n");
		gotoxy(2,2);
		printf("NAME         CATEGORY    ID    BOOK NAME    ISSUED DATE    RETURN DATE");
	       fs=fopen("Issue.dat","rb");
		while(fread(&a,sizeof(a),1,fs)==1)
		{
			struct dosdate_t d;
			gotoxy(2,j);
			printf("%s",a.stname);
			gotoxy(16,j);
			printf("%s",a.cat);
			gotoxy(28,j);
			printf("%d",a.id);
			gotoxy(34,j);
			printf("%s",a.name);
			gotoxy(47,j);
			printf("%d-%d-%d",a.issued.dd,a.issued.mm,a.issued.yy );
			gotoxy(61,j);
			printf("%d-%d-%d",a.duedate.dd,a.duedate.mm,a.duedate.yy);
			_dos_getdate(&d);
			gotoxy(50,25);
			printf("Current date=%d-%d-%d",d.day,d.month,d.year);
			j++;

		}
		fclose(fs);
		gotoxy(1,25);
		returnfunc();
	}
	break;
	case '3':   //search issued books by id
	{
		int p,c=0;
		char another='y';
		clrscr();
		while(another=='y')
		{
			gotoxy(10,6);
			printf("Enter Book ID:");
			scanf("%d",&p);
			fs=fopen("Issue.dat","rb");
			while(fread(&a,sizeof(a),1,fs)==1)
			{
				if(a.id==p)
				{
					issuerecord();
					gotoxy(10,12);
					printf("Press any key.......");
					getch();
					issuerecord();
					c=1;
				}

			}
			fflush(stdin);
			fclose(fs);
			if(c==0)
			{
				gotoxy(10,8);
				printf("No Record Found");
			}
			gotoxy(10,13);
			printf("Try Another Search?(Y/N)");
			another=getch();
		}
	}
	break;
	case '4':  //remove issued books from list
	{
		int b;
		FILE *fg;  //declaration of temporary file for delete
		char another='y';
		clrscr();
		while(another=='y')
		{
			gotoxy(10,5);
			printf("Enter book id to remove:");
			scanf("%d",&b);
			fs=fopen("Issue.dat","rb+");
			while(fread(&a,sizeof(a),1,fs)==1)
			{
				if(a.id==b)
				{
					issuerecord();
					findbook='t';
				}
				if(findbook=='t')
				{
					gotoxy(10,12);
					printf("Do You Want to Remove it?(Y/N)");
					if(getch()=='y')
					{
						fg=fopen("record.dat","wb+");
						rewind(fs);
						while(fread(&a,sizeof(a),1,fs)==1)
						{
							if(a.id!=b)
							{
							fseek(fs,0,SEEK_CUR);
							fwrite(&a,sizeof(a),1,fg);
							}
						}
						fclose(fs);
						fclose(fg);
						remove("Issue.dat");
						rename("record.dat","Issue.dat");
						gotoxy(10,14);
						printf("The issued book is removed from list");

				       }

				}
				if(findbook!='t')
				{
					gotoxy(10,15);
					printf("No Record Found");
				}
			}
			gotoxy(10,16);
			printf("Delete any more?(Y/N)");
			another=getch();
		}
	}
	default:
       //	gotoxy(10,18);
       //	printf("\aWrong Entry!!");
	//getch();
	//issuebooks();
	break;
      }
      gotoxy(1,30);
      returnfunc();
}
void viewbooks(void)  //show the list of book persists in library
{
    int j;
    clrscr();
    gotoxy(1,1);
    printf("*********************************Book List*****************************");
    gotoxy(2,2);
    printf(" CATEGORY    ID    BOOK NAME     AUTHOR  ");
    j=4;
    fp=fopen("Shadow.dat","rb");
    while(fread(&a,sizeof(a),1,fp)==1)
    {
	gotoxy(3,j);
	printf("%s",a.cat);
	gotoxy(16,j);
	printf("%d",a.id);
	gotoxy(22,j);
	printf("%s",a.name);
	gotoxy(36,j);
	printf("%s",a.Author);
	gotoxy(50,j);
	printf("\n\n");
	j++;
      }
      fclose(fp);
      gotoxy(35,25);
      returnfunc();
}
void editbooks(void)  //edit information about book
{
	int c=0;
	int d,e;
	char another='y';
	gotoxy(20,4);
	printf("****Edit Books Section****");
	clrscr();
	while(another=='y')
	{
		clrscr();
		gotoxy(15,6);
		printf("Enter Book Id to be edited:");
		scanf("%d",&d);
		fp=fopen("Shadow.dat","rb+");
		while(fread(&a,sizeof(a),1,fp)==1)
		{
			if(checkid(d)==0)
			{
				gotoxy(15,7);
				printf("The book is availble");
				gotoxy(15,8);
				printf("The Book ID:%d",a.id);
				gotoxy(15,9);
				printf("Enter new name:");scanf("%s",a.name);
				gotoxy(15,10);
				printf("Enter new Author:");scanf("%s",a.Author);
				printf("The record is modified");
				fseek(fp,ftell(fp)-sizeof(a),0);
				fwrite(&a,sizeof(a),1,fp);
				fclose(fp);
				c=1;
			}
			if(c==0)
			{
				gotoxy(15,12);
				printf("No record found");
			}
		}
		gotoxy(15,16);
		printf("Modify another Record?(Y/N)");
		fflush(stdin);
		another=getch() ;
	}
		returnfunc();
}
void returnfunc(void)
{
    {
	printf(" \nPress ENTER to return to main menu");
    }
    a:
    if(getch()==13) //allow only use of enter
    mainmenu();
    else
    goto a;
}
int getdata()
{
	int t;
	gotoxy(20,3);printf("Enter the Information Below");
	
	gotoxy(21,5);
	printf("Category:");
	gotoxy(31,5);
	printf("%s",catagories[s-1]);
	gotoxy(21,6);
	printf("Book ID:\t");
	gotoxy(30,6);
	scanf("%d",&t);
	if(checkid(t) == 0)
	{
		gotoxy(21,13);
		printf("\aThe book id already exists\a");
		getch();
		mainmenu();
		return 0;
	}
	a.id=t;
	gotoxy(21,7);
	printf("Book Name:");gotoxy(33,7);
	scanf("%s",a.name);
	gotoxy(21,8);
	printf("Author:");gotoxy(30,8);
	scanf("%s",a.Author);
	gotoxy(21,9);
	return 1;
}
int checkid(int t)  //check whether the book is exist in library or not
{
	rewind(fp);
	while(fread(&a,sizeof(a),1,fp)==1)
	if(a.id==t)
	return 0;  //returns 0 if book exits
      return 1; //return 1 if it not
}
int t(void) //for time
{
time_t t;
time(&t);
printf("Date and time:%s\n",ctime(&t));

return 0 ;
}
void Password(void) //for password option
{
   char ch,pass[10];
   int i=0;
   clrscr();
   gotoxy(15,5);
   printf("***Password Protected***");
   gotoxy(15,7);
   printf("Enter Password:");

   while(ch!=13)
   {
	ch=getch();
	putch('*');
	if(ch!=13){
	pass[i] = ch;
	i++;
	}
   }
   pass[i] = '\0';
   if(strcmp(pass,password)==0)
   {	gotoxy(17,8);
	printf("Password match");
	gotoxy(17,10);
	printf("Press any key to countinue.....");
	getch();
	mainmenu();
   }
   else
   {
	 gotoxy(15,16);
	 printf("\aWarning!! Incorrect Password");
	 getch();
	 Password();
   }
}
void issuerecord()  //display issued book's information
{
		 clrscr();
		 gotoxy(10,8);
		 printf("The Book has been taken by %s",a.stname);
		 gotoxy(10,9);
		 printf("Issued Date:%d-%d-%d",a.issued.dd,a.issued.mm,a.issued.yy);
		 gotoxy(10,10);
		 printf("Returning Date:%d-%d-%d",a.duedate.dd,a.duedate.mm,a.duedate.yy);
}
void view_wish(void)  //show the wishlist
{
    int j;
    clrscr();
    gotoxy(1,1);
    printf("*********************************Wish List*****************************");
    gotoxy(2,2);
    printf("SERIAL NO.          MEMBER NAME           BOOK NAME  ");
    j=4;
    fp=fopen("WISH.dat","rb");
    while(fread(&b,sizeof(b),1,fp)==1)
    {

	gotoxy(3,j);
	printf("%d",b.serialno);
	gotoxy(22,j);
	printf("%s",b.memname);
	gotoxy(42,j);
	printf("%s",b.bookname);
	gotoxy(50,j);
	printf("\n\n");
	j++;
      }
      fclose(fp);
      getch();
      wishlist();
}
void addwish(void)    //funtion to add books to wishlist
{       clrscr();
	fp=fopen("WISH.dat","ab+");
	if(get_data()==1)
	{
	fwrite(&b,sizeof(b),1,fp);
	fclose(fp);
	gotoxy(21,14);
	printf("The record is sucessfully saved");
	gotoxy(21,15);
	printf("Save any more?(Y / N):");
	if(getch()=='n')
	    wishlist();
	else
	    clrscr();
	    addwish();
	}
}
void deletewish()    //function that delete books from wishlist
{   int d;
    char another='y';
    clrscr();
    while(another=='y')  //infinite loop
    {
	clrscr();
	gotoxy(10,5);
	printf("Enter the Serial No. to  delete:");
	scanf("%d",&d);
	fp=fopen("WISH.dat","rb+");
	rewind(fp);
	while(fread(&b,sizeof(b),1,fp)==1)
	{
	    if(b.serialno==d)
	    {
		gotoxy(10,7);
		printf("The book record is available");
		gotoxy(10,8);
		printf("Book name is %s",b.bookname);
		findbook='t';
	    }
	}
	if(findbook!='t')
	{
	    gotoxy(10,10);
	    printf("No record is found modify the search");
	    if(getch())
	    wishlist();
	}
	if(findbook=='t' )
	{
	    gotoxy(10,9);
	    printf("Do you want to delete it?(Y/N):");
	    if(getch()=='y')
	    {
		ft=fopen("test.dat","wb+");  //temporary file for delete
		rewind(fp);
		while(fread(&b,sizeof(b),1,fp)==1)
		{
		    if(b.serialno!=d)
		    {
			fwrite(&b,sizeof(b),1,ft); //write all in tempory file except that
		    }                              //we want to delete
		}
		fclose(ft);
		fclose(fp);
		remove("WISH.dat");
		rename("test.dat","WISH.dat"); //copy all item from temporary file to fp except that
		fp=fopen("WISH.dat","rb+");    //we want to delete
		if(findbook=='t')
		{
		    gotoxy(10,10);
		    printf("The record is sucessfully deleted");
		    gotoxy(10,11);
		    printf("Delete another record?(Y/N)");
		}
	}
	else
	wishlist();
	fflush(stdin);
	another=getch();
	}
	}
    gotoxy(10,15);
    wishlist();
}
void wishlist()
{ 
    clrscr(); 
    printf("********************************WISHLIST**************************");
    gotoxy(10,5);
    printf("1. Add Book");
    gotoxy(10,7);
    printf("2. Delete Book");
    gotoxy(10,9);
    printf("3. View Wishlist");
    gotoxy(10,11);
    printf("4. Main Menu");
    gotoxy(10,13);
    printf("Enter a Choice:");
    switch(getch())
    {
	case '1':
		 addwish();
		 break;
	case '2':
		 deletewish();
		 break;
	case '3':
		 view_wish();
		 break;
	case '4':
		 mainmenu();
		 break;
		 default:
       	gotoxy(10,18);
       	printf("\aWrong Entry!!");
	getch();
	wishlist();
	break;
      }
}
int get_data()
{
	int t;
	gotoxy(20,3);
	printf("Enter the Information Below");
	gotoxy(21,5);
	printf("Serial No.:");
	gotoxy(41,5);
	scanf("%d",&t);
	if(checksl(t)==0)
	{
		gotoxy(21,13);
		printf("\aThe book id already exists\a");
		getch();
		wishlist();
		return 0;
	}
                   b.serialno=t;
	gotoxy(21,7);
	printf("Member name:");
	gotoxy(41,7);
	scanf("%s",b.memname);
	gotoxy(21,9);
	printf("Book Name:");
	gotoxy(41,9);
	scanf("%s",b.bookname);
	return 1;

}
int checksl(int t)  //check whether the book is exist in library or not
{
	rewind(fp);
	while(fread(&b,sizeof(b),1,fp)==1)
	if(b.serialno==t)
	return 0;  //returns 0 if book exits
	return 1; //return 1 if it not
}

//End of program