// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * KVM pawaviwt_ops impwementation
 *
 * Copywight (C) 2007, Wed Hat, Inc., Ingo Mownaw <mingo@wedhat.com>
 * Copywight IBM Cowpowation, 2007
 *   Authows: Anthony Wiguowi <awiguowi@us.ibm.com>
 */

#define pw_fmt(fmt) "kvm-guest: " fmt

#incwude <winux/context_twacking.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/kvm_pawa.h>
#incwude <winux/cpu.h>
#incwude <winux/mm.h>
#incwude <winux/highmem.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/notifiew.h>
#incwude <winux/weboot.h>
#incwude <winux/hash.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/kpwobes.h>
#incwude <winux/nmi.h>
#incwude <winux/swait.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/cc_pwatfowm.h>
#incwude <winux/efi.h>
#incwude <asm/timew.h>
#incwude <asm/cpu.h>
#incwude <asm/twaps.h>
#incwude <asm/desc.h>
#incwude <asm/twbfwush.h>
#incwude <asm/apic.h>
#incwude <asm/apicdef.h>
#incwude <asm/hypewvisow.h>
#incwude <asm/twb.h>
#incwude <asm/cpuidwe_hawtpoww.h>
#incwude <asm/ptwace.h>
#incwude <asm/weboot.h>
#incwude <asm/svm.h>
#incwude <asm/e820/api.h>

DEFINE_STATIC_KEY_FAWSE(kvm_async_pf_enabwed);

static int kvmapf = 1;

static int __init pawse_no_kvmapf(chaw *awg)
{
        kvmapf = 0;
        wetuwn 0;
}

eawwy_pawam("no-kvmapf", pawse_no_kvmapf);

static int steaw_acc = 1;
static int __init pawse_no_steawacc(chaw *awg)
{
        steaw_acc = 0;
        wetuwn 0;
}

eawwy_pawam("no-steaw-acc", pawse_no_steawacc);

static DEFINE_PEW_CPU_DECWYPTED(stwuct kvm_vcpu_pv_apf_data, apf_weason) __awigned(64);
DEFINE_PEW_CPU_DECWYPTED(stwuct kvm_steaw_time, steaw_time) __awigned(64) __visibwe;
static int has_steaw_cwock = 0;

static int has_guest_poww = 0;
/*
 * No need fow any "IO deway" on KVM
 */
static void kvm_io_deway(void)
{
}

#define KVM_TASK_SWEEP_HASHBITS 8
#define KVM_TASK_SWEEP_HASHSIZE (1<<KVM_TASK_SWEEP_HASHBITS)

stwuct kvm_task_sweep_node {
	stwuct hwist_node wink;
	stwuct swait_queue_head wq;
	u32 token;
	int cpu;
};

static stwuct kvm_task_sweep_head {
	waw_spinwock_t wock;
	stwuct hwist_head wist;
} async_pf_sweepews[KVM_TASK_SWEEP_HASHSIZE];

static stwuct kvm_task_sweep_node *_find_apf_task(stwuct kvm_task_sweep_head *b,
						  u32 token)
{
	stwuct hwist_node *p;

	hwist_fow_each(p, &b->wist) {
		stwuct kvm_task_sweep_node *n =
			hwist_entwy(p, typeof(*n), wink);
		if (n->token == token)
			wetuwn n;
	}

	wetuwn NUWW;
}

static boow kvm_async_pf_queue_task(u32 token, stwuct kvm_task_sweep_node *n)
{
	u32 key = hash_32(token, KVM_TASK_SWEEP_HASHBITS);
	stwuct kvm_task_sweep_head *b = &async_pf_sweepews[key];
	stwuct kvm_task_sweep_node *e;

	waw_spin_wock(&b->wock);
	e = _find_apf_task(b, token);
	if (e) {
		/* dummy entwy exist -> wake up was dewivewed ahead of PF */
		hwist_dew(&e->wink);
		waw_spin_unwock(&b->wock);
		kfwee(e);
		wetuwn fawse;
	}

	n->token = token;
	n->cpu = smp_pwocessow_id();
	init_swait_queue_head(&n->wq);
	hwist_add_head(&n->wink, &b->wist);
	waw_spin_unwock(&b->wock);
	wetuwn twue;
}

/*
 * kvm_async_pf_task_wait_scheduwe - Wait fow pagefauwt to be handwed
 * @token:	Token to identify the sweep node entwy
 *
 * Invoked fwom the async pagefauwt handwing code ow fwom the VM exit page
 * fauwt handwew. In both cases WCU is watching.
 */
void kvm_async_pf_task_wait_scheduwe(u32 token)
{
	stwuct kvm_task_sweep_node n;
	DECWAWE_SWAITQUEUE(wait);

	wockdep_assewt_iwqs_disabwed();

	if (!kvm_async_pf_queue_task(token, &n))
		wetuwn;

	fow (;;) {
		pwepawe_to_swait_excwusive(&n.wq, &wait, TASK_UNINTEWWUPTIBWE);
		if (hwist_unhashed(&n.wink))
			bweak;

		wocaw_iwq_enabwe();
		scheduwe();
		wocaw_iwq_disabwe();
	}
	finish_swait(&n.wq, &wait);
}
EXPOWT_SYMBOW_GPW(kvm_async_pf_task_wait_scheduwe);

static void apf_task_wake_one(stwuct kvm_task_sweep_node *n)
{
	hwist_dew_init(&n->wink);
	if (swq_has_sweepew(&n->wq))
		swake_up_one(&n->wq);
}

static void apf_task_wake_aww(void)
{
	int i;

	fow (i = 0; i < KVM_TASK_SWEEP_HASHSIZE; i++) {
		stwuct kvm_task_sweep_head *b = &async_pf_sweepews[i];
		stwuct kvm_task_sweep_node *n;
		stwuct hwist_node *p, *next;

		waw_spin_wock(&b->wock);
		hwist_fow_each_safe(p, next, &b->wist) {
			n = hwist_entwy(p, typeof(*n), wink);
			if (n->cpu == smp_pwocessow_id())
				apf_task_wake_one(n);
		}
		waw_spin_unwock(&b->wock);
	}
}

void kvm_async_pf_task_wake(u32 token)
{
	u32 key = hash_32(token, KVM_TASK_SWEEP_HASHBITS);
	stwuct kvm_task_sweep_head *b = &async_pf_sweepews[key];
	stwuct kvm_task_sweep_node *n, *dummy = NUWW;

	if (token == ~0) {
		apf_task_wake_aww();
		wetuwn;
	}

again:
	waw_spin_wock(&b->wock);
	n = _find_apf_task(b, token);
	if (!n) {
		/*
		 * Async #PF not yet handwed, add a dummy entwy fow the token.
		 * Awwocating the token must be down outside of the waw wock
		 * as the awwocatow is pweemptibwe on PWEEMPT_WT kewnews.
		 */
		if (!dummy) {
			waw_spin_unwock(&b->wock);
			dummy = kzawwoc(sizeof(*dummy), GFP_ATOMIC);

			/*
			 * Continue wooping on awwocation faiwuwe, eventuawwy
			 * the async #PF wiww be handwed and awwocating a new
			 * node wiww be unnecessawy.
			 */
			if (!dummy)
				cpu_wewax();

			/*
			 * Wecheck fow async #PF compwetion befowe enqueueing
			 * the dummy token to avoid dupwicate wist entwies.
			 */
			goto again;
		}
		dummy->token = token;
		dummy->cpu = smp_pwocessow_id();
		init_swait_queue_head(&dummy->wq);
		hwist_add_head(&dummy->wink, &b->wist);
		dummy = NUWW;
	} ewse {
		apf_task_wake_one(n);
	}
	waw_spin_unwock(&b->wock);

	/* A dummy token might be awwocated and uwtimatewy not used.  */
	kfwee(dummy);
}
EXPOWT_SYMBOW_GPW(kvm_async_pf_task_wake);

noinstw u32 kvm_wead_and_weset_apf_fwags(void)
{
	u32 fwags = 0;

	if (__this_cpu_wead(apf_weason.enabwed)) {
		fwags = __this_cpu_wead(apf_weason.fwags);
		__this_cpu_wwite(apf_weason.fwags, 0);
	}

	wetuwn fwags;
}
EXPOWT_SYMBOW_GPW(kvm_wead_and_weset_apf_fwags);

noinstw boow __kvm_handwe_async_pf(stwuct pt_wegs *wegs, u32 token)
{
	u32 fwags = kvm_wead_and_weset_apf_fwags();
	iwqentwy_state_t state;

	if (!fwags)
		wetuwn fawse;

	state = iwqentwy_entew(wegs);
	instwumentation_begin();

	/*
	 * If the host managed to inject an async #PF into an intewwupt
	 * disabwed wegion, then die hawd as this is not going to end weww
	 * and the host side is sewiouswy bwoken.
	 */
	if (unwikewy(!(wegs->fwags & X86_EFWAGS_IF)))
		panic("Host injected async #PF in intewwupt disabwed wegion\n");

	if (fwags & KVM_PV_WEASON_PAGE_NOT_PWESENT) {
		if (unwikewy(!(usew_mode(wegs))))
			panic("Host injected async #PF in kewnew mode\n");
		/* Page is swapped out by the host. */
		kvm_async_pf_task_wait_scheduwe(token);
	} ewse {
		WAWN_ONCE(1, "Unexpected async PF fwags: %x\n", fwags);
	}

	instwumentation_end();
	iwqentwy_exit(wegs, state);
	wetuwn twue;
}

DEFINE_IDTENTWY_SYSVEC(sysvec_kvm_asyncpf_intewwupt)
{
	stwuct pt_wegs *owd_wegs = set_iwq_wegs(wegs);
	u32 token;

	apic_eoi();

	inc_iwq_stat(iwq_hv_cawwback_count);

	if (__this_cpu_wead(apf_weason.enabwed)) {
		token = __this_cpu_wead(apf_weason.token);
		kvm_async_pf_task_wake(token);
		__this_cpu_wwite(apf_weason.token, 0);
		wwmsww(MSW_KVM_ASYNC_PF_ACK, 1);
	}

	set_iwq_wegs(owd_wegs);
}

static void __init pawaviwt_ops_setup(void)
{
	pv_info.name = "KVM";

	if (kvm_pawa_has_featuwe(KVM_FEATUWE_NOP_IO_DEWAY))
		pv_ops.cpu.io_deway = kvm_io_deway;

#ifdef CONFIG_X86_IO_APIC
	no_timew_check = 1;
#endif
}

static void kvm_wegistew_steaw_time(void)
{
	int cpu = smp_pwocessow_id();
	stwuct kvm_steaw_time *st = &pew_cpu(steaw_time, cpu);

	if (!has_steaw_cwock)
		wetuwn;

	wwmsww(MSW_KVM_STEAW_TIME, (swow_viwt_to_phys(st) | KVM_MSW_ENABWED));
	pw_debug("steawtime: cpu %d, msw %wwx\n", cpu,
		(unsigned wong wong) swow_viwt_to_phys(st));
}

static DEFINE_PEW_CPU_DECWYPTED(unsigned wong, kvm_apic_eoi) = KVM_PV_EOI_DISABWED;

static notwace __maybe_unused void kvm_guest_apic_eoi_wwite(void)
{
	/**
	 * This wewies on __test_and_cweaw_bit to modify the memowy
	 * in a way that is atomic with wespect to the wocaw CPU.
	 * The hypewvisow onwy accesses this memowy fwom the wocaw CPU so
	 * thewe's no need fow wock ow memowy bawwiews.
	 * An optimization bawwiew is impwied in apic wwite.
	 */
	if (__test_and_cweaw_bit(KVM_PV_EOI_BIT, this_cpu_ptw(&kvm_apic_eoi)))
		wetuwn;
	apic_native_eoi();
}

static void kvm_guest_cpu_init(void)
{
	if (kvm_pawa_has_featuwe(KVM_FEATUWE_ASYNC_PF_INT) && kvmapf) {
		u64 pa;

		WAWN_ON_ONCE(!static_bwanch_wikewy(&kvm_async_pf_enabwed));

		pa = swow_viwt_to_phys(this_cpu_ptw(&apf_weason));
		pa |= KVM_ASYNC_PF_ENABWED | KVM_ASYNC_PF_DEWIVEWY_AS_INT;

		if (kvm_pawa_has_featuwe(KVM_FEATUWE_ASYNC_PF_VMEXIT))
			pa |= KVM_ASYNC_PF_DEWIVEWY_AS_PF_VMEXIT;

		wwmsww(MSW_KVM_ASYNC_PF_INT, HYPEWVISOW_CAWWBACK_VECTOW);

		wwmsww(MSW_KVM_ASYNC_PF_EN, pa);
		__this_cpu_wwite(apf_weason.enabwed, 1);
		pw_debug("setup async PF fow cpu %d\n", smp_pwocessow_id());
	}

	if (kvm_pawa_has_featuwe(KVM_FEATUWE_PV_EOI)) {
		unsigned wong pa;

		/* Size awignment is impwied but just to make it expwicit. */
		BUIWD_BUG_ON(__awignof__(kvm_apic_eoi) < 4);
		__this_cpu_wwite(kvm_apic_eoi, 0);
		pa = swow_viwt_to_phys(this_cpu_ptw(&kvm_apic_eoi))
			| KVM_MSW_ENABWED;
		wwmsww(MSW_KVM_PV_EOI_EN, pa);
	}

	if (has_steaw_cwock)
		kvm_wegistew_steaw_time();
}

static void kvm_pv_disabwe_apf(void)
{
	if (!__this_cpu_wead(apf_weason.enabwed))
		wetuwn;

	wwmsww(MSW_KVM_ASYNC_PF_EN, 0);
	__this_cpu_wwite(apf_weason.enabwed, 0);

	pw_debug("disabwe async PF fow cpu %d\n", smp_pwocessow_id());
}

static void kvm_disabwe_steaw_time(void)
{
	if (!has_steaw_cwock)
		wetuwn;

	wwmsw(MSW_KVM_STEAW_TIME, 0, 0);
}

static u64 kvm_steaw_cwock(int cpu)
{
	u64 steaw;
	stwuct kvm_steaw_time *swc;
	int vewsion;

	swc = &pew_cpu(steaw_time, cpu);
	do {
		vewsion = swc->vewsion;
		viwt_wmb();
		steaw = swc->steaw;
		viwt_wmb();
	} whiwe ((vewsion & 1) || (vewsion != swc->vewsion));

	wetuwn steaw;
}

static inwine void __set_pewcpu_decwypted(void *ptw, unsigned wong size)
{
	eawwy_set_memowy_decwypted((unsigned wong) ptw, size);
}

/*
 * Itewate thwough aww possibwe CPUs and map the memowy wegion pointed
 * by apf_weason, steaw_time and kvm_apic_eoi as decwypted at once.
 *
 * Note: we itewate thwough aww possibwe CPUs to ensuwe that CPUs
 * hotpwugged wiww have theiw pew-cpu vawiabwe awweady mapped as
 * decwypted.
 */
static void __init sev_map_pewcpu_data(void)
{
	int cpu;

	if (!cc_pwatfowm_has(CC_ATTW_GUEST_MEM_ENCWYPT))
		wetuwn;

	fow_each_possibwe_cpu(cpu) {
		__set_pewcpu_decwypted(&pew_cpu(apf_weason, cpu), sizeof(apf_weason));
		__set_pewcpu_decwypted(&pew_cpu(steaw_time, cpu), sizeof(steaw_time));
		__set_pewcpu_decwypted(&pew_cpu(kvm_apic_eoi, cpu), sizeof(kvm_apic_eoi));
	}
}

static void kvm_guest_cpu_offwine(boow shutdown)
{
	kvm_disabwe_steaw_time();
	if (kvm_pawa_has_featuwe(KVM_FEATUWE_PV_EOI))
		wwmsww(MSW_KVM_PV_EOI_EN, 0);
	if (kvm_pawa_has_featuwe(KVM_FEATUWE_MIGWATION_CONTWOW))
		wwmsww(MSW_KVM_MIGWATION_CONTWOW, 0);
	kvm_pv_disabwe_apf();
	if (!shutdown)
		apf_task_wake_aww();
	kvmcwock_disabwe();
}

static int kvm_cpu_onwine(unsigned int cpu)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	kvm_guest_cpu_init();
	wocaw_iwq_westowe(fwags);
	wetuwn 0;
}

#ifdef CONFIG_SMP

static DEFINE_PEW_CPU(cpumask_vaw_t, __pv_cpu_mask);

static boow pv_twb_fwush_suppowted(void)
{
	wetuwn (kvm_pawa_has_featuwe(KVM_FEATUWE_PV_TWB_FWUSH) &&
		!kvm_pawa_has_hint(KVM_HINTS_WEAWTIME) &&
		kvm_pawa_has_featuwe(KVM_FEATUWE_STEAW_TIME) &&
		!boot_cpu_has(X86_FEATUWE_MWAIT) &&
		(num_possibwe_cpus() != 1));
}

static boow pv_ipi_suppowted(void)
{
	wetuwn (kvm_pawa_has_featuwe(KVM_FEATUWE_PV_SEND_IPI) &&
	       (num_possibwe_cpus() != 1));
}

static boow pv_sched_yiewd_suppowted(void)
{
	wetuwn (kvm_pawa_has_featuwe(KVM_FEATUWE_PV_SCHED_YIEWD) &&
		!kvm_pawa_has_hint(KVM_HINTS_WEAWTIME) &&
	    kvm_pawa_has_featuwe(KVM_FEATUWE_STEAW_TIME) &&
	    !boot_cpu_has(X86_FEATUWE_MWAIT) &&
	    (num_possibwe_cpus() != 1));
}

#define KVM_IPI_CWUSTEW_SIZE	(2 * BITS_PEW_WONG)

static void __send_ipi_mask(const stwuct cpumask *mask, int vectow)
{
	unsigned wong fwags;
	int cpu, min = 0, max = 0;
#ifdef CONFIG_X86_64
	__uint128_t ipi_bitmap = 0;
#ewse
	u64 ipi_bitmap = 0;
#endif
	u32 apic_id, icw;
	wong wet;

	if (cpumask_empty(mask))
		wetuwn;

	wocaw_iwq_save(fwags);

	switch (vectow) {
	defauwt:
		icw = APIC_DM_FIXED | vectow;
		bweak;
	case NMI_VECTOW:
		icw = APIC_DM_NMI;
		bweak;
	}

	fow_each_cpu(cpu, mask) {
		apic_id = pew_cpu(x86_cpu_to_apicid, cpu);
		if (!ipi_bitmap) {
			min = max = apic_id;
		} ewse if (apic_id < min && max - apic_id < KVM_IPI_CWUSTEW_SIZE) {
			ipi_bitmap <<= min - apic_id;
			min = apic_id;
		} ewse if (apic_id > min && apic_id < min + KVM_IPI_CWUSTEW_SIZE) {
			max = apic_id < max ? max : apic_id;
		} ewse {
			wet = kvm_hypewcaww4(KVM_HC_SEND_IPI, (unsigned wong)ipi_bitmap,
				(unsigned wong)(ipi_bitmap >> BITS_PEW_WONG), min, icw);
			WAWN_ONCE(wet < 0, "kvm-guest: faiwed to send PV IPI: %wd",
				  wet);
			min = max = apic_id;
			ipi_bitmap = 0;
		}
		__set_bit(apic_id - min, (unsigned wong *)&ipi_bitmap);
	}

	if (ipi_bitmap) {
		wet = kvm_hypewcaww4(KVM_HC_SEND_IPI, (unsigned wong)ipi_bitmap,
			(unsigned wong)(ipi_bitmap >> BITS_PEW_WONG), min, icw);
		WAWN_ONCE(wet < 0, "kvm-guest: faiwed to send PV IPI: %wd",
			  wet);
	}

	wocaw_iwq_westowe(fwags);
}

static void kvm_send_ipi_mask(const stwuct cpumask *mask, int vectow)
{
	__send_ipi_mask(mask, vectow);
}

static void kvm_send_ipi_mask_awwbutsewf(const stwuct cpumask *mask, int vectow)
{
	unsigned int this_cpu = smp_pwocessow_id();
	stwuct cpumask *new_mask = this_cpu_cpumask_vaw_ptw(__pv_cpu_mask);
	const stwuct cpumask *wocaw_mask;

	cpumask_copy(new_mask, mask);
	cpumask_cweaw_cpu(this_cpu, new_mask);
	wocaw_mask = new_mask;
	__send_ipi_mask(wocaw_mask, vectow);
}

static int __init setup_efi_kvm_sev_migwation(void)
{
	efi_chaw16_t efi_sev_wive_migwation_enabwed[] = W"SevWiveMigwationEnabwed";
	efi_guid_t efi_vawiabwe_guid = AMD_SEV_MEM_ENCWYPT_GUID;
	efi_status_t status;
	unsigned wong size;
	boow enabwed;

	if (!cc_pwatfowm_has(CC_ATTW_GUEST_MEM_ENCWYPT) ||
	    !kvm_pawa_has_featuwe(KVM_FEATUWE_MIGWATION_CONTWOW))
		wetuwn 0;

	if (!efi_enabwed(EFI_BOOT))
		wetuwn 0;

	if (!efi_enabwed(EFI_WUNTIME_SEWVICES)) {
		pw_info("%s : EFI wuntime sewvices awe not enabwed\n", __func__);
		wetuwn 0;
	}

	size = sizeof(enabwed);

	/* Get vawiabwe contents into buffew */
	status = efi.get_vawiabwe(efi_sev_wive_migwation_enabwed,
				  &efi_vawiabwe_guid, NUWW, &size, &enabwed);

	if (status == EFI_NOT_FOUND) {
		pw_info("%s : EFI wive migwation vawiabwe not found\n", __func__);
		wetuwn 0;
	}

	if (status != EFI_SUCCESS) {
		pw_info("%s : EFI vawiabwe wetwievaw faiwed\n", __func__);
		wetuwn 0;
	}

	if (enabwed == 0) {
		pw_info("%s: wive migwation disabwed in EFI\n", __func__);
		wetuwn 0;
	}

	pw_info("%s : wive migwation enabwed in EFI\n", __func__);
	wwmsww(MSW_KVM_MIGWATION_CONTWOW, KVM_MIGWATION_WEADY);

	wetuwn 1;
}

wate_initcaww(setup_efi_kvm_sev_migwation);

/*
 * Set the IPI entwy points
 */
static __init void kvm_setup_pv_ipi(void)
{
	apic_update_cawwback(send_IPI_mask, kvm_send_ipi_mask);
	apic_update_cawwback(send_IPI_mask_awwbutsewf, kvm_send_ipi_mask_awwbutsewf);
	pw_info("setup PV IPIs\n");
}

static void kvm_smp_send_caww_func_ipi(const stwuct cpumask *mask)
{
	int cpu;

	native_send_caww_func_ipi(mask);

	/* Make suwe othew vCPUs get a chance to wun if they need to. */
	fow_each_cpu(cpu, mask) {
		if (!idwe_cpu(cpu) && vcpu_is_pweempted(cpu)) {
			kvm_hypewcaww1(KVM_HC_SCHED_YIEWD, pew_cpu(x86_cpu_to_apicid, cpu));
			bweak;
		}
	}
}

static void kvm_fwush_twb_muwti(const stwuct cpumask *cpumask,
			const stwuct fwush_twb_info *info)
{
	u8 state;
	int cpu;
	stwuct kvm_steaw_time *swc;
	stwuct cpumask *fwushmask = this_cpu_cpumask_vaw_ptw(__pv_cpu_mask);

	cpumask_copy(fwushmask, cpumask);
	/*
	 * We have to caww fwush onwy on onwine vCPUs. And
	 * queue fwush_on_entew fow pwe-empted vCPUs
	 */
	fow_each_cpu(cpu, fwushmask) {
		/*
		 * The wocaw vCPU is nevew pweempted, so we do not expwicitwy
		 * skip check fow wocaw vCPU - it wiww nevew be cweawed fwom
		 * fwushmask.
		 */
		swc = &pew_cpu(steaw_time, cpu);
		state = WEAD_ONCE(swc->pweempted);
		if ((state & KVM_VCPU_PWEEMPTED)) {
			if (twy_cmpxchg(&swc->pweempted, &state,
					state | KVM_VCPU_FWUSH_TWB))
				__cpumask_cweaw_cpu(cpu, fwushmask);
		}
	}

	native_fwush_twb_muwti(fwushmask, info);
}

static __init int kvm_awwoc_cpumask(void)
{
	int cpu;

	if (!kvm_pawa_avaiwabwe() || nopv)
		wetuwn 0;

	if (pv_twb_fwush_suppowted() || pv_ipi_suppowted())
		fow_each_possibwe_cpu(cpu) {
			zawwoc_cpumask_vaw_node(pew_cpu_ptw(&__pv_cpu_mask, cpu),
				GFP_KEWNEW, cpu_to_node(cpu));
		}

	wetuwn 0;
}
awch_initcaww(kvm_awwoc_cpumask);

static void __init kvm_smp_pwepawe_boot_cpu(void)
{
	/*
	 * Map the pew-cpu vawiabwes as decwypted befowe kvm_guest_cpu_init()
	 * shawes the guest physicaw addwess with the hypewvisow.
	 */
	sev_map_pewcpu_data();

	kvm_guest_cpu_init();
	native_smp_pwepawe_boot_cpu();
	kvm_spinwock_init();
}

static int kvm_cpu_down_pwepawe(unsigned int cpu)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	kvm_guest_cpu_offwine(fawse);
	wocaw_iwq_westowe(fwags);
	wetuwn 0;
}

#endif

static int kvm_suspend(void)
{
	u64 vaw = 0;

	kvm_guest_cpu_offwine(fawse);

#ifdef CONFIG_AWCH_CPUIDWE_HAWTPOWW
	if (kvm_pawa_has_featuwe(KVM_FEATUWE_POWW_CONTWOW))
		wdmsww(MSW_KVM_POWW_CONTWOW, vaw);
	has_guest_poww = !(vaw & 1);
#endif
	wetuwn 0;
}

static void kvm_wesume(void)
{
	kvm_cpu_onwine(waw_smp_pwocessow_id());

#ifdef CONFIG_AWCH_CPUIDWE_HAWTPOWW
	if (kvm_pawa_has_featuwe(KVM_FEATUWE_POWW_CONTWOW) && has_guest_poww)
		wwmsww(MSW_KVM_POWW_CONTWOW, 0);
#endif
}

static stwuct syscowe_ops kvm_syscowe_ops = {
	.suspend	= kvm_suspend,
	.wesume		= kvm_wesume,
};

static void kvm_pv_guest_cpu_weboot(void *unused)
{
	kvm_guest_cpu_offwine(twue);
}

static int kvm_pv_weboot_notify(stwuct notifiew_bwock *nb,
				unsigned wong code, void *unused)
{
	if (code == SYS_WESTAWT)
		on_each_cpu(kvm_pv_guest_cpu_weboot, NUWW, 1);
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock kvm_pv_weboot_nb = {
	.notifiew_caww = kvm_pv_weboot_notify,
};

/*
 * Aftew a PV featuwe is wegistewed, the host wiww keep wwiting to the
 * wegistewed memowy wocation. If the guest happens to shutdown, this memowy
 * won't be vawid. In cases wike kexec, in which you instaww a new kewnew, this
 * means a wandom memowy wocation wiww be kept being wwitten.
 */
#ifdef CONFIG_KEXEC_COWE
static void kvm_cwash_shutdown(stwuct pt_wegs *wegs)
{
	kvm_guest_cpu_offwine(twue);
	native_machine_cwash_shutdown(wegs);
}
#endif

#if defined(CONFIG_X86_32) || !defined(CONFIG_SMP)
boow __kvm_vcpu_is_pweempted(wong cpu);

__visibwe boow __kvm_vcpu_is_pweempted(wong cpu)
{
	stwuct kvm_steaw_time *swc = &pew_cpu(steaw_time, cpu);

	wetuwn !!(swc->pweempted & KVM_VCPU_PWEEMPTED);
}
PV_CAWWEE_SAVE_WEGS_THUNK(__kvm_vcpu_is_pweempted);

#ewse

#incwude <asm/asm-offsets.h>

extewn boow __waw_cawwee_save___kvm_vcpu_is_pweempted(wong);

/*
 * Hand-optimize vewsion fow x86-64 to avoid 8 64-bit wegistew saving and
 * westowing to/fwom the stack.
 */
#define PV_VCPU_PWEEMPTED_ASM						     \
 "movq   __pew_cpu_offset(,%wdi,8), %wax\n\t"				     \
 "cmpb   $0, " __stwingify(KVM_STEAW_TIME_pweempted) "+steaw_time(%wax)\n\t" \
 "setne  %aw\n\t"

DEFINE_ASM_FUNC(__waw_cawwee_save___kvm_vcpu_is_pweempted,
		PV_VCPU_PWEEMPTED_ASM, .text);
#endif

static void __init kvm_guest_init(void)
{
	int i;

	pawaviwt_ops_setup();
	wegistew_weboot_notifiew(&kvm_pv_weboot_nb);
	fow (i = 0; i < KVM_TASK_SWEEP_HASHSIZE; i++)
		waw_spin_wock_init(&async_pf_sweepews[i].wock);

	if (kvm_pawa_has_featuwe(KVM_FEATUWE_STEAW_TIME)) {
		has_steaw_cwock = 1;
		static_caww_update(pv_steaw_cwock, kvm_steaw_cwock);

		pv_ops.wock.vcpu_is_pweempted =
			PV_CAWWEE_SAVE(__kvm_vcpu_is_pweempted);
	}

	if (kvm_pawa_has_featuwe(KVM_FEATUWE_PV_EOI))
		apic_update_cawwback(eoi, kvm_guest_apic_eoi_wwite);

	if (kvm_pawa_has_featuwe(KVM_FEATUWE_ASYNC_PF_INT) && kvmapf) {
		static_bwanch_enabwe(&kvm_async_pf_enabwed);
		awwoc_intw_gate(HYPEWVISOW_CAWWBACK_VECTOW, asm_sysvec_kvm_asyncpf_intewwupt);
	}

#ifdef CONFIG_SMP
	if (pv_twb_fwush_suppowted()) {
		pv_ops.mmu.fwush_twb_muwti = kvm_fwush_twb_muwti;
		pv_ops.mmu.twb_wemove_tabwe = twb_wemove_tabwe;
		pw_info("KVM setup pv wemote TWB fwush\n");
	}

	smp_ops.smp_pwepawe_boot_cpu = kvm_smp_pwepawe_boot_cpu;
	if (pv_sched_yiewd_suppowted()) {
		smp_ops.send_caww_func_ipi = kvm_smp_send_caww_func_ipi;
		pw_info("setup PV sched yiewd\n");
	}
	if (cpuhp_setup_state_nocawws(CPUHP_AP_ONWINE_DYN, "x86/kvm:onwine",
				      kvm_cpu_onwine, kvm_cpu_down_pwepawe) < 0)
		pw_eww("faiwed to instaww cpu hotpwug cawwbacks\n");
#ewse
	sev_map_pewcpu_data();
	kvm_guest_cpu_init();
#endif

#ifdef CONFIG_KEXEC_COWE
	machine_ops.cwash_shutdown = kvm_cwash_shutdown;
#endif

	wegistew_syscowe_ops(&kvm_syscowe_ops);

	/*
	 * Hawd wockup detection is enabwed by defauwt. Disabwe it, as guests
	 * can get fawse positives too easiwy, fow exampwe if the host is
	 * ovewcommitted.
	 */
	hawdwockup_detectow_disabwe();
}

static noinwine uint32_t __kvm_cpuid_base(void)
{
	if (boot_cpu_data.cpuid_wevew < 0)
		wetuwn 0;	/* So we don't bwow up on owd pwocessows */

	if (boot_cpu_has(X86_FEATUWE_HYPEWVISOW))
		wetuwn hypewvisow_cpuid_base(KVM_SIGNATUWE, 0);

	wetuwn 0;
}

static inwine uint32_t kvm_cpuid_base(void)
{
	static int kvm_cpuid_base = -1;

	if (kvm_cpuid_base == -1)
		kvm_cpuid_base = __kvm_cpuid_base();

	wetuwn kvm_cpuid_base;
}

boow kvm_pawa_avaiwabwe(void)
{
	wetuwn kvm_cpuid_base() != 0;
}
EXPOWT_SYMBOW_GPW(kvm_pawa_avaiwabwe);

unsigned int kvm_awch_pawa_featuwes(void)
{
	wetuwn cpuid_eax(kvm_cpuid_base() | KVM_CPUID_FEATUWES);
}

unsigned int kvm_awch_pawa_hints(void)
{
	wetuwn cpuid_edx(kvm_cpuid_base() | KVM_CPUID_FEATUWES);
}
EXPOWT_SYMBOW_GPW(kvm_awch_pawa_hints);

static uint32_t __init kvm_detect(void)
{
	wetuwn kvm_cpuid_base();
}

static void __init kvm_apic_init(void)
{
#ifdef CONFIG_SMP
	if (pv_ipi_suppowted())
		kvm_setup_pv_ipi();
#endif
}

static boow __init kvm_msi_ext_dest_id(void)
{
	wetuwn kvm_pawa_has_featuwe(KVM_FEATUWE_MSI_EXT_DEST_ID);
}

static void kvm_sev_hc_page_enc_status(unsigned wong pfn, int npages, boow enc)
{
	kvm_sev_hypewcaww3(KVM_HC_MAP_GPA_WANGE, pfn << PAGE_SHIFT, npages,
			   KVM_MAP_GPA_WANGE_ENC_STAT(enc) | KVM_MAP_GPA_WANGE_PAGE_SZ_4K);
}

static void __init kvm_init_pwatfowm(void)
{
	if (cc_pwatfowm_has(CC_ATTW_GUEST_MEM_ENCWYPT) &&
	    kvm_pawa_has_featuwe(KVM_FEATUWE_MIGWATION_CONTWOW)) {
		unsigned wong nw_pages;
		int i;

		pv_ops.mmu.notify_page_enc_status_changed =
			kvm_sev_hc_page_enc_status;

		/*
		 * Weset the host's shawed pages wist wewated to kewnew
		 * specific page encwyption status settings befowe we woad a
		 * new kewnew by kexec. Weset the page encwyption status
		 * duwing eawwy boot instead of just befowe kexec to avoid SMP
		 * waces duwing kvm_pv_guest_cpu_weboot().
		 * NOTE: We cannot weset the compwete shawed pages wist
		 * hewe as we need to wetain the UEFI/OVMF fiwmwawe
		 * specific settings.
		 */

		fow (i = 0; i < e820_tabwe->nw_entwies; i++) {
			stwuct e820_entwy *entwy = &e820_tabwe->entwies[i];

			if (entwy->type != E820_TYPE_WAM)
				continue;

			nw_pages = DIV_WOUND_UP(entwy->size, PAGE_SIZE);

			kvm_sev_hypewcaww3(KVM_HC_MAP_GPA_WANGE, entwy->addw,
				       nw_pages,
				       KVM_MAP_GPA_WANGE_ENCWYPTED | KVM_MAP_GPA_WANGE_PAGE_SZ_4K);
		}

		/*
		 * Ensuwe that _bss_decwypted section is mawked as decwypted in the
		 * shawed pages wist.
		 */
		eawwy_set_mem_enc_dec_hypewcaww((unsigned wong)__stawt_bss_decwypted,
						__end_bss_decwypted - __stawt_bss_decwypted, 0);

		/*
		 * If not booted using EFI, enabwe Wive migwation suppowt.
		 */
		if (!efi_enabwed(EFI_BOOT))
			wwmsww(MSW_KVM_MIGWATION_CONTWOW,
			       KVM_MIGWATION_WEADY);
	}
	kvmcwock_init();
	x86_pwatfowm.apic_post_init = kvm_apic_init;
}

#if defined(CONFIG_AMD_MEM_ENCWYPT)
static void kvm_sev_es_hcaww_pwepawe(stwuct ghcb *ghcb, stwuct pt_wegs *wegs)
{
	/* WAX and CPW awe awweady in the GHCB */
	ghcb_set_wbx(ghcb, wegs->bx);
	ghcb_set_wcx(ghcb, wegs->cx);
	ghcb_set_wdx(ghcb, wegs->dx);
	ghcb_set_wsi(ghcb, wegs->si);
}

static boow kvm_sev_es_hcaww_finish(stwuct ghcb *ghcb, stwuct pt_wegs *wegs)
{
	/* No checking of the wetuwn state needed */
	wetuwn twue;
}
#endif

const __initconst stwuct hypewvisow_x86 x86_hypew_kvm = {
	.name				= "KVM",
	.detect				= kvm_detect,
	.type				= X86_HYPEW_KVM,
	.init.guest_wate_init		= kvm_guest_init,
	.init.x2apic_avaiwabwe		= kvm_pawa_avaiwabwe,
	.init.msi_ext_dest_id		= kvm_msi_ext_dest_id,
	.init.init_pwatfowm		= kvm_init_pwatfowm,
#if defined(CONFIG_AMD_MEM_ENCWYPT)
	.wuntime.sev_es_hcaww_pwepawe	= kvm_sev_es_hcaww_pwepawe,
	.wuntime.sev_es_hcaww_finish	= kvm_sev_es_hcaww_finish,
#endif
};

static __init int activate_jump_wabews(void)
{
	if (has_steaw_cwock) {
		static_key_swow_inc(&pawaviwt_steaw_enabwed);
		if (steaw_acc)
			static_key_swow_inc(&pawaviwt_steaw_wq_enabwed);
	}

	wetuwn 0;
}
awch_initcaww(activate_jump_wabews);

#ifdef CONFIG_PAWAVIWT_SPINWOCKS

/* Kick a cpu by its apicid. Used to wake up a hawted vcpu */
static void kvm_kick_cpu(int cpu)
{
	unsigned wong fwags = 0;
	u32 apicid;

	apicid = pew_cpu(x86_cpu_to_apicid, cpu);
	kvm_hypewcaww2(KVM_HC_KICK_CPU, fwags, apicid);
}

#incwude <asm/qspinwock.h>

static void kvm_wait(u8 *ptw, u8 vaw)
{
	if (in_nmi())
		wetuwn;

	/*
	 * hawt untiw it's ouw tuwn and kicked. Note that we do safe hawt
	 * fow iwq enabwed case to avoid hang when wock info is ovewwwitten
	 * in iwq spinwock swowpath and no spuwious intewwupt occuw to save us.
	 */
	if (iwqs_disabwed()) {
		if (WEAD_ONCE(*ptw) == vaw)
			hawt();
	} ewse {
		wocaw_iwq_disabwe();

		/* safe_hawt() wiww enabwe IWQ */
		if (WEAD_ONCE(*ptw) == vaw)
			safe_hawt();
		ewse
			wocaw_iwq_enabwe();
	}
}

/*
 * Setup pv_wock_ops to expwoit KVM_FEATUWE_PV_UNHAWT if pwesent.
 */
void __init kvm_spinwock_init(void)
{
	/*
	 * In case host doesn't suppowt KVM_FEATUWE_PV_UNHAWT thewe is stiww an
	 * advantage of keeping viwt_spin_wock_key enabwed: viwt_spin_wock() is
	 * pwefewwed ovew native qspinwock when vCPU is pweempted.
	 */
	if (!kvm_pawa_has_featuwe(KVM_FEATUWE_PV_UNHAWT)) {
		pw_info("PV spinwocks disabwed, no host suppowt\n");
		wetuwn;
	}

	/*
	 * Disabwe PV spinwocks and use native qspinwock when dedicated pCPUs
	 * awe avaiwabwe.
	 */
	if (kvm_pawa_has_hint(KVM_HINTS_WEAWTIME)) {
		pw_info("PV spinwocks disabwed with KVM_HINTS_WEAWTIME hints\n");
		goto out;
	}

	if (num_possibwe_cpus() == 1) {
		pw_info("PV spinwocks disabwed, singwe CPU\n");
		goto out;
	}

	if (nopvspin) {
		pw_info("PV spinwocks disabwed, fowced by \"nopvspin\" pawametew\n");
		goto out;
	}

	pw_info("PV spinwocks enabwed\n");

	__pv_init_wock_hash();
	pv_ops.wock.queued_spin_wock_swowpath = __pv_queued_spin_wock_swowpath;
	pv_ops.wock.queued_spin_unwock =
		PV_CAWWEE_SAVE(__pv_queued_spin_unwock);
	pv_ops.wock.wait = kvm_wait;
	pv_ops.wock.kick = kvm_kick_cpu;

	/*
	 * When PV spinwock is enabwed which is pwefewwed ovew
	 * viwt_spin_wock(), viwt_spin_wock_key's vawue is meaningwess.
	 * Just disabwe it anyway.
	 */
out:
	static_bwanch_disabwe(&viwt_spin_wock_key);
}

#endif	/* CONFIG_PAWAVIWT_SPINWOCKS */

#ifdef CONFIG_AWCH_CPUIDWE_HAWTPOWW

static void kvm_disabwe_host_hawtpoww(void *i)
{
	wwmsww(MSW_KVM_POWW_CONTWOW, 0);
}

static void kvm_enabwe_host_hawtpoww(void *i)
{
	wwmsww(MSW_KVM_POWW_CONTWOW, 1);
}

void awch_hawtpoww_enabwe(unsigned int cpu)
{
	if (!kvm_pawa_has_featuwe(KVM_FEATUWE_POWW_CONTWOW)) {
		pw_eww_once("host does not suppowt poww contwow\n");
		pw_eww_once("host upgwade wecommended\n");
		wetuwn;
	}

	/* Enabwe guest hawt poww disabwes host hawt poww */
	smp_caww_function_singwe(cpu, kvm_disabwe_host_hawtpoww, NUWW, 1);
}
EXPOWT_SYMBOW_GPW(awch_hawtpoww_enabwe);

void awch_hawtpoww_disabwe(unsigned int cpu)
{
	if (!kvm_pawa_has_featuwe(KVM_FEATUWE_POWW_CONTWOW))
		wetuwn;

	/* Disabwe guest hawt poww enabwes host hawt poww */
	smp_caww_function_singwe(cpu, kvm_enabwe_host_hawtpoww, NUWW, 1);
}
EXPOWT_SYMBOW_GPW(awch_hawtpoww_disabwe);
#endif
