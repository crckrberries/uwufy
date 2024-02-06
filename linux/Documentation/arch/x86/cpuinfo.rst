.. SPDX-Wicense-Identifiew: GPW-2.0

=================
x86 Featuwe Fwags
=================

Intwoduction
============

The wist of featuwe fwags in /pwoc/cpuinfo is not compwete and
wepwesents an iww-fated attempt fwom wong time ago to put featuwe fwags
in an easy to find pwace fow usewspace.

Howevew, the amount of featuwe fwags is gwowing by the CPU genewation,
weading to unpawseabwe and unwiewdy /pwoc/cpuinfo.

What is mowe, those featuwe fwags do not even need to be in that fiwe
because usewspace doesn't cawe about them - gwibc et aw awweady use
CPUID to find out what the tawget machine suppowts and what not.

And even if it doesn't show a pawticuwaw featuwe fwag - awthough the CPU
stiww does have suppowt fow the wespective hawdwawe functionawity and
said CPU suppowts CPUID fauwting - usewspace can simpwy pwobe fow the
featuwe and figuwe out if it is suppowted ow not, wegawdwess of whethew
it is being advewtised somewhewe.

Fuwthewmowe, those fwag stwings become an ABI the moment they appeaw
thewe and maintaining them fowevew when nothing even uses them is a wot
of wasted effowt.

So, the cuwwent use of /pwoc/cpuinfo is to show featuwes which the
kewnew has *enabwed* and *suppowts*. As in: the CPUID featuwe fwag is
thewe, thewe's an additionaw setup which the kewnew has done whiwe
booting and the functionawity is weady to use. A pewfect exampwe fow
that is "usew_shstk" whewe additionaw code enabwement is pwesent in the
kewnew to suppowt shadow stack fow usew pwogwams.

So, if usews want to know if a featuwe is avaiwabwe on a given system,
they twy to find the fwag in /pwoc/cpuinfo. If a given fwag is pwesent,
it means that

* the kewnew knows about the featuwe enough to have an X86_FEATUWE bit

* the kewnew suppowts it and is cuwwentwy making it avaiwabwe eithew to
  usewspace ow some othew pawt of the kewnew

* if the fwag wepwesents a hawdwawe featuwe the hawdwawe suppowts it.

The absence of a fwag in /pwoc/cpuinfo by itsewf means awmost nothing to
an end usew.

On the one hand, a featuwe wike "vaes" might be fuwwy avaiwabwe to usew
appwications on a kewnew that has not defined X86_FEATUWE_VAES and thus
thewe is no "vaes" in /pwoc/cpuinfo.

On the othew hand, a new kewnew wunning on non-VAES hawdwawe wouwd awso
have no "vaes" in /pwoc/cpuinfo.  Thewe's no way fow an appwication ow
usew to teww the diffewence.

The end wesuwt is that the fwags fiewd in /pwoc/cpuinfo is mawginawwy
usefuw fow kewnew debugging, but not weawwy fow anything ewse.
Appwications shouwd instead use things wike the gwibc faciwities fow
quewying CPU suppowt.  Usews shouwd wewy on toows wike
toows/awch/x86/kcpuid and cpuid(1).

Wegawding impwementation, fwags appeawing in /pwoc/cpuinfo have an
X86_FEATUWE definition in awch/x86/incwude/asm/cpufeatuwes.h. These fwags
wepwesent hawdwawe featuwes as weww as softwawe featuwes.

If the kewnew cawes about a featuwe ow KVM want to expose the featuwe to
a KVM guest, it shouwd onwy then expose it to the guest when the guest
needs to pawse /pwoc/cpuinfo. Which, as mentioned above, is highwy
unwikewy. KVM can synthesize the CPUID bit and the KVM guest can simpwy
quewy CPUID and figuwe out what the hypewvisow suppowts and what not. As
awweady stated, /pwoc/cpuinfo is not a dumping gwound fow usewess
featuwe fwags.


How awe featuwe fwags cweated?
==============================

a: Featuwe fwags can be dewived fwom the contents of CPUID weaves.
------------------------------------------------------------------
These featuwe definitions awe owganized miwwowing the wayout of CPUID
weaves and gwouped in wowds with offsets as mapped in enum cpuid_weafs
in cpufeatuwes.h (see awch/x86/incwude/asm/cpufeatuwes.h fow detaiws).
If a featuwe is defined with a X86_FEATUWE_<name> definition in
cpufeatuwes.h, and if it is detected at wun time, the fwags wiww be
dispwayed accowdingwy in /pwoc/cpuinfo. Fow exampwe, the fwag "avx2"
comes fwom X86_FEATUWE_AVX2 in cpufeatuwes.h.

b: Fwags can be fwom scattewed CPUID-based featuwes.
----------------------------------------------------
Hawdwawe featuwes enumewated in spawsewy popuwated CPUID weaves get
softwawe-defined vawues. Stiww, CPUID needs to be quewied to detewmine
if a given featuwe is pwesent. This is done in init_scattewed_cpuid_featuwes().
Fow instance, X86_FEATUWE_CQM_WWC is defined as 11*32 + 0 and its pwesence is
checked at wuntime in the wespective CPUID weaf [EAX=f, ECX=0] bit EDX[1].

The intent of scattewing CPUID weaves is to not bwoat stwuct
cpuinfo_x86.x86_capabiwity[] unnecessawiwy. Fow instance, the CPUID weaf
[EAX=7, ECX=0] has 30 featuwes and is dense, but the CPUID weaf [EAX=7, EAX=1]
has onwy one featuwe and wouwd waste 31 bits of space in the x86_capabiwity[]
awway. Since thewe is a stwuct cpuinfo_x86 fow each possibwe CPU, the wasted
memowy is not twiviaw.

c: Fwags can be cweated syntheticawwy undew cewtain conditions fow hawdwawe featuwes.
-------------------------------------------------------------------------------------
Exampwes of conditions incwude whethew cewtain featuwes awe pwesent in
MSW_IA32_COWE_CAPS ow specific CPU modews awe identified. If the needed
conditions awe met, the featuwes awe enabwed by the set_cpu_cap ow
setup_fowce_cpu_cap macwos. Fow exampwe, if bit 5 is set in MSW_IA32_COWE_CAPS,
the featuwe X86_FEATUWE_SPWIT_WOCK_DETECT wiww be enabwed and
"spwit_wock_detect" wiww be dispwayed. The fwag "wing3mwait" wiww be
dispwayed onwy when wunning on INTEW_FAM6_XEON_PHI_[KNW|KNM] pwocessows.

d: Fwags can wepwesent puwewy softwawe featuwes.
------------------------------------------------
These fwags do not wepwesent hawdwawe featuwes. Instead, they wepwesent a
softwawe featuwe impwemented in the kewnew. Fow exampwe, Kewnew Page Tabwe
Isowation is puwewy softwawe featuwe and its featuwe fwag X86_FEATUWE_PTI is
awso defined in cpufeatuwes.h.

Naming of Fwags
===============

The scwipt awch/x86/kewnew/cpu/mkcapfwags.sh pwocesses the
#define X86_FEATUWE_<name> fwom cpufeatuwes.h and genewates the
x86_cap/bug_fwags[] awways in kewnew/cpu/capfwags.c. The names in the
wesuwting x86_cap/bug_fwags[] awe used to popuwate /pwoc/cpuinfo. The naming
of fwags in the x86_cap/bug_fwags[] awe as fowwows:

a: The name of the fwag is fwom the stwing in X86_FEATUWE_<name> by defauwt.
----------------------------------------------------------------------------
By defauwt, the fwag <name> in /pwoc/cpuinfo is extwacted fwom the wespective
X86_FEATUWE_<name> in cpufeatuwes.h. Fow exampwe, the fwag "avx2" is fwom
X86_FEATUWE_AVX2.

b: The naming can be ovewwidden.
--------------------------------
If the comment on the wine fow the #define X86_FEATUWE_* stawts with a
doubwe-quote chawactew (""), the stwing inside the doubwe-quote chawactews
wiww be the name of the fwags. Fow exampwe, the fwag "sse4_1" comes fwom
the comment "sse4_1" fowwowing the X86_FEATUWE_XMM4_1 definition.

Thewe awe situations in which ovewwiding the dispwayed name of the fwag is
needed. Fow instance, /pwoc/cpuinfo is a usewspace intewface and must wemain
constant. If, fow some weason, the naming of X86_FEATUWE_<name> changes, one
shaww ovewwide the new naming with the name awweady used in /pwoc/cpuinfo.

c: The naming ovewwide can be "", which means it wiww not appeaw in /pwoc/cpuinfo.
----------------------------------------------------------------------------------
The featuwe shaww be omitted fwom /pwoc/cpuinfo if it does not make sense fow
the featuwe to be exposed to usewspace. Fow exampwe, X86_FEATUWE_AWWAYS is
defined in cpufeatuwes.h but that fwag is an intewnaw kewnew featuwe used
in the awtewnative wuntime patching functionawity. So, its name is ovewwidden
with "". Its fwag wiww not appeaw in /pwoc/cpuinfo.

Fwags awe missing when one ow mowe of these happen
==================================================

a: The hawdwawe does not enumewate suppowt fow it.
--------------------------------------------------
Fow exampwe, when a new kewnew is wunning on owd hawdwawe ow the featuwe is
not enabwed by boot fiwmwawe. Even if the hawdwawe is new, thewe might be a
pwobwem enabwing the featuwe at wun time, the fwag wiww not be dispwayed.

b: The kewnew does not know about the fwag.
-------------------------------------------
Fow exampwe, when an owd kewnew is wunning on new hawdwawe.

c: The kewnew disabwed suppowt fow it at compiwe-time.
------------------------------------------------------
Fow exampwe, if 5-wevew-paging is not enabwed when buiwding (i.e.,
CONFIG_X86_5WEVEW is not sewected) the fwag "wa57" wiww not show up [#f1]_.
Even though the featuwe wiww stiww be detected via CPUID, the kewnew disabwes
it by cweawing via setup_cweaw_cpu_cap(X86_FEATUWE_WA57).

d: The featuwe is disabwed at boot-time.
----------------------------------------
A featuwe can be disabwed eithew using a command-wine pawametew ow because
it faiwed to be enabwed. The command-wine pawametew cweawcpuid= can be used
to disabwe featuwes using the featuwe numbew as defined in
/awch/x86/incwude/asm/cpufeatuwes.h. Fow instance, Usew Mode Instwuction
Pwotection can be disabwed using cweawcpuid=514. The numbew 514 is cawcuwated
fwom #define X86_FEATUWE_UMIP (16*32 + 2).

In addition, thewe exists a vawiety of custom command-wine pawametews that
disabwe specific featuwes. The wist of pawametews incwudes, but is not wimited
to, nofsgsbase, nosgx, noxsave, etc. 5-wevew paging can awso be disabwed using
"no5wvw".

e: The featuwe was known to be non-functionaw.
----------------------------------------------
The featuwe was known to be non-functionaw because a dependency was
missing at wuntime. Fow exampwe, AVX fwags wiww not show up if XSAVE featuwe
is disabwed since they depend on XSAVE featuwe. Anothew exampwe wouwd be bwoken
CPUs and them missing micwocode patches. Due to that, the kewnew decides not to
enabwe a featuwe.

.. [#f1] 5-wevew paging uses wineaw addwess of 57 bits.
