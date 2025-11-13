#include <stdio.h>
#include <string.h>

#define ROWS 5
#define COLS 5

#define POWER_STATUS 0
#define OVERLOAD_WARNING 1
#define MAINTENANCE_REQ 2

void setbit(int *sector, int Bitposition){
	*sector|=(1<< Bitposition);
}

void clearbit(int *sector, int Bitposition){
	*sector &=(1<<Bitposition);
}

int isbitset (int sector, int Bitposition) {
	return (sector>>Bitposition)&1;
}

void updatesectorstatus (int grid[ROWS][COLS]){
	int row, col, flag, action;
	
	printf("\nEnter sector coordinates (rows cols): ");
	scanf("%d %d", &row, &col);
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        printf("Invalid coordinates!\n");
        return;
    }
    printf("1. Power Status\n2. Overload Warning\n3. Maintenance Required\n");
    printf("Select flag: ");
    scanf("%d", &flag);
    
    printf("1. Set\n2. Clear\nSelect action: ");
    scanf("%d", &action);
    
    int bitPosition = flag - 1;
    
    if (action == 1) {
        setbit(&grid[row][col], bitPosition);
        printf("Bit %d SET\n", bitPosition);
    } else if (action == 2) {
        clearbit(&grid[row][col], bitPosition);
        printf("Bit %d CLEARED\n", bitPosition);
    } else {
        printf("Invalid action!\n");
    }
}

void querySectorStatus(int grid[ROWS][COLS]) {
    int row, col;
    
    printf("\nEnter sector coordinates (row col): ");
    scanf("%d %d", &row, &col);
    
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        printf("Invalid coordinates!\n");
        return;
    }
    
    int sector = grid[row][col];
    
    printf("\nSector [%d][%d] Status:\n", row, col);
    printf("Power: %s\n", isbitset(sector, POWER_STATUS) ? "ON" : "OFF");
    printf("Overload: %s\n", isbitset(sector, OVERLOAD_WARNING) ? "YES" : "NO");
    printf("Maintenance: %s\n", isbitset(sector, MAINTENANCE_REQ) ? "YES" : "NO");
}

void displayGrid(int grid[ROWS][COLS]) {
    printf("\nGrid Status [POM]:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int sector = grid[i][j];
            printf("[%d%d%d] ", 
                   isbitset(sector, POWER_STATUS),
                   isbitset(sector, OVERLOAD_WARNING),
                   isbitset(sector, MAINTENANCE_REQ));
        }
        printf("\n");
    }
}
void initializeGrid(int grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = 0;
        }
    }
    grid[0][0] = 3;
    grid[1][1] = 5;
    grid[2][2] = 1;
}
void runSystemDiagnostic(int grid[ROWS][COLS]) {
    int overloaded = 0;
    int maintenance = 0;
    
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int sector = grid[i][j];
            if (isbitset(sector, OVERLOAD_WARNING)) overloaded++;
            if (isbitset(sector, MAINTENANCE_REQ)) maintenance++;
        }
    }
    
    printf("\nSystem Diagnostic:\n");
    printf("Overloaded sectors: %d\n", overloaded);
    printf("Maintenance required: %d\n", maintenance);
}
int main(){
	int grid[ROWS][COLS];
    char choice;
    
    printf("IESCO Power Grid System\n");
    initializeGrid(grid);
    
    do {
        printf("\nMenu:\n");
        printf("U. Update Sector\n");
        printf("Q. Query Sector\n");
        printf("D. Diagnostic\n");
        printf("G. Display Grid\n");
        printf("X. Exit\n");
        printf("Choice: ");
        scanf(" %c", &choice);
        
        switch(choice) {
            case 'U': case 'u': updatesectorstatus(grid); break;
            case 'Q': case 'q': querySectorStatus(grid); break;
            case 'D': case 'd': runSystemDiagnostic(grid); break;
            case 'G': case 'g': displayGrid(grid); break;
            case 'X': case 'x': printf("Goodbye!\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 'X' && choice != 'x');
    
    return 0;
}

