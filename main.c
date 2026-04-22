#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Expense {
    float amount;
    char category[20];
    char date[15];
};

// Global config
float initial_balance = 0;
float food_percent = 0, travel_percent = 0, total_percent = 0;
int curr_year = 0, curr_month = 0, curr_day = 0;

// -------- SAFE INPUT --------
void clearBuffer() {
    while (getchar() != '\n');
}

int getInt() {
    int x;
    while (1) {
        if (scanf("%d", &x) != 1) {
            printf("Invalid input! Enter number: ");
            clearBuffer();
            continue;
        }

        if (x == -1) return -1; // GO BACK

        return x;
    }
}

float getFloat() {
    float x;
    while (1) {
        if (scanf("%f", &x) != 1) {
            printf("Invalid input! Enter number: ");
            clearBuffer();
            continue;
        }

        if (x == -1) return -1; // GO BACK

        return x;
    }
}

float getPercentage() {
    float x;

    while (1) {
        if (scanf("%f", &x) != 1) {
            printf("Invalid input! Enter a number: ");
            clearBuffer();
            continue;
        }

        if (x == -1) return -1; // 🚪 GO BACK

        if (x < 0 || x > 100) {
            printf("Enter value between 0 and 100 (or -1 to cancel): ");
            continue;
        }

        return x;
    }
}

// -------- DATE VALIDATION --------
int validateDate(int y, int m, int d) {
    if (m < 1 || m > 12 || d < 1 || d > 31) return 0;
    return 1;
}

// -------- MENU --------
void menu() {
    printf("\n====== EXPENSE TRACKER PRO ======\n");
    printf("1. Set Balance & Limits\n");
    printf("2. Add Expense\n");
    printf("3. View All Expenses\n");
    printf("4. Monthly Summary\n");
    printf("5. Weekly Summary\n");
    printf("6. Monthly Comparison\n");
    printf("7. Weekly Comparison\n");
    printf("8. Generate Graph (Python)\n");
    printf("9. Delete All Expenses\n");
    printf("10. Exit\n");
    printf("Enter choice: ");
}

// -------- SET DATA --------
void setData() {
    FILE *fp = fopen("config.txt", "a");  //append mode
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter this month's initial balance (-1 to go back to menu): ");
    initial_balance = getFloat();

    if (initial_balance == -1) {
    printf("Returning to main menu.\n");
    return;
    }

    while (1) {
    printf("Enter Food limit %% (-1 to go back to menu): ");
    food_percent = getPercentage();
    if (food_percent == -1) return;

    printf("Enter Travel limit %% (-1 to go back to menu): ");
    travel_percent = getPercentage();
    if (travel_percent == -1) return;

    float total = food_percent + travel_percent;

    if (total <= 100) break;

    printf("\nTotal = %.2f%% exceeds 100%%!\n", total);
    printf("1. Re-enter\n2. Auto-adjust\n3. Go back to main menu\nEnter choice: ");

    int opt = getInt();

    if (opt == -1 || opt == 3) return;
    if (opt == 1) continue;

    if (opt == 2) {
        food_percent = (food_percent / total) * 100;
        travel_percent = (travel_percent / total) * 100;

        printf("\nAdjusted:\nFood: %.2f%%\nTravel: %.2f%%\n\n",
               food_percent, travel_percent);
        break;
    }

    printf("Invalid choice!\n");
}
    
    printf("Enter TOTAL spending warning %%: ");
    total_percent = getPercentage();

    char input[50];
    int y, m, d;

    printf("Enter today's date (YYYY-MM-DD) or -1 to go back to menu: ");
    scanf("%s", input);

    if (strcmp(input, "-1") == 0) {
    printf("Returning to main menu.\n");
    return;
    }

    if (sscanf(input, "%d-%d-%d", &y, &m, &d) != 3 || !validateDate(y, m, d)) {
        printf("Invalid date!\n");
        fclose(fp);
        return;
    }

    curr_year = y;
    curr_month = m;
    curr_day = d;

    fprintf(fp, "%d %d %.2f %.2f %.2f %.2f\n",
        curr_year, curr_month,
        initial_balance,
        food_percent,
        travel_percent,
        total_percent);


    fclose(fp);
    printf(" Data saved!\n");
}

// -------- LOAD CONFIG --------
void loadConfig() {
    FILE *fp = fopen("config.txt", "r");
    if (fp) {
        fscanf(fp, "%f %f %f %f %d %d %d",
               &initial_balance, &food_percent,
               &travel_percent, &total_percent,
               &curr_year, &curr_month, &curr_day);
        fclose(fp);
    }
}

// --------LOAD CONFIG FOR MONTH-------
int loadConfigForMonth(int year, int month) {
    FILE *fp = fopen("config.txt", "r");

    if (!fp) return 0;

    int y, m;
    float bal, food, travel, total;

    while (fscanf(fp, "%d %d %f %f %f %f",
                  &y, &m, &bal, &food, &travel, &total) != EOF) {

        if (y == year && m == month) {
            initial_balance = bal;
            food_percent = food;
            travel_percent = travel;
            total_percent = total;

            fclose(fp);
            return 1; // found
        }
    }

    fclose(fp);
    return 0; // not found
}

// -------- TOTAL SPENT --------
float getTotalSpent() {
    struct Expense e;
    FILE *fp = fopen("expenses.txt", "r");
    float total = 0;

    if (!fp) return 0;

    while (fscanf(fp, "%f %s %s",
           &e.amount, e.category, e.date) != EOF) {
        total += e.amount;
    }

    fclose(fp);
    return total;
}

// -------- ADD EXPENSE --------
void addExpense() {

    struct Expense e;
    FILE *fp = fopen("expenses.txt", "a");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter amount (-1 to go back to menu): ");
    e.amount = getFloat();
    if (e.amount == -1) return;

    printf("\n1. Food\n2. Travel\n3. Shopping\n4. Others\n5. Go back to main menu\n");
    int choice = getInt();

    if (choice == -1 || choice == 5) return;
    else if (choice == 1) strcpy(e.category, "food");
    else if (choice == 2) strcpy(e.category, "travel");
    else if (choice == 3) strcpy(e.category, "shopping");
    else strcpy(e.category, "others");

    char input[50];
    int y, m, d;

    printf("Enter date (YYYY-MM-DD) or -1 to go back to menu: ");
    scanf("%s", input);

    if (strcmp(input, "-1") == 0) return;

    if (sscanf(input, "%d-%d-%d", &y, &m, &d) != 3 || !validateDate(y, m, d)) {
        printf("Invalid date!\n");
        fclose(fp);
        return;
    }

   if (!loadConfigForMonth(y, m)) {
    printf("No config found for this timeline! Please set it first.\n");
    fclose(fp);
    return;
    }

    strcpy(e.date, input);

    fprintf(fp, "%.2f %s %s\n", e.amount, e.category, e.date);
    fclose(fp);

    printf(" Expense added!\n");

    // Calculate totals
    float total_spent = getTotalSpent();
    float total_limit = (total_percent / 100) * initial_balance;

    float food_total = 0, travel_total = 0, shopping_total = 0, others_total = 0;

    struct Expense temp;
    FILE *f = fopen("expenses.txt", "r");

    while (fscanf(f, "%f %s %s", &temp.amount, temp.category, temp.date) != EOF) {
        if (strcmp(temp.category, "food") == 0)
            food_total += temp.amount;
        else if (strcmp(temp.category, "travel") == 0)
            travel_total += temp.amount;
        else if (strcmp(temp.category, "shopping") == 0)
            shopping_total += temp.amount;
        else
            others_total += temp.amount;
    }
    fclose(f);

    // Warnings
    if (total_spent >= total_limit)
        printf("ALERT: Total spending crossed %.2f%%!\n", total_percent);

    if (food_total >= (food_percent/100)*initial_balance)
        printf("Food limit exceeded!\n");

    if (travel_total >= (travel_percent/100)*initial_balance)
        printf("Travel limit exceeded!\n");
}

// -------- VIEW --------
void viewExpenses() {
    struct Expense e;
    FILE *fp = fopen("expenses.txt", "r");

    if (!fp) {
        printf("No data.\n");
        return;
    }

    while (fscanf(fp, "%f %s %s",
           &e.amount, e.category, e.date) != EOF) {
        printf("%.2f | %s | %s\n",
               e.amount, e.category, e.date);
    }

    fclose(fp);
}

// -------- MONTH TOTAL --------
float calculateMonthTotal(int target_month, float daily[]) {
    struct Expense e;
    FILE *fp = fopen("expenses.txt", "r");

    float total = 0;

    if (!fp) return 0;

    while (fscanf(fp, "%f %s %s",
           &e.amount, e.category, e.date) != EOF) {

        int y, m, d;
        sscanf(e.date, "%d-%d-%d", &y, &m, &d);

        if (m == target_month) {
            total += e.amount;
            if (daily != NULL)
                daily[d] += e.amount;
        }
    }

    fclose(fp);
    return total;
}

// -------- WEEK TOTAL --------
float calculateWeekTotal(int week) {
    struct Expense e;
    FILE *fp = fopen("expenses.txt", "r");
    float total = 0;

    if (!fp) return 0;

    while (fscanf(fp, "%f %s %s",
           &e.amount, e.category, e.date) != EOF) {

        int y, m, d;
        sscanf(e.date, "%d-%d-%d", &y, &m, &d);

        if (d >= (week-1)*7+1 && d <= week*7)
            total += e.amount;
    }

    fclose(fp);
    return total;
}



// -------- MONTHLY SUMMARY --------
void monthlySummary() {

    int choice, month;

    printf("1. Use present month\n2. Enter manually\n");
    scanf("%d", &choice);

    if (choice == 1)
        month = curr_month;
    else {
        printf("Enter month: ");
        scanf("%d", &month);
    }

    if (!loadConfigForMonth(curr_year, month)) {
    printf("No config found for this month!\n");
    return;
    }

    float daily[32] = {0};
    float food=0, travel=0, shopping=0, others=0;

    struct Expense e;
    FILE *fp = fopen("expenses.txt", "r");

    while (fscanf(fp, "%f %s %s", &e.amount, e.category, e.date) != EOF) {
        int y,m,d;
        sscanf(e.date,"%d-%d-%d",&y,&m,&d);

        if(m==month){
            daily[d]+=e.amount;

            if(strcmp(e.category,"food")==0) food+=e.amount;
            else if(strcmp(e.category,"travel")==0) travel+=e.amount;
            else if(strcmp(e.category,"shopping")==0) shopping+=e.amount;
            else others+=e.amount;
        }
    }
    fclose(fp);

    float max_cat = food;
    char max_cat_name[20] = "Food";

    if (travel > max_cat) {
    max_cat = travel;
    strcpy(max_cat_name, "Travel");
    }
    if (shopping > max_cat) {
    max_cat = shopping;
    strcpy(max_cat_name, "Shopping");
    }
    if (others > max_cat) {
    max_cat = others;
    strcpy(max_cat_name, "Others");
    }

    float max_day_amt = 0;
    int max_day = 0;

    for (int i = 1; i <= 31; i++) {
    if (daily[i] > max_day_amt) {
        max_day_amt = daily[i];
        max_day = i;
    }
    }

    float current = food + travel + shopping + others;

    // final balance after this month
    float final_balance = initial_balance - current;

    int prev = (month==1)?12:month-1;

    //spent in only previous month
    float previous = calculateMonthTotal(prev,NULL);

    printf("\n--- Monthly Summary ---\n");

    printf("This month initial Balance: %.2f\n", initial_balance);
    printf("Current Month Spent: %.2f\n", current);
    printf("This month final Balance: %.2f\n", final_balance);
    printf("\nMost Spent Category: %s (₹%.2f)\n", max_cat_name, max_cat);
    printf("Highest Spending Day: Day %d (₹%.2f)\n", max_day, max_day_amt);
    printf("Previous Month Spent: %.2f\n", previous);

    printf("\nCategory Breakdown:\n");
    printf("Food: %.2f\nTravel: %.2f\nShopping: %.2f\nOthers: %.2f\n",
           food, travel, shopping, others);

    if(previous>0){
        float percent=((current-previous)/previous)*100;
        if(percent>0) printf(" %.2f%% MORE than last month\n",percent);
        else printf(" %.2f%% LESS than last month\n",-percent);
    }

    FILE *fd=fopen("daily.txt","w");
    for(int i=1;i<=31;i++)
        fprintf(fd,"%d %.2f\n",i,daily[i]);
    fclose(fd);
}

// -------- WEEKLY SUMMARY --------
void weeklySummary() {
    loadConfig();

    int choice, week;

    printf("1. Use present week\n2. Enter manually\n");
    scanf("%d",&choice);

    if(choice==1)
        week=(curr_day-1)/7+1;
    else{
        printf("Enter week: ");
        scanf("%d",&week);
    }

    float current=0, previous;
    float daily[8] = {0}; // 1 to 7 days

    struct Expense e;
    FILE *fp = fopen("expenses.txt", "r");

    while (fscanf(fp, "%f %s %s", &e.amount, e.category, e.date) != EOF) {
        int y,m,d;
        sscanf(e.date,"%d-%d-%d",&y,&m,&d);

        if (d >= (week-1)*7+1 && d <= week*7) {
            current += e.amount;
            int day_index = (d-1)%7 + 1;
            daily[day_index] += e.amount;
        }
    }
    fclose(fp);

    int prev=(week==1)?4:week-1;
    previous=calculateWeekTotal(prev);

    printf("\n--- Weekly Summary ---\n");
    printf("Current Week: %.2f\nPrevious Week: %.2f\n",current,previous);

    // 🔥 MOST SPENT DAY
    float max_day_amt = 0;
    int max_day = 0;

    for (int i = 1; i <= 7; i++) {
        if (daily[i] > max_day_amt) {
            max_day_amt = daily[i];
            max_day = i;
        }
    }

    printf("Highest Spending Day in Week: Day %d (%.2f)\n", max_day, max_day_amt);

    if(previous>0){
        float percent=((current-previous)/previous)*100;
        if(percent>0) printf("%.2f%% MORE than last week\n",percent);
        else printf("%.2f%% LESS than last week\n",-percent);
    }
}

// -------- COMPARISONS --------
void monthlyComparison() {
    printf("Enter two months: ");
    int m1 = getInt();
    int m2 = getInt();

    float t1 = calculateMonthTotal(m1, NULL);
    float t2 = calculateMonthTotal(m2, NULL);

    printf("\nMonth %d: %.2f\n", m1, t1);
    printf("Month %d: %.2f\n", m2, t2);

    if (t2 > t1)
        printf("Spent MORE in month %d\n", m2);
    else if(t2 < t1)
        printf("Spent LESS in month %d\n", m2);
    else
       printf("Spent equal in both months\n");
}

void weeklyComparison() {
    printf("Enter two weeks: ");
    int w1 = getInt();
    int w2 = getInt();

    float t1 = calculateWeekTotal(w1);
    float t2 = calculateWeekTotal(w2);

    printf("\nWeek %d: %.2f\n", w1, t1);
    printf("Week %d: %.2f\n", w2, t2);

    if (t1 == 0) return;

    float percent = ((t2 - t1) / t1) * 100;

    if (percent > 0)
        printf(" %.2f%% MORE in week %d\n", percent, w2);
    else
        printf(" %.2f%% LESS in week %d\n", -percent, w2);
}

//----DELETE ALL EXPENSES-----

void deleteAllExpenses() {
    char confirm;

    printf(" Are you sure you want to delete ALL expenses? (y/n): ");
    scanf(" %c", &confirm);

    if (confirm != 'y' && confirm != 'Y') {
        printf("Cancelled.\n");
        return;
    }

    FILE *fp = fopen("expenses.txt", "w");

    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    fclose(fp);
    printf(" All expenses deleted successfully!\n");
}

// -------- MAIN --------
int main() {
    int choice;

    while (1) {
        menu();
        choice = getInt();

    if (choice == -1) {
    printf("Use option 10 to exit.\n");
    continue;
     }

        switch (choice) {
            case 1: setData(); break;
            case 2: addExpense(); break;
            case 3: viewExpenses(); break;
            case 4: monthlySummary(); break;
            case 5: weeklySummary(); break;
            case 6: monthlyComparison(); break;
            case 7: weeklyComparison(); break;
            case 8: system("python graph.py"); break;
            case 9: deleteAllExpenses(); break;
            case 10: exit(0);
            default: printf("Invalid choice\n");
        }
    }
}
