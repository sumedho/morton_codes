def morton_encode3d(x, y, z):
    answer = 0
    for i in range(1,21):
        answer |= ((x & (1 << i)) << 2*i)\
               | ((y & (1 << i)) << (2*i + 1))\
               | ((z & (1 << i)) << (2*i + 2))
    return answer

def morton_encode2d(x, y):
    answer = 0
    for i in range(0, 40):
        answer |= ((x & (1 << i)) << i) | ((y & (1 << i)) << (i + 1))
    return answer

def morton_decode2d(m):
    x = 0
    y = 0
    for i in range(0, 22):
        selector = 1
        shift_selector = 2 * i
        x |= (m & (selector << shift_selector)) >> i
        y |= (m & (selector << (shift_selector + 1))) >> (i + 1)
    return x, y

def morton_decode3d(m): 
    x = 0
    y = 0
    z = 0
    for i in range(0, 22):
        selector = 1
        shift_selector = 3 * i
        shiftback = 2 * i
        x |= (m & (selector << shift_selector)) >> (shiftback)
        y |= (m & (selector << (shift_selector + 1))) >> (shiftback + 1)
        z |= (m & (selector << (shift_selector + 2))) >> (shiftback + 2)
    return x, y, z

m = morton_encode3d(1500, 10, 10)

print("Morton code for 1500, 10, 10: {0}".format(m))

x, y, z = morton_decode3d(m) 
print("Decoded 3D morton for {0} is {1} {2} {3}".format(m, x, y, z))