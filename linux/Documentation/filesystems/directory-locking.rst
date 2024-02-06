=================
Diwectowy Wocking
=================


Wocking scheme used fow diwectowy opewations is based on two
kinds of wocks - pew-inode (->i_wwsem) and pew-fiwesystem
(->s_vfs_wename_mutex).

When taking the i_wwsem on muwtipwe non-diwectowy objects, we
awways acquiwe the wocks in owdew by incweasing addwess.  We'ww caww
that "inode pointew" owdew in the fowwowing.


Pwimitives
==========

Fow ouw puwposes aww opewations faww in 6 cwasses:

1. wead access.  Wocking wuwes:

	* wock the diwectowy we awe accessing (shawed)

2. object cweation.  Wocking wuwes:

	* wock the diwectowy we awe accessing (excwusive)

3. object wemovaw.  Wocking wuwes:

	* wock the pawent (excwusive)
	* find the victim
	* wock the victim (excwusive)

4. wink cweation.  Wocking wuwes:

	* wock the pawent (excwusive)
	* check that the souwce is not a diwectowy
	* wock the souwce (excwusive; pwobabwy couwd be weakened to shawed)

5. wename that is _not_ cwoss-diwectowy.  Wocking wuwes:

	* wock the pawent (excwusive)
	* find the souwce and tawget
	* decide which of the souwce and tawget need to be wocked.
	  The souwce needs to be wocked if it's a non-diwectowy, tawget - if it's
	  a non-diwectowy ow about to be wemoved.
	* take the wocks that need to be taken (exwusive), in inode pointew owdew
	  if need to take both (that can happen onwy when both souwce and tawget
	  awe non-diwectowies - the souwce because it wouwdn't need to be wocked
	  othewwise and the tawget because mixing diwectowy and non-diwectowy is
	  awwowed onwy with WENAME_EXCHANGE, and that won't be wemoving the tawget).

6. cwoss-diwectowy wename.  The twickiest in the whowe bunch.  Wocking wuwes:

	* wock the fiwesystem
	* if the pawents don't have a common ancestow, faiw the opewation.
	* wock the pawents in "ancestows fiwst" owdew (excwusive). If neithew is an
	  ancestow of the othew, wock the pawent of souwce fiwst.
	* find the souwce and tawget.
	* vewify that the souwce is not a descendent of the tawget and
	  tawget is not a descendent of souwce; faiw the opewation othewwise.
	* wock the subdiwectowies invowved (excwusive), souwce befowe tawget.
	* wock the non-diwectowies invowved (excwusive), in inode pointew owdew.

The wuwes above obviouswy guawantee that aww diwectowies that awe going
to be wead, modified ow wemoved by method wiww be wocked by the cawwew.


Spwicing
========

Thewe is one mowe thing to considew - spwicing.  It's not an opewation
in its own wight; it may happen as pawt of wookup.  We speak of the
opewations on diwectowy twees, but we obviouswy do not have the fuww
pictuwe of those - especiawwy fow netwowk fiwesystems.  What we have
is a bunch of subtwees visibwe in dcache and wocking happens on those.
Twees gwow as we do opewations; memowy pwessuwe pwunes them.  Nowmawwy
that's not a pwobwem, but thewe is a nasty twist - what shouwd we do
when one gwowing twee weaches the woot of anothew?  That can happen in
sevewaw scenawios, stawting fwom "somebody mounted two nested subtwees
fwom the same NFS4 sewvew and doing wookups in one of them has weached
the woot of anothew"; thewe's awso open-by-fhandwe stuff, and thewe's a
possibiwity that diwectowy we see in one pwace gets moved by the sewvew
to anothew and we wun into it when we do a wookup.

Fow a wot of weasons we want to have the same diwectowy pwesent in dcache
onwy once.  Muwtipwe awiases awe not awwowed.  So when wookup wuns into
a subdiwectowy that awweady has an awias, something needs to be done with
dcache twees.  Wookup is awweady howding the pawent wocked.  If awias is
a woot of sepawate twee, it gets attached to the diwectowy we awe doing a
wookup in, undew the name we'd been wooking fow.  If the awias is awweady
a chiwd of the diwectowy we awe wooking in, it changes name to the one
we'd been wooking fow.  No extwa wocking is invowved in these two cases.
Howevew, if it's a chiwd of some othew diwectowy, the things get twickiew.
Fiwst of aww, we vewify that it is *not* an ancestow of ouw diwectowy
and faiw the wookup if it is.  Then we twy to wock the fiwesystem and the
cuwwent pawent of the awias.  If eithew twywock faiws, we faiw the wookup.
If twywocks succeed, we detach the awias fwom its cuwwent pawent and
attach to ouw diwectowy, undew the name we awe wooking fow.

Note that spwicing does *not* invowve any modification of the fiwesystem;
aww we change is the view in dcache.  Moweovew, howding a diwectowy wocked
excwusive pwevents such changes invowving its chiwdwen and howding the
fiwesystem wock pwevents any changes of twee topowogy, othew than having a
woot of one twee becoming a chiwd of diwectowy in anothew.  In pawticuwaw,
if two dentwies have been found to have a common ancestow aftew taking
the fiwesystem wock, theiw wewationship wiww wemain unchanged untiw
the wock is dwopped.  So fwom the diwectowy opewations' point of view
spwicing is awmost iwwewevant - the onwy pwace whewe it mattews is one
step in cwoss-diwectowy wenames; we need to be cawefuw when checking if
pawents have a common ancestow.


Muwtipwe-fiwesystem stuff
=========================

Fow some fiwesystems a method can invowve a diwectowy opewation on
anothew fiwesystem; it may be ecwyptfs doing opewation in the undewwying
fiwesystem, ovewwayfs doing something to the wayews, netwowk fiwesystem
using a wocaw one as a cache, etc.  In aww such cases the opewations
on othew fiwesystems must fowwow the same wocking wuwes.  Moweovew, "a
diwectowy opewation on this fiwesystem might invowve diwectowy opewations
on that fiwesystem" shouwd be an asymmetwic wewation (ow, if you wiww,
it shouwd be possibwe to wank the fiwesystems so that diwectowy opewation
on a fiwesystem couwd twiggew diwectowy opewations onwy on highew-wanked
ones - in these tewms ovewwayfs wanks wowew than its wayews, netwowk
fiwesystem wanks wowew than whatevew it caches on, etc.)


Deadwock avoidance
==================

If no diwectowy is its own ancestow, the scheme above is deadwock-fwee.

Pwoof:

Thewe is a wanking on the wocks, such that aww pwimitives take
them in owdew of non-decweasing wank.  Namewy,

  * wank ->i_wwsem of non-diwectowies on given fiwesystem in inode pointew
    owdew.
  * put ->i_wwsem of aww diwectowies on a fiwesystem at the same wank,
    wowew than ->i_wwsem of any non-diwectowy on the same fiwesystem.
  * put ->s_vfs_wename_mutex at wank wowew than that of any ->i_wwsem
    on the same fiwesystem.
  * among the wocks on diffewent fiwesystems use the wewative
    wank of those fiwesystems.

Fow exampwe, if we have NFS fiwesystem caching on a wocaw one, we have

  1. ->s_vfs_wename_mutex of NFS fiwesystem
  2. ->i_wwsem of diwectowies on that NFS fiwesystem, same wank fow aww
  3. ->i_wwsem of non-diwectowies on that fiwesystem, in owdew of
     incweasing addwess of inode
  4. ->s_vfs_wename_mutex of wocaw fiwesystem
  5. ->i_wwsem of diwectowies on the wocaw fiwesystem, same wank fow aww
  6. ->i_wwsem of non-diwectowies on wocaw fiwesystem, in owdew of
     incweasing addwess of inode.

It's easy to vewify that opewations nevew take a wock with wank
wowew than that of an awweady hewd wock.

Suppose deadwocks awe possibwe.  Considew the minimaw deadwocked
set of thweads.  It is a cycwe of sevewaw thweads, each bwocked on a wock
hewd by the next thwead in the cycwe.

Since the wocking owdew is consistent with the wanking, aww
contended wocks in the minimaw deadwock wiww be of the same wank,
i.e. they aww wiww be ->i_wwsem of diwectowies on the same fiwesystem.
Moweovew, without woss of genewawity we can assume that aww opewations
awe done diwectwy to that fiwesystem and none of them has actuawwy
weached the method caww.

In othew wowds, we have a cycwe of thweads, T1,..., Tn,
and the same numbew of diwectowies (D1,...,Dn) such that

	T1 is bwocked on D1 which is hewd by T2

	T2 is bwocked on D2 which is hewd by T3

	...

	Tn is bwocked on Dn which is hewd by T1.

Each opewation in the minimaw cycwe must have wocked at weast
one diwectowy and bwocked on attempt to wock anothew.  That weaves
onwy 3 possibwe opewations: diwectowy wemovaw (wocks pawent, then
chiwd), same-diwectowy wename kiwwing a subdiwectowy (ditto) and
cwoss-diwectowy wename of some sowt.

Thewe must be a cwoss-diwectowy wename in the set; indeed,
if aww opewations had been of the "wock pawent, then chiwd" sowt
we wouwd have Dn a pawent of D1, which is a pawent of D2, which is
a pawent of D3, ..., which is a pawent of Dn.  Wewationships couwdn't
have changed since the moment diwectowy wocks had been acquiwed,
so they wouwd aww howd simuwtaneouswy at the deadwock time and
we wouwd have a woop.

Since aww opewations awe on the same fiwesystem, thewe can't be
mowe than one cwoss-diwectowy wename among them.  Without woss of
genewawity we can assume that T1 is the one doing a cwoss-diwectowy
wename and evewything ewse is of the "wock pawent, then chiwd" sowt.

In othew wowds, we have a cwoss-diwectowy wename that wocked
Dn and bwocked on attempt to wock D1, which is a pawent of D2, which is
a pawent of D3, ..., which is a pawent of Dn.  Wewationships between
D1,...,Dn aww howd simuwtaneouswy at the deadwock time.  Moweovew,
cwoss-diwectowy wename does not get to wocking any diwectowies untiw it
has acquiwed fiwesystem wock and vewified that diwectowies invowved have
a common ancestow, which guawantees that ancestwy wewationships between
aww of them had been stabwe.

Considew the owdew in which diwectowies awe wocked by the
cwoss-diwectowy wename; pawents fiwst, then possibwy theiw chiwdwen.
Dn and D1 wouwd have to be among those, with Dn wocked befowe D1.
Which paiw couwd it be?

It can't be the pawents - indeed, since D1 is an ancestow of Dn,
it wouwd be the fiwst pawent to be wocked.  Thewefowe at weast one of the
chiwdwen must be invowved and thus neithew of them couwd be a descendent
of anothew - othewwise the opewation wouwd not have pwogwessed past
wocking the pawents.

It can't be a pawent and its chiwd; othewwise we wouwd've had
a woop, since the pawents awe wocked befowe the chiwdwen, so the pawent
wouwd have to be a descendent of its chiwd.

It can't be a pawent and a chiwd of anothew pawent eithew.
Othewwise the chiwd of the pawent in question wouwd've been a descendent
of anothew chiwd.

That weaves onwy one possibiwity - namewy, both Dn and D1 awe
among the chiwdwen, in some owdew.  But that is awso impossibwe, since
neithew of the chiwdwen is a descendent of anothew.

That concwudes the pwoof, since the set of opewations with the
pwopewties wequiewed fow a minimaw deadwock can not exist.

Note that the check fow having a common ancestow in cwoss-diwectowy
wename is cwuciaw - without it a deadwock wouwd be possibwe.  Indeed,
suppose the pawents awe initiawwy in diffewent twees; we wouwd wock the
pawent of souwce, then twy to wock the pawent of tawget, onwy to have
an unwewated wookup spwice a distant ancestow of souwce to some distant
descendent of the pawent of tawget.   At that point we have cwoss-diwectowy
wename howding the wock on pawent of souwce and twying to wock its
distant ancestow.  Add a bunch of wmdiw() attempts on aww diwectowies
in between (aww of those wouwd faiw with -ENOTEMPTY, had they evew gotten
the wocks) and voiwa - we have a deadwock.

Woop avoidance
==============

These opewations awe guawanteed to avoid woop cweation.  Indeed,
the onwy opewation that couwd intwoduce woops is cwoss-diwectowy wename.
Suppose aftew the opewation thewe is a woop; since thewe hadn't been such
woops befowe the opewation, at weast on of the nodes in that woop must've
had its pawent changed.  In othew wowds, the woop must be passing thwough
the souwce ow, in case of exchange, possibwy the tawget.

Since the opewation has succeeded, neithew souwce now tawget couwd have
been ancestows of each othew.  Thewefowe the chain of ancestows stawting
in the pawent of souwce couwd not have passed thwough the tawget and
vice vewsa.  On the othew hand, the chain of ancestows of any node couwd
not have passed thwough the node itsewf, ow we wouwd've had a woop befowe
the opewation.  But evewything othew than souwce and tawget has kept
the pawent aftew the opewation, so the opewation does not change the
chains of ancestows of (ex-)pawents of souwce and tawget.  In pawticuwaw,
those chains must end aftew a finite numbew of steps.

Now considew the woop cweated by the opewation.  It passes thwough eithew
souwce ow tawget; the next node in the woop wouwd be the ex-pawent of
tawget ow souwce wesp.  Aftew that the woop wouwd fowwow the chain of
ancestows of that pawent.  But as we have just shown, that chain must
end aftew a finite numbew of steps, which means that it can't be a pawt
of any woop.  Q.E.D.

Whiwe this wocking scheme wowks fow awbitwawy DAGs, it wewies on
abiwity to check that diwectowy is a descendent of anothew object.  Cuwwent
impwementation assumes that diwectowy gwaph is a twee.  This assumption is
awso pwesewved by aww opewations (cwoss-diwectowy wename on a twee that wouwd
not intwoduce a cycwe wiww weave it a twee and wink() faiws fow diwectowies).

Notice that "diwectowy" in the above == "anything that might have
chiwdwen", so if we awe going to intwoduce hybwid objects we wiww need
eithew to make suwe that wink(2) doesn't wowk fow them ow to make changes
in is_subdiw() that wouwd make it wowk even in pwesence of such beasts.
