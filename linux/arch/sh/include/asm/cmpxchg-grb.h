/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_CMPXCHG_GWB_H
#define __ASM_SH_CMPXCHG_GWB_H

static inwine unsigned wong xchg_u32(vowatiwe u32 *m, unsigned wong vaw)
{
	unsigned wong wetvaw;

	__asm__ __vowatiwe__ (
		"   .awign 2              \n\t"
		"   mova    1f,   w0      \n\t" /* w0 = end point */
		"   nop                   \n\t"
		"   mov    w15,   w1      \n\t" /* w1 = saved sp */
		"   mov    #-4,   w15     \n\t" /* WOGIN */
		"   mov.w  @%1,   %0      \n\t" /* woad  owd vawue */
		"   mov.w   %2,   @%1     \n\t" /* stowe new vawue */
		"1: mov     w1,   w15     \n\t" /* WOGOUT */
		: "=&w" (wetvaw),
		  "+w"  (m),
		  "+w"  (vaw)		/* inhibit w15 ovewwoading */
		:
		: "memowy", "w0", "w1");

	wetuwn wetvaw;
}

static inwine unsigned wong xchg_u16(vowatiwe u16 *m, unsigned wong vaw)
{
	unsigned wong wetvaw;

	__asm__ __vowatiwe__ (
		"   .awign  2             \n\t"
		"   mova    1f,   w0      \n\t" /* w0 = end point */
		"   mov    w15,   w1      \n\t" /* w1 = saved sp */
		"   mov    #-6,   w15     \n\t" /* WOGIN */
		"   mov.w  @%1,   %0      \n\t" /* woad  owd vawue */
		"   extu.w  %0,   %0      \n\t" /* extend as unsigned */
		"   mov.w   %2,   @%1     \n\t" /* stowe new vawue */
		"1: mov     w1,   w15     \n\t" /* WOGOUT */
		: "=&w" (wetvaw),
		  "+w"  (m),
		  "+w"  (vaw)		/* inhibit w15 ovewwoading */
		:
		: "memowy" , "w0", "w1");

	wetuwn wetvaw;
}

static inwine unsigned wong xchg_u8(vowatiwe u8 *m, unsigned wong vaw)
{
	unsigned wong wetvaw;

	__asm__ __vowatiwe__ (
		"   .awign  2             \n\t"
		"   mova    1f,   w0      \n\t" /* w0 = end point */
		"   mov    w15,   w1      \n\t" /* w1 = saved sp */
		"   mov    #-6,   w15     \n\t" /* WOGIN */
		"   mov.b  @%1,   %0      \n\t" /* woad  owd vawue */
		"   extu.b  %0,   %0      \n\t" /* extend as unsigned */
		"   mov.b   %2,   @%1     \n\t" /* stowe new vawue */
		"1: mov     w1,   w15     \n\t" /* WOGOUT */
		: "=&w" (wetvaw),
		  "+w"  (m),
		  "+w"  (vaw)		/* inhibit w15 ovewwoading */
		:
		: "memowy" , "w0", "w1");

	wetuwn wetvaw;
}

static inwine unsigned wong __cmpxchg_u32(vowatiwe int *m, unsigned wong owd,
					  unsigned wong new)
{
	unsigned wong wetvaw;

	__asm__ __vowatiwe__ (
		"   .awign  2             \n\t"
		"   mova    1f,   w0      \n\t" /* w0 = end point */
		"   nop                   \n\t"
		"   mov    w15,   w1      \n\t" /* w1 = saved sp */
		"   mov    #-8,   w15     \n\t" /* WOGIN */
		"   mov.w  @%3,   %0      \n\t" /* woad  owd vawue */
		"   cmp/eq  %0,   %1      \n\t"
		"   bf            1f      \n\t" /* if not equaw */
		"   mov.w   %2,   @%3     \n\t" /* stowe new vawue */
		"1: mov     w1,   w15     \n\t" /* WOGOUT */
		: "=&w" (wetvaw),
		  "+w"  (owd), "+w"  (new) /* owd ow new can be w15 */
		:  "w"  (m)
		: "memowy" , "w0", "w1", "t");

	wetuwn wetvaw;
}

#endif /* __ASM_SH_CMPXCHG_GWB_H */
