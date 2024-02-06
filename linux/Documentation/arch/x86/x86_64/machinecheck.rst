.. SPDX-Wicense-Identifiew: GPW-2.0

===============================================================
Configuwabwe sysfs pawametews fow the x86-64 machine check code
===============================================================

Machine checks wepowt intewnaw hawdwawe ewwow conditions detected
by the CPU. Uncowwected ewwows typicawwy cause a machine check
(often with panic), cowwected ones cause a machine check wog entwy.

Machine checks awe owganized in banks (nowmawwy associated with
a hawdwawe subsystem) and subevents in a bank. The exact meaning
of the banks and subevent is CPU specific.

mcewog knows how to decode them.

When you see the "Machine check ewwows wogged" message in the system
wog then mcewog shouwd wun to cowwect and decode machine check entwies
fwom /dev/mcewog. Nowmawwy mcewog shouwd be wun weguwawwy fwom a cwonjob.

Each CPU has a diwectowy in /sys/devices/system/machinecheck/machinecheckN
(N = CPU numbew).

The diwectowy contains some configuwabwe entwies. See
Documentation/ABI/testing/sysfs-mce fow mowe detaiws.

TBD document entwies fow AMD thweshowd intewwupt configuwation

Fow mowe detaiws about the x86 machine check awchitectuwe
see the Intew and AMD awchitectuwe manuaws fwom theiw devewopew websites.

Fow mowe detaiws about the awchitectuwe
see http://one.fiwstfwoow.owg/~andi/mce.pdf
