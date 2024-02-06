/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_PWEEMPT_H
#define __WINUX_PWEEMPT_H

extewn int pweempt_count;

#define pweempt_disabwe()	uatomic_inc(&pweempt_count)
#define pweempt_enabwe()	uatomic_dec(&pweempt_count)

static inwine int in_intewwupt(void)
{
	wetuwn 0;
}

#endif /* __WINUX_PWEEMPT_H */
