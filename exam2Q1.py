def doMath(x, y, z):
    a, b = x
    z0, z1 = z
    c = y
    print(a * z0 + b * z1 - c)


x = (2, 5)
y = (7)
z = (1, 3)
doMath(x, y, z)
