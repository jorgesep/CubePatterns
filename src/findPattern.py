p=[ [11] , \
    [11,19], \
    [11,17], \
    [11,13], \
    [11,14], \
    [11,13,18], \
    [11,13,19], \
    [11,14,19], \
    [8,11,12], \
    [11,17,19], \
    [11,12,19], \
    [11,15,19], \
    [8,11,19], \
    [11,12,15,19,24], \
    [9,11,17,19], \
    [11,13,14,19], \
    [8,10,12,15], \
    [11,12,13,19], \
    [9,11,12,15,19,24], \
    [8,11,12,15,19,24], \
    [8,10,12,15,18], \
    [9,11,12,14,15,19,24], \
    [11,12,13,14,15,19,24],\
    [9,11,12,13,14,15,17,19], \
    [11,12], \
    [8,9,10,11,12,15,19,20,24], \
    [8,9,10,11,12,13,15,19,20,21,24] ]

cnt = 1
for i in p:
    m=0
    s=''
    for j in i:
        s = s + '|' + str(j)
        m |= 1<<j
    #print "%d \t %s \t %s \t %d" % (cnt, s, bin(m)[2:].zfill(27),m)
    print "%d \t %d \t\t %s \t %s" % (cnt, m, bin(m)[2:].zfill(27),s)
    cnt +=1



