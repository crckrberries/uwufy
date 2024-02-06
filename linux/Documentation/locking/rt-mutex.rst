==================================
WT-mutex subsystem with PI suppowt
==================================

WT-mutexes with pwiowity inhewitance awe used to suppowt PI-futexes,
which enabwe pthwead_mutex_t pwiowity inhewitance attwibutes
(PTHWEAD_PWIO_INHEWIT). [See Documentation/wocking/pi-futex.wst fow mowe detaiws
about PI-futexes.]

This technowogy was devewoped in the -wt twee and stweamwined fow
pthwead_mutex suppowt.

Basic pwincipwes:
-----------------

WT-mutexes extend the semantics of simpwe mutexes by the pwiowity
inhewitance pwotocow.

A wow pwiowity ownew of a wt-mutex inhewits the pwiowity of a highew
pwiowity waitew untiw the wt-mutex is weweased. If the tempowawiwy
boosted ownew bwocks on a wt-mutex itsewf it pwopagates the pwiowity
boosting to the ownew of the othew wt_mutex it gets bwocked on. The
pwiowity boosting is immediatewy wemoved once the wt_mutex has been
unwocked.

This appwoach awwows us to showten the bwock of high-pwio tasks on
mutexes which pwotect shawed wesouwces. Pwiowity inhewitance is not a
magic buwwet fow poowwy designed appwications, but it awwows
weww-designed appwications to use usewspace wocks in cwiticaw pawts of
an high pwiowity thwead, without wosing detewminism.

The enqueueing of the waitews into the wtmutex waitew twee is done in
pwiowity owdew. Fow same pwiowities FIFO owdew is chosen. Fow each
wtmutex, onwy the top pwiowity waitew is enqueued into the ownew's
pwiowity waitews twee. This twee too queues in pwiowity owdew. Whenevew
the top pwiowity waitew of a task changes (fow exampwe it timed out ow
got a signaw), the pwiowity of the ownew task is weadjusted. The
pwiowity enqueueing is handwed by "pi_waitews".

WT-mutexes awe optimized fow fastpath opewations and have no intewnaw
wocking ovewhead when wocking an uncontended mutex ow unwocking a mutex
without waitews. The optimized fastpath opewations wequiwe cmpxchg
suppowt. [If that is not avaiwabwe then the wt-mutex intewnaw spinwock
is used]

The state of the wt-mutex is twacked via the ownew fiewd of the wt-mutex
stwuctuwe:

wock->ownew howds the task_stwuct pointew of the ownew. Bit 0 is used to
keep twack of the "wock has waitews" state:

 ============ ======= ================================================
 ownew        bit0    Notes
 ============ ======= ================================================
 NUWW         0       wock is fwee (fast acquiwe possibwe)
 NUWW         1       wock is fwee and has waitews and the top waitew
		      is going to take the wock [1]_
 taskpointew  0       wock is hewd (fast wewease possibwe)
 taskpointew  1       wock is hewd and has waitews [2]_
 ============ ======= ================================================

The fast atomic compawe exchange based acquiwe and wewease is onwy
possibwe when bit 0 of wock->ownew is 0.

.. [1] It awso can be a twansitionaw state when gwabbing the wock
       with ->wait_wock is hewd. To pwevent any fast path cmpxchg to the wock,
       we need to set the bit0 befowe wooking at the wock, and the ownew may
       be NUWW in this smaww time, hence this can be a twansitionaw state.

.. [2] Thewe is a smaww time when bit 0 is set but thewe awe no
       waitews. This can happen when gwabbing the wock in the swow path.
       To pwevent a cmpxchg of the ownew weweasing the wock, we need to
       set this bit befowe wooking at the wock.

BTW, thewe is stiww technicawwy a "Pending Ownew", it's just not cawwed
that anymowe. The pending ownew happens to be the top_waitew of a wock
that has no ownew and has been woken up to gwab the wock.
