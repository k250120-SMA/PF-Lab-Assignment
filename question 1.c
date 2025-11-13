#include <stdio.h>
#include <string.h>

#define Max_Books 100


void AddBooks (int isbn[Max_Books], char titles[Max_Books][50], float prices[Max_Books], int quantities[Max_Books], int *count) {
	int i= *count;
	printf("Please enter book ISBN: ");
	scanf("%d", &isbn[i]);
	
	 for (int j = 0; j < i; j++) {
        if (isbn[j] == isbn[i]) {
            printf("\nISBN already exists, please enter another: ");
            scanf("%d", &isbn[i]);
            j = -1;
        }
    }
	printf("\nPlease enter Book Title: ");
	scanf(" %[^\n]", &titles[i]);
	printf("\nEnter book price: ");
	scanf("%f", &prices[i]);
	printf("\nEnter quantity: ");
	scanf("%d", &quantities[i]);
	
	(*count)++;
	
	
	printf("\nBook added successfully:\n");
    printf("ISBN: %d\n", isbn[0]);
    printf("Title: %s\n", titles[0]);
    printf("Price: %.2f\n", prices[0]);
    printf("Quantity: %d\n", quantities[0]);
}
void ProcessSale(int isbn[], char titles[][50], float prices[], int quantities[], int count) {
    int search_isbn, copies_sold;
    float total_amount = 0;
    
    if (count == 0) {
        printf("No books in inventory! Cannot process sale.\n");
        return;
    }
    
    printf("\n=== PROCESS BOOK SALE ===\n");
    
    // Step 1: Ask for ISBN
    printf("Enter ISBN of the book to sell: ");
    scanf("%d", &search_isbn);
    
    // Step 2: Search for the book
    int found_index = -1;
    for (int i = 0; i < count; i++) {
        if (isbn[i] == search_isbn) {
            found_index = i;
            break;
        }
    }
    
    if (found_index == -1) {
        printf("Error: Book with ISBN %d not found in inventory!\n", search_isbn);
        printf("Sale cancelled.\n");
        return;
    }
    
    // Step 3: Display book information
    printf("\nBook Found:\n");
    printf("Title: %s\n", titles[found_index]);
    printf("Price per copy: $%.2f\n", prices[found_index]);
    printf("Current stock: %d copies\n", quantities[found_index]);
    
    // Check if already out of stock
    if (quantities[found_index] == 0) {
        printf("Error: This book is OUT OF STOCK!\n");
        printf("Sale cancelled.\n");
        return;
    }
    
    // Step 4: Ask for number of copies to sell
    printf("\nEnter number of copies to sell: ");
    scanf("%d", &copies_sold);
    
    // Step 5: Validate the quantity
    if (copies_sold <= 0) {
        printf("Error: Number of copies must be positive!\n");
        printf("Sale cancelled.\n");
        return;
    }
    
    if (copies_sold > quantities[found_index]) {
        printf("Error: Not enough stock! Only %d copies available.\n", quantities[found_index]);
        printf("Sale cancelled.\n");
        return;
    }
    
    // Step 6: Calculate total amount
    total_amount = copies_sold * prices[found_index];
    
    // Step 7: Display sale summary
    printf("\n=== SALE SUMMARY ===\n");
    printf("Book: %s\n", titles[found_index]);
    printf("ISBN: %d\n", isbn[found_index]);
    printf("Price per copy: $%.2f\n", prices[found_index]);
    printf("Copies sold: %d\n", copies_sold);
    printf("Total amount: $%.2f\n", total_amount);
    
    // Step 8: Confirm the sale
    char confirm;
    printf("\nConfirm sale? (y/n): ");
    scanf(" %c", &confirm);
    
    if (confirm == 'y' || confirm == 'Y') {
        // Step 9: Update inventory
        quantities[found_index] -= copies_sold;
        
        // Step 10: Display final result
        printf("\n=== SALE COMPLETED SUCCESSFULLY ===\n");
        printf("Book: %s\n", titles[found_index]);
        printf("Copies sold: %d\n", copies_sold);
        printf("Total revenue: $%.2f\n", total_amount);
        printf("Remaining stock: %d copies\n", quantities[found_index]);
        
        // Stock status after sale
        if (quantities[found_index] == 0) {
            printf("WARNING: This book is now OUT OF STOCK!\n");
        } else if (quantities[found_index] <= 3) {
            printf("WARNING: Very low stock! Only %d copies remaining.\n", quantities[found_index]);
        } else if (quantities[found_index] <= 10) {
            printf("Note: Low stock alert - %d copies remaining.\n", quantities[found_index]);
        }
    else {
        printf("Sale cancelled by user.\n");
    }
}
}

void GenerateLowStockReport(int isbn[], char titles[][50], float prices[], int quantities[], int count) {
    int low_stock_count = 0;
    
    printf("\n=== LOW-STOCK REPORT (Quantity < 5) ===\n");
    
    for (int i = 0; i < count; i++) {
        if (quantities[i] < 5) {
            low_stock_count++;
            printf("%d. ISBN: %d, Title: %-30s, Price: $%-6.2f, Quantity: %d",
                   low_stock_count, isbn[i], titles[i], prices[i], quantities[i]);
            
            if (quantities[i] == 0) {
                printf(" [OUT OF STOCK]");
            } else if (quantities[i] <= 2) {
                printf(" [URGENT]");
            } else {
                printf(" [LOW STOCK]");
            }
            printf("\n");
        }
    }
    
    if (low_stock_count == 0) {
        printf("No low-stock books found. All books have sufficient quantity.\n");
    } else {
        printf("\nTotal low-stock books: %d\n", low_stock_count);
    }
}

int main(){
	int isbn[Max_Books]; 
	char titles[Max_Books][50];
	float prices[Max_Books];
	int quantities[Max_Books];
	int i=0;
	int j=0;
	int count=0;
	int choice;
	do{
	printf("--------Liberty Books Management--------");
	printf("\n1. Add new books to inventory.");
	printf("\n2. Process a sale.");
	printf("\n3. Generate a low stock report.");
	printf("\n4. Exit.");
	printf("\nPlease enter your choice: ");
	scanf("%d", &choice);
	
	
	switch (choice) {
	
	case 1:
	    AddBooks(isbn, titles, prices, quantities, &count);
	    break;
	
	case 2:
		ProcessSale(isbn, titles, prices, quantities, count);
		break;
	
	case 3:
		GenerateLowStockReport(isbn, titles, prices, quantities, count);
        break;
}
} while(choice!=4);

    

	return 0;
}

