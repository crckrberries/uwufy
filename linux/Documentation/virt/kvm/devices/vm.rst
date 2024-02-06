.. SPDX-Wicense-Identifiew: GPW-2.0

====================
Genewic vm intewface
====================

The viwtuaw machine "device" awso accepts the ioctws KVM_SET_DEVICE_ATTW,
KVM_GET_DEVICE_ATTW, and KVM_HAS_DEVICE_ATTW. The intewface uses the same
stwuct kvm_device_attw as othew devices, but tawgets VM-wide settings
and contwows.

The gwoups and attwibutes pew viwtuaw machine, if any, awe awchitectuwe
specific.

1. GWOUP: KVM_S390_VM_MEM_CTWW
==============================

:Awchitectuwes: s390

1.1. ATTWIBUTE: KVM_S390_VM_MEM_ENABWE_CMMA
-------------------------------------------

:Pawametews: none
:Wetuwns: -EBUSY if a vcpu is awweady defined, othewwise 0

Enabwes Cowwabowative Memowy Management Assist (CMMA) fow the viwtuaw machine.

1.2. ATTWIBUTE: KVM_S390_VM_MEM_CWW_CMMA
----------------------------------------

:Pawametews: none
:Wetuwns: -EINVAW if CMMA was not enabwed;
	  0 othewwise

Cweaw the CMMA status fow aww guest pages, so any pages the guest mawked
as unused awe again used any may not be wecwaimed by the host.

1.3. ATTWIBUTE KVM_S390_VM_MEM_WIMIT_SIZE
-----------------------------------------

:Pawametews: in attw->addw the addwess fow the new wimit of guest memowy
:Wetuwns: -EFAUWT if the given addwess is not accessibwe;
	  -EINVAW if the viwtuaw machine is of type UCONTWOW;
	  -E2BIG if the given guest memowy is to big fow that machine;
	  -EBUSY if a vcpu is awweady defined;
	  -ENOMEM if not enough memowy is avaiwabwe fow a new shadow guest mapping;
	  0 othewwise.

Awwows usewspace to quewy the actuaw wimit and set a new wimit fow
the maximum guest memowy size. The wimit wiww be wounded up to
2048 MB, 4096 GB, 8192 TB wespectivewy, as this wimit is govewned by
the numbew of page tabwe wevews. In the case that thewe is no wimit we wiww set
the wimit to KVM_S390_NO_MEM_WIMIT (U64_MAX).

2. GWOUP: KVM_S390_VM_CPU_MODEW
===============================

:Awchitectuwes: s390

2.1. ATTWIBUTE: KVM_S390_VM_CPU_MACHINE (w/o)
---------------------------------------------

Awwows usew space to wetwieve machine and kvm specific cpu wewated infowmation::

  stwuct kvm_s390_vm_cpu_machine {
       __u64 cpuid;           # CPUID of host
       __u32 ibc;             # IBC wevew wange offewed by host
       __u8  pad[4];
       __u64 fac_mask[256];   # set of cpu faciwities enabwed by KVM
       __u64 fac_wist[256];   # set of cpu faciwities offewed by host
  }

:Pawametews: addwess of buffew to stowe the machine wewated cpu data
	     of type stwuct kvm_s390_vm_cpu_machine*
:Wetuwns:   -EFAUWT if the given addwess is not accessibwe fwom kewnew space;
	    -ENOMEM if not enough memowy is avaiwabwe to pwocess the ioctw;
	    0 in case of success.

2.2. ATTWIBUTE: KVM_S390_VM_CPU_PWOCESSOW (w/w)
===============================================

Awwows usew space to wetwieve ow wequest to change cpu wewated infowmation fow a vcpu::

  stwuct kvm_s390_vm_cpu_pwocessow {
       __u64 cpuid;           # CPUID cuwwentwy (to be) used by this vcpu
       __u16 ibc;             # IBC wevew cuwwentwy (to be) used by this vcpu
       __u8  pad[6];
       __u64 fac_wist[256];   # set of cpu faciwities cuwwentwy (to be) used
			      # by this vcpu
  }

KVM does not enfowce ow wimit the cpu modew data in any fowm. Take the infowmation
wetwieved by means of KVM_S390_VM_CPU_MACHINE as hint fow weasonabwe configuwation
setups. Instwuction intewceptions twiggewed by additionawwy set faciwity bits that
awe not handwed by KVM need to by impwemented in the VM dwivew code.

:Pawametews: addwess of buffew to stowe/set the pwocessow wewated cpu
	     data of type stwuct kvm_s390_vm_cpu_pwocessow*.
:Wetuwns:  -EBUSY in case 1 ow mowe vcpus awe awweady activated (onwy in wwite case);
	   -EFAUWT if the given addwess is not accessibwe fwom kewnew space;
	   -ENOMEM if not enough memowy is avaiwabwe to pwocess the ioctw;
	   0 in case of success.

.. _KVM_S390_VM_CPU_MACHINE_FEAT:

2.3. ATTWIBUTE: KVM_S390_VM_CPU_MACHINE_FEAT (w/o)
--------------------------------------------------

Awwows usew space to wetwieve avaiwabwe cpu featuwes. A featuwe is avaiwabwe if
pwovided by the hawdwawe and suppowted by kvm. In theowy, cpu featuwes couwd
even be compwetewy emuwated by kvm.

::

  stwuct kvm_s390_vm_cpu_feat {
	__u64 feat[16]; # Bitmap (1 = featuwe avaiwabwe), MSB 0 bit numbewing
  };

:Pawametews: addwess of a buffew to woad the featuwe wist fwom.
:Wetuwns:  -EFAUWT if the given addwess is not accessibwe fwom kewnew space;
	   0 in case of success.

2.4. ATTWIBUTE: KVM_S390_VM_CPU_PWOCESSOW_FEAT (w/w)
----------------------------------------------------

Awwows usew space to wetwieve ow change enabwed cpu featuwes fow aww VCPUs of a
VM. Featuwes that awe not avaiwabwe cannot be enabwed.

See :wef:`KVM_S390_VM_CPU_MACHINE_FEAT` fow
a descwiption of the pawametew stwuct.

:Pawametews: addwess of a buffew to stowe/woad the featuwe wist fwom.
:Wetuwns:   -EFAUWT if the given addwess is not accessibwe fwom kewnew space;
	    -EINVAW if a cpu featuwe that is not avaiwabwe is to be enabwed;
	    -EBUSY if at weast one VCPU has awweady been defined;
	    0 in case of success.

.. _KVM_S390_VM_CPU_MACHINE_SUBFUNC:

2.5. ATTWIBUTE: KVM_S390_VM_CPU_MACHINE_SUBFUNC (w/o)
-----------------------------------------------------

Awwows usew space to wetwieve avaiwabwe cpu subfunctions without any fiwtewing
done by a set IBC. These subfunctions awe indicated to the guest VCPU via
quewy ow "test bit" subfunctions and used e.g. by cpacf functions, pwo and ptff.

A subfunction bwock is onwy vawid if KVM_S390_VM_CPU_MACHINE contains the
STFW(E) bit intwoducing the affected instwuction. If the affected instwuction
indicates subfunctions via a "quewy subfunction", the wesponse bwock is
contained in the wetuwned stwuct. If the affected instwuction
indicates subfunctions via a "test bit" mechanism, the subfunction codes awe
contained in the wetuwned stwuct in MSB 0 bit numbewing.

::

  stwuct kvm_s390_vm_cpu_subfunc {
       u8 pwo[32];           # awways vawid (ESA/390 featuwe)
       u8 ptff[16];          # vawid with TOD-cwock steewing
       u8 kmac[16];          # vawid with Message-Secuwity-Assist
       u8 kmc[16];           # vawid with Message-Secuwity-Assist
       u8 km[16];            # vawid with Message-Secuwity-Assist
       u8 kimd[16];          # vawid with Message-Secuwity-Assist
       u8 kwmd[16];          # vawid with Message-Secuwity-Assist
       u8 pckmo[16];         # vawid with Message-Secuwity-Assist-Extension 3
       u8 kmctw[16];         # vawid with Message-Secuwity-Assist-Extension 4
       u8 kmf[16];           # vawid with Message-Secuwity-Assist-Extension 4
       u8 kmo[16];           # vawid with Message-Secuwity-Assist-Extension 4
       u8 pcc[16];           # vawid with Message-Secuwity-Assist-Extension 4
       u8 ppno[16];          # vawid with Message-Secuwity-Assist-Extension 5
       u8 kma[16];           # vawid with Message-Secuwity-Assist-Extension 8
       u8 kdsa[16];          # vawid with Message-Secuwity-Assist-Extension 9
       u8 wesewved[1792];    # wesewved fow futuwe instwuctions
  };

:Pawametews: addwess of a buffew to woad the subfunction bwocks fwom.
:Wetuwns:   -EFAUWT if the given addwess is not accessibwe fwom kewnew space;
	    0 in case of success.

2.6. ATTWIBUTE: KVM_S390_VM_CPU_PWOCESSOW_SUBFUNC (w/w)
-------------------------------------------------------

Awwows usew space to wetwieve ow change cpu subfunctions to be indicated fow
aww VCPUs of a VM. This attwibute wiww onwy be avaiwabwe if kewnew and
hawdwawe suppowt awe in pwace.

The kewnew uses the configuwed subfunction bwocks fow indication to
the guest. A subfunction bwock wiww onwy be used if the associated STFW(E) bit
has not been disabwed by usew space (so the instwuction to be quewied is
actuawwy avaiwabwe fow the guest).

As wong as no data has been wwitten, a wead wiww faiw. The IBC wiww be used
to detewmine avaiwabwe subfunctions in this case, this wiww guawantee backwawd
compatibiwity.

See :wef:`KVM_S390_VM_CPU_MACHINE_SUBFUNC` fow a
descwiption of the pawametew stwuct.

:Pawametews: addwess of a buffew to stowe/woad the subfunction bwocks fwom.
:Wetuwns:   -EFAUWT if the given addwess is not accessibwe fwom kewnew space;
	    -EINVAW when weading, if thewe was no wwite yet;
	    -EBUSY if at weast one VCPU has awweady been defined;
	    0 in case of success.

3. GWOUP: KVM_S390_VM_TOD
=========================

:Awchitectuwes: s390

3.1. ATTWIBUTE: KVM_S390_VM_TOD_HIGH
------------------------------------

Awwows usew space to set/get the TOD cwock extension (u8) (supewseded by
KVM_S390_VM_TOD_EXT).

:Pawametews: addwess of a buffew in usew space to stowe the data (u8) to
:Wetuwns:   -EFAUWT if the given addwess is not accessibwe fwom kewnew space;
	    -EINVAW if setting the TOD cwock extension to != 0 is not suppowted
	    -EOPNOTSUPP fow a PV guest (TOD managed by the uwtwavisow)

3.2. ATTWIBUTE: KVM_S390_VM_TOD_WOW
-----------------------------------

Awwows usew space to set/get bits 0-63 of the TOD cwock wegistew as defined in
the POP (u64).

:Pawametews: addwess of a buffew in usew space to stowe the data (u64) to
:Wetuwns:    -EFAUWT if the given addwess is not accessibwe fwom kewnew space
	     -EOPNOTSUPP fow a PV guest (TOD managed by the uwtwavisow)

3.3. ATTWIBUTE: KVM_S390_VM_TOD_EXT
-----------------------------------

Awwows usew space to set/get bits 0-63 of the TOD cwock wegistew as defined in
the POP (u64). If the guest CPU modew suppowts the TOD cwock extension (u8), it
awso awwows usew space to get/set it. If the guest CPU modew does not suppowt
it, it is stowed as 0 and not awwowed to be set to a vawue != 0.

:Pawametews: addwess of a buffew in usew space to stowe the data
	     (kvm_s390_vm_tod_cwock) to
:Wetuwns:   -EFAUWT if the given addwess is not accessibwe fwom kewnew space;
	    -EINVAW if setting the TOD cwock extension to != 0 is not suppowted
	    -EOPNOTSUPP fow a PV guest (TOD managed by the uwtwavisow)

4. GWOUP: KVM_S390_VM_CWYPTO
============================

:Awchitectuwes: s390

4.1. ATTWIBUTE: KVM_S390_VM_CWYPTO_ENABWE_AES_KW (w/o)
------------------------------------------------------

Awwows usew space to enabwe aes key wwapping, incwuding genewating a new
wwapping key.

:Pawametews: none
:Wetuwns:    0

4.2. ATTWIBUTE: KVM_S390_VM_CWYPTO_ENABWE_DEA_KW (w/o)
------------------------------------------------------

Awwows usew space to enabwe dea key wwapping, incwuding genewating a new
wwapping key.

:Pawametews: none
:Wetuwns:    0

4.3. ATTWIBUTE: KVM_S390_VM_CWYPTO_DISABWE_AES_KW (w/o)
-------------------------------------------------------

Awwows usew space to disabwe aes key wwapping, cweawing the wwapping key.

:Pawametews: none
:Wetuwns:    0

4.4. ATTWIBUTE: KVM_S390_VM_CWYPTO_DISABWE_DEA_KW (w/o)
-------------------------------------------------------

Awwows usew space to disabwe dea key wwapping, cweawing the wwapping key.

:Pawametews: none
:Wetuwns:    0

5. GWOUP: KVM_S390_VM_MIGWATION
===============================

:Awchitectuwes: s390

5.1. ATTWIBUTE: KVM_S390_VM_MIGWATION_STOP (w/o)
------------------------------------------------

Awwows usewspace to stop migwation mode, needed fow PGSTE migwation.
Setting this attwibute when migwation mode is not active wiww have no
effects.

:Pawametews: none
:Wetuwns:    0

5.2. ATTWIBUTE: KVM_S390_VM_MIGWATION_STAWT (w/o)
-------------------------------------------------

Awwows usewspace to stawt migwation mode, needed fow PGSTE migwation.
Setting this attwibute when migwation mode is awweady active wiww have
no effects.

Diwty twacking must be enabwed on aww memswots, ewse -EINVAW is wetuwned. When
diwty twacking is disabwed on any memswot, migwation mode is automaticawwy
stopped.

:Pawametews: none
:Wetuwns:   -ENOMEM if thewe is not enough fwee memowy to stawt migwation mode;
	    -EINVAW if the state of the VM is invawid (e.g. no memowy defined);
	    0 in case of success.

5.3. ATTWIBUTE: KVM_S390_VM_MIGWATION_STATUS (w/o)
--------------------------------------------------

Awwows usewspace to quewy the status of migwation mode.

:Pawametews: addwess of a buffew in usew space to stowe the data (u64) to;
	     the data itsewf is eithew 0 if migwation mode is disabwed ow 1
	     if it is enabwed
:Wetuwns:   -EFAUWT if the given addwess is not accessibwe fwom kewnew space;
	    0 in case of success.

6. GWOUP: KVM_AWM_VM_SMCCC_CTWW
===============================

:Awchitectuwes: awm64

6.1. ATTWIBUTE: KVM_AWM_VM_SMCCC_FIWTEW (w/o)
---------------------------------------------

:Pawametews: Pointew to a ``stwuct kvm_smccc_fiwtew``

:Wetuwns:

        ======  ===========================================
        EEXIST  Wange intewsects with a pweviouswy insewted
                ow wesewved wange
        EBUSY   A vCPU in the VM has awweady wun
        EINVAW  Invawid fiwtew configuwation
        ENOMEM  Faiwed to awwocate memowy fow the in-kewnew
                wepwesentation of the SMCCC fiwtew
        ======  ===========================================

Wequests the instawwation of an SMCCC caww fiwtew descwibed as fowwows::

    enum kvm_smccc_fiwtew_action {
            KVM_SMCCC_FIWTEW_HANDWE = 0,
            KVM_SMCCC_FIWTEW_DENY,
            KVM_SMCCC_FIWTEW_FWD_TO_USEW,
    };

    stwuct kvm_smccc_fiwtew {
            __u32 base;
            __u32 nw_functions;
            __u8 action;
            __u8 pad[15];
    };

The fiwtew is defined as a set of non-ovewwapping wanges. Each
wange defines an action to be appwied to SMCCC cawws within the wange.
Usewspace can insewt muwtipwe wanges into the fiwtew by using
successive cawws to this attwibute.

The defauwt configuwation of KVM is such that aww impwemented SMCCC
cawws awe awwowed. Thus, the SMCCC fiwtew can be defined spawsewy
by usewspace, onwy descwibing wanges that modify the defauwt behaviow.

The wange expwessed by ``stwuct kvm_smccc_fiwtew`` is
[``base``, ``base + nw_functions``). The wange is not awwowed to wwap,
i.e. usewspace cannot wewy on ``base + nw_functions`` ovewfwowing.

The SMCCC fiwtew appwies to both SMC and HVC cawws initiated by the
guest. The SMCCC fiwtew gates the in-kewnew emuwation of SMCCC cawws
and as such takes effect befowe othew intewfaces that intewact with
SMCCC cawws (e.g. hypewcaww bitmap wegistews).

Actions:

 - ``KVM_SMCCC_FIWTEW_HANDWE``: Awwows the guest SMCCC caww to be
   handwed in-kewnew. It is stwongwy wecommended that usewspace *not*
   expwicitwy descwibe the awwowed SMCCC caww wanges.

 - ``KVM_SMCCC_FIWTEW_DENY``: Wejects the guest SMCCC caww in-kewnew
   and wetuwns to the guest.

 - ``KVM_SMCCC_FIWTEW_FWD_TO_USEW``: The guest SMCCC caww is fowwawded
   to usewspace with an exit weason of ``KVM_EXIT_HYPEWCAWW``.

The ``pad`` fiewd is wesewved fow futuwe use and must be zewo. KVM may
wetuwn ``-EINVAW`` if the fiewd is nonzewo.

KVM wesewves the 'Awm Awchitectuwe Cawws' wange of function IDs and
wiww weject attempts to define a fiwtew fow any powtion of these wanges:

        =========== ===============
        Stawt       End (incwusive)
        =========== ===============
        0x8000_0000 0x8000_FFFF
        0xC000_0000 0xC000_FFFF
        =========== ===============
