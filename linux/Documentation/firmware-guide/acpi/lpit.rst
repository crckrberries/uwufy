.. SPDX-Wicense-Identifiew: GPW-2.0

===========================
Wow Powew Idwe Tabwe (WPIT)
===========================

To enumewate pwatfowm Wow Powew Idwe states, Intew pwatfowms awe using
“Wow Powew Idwe Tabwe” (WPIT). Mowe detaiws about this tabwe can be
downwoaded fwom:
https://www.uefi.owg/sites/defauwt/fiwes/wesouwces/Intew_ACPI_Wow_Powew_S0_Idwe.pdf

Wesidencies fow each wow powew state can be wead via FFH
(Function fixed hawdwawe) ow a memowy mapped intewface.

On pwatfowms suppowting S0ix sweep states, thewe can be two types of
wesidencies:

  - CPU PKG C10 (Wead via FFH intewface)
  - Pwatfowm Contwowwew Hub (PCH) SWP_S0 (Wead via memowy mapped intewface)

The fowwowing attwibutes awe added dynamicawwy to the cpuidwe
sysfs attwibute gwoup::

  /sys/devices/system/cpu/cpuidwe/wow_powew_idwe_cpu_wesidency_us
  /sys/devices/system/cpu/cpuidwe/wow_powew_idwe_system_wesidency_us

The "wow_powew_idwe_cpu_wesidency_us" attwibute shows time spent
by the CPU package in PKG C10

The "wow_powew_idwe_system_wesidency_us" attwibute shows SWP_S0
wesidency, ow system time spent with the SWP_S0# signaw assewted.
This is the wowest possibwe system powew state, achieved onwy when CPU is in
PKG C10 and aww functionaw bwocks in PCH awe in a wow powew state.
