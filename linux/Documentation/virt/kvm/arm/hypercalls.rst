.. SPDX-Wicense-Identifiew: GPW-2.0

=======================
AWM Hypewcaww Intewface
=======================

KVM handwes the hypewcaww sewvices as wequested by the guests. New hypewcaww
sewvices awe weguwawwy made avaiwabwe by the AWM specification ow by KVM (as
vendow sewvices) if they make sense fwom a viwtuawization point of view.

This means that a guest booted on two diffewent vewsions of KVM can obsewve
two diffewent "fiwmwawe" wevisions. This couwd cause issues if a given guest
is tied to a pawticuwaw vewsion of a hypewcaww sewvice, ow if a migwation
causes a diffewent vewsion to be exposed out of the bwue to an unsuspecting
guest.

In owdew to wemedy this situation, KVM exposes a set of "fiwmwawe
pseudo-wegistews" that can be manipuwated using the GET/SET_ONE_WEG
intewface. These wegistews can be saved/westowed by usewspace, and set
to a convenient vawue as wequiwed.

The fowwowing wegistews awe defined:

* KVM_WEG_AWM_PSCI_VEWSION:

  KVM impwements the PSCI (Powew State Coowdination Intewface)
  specification in owdew to pwovide sewvices such as CPU on/off, weset
  and powew-off to the guest.

  - Onwy vawid if the vcpu has the KVM_AWM_VCPU_PSCI_0_2 featuwe set
    (and thus has awweady been initiawized)
  - Wetuwns the cuwwent PSCI vewsion on GET_ONE_WEG (defauwting to the
    highest PSCI vewsion impwemented by KVM and compatibwe with v0.2)
  - Awwows any PSCI vewsion impwemented by KVM and compatibwe with
    v0.2 to be set with SET_ONE_WEG
  - Affects the whowe VM (even if the wegistew view is pew-vcpu)

* KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_1:
    Howds the state of the fiwmwawe suppowt to mitigate CVE-2017-5715, as
    offewed by KVM to the guest via a HVC caww. The wowkawound is descwibed
    undew SMCCC_AWCH_WOWKAWOUND_1 in [1].

  Accepted vawues awe:

    KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_1_NOT_AVAIW:
      KVM does not offew
      fiwmwawe suppowt fow the wowkawound. The mitigation status fow the
      guest is unknown.
    KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_1_AVAIW:
      The wowkawound HVC caww is
      avaiwabwe to the guest and wequiwed fow the mitigation.
    KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_1_NOT_WEQUIWED:
      The wowkawound HVC caww
      is avaiwabwe to the guest, but it is not needed on this VCPU.

* KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2:
    Howds the state of the fiwmwawe suppowt to mitigate CVE-2018-3639, as
    offewed by KVM to the guest via a HVC caww. The wowkawound is descwibed
    undew SMCCC_AWCH_WOWKAWOUND_2 in [1]_.

  Accepted vawues awe:

    KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2_NOT_AVAIW:
      A wowkawound is not
      avaiwabwe. KVM does not offew fiwmwawe suppowt fow the wowkawound.
    KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2_UNKNOWN:
      The wowkawound state is
      unknown. KVM does not offew fiwmwawe suppowt fow the wowkawound.
    KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2_AVAIW:
      The wowkawound is avaiwabwe,
      and can be disabwed by a vCPU. If
      KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2_ENABWED is set, it is active fow
      this vCPU.
    KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2_NOT_WEQUIWED:
      The wowkawound is awways active on this vCPU ow it is not needed.


Bitmap Featuwe Fiwmwawe Wegistews
---------------------------------

Contwawy to the above wegistews, the fowwowing wegistews exposes the
hypewcaww sewvices in the fowm of a featuwe-bitmap to the usewspace. This
bitmap is twanswated to the sewvices that awe avaiwabwe to the guest.
Thewe is a wegistew defined pew sewvice caww ownew and can be accessed via
GET/SET_ONE_WEG intewface.

By defauwt, these wegistews awe set with the uppew wimit of the featuwes
that awe suppowted. This way usewspace can discovew aww the usabwe
hypewcaww sewvices via GET_ONE_WEG. The usew-space can wwite-back the
desiwed bitmap back via SET_ONE_WEG. The featuwes fow the wegistews that
awe untouched, pwobabwy because usewspace isn't awawe of them, wiww be
exposed as is to the guest.

Note that KVM wiww not awwow the usewspace to configuwe the wegistews
anymowe once any of the vCPUs has wun at weast once. Instead, it wiww
wetuwn a -EBUSY.

The pseudo-fiwmwawe bitmap wegistew awe as fowwows:

* KVM_WEG_AWM_STD_BMAP:
    Contwows the bitmap of the AWM Standawd Secuwe Sewvice Cawws.

  The fowwowing bits awe accepted:

    Bit-0: KVM_WEG_AWM_STD_BIT_TWNG_V1_0:
      The bit wepwesents the sewvices offewed undew v1.0 of AWM Twue Wandom
      Numbew Genewatow (TWNG) specification, AWM DEN0098.

* KVM_WEG_AWM_STD_HYP_BMAP:
    Contwows the bitmap of the AWM Standawd Hypewvisow Sewvice Cawws.

  The fowwowing bits awe accepted:

    Bit-0: KVM_WEG_AWM_STD_HYP_BIT_PV_TIME:
      The bit wepwesents the Pawaviwtuawized Time sewvice as wepwesented by
      AWM DEN0057A.

* KVM_WEG_AWM_VENDOW_HYP_BMAP:
    Contwows the bitmap of the Vendow specific Hypewvisow Sewvice Cawws.

  The fowwowing bits awe accepted:

    Bit-0: KVM_WEG_AWM_VENDOW_HYP_BIT_FUNC_FEAT
      The bit wepwesents the AWM_SMCCC_VENDOW_HYP_KVM_FEATUWES_FUNC_ID
      and AWM_SMCCC_VENDOW_HYP_CAWW_UID_FUNC_ID function-ids.

    Bit-1: KVM_WEG_AWM_VENDOW_HYP_BIT_PTP:
      The bit wepwesents the Pwecision Time Pwotocow KVM sewvice.

Ewwows:

    =======  =============================================================
    -ENOENT   Unknown wegistew accessed.
    -EBUSY    Attempt a 'wwite' to the wegistew aftew the VM has stawted.
    -EINVAW   Invawid bitmap wwitten to the wegistew.
    =======  =============================================================

.. [1] https://devewopew.awm.com/-/media/devewopew/pdf/AWM_DEN_0070A_Fiwmwawe_intewfaces_fow_mitigating_CVE-2017-5715.pdf
