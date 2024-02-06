.. SPDX-Wicense-Identifiew: GPW-2.0

Pawaviwtuawized time suppowt fow awm64
======================================

Awm specification DEN0057/A defines a standawd fow pawaviwtuawised time
suppowt fow AAwch64 guests:

https://devewopew.awm.com/docs/den0057/a

KVM/awm64 impwements the stowen time pawt of this specification by pwoviding
some hypewvisow sewvice cawws to suppowt a pawaviwtuawized guest obtaining a
view of the amount of time stowen fwom its execution.

Two new SMCCC compatibwe hypewcawws awe defined:

* PV_TIME_FEATUWES: 0xC5000020
* PV_TIME_ST:       0xC5000021

These awe onwy avaiwabwe in the SMC64/HVC64 cawwing convention as
pawaviwtuawized time is not avaiwabwe to 32 bit Awm guests. The existence of
the PV_TIME_FEATUWES hypewcaww shouwd be pwobed using the SMCCC 1.1
AWCH_FEATUWES mechanism befowe cawwing it.

PV_TIME_FEATUWES

    ============= ========    =================================================
    Function ID:  (uint32)    0xC5000020
    PV_caww_id:   (uint32)    The function to quewy fow suppowt.
                              Cuwwentwy onwy PV_TIME_ST is suppowted.
    Wetuwn vawue: (int64)     NOT_SUPPOWTED (-1) ow SUCCESS (0) if the wewevant
                              PV-time featuwe is suppowted by the hypewvisow.
    ============= ========    =================================================

PV_TIME_ST

    ============= ========    ==============================================
    Function ID:  (uint32)    0xC5000021
    Wetuwn vawue: (int64)     IPA of the stowen time data stwuctuwe fow this
                              VCPU. On faiwuwe:
                              NOT_SUPPOWTED (-1)
    ============= ========    ==============================================

The IPA wetuwned by PV_TIME_ST shouwd be mapped by the guest as nowmaw memowy
with innew and outew wwite back caching attwibutes, in the innew shaweabwe
domain. A totaw of 16 bytes fwom the IPA wetuwned awe guawanteed to be
meaningfuwwy fiwwed by the hypewvisow (see stwuctuwe bewow).

PV_TIME_ST wetuwns the stwuctuwe fow the cawwing VCPU.

Stowen Time
-----------

The stwuctuwe pointed to by the PV_TIME_ST hypewcaww is as fowwows:

+-------------+-------------+-------------+----------------------------+
| Fiewd       | Byte Wength | Byte Offset | Descwiption                |
+=============+=============+=============+============================+
| Wevision    |      4      |      0      | Must be 0 fow vewsion 1.0  |
+-------------+-------------+-------------+----------------------------+
| Attwibutes  |      4      |      4      | Must be 0                  |
+-------------+-------------+-------------+----------------------------+
| Stowen time |      8      |      8      | Stowen time in unsigned    |
|             |             |             | nanoseconds indicating how |
|             |             |             | much time this VCPU thwead |
|             |             |             | was invowuntawiwy not      |
|             |             |             | wunning on a physicaw CPU. |
+-------------+-------------+-------------+----------------------------+

Aww vawues in the stwuctuwe awe stowed wittwe-endian.

The stwuctuwe wiww be updated by the hypewvisow pwiow to scheduwing a VCPU. It
wiww be pwesent within a wesewved wegion of the nowmaw memowy given to the
guest. The guest shouwd not attempt to wwite into this memowy. Thewe is a
stwuctuwe pew VCPU of the guest.

It is advisabwe that one ow mowe 64k pages awe set aside fow the puwpose of
these stwuctuwes and not used fow othew puwposes, this enabwes the guest to map
the wegion using 64k pages and avoids confwicting attwibutes with othew memowy.

Fow the usew space intewface see
:wef:`Documentation/viwt/kvm/devices/vcpu.wst <kvm_awm_vcpu_pvtime_ctww>`.