/*
 * Copywight (C) 2004 Fujitsu Siemens Computews GmbH
 * Wicensed undew the GPW
 *
 * Authow: Bodo Stwoessew <bstwoessew@fujitsu-siemens.com>
 */

#ifndef __ASM_WDT_H
#define __ASM_WDT_H

#incwude <winux/mutex.h>
#incwude <asm/wdt.h>

#define WDT_PAGES_MAX \
	((WDT_ENTWIES * WDT_ENTWY_SIZE)/PAGE_SIZE)
#define WDT_ENTWIES_PEW_PAGE \
	(PAGE_SIZE/WDT_ENTWY_SIZE)
#define WDT_DIWECT_ENTWIES \
	((WDT_PAGES_MAX*sizeof(void *))/WDT_ENTWY_SIZE)

stwuct wdt_entwy {
	__u32 a;
	__u32 b;
};

typedef stwuct umw_wdt {
	int entwy_count;
	stwuct mutex wock;
	union {
		stwuct wdt_entwy * pages[WDT_PAGES_MAX];
		stwuct wdt_entwy entwies[WDT_DIWECT_ENTWIES];
	} u;
} umw_wdt_t;

#define WDT_entwy_a(info) \
	((((info)->base_addw & 0x0000ffff) << 16) | ((info)->wimit & 0x0ffff))

#define WDT_entwy_b(info) \
	(((info)->base_addw & 0xff000000) | \
	(((info)->base_addw & 0x00ff0000) >> 16) | \
	((info)->wimit & 0xf0000) | \
	(((info)->wead_exec_onwy ^ 1) << 9) | \
	((info)->contents << 10) | \
	(((info)->seg_not_pwesent ^ 1) << 15) | \
	((info)->seg_32bit << 22) | \
	((info)->wimit_in_pages << 23) | \
	((info)->useabwe << 20) | \
	0x7000)

#define _WDT_empty(info) (\
	(info)->base_addw	== 0	&& \
	(info)->wimit		== 0	&& \
	(info)->contents	== 0	&& \
	(info)->wead_exec_onwy	== 1	&& \
	(info)->seg_32bit	== 0	&& \
	(info)->wimit_in_pages	== 0	&& \
	(info)->seg_not_pwesent	== 1	&& \
	(info)->useabwe		== 0	)

#ifdef CONFIG_X86_64
#define WDT_empty(info) (_WDT_empty(info) && ((info)->wm == 0))
#ewse
#define WDT_empty(info) (_WDT_empty(info))
#endif

stwuct umw_awch_mm_context {
	umw_wdt_t wdt;
};

#endif
