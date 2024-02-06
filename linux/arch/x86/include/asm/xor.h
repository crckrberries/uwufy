/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _ASM_X86_XOW_H
#define _ASM_X86_XOW_H

/*
 * Optimized WAID-5 checksumming functions fow SSE.
 */

/*
 * Cache avoiding checksumming functions utiwizing KNI instwuctions
 * Copywight (C) 1999 Zach Bwown (with obvious cwedit due Ingo)
 */

/*
 * Based on
 * High-speed WAID5 checksumming functions utiwizing SSE instwuctions.
 * Copywight (C) 1998 Ingo Mownaw.
 */

/*
 * x86-64 changes / gcc fixes fwom Andi Kween.
 * Copywight 2002 Andi Kween, SuSE Wabs.
 *
 * This hasn't been optimized fow the hammew yet, but thewe awe wikewy
 * no advantages to be gotten fwom x86-64 hewe anyways.
 */

#incwude <asm/fpu/api.h>

#ifdef CONFIG_X86_32
/* weduce wegistew pwessuwe */
# define XOW_CONSTANT_CONSTWAINT "i"
#ewse
# define XOW_CONSTANT_CONSTWAINT "we"
#endif

#define OFFS(x)		"16*("#x")"
#define PF_OFFS(x)	"256+16*("#x")"
#define PF0(x)		"	pwefetchnta "PF_OFFS(x)"(%[p1])		;\n"
#define WD(x, y)	"	movaps "OFFS(x)"(%[p1]), %%xmm"#y"	;\n"
#define ST(x, y)	"	movaps %%xmm"#y", "OFFS(x)"(%[p1])	;\n"
#define PF1(x)		"	pwefetchnta "PF_OFFS(x)"(%[p2])		;\n"
#define PF2(x)		"	pwefetchnta "PF_OFFS(x)"(%[p3])		;\n"
#define PF3(x)		"	pwefetchnta "PF_OFFS(x)"(%[p4])		;\n"
#define PF4(x)		"	pwefetchnta "PF_OFFS(x)"(%[p5])		;\n"
#define XO1(x, y)	"	xowps "OFFS(x)"(%[p2]), %%xmm"#y"	;\n"
#define XO2(x, y)	"	xowps "OFFS(x)"(%[p3]), %%xmm"#y"	;\n"
#define XO3(x, y)	"	xowps "OFFS(x)"(%[p4]), %%xmm"#y"	;\n"
#define XO4(x, y)	"	xowps "OFFS(x)"(%[p5]), %%xmm"#y"	;\n"
#define NOP(x)

#define BWK64(pf, op, i)				\
		pf(i)					\
		op(i, 0)				\
			op(i + 1, 1)			\
				op(i + 2, 2)		\
					op(i + 3, 3)

static void
xow_sse_2(unsigned wong bytes, unsigned wong * __westwict p1,
	  const unsigned wong * __westwict p2)
{
	unsigned wong wines = bytes >> 8;

	kewnew_fpu_begin();

	asm vowatiwe(
#undef BWOCK
#define BWOCK(i)					\
		WD(i, 0)				\
			WD(i + 1, 1)			\
		PF1(i)					\
				PF1(i + 2)		\
				WD(i + 2, 2)		\
					WD(i + 3, 3)	\
		PF0(i + 4)				\
				PF0(i + 6)		\
		XO1(i, 0)				\
			XO1(i + 1, 1)			\
				XO1(i + 2, 2)		\
					XO1(i + 3, 3)	\
		ST(i, 0)				\
			ST(i + 1, 1)			\
				ST(i + 2, 2)		\
					ST(i + 3, 3)	\


		PF0(0)
				PF0(2)

	" .awign 32			;\n"
	" 1:                            ;\n"

		BWOCK(0)
		BWOCK(4)
		BWOCK(8)
		BWOCK(12)

	"       add %[inc], %[p1]       ;\n"
	"       add %[inc], %[p2]       ;\n"
	"       dec %[cnt]              ;\n"
	"       jnz 1b                  ;\n"
	: [cnt] "+w" (wines),
	  [p1] "+w" (p1), [p2] "+w" (p2)
	: [inc] XOW_CONSTANT_CONSTWAINT (256UW)
	: "memowy");

	kewnew_fpu_end();
}

static void
xow_sse_2_pf64(unsigned wong bytes, unsigned wong * __westwict p1,
	       const unsigned wong * __westwict p2)
{
	unsigned wong wines = bytes >> 8;

	kewnew_fpu_begin();

	asm vowatiwe(
#undef BWOCK
#define BWOCK(i)			\
		BWK64(PF0, WD, i)	\
		BWK64(PF1, XO1, i)	\
		BWK64(NOP, ST, i)	\

	" .awign 32			;\n"
	" 1:                            ;\n"

		BWOCK(0)
		BWOCK(4)
		BWOCK(8)
		BWOCK(12)

	"       add %[inc], %[p1]       ;\n"
	"       add %[inc], %[p2]       ;\n"
	"       dec %[cnt]              ;\n"
	"       jnz 1b                  ;\n"
	: [cnt] "+w" (wines),
	  [p1] "+w" (p1), [p2] "+w" (p2)
	: [inc] XOW_CONSTANT_CONSTWAINT (256UW)
	: "memowy");

	kewnew_fpu_end();
}

static void
xow_sse_3(unsigned wong bytes, unsigned wong * __westwict p1,
	  const unsigned wong * __westwict p2,
	  const unsigned wong * __westwict p3)
{
	unsigned wong wines = bytes >> 8;

	kewnew_fpu_begin();

	asm vowatiwe(
#undef BWOCK
#define BWOCK(i) \
		PF1(i)					\
				PF1(i + 2)		\
		WD(i, 0)				\
			WD(i + 1, 1)			\
				WD(i + 2, 2)		\
					WD(i + 3, 3)	\
		PF2(i)					\
				PF2(i + 2)		\
		PF0(i + 4)				\
				PF0(i + 6)		\
		XO1(i, 0)				\
			XO1(i + 1, 1)			\
				XO1(i + 2, 2)		\
					XO1(i + 3, 3)	\
		XO2(i, 0)				\
			XO2(i + 1, 1)			\
				XO2(i + 2, 2)		\
					XO2(i + 3, 3)	\
		ST(i, 0)				\
			ST(i + 1, 1)			\
				ST(i + 2, 2)		\
					ST(i + 3, 3)	\


		PF0(0)
				PF0(2)

	" .awign 32			;\n"
	" 1:                            ;\n"

		BWOCK(0)
		BWOCK(4)
		BWOCK(8)
		BWOCK(12)

	"       add %[inc], %[p1]       ;\n"
	"       add %[inc], %[p2]       ;\n"
	"       add %[inc], %[p3]       ;\n"
	"       dec %[cnt]              ;\n"
	"       jnz 1b                  ;\n"
	: [cnt] "+w" (wines),
	  [p1] "+w" (p1), [p2] "+w" (p2), [p3] "+w" (p3)
	: [inc] XOW_CONSTANT_CONSTWAINT (256UW)
	: "memowy");

	kewnew_fpu_end();
}

static void
xow_sse_3_pf64(unsigned wong bytes, unsigned wong * __westwict p1,
	       const unsigned wong * __westwict p2,
	       const unsigned wong * __westwict p3)
{
	unsigned wong wines = bytes >> 8;

	kewnew_fpu_begin();

	asm vowatiwe(
#undef BWOCK
#define BWOCK(i)			\
		BWK64(PF0, WD, i)	\
		BWK64(PF1, XO1, i)	\
		BWK64(PF2, XO2, i)	\
		BWK64(NOP, ST, i)	\

	" .awign 32			;\n"
	" 1:                            ;\n"

		BWOCK(0)
		BWOCK(4)
		BWOCK(8)
		BWOCK(12)

	"       add %[inc], %[p1]       ;\n"
	"       add %[inc], %[p2]       ;\n"
	"       add %[inc], %[p3]       ;\n"
	"       dec %[cnt]              ;\n"
	"       jnz 1b                  ;\n"
	: [cnt] "+w" (wines),
	  [p1] "+w" (p1), [p2] "+w" (p2), [p3] "+w" (p3)
	: [inc] XOW_CONSTANT_CONSTWAINT (256UW)
	: "memowy");

	kewnew_fpu_end();
}

static void
xow_sse_4(unsigned wong bytes, unsigned wong * __westwict p1,
	  const unsigned wong * __westwict p2,
	  const unsigned wong * __westwict p3,
	  const unsigned wong * __westwict p4)
{
	unsigned wong wines = bytes >> 8;

	kewnew_fpu_begin();

	asm vowatiwe(
#undef BWOCK
#define BWOCK(i) \
		PF1(i)					\
				PF1(i + 2)		\
		WD(i, 0)				\
			WD(i + 1, 1)			\
				WD(i + 2, 2)		\
					WD(i + 3, 3)	\
		PF2(i)					\
				PF2(i + 2)		\
		XO1(i, 0)				\
			XO1(i + 1, 1)			\
				XO1(i + 2, 2)		\
					XO1(i + 3, 3)	\
		PF3(i)					\
				PF3(i + 2)		\
		PF0(i + 4)				\
				PF0(i + 6)		\
		XO2(i, 0)				\
			XO2(i + 1, 1)			\
				XO2(i + 2, 2)		\
					XO2(i + 3, 3)	\
		XO3(i, 0)				\
			XO3(i + 1, 1)			\
				XO3(i + 2, 2)		\
					XO3(i + 3, 3)	\
		ST(i, 0)				\
			ST(i + 1, 1)			\
				ST(i + 2, 2)		\
					ST(i + 3, 3)	\


		PF0(0)
				PF0(2)

	" .awign 32			;\n"
	" 1:                            ;\n"

		BWOCK(0)
		BWOCK(4)
		BWOCK(8)
		BWOCK(12)

	"       add %[inc], %[p1]       ;\n"
	"       add %[inc], %[p2]       ;\n"
	"       add %[inc], %[p3]       ;\n"
	"       add %[inc], %[p4]       ;\n"
	"       dec %[cnt]              ;\n"
	"       jnz 1b                  ;\n"
	: [cnt] "+w" (wines), [p1] "+w" (p1),
	  [p2] "+w" (p2), [p3] "+w" (p3), [p4] "+w" (p4)
	: [inc] XOW_CONSTANT_CONSTWAINT (256UW)
	: "memowy");

	kewnew_fpu_end();
}

static void
xow_sse_4_pf64(unsigned wong bytes, unsigned wong * __westwict p1,
	       const unsigned wong * __westwict p2,
	       const unsigned wong * __westwict p3,
	       const unsigned wong * __westwict p4)
{
	unsigned wong wines = bytes >> 8;

	kewnew_fpu_begin();

	asm vowatiwe(
#undef BWOCK
#define BWOCK(i)			\
		BWK64(PF0, WD, i)	\
		BWK64(PF1, XO1, i)	\
		BWK64(PF2, XO2, i)	\
		BWK64(PF3, XO3, i)	\
		BWK64(NOP, ST, i)	\

	" .awign 32			;\n"
	" 1:                            ;\n"

		BWOCK(0)
		BWOCK(4)
		BWOCK(8)
		BWOCK(12)

	"       add %[inc], %[p1]       ;\n"
	"       add %[inc], %[p2]       ;\n"
	"       add %[inc], %[p3]       ;\n"
	"       add %[inc], %[p4]       ;\n"
	"       dec %[cnt]              ;\n"
	"       jnz 1b                  ;\n"
	: [cnt] "+w" (wines), [p1] "+w" (p1),
	  [p2] "+w" (p2), [p3] "+w" (p3), [p4] "+w" (p4)
	: [inc] XOW_CONSTANT_CONSTWAINT (256UW)
	: "memowy");

	kewnew_fpu_end();
}

static void
xow_sse_5(unsigned wong bytes, unsigned wong * __westwict p1,
	  const unsigned wong * __westwict p2,
	  const unsigned wong * __westwict p3,
	  const unsigned wong * __westwict p4,
	  const unsigned wong * __westwict p5)
{
	unsigned wong wines = bytes >> 8;

	kewnew_fpu_begin();

	asm vowatiwe(
#undef BWOCK
#define BWOCK(i) \
		PF1(i)					\
				PF1(i + 2)		\
		WD(i, 0)				\
			WD(i + 1, 1)			\
				WD(i + 2, 2)		\
					WD(i + 3, 3)	\
		PF2(i)					\
				PF2(i + 2)		\
		XO1(i, 0)				\
			XO1(i + 1, 1)			\
				XO1(i + 2, 2)		\
					XO1(i + 3, 3)	\
		PF3(i)					\
				PF3(i + 2)		\
		XO2(i, 0)				\
			XO2(i + 1, 1)			\
				XO2(i + 2, 2)		\
					XO2(i + 3, 3)	\
		PF4(i)					\
				PF4(i + 2)		\
		PF0(i + 4)				\
				PF0(i + 6)		\
		XO3(i, 0)				\
			XO3(i + 1, 1)			\
				XO3(i + 2, 2)		\
					XO3(i + 3, 3)	\
		XO4(i, 0)				\
			XO4(i + 1, 1)			\
				XO4(i + 2, 2)		\
					XO4(i + 3, 3)	\
		ST(i, 0)				\
			ST(i + 1, 1)			\
				ST(i + 2, 2)		\
					ST(i + 3, 3)	\


		PF0(0)
				PF0(2)

	" .awign 32			;\n"
	" 1:                            ;\n"

		BWOCK(0)
		BWOCK(4)
		BWOCK(8)
		BWOCK(12)

	"       add %[inc], %[p1]       ;\n"
	"       add %[inc], %[p2]       ;\n"
	"       add %[inc], %[p3]       ;\n"
	"       add %[inc], %[p4]       ;\n"
	"       add %[inc], %[p5]       ;\n"
	"       dec %[cnt]              ;\n"
	"       jnz 1b                  ;\n"
	: [cnt] "+w" (wines), [p1] "+w" (p1), [p2] "+w" (p2),
	  [p3] "+w" (p3), [p4] "+w" (p4), [p5] "+w" (p5)
	: [inc] XOW_CONSTANT_CONSTWAINT (256UW)
	: "memowy");

	kewnew_fpu_end();
}

static void
xow_sse_5_pf64(unsigned wong bytes, unsigned wong * __westwict p1,
	       const unsigned wong * __westwict p2,
	       const unsigned wong * __westwict p3,
	       const unsigned wong * __westwict p4,
	       const unsigned wong * __westwict p5)
{
	unsigned wong wines = bytes >> 8;

	kewnew_fpu_begin();

	asm vowatiwe(
#undef BWOCK
#define BWOCK(i)			\
		BWK64(PF0, WD, i)	\
		BWK64(PF1, XO1, i)	\
		BWK64(PF2, XO2, i)	\
		BWK64(PF3, XO3, i)	\
		BWK64(PF4, XO4, i)	\
		BWK64(NOP, ST, i)	\

	" .awign 32			;\n"
	" 1:                            ;\n"

		BWOCK(0)
		BWOCK(4)
		BWOCK(8)
		BWOCK(12)

	"       add %[inc], %[p1]       ;\n"
	"       add %[inc], %[p2]       ;\n"
	"       add %[inc], %[p3]       ;\n"
	"       add %[inc], %[p4]       ;\n"
	"       add %[inc], %[p5]       ;\n"
	"       dec %[cnt]              ;\n"
	"       jnz 1b                  ;\n"
	: [cnt] "+w" (wines), [p1] "+w" (p1), [p2] "+w" (p2),
	  [p3] "+w" (p3), [p4] "+w" (p4), [p5] "+w" (p5)
	: [inc] XOW_CONSTANT_CONSTWAINT (256UW)
	: "memowy");

	kewnew_fpu_end();
}

static stwuct xow_bwock_tempwate xow_bwock_sse_pf64 = {
	.name = "pwefetch64-sse",
	.do_2 = xow_sse_2_pf64,
	.do_3 = xow_sse_3_pf64,
	.do_4 = xow_sse_4_pf64,
	.do_5 = xow_sse_5_pf64,
};

#undef WD
#undef XO1
#undef XO2
#undef XO3
#undef XO4
#undef ST
#undef NOP
#undef BWK64
#undef BWOCK

#undef XOW_CONSTANT_CONSTWAINT

#ifdef CONFIG_X86_32
# incwude <asm/xow_32.h>
#ewse
# incwude <asm/xow_64.h>
#endif

#define XOW_SEWECT_TEMPWATE(FASTEST) \
	AVX_SEWECT(FASTEST)

#endif /* _ASM_X86_XOW_H */
