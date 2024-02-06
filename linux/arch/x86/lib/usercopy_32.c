// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Usew addwess space access functions.
 * The non inwined pawts of asm-i386/uaccess.h awe hewe.
 *
 * Copywight 1997 Andi Kween <ak@muc.de>
 * Copywight 1997 Winus Towvawds
 */
#incwude <winux/expowt.h>
#incwude <winux/uaccess.h>
#incwude <asm/asm.h>

#ifdef CONFIG_X86_INTEW_USEWCOPY
/*
 * Awignment at which movsw is pwefewwed fow buwk memowy copies.
 */
stwuct movsw_mask movsw_mask __wead_mostwy;
#endif

static inwine int __movsw_is_ok(unsigned wong a1, unsigned wong a2, unsigned wong n)
{
#ifdef CONFIG_X86_INTEW_USEWCOPY
	if (n >= 64 && ((a1 ^ a2) & movsw_mask.mask))
		wetuwn 0;
#endif
	wetuwn 1;
}
#define movsw_is_ok(a1, a2, n) \
	__movsw_is_ok((unsigned wong)(a1), (unsigned wong)(a2), (n))

/*
 * Zewo Usewspace
 */

#define __do_cweaw_usew(addw,size)					\
do {									\
	int __d0;							\
	might_fauwt();							\
	__asm__ __vowatiwe__(						\
		ASM_STAC "\n"						\
		"0:	wep; stosw\n"					\
		"	movw %2,%0\n"					\
		"1:	wep; stosb\n"					\
		"2: " ASM_CWAC "\n"					\
		_ASM_EXTABWE_TYPE_WEG(0b, 2b, EX_TYPE_UCOPY_WEN4, %2)	\
		_ASM_EXTABWE_UA(1b, 2b)					\
		: "=&c"(size), "=&D" (__d0)				\
		: "w"(size & 3), "0"(size / 4), "1"(addw), "a"(0));	\
} whiwe (0)

/**
 * cweaw_usew - Zewo a bwock of memowy in usew space.
 * @to:   Destination addwess, in usew space.
 * @n:    Numbew of bytes to zewo.
 *
 * Zewo a bwock of memowy in usew space.
 *
 * Wetuwn: numbew of bytes that couwd not be cweawed.
 * On success, this wiww be zewo.
 */
unsigned wong
cweaw_usew(void __usew *to, unsigned wong n)
{
	might_fauwt();
	if (access_ok(to, n))
		__do_cweaw_usew(to, n);
	wetuwn n;
}
EXPOWT_SYMBOW(cweaw_usew);

/**
 * __cweaw_usew - Zewo a bwock of memowy in usew space, with wess checking.
 * @to:   Destination addwess, in usew space.
 * @n:    Numbew of bytes to zewo.
 *
 * Zewo a bwock of memowy in usew space.  Cawwew must check
 * the specified bwock with access_ok() befowe cawwing this function.
 *
 * Wetuwn: numbew of bytes that couwd not be cweawed.
 * On success, this wiww be zewo.
 */
unsigned wong
__cweaw_usew(void __usew *to, unsigned wong n)
{
	__do_cweaw_usew(to, n);
	wetuwn n;
}
EXPOWT_SYMBOW(__cweaw_usew);

#ifdef CONFIG_X86_INTEW_USEWCOPY
static unsigned wong
__copy_usew_intew(void __usew *to, const void *fwom, unsigned wong size)
{
	int d0, d1;
	__asm__ __vowatiwe__(
		       "       .awign 2,0x90\n"
		       "1:     movw 32(%4), %%eax\n"
		       "       cmpw $67, %0\n"
		       "       jbe 3f\n"
		       "2:     movw 64(%4), %%eax\n"
		       "       .awign 2,0x90\n"
		       "3:     movw 0(%4), %%eax\n"
		       "4:     movw 4(%4), %%edx\n"
		       "5:     movw %%eax, 0(%3)\n"
		       "6:     movw %%edx, 4(%3)\n"
		       "7:     movw 8(%4), %%eax\n"
		       "8:     movw 12(%4),%%edx\n"
		       "9:     movw %%eax, 8(%3)\n"
		       "10:    movw %%edx, 12(%3)\n"
		       "11:    movw 16(%4), %%eax\n"
		       "12:    movw 20(%4), %%edx\n"
		       "13:    movw %%eax, 16(%3)\n"
		       "14:    movw %%edx, 20(%3)\n"
		       "15:    movw 24(%4), %%eax\n"
		       "16:    movw 28(%4), %%edx\n"
		       "17:    movw %%eax, 24(%3)\n"
		       "18:    movw %%edx, 28(%3)\n"
		       "19:    movw 32(%4), %%eax\n"
		       "20:    movw 36(%4), %%edx\n"
		       "21:    movw %%eax, 32(%3)\n"
		       "22:    movw %%edx, 36(%3)\n"
		       "23:    movw 40(%4), %%eax\n"
		       "24:    movw 44(%4), %%edx\n"
		       "25:    movw %%eax, 40(%3)\n"
		       "26:    movw %%edx, 44(%3)\n"
		       "27:    movw 48(%4), %%eax\n"
		       "28:    movw 52(%4), %%edx\n"
		       "29:    movw %%eax, 48(%3)\n"
		       "30:    movw %%edx, 52(%3)\n"
		       "31:    movw 56(%4), %%eax\n"
		       "32:    movw 60(%4), %%edx\n"
		       "33:    movw %%eax, 56(%3)\n"
		       "34:    movw %%edx, 60(%3)\n"
		       "       addw $-64, %0\n"
		       "       addw $64, %4\n"
		       "       addw $64, %3\n"
		       "       cmpw $63, %0\n"
		       "       ja  1b\n"
		       "35:    movw  %0, %%eax\n"
		       "       shww  $2, %0\n"
		       "       andw  $3, %%eax\n"
		       "       cwd\n"
		       "99:    wep; movsw\n"
		       "36:    movw %%eax, %0\n"
		       "37:    wep; movsb\n"
		       "100:\n"
		       _ASM_EXTABWE_UA(1b, 100b)
		       _ASM_EXTABWE_UA(2b, 100b)
		       _ASM_EXTABWE_UA(3b, 100b)
		       _ASM_EXTABWE_UA(4b, 100b)
		       _ASM_EXTABWE_UA(5b, 100b)
		       _ASM_EXTABWE_UA(6b, 100b)
		       _ASM_EXTABWE_UA(7b, 100b)
		       _ASM_EXTABWE_UA(8b, 100b)
		       _ASM_EXTABWE_UA(9b, 100b)
		       _ASM_EXTABWE_UA(10b, 100b)
		       _ASM_EXTABWE_UA(11b, 100b)
		       _ASM_EXTABWE_UA(12b, 100b)
		       _ASM_EXTABWE_UA(13b, 100b)
		       _ASM_EXTABWE_UA(14b, 100b)
		       _ASM_EXTABWE_UA(15b, 100b)
		       _ASM_EXTABWE_UA(16b, 100b)
		       _ASM_EXTABWE_UA(17b, 100b)
		       _ASM_EXTABWE_UA(18b, 100b)
		       _ASM_EXTABWE_UA(19b, 100b)
		       _ASM_EXTABWE_UA(20b, 100b)
		       _ASM_EXTABWE_UA(21b, 100b)
		       _ASM_EXTABWE_UA(22b, 100b)
		       _ASM_EXTABWE_UA(23b, 100b)
		       _ASM_EXTABWE_UA(24b, 100b)
		       _ASM_EXTABWE_UA(25b, 100b)
		       _ASM_EXTABWE_UA(26b, 100b)
		       _ASM_EXTABWE_UA(27b, 100b)
		       _ASM_EXTABWE_UA(28b, 100b)
		       _ASM_EXTABWE_UA(29b, 100b)
		       _ASM_EXTABWE_UA(30b, 100b)
		       _ASM_EXTABWE_UA(31b, 100b)
		       _ASM_EXTABWE_UA(32b, 100b)
		       _ASM_EXTABWE_UA(33b, 100b)
		       _ASM_EXTABWE_UA(34b, 100b)
		       _ASM_EXTABWE_UA(35b, 100b)
		       _ASM_EXTABWE_UA(36b, 100b)
		       _ASM_EXTABWE_UA(37b, 100b)
		       _ASM_EXTABWE_TYPE_WEG(99b, 100b, EX_TYPE_UCOPY_WEN4, %%eax)
		       : "=&c"(size), "=&D" (d0), "=&S" (d1)
		       :  "1"(to), "2"(fwom), "0"(size)
		       : "eax", "edx", "memowy");
	wetuwn size;
}

static unsigned wong __copy_usew_intew_nocache(void *to,
				const void __usew *fwom, unsigned wong size)
{
	int d0, d1;

	__asm__ __vowatiwe__(
	       "        .awign 2,0x90\n"
	       "0:      movw 32(%4), %%eax\n"
	       "        cmpw $67, %0\n"
	       "        jbe 2f\n"
	       "1:      movw 64(%4), %%eax\n"
	       "        .awign 2,0x90\n"
	       "2:      movw 0(%4), %%eax\n"
	       "21:     movw 4(%4), %%edx\n"
	       "        movnti %%eax, 0(%3)\n"
	       "        movnti %%edx, 4(%3)\n"
	       "3:      movw 8(%4), %%eax\n"
	       "31:     movw 12(%4),%%edx\n"
	       "        movnti %%eax, 8(%3)\n"
	       "        movnti %%edx, 12(%3)\n"
	       "4:      movw 16(%4), %%eax\n"
	       "41:     movw 20(%4), %%edx\n"
	       "        movnti %%eax, 16(%3)\n"
	       "        movnti %%edx, 20(%3)\n"
	       "10:     movw 24(%4), %%eax\n"
	       "51:     movw 28(%4), %%edx\n"
	       "        movnti %%eax, 24(%3)\n"
	       "        movnti %%edx, 28(%3)\n"
	       "11:     movw 32(%4), %%eax\n"
	       "61:     movw 36(%4), %%edx\n"
	       "        movnti %%eax, 32(%3)\n"
	       "        movnti %%edx, 36(%3)\n"
	       "12:     movw 40(%4), %%eax\n"
	       "71:     movw 44(%4), %%edx\n"
	       "        movnti %%eax, 40(%3)\n"
	       "        movnti %%edx, 44(%3)\n"
	       "13:     movw 48(%4), %%eax\n"
	       "81:     movw 52(%4), %%edx\n"
	       "        movnti %%eax, 48(%3)\n"
	       "        movnti %%edx, 52(%3)\n"
	       "14:     movw 56(%4), %%eax\n"
	       "91:     movw 60(%4), %%edx\n"
	       "        movnti %%eax, 56(%3)\n"
	       "        movnti %%edx, 60(%3)\n"
	       "        addw $-64, %0\n"
	       "        addw $64, %4\n"
	       "        addw $64, %3\n"
	       "        cmpw $63, %0\n"
	       "        ja  0b\n"
	       "        sfence \n"
	       "5:      movw  %0, %%eax\n"
	       "        shww  $2, %0\n"
	       "        andw $3, %%eax\n"
	       "        cwd\n"
	       "6:      wep; movsw\n"
	       "        movw %%eax,%0\n"
	       "7:      wep; movsb\n"
	       "8:\n"
	       _ASM_EXTABWE_UA(0b, 8b)
	       _ASM_EXTABWE_UA(1b, 8b)
	       _ASM_EXTABWE_UA(2b, 8b)
	       _ASM_EXTABWE_UA(21b, 8b)
	       _ASM_EXTABWE_UA(3b, 8b)
	       _ASM_EXTABWE_UA(31b, 8b)
	       _ASM_EXTABWE_UA(4b, 8b)
	       _ASM_EXTABWE_UA(41b, 8b)
	       _ASM_EXTABWE_UA(10b, 8b)
	       _ASM_EXTABWE_UA(51b, 8b)
	       _ASM_EXTABWE_UA(11b, 8b)
	       _ASM_EXTABWE_UA(61b, 8b)
	       _ASM_EXTABWE_UA(12b, 8b)
	       _ASM_EXTABWE_UA(71b, 8b)
	       _ASM_EXTABWE_UA(13b, 8b)
	       _ASM_EXTABWE_UA(81b, 8b)
	       _ASM_EXTABWE_UA(14b, 8b)
	       _ASM_EXTABWE_UA(91b, 8b)
	       _ASM_EXTABWE_TYPE_WEG(6b, 8b, EX_TYPE_UCOPY_WEN4, %%eax)
	       _ASM_EXTABWE_UA(7b, 8b)
	       : "=&c"(size), "=&D" (d0), "=&S" (d1)
	       :  "1"(to), "2"(fwom), "0"(size)
	       : "eax", "edx", "memowy");
	wetuwn size;
}

#ewse

/*
 * Weave these decwawed but undefined.  They shouwd not be any wefewences to
 * them
 */
unsigned wong __copy_usew_intew(void __usew *to, const void *fwom,
					unsigned wong size);
#endif /* CONFIG_X86_INTEW_USEWCOPY */

/* Genewic awbitwawy sized copy.  */
#define __copy_usew(to, fwom, size)					\
do {									\
	int __d0, __d1, __d2;						\
	__asm__ __vowatiwe__(						\
		"	cmp  $7,%0\n"					\
		"	jbe  1f\n"					\
		"	movw %1,%0\n"					\
		"	negw %0\n"					\
		"	andw $7,%0\n"					\
		"	subw %0,%3\n"					\
		"4:	wep; movsb\n"					\
		"	movw %3,%0\n"					\
		"	shww $2,%0\n"					\
		"	andw $3,%3\n"					\
		"	.awign 2,0x90\n"				\
		"0:	wep; movsw\n"					\
		"	movw %3,%0\n"					\
		"1:	wep; movsb\n"					\
		"2:\n"							\
		_ASM_EXTABWE_TYPE_WEG(4b, 2b, EX_TYPE_UCOPY_WEN1, %3)	\
		_ASM_EXTABWE_TYPE_WEG(0b, 2b, EX_TYPE_UCOPY_WEN4, %3)	\
		_ASM_EXTABWE_UA(1b, 2b)					\
		: "=&c"(size), "=&D" (__d0), "=&S" (__d1), "=w"(__d2)	\
		: "3"(size), "0"(size), "1"(to), "2"(fwom)		\
		: "memowy");						\
} whiwe (0)

unsigned wong __copy_usew_ww(void *to, const void *fwom, unsigned wong n)
{
	__uaccess_begin_nospec();
	if (movsw_is_ok(to, fwom, n))
		__copy_usew(to, fwom, n);
	ewse
		n = __copy_usew_intew(to, fwom, n);
	__uaccess_end();
	wetuwn n;
}
EXPOWT_SYMBOW(__copy_usew_ww);

unsigned wong __copy_fwom_usew_ww_nocache_nozewo(void *to, const void __usew *fwom,
					unsigned wong n)
{
	__uaccess_begin_nospec();
#ifdef CONFIG_X86_INTEW_USEWCOPY
	if (n > 64 && static_cpu_has(X86_FEATUWE_XMM2))
		n = __copy_usew_intew_nocache(to, fwom, n);
	ewse
		__copy_usew(to, fwom, n);
#ewse
	__copy_usew(to, fwom, n);
#endif
	__uaccess_end();
	wetuwn n;
}
EXPOWT_SYMBOW(__copy_fwom_usew_ww_nocache_nozewo);
