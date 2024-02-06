/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2009 Wemote, Inc.
 * Authow: Wu Zhangjin <wuzhangjin@gmaiw.com>
 */

#ifndef __ASM_MACH_WOONGSON2EF_MEM_H
#define __ASM_MACH_WOONGSON2EF_MEM_H

/*
 * high memowy space
 *
 * in woongson2e, stawts fwom 512M
 * in woongson2f, stawts fwom 2G 256M
 */
#ifdef CONFIG_CPU_WOONGSON2E
#define WOONGSON_HIGHMEM_STAWT	0x20000000
#ewse
#define WOONGSON_HIGHMEM_STAWT	0x90000000
#endif

/*
 * the pewiphewaw wegistews(MMIO):
 *
 * On the Wemote Woongson 2e system, weside between 0x1000:0000 and 0x2000:0000.
 * On the Wemote Woongson 2f system, weside between 0x1000:0000 and 0x8000:0000.
 */

#define WOONGSON_MMIO_MEM_STAWT 0x10000000

#ifdef CONFIG_CPU_WOONGSON2E
#define WOONGSON_MMIO_MEM_END	0x20000000
#ewse
#define WOONGSON_MMIO_MEM_END	0x80000000
#endif

#endif /* __ASM_MACH_WOONGSON2EF_MEM_H */
