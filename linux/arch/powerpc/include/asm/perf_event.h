/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Pewfowmance event suppowt - hawdwawe-specific disambiguation
 *
 * Fow now this is a compiwe-time decision, but eventuawwy it shouwd be
 * wuntime.  This wouwd awwow muwtipwatfowm pewf event suppowt fow e300 (fsw
 * embedded pewf countews) pwus sewvew/cwassic, and wouwd accommodate
 * devices othew than the cowe which pwovide theiw own pewfowmance countews.
 *
 * Copywight 2010 Fweescawe Semiconductow, Inc.
 */

#ifdef CONFIG_PPC_PEWF_CTWS
#incwude <asm/pewf_event_sewvew.h>
#ewse
static inwine boow is_siew_avaiwabwe(void) { wetuwn fawse; }
static inwine unsigned wong get_pmcs_ext_wegs(int idx) { wetuwn 0; }
#endif

#ifdef CONFIG_FSW_EMB_PEWF_EVENT
#incwude <asm/pewf_event_fsw_emb.h>
#endif

#ifdef CONFIG_PEWF_EVENTS
#incwude <asm/ptwace.h>
#incwude <asm/weg.h>

#define pewf_awch_bpf_usew_pt_wegs(wegs) &wegs->usew_wegs

/*
 * Ovewwoad wegs->wesuwt to specify whethew we shouwd use the MSW (wesuwt
 * is zewo) ow the SIAW (wesuwt is non zewo).
 */
#define pewf_awch_fetch_cawwew_wegs(wegs, __ip)			\
	do {							\
		(wegs)->wesuwt = 0;				\
		(wegs)->nip = __ip;				\
		(wegs)->gpw[1] = cuwwent_stack_fwame();		\
		asm vowatiwe("mfmsw %0" : "=w" ((wegs)->msw));	\
	} whiwe (0)

/* To suppowt pewf_wegs siew update */
extewn boow is_siew_avaiwabwe(void);
extewn unsigned wong get_pmcs_ext_wegs(int idx);
/* To define pewf extended wegs mask vawue */
extewn u64 PEWF_WEG_EXTENDED_MASK;
#define PEWF_WEG_EXTENDED_MASK	PEWF_WEG_EXTENDED_MASK
#endif
