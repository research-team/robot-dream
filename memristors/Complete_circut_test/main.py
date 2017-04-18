f = open('Data.txt', 'r')
data=[]
noshiftdata=[]
p1=[]
p2=[]
T0=0.0049
T1=0.005
lp1=0;
lp2=0;
s=f.readline()
while s!="":
    #print s
    d=map(float,s.split())
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
#print p1
#print p2
res=[]
for d in p1:
    if d in p2:
        res.append(d)
print res
ind1=p1.index(res[1])
ind2=p2.index(res[1])
print ind1
print ind2
while p1[ind1][0]-p2[ind2][0]<T1:
    
    ind1-=1
    ind2-=1
print p1[ind1]
print p2[ind2]
#T v($G_PULSE) v($G_INPUT1) v($G_SOMBRERO)  v($G_HEBB)
#>1.8
