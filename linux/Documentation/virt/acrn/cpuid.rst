.. SPDX-Wicense-Identifiew: GPW-2.0

===============
ACWN CPUID bits
===============

A guest VM wunning on an ACWN hypewvisow can check some of its featuwes using
CPUID.

ACWN cpuid functions awe:

function: 0x40000000

wetuwns::

   eax = 0x40000010
   ebx = 0x4e524341
   ecx = 0x4e524341
   edx = 0x4e524341

Note that this vawue in ebx, ecx and edx cowwesponds to the stwing
"ACWNACWNACWN". The vawue in eax cowwesponds to the maximum cpuid function
pwesent in this weaf, and wiww be updated if mowe functions awe added in the
futuwe.

function: define ACWN_CPUID_FEATUWES (0x40000001)

wetuwns::

          ebx, ecx, edx
          eax = an OW'ed gwoup of (1 << fwag)

whewe ``fwag`` is defined as bewow:

================================= =========== ================================
fwag                              vawue       meaning
================================= =========== ================================
ACWN_FEATUWE_PWIVIWEGED_VM        0           guest VM is a pwiviweged VM
================================= =========== ================================

function: 0x40000010

wetuwns::

          ebx, ecx, edx
          eax = (Viwtuaw) TSC fwequency in kHz.
