# Read a matrix prototype from stdin and produce .alist file
# http://luci.subsignal.org/~jow/802.11n-2009.pdf

import sys
import csv
import re
import os
import numpy as np

if len(sys.argv) < 3:
    print('Provide the .txt file containing the matrix prototype as the first argument and the destination .alist file as the second argument')
    sys.exit(-1)

mat_txt = sys.argv[1]
alist_txt = sys.argv[2]
H_csv_out = ""

# Optional 3rd argument holds dst of complete matrix
if len(sys.argv) > 3:
    H_csv_out = sys.argv[3]


print('Processing file: ', mat_txt)

# Extract N, Z and R from the filename
# File format n0-z0-r0_0.txt
# n([0-9]+)-z([0-9]+)-r([0-9]+)_([0-9]+)
mat_fn = os.path.basename(mat_txt)
matchObj = re.match( r'n([0-9]+)-z([0-9]+)-r([0-9]+)_([0-9]+)', mat_fn, re.M|re.I)

N = int(matchObj.group(1))
Z = int(matchObj.group(2))
r1 = int(matchObj.group(3))
r2 = int(matchObj.group(4))
R = r1/r2

#print('File: ', mat_fn)
#print('N: ', N)
#print('Z: ', Z)
#print('R: ', R)

reader = csv.reader(open(mat_txt), delimiter=" ")
result = [[item for item in row if item != ''] for row in reader]
matlist = list(result)


ROWS = len(matlist)
COLS = len(matlist[0])

# Check if N is the same in all rows (sanity check)
for row in matlist:
    if len(row) != COLS:
        print('Inconsistent number of elements: ', len(row), ' expected COLS=', COLS)
        sys.exit(-1)


#print('Rows: ', ROWS)
#print('Columns: ', COLS)

# Replace '-' with -1
for idx_r, row in enumerate(matlist):
    for idx_c, item in enumerate(row):
        if item == '-':
            item = '-1'
            matlist[idx_r][idx_c] = '-1'


# Convert to int
matlist = [list(map(int,i)) for i in matlist]

# Convert to Numpy Matrix
Hbase = np.array(matlist, dtype=int)

#N = 648
#Z = 27

K = int(R * N)
M = N - K

print('N: ', N)
print('M: ', M)
print('K: ', K)
print('Z: ', Z)
print('N/Z: ', int(N/Z))
print('M/Z: ', int(M/Z))
#print(Hbase)

# MATLAB conversion code
# https://github.com/giuliomarin/tlc/blob/master/ldpc/LDPC.m

#H = zeros(size(matrix_prototype)*Z);
#P0 = eye(Z);
#
#for r=1:size(matrix_prototype,1)
#    for c=1:size(matrix_prototype,2)
#        shift = matrix_prototype(r,c);
#        if (shift > -1)
#            Pi = circshift(P0,[0 shift]);
#        else
#            Pi = zeros(Z);
#        end
#        R = (r-1)*Z+1:r*Z;
#        C = (c-1)*Z+1:c*Z;
#        H(R,C) = Pi;
#    end
#end

H = np.empty([M, N], dtype=int)
P0 = np.identity(Z, dtype=int)

for r in range(0, ROWS):
    for c in range(0, COLS):
        shift = Hbase[r][c]
        if shift > -1:
            Pi = np.roll(P0, shift, axis=1)
        else:
            Pi = np.zeros((Z,Z))

        for R in range(r*Z, (r+1)*Z):
            for C in range(c*Z, (c+1)*Z):
                H[R][C] = Pi[R-(r*Z)][C-(c*Z)]

#print(H)
if H_csv_out != "":
    np.savetxt(H_csv_out, H.astype(int), fmt='%i', delimiter=",")

#N=16
#M=8
#H = np.array(
#[[0,  0,  0,  27, 0,  0,  1,  0,  0,  36, 0,  0,  0,  0,  0,  49],
#[0,  0,  0,  60, 45, 0,  0,  0,  32, 0,  0,  0,  0,  0,  23, 0],
#[0,  6,  0,  0,  0,  21, 56, 0,  0,  0,  0,  0,  0,  47, 0,  0],
#[32, 0,  0,  0,  0,  0,  0,  23, 0,  0,  60, 0,  0,  0,  0,  45],
#[0,  0,  52, 0,  0,  0,  0,  0,  61, 0,  26, 0,  0,  11, 0,  0],
#[39, 0,  0,  0,  0,  2,  0,  0,  0,  0,  0,  24, 0,  0,  11, 0],
#[0,  36, 0,  0,  45, 0,  0,  10, 0,  0,  0,  0,  58, 0,  0,  0],
#[0,  0,  62, 0,  0,  0,  0,  0,  0,  12, 0,  53, 27, 0,  0,  0]])
#print('H: ', H)

# Convert to alist

# Build N list
nlist = []
for c in range(N):
    nlist.append([])
    for r in range(M):
        if H[r][c] > 0:
            nlist[c].append(r+1)

num_nlist = []
for entry in nlist:
    num_nlist.append(len(entry))

biggest_num_n = max(num_nlist)


# Build M list
mlist = []
for r in range(M):
    mlist.append([])
    for c in range(N):
        if H[r][c] > 0:
            mlist[r].append(c+1)

num_mlist = []
for entry in mlist:
    num_mlist.append(len(entry))

biggest_num_m = max(num_mlist)

#print('Largest N', biggest_num_n)
#print('Num N list: ', num_nlist)
#print('N list: ', nlist)
#
#print('Largest M', biggest_num_m)
#print('Num M list: ', num_mlist)
#print('M list: ', mlist)


# Write alist to file
# N
# M
# Biggest num N
# Biggest num M
# Num N list [n1 n2 n3 n4]
# Num M list [n1 n2 n3 n4]
# N List (idx)
# M list (idx)
print('Writing to .alist file: ', alist_txt)
with open(alist_txt,'w') as alist:
    wr = csv.writer(alist, delimiter=" ")
    wr.writerow([N])
    wr.writerow([M])
    wr.writerow([biggest_num_n])
    wr.writerow([biggest_num_m])
    wr.writerow(num_nlist)
    wr.writerow(num_mlist)
    for row in nlist:
        wr.writerow(row)
    for row in mlist:
        wr.writerow(row)
