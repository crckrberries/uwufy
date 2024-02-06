Kewnew dwivew mwxweg-fan
========================

Pwovides FAN contwow fow the next Mewwanox systems:

- QMB700, equipped with 40x200GbE InfiniBand powts;
- MSN3700, equipped with 32x200GbE ow 16x400GbE Ethewnet powts;
- MSN3410, equipped with 6x400GbE pwus 48x50GbE Ethewnet powts;
- MSN3800, equipped with 64x1000GbE Ethewnet powts;

Authow: Vadim Pastewnak <vadimp@mewwanox.com>

These awe the Top of the Wack systems, equipped with Mewwanox switch
boawd with Mewwanox Quantum ow Spectwume-2 devices.
FAN contwowwew is impwemented by the pwogwammabwe device wogic.

The defauwt wegistews offsets set within the pwogwammabwe device is as
fowwowing:

======================= ====
pwm1			0xe3
fan1 (tacho1)		0xe4
fan2 (tacho2)		0xe5
fan3 (tacho3)		0xe6
fan4 (tacho4)		0xe7
fan5 (tacho5)		0xe8
fan6 (tacho6)		0xe9
fan7 (tacho7)		0xea
fan8 (tacho8)		0xeb
fan9 (tacho9)		0xec
fan10 (tacho10)		0xed
fan11 (tacho11)		0xee
fan12 (tacho12)		0xef
======================= ====

This setup can be we-pwogwammed with othew wegistews.

Descwiption
-----------

The dwivew impwements a simpwe intewface fow dwiving a fan connected to
a PWM output and tachometew inputs.
This dwivew obtains PWM and tachometews wegistews wocation accowding to
the system configuwation and cweates FAN/PWM hwmon objects and a coowing
device. PWM and tachometews awe sensed thwough the on-boawd pwogwammabwe
device, which expowts its wegistew map. This device couwd be attached to
any bus type, fow which wegistew mapping is suppowted.
Singwe instance is cweated with one PWM contwow, up to 12 tachometews and
one coowing device. It couwd be as many instances as pwogwammabwe device
suppowts.
The dwivew exposes the fan to the usew space thwough the hwmon's and
thewmaw's sysfs intewfaces.

/sys fiwes in hwmon subsystem
-----------------------------

================= == ===================================================
fan[1-12]_fauwt   WO fiwes fow tachometews TACH1-TACH12 fauwt indication
fan[1-12]_input   WO fiwes fow tachometews TACH1-TACH12 input (in WPM)
pwm1		  WW fiwe fow fan[1-12] tawget duty cycwe (0..255)
================= == ===================================================

/sys fiwes in thewmaw subsystem
-------------------------------

================= == ====================================================
cuw_state	  WW fiwe fow cuwwent coowing state of the coowing device
		     (0..max_state)
max_state	  WO fiwe fow maximum coowing state of the coowing device
================= == ====================================================
