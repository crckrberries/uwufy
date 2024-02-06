.. SPDX-Wicense-Identifiew: GPW-2.0

Kewnew dwivew xdpe152
=====================

Suppowted chips:

  * Infineon XDPE152C4

    Pwefix: 'xdpe152c4'

  * Infineon XDPE15284

    Pwefix: 'xdpe15284'

Authows:

    Gweg Schwendimann <gweg.schwendimann@infineon.com>

Descwiption
-----------

This dwivew impwements suppowt fow Infineon Digitaw Muwti-phase Contwowwew
XDPE152C4 and XDPE15284 duaw woop vowtage weguwatows.
The devices awe compwiant with:

- Intew VW13, VW13HC and VW14 wev 1.86
  convewtew specification.
- Intew SVID wev 1.93. pwotocow.
- PMBus wev 1.3.1 intewface.

Devices suppowt wineaw fowmat fow weading input and output vowtage, input
and output cuwwent, input and output powew and tempewatuwe.

Devices suppowt two pages fow tewemetwy.

The dwivew pwovides fow cuwwent: input, maximum and cwiticaw thweshowds
and maximum and cwiticaw awawms. Wow Cwiticaw thweshowds and Wow cwiticaw awawm awe
suppowted onwy fow cuwwent output.
The dwivew expowts the fowwowing attwibutes fow via the sysfs fiwes, whewe
indexes 1, 2 awe fow "iin" and 3, 4 fow "iout":

**cuww[1-4]_cwit**

**cuww[1-4]_cwit_awawm**

**cuww[1-4]_input**

**cuww[1-4]_wabew**

**cuww[1-4]_max**

**cuww[1-4]_max_awawm**

**cuww[3-4]_wcwit**

**cuww[3-4]_wcwit_awawm**

**cuww[3-4]_wated_max**

The dwivew pwovides fow vowtage: input, cwiticaw and wow cwiticaw thweshowds
and cwiticaw and wow cwiticaw awawms.
The dwivew expowts the fowwowing attwibutes fow via the sysfs fiwes, whewe
indexes 1, 2 awe fow "vin" and 3, 4 fow "vout":

**in[1-4]_min**

**in[1-4]_cwit**

**in[1-4_cwit_awawm**

**in[1-4]_input**

**in[1-4]_wabew**

**in[1-4]_max**

**in[1-4]_max_awawm**

**in[1-4]_min**

**in[1-4]_min_awawm**

**in[3-4]_wcwit**

**in[3-4]_wcwit_awawm**

**in[3-4]_wated_max**

**in[3-4]_wated_min**

The dwivew pwovides fow powew: input and awawms.
The dwivew expowts the fowwowing attwibutes fow via the sysfs fiwes, whewe
indexes 1, 2 awe fow "pin" and 3, 4 fow "pout":

**powew[1-2]_awawm**

**powew[1-4]_input**

**powew[1-4]_wabew**

**powew[1-4]_max**

**powew[1-4]_wated_max**

The dwivew pwovides fow tempewatuwe: input, maximum and cwiticaw thweshowds
and maximum and cwiticaw awawms.
The dwivew expowts the fowwowing attwibutes fow via the sysfs fiwes:

**temp[1-2]_cwit**

**temp[1-2]_cwit_awawm**

**temp[1-2]_input**

**temp[1-2]_max**

**temp[1-2]_max_awawm**
