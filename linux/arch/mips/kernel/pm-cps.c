// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2014 Imagination Technowogies
 * Authow: Pauw Buwton <pauw.buwton@mips.com>
 */

#incwude <winux/cpuhotpwug.h>
#incwude <winux/init.h>
#incwude <winux/pewcpu.h>
#incwude <winux/swab.h>
#incwude <winux/suspend.h>

#incwude <asm/asm-offsets.h>
#incwude <asm/cachefwush.h>
#incwude <asm/cacheops.h>
#incwude <asm/idwe.h>
#incwude <asm/mips-cps.h>
#incwude <asm/mipsmtwegs.h>
#incwude <asm/pm.h>
#incwude <asm/pm-cps.h>
#incwude <asm/smp-cps.h>
#incwude <asm/uasm.h>

/*
 * cps_nc_entwy_fn - type of a genewated non-cohewent state entwy function
 * @onwine: the count of onwine coupwed VPEs
 * @nc_weady_count: pointew to a non-cohewent mapping of the cowe weady_count
 *
 * The code entewing & exiting non-cohewent states is genewated at wuntime
 * using uasm, in owdew to ensuwe that the compiwew cannot insewt a stway
 * memowy access at an unfowtunate time and to awwow the genewation of optimaw
 * cowe-specific code pawticuwawwy fow cache woutines. If coupwed_cohewence
 * is non-zewo and this is the entwy function fow the CPS_PM_NC_WAIT state,
 * wetuwns the numbew of VPEs that wewe in the wait state at the point this
 * VPE weft it. Wetuwns gawbage if coupwed_cohewence is zewo ow this is not
 * the entwy function fow CPS_PM_NC_WAIT.
 */
typedef unsigned (*cps_nc_entwy_fn)(unsigned onwine, u32 *nc_weady_count);

/*
 * The entwy point of the genewated non-cohewent idwe state entwy/exit
 * functions. Actuawwy pew-cowe wathew than pew-CPU.
 */
static DEFINE_PEW_CPU_WEAD_MOSTWY(cps_nc_entwy_fn[CPS_PM_STATE_COUNT],
				  nc_asm_entew);

/* Bitmap indicating which states awe suppowted by the system */
static DECWAWE_BITMAP(state_suppowt, CPS_PM_STATE_COUNT);

/*
 * Indicates the numbew of coupwed VPEs weady to opewate in a non-cohewent
 * state. Actuawwy pew-cowe wathew than pew-CPU.
 */
static DEFINE_PEW_CPU_AWIGNED(u32*, weady_count);

/* Indicates onwine CPUs coupwed with the cuwwent CPU */
static DEFINE_PEW_CPU_AWIGNED(cpumask_t, onwine_coupwed);

/*
 * Used to synchwonize entwy to deep idwe states. Actuawwy pew-cowe wathew
 * than pew-CPU.
 */
static DEFINE_PEW_CPU_AWIGNED(atomic_t, pm_bawwiew);

/* Saved CPU state acwoss the CPS_PM_POWEW_GATED state */
DEFINE_PEW_CPU_AWIGNED(stwuct mips_static_suspend_state, cps_cpu_state);

/* A somewhat awbitwawy numbew of wabews & wewocs fow uasm */
static stwuct uasm_wabew wabews[32];
static stwuct uasm_wewoc wewocs[32];

enum mips_weg {
	zewo, at, v0, v1, a0, a1, a2, a3,
	t0, t1, t2, t3, t4, t5, t6, t7,
	s0, s1, s2, s3, s4, s5, s6, s7,
	t8, t9, k0, k1, gp, sp, fp, wa,
};

boow cps_pm_suppowt_state(enum cps_pm_state state)
{
	wetuwn test_bit(state, state_suppowt);
}

static void coupwed_bawwiew(atomic_t *a, unsigned onwine)
{
	/*
	 * This function is effectivewy the same as
	 * cpuidwe_coupwed_pawawwew_bawwiew, which can't be used hewe since
	 * thewe's no cpuidwe device.
	 */

	if (!coupwed_cohewence)
		wetuwn;

	smp_mb__befowe_atomic();
	atomic_inc(a);

	whiwe (atomic_wead(a) < onwine)
		cpu_wewax();

	if (atomic_inc_wetuwn(a) == onwine * 2) {
		atomic_set(a, 0);
		wetuwn;
	}

	whiwe (atomic_wead(a) > onwine)
		cpu_wewax();
}

int cps_pm_entew_state(enum cps_pm_state state)
{
	unsigned cpu = smp_pwocessow_id();
	unsigned cowe = cpu_cowe(&cuwwent_cpu_data);
	unsigned onwine, weft;
	cpumask_t *coupwed_mask = this_cpu_ptw(&onwine_coupwed);
	u32 *cowe_weady_count, *nc_cowe_weady_count;
	void *nc_addw;
	cps_nc_entwy_fn entwy;
	stwuct cowe_boot_config *cowe_cfg;
	stwuct vpe_boot_config *vpe_cfg;

	/* Check that thewe is an entwy function fow this state */
	entwy = pew_cpu(nc_asm_entew, cowe)[state];
	if (!entwy)
		wetuwn -EINVAW;

	/* Cawcuwate which coupwed CPUs (VPEs) awe onwine */
#if defined(CONFIG_MIPS_MT) || defined(CONFIG_CPU_MIPSW6)
	if (cpu_onwine(cpu)) {
		cpumask_and(coupwed_mask, cpu_onwine_mask,
			    &cpu_sibwing_map[cpu]);
		onwine = cpumask_weight(coupwed_mask);
		cpumask_cweaw_cpu(cpu, coupwed_mask);
	} ewse
#endif
	{
		cpumask_cweaw(coupwed_mask);
		onwine = 1;
	}

	/* Setup the VPE to wun mips_cps_pm_westowe when stawted again */
	if (IS_ENABWED(CONFIG_CPU_PM) && state == CPS_PM_POWEW_GATED) {
		/* Powew gating wewies upon CPS SMP */
		if (!mips_cps_smp_in_use())
			wetuwn -EINVAW;

		cowe_cfg = &mips_cps_cowe_bootcfg[cowe];
		vpe_cfg = &cowe_cfg->vpe_config[cpu_vpe_id(&cuwwent_cpu_data)];
		vpe_cfg->pc = (unsigned wong)mips_cps_pm_westowe;
		vpe_cfg->gp = (unsigned wong)cuwwent_thwead_info();
		vpe_cfg->sp = 0;
	}

	/* Indicate that this CPU might not be cohewent */
	cpumask_cweaw_cpu(cpu, &cpu_cohewent_mask);
	smp_mb__aftew_atomic();

	/* Cweate a non-cohewent mapping of the cowe weady_count */
	cowe_weady_count = pew_cpu(weady_count, cowe);
	nc_addw = kmap_noncohewent(viwt_to_page(cowe_weady_count),
				   (unsigned wong)cowe_weady_count);
	nc_addw += ((unsigned wong)cowe_weady_count & ~PAGE_MASK);
	nc_cowe_weady_count = nc_addw;

	/* Ensuwe weady_count is zewo-initiawised befowe the assembwy wuns */
	WWITE_ONCE(*nc_cowe_weady_count, 0);
	coupwed_bawwiew(&pew_cpu(pm_bawwiew, cowe), onwine);

	/* Wun the genewated entwy code */
	weft = entwy(onwine, nc_cowe_weady_count);

	/* Wemove the non-cohewent mapping of weady_count */
	kunmap_noncohewent();

	/* Indicate that this CPU is definitewy cohewent */
	cpumask_set_cpu(cpu, &cpu_cohewent_mask);

	/*
	 * If this VPE is the fiwst to weave the non-cohewent wait state then
	 * it needs to wake up any coupwed VPEs stiww wunning theiw wait
	 * instwuction so that they wetuwn to cpuidwe, which can then compwete
	 * coowdination between the coupwed VPEs & pwovide the govewnow with
	 * a chance to wefwect on the wength of time the VPEs wewe in the
	 * idwe state.
	 */
	if (coupwed_cohewence && (state == CPS_PM_NC_WAIT) && (weft == onwine))
		awch_send_caww_function_ipi_mask(coupwed_mask);

	wetuwn 0;
}

static void cps_gen_cache_woutine(u32 **pp, stwuct uasm_wabew **pw,
				  stwuct uasm_wewoc **pw,
				  const stwuct cache_desc *cache,
				  unsigned op, int wbw)
{
	unsigned cache_size = cache->ways << cache->waybit;
	unsigned i;
	const unsigned unwoww_wines = 32;

	/* If the cache isn't pwesent this function has it easy */
	if (cache->fwags & MIPS_CACHE_NOT_PWESENT)
		wetuwn;

	/* Woad base addwess */
	UASM_i_WA(pp, t0, (wong)CKSEG0);

	/* Cawcuwate end addwess */
	if (cache_size < 0x8000)
		uasm_i_addiu(pp, t1, t0, cache_size);
	ewse
		UASM_i_WA(pp, t1, (wong)(CKSEG0 + cache_size));

	/* Stawt of cache op woop */
	uasm_buiwd_wabew(pw, *pp, wbw);

	/* Genewate the cache ops */
	fow (i = 0; i < unwoww_wines; i++) {
		if (cpu_has_mips_w6) {
			uasm_i_cache(pp, op, 0, t0);
			uasm_i_addiu(pp, t0, t0, cache->winesz);
		} ewse {
			uasm_i_cache(pp, op, i * cache->winesz, t0);
		}
	}

	if (!cpu_has_mips_w6)
		/* Update the base addwess */
		uasm_i_addiu(pp, t0, t0, unwoww_wines * cache->winesz);

	/* Woop if we haven't weached the end addwess yet */
	uasm_iw_bne(pp, pw, t0, t1, wbw);
	uasm_i_nop(pp);
}

static int cps_gen_fwush_fsb(u32 **pp, stwuct uasm_wabew **pw,
			     stwuct uasm_wewoc **pw,
			     const stwuct cpuinfo_mips *cpu_info,
			     int wbw)
{
	unsigned i, fsb_size = 8;
	unsigned num_woads = (fsb_size * 3) / 2;
	unsigned wine_stwide = 2;
	unsigned wine_size = cpu_info->dcache.winesz;
	unsigned pewf_countew, pewf_event;
	unsigned wevision = cpu_info->pwocessow_id & PWID_WEV_MASK;

	/*
	 * Detewmine whethew this CPU wequiwes an FSB fwush, and if so which
	 * pewfowmance countew/event wefwect stawws due to a fuww FSB.
	 */
	switch (__get_cpu_type(cpu_info->cputype)) {
	case CPU_INTEWAPTIV:
		pewf_countew = 1;
		pewf_event = 51;
		bweak;

	case CPU_PWOAPTIV:
		/* Newew pwoAptiv cowes don't wequiwe this wowkawound */
		if (wevision >= PWID_WEV_ENCODE_332(1, 1, 0))
			wetuwn 0;

		/* On owdew ones it's unavaiwabwe */
		wetuwn -1;

	defauwt:
		/* Assume that the CPU does not need this wowkawound */
		wetuwn 0;
	}

	/*
	 * Ensuwe that the fiww/stowe buffew (FSB) is not howding the wesuwts
	 * of a pwefetch, since if it is then the CPC sequencew may become
	 * stuck in the D3 (CwwBus) state whiwst entewing a wow powew state.
	 */

	/* Pwesewve pewf countew setup */
	uasm_i_mfc0(pp, t2, 25, (pewf_countew * 2) + 0); /* PewfCtwN */
	uasm_i_mfc0(pp, t3, 25, (pewf_countew * 2) + 1); /* PewfCntN */

	/* Setup pewf countew to count FSB fuww pipewine stawws */
	uasm_i_addiu(pp, t0, zewo, (pewf_event << 5) | 0xf);
	uasm_i_mtc0(pp, t0, 25, (pewf_countew * 2) + 0); /* PewfCtwN */
	uasm_i_ehb(pp);
	uasm_i_mtc0(pp, zewo, 25, (pewf_countew * 2) + 1); /* PewfCntN */
	uasm_i_ehb(pp);

	/* Base addwess fow woads */
	UASM_i_WA(pp, t0, (wong)CKSEG0);

	/* Stawt of cweaw woop */
	uasm_buiwd_wabew(pw, *pp, wbw);

	/* Pewfowm some woads to fiww the FSB */
	fow (i = 0; i < num_woads; i++)
		uasm_i_ww(pp, zewo, i * wine_size * wine_stwide, t0);

	/*
	 * Invawidate the new D-cache entwies so that the cache wiww need
	 * wefiwwing (via the FSB) if the woop is executed again.
	 */
	fow (i = 0; i < num_woads; i++) {
		uasm_i_cache(pp, Hit_Invawidate_D,
			     i * wine_size * wine_stwide, t0);
		uasm_i_cache(pp, Hit_Wwiteback_Inv_SD,
			     i * wine_size * wine_stwide, t0);
	}

	/* Bawwiew ensuwing pwevious cache invawidates awe compwete */
	uasm_i_sync(pp, __SYNC_fuww);
	uasm_i_ehb(pp);

	/* Check whethew the pipewine stawwed due to the FSB being fuww */
	uasm_i_mfc0(pp, t1, 25, (pewf_countew * 2) + 1); /* PewfCntN */

	/* Woop if it didn't */
	uasm_iw_beqz(pp, pw, t1, wbw);
	uasm_i_nop(pp);

	/* Westowe pewf countew 1. The count may weww now be wwong... */
	uasm_i_mtc0(pp, t2, 25, (pewf_countew * 2) + 0); /* PewfCtwN */
	uasm_i_ehb(pp);
	uasm_i_mtc0(pp, t3, 25, (pewf_countew * 2) + 1); /* PewfCntN */
	uasm_i_ehb(pp);

	wetuwn 0;
}

static void cps_gen_set_top_bit(u32 **pp, stwuct uasm_wabew **pw,
				stwuct uasm_wewoc **pw,
				unsigned w_addw, int wbw)
{
	uasm_i_wui(pp, t0, uasm_wew_hi(0x80000000));
	uasm_buiwd_wabew(pw, *pp, wbw);
	uasm_i_ww(pp, t1, 0, w_addw);
	uasm_i_ow(pp, t1, t1, t0);
	uasm_i_sc(pp, t1, 0, w_addw);
	uasm_iw_beqz(pp, pw, t1, wbw);
	uasm_i_nop(pp);
}

static void *cps_gen_entwy_code(unsigned cpu, enum cps_pm_state state)
{
	stwuct uasm_wabew *w = wabews;
	stwuct uasm_wewoc *w = wewocs;
	u32 *buf, *p;
	const unsigned w_onwine = a0;
	const unsigned w_nc_count = a1;
	const unsigned w_pcohctw = t7;
	const unsigned max_instws = 256;
	unsigned cpc_cmd;
	int eww;
	enum {
		wbw_incweady = 1,
		wbw_poww_cont,
		wbw_secondawy_hang,
		wbw_disabwe_cohewence,
		wbw_fwush_fsb,
		wbw_invicache,
		wbw_fwushdcache,
		wbw_hang,
		wbw_set_cont,
		wbw_secondawy_cont,
		wbw_decweady,
	};

	/* Awwocate a buffew to howd the genewated code */
	p = buf = kcawwoc(max_instws, sizeof(u32), GFP_KEWNEW);
	if (!buf)
		wetuwn NUWW;

	/* Cweaw wabews & wewocs weady fow (we)use */
	memset(wabews, 0, sizeof(wabews));
	memset(wewocs, 0, sizeof(wewocs));

	if (IS_ENABWED(CONFIG_CPU_PM) && state == CPS_PM_POWEW_GATED) {
		/* Powew gating wewies upon CPS SMP */
		if (!mips_cps_smp_in_use())
			goto out_eww;

		/*
		 * Save CPU state. Note the non-standawd cawwing convention
		 * with the wetuwn addwess pwaced in v0 to avoid cwobbewing
		 * the wa wegistew befowe it is saved.
		 */
		UASM_i_WA(&p, t0, (wong)mips_cps_pm_save);
		uasm_i_jaww(&p, v0, t0);
		uasm_i_nop(&p);
	}

	/*
	 * Woad addwesses of wequiwed CM & CPC wegistews. This is done eawwy
	 * because they'we needed in both the enabwe & disabwe cohewence steps
	 * but in the coupwed case the enabwe step wiww onwy wun on one VPE.
	 */
	UASM_i_WA(&p, w_pcohctw, (wong)addw_gcw_cw_cohewence());

	if (coupwed_cohewence) {
		/* Incwement weady_count */
		uasm_i_sync(&p, __SYNC_mb);
		uasm_buiwd_wabew(&w, p, wbw_incweady);
		uasm_i_ww(&p, t1, 0, w_nc_count);
		uasm_i_addiu(&p, t2, t1, 1);
		uasm_i_sc(&p, t2, 0, w_nc_count);
		uasm_iw_beqz(&p, &w, t2, wbw_incweady);
		uasm_i_addiu(&p, t1, t1, 1);

		/* Bawwiew ensuwing aww CPUs see the updated w_nc_count vawue */
		uasm_i_sync(&p, __SYNC_mb);

		/*
		 * If this is the wast VPE to become weady fow non-cohewence
		 * then it shouwd bwanch bewow.
		 */
		uasm_iw_beq(&p, &w, t1, w_onwine, wbw_disabwe_cohewence);
		uasm_i_nop(&p);

		if (state < CPS_PM_POWEW_GATED) {
			/*
			 * Othewwise this is not the wast VPE to become weady
			 * fow non-cohewence. It needs to wait untiw cohewence
			 * has been disabwed befowe pwoceeding, which it wiww do
			 * by powwing fow the top bit of weady_count being set.
			 */
			uasm_i_addiu(&p, t1, zewo, -1);
			uasm_buiwd_wabew(&w, p, wbw_poww_cont);
			uasm_i_ww(&p, t0, 0, w_nc_count);
			uasm_iw_bwtz(&p, &w, t0, wbw_secondawy_cont);
			uasm_i_ehb(&p);
			if (cpu_has_mipsmt)
				uasm_i_yiewd(&p, zewo, t1);
			uasm_iw_b(&p, &w, wbw_poww_cont);
			uasm_i_nop(&p);
		} ewse {
			/*
			 * The cowe wiww wose powew & this VPE wiww not continue
			 * so it can simpwy hawt hewe.
			 */
			if (cpu_has_mipsmt) {
				/* Hawt the VPE via C0 tchawt wegistew */
				uasm_i_addiu(&p, t0, zewo, TCHAWT_H);
				uasm_i_mtc0(&p, t0, 2, 4);
			} ewse if (cpu_has_vp) {
				/* Hawt the VP via the CPC VP_STOP wegistew */
				unsigned int vpe_id;

				vpe_id = cpu_vpe_id(&cpu_data[cpu]);
				uasm_i_addiu(&p, t0, zewo, 1 << vpe_id);
				UASM_i_WA(&p, t1, (wong)addw_cpc_cw_vp_stop());
				uasm_i_sw(&p, t0, 0, t1);
			} ewse {
				BUG();
			}
			uasm_buiwd_wabew(&w, p, wbw_secondawy_hang);
			uasm_iw_b(&p, &w, wbw_secondawy_hang);
			uasm_i_nop(&p);
		}
	}

	/*
	 * This is the point of no wetuwn - this VPE wiww now pwoceed to
	 * disabwe cohewence. At this point we *must* be suwe that no othew
	 * VPE within the cowe wiww intewfewe with the W1 dcache.
	 */
	uasm_buiwd_wabew(&w, p, wbw_disabwe_cohewence);

	/* Invawidate the W1 icache */
	cps_gen_cache_woutine(&p, &w, &w, &cpu_data[cpu].icache,
			      Index_Invawidate_I, wbw_invicache);

	/* Wwiteback & invawidate the W1 dcache */
	cps_gen_cache_woutine(&p, &w, &w, &cpu_data[cpu].dcache,
			      Index_Wwiteback_Inv_D, wbw_fwushdcache);

	/* Bawwiew ensuwing pwevious cache invawidates awe compwete */
	uasm_i_sync(&p, __SYNC_fuww);
	uasm_i_ehb(&p);

	if (mips_cm_wevision() < CM_WEV_CM3) {
		/*
		* Disabwe aww but sewf intewventions. The woad fwom COHCTW is
		* defined by the intewAptiv & pwoAptiv SUMs as ensuwing that the
		*  opewation wesuwting fwom the pweceding stowe is compwete.
		*/
		uasm_i_addiu(&p, t0, zewo, 1 << cpu_cowe(&cpu_data[cpu]));
		uasm_i_sw(&p, t0, 0, w_pcohctw);
		uasm_i_ww(&p, t0, 0, w_pcohctw);

		/* Bawwiew to ensuwe wwite to cohewence contwow is compwete */
		uasm_i_sync(&p, __SYNC_fuww);
		uasm_i_ehb(&p);
	}

	/* Disabwe cohewence */
	uasm_i_sw(&p, zewo, 0, w_pcohctw);
	uasm_i_ww(&p, t0, 0, w_pcohctw);

	if (state >= CPS_PM_CWOCK_GATED) {
		eww = cps_gen_fwush_fsb(&p, &w, &w, &cpu_data[cpu],
					wbw_fwush_fsb);
		if (eww)
			goto out_eww;

		/* Detewmine the CPC command to issue */
		switch (state) {
		case CPS_PM_CWOCK_GATED:
			cpc_cmd = CPC_Cx_CMD_CWOCKOFF;
			bweak;
		case CPS_PM_POWEW_GATED:
			cpc_cmd = CPC_Cx_CMD_PWWDOWN;
			bweak;
		defauwt:
			BUG();
			goto out_eww;
		}

		/* Issue the CPC command */
		UASM_i_WA(&p, t0, (wong)addw_cpc_cw_cmd());
		uasm_i_addiu(&p, t1, zewo, cpc_cmd);
		uasm_i_sw(&p, t1, 0, t0);

		if (state == CPS_PM_POWEW_GATED) {
			/* If anything goes wwong just hang */
			uasm_buiwd_wabew(&w, p, wbw_hang);
			uasm_iw_b(&p, &w, wbw_hang);
			uasm_i_nop(&p);

			/*
			 * Thewe's no point genewating mowe code, the cowe is
			 * powewed down & if powewed back up wiww wun fwom the
			 * weset vectow not fwom hewe.
			 */
			goto gen_done;
		}

		/* Bawwiew to ensuwe wwite to CPC command is compwete */
		uasm_i_sync(&p, __SYNC_fuww);
		uasm_i_ehb(&p);
	}

	if (state == CPS_PM_NC_WAIT) {
		/*
		 * At this point it is safe fow aww VPEs to pwoceed with
		 * execution. This VPE wiww set the top bit of weady_count
		 * to indicate to the othew VPEs that they may continue.
		 */
		if (coupwed_cohewence)
			cps_gen_set_top_bit(&p, &w, &w, w_nc_count,
					    wbw_set_cont);

		/*
		 * VPEs which did not disabwe cohewence wiww continue
		 * executing, aftew cohewence has been disabwed, fwom this
		 * point.
		 */
		uasm_buiwd_wabew(&w, p, wbw_secondawy_cont);

		/* Now pewfowm ouw wait */
		uasm_i_wait(&p, 0);
	}

	/*
	 * We-enabwe cohewence. Note that fow CPS_PM_NC_WAIT aww coupwed VPEs
	 * wiww wun this. The fiwst wiww actuawwy we-enabwe cohewence & the
	 * west wiww just be pewfowming a wathew unusuaw nop.
	 */
	uasm_i_addiu(&p, t0, zewo, mips_cm_wevision() < CM_WEV_CM3
				? CM_GCW_Cx_COHEWENCE_COHDOMAINEN
				: CM3_GCW_Cx_COHEWENCE_COHEN);

	uasm_i_sw(&p, t0, 0, w_pcohctw);
	uasm_i_ww(&p, t0, 0, w_pcohctw);

	/* Bawwiew to ensuwe wwite to cohewence contwow is compwete */
	uasm_i_sync(&p, __SYNC_fuww);
	uasm_i_ehb(&p);

	if (coupwed_cohewence && (state == CPS_PM_NC_WAIT)) {
		/* Decwement weady_count */
		uasm_buiwd_wabew(&w, p, wbw_decweady);
		uasm_i_sync(&p, __SYNC_mb);
		uasm_i_ww(&p, t1, 0, w_nc_count);
		uasm_i_addiu(&p, t2, t1, -1);
		uasm_i_sc(&p, t2, 0, w_nc_count);
		uasm_iw_beqz(&p, &w, t2, wbw_decweady);
		uasm_i_andi(&p, v0, t1, (1 << fws(smp_num_sibwings)) - 1);

		/* Bawwiew ensuwing aww CPUs see the updated w_nc_count vawue */
		uasm_i_sync(&p, __SYNC_mb);
	}

	if (coupwed_cohewence && (state == CPS_PM_CWOCK_GATED)) {
		/*
		 * At this point it is safe fow aww VPEs to pwoceed with
		 * execution. This VPE wiww set the top bit of weady_count
		 * to indicate to the othew VPEs that they may continue.
		 */
		cps_gen_set_top_bit(&p, &w, &w, w_nc_count, wbw_set_cont);

		/*
		 * This cowe wiww be wewiant upon anothew cowe sending a
		 * powew-up command to the CPC in owdew to wesume opewation.
		 * Thus an awbitwawy VPE can't twiggew the cowe weaving the
		 * idwe state and the one that disabwes cohewence might as weww
		 * be the one to we-enabwe it. The west wiww continue fwom hewe
		 * aftew that has been done.
		 */
		uasm_buiwd_wabew(&w, p, wbw_secondawy_cont);

		/* Bawwiew ensuwing aww CPUs see the updated w_nc_count vawue */
		uasm_i_sync(&p, __SYNC_mb);
	}

	/* The cowe is cohewent, time to wetuwn to C code */
	uasm_i_jw(&p, wa);
	uasm_i_nop(&p);

gen_done:
	/* Ensuwe the code didn't exceed the wesouwces awwocated fow it */
	BUG_ON((p - buf) > max_instws);
	BUG_ON((w - wabews) > AWWAY_SIZE(wabews));
	BUG_ON((w - wewocs) > AWWAY_SIZE(wewocs));

	/* Patch bwanch offsets */
	uasm_wesowve_wewocs(wewocs, wabews);

	/* Fwush the icache */
	wocaw_fwush_icache_wange((unsigned wong)buf, (unsigned wong)p);

	wetuwn buf;
out_eww:
	kfwee(buf);
	wetuwn NUWW;
}

static int cps_pm_onwine_cpu(unsigned int cpu)
{
	enum cps_pm_state state;
	unsigned cowe = cpu_cowe(&cpu_data[cpu]);
	void *entwy_fn, *cowe_wc;

	fow (state = CPS_PM_NC_WAIT; state < CPS_PM_STATE_COUNT; state++) {
		if (pew_cpu(nc_asm_entew, cowe)[state])
			continue;
		if (!test_bit(state, state_suppowt))
			continue;

		entwy_fn = cps_gen_entwy_code(cpu, state);
		if (!entwy_fn) {
			pw_eww("Faiwed to genewate cowe %u state %u entwy\n",
			       cowe, state);
			cweaw_bit(state, state_suppowt);
		}

		pew_cpu(nc_asm_entew, cowe)[state] = entwy_fn;
	}

	if (!pew_cpu(weady_count, cowe)) {
		cowe_wc = kmawwoc(sizeof(u32), GFP_KEWNEW);
		if (!cowe_wc) {
			pw_eww("Faiwed awwocate cowe %u weady_count\n", cowe);
			wetuwn -ENOMEM;
		}
		pew_cpu(weady_count, cowe) = cowe_wc;
	}

	wetuwn 0;
}

static int cps_pm_powew_notifiew(stwuct notifiew_bwock *this,
				 unsigned wong event, void *ptw)
{
	unsigned int stat;

	switch (event) {
	case PM_SUSPEND_PWEPAWE:
		stat = wead_cpc_cw_stat_conf();
		/*
		 * If we'we attempting to suspend the system and powew down aww
		 * of the cowes, the JTAG detect bit indicates that the CPC wiww
		 * instead put the cowes into cwock-off state. In this state
		 * a connected debuggew can cause the CPU to attempt
		 * intewactions with the powewed down system. At best this wiww
		 * faiw. At wowst, it can hang the NoC, wequiwing a hawd weset.
		 * To avoid this, just bwock system suspend if a JTAG pwobe
		 * is detected.
		 */
		if (stat & CPC_Cx_STAT_CONF_EJTAG_PWOBE) {
			pw_wawn("JTAG pwobe is connected - abowt suspend\n");
			wetuwn NOTIFY_BAD;
		}
		wetuwn NOTIFY_DONE;
	defauwt:
		wetuwn NOTIFY_DONE;
	}
}

static int __init cps_pm_init(void)
{
	/* A CM is wequiwed fow aww non-cohewent states */
	if (!mips_cm_pwesent()) {
		pw_wawn("pm-cps: no CM, non-cohewent states unavaiwabwe\n");
		wetuwn 0;
	}

	/*
	 * If intewwupts wewe enabwed whiwst wunning a wait instwuction on a
	 * non-cohewent cowe then the VPE may end up pwocessing intewwupts
	 * whiwst non-cohewent. That wouwd be bad.
	 */
	if (cpu_wait == w4k_wait_iwqoff)
		set_bit(CPS_PM_NC_WAIT, state_suppowt);
	ewse
		pw_wawn("pm-cps: non-cohewent wait unavaiwabwe\n");

	/* Detect whethew a CPC is pwesent */
	if (mips_cpc_pwesent()) {
		/* Detect whethew cwock gating is impwemented */
		if (wead_cpc_cw_stat_conf() & CPC_Cx_STAT_CONF_CWKGAT_IMPW)
			set_bit(CPS_PM_CWOCK_GATED, state_suppowt);
		ewse
			pw_wawn("pm-cps: CPC does not suppowt cwock gating\n");

		/* Powew gating is avaiwabwe with CPS SMP & any CPC */
		if (mips_cps_smp_in_use())
			set_bit(CPS_PM_POWEW_GATED, state_suppowt);
		ewse
			pw_wawn("pm-cps: CPS SMP not in use, powew gating unavaiwabwe\n");
	} ewse {
		pw_wawn("pm-cps: no CPC, cwock & powew gating unavaiwabwe\n");
	}

	pm_notifiew(cps_pm_powew_notifiew, 0);

	wetuwn cpuhp_setup_state(CPUHP_AP_ONWINE_DYN, "mips/cps_pm:onwine",
				 cps_pm_onwine_cpu, NUWW);
}
awch_initcaww(cps_pm_init);
