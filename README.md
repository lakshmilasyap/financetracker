# financetracker
#Smart Expense Tracker (C + Python)  
 Project Overview

A menu-driven expense tracking system built in C, designed to help users monitor and analyze their spending habits. The system records expenses, applies intelligent limits, and generates summaries.

Additionally, it integrates with Python for graphical visualization, making financial analysis more intuitive and visually clear.  

#Key Features  
Expense Management:  
Add, store, and view expenses with date and category.  
Smart Budget Control:  
Set initial balance  
Define category limits (Food, Travel)  
Set total spending warning threshold  
Summaries & Insights:  
Monthly summary  
Weekly summary  
Highest spending day  
Most spent category  
Comparisons:  
Month-to-month comparison  
Week-to-week comparison  
Alerts System:  
Category limit exceeded warning  
Total spending alert  
Persistent Storage:  
expenses.txt → Stores all expense records  
config.txt → Stores monthly settings  
Graph Visualization (Python Integration):  
Generates graphs for better understanding of spending trends.  
Data Control:
Delete all expenses with confirmation.  
Safe Input Handling:  
Prevents invalid inputs using validation functions.  

#How It Works  
User first sets up monthly configuration (balance, limits, date).  
Data is stored in config.txt.  
Expenses are added with category + date and saved in expenses.txt.  
The system dynamically calculates totals and triggers alerts.  
Summaries and comparisons can be generated anytime.  
Graphs can be visualized using Python.  
  
#Setting Up Python & Running Graph Feature  
Note  
Graph option by following given instructions works only in windows(does not work in linux)  
  
Follow these steps to enable and use the graph visualization in this project.

Step 1: Install Python  
Go to the official website:
Python  
Download the latest version.  
While installing:
Tick “Add Python to PATH”  
Click Install Now  

Step 2: Check if Python is Installed

Open terminal / command prompt and run:  
python --version  
If installed correctly, you will see something like:  
Python 3.x.x  
If not, reinstall Python and ensure PATH is enabled.  

Step 3: Install Required Library

This project uses Matplotlib for generating graphs.

Run:  
pip install matplotlib  
If that doesn’t work:  
python -m pip install matplotlib  

Step 4: Ensure Required Files Are Present

Make sure these files are in the same folder:

main.c  
graph.py  
expenses.txt (auto-created)  
config.txt (auto-created)  

Step 5: Compile and Run the C Program

Compile:  
gcc main.c  
Run:  
./a.out  

Step 6: Generate Graph  
First, use the program to:  
Add expenses  
Generate Monthly Summary (this creates daily.txt)
Then choose:  
8. Generate Graph (Python)

Note
If your system uses python3, update this line in your code:  
system("python3 graph.py");  
To continue close the graph file.

What the Graph Shows  
X-axis → Days of the month (1–31)  
Y-axis → Amount spent  
Helps identify:  
Spending patterns  
Peak expense days  
Irregular spending behavior  

#Project Structure  
main.c → Main program and menu system  
expenses.txt → Stores expenses  
config.txt → Stores monthly configurations  
daily.txt → Stores day-wise expense data  
graph.py → Python script for graph generation  

#How to Run

Compile the code:  
gcc main.c  
Run the program:  
./a.out  




