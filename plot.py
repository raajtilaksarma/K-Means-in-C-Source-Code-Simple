import matplotlib.pyplot as plt
f = open("x-y-cluster.csv","r")
lines = f.read().splitlines();    
f.close();
items = [];

for i in range(0,len(lines)):   
	line = lines[i].split(',');
	XYC = [];
        for j in range(len(line)):
            v = line[j]; 
            XYC.append(v);
    	items.append(XYC);
for i in range(0,len(items)):
	if(items[i][2]=='R'):
		plt.plot(float(items[i][0]),float(items[i][1]),"ro")
	elif(items[i][2]=='T'):
		plt.plot(float(items[i][0]),float(items[i][1]),"yo")
	elif(items[i][2]=='S'):
		plt.plot(float(items[i][0]),float(items[i][1]),"bo")
plt.show()
