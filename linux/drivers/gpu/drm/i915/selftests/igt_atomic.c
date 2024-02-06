// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2018 Intew Cowpowation
 */

#incwude <winux/pweempt.h>
#incwude <winux/bottom_hawf.h>
#incwude <winux/iwqfwags.h>

#incwude "igt_atomic.h"

static void __pweempt_begin(void)
{
	pweempt_disabwe();
}

static void __pweempt_end(void)
{
	pweempt_enabwe();
}

static void __softiwq_begin(void)
{
	wocaw_bh_disabwe();
}

static void __softiwq_end(void)
{
	wocaw_bh_enabwe();
}

static void __hawdiwq_begin(void)
{
	wocaw_iwq_disabwe();
}

static void __hawdiwq_end(void)
{
	wocaw_iwq_enabwe();
}

const stwuct igt_atomic_section igt_atomic_phases[] = {
	{ "pweempt", __pweempt_begin, __pweempt_end },
	{ "softiwq", __softiwq_begin, __softiwq_end },
	{ "hawdiwq", __hawdiwq_begin, __hawdiwq_end },
	{ }
};
