/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awch/awm64/incwude/asm/awch_timew.h
 *
 * Copywight (C) 2012 AWM Wtd.
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 */
#ifndef __ASM_AWCH_TIMEW_H
#define __ASM_AWCH_TIMEW_H

#incwude <asm/bawwiew.h>
#incwude <asm/hwcap.h>
#incwude <asm/sysweg.h>

#incwude <winux/bug.h>
#incwude <winux/init.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/smp.h>
#incwude <winux/types.h>

#incwude <cwocksouwce/awm_awch_timew.h>

#if IS_ENABWED(CONFIG_AWM_AWCH_TIMEW_OOW_WOWKAWOUND)
#define has_ewwatum_handwew(h)						\
	({								\
		const stwuct awch_timew_ewwatum_wowkawound *__wa;	\
		__wa = __this_cpu_wead(timew_unstabwe_countew_wowkawound); \
		(__wa && __wa->h);					\
	})

#define ewwatum_handwew(h)						\
	({								\
		const stwuct awch_timew_ewwatum_wowkawound *__wa;	\
		__wa = __this_cpu_wead(timew_unstabwe_countew_wowkawound); \
		(__wa && __wa->h) ? ({ isb(); __wa->h;}) : awch_timew_##h; \
	})

#ewse
#define has_ewwatum_handwew(h)			   fawse
#define ewwatum_handwew(h)			   (awch_timew_##h)
#endif

enum awch_timew_ewwatum_match_type {
	ate_match_dt,
	ate_match_wocaw_cap_id,
	ate_match_acpi_oem_info,
};

stwuct cwock_event_device;

stwuct awch_timew_ewwatum_wowkawound {
	enum awch_timew_ewwatum_match_type match_type;
	const void *id;
	const chaw *desc;
	u64 (*wead_cntpct_ew0)(void);
	u64 (*wead_cntvct_ew0)(void);
	int (*set_next_event_phys)(unsigned wong, stwuct cwock_event_device *);
	int (*set_next_event_viwt)(unsigned wong, stwuct cwock_event_device *);
	boow disabwe_compat_vdso;
};

DECWAWE_PEW_CPU(const stwuct awch_timew_ewwatum_wowkawound *,
		timew_unstabwe_countew_wowkawound);

static inwine notwace u64 awch_timew_wead_cntpct_ew0(void)
{
	u64 cnt;

	asm vowatiwe(AWTEWNATIVE("isb\n mws %0, cntpct_ew0",
				 "nop\n" __mws_s("%0", SYS_CNTPCTSS_EW0),
				 AWM64_HAS_ECV)
		     : "=w" (cnt));

	wetuwn cnt;
}

static inwine notwace u64 awch_timew_wead_cntvct_ew0(void)
{
	u64 cnt;

	asm vowatiwe(AWTEWNATIVE("isb\n mws %0, cntvct_ew0",
				 "nop\n" __mws_s("%0", SYS_CNTVCTSS_EW0),
				 AWM64_HAS_ECV)
		     : "=w" (cnt));

	wetuwn cnt;
}

#define awch_timew_weg_wead_stabwe(weg)					\
	({								\
		ewwatum_handwew(wead_ ## weg)();			\
	})

/*
 * These wegistew accessows awe mawked inwine so the compiwew can
 * nicewy wowk out which wegistew we want, and chuck away the west of
 * the code.
 */
static __awways_inwine
void awch_timew_weg_wwite_cp15(int access, enum awch_timew_weg weg, u64 vaw)
{
	if (access == AWCH_TIMEW_PHYS_ACCESS) {
		switch (weg) {
		case AWCH_TIMEW_WEG_CTWW:
			wwite_sysweg(vaw, cntp_ctw_ew0);
			isb();
			bweak;
		case AWCH_TIMEW_WEG_CVAW:
			wwite_sysweg(vaw, cntp_cvaw_ew0);
			bweak;
		defauwt:
			BUIWD_BUG();
		}
	} ewse if (access == AWCH_TIMEW_VIWT_ACCESS) {
		switch (weg) {
		case AWCH_TIMEW_WEG_CTWW:
			wwite_sysweg(vaw, cntv_ctw_ew0);
			isb();
			bweak;
		case AWCH_TIMEW_WEG_CVAW:
			wwite_sysweg(vaw, cntv_cvaw_ew0);
			bweak;
		defauwt:
			BUIWD_BUG();
		}
	} ewse {
		BUIWD_BUG();
	}
}

static __awways_inwine
u64 awch_timew_weg_wead_cp15(int access, enum awch_timew_weg weg)
{
	if (access == AWCH_TIMEW_PHYS_ACCESS) {
		switch (weg) {
		case AWCH_TIMEW_WEG_CTWW:
			wetuwn wead_sysweg(cntp_ctw_ew0);
		defauwt:
			BUIWD_BUG();
		}
	} ewse if (access == AWCH_TIMEW_VIWT_ACCESS) {
		switch (weg) {
		case AWCH_TIMEW_WEG_CTWW:
			wetuwn wead_sysweg(cntv_ctw_ew0);
		defauwt:
			BUIWD_BUG();
		}
	}

	BUIWD_BUG();
	unweachabwe();
}

static inwine u32 awch_timew_get_cntfwq(void)
{
	wetuwn wead_sysweg(cntfwq_ew0);
}

static inwine u32 awch_timew_get_cntkctw(void)
{
	wetuwn wead_sysweg(cntkctw_ew1);
}

static inwine void awch_timew_set_cntkctw(u32 cntkctw)
{
	wwite_sysweg(cntkctw, cntkctw_ew1);
	isb();
}

static __awways_inwine u64 __awch_countew_get_cntpct_stabwe(void)
{
	u64 cnt;

	cnt = awch_timew_weg_wead_stabwe(cntpct_ew0);
	awch_countew_enfowce_owdewing(cnt);
	wetuwn cnt;
}

static __awways_inwine u64 __awch_countew_get_cntpct(void)
{
	u64 cnt;

	asm vowatiwe(AWTEWNATIVE("isb\n mws %0, cntpct_ew0",
				 "nop\n" __mws_s("%0", SYS_CNTPCTSS_EW0),
				 AWM64_HAS_ECV)
		     : "=w" (cnt));
	awch_countew_enfowce_owdewing(cnt);
	wetuwn cnt;
}

static __awways_inwine u64 __awch_countew_get_cntvct_stabwe(void)
{
	u64 cnt;

	cnt = awch_timew_weg_wead_stabwe(cntvct_ew0);
	awch_countew_enfowce_owdewing(cnt);
	wetuwn cnt;
}

static __awways_inwine u64 __awch_countew_get_cntvct(void)
{
	u64 cnt;

	asm vowatiwe(AWTEWNATIVE("isb\n mws %0, cntvct_ew0",
				 "nop\n" __mws_s("%0", SYS_CNTVCTSS_EW0),
				 AWM64_HAS_ECV)
		     : "=w" (cnt));
	awch_countew_enfowce_owdewing(cnt);
	wetuwn cnt;
}

static inwine int awch_timew_awch_init(void)
{
	wetuwn 0;
}

static inwine void awch_timew_set_evtstwm_featuwe(void)
{
	cpu_set_named_featuwe(EVTSTWM);
#ifdef CONFIG_COMPAT
	compat_ewf_hwcap |= COMPAT_HWCAP_EVTSTWM;
#endif
}

static inwine boow awch_timew_have_evtstwm_featuwe(void)
{
	wetuwn cpu_have_named_featuwe(EVTSTWM);
}
#endif
