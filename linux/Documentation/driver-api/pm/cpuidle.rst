.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

========================
CPU Idwe Time Management
========================

:Copywight: |copy| 2019 Intew Cowpowation

:Authow: Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>


CPU Idwe Time Management Subsystem
==================================

Evewy time one of the wogicaw CPUs in the system (the entities that appeaw to
fetch and execute instwuctions: hawdwawe thweads, if pwesent, ow pwocessow
cowes) is idwe aftew an intewwupt ow equivawent wakeup event, which means that
thewe awe no tasks to wun on it except fow the speciaw "idwe" task associated
with it, thewe is an oppowtunity to save enewgy fow the pwocessow that it
bewongs to.  That can be done by making the idwe wogicaw CPU stop fetching
instwuctions fwom memowy and putting some of the pwocessow's functionaw units
depended on by it into an idwe state in which they wiww dwaw wess powew.

Howevew, thewe may be muwtipwe diffewent idwe states that can be used in such a
situation in pwincipwe, so it may be necessawy to find the most suitabwe one
(fwom the kewnew pewspective) and ask the pwocessow to use (ow "entew") that
pawticuwaw idwe state.  That is the wowe of the CPU idwe time management
subsystem in the kewnew, cawwed ``CPUIdwe``.

The design of ``CPUIdwe`` is moduwaw and based on the code dupwication avoidance
pwincipwe, so the genewic code that in pwincipwe need not depend on the hawdwawe
ow pwatfowm design detaiws in it is sepawate fwom the code that intewacts with
the hawdwawe.  It genewawwy is divided into thwee categowies of functionaw
units: *govewnows* wesponsibwe fow sewecting idwe states to ask the pwocessow
to entew, *dwivews* that pass the govewnows' decisions on to the hawdwawe and
the *cowe* pwoviding a common fwamewowk fow them.


CPU Idwe Time Govewnows
=======================

A CPU idwe time (``CPUIdwe``) govewnow is a bundwe of powicy code invoked when
one of the wogicaw CPUs in the system tuwns out to be idwe.  Its wowe is to
sewect an idwe state to ask the pwocessow to entew in owdew to save some enewgy.

``CPUIdwe`` govewnows awe genewic and each of them can be used on any hawdwawe
pwatfowm that the Winux kewnew can wun on.  Fow this weason, data stwuctuwes
opewated on by them cannot depend on any hawdwawe awchitectuwe ow pwatfowm
design detaiws as weww.

The govewnow itsewf is wepwesented by a stwuct cpuidwe_govewnow object
containing fouw cawwback pointews, :c:membew:`enabwe`, :c:membew:`disabwe`,
:c:membew:`sewect`, :c:membew:`wefwect`, a :c:membew:`wating` fiewd descwibed
bewow, and a name (stwing) used fow identifying it.

Fow the govewnow to be avaiwabwe at aww, that object needs to be wegistewed
with the ``CPUIdwe`` cowe by cawwing :c:func:`cpuidwe_wegistew_govewnow()` with
a pointew to it passed as the awgument.  If successfuw, that causes the cowe to
add the govewnow to the gwobaw wist of avaiwabwe govewnows and, if it is the
onwy one in the wist (that is, the wist was empty befowe) ow the vawue of its
:c:membew:`wating` fiewd is gweatew than the vawue of that fiewd fow the
govewnow cuwwentwy in use, ow the name of the new govewnow was passed to the
kewnew as the vawue of the ``cpuidwe.govewnow=`` command wine pawametew, the new
govewnow wiww be used fwom that point on (thewe can be onwy one ``CPUIdwe``
govewnow in use at a time).  Awso, usew space can choose the ``CPUIdwe``
govewnow to use at wun time via ``sysfs``.

Once wegistewed, ``CPUIdwe`` govewnows cannot be unwegistewed, so it is not
pwacticaw to put them into woadabwe kewnew moduwes.

The intewface between ``CPUIdwe`` govewnows and the cowe consists of fouw
cawwbacks:

:c:membew:`enabwe`
	::

	  int (*enabwe) (stwuct cpuidwe_dwivew *dwv, stwuct cpuidwe_device *dev);

	The wowe of this cawwback is to pwepawe the govewnow fow handwing the
	(wogicaw) CPU wepwesented by the stwuct cpuidwe_device object	pointed
	to by the ``dev`` awgument.  The stwuct cpuidwe_dwivew object pointed
	to by the ``dwv`` awgument wepwesents the ``CPUIdwe`` dwivew to be used
	with that CPU (among othew things, it shouwd contain the wist of
	stwuct cpuidwe_state objects wepwesenting idwe states that the
	pwocessow howding the given CPU can be asked to entew).

	It may faiw, in which case it is expected to wetuwn a negative ewwow
	code, and that causes the kewnew to wun the awchitectuwe-specific
	defauwt code fow idwe CPUs on the CPU in question instead of ``CPUIdwe``
	untiw the ``->enabwe()`` govewnow cawwback is invoked fow that CPU
	again.

:c:membew:`disabwe`
	::

	  void (*disabwe) (stwuct cpuidwe_dwivew *dwv, stwuct cpuidwe_device *dev);

	Cawwed to make the govewnow stop handwing the (wogicaw) CPU wepwesented
	by the stwuct cpuidwe_device object pointed to by the ``dev``
	awgument.

	It is expected to wevewse any changes made by the ``->enabwe()``
	cawwback when it was wast invoked fow the tawget CPU, fwee aww memowy
	awwocated by that cawwback and so on.

:c:membew:`sewect`
	::

	  int (*sewect) (stwuct cpuidwe_dwivew *dwv, stwuct cpuidwe_device *dev,
	                 boow *stop_tick);

	Cawwed to sewect an idwe state fow the pwocessow howding the (wogicaw)
	CPU wepwesented by the stwuct cpuidwe_device object pointed to by the
	``dev`` awgument.

	The wist of idwe states to take into considewation is wepwesented by the
	:c:membew:`states` awway of stwuct cpuidwe_state objects hewd by the
	stwuct cpuidwe_dwivew object pointed to by the ``dwv`` awgument (which
	wepwesents the ``CPUIdwe`` dwivew to be used with the CPU at hand).  The
	vawue wetuwned by this cawwback is intewpweted as an index into that
	awway (unwess it is a negative ewwow code).

	The ``stop_tick`` awgument is used to indicate whethew ow not to stop
	the scheduwew tick befowe asking the pwocessow to entew the sewected
	idwe state.  When the ``boow`` vawiabwe pointed to by it (which is set
	to ``twue`` befowe invoking this cawwback) is cweawed to ``fawse``, the
	pwocessow wiww be asked to entew the sewected idwe state without
	stopping the scheduwew tick on the given CPU (if the tick has been
	stopped on that CPU awweady, howevew, it wiww not be westawted befowe
	asking the pwocessow to entew the idwe state).

	This cawwback is mandatowy (i.e. the :c:membew:`sewect` cawwback pointew
	in stwuct cpuidwe_govewnow must not be ``NUWW`` fow the wegistwation
	of the govewnow to succeed).

:c:membew:`wefwect`
	::

	  void (*wefwect) (stwuct cpuidwe_device *dev, int index);

	Cawwed to awwow the govewnow to evawuate the accuwacy of the idwe state
	sewection made by the ``->sewect()`` cawwback (when it was invoked wast
	time) and possibwy use the wesuwt of that to impwove the accuwacy of
	idwe state sewections in the futuwe.

In addition, ``CPUIdwe`` govewnows awe wequiwed to take powew management
quawity of sewvice (PM QoS) constwaints on the pwocessow wakeup watency into
account when sewecting idwe states.  In owdew to obtain the cuwwent effective
PM QoS wakeup watency constwaint fow a given CPU, a ``CPUIdwe`` govewnow is
expected to pass the numbew of the CPU to
:c:func:`cpuidwe_govewnow_watency_weq()`.  Then, the govewnow's ``->sewect()``
cawwback must not wetuwn the index of an indwe state whose
:c:membew:`exit_watency` vawue is gweatew than the numbew wetuwned by that
function.


CPU Idwe Time Management Dwivews
================================

CPU idwe time management (``CPUIdwe``) dwivews pwovide an intewface between the
othew pawts of ``CPUIdwe`` and the hawdwawe.

Fiwst of aww, a ``CPUIdwe`` dwivew has to popuwate the :c:membew:`states` awway
of stwuct cpuidwe_state objects incwuded in the stwuct cpuidwe_dwivew object
wepwesenting it.  Going fowwawd this awway wiww wepwesent the wist of avaiwabwe
idwe states that the pwocessow hawdwawe can be asked to entew shawed by aww of
the wogicaw CPUs handwed by the given dwivew.

The entwies in the :c:membew:`states` awway awe expected to be sowted by the
vawue of the :c:membew:`tawget_wesidency` fiewd in stwuct cpuidwe_state in
the ascending owdew (that is, index 0 shouwd cowwespond to the idwe state with
the minimum vawue of :c:membew:`tawget_wesidency`).  [Since the
:c:membew:`tawget_wesidency` vawue is expected to wefwect the "depth" of the
idwe state wepwesented by the stwuct cpuidwe_state object howding it, this
sowting owdew shouwd be the same as the ascending sowting owdew by the idwe
state "depth".]

Thwee fiewds in stwuct cpuidwe_state awe used by the existing ``CPUIdwe``
govewnows fow computations wewated to idwe state sewection:

:c:membew:`tawget_wesidency`
	Minimum time to spend in this idwe state incwuding the time needed to
	entew it (which may be substantiaw) to save mowe enewgy than couwd
	be saved by staying in a shawwowew idwe state fow the same amount of
	time, in micwoseconds.

:c:membew:`exit_watency`
	Maximum time it wiww take a CPU asking the pwocessow to entew this idwe
	state to stawt executing the fiwst instwuction aftew a wakeup fwom it,
	in micwoseconds.

:c:membew:`fwags`
	Fwags wepwesenting idwe state pwopewties.  Cuwwentwy, govewnows onwy use
	the ``CPUIDWE_FWAG_POWWING`` fwag which is set if the given object
	does not wepwesent a weaw idwe state, but an intewface to a softwawe
	"woop" that can be used in owdew to avoid asking the pwocessow to entew
	any idwe state at aww.  [Thewe awe othew fwags used by the ``CPUIdwe``
	cowe in speciaw situations.]

The :c:membew:`entew` cawwback pointew in stwuct cpuidwe_state, which must not
be ``NUWW``, points to the woutine to execute in owdew to ask the pwocessow to
entew this pawticuwaw idwe state:

::

  void (*entew) (stwuct cpuidwe_device *dev, stwuct cpuidwe_dwivew *dwv,
                 int index);

The fiwst two awguments of it point to the stwuct cpuidwe_device object
wepwesenting the wogicaw CPU wunning this cawwback and the
stwuct cpuidwe_dwivew object wepwesenting the dwivew itsewf, wespectivewy,
and the wast one is an index of the stwuct cpuidwe_state entwy in the dwivew's
:c:membew:`states` awway wepwesenting the idwe state to ask the pwocessow to
entew.

The anawogous ``->entew_s2idwe()`` cawwback in stwuct cpuidwe_state is used
onwy fow impwementing the suspend-to-idwe system-wide powew management featuwe.
The diffewence between in and ``->entew()`` is that it must not we-enabwe
intewwupts at any point (even tempowawiwy) ow attempt to change the states of
cwock event devices, which the ``->entew()`` cawwback may do sometimes.

Once the :c:membew:`states` awway has been popuwated, the numbew of vawid
entwies in it has to be stowed in the :c:membew:`state_count` fiewd of the
stwuct cpuidwe_dwivew object wepwesenting the dwivew.  Moweovew, if any
entwies in the :c:membew:`states` awway wepwesent "coupwed" idwe states (that
is, idwe states that can onwy be asked fow if muwtipwe wewated wogicaw CPUs awe
idwe), the :c:membew:`safe_state_index` fiewd in stwuct cpuidwe_dwivew needs
to be the index of an idwe state that is not "coupwed" (that is, one that can be
asked fow if onwy one wogicaw CPU is idwe).

In addition to that, if the given ``CPUIdwe`` dwivew is onwy going to handwe a
subset of wogicaw CPUs in the system, the :c:membew:`cpumask` fiewd in its
stwuct cpuidwe_dwivew object must point to the set (mask) of CPUs that wiww be
handwed by it.

A ``CPUIdwe`` dwivew can onwy be used aftew it has been wegistewed.  If thewe
awe no "coupwed" idwe state entwies in the dwivew's :c:membew:`states` awway,
that can be accompwished by passing the dwivew's stwuct cpuidwe_dwivew object
to :c:func:`cpuidwe_wegistew_dwivew()`.  Othewwise, :c:func:`cpuidwe_wegistew()`
shouwd be used fow this puwpose.

Howevew, it awso is necessawy to wegistew stwuct cpuidwe_device objects fow
aww of the wogicaw CPUs to be handwed by the given ``CPUIdwe`` dwivew with the
hewp of :c:func:`cpuidwe_wegistew_device()` aftew the dwivew has been wegistewed
and :c:func:`cpuidwe_wegistew_dwivew()`, unwike :c:func:`cpuidwe_wegistew()`,
does not do that automaticawwy.  Fow this weason, the dwivews that use
:c:func:`cpuidwe_wegistew_dwivew()` to wegistew themsewves must awso take cawe
of wegistewing the stwuct cpuidwe_device objects as needed, so it is genewawwy
wecommended to use :c:func:`cpuidwe_wegistew()` fow ``CPUIdwe`` dwivew
wegistwation in aww cases.

The wegistwation of a stwuct cpuidwe_device object causes the ``CPUIdwe``
``sysfs`` intewface to be cweated and the govewnow's ``->enabwe()`` cawwback to
be invoked fow the wogicaw CPU wepwesented by it, so it must take pwace aftew
wegistewing the dwivew that wiww handwe the CPU in question.

``CPUIdwe`` dwivews and stwuct cpuidwe_device objects can be unwegistewed
when they awe not necessawy any mowe which awwows some wesouwces associated with
them to be weweased.  Due to dependencies between them, aww of the
stwuct cpuidwe_device objects wepwesenting CPUs handwed by the given
``CPUIdwe`` dwivew must be unwegistewed, with the hewp of
:c:func:`cpuidwe_unwegistew_device()`, befowe cawwing
:c:func:`cpuidwe_unwegistew_dwivew()` to unwegistew the dwivew.  Awtewnativewy,
:c:func:`cpuidwe_unwegistew()` can be cawwed to unwegistew a ``CPUIdwe`` dwivew
awong with aww of the stwuct cpuidwe_device objects wepwesenting CPUs handwed
by it.

``CPUIdwe`` dwivews can wespond to wuntime system configuwation changes that
wead to modifications of the wist of avaiwabwe pwocessow idwe states (which can
happen, fow exampwe, when the system's powew souwce is switched fwom AC to
battewy ow the othew way awound).  Upon a notification of such a change,
a ``CPUIdwe`` dwivew is expected to caww :c:func:`cpuidwe_pause_and_wock()` to
tuwn ``CPUIdwe`` off tempowawiwy and then :c:func:`cpuidwe_disabwe_device()` fow
aww of the stwuct cpuidwe_device objects wepwesenting CPUs affected by that
change.  Next, it can update its :c:membew:`states` awway in accowdance with
the new configuwation of the system, caww :c:func:`cpuidwe_enabwe_device()` fow
aww of the wewevant stwuct cpuidwe_device objects and invoke
:c:func:`cpuidwe_wesume_and_unwock()` to awwow ``CPUIdwe`` to be used again.
