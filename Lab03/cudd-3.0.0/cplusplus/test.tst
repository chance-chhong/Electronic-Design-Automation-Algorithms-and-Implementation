Entering testBdd
f: 3 nodes 1 leaves 1 minterms
11  1

g: 3 nodes 1 leaves 3 minterms
0-  1
11  1

f and g are not complementary
f is less than or equal to g
g: 2 nodes 1 leaves 2 minterms
1-  1

h: 2 nodes 1 leaves 2 minterms
-1  1

x + h has 3 nodes
h: 3 nodes 1 leaves 3 minterms
01  1
1-  1

Entering testAdd
r: 6 nodes 3 leaves 3 minterms
01  1
10  1
11  2

s: 4 nodes 2 leaves 1 minterms
11  3

s: 1 nodes 1 leaves 4 minterms
--  inf

p is less than or equal to r
r: 4 nodes 2 leaves 3 minterms
01  1
1-  1

Entering testAdd2
f: 7 nodes 4 leaves 4 minterms
00  0.1
01  0.2
10  0.3
11  0.4

l: 7 nodes 4 leaves 4 minterms
00 -2.30259
01 -1.60944
10 -1.20397
11 -0.916291

r: 7 nodes 4 leaves 4 minterms
00 -0.230259
01 -0.321888
10 -0.361192
11 -0.366516

e: 1 nodes 1 leaves 4 minterms
--  1.84644

Entering testZdd
s: 3 nodes 3 minterms
1- 1
01 1

v is less than s
s: 1 nodes 1 minterms
01 1

Entering testBdd2
f: 7 nodes 1 leaves 7 minterms
01-1  1
101-  1
1101  1
111-  1

Irredundant cover of f:
1-1- 1
-1-1 1

Number of minterms (arbitrary precision): 7
Number of minterms (extended precision):  7.000000e+00Two-literal clauses of f:
 x2 |  x3
 x1 |  x2
 x0 |  x3
 x0 |  x1

vect[0]
1--- 1

vect[1]
0--- 1
-1-- 1

vect[2]
10-- 1
--1- 1

vect[3]
0--- 1
-10- 1
---1 1

digraph "DD" {
size = "7.5,10"
center = true;
edge [dir = none];
{ node [shape = plaintext];
  edge [style = invis];
  "CONST NODES" [style = invis];
" x0 " -> " x1 " -> " x2 " -> " x3 " -> "CONST NODES"; 
}
{ rank = same; node [shape = box]; edge [style = invis];
"  v0  " -> "  v1  " -> "  v2  " -> "  v3  "; }
{ rank = same; " x0 ";
"0x17a";
"0x1bf";
"0x1bc";
"0x17e";
}
{ rank = same; " x1 ";
"0x17b";
"0x1bb";
"0x1be";
}
{ rank = same; " x2 ";
"0x1bd";
"0x1ac";
}
{ rank = same; " x3 ";
"0x1ad";
}
{ rank = same; "CONST NODES";
{ node [shape = box]; "0x174";
}
}
"  v0  " -> "0x17a" [style = solid];
"  v1  " -> "0x17e" [style = solid];
"  v2  " -> "0x1bc" [style = solid];
"  v3  " -> "0x1bf" [style = solid];
"0x17a" -> "0x174";
"0x17a" -> "0x174" [style = dotted];
"0x1bf" -> "0x1be";
"0x1bf" -> "0x174" [style = dashed];
"0x1bc" -> "0x1bb";
"0x1bc" -> "0x1ac" [style = dashed];
"0x17e" -> "0x17b";
"0x17e" -> "0x174" [style = dashed];
"0x17b" -> "0x174";
"0x17b" -> "0x174" [style = dotted];
"0x1bb" -> "0x1ac";
"0x1bb" -> "0x174" [style = dashed];
"0x1be" -> "0x1bd";
"0x1be" -> "0x1ad" [style = dashed];
"0x1bd" -> "0x1ad";
"0x1bd" -> "0x174" [style = dashed];
"0x1ac" -> "0x174";
"0x1ac" -> "0x174" [style = dotted];
"0x1ad" -> "0x174";
"0x1ad" -> "0x174" [style = dotted];
"0x174" [label = "1"];
}
Entering testBdd3
f: 10 nodes 1 leaves 50 minterms
0-0-0-  1
0-0-10  1
0-100-  1
0-1010  1
0-11--  1
10-00-  1
10-010  1
10-1--  1
11000-  1
110010  1
1101--  1
1110-1  1
111101  1

f1: 5 nodes 1 leaves 36 minterms
0---0-  1
0---10  1
10--0-  1
10--10  1

f1 is less than or equal to f
g: 6 nodes 1 leaves 62 minterms
0-----  1
10----  1
110---  1
1110--  1
11110-  1

h: 8 nodes 1 leaves 51 minterms
0-0-0-  1
0-0-10  1
0-100-  1
0-1010  1
0-11--  1
10-00-  1
10-010  1
10-1--  1
11000-  1
110010  1
1101--  1
111--1  1

g * h == f
Entering testZdd2
p[0]: 3 nodes 1 leaves 64 minterms
----0-0  1
----1-1  1

p[1]: 5 nodes 1 leaves 64 minterms
--0-0-0  1
--0-10-  1
--1-0-1  1
--1-11-  1

p[2]: 7 nodes 1 leaves 64 minterms
0-0-0-0  1
0-0-10-  1
0-10---  1
1-0-0-1  1
1-0-11-  1
1-11---  1

p[3]: 8 nodes 1 leaves 64 minterms
0-0-0-1  1
0-0-11-  1
0-11---  1
11-----  1

digraph "DD" {
size = "7.5,10"
center = true;
edge [dir = none];
{ node [shape = plaintext];
  edge [style = invis];
  "CONST NODES" [style = invis];
" a2 " -> " b2 " -> " a1 " -> " b1 " -> " a0 " -> " b0 " -> " c0 " -> "CONST NODES"; 
}
{ rank = same; node [shape = box]; edge [style = invis];
"  s0  " -> "  s1  " -> "  s2  " -> "  c3  "; }
{ rank = same; " a2 ";
"0x1f6";
"0x1f5";
}
{ rank = same; " b2 ";
"0x17b";
}
{ rank = same; " a1 ";
"0x1f4";
"0x1f3";
}
{ rank = same; " b1 ";
"0x1ad";
}
{ rank = same; " a0 ";
"0x1f2";
"0x1f1";
}
{ rank = same; " b0 ";
"0x1cc";
}
{ rank = same; " c0 ";
"0x1f0";
}
{ rank = same; "CONST NODES";
{ node [shape = box]; "0x174";
}
}
"  s0  " -> "0x1f1" [style = solid];
"  s1  " -> "0x1f3" [style = solid];
"  s2  " -> "0x1f5" [style = solid];
"  c3  " -> "0x1f6" [style = solid];
"0x1f6" -> "0x17b";
"0x1f6" -> "0x1f4" [style = dashed];
"0x1f5" -> "0x1f4";
"0x1f5" -> "0x1f4" [style = dotted];
"0x17b" -> "0x174";
"0x17b" -> "0x174" [style = dotted];
"0x1f4" -> "0x1ad";
"0x1f4" -> "0x1f2" [style = dashed];
"0x1f3" -> "0x1f2";
"0x1f3" -> "0x1f2" [style = dotted];
"0x1ad" -> "0x174";
"0x1ad" -> "0x174" [style = dotted];
"0x1f2" -> "0x1cc";
"0x1f2" -> "0x1f0" [style = dashed];
"0x1f1" -> "0x1f0";
"0x1f1" -> "0x1f0" [style = dotted];
"0x1cc" -> "0x174";
"0x1cc" -> "0x174" [style = dotted];
"0x1f0" -> "0x174";
"0x1f0" -> "0x174" [style = dotted];
"0x174" [label = "1"];
}
z[0]: 4 nodes 2 minterms
00000000100010 1
00000000010001 1

z[1]: 10 nodes 4 minterms
00001000101000 1
00001000010010 1
00000100100100 1
00000100010001 1

z[2]: 16 nodes 6 minterms
10001010000000 1
10000100101000 1
10000100010010 1
01001001000000 1
01000100100100 1
01000100010001 1

z[3]: 10 nodes 4 minterms
10100000000000 1
01001010000000 1
01000100101000 1
01000100010010 1

z[0]
----1-1 1
----0-0 1
z[0]
----0-0 1
----1-1 1
z[1]
--1-11- 1
--1-0-1 1
--0-10- 1
--0-0-0 1
z[1]
--0-0-0 1
--0-10- 1
--1-0-1 1
--1-11- 1
z[2]
1-11--- 1
1-0-11- 1
1-0-0-1 1
0-10--- 1
0-0-10- 1
0-0-0-0 1
z[2]
0-0-0-0 1
0-0-10- 1
0-10--- 1
1-0-0-1 1
1-0-11- 1
1-11--- 1
z[3]
11----- 1
0-11--- 1
0-0-11- 1
0-0-0-1 1
z[3]
0-0-0-1 1
0-0-11- 1
0-11--- 1
11----- 1
digraph "ZDD" {
size = "7.5,10"
center = true;
edge [dir = none];
{ node [shape = plaintext];
  edge [style = invis];
  "CONST NODES" [style = invis];
" a2+ " -> " a2- " -> " b2+ " -> " a1+ " -> " a1- " -> " b1+ " -> " b1- " -> " a0+ " -> " a0- " -> " b0+ " -> " b0- " -> " c0+ " -> " c0- " -> "CONST NODES"; 
}
{ rank = same; node [shape = box]; edge [style = invis];
"  s0  " -> "  s1  " -> "  s2  " -> "  c3  "; }
{ rank = same; " a2+ ";
"0x1b7";
"0x1ae";
}
{ rank = same; " a2- ";
"0x1b5";
"0x1aa";
}
{ rank = same; " b2+ ";
"0x1b1";
}
{ rank = same; " a1+ ";
"0x1a5";
"0x197";
"0x19e";
}
{ rank = same; " a1- ";
"0x195";
"0x1a3";
}
{ rank = same; " b1+ ";
"0x19f";
}
{ rank = same; " b1- ";
"0x19a";
}
{ rank = same; " a0+ ";
"0x190";
"0x182";
"0x189";
}
{ rank = same; " a0- ";
"0x18e";
"0x180";
}
{ rank = same; " b0+ ";
"0x18a";
}
{ rank = same; " b0- ";
"0x185";
}
{ rank = same; " c0+ ";
"0x179";
}
{ rank = same; " c0- ";
"0x178";
}
{ rank = same; "CONST NODES";
{ node [shape = box]; "0x175";
"0x174";
}
}
"  s0  " -> "0x182" [style = solid];
"  s1  " -> "0x197" [style = solid];
"  s2  " -> "0x1ae" [style = solid];
"  c3  " -> "0x1b7" [style = solid];
"0x1b7" -> "0x1b1";
"0x1b7" -> "0x1b5" [style = dashed];
"0x1ae" -> "0x1a5";
"0x1ae" -> "0x1aa" [style = dashed];
"0x1b5" -> "0x1a5";
"0x1b5" -> "0x175" [style = dashed];
"0x1aa" -> "0x19e";
"0x1aa" -> "0x175" [style = dashed];
"0x1b1" -> "0x174";
"0x1b1" -> "0x175" [style = dashed];
"0x1a5" -> "0x19f";
"0x1a5" -> "0x1a3" [style = dashed];
"0x197" -> "0x190";
"0x197" -> "0x195" [style = dashed];
"0x19e" -> "0x19a";
"0x19e" -> "0x195" [style = dashed];
"0x195" -> "0x189";
"0x195" -> "0x175" [style = dashed];
"0x1a3" -> "0x190";
"0x1a3" -> "0x175" [style = dashed];
"0x19f" -> "0x174";
"0x19f" -> "0x175" [style = dashed];
"0x19a" -> "0x174";
"0x19a" -> "0x175" [style = dashed];
"0x190" -> "0x18a";
"0x190" -> "0x18e" [style = dashed];
"0x182" -> "0x179";
"0x182" -> "0x180" [style = dashed];
"0x189" -> "0x185";
"0x189" -> "0x180" [style = dashed];
"0x18e" -> "0x179";
"0x18e" -> "0x175" [style = dashed];
"0x180" -> "0x178";
"0x180" -> "0x175" [style = dashed];
"0x18a" -> "0x174";
"0x18a" -> "0x175" [style = dashed];
"0x185" -> "0x174";
"0x185" -> "0x175" [style = dashed];
"0x179" -> "0x174";
"0x179" -> "0x175" [style = dashed];
"0x178" -> "0x174";
"0x178" -> "0x175" [style = dashed];
"0x175" [label = "0"];
"0x174" [label = "1"];
}
Entering testBdd4
f: 5 nodes 1 leaves 3 minterms
000-----------  1
11------------  1

g: 5 nodes 1 leaves 3 minterms
000  1
11-  1

f and h are identical
Entering testBdd5
digraph "DD" {
size = "7.5,10"
center = true;
edge [dir = none];
{ node [shape = plaintext];
  edge [style = invis];
  "CONST NODES" [style = invis];
" a " -> " b " -> " c " -> " d " -> "CONST NODES"; 
}
{ rank = same; node [shape = box]; edge [style = invis];
"  lb  " -> "  ub  " -> "  f  " -> "  primes  " -> "  lprime  "; }
{ rank = same; " a ";
"0x1e8";
}
{ rank = same; " b ";
"0x1e4";
"0x1e7";
"0x1e5";
"0x1e9";
}
{ rank = same; " c ";
"0x19c";
"0x1e2";
}
{ rank = same; " d ";
"0x1ad";
}
{ rank = same; "CONST NODES";
{ node [shape = box]; "0x174";
}
}
"  lb  " -> "0x1e9" [style = dotted];
"  ub  " -> "0x1ad" [style = solid];
"  f  " -> "0x1e8" [style = solid];
"  primes  " -> "0x1e4" [style = solid];
"  lprime  " -> "0x1e4" [style = solid];
"0x1e8" -> "0x1e5";
"0x1e8" -> "0x1e7" [style = dashed];
"0x1e4" -> "0x1ad";
"0x1e4" -> "0x174" [style = dotted];
"0x1e7" -> "0x19c";
"0x1e7" -> "0x174" [style = dotted];
"0x1e5" -> "0x1ad";
"0x1e5" -> "0x1e2" [style = dotted];
"0x1e9" -> "0x1e2";
"0x1e9" -> "0x174" [style = dashed];
"0x19c" -> "0x1ad";
"0x19c" -> "0x174" [style = dashed];
"0x1e2" -> "0x174";
"0x1e2" -> "0x1ad" [style = dotted];
"0x1ad" -> "0x174";
"0x1ad" -> "0x174" [style = dotted];
"0x174" [label = "1"];
}
primes(1): 3 nodes 1 leaves 4 minterms
-1-1----------  1

primes(2): is the zero DD
primes(3): 4 nodes 1 leaves 2 minterms
1-01----------  1

primes(4): 6 nodes 1 leaves 5 minterms
-1-1---------- 1
010----------- 1

primes(5): 4 nodes 1 leaves 2 minterms
01-1----------  1

l1: 7 nodes 1 leaves 3 minterms
0111----------  1
111-----------  1

u1: 4 nodes 1 leaves 8 minterms
000-----------  1
011-----------  1
1-1-----------  1

interpolant1: 4 nodes 1 leaves 6 minterms
011-----------  1
1-1-----------  1

l2: 7 nodes 1 leaves 5 minterms
001-----------  1
0110----------  1
101-----------  1

u2: 5 nodes 1 leaves 8 minterms
-000----------  1
-01-----------  1
-110----------  1

interpolant2: 5 nodes 1 leaves 6 minterms
-01-----------  1
-110----------  1

l3: 4 nodes 1 leaves 2 minterms
00-1----------  1

u3: 3 nodes 1 leaves 4 minterms
-0-1----------  1

interpolant3: 3 nodes 1 leaves 4 minterms
-0-1----------  1

Entering testErrorHandling
Oops! Caught: empty DD.
Caught: Invalid argument.
f = var[1] | (var[2] & var[3])
var[0] | var[1] is not a cube
Cudd_Cofactor: Invalid restriction 2
Caught: Invalid argument.
f : 511 nodes 1 leaves 115422332637413376 minterms
g : 511 nodes 1 leaves 115422332637413376 minterms
h Caught: empty DD.
f : 88 nodes 1 leaves 226007109 minterms
g : 91 nodes 1 leaves 3143500301 minterms
h : 142 nodes 1 leaves 2917493192 minterms
Caught: Maximum memory exceeded.
Caught: Timeout expired.  Lag = 109 ms.
**** CUDD modifiable parameters ****
Hard limit for cache size: 2796202
Cache hit threshold for resizing: 30%
Garbage collection enabled: yes
Limit for fast unique table growth: 1677721
Maximum number of variables sifted per reordering: 1000
Maximum number of variable swaps per reordering: 2000000
Maximum growth while sifting a variable: 1.2
Dynamic reordering of BDDs enabled: no
Default BDD reordering method: 4
Dynamic reordering of ZDDs enabled: no
Default ZDD reordering method: 4
Realignment of ZDDs to BDDs enabled: no
Realignment of BDDs to ZDDs enabled: no
Dead nodes counted in triggering reordering: no
Group checking criterion: 7
Recombination threshold: 0
Symmetry violation threshold: 0
Arc violation threshold: 0
GA population size: 0
Number of crossovers for GA: 0
Next reordering threshold: 4004
**** CUDD non-modifiable parameters ****
Memory in use: 146651984
Peak number of nodes: 2044
Peak number of live nodes: 2030
Number of BDD variables: 60
Number of ZDD variables: 14
Number of cache entries: 524288
Number of cache look-ups: 3847
Number of cache hits: 876
Number of cache insertions: 3052
Number of cache collisions: 7
Number of cache deletions: 2293
Cache used slots = 0.17% (expected 0.17%)
Soft limit for cache size: 76800
Number of buckets in unique table: 19200
Used buckets in unique table: 4.22% (expected 4.19%)
Number of BDD and ADD nodes: 2634
Number of ZDD nodes: 14
Number of dead BDD and ADD nodes: 2570
Number of dead ZDD nodes: 0
Total number of nodes allocated: 4857
Total number of nodes reclaimed: 154
Garbage collections so far: 3
Time for garbage collection: 0.00 sec
Reorderings so far: 0
Time for reordering: 0.00 sec
