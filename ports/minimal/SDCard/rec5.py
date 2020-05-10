import math
i=1j

sqrt=math.sqrt
sin=math.sin
cos=math.cos
exp=math.exp
pi=math.pi
log=math.log

def dem(legende):
    #demande et convertit en int ou float
    a=input(legende)
    a=eval(a)
    if a==int(a):
        return int(a)
    else:
        return a

def signe(x):
    if x>0:
        return 1
    elif x<0:
        return -1
    else:
        return 1

def fact(n):
    a=1
    for k in range(2,n+1):
        a*=k
    return a

def binom(n,k,p):
    return fact(n)/(fact(k)*fact(n-k))*p**k*(1-p)**(n-k)

def frac(x):
    precision=10**-8
    #retourne la tableau [str_fraction,int_num,int_denom] ou None
    maxi=10000
    q=abs(x)
    y,b,d,s,n=q,1,1,0,int(q)
    signe=1
    if x<0:
        signe=-1
    if y<10**-12:
        return ["0",0,1]
    else:
        while abs(y-n/d)>precision:
            s=q%b
            n=y//b
            d=1//b
            q=b
            b=s
        n=int(abs(n))
        d=int(abs(d))
        if n<maxi and d<maxi:
            ch = str(signe*n)
            if d>1:
                ch+="/"+str(d)
            return [ch,n,d]

def extraire_carres(a):
    b=int(sqrt(a))
    for k in range(b-1):
        c=b-k
        if a//c**2==a/c**2:
            return c
    return 1

def quadra(x):
    n=30
    for a in range(1,n):
        for c in range(1,n):
            b1=(c*x-a)**2
            if entier(b1):
                s=signe(c*x-a)
                return mf(a,s,int(b1),c)
            b2=(c*x+a)**2
            if entier(b2):
                s=signe(c*x+a)
                return mf(-a,s,int(b2),c)

def pgcd(a,b):
    while b!=0:
        r=a%b
        a,b=b,r
    return a

def egal(a,b):
    return abs(a-b)<10**-10

def entier(x):
    return egal(x,int(x))

def monome(valeur_coeff,devant_coeff,nom_variable):
    stock=""
    if not egal(valeur_coeff,0):
        if egal(valeur_coeff,1):
                if nom_variable=="":
                    stock=devant_coeff+"1";
                else:
                    stock=devant_coeff+nom_variable
        elif egal(valeur_coeff,-1):
            if nom_variable=="":
                stock="-1"
            else:
                stock="-"+nom_variable
        else:
            if valeur_coeff<0:
                stock=str(valeur_coeff)+nom_variable
            else:
                stock=devant_coeff+str(valeur_coeff)+nom_variable
    return stock

def somme_monomes(tab_coeff,tab_variables):
    #cette fonction renvoie somme des coeff* variable
    stock=""
    entre_les_chaines=""
    n=len(tab_coeff)
    for i in range(n):
        if tab_coeff[i]!=0 and i>0:
            entre_les_chaines="+"
        stock=stock+monome(tab_coeff[i],entre_les_chaines,tab_variables[i])
    if stock[0]=="+":
        stock=stock[1:]
    if(stock==""):
        stock="0"
    return stock

def mf(a,s,b,c):
    #met en forme (a+s*rac(b))/c avec s=+ou-1
    d=extraire_carres(b)
    b1=b//d**2
    p=pgcd(a,d)
    p=pgcd(p,c)
    a1=a//p
    d1=d//p
    c1=c//p
    r="*sqrt("
    if s*d1==1 or s*d1==-1:
        r="sqrt("
    r=somme_monomes([a1,s*d1],["",r+str(b1)+")"])

    if c1!=1:
        r="("+r+")/"+str(c1)
    return r

def taux(str_f,a,b):
    f1=str_f.replace("exp","###")
    f2=str_f.replace("exp","###")
    f1=f1.replace("x","("+str(b)+")")
    f2=f2.replace("x","("+str(a)+")")
    f1=f1.replace("###","exp")
    f2=f2.replace("###","exp")
    d="("+f1+"-("+f2+"))/("+str(b)+"-("+str(a)+"))"
    return eval(d)

def derivee(str_f,a):
    #évalue la dérivée en a de str_f : ex :derivee("x**2",4)
    h=10**-2
    A=taux(str_f,a-h/2,a+h/2)
    B=taux(str_f,a-h,a+h)
    return (A-0.25*B)/0.75

def rec(*args):
     #fonction qui tente de reconnaitre le nombre x rÃ©el
    L=["pi","rac","exp","ln","quad"]
    if len(args)>1:
        L=args[1]
    z=args[0]
    #x=complex(z).real
    x=float(z.real)
    #y=complex(z).imag
    y=float(z.imag)
    t=False
    if egal(y,0):#cas des rÃ©els
        a=frac(x)
        if a!=None:#fraction
            t=True
            return a[0]

        if "pi" in L:
            a=frac(x/pi)
            if a!=None:#fraction*pi
                t=True
                if a[0]=="1" or a[0]=="-1":
                    return monome(int(a[0]),"","pi")
                else:
                    return a[0]+"*pi"

        if "rac" in L:
            a=frac(x**2)
            if a!=None:#racine d'une fraction ecrite sous la forme a*rac(b)
                t=True
                s=signe(x)
                c=a[1]
                d=a[2]
                a=extraire_carres(c*d)
                b=c*d//(a**2)
                a=frac(s*a/d)
                if a[0]=="1" or a[0]=="-1":
                    return monome(int(a[0]),"","sqrt("+str(b)+")")
                else:
                    return a[0]+"*sqrt("+str(b)+")"

        if "ln" in L:
            b=exp(x)
            a=frac(b)
            if a!=None:#ln(fraction)
                t=True
                if a[1]==1:
                    return "-ln("+str(a[2])+")"
                else:
                    return "ln("+a[0]+")"

        if "exp" in L and x>0:
            b=log(x)
            a=frac(b)
            if a!=None:#exp(fraction)
                t=True
                return "exp("+a[0]+")"

        if "quad" in L:
            a=quadra(x)
            if a!=None:
                t=True
                return a
        if not t:
            return str(round(x,3))

    else:#cas des complexes
        b=rec(y,["rac","pi"])
        if egal(x,0):#imag pur
            if "." not in b:
                if b=="1" or b=="-1":
                    return monome(int(b),"","i")
                else:
                    return b+"*i"
        else:
            a=rec(x,["rac","pi"])
            if "." not in b and (b=="1" or b=="-1"):
                return somme_monomes([1,int(b)],[a,"i"])
            else:
                s=signe(eval(b))
                if s>0:
                    return a+monome(1,"+",b+"*i")
                else:
                    return a+monome(1,"",b+"*i")