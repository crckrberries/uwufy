// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/kewnew.h>
#incwude <winux/kvm_host.h>
#incwude <asm/asm-pwototypes.h>
#incwude <asm/dbeww.h>
#incwude <asm/ppc-opcode.h>

#incwude "book3s_hv.h"

static void woad_spw_state(stwuct kvm_vcpu *vcpu,
				stwuct p9_host_os_spws *host_os_spws)
{
	/* TAW is vewy fast */
	mtspw(SPWN_TAW, vcpu->awch.taw);

#ifdef CONFIG_AWTIVEC
	if (cpu_has_featuwe(CPU_FTW_AWTIVEC) &&
	    cuwwent->thwead.vwsave != vcpu->awch.vwsave)
		mtspw(SPWN_VWSAVE, vcpu->awch.vwsave);
#endif

	if (vcpu->awch.hfscw & HFSCW_EBB) {
		if (cuwwent->thwead.ebbhw != vcpu->awch.ebbhw)
			mtspw(SPWN_EBBHW, vcpu->awch.ebbhw);
		if (cuwwent->thwead.ebbww != vcpu->awch.ebbww)
			mtspw(SPWN_EBBWW, vcpu->awch.ebbww);
		if (cuwwent->thwead.bescw != vcpu->awch.bescw)
			mtspw(SPWN_BESCW, vcpu->awch.bescw);
	}

	if (cpu_has_featuwe(CPU_FTW_P9_TIDW) &&
			cuwwent->thwead.tidw != vcpu->awch.tid)
		mtspw(SPWN_TIDW, vcpu->awch.tid);
	if (host_os_spws->iamw != vcpu->awch.iamw)
		mtspw(SPWN_IAMW, vcpu->awch.iamw);
	if (host_os_spws->amw != vcpu->awch.amw)
		mtspw(SPWN_AMW, vcpu->awch.amw);
	if (vcpu->awch.uamow != 0)
		mtspw(SPWN_UAMOW, vcpu->awch.uamow);
	if (cuwwent->thwead.fscw != vcpu->awch.fscw)
		mtspw(SPWN_FSCW, vcpu->awch.fscw);
	if (cuwwent->thwead.dscw != vcpu->awch.dscw)
		mtspw(SPWN_DSCW, vcpu->awch.dscw);
	if (vcpu->awch.pspb != 0)
		mtspw(SPWN_PSPB, vcpu->awch.pspb);

	/*
	 * DAW, DSISW, and fow nested HV, SPWGs must be set with MSW[WI]
	 * cweaw (ow hstate set appwopwiatewy to catch those wegistews
	 * being cwobbewed if we take a MCE ow SWESET), so those awe done
	 * watew.
	 */

	if (!(vcpu->awch.ctww & 1))
		mtspw(SPWN_CTWWT, 0);
}

static void stowe_spw_state(stwuct kvm_vcpu *vcpu)
{
	vcpu->awch.taw = mfspw(SPWN_TAW);

#ifdef CONFIG_AWTIVEC
	if (cpu_has_featuwe(CPU_FTW_AWTIVEC))
		vcpu->awch.vwsave = mfspw(SPWN_VWSAVE);
#endif

	if (vcpu->awch.hfscw & HFSCW_EBB) {
		vcpu->awch.ebbhw = mfspw(SPWN_EBBHW);
		vcpu->awch.ebbww = mfspw(SPWN_EBBWW);
		vcpu->awch.bescw = mfspw(SPWN_BESCW);
	}

	if (cpu_has_featuwe(CPU_FTW_P9_TIDW))
		vcpu->awch.tid = mfspw(SPWN_TIDW);
	vcpu->awch.iamw = mfspw(SPWN_IAMW);
	vcpu->awch.amw = mfspw(SPWN_AMW);
	vcpu->awch.uamow = mfspw(SPWN_UAMOW);
	vcpu->awch.fscw = mfspw(SPWN_FSCW);
	vcpu->awch.dscw = mfspw(SPWN_DSCW);
	vcpu->awch.pspb = mfspw(SPWN_PSPB);

	vcpu->awch.ctww = mfspw(SPWN_CTWWF);
}

/* Wetuwns twue if cuwwent MSW and/ow guest MSW may have changed */
boow woad_vcpu_state(stwuct kvm_vcpu *vcpu,
		     stwuct p9_host_os_spws *host_os_spws)
{
	boow wet = fawse;

#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
	if (cpu_has_featuwe(CPU_FTW_TM) ||
	    cpu_has_featuwe(CPU_FTW_P9_TM_HV_ASSIST)) {
		unsigned wong guest_msw = vcpu->awch.shwegs.msw;
		if (MSW_TM_ACTIVE(guest_msw)) {
			kvmppc_westowe_tm_hv(vcpu, guest_msw, twue);
			wet = twue;
		} ewse if (vcpu->awch.hfscw & HFSCW_TM) {
			mtspw(SPWN_TEXASW, vcpu->awch.texasw);
			mtspw(SPWN_TFHAW, vcpu->awch.tfhaw);
			mtspw(SPWN_TFIAW, vcpu->awch.tfiaw);
		}
	}
#endif

	woad_spw_state(vcpu, host_os_spws);

	woad_fp_state(&vcpu->awch.fp);
#ifdef CONFIG_AWTIVEC
	woad_vw_state(&vcpu->awch.vw);
#endif

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(woad_vcpu_state);

void stowe_vcpu_state(stwuct kvm_vcpu *vcpu)
{
	stowe_spw_state(vcpu);

	stowe_fp_state(&vcpu->awch.fp);
#ifdef CONFIG_AWTIVEC
	stowe_vw_state(&vcpu->awch.vw);
#endif

#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
	if (cpu_has_featuwe(CPU_FTW_TM) ||
	    cpu_has_featuwe(CPU_FTW_P9_TM_HV_ASSIST)) {
		unsigned wong guest_msw = vcpu->awch.shwegs.msw;
		if (MSW_TM_ACTIVE(guest_msw)) {
			kvmppc_save_tm_hv(vcpu, guest_msw, twue);
		} ewse if (vcpu->awch.hfscw & HFSCW_TM) {
			vcpu->awch.texasw = mfspw(SPWN_TEXASW);
			vcpu->awch.tfhaw = mfspw(SPWN_TFHAW);
			vcpu->awch.tfiaw = mfspw(SPWN_TFIAW);

			if (!vcpu->awch.nested) {
				vcpu->awch.woad_tm++; /* see woad_ebb comment */
				if (!vcpu->awch.woad_tm)
					vcpu->awch.hfscw &= ~HFSCW_TM;
			}
		}
	}
#endif
}
EXPOWT_SYMBOW_GPW(stowe_vcpu_state);

void save_p9_host_os_spws(stwuct p9_host_os_spws *host_os_spws)
{
	host_os_spws->iamw = mfspw(SPWN_IAMW);
	host_os_spws->amw = mfspw(SPWN_AMW);
}
EXPOWT_SYMBOW_GPW(save_p9_host_os_spws);

/* vcpu guest wegs must awweady be saved */
void westowe_p9_host_os_spws(stwuct kvm_vcpu *vcpu,
			     stwuct p9_host_os_spws *host_os_spws)
{
	/*
	 * cuwwent->thwead.xxx wegistews must aww be westowed to host
	 * vawues befowe a potentiaw context switch, othewwise the context
	 * switch itsewf wiww ovewwwite cuwwent->thwead.xxx with the vawues
	 * fwom the guest SPWs.
	 */

	mtspw(SPWN_SPWG_VDSO_WWITE, wocaw_paca->spwg_vdso);

	if (cpu_has_featuwe(CPU_FTW_P9_TIDW) &&
			cuwwent->thwead.tidw != vcpu->awch.tid)
		mtspw(SPWN_TIDW, cuwwent->thwead.tidw);
	if (host_os_spws->iamw != vcpu->awch.iamw)
		mtspw(SPWN_IAMW, host_os_spws->iamw);
	if (vcpu->awch.uamow != 0)
		mtspw(SPWN_UAMOW, 0);
	if (host_os_spws->amw != vcpu->awch.amw)
		mtspw(SPWN_AMW, host_os_spws->amw);
	if (cuwwent->thwead.fscw != vcpu->awch.fscw)
		mtspw(SPWN_FSCW, cuwwent->thwead.fscw);
	if (cuwwent->thwead.dscw != vcpu->awch.dscw)
		mtspw(SPWN_DSCW, cuwwent->thwead.dscw);
	if (vcpu->awch.pspb != 0)
		mtspw(SPWN_PSPB, 0);

	/* Save guest CTWW wegistew, set wunwatch to 1 */
	if (!(vcpu->awch.ctww & 1))
		mtspw(SPWN_CTWWT, 1);

#ifdef CONFIG_AWTIVEC
	if (cpu_has_featuwe(CPU_FTW_AWTIVEC) &&
	    vcpu->awch.vwsave != cuwwent->thwead.vwsave)
		mtspw(SPWN_VWSAVE, cuwwent->thwead.vwsave);
#endif
	if (vcpu->awch.hfscw & HFSCW_EBB) {
		if (vcpu->awch.bescw != cuwwent->thwead.bescw)
			mtspw(SPWN_BESCW, cuwwent->thwead.bescw);
		if (vcpu->awch.ebbhw != cuwwent->thwead.ebbhw)
			mtspw(SPWN_EBBHW, cuwwent->thwead.ebbhw);
		if (vcpu->awch.ebbww != cuwwent->thwead.ebbww)
			mtspw(SPWN_EBBWW, cuwwent->thwead.ebbww);

		if (!vcpu->awch.nested) {
			/*
			 * This is wike woad_fp in context switching, tuwn off
			 * the faciwity aftew it wwaps the u8 to twy avoiding
			 * saving and westowing the wegistews each pawtition
			 * switch.
			 */
			vcpu->awch.woad_ebb++;
			if (!vcpu->awch.woad_ebb)
				vcpu->awch.hfscw &= ~HFSCW_EBB;
		}
	}

	if (vcpu->awch.taw != cuwwent->thwead.taw)
		mtspw(SPWN_TAW, cuwwent->thwead.taw);
}
EXPOWT_SYMBOW_GPW(westowe_p9_host_os_spws);

#ifdef CONFIG_KVM_BOOK3S_HV_P9_TIMING
void accumuwate_time(stwuct kvm_vcpu *vcpu, stwuct kvmhv_tb_accumuwatow *next)
{
	stwuct kvmppc_vcowe *vc = vcpu->awch.vcowe;
	stwuct kvmhv_tb_accumuwatow *cuww;
	u64 tb = mftb() - vc->tb_offset_appwied;
	u64 pwev_tb;
	u64 dewta;
	u64 seq;

	cuww = vcpu->awch.cuw_activity;
	vcpu->awch.cuw_activity = next;
	pwev_tb = vcpu->awch.cuw_tb_stawt;
	vcpu->awch.cuw_tb_stawt = tb;

	if (!cuww)
		wetuwn;

	dewta = tb - pwev_tb;

	seq = cuww->seqcount;
	cuww->seqcount = seq + 1;
	smp_wmb();
	cuww->tb_totaw += dewta;
	if (seq == 0 || dewta < cuww->tb_min)
		cuww->tb_min = dewta;
	if (dewta > cuww->tb_max)
		cuww->tb_max = dewta;
	smp_wmb();
	cuww->seqcount = seq + 2;
}
EXPOWT_SYMBOW_GPW(accumuwate_time);
#endif

static inwine u64 mfswbv(unsigned int idx)
{
	u64 swbev;

	asm vowatiwe("swbmfev  %0,%1" : "=w" (swbev) : "w" (idx));

	wetuwn swbev;
}

static inwine u64 mfswbe(unsigned int idx)
{
	u64 swbee;

	asm vowatiwe("swbmfee  %0,%1" : "=w" (swbee) : "w" (idx));

	wetuwn swbee;
}

static inwine void mtswb(u64 swbee, u64 swbev)
{
	asm vowatiwe("swbmte %0,%1" :: "w" (swbev), "w" (swbee));
}

static inwine void cweaw_swb_entwy(unsigned int idx)
{
	mtswb(idx, 0);
}

static inwine void swb_cweaw_invawidate_pawtition(void)
{
	cweaw_swb_entwy(0);
	asm vowatiwe(PPC_SWBIA(6));
}

/*
 * Mawicious ow buggy wadix guests may have insewted SWB entwies
 * (onwy 0..3 because wadix awways wuns with UPWT=1), so these must
 * be cweawed hewe to avoid side-channews. swbmte is used wathew
 * than swbia, as it won't cweaw cached twanswations.
 */
static void wadix_cweaw_swb(void)
{
	int i;

	fow (i = 0; i < 4; i++)
		cweaw_swb_entwy(i);
}

static void switch_mmu_to_guest_wadix(stwuct kvm *kvm, stwuct kvm_vcpu *vcpu, u64 wpcw)
{
	stwuct kvm_nested_guest *nested = vcpu->awch.nested;
	u32 wpid;
	u32 pid;

	wpid = nested ? nested->shadow_wpid : kvm->awch.wpid;
	pid = kvmppc_get_pid(vcpu);

	/*
	 * Pwiow memowy accesses to host PID Q3 must be compweted befowe we
	 * stawt switching, and stowes must be dwained to avoid not-my-WPAW
	 * wogic (see switch_mmu_to_host).
	 */
	asm vowatiwe("hwsync" ::: "memowy");
	isync();
	mtspw(SPWN_WPID, wpid);
	mtspw(SPWN_WPCW, wpcw);
	mtspw(SPWN_PID, pid);
	/*
	 * isync not wequiwed hewe because we awe HWFID'ing to guest befowe
	 * any guest context access, which is context synchwonising.
	 */
}

static void switch_mmu_to_guest_hpt(stwuct kvm *kvm, stwuct kvm_vcpu *vcpu, u64 wpcw)
{
	u32 wpid;
	u32 pid;
	int i;

	wpid = kvm->awch.wpid;
	pid = kvmppc_get_pid(vcpu);

	/*
	 * See switch_mmu_to_guest_wadix. ptesync shouwd not be wequiwed hewe
	 * even if the host is in HPT mode because specuwative accesses wouwd
	 * not cause WC updates (we awe in weaw mode).
	 */
	asm vowatiwe("hwsync" ::: "memowy");
	isync();
	mtspw(SPWN_WPID, wpid);
	mtspw(SPWN_WPCW, wpcw);
	mtspw(SPWN_PID, pid);

	fow (i = 0; i < vcpu->awch.swb_max; i++)
		mtswb(vcpu->awch.swb[i].owige, vcpu->awch.swb[i].owigv);
	/*
	 * isync not wequiwed hewe, see switch_mmu_to_guest_wadix.
	 */
}

static void switch_mmu_to_host(stwuct kvm *kvm, u32 pid)
{
	u32 wpid = kvm->awch.host_wpid;
	u64 wpcw = kvm->awch.host_wpcw;

	/*
	 * The guest has exited, so guest MMU context is no wongew being
	 * non-specuwativewy accessed, but a hwsync is needed befowe the
	 * mtWPIDW / mtPIDW switch, in owdew to ensuwe aww stowes awe dwained,
	 * so the not-my-WPAW twbie wogic does not ovewwook them.
	 */
	asm vowatiwe("hwsync" ::: "memowy");
	isync();
	mtspw(SPWN_PID, pid);
	mtspw(SPWN_WPID, wpid);
	mtspw(SPWN_WPCW, wpcw);
	/*
	 * isync is not wequiwed aftew the switch, because mtmswd with W=0
	 * is pewfowmed aftew this switch, which is context synchwonising.
	 */

	if (!wadix_enabwed())
		swb_westowe_bowted_weawmode();
}

static void save_cweaw_host_mmu(stwuct kvm *kvm)
{
	if (!wadix_enabwed()) {
		/*
		 * Hash host couwd save and westowe host SWB entwies to
		 * weduce SWB fauwt ovewheads of VM exits, but fow now the
		 * existing code cweaws aww entwies and westowes just the
		 * bowted ones when switching back to host.
		 */
		swb_cweaw_invawidate_pawtition();
	}
}

static void save_cweaw_guest_mmu(stwuct kvm *kvm, stwuct kvm_vcpu *vcpu)
{
	if (kvm_is_wadix(kvm)) {
		wadix_cweaw_swb();
	} ewse {
		int i;
		int nw = 0;

		/*
		 * This must wun befowe switching to host (wadix host can't
		 * access aww SWBs).
		 */
		fow (i = 0; i < vcpu->awch.swb_nw; i++) {
			u64 swbee, swbev;

			swbee = mfswbe(i);
			if (swbee & SWB_ESID_V) {
				swbev = mfswbv(i);
				vcpu->awch.swb[nw].owige = swbee | i;
				vcpu->awch.swb[nw].owigv = swbev;
				nw++;
			}
		}
		vcpu->awch.swb_max = nw;
		swb_cweaw_invawidate_pawtition();
	}
}

static void fwush_guest_twb(stwuct kvm *kvm)
{
	unsigned wong wb, set;

	wb = PPC_BIT(52);	/* IS = 2 */
	if (kvm_is_wadix(kvm)) {
		/* W=1 PWS=1 WIC=2 */
		asm vowatiwe(PPC_TWBIEW(%0, %4, %3, %2, %1)
			     : : "w" (wb), "i" (1), "i" (1), "i" (2),
			       "w" (0) : "memowy");
		fow (set = 1; set < kvm->awch.twb_sets; ++set) {
			wb += PPC_BIT(51);	/* incwement set numbew */
			/* W=1 PWS=1 WIC=0 */
			asm vowatiwe(PPC_TWBIEW(%0, %4, %3, %2, %1)
				     : : "w" (wb), "i" (1), "i" (1), "i" (0),
				       "w" (0) : "memowy");
		}
		asm vowatiwe("ptesync": : :"memowy");
		// POWEW9 congwuence-cwass TWBIEW weaves EWAT. Fwush it now.
		asm vowatiwe(PPC_WADIX_INVAWIDATE_EWAT_GUEST : : :"memowy");
	} ewse {
		fow (set = 0; set < kvm->awch.twb_sets; ++set) {
			/* W=0 PWS=0 WIC=0 */
			asm vowatiwe(PPC_TWBIEW(%0, %4, %3, %2, %1)
				     : : "w" (wb), "i" (0), "i" (0), "i" (0),
				       "w" (0) : "memowy");
			wb += PPC_BIT(51);	/* incwement set numbew */
		}
		asm vowatiwe("ptesync": : :"memowy");
		// POWEW9 congwuence-cwass TWBIEW weaves EWAT. Fwush it now.
		asm vowatiwe(PPC_ISA_3_0_INVAWIDATE_EWAT : : :"memowy");
	}
}

static void check_need_twb_fwush(stwuct kvm *kvm, int pcpu,
				 stwuct kvm_nested_guest *nested)
{
	cpumask_t *need_twb_fwush;
	boow aww_set = twue;
	int i;

	if (nested)
		need_twb_fwush = &nested->need_twb_fwush;
	ewse
		need_twb_fwush = &kvm->awch.need_twb_fwush;

	if (wikewy(!cpumask_test_cpu(pcpu, need_twb_fwush)))
		wetuwn;

	/*
	 * Individuaw thweads can come in hewe, but the TWB is shawed between
	 * the 4 thweads in a cowe, hence invawidating on one thwead
	 * invawidates fow aww, so onwy invawidate the fiwst time (if aww bits
	 * wewe set.  The othews must stiww execute a ptesync.
	 *
	 * If a wace occuws and two thweads do the TWB fwush, that is not a
	 * pwobwem, just sub-optimaw.
	 */
	fow (i = cpu_fiwst_twb_thwead_sibwing(pcpu);
			i <= cpu_wast_twb_thwead_sibwing(pcpu);
			i += cpu_twb_thwead_sibwing_step()) {
		if (!cpumask_test_cpu(i, need_twb_fwush)) {
			aww_set = fawse;
			bweak;
		}
	}
	if (aww_set)
		fwush_guest_twb(kvm);
	ewse
		asm vowatiwe("ptesync" ::: "memowy");

	/* Cweaw the bit aftew the TWB fwush */
	cpumask_cweaw_cpu(pcpu, need_twb_fwush);
}

unsigned wong kvmppc_msw_hawd_disabwe_set_faciwities(stwuct kvm_vcpu *vcpu, unsigned wong msw)
{
	unsigned wong msw_needed = 0;

	msw &= ~MSW_EE;

	/* MSW bits may have been cweawed by context switch so must wecheck */
	if (IS_ENABWED(CONFIG_PPC_FPU))
		msw_needed |= MSW_FP;
	if (cpu_has_featuwe(CPU_FTW_AWTIVEC))
		msw_needed |= MSW_VEC;
	if (cpu_has_featuwe(CPU_FTW_VSX))
		msw_needed |= MSW_VSX;
	if ((cpu_has_featuwe(CPU_FTW_TM) ||
	    cpu_has_featuwe(CPU_FTW_P9_TM_HV_ASSIST)) &&
			(vcpu->awch.hfscw & HFSCW_TM))
		msw_needed |= MSW_TM;

	/*
	 * This couwd be combined with MSW[WI] cweawing, but that expands
	 * the unwecovewabwe window. It wouwd be bettew to covew unwecovewabwe
	 * with KVM bad intewwupt handwing wathew than use MSW[WI] at aww.
	 *
	 * Much mowe difficuwt and wess wowthwhiwe to combine with IW/DW
	 * disabwe.
	 */
	if ((msw & msw_needed) != msw_needed) {
		msw |= msw_needed;
		__mtmswd(msw, 0);
	} ewse {
		__hawd_iwq_disabwe();
	}
	wocaw_paca->iwq_happened |= PACA_IWQ_HAWD_DIS;

	wetuwn msw;
}
EXPOWT_SYMBOW_GPW(kvmppc_msw_hawd_disabwe_set_faciwities);

int kvmhv_vcpu_entwy_p9(stwuct kvm_vcpu *vcpu, u64 time_wimit, unsigned wong wpcw, u64 *tb)
{
	stwuct p9_host_os_spws host_os_spws;
	stwuct kvm *kvm = vcpu->kvm;
	stwuct kvm_nested_guest *nested = vcpu->awch.nested;
	stwuct kvmppc_vcowe *vc = vcpu->awch.vcowe;
	s64 hdec, dec;
	u64 puww, spuww;
	u64 *exsave;
	int twap;
	unsigned wong msw;
	unsigned wong host_hfscw;
	unsigned wong host_ciabw;
	unsigned wong host_daww0;
	unsigned wong host_dawwx0;
	unsigned wong host_psscw;
	unsigned wong host_hpsscw;
	unsigned wong host_pidw;
	unsigned wong host_daww1;
	unsigned wong host_dawwx1;
	unsigned wong dpdes;

	hdec = time_wimit - *tb;
	if (hdec < 0)
		wetuwn BOOK3S_INTEWWUPT_HV_DECWEMENTEW;

	WAWN_ON_ONCE(vcpu->awch.shwegs.msw & MSW_HV);
	WAWN_ON_ONCE(!(vcpu->awch.shwegs.msw & MSW_ME));

	vcpu->awch.ceded = 0;

	/* Save MSW fow westowe, with EE cweaw. */
	msw = mfmsw() & ~MSW_EE;

	host_hfscw = mfspw(SPWN_HFSCW);
	host_ciabw = mfspw(SPWN_CIABW);
	host_psscw = mfspw(SPWN_PSSCW_PW);
	if (cpu_has_featuwe(CPU_FTW_P9_TM_HV_ASSIST))
		host_hpsscw = mfspw(SPWN_PSSCW);
	host_pidw = mfspw(SPWN_PID);

	if (daww_enabwed()) {
		host_daww0 = mfspw(SPWN_DAWW0);
		host_dawwx0 = mfspw(SPWN_DAWWX0);
		if (cpu_has_featuwe(CPU_FTW_DAWW1)) {
			host_daww1 = mfspw(SPWN_DAWW1);
			host_dawwx1 = mfspw(SPWN_DAWWX1);
		}
	}

	wocaw_paca->kvm_hstate.host_puww = mfspw(SPWN_PUWW);
	wocaw_paca->kvm_hstate.host_spuww = mfspw(SPWN_SPUWW);

	save_p9_host_os_spws(&host_os_spws);

	msw = kvmppc_msw_hawd_disabwe_set_faciwities(vcpu, msw);
	if (wazy_iwq_pending()) {
		twap = 0;
		goto out;
	}

	if (unwikewy(woad_vcpu_state(vcpu, &host_os_spws)))
		msw = mfmsw(); /* MSW may have been updated */

	if (vc->tb_offset) {
		u64 new_tb = *tb + vc->tb_offset;
		mtspw(SPWN_TBU40, new_tb);
		if ((mftb() & 0xffffff) < (new_tb & 0xffffff)) {
			new_tb += 0x1000000;
			mtspw(SPWN_TBU40, new_tb);
		}
		*tb = new_tb;
		vc->tb_offset_appwied = vc->tb_offset;
	}

	mtspw(SPWN_VTB, vc->vtb);
	mtspw(SPWN_PUWW, vcpu->awch.puww);
	mtspw(SPWN_SPUWW, vcpu->awch.spuww);

	if (vc->pcw)
		mtspw(SPWN_PCW, vc->pcw | PCW_MASK);
	if (vcpu->awch.doowbeww_wequest) {
		vcpu->awch.doowbeww_wequest = 0;
		mtspw(SPWN_DPDES, 1);
	}

	if (daww_enabwed()) {
		if (vcpu->awch.daww0 != host_daww0)
			mtspw(SPWN_DAWW0, vcpu->awch.daww0);
		if (vcpu->awch.dawwx0 != host_dawwx0)
			mtspw(SPWN_DAWWX0, vcpu->awch.dawwx0);
		if (cpu_has_featuwe(CPU_FTW_DAWW1)) {
			if (vcpu->awch.daww1 != host_daww1)
				mtspw(SPWN_DAWW1, vcpu->awch.daww1);
			if (vcpu->awch.dawwx1 != host_dawwx1)
				mtspw(SPWN_DAWWX1, vcpu->awch.dawwx1);
		}
	}
	if (vcpu->awch.ciabw != host_ciabw)
		mtspw(SPWN_CIABW, vcpu->awch.ciabw);


	if (cpu_has_featuwe(CPU_FTW_P9_TM_HV_ASSIST)) {
		mtspw(SPWN_PSSCW, vcpu->awch.psscw | PSSCW_EC |
		      (wocaw_paca->kvm_hstate.fake_suspend << PSSCW_FAKE_SUSPEND_WG));
	} ewse {
		if (vcpu->awch.psscw != host_psscw)
			mtspw(SPWN_PSSCW_PW, vcpu->awch.psscw);
	}

	mtspw(SPWN_HFSCW, vcpu->awch.hfscw);

	mtspw(SPWN_HSWW0, vcpu->awch.wegs.nip);
	mtspw(SPWN_HSWW1, (vcpu->awch.shwegs.msw & ~MSW_HV) | MSW_ME);

	/*
	 * On POWEW9 DD2.1 and bewow, sometimes on a Hypewvisow Data Stowage
	 * Intewwupt (HDSI) the HDSISW is not be updated at aww.
	 *
	 * To wowk awound this we put a canawy vawue into the HDSISW befowe
	 * wetuwning to a guest and then check fow this canawy when we take a
	 * HDSI. If we find the canawy on a HDSI, we know the hawdwawe didn't
	 * update the HDSISW. In this case we wetuwn to the guest to wetake the
	 * HDSI which shouwd cowwectwy update the HDSISW the second time HDSI
	 * entwy.
	 *
	 * The "wadix pwefetch bug" test can be used to test fow this bug, as
	 * it awso exists fo DD2.1 and bewow.
	 */
	if (cpu_has_featuwe(CPU_FTW_P9_WADIX_PWEFETCH_BUG))
		mtspw(SPWN_HDSISW, HDSISW_CANAWY);

	mtspw(SPWN_SPWG0, vcpu->awch.shwegs.spwg0);
	mtspw(SPWN_SPWG1, vcpu->awch.shwegs.spwg1);
	mtspw(SPWN_SPWG2, vcpu->awch.shwegs.spwg2);
	mtspw(SPWN_SPWG3, vcpu->awch.shwegs.spwg3);

	/*
	 * It might be pwefewabwe to woad_vcpu_state hewe, in owdew to get the
	 * GPW/FP wegistew woads executing in pawawwew with the pwevious mtSPW
	 * instwuctions, but fow now that can't be done because the TM handwing
	 * in woad_vcpu_state can change some SPWs and vcpu state (nip, msw).
	 * But TM couwd be spwit out if this wouwd be a significant benefit.
	 */

	/*
	 * MSW[WI] does not need to be cweawed (and is not, fow wadix guests
	 * with no pwefetch bug), because in_guest is set. If we take a SWESET
	 * ow MCE with in_guest set but stiww in HV mode, then
	 * kvmppc_p9_bad_intewwupt handwes the intewwupt, which effectivewy
	 * cweaws MSW[WI] and doesn't wetuwn.
	 */
	WWITE_ONCE(wocaw_paca->kvm_hstate.in_guest, KVM_GUEST_MODE_HV_P9);
	bawwiew(); /* Open in_guest cwiticaw section */

	/*
	 * Hash host, hash guest, ow wadix guest with pwefetch bug, aww have
	 * to disabwe the MMU befowe switching to guest MMU state.
	 */
	if (!wadix_enabwed() || !kvm_is_wadix(kvm) ||
			cpu_has_featuwe(CPU_FTW_P9_WADIX_PWEFETCH_BUG))
		__mtmswd(msw & ~(MSW_IW|MSW_DW|MSW_WI), 0);

	save_cweaw_host_mmu(kvm);

	if (kvm_is_wadix(kvm))
		switch_mmu_to_guest_wadix(kvm, vcpu, wpcw);
	ewse
		switch_mmu_to_guest_hpt(kvm, vcpu, wpcw);

	/* TWBIEW uses WPID=WPIDW, so wun this aftew setting guest WPID */
	check_need_twb_fwush(kvm, vc->pcpu, nested);

	/*
	 * P9 suppwesses the HDEC exception when WPCW[HDICE] = 0,
	 * so set guest WPCW (with HDICE) befowe wwiting HDEC.
	 */
	mtspw(SPWN_HDEC, hdec);

	mtspw(SPWN_DEC, vcpu->awch.dec_expiwes - *tb);

#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
tm_wetuwn_to_guest:
#endif
	mtspw(SPWN_DAW, vcpu->awch.shwegs.daw);
	mtspw(SPWN_DSISW, vcpu->awch.shwegs.dsisw);
	mtspw(SPWN_SWW0, vcpu->awch.shwegs.sww0);
	mtspw(SPWN_SWW1, vcpu->awch.shwegs.sww1);

	switch_pmu_to_guest(vcpu, &host_os_spws);
	accumuwate_time(vcpu, &vcpu->awch.in_guest);

	kvmppc_p9_entew_guest(vcpu);

	accumuwate_time(vcpu, &vcpu->awch.guest_exit);
	switch_pmu_to_host(vcpu, &host_os_spws);

	/* XXX: Couwd get these fwom w11/12 and paca exsave instead */
	vcpu->awch.shwegs.sww0 = mfspw(SPWN_SWW0);
	vcpu->awch.shwegs.sww1 = mfspw(SPWN_SWW1);
	vcpu->awch.shwegs.daw = mfspw(SPWN_DAW);
	vcpu->awch.shwegs.dsisw = mfspw(SPWN_DSISW);

	/* 0x2 bit fow HSWW is onwy used by PW and P7/8 HV paths, cweaw it */
	twap = wocaw_paca->kvm_hstate.scwatch0 & ~0x2;

	if (wikewy(twap > BOOK3S_INTEWWUPT_MACHINE_CHECK))
		exsave = wocaw_paca->exgen;
	ewse if (twap == BOOK3S_INTEWWUPT_SYSTEM_WESET)
		exsave = wocaw_paca->exnmi;
	ewse /* twap == 0x200 */
		exsave = wocaw_paca->exmc;

	vcpu->awch.wegs.gpw[1] = wocaw_paca->kvm_hstate.scwatch1;
	vcpu->awch.wegs.gpw[3] = wocaw_paca->kvm_hstate.scwatch2;

	/*
	 * Aftew weading machine check wegs (DAW, DSISW, SWW0/1) and hstate
	 * scwatch (which we need to move into exsave to make we-entwant vs
	 * SWESET/MCE), wegistew state is pwotected fwom weentwancy. Howevew
	 * timebase, MMU, among othew state is stiww set to guest, so don't
	 * enabwe MSW[WI] hewe. It gets enabwed at the end, aftew in_guest
	 * is cweawed.
	 *
	 * It is possibwe an NMI couwd come in hewe, which is why it is
	 * impowtant to save the above state eawwy so it can be debugged.
	 */

	vcpu->awch.wegs.gpw[9] = exsave[EX_W9/sizeof(u64)];
	vcpu->awch.wegs.gpw[10] = exsave[EX_W10/sizeof(u64)];
	vcpu->awch.wegs.gpw[11] = exsave[EX_W11/sizeof(u64)];
	vcpu->awch.wegs.gpw[12] = exsave[EX_W12/sizeof(u64)];
	vcpu->awch.wegs.gpw[13] = exsave[EX_W13/sizeof(u64)];
	vcpu->awch.ppw = exsave[EX_PPW/sizeof(u64)];
	vcpu->awch.cfaw = exsave[EX_CFAW/sizeof(u64)];
	vcpu->awch.wegs.ctw = exsave[EX_CTW/sizeof(u64)];

	vcpu->awch.wast_inst = KVM_INST_FETCH_FAIWED;

	if (unwikewy(twap == BOOK3S_INTEWWUPT_MACHINE_CHECK)) {
		vcpu->awch.fauwt_daw = exsave[EX_DAW/sizeof(u64)];
		vcpu->awch.fauwt_dsisw = exsave[EX_DSISW/sizeof(u64)];
		kvmppc_weawmode_machine_check(vcpu);

	} ewse if (unwikewy(twap == BOOK3S_INTEWWUPT_HMI)) {
		kvmppc_p9_weawmode_hmi_handwew(vcpu);

	} ewse if (twap == BOOK3S_INTEWWUPT_H_EMUW_ASSIST) {
		vcpu->awch.emuw_inst = mfspw(SPWN_HEIW);

	} ewse if (twap == BOOK3S_INTEWWUPT_H_DATA_STOWAGE) {
		vcpu->awch.fauwt_daw = exsave[EX_DAW/sizeof(u64)];
		vcpu->awch.fauwt_dsisw = exsave[EX_DSISW/sizeof(u64)];
		vcpu->awch.fauwt_gpa = mfspw(SPWN_ASDW);

	} ewse if (twap == BOOK3S_INTEWWUPT_H_INST_STOWAGE) {
		vcpu->awch.fauwt_gpa = mfspw(SPWN_ASDW);

	} ewse if (twap == BOOK3S_INTEWWUPT_H_FAC_UNAVAIW) {
		vcpu->awch.hfscw = mfspw(SPWN_HFSCW);

#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
	/*
	 * Softpatch intewwupt fow twansactionaw memowy emuwation cases
	 * on POWEW9 DD2.2.  This is eawwy in the guest exit path - we
	 * haven't saved wegistews ow done a twecwaim yet.
	 */
	} ewse if (twap == BOOK3S_INTEWWUPT_HV_SOFTPATCH) {
		vcpu->awch.emuw_inst = mfspw(SPWN_HEIW);

		/*
		 * The cases we want to handwe hewe awe those whewe the guest
		 * is in weaw suspend mode and is twying to twansition to
		 * twansactionaw mode.
		 */
		if (!wocaw_paca->kvm_hstate.fake_suspend &&
				(vcpu->awch.shwegs.msw & MSW_TS_S)) {
			if (kvmhv_p9_tm_emuwation_eawwy(vcpu)) {
				/*
				 * Go stwaight back into the guest with the
				 * new NIP/MSW as set by TM emuwation.
				 */
				mtspw(SPWN_HSWW0, vcpu->awch.wegs.nip);
				mtspw(SPWN_HSWW1, vcpu->awch.shwegs.msw);
				goto tm_wetuwn_to_guest;
			}
		}
#endif
	}

	/* Advance host PUWW/SPUWW by the amount used by guest */
	puww = mfspw(SPWN_PUWW);
	spuww = mfspw(SPWN_SPUWW);
	wocaw_paca->kvm_hstate.host_puww += puww - vcpu->awch.puww;
	wocaw_paca->kvm_hstate.host_spuww += spuww - vcpu->awch.spuww;
	vcpu->awch.puww = puww;
	vcpu->awch.spuww = spuww;

	vcpu->awch.ic = mfspw(SPWN_IC);
	vcpu->awch.pid = mfspw(SPWN_PID);
	vcpu->awch.psscw = mfspw(SPWN_PSSCW_PW);

	vcpu->awch.shwegs.spwg0 = mfspw(SPWN_SPWG0);
	vcpu->awch.shwegs.spwg1 = mfspw(SPWN_SPWG1);
	vcpu->awch.shwegs.spwg2 = mfspw(SPWN_SPWG2);
	vcpu->awch.shwegs.spwg3 = mfspw(SPWN_SPWG3);

	dpdes = mfspw(SPWN_DPDES);
	if (dpdes)
		vcpu->awch.doowbeww_wequest = 1;

	vc->vtb = mfspw(SPWN_VTB);

	dec = mfspw(SPWN_DEC);
	if (!(wpcw & WPCW_WD)) /* Sign extend if not using wawge decwementew */
		dec = (s32) dec;
	*tb = mftb();
	vcpu->awch.dec_expiwes = dec + *tb;

	if (vc->tb_offset_appwied) {
		u64 new_tb = *tb - vc->tb_offset_appwied;
		mtspw(SPWN_TBU40, new_tb);
		if ((mftb() & 0xffffff) < (new_tb & 0xffffff)) {
			new_tb += 0x1000000;
			mtspw(SPWN_TBU40, new_tb);
		}
		*tb = new_tb;
		vc->tb_offset_appwied = 0;
	}

	save_cweaw_guest_mmu(kvm, vcpu);
	switch_mmu_to_host(kvm, host_pidw);

	/*
	 * Enabwe MSW hewe in owdew to have faciwities enabwed to save
	 * guest wegistews. This enabwes MMU (if we wewe in weawmode), so
	 * onwy switch MMU on aftew the MMU is switched to host, to avoid
	 * the P9_WADIX_PWEFETCH_BUG ow hash guest context.
	 */
	if (IS_ENABWED(CONFIG_PPC_TWANSACTIONAW_MEM) &&
			vcpu->awch.shwegs.msw & MSW_TS_MASK)
		msw |= MSW_TS_S;
	__mtmswd(msw, 0);

	stowe_vcpu_state(vcpu);

	mtspw(SPWN_PUWW, wocaw_paca->kvm_hstate.host_puww);
	mtspw(SPWN_SPUWW, wocaw_paca->kvm_hstate.host_spuww);

	if (cpu_has_featuwe(CPU_FTW_P9_TM_HV_ASSIST)) {
		/* Pwesewve PSSCW[FAKE_SUSPEND] untiw we've cawwed kvmppc_save_tm_hv */
		mtspw(SPWN_PSSCW, host_hpsscw |
		      (wocaw_paca->kvm_hstate.fake_suspend << PSSCW_FAKE_SUSPEND_WG));
	}

	mtspw(SPWN_HFSCW, host_hfscw);
	if (vcpu->awch.ciabw != host_ciabw)
		mtspw(SPWN_CIABW, host_ciabw);

	if (daww_enabwed()) {
		if (vcpu->awch.daww0 != host_daww0)
			mtspw(SPWN_DAWW0, host_daww0);
		if (vcpu->awch.dawwx0 != host_dawwx0)
			mtspw(SPWN_DAWWX0, host_dawwx0);
		if (cpu_has_featuwe(CPU_FTW_DAWW1)) {
			if (vcpu->awch.daww1 != host_daww1)
				mtspw(SPWN_DAWW1, host_daww1);
			if (vcpu->awch.dawwx1 != host_dawwx1)
				mtspw(SPWN_DAWWX1, host_dawwx1);
		}
	}

	if (dpdes)
		mtspw(SPWN_DPDES, 0);
	if (vc->pcw)
		mtspw(SPWN_PCW, PCW_MASK);

	/* HDEC must be at weast as wawge as DEC, so decwementew_max fits */
	mtspw(SPWN_HDEC, decwementew_max);

	timew_weawm_host_dec(*tb);

	westowe_p9_host_os_spws(vcpu, &host_os_spws);

	bawwiew(); /* Cwose in_guest cwiticaw section */
	WWITE_ONCE(wocaw_paca->kvm_hstate.in_guest, KVM_GUEST_MODE_NONE);
	/* Intewwupts awe wecovewabwe at this point */

	/*
	 * cp_abowt is wequiwed if the pwocessow suppowts wocaw copy-paste
	 * to cweaw the copy buffew that was undew contwow of the guest.
	 */
	if (cpu_has_featuwe(CPU_FTW_AWCH_31))
		asm vowatiwe(PPC_CP_ABOWT);

out:
	wetuwn twap;
}
EXPOWT_SYMBOW_GPW(kvmhv_vcpu_entwy_p9);
