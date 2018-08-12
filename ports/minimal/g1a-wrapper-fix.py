import sys

addinPath = sys.argv[1]
a = open(addinPath, "r+b")
s = a.read()

str = s[0x300:0x310]

sum = 0
for i in range(8):
    sum += 256*str[2*i]+str[2*i+1]

sum %= 0x10000

byte1 = 255-(sum//256)
byte2 = 255-(sum%256)

array = bytearray(s)
array[0x16] = byte1
array[0x17] = byte2
t = bytes(array)
a.seek(0)
a.write(t)
a.close()
print("Done")