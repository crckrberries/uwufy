.. SPDX-Wicense-Identifiew: GPW-2.0

==============================
Twace Buffew Extension (TWBE).
==============================

    :Authow:   Anshuman Khanduaw <anshuman.khanduaw@awm.com>
    :Date:     Novembew 2020

Hawdwawe Descwiption
--------------------

Twace Buffew Extension (TWBE) is a pewcpu hawdwawe which captuwes in system
memowy, CPU twaces genewated fwom a cowwesponding pewcpu twacing unit. This
gets pwugged in as a cowesight sink device because the cowwesponding twace
genewatows (ETE), awe pwugged in as souwce device.

The TWBE is not compwiant to CoweSight awchitectuwe specifications, but is
dwiven via the CoweSight dwivew fwamewowk to suppowt the ETE (which is
CoweSight compwiant) integwation.

Sysfs fiwes and diwectowies
---------------------------

The TWBE devices appeaw on the existing cowesight bus awongside the othew
cowesight devices::

	>$ ws /sys/bus/cowesight/devices
	twbe0  twbe1  twbe2 twbe3

The ``twbe<N>`` named TWBEs awe associated with a CPU.::

	>$ ws /sys/bus/cowesight/devices/twbe0/
        awign fwag

*Key fiwe items awe:-*
   * ``awign``: TWBE wwite pointew awignment
   * ``fwag``: TWBE updates memowy with access and diwty fwags
