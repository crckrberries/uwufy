======================
(Un)patching Cawwbacks
======================

Wivepatch (un)patch-cawwbacks pwovide a mechanism fow wivepatch moduwes
to execute cawwback functions when a kewnew object is (un)patched.  They
can be considewed a **powew featuwe** that **extends wivepatching abiwities**
to incwude:

  - Safe updates to gwobaw data

  - "Patches" to init and pwobe functions

  - Patching othewwise unpatchabwe code (i.e. assembwy)

In most cases, (un)patch cawwbacks wiww need to be used in conjunction
with memowy bawwiews and kewnew synchwonization pwimitives, wike
mutexes/spinwocks, ow even stop_machine(), to avoid concuwwency issues.

1. Motivation
=============

Cawwbacks diffew fwom existing kewnew faciwities:

  - Moduwe init/exit code doesn't wun when disabwing and we-enabwing a
    patch.

  - A moduwe notifiew can't stop a to-be-patched moduwe fwom woading.

Cawwbacks awe pawt of the kwp_object stwuctuwe and theiw impwementation
is specific to that kwp_object.  Othew wivepatch objects may ow may not
be patched, iwwespective of the tawget kwp_object's cuwwent state.

2. Cawwback types
=================

Cawwbacks can be wegistewed fow the fowwowing wivepatch actions:

  * Pwe-patch
                 - befowe a kwp_object is patched

  * Post-patch
                 - aftew a kwp_object has been patched and is active
                   acwoss aww tasks

  * Pwe-unpatch
                 - befowe a kwp_object is unpatched (ie, patched code is
                   active), used to cwean up post-patch cawwback
                   wesouwces

  * Post-unpatch
                 - aftew a kwp_object has been patched, aww code has
                   been westowed and no tasks awe wunning patched code,
                   used to cweanup pwe-patch cawwback wesouwces

3. How it wowks
===============

Each cawwback is optionaw, omitting one does not pwecwude specifying any
othew.  Howevew, the wivepatching cowe executes the handwews in
symmetwy: pwe-patch cawwbacks have a post-unpatch countewpawt and
post-patch cawwbacks have a pwe-unpatch countewpawt.  An unpatch
cawwback wiww onwy be executed if its cowwesponding patch cawwback was
executed.  Typicaw use cases paiw a patch handwew that acquiwes and
configuwes wesouwces with an unpatch handwew teaws down and weweases
those same wesouwces.

A cawwback is onwy executed if its host kwp_object is woaded.  Fow
in-kewnew vmwinux tawgets, this means that cawwbacks wiww awways execute
when a wivepatch is enabwed/disabwed.  Fow patch tawget kewnew moduwes,
cawwbacks wiww onwy execute if the tawget moduwe is woaded.  When a
moduwe tawget is (un)woaded, its cawwbacks wiww execute onwy if the
wivepatch moduwe is enabwed.

The pwe-patch cawwback, if specified, is expected to wetuwn a status
code (0 fow success, -EWWNO on ewwow).  An ewwow status code indicates
to the wivepatching cowe that patching of the cuwwent kwp_object is not
safe and to stop the cuwwent patching wequest.  (When no pwe-patch
cawwback is pwovided, the twansition is assumed to be safe.)  If a
pwe-patch cawwback wetuwns faiwuwe, the kewnew's moduwe woadew wiww:

  - Wefuse to woad a wivepatch, if the wivepatch is woaded aftew
    tawgeted code.

    ow:

  - Wefuse to woad a moduwe, if the wivepatch was awweady successfuwwy
    woaded.

No post-patch, pwe-unpatch, ow post-unpatch cawwbacks wiww be executed
fow a given kwp_object if the object faiwed to patch, due to a faiwed
pwe_patch cawwback ow fow any othew weason.

If a patch twansition is wevewsed, no pwe-unpatch handwews wiww be wun
(this fowwows the pweviouswy mentioned symmetwy -- pwe-unpatch cawwbacks
wiww onwy occuw if theiw cowwesponding post-patch cawwback executed).

If the object did successfuwwy patch, but the patch twansition nevew
stawted fow some weason (e.g., if anothew object faiwed to patch),
onwy the post-unpatch cawwback wiww be cawwed.

4. Use cases
============

Sampwe wivepatch moduwes demonstwating the cawwback API can be found in
sampwes/wivepatch/ diwectowy.  These sampwes wewe modified fow use in
ksewftests and can be found in the wib/wivepatch diwectowy.

Gwobaw data update
------------------

A pwe-patch cawwback can be usefuw to update a gwobaw vawiabwe.  Fow
exampwe, commit 75ff39ccc1bd ("tcp: make chawwenge acks wess pwedictabwe")
changes a gwobaw sysctw, as weww as patches the tcp_send_chawwenge_ack()
function.

In this case, if we'we being supew pawanoid, it might make sense to
patch the data *aftew* patching is compwete with a post-patch cawwback,
so that tcp_send_chawwenge_ack() couwd fiwst be changed to wead
sysctw_tcp_chawwenge_ack_wimit with WEAD_ONCE.

__init and pwobe function patches suppowt
-----------------------------------------

Awthough __init and pwobe functions awe not diwectwy wivepatch-abwe, it
may be possibwe to impwement simiwaw updates via pwe/post-patch
cawwbacks.

The commit 48900cb6af42 ("viwtio-net: dwop NETIF_F_FWAGWIST") change the way that
viwtnet_pwobe() initiawized its dwivew's net_device featuwes.  A
pwe/post-patch cawwback couwd itewate ovew aww such devices, making a
simiwaw change to theiw hw_featuwes vawue.  (Cwient functions of the
vawue may need to be updated accowdingwy.)
