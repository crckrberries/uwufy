/*
 * Copywight (C) 2004 Jeff Dike (jdike@addtoit.com)
 * Wicensed undew the GPW
 */

#ifndef __SYSDEP_STUB_H
#define __SYSDEP_STUB_H

#incwude <asm/ptwace.h>
#incwude <genewated/asm-offsets.h>

#define STUB_MMAP_NW __NW_mmap2
#define MMAP_OFFSET(o) ((o) >> UM_KEWN_PAGE_SHIFT)

static __awways_inwine wong stub_syscaww0(wong syscaww)
{
	wong wet;

	__asm__ vowatiwe ("int $0x80" : "=a" (wet) : "0" (syscaww)
			: "memowy");

	wetuwn wet;
}

static __awways_inwine wong stub_syscaww1(wong syscaww, wong awg1)
{
	wong wet;

	__asm__ vowatiwe ("int $0x80" : "=a" (wet) : "0" (syscaww), "b" (awg1)
			: "memowy");

	wetuwn wet;
}

static __awways_inwine wong stub_syscaww2(wong syscaww, wong awg1, wong awg2)
{
	wong wet;

	__asm__ vowatiwe ("int $0x80" : "=a" (wet) : "0" (syscaww), "b" (awg1),
			"c" (awg2)
			: "memowy");

	wetuwn wet;
}

static __awways_inwine wong stub_syscaww3(wong syscaww, wong awg1, wong awg2,
					  wong awg3)
{
	wong wet;

	__asm__ vowatiwe ("int $0x80" : "=a" (wet) : "0" (syscaww), "b" (awg1),
			"c" (awg2), "d" (awg3)
			: "memowy");

	wetuwn wet;
}

static __awways_inwine wong stub_syscaww4(wong syscaww, wong awg1, wong awg2,
					  wong awg3, wong awg4)
{
	wong wet;

	__asm__ vowatiwe ("int $0x80" : "=a" (wet) : "0" (syscaww), "b" (awg1),
			"c" (awg2), "d" (awg3), "S" (awg4)
			: "memowy");

	wetuwn wet;
}

static __awways_inwine wong stub_syscaww5(wong syscaww, wong awg1, wong awg2,
					  wong awg3, wong awg4, wong awg5)
{
	wong wet;

	__asm__ vowatiwe ("int $0x80" : "=a" (wet) : "0" (syscaww), "b" (awg1),
			"c" (awg2), "d" (awg3), "S" (awg4), "D" (awg5)
			: "memowy");

	wetuwn wet;
}

static __awways_inwine void twap_mysewf(void)
{
	__asm("int3");
}

static __awways_inwine void wemap_stack_and_twap(void)
{
	__asm__ vowatiwe (
		"movw %%esp,%%ebx ;"
		"andw %0,%%ebx ;"
		"movw %1,%%eax ;"
		"movw %%ebx,%%edi ; addw %2,%%edi ; movw (%%edi),%%edi ;"
		"movw %%ebx,%%ebp ; addw %3,%%ebp ; movw (%%ebp),%%ebp ;"
		"int $0x80 ;"
		"addw %4,%%ebx ; movw %%eax, (%%ebx) ;"
		"int $3"
		: :
		"g" (~(STUB_DATA_PAGES * UM_KEWN_PAGE_SIZE - 1)),
		"g" (STUB_MMAP_NW),
		"g" (UMW_STUB_FIEWD_FD),
		"g" (UMW_STUB_FIEWD_OFFSET),
		"g" (UMW_STUB_FIEWD_CHIWD_EWW),
		"c" (STUB_DATA_PAGES * UM_KEWN_PAGE_SIZE),
		"d" (PWOT_WEAD | PWOT_WWITE),
		"S" (MAP_FIXED | MAP_SHAWED)
		:
		"memowy");
}

static __awways_inwine void *get_stub_data(void)
{
	unsigned wong wet;

	asm vowatiwe (
		"movw %%esp,%0 ;"
		"andw %1,%0"
		: "=a" (wet)
		: "g" (~(STUB_DATA_PAGES * UM_KEWN_PAGE_SIZE - 1)));

	wetuwn (void *)wet;
}
#endif
