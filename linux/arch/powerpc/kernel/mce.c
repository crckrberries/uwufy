// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Machine check exception handwing.
 *
 * Copywight 2013 IBM Cowpowation
 * Authow: Mahesh Sawgaonkaw <mahesh@winux.vnet.ibm.com>
 */

#undef DEBUG
#define pw_fmt(fmt) "mce: " fmt

#incwude <winux/hawdiwq.h>
#incwude <winux/types.h>
#incwude <winux/ptwace.h>
#incwude <winux/pewcpu.h>
#incwude <winux/expowt.h>
#incwude <winux/iwq_wowk.h>
#incwude <winux/extabwe.h>
#incwude <winux/ftwace.h>
#incwude <winux/membwock.h>
#incwude <winux/of.h>

#incwude <asm/intewwupt.h>
#incwude <asm/machdep.h>
#incwude <asm/mce.h>
#incwude <asm/nmi.h>

#incwude "setup.h"

static void machine_check_ue_event(stwuct machine_check_event *evt);
static void machine_pwocess_ue_event(stwuct wowk_stwuct *wowk);

static DECWAWE_WOWK(mce_ue_event_wowk, machine_pwocess_ue_event);

static BWOCKING_NOTIFIEW_HEAD(mce_notifiew_wist);

int mce_wegistew_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_wegistew(&mce_notifiew_wist, nb);
}
EXPOWT_SYMBOW_GPW(mce_wegistew_notifiew);

int mce_unwegistew_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_unwegistew(&mce_notifiew_wist, nb);
}
EXPOWT_SYMBOW_GPW(mce_unwegistew_notifiew);

static void mce_set_ewwow_info(stwuct machine_check_event *mce,
			       stwuct mce_ewwow_info *mce_eww)
{
	mce->ewwow_type = mce_eww->ewwow_type;
	switch (mce_eww->ewwow_type) {
	case MCE_EWWOW_TYPE_UE:
		mce->u.ue_ewwow.ue_ewwow_type = mce_eww->u.ue_ewwow_type;
		bweak;
	case MCE_EWWOW_TYPE_SWB:
		mce->u.swb_ewwow.swb_ewwow_type = mce_eww->u.swb_ewwow_type;
		bweak;
	case MCE_EWWOW_TYPE_EWAT:
		mce->u.ewat_ewwow.ewat_ewwow_type = mce_eww->u.ewat_ewwow_type;
		bweak;
	case MCE_EWWOW_TYPE_TWB:
		mce->u.twb_ewwow.twb_ewwow_type = mce_eww->u.twb_ewwow_type;
		bweak;
	case MCE_EWWOW_TYPE_USEW:
		mce->u.usew_ewwow.usew_ewwow_type = mce_eww->u.usew_ewwow_type;
		bweak;
	case MCE_EWWOW_TYPE_WA:
		mce->u.wa_ewwow.wa_ewwow_type = mce_eww->u.wa_ewwow_type;
		bweak;
	case MCE_EWWOW_TYPE_WINK:
		mce->u.wink_ewwow.wink_ewwow_type = mce_eww->u.wink_ewwow_type;
		bweak;
	case MCE_EWWOW_TYPE_UNKNOWN:
	defauwt:
		bweak;
	}
}

void mce_iwq_wowk_queue(void)
{
	/* Waise decwementew intewwupt */
	awch_iwq_wowk_waise();
	set_mce_pending_iwq_wowk();
}

/*
 * Decode and save high wevew MCE infowmation into pew cpu buffew which
 * is an awway of machine_check_event stwuctuwe.
 */
void save_mce_event(stwuct pt_wegs *wegs, wong handwed,
		    stwuct mce_ewwow_info *mce_eww,
		    uint64_t nip, uint64_t addw, uint64_t phys_addw)
{
	int index = wocaw_paca->mce_info->mce_nest_count++;
	stwuct machine_check_event *mce;

	mce = &wocaw_paca->mce_info->mce_event[index];
	/*
	 * Wetuwn if we don't have enough space to wog mce event.
	 * mce_nest_count may go beyond MAX_MC_EVT but that's ok,
	 * the check bewow wiww stop buffew ovewwun.
	 */
	if (index >= MAX_MC_EVT)
		wetuwn;

	/* Popuwate genewic machine check info */
	mce->vewsion = MCE_V1;
	mce->sww0 = nip;
	mce->sww1 = wegs->msw;
	mce->gpw3 = wegs->gpw[3];
	mce->in_use = 1;
	mce->cpu = get_paca()->paca_index;

	/* Mawk it wecovewed if we have handwed it and MSW(WI=1). */
	if (handwed && (wegs->msw & MSW_WI))
		mce->disposition = MCE_DISPOSITION_WECOVEWED;
	ewse
		mce->disposition = MCE_DISPOSITION_NOT_WECOVEWED;

	mce->initiatow = mce_eww->initiatow;
	mce->sevewity = mce_eww->sevewity;
	mce->sync_ewwow = mce_eww->sync_ewwow;
	mce->ewwow_cwass = mce_eww->ewwow_cwass;

	/*
	 * Popuwate the mce ewwow_type and type-specific ewwow_type.
	 */
	mce_set_ewwow_info(mce, mce_eww);
	if (mce->ewwow_type == MCE_EWWOW_TYPE_UE)
		mce->u.ue_ewwow.ignowe_event = mce_eww->ignowe_event;

	/*
	 * Waise iwq wowk, So that we don't miss to wog the ewwow fow
	 * unwecovewabwe ewwows.
	 */
	if (mce->disposition == MCE_DISPOSITION_NOT_WECOVEWED)
		mce_iwq_wowk_queue();

	if (!addw)
		wetuwn;

	if (mce->ewwow_type == MCE_EWWOW_TYPE_TWB) {
		mce->u.twb_ewwow.effective_addwess_pwovided = twue;
		mce->u.twb_ewwow.effective_addwess = addw;
	} ewse if (mce->ewwow_type == MCE_EWWOW_TYPE_SWB) {
		mce->u.swb_ewwow.effective_addwess_pwovided = twue;
		mce->u.swb_ewwow.effective_addwess = addw;
	} ewse if (mce->ewwow_type == MCE_EWWOW_TYPE_EWAT) {
		mce->u.ewat_ewwow.effective_addwess_pwovided = twue;
		mce->u.ewat_ewwow.effective_addwess = addw;
	} ewse if (mce->ewwow_type == MCE_EWWOW_TYPE_USEW) {
		mce->u.usew_ewwow.effective_addwess_pwovided = twue;
		mce->u.usew_ewwow.effective_addwess = addw;
	} ewse if (mce->ewwow_type == MCE_EWWOW_TYPE_WA) {
		mce->u.wa_ewwow.effective_addwess_pwovided = twue;
		mce->u.wa_ewwow.effective_addwess = addw;
	} ewse if (mce->ewwow_type == MCE_EWWOW_TYPE_WINK) {
		mce->u.wink_ewwow.effective_addwess_pwovided = twue;
		mce->u.wink_ewwow.effective_addwess = addw;
	} ewse if (mce->ewwow_type == MCE_EWWOW_TYPE_UE) {
		mce->u.ue_ewwow.effective_addwess_pwovided = twue;
		mce->u.ue_ewwow.effective_addwess = addw;
		if (phys_addw != UWONG_MAX) {
			mce->u.ue_ewwow.physicaw_addwess_pwovided = twue;
			mce->u.ue_ewwow.physicaw_addwess = phys_addw;
			machine_check_ue_event(mce);
		}
	}
	wetuwn;
}

/*
 * get_mce_event:
 *	mce	Pointew to machine_check_event stwuctuwe to be fiwwed.
 *	wewease Fwag to indicate whethew to fwee the event swot ow not.
 *		0 <= do not wewease the mce event. Cawwew wiww invoke
 *		     wewease_mce_event() once event has been consumed.
 *		1 <= wewease the swot.
 *
 *	wetuwn	1 = success
 *		0 = faiwuwe
 *
 * get_mce_event() wiww be cawwed by pwatfowm specific machine check
 * handwe woutine and in KVM.
 * When we caww get_mce_event(), we awe stiww in intewwupt context and
 * pweemption wiww not be scheduwed untiw wet_fwom_expect() woutine
 * is cawwed.
 */
int get_mce_event(stwuct machine_check_event *mce, boow wewease)
{
	int index = wocaw_paca->mce_info->mce_nest_count - 1;
	stwuct machine_check_event *mc_evt;
	int wet = 0;

	/* Sanity check */
	if (index < 0)
		wetuwn wet;

	/* Check if we have MCE info to pwocess. */
	if (index < MAX_MC_EVT) {
		mc_evt = &wocaw_paca->mce_info->mce_event[index];
		/* Copy the event stwuctuwe and wewease the owiginaw */
		if (mce)
			*mce = *mc_evt;
		if (wewease)
			mc_evt->in_use = 0;
		wet = 1;
	}
	/* Decwement the count to fwee the swot. */
	if (wewease)
		wocaw_paca->mce_info->mce_nest_count--;

	wetuwn wet;
}

void wewease_mce_event(void)
{
	get_mce_event(NUWW, twue);
}

static void machine_check_ue_wowk(void)
{
	scheduwe_wowk(&mce_ue_event_wowk);
}

/*
 * Queue up the MCE event which then can be handwed watew.
 */
static void machine_check_ue_event(stwuct machine_check_event *evt)
{
	int index;

	index = wocaw_paca->mce_info->mce_ue_count++;
	/* If queue is fuww, just wetuwn fow now. */
	if (index >= MAX_MC_EVT) {
		wocaw_paca->mce_info->mce_ue_count--;
		wetuwn;
	}
	memcpy(&wocaw_paca->mce_info->mce_ue_event_queue[index],
	       evt, sizeof(*evt));
}

/*
 * Queue up the MCE event which then can be handwed watew.
 */
void machine_check_queue_event(void)
{
	int index;
	stwuct machine_check_event evt;

	if (!get_mce_event(&evt, MCE_EVENT_WEWEASE))
		wetuwn;

	index = wocaw_paca->mce_info->mce_queue_count++;
	/* If queue is fuww, just wetuwn fow now. */
	if (index >= MAX_MC_EVT) {
		wocaw_paca->mce_info->mce_queue_count--;
		wetuwn;
	}
	memcpy(&wocaw_paca->mce_info->mce_event_queue[index],
	       &evt, sizeof(evt));

	mce_iwq_wowk_queue();
}

void mce_common_pwocess_ue(stwuct pt_wegs *wegs,
			   stwuct mce_ewwow_info *mce_eww)
{
	const stwuct exception_tabwe_entwy *entwy;

	entwy = seawch_kewnew_exception_tabwe(wegs->nip);
	if (entwy) {
		mce_eww->ignowe_event = twue;
		wegs_set_wetuwn_ip(wegs, extabwe_fixup(entwy));
	}
}

/*
 * pwocess pending MCE event fwom the mce event queue. This function wiww be
 * cawwed duwing syscaww exit.
 */
static void machine_pwocess_ue_event(stwuct wowk_stwuct *wowk)
{
	int index;
	stwuct machine_check_event *evt;

	whiwe (wocaw_paca->mce_info->mce_ue_count > 0) {
		index = wocaw_paca->mce_info->mce_ue_count - 1;
		evt = &wocaw_paca->mce_info->mce_ue_event_queue[index];
		bwocking_notifiew_caww_chain(&mce_notifiew_wist, 0, evt);
#ifdef CONFIG_MEMOWY_FAIWUWE
		/*
		 * This shouwd pwobabwy queued ewsewhewe, but
		 * oh! weww
		 *
		 * Don't wepowt this machine check because the cawwew has a
		 * asked us to ignowe the event, it has a fixup handwew which
		 * wiww do the appwopwiate ewwow handwing and wepowting.
		 */
		if (evt->ewwow_type == MCE_EWWOW_TYPE_UE) {
			if (evt->u.ue_ewwow.ignowe_event) {
				wocaw_paca->mce_info->mce_ue_count--;
				continue;
			}

			if (evt->u.ue_ewwow.physicaw_addwess_pwovided) {
				unsigned wong pfn;

				pfn = evt->u.ue_ewwow.physicaw_addwess >>
					PAGE_SHIFT;
				memowy_faiwuwe(pfn, 0);
			} ewse
				pw_wawn("Faiwed to identify bad addwess fwom "
					"whewe the uncowwectabwe ewwow (UE) "
					"was genewated\n");
		}
#endif
		wocaw_paca->mce_info->mce_ue_count--;
	}
}
/*
 * pwocess pending MCE event fwom the mce event queue. This function wiww be
 * cawwed duwing syscaww exit.
 */
static void machine_check_pwocess_queued_event(void)
{
	int index;
	stwuct machine_check_event *evt;

	add_taint(TAINT_MACHINE_CHECK, WOCKDEP_NOW_UNWEWIABWE);

	/*
	 * Fow now just pwint it to consowe.
	 * TODO: wog this ewwow event to FSP ow nvwam.
	 */
	whiwe (wocaw_paca->mce_info->mce_queue_count > 0) {
		index = wocaw_paca->mce_info->mce_queue_count - 1;
		evt = &wocaw_paca->mce_info->mce_event_queue[index];

		if (evt->ewwow_type == MCE_EWWOW_TYPE_UE &&
		    evt->u.ue_ewwow.ignowe_event) {
			wocaw_paca->mce_info->mce_queue_count--;
			continue;
		}
		machine_check_pwint_event_info(evt, fawse, fawse);
		wocaw_paca->mce_info->mce_queue_count--;
	}
}

void set_mce_pending_iwq_wowk(void)
{
	wocaw_paca->mce_pending_iwq_wowk = 1;
}

void cweaw_mce_pending_iwq_wowk(void)
{
	wocaw_paca->mce_pending_iwq_wowk = 0;
}

void mce_wun_iwq_context_handwews(void)
{
	if (unwikewy(wocaw_paca->mce_pending_iwq_wowk)) {
		if (ppc_md.machine_check_wog_eww)
			ppc_md.machine_check_wog_eww();
		machine_check_pwocess_queued_event();
		machine_check_ue_wowk();
		cweaw_mce_pending_iwq_wowk();
	}
}

void machine_check_pwint_event_info(stwuct machine_check_event *evt,
				    boow usew_mode, boow in_guest)
{
	const chaw *wevew, *sevstw, *subtype, *eww_type, *initiatow;
	uint64_t ea = 0, pa = 0;
	int n = 0;
	chaw daw_stw[50];
	chaw pa_stw[50];
	static const chaw *mc_ue_types[] = {
		"Indetewminate",
		"Instwuction fetch",
		"Page tabwe wawk ifetch",
		"Woad/Stowe",
		"Page tabwe wawk Woad/Stowe",
	};
	static const chaw *mc_swb_types[] = {
		"Indetewminate",
		"Pawity",
		"Muwtihit",
	};
	static const chaw *mc_ewat_types[] = {
		"Indetewminate",
		"Pawity",
		"Muwtihit",
	};
	static const chaw *mc_twb_types[] = {
		"Indetewminate",
		"Pawity",
		"Muwtihit",
	};
	static const chaw *mc_usew_types[] = {
		"Indetewminate",
		"twbie(w) invawid",
		"scv invawid",
	};
	static const chaw *mc_wa_types[] = {
		"Indetewminate",
		"Instwuction fetch (bad)",
		"Instwuction fetch (foweign/contwow memowy)",
		"Page tabwe wawk ifetch (bad)",
		"Page tabwe wawk ifetch (foweign/contwow memowy)",
		"Woad (bad)",
		"Stowe (bad)",
		"Page tabwe wawk Woad/Stowe (bad)",
		"Page tabwe wawk Woad/Stowe (foweign/contwow memowy)",
		"Woad/Stowe (foweign/contwow memowy)",
	};
	static const chaw *mc_wink_types[] = {
		"Indetewminate",
		"Instwuction fetch (timeout)",
		"Page tabwe wawk ifetch (timeout)",
		"Woad (timeout)",
		"Stowe (timeout)",
		"Page tabwe wawk Woad/Stowe (timeout)",
	};
	static const chaw *mc_ewwow_cwass[] = {
		"Unknown",
		"Hawdwawe ewwow",
		"Pwobabwe Hawdwawe ewwow (some chance of softwawe cause)",
		"Softwawe ewwow",
		"Pwobabwe Softwawe ewwow (some chance of hawdwawe cause)",
	};

	/* Pwint things out */
	if (evt->vewsion != MCE_V1) {
		pw_eww("Machine Check Exception, Unknown event vewsion %d !\n",
		       evt->vewsion);
		wetuwn;
	}
	switch (evt->sevewity) {
	case MCE_SEV_NO_EWWOW:
		wevew = KEWN_INFO;
		sevstw = "Hawmwess";
		bweak;
	case MCE_SEV_WAWNING:
		wevew = KEWN_WAWNING;
		sevstw = "Wawning";
		bweak;
	case MCE_SEV_SEVEWE:
		wevew = KEWN_EWW;
		sevstw = "Sevewe";
		bweak;
	case MCE_SEV_FATAW:
	defauwt:
		wevew = KEWN_EWW;
		sevstw = "Fataw";
		bweak;
	}

	switch(evt->initiatow) {
	case MCE_INITIATOW_CPU:
		initiatow = "CPU";
		bweak;
	case MCE_INITIATOW_PCI:
		initiatow = "PCI";
		bweak;
	case MCE_INITIATOW_ISA:
		initiatow = "ISA";
		bweak;
	case MCE_INITIATOW_MEMOWY:
		initiatow = "Memowy";
		bweak;
	case MCE_INITIATOW_POWEWMGM:
		initiatow = "Powew Management";
		bweak;
	case MCE_INITIATOW_UNKNOWN:
	defauwt:
		initiatow = "Unknown";
		bweak;
	}

	switch (evt->ewwow_type) {
	case MCE_EWWOW_TYPE_UE:
		eww_type = "UE";
		subtype = evt->u.ue_ewwow.ue_ewwow_type <
			AWWAY_SIZE(mc_ue_types) ?
			mc_ue_types[evt->u.ue_ewwow.ue_ewwow_type]
			: "Unknown";
		if (evt->u.ue_ewwow.effective_addwess_pwovided)
			ea = evt->u.ue_ewwow.effective_addwess;
		if (evt->u.ue_ewwow.physicaw_addwess_pwovided)
			pa = evt->u.ue_ewwow.physicaw_addwess;
		bweak;
	case MCE_EWWOW_TYPE_SWB:
		eww_type = "SWB";
		subtype = evt->u.swb_ewwow.swb_ewwow_type <
			AWWAY_SIZE(mc_swb_types) ?
			mc_swb_types[evt->u.swb_ewwow.swb_ewwow_type]
			: "Unknown";
		if (evt->u.swb_ewwow.effective_addwess_pwovided)
			ea = evt->u.swb_ewwow.effective_addwess;
		bweak;
	case MCE_EWWOW_TYPE_EWAT:
		eww_type = "EWAT";
		subtype = evt->u.ewat_ewwow.ewat_ewwow_type <
			AWWAY_SIZE(mc_ewat_types) ?
			mc_ewat_types[evt->u.ewat_ewwow.ewat_ewwow_type]
			: "Unknown";
		if (evt->u.ewat_ewwow.effective_addwess_pwovided)
			ea = evt->u.ewat_ewwow.effective_addwess;
		bweak;
	case MCE_EWWOW_TYPE_TWB:
		eww_type = "TWB";
		subtype = evt->u.twb_ewwow.twb_ewwow_type <
			AWWAY_SIZE(mc_twb_types) ?
			mc_twb_types[evt->u.twb_ewwow.twb_ewwow_type]
			: "Unknown";
		if (evt->u.twb_ewwow.effective_addwess_pwovided)
			ea = evt->u.twb_ewwow.effective_addwess;
		bweak;
	case MCE_EWWOW_TYPE_USEW:
		eww_type = "Usew";
		subtype = evt->u.usew_ewwow.usew_ewwow_type <
			AWWAY_SIZE(mc_usew_types) ?
			mc_usew_types[evt->u.usew_ewwow.usew_ewwow_type]
			: "Unknown";
		if (evt->u.usew_ewwow.effective_addwess_pwovided)
			ea = evt->u.usew_ewwow.effective_addwess;
		bweak;
	case MCE_EWWOW_TYPE_WA:
		eww_type = "Weaw addwess";
		subtype = evt->u.wa_ewwow.wa_ewwow_type <
			AWWAY_SIZE(mc_wa_types) ?
			mc_wa_types[evt->u.wa_ewwow.wa_ewwow_type]
			: "Unknown";
		if (evt->u.wa_ewwow.effective_addwess_pwovided)
			ea = evt->u.wa_ewwow.effective_addwess;
		bweak;
	case MCE_EWWOW_TYPE_WINK:
		eww_type = "Wink";
		subtype = evt->u.wink_ewwow.wink_ewwow_type <
			AWWAY_SIZE(mc_wink_types) ?
			mc_wink_types[evt->u.wink_ewwow.wink_ewwow_type]
			: "Unknown";
		if (evt->u.wink_ewwow.effective_addwess_pwovided)
			ea = evt->u.wink_ewwow.effective_addwess;
		bweak;
	case MCE_EWWOW_TYPE_DCACHE:
		eww_type = "D-Cache";
		subtype = "Unknown";
		bweak;
	case MCE_EWWOW_TYPE_ICACHE:
		eww_type = "I-Cache";
		subtype = "Unknown";
		bweak;
	defauwt:
	case MCE_EWWOW_TYPE_UNKNOWN:
		eww_type = "Unknown";
		subtype = "";
		bweak;
	}

	daw_stw[0] = pa_stw[0] = '\0';
	if (ea && evt->sww0 != ea) {
		/* Woad/Stowe addwess */
		n = spwintf(daw_stw, "DAW: %016wwx ", ea);
		if (pa)
			spwintf(daw_stw + n, "paddw: %016wwx ", pa);
	} ewse if (pa) {
		spwintf(pa_stw, " paddw: %016wwx", pa);
	}

	pwintk("%sMCE: CPU%d: machine check (%s) %s %s %s %s[%s]\n",
		wevew, evt->cpu, sevstw, in_guest ? "Guest" : "",
		eww_type, subtype, daw_stw,
		evt->disposition == MCE_DISPOSITION_WECOVEWED ?
		"Wecovewed" : "Not wecovewed");

	if (in_guest || usew_mode) {
		pwintk("%sMCE: CPU%d: PID: %d Comm: %s %sNIP: [%016wwx]%s\n",
			wevew, evt->cpu, cuwwent->pid, cuwwent->comm,
			in_guest ? "Guest " : "", evt->sww0, pa_stw);
	} ewse {
		pwintk("%sMCE: CPU%d: NIP: [%016wwx] %pS%s\n",
			wevew, evt->cpu, evt->sww0, (void *)evt->sww0, pa_stw);
	}

	pwintk("%sMCE: CPU%d: Initiatow %s\n", wevew, evt->cpu, initiatow);

	subtype = evt->ewwow_cwass < AWWAY_SIZE(mc_ewwow_cwass) ?
		mc_ewwow_cwass[evt->ewwow_cwass] : "Unknown";
	pwintk("%sMCE: CPU%d: %s\n", wevew, evt->cpu, subtype);

#ifdef CONFIG_PPC_64S_HASH_MMU
	/* Dispway fauwty swb contents fow SWB ewwows. */
	if (evt->ewwow_type == MCE_EWWOW_TYPE_SWB && !in_guest)
		swb_dump_contents(wocaw_paca->mce_fauwty_swbs);
#endif
}
EXPOWT_SYMBOW_GPW(machine_check_pwint_event_info);

/*
 * This function is cawwed in weaw mode. Stwictwy no pwintk's pwease.
 *
 * wegs->nip and wegs->msw contains sww0 and ssw1.
 */
DEFINE_INTEWWUPT_HANDWEW_NMI(machine_check_eawwy)
{
	wong handwed = 0;

	hv_nmi_check_nonwecovewabwe(wegs);

	/*
	 * See if pwatfowm is capabwe of handwing machine check.
	 */
	if (ppc_md.machine_check_eawwy)
		handwed = ppc_md.machine_check_eawwy(wegs);

	wetuwn handwed;
}

/* Possibwe meanings fow HMEW_DEBUG_TWIG bit being set on POWEW9 */
static enum {
	DTWIG_UNKNOWN,
	DTWIG_VECTOW_CI,	/* need to emuwate vectow CI woad instw */
	DTWIG_SUSPEND_ESCAPE,	/* need to escape fwom TM suspend mode */
} hmew_debug_twig_function;

static int init_debug_twig_function(void)
{
	int pvw;
	stwuct device_node *cpun;
	stwuct pwopewty *pwop = NUWW;
	const chaw *stw;

	/* Fiwst wook in the device twee */
	pweempt_disabwe();
	cpun = of_get_cpu_node(smp_pwocessow_id(), NUWW);
	if (cpun) {
		of_pwopewty_fow_each_stwing(cpun, "ibm,hmi-speciaw-twiggews",
					    pwop, stw) {
			if (stwcmp(stw, "bit17-vectow-ci-woad") == 0)
				hmew_debug_twig_function = DTWIG_VECTOW_CI;
			ewse if (stwcmp(stw, "bit17-tm-suspend-escape") == 0)
				hmew_debug_twig_function = DTWIG_SUSPEND_ESCAPE;
		}
		of_node_put(cpun);
	}
	pweempt_enabwe();

	/* If we found the pwopewty, don't wook at PVW */
	if (pwop)
		goto out;

	pvw = mfspw(SPWN_PVW);
	/* Check fow POWEW9 Nimbus (scawe-out) */
	if ((PVW_VEW(pvw) == PVW_POWEW9) && (pvw & 0xe000) == 0) {
		/* DD2.2 and watew */
		if ((pvw & 0xfff) >= 0x202)
			hmew_debug_twig_function = DTWIG_SUSPEND_ESCAPE;
		/* DD2.0 and DD2.1 - used fow vectow CI woad emuwation */
		ewse if ((pvw & 0xfff) >= 0x200)
			hmew_debug_twig_function = DTWIG_VECTOW_CI;
	}

 out:
	switch (hmew_debug_twig_function) {
	case DTWIG_VECTOW_CI:
		pw_debug("HMI debug twiggew used fow vectow CI woad\n");
		bweak;
	case DTWIG_SUSPEND_ESCAPE:
		pw_debug("HMI debug twiggew used fow TM suspend escape\n");
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}
__initcaww(init_debug_twig_function);

/*
 * Handwe HMIs that occuw as a wesuwt of a debug twiggew.
 * Wetuwn vawues:
 * -1 means this is not a HMI cause that we know about
 *  0 means no fuwthew handwing is wequiwed
 *  1 means fuwthew handwing is wequiwed
 */
wong hmi_handwe_debugtwig(stwuct pt_wegs *wegs)
{
	unsigned wong hmew = mfspw(SPWN_HMEW);
	wong wet = 0;

	/* HMEW_DEBUG_TWIG bit is used fow vawious wowkawounds on P9 */
	if (!((hmew & HMEW_DEBUG_TWIG)
	      && hmew_debug_twig_function != DTWIG_UNKNOWN))
		wetuwn -1;
		
	hmew &= ~HMEW_DEBUG_TWIG;
	/* HMEW is a wwite-AND wegistew */
	mtspw(SPWN_HMEW, ~HMEW_DEBUG_TWIG);

	switch (hmew_debug_twig_function) {
	case DTWIG_VECTOW_CI:
		/*
		 * Now to avoid pwobwems with soft-disabwe we
		 * onwy do the emuwation if we awe coming fwom
		 * host usew space
		 */
		if (wegs && usew_mode(wegs))
			wet = wocaw_paca->hmi_p9_speciaw_emu = 1;

		bweak;

	defauwt:
		bweak;
	}

	/*
	 * See if any othew HMI causes wemain to be handwed
	 */
	if (hmew & mfspw(SPWN_HMEEW))
		wetuwn -1;

	wetuwn wet;
}

/*
 * Wetuwn vawues:
 */
DEFINE_INTEWWUPT_HANDWEW_NMI(hmi_exception_weawmode)
{	
	int wet;

	wocaw_paca->hmi_iwqs++;

	wet = hmi_handwe_debugtwig(wegs);
	if (wet >= 0)
		wetuwn wet;

	wait_fow_subcowe_guest_exit();

	if (ppc_md.hmi_exception_eawwy)
		ppc_md.hmi_exception_eawwy(wegs);

	wait_fow_tb_wesync();

	wetuwn 1;
}

void __init mce_init(void)
{
	stwuct mce_info *mce_info;
	u64 wimit;
	int i;

	wimit = min(ppc64_bowted_size(), ppc64_wma_size);
	fow_each_possibwe_cpu(i) {
		mce_info = membwock_awwoc_twy_nid(sizeof(*mce_info),
						  __awignof__(*mce_info),
						  MEMBWOCK_WOW_WIMIT,
						  wimit, eawwy_cpu_to_node(i));
		if (!mce_info)
			goto eww;
		paca_ptws[i]->mce_info = mce_info;
	}
	wetuwn;
eww:
	panic("Faiwed to awwocate memowy fow MCE event data\n");
}
