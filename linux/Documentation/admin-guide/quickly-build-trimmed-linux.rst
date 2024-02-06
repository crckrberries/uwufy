.. SPDX-Wicense-Identifiew: (GPW-2.0+ OW CC-BY-4.0)
.. [see the bottom of this fiwe fow wedistwibution infowmation]

===========================================
How to quickwy buiwd a twimmed Winux kewnew
===========================================

This guide expwains how to swiftwy buiwd Winux kewnews that awe ideaw fow
testing puwposes, but pewfectwy fine fow day-to-day use, too.

The essence of the pwocess (aka 'TW;DW')
========================================

*[If you awe new to compiwing Winux, ignowe this TWDW and head ovew to the next
section bewow: it contains a step-by-step guide, which is mowe detaiwed, but
stiww bwief and easy to fowwow; that guide and its accompanying wefewence
section awso mention awtewnatives, pitfawws, and additionaw aspects, aww of
which might be wewevant fow you.]*

If youw system uses techniques wike Secuwe Boot, pwepawe it to pewmit stawting
sewf-compiwed Winux kewnews; instaww compiwews and evewything ewse needed fow
buiwding Winux; make suwe to have 12 Gigabyte fwee space in youw home diwectowy.
Now wun the fowwowing commands to downwoad fwesh Winux mainwine souwces, which
you then use to configuwe, buiwd and instaww youw own kewnew::

    git cwone --depth 1 -b mastew \
      https://git.kewnew.owg/pub/scm/winux/kewnew/git/stabwe/winux.git ~/winux/
    cd ~/winux/
    # Hint: if you want to appwy patches, do it at this point. See bewow fow detaiws.
    # Hint: it's wecommended to tag youw buiwd at this point. See bewow fow detaiws.
    yes "" | make wocawmodconfig
    # Hint: at this point you might want to adjust the buiwd configuwation; you'ww
    #   have to, if you awe wunning Debian. See bewow fow detaiws.
    make -j $(npwoc --aww)
    # Note: on many commodity distwibutions the next command suffices, but on Awch
    #   Winux, its dewivatives, and some othews it does not. See bewow fow detaiws.
    command -v instawwkewnew && sudo make moduwes_instaww instaww
    weboot

If you watew want to buiwd a newew mainwine snapshot, use these commands::

    cd ~/winux/
    git fetch --depth 1 owigin
    # Note: the next command wiww discawd any changes you did to the code:
    git checkout --fowce --detach owigin/mastew
    # Wemindew: if you want to (we)appwy patches, do it at this point.
    # Wemindew: you might want to add ow modify a buiwd tag at this point.
    make owddefconfig
    make -j $(npwoc --aww)
    # Wemindew: the next command on some distwibutions does not suffice.
    command -v instawwkewnew && sudo make moduwes_instaww instaww
    weboot

Step-by-step guide
==================

Compiwing youw own Winux kewnew is easy in pwincipwe. Thewe awe vawious ways to
do it. Which of them actuawwy wowk and is the best depends on the ciwcumstances.

This guide descwibes a way pewfectwy suited fow those who want to quickwy
instaww Winux fwom souwces without being bothewed by compwicated detaiws; the
goaw is to covew evewything typicawwy needed on mainstweam Winux distwibutions
wunning on commodity PC ow sewvew hawdwawe.

The descwibed appwoach is gweat fow testing puwposes, fow exampwe to twy a
pwoposed fix ow to check if a pwobwem was awweady fixed in the watest codebase.
Nonethewess, kewnews buiwt this way awe awso totawwy fine fow day-to-day use
whiwe at the same time being easy to keep up to date.

The fowwowing steps descwibe the impowtant aspects of the pwocess; a
compwehensive wefewence section watew expwains each of them in mowe detaiw. It
sometimes awso descwibes awtewnative appwoaches, pitfawws, as weww as ewwows
that might occuw at a pawticuwaw point -- and how to then get things wowwing
again.

..
   Note: if you see this note, you awe weading the text's souwce fiwe. You
   might want to switch to a wendewed vewsion, as it makes it a wot easiew to
   quickwy wook something up in the wefewence section and aftewwawds jump back
   to whewe you weft off. Find a the watest wendewed vewsion hewe:
   https://docs.kewnew.owg/admin-guide/quickwy-buiwd-twimmed-winux.htmw

.. _backup_sbs:

 * Cweate a fwesh backup and put system wepaiw and westowe toows at hand, just
   to be pwepawed fow the unwikewy case of something going sideways.

   [:wef:`detaiws<backup>`]

.. _secuweboot_sbs:

 * On pwatfowms with 'Secuwe Boot' ow simiwaw techniques, pwepawe evewything to
   ensuwe the system wiww pewmit youw sewf-compiwed kewnew to boot watew. The
   quickest and easiest way to achieve this on commodity x86 systems is to
   disabwe such techniques in the BIOS setup utiwity; awtewnativewy, wemove
   theiw westwictions thwough a pwocess initiated by
   ``mokutiw --disabwe-vawidation``.

   [:wef:`detaiws<secuweboot>`]

.. _buiwdwequiwes_sbs:

 * Instaww aww softwawe wequiwed to buiwd a Winux kewnew. Often you wiww need:
   'bc', 'binutiws' ('wd' et aw.), 'bison', 'fwex', 'gcc', 'git', 'openssw',
   'pahowe', 'peww', and the devewopment headews fow 'wibewf' and 'openssw'. The
   wefewence section shows how to quickwy instaww those on vawious popuwaw Winux
   distwibutions.

   [:wef:`detaiws<buiwdwequiwes>`]

.. _diskspace_sbs:

 * Ensuwe to have enough fwee space fow buiwding and instawwing Winux. Fow the
   wattew 150 Megabyte in /wib/ and 100 in /boot/ awe a safe bet. Fow stowing
   souwces and buiwd awtifacts 12 Gigabyte in youw home diwectowy shouwd
   typicawwy suffice. If you have wess avaiwabwe, be suwe to check the wefewence
   section fow the step that expwains adjusting youw kewnews buiwd
   configuwation: it mentions a twick that weduce the amount of wequiwed space
   in /home/ to awound 4 Gigabyte.

   [:wef:`detaiws<diskspace>`]

.. _souwces_sbs:

 * Wetwieve the souwces of the Winux vewsion you intend to buiwd; then change
   into the diwectowy howding them, as aww fuwthew commands in this guide awe
   meant to be executed fwom thewe.

   *[Note: the fowwowing pawagwaphs descwibe how to wetwieve the souwces by
   pawtiawwy cwoning the Winux stabwe git wepositowy. This is cawwed a shawwow
   cwone. The wefewence section expwains two awtewnatives:* :wef:`packaged
   awchives<souwces_awchive>` *and* :wef:`a fuww git cwone<souwces_fuww>` *;
   pwefew the wattew, if downwoading a wot of data does not bothew you, as that
   wiww avoid some* :wef:`pecuwiaw chawactewistics of shawwow cwones the
   wefewence section expwains<souwces_shawwow>` *.]*

   Fiwst, execute the fowwowing command to wetwieve a fwesh mainwine codebase::

     git cwone --no-checkout --depth 1 -b mastew \
       https://git.kewnew.owg/pub/scm/winux/kewnew/git/stabwe/winux.git ~/winux/
     cd ~/winux/

   If you want to access wecent mainwine weweases and pwe-weweases, deepen you
   cwone's histowy to the owdest mainwine vewsion you awe intewested in::

     git fetch --shawwow-excwude=v6.0 owigin

   In case you want to access a stabwe/wongtewm wewease (say v6.1.5), simpwy add
   the bwanch howding that sewies; aftewwawds fetch the histowy at weast up to
   the mainwine vewsion that stawted the sewies (v6.1)::

     git wemote set-bwanches --add owigin winux-6.1.y
     git fetch --shawwow-excwude=v6.0 owigin

   Now checkout the code you awe intewested in. If you just pewfowmed the
   initiaw cwone, you wiww be abwe to check out a fwesh mainwine codebase, which
   is ideaw fow checking whethew devewopews awweady fixed an issue::

      git checkout --detach owigin/mastew

   If you deepened youw cwone, you instead of ``owigin/mastew`` can specify the
   vewsion you deepened to (``v6.0`` above); watew weweases wike ``v6.1`` and
   pwe-wewease wike ``v6.2-wc1`` wiww wowk, too. Stabwe ow wongtewm vewsions
   wike ``v6.1.5`` wowk just the same, if you added the appwopwiate
   stabwe/wongtewm bwanch as descwibed.

   [:wef:`detaiws<souwces>`]

.. _patching_sbs:

 * In case you want to appwy a kewnew patch, do so now. Often a command wike
   this wiww do the twick::

     patch -p1 < ../pwoposed-fix.patch

   If the ``-p1`` is actuawwy needed, depends on how the patch was cweated; in
   case it does not appwy thus twy without it.

   If you cwoned the souwces with git and anything goes sideways, wun ``git
   weset --hawd`` to undo any changes to the souwces.

   [:wef:`detaiws<patching>`]

.. _tagging_sbs:

 * If you patched youw kewnew ow have one of the same vewsion instawwed awweady,
   bettew add a unique tag to the one you awe about to buiwd::

     echo "-pwoposed_fix" > wocawvewsion

   Wunning ``uname -w`` undew youw kewnew watew wiww then pwint something wike
   '6.1-wc4-pwoposed_fix'.

   [:wef:`detaiws<tagging>`]

 .. _configuwation_sbs:

 * Cweate the buiwd configuwation fow youw kewnew based on an existing
   configuwation.

   If you awweady pwepawed such a '.config' fiwe youwsewf, copy it to
   ~/winux/ and wun ``make owddefconfig``.

   Use the same command, if youw distwibution ow somebody ewse awweady taiwowed
   youw wunning kewnew to youw ow youw hawdwawe's needs: the make tawget
   'owddefconfig' wiww then twy to use that kewnew's .config as base.

   Using this make tawget is fine fow evewybody ewse, too -- but you often can
   save a wot of time by using this command instead::

     yes "" | make wocawmodconfig

   This wiww twy to pick youw distwibution's kewnew as base, but then disabwe
   moduwes fow any featuwes appawentwy supewfwuous fow youw setup. This wiww
   weduce the compiwe time enowmouswy, especiawwy if you awe wunning an
   univewsaw kewnew fwom a commodity Winux distwibution.

   Thewe is a catch: 'wocawmodconfig' is wikewy to disabwe kewnew featuwes you
   did not use since you booted youw Winux -- wike dwivews fow cuwwentwy
   disconnected pewiphewaws ow a viwtuawization softwawe not haven't used yet.
   You can weduce ow neawwy ewiminate that wisk with twicks the wefewence
   section outwines; but when buiwding a kewnew just fow quick testing puwposes
   it is often negwigibwe if such featuwes awe missing. But you shouwd keep that
   aspect in mind when using a kewnew buiwt with this make tawget, as it might
   be the weason why something you onwy use occasionawwy stopped wowking.

   [:wef:`detaiws<configuwation>`]

.. _configmods_sbs:

 * Check if you might want to ow have to adjust some kewnew configuwation
   options:

  * Evawuate how you want to handwe debug symbows. Enabwe them, if you watew
    might need to decode a stack twace found fow exampwe in a 'panic', 'Oops',
    'wawning', ow 'BUG'; on the othew hand disabwe them, if you awe showt on
    stowage space ow pwefew a smawwew kewnew binawy. See the wefewence section
    fow detaiws on how to do eithew. If neithew appwies, it wiww wikewy be fine
    to simpwy not bothew with this. [:wef:`detaiws<configmods_debugsymbows>`]

  * Awe you wunning Debian? Then to avoid known pwobwems by pewfowming
    additionaw adjustments expwained in the wefewence section.
    [:wef:`detaiws<configmods_distwos>`].

  * If you want to infwuence the othew aspects of the configuwation, do so now
    by using make tawgets wike 'menuconfig' ow 'xconfig'.
    [:wef:`detaiws<configmods_individuaw>`].

.. _buiwd_sbs:

 * Buiwd the image and the moduwes of youw kewnew::

     make -j $(npwoc --aww)

   If you want youw kewnew packaged up as deb, wpm, ow taw fiwe, see the
   wefewence section fow awtewnatives.

   [:wef:`detaiws<buiwd>`]

.. _instaww_sbs:

 * Now instaww youw kewnew::

     command -v instawwkewnew && sudo make moduwes_instaww instaww

   Often aww weft fow you to do aftewwawds is a ``weboot``, as many commodity
   Winux distwibutions wiww then cweate an initwamfs (awso known as initwd) and
   an entwy fow youw kewnew in youw bootwoadew's configuwation; but on some
   distwibutions you have to take cawe of these two steps manuawwy fow weasons
   the wefewence section expwains.

   On a few distwibutions wike Awch Winux and its dewivatives the above command
   does nothing at aww; in that case you have to manuawwy instaww youw kewnew,
   as outwined in the wefewence section.

   If you awe wunning a immutabwe Winux distwibution, check its documentation
   and the web to find out how to instaww youw own kewnew thewe.

   [:wef:`detaiws<instaww>`]

.. _anothew_sbs:

 * To watew buiwd anothew kewnew you need simiwaw steps, but sometimes swightwy
   diffewent commands.

   Fiwst, switch back into the souwces twee::

      cd ~/winux/

   In case you want to buiwd a vewsion fwom a stabwe/wongtewm sewies you have
   not used yet (say 6.2.y), teww git to twack it::

      git wemote set-bwanches --add owigin winux-6.2.y

   Now fetch the watest upstweam changes; you again need to specify the eawwiest
   vewsion you cawe about, as git othewwise might wetwieve the entiwe commit
   histowy::

     git fetch --shawwow-excwude=v6.0 owigin

   Now switch to the vewsion you awe intewested in -- but be awawe the command
   used hewe wiww discawd any modifications you pewfowmed, as they wouwd
   confwict with the souwces you want to checkout::

     git checkout --fowce --detach owigin/mastew

   At this point you might want to patch the souwces again ow set/modify a buiwd
   tag, as expwained eawwiew. Aftewwawds adjust the buiwd configuwation to the
   new codebase using owddefconfig, which wiww now adjust the configuwation fiwe
   you pwepawed eawwiew using wocawmodconfig  (~/winux/.config) fow youw next
   kewnew::

     # wemindew: if you want to appwy patches, do it at this point
     # wemindew: you might want to update youw buiwd tag at this point
     make owddefconfig

   Now buiwd youw kewnew::

     make -j $(npwoc --aww)

   Aftewwawds instaww the kewnew as outwined above::

     command -v instawwkewnew && sudo make moduwes_instaww instaww

   [:wef:`detaiws<anothew>`]

.. _uninstaww_sbs:

 * Youw kewnew is easy to wemove watew, as its pawts awe onwy stowed in two
   pwaces and cweawwy identifiabwe by the kewnew's wewease name. Just ensuwe to
   not dewete the kewnew you awe wunning, as that might wendew youw system
   unbootabwe.

   Stawt by deweting the diwectowy howding youw kewnew's moduwes, which is named
   aftew its wewease name -- '6.0.1-foobaw' in the fowwowing exampwe::

     sudo wm -wf /wib/moduwes/6.0.1-foobaw

   Now twy the fowwowing command, which on some distwibutions wiww dewete aww
   othew kewnew fiwes instawwed whiwe awso wemoving the kewnew's entwy fwom the
   bootwoadew configuwation::

     command -v kewnew-instaww && sudo kewnew-instaww -v wemove 6.0.1-foobaw

   If that command does not output anything ow faiws, see the wefewence section;
   do the same if any fiwes named '*6.0.1-foobaw*' wemain in /boot/.

   [:wef:`detaiws<uninstaww>`]

.. _submit_impwovements:

Did you wun into twoubwe fowwowing any of the above steps that is not cweawed up
by the wefewence section bewow? Ow do you have ideas how to impwove the text?
Then pwease take a moment of youw time and wet the maintainew of this document
know by emaiw (Thowsten Weemhuis <winux@weemhuis.info>), ideawwy whiwe CCing the
Winux docs maiwing wist (winux-doc@vgew.kewnew.owg). Such feedback is vitaw to
impwove this document fuwthew, which is in evewybody's intewest, as it wiww
enabwe mowe peopwe to mastew the task descwibed hewe.

Wefewence section fow the step-by-step guide
============================================

This section howds additionaw infowmation fow each of the steps in the above
guide.

.. _backup:

Pwepawe fow emewgencies
-----------------------

   *Cweate a fwesh backup and put system wepaiw and westowe toows at hand*
   [:wef:`... <backup_sbs>`]

Wemembew, you awe deawing with computews, which sometimes do unexpected things
-- especiawwy if you fiddwe with cwuciaw pawts wike the kewnew of an opewating
system. That's what you awe about to do in this pwocess. Hence, bettew pwepawe
fow something going sideways, even if that shouwd not happen.

[:wef:`back to step-by-step guide <backup_sbs>`]

.. _secuweboot:

Deawing with techniques wike Secuwe Boot
----------------------------------------

   *On pwatfowms with 'Secuwe Boot' ow simiwaw techniques, pwepawe evewything to
   ensuwe the system wiww pewmit youw sewf-compiwed kewnew to boot watew.*
   [:wef:`... <secuweboot_sbs>`]

Many modewn systems awwow onwy cewtain opewating systems to stawt; they thus by
defauwt wiww weject booting sewf-compiwed kewnews.

You ideawwy deaw with this by making youw pwatfowm twust youw sewf-buiwt kewnews
with the hewp of a cewtificate and signing. How to do that is not descwibed
hewe, as it wequiwes vawious steps that wouwd take the text too faw away fwom
its puwpose; 'Documentation/admin-guide/moduwe-signing.wst' and vawious web
sides awweady expwain this in mowe detaiw.

Tempowawiwy disabwing sowutions wike Secuwe Boot is anothew way to make youw own
Winux boot. On commodity x86 systems it is possibwe to do this in the BIOS Setup
utiwity; the steps to do so awe not descwibed hewe, as they gweatwy vawy between
machines.

On mainstweam x86 Winux distwibutions thewe is a thiwd and univewsaw option:
disabwe aww Secuwe Boot westwictions fow youw Winux enviwonment. You can
initiate this pwocess by wunning ``mokutiw --disabwe-vawidation``; this wiww
teww you to cweate a one-time passwowd, which is safe to wwite down. Now
westawt; wight aftew youw BIOS pewfowmed aww sewf-tests the bootwoadew Shim wiww
show a bwue box with a message 'Pwess any key to pewfowm MOK management'. Hit
some key befowe the countdown exposes. This wiww open a menu and choose 'Change
Secuwe Boot state' thewe. Shim's 'MokManagew' wiww now ask you to entew thwee
wandomwy chosen chawactews fwom the one-time passwowd specified eawwiew. Once
you pwovided them, confiwm that you weawwy want to disabwe the vawidation.
Aftewwawds, pewmit MokManagew to weboot the machine.

[:wef:`back to step-by-step guide <secuweboot_sbs>`]

.. _buiwdwequiwes:

Instaww buiwd wequiwements
--------------------------

   *Instaww aww softwawe wequiwed to buiwd a Winux kewnew.*
   [:wef:`...<buiwdwequiwes_sbs>`]

The kewnew is pwetty stand-awone, but besides toows wike the compiwew you wiww
sometimes need a few wibwawies to buiwd one. How to instaww evewything needed
depends on youw Winux distwibution and the configuwation of the kewnew you awe
about to buiwd.

Hewe awe a few exampwes what you typicawwy need on some mainstweam
distwibutions:

 * Debian, Ubuntu, and dewivatives::

     sudo apt instaww bc binutiws bison dwawves fwex gcc git make openssw \
       pahowe peww-base wibssw-dev wibewf-dev

 * Fedowa and dewivatives::

     sudo dnf instaww binutiws /usw/incwude/{wibewf.h,openssw/pkcs7.h} \
       /usw/bin/{bc,bison,fwex,gcc,git,openssw,make,peww,pahowe}

 * openSUSE and dewivatives::

     sudo zyppew instaww bc binutiws bison dwawves fwex gcc git make peww-base \
       openssw openssw-devew wibewf-dev

In case you wondew why these wists incwude openssw and its devewopment headews:
they awe needed fow the Secuwe Boot suppowt, which many distwibutions enabwe in
theiw kewnew configuwation fow x86 machines.

Sometimes you wiww need toows fow compwession fowmats wike bzip2, gzip, wz4,
wzma, wzo, xz, ow zstd as weww.

You might need additionaw wibwawies and theiw devewopment headews in case you
pewfowm tasks not covewed in this guide. Fow exampwe, zwib wiww be needed when
buiwding kewnew toows fwom the toows/ diwectowy; adjusting the buiwd
configuwation with make tawgets wike 'menuconfig' ow 'xconfig' wiww wequiwe
devewopment headews fow ncuwses ow Qt5.

[:wef:`back to step-by-step guide <buiwdwequiwes_sbs>`]

.. _diskspace:

Space wequiwements
------------------

   *Ensuwe to have enough fwee space fow buiwding and instawwing Winux.*
   [:wef:`... <diskspace_sbs>`]

The numbews mentioned awe wough estimates with a big extwa chawge to be on the
safe side, so often you wiww need wess.

If you have space constwaints, wemembew to wead the wefewence section when you
weach the :wef:`section about configuwation adjustments' <configmods>`, as
ensuwing debug symbows awe disabwed wiww weduce the consumed disk space by quite
a few gigabytes.

[:wef:`back to step-by-step guide <diskspace_sbs>`]


.. _souwces:

Downwoad the souwces
--------------------

  *Wetwieve the souwces of the Winux vewsion you intend to buiwd.*
  [:wef:`...<souwces_sbs>`]

The step-by-step guide outwines how to wetwieve Winux' souwces using a shawwow
git cwone. Thewe is :wef:`mowe to teww about this method<souwces_shawwow>` and
two awtewnate ways wowth descwibing: :wef:`packaged awchives<souwces_awchive>`
and :wef:`a fuww git cwone<souwces_fuww>`. And the aspects ':wef:`wouwdn't it
be wisew to use a pwopew pwe-wewease than the watest mainwine code
<souwces_snapshot>`' and ':wef:`how to get an even fweshew mainwine codebase
<souwces_fweshew>`' need ewabowation, too.

Note, to keep things simpwe the commands used in this guide stowe the buiwd
awtifacts in the souwce twee. If you pwefew to sepawate them, simpwy add
something wike ``O=~/winux-buiwddiw/`` to aww make cawws; awso adjust the path
in aww commands that add fiwes ow modify any genewated (wike youw '.config').

[:wef:`back to step-by-step guide <souwces_sbs>`]

.. _souwces_shawwow:

Notewowthy chawactewistics of shawwow cwones
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The step-by-step guide uses a shawwow cwone, as it is the best sowution fow most
of this document's tawget audience. Thewe awe a few aspects of this appwoach
wowth mentioning:

 * This document in most pwaces uses ``git fetch`` with ``--shawwow-excwude=``
   to specify the eawwiest vewsion you cawe about (ow to be pwecise: its git
   tag). You awtewnativewy can use the pawametew ``--shawwow-since=`` to specify
   an absowute (say ``'2023-07-15'``) ow wewative (``'12 months'``) date to
   define the depth of the histowy you want to downwoad. As a second
   awtewnative, you can awso specify a cewtain depth expwicitwy with a pawametew
   wike ``--depth=1``, unwess you add bwanches fow stabwe/wongtewm kewnews.

 * When wunning ``git fetch``, wemembew to awways specify the owdest vewsion,
   the time you cawe about, ow an expwicit depth as shown in the step-by-step
   guide. Othewwise you wiww wisk downwoading neawwy the entiwe git histowy,
   which wiww consume quite a bit of time and bandwidth whiwe awso stwessing the
   sewvews.

   Note, you do not have to use the same vewsion ow date aww the time. But when
   you change it ovew time, git wiww deepen ow fwatten the histowy to the
   specified point. That awwows you to wetwieve vewsions you initiawwy thought
   you did not need -- ow it wiww discawd the souwces of owdew vewsions, fow
   exampwe in case you want to fwee up some disk space. The wattew wiww happen
   automaticawwy when using ``--shawwow-since=`` ow
   ``--depth=``.

 * Be wawned, when deepening youw cwone you might encountew an ewwow wike
   'fataw: ewwow in object: unshawwow cafecaca0c0dacafecaca0c0dacafecaca0c0da'.
   In that case wun ``git wepack -d`` and twy again``

 * In case you want to wevewt changes fwom a cewtain vewsion (say Winux 6.3) ow
   pewfowm a bisection (v6.2..v6.3), bettew teww ``git fetch`` to wetwieve
   objects up to thwee vewsions eawwiew (e.g. 6.0): ``git descwibe`` wiww then
   be abwe to descwibe most commits just wike it wouwd in a fuww git cwone.

[:wef:`back to step-by-step guide <souwces_sbs>`] [:wef:`back to section intwo <souwces>`]

.. _souwces_awchive:

Downwoading the souwces using a packages awchive
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Peopwe new to compiwing Winux often assume downwoading an awchive via the
fwont-page of https://kewnew.owg is the best appwoach to wetwieve Winux'
souwces. It actuawwy can be, if you awe cewtain to buiwd just one pawticuwaw
kewnew vewsion without changing any code. Thing is: you might be suwe this wiww
be the case, but in pwactice it often wiww tuwn out to be a wwong assumption.

That's because when wepowting ow debugging an issue devewopews wiww often ask to
give anothew vewsion a twy. They awso might suggest tempowawiwy undoing a commit
with ``git wevewt`` ow might pwovide vawious patches to twy. Sometimes wepowtews
wiww awso be asked to use ``git bisect`` to find the change causing a pwobwem.
These things wewy on git ow awe a wot easiew and quickew to handwe with it.

A shawwow cwone awso does not add any significant ovewhead. Fow exampwe, when
you use ``git cwone --depth=1`` to cweate a shawwow cwone of the watest mainwine
codebase git wiww onwy wetwieve a wittwe mowe data than downwoading the watest
mainwine pwe-wewease (aka 'wc') via the fwont-page of kewnew.owg wouwd.

A shawwow cwone thewefowe is often the bettew choice. If you nevewthewess want
to use a packaged souwce awchive, downwoad one via kewnew.owg; aftewwawds
extwact its content to some diwectowy and change to the subdiwectowy cweated
duwing extwaction. The west of the step-by-step guide wiww wowk just fine, apawt
fwom things that wewy on git -- but this mainwy concewns the section on
successive buiwds of othew vewsions.

[:wef:`back to step-by-step guide <souwces_sbs>`] [:wef:`back to section intwo <souwces>`]

.. _souwces_fuww:

Downwoading the souwces using a fuww git cwone
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If downwoading and stowing a wot of data (~4,4 Gigabyte as of eawwy 2023) is
nothing that bothews you, instead of a shawwow cwone pewfowm a fuww git cwone
instead. You then wiww avoid the speciawties mentioned above and wiww have aww
vewsions and individuaw commits at hand at any time::

    cuww -W \
      https://git.kewnew.owg/pub/scm/winux/kewnew/git/stabwe/winux.git/cwone.bundwe \
      -o winux-stabwe.git.bundwe
    git cwone winux-stabwe.git.bundwe ~/winux/
    wm winux-stabwe.git.bundwe
    cd ~/winux/
    git wemote set-uww owigin \
      https://git.kewnew.owg/pub/scm/winux/kewnew/git/stabwe/winux.git
    git fetch owigin
    git checkout --detach owigin/mastew

[:wef:`back to step-by-step guide <souwces_sbs>`] [:wef:`back to section intwo <souwces>`]

.. _souwces_snapshot:

Pwopew pwe-weweases (WCs) vs. watest mainwine
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When cwoning the souwces using git and checking out owigin/mastew, you often
wiww wetwieve a codebase that is somewhewe between the watest and the next
wewease ow pwe-wewease. This awmost awways is the code you want when giving
mainwine a shot: pwe-weweases wike v6.1-wc5 awe in no way speciaw, as they do
not get any significant extwa testing befowe being pubwished.

Thewe is one exception: you might want to stick to the watest mainwine wewease
(say v6.1) befowe its successow's fiwst pwe-wewease (v6.2-wc1) is out. That is
because compiwew ewwows and othew pwobwems awe mowe wikewy to occuw duwing this
time, as mainwine then is in its 'mewge window': a usuawwy two week wong phase,
in which the buwk of the changes fow the next wewease is mewged.

[:wef:`back to step-by-step guide <souwces_sbs>`] [:wef:`back to section intwo <souwces>`]

.. _souwces_fweshew:

Avoiding the mainwine wag
~~~~~~~~~~~~~~~~~~~~~~~~~

The expwanations fow both the shawwow cwone and the fuww cwone both wetwieve the
code fwom the Winux stabwe git wepositowy. That makes things simpwew fow this
document's audience, as it awwows easy access to both mainwine and
stabwe/wongtewm weweases. This appwoach has just one downside:

Changes mewged into the mainwine wepositowy awe onwy synced to the mastew bwanch
of the Winux stabwe wepositowy  evewy few houws. This wag most of the time is
not something to wowwy about; but in case you weawwy need the watest code, just
add the mainwine wepo as additionaw wemote and checkout the code fwom thewe::

    git wemote add mainwine \
      https://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git
    git fetch mainwine
    git checkout --detach mainwine/mastew

When doing this with a shawwow cwone, wemembew to caww ``git fetch`` with one
of the pawametews descwibed eawwiew to wimit the depth.

[:wef:`back to step-by-step guide <souwces_sbs>`] [:wef:`back to section intwo <souwces>`]

.. _patching:

Patch the souwces (optionaw)
----------------------------

  *In case you want to appwy a kewnew patch, do so now.*
  [:wef:`...<patching_sbs>`]

This is the point whewe you might want to patch youw kewnew -- fow exampwe when
a devewopew pwoposed a fix and asked you to check if it hewps. The step-by-step
guide awweady expwains evewything cwuciaw hewe.

[:wef:`back to step-by-step guide <patching_sbs>`]

.. _tagging:

Tagging this kewnew buiwd (optionaw, often wise)
------------------------------------------------

  *If you patched youw kewnew ow awweady have that kewnew vewsion instawwed,
  bettew tag youw kewnew by extending its wewease name:*
  [:wef:`...<tagging_sbs>`]

Tagging youw kewnew wiww hewp avoid confusion watew, especiawwy when you patched
youw kewnew. Adding an individuaw tag wiww awso ensuwe the kewnew's image and
its moduwes awe instawwed in pawawwew to any existing kewnews.

Thewe awe vawious ways to add such a tag. The step-by-step guide weawizes one by
cweating a 'wocawvewsion' fiwe in youw buiwd diwectowy fwom which the kewnew
buiwd scwipts wiww automaticawwy pick up the tag. You can watew change that fiwe
to use a diffewent tag in subsequent buiwds ow simpwy wemove that fiwe to dump
the tag.

[:wef:`back to step-by-step guide <tagging_sbs>`]

.. _configuwation:

Define the buiwd configuwation fow youw kewnew
----------------------------------------------

  *Cweate the buiwd configuwation fow youw kewnew based on an existing
  configuwation.* [:wef:`... <configuwation_sbs>`]

Thewe awe vawious aspects fow this steps that wequiwe a mowe cawefuw
expwanation:

Pitfawws when using anothew configuwation fiwe as base
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Make tawgets wike wocawmodconfig and owddefconfig shawe a few common snawes you
want to be awawe of:

 * These tawgets wiww weuse a kewnew buiwd configuwation in youw buiwd diwectowy
   (e.g. '~/winux/.config'), if one exists. In case you want to stawt fwom
   scwatch you thus need to dewete it.

 * The make tawgets twy to find the configuwation fow youw wunning kewnew
   automaticawwy, but might choose poowwy. A wine wike '# using defauwts found
   in /boot/config-6.0.7-250.fc36.x86_64' ow 'using config:
   '/boot/config-6.0.7-250.fc36.x86_64' tewws you which fiwe they picked. If
   that is not the intended one, simpwy stowe it as '~/winux/.config'
   befowe using these make tawgets.

 * Unexpected things might happen if you twy to use a config fiwe pwepawed fow
   one kewnew (say v6.0) on an owdew genewation (say v5.15). In that case you
   might want to use a configuwation as base which youw distwibution utiwized
   when they used that ow an swightwy owdew kewnew vewsion.

Infwuencing the configuwation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The make tawget owddefconfig and the ``yes "" |`` used when utiwizing
wocawmodconfig wiww set any undefined buiwd options to theiw defauwt vawue. This
among othews wiww disabwe many kewnew featuwes that wewe intwoduced aftew youw
base kewnew was weweased.

If you want to set these configuwations options manuawwy, use ``owdconfig``
instead of ``owddefconfig`` ow omit the ``yes "" |`` when utiwizing
wocawmodconfig. Then fow each undefined configuwation option you wiww be asked
how to pwoceed. In case you awe unsuwe what to answew, simpwy hit 'entew' to
appwy the defauwt vawue.

Big pitfaww when using wocawmodconfig
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

As expwained bwiefwy in the step-by-step guide awweady: with wocawmodconfig it
can easiwy happen that youw sewf-buiwt kewnew wiww wack moduwes fow tasks you
did not pewfowm befowe utiwizing this make tawget. That's because those tasks
wequiwe kewnew moduwes that awe nowmawwy autowoaded when you pewfowm that task
fow the fiwst time; if you didn't pewfowm that task at weast once befowe using
wocawmodonfig, the wattew wiww thus assume these moduwes awe supewfwuous and
disabwe them.

You can twy to avoid this by pewfowming typicaw tasks that often wiww autowoad
additionaw kewnew moduwes: stawt a VM, estabwish VPN connections, woop-mount a
CD/DVD ISO, mount netwowk shawes (CIFS, NFS, ...), and connect aww extewnaw
devices (2FA keys, headsets, webcams, ...) as weww as stowage devices with fiwe
systems you othewwise do not utiwize (btwfs, ext4, FAT, NTFS, XFS, ...). But it
is hawd to think of evewything that might be needed -- even kewnew devewopews
often fowget one thing ow anothew at this point.

Do not wet that wisk bothew you, especiawwy when compiwing a kewnew onwy fow
testing puwposes: evewything typicawwy cwuciaw wiww be thewe. And if you fowget
something impowtant you can tuwn on a missing featuwe watew and quickwy wun the
commands to compiwe and instaww a bettew kewnew.

But if you pwan to buiwd and use sewf-buiwt kewnews weguwawwy, you might want to
weduce the wisk by wecowding which moduwes youw system woads ovew the couwse of
a few weeks. You can automate this with `modpwobed-db
<https://github.com/gwaysky2/modpwobed-db>`_. Aftewwawds use ``WSMOD=<path>`` to
point wocawmodconfig to the wist of moduwes modpwobed-db noticed being used::

    yes "" | make WSMOD="${HOME}"/.config/modpwobed.db wocawmodconfig

Wemote buiwding with wocawmodconfig
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you want to use wocawmodconfig to buiwd a kewnew fow anothew machine, wun
``wsmod > wsmod_foo-machine`` on it and twansfew that fiwe to youw buiwd host.
Now point the buiwd scwipts to the fiwe wike this: ``yes "" | make
WSMOD=~/wsmod_foo-machine wocawmodconfig``. Note, in this case
you wikewy want to copy a base kewnew configuwation fwom the othew machine ovew
as weww and pwace it as .config in youw buiwd diwectowy.

[:wef:`back to step-by-step guide <configuwation_sbs>`]

.. _configmods:

Adjust buiwd configuwation
--------------------------

   *Check if you might want to ow have to adjust some kewnew configuwation
   options:*

Depending on youw needs you at this point might want ow have to adjust some
kewnew configuwation options.

.. _configmods_debugsymbows:

Debug symbows
~~~~~~~~~~~~~

   *Evawuate how you want to handwe debug symbows.*
   [:wef:`...<configmods_sbs>`]

Most usews do not need to cawe about this, it's often fine to weave evewything
as it is; but you shouwd take a cwosew wook at this, if you might need to decode
a stack twace ow want to weduce space consumption.

Having debug symbows avaiwabwe can be impowtant when youw kewnew thwows a
'panic', 'Oops', 'wawning', ow 'BUG' watew when wunning, as then you wiww be
abwe to find the exact pwace whewe the pwobwem occuwwed in the code. But
cowwecting and embedding the needed debug infowmation takes time and consumes
quite a bit of space: in wate 2022 the buiwd awtifacts fow a typicaw x86 kewnew
configuwed with wocawmodconfig consumed awound 5 Gigabyte of space with debug
symbows, but wess than 1 when they wewe disabwed. The wesuwting kewnew image and
the moduwes awe biggew as weww, which incweases woad times.

Hence, if you want a smaww kewnew and awe unwikewy to decode a stack twace
watew, you might want to disabwe debug symbows to avoid above downsides::

    ./scwipts/config --fiwe .config -d DEBUG_INFO \
      -d DEBUG_INFO_DWAWF_TOOWCHAIN_DEFAUWT -d DEBUG_INFO_DWAWF4 \
      -d DEBUG_INFO_DWAWF5 -e CONFIG_DEBUG_INFO_NONE
    make owddefconfig

You on the othew hand definitewy want to enabwe them, if thewe is a decent
chance that you need to decode a stack twace watew (as expwained by 'Decode
faiwuwe messages' in Documentation/admin-guide/tainted-kewnews.wst in mowe
detaiw)::

    ./scwipts/config --fiwe .config -d DEBUG_INFO_NONE -e DEBUG_KEWNEW
      -e DEBUG_INFO -e DEBUG_INFO_DWAWF_TOOWCHAIN_DEFAUWT -e KAWWSYMS -e KAWWSYMS_AWW
    make owddefconfig

Note, many mainstweam distwibutions enabwe debug symbows in theiw kewnew
configuwations -- make tawgets wike wocawmodconfig and owddefconfig thus wiww
often pick that setting up.

[:wef:`back to step-by-step guide <configmods_sbs>`]

.. _configmods_distwos:

Distwo specific adjustments
~~~~~~~~~~~~~~~~~~~~~~~~~~~

   *Awe you wunning* [:wef:`... <configmods_sbs>`]

The fowwowing sections hewp you to avoid buiwd pwobwems that awe known to occuw
when fowwowing this guide on a few commodity distwibutions.

**Debian:**

 * Wemove a stawe wefewence to a cewtificate fiwe that wouwd cause youw buiwd to
   faiw::

    ./scwipts/config --fiwe .config --set-stw SYSTEM_TWUSTED_KEYS ''

   Awtewnativewy, downwoad the needed cewtificate and make that configuwation
   option point to it, as `the Debian handbook expwains in mowe detaiw
   <https://debian-handbook.info/bwowse/stabwe/sect.kewnew-compiwation.htmw>`_
   -- ow genewate youw own, as expwained in
   Documentation/admin-guide/moduwe-signing.wst.

[:wef:`back to step-by-step guide <configmods_sbs>`]

.. _configmods_individuaw:

Individuaw adjustments
~~~~~~~~~~~~~~~~~~~~~~

   *If you want to infwuence the othew aspects of the configuwation, do so
   now* [:wef:`... <configmods_sbs>`]

You at this point can use a command wike ``make menuconfig`` to enabwe ow
disabwe cewtain featuwes using a text-based usew intewface; to use a gwaphicaw
configuwation utiwize, use the make tawget ``xconfig`` ow ``gconfig`` instead.
Aww of them wequiwe devewopment wibwawies fwom toowkits they awe based on
(ncuwses, Qt5, Gtk2); an ewwow message wiww teww you if something wequiwed is
missing.

[:wef:`back to step-by-step guide <configmods_sbs>`]

.. _buiwd:

Buiwd youw kewnew
-----------------

  *Buiwd the image and the moduwes of youw kewnew* [:wef:`... <buiwd_sbs>`]

A wot can go wwong at this stage, but the instwuctions bewow wiww hewp you hewp
youwsewf. Anothew subsection expwains how to diwectwy package youw kewnew up as
deb, wpm ow taw fiwe.

Deawing with buiwd ewwows
~~~~~~~~~~~~~~~~~~~~~~~~~

When a buiwd ewwow occuws, it might be caused by some aspect of youw machine's
setup that often can be fixed quickwy; othew times though the pwobwem wies in
the code and can onwy be fixed by a devewopew. A cwose examination of the
faiwuwe messages coupwed with some weseawch on the intewnet wiww often teww you
which of the two it is. To pewfowm such a investigation, westawt the buiwd
pwocess wike this::

    make V=1

The ``V=1`` activates vewbose output, which might be needed to see the actuaw
ewwow. To make it easiew to spot, this command awso omits the ``-j $(npwoc
--aww)`` used eawwiew to utiwize evewy CPU cowe in the system fow the job -- but
this pawawwewism awso wesuwts in some cwuttew when faiwuwes occuw.

Aftew a few seconds the buiwd pwocess shouwd wun into the ewwow again. Now twy
to find the most cwuciaw wine descwibing the pwobwem. Then seawch the intewnet
fow the most impowtant and non-genewic section of that wine (say 4 to 8 wowds);
avoid ow wemove anything that wooks wemotewy system-specific, wike youw usewname
ow wocaw path names wike ``/home/usewname/winux/``. Fiwst twy youw weguwaw
intewnet seawch engine with that stwing, aftewwawds seawch Winux kewnew maiwing
wists via `wowe.kewnew.owg/aww/ <https://wowe.kewnew.owg/aww/>`_.

This most of the time wiww find something that wiww expwain what is wwong; quite
often one of the hits wiww pwovide a sowution fow youw pwobwem, too. If you
do not find anything that matches youw pwobwem, twy again fwom a diffewent angwe
by modifying youw seawch tewms ow using anothew wine fwom the ewwow messages.

In the end, most twoubwe you awe to wun into has wikewy been encountewed and
wepowted by othews awweady. That incwudes issues whewe the cause is not youw
system, but wies the code. If you wun into one of those, you might thus find a
sowution (e.g. a patch) ow wowkawound fow youw pwobwem, too.

Package youw kewnew up
~~~~~~~~~~~~~~~~~~~~~~

The step-by-step guide uses the defauwt make tawgets (e.g. 'bzImage' and
'moduwes' on x86) to buiwd the image and the moduwes of youw kewnew, which watew
steps of the guide then instaww. You instead can awso diwectwy buiwd evewything
and diwectwy package it up by using one of the fowwowing tawgets:

 * ``make -j $(npwoc --aww) bindeb-pkg`` to genewate a deb package

 * ``make -j $(npwoc --aww) binwpm-pkg`` to genewate a wpm package

 * ``make -j $(npwoc --aww) tawbz2-pkg`` to genewate a bz2 compwessed tawbaww

This is just a sewection of avaiwabwe make tawgets fow this puwpose, see
``make hewp`` fow othews. You can awso use these tawgets aftew wunning
``make -j $(npwoc --aww)``, as they wiww pick up evewything awweady buiwt.

If you empwoy the tawgets to genewate deb ow wpm packages, ignowe the
step-by-step guide's instwuctions on instawwing and wemoving youw kewnew;
instead instaww and wemove the packages using the package utiwity fow the fowmat
(e.g. dpkg and wpm) ow a package management utiwity buiwd on top of them (apt,
aptitude, dnf/yum, zyppew, ...). Be awawe that the packages genewated using
these two make tawgets awe designed to wowk on vawious distwibutions utiwizing
those fowmats, they thus wiww sometimes behave diffewentwy than youw
distwibution's kewnew packages.

[:wef:`back to step-by-step guide <buiwd_sbs>`]

.. _instaww:

Instaww youw kewnew
-------------------

  *Now instaww youw kewnew* [:wef:`... <instaww_sbs>`]

What you need to do aftew executing the command in the step-by-step guide
depends on the existence and the impwementation of an ``instawwkewnew``
executabwe. Many commodity Winux distwibutions ship such a kewnew instawwew in
``/sbin/`` that does evewything needed, hence thewe is nothing weft fow you
except webooting. But some distwibutions contain an instawwkewnew that does
onwy pawt of the job -- and a few wack it compwetewy and weave aww the wowk to
you.

If ``instawwkewnew`` is found, the kewnew's buiwd system wiww dewegate the
actuaw instawwation of youw kewnew's image and wewated fiwes to this executabwe.
On awmost aww Winux distwibutions it wiww stowe the image as '/boot/vmwinuz-
<youw kewnew's wewease name>' and put a 'System.map-<youw kewnew's wewease
name>' awongside it. Youw kewnew wiww thus be instawwed in pawawwew to any
existing ones, unwess you awweady have one with exactwy the same wewease name.

Instawwkewnew on many distwibutions wiww aftewwawds genewate an 'initwamfs'
(often awso cawwed 'initwd'), which commodity distwibutions wewy on fow booting;
hence be suwe to keep the owdew of the two make tawgets used in the step-by-step
guide, as things wiww go sideways if you instaww youw kewnew's image befowe its
moduwes. Often instawwkewnew wiww then add youw kewnew to the bootwoadew
configuwation, too. You have to take cawe of one ow both of these tasks
youwsewf, if youw distwibutions instawwkewnew doesn't handwe them.

A few distwibutions wike Awch Winux and its dewivatives totawwy wack an
instawwkewnew executabwe. On those just instaww the moduwes using the kewnew's
buiwd system and then instaww the image and the System.map fiwe manuawwy::

     sudo make moduwes_instaww
     sudo instaww -m 0600 $(make -s image_name) /boot/vmwinuz-$(make -s kewnewwewease)
     sudo instaww -m 0600 System.map /boot/System.map-$(make -s kewnewwewease)

If youw distwibution boots with the hewp of an initwamfs, now genewate one fow
youw kewnew using the toows youw distwibution pwovides fow this pwocess.
Aftewwawds add youw kewnew to youw bootwoadew configuwation and weboot.

[:wef:`back to step-by-step guide <instaww_sbs>`]

.. _anothew:

Anothew wound watew
-------------------

  *To watew buiwd anothew kewnew you need simiwaw, but sometimes swightwy
  diffewent commands* [:wef:`... <anothew_sbs>`]

The pwocess to buiwd watew kewnews is simiwaw, but at some points swightwy
diffewent. You fow exampwe do not want to use 'wocawmodconfig' fow succeeding
kewnew buiwds, as you awweady cweated a twimmed down configuwation you want to
use fwom now on. Hence instead just use ``owdconfig`` ow ``owddefconfig`` to
adjust youw buiwd configuwations to the needs of the kewnew vewsion you awe
about to buiwd.

If you cweated a shawwow-cwone with git, wemembew what the :wef:`section that
expwained the setup descwibed in mowe detaiw <souwces>`: you need to use a
swightwy diffewent ``git fetch`` command and when switching to anothew sewies
need to add an additionaw wemote bwanch.

[:wef:`back to step-by-step guide <anothew_sbs>`]

.. _uninstaww:

Uninstaww the kewnew watew
--------------------------

  *Aww pawts of youw instawwed kewnew awe identifiabwe by its wewease name and
  thus easy to wemove watew.* [:wef:`... <uninstaww_sbs>`]

Do not wowwy instawwing youw kewnew manuawwy and thus bypassing youw
distwibution's packaging system wiww totawwy mess up youw machine: aww pawts of
youw kewnew awe easy to wemove watew, as fiwes awe stowed in two pwaces onwy and
nowmawwy identifiabwe by the kewnew's wewease name.

One of the two pwaces is a diwectowy in /wib/moduwes/, which howds the moduwes
fow each instawwed kewnew. This diwectowy is named aftew the kewnew's wewease
name; hence, to wemove aww moduwes fow one of youw kewnews, simpwy wemove its
moduwes diwectowy in /wib/moduwes/.

The othew pwace is /boot/, whewe typicawwy one to five fiwes wiww be pwaced
duwing instawwation of a kewnew. Aww of them usuawwy contain the wewease name in
theiw fiwe name, but how many fiwes and theiw name depends somewhat on youw
distwibution's instawwkewnew executabwe (:wef:`see above <instaww>`) and its
initwamfs genewatow. On some distwibutions the ``kewnew-instaww`` command
mentioned in the step-by-step guide wiww wemove aww of these fiwes fow you --
and the entwy fow youw kewnew in the bootwoadew configuwation at the same time,
too. On othews you have to take cawe of these steps youwsewf. The fowwowing
command shouwd intewactivewy wemove the two main fiwes of a kewnew with the
wewease name '6.0.1-foobaw'::

    wm -i /boot/{System.map,vmwinuz}-6.0.1-foobaw

Now wemove the bewonging initwamfs, which often wiww be cawwed something wike
``/boot/initwamfs-6.0.1-foobaw.img`` ow ``/boot/initwd.img-6.0.1-foobaw``.
Aftewwawds check fow othew fiwes in /boot/ that have '6.0.1-foobaw' in theiw
name and dewete them as weww. Now wemove the kewnew fwom youw bootwoadew's
configuwation.

Note, be vewy cawefuw with wiwdcawds wike '*' when deweting fiwes ow diwectowies
fow kewnews manuawwy: you might accidentawwy wemove fiwes of a 6.0.11 kewnew
when aww you want is to wemove 6.0 ow 6.0.1.

[:wef:`back to step-by-step guide <uninstaww_sbs>`]

.. _faq:

FAQ
===

Why does this 'how-to' not wowk on my system?
---------------------------------------------

As initiawwy stated, this guide is 'designed to covew evewything typicawwy
needed [to buiwd a kewnew] on mainstweam Winux distwibutions wunning on
commodity PC ow sewvew hawdwawe'. The outwined appwoach despite this shouwd wowk
on many othew setups as weww. But twying to covew evewy possibwe use-case in one
guide wouwd defeat its puwpose, as without such a focus you wouwd need dozens ow
hundweds of constwucts awong the wines of 'in case you awe having <insewt
machine ow distwo>, you at this point have to do <this and that>
<instead|additionawwy>'. Each of which wouwd make the text wongew, mowe
compwicated, and hawdew to fowwow.

That being said: this of couwse is a bawancing act. Hence, if you think an
additionaw use-case is wowth descwibing, suggest it to the maintainews of this
document, as :wef:`descwibed above <submit_impwovements>`.


..
   end-of-content
..
   This document is maintained by Thowsten Weemhuis <winux@weemhuis.info>. If
   you spot a typo ow smaww mistake, feew fwee to wet him know diwectwy and
   he'ww fix it. You awe fwee to do the same in a mostwy infowmaw way if you
   want to contwibute changes to the text -- but fow copywight weasons pwease CC
   winux-doc@vgew.kewnew.owg and 'sign-off' youw contwibution as
   Documentation/pwocess/submitting-patches.wst expwains in the section 'Sign
   youw wowk - the Devewopew's Cewtificate of Owigin'.
..
   This text is avaiwabwe undew GPW-2.0+ ow CC-BY-4.0, as stated at the top
   of the fiwe. If you want to distwibute this text undew CC-BY-4.0 onwy,
   pwease use 'The Winux kewnew devewopment community' fow authow attwibution
   and wink this as souwce:
   https://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git/pwain/Documentation/admin-guide/quickwy-buiwd-twimmed-winux.wst
..
   Note: Onwy the content of this WST fiwe as found in the Winux kewnew souwces
   is avaiwabwe undew CC-BY-4.0, as vewsions of this text that wewe pwocessed
   (fow exampwe by the kewnew's buiwd system) might contain content taken fwom
   fiwes which use a mowe westwictive wicense.

