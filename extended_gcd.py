'''
Let a and b be positive integers.

The extended Euclidean algorithm is an efficient way to find integers u,v such that

a⋅u+b⋅v=gcd(a,b)
'''


def egcd(a, b):
    x,y, u,v = 0,1, 1,0
    while a != 0:
        q, r = b//a, b%a
        m, n = x-u*q, y-v*q
        b,a, x,y, u,v = a,r, u,v, m,n
    gcd = b
    return gcd, x, y

print( egcd(26513,32321))

# 2. solution2
def egcd(a, b):
    if a == 0:
        return b, 0, 1
    else:
        gcd, x, y = egcd(b % a, a)
        return gcd, y - (b // a) * x, x


print(egcd(26513, 32321))



# 3. solution3 
p = 26513
q = 32321

g = 1 # gcd of two different primes

# note that as p*u + q*v = g
# q*v = g (mod p)
# v = g/q (mod p)

v = pow(q,-1,p)
v -= p # subtract p to make v negative 
u = (g - (q*v))//p

print(u,v)

