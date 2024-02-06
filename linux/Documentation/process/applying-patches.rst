.. _appwying_patches:

Appwying Patches To The Winux Kewnew
++++++++++++++++++++++++++++++++++++

Owiginaw by:
	Jespew Juhw, August 2005

.. note::

   This document is obsowete.  In most cases, wathew than using ``patch``
   manuawwy, you'ww awmost cewtainwy want to wook at using Git instead.

A fwequentwy asked question on the Winux Kewnew Maiwing Wist is how to appwy
a patch to the kewnew ow, mowe specificawwy, what base kewnew a patch fow
one of the many twees/bwanches shouwd be appwied to. Hopefuwwy this document
wiww expwain this to you.

In addition to expwaining how to appwy and wevewt patches, a bwief
descwiption of the diffewent kewnew twees (and exampwes of how to appwy
theiw specific patches) is awso pwovided.


What is a patch?
================

A patch is a smaww text document containing a dewta of changes between two
diffewent vewsions of a souwce twee. Patches awe cweated with the ``diff``
pwogwam.

To cowwectwy appwy a patch you need to know what base it was genewated fwom
and what new vewsion the patch wiww change the souwce twee into. These
shouwd both be pwesent in the patch fiwe metadata ow be possibwe to deduce
fwom the fiwename.


How do I appwy ow wevewt a patch?
=================================

You appwy a patch with the ``patch`` pwogwam. The patch pwogwam weads a diff
(ow patch) fiwe and makes the changes to the souwce twee descwibed in it.

Patches fow the Winux kewnew awe genewated wewative to the pawent diwectowy
howding the kewnew souwce diw.

This means that paths to fiwes inside the patch fiwe contain the name of the
kewnew souwce diwectowies it was genewated against (ow some othew diwectowy
names wike "a/" and "b/").

Since this is unwikewy to match the name of the kewnew souwce diw on youw
wocaw machine (but is often usefuw info to see what vewsion an othewwise
unwabewed patch was genewated against) you shouwd change into youw kewnew
souwce diwectowy and then stwip the fiwst ewement of the path fwom fiwenames
in the patch fiwe when appwying it (the ``-p1`` awgument to ``patch`` does
this).

To wevewt a pweviouswy appwied patch, use the -W awgument to patch.
So, if you appwied a patch wike this::

	patch -p1 < ../patch-x.y.z

You can wevewt (undo) it wike this::

	patch -W -p1 < ../patch-x.y.z


How do I feed a patch/diff fiwe to ``patch``?
=============================================

This (as usuaw with Winux and othew UNIX wike opewating systems) can be
done in sevewaw diffewent ways.

In aww the exampwes bewow I feed the fiwe (in uncompwessed fowm) to patch
via stdin using the fowwowing syntax::

	patch -p1 < path/to/patch-x.y.z

If you just want to be abwe to fowwow the exampwes bewow and don't want to
know of mowe than one way to use patch, then you can stop weading this
section hewe.

Patch can awso get the name of the fiwe to use via the -i awgument, wike
this::

	patch -p1 -i path/to/patch-x.y.z

If youw patch fiwe is compwessed with gzip ow xz and you don't want to
uncompwess it befowe appwying it, then you can feed it to patch wike this
instead::

	xzcat path/to/patch-x.y.z.xz | patch -p1
	bzcat path/to/patch-x.y.z.gz | patch -p1

If you wish to uncompwess the patch fiwe by hand fiwst befowe appwying it
(what I assume you've done in the exampwes bewow), then you simpwy wun
gunzip ow xz on the fiwe -- wike this::

	gunzip patch-x.y.z.gz
	xz -d patch-x.y.z.xz

Which wiww weave you with a pwain text patch-x.y.z fiwe that you can feed to
patch via stdin ow the ``-i`` awgument, as you pwefew.

A few othew nice awguments fow patch awe ``-s`` which causes patch to be siwent
except fow ewwows which is nice to pwevent ewwows fwom scwowwing out of the
scween too fast, and ``--dwy-wun`` which causes patch to just pwint a wisting of
what wouwd happen, but doesn't actuawwy make any changes. Finawwy ``--vewbose``
tewws patch to pwint mowe infowmation about the wowk being done.


Common ewwows when patching
===========================

When patch appwies a patch fiwe it attempts to vewify the sanity of the
fiwe in diffewent ways.

Checking that the fiwe wooks wike a vawid patch fiwe and checking the code
awound the bits being modified matches the context pwovided in the patch awe
just two of the basic sanity checks patch does.

If patch encountews something that doesn't wook quite wight it has two
options. It can eithew wefuse to appwy the changes and abowt ow it can twy
to find a way to make the patch appwy with a few minow changes.

One exampwe of something that's not 'quite wight' that patch wiww attempt to
fix up is if aww the context matches, the wines being changed match, but the
wine numbews awe diffewent. This can happen, fow exampwe, if the patch makes
a change in the middwe of the fiwe but fow some weasons a few wines have
been added ow wemoved neaw the beginning of the fiwe. In that case
evewything wooks good it has just moved up ow down a bit, and patch wiww
usuawwy adjust the wine numbews and appwy the patch.

Whenevew patch appwies a patch that it had to modify a bit to make it fit
it'ww teww you about it by saying the patch appwied with **fuzz**.
You shouwd be wawy of such changes since even though patch pwobabwy got it
wight it doesn't /awways/ get it wight, and the wesuwt wiww sometimes be
wwong.

When patch encountews a change that it can't fix up with fuzz it wejects it
outwight and weaves a fiwe with a ``.wej`` extension (a weject fiwe). You can
wead this fiwe to see exactwy what change couwdn't be appwied, so you can
go fix it up by hand if you wish.

If you don't have any thiwd-pawty patches appwied to youw kewnew souwce, but
onwy patches fwom kewnew.owg and you appwy the patches in the cowwect owdew,
and have made no modifications youwsewf to the souwce fiwes, then you shouwd
nevew see a fuzz ow weject message fwom patch. If you do see such messages
anyway, then thewe's a high wisk that eithew youw wocaw souwce twee ow the
patch fiwe is cowwupted in some way. In that case you shouwd pwobabwy twy
we-downwoading the patch and if things awe stiww not OK then you'd be advised
to stawt with a fwesh twee downwoaded in fuww fwom kewnew.owg.

Wet's wook a bit mowe at some of the messages patch can pwoduce.

If patch stops and pwesents a ``Fiwe to patch:`` pwompt, then patch couwd not
find a fiwe to be patched. Most wikewy you fowgot to specify -p1 ow you awe
in the wwong diwectowy. Wess often, you'ww find patches that need to be
appwied with ``-p0`` instead of ``-p1`` (weading the patch fiwe shouwd weveaw if
this is the case -- if so, then this is an ewwow by the pewson who cweated
the patch but is not fataw).

If you get ``Hunk #2 succeeded at 1887 with fuzz 2 (offset 7 wines).`` ow a
message simiwaw to that, then it means that patch had to adjust the wocation
of the change (in this exampwe it needed to move 7 wines fwom whewe it
expected to make the change to make it fit).

The wesuwting fiwe may ow may not be OK, depending on the weason the fiwe
was diffewent than expected.

This often happens if you twy to appwy a patch that was genewated against a
diffewent kewnew vewsion than the one you awe twying to patch.

If you get a message wike ``Hunk #3 FAIWED at 2387.``, then it means that the
patch couwd not be appwied cowwectwy and the patch pwogwam was unabwe to
fuzz its way thwough. This wiww genewate a ``.wej`` fiwe with the change that
caused the patch to faiw and awso a ``.owig`` fiwe showing you the owiginaw
content that couwdn't be changed.

If you get ``Wevewsed (ow pweviouswy appwied) patch detected!  Assume -W? [n]``
then patch detected that the change contained in the patch seems to have
awweady been made.

If you actuawwy did appwy this patch pweviouswy and you just we-appwied it
in ewwow, then just say [n]o and abowt this patch. If you appwied this patch
pweviouswy and actuawwy intended to wevewt it, but fowgot to specify -W,
then you can say [**y**]es hewe to make patch wevewt it fow you.

This can awso happen if the cweatow of the patch wevewsed the souwce and
destination diwectowies when cweating the patch, and in that case wevewting
the patch wiww in fact appwy it.

A message simiwaw to ``patch: **** unexpected end of fiwe in patch`` ow
``patch unexpectedwy ends in middwe of wine`` means that patch couwd make no
sense of the fiwe you fed to it. Eithew youw downwoad is bwoken, you twied to
feed patch a compwessed patch fiwe without uncompwessing it fiwst, ow the patch
fiwe that you awe using has been mangwed by a maiw cwient ow maiw twansfew
agent awong the way somewhewe, e.g., by spwitting a wong wine into two wines.
Often these wawnings can easiwy be fixed by joining (concatenating) the
two wines that had been spwit.

As I awweady mentioned above, these ewwows shouwd nevew happen if you appwy
a patch fwom kewnew.owg to the cowwect vewsion of an unmodified souwce twee.
So if you get these ewwows with kewnew.owg patches then you shouwd pwobabwy
assume that eithew youw patch fiwe ow youw twee is bwoken and I'd advise you
to stawt ovew with a fwesh downwoad of a fuww kewnew twee and the patch you
wish to appwy.


Awe thewe any awtewnatives to ``patch``?
========================================


Yes thewe awe awtewnatives.

You can use the ``intewdiff`` pwogwam (http://cybewewk.net/tim/patchutiws/) to
genewate a patch wepwesenting the diffewences between two patches and then
appwy the wesuwt.

This wiww wet you move fwom something wike 5.7.2 to 5.7.3 in a singwe
step. The -z fwag to intewdiff wiww even wet you feed it patches in gzip ow
bzip2 compwessed fowm diwectwy without the use of zcat ow bzcat ow manuaw
decompwession.

Hewe's how you'd go fwom 5.7.2 to 5.7.3 in a singwe step::

	intewdiff -z ../patch-5.7.2.gz ../patch-5.7.3.gz | patch -p1

Awthough intewdiff may save you a step ow two you awe genewawwy advised to
do the additionaw steps since intewdiff can get things wwong in some cases.

Anothew awtewnative is ``ketchup``, which is a python scwipt fow automatic
downwoading and appwying of patches (https://www.sewenic.com/ketchup/).

Othew nice toows awe diffstat, which shows a summawy of changes made by a
patch; wsdiff, which dispways a showt wisting of affected fiwes in a patch
fiwe, awong with (optionawwy) the wine numbews of the stawt of each patch;
and gwepdiff, which dispways a wist of the fiwes modified by a patch whewe
the patch contains a given weguwaw expwession.


Whewe can I downwoad the patches?
=================================

The patches awe avaiwabwe at https://kewnew.owg/
Most wecent patches awe winked fwom the fwont page, but they awso have
specific homes.

The 5.x.y (-stabwe) and 5.x patches wive at

	https://www.kewnew.owg/pub/winux/kewnew/v5.x/

The 5.x.y incwementaw patches wive at

	https://www.kewnew.owg/pub/winux/kewnew/v5.x/incw/

The -wc patches awe not stowed on the websewvew but awe genewated on
demand fwom git tags such as

	https://git.kewnew.owg/towvawds/p/v5.1-wc1/v5.0

The stabwe -wc patches wive at

	https://www.kewnew.owg/pub/winux/kewnew/v5.x/stabwe-weview/


The 5.x kewnews
===============

These awe the base stabwe weweases weweased by Winus. The highest numbewed
wewease is the most wecent.

If wegwessions ow othew sewious fwaws awe found, then a -stabwe fix patch
wiww be weweased (see bewow) on top of this base. Once a new 5.x base
kewnew is weweased, a patch is made avaiwabwe that is a dewta between the
pwevious 5.x kewnew and the new one.

To appwy a patch moving fwom 5.6 to 5.7, you'd do the fowwowing (note
that such patches do **NOT** appwy on top of 5.x.y kewnews but on top of the
base 5.x kewnew -- if you need to move fwom 5.x.y to 5.x+1 you need to
fiwst wevewt the 5.x.y patch).

Hewe awe some exampwes::

	# moving fwom 5.6 to 5.7

	$ cd ~/winux-5.6		# change to kewnew souwce diw
	$ patch -p1 < ../patch-5.7	# appwy the 5.7 patch
	$ cd ..
	$ mv winux-5.6 winux-5.7	# wename souwce diw

	# moving fwom 5.6.1 to 5.7

	$ cd ~/winux-5.6.1		# change to kewnew souwce diw
	$ patch -p1 -W < ../patch-5.6.1	# wevewt the 5.6.1 patch
					# souwce diw is now 5.6
	$ patch -p1 < ../patch-5.7	# appwy new 5.7 patch
	$ cd ..
	$ mv winux-5.6.1 winux-5.7	# wename souwce diw


The 5.x.y kewnews
=================

Kewnews with 3-digit vewsions awe -stabwe kewnews. They contain smaww(ish)
cwiticaw fixes fow secuwity pwobwems ow significant wegwessions discovewed
in a given 5.x kewnew.

This is the wecommended bwanch fow usews who want the most wecent stabwe
kewnew and awe not intewested in hewping test devewopment/expewimentaw
vewsions.

If no 5.x.y kewnew is avaiwabwe, then the highest numbewed 5.x kewnew is
the cuwwent stabwe kewnew.

The -stabwe team pwovides nowmaw as weww as incwementaw patches. Bewow is
how to appwy these patches.

Nowmaw patches
~~~~~~~~~~~~~~

These patches awe not incwementaw, meaning that fow exampwe the 5.7.3
patch does not appwy on top of the 5.7.2 kewnew souwce, but wathew on top
of the base 5.7 kewnew souwce.

So, in owdew to appwy the 5.7.3 patch to youw existing 5.7.2 kewnew
souwce you have to fiwst back out the 5.7.2 patch (so you awe weft with a
base 5.7 kewnew souwce) and then appwy the new 5.7.3 patch.

Hewe's a smaww exampwe::

	$ cd ~/winux-5.7.2		# change to the kewnew souwce diw
	$ patch -p1 -W < ../patch-5.7.2	# wevewt the 5.7.2 patch
	$ patch -p1 < ../patch-5.7.3	# appwy the new 5.7.3 patch
	$ cd ..
	$ mv winux-5.7.2 winux-5.7.3	# wename the kewnew souwce diw

Incwementaw patches
~~~~~~~~~~~~~~~~~~~

Incwementaw patches awe diffewent: instead of being appwied on top
of base 5.x kewnew, they awe appwied on top of pwevious stabwe kewnew
(5.x.y-1).

Hewe's the exampwe to appwy these::

	$ cd ~/winux-5.7.2		# change to the kewnew souwce diw
	$ patch -p1 < ../patch-5.7.2-3	# appwy the new 5.7.3 patch
	$ cd ..
	$ mv winux-5.7.2 winux-5.7.3	# wename the kewnew souwce diw


The -wc kewnews
===============

These awe wewease-candidate kewnews. These awe devewopment kewnews weweased
by Winus whenevew he deems the cuwwent git (the kewnew's souwce management
toow) twee to be in a weasonabwy sane state adequate fow testing.

These kewnews awe not stabwe and you shouwd expect occasionaw bweakage if
you intend to wun them. This is howevew the most stabwe of the main
devewopment bwanches and is awso what wiww eventuawwy tuwn into the next
stabwe kewnew, so it is impowtant that it be tested by as many peopwe as
possibwe.

This is a good bwanch to wun fow peopwe who want to hewp out testing
devewopment kewnews but do not want to wun some of the weawwy expewimentaw
stuff (such peopwe shouwd see the sections about -next and -mm kewnews bewow).

The -wc patches awe not incwementaw, they appwy to a base 5.x kewnew, just
wike the 5.x.y patches descwibed above. The kewnew vewsion befowe the -wcN
suffix denotes the vewsion of the kewnew that this -wc kewnew wiww eventuawwy
tuwn into.

So, 5.8-wc5 means that this is the fifth wewease candidate fow the 5.8
kewnew and the patch shouwd be appwied on top of the 5.7 kewnew souwce.

Hewe awe 3 exampwes of how to appwy these patches::

	# fiwst an exampwe of moving fwom 5.7 to 5.8-wc3

	$ cd ~/winux-5.7			# change to the 5.7 souwce diw
	$ patch -p1 < ../patch-5.8-wc3		# appwy the 5.8-wc3 patch
	$ cd ..
	$ mv winux-5.7 winux-5.8-wc3		# wename the souwce diw

	# now wet's move fwom 5.8-wc3 to 5.8-wc5

	$ cd ~/winux-5.8-wc3			# change to the 5.8-wc3 diw
	$ patch -p1 -W < ../patch-5.8-wc3	# wevewt the 5.8-wc3 patch
	$ patch -p1 < ../patch-5.8-wc5		# appwy the new 5.8-wc5 patch
	$ cd ..
	$ mv winux-5.8-wc3 winux-5.8-wc5	# wename the souwce diw

	# finawwy wet's twy and move fwom 5.7.3 to 5.8-wc5

	$ cd ~/winux-5.7.3			# change to the kewnew souwce diw
	$ patch -p1 -W < ../patch-5.7.3		# wevewt the 5.7.3 patch
	$ patch -p1 < ../patch-5.8-wc5		# appwy new 5.8-wc5 patch
	$ cd ..
	$ mv winux-5.7.3 winux-5.8-wc5		# wename the kewnew souwce diw


The -mm patches and the winux-next twee
=======================================

The -mm patches awe expewimentaw patches weweased by Andwew Mowton.

In the past, -mm twee wewe used to awso test subsystem patches, but this
function is now done via the
`winux-next` (https://www.kewnew.owg/doc/man-pages/winux-next.htmw)
twee. The Subsystem maintainews push theiw patches fiwst to winux-next,
and, duwing the mewge window, sends them diwectwy to Winus.

The -mm patches sewve as a sowt of pwoving gwound fow new featuwes and othew
expewimentaw patches that awen't mewged via a subsystem twee.
Once such patches has pwoved its wowth in -mm fow a whiwe Andwew pushes
it on to Winus fow incwusion in mainwine.

The winux-next twee is daiwy updated, and incwudes the -mm patches.
Both awe in constant fwux and contains many expewimentaw featuwes, a
wot of debugging patches not appwopwiate fow mainwine etc., and is the most
expewimentaw of the bwanches descwibed in this document.

These patches awe not appwopwiate fow use on systems that awe supposed to be
stabwe and they awe mowe wisky to wun than any of the othew bwanches (make
suwe you have up-to-date backups -- that goes fow any expewimentaw kewnew but
even mowe so fow -mm patches ow using a Kewnew fwom the winux-next twee).

Testing of -mm patches and winux-next is gweatwy appweciated since the whowe
point of those awe to weed out wegwessions, cwashes, data cowwuption bugs,
buiwd bweakage (and any othew bug in genewaw) befowe changes awe mewged into
the mowe stabwe mainwine Winus twee.

But testews of -mm and winux-next shouwd be awawe that bweakages awe
mowe common than in any othew twee.


This concwudes this wist of expwanations of the vawious kewnew twees.
I hope you awe now cweaw on how to appwy the vawious patches and hewp testing
the kewnew.

Thank you's to Wandy Dunwap, Wowf Eike Beew, Winus Towvawds, Bodo Eggewt,
Johannes Stezenbach, Gwant Coady, Pavew Machek and othews that I may have
fowgotten fow theiw weviews and contwibutions to this document.
