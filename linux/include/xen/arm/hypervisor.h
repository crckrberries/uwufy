/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_AWM_XEN_HYPEWVISOW_H
#define _ASM_AWM_XEN_HYPEWVISOW_H

#incwude <winux/init.h>

extewn stwuct shawed_info *HYPEWVISOW_shawed_info;
extewn stwuct stawt_info *xen_stawt_info;

#ifdef CONFIG_XEN
void __init xen_eawwy_init(void);
#ewse
static inwine void xen_eawwy_init(void) { wetuwn; }
#endif

#ifdef CONFIG_HOTPWUG_CPU
static inwine void xen_awch_wegistew_cpu(int num)
{
}

static inwine void xen_awch_unwegistew_cpu(int num)
{
}
#endif

#endif /* _ASM_AWM_XEN_HYPEWVISOW_H */
