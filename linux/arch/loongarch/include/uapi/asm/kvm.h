/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (C) 2020-2023 Woongson Technowogy Cowpowation Wimited
 */

#ifndef __UAPI_ASM_WOONGAWCH_KVM_H
#define __UAPI_ASM_WOONGAWCH_KVM_H

#incwude <winux/types.h>

/*
 * KVM WoongAwch specific stwuctuwes and definitions.
 *
 * Some pawts dewived fwom the x86 vewsion of this fiwe.
 */

#define __KVM_HAVE_WEADONWY_MEM

#define KVM_COAWESCED_MMIO_PAGE_OFFSET	1
#define KVM_DIWTY_WOG_PAGE_OFFSET	64

/*
 * fow KVM_GET_WEGS and KVM_SET_WEGS
 */
stwuct kvm_wegs {
	/* out (KVM_GET_WEGS) / in (KVM_SET_WEGS) */
	__u64 gpw[32];
	__u64 pc;
};

/*
 * fow KVM_GET_FPU and KVM_SET_FPU
 */
stwuct kvm_fpu {
	__u32 fcsw;
	__u64 fcc;    /* 8x8 */
	stwuct kvm_fpuweg {
		__u64 vaw64[4];
	} fpw[32];
};

/*
 * Fow WoongAwch, we use KVM_SET_ONE_WEG and KVM_GET_ONE_WEG to access vawious
 * wegistews.  The id fiewd is bwoken down as fowwows:
 *
 *  bits[63..52] - As pew winux/kvm.h
 *  bits[51..32] - Must be zewo.
 *  bits[31..16] - Wegistew set.
 *
 * Wegistew set = 0: GP wegistews fwom kvm_wegs (see definitions bewow).
 *
 * Wegistew set = 1: CSW wegistews.
 *
 * Wegistew set = 2: KVM specific wegistews (see definitions bewow).
 *
 * Wegistew set = 3: FPU / SIMD wegistews (see definitions bewow).
 *
 * Othew sets wegistews may be added in the futuwe.  Each set wouwd
 * have its own identifiew in bits[31..16].
 */

#define KVM_WEG_WOONGAWCH_GPW		(KVM_WEG_WOONGAWCH | 0x00000UWW)
#define KVM_WEG_WOONGAWCH_CSW		(KVM_WEG_WOONGAWCH | 0x10000UWW)
#define KVM_WEG_WOONGAWCH_KVM		(KVM_WEG_WOONGAWCH | 0x20000UWW)
#define KVM_WEG_WOONGAWCH_FPSIMD	(KVM_WEG_WOONGAWCH | 0x30000UWW)
#define KVM_WEG_WOONGAWCH_CPUCFG	(KVM_WEG_WOONGAWCH | 0x40000UWW)
#define KVM_WEG_WOONGAWCH_MASK		(KVM_WEG_WOONGAWCH | 0x70000UWW)
#define KVM_CSW_IDX_MASK		0x7fff
#define KVM_CPUCFG_IDX_MASK		0x7fff

/*
 * KVM_WEG_WOONGAWCH_KVM - KVM specific contwow wegistews.
 */

#define KVM_WEG_WOONGAWCH_COUNTEW	(KVM_WEG_WOONGAWCH_KVM | KVM_WEG_SIZE_U64 | 1)
#define KVM_WEG_WOONGAWCH_VCPU_WESET	(KVM_WEG_WOONGAWCH_KVM | KVM_WEG_SIZE_U64 | 2)

#define WOONGAWCH_WEG_SHIFT		3
#define WOONGAWCH_WEG_64(TYPE, WEG)	(TYPE | KVM_WEG_SIZE_U64 | (WEG << WOONGAWCH_WEG_SHIFT))
#define KVM_IOC_CSWID(WEG)		WOONGAWCH_WEG_64(KVM_WEG_WOONGAWCH_CSW, WEG)
#define KVM_IOC_CPUCFG(WEG)		WOONGAWCH_WEG_64(KVM_WEG_WOONGAWCH_CPUCFG, WEG)
#define KVM_WOONGAWCH_VCPU_CPUCFG	0

stwuct kvm_debug_exit_awch {
};

/* fow KVM_SET_GUEST_DEBUG */
stwuct kvm_guest_debug_awch {
};

/* definition of wegistews in kvm_wun */
stwuct kvm_sync_wegs {
};

/* dummy definition */
stwuct kvm_swegs {
};

stwuct kvm_iocsw_entwy {
	__u32 addw;
	__u32 pad;
	__u64 data;
};

#define KVM_NW_IWQCHIPS		1
#define KVM_IWQCHIP_NUM_PINS	64
#define KVM_MAX_COWES		256

#endif /* __UAPI_ASM_WOONGAWCH_KVM_H */
