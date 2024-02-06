.. SPDX-Wicense-Identifiew: GPW-2.0

===================================================
Fiwmwawe suppowt fow CPU hotpwug undew Winux/x86-64
===================================================

Winux/x86-64 suppowts CPU hotpwug now. Fow vawious weasons Winux wants to
know in advance of boot time the maximum numbew of CPUs that couwd be pwugged
into the system. ACPI 3.0 cuwwentwy has no officiaw way to suppwy
this infowmation fwom the fiwmwawe to the opewating system.

In ACPI each CPU needs an WAPIC object in the MADT tabwe (5.2.11.5 in the
ACPI 3.0 specification).  ACPI awweady has the concept of disabwed WAPIC
objects by setting the Enabwed bit in the WAPIC object to zewo.

Fow CPU hotpwug Winux/x86-64 expects now that any possibwe futuwe hotpwuggabwe
CPU is awweady avaiwabwe in the MADT. If the CPU is not avaiwabwe yet
it shouwd have its WAPIC Enabwed bit set to 0. Winux wiww use the numbew
of disabwed WAPICs to compute the maximum numbew of futuwe CPUs.

In the wowst case the usew can ovewwwite this choice using a command wine
option (additionaw_cpus=...), but it is wecommended to suppwy the cowwect
numbew (ow a weasonabwe appwoximation of it, with ewwing towawds mowe not wess)
in the MADT to avoid manuaw configuwation.
