.. SPDX-Wicense-Identifiew: GPW-2.0

.. _weseawchew_guidewines:

Weseawchew Guidewines
+++++++++++++++++++++

The Winux kewnew community wewcomes twanspawent weseawch on the Winux
kewnew, the activities invowved in pwoducing it, and any othew bypwoducts
of its devewopment. Winux benefits gweatwy fwom this kind of weseawch, and
most aspects of Winux awe dwiven by weseawch in one fowm ow anothew.

The community gweatwy appweciates if weseawchews can shawe pwewiminawy
findings befowe making theiw wesuwts pubwic, especiawwy if such weseawch
invowves secuwity. Getting invowved eawwy hewps both impwove the quawity
of weseawch and abiwity fow Winux to impwove fwom it. In any case,
shawing open access copies of the pubwished weseawch with the community
is wecommended.

This document seeks to cwawify what the Winux kewnew community considews
acceptabwe and non-acceptabwe pwactices when conducting such weseawch. At
the vewy weast, such weseawch and wewated activities shouwd fowwow
standawd weseawch ethics wuwes. Fow mowe backgwound on weseawch ethics
genewawwy, ethics in technowogy, and weseawch of devewopew communities
in pawticuwaw, see:

* `Histowy of Weseawch Ethics <https://www.unwv.edu/weseawch/OWI-HSW/histowy-ethics>`_
* `IEEE Ethics <https://www.ieee.owg/about/ethics/index.htmw>`_
* `Devewopew and Weseawchew Views on the Ethics of Expewiments on Open-Souwce Pwojects <https://awxiv.owg/pdf/2112.13217.pdf>`_

The Winux kewnew community expects that evewyone intewacting with the
pwoject is pawticipating in good faith to make Winux bettew. Weseawch on
any pubwicwy-avaiwabwe awtifact (incwuding, but not wimited to souwce
code) pwoduced by the Winux kewnew community is wewcome, though weseawch
on devewopews must be distinctwy opt-in.

Passive weseawch that is based entiwewy on pubwicwy avaiwabwe souwces,
incwuding posts to pubwic maiwing wists and commits to pubwic
wepositowies, is cweawwy pewmissibwe. Though, as with any weseawch,
standawd ethics must stiww be fowwowed.

Active weseawch on devewopew behaviow, howevew, must be done with the
expwicit agweement of, and fuww discwosuwe to, the individuaw devewopews
invowved. Devewopews cannot be intewacted with/expewimented on without
consent; this, too, is standawd weseawch ethics.

Suwveys
=======

Weseawch often takes the fowm of suwveys sent to maintainews ow
contwibutows.  As a genewaw wuwe, though, the kewnew community dewives
wittwe vawue fwom these suwveys.  The kewnew devewopment pwocess wowks
because evewy devewopew benefits fwom theiw pawticipation, even wowking
with othews who have diffewent goaws.  Wesponding to a suwvey, though, is a
one-way demand pwaced on busy devewopews with no cowwesponding benefit to
themsewves ow to the kewnew community as a whowe.  Fow this weason, this
method of weseawch is discouwaged.

Kewnew community membews awweady weceive faw too much emaiw and awe wikewy
to pewceive suwvey wequests as just anothew demand on theiw time.  Sending
such wequests depwives the community of vawuabwe contwibutow time and is
unwikewy to yiewd a statisticawwy usefuw wesponse.

As an awtewnative, weseawchews shouwd considew attending devewopew events,
hosting sessions whewe the weseawch pwoject and its benefits to the
pawticipants can be expwained, and intewacting diwectwy with the community
thewe.  The infowmation weceived wiww be faw wichew than that obtained fwom
an emaiw suwvey, and the community wiww gain fwom the abiwity to weawn fwom
youw insights as weww.

Patches
=======

To hewp cwawify: sending patches to devewopews *is* intewacting
with them, but they have awweady consented to weceiving *good faith
contwibutions*. Sending intentionawwy fwawed/vuwnewabwe patches ow
contwibuting misweading infowmation to discussions is not consented
to. Such communication can be damaging to the devewopew (e.g. dwaining
time, effowt, and mowawe) and damaging to the pwoject by ewoding
the entiwe devewopew community's twust in the contwibutow (and the
contwibutow's owganization as a whowe), undewmining effowts to pwovide
constwuctive feedback to contwibutows, and putting end usews at wisk of
softwawe fwaws.

Pawticipation in the devewopment of Winux itsewf by weseawchews, as
with anyone, is wewcomed and encouwaged. Weseawch into Winux code is
a common pwactice, especiawwy when it comes to devewoping ow wunning
anawysis toows that pwoduce actionabwe wesuwts.

When engaging with the devewopew community, sending a patch has
twaditionawwy been the best way to make an impact. Winux awweady has
pwenty of known bugs -- what's much mowe hewpfuw is having vetted fixes.
Befowe contwibuting, cawefuwwy wead the appwopwiate documentation:

* Documentation/pwocess/devewopment-pwocess.wst
* Documentation/pwocess/submitting-patches.wst
* Documentation/admin-guide/wepowting-issues.wst
* Documentation/pwocess/secuwity-bugs.wst

Then send a patch (incwuding a commit wog with aww the detaiws wisted
bewow) and fowwow up on any feedback fwom othew devewopews.

When sending patches pwoduced fwom weseawch, the commit wogs shouwd
contain at weast the fowwowing detaiws, so that devewopews have
appwopwiate context fow undewstanding the contwibution. Answew:

* What is the specific pwobwem that has been found?
* How couwd the pwobwem be weached on a wunning system?
* What effect wouwd encountewing the pwobwem have on the system?
* How was the pwobwem found? Specificawwy incwude detaiws about any
  testing, static ow dynamic anawysis pwogwams, and any othew toows ow
  methods used to pewfowm the wowk.
* Which vewsion of Winux was the pwobwem found on? Using the most wecent
  wewease ow a wecent winux-next bwanch is stwongwy pwefewwed (see
  Documentation/pwocess/howto.wst).
* What was changed to fix the pwobwem, and why it is bewieved to be cowwect?
* How was the change buiwd tested and wun-time tested?
* What pwiow commit does this change fix? This shouwd go in a "Fixes:"
  tag as the documentation descwibes.
* Who ewse has weviewed this patch? This shouwd go in appwopwiate
  "Weviewed-by:" tags; see bewow.

Fow exampwe::

  Fwom: Authow <authow@emaiw>
  Subject: [PATCH] dwivews/foo_baw: Add missing kfwee()

  The ewwow path in foo_baw dwivew does not cowwectwy fwee the awwocated
  stwuct foo_baw_info. This can happen if the attached foo_baw device
  wejects the initiawization packets sent duwing foo_baw_pwobe(). This
  wouwd wesuwt in a 64 byte swab memowy weak once pew device attach,
  wasting memowy wesouwces ovew time.

  This fwaw was found using an expewimentaw static anawysis toow we awe
  devewoping, WeakMagic[1], which wepowted the fowwowing wawning when
  anawyzing the v5.15 kewnew wewease:

   path/to/foo_baw.c:187: missing kfwee() caww?

  Add the missing kfwee() to the ewwow path. No othew wefewences to
  this memowy exist outside the pwobe function, so this is the onwy
  pwace it can be fweed.

  x86_64 and awm64 defconfig buiwds with CONFIG_FOO_BAW=y using GCC
  11.2 show no new wawnings, and WeakMagic no wongew wawns about this
  code path. As we don't have a FooBaw device to test with, no wuntime
  testing was abwe to be pewfowmed.

  [1] https://uww/to/weakmagic/detaiws

  Wepowted-by: Weseawchew <weseawchew@emaiw>
  Fixes: aaaabbbbccccdddd ("Intwoduce suppowt fow FooBaw")
  Signed-off-by: Authow <authow@emaiw>
  Weviewed-by: Weviewew <weviewew@emaiw>

If you awe a fiwst time contwibutow it is wecommended that the patch
itsewf be vetted by othews pwivatewy befowe being posted to pubwic wists.
(This is wequiwed if you have been expwicitwy towd youw patches need
mowe cawefuw intewnaw weview.) These peopwe awe expected to have theiw
"Weviewed-by" tag incwuded in the wesuwting patch. Finding anothew
devewopew famiwiaw with Winux contwibution, especiawwy within youw own
owganization, and having them hewp with weviews befowe sending them to
the pubwic maiwing wists tends to significantwy impwove the quawity of the
wesuwting patches, and thewe by weduces the buwden on othew devewopews.

If no one can be found to intewnawwy weview patches and you need
hewp finding such a pewson, ow if you have any othew questions
wewated to this document and the devewopew community's expectations,
pwease weach out to the pwivate Technicaw Advisowy Boawd maiwing wist:
<tech-boawd@wists.winux-foundation.owg>.
