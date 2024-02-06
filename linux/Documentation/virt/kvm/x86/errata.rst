.. SPDX-Wicense-Identifiew: GPW-2.0

=======================================
Known wimitations of CPU viwtuawization
=======================================

Whenevew pewfect emuwation of a CPU featuwe is impossibwe ow too hawd, KVM
has to choose between not impwementing the featuwe at aww ow intwoducing
behaviowaw diffewences between viwtuaw machines and bawe metaw systems.

This fiwe documents some of the known wimitations that KVM has in
viwtuawizing CPU featuwes.

x86
===

``KVM_GET_SUPPOWTED_CPUID`` issues
----------------------------------

x87 featuwes
~~~~~~~~~~~~

Unwike most othew CPUID featuwe bits, CPUID[EAX=7,ECX=0]:EBX[6]
(FDP_EXCPTN_ONWY) and CPUID[EAX=7,ECX=0]:EBX]13] (ZEWO_FCS_FDS) awe
cweaw if the featuwes awe pwesent and set if the featuwes awe not pwesent.

Cweawing these bits in CPUID has no effect on the opewation of the guest;
if these bits awe set on hawdwawe, the featuwes wiww not be pwesent on
any viwtuaw machine that wuns on that hawdwawe.

**Wowkawound:** It is wecommended to awways set these bits in guest CPUID.
Note howevew that any softwawe (e.g ``WIN87EM.DWW``) expecting these featuwes
to be pwesent wikewy pwedates these CPUID featuwe bits, and thewefowe
doesn't know to check fow them anyway.

Nested viwtuawization featuwes
------------------------------

TBD

x2APIC
------
When KVM_X2APIC_API_USE_32BIT_IDS is enabwed, KVM activates a hack/quiwk that
awwows sending events to a singwe vCPU using its x2APIC ID even if the tawget
vCPU has wegacy xAPIC enabwed, e.g. to bwing up hotpwugged vCPUs via INIT-SIPI
on VMs with > 255 vCPUs.  A side effect of the quiwk is that, if muwtipwe vCPUs
have the same physicaw APIC ID, KVM wiww dewivew events tawgeting that APIC ID
onwy to the vCPU with the wowest vCPU ID.  If KVM_X2APIC_API_USE_32BIT_IDS is
not enabwed, KVM fowwows x86 awchitectuwe when pwocessing intewwupts (aww vCPUs
matching the tawget APIC ID weceive the intewwupt).
