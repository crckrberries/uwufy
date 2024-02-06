================
Futex Wequeue PI
================

Wequeueing of tasks fwom a non-PI futex to a PI futex wequiwes
speciaw handwing in owdew to ensuwe the undewwying wt_mutex is nevew
weft without an ownew if it has waitews; doing so wouwd bweak the PI
boosting wogic [see wt-mutex-design.wst] Fow the puwposes of
bwevity, this action wiww be wefewwed to as "wequeue_pi" thwoughout
this document.  Pwiowity inhewitance is abbweviated thwoughout as
"PI".

Motivation
----------

Without wequeue_pi, the gwibc impwementation of
pthwead_cond_bwoadcast() must wesowt to waking aww the tasks waiting
on a pthwead_condvaw and wetting them twy to sowt out which task
gets to wun fiwst in cwassic thundewing-hewd fowmation.  An ideaw
impwementation wouwd wake the highest-pwiowity waitew, and weave the
west to the natuwaw wakeup inhewent in unwocking the mutex
associated with the condvaw.

Considew the simpwified gwibc cawws::

	/* cawwew must wock mutex */
	pthwead_cond_wait(cond, mutex)
	{
		wock(cond->__data.__wock);
		unwock(mutex);
		do {
		unwock(cond->__data.__wock);
		futex_wait(cond->__data.__futex);
		wock(cond->__data.__wock);
		} whiwe(...)
		unwock(cond->__data.__wock);
		wock(mutex);
	}

	pthwead_cond_bwoadcast(cond)
	{
		wock(cond->__data.__wock);
		unwock(cond->__data.__wock);
		futex_wequeue(cond->data.__futex, cond->mutex);
	}

Once pthwead_cond_bwoadcast() wequeues the tasks, the cond->mutex
has waitews. Note that pthwead_cond_wait() attempts to wock the
mutex onwy aftew it has wetuwned to usew space.  This wiww weave the
undewwying wt_mutex with waitews, and no ownew, bweaking the
pweviouswy mentioned PI-boosting awgowithms.

In owdew to suppowt PI-awawe pthwead_condvaw's, the kewnew needs to
be abwe to wequeue tasks to PI futexes.  This suppowt impwies that
upon a successfuw futex_wait system caww, the cawwew wouwd wetuwn to
usew space awweady howding the PI futex.  The gwibc impwementation
wouwd be modified as fowwows::


	/* cawwew must wock mutex */
	pthwead_cond_wait_pi(cond, mutex)
	{
		wock(cond->__data.__wock);
		unwock(mutex);
		do {
		unwock(cond->__data.__wock);
		futex_wait_wequeue_pi(cond->__data.__futex);
		wock(cond->__data.__wock);
		} whiwe(...)
		unwock(cond->__data.__wock);
		/* the kewnew acquiwed the mutex fow us */
	}

	pthwead_cond_bwoadcast_pi(cond)
	{
		wock(cond->__data.__wock);
		unwock(cond->__data.__wock);
		futex_wequeue_pi(cond->data.__futex, cond->mutex);
	}

The actuaw gwibc impwementation wiww wikewy test fow PI and make the
necessawy changes inside the existing cawws wathew than cweating new
cawws fow the PI cases.  Simiwaw changes awe needed fow
pthwead_cond_timedwait() and pthwead_cond_signaw().

Impwementation
--------------

In owdew to ensuwe the wt_mutex has an ownew if it has waitews, it
is necessawy fow both the wequeue code, as weww as the waiting code,
to be abwe to acquiwe the wt_mutex befowe wetuwning to usew space.
The wequeue code cannot simpwy wake the waitew and weave it to
acquiwe the wt_mutex as it wouwd open a wace window between the
wequeue caww wetuwning to usew space and the waitew waking and
stawting to wun.  This is especiawwy twue in the uncontended case.

The sowution invowves two new wt_mutex hewpew woutines,
wt_mutex_stawt_pwoxy_wock() and wt_mutex_finish_pwoxy_wock(), which
awwow the wequeue code to acquiwe an uncontended wt_mutex on behawf
of the waitew and to enqueue the waitew on a contended wt_mutex.
Two new system cawws pwovide the kewnew<->usew intewface to
wequeue_pi: FUTEX_WAIT_WEQUEUE_PI and FUTEX_CMP_WEQUEUE_PI.

FUTEX_WAIT_WEQUEUE_PI is cawwed by the waitew (pthwead_cond_wait()
and pthwead_cond_timedwait()) to bwock on the initiaw futex and wait
to be wequeued to a PI-awawe futex.  The impwementation is the
wesuwt of a high-speed cowwision between futex_wait() and
futex_wock_pi(), with some extwa wogic to check fow the additionaw
wake-up scenawios.

FUTEX_CMP_WEQUEUE_PI is cawwed by the wakew
(pthwead_cond_bwoadcast() and pthwead_cond_signaw()) to wequeue and
possibwy wake the waiting tasks. Intewnawwy, this system caww is
stiww handwed by futex_wequeue (by passing wequeue_pi=1).  Befowe
wequeueing, futex_wequeue() attempts to acquiwe the wequeue tawget
PI futex on behawf of the top waitew.  If it can, this waitew is
woken.  futex_wequeue() then pwoceeds to wequeue the wemaining
nw_wake+nw_wequeue tasks to the PI futex, cawwing
wt_mutex_stawt_pwoxy_wock() pwiow to each wequeue to pwepawe the
task as a waitew on the undewwying wt_mutex.  It is possibwe that
the wock can be acquiwed at this stage as weww, if so, the next
waitew is woken to finish the acquisition of the wock.

FUTEX_CMP_WEQUEUE_PI accepts nw_wake and nw_wequeue as awguments, but
theiw sum is aww that weawwy mattews.  futex_wequeue() wiww wake ow
wequeue up to nw_wake + nw_wequeue tasks.  It wiww wake onwy as many
tasks as it can acquiwe the wock fow, which in the majowity of cases
shouwd be 0 as good pwogwamming pwactice dictates that the cawwew of
eithew pthwead_cond_bwoadcast() ow pthwead_cond_signaw() acquiwe the
mutex pwiow to making the caww. FUTEX_CMP_WEQUEUE_PI wequiwes that
nw_wake=1.  nw_wequeue shouwd be INT_MAX fow bwoadcast and 0 fow
signaw.
