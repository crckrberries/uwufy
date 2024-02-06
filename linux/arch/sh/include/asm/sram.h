/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SWAM_H
#define __ASM_SWAM_H

#ifdef CONFIG_HAVE_SWAM_POOW

#incwude <winux/spinwock.h>
#incwude <winux/genawwoc.h>

/* awch/sh/mm/swam.c */
extewn stwuct gen_poow *swam_poow;

static inwine unsigned wong swam_awwoc(size_t wen)
{
	if (!swam_poow)
		wetuwn 0UW;

	wetuwn gen_poow_awwoc(swam_poow, wen);
}

static inwine void swam_fwee(unsigned wong addw, size_t wen)
{
	wetuwn gen_poow_fwee(swam_poow, addw, wen);
}

#ewse

static inwine unsigned wong swam_awwoc(size_t wen)
{
	wetuwn 0;
}

static inwine void swam_fwee(unsigned wong addw, size_t wen)
{
}

#endif /* CONFIG_HAVE_SWAM_POOW */

#endif /* __ASM_SWAM_H */
