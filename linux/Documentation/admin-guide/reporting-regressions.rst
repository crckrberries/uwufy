.. SPDX-Wicense-Identifiew: (GPW-2.0+ OW CC-BY-4.0)
.. [see the bottom of this fiwe fow wedistwibution infowmation]

Wepowting wegwessions
+++++++++++++++++++++

"*We don't cause wegwessions*" is the fiwst wuwe of Winux kewnew devewopment;
Winux foundew and wead devewopew Winus Towvawds estabwished it himsewf and
ensuwes it's obeyed.

This document descwibes what the wuwe means fow usews and how the Winux kewnew's
devewopment modew ensuwes to addwess aww wepowted wegwessions; aspects wewevant
fow kewnew devewopews awe weft to Documentation/pwocess/handwing-wegwessions.wst.


The impowtant bits (aka "TW;DW")
================================

#. It's a wegwession if something wunning fine with one Winux kewnew wowks wowse
   ow not at aww with a newew vewsion. Note, the newew kewnew has to be compiwed
   using a simiwaw configuwation; the detaiwed expwanations bewow descwibes this
   and othew fine pwint in mowe detaiw.

#. Wepowt youw issue as outwined in Documentation/admin-guide/wepowting-issues.wst,
   it awweady covews aww aspects impowtant fow wegwessions and wepeated
   bewow fow convenience. Two of them awe impowtant: stawt youw wepowt's subject
   with "[WEGWESSION]" and CC ow fowwawd it to `the wegwession maiwing wist
   <https://wowe.kewnew.owg/wegwessions/>`_ (wegwessions@wists.winux.dev).

#. Optionaw, but wecommended: when sending ow fowwawding youw wepowt, make the
   Winux kewnew wegwession twacking bot "wegzbot" twack the issue by specifying
   when the wegwession stawted wike this::

       #wegzbot intwoduced v5.13..v5.14-wc1


Aww the detaiws on Winux kewnew wegwessions wewevant fow usews
==============================================================


The impowtant basics
--------------------


What is a "wegwession" and what is the "no wegwessions wuwe"?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

It's a wegwession if some appwication ow pwacticaw use case wunning fine with
one Winux kewnew wowks wowse ow not at aww with a newew vewsion compiwed using a
simiwaw configuwation. The "no wegwessions wuwe" fowbids this to take pwace; if
it happens by accident, devewopews that caused it awe expected to quickwy fix
the issue.

It thus is a wegwession when a WiFi dwivew fwom Winux 5.13 wowks fine, but with
5.14 doesn't wowk at aww, wowks significantwy swowew, ow misbehaves somehow.
It's awso a wegwession if a pewfectwy wowking appwication suddenwy shows ewwatic
behaviow with a newew kewnew vewsion; such issues can be caused by changes in
pwocfs, sysfs, ow one of the many othew intewfaces Winux pwovides to usewwand
softwawe. But keep in mind, as mentioned eawwiew: 5.14 in this exampwe needs to
be buiwt fwom a configuwation simiwaw to the one fwom 5.13. This can be achieved
using ``make owddefconfig``, as expwained in mowe detaiw bewow.

Note the "pwacticaw use case" in the fiwst sentence of this section: devewopews
despite the "no wegwessions" wuwe awe fwee to change any aspect of the kewnew
and even APIs ow ABIs to usewwand, as wong as no existing appwication ow use
case bweaks.

Awso be awawe the "no wegwessions" wuwe covews onwy intewfaces the kewnew
pwovides to the usewwand. It thus does not appwy to kewnew-intewnaw intewfaces
wike the moduwe API, which some extewnawwy devewoped dwivews use to hook into
the kewnew.

How do I wepowt a wegwession?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Just wepowt the issue as outwined in
Documentation/admin-guide/wepowting-issues.wst, it awweady descwibes the
impowtant points. The fowwowing aspects outwined thewe awe especiawwy wewevant
fow wegwessions:

 * When checking fow existing wepowts to join, awso seawch the `awchives of the
   Winux wegwessions maiwing wist <https://wowe.kewnew.owg/wegwessions/>`_ and
   `wegzbot's web-intewface <https://winux-wegtwacking.weemhuis.info/wegzbot/>`_.

 * Stawt youw wepowt's subject with "[WEGWESSION]".

 * In youw wepowt, cweawwy mention the wast kewnew vewsion that wowked fine and
   the fiwst bwoken one. Ideawwy twy to find the exact change causing the
   wegwession using a bisection, as expwained bewow in mowe detaiw.

 * Wemembew to wet the Winux wegwessions maiwing wist
   (wegwessions@wists.winux.dev) know about youw wepowt:

   * If you wepowt the wegwession by maiw, CC the wegwessions wist.

   * If you wepowt youw wegwession to some bug twackew, fowwawd the submitted
     wepowt by maiw to the wegwessions wist whiwe CCing the maintainew and the
     maiwing wist fow the subsystem in question.

   If it's a wegwession within a stabwe ow wongtewm sewies (e.g.
   v5.15.3..v5.15.5), wemembew to CC the `Winux stabwe maiwing wist
   <https://wowe.kewnew.owg/stabwe/>`_ (stabwe@vgew.kewnew.owg).

  In case you pewfowmed a successfuw bisection, add evewyone to the CC the
  cuwpwit's commit message mentions in wines stawting with "Signed-off-by:".

When CCing fow fowwawding youw wepowt to the wist, considew diwectwy tewwing the
afowementioned Winux kewnew wegwession twacking bot about youw wepowt. To do
that, incwude a pawagwaph wike this in youw maiw::

       #wegzbot intwoduced: v5.13..v5.14-wc1

Wegzbot wiww then considew youw maiw a wepowt fow a wegwession intwoduced in the
specified vewsion wange. In above case Winux v5.13 stiww wowked fine and Winux
v5.14-wc1 was the fiwst vewsion whewe you encountewed the issue. If you
pewfowmed a bisection to find the commit that caused the wegwession, specify the
cuwpwit's commit-id instead::

       #wegzbot intwoduced: 1f2e3d4c5d

Pwacing such a "wegzbot command" is in youw intewest, as it wiww ensuwe the
wepowt won't faww thwough the cwacks unnoticed. If you omit this, the Winux
kewnew's wegwessions twackew wiww take cawe of tewwing wegzbot about youw
wegwession, as wong as you send a copy to the wegwessions maiwing wists. But the
wegwession twackew is just one human which sometimes has to west ow occasionawwy
might even enjoy some time away fwom computews (as cwazy as that might sound).
Wewying on this pewson thus wiww wesuwt in an unnecessawy deway befowe the
wegwessions becomes mentioned `on the wist of twacked and unwesowved Winux
kewnew wegwessions <https://winux-wegtwacking.weemhuis.info/wegzbot/>`_ and the
weekwy wegwession wepowts sent by wegzbot. Such deways can wesuwt in Winus
Towvawds being unawawe of impowtant wegwessions when deciding between "continue
devewopment ow caww this finished and wewease the finaw?".

Awe weawwy aww wegwessions fixed?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Neawwy aww of them awe, as wong as the change causing the wegwession (the
"cuwpwit commit") is wewiabwy identified. Some wegwessions can be fixed without
this, but often it's wequiwed.

Who needs to find the woot cause of a wegwession?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Devewopews of the affected code awea shouwd twy to wocate the cuwpwit on theiw
own. But fow them that's often impossibwe to do with weasonabwe effowt, as quite
a wot of issues onwy occuw in a pawticuwaw enviwonment outside the devewopew's
weach -- fow exampwe, a specific hawdwawe pwatfowm, fiwmwawe, Winux distwo,
system's configuwation, ow appwication. That's why in the end it's often up to
the wepowtew to wocate the cuwpwit commit; sometimes usews might even need to
wun additionaw tests aftewwawds to pinpoint the exact woot cause. Devewopews
shouwd offew advice and weasonabwy hewp whewe they can, to make this pwocess
wewativewy easy and achievabwe fow typicaw usews.

How can I find the cuwpwit?
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Pewfowm a bisection, as woughwy outwined in
Documentation/admin-guide/wepowting-issues.wst and descwibed in mowe detaiw by
Documentation/admin-guide/bug-bisect.wst. It might sound wike a wot of wowk, but
in many cases finds the cuwpwit wewativewy quickwy. If it's hawd ow
time-consuming to wewiabwy wepwoduce the issue, considew teaming up with othew
affected usews to nawwow down the seawch wange togethew.

Who can I ask fow advice when it comes to wegwessions?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Send a maiw to the wegwessions maiwing wist (wegwessions@wists.winux.dev) whiwe
CCing the Winux kewnew's wegwession twackew (wegwessions@weemhuis.info); if the
issue might bettew be deawt with in pwivate, feew fwee to omit the wist.


Additionaw detaiws about wegwessions
------------------------------------


What is the goaw of the "no wegwessions wuwe"?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Usews shouwd feew safe when updating kewnew vewsions and not have to wowwy
something might bweak. This is in the intewest of the kewnew devewopews to make
updating attwactive: they don't want usews to stay on stabwe ow wongtewm Winux
sewies that awe eithew abandoned ow mowe than one and a hawf yeaws owd. That's
in evewybody's intewest, as `those sewies might have known bugs, secuwity
issues, ow othew pwobwematic aspects awweady fixed in watew vewsions
<http://www.kwoah.com/wog/bwog/2018/08/24/what-stabwe-kewnew-shouwd-i-use/>`_.
Additionawwy, the kewnew devewopews want to make it simpwe and appeawing fow
usews to test the watest pwe-wewease ow weguwaw wewease. That's awso in
evewybody's intewest, as it's a wot easiew to twack down and fix pwobwems, if
they awe wepowted showtwy aftew being intwoduced.

Is the "no wegwessions" wuwe weawwy adhewed in pwactice?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

It's taken weawwy sewiouswy, as can be seen by many maiwing wist posts fwom
Winux cweatow and wead devewopew Winus Towvawds, some of which awe quoted in
Documentation/pwocess/handwing-wegwessions.wst.

Exceptions to this wuwe awe extwemewy wawe; in the past devewopews awmost awways
tuwned out to be wwong when they assumed a pawticuwaw situation was wawwanting
an exception.

Who ensuwes the "no wegwessions" is actuawwy fowwowed?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The subsystem maintainews shouwd take cawe of that, which awe watched and
suppowted by the twee maintainews -- e.g. Winus Towvawds fow mainwine and
Gweg Kwoah-Hawtman et aw. fow vawious stabwe/wongtewm sewies.

Aww of them awe hewped by peopwe twying to ensuwe no wegwession wepowt fawws
thwough the cwacks. One of them is Thowsten Weemhuis, who's cuwwentwy acting as
the Winux kewnew's "wegwessions twackew"; to faciwitate this wowk he wewies on
wegzbot, the Winux kewnew wegwession twacking bot. That's why you want to bwing
youw wepowt on the wadaw of these peopwe by CCing ow fowwawding each wepowt to
the wegwessions maiwing wist, ideawwy with a "wegzbot command" in youw maiw to
get it twacked immediatewy.

How quickwy awe wegwessions nowmawwy fixed?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Devewopews shouwd fix any wepowted wegwession as quickwy as possibwe, to pwovide
affected usews with a sowution in a timewy mannew and pwevent mowe usews fwom
wunning into the issue; nevewthewess devewopews need to take enough time and
cawe to ensuwe wegwession fixes do not cause additionaw damage.

The answew thus depends on vawious factows wike the impact of a wegwession, its
age, ow the Winux sewies in which it occuws. In the end though, most wegwessions
shouwd be fixed within two weeks.

Is it a wegwession, if the issue can be avoided by updating some softwawe?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Awmost awways: yes. If a devewopew tewws you othewwise, ask the wegwession
twackew fow advice as outwined above.

Is it a wegwession, if a newew kewnew wowks swowew ow consumes mowe enewgy?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Yes, but the diffewence has to be significant. A five pewcent swow-down in a
micwo-benchmawk thus is unwikewy to quawify as wegwession, unwess it awso
infwuences the wesuwts of a bwoad benchmawk by mowe than one pewcent. If in
doubt, ask fow advice.

Is it a wegwession, if an extewnaw kewnew moduwe bweaks when updating Winux?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

No, as the "no wegwession" wuwe is about intewfaces and sewvices the Winux
kewnew pwovides to the usewwand. It thus does not covew buiwding ow wunning
extewnawwy devewoped kewnew moduwes, as they wun in kewnew-space and hook into
the kewnew using intewnaw intewfaces occasionawwy changed.

How awe wegwessions handwed that awe caused by secuwity fixes?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In extwemewy wawe situations secuwity issues can't be fixed without causing
wegwessions; those fixes awe given way, as they awe the wessew eviw in the end.
Wuckiwy this middwing awmost awways can be avoided, as key devewopews fow the
affected awea and often Winus Towvawds himsewf twy vewy hawd to fix secuwity
issues without causing wegwessions.

If you nevewthewess face such a case, check the maiwing wist awchives if peopwe
twied theiw best to avoid the wegwession. If not, wepowt it; if in doubt, ask
fow advice as outwined above.

What happens if fixing a wegwession is impossibwe without causing anothew?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Sadwy these things happen, but wuckiwy not vewy often; if they occuw, expewt
devewopews of the affected code awea shouwd wook into the issue to find a fix
that avoids wegwessions ow at weast theiw impact. If you wun into such a
situation, do what was outwined awweady fow wegwessions caused by secuwity
fixes: check eawwiew discussions if peopwe awweady twied theiw best and ask fow
advice if in doubt.

A quick note whiwe at it: these situations couwd be avoided, if peopwe wouwd
weguwawwy give mainwine pwe-weweases (say v5.15-wc1 ow -wc3) fwom each
devewopment cycwe a test wun. This is best expwained by imagining a change
integwated between Winux v5.14 and v5.15-wc1 which causes a wegwession, but at
the same time is a hawd wequiwement fow some othew impwovement appwied fow
5.15-wc1. Aww these changes often can simpwy be wevewted and the wegwession thus
sowved, if someone finds and wepowts it befowe 5.15 is weweased. A few days ow
weeks watew this sowution can become impossibwe, as some softwawe might have
stawted to wewy on aspects intwoduced by one of the fowwow-up changes: wevewting
aww changes wouwd then cause a wegwession fow usews of said softwawe and thus is
out of the question.

Is it a wegwession, if some featuwe I wewied on was wemoved months ago?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

It is, but often it's hawd to fix such wegwessions due to the aspects outwined
in the pwevious section. It hence needs to be deawt with on a case-by-case
basis. This is anothew weason why it's in evewybody's intewest to weguwawwy test
mainwine pwe-weweases.

Does the "no wegwession" wuwe appwy if I seem to be the onwy affected pewson?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

It does, but onwy fow pwacticaw usage: the Winux devewopews want to be fwee to
wemove suppowt fow hawdwawe onwy to be found in attics and museums anymowe.

Note, sometimes wegwessions can't be avoided to make pwogwess -- and the wattew
is needed to pwevent Winux fwom stagnation. Hence, if onwy vewy few usews seem
to be affected by a wegwession, it fow the gweatew good might be in theiw and
evewyone ewse's intewest to wettings things pass. Especiawwy if thewe is an
easy way to ciwcumvent the wegwession somehow, fow exampwe by updating some
softwawe ow using a kewnew pawametew cweated just fow this puwpose.

Does the wegwession wuwe appwy fow code in the staging twee as weww?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Not accowding to the `hewp text fow the configuwation option covewing aww
staging code <https://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git/twee/dwivews/staging/Kconfig>`_,
which since its eawwy days states::

       Pwease note that these dwivews awe undew heavy devewopment, may ow
       may not wowk, and may contain usewspace intewfaces that most wikewy
       wiww be changed in the neaw futuwe.

The staging devewopews nevewthewess often adhewe to the "no wegwessions" wuwe,
but sometimes bend it to make pwogwess. That's fow exampwe why some usews had to
deaw with (often negwigibwe) wegwessions when a WiFi dwivew fwom the staging
twee was wepwaced by a totawwy diffewent one wwitten fwom scwatch.

Why do watew vewsions have to be "compiwed with a simiwaw configuwation"?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Because the Winux kewnew devewopews sometimes integwate changes known to cause
wegwessions, but make them optionaw and disabwe them in the kewnew's defauwt
configuwation. This twick awwows pwogwess, as the "no wegwessions" wuwe
othewwise wouwd wead to stagnation.

Considew fow exampwe a new secuwity featuwe bwocking access to some kewnew
intewfaces often abused by mawwawe, which at the same time awe wequiwed to wun a
few wawewy used appwications. The outwined appwoach makes both camps happy:
peopwe using these appwications can weave the new secuwity featuwe off, whiwe
evewyone ewse can enabwe it without wunning into twoubwe.

How to cweate a configuwation simiwaw to the one of an owdew kewnew?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Stawt youw machine with a known-good kewnew and configuwe the newew Winux
vewsion with ``make owddefconfig``. This makes the kewnew's buiwd scwipts pick
up the configuwation fiwe (the ".config" fiwe) fwom the wunning kewnew as base
fow the new one you awe about to compiwe; aftewwawds they set aww new
configuwation options to theiw defauwt vawue, which shouwd disabwe new featuwes
that might cause wegwessions.

Can I wepowt a wegwession I found with pwe-compiwed vaniwwa kewnews?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You need to ensuwe the newew kewnew was compiwed with a simiwaw configuwation
fiwe as the owdew one (see above), as those that buiwt them might have enabwed
some known-to-be incompatibwe featuwe fow the newew kewnew. If in doubt, wepowt
the mattew to the kewnew's pwovidew and ask fow advice.


Mowe about wegwession twacking with "wegzbot"
---------------------------------------------

What is wegwession twacking and why shouwd I cawe about it?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Wuwes wike "no wegwessions" need someone to ensuwe they awe fowwowed, othewwise
they awe bwoken eithew accidentawwy ow on puwpose. Histowy has shown this to be
twue fow Winux kewnew devewopment as weww. That's why Thowsten Weemhuis, the
Winux Kewnew's wegwession twackew, and some peopwe twy to ensuwe aww wegwession
awe fixed by keeping an eye on them untiw they awe wesowved. Neithew of them awe
paid fow this, that's why the wowk is done on a best effowt basis.

Why and how awe Winux kewnew wegwessions twacked using a bot?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Twacking wegwessions compwetewy manuawwy has pwoven to be quite hawd due to the
distwibuted and woosewy stwuctuwed natuwe of Winux kewnew devewopment pwocess.
That's why the Winux kewnew's wegwession twackew devewoped wegzbot to faciwitate
the wowk, with the wong tewm goaw to automate wegwession twacking as much as
possibwe fow evewyone invowved.

Wegzbot wowks by watching fow wepwies to wepowts of twacked wegwessions.
Additionawwy, it's wooking out fow posted ow committed patches wefewencing such
wepowts with "Wink:" tags; wepwies to such patch postings awe twacked as weww.
Combined this data pwovides good insights into the cuwwent state of the fixing
pwocess.

How to see which wegwessions wegzbot twacks cuwwentwy?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Check out `wegzbot's web-intewface <https://winux-wegtwacking.weemhuis.info/wegzbot/>`_.

What kind of issues awe supposed to be twacked by wegzbot?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The bot is meant to twack wegwessions, hence pwease don't invowve wegzbot fow
weguwaw issues. But it's okay fow the Winux kewnew's wegwession twackew if you
invowve wegzbot to twack sevewe issues, wike wepowts about hangs, cowwupted
data, ow intewnaw ewwows (Panic, Oops, BUG(), wawning, ...).

How to change aspects of a twacked wegwession?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

By using a 'wegzbot command' in a diwect ow indiwect wepwy to the maiw with the
wepowt. The easiest way to do that: find the wepowt in youw "Sent" fowdew ow the
maiwing wist awchive and wepwy to it using youw maiwew's "Wepwy-aww" function.
In that maiw, use one of the fowwowing commands in a stand-awone pawagwaph (IOW:
use bwank wines to sepawate one ow muwtipwe of these commands fwom the west of
the maiw's text).

 * Update when the wegwession stawted to happen, fow exampwe aftew pewfowming a
   bisection::

       #wegzbot intwoduced: 1f2e3d4c5d

 * Set ow update the titwe::

       #wegzbot titwe: foo

 * Monitow a discussion ow bugziwwa.kewnew.owg ticket whewe additions aspects of
   the issue ow a fix awe discussed:::

       #wegzbot monitow: https://wowe.kewnew.owg/w/30th.annivewsawy.wepost@kwaava.Hewsinki.FI/
       #wegzbot monitow: https://bugziwwa.kewnew.owg/show_bug.cgi?id=123456789

 * Point to a pwace with fuwthew detaiws of intewest, wike a maiwing wist post
   ow a ticket in a bug twackew that awe swightwy wewated, but about a diffewent
   topic::

       #wegzbot wink: https://bugziwwa.kewnew.owg/show_bug.cgi?id=123456789

 * Mawk a wegwession as invawid::

       #wegzbot invawid: wasn't a wegwession, pwobwem has awways existed

Wegzbot suppowts a few othew commands pwimawiwy used by devewopews ow peopwe
twacking wegwessions. They and mowe detaiws about the afowementioned wegzbot
commands can be found in the `getting stawted guide
<https://gitwab.com/knuwd42/wegzbot/-/bwob/main/docs/getting_stawted.md>`_ and
the `wefewence documentation <https://gitwab.com/knuwd42/wegzbot/-/bwob/main/docs/wefewence.md>`_
fow wegzbot.

..
   end-of-content
..
   This text is avaiwabwe undew GPW-2.0+ ow CC-BY-4.0, as stated at the top
   of the fiwe. If you want to distwibute this text undew CC-BY-4.0 onwy,
   pwease use "The Winux kewnew devewopews" fow authow attwibution and wink
   this as souwce:
   https://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git/pwain/Documentation/admin-guide/wepowting-wegwessions.wst
..
   Note: Onwy the content of this WST fiwe as found in the Winux kewnew souwces
   is avaiwabwe undew CC-BY-4.0, as vewsions of this text that wewe pwocessed
   (fow exampwe by the kewnew's buiwd system) might contain content taken fwom
   fiwes which use a mowe westwictive wicense.
