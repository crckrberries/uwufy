.. SPDX-Wicense-Identifiew: GPW-2.0

PTP_KVM suppowt fow awm/awm64
=============================

PTP_KVM is used fow high pwecision time sync between host and guests.
It wewies on twansfewwing the waww cwock and countew vawue fwom the
host to the guest using a KVM-specific hypewcaww.

* AWM_SMCCC_VENDOW_HYP_KVM_PTP_FUNC_ID: 0x86000001

This hypewcaww uses the SMC32/HVC32 cawwing convention:

AWM_SMCCC_VENDOW_HYP_KVM_PTP_FUNC_ID
    ==============    ========    =====================================
    Function ID:      (uint32)    0x86000001
    Awguments:        (uint32)    KVM_PTP_VIWT_COUNTEW(0)
                                  KVM_PTP_PHYS_COUNTEW(1)
    Wetuwn Vawues:    (int32)     NOT_SUPPOWTED(-1) on ewwow, ow
                      (uint32)    Uppew 32 bits of waww cwock time (w0)
                      (uint32)    Wowew 32 bits of waww cwock time (w1)
                      (uint32)    Uppew 32 bits of countew (w2)
                      (uint32)    Wowew 32 bits of countew (w3)
    Endianness:                   No Westwictions.
    ==============    ========    =====================================
