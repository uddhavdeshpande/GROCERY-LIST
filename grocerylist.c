/*****************************************************************************
 * Copyright (C) Uddhav Deshpande yudideshpande@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"grocerylist.h"


int main(){
	FILE *fp;
	int a;
	int select;
	printf("*********::********************************************\n");
	
	printf("\n\t\t\tWELCOME");

	printf("\n\t\t     (Grocery List)\n");

	printf("\n");

	printf("\n");

	printf("\t             Press 1 to enter\n");

	printf("\n******************************************************\n");

	scanf("%d",&a);

	if(a == 1){

		printf("*********************************************************\n");

			printf("\n\t1. make new changes in the database\n"\
			       "\n\t2. purchase item from the database\n"\
			       "\n\t3. generate the final bill\n"\
			       "\n\t0. exit the list\n");

			printf("\n*********************************************************\n");

			scanf("%d",&select);
		switch(select)
			{
			case (1): manageitem();
				  break;

			case (2): purchaseitem();
				  break;

			case (3): finalbill();
				  break; 

			case (0): exit(0);

			}

		}

	return(0);

}


int id(){	/* used to find the serial number of the item selected*/
	int v = 0;
	FILE *fp;
	fp = fopen("itemsr.txt","r");
	
	if(fp == NULL){

		fp = fopen("itemsr.txt","w");

		fprintf(fp,"%d",0);

		fclose(fp);

		fp = fopen("itemsr.txt","r");

		}

	fscanf(fp,"%d",&v);

	fclose(fp);
	fp = fopen("itemsr.txt","w");

	fprintf(fp,"%d",v+1);

	fclose(fp);
	return v + 1;

}

/*another call to select whether we want to add or display the items in the list*/

void manageitem(){
	int select ,done = 0;

	printf("*********************************************************************\n");

	printf("\t 1.add new item in the database\n");

	printf("\t 2.display all items in the database\n");

	printf("\t 3.exit the list\n");

	printf("**********************************************************************\n");

	printf("please enter the choice\n");

	scanf("%d", &select);

	switch(select){
		case 1: additem();
			break;

		case 2: displayallitem();
			 break;

		case 3: done = 1;
			break;
			
		if(done = 1){
			break;
			}
		}		
}

/*in order to add an item in the file named fitem*/

void additem(){
	char ch; 	
	FILE *fp;
	struct item d;
	fp = fopen(fitem ,"ab");
	d.id = id();

	printf("please enter the item name\n");

	scanf("%s", d.name);

	printf("please enter the mrp of the item\n");

	scanf("%d",&d.cost);

	printf("please enter the number of items you want to add\n");

	scanf("%d",&d.qty);

	fwrite(&d,sizeof(d),1,fp);

	fclose(fp);
	displayallitem();

}

/*to display the list*/

void displayallitem(){
	FILE *fp;
	struct item d;
	int id ,found = 0;
	system("clear");

	fp = fopen(fitem ,"rb");

	printf("***************************************************************************\n");

	printf("\t\tList of the items are\n");

	printf("***************************************************************************\n");

	printf("Sr\titem name\tqty\tcost\n");

	while(1){
		fread(&d ,sizeof(d) ,1 ,fp);
		if(feof(fp)){

			break;

			}
	
		printf("%d\t",d.id);

		printf("%s\t\t",d.name);

		printf("%d\t",d.qty);

		printf("%d\n",d.cost);


		}
	printf("*****************************************************************************\n");
	fclose(fp);

}



void finalbill(){	/*it is used to generate the final bill*/
	FILE *fp;
	struct bill d;
	int id ,found = 0 ,sum = 0;	
	char ch;
	char billname[40];
	system("clear");
	fp = fopen(fbill ,"rb");
	printf("****************************************************************************\n");

	printf("\tfinal bill \n");

	printf("****************************************************************************\n");
	
	printf("  Sr\tname of the item\tcost\n");

	while(1){

		fread(&d ,sizeof(d) ,1 ,fp);

		if(feof(fp)){

			break;

		}

	printf("%d\t",d.nid);

	printf("\t%s\t",d.nname);

	printf("%d\n",d.ncost);

	sum = sum+d.ncost;

	}

	printf("---------------------------------------------\n");

	printf("\tTOTAL = %d\n",sum);

	printf("*******************************************************************************\n");

	fclose(fp);
	

}


void updateitem(int id , int qty){	/*it is used to update the quantity of the items in the database*/
	FILE *fp1 ,*fp2;
	struct item d;
	int found = 0;

	fp1 = fopen(fitem ,"rb");
	fp2 = fopen("temp.dat","wb");

	while(1){
		fread(&d ,sizeof(d) ,1 ,fp1);

		if(feof(fp1)){

			break;
		}

		if(d.id == id){

				found = 1;
				d.qty =qty;
			fwrite(&d ,sizeof(d) ,1 ,fp2);

		}

		else{
			fwrite(&d ,sizeof(d) ,1 ,fp2);

			}

		}

		fclose(fp1);
		fclose(fp2);

		if(found = 0){

			printf("no match found");

			}

		else{
			fp1 = fopen(fitem ,"wb");
			fp2 = fopen("temp.dat","rb");

			while(1){

				fread(&d ,sizeof(d) ,1 ,fp2);
				if(feof(fp2)){
				
					break;
				}

				fwrite(&d,sizeof(d),1,fp1);
			}

		}

		fclose(fp1);
		fclose(fp2);

}


void purchaseitem(){		/*it is used to select the item the customer wants to purchase*/
	int id;
	char ch1 ,ch2 ;

	printf("********************************************************************************\n");

	printf(" Select from the list \n");

	printf("*********************************************************************************\n");

	while(1){

		displayallitem();

		printf("would you like to purchase the item(y/n)\n");

		scanf("%c",&ch1);

		if(ch1 == 'y'){

			FILE *fp;
			struct bill m;
			struct item p;
			fp = fopen(fbill ,"ab");

			printf("please enter the serial number of the item you want to purchase\n");

			scanf("%d",&id);

			p = finditem(id);
			m.nid = p.id;
			m.ncost = p.cost;
			strcpy(m.nname ,p.name);
			fwrite(&m,sizeof(p),1,fp);
			fclose(fp);

			}
		if(ch1 == 'n'){
			
			exit(0);
			
			}

		printf("would you like to buy another item(y/n)\n");

		scanf("%c\n",ch2);

		if(ch2 == 'n'){

			break;

			}

		}

}	

			
struct item finditem(int id){		/*here when we enter the serial number of the  item we want to purchase from the database ,this 					function is used to find the item from the given serial number*/
	FILE *fp;
	struct item d;
	fp = fopen(fitem, "rb");

	while(1){

		fread(&d,sizeof(d),1,fp);
		if(feof(fp)){

			break;

			}

		if(d.id == id){

			updateitem(id ,d.qty - 1);
			break;

			}

		}	

	fclose(fp);
	return d;

}

