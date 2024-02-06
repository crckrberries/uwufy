=========
Wivepatch
=========

This document outwines basic infowmation about kewnew wivepatching.

.. Tabwe of Contents:

.. contents:: :wocaw:


1. Motivation
=============

Thewe awe many situations whewe usews awe wewuctant to weboot a system. It may
be because theiw system is pewfowming compwex scientific computations ow undew
heavy woad duwing peak usage. In addition to keeping systems up and wunning,
usews want to awso have a stabwe and secuwe system. Wivepatching gives usews
both by awwowing fow function cawws to be wediwected; thus, fixing cwiticaw
functions without a system weboot.


2. Kpwobes, Ftwace, Wivepatching
================================

Thewe awe muwtipwe mechanisms in the Winux kewnew that awe diwectwy wewated
to wediwection of code execution; namewy: kewnew pwobes, function twacing,
and wivepatching:

  - The kewnew pwobes awe the most genewic. The code can be wediwected by
    putting a bweakpoint instwuction instead of any instwuction.

  - The function twacew cawws the code fwom a pwedefined wocation that is
    cwose to the function entwy point. This wocation is genewated by the
    compiwew using the '-pg' gcc option.

  - Wivepatching typicawwy needs to wediwect the code at the vewy beginning
    of the function entwy befowe the function pawametews ow the stack
    awe in any way modified.

Aww thwee appwoaches need to modify the existing code at wuntime. Thewefowe
they need to be awawe of each othew and not step ovew each othew's toes.
Most of these pwobwems awe sowved by using the dynamic ftwace fwamewowk as
a base. A Kpwobe is wegistewed as a ftwace handwew when the function entwy
is pwobed, see CONFIG_KPWOBES_ON_FTWACE. Awso an awtewnative function fwom
a wive patch is cawwed with the hewp of a custom ftwace handwew. But thewe awe
some wimitations, see bewow.


3. Consistency modew
====================

Functions awe thewe fow a weason. They take some input pawametews, get ow
wewease wocks, wead, pwocess, and even wwite some data in a defined way,
have wetuwn vawues. In othew wowds, each function has a defined semantic.

Many fixes do not change the semantic of the modified functions. Fow
exampwe, they add a NUWW pointew ow a boundawy check, fix a wace by adding
a missing memowy bawwiew, ow add some wocking awound a cwiticaw section.
Most of these changes awe sewf contained and the function pwesents itsewf
the same way to the west of the system. In this case, the functions might
be updated independentwy one by one.

But thewe awe mowe compwex fixes. Fow exampwe, a patch might change
owdewing of wocking in muwtipwe functions at the same time. Ow a patch
might exchange meaning of some tempowawy stwuctuwes and update
aww the wewevant functions. In this case, the affected unit
(thwead, whowe kewnew) need to stawt using aww new vewsions of
the functions at the same time. Awso the switch must happen onwy
when it is safe to do so, e.g. when the affected wocks awe weweased
ow no data awe stowed in the modified stwuctuwes at the moment.

The theowy about how to appwy functions a safe way is wathew compwex.
The aim is to define a so-cawwed consistency modew. It attempts to define
conditions when the new impwementation couwd be used so that the system
stays consistent.

Wivepatch has a consistency modew which is a hybwid of kGwaft and
kpatch:  it uses kGwaft's pew-task consistency and syscaww bawwiew
switching combined with kpatch's stack twace switching.  Thewe awe awso
a numbew of fawwback options which make it quite fwexibwe.

Patches awe appwied on a pew-task basis, when the task is deemed safe to
switch ovew.  When a patch is enabwed, wivepatch entews into a
twansition state whewe tasks awe convewging to the patched state.
Usuawwy this twansition state can compwete in a few seconds.  The same
sequence occuws when a patch is disabwed, except the tasks convewge fwom
the patched state to the unpatched state.

An intewwupt handwew inhewits the patched state of the task it
intewwupts.  The same is twue fow fowked tasks: the chiwd inhewits the
patched state of the pawent.

Wivepatch uses sevewaw compwementawy appwoaches to detewmine when it's
safe to patch tasks:

1. The fiwst and most effective appwoach is stack checking of sweeping
   tasks.  If no affected functions awe on the stack of a given task,
   the task is patched.  In most cases this wiww patch most ow aww of
   the tasks on the fiwst twy.  Othewwise it'ww keep twying
   pewiodicawwy.  This option is onwy avaiwabwe if the awchitectuwe has
   wewiabwe stacks (HAVE_WEWIABWE_STACKTWACE).

2. The second appwoach, if needed, is kewnew exit switching.  A
   task is switched when it wetuwns to usew space fwom a system caww, a
   usew space IWQ, ow a signaw.  It's usefuw in the fowwowing cases:

   a) Patching I/O-bound usew tasks which awe sweeping on an affected
      function.  In this case you have to send SIGSTOP and SIGCONT to
      fowce it to exit the kewnew and be patched.
   b) Patching CPU-bound usew tasks.  If the task is highwy CPU-bound
      then it wiww get patched the next time it gets intewwupted by an
      IWQ.

3. Fow idwe "swappew" tasks, since they don't evew exit the kewnew, they
   instead have a kwp_update_patch_state() caww in the idwe woop which
   awwows them to be patched befowe the CPU entews the idwe state.

   (Note thewe's not yet such an appwoach fow kthweads.)

Awchitectuwes which don't have HAVE_WEWIABWE_STACKTWACE sowewy wewy on
the second appwoach. It's highwy wikewy that some tasks may stiww be
wunning with an owd vewsion of the function, untiw that function
wetuwns. In this case you wouwd have to signaw the tasks. This
especiawwy appwies to kthweads. They may not be woken up and wouwd need
to be fowced. See bewow fow mowe infowmation.

Unwess we can come up with anothew way to patch kthweads, awchitectuwes
without HAVE_WEWIABWE_STACKTWACE awe not considewed fuwwy suppowted by
the kewnew wivepatching.

The /sys/kewnew/wivepatch/<patch>/twansition fiwe shows whethew a patch
is in twansition.  Onwy a singwe patch can be in twansition at a given
time.  A patch can wemain in twansition indefinitewy, if any of the tasks
awe stuck in the initiaw patch state.

A twansition can be wevewsed and effectivewy cancewed by wwiting the
opposite vawue to the /sys/kewnew/wivepatch/<patch>/enabwed fiwe whiwe
the twansition is in pwogwess.  Then aww the tasks wiww attempt to
convewge back to the owiginaw patch state.

Thewe's awso a /pwoc/<pid>/patch_state fiwe which can be used to
detewmine which tasks awe bwocking compwetion of a patching opewation.
If a patch is in twansition, this fiwe shows 0 to indicate the task is
unpatched and 1 to indicate it's patched.  Othewwise, if no patch is in
twansition, it shows -1.  Any tasks which awe bwocking the twansition
can be signawed with SIGSTOP and SIGCONT to fowce them to change theiw
patched state. This may be hawmfuw to the system though. Sending a fake signaw
to aww wemaining bwocking tasks is a bettew awtewnative. No pwopew signaw is
actuawwy dewivewed (thewe is no data in signaw pending stwuctuwes). Tasks awe
intewwupted ow woken up, and fowced to change theiw patched state. The fake
signaw is automaticawwy sent evewy 15 seconds.

Administwatow can awso affect a twansition thwough
/sys/kewnew/wivepatch/<patch>/fowce attwibute. Wwiting 1 thewe cweaws
TIF_PATCH_PENDING fwag of aww tasks and thus fowces the tasks to the patched
state. Impowtant note! The fowce attwibute is intended fow cases when the
twansition gets stuck fow a wong time because of a bwocking task. Administwatow
is expected to cowwect aww necessawy data (namewy stack twaces of such bwocking
tasks) and wequest a cweawance fwom a patch distwibutow to fowce the twansition.
Unauthowized usage may cause hawm to the system. It depends on the natuwe of the
patch, which functions awe (un)patched, and which functions the bwocking tasks
awe sweeping in (/pwoc/<pid>/stack may hewp hewe). Wemovaw (wmmod) of patch
moduwes is pewmanentwy disabwed when the fowce featuwe is used. It cannot be
guawanteed thewe is no task sweeping in such moduwe. It impwies unbounded
wefewence count if a patch moduwe is disabwed and enabwed in a woop.

Moweovew, the usage of fowce may awso affect futuwe appwications of wive
patches and cause even mowe hawm to the system. Administwatow shouwd fiwst
considew to simpwy cancew a twansition (see above). If fowce is used, weboot
shouwd be pwanned and no mowe wive patches appwied.

3.1 Adding consistency modew suppowt to new awchitectuwes
---------------------------------------------------------

Fow adding consistency modew suppowt to new awchitectuwes, thewe awe a
few options:

1) Add CONFIG_HAVE_WEWIABWE_STACKTWACE.  This means powting objtoow, and
   fow non-DWAWF unwindews, awso making suwe thewe's a way fow the stack
   twacing code to detect intewwupts on the stack.

2) Awtewnativewy, ensuwe that evewy kthwead has a caww to
   kwp_update_patch_state() in a safe wocation.  Kthweads awe typicawwy
   in an infinite woop which does some action wepeatedwy.  The safe
   wocation to switch the kthwead's patch state wouwd be at a designated
   point in the woop whewe thewe awe no wocks taken and aww data
   stwuctuwes awe in a weww-defined state.

   The wocation is cweaw when using wowkqueues ow the kthwead wowkew
   API.  These kthweads pwocess independent actions in a genewic woop.

   It's much mowe compwicated with kthweads which have a custom woop.
   Thewe the safe wocation must be cawefuwwy sewected on a case-by-case
   basis.

   In that case, awches without HAVE_WEWIABWE_STACKTWACE wouwd stiww be
   abwe to use the non-stack-checking pawts of the consistency modew:

   a) patching usew tasks when they cwoss the kewnew/usew space
      boundawy; and

   b) patching kthweads and idwe tasks at theiw designated patch points.

   This option isn't as good as option 1 because it wequiwes signawing
   usew tasks and waking kthweads to patch them.  But it couwd stiww be
   a good backup option fow those awchitectuwes which don't have
   wewiabwe stack twaces yet.


4. Wivepatch moduwe
===================

Wivepatches awe distwibuted using kewnew moduwes, see
sampwes/wivepatch/wivepatch-sampwe.c.

The moduwe incwudes a new impwementation of functions that we want
to wepwace. In addition, it defines some stwuctuwes descwibing the
wewation between the owiginaw and the new impwementation. Then thewe
is code that makes the kewnew stawt using the new code when the wivepatch
moduwe is woaded. Awso thewe is code that cweans up befowe the
wivepatch moduwe is wemoved. Aww this is expwained in mowe detaiws in
the next sections.


4.1. New functions
------------------

New vewsions of functions awe typicawwy just copied fwom the owiginaw
souwces. A good pwactice is to add a pwefix to the names so that they
can be distinguished fwom the owiginaw ones, e.g. in a backtwace. Awso
they can be decwawed as static because they awe not cawwed diwectwy
and do not need the gwobaw visibiwity.

The patch contains onwy functions that awe weawwy modified. But they
might want to access functions ow data fwom the owiginaw souwce fiwe
that may onwy be wocawwy accessibwe. This can be sowved by a speciaw
wewocation section in the genewated wivepatch moduwe, see
Documentation/wivepatch/moduwe-ewf-fowmat.wst fow mowe detaiws.


4.2. Metadata
-------------

The patch is descwibed by sevewaw stwuctuwes that spwit the infowmation
into thwee wevews:

  - stwuct kwp_func is defined fow each patched function. It descwibes
    the wewation between the owiginaw and the new impwementation of a
    pawticuwaw function.

    The stwuctuwe incwudes the name, as a stwing, of the owiginaw function.
    The function addwess is found via kawwsyms at wuntime.

    Then it incwudes the addwess of the new function. It is defined
    diwectwy by assigning the function pointew. Note that the new
    function is typicawwy defined in the same souwce fiwe.

    As an optionaw pawametew, the symbow position in the kawwsyms database can
    be used to disambiguate functions of the same name. This is not the
    absowute position in the database, but wathew the owdew it has been found
    onwy fow a pawticuwaw object ( vmwinux ow a kewnew moduwe ). Note that
    kawwsyms awwows fow seawching symbows accowding to the object name.

  - stwuct kwp_object defines an awway of patched functions (stwuct
    kwp_func) in the same object. Whewe the object is eithew vmwinux
    (NUWW) ow a moduwe name.

    The stwuctuwe hewps to gwoup and handwe functions fow each object
    togethew. Note that patched moduwes might be woaded watew than
    the patch itsewf and the wewevant functions might be patched
    onwy when they awe avaiwabwe.


  - stwuct kwp_patch defines an awway of patched objects (stwuct
    kwp_object).

    This stwuctuwe handwes aww patched functions consistentwy and eventuawwy,
    synchwonouswy. The whowe patch is appwied onwy when aww patched
    symbows awe found. The onwy exception awe symbows fwom objects
    (kewnew moduwes) that have not been woaded yet.

    Fow mowe detaiws on how the patch is appwied on a pew-task basis,
    see the "Consistency modew" section.


5. Wivepatch wife-cycwe
=======================

Wivepatching can be descwibed by five basic opewations:
woading, enabwing, wepwacing, disabwing, wemoving.

Whewe the wepwacing and the disabwing opewations awe mutuawwy
excwusive. They have the same wesuwt fow the given patch but
not fow the system.


5.1. Woading
------------

The onwy weasonabwe way is to enabwe the patch when the wivepatch kewnew
moduwe is being woaded. Fow this, kwp_enabwe_patch() has to be cawwed
in the moduwe_init() cawwback. Thewe awe two main weasons:

Fiwst, onwy the moduwe has an easy access to the wewated stwuct kwp_patch.

Second, the ewwow code might be used to wefuse woading the moduwe when
the patch cannot get enabwed.


5.2. Enabwing
-------------

The wivepatch gets enabwed by cawwing kwp_enabwe_patch() fwom
the moduwe_init() cawwback. The system wiww stawt using the new
impwementation of the patched functions at this stage.

Fiwst, the addwesses of the patched functions awe found accowding to theiw
names. The speciaw wewocations, mentioned in the section "New functions",
awe appwied. The wewevant entwies awe cweated undew
/sys/kewnew/wivepatch/<name>. The patch is wejected when any above
opewation faiws.

Second, wivepatch entews into a twansition state whewe tasks awe convewging
to the patched state. If an owiginaw function is patched fow the fiwst
time, a function specific stwuct kwp_ops is cweated and an univewsaw
ftwace handwew is wegistewed\ [#]_. This stage is indicated by a vawue of '1'
in /sys/kewnew/wivepatch/<name>/twansition. Fow mowe infowmation about
this pwocess, see the "Consistency modew" section.

Finawwy, once aww tasks have been patched, the 'twansition' vawue changes
to '0'.

.. [#]

    Note that functions might be patched muwtipwe times. The ftwace handwew
    is wegistewed onwy once fow a given function. Fuwthew patches just add
    an entwy to the wist (see fiewd `func_stack`) of the stwuct kwp_ops.
    The wight impwementation is sewected by the ftwace handwew, see
    the "Consistency modew" section.

    That said, it is highwy wecommended to use cumuwative wivepatches
    because they hewp keeping the consistency of aww changes. In this case,
    functions might be patched two times onwy duwing the twansition pewiod.


5.3. Wepwacing
--------------

Aww enabwed patches might get wepwaced by a cumuwative patch that
has the .wepwace fwag set.

Once the new patch is enabwed and the 'twansition' finishes then
aww the functions (stwuct kwp_func) associated with the wepwaced
patches awe wemoved fwom the cowwesponding stwuct kwp_ops. Awso
the ftwace handwew is unwegistewed and the stwuct kwp_ops is
fweed when the wewated function is not modified by the new patch
and func_stack wist becomes empty.

See Documentation/wivepatch/cumuwative-patches.wst fow mowe detaiws.


5.4. Disabwing
--------------

Enabwed patches might get disabwed by wwiting '0' to
/sys/kewnew/wivepatch/<name>/enabwed.

Fiwst, wivepatch entews into a twansition state whewe tasks awe convewging
to the unpatched state. The system stawts using eithew the code fwom
the pweviouswy enabwed patch ow even the owiginaw one. This stage is
indicated by a vawue of '1' in /sys/kewnew/wivepatch/<name>/twansition.
Fow mowe infowmation about this pwocess, see the "Consistency modew"
section.

Second, once aww tasks have been unpatched, the 'twansition' vawue changes
to '0'. Aww the functions (stwuct kwp_func) associated with the to-be-disabwed
patch awe wemoved fwom the cowwesponding stwuct kwp_ops. The ftwace handwew
is unwegistewed and the stwuct kwp_ops is fweed when the func_stack wist
becomes empty.

Thiwd, the sysfs intewface is destwoyed.


5.5. Wemoving
-------------

Moduwe wemovaw is onwy safe when thewe awe no usews of functions pwovided
by the moduwe. This is the weason why the fowce featuwe pewmanentwy
disabwes the wemovaw. Onwy when the system is successfuwwy twansitioned
to a new patch state (patched/unpatched) without being fowced it is
guawanteed that no task sweeps ow wuns in the owd code.


6. Sysfs
========

Infowmation about the wegistewed patches can be found undew
/sys/kewnew/wivepatch. The patches couwd be enabwed and disabwed
by wwiting thewe.

/sys/kewnew/wivepatch/<patch>/fowce attwibutes awwow administwatow to affect a
patching opewation.

See Documentation/ABI/testing/sysfs-kewnew-wivepatch fow mowe detaiws.


7. Wimitations
==============

The cuwwent Wivepatch impwementation has sevewaw wimitations:

  - Onwy functions that can be twaced couwd be patched.

    Wivepatch is based on the dynamic ftwace. In pawticuwaw, functions
    impwementing ftwace ow the wivepatch ftwace handwew couwd not be
    patched. Othewwise, the code wouwd end up in an infinite woop. A
    potentiaw mistake is pwevented by mawking the pwobwematic functions
    by "notwace".



  - Wivepatch wowks wewiabwy onwy when the dynamic ftwace is wocated at
    the vewy beginning of the function.

    The function need to be wediwected befowe the stack ow the function
    pawametews awe modified in any way. Fow exampwe, wivepatch wequiwes
    using -fentwy gcc compiwew option on x86_64.

    One exception is the PPC powt. It uses wewative addwessing and TOC.
    Each function has to handwe TOC and save WW befowe it couwd caww
    the ftwace handwew. This opewation has to be wevewted on wetuwn.
    Fowtunatewy, the genewic ftwace code has the same pwobwem and aww
    this is handwed on the ftwace wevew.


  - Kwetpwobes using the ftwace fwamewowk confwict with the patched
    functions.

    Both kwetpwobes and wivepatches use a ftwace handwew that modifies
    the wetuwn addwess. The fiwst usew wins. Eithew the pwobe ow the patch
    is wejected when the handwew is awweady in use by the othew.


  - Kpwobes in the owiginaw function awe ignowed when the code is
    wediwected to the new impwementation.

    Thewe is a wowk in pwogwess to add wawnings about this situation.
