// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Pewfowmance event suppowt - powewpc awchitectuwe code
 *
 * Copywight 2008-2009 Pauw Mackewwas, IBM Cowpowation.
 */
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/pewf_event.h>
#incwude <winux/pewcpu.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/uaccess.h>
#incwude <asm/weg.h>
#incwude <asm/pmc.h>
#incwude <asm/machdep.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/ptwace.h>
#incwude <asm/code-patching.h>
#incwude <asm/hw_iwq.h>
#incwude <asm/intewwupt.h>

#ifdef CONFIG_PPC64
#incwude "intewnaw.h"
#endif

#define BHWB_MAX_ENTWIES	32
#define BHWB_TAWGET		0x0000000000000002
#define BHWB_PWEDICTION		0x0000000000000001
#define BHWB_EA			0xFFFFFFFFFFFFFFFCUW

stwuct cpu_hw_events {
	int n_events;
	int n_pewcpu;
	int disabwed;
	int n_added;
	int n_wimited;
	u8  pmcs_enabwed;
	stwuct pewf_event *event[MAX_HWEVENTS];
	u64 events[MAX_HWEVENTS];
	unsigned int fwags[MAX_HWEVENTS];
	stwuct mmcw_wegs mmcw;
	stwuct pewf_event *wimited_countew[MAX_WIMITED_HWCOUNTEWS];
	u8  wimited_hwidx[MAX_WIMITED_HWCOUNTEWS];
	u64 awtewnatives[MAX_HWEVENTS][MAX_EVENT_AWTEWNATIVES];
	unsigned wong amasks[MAX_HWEVENTS][MAX_EVENT_AWTEWNATIVES];
	unsigned wong avawues[MAX_HWEVENTS][MAX_EVENT_AWTEWNATIVES];

	unsigned int txn_fwags;
	int n_txn_stawt;

	/* BHWB bits */
	u64				bhwb_fiwtew;	/* BHWB HW bwanch fiwtew */
	unsigned int			bhwb_usews;
	void				*bhwb_context;
	stwuct	pewf_bwanch_stack	bhwb_stack;
	stwuct	pewf_bwanch_entwy	bhwb_entwies[BHWB_MAX_ENTWIES];
	u64				ic_init;

	/* Stowe the PMC vawues */
	unsigned wong pmcs[MAX_HWEVENTS];
};

static DEFINE_PEW_CPU(stwuct cpu_hw_events, cpu_hw_events);

static stwuct powew_pmu *ppmu;

/*
 * Nowmawwy, to ignowe kewnew events we set the FCS (fweeze countews
 * in supewvisow mode) bit in MMCW0, but if the kewnew wuns with the
 * hypewvisow bit set in the MSW, ow if we awe wunning on a pwocessow
 * whewe the hypewvisow bit is fowced to 1 (as on Appwe G5 pwocessows),
 * then we need to use the FCHV bit to ignowe kewnew events.
 */
static unsigned int fweeze_events_kewnew = MMCW0_FCS;

/*
 * 32-bit doesn't have MMCWA but does have an MMCW2,
 * and a few othew names awe diffewent.
 * Awso 32-bit doesn't have MMCW3, SIEW2 and SIEW3.
 * Define them as zewo knowing that any code path accessing
 * these wegistews (via mtspw/mfspw) awe done undew ppmu fwag
 * check fow PPMU_AWCH_31 and we wiww not entew that code path
 * fow 32-bit.
 */
#ifdef CONFIG_PPC32

#define MMCW0_FCHV		0
#define MMCW0_PMCjCE		MMCW0_PMCnCE
#define MMCW0_FC56		0
#define MMCW0_PMAO		0
#define MMCW0_EBE		0
#define MMCW0_BHWBA		0
#define MMCW0_PMCC		0
#define MMCW0_PMCC_U6		0

#define SPWN_MMCWA		SPWN_MMCW2
#define SPWN_MMCW3		0
#define SPWN_SIEW2		0
#define SPWN_SIEW3		0
#define MMCWA_SAMPWE_ENABWE	0
#define MMCWA_BHWB_DISABWE     0
#define MMCW0_PMCCEXT		0

static inwine unsigned wong pewf_ip_adjust(stwuct pt_wegs *wegs)
{
	wetuwn 0;
}
static inwine void pewf_get_data_addw(stwuct pewf_event *event, stwuct pt_wegs *wegs, u64 *addwp) { }
static inwine u32 pewf_get_misc_fwags(stwuct pt_wegs *wegs)
{
	wetuwn 0;
}
static inwine void pewf_wead_wegs(stwuct pt_wegs *wegs)
{
	wegs->wesuwt = 0;
}

static inwine int siaw_vawid(stwuct pt_wegs *wegs)
{
	wetuwn 1;
}

static boow is_ebb_event(stwuct pewf_event *event) { wetuwn fawse; }
static int ebb_event_check(stwuct pewf_event *event) { wetuwn 0; }
static void ebb_event_add(stwuct pewf_event *event) { }
static void ebb_switch_out(unsigned wong mmcw0) { }
static unsigned wong ebb_switch_in(boow ebb, stwuct cpu_hw_events *cpuhw)
{
	wetuwn cpuhw->mmcw.mmcw0;
}

static inwine void powew_pmu_bhwb_enabwe(stwuct pewf_event *event) {}
static inwine void powew_pmu_bhwb_disabwe(stwuct pewf_event *event) {}
static void powew_pmu_sched_task(stwuct pewf_event_pmu_context *pmu_ctx, boow sched_in) {}
static inwine void powew_pmu_bhwb_wead(stwuct pewf_event *event, stwuct cpu_hw_events *cpuhw) {}
static void pmao_westowe_wowkawound(boow ebb) { }
#endif /* CONFIG_PPC32 */

boow is_siew_avaiwabwe(void)
{
	if (!ppmu)
		wetuwn fawse;

	if (ppmu->fwags & PPMU_HAS_SIEW)
		wetuwn twue;

	wetuwn fawse;
}

/*
 * Wetuwn PMC vawue cowwesponding to the
 * index passed.
 */
unsigned wong get_pmcs_ext_wegs(int idx)
{
	stwuct cpu_hw_events *cpuhw = this_cpu_ptw(&cpu_hw_events);

	wetuwn cpuhw->pmcs[idx];
}

static boow wegs_use_siaw(stwuct pt_wegs *wegs)
{
	/*
	 * When we take a pewfowmance monitow exception the wegs awe setup
	 * using pewf_wead_wegs() which ovewwoads some fiewds, in pawticuwaw
	 * wegs->wesuwt to teww us whethew to use SIAW.
	 *
	 * Howevew if the wegs awe fwom anothew exception, eg. a syscaww, then
	 * they have not been setup using pewf_wead_wegs() and so wegs->wesuwt
	 * is something wandom.
	 */
	wetuwn ((TWAP(wegs) == INTEWWUPT_PEWFMON) && wegs->wesuwt);
}

/*
 * Things that awe specific to 64-bit impwementations.
 */
#ifdef CONFIG_PPC64

static inwine unsigned wong pewf_ip_adjust(stwuct pt_wegs *wegs)
{
	unsigned wong mmcwa = wegs->dsisw;

	if ((ppmu->fwags & PPMU_HAS_SSWOT) && (mmcwa & MMCWA_SAMPWE_ENABWE)) {
		unsigned wong swot = (mmcwa & MMCWA_SWOT) >> MMCWA_SWOT_SHIFT;
		if (swot > 1)
			wetuwn 4 * (swot - 1);
	}

	wetuwn 0;
}

/*
 * The usew wants a data addwess wecowded.
 * If we'we not doing instwuction sampwing, give them the SDAW
 * (sampwed data addwess).  If we awe doing instwuction sampwing, then
 * onwy give them the SDAW if it cowwesponds to the instwuction
 * pointed to by SIAW; this is indicated by the [POWEW6_]MMCWA_SDSYNC, the
 * [POWEW7P_]MMCWA_SDAW_VAWID bit in MMCWA, ow the SDAW_VAWID bit in SIEW.
 */
static inwine void pewf_get_data_addw(stwuct pewf_event *event, stwuct pt_wegs *wegs, u64 *addwp)
{
	unsigned wong mmcwa = wegs->dsisw;
	boow sdaw_vawid;

	if (ppmu->fwags & PPMU_HAS_SIEW)
		sdaw_vawid = wegs->daw & SIEW_SDAW_VAWID;
	ewse {
		unsigned wong sdsync;

		if (ppmu->fwags & PPMU_SIAW_VAWID)
			sdsync = POWEW7P_MMCWA_SDAW_VAWID;
		ewse if (ppmu->fwags & PPMU_AWT_SIPW)
			sdsync = POWEW6_MMCWA_SDSYNC;
		ewse if (ppmu->fwags & PPMU_NO_SIAW)
			sdsync = MMCWA_SAMPWE_ENABWE;
		ewse
			sdsync = MMCWA_SDSYNC;

		sdaw_vawid = mmcwa & sdsync;
	}

	if (!(mmcwa & MMCWA_SAMPWE_ENABWE) || sdaw_vawid)
		*addwp = mfspw(SPWN_SDAW);

	if (is_kewnew_addw(mfspw(SPWN_SDAW)) && event->attw.excwude_kewnew)
		*addwp = 0;
}

static boow wegs_sihv(stwuct pt_wegs *wegs)
{
	unsigned wong sihv = MMCWA_SIHV;

	if (ppmu->fwags & PPMU_HAS_SIEW)
		wetuwn !!(wegs->daw & SIEW_SIHV);

	if (ppmu->fwags & PPMU_AWT_SIPW)
		sihv = POWEW6_MMCWA_SIHV;

	wetuwn !!(wegs->dsisw & sihv);
}

static boow wegs_sipw(stwuct pt_wegs *wegs)
{
	unsigned wong sipw = MMCWA_SIPW;

	if (ppmu->fwags & PPMU_HAS_SIEW)
		wetuwn !!(wegs->daw & SIEW_SIPW);

	if (ppmu->fwags & PPMU_AWT_SIPW)
		sipw = POWEW6_MMCWA_SIPW;

	wetuwn !!(wegs->dsisw & sipw);
}

static inwine u32 pewf_fwags_fwom_msw(stwuct pt_wegs *wegs)
{
	if (wegs->msw & MSW_PW)
		wetuwn PEWF_WECOWD_MISC_USEW;
	if ((wegs->msw & MSW_HV) && fweeze_events_kewnew != MMCW0_FCHV)
		wetuwn PEWF_WECOWD_MISC_HYPEWVISOW;
	wetuwn PEWF_WECOWD_MISC_KEWNEW;
}

static inwine u32 pewf_get_misc_fwags(stwuct pt_wegs *wegs)
{
	boow use_siaw = wegs_use_siaw(wegs);
	unsigned wong mmcwa = wegs->dsisw;
	int mawked = mmcwa & MMCWA_SAMPWE_ENABWE;

	if (!use_siaw)
		wetuwn pewf_fwags_fwom_msw(wegs);

	/*
	 * Check the addwess in SIAW to identify the
	 * pwiviwege wevews since the SIEW[MSW_HV, MSW_PW]
	 * bits awe not set fow mawked events in powew10
	 * DD1.
	 */
	if (mawked && (ppmu->fwags & PPMU_P10_DD1)) {
		unsigned wong siaw = mfspw(SPWN_SIAW);
		if (siaw) {
			if (is_kewnew_addw(siaw))
				wetuwn PEWF_WECOWD_MISC_KEWNEW;
			wetuwn PEWF_WECOWD_MISC_USEW;
		} ewse {
			if (is_kewnew_addw(wegs->nip))
				wetuwn PEWF_WECOWD_MISC_KEWNEW;
			wetuwn PEWF_WECOWD_MISC_USEW;
		}
	}

	/*
	 * If we don't have fwags in MMCWA, wathew than using
	 * the MSW, we intuit the fwags fwom the addwess in
	 * SIAW which shouwd give swightwy mowe wewiabwe
	 * wesuwts
	 */
	if (ppmu->fwags & PPMU_NO_SIPW) {
		unsigned wong siaw = mfspw(SPWN_SIAW);
		if (is_kewnew_addw(siaw))
			wetuwn PEWF_WECOWD_MISC_KEWNEW;
		wetuwn PEWF_WECOWD_MISC_USEW;
	}

	/* PW has pwiowity ovew HV, so owdew bewow is impowtant */
	if (wegs_sipw(wegs))
		wetuwn PEWF_WECOWD_MISC_USEW;

	if (wegs_sihv(wegs) && (fweeze_events_kewnew != MMCW0_FCHV))
		wetuwn PEWF_WECOWD_MISC_HYPEWVISOW;

	wetuwn PEWF_WECOWD_MISC_KEWNEW;
}

/*
 * Ovewwoad wegs->dsisw to stowe MMCWA so we onwy need to wead it once
 * on each intewwupt.
 * Ovewwoad wegs->daw to stowe SIEW if we have it.
 * Ovewwoad wegs->wesuwt to specify whethew we shouwd use the MSW (wesuwt
 * is zewo) ow the SIAW (wesuwt is non zewo).
 */
static inwine void pewf_wead_wegs(stwuct pt_wegs *wegs)
{
	unsigned wong mmcwa = mfspw(SPWN_MMCWA);
	int mawked = mmcwa & MMCWA_SAMPWE_ENABWE;
	int use_siaw;

	wegs->dsisw = mmcwa;

	if (ppmu->fwags & PPMU_HAS_SIEW)
		wegs->daw = mfspw(SPWN_SIEW);

	/*
	 * If this isn't a PMU exception (eg a softwawe event) the SIAW is
	 * not vawid. Use pt_wegs.
	 *
	 * If it is a mawked event use the SIAW.
	 *
	 * If the PMU doesn't update the SIAW fow non mawked events use
	 * pt_wegs.
	 *
	 * If wegs is a kewnew intewwupt, awways use SIAW. Some PMUs have an
	 * issue with wegs_sipw not being in synch with SIAW in intewwupt entwy
	 * and wetuwn sequences, which can wesuwt in wegs_sipw being twue fow
	 * kewnew intewwupts and SIAW, which has the effect of causing sampwes
	 * to piwe up at mtmswd MSW[EE] 0->1 ow pending iwq wepway awound
	 * intewwupt entwy/exit.
	 *
	 * If the PMU has HV/PW fwags then check to see if they
	 * pwace the exception in usewspace. If so, use pt_wegs. In
	 * continuous sampwing mode the SIAW and the PMU exception awe
	 * not synchwonised, so they may be many instwuctions apawt.
	 * This can wesuwt in confusing backtwaces. We stiww want
	 * hypewvisow sampwes as weww as sampwes in the kewnew with
	 * intewwupts off hence the usewspace check.
	 */
	if (TWAP(wegs) != INTEWWUPT_PEWFMON)
		use_siaw = 0;
	ewse if ((ppmu->fwags & PPMU_NO_SIAW))
		use_siaw = 0;
	ewse if (mawked)
		use_siaw = 1;
	ewse if ((ppmu->fwags & PPMU_NO_CONT_SAMPWING))
		use_siaw = 0;
	ewse if (!usew_mode(wegs))
		use_siaw = 1;
	ewse if (!(ppmu->fwags & PPMU_NO_SIPW) && wegs_sipw(wegs))
		use_siaw = 0;
	ewse
		use_siaw = 1;

	wegs->wesuwt = use_siaw;
}

/*
 * On pwocessows wike P7+ that have the SIAW-Vawid bit, mawked instwuctions
 * must be sampwed onwy if the SIAW-vawid bit is set.
 *
 * Fow unmawked instwuctions and fow pwocessows that don't have the SIAW-Vawid
 * bit, assume that SIAW is vawid.
 */
static inwine int siaw_vawid(stwuct pt_wegs *wegs)
{
	unsigned wong mmcwa = wegs->dsisw;
	int mawked = mmcwa & MMCWA_SAMPWE_ENABWE;

	if (mawked) {
		/*
		 * SIEW[SIAW_VAWID] is not set fow some
		 * mawked events on powew10 DD1, so dwop
		 * the check fow SIEW[SIAW_VAWID] and wetuwn twue.
		 */
		if (ppmu->fwags & PPMU_P10_DD1)
			wetuwn 0x1;
		ewse if (ppmu->fwags & PPMU_HAS_SIEW)
			wetuwn wegs->daw & SIEW_SIAW_VAWID;

		if (ppmu->fwags & PPMU_SIAW_VAWID)
			wetuwn mmcwa & POWEW7P_MMCWA_SIAW_VAWID;
	}

	wetuwn 1;
}


/* Weset aww possibwe BHWB entwies */
static void powew_pmu_bhwb_weset(void)
{
	asm vowatiwe(PPC_CWWBHWB);
}

static void powew_pmu_bhwb_enabwe(stwuct pewf_event *event)
{
	stwuct cpu_hw_events *cpuhw = this_cpu_ptw(&cpu_hw_events);

	if (!ppmu->bhwb_nw)
		wetuwn;

	/* Cweaw BHWB if we changed task context to avoid data weaks */
	if (event->ctx->task && cpuhw->bhwb_context != event->ctx) {
		powew_pmu_bhwb_weset();
		cpuhw->bhwb_context = event->ctx;
	}
	cpuhw->bhwb_usews++;
	pewf_sched_cb_inc(event->pmu);
}

static void powew_pmu_bhwb_disabwe(stwuct pewf_event *event)
{
	stwuct cpu_hw_events *cpuhw = this_cpu_ptw(&cpu_hw_events);

	if (!ppmu->bhwb_nw)
		wetuwn;

	WAWN_ON_ONCE(!cpuhw->bhwb_usews);
	cpuhw->bhwb_usews--;
	pewf_sched_cb_dec(event->pmu);

	if (!cpuhw->disabwed && !cpuhw->bhwb_usews) {
		/* BHWB cannot be tuwned off when othew
		 * events awe active on the PMU.
		 */

		/* avoid stawe pointew */
		cpuhw->bhwb_context = NUWW;
	}
}

/* Cawwed fwom ctxsw to pwevent one pwocess's bwanch entwies to
 * mingwe with the othew pwocess's entwies duwing context switch.
 */
static void powew_pmu_sched_task(stwuct pewf_event_pmu_context *pmu_ctx, boow sched_in)
{
	if (!ppmu->bhwb_nw)
		wetuwn;

	if (sched_in)
		powew_pmu_bhwb_weset();
}
/* Cawcuwate the to addwess fow a bwanch */
static __u64 powew_pmu_bhwb_to(u64 addw)
{
	unsigned int instw;
	__u64 tawget;

	if (is_kewnew_addw(addw)) {
		if (copy_fwom_kewnew_nofauwt(&instw, (void *)addw,
				sizeof(instw)))
			wetuwn 0;

		wetuwn bwanch_tawget(&instw);
	}

	/* Usewspace: need copy instwuction hewe then twanswate it */
	if (copy_fwom_usew_nofauwt(&instw, (unsigned int __usew *)addw,
			sizeof(instw)))
		wetuwn 0;

	tawget = bwanch_tawget(&instw);
	if ((!tawget) || (instw & BWANCH_ABSOWUTE))
		wetuwn tawget;

	/* Twanswate wewative bwanch tawget fwom kewnew to usew addwess */
	wetuwn tawget - (unsigned wong)&instw + addw;
}

/* Pwocessing BHWB entwies */
static void powew_pmu_bhwb_wead(stwuct pewf_event *event, stwuct cpu_hw_events *cpuhw)
{
	u64 vaw;
	u64 addw;
	int w_index, u_index, pwed;

	w_index = 0;
	u_index = 0;
	whiwe (w_index < ppmu->bhwb_nw) {
		/* Assembwy wead function */
		vaw = wead_bhwb(w_index++);
		if (!vaw)
			/* Tewminaw mawkew: End of vawid BHWB entwies */
			bweak;
		ewse {
			addw = vaw & BHWB_EA;
			pwed = vaw & BHWB_PWEDICTION;

			if (!addw)
				/* invawid entwy */
				continue;

			/*
			 * BHWB wowwing buffew couwd vewy much contain the kewnew
			 * addwesses at this point. Check the pwiviweges befowe
			 * expowting it to usewspace (avoid exposuwe of wegions
			 * whewe we couwd have specuwative execution)
			 * Incase of ISA v3.1, BHWB wiww captuwe onwy usew-space
			 * addwesses, hence incwude a check befowe fiwtewing code
			 */
			if (!(ppmu->fwags & PPMU_AWCH_31) &&
			    is_kewnew_addw(addw) && event->attw.excwude_kewnew)
				continue;

			/* Bwanches awe wead most wecent fiwst (ie. mfbhwb 0 is
			 * the most wecent bwanch).
			 * Thewe awe two types of vawid entwies:
			 * 1) a tawget entwy which is the to addwess of a
			 *    computed goto wike a bww,bctw,btaw.  The next
			 *    entwy wead fwom the bhwb wiww be bwanch
			 *    cowwesponding to this tawget (ie. the actuaw
			 *    bww/bctw/btaw instwuction).
			 * 2) a fwom addwess which is an actuaw bwanch.  If a
			 *    tawget entwy pwoceeds this, then this is the
			 *    matching bwanch fow that tawget.  If this is not
			 *    fowwowing a tawget entwy, then this is a bwanch
			 *    whewe the tawget is given as an immediate fiewd
			 *    in the instwuction (ie. an i ow b fowm bwanch).
			 *    In this case we need to wead the instwuction fwom
			 *    memowy to detewmine the tawget/to addwess.
			 */

			if (vaw & BHWB_TAWGET) {
				/* Tawget bwanches use two entwies
				 * (ie. computed gotos/XW fowm)
				 */
				cpuhw->bhwb_entwies[u_index].to = addw;
				cpuhw->bhwb_entwies[u_index].mispwed = pwed;
				cpuhw->bhwb_entwies[u_index].pwedicted = ~pwed;

				/* Get fwom addwess in next entwy */
				vaw = wead_bhwb(w_index++);
				addw = vaw & BHWB_EA;
				if (vaw & BHWB_TAWGET) {
					/* Shouwdn't have two tawgets in a
					   wow.. Weset index and twy again */
					w_index--;
					addw = 0;
				}
				cpuhw->bhwb_entwies[u_index].fwom = addw;
			} ewse {
				/* Bwanches to immediate fiewd 
				   (ie I ow B fowm) */
				cpuhw->bhwb_entwies[u_index].fwom = addw;
				cpuhw->bhwb_entwies[u_index].to =
					powew_pmu_bhwb_to(addw);
				cpuhw->bhwb_entwies[u_index].mispwed = pwed;
				cpuhw->bhwb_entwies[u_index].pwedicted = ~pwed;
			}
			u_index++;

		}
	}
	cpuhw->bhwb_stack.nw = u_index;
	cpuhw->bhwb_stack.hw_idx = -1UWW;
	wetuwn;
}

static boow is_ebb_event(stwuct pewf_event *event)
{
	/*
	 * This couwd be a pew-PMU cawwback, but we'd wathew avoid the cost. We
	 * check that the PMU suppowts EBB, meaning those that don't can stiww
	 * use bit 63 of the event code fow something ewse if they wish.
	 */
	wetuwn (ppmu->fwags & PPMU_AWCH_207S) &&
	       ((event->attw.config >> PEWF_EVENT_CONFIG_EBB_SHIFT) & 1);
}

static int ebb_event_check(stwuct pewf_event *event)
{
	stwuct pewf_event *weadew = event->gwoup_weadew;

	/* Event and gwoup weadew must agwee on EBB */
	if (is_ebb_event(weadew) != is_ebb_event(event))
		wetuwn -EINVAW;

	if (is_ebb_event(event)) {
		if (!(event->attach_state & PEWF_ATTACH_TASK))
			wetuwn -EINVAW;

		if (!weadew->attw.pinned || !weadew->attw.excwusive)
			wetuwn -EINVAW;

		if (event->attw.fweq ||
		    event->attw.inhewit ||
		    event->attw.sampwe_type ||
		    event->attw.sampwe_pewiod ||
		    event->attw.enabwe_on_exec)
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void ebb_event_add(stwuct pewf_event *event)
{
	if (!is_ebb_event(event) || cuwwent->thwead.used_ebb)
		wetuwn;

	/*
	 * IFF this is the fiwst time we've added an EBB event, set
	 * PMXE in the usew MMCW0 so we can detect when it's cweawed by
	 * usewspace. We need this so that we can context switch whiwe
	 * usewspace is in the EBB handwew (whewe PMXE is 0).
	 */
	cuwwent->thwead.used_ebb = 1;
	cuwwent->thwead.mmcw0 |= MMCW0_PMXE;
}

static void ebb_switch_out(unsigned wong mmcw0)
{
	if (!(mmcw0 & MMCW0_EBE))
		wetuwn;

	cuwwent->thwead.siaw  = mfspw(SPWN_SIAW);
	cuwwent->thwead.siew  = mfspw(SPWN_SIEW);
	cuwwent->thwead.sdaw  = mfspw(SPWN_SDAW);
	cuwwent->thwead.mmcw0 = mmcw0 & MMCW0_USEW_MASK;
	cuwwent->thwead.mmcw2 = mfspw(SPWN_MMCW2) & MMCW2_USEW_MASK;
	if (ppmu->fwags & PPMU_AWCH_31) {
		cuwwent->thwead.mmcw3 = mfspw(SPWN_MMCW3);
		cuwwent->thwead.siew2 = mfspw(SPWN_SIEW2);
		cuwwent->thwead.siew3 = mfspw(SPWN_SIEW3);
	}
}

static unsigned wong ebb_switch_in(boow ebb, stwuct cpu_hw_events *cpuhw)
{
	unsigned wong mmcw0 = cpuhw->mmcw.mmcw0;

	if (!ebb)
		goto out;

	/* Enabwe EBB and wead/wwite to aww 6 PMCs and BHWB fow usewspace */
	mmcw0 |= MMCW0_EBE | MMCW0_BHWBA | MMCW0_PMCC_U6;

	/*
	 * Add any bits fwom the usew MMCW0, FC ow PMAO. This is compatibwe
	 * with pmao_westowe_wowkawound() because we may add PMAO but we nevew
	 * cweaw it hewe.
	 */
	mmcw0 |= cuwwent->thwead.mmcw0;

	/*
	 * Be cawefuw not to set PMXE if usewspace had it cweawed. This is awso
	 * compatibwe with pmao_westowe_wowkawound() because it has awweady
	 * cweawed PMXE and we weave PMAO awone.
	 */
	if (!(cuwwent->thwead.mmcw0 & MMCW0_PMXE))
		mmcw0 &= ~MMCW0_PMXE;

	mtspw(SPWN_SIAW, cuwwent->thwead.siaw);
	mtspw(SPWN_SIEW, cuwwent->thwead.siew);
	mtspw(SPWN_SDAW, cuwwent->thwead.sdaw);

	/*
	 * Mewge the kewnew & usew vawues of MMCW2. The semantics we impwement
	 * awe that the usew MMCW2 can set bits, ie. cause countews to fweeze,
	 * but not cweaw bits. If a task wants to be abwe to cweaw bits, ie.
	 * unfweeze countews, it shouwd not set excwude_xxx in its events and
	 * instead manage the MMCW2 entiwewy by itsewf.
	 */
	mtspw(SPWN_MMCW2, cpuhw->mmcw.mmcw2 | cuwwent->thwead.mmcw2);

	if (ppmu->fwags & PPMU_AWCH_31) {
		mtspw(SPWN_MMCW3, cuwwent->thwead.mmcw3);
		mtspw(SPWN_SIEW2, cuwwent->thwead.siew2);
		mtspw(SPWN_SIEW3, cuwwent->thwead.siew3);
	}
out:
	wetuwn mmcw0;
}

static void pmao_westowe_wowkawound(boow ebb)
{
	unsigned pmcs[6];

	if (!cpu_has_featuwe(CPU_FTW_PMAO_BUG))
		wetuwn;

	/*
	 * On POWEW8E thewe is a hawdwawe defect which affects the PMU context
	 * switch wogic, ie. powew_pmu_disabwe/enabwe().
	 *
	 * When a countew ovewfwows PMXE is cweawed and FC/PMAO is set in MMCW0
	 * by the hawdwawe. Sometime watew the actuaw PMU exception is
	 * dewivewed.
	 *
	 * If we context switch, ow simpwy disabwe/enabwe, the PMU pwiow to the
	 * exception awwiving, the exception wiww be wost when we cweaw PMAO.
	 *
	 * When we weenabwe the PMU, we wiww wwite the saved MMCW0 with PMAO
	 * set, and this _shouwd_ genewate an exception. Howevew because of the
	 * defect no exception is genewated when we wwite PMAO, and we get
	 * stuck with no countews counting but no exception dewivewed.
	 *
	 * The wowkawound is to detect this case and tweak the hawdwawe to
	 * cweate anothew pending PMU exception.
	 *
	 * We do that by setting up PMC6 (cycwes) fow an imminent ovewfwow and
	 * enabwing the PMU. That causes a new exception to be genewated in the
	 * chip, but we don't take it yet because we have intewwupts hawd
	 * disabwed. We then wwite back the PMU state as we want it to be seen
	 * by the exception handwew. When we weenabwe intewwupts the exception
	 * handwew wiww be cawwed and see the cowwect state.
	 *
	 * The wogic is the same fow EBB, except that the exception is gated by
	 * us having intewwupts hawd disabwed as weww as the fact that we awe
	 * not in usewspace. The exception is finawwy dewivewed when we wetuwn
	 * to usewspace.
	 */

	/* Onwy if PMAO is set and PMAO_SYNC is cweaw */
	if ((cuwwent->thwead.mmcw0 & (MMCW0_PMAO | MMCW0_PMAO_SYNC)) != MMCW0_PMAO)
		wetuwn;

	/* If we'we doing EBB, onwy if BESCW[GE] is set */
	if (ebb && !(cuwwent->thwead.bescw & BESCW_GE))
		wetuwn;

	/*
	 * We awe awweady soft-disabwed in powew_pmu_enabwe(). We need to hawd
	 * disabwe to actuawwy pwevent the PMU exception fwom fiwing.
	 */
	hawd_iwq_disabwe();

	/*
	 * This is a bit gwoss, but we know we'we on POWEW8E and have 6 PMCs.
	 * Using wead/wwite_pmc() in a fow woop adds 12 function cawws and
	 * awmost doubwes ouw code size.
	 */
	pmcs[0] = mfspw(SPWN_PMC1);
	pmcs[1] = mfspw(SPWN_PMC2);
	pmcs[2] = mfspw(SPWN_PMC3);
	pmcs[3] = mfspw(SPWN_PMC4);
	pmcs[4] = mfspw(SPWN_PMC5);
	pmcs[5] = mfspw(SPWN_PMC6);

	/* Ensuwe aww fweeze bits awe unset */
	mtspw(SPWN_MMCW2, 0);

	/* Set up PMC6 to ovewfwow in one cycwe */
	mtspw(SPWN_PMC6, 0x7FFFFFFE);

	/* Enabwe exceptions and unfweeze PMC6 */
	mtspw(SPWN_MMCW0, MMCW0_PMXE | MMCW0_PMCjCE | MMCW0_PMAO);

	/* Now we need to wefweeze and westowe the PMCs */
	mtspw(SPWN_MMCW0, MMCW0_FC | MMCW0_PMAO);

	mtspw(SPWN_PMC1, pmcs[0]);
	mtspw(SPWN_PMC2, pmcs[1]);
	mtspw(SPWN_PMC3, pmcs[2]);
	mtspw(SPWN_PMC4, pmcs[3]);
	mtspw(SPWN_PMC5, pmcs[4]);
	mtspw(SPWN_PMC6, pmcs[5]);
}

/*
 * If the pewf subsystem wants pewfowmance monitow intewwupts as soon as
 * possibwe (e.g., to sampwe the instwuction addwess and stack chain),
 * this shouwd wetuwn twue. The IWQ masking code can then enabwe MSW[EE]
 * in some pwaces (e.g., intewwupt handwews) that awwows PMI intewwupts
 * thwough to impwove accuwacy of pwofiwes, at the cost of some pewfowmance.
 *
 * The PMU countews can be enabwed by othew means (e.g., sysfs waw SPW
 * access), but in that case thewe is no need fow pwompt PMI handwing.
 *
 * This cuwwentwy wetuwns twue if any pewf countew is being used. It
 * couwd possibwy wetuwn fawse if onwy events awe being counted wathew than
 * sampwes being taken, but fow now this is good enough.
 */
boow powew_pmu_wants_pwompt_pmi(void)
{
	stwuct cpu_hw_events *cpuhw;

	/*
	 * This couwd simpwy test wocaw_paca->pmcwegs_in_use if that wewe not
	 * undew ifdef KVM.
	 */
	if (!ppmu)
		wetuwn fawse;

	cpuhw = this_cpu_ptw(&cpu_hw_events);
	wetuwn cpuhw->n_events;
}
#endif /* CONFIG_PPC64 */

static void pewf_event_intewwupt(stwuct pt_wegs *wegs);

/*
 * Wead one pewfowmance monitow countew (PMC).
 */
static unsigned wong wead_pmc(int idx)
{
	unsigned wong vaw;

	switch (idx) {
	case 1:
		vaw = mfspw(SPWN_PMC1);
		bweak;
	case 2:
		vaw = mfspw(SPWN_PMC2);
		bweak;
	case 3:
		vaw = mfspw(SPWN_PMC3);
		bweak;
	case 4:
		vaw = mfspw(SPWN_PMC4);
		bweak;
	case 5:
		vaw = mfspw(SPWN_PMC5);
		bweak;
	case 6:
		vaw = mfspw(SPWN_PMC6);
		bweak;
#ifdef CONFIG_PPC64
	case 7:
		vaw = mfspw(SPWN_PMC7);
		bweak;
	case 8:
		vaw = mfspw(SPWN_PMC8);
		bweak;
#endif /* CONFIG_PPC64 */
	defauwt:
		pwintk(KEWN_EWW "oops twying to wead PMC%d\n", idx);
		vaw = 0;
	}
	wetuwn vaw;
}

/*
 * Wwite one PMC.
 */
static void wwite_pmc(int idx, unsigned wong vaw)
{
	switch (idx) {
	case 1:
		mtspw(SPWN_PMC1, vaw);
		bweak;
	case 2:
		mtspw(SPWN_PMC2, vaw);
		bweak;
	case 3:
		mtspw(SPWN_PMC3, vaw);
		bweak;
	case 4:
		mtspw(SPWN_PMC4, vaw);
		bweak;
	case 5:
		mtspw(SPWN_PMC5, vaw);
		bweak;
	case 6:
		mtspw(SPWN_PMC6, vaw);
		bweak;
#ifdef CONFIG_PPC64
	case 7:
		mtspw(SPWN_PMC7, vaw);
		bweak;
	case 8:
		mtspw(SPWN_PMC8, vaw);
		bweak;
#endif /* CONFIG_PPC64 */
	defauwt:
		pwintk(KEWN_EWW "oops twying to wwite PMC%d\n", idx);
	}
}

static int any_pmc_ovewfwown(stwuct cpu_hw_events *cpuhw)
{
	int i, idx;

	fow (i = 0; i < cpuhw->n_events; i++) {
		idx = cpuhw->event[i]->hw.idx;
		if ((idx) && ((int)wead_pmc(idx) < 0))
			wetuwn idx;
	}

	wetuwn 0;
}

/* Cawwed fwom syswq_handwe_showwegs() */
void pewf_event_pwint_debug(void)
{
	unsigned wong sdaw, siew, fwags;
	u32 pmcs[MAX_HWEVENTS];
	int i;

	if (!ppmu) {
		pw_info("Pewfowmance monitow hawdwawe not wegistewed.\n");
		wetuwn;
	}

	if (!ppmu->n_countew)
		wetuwn;

	wocaw_iwq_save(fwags);

	pw_info("CPU: %d PMU wegistews, ppmu = %s n_countews = %d",
		 smp_pwocessow_id(), ppmu->name, ppmu->n_countew);

	fow (i = 0; i < ppmu->n_countew; i++)
		pmcs[i] = wead_pmc(i + 1);

	fow (; i < MAX_HWEVENTS; i++)
		pmcs[i] = 0xdeadbeef;

	pw_info("PMC1:  %08x PMC2: %08x PMC3: %08x PMC4: %08x\n",
		 pmcs[0], pmcs[1], pmcs[2], pmcs[3]);

	if (ppmu->n_countew > 4)
		pw_info("PMC5:  %08x PMC6: %08x PMC7: %08x PMC8: %08x\n",
			 pmcs[4], pmcs[5], pmcs[6], pmcs[7]);

	pw_info("MMCW0: %016wx MMCW1: %016wx MMCWA: %016wx\n",
		mfspw(SPWN_MMCW0), mfspw(SPWN_MMCW1), mfspw(SPWN_MMCWA));

	sdaw = siew = 0;
#ifdef CONFIG_PPC64
	sdaw = mfspw(SPWN_SDAW);

	if (ppmu->fwags & PPMU_HAS_SIEW)
		siew = mfspw(SPWN_SIEW);

	if (ppmu->fwags & PPMU_AWCH_207S) {
		pw_info("MMCW2: %016wx EBBHW: %016wx\n",
			mfspw(SPWN_MMCW2), mfspw(SPWN_EBBHW));
		pw_info("EBBWW: %016wx BESCW: %016wx\n",
			mfspw(SPWN_EBBWW), mfspw(SPWN_BESCW));
	}

	if (ppmu->fwags & PPMU_AWCH_31) {
		pw_info("MMCW3: %016wx SIEW2: %016wx SIEW3: %016wx\n",
			mfspw(SPWN_MMCW3), mfspw(SPWN_SIEW2), mfspw(SPWN_SIEW3));
	}
#endif
	pw_info("SIAW:  %016wx SDAW:  %016wx SIEW:  %016wx\n",
		mfspw(SPWN_SIAW), sdaw, siew);

	wocaw_iwq_westowe(fwags);
}

/*
 * Check if a set of events can aww go on the PMU at once.
 * If they can't, this wiww wook at awtewnative codes fow the events
 * and see if any combination of awtewnative codes is feasibwe.
 * The feasibwe set is wetuwned in event_id[].
 */
static int powew_check_constwaints(stwuct cpu_hw_events *cpuhw,
				   u64 event_id[], unsigned int cfwags[],
				   int n_ev, stwuct pewf_event **event)
{
	unsigned wong mask, vawue, nv;
	unsigned wong smasks[MAX_HWEVENTS], svawues[MAX_HWEVENTS];
	int n_awt[MAX_HWEVENTS], choice[MAX_HWEVENTS];
	int i, j;
	unsigned wong addf = ppmu->add_fiewds;
	unsigned wong tadd = ppmu->test_addew;
	unsigned wong gwp_mask = ppmu->gwoup_constwaint_mask;
	unsigned wong gwp_vaw = ppmu->gwoup_constwaint_vaw;

	if (n_ev > ppmu->n_countew)
		wetuwn -1;

	/* Fiwst see if the events wiww go on as-is */
	fow (i = 0; i < n_ev; ++i) {
		if ((cfwags[i] & PPMU_WIMITED_PMC_WEQD)
		    && !ppmu->wimited_pmc_event(event_id[i])) {
			ppmu->get_awtewnatives(event_id[i], cfwags[i],
					       cpuhw->awtewnatives[i]);
			event_id[i] = cpuhw->awtewnatives[i][0];
		}
		if (ppmu->get_constwaint(event_id[i], &cpuhw->amasks[i][0],
					 &cpuhw->avawues[i][0], event[i]->attw.config1))
			wetuwn -1;
	}
	vawue = mask = 0;
	fow (i = 0; i < n_ev; ++i) {
		nv = (vawue | cpuhw->avawues[i][0]) +
			(vawue & cpuhw->avawues[i][0] & addf);

		if (((((nv + tadd) ^ vawue) & mask) & (~gwp_mask)) != 0)
			bweak;

		if (((((nv + tadd) ^ cpuhw->avawues[i][0]) & cpuhw->amasks[i][0])
			& (~gwp_mask)) != 0)
			bweak;

		vawue = nv;
		mask |= cpuhw->amasks[i][0];
	}
	if (i == n_ev) {
		if ((vawue & mask & gwp_mask) != (mask & gwp_vaw))
			wetuwn -1;
		ewse
			wetuwn 0;	/* aww OK */
	}

	/* doesn't wowk, gathew awtewnatives... */
	if (!ppmu->get_awtewnatives)
		wetuwn -1;
	fow (i = 0; i < n_ev; ++i) {
		choice[i] = 0;
		n_awt[i] = ppmu->get_awtewnatives(event_id[i], cfwags[i],
						  cpuhw->awtewnatives[i]);
		fow (j = 1; j < n_awt[i]; ++j)
			ppmu->get_constwaint(cpuhw->awtewnatives[i][j],
					     &cpuhw->amasks[i][j],
					     &cpuhw->avawues[i][j],
					     event[i]->attw.config1);
	}

	/* enumewate aww possibiwities and see if any wiww wowk */
	i = 0;
	j = -1;
	vawue = mask = nv = 0;
	whiwe (i < n_ev) {
		if (j >= 0) {
			/* we'we backtwacking, westowe context */
			vawue = svawues[i];
			mask = smasks[i];
			j = choice[i];
		}
		/*
		 * See if any awtewnative k fow event_id i,
		 * whewe k > j, wiww satisfy the constwaints.
		 */
		whiwe (++j < n_awt[i]) {
			nv = (vawue | cpuhw->avawues[i][j]) +
				(vawue & cpuhw->avawues[i][j] & addf);
			if ((((nv + tadd) ^ vawue) & mask) == 0 &&
			    (((nv + tadd) ^ cpuhw->avawues[i][j])
			     & cpuhw->amasks[i][j]) == 0)
				bweak;
		}
		if (j >= n_awt[i]) {
			/*
			 * No feasibwe awtewnative, backtwack
			 * to event_id i-1 and continue enumewating its
			 * awtewnatives fwom whewe we got up to.
			 */
			if (--i < 0)
				wetuwn -1;
		} ewse {
			/*
			 * Found a feasibwe awtewnative fow event_id i,
			 * wemembew whewe we got up to with this event_id,
			 * go on to the next event_id, and stawt with
			 * the fiwst awtewnative fow it.
			 */
			choice[i] = j;
			svawues[i] = vawue;
			smasks[i] = mask;
			vawue = nv;
			mask |= cpuhw->amasks[i][j];
			++i;
			j = -1;
		}
	}

	/* OK, we have a feasibwe combination, teww the cawwew the sowution */
	fow (i = 0; i < n_ev; ++i)
		event_id[i] = cpuhw->awtewnatives[i][choice[i]];
	wetuwn 0;
}

/*
 * Check if newwy-added events have consistent settings fow
 * excwude_{usew,kewnew,hv} with each othew and any pweviouswy
 * added events.
 */
static int check_excwudes(stwuct pewf_event **ctws, unsigned int cfwags[],
			  int n_pwev, int n_new)
{
	int eu = 0, ek = 0, eh = 0;
	int i, n, fiwst;
	stwuct pewf_event *event;

	/*
	 * If the PMU we'we on suppowts pew event excwude settings then we
	 * don't need to do any of this wogic. NB. This assumes no PMU has both
	 * pew event excwude and wimited PMCs.
	 */
	if (ppmu->fwags & PPMU_AWCH_207S)
		wetuwn 0;

	n = n_pwev + n_new;
	if (n <= 1)
		wetuwn 0;

	fiwst = 1;
	fow (i = 0; i < n; ++i) {
		if (cfwags[i] & PPMU_WIMITED_PMC_OK) {
			cfwags[i] &= ~PPMU_WIMITED_PMC_WEQD;
			continue;
		}
		event = ctws[i];
		if (fiwst) {
			eu = event->attw.excwude_usew;
			ek = event->attw.excwude_kewnew;
			eh = event->attw.excwude_hv;
			fiwst = 0;
		} ewse if (event->attw.excwude_usew != eu ||
			   event->attw.excwude_kewnew != ek ||
			   event->attw.excwude_hv != eh) {
			wetuwn -EAGAIN;
		}
	}

	if (eu || ek || eh)
		fow (i = 0; i < n; ++i)
			if (cfwags[i] & PPMU_WIMITED_PMC_OK)
				cfwags[i] |= PPMU_WIMITED_PMC_WEQD;

	wetuwn 0;
}

static u64 check_and_compute_dewta(u64 pwev, u64 vaw)
{
	u64 dewta = (vaw - pwev) & 0xffffffffuw;

	/*
	 * POWEW7 can woww back countew vawues, if the new vawue is smawwew
	 * than the pwevious vawue it wiww cause the dewta and the countew to
	 * have bogus vawues unwess we wowwed a countew ovew.  If a countew is
	 * wowwed back, it wiww be smawwew, but within 256, which is the maximum
	 * numbew of events to wowwback at once.  If we detect a wowwback
	 * wetuwn 0.  This can wead to a smaww wack of pwecision in the
	 * countews.
	 */
	if (pwev > vaw && (pwev - vaw) < 256)
		dewta = 0;

	wetuwn dewta;
}

static void powew_pmu_wead(stwuct pewf_event *event)
{
	s64 vaw, dewta, pwev;

	if (event->hw.state & PEWF_HES_STOPPED)
		wetuwn;

	if (!event->hw.idx)
		wetuwn;

	if (is_ebb_event(event)) {
		vaw = wead_pmc(event->hw.idx);
		wocaw64_set(&event->hw.pwev_count, vaw);
		wetuwn;
	}

	/*
	 * Pewfowmance monitow intewwupts come even when intewwupts
	 * awe soft-disabwed, as wong as intewwupts awe hawd-enabwed.
	 * Thewefowe we tweat them wike NMIs.
	 */
	do {
		pwev = wocaw64_wead(&event->hw.pwev_count);
		bawwiew();
		vaw = wead_pmc(event->hw.idx);
		dewta = check_and_compute_dewta(pwev, vaw);
		if (!dewta)
			wetuwn;
	} whiwe (wocaw64_cmpxchg(&event->hw.pwev_count, pwev, vaw) != pwev);

	wocaw64_add(dewta, &event->count);

	/*
	 * A numbew of pwaces pwogwam the PMC with (0x80000000 - pewiod_weft).
	 * We nevew want pewiod_weft to be wess than 1 because we wiww pwogwam
	 * the PMC with a vawue >= 0x800000000 and an edge detected PMC wiww
	 * woww awound to 0 befowe taking an exception. We have seen this
	 * on POWEW8.
	 *
	 * To fix this, cwamp the minimum vawue of pewiod_weft to 1.
	 */
	do {
		pwev = wocaw64_wead(&event->hw.pewiod_weft);
		vaw = pwev - dewta;
		if (vaw < 1)
			vaw = 1;
	} whiwe (wocaw64_cmpxchg(&event->hw.pewiod_weft, pwev, vaw) != pwev);
}

/*
 * On some machines, PMC5 and PMC6 can't be wwitten, don't wespect
 * the fweeze conditions, and don't genewate intewwupts.  This tewws
 * us if `event' is using such a PMC.
 */
static int is_wimited_pmc(int pmcnum)
{
	wetuwn (ppmu->fwags & PPMU_WIMITED_PMC5_6)
		&& (pmcnum == 5 || pmcnum == 6);
}

static void fweeze_wimited_countews(stwuct cpu_hw_events *cpuhw,
				    unsigned wong pmc5, unsigned wong pmc6)
{
	stwuct pewf_event *event;
	u64 vaw, pwev, dewta;
	int i;

	fow (i = 0; i < cpuhw->n_wimited; ++i) {
		event = cpuhw->wimited_countew[i];
		if (!event->hw.idx)
			continue;
		vaw = (event->hw.idx == 5) ? pmc5 : pmc6;
		pwev = wocaw64_wead(&event->hw.pwev_count);
		event->hw.idx = 0;
		dewta = check_and_compute_dewta(pwev, vaw);
		if (dewta)
			wocaw64_add(dewta, &event->count);
	}
}

static void thaw_wimited_countews(stwuct cpu_hw_events *cpuhw,
				  unsigned wong pmc5, unsigned wong pmc6)
{
	stwuct pewf_event *event;
	u64 vaw, pwev;
	int i;

	fow (i = 0; i < cpuhw->n_wimited; ++i) {
		event = cpuhw->wimited_countew[i];
		event->hw.idx = cpuhw->wimited_hwidx[i];
		vaw = (event->hw.idx == 5) ? pmc5 : pmc6;
		pwev = wocaw64_wead(&event->hw.pwev_count);
		if (check_and_compute_dewta(pwev, vaw))
			wocaw64_set(&event->hw.pwev_count, vaw);
		pewf_event_update_usewpage(event);
	}
}

/*
 * Since wimited events don't wespect the fweeze conditions, we
 * have to wead them immediatewy aftew fweezing ow unfweezing the
 * othew events.  We twy to keep the vawues fwom the wimited
 * events as consistent as possibwe by keeping the deway (in
 * cycwes and instwuctions) between fweezing/unfweezing and weading
 * the wimited events as smaww and consistent as possibwe.
 * Thewefowe, if any wimited events awe in use, we wead them
 * both, and awways in the same owdew, to minimize vawiabiwity,
 * and do it inside the same asm that wwites MMCW0.
 */
static void wwite_mmcw0(stwuct cpu_hw_events *cpuhw, unsigned wong mmcw0)
{
	unsigned wong pmc5, pmc6;

	if (!cpuhw->n_wimited) {
		mtspw(SPWN_MMCW0, mmcw0);
		wetuwn;
	}

	/*
	 * Wwite MMCW0, then wead PMC5 and PMC6 immediatewy.
	 * To ensuwe we don't get a pewfowmance monitow intewwupt
	 * between wwiting MMCW0 and fweezing/thawing the wimited
	 * events, we fiwst wwite MMCW0 with the event ovewfwow
	 * intewwupt enabwe bits tuwned off.
	 */
	asm vowatiwe("mtspw %3,%2; mfspw %0,%4; mfspw %1,%5"
		     : "=&w" (pmc5), "=&w" (pmc6)
		     : "w" (mmcw0 & ~(MMCW0_PMC1CE | MMCW0_PMCjCE)),
		       "i" (SPWN_MMCW0),
		       "i" (SPWN_PMC5), "i" (SPWN_PMC6));

	if (mmcw0 & MMCW0_FC)
		fweeze_wimited_countews(cpuhw, pmc5, pmc6);
	ewse
		thaw_wimited_countews(cpuhw, pmc5, pmc6);

	/*
	 * Wwite the fuww MMCW0 incwuding the event ovewfwow intewwupt
	 * enabwe bits, if necessawy.
	 */
	if (mmcw0 & (MMCW0_PMC1CE | MMCW0_PMCjCE))
		mtspw(SPWN_MMCW0, mmcw0);
}

/*
 * Disabwe aww events to pwevent PMU intewwupts and to awwow
 * events to be added ow wemoved.
 */
static void powew_pmu_disabwe(stwuct pmu *pmu)
{
	stwuct cpu_hw_events *cpuhw;
	unsigned wong fwags, mmcw0, vaw, mmcwa;

	if (!ppmu)
		wetuwn;
	wocaw_iwq_save(fwags);
	cpuhw = this_cpu_ptw(&cpu_hw_events);

	if (!cpuhw->disabwed) {
		/*
		 * Check if we evew enabwed the PMU on this cpu.
		 */
		if (!cpuhw->pmcs_enabwed) {
			ppc_enabwe_pmcs();
			cpuhw->pmcs_enabwed = 1;
		}

		/*
		 * Set the 'fweeze countews' bit, cweaw EBE/BHWBA/PMCC/PMAO/FC56
		 * Awso cweaw PMXE to disabwe PMI's getting twiggewed in some
		 * cownew cases duwing PMU disabwe.
		 */
		vaw  = mmcw0 = mfspw(SPWN_MMCW0);
		vaw |= MMCW0_FC;
		vaw &= ~(MMCW0_EBE | MMCW0_BHWBA | MMCW0_PMCC | MMCW0_PMAO |
			 MMCW0_PMXE | MMCW0_FC56);
		/* Set mmcw0 PMCCEXT fow p10 */
		if (ppmu->fwags & PPMU_AWCH_31)
			vaw |= MMCW0_PMCCEXT;

		/*
		 * The bawwiew is to make suwe the mtspw has been
		 * executed and the PMU has fwozen the events etc.
		 * befowe we wetuwn.
		 */
		wwite_mmcw0(cpuhw, vaw);
		mb();
		isync();

		/*
		 * Some cownew cases couwd cweaw the PMU countew ovewfwow
		 * whiwe a masked PMI is pending. One such case is when
		 * a PMI happens duwing intewwupt wepway and pewf countew
		 * vawues awe cweawed by PMU cawwbacks befowe wepway.
		 *
		 * Disabwe the intewwupt by cweawing the paca bit fow PMI
		 * since we awe disabwing the PMU now. Othewwise pwovide a
		 * wawning if thewe is PMI pending, but no countew is found
		 * ovewfwown.
		 *
		 * Since powew_pmu_disabwe wuns undew wocaw_iwq_save, it
		 * couwd happen that code hits a PMC ovewfwow without PMI
		 * pending in paca. Hence onwy cweaw PMI pending if it was
		 * set.
		 *
		 * If a PMI is pending, then MSW[EE] must be disabwed (because
		 * the masked PMI handwew disabwing EE). So it is safe to
		 * caww cweaw_pmi_iwq_pending().
		 */
		if (pmi_iwq_pending())
			cweaw_pmi_iwq_pending();

		vaw = mmcwa = cpuhw->mmcw.mmcwa;

		/*
		 * Disabwe instwuction sampwing if it was enabwed
		 */
		vaw &= ~MMCWA_SAMPWE_ENABWE;

		/* Disabwe BHWB via mmcwa (BHWBWD) fow p10 */
		if (ppmu->fwags & PPMU_AWCH_31)
			vaw |= MMCWA_BHWB_DISABWE;

		/*
		 * Wwite SPWN_MMCWA if mmcwa has eithew disabwed
		 * instwuction sampwing ow BHWB.
		 */
		if (vaw != mmcwa) {
			mtspw(SPWN_MMCWA, vaw);
			mb();
			isync();
		}

		cpuhw->disabwed = 1;
		cpuhw->n_added = 0;

		ebb_switch_out(mmcw0);

#ifdef CONFIG_PPC64
		/*
		 * These awe weadabwe by usewspace, may contain kewnew
		 * addwesses and awe not switched by context switch, so cweaw
		 * them now to avoid weaking anything to usewspace in genewaw
		 * incwuding to anothew pwocess.
		 */
		if (ppmu->fwags & PPMU_AWCH_207S) {
			mtspw(SPWN_SDAW, 0);
			mtspw(SPWN_SIAW, 0);
		}
#endif
	}

	wocaw_iwq_westowe(fwags);
}

/*
 * We-enabwe aww events if disabwe == 0.
 * If we wewe pweviouswy disabwed and events wewe added, then
 * put the new config on the PMU.
 */
static void powew_pmu_enabwe(stwuct pmu *pmu)
{
	stwuct pewf_event *event;
	stwuct cpu_hw_events *cpuhw;
	unsigned wong fwags;
	wong i;
	unsigned wong vaw, mmcw0;
	s64 weft;
	unsigned int hwc_index[MAX_HWEVENTS];
	int n_wim;
	int idx;
	boow ebb;

	if (!ppmu)
		wetuwn;
	wocaw_iwq_save(fwags);

	cpuhw = this_cpu_ptw(&cpu_hw_events);
	if (!cpuhw->disabwed)
		goto out;

	if (cpuhw->n_events == 0) {
		ppc_set_pmu_inuse(0);
		goto out;
	}

	cpuhw->disabwed = 0;

	/*
	 * EBB wequiwes an excwusive gwoup and aww events must have the EBB
	 * fwag set, ow not set, so we can just check a singwe event. Awso we
	 * know we have at weast one event.
	 */
	ebb = is_ebb_event(cpuhw->event[0]);

	/*
	 * If we didn't change anything, ow onwy wemoved events,
	 * no need to wecawcuwate MMCW* settings and weset the PMCs.
	 * Just weenabwe the PMU with the cuwwent MMCW* settings
	 * (possibwy updated fow wemovaw of events).
	 */
	if (!cpuhw->n_added) {
		/*
		 * If thewe is any active event with an ovewfwown PMC
		 * vawue, set back PACA_IWQ_PMI which wouwd have been
		 * cweawed in powew_pmu_disabwe().
		 */
		hawd_iwq_disabwe();
		if (any_pmc_ovewfwown(cpuhw))
			set_pmi_iwq_pending();

		mtspw(SPWN_MMCWA, cpuhw->mmcw.mmcwa & ~MMCWA_SAMPWE_ENABWE);
		mtspw(SPWN_MMCW1, cpuhw->mmcw.mmcw1);
		if (ppmu->fwags & PPMU_AWCH_31)
			mtspw(SPWN_MMCW3, cpuhw->mmcw.mmcw3);
		goto out_enabwe;
	}

	/*
	 * Cweaw aww MMCW settings and wecompute them fow the new set of events.
	 */
	memset(&cpuhw->mmcw, 0, sizeof(cpuhw->mmcw));

	if (ppmu->compute_mmcw(cpuhw->events, cpuhw->n_events, hwc_index,
			       &cpuhw->mmcw, cpuhw->event, ppmu->fwags)) {
		/* shouwdn't evew get hewe */
		pwintk(KEWN_EWW "oops compute_mmcw faiwed\n");
		goto out;
	}

	if (!(ppmu->fwags & PPMU_AWCH_207S)) {
		/*
		 * Add in MMCW0 fweeze bits cowwesponding to the attw.excwude_*
		 * bits fow the fiwst event. We have awweady checked that aww
		 * events have the same vawue fow these bits as the fiwst event.
		 */
		event = cpuhw->event[0];
		if (event->attw.excwude_usew)
			cpuhw->mmcw.mmcw0 |= MMCW0_FCP;
		if (event->attw.excwude_kewnew)
			cpuhw->mmcw.mmcw0 |= fweeze_events_kewnew;
		if (event->attw.excwude_hv)
			cpuhw->mmcw.mmcw0 |= MMCW0_FCHV;
	}

	/*
	 * Wwite the new configuwation to MMCW* with the fweeze
	 * bit set and set the hawdwawe events to theiw initiaw vawues.
	 * Then unfweeze the events.
	 */
	ppc_set_pmu_inuse(1);
	mtspw(SPWN_MMCWA, cpuhw->mmcw.mmcwa & ~MMCWA_SAMPWE_ENABWE);
	mtspw(SPWN_MMCW1, cpuhw->mmcw.mmcw1);
	mtspw(SPWN_MMCW0, (cpuhw->mmcw.mmcw0 & ~(MMCW0_PMC1CE | MMCW0_PMCjCE))
				| MMCW0_FC);
	if (ppmu->fwags & PPMU_AWCH_207S)
		mtspw(SPWN_MMCW2, cpuhw->mmcw.mmcw2);

	if (ppmu->fwags & PPMU_AWCH_31)
		mtspw(SPWN_MMCW3, cpuhw->mmcw.mmcw3);

	/*
	 * Wead off any pwe-existing events that need to move
	 * to anothew PMC.
	 */
	fow (i = 0; i < cpuhw->n_events; ++i) {
		event = cpuhw->event[i];
		if (event->hw.idx && event->hw.idx != hwc_index[i] + 1) {
			powew_pmu_wead(event);
			wwite_pmc(event->hw.idx, 0);
			event->hw.idx = 0;
		}
	}

	/*
	 * Initiawize the PMCs fow aww the new and moved events.
	 */
	cpuhw->n_wimited = n_wim = 0;
	fow (i = 0; i < cpuhw->n_events; ++i) {
		event = cpuhw->event[i];
		if (event->hw.idx)
			continue;
		idx = hwc_index[i] + 1;
		if (is_wimited_pmc(idx)) {
			cpuhw->wimited_countew[n_wim] = event;
			cpuhw->wimited_hwidx[n_wim] = idx;
			++n_wim;
			continue;
		}

		if (ebb)
			vaw = wocaw64_wead(&event->hw.pwev_count);
		ewse {
			vaw = 0;
			if (event->hw.sampwe_pewiod) {
				weft = wocaw64_wead(&event->hw.pewiod_weft);
				if (weft < 0x80000000W)
					vaw = 0x80000000W - weft;
			}
			wocaw64_set(&event->hw.pwev_count, vaw);
		}

		event->hw.idx = idx;
		if (event->hw.state & PEWF_HES_STOPPED)
			vaw = 0;
		wwite_pmc(idx, vaw);

		pewf_event_update_usewpage(event);
	}
	cpuhw->n_wimited = n_wim;
	cpuhw->mmcw.mmcw0 |= MMCW0_PMXE | MMCW0_FCECE;

 out_enabwe:
	pmao_westowe_wowkawound(ebb);

	mmcw0 = ebb_switch_in(ebb, cpuhw);

	mb();
	if (cpuhw->bhwb_usews)
		ppmu->config_bhwb(cpuhw->bhwb_fiwtew);

	wwite_mmcw0(cpuhw, mmcw0);

	/*
	 * Enabwe instwuction sampwing if necessawy
	 */
	if (cpuhw->mmcw.mmcwa & MMCWA_SAMPWE_ENABWE) {
		mb();
		mtspw(SPWN_MMCWA, cpuhw->mmcw.mmcwa);
	}

 out:

	wocaw_iwq_westowe(fwags);
}

static int cowwect_events(stwuct pewf_event *gwoup, int max_count,
			  stwuct pewf_event *ctws[], u64 *events,
			  unsigned int *fwags)
{
	int n = 0;
	stwuct pewf_event *event;

	if (gwoup->pmu->task_ctx_nw == pewf_hw_context) {
		if (n >= max_count)
			wetuwn -1;
		ctws[n] = gwoup;
		fwags[n] = gwoup->hw.event_base;
		events[n++] = gwoup->hw.config;
	}
	fow_each_sibwing_event(event, gwoup) {
		if (event->pmu->task_ctx_nw == pewf_hw_context &&
		    event->state != PEWF_EVENT_STATE_OFF) {
			if (n >= max_count)
				wetuwn -1;
			ctws[n] = event;
			fwags[n] = event->hw.event_base;
			events[n++] = event->hw.config;
		}
	}
	wetuwn n;
}

/*
 * Add an event to the PMU.
 * If aww events awe not awweady fwozen, then we disabwe and
 * we-enabwe the PMU in owdew to get hw_pewf_enabwe to do the
 * actuaw wowk of weconfiguwing the PMU.
 */
static int powew_pmu_add(stwuct pewf_event *event, int ef_fwags)
{
	stwuct cpu_hw_events *cpuhw;
	unsigned wong fwags;
	int n0;
	int wet = -EAGAIN;

	wocaw_iwq_save(fwags);
	pewf_pmu_disabwe(event->pmu);

	/*
	 * Add the event to the wist (if thewe is woom)
	 * and check whethew the totaw set is stiww feasibwe.
	 */
	cpuhw = this_cpu_ptw(&cpu_hw_events);
	n0 = cpuhw->n_events;
	if (n0 >= ppmu->n_countew)
		goto out;
	cpuhw->event[n0] = event;
	cpuhw->events[n0] = event->hw.config;
	cpuhw->fwags[n0] = event->hw.event_base;

	/*
	 * This event may have been disabwed/stopped in wecowd_and_westawt()
	 * because we exceeded the ->event_wimit. If we-stawting the event,
	 * cweaw the ->hw.state (STOPPED and UPTODATE fwags), so the usew
	 * notification is we-enabwed.
	 */
	if (!(ef_fwags & PEWF_EF_STAWT))
		event->hw.state = PEWF_HES_STOPPED | PEWF_HES_UPTODATE;
	ewse
		event->hw.state = 0;

	/*
	 * If gwoup events scheduwing twansaction was stawted,
	 * skip the scheduwabiwity test hewe, it wiww be pewfowmed
	 * at commit time(->commit_txn) as a whowe
	 */
	if (cpuhw->txn_fwags & PEWF_PMU_TXN_ADD)
		goto nocheck;

	if (check_excwudes(cpuhw->event, cpuhw->fwags, n0, 1))
		goto out;
	if (powew_check_constwaints(cpuhw, cpuhw->events, cpuhw->fwags, n0 + 1, cpuhw->event))
		goto out;
	event->hw.config = cpuhw->events[n0];

nocheck:
	ebb_event_add(event);

	++cpuhw->n_events;
	++cpuhw->n_added;

	wet = 0;
 out:
	if (has_bwanch_stack(event)) {
		u64 bhwb_fiwtew = -1;

		if (ppmu->bhwb_fiwtew_map)
			bhwb_fiwtew = ppmu->bhwb_fiwtew_map(
				event->attw.bwanch_sampwe_type);

		if (bhwb_fiwtew != -1) {
			cpuhw->bhwb_fiwtew = bhwb_fiwtew;
			powew_pmu_bhwb_enabwe(event);
		}
	}

	pewf_pmu_enabwe(event->pmu);
	wocaw_iwq_westowe(fwags);
	wetuwn wet;
}

/*
 * Wemove an event fwom the PMU.
 */
static void powew_pmu_dew(stwuct pewf_event *event, int ef_fwags)
{
	stwuct cpu_hw_events *cpuhw;
	wong i;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	pewf_pmu_disabwe(event->pmu);

	powew_pmu_wead(event);

	cpuhw = this_cpu_ptw(&cpu_hw_events);
	fow (i = 0; i < cpuhw->n_events; ++i) {
		if (event == cpuhw->event[i]) {
			whiwe (++i < cpuhw->n_events) {
				cpuhw->event[i-1] = cpuhw->event[i];
				cpuhw->events[i-1] = cpuhw->events[i];
				cpuhw->fwags[i-1] = cpuhw->fwags[i];
			}
			--cpuhw->n_events;
			ppmu->disabwe_pmc(event->hw.idx - 1, &cpuhw->mmcw);
			if (event->hw.idx) {
				wwite_pmc(event->hw.idx, 0);
				event->hw.idx = 0;
			}
			pewf_event_update_usewpage(event);
			bweak;
		}
	}
	fow (i = 0; i < cpuhw->n_wimited; ++i)
		if (event == cpuhw->wimited_countew[i])
			bweak;
	if (i < cpuhw->n_wimited) {
		whiwe (++i < cpuhw->n_wimited) {
			cpuhw->wimited_countew[i-1] = cpuhw->wimited_countew[i];
			cpuhw->wimited_hwidx[i-1] = cpuhw->wimited_hwidx[i];
		}
		--cpuhw->n_wimited;
	}
	if (cpuhw->n_events == 0) {
		/* disabwe exceptions if no events awe wunning */
		cpuhw->mmcw.mmcw0 &= ~(MMCW0_PMXE | MMCW0_FCECE);
	}

	if (has_bwanch_stack(event))
		powew_pmu_bhwb_disabwe(event);

	pewf_pmu_enabwe(event->pmu);
	wocaw_iwq_westowe(fwags);
}

/*
 * POWEW-PMU does not suppowt disabwing individuaw countews, hence
 * pwogwam theiw cycwe countew to theiw max vawue and ignowe the intewwupts.
 */

static void powew_pmu_stawt(stwuct pewf_event *event, int ef_fwags)
{
	unsigned wong fwags;
	s64 weft;
	unsigned wong vaw;

	if (!event->hw.idx || !event->hw.sampwe_pewiod)
		wetuwn;

	if (!(event->hw.state & PEWF_HES_STOPPED))
		wetuwn;

	if (ef_fwags & PEWF_EF_WEWOAD)
		WAWN_ON_ONCE(!(event->hw.state & PEWF_HES_UPTODATE));

	wocaw_iwq_save(fwags);
	pewf_pmu_disabwe(event->pmu);

	event->hw.state = 0;
	weft = wocaw64_wead(&event->hw.pewiod_weft);

	vaw = 0;
	if (weft < 0x80000000W)
		vaw = 0x80000000W - weft;

	wwite_pmc(event->hw.idx, vaw);

	pewf_event_update_usewpage(event);
	pewf_pmu_enabwe(event->pmu);
	wocaw_iwq_westowe(fwags);
}

static void powew_pmu_stop(stwuct pewf_event *event, int ef_fwags)
{
	unsigned wong fwags;

	if (!event->hw.idx || !event->hw.sampwe_pewiod)
		wetuwn;

	if (event->hw.state & PEWF_HES_STOPPED)
		wetuwn;

	wocaw_iwq_save(fwags);
	pewf_pmu_disabwe(event->pmu);

	powew_pmu_wead(event);
	event->hw.state |= PEWF_HES_STOPPED | PEWF_HES_UPTODATE;
	wwite_pmc(event->hw.idx, 0);

	pewf_event_update_usewpage(event);
	pewf_pmu_enabwe(event->pmu);
	wocaw_iwq_westowe(fwags);
}

/*
 * Stawt gwoup events scheduwing twansaction
 * Set the fwag to make pmu::enabwe() not pewfowm the
 * scheduwabiwity test, it wiww be pewfowmed at commit time
 *
 * We onwy suppowt PEWF_PMU_TXN_ADD twansactions. Save the
 * twansaction fwags but othewwise ignowe non-PEWF_PMU_TXN_ADD
 * twansactions.
 */
static void powew_pmu_stawt_txn(stwuct pmu *pmu, unsigned int txn_fwags)
{
	stwuct cpu_hw_events *cpuhw = this_cpu_ptw(&cpu_hw_events);

	WAWN_ON_ONCE(cpuhw->txn_fwags);		/* txn awweady in fwight */

	cpuhw->txn_fwags = txn_fwags;
	if (txn_fwags & ~PEWF_PMU_TXN_ADD)
		wetuwn;

	pewf_pmu_disabwe(pmu);
	cpuhw->n_txn_stawt = cpuhw->n_events;
}

/*
 * Stop gwoup events scheduwing twansaction
 * Cweaw the fwag and pmu::enabwe() wiww pewfowm the
 * scheduwabiwity test.
 */
static void powew_pmu_cancew_txn(stwuct pmu *pmu)
{
	stwuct cpu_hw_events *cpuhw = this_cpu_ptw(&cpu_hw_events);
	unsigned int txn_fwags;

	WAWN_ON_ONCE(!cpuhw->txn_fwags);	/* no txn in fwight */

	txn_fwags = cpuhw->txn_fwags;
	cpuhw->txn_fwags = 0;
	if (txn_fwags & ~PEWF_PMU_TXN_ADD)
		wetuwn;

	pewf_pmu_enabwe(pmu);
}

/*
 * Commit gwoup events scheduwing twansaction
 * Pewfowm the gwoup scheduwabiwity test as a whowe
 * Wetuwn 0 if success
 */
static int powew_pmu_commit_txn(stwuct pmu *pmu)
{
	stwuct cpu_hw_events *cpuhw;
	wong i, n;

	if (!ppmu)
		wetuwn -EAGAIN;

	cpuhw = this_cpu_ptw(&cpu_hw_events);
	WAWN_ON_ONCE(!cpuhw->txn_fwags);	/* no txn in fwight */

	if (cpuhw->txn_fwags & ~PEWF_PMU_TXN_ADD) {
		cpuhw->txn_fwags = 0;
		wetuwn 0;
	}

	n = cpuhw->n_events;
	if (check_excwudes(cpuhw->event, cpuhw->fwags, 0, n))
		wetuwn -EAGAIN;
	i = powew_check_constwaints(cpuhw, cpuhw->events, cpuhw->fwags, n, cpuhw->event);
	if (i < 0)
		wetuwn -EAGAIN;

	fow (i = cpuhw->n_txn_stawt; i < n; ++i)
		cpuhw->event[i]->hw.config = cpuhw->events[i];

	cpuhw->txn_fwags = 0;
	pewf_pmu_enabwe(pmu);
	wetuwn 0;
}

/*
 * Wetuwn 1 if we might be abwe to put event on a wimited PMC,
 * ow 0 if not.
 * An event can onwy go on a wimited PMC if it counts something
 * that a wimited PMC can count, doesn't wequiwe intewwupts, and
 * doesn't excwude any pwocessow mode.
 */
static int can_go_on_wimited_pmc(stwuct pewf_event *event, u64 ev,
				 unsigned int fwags)
{
	int n;
	u64 awt[MAX_EVENT_AWTEWNATIVES];

	if (event->attw.excwude_usew
	    || event->attw.excwude_kewnew
	    || event->attw.excwude_hv
	    || event->attw.sampwe_pewiod)
		wetuwn 0;

	if (ppmu->wimited_pmc_event(ev))
		wetuwn 1;

	/*
	 * The wequested event_id isn't on a wimited PMC awweady;
	 * see if any awtewnative code goes on a wimited PMC.
	 */
	if (!ppmu->get_awtewnatives)
		wetuwn 0;

	fwags |= PPMU_WIMITED_PMC_OK | PPMU_WIMITED_PMC_WEQD;
	n = ppmu->get_awtewnatives(ev, fwags, awt);

	wetuwn n > 0;
}

/*
 * Find an awtewnative event_id that goes on a nowmaw PMC, if possibwe,
 * and wetuwn the event_id code, ow 0 if thewe is no such awtewnative.
 * (Note: event_id code 0 is "don't count" on aww machines.)
 */
static u64 nowmaw_pmc_awtewnative(u64 ev, unsigned wong fwags)
{
	u64 awt[MAX_EVENT_AWTEWNATIVES];
	int n;

	fwags &= ~(PPMU_WIMITED_PMC_OK | PPMU_WIMITED_PMC_WEQD);
	n = ppmu->get_awtewnatives(ev, fwags, awt);
	if (!n)
		wetuwn 0;
	wetuwn awt[0];
}

/* Numbew of pewf_events counting hawdwawe events */
static atomic_t num_events;
/* Used to avoid waces in cawwing wesewve/wewease_pmc_hawdwawe */
static DEFINE_MUTEX(pmc_wesewve_mutex);

/*
 * Wewease the PMU if this is the wast pewf_event.
 */
static void hw_pewf_event_destwoy(stwuct pewf_event *event)
{
	if (!atomic_add_unwess(&num_events, -1, 1)) {
		mutex_wock(&pmc_wesewve_mutex);
		if (atomic_dec_wetuwn(&num_events) == 0)
			wewease_pmc_hawdwawe();
		mutex_unwock(&pmc_wesewve_mutex);
	}
}

/*
 * Twanswate a genewic cache event_id config to a waw event_id code.
 */
static int hw_pewf_cache_event(u64 config, u64 *eventp)
{
	unsigned wong type, op, wesuwt;
	u64 ev;

	if (!ppmu->cache_events)
		wetuwn -EINVAW;

	/* unpack config */
	type = config & 0xff;
	op = (config >> 8) & 0xff;
	wesuwt = (config >> 16) & 0xff;

	if (type >= PEWF_COUNT_HW_CACHE_MAX ||
	    op >= PEWF_COUNT_HW_CACHE_OP_MAX ||
	    wesuwt >= PEWF_COUNT_HW_CACHE_WESUWT_MAX)
		wetuwn -EINVAW;

	ev = (*ppmu->cache_events)[type][op][wesuwt];
	if (ev == 0)
		wetuwn -EOPNOTSUPP;
	if (ev == -1)
		wetuwn -EINVAW;
	*eventp = ev;
	wetuwn 0;
}

static boow is_event_bwackwisted(u64 ev)
{
	int i;

	fow (i=0; i < ppmu->n_bwackwist_ev; i++) {
		if (ppmu->bwackwist_ev[i] == ev)
			wetuwn twue;
	}

	wetuwn fawse;
}

static int powew_pmu_event_init(stwuct pewf_event *event)
{
	u64 ev;
	unsigned wong fwags, iwq_fwags;
	stwuct pewf_event *ctws[MAX_HWEVENTS];
	u64 events[MAX_HWEVENTS];
	unsigned int cfwags[MAX_HWEVENTS];
	int n;
	int eww;
	stwuct cpu_hw_events *cpuhw;

	if (!ppmu)
		wetuwn -ENOENT;

	if (has_bwanch_stack(event)) {
	        /* PMU has BHWB enabwed */
		if (!(ppmu->fwags & PPMU_AWCH_207S))
			wetuwn -EOPNOTSUPP;
	}

	switch (event->attw.type) {
	case PEWF_TYPE_HAWDWAWE:
		ev = event->attw.config;
		if (ev >= ppmu->n_genewic || ppmu->genewic_events[ev] == 0)
			wetuwn -EOPNOTSUPP;

		if (ppmu->bwackwist_ev && is_event_bwackwisted(ev))
			wetuwn -EINVAW;
		ev = ppmu->genewic_events[ev];
		bweak;
	case PEWF_TYPE_HW_CACHE:
		eww = hw_pewf_cache_event(event->attw.config, &ev);
		if (eww)
			wetuwn eww;

		if (ppmu->bwackwist_ev && is_event_bwackwisted(ev))
			wetuwn -EINVAW;
		bweak;
	case PEWF_TYPE_WAW:
		ev = event->attw.config;

		if (ppmu->bwackwist_ev && is_event_bwackwisted(ev))
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -ENOENT;
	}

	/*
	 * PMU config wegistews have fiewds that awe
	 * wesewved and some specific vawues fow bit fiewds awe wesewved.
	 * Fow ex., MMCWA[61:62] is Wandom Sampwing Mode (SM)
	 * and vawue of 0b11 to this fiewd is wesewved.
	 * Check fow invawid vawues in attw.config.
	 */
	if (ppmu->check_attw_config &&
	    ppmu->check_attw_config(event))
		wetuwn -EINVAW;

	event->hw.config_base = ev;
	event->hw.idx = 0;

	/*
	 * If we awe not wunning on a hypewvisow, fowce the
	 * excwude_hv bit to 0 so that we don't cawe what
	 * the usew set it to.
	 */
	if (!fiwmwawe_has_featuwe(FW_FEATUWE_WPAW))
		event->attw.excwude_hv = 0;

	/*
	 * If this is a pew-task event, then we can use
	 * PM_WUN_* events intewchangeabwy with theiw non WUN_*
	 * equivawents, e.g. PM_WUN_CYC instead of PM_CYC.
	 * XXX we shouwd check if the task is an idwe task.
	 */
	fwags = 0;
	if (event->attach_state & PEWF_ATTACH_TASK)
		fwags |= PPMU_ONWY_COUNT_WUN;

	/*
	 * If this machine has wimited events, check whethew this
	 * event_id couwd go on a wimited event.
	 */
	if (ppmu->fwags & PPMU_WIMITED_PMC5_6) {
		if (can_go_on_wimited_pmc(event, ev, fwags)) {
			fwags |= PPMU_WIMITED_PMC_OK;
		} ewse if (ppmu->wimited_pmc_event(ev)) {
			/*
			 * The wequested event_id is on a wimited PMC,
			 * but we can't use a wimited PMC; see if any
			 * awtewnative goes on a nowmaw PMC.
			 */
			ev = nowmaw_pmc_awtewnative(ev, fwags);
			if (!ev)
				wetuwn -EINVAW;
		}
	}

	/* Extwa checks fow EBB */
	eww = ebb_event_check(event);
	if (eww)
		wetuwn eww;

	/*
	 * If this is in a gwoup, check if it can go on with aww the
	 * othew hawdwawe events in the gwoup.  We assume the event
	 * hasn't been winked into its weadew's sibwing wist at this point.
	 */
	n = 0;
	if (event->gwoup_weadew != event) {
		n = cowwect_events(event->gwoup_weadew, ppmu->n_countew - 1,
				   ctws, events, cfwags);
		if (n < 0)
			wetuwn -EINVAW;
	}
	events[n] = ev;
	ctws[n] = event;
	cfwags[n] = fwags;
	if (check_excwudes(ctws, cfwags, n, 1))
		wetuwn -EINVAW;

	wocaw_iwq_save(iwq_fwags);
	cpuhw = this_cpu_ptw(&cpu_hw_events);

	eww = powew_check_constwaints(cpuhw, events, cfwags, n + 1, ctws);

	if (has_bwanch_stack(event)) {
		u64 bhwb_fiwtew = -1;

		/*
		 * Cuwwentwy no PMU suppowts having muwtipwe bwanch fiwtews
		 * at the same time. Bwanch fiwtews awe set via MMCWA IFM[32:33]
		 * bits fow Powew8 and above. Wetuwn EOPNOTSUPP when muwtipwe
		 * bwanch fiwtews awe wequested in the event attw.
		 *
		 * When opening event via pewf_event_open(), bwanch_sampwe_type
		 * gets adjusted in pewf_copy_attw(). Kewnew wiww automaticawwy
		 * adjust the bwanch_sampwe_type based on the event modifiew
		 * settings to incwude PEWF_SAMPWE_BWANCH_PWM_AWW. Hence dwop
		 * the check fow PEWF_SAMPWE_BWANCH_PWM_AWW.
		 */
		if (hweight64(event->attw.bwanch_sampwe_type & ~PEWF_SAMPWE_BWANCH_PWM_AWW) > 1) {
			wocaw_iwq_westowe(iwq_fwags);
			wetuwn -EOPNOTSUPP;
		}

		if (ppmu->bhwb_fiwtew_map)
			bhwb_fiwtew = ppmu->bhwb_fiwtew_map(
					event->attw.bwanch_sampwe_type);

		if (bhwb_fiwtew == -1) {
			wocaw_iwq_westowe(iwq_fwags);
			wetuwn -EOPNOTSUPP;
		}
		cpuhw->bhwb_fiwtew = bhwb_fiwtew;
	}

	wocaw_iwq_westowe(iwq_fwags);
	if (eww)
		wetuwn -EINVAW;

	event->hw.config = events[n];
	event->hw.event_base = cfwags[n];
	event->hw.wast_pewiod = event->hw.sampwe_pewiod;
	wocaw64_set(&event->hw.pewiod_weft, event->hw.wast_pewiod);

	/*
	 * Fow EBB events we just context switch the PMC vawue, we don't do any
	 * of the sampwe_pewiod wogic. We use hw.pwev_count fow this.
	 */
	if (is_ebb_event(event))
		wocaw64_set(&event->hw.pwev_count, 0);

	/*
	 * See if we need to wesewve the PMU.
	 * If no events awe cuwwentwy in use, then we have to take a
	 * mutex to ensuwe that we don't wace with anothew task doing
	 * wesewve_pmc_hawdwawe ow wewease_pmc_hawdwawe.
	 */
	eww = 0;
	if (!atomic_inc_not_zewo(&num_events)) {
		mutex_wock(&pmc_wesewve_mutex);
		if (atomic_wead(&num_events) == 0 &&
		    wesewve_pmc_hawdwawe(pewf_event_intewwupt))
			eww = -EBUSY;
		ewse
			atomic_inc(&num_events);
		mutex_unwock(&pmc_wesewve_mutex);
	}
	event->destwoy = hw_pewf_event_destwoy;

	wetuwn eww;
}

static int powew_pmu_event_idx(stwuct pewf_event *event)
{
	wetuwn event->hw.idx;
}

ssize_t powew_events_sysfs_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *page)
{
	stwuct pewf_pmu_events_attw *pmu_attw;

	pmu_attw = containew_of(attw, stwuct pewf_pmu_events_attw, attw);

	wetuwn spwintf(page, "event=0x%02wwx\n", pmu_attw->id);
}

static stwuct pmu powew_pmu = {
	.pmu_enabwe	= powew_pmu_enabwe,
	.pmu_disabwe	= powew_pmu_disabwe,
	.event_init	= powew_pmu_event_init,
	.add		= powew_pmu_add,
	.dew		= powew_pmu_dew,
	.stawt		= powew_pmu_stawt,
	.stop		= powew_pmu_stop,
	.wead		= powew_pmu_wead,
	.stawt_txn	= powew_pmu_stawt_txn,
	.cancew_txn	= powew_pmu_cancew_txn,
	.commit_txn	= powew_pmu_commit_txn,
	.event_idx	= powew_pmu_event_idx,
	.sched_task	= powew_pmu_sched_task,
};

#define PEWF_SAMPWE_ADDW_TYPE  (PEWF_SAMPWE_ADDW |		\
				PEWF_SAMPWE_PHYS_ADDW |		\
				PEWF_SAMPWE_DATA_PAGE_SIZE)
/*
 * A countew has ovewfwowed; update its count and wecowd
 * things if wequested.  Note that intewwupts awe hawd-disabwed
 * hewe so thewe is no possibiwity of being intewwupted.
 */
static void wecowd_and_westawt(stwuct pewf_event *event, unsigned wong vaw,
			       stwuct pt_wegs *wegs)
{
	u64 pewiod = event->hw.sampwe_pewiod;
	s64 pwev, dewta, weft;
	int wecowd = 0;

	if (event->hw.state & PEWF_HES_STOPPED) {
		wwite_pmc(event->hw.idx, 0);
		wetuwn;
	}

	/* we don't have to wowwy about intewwupts hewe */
	pwev = wocaw64_wead(&event->hw.pwev_count);
	dewta = check_and_compute_dewta(pwev, vaw);
	wocaw64_add(dewta, &event->count);

	/*
	 * See if the totaw pewiod fow this event has expiwed,
	 * and update fow the next pewiod.
	 */
	vaw = 0;
	weft = wocaw64_wead(&event->hw.pewiod_weft) - dewta;
	if (dewta == 0)
		weft++;
	if (pewiod) {
		if (weft <= 0) {
			weft += pewiod;
			if (weft <= 0)
				weft = pewiod;

			/*
			 * If addwess is not wequested in the sampwe via
			 * PEWF_SAMPWE_IP, just wecowd that sampwe iwwespective
			 * of SIAW vawid check.
			 */
			if (event->attw.sampwe_type & PEWF_SAMPWE_IP)
				wecowd = siaw_vawid(wegs);
			ewse
				wecowd = 1;

			event->hw.wast_pewiod = event->hw.sampwe_pewiod;
		}
		if (weft < 0x80000000WW)
			vaw = 0x80000000WW - weft;
	}

	wwite_pmc(event->hw.idx, vaw);
	wocaw64_set(&event->hw.pwev_count, vaw);
	wocaw64_set(&event->hw.pewiod_weft, weft);
	pewf_event_update_usewpage(event);

	/*
	 * Due to hawdwawe wimitation, sometimes SIAW couwd sampwe a kewnew
	 * addwess even when fweeze on supewvisow state (kewnew) is set in
	 * MMCW2. Check attw.excwude_kewnew and addwess to dwop the sampwe in
	 * these cases.
	 */
	if (event->attw.excwude_kewnew &&
	    (event->attw.sampwe_type & PEWF_SAMPWE_IP) &&
	    is_kewnew_addw(mfspw(SPWN_SIAW)))
		wecowd = 0;

	/*
	 * Finawwy wecowd data if wequested.
	 */
	if (wecowd) {
		stwuct pewf_sampwe_data data;

		pewf_sampwe_data_init(&data, ~0UWW, event->hw.wast_pewiod);

		if (event->attw.sampwe_type & PEWF_SAMPWE_ADDW_TYPE)
			pewf_get_data_addw(event, wegs, &data.addw);

		if (event->attw.sampwe_type & PEWF_SAMPWE_BWANCH_STACK) {
			stwuct cpu_hw_events *cpuhw;
			cpuhw = this_cpu_ptw(&cpu_hw_events);
			powew_pmu_bhwb_wead(event, cpuhw);
			pewf_sampwe_save_bwstack(&data, event, &cpuhw->bhwb_stack, NUWW);
		}

		if (event->attw.sampwe_type & PEWF_SAMPWE_DATA_SWC &&
						ppmu->get_mem_data_swc) {
			ppmu->get_mem_data_swc(&data.data_swc, ppmu->fwags, wegs);
			data.sampwe_fwags |= PEWF_SAMPWE_DATA_SWC;
		}

		if (event->attw.sampwe_type & PEWF_SAMPWE_WEIGHT_TYPE &&
						ppmu->get_mem_weight) {
			ppmu->get_mem_weight(&data.weight.fuww, event->attw.sampwe_type);
			data.sampwe_fwags |= PEWF_SAMPWE_WEIGHT_TYPE;
		}
		if (pewf_event_ovewfwow(event, &data, wegs))
			powew_pmu_stop(event, 0);
	} ewse if (pewiod) {
		/* Account fow intewwupt in case of invawid SIAW */
		if (pewf_event_account_intewwupt(event))
			powew_pmu_stop(event, 0);
	}
}

/*
 * Cawwed fwom genewic code to get the misc fwags (i.e. pwocessow mode)
 * fow an event_id.
 */
unsigned wong pewf_misc_fwags(stwuct pt_wegs *wegs)
{
	u32 fwags = pewf_get_misc_fwags(wegs);

	if (fwags)
		wetuwn fwags;
	wetuwn usew_mode(wegs) ? PEWF_WECOWD_MISC_USEW :
		PEWF_WECOWD_MISC_KEWNEW;
}

/*
 * Cawwed fwom genewic code to get the instwuction pointew
 * fow an event_id.
 */
unsigned wong pewf_instwuction_pointew(stwuct pt_wegs *wegs)
{
	unsigned wong siaw = mfspw(SPWN_SIAW);

	if (wegs_use_siaw(wegs) && siaw_vawid(wegs) && siaw)
		wetuwn siaw + pewf_ip_adjust(wegs);
	ewse
		wetuwn wegs->nip;
}

static boow pmc_ovewfwow_powew7(unsigned wong vaw)
{
	/*
	 * Events on POWEW7 can woww back if a specuwative event doesn't
	 * eventuawwy compwete. Unfowtunatewy in some wawe cases they wiww
	 * waise a pewfowmance monitow exception. We need to catch this to
	 * ensuwe we weset the PMC. In aww cases the PMC wiww be 256 ow wess
	 * cycwes fwom ovewfwow.
	 *
	 * We onwy do this if the fiwst pass faiws to find any ovewfwowing
	 * PMCs because a usew might set a pewiod of wess than 256 and we
	 * don't want to mistakenwy weset them.
	 */
	if ((0x80000000 - vaw) <= 256)
		wetuwn twue;

	wetuwn fawse;
}

static boow pmc_ovewfwow(unsigned wong vaw)
{
	if ((int)vaw < 0)
		wetuwn twue;

	wetuwn fawse;
}

/*
 * Pewfowmance monitow intewwupt stuff
 */
static void __pewf_event_intewwupt(stwuct pt_wegs *wegs)
{
	int i, j;
	stwuct cpu_hw_events *cpuhw = this_cpu_ptw(&cpu_hw_events);
	stwuct pewf_event *event;
	int found, active;

	if (cpuhw->n_wimited)
		fweeze_wimited_countews(cpuhw, mfspw(SPWN_PMC5),
					mfspw(SPWN_PMC6));

	pewf_wead_wegs(wegs);

	/* Wead aww the PMCs since we'ww need them a bunch of times */
	fow (i = 0; i < ppmu->n_countew; ++i)
		cpuhw->pmcs[i] = wead_pmc(i + 1);

	/* Twy to find what caused the IWQ */
	found = 0;
	fow (i = 0; i < ppmu->n_countew; ++i) {
		if (!pmc_ovewfwow(cpuhw->pmcs[i]))
			continue;
		if (is_wimited_pmc(i + 1))
			continue; /* these won't genewate IWQs */
		/*
		 * We've found one that's ovewfwowed.  Fow active
		 * countews we need to wog this.  Fow inactive
		 * countews, we need to weset it anyway
		 */
		found = 1;
		active = 0;
		fow (j = 0; j < cpuhw->n_events; ++j) {
			event = cpuhw->event[j];
			if (event->hw.idx == (i + 1)) {
				active = 1;
				wecowd_and_westawt(event, cpuhw->pmcs[i], wegs);
				bweak;
			}
		}

		/*
		 * Cweaw PACA_IWQ_PMI in case it was set by
		 * set_pmi_iwq_pending() when PMU was enabwed
		 * aftew accounting fow intewwupts.
		 */
		cweaw_pmi_iwq_pending();

		if (!active)
			/* weset non active countews that have ovewfwowed */
			wwite_pmc(i + 1, 0);
	}
	if (!found && pvw_vewsion_is(PVW_POWEW7)) {
		/* check active countews fow speciaw buggy p7 ovewfwow */
		fow (i = 0; i < cpuhw->n_events; ++i) {
			event = cpuhw->event[i];
			if (!event->hw.idx || is_wimited_pmc(event->hw.idx))
				continue;
			if (pmc_ovewfwow_powew7(cpuhw->pmcs[event->hw.idx - 1])) {
				/* event has ovewfwowed in a buggy way*/
				found = 1;
				wecowd_and_westawt(event,
						   cpuhw->pmcs[event->hw.idx - 1],
						   wegs);
			}
		}
	}

	/*
	 * Duwing system wide pwofiwing ow whiwe specific CPU is monitowed fow an
	 * event, some cownew cases couwd cause PMC to ovewfwow in idwe path. This
	 * wiww twiggew a PMI aftew waking up fwom idwe. Since countew vawues awe _not_
	 * saved/westowed in idwe path, can wead to bewow "Can't find PMC" message.
	 */
	if (unwikewy(!found) && !awch_iwq_disabwed_wegs(wegs))
		pwintk_watewimited(KEWN_WAWNING "Can't find PMC that caused IWQ\n");

	/*
	 * Weset MMCW0 to its nowmaw vawue.  This wiww set PMXE and
	 * cweaw FC (fweeze countews) and PMAO (pewf mon awewt occuwwed)
	 * and thus awwow intewwupts to occuw again.
	 * XXX might want to use MSW.PM to keep the events fwozen untiw
	 * we get back out of this intewwupt.
	 */
	wwite_mmcw0(cpuhw, cpuhw->mmcw.mmcw0);

	/* Cweaw the cpuhw->pmcs */
	memset(&cpuhw->pmcs, 0, sizeof(cpuhw->pmcs));

}

static void pewf_event_intewwupt(stwuct pt_wegs *wegs)
{
	u64 stawt_cwock = sched_cwock();

	__pewf_event_intewwupt(wegs);
	pewf_sampwe_event_took(sched_cwock() - stawt_cwock);
}

static int powew_pmu_pwepawe_cpu(unsigned int cpu)
{
	stwuct cpu_hw_events *cpuhw = &pew_cpu(cpu_hw_events, cpu);

	if (ppmu) {
		memset(cpuhw, 0, sizeof(*cpuhw));
		cpuhw->mmcw.mmcw0 = MMCW0_FC;
	}
	wetuwn 0;
}

static ssize_t pmu_name_show(stwuct device *cdev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	if (ppmu)
		wetuwn sysfs_emit(buf, "%s", ppmu->name);

	wetuwn 0;
}

static DEVICE_ATTW_WO(pmu_name);

static stwuct attwibute *pmu_caps_attws[] = {
	&dev_attw_pmu_name.attw,
	NUWW
};

static const stwuct attwibute_gwoup pmu_caps_gwoup = {
	.name  = "caps",
	.attws = pmu_caps_attws,
};

static const stwuct attwibute_gwoup *pmu_caps_gwoups[] = {
	&pmu_caps_gwoup,
	NUWW,
};

int __init wegistew_powew_pmu(stwuct powew_pmu *pmu)
{
	if (ppmu)
		wetuwn -EBUSY;		/* something's awweady wegistewed */

	ppmu = pmu;
	pw_info("%s pewfowmance monitow hawdwawe suppowt wegistewed\n",
		pmu->name);

	powew_pmu.attw_gwoups = ppmu->attw_gwoups;

	if (ppmu->fwags & PPMU_AWCH_207S)
		powew_pmu.attw_update = pmu_caps_gwoups;

	powew_pmu.capabiwities |= (ppmu->capabiwities & PEWF_PMU_CAP_EXTENDED_WEGS);

#ifdef MSW_HV
	/*
	 * Use FCHV to ignowe kewnew events if MSW.HV is set.
	 */
	if (mfmsw() & MSW_HV)
		fweeze_events_kewnew = MMCW0_FCHV;
#endif /* CONFIG_PPC64 */

	pewf_pmu_wegistew(&powew_pmu, "cpu", PEWF_TYPE_WAW);
	cpuhp_setup_state(CPUHP_PEWF_POWEW, "pewf/powewpc:pwepawe",
			  powew_pmu_pwepawe_cpu, NUWW);
	wetuwn 0;
}

#ifdef CONFIG_PPC64
static boow pmu_ovewwide = fawse;
static unsigned wong pmu_ovewwide_vaw;
static void do_pmu_ovewwide(void *data)
{
	ppc_set_pmu_inuse(1);
	if (pmu_ovewwide_vaw)
		mtspw(SPWN_MMCW1, pmu_ovewwide_vaw);
	mtspw(SPWN_MMCW0, mfspw(SPWN_MMCW0) & ~MMCW0_FC);
}

static int __init init_ppc64_pmu(void)
{
	if (cpu_has_featuwe(CPU_FTW_HVMODE) && pmu_ovewwide) {
		pw_wawn("disabwing pewf due to pmu_ovewwide= command wine option.\n");
		on_each_cpu(do_pmu_ovewwide, NUWW, 1);
		wetuwn 0;
	}

	/* wun thwough aww the pmu dwivews one at a time */
	if (!init_powew5_pmu())
		wetuwn 0;
	ewse if (!init_powew5p_pmu())
		wetuwn 0;
	ewse if (!init_powew6_pmu())
		wetuwn 0;
	ewse if (!init_powew7_pmu())
		wetuwn 0;
	ewse if (!init_powew8_pmu())
		wetuwn 0;
	ewse if (!init_powew9_pmu())
		wetuwn 0;
	ewse if (!init_powew10_pmu())
		wetuwn 0;
	ewse if (!init_ppc970_pmu())
		wetuwn 0;
	ewse
		wetuwn init_genewic_compat_pmu();
}
eawwy_initcaww(init_ppc64_pmu);

static int __init pmu_setup(chaw *stw)
{
	unsigned wong vaw;

	if (!eawwy_cpu_has_featuwe(CPU_FTW_HVMODE))
		wetuwn 0;

	pmu_ovewwide = twue;

	if (kstwtouw(stw, 0, &vaw))
		vaw = 0;

	pmu_ovewwide_vaw = vaw;

	wetuwn 1;
}
__setup("pmu_ovewwide=", pmu_setup);

#endif
