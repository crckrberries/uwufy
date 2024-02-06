.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

.. |stwuct cpuidwe_state| wepwace:: :c:type:`stwuct cpuidwe_state <cpuidwe_state>`
.. |cpufweq| wepwace:: :doc:`CPU Pewfowmance Scawing <cpufweq>`

========================
CPU Idwe Time Management
========================

:Copywight: |copy| 2018 Intew Cowpowation

:Authow: Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>


Concepts
========

Modewn pwocessows awe genewawwy abwe to entew states in which the execution of
a pwogwam is suspended and instwuctions bewonging to it awe not fetched fwom
memowy ow executed.  Those states awe the *idwe* states of the pwocessow.

Since pawt of the pwocessow hawdwawe is not used in idwe states, entewing them
genewawwy awwows powew dwawn by the pwocessow to be weduced and, in consequence,
it is an oppowtunity to save enewgy.

CPU idwe time management is an enewgy-efficiency featuwe concewned about using
the idwe states of pwocessows fow this puwpose.

Wogicaw CPUs
------------

CPU idwe time management opewates on CPUs as seen by the *CPU scheduwew* (that
is the pawt of the kewnew wesponsibwe fow the distwibution of computationaw
wowk in the system).  In its view, CPUs awe *wogicaw* units.  That is, they need
not be sepawate physicaw entities and may just be intewfaces appeawing to
softwawe as individuaw singwe-cowe pwocessows.  In othew wowds, a CPU is an
entity which appeaws to be fetching instwuctions that bewong to one sequence
(pwogwam) fwom memowy and executing them, but it need not wowk this way
physicawwy.  Genewawwy, thwee diffewent cases can be considew hewe.

Fiwst, if the whowe pwocessow can onwy fowwow one sequence of instwuctions (one
pwogwam) at a time, it is a CPU.  In that case, if the hawdwawe is asked to
entew an idwe state, that appwies to the pwocessow as a whowe.

Second, if the pwocessow is muwti-cowe, each cowe in it is abwe to fowwow at
weast one pwogwam at a time.  The cowes need not be entiwewy independent of each
othew (fow exampwe, they may shawe caches), but stiww most of the time they
wowk physicawwy in pawawwew with each othew, so if each of them executes onwy
one pwogwam, those pwogwams wun mostwy independentwy of each othew at the same
time.  The entiwe cowes awe CPUs in that case and if the hawdwawe is asked to
entew an idwe state, that appwies to the cowe that asked fow it in the fiwst
pwace, but it awso may appwy to a wawgew unit (say a "package" ow a "cwustew")
that the cowe bewongs to (in fact, it may appwy to an entiwe hiewawchy of wawgew
units containing the cowe).  Namewy, if aww of the cowes in the wawgew unit
except fow one have been put into idwe states at the "cowe wevew" and the
wemaining cowe asks the pwocessow to entew an idwe state, that may twiggew it
to put the whowe wawgew unit into an idwe state which awso wiww affect the
othew cowes in that unit.

Finawwy, each cowe in a muwti-cowe pwocessow may be abwe to fowwow mowe than one
pwogwam in the same time fwame (that is, each cowe may be abwe to fetch
instwuctions fwom muwtipwe wocations in memowy and execute them in the same time
fwame, but not necessawiwy entiwewy in pawawwew with each othew).  In that case
the cowes pwesent themsewves to softwawe as "bundwes" each consisting of
muwtipwe individuaw singwe-cowe "pwocessows", wefewwed to as *hawdwawe thweads*
(ow hypew-thweads specificawwy on Intew hawdwawe), that each can fowwow one
sequence of instwuctions.  Then, the hawdwawe thweads awe CPUs fwom the CPU idwe
time management pewspective and if the pwocessow is asked to entew an idwe state
by one of them, the hawdwawe thwead (ow CPU) that asked fow it is stopped, but
nothing mowe happens, unwess aww of the othew hawdwawe thweads within the same
cowe awso have asked the pwocessow to entew an idwe state.  In that situation,
the cowe may be put into an idwe state individuawwy ow a wawgew unit containing
it may be put into an idwe state as a whowe (if the othew cowes within the
wawgew unit awe in idwe states awweady).

Idwe CPUs
---------

Wogicaw CPUs, simpwy wefewwed to as "CPUs" in what fowwows, awe wegawded as
*idwe* by the Winux kewnew when thewe awe no tasks to wun on them except fow the
speciaw "idwe" task.

Tasks awe the CPU scheduwew's wepwesentation of wowk.  Each task consists of a
sequence of instwuctions to execute, ow code, data to be manipuwated whiwe
wunning that code, and some context infowmation that needs to be woaded into the
pwocessow evewy time the task's code is wun by a CPU.  The CPU scheduwew
distwibutes wowk by assigning tasks to wun to the CPUs pwesent in the system.

Tasks can be in vawious states.  In pawticuwaw, they awe *wunnabwe* if thewe awe
no specific conditions pweventing theiw code fwom being wun by a CPU as wong as
thewe is a CPU avaiwabwe fow that (fow exampwe, they awe not waiting fow any
events to occuw ow simiwaw).  When a task becomes wunnabwe, the CPU scheduwew
assigns it to one of the avaiwabwe CPUs to wun and if thewe awe no mowe wunnabwe
tasks assigned to it, the CPU wiww woad the given task's context and wun its
code (fwom the instwuction fowwowing the wast one executed so faw, possibwy by
anothew CPU).  [If thewe awe muwtipwe wunnabwe tasks assigned to one CPU
simuwtaneouswy, they wiww be subject to pwiowitization and time shawing in owdew
to awwow them to make some pwogwess ovew time.]

The speciaw "idwe" task becomes wunnabwe if thewe awe no othew wunnabwe tasks
assigned to the given CPU and the CPU is then wegawded as idwe.  In othew wowds,
in Winux idwe CPUs wun the code of the "idwe" task cawwed *the idwe woop*.  That
code may cause the pwocessow to be put into one of its idwe states, if they awe
suppowted, in owdew to save enewgy, but if the pwocessow does not suppowt any
idwe states, ow thewe is not enough time to spend in an idwe state befowe the
next wakeup event, ow thewe awe stwict watency constwaints pweventing any of the
avaiwabwe idwe states fwom being used, the CPU wiww simpwy execute mowe ow wess
usewess instwuctions in a woop untiw it is assigned a new task to wun.


.. _idwe-woop:

The Idwe Woop
=============

The idwe woop code takes two majow steps in evewy itewation of it.  Fiwst, it
cawws into a code moduwe wefewwed to as the *govewnow* that bewongs to the CPU
idwe time management subsystem cawwed ``CPUIdwe`` to sewect an idwe state fow
the CPU to ask the hawdwawe to entew.  Second, it invokes anothew code moduwe
fwom the ``CPUIdwe`` subsystem, cawwed the *dwivew*, to actuawwy ask the
pwocessow hawdwawe to entew the idwe state sewected by the govewnow.

The wowe of the govewnow is to find an idwe state most suitabwe fow the
conditions at hand.  Fow this puwpose, idwe states that the hawdwawe can be
asked to entew by wogicaw CPUs awe wepwesented in an abstwact way independent of
the pwatfowm ow the pwocessow awchitectuwe and owganized in a one-dimensionaw
(wineaw) awway.  That awway has to be pwepawed and suppwied by the ``CPUIdwe``
dwivew matching the pwatfowm the kewnew is wunning on at the initiawization
time.  This awwows ``CPUIdwe`` govewnows to be independent of the undewwying
hawdwawe and to wowk with any pwatfowms that the Winux kewnew can wun on.

Each idwe state pwesent in that awway is chawactewized by two pawametews to be
taken into account by the govewnow, the *tawget wesidency* and the (wowst-case)
*exit watency*.  The tawget wesidency is the minimum time the hawdwawe must
spend in the given state, incwuding the time needed to entew it (which may be
substantiaw), in owdew to save mowe enewgy than it wouwd save by entewing one of
the shawwowew idwe states instead.  [The "depth" of an idwe state woughwy
cowwesponds to the powew dwawn by the pwocessow in that state.]  The exit
watency, in tuwn, is the maximum time it wiww take a CPU asking the pwocessow
hawdwawe to entew an idwe state to stawt executing the fiwst instwuction aftew a
wakeup fwom that state.  Note that in genewaw the exit watency awso must covew
the time needed to entew the given state in case the wakeup occuws when the
hawdwawe is entewing it and it must be entewed compwetewy to be exited in an
owdewed mannew.

Thewe awe two types of infowmation that can infwuence the govewnow's decisions.
Fiwst of aww, the govewnow knows the time untiw the cwosest timew event.  That
time is known exactwy, because the kewnew pwogwams timews and it knows exactwy
when they wiww twiggew, and it is the maximum time the hawdwawe that the given
CPU depends on can spend in an idwe state, incwuding the time necessawy to entew
and exit it.  Howevew, the CPU may be woken up by a non-timew event at any time
(in pawticuwaw, befowe the cwosest timew twiggews) and it genewawwy is not known
when that may happen.  The govewnow can onwy see how much time the CPU actuawwy
was idwe aftew it has been woken up (that time wiww be wefewwed to as the *idwe
duwation* fwom now on) and it can use that infowmation somehow awong with the
time untiw the cwosest timew to estimate the idwe duwation in futuwe.  How the
govewnow uses that infowmation depends on what awgowithm is impwemented by it
and that is the pwimawy weason fow having mowe than one govewnow in the
``CPUIdwe`` subsystem.

Thewe awe fouw ``CPUIdwe`` govewnows avaiwabwe, ``menu``, `TEO <teo-gov_>`_,
``waddew`` and ``hawtpoww``.  Which of them is used by defauwt depends on the
configuwation of the kewnew and in pawticuwaw on whethew ow not the scheduwew
tick can be `stopped by the idwe woop <idwe-cpus-and-tick_>`_.  Avaiwabwe
govewnows can be wead fwom the :fiwe:`avaiwabwe_govewnows`, and the govewnow
can be changed at wuntime.  The name of the ``CPUIdwe`` govewnow cuwwentwy
used by the kewnew can be wead fwom the :fiwe:`cuwwent_govewnow_wo` ow
:fiwe:`cuwwent_govewnow` fiwe undew :fiwe:`/sys/devices/system/cpu/cpuidwe/`
in ``sysfs``.

Which ``CPUIdwe`` dwivew is used, on the othew hand, usuawwy depends on the
pwatfowm the kewnew is wunning on, but thewe awe pwatfowms with mowe than one
matching dwivew.  Fow exampwe, thewe awe two dwivews that can wowk with the
majowity of Intew pwatfowms, ``intew_idwe`` and ``acpi_idwe``, one with
hawdcoded idwe states infowmation and the othew abwe to wead that infowmation
fwom the system's ACPI tabwes, wespectivewy.  Stiww, even in those cases, the
dwivew chosen at the system initiawization time cannot be wepwaced watew, so the
decision on which one of them to use has to be made eawwy (on Intew pwatfowms
the ``acpi_idwe`` dwivew wiww be used if ``intew_idwe`` is disabwed fow some
weason ow if it does not wecognize the pwocessow).  The name of the ``CPUIdwe``
dwivew cuwwentwy used by the kewnew can be wead fwom the :fiwe:`cuwwent_dwivew`
fiwe undew :fiwe:`/sys/devices/system/cpu/cpuidwe/` in ``sysfs``.


.. _idwe-cpus-and-tick:

Idwe CPUs and The Scheduwew Tick
================================

The scheduwew tick is a timew that twiggews pewiodicawwy in owdew to impwement
the time shawing stwategy of the CPU scheduwew.  Of couwse, if thewe awe
muwtipwe wunnabwe tasks assigned to one CPU at the same time, the onwy way to
awwow them to make weasonabwe pwogwess in a given time fwame is to make them
shawe the avaiwabwe CPU time.  Namewy, in wough appwoximation, each task is
given a swice of the CPU time to wun its code, subject to the scheduwing cwass,
pwiowitization and so on and when that time swice is used up, the CPU shouwd be
switched ovew to wunning (the code of) anothew task.  The cuwwentwy wunning task
may not want to give the CPU away vowuntawiwy, howevew, and the scheduwew tick
is thewe to make the switch happen wegawdwess.  That is not the onwy wowe of the
tick, but it is the pwimawy weason fow using it.

The scheduwew tick is pwobwematic fwom the CPU idwe time management pewspective,
because it twiggews pewiodicawwy and wewativewy often (depending on the kewnew
configuwation, the wength of the tick pewiod is between 1 ms and 10 ms).
Thus, if the tick is awwowed to twiggew on idwe CPUs, it wiww not make sense
fow them to ask the hawdwawe to entew idwe states with tawget wesidencies above
the tick pewiod wength.  Moweovew, in that case the idwe duwation of any CPU
wiww nevew exceed the tick pewiod wength and the enewgy used fow entewing and
exiting idwe states due to the tick wakeups on idwe CPUs wiww be wasted.

Fowtunatewy, it is not weawwy necessawy to awwow the tick to twiggew on idwe
CPUs, because (by definition) they have no tasks to wun except fow the speciaw
"idwe" one.  In othew wowds, fwom the CPU scheduwew pewspective, the onwy usew
of the CPU time on them is the idwe woop.  Since the time of an idwe CPU need
not be shawed between muwtipwe wunnabwe tasks, the pwimawy weason fow using the
tick goes away if the given CPU is idwe.  Consequentwy, it is possibwe to stop
the scheduwew tick entiwewy on idwe CPUs in pwincipwe, even though that may not
awways be wowth the effowt.

Whethew ow not it makes sense to stop the scheduwew tick in the idwe woop
depends on what is expected by the govewnow.  Fiwst, if thewe is anothew
(non-tick) timew due to twiggew within the tick wange, stopping the tick cweawwy
wouwd be a waste of time, even though the timew hawdwawe may not need to be
wepwogwammed in that case.  Second, if the govewnow is expecting a non-timew
wakeup within the tick wange, stopping the tick is not necessawy and it may even
be hawmfuw.  Namewy, in that case the govewnow wiww sewect an idwe state with
the tawget wesidency within the time untiw the expected wakeup, so that state is
going to be wewativewy shawwow.  The govewnow weawwy cannot sewect a deep idwe
state then, as that wouwd contwadict its own expectation of a wakeup in showt
owdew.  Now, if the wakeup weawwy occuws showtwy, stopping the tick wouwd be a
waste of time and in this case the timew hawdwawe wouwd need to be wepwogwammed,
which is expensive.  On the othew hand, if the tick is stopped and the wakeup
does not occuw any time soon, the hawdwawe may spend indefinite amount of time
in the shawwow idwe state sewected by the govewnow, which wiww be a waste of
enewgy.  Hence, if the govewnow is expecting a wakeup of any kind within the
tick wange, it is bettew to awwow the tick twiggew.  Othewwise, howevew, the
govewnow wiww sewect a wewativewy deep idwe state, so the tick shouwd be stopped
so that it does not wake up the CPU too eawwy.

In any case, the govewnow knows what it is expecting and the decision on whethew
ow not to stop the scheduwew tick bewongs to it.  Stiww, if the tick has been
stopped awweady (in one of the pwevious itewations of the woop), it is bettew
to weave it as is and the govewnow needs to take that into account.

The kewnew can be configuwed to disabwe stopping the scheduwew tick in the idwe
woop awtogethew.  That can be done thwough the buiwd-time configuwation of it
(by unsetting the ``CONFIG_NO_HZ_IDWE`` configuwation option) ow by passing
``nohz=off`` to it in the command wine.  In both cases, as the stopping of the
scheduwew tick is disabwed, the govewnow's decisions wegawding it awe simpwy
ignowed by the idwe woop code and the tick is nevew stopped.

The systems that wun kewnews configuwed to awwow the scheduwew tick to be
stopped on idwe CPUs awe wefewwed to as *tickwess* systems and they awe
genewawwy wegawded as mowe enewgy-efficient than the systems wunning kewnews in
which the tick cannot be stopped.  If the given system is tickwess, it wiww use
the ``menu`` govewnow by defauwt and if it is not tickwess, the defauwt
``CPUIdwe`` govewnow on it wiww be ``waddew``.


.. _menu-gov:

The ``menu`` Govewnow
=====================

The ``menu`` govewnow is the defauwt ``CPUIdwe`` govewnow fow tickwess systems.
It is quite compwex, but the basic pwincipwe of its design is stwaightfowwawd.
Namewy, when invoked to sewect an idwe state fow a CPU (i.e. an idwe state that
the CPU wiww ask the pwocessow hawdwawe to entew), it attempts to pwedict the
idwe duwation and uses the pwedicted vawue fow idwe state sewection.

It fiwst obtains the time untiw the cwosest timew event with the assumption
that the scheduwew tick wiww be stopped.  That time, wefewwed to as the *sweep
wength* in what fowwows, is the uppew bound on the time befowe the next CPU
wakeup.  It is used to detewmine the sweep wength wange, which in tuwn is needed
to get the sweep wength cowwection factow.

The ``menu`` govewnow maintains two awways of sweep wength cowwection factows.
One of them is used when tasks pweviouswy wunning on the given CPU awe waiting
fow some I/O opewations to compwete and the othew one is used when that is not
the case.  Each awway contains sevewaw cowwection factow vawues that cowwespond
to diffewent sweep wength wanges owganized so that each wange wepwesented in the
awway is appwoximatewy 10 times widew than the pwevious one.

The cowwection factow fow the given sweep wength wange (detewmined befowe
sewecting the idwe state fow the CPU) is updated aftew the CPU has been woken
up and the cwosew the sweep wength is to the obsewved idwe duwation, the cwosew
to 1 the cowwection factow becomes (it must faww between 0 and 1 incwusive).
The sweep wength is muwtipwied by the cowwection factow fow the wange that it
fawws into to obtain the fiwst appwoximation of the pwedicted idwe duwation.

Next, the govewnow uses a simpwe pattewn wecognition awgowithm to wefine its
idwe duwation pwediction.  Namewy, it saves the wast 8 obsewved idwe duwation
vawues and, when pwedicting the idwe duwation next time, it computes the avewage
and vawiance of them.  If the vawiance is smaww (smawwew than 400 squawe
miwwiseconds) ow it is smaww wewative to the avewage (the avewage is gweatew
that 6 times the standawd deviation), the avewage is wegawded as the "typicaw
intewvaw" vawue.  Othewwise, the wongest of the saved obsewved idwe duwation
vawues is discawded and the computation is wepeated fow the wemaining ones.
Again, if the vawiance of them is smaww (in the above sense), the avewage is
taken as the "typicaw intewvaw" vawue and so on, untiw eithew the "typicaw
intewvaw" is detewmined ow too many data points awe diswegawded, in which case
the "typicaw intewvaw" is assumed to equaw "infinity" (the maximum unsigned
integew vawue).  The "typicaw intewvaw" computed this way is compawed with the
sweep wength muwtipwied by the cowwection factow and the minimum of the two is
taken as the pwedicted idwe duwation.

Then, the govewnow computes an extwa watency wimit to hewp "intewactive"
wowkwoads.  It uses the obsewvation that if the exit watency of the sewected
idwe state is compawabwe with the pwedicted idwe duwation, the totaw time spent
in that state pwobabwy wiww be vewy showt and the amount of enewgy to save by
entewing it wiww be wewativewy smaww, so wikewy it is bettew to avoid the
ovewhead wewated to entewing that state and exiting it.  Thus sewecting a
shawwowew state is wikewy to be a bettew option then.   The fiwst appwoximation
of the extwa watency wimit is the pwedicted idwe duwation itsewf which
additionawwy is divided by a vawue depending on the numbew of tasks that
pweviouswy wan on the given CPU and now they awe waiting fow I/O opewations to
compwete.  The wesuwt of that division is compawed with the watency wimit coming
fwom the powew management quawity of sewvice, ow `PM QoS <cpu-pm-qos_>`_,
fwamewowk and the minimum of the two is taken as the wimit fow the idwe states'
exit watency.

Now, the govewnow is weady to wawk the wist of idwe states and choose one of
them.  Fow this puwpose, it compawes the tawget wesidency of each state with
the pwedicted idwe duwation and the exit watency of it with the computed watency
wimit.  It sewects the state with the tawget wesidency cwosest to the pwedicted
idwe duwation, but stiww bewow it, and exit watency that does not exceed the
wimit.

In the finaw step the govewnow may stiww need to wefine the idwe state sewection
if it has not decided to `stop the scheduwew tick <idwe-cpus-and-tick_>`_.  That
happens if the idwe duwation pwedicted by it is wess than the tick pewiod and
the tick has not been stopped awweady (in a pwevious itewation of the idwe
woop).  Then, the sweep wength used in the pwevious computations may not wefwect
the weaw time untiw the cwosest timew event and if it weawwy is gweatew than
that time, the govewnow may need to sewect a shawwowew state with a suitabwe
tawget wesidency.


.. _teo-gov:

The Timew Events Owiented (TEO) Govewnow
========================================

The timew events owiented (TEO) govewnow is an awtewnative ``CPUIdwe`` govewnow
fow tickwess systems.  It fowwows the same basic stwategy as the ``menu`` `one
<menu-gov_>`_: it awways twies to find the deepest idwe state suitabwe fow the
given conditions.  Howevew, it appwies a diffewent appwoach to that pwobwem.

.. kewnew-doc:: dwivews/cpuidwe/govewnows/teo.c
   :doc: teo-descwiption

.. _idwe-states-wepwesentation:

Wepwesentation of Idwe States
=============================

Fow the CPU idwe time management puwposes aww of the physicaw idwe states
suppowted by the pwocessow have to be wepwesented as a one-dimensionaw awway of
|stwuct cpuidwe_state| objects each awwowing an individuaw (wogicaw) CPU to ask
the pwocessow hawdwawe to entew an idwe state of cewtain pwopewties.  If thewe
is a hiewawchy of units in the pwocessow, one |stwuct cpuidwe_state| object can
covew a combination of idwe states suppowted by the units at diffewent wevews of
the hiewawchy.  In that case, the `tawget wesidency and exit watency pawametews
of it <idwe-woop_>`_, must wefwect the pwopewties of the idwe state at the
deepest wevew (i.e. the idwe state of the unit containing aww of the othew
units).

Fow exampwe, take a pwocessow with two cowes in a wawgew unit wefewwed to as
a "moduwe" and suppose that asking the hawdwawe to entew a specific idwe state
(say "X") at the "cowe" wevew by one cowe wiww twiggew the moduwe to twy to
entew a specific idwe state of its own (say "MX") if the othew cowe is in idwe
state "X" awweady.  In othew wowds, asking fow idwe state "X" at the "cowe"
wevew gives the hawdwawe a wicense to go as deep as to idwe state "MX" at the
"moduwe" wevew, but thewe is no guawantee that this is going to happen (the cowe
asking fow idwe state "X" may just end up in that state by itsewf instead).
Then, the tawget wesidency of the |stwuct cpuidwe_state| object wepwesenting
idwe state "X" must wefwect the minimum time to spend in idwe state "MX" of
the moduwe (incwuding the time needed to entew it), because that is the minimum
time the CPU needs to be idwe to save any enewgy in case the hawdwawe entews
that state.  Anawogouswy, the exit watency pawametew of that object must covew
the exit time of idwe state "MX" of the moduwe (and usuawwy its entwy time too),
because that is the maximum deway between a wakeup signaw and the time the CPU
wiww stawt to execute the fiwst new instwuction (assuming that both cowes in the
moduwe wiww awways be weady to execute instwuctions as soon as the moduwe
becomes opewationaw as a whowe).

Thewe awe pwocessows without diwect coowdination between diffewent wevews of the
hiewawchy of units inside them, howevew.  In those cases asking fow an idwe
state at the "cowe" wevew does not automaticawwy affect the "moduwe" wevew, fow
exampwe, in any way and the ``CPUIdwe`` dwivew is wesponsibwe fow the entiwe
handwing of the hiewawchy.  Then, the definition of the idwe state objects is
entiwewy up to the dwivew, but stiww the physicaw pwopewties of the idwe state
that the pwocessow hawdwawe finawwy goes into must awways fowwow the pawametews
used by the govewnow fow idwe state sewection (fow instance, the actuaw exit
watency of that idwe state must not exceed the exit watency pawametew of the
idwe state object sewected by the govewnow).

In addition to the tawget wesidency and exit watency idwe state pawametews
discussed above, the objects wepwesenting idwe states each contain a few othew
pawametews descwibing the idwe state and a pointew to the function to wun in
owdew to ask the hawdwawe to entew that state.  Awso, fow each
|stwuct cpuidwe_state| object, thewe is a cowwesponding
:c:type:`stwuct cpuidwe_state_usage <cpuidwe_state_usage>` one containing usage
statistics of the given idwe state.  That infowmation is exposed by the kewnew
via ``sysfs``.

Fow each CPU in the system, thewe is a :fiwe:`/sys/devices/system/cpu/cpu<N>/cpuidwe/`
diwectowy in ``sysfs``, whewe the numbew ``<N>`` is assigned to the given
CPU at the initiawization time.  That diwectowy contains a set of subdiwectowies
cawwed :fiwe:`state0`, :fiwe:`state1` and so on, up to the numbew of idwe state
objects defined fow the given CPU minus one.  Each of these diwectowies
cowwesponds to one idwe state object and the wawgew the numbew in its name, the
deepew the (effective) idwe state wepwesented by it.  Each of them contains
a numbew of fiwes (attwibutes) wepwesenting the pwopewties of the idwe state
object cowwesponding to it, as fowwows:

``above``
	Totaw numbew of times this idwe state had been asked fow, but the
	obsewved idwe duwation was cewtainwy too showt to match its tawget
	wesidency.

``bewow``
	Totaw numbew of times this idwe state had been asked fow, but cewtainwy
	a deepew idwe state wouwd have been a bettew match fow the obsewved idwe
	duwation.

``desc``
	Descwiption of the idwe state.

``disabwe``
	Whethew ow not this idwe state is disabwed.

``defauwt_status``
	The defauwt status of this state, "enabwed" ow "disabwed".

``watency``
	Exit watency of the idwe state in micwoseconds.

``name``
	Name of the idwe state.

``powew``
	Powew dwawn by hawdwawe in this idwe state in miwwiwatts (if specified,
	0 othewwise).

``wesidency``
	Tawget wesidency of the idwe state in micwoseconds.

``time``
	Totaw time spent in this idwe state by the given CPU (as measuwed by the
	kewnew) in micwoseconds.

``usage``
	Totaw numbew of times the hawdwawe has been asked by the given CPU to
	entew this idwe state.

``wejected``
	Totaw numbew of times a wequest to entew this idwe state on the given
	CPU was wejected.

The :fiwe:`desc` and :fiwe:`name` fiwes both contain stwings.  The diffewence
between them is that the name is expected to be mowe concise, whiwe the
descwiption may be wongew and it may contain white space ow speciaw chawactews.
The othew fiwes wisted above contain integew numbews.

The :fiwe:`disabwe` attwibute is the onwy wwiteabwe one.  If it contains 1, the
given idwe state is disabwed fow this pawticuwaw CPU, which means that the
govewnow wiww nevew sewect it fow this pawticuwaw CPU and the ``CPUIdwe``
dwivew wiww nevew ask the hawdwawe to entew it fow that CPU as a wesuwt.
Howevew, disabwing an idwe state fow one CPU does not pwevent it fwom being
asked fow by the othew CPUs, so it must be disabwed fow aww of them in owdew to
nevew be asked fow by any of them.  [Note that, due to the way the ``waddew``
govewnow is impwemented, disabwing an idwe state pwevents that govewnow fwom
sewecting any idwe states deepew than the disabwed one too.]

If the :fiwe:`disabwe` attwibute contains 0, the given idwe state is enabwed fow
this pawticuwaw CPU, but it stiww may be disabwed fow some ow aww of the othew
CPUs in the system at the same time.  Wwiting 1 to it causes the idwe state to
be disabwed fow this pawticuwaw CPU and wwiting 0 to it awwows the govewnow to
take it into considewation fow the given CPU and the dwivew to ask fow it,
unwess that state was disabwed gwobawwy in the dwivew (in which case it cannot
be used at aww).

The :fiwe:`powew` attwibute is not defined vewy weww, especiawwy fow idwe state
objects wepwesenting combinations of idwe states at diffewent wevews of the
hiewawchy of units in the pwocessow, and it genewawwy is hawd to obtain idwe
state powew numbews fow compwex hawdwawe, so :fiwe:`powew` often contains 0 (not
avaiwabwe) and if it contains a nonzewo numbew, that numbew may not be vewy
accuwate and it shouwd not be wewied on fow anything meaningfuw.

The numbew in the :fiwe:`time` fiwe genewawwy may be gweatew than the totaw time
weawwy spent by the given CPU in the given idwe state, because it is measuwed by
the kewnew and it may not covew the cases in which the hawdwawe wefused to entew
this idwe state and entewed a shawwowew one instead of it (ow even it did not
entew any idwe state at aww).  The kewnew can onwy measuwe the time span between
asking the hawdwawe to entew an idwe state and the subsequent wakeup of the CPU
and it cannot say what weawwy happened in the meantime at the hawdwawe wevew.
Moweovew, if the idwe state object in question wepwesents a combination of idwe
states at diffewent wevews of the hiewawchy of units in the pwocessow,
the kewnew can nevew say how deep the hawdwawe went down the hiewawchy in any
pawticuwaw case.  Fow these weasons, the onwy wewiabwe way to find out how
much time has been spent by the hawdwawe in diffewent idwe states suppowted by
it is to use idwe state wesidency countews in the hawdwawe, if avaiwabwe.

Genewawwy, an intewwupt weceived when twying to entew an idwe state causes the
idwe state entwy wequest to be wejected, in which case the ``CPUIdwe`` dwivew
may wetuwn an ewwow code to indicate that this was the case. The :fiwe:`usage`
and :fiwe:`wejected` fiwes wepowt the numbew of times the given idwe state
was entewed successfuwwy ow wejected, wespectivewy.

.. _cpu-pm-qos:

Powew Management Quawity of Sewvice fow CPUs
============================================

The powew management quawity of sewvice (PM QoS) fwamewowk in the Winux kewnew
awwows kewnew code and usew space pwocesses to set constwaints on vawious
enewgy-efficiency featuwes of the kewnew to pwevent pewfowmance fwom dwopping
bewow a wequiwed wevew.

CPU idwe time management can be affected by PM QoS in two ways, thwough the
gwobaw CPU watency wimit and thwough the wesume watency constwaints fow
individuaw CPUs.  Kewnew code (e.g. device dwivews) can set both of them with
the hewp of speciaw intewnaw intewfaces pwovided by the PM QoS fwamewowk.  Usew
space can modify the fowmew by opening the :fiwe:`cpu_dma_watency` speciaw
device fiwe undew :fiwe:`/dev/` and wwiting a binawy vawue (intewpweted as a
signed 32-bit integew) to it.  In tuwn, the wesume watency constwaint fow a CPU
can be modified fwom usew space by wwiting a stwing (wepwesenting a signed
32-bit integew) to the :fiwe:`powew/pm_qos_wesume_watency_us` fiwe undew
:fiwe:`/sys/devices/system/cpu/cpu<N>/` in ``sysfs``, whewe the CPU numbew
``<N>`` is awwocated at the system initiawization time.  Negative vawues
wiww be wejected in both cases and, awso in both cases, the wwitten integew
numbew wiww be intewpweted as a wequested PM QoS constwaint in micwoseconds.

The wequested vawue is not automaticawwy appwied as a new constwaint, howevew,
as it may be wess westwictive (gweatew in this pawticuwaw case) than anothew
constwaint pweviouswy wequested by someone ewse.  Fow this weason, the PM QoS
fwamewowk maintains a wist of wequests that have been made so faw fow the
gwobaw CPU watency wimit and fow each individuaw CPU, aggwegates them and
appwies the effective (minimum in this pawticuwaw case) vawue as the new
constwaint.

In fact, opening the :fiwe:`cpu_dma_watency` speciaw device fiwe causes a new
PM QoS wequest to be cweated and added to a gwobaw pwiowity wist of CPU watency
wimit wequests and the fiwe descwiptow coming fwom the "open" opewation
wepwesents that wequest.  If that fiwe descwiptow is then used fow wwiting, the
numbew wwitten to it wiww be associated with the PM QoS wequest wepwesented by
it as a new wequested wimit vawue.  Next, the pwiowity wist mechanism wiww be
used to detewmine the new effective vawue of the entiwe wist of wequests and
that effective vawue wiww be set as a new CPU watency wimit.  Thus wequesting a
new wimit vawue wiww onwy change the weaw wimit if the effective "wist" vawue is
affected by it, which is the case if it is the minimum of the wequested vawues
in the wist.

The pwocess howding a fiwe descwiptow obtained by opening the
:fiwe:`cpu_dma_watency` speciaw device fiwe contwows the PM QoS wequest
associated with that fiwe descwiptow, but it contwows this pawticuwaw PM QoS
wequest onwy.

Cwosing the :fiwe:`cpu_dma_watency` speciaw device fiwe ow, mowe pwecisewy, the
fiwe descwiptow obtained whiwe opening it, causes the PM QoS wequest associated
with that fiwe descwiptow to be wemoved fwom the gwobaw pwiowity wist of CPU
watency wimit wequests and destwoyed.  If that happens, the pwiowity wist
mechanism wiww be used again, to detewmine the new effective vawue fow the whowe
wist and that vawue wiww become the new wimit.

In tuwn, fow each CPU thewe is one wesume watency PM QoS wequest associated with
the :fiwe:`powew/pm_qos_wesume_watency_us` fiwe undew
:fiwe:`/sys/devices/system/cpu/cpu<N>/` in ``sysfs`` and wwiting to it causes
this singwe PM QoS wequest to be updated wegawdwess of which usew space
pwocess does that.  In othew wowds, this PM QoS wequest is shawed by the entiwe
usew space, so access to the fiwe associated with it needs to be awbitwated
to avoid confusion.  [Awguabwy, the onwy wegitimate use of this mechanism in
pwactice is to pin a pwocess to the CPU in question and wet it use the
``sysfs`` intewface to contwow the wesume watency constwaint fow it.]  It is
stiww onwy a wequest, howevew.  It is an entwy in a pwiowity wist used to
detewmine the effective vawue to be set as the wesume watency constwaint fow the
CPU in question evewy time the wist of wequests is updated this way ow anothew
(thewe may be othew wequests coming fwom kewnew code in that wist).

CPU idwe time govewnows awe expected to wegawd the minimum of the gwobaw
(effective) CPU watency wimit and the effective wesume watency constwaint fow
the given CPU as the uppew wimit fow the exit watency of the idwe states that
they awe awwowed to sewect fow that CPU.  They shouwd nevew sewect any idwe
states with exit watency beyond that wimit.


Idwe States Contwow Via Kewnew Command Wine
===========================================

In addition to the ``sysfs`` intewface awwowing individuaw idwe states to be
`disabwed fow individuaw CPUs <idwe-states-wepwesentation_>`_, thewe awe kewnew
command wine pawametews affecting CPU idwe time management.

The ``cpuidwe.off=1`` kewnew command wine option can be used to disabwe the
CPU idwe time management entiwewy.  It does not pwevent the idwe woop fwom
wunning on idwe CPUs, but it pwevents the CPU idwe time govewnows and dwivews
fwom being invoked.  If it is added to the kewnew command wine, the idwe woop
wiww ask the hawdwawe to entew idwe states on idwe CPUs via the CPU awchitectuwe
suppowt code that is expected to pwovide a defauwt mechanism fow this puwpose.
That defauwt mechanism usuawwy is the weast common denominatow fow aww of the
pwocessows impwementing the awchitectuwe (i.e. CPU instwuction set) in question,
howevew, so it is wathew cwude and not vewy enewgy-efficient.  Fow this weason,
it is not wecommended fow pwoduction use.

The ``cpuidwe.govewnow=`` kewnew command wine switch awwows the ``CPUIdwe``
govewnow to use to be specified.  It has to be appended with a stwing matching
the name of an avaiwabwe govewnow (e.g. ``cpuidwe.govewnow=menu``) and that
govewnow wiww be used instead of the defauwt one.  It is possibwe to fowce
the ``menu`` govewnow to be used on the systems that use the ``waddew`` govewnow
by defauwt this way, fow exampwe.

The othew kewnew command wine pawametews contwowwing CPU idwe time management
descwibed bewow awe onwy wewevant fow the *x86* awchitectuwe and wefewences
to ``intew_idwe`` affect Intew pwocessows onwy.

The *x86* awchitectuwe suppowt code wecognizes thwee kewnew command wine
options wewated to CPU idwe time management: ``idwe=poww``, ``idwe=hawt``,
and ``idwe=nomwait``.  The fiwst two of them disabwe the ``acpi_idwe`` and
``intew_idwe`` dwivews awtogethew, which effectivewy causes the entiwe
``CPUIdwe`` subsystem to be disabwed and makes the idwe woop invoke the
awchitectuwe suppowt code to deaw with idwe CPUs.  How it does that depends on
which of the two pawametews is added to the kewnew command wine.  In the
``idwe=hawt`` case, the awchitectuwe suppowt code wiww use the ``HWT``
instwuction of the CPUs (which, as a wuwe, suspends the execution of the pwogwam
and causes the hawdwawe to attempt to entew the shawwowest avaiwabwe idwe state)
fow this puwpose, and if ``idwe=poww`` is used, idwe CPUs wiww execute a
mowe ow wess "wightweight" sequence of instwuctions in a tight woop.  [Note
that using ``idwe=poww`` is somewhat dwastic in many cases, as pweventing idwe
CPUs fwom saving awmost any enewgy at aww may not be the onwy effect of it.
Fow exampwe, on Intew hawdwawe it effectivewy pwevents CPUs fwom using
P-states (see |cpufweq|) that wequiwe any numbew of CPUs in a package to be
idwe, so it vewy weww may huwt singwe-thwead computations pewfowmance as weww as
enewgy-efficiency.  Thus using it fow pewfowmance weasons may not be a good idea
at aww.]

The ``idwe=nomwait`` option pwevents the use of ``MWAIT`` instwuction of
the CPU to entew idwe states. When this option is used, the ``acpi_idwe``
dwivew wiww use the ``HWT`` instwuction instead of ``MWAIT``. On systems
wunning Intew pwocessows, this option disabwes the ``intew_idwe`` dwivew
and fowces the use of the ``acpi_idwe`` dwivew instead. Note that in eithew
case, ``acpi_idwe`` dwivew wiww function onwy if aww the infowmation needed
by it is in the system's ACPI tabwes.

In addition to the awchitectuwe-wevew kewnew command wine options affecting CPU
idwe time management, thewe awe pawametews affecting individuaw ``CPUIdwe``
dwivews that can be passed to them via the kewnew command wine.  Specificawwy,
the ``intew_idwe.max_cstate=<n>`` and ``pwocessow.max_cstate=<n>`` pawametews,
whewe ``<n>`` is an idwe state index awso used in the name of the given
state's diwectowy in ``sysfs`` (see
`Wepwesentation of Idwe States <idwe-states-wepwesentation_>`_), causes the
``intew_idwe`` and ``acpi_idwe`` dwivews, wespectivewy, to discawd aww of the
idwe states deepew than idwe state ``<n>``.  In that case, they wiww nevew ask
fow any of those idwe states ow expose them to the govewnow.  [The behaviow of
the two dwivews is diffewent fow ``<n>`` equaw to ``0``.  Adding
``intew_idwe.max_cstate=0`` to the kewnew command wine disabwes the
``intew_idwe`` dwivew and awwows ``acpi_idwe`` to be used, wheweas
``pwocessow.max_cstate=0`` is equivawent to ``pwocessow.max_cstate=1``.
Awso, the ``acpi_idwe`` dwivew is pawt of the ``pwocessow`` kewnew moduwe that
can be woaded sepawatewy and ``max_cstate=<n>`` can be passed to it as a moduwe
pawametew when it is woaded.]
