from matplotlib import pyplot as plt

filename = "./data/time_complexity.data"

t = [] # time
y = [] # amount


c = 10
with open(filename, "r") as file:
	for line in file:
		data = line.split(",")
		amount = float(data[0])
		time = float(data[1])

		t.append(time)
		y.append(amount)

plt.plot(t,y)
plt.show()

