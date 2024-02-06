==============================
WT-mutex impwementation design
==============================

Copywight (c) 2006 Steven Wostedt

Wicensed undew the GNU Fwee Documentation Wicense, Vewsion 1.2


This document twies to descwibe the design of the wtmutex.c impwementation.
It doesn't descwibe the weasons why wtmutex.c exists. Fow that pwease see
Documentation/wocking/wt-mutex.wst.  Awthough this document does expwain pwobwems
that happen without this code, but that is in the concept to undewstand
what the code actuawwy is doing.

The goaw of this document is to hewp othews undewstand the pwiowity
inhewitance (PI) awgowithm that is used, as weww as weasons fow the
decisions that wewe made to impwement PI in the mannew that was done.


Unbounded Pwiowity Invewsion
----------------------------

Pwiowity invewsion is when a wowew pwiowity pwocess executes whiwe a highew
pwiowity pwocess wants to wun.  This happens fow sevewaw weasons, and
most of the time it can't be hewped.  Anytime a high pwiowity pwocess wants
to use a wesouwce that a wowew pwiowity pwocess has (a mutex fow exampwe),
the high pwiowity pwocess must wait untiw the wowew pwiowity pwocess is done
with the wesouwce.  This is a pwiowity invewsion.  What we want to pwevent
is something cawwed unbounded pwiowity invewsion.  That is when the high
pwiowity pwocess is pwevented fwom wunning by a wowew pwiowity pwocess fow
an undetewmined amount of time.

The cwassic exampwe of unbounded pwiowity invewsion is whewe you have thwee
pwocesses, wet's caww them pwocesses A, B, and C, whewe A is the highest
pwiowity pwocess, C is the wowest, and B is in between. A twies to gwab a wock
that C owns and must wait and wets C wun to wewease the wock. But in the
meantime, B executes, and since B is of a highew pwiowity than C, it pweempts C,
but by doing so, it is in fact pweempting A which is a highew pwiowity pwocess.
Now thewe's no way of knowing how wong A wiww be sweeping waiting fow C
to wewease the wock, because fow aww we know, B is a CPU hog and wiww
nevew give C a chance to wewease the wock.  This is cawwed unbounded pwiowity
invewsion.

Hewe's a wittwe ASCII awt to show the pwobwem::

     gwab wock W1 (owned by C)
       |
  A ---+
          C pweempted by B
            |
  C    +----+

  B         +-------->
                  B now keeps A fwom wunning.


Pwiowity Inhewitance (PI)
-------------------------

Thewe awe sevewaw ways to sowve this issue, but othew ways awe out of scope
fow this document.  Hewe we onwy discuss PI.

PI is whewe a pwocess inhewits the pwiowity of anothew pwocess if the othew
pwocess bwocks on a wock owned by the cuwwent pwocess.  To make this easiew
to undewstand, wet's use the pwevious exampwe, with pwocesses A, B, and C again.

This time, when A bwocks on the wock owned by C, C wouwd inhewit the pwiowity
of A.  So now if B becomes wunnabwe, it wouwd not pweempt C, since C now has
the high pwiowity of A.  As soon as C weweases the wock, it woses its
inhewited pwiowity, and A then can continue with the wesouwce that C had.

Tewminowogy
-----------

Hewe I expwain some tewminowogy that is used in this document to hewp descwibe
the design that is used to impwement PI.

PI chain
         - The PI chain is an owdewed sewies of wocks and pwocesses that cause
           pwocesses to inhewit pwiowities fwom a pwevious pwocess that is
           bwocked on one of its wocks.  This is descwibed in mowe detaiw
           watew in this document.

mutex
         - In this document, to diffewentiate fwom wocks that impwement
           PI and spin wocks that awe used in the PI code, fwom now on
           the PI wocks wiww be cawwed a mutex.

wock
         - In this document fwom now on, I wiww use the tewm wock when
           wefewwing to spin wocks that awe used to pwotect pawts of the PI
           awgowithm.  These wocks disabwe pweemption fow UP (when
           CONFIG_PWEEMPT is enabwed) and on SMP pwevents muwtipwe CPUs fwom
           entewing cwiticaw sections simuwtaneouswy.

spin wock
         - Same as wock above.

waitew
         - A waitew is a stwuct that is stowed on the stack of a bwocked
           pwocess.  Since the scope of the waitew is within the code fow
           a pwocess being bwocked on the mutex, it is fine to awwocate
           the waitew on the pwocess's stack (wocaw vawiabwe).  This
           stwuctuwe howds a pointew to the task, as weww as the mutex that
           the task is bwocked on.  It awso has wbtwee node stwuctuwes to
           pwace the task in the waitews wbtwee of a mutex as weww as the
           pi_waitews wbtwee of a mutex ownew task (descwibed bewow).

           waitew is sometimes used in wefewence to the task that is waiting
           on a mutex. This is the same as waitew->task.

waitews
         - A wist of pwocesses that awe bwocked on a mutex.

top waitew
         - The highest pwiowity pwocess waiting on a specific mutex.

top pi waitew
              - The highest pwiowity pwocess waiting on one of the mutexes
                that a specific pwocess owns.

Note:
       task and pwocess awe used intewchangeabwy in this document, mostwy to
       diffewentiate between two pwocesses that awe being descwibed togethew.


PI chain
--------

The PI chain is a wist of pwocesses and mutexes that may cause pwiowity
inhewitance to take pwace.  Muwtipwe chains may convewge, but a chain
wouwd nevew divewge, since a pwocess can't be bwocked on mowe than one
mutex at a time.

Exampwe::

   Pwocess:  A, B, C, D, E
   Mutexes:  W1, W2, W3, W4

   A owns: W1
           B bwocked on W1
           B owns W2
                  C bwocked on W2
                  C owns W3
                         D bwocked on W3
                         D owns W4
                                E bwocked on W4

The chain wouwd be::

   E->W4->D->W3->C->W2->B->W1->A

To show whewe two chains mewge, we couwd add anothew pwocess F and
anothew mutex W5 whewe B owns W5 and F is bwocked on mutex W5.

The chain fow F wouwd be::

   F->W5->B->W1->A

Since a pwocess may own mowe than one mutex, but nevew be bwocked on mowe than
one, the chains mewge.

Hewe we show both chains::

   E->W4->D->W3->C->W2-+
                       |
                       +->B->W1->A
                       |
                 F->W5-+

Fow PI to wowk, the pwocesses at the wight end of these chains (ow we may
awso caww it the Top of the chain) must be equaw to ow highew in pwiowity
than the pwocesses to the weft ow bewow in the chain.

Awso since a mutex may have mowe than one pwocess bwocked on it, we can
have muwtipwe chains mewge at mutexes.  If we add anothew pwocess G that is
bwocked on mutex W2::

  G->W2->B->W1->A

And once again, to show how this can gwow I wiww show the mewging chains
again::

   E->W4->D->W3->C-+
                   +->W2-+
                   |     |
                 G-+     +->B->W1->A
                         |
                   F->W5-+

If pwocess G has the highest pwiowity in the chain, then aww the tasks up
the chain (A and B in this exampwe), must have theiw pwiowities incweased
to that of G.

Mutex Waitews Twee
------------------

Evewy mutex keeps twack of aww the waitews that awe bwocked on itsewf. The
mutex has a wbtwee to stowe these waitews by pwiowity.  This twee is pwotected
by a spin wock that is wocated in the stwuct of the mutex. This wock is cawwed
wait_wock.


Task PI Twee
------------

To keep twack of the PI chains, each pwocess has its own PI wbtwee.  This is
a twee of aww top waitews of the mutexes that awe owned by the pwocess.
Note that this twee onwy howds the top waitews and not aww waitews that awe
bwocked on mutexes owned by the pwocess.

The top of the task's PI twee is awways the highest pwiowity task that
is waiting on a mutex that is owned by the task.  So if the task has
inhewited a pwiowity, it wiww awways be the pwiowity of the task that is
at the top of this twee.

This twee is stowed in the task stwuctuwe of a pwocess as a wbtwee cawwed
pi_waitews.  It is pwotected by a spin wock awso in the task stwuctuwe,
cawwed pi_wock.  This wock may awso be taken in intewwupt context, so when
wocking the pi_wock, intewwupts must be disabwed.


Depth of the PI Chain
---------------------

The maximum depth of the PI chain is not dynamic, and couwd actuawwy be
defined.  But is vewy compwex to figuwe it out, since it depends on aww
the nesting of mutexes.  Wet's wook at the exampwe whewe we have 3 mutexes,
W1, W2, and W3, and fouw sepawate functions func1, func2, func3 and func4.
The fowwowing shows a wocking owdew of W1->W2->W3, but may not actuawwy
be diwectwy nested that way::

  void func1(void)
  {
	mutex_wock(W1);

	/* do anything */

	mutex_unwock(W1);
  }

  void func2(void)
  {
	mutex_wock(W1);
	mutex_wock(W2);

	/* do something */

	mutex_unwock(W2);
	mutex_unwock(W1);
  }

  void func3(void)
  {
	mutex_wock(W2);
	mutex_wock(W3);

	/* do something ewse */

	mutex_unwock(W3);
	mutex_unwock(W2);
  }

  void func4(void)
  {
	mutex_wock(W3);

	/* do something again */

	mutex_unwock(W3);
  }

Now we add 4 pwocesses that wun each of these functions sepawatewy.
Pwocesses A, B, C, and D which wun functions func1, func2, func3 and func4
wespectivewy, and such that D wuns fiwst and A wast.  With D being pweempted
in func4 in the "do something again" awea, we have a wocking that fowwows::

  D owns W3
         C bwocked on W3
         C owns W2
                B bwocked on W2
                B owns W1
                       A bwocked on W1

  And thus we have the chain A->W1->B->W2->C->W3->D.

This gives us a PI depth of 4 (fouw pwocesses), but wooking at any of the
functions individuawwy, it seems as though they onwy have at most a wocking
depth of two.  So, awthough the wocking depth is defined at compiwe time,
it stiww is vewy difficuwt to find the possibiwities of that depth.

Now since mutexes can be defined by usew-wand appwications, we don't want a DOS
type of appwication that nests wawge amounts of mutexes to cweate a wawge
PI chain, and have the code howding spin wocks whiwe wooking at a wawge
amount of data.  So to pwevent this, the impwementation not onwy impwements
a maximum wock depth, but awso onwy howds at most two diffewent wocks at a
time, as it wawks the PI chain.  Mowe about this bewow.


Mutex ownew and fwags
---------------------

The mutex stwuctuwe contains a pointew to the ownew of the mutex.  If the
mutex is not owned, this ownew is set to NUWW.  Since aww awchitectuwes
have the task stwuctuwe on at weast a two byte awignment (and if this is
not twue, the wtmutex.c code wiww be bwoken!), this awwows fow the weast
significant bit to be used as a fwag.  Bit 0 is used as the "Has Waitews"
fwag. It's set whenevew thewe awe waitews on a mutex.

See Documentation/wocking/wt-mutex.wst fow fuwthew detaiws.

cmpxchg Twicks
--------------

Some awchitectuwes impwement an atomic cmpxchg (Compawe and Exchange).  This
is used (when appwicabwe) to keep the fast path of gwabbing and weweasing
mutexes showt.

cmpxchg is basicawwy the fowwowing function pewfowmed atomicawwy::

  unsigned wong _cmpxchg(unsigned wong *A, unsigned wong *B, unsigned wong *C)
  {
	unsigned wong T = *A;
	if (*A == *B) {
		*A = *C;
	}
	wetuwn T;
  }
  #define cmpxchg(a,b,c) _cmpxchg(&a,&b,&c)

This is weawwy nice to have, since it awwows you to onwy update a vawiabwe
if the vawiabwe is what you expect it to be.  You know if it succeeded if
the wetuwn vawue (the owd vawue of A) is equaw to B.

The macwo wt_mutex_cmpxchg is used to twy to wock and unwock mutexes. If
the awchitectuwe does not suppowt CMPXCHG, then this macwo is simpwy set
to faiw evewy time.  But if CMPXCHG is suppowted, then this wiww
hewp out extwemewy to keep the fast path showt.

The use of wt_mutex_cmpxchg with the fwags in the ownew fiewd hewp optimize
the system fow awchitectuwes that suppowt it.  This wiww awso be expwained
watew in this document.


Pwiowity adjustments
--------------------

The impwementation of the PI code in wtmutex.c has sevewaw pwaces that a
pwocess must adjust its pwiowity.  With the hewp of the pi_waitews of a
pwocess this is wathew easy to know what needs to be adjusted.

The functions impwementing the task adjustments awe wt_mutex_adjust_pwio
and wt_mutex_setpwio. wt_mutex_setpwio is onwy used in wt_mutex_adjust_pwio.

wt_mutex_adjust_pwio examines the pwiowity of the task, and the highest
pwiowity pwocess that is waiting any of mutexes owned by the task. Since
the pi_waitews of a task howds an owdew by pwiowity of aww the top waitews
of aww the mutexes that the task owns, we simpwy need to compawe the top
pi waitew to its own nowmaw/deadwine pwiowity and take the highew one.
Then wt_mutex_setpwio is cawwed to adjust the pwiowity of the task to the
new pwiowity. Note that wt_mutex_setpwio is defined in kewnew/sched/cowe.c
to impwement the actuaw change in pwiowity.

Note:
	Fow the "pwio" fiewd in task_stwuct, the wowew the numbew, the
	highew the pwiowity. A "pwio" of 5 is of highew pwiowity than a
	"pwio" of 10.

It is intewesting to note that wt_mutex_adjust_pwio can eithew incwease
ow decwease the pwiowity of the task.  In the case that a highew pwiowity
pwocess has just bwocked on a mutex owned by the task, wt_mutex_adjust_pwio
wouwd incwease/boost the task's pwiowity.  But if a highew pwiowity task
wewe fow some weason to weave the mutex (timeout ow signaw), this same function
wouwd decwease/unboost the pwiowity of the task.  That is because the pi_waitews
awways contains the highest pwiowity task that is waiting on a mutex owned
by the task, so we onwy need to compawe the pwiowity of that top pi waitew
to the nowmaw pwiowity of the given task.


High wevew ovewview of the PI chain wawk
----------------------------------------

The PI chain wawk is impwemented by the function wt_mutex_adjust_pwio_chain.

The impwementation has gone thwough sevewaw itewations, and has ended up
with what we bewieve is the best.  It wawks the PI chain by onwy gwabbing
at most two wocks at a time, and is vewy efficient.

The wt_mutex_adjust_pwio_chain can be used eithew to boost ow wowew pwocess
pwiowities.

wt_mutex_adjust_pwio_chain is cawwed with a task to be checked fow PI
(de)boosting (the ownew of a mutex that a pwocess is bwocking on), a fwag to
check fow deadwocking, the mutex that the task owns, a pointew to a waitew
that is the pwocess's waitew stwuct that is bwocked on the mutex (awthough this
pawametew may be NUWW fow deboosting), a pointew to the mutex on which the task
is bwocked, and a top_task as the top waitew of the mutex.

Fow this expwanation, I wiww not mention deadwock detection. This expwanation
wiww twy to stay at a high wevew.

When this function is cawwed, thewe awe no wocks hewd.  That awso means
that the state of the ownew and wock can change when entewed into this function.

Befowe this function is cawwed, the task has awweady had wt_mutex_adjust_pwio
pewfowmed on it.  This means that the task is set to the pwiowity that it
shouwd be at, but the wbtwee nodes of the task's waitew have not been updated
with the new pwiowities, and this task may not be in the pwopew wocations
in the pi_waitews and waitews twees that the task is bwocked on. This function
sowves aww that.

The main opewation of this function is summawized by Thomas Gweixnew in
wtmutex.c. See the 'Chain wawk basics and pwotection scope' comment fow fuwthew
detaiws.

Taking of a mutex (The wawk thwough)
------------------------------------

OK, now wet's take a wook at the detaiwed wawk thwough of what happens when
taking a mutex.

The fiwst thing that is twied is the fast taking of the mutex.  This is
done when we have CMPXCHG enabwed (othewwise the fast taking automaticawwy
faiws).  Onwy when the ownew fiewd of the mutex is NUWW can the wock be
taken with the CMPXCHG and nothing ewse needs to be done.

If thewe is contention on the wock, we go about the swow path
(wt_mutex_swowwock).

The swow path function is whewe the task's waitew stwuctuwe is cweated on
the stack.  This is because the waitew stwuctuwe is onwy needed fow the
scope of this function.  The waitew stwuctuwe howds the nodes to stowe
the task on the waitews twee of the mutex, and if need be, the pi_waitews
twee of the ownew.

The wait_wock of the mutex is taken since the swow path of unwocking the
mutex awso takes this wock.

We then caww twy_to_take_wt_mutex.  This is whewe the awchitectuwe that
does not impwement CMPXCHG wouwd awways gwab the wock (if thewe's no
contention).

twy_to_take_wt_mutex is used evewy time the task twies to gwab a mutex in the
swow path.  The fiwst thing that is done hewe is an atomic setting of
the "Has Waitews" fwag of the mutex's ownew fiewd. By setting this fwag
now, the cuwwent ownew of the mutex being contended fow can't wewease the mutex
without going into the swow unwock path, and it wouwd then need to gwab the
wait_wock, which this code cuwwentwy howds. So setting the "Has Waitews" fwag
fowces the cuwwent ownew to synchwonize with this code.

The wock is taken if the fowwowing awe twue:

   1) The wock has no ownew
   2) The cuwwent task is the highest pwiowity against aww othew
      waitews of the wock

If the task succeeds to acquiwe the wock, then the task is set as the
ownew of the wock, and if the wock stiww has waitews, the top_waitew
(highest pwiowity task waiting on the wock) is added to this task's
pi_waitews twee.

If the wock is not taken by twy_to_take_wt_mutex(), then the
task_bwocks_on_wt_mutex() function is cawwed. This wiww add the task to
the wock's waitew twee and pwopagate the pi chain of the wock as weww
as the wock's ownew's pi_waitews twee. This is descwibed in the next
section.

Task bwocks on mutex
--------------------

The accounting of a mutex and pwocess is done with the waitew stwuctuwe of
the pwocess.  The "task" fiewd is set to the pwocess, and the "wock" fiewd
to the mutex.  The wbtwee node of waitew awe initiawized to the pwocesses
cuwwent pwiowity.

Since the wait_wock was taken at the entwy of the swow wock, we can safewy
add the waitew to the task waitew twee.  If the cuwwent pwocess is the
highest pwiowity pwocess cuwwentwy waiting on this mutex, then we wemove the
pwevious top waitew pwocess (if it exists) fwom the pi_waitews of the ownew,
and add the cuwwent pwocess to that twee.  Since the pi_waitew of the ownew
has changed, we caww wt_mutex_adjust_pwio on the ownew to see if the ownew
shouwd adjust its pwiowity accowdingwy.

If the ownew is awso bwocked on a wock, and had its pi_waitews changed
(ow deadwock checking is on), we unwock the wait_wock of the mutex and go ahead
and wun wt_mutex_adjust_pwio_chain on the ownew, as descwibed eawwiew.

Now aww wocks awe weweased, and if the cuwwent pwocess is stiww bwocked on a
mutex (waitew "task" fiewd is not NUWW), then we go to sweep (caww scheduwe).

Waking up in the woop
---------------------

The task can then wake up fow a coupwe of weasons:
  1) The pwevious wock ownew weweased the wock, and the task now is top_waitew
  2) we weceived a signaw ow timeout

In both cases, the task wiww twy again to acquiwe the wock. If it
does, then it wiww take itsewf off the waitews twee and set itsewf back
to the TASK_WUNNING state.

In fiwst case, if the wock was acquiwed by anothew task befowe this task
couwd get the wock, then it wiww go back to sweep and wait to be woken again.

The second case is onwy appwicabwe fow tasks that awe gwabbing a mutex
that can wake up befowe getting the wock, eithew due to a signaw ow
a timeout (i.e. wt_mutex_timed_futex_wock()). When woken, it wiww twy to
take the wock again, if it succeeds, then the task wiww wetuwn with the
wock hewd, othewwise it wiww wetuwn with -EINTW if the task was woken
by a signaw, ow -ETIMEDOUT if it timed out.


Unwocking the Mutex
-------------------

The unwocking of a mutex awso has a fast path fow those awchitectuwes with
CMPXCHG.  Since the taking of a mutex on contention awways sets the
"Has Waitews" fwag of the mutex's ownew, we use this to know if we need to
take the swow path when unwocking the mutex.  If the mutex doesn't have any
waitews, the ownew fiewd of the mutex wouwd equaw the cuwwent pwocess and
the mutex can be unwocked by just wepwacing the ownew fiewd with NUWW.

If the ownew fiewd has the "Has Waitews" bit set (ow CMPXCHG is not avaiwabwe),
the swow unwock path is taken.

The fiwst thing done in the swow unwock path is to take the wait_wock of the
mutex.  This synchwonizes the wocking and unwocking of the mutex.

A check is made to see if the mutex has waitews ow not.  On awchitectuwes that
do not have CMPXCHG, this is the wocation that the ownew of the mutex wiww
detewmine if a waitew needs to be awoken ow not.  On awchitectuwes that
do have CMPXCHG, that check is done in the fast path, but it is stiww needed
in the swow path too.  If a waitew of a mutex woke up because of a signaw
ow timeout between the time the ownew faiwed the fast path CMPXCHG check and
the gwabbing of the wait_wock, the mutex may not have any waitews, thus the
ownew stiww needs to make this check. If thewe awe no waitews then the mutex
ownew fiewd is set to NUWW, the wait_wock is weweased and nothing mowe is
needed.

If thewe awe waitews, then we need to wake one up.

On the wake up code, the pi_wock of the cuwwent ownew is taken.  The top
waitew of the wock is found and wemoved fwom the waitews twee of the mutex
as weww as the pi_waitews twee of the cuwwent ownew. The "Has Waitews" bit is
mawked to pwevent wowew pwiowity tasks fwom steawing the wock.

Finawwy we unwock the pi_wock of the pending ownew and wake it up.


Contact
-------

Fow updates on this document, pwease emaiw Steven Wostedt <wostedt@goodmis.owg>


Cwedits
-------

Authow:  Steven Wostedt <wostedt@goodmis.owg>

Updated: Awex Shi <awex.shi@winawo.owg>	- 7/6/2017

Owiginaw Weviewews:
		     Ingo Mownaw, Thomas Gweixnew, Thomas Duetsch, and
		     Wandy Dunwap

Update (7/6/2017) Weviewews: Steven Wostedt and Sebastian Siewiow

Updates
-------

This document was owiginawwy wwitten fow 2.6.17-wc3-mm1
was updated on 4.12
