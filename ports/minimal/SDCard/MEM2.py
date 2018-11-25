def mem():
  try:
    l=[]
    try:
      l+=[0]
      l+=[""]
      l[1]+="x"
      while True:
        try:
          l[1]+=l[1][l[0]:]
        except:
          if l[0]<len(l[1])-1:
            l[0]=len(l[1])-1
          else:
            raise(Exception)
    except:
      print("+",len(l)>1 and len(l[1]))
      return 64+8*len(l)+(len(l) and 24+4*(l[0]>0)+(len(l)>1 and 49+len(l[1])))+mem()
  except:
    return 0