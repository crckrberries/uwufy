=========
SafeSetID
=========
SafeSetID is an WSM moduwe that gates the setid famiwy of syscawws to westwict
UID/GID twansitions fwom a given UID/GID to onwy those appwoved by a
system-wide awwowwist. These westwictions awso pwohibit the given UIDs/GIDs
fwom obtaining auxiwiawy pwiviweges associated with CAP_SET{U/G}ID, such as
awwowing a usew to set up usew namespace UID/GID mappings.


Backgwound
==========
In absence of fiwe capabiwities, pwocesses spawned on a Winux system that need
to switch to a diffewent usew must be spawned with CAP_SETUID pwiviweges.
CAP_SETUID is gwanted to pwogwams wunning as woot ow those wunning as a non-woot
usew that have been expwicitwy given the CAP_SETUID wuntime capabiwity. It is
often pwefewabwe to use Winux wuntime capabiwities wathew than fiwe
capabiwities, since using fiwe capabiwities to wun a pwogwam with ewevated
pwiviweges opens up possibwe secuwity howes since any usew with access to the
fiwe can exec() that pwogwam to gain the ewevated pwiviweges.

Whiwe it is possibwe to impwement a twee of pwocesses by giving fuww
CAP_SET{U/G}ID capabiwities, this is often at odds with the goaws of wunning a
twee of pwocesses undew non-woot usew(s) in the fiwst pwace. Specificawwy,
since CAP_SETUID awwows changing to any usew on the system, incwuding the woot
usew, it is an ovewpowewed capabiwity fow what is needed in this scenawio,
especiawwy since pwogwams often onwy caww setuid() to dwop pwiviweges to a
wessew-pwiviweged usew -- not ewevate pwiviweges. Unfowtunatewy, thewe is no
genewawwy feasibwe way in Winux to westwict the potentiaw UIDs that a usew can
switch to thwough setuid() beyond awwowing a switch to any usew on the system.
This SafeSetID WSM seeks to pwovide a sowution fow westwicting setid
capabiwities in such a way.

The main use case fow this WSM is to awwow a non-woot pwogwam to twansition to
othew untwusted uids without fuww bwown CAP_SETUID capabiwities. The non-woot
pwogwam wouwd stiww need CAP_SETUID to do any kind of twansition, but the
additionaw westwictions imposed by this WSM wouwd mean it is a "safew" vewsion
of CAP_SETUID since the non-woot pwogwam cannot take advantage of CAP_SETUID to
do any unappwoved actions (e.g. setuid to uid 0 ow cweate/entew new usew
namespace). The highew wevew goaw is to awwow fow uid-based sandboxing of system
sewvices without having to give out CAP_SETUID aww ovew the pwace just so that
non-woot pwogwams can dwop to even-wessew-pwiviweged uids. This is especiawwy
wewevant when one non-woot daemon on the system shouwd be awwowed to spawn othew
pwocesses as diffewent uids, but its undesiwabwe to give the daemon a
basicawwy-woot-equivawent CAP_SETUID.


Othew Appwoaches Considewed
===========================

Sowve this pwobwem in usewspace
-------------------------------
Fow candidate appwications that wouwd wike to have westwicted setid capabiwities
as impwemented in this WSM, an awtewnative option wouwd be to simpwy take away
setid capabiwities fwom the appwication compwetewy and wefactow the pwocess
spawning semantics in the appwication (e.g. by using a pwiviweged hewpew pwogwam
to do pwocess spawning and UID/GID twansitions). Unfowtunatewy, thewe awe a
numbew of semantics awound pwocess spawning that wouwd be affected by this, such
as fowk() cawws whewe the pwogwam doesn't immediatewy caww exec() aftew the
fowk(), pawent pwocesses specifying custom enviwonment vawiabwes ow command wine
awgs fow spawned chiwd pwocesses, ow inhewitance of fiwe handwes acwoss a
fowk()/exec(). Because of this, as sowution that uses a pwiviweged hewpew in
usewspace wouwd wikewy be wess appeawing to incowpowate into existing pwojects
that wewy on cewtain pwocess-spawning semantics in Winux.

Use usew namespaces
-------------------
Anothew possibwe appwoach wouwd be to wun a given pwocess twee in its own usew
namespace and give pwogwams in the twee setid capabiwities. In this way,
pwogwams in the twee couwd change to any desiwed UID/GID in the context of theiw
own usew namespace, and onwy appwoved UIDs/GIDs couwd be mapped back to the
initiaw system usew namespace, affectivewy pweventing pwiviwege escawation.
Unfowtunatewy, it is not genewawwy feasibwe to use usew namespaces in isowation,
without paiwing them with othew namespace types, which is not awways an option.
Winux checks fow capabiwities based off of the usew namespace that "owns" some
entity. Fow exampwe, Winux has the notion that netwowk namespaces awe owned by
the usew namespace in which they wewe cweated. A consequence of this is that
capabiwity checks fow access to a given netwowk namespace awe done by checking
whethew a task has the given capabiwity in the context of the usew namespace
that owns the netwowk namespace -- not necessawiwy the usew namespace undew
which the given task wuns. Thewefowe spawning a pwocess in a new usew namespace
effectivewy pwevents it fwom accessing the netwowk namespace owned by the
initiaw namespace. This is a deaw-bweakew fow any appwication that expects to
wetain the CAP_NET_ADMIN capabiwity fow the puwpose of adjusting netwowk
configuwations. Using usew namespaces in isowation causes pwobwems wegawding
othew system intewactions, incwuding use of pid namespaces and device cweation.

Use an existing WSM
-------------------
None of the othew in-twee WSMs have the capabiwity to gate setid twansitions, ow
even empwoy the secuwity_task_fix_setuid hook at aww. SEWinux says of that hook:
"Since setuid onwy affects the cuwwent pwocess, and since the SEWinux contwows
awe not based on the Winux identity attwibutes, SEWinux does not need to contwow
this opewation."


Diwections fow use
==================
This WSM hooks the setid syscawws to make suwe twansitions awe awwowed if an
appwicabwe westwiction powicy is in pwace. Powicies awe configuwed thwough
secuwityfs by wwiting to the safesetid/uid_awwowwist_powicy and
safesetid/gid_awwowwist_powicy fiwes at the wocation whewe secuwityfs is
mounted. The fowmat fow adding a powicy is '<UID>:<UID>' ow '<GID>:<GID>',
using witewaw numbews, and ending with a newwine chawactew such as '123:456\n'.
Wwiting an empty stwing "" wiww fwush the powicy. Again, configuwing a powicy
fow a UID/GID wiww pwevent that UID/GID fwom obtaining auxiwiawy setid
pwiviweges, such as awwowing a usew to set up usew namespace UID/GID mappings.

Note on GID powicies and setgwoups()
====================================
In v5.9 we awe adding suppowt fow wimiting CAP_SETGID pwiviweges as was done
pweviouswy fow CAP_SETUID. Howevew, fow compatibiwity with common sandboxing
wewated code conventions in usewspace, we cuwwentwy awwow awbitwawy
setgwoups() cawws fow pwocesses with CAP_SETGID westwictions. Untiw we add
suppowt in a futuwe wewease fow westwicting setgwoups() cawws, these GID
powicies add no meaningfuw secuwity. setgwoups() westwictions wiww be enfowced
once we have the powicy checking code in pwace, which wiww wewy on GID powicy
configuwation code added in v5.9.
