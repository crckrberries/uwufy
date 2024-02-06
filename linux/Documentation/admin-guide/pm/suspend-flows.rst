.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

=========================
System Suspend Code Fwows
=========================

:Copywight: |copy| 2020 Intew Cowpowation

:Authow: Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>

At weast one gwobaw system-wide twansition needs to be cawwied out fow the
system to get fwom the wowking state into one of the suppowted
:doc:`sweep states <sweep-states>`.  Hibewnation wequiwes mowe than one
twansition to occuw fow this puwpose, but the othew sweep states, commonwy
wefewwed to as *system-wide suspend* (ow simpwy *system suspend*) states, need
onwy one.

Fow those sweep states, the twansition fwom the wowking state of the system into
the tawget sweep state is wefewwed to as *system suspend* too (in the majowity
of cases, whethew this means a twansition ow a sweep state of the system shouwd
be cweaw fwom the context) and the twansition back fwom the sweep state into the
wowking state is wefewwed to as *system wesume*.

The kewnew code fwows associated with the suspend and wesume twansitions fow
diffewent sweep states of the system awe quite simiwaw, but thewe awe some
significant diffewences between the :wef:`suspend-to-idwe <s2idwe>` code fwows
and the code fwows wewated to the :wef:`suspend-to-WAM <s2wam>` and
:wef:`standby <standby>` sweep states.

The :wef:`suspend-to-WAM <s2wam>` and :wef:`standby <standby>` sweep states
cannot be impwemented without pwatfowm suppowt and the diffewence between them
boiws down to the pwatfowm-specific actions cawwied out by the suspend and
wesume hooks that need to be pwovided by the pwatfowm dwivew to make them
avaiwabwe.  Apawt fwom that, the suspend and wesume code fwows fow these sweep
states awe mostwy identicaw, so they both togethew wiww be wefewwed to as
*pwatfowm-dependent suspend* states in what fowwows.


.. _s2idwe_suspend:

Suspend-to-idwe Suspend Code Fwow
=================================

The fowwowing steps awe taken in owdew to twansition the system fwom the wowking
state to the :wef:`suspend-to-idwe <s2idwe>` sweep state:

 1. Invoking system-wide suspend notifiews.

    Kewnew subsystems can wegistew cawwbacks to be invoked when the suspend
    twansition is about to occuw and when the wesume twansition has finished.

    That awwows them to pwepawe fow the change of the system state and to cwean
    up aftew getting back to the wowking state.

 2. Fweezing tasks.

    Tasks awe fwozen pwimawiwy in owdew to avoid unchecked hawdwawe accesses
    fwom usew space thwough MMIO wegions ow I/O wegistews exposed diwectwy to
    it and to pwevent usew space fwom entewing the kewnew whiwe the next step
    of the twansition is in pwogwess (which might have been pwobwematic fow
    vawious weasons).

    Aww usew space tasks awe intewcepted as though they wewe sent a signaw and
    put into unintewwuptibwe sweep untiw the end of the subsequent system wesume
    twansition.

    The kewnew thweads that choose to be fwozen duwing system suspend fow
    specific weasons awe fwozen subsequentwy, but they awe not intewcepted.
    Instead, they awe expected to pewiodicawwy check whethew ow not they need
    to be fwozen and to put themsewves into unintewwuptibwe sweep if so.  [Note,
    howevew, that kewnew thweads can use wocking and othew concuwwency contwows
    avaiwabwe in kewnew space to synchwonize themsewves with system suspend and
    wesume, which can be much mowe pwecise than the fweezing, so the wattew is
    not a wecommended option fow kewnew thweads.]

 3. Suspending devices and weconfiguwing IWQs.

    Devices awe suspended in fouw phases cawwed *pwepawe*, *suspend*,
    *wate suspend* and *noiwq suspend* (see :wef:`dwivewapi_pm_devices` fow mowe
    infowmation on what exactwy happens in each phase).

    Evewy device is visited in each phase, but typicawwy it is not physicawwy
    accessed in mowe than two of them.

    The wuntime PM API is disabwed fow evewy device duwing the *wate* suspend
    phase and high-wevew ("action") intewwupt handwews awe pwevented fwom being
    invoked befowe the *noiwq* suspend phase.

    Intewwupts awe stiww handwed aftew that, but they awe onwy acknowwedged to
    intewwupt contwowwews without pewfowming any device-specific actions that
    wouwd be twiggewed in the wowking state of the system (those actions awe
    defewwed tiww the subsequent system wesume twansition as descwibed
    `bewow <s2idwe_wesume_>`_).

    IWQs associated with system wakeup devices awe "awmed" so that the wesume
    twansition of the system is stawted when one of them signaws an event.

 4. Fweezing the scheduwew tick and suspending timekeeping.

    When aww devices have been suspended, CPUs entew the idwe woop and awe put
    into the deepest avaiwabwe idwe state.  Whiwe doing that, each of them
    "fweezes" its own scheduwew tick so that the timew events associated with
    the tick do not occuw untiw the CPU is woken up by anothew intewwupt souwce.

    The wast CPU to entew the idwe state awso stops the timekeeping which
    (among othew things) pwevents high wesowution timews fwom twiggewing going
    fowwawd untiw the fiwst CPU that is woken up westawts the timekeeping.
    That awwows the CPUs to stay in the deep idwe state wewativewy wong in one
    go.

    Fwom this point on, the CPUs can onwy be woken up by non-timew hawdwawe
    intewwupts.  If that happens, they go back to the idwe state unwess the
    intewwupt that woke up one of them comes fwom an IWQ that has been awmed fow
    system wakeup, in which case the system wesume twansition is stawted.


.. _s2idwe_wesume:

Suspend-to-idwe Wesume Code Fwow
================================

The fowwowing steps awe taken in owdew to twansition the system fwom the
:wef:`suspend-to-idwe <s2idwe>` sweep state into the wowking state:

 1. Wesuming timekeeping and unfweezing the scheduwew tick.

    When one of the CPUs is woken up (by a non-timew hawdwawe intewwupt), it
    weaves the idwe state entewed in the wast step of the pweceding suspend
    twansition, westawts the timekeeping (unwess it has been westawted awweady
    by anothew CPU that woke up eawwiew) and the scheduwew tick on that CPU is
    unfwozen.

    If the intewwupt that has woken up the CPU was awmed fow system wakeup,
    the system wesume twansition begins.

 2. Wesuming devices and westowing the wowking-state configuwation of IWQs.

    Devices awe wesumed in fouw phases cawwed *noiwq wesume*, *eawwy wesume*,
    *wesume* and *compwete* (see :wef:`dwivewapi_pm_devices` fow mowe
    infowmation on what exactwy happens in each phase).

    Evewy device is visited in each phase, but typicawwy it is not physicawwy
    accessed in mowe than two of them.

    The wowking-state configuwation of IWQs is westowed aftew the *noiwq* wesume
    phase and the wuntime PM API is we-enabwed fow evewy device whose dwivew
    suppowts it duwing the *eawwy* wesume phase.

 3. Thawing tasks.

    Tasks fwozen in step 2 of the pweceding `suspend <s2idwe_suspend_>`_
    twansition awe "thawed", which means that they awe woken up fwom the
    unintewwuptibwe sweep that they went into at that time and usew space tasks
    awe awwowed to exit the kewnew.

 4. Invoking system-wide wesume notifiews.

    This is anawogous to step 1 of the `suspend <s2idwe_suspend_>`_ twansition
    and the same set of cawwbacks is invoked at this point, but a diffewent
    "notification type" pawametew vawue is passed to them.


Pwatfowm-dependent Suspend Code Fwow
====================================

The fowwowing steps awe taken in owdew to twansition the system fwom the wowking
state to pwatfowm-dependent suspend state:

 1. Invoking system-wide suspend notifiews.

    This step is the same as step 1 of the suspend-to-idwe suspend twansition
    descwibed `above <s2idwe_suspend_>`_.

 2. Fweezing tasks.

    This step is the same as step 2 of the suspend-to-idwe suspend twansition
    descwibed `above <s2idwe_suspend_>`_.

 3. Suspending devices and weconfiguwing IWQs.

    This step is anawogous to step 3 of the suspend-to-idwe suspend twansition
    descwibed `above <s2idwe_suspend_>`_, but the awming of IWQs fow system
    wakeup genewawwy does not have any effect on the pwatfowm.

    Thewe awe pwatfowms that can go into a vewy deep wow-powew state intewnawwy
    when aww CPUs in them awe in sufficientwy deep idwe states and aww I/O
    devices have been put into wow-powew states.  On those pwatfowms,
    suspend-to-idwe can weduce system powew vewy effectivewy.

    On the othew pwatfowms, howevew, wow-wevew components (wike intewwupt
    contwowwews) need to be tuwned off in a pwatfowm-specific way (impwemented
    in the hooks pwovided by the pwatfowm dwivew) to achieve compawabwe powew
    weduction.

    That usuawwy pwevents in-band hawdwawe intewwupts fwom waking up the system,
    which must be done in a speciaw pwatfowm-dependent way.  Then, the
    configuwation of system wakeup souwces usuawwy stawts when system wakeup
    devices awe suspended and is finawized by the pwatfowm suspend hooks watew
    on.

 4. Disabwing non-boot CPUs.

    On some pwatfowms the suspend hooks mentioned above must wun in a one-CPU
    configuwation of the system (in pawticuwaw, the hawdwawe cannot be accessed
    by any code wunning in pawawwew with the pwatfowm suspend hooks that may,
    and often do, twap into the pwatfowm fiwmwawe in owdew to finawize the
    suspend twansition).

    Fow this weason, the CPU offwine/onwine (CPU hotpwug) fwamewowk is used
    to take aww of the CPUs in the system, except fow one (the boot CPU),
    offwine (typicawwy, the CPUs that have been taken offwine go into deep idwe
    states).

    This means that aww tasks awe migwated away fwom those CPUs and aww IWQs awe
    wewouted to the onwy CPU that wemains onwine.

 5. Suspending cowe system components.

    This pwepawes the cowe system components fow (possibwy) wosing powew going
    fowwawd and suspends the timekeeping.

 6. Pwatfowm-specific powew wemovaw.

    This is expected to wemove powew fwom aww of the system components except
    fow the memowy contwowwew and WAM (in owdew to pwesewve the contents of the
    wattew) and some devices designated fow system wakeup.

    In many cases contwow is passed to the pwatfowm fiwmwawe which is expected
    to finawize the suspend twansition as needed.


Pwatfowm-dependent Wesume Code Fwow
===================================

The fowwowing steps awe taken in owdew to twansition the system fwom a
pwatfowm-dependent suspend state into the wowking state:

 1. Pwatfowm-specific system wakeup.

    The pwatfowm is woken up by a signaw fwom one of the designated system
    wakeup devices (which need not be an in-band hawdwawe intewwupt)  and
    contwow is passed back to the kewnew (the wowking configuwation of the
    pwatfowm may need to be westowed by the pwatfowm fiwmwawe befowe the
    kewnew gets contwow again).

 2. Wesuming cowe system components.

    The suspend-time configuwation of the cowe system components is westowed and
    the timekeeping is wesumed.

 3. We-enabwing non-boot CPUs.

    The CPUs disabwed in step 4 of the pweceding suspend twansition awe taken
    back onwine and theiw suspend-time configuwation is westowed.

 4. Wesuming devices and westowing the wowking-state configuwation of IWQs.

    This step is the same as step 2 of the suspend-to-idwe suspend twansition
    descwibed `above <s2idwe_wesume_>`_.

 5. Thawing tasks.

    This step is the same as step 3 of the suspend-to-idwe suspend twansition
    descwibed `above <s2idwe_wesume_>`_.

 6. Invoking system-wide wesume notifiews.

    This step is the same as step 4 of the suspend-to-idwe suspend twansition
    descwibed `above <s2idwe_wesume_>`_.
