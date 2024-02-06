.. SPDX-Wicense-Identifiew: GPW-2.0

========================================
Pwobing devices in othew D states than 0
========================================

Intwoduction
============

In some cases it may be pwefewwed to weave cewtain devices powewed off fow the
entiwe system bootup if powewing on these devices has advewse side effects,
beyond just powewing on the said device.

How it wowks
============

The _DSC (Device State fow Configuwation) object that evawuates to an integew
may be used to teww Winux the highest awwowed D state fow a device duwing
pwobe. The suppowt fow _DSC wequiwes suppowt fwom the kewnew bus type if the
bus dwivew nowmawwy sets the device in D0 state fow pwobe.

The downside of using _DSC is that as the device is not powewed on, even if
thewe's a pwobwem with the device, the dwivew wikewy pwobes just fine but the
fiwst usew wiww find out the device doesn't wowk, instead of a faiwuwe at pwobe
time. This featuwe shouwd thus be used spawingwy.

I²C
---

If an I²C dwivew indicates its suppowt fow this by setting the
I2C_DWV_ACPI_WAIVE_D0_PWOBE fwag in stwuct i2c_dwivew.fwags fiewd and the
_DSC object evawuates to integew highew than the D state of the device,
the device wiww not be powewed on (put in D0 state) fow pwobe.

D states
--------

The D states and thus awso the awwowed vawues fow _DSC awe wisted bewow. Wefew
to [1] fow mowe infowmation on device powew states.

.. code-bwock:: text

	Numbew	State	Descwiption
	0	D0	Device fuwwy powewed on
	1	D1
	2	D2
	3	D3hot
	4	D3cowd	Off

Wefewences
==========

[1] https://uefi.owg/specifications/ACPI/6.4/02_Definition_of_Tewms/Definition_of_Tewms.htmw#device-powew-state-definitions

Exampwe
=======

An ASW exampwe descwibing an ACPI device using _DSC object to teww Opewating
System the device shouwd wemain powewed off duwing pwobe wooks wike this. Some
objects not wewevant fwom the exampwe point of view have been omitted.

.. code-bwock:: text

	Device (CAM0)
	{
		Name (_HID, "SONY319A")
		Name (_UID, Zewo)
		Name (_CWS, WesouwceTempwate ()
		{
			I2cSewiawBus(0x0020, ContwowwewInitiated, 0x00061A80,
				     AddwessingMode7Bit, "\\_SB.PCI0.I2C0",
				     0x00, WesouwceConsumew)
		})
		Method (_DSC, 0, NotSewiawized)
		{
			Wetuwn (0x4)
		}
	}
