/*RESTAURANT SALES TRACKER
This is a system that displays the menu in the restaurant, and then creates an order list by taking input from customers,
for the reference of the restaurant management and staff.
This way they can keep track of their sales, and all of the food items that they have catered to customers.*/
#include <stdio.h>
#include <conio.h>
#include <stdlib.h> 
#include <string.h>
void add_order_item();
void read_order_list();
void modify_order_list();
void delete_order_item();
int option();
struct order
      {
            char name[30];
            int price;
            int quantity;
            int code;
      };
void main()
{
    printf("Welcome to Restaurant Sales Tracking System\n");
    printf("Please pick dishes that have been ordered from the Menu below:\n");
    printf("DISH CODE \t DISH NAME \t\t    DISH PRICE\n");
    printf("001 \t       French Fries \t\t\t 60\n");
    printf("002 \t       Cheese Burger \t\t\t 70\n");
    printf("003 \t       Grilled Sandwich \t\t 70\n");
    printf("004 \t       Steamed Momos \t\t\t 80\n");
    printf("005 \t       Veg Paneer Roll \t\t\t 55\n");
    printf("006 \t       Chicken Roll \t\t\t 65\n");
    printf("007 \t       Schezwan Noodles \t\t 90\n");
    printf("008 \t       Schezwan Fried Rice \t\t 90\n");
    printf("009 \t       Chicken Shawarma \t\t 80\n");
    printf("010 \t       Bread Omlette \t\t\t 55\n");
    printf("011 \t       Chocolate Milkshake \t\t 50\n");
    printf("012 \t       Rose Milk \t\t\t 30\n");
    printf("013 \t       Mixed Fruit Juice \t\t 40\n");
    printf("014 \t       Cold Coffee \t\t\t 50\n");
    printf("015 \t       Milkshake with Icecream \t\t 65\n");
    
      int c;
      char confirm='Y'; 
      while(confirm=='Y')
      {
            c=option();
            switch(c)
{       
                  case 1:
                  add_order_item();
                  break;
                  case 2:
                  read_order_list();
                  break;
                  case 3:
                  modify_order_list();
                  break;
                  case 4:
                  delete_order_item();
                  break; 
            }
            printf("\nType 'Y' to continue with operations:");
            scanf("\n%c",&confirm);
      } 
}
int option()
{
      int ch;
      printf("\nOptions available:");
      printf("\nPlease press 1 to add items to order list. \nPlease press 2 to read items from order list. \n");
      printf("Please press 3 to modify order item quantity. \nPlease press 4 to remove item from order list.");
      printf("\nEnter choice: ");
      scanf("%d",&ch);
      return ch;
}
void add_order_item()
{ 
      struct order list;
      FILE *ft;
      char x='Y';
      ft=fopen("Restaurant Order","a+");
do
      {
            char ch;
            printf("\nEnter the name of the item, its code, the price, and the order quantity: ");
            scanf("%s %d %d %d",list.name,&list.code,&list.price,&list.quantity);
            fprintf(ft,"%s   %d    %d   %d\n",list.name,list.code,list.price,list.quantity);
printf("Type 'Y' to repeat the operation\n");
scanf("\n%c",&ch);
x=ch;
      }while(x=='Y');
      fclose(ft);
}
void read_order_list() 
{
      struct order list;
      FILE *ft;
      ft=fopen("Restaurant Order","r");
      printf("NAME      CODE      PRICE     QUANTITY");
      while(feof(ft)==0)
      {
            fscanf(ft,"%s     %d     %d     %d\n",list.name, &list.code,&list.price,&list.quantity);
            printf("\n%s  %d   %d   %d",list.name,list.code,list.price,list.quantity);
}
fclose(ft);
}
void modify_order_list()
{
      struct order list; 
      FILE *ft,*fp;
      ft=fopen("Restaurant Order","r");
      fp=fopen("temp","w+");
      int code;
      int quant;
      printf("\nPlease enter the item code who's quantity is to be modified, and enter the new quantity.:\n");
      scanf("%d %d",&code,&quant);
      while(!feof(ft))
      {
            fscanf(ft,"%s     %d     %d     %d\n",list.name,&list.code,&list.price,&list.quantity);
            if(list.code!=code)
            fprintf(fp,"%s    %d    %d %d\n",list.name,list.code,list.price,list.quantity); 
            else
            { 
                  list.quantity=quant;
                  fprintf(fp,"%s  %d   %d   %d\n",list.name,list.code,list.price,list.quantity);
             }
}
fclose(ft);
fclose(fp);
remove("Restaurant Order");
rename("temp","Restaurant Order");
}
void delete_order_item()
{
      struct order list;
      FILE *ft,*fp;
      int code;
      ft=fopen("Restaurant Order","r");
      fp=fopen("temp","w+"); 
     printf("\nPlease enter the code of the item to be deleted:\n"); 
      scanf("%d",&code);
      while (!feof(ft))
      {
            fscanf(ft,"%s     %d     %d     %d\n",list.name,&list.code,&list.price,&list.quantity);
            if(code!=list.code)
            fprintf(fp,"%s    %d     %d   %d\n",list.name,list.code,list.price,list.quantity);
}
fclose(ft);
fclose(fp);
      remove("Restaurant Order");
   rename("temp","Restaurant Order");
}