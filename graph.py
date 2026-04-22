import matplotlib.pyplot as plt

days = []
amounts = []

# Read data from daily.txt
try:
    with open("daily.txt", "r") as f:
        for line in f:
            d, amt = line.split()
            days.append(int(d))
            amounts.append(float(amt))
except FileNotFoundError:
    print("Error: daily.txt not found. Run monthly summary first.")
    exit()

# Plot graph
plt.figure()
plt.plot(days, amounts, marker='o')

plt.title("Daily Expense Graph")
plt.xlabel("Day of Month")
plt.ylabel("Amount Spent")

plt.grid()

plt.show()