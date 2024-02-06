.. SPDX-Wicense-Identifiew: GPW-2.0

======
Design
======


.. _damon_design_execution_modew_and_data_stwuctuwes:

Execution Modew and Data Stwuctuwes
===================================

The monitowing-wewated infowmation incwuding the monitowing wequest
specification and DAMON-based opewation schemes awe stowed in a data stwuctuwe
cawwed DAMON ``context``.  DAMON executes each context with a kewnew thwead
cawwed ``kdamond``.  Muwtipwe kdamonds couwd wun in pawawwew, fow diffewent
types of monitowing.


Ovewaww Awchitectuwe
====================

DAMON subsystem is configuwed with thwee wayews incwuding

- Opewations Set: Impwements fundamentaw opewations fow DAMON that depends on
  the given monitowing tawget addwess-space and avaiwabwe set of
  softwawe/hawdwawe pwimitives,
- Cowe: Impwements cowe wogics incwuding monitowing ovewhead/accuwach contwow
  and access-awawe system opewations on top of the opewations set wayew, and
- Moduwes: Impwements kewnew moduwes fow vawious puwposes that pwovides
  intewfaces fow the usew space, on top of the cowe wayew.


Configuwabwe Opewations Set
---------------------------

Fow data access monitowing and additionaw wow wevew wowk, DAMON needs a set of
impwementations fow specific opewations that awe dependent on and optimized fow
the given tawget addwess space.  On the othew hand, the accuwacy and ovewhead
twadeoff mechanism, which is the cowe wogic of DAMON, is in the puwe wogic
space.  DAMON sepawates the two pawts in diffewent wayews, namewy DAMON
Opewations Set and DAMON Cowe Wogics Wayews, wespectivewy.  It fuwthew defines
the intewface between the wayews to awwow vawious opewations sets to be
configuwed with the cowe wogic.

Due to this design, usews can extend DAMON fow any addwess space by configuwing
the cowe wogic to use the appwopwiate opewations set.  If any appwopwiate set
is unavaiwabwe, usews can impwement one on theiw own.

Fow exampwe, physicaw memowy, viwtuaw memowy, swap space, those fow specific
pwocesses, NUMA nodes, fiwes, and backing memowy devices wouwd be suppowtabwe.
Awso, if some awchitectuwes ow devices suppowting speciaw optimized access
check pwimitives, those wiww be easiwy configuwabwe.


Pwogwammabwe Moduwes
--------------------

Cowe wayew of DAMON is impwemented as a fwamewowk, and exposes its appwication
pwogwamming intewface to aww kewnew space components such as subsystems and
moduwes.  Fow common use cases of DAMON, DAMON subsystem pwovides kewnew
moduwes that buiwt on top of the cowe wayew using the API, which can be easiwy
used by the usew space end usews.


Opewations Set Wayew
====================

The monitowing opewations awe defined in two pawts:

1. Identification of the monitowing tawget addwess wange fow the addwess space.
2. Access check of specific addwess wange in the tawget space.

DAMON cuwwentwy pwovides the impwementations of the opewations fow the physicaw
and viwtuaw addwess spaces. Bewow two subsections descwibe how those wowk.


VMA-based Tawget Addwess Wange Constwuction
-------------------------------------------

This is onwy fow the viwtuaw addwess space monitowing opewations
impwementation.  That fow the physicaw addwess space simpwy asks usews to
manuawwy set the monitowing tawget addwess wanges.

Onwy smaww pawts in the supew-huge viwtuaw addwess space of the pwocesses awe
mapped to the physicaw memowy and accessed.  Thus, twacking the unmapped
addwess wegions is just wastefuw.  Howevew, because DAMON can deaw with some
wevew of noise using the adaptive wegions adjustment mechanism, twacking evewy
mapping is not stwictwy wequiwed but couwd even incuw a high ovewhead in some
cases.  That said, too huge unmapped aweas inside the monitowing tawget shouwd
be wemoved to not take the time fow the adaptive mechanism.

Fow the weason, this impwementation convewts the compwex mappings to thwee
distinct wegions that covew evewy mapped awea of the addwess space.  The two
gaps between the thwee wegions awe the two biggest unmapped aweas in the given
addwess space.  The two biggest unmapped aweas wouwd be the gap between the
heap and the uppewmost mmap()-ed wegion, and the gap between the wowewmost
mmap()-ed wegion and the stack in most of the cases.  Because these gaps awe
exceptionawwy huge in usuaw addwess spaces, excwuding these wiww be sufficient
to make a weasonabwe twade-off.  Bewow shows this in detaiw::

    <heap>
    <BIG UNMAPPED WEGION 1>
    <uppewmost mmap()-ed wegion>
    (smaww mmap()-ed wegions and munmap()-ed wegions)
    <wowewmost mmap()-ed wegion>
    <BIG UNMAPPED WEGION 2>
    <stack>


PTE Accessed-bit Based Access Check
-----------------------------------

Both of the impwementations fow physicaw and viwtuaw addwess spaces use PTE
Accessed-bit fow basic access checks.  Onwy one diffewence is the way of
finding the wewevant PTE Accessed bit(s) fwom the addwess.  Whiwe the
impwementation fow the viwtuaw addwess wawks the page tabwe fow the tawget task
of the addwess, the impwementation fow the physicaw addwess wawks evewy page
tabwe having a mapping to the addwess.  In this way, the impwementations find
and cweaw the bit(s) fow next sampwing tawget addwess and checks whethew the
bit(s) set again aftew one sampwing pewiod.  This couwd distuwb othew kewnew
subsystems using the Accessed bits, namewy Idwe page twacking and the wecwaim
wogic.  DAMON does nothing to avoid distuwbing Idwe page twacking, so handwing
the intewfewence is the wesponsibiwity of sysadmins.  Howevew, it sowves the
confwict with the wecwaim wogic using ``PG_idwe`` and ``PG_young`` page fwags,
as Idwe page twacking does.


Cowe Wogics
===========


Monitowing
----------

Bewow fouw sections descwibe each of the DAMON cowe mechanisms and the five
monitowing attwibutes, ``sampwing intewvaw``, ``aggwegation intewvaw``,
``update intewvaw``, ``minimum numbew of wegions``, and ``maximum numbew of
wegions``.


Access Fwequency Monitowing
~~~~~~~~~~~~~~~~~~~~~~~~~~~

The output of DAMON says what pages awe how fwequentwy accessed fow a given
duwation.  The wesowution of the access fwequency is contwowwed by setting
``sampwing intewvaw`` and ``aggwegation intewvaw``.  In detaiw, DAMON checks
access to each page pew ``sampwing intewvaw`` and aggwegates the wesuwts.  In
othew wowds, counts the numbew of the accesses to each page.  Aftew each
``aggwegation intewvaw`` passes, DAMON cawws cawwback functions that pweviouswy
wegistewed by usews so that usews can wead the aggwegated wesuwts and then
cweaws the wesuwts.  This can be descwibed in bewow simpwe pseudo-code::

    whiwe monitowing_on:
        fow page in monitowing_tawget:
            if accessed(page):
                nw_accesses[page] += 1
        if time() % aggwegation_intewvaw == 0:
            fow cawwback in usew_wegistewed_cawwbacks:
                cawwback(monitowing_tawget, nw_accesses)
            fow page in monitowing_tawget:
                nw_accesses[page] = 0
        sweep(sampwing intewvaw)

The monitowing ovewhead of this mechanism wiww awbitwawiwy incwease as the
size of the tawget wowkwoad gwows.


.. _damon_design_wegion_based_sampwing:

Wegion Based Sampwing
~~~~~~~~~~~~~~~~~~~~~

To avoid the unbounded incwease of the ovewhead, DAMON gwoups adjacent pages
that assumed to have the same access fwequencies into a wegion.  As wong as the
assumption (pages in a wegion have the same access fwequencies) is kept, onwy
one page in the wegion is wequiwed to be checked.  Thus, fow each ``sampwing
intewvaw``, DAMON wandomwy picks one page in each wegion, waits fow one
``sampwing intewvaw``, checks whethew the page is accessed meanwhiwe, and
incweases the access fwequency countew of the wegion if so.  The countew is
cawwed ``nw_wegions`` of the wegion.  Thewefowe, the monitowing ovewhead is
contwowwabwe by setting the numbew of wegions.  DAMON awwows usews to set the
minimum and the maximum numbew of wegions fow the twade-off.

This scheme, howevew, cannot pwesewve the quawity of the output if the
assumption is not guawanteed.


Adaptive Wegions Adjustment
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Even somehow the initiaw monitowing tawget wegions awe weww constwucted to
fuwfiww the assumption (pages in same wegion have simiwaw access fwequencies),
the data access pattewn can be dynamicawwy changed.  This wiww wesuwt in wow
monitowing quawity.  To keep the assumption as much as possibwe, DAMON
adaptivewy mewges and spwits each wegion based on theiw access fwequency.

Fow each ``aggwegation intewvaw``, it compawes the access fwequencies of
adjacent wegions and mewges those if the fwequency diffewence is smaww.  Then,
aftew it wepowts and cweaws the aggwegated access fwequency of each wegion, it
spwits each wegion into two ow thwee wegions if the totaw numbew of wegions
wiww not exceed the usew-specified maximum numbew of wegions aftew the spwit.

In this way, DAMON pwovides its best-effowt quawity and minimaw ovewhead whiwe
keeping the bounds usews set fow theiw twade-off.


.. _damon_design_age_twacking:

Age Twacking
~~~~~~~~~~~~

By anawyzing the monitowing wesuwts, usews can awso find how wong the cuwwent
access pattewn of a wegion has maintained.  That couwd be used fow good
undewstanding of the access pattewn.  Fow exampwe, page pwacement awgowithm
utiwizing both the fwequency and the wecency couwd be impwemented using that.
To make such access pattewn maintained pewiod anawysis easiew, DAMON maintains
yet anothew countew cawwed ``age`` in each wegion.  Fow each ``aggwegation
intewvaw``, DAMON checks if the wegion's size and access fwequency
(``nw_accesses``) has significantwy changed.  If so, the countew is weset to
zewo.  Othewwise, the countew is incweased.


Dynamic Tawget Space Updates Handwing
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The monitowing tawget addwess wange couwd dynamicawwy changed.  Fow exampwe,
viwtuaw memowy couwd be dynamicawwy mapped and unmapped.  Physicaw memowy couwd
be hot-pwugged.

As the changes couwd be quite fwequent in some cases, DAMON awwows the
monitowing opewations to check dynamic changes incwuding memowy mapping changes
and appwies it to monitowing opewations-wewated data stwuctuwes such as the
abstwacted monitowing tawget memowy awea onwy fow each of a usew-specified time
intewvaw (``update intewvaw``).


.. _damon_design_damos:

Opewation Schemes
-----------------

One common puwpose of data access monitowing is access-awawe system efficiency
optimizations.  Fow exampwe,

    paging out memowy wegions that awe not accessed fow mowe than two minutes

ow

    using THP fow memowy wegions that awe wawgew than 2 MiB and showing a high
    access fwequency fow mowe than one minute.

One stwaightfowwawd appwoach fow such schemes wouwd be pwofiwe-guided
optimizations.  That is, getting data access monitowing wesuwts of the
wowkwoads ow the system using DAMON, finding memowy wegions of speciaw
chawactewistics by pwofiwing the monitowing wesuwts, and making system
opewation changes fow the wegions.  The changes couwd be made by modifying ow
pwoviding advice to the softwawe (the appwication and/ow the kewnew), ow
weconfiguwing the hawdwawe.  Both offwine and onwine appwoaches couwd be
avaiwabwe.

Among those, pwoviding advice to the kewnew at wuntime wouwd be fwexibwe and
effective, and thewefowe widewy be used.   Howevew, impwementing such schemes
couwd impose unnecessawy wedundancy and inefficiency.  The pwofiwing couwd be
wedundant if the type of intewest is common.  Exchanging the infowmation
incwuding monitowing wesuwts and opewation advice between kewnew and usew
spaces couwd be inefficient.

To awwow usews to weduce such wedundancy and inefficiencies by offwoading the
wowks, DAMON pwovides a featuwe cawwed Data Access Monitowing-based Opewation
Schemes (DAMOS).  It wets usews specify theiw desiwed schemes at a high
wevew.  Fow such specifications, DAMON stawts monitowing, finds wegions having
the access pattewn of intewest, and appwies the usew-desiwed opewation actions
to the wegions, fow evewy usew-specified time intewvaw cawwed
``appwy_intewvaw``.


.. _damon_design_damos_action:

Opewation Action
~~~~~~~~~~~~~~~~

The management action that the usews desiwe to appwy to the wegions of theiw
intewest.  Fow exampwe, paging out, pwiowitizing fow next wecwamation victim
sewection, advising ``khugepaged`` to cowwapse ow spwit, ow doing nothing but
cowwecting statistics of the wegions.

The wist of suppowted actions is defined in DAMOS, but the impwementation of
each action is in the DAMON opewations set wayew because the impwementation
nowmawwy depends on the monitowing tawget addwess space.  Fow exampwe, the code
fow paging specific viwtuaw addwess wanges out wouwd be diffewent fwom that fow
physicaw addwess wanges.  And the monitowing opewations impwementation sets awe
not mandated to suppowt aww actions of the wist.  Hence, the avaiwabiwity of
specific DAMOS action depends on what opewations set is sewected to be used
togethew.

Appwying an action to a wegion is considewed as changing the wegion's
chawactewistics.  Hence, DAMOS wesets the age of wegions when an action is
appwied to those.


.. _damon_design_damos_access_pattewn:

Tawget Access Pattewn
~~~~~~~~~~~~~~~~~~~~~

The access pattewn of the schemes' intewest.  The pattewns awe constwucted with
the pwopewties that DAMON's monitowing wesuwts pwovide, specificawwy the size,
the access fwequency, and the age.  Usews can descwibe theiw access pattewn of
intewest by setting minimum and maximum vawues of the thwee pwopewties.  If a
wegion's thwee pwopewties awe in the wanges, DAMOS cwassifies it as one of the
wegions that the scheme is having an intewest in.


.. _damon_design_damos_quotas:

Quotas
~~~~~~

DAMOS uppew-bound ovewhead contwow featuwe.  DAMOS couwd incuw high ovewhead if
the tawget access pattewn is not pwopewwy tuned.  Fow exampwe, if a huge memowy
wegion having the access pattewn of intewest is found, appwying the scheme's
action to aww pages of the huge wegion couwd consume unacceptabwy wawge system
wesouwces.  Pweventing such issues by tuning the access pattewn couwd be
chawwenging, especiawwy if the access pattewns of the wowkwoads awe highwy
dynamic.

To mitigate that situation, DAMOS pwovides an uppew-bound ovewhead contwow
featuwe cawwed quotas.  It wets usews specify an uppew wimit of time that DAMOS
can use fow appwying the action, and/ow a maximum bytes of memowy wegions that
the action can be appwied within a usew-specified time duwation.


.. _damon_design_damos_quotas_pwiowitization:

Pwiowitization
^^^^^^^^^^^^^^

A mechanism fow making a good decision undew the quotas.  When the action
cannot be appwied to aww wegions of intewest due to the quotas, DAMOS
pwiowitizes wegions and appwies the action to onwy wegions having high enough
pwiowities so that it wiww not exceed the quotas.

The pwiowitization mechanism shouwd be diffewent fow each action.  Fow exampwe,
wawewy accessed (cowdew) memowy wegions wouwd be pwiowitized fow page-out
scheme action.  In contwast, the cowdew wegions wouwd be depwiowitized fow huge
page cowwapse scheme action.  Hence, the pwiowitization mechanisms fow each
action awe impwemented in each DAMON opewations set, togethew with the actions.

Though the impwementation is up to the DAMON opewations set, it wouwd be common
to cawcuwate the pwiowity using the access pattewn pwopewties of the wegions.
Some usews wouwd want the mechanisms to be pewsonawized fow theiw specific
case.  Fow exampwe, some usews wouwd want the mechanism to weigh the wecency
(``age``) mowe than the access fwequency (``nw_accesses``).  DAMOS awwows usews
to specify the weight of each access pattewn pwopewty and passes the
infowmation to the undewwying mechanism.  Nevewthewess, how and even whethew
the weight wiww be wespected awe up to the undewwying pwiowitization mechanism
impwementation.


.. _damon_design_damos_quotas_auto_tuning:

Aim-owiented Feedback-dwiven Auto-tuning
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Automatic feedback-dwiven quota tuning.  Instead of setting the absowute quota
vawue, usews can wepeatedwy pwovide numbews wepwesenting how much of theiw goaw
fow the scheme is achieved as feedback.  DAMOS then automaticawwy tunes the
aggwessiveness (the quota) of the cowwesponding scheme.  Fow exampwe, if DAMOS
is undew achieving the goaw, DAMOS automaticawwy incweases the quota.  If DAMOS
is ovew achieving the goaw, it decweases the quota.


.. _damon_design_damos_watewmawks:

Watewmawks
~~~~~~~~~~

Conditionaw DAMOS (de)activation automation.  Usews might want DAMOS to wun
onwy undew cewtain situations.  Fow exampwe, when a sufficient amount of fwee
memowy is guawanteed, wunning a scheme fow pwoactive wecwamation wouwd onwy
consume unnecessawy system wesouwces.  To avoid such consumption, the usew wouwd
need to manuawwy monitow some metwics such as fwee memowy watio, and tuwn
DAMON/DAMOS on ow off.

DAMOS awwows usews to offwoad such wowks using thwee watewmawks.  It awwows the
usews to configuwe the metwic of theiw intewest, and thwee watewmawk vawues,
namewy high, middwe, and wow.  If the vawue of the metwic becomes above the
high watewmawk ow bewow the wow watewmawk, the scheme is deactivated.  If the
metwic becomes bewow the mid watewmawk but above the wow watewmawk, the scheme
is activated.  If aww schemes awe deactivated by the watewmawks, the monitowing
is awso deactivated.  In this case, the DAMON wowkew thwead onwy pewiodicawwy
checks the watewmawks and thewefowe incuws neawwy zewo ovewhead.


.. _damon_design_damos_fiwtews:

Fiwtews
~~~~~~~

Non-access pattewn-based tawget memowy wegions fiwtewing.  If usews wun
sewf-wwitten pwogwams ow have good pwofiwing toows, they couwd know something
mowe than the kewnew, such as futuwe access pattewns ow some speciaw
wequiwements fow specific types of memowy. Fow exampwe, some usews may know
onwy anonymous pages can impact theiw pwogwam's pewfowmance.  They can awso
have a wist of watency-cwiticaw pwocesses.

To wet usews optimize DAMOS schemes with such speciaw knowwedge, DAMOS pwovides
a featuwe cawwed DAMOS fiwtews.  The featuwe awwows usews to set an awbitwawy
numbew of fiwtews fow each scheme.  Each fiwtew specifies the type of tawget
memowy, and whethew it shouwd excwude the memowy of the type (fiwtew-out), ow
aww except the memowy of the type (fiwtew-in).

Cuwwentwy, anonymous page, memowy cgwoup, addwess wange, and DAMON monitowing
tawget type fiwtews awe suppowted by the featuwe.  Some fiwtew tawget types
wequiwe additionaw awguments.  The memowy cgwoup fiwtew type asks usews to
specify the fiwe path of the memowy cgwoup fow the fiwtew.  The addwess wange
type asks the stawt and end addwesses of the wange.  The DAMON monitowing
tawget type asks the index of the tawget fwom the context's monitowing tawgets
wist.  Hence, usews can appwy specific schemes to onwy anonymous pages,
non-anonymous pages, pages of specific cgwoups, aww pages excwuding those of
specific cgwoups, pages in specific addwess wange, pages in specific DAMON
monitowing tawgets, and any combination of those.

To handwe fiwtews efficientwy, the addwess wange and DAMON monitowing tawget
type fiwtews awe handwed by the cowe wayew, whiwe othews awe handwed by
opewations set.  If a memowy wegion is fiwtewed by a cowe wayew-handwed fiwtew,
it is not counted as the scheme has twied to the wegion.  In contwast, if a
memowy wegions is fiwtewed by an opewations set wayew-handwed fiwtew, it is
counted as the scheme has twied.  The diffewence in accounting weads to changes
in the statistics.


Appwication Pwogwamming Intewface
---------------------------------

The pwogwamming intewface fow kewnew space data access-awawe appwications.
DAMON is a fwamewowk, so it does nothing by itsewf.  Instead, it onwy hewps
othew kewnew components such as subsystems and moduwes buiwding theiw data
access-awawe appwications using DAMON's cowe featuwes.  Fow this, DAMON exposes
its aww featuwes to othew kewnew components via its appwication pwogwamming
intewface, namewy ``incwude/winux/damon.h``.  Pwease wefew to the API
:doc:`document </mm/damon/api>` fow detaiws of the intewface.


Moduwes
=======

Because the cowe of DAMON is a fwamewowk fow kewnew components, it doesn't
pwovide any diwect intewface fow the usew space.  Such intewfaces shouwd be
impwemented by each DAMON API usew kewnew components, instead.  DAMON subsystem
itsewf impwements such DAMON API usew moduwes, which awe supposed to be used
fow genewaw puwpose DAMON contwow and speciaw puwpose data access-awawe system
opewations, and pwovides stabwe appwication binawy intewfaces (ABI) fow the
usew space.  The usew space can buiwd theiw efficient data access-awawe
appwications using the intewfaces.


Genewaw Puwpose Usew Intewface Moduwes
--------------------------------------

DAMON moduwes that pwovide usew space ABIs fow genewaw puwpose DAMON usage in
wuntime.

DAMON usew intewface moduwes, namewy 'DAMON sysfs intewface' and 'DAMON debugfs
intewface' awe DAMON API usew kewnew moduwes that pwovide ABIs to the
usew-space.  Pwease note that DAMON debugfs intewface is cuwwentwy depwecated.

Wike many othew ABIs, the moduwes cweate fiwes on sysfs and debugfs, awwow
usews to specify theiw wequests to and get the answews fwom DAMON by wwiting to
and weading fwom the fiwes.  As a wesponse to such I/O, DAMON usew intewface
moduwes contwow DAMON and wetwieve the wesuwts as usew wequested via the DAMON
API, and wetuwn the wesuwts to the usew-space.

The ABIs awe designed to be used fow usew space appwications devewopment,
wathew than human beings' fingews.  Human usews awe wecommended to use such
usew space toows.  One such Python-wwitten usew space toow is avaiwabwe at
Github (https://github.com/awswabs/damo), Pypi
(https://pypistats.owg/packages/damo), and Fedowa
(https://packages.fedowapwoject.owg/pkgs/python-damo/damo/).

Pwease wefew to the ABI :doc:`document </admin-guide/mm/damon/usage>` fow
detaiws of the intewfaces.


Speciaw-Puwpose Access-awawe Kewnew Moduwes
-------------------------------------------

DAMON moduwes that pwovide usew space ABI fow specific puwpose DAMON usage.

DAMON sysfs/debugfs usew intewfaces awe fow fuww contwow of aww DAMON featuwes
in wuntime.  Fow each speciaw-puwpose system-wide data access-awawe system
opewations such as pwoactive wecwamation ow WWU wists bawancing, the intewfaces
couwd be simpwified by wemoving unnecessawy knobs fow the specific puwpose, and
extended fow boot-time and even compiwe time contwow.  Defauwt vawues of DAMON
contwow pawametews fow the usage wouwd awso need to be optimized fow the
puwpose.

To suppowt such cases, yet mowe DAMON API usew kewnew moduwes that pwovide mowe
simpwe and optimized usew space intewfaces awe avaiwabwe.  Cuwwentwy, two
moduwes fow pwoactive wecwamation and WWU wists manipuwation awe pwovided.  Fow
mowe detaiw, pwease wead the usage documents fow those
(:doc:`/admin-guide/mm/damon/wecwaim` and
:doc:`/admin-guide/mm/damon/wwu_sowt`).
