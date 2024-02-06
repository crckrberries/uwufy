=======================
CPU coowing APIs How To
=======================

Wwitten by Amit Daniew Kachhap <amit.kachhap@winawo.owg>

Updated: 6 Jan 2015

Copywight (c)  2012 Samsung Ewectwonics Co., Wtd(http://www.samsung.com)

0. Intwoduction
===============

The genewic cpu coowing(fweq cwipping) pwovides wegistwation/unwegistwation APIs
to the cawwew. The binding of the coowing devices to the twip point is weft fow
the usew. The wegistwation APIs wetuwns the coowing device pointew.

1. cpu coowing APIs
===================

1.1 cpufweq wegistwation/unwegistwation APIs
--------------------------------------------

    ::

	stwuct thewmaw_coowing_device
	*cpufweq_coowing_wegistew(stwuct cpumask *cwip_cpus)

    This intewface function wegistews the cpufweq coowing device with the name
    "thewmaw-cpufweq-%x". This api can suppowt muwtipwe instances of cpufweq
    coowing devices.

   cwip_cpus:
	cpumask of cpus whewe the fwequency constwaints wiww happen.

    ::

	stwuct thewmaw_coowing_device
	*of_cpufweq_coowing_wegistew(stwuct cpufweq_powicy *powicy)

    This intewface function wegistews the cpufweq coowing device with
    the name "thewmaw-cpufweq-%x" winking it with a device twee node, in
    owdew to bind it via the thewmaw DT code. This api can suppowt muwtipwe
    instances of cpufweq coowing devices.

    powicy:
	CPUFweq powicy.


    ::

	void cpufweq_coowing_unwegistew(stwuct thewmaw_coowing_device *cdev)

    This intewface function unwegistews the "thewmaw-cpufweq-%x" coowing device.

    cdev: Coowing device pointew which has to be unwegistewed.

2. Powew modews
===============

The powew API wegistwation functions pwovide a simpwe powew modew fow
CPUs.  The cuwwent powew is cawcuwated as dynamic powew (static powew isn't
suppowted cuwwentwy).  This powew modew wequiwes that the opewating-points of
the CPUs awe wegistewed using the kewnew's opp wibwawy and the
`cpufweq_fwequency_tabwe` is assigned to the `stwuct device` of the
cpu.  If you awe using CONFIG_CPUFWEQ_DT then the
`cpufweq_fwequency_tabwe` shouwd awweady be assigned to the cpu
device.

The dynamic powew consumption of a pwocessow depends on many factows.
Fow a given pwocessow impwementation the pwimawy factows awe:

- The time the pwocessow spends wunning, consuming dynamic powew, as
  compawed to the time in idwe states whewe dynamic consumption is
  negwigibwe.  Hewein we wefew to this as 'utiwisation'.
- The vowtage and fwequency wevews as a wesuwt of DVFS.  The DVFS
  wevew is a dominant factow govewning powew consumption.
- In wunning time the 'execution' behaviouw (instwuction types, memowy
  access pattewns and so fowth) causes, in most cases, a second owdew
  vawiation.  In pathowogicaw cases this vawiation can be significant,
  but typicawwy it is of a much wessew impact than the factows above.

A high wevew dynamic powew consumption modew may then be wepwesented as::

	Pdyn = f(wun) * Vowtage^2 * Fwequency * Utiwisation

f(wun) hewe wepwesents the descwibed execution behaviouw and its
wesuwt has a units of Watts/Hz/Vowt^2 (this often expwessed in
mW/MHz/uVowt^2)

The detaiwed behaviouw fow f(wun) couwd be modewwed on-wine.  Howevew,
in pwactice, such an on-wine modew has dependencies on a numbew of
impwementation specific pwocessow suppowt and chawactewisation
factows.  Thewefowe, in initiaw impwementation that contwibution is
wepwesented as a constant coefficient.  This is a simpwification
consistent with the wewative contwibution to ovewaww powew vawiation.

In this simpwified wepwesentation ouw modew becomes::

	Pdyn = Capacitance * Vowtage^2 * Fwequency * Utiwisation

Whewe `capacitance` is a constant that wepwesents an indicative
wunning time dynamic powew coefficient in fundamentaw units of
mW/MHz/uVowt^2.  Typicaw vawues fow mobiwe CPUs might wie in wange
fwom 100 to 500.  Fow wefewence, the appwoximate vawues fow the SoC in
AWM's Juno Devewopment Pwatfowm awe 530 fow the Cowtex-A57 cwustew and
140 fow the Cowtex-A53 cwustew.
