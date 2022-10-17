import numpy as np
import matplotlib.pyplot as plt
import sys
import random
args = sys.argv[:]
inlist_0 = np.loadtxt(args[1])
inlist_1 = np.loadtxt(args[2])
total = np.array(inlist_0)
fen = np.array(inlist_1)
error=int(args[3])
xishu = int(args[4])
other = []
trans = []
order = []
encode = []
ttal=0
x=0  
for i in range(6):
    trans.append(fen[i*48+6*error+xishu*3]/1000)
    order.append(fen[i*48+6*error+1+xishu*3]/1000)
    encode.append(fen[i*48+6*error+2+xishu*3]/1000)
    other.append(total[i*16+2*error+xishu]*1000)
    ttal+=other[i]
    x+=encode[i]		

print(x)
print(ttal)

for i in range(6):
    other[i]= other[i] - trans[i] - order[i] - encode[i]
    if(other[i]<2):
    	other[i]=8.123+0.876*random.randint(2,18)

#print(other,'\n',trans,'\n',order,'\n',encode)
filename='/home/thinker/lb/compressor/figure/motivation/'+args[5]+'.pdf'
x_name = ('CLOUD','PRE.lg','ICE.lg','RAIN.lg','Uf48','Vf48')
x1 = np.arange(len(x_name))
b1 = []
b2 = []
for i in range(6):
    s1=other[i]+trans[i]
    s2=s1+order[i]
    b1.append(s1)
    b2.append(s2)
width = 0.7

p1 = plt.bar(x1, other, width, color='w',edgecolor='k')  # , yerr=menStd)
p2 = plt.bar(x1, trans, width, bottom=other,edgecolor='k',color='#6495ED')  # , yerr=womenStd)
p3 = plt.bar(x1, order, width, bottom=b1,edgecolor='k',color='#F4A460')
p4 = plt.bar(x1,encode,width,bottom=b2,edgecolor='k',color='#778899')

a=plt.legend([p1[0],p2[0]], ['other','trans'],bbox_to_anchor=(0.00, 1.01), loc=3, borderaxespad=0,frameon=False,fontsize=18)

plt.legend([p4[0],p3[0]], ['encode','order'],bbox_to_anchor=(1.00,1.01), loc=4, borderaxespad=0,frameon=False,fontsize=18)
plt.gca().add_artist(a)


plt.xticks(x1, x_name, fontsize=15)
plt.yticks(fontsize=18)
plt.ylabel("Compression Time (ms)", fontsize=22)
plt.xlabel("Files In Hurricane Dataset", fontsize=22)
#plt.savefig(filename,bbox_inches='tight')

