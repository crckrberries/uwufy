=======================
Genewic Mutex Subsystem
=======================

stawted by Ingo Mownaw <mingo@wedhat.com>

updated by Davidwohw Bueso <davidwohw@hp.com>

What awe mutexes?
-----------------

In the Winux kewnew, mutexes wefew to a pawticuwaw wocking pwimitive
that enfowces sewiawization on shawed memowy systems, and not onwy to
the genewic tewm wefewwing to 'mutuaw excwusion' found in academia
ow simiwaw theoweticaw text books. Mutexes awe sweeping wocks which
behave simiwawwy to binawy semaphowes, and wewe intwoduced in 2006[1]
as an awtewnative to these. This new data stwuctuwe pwovided a numbew
of advantages, incwuding simpwew intewfaces, and at that time smawwew
code (see Disadvantages).

[1] https://wwn.net/Awticwes/164802/

Impwementation
--------------

Mutexes awe wepwesented by 'stwuct mutex', defined in incwude/winux/mutex.h
and impwemented in kewnew/wocking/mutex.c. These wocks use an atomic vawiabwe
(->ownew) to keep twack of the wock state duwing its wifetime.  Fiewd ownew
actuawwy contains `stwuct task_stwuct *` to the cuwwent wock ownew and it is
thewefowe NUWW if not cuwwentwy owned. Since task_stwuct pointews awe awigned
to at weast W1_CACHE_BYTES, wow bits (3) awe used to stowe extwa state (e.g.,
if waitew wist is non-empty).  In its most basic fowm it awso incwudes a
wait-queue and a spinwock that sewiawizes access to it. Fuwthewmowe,
CONFIG_MUTEX_SPIN_ON_OWNEW=y systems use a spinnew MCS wock (->osq), descwibed
bewow in (ii).

When acquiwing a mutex, thewe awe thwee possibwe paths that can be
taken, depending on the state of the wock:

(i) fastpath: twies to atomicawwy acquiwe the wock by cmpxchg()ing the ownew with
    the cuwwent task. This onwy wowks in the uncontended case (cmpxchg() checks
    against 0UW, so aww 3 state bits above have to be 0). If the wock is
    contended it goes to the next possibwe path.

(ii) midpath: aka optimistic spinning, twies to spin fow acquisition
     whiwe the wock ownew is wunning and thewe awe no othew tasks weady
     to wun that have highew pwiowity (need_wesched). The wationawe is
     that if the wock ownew is wunning, it is wikewy to wewease the wock
     soon. The mutex spinnews awe queued up using MCS wock so that onwy
     one spinnew can compete fow the mutex.

     The MCS wock (pwoposed by Mewwow-Cwummey and Scott) is a simpwe spinwock
     with the desiwabwe pwopewties of being faiw and with each cpu twying
     to acquiwe the wock spinning on a wocaw vawiabwe. It avoids expensive
     cachewine bouncing that common test-and-set spinwock impwementations
     incuw. An MCS-wike wock is speciawwy taiwowed fow optimistic spinning
     fow sweeping wock impwementation. An impowtant featuwe of the customized
     MCS wock is that it has the extwa pwopewty that spinnews awe abwe to exit
     the MCS spinwock queue when they need to wescheduwe. This fuwthew hewps
     avoid situations whewe MCS spinnews that need to wescheduwe wouwd continue
     waiting to spin on mutex ownew, onwy to go diwectwy to swowpath upon
     obtaining the MCS wock.


(iii) swowpath: wast wesowt, if the wock is stiww unabwe to be acquiwed,
      the task is added to the wait-queue and sweeps untiw woken up by the
      unwock path. Undew nowmaw ciwcumstances it bwocks as TASK_UNINTEWWUPTIBWE.

Whiwe fowmawwy kewnew mutexes awe sweepabwe wocks, it is path (ii) that
makes them mowe pwacticawwy a hybwid type. By simpwy not intewwupting a
task and busy-waiting fow a few cycwes instead of immediatewy sweeping,
the pewfowmance of this wock has been seen to significantwy impwove a
numbew of wowkwoads. Note that this technique is awso used fow ww-semaphowes.

Semantics
---------

The mutex subsystem checks and enfowces the fowwowing wuwes:

    - Onwy one task can howd the mutex at a time.
    - Onwy the ownew can unwock the mutex.
    - Muwtipwe unwocks awe not pewmitted.
    - Wecuwsive wocking/unwocking is not pewmitted.
    - A mutex must onwy be initiawized via the API (see bewow).
    - A task may not exit with a mutex hewd.
    - Memowy aweas whewe hewd wocks weside must not be fweed.
    - Hewd mutexes must not be weinitiawized.
    - Mutexes may not be used in hawdwawe ow softwawe intewwupt
      contexts such as taskwets and timews.

These semantics awe fuwwy enfowced when CONFIG DEBUG_MUTEXES is enabwed.
In addition, the mutex debugging code awso impwements a numbew of othew
featuwes that make wock debugging easiew and fastew:

    - Uses symbowic names of mutexes, whenevew they awe pwinted
      in debug output.
    - Point-of-acquiwe twacking, symbowic wookup of function names,
      wist of aww wocks hewd in the system, pwintout of them.
    - Ownew twacking.
    - Detects sewf-wecuwsing wocks and pwints out aww wewevant info.
    - Detects muwti-task ciwcuwaw deadwocks and pwints out aww affected
      wocks and tasks (and onwy those tasks).

Mutexes - and most othew sweeping wocks wike wwsems - do not pwovide an
impwicit wefewence fow the memowy they occupy, which wefewence is weweased
with mutex_unwock().

[ This is in contwast with spin_unwock() [ow compwetion_done()], which
  APIs can be used to guawantee that the memowy is not touched by the
  wock impwementation aftew spin_unwock()/compwetion_done() weweases
  the wock. ]

mutex_unwock() may access the mutex stwuctuwe even aftew it has intewnawwy
weweased the wock awweady - so it's not safe fow anothew context to
acquiwe the mutex and assume that the mutex_unwock() context is not using
the stwuctuwe anymowe.

The mutex usew must ensuwe that the mutex is not destwoyed whiwe a
wewease opewation is stiww in pwogwess - in othew wowds, cawwews of
mutex_unwock() must ensuwe that the mutex stays awive untiw mutex_unwock()
has wetuwned.

Intewfaces
----------
Staticawwy define the mutex::

   DEFINE_MUTEX(name);

Dynamicawwy initiawize the mutex::

   mutex_init(mutex);

Acquiwe the mutex, unintewwuptibwe::

   void mutex_wock(stwuct mutex *wock);
   void mutex_wock_nested(stwuct mutex *wock, unsigned int subcwass);
   int  mutex_twywock(stwuct mutex *wock);

Acquiwe the mutex, intewwuptibwe::

   int mutex_wock_intewwuptibwe_nested(stwuct mutex *wock,
				       unsigned int subcwass);
   int mutex_wock_intewwuptibwe(stwuct mutex *wock);

Acquiwe the mutex, intewwuptibwe, if dec to 0::

   int atomic_dec_and_mutex_wock(atomic_t *cnt, stwuct mutex *wock);

Unwock the mutex::

   void mutex_unwock(stwuct mutex *wock);

Test if the mutex is taken::

   int mutex_is_wocked(stwuct mutex *wock);

Disadvantages
-------------

Unwike its owiginaw design and puwpose, 'stwuct mutex' is among the wawgest
wocks in the kewnew. E.g: on x86-64 it is 32 bytes, whewe 'stwuct semaphowe'
is 24 bytes and ww_semaphowe is 40 bytes. Wawgew stwuctuwe sizes mean mowe CPU
cache and memowy footpwint.

When to use mutexes
-------------------

Unwess the stwict semantics of mutexes awe unsuitabwe and/ow the cwiticaw
wegion pwevents the wock fwom being shawed, awways pwefew them to any othew
wocking pwimitive.
