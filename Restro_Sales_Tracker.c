/*RESTAURANT SALES TRACKER
This is a system that displays the menu in the restaurant, and then creates an order list by taking input from customers,
for the reference of the restaurant management and staff.
This way they can keep track of their sales, and all of the food items that they have catered to customers.*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct items{
    char item[20];
    float price;
    int qty;
};

struct orders{
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};
 
void BillHeader(char name[50],char date[30]){
    printf("\n\n");
        printf("\t    Atre's Restaurant");
        printf("\n\t   -----------------");
        printf("\nDate:%s",date);
        printf("\nInvoice To: %s",name);
        printf("\n");
        printf("---------------------------------------\n");
        printf("Items\t\t");
        printf("Qty\t\t");
        printf("Total\t\t");
        printf("\n---------------------------------------");
        printf("\n\n");
}
void BillBody(char item[30],int qty, float price){
    printf("%s\t\t",item); 
        printf("%d\t\t",qty); 
        printf("%.2f\t\t",qty * price); 
        printf("\n");
}



void BillFooter(float total){
    printf("\n");
    float dis = 0.1*total;
    float netTotal=total-dis;
    float cgst=0.09*netTotal,grandTotal=netTotal + 2*cgst;
    printf("---------------------------------------\n");
    printf("Sub Total\t\t\t%.2f",total);
    printf("\nDiscount @10%s\t\t\t%.2f","%",dis);
    printf("\n\t\t\t\t-------");
    printf("\nNet Total\t\t\t%.2f",netTotal);
    printf("\nCGST @9%s\t\t\t%.2f","%",cgst);
    printf("\nSGST @9%s\t\t\t%.2f","%",cgst);
    printf("\n---------------------------------------");
    printf("\nGrand Total\t\t\t%.2f",grandTotal);
    printf("\n---------------------------------------\n");
}
int main(){
    
    int opt,n;
    struct orders ord;
    struct orders order;
    char saveBill = 'Y',CheckContinue = 'Y';
    char name[50];
    FILE *fp;
       
    while(CheckContinue == 'Y'){
    system("clear");			
    float total = 0;
    int invoiceFound = 0;
    printf("\t============ATRE's RESTAURANT============");
    printf("\n\nWhat operation would you like to perform?");
    printf("\n\n1.Generate Invoice");
    printf("\n2.Show all previous Invoices");
    printf("\n3.Search for an Invoice");
    printf("\n4.Exit");

    printf("\n\nOperation to be performed:\t");
    scanf("%d",&opt);
    fgetc(stdin);
    switch(opt){
        case 1:
        system("clear");
        printf("\nName of the customer: \t");
        fgets(ord.customer,50,stdin);
        ord.customer[strlen(ord.customer)-1] = 0;
        strcpy(ord.date,__DATE__);
        printf("\nNumber of items:\t");
        scanf("%d",&n);
        ord.numOfItems = n;
        for(int i=0;i<n;i++){
            fgetc(stdin);
            printf("\n\n");
            printf("Item name %d:\t",i+1);
            fgets(ord.itm[i].item,20,stdin);
            ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
            printf("Item Quantity:\t");
            scanf("%d",&ord.itm[i].qty);
            printf("Item Price per Unit:\t");
            scanf("%f",&ord.itm[i].price);
            total += ord.itm[i].qty * ord.itm[i].price;
        }

        BillHeader(ord.customer,ord.date);
        for(int i=0;i<ord.numOfItems;i++){
            BillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
        }
        BillFooter(total);

        printf("\nDo you want to save the invoice [Y/N]:\t");
        scanf("%s",&saveBill);

        if(saveBill == 'Y'){
            fp = fopen("RestaurantBill.dat","a+");
            fwrite(&ord,sizeof(struct orders),1,fp);
            if(fwrite != 0)
            printf("\nSuccessfully saved");
            else 
            printf("\nError saving");
            fclose(fp);
        }
        break;

        case 2:
        system("clear");
        fp = fopen("RestaurantBill.dat","r");
        printf("\n  *****Your Previous Invoices*****\n");
        while(fread(&order,sizeof(struct orders),1,fp)){
            float tot = 0;
            BillHeader(order.customer,order.date);
            for(int i=0;i<order.numOfItems;i++){
                BillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                tot+=order.itm[i].qty * order.itm[i].price;
            }
            BillFooter(tot);
        }
        fclose(fp);
        break;

        case 3:
        printf("Enter the name of the customer:\t");
        fgets(name,50,stdin);
        name[strlen(name)-1] = 0;
        system("clear");
        fp = fopen("RestaurantBill.dat","r");
        printf("\t*****Invoice of %s*****",name);
        while(fread(&order,sizeof(struct orders),1,fp)){
            float tot = 0;
            if(!strcmp(order.customer,name)){
            BillHeader(order.customer,order.date);
            for(int i=0;i<order.numOfItems;i++){
                BillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                tot+=order.itm[i].qty * order.itm[i].price;
            }
            BillFooter(tot);
            invoiceFound = 1;
            }
        
        }
        if(!invoiceFound){
            printf("Sorry the invoice for %s doesn't exists",name);
        }
        fclose(fp);
        break;

    case 4:
    printf("\n\t\t...Terminating Program...\n\n");
    exit(0);
    break;

    default:
    printf("Sorry invalid option");
    break;
    }
    printf("\nWould you like to perform another operation??[Y/N]:\t");
    scanf("%s",&CheckContinue);
    }
    printf("\n\t\t Bye Bye :)\n\n");
    printf("\n\n");

    return 0;
}
