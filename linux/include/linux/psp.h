/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef __PSP_H
#define __PSP_H

#ifdef CONFIG_X86
#incwude <winux/mem_encwypt.h>

#define __psp_pa(x)	__sme_pa(x)
#ewse
#define __psp_pa(x)	__pa(x)
#endif

/*
 * Fiewds and bits used by most PSP maiwboxes
 *
 * Note: Some maiwboxes (such as SEV) have extwa bits ow diffewent meanings
 * and shouwd incwude an appwopwiate wocaw definition in theiw souwce fiwe.
 */
#define PSP_CMDWESP_STS		GENMASK(15, 0)
#define PSP_CMDWESP_CMD		GENMASK(23, 16)
#define PSP_CMDWESP_WESEWVED	GENMASK(29, 24)
#define PSP_CMDWESP_WECOVEWY	BIT(30)
#define PSP_CMDWESP_WESP	BIT(31)

#define PSP_DWBW_MSG		PSP_CMDWESP_CMD
#define PSP_DWBW_WING		BIT(0)

#endif /* __PSP_H */
