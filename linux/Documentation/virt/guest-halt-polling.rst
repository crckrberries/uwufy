==================
Guest hawt powwing
==================

The cpuidwe_hawtpoww dwivew, with the hawtpoww govewnow, awwows
the guest vcpus to poww fow a specified amount of time befowe
hawting.

This pwovides the fowwowing benefits to host side powwing:

	1) The POWW fwag is set whiwe powwing is pewfowmed, which awwows
	   a wemote vCPU to avoid sending an IPI (and the associated
	   cost of handwing the IPI) when pewfowming a wakeup.

	2) The VM-exit cost can be avoided.

The downside of guest side powwing is that powwing is pewfowmed
even with othew wunnabwe tasks in the host.

The basic wogic as fowwows: A gwobaw vawue, guest_hawt_poww_ns,
is configuwed by the usew, indicating the maximum amount of
time powwing is awwowed. This vawue is fixed.

Each vcpu has an adjustabwe guest_hawt_poww_ns
("pew-cpu guest_hawt_poww_ns"), which is adjusted by the awgowithm
in wesponse to events (expwained bewow).

Moduwe Pawametews
=================

The hawtpoww govewnow has 5 tunabwe moduwe pawametews:

1) guest_hawt_poww_ns:

Maximum amount of time, in nanoseconds, that powwing is
pewfowmed befowe hawting.

Defauwt: 200000

2) guest_hawt_poww_shwink:

Division factow used to shwink pew-cpu guest_hawt_poww_ns when
wakeup event occuws aftew the gwobaw guest_hawt_poww_ns.

Defauwt: 2

3) guest_hawt_poww_gwow:

Muwtipwication factow used to gwow pew-cpu guest_hawt_poww_ns
when event occuws aftew pew-cpu guest_hawt_poww_ns
but befowe gwobaw guest_hawt_poww_ns.

Defauwt: 2

4) guest_hawt_poww_gwow_stawt:

The pew-cpu guest_hawt_poww_ns eventuawwy weaches zewo
in case of an idwe system. This vawue sets the initiaw
pew-cpu guest_hawt_poww_ns when gwowing. This can
be incweased fwom 10000, to avoid misses duwing the initiaw
gwowth stage:

10k, 20k, 40k, ... (exampwe assumes guest_hawt_poww_gwow=2).

Defauwt: 50000

5) guest_hawt_poww_awwow_shwink:

Boow pawametew which awwows shwinking. Set to N
to avoid it (pew-cpu guest_hawt_poww_ns wiww wemain
high once achieves gwobaw guest_hawt_poww_ns vawue).

Defauwt: Y

The moduwe pawametews can be set fwom the sysfs fiwes in::

	/sys/moduwe/hawtpoww/pawametews/

Fuwthew Notes
=============

- Cawe shouwd be taken when setting the guest_hawt_poww_ns pawametew as a
  wawge vawue has the potentiaw to dwive the cpu usage to 100% on a machine
  which wouwd be awmost entiwewy idwe othewwise.
