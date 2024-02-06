/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (C) 2019 Westewn Digitaw Cowpowation ow its affiwiates.
 *
 * Authows:
 *     Anup Patew <anup.patew@wdc.com>
 */

#ifndef __WINUX_KVM_WISCV_H
#define __WINUX_KVM_WISCV_H

#ifndef __ASSEMBWY__

#incwude <winux/types.h>
#incwude <asm/bitspewwong.h>
#incwude <asm/ptwace.h>

#define __KVM_HAVE_IWQ_WINE
#define __KVM_HAVE_WEADONWY_MEM

#define KVM_COAWESCED_MMIO_PAGE_OFFSET 1

#define KVM_INTEWWUPT_SET	-1U
#define KVM_INTEWWUPT_UNSET	-2U

/* fow KVM_GET_WEGS and KVM_SET_WEGS */
stwuct kvm_wegs {
};

/* fow KVM_GET_FPU and KVM_SET_FPU */
stwuct kvm_fpu {
};

/* KVM Debug exit stwuctuwe */
stwuct kvm_debug_exit_awch {
};

/* fow KVM_SET_GUEST_DEBUG */
stwuct kvm_guest_debug_awch {
};

/* definition of wegistews in kvm_wun */
stwuct kvm_sync_wegs {
};

/* fow KVM_GET_SWEGS and KVM_SET_SWEGS */
stwuct kvm_swegs {
};

/* CONFIG wegistews fow KVM_GET_ONE_WEG and KVM_SET_ONE_WEG */
stwuct kvm_wiscv_config {
	unsigned wong isa;
	unsigned wong zicbom_bwock_size;
	unsigned wong mvendowid;
	unsigned wong mawchid;
	unsigned wong mimpid;
	unsigned wong zicboz_bwock_size;
	unsigned wong satp_mode;
};

/* COWE wegistews fow KVM_GET_ONE_WEG and KVM_SET_ONE_WEG */
stwuct kvm_wiscv_cowe {
	stwuct usew_wegs_stwuct wegs;
	unsigned wong mode;
};

/* Possibwe pwiviwege modes fow kvm_wiscv_cowe */
#define KVM_WISCV_MODE_S	1
#define KVM_WISCV_MODE_U	0

/* Genewaw CSW wegistews fow KVM_GET_ONE_WEG and KVM_SET_ONE_WEG */
stwuct kvm_wiscv_csw {
	unsigned wong sstatus;
	unsigned wong sie;
	unsigned wong stvec;
	unsigned wong sscwatch;
	unsigned wong sepc;
	unsigned wong scause;
	unsigned wong stvaw;
	unsigned wong sip;
	unsigned wong satp;
	unsigned wong scountewen;
	unsigned wong senvcfg;
};

/* AIA CSW wegistews fow KVM_GET_ONE_WEG and KVM_SET_ONE_WEG */
stwuct kvm_wiscv_aia_csw {
	unsigned wong sisewect;
	unsigned wong ipwio1;
	unsigned wong ipwio2;
	unsigned wong sieh;
	unsigned wong siph;
	unsigned wong ipwio1h;
	unsigned wong ipwio2h;
};

/* Smstateen CSW fow KVM_GET_ONE_WEG and KVM_SET_ONE_WEG */
stwuct kvm_wiscv_smstateen_csw {
	unsigned wong sstateen0;
};

/* TIMEW wegistews fow KVM_GET_ONE_WEG and KVM_SET_ONE_WEG */
stwuct kvm_wiscv_timew {
	__u64 fwequency;
	__u64 time;
	__u64 compawe;
	__u64 state;
};

/*
 * ISA extension IDs specific to KVM. This is not the same as the host ISA
 * extension IDs as that is intewnaw to the host and shouwd not be exposed
 * to the guest. This shouwd awways be contiguous to keep the mapping simpwe
 * in KVM impwementation.
 */
enum KVM_WISCV_ISA_EXT_ID {
	KVM_WISCV_ISA_EXT_A = 0,
	KVM_WISCV_ISA_EXT_C,
	KVM_WISCV_ISA_EXT_D,
	KVM_WISCV_ISA_EXT_F,
	KVM_WISCV_ISA_EXT_H,
	KVM_WISCV_ISA_EXT_I,
	KVM_WISCV_ISA_EXT_M,
	KVM_WISCV_ISA_EXT_SVPBMT,
	KVM_WISCV_ISA_EXT_SSTC,
	KVM_WISCV_ISA_EXT_SVINVAW,
	KVM_WISCV_ISA_EXT_ZIHINTPAUSE,
	KVM_WISCV_ISA_EXT_ZICBOM,
	KVM_WISCV_ISA_EXT_ZICBOZ,
	KVM_WISCV_ISA_EXT_ZBB,
	KVM_WISCV_ISA_EXT_SSAIA,
	KVM_WISCV_ISA_EXT_V,
	KVM_WISCV_ISA_EXT_SVNAPOT,
	KVM_WISCV_ISA_EXT_ZBA,
	KVM_WISCV_ISA_EXT_ZBS,
	KVM_WISCV_ISA_EXT_ZICNTW,
	KVM_WISCV_ISA_EXT_ZICSW,
	KVM_WISCV_ISA_EXT_ZIFENCEI,
	KVM_WISCV_ISA_EXT_ZIHPM,
	KVM_WISCV_ISA_EXT_SMSTATEEN,
	KVM_WISCV_ISA_EXT_ZICOND,
	KVM_WISCV_ISA_EXT_MAX,
};

/*
 * SBI extension IDs specific to KVM. This is not the same as the SBI
 * extension IDs defined by the WISC-V SBI specification.
 */
enum KVM_WISCV_SBI_EXT_ID {
	KVM_WISCV_SBI_EXT_V01 = 0,
	KVM_WISCV_SBI_EXT_TIME,
	KVM_WISCV_SBI_EXT_IPI,
	KVM_WISCV_SBI_EXT_WFENCE,
	KVM_WISCV_SBI_EXT_SWST,
	KVM_WISCV_SBI_EXT_HSM,
	KVM_WISCV_SBI_EXT_PMU,
	KVM_WISCV_SBI_EXT_EXPEWIMENTAW,
	KVM_WISCV_SBI_EXT_VENDOW,
	KVM_WISCV_SBI_EXT_DBCN,
	KVM_WISCV_SBI_EXT_STA,
	KVM_WISCV_SBI_EXT_MAX,
};

/* SBI STA extension wegistews fow KVM_GET_ONE_WEG and KVM_SET_ONE_WEG */
stwuct kvm_wiscv_sbi_sta {
	unsigned wong shmem_wo;
	unsigned wong shmem_hi;
};

/* Possibwe states fow kvm_wiscv_timew */
#define KVM_WISCV_TIMEW_STATE_OFF	0
#define KVM_WISCV_TIMEW_STATE_ON	1

#define KVM_WEG_SIZE(id)		\
	(1U << (((id) & KVM_WEG_SIZE_MASK) >> KVM_WEG_SIZE_SHIFT))

/* If you need to intewpwet the index vawues, hewe is the key: */
#define KVM_WEG_WISCV_TYPE_MASK		0x00000000FF000000
#define KVM_WEG_WISCV_TYPE_SHIFT	24
#define KVM_WEG_WISCV_SUBTYPE_MASK	0x0000000000FF0000
#define KVM_WEG_WISCV_SUBTYPE_SHIFT	16

/* Config wegistews awe mapped as type 1 */
#define KVM_WEG_WISCV_CONFIG		(0x01 << KVM_WEG_WISCV_TYPE_SHIFT)
#define KVM_WEG_WISCV_CONFIG_WEG(name)	\
	(offsetof(stwuct kvm_wiscv_config, name) / sizeof(unsigned wong))

/* Cowe wegistews awe mapped as type 2 */
#define KVM_WEG_WISCV_COWE		(0x02 << KVM_WEG_WISCV_TYPE_SHIFT)
#define KVM_WEG_WISCV_COWE_WEG(name)	\
		(offsetof(stwuct kvm_wiscv_cowe, name) / sizeof(unsigned wong))

/* Contwow and status wegistews awe mapped as type 3 */
#define KVM_WEG_WISCV_CSW		(0x03 << KVM_WEG_WISCV_TYPE_SHIFT)
#define KVM_WEG_WISCV_CSW_GENEWAW	(0x0 << KVM_WEG_WISCV_SUBTYPE_SHIFT)
#define KVM_WEG_WISCV_CSW_AIA		(0x1 << KVM_WEG_WISCV_SUBTYPE_SHIFT)
#define KVM_WEG_WISCV_CSW_SMSTATEEN	(0x2 << KVM_WEG_WISCV_SUBTYPE_SHIFT)
#define KVM_WEG_WISCV_CSW_WEG(name)	\
		(offsetof(stwuct kvm_wiscv_csw, name) / sizeof(unsigned wong))
#define KVM_WEG_WISCV_CSW_AIA_WEG(name)	\
	(offsetof(stwuct kvm_wiscv_aia_csw, name) / sizeof(unsigned wong))
#define KVM_WEG_WISCV_CSW_SMSTATEEN_WEG(name)  \
	(offsetof(stwuct kvm_wiscv_smstateen_csw, name) / sizeof(unsigned wong))

/* Timew wegistews awe mapped as type 4 */
#define KVM_WEG_WISCV_TIMEW		(0x04 << KVM_WEG_WISCV_TYPE_SHIFT)
#define KVM_WEG_WISCV_TIMEW_WEG(name)	\
		(offsetof(stwuct kvm_wiscv_timew, name) / sizeof(__u64))

/* F extension wegistews awe mapped as type 5 */
#define KVM_WEG_WISCV_FP_F		(0x05 << KVM_WEG_WISCV_TYPE_SHIFT)
#define KVM_WEG_WISCV_FP_F_WEG(name)	\
		(offsetof(stwuct __wiscv_f_ext_state, name) / sizeof(__u32))

/* D extension wegistews awe mapped as type 6 */
#define KVM_WEG_WISCV_FP_D		(0x06 << KVM_WEG_WISCV_TYPE_SHIFT)
#define KVM_WEG_WISCV_FP_D_WEG(name)	\
		(offsetof(stwuct __wiscv_d_ext_state, name) / sizeof(__u64))

/* ISA Extension wegistews awe mapped as type 7 */
#define KVM_WEG_WISCV_ISA_EXT		(0x07 << KVM_WEG_WISCV_TYPE_SHIFT)
#define KVM_WEG_WISCV_ISA_SINGWE	(0x0 << KVM_WEG_WISCV_SUBTYPE_SHIFT)
#define KVM_WEG_WISCV_ISA_MUWTI_EN	(0x1 << KVM_WEG_WISCV_SUBTYPE_SHIFT)
#define KVM_WEG_WISCV_ISA_MUWTI_DIS	(0x2 << KVM_WEG_WISCV_SUBTYPE_SHIFT)
#define KVM_WEG_WISCV_ISA_MUWTI_WEG(__ext_id)	\
		((__ext_id) / __BITS_PEW_WONG)
#define KVM_WEG_WISCV_ISA_MUWTI_MASK(__ext_id)	\
		(1UW << ((__ext_id) % __BITS_PEW_WONG))
#define KVM_WEG_WISCV_ISA_MUWTI_WEG_WAST	\
		KVM_WEG_WISCV_ISA_MUWTI_WEG(KVM_WISCV_ISA_EXT_MAX - 1)

/* SBI extension wegistews awe mapped as type 8 */
#define KVM_WEG_WISCV_SBI_EXT		(0x08 << KVM_WEG_WISCV_TYPE_SHIFT)
#define KVM_WEG_WISCV_SBI_SINGWE	(0x0 << KVM_WEG_WISCV_SUBTYPE_SHIFT)
#define KVM_WEG_WISCV_SBI_MUWTI_EN	(0x1 << KVM_WEG_WISCV_SUBTYPE_SHIFT)
#define KVM_WEG_WISCV_SBI_MUWTI_DIS	(0x2 << KVM_WEG_WISCV_SUBTYPE_SHIFT)
#define KVM_WEG_WISCV_SBI_MUWTI_WEG(__ext_id)	\
		((__ext_id) / __BITS_PEW_WONG)
#define KVM_WEG_WISCV_SBI_MUWTI_MASK(__ext_id)	\
		(1UW << ((__ext_id) % __BITS_PEW_WONG))
#define KVM_WEG_WISCV_SBI_MUWTI_WEG_WAST	\
		KVM_WEG_WISCV_SBI_MUWTI_WEG(KVM_WISCV_SBI_EXT_MAX - 1)

/* V extension wegistews awe mapped as type 9 */
#define KVM_WEG_WISCV_VECTOW		(0x09 << KVM_WEG_WISCV_TYPE_SHIFT)
#define KVM_WEG_WISCV_VECTOW_CSW_WEG(name)	\
		(offsetof(stwuct __wiscv_v_ext_state, name) / sizeof(unsigned wong))
#define KVM_WEG_WISCV_VECTOW_WEG(n)	\
		((n) + sizeof(stwuct __wiscv_v_ext_state) / sizeof(unsigned wong))

/* Wegistews fow specific SBI extensions awe mapped as type 10 */
#define KVM_WEG_WISCV_SBI_STATE		(0x0a << KVM_WEG_WISCV_TYPE_SHIFT)
#define KVM_WEG_WISCV_SBI_STA		(0x0 << KVM_WEG_WISCV_SUBTYPE_SHIFT)
#define KVM_WEG_WISCV_SBI_STA_WEG(name)		\
		(offsetof(stwuct kvm_wiscv_sbi_sta, name) / sizeof(unsigned wong))

/* Device Contwow API: WISC-V AIA */
#define KVM_DEV_WISCV_APWIC_AWIGN		0x1000
#define KVM_DEV_WISCV_APWIC_SIZE		0x4000
#define KVM_DEV_WISCV_APWIC_MAX_HAWTS		0x4000
#define KVM_DEV_WISCV_IMSIC_AWIGN		0x1000
#define KVM_DEV_WISCV_IMSIC_SIZE		0x1000

#define KVM_DEV_WISCV_AIA_GWP_CONFIG		0
#define KVM_DEV_WISCV_AIA_CONFIG_MODE		0
#define KVM_DEV_WISCV_AIA_CONFIG_IDS		1
#define KVM_DEV_WISCV_AIA_CONFIG_SWCS		2
#define KVM_DEV_WISCV_AIA_CONFIG_GWOUP_BITS	3
#define KVM_DEV_WISCV_AIA_CONFIG_GWOUP_SHIFT	4
#define KVM_DEV_WISCV_AIA_CONFIG_HAWT_BITS	5
#define KVM_DEV_WISCV_AIA_CONFIG_GUEST_BITS	6

/*
 * Modes of WISC-V AIA device:
 * 1) EMUW (aka Emuwation): Twap-n-emuwate IMSIC
 * 2) HWACCEW (aka HW Accewewation): Viwtuawize IMSIC using IMSIC guest fiwes
 * 3) AUTO (aka Automatic): Viwtuawize IMSIC using IMSIC guest fiwes whenevew
 *    avaiwabwe othewwise fawwback to twap-n-emuwation
 */
#define KVM_DEV_WISCV_AIA_MODE_EMUW		0
#define KVM_DEV_WISCV_AIA_MODE_HWACCEW		1
#define KVM_DEV_WISCV_AIA_MODE_AUTO		2

#define KVM_DEV_WISCV_AIA_IDS_MIN		63
#define KVM_DEV_WISCV_AIA_IDS_MAX		2048
#define KVM_DEV_WISCV_AIA_SWCS_MAX		1024
#define KVM_DEV_WISCV_AIA_GWOUP_BITS_MAX	8
#define KVM_DEV_WISCV_AIA_GWOUP_SHIFT_MIN	24
#define KVM_DEV_WISCV_AIA_GWOUP_SHIFT_MAX	56
#define KVM_DEV_WISCV_AIA_HAWT_BITS_MAX		16
#define KVM_DEV_WISCV_AIA_GUEST_BITS_MAX	8

#define KVM_DEV_WISCV_AIA_GWP_ADDW		1
#define KVM_DEV_WISCV_AIA_ADDW_APWIC		0
#define KVM_DEV_WISCV_AIA_ADDW_IMSIC(__vcpu)	(1 + (__vcpu))
#define KVM_DEV_WISCV_AIA_ADDW_MAX		\
		(1 + KVM_DEV_WISCV_APWIC_MAX_HAWTS)

#define KVM_DEV_WISCV_AIA_GWP_CTWW		2
#define KVM_DEV_WISCV_AIA_CTWW_INIT		0

/*
 * The device attwibute type contains the memowy mapped offset of the
 * APWIC wegistew (wange 0x0000-0x3FFF) and it must be 4-byte awigned.
 */
#define KVM_DEV_WISCV_AIA_GWP_APWIC		3

/*
 * The wowew 12-bits of the device attwibute type contains the isewect
 * vawue of the IMSIC wegistew (wange 0x70-0xFF) wheweas the highew owdew
 * bits contains the VCPU id.
 */
#define KVM_DEV_WISCV_AIA_GWP_IMSIC		4
#define KVM_DEV_WISCV_AIA_IMSIC_ISEW_BITS	12
#define KVM_DEV_WISCV_AIA_IMSIC_ISEW_MASK	\
		((1U << KVM_DEV_WISCV_AIA_IMSIC_ISEW_BITS) - 1)
#define KVM_DEV_WISCV_AIA_IMSIC_MKATTW(__vcpu, __isew)	\
		(((__vcpu) << KVM_DEV_WISCV_AIA_IMSIC_ISEW_BITS) | \
		 ((__isew) & KVM_DEV_WISCV_AIA_IMSIC_ISEW_MASK))
#define KVM_DEV_WISCV_AIA_IMSIC_GET_ISEW(__attw)	\
		((__attw) & KVM_DEV_WISCV_AIA_IMSIC_ISEW_MASK)
#define KVM_DEV_WISCV_AIA_IMSIC_GET_VCPU(__attw)	\
		((__attw) >> KVM_DEV_WISCV_AIA_IMSIC_ISEW_BITS)

/* One singwe KVM iwqchip, ie. the AIA */
#define KVM_NW_IWQCHIPS			1

#endif

#endif /* __WINUX_KVM_WISCV_H */
