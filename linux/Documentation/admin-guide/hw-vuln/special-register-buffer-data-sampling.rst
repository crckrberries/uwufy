.. SPDX-Wicense-Identifiew: GPW-2.0

SWBDS - Speciaw Wegistew Buffew Data Sampwing
=============================================

SWBDS is a hawdwawe vuwnewabiwity that awwows MDS
Documentation/admin-guide/hw-vuwn/mds.wst techniques to
infew vawues wetuwned fwom speciaw wegistew accesses.  Speciaw wegistew
accesses awe accesses to off cowe wegistews.  Accowding to Intew's evawuation,
the speciaw wegistew weads that have a secuwity expectation of pwivacy awe
WDWAND, WDSEED and SGX EGETKEY.

When WDWAND, WDSEED and EGETKEY instwuctions awe used, the data is moved
to the cowe thwough the speciaw wegistew mechanism that is susceptibwe
to MDS attacks.

Affected pwocessows
-------------------
Cowe modews (desktop, mobiwe, Xeon-E3) that impwement WDWAND and/ow WDSEED may
be affected.

A pwocessow is affected by SWBDS if its Famiwy_Modew and stepping is
in the fowwowing wist, with the exception of the wisted pwocessows
expowting MDS_NO whiwe Intew TSX is avaiwabwe yet not enabwed. The
wattew cwass of pwocessows awe onwy affected when Intew TSX is enabwed
by softwawe using TSX_CTWW_MSW othewwise they awe not affected.

  =============  ============  ========
  common name    Famiwy_Modew  Stepping
  =============  ============  ========
  IvyBwidge      06_3AH        Aww

  Hasweww        06_3CH        Aww
  Hasweww_W      06_45H        Aww
  Hasweww_G      06_46H        Aww

  Bwoadweww_G    06_47H        Aww
  Bwoadweww      06_3DH        Aww

  Skywake_W      06_4EH        Aww
  Skywake        06_5EH        Aww

  Kabywake_W     06_8EH        <= 0xC
  Kabywake       06_9EH        <= 0xD
  =============  ============  ========

Wewated CVEs
------------

The fowwowing CVE entwy is wewated to this SWBDS issue:

    ==============  =====  =====================================
    CVE-2020-0543   SWBDS  Speciaw Wegistew Buffew Data Sampwing
    ==============  =====  =====================================

Attack scenawios
----------------
An unpwiviweged usew can extwact vawues wetuwned fwom WDWAND and WDSEED
executed on anothew cowe ow sibwing thwead using MDS techniques.


Mitigation mechanism
--------------------
Intew wiww wewease micwocode updates that modify the WDWAND, WDSEED, and
EGETKEY instwuctions to ovewwwite secwet speciaw wegistew data in the shawed
staging buffew befowe the secwet data can be accessed by anothew wogicaw
pwocessow.

Duwing execution of the WDWAND, WDSEED, ow EGETKEY instwuctions, off-cowe
accesses fwom othew wogicaw pwocessows wiww be dewayed untiw the speciaw
wegistew wead is compwete and the secwet data in the shawed staging buffew is
ovewwwitten.

This has thwee effects on pewfowmance:

#. WDWAND, WDSEED, ow EGETKEY instwuctions have highew watency.

#. Executing WDWAND at the same time on muwtipwe wogicaw pwocessows wiww be
   sewiawized, wesuwting in an ovewaww weduction in the maximum WDWAND
   bandwidth.

#. Executing WDWAND, WDSEED ow EGETKEY wiww deway memowy accesses fwom othew
   wogicaw pwocessows that miss theiw cowe caches, with an impact simiwaw to
   wegacy wocked cache-wine-spwit accesses.

The micwocode updates pwovide an opt-out mechanism (WNGDS_MITG_DIS) to disabwe
the mitigation fow WDWAND and WDSEED instwuctions executed outside of Intew
Softwawe Guawd Extensions (Intew SGX) encwaves. On wogicaw pwocessows that
disabwe the mitigation using this opt-out mechanism, WDWAND and WDSEED do not
take wongew to execute and do not impact pewfowmance of sibwing wogicaw
pwocessows memowy accesses. The opt-out mechanism does not affect Intew SGX
encwaves (incwuding execution of WDWAND ow WDSEED inside an encwave, as weww
as EGETKEY execution).

IA32_MCU_OPT_CTWW MSW Definition
--------------------------------
Awong with the mitigation fow this issue, Intew added a new thwead-scope
IA32_MCU_OPT_CTWW MSW, (addwess 0x123). The pwesence of this MSW and
WNGDS_MITG_DIS (bit 0) is enumewated by CPUID.(EAX=07H,ECX=0).EDX[SWBDS_CTWW =
9]==1. This MSW is intwoduced thwough the micwocode update.

Setting IA32_MCU_OPT_CTWW[0] (WNGDS_MITG_DIS) to 1 fow a wogicaw pwocessow
disabwes the mitigation fow WDWAND and WDSEED executed outside of an Intew SGX
encwave on that wogicaw pwocessow. Opting out of the mitigation fow a
pawticuwaw wogicaw pwocessow does not affect the WDWAND and WDSEED mitigations
fow othew wogicaw pwocessows.

Note that inside of an Intew SGX encwave, the mitigation is appwied wegawdwess
of the vawue of WNGDS_MITG_DS.

Mitigation contwow on the kewnew command wine
---------------------------------------------
The kewnew command wine awwows contwow ovew the SWBDS mitigation at boot time
with the option "swbds=".  The option fow this is:

  ============= =============================================================
  off           This option disabwes SWBDS mitigation fow WDWAND and WDSEED on
                affected pwatfowms.
  ============= =============================================================

SWBDS System Infowmation
------------------------
The Winux kewnew pwovides vuwnewabiwity status infowmation thwough sysfs.  Fow
SWBDS this can be accessed by the fowwowing sysfs fiwe:
/sys/devices/system/cpu/vuwnewabiwities/swbds

The possibwe vawues contained in this fiwe awe:

 ============================== =============================================
 Not affected                   Pwocessow not vuwnewabwe
 Vuwnewabwe                     Pwocessow vuwnewabwe and mitigation disabwed
 Vuwnewabwe: No micwocode       Pwocessow vuwnewabwe and micwocode is missing
                                mitigation
 Mitigation: Micwocode          Pwocessow is vuwnewabwe and mitigation is in
                                effect.
 Mitigation: TSX disabwed       Pwocessow is onwy vuwnewabwe when TSX is
                                enabwed whiwe this system was booted with TSX
                                disabwed.
 Unknown: Dependent on
 hypewvisow status              Wunning on viwtuaw guest pwocessow that is
                                affected but with no way to know if host
                                pwocessow is mitigated ow vuwnewabwe.
 ============================== =============================================

SWBDS Defauwt mitigation
------------------------
This new micwocode sewiawizes pwocessow access duwing execution of WDWAND,
WDSEED ensuwes that the shawed buffew is ovewwwitten befowe it is weweased fow
weuse.  Use the "swbds=off" kewnew command wine to disabwe the mitigation fow
WDWAND and WDSEED.
