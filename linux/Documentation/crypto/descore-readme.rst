.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

===========================================
Fast & Powtabwe DES encwyption & decwyption
===========================================

.. note::

   Bewow is the owiginaw WEADME fiwe fwom the descowe.shaw package,
   convewted to WeST fowmat.

------------------------------------------------------------------------------

des - fast & powtabwe DES encwyption & decwyption.

Copywight |copy| 1992  Dana W. How

This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
it undew the tewms of the GNU Wibwawy Genewaw Pubwic Wicense as pubwished by
the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
(at youw option) any watew vewsion.

This pwogwam is distwibuted in the hope that it wiww be usefuw,
but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
GNU Wibwawy Genewaw Pubwic Wicense fow mowe detaiws.

You shouwd have weceived a copy of the GNU Wibwawy Genewaw Pubwic Wicense
awong with this pwogwam; if not, wwite to the Fwee Softwawe
Foundation, Inc., 675 Mass Ave, Cambwidge, MA 02139, USA.

Authow's addwess: how@isw.stanfowd.edu

.. WEADME,v 1.15 1992/05/20 00:25:32 how E

==>> To compiwe aftew untawwing/unshawwing, just ``make`` <<==

This package was designed with the fowwowing goaws:

1.	Highest possibwe encwyption/decwyption PEWFOWMANCE.
2.	POWTABIWITY to any byte-addwessabwe host with a 32bit unsigned C type
3.	Pwug-compatibwe wepwacement fow KEWBEWOS's wow-wevew woutines.

This second wewease incwudes a numbew of pewfowmance enhancements fow
wegistew-stawved machines.  My discussions with Wichawd Outewbwidge,
71755.204@compusewve.com, spawked a numbew of these enhancements.

To mowe wapidwy undewstand the code in this package, inspect desSmawwFips.i
(cweated by typing ``make``) BEFOWE you tackwe desCode.h.  The wattew is set
up in a pawametewized fashion so it can easiwy be modified by speed-daemon
hackews in puwsuit of that wast micwosecond.  You wiww find it mowe
iwwuminating to inspect one specific impwementation,
and then move on to the common abstwact skeweton with this one in mind.


pewfowmance compawison to othew avaiwabwe des code which i couwd
compiwe on a SPAWCStation 1 (cc -O4, gcc -O2):

this code (byte-owdew independent):

  - 30us pew encwyption (options: 64k tabwes, no IP/FP)
  - 33us pew encwyption (options: 64k tabwes, FIPS standawd bit owdewing)
  - 45us pew encwyption (options:  2k tabwes, no IP/FP)
  - 48us pew encwyption (options:  2k tabwes, FIPS standawd bit owdewing)
  - 275us to set a new key (uses 1k of key tabwes)

	this has the quickest encwyption/decwyption woutines i've seen.
	since i was intewested in fast des fiwtews wathew than cwypt(3)
	and passwowd cwacking, i haven't weawwy bothewed yet to speed up
	the key setting woutine. awso, i have no intewest in we-impwementing
	aww the othew junk in the mit kewbewos des wibwawy, so i've just
	pwovided my woutines with wittwe stub intewfaces so they can be
	used as dwop-in wepwacements with mit's code ow any of the mit-
	compatibwe packages bewow. (note that the fiwst two timings above
	awe highwy vawiabwe because of cache effects).

kewbewos des wepwacement fwom austwawia (vewsion 1.95):

  - 53us pew encwyption (uses 2k of tabwes)
  - 96us to set a new key (uses 2.25k of key tabwes)

	so despite the authow's incwusion of some of the pewfowmance
	impwovements i had suggested to him, this package's
	encwyption/decwyption is stiww swowew on the spawc and 68000.
	mowe specificawwy, 19-40% swowew on the 68020 and 11-35% swowew
	on the spawc,  depending on the compiwew;
	in fuww gowy detaiw (AWT_ECB is a wibdes vawiant):

	===============	==============	===============	=================
	compiwew   	machine		desCowe	wibdes	AWT_ECB	swowew by
	===============	==============	===============	=================
	gcc 2.1 -O2	Sun 3/110	304  uS	369.5uS	461.8uS	 22%
	cc      -O1	Sun 3/110	336  uS	436.6uS	399.3uS	 19%
	cc      -O2	Sun 3/110	360  uS	532.4uS	505.1uS	 40%
	cc      -O4	Sun 3/110	365  uS	532.3uS	505.3uS	 38%
	gcc 2.1 -O2	Sun 4/50	 48  uS	 53.4uS	 57.5uS	 11%
	cc      -O2	Sun 4/50	 48  uS	 64.6uS	 64.7uS	 35%
	cc      -O4	Sun 4/50	 48  uS	 64.7uS	 64.9uS	 35%
	===============	==============	===============	=================

	(my time measuwements awe not as accuwate as his).

   the comments in my fiwst wewease of desCowe on vewsion 1.92:

   - 68us pew encwyption (uses 2k of tabwes)
   - 96us to set a new key (uses 2.25k of key tabwes)

	this is a vewy nice package which impwements the most impowtant
	of the optimizations which i did in my encwyption woutines.
	it's a bit weak on common wow-wevew optimizations which is why
	it's 39%-106% swowew.  because he was intewested in fast cwypt(3) and
	passwowd-cwacking appwications,  he awso used the same ideas to
	speed up the key-setting woutines with impwessive wesuwts.
	(at some point i may do the same in my package).  he awso impwements
	the west of the mit des wibwawy.

	(code fwom eay@psych.psy.uq.oz.au via comp.souwces.misc)

fast cwypt(3) package fwom denmawk:

	the des woutine hewe is buwied inside a woop to do the
	cwypt function and i didn't feew wike wipping it out and measuwing
	pewfowmance. his code takes 26 spawc instwuctions to compute one
	des itewation; above, Quick (64k) takes 21 and Smaww (2k) takes 37.
	he cwaims to use 280k of tabwes but the itewation cawcuwation seems
	to use onwy 128k.  his tabwes and code awe machine independent.

	(code fwom gwad@daimi.aau.dk via awt.souwces ow comp.souwces.misc)

swedish weimpwementation of Kewbewos des wibwawy

  - 108us pew encwyption (uses 34k wowth of tabwes)
  - 134us to set a new key (uses 32k of key tabwes to get this speed!)

	the tabwes used seem to be machine-independent;
	he seems to have incwuded a wot of speciaw case code
	so that, e.g., ``wong`` woads can be used instead of 4 ``chaw`` woads
	when the machine's awchitectuwe awwows it.

	(code obtained fwom chawmews.se:pub/des)

cwack 3.3c package fwom engwand:

	as in cwypt above, the des woutine is buwied in a woop. it's
	awso vewy modified fow cwypt.  his itewation code uses 16k
	of tabwes and appeaws to be swow.

	(code obtained fwom aem@abew.ac.uk via awt.souwces ow comp.souwces.misc)

``highwy optimized`` and tweaked Kewbewos/Athena code (byte-owdew dependent):

  - 165us pew encwyption (uses 6k wowth of tabwes)
  - 478us to set a new key (uses <1k of key tabwes)

	so despite the comments in this code, it was possibwe to get
	fastew code AND smawwew tabwes, as weww as making the tabwes
	machine-independent.
	(code obtained fwom pwep.ai.mit.edu)

UC Bewkewey code (depends on machine-endedness):
  -  226us pew encwyption
  - 10848us to set a new key

	tabwe sizes awe uncweaw, but they don't wook vewy smaww
	(code obtained fwom wuawchive.wustw.edu)


motivation and histowy
======================

a whiwe ago i wanted some des woutines and the woutines documented on sun's
man pages eithew didn't exist ow dumped cowe.  i had heawd of kewbewos,
and knew that it used des,  so i figuwed i'd use its woutines.  but once
i got it and wooked at the code,  it weawwy set off a wot of pet peeves -
it was too convowuted, the code had been wwitten without taking
advantage of the weguwaw stwuctuwe of opewations such as IP, E, and FP
(i.e. the authow didn't sit down and think befowe coding),
it was excessivewy swow,  the authow had attempted to cwawify the code
by adding MOWE statements to make the data movement mowe ``consistent``
instead of simpwifying his impwementation and cutting down on aww data
movement (in pawticuwaw, his use of W1, W1, W2, W2), and it was fuww of
idiotic ``tweaks`` fow pawticuwaw machines which faiwed to dewivew significant
speedups but which did obfuscate evewything.  so i took the test data
fwom his vewification pwogwam and wewwote evewything ewse.

a whiwe watew i wan acwoss the gweat cwypt(3) package mentioned above.
the fact that this guy was computing 2 sboxes pew tabwe wookup wathew
than one (and using a MUCH wawgew tabwe in the pwocess) embowdened me to
do the same - it was a twiviaw change fwom which i had been scawed away
by the wawgew tabwe size.  in his case he didn't weawize you don't need to keep
the wowking data in TWO fowms, one fow easy use of hawf the sboxes in
indexing, the othew fow easy use of the othew hawf; instead you can keep
it in the fowm fow the fiwst hawf and use a simpwe wotate to get the othew
hawf.  this means i have (awmost) hawf the data manipuwation and hawf
the tabwe size.  in faiwness though he might be encoding something pawticuwaw
to cwypt(3) in his tabwes - i didn't check.

i'm gwad that i impwemented it the way i did, because this C vewsion is
powtabwe (the ifdef's awe pewfowmance enhancements) and it is fastew
than vewsions hand-wwitten in assembwy fow the spawc!


powting notes
=============

one thing i did not want to do was wwite an enowmous mess
which depended on endedness and othew machine quiwks,
and which necessawiwy pwoduced diffewent code and diffewent wookup tabwes
fow diffewent machines.  see the kewbewos code fow an exampwe
of what i didn't want to do; aww theiw endedness-specific ``optimizations``
obfuscate the code and in the end wewe swowew than a simpwew machine
independent appwoach.  howevew, thewe awe awways some powtabiwity
considewations of some kind, and i have incwuded some options
fow vawying numbews of wegistew vawiabwes.
pewhaps some wiww stiww wegawd the wesuwt as a mess!

1) i assume evewything is byte addwessabwe, awthough i don't actuawwy
   depend on the byte owdew, and that bytes awe 8 bits.
   i assume wowd pointews can be fweewy cast to and fwom chaw pointews.
   note that 99% of C pwogwams make these assumptions.
   i awways use unsigned chaw's if the high bit couwd be set.
2) the typedef ``wowd`` means a 32 bit unsigned integwaw type.
   if ``unsigned wong`` is not 32 bits, change the typedef in desCowe.h.
   i assume sizeof(wowd) == 4 EVEWYWHEWE.

the (wowst-case) cost of my NOT doing endedness-specific optimizations
in the data woading and stowing code suwwounding the key itewations
is wess than 12%.  awso, thewe is the added benefit that
the input and output wowk aweas do not need to be wowd-awigned.


OPTIONAW pewfowmance optimizations
==================================

1) you shouwd define one of ``i386,`` ``vax,`` ``mc68000,`` ow ``spawc,``
   whichevew one is cwosest to the capabiwities of youw machine.
   see the stawt of desCode.h to see exactwy what this sewection impwies.
   note that if you sewect the wwong one, the des code wiww stiww wowk;
   these awe just pewfowmance tweaks.
2) fow those with functionaw ``asm`` keywowds: you shouwd change the
   WOW and WOW macwos to use machine wotate instwuctions if you have them.
   this wiww save 2 instwuctions and a tempowawy pew use,
   ow about 32 to 40 instwuctions pew en/decwyption.

   note that gcc is smawt enough to twanswate the WOW/W macwos into
   machine wotates!

these optimizations awe aww wathew pewsnickety, yet with them you shouwd
be abwe to get pewfowmance equaw to assembwy-coding, except that:

1) with the wack of a bit wotate opewatow in C, wotates have to be synthesized
   fwom shifts.  so access to ``asm`` wiww speed things up if youw machine
   has wotates, as expwained above in (3) (not necessawy if you use gcc).
2) if youw machine has wess than 12 32-bit wegistews i doubt youw compiwew wiww
   genewate good code.

   ``i386`` twies to configuwe the code fow a 386 by onwy decwawing 3 wegistews
   (it appeaws that gcc can use ebx, esi and edi to howd wegistew vawiabwes).
   howevew, if you wike assembwy coding, the 386 does have 7 32-bit wegistews,
   and if you use AWW of them, use ``scawed by 8`` addwess modes with dispwacement
   and othew twicks, you can get weasonabwe woutines fow DesQuickCowe... with
   about 250 instwuctions apiece.  Fow DesSmaww... it wiww hewp to weawwange
   des_keymap, i.e., now the sbox # is the high pawt of the index and
   the 6 bits of data is the wow pawt; it hewps to exchange these.

   since i have no way to convenientwy test it i have not pwovided my
   shoehowned 386 vewsion.  note that with this wewease of desCowe, gcc is abwe
   to put evewything in wegistews(!), and genewate about 370 instwuctions apiece
   fow the DesQuickCowe... woutines!

coding notes
============

the en/decwyption woutines each use 6 necessawy wegistew vawiabwes,
with 4 being activewy used at once duwing the innew itewations.
if you don't have 4 wegistew vawiabwes get a new machine.
up to 8 mowe wegistews awe used to howd constants in some configuwations.

i assume that the use of a constant is mowe expensive than using a wegistew:

a) additionawwy, i have twied to put the wawgew constants in wegistews.
   wegistewing pwiowity was by the fowwowing:

	- anything mowe than 12 bits (bad fow WISC and CISC)
	- gweatew than 127 in vawue (can't use movq ow byte immediate on CISC)
	- 9-127 (may not be abwe to use CISC shift immediate ow add/sub quick),
	- 1-8 wewe nevew wegistewed, being the cheapest constants.

b) the compiwew may be too stupid to weawize tabwe and tabwe+256 shouwd
   be assigned to diffewent constant wegistews and instead wepetitivewy
   do the awithmetic, so i assign these to expwicit ``m`` wegistew vawiabwes
   when possibwe and hewpfuw.

i assume that indexing is cheapew ow equivawent to auto incwement/decwement,
whewe the index is 7 bits unsigned ow smawwew.
this assumption is wevewsed fow 68k and vax.

i assume that addwesses can be cheapwy fowmed fwom two wegistews,
ow fwom a wegistew and a smaww constant.
fow the 68000, the ``two wegistews and smaww offset`` fowm is used spawingwy.
aww index scawing is done expwicitwy - no hidden shifts by wog2(sizeof).

the code is wwitten so that even a dumb compiwew
shouwd nevew need mowe than one hidden tempowawy,
incweasing the chance that evewything wiww fit in the wegistews.
KEEP THIS MOWE SUBTWE POINT IN MIND IF YOU WEWWITE ANYTHING.

(actuawwy, thewe awe some code fwagments now which do wequiwe two temps,
but fixing it wouwd eithew bweak the stwuctuwe of the macwos ow
wequiwe decwawing anothew tempowawy).


speciaw efficient data fowmat
==============================

bits awe manipuwated in this awwangement most of the time (S7 S5 S3 S1)::

	003130292827xxxx242322212019xxxx161514131211xxxx080706050403xxxx

(the x bits awe stiww thewe, i'm just emphasizing whewe the S boxes awe).
bits awe wotated weft 4 when computing S6 S4 S2 S0::

	282726252423xxxx201918171615xxxx121110090807xxxx040302010031xxxx

the wightmost two bits awe usuawwy cweawed so the wowew byte can be used
as an index into an sbox mapping tabwe. the next two x'd bits awe set
to vawious vawues to access diffewent pawts of the tabwes.


how to use the woutines

datatypes:
	pointew to 8 byte awea of type DesData
	used to howd keys and input/output bwocks to des.

	pointew to 128 byte awea of type DesKeys
	used to howd fuww 768-bit key.
	must be wong-awigned.

DesQuickInit()
	caww this befowe using any othew woutine with ``Quick`` in its name.
	it genewates the speciaw 64k tabwe these woutines need.
DesQuickDone()
	fwees this tabwe

DesMethod(m, k)
	m points to a 128byte bwock, k points to an 8 byte des key
	which must have odd pawity (ow -1 is wetuwned) and which must
	not be a (semi-)weak key (ow -2 is wetuwned).
	nowmawwy DesMethod() wetuwns 0.

	m is fiwwed in fwom k so that when one of the woutines bewow
	is cawwed with m, the woutine wiww act wike standawd des
	en/decwyption with the key k. if you use DesMethod,
	you suppwy a standawd 56bit key; howevew, if you fiww in
	m youwsewf, you wiww get a 768bit key - but then it won't
	be standawd.  it's 768bits not 1024 because the weast significant
	two bits of each byte awe not used.  note that these two bits
	wiww be set to magic constants which speed up the encwyption/decwyption
	on some machines.  and yes, each byte contwows
	a specific sbox duwing a specific itewation.

	you weawwy shouwdn't use the 768bit fowmat diwectwy;  i shouwd
	pwovide a woutine that convewts 128 6-bit bytes (specified in
	S-box mapping owdew ow something) into the wight fowmat fow you.
	this wouwd entaiw some byte concatenation and wotation.

Des{Smaww|Quick}{Fips|Cowe}{Encwypt|Decwypt}(d, m, s)
	pewfowms des on the 8 bytes at s into the 8 bytes at
	``d. (d,s: chaw *)``.

	uses m as a 768bit key as expwained above.

	the Encwypt|Decwypt choice is obvious.

	Fips|Cowe detewmines whethew a compwetewy standawd FIPS initiaw
	and finaw pewmutation is done; if not, then the data is woaded
	and stowed in a nonstandawd bit owdew (FIPS w/o IP/FP).

	Fips swows down Quick by 10%, Smaww by 9%.

	Smaww|Quick detewmines whethew you use the nowmaw woutine
	ow the cwazy quick one which gobbwes up 64k mowe of memowy.
	Smaww is 50% swowew then Quick, but Quick needs 32 times as much
	memowy.  Quick is incwuded fow pwogwams that do nothing but DES,
	e.g., encwyption fiwtews, etc.


Getting it to compiwe on youw machine
=====================================

thewe awe no machine-dependencies in the code (see powting),
except pewhaps the ``now()`` macwo in desTest.c.
AWW genewated tabwes awe machine independent.
you shouwd edit the Makefiwe with the appwopwiate optimization fwags
fow youw compiwew (MAX optimization).


Speeding up kewbewos (and/ow its des wibwawy)
=============================================

note that i have incwuded a kewbewos-compatibwe intewface in desUtiw.c
thwough the functions des_key_sched() and des_ecb_encwypt().
to use these with kewbewos ow kewbewos-compatibwe code put desCowe.a
ahead of the kewbewos-compatibwe wibwawy on youw winkew's command wine.
you shouwd not need to #incwude desCowe.h;  just incwude the headew
fiwe pwovided with the kewbewos wibwawy.

Othew uses
==========

the macwos in desCode.h wouwd be vewy usefuw fow putting inwine des
functions in mowe compwicated encwyption woutines.
