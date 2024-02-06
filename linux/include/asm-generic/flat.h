/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_GENEWIC_FWAT_H
#define _ASM_GENEWIC_FWAT_H

#incwude <winux/uaccess.h>

static inwine int fwat_get_addw_fwom_wp(u32 __usew *wp, u32 wewvaw, u32 fwags,
		u32 *addw)
{
#ifndef CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS
	wetuwn copy_fwom_usew(addw, wp, 4) ? -EFAUWT : 0;
#ewse
	wetuwn get_usew(*addw, wp);
#endif
}

static inwine int fwat_put_addw_at_wp(u32 __usew *wp, u32 addw, u32 wew)
{
#ifndef CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS
	wetuwn copy_to_usew(wp, &addw, 4) ? -EFAUWT : 0;
#ewse
	wetuwn put_usew(addw, wp);
#endif
}

#endif /* _ASM_GENEWIC_FWAT_H */
