#python3 draw.py NYX 2 536870912 4
import numpy as np
import matplotlib.pyplot as plt
import sys
args = sys.argv[:]
error =["1E-1", "1E-2", "1E-3", "1E-4","1E-5","1E-6","1E-7","1E-8"]
inlist_0 = [[]]*8
inlist_1 = [[]]*8
inlist_2 = [[]]*8
inlist_3 = [[]]*8


for i in range(8) :
    path='../experiment_data/SZ2/'+args[1]+'/'+error[i]
    inlist_0[i] = np.loadtxt(path)
for i in range(8) :
    path='../experiment_data/SZ3/'+args[1]+'/'+error[i]
    inlist_1[i] = np.loadtxt(path)
for i in range(8) :
    path='../experiment_data/ZFP/'+args[1]+'/'+error[i]
    inlist_2[i] = np.loadtxt(path)
for i in range(8) :
    path='../experiment_data/ZFP-X/'+args[1]+'/'+error[i]
    inlist_3[i] = np.loadtxt(path)

data0 = [[]]*8
data1 = [[]]*8
data2 = [[]]*8
data3 = [[]]*8
for i in range(8) :
    data0[i] = np.array(inlist_0[i])
for i in range(8) :
    data1[i] = np.array(inlist_1[i])
for i in range(8) :
    data2[i] = np.array(inlist_2[i])
for i in range(8) :
    data3[i] = np.array(inlist_3[i])

com_s2 = [0 for i in range(8)]
com_s2_d = [0 for i in range(8)]
com_s3 = [0 for i in range(8)]
com_s3_d = [0 for i in range(8)]
com_z = [0 for i in range(8)]
com_z_d = [0 for i in range(8)]
com_zn = [0 for i in range(8)]
com_zn_d = [0 for i in range(8)]

for i in range(8):
    for j in range(0,len(data0[0]),2):
        com_s2[i] += data0[i][j]
        com_s2_d[i] += data0[i][j+1]
for i in range(8):
    for j in range(0,len(data1[0]),2):
        com_s3[i] += data1[i][j]
        com_s3_d[i] += data1[i][j+1]
for i in range(8):
    for j in range(0,len(data2[0]),2):
        com_z[i] += data2[i][j]
        com_z_d[i] += data2[i][j+1]
for i in range(8):
    for j in range(0,len(data3[0]),2):
        com_zn[i] += data3[i][j]
        com_zn_d[i] += data3[i][j+1]

idx = int(args[2])

x_name = [[]]*4
x_name[0] = ["1E-1", "1E-2", "1E-3", "1E-4"]
x_name[1] = ["1E-2", "1E-3", "1E-4", "1E-5"]
x_name[2] = ["1E-3", "1E-4", "1E-5", "1E-6"]
x_name[3] = ["1E-4", "1E-5", "1E-6", "1E-7"]
x1 = np.arange(len(x_name[idx]))

memory=int(args[3])/1048576*int(args[4])
#p=int(args[4])

if(args[5]=='-d'):
    yl = 'Decompression Throughput (MB/S)'
    na = '_de'
else:
    yl = 'Compression Throughput (MB/S)'
    na = ''
filename = '../figure/' +args[2]+'/'+args[1] + na + '.pdf'

SZ2=[[]]*4
SZ2[0]= [memory/com_s2[0], memory/com_s2[1],memory/com_s2[2],memory/com_s2[3]]
SZ2[1]= [memory/com_s2[1], memory/com_s2[2],memory/com_s2[3],memory/com_s2[4]]
SZ2[2]= [memory/com_s2[2], memory/com_s2[3],memory/com_s2[4],memory/com_s2[5]]
SZ2[3]= [memory/com_s2[3], memory/com_s2[4],memory/com_s2[5],memory/com_s2[6]]

SZ3=[[]]*4
SZ3[0]= [memory/com_s3[0], memory/com_s3[1],memory/com_s3[2],memory/com_s3[3]]
SZ3[1]= [memory/com_s3[1], memory/com_s3[2],memory/com_s3[3],memory/com_s3[4]]
SZ3[2]= [memory/com_s3[2], memory/com_s3[3],memory/com_s3[4],memory/com_s3[5]]
SZ3[3]= [memory/com_s3[3], memory/com_s3[4],memory/com_s3[5],memory/com_s3[6]]

ZFP=[[]]*4
ZFP[0]= [memory/com_z[0], memory/com_z[1],memory/com_z[2],memory/com_z[3]]
ZFP[1]= [memory/com_z[1], memory/com_z[2],memory/com_z[3],memory/com_z[4]]
ZFP[2]= [memory/com_z[2], memory/com_z[3],memory/com_z[4],memory/com_z[5]]
ZFP[3]= [memory/com_z[3], memory/com_z[4],memory/com_z[5],memory/com_z[6]]

new_ZFP=[[]]*4
new_ZFP[0]= [memory/com_zn[0], memory/com_zn[1],memory/com_zn[2],memory/com_zn[3]]
new_ZFP[1]= [memory/com_zn[1], memory/com_zn[2],memory/com_zn[3],memory/com_zn[4]]
new_ZFP[2]= [memory/com_zn[2], memory/com_zn[3],memory/com_zn[4],memory/com_zn[5]]
new_ZFP[3]= [memory/com_zn[3], memory/com_zn[4],memory/com_zn[5],memory/com_zn[6]]

width = 0.15
p0=plt.bar(x1, SZ2[idx], width, label="SZ2",edgecolor='k',color="#708090")
p1=plt.bar(width+x1+0.04, SZ3[idx], width, label="SZ3",edgecolor='k',color="#98568d",)
p2=plt.bar(x1+width+width+0.08, ZFP[idx], width,  color="#6495ED", label="ZFP",edgecolor='k',)
p3=plt.bar(x1+width*3+0.12, new_ZFP[idx], width, color="#F4A460", label="ZFP-X",edgecolor='k')

# Compression throughput on average 
# zzz,r=0,0
# for i in range(4): 
    # zzz+=ZFP[2][i]
    # r+=new_ZFP[2][i]
    # print(new_ZFP[2][i]/ZFP[2][i])
# print(r/zzz)

plt.xticks(x1+1.5*width+0.06, x_name[idx], fontsize=18)
plt.yticks(fontsize=18)
a=plt.legend([p0[0],p1[0]], ['SZ2','SZ3'],bbox_to_anchor=(0.00, 1.01), loc=3, frameon=False,fontsize=18)
plt.legend([p2[0],p3[0]], ['ZFP','ZFP-X'],bbox_to_anchor=(1.00,1.01), loc=4, frameon=False,fontsize=18)
plt.gca().add_artist(a)

plt.ylabel(yl, fontsize=22)
#plt.xlabel("Relative Error bound", fontsize=22)
plt.savefig(filename,bbox_inches='tight')
#plt.show()
