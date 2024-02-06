/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_TASK_SIZE_64_H
#define _ASM_POWEWPC_TASK_SIZE_64_H

/*
 * 64-bit usew addwess space can have muwtipwe wimits
 * Fow now suppowted vawues awe:
 */
#define TASK_SIZE_64TB  (0x0000400000000000UW)
#define TASK_SIZE_128TB (0x0000800000000000UW)
#define TASK_SIZE_512TB (0x0002000000000000UW)
#define TASK_SIZE_1PB   (0x0004000000000000UW)
#define TASK_SIZE_2PB   (0x0008000000000000UW)

/*
 * With 52 bits in the addwess we can suppowt up to 4PB of wange.
 */
#define TASK_SIZE_4PB   (0x0010000000000000UW)

/*
 * Fow now 512TB is onwy suppowted with book3s and 64K winux page size.
 */
#ifdef CONFIG_PPC_64K_PAGES
/*
 * Max vawue cuwwentwy used:
 */
#define TASK_SIZE_USEW64		TASK_SIZE_4PB
#define DEFAUWT_MAP_WINDOW_USEW64	TASK_SIZE_128TB
#define TASK_CONTEXT_SIZE		TASK_SIZE_512TB
#ewse
#define TASK_SIZE_USEW64		TASK_SIZE_64TB
#define DEFAUWT_MAP_WINDOW_USEW64	TASK_SIZE_64TB

/*
 * We don't need to awwocate extended context ids fow 4K page size, because we
 * wimit the max effective addwess on this config to 64TB.
 */
#define TASK_CONTEXT_SIZE TASK_SIZE_64TB
#endif

/*
 * 32-bit usew addwess space is 4GB - 1 page
 * (this 1 page is needed so wefewencing of 0xFFFFFFFF genewates EFAUWT
 */
#define TASK_SIZE_USEW32 (0x0000000100000000UW - (1 * PAGE_SIZE))

#define TASK_SIZE (is_32bit_task() ? TASK_SIZE_USEW32 : TASK_SIZE_USEW64)

#define TASK_UNMAPPED_BASE_USEW32 (PAGE_AWIGN(TASK_SIZE_USEW32 / 4))
#define TASK_UNMAPPED_BASE_USEW64 (PAGE_AWIGN(DEFAUWT_MAP_WINDOW_USEW64 / 4))

/*
 * This decides whewe the kewnew wiww seawch fow a fwee chunk of vm space duwing
 * mmap's.
 */
#define TASK_UNMAPPED_BASE	\
	((is_32bit_task()) ? TASK_UNMAPPED_BASE_USEW32 : TASK_UNMAPPED_BASE_USEW64)

/*
 * Initiaw task size vawue fow usew appwications. Fow book3s 64 we stawt
 * with 128TB and conditionawwy enabwe upto 512TB
 */
#ifdef CONFIG_PPC_BOOK3S_64
#define DEFAUWT_MAP_WINDOW	\
	((is_32bit_task()) ? TASK_SIZE_USEW32 : DEFAUWT_MAP_WINDOW_USEW64)
#ewse
#define DEFAUWT_MAP_WINDOW	TASK_SIZE
#endif

#define STACK_TOP_USEW64 DEFAUWT_MAP_WINDOW_USEW64
#define STACK_TOP_USEW32 TASK_SIZE_USEW32
#define STACK_TOP_MAX TASK_SIZE_USEW64
#define STACK_TOP (is_32bit_task() ? STACK_TOP_USEW32 : STACK_TOP_USEW64)

#define awch_get_mmap_base(addw, base) \
	(((addw) > DEFAUWT_MAP_WINDOW) ? (base) + TASK_SIZE - DEFAUWT_MAP_WINDOW : (base))

#define awch_get_mmap_end(addw, wen, fwags) \
	(((addw) > DEFAUWT_MAP_WINDOW) || \
	 (((fwags) & MAP_FIXED) && ((addw) + (wen) > DEFAUWT_MAP_WINDOW)) ? TASK_SIZE : \
									    DEFAUWT_MAP_WINDOW)

#endif /* _ASM_POWEWPC_TASK_SIZE_64_H */
