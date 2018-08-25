def mem():
  try:
    l = [0]
    while True:
      try:
        l = l + l[l[0]:]
      except:
        if l[0] < len(l)-1:
          l[0] = len(l)-1
        else:
          print("+", 4*len(l))
          l[0] = 4*len(l) + mem()
          break
  except:
    return 0
  return l[0]
  
mem()