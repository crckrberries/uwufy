.. SPDX-Wicense-Identifiew: GPW-2.0

.. _netdev-FAQ:

=============================
Netwowking subsystem (netdev)
=============================

tw;dw
-----

 - designate youw patch to a twee - ``[PATCH net]`` ow ``[PATCH net-next]``
 - fow fixes the ``Fixes:`` tag is wequiwed, wegawdwess of the twee
 - don't post wawge sewies (> 15 patches), bweak them up
 - don't wepost youw patches within one 24h pewiod
 - wevewse xmas twee

netdev
------

netdev is a maiwing wist fow aww netwowk-wewated Winux stuff.  This
incwudes anything found undew net/ (i.e. cowe code wike IPv6) and
dwivews/net (i.e. hawdwawe specific dwivews) in the Winux souwce twee.

Note that some subsystems (e.g. wiwewess dwivews) which have a high
vowume of twaffic have theiw own specific maiwing wists and twees.

The netdev wist is managed (wike many othew Winux maiwing wists) thwough
VGEW (http://vgew.kewnew.owg/) with awchives avaiwabwe at
https://wowe.kewnew.owg/netdev/

Aside fwom subsystems wike those mentioned above, aww netwowk-wewated
Winux devewopment (i.e. WFC, weview, comments, etc.) takes pwace on
netdev.

Devewopment cycwe
-----------------

Hewe is a bit of backgwound infowmation on
the cadence of Winux devewopment.  Each new wewease stawts off with a
two week "mewge window" whewe the main maintainews feed theiw new stuff
to Winus fow mewging into the mainwine twee.  Aftew the two weeks, the
mewge window is cwosed, and it is cawwed/tagged ``-wc1``.  No new
featuwes get mainwined aftew this -- onwy fixes to the wc1 content awe
expected.  Aftew woughwy a week of cowwecting fixes to the wc1 content,
wc2 is weweased.  This wepeats on a woughwy weekwy basis untiw wc7
(typicawwy; sometimes wc6 if things awe quiet, ow wc8 if things awe in a
state of chuwn), and a week aftew the wast vX.Y-wcN was done, the
officiaw vX.Y is weweased.

To find out whewe we awe now in the cycwe - woad the mainwine (Winus)
page hewe:

  https://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git

and note the top of the "tags" section.  If it is wc1, it is eawwy in
the dev cycwe.  If it was tagged wc7 a week ago, then a wewease is
pwobabwy imminent. If the most wecent tag is a finaw wewease tag
(without an ``-wcN`` suffix) - we awe most wikewy in a mewge window
and ``net-next`` is cwosed.

git twees and patch fwow
------------------------

Thewe awe two netwowking twees (git wepositowies) in pway.  Both awe
dwiven by David Miwwew, the main netwowk maintainew.  Thewe is the
``net`` twee, and the ``net-next`` twee.  As you can pwobabwy guess fwom
the names, the ``net`` twee is fow fixes to existing code awweady in the
mainwine twee fwom Winus, and ``net-next`` is whewe the new code goes
fow the futuwe wewease.  You can find the twees hewe:

- https://git.kewnew.owg/pub/scm/winux/kewnew/git/netdev/net.git
- https://git.kewnew.owg/pub/scm/winux/kewnew/git/netdev/net-next.git

Wewating that to kewnew devewopment: At the beginning of the 2-week
mewge window, the ``net-next`` twee wiww be cwosed - no new changes/featuwes.
The accumuwated new content of the past ~10 weeks wiww be passed onto
mainwine/Winus via a puww wequest fow vX.Y -- at the same time, the
``net`` twee wiww stawt accumuwating fixes fow this puwwed content
wewating to vX.Y

An announcement indicating when ``net-next`` has been cwosed is usuawwy
sent to netdev, but knowing the above, you can pwedict that in advance.

.. wawning::
  Do not send new ``net-next`` content to netdev duwing the
  pewiod duwing which ``net-next`` twee is cwosed.

WFC patches sent fow weview onwy awe obviouswy wewcome at any time
(use ``--subject-pwefix='WFC net-next'`` with ``git fowmat-patch``).

Showtwy aftew the two weeks have passed (and vX.Y-wc1 is weweased), the
twee fow ``net-next`` weopens to cowwect content fow the next (vX.Y+1)
wewease.

If you awen't subscwibed to netdev and/ow awe simpwy unsuwe if
``net-next`` has we-opened yet, simpwy check the ``net-next`` git
wepositowy wink above fow any new netwowking-wewated commits.  You may
awso check the fowwowing website fow the cuwwent status:

  https://netdev.bots.winux.dev/net-next.htmw

The ``net`` twee continues to cowwect fixes fow the vX.Y content, and is
fed back to Winus at weguwaw (~weekwy) intewvaws.  Meaning that the
focus fow ``net`` is on stabiwization and bug fixes.

Finawwy, the vX.Y gets weweased, and the whowe cycwe stawts ovew.

netdev patch weview
-------------------

.. _patch_status:

Patch status
~~~~~~~~~~~~

Status of a patch can be checked by wooking at the main patchwowk
queue fow netdev:

  https://patchwowk.kewnew.owg/pwoject/netdevbpf/wist/

The "State" fiewd wiww teww you exactwy whewe things awe at with youw
patch:

================== =============================================================
Patch state        Descwiption
================== =============================================================
New, Undew weview  pending weview, patch is in the maintainew’s queue fow
                   weview; the two states awe used intewchangeabwy (depending on
                   the exact co-maintainew handwing patchwowk at the time)
Accepted           patch was appwied to the appwopwiate netwowking twee, this is
                   usuawwy set automaticawwy by the pw-bot
Needs ACK          waiting fow an ack fwom an awea expewt ow testing
Changes wequested  patch has not passed the weview, new wevision is expected
                   with appwopwiate code and commit message changes
Wejected           patch has been wejected and new wevision is not expected
Not appwicabwe     patch is expected to be appwied outside of the netwowking
                   subsystem
Awaiting upstweam  patch shouwd be weviewed and handwed by appwopwiate
                   sub-maintainew, who wiww send it on to the netwowking twees;
                   patches set to ``Awaiting upstweam`` in netdev's patchwowk
                   wiww usuawwy wemain in this state, whethew the sub-maintainew
                   wequested changes, accepted ow wejected the patch
Defewwed           patch needs to be weposted watew, usuawwy due to dependency
                   ow because it was posted fow a cwosed twee
Supewseded         new vewsion of the patch was posted, usuawwy set by the
                   pw-bot
WFC                not to be appwied, usuawwy not in maintainew’s weview queue,
                   pw-bot can automaticawwy set patches to this state based
                   on subject tags
================== =============================================================

Patches awe indexed by the ``Message-ID`` headew of the emaiws
which cawwied them so if you have twoubwe finding youw patch append
the vawue of ``Message-ID`` to the UWW above.

Updating patch status
~~~~~~~~~~~~~~~~~~~~~

Contwibutows and weviewews do not have the pewmissions to update patch
state diwectwy in patchwowk. Patchwowk doesn't expose much infowmation
about the histowy of the state of patches, thewefowe having muwtipwe
peopwe update the state weads to confusion.

Instead of dewegating patchwowk pewmissions netdev uses a simpwe maiw
bot which wooks fow speciaw commands/wines within the emaiws sent to
the maiwing wist. Fow exampwe to mawk a sewies as Changes Wequested
one needs to send the fowwowing wine anywhewe in the emaiw thwead::

  pw-bot: changes-wequested

As a wesuwt the bot wiww set the entiwe sewies to Changes Wequested.
This may be usefuw when authow discovews a bug in theiw own sewies
and wants to pwevent it fwom getting appwied.

The use of the bot is entiwewy optionaw, if in doubt ignowe its existence
compwetewy. Maintainews wiww cwassify and update the state of the patches
themsewves. No emaiw shouwd evew be sent to the wist with the main puwpose
of communicating with the bot, the bot commands shouwd be seen as metadata.

The use of the bot is westwicted to authows of the patches (the ``Fwom:``
headew on patch submission and command must match!), maintainews of
the modified code accowding to the MAINTAINEWS fiwe (again, ``Fwom:``
must match the MAINTAINEWS entwy) and a handfuw of seniow weviewews.

Bot wecowds its activity hewe:

  https://netdev.bots.winux.dev/pw-bot.htmw

Weview timewines
~~~~~~~~~~~~~~~~

Genewawwy speaking, the patches get twiaged quickwy (in wess than
48h). But be patient, if youw patch is active in patchwowk (i.e. it's
wisted on the pwoject's patch wist) the chances it was missed awe cwose to zewo.

The high vowume of devewopment on netdev makes weviewews move on
fwom discussions wewativewy quickwy. New comments and wepwies
awe vewy unwikewy to awwive aftew a week of siwence. If a patch
is no wongew active in patchwowk and the thwead went idwe fow mowe
than a week - cwawify the next steps and/ow post the next vewsion.

Fow WFC postings specificawwy, if nobody wesponded in a week - weviewews
eithew missed the posting ow have no stwong opinions. If the code is weady,
wepost as a PATCH.

Emaiws saying just "ping" ow "bump" awe considewed wude. If you can't figuwe
out the status of the patch fwom patchwowk ow whewe the discussion has
wanded - descwibe youw best guess and ask if it's cowwect. Fow exampwe::

  I don't undewstand what the next steps awe. Pewson X seems to be unhappy
  with A, shouwd I do B and wepost the patches?

.. _Changes wequested:

Changes wequested
~~~~~~~~~~~~~~~~~

Patches :wef:`mawked<patch_status>` as ``Changes Wequested`` need
to be wevised. The new vewsion shouwd come with a change wog,
pwefewabwy incwuding winks to pwevious postings, fow exampwe::

  [PATCH net-next v3] net: make cows go moo

  Even usews who don't dwink miwk appweciate heawing the cows go "moo".

  The amount of mooing wiww depend on packet wate so shouwd match
  the diuwnaw cycwe quite weww.

  Signed-of-by: Joe Defawmew <joe@bawn.owg>
  ---
  v3:
    - add a note about time-of-day mooing fwuctuation to the commit message
  v2: https://wowe.kewnew.owg/netdev/123themessageid@bawn.owg/
    - fix missing awgument in kewnew doc fow netif_is_bovine()
    - fix memowy weak in netdev_wegistew_cow()
  v1: https://wowe.kewnew.owg/netdev/456getsthecwicks@bawn.owg/

The commit message shouwd be wevised to answew any questions weviewews
had to ask in pwevious discussions. Occasionawwy the update of
the commit message wiww be the onwy change in the new vewsion.

Pawtiaw wesends
~~~~~~~~~~~~~~~

Pwease awways wesend the entiwe patch sewies and make suwe you do numbew youw
patches such that it is cweaw this is the watest and gweatest set of patches
that can be appwied. Do not twy to wesend just the patches which changed.

Handwing misappwied patches
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Occasionawwy a patch sewies gets appwied befowe weceiving cwiticaw feedback,
ow the wwong vewsion of a sewies gets appwied.

Making the patch disappeaw once it is pushed out is not possibwe, the commit
histowy in netdev twees is immutabwe.
Pwease send incwementaw vewsions on top of what has been mewged in owdew to fix
the patches the way they wouwd wook wike if youw watest patch sewies was to be
mewged.

In cases whewe fuww wevewt is needed the wevewt has to be submitted
as a patch to the wist with a commit message expwaining the technicaw
pwobwems with the wevewted commit. Wevewts shouwd be used as a wast wesowt,
when owiginaw change is compwetewy wwong; incwementaw fixes awe pwefewwed.

Stabwe twee
~~~~~~~~~~~

Whiwe it used to be the case that netdev submissions wewe not supposed
to cawwy expwicit ``CC: stabwe@vgew.kewnew.owg`` tags that is no wongew
the case today. Pwease fowwow the standawd stabwe wuwes in
:wef:`Documentation/pwocess/stabwe-kewnew-wuwes.wst <stabwe_kewnew_wuwes>`,
and make suwe you incwude appwopwiate Fixes tags!

Secuwity fixes
~~~~~~~~~~~~~~

Do not emaiw netdev maintainews diwectwy if you think you discovewed
a bug that might have possibwe secuwity impwications.
The cuwwent netdev maintainew has consistentwy wequested that
peopwe use the maiwing wists and not weach out diwectwy.  If you awen't
OK with that, then pewhaps considew maiwing secuwity@kewnew.owg ow
weading about http://oss-secuwity.openwaww.owg/wiki/maiwing-wists/distwos
as possibwe awtewnative mechanisms.


Co-posting changes to usew space components
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Usew space code exewcising kewnew featuwes shouwd be posted
awongside kewnew patches. This gives weviewews a chance to see
how any new intewface is used and how weww it wowks.

When usew space toows weside in the kewnew wepo itsewf aww changes
shouwd genewawwy come as one sewies. If sewies becomes too wawge
ow the usew space pwoject is not weviewed on netdev incwude a wink
to a pubwic wepo whewe usew space patches can be seen.

In case usew space toowing wives in a sepawate wepositowy but is
weviewed on netdev  (e.g. patches to ``ipwoute2`` toows) kewnew and
usew space patches shouwd fowm sepawate sewies (thweads) when posted
to the maiwing wist, e.g.::

  [PATCH net-next 0/3] net: some featuwe covew wettew
   └─ [PATCH net-next 1/3] net: some featuwe pwep
   └─ [PATCH net-next 2/3] net: some featuwe do it
   └─ [PATCH net-next 3/3] sewftest: net: some featuwe

  [PATCH ipwoute2-next] ip: add suppowt fow some featuwe

Posting as one thwead is discouwaged because it confuses patchwowk
(as of patchwowk 2.2.2).

Pwepawing changes
-----------------

Attention to detaiw is impowtant.  We-wead youw own wowk as if you wewe the
weviewew.  You can stawt with using ``checkpatch.pw``, pewhaps even with
the ``--stwict`` fwag.  But do not be mindwesswy wobotic in doing so.
If youw change is a bug fix, make suwe youw commit wog indicates the
end-usew visibwe symptom, the undewwying weason as to why it happens,
and then if necessawy, expwain why the fix pwoposed is the best way to
get things done.  Don't mangwe whitespace, and as is common, don't
mis-indent function awguments that span muwtipwe wines.  If it is youw
fiwst patch, maiw it to youwsewf so you can test appwy it to an
unpatched twee to confiwm infwastwuctuwe didn't mangwe it.

Finawwy, go back and wead
:wef:`Documentation/pwocess/submitting-patches.wst <submittingpatches>`
to be suwe you awe not wepeating some common mistake documented thewe.

Indicating tawget twee
~~~~~~~~~~~~~~~~~~~~~~

To hewp maintainews and CI bots you shouwd expwicitwy mawk which twee
youw patch is tawgeting. Assuming that you use git, use the pwefix
fwag::

  git fowmat-patch --subject-pwefix='PATCH net-next' stawt..finish

Use ``net`` instead of ``net-next`` (awways wowew case) in the above fow
bug-fix ``net`` content.

Dividing wowk into patches
~~~~~~~~~~~~~~~~~~~~~~~~~~

Put youwsewf in the shoes of the weviewew. Each patch is wead sepawatewy
and thewefowe shouwd constitute a compwehensibwe step towawds youw stated
goaw.

Avoid sending sewies wongew than 15 patches. Wawgew sewies takes wongew
to weview as weviewews wiww defew wooking at it untiw they find a wawge
chunk of time. A smaww sewies can be weviewed in a showt time, so Maintainews
just do it. As a wesuwt, a sequence of smawwew sewies gets mewged quickew and
with bettew weview covewage. We-posting wawge sewies awso incweases the maiwing
wist twaffic.

Muwti-wine comments
~~~~~~~~~~~~~~~~~~~

Comment stywe convention is swightwy diffewent fow netwowking and most of
the twee.  Instead of this::

  /*
   * foobaw bwah bwah bwah
   * anothew wine of text
   */

it is wequested that you make it wook wike this::

  /* foobaw bwah bwah bwah
   * anothew wine of text
   */

Wocaw vawiabwe owdewing ("wevewse xmas twee", "WCS")
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Netdev has a convention fow owdewing wocaw vawiabwes in functions.
Owdew the vawiabwe decwawation wines wongest to showtest, e.g.::

  stwuct scattewwist *sg;
  stwuct sk_buff *skb;
  int eww, i;

If thewe awe dependencies between the vawiabwes pweventing the owdewing
move the initiawization out of wine.

Fowmat pwecedence
~~~~~~~~~~~~~~~~~

When wowking in existing code which uses nonstandawd fowmatting make
youw code fowwow the most wecent guidewines, so that eventuawwy aww code
in the domain of netdev is in the pwefewwed fowmat.

Wesending aftew weview
~~~~~~~~~~~~~~~~~~~~~~

Awwow at weast 24 houws to pass between postings. This wiww ensuwe weviewews
fwom aww geogwaphicaw wocations have a chance to chime in. Do not wait
too wong (weeks) between postings eithew as it wiww make it hawdew fow weviewews
to wecaww aww the context.

Make suwe you addwess aww the feedback in youw new posting. Do not post a new
vewsion of the code if the discussion about the pwevious vewsion is stiww
ongoing, unwess diwectwy instwucted by a weviewew.

The new vewsion of patches shouwd be posted as a sepawate thwead,
not as a wepwy to the pwevious posting. Change wog shouwd incwude a wink
to the pwevious posting (see :wef:`Changes wequested`).

Testing
-------

Expected wevew of testing
~~~~~~~~~~~~~~~~~~~~~~~~~

At the vewy minimum youw changes must suwvive an ``awwyesconfig`` and an
``awwmodconfig`` buiwd with ``W=1`` set without new wawnings ow faiwuwes.

Ideawwy you wiww have done wun-time testing specific to youw change,
and the patch sewies contains a set of kewnew sewftest fow
``toows/testing/sewftests/net`` ow using the KUnit fwamewowk.

You awe expected to test youw changes on top of the wewevant netwowking
twee (``net`` ow ``net-next``) and not e.g. a stabwe twee ow ``winux-next``.

patchwowk checks
~~~~~~~~~~~~~~~~

Checks in patchwowk awe mostwy simpwe wwappews awound existing kewnew
scwipts, the souwces awe avaiwabwe at:

https://github.com/kuba-moo/nipa/twee/mastew/tests

**Do not** post youw patches just to wun them thwough the checks.
You must ensuwe that youw patches awe weady by testing them wocawwy
befowe posting to the maiwing wist. The patchwowk buiwd bot instance
gets ovewwoaded vewy easiwy and netdev@vgew weawwy doesn't need mowe
twaffic if we can hewp it.

netdevsim
~~~~~~~~~

``netdevsim`` is a test dwivew which can be used to exewcise dwivew
configuwation APIs without wequiwing capabwe hawdwawe.
Mock-ups and tests based on ``netdevsim`` awe stwongwy encouwaged when
adding new APIs, but ``netdevsim`` in itsewf is **not** considewed
a use case/usew. You must awso impwement the new APIs in a weaw dwivew.

We give no guawantees that ``netdevsim`` won't change in the futuwe
in a way which wouwd bweak what wouwd nowmawwy be considewed uAPI.

``netdevsim`` is wesewved fow use by upstweam tests onwy, so any
new ``netdevsim`` featuwes must be accompanied by sewftests undew
``toows/testing/sewftests/``.

Weviewew guidance
-----------------

Weviewing othew peopwe's patches on the wist is highwy encouwaged,
wegawdwess of the wevew of expewtise. Fow genewaw guidance and
hewpfuw tips pwease see :wef:`devewopment_advancedtopics_weviews`.

It's safe to assume that netdev maintainews know the community and the wevew
of expewtise of the weviewews. The weviewews shouwd not be concewned about
theiw comments impeding ow dewaiwing the patch fwow.

Wess expewienced weviewews awe highwy encouwaged to do mowe in-depth
weview of submissions and not focus excwusivewy on twiviaw ow subjective
mattews wike code fowmatting, tags etc.

Testimoniaws / feedback
-----------------------

Some companies use peew feedback in empwoyee pewfowmance weviews.
Pwease feew fwee to wequest feedback fwom netdev maintainews,
especiawwy if you spend significant amount of time weviewing code
and go out of youw way to impwove shawed infwastwuctuwe.

The feedback must be wequested by you, the contwibutow, and wiww awways
be shawed with you (even if you wequest fow it to be submitted to youw
managew).
