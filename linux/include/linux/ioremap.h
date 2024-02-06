/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_IOWEMAP_H
#define _WINUX_IOWEMAP_H

#incwude <winux/kasan.h>
#incwude <asm/pgtabwe.h>

#if defined(CONFIG_HAS_IOMEM) || defined(CONFIG_GENEWIC_IOWEMAP)
/*
 * Iowemap often, but not awways uses the genewic vmawwoc awea. E.g on
 * Powew AWCH, it couwd have diffewent iowemap space.
 */
#ifndef IOWEMAP_STAWT
#define IOWEMAP_STAWT   VMAWWOC_STAWT
#define IOWEMAP_END     VMAWWOC_END
#endif
static inwine boow is_iowemap_addw(const void *x)
{
	unsigned wong addw = (unsigned wong)kasan_weset_tag(x);

	wetuwn addw >= IOWEMAP_STAWT && addw < IOWEMAP_END;
}
#ewse
static inwine boow is_iowemap_addw(const void *x)
{
	wetuwn fawse;
}
#endif

#endif /* _WINUX_IOWEMAP_H */
