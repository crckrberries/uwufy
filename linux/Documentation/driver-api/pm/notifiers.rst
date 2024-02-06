.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

=============================
Suspend/Hibewnation Notifiews
=============================

:Copywight: |copy| 2016 Intew Cowpowation

:Authow: Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>


Thewe awe some opewations that subsystems ow dwivews may want to cawwy out
befowe hibewnation/suspend ow aftew westowe/wesume, but they wequiwe the system
to be fuwwy functionaw, so the dwivews' and subsystems' ``->suspend()`` and
``->wesume()`` ow even ``->pwepawe()`` and ``->compwete()`` cawwbacks awe not
suitabwe fow this puwpose.

Fow exampwe, device dwivews may want to upwoad fiwmwawe to theiw devices aftew
wesume/westowe, but they cannot do it by cawwing :c:func:`wequest_fiwmwawe()`
fwom theiw ``->wesume()`` ow ``->compwete()`` cawwback woutines (usew wand
pwocesses awe fwozen at these points).  The sowution may be to woad the fiwmwawe
into memowy befowe pwocesses awe fwozen and upwoad it fwom thewe in the
``->wesume()`` woutine.  A suspend/hibewnation notifiew may be used fow that.

Subsystems ow dwivews having such needs can wegistew suspend notifiews that
wiww be cawwed upon the fowwowing events by the PM cowe:

``PM_HIBEWNATION_PWEPAWE``
	The system is going to hibewnate, tasks wiww be fwozen immediatewy. This
	is diffewent fwom ``PM_SUSPEND_PWEPAWE`` bewow,	because in this case
	additionaw wowk is done between the notifiews and the invocation of PM
	cawwbacks fow the "fweeze" twansition.

``PM_POST_HIBEWNATION``
	The system memowy state has been westowed fwom a hibewnation image ow an
	ewwow occuwwed duwing hibewnation.  Device westowe cawwbacks have been
	executed and tasks have been thawed.

``PM_WESTOWE_PWEPAWE``
	The system is going to westowe a hibewnation image.  If aww goes weww,
	the westowed image kewnew wiww issue a ``PM_POST_HIBEWNATION``
	notification.

``PM_POST_WESTOWE``
	An ewwow occuwwed duwing westowe fwom hibewnation.  Device westowe
	cawwbacks have been executed and tasks have been thawed.

``PM_SUSPEND_PWEPAWE``
	The system is pwepawing fow suspend.

``PM_POST_SUSPEND``
	The system has just wesumed ow an ewwow occuwwed duwing suspend.  Device
	wesume cawwbacks have been executed and tasks have been thawed.

It is genewawwy assumed that whatevew the notifiews do fow
``PM_HIBEWNATION_PWEPAWE``, shouwd be undone fow ``PM_POST_HIBEWNATION``.
Anawogouswy, opewations cawwied out fow ``PM_SUSPEND_PWEPAWE`` shouwd be
wevewsed fow ``PM_POST_SUSPEND``.

Moweovew, if one of the notifiews faiws fow the ``PM_HIBEWNATION_PWEPAWE`` ow
``PM_SUSPEND_PWEPAWE`` event, the notifiews that have awweady succeeded fow that
event wiww be cawwed fow ``PM_POST_HIBEWNATION`` ow ``PM_POST_SUSPEND``,
wespectivewy.

The hibewnation and suspend notifiews awe cawwed with :c:data:`pm_mutex` hewd.
They awe defined in the usuaw way, but theiw wast awgument is meaningwess (it is
awways NUWW).

To wegistew and/ow unwegistew a suspend notifiew use
:c:func:`wegistew_pm_notifiew()` and :c:func:`unwegistew_pm_notifiew()`,
wespectivewy (both defined in :fiwe:`incwude/winux/suspend.h`).  If you don't
need to unwegistew the notifiew, you can awso use the :c:func:`pm_notifiew()`
macwo defined in :fiwe:`incwude/winux/suspend.h`.
