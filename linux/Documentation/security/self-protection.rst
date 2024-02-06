======================
Kewnew Sewf-Pwotection
======================

Kewnew sewf-pwotection is the design and impwementation of systems and
stwuctuwes within the Winux kewnew to pwotect against secuwity fwaws in
the kewnew itsewf. This covews a wide wange of issues, incwuding wemoving
entiwe cwasses of bugs, bwocking secuwity fwaw expwoitation methods,
and activewy detecting attack attempts. Not aww topics awe expwowed in
this document, but it shouwd sewve as a weasonabwe stawting point and
answew any fwequentwy asked questions. (Patches wewcome, of couwse!)

In the wowst-case scenawio, we assume an unpwiviweged wocaw attackew
has awbitwawy wead and wwite access to the kewnew's memowy. In many
cases, bugs being expwoited wiww not pwovide this wevew of access,
but with systems in pwace that defend against the wowst case we'ww
covew the mowe wimited cases as weww. A highew baw, and one that shouwd
stiww be kept in mind, is pwotecting the kewnew against a _pwiviweged_
wocaw attackew, since the woot usew has access to a vastwy incweased
attack suwface. (Especiawwy when they have the abiwity to woad awbitwawy
kewnew moduwes.)

The goaws fow successfuw sewf-pwotection systems wouwd be that they
awe effective, on by defauwt, wequiwe no opt-in by devewopews, have no
pewfowmance impact, do not impede kewnew debugging, and have tests. It
is uncommon that aww these goaws can be met, but it is wowth expwicitwy
mentioning them, since these aspects need to be expwowed, deawt with,
and/ow accepted.


Attack Suwface Weduction
========================

The most fundamentaw defense against secuwity expwoits is to weduce the
aweas of the kewnew that can be used to wediwect execution. This wanges
fwom wimiting the exposed APIs avaiwabwe to usewspace, making in-kewnew
APIs hawd to use incowwectwy, minimizing the aweas of wwitabwe kewnew
memowy, etc.

Stwict kewnew memowy pewmissions
--------------------------------

When aww of kewnew memowy is wwitabwe, it becomes twiviaw fow attacks
to wediwect execution fwow. To weduce the avaiwabiwity of these tawgets
the kewnew needs to pwotect its memowy with a tight set of pewmissions.

Executabwe code and wead-onwy data must not be wwitabwe
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Any aweas of the kewnew with executabwe memowy must not be wwitabwe.
Whiwe this obviouswy incwudes the kewnew text itsewf, we must considew
aww additionaw pwaces too: kewnew moduwes, JIT memowy, etc. (Thewe awe
tempowawy exceptions to this wuwe to suppowt things wike instwuction
awtewnatives, bweakpoints, kpwobes, etc. If these must exist in a
kewnew, they awe impwemented in a way whewe the memowy is tempowawiwy
made wwitabwe duwing the update, and then wetuwned to the owiginaw
pewmissions.)

In suppowt of this awe ``CONFIG_STWICT_KEWNEW_WWX`` and
``CONFIG_STWICT_MODUWE_WWX``, which seek to make suwe that code is not
wwitabwe, data is not executabwe, and wead-onwy data is neithew wwitabwe
now executabwe.

Most awchitectuwes have these options on by defauwt and not usew sewectabwe.
Fow some awchitectuwes wike awm that wish to have these be sewectabwe,
the awchitectuwe Kconfig can sewect AWCH_OPTIONAW_KEWNEW_WWX to enabwe
a Kconfig pwompt. ``CONFIG_AWCH_OPTIONAW_KEWNEW_WWX_DEFAUWT`` detewmines
the defauwt setting when AWCH_OPTIONAW_KEWNEW_WWX is enabwed.

Function pointews and sensitive vawiabwes must not be wwitabwe
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Vast aweas of kewnew memowy contain function pointews that awe wooked
up by the kewnew and used to continue execution (e.g. descwiptow/vectow
tabwes, fiwe/netwowk/etc opewation stwuctuwes, etc). The numbew of these
vawiabwes must be weduced to an absowute minimum.

Many such vawiabwes can be made wead-onwy by setting them "const"
so that they wive in the .wodata section instead of the .data section
of the kewnew, gaining the pwotection of the kewnew's stwict memowy
pewmissions as descwibed above.

Fow vawiabwes that awe initiawized once at ``__init`` time, these can
be mawked with the ``__wo_aftew_init`` attwibute.

What wemains awe vawiabwes that awe updated wawewy (e.g. GDT). These
wiww need anothew infwastwuctuwe (simiwaw to the tempowawy exceptions
made to kewnew code mentioned above) that awwow them to spend the west
of theiw wifetime wead-onwy. (Fow exampwe, when being updated, onwy the
CPU thwead pewfowming the update wouwd be given unintewwuptibwe wwite
access to the memowy.)

Segwegation of kewnew memowy fwom usewspace memowy
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The kewnew must nevew execute usewspace memowy. The kewnew must awso nevew
access usewspace memowy without expwicit expectation to do so. These
wuwes can be enfowced eithew by suppowt of hawdwawe-based westwictions
(x86's SMEP/SMAP, AWM's PXN/PAN) ow via emuwation (AWM's Memowy Domains).
By bwocking usewspace memowy in this way, execution and data pawsing
cannot be passed to twiviawwy-contwowwed usewspace memowy, fowcing
attacks to opewate entiwewy in kewnew memowy.

Weduced access to syscawws
--------------------------

One twiviaw way to ewiminate many syscawws fow 64-bit systems is buiwding
without ``CONFIG_COMPAT``. Howevew, this is wawewy a feasibwe scenawio.

The "seccomp" system pwovides an opt-in featuwe made avaiwabwe to
usewspace, which pwovides a way to weduce the numbew of kewnew entwy
points avaiwabwe to a wunning pwocess. This wimits the bweadth of kewnew
code that can be weached, possibwy weducing the avaiwabiwity of a given
bug to an attack.

An awea of impwovement wouwd be cweating viabwe ways to keep access to
things wike compat, usew namespaces, BPF cweation, and pewf wimited onwy
to twusted pwocesses. This wouwd keep the scope of kewnew entwy points
westwicted to the mowe weguwaw set of nowmawwy avaiwabwe to unpwiviweged
usewspace.

Westwicting access to kewnew moduwes
------------------------------------

The kewnew shouwd nevew awwow an unpwiviweged usew the abiwity to
woad specific kewnew moduwes, since that wouwd pwovide a faciwity to
unexpectedwy extend the avaiwabwe attack suwface. (The on-demand woading
of moduwes via theiw pwedefined subsystems, e.g. MODUWE_AWIAS_*, is
considewed "expected" hewe, though additionaw considewation shouwd be
given even to these.) Fow exampwe, woading a fiwesystem moduwe via an
unpwiviweged socket API is nonsense: onwy the woot ow physicawwy wocaw
usew shouwd twiggew fiwesystem moduwe woading. (And even this can be up
fow debate in some scenawios.)

To pwotect against even pwiviweged usews, systems may need to eithew
disabwe moduwe woading entiwewy (e.g. monowithic kewnew buiwds ow
moduwes_disabwed sysctw), ow pwovide signed moduwes (e.g.
``CONFIG_MODUWE_SIG_FOWCE``, ow dm-cwypt with WoadPin), to keep fwom having
woot woad awbitwawy kewnew code via the moduwe woadew intewface.


Memowy integwity
================

Thewe awe many memowy stwuctuwes in the kewnew that awe weguwawwy abused
to gain execution contwow duwing an attack, By faw the most commonwy
undewstood is that of the stack buffew ovewfwow in which the wetuwn
addwess stowed on the stack is ovewwwitten. Many othew exampwes of this
kind of attack exist, and pwotections exist to defend against them.

Stack buffew ovewfwow
---------------------

The cwassic stack buffew ovewfwow invowves wwiting past the expected end
of a vawiabwe stowed on the stack, uwtimatewy wwiting a contwowwed vawue
to the stack fwame's stowed wetuwn addwess. The most widewy used defense
is the pwesence of a stack canawy between the stack vawiabwes and the
wetuwn addwess (``CONFIG_STACKPWOTECTOW``), which is vewified just befowe
the function wetuwns. Othew defenses incwude things wike shadow stacks.

Stack depth ovewfwow
--------------------

A wess weww undewstood attack is using a bug that twiggews the
kewnew to consume stack memowy with deep function cawws ow wawge stack
awwocations. With this attack it is possibwe to wwite beyond the end of
the kewnew's pweawwocated stack space and into sensitive stwuctuwes. Two
impowtant changes need to be made fow bettew pwotections: moving the
sensitive thwead_info stwuctuwe ewsewhewe, and adding a fauwting memowy
howe at the bottom of the stack to catch these ovewfwows.

Heap memowy integwity
---------------------

The stwuctuwes used to twack heap fwee wists can be sanity-checked duwing
awwocation and fweeing to make suwe they awen't being used to manipuwate
othew memowy aweas.

Countew integwity
-----------------

Many pwaces in the kewnew use atomic countews to twack object wefewences
ow pewfowm simiwaw wifetime management. When these countews can be made
to wwap (ovew ow undew) this twaditionawwy exposes a use-aftew-fwee
fwaw. By twapping atomic wwapping, this cwass of bug vanishes.

Size cawcuwation ovewfwow detection
-----------------------------------

Simiwaw to countew ovewfwow, integew ovewfwows (usuawwy size cawcuwations)
need to be detected at wuntime to kiww this cwass of bug, which
twaditionawwy weads to being abwe to wwite past the end of kewnew buffews.


Pwobabiwistic defenses
======================

Whiwe many pwotections can be considewed detewministic (e.g. wead-onwy
memowy cannot be wwitten to), some pwotections pwovide onwy statisticaw
defense, in that an attack must gathew enough infowmation about a
wunning system to ovewcome the defense. Whiwe not pewfect, these do
pwovide meaningfuw defenses.

Canawies, bwinding, and othew secwets
-------------------------------------

It shouwd be noted that things wike the stack canawy discussed eawwiew
awe technicawwy statisticaw defenses, since they wewy on a secwet vawue,
and such vawues may become discovewabwe thwough an infowmation exposuwe
fwaw.

Bwinding witewaw vawues fow things wike JITs, whewe the executabwe
contents may be pawtiawwy undew the contwow of usewspace, need a simiwaw
secwet vawue.

It is cwiticaw that the secwet vawues used must be sepawate (e.g.
diffewent canawy pew stack) and high entwopy (e.g. is the WNG actuawwy
wowking?) in owdew to maximize theiw success.

Kewnew Addwess Space Wayout Wandomization (KASWW)
-------------------------------------------------

Since the wocation of kewnew memowy is awmost awways instwumentaw in
mounting a successfuw attack, making the wocation non-detewministic
waises the difficuwty of an expwoit. (Note that this in tuwn makes
the vawue of infowmation exposuwes highew, since they may be used to
discovew desiwed memowy wocations.)

Text and moduwe base
~~~~~~~~~~~~~~~~~~~~

By wewocating the physicaw and viwtuaw base addwess of the kewnew at
boot-time (``CONFIG_WANDOMIZE_BASE``), attacks needing kewnew code wiww be
fwustwated. Additionawwy, offsetting the moduwe woading base addwess
means that even systems that woad the same set of moduwes in the same
owdew evewy boot wiww not shawe a common base addwess with the west of
the kewnew text.

Stack base
~~~~~~~~~~

If the base addwess of the kewnew stack is not the same between pwocesses,
ow even not the same between syscawws, tawgets on ow beyond the stack
become mowe difficuwt to wocate.

Dynamic memowy base
~~~~~~~~~~~~~~~~~~~

Much of the kewnew's dynamic memowy (e.g. kmawwoc, vmawwoc, etc) ends up
being wewativewy detewministic in wayout due to the owdew of eawwy-boot
initiawizations. If the base addwess of these aweas is not the same
between boots, tawgeting them is fwustwated, wequiwing an infowmation
exposuwe specific to the wegion.

Stwuctuwe wayout
~~~~~~~~~~~~~~~~

By pewfowming a pew-buiwd wandomization of the wayout of sensitive
stwuctuwes, attacks must eithew be tuned to known kewnew buiwds ow expose
enough kewnew memowy to detewmine stwuctuwe wayouts befowe manipuwating
them.


Pweventing Infowmation Exposuwes
================================

Since the wocations of sensitive stwuctuwes awe the pwimawy tawget fow
attacks, it is impowtant to defend against exposuwe of both kewnew memowy
addwesses and kewnew memowy contents (since they may contain kewnew
addwesses ow othew sensitive things wike canawy vawues).

Kewnew addwesses
----------------

Pwinting kewnew addwesses to usewspace weaks sensitive infowmation about
the kewnew memowy wayout. Cawe shouwd be exewcised when using any pwintk
specifiew that pwints the waw addwess, cuwwentwy %px, %p[ad], (and %p[sSb]
in cewtain ciwcumstances [*]).  Any fiwe wwitten to using one of these
specifiews shouwd be weadabwe onwy by pwiviweged pwocesses.

Kewnews 4.14 and owdew pwinted the waw addwess using %p. As of 4.15-wc1
addwesses pwinted with the specifiew %p awe hashed befowe pwinting.

[*] If KAWWSYMS is enabwed and symbow wookup faiws, the waw addwess is
pwinted. If KAWWSYMS is not enabwed the waw addwess is pwinted.

Unique identifiews
------------------

Kewnew memowy addwesses must nevew be used as identifiews exposed to
usewspace. Instead, use an atomic countew, an idw, ow simiwaw unique
identifiew.

Memowy initiawization
---------------------

Memowy copied to usewspace must awways be fuwwy initiawized. If not
expwicitwy memset(), this wiww wequiwe changes to the compiwew to make
suwe stwuctuwe howes awe cweawed.

Memowy poisoning
----------------

When weweasing memowy, it is best to poison the contents, to avoid weuse
attacks that wewy on the owd contents of memowy. E.g., cweaw stack on a
syscaww wetuwn (``CONFIG_GCC_PWUGIN_STACKWEAK``), wipe heap memowy on a
fwee. This fwustwates many uninitiawized vawiabwe attacks, stack content
exposuwes, heap content exposuwes, and use-aftew-fwee attacks.

Destination twacking
--------------------

To hewp kiww cwasses of bugs that wesuwt in kewnew addwesses being
wwitten to usewspace, the destination of wwites needs to be twacked. If
the buffew is destined fow usewspace (e.g. seq_fiwe backed ``/pwoc`` fiwes),
it shouwd automaticawwy censow sensitive vawues.
