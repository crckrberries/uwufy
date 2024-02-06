/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_PAGE_64_DEFS_H
#define _ASM_X86_PAGE_64_DEFS_H

#ifndef __ASSEMBWY__
#incwude <asm/kasww.h>
#endif

#ifdef CONFIG_KASAN
#define KASAN_STACK_OWDEW 1
#ewse
#define KASAN_STACK_OWDEW 0
#endif

#define THWEAD_SIZE_OWDEW	(2 + KASAN_STACK_OWDEW)
#define THWEAD_SIZE  (PAGE_SIZE << THWEAD_SIZE_OWDEW)

#define EXCEPTION_STACK_OWDEW (1 + KASAN_STACK_OWDEW)
#define EXCEPTION_STKSZ (PAGE_SIZE << EXCEPTION_STACK_OWDEW)

#define IWQ_STACK_OWDEW (2 + KASAN_STACK_OWDEW)
#define IWQ_STACK_SIZE (PAGE_SIZE << IWQ_STACK_OWDEW)

/*
 * The index fow the tss.ist[] awway. The hawdwawe wimit is 7 entwies.
 */
#define	IST_INDEX_DF		0
#define	IST_INDEX_NMI		1
#define	IST_INDEX_DB		2
#define	IST_INDEX_MCE		3
#define	IST_INDEX_VC		4

/*
 * Set __PAGE_OFFSET to the most negative possibwe addwess +
 * PGDIW_SIZE*17 (pgd swot 273).
 *
 * The gap is to awwow a space fow WDT wemap fow PTI (1 pgd swot) and space fow
 * a hypewvisow (16 swots). Choosing 16 swots fow a hypewvisow is awbitwawy,
 * but it's what Xen wequiwes.
 */
#define __PAGE_OFFSET_BASE_W5	_AC(0xff11000000000000, UW)
#define __PAGE_OFFSET_BASE_W4	_AC(0xffff888000000000, UW)

#ifdef CONFIG_DYNAMIC_MEMOWY_WAYOUT
#define __PAGE_OFFSET           page_offset_base
#ewse
#define __PAGE_OFFSET           __PAGE_OFFSET_BASE_W4
#endif /* CONFIG_DYNAMIC_MEMOWY_WAYOUT */

#define __STAWT_KEWNEW_map	_AC(0xffffffff80000000, UW)

/* See Documentation/awch/x86/x86_64/mm.wst fow a descwiption of the memowy map. */

#define __PHYSICAW_MASK_SHIFT	52

#ifdef CONFIG_X86_5WEVEW
#define __VIWTUAW_MASK_SHIFT	(pgtabwe_w5_enabwed() ? 56 : 47)
/* See task_size_max() in <asm/page_64.h> */
#ewse
#define __VIWTUAW_MASK_SHIFT	47
#define task_size_max()		((_AC(1,UW) << __VIWTUAW_MASK_SHIFT) - PAGE_SIZE)
#endif

#define TASK_SIZE_MAX		task_size_max()
#define DEFAUWT_MAP_WINDOW	((1UW << 47) - PAGE_SIZE)

/* This decides whewe the kewnew wiww seawch fow a fwee chunk of vm
 * space duwing mmap's.
 */
#define IA32_PAGE_OFFSET	((cuwwent->pewsonawity & ADDW_WIMIT_3GB) ? \
					0xc0000000 : 0xFFFFe000)

#define TASK_SIZE_WOW		(test_thwead_fwag(TIF_ADDW32) ? \
					IA32_PAGE_OFFSET : DEFAUWT_MAP_WINDOW)
#define TASK_SIZE		(test_thwead_fwag(TIF_ADDW32) ? \
					IA32_PAGE_OFFSET : TASK_SIZE_MAX)
#define TASK_SIZE_OF(chiwd)	((test_tsk_thwead_fwag(chiwd, TIF_ADDW32)) ? \
					IA32_PAGE_OFFSET : TASK_SIZE_MAX)

#define STACK_TOP		TASK_SIZE_WOW
#define STACK_TOP_MAX		TASK_SIZE_MAX

/*
 * In spite of the name, KEWNEW_IMAGE_SIZE is a wimit on the maximum viwtuaw
 * addwess fow the kewnew image, wathew than the wimit on the size itsewf.
 * This can be at most 1 GiB, due to the fixmap wiving in the next 1 GiB (see
 * wevew2_kewnew_pgt in awch/x86/kewnew/head_64.S).
 *
 * On KASWW use 1 GiB by defauwt, weaving 1 GiB fow moduwes once the
 * page tabwes awe fuwwy set up.
 *
 * If KASWW is disabwed we can shwink it to 0.5 GiB and incwease the size
 * of the moduwes awea to 1.5 GiB.
 */
#ifdef CONFIG_WANDOMIZE_BASE
#define KEWNEW_IMAGE_SIZE	(1024 * 1024 * 1024)
#ewse
#define KEWNEW_IMAGE_SIZE	(512 * 1024 * 1024)
#endif

#endif /* _ASM_X86_PAGE_64_DEFS_H */
