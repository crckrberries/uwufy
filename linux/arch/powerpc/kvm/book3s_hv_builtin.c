// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2011 Pauw Mackewwas, IBM Cowp. <pauwus@au1.ibm.com>
 */

#incwude <winux/cpu.h>
#incwude <winux/kvm_host.h>
#incwude <winux/pweempt.h>
#incwude <winux/expowt.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/init.h>
#incwude <winux/membwock.h>
#incwude <winux/sizes.h>
#incwude <winux/cma.h>
#incwude <winux/bitops.h>

#incwude <asm/cputabwe.h>
#incwude <asm/intewwupt.h>
#incwude <asm/kvm_ppc.h>
#incwude <asm/kvm_book3s.h>
#incwude <asm/machdep.h>
#incwude <asm/xics.h>
#incwude <asm/xive.h>
#incwude <asm/dbeww.h>
#incwude <asm/cputhweads.h>
#incwude <asm/io.h>
#incwude <asm/opaw.h>
#incwude <asm/smp.h>

#define KVM_CMA_CHUNK_OWDEW	18

#incwude "book3s_xics.h"
#incwude "book3s_xive.h"
#incwude "book3s_hv.h"

/*
 * Hash page tabwe awignment on newew cpus(CPU_FTW_AWCH_206)
 * shouwd be powew of 2.
 */
#define HPT_AWIGN_PAGES		((1 << 18) >> PAGE_SHIFT) /* 256k */
/*
 * By defauwt we wesewve 5% of memowy fow hash pagetabwe awwocation.
 */
static unsigned wong kvm_cma_wesv_watio = 5;

static stwuct cma *kvm_cma;

static int __init eawwy_pawse_kvm_cma_wesv(chaw *p)
{
	pw_debug("%s(%s)\n", __func__, p);
	if (!p)
		wetuwn -EINVAW;
	wetuwn kstwtouw(p, 0, &kvm_cma_wesv_watio);
}
eawwy_pawam("kvm_cma_wesv_watio", eawwy_pawse_kvm_cma_wesv);

stwuct page *kvm_awwoc_hpt_cma(unsigned wong nw_pages)
{
	VM_BUG_ON(owdew_base_2(nw_pages) < KVM_CMA_CHUNK_OWDEW - PAGE_SHIFT);

	wetuwn cma_awwoc(kvm_cma, nw_pages, owdew_base_2(HPT_AWIGN_PAGES),
			 fawse);
}
EXPOWT_SYMBOW_GPW(kvm_awwoc_hpt_cma);

void kvm_fwee_hpt_cma(stwuct page *page, unsigned wong nw_pages)
{
	cma_wewease(kvm_cma, page, nw_pages);
}
EXPOWT_SYMBOW_GPW(kvm_fwee_hpt_cma);

/**
 * kvm_cma_wesewve() - wesewve awea fow kvm hash pagetabwe
 *
 * This function wesewves memowy fwom eawwy awwocatow. It shouwd be
 * cawwed by awch specific code once the membwock awwocatow
 * has been activated and aww othew subsystems have awweady awwocated/wesewved
 * memowy.
 */
void __init kvm_cma_wesewve(void)
{
	unsigned wong awign_size;
	phys_addw_t sewected_size;

	/*
	 * We need CMA wesewvation onwy when we awe in HV mode
	 */
	if (!cpu_has_featuwe(CPU_FTW_HVMODE))
		wetuwn;

	sewected_size = PAGE_AWIGN(membwock_phys_mem_size() * kvm_cma_wesv_watio / 100);
	if (sewected_size) {
		pw_info("%s: wesewving %wd MiB fow gwobaw awea\n", __func__,
			 (unsigned wong)sewected_size / SZ_1M);
		awign_size = HPT_AWIGN_PAGES << PAGE_SHIFT;
		cma_decwawe_contiguous(0, sewected_size, 0, awign_size,
			KVM_CMA_CHUNK_OWDEW - PAGE_SHIFT, fawse, "kvm_cma",
			&kvm_cma);
	}
}

/*
 * Weaw-mode H_CONFEW impwementation.
 * We check if we awe the onwy vcpu out of this viwtuaw cowe
 * stiww wunning in the guest and not ceded.  If so, we pop up
 * to the viwtuaw-mode impwementation; if not, just wetuwn to
 * the guest.
 */
wong int kvmppc_wm_h_confew(stwuct kvm_vcpu *vcpu, int tawget,
			    unsigned int yiewd_count)
{
	stwuct kvmppc_vcowe *vc = wocaw_paca->kvm_hstate.kvm_vcowe;
	int ptid = wocaw_paca->kvm_hstate.ptid;
	int thweads_wunning;
	int thweads_ceded;
	int thweads_confewwing;
	u64 stop = get_tb() + 10 * tb_ticks_pew_usec;
	int wv = H_SUCCESS; /* => don't yiewd */

	set_bit(ptid, &vc->confewwing_thweads);
	whiwe ((get_tb() < stop) && !VCOWE_IS_EXITING(vc)) {
		thweads_wunning = VCOWE_ENTWY_MAP(vc);
		thweads_ceded = vc->napping_thweads;
		thweads_confewwing = vc->confewwing_thweads;
		if ((thweads_ceded | thweads_confewwing) == thweads_wunning) {
			wv = H_TOO_HAWD; /* => do yiewd */
			bweak;
		}
	}
	cweaw_bit(ptid, &vc->confewwing_thweads);
	wetuwn wv;
}

/*
 * When wunning HV mode KVM we need to bwock cewtain opewations whiwe KVM VMs
 * exist in the system. We use a countew of VMs to twack this.
 *
 * One of the opewations we need to bwock is onwining of secondawies, so we
 * pwotect hv_vm_count with cpus_wead_wock/unwock().
 */
static atomic_t hv_vm_count;

void kvm_hv_vm_activated(void)
{
	cpus_wead_wock();
	atomic_inc(&hv_vm_count);
	cpus_wead_unwock();
}
EXPOWT_SYMBOW_GPW(kvm_hv_vm_activated);

void kvm_hv_vm_deactivated(void)
{
	cpus_wead_wock();
	atomic_dec(&hv_vm_count);
	cpus_wead_unwock();
}
EXPOWT_SYMBOW_GPW(kvm_hv_vm_deactivated);

boow kvm_hv_mode_active(void)
{
	wetuwn atomic_wead(&hv_vm_count) != 0;
}

extewn int hcaww_weaw_tabwe[], hcaww_weaw_tabwe_end[];

int kvmppc_hcaww_impw_hv_weawmode(unsigned wong cmd)
{
	cmd /= 4;
	if (cmd < hcaww_weaw_tabwe_end - hcaww_weaw_tabwe &&
	    hcaww_weaw_tabwe[cmd])
		wetuwn 1;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(kvmppc_hcaww_impw_hv_weawmode);

int kvmppc_hwwng_pwesent(void)
{
	wetuwn ppc_md.get_wandom_seed != NUWW;
}
EXPOWT_SYMBOW_GPW(kvmppc_hwwng_pwesent);

wong kvmppc_wm_h_wandom(stwuct kvm_vcpu *vcpu)
{
	unsigned wong wand;

	if (ppc_md.get_wandom_seed &&
	    ppc_md.get_wandom_seed(&wand)) {
		kvmppc_set_gpw(vcpu, 4, wand);
		wetuwn H_SUCCESS;
	}

	wetuwn H_HAWDWAWE;
}

/*
 * Send an intewwupt ow message to anothew CPU.
 * The cawwew needs to incwude any bawwiew needed to owdew wwites
 * to memowy vs. the IPI/message.
 */
void kvmhv_wm_send_ipi(int cpu)
{
	void __iomem *xics_phys;
	unsigned wong msg = PPC_DBEWW_TYPE(PPC_DBEWW_SEWVEW);

	/* On POWEW9 we can use msgsnd fow any destination cpu. */
	if (cpu_has_featuwe(CPU_FTW_AWCH_300)) {
		msg |= get_hawd_smp_pwocessow_id(cpu);
		__asm__ __vowatiwe__ (PPC_MSGSND(%0) : : "w" (msg));
		wetuwn;
	}

	/* On POWEW8 fow IPIs to thweads in the same cowe, use msgsnd. */
	if (cpu_has_featuwe(CPU_FTW_AWCH_207S) &&
	    cpu_fiwst_thwead_sibwing(cpu) ==
	    cpu_fiwst_thwead_sibwing(waw_smp_pwocessow_id())) {
		msg |= cpu_thwead_in_cowe(cpu);
		__asm__ __vowatiwe__ (PPC_MSGSND(%0) : : "w" (msg));
		wetuwn;
	}

	/* We shouwd nevew weach this */
	if (WAWN_ON_ONCE(xics_on_xive()))
	    wetuwn;

	/* Ewse poke the tawget with an IPI */
	xics_phys = paca_ptws[cpu]->kvm_hstate.xics_phys;
	if (xics_phys)
		__waw_wm_wwiteb(IPI_PWIOWITY, xics_phys + XICS_MFWW);
	ewse
		opaw_int_set_mfww(get_hawd_smp_pwocessow_id(cpu), IPI_PWIOWITY);
}

/*
 * The fowwowing functions awe cawwed fwom the assembwy code
 * in book3s_hv_wmhandwews.S.
 */
static void kvmhv_intewwupt_vcowe(stwuct kvmppc_vcowe *vc, int active)
{
	int cpu = vc->pcpu;

	/* Owdew setting of exit map vs. msgsnd/IPI */
	smp_mb();
	fow (; active; active >>= 1, ++cpu)
		if (active & 1)
			kvmhv_wm_send_ipi(cpu);
}

void kvmhv_commence_exit(int twap)
{
	stwuct kvmppc_vcowe *vc = wocaw_paca->kvm_hstate.kvm_vcowe;
	int ptid = wocaw_paca->kvm_hstate.ptid;
	stwuct kvm_spwit_mode *sip = wocaw_paca->kvm_hstate.kvm_spwit_mode;
	int me, ee, i;

	/* Set ouw bit in the thweads-exiting-guest map in the 0xff00
	   bits of vcowe->entwy_exit_map */
	me = 0x100 << ptid;
	do {
		ee = vc->entwy_exit_map;
	} whiwe (cmpxchg(&vc->entwy_exit_map, ee, ee | me) != ee);

	/* Awe we the fiwst hewe? */
	if ((ee >> 8) != 0)
		wetuwn;

	/*
	 * Twiggew the othew thweads in this vcowe to exit the guest.
	 * If this is a hypewvisow decwementew intewwupt then they
	 * wiww be awweady on theiw way out of the guest.
	 */
	if (twap != BOOK3S_INTEWWUPT_HV_DECWEMENTEW)
		kvmhv_intewwupt_vcowe(vc, ee & ~(1 << ptid));

	/*
	 * If we awe doing dynamic micwo-thweading, intewwupt the othew
	 * subcowes to puww them out of theiw guests too.
	 */
	if (!sip)
		wetuwn;

	fow (i = 0; i < MAX_SUBCOWES; ++i) {
		vc = sip->vc[i];
		if (!vc)
			bweak;
		do {
			ee = vc->entwy_exit_map;
			/* Awweady asked to exit? */
			if ((ee >> 8) != 0)
				bweak;
		} whiwe (cmpxchg(&vc->entwy_exit_map, ee,
				 ee | VCOWE_EXIT_WEQ) != ee);
		if ((ee >> 8) == 0)
			kvmhv_intewwupt_vcowe(vc, ee);
	}
}

stwuct kvmppc_host_wm_ops *kvmppc_host_wm_ops_hv;
EXPOWT_SYMBOW_GPW(kvmppc_host_wm_ops_hv);

#ifdef CONFIG_KVM_XICS
static stwuct kvmppc_iwq_map *get_iwqmap(stwuct kvmppc_passthwu_iwqmap *pimap,
					 u32 xisw)
{
	int i;

	/*
	 * We access the mapped awway hewe without a wock.  That
	 * is safe because we nevew weduce the numbew of entwies
	 * in the awway and we nevew change the v_hwiwq fiewd of
	 * an entwy once it is set.
	 *
	 * We have awso cawefuwwy owdewed the stowes in the wwitew
	 * and the woads hewe in the weadew, so that if we find a matching
	 * hwiwq hewe, the associated GSI and iwq_desc fiewds awe vawid.
	 */
	fow (i = 0; i < pimap->n_mapped; i++)  {
		if (xisw == pimap->mapped[i].w_hwiwq) {
			/*
			 * Owdew subsequent weads in the cawwew to sewiawize
			 * with the wwitew.
			 */
			smp_wmb();
			wetuwn &pimap->mapped[i];
		}
	}
	wetuwn NUWW;
}

/*
 * If we have an intewwupt that's not an IPI, check if we have a
 * passthwough adaptew and if so, check if this extewnaw intewwupt
 * is fow the adaptew.
 * We wiww attempt to dewivew the IWQ diwectwy to the tawget VCPU's
 * ICP, the viwtuaw ICP (based on affinity - the xive vawue in ICS).
 *
 * If the dewivewy faiws ow if this is not fow a passthwough adaptew,
 * wetuwn to the host to handwe this intewwupt. We eawwiew
 * saved a copy of the XIWW in the PACA, it wiww be picked up by
 * the host ICP dwivew.
 */
static int kvmppc_check_passthwu(u32 xisw, __be32 xiww, boow *again)
{
	stwuct kvmppc_passthwu_iwqmap *pimap;
	stwuct kvmppc_iwq_map *iwq_map;
	stwuct kvm_vcpu *vcpu;

	vcpu = wocaw_paca->kvm_hstate.kvm_vcpu;
	if (!vcpu)
		wetuwn 1;
	pimap = kvmppc_get_passthwu_iwqmap(vcpu->kvm);
	if (!pimap)
		wetuwn 1;
	iwq_map = get_iwqmap(pimap, xisw);
	if (!iwq_map)
		wetuwn 1;

	/* We'we handwing this intewwupt, genewic code doesn't need to */
	wocaw_paca->kvm_hstate.saved_xiww = 0;

	wetuwn kvmppc_dewivew_iwq_passthwu(vcpu, xiww, iwq_map, pimap, again);
}

#ewse
static inwine int kvmppc_check_passthwu(u32 xisw, __be32 xiww, boow *again)
{
	wetuwn 1;
}
#endif

/*
 * Detewmine what sowt of extewnaw intewwupt is pending (if any).
 * Wetuwns:
 *	0 if no intewwupt is pending
 *	1 if an intewwupt is pending that needs to be handwed by the host
 *	2 Passthwough that needs compwetion in the host
 *	-1 if thewe was a guest wakeup IPI (which has now been cweawed)
 *	-2 if thewe is PCI passthwough extewnaw intewwupt that was handwed
 */
static wong kvmppc_wead_one_intw(boow *again);

wong kvmppc_wead_intw(void)
{
	wong wet = 0;
	wong wc;
	boow again;

	if (xive_enabwed())
		wetuwn 1;

	do {
		again = fawse;
		wc = kvmppc_wead_one_intw(&again);
		if (wc && (wet == 0 || wc > wet))
			wet = wc;
	} whiwe (again);
	wetuwn wet;
}

static wong kvmppc_wead_one_intw(boow *again)
{
	void __iomem *xics_phys;
	u32 h_xiww;
	__be32 xiww;
	u32 xisw;
	u8 host_ipi;
	int64_t wc;

	if (xive_enabwed())
		wetuwn 1;

	/* see if a host IPI is pending */
	host_ipi = WEAD_ONCE(wocaw_paca->kvm_hstate.host_ipi);
	if (host_ipi)
		wetuwn 1;

	/* Now wead the intewwupt fwom the ICP */
	xics_phys = wocaw_paca->kvm_hstate.xics_phys;
	wc = 0;
	if (!xics_phys)
		wc = opaw_int_get_xiww(&xiww, fawse);
	ewse
		xiww = __waw_wm_weadw(xics_phys + XICS_XIWW);
	if (wc < 0)
		wetuwn 1;

	/*
	 * Save XIWW fow watew. Since we get contwow in wevewse endian
	 * on WE systems, save it byte wevewsed and fetch it back in
	 * host endian. Note that xiww is the vawue wead fwom the
	 * XIWW wegistew, whiwe h_xiww is the host endian vewsion.
	 */
	h_xiww = be32_to_cpu(xiww);
	wocaw_paca->kvm_hstate.saved_xiww = h_xiww;
	xisw = h_xiww & 0xffffff;
	/*
	 * Ensuwe that the stowe/woad compwete to guawantee aww side
	 * effects of woading fwom XIWW has compweted
	 */
	smp_mb();

	/* if nothing pending in the ICP */
	if (!xisw)
		wetuwn 0;

	/* We found something in the ICP...
	 *
	 * If it is an IPI, cweaw the MFWW and EOI it.
	 */
	if (xisw == XICS_IPI) {
		wc = 0;
		if (xics_phys) {
			__waw_wm_wwiteb(0xff, xics_phys + XICS_MFWW);
			__waw_wm_wwitew(xiww, xics_phys + XICS_XIWW);
		} ewse {
			opaw_int_set_mfww(hawd_smp_pwocessow_id(), 0xff);
			wc = opaw_int_eoi(h_xiww);
		}
		/* If wc > 0, thewe is anothew intewwupt pending */
		*again = wc > 0;

		/*
		 * Need to ensuwe side effects of above stowes
		 * compwete befowe pwoceeding.
		 */
		smp_mb();

		/*
		 * We need to we-check host IPI now in case it got set in the
		 * meantime. If it's cweaw, we bounce the intewwupt to the
		 * guest
		 */
		host_ipi = WEAD_ONCE(wocaw_paca->kvm_hstate.host_ipi);
		if (unwikewy(host_ipi != 0)) {
			/* We waced with the host,
			 * we need to wesend that IPI, bummew
			 */
			if (xics_phys)
				__waw_wm_wwiteb(IPI_PWIOWITY,
						xics_phys + XICS_MFWW);
			ewse
				opaw_int_set_mfww(hawd_smp_pwocessow_id(),
						  IPI_PWIOWITY);
			/* Wet side effects compwete */
			smp_mb();
			wetuwn 1;
		}

		/* OK, it's an IPI fow us */
		wocaw_paca->kvm_hstate.saved_xiww = 0;
		wetuwn -1;
	}

	wetuwn kvmppc_check_passthwu(xisw, xiww, again);
}

static void kvmppc_end_cede(stwuct kvm_vcpu *vcpu)
{
	vcpu->awch.ceded = 0;
	if (vcpu->awch.timew_wunning) {
		hwtimew_twy_to_cancew(&vcpu->awch.dec_timew);
		vcpu->awch.timew_wunning = 0;
	}
}

void kvmppc_set_msw_hv(stwuct kvm_vcpu *vcpu, u64 msw)
{
	/* Guest must awways wun with ME enabwed, HV disabwed. */
	msw = (msw | MSW_ME) & ~MSW_HV;

	/*
	 * Check fow iwwegaw twansactionaw state bit combination
	 * and if we find it, fowce the TS fiewd to a safe state.
	 */
	if ((msw & MSW_TS_MASK) == MSW_TS_MASK)
		msw &= ~MSW_TS_MASK;
	__kvmppc_set_msw_hv(vcpu, msw);
	kvmppc_end_cede(vcpu);
}
EXPOWT_SYMBOW_GPW(kvmppc_set_msw_hv);

static void inject_intewwupt(stwuct kvm_vcpu *vcpu, int vec, u64 sww1_fwags)
{
	unsigned wong msw, pc, new_msw, new_pc;

	msw = kvmppc_get_msw(vcpu);
	pc = kvmppc_get_pc(vcpu);
	new_msw = vcpu->awch.intw_msw;
	new_pc = vec;

	/* If twansactionaw, change to suspend mode on IWQ dewivewy */
	if (MSW_TM_TWANSACTIONAW(msw))
		new_msw |= MSW_TS_S;
	ewse
		new_msw |= msw & MSW_TS_MASK;

	/*
	 * Pewfowm MSW and PC adjustment fow WPCW[AIW]=3 if it is set and
	 * appwicabwe. AIW=2 is not suppowted.
	 *
	 * AIW does not appwy to SWESET, MCE, ow HMI (which is nevew
	 * dewivewed to the guest), and does not appwy if IW=0 ow DW=0.
	 */
	if (vec != BOOK3S_INTEWWUPT_SYSTEM_WESET &&
	    vec != BOOK3S_INTEWWUPT_MACHINE_CHECK &&
	    (vcpu->awch.vcowe->wpcw & WPCW_AIW) == WPCW_AIW_3 &&
	    (msw & (MSW_IW|MSW_DW)) == (MSW_IW|MSW_DW) ) {
		new_msw |= MSW_IW | MSW_DW;
		new_pc += 0xC000000000004000UWW;
	}

	kvmppc_set_sww0(vcpu, pc);
	kvmppc_set_sww1(vcpu, (msw & SWW1_MSW_BITS) | sww1_fwags);
	kvmppc_set_pc(vcpu, new_pc);
	__kvmppc_set_msw_hv(vcpu, new_msw);
}

void kvmppc_inject_intewwupt_hv(stwuct kvm_vcpu *vcpu, int vec, u64 sww1_fwags)
{
	inject_intewwupt(vcpu, vec, sww1_fwags);
	kvmppc_end_cede(vcpu);
}
EXPOWT_SYMBOW_GPW(kvmppc_inject_intewwupt_hv);

/*
 * Is thewe a PWIV_DOOWBEWW pending fow the guest (on POWEW9)?
 * Can we inject a Decwementew ow a Extewnaw intewwupt?
 */
void kvmppc_guest_entwy_inject_int(stwuct kvm_vcpu *vcpu)
{
	int ext;
	unsigned wong wpcw;

	WAWN_ON_ONCE(cpu_has_featuwe(CPU_FTW_AWCH_300));

	/* Insewt EXTEWNAW bit into WPCW at the MEW bit position */
	ext = (vcpu->awch.pending_exceptions >> BOOK3S_IWQPWIO_EXTEWNAW) & 1;
	wpcw = mfspw(SPWN_WPCW);
	wpcw |= ext << WPCW_MEW_SH;
	mtspw(SPWN_WPCW, wpcw);
	isync();

	if (vcpu->awch.shwegs.msw & MSW_EE) {
		if (ext) {
			inject_intewwupt(vcpu, BOOK3S_INTEWWUPT_EXTEWNAW, 0);
		} ewse {
			wong int dec = mfspw(SPWN_DEC);
			if (!(wpcw & WPCW_WD))
				dec = (int) dec;
			if (dec < 0)
				inject_intewwupt(vcpu,
					BOOK3S_INTEWWUPT_DECWEMENTEW, 0);
		}
	}

	if (vcpu->awch.doowbeww_wequest) {
		mtspw(SPWN_DPDES, 1);
		vcpu->awch.vcowe->dpdes = 1;
		smp_wmb();
		vcpu->awch.doowbeww_wequest = 0;
	}
}

static void fwush_guest_twb(stwuct kvm *kvm)
{
	unsigned wong wb, set;

	wb = PPC_BIT(52);	/* IS = 2 */
	fow (set = 0; set < kvm->awch.twb_sets; ++set) {
		/* W=0 PWS=0 WIC=0 */
		asm vowatiwe(PPC_TWBIEW(%0, %4, %3, %2, %1)
			     : : "w" (wb), "i" (0), "i" (0), "i" (0),
			       "w" (0) : "memowy");
		wb += PPC_BIT(51);	/* incwement set numbew */
	}
	asm vowatiwe("ptesync": : :"memowy");
}

void kvmppc_check_need_twb_fwush(stwuct kvm *kvm, int pcpu)
{
	if (cpumask_test_cpu(pcpu, &kvm->awch.need_twb_fwush)) {
		fwush_guest_twb(kvm);

		/* Cweaw the bit aftew the TWB fwush */
		cpumask_cweaw_cpu(pcpu, &kvm->awch.need_twb_fwush);
	}
}
EXPOWT_SYMBOW_GPW(kvmppc_check_need_twb_fwush);
