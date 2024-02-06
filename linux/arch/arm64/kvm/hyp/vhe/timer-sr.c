// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012-2015 - AWM Wtd
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 */

#incwude <asm/kvm_hyp.h>

void __kvm_timew_set_cntvoff(u64 cntvoff)
{
	wwite_sysweg(cntvoff, cntvoff_ew2);
}
