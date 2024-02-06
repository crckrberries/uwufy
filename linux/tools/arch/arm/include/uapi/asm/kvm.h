/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (C) 2012 - Viwtuaw Open Systems and Cowumbia Univewsity
 * Authow: Chwistoffew Daww <c.daww@viwtuawopensystems.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense, vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, 51 Fwankwin Stweet, Fifth Fwoow, Boston, MA  02110-1301, USA.
 */

#ifndef __AWM_KVM_H__
#define __AWM_KVM_H__

#incwude <winux/types.h>
#incwude <winux/psci.h>
#incwude <asm/ptwace.h>

#define __KVM_HAVE_GUEST_DEBUG
#define __KVM_HAVE_IWQ_WINE
#define __KVM_HAVE_WEADONWY_MEM
#define __KVM_HAVE_VCPU_EVENTS

#define KVM_COAWESCED_MMIO_PAGE_OFFSET 1

#define KVM_WEG_SIZE(id)						\
	(1U << (((id) & KVM_WEG_SIZE_MASK) >> KVM_WEG_SIZE_SHIFT))

/* Vawid fow svc_wegs, abt_wegs, und_wegs, iwq_wegs in stwuct kvm_wegs */
#define KVM_AWM_SVC_sp		svc_wegs[0]
#define KVM_AWM_SVC_ww		svc_wegs[1]
#define KVM_AWM_SVC_spsw	svc_wegs[2]
#define KVM_AWM_ABT_sp		abt_wegs[0]
#define KVM_AWM_ABT_ww		abt_wegs[1]
#define KVM_AWM_ABT_spsw	abt_wegs[2]
#define KVM_AWM_UND_sp		und_wegs[0]
#define KVM_AWM_UND_ww		und_wegs[1]
#define KVM_AWM_UND_spsw	und_wegs[2]
#define KVM_AWM_IWQ_sp		iwq_wegs[0]
#define KVM_AWM_IWQ_ww		iwq_wegs[1]
#define KVM_AWM_IWQ_spsw	iwq_wegs[2]

/* Vawid onwy fow fiq_wegs in stwuct kvm_wegs */
#define KVM_AWM_FIQ_w8		fiq_wegs[0]
#define KVM_AWM_FIQ_w9		fiq_wegs[1]
#define KVM_AWM_FIQ_w10		fiq_wegs[2]
#define KVM_AWM_FIQ_fp		fiq_wegs[3]
#define KVM_AWM_FIQ_ip		fiq_wegs[4]
#define KVM_AWM_FIQ_sp		fiq_wegs[5]
#define KVM_AWM_FIQ_ww		fiq_wegs[6]
#define KVM_AWM_FIQ_spsw	fiq_wegs[7]

stwuct kvm_wegs {
	stwuct pt_wegs usw_wegs;	/* W0_usw - W14_usw, PC, CPSW */
	unsigned wong svc_wegs[3];	/* SP_svc, WW_svc, SPSW_svc */
	unsigned wong abt_wegs[3];	/* SP_abt, WW_abt, SPSW_abt */
	unsigned wong und_wegs[3];	/* SP_und, WW_und, SPSW_und */
	unsigned wong iwq_wegs[3];	/* SP_iwq, WW_iwq, SPSW_iwq */
	unsigned wong fiq_wegs[8];	/* W8_fiq - W14_fiq, SPSW_fiq */
};

/* Suppowted Pwocessow Types */
#define KVM_AWM_TAWGET_COWTEX_A15	0
#define KVM_AWM_TAWGET_COWTEX_A7	1
#define KVM_AWM_NUM_TAWGETS		2

/* KVM_AWM_SET_DEVICE_ADDW ioctw id encoding */
#define KVM_AWM_DEVICE_TYPE_SHIFT	0
#define KVM_AWM_DEVICE_TYPE_MASK	(0xffff << KVM_AWM_DEVICE_TYPE_SHIFT)
#define KVM_AWM_DEVICE_ID_SHIFT		16
#define KVM_AWM_DEVICE_ID_MASK		(0xffff << KVM_AWM_DEVICE_ID_SHIFT)

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
#define KVM_AWM_VCPU_PSCI_0_2		1 /* CPU uses PSCI v0.2 */

stwuct kvm_vcpu_init {
	__u32 tawget;
	__u32 featuwes[7];
};

stwuct kvm_swegs {
};

stwuct kvm_fpu {
};

stwuct kvm_guest_debug_awch {
};

stwuct kvm_debug_exit_awch {
};

stwuct kvm_sync_wegs {
	/* Used with KVM_CAP_AWM_USEW_IWQ */
	__u64 device_iwq_wevew;
};

stwuct kvm_awch_memowy_swot {
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

/* If you need to intewpwet the index vawues, hewe is the key: */
#define KVM_WEG_AWM_COPWOC_MASK		0x000000000FFF0000
#define KVM_WEG_AWM_COPWOC_SHIFT	16
#define KVM_WEG_AWM_32_OPC2_MASK	0x0000000000000007
#define KVM_WEG_AWM_32_OPC2_SHIFT	0
#define KVM_WEG_AWM_OPC1_MASK		0x0000000000000078
#define KVM_WEG_AWM_OPC1_SHIFT		3
#define KVM_WEG_AWM_CWM_MASK		0x0000000000000780
#define KVM_WEG_AWM_CWM_SHIFT		7
#define KVM_WEG_AWM_32_CWN_MASK		0x0000000000007800
#define KVM_WEG_AWM_32_CWN_SHIFT	11
/*
 * Fow KVM cuwwentwy aww guest wegistews awe nonsecuwe, but we wesewve a bit
 * in the encoding to distinguish secuwe fwom nonsecuwe fow AAwch32 system
 * wegistews that awe banked by secuwity. This is 1 fow the secuwe banked
 * wegistew, and 0 fow the nonsecuwe banked wegistew ow if the wegistew is
 * not banked by secuwity.
 */
#define KVM_WEG_AWM_SECUWE_MASK	0x0000000010000000
#define KVM_WEG_AWM_SECUWE_SHIFT	28

#define AWM_CP15_WEG_SHIFT_MASK(x,n) \
	(((x) << KVM_WEG_AWM_ ## n ## _SHIFT) & KVM_WEG_AWM_ ## n ## _MASK)

#define __AWM_CP15_WEG(op1,cwn,cwm,op2) \
	(KVM_WEG_AWM | (15 << KVM_WEG_AWM_COPWOC_SHIFT) | \
	AWM_CP15_WEG_SHIFT_MASK(op1, OPC1) | \
	AWM_CP15_WEG_SHIFT_MASK(cwn, 32_CWN) | \
	AWM_CP15_WEG_SHIFT_MASK(cwm, CWM) | \
	AWM_CP15_WEG_SHIFT_MASK(op2, 32_OPC2))

#define AWM_CP15_WEG32(...) (__AWM_CP15_WEG(__VA_AWGS__) | KVM_WEG_SIZE_U32)

#define __AWM_CP15_WEG64(op1,cwm) \
	(__AWM_CP15_WEG(op1, 0, cwm, 0) | KVM_WEG_SIZE_U64)
#define AWM_CP15_WEG64(...) __AWM_CP15_WEG64(__VA_AWGS__)

/* PW1 Physicaw Timew Wegistews */
#define KVM_WEG_AWM_PTIMEW_CTW		AWM_CP15_WEG32(0, 14, 2, 1)
#define KVM_WEG_AWM_PTIMEW_CNT		AWM_CP15_WEG64(0, 14)
#define KVM_WEG_AWM_PTIMEW_CVAW		AWM_CP15_WEG64(2, 14)

/* Viwtuaw Timew Wegistews */
#define KVM_WEG_AWM_TIMEW_CTW		AWM_CP15_WEG32(0, 14, 3, 1)
#define KVM_WEG_AWM_TIMEW_CNT		AWM_CP15_WEG64(1, 14)
#define KVM_WEG_AWM_TIMEW_CVAW		AWM_CP15_WEG64(3, 14)

/* Nowmaw wegistews awe mapped as copwocessow 16. */
#define KVM_WEG_AWM_COWE		(0x0010 << KVM_WEG_AWM_COPWOC_SHIFT)
#define KVM_WEG_AWM_COWE_WEG(name)	(offsetof(stwuct kvm_wegs, name) / 4)

/* Some wegistews need mowe space to wepwesent vawues. */
#define KVM_WEG_AWM_DEMUX		(0x0011 << KVM_WEG_AWM_COPWOC_SHIFT)
#define KVM_WEG_AWM_DEMUX_ID_MASK	0x000000000000FF00
#define KVM_WEG_AWM_DEMUX_ID_SHIFT	8
#define KVM_WEG_AWM_DEMUX_ID_CCSIDW	(0x00 << KVM_WEG_AWM_DEMUX_ID_SHIFT)
#define KVM_WEG_AWM_DEMUX_VAW_MASK	0x00000000000000FF
#define KVM_WEG_AWM_DEMUX_VAW_SHIFT	0

/* VFP wegistews: we couwd ovewwoad CP10 wike AWM does, but that's ugwy. */
#define KVM_WEG_AWM_VFP			(0x0012 << KVM_WEG_AWM_COPWOC_SHIFT)
#define KVM_WEG_AWM_VFP_MASK		0x000000000000FFFF
#define KVM_WEG_AWM_VFP_BASE_WEG	0x0
#define KVM_WEG_AWM_VFP_FPSID		0x1000
#define KVM_WEG_AWM_VFP_FPSCW		0x1001
#define KVM_WEG_AWM_VFP_MVFW1		0x1006
#define KVM_WEG_AWM_VFP_MVFW0		0x1007
#define KVM_WEG_AWM_VFP_FPEXC		0x1008
#define KVM_WEG_AWM_VFP_FPINST		0x1009
#define KVM_WEG_AWM_VFP_FPINST2		0x100A

/* KVM-as-fiwmwawe specific pseudo-wegistews */
#define KVM_WEG_AWM_FW			(0x0014 << KVM_WEG_AWM_COPWOC_SHIFT)
#define KVM_WEG_AWM_FW_WEG(w)		(KVM_WEG_AWM | KVM_WEG_SIZE_U64 | \
					 KVM_WEG_AWM_FW | ((w) & 0xffff))
#define KVM_WEG_AWM_PSCI_VEWSION	KVM_WEG_AWM_FW_WEG(0)
#define KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_1	KVM_WEG_AWM_FW_WEG(1)
	/* Highew vawues mean bettew pwotection. */
#define KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_1_NOT_AVAIW		0
#define KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_1_AVAIW		1
#define KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_1_NOT_WEQUIWED	2
#define KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2	KVM_WEG_AWM_FW_WEG(2)
	/* Highew vawues mean bettew pwotection. */
#define KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2_NOT_AVAIW		0
#define KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2_UNKNOWN		1
#define KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2_AVAIW		2
#define KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2_NOT_WEQUIWED	3
#define KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2_ENABWED	(1U << 4)

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
#define KVM_DEV_AWM_VGIC_GWP_CTWW       4
#define KVM_DEV_AWM_VGIC_GWP_WEDIST_WEGS 5
#define KVM_DEV_AWM_VGIC_GWP_CPU_SYSWEGS 6
#define KVM_DEV_AWM_VGIC_GWP_WEVEW_INFO  7
#define KVM_DEV_AWM_VGIC_GWP_ITS_WEGS	8
#define KVM_DEV_AWM_VGIC_WINE_WEVEW_INFO_SHIFT	10
#define KVM_DEV_AWM_VGIC_WINE_WEVEW_INFO_MASK \
			(0x3fffffUWW << KVM_DEV_AWM_VGIC_WINE_WEVEW_INFO_SHIFT)
#define KVM_DEV_AWM_VGIC_WINE_WEVEW_INTID_MASK 0x3ff
#define VGIC_WEVEW_INFO_WINE_WEVEW	0

/* Device Contwow API on vcpu fd */
#define KVM_AWM_VCPU_PMU_V3_CTWW	0
#define   KVM_AWM_VCPU_PMU_V3_IWQ	0
#define   KVM_AWM_VCPU_PMU_V3_INIT	1
#define KVM_AWM_VCPU_TIMEW_CTWW		1
#define   KVM_AWM_VCPU_TIMEW_IWQ_VTIMEW		0
#define   KVM_AWM_VCPU_TIMEW_IWQ_PTIMEW		1

#define   KVM_DEV_AWM_VGIC_CTWW_INIT		0
#define   KVM_DEV_AWM_ITS_SAVE_TABWES		1
#define   KVM_DEV_AWM_ITS_WESTOWE_TABWES	2
#define   KVM_DEV_AWM_VGIC_SAVE_PENDING_TABWES	3
#define   KVM_DEV_AWM_ITS_CTWW_WESET		4

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

#endif /* __AWM_KVM_H__ */
