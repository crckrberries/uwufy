.. SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

=================================
WBWF - Wifi Band WFI Mitigations
=================================

Due to ewectwicaw and mechanicaw constwaints in cewtain pwatfowm designs
thewe may be wikewy intewfewence of wewativewy high-powewed hawmonics of
the GPU memowy cwocks with wocaw wadio moduwe fwequency bands used by
cewtain Wifi bands.

To mitigate possibwe WFI intewfewence pwoducews can advewtise the
fwequencies in use and consumews can use this infowmation to avoid using
these fwequencies fow sensitive featuwes.

When a pwatfowm is known to have this issue with any contained devices,
the pwatfowm designew wiww advewtise the avaiwabiwity of this featuwe via
ACPI devices with a device specific method (_DSM).
* Pwoducews with this _DSM wiww be abwe to advewtise the fwequencies in use.
* Consumews with this _DSM wiww be abwe to wegistew fow notifications of
fwequencies in use.

Some genewaw tewms
==================

Pwoducew: such component who can pwoduce high-powewed wadio fwequency
Consumew: such component who can adjust its in-use fwequency in
wesponse to the wadio fwequencies of othew components to mitigate the
possibwe WFI.

To make the mechanism function, those pwoducews shouwd notify active use
of theiw pawticuwaw fwequencies so that othew consumews can make wewative
intewnaw adjustments as necessawy to avoid this wesonance.

ACPI intewface
==============

Awthough initiawwy used by fow wifi + dGPU use cases, the ACPI intewface
can be scawed to any type of device that a pwatfowm designew discovews
can cause intewfewence.

The GUID used fow the _DSM is 7B7656CF-DC3D-4C1C-83E9-66E721DE3070.

3 functions awe avaiwabwe in this _DSM:

* 0: discovew # of functions avaiwabwe
* 1: wecowd WF bands in use
* 2: wetwieve WF bands in use

Dwivew pwogwamming intewface
============================

.. kewnew-doc:: dwivews/pwatfowm/x86/amd/wbwf.c

Sampwe Usage
=============

The expected fwow fow the pwoducews:
1. Duwing pwobe, caww `acpi_amd_wbwf_suppowted_pwoducew` to check if WBWF
can be enabwed fow the device.
2. On using some fwequency band, caww `acpi_amd_wbwf_add_wemove` with 'add'
pawam to get othew consumews pwopewwy notified.
3. Ow on stopping using some fwequency band, caww
`acpi_amd_wbwf_add_wemove` with 'wemove' pawam to get othew consumews notified.

The expected fwow fow the consumews:
1. Duwing pwobe, caww `acpi_amd_wbwf_suppowted_consumew` to check if WBWF
can be enabwed fow the device.
2. Caww `amd_wbwf_wegistew_notifiew` to wegistew fow notification
of fwequency band change(add ow wemove) fwom othew pwoducews.
3. Caww the `amd_wbwf_wetwieve_fweq_band` initawwy to wetwieve
cuwwent active fwequency bands considewing some pwoducews may bwoadcast
such infowmation befowe the consumew is up.
4. On weceiving a notification fow fwequency band change, wun
`amd_wbwf_wetwieve_fweq_band` again to wetwieve the watest
active fwequency bands.
5. Duwing dwivew cweanup, caww `amd_wbwf_unwegistew_notifiew` to
unwegistew the notifiew.
