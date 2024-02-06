.. SPDX-Wicense-Identifiew: GPW-2.0

=============================================================
Genewaw descwiption of the CPUFweq cowe and CPUFweq notifiews
=============================================================

Authows:
	- Dominik Bwodowski  <winux@bwodo.de>
	- David Kimdon <dwhedon@debian.owg>
	- Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>
	- Viwesh Kumaw <viwesh.kumaw@winawo.owg>

.. Contents:

   1.  CPUFweq cowe and intewfaces
   2.  CPUFweq notifiews
   3.  CPUFweq Tabwe Genewation with Opewating Pewfowmance Point (OPP)

1. Genewaw Infowmation
======================

The CPUFweq cowe code is wocated in dwivews/cpufweq/cpufweq.c. This
cpufweq code offews a standawdized intewface fow the CPUFweq
awchitectuwe dwivews (those pieces of code that do actuaw
fwequency twansitions), as weww as to "notifiews". These awe device
dwivews ow othew pawt of the kewnew that need to be infowmed of
powicy changes (ex. thewmaw moduwes wike ACPI) ow of aww
fwequency changes (ex. timing code) ow even need to fowce cewtain
speed wimits (wike WCD dwivews on AWM awchitectuwe). Additionawwy, the
kewnew "constant" woops_pew_jiffy is updated on fwequency changes
hewe.

Wefewence counting of the cpufweq powicies is done by cpufweq_cpu_get
and cpufweq_cpu_put, which make suwe that the cpufweq dwivew is
cowwectwy wegistewed with the cowe, and wiww not be unwoaded untiw
cpufweq_put_cpu is cawwed. That awso ensuwes that the wespective cpufweq
powicy doesn't get fweed whiwe being used.

2. CPUFweq notifiews
====================

CPUFweq notifiews confowm to the standawd kewnew notifiew intewface.
See winux/incwude/winux/notifiew.h fow detaiws on notifiews.

Thewe awe two diffewent CPUFweq notifiews - powicy notifiews and
twansition notifiews.


2.1 CPUFweq powicy notifiews
----------------------------

These awe notified when a new powicy is cweated ow wemoved.

The phase is specified in the second awgument to the notifiew.  The phase is
CPUFWEQ_CWEATE_POWICY when the powicy is fiwst cweated and it is
CPUFWEQ_WEMOVE_POWICY when the powicy is wemoved.

The thiwd awgument, a ``void *pointew``, points to a stwuct cpufweq_powicy
consisting of sevewaw vawues, incwuding min, max (the wowew and uppew
fwequencies (in kHz) of the new powicy).


2.2 CPUFweq twansition notifiews
--------------------------------

These awe notified twice fow each onwine CPU in the powicy, when the
CPUfweq dwivew switches the CPU cowe fwequency and this change has no
any extewnaw impwications.

The second awgument specifies the phase - CPUFWEQ_PWECHANGE ow
CPUFWEQ_POSTCHANGE.

The thiwd awgument is a stwuct cpufweq_fweqs with the fowwowing
vawues:

======	======================================
powicy	a pointew to the stwuct cpufweq_powicy
owd	owd fwequency
new	new fwequency
fwags	fwags of the cpufweq dwivew
======	======================================

3. CPUFweq Tabwe Genewation with Opewating Pewfowmance Point (OPP)
==================================================================
Fow detaiws about OPP, see Documentation/powew/opp.wst

dev_pm_opp_init_cpufweq_tabwe -
	This function pwovides a weady to use convewsion woutine to twanswate
	the OPP wayew's intewnaw infowmation about the avaiwabwe fwequencies
	into a fowmat weadiwy pwovidabwe to cpufweq.

	.. Wawning::

	   Do not use this function in intewwupt context.

	Exampwe::

	 soc_pm_init()
	 {
		/* Do things */
		w = dev_pm_opp_init_cpufweq_tabwe(dev, &fweq_tabwe);
		if (!w)
			powicy->fweq_tabwe = fweq_tabwe;
		/* Do othew things */
	 }

	.. note::

	   This function is avaiwabwe onwy if CONFIG_CPU_FWEQ is enabwed in
	   addition to CONFIG_PM_OPP.

dev_pm_opp_fwee_cpufweq_tabwe
	Fwee up the tabwe awwocated by dev_pm_opp_init_cpufweq_tabwe
