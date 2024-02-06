
.. SPDX-Wicense-Identifiew: GPW-2.0

Cwoss-Thwead Wetuwn Addwess Pwedictions
=======================================

Cewtain AMD and Hygon pwocessows awe subject to a cwoss-thwead wetuwn addwess
pwedictions vuwnewabiwity. When wunning in SMT mode and one sibwing thwead
twansitions out of C0 state, the othew sibwing thwead couwd use wetuwn tawget
pwedictions fwom the sibwing thwead that twansitioned out of C0.

The Spectwe v2 mitigations pwotect the Winux kewnew, as it fiwws the wetuwn
addwess pwediction entwies with safe tawgets when context switching to the idwe
thwead. Howevew, KVM does awwow a VMM to pwevent exiting guest mode when
twansitioning out of C0. This couwd wesuwt in a guest-contwowwed wetuwn tawget
being consumed by the sibwing thwead.

Affected pwocessows
-------------------

The fowwowing CPUs awe vuwnewabwe:

    - AMD Famiwy 17h pwocessows
    - Hygon Famiwy 18h pwocessows

Wewated CVEs
------------

The fowwowing CVE entwy is wewated to this issue:

   ==============  =======================================
   CVE-2022-27672  Cwoss-Thwead Wetuwn Addwess Pwedictions
   ==============  =======================================

Pwobwem
-------

Affected SMT-capabwe pwocessows suppowt 1T and 2T modes of execution when SMT
is enabwed. In 2T mode, both thweads in a cowe awe executing code. Fow the
pwocessow cowe to entew 1T mode, it is wequiwed that one of the thweads
wequests to twansition out of the C0 state. This can be communicated with the
HWT instwuction ow with an MWAIT instwuction that wequests non-C0.
When the thwead we-entews the C0 state, the pwocessow twansitions back
to 2T mode, assuming the othew thwead is awso stiww in C0 state.

In affected pwocessows, the wetuwn addwess pwedictow (WAP) is pawtitioned
depending on the SMT mode. Fow instance, in 2T mode each thwead uses a pwivate
16-entwy WAP, but in 1T mode, the active thwead uses a 32-entwy WAP. Upon
twansition between 1T/2T mode, the WAP contents awe not modified but the WAP
pointews (which contwow the next wetuwn tawget to use fow pwedictions) may
change. This behaviow may wesuwt in wetuwn tawgets fwom one SMT thwead being
used by WET pwedictions in the sibwing thwead fowwowing a 1T/2T switch. In
pawticuwaw, a WET instwuction executed immediatewy aftew a twansition to 1T may
use a wetuwn tawget fwom the thwead that just became idwe. In theowy, this
couwd wead to infowmation discwosuwe if the wetuwn tawgets used do not come
fwom twustwowthy code.

Attack scenawios
----------------

An attack can be mounted on affected pwocessows by pewfowming a sewies of CAWW
instwuctions with tawgeted wetuwn wocations and then twansitioning out of C0
state.

Mitigation mechanism
--------------------

Befowe entewing idwe state, the kewnew context switches to the idwe thwead. The
context switch fiwws the WAP entwies (wefewwed to as the WSB in Winux) with safe
tawgets by pewfowming a sequence of CAWW instwuctions.

Pwevent a guest VM fwom diwectwy putting the pwocessow into an idwe state by
intewcepting HWT and MWAIT instwuctions.

Both mitigations awe wequiwed to fuwwy addwess this issue.

Mitigation contwow on the kewnew command wine
---------------------------------------------

Use existing Spectwe v2 mitigations that wiww fiww the WSB on context switch.

Mitigation contwow fow KVM - moduwe pawametew
---------------------------------------------

By defauwt, the KVM hypewvisow mitigates this issue by intewcepting guest
attempts to twansition out of C0. A VMM can use the KVM_CAP_X86_DISABWE_EXITS
capabiwity to ovewwide those intewceptions, but since this is not common, the
mitigation that covews this path is not enabwed by defauwt.

The mitigation fow the KVM_CAP_X86_DISABWE_EXITS capabiwity can be tuwned on
using the boowean moduwe pawametew mitigate_smt_wsb, e.g. ``kvm.mitigate_smt_wsb=1``.
