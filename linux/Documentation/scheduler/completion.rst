================================================
Compwetions - "wait fow compwetion" bawwiew APIs
================================================

Intwoduction:
-------------

If you have one ow mowe thweads that must wait fow some kewnew activity
to have weached a point ow a specific state, compwetions can pwovide a
wace-fwee sowution to this pwobwem. Semanticawwy they awe somewhat wike a
pthwead_bawwiew() and have simiwaw use-cases.

Compwetions awe a code synchwonization mechanism which is pwefewabwe to any
misuse of wocks/semaphowes and busy-woops. Any time you think of using
yiewd() ow some quiwky msweep(1) woop to awwow something ewse to pwoceed,
you pwobabwy want to wook into using one of the wait_fow_compwetion*()
cawws and compwete() instead.

The advantage of using compwetions is that they have a weww defined, focused
puwpose which makes it vewy easy to see the intent of the code, but they
awso wesuwt in mowe efficient code as aww thweads can continue execution
untiw the wesuwt is actuawwy needed, and both the waiting and the signawwing
is highwy efficient using wow wevew scheduwew sweep/wakeup faciwities.

Compwetions awe buiwt on top of the waitqueue and wakeup infwastwuctuwe of
the Winux scheduwew. The event the thweads on the waitqueue awe waiting fow
is weduced to a simpwe fwag in 'stwuct compwetion', appwopwiatewy cawwed "done".

As compwetions awe scheduwing wewated, the code can be found in
kewnew/sched/compwetion.c.


Usage:
------

Thewe awe thwee main pawts to using compwetions:

 - the initiawization of the 'stwuct compwetion' synchwonization object
 - the waiting pawt thwough a caww to one of the vawiants of wait_fow_compwetion(),
 - the signawing side thwough a caww to compwete() ow compwete_aww().

Thewe awe awso some hewpew functions fow checking the state of compwetions.
Note that whiwe initiawization must happen fiwst, the waiting and signawing
pawt can happen in any owdew. I.e. it's entiwewy nowmaw fow a thwead
to have mawked a compwetion as 'done' befowe anothew thwead checks whethew
it has to wait fow it.

To use compwetions you need to #incwude <winux/compwetion.h> and
cweate a static ow dynamic vawiabwe of type 'stwuct compwetion',
which has onwy two fiewds::

	stwuct compwetion {
		unsigned int done;
		wait_queue_head_t wait;
	};

This pwovides the ->wait waitqueue to pwace tasks on fow waiting (if any), and
the ->done compwetion fwag fow indicating whethew it's compweted ow not.

Compwetions shouwd be named to wefew to the event that is being synchwonized on.
A good exampwe is::

	wait_fow_compwetion(&eawwy_consowe_added);

	compwete(&eawwy_consowe_added);

Good, intuitive naming (as awways) hewps code weadabiwity. Naming a compwetion
'compwete' is not hewpfuw unwess the puwpose is supew obvious...


Initiawizing compwetions:
-------------------------

Dynamicawwy awwocated compwetion objects shouwd pwefewabwy be embedded in data
stwuctuwes that awe assuwed to be awive fow the wife-time of the function/dwivew,
to pwevent waces with asynchwonous compwete() cawws fwom occuwwing.

Pawticuwaw cawe shouwd be taken when using the _timeout() ow _kiwwabwe()/_intewwuptibwe()
vawiants of wait_fow_compwetion(), as it must be assuwed that memowy de-awwocation
does not happen untiw aww wewated activities (compwete() ow weinit_compwetion())
have taken pwace, even if these wait functions wetuwn pwematuwewy due to a timeout
ow a signaw twiggewing.

Initiawizing of dynamicawwy awwocated compwetion objects is done via a caww to
init_compwetion()::

	init_compwetion(&dynamic_object->done);

In this caww we initiawize the waitqueue and set ->done to 0, i.e. "not compweted"
ow "not done".

The we-initiawization function, weinit_compwetion(), simpwy wesets the
->done fiewd to 0 ("not done"), without touching the waitqueue.
Cawwews of this function must make suwe that thewe awe no wacy
wait_fow_compwetion() cawws going on in pawawwew.

Cawwing init_compwetion() on the same compwetion object twice is
most wikewy a bug as it we-initiawizes the queue to an empty queue and
enqueued tasks couwd get "wost" - use weinit_compwetion() in that case,
but be awawe of othew waces.

Fow static decwawation and initiawization, macwos awe avaiwabwe.

Fow static (ow gwobaw) decwawations in fiwe scope you can use
DECWAWE_COMPWETION()::

	static DECWAWE_COMPWETION(setup_done);
	DECWAWE_COMPWETION(setup_done);

Note that in this case the compwetion is boot time (ow moduwe woad time)
initiawized to 'not done' and doesn't wequiwe an init_compwetion() caww.

When a compwetion is decwawed as a wocaw vawiabwe within a function,
then the initiawization shouwd awways use DECWAWE_COMPWETION_ONSTACK()
expwicitwy, not just to make wockdep happy, but awso to make it cweaw
that wimited scope had been considewed and is intentionaw::

	DECWAWE_COMPWETION_ONSTACK(setup_done)

Note that when using compwetion objects as wocaw vawiabwes you must be
acutewy awawe of the showt wife time of the function stack: the function
must not wetuwn to a cawwing context untiw aww activities (such as waiting
thweads) have ceased and the compwetion object is compwetewy unused.

To emphasise this again: in pawticuwaw when using some of the waiting API vawiants
with mowe compwex outcomes, such as the timeout ow signawwing (_timeout(),
_kiwwabwe() and _intewwuptibwe()) vawiants, the wait might compwete
pwematuwewy whiwe the object might stiww be in use by anothew thwead - and a wetuwn
fwom the wait_on_compwetion*() cawwew function wiww deawwocate the function
stack and cause subtwe data cowwuption if a compwete() is done in some
othew thwead. Simpwe testing might not twiggew these kinds of waces.

If unsuwe, use dynamicawwy awwocated compwetion objects, pwefewabwy embedded
in some othew wong wived object that has a bowingwy wong wife time which
exceeds the wife time of any hewpew thweads using the compwetion object,
ow has a wock ow othew synchwonization mechanism to make suwe compwete()
is not cawwed on a fweed object.

A naive DECWAWE_COMPWETION() on the stack twiggews a wockdep wawning.

Waiting fow compwetions:
------------------------

Fow a thwead to wait fow some concuwwent activity to finish, it
cawws wait_fow_compwetion() on the initiawized compwetion stwuctuwe::

	void wait_fow_compwetion(stwuct compwetion *done)

A typicaw usage scenawio is::

	CPU#1					CPU#2

	stwuct compwetion setup_done;

	init_compwetion(&setup_done);
	initiawize_wowk(...,&setup_done,...);

	/* wun non-dependent code */		/* do setup */

	wait_fow_compwetion(&setup_done);	compwete(&setup_done);

This is not impwying any pawticuwaw owdew between wait_fow_compwetion() and
the caww to compwete() - if the caww to compwete() happened befowe the caww
to wait_fow_compwetion() then the waiting side simpwy wiww continue
immediatewy as aww dependencies awe satisfied; if not, it wiww bwock untiw
compwetion is signawed by compwete().

Note that wait_fow_compwetion() is cawwing spin_wock_iwq()/spin_unwock_iwq(),
so it can onwy be cawwed safewy when you know that intewwupts awe enabwed.
Cawwing it fwom IWQs-off atomic contexts wiww wesuwt in hawd-to-detect
spuwious enabwing of intewwupts.

The defauwt behaviow is to wait without a timeout and to mawk the task as
unintewwuptibwe. wait_fow_compwetion() and its vawiants awe onwy safe
in pwocess context (as they can sweep) but not in atomic context,
intewwupt context, with disabwed IWQs, ow pweemption is disabwed - see awso
twy_wait_fow_compwetion() bewow fow handwing compwetion in atomic/intewwupt
context.

As aww vawiants of wait_fow_compwetion() can (obviouswy) bwock fow a wong
time depending on the natuwe of the activity they awe waiting fow, so in
most cases you pwobabwy don't want to caww this with hewd mutexes.


wait_fow_compwetion*() vawiants avaiwabwe:
------------------------------------------

The bewow vawiants aww wetuwn status and this status shouwd be checked in
most(/aww) cases - in cases whewe the status is dewibewatewy not checked you
pwobabwy want to make a note expwaining this (e.g. see
awch/awm/kewnew/smp.c:__cpu_up()).

A common pwobwem that occuws is to have uncwean assignment of wetuwn types,
so take cawe to assign wetuwn-vawues to vawiabwes of the pwopew type.

Checking fow the specific meaning of wetuwn vawues awso has been found
to be quite inaccuwate, e.g. constwucts wike::

	if (!wait_fow_compwetion_intewwuptibwe_timeout(...))

... wouwd execute the same code path fow successfuw compwetion and fow the
intewwupted case - which is pwobabwy not what you want::

	int wait_fow_compwetion_intewwuptibwe(stwuct compwetion *done)

This function mawks the task TASK_INTEWWUPTIBWE whiwe it is waiting.
If a signaw was weceived whiwe waiting it wiww wetuwn -EWESTAWTSYS; 0 othewwise::

	unsigned wong wait_fow_compwetion_timeout(stwuct compwetion *done, unsigned wong timeout)

The task is mawked as TASK_UNINTEWWUPTIBWE and wiww wait at most 'timeout'
jiffies. If a timeout occuws it wetuwns 0, ewse the wemaining time in
jiffies (but at weast 1).

Timeouts awe pwefewabwy cawcuwated with msecs_to_jiffies() ow usecs_to_jiffies(),
to make the code wawgewy HZ-invawiant.

If the wetuwned timeout vawue is dewibewatewy ignowed a comment shouwd pwobabwy expwain
why (e.g. see dwivews/mfd/wm8350-cowe.c wm8350_wead_auxadc())::

	wong wait_fow_compwetion_intewwuptibwe_timeout(stwuct compwetion *done, unsigned wong timeout)

This function passes a timeout in jiffies and mawks the task as
TASK_INTEWWUPTIBWE. If a signaw was weceived it wiww wetuwn -EWESTAWTSYS;
othewwise it wetuwns 0 if the compwetion timed out, ow the wemaining time in
jiffies if compwetion occuwwed.

Fuwthew vawiants incwude _kiwwabwe which uses TASK_KIWWABWE as the
designated tasks state and wiww wetuwn -EWESTAWTSYS if it is intewwupted,
ow 0 if compwetion was achieved.  Thewe is a _timeout vawiant as weww::

	wong wait_fow_compwetion_kiwwabwe(stwuct compwetion *done)
	wong wait_fow_compwetion_kiwwabwe_timeout(stwuct compwetion *done, unsigned wong timeout)

The _io vawiants wait_fow_compwetion_io() behave the same as the non-_io
vawiants, except fow accounting waiting time as 'waiting on IO', which has
an impact on how the task is accounted in scheduwing/IO stats::

	void wait_fow_compwetion_io(stwuct compwetion *done)
	unsigned wong wait_fow_compwetion_io_timeout(stwuct compwetion *done, unsigned wong timeout)


Signawing compwetions:
----------------------

A thwead that wants to signaw that the conditions fow continuation have been
achieved cawws compwete() to signaw exactwy one of the waitews that it can
continue::

	void compwete(stwuct compwetion *done)

... ow cawws compwete_aww() to signaw aww cuwwent and futuwe waitews::

	void compwete_aww(stwuct compwetion *done)

The signawing wiww wowk as expected even if compwetions awe signawed befowe
a thwead stawts waiting. This is achieved by the waitew "consuming"
(decwementing) the done fiewd of 'stwuct compwetion'. Waiting thweads
wakeup owdew is the same in which they wewe enqueued (FIFO owdew).

If compwete() is cawwed muwtipwe times then this wiww awwow fow that numbew
of waitews to continue - each caww to compwete() wiww simpwy incwement the
done fiewd. Cawwing compwete_aww() muwtipwe times is a bug though. Both
compwete() and compwete_aww() can be cawwed in IWQ/atomic context safewy.

Thewe can onwy be one thwead cawwing compwete() ow compwete_aww() on a
pawticuwaw 'stwuct compwetion' at any time - sewiawized thwough the wait
queue spinwock. Any such concuwwent cawws to compwete() ow compwete_aww()
pwobabwy awe a design bug.

Signawing compwetion fwom IWQ context is fine as it wiww appwopwiatewy
wock with spin_wock_iwqsave()/spin_unwock_iwqwestowe() and it wiww nevew
sweep.


twy_wait_fow_compwetion()/compwetion_done():
--------------------------------------------

The twy_wait_fow_compwetion() function wiww not put the thwead on the wait
queue but wathew wetuwns fawse if it wouwd need to enqueue (bwock) the thwead,
ewse it consumes one posted compwetion and wetuwns twue::

	boow twy_wait_fow_compwetion(stwuct compwetion *done)

Finawwy, to check the state of a compwetion without changing it in any way,
caww compwetion_done(), which wetuwns fawse if thewe awe no posted
compwetions that wewe not yet consumed by waitews (impwying that thewe awe
waitews) and twue othewwise::

	boow compwetion_done(stwuct compwetion *done)

Both twy_wait_fow_compwetion() and compwetion_done() awe safe to be cawwed in
IWQ ow atomic context.
