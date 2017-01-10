* binandhex
* by Matt Beller

* Converts binary and hexadecimal numbers back and forth.

**************************************************************************
* To convert a binary number to hexidecimal, enter it as any string of   *
*  bits.  To convert a number from hexidecimal to binary, enter 0x or 0X *
*  in front of it.  If the string contains any non(0 or 1) characters    *
*  (e.g. 7, A, C), it will automatically be converted to binary, even    *
*  without the 0x.                                                       *
**************************************************************************

* Note: Letters A-F must be entered as capital letters


* If it's multiple of four (0 or 1) convert fourbit strings from binary to 
*  hex.  If it's not a multiple of four, translate the first 1, 
*  2, or 3 bits to a hex number.

* States S and A through D decide whether it's a multiple of four 
*  consisting entirely of 0's and 1's, or whether it has odd bits on the 
*  front.

S#H
S0A0
S1A1
S2E2
S3E3
S4E4
S5E5
S6E6
S7E7
S8E8
S9E9
SAEA
SBEB
SCEC
SDED
SEEE
SFEF

A#s#
A0B0
Axq
AXq
A1B1
A2E2
A3E3
A4E4
A5E5
A6E6
A7E7
A8E8
A9E9
AAEA
ABEB
ACEC
ADED
AEEE
AFEF

B#t#
B0C0
B1C1
B2E2
B3E3
B4E4
B5E5
B6E6
B7E7
B8E8
B9E9
BAEA
BBEB
BCEC
BDED
BEEE
BFEF

C#u#
C0D0
C1D1
C2E2
C3E3
C4E4
C5E5
C6E6
C7E7
C8E8
C9E9
CAEA
CBEB
CCEC
CDED
CEEE
CFEF

D#I#
D0A0
D1A1
D2E2
D3E3
D4E4
D5E5
D6E6
D7E7
D8E8
D9E9
DAEA
DBEB
DCEC
DDED
DEEE
DFEF

* cycle back to front to then convert
E#F#
E0E0
E1E1
E2E2
E3E3
E4E4
E5E5
E6E6
E7E7
E8E8
E9E9
EAEA
EBEB
ECEC
EDED
EEEE
EFEF


* The purpose of q is to handle 0x.  It then cycles back to the front
q0q0
q1q1
q2q2
q3q3
q4q4
q5q5
q6q6
q7q7
q8q8
q9q9
qAqA
qBqB
qCqC
qDqD
qEqE
qFqF
q#r#

* r removes the 0 on the front leftover from 0x and goes to convert to 
*  binary

r0F

* convert first hex number to binary
F#H
F0F
F1G1
F2G10
F3G11
F4G100
F5G101
F6G110
F7G111
F8G1000
F9G1001
FAG1010
FBG1011
FCG1100
FDG1101
FEG1110
FFG1111

* convert all other hex numbers to binary
G#H
G0G0000
G1G0001
G2G0010
G3G0011
G4G0100
G5G0101
G6G0110
G7G0111
G8G1000
G9G1001
GAG1010
GBG1011
GCG1100
GDG1101
GEG1110
GFG1111


* convert first 4bit string to hex equivalent
* Note: I convert the first 4bit string differently to eliminate 
*  extraneous zero's

I0J
I1K
* in case user enters zero
I#H0

J0L
J1M
K0N
K1O

L0P
L1Q
M0R
M1T
N0U
N1V
O0W
O1X

P0I
P1a1
Q0a2
Q1a3
R0a4
R1a5
T0a6
T1a7
U0a8
U1a9
V0aA
V1aB
W0aC
W1aD
X0aE
X1aF

* convert all other 4bitstrings to hex equivalent
a#H
a0b
a1c

b0d
b1e
c0f
c1g

d0h
d1i
e0j
e1k
f0l
f1m
g0n
g1o


h0a0
h1a1
i0a2
i1a3
j0a4
j1a5
k0a6
k1a7
l0a8
l1a9
m0aA
m1aB
n0aC
n1aD
o0aE
o1aF

* 1bit string on front
s0s0
s1s1
s#6#

* 2bit string on front
t0t0
t1t1
t#3#

* 3bit string on front
u0u0
u1u1
u#v#

* convert 3bit string
v0w
v1x

w0y
w1z
x01
x12

y0I
y1a1
z0a2
z1a3
10a4
11a5
20a6
21a7

* convert 2-bit string
304
315

40I
41a1
50a2
51a3

* convert 1-bit string
60I
61a1
*


