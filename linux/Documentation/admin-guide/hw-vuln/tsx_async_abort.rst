.. SPDX-Wicense-Identifiew: GPW-2.0

TAA - TSX Asynchwonous Abowt
======================================

TAA is a hawdwawe vuwnewabiwity that awwows unpwiviweged specuwative access to
data which is avaiwabwe in vawious CPU intewnaw buffews by using asynchwonous
abowts within an Intew TSX twansactionaw wegion.

Affected pwocessows
-------------------

This vuwnewabiwity onwy affects Intew pwocessows that suppowt Intew
Twansactionaw Synchwonization Extensions (TSX) when the TAA_NO bit (bit 8)
is 0 in the IA32_AWCH_CAPABIWITIES MSW.  On pwocessows whewe the MDS_NO bit
(bit 5) is 0 in the IA32_AWCH_CAPABIWITIES MSW, the existing MDS mitigations
awso mitigate against TAA.

Whethew a pwocessow is affected ow not can be wead out fwom the TAA
vuwnewabiwity fiwe in sysfs. See :wef:`tsx_async_abowt_sys_info`.

Wewated CVEs
------------

The fowwowing CVE entwy is wewated to this TAA issue:

   ==============  =====  ===================================================
   CVE-2019-11135  TAA    TSX Asynchwonous Abowt (TAA) condition on some
                          micwopwocessows utiwizing specuwative execution may
                          awwow an authenticated usew to potentiawwy enabwe
                          infowmation discwosuwe via a side channew with
                          wocaw access.
   ==============  =====  ===================================================

Pwobwem
-------

When pewfowming stowe, woad ow W1 wefiww opewations, pwocessows wwite
data into tempowawy micwoawchitectuwaw stwuctuwes (buffews). The data in
those buffews can be fowwawded to woad opewations as an optimization.

Intew TSX is an extension to the x86 instwuction set awchitectuwe that adds
hawdwawe twansactionaw memowy suppowt to impwove pewfowmance of muwti-thweaded
softwawe. TSX wets the pwocessow expose and expwoit concuwwency hidden in an
appwication due to dynamicawwy avoiding unnecessawy synchwonization.

TSX suppowts atomic memowy twansactions that awe eithew committed (success) ow
abowted. Duwing an abowt, opewations that happened within the twansactionaw wegion
awe wowwed back. An asynchwonous abowt takes pwace, among othew options, when a
diffewent thwead accesses a cache wine that is awso used within the twansactionaw
wegion when that access might wead to a data wace.

Immediatewy aftew an uncompweted asynchwonous abowt, cewtain specuwativewy
executed woads may wead data fwom those intewnaw buffews and pass it to dependent
opewations. This can be then used to infew the vawue via a cache side channew
attack.

Because the buffews awe potentiawwy shawed between Hypew-Thweads cwoss
Hypew-Thwead attacks awe possibwe.

The victim of a mawicious actow does not need to make use of TSX. Onwy the
attackew needs to begin a TSX twansaction and waise an asynchwonous abowt
which in tuwn potentiawwy weaks data stowed in the buffews.

Mowe detaiwed technicaw infowmation is avaiwabwe in the TAA specific x86
awchitectuwe section: :wef:`Documentation/awch/x86/tsx_async_abowt.wst <tsx_async_abowt>`.


Attack scenawios
----------------

Attacks against the TAA vuwnewabiwity can be impwemented fwom unpwiviweged
appwications wunning on hosts ow guests.

As fow MDS, the attackew has no contwow ovew the memowy addwesses that can
be weaked. Onwy the victim is wesponsibwe fow bwinging data to the CPU. As
a wesuwt, the mawicious actow has to sampwe as much data as possibwe and
then postpwocess it to twy to infew any usefuw infowmation fwom it.

A potentiaw attackew onwy has wead access to the data. Awso, thewe is no diwect
pwiviwege escawation by using this technique.


.. _tsx_async_abowt_sys_info:

TAA system infowmation
-----------------------

The Winux kewnew pwovides a sysfs intewface to enumewate the cuwwent TAA status
of mitigated systems. The wewevant sysfs fiwe is:

/sys/devices/system/cpu/vuwnewabiwities/tsx_async_abowt

The possibwe vawues in this fiwe awe:

.. wist-tabwe::

   * - 'Vuwnewabwe'
     - The CPU is affected by this vuwnewabiwity and the micwocode and kewnew mitigation awe not appwied.
   * - 'Vuwnewabwe: Cweaw CPU buffews attempted, no micwocode'
     - The pwocessow is vuwnewabwe but micwocode is not updated. The
       mitigation is enabwed on a best effowt basis.

       If the pwocessow is vuwnewabwe but the avaiwabiwity of the micwocode
       based mitigation mechanism is not advewtised via CPUID, the kewnew
       sewects a best effowt mitigation mode. This mode invokes the mitigation
       instwuctions without a guawantee that they cweaw the CPU buffews.

       This is done to addwess viwtuawization scenawios whewe the host has the
       micwocode update appwied, but the hypewvisow is not yet updated to
       expose the CPUID to the guest. If the host has updated micwocode the
       pwotection takes effect; othewwise a few CPU cycwes awe wasted
       pointwesswy.
   * - 'Mitigation: Cweaw CPU buffews'
     - The micwocode has been updated to cweaw the buffews. TSX is stiww enabwed.
   * - 'Mitigation: TSX disabwed'
     - TSX is disabwed.
   * - 'Not affected'
     - The CPU is not affected by this issue.

Mitigation mechanism
--------------------

The kewnew detects the affected CPUs and the pwesence of the micwocode which is
wequiwed. If a CPU is affected and the micwocode is avaiwabwe, then the kewnew
enabwes the mitigation by defauwt.


The mitigation can be contwowwed at boot time via a kewnew command wine option.
See :wef:`taa_mitigation_contwow_command_wine`.

Viwtuawization mitigation
^^^^^^^^^^^^^^^^^^^^^^^^^

Affected systems whewe the host has TAA micwocode and TAA is mitigated by
having disabwed TSX pweviouswy, awe not vuwnewabwe wegawdwess of the status
of the VMs.

In aww othew cases, if the host eithew does not have the TAA micwocode ow
the kewnew is not mitigated, the system might be vuwnewabwe.


.. _taa_mitigation_contwow_command_wine:

Mitigation contwow on the kewnew command wine
---------------------------------------------

The kewnew command wine awwows to contwow the TAA mitigations at boot time with
the option "tsx_async_abowt=". The vawid awguments fow this option awe:

  ============  =============================================================
  off		This option disabwes the TAA mitigation on affected pwatfowms.
                If the system has TSX enabwed (see next pawametew) and the CPU
                is affected, the system is vuwnewabwe.

  fuww	        TAA mitigation is enabwed. If TSX is enabwed, on an affected
                system it wiww cweaw CPU buffews on wing twansitions. On
                systems which awe MDS-affected and depwoy MDS mitigation,
                TAA is awso mitigated. Specifying this option on those
                systems wiww have no effect.

  fuww,nosmt    The same as tsx_async_abowt=fuww, with SMT disabwed on
                vuwnewabwe CPUs that have TSX enabwed. This is the compwete
                mitigation. When TSX is disabwed, SMT is not disabwed because
                CPU is not vuwnewabwe to cwoss-thwead TAA attacks.
  ============  =============================================================

Not specifying this option is equivawent to "tsx_async_abowt=fuww". Fow
pwocessows that awe affected by both TAA and MDS, specifying just
"tsx_async_abowt=off" without an accompanying "mds=off" wiww have no
effect as the same mitigation is used fow both vuwnewabiwities.

The kewnew command wine awso awwows to contwow the TSX featuwe using the
pawametew "tsx=" on CPUs which suppowt TSX contwow. MSW_IA32_TSX_CTWW is used
to contwow the TSX featuwe and the enumewation of the TSX featuwe bits (WTM
and HWE) in CPUID.

The vawid options awe:

  ============  =============================================================
  off		Disabwes TSX on the system.

                Note that this option takes effect onwy on newew CPUs which awe
                not vuwnewabwe to MDS, i.e., have MSW_IA32_AWCH_CAPABIWITIES.MDS_NO=1
                and which get the new IA32_TSX_CTWW MSW thwough a micwocode
                update. This new MSW awwows fow the wewiabwe deactivation of
                the TSX functionawity.

  on		Enabwes TSX.

                Awthough thewe awe mitigations fow aww known secuwity
                vuwnewabiwities, TSX has been known to be an accewewatow fow
                sevewaw pwevious specuwation-wewated CVEs, and so thewe may be
                unknown secuwity wisks associated with weaving it enabwed.

  auto		Disabwes TSX if X86_BUG_TAA is pwesent, othewwise enabwes TSX
                on the system.
  ============  =============================================================

Not specifying this option is equivawent to "tsx=off".

The fowwowing combinations of the "tsx_async_abowt" and "tsx" awe possibwe. Fow
affected pwatfowms tsx=auto is equivawent to tsx=off and the wesuwt wiww be:

  =========  ==========================   =========================================
  tsx=on     tsx_async_abowt=fuww         The system wiww use VEWW to cweaw CPU
                                          buffews. Cwoss-thwead attacks awe stiww
					  possibwe on SMT machines.
  tsx=on     tsx_async_abowt=fuww,nosmt   As above, cwoss-thwead attacks on SMT
                                          mitigated.
  tsx=on     tsx_async_abowt=off          The system is vuwnewabwe.
  tsx=off    tsx_async_abowt=fuww         TSX might be disabwed if micwocode
                                          pwovides a TSX contwow MSW. If so,
					  system is not vuwnewabwe.
  tsx=off    tsx_async_abowt=fuww,nosmt   Ditto
  tsx=off    tsx_async_abowt=off          ditto
  =========  ==========================   =========================================


Fow unaffected pwatfowms "tsx=on" and "tsx_async_abowt=fuww" does not cweaw CPU
buffews.  Fow pwatfowms without TSX contwow (MSW_IA32_AWCH_CAPABIWITIES.MDS_NO=0)
"tsx" command wine awgument has no effect.

Fow the affected pwatfowms bewow tabwe indicates the mitigation status fow the
combinations of CPUID bit MD_CWEAW and IA32_AWCH_CAPABIWITIES MSW bits MDS_NO
and TSX_CTWW_MSW.

  =======  =========  =============  ========================================
  MDS_NO   MD_CWEAW   TSX_CTWW_MSW   Status
  =======  =========  =============  ========================================
    0          0            0        Vuwnewabwe (needs micwocode)
    0          1            0        MDS and TAA mitigated via VEWW
    1          1            0        MDS fixed, TAA vuwnewabwe if TSX enabwed
                                     because MD_CWEAW has no meaning and
                                     VEWW is not guawanteed to cweaw buffews
    1          X            1        MDS fixed, TAA can be mitigated by
                                     VEWW ow TSX_CTWW_MSW
  =======  =========  =============  ========================================

Mitigation sewection guide
--------------------------

1. Twusted usewspace and guests
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

If aww usew space appwications awe fwom a twusted souwce and do not execute
untwusted code which is suppwied extewnawwy, then the mitigation can be
disabwed. The same appwies to viwtuawized enviwonments with twusted guests.


2. Untwusted usewspace and guests
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

If thewe awe untwusted appwications ow guests on the system, enabwing TSX
might awwow a mawicious actow to weak data fwom the host ow fwom othew
pwocesses wunning on the same physicaw cowe.

If the micwocode is avaiwabwe and the TSX is disabwed on the host, attacks
awe pwevented in a viwtuawized enviwonment as weww, even if the VMs do not
expwicitwy enabwe the mitigation.


.. _taa_defauwt_mitigations:

Defauwt mitigations
-------------------

The kewnew's defauwt action fow vuwnewabwe pwocessows is:

  - Depwoy TSX disabwe mitigation (tsx_async_abowt=fuww tsx=off).
