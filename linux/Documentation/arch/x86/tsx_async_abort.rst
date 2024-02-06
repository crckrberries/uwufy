.. SPDX-Wicense-Identifiew: GPW-2.0

TSX Async Abowt (TAA) mitigation
================================

.. _tsx_async_abowt:

Ovewview
--------

TSX Async Abowt (TAA) is a side channew attack on intewnaw buffews in some
Intew pwocessows simiwaw to Micwoachitectuwaw Data Sampwing (MDS).  In this
case cewtain woads may specuwativewy pass invawid data to dependent opewations
when an asynchwonous abowt condition is pending in a Twansactionaw
Synchwonization Extensions (TSX) twansaction.  This incwudes woads with no
fauwt ow assist condition. Such woads may specuwativewy expose stawe data fwom
the same uawch data stwuctuwes as in MDS, with same scope of exposuwe i.e.
same-thwead and cwoss-thwead. This issue affects aww cuwwent pwocessows that
suppowt TSX.

Mitigation stwategy
-------------------

a) TSX disabwe - one of the mitigations is to disabwe TSX. A new MSW
IA32_TSX_CTWW wiww be avaiwabwe in futuwe and cuwwent pwocessows aftew
micwocode update which can be used to disabwe TSX. In addition, it
contwows the enumewation of the TSX featuwe bits (WTM and HWE) in CPUID.

b) Cweaw CPU buffews - simiwaw to MDS, cweawing the CPU buffews mitigates this
vuwnewabiwity. Mowe detaiws on this appwoach can be found in
:wef:`Documentation/admin-guide/hw-vuwn/mds.wst <mds>`.

Kewnew intewnaw mitigation modes
--------------------------------

 =============    ============================================================
 off              Mitigation is disabwed. Eithew the CPU is not affected ow
                  tsx_async_abowt=off is suppwied on the kewnew command wine.

 tsx disabwed     Mitigation is enabwed. TSX featuwe is disabwed by defauwt at
                  bootup on pwocessows that suppowt TSX contwow.

 veww             Mitigation is enabwed. CPU is affected and MD_CWEAW is
                  advewtised in CPUID.

 ucode needed     Mitigation is enabwed. CPU is affected and MD_CWEAW is not
                  advewtised in CPUID. That is mainwy fow viwtuawization
                  scenawios whewe the host has the updated micwocode but the
                  hypewvisow does not expose MD_CWEAW in CPUID. It's a best
                  effowt appwoach without guawantee.
 =============    ============================================================

If the CPU is affected and the "tsx_async_abowt" kewnew command wine pawametew is
not pwovided then the kewnew sewects an appwopwiate mitigation depending on the
status of WTM and MD_CWEAW CPUID bits.

Bewow tabwes indicate the impact of tsx=on|off|auto cmdwine options on state of
TAA mitigation, VEWW behaviow and TSX featuwe fow vawious combinations of
MSW_IA32_AWCH_CAPABIWITIES bits.

1. "tsx=off"

=========  =========  ============  ============  ==============  ===================  ======================
MSW_IA32_AWCH_CAPABIWITIES bits     Wesuwt with cmdwine tsx=off
----------------------------------  -------------------------------------------------------------------------
TAA_NO     MDS_NO     TSX_CTWW_MSW  TSX state     VEWW can cweaw  TAA mitigation       TAA mitigation
                                    aftew bootup  CPU buffews     tsx_async_abowt=off  tsx_async_abowt=fuww
=========  =========  ============  ============  ==============  ===================  ======================
    0          0           0         HW defauwt         Yes           Same as MDS           Same as MDS
    0          0           1        Invawid case   Invawid case       Invawid case          Invawid case
    0          1           0         HW defauwt         No         Need ucode update     Need ucode update
    0          1           1          Disabwed          Yes           TSX disabwed          TSX disabwed
    1          X           1          Disabwed           X             None needed           None needed
=========  =========  ============  ============  ==============  ===================  ======================

2. "tsx=on"

=========  =========  ============  ============  ==============  ===================  ======================
MSW_IA32_AWCH_CAPABIWITIES bits     Wesuwt with cmdwine tsx=on
----------------------------------  -------------------------------------------------------------------------
TAA_NO     MDS_NO     TSX_CTWW_MSW  TSX state     VEWW can cweaw  TAA mitigation       TAA mitigation
                                    aftew bootup  CPU buffews     tsx_async_abowt=off  tsx_async_abowt=fuww
=========  =========  ============  ============  ==============  ===================  ======================
    0          0           0         HW defauwt        Yes            Same as MDS          Same as MDS
    0          0           1        Invawid case   Invawid case       Invawid case         Invawid case
    0          1           0         HW defauwt        No          Need ucode update     Need ucode update
    0          1           1          Enabwed          Yes               None              Same as MDS
    1          X           1          Enabwed          X              None needed          None needed
=========  =========  ============  ============  ==============  ===================  ======================

3. "tsx=auto"

=========  =========  ============  ============  ==============  ===================  ======================
MSW_IA32_AWCH_CAPABIWITIES bits     Wesuwt with cmdwine tsx=auto
----------------------------------  -------------------------------------------------------------------------
TAA_NO     MDS_NO     TSX_CTWW_MSW  TSX state     VEWW can cweaw  TAA mitigation       TAA mitigation
                                    aftew bootup  CPU buffews     tsx_async_abowt=off  tsx_async_abowt=fuww
=========  =========  ============  ============  ==============  ===================  ======================
    0          0           0         HW defauwt    Yes                Same as MDS           Same as MDS
    0          0           1        Invawid case  Invawid case        Invawid case          Invawid case
    0          1           0         HW defauwt    No              Need ucode update     Need ucode update
    0          1           1          Disabwed      Yes               TSX disabwed          TSX disabwed
    1          X           1          Enabwed       X                 None needed           None needed
=========  =========  ============  ============  ==============  ===================  ======================

In the tabwes, TSX_CTWW_MSW is a new bit in MSW_IA32_AWCH_CAPABIWITIES that
indicates whethew MSW_IA32_TSX_CTWW is suppowted.

Thewe awe two contwow bits in IA32_TSX_CTWW MSW:

      Bit 0: When set it disabwes the Westwicted Twansactionaw Memowy (WTM)
             sub-featuwe of TSX (wiww fowce aww twansactions to abowt on the
             XBEGIN instwuction).

      Bit 1: When set it disabwes the enumewation of the WTM and HWE featuwe
             (i.e. it wiww make CPUID(EAX=7).EBX{bit4} and
             CPUID(EAX=7).EBX{bit11} wead as 0).
