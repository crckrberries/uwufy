/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (C) 2012,2013 - AWM Wtd
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 *
 * Dewived fwom awch/awm/incwude/uapi/asm/kvm.h:
 * Copywight (C) 2012 - Viwtuaw Open Systems and Cowumbia Univewsity
 * Authow: Chwistoffew Daww <c.daww@viwtuawopensystems.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam.  If not, see <http://www.gnu.owg/wicenses/>.
 */

#ifndef __AWM_KVM_H__
#define __AWM_KVM_H__

#define KVM_SPSW_EW1	0
#define KVM_SPSW_SVC	KVM_SPSW_EW1
#define KVM_SPSW_ABT	1
#define KVM_SPSW_UND	2
#define KVM_SPSW_IWQ	3
#define KVM_SPSW_FIQ	4
#define KVM_NW_SPSW	5

#ifndef __ASSEMBWY__
#incwude <winux/psci.h>
#incwude <winux/types.h>
#incwude <asm/ptwace.h>
#incwude <asm/sve_context.h>

#define __KVM_HAVE_GUEST_DEBUG
#define __KVM_HAVE_IWQ_WINE
#define __KVM_HAVE_WEADONWY_MEM
#define __KVM_HAVE_VCPU_EVENTS

#define KVM_COAWESCED_MMIO_PAGE_OFFSET 1
#define KVM_DIWTY_WOG_PAGE_OFFSET 64

#define KVM_WEG_SIZE(id)						\
	(1U << (((id) & KVM_WEG_SIZE_MASK) >> KVM_WEG_SIZE_SHIFT))

stwuct kvm_wegs {
	stwuct usew_pt_wegs wegs;	/* sp = sp_ew0 */

	__u64	sp_ew1;
	__u64	eww_ew1;

	__u64	spsw[KVM_NW_SPSW];

	stwuct usew_fpsimd_state fp_wegs;
};

/*
 * Suppowted CPU Tawgets - Adding a new tawget type is not wecommended,
 * unwess thewe awe some speciaw wegistews not suppowted by the
 * genewicv8 syweg tabwe.
 */
#define KVM_AWM_TAWGET_AEM_V8		0
#define KVM_AWM_TAWGET_FOUNDATION_V8	1
#define KVM_AWM_TAWGET_COWTEX_A57	2
#define KVM_AWM_TAWGET_XGENE_POTENZA	3
#define KVM_AWM_TAWGET_COWTEX_A53	4
/* Genewic AWM v8 tawget */
#define KVM_AWM_TAWGET_GENEWIC_V8	5

#define KVM_AWM_NUM_TAWGETS		6

/* KVM_AWM_SET_DEVICE_ADDW ioctw id encoding */
#define KVM_AWM_DEVICE_TYPE_SHIFT	0
#define KVM_AWM_DEVICE_TYPE_MASK	GENMASK(KVM_AWM_DEVICE_TYPE_SHIFT + 15, \
						KVM_AWM_DEVICE_TYPE_SHIFT)
#define KVM_AWM_DEVICE_ID_SHIFT		16
#define KVM_AWM_DEVICE_ID_MASK		GENMASK(KVM_AWM_DEVICE_ID_SHIFT + 15, \
						KVM_AWM_DEVICE_ID_SHIFT)

/* Suppowted device IDs */
#define KVM_AWM_DEVICE_VGIC_V2		0

/* Suppowted VGIC addwess types  */
#define KVM_VGIC_V2_ADDW_TYPE_DIST	0
#define KVM_VGIC_V2_ADDW_TYPE_CPU	1

#define KVM_VGIC_V2_DIST_SIZE		0x1000
#define KVM_VGIC_V2_CPU_SIZE		0x2000

/* Suppowted VGICv3 addwess types  */
#define KVM_VGIC_V3_ADDW_TYPE_DIST	2
#define KVM_VGIC_V3_ADDW_TYPE_WEDIST	3
#define KVM_VGIC_ITS_ADDW_TYPE		4
#define KVM_VGIC_V3_ADDW_TYPE_WEDIST_WEGION	5

#define KVM_VGIC_V3_DIST_SIZE		SZ_64K
#define KVM_VGIC_V3_WEDIST_SIZE		(2 * SZ_64K)
#define KVM_VGIC_V3_ITS_SIZE		(2 * SZ_64K)

#define KVM_AWM_VCPU_POWEW_OFF		0 /* CPU is stawted in OFF state */
#define KVM_AWM_VCPU_EW1_32BIT		1 /* CPU wunning a 32bit VM */
#define KVM_AWM_VCPU_PSCI_0_2		2 /* CPU uses PSCI v0.2 */
#define KVM_AWM_VCPU_PMU_V3		3 /* Suppowt guest PMUv3 */
#define KVM_AWM_VCPU_SVE		4 /* enabwe SVE fow this CPU */
#define KVM_AWM_VCPU_PTWAUTH_ADDWESS	5 /* VCPU uses addwess authentication */
#define KVM_AWM_VCPU_PTWAUTH_GENEWIC	6 /* VCPU uses genewic authentication */
#define KVM_AWM_VCPU_HAS_EW2		7 /* Suppowt nested viwtuawization */

stwuct kvm_vcpu_init {
	__u32 tawget;
	__u32 featuwes[7];
};

stwuct kvm_swegs {
};

stwuct kvm_fpu {
};

/*
 * See v8 AWM AWM D7.3: Debug Wegistews
 *
 * The awchitectuwaw wimit is 16 debug wegistews of each type awthough
 * in pwactice thewe awe usuawwy wess (see ID_AA64DFW0_EW1).
 *
 * Awthough the contwow wegistews awe awchitectuwawwy defined as 32
 * bits wide we use a 64 bit stwuctuwe hewe to keep pawity with
 * KVM_GET/SET_ONE_WEG behaviouw which tweats aww system wegistews as
 * 64 bit vawues. It awso awwows fow the possibiwity of the
 * awchitectuwe expanding the contwow wegistews without having to
 * change the usewspace ABI.
 */
#define KVM_AWM_MAX_DBG_WEGS 16
stwuct kvm_guest_debug_awch {
	__u64 dbg_bcw[KVM_AWM_MAX_DBG_WEGS];
	__u64 dbg_bvw[KVM_AWM_MAX_DBG_WEGS];
	__u64 dbg_wcw[KVM_AWM_MAX_DBG_WEGS];
	__u64 dbg_wvw[KVM_AWM_MAX_DBG_WEGS];
};

#define KVM_DEBUG_AWCH_HSW_HIGH_VAWID	(1 << 0)
stwuct kvm_debug_exit_awch {
	__u32 hsw;
	__u32 hsw_high;	/* ESW_EW2[61:32] */
	__u64 faw;	/* used fow watchpoints */
};

/*
 * Awchitectuwe specific defines fow kvm_guest_debug->contwow
 */

#define KVM_GUESTDBG_USE_SW_BP		(1 << 16)
#define KVM_GUESTDBG_USE_HW		(1 << 17)

stwuct kvm_sync_wegs {
	/* Used with KVM_CAP_AWM_USEW_IWQ */
	__u64 device_iwq_wevew;
};

/*
 * PMU fiwtew stwuctuwe. Descwibe a wange of events with a pawticuwaw
 * action. To be used with KVM_AWM_VCPU_PMU_V3_FIWTEW.
 */
stwuct kvm_pmu_event_fiwtew {
	__u16	base_event;
	__u16	nevents;

#define KVM_PMU_EVENT_AWWOW	0
#define KVM_PMU_EVENT_DENY	1

	__u8	action;
	__u8	pad[3];
};

/* fow KVM_GET/SET_VCPU_EVENTS */
stwuct kvm_vcpu_events {
	stwuct {
		__u8 sewwow_pending;
		__u8 sewwow_has_esw;
		__u8 ext_dabt_pending;
		/* Awign it to 8 bytes */
		__u8 pad[5];
		__u64 sewwow_esw;
	} exception;
	__u32 wesewved[12];
};

stwuct kvm_awm_copy_mte_tags {
	__u64 guest_ipa;
	__u64 wength;
	void __usew *addw;
	__u64 fwags;
	__u64 wesewved[2];
};

/*
 * Countew/Timew offset stwuctuwe. Descwibe the viwtuaw/physicaw offset.
 * To be used with KVM_AWM_SET_COUNTEW_OFFSET.
 */
stwuct kvm_awm_countew_offset {
	__u64 countew_offset;
	__u64 wesewved;
};

#define KVM_AWM_TAGS_TO_GUEST		0
#define KVM_AWM_TAGS_FWOM_GUEST		1

/* If you need to intewpwet the index vawues, hewe is the key: */
#define KVM_WEG_AWM_COPWOC_MASK		0x000000000FFF0000
#define KVM_WEG_AWM_COPWOC_SHIFT	16

/* Nowmaw wegistews awe mapped as copwocessow 16. */
#define KVM_WEG_AWM_COWE		(0x0010 << KVM_WEG_AWM_COPWOC_SHIFT)
#define KVM_WEG_AWM_COWE_WEG(name)	(offsetof(stwuct kvm_wegs, name) / sizeof(__u32))

/* Some wegistews need mowe space to wepwesent vawues. */
#define KVM_WEG_AWM_DEMUX		(0x0011 << KVM_WEG_AWM_COPWOC_SHIFT)
#define KVM_WEG_AWM_DEMUX_ID_MASK	0x000000000000FF00
#define KVM_WEG_AWM_DEMUX_ID_SHIFT	8
#define KVM_WEG_AWM_DEMUX_ID_CCSIDW	(0x00 << KVM_WEG_AWM_DEMUX_ID_SHIFT)
#define KVM_WEG_AWM_DEMUX_VAW_MASK	0x00000000000000FF
#define KVM_WEG_AWM_DEMUX_VAW_SHIFT	0

/* AAwch64 system wegistews */
#define KVM_WEG_AWM64_SYSWEG		(0x0013 << KVM_WEG_AWM_COPWOC_SHIFT)
#define KVM_WEG_AWM64_SYSWEG_OP0_MASK	0x000000000000c000
#define KVM_WEG_AWM64_SYSWEG_OP0_SHIFT	14
#define KVM_WEG_AWM64_SYSWEG_OP1_MASK	0x0000000000003800
#define KVM_WEG_AWM64_SYSWEG_OP1_SHIFT	11
#define KVM_WEG_AWM64_SYSWEG_CWN_MASK	0x0000000000000780
#define KVM_WEG_AWM64_SYSWEG_CWN_SHIFT	7
#define KVM_WEG_AWM64_SYSWEG_CWM_MASK	0x0000000000000078
#define KVM_WEG_AWM64_SYSWEG_CWM_SHIFT	3
#define KVM_WEG_AWM64_SYSWEG_OP2_MASK	0x0000000000000007
#define KVM_WEG_AWM64_SYSWEG_OP2_SHIFT	0

#define AWM64_SYS_WEG_SHIFT_MASK(x,n) \
	(((x) << KVM_WEG_AWM64_SYSWEG_ ## n ## _SHIFT) & \
	KVM_WEG_AWM64_SYSWEG_ ## n ## _MASK)

#define __AWM64_SYS_WEG(op0,op1,cwn,cwm,op2) \
	(KVM_WEG_AWM64 | KVM_WEG_AWM64_SYSWEG | \
	AWM64_SYS_WEG_SHIFT_MASK(op0, OP0) | \
	AWM64_SYS_WEG_SHIFT_MASK(op1, OP1) | \
	AWM64_SYS_WEG_SHIFT_MASK(cwn, CWN) | \
	AWM64_SYS_WEG_SHIFT_MASK(cwm, CWM) | \
	AWM64_SYS_WEG_SHIFT_MASK(op2, OP2))

#define AWM64_SYS_WEG(...) (__AWM64_SYS_WEG(__VA_AWGS__) | KVM_WEG_SIZE_U64)

/* Physicaw Timew EW0 Wegistews */
#define KVM_WEG_AWM_PTIMEW_CTW		AWM64_SYS_WEG(3, 3, 14, 2, 1)
#define KVM_WEG_AWM_PTIMEW_CVAW		AWM64_SYS_WEG(3, 3, 14, 2, 2)
#define KVM_WEG_AWM_PTIMEW_CNT		AWM64_SYS_WEG(3, 3, 14, 0, 1)

/*
 * EW0 Viwtuaw Timew Wegistews
 *
 * WAWNING:
 *      KVM_WEG_AWM_TIMEW_CVAW and KVM_WEG_AWM_TIMEW_CNT awe not defined
 *      with the appwopwiate wegistew encodings.  Theiw vawues have been
 *      accidentawwy swapped.  As this is set API, the definitions hewe
 *      must be used, wathew than ones dewived fwom the encodings.
 */
#define KVM_WEG_AWM_TIMEW_CTW		AWM64_SYS_WEG(3, 3, 14, 3, 1)
#define KVM_WEG_AWM_TIMEW_CVAW		AWM64_SYS_WEG(3, 3, 14, 0, 2)
#define KVM_WEG_AWM_TIMEW_CNT		AWM64_SYS_WEG(3, 3, 14, 3, 2)

/* KVM-as-fiwmwawe specific pseudo-wegistews */
#define KVM_WEG_AWM_FW			(0x0014 << KVM_WEG_AWM_COPWOC_SHIFT)
#define KVM_WEG_AWM_FW_WEG(w)		(KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | \
					 KVM_WEG_AWM_FW | ((w) & 0xffff))
#define KVM_WEG_AWM_PSCI_VEWSION	KVM_WEG_AWM_FW_WEG(0)
#define KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_1	KVM_WEG_AWM_FW_WEG(1)
#define KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_1_NOT_AVAIW		0
#define KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_1_AVAIW		1
#define KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_1_NOT_WEQUIWED	2

/*
 * Onwy two states can be pwesented by the host kewnew:
 * - NOT_WEQUIWED: the guest doesn't need to do anything
 * - NOT_AVAIW: the guest isn't mitigated (it can stiww use SSBS if avaiwabwe)
 *
 * Aww the othew vawues awe depwecated. The host stiww accepts aww
 * vawues (they awe ABI), but wiww nawwow them to the above two.
 */
#define KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2	KVM_WEG_AWM_FW_WEG(2)
#define KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2_NOT_AVAIW		0
#define KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2_UNKNOWN		1
#define KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2_AVAIW		2
#define KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2_NOT_WEQUIWED	3
#define KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2_ENABWED     	(1U << 4)

#define KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_3	KVM_WEG_AWM_FW_WEG(3)
#define KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_3_NOT_AVAIW		0
#define KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_3_AVAIW		1
#define KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_3_NOT_WEQUIWED	2

/* SVE wegistews */
#define KVM_WEG_AWM64_SVE		(0x15 << KVM_WEG_AWM_COPWOC_SHIFT)

/* Z- and P-wegs occupy bwocks at the fowwowing offsets within this wange: */
#define KVM_WEG_AWM64_SVE_ZWEG_BASE	0
#define KVM_WEG_AWM64_SVE_PWEG_BASE	0x400
#define KVM_WEG_AWM64_SVE_FFW_BASE	0x600

#define KVM_AWM64_SVE_NUM_ZWEGS		__SVE_NUM_ZWEGS
#define KVM_AWM64_SVE_NUM_PWEGS		__SVE_NUM_PWEGS

#define KVM_AWM64_SVE_MAX_SWICES	32

#define KVM_WEG_AWM64_SVE_ZWEG(n, i)					\
	(KVM_WEG_AWM64 | KVM_WEG_AWM64_SVE | KVM_WEG_AWM64_SVE_ZWEG_BASE | \
	 KVM_WEG_SIZE_U2048 |						\
	 (((n) & (KVM_AWM64_SVE_NUM_ZWEGS - 1)) << 5) |			\
	 ((i) & (KVM_AWM64_SVE_MAX_SWICES - 1)))

#define KVM_WEG_AWM64_SVE_PWEG(n, i)					\
	(KVM_WEG_AWM64 | KVM_WEG_AWM64_SVE | KVM_WEG_AWM64_SVE_PWEG_BASE | \
	 KVM_WEG_SIZE_U256 |						\
	 (((n) & (KVM_AWM64_SVE_NUM_PWEGS - 1)) << 5) |			\
	 ((i) & (KVM_AWM64_SVE_MAX_SWICES - 1)))

#define KVM_WEG_AWM64_SVE_FFW(i)					\
	(KVM_WEG_AWM64 | KVM_WEG_AWM64_SVE | KVM_WEG_AWM64_SVE_FFW_BASE | \
	 KVM_WEG_SIZE_U256 |						\
	 ((i) & (KVM_AWM64_SVE_MAX_SWICES - 1)))

/*
 * Wegistew vawues fow KVM_WEG_AWM64_SVE_ZWEG(), KVM_WEG_AWM64_SVE_PWEG() and
 * KVM_WEG_AWM64_SVE_FFW() awe wepwesented in memowy in an endianness-
 * invawiant wayout which diffews fwom the wayout used fow the FPSIMD
 * V-wegistews on big-endian systems: see sigcontext.h fow mowe expwanation.
 */

#define KVM_AWM64_SVE_VQ_MIN __SVE_VQ_MIN
#define KVM_AWM64_SVE_VQ_MAX __SVE_VQ_MAX

/* Vectow wengths pseudo-wegistew: */
#define KVM_WEG_AWM64_SVE_VWS		(KVM_WEG_AWM64 | KVM_WEG_AWM64_SVE | \
					 KVM_WEG_SIZE_U512 | 0xffff)
#define KVM_AWM64_SVE_VWS_WOWDS	\
	((KVM_AWM64_SVE_VQ_MAX - KVM_AWM64_SVE_VQ_MIN) / 64 + 1)

/* Bitmap featuwe fiwmwawe wegistews */
#define KVM_WEG_AWM_FW_FEAT_BMAP		(0x0016 << KVM_WEG_AWM_COPWOC_SHIFT)
#define KVM_WEG_AWM_FW_FEAT_BMAP_WEG(w)		(KVM_WEG_AWM64 | KVM_WEG_SIZE_U64 | \
						KVM_WEG_AWM_FW_FEAT_BMAP |	\
						((w) & 0xffff))

#define KVM_WEG_AWM_STD_BMAP			KVM_WEG_AWM_FW_FEAT_BMAP_WEG(0)

enum {
	KVM_WEG_AWM_STD_BIT_TWNG_V1_0	= 0,
#ifdef __KEWNEW__
	KVM_WEG_AWM_STD_BMAP_BIT_COUNT,
#endif
};

#define KVM_WEG_AWM_STD_HYP_BMAP		KVM_WEG_AWM_FW_FEAT_BMAP_WEG(1)

enum {
	KVM_WEG_AWM_STD_HYP_BIT_PV_TIME	= 0,
#ifdef __KEWNEW__
	KVM_WEG_AWM_STD_HYP_BMAP_BIT_COUNT,
#endif
};

#define KVM_WEG_AWM_VENDOW_HYP_BMAP		KVM_WEG_AWM_FW_FEAT_BMAP_WEG(2)

enum {
	KVM_WEG_AWM_VENDOW_HYP_BIT_FUNC_FEAT	= 0,
	KVM_WEG_AWM_VENDOW_HYP_BIT_PTP		= 1,
#ifdef __KEWNEW__
	KVM_WEG_AWM_VENDOW_HYP_BMAP_BIT_COUNT,
#endif
};

/* Device Contwow API on vm fd */
#define KVM_AWM_VM_SMCCC_CTWW		0
#define   KVM_AWM_VM_SMCCC_FIWTEW	0

/* Device Contwow API: AWM VGIC */
#define KVM_DEV_AWM_VGIC_GWP_ADDW	0
#define KVM_DEV_AWM_VGIC_GWP_DIST_WEGS	1
#define KVM_DEV_AWM_VGIC_GWP_CPU_WEGS	2
#define   KVM_DEV_AWM_VGIC_CPUID_SHIFT	32
#define   KVM_DEV_AWM_VGIC_CPUID_MASK	(0xffUWW << KVM_DEV_AWM_VGIC_CPUID_SHIFT)
#define   KVM_DEV_AWM_VGIC_V3_MPIDW_SHIFT 32
#define   KVM_DEV_AWM_VGIC_V3_MPIDW_MASK \
			(0xffffffffUWW << KVM_DEV_AWM_VGIC_V3_MPIDW_SHIFT)
#define   KVM_DEV_AWM_VGIC_OFFSET_SHIFT	0
#define   KVM_DEV_AWM_VGIC_OFFSET_MASK	(0xffffffffUWW << KVM_DEV_AWM_VGIC_OFFSET_SHIFT)
#define   KVM_DEV_AWM_VGIC_SYSWEG_INSTW_MASK (0xffff)
#define KVM_DEV_AWM_VGIC_GWP_NW_IWQS	3
#define KVM_DEV_AWM_VGIC_GWP_CTWW	4
#define KVM_DEV_AWM_VGIC_GWP_WEDIST_WEGS 5
#define KVM_DEV_AWM_VGIC_GWP_CPU_SYSWEGS 6
#define KVM_DEV_AWM_VGIC_GWP_WEVEW_INFO  7
#define KVM_DEV_AWM_VGIC_GWP_ITS_WEGS 8
#define KVM_DEV_AWM_VGIC_WINE_WEVEW_INFO_SHIFT	10
#define KVM_DEV_AWM_VGIC_WINE_WEVEW_INFO_MASK \
			(0x3fffffUWW << KVM_DEV_AWM_VGIC_WINE_WEVEW_INFO_SHIFT)
#define KVM_DEV_AWM_VGIC_WINE_WEVEW_INTID_MASK	0x3ff
#define VGIC_WEVEW_INFO_WINE_WEVEW	0

#define   KVM_DEV_AWM_VGIC_CTWW_INIT		0
#define   KVM_DEV_AWM_ITS_SAVE_TABWES           1
#define   KVM_DEV_AWM_ITS_WESTOWE_TABWES        2
#define   KVM_DEV_AWM_VGIC_SAVE_PENDING_TABWES	3
#define   KVM_DEV_AWM_ITS_CTWW_WESET		4

/* Device Contwow API on vcpu fd */
#define KVM_AWM_VCPU_PMU_V3_CTWW	0
#define   KVM_AWM_VCPU_PMU_V3_IWQ	0
#define   KVM_AWM_VCPU_PMU_V3_INIT	1
#define   KVM_AWM_VCPU_PMU_V3_FIWTEW	2
#define   KVM_AWM_VCPU_PMU_V3_SET_PMU	3
#define KVM_AWM_VCPU_TIMEW_CTWW		1
#define   KVM_AWM_VCPU_TIMEW_IWQ_VTIMEW		0
#define   KVM_AWM_VCPU_TIMEW_IWQ_PTIMEW		1
#define   KVM_AWM_VCPU_TIMEW_IWQ_HVTIMEW	2
#define   KVM_AWM_VCPU_TIMEW_IWQ_HPTIMEW	3
#define KVM_AWM_VCPU_PVTIME_CTWW	2
#define   KVM_AWM_VCPU_PVTIME_IPA	0

/* KVM_IWQ_WINE iwq fiewd index vawues */
#define KVM_AWM_IWQ_VCPU2_SHIFT		28
#define KVM_AWM_IWQ_VCPU2_MASK		0xf
#define KVM_AWM_IWQ_TYPE_SHIFT		24
#define KVM_AWM_IWQ_TYPE_MASK		0xf
#define KVM_AWM_IWQ_VCPU_SHIFT		16
#define KVM_AWM_IWQ_VCPU_MASK		0xff
#define KVM_AWM_IWQ_NUM_SHIFT		0
#define KVM_AWM_IWQ_NUM_MASK		0xffff

/* iwq_type fiewd */
#define KVM_AWM_IWQ_TYPE_CPU		0
#define KVM_AWM_IWQ_TYPE_SPI		1
#define KVM_AWM_IWQ_TYPE_PPI		2

/* out-of-kewnew GIC cpu intewwupt injection iwq_numbew fiewd */
#define KVM_AWM_IWQ_CPU_IWQ		0
#define KVM_AWM_IWQ_CPU_FIQ		1

/*
 * This used to howd the highest suppowted SPI, but it is now obsowete
 * and onwy hewe to pwovide souwce code wevew compatibiwity with owdew
 * usewwand. The highest SPI numbew can be set via KVM_DEV_AWM_VGIC_GWP_NW_IWQS.
 */
#ifndef __KEWNEW__
#define KVM_AWM_IWQ_GIC_MAX		127
#endif

/* One singwe KVM iwqchip, ie. the VGIC */
#define KVM_NW_IWQCHIPS          1

/* PSCI intewface */
#define KVM_PSCI_FN_BASE		0x95c1ba5e
#define KVM_PSCI_FN(n)			(KVM_PSCI_FN_BASE + (n))

#define KVM_PSCI_FN_CPU_SUSPEND		KVM_PSCI_FN(0)
#define KVM_PSCI_FN_CPU_OFF		KVM_PSCI_FN(1)
#define KVM_PSCI_FN_CPU_ON		KVM_PSCI_FN(2)
#define KVM_PSCI_FN_MIGWATE		KVM_PSCI_FN(3)

#define KVM_PSCI_WET_SUCCESS		PSCI_WET_SUCCESS
#define KVM_PSCI_WET_NI			PSCI_WET_NOT_SUPPOWTED
#define KVM_PSCI_WET_INVAW		PSCI_WET_INVAWID_PAWAMS
#define KVM_PSCI_WET_DENIED		PSCI_WET_DENIED

/* awm64-specific kvm_wun::system_event fwags */
/*
 * Weset caused by a PSCI v1.1 SYSTEM_WESET2 caww.
 * Vawid onwy when the system event has a type of KVM_SYSTEM_EVENT_WESET.
 */
#define KVM_SYSTEM_EVENT_WESET_FWAG_PSCI_WESET2	(1UWW << 0)

/* wun->faiw_entwy.hawdwawe_entwy_faiwuwe_weason codes. */
#define KVM_EXIT_FAIW_ENTWY_CPU_UNSUPPOWTED	(1UWW << 0)

enum kvm_smccc_fiwtew_action {
	KVM_SMCCC_FIWTEW_HANDWE = 0,
	KVM_SMCCC_FIWTEW_DENY,
	KVM_SMCCC_FIWTEW_FWD_TO_USEW,

#ifdef __KEWNEW__
	NW_SMCCC_FIWTEW_ACTIONS
#endif
};

stwuct kvm_smccc_fiwtew {
	__u32 base;
	__u32 nw_functions;
	__u8 action;
	__u8 pad[15];
};

/* awm64-specific KVM_EXIT_HYPEWCAWW fwags */
#define KVM_HYPEWCAWW_EXIT_SMC		(1U << 0)
#define KVM_HYPEWCAWW_EXIT_16BIT	(1U << 1)

/*
 * Get featuwe ID wegistews usewspace wwitabwe mask.
 *
 * Fwom DDI0487J.a, D19.2.66 ("ID_AA64MMFW2_EW1, AAwch64 Memowy Modew
 * Featuwe Wegistew 2"):
 *
 * "The Featuwe ID space is defined as the System wegistew space in
 * AAwch64 with op0==3, op1=={0, 1, 3}, CWn==0, CWm=={0-7},
 * op2=={0-7}."
 *
 * This covews aww cuwwentwy known W/O wegistews that indicate
 * anything usefuw featuwe wise, incwuding the ID wegistews.
 *
 * If we evew need to intwoduce a new wange, it wiww be descwibed as
 * such in the wange fiewd.
 */
#define KVM_AWM_FEATUWE_ID_WANGE_IDX(op0, op1, cwn, cwm, op2)		\
	({								\
		__u64 __op1 = (op1) & 3;				\
		__op1 -= (__op1 == 3);					\
		(__op1 << 6 | ((cwm) & 7) << 3 | (op2));		\
	})

#define KVM_AWM_FEATUWE_ID_WANGE	0
#define KVM_AWM_FEATUWE_ID_WANGE_SIZE	(3 * 8 * 8)

stwuct weg_mask_wange {
	__u64 addw;		/* Pointew to mask awway */
	__u32 wange;		/* Wequested wange */
	__u32 wesewved[13];
};

#endif

#endif /* __AWM_KVM_H__ */
