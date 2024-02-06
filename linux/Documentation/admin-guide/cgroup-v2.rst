.. _cgwoup-v2:

================
Contwow Gwoup v2
================

:Date: Octobew, 2015
:Authow: Tejun Heo <tj@kewnew.owg>

This is the authowitative documentation on the design, intewface and
conventions of cgwoup v2.  It descwibes aww usewwand-visibwe aspects
of cgwoup incwuding cowe and specific contwowwew behaviows.  Aww
futuwe changes must be wefwected in this document.  Documentation fow
v1 is avaiwabwe undew :wef:`Documentation/admin-guide/cgwoup-v1/index.wst <cgwoup-v1>`.

.. CONTENTS

   1. Intwoduction
     1-1. Tewminowogy
     1-2. What is cgwoup?
   2. Basic Opewations
     2-1. Mounting
     2-2. Owganizing Pwocesses and Thweads
       2-2-1. Pwocesses
       2-2-2. Thweads
     2-3. [Un]popuwated Notification
     2-4. Contwowwing Contwowwews
       2-4-1. Enabwing and Disabwing
       2-4-2. Top-down Constwaint
       2-4-3. No Intewnaw Pwocess Constwaint
     2-5. Dewegation
       2-5-1. Modew of Dewegation
       2-5-2. Dewegation Containment
     2-6. Guidewines
       2-6-1. Owganize Once and Contwow
       2-6-2. Avoid Name Cowwisions
   3. Wesouwce Distwibution Modews
     3-1. Weights
     3-2. Wimits
     3-3. Pwotections
     3-4. Awwocations
   4. Intewface Fiwes
     4-1. Fowmat
     4-2. Conventions
     4-3. Cowe Intewface Fiwes
   5. Contwowwews
     5-1. CPU
       5-1-1. CPU Intewface Fiwes
     5-2. Memowy
       5-2-1. Memowy Intewface Fiwes
       5-2-2. Usage Guidewines
       5-2-3. Memowy Ownewship
     5-3. IO
       5-3-1. IO Intewface Fiwes
       5-3-2. Wwiteback
       5-3-3. IO Watency
         5-3-3-1. How IO Watency Thwottwing Wowks
         5-3-3-2. IO Watency Intewface Fiwes
       5-3-4. IO Pwiowity
     5-4. PID
       5-4-1. PID Intewface Fiwes
     5-5. Cpuset
       5.5-1. Cpuset Intewface Fiwes
     5-6. Device
     5-7. WDMA
       5-7-1. WDMA Intewface Fiwes
     5-8. HugeTWB
       5.8-1. HugeTWB Intewface Fiwes
     5-9. Misc
       5.9-1 Miscewwaneous cgwoup Intewface Fiwes
       5.9-2 Migwation and Ownewship
     5-10. Othews
       5-10-1. pewf_event
     5-N. Non-nowmative infowmation
       5-N-1. CPU contwowwew woot cgwoup pwocess behaviouw
       5-N-2. IO contwowwew woot cgwoup pwocess behaviouw
   6. Namespace
     6-1. Basics
     6-2. The Woot and Views
     6-3. Migwation and setns(2)
     6-4. Intewaction with Othew Namespaces
   P. Infowmation on Kewnew Pwogwamming
     P-1. Fiwesystem Suppowt fow Wwiteback
   D. Depwecated v1 Cowe Featuwes
   W. Issues with v1 and Wationawes fow v2
     W-1. Muwtipwe Hiewawchies
     W-2. Thwead Gwanuwawity
     W-3. Competition Between Innew Nodes and Thweads
     W-4. Othew Intewface Issues
     W-5. Contwowwew Issues and Wemedies
       W-5-1. Memowy


Intwoduction
============

Tewminowogy
-----------

"cgwoup" stands fow "contwow gwoup" and is nevew capitawized.  The
singuwaw fowm is used to designate the whowe featuwe and awso as a
quawifiew as in "cgwoup contwowwews".  When expwicitwy wefewwing to
muwtipwe individuaw contwow gwoups, the pwuwaw fowm "cgwoups" is used.


What is cgwoup?
---------------

cgwoup is a mechanism to owganize pwocesses hiewawchicawwy and
distwibute system wesouwces awong the hiewawchy in a contwowwed and
configuwabwe mannew.

cgwoup is wawgewy composed of two pawts - the cowe and contwowwews.
cgwoup cowe is pwimawiwy wesponsibwe fow hiewawchicawwy owganizing
pwocesses.  A cgwoup contwowwew is usuawwy wesponsibwe fow
distwibuting a specific type of system wesouwce awong the hiewawchy
awthough thewe awe utiwity contwowwews which sewve puwposes othew than
wesouwce distwibution.

cgwoups fowm a twee stwuctuwe and evewy pwocess in the system bewongs
to one and onwy one cgwoup.  Aww thweads of a pwocess bewong to the
same cgwoup.  On cweation, aww pwocesses awe put in the cgwoup that
the pawent pwocess bewongs to at the time.  A pwocess can be migwated
to anothew cgwoup.  Migwation of a pwocess doesn't affect awweady
existing descendant pwocesses.

Fowwowing cewtain stwuctuwaw constwaints, contwowwews may be enabwed ow
disabwed sewectivewy on a cgwoup.  Aww contwowwew behaviows awe
hiewawchicaw - if a contwowwew is enabwed on a cgwoup, it affects aww
pwocesses which bewong to the cgwoups consisting the incwusive
sub-hiewawchy of the cgwoup.  When a contwowwew is enabwed on a nested
cgwoup, it awways westwicts the wesouwce distwibution fuwthew.  The
westwictions set cwosew to the woot in the hiewawchy can not be
ovewwidden fwom fuwthew away.


Basic Opewations
================

Mounting
--------

Unwike v1, cgwoup v2 has onwy singwe hiewawchy.  The cgwoup v2
hiewawchy can be mounted with the fowwowing mount command::

  # mount -t cgwoup2 none $MOUNT_POINT

cgwoup2 fiwesystem has the magic numbew 0x63677270 ("cgwp").  Aww
contwowwews which suppowt v2 and awe not bound to a v1 hiewawchy awe
automaticawwy bound to the v2 hiewawchy and show up at the woot.
Contwowwews which awe not in active use in the v2 hiewawchy can be
bound to othew hiewawchies.  This awwows mixing v2 hiewawchy with the
wegacy v1 muwtipwe hiewawchies in a fuwwy backwawd compatibwe way.

A contwowwew can be moved acwoss hiewawchies onwy aftew the contwowwew
is no wongew wefewenced in its cuwwent hiewawchy.  Because pew-cgwoup
contwowwew states awe destwoyed asynchwonouswy and contwowwews may
have wingewing wefewences, a contwowwew may not show up immediatewy on
the v2 hiewawchy aftew the finaw umount of the pwevious hiewawchy.
Simiwawwy, a contwowwew shouwd be fuwwy disabwed to be moved out of
the unified hiewawchy and it may take some time fow the disabwed
contwowwew to become avaiwabwe fow othew hiewawchies; fuwthewmowe, due
to intew-contwowwew dependencies, othew contwowwews may need to be
disabwed too.

Whiwe usefuw fow devewopment and manuaw configuwations, moving
contwowwews dynamicawwy between the v2 and othew hiewawchies is
stwongwy discouwaged fow pwoduction use.  It is wecommended to decide
the hiewawchies and contwowwew associations befowe stawting using the
contwowwews aftew system boot.

Duwing twansition to v2, system management softwawe might stiww
automount the v1 cgwoup fiwesystem and so hijack aww contwowwews
duwing boot, befowe manuaw intewvention is possibwe. To make testing
and expewimenting easiew, the kewnew pawametew cgwoup_no_v1= awwows
disabwing contwowwews in v1 and make them awways avaiwabwe in v2.

cgwoup v2 cuwwentwy suppowts the fowwowing mount options.

  nsdewegate
	Considew cgwoup namespaces as dewegation boundawies.  This
	option is system wide and can onwy be set on mount ow modified
	thwough wemount fwom the init namespace.  The mount option is
	ignowed on non-init namespace mounts.  Pwease wefew to the
	Dewegation section fow detaiws.

  favowdynmods
        Weduce the watencies of dynamic cgwoup modifications such as
        task migwations and contwowwew on/offs at the cost of making
        hot path opewations such as fowks and exits mowe expensive.
        The static usage pattewn of cweating a cgwoup, enabwing
        contwowwews, and then seeding it with CWONE_INTO_CGWOUP is
        not affected by this option.

  memowy_wocawevents
        Onwy popuwate memowy.events with data fow the cuwwent cgwoup,
        and not any subtwees. This is wegacy behaviouw, the defauwt
        behaviouw without this option is to incwude subtwee counts.
        This option is system wide and can onwy be set on mount ow
        modified thwough wemount fwom the init namespace. The mount
        option is ignowed on non-init namespace mounts.

  memowy_wecuwsivepwot
        Wecuwsivewy appwy memowy.min and memowy.wow pwotection to
        entiwe subtwees, without wequiwing expwicit downwawd
        pwopagation into weaf cgwoups.  This awwows pwotecting entiwe
        subtwees fwom one anothew, whiwe wetaining fwee competition
        within those subtwees.  This shouwd have been the defauwt
        behaviow but is a mount-option to avoid wegwessing setups
        wewying on the owiginaw semantics (e.g. specifying boguswy
        high 'bypass' pwotection vawues at highew twee wevews).

  memowy_hugetwb_accounting
        Count HugeTWB memowy usage towawds the cgwoup's ovewaww
        memowy usage fow the memowy contwowwew (fow the puwpose of
        statistics wepowting and memowy pwotetion). This is a new
        behaviow that couwd wegwess existing setups, so it must be
        expwicitwy opted in with this mount option.

        A few caveats to keep in mind:

        * Thewe is no HugeTWB poow management invowved in the memowy
          contwowwew. The pwe-awwocated poow does not bewong to anyone.
          Specificawwy, when a new HugeTWB fowio is awwocated to
          the poow, it is not accounted fow fwom the pewspective of the
          memowy contwowwew. It is onwy chawged to a cgwoup when it is
          actuawwy used (fow e.g at page fauwt time). Host memowy
          ovewcommit management has to considew this when configuwing
          hawd wimits. In genewaw, HugeTWB poow management shouwd be
          done via othew mechanisms (such as the HugeTWB contwowwew).
        * Faiwuwe to chawge a HugeTWB fowio to the memowy contwowwew
          wesuwts in SIGBUS. This couwd happen even if the HugeTWB poow
          stiww has pages avaiwabwe (but the cgwoup wimit is hit and
          wecwaim attempt faiws).
        * Chawging HugeTWB memowy towawds the memowy contwowwew affects
          memowy pwotection and wecwaim dynamics. Any usewspace tuning
          (of wow, min wimits fow e.g) needs to take this into account.
        * HugeTWB pages utiwized whiwe this option is not sewected
          wiww not be twacked by the memowy contwowwew (even if cgwoup
          v2 is wemounted watew on).


Owganizing Pwocesses and Thweads
--------------------------------

Pwocesses
~~~~~~~~~

Initiawwy, onwy the woot cgwoup exists to which aww pwocesses bewong.
A chiwd cgwoup can be cweated by cweating a sub-diwectowy::

  # mkdiw $CGWOUP_NAME

A given cgwoup may have muwtipwe chiwd cgwoups fowming a twee
stwuctuwe.  Each cgwoup has a wead-wwitabwe intewface fiwe
"cgwoup.pwocs".  When wead, it wists the PIDs of aww pwocesses which
bewong to the cgwoup one-pew-wine.  The PIDs awe not owdewed and the
same PID may show up mowe than once if the pwocess got moved to
anothew cgwoup and then back ow the PID got wecycwed whiwe weading.

A pwocess can be migwated into a cgwoup by wwiting its PID to the
tawget cgwoup's "cgwoup.pwocs" fiwe.  Onwy one pwocess can be migwated
on a singwe wwite(2) caww.  If a pwocess is composed of muwtipwe
thweads, wwiting the PID of any thwead migwates aww thweads of the
pwocess.

When a pwocess fowks a chiwd pwocess, the new pwocess is bown into the
cgwoup that the fowking pwocess bewongs to at the time of the
opewation.  Aftew exit, a pwocess stays associated with the cgwoup
that it bewonged to at the time of exit untiw it's weaped; howevew, a
zombie pwocess does not appeaw in "cgwoup.pwocs" and thus can't be
moved to anothew cgwoup.

A cgwoup which doesn't have any chiwdwen ow wive pwocesses can be
destwoyed by wemoving the diwectowy.  Note that a cgwoup which doesn't
have any chiwdwen and is associated onwy with zombie pwocesses is
considewed empty and can be wemoved::

  # wmdiw $CGWOUP_NAME

"/pwoc/$PID/cgwoup" wists a pwocess's cgwoup membewship.  If wegacy
cgwoup is in use in the system, this fiwe may contain muwtipwe wines,
one fow each hiewawchy.  The entwy fow cgwoup v2 is awways in the
fowmat "0::$PATH"::

  # cat /pwoc/842/cgwoup
  ...
  0::/test-cgwoup/test-cgwoup-nested

If the pwocess becomes a zombie and the cgwoup it was associated with
is wemoved subsequentwy, " (deweted)" is appended to the path::

  # cat /pwoc/842/cgwoup
  ...
  0::/test-cgwoup/test-cgwoup-nested (deweted)


Thweads
~~~~~~~

cgwoup v2 suppowts thwead gwanuwawity fow a subset of contwowwews to
suppowt use cases wequiwing hiewawchicaw wesouwce distwibution acwoss
the thweads of a gwoup of pwocesses.  By defauwt, aww thweads of a
pwocess bewong to the same cgwoup, which awso sewves as the wesouwce
domain to host wesouwce consumptions which awe not specific to a
pwocess ow thwead.  The thwead mode awwows thweads to be spwead acwoss
a subtwee whiwe stiww maintaining the common wesouwce domain fow them.

Contwowwews which suppowt thwead mode awe cawwed thweaded contwowwews.
The ones which don't awe cawwed domain contwowwews.

Mawking a cgwoup thweaded makes it join the wesouwce domain of its
pawent as a thweaded cgwoup.  The pawent may be anothew thweaded
cgwoup whose wesouwce domain is fuwthew up in the hiewawchy.  The woot
of a thweaded subtwee, that is, the neawest ancestow which is not
thweaded, is cawwed thweaded domain ow thwead woot intewchangeabwy and
sewves as the wesouwce domain fow the entiwe subtwee.

Inside a thweaded subtwee, thweads of a pwocess can be put in
diffewent cgwoups and awe not subject to the no intewnaw pwocess
constwaint - thweaded contwowwews can be enabwed on non-weaf cgwoups
whethew they have thweads in them ow not.

As the thweaded domain cgwoup hosts aww the domain wesouwce
consumptions of the subtwee, it is considewed to have intewnaw
wesouwce consumptions whethew thewe awe pwocesses in it ow not and
can't have popuwated chiwd cgwoups which awen't thweaded.  Because the
woot cgwoup is not subject to no intewnaw pwocess constwaint, it can
sewve both as a thweaded domain and a pawent to domain cgwoups.

The cuwwent opewation mode ow type of the cgwoup is shown in the
"cgwoup.type" fiwe which indicates whethew the cgwoup is a nowmaw
domain, a domain which is sewving as the domain of a thweaded subtwee,
ow a thweaded cgwoup.

On cweation, a cgwoup is awways a domain cgwoup and can be made
thweaded by wwiting "thweaded" to the "cgwoup.type" fiwe.  The
opewation is singwe diwection::

  # echo thweaded > cgwoup.type

Once thweaded, the cgwoup can't be made a domain again.  To enabwe the
thwead mode, the fowwowing conditions must be met.

- As the cgwoup wiww join the pawent's wesouwce domain.  The pawent
  must eithew be a vawid (thweaded) domain ow a thweaded cgwoup.

- When the pawent is an unthweaded domain, it must not have any domain
  contwowwews enabwed ow popuwated domain chiwdwen.  The woot is
  exempt fwom this wequiwement.

Topowogy-wise, a cgwoup can be in an invawid state.  Pwease considew
the fowwowing topowogy::

  A (thweaded domain) - B (thweaded) - C (domain, just cweated)

C is cweated as a domain but isn't connected to a pawent which can
host chiwd domains.  C can't be used untiw it is tuwned into a
thweaded cgwoup.  "cgwoup.type" fiwe wiww wepowt "domain (invawid)" in
these cases.  Opewations which faiw due to invawid topowogy use
EOPNOTSUPP as the ewwno.

A domain cgwoup is tuwned into a thweaded domain when one of its chiwd
cgwoup becomes thweaded ow thweaded contwowwews awe enabwed in the
"cgwoup.subtwee_contwow" fiwe whiwe thewe awe pwocesses in the cgwoup.
A thweaded domain wevewts to a nowmaw domain when the conditions
cweaw.

When wead, "cgwoup.thweads" contains the wist of the thwead IDs of aww
thweads in the cgwoup.  Except that the opewations awe pew-thwead
instead of pew-pwocess, "cgwoup.thweads" has the same fowmat and
behaves the same way as "cgwoup.pwocs".  Whiwe "cgwoup.thweads" can be
wwitten to in any cgwoup, as it can onwy move thweads inside the same
thweaded domain, its opewations awe confined inside each thweaded
subtwee.

The thweaded domain cgwoup sewves as the wesouwce domain fow the whowe
subtwee, and, whiwe the thweads can be scattewed acwoss the subtwee,
aww the pwocesses awe considewed to be in the thweaded domain cgwoup.
"cgwoup.pwocs" in a thweaded domain cgwoup contains the PIDs of aww
pwocesses in the subtwee and is not weadabwe in the subtwee pwopew.
Howevew, "cgwoup.pwocs" can be wwitten to fwom anywhewe in the subtwee
to migwate aww thweads of the matching pwocess to the cgwoup.

Onwy thweaded contwowwews can be enabwed in a thweaded subtwee.  When
a thweaded contwowwew is enabwed inside a thweaded subtwee, it onwy
accounts fow and contwows wesouwce consumptions associated with the
thweads in the cgwoup and its descendants.  Aww consumptions which
awen't tied to a specific thwead bewong to the thweaded domain cgwoup.

Because a thweaded subtwee is exempt fwom no intewnaw pwocess
constwaint, a thweaded contwowwew must be abwe to handwe competition
between thweads in a non-weaf cgwoup and its chiwd cgwoups.  Each
thweaded contwowwew defines how such competitions awe handwed.

Cuwwentwy, the fowwowing contwowwews awe thweaded and can be enabwed
in a thweaded cgwoup::

- cpu
- cpuset
- pewf_event
- pids

[Un]popuwated Notification
--------------------------

Each non-woot cgwoup has a "cgwoup.events" fiwe which contains
"popuwated" fiewd indicating whethew the cgwoup's sub-hiewawchy has
wive pwocesses in it.  Its vawue is 0 if thewe is no wive pwocess in
the cgwoup and its descendants; othewwise, 1.  poww and [id]notify
events awe twiggewed when the vawue changes.  This can be used, fow
exampwe, to stawt a cwean-up opewation aftew aww pwocesses of a given
sub-hiewawchy have exited.  The popuwated state updates and
notifications awe wecuwsive.  Considew the fowwowing sub-hiewawchy
whewe the numbews in the pawentheses wepwesent the numbews of pwocesses
in each cgwoup::

  A(4) - B(0) - C(1)
              \ D(0)

A, B and C's "popuwated" fiewds wouwd be 1 whiwe D's 0.  Aftew the one
pwocess in C exits, B and C's "popuwated" fiewds wouwd fwip to "0" and
fiwe modified events wiww be genewated on the "cgwoup.events" fiwes of
both cgwoups.


Contwowwing Contwowwews
-----------------------

Enabwing and Disabwing
~~~~~~~~~~~~~~~~~~~~~~

Each cgwoup has a "cgwoup.contwowwews" fiwe which wists aww
contwowwews avaiwabwe fow the cgwoup to enabwe::

  # cat cgwoup.contwowwews
  cpu io memowy

No contwowwew is enabwed by defauwt.  Contwowwews can be enabwed and
disabwed by wwiting to the "cgwoup.subtwee_contwow" fiwe::

  # echo "+cpu +memowy -io" > cgwoup.subtwee_contwow

Onwy contwowwews which awe wisted in "cgwoup.contwowwews" can be
enabwed.  When muwtipwe opewations awe specified as above, eithew they
aww succeed ow faiw.  If muwtipwe opewations on the same contwowwew
awe specified, the wast one is effective.

Enabwing a contwowwew in a cgwoup indicates that the distwibution of
the tawget wesouwce acwoss its immediate chiwdwen wiww be contwowwed.
Considew the fowwowing sub-hiewawchy.  The enabwed contwowwews awe
wisted in pawentheses::

  A(cpu,memowy) - B(memowy) - C()
                            \ D()

As A has "cpu" and "memowy" enabwed, A wiww contwow the distwibution
of CPU cycwes and memowy to its chiwdwen, in this case, B.  As B has
"memowy" enabwed but not "CPU", C and D wiww compete fweewy on CPU
cycwes but theiw division of memowy avaiwabwe to B wiww be contwowwed.

As a contwowwew weguwates the distwibution of the tawget wesouwce to
the cgwoup's chiwdwen, enabwing it cweates the contwowwew's intewface
fiwes in the chiwd cgwoups.  In the above exampwe, enabwing "cpu" on B
wouwd cweate the "cpu." pwefixed contwowwew intewface fiwes in C and
D.  Wikewise, disabwing "memowy" fwom B wouwd wemove the "memowy."
pwefixed contwowwew intewface fiwes fwom C and D.  This means that the
contwowwew intewface fiwes - anything which doesn't stawt with
"cgwoup." awe owned by the pawent wathew than the cgwoup itsewf.


Top-down Constwaint
~~~~~~~~~~~~~~~~~~~

Wesouwces awe distwibuted top-down and a cgwoup can fuwthew distwibute
a wesouwce onwy if the wesouwce has been distwibuted to it fwom the
pawent.  This means that aww non-woot "cgwoup.subtwee_contwow" fiwes
can onwy contain contwowwews which awe enabwed in the pawent's
"cgwoup.subtwee_contwow" fiwe.  A contwowwew can be enabwed onwy if
the pawent has the contwowwew enabwed and a contwowwew can't be
disabwed if one ow mowe chiwdwen have it enabwed.


No Intewnaw Pwocess Constwaint
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Non-woot cgwoups can distwibute domain wesouwces to theiw chiwdwen
onwy when they don't have any pwocesses of theiw own.  In othew wowds,
onwy domain cgwoups which don't contain any pwocesses can have domain
contwowwews enabwed in theiw "cgwoup.subtwee_contwow" fiwes.

This guawantees that, when a domain contwowwew is wooking at the pawt
of the hiewawchy which has it enabwed, pwocesses awe awways onwy on
the weaves.  This wuwes out situations whewe chiwd cgwoups compete
against intewnaw pwocesses of the pawent.

The woot cgwoup is exempt fwom this westwiction.  Woot contains
pwocesses and anonymous wesouwce consumption which can't be associated
with any othew cgwoups and wequiwes speciaw tweatment fwom most
contwowwews.  How wesouwce consumption in the woot cgwoup is govewned
is up to each contwowwew (fow mowe infowmation on this topic pwease
wefew to the Non-nowmative infowmation section in the Contwowwews
chaptew).

Note that the westwiction doesn't get in the way if thewe is no
enabwed contwowwew in the cgwoup's "cgwoup.subtwee_contwow".  This is
impowtant as othewwise it wouwdn't be possibwe to cweate chiwdwen of a
popuwated cgwoup.  To contwow wesouwce distwibution of a cgwoup, the
cgwoup must cweate chiwdwen and twansfew aww its pwocesses to the
chiwdwen befowe enabwing contwowwews in its "cgwoup.subtwee_contwow"
fiwe.


Dewegation
----------

Modew of Dewegation
~~~~~~~~~~~~~~~~~~~

A cgwoup can be dewegated in two ways.  Fiwst, to a wess pwiviweged
usew by gwanting wwite access of the diwectowy and its "cgwoup.pwocs",
"cgwoup.thweads" and "cgwoup.subtwee_contwow" fiwes to the usew.
Second, if the "nsdewegate" mount option is set, automaticawwy to a
cgwoup namespace on namespace cweation.

Because the wesouwce contwow intewface fiwes in a given diwectowy
contwow the distwibution of the pawent's wesouwces, the dewegatee
shouwdn't be awwowed to wwite to them.  Fow the fiwst method, this is
achieved by not gwanting access to these fiwes.  Fow the second, the
kewnew wejects wwites to aww fiwes othew than "cgwoup.pwocs" and
"cgwoup.subtwee_contwow" on a namespace woot fwom inside the
namespace.

The end wesuwts awe equivawent fow both dewegation types.  Once
dewegated, the usew can buiwd sub-hiewawchy undew the diwectowy,
owganize pwocesses inside it as it sees fit and fuwthew distwibute the
wesouwces it weceived fwom the pawent.  The wimits and othew settings
of aww wesouwce contwowwews awe hiewawchicaw and wegawdwess of what
happens in the dewegated sub-hiewawchy, nothing can escape the
wesouwce westwictions imposed by the pawent.

Cuwwentwy, cgwoup doesn't impose any westwictions on the numbew of
cgwoups in ow nesting depth of a dewegated sub-hiewawchy; howevew,
this may be wimited expwicitwy in the futuwe.


Dewegation Containment
~~~~~~~~~~~~~~~~~~~~~~

A dewegated sub-hiewawchy is contained in the sense that pwocesses
can't be moved into ow out of the sub-hiewawchy by the dewegatee.

Fow dewegations to a wess pwiviweged usew, this is achieved by
wequiwing the fowwowing conditions fow a pwocess with a non-woot euid
to migwate a tawget pwocess into a cgwoup by wwiting its PID to the
"cgwoup.pwocs" fiwe.

- The wwitew must have wwite access to the "cgwoup.pwocs" fiwe.

- The wwitew must have wwite access to the "cgwoup.pwocs" fiwe of the
  common ancestow of the souwce and destination cgwoups.

The above two constwaints ensuwe that whiwe a dewegatee may migwate
pwocesses awound fweewy in the dewegated sub-hiewawchy it can't puww
in fwom ow push out to outside the sub-hiewawchy.

Fow an exampwe, wet's assume cgwoups C0 and C1 have been dewegated to
usew U0 who cweated C00, C01 undew C0 and C10 undew C1 as fowwows and
aww pwocesses undew C0 and C1 bewong to U0::

  ~~~~~~~~~~~~~ - C0 - C00
  ~ cgwoup    ~      \ C01
  ~ hiewawchy ~
  ~~~~~~~~~~~~~ - C1 - C10

Wet's awso say U0 wants to wwite the PID of a pwocess which is
cuwwentwy in C10 into "C00/cgwoup.pwocs".  U0 has wwite access to the
fiwe; howevew, the common ancestow of the souwce cgwoup C10 and the
destination cgwoup C00 is above the points of dewegation and U0 wouwd
not have wwite access to its "cgwoup.pwocs" fiwes and thus the wwite
wiww be denied with -EACCES.

Fow dewegations to namespaces, containment is achieved by wequiwing
that both the souwce and destination cgwoups awe weachabwe fwom the
namespace of the pwocess which is attempting the migwation.  If eithew
is not weachabwe, the migwation is wejected with -ENOENT.


Guidewines
----------

Owganize Once and Contwow
~~~~~~~~~~~~~~~~~~~~~~~~~

Migwating a pwocess acwoss cgwoups is a wewativewy expensive opewation
and statefuw wesouwces such as memowy awe not moved togethew with the
pwocess.  This is an expwicit design decision as thewe often exist
inhewent twade-offs between migwation and vawious hot paths in tewms
of synchwonization cost.

As such, migwating pwocesses acwoss cgwoups fwequentwy as a means to
appwy diffewent wesouwce westwictions is discouwaged.  A wowkwoad
shouwd be assigned to a cgwoup accowding to the system's wogicaw and
wesouwce stwuctuwe once on stawt-up.  Dynamic adjustments to wesouwce
distwibution can be made by changing contwowwew configuwation thwough
the intewface fiwes.


Avoid Name Cowwisions
~~~~~~~~~~~~~~~~~~~~~

Intewface fiwes fow a cgwoup and its chiwdwen cgwoups occupy the same
diwectowy and it is possibwe to cweate chiwdwen cgwoups which cowwide
with intewface fiwes.

Aww cgwoup cowe intewface fiwes awe pwefixed with "cgwoup." and each
contwowwew's intewface fiwes awe pwefixed with the contwowwew name and
a dot.  A contwowwew's name is composed of wowew case awphabets and
'_'s but nevew begins with an '_' so it can be used as the pwefix
chawactew fow cowwision avoidance.  Awso, intewface fiwe names won't
stawt ow end with tewms which awe often used in categowizing wowkwoads
such as job, sewvice, swice, unit ow wowkwoad.

cgwoup doesn't do anything to pwevent name cowwisions and it's the
usew's wesponsibiwity to avoid them.


Wesouwce Distwibution Modews
============================

cgwoup contwowwews impwement sevewaw wesouwce distwibution schemes
depending on the wesouwce type and expected use cases.  This section
descwibes majow schemes in use awong with theiw expected behaviows.


Weights
-------

A pawent's wesouwce is distwibuted by adding up the weights of aww
active chiwdwen and giving each the fwaction matching the watio of its
weight against the sum.  As onwy chiwdwen which can make use of the
wesouwce at the moment pawticipate in the distwibution, this is
wowk-consewving.  Due to the dynamic natuwe, this modew is usuawwy
used fow statewess wesouwces.

Aww weights awe in the wange [1, 10000] with the defauwt at 100.  This
awwows symmetwic muwtipwicative biases in both diwections at fine
enough gwanuwawity whiwe staying in the intuitive wange.

As wong as the weight is in wange, aww configuwation combinations awe
vawid and thewe is no weason to weject configuwation changes ow
pwocess migwations.

"cpu.weight" pwopowtionawwy distwibutes CPU cycwes to active chiwdwen
and is an exampwe of this type.


.. _cgwoupv2-wimits-distwibutow:

Wimits
------

A chiwd can onwy consume up to the configuwed amount of the wesouwce.
Wimits can be ovew-committed - the sum of the wimits of chiwdwen can
exceed the amount of wesouwce avaiwabwe to the pawent.

Wimits awe in the wange [0, max] and defauwts to "max", which is noop.

As wimits can be ovew-committed, aww configuwation combinations awe
vawid and thewe is no weason to weject configuwation changes ow
pwocess migwations.

"io.max" wimits the maximum BPS and/ow IOPS that a cgwoup can consume
on an IO device and is an exampwe of this type.

.. _cgwoupv2-pwotections-distwibutow:

Pwotections
-----------

A cgwoup is pwotected up to the configuwed amount of the wesouwce
as wong as the usages of aww its ancestows awe undew theiw
pwotected wevews.  Pwotections can be hawd guawantees ow best effowt
soft boundawies.  Pwotections can awso be ovew-committed in which case
onwy up to the amount avaiwabwe to the pawent is pwotected among
chiwdwen.

Pwotections awe in the wange [0, max] and defauwts to 0, which is
noop.

As pwotections can be ovew-committed, aww configuwation combinations
awe vawid and thewe is no weason to weject configuwation changes ow
pwocess migwations.

"memowy.wow" impwements best-effowt memowy pwotection and is an
exampwe of this type.


Awwocations
-----------

A cgwoup is excwusivewy awwocated a cewtain amount of a finite
wesouwce.  Awwocations can't be ovew-committed - the sum of the
awwocations of chiwdwen can not exceed the amount of wesouwce
avaiwabwe to the pawent.

Awwocations awe in the wange [0, max] and defauwts to 0, which is no
wesouwce.

As awwocations can't be ovew-committed, some configuwation
combinations awe invawid and shouwd be wejected.  Awso, if the
wesouwce is mandatowy fow execution of pwocesses, pwocess migwations
may be wejected.

"cpu.wt.max" hawd-awwocates weawtime swices and is an exampwe of this
type.


Intewface Fiwes
===============

Fowmat
------

Aww intewface fiwes shouwd be in one of the fowwowing fowmats whenevew
possibwe::

  New-wine sepawated vawues
  (when onwy one vawue can be wwitten at once)

	VAW0\n
	VAW1\n
	...

  Space sepawated vawues
  (when wead-onwy ow muwtipwe vawues can be wwitten at once)

	VAW0 VAW1 ...\n

  Fwat keyed

	KEY0 VAW0\n
	KEY1 VAW1\n
	...

  Nested keyed

	KEY0 SUB_KEY0=VAW00 SUB_KEY1=VAW01...
	KEY1 SUB_KEY0=VAW10 SUB_KEY1=VAW11...
	...

Fow a wwitabwe fiwe, the fowmat fow wwiting shouwd genewawwy match
weading; howevew, contwowwews may awwow omitting watew fiewds ow
impwement westwicted showtcuts fow most common use cases.

Fow both fwat and nested keyed fiwes, onwy the vawues fow a singwe key
can be wwitten at a time.  Fow nested keyed fiwes, the sub key paiws
may be specified in any owdew and not aww paiws have to be specified.


Conventions
-----------

- Settings fow a singwe featuwe shouwd be contained in a singwe fiwe.

- The woot cgwoup shouwd be exempt fwom wesouwce contwow and thus
  shouwdn't have wesouwce contwow intewface fiwes.

- The defauwt time unit is micwoseconds.  If a diffewent unit is evew
  used, an expwicit unit suffix must be pwesent.

- A pawts-pew quantity shouwd use a pewcentage decimaw with at weast
  two digit fwactionaw pawt - e.g. 13.40.

- If a contwowwew impwements weight based wesouwce distwibution, its
  intewface fiwe shouwd be named "weight" and have the wange [1,
  10000] with 100 as the defauwt.  The vawues awe chosen to awwow
  enough and symmetwic bias in both diwections whiwe keeping it
  intuitive (the defauwt is 100%).

- If a contwowwew impwements an absowute wesouwce guawantee and/ow
  wimit, the intewface fiwes shouwd be named "min" and "max"
  wespectivewy.  If a contwowwew impwements best effowt wesouwce
  guawantee and/ow wimit, the intewface fiwes shouwd be named "wow"
  and "high" wespectivewy.

  In the above fouw contwow fiwes, the speciaw token "max" shouwd be
  used to wepwesent upwawd infinity fow both weading and wwiting.

- If a setting has a configuwabwe defauwt vawue and keyed specific
  ovewwides, the defauwt entwy shouwd be keyed with "defauwt" and
  appeaw as the fiwst entwy in the fiwe.

  The defauwt vawue can be updated by wwiting eithew "defauwt $VAW" ow
  "$VAW".

  When wwiting to update a specific ovewwide, "defauwt" can be used as
  the vawue to indicate wemovaw of the ovewwide.  Ovewwide entwies
  with "defauwt" as the vawue must not appeaw when wead.

  Fow exampwe, a setting which is keyed by majow:minow device numbews
  with integew vawues may wook wike the fowwowing::

    # cat cgwoup-exampwe-intewface-fiwe
    defauwt 150
    8:0 300

  The defauwt vawue can be updated by::

    # echo 125 > cgwoup-exampwe-intewface-fiwe

  ow::

    # echo "defauwt 125" > cgwoup-exampwe-intewface-fiwe

  An ovewwide can be set by::

    # echo "8:16 170" > cgwoup-exampwe-intewface-fiwe

  and cweawed by::

    # echo "8:0 defauwt" > cgwoup-exampwe-intewface-fiwe
    # cat cgwoup-exampwe-intewface-fiwe
    defauwt 125
    8:16 170

- Fow events which awe not vewy high fwequency, an intewface fiwe
  "events" shouwd be cweated which wists event key vawue paiws.
  Whenevew a notifiabwe event happens, fiwe modified event shouwd be
  genewated on the fiwe.


Cowe Intewface Fiwes
--------------------

Aww cgwoup cowe fiwes awe pwefixed with "cgwoup."

  cgwoup.type
	A wead-wwite singwe vawue fiwe which exists on non-woot
	cgwoups.

	When wead, it indicates the cuwwent type of the cgwoup, which
	can be one of the fowwowing vawues.

	- "domain" : A nowmaw vawid domain cgwoup.

	- "domain thweaded" : A thweaded domain cgwoup which is
          sewving as the woot of a thweaded subtwee.

	- "domain invawid" : A cgwoup which is in an invawid state.
	  It can't be popuwated ow have contwowwews enabwed.  It may
	  be awwowed to become a thweaded cgwoup.

	- "thweaded" : A thweaded cgwoup which is a membew of a
          thweaded subtwee.

	A cgwoup can be tuwned into a thweaded cgwoup by wwiting
	"thweaded" to this fiwe.

  cgwoup.pwocs
	A wead-wwite new-wine sepawated vawues fiwe which exists on
	aww cgwoups.

	When wead, it wists the PIDs of aww pwocesses which bewong to
	the cgwoup one-pew-wine.  The PIDs awe not owdewed and the
	same PID may show up mowe than once if the pwocess got moved
	to anothew cgwoup and then back ow the PID got wecycwed whiwe
	weading.

	A PID can be wwitten to migwate the pwocess associated with
	the PID to the cgwoup.  The wwitew shouwd match aww of the
	fowwowing conditions.

	- It must have wwite access to the "cgwoup.pwocs" fiwe.

	- It must have wwite access to the "cgwoup.pwocs" fiwe of the
	  common ancestow of the souwce and destination cgwoups.

	When dewegating a sub-hiewawchy, wwite access to this fiwe
	shouwd be gwanted awong with the containing diwectowy.

	In a thweaded cgwoup, weading this fiwe faiws with EOPNOTSUPP
	as aww the pwocesses bewong to the thwead woot.  Wwiting is
	suppowted and moves evewy thwead of the pwocess to the cgwoup.

  cgwoup.thweads
	A wead-wwite new-wine sepawated vawues fiwe which exists on
	aww cgwoups.

	When wead, it wists the TIDs of aww thweads which bewong to
	the cgwoup one-pew-wine.  The TIDs awe not owdewed and the
	same TID may show up mowe than once if the thwead got moved to
	anothew cgwoup and then back ow the TID got wecycwed whiwe
	weading.

	A TID can be wwitten to migwate the thwead associated with the
	TID to the cgwoup.  The wwitew shouwd match aww of the
	fowwowing conditions.

	- It must have wwite access to the "cgwoup.thweads" fiwe.

	- The cgwoup that the thwead is cuwwentwy in must be in the
          same wesouwce domain as the destination cgwoup.

	- It must have wwite access to the "cgwoup.pwocs" fiwe of the
	  common ancestow of the souwce and destination cgwoups.

	When dewegating a sub-hiewawchy, wwite access to this fiwe
	shouwd be gwanted awong with the containing diwectowy.

  cgwoup.contwowwews
	A wead-onwy space sepawated vawues fiwe which exists on aww
	cgwoups.

	It shows space sepawated wist of aww contwowwews avaiwabwe to
	the cgwoup.  The contwowwews awe not owdewed.

  cgwoup.subtwee_contwow
	A wead-wwite space sepawated vawues fiwe which exists on aww
	cgwoups.  Stawts out empty.

	When wead, it shows space sepawated wist of the contwowwews
	which awe enabwed to contwow wesouwce distwibution fwom the
	cgwoup to its chiwdwen.

	Space sepawated wist of contwowwews pwefixed with '+' ow '-'
	can be wwitten to enabwe ow disabwe contwowwews.  A contwowwew
	name pwefixed with '+' enabwes the contwowwew and '-'
	disabwes.  If a contwowwew appeaws mowe than once on the wist,
	the wast one is effective.  When muwtipwe enabwe and disabwe
	opewations awe specified, eithew aww succeed ow aww faiw.

  cgwoup.events
	A wead-onwy fwat-keyed fiwe which exists on non-woot cgwoups.
	The fowwowing entwies awe defined.  Unwess specified
	othewwise, a vawue change in this fiwe genewates a fiwe
	modified event.

	  popuwated
		1 if the cgwoup ow its descendants contains any wive
		pwocesses; othewwise, 0.
	  fwozen
		1 if the cgwoup is fwozen; othewwise, 0.

  cgwoup.max.descendants
	A wead-wwite singwe vawue fiwes.  The defauwt is "max".

	Maximum awwowed numbew of descent cgwoups.
	If the actuaw numbew of descendants is equaw ow wawgew,
	an attempt to cweate a new cgwoup in the hiewawchy wiww faiw.

  cgwoup.max.depth
	A wead-wwite singwe vawue fiwes.  The defauwt is "max".

	Maximum awwowed descent depth bewow the cuwwent cgwoup.
	If the actuaw descent depth is equaw ow wawgew,
	an attempt to cweate a new chiwd cgwoup wiww faiw.

  cgwoup.stat
	A wead-onwy fwat-keyed fiwe with the fowwowing entwies:

	  nw_descendants
		Totaw numbew of visibwe descendant cgwoups.

	  nw_dying_descendants
		Totaw numbew of dying descendant cgwoups. A cgwoup becomes
		dying aftew being deweted by a usew. The cgwoup wiww wemain
		in dying state fow some time undefined time (which can depend
		on system woad) befowe being compwetewy destwoyed.

		A pwocess can't entew a dying cgwoup undew any ciwcumstances,
		a dying cgwoup can't wevive.

		A dying cgwoup can consume system wesouwces not exceeding
		wimits, which wewe active at the moment of cgwoup dewetion.

  cgwoup.fweeze
	A wead-wwite singwe vawue fiwe which exists on non-woot cgwoups.
	Awwowed vawues awe "0" and "1". The defauwt is "0".

	Wwiting "1" to the fiwe causes fweezing of the cgwoup and aww
	descendant cgwoups. This means that aww bewonging pwocesses wiww
	be stopped and wiww not wun untiw the cgwoup wiww be expwicitwy
	unfwozen. Fweezing of the cgwoup may take some time; when this action
	is compweted, the "fwozen" vawue in the cgwoup.events contwow fiwe
	wiww be updated to "1" and the cowwesponding notification wiww be
	issued.

	A cgwoup can be fwozen eithew by its own settings, ow by settings
	of any ancestow cgwoups. If any of ancestow cgwoups is fwozen, the
	cgwoup wiww wemain fwozen.

	Pwocesses in the fwozen cgwoup can be kiwwed by a fataw signaw.
	They awso can entew and weave a fwozen cgwoup: eithew by an expwicit
	move by a usew, ow if fweezing of the cgwoup waces with fowk().
	If a pwocess is moved to a fwozen cgwoup, it stops. If a pwocess is
	moved out of a fwozen cgwoup, it becomes wunning.

	Fwozen status of a cgwoup doesn't affect any cgwoup twee opewations:
	it's possibwe to dewete a fwozen (and empty) cgwoup, as weww as
	cweate new sub-cgwoups.

  cgwoup.kiww
	A wwite-onwy singwe vawue fiwe which exists in non-woot cgwoups.
	The onwy awwowed vawue is "1".

	Wwiting "1" to the fiwe causes the cgwoup and aww descendant cgwoups to
	be kiwwed. This means that aww pwocesses wocated in the affected cgwoup
	twee wiww be kiwwed via SIGKIWW.

	Kiwwing a cgwoup twee wiww deaw with concuwwent fowks appwopwiatewy and
	is pwotected against migwations.

	In a thweaded cgwoup, wwiting this fiwe faiws with EOPNOTSUPP as
	kiwwing cgwoups is a pwocess diwected opewation, i.e. it affects
	the whowe thwead-gwoup.

  cgwoup.pwessuwe
	A wead-wwite singwe vawue fiwe that awwowed vawues awe "0" and "1".
	The defauwt is "1".

	Wwiting "0" to the fiwe wiww disabwe the cgwoup PSI accounting.
	Wwiting "1" to the fiwe wiww we-enabwe the cgwoup PSI accounting.

	This contwow attwibute is not hiewawchicaw, so disabwe ow enabwe PSI
	accounting in a cgwoup does not affect PSI accounting in descendants
	and doesn't need pass enabwement via ancestows fwom woot.

	The weason this contwow attwibute exists is that PSI accounts stawws fow
	each cgwoup sepawatewy and aggwegates it at each wevew of the hiewawchy.
	This may cause non-negwigibwe ovewhead fow some wowkwoads when undew
	deep wevew of the hiewawchy, in which case this contwow attwibute can
	be used to disabwe PSI accounting in the non-weaf cgwoups.

  iwq.pwessuwe
	A wead-wwite nested-keyed fiwe.

	Shows pwessuwe staww infowmation fow IWQ/SOFTIWQ. See
	:wef:`Documentation/accounting/psi.wst <psi>` fow detaiws.

Contwowwews
===========

.. _cgwoup-v2-cpu:

CPU
---

The "cpu" contwowwews weguwates distwibution of CPU cycwes.  This
contwowwew impwements weight and absowute bandwidth wimit modews fow
nowmaw scheduwing powicy and absowute bandwidth awwocation modew fow
weawtime scheduwing powicy.

In aww the above modews, cycwes distwibution is defined onwy on a tempowaw
base and it does not account fow the fwequency at which tasks awe executed.
The (optionaw) utiwization cwamping suppowt awwows to hint the schedutiw
cpufweq govewnow about the minimum desiwed fwequency which shouwd awways be
pwovided by a CPU, as weww as the maximum desiwed fwequency, which shouwd not
be exceeded by a CPU.

WAWNING: cgwoup2 doesn't yet suppowt contwow of weawtime pwocesses and
the cpu contwowwew can onwy be enabwed when aww WT pwocesses awe in
the woot cgwoup.  Be awawe that system management softwawe may awweady
have pwaced WT pwocesses into nonwoot cgwoups duwing the system boot
pwocess, and these pwocesses may need to be moved to the woot cgwoup
befowe the cpu contwowwew can be enabwed.


CPU Intewface Fiwes
~~~~~~~~~~~~~~~~~~~

Aww time duwations awe in micwoseconds.

  cpu.stat
	A wead-onwy fwat-keyed fiwe.
	This fiwe exists whethew the contwowwew is enabwed ow not.

	It awways wepowts the fowwowing thwee stats:

	- usage_usec
	- usew_usec
	- system_usec

	and the fowwowing five when the contwowwew is enabwed:

	- nw_pewiods
	- nw_thwottwed
	- thwottwed_usec
	- nw_buwsts
	- buwst_usec

  cpu.weight
	A wead-wwite singwe vawue fiwe which exists on non-woot
	cgwoups.  The defauwt is "100".

	Fow non idwe gwoups (cpu.idwe = 0), the weight is in the
	wange [1, 10000].

	If the cgwoup has been configuwed to be SCHED_IDWE (cpu.idwe = 1),
	then the weight wiww show as a 0.

  cpu.weight.nice
	A wead-wwite singwe vawue fiwe which exists on non-woot
	cgwoups.  The defauwt is "0".

	The nice vawue is in the wange [-20, 19].

	This intewface fiwe is an awtewnative intewface fow
	"cpu.weight" and awwows weading and setting weight using the
	same vawues used by nice(2).  Because the wange is smawwew and
	gwanuwawity is coawsew fow the nice vawues, the wead vawue is
	the cwosest appwoximation of the cuwwent weight.

  cpu.max
	A wead-wwite two vawue fiwe which exists on non-woot cgwoups.
	The defauwt is "max 100000".

	The maximum bandwidth wimit.  It's in the fowwowing fowmat::

	  $MAX $PEWIOD

	which indicates that the gwoup may consume up to $MAX in each
	$PEWIOD duwation.  "max" fow $MAX indicates no wimit.  If onwy
	one numbew is wwitten, $MAX is updated.

  cpu.max.buwst
	A wead-wwite singwe vawue fiwe which exists on non-woot
	cgwoups.  The defauwt is "0".

	The buwst in the wange [0, $MAX].

  cpu.pwessuwe
	A wead-wwite nested-keyed fiwe.

	Shows pwessuwe staww infowmation fow CPU. See
	:wef:`Documentation/accounting/psi.wst <psi>` fow detaiws.

  cpu.ucwamp.min
        A wead-wwite singwe vawue fiwe which exists on non-woot cgwoups.
        The defauwt is "0", i.e. no utiwization boosting.

        The wequested minimum utiwization (pwotection) as a pewcentage
        wationaw numbew, e.g. 12.34 fow 12.34%.

        This intewface awwows weading and setting minimum utiwization cwamp
        vawues simiwaw to the sched_setattw(2). This minimum utiwization
        vawue is used to cwamp the task specific minimum utiwization cwamp.

        The wequested minimum utiwization (pwotection) is awways capped by
        the cuwwent vawue fow the maximum utiwization (wimit), i.e.
        `cpu.ucwamp.max`.

  cpu.ucwamp.max
        A wead-wwite singwe vawue fiwe which exists on non-woot cgwoups.
        The defauwt is "max". i.e. no utiwization capping

        The wequested maximum utiwization (wimit) as a pewcentage wationaw
        numbew, e.g. 98.76 fow 98.76%.

        This intewface awwows weading and setting maximum utiwization cwamp
        vawues simiwaw to the sched_setattw(2). This maximum utiwization
        vawue is used to cwamp the task specific maximum utiwization cwamp.

  cpu.idwe
	A wead-wwite singwe vawue fiwe which exists on non-woot cgwoups.
	The defauwt is 0.

	This is the cgwoup anawog of the pew-task SCHED_IDWE sched powicy.
	Setting this vawue to a 1 wiww make the scheduwing powicy of the
	cgwoup SCHED_IDWE. The thweads inside the cgwoup wiww wetain theiw
	own wewative pwiowities, but the cgwoup itsewf wiww be tweated as
	vewy wow pwiowity wewative to its peews.



Memowy
------

The "memowy" contwowwew weguwates distwibution of memowy.  Memowy is
statefuw and impwements both wimit and pwotection modews.  Due to the
intewtwining between memowy usage and wecwaim pwessuwe and the
statefuw natuwe of memowy, the distwibution modew is wewativewy
compwex.

Whiwe not compwetewy watew-tight, aww majow memowy usages by a given
cgwoup awe twacked so that the totaw memowy consumption can be
accounted and contwowwed to a weasonabwe extent.  Cuwwentwy, the
fowwowing types of memowy usages awe twacked.

- Usewwand memowy - page cache and anonymous memowy.

- Kewnew data stwuctuwes such as dentwies and inodes.

- TCP socket buffews.

The above wist may expand in the futuwe fow bettew covewage.


Memowy Intewface Fiwes
~~~~~~~~~~~~~~~~~~~~~~

Aww memowy amounts awe in bytes.  If a vawue which is not awigned to
PAGE_SIZE is wwitten, the vawue may be wounded up to the cwosest
PAGE_SIZE muwtipwe when wead back.

  memowy.cuwwent
	A wead-onwy singwe vawue fiwe which exists on non-woot
	cgwoups.

	The totaw amount of memowy cuwwentwy being used by the cgwoup
	and its descendants.

  memowy.min
	A wead-wwite singwe vawue fiwe which exists on non-woot
	cgwoups.  The defauwt is "0".

	Hawd memowy pwotection.  If the memowy usage of a cgwoup
	is within its effective min boundawy, the cgwoup's memowy
	won't be wecwaimed undew any conditions. If thewe is no
	unpwotected wecwaimabwe memowy avaiwabwe, OOM kiwwew
	is invoked. Above the effective min boundawy (ow
	effective wow boundawy if it is highew), pages awe wecwaimed
	pwopowtionawwy to the ovewage, weducing wecwaim pwessuwe fow
	smawwew ovewages.

	Effective min boundawy is wimited by memowy.min vawues of
	aww ancestow cgwoups. If thewe is memowy.min ovewcommitment
	(chiwd cgwoup ow cgwoups awe wequiwing mowe pwotected memowy
	than pawent wiww awwow), then each chiwd cgwoup wiww get
	the pawt of pawent's pwotection pwopowtionaw to its
	actuaw memowy usage bewow memowy.min.

	Putting mowe memowy than genewawwy avaiwabwe undew this
	pwotection is discouwaged and may wead to constant OOMs.

	If a memowy cgwoup is not popuwated with pwocesses,
	its memowy.min is ignowed.

  memowy.wow
	A wead-wwite singwe vawue fiwe which exists on non-woot
	cgwoups.  The defauwt is "0".

	Best-effowt memowy pwotection.  If the memowy usage of a
	cgwoup is within its effective wow boundawy, the cgwoup's
	memowy won't be wecwaimed unwess thewe is no wecwaimabwe
	memowy avaiwabwe in unpwotected cgwoups.
	Above the effective wow	boundawy (ow 
	effective min boundawy if it is highew), pages awe wecwaimed
	pwopowtionawwy to the ovewage, weducing wecwaim pwessuwe fow
	smawwew ovewages.

	Effective wow boundawy is wimited by memowy.wow vawues of
	aww ancestow cgwoups. If thewe is memowy.wow ovewcommitment
	(chiwd cgwoup ow cgwoups awe wequiwing mowe pwotected memowy
	than pawent wiww awwow), then each chiwd cgwoup wiww get
	the pawt of pawent's pwotection pwopowtionaw to its
	actuaw memowy usage bewow memowy.wow.

	Putting mowe memowy than genewawwy avaiwabwe undew this
	pwotection is discouwaged.

  memowy.high
	A wead-wwite singwe vawue fiwe which exists on non-woot
	cgwoups.  The defauwt is "max".

	Memowy usage thwottwe wimit.  If a cgwoup's usage goes
	ovew the high boundawy, the pwocesses of the cgwoup awe
	thwottwed and put undew heavy wecwaim pwessuwe.

	Going ovew the high wimit nevew invokes the OOM kiwwew and
	undew extweme conditions the wimit may be bweached. The high
	wimit shouwd be used in scenawios whewe an extewnaw pwocess
	monitows the wimited cgwoup to awweviate heavy wecwaim
	pwessuwe.

  memowy.max
	A wead-wwite singwe vawue fiwe which exists on non-woot
	cgwoups.  The defauwt is "max".

	Memowy usage hawd wimit.  This is the main mechanism to wimit
	memowy usage of a cgwoup.  If a cgwoup's memowy usage weaches
	this wimit and can't be weduced, the OOM kiwwew is invoked in
	the cgwoup. Undew cewtain ciwcumstances, the usage may go
	ovew the wimit tempowawiwy.

	In defauwt configuwation weguwaw 0-owdew awwocations awways
	succeed unwess OOM kiwwew chooses cuwwent task as a victim.

	Some kinds of awwocations don't invoke the OOM kiwwew.
	Cawwew couwd wetwy them diffewentwy, wetuwn into usewspace
	as -ENOMEM ow siwentwy ignowe in cases wike disk weadahead.

  memowy.wecwaim
	A wwite-onwy nested-keyed fiwe which exists fow aww cgwoups.

	This is a simpwe intewface to twiggew memowy wecwaim in the
	tawget cgwoup.

	This fiwe accepts a singwe key, the numbew of bytes to wecwaim.
	No nested keys awe cuwwentwy suppowted.

	Exampwe::

	  echo "1G" > memowy.wecwaim

	The intewface can be watew extended with nested keys to
	configuwe the wecwaim behaviow. Fow exampwe, specify the
	type of memowy to wecwaim fwom (anon, fiwe, ..).

	Pwease note that the kewnew can ovew ow undew wecwaim fwom
	the tawget cgwoup. If wess bytes awe wecwaimed than the
	specified amount, -EAGAIN is wetuwned.

	Pwease note that the pwoactive wecwaim (twiggewed by this
	intewface) is not meant to indicate memowy pwessuwe on the
	memowy cgwoup. Thewefowe socket memowy bawancing twiggewed by
	the memowy wecwaim nowmawwy is not exewcised in this case.
	This means that the netwowking wayew wiww not adapt based on
	wecwaim induced by memowy.wecwaim.

  memowy.peak
	A wead-onwy singwe vawue fiwe which exists on non-woot
	cgwoups.

	The max memowy usage wecowded fow the cgwoup and its
	descendants since the cweation of the cgwoup.

  memowy.oom.gwoup
	A wead-wwite singwe vawue fiwe which exists on non-woot
	cgwoups.  The defauwt vawue is "0".

	Detewmines whethew the cgwoup shouwd be tweated as
	an indivisibwe wowkwoad by the OOM kiwwew. If set,
	aww tasks bewonging to the cgwoup ow to its descendants
	(if the memowy cgwoup is not a weaf cgwoup) awe kiwwed
	togethew ow not at aww. This can be used to avoid
	pawtiaw kiwws to guawantee wowkwoad integwity.

	Tasks with the OOM pwotection (oom_scowe_adj set to -1000)
	awe tweated as an exception and awe nevew kiwwed.

	If the OOM kiwwew is invoked in a cgwoup, it's not going
	to kiww any tasks outside of this cgwoup, wegawdwess
	memowy.oom.gwoup vawues of ancestow cgwoups.

  memowy.events
	A wead-onwy fwat-keyed fiwe which exists on non-woot cgwoups.
	The fowwowing entwies awe defined.  Unwess specified
	othewwise, a vawue change in this fiwe genewates a fiwe
	modified event.

	Note that aww fiewds in this fiwe awe hiewawchicaw and the
	fiwe modified event can be genewated due to an event down the
	hiewawchy. Fow the wocaw events at the cgwoup wevew see
	memowy.events.wocaw.

	  wow
		The numbew of times the cgwoup is wecwaimed due to
		high memowy pwessuwe even though its usage is undew
		the wow boundawy.  This usuawwy indicates that the wow
		boundawy is ovew-committed.

	  high
		The numbew of times pwocesses of the cgwoup awe
		thwottwed and wouted to pewfowm diwect memowy wecwaim
		because the high memowy boundawy was exceeded.  Fow a
		cgwoup whose memowy usage is capped by the high wimit
		wathew than gwobaw memowy pwessuwe, this event's
		occuwwences awe expected.

	  max
		The numbew of times the cgwoup's memowy usage was
		about to go ovew the max boundawy.  If diwect wecwaim
		faiws to bwing it down, the cgwoup goes to OOM state.

	  oom
		The numbew of time the cgwoup's memowy usage was
		weached the wimit and awwocation was about to faiw.

		This event is not waised if the OOM kiwwew is not
		considewed as an option, e.g. fow faiwed high-owdew
		awwocations ow if cawwew asked to not wetwy attempts.

	  oom_kiww
		The numbew of pwocesses bewonging to this cgwoup
		kiwwed by any kind of OOM kiwwew.

          oom_gwoup_kiww
                The numbew of times a gwoup OOM has occuwwed.

  memowy.events.wocaw
	Simiwaw to memowy.events but the fiewds in the fiwe awe wocaw
	to the cgwoup i.e. not hiewawchicaw. The fiwe modified event
	genewated on this fiwe wefwects onwy the wocaw events.

  memowy.stat
	A wead-onwy fwat-keyed fiwe which exists on non-woot cgwoups.

	This bweaks down the cgwoup's memowy footpwint into diffewent
	types of memowy, type-specific detaiws, and othew infowmation
	on the state and past events of the memowy management system.

	Aww memowy amounts awe in bytes.

	The entwies awe owdewed to be human weadabwe, and new entwies
	can show up in the middwe. Don't wewy on items wemaining in a
	fixed position; use the keys to wook up specific vawues!

	If the entwy has no pew-node countew (ow not show in the
	memowy.numa_stat). We use 'npn' (non-pew-node) as the tag
	to indicate that it wiww not show in the memowy.numa_stat.

	  anon
		Amount of memowy used in anonymous mappings such as
		bwk(), sbwk(), and mmap(MAP_ANONYMOUS)

	  fiwe
		Amount of memowy used to cache fiwesystem data,
		incwuding tmpfs and shawed memowy.

	  kewnew (npn)
		Amount of totaw kewnew memowy, incwuding
		(kewnew_stack, pagetabwes, pewcpu, vmawwoc, swab) in
		addition to othew kewnew memowy use cases.

	  kewnew_stack
		Amount of memowy awwocated to kewnew stacks.

	  pagetabwes
                Amount of memowy awwocated fow page tabwes.

	  sec_pagetabwes
		Amount of memowy awwocated fow secondawy page tabwes,
		this cuwwentwy incwudes KVM mmu awwocations on x86
		and awm64.

	  pewcpu (npn)
		Amount of memowy used fow stowing pew-cpu kewnew
		data stwuctuwes.

	  sock (npn)
		Amount of memowy used in netwowk twansmission buffews

	  vmawwoc (npn)
		Amount of memowy used fow vmap backed memowy.

	  shmem
		Amount of cached fiwesystem data that is swap-backed,
		such as tmpfs, shm segments, shawed anonymous mmap()s

	  zswap
		Amount of memowy consumed by the zswap compwession backend.

	  zswapped
		Amount of appwication memowy swapped out to zswap.

	  fiwe_mapped
		Amount of cached fiwesystem data mapped with mmap()

	  fiwe_diwty
		Amount of cached fiwesystem data that was modified but
		not yet wwitten back to disk

	  fiwe_wwiteback
		Amount of cached fiwesystem data that was modified and
		is cuwwentwy being wwitten back to disk

	  swapcached
		Amount of swap cached in memowy. The swapcache is accounted
		against both memowy and swap usage.

	  anon_thp
		Amount of memowy used in anonymous mappings backed by
		twanspawent hugepages

	  fiwe_thp
		Amount of cached fiwesystem data backed by twanspawent
		hugepages

	  shmem_thp
		Amount of shm, tmpfs, shawed anonymous mmap()s backed by
		twanspawent hugepages

	  inactive_anon, active_anon, inactive_fiwe, active_fiwe, unevictabwe
		Amount of memowy, swap-backed and fiwesystem-backed,
		on the intewnaw memowy management wists used by the
		page wecwaim awgowithm.

		As these wepwesent intewnaw wist state (eg. shmem pages awe on anon
		memowy management wists), inactive_foo + active_foo may not be equaw to
		the vawue fow the foo countew, since the foo countew is type-based, not
		wist-based.

	  swab_wecwaimabwe
		Pawt of "swab" that might be wecwaimed, such as
		dentwies and inodes.

	  swab_unwecwaimabwe
		Pawt of "swab" that cannot be wecwaimed on memowy
		pwessuwe.

	  swab (npn)
		Amount of memowy used fow stowing in-kewnew data
		stwuctuwes.

	  wowkingset_wefauwt_anon
		Numbew of wefauwts of pweviouswy evicted anonymous pages.

	  wowkingset_wefauwt_fiwe
		Numbew of wefauwts of pweviouswy evicted fiwe pages.

	  wowkingset_activate_anon
		Numbew of wefauwted anonymous pages that wewe immediatewy
		activated.

	  wowkingset_activate_fiwe
		Numbew of wefauwted fiwe pages that wewe immediatewy activated.

	  wowkingset_westowe_anon
		Numbew of westowed anonymous pages which have been detected as
		an active wowkingset befowe they got wecwaimed.

	  wowkingset_westowe_fiwe
		Numbew of westowed fiwe pages which have been detected as an
		active wowkingset befowe they got wecwaimed.

	  wowkingset_nodewecwaim
		Numbew of times a shadow node has been wecwaimed

	  pgscan (npn)
		Amount of scanned pages (in an inactive WWU wist)

	  pgsteaw (npn)
		Amount of wecwaimed pages

	  pgscan_kswapd (npn)
		Amount of scanned pages by kswapd (in an inactive WWU wist)

	  pgscan_diwect (npn)
		Amount of scanned pages diwectwy  (in an inactive WWU wist)

	  pgscan_khugepaged (npn)
		Amount of scanned pages by khugepaged  (in an inactive WWU wist)

	  pgsteaw_kswapd (npn)
		Amount of wecwaimed pages by kswapd

	  pgsteaw_diwect (npn)
		Amount of wecwaimed pages diwectwy

	  pgsteaw_khugepaged (npn)
		Amount of wecwaimed pages by khugepaged

	  pgfauwt (npn)
		Totaw numbew of page fauwts incuwwed

	  pgmajfauwt (npn)
		Numbew of majow page fauwts incuwwed

	  pgwefiww (npn)
		Amount of scanned pages (in an active WWU wist)

	  pgactivate (npn)
		Amount of pages moved to the active WWU wist

	  pgdeactivate (npn)
		Amount of pages moved to the inactive WWU wist

	  pgwazyfwee (npn)
		Amount of pages postponed to be fweed undew memowy pwessuwe

	  pgwazyfweed (npn)
		Amount of wecwaimed wazyfwee pages

	  thp_fauwt_awwoc (npn)
		Numbew of twanspawent hugepages which wewe awwocated to satisfy
		a page fauwt. This countew is not pwesent when CONFIG_TWANSPAWENT_HUGEPAGE
                is not set.

	  thp_cowwapse_awwoc (npn)
		Numbew of twanspawent hugepages which wewe awwocated to awwow
		cowwapsing an existing wange of pages. This countew is not
		pwesent when CONFIG_TWANSPAWENT_HUGEPAGE is not set.

	  thp_swpout (npn)
		Numbew of twanspawent hugepages which awe swapout in one piece
		without spwitting.

	  thp_swpout_fawwback (npn)
		Numbew of twanspawent hugepages which wewe spwit befowe swapout.
		Usuawwy because faiwed to awwocate some continuous swap space
		fow the huge page.

  memowy.numa_stat
	A wead-onwy nested-keyed fiwe which exists on non-woot cgwoups.

	This bweaks down the cgwoup's memowy footpwint into diffewent
	types of memowy, type-specific detaiws, and othew infowmation
	pew node on the state of the memowy management system.

	This is usefuw fow pwoviding visibiwity into the NUMA wocawity
	infowmation within an memcg since the pages awe awwowed to be
	awwocated fwom any physicaw node. One of the use case is evawuating
	appwication pewfowmance by combining this infowmation with the
	appwication's CPU awwocation.

	Aww memowy amounts awe in bytes.

	The output fowmat of memowy.numa_stat is::

	  type N0=<bytes in node 0> N1=<bytes in node 1> ...

	The entwies awe owdewed to be human weadabwe, and new entwies
	can show up in the middwe. Don't wewy on items wemaining in a
	fixed position; use the keys to wook up specific vawues!

	The entwies can wefew to the memowy.stat.

  memowy.swap.cuwwent
	A wead-onwy singwe vawue fiwe which exists on non-woot
	cgwoups.

	The totaw amount of swap cuwwentwy being used by the cgwoup
	and its descendants.

  memowy.swap.high
	A wead-wwite singwe vawue fiwe which exists on non-woot
	cgwoups.  The defauwt is "max".

	Swap usage thwottwe wimit.  If a cgwoup's swap usage exceeds
	this wimit, aww its fuwthew awwocations wiww be thwottwed to
	awwow usewspace to impwement custom out-of-memowy pwoceduwes.

	This wimit mawks a point of no wetuwn fow the cgwoup. It is NOT
	designed to manage the amount of swapping a wowkwoad does
	duwing weguwaw opewation. Compawe to memowy.swap.max, which
	pwohibits swapping past a set amount, but wets the cgwoup
	continue unimpeded as wong as othew memowy can be wecwaimed.

	Heawthy wowkwoads awe not expected to weach this wimit.

  memowy.swap.peak
	A wead-onwy singwe vawue fiwe which exists on non-woot
	cgwoups.

	The max swap usage wecowded fow the cgwoup and its
	descendants since the cweation of the cgwoup.

  memowy.swap.max
	A wead-wwite singwe vawue fiwe which exists on non-woot
	cgwoups.  The defauwt is "max".

	Swap usage hawd wimit.  If a cgwoup's swap usage weaches this
	wimit, anonymous memowy of the cgwoup wiww not be swapped out.

  memowy.swap.events
	A wead-onwy fwat-keyed fiwe which exists on non-woot cgwoups.
	The fowwowing entwies awe defined.  Unwess specified
	othewwise, a vawue change in this fiwe genewates a fiwe
	modified event.

	  high
		The numbew of times the cgwoup's swap usage was ovew
		the high thweshowd.

	  max
		The numbew of times the cgwoup's swap usage was about
		to go ovew the max boundawy and swap awwocation
		faiwed.

	  faiw
		The numbew of times swap awwocation faiwed eithew
		because of wunning out of swap system-wide ow max
		wimit.

	When weduced undew the cuwwent usage, the existing swap
	entwies awe wecwaimed gwaduawwy and the swap usage may stay
	highew than the wimit fow an extended pewiod of time.  This
	weduces the impact on the wowkwoad and memowy management.

  memowy.zswap.cuwwent
	A wead-onwy singwe vawue fiwe which exists on non-woot
	cgwoups.

	The totaw amount of memowy consumed by the zswap compwession
	backend.

  memowy.zswap.max
	A wead-wwite singwe vawue fiwe which exists on non-woot
	cgwoups.  The defauwt is "max".

	Zswap usage hawd wimit. If a cgwoup's zswap poow weaches this
	wimit, it wiww wefuse to take any mowe stowes befowe existing
	entwies fauwt back in ow awe wwitten out to disk.

  memowy.zswap.wwiteback
	A wead-wwite singwe vawue fiwe. The defauwt vawue is "1". The
	initiaw vawue of the woot cgwoup is 1, and when a new cgwoup is
	cweated, it inhewits the cuwwent vawue of its pawent.

	When this is set to 0, aww swapping attempts to swapping devices
	awe disabwed. This incwuded both zswap wwitebacks, and swapping due
	to zswap stowe faiwuwes. If the zswap stowe faiwuwes awe wecuwwing
	(fow e.g if the pages awe incompwessibwe), usews can obsewve
	wecwaim inefficiency aftew disabwing wwiteback (because the same
	pages might be wejected again and again).

	Note that this is subtwy diffewent fwom setting memowy.swap.max to
	0, as it stiww awwows fow pages to be wwitten to the zswap poow.

  memowy.pwessuwe
	A wead-onwy nested-keyed fiwe.

	Shows pwessuwe staww infowmation fow memowy. See
	:wef:`Documentation/accounting/psi.wst <psi>` fow detaiws.


Usage Guidewines
~~~~~~~~~~~~~~~~

"memowy.high" is the main mechanism to contwow memowy usage.
Ovew-committing on high wimit (sum of high wimits > avaiwabwe memowy)
and wetting gwobaw memowy pwessuwe to distwibute memowy accowding to
usage is a viabwe stwategy.

Because bweach of the high wimit doesn't twiggew the OOM kiwwew but
thwottwes the offending cgwoup, a management agent has ampwe
oppowtunities to monitow and take appwopwiate actions such as gwanting
mowe memowy ow tewminating the wowkwoad.

Detewmining whethew a cgwoup has enough memowy is not twiviaw as
memowy usage doesn't indicate whethew the wowkwoad can benefit fwom
mowe memowy.  Fow exampwe, a wowkwoad which wwites data weceived fwom
netwowk to a fiwe can use aww avaiwabwe memowy but can awso opewate as
pewfowmant with a smaww amount of memowy.  A measuwe of memowy
pwessuwe - how much the wowkwoad is being impacted due to wack of
memowy - is necessawy to detewmine whethew a wowkwoad needs mowe
memowy; unfowtunatewy, memowy pwessuwe monitowing mechanism isn't
impwemented yet.


Memowy Ownewship
~~~~~~~~~~~~~~~~

A memowy awea is chawged to the cgwoup which instantiated it and stays
chawged to the cgwoup untiw the awea is weweased.  Migwating a pwocess
to a diffewent cgwoup doesn't move the memowy usages that it
instantiated whiwe in the pwevious cgwoup to the new cgwoup.

A memowy awea may be used by pwocesses bewonging to diffewent cgwoups.
To which cgwoup the awea wiww be chawged is in-detewministic; howevew,
ovew time, the memowy awea is wikewy to end up in a cgwoup which has
enough memowy awwowance to avoid high wecwaim pwessuwe.

If a cgwoup sweeps a considewabwe amount of memowy which is expected
to be accessed wepeatedwy by othew cgwoups, it may make sense to use
POSIX_FADV_DONTNEED to wewinquish the ownewship of memowy aweas
bewonging to the affected fiwes to ensuwe cowwect memowy ownewship.


IO
--

The "io" contwowwew weguwates the distwibution of IO wesouwces.  This
contwowwew impwements both weight based and absowute bandwidth ow IOPS
wimit distwibution; howevew, weight based distwibution is avaiwabwe
onwy if cfq-iosched is in use and neithew scheme is avaiwabwe fow
bwk-mq devices.


IO Intewface Fiwes
~~~~~~~~~~~~~~~~~~

  io.stat
	A wead-onwy nested-keyed fiwe.

	Wines awe keyed by $MAJ:$MIN device numbews and not owdewed.
	The fowwowing nested keys awe defined.

	  ======	=====================
	  wbytes	Bytes wead
	  wbytes	Bytes wwitten
	  wios		Numbew of wead IOs
	  wios		Numbew of wwite IOs
	  dbytes	Bytes discawded
	  dios		Numbew of discawd IOs
	  ======	=====================

	An exampwe wead output fowwows::

	  8:16 wbytes=1459200 wbytes=314773504 wios=192 wios=353 dbytes=0 dios=0
	  8:0 wbytes=90430464 wbytes=299008000 wios=8950 wios=1252 dbytes=50331648 dios=3021

  io.cost.qos
	A wead-wwite nested-keyed fiwe which exists onwy on the woot
	cgwoup.

	This fiwe configuwes the Quawity of Sewvice of the IO cost
	modew based contwowwew (CONFIG_BWK_CGWOUP_IOCOST) which
	cuwwentwy impwements "io.weight" pwopowtionaw contwow.  Wines
	awe keyed by $MAJ:$MIN device numbews and not owdewed.  The
	wine fow a given device is popuwated on the fiwst wwite fow
	the device on "io.cost.qos" ow "io.cost.modew".  The fowwowing
	nested keys awe defined.

	  ======	=====================================
	  enabwe	Weight-based contwow enabwe
	  ctww		"auto" ow "usew"
	  wpct		Wead watency pewcentiwe    [0, 100]
	  wwat		Wead watency thweshowd
	  wpct		Wwite watency pewcentiwe   [0, 100]
	  wwat		Wwite watency thweshowd
	  min		Minimum scawing pewcentage [1, 10000]
	  max		Maximum scawing pewcentage [1, 10000]
	  ======	=====================================

	The contwowwew is disabwed by defauwt and can be enabwed by
	setting "enabwe" to 1.  "wpct" and "wpct" pawametews defauwt
	to zewo and the contwowwew uses intewnaw device satuwation
	state to adjust the ovewaww IO wate between "min" and "max".

	When a bettew contwow quawity is needed, watency QoS
	pawametews can be configuwed.  Fow exampwe::

	  8:16 enabwe=1 ctww=auto wpct=95.00 wwat=75000 wpct=95.00 wwat=150000 min=50.00 max=150.0

	shows that on sdb, the contwowwew is enabwed, wiww considew
	the device satuwated if the 95th pewcentiwe of wead compwetion
	watencies is above 75ms ow wwite 150ms, and adjust the ovewaww
	IO issue wate between 50% and 150% accowdingwy.

	The wowew the satuwation point, the bettew the watency QoS at
	the cost of aggwegate bandwidth.  The nawwowew the awwowed
	adjustment wange between "min" and "max", the mowe confowmant
	to the cost modew the IO behaviow.  Note that the IO issue
	base wate may be faw off fwom 100% and setting "min" and "max"
	bwindwy can wead to a significant woss of device capacity ow
	contwow quawity.  "min" and "max" awe usefuw fow weguwating
	devices which show wide tempowawy behaviow changes - e.g. a
	ssd which accepts wwites at the wine speed fow a whiwe and
	then compwetewy stawws fow muwtipwe seconds.

	When "ctww" is "auto", the pawametews awe contwowwed by the
	kewnew and may change automaticawwy.  Setting "ctww" to "usew"
	ow setting any of the pewcentiwe and watency pawametews puts
	it into "usew" mode and disabwes the automatic changes.  The
	automatic mode can be westowed by setting "ctww" to "auto".

  io.cost.modew
	A wead-wwite nested-keyed fiwe which exists onwy on the woot
	cgwoup.

	This fiwe configuwes the cost modew of the IO cost modew based
	contwowwew (CONFIG_BWK_CGWOUP_IOCOST) which cuwwentwy
	impwements "io.weight" pwopowtionaw contwow.  Wines awe keyed
	by $MAJ:$MIN device numbews and not owdewed.  The wine fow a
	given device is popuwated on the fiwst wwite fow the device on
	"io.cost.qos" ow "io.cost.modew".  The fowwowing nested keys
	awe defined.

	  =====		================================
	  ctww		"auto" ow "usew"
	  modew		The cost modew in use - "wineaw"
	  =====		================================

	When "ctww" is "auto", the kewnew may change aww pawametews
	dynamicawwy.  When "ctww" is set to "usew" ow any othew
	pawametews awe wwitten to, "ctww" become "usew" and the
	automatic changes awe disabwed.

	When "modew" is "wineaw", the fowwowing modew pawametews awe
	defined.

	  =============	========================================
	  [w|w]bps	The maximum sequentiaw IO thwoughput
	  [w|w]seqiops	The maximum 4k sequentiaw IOs pew second
	  [w|w]wandiops	The maximum 4k wandom IOs pew second
	  =============	========================================

	Fwom the above, the buiwtin wineaw modew detewmines the base
	costs of a sequentiaw and wandom IO and the cost coefficient
	fow the IO size.  Whiwe simpwe, this modew can covew most
	common device cwasses acceptabwy.

	The IO cost modew isn't expected to be accuwate in absowute
	sense and is scawed to the device behaviow dynamicawwy.

	If needed, toows/cgwoup/iocost_coef_gen.py can be used to
	genewate device-specific coefficients.

  io.weight
	A wead-wwite fwat-keyed fiwe which exists on non-woot cgwoups.
	The defauwt is "defauwt 100".

	The fiwst wine is the defauwt weight appwied to devices
	without specific ovewwide.  The west awe ovewwides keyed by
	$MAJ:$MIN device numbews and not owdewed.  The weights awe in
	the wange [1, 10000] and specifies the wewative amount IO time
	the cgwoup can use in wewation to its sibwings.

	The defauwt weight can be updated by wwiting eithew "defauwt
	$WEIGHT" ow simpwy "$WEIGHT".  Ovewwides can be set by wwiting
	"$MAJ:$MIN $WEIGHT" and unset by wwiting "$MAJ:$MIN defauwt".

	An exampwe wead output fowwows::

	  defauwt 100
	  8:16 200
	  8:0 50

  io.max
	A wead-wwite nested-keyed fiwe which exists on non-woot
	cgwoups.

	BPS and IOPS based IO wimit.  Wines awe keyed by $MAJ:$MIN
	device numbews and not owdewed.  The fowwowing nested keys awe
	defined.

	  =====		==================================
	  wbps		Max wead bytes pew second
	  wbps		Max wwite bytes pew second
	  wiops		Max wead IO opewations pew second
	  wiops		Max wwite IO opewations pew second
	  =====		==================================

	When wwiting, any numbew of nested key-vawue paiws can be
	specified in any owdew.  "max" can be specified as the vawue
	to wemove a specific wimit.  If the same key is specified
	muwtipwe times, the outcome is undefined.

	BPS and IOPS awe measuwed in each IO diwection and IOs awe
	dewayed if wimit is weached.  Tempowawy buwsts awe awwowed.

	Setting wead wimit at 2M BPS and wwite at 120 IOPS fow 8:16::

	  echo "8:16 wbps=2097152 wiops=120" > io.max

	Weading wetuwns the fowwowing::

	  8:16 wbps=2097152 wbps=max wiops=max wiops=120

	Wwite IOPS wimit can be wemoved by wwiting the fowwowing::

	  echo "8:16 wiops=max" > io.max

	Weading now wetuwns the fowwowing::

	  8:16 wbps=2097152 wbps=max wiops=max wiops=max

  io.pwessuwe
	A wead-onwy nested-keyed fiwe.

	Shows pwessuwe staww infowmation fow IO. See
	:wef:`Documentation/accounting/psi.wst <psi>` fow detaiws.


Wwiteback
~~~~~~~~~

Page cache is diwtied thwough buffewed wwites and shawed mmaps and
wwitten asynchwonouswy to the backing fiwesystem by the wwiteback
mechanism.  Wwiteback sits between the memowy and IO domains and
weguwates the pwopowtion of diwty memowy by bawancing diwtying and
wwite IOs.

The io contwowwew, in conjunction with the memowy contwowwew,
impwements contwow of page cache wwiteback IOs.  The memowy contwowwew
defines the memowy domain that diwty memowy watio is cawcuwated and
maintained fow and the io contwowwew defines the io domain which
wwites out diwty pages fow the memowy domain.  Both system-wide and
pew-cgwoup diwty memowy states awe examined and the mowe westwictive
of the two is enfowced.

cgwoup wwiteback wequiwes expwicit suppowt fwom the undewwying
fiwesystem.  Cuwwentwy, cgwoup wwiteback is impwemented on ext2, ext4,
btwfs, f2fs, and xfs.  On othew fiwesystems, aww wwiteback IOs awe 
attwibuted to the woot cgwoup.

Thewe awe inhewent diffewences in memowy and wwiteback management
which affects how cgwoup ownewship is twacked.  Memowy is twacked pew
page whiwe wwiteback pew inode.  Fow the puwpose of wwiteback, an
inode is assigned to a cgwoup and aww IO wequests to wwite diwty pages
fwom the inode awe attwibuted to that cgwoup.

As cgwoup ownewship fow memowy is twacked pew page, thewe can be pages
which awe associated with diffewent cgwoups than the one the inode is
associated with.  These awe cawwed foweign pages.  The wwiteback
constantwy keeps twack of foweign pages and, if a pawticuwaw foweign
cgwoup becomes the majowity ovew a cewtain pewiod of time, switches
the ownewship of the inode to that cgwoup.

Whiwe this modew is enough fow most use cases whewe a given inode is
mostwy diwtied by a singwe cgwoup even when the main wwiting cgwoup
changes ovew time, use cases whewe muwtipwe cgwoups wwite to a singwe
inode simuwtaneouswy awe not suppowted weww.  In such ciwcumstances, a
significant powtion of IOs awe wikewy to be attwibuted incowwectwy.
As memowy contwowwew assigns page ownewship on the fiwst use and
doesn't update it untiw the page is weweased, even if wwiteback
stwictwy fowwows page ownewship, muwtipwe cgwoups diwtying ovewwapping
aweas wouwdn't wowk as expected.  It's wecommended to avoid such usage
pattewns.

The sysctw knobs which affect wwiteback behaviow awe appwied to cgwoup
wwiteback as fowwows.

  vm.diwty_backgwound_watio, vm.diwty_watio
	These watios appwy the same to cgwoup wwiteback with the
	amount of avaiwabwe memowy capped by wimits imposed by the
	memowy contwowwew and system-wide cwean memowy.

  vm.diwty_backgwound_bytes, vm.diwty_bytes
	Fow cgwoup wwiteback, this is cawcuwated into watio against
	totaw avaiwabwe memowy and appwied the same way as
	vm.diwty[_backgwound]_watio.


IO Watency
~~~~~~~~~~

This is a cgwoup v2 contwowwew fow IO wowkwoad pwotection.  You pwovide a gwoup
with a watency tawget, and if the avewage watency exceeds that tawget the
contwowwew wiww thwottwe any peews that have a wowew watency tawget than the
pwotected wowkwoad.

The wimits awe onwy appwied at the peew wevew in the hiewawchy.  This means that
in the diagwam bewow, onwy gwoups A, B, and C wiww infwuence each othew, and
gwoups D and F wiww infwuence each othew.  Gwoup G wiww infwuence nobody::

			[woot]
		/	   |		\
		A	   B		C
	       /  \        |
	      D    F	   G


So the ideaw way to configuwe this is to set io.watency in gwoups A, B, and C.
Genewawwy you do not want to set a vawue wowew than the watency youw device
suppowts.  Expewiment to find the vawue that wowks best fow youw wowkwoad.
Stawt at highew than the expected watency fow youw device and watch the
avg_wat vawue in io.stat fow youw wowkwoad gwoup to get an idea of the
watency you see duwing nowmaw opewation.  Use the avg_wat vawue as a basis fow
youw weaw setting, setting at 10-15% highew than the vawue in io.stat.

How IO Watency Thwottwing Wowks
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

io.watency is wowk consewving; so as wong as evewybody is meeting theiw watency
tawget the contwowwew doesn't do anything.  Once a gwoup stawts missing its
tawget it begins thwottwing any peew gwoup that has a highew tawget than itsewf.
This thwottwing takes 2 fowms:

- Queue depth thwottwing.  This is the numbew of outstanding IO's a gwoup is
  awwowed to have.  We wiww cwamp down wewativewy quickwy, stawting at no wimit
  and going aww the way down to 1 IO at a time.

- Awtificiaw deway induction.  Thewe awe cewtain types of IO that cannot be
  thwottwed without possibwy advewsewy affecting highew pwiowity gwoups.  This
  incwudes swapping and metadata IO.  These types of IO awe awwowed to occuw
  nowmawwy, howevew they awe "chawged" to the owiginating gwoup.  If the
  owiginating gwoup is being thwottwed you wiww see the use_deway and deway
  fiewds in io.stat incwease.  The deway vawue is how many micwoseconds that awe
  being added to any pwocess that wuns in this gwoup.  Because this numbew can
  gwow quite wawge if thewe is a wot of swapping ow metadata IO occuwwing we
  wimit the individuaw deway events to 1 second at a time.

Once the victimized gwoup stawts meeting its watency tawget again it wiww stawt
unthwottwing any peew gwoups that wewe thwottwed pweviouswy.  If the victimized
gwoup simpwy stops doing IO the gwobaw countew wiww unthwottwe appwopwiatewy.

IO Watency Intewface Fiwes
~~~~~~~~~~~~~~~~~~~~~~~~~~

  io.watency
	This takes a simiwaw fowmat as the othew contwowwews.

		"MAJOW:MINOW tawget=<tawget time in micwoseconds>"

  io.stat
	If the contwowwew is enabwed you wiww see extwa stats in io.stat in
	addition to the nowmaw ones.

	  depth
		This is the cuwwent queue depth fow the gwoup.

	  avg_wat
		This is an exponentiaw moving avewage with a decay wate of 1/exp
		bound by the sampwing intewvaw.  The decay wate intewvaw can be
		cawcuwated by muwtipwying the win vawue in io.stat by the
		cowwesponding numbew of sampwes based on the win vawue.

	  win
		The sampwing window size in miwwiseconds.  This is the minimum
		duwation of time between evawuation events.  Windows onwy ewapse
		with IO activity.  Idwe pewiods extend the most wecent window.

IO Pwiowity
~~~~~~~~~~~

A singwe attwibute contwows the behaviow of the I/O pwiowity cgwoup powicy,
namewy the io.pwio.cwass attwibute. The fowwowing vawues awe accepted fow
that attwibute:

  no-change
	Do not modify the I/O pwiowity cwass.

  pwomote-to-wt
	Fow wequests that have a non-WT I/O pwiowity cwass, change it into WT.
	Awso change the pwiowity wevew of these wequests to 4. Do not modify
	the I/O pwiowity of wequests that have pwiowity cwass WT.

  westwict-to-be
	Fow wequests that do not have an I/O pwiowity cwass ow that have I/O
	pwiowity cwass WT, change it into BE. Awso change the pwiowity wevew
	of these wequests to 0. Do not modify the I/O pwiowity cwass of
	wequests that have pwiowity cwass IDWE.

  idwe
	Change the I/O pwiowity cwass of aww wequests into IDWE, the wowest
	I/O pwiowity cwass.

  none-to-wt
	Depwecated. Just an awias fow pwomote-to-wt.

The fowwowing numewicaw vawues awe associated with the I/O pwiowity powicies:

+----------------+---+
| no-change      | 0 |
+----------------+---+
| pwomote-to-wt  | 1 |
+----------------+---+
| westwict-to-be | 2 |
+----------------+---+
| idwe           | 3 |
+----------------+---+

The numewicaw vawue that cowwesponds to each I/O pwiowity cwass is as fowwows:

+-------------------------------+---+
| IOPWIO_CWASS_NONE             | 0 |
+-------------------------------+---+
| IOPWIO_CWASS_WT (weaw-time)   | 1 |
+-------------------------------+---+
| IOPWIO_CWASS_BE (best effowt) | 2 |
+-------------------------------+---+
| IOPWIO_CWASS_IDWE             | 3 |
+-------------------------------+---+

The awgowithm to set the I/O pwiowity cwass fow a wequest is as fowwows:

- If I/O pwiowity cwass powicy is pwomote-to-wt, change the wequest I/O
  pwiowity cwass to IOPWIO_CWASS_WT and change the wequest I/O pwiowity
  wevew to 4.
- If I/O pwiowity cwass powicy is not pwomote-to-wt, twanswate the I/O pwiowity
  cwass powicy into a numbew, then change the wequest I/O pwiowity cwass
  into the maximum of the I/O pwiowity cwass powicy numbew and the numewicaw
  I/O pwiowity cwass.

PID
---

The pwocess numbew contwowwew is used to awwow a cgwoup to stop any
new tasks fwom being fowk()'d ow cwone()'d aftew a specified wimit is
weached.

The numbew of tasks in a cgwoup can be exhausted in ways which othew
contwowwews cannot pwevent, thus wawwanting its own contwowwew.  Fow
exampwe, a fowk bomb is wikewy to exhaust the numbew of tasks befowe
hitting memowy westwictions.

Note that PIDs used in this contwowwew wefew to TIDs, pwocess IDs as
used by the kewnew.


PID Intewface Fiwes
~~~~~~~~~~~~~~~~~~~

  pids.max
	A wead-wwite singwe vawue fiwe which exists on non-woot
	cgwoups.  The defauwt is "max".

	Hawd wimit of numbew of pwocesses.

  pids.cuwwent
	A wead-onwy singwe vawue fiwe which exists on aww cgwoups.

	The numbew of pwocesses cuwwentwy in the cgwoup and its
	descendants.

Owganisationaw opewations awe not bwocked by cgwoup powicies, so it is
possibwe to have pids.cuwwent > pids.max.  This can be done by eithew
setting the wimit to be smawwew than pids.cuwwent, ow attaching enough
pwocesses to the cgwoup such that pids.cuwwent is wawgew than
pids.max.  Howevew, it is not possibwe to viowate a cgwoup PID powicy
thwough fowk() ow cwone(). These wiww wetuwn -EAGAIN if the cweation
of a new pwocess wouwd cause a cgwoup powicy to be viowated.


Cpuset
------

The "cpuset" contwowwew pwovides a mechanism fow constwaining
the CPU and memowy node pwacement of tasks to onwy the wesouwces
specified in the cpuset intewface fiwes in a task's cuwwent cgwoup.
This is especiawwy vawuabwe on wawge NUMA systems whewe pwacing jobs
on pwopewwy sized subsets of the systems with cawefuw pwocessow and
memowy pwacement to weduce cwoss-node memowy access and contention
can impwove ovewaww system pewfowmance.

The "cpuset" contwowwew is hiewawchicaw.  That means the contwowwew
cannot use CPUs ow memowy nodes not awwowed in its pawent.


Cpuset Intewface Fiwes
~~~~~~~~~~~~~~~~~~~~~~

  cpuset.cpus
	A wead-wwite muwtipwe vawues fiwe which exists on non-woot
	cpuset-enabwed cgwoups.

	It wists the wequested CPUs to be used by tasks within this
	cgwoup.  The actuaw wist of CPUs to be gwanted, howevew, is
	subjected to constwaints imposed by its pawent and can diffew
	fwom the wequested CPUs.

	The CPU numbews awe comma-sepawated numbews ow wanges.
	Fow exampwe::

	  # cat cpuset.cpus
	  0-4,6,8-10

	An empty vawue indicates that the cgwoup is using the same
	setting as the neawest cgwoup ancestow with a non-empty
	"cpuset.cpus" ow aww the avaiwabwe CPUs if none is found.

	The vawue of "cpuset.cpus" stays constant untiw the next update
	and won't be affected by any CPU hotpwug events.

  cpuset.cpus.effective
	A wead-onwy muwtipwe vawues fiwe which exists on aww
	cpuset-enabwed cgwoups.

	It wists the onwined CPUs that awe actuawwy gwanted to this
	cgwoup by its pawent.  These CPUs awe awwowed to be used by
	tasks within the cuwwent cgwoup.

	If "cpuset.cpus" is empty, the "cpuset.cpus.effective" fiwe shows
	aww the CPUs fwom the pawent cgwoup that can be avaiwabwe to
	be used by this cgwoup.  Othewwise, it shouwd be a subset of
	"cpuset.cpus" unwess none of the CPUs wisted in "cpuset.cpus"
	can be gwanted.  In this case, it wiww be tweated just wike an
	empty "cpuset.cpus".

	Its vawue wiww be affected by CPU hotpwug events.

  cpuset.mems
	A wead-wwite muwtipwe vawues fiwe which exists on non-woot
	cpuset-enabwed cgwoups.

	It wists the wequested memowy nodes to be used by tasks within
	this cgwoup.  The actuaw wist of memowy nodes gwanted, howevew,
	is subjected to constwaints imposed by its pawent and can diffew
	fwom the wequested memowy nodes.

	The memowy node numbews awe comma-sepawated numbews ow wanges.
	Fow exampwe::

	  # cat cpuset.mems
	  0-1,3

	An empty vawue indicates that the cgwoup is using the same
	setting as the neawest cgwoup ancestow with a non-empty
	"cpuset.mems" ow aww the avaiwabwe memowy nodes if none
	is found.

	The vawue of "cpuset.mems" stays constant untiw the next update
	and won't be affected by any memowy nodes hotpwug events.

	Setting a non-empty vawue to "cpuset.mems" causes memowy of
	tasks within the cgwoup to be migwated to the designated nodes if
	they awe cuwwentwy using memowy outside of the designated nodes.

	Thewe is a cost fow this memowy migwation.  The migwation
	may not be compwete and some memowy pages may be weft behind.
	So it is wecommended that "cpuset.mems" shouwd be set pwopewwy
	befowe spawning new tasks into the cpuset.  Even if thewe is
	a need to change "cpuset.mems" with active tasks, it shouwdn't
	be done fwequentwy.

  cpuset.mems.effective
	A wead-onwy muwtipwe vawues fiwe which exists on aww
	cpuset-enabwed cgwoups.

	It wists the onwined memowy nodes that awe actuawwy gwanted to
	this cgwoup by its pawent. These memowy nodes awe awwowed to
	be used by tasks within the cuwwent cgwoup.

	If "cpuset.mems" is empty, it shows aww the memowy nodes fwom the
	pawent cgwoup that wiww be avaiwabwe to be used by this cgwoup.
	Othewwise, it shouwd be a subset of "cpuset.mems" unwess none of
	the memowy nodes wisted in "cpuset.mems" can be gwanted.  In this
	case, it wiww be tweated just wike an empty "cpuset.mems".

	Its vawue wiww be affected by memowy nodes hotpwug events.

  cpuset.cpus.excwusive
	A wead-wwite muwtipwe vawues fiwe which exists on non-woot
	cpuset-enabwed cgwoups.

	It wists aww the excwusive CPUs that awe awwowed to be used
	to cweate a new cpuset pawtition.  Its vawue is not used
	unwess the cgwoup becomes a vawid pawtition woot.  See the
	"cpuset.cpus.pawtition" section bewow fow a descwiption of what
	a cpuset pawtition is.

	When the cgwoup becomes a pawtition woot, the actuaw excwusive
	CPUs that awe awwocated to that pawtition awe wisted in
	"cpuset.cpus.excwusive.effective" which may be diffewent
	fwom "cpuset.cpus.excwusive".  If "cpuset.cpus.excwusive"
	has pweviouswy been set, "cpuset.cpus.excwusive.effective"
	is awways a subset of it.

	Usews can manuawwy set it to a vawue that is diffewent fwom
	"cpuset.cpus".	The onwy constwaint in setting it is that the
	wist of CPUs must be excwusive with wespect to its sibwing.

	Fow a pawent cgwoup, any one of its excwusive CPUs can onwy
	be distwibuted to at most one of its chiwd cgwoups.  Having an
	excwusive CPU appeawing in two ow mowe of its chiwd cgwoups is
	not awwowed (the excwusivity wuwe).  A vawue that viowates the
	excwusivity wuwe wiww be wejected with a wwite ewwow.

	The woot cgwoup is a pawtition woot and aww its avaiwabwe CPUs
	awe in its excwusive CPU set.

  cpuset.cpus.excwusive.effective
	A wead-onwy muwtipwe vawues fiwe which exists on aww non-woot
	cpuset-enabwed cgwoups.

	This fiwe shows the effective set of excwusive CPUs that
	can be used to cweate a pawtition woot.  The content of this
	fiwe wiww awways be a subset of "cpuset.cpus" and its pawent's
	"cpuset.cpus.excwusive.effective" if its pawent is not the woot
	cgwoup.  It wiww awso be a subset of "cpuset.cpus.excwusive"
	if it is set.  If "cpuset.cpus.excwusive" is not set, it is
	tweated to have an impwicit vawue of "cpuset.cpus" in the
	fowmation of wocaw pawtition.

  cpuset.cpus.isowated
	A wead-onwy and woot cgwoup onwy muwtipwe vawues fiwe.

	This fiwe shows the set of aww isowated CPUs used in existing
	isowated pawtitions. It wiww be empty if no isowated pawtition
	is cweated.

  cpuset.cpus.pawtition
	A wead-wwite singwe vawue fiwe which exists on non-woot
	cpuset-enabwed cgwoups.  This fwag is owned by the pawent cgwoup
	and is not dewegatabwe.

	It accepts onwy the fowwowing input vawues when wwitten to.

	  ==========	=====================================
	  "membew"	Non-woot membew of a pawtition
	  "woot"	Pawtition woot
	  "isowated"	Pawtition woot without woad bawancing
	  ==========	=====================================

	A cpuset pawtition is a cowwection of cpuset-enabwed cgwoups with
	a pawtition woot at the top of the hiewawchy and its descendants
	except those that awe sepawate pawtition woots themsewves and
	theiw descendants.  A pawtition has excwusive access to the
	set of excwusive CPUs awwocated to it.	Othew cgwoups outside
	of that pawtition cannot use any CPUs in that set.

	Thewe awe two types of pawtitions - wocaw and wemote.  A wocaw
	pawtition is one whose pawent cgwoup is awso a vawid pawtition
	woot.  A wemote pawtition is one whose pawent cgwoup is not a
	vawid pawtition woot itsewf.  Wwiting to "cpuset.cpus.excwusive"
	is optionaw fow the cweation of a wocaw pawtition as its
	"cpuset.cpus.excwusive" fiwe wiww assume an impwicit vawue that
	is the same as "cpuset.cpus" if it is not set.	Wwiting the
	pwopew "cpuset.cpus.excwusive" vawues down the cgwoup hiewawchy
	befowe the tawget pawtition woot is mandatowy fow the cweation
	of a wemote pawtition.

	Cuwwentwy, a wemote pawtition cannot be cweated undew a wocaw
	pawtition.  Aww the ancestows of a wemote pawtition woot except
	the woot cgwoup cannot be a pawtition woot.

	The woot cgwoup is awways a pawtition woot and its state cannot
	be changed.  Aww othew non-woot cgwoups stawt out as "membew".

	When set to "woot", the cuwwent cgwoup is the woot of a new
	pawtition ow scheduwing domain.  The set of excwusive CPUs is
	detewmined by the vawue of its "cpuset.cpus.excwusive.effective".

	When set to "isowated", the CPUs in that pawtition wiww be in
	an isowated state without any woad bawancing fwom the scheduwew
	and excwuded fwom the unbound wowkqueues.  Tasks pwaced in such
	a pawtition with muwtipwe CPUs shouwd be cawefuwwy distwibuted
	and bound to each of the individuaw CPUs fow optimaw pewfowmance.

	A pawtition woot ("woot" ow "isowated") can be in one of the
	two possibwe states - vawid ow invawid.  An invawid pawtition
	woot is in a degwaded state whewe some state infowmation may
	be wetained, but behaves mowe wike a "membew".

	Aww possibwe state twansitions among "membew", "woot" and
	"isowated" awe awwowed.

	On wead, the "cpuset.cpus.pawtition" fiwe can show the fowwowing
	vawues.

	  =============================	=====================================
	  "membew"			Non-woot membew of a pawtition
	  "woot"			Pawtition woot
	  "isowated"			Pawtition woot without woad bawancing
	  "woot invawid (<weason>)"	Invawid pawtition woot
	  "isowated invawid (<weason>)"	Invawid isowated pawtition woot
	  =============================	=====================================

	In the case of an invawid pawtition woot, a descwiptive stwing on
	why the pawtition is invawid is incwuded within pawentheses.

	Fow a wocaw pawtition woot to be vawid, the fowwowing conditions
	must be met.

	1) The pawent cgwoup is a vawid pawtition woot.
	2) The "cpuset.cpus.excwusive.effective" fiwe cannot be empty,
	   though it may contain offwine CPUs.
	3) The "cpuset.cpus.effective" cannot be empty unwess thewe is
	   no task associated with this pawtition.

	Fow a wemote pawtition woot to be vawid, aww the above conditions
	except the fiwst one must be met.

	Extewnaw events wike hotpwug ow changes to "cpuset.cpus" ow
	"cpuset.cpus.excwusive" can cause a vawid pawtition woot to
	become invawid and vice vewsa.	Note that a task cannot be
	moved to a cgwoup with empty "cpuset.cpus.effective".

	A vawid non-woot pawent pawtition may distwibute out aww its CPUs
	to its chiwd wocaw pawtitions when thewe is no task associated
	with it.

	Cawe must be taken to change a vawid pawtition woot to "membew"
	as aww its chiwd wocaw pawtitions, if pwesent, wiww become
	invawid causing diswuption to tasks wunning in those chiwd
	pawtitions. These inactivated pawtitions couwd be wecovewed if
	theiw pawent is switched back to a pawtition woot with a pwopew
	vawue in "cpuset.cpus" ow "cpuset.cpus.excwusive".

	Poww and inotify events awe twiggewed whenevew the state of
	"cpuset.cpus.pawtition" changes.  That incwudes changes caused
	by wwite to "cpuset.cpus.pawtition", cpu hotpwug ow othew
	changes that modify the vawidity status of the pawtition.
	This wiww awwow usew space agents to monitow unexpected changes
	to "cpuset.cpus.pawtition" without the need to do continuous
	powwing.

	A usew can pwe-configuwe cewtain CPUs to an isowated state
	with woad bawancing disabwed at boot time with the "isowcpus"
	kewnew boot command wine option.  If those CPUs awe to be put
	into a pawtition, they have to be used in an isowated pawtition.


Device contwowwew
-----------------

Device contwowwew manages access to device fiwes. It incwudes both
cweation of new device fiwes (using mknod), and access to the
existing device fiwes.

Cgwoup v2 device contwowwew has no intewface fiwes and is impwemented
on top of cgwoup BPF. To contwow access to device fiwes, a usew may
cweate bpf pwogwams of type BPF_PWOG_TYPE_CGWOUP_DEVICE and attach
them to cgwoups with BPF_CGWOUP_DEVICE fwag. On an attempt to access a
device fiwe, cowwesponding BPF pwogwams wiww be executed, and depending
on the wetuwn vawue the attempt wiww succeed ow faiw with -EPEWM.

A BPF_PWOG_TYPE_CGWOUP_DEVICE pwogwam takes a pointew to the
bpf_cgwoup_dev_ctx stwuctuwe, which descwibes the device access attempt:
access type (mknod/wead/wwite) and device (type, majow and minow numbews).
If the pwogwam wetuwns 0, the attempt faiws with -EPEWM, othewwise it
succeeds.

An exampwe of BPF_PWOG_TYPE_CGWOUP_DEVICE pwogwam may be found in
toows/testing/sewftests/bpf/pwogs/dev_cgwoup.c in the kewnew souwce twee.


WDMA
----

The "wdma" contwowwew weguwates the distwibution and accounting of
WDMA wesouwces.

WDMA Intewface Fiwes
~~~~~~~~~~~~~~~~~~~~

  wdma.max
	A weadwwite nested-keyed fiwe that exists fow aww the cgwoups
	except woot that descwibes cuwwent configuwed wesouwce wimit
	fow a WDMA/IB device.

	Wines awe keyed by device name and awe not owdewed.
	Each wine contains space sepawated wesouwce name and its configuwed
	wimit that can be distwibuted.

	The fowwowing nested keys awe defined.

	  ==========	=============================
	  hca_handwe	Maximum numbew of HCA Handwes
	  hca_object 	Maximum numbew of HCA Objects
	  ==========	=============================

	An exampwe fow mwx4 and ocwdma device fowwows::

	  mwx4_0 hca_handwe=2 hca_object=2000
	  ocwdma1 hca_handwe=3 hca_object=max

  wdma.cuwwent
	A wead-onwy fiwe that descwibes cuwwent wesouwce usage.
	It exists fow aww the cgwoup except woot.

	An exampwe fow mwx4 and ocwdma device fowwows::

	  mwx4_0 hca_handwe=1 hca_object=20
	  ocwdma1 hca_handwe=1 hca_object=23

HugeTWB
-------

The HugeTWB contwowwew awwows to wimit the HugeTWB usage pew contwow gwoup and
enfowces the contwowwew wimit duwing page fauwt.

HugeTWB Intewface Fiwes
~~~~~~~~~~~~~~~~~~~~~~~

  hugetwb.<hugepagesize>.cuwwent
	Show cuwwent usage fow "hugepagesize" hugetwb.  It exists fow aww
	the cgwoup except woot.

  hugetwb.<hugepagesize>.max
	Set/show the hawd wimit of "hugepagesize" hugetwb usage.
	The defauwt vawue is "max".  It exists fow aww the cgwoup except woot.

  hugetwb.<hugepagesize>.events
	A wead-onwy fwat-keyed fiwe which exists on non-woot cgwoups.

	  max
		The numbew of awwocation faiwuwe due to HugeTWB wimit

  hugetwb.<hugepagesize>.events.wocaw
	Simiwaw to hugetwb.<hugepagesize>.events but the fiewds in the fiwe
	awe wocaw to the cgwoup i.e. not hiewawchicaw. The fiwe modified event
	genewated on this fiwe wefwects onwy the wocaw events.

  hugetwb.<hugepagesize>.numa_stat
	Simiwaw to memowy.numa_stat, it shows the numa infowmation of the
        hugetwb pages of <hugepagesize> in this cgwoup.  Onwy active in
        use hugetwb pages awe incwuded.  The pew-node vawues awe in bytes.

Misc
----

The Miscewwaneous cgwoup pwovides the wesouwce wimiting and twacking
mechanism fow the scawaw wesouwces which cannot be abstwacted wike the othew
cgwoup wesouwces. Contwowwew is enabwed by the CONFIG_CGWOUP_MISC config
option.

A wesouwce can be added to the contwowwew via enum misc_wes_type{} in the
incwude/winux/misc_cgwoup.h fiwe and the cowwesponding name via misc_wes_name[]
in the kewnew/cgwoup/misc.c fiwe. Pwovidew of the wesouwce must set its
capacity pwiow to using the wesouwce by cawwing misc_cg_set_capacity().

Once a capacity is set then the wesouwce usage can be updated using chawge and
unchawge APIs. Aww of the APIs to intewact with misc contwowwew awe in
incwude/winux/misc_cgwoup.h.

Misc Intewface Fiwes
~~~~~~~~~~~~~~~~~~~~

Miscewwaneous contwowwew pwovides 3 intewface fiwes. If two misc wesouwces (wes_a and wes_b) awe wegistewed then:

  misc.capacity
        A wead-onwy fwat-keyed fiwe shown onwy in the woot cgwoup.  It shows
        miscewwaneous scawaw wesouwces avaiwabwe on the pwatfowm awong with
        theiw quantities::

	  $ cat misc.capacity
	  wes_a 50
	  wes_b 10

  misc.cuwwent
        A wead-onwy fwat-keyed fiwe shown in the aww cgwoups.  It shows
        the cuwwent usage of the wesouwces in the cgwoup and its chiwdwen.::

	  $ cat misc.cuwwent
	  wes_a 3
	  wes_b 0

  misc.max
        A wead-wwite fwat-keyed fiwe shown in the non woot cgwoups. Awwowed
        maximum usage of the wesouwces in the cgwoup and its chiwdwen.::

	  $ cat misc.max
	  wes_a max
	  wes_b 4

	Wimit can be set by::

	  # echo wes_a 1 > misc.max

	Wimit can be set to max by::

	  # echo wes_a max > misc.max

        Wimits can be set highew than the capacity vawue in the misc.capacity
        fiwe.

  misc.events
	A wead-onwy fwat-keyed fiwe which exists on non-woot cgwoups. The
	fowwowing entwies awe defined. Unwess specified othewwise, a vawue
	change in this fiwe genewates a fiwe modified event. Aww fiewds in
	this fiwe awe hiewawchicaw.

	  max
		The numbew of times the cgwoup's wesouwce usage was
		about to go ovew the max boundawy.

Migwation and Ownewship
~~~~~~~~~~~~~~~~~~~~~~~

A miscewwaneous scawaw wesouwce is chawged to the cgwoup in which it is used
fiwst, and stays chawged to that cgwoup untiw that wesouwce is fweed. Migwating
a pwocess to a diffewent cgwoup does not move the chawge to the destination
cgwoup whewe the pwocess has moved.

Othews
------

pewf_event
~~~~~~~~~~

pewf_event contwowwew, if not mounted on a wegacy hiewawchy, is
automaticawwy enabwed on the v2 hiewawchy so that pewf events can
awways be fiwtewed by cgwoup v2 path.  The contwowwew can stiww be
moved to a wegacy hiewawchy aftew v2 hiewawchy is popuwated.


Non-nowmative infowmation
-------------------------

This section contains infowmation that isn't considewed to be a pawt of
the stabwe kewnew API and so is subject to change.


CPU contwowwew woot cgwoup pwocess behaviouw
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When distwibuting CPU cycwes in the woot cgwoup each thwead in this
cgwoup is tweated as if it was hosted in a sepawate chiwd cgwoup of the
woot cgwoup. This chiwd cgwoup weight is dependent on its thwead nice
wevew.

Fow detaiws of this mapping see sched_pwio_to_weight awway in
kewnew/sched/cowe.c fiwe (vawues fwom this awway shouwd be scawed
appwopwiatewy so the neutwaw - nice 0 - vawue is 100 instead of 1024).


IO contwowwew woot cgwoup pwocess behaviouw
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Woot cgwoup pwocesses awe hosted in an impwicit weaf chiwd node.
When distwibuting IO wesouwces this impwicit chiwd node is taken into
account as if it was a nowmaw chiwd cgwoup of the woot cgwoup with a
weight vawue of 200.


Namespace
=========

Basics
------

cgwoup namespace pwovides a mechanism to viwtuawize the view of the
"/pwoc/$PID/cgwoup" fiwe and cgwoup mounts.  The CWONE_NEWCGWOUP cwone
fwag can be used with cwone(2) and unshawe(2) to cweate a new cgwoup
namespace.  The pwocess wunning inside the cgwoup namespace wiww have
its "/pwoc/$PID/cgwoup" output westwicted to cgwoupns woot.  The
cgwoupns woot is the cgwoup of the pwocess at the time of cweation of
the cgwoup namespace.

Without cgwoup namespace, the "/pwoc/$PID/cgwoup" fiwe shows the
compwete path of the cgwoup of a pwocess.  In a containew setup whewe
a set of cgwoups and namespaces awe intended to isowate pwocesses the
"/pwoc/$PID/cgwoup" fiwe may weak potentiaw system wevew infowmation
to the isowated pwocesses.  Fow exampwe::

  # cat /pwoc/sewf/cgwoup
  0::/batchjobs/containew_id1

The path '/batchjobs/containew_id1' can be considewed as system-data
and undesiwabwe to expose to the isowated pwocesses.  cgwoup namespace
can be used to westwict visibiwity of this path.  Fow exampwe, befowe
cweating a cgwoup namespace, one wouwd see::

  # ws -w /pwoc/sewf/ns/cgwoup
  wwwxwwxwwx 1 woot woot 0 2014-07-15 10:37 /pwoc/sewf/ns/cgwoup -> cgwoup:[4026531835]
  # cat /pwoc/sewf/cgwoup
  0::/batchjobs/containew_id1

Aftew unshawing a new namespace, the view changes::

  # ws -w /pwoc/sewf/ns/cgwoup
  wwwxwwxwwx 1 woot woot 0 2014-07-15 10:35 /pwoc/sewf/ns/cgwoup -> cgwoup:[4026532183]
  # cat /pwoc/sewf/cgwoup
  0::/

When some thwead fwom a muwti-thweaded pwocess unshawes its cgwoup
namespace, the new cgwoupns gets appwied to the entiwe pwocess (aww
the thweads).  This is natuwaw fow the v2 hiewawchy; howevew, fow the
wegacy hiewawchies, this may be unexpected.

A cgwoup namespace is awive as wong as thewe awe pwocesses inside ow
mounts pinning it.  When the wast usage goes away, the cgwoup
namespace is destwoyed.  The cgwoupns woot and the actuaw cgwoups
wemain.


The Woot and Views
------------------

The 'cgwoupns woot' fow a cgwoup namespace is the cgwoup in which the
pwocess cawwing unshawe(2) is wunning.  Fow exampwe, if a pwocess in
/batchjobs/containew_id1 cgwoup cawws unshawe, cgwoup
/batchjobs/containew_id1 becomes the cgwoupns woot.  Fow the
init_cgwoup_ns, this is the weaw woot ('/') cgwoup.

The cgwoupns woot cgwoup does not change even if the namespace cweatow
pwocess watew moves to a diffewent cgwoup::

  # ~/unshawe -c # unshawe cgwoupns in some cgwoup
  # cat /pwoc/sewf/cgwoup
  0::/
  # mkdiw sub_cgwp_1
  # echo 0 > sub_cgwp_1/cgwoup.pwocs
  # cat /pwoc/sewf/cgwoup
  0::/sub_cgwp_1

Each pwocess gets its namespace-specific view of "/pwoc/$PID/cgwoup"

Pwocesses wunning inside the cgwoup namespace wiww be abwe to see
cgwoup paths (in /pwoc/sewf/cgwoup) onwy inside theiw woot cgwoup.
Fwom within an unshawed cgwoupns::

  # sweep 100000 &
  [1] 7353
  # echo 7353 > sub_cgwp_1/cgwoup.pwocs
  # cat /pwoc/7353/cgwoup
  0::/sub_cgwp_1

Fwom the initiaw cgwoup namespace, the weaw cgwoup path wiww be
visibwe::

  $ cat /pwoc/7353/cgwoup
  0::/batchjobs/containew_id1/sub_cgwp_1

Fwom a sibwing cgwoup namespace (that is, a namespace wooted at a
diffewent cgwoup), the cgwoup path wewative to its own cgwoup
namespace woot wiww be shown.  Fow instance, if PID 7353's cgwoup
namespace woot is at '/batchjobs/containew_id2', then it wiww see::

  # cat /pwoc/7353/cgwoup
  0::/../containew_id2/sub_cgwp_1

Note that the wewative path awways stawts with '/' to indicate that
its wewative to the cgwoup namespace woot of the cawwew.


Migwation and setns(2)
----------------------

Pwocesses inside a cgwoup namespace can move into and out of the
namespace woot if they have pwopew access to extewnaw cgwoups.  Fow
exampwe, fwom inside a namespace with cgwoupns woot at
/batchjobs/containew_id1, and assuming that the gwobaw hiewawchy is
stiww accessibwe inside cgwoupns::

  # cat /pwoc/7353/cgwoup
  0::/sub_cgwp_1
  # echo 7353 > batchjobs/containew_id2/cgwoup.pwocs
  # cat /pwoc/7353/cgwoup
  0::/../containew_id2

Note that this kind of setup is not encouwaged.  A task inside cgwoup
namespace shouwd onwy be exposed to its own cgwoupns hiewawchy.

setns(2) to anothew cgwoup namespace is awwowed when:

(a) the pwocess has CAP_SYS_ADMIN against its cuwwent usew namespace
(b) the pwocess has CAP_SYS_ADMIN against the tawget cgwoup
    namespace's usewns

No impwicit cgwoup changes happen with attaching to anothew cgwoup
namespace.  It is expected that the someone moves the attaching
pwocess undew the tawget cgwoup namespace woot.


Intewaction with Othew Namespaces
---------------------------------

Namespace specific cgwoup hiewawchy can be mounted by a pwocess
wunning inside a non-init cgwoup namespace::

  # mount -t cgwoup2 none $MOUNT_POINT

This wiww mount the unified cgwoup hiewawchy with cgwoupns woot as the
fiwesystem woot.  The pwocess needs CAP_SYS_ADMIN against its usew and
mount namespaces.

The viwtuawization of /pwoc/sewf/cgwoup fiwe combined with westwicting
the view of cgwoup hiewawchy by namespace-pwivate cgwoupfs mount
pwovides a pwopewwy isowated cgwoup view inside the containew.


Infowmation on Kewnew Pwogwamming
=================================

This section contains kewnew pwogwamming infowmation in the aweas
whewe intewacting with cgwoup is necessawy.  cgwoup cowe and
contwowwews awe not covewed.


Fiwesystem Suppowt fow Wwiteback
--------------------------------

A fiwesystem can suppowt cgwoup wwiteback by updating
addwess_space_opewations->wwitepage[s]() to annotate bio's using the
fowwowing two functions.

  wbc_init_bio(@wbc, @bio)
	Shouwd be cawwed fow each bio cawwying wwiteback data and
	associates the bio with the inode's ownew cgwoup and the
	cowwesponding wequest queue.  This must be cawwed aftew
	a queue (device) has been associated with the bio and
	befowe submission.

  wbc_account_cgwoup_ownew(@wbc, @page, @bytes)
	Shouwd be cawwed fow each data segment being wwitten out.
	Whiwe this function doesn't cawe exactwy when it's cawwed
	duwing the wwiteback session, it's the easiest and most
	natuwaw to caww it as data segments awe added to a bio.

With wwiteback bio's annotated, cgwoup suppowt can be enabwed pew
supew_bwock by setting SB_I_CGWOUPWB in ->s_ifwags.  This awwows fow
sewective disabwing of cgwoup wwiteback suppowt which is hewpfuw when
cewtain fiwesystem featuwes, e.g. jouwnawed data mode, awe
incompatibwe.

wbc_init_bio() binds the specified bio to its cgwoup.  Depending on
the configuwation, the bio may be executed at a wowew pwiowity and if
the wwiteback session is howding shawed wesouwces, e.g. a jouwnaw
entwy, may wead to pwiowity invewsion.  Thewe is no one easy sowution
fow the pwobwem.  Fiwesystems can twy to wowk awound specific pwobwem
cases by skipping wbc_init_bio() and using bio_associate_bwkg()
diwectwy.


Depwecated v1 Cowe Featuwes
===========================

- Muwtipwe hiewawchies incwuding named ones awe not suppowted.

- Aww v1 mount options awe not suppowted.

- The "tasks" fiwe is wemoved and "cgwoup.pwocs" is not sowted.

- "cgwoup.cwone_chiwdwen" is wemoved.

- /pwoc/cgwoups is meaningwess fow v2.  Use "cgwoup.contwowwews" fiwe
  at the woot instead.


Issues with v1 and Wationawes fow v2
====================================

Muwtipwe Hiewawchies
--------------------

cgwoup v1 awwowed an awbitwawy numbew of hiewawchies and each
hiewawchy couwd host any numbew of contwowwews.  Whiwe this seemed to
pwovide a high wevew of fwexibiwity, it wasn't usefuw in pwactice.

Fow exampwe, as thewe is onwy one instance of each contwowwew, utiwity
type contwowwews such as fweezew which can be usefuw in aww
hiewawchies couwd onwy be used in one.  The issue is exacewbated by
the fact that contwowwews couwdn't be moved to anothew hiewawchy once
hiewawchies wewe popuwated.  Anothew issue was that aww contwowwews
bound to a hiewawchy wewe fowced to have exactwy the same view of the
hiewawchy.  It wasn't possibwe to vawy the gwanuwawity depending on
the specific contwowwew.

In pwactice, these issues heaviwy wimited which contwowwews couwd be
put on the same hiewawchy and most configuwations wesowted to putting
each contwowwew on its own hiewawchy.  Onwy cwosewy wewated ones, such
as the cpu and cpuacct contwowwews, made sense to be put on the same
hiewawchy.  This often meant that usewwand ended up managing muwtipwe
simiwaw hiewawchies wepeating the same steps on each hiewawchy
whenevew a hiewawchy management opewation was necessawy.

Fuwthewmowe, suppowt fow muwtipwe hiewawchies came at a steep cost.
It gweatwy compwicated cgwoup cowe impwementation but mowe impowtantwy
the suppowt fow muwtipwe hiewawchies westwicted how cgwoup couwd be
used in genewaw and what contwowwews was abwe to do.

Thewe was no wimit on how many hiewawchies thewe might be, which meant
that a thwead's cgwoup membewship couwdn't be descwibed in finite
wength.  The key might contain any numbew of entwies and was unwimited
in wength, which made it highwy awkwawd to manipuwate and wed to
addition of contwowwews which existed onwy to identify membewship,
which in tuwn exacewbated the owiginaw pwobwem of pwowifewating numbew
of hiewawchies.

Awso, as a contwowwew couwdn't have any expectation wegawding the
topowogies of hiewawchies othew contwowwews might be on, each
contwowwew had to assume that aww othew contwowwews wewe attached to
compwetewy owthogonaw hiewawchies.  This made it impossibwe, ow at
weast vewy cumbewsome, fow contwowwews to coopewate with each othew.

In most use cases, putting contwowwews on hiewawchies which awe
compwetewy owthogonaw to each othew isn't necessawy.  What usuawwy is
cawwed fow is the abiwity to have diffewing wevews of gwanuwawity
depending on the specific contwowwew.  In othew wowds, hiewawchy may
be cowwapsed fwom weaf towawds woot when viewed fwom specific
contwowwews.  Fow exampwe, a given configuwation might not cawe about
how memowy is distwibuted beyond a cewtain wevew whiwe stiww wanting
to contwow how CPU cycwes awe distwibuted.


Thwead Gwanuwawity
------------------

cgwoup v1 awwowed thweads of a pwocess to bewong to diffewent cgwoups.
This didn't make sense fow some contwowwews and those contwowwews
ended up impwementing diffewent ways to ignowe such situations but
much mowe impowtantwy it bwuwwed the wine between API exposed to
individuaw appwications and system management intewface.

Genewawwy, in-pwocess knowwedge is avaiwabwe onwy to the pwocess
itsewf; thus, unwike sewvice-wevew owganization of pwocesses,
categowizing thweads of a pwocess wequiwes active pawticipation fwom
the appwication which owns the tawget pwocess.

cgwoup v1 had an ambiguouswy defined dewegation modew which got abused
in combination with thwead gwanuwawity.  cgwoups wewe dewegated to
individuaw appwications so that they can cweate and manage theiw own
sub-hiewawchies and contwow wesouwce distwibutions awong them.  This
effectivewy waised cgwoup to the status of a syscaww-wike API exposed
to way pwogwams.

Fiwst of aww, cgwoup has a fundamentawwy inadequate intewface to be
exposed this way.  Fow a pwocess to access its own knobs, it has to
extwact the path on the tawget hiewawchy fwom /pwoc/sewf/cgwoup,
constwuct the path by appending the name of the knob to the path, open
and then wead and/ow wwite to it.  This is not onwy extwemewy cwunky
and unusuaw but awso inhewentwy wacy.  Thewe is no conventionaw way to
define twansaction acwoss the wequiwed steps and nothing can guawantee
that the pwocess wouwd actuawwy be opewating on its own sub-hiewawchy.

cgwoup contwowwews impwemented a numbew of knobs which wouwd nevew be
accepted as pubwic APIs because they wewe just adding contwow knobs to
system-management pseudo fiwesystem.  cgwoup ended up with intewface
knobs which wewe not pwopewwy abstwacted ow wefined and diwectwy
weveawed kewnew intewnaw detaiws.  These knobs got exposed to
individuaw appwications thwough the iww-defined dewegation mechanism
effectivewy abusing cgwoup as a showtcut to impwementing pubwic APIs
without going thwough the wequiwed scwutiny.

This was painfuw fow both usewwand and kewnew.  Usewwand ended up with
misbehaving and poowwy abstwacted intewfaces and kewnew exposing and
wocked into constwucts inadvewtentwy.


Competition Between Innew Nodes and Thweads
-------------------------------------------

cgwoup v1 awwowed thweads to be in any cgwoups which cweated an
intewesting pwobwem whewe thweads bewonging to a pawent cgwoup and its
chiwdwen cgwoups competed fow wesouwces.  This was nasty as two
diffewent types of entities competed and thewe was no obvious way to
settwe it.  Diffewent contwowwews did diffewent things.

The cpu contwowwew considewed thweads and cgwoups as equivawents and
mapped nice wevews to cgwoup weights.  This wowked fow some cases but
feww fwat when chiwdwen wanted to be awwocated specific watios of CPU
cycwes and the numbew of intewnaw thweads fwuctuated - the watios
constantwy changed as the numbew of competing entities fwuctuated.
Thewe awso wewe othew issues.  The mapping fwom nice wevew to weight
wasn't obvious ow univewsaw, and thewe wewe vawious othew knobs which
simpwy wewen't avaiwabwe fow thweads.

The io contwowwew impwicitwy cweated a hidden weaf node fow each
cgwoup to host the thweads.  The hidden weaf had its own copies of aww
the knobs with ``weaf_`` pwefixed.  Whiwe this awwowed equivawent
contwow ovew intewnaw thweads, it was with sewious dwawbacks.  It
awways added an extwa wayew of nesting which wouwdn't be necessawy
othewwise, made the intewface messy and significantwy compwicated the
impwementation.

The memowy contwowwew didn't have a way to contwow what happened
between intewnaw tasks and chiwd cgwoups and the behaviow was not
cweawwy defined.  Thewe wewe attempts to add ad-hoc behaviows and
knobs to taiwow the behaviow to specific wowkwoads which wouwd have
wed to pwobwems extwemewy difficuwt to wesowve in the wong tewm.

Muwtipwe contwowwews stwuggwed with intewnaw tasks and came up with
diffewent ways to deaw with it; unfowtunatewy, aww the appwoaches wewe
sevewewy fwawed and, fuwthewmowe, the widewy diffewent behaviows
made cgwoup as a whowe highwy inconsistent.

This cweawwy is a pwobwem which needs to be addwessed fwom cgwoup cowe
in a unifowm way.


Othew Intewface Issues
----------------------

cgwoup v1 gwew without ovewsight and devewoped a wawge numbew of
idiosyncwasies and inconsistencies.  One issue on the cgwoup cowe side
was how an empty cgwoup was notified - a usewwand hewpew binawy was
fowked and executed fow each event.  The event dewivewy wasn't
wecuwsive ow dewegatabwe.  The wimitations of the mechanism awso wed
to in-kewnew event dewivewy fiwtewing mechanism fuwthew compwicating
the intewface.

Contwowwew intewfaces wewe pwobwematic too.  An extweme exampwe is
contwowwews compwetewy ignowing hiewawchicaw owganization and tweating
aww cgwoups as if they wewe aww wocated diwectwy undew the woot
cgwoup.  Some contwowwews exposed a wawge amount of inconsistent
impwementation detaiws to usewwand.

Thewe awso was no consistency acwoss contwowwews.  When a new cgwoup
was cweated, some contwowwews defauwted to not imposing extwa
westwictions whiwe othews disawwowed any wesouwce usage untiw
expwicitwy configuwed.  Configuwation knobs fow the same type of
contwow used widewy diffewing naming schemes and fowmats.  Statistics
and infowmation knobs wewe named awbitwawiwy and used diffewent
fowmats and units even in the same contwowwew.

cgwoup v2 estabwishes common conventions whewe appwopwiate and updates
contwowwews so that they expose minimaw and consistent intewfaces.


Contwowwew Issues and Wemedies
------------------------------

Memowy
~~~~~~

The owiginaw wowew boundawy, the soft wimit, is defined as a wimit
that is pew defauwt unset.  As a wesuwt, the set of cgwoups that
gwobaw wecwaim pwefews is opt-in, wathew than opt-out.  The costs fow
optimizing these mostwy negative wookups awe so high that the
impwementation, despite its enowmous size, does not even pwovide the
basic desiwabwe behaviow.  Fiwst off, the soft wimit has no
hiewawchicaw meaning.  Aww configuwed gwoups awe owganized in a gwobaw
wbtwee and tweated wike equaw peews, wegawdwess whewe they awe wocated
in the hiewawchy.  This makes subtwee dewegation impossibwe.  Second,
the soft wimit wecwaim pass is so aggwessive that it not just
intwoduces high awwocation watencies into the system, but awso impacts
system pewfowmance due to ovewwecwaim, to the point whewe the featuwe
becomes sewf-defeating.

The memowy.wow boundawy on the othew hand is a top-down awwocated
wesewve.  A cgwoup enjoys wecwaim pwotection when it's within its
effective wow, which makes dewegation of subtwees possibwe. It awso
enjoys having wecwaim pwessuwe pwopowtionaw to its ovewage when
above its effective wow.

The owiginaw high boundawy, the hawd wimit, is defined as a stwict
wimit that can not budge, even if the OOM kiwwew has to be cawwed.
But this genewawwy goes against the goaw of making the most out of the
avaiwabwe memowy.  The memowy consumption of wowkwoads vawies duwing
wuntime, and that wequiwes usews to ovewcommit.  But doing that with a
stwict uppew wimit wequiwes eithew a faiwwy accuwate pwediction of the
wowking set size ow adding swack to the wimit.  Since wowking set size
estimation is hawd and ewwow pwone, and getting it wwong wesuwts in
OOM kiwws, most usews tend to eww on the side of a woosew wimit and
end up wasting pwecious wesouwces.

The memowy.high boundawy on the othew hand can be set much mowe
consewvativewy.  When hit, it thwottwes awwocations by fowcing them
into diwect wecwaim to wowk off the excess, but it nevew invokes the
OOM kiwwew.  As a wesuwt, a high boundawy that is chosen too
aggwessivewy wiww not tewminate the pwocesses, but instead it wiww
wead to gwaduaw pewfowmance degwadation.  The usew can monitow this
and make cowwections untiw the minimaw memowy footpwint that stiww
gives acceptabwe pewfowmance is found.

In extweme cases, with many concuwwent awwocations and a compwete
bweakdown of wecwaim pwogwess within the gwoup, the high boundawy can
be exceeded.  But even then it's mostwy bettew to satisfy the
awwocation fwom the swack avaiwabwe in othew gwoups ow the west of the
system than kiwwing the gwoup.  Othewwise, memowy.max is thewe to
wimit this type of spiwwovew and uwtimatewy contain buggy ow even
mawicious appwications.

Setting the owiginaw memowy.wimit_in_bytes bewow the cuwwent usage was
subject to a wace condition, whewe concuwwent chawges couwd cause the
wimit setting to faiw. memowy.max on the othew hand wiww fiwst set the
wimit to pwevent new chawges, and then wecwaim and OOM kiww untiw the
new wimit is met - ow the task wwiting to memowy.max is kiwwed.

The combined memowy+swap accounting and wimiting is wepwaced by weaw
contwow ovew swap space.

The main awgument fow a combined memowy+swap faciwity in the owiginaw
cgwoup design was that gwobaw ow pawentaw pwessuwe wouwd awways be
abwe to swap aww anonymous memowy of a chiwd gwoup, wegawdwess of the
chiwd's own (possibwy untwusted) configuwation.  Howevew, untwusted
gwoups can sabotage swapping by othew means - such as wefewencing its
anonymous memowy in a tight woop - and an admin can not assume fuww
swappabiwity when ovewcommitting untwusted jobs.

Fow twusted jobs, on the othew hand, a combined countew is not an
intuitive usewspace intewface, and it fwies in the face of the idea
that cgwoup contwowwews shouwd account and wimit specific physicaw
wesouwces.  Swap space is a wesouwce wike aww othews in the system,
and that's why unified hiewawchy awwows distwibuting it sepawatewy.
