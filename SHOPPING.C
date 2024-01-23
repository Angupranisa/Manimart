#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
void menu();

static int bill=1;

struct stock
{
	char itemcode[20];
	char itemname[30];
	char quantity[10];
	char unit[5];
	char unitprice[10];
};

struct customer
{
	char name[30];
	char phno[15];
	char city[20];
};

void welcome()
{
	clrscr();
	printf("\n\n\t\t\t******************************\n");
	printf("\t\t\t**                          **\n");
	printf("\t\t\t**         WELCOME          **\n");
	printf("\t\t\t**                          **\n");
	printf("\t\t\t**           TO             **\n");
	printf("\t\t\t**                          **\n");
	printf("\t\t\t**        MANI MART         **\n");
	printf("\t\t\t**                          **\n");
	printf("\t\t\t**                          **\n");
	printf("\t\t\t******************************");
	getch();
}

void login()
{
	int i,flag=0;
	char ch;
	char username[10],password[10],fuser[10],fpass[10];
	FILE *login;
	login = fopen("LoginID.txt","r");
	do
	{
		i=0;
		clrscr();
		printf("\n\n\t\t*****************LOGIN FORM****************\n");
		printf("\n\n\t             Enter Username: ");
		scanf("%s",username);
		printf("\n\n\t             Enter password: ");
		while((ch = getch())!=13)
		{
			password[i]=ch;
			i++;
			printf("*");
		}

		password[i]=NULL;

		fscanf(login,"%s%s",&fuser,&fpass);
		if(strcmp(username,fuser)!=0)
		{
			printf("\n\nInvalid username... Try again!!!");
		}
		else if(strcmp(password,fpass)!=0)
		{
			printf("\n\nInvalid password... Try again!!!");
		}
		else
		{
			flag=1;
			printf("\n\n\t\t*************LOGIN SUCCESSFUL**************");
		}
		getch();
	}while(flag==0);
}


void add(int option)
{
int i,n;
char ch;
struct stock st;
struct customer cu[10];
FILE *sp;
FILE *cp;

	clrscr();
	switch(option)
	{
		case 1:
		sp = fopen("stock.txt","r");
		if(sp != NULL)
		{
		sp = fopen("stock.txt","a");
		}
		else
		{
		sp = fopen("stock.txt","w");
		}
		printf("\n\n\t\tAdd stock details\n");
		printf("\t\t*****************\n\n");
		printf("Enter Item code:\"end\" to terminate...\n");
		while(1)
		{
			printf("\tStock\n");
			printf("\t-------\n");
			printf("Enter Item code  : ");
			scanf("%s",st.itemcode);
			if(strcmp(st.itemcode,"end")==0) break;
			printf("Enter Item Name  : ");
			scanf("%s",st.itemname);
			printf("Enter Quantity   : ");
			scanf("%s",st.quantity);
			printf("Enter unit       : ");
			scanf("%s",st.unit);
			printf("Enter Unit price : ");
			scanf("%s",st.unitprice);
			fprintf(sp,"%s\t%s\t%s\t%s\t%s\n",st.itemcode,st.itemname,st.quantity,st.unit,st.unitprice);

		}
		fclose(sp);
		printf("\n\nAdded succesfully...");
		break;

		case 2:
		cp = fopen("customer.txt","r");
		if(cp != NULL)
		{
		cp = fopen("customer.txt","a");
		}
		else
		{
		cp = fopen("customer.txt","w");
		}
		printf("\n\n");
		printf("\t\tAdd Customer details\n");
		printf("\t\t***********************\n\n");
		printf("Enter the number of Customers: ");
		scanf("%d",&n);
		for(i=1;i<=n;i++)
		{
			printf("\tCustomer %d\n",i);
			printf("\t--------\n");
			printf("Enter Name            : ");
			scanf("%s",cu[i].name);
			printf("Enter Phone number    : ");
			scanf("%s",cu[i].phno);
			printf("Enter City            : ");
			scanf("%s",cu[i].city);
			fprintf(cp,"%s\t%s\t%s\n",cu[i].name,cu[i].phno,cu[i].city);

		}
		fclose(cp);
		printf("\n\nAdded succesfully...");
		break;

	}
	getch();
	menu();
}

void update(int option)
{
FILE *ups,*temp,*upc;
char icode[20],iquant[10];
char phone[15],iphno[15];
struct stock st;
struct customer cu;
int flag=0,nquan,n1,n2;

	clrscr();
	switch(option)
	{
		case 1:
		printf("\n\n");
		printf("\tUpdate stock\n");
		printf("\t************\n\n\n");
		printf("Enter item code        : ");
		scanf("%s",icode);
		printf("Enter the new quantity : ");
		scanf("%s",iquant);
		ups = fopen("stock.txt","r");
		temp = fopen("stocktemp.txt","w");
		if(ups==NULL || temp == NULL)
		{
			printf("Error opening file");
		}
		while(1)
		{
			fscanf(ups,"%s%s%s%s%s",&st.itemcode,&st.itemname,&st.quantity,&st.unit,&st.unitprice);
			if(feof(ups))
				break;

			if(strcmp(st.itemcode,icode)==0)
			{
				flag = 1;
				n1=atoi(st.quantity);
				n2=atoi(iquant);
				nquan=n1+n2;
				fprintf(temp,"%s\t%s\t%d\t%s\t%s\n",st.itemcode,st.itemname,nquan,st.unit,st.unitprice);
			}
			else
			fprintf(temp,"%s\t%s\t%s\t%s\t%s\n",st.itemcode,st.itemname,st.quantity,st.unit,st.unitprice);

		}

		if(flag == 0)
			printf("\n\nItemcode doesn't exist");

		fclose(ups);
		fclose(temp);

		remove("stock.txt");
		rename("stocktemp.txt","stock.txt");
		if(flag==1)
		printf("\n\nUpdated succesfully...");
		break;

		case 2:
		printf("\n\n");
		printf("\tUpdate Customer details\n");
		printf("\t************************\n\n\n");
		printf("Enter phone number   : ");
		scanf("%s",phone);
		printf("Enter the new number : ");
		scanf("%s",iphno);
		upc = fopen("customer.txt","r");
		temp = fopen("custtemp.txt","w");
		if(upc==NULL || temp == NULL)
		{
			printf("\n\nError opening file");
		}
		while(1)
		{
			fscanf(upc,"%s%s%s",&cu.name,&cu.phno,&cu.city);
			if(feof(upc))
				break;
			if(strcmp(cu.phno,phone)==0)
			{
				flag = 1;
				fprintf(temp,"%s\t%s\t%s\n",cu.name,iphno,cu.city);

			}
			else
			fprintf(temp,"%s\t%s\t%s\n",cu.name,cu.phno,cu.city);
		}
		if(flag == 0)
			printf("\n\nPhone number doesn't exist");

		fclose(upc);
		fclose(temp);

		remove("customer.txt");
		rename("custtemp.txt","customer.txt");
		if(flag==1)
		printf("\n\nUpdated succesfully...");
		break;
	  }
	  getch();
	  menu();

}

void deletee(int option)
{
FILE *des,*temp,*dec;
char icode[20],iquant[10];
char iphno[50];
struct stock st;
struct customer cu;
int flag = 0;
	clrscr();
	switch(option)
	{
		case 1:
		printf("\n\n");
		printf("\tDelete stock\n");
		printf("\t************\n\n\n");
		printf("Enter item code: ");
		scanf("%s",icode);
		des = fopen("stock.txt","r");
		temp = fopen("stocktemp.txt","w");
		if(des==NULL || temp == NULL)
		{
			printf("\n\nError opening file");
		}
		while(1)
		{
			fscanf(des,"%s%s%s%s%s",&st.itemcode,&st.itemname,&st.quantity,&st.unit,&st.unitprice);

			if (feof(des))	break;

			if(strcmp(st.itemcode,icode)!=0)
				fprintf(temp,"%s\t%s\t%s\t%s\t%s\n",st.itemcode,st.itemname,st.quantity,st.unit,st.unitprice);
			else
				flag = 1;
		}
			if(flag == 0)
			printf("\n\nItemcode doesn't exist");
			fclose(des);
			fclose(temp);

			remove("stock.txt");
			rename("stocktemp.txt","stock.txt");
			if(flag==1)
			printf("\n\nDeleted succesfully...");
			break;

			case 2:
			printf("\n\n");
			printf("\tDelete customer\n");
			printf("\t***************\n\n\n");
			printf("Enter Phone number: ");
			scanf("%s",iphno);
			dec = fopen("customer.txt","r");
			temp = fopen("custtemp.txt","w");
			if(dec==NULL || temp == NULL)
			{
				printf("\n\nError opening file");
			}
			while(1)
			{
				fscanf(dec,"%s%s%s",&cu.name,&cu.phno,&cu.city);

				if (feof(dec))	break;

				if(strcmp(cu.phno,iphno)!=0)
				fprintf(temp,"%s\t%s\t%s\n",cu.name,cu.phno,cu.city);
				else
				flag = 1;
			}
			if(flag == 0)
			printf("\n\nPhone number doesn't exist");
			fclose(dec);
			fclose(temp);

			remove("customer.txt");
			rename("custtemp.txt","customer.txt");
			if(flag==1)
			printf("\n\nDeleted succesfully...");
			break;

	}
	getch();
	menu();
}

void display(int option)
{
FILE *diss,*disc;
struct stock st;
struct customer cu;

	clrscr();
	switch(option)
	{
		case 1:
		diss = fopen("stock.txt","r");
		printf("\n\n***********************************STOCK DETAILS*******************************\n\n");
		printf("ItemCode\tItemName\t\tQuantity\tUnit\tUnitPrice\n\n");
		while(1)
		{
			fscanf(diss,"%s%s%s%s%s",&st.itemcode,&st.itemname,&st.quantity,&st.unit,&st.unitprice);
			if(feof(diss)) break;
			printf("%-16s%-25s%-16s%-10s%-10s\n",st.itemcode,st.itemname,st.quantity,st.unit,st.unitprice);

		}
		printf("\n*******************************************************************************");
		break;

		case 2:
		disc = fopen("customer.txt","r");
		printf("\n\n******************************CUSTOMER DETAILS**********************************\n");
		printf("Name\t\t\tPhoneNumber\t\t\tCity\n\n");
		while(1)
		{
			fscanf(disc,"%s%s%s",&cu.name,&cu.phno,&cu.city);
			if(feof(disc)) break;
			printf("%-25s%-30s%-20s\n",cu.name,cu.phno,cu.city);

		}
		printf("\n********************************************************************************");
		break;
	}
	getch();
	menu();
}


void stock_menu()
{
	int choice,flag=0;
	do
	{
	clrscr();
	printf("\n\n\t\t********************STOCK*******************\n\n");
	printf("\t\t                   1.Add\n");
	printf("\t\t                   2.Update\n");
	printf("\t\t                   3.Delete\n");
	printf("\t\t                   4.Display\n");
	printf("\t\t                   5.Back to Main Menu\n\n");
	printf("\t\t********************************************\n\n");
	printf("\nEnter your choice: ");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
		add(1);
		break;

		case 2:
		update(1);
		break;

		case 3:
		deletee(1);
		break;

		case 4:
		display(1);
		break;

		case 5:
		menu();
		break;

		default:
		flag=1;
		printf("Invalid Choice... Try again!!!");
	}
	getch();
	}while(flag==1);

}

void cust_menu()
{
	int choice,flag=0;
	do
	{
	clrscr();
	printf("\n\n\t\t********************CUSTOMER DETAILS*******************\n\n");
	printf("\t\t                  1.Add Customer\n");
	printf("\t\t                  2.Update\n");
	printf("\t\t                  3.Delete\n");
	printf("\t\t                  4.Display\n");
	printf("\t\t                  5.Back to Main Menu\n\n");
	printf("\t\t*******************************************************\n\n");
	printf("\nEnter your choice: ");
	scanf("%d",&choice);

	switch(choice)
	{
		case 1:
		add(2);
		break;

		case 2:
		update(2);
		break;

		case 3:
		deletee(2);
		break;

		case 4:
		display(2);
		break;

		case 5:
		menu();
		break;

		default:
		flag = 1;
		printf("Invalid choice...Try again!!!");

	}
	getch();
	}while(flag==1);

}

void purchase()
{
int n,i,flag=0,cflag=0,amount=1,q,up,rem;
char itname[30],quan[10];
char cname[30],cphno[15],ccity[20];
struct stock st;
struct customer cu;
FILE *pur,*fst,*fcp,*ftcp,*fstt;

	clrscr();
	pur=fopen("purchase.txt","r");
	fcp=fopen("customer.txt","r");
	ftcp=fopen("custtemp.txt","w");

	if(pur!= NULL)
	pur=fopen("purchase.txt","a");
	else
	pur=fopen("purchase.txt","w");
	printf("\n\n\t\t*********************Purchase******************\n");
	printf("\nEnter customer name : ");
	scanf("%s",cname);
	printf("Enter phone number : ");
	scanf("%s",cphno);
	printf("Enter city : ");
	scanf("%s",ccity);
	while (1)
	{
		fscanf(fcp,"%s%s%s",&cu.name,&cu.phno,&cu.city);
		if(feof(fcp)) break;
		if(strcmp(cphno,cu.phno)!=0)  cflag=1;
		fprintf(ftcp,"%s\t%s\t%s\n",cu.name,cu.phno,cu.city);
	}
	if (cflag==1)
		fprintf(ftcp,"%s\t%s\t%s\n",cname,cphno,ccity);

	fclose(fcp);
	fclose(ftcp);
	remove("customer.txt");
	rename("custtemp.txt","customer.txt");
	printf("\nEnter Item name \"end\" to terminate...\n");

	while(1)
	{
		printf("\nProduct\n");
		printf("--------\n");
		printf("Enter item name: ");
		scanf("%s",itname);
		if(strcmp(itname,"end")==0) break;
		printf("Enter quantity : ");
		scanf("%s",quan);
		fst=fopen("stock.txt","r");
		fstt=fopen("stocktemp.txt","w");
		while(!feof(fst))
		{
		fscanf(fst,"%s%s%s%s%s",&st.itemcode,&st.itemname,&st.quantity,&st.unit,&st.unitprice);
		if(feof(fst)) break;
		if((strcmp(itname,st.itemname)!=0))
			fprintf(fstt,"%s\t%s\t%s\t%s\t%s\n",st.itemcode,st.itemname,st.quantity,st.unit,st.unitprice);
		else if((strcmp(itname,st.itemname)==0) && (
		atoi(st.quantity)>=atoi(quan)))
		{
			flag=1;
			q=atoi(quan);
			up=atoi(st.unitprice);
			amount=q*up;
			fprintf(pur,"%s %s %s %s %s %s %s %s %d\n",cname,cphno,ccity,st.itemcode,st.itemname,quan,st.unit,st.unitprice,amount);
			rem=atoi(st.quantity)-atoi(quan);
			fprintf(fstt,"%s\t%s\t%d\t%s\t%s\n",st.itemcode,st.itemname,rem,st.unit,st.unitprice);
		}
		}

		fclose(fst);
		fclose(fstt);
		remove("stock.txt");
		rename("stocktemp.txt","stock.txt");

	}
	if(flag==0)
		printf("\n\nItem not available\n");

	if(flag==1)
		printf("\n\nPurchased succesfully");

	fclose(pur);
	getch();
	menu();
}

void bill_menu()
{
FILE *purs,*cuss;
int printed=0;
float gst,totalamount=0.0,amount1;
char amount[10],phone[15];
struct stock st;
struct customer cu;
 time_t tim= time(NULL);

	clrscr();
	printf("\n\nEnter Customer phone number: ");
	scanf("%s",phone);
	clrscr();
	purs= fopen("purchase.txt","r");
	printf("\n\n\t***********************BILL************************\n\n");
	printf("\t\t\tMANI MART\n\n");
	printf("\tDate and time:");
	printf("%s\n",ctime(&tim));
	printf("\tBill number:MM000%d\n",bill);
	bill++;
	printf("\t---------------------------------------------------\n");
	while (1)
	{
		fscanf(purs,"%s%s%s%s%s%s%s%s%s",&cu.name,&cu.phno,&cu.city,&st.itemcode,&st.itemname,&st.quantity,&st.unit,&st.unitprice,&amount);
		if(feof(purs)) break;
		if(strcmp(cu.phno,phone)==0 && printed!=1)
		{
			printed=1;
			printf("\tCustomer Name : %s\n",cu.name);
			printf("\tPhone Number  : %s\n",cu.phno);
			printf("\tCity          : %s\n",cu.city);
			printf("\t---------------------------------------------------\n");
		}
		if(strcmp(cu.phno,phone)==0)
		{
			printf("\t%-10s%-20s\t%s\t%s\t%s\n",st.itemcode,st.itemname,st.quantity,st.unit,amount);
			amount1 = atoi(amount);
			totalamount = totalamount + amount1;
		}

	}
	gst=totalamount * 0.03;
	printf("\t---------------------------------------------------\n");
	printf("                                Amount=%.2f\n",totalamount);
	printf("                                GST=%.2f\n",gst);
	printf("                                Total Amount=%.2f\n",totalamount+gst);
	printf("\t****************************************************");
	printf("\n\t              ThankYou. Visit Again!!!");

	getch();
	menu();
}


void menu()
{
	int choice,flag=0;

	do
	{
	clrscr();
	printf("\n\n\t\t**********************MAIN MENU*********************\n\n");
	printf("\t\t                1.Stock Management\n");
	printf("\t\t                2.Customer details\n");
	printf("\t\t                3.Purchase\n");
	printf("\t\t                4.Billing\n");
	printf("\t\t                5.Exit\n");
	printf("\n\t\t****************************************************");
	printf("\n\n\nEnter your choice: ");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
		stock_menu();
		break;

		case 2:
		cust_menu();
		break;

		case 3:
		purchase();
		break;

		case 4:
		bill_menu();
		break;

		case 5:
		exit(0);
		break;

		default:
		printf("Invalid choice...Try again!!!");
		flag=1;
	}
	getch();
	}while(flag==1);
}

int main()
{
	welcome();
	login();
	menu();

	getch();
	return 0;
}

