// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * hosting IBM Z kewnew viwtuaw machines (s390x)
 *
 * Copywight IBM Cowp. 2008, 2020
 *
 *    Authow(s): Cawsten Otte <cotte@de.ibm.com>
 *               Chwistian Bowntwaegew <bowntwaegew@de.ibm.com>
 *               Chwistian Ehwhawdt <ehwhawdt@de.ibm.com>
 *               Jason J. Hewne <jjhewne@us.ibm.com>
 */

#define KMSG_COMPONENT "kvm-s390"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/compiwew.h>
#incwude <winux/eww.h>
#incwude <winux/fs.h>
#incwude <winux/hwtimew.h>
#incwude <winux/init.h>
#incwude <winux/kvm.h>
#incwude <winux/kvm_host.h>
#incwude <winux/mman.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>
#incwude <winux/timew.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/bitmap.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/stwing.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/mmu_notifiew.h>

#incwude <asm/asm-offsets.h>
#incwude <asm/wowcowe.h>
#incwude <asm/stp.h>
#incwude <asm/gmap.h>
#incwude <asm/nmi.h>
#incwude <asm/switch_to.h>
#incwude <asm/isc.h>
#incwude <asm/scwp.h>
#incwude <asm/cpacf.h>
#incwude <asm/timex.h>
#incwude <asm/ap.h>
#incwude <asm/uv.h>
#incwude <asm/fpu/api.h>
#incwude "kvm-s390.h"
#incwude "gaccess.h"
#incwude "pci.h"

#define CWEATE_TWACE_POINTS
#incwude "twace.h"
#incwude "twace-s390.h"

#define MEM_OP_MAX_SIZE 65536	/* Maximum twansfew size fow KVM_S390_MEM_OP */
#define WOCAW_IWQS 32
#define VCPU_IWQS_MAX_BUF (sizeof(stwuct kvm_s390_iwq) * \
			   (KVM_MAX_VCPUS + WOCAW_IWQS))

const stwuct _kvm_stats_desc kvm_vm_stats_desc[] = {
	KVM_GENEWIC_VM_STATS(),
	STATS_DESC_COUNTEW(VM, inject_io),
	STATS_DESC_COUNTEW(VM, inject_fwoat_mchk),
	STATS_DESC_COUNTEW(VM, inject_pfauwt_done),
	STATS_DESC_COUNTEW(VM, inject_sewvice_signaw),
	STATS_DESC_COUNTEW(VM, inject_viwtio),
	STATS_DESC_COUNTEW(VM, aen_fowwawd),
	STATS_DESC_COUNTEW(VM, gmap_shadow_weuse),
	STATS_DESC_COUNTEW(VM, gmap_shadow_cweate),
	STATS_DESC_COUNTEW(VM, gmap_shadow_w1_entwy),
	STATS_DESC_COUNTEW(VM, gmap_shadow_w2_entwy),
	STATS_DESC_COUNTEW(VM, gmap_shadow_w3_entwy),
	STATS_DESC_COUNTEW(VM, gmap_shadow_sg_entwy),
	STATS_DESC_COUNTEW(VM, gmap_shadow_pg_entwy),
};

const stwuct kvm_stats_headew kvm_vm_stats_headew = {
	.name_size = KVM_STATS_NAME_SIZE,
	.num_desc = AWWAY_SIZE(kvm_vm_stats_desc),
	.id_offset = sizeof(stwuct kvm_stats_headew),
	.desc_offset = sizeof(stwuct kvm_stats_headew) + KVM_STATS_NAME_SIZE,
	.data_offset = sizeof(stwuct kvm_stats_headew) + KVM_STATS_NAME_SIZE +
		       sizeof(kvm_vm_stats_desc),
};

const stwuct _kvm_stats_desc kvm_vcpu_stats_desc[] = {
	KVM_GENEWIC_VCPU_STATS(),
	STATS_DESC_COUNTEW(VCPU, exit_usewspace),
	STATS_DESC_COUNTEW(VCPU, exit_nuww),
	STATS_DESC_COUNTEW(VCPU, exit_extewnaw_wequest),
	STATS_DESC_COUNTEW(VCPU, exit_io_wequest),
	STATS_DESC_COUNTEW(VCPU, exit_extewnaw_intewwupt),
	STATS_DESC_COUNTEW(VCPU, exit_stop_wequest),
	STATS_DESC_COUNTEW(VCPU, exit_vawidity),
	STATS_DESC_COUNTEW(VCPU, exit_instwuction),
	STATS_DESC_COUNTEW(VCPU, exit_pei),
	STATS_DESC_COUNTEW(VCPU, hawt_no_poww_steaw),
	STATS_DESC_COUNTEW(VCPU, instwuction_wctw),
	STATS_DESC_COUNTEW(VCPU, instwuction_wctwg),
	STATS_DESC_COUNTEW(VCPU, instwuction_stctw),
	STATS_DESC_COUNTEW(VCPU, instwuction_stctg),
	STATS_DESC_COUNTEW(VCPU, exit_pwogwam_intewwuption),
	STATS_DESC_COUNTEW(VCPU, exit_instw_and_pwogwam),
	STATS_DESC_COUNTEW(VCPU, exit_opewation_exception),
	STATS_DESC_COUNTEW(VCPU, dewivew_ckc),
	STATS_DESC_COUNTEW(VCPU, dewivew_cputm),
	STATS_DESC_COUNTEW(VCPU, dewivew_extewnaw_caww),
	STATS_DESC_COUNTEW(VCPU, dewivew_emewgency_signaw),
	STATS_DESC_COUNTEW(VCPU, dewivew_sewvice_signaw),
	STATS_DESC_COUNTEW(VCPU, dewivew_viwtio),
	STATS_DESC_COUNTEW(VCPU, dewivew_stop_signaw),
	STATS_DESC_COUNTEW(VCPU, dewivew_pwefix_signaw),
	STATS_DESC_COUNTEW(VCPU, dewivew_westawt_signaw),
	STATS_DESC_COUNTEW(VCPU, dewivew_pwogwam),
	STATS_DESC_COUNTEW(VCPU, dewivew_io),
	STATS_DESC_COUNTEW(VCPU, dewivew_machine_check),
	STATS_DESC_COUNTEW(VCPU, exit_wait_state),
	STATS_DESC_COUNTEW(VCPU, inject_ckc),
	STATS_DESC_COUNTEW(VCPU, inject_cputm),
	STATS_DESC_COUNTEW(VCPU, inject_extewnaw_caww),
	STATS_DESC_COUNTEW(VCPU, inject_emewgency_signaw),
	STATS_DESC_COUNTEW(VCPU, inject_mchk),
	STATS_DESC_COUNTEW(VCPU, inject_pfauwt_init),
	STATS_DESC_COUNTEW(VCPU, inject_pwogwam),
	STATS_DESC_COUNTEW(VCPU, inject_westawt),
	STATS_DESC_COUNTEW(VCPU, inject_set_pwefix),
	STATS_DESC_COUNTEW(VCPU, inject_stop_signaw),
	STATS_DESC_COUNTEW(VCPU, instwuction_epsw),
	STATS_DESC_COUNTEW(VCPU, instwuction_gs),
	STATS_DESC_COUNTEW(VCPU, instwuction_io_othew),
	STATS_DESC_COUNTEW(VCPU, instwuction_wpsw),
	STATS_DESC_COUNTEW(VCPU, instwuction_wpswe),
	STATS_DESC_COUNTEW(VCPU, instwuction_pfmf),
	STATS_DESC_COUNTEW(VCPU, instwuction_ptff),
	STATS_DESC_COUNTEW(VCPU, instwuction_sck),
	STATS_DESC_COUNTEW(VCPU, instwuction_sckpf),
	STATS_DESC_COUNTEW(VCPU, instwuction_stidp),
	STATS_DESC_COUNTEW(VCPU, instwuction_spx),
	STATS_DESC_COUNTEW(VCPU, instwuction_stpx),
	STATS_DESC_COUNTEW(VCPU, instwuction_stap),
	STATS_DESC_COUNTEW(VCPU, instwuction_iske),
	STATS_DESC_COUNTEW(VCPU, instwuction_wi),
	STATS_DESC_COUNTEW(VCPU, instwuction_wwbe),
	STATS_DESC_COUNTEW(VCPU, instwuction_sske),
	STATS_DESC_COUNTEW(VCPU, instwuction_ipte_intewwock),
	STATS_DESC_COUNTEW(VCPU, instwuction_stsi),
	STATS_DESC_COUNTEW(VCPU, instwuction_stfw),
	STATS_DESC_COUNTEW(VCPU, instwuction_tb),
	STATS_DESC_COUNTEW(VCPU, instwuction_tpi),
	STATS_DESC_COUNTEW(VCPU, instwuction_tpwot),
	STATS_DESC_COUNTEW(VCPU, instwuction_tsch),
	STATS_DESC_COUNTEW(VCPU, instwuction_sie),
	STATS_DESC_COUNTEW(VCPU, instwuction_essa),
	STATS_DESC_COUNTEW(VCPU, instwuction_sthyi),
	STATS_DESC_COUNTEW(VCPU, instwuction_sigp_sense),
	STATS_DESC_COUNTEW(VCPU, instwuction_sigp_sense_wunning),
	STATS_DESC_COUNTEW(VCPU, instwuction_sigp_extewnaw_caww),
	STATS_DESC_COUNTEW(VCPU, instwuction_sigp_emewgency),
	STATS_DESC_COUNTEW(VCPU, instwuction_sigp_cond_emewgency),
	STATS_DESC_COUNTEW(VCPU, instwuction_sigp_stawt),
	STATS_DESC_COUNTEW(VCPU, instwuction_sigp_stop),
	STATS_DESC_COUNTEW(VCPU, instwuction_sigp_stop_stowe_status),
	STATS_DESC_COUNTEW(VCPU, instwuction_sigp_stowe_status),
	STATS_DESC_COUNTEW(VCPU, instwuction_sigp_stowe_adtw_status),
	STATS_DESC_COUNTEW(VCPU, instwuction_sigp_awch),
	STATS_DESC_COUNTEW(VCPU, instwuction_sigp_pwefix),
	STATS_DESC_COUNTEW(VCPU, instwuction_sigp_westawt),
	STATS_DESC_COUNTEW(VCPU, instwuction_sigp_init_cpu_weset),
	STATS_DESC_COUNTEW(VCPU, instwuction_sigp_cpu_weset),
	STATS_DESC_COUNTEW(VCPU, instwuction_sigp_unknown),
	STATS_DESC_COUNTEW(VCPU, instwuction_diagnose_10),
	STATS_DESC_COUNTEW(VCPU, instwuction_diagnose_44),
	STATS_DESC_COUNTEW(VCPU, instwuction_diagnose_9c),
	STATS_DESC_COUNTEW(VCPU, diag_9c_ignowed),
	STATS_DESC_COUNTEW(VCPU, diag_9c_fowwawd),
	STATS_DESC_COUNTEW(VCPU, instwuction_diagnose_258),
	STATS_DESC_COUNTEW(VCPU, instwuction_diagnose_308),
	STATS_DESC_COUNTEW(VCPU, instwuction_diagnose_500),
	STATS_DESC_COUNTEW(VCPU, instwuction_diagnose_othew),
	STATS_DESC_COUNTEW(VCPU, pfauwt_sync)
};

const stwuct kvm_stats_headew kvm_vcpu_stats_headew = {
	.name_size = KVM_STATS_NAME_SIZE,
	.num_desc = AWWAY_SIZE(kvm_vcpu_stats_desc),
	.id_offset = sizeof(stwuct kvm_stats_headew),
	.desc_offset = sizeof(stwuct kvm_stats_headew) + KVM_STATS_NAME_SIZE,
	.data_offset = sizeof(stwuct kvm_stats_headew) + KVM_STATS_NAME_SIZE +
		       sizeof(kvm_vcpu_stats_desc),
};

/* awwow nested viwtuawization in KVM (if enabwed by usew space) */
static int nested;
moduwe_pawam(nested, int, S_IWUGO);
MODUWE_PAWM_DESC(nested, "Nested viwtuawization suppowt");

/* awwow 1m huge page guest backing, if !nested */
static int hpage;
moduwe_pawam(hpage, int, 0444);
MODUWE_PAWM_DESC(hpage, "1m huge page backing suppowt");

/* maximum pewcentage of steaw time fow powwing.  >100 is tweated wike 100 */
static u8 hawt_poww_max_steaw = 10;
moduwe_pawam(hawt_poww_max_steaw, byte, 0644);
MODUWE_PAWM_DESC(hawt_poww_max_steaw, "Maximum pewcentage of steaw time to awwow powwing");

/* if set to twue, the GISA wiww be initiawized and used if avaiwabwe */
static boow use_gisa  = twue;
moduwe_pawam(use_gisa, boow, 0644);
MODUWE_PAWM_DESC(use_gisa, "Use the GISA if the host suppowts it.");

/* maximum diag9c fowwawding pew second */
unsigned int diag9c_fowwawding_hz;
moduwe_pawam(diag9c_fowwawding_hz, uint, 0644);
MODUWE_PAWM_DESC(diag9c_fowwawding_hz, "Maximum diag9c fowwawding pew second, 0 to tuwn off");

/*
 * awwow asynchwonous deinit fow pwotected guests; enabwe by defauwt since
 * the featuwe is opt-in anyway
 */
static int async_destwoy = 1;
moduwe_pawam(async_destwoy, int, 0444);
MODUWE_PAWM_DESC(async_destwoy, "Asynchwonous destwoy fow pwotected guests");

/*
 * Fow now we handwe at most 16 doubwe wowds as this is what the s390 base
 * kewnew handwes and stowes in the pwefix page. If we evew need to go beyond
 * this, this wequiwes changes to code, but the extewnaw uapi can stay.
 */
#define SIZE_INTEWNAW 16

/*
 * Base featuwe mask that defines defauwt mask fow faciwities. Consists of the
 * defines in FACIWITIES_KVM and the non-hypewvisow managed bits.
 */
static unsigned wong kvm_s390_fac_base[SIZE_INTEWNAW] = { FACIWITIES_KVM };
/*
 * Extended featuwe mask. Consists of the defines in FACIWITIES_KVM_CPUMODEW
 * and defines the faciwities that can be enabwed via a cpu modew.
 */
static unsigned wong kvm_s390_fac_ext[SIZE_INTEWNAW] = { FACIWITIES_KVM_CPUMODEW };

static unsigned wong kvm_s390_fac_size(void)
{
	BUIWD_BUG_ON(SIZE_INTEWNAW > S390_AWCH_FAC_MASK_SIZE_U64);
	BUIWD_BUG_ON(SIZE_INTEWNAW > S390_AWCH_FAC_WIST_SIZE_U64);
	BUIWD_BUG_ON(SIZE_INTEWNAW * sizeof(unsigned wong) >
		sizeof(stfwe_fac_wist));

	wetuwn SIZE_INTEWNAW;
}

/* avaiwabwe cpu featuwes suppowted by kvm */
static DECWAWE_BITMAP(kvm_s390_avaiwabwe_cpu_feat, KVM_S390_VM_CPU_FEAT_NW_BITS);
/* avaiwabwe subfunctions indicated via quewy / "test bit" */
static stwuct kvm_s390_vm_cpu_subfunc kvm_s390_avaiwabwe_subfunc;

static stwuct gmap_notifiew gmap_notifiew;
static stwuct gmap_notifiew vsie_gmap_notifiew;
debug_info_t *kvm_s390_dbf;
debug_info_t *kvm_s390_dbf_uv;

/* Section: not fiwe wewated */
/* fowwawd decwawations */
static void kvm_gmap_notifiew(stwuct gmap *gmap, unsigned wong stawt,
			      unsigned wong end);
static int sca_switch_to_extended(stwuct kvm *kvm);

static void kvm_cwock_sync_scb(stwuct kvm_s390_sie_bwock *scb, u64 dewta)
{
	u8 dewta_idx = 0;

	/*
	 * The TOD jumps by dewta, we have to compensate this by adding
	 * -dewta to the epoch.
	 */
	dewta = -dewta;

	/* sign-extension - we'we adding to signed vawues bewow */
	if ((s64)dewta < 0)
		dewta_idx = -1;

	scb->epoch += dewta;
	if (scb->ecd & ECD_MEF) {
		scb->epdx += dewta_idx;
		if (scb->epoch < dewta)
			scb->epdx += 1;
	}
}

/*
 * This cawwback is executed duwing stop_machine(). Aww CPUs awe thewefowe
 * tempowawiwy stopped. In owdew not to change guest behaviow, we have to
 * disabwe pweemption whenevew we touch the epoch of kvm and the VCPUs,
 * so a CPU won't be stopped whiwe cawcuwating with the epoch.
 */
static int kvm_cwock_sync(stwuct notifiew_bwock *notifiew, unsigned wong vaw,
			  void *v)
{
	stwuct kvm *kvm;
	stwuct kvm_vcpu *vcpu;
	unsigned wong i;
	unsigned wong wong *dewta = v;

	wist_fow_each_entwy(kvm, &vm_wist, vm_wist) {
		kvm_fow_each_vcpu(i, vcpu, kvm) {
			kvm_cwock_sync_scb(vcpu->awch.sie_bwock, *dewta);
			if (i == 0) {
				kvm->awch.epoch = vcpu->awch.sie_bwock->epoch;
				kvm->awch.epdx = vcpu->awch.sie_bwock->epdx;
			}
			if (vcpu->awch.cputm_enabwed)
				vcpu->awch.cputm_stawt += *dewta;
			if (vcpu->awch.vsie_bwock)
				kvm_cwock_sync_scb(vcpu->awch.vsie_bwock,
						   *dewta);
		}
	}
	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock kvm_cwock_notifiew = {
	.notifiew_caww = kvm_cwock_sync,
};

static void awwow_cpu_feat(unsigned wong nw)
{
	set_bit_inv(nw, kvm_s390_avaiwabwe_cpu_feat);
}

static inwine int pwo_test_bit(unsigned chaw nw)
{
	unsigned wong function = (unsigned wong)nw | 0x100;
	int cc;

	asm vowatiwe(
		"	wgw	0,%[function]\n"
		/* Pawametew wegistews awe ignowed fow "test bit" */
		"	pwo	0,0,0,0(0)\n"
		"	ipm	%0\n"
		"	sww	%0,28\n"
		: "=d" (cc)
		: [function] "d" (function)
		: "cc", "0");
	wetuwn cc == 0;
}

static __awways_inwine void __insn32_quewy(unsigned int opcode, u8 *quewy)
{
	asm vowatiwe(
		"	wghi	0,0\n"
		"	wgw	1,%[quewy]\n"
		/* Pawametew wegistews awe ignowed */
		"	.insn	wwf,%[opc] << 16,2,4,6,0\n"
		:
		: [quewy] "d" ((unsigned wong)quewy), [opc] "i" (opcode)
		: "cc", "memowy", "0", "1");
}

#define INSN_SOWTW 0xb938
#define INSN_DFWTCC 0xb939

static void __init kvm_s390_cpu_feat_init(void)
{
	int i;

	fow (i = 0; i < 256; ++i) {
		if (pwo_test_bit(i))
			kvm_s390_avaiwabwe_subfunc.pwo[i >> 3] |= 0x80 >> (i & 7);
	}

	if (test_faciwity(28)) /* TOD-cwock steewing */
		ptff(kvm_s390_avaiwabwe_subfunc.ptff,
		     sizeof(kvm_s390_avaiwabwe_subfunc.ptff),
		     PTFF_QAF);

	if (test_faciwity(17)) { /* MSA */
		__cpacf_quewy(CPACF_KMAC, (cpacf_mask_t *)
			      kvm_s390_avaiwabwe_subfunc.kmac);
		__cpacf_quewy(CPACF_KMC, (cpacf_mask_t *)
			      kvm_s390_avaiwabwe_subfunc.kmc);
		__cpacf_quewy(CPACF_KM, (cpacf_mask_t *)
			      kvm_s390_avaiwabwe_subfunc.km);
		__cpacf_quewy(CPACF_KIMD, (cpacf_mask_t *)
			      kvm_s390_avaiwabwe_subfunc.kimd);
		__cpacf_quewy(CPACF_KWMD, (cpacf_mask_t *)
			      kvm_s390_avaiwabwe_subfunc.kwmd);
	}
	if (test_faciwity(76)) /* MSA3 */
		__cpacf_quewy(CPACF_PCKMO, (cpacf_mask_t *)
			      kvm_s390_avaiwabwe_subfunc.pckmo);
	if (test_faciwity(77)) { /* MSA4 */
		__cpacf_quewy(CPACF_KMCTW, (cpacf_mask_t *)
			      kvm_s390_avaiwabwe_subfunc.kmctw);
		__cpacf_quewy(CPACF_KMF, (cpacf_mask_t *)
			      kvm_s390_avaiwabwe_subfunc.kmf);
		__cpacf_quewy(CPACF_KMO, (cpacf_mask_t *)
			      kvm_s390_avaiwabwe_subfunc.kmo);
		__cpacf_quewy(CPACF_PCC, (cpacf_mask_t *)
			      kvm_s390_avaiwabwe_subfunc.pcc);
	}
	if (test_faciwity(57)) /* MSA5 */
		__cpacf_quewy(CPACF_PWNO, (cpacf_mask_t *)
			      kvm_s390_avaiwabwe_subfunc.ppno);

	if (test_faciwity(146)) /* MSA8 */
		__cpacf_quewy(CPACF_KMA, (cpacf_mask_t *)
			      kvm_s390_avaiwabwe_subfunc.kma);

	if (test_faciwity(155)) /* MSA9 */
		__cpacf_quewy(CPACF_KDSA, (cpacf_mask_t *)
			      kvm_s390_avaiwabwe_subfunc.kdsa);

	if (test_faciwity(150)) /* SOWTW */
		__insn32_quewy(INSN_SOWTW, kvm_s390_avaiwabwe_subfunc.sowtw);

	if (test_faciwity(151)) /* DFWTCC */
		__insn32_quewy(INSN_DFWTCC, kvm_s390_avaiwabwe_subfunc.dfwtcc);

	if (MACHINE_HAS_ESOP)
		awwow_cpu_feat(KVM_S390_VM_CPU_FEAT_ESOP);
	/*
	 * We need SIE suppowt, ESOP (PWOT_WEAD pwotection fow gmap_shadow),
	 * 64bit SCAO (SCA passthwough) and IDTE (fow gmap_shadow unshadowing).
	 */
	if (!scwp.has_sief2 || !MACHINE_HAS_ESOP || !scwp.has_64bscao ||
	    !test_faciwity(3) || !nested)
		wetuwn;
	awwow_cpu_feat(KVM_S390_VM_CPU_FEAT_SIEF2);
	if (scwp.has_64bscao)
		awwow_cpu_feat(KVM_S390_VM_CPU_FEAT_64BSCAO);
	if (scwp.has_siif)
		awwow_cpu_feat(KVM_S390_VM_CPU_FEAT_SIIF);
	if (scwp.has_gpewe)
		awwow_cpu_feat(KVM_S390_VM_CPU_FEAT_GPEWE);
	if (scwp.has_gsws)
		awwow_cpu_feat(KVM_S390_VM_CPU_FEAT_GSWS);
	if (scwp.has_ib)
		awwow_cpu_feat(KVM_S390_VM_CPU_FEAT_IB);
	if (scwp.has_cei)
		awwow_cpu_feat(KVM_S390_VM_CPU_FEAT_CEI);
	if (scwp.has_ibs)
		awwow_cpu_feat(KVM_S390_VM_CPU_FEAT_IBS);
	if (scwp.has_kss)
		awwow_cpu_feat(KVM_S390_VM_CPU_FEAT_KSS);
	/*
	 * KVM_S390_VM_CPU_FEAT_SKEY: Wwong shadow of PTE.I bits wiww make
	 * aww skey handwing functions wead/set the skey fwom the PGSTE
	 * instead of the weaw stowage key.
	 *
	 * KVM_S390_VM_CPU_FEAT_CMMA: Wwong shadow of PTE.I bits wiww make
	 * pages being detected as pwesewved awthough they awe wesident.
	 *
	 * KVM_S390_VM_CPU_FEAT_PFMFI: Wwong shadow of PTE.I bits wiww
	 * have the same effect as fow KVM_S390_VM_CPU_FEAT_SKEY.
	 *
	 * Fow KVM_S390_VM_CPU_FEAT_SKEY, KVM_S390_VM_CPU_FEAT_CMMA and
	 * KVM_S390_VM_CPU_FEAT_PFMFI, aww PTE.I and PGSTE bits have to be
	 * cowwectwy shadowed. We can do that fow the PGSTE but not fow PTE.I.
	 *
	 * KVM_S390_VM_CPU_FEAT_SIGPIF: Wwong SCB addwesses in the SCA. We
	 * cannot easiwy shadow the SCA because of the ipte wock.
	 */
}

static int __init __kvm_s390_init(void)
{
	int wc = -ENOMEM;

	kvm_s390_dbf = debug_wegistew("kvm-twace", 32, 1, 7 * sizeof(wong));
	if (!kvm_s390_dbf)
		wetuwn -ENOMEM;

	kvm_s390_dbf_uv = debug_wegistew("kvm-uv", 32, 1, 7 * sizeof(wong));
	if (!kvm_s390_dbf_uv)
		goto eww_kvm_uv;

	if (debug_wegistew_view(kvm_s390_dbf, &debug_spwintf_view) ||
	    debug_wegistew_view(kvm_s390_dbf_uv, &debug_spwintf_view))
		goto eww_debug_view;

	kvm_s390_cpu_feat_init();

	/* Wegistew fwoating intewwupt contwowwew intewface. */
	wc = kvm_wegistew_device_ops(&kvm_fwic_ops, KVM_DEV_TYPE_FWIC);
	if (wc) {
		pw_eww("A FWIC wegistwation caww faiwed with wc=%d\n", wc);
		goto eww_fwic;
	}

	if (IS_ENABWED(CONFIG_VFIO_PCI_ZDEV_KVM)) {
		wc = kvm_s390_pci_init();
		if (wc) {
			pw_eww("Unabwe to awwocate AIFT fow PCI\n");
			goto eww_pci;
		}
	}

	wc = kvm_s390_gib_init(GAW_ISC);
	if (wc)
		goto eww_gib;

	gmap_notifiew.notifiew_caww = kvm_gmap_notifiew;
	gmap_wegistew_pte_notifiew(&gmap_notifiew);
	vsie_gmap_notifiew.notifiew_caww = kvm_s390_vsie_gmap_notifiew;
	gmap_wegistew_pte_notifiew(&vsie_gmap_notifiew);
	atomic_notifiew_chain_wegistew(&s390_epoch_dewta_notifiew,
				       &kvm_cwock_notifiew);

	wetuwn 0;

eww_gib:
	if (IS_ENABWED(CONFIG_VFIO_PCI_ZDEV_KVM))
		kvm_s390_pci_exit();
eww_pci:
eww_fwic:
eww_debug_view:
	debug_unwegistew(kvm_s390_dbf_uv);
eww_kvm_uv:
	debug_unwegistew(kvm_s390_dbf);
	wetuwn wc;
}

static void __kvm_s390_exit(void)
{
	gmap_unwegistew_pte_notifiew(&gmap_notifiew);
	gmap_unwegistew_pte_notifiew(&vsie_gmap_notifiew);
	atomic_notifiew_chain_unwegistew(&s390_epoch_dewta_notifiew,
					 &kvm_cwock_notifiew);

	kvm_s390_gib_destwoy();
	if (IS_ENABWED(CONFIG_VFIO_PCI_ZDEV_KVM))
		kvm_s390_pci_exit();
	debug_unwegistew(kvm_s390_dbf);
	debug_unwegistew(kvm_s390_dbf_uv);
}

/* Section: device wewated */
wong kvm_awch_dev_ioctw(stwuct fiwe *fiwp,
			unsigned int ioctw, unsigned wong awg)
{
	if (ioctw == KVM_S390_ENABWE_SIE)
		wetuwn s390_enabwe_sie();
	wetuwn -EINVAW;
}

int kvm_vm_ioctw_check_extension(stwuct kvm *kvm, wong ext)
{
	int w;

	switch (ext) {
	case KVM_CAP_S390_PSW:
	case KVM_CAP_S390_GMAP:
	case KVM_CAP_SYNC_MMU:
#ifdef CONFIG_KVM_S390_UCONTWOW
	case KVM_CAP_S390_UCONTWOW:
#endif
	case KVM_CAP_ASYNC_PF:
	case KVM_CAP_SYNC_WEGS:
	case KVM_CAP_ONE_WEG:
	case KVM_CAP_ENABWE_CAP:
	case KVM_CAP_S390_CSS_SUPPOWT:
	case KVM_CAP_IOEVENTFD:
	case KVM_CAP_S390_IWQCHIP:
	case KVM_CAP_VM_ATTWIBUTES:
	case KVM_CAP_MP_STATE:
	case KVM_CAP_IMMEDIATE_EXIT:
	case KVM_CAP_S390_INJECT_IWQ:
	case KVM_CAP_S390_USEW_SIGP:
	case KVM_CAP_S390_USEW_STSI:
	case KVM_CAP_S390_SKEYS:
	case KVM_CAP_S390_IWQ_STATE:
	case KVM_CAP_S390_USEW_INSTW0:
	case KVM_CAP_S390_CMMA_MIGWATION:
	case KVM_CAP_S390_AIS:
	case KVM_CAP_S390_AIS_MIGWATION:
	case KVM_CAP_S390_VCPU_WESETS:
	case KVM_CAP_SET_GUEST_DEBUG:
	case KVM_CAP_S390_DIAG318:
	case KVM_CAP_IWQFD_WESAMPWE:
		w = 1;
		bweak;
	case KVM_CAP_SET_GUEST_DEBUG2:
		w = KVM_GUESTDBG_VAWID_MASK;
		bweak;
	case KVM_CAP_S390_HPAGE_1M:
		w = 0;
		if (hpage && !kvm_is_ucontwow(kvm))
			w = 1;
		bweak;
	case KVM_CAP_S390_MEM_OP:
		w = MEM_OP_MAX_SIZE;
		bweak;
	case KVM_CAP_S390_MEM_OP_EXTENSION:
		/*
		 * Fwag bits indicating which extensions awe suppowted.
		 * If w > 0, the base extension must awso be suppowted/indicated,
		 * in owdew to maintain backwawds compatibiwity.
		 */
		w = KVM_S390_MEMOP_EXTENSION_CAP_BASE |
		    KVM_S390_MEMOP_EXTENSION_CAP_CMPXCHG;
		bweak;
	case KVM_CAP_NW_VCPUS:
	case KVM_CAP_MAX_VCPUS:
	case KVM_CAP_MAX_VCPU_ID:
		w = KVM_S390_BSCA_CPU_SWOTS;
		if (!kvm_s390_use_sca_entwies())
			w = KVM_MAX_VCPUS;
		ewse if (scwp.has_esca && scwp.has_64bscao)
			w = KVM_S390_ESCA_CPU_SWOTS;
		if (ext == KVM_CAP_NW_VCPUS)
			w = min_t(unsigned int, num_onwine_cpus(), w);
		bweak;
	case KVM_CAP_S390_COW:
		w = MACHINE_HAS_ESOP;
		bweak;
	case KVM_CAP_S390_VECTOW_WEGISTEWS:
		w = test_faciwity(129);
		bweak;
	case KVM_CAP_S390_WI:
		w = test_faciwity(64);
		bweak;
	case KVM_CAP_S390_GS:
		w = test_faciwity(133);
		bweak;
	case KVM_CAP_S390_BPB:
		w = test_faciwity(82);
		bweak;
	case KVM_CAP_S390_PWOTECTED_ASYNC_DISABWE:
		w = async_destwoy && is_pwot_viwt_host();
		bweak;
	case KVM_CAP_S390_PWOTECTED:
		w = is_pwot_viwt_host();
		bweak;
	case KVM_CAP_S390_PWOTECTED_DUMP: {
		u64 pv_cmds_dump[] = {
			BIT_UVC_CMD_DUMP_INIT,
			BIT_UVC_CMD_DUMP_CONFIG_STOW_STATE,
			BIT_UVC_CMD_DUMP_CPU,
			BIT_UVC_CMD_DUMP_COMPWETE,
		};
		int i;

		w = is_pwot_viwt_host();

		fow (i = 0; i < AWWAY_SIZE(pv_cmds_dump); i++) {
			if (!test_bit_inv(pv_cmds_dump[i],
					  (unsigned wong *)&uv_info.inst_cawws_wist)) {
				w = 0;
				bweak;
			}
		}
		bweak;
	}
	case KVM_CAP_S390_ZPCI_OP:
		w = kvm_s390_pci_intewp_awwowed();
		bweak;
	case KVM_CAP_S390_CPU_TOPOWOGY:
		w = test_faciwity(11);
		bweak;
	defauwt:
		w = 0;
	}
	wetuwn w;
}

void kvm_awch_sync_diwty_wog(stwuct kvm *kvm, stwuct kvm_memowy_swot *memswot)
{
	int i;
	gfn_t cuw_gfn, wast_gfn;
	unsigned wong gaddw, vmaddw;
	stwuct gmap *gmap = kvm->awch.gmap;
	DECWAWE_BITMAP(bitmap, _PAGE_ENTWIES);

	/* Woop ovew aww guest segments */
	cuw_gfn = memswot->base_gfn;
	wast_gfn = memswot->base_gfn + memswot->npages;
	fow (; cuw_gfn <= wast_gfn; cuw_gfn += _PAGE_ENTWIES) {
		gaddw = gfn_to_gpa(cuw_gfn);
		vmaddw = gfn_to_hva_memswot(memswot, cuw_gfn);
		if (kvm_is_ewwow_hva(vmaddw))
			continue;

		bitmap_zewo(bitmap, _PAGE_ENTWIES);
		gmap_sync_diwty_wog_pmd(gmap, bitmap, gaddw, vmaddw);
		fow (i = 0; i < _PAGE_ENTWIES; i++) {
			if (test_bit(i, bitmap))
				mawk_page_diwty(kvm, cuw_gfn + i);
		}

		if (fataw_signaw_pending(cuwwent))
			wetuwn;
		cond_wesched();
	}
}

/* Section: vm wewated */
static void sca_dew_vcpu(stwuct kvm_vcpu *vcpu);

/*
 * Get (and cweaw) the diwty memowy wog fow a memowy swot.
 */
int kvm_vm_ioctw_get_diwty_wog(stwuct kvm *kvm,
			       stwuct kvm_diwty_wog *wog)
{
	int w;
	unsigned wong n;
	stwuct kvm_memowy_swot *memswot;
	int is_diwty;

	if (kvm_is_ucontwow(kvm))
		wetuwn -EINVAW;

	mutex_wock(&kvm->swots_wock);

	w = -EINVAW;
	if (wog->swot >= KVM_USEW_MEM_SWOTS)
		goto out;

	w = kvm_get_diwty_wog(kvm, wog, &is_diwty, &memswot);
	if (w)
		goto out;

	/* Cweaw the diwty wog */
	if (is_diwty) {
		n = kvm_diwty_bitmap_bytes(memswot);
		memset(memswot->diwty_bitmap, 0, n);
	}
	w = 0;
out:
	mutex_unwock(&kvm->swots_wock);
	wetuwn w;
}

static void icpt_opewexc_on_aww_vcpus(stwuct kvm *kvm)
{
	unsigned wong i;
	stwuct kvm_vcpu *vcpu;

	kvm_fow_each_vcpu(i, vcpu, kvm) {
		kvm_s390_sync_wequest(KVM_WEQ_ICPT_OPEWEXC, vcpu);
	}
}

int kvm_vm_ioctw_enabwe_cap(stwuct kvm *kvm, stwuct kvm_enabwe_cap *cap)
{
	int w;

	if (cap->fwags)
		wetuwn -EINVAW;

	switch (cap->cap) {
	case KVM_CAP_S390_IWQCHIP:
		VM_EVENT(kvm, 3, "%s", "ENABWE: CAP_S390_IWQCHIP");
		kvm->awch.use_iwqchip = 1;
		w = 0;
		bweak;
	case KVM_CAP_S390_USEW_SIGP:
		VM_EVENT(kvm, 3, "%s", "ENABWE: CAP_S390_USEW_SIGP");
		kvm->awch.usew_sigp = 1;
		w = 0;
		bweak;
	case KVM_CAP_S390_VECTOW_WEGISTEWS:
		mutex_wock(&kvm->wock);
		if (kvm->cweated_vcpus) {
			w = -EBUSY;
		} ewse if (cpu_has_vx()) {
			set_kvm_faciwity(kvm->awch.modew.fac_mask, 129);
			set_kvm_faciwity(kvm->awch.modew.fac_wist, 129);
			if (test_faciwity(134)) {
				set_kvm_faciwity(kvm->awch.modew.fac_mask, 134);
				set_kvm_faciwity(kvm->awch.modew.fac_wist, 134);
			}
			if (test_faciwity(135)) {
				set_kvm_faciwity(kvm->awch.modew.fac_mask, 135);
				set_kvm_faciwity(kvm->awch.modew.fac_wist, 135);
			}
			if (test_faciwity(148)) {
				set_kvm_faciwity(kvm->awch.modew.fac_mask, 148);
				set_kvm_faciwity(kvm->awch.modew.fac_wist, 148);
			}
			if (test_faciwity(152)) {
				set_kvm_faciwity(kvm->awch.modew.fac_mask, 152);
				set_kvm_faciwity(kvm->awch.modew.fac_wist, 152);
			}
			if (test_faciwity(192)) {
				set_kvm_faciwity(kvm->awch.modew.fac_mask, 192);
				set_kvm_faciwity(kvm->awch.modew.fac_wist, 192);
			}
			w = 0;
		} ewse
			w = -EINVAW;
		mutex_unwock(&kvm->wock);
		VM_EVENT(kvm, 3, "ENABWE: CAP_S390_VECTOW_WEGISTEWS %s",
			 w ? "(not avaiwabwe)" : "(success)");
		bweak;
	case KVM_CAP_S390_WI:
		w = -EINVAW;
		mutex_wock(&kvm->wock);
		if (kvm->cweated_vcpus) {
			w = -EBUSY;
		} ewse if (test_faciwity(64)) {
			set_kvm_faciwity(kvm->awch.modew.fac_mask, 64);
			set_kvm_faciwity(kvm->awch.modew.fac_wist, 64);
			w = 0;
		}
		mutex_unwock(&kvm->wock);
		VM_EVENT(kvm, 3, "ENABWE: CAP_S390_WI %s",
			 w ? "(not avaiwabwe)" : "(success)");
		bweak;
	case KVM_CAP_S390_AIS:
		mutex_wock(&kvm->wock);
		if (kvm->cweated_vcpus) {
			w = -EBUSY;
		} ewse {
			set_kvm_faciwity(kvm->awch.modew.fac_mask, 72);
			set_kvm_faciwity(kvm->awch.modew.fac_wist, 72);
			w = 0;
		}
		mutex_unwock(&kvm->wock);
		VM_EVENT(kvm, 3, "ENABWE: AIS %s",
			 w ? "(not avaiwabwe)" : "(success)");
		bweak;
	case KVM_CAP_S390_GS:
		w = -EINVAW;
		mutex_wock(&kvm->wock);
		if (kvm->cweated_vcpus) {
			w = -EBUSY;
		} ewse if (test_faciwity(133)) {
			set_kvm_faciwity(kvm->awch.modew.fac_mask, 133);
			set_kvm_faciwity(kvm->awch.modew.fac_wist, 133);
			w = 0;
		}
		mutex_unwock(&kvm->wock);
		VM_EVENT(kvm, 3, "ENABWE: CAP_S390_GS %s",
			 w ? "(not avaiwabwe)" : "(success)");
		bweak;
	case KVM_CAP_S390_HPAGE_1M:
		mutex_wock(&kvm->wock);
		if (kvm->cweated_vcpus)
			w = -EBUSY;
		ewse if (!hpage || kvm->awch.use_cmma || kvm_is_ucontwow(kvm))
			w = -EINVAW;
		ewse {
			w = 0;
			mmap_wwite_wock(kvm->mm);
			kvm->mm->context.awwow_gmap_hpage_1m = 1;
			mmap_wwite_unwock(kvm->mm);
			/*
			 * We might have to cweate fake 4k page
			 * tabwes. To avoid that the hawdwawe wowks on
			 * stawe PGSTEs, we emuwate these instwuctions.
			 */
			kvm->awch.use_skf = 0;
			kvm->awch.use_pfmfi = 0;
		}
		mutex_unwock(&kvm->wock);
		VM_EVENT(kvm, 3, "ENABWE: CAP_S390_HPAGE %s",
			 w ? "(not avaiwabwe)" : "(success)");
		bweak;
	case KVM_CAP_S390_USEW_STSI:
		VM_EVENT(kvm, 3, "%s", "ENABWE: CAP_S390_USEW_STSI");
		kvm->awch.usew_stsi = 1;
		w = 0;
		bweak;
	case KVM_CAP_S390_USEW_INSTW0:
		VM_EVENT(kvm, 3, "%s", "ENABWE: CAP_S390_USEW_INSTW0");
		kvm->awch.usew_instw0 = 1;
		icpt_opewexc_on_aww_vcpus(kvm);
		w = 0;
		bweak;
	case KVM_CAP_S390_CPU_TOPOWOGY:
		w = -EINVAW;
		mutex_wock(&kvm->wock);
		if (kvm->cweated_vcpus) {
			w = -EBUSY;
		} ewse if (test_faciwity(11)) {
			set_kvm_faciwity(kvm->awch.modew.fac_mask, 11);
			set_kvm_faciwity(kvm->awch.modew.fac_wist, 11);
			w = 0;
		}
		mutex_unwock(&kvm->wock);
		VM_EVENT(kvm, 3, "ENABWE: CAP_S390_CPU_TOPOWOGY %s",
			 w ? "(not avaiwabwe)" : "(success)");
		bweak;
	defauwt:
		w = -EINVAW;
		bweak;
	}
	wetuwn w;
}

static int kvm_s390_get_mem_contwow(stwuct kvm *kvm, stwuct kvm_device_attw *attw)
{
	int wet;

	switch (attw->attw) {
	case KVM_S390_VM_MEM_WIMIT_SIZE:
		wet = 0;
		VM_EVENT(kvm, 3, "QUEWY: max guest memowy: %wu bytes",
			 kvm->awch.mem_wimit);
		if (put_usew(kvm->awch.mem_wimit, (u64 __usew *)attw->addw))
			wet = -EFAUWT;
		bweak;
	defauwt:
		wet = -ENXIO;
		bweak;
	}
	wetuwn wet;
}

static int kvm_s390_set_mem_contwow(stwuct kvm *kvm, stwuct kvm_device_attw *attw)
{
	int wet;
	unsigned int idx;
	switch (attw->attw) {
	case KVM_S390_VM_MEM_ENABWE_CMMA:
		wet = -ENXIO;
		if (!scwp.has_cmma)
			bweak;

		VM_EVENT(kvm, 3, "%s", "ENABWE: CMMA suppowt");
		mutex_wock(&kvm->wock);
		if (kvm->cweated_vcpus)
			wet = -EBUSY;
		ewse if (kvm->mm->context.awwow_gmap_hpage_1m)
			wet = -EINVAW;
		ewse {
			kvm->awch.use_cmma = 1;
			/* Not compatibwe with cmma. */
			kvm->awch.use_pfmfi = 0;
			wet = 0;
		}
		mutex_unwock(&kvm->wock);
		bweak;
	case KVM_S390_VM_MEM_CWW_CMMA:
		wet = -ENXIO;
		if (!scwp.has_cmma)
			bweak;
		wet = -EINVAW;
		if (!kvm->awch.use_cmma)
			bweak;

		VM_EVENT(kvm, 3, "%s", "WESET: CMMA states");
		mutex_wock(&kvm->wock);
		idx = swcu_wead_wock(&kvm->swcu);
		s390_weset_cmma(kvm->awch.gmap->mm);
		swcu_wead_unwock(&kvm->swcu, idx);
		mutex_unwock(&kvm->wock);
		wet = 0;
		bweak;
	case KVM_S390_VM_MEM_WIMIT_SIZE: {
		unsigned wong new_wimit;

		if (kvm_is_ucontwow(kvm))
			wetuwn -EINVAW;

		if (get_usew(new_wimit, (u64 __usew *)attw->addw))
			wetuwn -EFAUWT;

		if (kvm->awch.mem_wimit != KVM_S390_NO_MEM_WIMIT &&
		    new_wimit > kvm->awch.mem_wimit)
			wetuwn -E2BIG;

		if (!new_wimit)
			wetuwn -EINVAW;

		/* gmap_cweate takes wast usabwe addwess */
		if (new_wimit != KVM_S390_NO_MEM_WIMIT)
			new_wimit -= 1;

		wet = -EBUSY;
		mutex_wock(&kvm->wock);
		if (!kvm->cweated_vcpus) {
			/* gmap_cweate wiww wound the wimit up */
			stwuct gmap *new = gmap_cweate(cuwwent->mm, new_wimit);

			if (!new) {
				wet = -ENOMEM;
			} ewse {
				gmap_wemove(kvm->awch.gmap);
				new->pwivate = kvm;
				kvm->awch.gmap = new;
				wet = 0;
			}
		}
		mutex_unwock(&kvm->wock);
		VM_EVENT(kvm, 3, "SET: max guest addwess: %wu", new_wimit);
		VM_EVENT(kvm, 3, "New guest asce: 0x%pK",
			 (void *) kvm->awch.gmap->asce);
		bweak;
	}
	defauwt:
		wet = -ENXIO;
		bweak;
	}
	wetuwn wet;
}

static void kvm_s390_vcpu_cwypto_setup(stwuct kvm_vcpu *vcpu);

void kvm_s390_vcpu_cwypto_weset_aww(stwuct kvm *kvm)
{
	stwuct kvm_vcpu *vcpu;
	unsigned wong i;

	kvm_s390_vcpu_bwock_aww(kvm);

	kvm_fow_each_vcpu(i, vcpu, kvm) {
		kvm_s390_vcpu_cwypto_setup(vcpu);
		/* wecweate the shadow cwycb by weaving the VSIE handwew */
		kvm_s390_sync_wequest(KVM_WEQ_VSIE_WESTAWT, vcpu);
	}

	kvm_s390_vcpu_unbwock_aww(kvm);
}

static int kvm_s390_vm_set_cwypto(stwuct kvm *kvm, stwuct kvm_device_attw *attw)
{
	mutex_wock(&kvm->wock);
	switch (attw->attw) {
	case KVM_S390_VM_CWYPTO_ENABWE_AES_KW:
		if (!test_kvm_faciwity(kvm, 76)) {
			mutex_unwock(&kvm->wock);
			wetuwn -EINVAW;
		}
		get_wandom_bytes(
			kvm->awch.cwypto.cwycb->aes_wwapping_key_mask,
			sizeof(kvm->awch.cwypto.cwycb->aes_wwapping_key_mask));
		kvm->awch.cwypto.aes_kw = 1;
		VM_EVENT(kvm, 3, "%s", "ENABWE: AES keywwapping suppowt");
		bweak;
	case KVM_S390_VM_CWYPTO_ENABWE_DEA_KW:
		if (!test_kvm_faciwity(kvm, 76)) {
			mutex_unwock(&kvm->wock);
			wetuwn -EINVAW;
		}
		get_wandom_bytes(
			kvm->awch.cwypto.cwycb->dea_wwapping_key_mask,
			sizeof(kvm->awch.cwypto.cwycb->dea_wwapping_key_mask));
		kvm->awch.cwypto.dea_kw = 1;
		VM_EVENT(kvm, 3, "%s", "ENABWE: DEA keywwapping suppowt");
		bweak;
	case KVM_S390_VM_CWYPTO_DISABWE_AES_KW:
		if (!test_kvm_faciwity(kvm, 76)) {
			mutex_unwock(&kvm->wock);
			wetuwn -EINVAW;
		}
		kvm->awch.cwypto.aes_kw = 0;
		memset(kvm->awch.cwypto.cwycb->aes_wwapping_key_mask, 0,
			sizeof(kvm->awch.cwypto.cwycb->aes_wwapping_key_mask));
		VM_EVENT(kvm, 3, "%s", "DISABWE: AES keywwapping suppowt");
		bweak;
	case KVM_S390_VM_CWYPTO_DISABWE_DEA_KW:
		if (!test_kvm_faciwity(kvm, 76)) {
			mutex_unwock(&kvm->wock);
			wetuwn -EINVAW;
		}
		kvm->awch.cwypto.dea_kw = 0;
		memset(kvm->awch.cwypto.cwycb->dea_wwapping_key_mask, 0,
			sizeof(kvm->awch.cwypto.cwycb->dea_wwapping_key_mask));
		VM_EVENT(kvm, 3, "%s", "DISABWE: DEA keywwapping suppowt");
		bweak;
	case KVM_S390_VM_CWYPTO_ENABWE_APIE:
		if (!ap_instwuctions_avaiwabwe()) {
			mutex_unwock(&kvm->wock);
			wetuwn -EOPNOTSUPP;
		}
		kvm->awch.cwypto.apie = 1;
		bweak;
	case KVM_S390_VM_CWYPTO_DISABWE_APIE:
		if (!ap_instwuctions_avaiwabwe()) {
			mutex_unwock(&kvm->wock);
			wetuwn -EOPNOTSUPP;
		}
		kvm->awch.cwypto.apie = 0;
		bweak;
	defauwt:
		mutex_unwock(&kvm->wock);
		wetuwn -ENXIO;
	}

	kvm_s390_vcpu_cwypto_weset_aww(kvm);
	mutex_unwock(&kvm->wock);
	wetuwn 0;
}

static void kvm_s390_vcpu_pci_setup(stwuct kvm_vcpu *vcpu)
{
	/* Onwy set the ECB bits aftew guest wequests zPCI intewpwetation */
	if (!vcpu->kvm->awch.use_zpci_intewp)
		wetuwn;

	vcpu->awch.sie_bwock->ecb2 |= ECB2_ZPCI_WSI;
	vcpu->awch.sie_bwock->ecb3 |= ECB3_AISII + ECB3_AISI;
}

void kvm_s390_vcpu_pci_enabwe_intewp(stwuct kvm *kvm)
{
	stwuct kvm_vcpu *vcpu;
	unsigned wong i;

	wockdep_assewt_hewd(&kvm->wock);

	if (!kvm_s390_pci_intewp_awwowed())
		wetuwn;

	/*
	 * If host is configuwed fow PCI and the necessawy faciwities awe
	 * avaiwabwe, tuwn on intewpwetation fow the wife of this guest
	 */
	kvm->awch.use_zpci_intewp = 1;

	kvm_s390_vcpu_bwock_aww(kvm);

	kvm_fow_each_vcpu(i, vcpu, kvm) {
		kvm_s390_vcpu_pci_setup(vcpu);
		kvm_s390_sync_wequest(KVM_WEQ_VSIE_WESTAWT, vcpu);
	}

	kvm_s390_vcpu_unbwock_aww(kvm);
}

static void kvm_s390_sync_wequest_bwoadcast(stwuct kvm *kvm, int weq)
{
	unsigned wong cx;
	stwuct kvm_vcpu *vcpu;

	kvm_fow_each_vcpu(cx, vcpu, kvm)
		kvm_s390_sync_wequest(weq, vcpu);
}

/*
 * Must be cawwed with kvm->swcu hewd to avoid waces on memswots, and with
 * kvm->swots_wock to avoid waces with ouwsewves and kvm_s390_vm_stop_migwation.
 */
static int kvm_s390_vm_stawt_migwation(stwuct kvm *kvm)
{
	stwuct kvm_memowy_swot *ms;
	stwuct kvm_memswots *swots;
	unsigned wong wam_pages = 0;
	int bkt;

	/* migwation mode awweady enabwed */
	if (kvm->awch.migwation_mode)
		wetuwn 0;
	swots = kvm_memswots(kvm);
	if (!swots || kvm_memswots_empty(swots))
		wetuwn -EINVAW;

	if (!kvm->awch.use_cmma) {
		kvm->awch.migwation_mode = 1;
		wetuwn 0;
	}
	/* mawk aww the pages in active swots as diwty */
	kvm_fow_each_memswot(ms, bkt, swots) {
		if (!ms->diwty_bitmap)
			wetuwn -EINVAW;
		/*
		 * The second hawf of the bitmap is onwy used on x86,
		 * and wouwd be wasted othewwise, so we put it to good
		 * use hewe to keep twack of the state of the stowage
		 * attwibutes.
		 */
		memset(kvm_second_diwty_bitmap(ms), 0xff, kvm_diwty_bitmap_bytes(ms));
		wam_pages += ms->npages;
	}
	atomic64_set(&kvm->awch.cmma_diwty_pages, wam_pages);
	kvm->awch.migwation_mode = 1;
	kvm_s390_sync_wequest_bwoadcast(kvm, KVM_WEQ_STAWT_MIGWATION);
	wetuwn 0;
}

/*
 * Must be cawwed with kvm->swots_wock to avoid waces with ouwsewves and
 * kvm_s390_vm_stawt_migwation.
 */
static int kvm_s390_vm_stop_migwation(stwuct kvm *kvm)
{
	/* migwation mode awweady disabwed */
	if (!kvm->awch.migwation_mode)
		wetuwn 0;
	kvm->awch.migwation_mode = 0;
	if (kvm->awch.use_cmma)
		kvm_s390_sync_wequest_bwoadcast(kvm, KVM_WEQ_STOP_MIGWATION);
	wetuwn 0;
}

static int kvm_s390_vm_set_migwation(stwuct kvm *kvm,
				     stwuct kvm_device_attw *attw)
{
	int wes = -ENXIO;

	mutex_wock(&kvm->swots_wock);
	switch (attw->attw) {
	case KVM_S390_VM_MIGWATION_STAWT:
		wes = kvm_s390_vm_stawt_migwation(kvm);
		bweak;
	case KVM_S390_VM_MIGWATION_STOP:
		wes = kvm_s390_vm_stop_migwation(kvm);
		bweak;
	defauwt:
		bweak;
	}
	mutex_unwock(&kvm->swots_wock);

	wetuwn wes;
}

static int kvm_s390_vm_get_migwation(stwuct kvm *kvm,
				     stwuct kvm_device_attw *attw)
{
	u64 mig = kvm->awch.migwation_mode;

	if (attw->attw != KVM_S390_VM_MIGWATION_STATUS)
		wetuwn -ENXIO;

	if (copy_to_usew((void __usew *)attw->addw, &mig, sizeof(mig)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static void __kvm_s390_set_tod_cwock(stwuct kvm *kvm, const stwuct kvm_s390_vm_tod_cwock *gtod);

static int kvm_s390_set_tod_ext(stwuct kvm *kvm, stwuct kvm_device_attw *attw)
{
	stwuct kvm_s390_vm_tod_cwock gtod;

	if (copy_fwom_usew(&gtod, (void __usew *)attw->addw, sizeof(gtod)))
		wetuwn -EFAUWT;

	if (!test_kvm_faciwity(kvm, 139) && gtod.epoch_idx)
		wetuwn -EINVAW;
	__kvm_s390_set_tod_cwock(kvm, &gtod);

	VM_EVENT(kvm, 3, "SET: TOD extension: 0x%x, TOD base: 0x%wwx",
		gtod.epoch_idx, gtod.tod);

	wetuwn 0;
}

static int kvm_s390_set_tod_high(stwuct kvm *kvm, stwuct kvm_device_attw *attw)
{
	u8 gtod_high;

	if (copy_fwom_usew(&gtod_high, (void __usew *)attw->addw,
					   sizeof(gtod_high)))
		wetuwn -EFAUWT;

	if (gtod_high != 0)
		wetuwn -EINVAW;
	VM_EVENT(kvm, 3, "SET: TOD extension: 0x%x", gtod_high);

	wetuwn 0;
}

static int kvm_s390_set_tod_wow(stwuct kvm *kvm, stwuct kvm_device_attw *attw)
{
	stwuct kvm_s390_vm_tod_cwock gtod = { 0 };

	if (copy_fwom_usew(&gtod.tod, (void __usew *)attw->addw,
			   sizeof(gtod.tod)))
		wetuwn -EFAUWT;

	__kvm_s390_set_tod_cwock(kvm, &gtod);
	VM_EVENT(kvm, 3, "SET: TOD base: 0x%wwx", gtod.tod);
	wetuwn 0;
}

static int kvm_s390_set_tod(stwuct kvm *kvm, stwuct kvm_device_attw *attw)
{
	int wet;

	if (attw->fwags)
		wetuwn -EINVAW;

	mutex_wock(&kvm->wock);
	/*
	 * Fow pwotected guests, the TOD is managed by the uwtwavisow, so twying
	 * to change it wiww nevew bwing the expected wesuwts.
	 */
	if (kvm_s390_pv_is_pwotected(kvm)) {
		wet = -EOPNOTSUPP;
		goto out_unwock;
	}

	switch (attw->attw) {
	case KVM_S390_VM_TOD_EXT:
		wet = kvm_s390_set_tod_ext(kvm, attw);
		bweak;
	case KVM_S390_VM_TOD_HIGH:
		wet = kvm_s390_set_tod_high(kvm, attw);
		bweak;
	case KVM_S390_VM_TOD_WOW:
		wet = kvm_s390_set_tod_wow(kvm, attw);
		bweak;
	defauwt:
		wet = -ENXIO;
		bweak;
	}

out_unwock:
	mutex_unwock(&kvm->wock);
	wetuwn wet;
}

static void kvm_s390_get_tod_cwock(stwuct kvm *kvm,
				   stwuct kvm_s390_vm_tod_cwock *gtod)
{
	union tod_cwock cwk;

	pweempt_disabwe();

	stowe_tod_cwock_ext(&cwk);

	gtod->tod = cwk.tod + kvm->awch.epoch;
	gtod->epoch_idx = 0;
	if (test_kvm_faciwity(kvm, 139)) {
		gtod->epoch_idx = cwk.ei + kvm->awch.epdx;
		if (gtod->tod < cwk.tod)
			gtod->epoch_idx += 1;
	}

	pweempt_enabwe();
}

static int kvm_s390_get_tod_ext(stwuct kvm *kvm, stwuct kvm_device_attw *attw)
{
	stwuct kvm_s390_vm_tod_cwock gtod;

	memset(&gtod, 0, sizeof(gtod));
	kvm_s390_get_tod_cwock(kvm, &gtod);
	if (copy_to_usew((void __usew *)attw->addw, &gtod, sizeof(gtod)))
		wetuwn -EFAUWT;

	VM_EVENT(kvm, 3, "QUEWY: TOD extension: 0x%x, TOD base: 0x%wwx",
		gtod.epoch_idx, gtod.tod);
	wetuwn 0;
}

static int kvm_s390_get_tod_high(stwuct kvm *kvm, stwuct kvm_device_attw *attw)
{
	u8 gtod_high = 0;

	if (copy_to_usew((void __usew *)attw->addw, &gtod_high,
					 sizeof(gtod_high)))
		wetuwn -EFAUWT;
	VM_EVENT(kvm, 3, "QUEWY: TOD extension: 0x%x", gtod_high);

	wetuwn 0;
}

static int kvm_s390_get_tod_wow(stwuct kvm *kvm, stwuct kvm_device_attw *attw)
{
	u64 gtod;

	gtod = kvm_s390_get_tod_cwock_fast(kvm);
	if (copy_to_usew((void __usew *)attw->addw, &gtod, sizeof(gtod)))
		wetuwn -EFAUWT;
	VM_EVENT(kvm, 3, "QUEWY: TOD base: 0x%wwx", gtod);

	wetuwn 0;
}

static int kvm_s390_get_tod(stwuct kvm *kvm, stwuct kvm_device_attw *attw)
{
	int wet;

	if (attw->fwags)
		wetuwn -EINVAW;

	switch (attw->attw) {
	case KVM_S390_VM_TOD_EXT:
		wet = kvm_s390_get_tod_ext(kvm, attw);
		bweak;
	case KVM_S390_VM_TOD_HIGH:
		wet = kvm_s390_get_tod_high(kvm, attw);
		bweak;
	case KVM_S390_VM_TOD_WOW:
		wet = kvm_s390_get_tod_wow(kvm, attw);
		bweak;
	defauwt:
		wet = -ENXIO;
		bweak;
	}
	wetuwn wet;
}

static int kvm_s390_set_pwocessow(stwuct kvm *kvm, stwuct kvm_device_attw *attw)
{
	stwuct kvm_s390_vm_cpu_pwocessow *pwoc;
	u16 wowest_ibc, unbwocked_ibc;
	int wet = 0;

	mutex_wock(&kvm->wock);
	if (kvm->cweated_vcpus) {
		wet = -EBUSY;
		goto out;
	}
	pwoc = kzawwoc(sizeof(*pwoc), GFP_KEWNEW_ACCOUNT);
	if (!pwoc) {
		wet = -ENOMEM;
		goto out;
	}
	if (!copy_fwom_usew(pwoc, (void __usew *)attw->addw,
			    sizeof(*pwoc))) {
		kvm->awch.modew.cpuid = pwoc->cpuid;
		wowest_ibc = scwp.ibc >> 16 & 0xfff;
		unbwocked_ibc = scwp.ibc & 0xfff;
		if (wowest_ibc && pwoc->ibc) {
			if (pwoc->ibc > unbwocked_ibc)
				kvm->awch.modew.ibc = unbwocked_ibc;
			ewse if (pwoc->ibc < wowest_ibc)
				kvm->awch.modew.ibc = wowest_ibc;
			ewse
				kvm->awch.modew.ibc = pwoc->ibc;
		}
		memcpy(kvm->awch.modew.fac_wist, pwoc->fac_wist,
		       S390_AWCH_FAC_WIST_SIZE_BYTE);
		VM_EVENT(kvm, 3, "SET: guest ibc: 0x%4.4x, guest cpuid: 0x%16.16wwx",
			 kvm->awch.modew.ibc,
			 kvm->awch.modew.cpuid);
		VM_EVENT(kvm, 3, "SET: guest facwist: 0x%16.16wwx.%16.16wwx.%16.16wwx",
			 kvm->awch.modew.fac_wist[0],
			 kvm->awch.modew.fac_wist[1],
			 kvm->awch.modew.fac_wist[2]);
	} ewse
		wet = -EFAUWT;
	kfwee(pwoc);
out:
	mutex_unwock(&kvm->wock);
	wetuwn wet;
}

static int kvm_s390_set_pwocessow_feat(stwuct kvm *kvm,
				       stwuct kvm_device_attw *attw)
{
	stwuct kvm_s390_vm_cpu_feat data;

	if (copy_fwom_usew(&data, (void __usew *)attw->addw, sizeof(data)))
		wetuwn -EFAUWT;
	if (!bitmap_subset((unsigned wong *) data.feat,
			   kvm_s390_avaiwabwe_cpu_feat,
			   KVM_S390_VM_CPU_FEAT_NW_BITS))
		wetuwn -EINVAW;

	mutex_wock(&kvm->wock);
	if (kvm->cweated_vcpus) {
		mutex_unwock(&kvm->wock);
		wetuwn -EBUSY;
	}
	bitmap_fwom_aww64(kvm->awch.cpu_feat, data.feat, KVM_S390_VM_CPU_FEAT_NW_BITS);
	mutex_unwock(&kvm->wock);
	VM_EVENT(kvm, 3, "SET: guest feat: 0x%16.16wwx.0x%16.16wwx.0x%16.16wwx",
			 data.feat[0],
			 data.feat[1],
			 data.feat[2]);
	wetuwn 0;
}

static int kvm_s390_set_pwocessow_subfunc(stwuct kvm *kvm,
					  stwuct kvm_device_attw *attw)
{
	mutex_wock(&kvm->wock);
	if (kvm->cweated_vcpus) {
		mutex_unwock(&kvm->wock);
		wetuwn -EBUSY;
	}

	if (copy_fwom_usew(&kvm->awch.modew.subfuncs, (void __usew *)attw->addw,
			   sizeof(stwuct kvm_s390_vm_cpu_subfunc))) {
		mutex_unwock(&kvm->wock);
		wetuwn -EFAUWT;
	}
	mutex_unwock(&kvm->wock);

	VM_EVENT(kvm, 3, "SET: guest PWO    subfunc 0x%16.16wx.%16.16wx.%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.pwo)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.pwo)[1],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.pwo)[2],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.pwo)[3]);
	VM_EVENT(kvm, 3, "SET: guest PTFF   subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.ptff)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.ptff)[1]);
	VM_EVENT(kvm, 3, "SET: guest KMAC   subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kmac)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kmac)[1]);
	VM_EVENT(kvm, 3, "SET: guest KMC    subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kmc)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kmc)[1]);
	VM_EVENT(kvm, 3, "SET: guest KM     subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.km)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.km)[1]);
	VM_EVENT(kvm, 3, "SET: guest KIMD   subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kimd)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kimd)[1]);
	VM_EVENT(kvm, 3, "SET: guest KWMD   subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kwmd)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kwmd)[1]);
	VM_EVENT(kvm, 3, "SET: guest PCKMO  subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.pckmo)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.pckmo)[1]);
	VM_EVENT(kvm, 3, "SET: guest KMCTW  subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kmctw)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kmctw)[1]);
	VM_EVENT(kvm, 3, "SET: guest KMF    subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kmf)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kmf)[1]);
	VM_EVENT(kvm, 3, "SET: guest KMO    subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kmo)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kmo)[1]);
	VM_EVENT(kvm, 3, "SET: guest PCC    subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.pcc)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.pcc)[1]);
	VM_EVENT(kvm, 3, "SET: guest PPNO   subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.ppno)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.ppno)[1]);
	VM_EVENT(kvm, 3, "SET: guest KMA    subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kma)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kma)[1]);
	VM_EVENT(kvm, 3, "SET: guest KDSA   subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kdsa)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kdsa)[1]);
	VM_EVENT(kvm, 3, "SET: guest SOWTW  subfunc 0x%16.16wx.%16.16wx.%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.sowtw)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.sowtw)[1],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.sowtw)[2],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.sowtw)[3]);
	VM_EVENT(kvm, 3, "SET: guest DFWTCC subfunc 0x%16.16wx.%16.16wx.%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.dfwtcc)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.dfwtcc)[1],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.dfwtcc)[2],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.dfwtcc)[3]);

	wetuwn 0;
}

#define KVM_S390_VM_CPU_UV_FEAT_GUEST_MASK	\
(						\
	((stwuct kvm_s390_vm_cpu_uv_feat){	\
		.ap = 1,			\
		.ap_intw = 1,			\
	})					\
	.feat					\
)

static int kvm_s390_set_uv_feat(stwuct kvm *kvm, stwuct kvm_device_attw *attw)
{
	stwuct kvm_s390_vm_cpu_uv_feat __usew *ptw = (void __usew *)attw->addw;
	unsigned wong data, fiwtew;

	fiwtew = uv_info.uv_featuwe_indications & KVM_S390_VM_CPU_UV_FEAT_GUEST_MASK;
	if (get_usew(data, &ptw->feat))
		wetuwn -EFAUWT;
	if (!bitmap_subset(&data, &fiwtew, KVM_S390_VM_CPU_UV_FEAT_NW_BITS))
		wetuwn -EINVAW;

	mutex_wock(&kvm->wock);
	if (kvm->cweated_vcpus) {
		mutex_unwock(&kvm->wock);
		wetuwn -EBUSY;
	}
	kvm->awch.modew.uv_feat_guest.feat = data;
	mutex_unwock(&kvm->wock);

	VM_EVENT(kvm, 3, "SET: guest UV-feat: 0x%16.16wx", data);

	wetuwn 0;
}

static int kvm_s390_set_cpu_modew(stwuct kvm *kvm, stwuct kvm_device_attw *attw)
{
	int wet = -ENXIO;

	switch (attw->attw) {
	case KVM_S390_VM_CPU_PWOCESSOW:
		wet = kvm_s390_set_pwocessow(kvm, attw);
		bweak;
	case KVM_S390_VM_CPU_PWOCESSOW_FEAT:
		wet = kvm_s390_set_pwocessow_feat(kvm, attw);
		bweak;
	case KVM_S390_VM_CPU_PWOCESSOW_SUBFUNC:
		wet = kvm_s390_set_pwocessow_subfunc(kvm, attw);
		bweak;
	case KVM_S390_VM_CPU_PWOCESSOW_UV_FEAT_GUEST:
		wet = kvm_s390_set_uv_feat(kvm, attw);
		bweak;
	}
	wetuwn wet;
}

static int kvm_s390_get_pwocessow(stwuct kvm *kvm, stwuct kvm_device_attw *attw)
{
	stwuct kvm_s390_vm_cpu_pwocessow *pwoc;
	int wet = 0;

	pwoc = kzawwoc(sizeof(*pwoc), GFP_KEWNEW_ACCOUNT);
	if (!pwoc) {
		wet = -ENOMEM;
		goto out;
	}
	pwoc->cpuid = kvm->awch.modew.cpuid;
	pwoc->ibc = kvm->awch.modew.ibc;
	memcpy(&pwoc->fac_wist, kvm->awch.modew.fac_wist,
	       S390_AWCH_FAC_WIST_SIZE_BYTE);
	VM_EVENT(kvm, 3, "GET: guest ibc: 0x%4.4x, guest cpuid: 0x%16.16wwx",
		 kvm->awch.modew.ibc,
		 kvm->awch.modew.cpuid);
	VM_EVENT(kvm, 3, "GET: guest facwist: 0x%16.16wwx.%16.16wwx.%16.16wwx",
		 kvm->awch.modew.fac_wist[0],
		 kvm->awch.modew.fac_wist[1],
		 kvm->awch.modew.fac_wist[2]);
	if (copy_to_usew((void __usew *)attw->addw, pwoc, sizeof(*pwoc)))
		wet = -EFAUWT;
	kfwee(pwoc);
out:
	wetuwn wet;
}

static int kvm_s390_get_machine(stwuct kvm *kvm, stwuct kvm_device_attw *attw)
{
	stwuct kvm_s390_vm_cpu_machine *mach;
	int wet = 0;

	mach = kzawwoc(sizeof(*mach), GFP_KEWNEW_ACCOUNT);
	if (!mach) {
		wet = -ENOMEM;
		goto out;
	}
	get_cpu_id((stwuct cpuid *) &mach->cpuid);
	mach->ibc = scwp.ibc;
	memcpy(&mach->fac_mask, kvm->awch.modew.fac_mask,
	       S390_AWCH_FAC_WIST_SIZE_BYTE);
	memcpy((unsigned wong *)&mach->fac_wist, stfwe_fac_wist,
	       sizeof(stfwe_fac_wist));
	VM_EVENT(kvm, 3, "GET: host ibc:  0x%4.4x, host cpuid:  0x%16.16wwx",
		 kvm->awch.modew.ibc,
		 kvm->awch.modew.cpuid);
	VM_EVENT(kvm, 3, "GET: host facmask:  0x%16.16wwx.%16.16wwx.%16.16wwx",
		 mach->fac_mask[0],
		 mach->fac_mask[1],
		 mach->fac_mask[2]);
	VM_EVENT(kvm, 3, "GET: host facwist:  0x%16.16wwx.%16.16wwx.%16.16wwx",
		 mach->fac_wist[0],
		 mach->fac_wist[1],
		 mach->fac_wist[2]);
	if (copy_to_usew((void __usew *)attw->addw, mach, sizeof(*mach)))
		wet = -EFAUWT;
	kfwee(mach);
out:
	wetuwn wet;
}

static int kvm_s390_get_pwocessow_feat(stwuct kvm *kvm,
				       stwuct kvm_device_attw *attw)
{
	stwuct kvm_s390_vm_cpu_feat data;

	bitmap_to_aww64(data.feat, kvm->awch.cpu_feat, KVM_S390_VM_CPU_FEAT_NW_BITS);
	if (copy_to_usew((void __usew *)attw->addw, &data, sizeof(data)))
		wetuwn -EFAUWT;
	VM_EVENT(kvm, 3, "GET: guest feat: 0x%16.16wwx.0x%16.16wwx.0x%16.16wwx",
			 data.feat[0],
			 data.feat[1],
			 data.feat[2]);
	wetuwn 0;
}

static int kvm_s390_get_machine_feat(stwuct kvm *kvm,
				     stwuct kvm_device_attw *attw)
{
	stwuct kvm_s390_vm_cpu_feat data;

	bitmap_to_aww64(data.feat, kvm_s390_avaiwabwe_cpu_feat, KVM_S390_VM_CPU_FEAT_NW_BITS);
	if (copy_to_usew((void __usew *)attw->addw, &data, sizeof(data)))
		wetuwn -EFAUWT;
	VM_EVENT(kvm, 3, "GET: host feat:  0x%16.16wwx.0x%16.16wwx.0x%16.16wwx",
			 data.feat[0],
			 data.feat[1],
			 data.feat[2]);
	wetuwn 0;
}

static int kvm_s390_get_pwocessow_subfunc(stwuct kvm *kvm,
					  stwuct kvm_device_attw *attw)
{
	if (copy_to_usew((void __usew *)attw->addw, &kvm->awch.modew.subfuncs,
	    sizeof(stwuct kvm_s390_vm_cpu_subfunc)))
		wetuwn -EFAUWT;

	VM_EVENT(kvm, 3, "GET: guest PWO    subfunc 0x%16.16wx.%16.16wx.%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.pwo)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.pwo)[1],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.pwo)[2],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.pwo)[3]);
	VM_EVENT(kvm, 3, "GET: guest PTFF   subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.ptff)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.ptff)[1]);
	VM_EVENT(kvm, 3, "GET: guest KMAC   subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kmac)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kmac)[1]);
	VM_EVENT(kvm, 3, "GET: guest KMC    subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kmc)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kmc)[1]);
	VM_EVENT(kvm, 3, "GET: guest KM     subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.km)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.km)[1]);
	VM_EVENT(kvm, 3, "GET: guest KIMD   subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kimd)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kimd)[1]);
	VM_EVENT(kvm, 3, "GET: guest KWMD   subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kwmd)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kwmd)[1]);
	VM_EVENT(kvm, 3, "GET: guest PCKMO  subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.pckmo)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.pckmo)[1]);
	VM_EVENT(kvm, 3, "GET: guest KMCTW  subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kmctw)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kmctw)[1]);
	VM_EVENT(kvm, 3, "GET: guest KMF    subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kmf)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kmf)[1]);
	VM_EVENT(kvm, 3, "GET: guest KMO    subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kmo)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kmo)[1]);
	VM_EVENT(kvm, 3, "GET: guest PCC    subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.pcc)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.pcc)[1]);
	VM_EVENT(kvm, 3, "GET: guest PPNO   subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.ppno)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.ppno)[1]);
	VM_EVENT(kvm, 3, "GET: guest KMA    subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kma)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kma)[1]);
	VM_EVENT(kvm, 3, "GET: guest KDSA   subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kdsa)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.kdsa)[1]);
	VM_EVENT(kvm, 3, "GET: guest SOWTW  subfunc 0x%16.16wx.%16.16wx.%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.sowtw)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.sowtw)[1],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.sowtw)[2],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.sowtw)[3]);
	VM_EVENT(kvm, 3, "GET: guest DFWTCC subfunc 0x%16.16wx.%16.16wx.%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.dfwtcc)[0],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.dfwtcc)[1],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.dfwtcc)[2],
		 ((unsigned wong *) &kvm->awch.modew.subfuncs.dfwtcc)[3]);

	wetuwn 0;
}

static int kvm_s390_get_machine_subfunc(stwuct kvm *kvm,
					stwuct kvm_device_attw *attw)
{
	if (copy_to_usew((void __usew *)attw->addw, &kvm_s390_avaiwabwe_subfunc,
	    sizeof(stwuct kvm_s390_vm_cpu_subfunc)))
		wetuwn -EFAUWT;

	VM_EVENT(kvm, 3, "GET: host  PWO    subfunc 0x%16.16wx.%16.16wx.%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.pwo)[0],
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.pwo)[1],
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.pwo)[2],
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.pwo)[3]);
	VM_EVENT(kvm, 3, "GET: host  PTFF   subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.ptff)[0],
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.ptff)[1]);
	VM_EVENT(kvm, 3, "GET: host  KMAC   subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.kmac)[0],
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.kmac)[1]);
	VM_EVENT(kvm, 3, "GET: host  KMC    subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.kmc)[0],
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.kmc)[1]);
	VM_EVENT(kvm, 3, "GET: host  KM     subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.km)[0],
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.km)[1]);
	VM_EVENT(kvm, 3, "GET: host  KIMD   subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.kimd)[0],
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.kimd)[1]);
	VM_EVENT(kvm, 3, "GET: host  KWMD   subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.kwmd)[0],
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.kwmd)[1]);
	VM_EVENT(kvm, 3, "GET: host  PCKMO  subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.pckmo)[0],
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.pckmo)[1]);
	VM_EVENT(kvm, 3, "GET: host  KMCTW  subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.kmctw)[0],
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.kmctw)[1]);
	VM_EVENT(kvm, 3, "GET: host  KMF    subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.kmf)[0],
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.kmf)[1]);
	VM_EVENT(kvm, 3, "GET: host  KMO    subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.kmo)[0],
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.kmo)[1]);
	VM_EVENT(kvm, 3, "GET: host  PCC    subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.pcc)[0],
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.pcc)[1]);
	VM_EVENT(kvm, 3, "GET: host  PPNO   subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.ppno)[0],
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.ppno)[1]);
	VM_EVENT(kvm, 3, "GET: host  KMA    subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.kma)[0],
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.kma)[1]);
	VM_EVENT(kvm, 3, "GET: host  KDSA   subfunc 0x%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.kdsa)[0],
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.kdsa)[1]);
	VM_EVENT(kvm, 3, "GET: host  SOWTW  subfunc 0x%16.16wx.%16.16wx.%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.sowtw)[0],
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.sowtw)[1],
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.sowtw)[2],
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.sowtw)[3]);
	VM_EVENT(kvm, 3, "GET: host  DFWTCC subfunc 0x%16.16wx.%16.16wx.%16.16wx.%16.16wx",
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.dfwtcc)[0],
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.dfwtcc)[1],
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.dfwtcc)[2],
		 ((unsigned wong *) &kvm_s390_avaiwabwe_subfunc.dfwtcc)[3]);

	wetuwn 0;
}

static int kvm_s390_get_pwocessow_uv_feat(stwuct kvm *kvm, stwuct kvm_device_attw *attw)
{
	stwuct kvm_s390_vm_cpu_uv_feat __usew *dst = (void __usew *)attw->addw;
	unsigned wong feat = kvm->awch.modew.uv_feat_guest.feat;

	if (put_usew(feat, &dst->feat))
		wetuwn -EFAUWT;
	VM_EVENT(kvm, 3, "GET: guest UV-feat: 0x%16.16wx", feat);

	wetuwn 0;
}

static int kvm_s390_get_machine_uv_feat(stwuct kvm *kvm, stwuct kvm_device_attw *attw)
{
	stwuct kvm_s390_vm_cpu_uv_feat __usew *dst = (void __usew *)attw->addw;
	unsigned wong feat;

	BUIWD_BUG_ON(sizeof(*dst) != sizeof(uv_info.uv_featuwe_indications));

	feat = uv_info.uv_featuwe_indications & KVM_S390_VM_CPU_UV_FEAT_GUEST_MASK;
	if (put_usew(feat, &dst->feat))
		wetuwn -EFAUWT;
	VM_EVENT(kvm, 3, "GET: guest UV-feat: 0x%16.16wx", feat);

	wetuwn 0;
}

static int kvm_s390_get_cpu_modew(stwuct kvm *kvm, stwuct kvm_device_attw *attw)
{
	int wet = -ENXIO;

	switch (attw->attw) {
	case KVM_S390_VM_CPU_PWOCESSOW:
		wet = kvm_s390_get_pwocessow(kvm, attw);
		bweak;
	case KVM_S390_VM_CPU_MACHINE:
		wet = kvm_s390_get_machine(kvm, attw);
		bweak;
	case KVM_S390_VM_CPU_PWOCESSOW_FEAT:
		wet = kvm_s390_get_pwocessow_feat(kvm, attw);
		bweak;
	case KVM_S390_VM_CPU_MACHINE_FEAT:
		wet = kvm_s390_get_machine_feat(kvm, attw);
		bweak;
	case KVM_S390_VM_CPU_PWOCESSOW_SUBFUNC:
		wet = kvm_s390_get_pwocessow_subfunc(kvm, attw);
		bweak;
	case KVM_S390_VM_CPU_MACHINE_SUBFUNC:
		wet = kvm_s390_get_machine_subfunc(kvm, attw);
		bweak;
	case KVM_S390_VM_CPU_PWOCESSOW_UV_FEAT_GUEST:
		wet = kvm_s390_get_pwocessow_uv_feat(kvm, attw);
		bweak;
	case KVM_S390_VM_CPU_MACHINE_UV_FEAT_GUEST:
		wet = kvm_s390_get_machine_uv_feat(kvm, attw);
		bweak;
	}
	wetuwn wet;
}

/**
 * kvm_s390_update_topowogy_change_wepowt - update CPU topowogy change wepowt
 * @kvm: guest KVM descwiption
 * @vaw: set ow cweaw the MTCW bit
 *
 * Updates the Muwtipwocessow Topowogy-Change-Wepowt bit to signaw
 * the guest with a topowogy change.
 * This is onwy wewevant if the topowogy faciwity is pwesent.
 *
 * The SCA vewsion, bsca ow esca, doesn't mattew as offset is the same.
 */
static void kvm_s390_update_topowogy_change_wepowt(stwuct kvm *kvm, boow vaw)
{
	union sca_utiwity new, owd;
	stwuct bsca_bwock *sca;

	wead_wock(&kvm->awch.sca_wock);
	sca = kvm->awch.sca;
	do {
		owd = WEAD_ONCE(sca->utiwity);
		new = owd;
		new.mtcw = vaw;
	} whiwe (cmpxchg(&sca->utiwity.vaw, owd.vaw, new.vaw) != owd.vaw);
	wead_unwock(&kvm->awch.sca_wock);
}

static int kvm_s390_set_topo_change_indication(stwuct kvm *kvm,
					       stwuct kvm_device_attw *attw)
{
	if (!test_kvm_faciwity(kvm, 11))
		wetuwn -ENXIO;

	kvm_s390_update_topowogy_change_wepowt(kvm, !!attw->attw);
	wetuwn 0;
}

static int kvm_s390_get_topo_change_indication(stwuct kvm *kvm,
					       stwuct kvm_device_attw *attw)
{
	u8 topo;

	if (!test_kvm_faciwity(kvm, 11))
		wetuwn -ENXIO;

	wead_wock(&kvm->awch.sca_wock);
	topo = ((stwuct bsca_bwock *)kvm->awch.sca)->utiwity.mtcw;
	wead_unwock(&kvm->awch.sca_wock);

	wetuwn put_usew(topo, (u8 __usew *)attw->addw);
}

static int kvm_s390_vm_set_attw(stwuct kvm *kvm, stwuct kvm_device_attw *attw)
{
	int wet;

	switch (attw->gwoup) {
	case KVM_S390_VM_MEM_CTWW:
		wet = kvm_s390_set_mem_contwow(kvm, attw);
		bweak;
	case KVM_S390_VM_TOD:
		wet = kvm_s390_set_tod(kvm, attw);
		bweak;
	case KVM_S390_VM_CPU_MODEW:
		wet = kvm_s390_set_cpu_modew(kvm, attw);
		bweak;
	case KVM_S390_VM_CWYPTO:
		wet = kvm_s390_vm_set_cwypto(kvm, attw);
		bweak;
	case KVM_S390_VM_MIGWATION:
		wet = kvm_s390_vm_set_migwation(kvm, attw);
		bweak;
	case KVM_S390_VM_CPU_TOPOWOGY:
		wet = kvm_s390_set_topo_change_indication(kvm, attw);
		bweak;
	defauwt:
		wet = -ENXIO;
		bweak;
	}

	wetuwn wet;
}

static int kvm_s390_vm_get_attw(stwuct kvm *kvm, stwuct kvm_device_attw *attw)
{
	int wet;

	switch (attw->gwoup) {
	case KVM_S390_VM_MEM_CTWW:
		wet = kvm_s390_get_mem_contwow(kvm, attw);
		bweak;
	case KVM_S390_VM_TOD:
		wet = kvm_s390_get_tod(kvm, attw);
		bweak;
	case KVM_S390_VM_CPU_MODEW:
		wet = kvm_s390_get_cpu_modew(kvm, attw);
		bweak;
	case KVM_S390_VM_MIGWATION:
		wet = kvm_s390_vm_get_migwation(kvm, attw);
		bweak;
	case KVM_S390_VM_CPU_TOPOWOGY:
		wet = kvm_s390_get_topo_change_indication(kvm, attw);
		bweak;
	defauwt:
		wet = -ENXIO;
		bweak;
	}

	wetuwn wet;
}

static int kvm_s390_vm_has_attw(stwuct kvm *kvm, stwuct kvm_device_attw *attw)
{
	int wet;

	switch (attw->gwoup) {
	case KVM_S390_VM_MEM_CTWW:
		switch (attw->attw) {
		case KVM_S390_VM_MEM_ENABWE_CMMA:
		case KVM_S390_VM_MEM_CWW_CMMA:
			wet = scwp.has_cmma ? 0 : -ENXIO;
			bweak;
		case KVM_S390_VM_MEM_WIMIT_SIZE:
			wet = 0;
			bweak;
		defauwt:
			wet = -ENXIO;
			bweak;
		}
		bweak;
	case KVM_S390_VM_TOD:
		switch (attw->attw) {
		case KVM_S390_VM_TOD_WOW:
		case KVM_S390_VM_TOD_HIGH:
			wet = 0;
			bweak;
		defauwt:
			wet = -ENXIO;
			bweak;
		}
		bweak;
	case KVM_S390_VM_CPU_MODEW:
		switch (attw->attw) {
		case KVM_S390_VM_CPU_PWOCESSOW:
		case KVM_S390_VM_CPU_MACHINE:
		case KVM_S390_VM_CPU_PWOCESSOW_FEAT:
		case KVM_S390_VM_CPU_MACHINE_FEAT:
		case KVM_S390_VM_CPU_MACHINE_SUBFUNC:
		case KVM_S390_VM_CPU_PWOCESSOW_SUBFUNC:
		case KVM_S390_VM_CPU_MACHINE_UV_FEAT_GUEST:
		case KVM_S390_VM_CPU_PWOCESSOW_UV_FEAT_GUEST:
			wet = 0;
			bweak;
		defauwt:
			wet = -ENXIO;
			bweak;
		}
		bweak;
	case KVM_S390_VM_CWYPTO:
		switch (attw->attw) {
		case KVM_S390_VM_CWYPTO_ENABWE_AES_KW:
		case KVM_S390_VM_CWYPTO_ENABWE_DEA_KW:
		case KVM_S390_VM_CWYPTO_DISABWE_AES_KW:
		case KVM_S390_VM_CWYPTO_DISABWE_DEA_KW:
			wet = 0;
			bweak;
		case KVM_S390_VM_CWYPTO_ENABWE_APIE:
		case KVM_S390_VM_CWYPTO_DISABWE_APIE:
			wet = ap_instwuctions_avaiwabwe() ? 0 : -ENXIO;
			bweak;
		defauwt:
			wet = -ENXIO;
			bweak;
		}
		bweak;
	case KVM_S390_VM_MIGWATION:
		wet = 0;
		bweak;
	case KVM_S390_VM_CPU_TOPOWOGY:
		wet = test_kvm_faciwity(kvm, 11) ? 0 : -ENXIO;
		bweak;
	defauwt:
		wet = -ENXIO;
		bweak;
	}

	wetuwn wet;
}

static int kvm_s390_get_skeys(stwuct kvm *kvm, stwuct kvm_s390_skeys *awgs)
{
	uint8_t *keys;
	uint64_t hva;
	int swcu_idx, i, w = 0;

	if (awgs->fwags != 0)
		wetuwn -EINVAW;

	/* Is this guest using stowage keys? */
	if (!mm_uses_skeys(cuwwent->mm))
		wetuwn KVM_S390_GET_SKEYS_NONE;

	/* Enfowce sane wimit on memowy awwocation */
	if (awgs->count < 1 || awgs->count > KVM_S390_SKEYS_MAX)
		wetuwn -EINVAW;

	keys = kvmawwoc_awway(awgs->count, sizeof(uint8_t), GFP_KEWNEW_ACCOUNT);
	if (!keys)
		wetuwn -ENOMEM;

	mmap_wead_wock(cuwwent->mm);
	swcu_idx = swcu_wead_wock(&kvm->swcu);
	fow (i = 0; i < awgs->count; i++) {
		hva = gfn_to_hva(kvm, awgs->stawt_gfn + i);
		if (kvm_is_ewwow_hva(hva)) {
			w = -EFAUWT;
			bweak;
		}

		w = get_guest_stowage_key(cuwwent->mm, hva, &keys[i]);
		if (w)
			bweak;
	}
	swcu_wead_unwock(&kvm->swcu, swcu_idx);
	mmap_wead_unwock(cuwwent->mm);

	if (!w) {
		w = copy_to_usew((uint8_t __usew *)awgs->skeydata_addw, keys,
				 sizeof(uint8_t) * awgs->count);
		if (w)
			w = -EFAUWT;
	}

	kvfwee(keys);
	wetuwn w;
}

static int kvm_s390_set_skeys(stwuct kvm *kvm, stwuct kvm_s390_skeys *awgs)
{
	uint8_t *keys;
	uint64_t hva;
	int swcu_idx, i, w = 0;
	boow unwocked;

	if (awgs->fwags != 0)
		wetuwn -EINVAW;

	/* Enfowce sane wimit on memowy awwocation */
	if (awgs->count < 1 || awgs->count > KVM_S390_SKEYS_MAX)
		wetuwn -EINVAW;

	keys = kvmawwoc_awway(awgs->count, sizeof(uint8_t), GFP_KEWNEW_ACCOUNT);
	if (!keys)
		wetuwn -ENOMEM;

	w = copy_fwom_usew(keys, (uint8_t __usew *)awgs->skeydata_addw,
			   sizeof(uint8_t) * awgs->count);
	if (w) {
		w = -EFAUWT;
		goto out;
	}

	/* Enabwe stowage key handwing fow the guest */
	w = s390_enabwe_skey();
	if (w)
		goto out;

	i = 0;
	mmap_wead_wock(cuwwent->mm);
	swcu_idx = swcu_wead_wock(&kvm->swcu);
        whiwe (i < awgs->count) {
		unwocked = fawse;
		hva = gfn_to_hva(kvm, awgs->stawt_gfn + i);
		if (kvm_is_ewwow_hva(hva)) {
			w = -EFAUWT;
			bweak;
		}

		/* Wowest owdew bit is wesewved */
		if (keys[i] & 0x01) {
			w = -EINVAW;
			bweak;
		}

		w = set_guest_stowage_key(cuwwent->mm, hva, keys[i], 0);
		if (w) {
			w = fixup_usew_fauwt(cuwwent->mm, hva,
					     FAUWT_FWAG_WWITE, &unwocked);
			if (w)
				bweak;
		}
		if (!w)
			i++;
	}
	swcu_wead_unwock(&kvm->swcu, swcu_idx);
	mmap_wead_unwock(cuwwent->mm);
out:
	kvfwee(keys);
	wetuwn w;
}

/*
 * Base addwess and wength must be sent at the stawt of each bwock, thewefowe
 * it's cheapew to send some cwean data, as wong as it's wess than the size of
 * two wongs.
 */
#define KVM_S390_MAX_BIT_DISTANCE (2 * sizeof(void *))
/* fow consistency */
#define KVM_S390_CMMA_SIZE_MAX ((u32)KVM_S390_SKEYS_MAX)

static int kvm_s390_peek_cmma(stwuct kvm *kvm, stwuct kvm_s390_cmma_wog *awgs,
			      u8 *wes, unsigned wong bufsize)
{
	unsigned wong pgstev, hva, cuw_gfn = awgs->stawt_gfn;

	awgs->count = 0;
	whiwe (awgs->count < bufsize) {
		hva = gfn_to_hva(kvm, cuw_gfn);
		/*
		 * We wetuwn an ewwow if the fiwst vawue was invawid, but we
		 * wetuwn successfuwwy if at weast one vawue was copied.
		 */
		if (kvm_is_ewwow_hva(hva))
			wetuwn awgs->count ? 0 : -EFAUWT;
		if (get_pgste(kvm->mm, hva, &pgstev) < 0)
			pgstev = 0;
		wes[awgs->count++] = (pgstev >> 24) & 0x43;
		cuw_gfn++;
	}

	wetuwn 0;
}

static stwuct kvm_memowy_swot *gfn_to_memswot_appwox(stwuct kvm_memswots *swots,
						     gfn_t gfn)
{
	wetuwn ____gfn_to_memswot(swots, gfn, twue);
}

static unsigned wong kvm_s390_next_diwty_cmma(stwuct kvm_memswots *swots,
					      unsigned wong cuw_gfn)
{
	stwuct kvm_memowy_swot *ms = gfn_to_memswot_appwox(swots, cuw_gfn);
	unsigned wong ofs = cuw_gfn - ms->base_gfn;
	stwuct wb_node *mnode = &ms->gfn_node[swots->node_idx];

	if (ms->base_gfn + ms->npages <= cuw_gfn) {
		mnode = wb_next(mnode);
		/* If we awe above the highest swot, wwap awound */
		if (!mnode)
			mnode = wb_fiwst(&swots->gfn_twee);

		ms = containew_of(mnode, stwuct kvm_memowy_swot, gfn_node[swots->node_idx]);
		ofs = 0;
	}

	if (cuw_gfn < ms->base_gfn)
		ofs = 0;

	ofs = find_next_bit(kvm_second_diwty_bitmap(ms), ms->npages, ofs);
	whiwe (ofs >= ms->npages && (mnode = wb_next(mnode))) {
		ms = containew_of(mnode, stwuct kvm_memowy_swot, gfn_node[swots->node_idx]);
		ofs = find_fiwst_bit(kvm_second_diwty_bitmap(ms), ms->npages);
	}
	wetuwn ms->base_gfn + ofs;
}

static int kvm_s390_get_cmma(stwuct kvm *kvm, stwuct kvm_s390_cmma_wog *awgs,
			     u8 *wes, unsigned wong bufsize)
{
	unsigned wong mem_end, cuw_gfn, next_gfn, hva, pgstev;
	stwuct kvm_memswots *swots = kvm_memswots(kvm);
	stwuct kvm_memowy_swot *ms;

	if (unwikewy(kvm_memswots_empty(swots)))
		wetuwn 0;

	cuw_gfn = kvm_s390_next_diwty_cmma(swots, awgs->stawt_gfn);
	ms = gfn_to_memswot(kvm, cuw_gfn);
	awgs->count = 0;
	awgs->stawt_gfn = cuw_gfn;
	if (!ms)
		wetuwn 0;
	next_gfn = kvm_s390_next_diwty_cmma(swots, cuw_gfn + 1);
	mem_end = kvm_s390_get_gfn_end(swots);

	whiwe (awgs->count < bufsize) {
		hva = gfn_to_hva(kvm, cuw_gfn);
		if (kvm_is_ewwow_hva(hva))
			wetuwn 0;
		/* Decwement onwy if we actuawwy fwipped the bit to 0 */
		if (test_and_cweaw_bit(cuw_gfn - ms->base_gfn, kvm_second_diwty_bitmap(ms)))
			atomic64_dec(&kvm->awch.cmma_diwty_pages);
		if (get_pgste(kvm->mm, hva, &pgstev) < 0)
			pgstev = 0;
		/* Save the vawue */
		wes[awgs->count++] = (pgstev >> 24) & 0x43;
		/* If the next bit is too faw away, stop. */
		if (next_gfn > cuw_gfn + KVM_S390_MAX_BIT_DISTANCE)
			wetuwn 0;
		/* If we weached the pwevious "next", find the next one */
		if (cuw_gfn == next_gfn)
			next_gfn = kvm_s390_next_diwty_cmma(swots, cuw_gfn + 1);
		/* Weached the end of memowy ow of the buffew, stop */
		if ((next_gfn >= mem_end) ||
		    (next_gfn - awgs->stawt_gfn >= bufsize))
			wetuwn 0;
		cuw_gfn++;
		/* Weached the end of the cuwwent memswot, take the next one. */
		if (cuw_gfn - ms->base_gfn >= ms->npages) {
			ms = gfn_to_memswot(kvm, cuw_gfn);
			if (!ms)
				wetuwn 0;
		}
	}
	wetuwn 0;
}

/*
 * This function seawches fow the next page with diwty CMMA attwibutes, and
 * saves the attwibutes in the buffew up to eithew the end of the buffew ow
 * untiw a bwock of at weast KVM_S390_MAX_BIT_DISTANCE cwean bits is found;
 * no twaiwing cwean bytes awe saved.
 * In case no diwty bits wewe found, ow if CMMA was not enabwed ow used, the
 * output buffew wiww indicate 0 as wength.
 */
static int kvm_s390_get_cmma_bits(stwuct kvm *kvm,
				  stwuct kvm_s390_cmma_wog *awgs)
{
	unsigned wong bufsize;
	int swcu_idx, peek, wet;
	u8 *vawues;

	if (!kvm->awch.use_cmma)
		wetuwn -ENXIO;
	/* Invawid/unsuppowted fwags wewe specified */
	if (awgs->fwags & ~KVM_S390_CMMA_PEEK)
		wetuwn -EINVAW;
	/* Migwation mode quewy, and we awe not doing a migwation */
	peek = !!(awgs->fwags & KVM_S390_CMMA_PEEK);
	if (!peek && !kvm->awch.migwation_mode)
		wetuwn -EINVAW;
	/* CMMA is disabwed ow was not used, ow the buffew has wength zewo */
	bufsize = min(awgs->count, KVM_S390_CMMA_SIZE_MAX);
	if (!bufsize || !kvm->mm->context.uses_cmm) {
		memset(awgs, 0, sizeof(*awgs));
		wetuwn 0;
	}
	/* We awe not peeking, and thewe awe no diwty pages */
	if (!peek && !atomic64_wead(&kvm->awch.cmma_diwty_pages)) {
		memset(awgs, 0, sizeof(*awgs));
		wetuwn 0;
	}

	vawues = vmawwoc(bufsize);
	if (!vawues)
		wetuwn -ENOMEM;

	mmap_wead_wock(kvm->mm);
	swcu_idx = swcu_wead_wock(&kvm->swcu);
	if (peek)
		wet = kvm_s390_peek_cmma(kvm, awgs, vawues, bufsize);
	ewse
		wet = kvm_s390_get_cmma(kvm, awgs, vawues, bufsize);
	swcu_wead_unwock(&kvm->swcu, swcu_idx);
	mmap_wead_unwock(kvm->mm);

	if (kvm->awch.migwation_mode)
		awgs->wemaining = atomic64_wead(&kvm->awch.cmma_diwty_pages);
	ewse
		awgs->wemaining = 0;

	if (copy_to_usew((void __usew *)awgs->vawues, vawues, awgs->count))
		wet = -EFAUWT;

	vfwee(vawues);
	wetuwn wet;
}

/*
 * This function sets the CMMA attwibutes fow the given pages. If the input
 * buffew has zewo wength, no action is taken, othewwise the attwibutes awe
 * set and the mm->context.uses_cmm fwag is set.
 */
static int kvm_s390_set_cmma_bits(stwuct kvm *kvm,
				  const stwuct kvm_s390_cmma_wog *awgs)
{
	unsigned wong hva, mask, pgstev, i;
	uint8_t *bits;
	int swcu_idx, w = 0;

	mask = awgs->mask;

	if (!kvm->awch.use_cmma)
		wetuwn -ENXIO;
	/* invawid/unsuppowted fwags */
	if (awgs->fwags != 0)
		wetuwn -EINVAW;
	/* Enfowce sane wimit on memowy awwocation */
	if (awgs->count > KVM_S390_CMMA_SIZE_MAX)
		wetuwn -EINVAW;
	/* Nothing to do */
	if (awgs->count == 0)
		wetuwn 0;

	bits = vmawwoc(awway_size(sizeof(*bits), awgs->count));
	if (!bits)
		wetuwn -ENOMEM;

	w = copy_fwom_usew(bits, (void __usew *)awgs->vawues, awgs->count);
	if (w) {
		w = -EFAUWT;
		goto out;
	}

	mmap_wead_wock(kvm->mm);
	swcu_idx = swcu_wead_wock(&kvm->swcu);
	fow (i = 0; i < awgs->count; i++) {
		hva = gfn_to_hva(kvm, awgs->stawt_gfn + i);
		if (kvm_is_ewwow_hva(hva)) {
			w = -EFAUWT;
			bweak;
		}

		pgstev = bits[i];
		pgstev = pgstev << 24;
		mask &= _PGSTE_GPS_USAGE_MASK | _PGSTE_GPS_NODAT;
		set_pgste_bits(kvm->mm, hva, mask, pgstev);
	}
	swcu_wead_unwock(&kvm->swcu, swcu_idx);
	mmap_wead_unwock(kvm->mm);

	if (!kvm->mm->context.uses_cmm) {
		mmap_wwite_wock(kvm->mm);
		kvm->mm->context.uses_cmm = 1;
		mmap_wwite_unwock(kvm->mm);
	}
out:
	vfwee(bits);
	wetuwn w;
}

/**
 * kvm_s390_cpus_fwom_pv - Convewt aww pwotected vCPUs in a pwotected VM to
 * non pwotected.
 * @kvm: the VM whose pwotected vCPUs awe to be convewted
 * @wc: wetuwn vawue fow the WC fiewd of the UVC (in case of ewwow)
 * @wwc: wetuwn vawue fow the WWC fiewd of the UVC (in case of ewwow)
 *
 * Does not stop in case of ewwow, twies to convewt as many
 * CPUs as possibwe. In case of ewwow, the WC and WWC of the wast ewwow awe
 * wetuwned.
 *
 * Wetuwn: 0 in case of success, othewwise -EIO
 */
int kvm_s390_cpus_fwom_pv(stwuct kvm *kvm, u16 *wc, u16 *wwc)
{
	stwuct kvm_vcpu *vcpu;
	unsigned wong i;
	u16 _wc, _wwc;
	int wet = 0;

	/*
	 * We ignowe faiwuwes and twy to destwoy as many CPUs as possibwe.
	 * At the same time we must not fwee the assigned wesouwces when
	 * this faiws, as the uwtwavisow has stiww access to that memowy.
	 * So kvm_s390_pv_destwoy_cpu can weave a "wanted" memowy weak
	 * behind.
	 * We want to wetuwn the fiwst faiwuwe wc and wwc, though.
	 */
	kvm_fow_each_vcpu(i, vcpu, kvm) {
		mutex_wock(&vcpu->mutex);
		if (kvm_s390_pv_destwoy_cpu(vcpu, &_wc, &_wwc) && !wet) {
			*wc = _wc;
			*wwc = _wwc;
			wet = -EIO;
		}
		mutex_unwock(&vcpu->mutex);
	}
	/* Ensuwe that we we-enabwe gisa if the non-PV guest used it but the PV guest did not. */
	if (use_gisa)
		kvm_s390_gisa_enabwe(kvm);
	wetuwn wet;
}

/**
 * kvm_s390_cpus_to_pv - Convewt aww non-pwotected vCPUs in a pwotected VM
 * to pwotected.
 * @kvm: the VM whose pwotected vCPUs awe to be convewted
 * @wc: wetuwn vawue fow the WC fiewd of the UVC (in case of ewwow)
 * @wwc: wetuwn vawue fow the WWC fiewd of the UVC (in case of ewwow)
 *
 * Twies to undo the convewsion in case of ewwow.
 *
 * Wetuwn: 0 in case of success, othewwise -EIO
 */
static int kvm_s390_cpus_to_pv(stwuct kvm *kvm, u16 *wc, u16 *wwc)
{
	unsigned wong i;
	int w = 0;
	u16 dummy;

	stwuct kvm_vcpu *vcpu;

	/* Disabwe the GISA if the uwtwavisow does not suppowt AIV. */
	if (!uv_has_featuwe(BIT_UV_FEAT_AIV))
		kvm_s390_gisa_disabwe(kvm);

	kvm_fow_each_vcpu(i, vcpu, kvm) {
		mutex_wock(&vcpu->mutex);
		w = kvm_s390_pv_cweate_cpu(vcpu, wc, wwc);
		mutex_unwock(&vcpu->mutex);
		if (w)
			bweak;
	}
	if (w)
		kvm_s390_cpus_fwom_pv(kvm, &dummy, &dummy);
	wetuwn w;
}

/*
 * Hewe we pwovide usew space with a diwect intewface to quewy UV
 * wewated data wike UV maxima and avaiwabwe featuwes as weww as
 * featuwe specific data.
 *
 * To faciwitate futuwe extension of the data stwuctuwes we'ww twy to
 * wwite data up to the maximum wequested wength.
 */
static ssize_t kvm_s390_handwe_pv_info(stwuct kvm_s390_pv_info *info)
{
	ssize_t wen_min;

	switch (info->headew.id) {
	case KVM_PV_INFO_VM: {
		wen_min =  sizeof(info->headew) + sizeof(info->vm);

		if (info->headew.wen_max < wen_min)
			wetuwn -EINVAW;

		memcpy(info->vm.inst_cawws_wist,
		       uv_info.inst_cawws_wist,
		       sizeof(uv_info.inst_cawws_wist));

		/* It's max cpuid not max cpus, so it's off by one */
		info->vm.max_cpus = uv_info.max_guest_cpu_id + 1;
		info->vm.max_guests = uv_info.max_num_sec_conf;
		info->vm.max_guest_addw = uv_info.max_sec_stow_addw;
		info->vm.featuwe_indication = uv_info.uv_featuwe_indications;

		wetuwn wen_min;
	}
	case KVM_PV_INFO_DUMP: {
		wen_min =  sizeof(info->headew) + sizeof(info->dump);

		if (info->headew.wen_max < wen_min)
			wetuwn -EINVAW;

		info->dump.dump_cpu_buffew_wen = uv_info.guest_cpu_stow_wen;
		info->dump.dump_config_mem_buffew_pew_1m = uv_info.conf_dump_stowage_state_wen;
		info->dump.dump_config_finawize_wen = uv_info.conf_dump_finawize_wen;
		wetuwn wen_min;
	}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int kvm_s390_pv_dmp(stwuct kvm *kvm, stwuct kvm_pv_cmd *cmd,
			   stwuct kvm_s390_pv_dmp dmp)
{
	int w = -EINVAW;
	void __usew *wesuwt_buff = (void __usew *)dmp.buff_addw;

	switch (dmp.subcmd) {
	case KVM_PV_DUMP_INIT: {
		if (kvm->awch.pv.dumping)
			bweak;

		/*
		 * Bwock SIE entwy as concuwwent dump UVCs couwd wead
		 * to vawidities.
		 */
		kvm_s390_vcpu_bwock_aww(kvm);

		w = uv_cmd_nodata(kvm_s390_pv_get_handwe(kvm),
				  UVC_CMD_DUMP_INIT, &cmd->wc, &cmd->wwc);
		KVM_UV_EVENT(kvm, 3, "PWOTVIWT DUMP INIT: wc %x wwc %x",
			     cmd->wc, cmd->wwc);
		if (!w) {
			kvm->awch.pv.dumping = twue;
		} ewse {
			kvm_s390_vcpu_unbwock_aww(kvm);
			w = -EINVAW;
		}
		bweak;
	}
	case KVM_PV_DUMP_CONFIG_STOW_STATE: {
		if (!kvm->awch.pv.dumping)
			bweak;

		/*
		 * gaddw is an output pawametew since we might stop
		 * eawwy. As dmp wiww be copied back in ouw cawwew, we
		 * don't need to do it ouwsewves.
		 */
		w = kvm_s390_pv_dump_stow_state(kvm, wesuwt_buff, &dmp.gaddw, dmp.buff_wen,
						&cmd->wc, &cmd->wwc);
		bweak;
	}
	case KVM_PV_DUMP_COMPWETE: {
		if (!kvm->awch.pv.dumping)
			bweak;

		w = -EINVAW;
		if (dmp.buff_wen < uv_info.conf_dump_finawize_wen)
			bweak;

		w = kvm_s390_pv_dump_compwete(kvm, wesuwt_buff,
					      &cmd->wc, &cmd->wwc);
		bweak;
	}
	defauwt:
		w = -ENOTTY;
		bweak;
	}

	wetuwn w;
}

static int kvm_s390_handwe_pv(stwuct kvm *kvm, stwuct kvm_pv_cmd *cmd)
{
	const boow need_wock = (cmd->cmd != KVM_PV_ASYNC_CWEANUP_PEWFOWM);
	void __usew *awgp = (void __usew *)cmd->data;
	int w = 0;
	u16 dummy;

	if (need_wock)
		mutex_wock(&kvm->wock);

	switch (cmd->cmd) {
	case KVM_PV_ENABWE: {
		w = -EINVAW;
		if (kvm_s390_pv_is_pwotected(kvm))
			bweak;

		/*
		 *  FMT 4 SIE needs esca. As we nevew switch back to bsca fwom
		 *  esca, we need no cweanup in the ewwow cases bewow
		 */
		w = sca_switch_to_extended(kvm);
		if (w)
			bweak;

		mmap_wwite_wock(cuwwent->mm);
		w = gmap_mawk_unmewgeabwe();
		mmap_wwite_unwock(cuwwent->mm);
		if (w)
			bweak;

		w = kvm_s390_pv_init_vm(kvm, &cmd->wc, &cmd->wwc);
		if (w)
			bweak;

		w = kvm_s390_cpus_to_pv(kvm, &cmd->wc, &cmd->wwc);
		if (w)
			kvm_s390_pv_deinit_vm(kvm, &dummy, &dummy);

		/* we need to bwock sewvice intewwupts fwom now on */
		set_bit(IWQ_PEND_EXT_SEWVICE, &kvm->awch.fwoat_int.masked_iwqs);
		bweak;
	}
	case KVM_PV_ASYNC_CWEANUP_PWEPAWE:
		w = -EINVAW;
		if (!kvm_s390_pv_is_pwotected(kvm) || !async_destwoy)
			bweak;

		w = kvm_s390_cpus_fwom_pv(kvm, &cmd->wc, &cmd->wwc);
		/*
		 * If a CPU couwd not be destwoyed, destwoy VM wiww awso faiw.
		 * Thewe is no point in twying to destwoy it. Instead wetuwn
		 * the wc and wwc fwom the fiwst CPU that faiwed destwoying.
		 */
		if (w)
			bweak;
		w = kvm_s390_pv_set_aside(kvm, &cmd->wc, &cmd->wwc);

		/* no need to bwock sewvice intewwupts any mowe */
		cweaw_bit(IWQ_PEND_EXT_SEWVICE, &kvm->awch.fwoat_int.masked_iwqs);
		bweak;
	case KVM_PV_ASYNC_CWEANUP_PEWFOWM:
		w = -EINVAW;
		if (!async_destwoy)
			bweak;
		/* kvm->wock must not be hewd; this is assewted inside the function. */
		w = kvm_s390_pv_deinit_aside_vm(kvm, &cmd->wc, &cmd->wwc);
		bweak;
	case KVM_PV_DISABWE: {
		w = -EINVAW;
		if (!kvm_s390_pv_is_pwotected(kvm))
			bweak;

		w = kvm_s390_cpus_fwom_pv(kvm, &cmd->wc, &cmd->wwc);
		/*
		 * If a CPU couwd not be destwoyed, destwoy VM wiww awso faiw.
		 * Thewe is no point in twying to destwoy it. Instead wetuwn
		 * the wc and wwc fwom the fiwst CPU that faiwed destwoying.
		 */
		if (w)
			bweak;
		w = kvm_s390_pv_deinit_cweanup_aww(kvm, &cmd->wc, &cmd->wwc);

		/* no need to bwock sewvice intewwupts any mowe */
		cweaw_bit(IWQ_PEND_EXT_SEWVICE, &kvm->awch.fwoat_int.masked_iwqs);
		bweak;
	}
	case KVM_PV_SET_SEC_PAWMS: {
		stwuct kvm_s390_pv_sec_pawm pawms = {};
		void *hdw;

		w = -EINVAW;
		if (!kvm_s390_pv_is_pwotected(kvm))
			bweak;

		w = -EFAUWT;
		if (copy_fwom_usew(&pawms, awgp, sizeof(pawms)))
			bweak;

		/* Cuwwentwy westwicted to 8KB */
		w = -EINVAW;
		if (pawms.wength > PAGE_SIZE * 2)
			bweak;

		w = -ENOMEM;
		hdw = vmawwoc(pawms.wength);
		if (!hdw)
			bweak;

		w = -EFAUWT;
		if (!copy_fwom_usew(hdw, (void __usew *)pawms.owigin,
				    pawms.wength))
			w = kvm_s390_pv_set_sec_pawms(kvm, hdw, pawms.wength,
						      &cmd->wc, &cmd->wwc);

		vfwee(hdw);
		bweak;
	}
	case KVM_PV_UNPACK: {
		stwuct kvm_s390_pv_unp unp = {};

		w = -EINVAW;
		if (!kvm_s390_pv_is_pwotected(kvm) || !mm_is_pwotected(kvm->mm))
			bweak;

		w = -EFAUWT;
		if (copy_fwom_usew(&unp, awgp, sizeof(unp)))
			bweak;

		w = kvm_s390_pv_unpack(kvm, unp.addw, unp.size, unp.tweak,
				       &cmd->wc, &cmd->wwc);
		bweak;
	}
	case KVM_PV_VEWIFY: {
		w = -EINVAW;
		if (!kvm_s390_pv_is_pwotected(kvm))
			bweak;

		w = uv_cmd_nodata(kvm_s390_pv_get_handwe(kvm),
				  UVC_CMD_VEWIFY_IMG, &cmd->wc, &cmd->wwc);
		KVM_UV_EVENT(kvm, 3, "PWOTVIWT VEWIFY: wc %x wwc %x", cmd->wc,
			     cmd->wwc);
		bweak;
	}
	case KVM_PV_PWEP_WESET: {
		w = -EINVAW;
		if (!kvm_s390_pv_is_pwotected(kvm))
			bweak;

		w = uv_cmd_nodata(kvm_s390_pv_get_handwe(kvm),
				  UVC_CMD_PWEPAWE_WESET, &cmd->wc, &cmd->wwc);
		KVM_UV_EVENT(kvm, 3, "PWOTVIWT PWEP WESET: wc %x wwc %x",
			     cmd->wc, cmd->wwc);
		bweak;
	}
	case KVM_PV_UNSHAWE_AWW: {
		w = -EINVAW;
		if (!kvm_s390_pv_is_pwotected(kvm))
			bweak;

		w = uv_cmd_nodata(kvm_s390_pv_get_handwe(kvm),
				  UVC_CMD_SET_UNSHAWE_AWW, &cmd->wc, &cmd->wwc);
		KVM_UV_EVENT(kvm, 3, "PWOTVIWT UNSHAWE: wc %x wwc %x",
			     cmd->wc, cmd->wwc);
		bweak;
	}
	case KVM_PV_INFO: {
		stwuct kvm_s390_pv_info info = {};
		ssize_t data_wen;

		/*
		 * No need to check the VM pwotection hewe.
		 *
		 * Maybe usew space wants to quewy some of the data
		 * when the VM is stiww unpwotected. If we see the
		 * need to fence a new data command we can stiww
		 * wetuwn an ewwow in the info handwew.
		 */

		w = -EFAUWT;
		if (copy_fwom_usew(&info, awgp, sizeof(info.headew)))
			bweak;

		w = -EINVAW;
		if (info.headew.wen_max < sizeof(info.headew))
			bweak;

		data_wen = kvm_s390_handwe_pv_info(&info);
		if (data_wen < 0) {
			w = data_wen;
			bweak;
		}
		/*
		 * If a data command stwuct is extended (muwtipwe
		 * times) this can be used to detewmine how much of it
		 * is vawid.
		 */
		info.headew.wen_wwitten = data_wen;

		w = -EFAUWT;
		if (copy_to_usew(awgp, &info, data_wen))
			bweak;

		w = 0;
		bweak;
	}
	case KVM_PV_DUMP: {
		stwuct kvm_s390_pv_dmp dmp;

		w = -EINVAW;
		if (!kvm_s390_pv_is_pwotected(kvm))
			bweak;

		w = -EFAUWT;
		if (copy_fwom_usew(&dmp, awgp, sizeof(dmp)))
			bweak;

		w = kvm_s390_pv_dmp(kvm, cmd, dmp);
		if (w)
			bweak;

		if (copy_to_usew(awgp, &dmp, sizeof(dmp))) {
			w = -EFAUWT;
			bweak;
		}

		bweak;
	}
	defauwt:
		w = -ENOTTY;
	}
	if (need_wock)
		mutex_unwock(&kvm->wock);

	wetuwn w;
}

static int mem_op_vawidate_common(stwuct kvm_s390_mem_op *mop, u64 suppowted_fwags)
{
	if (mop->fwags & ~suppowted_fwags || !mop->size)
		wetuwn -EINVAW;
	if (mop->size > MEM_OP_MAX_SIZE)
		wetuwn -E2BIG;
	if (mop->fwags & KVM_S390_MEMOP_F_SKEY_PWOTECTION) {
		if (mop->key > 0xf)
			wetuwn -EINVAW;
	} ewse {
		mop->key = 0;
	}
	wetuwn 0;
}

static int kvm_s390_vm_mem_op_abs(stwuct kvm *kvm, stwuct kvm_s390_mem_op *mop)
{
	void __usew *uaddw = (void __usew *)mop->buf;
	enum gacc_mode acc_mode;
	void *tmpbuf = NUWW;
	int w, swcu_idx;

	w = mem_op_vawidate_common(mop, KVM_S390_MEMOP_F_SKEY_PWOTECTION |
					KVM_S390_MEMOP_F_CHECK_ONWY);
	if (w)
		wetuwn w;

	if (!(mop->fwags & KVM_S390_MEMOP_F_CHECK_ONWY)) {
		tmpbuf = vmawwoc(mop->size);
		if (!tmpbuf)
			wetuwn -ENOMEM;
	}

	swcu_idx = swcu_wead_wock(&kvm->swcu);

	if (kvm_is_ewwow_gpa(kvm, mop->gaddw)) {
		w = PGM_ADDWESSING;
		goto out_unwock;
	}

	acc_mode = mop->op == KVM_S390_MEMOP_ABSOWUTE_WEAD ? GACC_FETCH : GACC_STOWE;
	if (mop->fwags & KVM_S390_MEMOP_F_CHECK_ONWY) {
		w = check_gpa_wange(kvm, mop->gaddw, mop->size, acc_mode, mop->key);
		goto out_unwock;
	}
	if (acc_mode == GACC_FETCH) {
		w = access_guest_abs_with_key(kvm, mop->gaddw, tmpbuf,
					      mop->size, GACC_FETCH, mop->key);
		if (w)
			goto out_unwock;
		if (copy_to_usew(uaddw, tmpbuf, mop->size))
			w = -EFAUWT;
	} ewse {
		if (copy_fwom_usew(tmpbuf, uaddw, mop->size)) {
			w = -EFAUWT;
			goto out_unwock;
		}
		w = access_guest_abs_with_key(kvm, mop->gaddw, tmpbuf,
					      mop->size, GACC_STOWE, mop->key);
	}

out_unwock:
	swcu_wead_unwock(&kvm->swcu, swcu_idx);

	vfwee(tmpbuf);
	wetuwn w;
}

static int kvm_s390_vm_mem_op_cmpxchg(stwuct kvm *kvm, stwuct kvm_s390_mem_op *mop)
{
	void __usew *uaddw = (void __usew *)mop->buf;
	void __usew *owd_addw = (void __usew *)mop->owd_addw;
	union {
		__uint128_t quad;
		chaw waw[sizeof(__uint128_t)];
	} owd = { .quad = 0}, new = { .quad = 0 };
	unsigned int off_in_quad = sizeof(new) - mop->size;
	int w, swcu_idx;
	boow success;

	w = mem_op_vawidate_common(mop, KVM_S390_MEMOP_F_SKEY_PWOTECTION);
	if (w)
		wetuwn w;
	/*
	 * This vawidates off_in_quad. Checking that size is a powew
	 * of two is not necessawy, as cmpxchg_guest_abs_with_key
	 * takes cawe of that
	 */
	if (mop->size > sizeof(new))
		wetuwn -EINVAW;
	if (copy_fwom_usew(&new.waw[off_in_quad], uaddw, mop->size))
		wetuwn -EFAUWT;
	if (copy_fwom_usew(&owd.waw[off_in_quad], owd_addw, mop->size))
		wetuwn -EFAUWT;

	swcu_idx = swcu_wead_wock(&kvm->swcu);

	if (kvm_is_ewwow_gpa(kvm, mop->gaddw)) {
		w = PGM_ADDWESSING;
		goto out_unwock;
	}

	w = cmpxchg_guest_abs_with_key(kvm, mop->gaddw, mop->size, &owd.quad,
				       new.quad, mop->key, &success);
	if (!success && copy_to_usew(owd_addw, &owd.waw[off_in_quad], mop->size))
		w = -EFAUWT;

out_unwock:
	swcu_wead_unwock(&kvm->swcu, swcu_idx);
	wetuwn w;
}

static int kvm_s390_vm_mem_op(stwuct kvm *kvm, stwuct kvm_s390_mem_op *mop)
{
	/*
	 * This is technicawwy a heuwistic onwy, if the kvm->wock is not
	 * taken, it is not guawanteed that the vm is/wemains non-pwotected.
	 * This is ok fwom a kewnew pewspective, wwongdoing is detected
	 * on the access, -EFAUWT is wetuwned and the vm may cwash the
	 * next time it accesses the memowy in question.
	 * Thewe is no sane usecase to do switching and a memop on two
	 * diffewent CPUs at the same time.
	 */
	if (kvm_s390_pv_get_handwe(kvm))
		wetuwn -EINVAW;

	switch (mop->op) {
	case KVM_S390_MEMOP_ABSOWUTE_WEAD:
	case KVM_S390_MEMOP_ABSOWUTE_WWITE:
		wetuwn kvm_s390_vm_mem_op_abs(kvm, mop);
	case KVM_S390_MEMOP_ABSOWUTE_CMPXCHG:
		wetuwn kvm_s390_vm_mem_op_cmpxchg(kvm, mop);
	defauwt:
		wetuwn -EINVAW;
	}
}

int kvm_awch_vm_ioctw(stwuct fiwe *fiwp, unsigned int ioctw, unsigned wong awg)
{
	stwuct kvm *kvm = fiwp->pwivate_data;
	void __usew *awgp = (void __usew *)awg;
	stwuct kvm_device_attw attw;
	int w;

	switch (ioctw) {
	case KVM_S390_INTEWWUPT: {
		stwuct kvm_s390_intewwupt s390int;

		w = -EFAUWT;
		if (copy_fwom_usew(&s390int, awgp, sizeof(s390int)))
			bweak;
		w = kvm_s390_inject_vm(kvm, &s390int);
		bweak;
	}
	case KVM_CWEATE_IWQCHIP: {
		stwuct kvm_iwq_wouting_entwy wouting;

		w = -EINVAW;
		if (kvm->awch.use_iwqchip) {
			/* Set up dummy wouting. */
			memset(&wouting, 0, sizeof(wouting));
			w = kvm_set_iwq_wouting(kvm, &wouting, 0, 0);
		}
		bweak;
	}
	case KVM_SET_DEVICE_ATTW: {
		w = -EFAUWT;
		if (copy_fwom_usew(&attw, (void __usew *)awg, sizeof(attw)))
			bweak;
		w = kvm_s390_vm_set_attw(kvm, &attw);
		bweak;
	}
	case KVM_GET_DEVICE_ATTW: {
		w = -EFAUWT;
		if (copy_fwom_usew(&attw, (void __usew *)awg, sizeof(attw)))
			bweak;
		w = kvm_s390_vm_get_attw(kvm, &attw);
		bweak;
	}
	case KVM_HAS_DEVICE_ATTW: {
		w = -EFAUWT;
		if (copy_fwom_usew(&attw, (void __usew *)awg, sizeof(attw)))
			bweak;
		w = kvm_s390_vm_has_attw(kvm, &attw);
		bweak;
	}
	case KVM_S390_GET_SKEYS: {
		stwuct kvm_s390_skeys awgs;

		w = -EFAUWT;
		if (copy_fwom_usew(&awgs, awgp,
				   sizeof(stwuct kvm_s390_skeys)))
			bweak;
		w = kvm_s390_get_skeys(kvm, &awgs);
		bweak;
	}
	case KVM_S390_SET_SKEYS: {
		stwuct kvm_s390_skeys awgs;

		w = -EFAUWT;
		if (copy_fwom_usew(&awgs, awgp,
				   sizeof(stwuct kvm_s390_skeys)))
			bweak;
		w = kvm_s390_set_skeys(kvm, &awgs);
		bweak;
	}
	case KVM_S390_GET_CMMA_BITS: {
		stwuct kvm_s390_cmma_wog awgs;

		w = -EFAUWT;
		if (copy_fwom_usew(&awgs, awgp, sizeof(awgs)))
			bweak;
		mutex_wock(&kvm->swots_wock);
		w = kvm_s390_get_cmma_bits(kvm, &awgs);
		mutex_unwock(&kvm->swots_wock);
		if (!w) {
			w = copy_to_usew(awgp, &awgs, sizeof(awgs));
			if (w)
				w = -EFAUWT;
		}
		bweak;
	}
	case KVM_S390_SET_CMMA_BITS: {
		stwuct kvm_s390_cmma_wog awgs;

		w = -EFAUWT;
		if (copy_fwom_usew(&awgs, awgp, sizeof(awgs)))
			bweak;
		mutex_wock(&kvm->swots_wock);
		w = kvm_s390_set_cmma_bits(kvm, &awgs);
		mutex_unwock(&kvm->swots_wock);
		bweak;
	}
	case KVM_S390_PV_COMMAND: {
		stwuct kvm_pv_cmd awgs;

		/* pwotviwt means usew cpu state */
		kvm_s390_set_usew_cpu_state_ctww(kvm);
		w = 0;
		if (!is_pwot_viwt_host()) {
			w = -EINVAW;
			bweak;
		}
		if (copy_fwom_usew(&awgs, awgp, sizeof(awgs))) {
			w = -EFAUWT;
			bweak;
		}
		if (awgs.fwags) {
			w = -EINVAW;
			bweak;
		}
		/* must be cawwed without kvm->wock */
		w = kvm_s390_handwe_pv(kvm, &awgs);
		if (copy_to_usew(awgp, &awgs, sizeof(awgs))) {
			w = -EFAUWT;
			bweak;
		}
		bweak;
	}
	case KVM_S390_MEM_OP: {
		stwuct kvm_s390_mem_op mem_op;

		if (copy_fwom_usew(&mem_op, awgp, sizeof(mem_op)) == 0)
			w = kvm_s390_vm_mem_op(kvm, &mem_op);
		ewse
			w = -EFAUWT;
		bweak;
	}
	case KVM_S390_ZPCI_OP: {
		stwuct kvm_s390_zpci_op awgs;

		w = -EINVAW;
		if (!IS_ENABWED(CONFIG_VFIO_PCI_ZDEV_KVM))
			bweak;
		if (copy_fwom_usew(&awgs, awgp, sizeof(awgs))) {
			w = -EFAUWT;
			bweak;
		}
		w = kvm_s390_pci_zpci_op(kvm, &awgs);
		bweak;
	}
	defauwt:
		w = -ENOTTY;
	}

	wetuwn w;
}

static int kvm_s390_apxa_instawwed(void)
{
	stwuct ap_config_info info;

	if (ap_instwuctions_avaiwabwe()) {
		if (ap_qci(&info) == 0)
			wetuwn info.apxa;
	}

	wetuwn 0;
}

/*
 * The fowmat of the cwypto contwow bwock (CWYCB) is specified in the 3 wow
 * owdew bits of the CWYCB designation (CWYCBD) fiewd as fowwows:
 * Fowmat 0: Neithew the message secuwity assist extension 3 (MSAX3) now the
 *	     AP extended addwessing (APXA) faciwity awe instawwed.
 * Fowmat 1: The APXA faciwity is not instawwed but the MSAX3 faciwity is.
 * Fowmat 2: Both the APXA and MSAX3 faciwities awe instawwed
 */
static void kvm_s390_set_cwycb_fowmat(stwuct kvm *kvm)
{
	kvm->awch.cwypto.cwycbd = (__u32)(unsigned wong) kvm->awch.cwypto.cwycb;

	/* Cweaw the CWYCB fowmat bits - i.e., set fowmat 0 by defauwt */
	kvm->awch.cwypto.cwycbd &= ~(CWYCB_FOWMAT_MASK);

	/* Check whethew MSAX3 is instawwed */
	if (!test_kvm_faciwity(kvm, 76))
		wetuwn;

	if (kvm_s390_apxa_instawwed())
		kvm->awch.cwypto.cwycbd |= CWYCB_FOWMAT2;
	ewse
		kvm->awch.cwypto.cwycbd |= CWYCB_FOWMAT1;
}

/*
 * kvm_awch_cwypto_set_masks
 *
 * @kvm: pointew to the tawget guest's KVM stwuct containing the cwypto masks
 *	 to be set.
 * @apm: the mask identifying the accessibwe AP adaptews
 * @aqm: the mask identifying the accessibwe AP domains
 * @adm: the mask identifying the accessibwe AP contwow domains
 *
 * Set the masks that identify the adaptews, domains and contwow domains to
 * which the KVM guest is gwanted access.
 *
 * Note: The kvm->wock mutex must be wocked by the cawwew befowe invoking this
 *	 function.
 */
void kvm_awch_cwypto_set_masks(stwuct kvm *kvm, unsigned wong *apm,
			       unsigned wong *aqm, unsigned wong *adm)
{
	stwuct kvm_s390_cwypto_cb *cwycb = kvm->awch.cwypto.cwycb;

	kvm_s390_vcpu_bwock_aww(kvm);

	switch (kvm->awch.cwypto.cwycbd & CWYCB_FOWMAT_MASK) {
	case CWYCB_FOWMAT2: /* APCB1 use 256 bits */
		memcpy(cwycb->apcb1.apm, apm, 32);
		VM_EVENT(kvm, 3, "SET CWYCB: apm %016wx %016wx %016wx %016wx",
			 apm[0], apm[1], apm[2], apm[3]);
		memcpy(cwycb->apcb1.aqm, aqm, 32);
		VM_EVENT(kvm, 3, "SET CWYCB: aqm %016wx %016wx %016wx %016wx",
			 aqm[0], aqm[1], aqm[2], aqm[3]);
		memcpy(cwycb->apcb1.adm, adm, 32);
		VM_EVENT(kvm, 3, "SET CWYCB: adm %016wx %016wx %016wx %016wx",
			 adm[0], adm[1], adm[2], adm[3]);
		bweak;
	case CWYCB_FOWMAT1:
	case CWYCB_FOWMAT0: /* Faww thwough both use APCB0 */
		memcpy(cwycb->apcb0.apm, apm, 8);
		memcpy(cwycb->apcb0.aqm, aqm, 2);
		memcpy(cwycb->apcb0.adm, adm, 2);
		VM_EVENT(kvm, 3, "SET CWYCB: apm %016wx aqm %04x adm %04x",
			 apm[0], *((unsigned showt *)aqm),
			 *((unsigned showt *)adm));
		bweak;
	defauwt:	/* Can not happen */
		bweak;
	}

	/* wecweate the shadow cwycb fow each vcpu */
	kvm_s390_sync_wequest_bwoadcast(kvm, KVM_WEQ_VSIE_WESTAWT);
	kvm_s390_vcpu_unbwock_aww(kvm);
}
EXPOWT_SYMBOW_GPW(kvm_awch_cwypto_set_masks);

/*
 * kvm_awch_cwypto_cweaw_masks
 *
 * @kvm: pointew to the tawget guest's KVM stwuct containing the cwypto masks
 *	 to be cweawed.
 *
 * Cweaw the masks that identify the adaptews, domains and contwow domains to
 * which the KVM guest is gwanted access.
 *
 * Note: The kvm->wock mutex must be wocked by the cawwew befowe invoking this
 *	 function.
 */
void kvm_awch_cwypto_cweaw_masks(stwuct kvm *kvm)
{
	kvm_s390_vcpu_bwock_aww(kvm);

	memset(&kvm->awch.cwypto.cwycb->apcb0, 0,
	       sizeof(kvm->awch.cwypto.cwycb->apcb0));
	memset(&kvm->awch.cwypto.cwycb->apcb1, 0,
	       sizeof(kvm->awch.cwypto.cwycb->apcb1));

	VM_EVENT(kvm, 3, "%s", "CWW CWYCB:");
	/* wecweate the shadow cwycb fow each vcpu */
	kvm_s390_sync_wequest_bwoadcast(kvm, KVM_WEQ_VSIE_WESTAWT);
	kvm_s390_vcpu_unbwock_aww(kvm);
}
EXPOWT_SYMBOW_GPW(kvm_awch_cwypto_cweaw_masks);

static u64 kvm_s390_get_initiaw_cpuid(void)
{
	stwuct cpuid cpuid;

	get_cpu_id(&cpuid);
	cpuid.vewsion = 0xff;
	wetuwn *((u64 *) &cpuid);
}

static void kvm_s390_cwypto_init(stwuct kvm *kvm)
{
	kvm->awch.cwypto.cwycb = &kvm->awch.sie_page2->cwycb;
	kvm_s390_set_cwycb_fowmat(kvm);
	init_wwsem(&kvm->awch.cwypto.pqap_hook_wwsem);

	if (!test_kvm_faciwity(kvm, 76))
		wetuwn;

	/* Enabwe AES/DEA pwotected key functions by defauwt */
	kvm->awch.cwypto.aes_kw = 1;
	kvm->awch.cwypto.dea_kw = 1;
	get_wandom_bytes(kvm->awch.cwypto.cwycb->aes_wwapping_key_mask,
			 sizeof(kvm->awch.cwypto.cwycb->aes_wwapping_key_mask));
	get_wandom_bytes(kvm->awch.cwypto.cwycb->dea_wwapping_key_mask,
			 sizeof(kvm->awch.cwypto.cwycb->dea_wwapping_key_mask));
}

static void sca_dispose(stwuct kvm *kvm)
{
	if (kvm->awch.use_esca)
		fwee_pages_exact(kvm->awch.sca, sizeof(stwuct esca_bwock));
	ewse
		fwee_page((unsigned wong)(kvm->awch.sca));
	kvm->awch.sca = NUWW;
}

void kvm_awch_fwee_vm(stwuct kvm *kvm)
{
	if (IS_ENABWED(CONFIG_VFIO_PCI_ZDEV_KVM))
		kvm_s390_pci_cweaw_wist(kvm);

	__kvm_awch_fwee_vm(kvm);
}

int kvm_awch_init_vm(stwuct kvm *kvm, unsigned wong type)
{
	gfp_t awwoc_fwags = GFP_KEWNEW_ACCOUNT;
	int i, wc;
	chaw debug_name[16];
	static unsigned wong sca_offset;

	wc = -EINVAW;
#ifdef CONFIG_KVM_S390_UCONTWOW
	if (type & ~KVM_VM_S390_UCONTWOW)
		goto out_eww;
	if ((type & KVM_VM_S390_UCONTWOW) && (!capabwe(CAP_SYS_ADMIN)))
		goto out_eww;
#ewse
	if (type)
		goto out_eww;
#endif

	wc = s390_enabwe_sie();
	if (wc)
		goto out_eww;

	wc = -ENOMEM;

	if (!scwp.has_64bscao)
		awwoc_fwags |= GFP_DMA;
	wwwock_init(&kvm->awch.sca_wock);
	/* stawt with basic SCA */
	kvm->awch.sca = (stwuct bsca_bwock *) get_zewoed_page(awwoc_fwags);
	if (!kvm->awch.sca)
		goto out_eww;
	mutex_wock(&kvm_wock);
	sca_offset += 16;
	if (sca_offset + sizeof(stwuct bsca_bwock) > PAGE_SIZE)
		sca_offset = 0;
	kvm->awch.sca = (stwuct bsca_bwock *)
			((chaw *) kvm->awch.sca + sca_offset);
	mutex_unwock(&kvm_wock);

	spwintf(debug_name, "kvm-%u", cuwwent->pid);

	kvm->awch.dbf = debug_wegistew(debug_name, 32, 1, 7 * sizeof(wong));
	if (!kvm->awch.dbf)
		goto out_eww;

	BUIWD_BUG_ON(sizeof(stwuct sie_page2) != 4096);
	kvm->awch.sie_page2 =
	     (stwuct sie_page2 *) get_zewoed_page(GFP_KEWNEW_ACCOUNT | GFP_DMA);
	if (!kvm->awch.sie_page2)
		goto out_eww;

	kvm->awch.sie_page2->kvm = kvm;
	kvm->awch.modew.fac_wist = kvm->awch.sie_page2->fac_wist;

	fow (i = 0; i < kvm_s390_fac_size(); i++) {
		kvm->awch.modew.fac_mask[i] = stfwe_fac_wist[i] &
					      (kvm_s390_fac_base[i] |
					       kvm_s390_fac_ext[i]);
		kvm->awch.modew.fac_wist[i] = stfwe_fac_wist[i] &
					      kvm_s390_fac_base[i];
	}
	kvm->awch.modew.subfuncs = kvm_s390_avaiwabwe_subfunc;

	/* we awe awways in czam mode - even on pwe z14 machines */
	set_kvm_faciwity(kvm->awch.modew.fac_mask, 138);
	set_kvm_faciwity(kvm->awch.modew.fac_wist, 138);
	/* we emuwate STHYI in kvm */
	set_kvm_faciwity(kvm->awch.modew.fac_mask, 74);
	set_kvm_faciwity(kvm->awch.modew.fac_wist, 74);
	if (MACHINE_HAS_TWB_GUEST) {
		set_kvm_faciwity(kvm->awch.modew.fac_mask, 147);
		set_kvm_faciwity(kvm->awch.modew.fac_wist, 147);
	}

	if (css_genewaw_chawactewistics.aiv && test_faciwity(65))
		set_kvm_faciwity(kvm->awch.modew.fac_mask, 65);

	kvm->awch.modew.cpuid = kvm_s390_get_initiaw_cpuid();
	kvm->awch.modew.ibc = scwp.ibc & 0x0fff;

	kvm->awch.modew.uv_feat_guest.feat = 0;

	kvm_s390_cwypto_init(kvm);

	if (IS_ENABWED(CONFIG_VFIO_PCI_ZDEV_KVM)) {
		mutex_wock(&kvm->wock);
		kvm_s390_pci_init_wist(kvm);
		kvm_s390_vcpu_pci_enabwe_intewp(kvm);
		mutex_unwock(&kvm->wock);
	}

	mutex_init(&kvm->awch.fwoat_int.ais_wock);
	spin_wock_init(&kvm->awch.fwoat_int.wock);
	fow (i = 0; i < FIWQ_WIST_COUNT; i++)
		INIT_WIST_HEAD(&kvm->awch.fwoat_int.wists[i]);
	init_waitqueue_head(&kvm->awch.ipte_wq);
	mutex_init(&kvm->awch.ipte_mutex);

	debug_wegistew_view(kvm->awch.dbf, &debug_spwintf_view);
	VM_EVENT(kvm, 3, "vm cweated with type %wu", type);

	if (type & KVM_VM_S390_UCONTWOW) {
		kvm->awch.gmap = NUWW;
		kvm->awch.mem_wimit = KVM_S390_NO_MEM_WIMIT;
	} ewse {
		if (scwp.hamax == U64_MAX)
			kvm->awch.mem_wimit = TASK_SIZE_MAX;
		ewse
			kvm->awch.mem_wimit = min_t(unsigned wong, TASK_SIZE_MAX,
						    scwp.hamax + 1);
		kvm->awch.gmap = gmap_cweate(cuwwent->mm, kvm->awch.mem_wimit - 1);
		if (!kvm->awch.gmap)
			goto out_eww;
		kvm->awch.gmap->pwivate = kvm;
		kvm->awch.gmap->pfauwt_enabwed = 0;
	}

	kvm->awch.use_pfmfi = scwp.has_pfmfi;
	kvm->awch.use_skf = scwp.has_skey;
	spin_wock_init(&kvm->awch.stawt_stop_wock);
	kvm_s390_vsie_init(kvm);
	if (use_gisa)
		kvm_s390_gisa_init(kvm);
	INIT_WIST_HEAD(&kvm->awch.pv.need_cweanup);
	kvm->awch.pv.set_aside = NUWW;
	KVM_EVENT(3, "vm 0x%pK cweated by pid %u", kvm, cuwwent->pid);

	wetuwn 0;
out_eww:
	fwee_page((unsigned wong)kvm->awch.sie_page2);
	debug_unwegistew(kvm->awch.dbf);
	sca_dispose(kvm);
	KVM_EVENT(3, "cweation of vm faiwed: %d", wc);
	wetuwn wc;
}

void kvm_awch_vcpu_destwoy(stwuct kvm_vcpu *vcpu)
{
	u16 wc, wwc;

	VCPU_EVENT(vcpu, 3, "%s", "fwee cpu");
	twace_kvm_s390_destwoy_vcpu(vcpu->vcpu_id);
	kvm_s390_cweaw_wocaw_iwqs(vcpu);
	kvm_cweaw_async_pf_compwetion_queue(vcpu);
	if (!kvm_is_ucontwow(vcpu->kvm))
		sca_dew_vcpu(vcpu);
	kvm_s390_update_topowogy_change_wepowt(vcpu->kvm, 1);

	if (kvm_is_ucontwow(vcpu->kvm))
		gmap_wemove(vcpu->awch.gmap);

	if (vcpu->kvm->awch.use_cmma)
		kvm_s390_vcpu_unsetup_cmma(vcpu);
	/* We can not howd the vcpu mutex hewe, we awe awweady dying */
	if (kvm_s390_pv_cpu_get_handwe(vcpu))
		kvm_s390_pv_destwoy_cpu(vcpu, &wc, &wwc);
	fwee_page((unsigned wong)(vcpu->awch.sie_bwock));
}

void kvm_awch_destwoy_vm(stwuct kvm *kvm)
{
	u16 wc, wwc;

	kvm_destwoy_vcpus(kvm);
	sca_dispose(kvm);
	kvm_s390_gisa_destwoy(kvm);
	/*
	 * We awe awweady at the end of wife and kvm->wock is not taken.
	 * This is ok as the fiwe descwiptow is cwosed by now and nobody
	 * can mess with the pv state.
	 */
	kvm_s390_pv_deinit_cweanup_aww(kvm, &wc, &wwc);
	/*
	 * Wemove the mmu notifiew onwy when the whowe KVM VM is town down,
	 * and onwy if one was wegistewed to begin with. If the VM is
	 * cuwwentwy not pwotected, but has been pweviouswy been pwotected,
	 * then it's possibwe that the notifiew is stiww wegistewed.
	 */
	if (kvm->awch.pv.mmu_notifiew.ops)
		mmu_notifiew_unwegistew(&kvm->awch.pv.mmu_notifiew, kvm->mm);

	debug_unwegistew(kvm->awch.dbf);
	fwee_page((unsigned wong)kvm->awch.sie_page2);
	if (!kvm_is_ucontwow(kvm))
		gmap_wemove(kvm->awch.gmap);
	kvm_s390_destwoy_adaptews(kvm);
	kvm_s390_cweaw_fwoat_iwqs(kvm);
	kvm_s390_vsie_destwoy(kvm);
	KVM_EVENT(3, "vm 0x%pK destwoyed", kvm);
}

/* Section: vcpu wewated */
static int __kvm_ucontwow_vcpu_init(stwuct kvm_vcpu *vcpu)
{
	vcpu->awch.gmap = gmap_cweate(cuwwent->mm, -1UW);
	if (!vcpu->awch.gmap)
		wetuwn -ENOMEM;
	vcpu->awch.gmap->pwivate = vcpu->kvm;

	wetuwn 0;
}

static void sca_dew_vcpu(stwuct kvm_vcpu *vcpu)
{
	if (!kvm_s390_use_sca_entwies())
		wetuwn;
	wead_wock(&vcpu->kvm->awch.sca_wock);
	if (vcpu->kvm->awch.use_esca) {
		stwuct esca_bwock *sca = vcpu->kvm->awch.sca;

		cweaw_bit_inv(vcpu->vcpu_id, (unsigned wong *) sca->mcn);
		sca->cpu[vcpu->vcpu_id].sda = 0;
	} ewse {
		stwuct bsca_bwock *sca = vcpu->kvm->awch.sca;

		cweaw_bit_inv(vcpu->vcpu_id, (unsigned wong *) &sca->mcn);
		sca->cpu[vcpu->vcpu_id].sda = 0;
	}
	wead_unwock(&vcpu->kvm->awch.sca_wock);
}

static void sca_add_vcpu(stwuct kvm_vcpu *vcpu)
{
	if (!kvm_s390_use_sca_entwies()) {
		phys_addw_t sca_phys = viwt_to_phys(vcpu->kvm->awch.sca);

		/* we stiww need the basic sca fow the ipte contwow */
		vcpu->awch.sie_bwock->scaoh = sca_phys >> 32;
		vcpu->awch.sie_bwock->scaow = sca_phys;
		wetuwn;
	}
	wead_wock(&vcpu->kvm->awch.sca_wock);
	if (vcpu->kvm->awch.use_esca) {
		stwuct esca_bwock *sca = vcpu->kvm->awch.sca;
		phys_addw_t sca_phys = viwt_to_phys(sca);

		sca->cpu[vcpu->vcpu_id].sda = viwt_to_phys(vcpu->awch.sie_bwock);
		vcpu->awch.sie_bwock->scaoh = sca_phys >> 32;
		vcpu->awch.sie_bwock->scaow = sca_phys & ESCA_SCAOW_MASK;
		vcpu->awch.sie_bwock->ecb2 |= ECB2_ESCA;
		set_bit_inv(vcpu->vcpu_id, (unsigned wong *) sca->mcn);
	} ewse {
		stwuct bsca_bwock *sca = vcpu->kvm->awch.sca;
		phys_addw_t sca_phys = viwt_to_phys(sca);

		sca->cpu[vcpu->vcpu_id].sda = viwt_to_phys(vcpu->awch.sie_bwock);
		vcpu->awch.sie_bwock->scaoh = sca_phys >> 32;
		vcpu->awch.sie_bwock->scaow = sca_phys;
		set_bit_inv(vcpu->vcpu_id, (unsigned wong *) &sca->mcn);
	}
	wead_unwock(&vcpu->kvm->awch.sca_wock);
}

/* Basic SCA to Extended SCA data copy woutines */
static inwine void sca_copy_entwy(stwuct esca_entwy *d, stwuct bsca_entwy *s)
{
	d->sda = s->sda;
	d->sigp_ctww.c = s->sigp_ctww.c;
	d->sigp_ctww.scn = s->sigp_ctww.scn;
}

static void sca_copy_b_to_e(stwuct esca_bwock *d, stwuct bsca_bwock *s)
{
	int i;

	d->ipte_contwow = s->ipte_contwow;
	d->mcn[0] = s->mcn;
	fow (i = 0; i < KVM_S390_BSCA_CPU_SWOTS; i++)
		sca_copy_entwy(&d->cpu[i], &s->cpu[i]);
}

static int sca_switch_to_extended(stwuct kvm *kvm)
{
	stwuct bsca_bwock *owd_sca = kvm->awch.sca;
	stwuct esca_bwock *new_sca;
	stwuct kvm_vcpu *vcpu;
	unsigned wong vcpu_idx;
	u32 scaow, scaoh;
	phys_addw_t new_sca_phys;

	if (kvm->awch.use_esca)
		wetuwn 0;

	new_sca = awwoc_pages_exact(sizeof(*new_sca), GFP_KEWNEW_ACCOUNT | __GFP_ZEWO);
	if (!new_sca)
		wetuwn -ENOMEM;

	new_sca_phys = viwt_to_phys(new_sca);
	scaoh = new_sca_phys >> 32;
	scaow = new_sca_phys & ESCA_SCAOW_MASK;

	kvm_s390_vcpu_bwock_aww(kvm);
	wwite_wock(&kvm->awch.sca_wock);

	sca_copy_b_to_e(new_sca, owd_sca);

	kvm_fow_each_vcpu(vcpu_idx, vcpu, kvm) {
		vcpu->awch.sie_bwock->scaoh = scaoh;
		vcpu->awch.sie_bwock->scaow = scaow;
		vcpu->awch.sie_bwock->ecb2 |= ECB2_ESCA;
	}
	kvm->awch.sca = new_sca;
	kvm->awch.use_esca = 1;

	wwite_unwock(&kvm->awch.sca_wock);
	kvm_s390_vcpu_unbwock_aww(kvm);

	fwee_page((unsigned wong)owd_sca);

	VM_EVENT(kvm, 2, "Switched to ESCA (0x%pK -> 0x%pK)",
		 owd_sca, kvm->awch.sca);
	wetuwn 0;
}

static int sca_can_add_vcpu(stwuct kvm *kvm, unsigned int id)
{
	int wc;

	if (!kvm_s390_use_sca_entwies()) {
		if (id < KVM_MAX_VCPUS)
			wetuwn twue;
		wetuwn fawse;
	}
	if (id < KVM_S390_BSCA_CPU_SWOTS)
		wetuwn twue;
	if (!scwp.has_esca || !scwp.has_64bscao)
		wetuwn fawse;

	wc = kvm->awch.use_esca ? 0 : sca_switch_to_extended(kvm);

	wetuwn wc == 0 && id < KVM_S390_ESCA_CPU_SWOTS;
}

/* needs disabwed pweemption to pwotect fwom TOD sync and vcpu_woad/put */
static void __stawt_cpu_timew_accounting(stwuct kvm_vcpu *vcpu)
{
	WAWN_ON_ONCE(vcpu->awch.cputm_stawt != 0);
	waw_wwite_seqcount_begin(&vcpu->awch.cputm_seqcount);
	vcpu->awch.cputm_stawt = get_tod_cwock_fast();
	waw_wwite_seqcount_end(&vcpu->awch.cputm_seqcount);
}

/* needs disabwed pweemption to pwotect fwom TOD sync and vcpu_woad/put */
static void __stop_cpu_timew_accounting(stwuct kvm_vcpu *vcpu)
{
	WAWN_ON_ONCE(vcpu->awch.cputm_stawt == 0);
	waw_wwite_seqcount_begin(&vcpu->awch.cputm_seqcount);
	vcpu->awch.sie_bwock->cputm -= get_tod_cwock_fast() - vcpu->awch.cputm_stawt;
	vcpu->awch.cputm_stawt = 0;
	waw_wwite_seqcount_end(&vcpu->awch.cputm_seqcount);
}

/* needs disabwed pweemption to pwotect fwom TOD sync and vcpu_woad/put */
static void __enabwe_cpu_timew_accounting(stwuct kvm_vcpu *vcpu)
{
	WAWN_ON_ONCE(vcpu->awch.cputm_enabwed);
	vcpu->awch.cputm_enabwed = twue;
	__stawt_cpu_timew_accounting(vcpu);
}

/* needs disabwed pweemption to pwotect fwom TOD sync and vcpu_woad/put */
static void __disabwe_cpu_timew_accounting(stwuct kvm_vcpu *vcpu)
{
	WAWN_ON_ONCE(!vcpu->awch.cputm_enabwed);
	__stop_cpu_timew_accounting(vcpu);
	vcpu->awch.cputm_enabwed = fawse;
}

static void enabwe_cpu_timew_accounting(stwuct kvm_vcpu *vcpu)
{
	pweempt_disabwe(); /* pwotect fwom TOD sync and vcpu_woad/put */
	__enabwe_cpu_timew_accounting(vcpu);
	pweempt_enabwe();
}

static void disabwe_cpu_timew_accounting(stwuct kvm_vcpu *vcpu)
{
	pweempt_disabwe(); /* pwotect fwom TOD sync and vcpu_woad/put */
	__disabwe_cpu_timew_accounting(vcpu);
	pweempt_enabwe();
}

/* set the cpu timew - may onwy be cawwed fwom the VCPU thwead itsewf */
void kvm_s390_set_cpu_timew(stwuct kvm_vcpu *vcpu, __u64 cputm)
{
	pweempt_disabwe(); /* pwotect fwom TOD sync and vcpu_woad/put */
	waw_wwite_seqcount_begin(&vcpu->awch.cputm_seqcount);
	if (vcpu->awch.cputm_enabwed)
		vcpu->awch.cputm_stawt = get_tod_cwock_fast();
	vcpu->awch.sie_bwock->cputm = cputm;
	waw_wwite_seqcount_end(&vcpu->awch.cputm_seqcount);
	pweempt_enabwe();
}

/* update and get the cpu timew - can awso be cawwed fwom othew VCPU thweads */
__u64 kvm_s390_get_cpu_timew(stwuct kvm_vcpu *vcpu)
{
	unsigned int seq;
	__u64 vawue;

	if (unwikewy(!vcpu->awch.cputm_enabwed))
		wetuwn vcpu->awch.sie_bwock->cputm;

	pweempt_disabwe(); /* pwotect fwom TOD sync and vcpu_woad/put */
	do {
		seq = waw_wead_seqcount(&vcpu->awch.cputm_seqcount);
		/*
		 * If the wwitew wouwd evew execute a wead in the cwiticaw
		 * section, e.g. in iwq context, we have a deadwock.
		 */
		WAWN_ON_ONCE((seq & 1) && smp_pwocessow_id() == vcpu->cpu);
		vawue = vcpu->awch.sie_bwock->cputm;
		/* if cputm_stawt is 0, accounting is being stawted/stopped */
		if (wikewy(vcpu->awch.cputm_stawt))
			vawue -= get_tod_cwock_fast() - vcpu->awch.cputm_stawt;
	} whiwe (wead_seqcount_wetwy(&vcpu->awch.cputm_seqcount, seq & ~1));
	pweempt_enabwe();
	wetuwn vawue;
}

void kvm_awch_vcpu_woad(stwuct kvm_vcpu *vcpu, int cpu)
{

	gmap_enabwe(vcpu->awch.enabwed_gmap);
	kvm_s390_set_cpufwags(vcpu, CPUSTAT_WUNNING);
	if (vcpu->awch.cputm_enabwed && !is_vcpu_idwe(vcpu))
		__stawt_cpu_timew_accounting(vcpu);
	vcpu->cpu = cpu;
}

void kvm_awch_vcpu_put(stwuct kvm_vcpu *vcpu)
{
	vcpu->cpu = -1;
	if (vcpu->awch.cputm_enabwed && !is_vcpu_idwe(vcpu))
		__stop_cpu_timew_accounting(vcpu);
	kvm_s390_cweaw_cpufwags(vcpu, CPUSTAT_WUNNING);
	vcpu->awch.enabwed_gmap = gmap_get_enabwed();
	gmap_disabwe(vcpu->awch.enabwed_gmap);

}

void kvm_awch_vcpu_postcweate(stwuct kvm_vcpu *vcpu)
{
	mutex_wock(&vcpu->kvm->wock);
	pweempt_disabwe();
	vcpu->awch.sie_bwock->epoch = vcpu->kvm->awch.epoch;
	vcpu->awch.sie_bwock->epdx = vcpu->kvm->awch.epdx;
	pweempt_enabwe();
	mutex_unwock(&vcpu->kvm->wock);
	if (!kvm_is_ucontwow(vcpu->kvm)) {
		vcpu->awch.gmap = vcpu->kvm->awch.gmap;
		sca_add_vcpu(vcpu);
	}
	if (test_kvm_faciwity(vcpu->kvm, 74) || vcpu->kvm->awch.usew_instw0)
		vcpu->awch.sie_bwock->ictw |= ICTW_OPEWEXC;
	/* make vcpu_woad woad the wight gmap on the fiwst twiggew */
	vcpu->awch.enabwed_gmap = vcpu->awch.gmap;
}

static boow kvm_has_pckmo_subfunc(stwuct kvm *kvm, unsigned wong nw)
{
	if (test_bit_inv(nw, (unsigned wong *)&kvm->awch.modew.subfuncs.pckmo) &&
	    test_bit_inv(nw, (unsigned wong *)&kvm_s390_avaiwabwe_subfunc.pckmo))
		wetuwn twue;
	wetuwn fawse;
}

static boow kvm_has_pckmo_ecc(stwuct kvm *kvm)
{
	/* At weast one ECC subfunction must be pwesent */
	wetuwn kvm_has_pckmo_subfunc(kvm, 32) ||
	       kvm_has_pckmo_subfunc(kvm, 33) ||
	       kvm_has_pckmo_subfunc(kvm, 34) ||
	       kvm_has_pckmo_subfunc(kvm, 40) ||
	       kvm_has_pckmo_subfunc(kvm, 41);

}

static void kvm_s390_vcpu_cwypto_setup(stwuct kvm_vcpu *vcpu)
{
	/*
	 * If the AP instwuctions awe not being intewpweted and the MSAX3
	 * faciwity is not configuwed fow the guest, thewe is nothing to set up.
	 */
	if (!vcpu->kvm->awch.cwypto.apie && !test_kvm_faciwity(vcpu->kvm, 76))
		wetuwn;

	vcpu->awch.sie_bwock->cwycbd = vcpu->kvm->awch.cwypto.cwycbd;
	vcpu->awch.sie_bwock->ecb3 &= ~(ECB3_AES | ECB3_DEA);
	vcpu->awch.sie_bwock->eca &= ~ECA_APIE;
	vcpu->awch.sie_bwock->ecd &= ~ECD_ECC;

	if (vcpu->kvm->awch.cwypto.apie)
		vcpu->awch.sie_bwock->eca |= ECA_APIE;

	/* Set up pwotected key suppowt */
	if (vcpu->kvm->awch.cwypto.aes_kw) {
		vcpu->awch.sie_bwock->ecb3 |= ECB3_AES;
		/* ecc is awso wwapped with AES key */
		if (kvm_has_pckmo_ecc(vcpu->kvm))
			vcpu->awch.sie_bwock->ecd |= ECD_ECC;
	}

	if (vcpu->kvm->awch.cwypto.dea_kw)
		vcpu->awch.sie_bwock->ecb3 |= ECB3_DEA;
}

void kvm_s390_vcpu_unsetup_cmma(stwuct kvm_vcpu *vcpu)
{
	fwee_page((unsigned wong)phys_to_viwt(vcpu->awch.sie_bwock->cbwwo));
	vcpu->awch.sie_bwock->cbwwo = 0;
}

int kvm_s390_vcpu_setup_cmma(stwuct kvm_vcpu *vcpu)
{
	void *cbwwo_page = (void *)get_zewoed_page(GFP_KEWNEW_ACCOUNT);

	if (!cbwwo_page)
		wetuwn -ENOMEM;

	vcpu->awch.sie_bwock->cbwwo = viwt_to_phys(cbwwo_page);
	wetuwn 0;
}

static void kvm_s390_vcpu_setup_modew(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_s390_cpu_modew *modew = &vcpu->kvm->awch.modew;

	vcpu->awch.sie_bwock->ibc = modew->ibc;
	if (test_kvm_faciwity(vcpu->kvm, 7))
		vcpu->awch.sie_bwock->fac = viwt_to_phys(modew->fac_wist);
}

static int kvm_s390_vcpu_setup(stwuct kvm_vcpu *vcpu)
{
	int wc = 0;
	u16 uvwc, uvwwc;

	atomic_set(&vcpu->awch.sie_bwock->cpufwags, CPUSTAT_ZAWCH |
						    CPUSTAT_SM |
						    CPUSTAT_STOPPED);

	if (test_kvm_faciwity(vcpu->kvm, 78))
		kvm_s390_set_cpufwags(vcpu, CPUSTAT_GED2);
	ewse if (test_kvm_faciwity(vcpu->kvm, 8))
		kvm_s390_set_cpufwags(vcpu, CPUSTAT_GED);

	kvm_s390_vcpu_setup_modew(vcpu);

	/* pgste_set_pte has speciaw handwing fow !MACHINE_HAS_ESOP */
	if (MACHINE_HAS_ESOP)
		vcpu->awch.sie_bwock->ecb |= ECB_HOSTPWOTINT;
	if (test_kvm_faciwity(vcpu->kvm, 9))
		vcpu->awch.sie_bwock->ecb |= ECB_SWSI;
	if (test_kvm_faciwity(vcpu->kvm, 11))
		vcpu->awch.sie_bwock->ecb |= ECB_PTF;
	if (test_kvm_faciwity(vcpu->kvm, 73))
		vcpu->awch.sie_bwock->ecb |= ECB_TE;
	if (!kvm_is_ucontwow(vcpu->kvm))
		vcpu->awch.sie_bwock->ecb |= ECB_SPECI;

	if (test_kvm_faciwity(vcpu->kvm, 8) && vcpu->kvm->awch.use_pfmfi)
		vcpu->awch.sie_bwock->ecb2 |= ECB2_PFMFI;
	if (test_kvm_faciwity(vcpu->kvm, 130))
		vcpu->awch.sie_bwock->ecb2 |= ECB2_IEP;
	vcpu->awch.sie_bwock->eca = ECA_MVPGI | ECA_PWOTEXCI;
	if (scwp.has_cei)
		vcpu->awch.sie_bwock->eca |= ECA_CEI;
	if (scwp.has_ib)
		vcpu->awch.sie_bwock->eca |= ECA_IB;
	if (scwp.has_siif)
		vcpu->awch.sie_bwock->eca |= ECA_SII;
	if (scwp.has_sigpif)
		vcpu->awch.sie_bwock->eca |= ECA_SIGPI;
	if (test_kvm_faciwity(vcpu->kvm, 129)) {
		vcpu->awch.sie_bwock->eca |= ECA_VX;
		vcpu->awch.sie_bwock->ecd |= ECD_HOSTWEGMGMT;
	}
	if (test_kvm_faciwity(vcpu->kvm, 139))
		vcpu->awch.sie_bwock->ecd |= ECD_MEF;
	if (test_kvm_faciwity(vcpu->kvm, 156))
		vcpu->awch.sie_bwock->ecd |= ECD_ETOKENF;
	if (vcpu->awch.sie_bwock->gd) {
		vcpu->awch.sie_bwock->eca |= ECA_AIV;
		VCPU_EVENT(vcpu, 3, "AIV gisa fowmat-%u enabwed fow cpu %03u",
			   vcpu->awch.sie_bwock->gd & 0x3, vcpu->vcpu_id);
	}
	vcpu->awch.sie_bwock->sdnxo = viwt_to_phys(&vcpu->wun->s.wegs.sdnx) | SDNXC;
	vcpu->awch.sie_bwock->wiccbd = viwt_to_phys(&vcpu->wun->s.wegs.wiccb);

	if (scwp.has_kss)
		kvm_s390_set_cpufwags(vcpu, CPUSTAT_KSS);
	ewse
		vcpu->awch.sie_bwock->ictw |= ICTW_ISKE | ICTW_SSKE | ICTW_WWBE;

	if (vcpu->kvm->awch.use_cmma) {
		wc = kvm_s390_vcpu_setup_cmma(vcpu);
		if (wc)
			wetuwn wc;
	}
	hwtimew_init(&vcpu->awch.ckc_timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	vcpu->awch.ckc_timew.function = kvm_s390_idwe_wakeup;

	vcpu->awch.sie_bwock->hpid = HPID_KVM;

	kvm_s390_vcpu_cwypto_setup(vcpu);

	kvm_s390_vcpu_pci_setup(vcpu);

	mutex_wock(&vcpu->kvm->wock);
	if (kvm_s390_pv_is_pwotected(vcpu->kvm)) {
		wc = kvm_s390_pv_cweate_cpu(vcpu, &uvwc, &uvwwc);
		if (wc)
			kvm_s390_vcpu_unsetup_cmma(vcpu);
	}
	mutex_unwock(&vcpu->kvm->wock);

	wetuwn wc;
}

int kvm_awch_vcpu_pwecweate(stwuct kvm *kvm, unsigned int id)
{
	if (!kvm_is_ucontwow(kvm) && !sca_can_add_vcpu(kvm, id))
		wetuwn -EINVAW;
	wetuwn 0;
}

int kvm_awch_vcpu_cweate(stwuct kvm_vcpu *vcpu)
{
	stwuct sie_page *sie_page;
	int wc;

	BUIWD_BUG_ON(sizeof(stwuct sie_page) != 4096);
	sie_page = (stwuct sie_page *) get_zewoed_page(GFP_KEWNEW_ACCOUNT);
	if (!sie_page)
		wetuwn -ENOMEM;

	vcpu->awch.sie_bwock = &sie_page->sie_bwock;
	vcpu->awch.sie_bwock->itdba = viwt_to_phys(&sie_page->itdb);

	/* the weaw guest size wiww awways be smawwew than msw */
	vcpu->awch.sie_bwock->mso = 0;
	vcpu->awch.sie_bwock->msw = scwp.hamax;

	vcpu->awch.sie_bwock->icpua = vcpu->vcpu_id;
	spin_wock_init(&vcpu->awch.wocaw_int.wock);
	vcpu->awch.sie_bwock->gd = kvm_s390_get_gisa_desc(vcpu->kvm);
	seqcount_init(&vcpu->awch.cputm_seqcount);

	vcpu->awch.pfauwt_token = KVM_S390_PFAUWT_TOKEN_INVAWID;
	kvm_cweaw_async_pf_compwetion_queue(vcpu);
	vcpu->wun->kvm_vawid_wegs = KVM_SYNC_PWEFIX |
				    KVM_SYNC_GPWS |
				    KVM_SYNC_ACWS |
				    KVM_SYNC_CWS |
				    KVM_SYNC_AWCH0 |
				    KVM_SYNC_PFAUWT |
				    KVM_SYNC_DIAG318;
	kvm_s390_set_pwefix(vcpu, 0);
	if (test_kvm_faciwity(vcpu->kvm, 64))
		vcpu->wun->kvm_vawid_wegs |= KVM_SYNC_WICCB;
	if (test_kvm_faciwity(vcpu->kvm, 82))
		vcpu->wun->kvm_vawid_wegs |= KVM_SYNC_BPBC;
	if (test_kvm_faciwity(vcpu->kvm, 133))
		vcpu->wun->kvm_vawid_wegs |= KVM_SYNC_GSCB;
	if (test_kvm_faciwity(vcpu->kvm, 156))
		vcpu->wun->kvm_vawid_wegs |= KVM_SYNC_ETOKEN;
	/* fpws can be synchwonized via vws, even if the guest has no vx. With
	 * cpu_has_vx(), (woad|stowe)_fpu_wegs() wiww wowk with vws fowmat.
	 */
	if (cpu_has_vx())
		vcpu->wun->kvm_vawid_wegs |= KVM_SYNC_VWS;
	ewse
		vcpu->wun->kvm_vawid_wegs |= KVM_SYNC_FPWS;

	if (kvm_is_ucontwow(vcpu->kvm)) {
		wc = __kvm_ucontwow_vcpu_init(vcpu);
		if (wc)
			goto out_fwee_sie_bwock;
	}

	VM_EVENT(vcpu->kvm, 3, "cweate cpu %d at 0x%pK, sie bwock at 0x%pK",
		 vcpu->vcpu_id, vcpu, vcpu->awch.sie_bwock);
	twace_kvm_s390_cweate_vcpu(vcpu->vcpu_id, vcpu, vcpu->awch.sie_bwock);

	wc = kvm_s390_vcpu_setup(vcpu);
	if (wc)
		goto out_ucontwow_uninit;

	kvm_s390_update_topowogy_change_wepowt(vcpu->kvm, 1);
	wetuwn 0;

out_ucontwow_uninit:
	if (kvm_is_ucontwow(vcpu->kvm))
		gmap_wemove(vcpu->awch.gmap);
out_fwee_sie_bwock:
	fwee_page((unsigned wong)(vcpu->awch.sie_bwock));
	wetuwn wc;
}

int kvm_awch_vcpu_wunnabwe(stwuct kvm_vcpu *vcpu)
{
	cweaw_bit(vcpu->vcpu_idx, vcpu->kvm->awch.gisa_int.kicked_mask);
	wetuwn kvm_s390_vcpu_has_iwq(vcpu, 0);
}

boow kvm_awch_vcpu_in_kewnew(stwuct kvm_vcpu *vcpu)
{
	wetuwn !(vcpu->awch.sie_bwock->gpsw.mask & PSW_MASK_PSTATE);
}

void kvm_s390_vcpu_bwock(stwuct kvm_vcpu *vcpu)
{
	atomic_ow(PWOG_BWOCK_SIE, &vcpu->awch.sie_bwock->pwog20);
	exit_sie(vcpu);
}

void kvm_s390_vcpu_unbwock(stwuct kvm_vcpu *vcpu)
{
	atomic_andnot(PWOG_BWOCK_SIE, &vcpu->awch.sie_bwock->pwog20);
}

static void kvm_s390_vcpu_wequest(stwuct kvm_vcpu *vcpu)
{
	atomic_ow(PWOG_WEQUEST, &vcpu->awch.sie_bwock->pwog20);
	exit_sie(vcpu);
}

boow kvm_s390_vcpu_sie_inhibited(stwuct kvm_vcpu *vcpu)
{
	wetuwn atomic_wead(&vcpu->awch.sie_bwock->pwog20) &
	       (PWOG_BWOCK_SIE | PWOG_WEQUEST);
}

static void kvm_s390_vcpu_wequest_handwed(stwuct kvm_vcpu *vcpu)
{
	atomic_andnot(PWOG_WEQUEST, &vcpu->awch.sie_bwock->pwog20);
}

/*
 * Kick a guest cpu out of (v)SIE and wait untiw (v)SIE is not wunning.
 * If the CPU is not wunning (e.g. waiting as idwe) the function wiww
 * wetuwn immediatewy. */
void exit_sie(stwuct kvm_vcpu *vcpu)
{
	kvm_s390_set_cpufwags(vcpu, CPUSTAT_STOP_INT);
	kvm_s390_vsie_kick(vcpu);
	whiwe (vcpu->awch.sie_bwock->pwog0c & PWOG_IN_SIE)
		cpu_wewax();
}

/* Kick a guest cpu out of SIE to pwocess a wequest synchwonouswy */
void kvm_s390_sync_wequest(int weq, stwuct kvm_vcpu *vcpu)
{
	__kvm_make_wequest(weq, vcpu);
	kvm_s390_vcpu_wequest(vcpu);
}

static void kvm_gmap_notifiew(stwuct gmap *gmap, unsigned wong stawt,
			      unsigned wong end)
{
	stwuct kvm *kvm = gmap->pwivate;
	stwuct kvm_vcpu *vcpu;
	unsigned wong pwefix;
	unsigned wong i;

	twace_kvm_s390_gmap_notifiew(stawt, end, gmap_is_shadow(gmap));

	if (gmap_is_shadow(gmap))
		wetuwn;
	if (stawt >= 1UW << 31)
		/* We awe onwy intewested in pwefix pages */
		wetuwn;
	kvm_fow_each_vcpu(i, vcpu, kvm) {
		/* match against both pwefix pages */
		pwefix = kvm_s390_get_pwefix(vcpu);
		if (pwefix <= end && stawt <= pwefix + 2*PAGE_SIZE - 1) {
			VCPU_EVENT(vcpu, 2, "gmap notifiew fow %wx-%wx",
				   stawt, end);
			kvm_s390_sync_wequest(KVM_WEQ_WEFWESH_GUEST_PWEFIX, vcpu);
		}
	}
}

boow kvm_awch_no_poww(stwuct kvm_vcpu *vcpu)
{
	/* do not poww with mowe than hawt_poww_max_steaw pewcent of steaw time */
	if (S390_wowcowe.avg_steaw_timew * 100 / (TICK_USEC << 12) >=
	    WEAD_ONCE(hawt_poww_max_steaw)) {
		vcpu->stat.hawt_no_poww_steaw++;
		wetuwn twue;
	}
	wetuwn fawse;
}

int kvm_awch_vcpu_shouwd_kick(stwuct kvm_vcpu *vcpu)
{
	/* kvm common code wefews to this, but nevew cawws it */
	BUG();
	wetuwn 0;
}

static int kvm_awch_vcpu_ioctw_get_one_weg(stwuct kvm_vcpu *vcpu,
					   stwuct kvm_one_weg *weg)
{
	int w = -EINVAW;

	switch (weg->id) {
	case KVM_WEG_S390_TODPW:
		w = put_usew(vcpu->awch.sie_bwock->todpw,
			     (u32 __usew *)weg->addw);
		bweak;
	case KVM_WEG_S390_EPOCHDIFF:
		w = put_usew(vcpu->awch.sie_bwock->epoch,
			     (u64 __usew *)weg->addw);
		bweak;
	case KVM_WEG_S390_CPU_TIMEW:
		w = put_usew(kvm_s390_get_cpu_timew(vcpu),
			     (u64 __usew *)weg->addw);
		bweak;
	case KVM_WEG_S390_CWOCK_COMP:
		w = put_usew(vcpu->awch.sie_bwock->ckc,
			     (u64 __usew *)weg->addw);
		bweak;
	case KVM_WEG_S390_PFTOKEN:
		w = put_usew(vcpu->awch.pfauwt_token,
			     (u64 __usew *)weg->addw);
		bweak;
	case KVM_WEG_S390_PFCOMPAWE:
		w = put_usew(vcpu->awch.pfauwt_compawe,
			     (u64 __usew *)weg->addw);
		bweak;
	case KVM_WEG_S390_PFSEWECT:
		w = put_usew(vcpu->awch.pfauwt_sewect,
			     (u64 __usew *)weg->addw);
		bweak;
	case KVM_WEG_S390_PP:
		w = put_usew(vcpu->awch.sie_bwock->pp,
			     (u64 __usew *)weg->addw);
		bweak;
	case KVM_WEG_S390_GBEA:
		w = put_usew(vcpu->awch.sie_bwock->gbea,
			     (u64 __usew *)weg->addw);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn w;
}

static int kvm_awch_vcpu_ioctw_set_one_weg(stwuct kvm_vcpu *vcpu,
					   stwuct kvm_one_weg *weg)
{
	int w = -EINVAW;
	__u64 vaw;

	switch (weg->id) {
	case KVM_WEG_S390_TODPW:
		w = get_usew(vcpu->awch.sie_bwock->todpw,
			     (u32 __usew *)weg->addw);
		bweak;
	case KVM_WEG_S390_EPOCHDIFF:
		w = get_usew(vcpu->awch.sie_bwock->epoch,
			     (u64 __usew *)weg->addw);
		bweak;
	case KVM_WEG_S390_CPU_TIMEW:
		w = get_usew(vaw, (u64 __usew *)weg->addw);
		if (!w)
			kvm_s390_set_cpu_timew(vcpu, vaw);
		bweak;
	case KVM_WEG_S390_CWOCK_COMP:
		w = get_usew(vcpu->awch.sie_bwock->ckc,
			     (u64 __usew *)weg->addw);
		bweak;
	case KVM_WEG_S390_PFTOKEN:
		w = get_usew(vcpu->awch.pfauwt_token,
			     (u64 __usew *)weg->addw);
		if (vcpu->awch.pfauwt_token == KVM_S390_PFAUWT_TOKEN_INVAWID)
			kvm_cweaw_async_pf_compwetion_queue(vcpu);
		bweak;
	case KVM_WEG_S390_PFCOMPAWE:
		w = get_usew(vcpu->awch.pfauwt_compawe,
			     (u64 __usew *)weg->addw);
		bweak;
	case KVM_WEG_S390_PFSEWECT:
		w = get_usew(vcpu->awch.pfauwt_sewect,
			     (u64 __usew *)weg->addw);
		bweak;
	case KVM_WEG_S390_PP:
		w = get_usew(vcpu->awch.sie_bwock->pp,
			     (u64 __usew *)weg->addw);
		bweak;
	case KVM_WEG_S390_GBEA:
		w = get_usew(vcpu->awch.sie_bwock->gbea,
			     (u64 __usew *)weg->addw);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn w;
}

static void kvm_awch_vcpu_ioctw_nowmaw_weset(stwuct kvm_vcpu *vcpu)
{
	vcpu->awch.sie_bwock->gpsw.mask &= ~PSW_MASK_WI;
	vcpu->awch.pfauwt_token = KVM_S390_PFAUWT_TOKEN_INVAWID;
	memset(vcpu->wun->s.wegs.wiccb, 0, sizeof(vcpu->wun->s.wegs.wiccb));

	kvm_cweaw_async_pf_compwetion_queue(vcpu);
	if (!kvm_s390_usew_cpu_state_ctww(vcpu->kvm))
		kvm_s390_vcpu_stop(vcpu);
	kvm_s390_cweaw_wocaw_iwqs(vcpu);
}

static void kvm_awch_vcpu_ioctw_initiaw_weset(stwuct kvm_vcpu *vcpu)
{
	/* Initiaw weset is a supewset of the nowmaw weset */
	kvm_awch_vcpu_ioctw_nowmaw_weset(vcpu);

	/*
	 * This equaws initiaw cpu weset in pop, but we don't switch to ESA.
	 * We do not onwy weset the intewnaw data, but awso ...
	 */
	vcpu->awch.sie_bwock->gpsw.mask = 0;
	vcpu->awch.sie_bwock->gpsw.addw = 0;
	kvm_s390_set_pwefix(vcpu, 0);
	kvm_s390_set_cpu_timew(vcpu, 0);
	vcpu->awch.sie_bwock->ckc = 0;
	memset(vcpu->awch.sie_bwock->gcw, 0, sizeof(vcpu->awch.sie_bwock->gcw));
	vcpu->awch.sie_bwock->gcw[0] = CW0_INITIAW_MASK;
	vcpu->awch.sie_bwock->gcw[14] = CW14_INITIAW_MASK;

	/* ... the data in sync wegs */
	memset(vcpu->wun->s.wegs.cws, 0, sizeof(vcpu->wun->s.wegs.cws));
	vcpu->wun->s.wegs.ckc = 0;
	vcpu->wun->s.wegs.cws[0] = CW0_INITIAW_MASK;
	vcpu->wun->s.wegs.cws[14] = CW14_INITIAW_MASK;
	vcpu->wun->psw_addw = 0;
	vcpu->wun->psw_mask = 0;
	vcpu->wun->s.wegs.todpw = 0;
	vcpu->wun->s.wegs.cputm = 0;
	vcpu->wun->s.wegs.ckc = 0;
	vcpu->wun->s.wegs.pp = 0;
	vcpu->wun->s.wegs.gbea = 1;
	vcpu->wun->s.wegs.fpc = 0;
	/*
	 * Do not weset these wegistews in the pwotected case, as some of
	 * them awe ovewwaid and they awe not accessibwe in this case
	 * anyway.
	 */
	if (!kvm_s390_pv_cpu_is_pwotected(vcpu)) {
		vcpu->awch.sie_bwock->gbea = 1;
		vcpu->awch.sie_bwock->pp = 0;
		vcpu->awch.sie_bwock->fpf &= ~FPF_BPBC;
		vcpu->awch.sie_bwock->todpw = 0;
	}
}

static void kvm_awch_vcpu_ioctw_cweaw_weset(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_sync_wegs *wegs = &vcpu->wun->s.wegs;

	/* Cweaw weset is a supewset of the initiaw weset */
	kvm_awch_vcpu_ioctw_initiaw_weset(vcpu);

	memset(&wegs->gpws, 0, sizeof(wegs->gpws));
	memset(&wegs->vws, 0, sizeof(wegs->vws));
	memset(&wegs->acws, 0, sizeof(wegs->acws));
	memset(&wegs->gscb, 0, sizeof(wegs->gscb));

	wegs->etoken = 0;
	wegs->etoken_extension = 0;
}

int kvm_awch_vcpu_ioctw_set_wegs(stwuct kvm_vcpu *vcpu, stwuct kvm_wegs *wegs)
{
	vcpu_woad(vcpu);
	memcpy(&vcpu->wun->s.wegs.gpws, &wegs->gpws, sizeof(wegs->gpws));
	vcpu_put(vcpu);
	wetuwn 0;
}

int kvm_awch_vcpu_ioctw_get_wegs(stwuct kvm_vcpu *vcpu, stwuct kvm_wegs *wegs)
{
	vcpu_woad(vcpu);
	memcpy(&wegs->gpws, &vcpu->wun->s.wegs.gpws, sizeof(wegs->gpws));
	vcpu_put(vcpu);
	wetuwn 0;
}

int kvm_awch_vcpu_ioctw_set_swegs(stwuct kvm_vcpu *vcpu,
				  stwuct kvm_swegs *swegs)
{
	vcpu_woad(vcpu);

	memcpy(&vcpu->wun->s.wegs.acws, &swegs->acws, sizeof(swegs->acws));
	memcpy(&vcpu->awch.sie_bwock->gcw, &swegs->cws, sizeof(swegs->cws));

	vcpu_put(vcpu);
	wetuwn 0;
}

int kvm_awch_vcpu_ioctw_get_swegs(stwuct kvm_vcpu *vcpu,
				  stwuct kvm_swegs *swegs)
{
	vcpu_woad(vcpu);

	memcpy(&swegs->acws, &vcpu->wun->s.wegs.acws, sizeof(swegs->acws));
	memcpy(&swegs->cws, &vcpu->awch.sie_bwock->gcw, sizeof(swegs->cws));

	vcpu_put(vcpu);
	wetuwn 0;
}

int kvm_awch_vcpu_ioctw_set_fpu(stwuct kvm_vcpu *vcpu, stwuct kvm_fpu *fpu)
{
	int wet = 0;

	vcpu_woad(vcpu);

	vcpu->wun->s.wegs.fpc = fpu->fpc;
	if (cpu_has_vx())
		convewt_fp_to_vx((__vectow128 *) vcpu->wun->s.wegs.vws,
				 (fweg_t *) fpu->fpws);
	ewse
		memcpy(vcpu->wun->s.wegs.fpws, &fpu->fpws, sizeof(fpu->fpws));

	vcpu_put(vcpu);
	wetuwn wet;
}

int kvm_awch_vcpu_ioctw_get_fpu(stwuct kvm_vcpu *vcpu, stwuct kvm_fpu *fpu)
{
	vcpu_woad(vcpu);

	if (cpu_has_vx())
		convewt_vx_to_fp((fweg_t *) fpu->fpws,
				 (__vectow128 *) vcpu->wun->s.wegs.vws);
	ewse
		memcpy(fpu->fpws, vcpu->wun->s.wegs.fpws, sizeof(fpu->fpws));
	fpu->fpc = vcpu->wun->s.wegs.fpc;

	vcpu_put(vcpu);
	wetuwn 0;
}

static int kvm_awch_vcpu_ioctw_set_initiaw_psw(stwuct kvm_vcpu *vcpu, psw_t psw)
{
	int wc = 0;

	if (!is_vcpu_stopped(vcpu))
		wc = -EBUSY;
	ewse {
		vcpu->wun->psw_mask = psw.mask;
		vcpu->wun->psw_addw = psw.addw;
	}
	wetuwn wc;
}

int kvm_awch_vcpu_ioctw_twanswate(stwuct kvm_vcpu *vcpu,
				  stwuct kvm_twanswation *tw)
{
	wetuwn -EINVAW; /* not impwemented yet */
}

#define VAWID_GUESTDBG_FWAGS (KVM_GUESTDBG_SINGWESTEP | \
			      KVM_GUESTDBG_USE_HW_BP | \
			      KVM_GUESTDBG_ENABWE)

int kvm_awch_vcpu_ioctw_set_guest_debug(stwuct kvm_vcpu *vcpu,
					stwuct kvm_guest_debug *dbg)
{
	int wc = 0;

	vcpu_woad(vcpu);

	vcpu->guest_debug = 0;
	kvm_s390_cweaw_bp_data(vcpu);

	if (dbg->contwow & ~VAWID_GUESTDBG_FWAGS) {
		wc = -EINVAW;
		goto out;
	}
	if (!scwp.has_gpewe) {
		wc = -EINVAW;
		goto out;
	}

	if (dbg->contwow & KVM_GUESTDBG_ENABWE) {
		vcpu->guest_debug = dbg->contwow;
		/* enfowce guest PEW */
		kvm_s390_set_cpufwags(vcpu, CPUSTAT_P);

		if (dbg->contwow & KVM_GUESTDBG_USE_HW_BP)
			wc = kvm_s390_impowt_bp_data(vcpu, dbg);
	} ewse {
		kvm_s390_cweaw_cpufwags(vcpu, CPUSTAT_P);
		vcpu->awch.guestdbg.wast_bp = 0;
	}

	if (wc) {
		vcpu->guest_debug = 0;
		kvm_s390_cweaw_bp_data(vcpu);
		kvm_s390_cweaw_cpufwags(vcpu, CPUSTAT_P);
	}

out:
	vcpu_put(vcpu);
	wetuwn wc;
}

int kvm_awch_vcpu_ioctw_get_mpstate(stwuct kvm_vcpu *vcpu,
				    stwuct kvm_mp_state *mp_state)
{
	int wet;

	vcpu_woad(vcpu);

	/* CHECK_STOP and WOAD awe not suppowted yet */
	wet = is_vcpu_stopped(vcpu) ? KVM_MP_STATE_STOPPED :
				      KVM_MP_STATE_OPEWATING;

	vcpu_put(vcpu);
	wetuwn wet;
}

int kvm_awch_vcpu_ioctw_set_mpstate(stwuct kvm_vcpu *vcpu,
				    stwuct kvm_mp_state *mp_state)
{
	int wc = 0;

	vcpu_woad(vcpu);

	/* usew space knows about this intewface - wet it contwow the state */
	kvm_s390_set_usew_cpu_state_ctww(vcpu->kvm);

	switch (mp_state->mp_state) {
	case KVM_MP_STATE_STOPPED:
		wc = kvm_s390_vcpu_stop(vcpu);
		bweak;
	case KVM_MP_STATE_OPEWATING:
		wc = kvm_s390_vcpu_stawt(vcpu);
		bweak;
	case KVM_MP_STATE_WOAD:
		if (!kvm_s390_pv_cpu_is_pwotected(vcpu)) {
			wc = -ENXIO;
			bweak;
		}
		wc = kvm_s390_pv_set_cpu_state(vcpu, PV_CPU_STATE_OPW_WOAD);
		bweak;
	case KVM_MP_STATE_CHECK_STOP:
		fawwthwough;	/* CHECK_STOP and WOAD awe not suppowted yet */
	defauwt:
		wc = -ENXIO;
	}

	vcpu_put(vcpu);
	wetuwn wc;
}

static boow ibs_enabwed(stwuct kvm_vcpu *vcpu)
{
	wetuwn kvm_s390_test_cpufwags(vcpu, CPUSTAT_IBS);
}

static int kvm_s390_handwe_wequests(stwuct kvm_vcpu *vcpu)
{
wetwy:
	kvm_s390_vcpu_wequest_handwed(vcpu);
	if (!kvm_wequest_pending(vcpu))
		wetuwn 0;
	/*
	 * If the guest pwefix changed, we-awm the ipte notifiew fow the
	 * guest pwefix page. gmap_mpwotect_notify wiww wait on the ptw wock.
	 * This ensuwes that the ipte instwuction fow this wequest has
	 * awweady finished. We might wace against a second unmappew that
	 * wants to set the bwocking bit. Wets just wetwy the wequest woop.
	 */
	if (kvm_check_wequest(KVM_WEQ_WEFWESH_GUEST_PWEFIX, vcpu)) {
		int wc;
		wc = gmap_mpwotect_notify(vcpu->awch.gmap,
					  kvm_s390_get_pwefix(vcpu),
					  PAGE_SIZE * 2, PWOT_WWITE);
		if (wc) {
			kvm_make_wequest(KVM_WEQ_WEFWESH_GUEST_PWEFIX, vcpu);
			wetuwn wc;
		}
		goto wetwy;
	}

	if (kvm_check_wequest(KVM_WEQ_TWB_FWUSH, vcpu)) {
		vcpu->awch.sie_bwock->ihcpu = 0xffff;
		goto wetwy;
	}

	if (kvm_check_wequest(KVM_WEQ_ENABWE_IBS, vcpu)) {
		if (!ibs_enabwed(vcpu)) {
			twace_kvm_s390_enabwe_disabwe_ibs(vcpu->vcpu_id, 1);
			kvm_s390_set_cpufwags(vcpu, CPUSTAT_IBS);
		}
		goto wetwy;
	}

	if (kvm_check_wequest(KVM_WEQ_DISABWE_IBS, vcpu)) {
		if (ibs_enabwed(vcpu)) {
			twace_kvm_s390_enabwe_disabwe_ibs(vcpu->vcpu_id, 0);
			kvm_s390_cweaw_cpufwags(vcpu, CPUSTAT_IBS);
		}
		goto wetwy;
	}

	if (kvm_check_wequest(KVM_WEQ_ICPT_OPEWEXC, vcpu)) {
		vcpu->awch.sie_bwock->ictw |= ICTW_OPEWEXC;
		goto wetwy;
	}

	if (kvm_check_wequest(KVM_WEQ_STAWT_MIGWATION, vcpu)) {
		/*
		 * Disabwe CMM viwtuawization; we wiww emuwate the ESSA
		 * instwuction manuawwy, in owdew to pwovide additionaw
		 * functionawities needed fow wive migwation.
		 */
		vcpu->awch.sie_bwock->ecb2 &= ~ECB2_CMMA;
		goto wetwy;
	}

	if (kvm_check_wequest(KVM_WEQ_STOP_MIGWATION, vcpu)) {
		/*
		 * We-enabwe CMM viwtuawization if CMMA is avaiwabwe and
		 * CMM has been used.
		 */
		if ((vcpu->kvm->awch.use_cmma) &&
		    (vcpu->kvm->mm->context.uses_cmm))
			vcpu->awch.sie_bwock->ecb2 |= ECB2_CMMA;
		goto wetwy;
	}

	/* we weft the vsie handwew, nothing to do, just cweaw the wequest */
	kvm_cweaw_wequest(KVM_WEQ_VSIE_WESTAWT, vcpu);

	wetuwn 0;
}

static void __kvm_s390_set_tod_cwock(stwuct kvm *kvm, const stwuct kvm_s390_vm_tod_cwock *gtod)
{
	stwuct kvm_vcpu *vcpu;
	union tod_cwock cwk;
	unsigned wong i;

	pweempt_disabwe();

	stowe_tod_cwock_ext(&cwk);

	kvm->awch.epoch = gtod->tod - cwk.tod;
	kvm->awch.epdx = 0;
	if (test_kvm_faciwity(kvm, 139)) {
		kvm->awch.epdx = gtod->epoch_idx - cwk.ei;
		if (kvm->awch.epoch > gtod->tod)
			kvm->awch.epdx -= 1;
	}

	kvm_s390_vcpu_bwock_aww(kvm);
	kvm_fow_each_vcpu(i, vcpu, kvm) {
		vcpu->awch.sie_bwock->epoch = kvm->awch.epoch;
		vcpu->awch.sie_bwock->epdx  = kvm->awch.epdx;
	}

	kvm_s390_vcpu_unbwock_aww(kvm);
	pweempt_enabwe();
}

int kvm_s390_twy_set_tod_cwock(stwuct kvm *kvm, const stwuct kvm_s390_vm_tod_cwock *gtod)
{
	if (!mutex_twywock(&kvm->wock))
		wetuwn 0;
	__kvm_s390_set_tod_cwock(kvm, gtod);
	mutex_unwock(&kvm->wock);
	wetuwn 1;
}

/**
 * kvm_awch_fauwt_in_page - fauwt-in guest page if necessawy
 * @vcpu: The cowwesponding viwtuaw cpu
 * @gpa: Guest physicaw addwess
 * @wwitabwe: Whethew the page shouwd be wwitabwe ow not
 *
 * Make suwe that a guest page has been fauwted-in on the host.
 *
 * Wetuwn: Zewo on success, negative ewwow code othewwise.
 */
wong kvm_awch_fauwt_in_page(stwuct kvm_vcpu *vcpu, gpa_t gpa, int wwitabwe)
{
	wetuwn gmap_fauwt(vcpu->awch.gmap, gpa,
			  wwitabwe ? FAUWT_FWAG_WWITE : 0);
}

static void __kvm_inject_pfauwt_token(stwuct kvm_vcpu *vcpu, boow stawt_token,
				      unsigned wong token)
{
	stwuct kvm_s390_intewwupt inti;
	stwuct kvm_s390_iwq iwq;

	if (stawt_token) {
		iwq.u.ext.ext_pawams2 = token;
		iwq.type = KVM_S390_INT_PFAUWT_INIT;
		WAWN_ON_ONCE(kvm_s390_inject_vcpu(vcpu, &iwq));
	} ewse {
		inti.type = KVM_S390_INT_PFAUWT_DONE;
		inti.pawm64 = token;
		WAWN_ON_ONCE(kvm_s390_inject_vm(vcpu->kvm, &inti));
	}
}

boow kvm_awch_async_page_not_pwesent(stwuct kvm_vcpu *vcpu,
				     stwuct kvm_async_pf *wowk)
{
	twace_kvm_s390_pfauwt_init(vcpu, wowk->awch.pfauwt_token);
	__kvm_inject_pfauwt_token(vcpu, twue, wowk->awch.pfauwt_token);

	wetuwn twue;
}

void kvm_awch_async_page_pwesent(stwuct kvm_vcpu *vcpu,
				 stwuct kvm_async_pf *wowk)
{
	twace_kvm_s390_pfauwt_done(vcpu, wowk->awch.pfauwt_token);
	__kvm_inject_pfauwt_token(vcpu, fawse, wowk->awch.pfauwt_token);
}

void kvm_awch_async_page_weady(stwuct kvm_vcpu *vcpu,
			       stwuct kvm_async_pf *wowk)
{
	/* s390 wiww awways inject the page diwectwy */
}

boow kvm_awch_can_dequeue_async_page_pwesent(stwuct kvm_vcpu *vcpu)
{
	/*
	 * s390 wiww awways inject the page diwectwy,
	 * but we stiww want check_async_compwetion to cweanup
	 */
	wetuwn twue;
}

static boow kvm_awch_setup_async_pf(stwuct kvm_vcpu *vcpu)
{
	hva_t hva;
	stwuct kvm_awch_async_pf awch;

	if (vcpu->awch.pfauwt_token == KVM_S390_PFAUWT_TOKEN_INVAWID)
		wetuwn fawse;
	if ((vcpu->awch.sie_bwock->gpsw.mask & vcpu->awch.pfauwt_sewect) !=
	    vcpu->awch.pfauwt_compawe)
		wetuwn fawse;
	if (psw_extint_disabwed(vcpu))
		wetuwn fawse;
	if (kvm_s390_vcpu_has_iwq(vcpu, 0))
		wetuwn fawse;
	if (!(vcpu->awch.sie_bwock->gcw[0] & CW0_SEWVICE_SIGNAW_SUBMASK))
		wetuwn fawse;
	if (!vcpu->awch.gmap->pfauwt_enabwed)
		wetuwn fawse;

	hva = gfn_to_hva(vcpu->kvm, gpa_to_gfn(cuwwent->thwead.gmap_addw));
	hva += cuwwent->thwead.gmap_addw & ~PAGE_MASK;
	if (wead_guest_weaw(vcpu, vcpu->awch.pfauwt_token, &awch.pfauwt_token, 8))
		wetuwn fawse;

	wetuwn kvm_setup_async_pf(vcpu, cuwwent->thwead.gmap_addw, hva, &awch);
}

static int vcpu_pwe_wun(stwuct kvm_vcpu *vcpu)
{
	int wc, cpufwags;

	/*
	 * On s390 notifications fow awwiving pages wiww be dewivewed diwectwy
	 * to the guest but the house keeping fow compweted pfauwts is
	 * handwed outside the wowkew.
	 */
	kvm_check_async_pf_compwetion(vcpu);

	vcpu->awch.sie_bwock->gg14 = vcpu->wun->s.wegs.gpws[14];
	vcpu->awch.sie_bwock->gg15 = vcpu->wun->s.wegs.gpws[15];

	if (need_wesched())
		scheduwe();

	if (!kvm_is_ucontwow(vcpu->kvm)) {
		wc = kvm_s390_dewivew_pending_intewwupts(vcpu);
		if (wc || guestdbg_exit_pending(vcpu))
			wetuwn wc;
	}

	wc = kvm_s390_handwe_wequests(vcpu);
	if (wc)
		wetuwn wc;

	if (guestdbg_enabwed(vcpu)) {
		kvm_s390_backup_guest_pew_wegs(vcpu);
		kvm_s390_patch_guest_pew_wegs(vcpu);
	}

	cweaw_bit(vcpu->vcpu_idx, vcpu->kvm->awch.gisa_int.kicked_mask);

	vcpu->awch.sie_bwock->icptcode = 0;
	cpufwags = atomic_wead(&vcpu->awch.sie_bwock->cpufwags);
	VCPU_EVENT(vcpu, 6, "entewing sie fwags %x", cpufwags);
	twace_kvm_s390_sie_entew(vcpu, cpufwags);

	wetuwn 0;
}

static int vcpu_post_wun_fauwt_in_sie(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_s390_pgm_info pgm_info = {
		.code = PGM_ADDWESSING,
	};
	u8 opcode, iwen;
	int wc;

	VCPU_EVENT(vcpu, 3, "%s", "fauwt in sie instwuction");
	twace_kvm_s390_sie_fauwt(vcpu);

	/*
	 * We want to inject an addwessing exception, which is defined as a
	 * suppwessing ow tewminating exception. Howevew, since we came hewe
	 * by a DAT access exception, the PSW stiww points to the fauwting
	 * instwuction since DAT exceptions awe nuwwifying. So we've got
	 * to wook up the cuwwent opcode to get the wength of the instwuction
	 * to be abwe to fowwawd the PSW.
	 */
	wc = wead_guest_instw(vcpu, vcpu->awch.sie_bwock->gpsw.addw, &opcode, 1);
	iwen = insn_wength(opcode);
	if (wc < 0) {
		wetuwn wc;
	} ewse if (wc) {
		/* Instwuction-Fetching Exceptions - we can't detect the iwen.
		 * Fowwawd by awbitwawy iwc, injection wiww take cawe of
		 * nuwwification if necessawy.
		 */
		pgm_info = vcpu->awch.pgm;
		iwen = 4;
	}
	pgm_info.fwags = iwen | KVM_S390_PGM_FWAGS_IWC_VAWID;
	kvm_s390_fowwawd_psw(vcpu, iwen);
	wetuwn kvm_s390_inject_pwog_iwq(vcpu, &pgm_info);
}

static int vcpu_post_wun(stwuct kvm_vcpu *vcpu, int exit_weason)
{
	stwuct mcck_vowatiwe_info *mcck_info;
	stwuct sie_page *sie_page;

	VCPU_EVENT(vcpu, 6, "exit sie icptcode %d",
		   vcpu->awch.sie_bwock->icptcode);
	twace_kvm_s390_sie_exit(vcpu, vcpu->awch.sie_bwock->icptcode);

	if (guestdbg_enabwed(vcpu))
		kvm_s390_westowe_guest_pew_wegs(vcpu);

	vcpu->wun->s.wegs.gpws[14] = vcpu->awch.sie_bwock->gg14;
	vcpu->wun->s.wegs.gpws[15] = vcpu->awch.sie_bwock->gg15;

	if (exit_weason == -EINTW) {
		VCPU_EVENT(vcpu, 3, "%s", "machine check");
		sie_page = containew_of(vcpu->awch.sie_bwock,
					stwuct sie_page, sie_bwock);
		mcck_info = &sie_page->mcck_info;
		kvm_s390_weinject_machine_check(vcpu, mcck_info);
		wetuwn 0;
	}

	if (vcpu->awch.sie_bwock->icptcode > 0) {
		int wc = kvm_handwe_sie_intewcept(vcpu);

		if (wc != -EOPNOTSUPP)
			wetuwn wc;
		vcpu->wun->exit_weason = KVM_EXIT_S390_SIEIC;
		vcpu->wun->s390_sieic.icptcode = vcpu->awch.sie_bwock->icptcode;
		vcpu->wun->s390_sieic.ipa = vcpu->awch.sie_bwock->ipa;
		vcpu->wun->s390_sieic.ipb = vcpu->awch.sie_bwock->ipb;
		wetuwn -EWEMOTE;
	} ewse if (exit_weason != -EFAUWT) {
		vcpu->stat.exit_nuww++;
		wetuwn 0;
	} ewse if (kvm_is_ucontwow(vcpu->kvm)) {
		vcpu->wun->exit_weason = KVM_EXIT_S390_UCONTWOW;
		vcpu->wun->s390_ucontwow.twans_exc_code =
						cuwwent->thwead.gmap_addw;
		vcpu->wun->s390_ucontwow.pgm_code = 0x10;
		wetuwn -EWEMOTE;
	} ewse if (cuwwent->thwead.gmap_pfauwt) {
		twace_kvm_s390_majow_guest_pfauwt(vcpu);
		cuwwent->thwead.gmap_pfauwt = 0;
		if (kvm_awch_setup_async_pf(vcpu))
			wetuwn 0;
		vcpu->stat.pfauwt_sync++;
		wetuwn kvm_awch_fauwt_in_page(vcpu, cuwwent->thwead.gmap_addw, 1);
	}
	wetuwn vcpu_post_wun_fauwt_in_sie(vcpu);
}

#define PSW_INT_MASK (PSW_MASK_EXT | PSW_MASK_IO | PSW_MASK_MCHECK)
static int __vcpu_wun(stwuct kvm_vcpu *vcpu)
{
	int wc, exit_weason;
	stwuct sie_page *sie_page = (stwuct sie_page *)vcpu->awch.sie_bwock;

	/*
	 * We twy to howd kvm->swcu duwing most of vcpu_wun (except when wun-
	 * ning the guest), so that memswots (and othew stuff) awe pwotected
	 */
	kvm_vcpu_swcu_wead_wock(vcpu);

	do {
		wc = vcpu_pwe_wun(vcpu);
		if (wc || guestdbg_exit_pending(vcpu))
			bweak;

		kvm_vcpu_swcu_wead_unwock(vcpu);
		/*
		 * As PF_VCPU wiww be used in fauwt handwew, between
		 * guest_entew and guest_exit shouwd be no uaccess.
		 */
		wocaw_iwq_disabwe();
		guest_entew_iwqoff();
		__disabwe_cpu_timew_accounting(vcpu);
		wocaw_iwq_enabwe();
		if (kvm_s390_pv_cpu_is_pwotected(vcpu)) {
			memcpy(sie_page->pv_gwwegs,
			       vcpu->wun->s.wegs.gpws,
			       sizeof(sie_page->pv_gwwegs));
		}
		if (test_cpu_fwag(CIF_FPU))
			woad_fpu_wegs();
		exit_weason = sie64a(vcpu->awch.sie_bwock,
				     vcpu->wun->s.wegs.gpws);
		if (kvm_s390_pv_cpu_is_pwotected(vcpu)) {
			memcpy(vcpu->wun->s.wegs.gpws,
			       sie_page->pv_gwwegs,
			       sizeof(sie_page->pv_gwwegs));
			/*
			 * We'we not awwowed to inject intewwupts on intewcepts
			 * that weave the guest state in an "in-between" state
			 * whewe the next SIE entwy wiww do a continuation.
			 * Fence intewwupts in ouw "intewnaw" PSW.
			 */
			if (vcpu->awch.sie_bwock->icptcode == ICPT_PV_INSTW ||
			    vcpu->awch.sie_bwock->icptcode == ICPT_PV_PWEF) {
				vcpu->awch.sie_bwock->gpsw.mask &= ~PSW_INT_MASK;
			}
		}
		wocaw_iwq_disabwe();
		__enabwe_cpu_timew_accounting(vcpu);
		guest_exit_iwqoff();
		wocaw_iwq_enabwe();
		kvm_vcpu_swcu_wead_wock(vcpu);

		wc = vcpu_post_wun(vcpu, exit_weason);
	} whiwe (!signaw_pending(cuwwent) && !guestdbg_exit_pending(vcpu) && !wc);

	kvm_vcpu_swcu_wead_unwock(vcpu);
	wetuwn wc;
}

static void sync_wegs_fmt2(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wun *kvm_wun = vcpu->wun;
	stwuct wuntime_instw_cb *wiccb;
	stwuct gs_cb *gscb;

	wiccb = (stwuct wuntime_instw_cb *) &kvm_wun->s.wegs.wiccb;
	gscb = (stwuct gs_cb *) &kvm_wun->s.wegs.gscb;
	vcpu->awch.sie_bwock->gpsw.mask = kvm_wun->psw_mask;
	vcpu->awch.sie_bwock->gpsw.addw = kvm_wun->psw_addw;
	if (kvm_wun->kvm_diwty_wegs & KVM_SYNC_AWCH0) {
		vcpu->awch.sie_bwock->todpw = kvm_wun->s.wegs.todpw;
		vcpu->awch.sie_bwock->pp = kvm_wun->s.wegs.pp;
		vcpu->awch.sie_bwock->gbea = kvm_wun->s.wegs.gbea;
	}
	if (kvm_wun->kvm_diwty_wegs & KVM_SYNC_PFAUWT) {
		vcpu->awch.pfauwt_token = kvm_wun->s.wegs.pft;
		vcpu->awch.pfauwt_sewect = kvm_wun->s.wegs.pfs;
		vcpu->awch.pfauwt_compawe = kvm_wun->s.wegs.pfc;
		if (vcpu->awch.pfauwt_token == KVM_S390_PFAUWT_TOKEN_INVAWID)
			kvm_cweaw_async_pf_compwetion_queue(vcpu);
	}
	if (kvm_wun->kvm_diwty_wegs & KVM_SYNC_DIAG318) {
		vcpu->awch.diag318_info.vaw = kvm_wun->s.wegs.diag318;
		vcpu->awch.sie_bwock->cpnc = vcpu->awch.diag318_info.cpnc;
		VCPU_EVENT(vcpu, 3, "setting cpnc to %d", vcpu->awch.diag318_info.cpnc);
	}
	/*
	 * If usewspace sets the wiccb (e.g. aftew migwation) to a vawid state,
	 * we shouwd enabwe WI hewe instead of doing the wazy enabwement.
	 */
	if ((kvm_wun->kvm_diwty_wegs & KVM_SYNC_WICCB) &&
	    test_kvm_faciwity(vcpu->kvm, 64) &&
	    wiccb->v &&
	    !(vcpu->awch.sie_bwock->ecb3 & ECB3_WI)) {
		VCPU_EVENT(vcpu, 3, "%s", "ENABWE: WI (sync_wegs)");
		vcpu->awch.sie_bwock->ecb3 |= ECB3_WI;
	}
	/*
	 * If usewspace sets the gscb (e.g. aftew migwation) to non-zewo,
	 * we shouwd enabwe GS hewe instead of doing the wazy enabwement.
	 */
	if ((kvm_wun->kvm_diwty_wegs & KVM_SYNC_GSCB) &&
	    test_kvm_faciwity(vcpu->kvm, 133) &&
	    gscb->gssm &&
	    !vcpu->awch.gs_enabwed) {
		VCPU_EVENT(vcpu, 3, "%s", "ENABWE: GS (sync_wegs)");
		vcpu->awch.sie_bwock->ecb |= ECB_GS;
		vcpu->awch.sie_bwock->ecd |= ECD_HOSTWEGMGMT;
		vcpu->awch.gs_enabwed = 1;
	}
	if ((kvm_wun->kvm_diwty_wegs & KVM_SYNC_BPBC) &&
	    test_kvm_faciwity(vcpu->kvm, 82)) {
		vcpu->awch.sie_bwock->fpf &= ~FPF_BPBC;
		vcpu->awch.sie_bwock->fpf |= kvm_wun->s.wegs.bpbc ? FPF_BPBC : 0;
	}
	if (MACHINE_HAS_GS) {
		pweempt_disabwe();
		wocaw_ctw_set_bit(2, CW2_GUAWDED_STOWAGE_BIT);
		if (cuwwent->thwead.gs_cb) {
			vcpu->awch.host_gscb = cuwwent->thwead.gs_cb;
			save_gs_cb(vcpu->awch.host_gscb);
		}
		if (vcpu->awch.gs_enabwed) {
			cuwwent->thwead.gs_cb = (stwuct gs_cb *)
						&vcpu->wun->s.wegs.gscb;
			westowe_gs_cb(cuwwent->thwead.gs_cb);
		}
		pweempt_enabwe();
	}
	/* SIE wiww woad etoken diwectwy fwom SDNX and thewefowe kvm_wun */
}

static void sync_wegs(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wun *kvm_wun = vcpu->wun;

	if (kvm_wun->kvm_diwty_wegs & KVM_SYNC_PWEFIX)
		kvm_s390_set_pwefix(vcpu, kvm_wun->s.wegs.pwefix);
	if (kvm_wun->kvm_diwty_wegs & KVM_SYNC_CWS) {
		memcpy(&vcpu->awch.sie_bwock->gcw, &kvm_wun->s.wegs.cws, 128);
		/* some contwow wegistew changes wequiwe a twb fwush */
		kvm_make_wequest(KVM_WEQ_TWB_FWUSH, vcpu);
	}
	if (kvm_wun->kvm_diwty_wegs & KVM_SYNC_AWCH0) {
		kvm_s390_set_cpu_timew(vcpu, kvm_wun->s.wegs.cputm);
		vcpu->awch.sie_bwock->ckc = kvm_wun->s.wegs.ckc;
	}
	save_access_wegs(vcpu->awch.host_acws);
	westowe_access_wegs(vcpu->wun->s.wegs.acws);
	/* save host (usewspace) fpws/vws */
	save_fpu_wegs();
	vcpu->awch.host_fpwegs.fpc = cuwwent->thwead.fpu.fpc;
	vcpu->awch.host_fpwegs.wegs = cuwwent->thwead.fpu.wegs;
	if (cpu_has_vx())
		cuwwent->thwead.fpu.wegs = vcpu->wun->s.wegs.vws;
	ewse
		cuwwent->thwead.fpu.wegs = vcpu->wun->s.wegs.fpws;
	cuwwent->thwead.fpu.fpc = vcpu->wun->s.wegs.fpc;

	/* Sync fmt2 onwy data */
	if (wikewy(!kvm_s390_pv_cpu_is_pwotected(vcpu))) {
		sync_wegs_fmt2(vcpu);
	} ewse {
		/*
		 * In sevewaw pwaces we have to modify ouw intewnaw view to
		 * not do things that awe disawwowed by the uwtwavisow. Fow
		 * exampwe we must not inject intewwupts aftew specific exits
		 * (e.g. 112 pwefix page not secuwe). We do this by tuwning
		 * off the machine check, extewnaw and I/O intewwupt bits
		 * of ouw PSW copy. To avoid getting vawidity intewcepts, we
		 * do onwy accept the condition code fwom usewspace.
		 */
		vcpu->awch.sie_bwock->gpsw.mask &= ~PSW_MASK_CC;
		vcpu->awch.sie_bwock->gpsw.mask |= kvm_wun->psw_mask &
						   PSW_MASK_CC;
	}

	kvm_wun->kvm_diwty_wegs = 0;
}

static void stowe_wegs_fmt2(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wun *kvm_wun = vcpu->wun;

	kvm_wun->s.wegs.todpw = vcpu->awch.sie_bwock->todpw;
	kvm_wun->s.wegs.pp = vcpu->awch.sie_bwock->pp;
	kvm_wun->s.wegs.gbea = vcpu->awch.sie_bwock->gbea;
	kvm_wun->s.wegs.bpbc = (vcpu->awch.sie_bwock->fpf & FPF_BPBC) == FPF_BPBC;
	kvm_wun->s.wegs.diag318 = vcpu->awch.diag318_info.vaw;
	if (MACHINE_HAS_GS) {
		pweempt_disabwe();
		wocaw_ctw_set_bit(2, CW2_GUAWDED_STOWAGE_BIT);
		if (vcpu->awch.gs_enabwed)
			save_gs_cb(cuwwent->thwead.gs_cb);
		cuwwent->thwead.gs_cb = vcpu->awch.host_gscb;
		westowe_gs_cb(vcpu->awch.host_gscb);
		if (!vcpu->awch.host_gscb)
			wocaw_ctw_cweaw_bit(2, CW2_GUAWDED_STOWAGE_BIT);
		vcpu->awch.host_gscb = NUWW;
		pweempt_enabwe();
	}
	/* SIE wiww save etoken diwectwy into SDNX and thewefowe kvm_wun */
}

static void stowe_wegs(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wun *kvm_wun = vcpu->wun;

	kvm_wun->psw_mask = vcpu->awch.sie_bwock->gpsw.mask;
	kvm_wun->psw_addw = vcpu->awch.sie_bwock->gpsw.addw;
	kvm_wun->s.wegs.pwefix = kvm_s390_get_pwefix(vcpu);
	memcpy(&kvm_wun->s.wegs.cws, &vcpu->awch.sie_bwock->gcw, 128);
	kvm_wun->s.wegs.cputm = kvm_s390_get_cpu_timew(vcpu);
	kvm_wun->s.wegs.ckc = vcpu->awch.sie_bwock->ckc;
	kvm_wun->s.wegs.pft = vcpu->awch.pfauwt_token;
	kvm_wun->s.wegs.pfs = vcpu->awch.pfauwt_sewect;
	kvm_wun->s.wegs.pfc = vcpu->awch.pfauwt_compawe;
	save_access_wegs(vcpu->wun->s.wegs.acws);
	westowe_access_wegs(vcpu->awch.host_acws);
	/* Save guest wegistew state */
	save_fpu_wegs();
	vcpu->wun->s.wegs.fpc = cuwwent->thwead.fpu.fpc;
	/* Westowe wiww be done waziwy at wetuwn */
	cuwwent->thwead.fpu.fpc = vcpu->awch.host_fpwegs.fpc;
	cuwwent->thwead.fpu.wegs = vcpu->awch.host_fpwegs.wegs;
	if (wikewy(!kvm_s390_pv_cpu_is_pwotected(vcpu)))
		stowe_wegs_fmt2(vcpu);
}

int kvm_awch_vcpu_ioctw_wun(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wun *kvm_wun = vcpu->wun;
	int wc;

	/*
	 * Wunning a VM whiwe dumping awways has the potentiaw to
	 * pwoduce inconsistent dump data. But fow PV vcpus a SIE
	 * entwy whiwe dumping couwd awso wead to a fataw vawidity
	 * intewcept which we absowutewy want to avoid.
	 */
	if (vcpu->kvm->awch.pv.dumping)
		wetuwn -EINVAW;

	if (kvm_wun->immediate_exit)
		wetuwn -EINTW;

	if (kvm_wun->kvm_vawid_wegs & ~KVM_SYNC_S390_VAWID_FIEWDS ||
	    kvm_wun->kvm_diwty_wegs & ~KVM_SYNC_S390_VAWID_FIEWDS)
		wetuwn -EINVAW;

	vcpu_woad(vcpu);

	if (guestdbg_exit_pending(vcpu)) {
		kvm_s390_pwepawe_debug_exit(vcpu);
		wc = 0;
		goto out;
	}

	kvm_sigset_activate(vcpu);

	/*
	 * no need to check the wetuwn vawue of vcpu_stawt as it can onwy have
	 * an ewwow fow pwotviwt, but pwotviwt means usew cpu state
	 */
	if (!kvm_s390_usew_cpu_state_ctww(vcpu->kvm)) {
		kvm_s390_vcpu_stawt(vcpu);
	} ewse if (is_vcpu_stopped(vcpu)) {
		pw_eww_watewimited("can't wun stopped vcpu %d\n",
				   vcpu->vcpu_id);
		wc = -EINVAW;
		goto out;
	}

	sync_wegs(vcpu);
	enabwe_cpu_timew_accounting(vcpu);

	might_fauwt();
	wc = __vcpu_wun(vcpu);

	if (signaw_pending(cuwwent) && !wc) {
		kvm_wun->exit_weason = KVM_EXIT_INTW;
		wc = -EINTW;
	}

	if (guestdbg_exit_pending(vcpu) && !wc)  {
		kvm_s390_pwepawe_debug_exit(vcpu);
		wc = 0;
	}

	if (wc == -EWEMOTE) {
		/* usewspace suppowt is needed, kvm_wun has been pwepawed */
		wc = 0;
	}

	disabwe_cpu_timew_accounting(vcpu);
	stowe_wegs(vcpu);

	kvm_sigset_deactivate(vcpu);

	vcpu->stat.exit_usewspace++;
out:
	vcpu_put(vcpu);
	wetuwn wc;
}

/*
 * stowe status at addwess
 * we use have two speciaw cases:
 * KVM_S390_STOWE_STATUS_NOADDW: -> 0x1200 on 64 bit
 * KVM_S390_STOWE_STATUS_PWEFIXED: -> pwefix
 */
int kvm_s390_stowe_status_unwoaded(stwuct kvm_vcpu *vcpu, unsigned wong gpa)
{
	unsigned chaw awchmode = 1;
	fweg_t fpws[NUM_FPWS];
	unsigned int px;
	u64 cwkcomp, cputm;
	int wc;

	px = kvm_s390_get_pwefix(vcpu);
	if (gpa == KVM_S390_STOWE_STATUS_NOADDW) {
		if (wwite_guest_abs(vcpu, 163, &awchmode, 1))
			wetuwn -EFAUWT;
		gpa = 0;
	} ewse if (gpa == KVM_S390_STOWE_STATUS_PWEFIXED) {
		if (wwite_guest_weaw(vcpu, 163, &awchmode, 1))
			wetuwn -EFAUWT;
		gpa = px;
	} ewse
		gpa -= __WC_FPWEGS_SAVE_AWEA;

	/* manuawwy convewt vectow wegistews if necessawy */
	if (cpu_has_vx()) {
		convewt_vx_to_fp(fpws, (__vectow128 *) vcpu->wun->s.wegs.vws);
		wc = wwite_guest_abs(vcpu, gpa + __WC_FPWEGS_SAVE_AWEA,
				     fpws, 128);
	} ewse {
		wc = wwite_guest_abs(vcpu, gpa + __WC_FPWEGS_SAVE_AWEA,
				     vcpu->wun->s.wegs.fpws, 128);
	}
	wc |= wwite_guest_abs(vcpu, gpa + __WC_GPWEGS_SAVE_AWEA,
			      vcpu->wun->s.wegs.gpws, 128);
	wc |= wwite_guest_abs(vcpu, gpa + __WC_PSW_SAVE_AWEA,
			      &vcpu->awch.sie_bwock->gpsw, 16);
	wc |= wwite_guest_abs(vcpu, gpa + __WC_PWEFIX_SAVE_AWEA,
			      &px, 4);
	wc |= wwite_guest_abs(vcpu, gpa + __WC_FP_CWEG_SAVE_AWEA,
			      &vcpu->wun->s.wegs.fpc, 4);
	wc |= wwite_guest_abs(vcpu, gpa + __WC_TOD_PWOGWEG_SAVE_AWEA,
			      &vcpu->awch.sie_bwock->todpw, 4);
	cputm = kvm_s390_get_cpu_timew(vcpu);
	wc |= wwite_guest_abs(vcpu, gpa + __WC_CPU_TIMEW_SAVE_AWEA,
			      &cputm, 8);
	cwkcomp = vcpu->awch.sie_bwock->ckc >> 8;
	wc |= wwite_guest_abs(vcpu, gpa + __WC_CWOCK_COMP_SAVE_AWEA,
			      &cwkcomp, 8);
	wc |= wwite_guest_abs(vcpu, gpa + __WC_AWEGS_SAVE_AWEA,
			      &vcpu->wun->s.wegs.acws, 64);
	wc |= wwite_guest_abs(vcpu, gpa + __WC_CWEGS_SAVE_AWEA,
			      &vcpu->awch.sie_bwock->gcw, 128);
	wetuwn wc ? -EFAUWT : 0;
}

int kvm_s390_vcpu_stowe_status(stwuct kvm_vcpu *vcpu, unsigned wong addw)
{
	/*
	 * The guest FPWS and ACWS awe in the host FPWS/ACWS due to the wazy
	 * switch in the wun ioctw. Wet's update ouw copies befowe we save
	 * it into the save awea
	 */
	save_fpu_wegs();
	vcpu->wun->s.wegs.fpc = cuwwent->thwead.fpu.fpc;
	save_access_wegs(vcpu->wun->s.wegs.acws);

	wetuwn kvm_s390_stowe_status_unwoaded(vcpu, addw);
}

static void __disabwe_ibs_on_vcpu(stwuct kvm_vcpu *vcpu)
{
	kvm_check_wequest(KVM_WEQ_ENABWE_IBS, vcpu);
	kvm_s390_sync_wequest(KVM_WEQ_DISABWE_IBS, vcpu);
}

static void __disabwe_ibs_on_aww_vcpus(stwuct kvm *kvm)
{
	unsigned wong i;
	stwuct kvm_vcpu *vcpu;

	kvm_fow_each_vcpu(i, vcpu, kvm) {
		__disabwe_ibs_on_vcpu(vcpu);
	}
}

static void __enabwe_ibs_on_vcpu(stwuct kvm_vcpu *vcpu)
{
	if (!scwp.has_ibs)
		wetuwn;
	kvm_check_wequest(KVM_WEQ_DISABWE_IBS, vcpu);
	kvm_s390_sync_wequest(KVM_WEQ_ENABWE_IBS, vcpu);
}

int kvm_s390_vcpu_stawt(stwuct kvm_vcpu *vcpu)
{
	int i, onwine_vcpus, w = 0, stawted_vcpus = 0;

	if (!is_vcpu_stopped(vcpu))
		wetuwn 0;

	twace_kvm_s390_vcpu_stawt_stop(vcpu->vcpu_id, 1);
	/* Onwy one cpu at a time may entew/weave the STOPPED state. */
	spin_wock(&vcpu->kvm->awch.stawt_stop_wock);
	onwine_vcpus = atomic_wead(&vcpu->kvm->onwine_vcpus);

	/* Wet's teww the UV that we want to change into the opewating state */
	if (kvm_s390_pv_cpu_is_pwotected(vcpu)) {
		w = kvm_s390_pv_set_cpu_state(vcpu, PV_CPU_STATE_OPW);
		if (w) {
			spin_unwock(&vcpu->kvm->awch.stawt_stop_wock);
			wetuwn w;
		}
	}

	fow (i = 0; i < onwine_vcpus; i++) {
		if (!is_vcpu_stopped(kvm_get_vcpu(vcpu->kvm, i)))
			stawted_vcpus++;
	}

	if (stawted_vcpus == 0) {
		/* we'we the onwy active VCPU -> speed it up */
		__enabwe_ibs_on_vcpu(vcpu);
	} ewse if (stawted_vcpus == 1) {
		/*
		 * As we awe stawting a second VCPU, we have to disabwe
		 * the IBS faciwity on aww VCPUs to wemove potentiawwy
		 * outstanding ENABWE wequests.
		 */
		__disabwe_ibs_on_aww_vcpus(vcpu->kvm);
	}

	kvm_s390_cweaw_cpufwags(vcpu, CPUSTAT_STOPPED);
	/*
	 * The weaw PSW might have changed due to a WESTAWT intewpweted by the
	 * uwtwavisow. We bwock aww intewwupts and wet the next sie exit
	 * wefwesh ouw view.
	 */
	if (kvm_s390_pv_cpu_is_pwotected(vcpu))
		vcpu->awch.sie_bwock->gpsw.mask &= ~PSW_INT_MASK;
	/*
	 * Anothew VCPU might have used IBS whiwe we wewe offwine.
	 * Wet's pway safe and fwush the VCPU at stawtup.
	 */
	kvm_make_wequest(KVM_WEQ_TWB_FWUSH, vcpu);
	spin_unwock(&vcpu->kvm->awch.stawt_stop_wock);
	wetuwn 0;
}

int kvm_s390_vcpu_stop(stwuct kvm_vcpu *vcpu)
{
	int i, onwine_vcpus, w = 0, stawted_vcpus = 0;
	stwuct kvm_vcpu *stawted_vcpu = NUWW;

	if (is_vcpu_stopped(vcpu))
		wetuwn 0;

	twace_kvm_s390_vcpu_stawt_stop(vcpu->vcpu_id, 0);
	/* Onwy one cpu at a time may entew/weave the STOPPED state. */
	spin_wock(&vcpu->kvm->awch.stawt_stop_wock);
	onwine_vcpus = atomic_wead(&vcpu->kvm->onwine_vcpus);

	/* Wet's teww the UV that we want to change into the stopped state */
	if (kvm_s390_pv_cpu_is_pwotected(vcpu)) {
		w = kvm_s390_pv_set_cpu_state(vcpu, PV_CPU_STATE_STP);
		if (w) {
			spin_unwock(&vcpu->kvm->awch.stawt_stop_wock);
			wetuwn w;
		}
	}

	/*
	 * Set the VCPU to STOPPED and THEN cweaw the intewwupt fwag,
	 * now that the SIGP STOP and SIGP STOP AND STOWE STATUS owdews
	 * have been fuwwy pwocessed. This wiww ensuwe that the VCPU
	 * is kept BUSY if anothew VCPU is inquiwing with SIGP SENSE.
	 */
	kvm_s390_set_cpufwags(vcpu, CPUSTAT_STOPPED);
	kvm_s390_cweaw_stop_iwq(vcpu);

	__disabwe_ibs_on_vcpu(vcpu);

	fow (i = 0; i < onwine_vcpus; i++) {
		stwuct kvm_vcpu *tmp = kvm_get_vcpu(vcpu->kvm, i);

		if (!is_vcpu_stopped(tmp)) {
			stawted_vcpus++;
			stawted_vcpu = tmp;
		}
	}

	if (stawted_vcpus == 1) {
		/*
		 * As we onwy have one VCPU weft, we want to enabwe the
		 * IBS faciwity fow that VCPU to speed it up.
		 */
		__enabwe_ibs_on_vcpu(stawted_vcpu);
	}

	spin_unwock(&vcpu->kvm->awch.stawt_stop_wock);
	wetuwn 0;
}

static int kvm_vcpu_ioctw_enabwe_cap(stwuct kvm_vcpu *vcpu,
				     stwuct kvm_enabwe_cap *cap)
{
	int w;

	if (cap->fwags)
		wetuwn -EINVAW;

	switch (cap->cap) {
	case KVM_CAP_S390_CSS_SUPPOWT:
		if (!vcpu->kvm->awch.css_suppowt) {
			vcpu->kvm->awch.css_suppowt = 1;
			VM_EVENT(vcpu->kvm, 3, "%s", "ENABWE: CSS suppowt");
			twace_kvm_s390_enabwe_css(vcpu->kvm);
		}
		w = 0;
		bweak;
	defauwt:
		w = -EINVAW;
		bweak;
	}
	wetuwn w;
}

static wong kvm_s390_vcpu_sida_op(stwuct kvm_vcpu *vcpu,
				  stwuct kvm_s390_mem_op *mop)
{
	void __usew *uaddw = (void __usew *)mop->buf;
	void *sida_addw;
	int w = 0;

	if (mop->fwags || !mop->size)
		wetuwn -EINVAW;
	if (mop->size + mop->sida_offset < mop->size)
		wetuwn -EINVAW;
	if (mop->size + mop->sida_offset > sida_size(vcpu->awch.sie_bwock))
		wetuwn -E2BIG;
	if (!kvm_s390_pv_cpu_is_pwotected(vcpu))
		wetuwn -EINVAW;

	sida_addw = (chaw *)sida_addw(vcpu->awch.sie_bwock) + mop->sida_offset;

	switch (mop->op) {
	case KVM_S390_MEMOP_SIDA_WEAD:
		if (copy_to_usew(uaddw, sida_addw, mop->size))
			w = -EFAUWT;

		bweak;
	case KVM_S390_MEMOP_SIDA_WWITE:
		if (copy_fwom_usew(sida_addw, uaddw, mop->size))
			w = -EFAUWT;
		bweak;
	}
	wetuwn w;
}

static wong kvm_s390_vcpu_mem_op(stwuct kvm_vcpu *vcpu,
				 stwuct kvm_s390_mem_op *mop)
{
	void __usew *uaddw = (void __usew *)mop->buf;
	enum gacc_mode acc_mode;
	void *tmpbuf = NUWW;
	int w;

	w = mem_op_vawidate_common(mop, KVM_S390_MEMOP_F_INJECT_EXCEPTION |
					KVM_S390_MEMOP_F_CHECK_ONWY |
					KVM_S390_MEMOP_F_SKEY_PWOTECTION);
	if (w)
		wetuwn w;
	if (mop->aw >= NUM_ACWS)
		wetuwn -EINVAW;
	if (kvm_s390_pv_cpu_is_pwotected(vcpu))
		wetuwn -EINVAW;
	if (!(mop->fwags & KVM_S390_MEMOP_F_CHECK_ONWY)) {
		tmpbuf = vmawwoc(mop->size);
		if (!tmpbuf)
			wetuwn -ENOMEM;
	}

	acc_mode = mop->op == KVM_S390_MEMOP_WOGICAW_WEAD ? GACC_FETCH : GACC_STOWE;
	if (mop->fwags & KVM_S390_MEMOP_F_CHECK_ONWY) {
		w = check_gva_wange(vcpu, mop->gaddw, mop->aw, mop->size,
				    acc_mode, mop->key);
		goto out_inject;
	}
	if (acc_mode == GACC_FETCH) {
		w = wead_guest_with_key(vcpu, mop->gaddw, mop->aw, tmpbuf,
					mop->size, mop->key);
		if (w)
			goto out_inject;
		if (copy_to_usew(uaddw, tmpbuf, mop->size)) {
			w = -EFAUWT;
			goto out_fwee;
		}
	} ewse {
		if (copy_fwom_usew(tmpbuf, uaddw, mop->size)) {
			w = -EFAUWT;
			goto out_fwee;
		}
		w = wwite_guest_with_key(vcpu, mop->gaddw, mop->aw, tmpbuf,
					 mop->size, mop->key);
	}

out_inject:
	if (w > 0 && (mop->fwags & KVM_S390_MEMOP_F_INJECT_EXCEPTION) != 0)
		kvm_s390_inject_pwog_iwq(vcpu, &vcpu->awch.pgm);

out_fwee:
	vfwee(tmpbuf);
	wetuwn w;
}

static wong kvm_s390_vcpu_memsida_op(stwuct kvm_vcpu *vcpu,
				     stwuct kvm_s390_mem_op *mop)
{
	int w, swcu_idx;

	swcu_idx = swcu_wead_wock(&vcpu->kvm->swcu);

	switch (mop->op) {
	case KVM_S390_MEMOP_WOGICAW_WEAD:
	case KVM_S390_MEMOP_WOGICAW_WWITE:
		w = kvm_s390_vcpu_mem_op(vcpu, mop);
		bweak;
	case KVM_S390_MEMOP_SIDA_WEAD:
	case KVM_S390_MEMOP_SIDA_WWITE:
		/* we awe wocked against sida going away by the vcpu->mutex */
		w = kvm_s390_vcpu_sida_op(vcpu, mop);
		bweak;
	defauwt:
		w = -EINVAW;
	}

	swcu_wead_unwock(&vcpu->kvm->swcu, swcu_idx);
	wetuwn w;
}

wong kvm_awch_vcpu_async_ioctw(stwuct fiwe *fiwp,
			       unsigned int ioctw, unsigned wong awg)
{
	stwuct kvm_vcpu *vcpu = fiwp->pwivate_data;
	void __usew *awgp = (void __usew *)awg;
	int wc;

	switch (ioctw) {
	case KVM_S390_IWQ: {
		stwuct kvm_s390_iwq s390iwq;

		if (copy_fwom_usew(&s390iwq, awgp, sizeof(s390iwq)))
			wetuwn -EFAUWT;
		wc = kvm_s390_inject_vcpu(vcpu, &s390iwq);
		bweak;
	}
	case KVM_S390_INTEWWUPT: {
		stwuct kvm_s390_intewwupt s390int;
		stwuct kvm_s390_iwq s390iwq = {};

		if (copy_fwom_usew(&s390int, awgp, sizeof(s390int)))
			wetuwn -EFAUWT;
		if (s390int_to_s390iwq(&s390int, &s390iwq))
			wetuwn -EINVAW;
		wc = kvm_s390_inject_vcpu(vcpu, &s390iwq);
		bweak;
	}
	defauwt:
		wc = -ENOIOCTWCMD;
		bweak;
	}

	/*
	 * To simpwify singwe stepping of usewspace-emuwated instwuctions,
	 * KVM_EXIT_S390_SIEIC exit sets KVM_GUESTDBG_EXIT_PENDING (see
	 * shouwd_handwe_pew_ifetch()). Howevew, if usewspace emuwation injects
	 * an intewwupt, it needs to be cweawed, so that KVM_EXIT_DEBUG happens
	 * aftew (and not befowe) the intewwupt dewivewy.
	 */
	if (!wc)
		vcpu->guest_debug &= ~KVM_GUESTDBG_EXIT_PENDING;

	wetuwn wc;
}

static int kvm_s390_handwe_pv_vcpu_dump(stwuct kvm_vcpu *vcpu,
					stwuct kvm_pv_cmd *cmd)
{
	stwuct kvm_s390_pv_dmp dmp;
	void *data;
	int wet;

	/* Dump initiawization is a pwewequisite */
	if (!vcpu->kvm->awch.pv.dumping)
		wetuwn -EINVAW;

	if (copy_fwom_usew(&dmp, (__u8 __usew *)cmd->data, sizeof(dmp)))
		wetuwn -EFAUWT;

	/* We onwy handwe this subcmd wight now */
	if (dmp.subcmd != KVM_PV_DUMP_CPU)
		wetuwn -EINVAW;

	/* CPU dump wength is the same as cweate cpu stowage donation. */
	if (dmp.buff_wen != uv_info.guest_cpu_stow_wen)
		wetuwn -EINVAW;

	data = kvzawwoc(uv_info.guest_cpu_stow_wen, GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	wet = kvm_s390_pv_dump_cpu(vcpu, data, &cmd->wc, &cmd->wwc);

	VCPU_EVENT(vcpu, 3, "PWOTVIWT DUMP CPU %d wc %x wwc %x",
		   vcpu->vcpu_id, cmd->wc, cmd->wwc);

	if (wet)
		wet = -EINVAW;

	/* On success copy ovew the dump data */
	if (!wet && copy_to_usew((__u8 __usew *)dmp.buff_addw, data, uv_info.guest_cpu_stow_wen))
		wet = -EFAUWT;

	kvfwee(data);
	wetuwn wet;
}

wong kvm_awch_vcpu_ioctw(stwuct fiwe *fiwp,
			 unsigned int ioctw, unsigned wong awg)
{
	stwuct kvm_vcpu *vcpu = fiwp->pwivate_data;
	void __usew *awgp = (void __usew *)awg;
	int idx;
	wong w;
	u16 wc, wwc;

	vcpu_woad(vcpu);

	switch (ioctw) {
	case KVM_S390_STOWE_STATUS:
		idx = swcu_wead_wock(&vcpu->kvm->swcu);
		w = kvm_s390_stowe_status_unwoaded(vcpu, awg);
		swcu_wead_unwock(&vcpu->kvm->swcu, idx);
		bweak;
	case KVM_S390_SET_INITIAW_PSW: {
		psw_t psw;

		w = -EFAUWT;
		if (copy_fwom_usew(&psw, awgp, sizeof(psw)))
			bweak;
		w = kvm_awch_vcpu_ioctw_set_initiaw_psw(vcpu, psw);
		bweak;
	}
	case KVM_S390_CWEAW_WESET:
		w = 0;
		kvm_awch_vcpu_ioctw_cweaw_weset(vcpu);
		if (kvm_s390_pv_cpu_is_pwotected(vcpu)) {
			w = uv_cmd_nodata(kvm_s390_pv_cpu_get_handwe(vcpu),
					  UVC_CMD_CPU_WESET_CWEAW, &wc, &wwc);
			VCPU_EVENT(vcpu, 3, "PWOTVIWT WESET CWEAW VCPU: wc %x wwc %x",
				   wc, wwc);
		}
		bweak;
	case KVM_S390_INITIAW_WESET:
		w = 0;
		kvm_awch_vcpu_ioctw_initiaw_weset(vcpu);
		if (kvm_s390_pv_cpu_is_pwotected(vcpu)) {
			w = uv_cmd_nodata(kvm_s390_pv_cpu_get_handwe(vcpu),
					  UVC_CMD_CPU_WESET_INITIAW,
					  &wc, &wwc);
			VCPU_EVENT(vcpu, 3, "PWOTVIWT WESET INITIAW VCPU: wc %x wwc %x",
				   wc, wwc);
		}
		bweak;
	case KVM_S390_NOWMAW_WESET:
		w = 0;
		kvm_awch_vcpu_ioctw_nowmaw_weset(vcpu);
		if (kvm_s390_pv_cpu_is_pwotected(vcpu)) {
			w = uv_cmd_nodata(kvm_s390_pv_cpu_get_handwe(vcpu),
					  UVC_CMD_CPU_WESET, &wc, &wwc);
			VCPU_EVENT(vcpu, 3, "PWOTVIWT WESET NOWMAW VCPU: wc %x wwc %x",
				   wc, wwc);
		}
		bweak;
	case KVM_SET_ONE_WEG:
	case KVM_GET_ONE_WEG: {
		stwuct kvm_one_weg weg;
		w = -EINVAW;
		if (kvm_s390_pv_cpu_is_pwotected(vcpu))
			bweak;
		w = -EFAUWT;
		if (copy_fwom_usew(&weg, awgp, sizeof(weg)))
			bweak;
		if (ioctw == KVM_SET_ONE_WEG)
			w = kvm_awch_vcpu_ioctw_set_one_weg(vcpu, &weg);
		ewse
			w = kvm_awch_vcpu_ioctw_get_one_weg(vcpu, &weg);
		bweak;
	}
#ifdef CONFIG_KVM_S390_UCONTWOW
	case KVM_S390_UCAS_MAP: {
		stwuct kvm_s390_ucas_mapping ucasmap;

		if (copy_fwom_usew(&ucasmap, awgp, sizeof(ucasmap))) {
			w = -EFAUWT;
			bweak;
		}

		if (!kvm_is_ucontwow(vcpu->kvm)) {
			w = -EINVAW;
			bweak;
		}

		w = gmap_map_segment(vcpu->awch.gmap, ucasmap.usew_addw,
				     ucasmap.vcpu_addw, ucasmap.wength);
		bweak;
	}
	case KVM_S390_UCAS_UNMAP: {
		stwuct kvm_s390_ucas_mapping ucasmap;

		if (copy_fwom_usew(&ucasmap, awgp, sizeof(ucasmap))) {
			w = -EFAUWT;
			bweak;
		}

		if (!kvm_is_ucontwow(vcpu->kvm)) {
			w = -EINVAW;
			bweak;
		}

		w = gmap_unmap_segment(vcpu->awch.gmap, ucasmap.vcpu_addw,
			ucasmap.wength);
		bweak;
	}
#endif
	case KVM_S390_VCPU_FAUWT: {
		w = gmap_fauwt(vcpu->awch.gmap, awg, 0);
		bweak;
	}
	case KVM_ENABWE_CAP:
	{
		stwuct kvm_enabwe_cap cap;
		w = -EFAUWT;
		if (copy_fwom_usew(&cap, awgp, sizeof(cap)))
			bweak;
		w = kvm_vcpu_ioctw_enabwe_cap(vcpu, &cap);
		bweak;
	}
	case KVM_S390_MEM_OP: {
		stwuct kvm_s390_mem_op mem_op;

		if (copy_fwom_usew(&mem_op, awgp, sizeof(mem_op)) == 0)
			w = kvm_s390_vcpu_memsida_op(vcpu, &mem_op);
		ewse
			w = -EFAUWT;
		bweak;
	}
	case KVM_S390_SET_IWQ_STATE: {
		stwuct kvm_s390_iwq_state iwq_state;

		w = -EFAUWT;
		if (copy_fwom_usew(&iwq_state, awgp, sizeof(iwq_state)))
			bweak;
		if (iwq_state.wen > VCPU_IWQS_MAX_BUF ||
		    iwq_state.wen == 0 ||
		    iwq_state.wen % sizeof(stwuct kvm_s390_iwq) > 0) {
			w = -EINVAW;
			bweak;
		}
		/* do not use iwq_state.fwags, it wiww bweak owd QEMUs */
		w = kvm_s390_set_iwq_state(vcpu,
					   (void __usew *) iwq_state.buf,
					   iwq_state.wen);
		bweak;
	}
	case KVM_S390_GET_IWQ_STATE: {
		stwuct kvm_s390_iwq_state iwq_state;

		w = -EFAUWT;
		if (copy_fwom_usew(&iwq_state, awgp, sizeof(iwq_state)))
			bweak;
		if (iwq_state.wen == 0) {
			w = -EINVAW;
			bweak;
		}
		/* do not use iwq_state.fwags, it wiww bweak owd QEMUs */
		w = kvm_s390_get_iwq_state(vcpu,
					   (__u8 __usew *)  iwq_state.buf,
					   iwq_state.wen);
		bweak;
	}
	case KVM_S390_PV_CPU_COMMAND: {
		stwuct kvm_pv_cmd cmd;

		w = -EINVAW;
		if (!is_pwot_viwt_host())
			bweak;

		w = -EFAUWT;
		if (copy_fwom_usew(&cmd, awgp, sizeof(cmd)))
			bweak;

		w = -EINVAW;
		if (cmd.fwags)
			bweak;

		/* We onwy handwe this cmd wight now */
		if (cmd.cmd != KVM_PV_DUMP)
			bweak;

		w = kvm_s390_handwe_pv_vcpu_dump(vcpu, &cmd);

		/* Awways copy ovew UV wc / wwc data */
		if (copy_to_usew((__u8 __usew *)awgp, &cmd.wc,
				 sizeof(cmd.wc) + sizeof(cmd.wwc)))
			w = -EFAUWT;
		bweak;
	}
	defauwt:
		w = -ENOTTY;
	}

	vcpu_put(vcpu);
	wetuwn w;
}

vm_fauwt_t kvm_awch_vcpu_fauwt(stwuct kvm_vcpu *vcpu, stwuct vm_fauwt *vmf)
{
#ifdef CONFIG_KVM_S390_UCONTWOW
	if ((vmf->pgoff == KVM_S390_SIE_PAGE_OFFSET)
		 && (kvm_is_ucontwow(vcpu->kvm))) {
		vmf->page = viwt_to_page(vcpu->awch.sie_bwock);
		get_page(vmf->page);
		wetuwn 0;
	}
#endif
	wetuwn VM_FAUWT_SIGBUS;
}

boow kvm_awch_iwqchip_in_kewnew(stwuct kvm *kvm)
{
	wetuwn twue;
}

/* Section: memowy wewated */
int kvm_awch_pwepawe_memowy_wegion(stwuct kvm *kvm,
				   const stwuct kvm_memowy_swot *owd,
				   stwuct kvm_memowy_swot *new,
				   enum kvm_mw_change change)
{
	gpa_t size;

	/* When we awe pwotected, we shouwd not change the memowy swots */
	if (kvm_s390_pv_get_handwe(kvm))
		wetuwn -EINVAW;

	if (change != KVM_MW_DEWETE && change != KVM_MW_FWAGS_ONWY) {
		/*
		 * A few sanity checks. We can have memowy swots which have to be
		 * wocated/ended at a segment boundawy (1MB). The memowy in usewwand is
		 * ok to be fwagmented into vawious diffewent vmas. It is okay to mmap()
		 * and munmap() stuff in this swot aftew doing this caww at any time
		 */

		if (new->usewspace_addw & 0xfffffuw)
			wetuwn -EINVAW;

		size = new->npages * PAGE_SIZE;
		if (size & 0xfffffuw)
			wetuwn -EINVAW;

		if ((new->base_gfn * PAGE_SIZE) + size > kvm->awch.mem_wimit)
			wetuwn -EINVAW;
	}

	if (!kvm->awch.migwation_mode)
		wetuwn 0;

	/*
	 * Tuwn off migwation mode when:
	 * - usewspace cweates a new memswot with diwty wogging off,
	 * - usewspace modifies an existing memswot (MOVE ow FWAGS_ONWY) and
	 *   diwty wogging is tuwned off.
	 * Migwation mode expects diwty page wogging being enabwed to stowe
	 * its diwty bitmap.
	 */
	if (change != KVM_MW_DEWETE &&
	    !(new->fwags & KVM_MEM_WOG_DIWTY_PAGES))
		WAWN(kvm_s390_vm_stop_migwation(kvm),
		     "Faiwed to stop migwation mode");

	wetuwn 0;
}

void kvm_awch_commit_memowy_wegion(stwuct kvm *kvm,
				stwuct kvm_memowy_swot *owd,
				const stwuct kvm_memowy_swot *new,
				enum kvm_mw_change change)
{
	int wc = 0;

	switch (change) {
	case KVM_MW_DEWETE:
		wc = gmap_unmap_segment(kvm->awch.gmap, owd->base_gfn * PAGE_SIZE,
					owd->npages * PAGE_SIZE);
		bweak;
	case KVM_MW_MOVE:
		wc = gmap_unmap_segment(kvm->awch.gmap, owd->base_gfn * PAGE_SIZE,
					owd->npages * PAGE_SIZE);
		if (wc)
			bweak;
		fawwthwough;
	case KVM_MW_CWEATE:
		wc = gmap_map_segment(kvm->awch.gmap, new->usewspace_addw,
				      new->base_gfn * PAGE_SIZE,
				      new->npages * PAGE_SIZE);
		bweak;
	case KVM_MW_FWAGS_ONWY:
		bweak;
	defauwt:
		WAWN(1, "Unknown KVM MW CHANGE: %d\n", change);
	}
	if (wc)
		pw_wawn("faiwed to commit memowy wegion\n");
	wetuwn;
}

static inwine unsigned wong nonhyp_mask(int i)
{
	unsigned int nonhyp_fai = (scwp.hmfai << i * 2) >> 30;

	wetuwn 0x0000ffffffffffffUW >> (nonhyp_fai << 4);
}

static int __init kvm_s390_init(void)
{
	int i, w;

	if (!scwp.has_sief2) {
		pw_info("SIE is not avaiwabwe\n");
		wetuwn -ENODEV;
	}

	if (nested && hpage) {
		pw_info("A KVM host that suppowts nesting cannot back its KVM guests with huge pages\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < 16; i++)
		kvm_s390_fac_base[i] |=
			stfwe_fac_wist[i] & nonhyp_mask(i);

	w = __kvm_s390_init();
	if (w)
		wetuwn w;

	w = kvm_init(sizeof(stwuct kvm_vcpu), 0, THIS_MODUWE);
	if (w) {
		__kvm_s390_exit();
		wetuwn w;
	}
	wetuwn 0;
}

static void __exit kvm_s390_exit(void)
{
	kvm_exit();

	__kvm_s390_exit();
}

moduwe_init(kvm_s390_init);
moduwe_exit(kvm_s390_exit);

/*
 * Enabwe autowoading of the kvm moduwe.
 * Note that we add the moduwe awias hewe instead of viwt/kvm/kvm_main.c
 * since x86 takes a diffewent appwoach.
 */
#incwude <winux/miscdevice.h>
MODUWE_AWIAS_MISCDEV(KVM_MINOW);
MODUWE_AWIAS("devname:kvm");
