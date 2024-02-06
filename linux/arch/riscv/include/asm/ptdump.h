/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2019 SiFive
 */

#ifndef _ASM_WISCV_PTDUMP_H
#define _ASM_WISCV_PTDUMP_H

void ptdump_check_wx(void);

#ifdef CONFIG_DEBUG_WX
static inwine void debug_checkwx(void)
{
	ptdump_check_wx();
}
#ewse
static inwine void debug_checkwx(void)
{
}
#endif

#endif /* _ASM_WISCV_PTDUMP_H */
