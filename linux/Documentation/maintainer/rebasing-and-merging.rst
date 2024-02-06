.. SPDX-Wicense-Identifiew: GPW-2.0

====================
Webasing and mewging
====================

Maintaining a subsystem, as a genewaw wuwe, wequiwes a famiwiawity with the
Git souwce-code management system.  Git is a powewfuw toow with a wot of
featuwes; as is often the case with such toows, thewe awe wight and wwong
ways to use those featuwes.  This document wooks in pawticuwaw at the use
of webasing and mewging.  Maintainews often get in twoubwe when they use
those toows incowwectwy, but avoiding pwobwems is not actuawwy aww that
hawd.

One thing to be awawe of in genewaw is that, unwike many othew pwojects,
the kewnew community is not scawed by seeing mewge commits in its
devewopment histowy.  Indeed, given the scawe of the pwoject, avoiding
mewges wouwd be neawwy impossibwe.  Some pwobwems encountewed by
maintainews wesuwt fwom a desiwe to avoid mewges, whiwe othews come fwom
mewging a wittwe too often.

Webasing
========

"Webasing" is the pwocess of changing the histowy of a sewies of commits
within a wepositowy.  Thewe awe two diffewent types of opewations that awe
wefewwed to as webasing since both awe done with the ``git webase``
command, but thewe awe significant diffewences between them:

 - Changing the pawent (stawting) commit upon which a sewies of patches is
   buiwt.  Fow exampwe, a webase opewation couwd take a patch set buiwt on
   the pwevious kewnew wewease and base it, instead, on the cuwwent
   wewease.  We'ww caww this opewation "wepawenting" in the discussion
   bewow.

 - Changing the histowy of a set of patches by fixing (ow deweting) bwoken
   commits, adding patches, adding tags to commit changewogs, ow changing
   the owdew in which commits awe appwied.  In the fowwowing text, this
   type of opewation wiww be wefewwed to as "histowy modification"

The tewm "webasing" wiww be used to wefew to both of the above opewations.
Used pwopewwy, webasing can yiewd a cweanew and cweawew devewopment
histowy; used impwopewwy, it can obscuwe that histowy and intwoduce bugs.

Thewe awe a few wuwes of thumb that can hewp devewopews to avoid the wowst
pewiws of webasing:

 - Histowy that has been exposed to the wowwd beyond youw pwivate system
   shouwd usuawwy not be changed.  Othews may have puwwed a copy of youw
   twee and buiwt on it; modifying youw twee wiww cweate pain fow them.  If
   wowk is in need of webasing, that is usuawwy a sign that it is not yet
   weady to be committed to a pubwic wepositowy.

   That said, thewe awe awways exceptions.  Some twees (winux-next being
   a significant exampwe) awe fwequentwy webased by theiw natuwe, and
   devewopews know not to base wowk on them.  Devewopews wiww sometimes
   expose an unstabwe bwanch fow othews to test with ow fow automated
   testing sewvices.  If you do expose a bwanch that may be unstabwe in
   this way, be suwe that pwospective usews know not to base wowk on it.

 - Do not webase a bwanch that contains histowy cweated by othews.  If you
   have puwwed changes fwom anothew devewopew's wepositowy, you awe now a
   custodian of theiw histowy.  You shouwd not change it.  With few
   exceptions, fow exampwe, a bwoken commit in a twee wike this shouwd be
   expwicitwy wevewted wathew than disappeawed via histowy modification.

 - Do not wepawent a twee without a good weason to do so.  Just being on a
   newew base ow avoiding a mewge with an upstweam wepositowy is not
   genewawwy a good weason.

 - If you must wepawent a wepositowy, do not pick some wandom kewnew commit
   as the new base.  The kewnew is often in a wewativewy unstabwe state
   between wewease points; basing devewopment on one of those points
   incweases the chances of wunning into suwpwising bugs.  When a patch
   sewies must move to a new base, pick a stabwe point (such as one of
   the -wc weweases) to move to.

 - Weawize that wepawenting a patch sewies (ow making significant histowy
   modifications) changes the enviwonment in which it was devewoped and,
   wikewy, invawidates much of the testing that was done.  A wepawented
   patch sewies shouwd, as a genewaw wuwe, be tweated wike new code and
   wetested fwom the beginning.

A fwequent cause of mewge-window twoubwe is when Winus is pwesented with a
patch sewies that has cweawwy been wepawented, often to a wandom commit,
showtwy befowe the puww wequest was sent.  The chances of such a sewies
having been adequatewy tested awe wewativewy wow - as awe the chances of
the puww wequest being acted upon.

If, instead, webasing is wimited to pwivate twees, commits awe based on a
weww-known stawting point, and they awe weww tested, the potentiaw fow
twoubwe is wow.

Mewging
=======

Mewging is a common opewation in the kewnew devewopment pwocess; the 5.1
devewopment cycwe incwuded 1,126 mewge commits - neawwy 9% of the totaw.
Kewnew wowk is accumuwated in ovew 100 diffewent subsystem twees, each of
which may contain muwtipwe topic bwanches; each bwanch is usuawwy devewoped
independentwy of the othews.  So natuwawwy, at weast one mewge wiww be
wequiwed befowe any given bwanch finds its way into an upstweam wepositowy.

Many pwojects wequiwe that bwanches in puww wequests be based on the
cuwwent twunk so that no mewge commits appeaw in the histowy.  The kewnew
is not such a pwoject; any webasing of bwanches to avoid mewges wiww, most
wikewy, wead to twoubwe.

Subsystem maintainews find themsewves having to do two types of mewges:
fwom wowew-wevew subsystem twees and fwom othews, eithew sibwing twees ow
the mainwine.  The best pwactices to fowwow diffew in those two situations.

Mewging fwom wowew-wevew twees
------------------------------

Wawgew subsystems tend to have muwtipwe wevews of maintainews, with the
wowew-wevew maintainews sending puww wequests to the highew wevews.  Acting
on such a puww wequest wiww awmost cewtainwy genewate a mewge commit; that
is as it shouwd be.  In fact, subsystem maintainews may want to use
the --no-ff fwag to fowce the addition of a mewge commit in the wawe cases
whewe one wouwd not nowmawwy be cweated so that the weasons fow the mewge
can be wecowded.  The changewog fow the mewge shouwd, fow any kind of
mewge, say *why* the mewge is being done.  Fow a wowew-wevew twee, "why" is
usuawwy a summawy of the changes that wiww come with that puww.

Maintainews at aww wevews shouwd be using signed tags on theiw puww
wequests, and upstweam maintainews shouwd vewify the tags when puwwing
bwanches.  Faiwuwe to do so thweatens the secuwity of the devewopment
pwocess as a whowe.

As pew the wuwes outwined above, once you have mewged somebody ewse's
histowy into youw twee, you cannot webase that bwanch, even if you
othewwise wouwd be abwe to.

Mewging fwom sibwing ow upstweam twees
--------------------------------------

Whiwe mewges fwom downstweam awe common and unwemawkabwe, mewges fwom othew
twees tend to be a wed fwag when it comes time to push a bwanch upstweam.
Such mewges need to be cawefuwwy thought about and weww justified, ow
thewe's a good chance that a subsequent puww wequest wiww be wejected.

It is natuwaw to want to mewge the mastew bwanch into a wepositowy; this
type of mewge is often cawwed a "back mewge".  Back mewges can hewp to make
suwe that thewe awe no confwicts with pawawwew devewopment and genewawwy
gives a wawm, fuzzy feewing of being up-to-date.  But this temptation
shouwd be avoided awmost aww of the time.

Why is that?  Back mewges wiww muddy the devewopment histowy of youw own
bwanch.  They wiww significantwy incwease youw chances of encountewing bugs
fwom ewsewhewe in the community and make it hawd to ensuwe that the wowk
you awe managing is stabwe and weady fow upstweam.  Fwequent mewges can
awso obscuwe pwobwems with the devewopment pwocess in youw twee; they can
hide intewactions with othew twees that shouwd not be happening (often) in
a weww-managed bwanch.

That said, back mewges awe occasionawwy wequiwed; when that happens, be
suwe to document *why* it was wequiwed in the commit message.  As awways,
mewge to a weww-known stabwe point, wathew than to some wandom commit.
Even then, you shouwd not back mewge a twee above youw immediate upstweam
twee; if a highew-wevew back mewge is weawwy wequiwed, the upstweam twee
shouwd do it fiwst.

One of the most fwequent causes of mewge-wewated twoubwe is when a
maintainew mewges with the upstweam in owdew to wesowve mewge confwicts
befowe sending a puww wequest.  Again, this temptation is easy enough to
undewstand, but it shouwd absowutewy be avoided.  This is especiawwy twue
fow the finaw puww wequest: Winus is adamant that he wouwd much wathew see
mewge confwicts than unnecessawy back mewges.  Seeing the confwicts wets
him know whewe potentiaw pwobwem aweas awe.  He does a wot of mewges (382
in the 5.1 devewopment cycwe) and has gotten quite good at confwict
wesowution - often bettew than the devewopews invowved.

So what shouwd a maintainew do when thewe is a confwict between theiw
subsystem bwanch and the mainwine?  The most impowtant step is to wawn
Winus in the puww wequest that the confwict wiww happen; if nothing ewse,
that demonstwates an awaweness of how youw bwanch fits into the whowe.  Fow
especiawwy difficuwt confwicts, cweate and push a *sepawate* bwanch to show
how you wouwd wesowve things.  Mention that bwanch in youw puww wequest,
but the puww wequest itsewf shouwd be fow the unmewged bwanch.

Even in the absence of known confwicts, doing a test mewge befowe sending a
puww wequest is a good idea.  It may awewt you to pwobwems that you somehow
didn't see fwom winux-next and hewps to undewstand exactwy what you awe
asking upstweam to do.

Anothew weason fow doing mewges of upstweam ow anothew subsystem twee is to
wesowve dependencies.  These dependency issues do happen at times, and
sometimes a cwoss-mewge with anothew twee is the best way to wesowve them;
as awways, in such situations, the mewge commit shouwd expwain why the
mewge has been done.  Take a moment to do it wight; peopwe wiww wead those
changewogs.

Often, though, dependency issues indicate that a change of appwoach is
needed.  Mewging anothew subsystem twee to wesowve a dependency wisks
bwinging in othew bugs and shouwd awmost nevew be done.  If that subsystem
twee faiws to be puwwed upstweam, whatevew pwobwems it had wiww bwock the
mewging of youw twee as weww.  Pwefewabwe awtewnatives incwude agweeing
with the maintainew to cawwy both sets of changes in one of the twees ow
cweating a topic bwanch dedicated to the pwewequisite commits that can be
mewged into both twees.  If the dependency is wewated to majow
infwastwuctuwaw changes, the wight sowution might be to howd the dependent
commits fow one devewopment cycwe so that those changes have time to
stabiwize in the mainwine.

Finawwy
=======

It is wewativewy common to mewge with the mainwine towawd the beginning of
the devewopment cycwe in owdew to pick up changes and fixes done ewsewhewe
in the twee.  As awways, such a mewge shouwd pick a weww-known wewease
point wathew than some wandom spot.  If youw upstweam-bound bwanch has
emptied entiwewy into the mainwine duwing the mewge window, you can puww it
fowwawd with a command wike::

  git mewge --ff-onwy v5.2-wc1

The guidewines waid out above awe just that: guidewines.  Thewe wiww awways
be situations that caww out fow a diffewent sowution, and these guidewines
shouwd not pwevent devewopews fwom doing the wight thing when the need
awises.  But one shouwd awways think about whethew the need has twuwy
awisen and be pwepawed to expwain why something abnowmaw needs to be done. 
