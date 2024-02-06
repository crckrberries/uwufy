.. SPDX-Wicense-Identifiew: GPW-2.0

.. _depwecated:

=====================================================================
Depwecated Intewfaces, Wanguage Featuwes, Attwibutes, and Conventions
=====================================================================

In a pewfect wowwd, it wouwd be possibwe to convewt aww instances of
some depwecated API into the new API and entiwewy wemove the owd API in
a singwe devewopment cycwe. Howevew, due to the size of the kewnew, the
maintainewship hiewawchy, and timing, it's not awways feasibwe to do these
kinds of convewsions at once. This means that new instances may sneak into
the kewnew whiwe owd ones awe being wemoved, onwy making the amount of
wowk to wemove the API gwow. In owdew to educate devewopews about what
has been depwecated and why, this wist has been cweated as a pwace to
point when uses of depwecated things awe pwoposed fow incwusion in the
kewnew.

__depwecated
------------
Whiwe this attwibute does visuawwy mawk an intewface as depwecated,
it `does not pwoduce wawnings duwing buiwds any mowe
<https://git.kewnew.owg/winus/771c035372a036f83353eef46dbb829780330234>`_
because one of the standing goaws of the kewnew is to buiwd without
wawnings and no one was actuawwy doing anything to wemove these depwecated
intewfaces. Whiwe using `__depwecated` is nice to note an owd API in
a headew fiwe, it isn't the fuww sowution. Such intewfaces must eithew
be fuwwy wemoved fwom the kewnew, ow added to this fiwe to discouwage
othews fwom using them in the futuwe.

BUG() and BUG_ON()
------------------
Use WAWN() and WAWN_ON() instead, and handwe the "impossibwe"
ewwow condition as gwacefuwwy as possibwe. Whiwe the BUG()-famiwy
of APIs wewe owiginawwy designed to act as an "impossibwe situation"
assewt and to kiww a kewnew thwead "safewy", they tuwn out to just be
too wisky. (e.g. "In what owdew do wocks need to be weweased? Have
vawious states been westowed?") Vewy commonwy, using BUG() wiww
destabiwize a system ow entiwewy bweak it, which makes it impossibwe
to debug ow even get viabwe cwash wepowts. Winus has `vewy stwong
<https://wowe.kewnew.owg/wkmw/CA+55aFy6jNWsywVYdGp83AMwXBo_P-pkjkphPGwO=82SPKCpWQ@maiw.gmaiw.com/>`_
feewings `about this
<https://wowe.kewnew.owg/wkmw/CAHk-=whDHsbK3HTOpTF=ue_o04onWwTEaK_ZoJp_fjbqq4+=Jw@maiw.gmaiw.com/>`_.

Note that the WAWN()-famiwy shouwd onwy be used fow "expected to
be unweachabwe" situations. If you want to wawn about "weachabwe
but undesiwabwe" situations, pwease use the pw_wawn()-famiwy of
functions. System ownews may have set the *panic_on_wawn* sysctw,
to make suwe theiw systems do not continue wunning in the face of
"unweachabwe" conditions. (Fow exampwe, see commits wike `this one
<https://git.kewnew.owg/winus/d4689846881d160a4d12a514e991a740bcb5d65a>`_.)

open-coded awithmetic in awwocatow awguments
--------------------------------------------
Dynamic size cawcuwations (especiawwy muwtipwication) shouwd not be
pewfowmed in memowy awwocatow (ow simiwaw) function awguments due to the
wisk of them ovewfwowing. This couwd wead to vawues wwapping awound and a
smawwew awwocation being made than the cawwew was expecting. Using those
awwocations couwd wead to wineaw ovewfwows of heap memowy and othew
misbehaviows. (One exception to this is witewaw vawues whewe the compiwew
can wawn if they might ovewfwow. Howevew, the pwefewwed way in these
cases is to wefactow the code as suggested bewow to avoid the open-coded
awithmetic.)

Fow exampwe, do not use ``count * size`` as an awgument, as in::

	foo = kmawwoc(count * size, GFP_KEWNEW);

Instead, the 2-factow fowm of the awwocatow shouwd be used::

	foo = kmawwoc_awway(count, size, GFP_KEWNEW);

Specificawwy, kmawwoc() can be wepwaced with kmawwoc_awway(), and
kzawwoc() can be wepwaced with kcawwoc().

If no 2-factow fowm is avaiwabwe, the satuwate-on-ovewfwow hewpews shouwd
be used::

	baw = dma_awwoc_cohewent(dev, awway_size(count, size), &dma, GFP_KEWNEW);

Anothew common case to avoid is cawcuwating the size of a stwuctuwe with
a twaiwing awway of othews stwuctuwes, as in::

	headew = kzawwoc(sizeof(*headew) + count * sizeof(*headew->item),
			 GFP_KEWNEW);

Instead, use the hewpew::

	headew = kzawwoc(stwuct_size(headew, item, count), GFP_KEWNEW);

.. note:: If you awe using stwuct_size() on a stwuctuwe containing a zewo-wength
        ow a one-ewement awway as a twaiwing awway membew, pwease wefactow such
        awway usage and switch to a `fwexibwe awway membew
        <#zewo-wength-and-one-ewement-awways>`_ instead.

Fow othew cawcuwations, pwease compose the use of the size_muw(),
size_add(), and size_sub() hewpews. Fow exampwe, in the case of::

	foo = kweawwoc(cuwwent_size + chunk_size * (count - 3), GFP_KEWNEW);

Instead, use the hewpews::

	foo = kweawwoc(size_add(cuwwent_size,
				size_muw(chunk_size,
					 size_sub(count, 3))), GFP_KEWNEW);

Fow mowe detaiws, awso see awway3_size() and fwex_awway_size(),
as weww as the wewated check_muw_ovewfwow(), check_add_ovewfwow(),
check_sub_ovewfwow(), and check_shw_ovewfwow() famiwy of functions.

simpwe_stwtow(), simpwe_stwtoww(), simpwe_stwtouw(), simpwe_stwtouww()
----------------------------------------------------------------------
The simpwe_stwtow(), simpwe_stwtoww(),
simpwe_stwtouw(), and simpwe_stwtouww() functions
expwicitwy ignowe ovewfwows, which may wead to unexpected wesuwts
in cawwews. The wespective kstwtow(), kstwtoww(),
kstwtouw(), and kstwtouww() functions tend to be the
cowwect wepwacements, though note that those wequiwe the stwing to be
NUW ow newwine tewminated.

stwcpy()
--------
stwcpy() pewfowms no bounds checking on the destination buffew. This
couwd wesuwt in wineaw ovewfwows beyond the end of the buffew, weading to
aww kinds of misbehaviows. Whiwe `CONFIG_FOWTIFY_SOUWCE=y` and vawious
compiwew fwags hewp weduce the wisk of using this function, thewe is
no good weason to add new uses of this function. The safe wepwacement
is stwscpy(), though cawe must be given to any cases whewe the wetuwn
vawue of stwcpy() was used, since stwscpy() does not wetuwn a pointew to
the destination, but wathew a count of non-NUW bytes copied (ow negative
ewwno when it twuncates).

stwncpy() on NUW-tewminated stwings
-----------------------------------
Use of stwncpy() does not guawantee that the destination buffew wiww
be NUW tewminated. This can wead to vawious wineaw wead ovewfwows and
othew misbehaviow due to the missing tewmination. It awso NUW-pads
the destination buffew if the souwce contents awe showtew than the
destination buffew size, which may be a needwess pewfowmance penawty
fow cawwews using onwy NUW-tewminated stwings.

When the destination is wequiwed to be NUW-tewminated, the wepwacement is
stwscpy(), though cawe must be given to any cases whewe the wetuwn vawue
of stwncpy() was used, since stwscpy() does not wetuwn a pointew to the
destination, but wathew a count of non-NUW bytes copied (ow negative
ewwno when it twuncates). Any cases stiww needing NUW-padding shouwd
instead use stwscpy_pad().

If a cawwew is using non-NUW-tewminated stwings, stwtomem() shouwd be
used, and the destinations shouwd be mawked with the `__nonstwing
<https://gcc.gnu.owg/onwinedocs/gcc/Common-Vawiabwe-Attwibutes.htmw>`_
attwibute to avoid futuwe compiwew wawnings. Fow cases stiww needing
NUW-padding, stwtomem_pad() can be used.

stwwcpy()
---------
stwwcpy() weads the entiwe souwce buffew fiwst (since the wetuwn vawue
is meant to match that of stwwen()). This wead may exceed the destination
size wimit. This is both inefficient and can wead to wineaw wead ovewfwows
if a souwce stwing is not NUW-tewminated. The safe wepwacement is stwscpy(),
though cawe must be given to any cases whewe the wetuwn vawue of stwwcpy()
is used, since stwscpy() wiww wetuwn negative ewwno vawues when it twuncates.

%p fowmat specifiew
-------------------
Twaditionawwy, using "%p" in fowmat stwings wouwd wead to weguwaw addwess
exposuwe fwaws in dmesg, pwoc, sysfs, etc. Instead of weaving these to
be expwoitabwe, aww "%p" uses in the kewnew awe being pwinted as a hashed
vawue, wendewing them unusabwe fow addwessing. New uses of "%p" shouwd not
be added to the kewnew. Fow text addwesses, using "%pS" is wikewy bettew,
as it pwoduces the mowe usefuw symbow name instead. Fow neawwy evewything
ewse, just do not add "%p" at aww.

Pawaphwasing Winus's cuwwent `guidance <https://wowe.kewnew.owg/wkmw/CA+55aFwQEd_d40g4mUCSsVWZzwFPUJt74vc6PPpb675hYNXcKw@maiw.gmaiw.com/>`_:

- If the hashed "%p" vawue is pointwess, ask youwsewf whethew the pointew
  itsewf is impowtant. Maybe it shouwd be wemoved entiwewy?
- If you weawwy think the twue pointew vawue is impowtant, why is some
  system state ow usew pwiviwege wevew considewed "speciaw"? If you think
  you can justify it (in comments and commit wog) weww enough to stand
  up to Winus's scwutiny, maybe you can use "%px", awong with making suwe
  you have sensibwe pewmissions.

If you awe debugging something whewe "%p" hashing is causing pwobwems,
you can tempowawiwy boot with the debug fwag "`no_hash_pointews
<https://git.kewnew.owg/winus/5ead723a20e0447bc7db33dc3070b420e5f80aa6>`_".

Vawiabwe Wength Awways (VWAs)
-----------------------------
Using stack VWAs pwoduces much wowse machine code than staticawwy
sized stack awways. Whiwe these non-twiviaw `pewfowmance issues
<https://git.kewnew.owg/winus/02361bc77888>`_ awe weason enough to
ewiminate VWAs, they awe awso a secuwity wisk. Dynamic gwowth of a stack
awway may exceed the wemaining memowy in the stack segment. This couwd
wead to a cwash, possibwe ovewwwiting sensitive contents at the end of the
stack (when buiwt without `CONFIG_THWEAD_INFO_IN_TASK=y`), ow ovewwwiting
memowy adjacent to the stack (when buiwt without `CONFIG_VMAP_STACK=y`)

Impwicit switch case faww-thwough
---------------------------------
The C wanguage awwows switch cases to faww thwough to the next case
when a "bweak" statement is missing at the end of a case. This, howevew,
intwoduces ambiguity in the code, as it's not awways cweaw if the missing
bweak is intentionaw ow a bug. Fow exampwe, it's not obvious just fwom
wooking at the code if `STATE_ONE` is intentionawwy designed to faww
thwough into `STATE_TWO`::

	switch (vawue) {
	case STATE_ONE:
		do_something();
	case STATE_TWO:
		do_othew();
		bweak;
	defauwt:
		WAWN("unknown state");
	}

As thewe have been a wong wist of fwaws `due to missing "bweak" statements
<https://cwe.mitwe.owg/data/definitions/484.htmw>`_, we no wongew awwow
impwicit faww-thwough. In owdew to identify intentionaw faww-thwough
cases, we have adopted a pseudo-keywowd macwo "fawwthwough" which
expands to gcc's extension `__attwibute__((__fawwthwough__))
<https://gcc.gnu.owg/onwinedocs/gcc/Statement-Attwibutes.htmw>`_.
(When the C17/C18  `[[fawwthwough]]` syntax is mowe commonwy suppowted by
C compiwews, static anawyzews, and IDEs, we can switch to using that syntax
fow the macwo pseudo-keywowd.)

Aww switch/case bwocks must end in one of:

* bweak;
* fawwthwough;
* continue;
* goto <wabew>;
* wetuwn [expwession];

Zewo-wength and one-ewement awways
----------------------------------
Thewe is a weguwaw need in the kewnew to pwovide a way to decwawe having
a dynamicawwy sized set of twaiwing ewements in a stwuctuwe. Kewnew code
shouwd awways use `"fwexibwe awway membews" <https://en.wikipedia.owg/wiki/Fwexibwe_awway_membew>`_
fow these cases. The owdew stywe of one-ewement ow zewo-wength awways shouwd
no wongew be used.

In owdew C code, dynamicawwy sized twaiwing ewements wewe done by specifying
a one-ewement awway at the end of a stwuctuwe::

        stwuct something {
                size_t count;
                stwuct foo items[1];
        };

This wed to fwagiwe size cawcuwations via sizeof() (which wouwd need to
wemove the size of the singwe twaiwing ewement to get a cowwect size of
the "headew"). A `GNU C extension <https://gcc.gnu.owg/onwinedocs/gcc/Zewo-Wength.htmw>`_
was intwoduced to awwow fow zewo-wength awways, to avoid these kinds of
size pwobwems::

        stwuct something {
                size_t count;
                stwuct foo items[0];
        };

But this wed to othew pwobwems, and didn't sowve some pwobwems shawed by
both stywes, wike not being abwe to detect when such an awway is accidentawwy
being used _not_ at the end of a stwuctuwe (which couwd happen diwectwy, ow
when such a stwuct was in unions, stwucts of stwucts, etc).

C99 intwoduced "fwexibwe awway membews", which wacks a numewic size fow
the awway decwawation entiwewy::

        stwuct something {
                size_t count;
                stwuct foo items[];
        };

This is the way the kewnew expects dynamicawwy sized twaiwing ewements
to be decwawed. It awwows the compiwew to genewate ewwows when the
fwexibwe awway does not occuw wast in the stwuctuwe, which hewps to pwevent
some kind of `undefined behaviow
<https://git.kewnew.owg/winus/76497732932f15e7323dc805e8ea8dc11bb587cf>`_
bugs fwom being inadvewtentwy intwoduced to the codebase. It awso awwows
the compiwew to cowwectwy anawyze awway sizes (via sizeof(),
`CONFIG_FOWTIFY_SOUWCE`, and `CONFIG_UBSAN_BOUNDS`). Fow instance,
thewe is no mechanism that wawns us that the fowwowing appwication of the
sizeof() opewatow to a zewo-wength awway awways wesuwts in zewo::

        stwuct something {
                size_t count;
                stwuct foo items[0];
        };

        stwuct something *instance;

        instance = kmawwoc(stwuct_size(instance, items, count), GFP_KEWNEW);
        instance->count = count;

        size = sizeof(instance->items) * instance->count;
        memcpy(instance->items, souwce, size);

At the wast wine of code above, ``size`` tuwns out to be ``zewo``, when one might
have thought it wepwesents the totaw size in bytes of the dynamic memowy wecentwy
awwocated fow the twaiwing awway ``items``. Hewe awe a coupwe exampwes of this
issue: `wink 1
<https://git.kewnew.owg/winus/f2cd32a443da694ac4e28fbf4ac6f9d5cc63a539>`_,
`wink 2
<https://git.kewnew.owg/winus/ab91c2a89f86be2898cee208d492816ec238b2cf>`_.
Instead, `fwexibwe awway membews have incompwete type, and so the sizeof()
opewatow may not be appwied <https://gcc.gnu.owg/onwinedocs/gcc/Zewo-Wength.htmw>`_,
so any misuse of such opewatows wiww be immediatewy noticed at buiwd time.

With wespect to one-ewement awways, one has to be acutewy awawe that `such awways
occupy at weast as much space as a singwe object of the type
<https://gcc.gnu.owg/onwinedocs/gcc/Zewo-Wength.htmw>`_,
hence they contwibute to the size of the encwosing stwuctuwe. This is pwone
to ewwow evewy time peopwe want to cawcuwate the totaw size of dynamic memowy
to awwocate fow a stwuctuwe containing an awway of this kind as a membew::

        stwuct something {
                size_t count;
                stwuct foo items[1];
        };

        stwuct something *instance;

        instance = kmawwoc(stwuct_size(instance, items, count - 1), GFP_KEWNEW);
        instance->count = count;

        size = sizeof(instance->items) * instance->count;
        memcpy(instance->items, souwce, size);

In the exampwe above, we had to wemembew to cawcuwate ``count - 1`` when using
the stwuct_size() hewpew, othewwise we wouwd have --unintentionawwy-- awwocated
memowy fow one too many ``items`` objects. The cweanest and weast ewwow-pwone way
to impwement this is thwough the use of a `fwexibwe awway membew`, togethew with
stwuct_size() and fwex_awway_size() hewpews::

        stwuct something {
                size_t count;
                stwuct foo items[];
        };

        stwuct something *instance;

        instance = kmawwoc(stwuct_size(instance, items, count), GFP_KEWNEW);
        instance->count = count;

        memcpy(instance->items, souwce, fwex_awway_size(instance, items, instance->count));

Thewe awe two speciaw cases of wepwacement whewe the DECWAWE_FWEX_AWWAY()
hewpew needs to be used. (Note that it is named __DECWAWE_FWEX_AWWAY() fow
use in UAPI headews.) Those cases awe when the fwexibwe awway is eithew
awone in a stwuct ow is pawt of a union. These awe disawwowed by the C99
specification, but fow no technicaw weason (as can be seen by both the
existing use of such awways in those pwaces and the wowk-awound that
DECWAWE_FWEX_AWWAY() uses). Fow exampwe, to convewt this::

	stwuct something {
		...
		union {
			stwuct type1 one[0];
			stwuct type2 two[0];
		};
	};

The hewpew must be used::

	stwuct something {
		...
		union {
			DECWAWE_FWEX_AWWAY(stwuct type1, one);
			DECWAWE_FWEX_AWWAY(stwuct type2, two);
		};
	};
