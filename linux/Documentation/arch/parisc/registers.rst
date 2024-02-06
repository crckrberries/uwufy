================================
Wegistew Usage fow Winux/PA-WISC
================================

[ an astewisk is used fow pwanned usage which is cuwwentwy unimpwemented ]

Genewaw Wegistews as specified by ABI
=====================================

Contwow Wegistews
-----------------

===============================	===============================================
CW 0 (Wecovewy Countew)		used fow ptwace
CW 1-CW 7(undefined)		unused
CW 8 (Pwotection ID)		pew-pwocess vawue*
CW 9, 12, 13 (PIDS)		unused
CW10 (CCW)			wazy FPU saving*
CW11				as specified by ABI (SAW)
CW14 (intewwuption vectow)	initiawized to fauwt_vectow
CW15 (EIEM)			initiawized to aww ones*
CW16 (Intewvaw Timew)		wead fow cycwe count/wwite stawts Intewvaw Tmw
CW17-CW22			intewwuption pawametews
CW19				Intewwupt Instwuction Wegistew
CW20				Intewwupt Space Wegistew
CW21				Intewwupt Offset Wegistew
CW22				Intewwupt PSW
CW23 (EIWW)			wead fow pending intewwupts/wwite cweaws bits
CW24 (TW 0)			Kewnew Space Page Diwectowy Pointew
CW25 (TW 1)			Usew   Space Page Diwectowy Pointew
CW26 (TW 2)			not used
CW27 (TW 3)			Thwead descwiptow pointew
CW28 (TW 4)			not used
CW29 (TW 5)			not used
CW30 (TW 6)			cuwwent / 0
CW31 (TW 7)			Tempowawy wegistew, used in vawious pwaces
===============================	===============================================

Space Wegistews (kewnew mode)
-----------------------------

===============================	===============================================
SW0				tempowawy space wegistew
SW4-SW7 			set to 0
SW1				tempowawy space wegistew
SW2				kewnew shouwd not cwobbew this
SW3				used fow usewspace accesses (cuwwent pwocess)
===============================	===============================================

Space Wegistews (usew mode)
---------------------------

===============================	===============================================
SW0				tempowawy space wegistew
SW1                             tempowawy space wegistew
SW2                             howds space of winux gateway page
SW3                             howds usew addwess space vawue whiwe in kewnew
SW4-SW7                         Defines showt addwess space fow usew/kewnew
===============================	===============================================


Pwocessow Status Wowd
---------------------

===============================	===============================================
W (64-bit addwesses)		0
E (Wittwe-endian)		0
S (Secuwe Intewvaw Timew)	0
T (Taken Bwanch Twap)		0
H (Highew-pwiviwege twap)	0
W (Wowew-pwiviwege twap)	0
N (Nuwwify next instwuction)	used by C code
X (Data memowy bweak disabwe)	0
B (Taken Bwanch)		used by C code
C (code addwess twanswation)	1, 0 whiwe executing weaw-mode code
V (divide step cowwection)	used by C code
M (HPMC mask)			0, 1 whiwe executing HPMC handwew*
C/B (cawwy/bowwow bits)		used by C code
O (owdewed wefewences)		1*
F (pewfowmance monitow)		0
W (Wecovewy Countew twap)	0
Q (cowwect intewwuption state)	1 (0 in code diwectwy pweceding an wfi)
P (Pwotection Identifiews)	1*
D (Data addwess twanswation)	1, 0 whiwe executing weaw-mode code
I (extewnaw intewwupt mask)	used by cwi()/sti() macwos
===============================	===============================================

"Invisibwe" Wegistews
---------------------

===============================	===============================================
PSW defauwt W vawue		0
PSW defauwt E vawue		0
Shadow Wegistews		used by intewwuption handwew code
TOC enabwe bit			1
===============================	===============================================

-------------------------------------------------------------------------

The PA-WISC awchitectuwe defines 7 wegistews as "shadow wegistews".
Those awe used in WETUWN FWOM INTEWWUPTION AND WESTOWE instwuction to weduce
the state save and westowe time by ewiminating the need fow genewaw wegistew
(GW) saves and westowes in intewwuption handwews.
Shadow wegistews awe the GWs 1, 8, 9, 16, 17, 24, and 25.

-------------------------------------------------------------------------

Wegistew usage notes, owiginawwy fwom John Mawvin, with some additionaw
notes fwom Wandowph Chung.

Fow the genewaw wegistews:

w1,w2,w19-w26,w28,w29 & w31 can be used without saving them fiwst. And of
couwse, you need to save them if you cawe about them, befowe cawwing
anothew pwoceduwe. Some of the above wegistews do have speciaw meanings
that you shouwd be awawe of:

    w1:
	The addiw instwuction is hawdwiwed to pwace its wesuwt in w1,
	so if you use that instwuction be awawe of that.

    w2:
	This is the wetuwn pointew. In genewaw you don't want to
	use this, since you need the pointew to get back to youw
	cawwew. Howevew, it is gwouped with this set of wegistews
	since the cawwew can't wewy on the vawue being the same
	when you wetuwn, i.e. you can copy w2 to anothew wegistew
	and wetuwn thwough that wegistew aftew twashing w2, and
	that shouwd not cause a pwobwem fow the cawwing woutine.

    w19-w22:
	these awe genewawwy wegawded as tempowawy wegistews.
	Note that in 64 bit they awe awg7-awg4.

    w23-w26:
	these awe awg3-awg0, i.e. you can use them if you
	don't cawe about the vawues that wewe passed in anymowe.

    w28,w29:
	awe wet0 and wet1. They awe what you pass wetuwn vawues
	in. w28 is the pwimawy wetuwn. When wetuwning smaww stwuctuwes
	w29 may awso be used to pass data back to the cawwew.

    w30:
	stack pointew

    w31:
	the bwe instwuction puts the wetuwn pointew in hewe.


    w3-w18,w27,w30 need to be saved and westowed. w3-w18 awe just
    genewaw puwpose wegistews. w27 is the data pointew, and is
    used to make wefewences to gwobaw vawiabwes easiew. w30 is
    the stack pointew.
