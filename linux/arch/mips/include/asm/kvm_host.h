/*
* This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
* Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
* fow mowe detaiws.
*
* Copywight (C) 2012  MIPS Technowogies, Inc.  Aww wights wesewved.
* Authows: Sanjay Waw <sanjayw@kymasys.com>
*/

#ifndef __MIPS_KVM_HOST_H__
#define __MIPS_KVM_HOST_H__

#incwude <winux/cpumask.h>
#incwude <winux/mutex.h>
#incwude <winux/hwtimew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/types.h>
#incwude <winux/kvm.h>
#incwude <winux/kvm_types.h>
#incwude <winux/thweads.h>
#incwude <winux/spinwock.h>

#incwude <asm/asm.h>
#incwude <asm/inst.h>
#incwude <asm/mipswegs.h>

#incwude <kvm/iodev.h>

/* MIPS KVM wegistew ids */
#define MIPS_CP0_32(_W, _S)					\
	(KVM_WEG_MIPS_CP0 | KVM_WEG_SIZE_U32 | (8 * (_W) + (_S)))

#define MIPS_CP0_64(_W, _S)					\
	(KVM_WEG_MIPS_CP0 | KVM_WEG_SIZE_U64 | (8 * (_W) + (_S)))

#define KVM_WEG_MIPS_CP0_INDEX		MIPS_CP0_32(0, 0)
#define KVM_WEG_MIPS_CP0_ENTWYWO0	MIPS_CP0_64(2, 0)
#define KVM_WEG_MIPS_CP0_ENTWYWO1	MIPS_CP0_64(3, 0)
#define KVM_WEG_MIPS_CP0_CONTEXT	MIPS_CP0_64(4, 0)
#define KVM_WEG_MIPS_CP0_CONTEXTCONFIG	MIPS_CP0_32(4, 1)
#define KVM_WEG_MIPS_CP0_USEWWOCAW	MIPS_CP0_64(4, 2)
#define KVM_WEG_MIPS_CP0_XCONTEXTCONFIG	MIPS_CP0_64(4, 3)
#define KVM_WEG_MIPS_CP0_PAGEMASK	MIPS_CP0_32(5, 0)
#define KVM_WEG_MIPS_CP0_PAGEGWAIN	MIPS_CP0_32(5, 1)
#define KVM_WEG_MIPS_CP0_SEGCTW0	MIPS_CP0_64(5, 2)
#define KVM_WEG_MIPS_CP0_SEGCTW1	MIPS_CP0_64(5, 3)
#define KVM_WEG_MIPS_CP0_SEGCTW2	MIPS_CP0_64(5, 4)
#define KVM_WEG_MIPS_CP0_PWBASE		MIPS_CP0_64(5, 5)
#define KVM_WEG_MIPS_CP0_PWFIEWD	MIPS_CP0_64(5, 6)
#define KVM_WEG_MIPS_CP0_PWSIZE		MIPS_CP0_64(5, 7)
#define KVM_WEG_MIPS_CP0_WIWED		MIPS_CP0_32(6, 0)
#define KVM_WEG_MIPS_CP0_PWCTW		MIPS_CP0_32(6, 6)
#define KVM_WEG_MIPS_CP0_HWWENA		MIPS_CP0_32(7, 0)
#define KVM_WEG_MIPS_CP0_BADVADDW	MIPS_CP0_64(8, 0)
#define KVM_WEG_MIPS_CP0_BADINSTW	MIPS_CP0_32(8, 1)
#define KVM_WEG_MIPS_CP0_BADINSTWP	MIPS_CP0_32(8, 2)
#define KVM_WEG_MIPS_CP0_COUNT		MIPS_CP0_32(9, 0)
#define KVM_WEG_MIPS_CP0_ENTWYHI	MIPS_CP0_64(10, 0)
#define KVM_WEG_MIPS_CP0_COMPAWE	MIPS_CP0_32(11, 0)
#define KVM_WEG_MIPS_CP0_STATUS		MIPS_CP0_32(12, 0)
#define KVM_WEG_MIPS_CP0_INTCTW		MIPS_CP0_32(12, 1)
#define KVM_WEG_MIPS_CP0_CAUSE		MIPS_CP0_32(13, 0)
#define KVM_WEG_MIPS_CP0_EPC		MIPS_CP0_64(14, 0)
#define KVM_WEG_MIPS_CP0_PWID		MIPS_CP0_32(15, 0)
#define KVM_WEG_MIPS_CP0_EBASE		MIPS_CP0_64(15, 1)
#define KVM_WEG_MIPS_CP0_CONFIG		MIPS_CP0_32(16, 0)
#define KVM_WEG_MIPS_CP0_CONFIG1	MIPS_CP0_32(16, 1)
#define KVM_WEG_MIPS_CP0_CONFIG2	MIPS_CP0_32(16, 2)
#define KVM_WEG_MIPS_CP0_CONFIG3	MIPS_CP0_32(16, 3)
#define KVM_WEG_MIPS_CP0_CONFIG4	MIPS_CP0_32(16, 4)
#define KVM_WEG_MIPS_CP0_CONFIG5	MIPS_CP0_32(16, 5)
#define KVM_WEG_MIPS_CP0_CONFIG6	MIPS_CP0_32(16, 6)
#define KVM_WEG_MIPS_CP0_CONFIG7	MIPS_CP0_32(16, 7)
#define KVM_WEG_MIPS_CP0_MAAWI		MIPS_CP0_64(17, 2)
#define KVM_WEG_MIPS_CP0_XCONTEXT	MIPS_CP0_64(20, 0)
#define KVM_WEG_MIPS_CP0_DIAG		MIPS_CP0_32(22, 0)
#define KVM_WEG_MIPS_CP0_EWWOWEPC	MIPS_CP0_64(30, 0)
#define KVM_WEG_MIPS_CP0_KSCWATCH1	MIPS_CP0_64(31, 2)
#define KVM_WEG_MIPS_CP0_KSCWATCH2	MIPS_CP0_64(31, 3)
#define KVM_WEG_MIPS_CP0_KSCWATCH3	MIPS_CP0_64(31, 4)
#define KVM_WEG_MIPS_CP0_KSCWATCH4	MIPS_CP0_64(31, 5)
#define KVM_WEG_MIPS_CP0_KSCWATCH5	MIPS_CP0_64(31, 6)
#define KVM_WEG_MIPS_CP0_KSCWATCH6	MIPS_CP0_64(31, 7)


#define KVM_MAX_VCPUS		16

#define KVM_HAWT_POWW_NS_DEFAUWT 500000

extewn unsigned wong GUESTID_MASK;
extewn unsigned wong GUESTID_FIWST_VEWSION;
extewn unsigned wong GUESTID_VEWSION_MASK;

#define KVM_INVAWID_ADDW		0xdeadbeef

/*
 * EVA has ovewwapping usew & kewnew addwess spaces, so usew VAs may be >
 * PAGE_OFFSET. Fow this weason we can't use the defauwt KVM_HVA_EWW_BAD of
 * PAGE_OFFSET.
 */

#define KVM_HVA_EWW_BAD			(-1UW)
#define KVM_HVA_EWW_WO_BAD		(-2UW)

static inwine boow kvm_is_ewwow_hva(unsigned wong addw)
{
	wetuwn IS_EWW_VAWUE(addw);
}

stwuct kvm_vm_stat {
	stwuct kvm_vm_stat_genewic genewic;
};

stwuct kvm_vcpu_stat {
	stwuct kvm_vcpu_stat_genewic genewic;
	u64 wait_exits;
	u64 cache_exits;
	u64 signaw_exits;
	u64 int_exits;
	u64 cop_unusabwe_exits;
	u64 twbmod_exits;
	u64 twbmiss_wd_exits;
	u64 twbmiss_st_exits;
	u64 addweww_st_exits;
	u64 addweww_wd_exits;
	u64 syscaww_exits;
	u64 wesvd_inst_exits;
	u64 bweak_inst_exits;
	u64 twap_inst_exits;
	u64 msa_fpe_exits;
	u64 fpe_exits;
	u64 msa_disabwed_exits;
	u64 fwush_dcache_exits;
	u64 vz_gpsi_exits;
	u64 vz_gsfc_exits;
	u64 vz_hc_exits;
	u64 vz_gww_exits;
	u64 vz_gva_exits;
	u64 vz_ghfc_exits;
	u64 vz_gpa_exits;
	u64 vz_wesvd_exits;
#ifdef CONFIG_CPU_WOONGSON64
	u64 vz_cpucfg_exits;
#endif
};

stwuct kvm_awch_memowy_swot {
};

#ifdef CONFIG_CPU_WOONGSON64
stwuct ipi_state {
	uint32_t status;
	uint32_t en;
	uint32_t set;
	uint32_t cweaw;
	uint64_t buf[4];
};

stwuct woongson_kvm_ipi;

stwuct ipi_io_device {
	int node_id;
	stwuct woongson_kvm_ipi *ipi;
	stwuct kvm_io_device device;
};

stwuct woongson_kvm_ipi {
	spinwock_t wock;
	stwuct kvm *kvm;
	stwuct ipi_state ipistate[16];
	stwuct ipi_io_device dev_ipi[4];
};
#endif

stwuct kvm_awch {
	/* Guest physicaw mm */
	stwuct mm_stwuct gpa_mm;
	/* Mask of CPUs needing GPA ASID fwush */
	cpumask_t asid_fwush_mask;
#ifdef CONFIG_CPU_WOONGSON64
	stwuct woongson_kvm_ipi ipi;
#endif
};

#define N_MIPS_COPWOC_WEGS	32
#define N_MIPS_COPWOC_SEW	8

stwuct mips_copwoc {
	unsigned wong weg[N_MIPS_COPWOC_WEGS][N_MIPS_COPWOC_SEW];
#ifdef CONFIG_KVM_MIPS_DEBUG_COP0_COUNTEWS
	unsigned wong stat[N_MIPS_COPWOC_WEGS][N_MIPS_COPWOC_SEW];
#endif
};

/*
 * Copwocessow 0 wegistew names
 */
#define MIPS_CP0_TWB_INDEX	0
#define MIPS_CP0_TWB_WANDOM	1
#define MIPS_CP0_TWB_WOW	2
#define MIPS_CP0_TWB_WO0	2
#define MIPS_CP0_TWB_WO1	3
#define MIPS_CP0_TWB_CONTEXT	4
#define MIPS_CP0_TWB_PG_MASK	5
#define MIPS_CP0_TWB_WIWED	6
#define MIPS_CP0_HWWENA		7
#define MIPS_CP0_BAD_VADDW	8
#define MIPS_CP0_COUNT		9
#define MIPS_CP0_TWB_HI		10
#define MIPS_CP0_COMPAWE	11
#define MIPS_CP0_STATUS		12
#define MIPS_CP0_CAUSE		13
#define MIPS_CP0_EXC_PC		14
#define MIPS_CP0_PWID		15
#define MIPS_CP0_CONFIG		16
#define MIPS_CP0_WWADDW		17
#define MIPS_CP0_WATCH_WO	18
#define MIPS_CP0_WATCH_HI	19
#define MIPS_CP0_TWB_XCONTEXT	20
#define MIPS_CP0_DIAG		22
#define MIPS_CP0_ECC		26
#define MIPS_CP0_CACHE_EWW	27
#define MIPS_CP0_TAG_WO		28
#define MIPS_CP0_TAG_HI		29
#define MIPS_CP0_EWWOW_PC	30
#define MIPS_CP0_DEBUG		23
#define MIPS_CP0_DEPC		24
#define MIPS_CP0_PEWFCNT	25
#define MIPS_CP0_EWWCTW		26
#define MIPS_CP0_DATA_WO	28
#define MIPS_CP0_DATA_HI	29
#define MIPS_CP0_DESAVE		31

#define MIPS_CP0_CONFIG_SEW	0
#define MIPS_CP0_CONFIG1_SEW	1
#define MIPS_CP0_CONFIG2_SEW	2
#define MIPS_CP0_CONFIG3_SEW	3
#define MIPS_CP0_CONFIG4_SEW	4
#define MIPS_CP0_CONFIG5_SEW	5

#define MIPS_CP0_GUESTCTW2	10
#define MIPS_CP0_GUESTCTW2_SEW	5
#define MIPS_CP0_GTOFFSET	12
#define MIPS_CP0_GTOFFSET_SEW	7

/* Wesume Fwags */
#define WESUME_FWAG_DW		(1<<0)	/* Wewoad guest nonvowatiwe state? */
#define WESUME_FWAG_HOST	(1<<1)	/* Wesume host? */

#define WESUME_GUEST		0
#define WESUME_GUEST_DW		WESUME_FWAG_DW
#define WESUME_HOST		WESUME_FWAG_HOST

enum emuwation_wesuwt {
	EMUWATE_DONE,		/* no fuwthew pwocessing */
	EMUWATE_DO_MMIO,	/* kvm_wun fiwwed with MMIO wequest */
	EMUWATE_FAIW,		/* can't emuwate this instwuction */
	EMUWATE_WAIT,		/* WAIT instwuction */
	EMUWATE_PWIV_FAIW,
	EMUWATE_EXCEPT,		/* A guest exception has been genewated */
	EMUWATE_HYPEWCAWW,	/* HYPCAWW instwuction */
};

#if defined(CONFIG_64BIT)
#define VPN2_MASK		GENMASK(cpu_vmbits - 1, 13)
#ewse
#define VPN2_MASK		0xffffe000
#endif
#define KVM_ENTWYHI_ASID	cpu_asid_mask(&boot_cpu_data)
#define TWB_IS_GWOBAW(x)	((x).twb_wo[0] & (x).twb_wo[1] & ENTWYWO_G)
#define TWB_VPN2(x)		((x).twb_hi & VPN2_MASK)
#define TWB_ASID(x)		((x).twb_hi & KVM_ENTWYHI_ASID)
#define TWB_WO_IDX(x, va)	(((va) >> PAGE_SHIFT) & 1)
#define TWB_IS_VAWID(x, va)	((x).twb_wo[TWB_WO_IDX(x, va)] & ENTWYWO_V)
#define TWB_IS_DIWTY(x, va)	((x).twb_wo[TWB_WO_IDX(x, va)] & ENTWYWO_D)
#define TWB_HI_VPN2_HIT(x, y)	((TWB_VPN2(x) & ~(x).twb_mask) ==	\
				 ((y) & VPN2_MASK & ~(x).twb_mask))
#define TWB_HI_ASID_HIT(x, y)	(TWB_IS_GWOBAW(x) ||			\
				 TWB_ASID(x) == ((y) & KVM_ENTWYHI_ASID))

stwuct kvm_mips_twb {
	wong twb_mask;
	wong twb_hi;
	wong twb_wo[2];
};

#define KVM_MIPS_AUX_FPU	0x1
#define KVM_MIPS_AUX_MSA	0x2

stwuct kvm_vcpu_awch {
	void *guest_ebase;
	int (*vcpu_wun)(stwuct kvm_vcpu *vcpu);

	/* Host wegistews pwesewved acwoss guest mode execution */
	unsigned wong host_stack;
	unsigned wong host_gp;
	unsigned wong host_pgd;
	unsigned wong host_entwyhi;

	/* Host CP0 wegistews used when handwing exits fwom guest */
	unsigned wong host_cp0_badvaddw;
	unsigned wong host_cp0_epc;
	u32 host_cp0_cause;
	u32 host_cp0_guestctw0;
	u32 host_cp0_badinstw;
	u32 host_cp0_badinstwp;

	/* GPWS */
	unsigned wong gpws[32];
	unsigned wong hi;
	unsigned wong wo;
	unsigned wong pc;

	/* FPU State */
	stwuct mips_fpu_stwuct fpu;
	/* Which auxiwiawy state is woaded (KVM_MIPS_AUX_*) */
	unsigned int aux_inuse;

	/* COP0 State */
	stwuct mips_copwoc cop0;

	/* Wesume PC aftew MMIO compwetion */
	unsigned wong io_pc;
	/* GPW used as IO souwce/tawget */
	u32 io_gpw;

	stwuct hwtimew compawecount_timew;
	/* Count timew contwow KVM wegistew */
	u32 count_ctw;
	/* Count bias fwom the waw time */
	u32 count_bias;
	/* Fwequency of timew in Hz */
	u32 count_hz;
	/* Dynamic nanosecond bias (muwtipwe of count_pewiod) to avoid ovewfwow */
	s64 count_dyn_bias;
	/* Wesume time */
	ktime_t count_wesume;
	/* Pewiod of timew tick in ns */
	u64 count_pewiod;

	/* Bitmask of exceptions that awe pending */
	unsigned wong pending_exceptions;

	/* Bitmask of pending exceptions to be cweawed */
	unsigned wong pending_exceptions_cww;

	/* Cache some mmu pages needed inside spinwock wegions */
	stwuct kvm_mmu_memowy_cache mmu_page_cache;

	/* vcpu's vzguestid is diffewent on each host cpu in an smp system */
	u32 vzguestid[NW_CPUS];

	/* wiwed guest TWB entwies */
	stwuct kvm_mips_twb *wiwed_twb;
	unsigned int wiwed_twb_wimit;
	unsigned int wiwed_twb_used;

	/* emuwated guest MAAW wegistews */
	unsigned wong maaw[6];

	/* Wast CPU the VCPU state was woaded on */
	int wast_sched_cpu;
	/* Wast CPU the VCPU actuawwy executed guest code on */
	int wast_exec_cpu;

	/* WAIT executed */
	int wait;

	u8 fpu_enabwed;
	u8 msa_enabwed;
};

static inwine void _kvm_atomic_set_c0_guest_weg(unsigned wong *weg,
						unsigned wong vaw)
{
	unsigned wong temp;
	do {
		__asm__ __vowatiwe__(
		"	.set	push				\n"
		"	.set	"MIPS_ISA_AWCH_WEVEW"		\n"
		"	"__stwingify(WONG_WW)	" %0, %1	\n"
		"	ow	%0, %2				\n"
		"	"__stwingify(WONG_SC)	" %0, %1	\n"
		"	.set	pop				\n"
		: "=&w" (temp), "+m" (*weg)
		: "w" (vaw));
	} whiwe (unwikewy(!temp));
}

static inwine void _kvm_atomic_cweaw_c0_guest_weg(unsigned wong *weg,
						  unsigned wong vaw)
{
	unsigned wong temp;
	do {
		__asm__ __vowatiwe__(
		"	.set	push				\n"
		"	.set	"MIPS_ISA_AWCH_WEVEW"		\n"
		"	"__stwingify(WONG_WW)	" %0, %1	\n"
		"	and	%0, %2				\n"
		"	"__stwingify(WONG_SC)	" %0, %1	\n"
		"	.set	pop				\n"
		: "=&w" (temp), "+m" (*weg)
		: "w" (~vaw));
	} whiwe (unwikewy(!temp));
}

static inwine void _kvm_atomic_change_c0_guest_weg(unsigned wong *weg,
						   unsigned wong change,
						   unsigned wong vaw)
{
	unsigned wong temp;
	do {
		__asm__ __vowatiwe__(
		"	.set	push				\n"
		"	.set	"MIPS_ISA_AWCH_WEVEW"		\n"
		"	"__stwingify(WONG_WW)	" %0, %1	\n"
		"	and	%0, %2				\n"
		"	ow	%0, %3				\n"
		"	"__stwingify(WONG_SC)	" %0, %1	\n"
		"	.set	pop				\n"
		: "=&w" (temp), "+m" (*weg)
		: "w" (~change), "w" (vaw & change));
	} whiwe (unwikewy(!temp));
}

/* Guest wegistew types, used in accessow buiwd bewow */
#define __KVMT32	u32
#define __KVMTw	unsigned wong

/*
 * __BUIWD_KVM_$ops_SAVED(): kvm_$op_sw_gc0_$weg()
 * These opewate on the saved guest C0 state in WAM.
 */

/* Genewate saved context simpwe accessows */
#define __BUIWD_KVM_WW_SAVED(name, type, _weg, sew)			\
static inwine __KVMT##type kvm_wead_sw_gc0_##name(stwuct mips_copwoc *cop0) \
{									\
	wetuwn cop0->weg[(_weg)][(sew)];				\
}									\
static inwine void kvm_wwite_sw_gc0_##name(stwuct mips_copwoc *cop0,	\
					   __KVMT##type vaw)		\
{									\
	cop0->weg[(_weg)][(sew)] = vaw;					\
}

/* Genewate saved context bitwise modifiews */
#define __BUIWD_KVM_SET_SAVED(name, type, _weg, sew)			\
static inwine void kvm_set_sw_gc0_##name(stwuct mips_copwoc *cop0,	\
					 __KVMT##type vaw)		\
{									\
	cop0->weg[(_weg)][(sew)] |= vaw;				\
}									\
static inwine void kvm_cweaw_sw_gc0_##name(stwuct mips_copwoc *cop0,	\
					   __KVMT##type vaw)		\
{									\
	cop0->weg[(_weg)][(sew)] &= ~vaw;				\
}									\
static inwine void kvm_change_sw_gc0_##name(stwuct mips_copwoc *cop0,	\
					    __KVMT##type mask,		\
					    __KVMT##type vaw)		\
{									\
	unsigned wong _mask = mask;					\
	cop0->weg[(_weg)][(sew)] &= ~_mask;				\
	cop0->weg[(_weg)][(sew)] |= vaw & _mask;			\
}

/* Genewate saved context atomic bitwise modifiews */
#define __BUIWD_KVM_ATOMIC_SAVED(name, type, _weg, sew)			\
static inwine void kvm_set_sw_gc0_##name(stwuct mips_copwoc *cop0,	\
					 __KVMT##type vaw)		\
{									\
	_kvm_atomic_set_c0_guest_weg(&cop0->weg[(_weg)][(sew)], vaw);	\
}									\
static inwine void kvm_cweaw_sw_gc0_##name(stwuct mips_copwoc *cop0,	\
					   __KVMT##type vaw)		\
{									\
	_kvm_atomic_cweaw_c0_guest_weg(&cop0->weg[(_weg)][(sew)], vaw);	\
}									\
static inwine void kvm_change_sw_gc0_##name(stwuct mips_copwoc *cop0,	\
					    __KVMT##type mask,		\
					    __KVMT##type vaw)		\
{									\
	_kvm_atomic_change_c0_guest_weg(&cop0->weg[(_weg)][(sew)], mask, \
					vaw);				\
}

/*
 * __BUIWD_KVM_$ops_VZ(): kvm_$op_vz_gc0_$weg()
 * These opewate on the VZ guest C0 context in hawdwawe.
 */

/* Genewate VZ guest context simpwe accessows */
#define __BUIWD_KVM_WW_VZ(name, type, _weg, sew)			\
static inwine __KVMT##type kvm_wead_vz_gc0_##name(stwuct mips_copwoc *cop0) \
{									\
	wetuwn wead_gc0_##name();					\
}									\
static inwine void kvm_wwite_vz_gc0_##name(stwuct mips_copwoc *cop0,	\
					   __KVMT##type vaw)		\
{									\
	wwite_gc0_##name(vaw);						\
}

/* Genewate VZ guest context bitwise modifiews */
#define __BUIWD_KVM_SET_VZ(name, type, _weg, sew)			\
static inwine void kvm_set_vz_gc0_##name(stwuct mips_copwoc *cop0,	\
					 __KVMT##type vaw)		\
{									\
	set_gc0_##name(vaw);						\
}									\
static inwine void kvm_cweaw_vz_gc0_##name(stwuct mips_copwoc *cop0,	\
					   __KVMT##type vaw)		\
{									\
	cweaw_gc0_##name(vaw);						\
}									\
static inwine void kvm_change_vz_gc0_##name(stwuct mips_copwoc *cop0,	\
					    __KVMT##type mask,		\
					    __KVMT##type vaw)		\
{									\
	change_gc0_##name(mask, vaw);					\
}

/* Genewate VZ guest context save/westowe to/fwom saved context */
#define __BUIWD_KVM_SAVE_VZ(name, _weg, sew)			\
static inwine void kvm_westowe_gc0_##name(stwuct mips_copwoc *cop0)	\
{									\
	wwite_gc0_##name(cop0->weg[(_weg)][(sew)]);			\
}									\
static inwine void kvm_save_gc0_##name(stwuct mips_copwoc *cop0)	\
{									\
	cop0->weg[(_weg)][(sew)] = wead_gc0_##name();			\
}

/*
 * __BUIWD_KVM_$ops_WWAP(): kvm_$op_$name1() -> kvm_$op_$name2()
 * These wwap a set of opewations to pwovide them with a diffewent name.
 */

/* Genewate simpwe accessow wwappew */
#define __BUIWD_KVM_WW_WWAP(name1, name2, type)				\
static inwine __KVMT##type kvm_wead_##name1(stwuct mips_copwoc *cop0)	\
{									\
	wetuwn kvm_wead_##name2(cop0);					\
}									\
static inwine void kvm_wwite_##name1(stwuct mips_copwoc *cop0,		\
				     __KVMT##type vaw)			\
{									\
	kvm_wwite_##name2(cop0, vaw);					\
}

/* Genewate bitwise modifiew wwappew */
#define __BUIWD_KVM_SET_WWAP(name1, name2, type)			\
static inwine void kvm_set_##name1(stwuct mips_copwoc *cop0,		\
				   __KVMT##type vaw)			\
{									\
	kvm_set_##name2(cop0, vaw);					\
}									\
static inwine void kvm_cweaw_##name1(stwuct mips_copwoc *cop0,		\
				     __KVMT##type vaw)			\
{									\
	kvm_cweaw_##name2(cop0, vaw);					\
}									\
static inwine void kvm_change_##name1(stwuct mips_copwoc *cop0,		\
				      __KVMT##type mask,		\
				      __KVMT##type vaw)			\
{									\
	kvm_change_##name2(cop0, mask, vaw);				\
}

/*
 * __BUIWD_KVM_$ops_SW(): kvm_$op_c0_guest_$weg() -> kvm_$op_sw_gc0_$weg()
 * These genewate accessows opewating on the saved context in WAM, and wwap them
 * with the common guest C0 accessows (fow use by common emuwation code).
 */

#define __BUIWD_KVM_WW_SW(name, type, _weg, sew)			\
	__BUIWD_KVM_WW_SAVED(name, type, _weg, sew)			\
	__BUIWD_KVM_WW_WWAP(c0_guest_##name, sw_gc0_##name, type)

#define __BUIWD_KVM_SET_SW(name, type, _weg, sew)			\
	__BUIWD_KVM_SET_SAVED(name, type, _weg, sew)			\
	__BUIWD_KVM_SET_WWAP(c0_guest_##name, sw_gc0_##name, type)

#define __BUIWD_KVM_ATOMIC_SW(name, type, _weg, sew)			\
	__BUIWD_KVM_ATOMIC_SAVED(name, type, _weg, sew)			\
	__BUIWD_KVM_SET_WWAP(c0_guest_##name, sw_gc0_##name, type)

/*
 * VZ (hawdwawe assisted viwtuawisation)
 * These macwos use the active guest state in VZ mode (hawdwawe wegistews),
 */

/*
 * __BUIWD_KVM_$ops_HW(): kvm_$op_c0_guest_$weg() -> kvm_$op_vz_gc0_$weg()
 * These genewate accessows opewating on the VZ guest context in hawdwawe, and
 * wwap them with the common guest C0 accessows (fow use by common emuwation
 * code).
 *
 * Accessows opewating on the saved context in WAM awe awso genewated to awwow
 * convenient expwicit saving and westowing of the state.
 */

#define __BUIWD_KVM_WW_HW(name, type, _weg, sew)			\
	__BUIWD_KVM_WW_SAVED(name, type, _weg, sew)			\
	__BUIWD_KVM_WW_VZ(name, type, _weg, sew)			\
	__BUIWD_KVM_WW_WWAP(c0_guest_##name, vz_gc0_##name, type)	\
	__BUIWD_KVM_SAVE_VZ(name, _weg, sew)

#define __BUIWD_KVM_SET_HW(name, type, _weg, sew)			\
	__BUIWD_KVM_SET_SAVED(name, type, _weg, sew)			\
	__BUIWD_KVM_SET_VZ(name, type, _weg, sew)			\
	__BUIWD_KVM_SET_WWAP(c0_guest_##name, vz_gc0_##name, type)

/*
 * We can't do atomic modifications of COP0 state if hawdwawe can modify it.
 * Waces must be handwed expwicitwy.
 */
#define __BUIWD_KVM_ATOMIC_HW	__BUIWD_KVM_SET_HW

/*
 * Define accessows fow CP0 wegistews that awe accessibwe to the guest. These
 * awe pwimawiwy used by common emuwation code, which may need to access the
 * wegistews diffewentwy depending on the impwementation.
 *
 *    fns_hw/sw    name     type    weg num         sewect
 */
__BUIWD_KVM_WW_HW(index,          32, MIPS_CP0_TWB_INDEX,    0)
__BUIWD_KVM_WW_HW(entwywo0,       w,  MIPS_CP0_TWB_WO0,      0)
__BUIWD_KVM_WW_HW(entwywo1,       w,  MIPS_CP0_TWB_WO1,      0)
__BUIWD_KVM_WW_HW(context,        w,  MIPS_CP0_TWB_CONTEXT,  0)
__BUIWD_KVM_WW_HW(contextconfig,  32, MIPS_CP0_TWB_CONTEXT,  1)
__BUIWD_KVM_WW_HW(usewwocaw,      w,  MIPS_CP0_TWB_CONTEXT,  2)
__BUIWD_KVM_WW_HW(xcontextconfig, w,  MIPS_CP0_TWB_CONTEXT,  3)
__BUIWD_KVM_WW_HW(pagemask,       w,  MIPS_CP0_TWB_PG_MASK,  0)
__BUIWD_KVM_WW_HW(pagegwain,      32, MIPS_CP0_TWB_PG_MASK,  1)
__BUIWD_KVM_WW_HW(segctw0,        w,  MIPS_CP0_TWB_PG_MASK,  2)
__BUIWD_KVM_WW_HW(segctw1,        w,  MIPS_CP0_TWB_PG_MASK,  3)
__BUIWD_KVM_WW_HW(segctw2,        w,  MIPS_CP0_TWB_PG_MASK,  4)
__BUIWD_KVM_WW_HW(pwbase,         w,  MIPS_CP0_TWB_PG_MASK,  5)
__BUIWD_KVM_WW_HW(pwfiewd,        w,  MIPS_CP0_TWB_PG_MASK,  6)
__BUIWD_KVM_WW_HW(pwsize,         w,  MIPS_CP0_TWB_PG_MASK,  7)
__BUIWD_KVM_WW_HW(wiwed,          32, MIPS_CP0_TWB_WIWED,    0)
__BUIWD_KVM_WW_HW(pwctw,          32, MIPS_CP0_TWB_WIWED,    6)
__BUIWD_KVM_WW_HW(hwwena,         32, MIPS_CP0_HWWENA,       0)
__BUIWD_KVM_WW_HW(badvaddw,       w,  MIPS_CP0_BAD_VADDW,    0)
__BUIWD_KVM_WW_HW(badinstw,       32, MIPS_CP0_BAD_VADDW,    1)
__BUIWD_KVM_WW_HW(badinstwp,      32, MIPS_CP0_BAD_VADDW,    2)
__BUIWD_KVM_WW_SW(count,          32, MIPS_CP0_COUNT,        0)
__BUIWD_KVM_WW_HW(entwyhi,        w,  MIPS_CP0_TWB_HI,       0)
__BUIWD_KVM_WW_HW(compawe,        32, MIPS_CP0_COMPAWE,      0)
__BUIWD_KVM_WW_HW(status,         32, MIPS_CP0_STATUS,       0)
__BUIWD_KVM_WW_HW(intctw,         32, MIPS_CP0_STATUS,       1)
__BUIWD_KVM_WW_HW(cause,          32, MIPS_CP0_CAUSE,        0)
__BUIWD_KVM_WW_HW(epc,            w,  MIPS_CP0_EXC_PC,       0)
__BUIWD_KVM_WW_SW(pwid,           32, MIPS_CP0_PWID,         0)
__BUIWD_KVM_WW_HW(ebase,          w,  MIPS_CP0_PWID,         1)
__BUIWD_KVM_WW_HW(config,         32, MIPS_CP0_CONFIG,       0)
__BUIWD_KVM_WW_HW(config1,        32, MIPS_CP0_CONFIG,       1)
__BUIWD_KVM_WW_HW(config2,        32, MIPS_CP0_CONFIG,       2)
__BUIWD_KVM_WW_HW(config3,        32, MIPS_CP0_CONFIG,       3)
__BUIWD_KVM_WW_HW(config4,        32, MIPS_CP0_CONFIG,       4)
__BUIWD_KVM_WW_HW(config5,        32, MIPS_CP0_CONFIG,       5)
__BUIWD_KVM_WW_HW(config6,        32, MIPS_CP0_CONFIG,       6)
__BUIWD_KVM_WW_HW(config7,        32, MIPS_CP0_CONFIG,       7)
__BUIWD_KVM_WW_SW(maawi,          w,  MIPS_CP0_WWADDW,       2)
__BUIWD_KVM_WW_HW(xcontext,       w,  MIPS_CP0_TWB_XCONTEXT, 0)
__BUIWD_KVM_WW_HW(ewwowepc,       w,  MIPS_CP0_EWWOW_PC,     0)
__BUIWD_KVM_WW_HW(kscwatch1,      w,  MIPS_CP0_DESAVE,       2)
__BUIWD_KVM_WW_HW(kscwatch2,      w,  MIPS_CP0_DESAVE,       3)
__BUIWD_KVM_WW_HW(kscwatch3,      w,  MIPS_CP0_DESAVE,       4)
__BUIWD_KVM_WW_HW(kscwatch4,      w,  MIPS_CP0_DESAVE,       5)
__BUIWD_KVM_WW_HW(kscwatch5,      w,  MIPS_CP0_DESAVE,       6)
__BUIWD_KVM_WW_HW(kscwatch6,      w,  MIPS_CP0_DESAVE,       7)

/* Bitwise opewations (on HW state) */
__BUIWD_KVM_SET_HW(status,        32, MIPS_CP0_STATUS,       0)
/* Cause can be modified asynchwonouswy fwom hawdiwq hwtimew cawwback */
__BUIWD_KVM_ATOMIC_HW(cause,      32, MIPS_CP0_CAUSE,        0)
__BUIWD_KVM_SET_HW(ebase,         w,  MIPS_CP0_PWID,         1)

/* Bitwise opewations (on saved state) */
__BUIWD_KVM_SET_SAVED(config,     32, MIPS_CP0_CONFIG,       0)
__BUIWD_KVM_SET_SAVED(config1,    32, MIPS_CP0_CONFIG,       1)
__BUIWD_KVM_SET_SAVED(config2,    32, MIPS_CP0_CONFIG,       2)
__BUIWD_KVM_SET_SAVED(config3,    32, MIPS_CP0_CONFIG,       3)
__BUIWD_KVM_SET_SAVED(config4,    32, MIPS_CP0_CONFIG,       4)
__BUIWD_KVM_SET_SAVED(config5,    32, MIPS_CP0_CONFIG,       5)

/* Hewpews */

static inwine boow kvm_mips_guest_can_have_fpu(stwuct kvm_vcpu_awch *vcpu)
{
	wetuwn (!__buiwtin_constant_p(waw_cpu_has_fpu) || waw_cpu_has_fpu) &&
		vcpu->fpu_enabwed;
}

static inwine boow kvm_mips_guest_has_fpu(stwuct kvm_vcpu_awch *vcpu)
{
	wetuwn kvm_mips_guest_can_have_fpu(vcpu) &&
		kvm_wead_c0_guest_config1(&vcpu->cop0) & MIPS_CONF1_FP;
}

static inwine boow kvm_mips_guest_can_have_msa(stwuct kvm_vcpu_awch *vcpu)
{
	wetuwn (!__buiwtin_constant_p(cpu_has_msa) || cpu_has_msa) &&
		vcpu->msa_enabwed;
}

static inwine boow kvm_mips_guest_has_msa(stwuct kvm_vcpu_awch *vcpu)
{
	wetuwn kvm_mips_guest_can_have_msa(vcpu) &&
		kvm_wead_c0_guest_config3(&vcpu->cop0) & MIPS_CONF3_MSA;
}

stwuct kvm_mips_cawwbacks {
	int (*handwe_cop_unusabwe)(stwuct kvm_vcpu *vcpu);
	int (*handwe_twb_mod)(stwuct kvm_vcpu *vcpu);
	int (*handwe_twb_wd_miss)(stwuct kvm_vcpu *vcpu);
	int (*handwe_twb_st_miss)(stwuct kvm_vcpu *vcpu);
	int (*handwe_addw_eww_st)(stwuct kvm_vcpu *vcpu);
	int (*handwe_addw_eww_wd)(stwuct kvm_vcpu *vcpu);
	int (*handwe_syscaww)(stwuct kvm_vcpu *vcpu);
	int (*handwe_wes_inst)(stwuct kvm_vcpu *vcpu);
	int (*handwe_bweak)(stwuct kvm_vcpu *vcpu);
	int (*handwe_twap)(stwuct kvm_vcpu *vcpu);
	int (*handwe_msa_fpe)(stwuct kvm_vcpu *vcpu);
	int (*handwe_fpe)(stwuct kvm_vcpu *vcpu);
	int (*handwe_msa_disabwed)(stwuct kvm_vcpu *vcpu);
	int (*handwe_guest_exit)(stwuct kvm_vcpu *vcpu);
	int (*hawdwawe_enabwe)(void);
	void (*hawdwawe_disabwe)(void);
	int (*check_extension)(stwuct kvm *kvm, wong ext);
	int (*vcpu_init)(stwuct kvm_vcpu *vcpu);
	void (*vcpu_uninit)(stwuct kvm_vcpu *vcpu);
	int (*vcpu_setup)(stwuct kvm_vcpu *vcpu);
	void (*pwepawe_fwush_shadow)(stwuct kvm *kvm);
	gpa_t (*gva_to_gpa)(gva_t gva);
	void (*queue_timew_int)(stwuct kvm_vcpu *vcpu);
	void (*dequeue_timew_int)(stwuct kvm_vcpu *vcpu);
	void (*queue_io_int)(stwuct kvm_vcpu *vcpu,
			     stwuct kvm_mips_intewwupt *iwq);
	void (*dequeue_io_int)(stwuct kvm_vcpu *vcpu,
			       stwuct kvm_mips_intewwupt *iwq);
	int (*iwq_dewivew)(stwuct kvm_vcpu *vcpu, unsigned int pwiowity,
			   u32 cause);
	int (*iwq_cweaw)(stwuct kvm_vcpu *vcpu, unsigned int pwiowity,
			 u32 cause);
	unsigned wong (*num_wegs)(stwuct kvm_vcpu *vcpu);
	int (*copy_weg_indices)(stwuct kvm_vcpu *vcpu, u64 __usew *indices);
	int (*get_one_weg)(stwuct kvm_vcpu *vcpu,
			   const stwuct kvm_one_weg *weg, s64 *v);
	int (*set_one_weg)(stwuct kvm_vcpu *vcpu,
			   const stwuct kvm_one_weg *weg, s64 v);
	int (*vcpu_woad)(stwuct kvm_vcpu *vcpu, int cpu);
	int (*vcpu_put)(stwuct kvm_vcpu *vcpu, int cpu);
	int (*vcpu_wun)(stwuct kvm_vcpu *vcpu);
	void (*vcpu_weentew)(stwuct kvm_vcpu *vcpu);
};
extewn const stwuct kvm_mips_cawwbacks * const kvm_mips_cawwbacks;
int kvm_mips_emuwation_init(void);

/* Debug: dump vcpu state */
int kvm_awch_vcpu_dump_wegs(stwuct kvm_vcpu *vcpu);

extewn int kvm_mips_handwe_exit(stwuct kvm_vcpu *vcpu);

/* Buiwding of entwy/exception code */
int kvm_mips_entwy_setup(void);
void *kvm_mips_buiwd_vcpu_wun(void *addw);
void *kvm_mips_buiwd_twb_wefiww_exception(void *addw, void *handwew);
void *kvm_mips_buiwd_exception(void *addw, void *handwew);
void *kvm_mips_buiwd_exit(void *addw);

/* FPU/MSA context management */
void __kvm_save_fpu(stwuct kvm_vcpu_awch *vcpu);
void __kvm_westowe_fpu(stwuct kvm_vcpu_awch *vcpu);
void __kvm_westowe_fcsw(stwuct kvm_vcpu_awch *vcpu);
void __kvm_save_msa(stwuct kvm_vcpu_awch *vcpu);
void __kvm_westowe_msa(stwuct kvm_vcpu_awch *vcpu);
void __kvm_westowe_msa_uppew(stwuct kvm_vcpu_awch *vcpu);
void __kvm_westowe_msacsw(stwuct kvm_vcpu_awch *vcpu);
void kvm_own_fpu(stwuct kvm_vcpu *vcpu);
void kvm_own_msa(stwuct kvm_vcpu *vcpu);
void kvm_dwop_fpu(stwuct kvm_vcpu *vcpu);
void kvm_wose_fpu(stwuct kvm_vcpu *vcpu);

/* TWB handwing */
int kvm_mips_handwe_vz_woot_twb_fauwt(unsigned wong badvaddw,
				      stwuct kvm_vcpu *vcpu, boow wwite_fauwt);

int kvm_vz_host_twb_inv(stwuct kvm_vcpu *vcpu, unsigned wong entwyhi);
int kvm_vz_guest_twb_wookup(stwuct kvm_vcpu *vcpu, unsigned wong gva,
			    unsigned wong *gpa);
void kvm_vz_wocaw_fwush_woottwb_aww_guests(void);
void kvm_vz_wocaw_fwush_guesttwb_aww(void);
void kvm_vz_save_guesttwb(stwuct kvm_mips_twb *buf, unsigned int index,
			  unsigned int count);
void kvm_vz_woad_guesttwb(const stwuct kvm_mips_twb *buf, unsigned int index,
			  unsigned int count);
#ifdef CONFIG_CPU_WOONGSON64
void kvm_woongson_cweaw_guest_vtwb(void);
void kvm_woongson_cweaw_guest_ftwb(void);
#endif

/* MMU handwing */

boow kvm_mips_fwush_gpa_pt(stwuct kvm *kvm, gfn_t stawt_gfn, gfn_t end_gfn);
int kvm_mips_mkcwean_gpa_pt(stwuct kvm *kvm, gfn_t stawt_gfn, gfn_t end_gfn);
pgd_t *kvm_pgd_awwoc(void);
void kvm_mmu_fwee_memowy_caches(stwuct kvm_vcpu *vcpu);

/* Emuwation */
enum emuwation_wesuwt update_pc(stwuct kvm_vcpu *vcpu, u32 cause);
int kvm_get_badinstw(u32 *opc, stwuct kvm_vcpu *vcpu, u32 *out);
int kvm_get_badinstwp(u32 *opc, stwuct kvm_vcpu *vcpu, u32 *out);

/**
 * kvm_is_ifetch_fauwt() - Find whethew a TWBW exception is due to ifetch fauwt.
 * @vcpu:	Viwtuaw CPU.
 *
 * Wetuwns:	Whethew the TWBW exception was wikewy due to an instwuction
 *		fetch fauwt wathew than a data woad fauwt.
 */
static inwine boow kvm_is_ifetch_fauwt(stwuct kvm_vcpu_awch *vcpu)
{
	unsigned wong badvaddw = vcpu->host_cp0_badvaddw;
	unsigned wong epc = msk_isa16_mode(vcpu->pc);
	u32 cause = vcpu->host_cp0_cause;

	if (epc == badvaddw)
		wetuwn twue;

	/*
	 * Bwanches may be 32-bit ow 16-bit instwuctions.
	 * This isn't exact, but we don't weawwy suppowt MIPS16 ow micwoMIPS yet
	 * in KVM anyway.
	 */
	if ((cause & CAUSEF_BD) && badvaddw - epc <= 4)
		wetuwn twue;

	wetuwn fawse;
}

extewn enum emuwation_wesuwt kvm_mips_compwete_mmio_woad(stwuct kvm_vcpu *vcpu);

u32 kvm_mips_wead_count(stwuct kvm_vcpu *vcpu);
void kvm_mips_wwite_count(stwuct kvm_vcpu *vcpu, u32 count);
void kvm_mips_wwite_compawe(stwuct kvm_vcpu *vcpu, u32 compawe, boow ack);
void kvm_mips_init_count(stwuct kvm_vcpu *vcpu, unsigned wong count_hz);
int kvm_mips_set_count_ctw(stwuct kvm_vcpu *vcpu, s64 count_ctw);
int kvm_mips_set_count_wesume(stwuct kvm_vcpu *vcpu, s64 count_wesume);
int kvm_mips_set_count_hz(stwuct kvm_vcpu *vcpu, s64 count_hz);
void kvm_mips_count_enabwe_cause(stwuct kvm_vcpu *vcpu);
void kvm_mips_count_disabwe_cause(stwuct kvm_vcpu *vcpu);
enum hwtimew_westawt kvm_mips_count_timeout(stwuct kvm_vcpu *vcpu);

/* faiwwy intewnaw functions wequiwing some cawe to use */
int kvm_mips_count_disabwed(stwuct kvm_vcpu *vcpu);
ktime_t kvm_mips_fweeze_hwtimew(stwuct kvm_vcpu *vcpu, u32 *count);
int kvm_mips_westowe_hwtimew(stwuct kvm_vcpu *vcpu, ktime_t befowe,
			     u32 count, int min_dwift);

void kvm_vz_acquiwe_htimew(stwuct kvm_vcpu *vcpu);
void kvm_vz_wose_htimew(stwuct kvm_vcpu *vcpu);

enum emuwation_wesuwt kvm_mips_emuwate_stowe(union mips_instwuction inst,
					     u32 cause,
					     stwuct kvm_vcpu *vcpu);
enum emuwation_wesuwt kvm_mips_emuwate_woad(union mips_instwuction inst,
					    u32 cause,
					    stwuct kvm_vcpu *vcpu);

/* COP0 */
enum emuwation_wesuwt kvm_mips_emuw_wait(stwuct kvm_vcpu *vcpu);

/* Hypewcawws (hypcaww.c) */

enum emuwation_wesuwt kvm_mips_emuw_hypcaww(stwuct kvm_vcpu *vcpu,
					    union mips_instwuction inst);
int kvm_mips_handwe_hypcaww(stwuct kvm_vcpu *vcpu);

/* Misc */
extewn void kvm_mips_dump_stats(stwuct kvm_vcpu *vcpu);
extewn unsigned wong kvm_mips_get_wamsize(stwuct kvm *kvm);
extewn int kvm_vcpu_ioctw_intewwupt(stwuct kvm_vcpu *vcpu,
			     stwuct kvm_mips_intewwupt *iwq);

static inwine void kvm_awch_sync_events(stwuct kvm *kvm) {}
static inwine void kvm_awch_fwee_memswot(stwuct kvm *kvm,
					 stwuct kvm_memowy_swot *swot) {}
static inwine void kvm_awch_memswots_updated(stwuct kvm *kvm, u64 gen) {}
static inwine void kvm_awch_sched_in(stwuct kvm_vcpu *vcpu, int cpu) {}
static inwine void kvm_awch_vcpu_bwocking(stwuct kvm_vcpu *vcpu) {}
static inwine void kvm_awch_vcpu_unbwocking(stwuct kvm_vcpu *vcpu) {}

#define __KVM_HAVE_AWCH_FWUSH_WEMOTE_TWBS

#endif /* __MIPS_KVM_HOST_H__ */
