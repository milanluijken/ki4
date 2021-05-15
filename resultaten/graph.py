import matplotlib.pyplot as plt
  
###-lees bestanden in-###################### 
with open('xor51.txt', 'r') as file:
    xor51string = file.read().replace('\n', ' ')

with open('xor52.txt', 'r') as file:
    xor52string = file.read().replace('\n', ' ')

with open('xor53.txt', 'r') as file:
    xor53string = file.read().replace('\n', ' ')

with open('xor151.txt', 'r') as file:
    xor151string = file.read().replace('\n', ' ')

with open('xor152.txt', 'r') as file:
    xor152string = file.read().replace('\n', ' ')

with open('xor153.txt', 'r') as file:
    xor153string = file.read().replace('\n', ' ')

#------------------------------------------------

with open('ab51.txt', 'r') as file:
    ab51string = file.read().replace('\n', ' ')

with open('ab52.txt', 'r') as file:
    ab52string = file.read().replace('\n', ' ')

with open('ab53.txt', 'r') as file:
    ab53string = file.read().replace('\n', ' ')

with open('ab151.txt', 'r') as file:
    ab151string = file.read().replace('\n', ' ')

with open('ab152.txt', 'r') as file:
    ab152string = file.read().replace('\n', ' ')

with open('ab153.txt', 'r') as file:
    ab153string = file.read().replace('\n', ' ')

###-zet om naar lijst-###########################
xor51list = xor51string.split(" ")
xor52list = xor52string.split(" ")
xor53list = xor53string.split(" ")
xor151list = xor151string.split(" ")
xor152list = xor152string.split(" ")
xor153list = xor153string.split(" ")

###----------------------------------------------

ab51list = ab51string.split(" ")
ab52list = ab52string.split(" ")
ab53list = ab53string.split(" ")
ab151list = ab151string.split(" ")
ab152list = ab152string.split(" ")
ab153list = ab153string.split(" ")

###-verwijder laatste lege element-###############

xor51list.pop()
xor52list.pop()
xor53list.pop()
xor151list.pop()
xor152list.pop()
xor153list.pop()

###----------------------------------------------

ab51list.pop()
ab52list.pop()
ab53list.pop()
ab151list.pop()
ab152list.pop()
ab153list.pop()

###-zet om naar floats en maak list voor x as-###

count = []
for i in range(len(xor51list)):
    xor51list[i] = float(xor51list[i])
    xor52list[i] = float(xor52list[i])
    xor53list[i] = float(xor53list[i])
    xor151list[i] = float(xor151list[i])
    xor152list[i] = float(xor152list[i])
    xor153list[i] = float(xor153list[i])
    ab51list[i] = float(ab51list[i])
    ab52list[i] = float(ab52list[i])
    ab53list[i] = float(ab53list[i])
    ab151list[i] = float(ab151list[i])
    ab152list[i] = float(ab152list[i])
    ab153list[i] = float(ab153list[i])    
    count.append(i+1)

####################################################

    newxor51list = xor51list[3:]
    newxor52list = xor52list[3:]
    newxor53list = xor53list[3:]
    newxor151list = xor151list[3:]
    newxor152list = xor152list[3:]
    newxor153list = xor153list[3:]
    newab51list = ab51list[3:]
    newab52list = ab52list[3:]
    newab53list = ab53list[3:]
    newab151list = ab151list[3:]
    newab152list = ab152list[3:]
    newab153list = ab153list[3:]
    newcount = count[3:]

###-grafiek-########################################

plt.plot(newcount, newxor53list, label = "5 knopen")

plt.plot(newcount, newxor153list, label = "15 knopen")

# naming the x axis
plt.xlabel('epochs (* 10^5)')

# naming the y axis
plt.ylabel('som error^2 laatste 10^5 epochs')

# giving a title to my graph
plt.title('Xor leren met functie-type 3, 5 en 15 hidden knopen')
  
# show a legend on the plot
plt.legend()
  
# function to show the plot
plt.savefig('graphs/xor3')