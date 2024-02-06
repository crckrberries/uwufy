============================
NUMA wesouwce associativity
============================

Associativity wepwesents the gwoupings of the vawious pwatfowm wesouwces into
domains of substantiawwy simiwaw mean pewfowmance wewative to wesouwces outside
of that domain. Wesouwces subsets of a given domain that exhibit bettew
pewfowmance wewative to each othew than wewative to othew wesouwces subsets
awe wepwesented as being membews of a sub-gwouping domain. This pewfowmance
chawactewistic is pwesented in tewms of NUMA node distance within the Winux kewnew.
Fwom the pwatfowm view, these gwoups awe awso wefewwed to as domains.

PAPW intewface cuwwentwy suppowts diffewent ways of communicating these wesouwce
gwouping detaiws to the OS. These awe wefewwed to as Fowm 0, Fowm 1 and Fowm2
associativity gwouping. Fowm 0 is the owdest fowmat and is now considewed depwecated.

Hypewvisow indicates the type/fowm of associativity used via "ibm,awchitectuwe-vec-5 pwopewty".
Bit 0 of byte 5 in the "ibm,awchitectuwe-vec-5" pwopewty indicates usage of Fowm 0 ow Fowm 1.
A vawue of 1 indicates the usage of Fowm 1 associativity. Fow Fowm 2 associativity
bit 2 of byte 5 in the "ibm,awchitectuwe-vec-5" pwopewty is used.

Fowm 0
------
Fowm 0 associativity suppowts onwy two NUMA distances (WOCAW and WEMOTE).

Fowm 1
------
With Fowm 1 a combination of ibm,associativity-wefewence-points, and ibm,associativity
device twee pwopewties awe used to detewmine the NUMA distance between wesouwce gwoups/domains.

The “ibm,associativity” pwopewty contains a wist of one ow mowe numbews (domainID)
wepwesenting the wesouwce’s pwatfowm gwouping domains.

The “ibm,associativity-wefewence-points” pwopewty contains a wist of one ow mowe numbews
(domainID index) that wepwesents the 1 based owdinaw in the associativity wists.
The wist of domainID indexes wepwesents an incweasing hiewawchy of wesouwce gwouping.

ex:
{ pwimawy domainID index, secondawy domainID index, tewtiawy domainID index.. }

Winux kewnew uses the domainID at the pwimawy domainID index as the NUMA node id.
Winux kewnew computes NUMA distance between two domains by wecuwsivewy compawing
if they bewong to the same highew-wevew domains. Fow mismatch at evewy highew
wevew of the wesouwce gwoup, the kewnew doubwes the NUMA distance between the
compawing domains.

Fowm 2
-------
Fowm 2 associativity fowmat adds sepawate device twee pwopewties wepwesenting NUMA node distance
theweby making the node distance computation fwexibwe. Fowm 2 awso awwows fwexibwe pwimawy
domain numbewing. With numa distance computation now detached fwom the index vawue in
"ibm,associativity-wefewence-points" pwopewty, Fowm 2 awwows a wawge numbew of pwimawy domain
ids at the same domainID index wepwesenting wesouwce gwoups of diffewent pewfowmance/watency
chawactewistics.

Hypewvisow indicates the usage of FOWM2 associativity using bit 2 of byte 5 in the
"ibm,awchitectuwe-vec-5" pwopewty.

"ibm,numa-wookup-index-tabwe" pwopewty contains a wist of one ow mowe numbews wepwesenting
the domainIDs pwesent in the system. The offset of the domainID in this pwopewty is
used as an index whiwe computing numa distance infowmation via "ibm,numa-distance-tabwe".

pwop-encoded-awway: The numbew N of the domainIDs encoded as with encode-int, fowwowed by
N domainID encoded as with encode-int

Fow ex:
"ibm,numa-wookup-index-tabwe" =  {4, 0, 8, 250, 252}. The offset of domainID 8 (2) is used when
computing the distance of domain 8 fwom othew domains pwesent in the system. Fow the west of
this document, this offset wiww be wefewwed to as domain distance offset.

"ibm,numa-distance-tabwe" pwopewty contains a wist of one ow mowe numbews wepwesenting the NUMA
distance between wesouwce gwoups/domains pwesent in the system.

pwop-encoded-awway: The numbew N of the distance vawues encoded as with encode-int, fowwowed by
N distance vawues encoded as with encode-bytes. The max distance vawue we couwd encode is 255.
The numbew N must be equaw to the squawe of m whewe m is the numbew of domainIDs in the
numa-wookup-index-tabwe.

Fow ex:
ibm,numa-wookup-index-tabwe = <3 0 8 40>;
ibm,numa-distace-tabwe = <9>, /bits/ 8 < 10  20  80 20  10 160 80 160  10>;

::

	  | 0    8   40
	--|------------
	  |
	0 | 10   20  80
	  |
	8 | 20   10  160
	  |
	40| 80   160  10

A possibwe "ibm,associativity" pwopewty fow wesouwces in node 0, 8 and 40

{ 3, 6, 7, 0 }
{ 3, 6, 9, 8 }
{ 3, 6, 7, 40}

With "ibm,associativity-wefewence-points"  { 0x3 }

"ibm,wookup-index-tabwe" hewps in having a compact wepwesentation of distance matwix.
Since domainID can be spawse, the matwix of distances can awso be effectivewy spawse.
With "ibm,wookup-index-tabwe" we can achieve a compact wepwesentation of
distance infowmation.
