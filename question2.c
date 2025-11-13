#include <stdio.h>
#include <string.h>


#define Max_Products 20
#define Max_CartItems 10

void CustomerInfo(double *CNIC, char name[100]){
	printf("\nEnter Customer Name: ");
	scanf(" %[^\n]", name);
	printf("\nEnter customer CNIC: ");
	scanf("%lf", CNIC);

}
void DisplayInventory(int Inventory[Max_Products][3]){

	for(int i=0;i<Max_Products;i++){
		for(int j=0;j<3;j++){
			printf("%03d\t\t\t", Inventory[i][j]);
		}
		printf("\n");
	}
}

void UpdateInventory(int Inventory[Max_Products][3], int ProductCode, int Quantity){
	
    printf("Enter Product Code: ");
	scanf("%03d", &ProductCode);
	printf("Enter Quantity (with negative sign if being purchased, and with no sign if being added)");
	scanf("%d", &Quantity);
	printf("Product Code\tQuantity in Stock\t\tPrice\n");
	for(int i=0; i<Max_Products;i++){
		if(Inventory[i][0]==ProductCode){
			Inventory[i][1]=Inventory[i][1]+Quantity;
			printf("Inventory Successfully Updated.");
			return;
		} 
	}printf("Product Code Not found");
}

void AddToCart(int Cart[Max_Products][3],int Inventory[Max_Products][3], int *CartCount){
	int ProductCode, Quantity;
	
		printf("\nEnter Product Code: ");
		scanf("%03d", &ProductCode);
		printf("\nEnter Quantity: ");
		scanf("%d", &Quantity);
	
	int found = 0;
    for(int i = 0; i < Max_Products; i++) {
        if(Inventory[i][0] == ProductCode) {  
            found = 1;
            
            if(Inventory[i][1] >= Quantity) {
                Cart[*CartCount][0] = ProductCode;       
                Cart[*CartCount][1] = Quantity;           
                Cart[*CartCount][2] = Inventory[i][2];   
                
                Inventory[i][1] -= Quantity;
                
                printf("Product added to cart successfully!\n");
                printf("Product: %03d, Quantity: %d, Price: %d\n", 
                       ProductCode, Quantity, Inventory[i][2]);
                       printf("Product added to cart successfully!\n");
                printf("Product: %03d, Quantity: %d, Price: %d\n", 
                       ProductCode, Quantity, Inventory[i][2]);
                
                (*CartCount)++;
            } else {
                printf("Error: Not enough quantity available!\n");
                printf("Available quantity: %d, Requested: %d\n", 
                       Inventory[i][1], Quantity);
            }
            break;
        }
    }
    
    if(!found) {
        printf("Error: Product code %03d not found in inventory!\n", ProductCode);
    }
}
void TotalBill(int Cart[Max_Products][3], float Bill,float billPC, char promocode[], char ans, int CartCount){
	
	for (int i=0; i<CartCount; i++){
		Bill += Cart[i][1]*Cart[i][2];
	}
	
	printf("\nDoes the customer have a promocode (y,n)? ");
	scanf("%c", &ans);
	
	switch (ans) {
	case 'y':{
	    printf("\nEnter Promocode: ");
	    scanf("%[^\n]", &promocode);
	    if (promocode="Eid2025"){
	    	billPC=Bill*0.75;
	    	printf("\nYour Total Bill is %f", Bill);
		}else{printf("\nPromocode is invalid.");
		ans='n';
		}
		break;
}
    case 'n':{
    	printf("\nYour Total Bill is %f", Bill);
		break;
	}

}
	
}
void ShowInvoice(float billPC, float Bill, char promocode [7], char ans){
	if(ans=='y'){printf("Your Total Bill before discount= %f", Bill);
	printf("Your Total Bill after discount= %f", billPC);
	}else if(ans=='n'){printf("Your Total Bill= %f", Bill);
}
}


int main(){
	double CNIC;
	char name[100];
	int choice;
	int Inventory[Max_Products][3]={
	     {001, 25, 200},
	     {002, 30, 300},
	     {003, 37, 400},
	     {004, 32, 500}
	};
	int ProductCode, Quantity;
	int Cart[Max_Products][3];
	int CartCount=0;
	float Bill;
	float billPC;
	char promocode[7];
	char ans;
	
printf("Welcome to the Superstore Management System.");
printf("\nEnter Customer Information");
CustomerInfo(&CNIC,name);

do{

printf("1. Display Inventory.\n");
printf("2. Update Ineventory.\n");
printf("3. Add Item to Cart.\n");
printf("4. Show Total Bill.\n");
printf("5. Show Total Invoice.\n");
printf("6. Exit\n");
printf("What would you like to do?\n");
scanf("%d", &choice);

switch (choice) {
	
	case 1: {
		DisplayInventory(Inventory);
		break;
	}
    case 2: {
		UpdateInventory(Inventory, ProductCode, Quantity);
		break;
	}
	case 3: {
		AddToCart(Cart, Inventory, &CartCount);
		break;
	}
	case 4: {
		TotalBill(Cart, Bill, billPC, promocode, ans, CartCount);
		break;
	}
	case 5: {
		ShowInvoice(billPC, Bill, promocode, ans);
		break;
	}
}
} while (choice!=6);

return 0;
}