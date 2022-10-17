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

#idx = int(args[2])

x_name = ["1E-1", "1E-2", "1E-3", "1E-4", "1E-5", "1E-6", "1E-7","1E-8"]
x1 = np.arange(len(x_name))

#memory=int(args[2])/1048576*int(args[3])
#p=int(args[4])

#if(args[4]=='-d'):
#    yl = 'Decompression Throughput (MB/S)'
#    na = '_de'
#else:
#    yl = 'Compression Throughput (MB/S)'
#    na = ''
filename = '../figure/rate/'+args[1]+'.pdf'

SZ2 = [com_s2[0], com_s2[1],com_s2[2],com_s2[3],
      com_s2[4],com_s2[5],com_s2[6],com_s2[7]]

SZ3 = [com_s3[0], com_s3[1],com_s3[2],com_s3[3],
      com_s3[4],com_s3[5],com_s3[6],com_s3[7]]

ZFP = [com_z[0], com_z[1],com_z[2],com_z[3],
      com_z[4],com_z[5],com_z[6],com_z[7]]

new_ZFP = [com_zn[0], com_zn[1],com_zn[2],com_zn[3],
      com_zn[4],com_zn[5],com_zn[6],com_zn[7]]

p0=plt.plot(x1, SZ2, label="SZ2",marker='o',color="#708090")
p1=plt.plot(x1, SZ3, label="SZ3",marker='o',color="#98568d",)
p2=plt.plot(x1, ZFP, color="#6495ED", label="ZFP",marker='*')
p3=plt.plot(x1, new_ZFP, color="#F4A460", label="ZFP-X",marker='*')


plt.xticks(x1, x_name, fontsize=17,rotation=30)
plt.yticks(fontsize=18)
a=plt.legend([p0[0],p1[0]], ['SZ2','SZ3'],bbox_to_anchor=(0.00, 1.01), loc=3, frameon=False,fontsize=18)
plt.legend([p2[0],p3[0]], ['ZFP','ZFP-X'],bbox_to_anchor=(1.00,1.01), loc=4, frameon=False,fontsize=18)
plt.gca().add_artist(a)

plt.ylabel("Compression Time (S)", fontsize=22)
plt.xlabel("Value-range-based Relative Error Bound", fontsize=20)
plt.savefig(filename,bbox_inches='tight')
#plt.show()
