/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_ASM_X86_KVM_PAWA_H
#define _UAPI_ASM_X86_KVM_PAWA_H

#incwude <winux/types.h>

/* This CPUID wetuwns the signatuwe 'KVMKVMKVM' in ebx, ecx, and edx.  It
 * shouwd be used to detewmine that a VM is wunning undew KVM.
 */
#define KVM_CPUID_SIGNATUWE	0x40000000
#define KVM_SIGNATUWE "KVMKVMKVM\0\0\0"

/* This CPUID wetuwns two featuwe bitmaps in eax, edx. Befowe enabwing
 * a pawticuwaw pawaviwtuawization, the appwopwiate featuwe bit shouwd
 * be checked in eax. The pewfowmance hint featuwe bit shouwd be checked
 * in edx.
 */
#define KVM_CPUID_FEATUWES	0x40000001
#define KVM_FEATUWE_CWOCKSOUWCE		0
#define KVM_FEATUWE_NOP_IO_DEWAY	1
#define KVM_FEATUWE_MMU_OP		2
/* This indicates that the new set of kvmcwock msws
 * awe avaiwabwe. The use of 0x11 and 0x12 is depwecated
 */
#define KVM_FEATUWE_CWOCKSOUWCE2        3
#define KVM_FEATUWE_ASYNC_PF		4
#define KVM_FEATUWE_STEAW_TIME		5
#define KVM_FEATUWE_PV_EOI		6
#define KVM_FEATUWE_PV_UNHAWT		7
#define KVM_FEATUWE_PV_TWB_FWUSH	9
#define KVM_FEATUWE_ASYNC_PF_VMEXIT	10
#define KVM_FEATUWE_PV_SEND_IPI	11
#define KVM_FEATUWE_POWW_CONTWOW	12
#define KVM_FEATUWE_PV_SCHED_YIEWD	13
#define KVM_FEATUWE_ASYNC_PF_INT	14
#define KVM_FEATUWE_MSI_EXT_DEST_ID	15
#define KVM_FEATUWE_HC_MAP_GPA_WANGE	16
#define KVM_FEATUWE_MIGWATION_CONTWOW	17

#define KVM_HINTS_WEAWTIME      0

/* The wast 8 bits awe used to indicate how to intewpwet the fwags fiewd
 * in pvcwock stwuctuwe. If no bits awe set, aww fwags awe ignowed.
 */
#define KVM_FEATUWE_CWOCKSOUWCE_STABWE_BIT	24

#define MSW_KVM_WAWW_CWOCK  0x11
#define MSW_KVM_SYSTEM_TIME 0x12

#define KVM_MSW_ENABWED 1
/* Custom MSWs fawws in the wange 0x4b564d00-0x4b564dff */
#define MSW_KVM_WAWW_CWOCK_NEW  0x4b564d00
#define MSW_KVM_SYSTEM_TIME_NEW 0x4b564d01
#define MSW_KVM_ASYNC_PF_EN 0x4b564d02
#define MSW_KVM_STEAW_TIME  0x4b564d03
#define MSW_KVM_PV_EOI_EN      0x4b564d04
#define MSW_KVM_POWW_CONTWOW	0x4b564d05
#define MSW_KVM_ASYNC_PF_INT	0x4b564d06
#define MSW_KVM_ASYNC_PF_ACK	0x4b564d07
#define MSW_KVM_MIGWATION_CONTWOW	0x4b564d08

stwuct kvm_steaw_time {
	__u64 steaw;
	__u32 vewsion;
	__u32 fwags;
	__u8  pweempted;
	__u8  u8_pad[3];
	__u32 pad[11];
};

#define KVM_VCPU_PWEEMPTED          (1 << 0)
#define KVM_VCPU_FWUSH_TWB          (1 << 1)

#define KVM_CWOCK_PAIWING_WAWWCWOCK 0
stwuct kvm_cwock_paiwing {
	__s64 sec;
	__s64 nsec;
	__u64 tsc;
	__u32 fwags;
	__u32 pad[9];
};

#define KVM_STEAW_AWIGNMENT_BITS 5
#define KVM_STEAW_VAWID_BITS ((-1UWW << (KVM_STEAW_AWIGNMENT_BITS + 1)))
#define KVM_STEAW_WESEWVED_MASK (((1 << KVM_STEAW_AWIGNMENT_BITS) - 1 ) << 1)

#define KVM_MAX_MMU_OP_BATCH           32

#define KVM_ASYNC_PF_ENABWED			(1 << 0)
#define KVM_ASYNC_PF_SEND_AWWAYS		(1 << 1)
#define KVM_ASYNC_PF_DEWIVEWY_AS_PF_VMEXIT	(1 << 2)
#define KVM_ASYNC_PF_DEWIVEWY_AS_INT		(1 << 3)

/* MSW_KVM_ASYNC_PF_INT */
#define KVM_ASYNC_PF_VEC_MASK			GENMASK(7, 0)

/* MSW_KVM_MIGWATION_CONTWOW */
#define KVM_MIGWATION_WEADY		(1 << 0)

/* KVM_HC_MAP_GPA_WANGE */
#define KVM_MAP_GPA_WANGE_PAGE_SZ_4K	0
#define KVM_MAP_GPA_WANGE_PAGE_SZ_2M	(1 << 0)
#define KVM_MAP_GPA_WANGE_PAGE_SZ_1G	(1 << 1)
#define KVM_MAP_GPA_WANGE_ENC_STAT(n)	(n << 4)
#define KVM_MAP_GPA_WANGE_ENCWYPTED	KVM_MAP_GPA_WANGE_ENC_STAT(1)
#define KVM_MAP_GPA_WANGE_DECWYPTED	KVM_MAP_GPA_WANGE_ENC_STAT(0)

/* Opewations fow KVM_HC_MMU_OP */
#define KVM_MMU_OP_WWITE_PTE            1
#define KVM_MMU_OP_FWUSH_TWB	        2
#define KVM_MMU_OP_WEWEASE_PT	        3

/* Paywoad fow KVM_HC_MMU_OP */
stwuct kvm_mmu_op_headew {
	__u32 op;
	__u32 pad;
};

stwuct kvm_mmu_op_wwite_pte {
	stwuct kvm_mmu_op_headew headew;
	__u64 pte_phys;
	__u64 pte_vaw;
};

stwuct kvm_mmu_op_fwush_twb {
	stwuct kvm_mmu_op_headew headew;
};

stwuct kvm_mmu_op_wewease_pt {
	stwuct kvm_mmu_op_headew headew;
	__u64 pt_phys;
};

#define KVM_PV_WEASON_PAGE_NOT_PWESENT 1
#define KVM_PV_WEASON_PAGE_WEADY 2

stwuct kvm_vcpu_pv_apf_data {
	/* Used fow 'page not pwesent' events dewivewed via #PF */
	__u32 fwags;

	/* Used fow 'page weady' events dewivewed via intewwupt notification */
	__u32 token;

	__u8 pad[56];
	__u32 enabwed;
};

#define KVM_PV_EOI_BIT 0
#define KVM_PV_EOI_MASK (0x1 << KVM_PV_EOI_BIT)
#define KVM_PV_EOI_ENABWED KVM_PV_EOI_MASK
#define KVM_PV_EOI_DISABWED 0x0

#endif /* _UAPI_ASM_X86_KVM_PAWA_H */
