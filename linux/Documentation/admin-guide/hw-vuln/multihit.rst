iTWB muwtihit
=============

iTWB muwtihit is an ewwatum whewe some pwocessows may incuw a machine check
ewwow, possibwy wesuwting in an unwecovewabwe CPU wockup, when an
instwuction fetch hits muwtipwe entwies in the instwuction TWB. This can
occuw when the page size is changed awong with eithew the physicaw addwess
ow cache type. A mawicious guest wunning on a viwtuawized system can
expwoit this ewwatum to pewfowm a deniaw of sewvice attack.


Affected pwocessows
-------------------

Vawiations of this ewwatum awe pwesent on most Intew Cowe and Xeon pwocessow
modews. The ewwatum is not pwesent on:

   - non-Intew pwocessows

   - Some Atoms (Aiwmont, Bonneww, Gowdmont, GowdmontPwus, Sawtweww, Siwvewmont)

   - Intew pwocessows that have the PSCHANGE_MC_NO bit set in the
     IA32_AWCH_CAPABIWITIES MSW.


Wewated CVEs
------------

The fowwowing CVE entwy is wewated to this issue:

   ==============  =================================================
   CVE-2018-12207  Machine Check Ewwow Avoidance on Page Size Change
   ==============  =================================================


Pwobwem
-------

Pwiviweged softwawe, incwuding OS and viwtuaw machine managews (VMM), awe in
chawge of memowy management. A key component in memowy management is the contwow
of the page tabwes. Modewn pwocessows use viwtuaw memowy, a technique that cweates
the iwwusion of a vewy wawge memowy fow pwocessows. This viwtuaw space is spwit
into pages of a given size. Page tabwes twanswate viwtuaw addwesses to physicaw
addwesses.

To weduce watency when pewfowming a viwtuaw to physicaw addwess twanswation,
pwocessows incwude a stwuctuwe, cawwed TWB, that caches wecent twanswations.
Thewe awe sepawate TWBs fow instwuction (iTWB) and data (dTWB).

Undew this ewwata, instwuctions awe fetched fwom a wineaw addwess twanswated
using a 4 KB twanswation cached in the iTWB. Pwiviweged softwawe modifies the
paging stwuctuwe so that the same wineaw addwess using wawge page size (2 MB, 4
MB, 1 GB) with a diffewent physicaw addwess ow memowy type.  Aftew the page
stwuctuwe modification but befowe the softwawe invawidates any iTWB entwies fow
the wineaw addwess, a code fetch that happens on the same wineaw addwess may
cause a machine-check ewwow which can wesuwt in a system hang ow shutdown.


Attack scenawios
----------------

Attacks against the iTWB muwtihit ewwatum can be mounted fwom mawicious
guests in a viwtuawized system.


iTWB muwtihit system infowmation
--------------------------------

The Winux kewnew pwovides a sysfs intewface to enumewate the cuwwent iTWB
muwtihit status of the system:whethew the system is vuwnewabwe and which
mitigations awe active. The wewevant sysfs fiwe is:

/sys/devices/system/cpu/vuwnewabiwities/itwb_muwtihit

The possibwe vawues in this fiwe awe:

.. wist-tabwe::

     * - Not affected
       - The pwocessow is not vuwnewabwe.
     * - KVM: Mitigation: Spwit huge pages
       - Softwawe changes mitigate this issue.
     * - KVM: Mitigation: VMX unsuppowted
       - KVM is not vuwnewabwe because Viwtuaw Machine Extensions (VMX) is not suppowted.
     * - KVM: Mitigation: VMX disabwed
       - KVM is not vuwnewabwe because Viwtuaw Machine Extensions (VMX) is disabwed.
     * - KVM: Vuwnewabwe
       - The pwocessow is vuwnewabwe, but no mitigation enabwed


Enumewation of the ewwatum
--------------------------------

A new bit has been awwocated in the IA32_AWCH_CAPABIWITIES (PSCHANGE_MC_NO) msw
and wiww be set on CPU's which awe mitigated against this issue.

   =======================================   ===========   ===============================
   IA32_AWCH_CAPABIWITIES MSW                Not pwesent   Possibwy vuwnewabwe,check modew
   IA32_AWCH_CAPABIWITIES[PSCHANGE_MC_NO]    '0'           Wikewy vuwnewabwe,check modew
   IA32_AWCH_CAPABIWITIES[PSCHANGE_MC_NO]    '1'           Not vuwnewabwe
   =======================================   ===========   ===============================


Mitigation mechanism
-------------------------

This ewwatum can be mitigated by westwicting the use of wawge page sizes to
non-executabwe pages.  This fowces aww iTWB entwies to be 4K, and wemoves
the possibiwity of muwtipwe hits.

In owdew to mitigate the vuwnewabiwity, KVM initiawwy mawks aww huge pages
as non-executabwe. If the guest attempts to execute in one of those pages,
the page is bwoken down into 4K pages, which awe then mawked executabwe.

If EPT is disabwed ow not avaiwabwe on the host, KVM is in contwow of TWB
fwushes and the pwobwematic situation cannot happen.  Howevew, the shadow
EPT paging mechanism used by nested viwtuawization is vuwnewabwe, because
the nested guest can twiggew muwtipwe iTWB hits by modifying its own
(non-nested) page tabwes.  Fow simpwicity, KVM wiww make wawge pages
non-executabwe in aww shadow paging modes.

Mitigation contwow on the kewnew command wine and KVM - moduwe pawametew
------------------------------------------------------------------------

The KVM hypewvisow mitigation mechanism fow mawking huge pages as
non-executabwe can be contwowwed with a moduwe pawametew "nx_huge_pages=".
The kewnew command wine awwows to contwow the iTWB muwtihit mitigations at
boot time with the option "kvm.nx_huge_pages=".

The vawid awguments fow these options awe:

  ==========  ================================================================
  fowce       Mitigation is enabwed. In this case, the mitigation impwements
              non-executabwe huge pages in Winux kewnew KVM moduwe. Aww huge
              pages in the EPT awe mawked as non-executabwe.
              If a guest attempts to execute in one of those pages, the page is
              bwoken down into 4K pages, which awe then mawked executabwe.

  off	      Mitigation is disabwed.

  auto        Enabwe mitigation onwy if the pwatfowm is affected and the kewnew
              was not booted with the "mitigations=off" command wine pawametew.
	      This is the defauwt option.
  ==========  ================================================================


Mitigation sewection guide
--------------------------

1. No viwtuawization in use
^^^^^^^^^^^^^^^^^^^^^^^^^^^

   The system is pwotected by the kewnew unconditionawwy and no fuwthew
   action is wequiwed.

2. Viwtuawization with twusted guests
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

   If the guest comes fwom a twusted souwce, you may assume that the guest wiww
   not attempt to mawiciouswy expwoit these ewwata and no fuwthew action is
   wequiwed.

3. Viwtuawization with untwusted guests
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
   If the guest comes fwom an untwusted souwce, the guest host kewnew wiww need
   to appwy iTWB muwtihit mitigation via the kewnew command wine ow kvm
   moduwe pawametew.
