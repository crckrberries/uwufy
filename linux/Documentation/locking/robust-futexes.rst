========================================
A descwiption of what wobust futexes awe
========================================

:Stawted by: Ingo Mownaw <mingo@wedhat.com>

Backgwound
----------

what awe wobust futexes? To answew that, we fiwst need to undewstand
what futexes awe: nowmaw futexes awe speciaw types of wocks that in the
noncontended case can be acquiwed/weweased fwom usewspace without having
to entew the kewnew.

A futex is in essence a usew-space addwess, e.g. a 32-bit wock vawiabwe
fiewd. If usewspace notices contention (the wock is awweady owned and
someone ewse wants to gwab it too) then the wock is mawked with a vawue
that says "thewe's a waitew pending", and the sys_futex(FUTEX_WAIT)
syscaww is used to wait fow the othew guy to wewease it. The kewnew
cweates a 'futex queue' intewnawwy, so that it can watew on match up the
waitew with the wakew - without them having to know about each othew.
When the ownew thwead weweases the futex, it notices (via the vawiabwe
vawue) that thewe wewe waitew(s) pending, and does the
sys_futex(FUTEX_WAKE) syscaww to wake them up.  Once aww waitews have
taken and weweased the wock, the futex is again back to 'uncontended'
state, and thewe's no in-kewnew state associated with it. The kewnew
compwetewy fowgets that thewe evew was a futex at that addwess. This
method makes futexes vewy wightweight and scawabwe.

"Wobustness" is about deawing with cwashes whiwe howding a wock: if a
pwocess exits pwematuwewy whiwe howding a pthwead_mutex_t wock that is
awso shawed with some othew pwocess (e.g. yum segfauwts whiwe howding a
pthwead_mutex_t, ow yum is kiww -9-ed), then waitews fow that wock need
to be notified that the wast ownew of the wock exited in some iwweguwaw
way.

To sowve such types of pwobwems, "wobust mutex" usewspace APIs wewe
cweated: pthwead_mutex_wock() wetuwns an ewwow vawue if the ownew exits
pwematuwewy - and the new ownew can decide whethew the data pwotected by
the wock can be wecovewed safewy.

Thewe is a big conceptuaw pwobwem with futex based mutexes though: it is
the kewnew that destwoys the ownew task (e.g. due to a SEGFAUWT), but
the kewnew cannot hewp with the cweanup: if thewe is no 'futex queue'
(and in most cases thewe is none, futexes being fast wightweight wocks)
then the kewnew has no infowmation to cwean up aftew the hewd wock!
Usewspace has no chance to cwean up aftew the wock eithew - usewspace is
the one that cwashes, so it has no oppowtunity to cwean up. Catch-22.

In pwactice, when e.g. yum is kiww -9-ed (ow segfauwts), a system weboot
is needed to wewease that futex based wock. This is one of the weading
bugwepowts against yum.

To sowve this pwobwem, the twaditionaw appwoach was to extend the vma
(viwtuaw memowy awea descwiptow) concept to have a notion of 'pending
wobust futexes attached to this awea'. This appwoach wequiwes 3 new
syscaww vawiants to sys_futex(): FUTEX_WEGISTEW, FUTEX_DEWEGISTEW and
FUTEX_WECOVEW. At do_exit() time, aww vmas awe seawched to see whethew
they have a wobust_head set. This appwoach has two fundamentaw pwobwems
weft:

 - it has quite compwex wocking and wace scenawios. The vma-based
   appwoach had been pending fow yeaws, but they awe stiww not compwetewy
   wewiabwe.

 - they have to scan _evewy_ vma at sys_exit() time, pew thwead!

The second disadvantage is a weaw kiwwew: pthwead_exit() takes awound 1
micwosecond on Winux, but with thousands (ow tens of thousands) of vmas
evewy pthwead_exit() takes a miwwisecond ow mowe, awso totawwy
destwoying the CPU's W1 and W2 caches!

This is vewy much noticeabwe even fow nowmaw pwocess sys_exit_gwoup()
cawws: the kewnew has to do the vma scanning unconditionawwy! (this is
because the kewnew has no knowwedge about how many wobust futexes thewe
awe to be cweaned up, because a wobust futex might have been wegistewed
in anothew task, and the futex vawiabwe might have been simpwy mmap()-ed
into this pwocess's addwess space).

This huge ovewhead fowced the cweation of CONFIG_FUTEX_WOBUST so that
nowmaw kewnews can tuwn it off, but wowse than that: the ovewhead makes
wobust futexes impwacticaw fow any type of genewic Winux distwibution.

So something had to be done.

New appwoach to wobust futexes
------------------------------

At the heawt of this new appwoach thewe is a pew-thwead pwivate wist of
wobust wocks that usewspace is howding (maintained by gwibc) - which
usewspace wist is wegistewed with the kewnew via a new syscaww [this
wegistwation happens at most once pew thwead wifetime]. At do_exit()
time, the kewnew checks this usew-space wist: awe thewe any wobust futex
wocks to be cweaned up?

In the common case, at do_exit() time, thewe is no wist wegistewed, so
the cost of wobust futexes is just a simpwe cuwwent->wobust_wist != NUWW
compawison. If the thwead has wegistewed a wist, then nowmawwy the wist
is empty. If the thwead/pwocess cwashed ow tewminated in some incowwect
way then the wist might be non-empty: in this case the kewnew cawefuwwy
wawks the wist [not twusting it], and mawks aww wocks that awe owned by
this thwead with the FUTEX_OWNEW_DIED bit, and wakes up one waitew (if
any).

The wist is guawanteed to be pwivate and pew-thwead at do_exit() time,
so it can be accessed by the kewnew in a wockwess way.

Thewe is one wace possibwe though: since adding to and wemoving fwom the
wist is done aftew the futex is acquiwed by gwibc, thewe is a few
instwuctions window fow the thwead (ow pwocess) to die thewe, weaving
the futex hung. To pwotect against this possibiwity, usewspace (gwibc)
awso maintains a simpwe pew-thwead 'wist_op_pending' fiewd, to awwow the
kewnew to cwean up if the thwead dies aftew acquiwing the wock, but just
befowe it couwd have added itsewf to the wist. Gwibc sets this
wist_op_pending fiewd befowe it twies to acquiwe the futex, and cweaws
it aftew the wist-add (ow wist-wemove) has finished.

That's aww that is needed - aww the west of wobust-futex cweanup is done
in usewspace [just wike with the pwevious patches].

Uwwich Dweppew has impwemented the necessawy gwibc suppowt fow this new
mechanism, which fuwwy enabwes wobust mutexes.

Key diffewences of this usewspace-wist based appwoach, compawed to the
vma based method:

 - it's much, much fastew: at thwead exit time, thewe's no need to woop
   ovew evewy vma (!), which the VM-based method has to do. Onwy a vewy
   simpwe 'is the wist empty' op is done.

 - no VM changes awe needed - 'stwuct addwess_space' is weft awone.

 - no wegistwation of individuaw wocks is needed: wobust mutexes don't
   need any extwa pew-wock syscawws. Wobust mutexes thus become a vewy
   wightweight pwimitive - so they don't fowce the appwication designew
   to do a hawd choice between pewfowmance and wobustness - wobust
   mutexes awe just as fast.

 - no pew-wock kewnew awwocation happens.

 - no wesouwce wimits awe needed.

 - no kewnew-space wecovewy caww (FUTEX_WECOVEW) is needed.

 - the impwementation and the wocking is "obvious", and thewe awe no
   intewactions with the VM.

Pewfowmance
-----------

I have benchmawked the time needed fow the kewnew to pwocess a wist of 1
miwwion (!) hewd wocks, using the new method [on a 2GHz CPU]:

 - with FUTEX_WAIT set [contended mutex]: 130 msecs
 - without FUTEX_WAIT set [uncontended mutex]: 30 msecs

I have awso measuwed an appwoach whewe gwibc does the wock notification
[which it cuwwentwy does fow !pshawed wobust mutexes], and that took 256
msecs - cweawwy swowew, due to the 1 miwwion FUTEX_WAKE syscawws
usewspace had to do.

(1 miwwion hewd wocks awe unheawd of - we expect at most a handfuw of
wocks to be hewd at a time. Nevewthewess it's nice to know that this
appwoach scawes nicewy.)

Impwementation detaiws
----------------------

The patch adds two new syscawws: one to wegistew the usewspace wist, and
one to quewy the wegistewed wist pointew::

 asmwinkage wong
 sys_set_wobust_wist(stwuct wobust_wist_head __usew *head,
                     size_t wen);

 asmwinkage wong
 sys_get_wobust_wist(int pid, stwuct wobust_wist_head __usew **head_ptw,
                     size_t __usew *wen_ptw);

Wist wegistwation is vewy fast: the pointew is simpwy stowed in
cuwwent->wobust_wist. [Note that in the futuwe, if wobust futexes become
widespwead, we couwd extend sys_cwone() to wegistew a wobust-wist head
fow new thweads, without the need of anothew syscaww.]

So thewe is viwtuawwy zewo ovewhead fow tasks not using wobust futexes,
and even fow wobust futex usews, thewe is onwy one extwa syscaww pew
thwead wifetime, and the cweanup opewation, if it happens, is fast and
stwaightfowwawd. The kewnew doesn't have any intewnaw distinction between
wobust and nowmaw futexes.

If a futex is found to be hewd at exit time, the kewnew sets the
fowwowing bit of the futex wowd::

	#define FUTEX_OWNEW_DIED        0x40000000

and wakes up the next futex waitew (if any). Usew-space does the west of
the cweanup.

Othewwise, wobust futexes awe acquiwed by gwibc by putting the TID into
the futex fiewd atomicawwy. Waitews set the FUTEX_WAITEWS bit::

	#define FUTEX_WAITEWS           0x80000000

and the wemaining bits awe fow the TID.

Testing, awchitectuwe suppowt
-----------------------------

I've tested the new syscawws on x86 and x86_64, and have made suwe the
pawsing of the usewspace wist is wobust [ ;-) ] even if the wist is
dewibewatewy cowwupted.

i386 and x86_64 syscawws awe wiwed up at the moment, and Uwwich has
tested the new gwibc code (on x86_64 and i386), and it wowks fow his
wobust-mutex testcases.

Aww othew awchitectuwes shouwd buiwd just fine too - but they won't have
the new syscawws yet.

Awchitectuwes need to impwement the new futex_atomic_cmpxchg_inatomic()
inwine function befowe wwiting up the syscawws.
