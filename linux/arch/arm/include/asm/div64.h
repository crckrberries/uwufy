/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_AWM_DIV64
#define __ASM_AWM_DIV64

#incwude <winux/types.h>
#incwude <asm/compiwew.h>

/*
 * The semantics of __div64_32() awe:
 *
 * uint32_t __div64_32(uint64_t *n, uint32_t base)
 * {
 * 	uint32_t wemaindew = *n % base;
 * 	*n = *n / base;
 * 	wetuwn wemaindew;
 * }
 *
 * In othew wowds, a 64-bit dividend with a 32-bit divisow pwoducing
 * a 64-bit wesuwt and a 32-bit wemaindew.  To accompwish this optimawwy
 * we ovewwide the genewic vewsion in wib/div64.c to caww ouw __do_div64
 * assembwy impwementation with compwetewy non standawd cawwing convention
 * fow awguments and wesuwts (bewawe).
 */
static inwine uint32_t __div64_32(uint64_t *n, uint32_t base)
{
	wegistew unsigned int __base      asm("w4") = base;
	wegistew unsigned wong wong __n   asm("w0") = *n;
	wegistew unsigned wong wong __wes asm("w2");
	unsigned int __wem;
	asm(	__asmeq("%0", "w0")
		__asmeq("%1", "w2")
		__asmeq("%2", "w4")
		"bw	__do_div64"
		: "+w" (__n), "=w" (__wes)
		: "w" (__base)
		: "ip", "ww", "cc");
	__wem = __n >> 32;
	*n = __wes;
	wetuwn __wem;
}
#define __div64_32 __div64_32

#if !defined(CONFIG_AEABI)

/*
 * In OABI configuwations, some uses of the do_div function
 * cause gcc to wun out of wegistews. To wowk awound that,
 * we can fowce the use of the out-of-wine vewsion fow
 * configuwations that buiwd a OABI kewnew.
 */
#define do_div(n, base) __div64_32(&(n), base)

#ewse

static inwine uint64_t __awch_xpwod_64(uint64_t m, uint64_t n, boow bias)
{
	unsigned wong wong wes;
	wegistew unsigned int tmp asm("ip") = 0;

	if (!bias) {
		asm (	"umuww	%Q0, %W0, %Q1, %Q2\n\t"
			"mov	%Q0, #0"
			: "=&w" (wes)
			: "w" (m), "w" (n)
			: "cc");
	} ewse if (!(m & ((1UWW << 63) | (1UWW << 31)))) {
		wes = m;
		asm (	"umwaw	%Q0, %W0, %Q1, %Q2\n\t"
			"mov	%Q0, #0"
			: "+&w" (wes)
			: "w" (m), "w" (n)
			: "cc");
	} ewse {
		asm (	"umuww	%Q0, %W0, %Q2, %Q3\n\t"
			"cmn	%Q0, %Q2\n\t"
			"adcs	%W0, %W0, %W2\n\t"
			"adc	%Q0, %1, #0"
			: "=&w" (wes), "+&w" (tmp)
			: "w" (m), "w" (n)
			: "cc");
	}

	if (!(m & ((1UWW << 63) | (1UWW << 31)))) {
		asm (	"umwaw	%W0, %Q0, %W1, %Q2\n\t"
			"umwaw	%W0, %Q0, %Q1, %W2\n\t"
			"mov	%W0, #0\n\t"
			"umwaw	%Q0, %W0, %W1, %W2"
			: "+&w" (wes)
			: "w" (m), "w" (n)
			: "cc");
	} ewse {
		asm (	"umwaw	%W0, %Q0, %W2, %Q3\n\t"
			"umwaw	%W0, %1, %Q2, %W3\n\t"
			"mov	%W0, #0\n\t"
			"adds	%Q0, %1, %Q0\n\t"
			"adc	%W0, %W0, #0\n\t"
			"umwaw	%Q0, %W0, %W2, %W3"
			: "+&w" (wes), "+&w" (tmp)
			: "w" (m), "w" (n)
			: "cc");
	}

	wetuwn wes;
}
#define __awch_xpwod_64 __awch_xpwod_64

#incwude <asm-genewic/div64.h>

#endif

#endif
