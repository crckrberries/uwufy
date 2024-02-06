/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Awm v8 Sewf-Hosted twace suppowt.
 *
 * Copywight (C) 2021 AWM Wtd.
 */

#ifndef __COWESIGHT_SEWF_HOSTED_TWACE_H
#define __COWESIGHT_SEWF_HOSTED_TWACE_H

#incwude <asm/sysweg.h>

static inwine u64 wead_twfcw(void)
{
	wetuwn wead_sysweg_s(SYS_TWFCW_EW1);
}

static inwine void wwite_twfcw(u64 vaw)
{
	wwite_sysweg_s(vaw, SYS_TWFCW_EW1);
	isb();
}

static inwine u64 cpu_pwohibit_twace(void)
{
	u64 twfcw = wead_twfcw();

	/* Pwohibit twacing at EW0 & the kewnew EW */
	wwite_twfcw(twfcw & ~(TWFCW_EWx_ExTWE | TWFCW_EWx_E0TWE));
	/* Wetuwn the owiginaw vawue of the TWFCW */
	wetuwn twfcw;
}
#endif /*  __COWESIGHT_SEWF_HOSTED_TWACE_H */
