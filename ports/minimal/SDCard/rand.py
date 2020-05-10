mrandmax=65537
mrand=0
def mseed(s):
  global mrand
  mrand=s%mrandmax
def mrandom():
  mseed(mrand*75)
  return mrand/mrandmax
def muniform(mini,maxi):
  return mrandom()*(maxi-mini)+mini
def mrandint(mini,maxi):
  return round(muniform(ceil(mini),floor(maxi)))