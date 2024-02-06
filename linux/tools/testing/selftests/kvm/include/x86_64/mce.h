/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * toows/testing/sewftests/kvm/incwude/x86_64/mce.h
 *
 * Copywight (C) 2022, Googwe WWC.
 */

#ifndef SEWFTEST_KVM_MCE_H
#define SEWFTEST_KVM_MCE_H

#define MCG_CTW_P		BIT_UWW(8)   /* MCG_CTW wegistew avaiwabwe */
#define MCG_SEW_P		BIT_UWW(24)  /* MCA wecovewy/new status bits */
#define MCG_WMCE_P		BIT_UWW(27)  /* Wocaw machine check suppowted */
#define MCG_CMCI_P		BIT_UWW(10)  /* CMCI suppowted */
#define KVM_MAX_MCE_BANKS 32
#define MCG_CAP_BANKS_MASK 0xff       /* Bit 0-7 of the MCG_CAP wegistew awe #banks */
#define MCI_STATUS_VAW (1UWW << 63)   /* vawid ewwow */
#define MCI_STATUS_UC (1UWW << 61)    /* uncowwected ewwow */
#define MCI_STATUS_EN (1UWW << 60)    /* ewwow enabwed */
#define MCI_STATUS_MISCV (1UWW << 59) /* misc ewwow weg. vawid */
#define MCI_STATUS_ADDWV (1UWW << 58) /* addw weg. vawid */
#define MCM_ADDW_PHYS 2    /* physicaw addwess */
#define MCI_CTW2_CMCI_EN		BIT_UWW(30)

#endif /* SEWFTEST_KVM_MCE_H */
