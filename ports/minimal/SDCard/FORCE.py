mrandmax=2147483647
mrand=0
def mfloor(f):
  return round(f)-(round(f)>f)
def mceil(f):
  return round(f)+(round(f)<f)
def mseed(s):
  global mrand
  mrand=s%mrandmax
def mrandom():
  mseed(mrand*16807)
  return mrand/mrandmax
def muniform(mini,maxi):
  return mrandom()*(maxi-mini)+mini
def mrandint(mini,maxi):
  return round(muniform(mceil(mini),mfloor(maxi)))
mfmax=93
def f2mf(f):
  return round(f*mfmax)
def mf2f(n):
  return float(n/mfmax)
def smf(l):
  s=""
  for k in range(len(l)):
    s=s+chr(33+l[k])
  return s
def bitand(a,b):
  return a&b
mseed(42)
st=[252,30,0,0,0,0,0,21]
sla=[0]*st[0]
ll=[f2mf(0)]*st[0]
ls=[f2mf(0)]*st[1]
for k in range(st[0]):
  sla[k]=mrandint(0,2**st[1]-1)
def ist(l):
  r=-1
  for k in range(len(l)):
    r=pot(k,mf2f(ord(l[k])-33),k>=len(l)-1)
  return r
def pst(s,d):
  li=["Allumees",str(st[3])+"/"+str(st[0]),"Grillees",str(st[6])+"/"+str(st[0]),"Aliment.",str(mf2f(st[2])),"Pertes",str(mf2f(st[5])),"Gaspill.",str(mf2f(st[4])),"Score",str(s),""]
  if d:
    t=""
    for j in range(st[0]):
      t=t+" O"[f2mf(1)<=ll[j]<f2mf(2)]
      if j%st[7]==st[7]-1 or j==st[0]-1:
        print(t+"|"+li[mfloor(j/st[7])])
        t=""
  ss="Score    : "+str(s)
  if d:
    while len(ss)<22:
      ss=ss+" |"[len(ss)==21]
    ss+=li[len(li)-1]
  return ss
def setst(k,v):
  global st
  st[k]=v
def setll(k,v):
  global ll
  ll[k]=v
def setls(k,v):
  global ls
  ls[k]=v
def setcode(v):
  global code
  code=v
def pot(k,v=1,d=True):
  if k>=0 and k<st[1]:
    v=f2mf(max(min(v,1),0))
    setst(2,st[2]+v-ls[k])
    for l in range(st[0]):
      if bitand(sla[l],2**k):
        ol=ll[l]
        setll(l,ll[l]+v-ls[k])
        setst(3,st[3]+((f2mf(1)<=ll[l]<=f2mf(2)) and ((ol<f2mf(1)) or (ol>f2mf(2))))-(((ll[l]<f2mf(1)) or (ll[l]>f2mf(2))) and (f2mf(1)<=ol<=f2mf(2))))
        setst(4,st[4]+max(ll[l]-f2mf(1),0)-max(ol-f2mf(1),0))
        setst(5,st[5]+ll[l]*(ll[l]<f2mf(1))-ol*(ol<f2mf(1)))
        setst(6,st[6]+((f2mf(2)<ll[l]) and (ol<=f2mf(2)))-((ll[l]<=f2mf(2)) and (ol>f2mf(2))))
    setls(k,v)
  s=float(st[3]-mf2f(st[2]+st[6]/2+st[4]/5+st[5]/10))
  c=smf(ls)
  setcode(c)
  ss=pst(s,d)
  if d:
    print("Bon score? Envoie le code ")
    print("suivant a info@tiplanet.org:")
  else:
    print(ss)
  print(c)
print(str(st[1])+" potentiometres poussables")
print("de 0 a 1 controlent jusqu'a")
print(str(st[0])+" lampes.")
print("Allume un max de lampes avec")
print("un minimum d'energie en en")
print("gaspillant le moins possible.")
print("Syntaxe: pot(,) avec numero de")
print("potentiometre de 0 a "+str(st[1]-1)+" et")
print("valeur de 0 a 1.")
print("Exemple: pot(3,0.8) pousse le")
print("potentiometre numero 3 a 80%.")