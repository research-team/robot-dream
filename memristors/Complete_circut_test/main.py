import matplotlib.pyplot as plt

f = open('Main.TNO', 'r')
#f = open('Data.txt', 'r')
data=[]
noshiftdata=[]
p1=[]
p2=[]
T0=0.0049
T1=0.005
lp1=0;
lp2=0;
s=f.readline()
d=[]
res=[]
while '(Secs)' not in s:
    s = f.readline()
s = f.readline()
print s
while (s!="")and(' ' in s):
    #print s
    d=map(float,s.split())
    #rint d
    data.append(d)
    #print data
    if d[1]>3.6:
        if (d[0]-lp1)>T0:
            p1.append(d)
            lp1=d[0]
    if d[2]==5:
        if (d[0]-lp2)>T1:
            p2.append(d)
            lp2=d[0]
    s=f.readline()
#rising g_inp
#print p1
#rising g_pul
#print p2
for d in p1:
    if d in p2:
        res.append(d)
print res
ind1=p1.index(res[1])#g_inp pulses
ind2=p2.index(res[1])#g_pul pulses
#print [ind1,ind2]
x=[]
sombrero=[]
hebb=[]

while p1[ind1][0]-p2[ind2][0]<T1:
    cur1=p1[ind1]
    cur2=p2[ind2]
    #rint cur1
    #print cur2
    i1=data.index(cur2)
    i2=data.index(p2[ind2+1])
    #print [i1,i2]
    maxs=data[i1]
    minh=data[i1]
    #print data[i1:i2]
    for d in data[i1:i2]:
        if d[3]>maxs[3]:
            maxs=d
        if d[4]>minh[4]:
            minh=d
    x.append(cur2[0]-cur1[0])
    sombrero.append(maxs[3])
    hebb.append(minh[4])
    ind1-=1
    ind2-=1
#print sombrero
x.reverse()
sombrero.reverse()
hebb.reverse()
#print x
ind1=p1.index(res[1])#g_inp pulses
ind2=p2.index(res[1])#g_pul pulses
while p2[ind2][0]-p1[ind1][0]<T1:
    cur1=p1[ind1]
    cur2=p2[ind2]
    cur3=p2[ind2+1]
    #rint cur1
    #print cur2
    i1=data.index(cur2)
    i2=data.index(cur3)
    #print [i1,i2]
    maxs=data[i1]
    minh=data[i1]
    #print data[i1:i2]
    for d in data[i1:i2]:
        if d[3]>maxs[3]:
            maxs=d
        if d[4]>minh[4]:
            minh=d
    x.append(cur2[0]-cur1[0])
    sombrero.append(maxs[3])
    hebb.append(minh[4])
    ind1+=1
    ind2+=1
#print x
#smb=plt.plot(x,sombrero)
#plt.setp(smb, color='r', linewidth=2.0)
heb=plt.plot(x,hebb)
plt.setp(heb, color='g', linewidth=2.0)
plt.show()
#print sombrero
#print hebb
#print p1[ind1]
#print p2[ind2]
#T v($G_PULSE) v($G_INPUT1) v($G_SOMBRERO)  v($G_HEBB)
#>1.8