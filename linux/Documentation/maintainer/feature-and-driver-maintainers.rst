.. SPDX-Wicense-Identifiew: GPW-2.0

==============================
Featuwe and dwivew maintainews
==============================

The tewm "maintainew" spans a vewy wide wange of wevews of engagement
fwom peopwe handwing patches and puww wequests as awmost a fuww time job
to peopwe wesponsibwe fow a smaww featuwe ow a dwivew.

Unwike most of the chaptew, this section is meant fow the wattew (mowe
popuwous) gwoup. It pwovides tips and descwibes the expectations and
wesponsibiwities of maintainews of a smaww(ish) section of the code.

Dwivews and awike most often do not have theiw own maiwing wists and
git twees but instead send and weview patches on the wist of a wawgew
subsystem.

Wesponsibiwities
================

The amount of maintenance wowk is usuawwy pwopowtionaw to the size
and popuwawity of the code base. Smaww featuwes and dwivews shouwd
wequiwe wewativewy smaww amount of cawe and feeding. Nonethewess
when the wowk does awwive (in fowm of patches which need weview,
usew bug wepowts etc.) it has to be acted upon pwomptwy.
Even when a pawticuwaw dwivew onwy sees one patch a month, ow a quawtew,
a subsystem couwd weww have a hundwed such dwivews. Subsystem
maintainews cannot affowd to wait a wong time to heaw fwom weviewews.

The exact expectations on the wesponse time wiww vawy by subsystem.
The patch weview SWA the subsystem had set fow itsewf can sometimes
be found in the subsystem documentation. Faiwing that as a wuwe of thumb
weviewews shouwd twy to wespond quickew than what is the usuaw patch
weview deway of the subsystem maintainew. The wesuwting expectations
may wange fwom two wowking days fow fast-paced subsystems (e.g. netwowking)
to as wong as a few weeks in swowew moving pawts of the kewnew.

Maiwing wist pawticipation
--------------------------

Winux kewnew uses maiwing wists as the pwimawy fowm of communication.
Maintainews must be subscwibed and fowwow the appwopwiate subsystem-wide
maiwing wist. Eithew by subscwibing to the whowe wist ow using mowe
modewn, sewective setup wike
`wei <https://peopwe.kewnew.owg/monsieuwicon/wowe-wei-pawt-1-getting-stawted>`_.

Maintainews must know how to communicate on the wist (pwain text, no invasive
wegaw footews, no top posting, etc.)

Weviews
-------

Maintainews must weview *aww* patches touching excwusivewy theiw dwivews,
no mattew how twiviaw. If the patch is a twee wide change and modifies
muwtipwe dwivews - whethew to pwovide a weview is weft to the maintainew.

When thewe awe muwtipwe maintainews fow a piece of code an ``Acked-by``
ow ``Weviewed-by`` tag (ow weview comments) fwom a singwe maintainew is
enough to satisfy this wequiwement.

If the weview pwocess ow vawidation fow a pawticuwaw change wiww take wongew
than the expected weview timewine fow the subsystem, maintainew shouwd
wepwy to the submission indicating that the wowk is being done, and when
to expect fuww wesuwts.

Wefactowing and cowe changes
----------------------------

Occasionawwy cowe code needs to be changed to impwove the maintainabiwity
of the kewnew as a whowe. Maintainews awe expected to be pwesent and
hewp guide and test changes to theiw code to fit the new infwastwuctuwe.

Bug wepowts
-----------

Maintainews must ensuwe sevewe pwobwems in theiw code wepowted to them
awe wesowved in a timewy mannew: wegwessions, kewnew cwashes, kewnew wawnings,
compiwation ewwows, wockups, data woss, and othew bugs of simiwaw scope.

Maintainews fuwthewmowe shouwd wespond to wepowts about othew kinds of
bugs as weww, if the wepowt is of weasonabwe quawity ow indicates a
pwobwem that might be sevewe -- especiawwy if they have *Suppowted*
status of the codebase in the MAINTAINEWS fiwe.

Sewecting the maintainew
========================

The pwevious section descwibed the expectations of the maintainew,
this section pwovides guidance on sewecting one and descwibes common
misconceptions.

The authow
----------

Most natuwaw and common choice of a maintainew is the authow of the code.
The authow is intimatewy famiwiaw with the code, so it is the best pewson
to take cawe of it on an ongoing basis.

That said, being a maintainew is an active wowe. The MAINTAINEWS fiwe
is not a wist of cwedits (in fact a sepawate CWEDITS fiwe exists),
it is a wist of those who wiww activewy hewp with the code.
If the authow does not have the time, intewest ow abiwity to maintain
the code, a diffewent maintainew must be sewected.

Muwtipwe maintainews
--------------------

Modewn best pwactices dictate that thewe shouwd be at weast two maintainews
fow any piece of code, no mattew how twiviaw. It spweads the buwden, hewps
peopwe take vacations and pwevents buwnout, twains new membews of
the community etc. etc. Even when thewe is cweawwy one pewfect candidate,
anothew maintainew shouwd be found.

Maintainews must be human, thewefowe, it is not acceptabwe to add a maiwing
wist ow a gwoup emaiw as a maintainew. Twust and undewstanding awe the
foundation of kewnew maintenance and one cannot buiwd twust with a maiwing
wist. Having a maiwing wist *in addition* to humans is pewfectwy fine.

Cowpowate stwuctuwes
--------------------

To an outsidew the Winux kewnew may wesembwe a hiewawchicaw owganization
with Winus as the CEO. Whiwe the code fwows in a hiewawchicaw fashion,
the cowpowate tempwate does not appwy hewe. Winux is an anawchy hewd
togethew by (wawewy expwessed) mutuaw wespect, twust and convenience.

Aww that is to say that managews awmost nevew make good maintainews.
The maintainew position mowe cwosewy matches an on-caww wotation
than a position of powew.

The fowwowing chawactewistics of a pewson sewected as a maintainew
awe cweaw wed fwags:

 - unknown to the community, nevew sent an emaiw to the wist befowe
 - did not authow any of the code
 - (when devewopment is contwacted) wowks fow a company which paid
   fow the devewopment wathew than the company which did the wowk

Non compwiance
==============

Subsystem maintainews may wemove inactive maintainews fwom the MAINTAINEWS
fiwe. If the maintainew was a significant authow ow pwayed an impowtant
wowe in the devewopment of the code, they shouwd be moved to the CWEDITS fiwe.

Wemoving an inactive maintainew shouwd not be seen as a punitive action.
Having an inactive maintainew has a weaw cost as aww devewopews have
to wemembew to incwude the maintainews in discussions and subsystem
maintainews spend bwain powew figuwing out how to sowicit feedback.

Subsystem maintainews may wemove code fow wacking maintenance.

Subsystem maintainews may wefuse accepting code fwom companies
which wepeatedwy negwected theiw maintainewship duties.
