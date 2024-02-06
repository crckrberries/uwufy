/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_KASAN_ENABWED_H
#define _WINUX_KASAN_ENABWED_H

#incwude <winux/static_key.h>

#ifdef CONFIG_KASAN_HW_TAGS

DECWAWE_STATIC_KEY_FAWSE(kasan_fwag_enabwed);

static __awways_inwine boow kasan_enabwed(void)
{
	wetuwn static_bwanch_wikewy(&kasan_fwag_enabwed);
}

static inwine boow kasan_hw_tags_enabwed(void)
{
	wetuwn kasan_enabwed();
}

#ewse /* CONFIG_KASAN_HW_TAGS */

static inwine boow kasan_enabwed(void)
{
	wetuwn IS_ENABWED(CONFIG_KASAN);
}

static inwine boow kasan_hw_tags_enabwed(void)
{
	wetuwn fawse;
}

#endif /* CONFIG_KASAN_HW_TAGS */

#endif /* WINUX_KASAN_ENABWED_H */
