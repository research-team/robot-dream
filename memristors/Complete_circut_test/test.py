import matplotlib.pyplot as plt

#f = open('Main.TNO', 'r')
f = open('Data2.txt', 'r')
data=[]
p1=[]
p2=[]
T0=0.0048
T1=0.0049
Pdt=0.01
lp1=0;
lp2=0;
s=f.readline()
d=[]
res=[]
#while '(Secs)' not in s:
#    s = f.readline()
#s = f.readline()
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
print "Data done!"
#rising g_inp
#print p1
#rising g_pul
#print p2
x=[]
sombrero=[]
hebb=[]
for p2p in p2:
    ind=p2.index(p2p)
    p1p=p1[ind]
    if (ind+1)< len(p2):
        p2p1 = p2[ind+1]
    else:
        p2p1=data[len(data)-1]
    dt=p2p[0]-p1p[0]+Pdt
    x.append(dt)
    ind1=data.index(p2p)
    ind2 = data.index(p2p1)
    maxs=p2p[3]
    maxh=p2p[4]
    minh = p2p[4]
    for d in data[ind1:ind2]:
        if d[3]>maxs:
            maxs=d[3]
        if (dt%T0)<=(T0/2):
            if maxh>d[4]:
                maxh=d[4]
        else:
            if maxh<d[4]:
                maxh=d[4]
    sombrero.append(maxs)
    hebb.append(maxh)
x.remove(x[0])
sombrero.remove(sombrero[0])
hebb.remove(hebb[0])
#smb=plt.plot(x,sombrero)
#plt.setp(smb, color='r', linewidth=2.0)
heb=plt.plot(x,hebb)
plt.setp(heb, color='g', linewidth=2.0)
plt.show()
