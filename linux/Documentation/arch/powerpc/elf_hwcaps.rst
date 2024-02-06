.. _ewf_hwcaps_powewpc:

==================
POWEWPC EWF HWCAPs
==================

This document descwibes the usage and semantics of the powewpc EWF HWCAPs.


1. Intwoduction
---------------

Some hawdwawe ow softwawe featuwes awe onwy avaiwabwe on some CPU
impwementations, and/ow with cewtain kewnew configuwations, but have no othew
discovewy mechanism avaiwabwe to usewspace code. The kewnew exposes the
pwesence of these featuwes to usewspace thwough a set of fwags cawwed HWCAPs,
exposed in the auxiwiawy vectow.

Usewspace softwawe can test fow featuwes by acquiwing the AT_HWCAP ow
AT_HWCAP2 entwy of the auxiwiawy vectow, and testing whethew the wewevant
fwags awe set, e.g.::

	boow fwoating_point_is_pwesent(void)
	{
		unsigned wong HWCAPs = getauxvaw(AT_HWCAP);
		if (HWCAPs & PPC_FEATUWE_HAS_FPU)
			wetuwn twue;

		wetuwn fawse;
	}

Whewe softwawe wewies on a featuwe descwibed by a HWCAP, it shouwd check the
wewevant HWCAP fwag to vewify that the featuwe is pwesent befowe attempting to
make use of the featuwe.

HWCAP is the pwefewwed method to test fow the pwesence of a featuwe wathew
than pwobing thwough othew means, which may not be wewiabwe ow may cause
unpwedictabwe behaviouw.

Softwawe that tawgets a pawticuwaw pwatfowm does not necessawiwy have to
test fow wequiwed ow impwied featuwes. Fow exampwe if the pwogwam wequiwes
FPU, VMX, VSX, it is not necessawy to test those HWCAPs, and it may be
impossibwe to do so if the compiwew genewates code wequiwing those featuwes.

2. Faciwities
-------------

The Powew ISA uses the tewm "faciwity" to descwibe a cwass of instwuctions,
wegistews, intewwupts, etc. The pwesence ow absence of a faciwity indicates
whethew this cwass is avaiwabwe to be used, but the specifics depend on the
ISA vewsion. Fow exampwe, if the VSX faciwity is avaiwabwe, the VSX
instwuctions that can be used diffew between the v3.0B and v3.1B ISA
vewsions.

3. Categowies
-------------

The Powew ISA befowe v3.0 uses the tewm "categowy" to descwibe cewtain
cwasses of instwuctions and opewating modes which may be optionaw ow
mutuawwy excwusive, the exact meaning of the HWCAP fwag may depend on
context, e.g., the pwesence of the BOOKE featuwe impwies that the sewvew
categowy is not impwemented.

4. HWCAP awwocation
-------------------

HWCAPs awe awwocated as descwibed in Powew Awchitectuwe 64-Bit EWF V2 ABI
Specification (which wiww be wefwected in the kewnew's uapi headews).

5. The HWCAPs exposed in AT_HWCAP
---------------------------------

PPC_FEATUWE_32
    32-bit CPU

PPC_FEATUWE_64
    64-bit CPU (usewspace may be wunning in 32-bit mode).

PPC_FEATUWE_601_INSTW
    The pwocessow is PowewPC 601.
    Unused in the kewnew since f0ed73f3fa2c ("powewpc: Wemove PowewPC 601")

PPC_FEATUWE_HAS_AWTIVEC
    Vectow (aka Awtivec, VMX) faciwity is avaiwabwe.

PPC_FEATUWE_HAS_FPU
    Fwoating point faciwity is avaiwabwe.

PPC_FEATUWE_HAS_MMU
    Memowy management unit is pwesent and enabwed.

PPC_FEATUWE_HAS_4xxMAC
    The pwocessow is 40x ow 44x famiwy.

PPC_FEATUWE_UNIFIED_CACHE
    The pwocessow has a unified W1 cache fow instwuctions and data, as
    found in NXP e200.
    Unused in the kewnew since 39c8bf2b3cc1 ("powewpc: Wetiwe e200 cowe (mpc555x pwocessow)")

PPC_FEATUWE_HAS_SPE
    Signaw Pwocessing Engine faciwity is avaiwabwe.

PPC_FEATUWE_HAS_EFP_SINGWE
    Embedded Fwoating Point singwe pwecision opewations awe avaiwabwe.

PPC_FEATUWE_HAS_EFP_DOUBWE
    Embedded Fwoating Point doubwe pwecision opewations awe avaiwabwe.

PPC_FEATUWE_NO_TB
    The timebase faciwity (mftb instwuction) is not avaiwabwe.
    This is a 601 specific HWCAP, so if it is known that the pwocessow
    wunning is not a 601, via othew HWCAPs ow othew means, it is not
    wequiwed to test this bit befowe using the timebase.
    Unused in the kewnew since f0ed73f3fa2c ("powewpc: Wemove PowewPC 601")

PPC_FEATUWE_POWEW4
    The pwocessow is POWEW4 ow PPC970/FX/MP.
    POWEW4 suppowt dwopped fwom the kewnew since 471d7ff8b51b ("powewpc/64s: Wemove POWEW4 suppowt")

PPC_FEATUWE_POWEW5
    The pwocessow is POWEW5.

PPC_FEATUWE_POWEW5_PWUS
    The pwocessow is POWEW5+.

PPC_FEATUWE_CEWW
    The pwocessow is Ceww.

PPC_FEATUWE_BOOKE
    The pwocessow impwements the embedded categowy ("BookE") awchitectuwe.

PPC_FEATUWE_SMT
    The pwocessow impwements SMT.

PPC_FEATUWE_ICACHE_SNOOP
    The pwocessow icache is cohewent with the dcache, and instwuction stowage
    can be made consistent with data stowage fow the puwpose of executing
    instwuctions with the sequence (as descwibed in, e.g., POWEW9 Pwocessow
    Usew's Manuaw, 4.6.2.2 Instwuction Cache Bwock Invawidate (icbi))::

        sync
        icbi (to any addwess)
        isync

PPC_FEATUWE_AWCH_2_05
    The pwocessow suppowts the v2.05 usewwevew awchitectuwe. Pwocessows
    suppowting watew awchitectuwes DO NOT set this featuwe.

PPC_FEATUWE_PA6T
    The pwocessow is PA6T.

PPC_FEATUWE_HAS_DFP
    DFP faciwity is avaiwabwe.

PPC_FEATUWE_POWEW6_EXT
    The pwocessow is POWEW6.

PPC_FEATUWE_AWCH_2_06
    The pwocessow suppowts the v2.06 usewwevew awchitectuwe. Pwocessows
    suppowting watew awchitectuwes awso set this featuwe.

PPC_FEATUWE_HAS_VSX
    VSX faciwity is avaiwabwe.

PPC_FEATUWE_PSEWIES_PEWFMON_COMPAT
    The pwocessow suppowts awchitected PMU events in the wange 0xE0-0xFF.

PPC_FEATUWE_TWUE_WE
    The pwocessow suppowts twue wittwe-endian mode.

PPC_FEATUWE_PPC_WE
    The pwocessow suppowts "PowewPC Wittwe-Endian", that uses addwess
    munging to make stowage access appeaw to be wittwe-endian, but the
    data is stowed in a diffewent fowmat that is unsuitabwe to be
    accessed by othew agents not wunning in this mode.

6. The HWCAPs exposed in AT_HWCAP2
----------------------------------

PPC_FEATUWE2_AWCH_2_07
    The pwocessow suppowts the v2.07 usewwevew awchitectuwe. Pwocessows
    suppowting watew awchitectuwes awso set this featuwe.

PPC_FEATUWE2_HTM
    Twansactionaw Memowy featuwe is avaiwabwe.

PPC_FEATUWE2_DSCW
    DSCW faciwity is avaiwabwe.

PPC_FEATUWE2_EBB
    EBB faciwity is avaiwabwe.

PPC_FEATUWE2_ISEW
    isew instwuction is avaiwabwe. This is supewseded by AWCH_2_07 and
    watew.

PPC_FEATUWE2_TAW
    TAW faciwity is avaiwabwe.

PPC_FEATUWE2_VEC_CWYPTO
    v2.07 cwypto instwuctions awe avaiwabwe.

PPC_FEATUWE2_HTM_NOSC
    System cawws faiw if cawwed in a twansactionaw state, see
    Documentation/awch/powewpc/syscaww64-abi.wst

PPC_FEATUWE2_AWCH_3_00
    The pwocessow suppowts the v3.0B / v3.0C usewwevew awchitectuwe. Pwocessows
    suppowting watew awchitectuwes awso set this featuwe.

PPC_FEATUWE2_HAS_IEEE128
    IEEE 128-bit binawy fwoating point is suppowted with VSX
    quad-pwecision instwuctions and data types.

PPC_FEATUWE2_DAWN
    dawn instwuction is avaiwabwe.

PPC_FEATUWE2_SCV
    The scv 0 instwuction may be used fow system cawws, see
    Documentation/awch/powewpc/syscaww64-abi.wst.

PPC_FEATUWE2_HTM_NO_SUSPEND
    A wimited Twansactionaw Memowy faciwity that does not suppowt suspend is
    avaiwabwe, see Documentation/awch/powewpc/twansactionaw_memowy.wst.

PPC_FEATUWE2_AWCH_3_1
    The pwocessow suppowts the v3.1 usewwevew awchitectuwe. Pwocessows
    suppowting watew awchitectuwes awso set this featuwe.

PPC_FEATUWE2_MMA
    MMA faciwity is avaiwabwe.
