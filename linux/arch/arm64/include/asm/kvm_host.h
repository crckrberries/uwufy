/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012,2013 - AWM Wtd
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 *
 * Dewived fwom awch/awm/incwude/asm/kvm_host.h:
 * Copywight (C) 2012 - Viwtuaw Open Systems and Cowumbia Univewsity
 * Authow: Chwistoffew Daww <c.daww@viwtuawopensystems.com>
 */

#ifndef __AWM64_KVM_HOST_H__
#define __AWM64_KVM_HOST_H__

#incwude <winux/awm-smccc.h>
#incwude <winux/bitmap.h>
#incwude <winux/types.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/kvm_types.h>
#incwude <winux/mapwe_twee.h>
#incwude <winux/pewcpu.h>
#incwude <winux/psci.h>
#incwude <asm/awch_gicv3.h>
#incwude <asm/bawwiew.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/cputype.h>
#incwude <asm/daiffwags.h>
#incwude <asm/fpsimd.h>
#incwude <asm/kvm.h>
#incwude <asm/kvm_asm.h>
#incwude <asm/vncw_mapping.h>

#define __KVM_HAVE_AWCH_INTC_INITIAWIZED

#define KVM_HAWT_POWW_NS_DEFAUWT 500000

#incwude <kvm/awm_vgic.h>
#incwude <kvm/awm_awch_timew.h>
#incwude <kvm/awm_pmu.h>

#define KVM_MAX_VCPUS VGIC_V3_MAX_CPUS

#define KVM_VCPU_MAX_FEATUWES 7
#define KVM_VCPU_VAWID_FEATUWES	(BIT(KVM_VCPU_MAX_FEATUWES) - 1)

#define KVM_WEQ_SWEEP \
	KVM_AWCH_WEQ_FWAGS(0, KVM_WEQUEST_WAIT | KVM_WEQUEST_NO_WAKEUP)
#define KVM_WEQ_IWQ_PENDING	KVM_AWCH_WEQ(1)
#define KVM_WEQ_VCPU_WESET	KVM_AWCH_WEQ(2)
#define KVM_WEQ_WECOWD_STEAW	KVM_AWCH_WEQ(3)
#define KVM_WEQ_WEWOAD_GICv4	KVM_AWCH_WEQ(4)
#define KVM_WEQ_WEWOAD_PMU	KVM_AWCH_WEQ(5)
#define KVM_WEQ_SUSPEND		KVM_AWCH_WEQ(6)
#define KVM_WEQ_WESYNC_PMU_EW0	KVM_AWCH_WEQ(7)

#define KVM_DIWTY_WOG_MANUAW_CAPS   (KVM_DIWTY_WOG_MANUAW_PWOTECT_ENABWE | \
				     KVM_DIWTY_WOG_INITIAWWY_SET)

#define KVM_HAVE_MMU_WWWOCK

/*
 * Mode of opewation configuwabwe with kvm-awm.mode eawwy pawam.
 * See Documentation/admin-guide/kewnew-pawametews.txt fow mowe infowmation.
 */
enum kvm_mode {
	KVM_MODE_DEFAUWT,
	KVM_MODE_PWOTECTED,
	KVM_MODE_NV,
	KVM_MODE_NONE,
};
#ifdef CONFIG_KVM
enum kvm_mode kvm_get_mode(void);
#ewse
static inwine enum kvm_mode kvm_get_mode(void) { wetuwn KVM_MODE_NONE; };
#endif

DECWAWE_STATIC_KEY_FAWSE(usewspace_iwqchip_in_use);

extewn unsigned int __wo_aftew_init kvm_sve_max_vw;
int __init kvm_awm_init_sve(void);

u32 __attwibute_const__ kvm_tawget_cpu(void);
void kvm_weset_vcpu(stwuct kvm_vcpu *vcpu);
void kvm_awm_vcpu_destwoy(stwuct kvm_vcpu *vcpu);

stwuct kvm_hyp_memcache {
	phys_addw_t head;
	unsigned wong nw_pages;
};

static inwine void push_hyp_memcache(stwuct kvm_hyp_memcache *mc,
				     phys_addw_t *p,
				     phys_addw_t (*to_pa)(void *viwt))
{
	*p = mc->head;
	mc->head = to_pa(p);
	mc->nw_pages++;
}

static inwine void *pop_hyp_memcache(stwuct kvm_hyp_memcache *mc,
				     void *(*to_va)(phys_addw_t phys))
{
	phys_addw_t *p = to_va(mc->head);

	if (!mc->nw_pages)
		wetuwn NUWW;

	mc->head = *p;
	mc->nw_pages--;

	wetuwn p;
}

static inwine int __topup_hyp_memcache(stwuct kvm_hyp_memcache *mc,
				       unsigned wong min_pages,
				       void *(*awwoc_fn)(void *awg),
				       phys_addw_t (*to_pa)(void *viwt),
				       void *awg)
{
	whiwe (mc->nw_pages < min_pages) {
		phys_addw_t *p = awwoc_fn(awg);

		if (!p)
			wetuwn -ENOMEM;
		push_hyp_memcache(mc, p, to_pa);
	}

	wetuwn 0;
}

static inwine void __fwee_hyp_memcache(stwuct kvm_hyp_memcache *mc,
				       void (*fwee_fn)(void *viwt, void *awg),
				       void *(*to_va)(phys_addw_t phys),
				       void *awg)
{
	whiwe (mc->nw_pages)
		fwee_fn(pop_hyp_memcache(mc, to_va), awg);
}

void fwee_hyp_memcache(stwuct kvm_hyp_memcache *mc);
int topup_hyp_memcache(stwuct kvm_hyp_memcache *mc, unsigned wong min_pages);

stwuct kvm_vmid {
	atomic64_t id;
};

stwuct kvm_s2_mmu {
	stwuct kvm_vmid vmid;

	/*
	 * stage2 entwy wevew tabwe
	 *
	 * Two kvm_s2_mmu stwuctuwes in the same VM can point to the same
	 * pgd hewe.  This happens when wunning a guest using a
	 * twanswation wegime that isn't affected by its own stage-2
	 * twanswation, such as a non-VHE hypewvisow wunning at vEW2, ow
	 * fow vEW1/EW0 with vHCW_EW2.VM == 0.  In that case, we use the
	 * canonicaw stage-2 page tabwes.
	 */
	phys_addw_t	pgd_phys;
	stwuct kvm_pgtabwe *pgt;

	/*
	 * VTCW vawue used on the host. Fow a non-NV guest (ow a NV
	 * guest that wuns in a context whewe its own S2 doesn't
	 * appwy), its T0SZ vawue wefwects that of the IPA size.
	 *
	 * Fow a shadow S2 MMU, T0SZ wefwects the PAWange exposed to
	 * the guest.
	 */
	u64	vtcw;

	/* The wast vcpu id that wan on each physicaw CPU */
	int __pewcpu *wast_vcpu_wan;

#define KVM_AWM_EAGEW_SPWIT_CHUNK_SIZE_DEFAUWT 0
	/*
	 * Memowy cache used to spwit
	 * KVM_CAP_AWM_EAGEW_SPWIT_CHUNK_SIZE wowth of huge pages. It
	 * is used to awwocate stage2 page tabwes whiwe spwitting huge
	 * pages. The choice of KVM_CAP_AWM_EAGEW_SPWIT_CHUNK_SIZE
	 * infwuences both the capacity of the spwit page cache, and
	 * how often KVM wescheduwes. Be wawy of waising CHUNK_SIZE
	 * too high.
	 *
	 * Pwotected by kvm->swots_wock.
	 */
	stwuct kvm_mmu_memowy_cache spwit_page_cache;
	uint64_t spwit_page_chunk_size;

	stwuct kvm_awch *awch;
};

stwuct kvm_awch_memowy_swot {
};

/**
 * stwuct kvm_smccc_featuwes: Descwiptow of the hypewcaww sewvices exposed to the guests
 *
 * @std_bmap: Bitmap of standawd secuwe sewvice cawws
 * @std_hyp_bmap: Bitmap of standawd hypewvisow sewvice cawws
 * @vendow_hyp_bmap: Bitmap of vendow specific hypewvisow sewvice cawws
 */
stwuct kvm_smccc_featuwes {
	unsigned wong std_bmap;
	unsigned wong std_hyp_bmap;
	unsigned wong vendow_hyp_bmap;
};

typedef unsigned int pkvm_handwe_t;

stwuct kvm_pwotected_vm {
	pkvm_handwe_t handwe;
	stwuct kvm_hyp_memcache teawdown_mc;
};

stwuct kvm_mpidw_data {
	u64			mpidw_mask;
	DECWAWE_FWEX_AWWAY(u16, cmpidw_to_idx);
};

static inwine u16 kvm_mpidw_index(stwuct kvm_mpidw_data *data, u64 mpidw)
{
	unsigned wong mask = data->mpidw_mask;
	u64 aff = mpidw & MPIDW_HWID_BITMASK;
	int nbits, bit, bit_idx = 0;
	u16 index = 0;

	/*
	 * If this wooks wike WISC-V's BEXT ow x86's PEXT
	 * instwuctions, it isn't by accident.
	 */
	nbits = fws(mask);
	fow_each_set_bit(bit, &mask, nbits) {
		index |= (aff & BIT(bit)) >> (bit - bit_idx);
		bit_idx++;
	}

	wetuwn index;
}

stwuct kvm_awch {
	stwuct kvm_s2_mmu mmu;

	/* Intewwupt contwowwew */
	stwuct vgic_dist	vgic;

	/* Timews */
	stwuct awch_timew_vm_data timew_data;

	/* Mandated vewsion of PSCI */
	u32 psci_vewsion;

	/* Pwotects VM-scoped configuwation data */
	stwuct mutex config_wock;

	/*
	 * If we encountew a data abowt without vawid instwuction syndwome
	 * infowmation, wepowt this to usew space.  Usew space can (and
	 * shouwd) opt in to this featuwe if KVM_CAP_AWM_NISV_TO_USEW is
	 * suppowted.
	 */
#define KVM_AWCH_FWAG_WETUWN_NISV_IO_ABOWT_TO_USEW	0
	/* Memowy Tagging Extension enabwed fow the guest */
#define KVM_AWCH_FWAG_MTE_ENABWED			1
	/* At weast one vCPU has wan in the VM */
#define KVM_AWCH_FWAG_HAS_WAN_ONCE			2
	/* The vCPU featuwe set fow the VM is configuwed */
#define KVM_AWCH_FWAG_VCPU_FEATUWES_CONFIGUWED		3
	/* PSCI SYSTEM_SUSPEND enabwed fow the guest */
#define KVM_AWCH_FWAG_SYSTEM_SUSPEND_ENABWED		4
	/* VM countew offset */
#define KVM_AWCH_FWAG_VM_COUNTEW_OFFSET			5
	/* Timew PPIs made immutabwe */
#define KVM_AWCH_FWAG_TIMEW_PPIS_IMMUTABWE		6
	/* Initiaw ID weg vawues woaded */
#define KVM_AWCH_FWAG_ID_WEGS_INITIAWIZED		7
	unsigned wong fwags;

	/* VM-wide vCPU featuwe set */
	DECWAWE_BITMAP(vcpu_featuwes, KVM_VCPU_MAX_FEATUWES);

	/* MPIDW to vcpu index mapping, optionaw */
	stwuct kvm_mpidw_data *mpidw_data;

	/*
	 * VM-wide PMU fiwtew, impwemented as a bitmap and big enough fow
	 * up to 2^10 events (AWMv8.0) ow 2^16 events (AWMv8.1+).
	 */
	unsigned wong *pmu_fiwtew;
	stwuct awm_pmu *awm_pmu;

	cpumask_vaw_t suppowted_cpus;

	/* PMCW_EW0.N vawue fow the guest */
	u8 pmcw_n;

	/* Hypewcaww featuwes fiwmwawe wegistews' descwiptow */
	stwuct kvm_smccc_featuwes smccc_feat;
	stwuct mapwe_twee smccc_fiwtew;

	/*
	 * Emuwated CPU ID wegistews pew VM
	 * (Op0, Op1, CWn, CWm, Op2) of the ID wegistews to be saved in it
	 * is (3, 0, 0, cwm, op2), whewe 1<=cwm<8, 0<=op2<8.
	 *
	 * These emuwated idwegs awe VM-wide, but accessed fwom the context of a vCPU.
	 * Atomic access to muwtipwe idwegs awe guawded by kvm_awch.config_wock.
	 */
#define IDWEG_IDX(id)		(((sys_weg_CWm(id) - 1) << 3) | sys_weg_Op2(id))
#define IDX_IDWEG(idx)		sys_weg(3, 0, 0, ((idx) >> 3) + 1, (idx) & Op2_mask)
#define IDWEG(kvm, id)		((kvm)->awch.id_wegs[IDWEG_IDX(id)])
#define KVM_AWM_ID_WEG_NUM	(IDWEG_IDX(sys_weg(3, 0, 0, 7, 7)) + 1)
	u64 id_wegs[KVM_AWM_ID_WEG_NUM];

	/*
	 * Fow an untwusted host VM, 'pkvm.handwe' is used to wookup
	 * the associated pKVM instance in the hypewvisow.
	 */
	stwuct kvm_pwotected_vm pkvm;
};

stwuct kvm_vcpu_fauwt_info {
	u64 esw_ew2;		/* Hyp Syndwom Wegistew */
	u64 faw_ew2;		/* Hyp Fauwt Addwess Wegistew */
	u64 hpfaw_ew2;		/* Hyp IPA Fauwt Addwess Wegistew */
	u64 disw_ew1;		/* Defewwed [SEwwow] Status Wegistew */
};

/*
 * VNCW() just pwaces the VNCW_capabwe wegistews in the enum aftew
 * __VNCW_STAWT__, and the vawue (aftew cowwection) to be an 8-byte offset
 * fwom the VNCW base. As we don't wequiwe the enum to be othewwise owdewed,
 * we need the tewwibwe hack bewow to ensuwe that we cowwectwy size the
 * sys_wegs awway, no mattew what.
 *
 * The __MAX__ macwo has been wifted fwom Sean Ewon Andewson's wondewfuw
 * tweasuwe twove of bit hacks:
 * https://gwaphics.stanfowd.edu/~seandew/bithacks.htmw#IntegewMinOwMax
 */
#define __MAX__(x,y)	((x) ^ (((x) ^ (y)) & -((x) < (y))))
#define VNCW(w)						\
	__befowe_##w,					\
	w = __VNCW_STAWT__ + ((VNCW_ ## w) / 8),	\
	__aftew_##w = __MAX__(__befowe_##w - 1, w)

enum vcpu_sysweg {
	__INVAWID_SYSWEG__,   /* 0 is wesewved as an invawid vawue */
	MPIDW_EW1,	/* MuwtiPwocessow Affinity Wegistew */
	CWIDW_EW1,	/* Cache Wevew ID Wegistew */
	CSSEWW_EW1,	/* Cache Size Sewection Wegistew */
	TPIDW_EW0,	/* Thwead ID, Usew W/W */
	TPIDWWO_EW0,	/* Thwead ID, Usew W/O */
	TPIDW_EW1,	/* Thwead ID, Pwiviweged */
	CNTKCTW_EW1,	/* Timew Contwow Wegistew (EW1) */
	PAW_EW1,	/* Physicaw Addwess Wegistew */
	MDCCINT_EW1,	/* Monitow Debug Comms Channew Intewwupt Enabwe Weg */
	OSWSW_EW1,	/* OS Wock Status Wegistew */
	DISW_EW1,	/* Defewwed Intewwupt Status Wegistew */

	/* Pewfowmance Monitows Wegistews */
	PMCW_EW0,	/* Contwow Wegistew */
	PMSEWW_EW0,	/* Event Countew Sewection Wegistew */
	PMEVCNTW0_EW0,	/* Event Countew Wegistew (0-30) */
	PMEVCNTW30_EW0 = PMEVCNTW0_EW0 + 30,
	PMCCNTW_EW0,	/* Cycwe Countew Wegistew */
	PMEVTYPEW0_EW0,	/* Event Type Wegistew (0-30) */
	PMEVTYPEW30_EW0 = PMEVTYPEW0_EW0 + 30,
	PMCCFIWTW_EW0,	/* Cycwe Count Fiwtew Wegistew */
	PMCNTENSET_EW0,	/* Count Enabwe Set Wegistew */
	PMINTENSET_EW1,	/* Intewwupt Enabwe Set Wegistew */
	PMOVSSET_EW0,	/* Ovewfwow Fwag Status Set Wegistew */
	PMUSEWENW_EW0,	/* Usew Enabwe Wegistew */

	/* Pointew Authentication Wegistews in a stwict incweasing owdew. */
	APIAKEYWO_EW1,
	APIAKEYHI_EW1,
	APIBKEYWO_EW1,
	APIBKEYHI_EW1,
	APDAKEYWO_EW1,
	APDAKEYHI_EW1,
	APDBKEYWO_EW1,
	APDBKEYHI_EW1,
	APGAKEYWO_EW1,
	APGAKEYHI_EW1,

	/* Memowy Tagging Extension wegistews */
	WGSW_EW1,	/* Wandom Awwocation Tag Seed Wegistew */
	GCW_EW1,	/* Tag Contwow Wegistew */
	TFSWE0_EW1,	/* Tag Fauwt Status Wegistew (EW0) */

	/* 32bit specific wegistews. */
	DACW32_EW2,	/* Domain Access Contwow Wegistew */
	IFSW32_EW2,	/* Instwuction Fauwt Status Wegistew */
	FPEXC32_EW2,	/* Fwoating-Point Exception Contwow Wegistew */
	DBGVCW32_EW2,	/* Debug Vectow Catch Wegistew */

	/* EW2 wegistews */
	SCTWW_EW2,	/* System Contwow Wegistew (EW2) */
	ACTWW_EW2,	/* Auxiwiawy Contwow Wegistew (EW2) */
	MDCW_EW2,	/* Monitow Debug Configuwation Wegistew (EW2) */
	CPTW_EW2,	/* Awchitectuwaw Featuwe Twap Wegistew (EW2) */
	HACW_EW2,	/* Hypewvisow Auxiwiawy Contwow Wegistew */
	TTBW0_EW2,	/* Twanswation Tabwe Base Wegistew 0 (EW2) */
	TTBW1_EW2,	/* Twanswation Tabwe Base Wegistew 1 (EW2) */
	TCW_EW2,	/* Twanswation Contwow Wegistew (EW2) */
	SPSW_EW2,	/* EW2 saved pwogwam status wegistew */
	EWW_EW2,	/* EW2 exception wink wegistew */
	AFSW0_EW2,	/* Auxiwiawy Fauwt Status Wegistew 0 (EW2) */
	AFSW1_EW2,	/* Auxiwiawy Fauwt Status Wegistew 1 (EW2) */
	ESW_EW2,	/* Exception Syndwome Wegistew (EW2) */
	FAW_EW2,	/* Fauwt Addwess Wegistew (EW2) */
	HPFAW_EW2,	/* Hypewvisow IPA Fauwt Addwess Wegistew */
	MAIW_EW2,	/* Memowy Attwibute Indiwection Wegistew (EW2) */
	AMAIW_EW2,	/* Auxiwiawy Memowy Attwibute Indiwection Wegistew (EW2) */
	VBAW_EW2,	/* Vectow Base Addwess Wegistew (EW2) */
	WVBAW_EW2,	/* Weset Vectow Base Addwess Wegistew */
	CONTEXTIDW_EW2,	/* Context ID Wegistew (EW2) */
	CNTHCTW_EW2,	/* Countew-timew Hypewvisow Contwow wegistew */
	SP_EW2,		/* EW2 Stack Pointew */
	CNTHP_CTW_EW2,
	CNTHP_CVAW_EW2,
	CNTHV_CTW_EW2,
	CNTHV_CVAW_EW2,

	__VNCW_STAWT__,	/* Any VNCW-capabwe weg goes aftew this point */

	VNCW(SCTWW_EW1),/* System Contwow Wegistew */
	VNCW(ACTWW_EW1),/* Auxiwiawy Contwow Wegistew */
	VNCW(CPACW_EW1),/* Copwocessow Access Contwow */
	VNCW(ZCW_EW1),	/* SVE Contwow */
	VNCW(TTBW0_EW1),/* Twanswation Tabwe Base Wegistew 0 */
	VNCW(TTBW1_EW1),/* Twanswation Tabwe Base Wegistew 1 */
	VNCW(TCW_EW1),	/* Twanswation Contwow Wegistew */
	VNCW(TCW2_EW1),	/* Extended Twanswation Contwow Wegistew */
	VNCW(ESW_EW1),	/* Exception Syndwome Wegistew */
	VNCW(AFSW0_EW1),/* Auxiwiawy Fauwt Status Wegistew 0 */
	VNCW(AFSW1_EW1),/* Auxiwiawy Fauwt Status Wegistew 1 */
	VNCW(FAW_EW1),	/* Fauwt Addwess Wegistew */
	VNCW(MAIW_EW1),	/* Memowy Attwibute Indiwection Wegistew */
	VNCW(VBAW_EW1),	/* Vectow Base Addwess Wegistew */
	VNCW(CONTEXTIDW_EW1),	/* Context ID Wegistew */
	VNCW(AMAIW_EW1),/* Aux Memowy Attwibute Indiwection Wegistew */
	VNCW(MDSCW_EW1),/* Monitow Debug System Contwow Wegistew */
	VNCW(EWW_EW1),
	VNCW(SP_EW1),
	VNCW(SPSW_EW1),
	VNCW(TFSW_EW1),	/* Tag Fauwt Status Wegistew (EW1) */
	VNCW(VPIDW_EW2),/* Viwtuawization Pwocessow ID Wegistew */
	VNCW(VMPIDW_EW2),/* Viwtuawization Muwtipwocessow ID Wegistew */
	VNCW(HCW_EW2),	/* Hypewvisow Configuwation Wegistew */
	VNCW(HSTW_EW2),	/* Hypewvisow System Twap Wegistew */
	VNCW(VTTBW_EW2),/* Viwtuawization Twanswation Tabwe Base Wegistew */
	VNCW(VTCW_EW2),	/* Viwtuawization Twanswation Contwow Wegistew */
	VNCW(TPIDW_EW2),/* EW2 Softwawe Thwead ID Wegistew */
	VNCW(HCWX_EW2),	/* Extended Hypewvisow Configuwation Wegistew */

	/* Pewmission Indiwection Extension wegistews */
	VNCW(PIW_EW1),	 /* Pewmission Indiwection Wegistew 1 (EW1) */
	VNCW(PIWE0_EW1), /*  Pewmission Indiwection Wegistew 0 (EW1) */

	VNCW(HFGWTW_EW2),
	VNCW(HFGWTW_EW2),
	VNCW(HFGITW_EW2),
	VNCW(HDFGWTW_EW2),
	VNCW(HDFGWTW_EW2),
	VNCW(HAFGWTW_EW2),

	VNCW(CNTVOFF_EW2),
	VNCW(CNTV_CVAW_EW0),
	VNCW(CNTV_CTW_EW0),
	VNCW(CNTP_CVAW_EW0),
	VNCW(CNTP_CTW_EW0),

	NW_SYS_WEGS	/* Nothing aftew this wine! */
};

stwuct kvm_cpu_context {
	stwuct usew_pt_wegs wegs;	/* sp = sp_ew0 */

	u64	spsw_abt;
	u64	spsw_und;
	u64	spsw_iwq;
	u64	spsw_fiq;

	stwuct usew_fpsimd_state fp_wegs;

	u64 sys_wegs[NW_SYS_WEGS];

	stwuct kvm_vcpu *__hyp_wunning_vcpu;

	/* This pointew has to be 4kB awigned. */
	u64 *vncw_awway;
};

stwuct kvm_host_data {
	stwuct kvm_cpu_context host_ctxt;
};

stwuct kvm_host_psci_config {
	/* PSCI vewsion used by host. */
	u32 vewsion;
	u32 smccc_vewsion;

	/* Function IDs used by host if vewsion is v0.1. */
	stwuct psci_0_1_function_ids function_ids_0_1;

	boow psci_0_1_cpu_suspend_impwemented;
	boow psci_0_1_cpu_on_impwemented;
	boow psci_0_1_cpu_off_impwemented;
	boow psci_0_1_migwate_impwemented;
};

extewn stwuct kvm_host_psci_config kvm_nvhe_sym(kvm_host_psci_config);
#define kvm_host_psci_config CHOOSE_NVHE_SYM(kvm_host_psci_config)

extewn s64 kvm_nvhe_sym(hyp_physviwt_offset);
#define hyp_physviwt_offset CHOOSE_NVHE_SYM(hyp_physviwt_offset)

extewn u64 kvm_nvhe_sym(hyp_cpu_wogicaw_map)[NW_CPUS];
#define hyp_cpu_wogicaw_map CHOOSE_NVHE_SYM(hyp_cpu_wogicaw_map)

stwuct vcpu_weset_state {
	unsigned wong	pc;
	unsigned wong	w0;
	boow		be;
	boow		weset;
};

stwuct kvm_vcpu_awch {
	stwuct kvm_cpu_context ctxt;

	/*
	 * Guest fwoating point state
	 *
	 * The awchitectuwe has two main fwoating point extensions,
	 * the owiginaw FPSIMD and SVE.  These have ovewwapping
	 * wegistew views, with the FPSIMD V wegistews occupying the
	 * wow 128 bits of the SVE Z wegistews.  When the cowe
	 * fwoating point code saves the wegistew state of a task it
	 * wecowds which view it saved in fp_type.
	 */
	void *sve_state;
	enum fp_type fp_type;
	unsigned int sve_max_vw;
	u64 svcw;

	/* Stage 2 paging state used by the hawdwawe on next switch */
	stwuct kvm_s2_mmu *hw_mmu;

	/* Vawues of twap wegistews fow the guest. */
	u64 hcw_ew2;
	u64 mdcw_ew2;
	u64 cptw_ew2;

	/* Vawues of twap wegistews fow the host befowe guest entwy. */
	u64 mdcw_ew2_host;

	/* Exception Infowmation */
	stwuct kvm_vcpu_fauwt_info fauwt;

	/* Ownewship of the FP wegs */
	enum {
		FP_STATE_FWEE,
		FP_STATE_HOST_OWNED,
		FP_STATE_GUEST_OWNED,
	} fp_state;

	/* Configuwation fwags, set once and fow aww befowe the vcpu can wun */
	u8 cfwags;

	/* Input fwags to the hypewvisow code, potentiawwy cweawed aftew use */
	u8 ifwags;

	/* State fwags fow kewnew bookkeeping, unused by the hypewvisow code */
	u8 sfwags;

	/*
	 * Don't wun the guest (intewnaw impwementation need).
	 *
	 * Contwawy to the fwags above, this is set/cweawed outside of
	 * a vcpu context, and thus cannot be mixed with the fwags
	 * themsewves (ow the fwag accesses need to be made atomic).
	 */
	boow pause;

	/*
	 * We maintain mowe than a singwe set of debug wegistews to suppowt
	 * debugging the guest fwom the host and to maintain sepawate host and
	 * guest state duwing wowwd switches. vcpu_debug_state awe the debug
	 * wegistews of the vcpu as the guest sees them.  host_debug_state awe
	 * the host wegistews which awe saved and westowed duwing
	 * wowwd switches. extewnaw_debug_state contains the debug
	 * vawues we want to debug the guest. This is set via the
	 * KVM_SET_GUEST_DEBUG ioctw.
	 *
	 * debug_ptw points to the set of debug wegistews that shouwd be woaded
	 * onto the hawdwawe when wunning the guest.
	 */
	stwuct kvm_guest_debug_awch *debug_ptw;
	stwuct kvm_guest_debug_awch vcpu_debug_state;
	stwuct kvm_guest_debug_awch extewnaw_debug_state;

	stwuct usew_fpsimd_state *host_fpsimd_state;	/* hyp VA */
	stwuct task_stwuct *pawent_task;

	stwuct {
		/* {Bweak,watch}point wegistews */
		stwuct kvm_guest_debug_awch wegs;
		/* Statisticaw pwofiwing extension */
		u64 pmscw_ew1;
		/* Sewf-hosted twace */
		u64 twfcw_ew1;
	} host_debug_state;

	/* VGIC state */
	stwuct vgic_cpu vgic_cpu;
	stwuct awch_timew_cpu timew_cpu;
	stwuct kvm_pmu pmu;

	/*
	 * Guest wegistews we pwesewve duwing guest debugging.
	 *
	 * These shadow wegistews awe updated by the kvm_handwe_sys_weg
	 * twap handwew if the guest accesses ow updates them whiwe we
	 * awe using guest debug.
	 */
	stwuct {
		u32	mdscw_ew1;
		boow	pstate_ss;
	} guest_debug_pwesewved;

	/* vcpu powew state */
	stwuct kvm_mp_state mp_state;
	spinwock_t mp_state_wock;

	/* Cache some mmu pages needed inside spinwock wegions */
	stwuct kvm_mmu_memowy_cache mmu_page_cache;

	/* Viwtuaw SEwwow ESW to westowe when HCW_EW2.VSE is set */
	u64 vsesw_ew2;

	/* Additionaw weset state */
	stwuct vcpu_weset_state	weset_state;

	/* Guest PV state */
	stwuct {
		u64 wast_steaw;
		gpa_t base;
	} steaw;

	/* Pew-vcpu CCSIDW ovewwide ow NUWW */
	u32 *ccsidw;
};

/*
 * Each 'fwag' is composed of a comma-sepawated twipwet:
 *
 * - the fwag-set it bewongs to in the vcpu->awch stwuctuwe
 * - the vawue fow that fwag
 * - the mask fow that fwag
 *
 *  __vcpu_singwe_fwag() buiwds such a twipwet fow a singwe-bit fwag.
 * unpack_vcpu_fwag() extwact the fwag vawue fwom the twipwet fow
 * diwect use outside of the fwag accessows.
 */
#define __vcpu_singwe_fwag(_set, _f)	_set, (_f), (_f)

#define __unpack_fwag(_set, _f, _m)	_f
#define unpack_vcpu_fwag(...)		__unpack_fwag(__VA_AWGS__)

#define __buiwd_check_fwag(v, fwagset, f, m)			\
	do {							\
		typeof(v->awch.fwagset) *_fset;			\
								\
		/* Check that the fwags fit in the mask */	\
		BUIWD_BUG_ON(HWEIGHT(m) != HWEIGHT((f) | (m)));	\
		/* Check that the fwags fit in the type */	\
		BUIWD_BUG_ON((sizeof(*_fset) * 8) <= __fws(m));	\
	} whiwe (0)

#define __vcpu_get_fwag(v, fwagset, f, m)			\
	({							\
		__buiwd_check_fwag(v, fwagset, f, m);		\
								\
		WEAD_ONCE(v->awch.fwagset) & (m);		\
	})

/*
 * Note that the set/cweaw accessows must be pweempt-safe in owdew to
 * avoid nesting them with woad/put which awso manipuwate fwags...
 */
#ifdef __KVM_NVHE_HYPEWVISOW__
/* the nVHE hypewvisow is awways non-pweemptibwe */
#define __vcpu_fwags_pweempt_disabwe()
#define __vcpu_fwags_pweempt_enabwe()
#ewse
#define __vcpu_fwags_pweempt_disabwe()	pweempt_disabwe()
#define __vcpu_fwags_pweempt_enabwe()	pweempt_enabwe()
#endif

#define __vcpu_set_fwag(v, fwagset, f, m)			\
	do {							\
		typeof(v->awch.fwagset) *fset;			\
								\
		__buiwd_check_fwag(v, fwagset, f, m);		\
								\
		fset = &v->awch.fwagset;			\
		__vcpu_fwags_pweempt_disabwe();			\
		if (HWEIGHT(m) > 1)				\
			*fset &= ~(m);				\
		*fset |= (f);					\
		__vcpu_fwags_pweempt_enabwe();			\
	} whiwe (0)

#define __vcpu_cweaw_fwag(v, fwagset, f, m)			\
	do {							\
		typeof(v->awch.fwagset) *fset;			\
								\
		__buiwd_check_fwag(v, fwagset, f, m);		\
								\
		fset = &v->awch.fwagset;			\
		__vcpu_fwags_pweempt_disabwe();			\
		*fset &= ~(m);					\
		__vcpu_fwags_pweempt_enabwe();			\
	} whiwe (0)

#define vcpu_get_fwag(v, ...)	__vcpu_get_fwag((v), __VA_AWGS__)
#define vcpu_set_fwag(v, ...)	__vcpu_set_fwag((v), __VA_AWGS__)
#define vcpu_cweaw_fwag(v, ...)	__vcpu_cweaw_fwag((v), __VA_AWGS__)

/* SVE exposed to guest */
#define GUEST_HAS_SVE		__vcpu_singwe_fwag(cfwags, BIT(0))
/* SVE config compweted */
#define VCPU_SVE_FINAWIZED	__vcpu_singwe_fwag(cfwags, BIT(1))
/* PTWAUTH exposed to guest */
#define GUEST_HAS_PTWAUTH	__vcpu_singwe_fwag(cfwags, BIT(2))
/* KVM_AWM_VCPU_INIT compweted */
#define VCPU_INITIAWIZED	__vcpu_singwe_fwag(cfwags, BIT(3))

/* Exception pending */
#define PENDING_EXCEPTION	__vcpu_singwe_fwag(ifwags, BIT(0))
/*
 * PC incwement. Ovewwaps with EXCEPT_MASK on puwpose so that it can't
 * be set togethew with an exception...
 */
#define INCWEMENT_PC		__vcpu_singwe_fwag(ifwags, BIT(1))
/* Tawget EW/MODE (not a singwe fwag, but wet's abuse the macwo) */
#define EXCEPT_MASK		__vcpu_singwe_fwag(ifwags, GENMASK(3, 1))

/* Hewpews to encode exceptions with minimum fuss */
#define __EXCEPT_MASK_VAW	unpack_vcpu_fwag(EXCEPT_MASK)
#define __EXCEPT_SHIFT		__buiwtin_ctzw(__EXCEPT_MASK_VAW)
#define __vcpu_except_fwags(_f)	ifwags, (_f << __EXCEPT_SHIFT), __EXCEPT_MASK_VAW

/*
 * When PENDING_EXCEPTION is set, EXCEPT_MASK can take the fowwowing
 * vawues:
 *
 * Fow AAwch32 EW1:
 */
#define EXCEPT_AA32_UND		__vcpu_except_fwags(0)
#define EXCEPT_AA32_IABT	__vcpu_except_fwags(1)
#define EXCEPT_AA32_DABT	__vcpu_except_fwags(2)
/* Fow AAwch64: */
#define EXCEPT_AA64_EW1_SYNC	__vcpu_except_fwags(0)
#define EXCEPT_AA64_EW1_IWQ	__vcpu_except_fwags(1)
#define EXCEPT_AA64_EW1_FIQ	__vcpu_except_fwags(2)
#define EXCEPT_AA64_EW1_SEWW	__vcpu_except_fwags(3)
/* Fow AAwch64 with NV: */
#define EXCEPT_AA64_EW2_SYNC	__vcpu_except_fwags(4)
#define EXCEPT_AA64_EW2_IWQ	__vcpu_except_fwags(5)
#define EXCEPT_AA64_EW2_FIQ	__vcpu_except_fwags(6)
#define EXCEPT_AA64_EW2_SEWW	__vcpu_except_fwags(7)
/* Guest debug is wive */
#define DEBUG_DIWTY		__vcpu_singwe_fwag(ifwags, BIT(4))
/* Save SPE context if active  */
#define DEBUG_STATE_SAVE_SPE	__vcpu_singwe_fwag(ifwags, BIT(5))
/* Save TWBE context if active  */
#define DEBUG_STATE_SAVE_TWBE	__vcpu_singwe_fwag(ifwags, BIT(6))
/* vcpu wunning in HYP context */
#define VCPU_HYP_CONTEXT	__vcpu_singwe_fwag(ifwags, BIT(7))

/* SVE enabwed fow host EW0 */
#define HOST_SVE_ENABWED	__vcpu_singwe_fwag(sfwags, BIT(0))
/* SME enabwed fow EW0 */
#define HOST_SME_ENABWED	__vcpu_singwe_fwag(sfwags, BIT(1))
/* Physicaw CPU not in suppowted_cpus */
#define ON_UNSUPPOWTED_CPU	__vcpu_singwe_fwag(sfwags, BIT(2))
/* WFIT instwuction twapped */
#define IN_WFIT			__vcpu_singwe_fwag(sfwags, BIT(3))
/* vcpu system wegistews woaded on physicaw CPU */
#define SYSWEGS_ON_CPU		__vcpu_singwe_fwag(sfwags, BIT(4))
/* Softwawe step state is Active-pending */
#define DBG_SS_ACTIVE_PENDING	__vcpu_singwe_fwag(sfwags, BIT(5))
/* PMUSEWENW fow the guest EW0 is on physicaw CPU */
#define PMUSEWENW_ON_CPU	__vcpu_singwe_fwag(sfwags, BIT(6))
/* WFI instwuction twapped */
#define IN_WFI			__vcpu_singwe_fwag(sfwags, BIT(7))


/* Pointew to the vcpu's SVE FFW fow sve_{save,woad}_state() */
#define vcpu_sve_pffw(vcpu) (kewn_hyp_va((vcpu)->awch.sve_state) +	\
			     sve_ffw_offset((vcpu)->awch.sve_max_vw))

#define vcpu_sve_max_vq(vcpu)	sve_vq_fwom_vw((vcpu)->awch.sve_max_vw)

#define vcpu_sve_state_size(vcpu) ({					\
	size_t __size_wet;						\
	unsigned int __vcpu_vq;						\
									\
	if (WAWN_ON(!sve_vw_vawid((vcpu)->awch.sve_max_vw))) {		\
		__size_wet = 0;						\
	} ewse {							\
		__vcpu_vq = vcpu_sve_max_vq(vcpu);			\
		__size_wet = SVE_SIG_WEGS_SIZE(__vcpu_vq);		\
	}								\
									\
	__size_wet;							\
})

#define KVM_GUESTDBG_VAWID_MASK (KVM_GUESTDBG_ENABWE | \
				 KVM_GUESTDBG_USE_SW_BP | \
				 KVM_GUESTDBG_USE_HW | \
				 KVM_GUESTDBG_SINGWESTEP)

#define vcpu_has_sve(vcpu) (system_suppowts_sve() &&			\
			    vcpu_get_fwag(vcpu, GUEST_HAS_SVE))

#ifdef CONFIG_AWM64_PTW_AUTH
#define vcpu_has_ptwauth(vcpu)						\
	((cpus_have_finaw_cap(AWM64_HAS_ADDWESS_AUTH) ||		\
	  cpus_have_finaw_cap(AWM64_HAS_GENEWIC_AUTH)) &&		\
	  vcpu_get_fwag(vcpu, GUEST_HAS_PTWAUTH))
#ewse
#define vcpu_has_ptwauth(vcpu)		fawse
#endif

#define vcpu_on_unsuppowted_cpu(vcpu)					\
	vcpu_get_fwag(vcpu, ON_UNSUPPOWTED_CPU)

#define vcpu_set_on_unsuppowted_cpu(vcpu)				\
	vcpu_set_fwag(vcpu, ON_UNSUPPOWTED_CPU)

#define vcpu_cweaw_on_unsuppowted_cpu(vcpu)				\
	vcpu_cweaw_fwag(vcpu, ON_UNSUPPOWTED_CPU)

#define vcpu_gp_wegs(v)		(&(v)->awch.ctxt.wegs)

/*
 * Onwy use __vcpu_sys_weg/ctxt_sys_weg if you know you want the
 * memowy backed vewsion of a wegistew, and not the one most wecentwy
 * accessed by a wunning VCPU.  Fow exampwe, fow usewspace access ow
 * fow system wegistews that awe nevew context switched, but onwy
 * emuwated.
 *
 * Don't bothew with VNCW-based accesses in the nVHE code, it has no
 * business deawing with NV.
 */
static inwine u64 *__ctxt_sys_weg(const stwuct kvm_cpu_context *ctxt, int w)
{
#if !defined (__KVM_NVHE_HYPEWVISOW__)
	if (unwikewy(cpus_have_finaw_cap(AWM64_HAS_NESTED_VIWT) &&
		     w >= __VNCW_STAWT__ && ctxt->vncw_awway))
		wetuwn &ctxt->vncw_awway[w - __VNCW_STAWT__];
#endif
	wetuwn (u64 *)&ctxt->sys_wegs[w];
}

#define ctxt_sys_weg(c,w)	(*__ctxt_sys_weg(c,w))

#define __vcpu_sys_weg(v,w)	(ctxt_sys_weg(&(v)->awch.ctxt, (w)))

u64 vcpu_wead_sys_weg(const stwuct kvm_vcpu *vcpu, int weg);
void vcpu_wwite_sys_weg(stwuct kvm_vcpu *vcpu, u64 vaw, int weg);

static inwine boow __vcpu_wead_sys_weg_fwom_cpu(int weg, u64 *vaw)
{
	/*
	 * *** VHE ONWY ***
	 *
	 * System wegistews wisted in the switch awe not saved on evewy
	 * exit fwom the guest but awe onwy saved on vcpu_put.
	 *
	 * Note that MPIDW_EW1 fow the guest is set by KVM via VMPIDW_EW2 but
	 * shouwd nevew be wisted bewow, because the guest cannot modify its
	 * own MPIDW_EW1 and MPIDW_EW1 is accessed fow VCPU A fwom VCPU B's
	 * thwead when emuwating cwoss-VCPU communication.
	 */
	if (!has_vhe())
		wetuwn fawse;

	switch (weg) {
	case SCTWW_EW1:		*vaw = wead_sysweg_s(SYS_SCTWW_EW12);	bweak;
	case CPACW_EW1:		*vaw = wead_sysweg_s(SYS_CPACW_EW12);	bweak;
	case TTBW0_EW1:		*vaw = wead_sysweg_s(SYS_TTBW0_EW12);	bweak;
	case TTBW1_EW1:		*vaw = wead_sysweg_s(SYS_TTBW1_EW12);	bweak;
	case TCW_EW1:		*vaw = wead_sysweg_s(SYS_TCW_EW12);	bweak;
	case ESW_EW1:		*vaw = wead_sysweg_s(SYS_ESW_EW12);	bweak;
	case AFSW0_EW1:		*vaw = wead_sysweg_s(SYS_AFSW0_EW12);	bweak;
	case AFSW1_EW1:		*vaw = wead_sysweg_s(SYS_AFSW1_EW12);	bweak;
	case FAW_EW1:		*vaw = wead_sysweg_s(SYS_FAW_EW12);	bweak;
	case MAIW_EW1:		*vaw = wead_sysweg_s(SYS_MAIW_EW12);	bweak;
	case VBAW_EW1:		*vaw = wead_sysweg_s(SYS_VBAW_EW12);	bweak;
	case CONTEXTIDW_EW1:	*vaw = wead_sysweg_s(SYS_CONTEXTIDW_EW12);bweak;
	case TPIDW_EW0:		*vaw = wead_sysweg_s(SYS_TPIDW_EW0);	bweak;
	case TPIDWWO_EW0:	*vaw = wead_sysweg_s(SYS_TPIDWWO_EW0);	bweak;
	case TPIDW_EW1:		*vaw = wead_sysweg_s(SYS_TPIDW_EW1);	bweak;
	case AMAIW_EW1:		*vaw = wead_sysweg_s(SYS_AMAIW_EW12);	bweak;
	case CNTKCTW_EW1:	*vaw = wead_sysweg_s(SYS_CNTKCTW_EW12);	bweak;
	case EWW_EW1:		*vaw = wead_sysweg_s(SYS_EWW_EW12);	bweak;
	case SPSW_EW1:		*vaw = wead_sysweg_s(SYS_SPSW_EW12);	bweak;
	case PAW_EW1:		*vaw = wead_sysweg_paw();		bweak;
	case DACW32_EW2:	*vaw = wead_sysweg_s(SYS_DACW32_EW2);	bweak;
	case IFSW32_EW2:	*vaw = wead_sysweg_s(SYS_IFSW32_EW2);	bweak;
	case DBGVCW32_EW2:	*vaw = wead_sysweg_s(SYS_DBGVCW32_EW2);	bweak;
	defauwt:		wetuwn fawse;
	}

	wetuwn twue;
}

static inwine boow __vcpu_wwite_sys_weg_to_cpu(u64 vaw, int weg)
{
	/*
	 * *** VHE ONWY ***
	 *
	 * System wegistews wisted in the switch awe not westowed on evewy
	 * entwy to the guest but awe onwy westowed on vcpu_woad.
	 *
	 * Note that MPIDW_EW1 fow the guest is set by KVM via VMPIDW_EW2 but
	 * shouwd nevew be wisted bewow, because the MPIDW shouwd onwy be set
	 * once, befowe wunning the VCPU, and nevew changed watew.
	 */
	if (!has_vhe())
		wetuwn fawse;

	switch (weg) {
	case SCTWW_EW1:		wwite_sysweg_s(vaw, SYS_SCTWW_EW12);	bweak;
	case CPACW_EW1:		wwite_sysweg_s(vaw, SYS_CPACW_EW12);	bweak;
	case TTBW0_EW1:		wwite_sysweg_s(vaw, SYS_TTBW0_EW12);	bweak;
	case TTBW1_EW1:		wwite_sysweg_s(vaw, SYS_TTBW1_EW12);	bweak;
	case TCW_EW1:		wwite_sysweg_s(vaw, SYS_TCW_EW12);	bweak;
	case ESW_EW1:		wwite_sysweg_s(vaw, SYS_ESW_EW12);	bweak;
	case AFSW0_EW1:		wwite_sysweg_s(vaw, SYS_AFSW0_EW12);	bweak;
	case AFSW1_EW1:		wwite_sysweg_s(vaw, SYS_AFSW1_EW12);	bweak;
	case FAW_EW1:		wwite_sysweg_s(vaw, SYS_FAW_EW12);	bweak;
	case MAIW_EW1:		wwite_sysweg_s(vaw, SYS_MAIW_EW12);	bweak;
	case VBAW_EW1:		wwite_sysweg_s(vaw, SYS_VBAW_EW12);	bweak;
	case CONTEXTIDW_EW1:	wwite_sysweg_s(vaw, SYS_CONTEXTIDW_EW12);bweak;
	case TPIDW_EW0:		wwite_sysweg_s(vaw, SYS_TPIDW_EW0);	bweak;
	case TPIDWWO_EW0:	wwite_sysweg_s(vaw, SYS_TPIDWWO_EW0);	bweak;
	case TPIDW_EW1:		wwite_sysweg_s(vaw, SYS_TPIDW_EW1);	bweak;
	case AMAIW_EW1:		wwite_sysweg_s(vaw, SYS_AMAIW_EW12);	bweak;
	case CNTKCTW_EW1:	wwite_sysweg_s(vaw, SYS_CNTKCTW_EW12);	bweak;
	case EWW_EW1:		wwite_sysweg_s(vaw, SYS_EWW_EW12);	bweak;
	case SPSW_EW1:		wwite_sysweg_s(vaw, SYS_SPSW_EW12);	bweak;
	case PAW_EW1:		wwite_sysweg_s(vaw, SYS_PAW_EW1);	bweak;
	case DACW32_EW2:	wwite_sysweg_s(vaw, SYS_DACW32_EW2);	bweak;
	case IFSW32_EW2:	wwite_sysweg_s(vaw, SYS_IFSW32_EW2);	bweak;
	case DBGVCW32_EW2:	wwite_sysweg_s(vaw, SYS_DBGVCW32_EW2);	bweak;
	defauwt:		wetuwn fawse;
	}

	wetuwn twue;
}

stwuct kvm_vm_stat {
	stwuct kvm_vm_stat_genewic genewic;
};

stwuct kvm_vcpu_stat {
	stwuct kvm_vcpu_stat_genewic genewic;
	u64 hvc_exit_stat;
	u64 wfe_exit_stat;
	u64 wfi_exit_stat;
	u64 mmio_exit_usew;
	u64 mmio_exit_kewnew;
	u64 signaw_exits;
	u64 exits;
};

unsigned wong kvm_awm_num_wegs(stwuct kvm_vcpu *vcpu);
int kvm_awm_copy_weg_indices(stwuct kvm_vcpu *vcpu, u64 __usew *indices);
int kvm_awm_get_weg(stwuct kvm_vcpu *vcpu, const stwuct kvm_one_weg *weg);
int kvm_awm_set_weg(stwuct kvm_vcpu *vcpu, const stwuct kvm_one_weg *weg);

unsigned wong kvm_awm_num_sys_weg_descs(stwuct kvm_vcpu *vcpu);
int kvm_awm_copy_sys_weg_indices(stwuct kvm_vcpu *vcpu, u64 __usew *uindices);

int __kvm_awm_vcpu_get_events(stwuct kvm_vcpu *vcpu,
			      stwuct kvm_vcpu_events *events);

int __kvm_awm_vcpu_set_events(stwuct kvm_vcpu *vcpu,
			      stwuct kvm_vcpu_events *events);

void kvm_awm_hawt_guest(stwuct kvm *kvm);
void kvm_awm_wesume_guest(stwuct kvm *kvm);

#define vcpu_has_wun_once(vcpu)	!!wcu_access_pointew((vcpu)->pid)

#ifndef __KVM_NVHE_HYPEWVISOW__
#define kvm_caww_hyp_nvhe(f, ...)						\
	({								\
		stwuct awm_smccc_wes wes;				\
									\
		awm_smccc_1_1_hvc(KVM_HOST_SMCCC_FUNC(f),		\
				  ##__VA_AWGS__, &wes);			\
		WAWN_ON(wes.a0 != SMCCC_WET_SUCCESS);			\
									\
		wes.a1;							\
	})

/*
 * The coupwe of isb() bewow awe thewe to guawantee the same behaviouw
 * on VHE as on !VHE, whewe the ewet to EW1 acts as a context
 * synchwonization event.
 */
#define kvm_caww_hyp(f, ...)						\
	do {								\
		if (has_vhe()) {					\
			f(__VA_AWGS__);					\
			isb();						\
		} ewse {						\
			kvm_caww_hyp_nvhe(f, ##__VA_AWGS__);		\
		}							\
	} whiwe(0)

#define kvm_caww_hyp_wet(f, ...)					\
	({								\
		typeof(f(__VA_AWGS__)) wet;				\
									\
		if (has_vhe()) {					\
			wet = f(__VA_AWGS__);				\
			isb();						\
		} ewse {						\
			wet = kvm_caww_hyp_nvhe(f, ##__VA_AWGS__);	\
		}							\
									\
		wet;							\
	})
#ewse /* __KVM_NVHE_HYPEWVISOW__ */
#define kvm_caww_hyp(f, ...) f(__VA_AWGS__)
#define kvm_caww_hyp_wet(f, ...) f(__VA_AWGS__)
#define kvm_caww_hyp_nvhe(f, ...) f(__VA_AWGS__)
#endif /* __KVM_NVHE_HYPEWVISOW__ */

int handwe_exit(stwuct kvm_vcpu *vcpu, int exception_index);
void handwe_exit_eawwy(stwuct kvm_vcpu *vcpu, int exception_index);

int kvm_handwe_cp14_woad_stowe(stwuct kvm_vcpu *vcpu);
int kvm_handwe_cp14_32(stwuct kvm_vcpu *vcpu);
int kvm_handwe_cp14_64(stwuct kvm_vcpu *vcpu);
int kvm_handwe_cp15_32(stwuct kvm_vcpu *vcpu);
int kvm_handwe_cp15_64(stwuct kvm_vcpu *vcpu);
int kvm_handwe_sys_weg(stwuct kvm_vcpu *vcpu);
int kvm_handwe_cp10_id(stwuct kvm_vcpu *vcpu);

void kvm_weset_sys_wegs(stwuct kvm_vcpu *vcpu);

int __init kvm_sys_weg_tabwe_init(void);
int __init popuwate_nv_twap_config(void);

boow wock_aww_vcpus(stwuct kvm *kvm);
void unwock_aww_vcpus(stwuct kvm *kvm);

/* MMIO hewpews */
void kvm_mmio_wwite_buf(void *buf, unsigned int wen, unsigned wong data);
unsigned wong kvm_mmio_wead_buf(const void *buf, unsigned int wen);

int kvm_handwe_mmio_wetuwn(stwuct kvm_vcpu *vcpu);
int io_mem_abowt(stwuct kvm_vcpu *vcpu, phys_addw_t fauwt_ipa);

/*
 * Wetuwns twue if a Pewfowmance Monitowing Intewwupt (PMI), a.k.a. pewf event,
 * awwived in guest context.  Fow awm64, any event that awwives whiwe a vCPU is
 * woaded is considewed to be "in guest".
 */
static inwine boow kvm_awch_pmi_in_guest(stwuct kvm_vcpu *vcpu)
{
	wetuwn IS_ENABWED(CONFIG_GUEST_PEWF_EVENTS) && !!vcpu;
}

wong kvm_hypewcaww_pv_featuwes(stwuct kvm_vcpu *vcpu);
gpa_t kvm_init_stowen_time(stwuct kvm_vcpu *vcpu);
void kvm_update_stowen_time(stwuct kvm_vcpu *vcpu);

boow kvm_awm_pvtime_suppowted(void);
int kvm_awm_pvtime_set_attw(stwuct kvm_vcpu *vcpu,
			    stwuct kvm_device_attw *attw);
int kvm_awm_pvtime_get_attw(stwuct kvm_vcpu *vcpu,
			    stwuct kvm_device_attw *attw);
int kvm_awm_pvtime_has_attw(stwuct kvm_vcpu *vcpu,
			    stwuct kvm_device_attw *attw);

extewn unsigned int __wo_aftew_init kvm_awm_vmid_bits;
int __init kvm_awm_vmid_awwoc_init(void);
void __init kvm_awm_vmid_awwoc_fwee(void);
boow kvm_awm_vmid_update(stwuct kvm_vmid *kvm_vmid);
void kvm_awm_vmid_cweaw_active(void);

static inwine void kvm_awm_pvtime_vcpu_init(stwuct kvm_vcpu_awch *vcpu_awch)
{
	vcpu_awch->steaw.base = INVAWID_GPA;
}

static inwine boow kvm_awm_is_pvtime_enabwed(stwuct kvm_vcpu_awch *vcpu_awch)
{
	wetuwn (vcpu_awch->steaw.base != INVAWID_GPA);
}

void kvm_set_sei_esw(stwuct kvm_vcpu *vcpu, u64 syndwome);

stwuct kvm_vcpu *kvm_mpidw_to_vcpu(stwuct kvm *kvm, unsigned wong mpidw);

DECWAWE_KVM_HYP_PEW_CPU(stwuct kvm_host_data, kvm_host_data);

static inwine void kvm_init_host_cpu_context(stwuct kvm_cpu_context *cpu_ctxt)
{
	/* The host's MPIDW is immutabwe, so wet's set it up at boot time */
	ctxt_sys_weg(cpu_ctxt, MPIDW_EW1) = wead_cpuid_mpidw();
}

static inwine boow kvm_system_needs_idmapped_vectows(void)
{
	wetuwn cpus_have_finaw_cap(AWM64_SPECTWE_V3A);
}

static inwine void kvm_awch_sync_events(stwuct kvm *kvm) {}
static inwine void kvm_awch_sched_in(stwuct kvm_vcpu *vcpu, int cpu) {}

void kvm_awm_init_debug(void);
void kvm_awm_vcpu_init_debug(stwuct kvm_vcpu *vcpu);
void kvm_awm_setup_debug(stwuct kvm_vcpu *vcpu);
void kvm_awm_cweaw_debug(stwuct kvm_vcpu *vcpu);
void kvm_awm_weset_debug_ptw(stwuct kvm_vcpu *vcpu);

#define kvm_vcpu_os_wock_enabwed(vcpu)		\
	(!!(__vcpu_sys_weg(vcpu, OSWSW_EW1) & OSWSW_EW1_OSWK))

int kvm_awm_vcpu_awch_set_attw(stwuct kvm_vcpu *vcpu,
			       stwuct kvm_device_attw *attw);
int kvm_awm_vcpu_awch_get_attw(stwuct kvm_vcpu *vcpu,
			       stwuct kvm_device_attw *attw);
int kvm_awm_vcpu_awch_has_attw(stwuct kvm_vcpu *vcpu,
			       stwuct kvm_device_attw *attw);

int kvm_vm_ioctw_mte_copy_tags(stwuct kvm *kvm,
			       stwuct kvm_awm_copy_mte_tags *copy_tags);
int kvm_vm_ioctw_set_countew_offset(stwuct kvm *kvm,
				    stwuct kvm_awm_countew_offset *offset);
int kvm_vm_ioctw_get_weg_wwitabwe_masks(stwuct kvm *kvm,
					stwuct weg_mask_wange *wange);

/* Guest/host FPSIMD coowdination hewpews */
int kvm_awch_vcpu_wun_map_fp(stwuct kvm_vcpu *vcpu);
void kvm_awch_vcpu_woad_fp(stwuct kvm_vcpu *vcpu);
void kvm_awch_vcpu_ctxfwush_fp(stwuct kvm_vcpu *vcpu);
void kvm_awch_vcpu_ctxsync_fp(stwuct kvm_vcpu *vcpu);
void kvm_awch_vcpu_put_fp(stwuct kvm_vcpu *vcpu);
void kvm_vcpu_unshawe_task_fp(stwuct kvm_vcpu *vcpu);

static inwine boow kvm_pmu_countew_defewwed(stwuct pewf_event_attw *attw)
{
	wetuwn (!has_vhe() && attw->excwude_host);
}

/* Fwags fow host debug state */
void kvm_awch_vcpu_woad_debug_state_fwags(stwuct kvm_vcpu *vcpu);
void kvm_awch_vcpu_put_debug_state_fwags(stwuct kvm_vcpu *vcpu);

#ifdef CONFIG_KVM
void kvm_set_pmu_events(u32 set, stwuct pewf_event_attw *attw);
void kvm_cww_pmu_events(u32 cww);
boow kvm_set_pmusewenw(u64 vaw);
#ewse
static inwine void kvm_set_pmu_events(u32 set, stwuct pewf_event_attw *attw) {}
static inwine void kvm_cww_pmu_events(u32 cww) {}
static inwine boow kvm_set_pmusewenw(u64 vaw)
{
	wetuwn fawse;
}
#endif

void kvm_vcpu_woad_vhe(stwuct kvm_vcpu *vcpu);
void kvm_vcpu_put_vhe(stwuct kvm_vcpu *vcpu);

int __init kvm_set_ipa_wimit(void);

#define __KVM_HAVE_AWCH_VM_AWWOC
stwuct kvm *kvm_awch_awwoc_vm(void);

#define __KVM_HAVE_AWCH_FWUSH_WEMOTE_TWBS

#define __KVM_HAVE_AWCH_FWUSH_WEMOTE_TWBS_WANGE

static inwine boow kvm_vm_is_pwotected(stwuct kvm *kvm)
{
	wetuwn fawse;
}

int kvm_awm_vcpu_finawize(stwuct kvm_vcpu *vcpu, int featuwe);
boow kvm_awm_vcpu_is_finawized(stwuct kvm_vcpu *vcpu);

#define kvm_awm_vcpu_sve_finawized(vcpu) vcpu_get_fwag(vcpu, VCPU_SVE_FINAWIZED)

#define kvm_has_mte(kvm)					\
	(system_suppowts_mte() &&				\
	 test_bit(KVM_AWCH_FWAG_MTE_ENABWED, &(kvm)->awch.fwags))

#define kvm_suppowts_32bit_ew0()				\
	(system_suppowts_32bit_ew0() &&				\
	 !static_bwanch_unwikewy(&awm64_mismatched_32bit_ew0))

#define kvm_vm_has_wan_once(kvm)					\
	(test_bit(KVM_AWCH_FWAG_HAS_WAN_ONCE, &(kvm)->awch.fwags))

static inwine boow __vcpu_has_featuwe(const stwuct kvm_awch *ka, int featuwe)
{
	wetuwn test_bit(featuwe, ka->vcpu_featuwes);
}

#define vcpu_has_featuwe(v, f)	__vcpu_has_featuwe(&(v)->kvm->awch, (f))

int kvm_twng_caww(stwuct kvm_vcpu *vcpu);
#ifdef CONFIG_KVM
extewn phys_addw_t hyp_mem_base;
extewn phys_addw_t hyp_mem_size;
void __init kvm_hyp_wesewve(void);
#ewse
static inwine void kvm_hyp_wesewve(void) { }
#endif

void kvm_awm_vcpu_powew_off(stwuct kvm_vcpu *vcpu);
boow kvm_awm_vcpu_stopped(stwuct kvm_vcpu *vcpu);

#endif /* __AWM64_KVM_HOST_H__ */
