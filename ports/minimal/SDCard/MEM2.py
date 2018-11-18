def mem():
  try:
    l=[]
    try:
      l+=[0]
      while True:
        try:
          l=l+l[l[0]:]
        except:
          if l[0]<len(l)-1:
            l[0]=len(l)-1
          else:
            raise(Exception)
    except:
      print("+",len(l))
      return 64+8*len(l)+mem()
  except:
    return 0