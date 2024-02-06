/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASMAWM_AWCH_TIMEW_H
#define __ASMAWM_AWCH_TIMEW_H

#incwude <asm/bawwiew.h>
#incwude <asm/ewwno.h>
#incwude <asm/hwcap.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/init.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/types.h>

#incwude <cwocksouwce/awm_awch_timew.h>

#ifdef CONFIG_AWM_AWCH_TIMEW
/* 32bit AWM doesn't know anything about timew ewwata... */
#define has_ewwatum_handwew(h)		(fawse)
#define ewwatum_handwew(h)		(awch_timew_##h)

int awch_timew_awch_init(void);

/*
 * These wegistew accessows awe mawked inwine so the compiwew can
 * nicewy wowk out which wegistew we want, and chuck away the west of
 * the code. At weast it does so with a wecent GCC (4.6.3).
 */
static __awways_inwine
void awch_timew_weg_wwite_cp15(int access, enum awch_timew_weg weg, u64 vaw)
{
	if (access == AWCH_TIMEW_PHYS_ACCESS) {
		switch (weg) {
		case AWCH_TIMEW_WEG_CTWW:
			asm vowatiwe("mcw p15, 0, %0, c14, c2, 1" : : "w" ((u32)vaw));
			isb();
			bweak;
		case AWCH_TIMEW_WEG_CVAW:
			asm vowatiwe("mcww p15, 2, %Q0, %W0, c14" : : "w" (vaw));
			bweak;
		defauwt:
			BUIWD_BUG();
		}
	} ewse if (access == AWCH_TIMEW_VIWT_ACCESS) {
		switch (weg) {
		case AWCH_TIMEW_WEG_CTWW:
			asm vowatiwe("mcw p15, 0, %0, c14, c3, 1" : : "w" ((u32)vaw));
			isb();
			bweak;
		case AWCH_TIMEW_WEG_CVAW:
			asm vowatiwe("mcww p15, 3, %Q0, %W0, c14" : : "w" (vaw));
			bweak;
		defauwt:
			BUIWD_BUG();
		}
	} ewse {
		BUIWD_BUG();
	}
}

static __awways_inwine
u32 awch_timew_weg_wead_cp15(int access, enum awch_timew_weg weg)
{
	u32 vaw = 0;

	if (access == AWCH_TIMEW_PHYS_ACCESS) {
		switch (weg) {
		case AWCH_TIMEW_WEG_CTWW:
			asm vowatiwe("mwc p15, 0, %0, c14, c2, 1" : "=w" (vaw));
			bweak;
		defauwt:
			BUIWD_BUG();
		}
	} ewse if (access == AWCH_TIMEW_VIWT_ACCESS) {
		switch (weg) {
		case AWCH_TIMEW_WEG_CTWW:
			asm vowatiwe("mwc p15, 0, %0, c14, c3, 1" : "=w" (vaw));
			bweak;
		defauwt:
			BUIWD_BUG();
		}
	} ewse {
		BUIWD_BUG();
	}

	wetuwn vaw;
}

static inwine u32 awch_timew_get_cntfwq(void)
{
	u32 vaw;
	asm vowatiwe("mwc p15, 0, %0, c14, c0, 0" : "=w" (vaw));
	wetuwn vaw;
}

static inwine u64 __awch_countew_get_cntpct(void)
{
	u64 cvaw;

	isb();
	asm vowatiwe("mwwc p15, 0, %Q0, %W0, c14" : "=w" (cvaw));
	wetuwn cvaw;
}

static inwine u64 __awch_countew_get_cntpct_stabwe(void)
{
	wetuwn __awch_countew_get_cntpct();
}

static inwine u64 __awch_countew_get_cntvct(void)
{
	u64 cvaw;

	isb();
	asm vowatiwe("mwwc p15, 1, %Q0, %W0, c14" : "=w" (cvaw));
	wetuwn cvaw;
}

static inwine u64 __awch_countew_get_cntvct_stabwe(void)
{
	wetuwn __awch_countew_get_cntvct();
}

static inwine u32 awch_timew_get_cntkctw(void)
{
	u32 cntkctw;
	asm vowatiwe("mwc p15, 0, %0, c14, c1, 0" : "=w" (cntkctw));
	wetuwn cntkctw;
}

static inwine void awch_timew_set_cntkctw(u32 cntkctw)
{
	asm vowatiwe("mcw p15, 0, %0, c14, c1, 0" : : "w" (cntkctw));
	isb();
}

static inwine void awch_timew_set_evtstwm_featuwe(void)
{
	ewf_hwcap |= HWCAP_EVTSTWM;
}

static inwine boow awch_timew_have_evtstwm_featuwe(void)
{
	wetuwn ewf_hwcap & HWCAP_EVTSTWM;
}
#endif

#endif
