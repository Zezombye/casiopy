#platforms: (0)TI-Nspire (1)NumWorks (2)Graph 90+E (3)Graph 75+E (4)TI-Python
plines=[29,12,  7, 9,11]
pcols =[53,99,509,32,32]
try:
  import sys
  try:
    if sys.platform=='nspire': platform=0
    if sys.platform=='TI-Python Adapter': platform=4
    platform=0
  except: platform=3
except:
  try:
    import kandinsky
    platform=1
  except:
    platform=2

nlines=plines[platform]
ncols=pcols[platform]
curline=0

def mprint(*ls):
  global curline
  st=""
  for s in ls:
    if not(isinstance(s,str)):
      s=str(s)
    st=st+s
  stlines=1+int(len(st)/ncols)
  if curline+stlines>=nlines:
    input("Input to continue:")
    curline=0
  print(st)
  curline+=stlines

def sstr(obj):
  try:
    s=obj.__name__
  except:
    s=str(obj)
    a=s.find("'")
    b=s.rfind("'")
    if a>=0 and b!=a:
      s=s[s.find("'")+1:s.rfind("'")]
  return s

def explmod(pitm,pitmsl=[],reset=True):
  global curline
  if(reset):
    curline=0
    pitmsl=[sstr(pitm)]
  hd="."*(len(pitmsl)-1)
  spath=".".join(pitmsl)
  c=0
  for itms in sorted(dir(pitm)):
    c=c+1
    try:
      itm=eval(spath+"."+itms)
      mprint(hd+itms+"="+str(itm))
      if spath.rfind(itms)<0:
        pitmsl2=pitmsl.copy()
        pitmsl2.append(itms)
        c=c+explmod(itm,pitmsl2,False)
    except:
      mprint(hd+itms)
  if c>0:
    mprint(hd+"Total: "+str(c)+" item(s)")
  return c