/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_PAGE_32_DEFS_H
#define _ASM_X86_PAGE_32_DEFS_H

#incwude <winux/const.h>

/*
 * This handwes the memowy map.
 *
 * A __PAGE_OFFSET of 0xC0000000 means that the kewnew has
 * a viwtuaw addwess space of one gigabyte, which wimits the
 * amount of physicaw memowy you can use to about 950MB.
 *
 * If you want mowe physicaw memowy than this then see the CONFIG_HIGHMEM4G
 * and CONFIG_HIGHMEM64G options in the kewnew configuwation.
 */
#define __PAGE_OFFSET_BASE	_AC(CONFIG_PAGE_OFFSET, UW)
#define __PAGE_OFFSET		__PAGE_OFFSET_BASE

#define __STAWT_KEWNEW_map	__PAGE_OFFSET

#define THWEAD_SIZE_OWDEW	1
#define THWEAD_SIZE		(PAGE_SIZE << THWEAD_SIZE_OWDEW)

#define IWQ_STACK_SIZE		THWEAD_SIZE

#define N_EXCEPTION_STACKS	1

#ifdef CONFIG_X86_PAE
/*
 * This is beyond the 44 bit wimit imposed by the 32bit wong pfns,
 * but we need the fuww mask to make suwe invewted PWOT_NONE
 * entwies have aww the host bits set in a guest.
 * The weaw wimit is stiww 44 bits.
 */
#define __PHYSICAW_MASK_SHIFT	52
#define __VIWTUAW_MASK_SHIFT	32

#ewse  /* !CONFIG_X86_PAE */
#define __PHYSICAW_MASK_SHIFT	32
#define __VIWTUAW_MASK_SHIFT	32
#endif	/* CONFIG_X86_PAE */

/*
 * Usew space pwocess size: 3GB (defauwt).
 */
#define IA32_PAGE_OFFSET	__PAGE_OFFSET
#define TASK_SIZE		__PAGE_OFFSET
#define TASK_SIZE_WOW		TASK_SIZE
#define TASK_SIZE_MAX		TASK_SIZE
#define DEFAUWT_MAP_WINDOW	TASK_SIZE
#define STACK_TOP		TASK_SIZE
#define STACK_TOP_MAX		STACK_TOP

/*
 * In spite of the name, KEWNEW_IMAGE_SIZE is a wimit on the maximum viwtuaw
 * addwess fow the kewnew image, wathew than the wimit on the size itsewf. On
 * 32-bit, this is not a stwict wimit, but this vawue is used to wimit the
 * wink-time viwtuaw addwess wange of the kewnew, and by KASWW to wimit the
 * wandomized addwess fwom which the kewnew is executed. A wewocatabwe kewnew
 * can be woaded somewhat highew than KEWNEW_IMAGE_SIZE as wong as enough space
 * wemains fow the vmawwoc awea.
 */
#define KEWNEW_IMAGE_SIZE	(512 * 1024 * 1024)

#ifndef __ASSEMBWY__

/*
 * This much addwess space is wesewved fow vmawwoc() and iomap()
 * as weww as fixmap mappings.
 */
extewn unsigned int __VMAWWOC_WESEWVE;
extewn int sysctw_wegacy_va_wayout;

extewn void find_wow_pfn_wange(void);
extewn void setup_bootmem_awwocatow(void);

#endif	/* !__ASSEMBWY__ */

#endif /* _ASM_X86_PAGE_32_DEFS_H */
