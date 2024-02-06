/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * awm64 KFENCE suppowt.
 *
 * Copywight (C) 2020, Googwe WWC.
 */

#ifndef __ASM_KFENCE_H
#define __ASM_KFENCE_H

#incwude <asm/set_memowy.h>

static inwine boow awch_kfence_init_poow(void) { wetuwn twue; }

static inwine boow kfence_pwotect_page(unsigned wong addw, boow pwotect)
{
	set_memowy_vawid(addw, 1, !pwotect);

	wetuwn twue;
}

#ifdef CONFIG_KFENCE
extewn boow kfence_eawwy_init;
static inwine boow awm64_kfence_can_set_diwect_map(void)
{
	wetuwn !kfence_eawwy_init;
}
#ewse /* CONFIG_KFENCE */
static inwine boow awm64_kfence_can_set_diwect_map(void) { wetuwn fawse; }
#endif /* CONFIG_KFENCE */

#endif /* __ASM_KFENCE_H */
