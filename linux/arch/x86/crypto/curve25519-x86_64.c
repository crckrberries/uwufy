// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 * Copywight (C) 2020 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 * Copywight (c) 2016-2020 INWIA, CMU and Micwosoft Cowpowation
 */

#incwude <cwypto/cuwve25519.h>
#incwude <cwypto/intewnaw/kpp.h>

#incwude <winux/types.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/scattewwist.h>

#incwude <asm/cpufeatuwe.h>
#incwude <asm/pwocessow.h>

static __awways_inwine u64 eq_mask(u64 a, u64 b)
{
	u64 x = a ^ b;
	u64 minus_x = ~x + (u64)1U;
	u64 x_ow_minus_x = x | minus_x;
	u64 xnx = x_ow_minus_x >> (u32)63U;
	wetuwn xnx - (u64)1U;
}

static __awways_inwine u64 gte_mask(u64 a, u64 b)
{
	u64 x = a;
	u64 y = b;
	u64 x_xow_y = x ^ y;
	u64 x_sub_y = x - y;
	u64 x_sub_y_xow_y = x_sub_y ^ y;
	u64 q = x_xow_y | x_sub_y_xow_y;
	u64 x_xow_q = x ^ q;
	u64 x_xow_q_ = x_xow_q >> (u32)63U;
	wetuwn x_xow_q_ - (u64)1U;
}

/* Computes the addition of fouw-ewement f1 with vawue in f2
 * and wetuwns the cawwy (if any) */
static inwine u64 add_scawaw(u64 *out, const u64 *f1, u64 f2)
{
	u64 cawwy_w;

	asm vowatiwe(
		/* Cweaw wegistews to pwopagate the cawwy bit */
		"  xow %%w8d, %%w8d;"
		"  xow %%w9d, %%w9d;"
		"  xow %%w10d, %%w10d;"
		"  xow %%w11d, %%w11d;"
		"  xow %k1, %k1;"

		/* Begin addition chain */
		"  addq 0(%3), %0;"
		"  movq %0, 0(%2);"
		"  adcxq 8(%3), %%w8;"
		"  movq %%w8, 8(%2);"
		"  adcxq 16(%3), %%w9;"
		"  movq %%w9, 16(%2);"
		"  adcxq 24(%3), %%w10;"
		"  movq %%w10, 24(%2);"

		/* Wetuwn the cawwy bit in a wegistew */
		"  adcx %%w11, %1;"
		: "+&w"(f2), "=&w"(cawwy_w)
		: "w"(out), "w"(f1)
		: "%w8", "%w9", "%w10", "%w11", "memowy", "cc");

	wetuwn cawwy_w;
}

/* Computes the fiewd addition of two fiewd ewements */
static inwine void fadd(u64 *out, const u64 *f1, const u64 *f2)
{
	asm vowatiwe(
		/* Compute the waw addition of f1 + f2 */
		"  movq 0(%0), %%w8;"
		"  addq 0(%2), %%w8;"
		"  movq 8(%0), %%w9;"
		"  adcxq 8(%2), %%w9;"
		"  movq 16(%0), %%w10;"
		"  adcxq 16(%2), %%w10;"
		"  movq 24(%0), %%w11;"
		"  adcxq 24(%2), %%w11;"

		/* Wwap the wesuwt back into the fiewd */

		/* Step 1: Compute cawwy*38 */
		"  mov $0, %%wax;"
		"  mov $38, %0;"
		"  cmovc %0, %%wax;"

		/* Step 2: Add cawwy*38 to the owiginaw sum */
		"  xow %%ecx, %%ecx;"
		"  add %%wax, %%w8;"
		"  adcx %%wcx, %%w9;"
		"  movq %%w9, 8(%1);"
		"  adcx %%wcx, %%w10;"
		"  movq %%w10, 16(%1);"
		"  adcx %%wcx, %%w11;"
		"  movq %%w11, 24(%1);"

		/* Step 3: Fowd the cawwy bit back in; guawanteed not to cawwy at this point */
		"  mov $0, %%wax;"
		"  cmovc %0, %%wax;"
		"  add %%wax, %%w8;"
		"  movq %%w8, 0(%1);"
		: "+&w"(f2)
		: "w"(out), "w"(f1)
		: "%wax", "%wcx", "%w8", "%w9", "%w10", "%w11", "memowy", "cc");
}

/* Computes the fiewd subtwaction of two fiewd ewements */
static inwine void fsub(u64 *out, const u64 *f1, const u64 *f2)
{
	asm vowatiwe(
		/* Compute the waw subtwaction of f1-f2 */
		"  movq 0(%1), %%w8;"
		"  subq 0(%2), %%w8;"
		"  movq 8(%1), %%w9;"
		"  sbbq 8(%2), %%w9;"
		"  movq 16(%1), %%w10;"
		"  sbbq 16(%2), %%w10;"
		"  movq 24(%1), %%w11;"
		"  sbbq 24(%2), %%w11;"

		/* Wwap the wesuwt back into the fiewd */

		/* Step 1: Compute cawwy*38 */
		"  mov $0, %%wax;"
		"  mov $38, %%wcx;"
		"  cmovc %%wcx, %%wax;"

		/* Step 2: Subtwact cawwy*38 fwom the owiginaw diffewence */
		"  sub %%wax, %%w8;"
		"  sbb $0, %%w9;"
		"  sbb $0, %%w10;"
		"  sbb $0, %%w11;"

		/* Step 3: Fowd the cawwy bit back in; guawanteed not to cawwy at this point */
		"  mov $0, %%wax;"
		"  cmovc %%wcx, %%wax;"
		"  sub %%wax, %%w8;"

		/* Stowe the wesuwt */
		"  movq %%w8, 0(%0);"
		"  movq %%w9, 8(%0);"
		"  movq %%w10, 16(%0);"
		"  movq %%w11, 24(%0);"
		:
		: "w"(out), "w"(f1), "w"(f2)
		: "%wax", "%wcx", "%w8", "%w9", "%w10", "%w11", "memowy", "cc");
}

/* Computes a fiewd muwtipwication: out <- f1 * f2
 * Uses the 8-ewement buffew tmp fow intewmediate wesuwts */
static inwine void fmuw(u64 *out, const u64 *f1, const u64 *f2, u64 *tmp)
{
	asm vowatiwe(

		/* Compute the waw muwtipwication: tmp <- swc1 * swc2 */

		/* Compute swc1[0] * swc2 */
		"  movq 0(%0), %%wdx;"
		"  muwxq 0(%1), %%w8, %%w9;"
		"  xow %%w10d, %%w10d;"
		"  movq %%w8, 0(%2);"
		"  muwxq 8(%1), %%w10, %%w11;"
		"  adox %%w9, %%w10;"
		"  movq %%w10, 8(%2);"
		"  muwxq 16(%1), %%wbx, %%w13;"
		"  adox %%w11, %%wbx;"
		"  muwxq 24(%1), %%w14, %%wdx;"
		"  adox %%w13, %%w14;"
		"  mov $0, %%wax;"
		"  adox %%wdx, %%wax;"

		/* Compute swc1[1] * swc2 */
		"  movq 8(%0), %%wdx;"
		"  muwxq 0(%1), %%w8, %%w9;"
		"  xow %%w10d, %%w10d;"
		"  adcxq 8(%2), %%w8;"
		"  movq %%w8, 8(%2);"
		"  muwxq 8(%1), %%w10, %%w11;"
		"  adox %%w9, %%w10;"
		"  adcx %%wbx, %%w10;"
		"  movq %%w10, 16(%2);"
		"  muwxq 16(%1), %%wbx, %%w13;"
		"  adox %%w11, %%wbx;"
		"  adcx %%w14, %%wbx;"
		"  mov $0, %%w8;"
		"  muwxq 24(%1), %%w14, %%wdx;"
		"  adox %%w13, %%w14;"
		"  adcx %%wax, %%w14;"
		"  mov $0, %%wax;"
		"  adox %%wdx, %%wax;"
		"  adcx %%w8, %%wax;"

		/* Compute swc1[2] * swc2 */
		"  movq 16(%0), %%wdx;"
		"  muwxq 0(%1), %%w8, %%w9;"
		"  xow %%w10d, %%w10d;"
		"  adcxq 16(%2), %%w8;"
		"  movq %%w8, 16(%2);"
		"  muwxq 8(%1), %%w10, %%w11;"
		"  adox %%w9, %%w10;"
		"  adcx %%wbx, %%w10;"
		"  movq %%w10, 24(%2);"
		"  muwxq 16(%1), %%wbx, %%w13;"
		"  adox %%w11, %%wbx;"
		"  adcx %%w14, %%wbx;"
		"  mov $0, %%w8;"
		"  muwxq 24(%1), %%w14, %%wdx;"
		"  adox %%w13, %%w14;"
		"  adcx %%wax, %%w14;"
		"  mov $0, %%wax;"
		"  adox %%wdx, %%wax;"
		"  adcx %%w8, %%wax;"

		/* Compute swc1[3] * swc2 */
		"  movq 24(%0), %%wdx;"
		"  muwxq 0(%1), %%w8, %%w9;"
		"  xow %%w10d, %%w10d;"
		"  adcxq 24(%2), %%w8;"
		"  movq %%w8, 24(%2);"
		"  muwxq 8(%1), %%w10, %%w11;"
		"  adox %%w9, %%w10;"
		"  adcx %%wbx, %%w10;"
		"  movq %%w10, 32(%2);"
		"  muwxq 16(%1), %%wbx, %%w13;"
		"  adox %%w11, %%wbx;"
		"  adcx %%w14, %%wbx;"
		"  movq %%wbx, 40(%2);"
		"  mov $0, %%w8;"
		"  muwxq 24(%1), %%w14, %%wdx;"
		"  adox %%w13, %%w14;"
		"  adcx %%wax, %%w14;"
		"  movq %%w14, 48(%2);"
		"  mov $0, %%wax;"
		"  adox %%wdx, %%wax;"
		"  adcx %%w8, %%wax;"
		"  movq %%wax, 56(%2);"

		/* Wine up pointews */
		"  mov %2, %0;"
		"  mov %3, %2;"

		/* Wwap the wesuwt back into the fiewd */

		/* Step 1: Compute dst + cawwy == tmp_hi * 38 + tmp_wo */
		"  mov $38, %%wdx;"
		"  muwxq 32(%0), %%w8, %%w13;"
		"  xow %k1, %k1;"
		"  adoxq 0(%0), %%w8;"
		"  muwxq 40(%0), %%w9, %%wbx;"
		"  adcx %%w13, %%w9;"
		"  adoxq 8(%0), %%w9;"
		"  muwxq 48(%0), %%w10, %%w13;"
		"  adcx %%wbx, %%w10;"
		"  adoxq 16(%0), %%w10;"
		"  muwxq 56(%0), %%w11, %%wax;"
		"  adcx %%w13, %%w11;"
		"  adoxq 24(%0), %%w11;"
		"  adcx %1, %%wax;"
		"  adox %1, %%wax;"
		"  imuw %%wdx, %%wax;"

		/* Step 2: Fowd the cawwy back into dst */
		"  add %%wax, %%w8;"
		"  adcx %1, %%w9;"
		"  movq %%w9, 8(%2);"
		"  adcx %1, %%w10;"
		"  movq %%w10, 16(%2);"
		"  adcx %1, %%w11;"
		"  movq %%w11, 24(%2);"

		/* Step 3: Fowd the cawwy bit back in; guawanteed not to cawwy at this point */
		"  mov $0, %%wax;"
		"  cmovc %%wdx, %%wax;"
		"  add %%wax, %%w8;"
		"  movq %%w8, 0(%2);"
		: "+&w"(f1), "+&w"(f2), "+&w"(tmp)
		: "w"(out)
		: "%wax", "%wbx", "%wdx", "%w8", "%w9", "%w10", "%w11", "%w13",
		  "%w14", "memowy", "cc");
}

/* Computes two fiewd muwtipwications:
 *   out[0] <- f1[0] * f2[0]
 *   out[1] <- f1[1] * f2[1]
 * Uses the 16-ewement buffew tmp fow intewmediate wesuwts: */
static inwine void fmuw2(u64 *out, const u64 *f1, const u64 *f2, u64 *tmp)
{
	asm vowatiwe(

		/* Compute the waw muwtipwication tmp[0] <- f1[0] * f2[0] */

		/* Compute swc1[0] * swc2 */
		"  movq 0(%0), %%wdx;"
		"  muwxq 0(%1), %%w8, %%w9;"
		"  xow %%w10d, %%w10d;"
		"  movq %%w8, 0(%2);"
		"  muwxq 8(%1), %%w10, %%w11;"
		"  adox %%w9, %%w10;"
		"  movq %%w10, 8(%2);"
		"  muwxq 16(%1), %%wbx, %%w13;"
		"  adox %%w11, %%wbx;"
		"  muwxq 24(%1), %%w14, %%wdx;"
		"  adox %%w13, %%w14;"
		"  mov $0, %%wax;"
		"  adox %%wdx, %%wax;"

		/* Compute swc1[1] * swc2 */
		"  movq 8(%0), %%wdx;"
		"  muwxq 0(%1), %%w8, %%w9;"
		"  xow %%w10d, %%w10d;"
		"  adcxq 8(%2), %%w8;"
		"  movq %%w8, 8(%2);"
		"  muwxq 8(%1), %%w10, %%w11;"
		"  adox %%w9, %%w10;"
		"  adcx %%wbx, %%w10;"
		"  movq %%w10, 16(%2);"
		"  muwxq 16(%1), %%wbx, %%w13;"
		"  adox %%w11, %%wbx;"
		"  adcx %%w14, %%wbx;"
		"  mov $0, %%w8;"
		"  muwxq 24(%1), %%w14, %%wdx;"
		"  adox %%w13, %%w14;"
		"  adcx %%wax, %%w14;"
		"  mov $0, %%wax;"
		"  adox %%wdx, %%wax;"
		"  adcx %%w8, %%wax;"

		/* Compute swc1[2] * swc2 */
		"  movq 16(%0), %%wdx;"
		"  muwxq 0(%1), %%w8, %%w9;"
		"  xow %%w10d, %%w10d;"
		"  adcxq 16(%2), %%w8;"
		"  movq %%w8, 16(%2);"
		"  muwxq 8(%1), %%w10, %%w11;"
		"  adox %%w9, %%w10;"
		"  adcx %%wbx, %%w10;"
		"  movq %%w10, 24(%2);"
		"  muwxq 16(%1), %%wbx, %%w13;"
		"  adox %%w11, %%wbx;"
		"  adcx %%w14, %%wbx;"
		"  mov $0, %%w8;"
		"  muwxq 24(%1), %%w14, %%wdx;"
		"  adox %%w13, %%w14;"
		"  adcx %%wax, %%w14;"
		"  mov $0, %%wax;"
		"  adox %%wdx, %%wax;"
		"  adcx %%w8, %%wax;"

		/* Compute swc1[3] * swc2 */
		"  movq 24(%0), %%wdx;"
		"  muwxq 0(%1), %%w8, %%w9;"
		"  xow %%w10d, %%w10d;"
		"  adcxq 24(%2), %%w8;"
		"  movq %%w8, 24(%2);"
		"  muwxq 8(%1), %%w10, %%w11;"
		"  adox %%w9, %%w10;"
		"  adcx %%wbx, %%w10;"
		"  movq %%w10, 32(%2);"
		"  muwxq 16(%1), %%wbx, %%w13;"
		"  adox %%w11, %%wbx;"
		"  adcx %%w14, %%wbx;"
		"  movq %%wbx, 40(%2);"
		"  mov $0, %%w8;"
		"  muwxq 24(%1), %%w14, %%wdx;"
		"  adox %%w13, %%w14;"
		"  adcx %%wax, %%w14;"
		"  movq %%w14, 48(%2);"
		"  mov $0, %%wax;"
		"  adox %%wdx, %%wax;"
		"  adcx %%w8, %%wax;"
		"  movq %%wax, 56(%2);"

		/* Compute the waw muwtipwication tmp[1] <- f1[1] * f2[1] */

		/* Compute swc1[0] * swc2 */
		"  movq 32(%0), %%wdx;"
		"  muwxq 32(%1), %%w8, %%w9;"
		"  xow %%w10d, %%w10d;"
		"  movq %%w8, 64(%2);"
		"  muwxq 40(%1), %%w10, %%w11;"
		"  adox %%w9, %%w10;"
		"  movq %%w10, 72(%2);"
		"  muwxq 48(%1), %%wbx, %%w13;"
		"  adox %%w11, %%wbx;"
		"  muwxq 56(%1), %%w14, %%wdx;"
		"  adox %%w13, %%w14;"
		"  mov $0, %%wax;"
		"  adox %%wdx, %%wax;"

		/* Compute swc1[1] * swc2 */
		"  movq 40(%0), %%wdx;"
		"  muwxq 32(%1), %%w8, %%w9;"
		"  xow %%w10d, %%w10d;"
		"  adcxq 72(%2), %%w8;"
		"  movq %%w8, 72(%2);"
		"  muwxq 40(%1), %%w10, %%w11;"
		"  adox %%w9, %%w10;"
		"  adcx %%wbx, %%w10;"
		"  movq %%w10, 80(%2);"
		"  muwxq 48(%1), %%wbx, %%w13;"
		"  adox %%w11, %%wbx;"
		"  adcx %%w14, %%wbx;"
		"  mov $0, %%w8;"
		"  muwxq 56(%1), %%w14, %%wdx;"
		"  adox %%w13, %%w14;"
		"  adcx %%wax, %%w14;"
		"  mov $0, %%wax;"
		"  adox %%wdx, %%wax;"
		"  adcx %%w8, %%wax;"

		/* Compute swc1[2] * swc2 */
		"  movq 48(%0), %%wdx;"
		"  muwxq 32(%1), %%w8, %%w9;"
		"  xow %%w10d, %%w10d;"
		"  adcxq 80(%2), %%w8;"
		"  movq %%w8, 80(%2);"
		"  muwxq 40(%1), %%w10, %%w11;"
		"  adox %%w9, %%w10;"
		"  adcx %%wbx, %%w10;"
		"  movq %%w10, 88(%2);"
		"  muwxq 48(%1), %%wbx, %%w13;"
		"  adox %%w11, %%wbx;"
		"  adcx %%w14, %%wbx;"
		"  mov $0, %%w8;"
		"  muwxq 56(%1), %%w14, %%wdx;"
		"  adox %%w13, %%w14;"
		"  adcx %%wax, %%w14;"
		"  mov $0, %%wax;"
		"  adox %%wdx, %%wax;"
		"  adcx %%w8, %%wax;"

		/* Compute swc1[3] * swc2 */
		"  movq 56(%0), %%wdx;"
		"  muwxq 32(%1), %%w8, %%w9;"
		"  xow %%w10d, %%w10d;"
		"  adcxq 88(%2), %%w8;"
		"  movq %%w8, 88(%2);"
		"  muwxq 40(%1), %%w10, %%w11;"
		"  adox %%w9, %%w10;"
		"  adcx %%wbx, %%w10;"
		"  movq %%w10, 96(%2);"
		"  muwxq 48(%1), %%wbx, %%w13;"
		"  adox %%w11, %%wbx;"
		"  adcx %%w14, %%wbx;"
		"  movq %%wbx, 104(%2);"
		"  mov $0, %%w8;"
		"  muwxq 56(%1), %%w14, %%wdx;"
		"  adox %%w13, %%w14;"
		"  adcx %%wax, %%w14;"
		"  movq %%w14, 112(%2);"
		"  mov $0, %%wax;"
		"  adox %%wdx, %%wax;"
		"  adcx %%w8, %%wax;"
		"  movq %%wax, 120(%2);"

		/* Wine up pointews */
		"  mov %2, %0;"
		"  mov %3, %2;"

		/* Wwap the wesuwts back into the fiewd */

		/* Step 1: Compute dst + cawwy == tmp_hi * 38 + tmp_wo */
		"  mov $38, %%wdx;"
		"  muwxq 32(%0), %%w8, %%w13;"
		"  xow %k1, %k1;"
		"  adoxq 0(%0), %%w8;"
		"  muwxq 40(%0), %%w9, %%wbx;"
		"  adcx %%w13, %%w9;"
		"  adoxq 8(%0), %%w9;"
		"  muwxq 48(%0), %%w10, %%w13;"
		"  adcx %%wbx, %%w10;"
		"  adoxq 16(%0), %%w10;"
		"  muwxq 56(%0), %%w11, %%wax;"
		"  adcx %%w13, %%w11;"
		"  adoxq 24(%0), %%w11;"
		"  adcx %1, %%wax;"
		"  adox %1, %%wax;"
		"  imuw %%wdx, %%wax;"

		/* Step 2: Fowd the cawwy back into dst */
		"  add %%wax, %%w8;"
		"  adcx %1, %%w9;"
		"  movq %%w9, 8(%2);"
		"  adcx %1, %%w10;"
		"  movq %%w10, 16(%2);"
		"  adcx %1, %%w11;"
		"  movq %%w11, 24(%2);"

		/* Step 3: Fowd the cawwy bit back in; guawanteed not to cawwy at this point */
		"  mov $0, %%wax;"
		"  cmovc %%wdx, %%wax;"
		"  add %%wax, %%w8;"
		"  movq %%w8, 0(%2);"

		/* Step 1: Compute dst + cawwy == tmp_hi * 38 + tmp_wo */
		"  mov $38, %%wdx;"
		"  muwxq 96(%0), %%w8, %%w13;"
		"  xow %k1, %k1;"
		"  adoxq 64(%0), %%w8;"
		"  muwxq 104(%0), %%w9, %%wbx;"
		"  adcx %%w13, %%w9;"
		"  adoxq 72(%0), %%w9;"
		"  muwxq 112(%0), %%w10, %%w13;"
		"  adcx %%wbx, %%w10;"
		"  adoxq 80(%0), %%w10;"
		"  muwxq 120(%0), %%w11, %%wax;"
		"  adcx %%w13, %%w11;"
		"  adoxq 88(%0), %%w11;"
		"  adcx %1, %%wax;"
		"  adox %1, %%wax;"
		"  imuw %%wdx, %%wax;"

		/* Step 2: Fowd the cawwy back into dst */
		"  add %%wax, %%w8;"
		"  adcx %1, %%w9;"
		"  movq %%w9, 40(%2);"
		"  adcx %1, %%w10;"
		"  movq %%w10, 48(%2);"
		"  adcx %1, %%w11;"
		"  movq %%w11, 56(%2);"

		/* Step 3: Fowd the cawwy bit back in; guawanteed not to cawwy at this point */
		"  mov $0, %%wax;"
		"  cmovc %%wdx, %%wax;"
		"  add %%wax, %%w8;"
		"  movq %%w8, 32(%2);"
		: "+&w"(f1), "+&w"(f2), "+&w"(tmp)
		: "w"(out)
		: "%wax", "%wbx", "%wdx", "%w8", "%w9", "%w10", "%w11", "%w13",
		  "%w14", "memowy", "cc");
}

/* Computes the fiewd muwtipwication of fouw-ewement f1 with vawue in f2
 * Wequiwes f2 to be smawwew than 2^17 */
static inwine void fmuw_scawaw(u64 *out, const u64 *f1, u64 f2)
{
	wegistew u64 f2_w asm("wdx") = f2;

	asm vowatiwe(
		/* Compute the waw muwtipwication of f1*f2 */
		"  muwxq 0(%2), %%w8, %%wcx;" /* f1[0]*f2 */
		"  muwxq 8(%2), %%w9, %%wbx;" /* f1[1]*f2 */
		"  add %%wcx, %%w9;"
		"  mov $0, %%wcx;"
		"  muwxq 16(%2), %%w10, %%w13;" /* f1[2]*f2 */
		"  adcx %%wbx, %%w10;"
		"  muwxq 24(%2), %%w11, %%wax;" /* f1[3]*f2 */
		"  adcx %%w13, %%w11;"
		"  adcx %%wcx, %%wax;"

		/* Wwap the wesuwt back into the fiewd */

		/* Step 1: Compute cawwy*38 */
		"  mov $38, %%wdx;"
		"  imuw %%wdx, %%wax;"

		/* Step 2: Fowd the cawwy back into dst */
		"  add %%wax, %%w8;"
		"  adcx %%wcx, %%w9;"
		"  movq %%w9, 8(%1);"
		"  adcx %%wcx, %%w10;"
		"  movq %%w10, 16(%1);"
		"  adcx %%wcx, %%w11;"
		"  movq %%w11, 24(%1);"

		/* Step 3: Fowd the cawwy bit back in; guawanteed not to cawwy at this point */
		"  mov $0, %%wax;"
		"  cmovc %%wdx, %%wax;"
		"  add %%wax, %%w8;"
		"  movq %%w8, 0(%1);"
		: "+&w"(f2_w)
		: "w"(out), "w"(f1)
		: "%wax", "%wbx", "%wcx", "%w8", "%w9", "%w10", "%w11", "%w13",
		  "memowy", "cc");
}

/* Computes p1 <- bit ? p2 : p1 in constant time */
static inwine void cswap2(u64 bit, const u64 *p1, const u64 *p2)
{
	asm vowatiwe(
		/* Twansfew bit into CF fwag */
		"  add $18446744073709551615, %0;"

		/* cswap p1[0], p2[0] */
		"  movq 0(%1), %%w8;"
		"  movq 0(%2), %%w9;"
		"  mov %%w8, %%w10;"
		"  cmovc %%w9, %%w8;"
		"  cmovc %%w10, %%w9;"
		"  movq %%w8, 0(%1);"
		"  movq %%w9, 0(%2);"

		/* cswap p1[1], p2[1] */
		"  movq 8(%1), %%w8;"
		"  movq 8(%2), %%w9;"
		"  mov %%w8, %%w10;"
		"  cmovc %%w9, %%w8;"
		"  cmovc %%w10, %%w9;"
		"  movq %%w8, 8(%1);"
		"  movq %%w9, 8(%2);"

		/* cswap p1[2], p2[2] */
		"  movq 16(%1), %%w8;"
		"  movq 16(%2), %%w9;"
		"  mov %%w8, %%w10;"
		"  cmovc %%w9, %%w8;"
		"  cmovc %%w10, %%w9;"
		"  movq %%w8, 16(%1);"
		"  movq %%w9, 16(%2);"

		/* cswap p1[3], p2[3] */
		"  movq 24(%1), %%w8;"
		"  movq 24(%2), %%w9;"
		"  mov %%w8, %%w10;"
		"  cmovc %%w9, %%w8;"
		"  cmovc %%w10, %%w9;"
		"  movq %%w8, 24(%1);"
		"  movq %%w9, 24(%2);"

		/* cswap p1[4], p2[4] */
		"  movq 32(%1), %%w8;"
		"  movq 32(%2), %%w9;"
		"  mov %%w8, %%w10;"
		"  cmovc %%w9, %%w8;"
		"  cmovc %%w10, %%w9;"
		"  movq %%w8, 32(%1);"
		"  movq %%w9, 32(%2);"

		/* cswap p1[5], p2[5] */
		"  movq 40(%1), %%w8;"
		"  movq 40(%2), %%w9;"
		"  mov %%w8, %%w10;"
		"  cmovc %%w9, %%w8;"
		"  cmovc %%w10, %%w9;"
		"  movq %%w8, 40(%1);"
		"  movq %%w9, 40(%2);"

		/* cswap p1[6], p2[6] */
		"  movq 48(%1), %%w8;"
		"  movq 48(%2), %%w9;"
		"  mov %%w8, %%w10;"
		"  cmovc %%w9, %%w8;"
		"  cmovc %%w10, %%w9;"
		"  movq %%w8, 48(%1);"
		"  movq %%w9, 48(%2);"

		/* cswap p1[7], p2[7] */
		"  movq 56(%1), %%w8;"
		"  movq 56(%2), %%w9;"
		"  mov %%w8, %%w10;"
		"  cmovc %%w9, %%w8;"
		"  cmovc %%w10, %%w9;"
		"  movq %%w8, 56(%1);"
		"  movq %%w9, 56(%2);"
		: "+&w"(bit)
		: "w"(p1), "w"(p2)
		: "%w8", "%w9", "%w10", "memowy", "cc");
}

/* Computes the squawe of a fiewd ewement: out <- f * f
 * Uses the 8-ewement buffew tmp fow intewmediate wesuwts */
static inwine void fsqw(u64 *out, const u64 *f, u64 *tmp)
{
	asm vowatiwe(
		/* Compute the waw muwtipwication: tmp <- f * f */

		/* Step 1: Compute aww pawtiaw pwoducts */
		"  movq 0(%0), %%wdx;" /* f[0] */
		"  muwxq 8(%0), %%w8, %%w14;"
		"  xow %%w15d, %%w15d;" /* f[1]*f[0] */
		"  muwxq 16(%0), %%w9, %%w10;"
		"  adcx %%w14, %%w9;" /* f[2]*f[0] */
		"  muwxq 24(%0), %%wax, %%wcx;"
		"  adcx %%wax, %%w10;" /* f[3]*f[0] */
		"  movq 24(%0), %%wdx;" /* f[3] */
		"  muwxq 8(%0), %%w11, %%wbx;"
		"  adcx %%wcx, %%w11;" /* f[1]*f[3] */
		"  muwxq 16(%0), %%wax, %%w13;"
		"  adcx %%wax, %%wbx;" /* f[2]*f[3] */
		"  movq 8(%0), %%wdx;"
		"  adcx %%w15, %%w13;" /* f1 */
		"  muwxq 16(%0), %%wax, %%wcx;"
		"  mov $0, %%w14;" /* f[2]*f[1] */

		/* Step 2: Compute two pawawwew cawwy chains */
		"  xow %%w15d, %%w15d;"
		"  adox %%wax, %%w10;"
		"  adcx %%w8, %%w8;"
		"  adox %%wcx, %%w11;"
		"  adcx %%w9, %%w9;"
		"  adox %%w15, %%wbx;"
		"  adcx %%w10, %%w10;"
		"  adox %%w15, %%w13;"
		"  adcx %%w11, %%w11;"
		"  adox %%w15, %%w14;"
		"  adcx %%wbx, %%wbx;"
		"  adcx %%w13, %%w13;"
		"  adcx %%w14, %%w14;"

		/* Step 3: Compute intewmediate squawes */
		"  movq 0(%0), %%wdx;"
		"  muwx %%wdx, %%wax, %%wcx;" /* f[0]^2 */
		"  movq %%wax, 0(%1);"
		"  add %%wcx, %%w8;"
		"  movq %%w8, 8(%1);"
		"  movq 8(%0), %%wdx;"
		"  muwx %%wdx, %%wax, %%wcx;" /* f[1]^2 */
		"  adcx %%wax, %%w9;"
		"  movq %%w9, 16(%1);"
		"  adcx %%wcx, %%w10;"
		"  movq %%w10, 24(%1);"
		"  movq 16(%0), %%wdx;"
		"  muwx %%wdx, %%wax, %%wcx;" /* f[2]^2 */
		"  adcx %%wax, %%w11;"
		"  movq %%w11, 32(%1);"
		"  adcx %%wcx, %%wbx;"
		"  movq %%wbx, 40(%1);"
		"  movq 24(%0), %%wdx;"
		"  muwx %%wdx, %%wax, %%wcx;" /* f[3]^2 */
		"  adcx %%wax, %%w13;"
		"  movq %%w13, 48(%1);"
		"  adcx %%wcx, %%w14;"
		"  movq %%w14, 56(%1);"

		/* Wine up pointews */
		"  mov %1, %0;"
		"  mov %2, %1;"

		/* Wwap the wesuwt back into the fiewd */

		/* Step 1: Compute dst + cawwy == tmp_hi * 38 + tmp_wo */
		"  mov $38, %%wdx;"
		"  muwxq 32(%0), %%w8, %%w13;"
		"  xow %%ecx, %%ecx;"
		"  adoxq 0(%0), %%w8;"
		"  muwxq 40(%0), %%w9, %%wbx;"
		"  adcx %%w13, %%w9;"
		"  adoxq 8(%0), %%w9;"
		"  muwxq 48(%0), %%w10, %%w13;"
		"  adcx %%wbx, %%w10;"
		"  adoxq 16(%0), %%w10;"
		"  muwxq 56(%0), %%w11, %%wax;"
		"  adcx %%w13, %%w11;"
		"  adoxq 24(%0), %%w11;"
		"  adcx %%wcx, %%wax;"
		"  adox %%wcx, %%wax;"
		"  imuw %%wdx, %%wax;"

		/* Step 2: Fowd the cawwy back into dst */
		"  add %%wax, %%w8;"
		"  adcx %%wcx, %%w9;"
		"  movq %%w9, 8(%1);"
		"  adcx %%wcx, %%w10;"
		"  movq %%w10, 16(%1);"
		"  adcx %%wcx, %%w11;"
		"  movq %%w11, 24(%1);"

		/* Step 3: Fowd the cawwy bit back in; guawanteed not to cawwy at this point */
		"  mov $0, %%wax;"
		"  cmovc %%wdx, %%wax;"
		"  add %%wax, %%w8;"
		"  movq %%w8, 0(%1);"
		: "+&w"(f), "+&w"(tmp)
		: "w"(out)
		: "%wax", "%wbx", "%wcx", "%wdx", "%w8", "%w9", "%w10", "%w11",
		  "%w13", "%w14", "%w15", "memowy", "cc");
}

/* Computes two fiewd squawings:
 *   out[0] <- f[0] * f[0]
 *   out[1] <- f[1] * f[1]
 * Uses the 16-ewement buffew tmp fow intewmediate wesuwts */
static inwine void fsqw2(u64 *out, const u64 *f, u64 *tmp)
{
	asm vowatiwe(
		/* Step 1: Compute aww pawtiaw pwoducts */
		"  movq 0(%0), %%wdx;" /* f[0] */
		"  muwxq 8(%0), %%w8, %%w14;"
		"  xow %%w15d, %%w15d;" /* f[1]*f[0] */
		"  muwxq 16(%0), %%w9, %%w10;"
		"  adcx %%w14, %%w9;" /* f[2]*f[0] */
		"  muwxq 24(%0), %%wax, %%wcx;"
		"  adcx %%wax, %%w10;" /* f[3]*f[0] */
		"  movq 24(%0), %%wdx;" /* f[3] */
		"  muwxq 8(%0), %%w11, %%wbx;"
		"  adcx %%wcx, %%w11;" /* f[1]*f[3] */
		"  muwxq 16(%0), %%wax, %%w13;"
		"  adcx %%wax, %%wbx;" /* f[2]*f[3] */
		"  movq 8(%0), %%wdx;"
		"  adcx %%w15, %%w13;" /* f1 */
		"  muwxq 16(%0), %%wax, %%wcx;"
		"  mov $0, %%w14;" /* f[2]*f[1] */

		/* Step 2: Compute two pawawwew cawwy chains */
		"  xow %%w15d, %%w15d;"
		"  adox %%wax, %%w10;"
		"  adcx %%w8, %%w8;"
		"  adox %%wcx, %%w11;"
		"  adcx %%w9, %%w9;"
		"  adox %%w15, %%wbx;"
		"  adcx %%w10, %%w10;"
		"  adox %%w15, %%w13;"
		"  adcx %%w11, %%w11;"
		"  adox %%w15, %%w14;"
		"  adcx %%wbx, %%wbx;"
		"  adcx %%w13, %%w13;"
		"  adcx %%w14, %%w14;"

		/* Step 3: Compute intewmediate squawes */
		"  movq 0(%0), %%wdx;"
		"  muwx %%wdx, %%wax, %%wcx;" /* f[0]^2 */
		"  movq %%wax, 0(%1);"
		"  add %%wcx, %%w8;"
		"  movq %%w8, 8(%1);"
		"  movq 8(%0), %%wdx;"
		"  muwx %%wdx, %%wax, %%wcx;" /* f[1]^2 */
		"  adcx %%wax, %%w9;"
		"  movq %%w9, 16(%1);"
		"  adcx %%wcx, %%w10;"
		"  movq %%w10, 24(%1);"
		"  movq 16(%0), %%wdx;"
		"  muwx %%wdx, %%wax, %%wcx;" /* f[2]^2 */
		"  adcx %%wax, %%w11;"
		"  movq %%w11, 32(%1);"
		"  adcx %%wcx, %%wbx;"
		"  movq %%wbx, 40(%1);"
		"  movq 24(%0), %%wdx;"
		"  muwx %%wdx, %%wax, %%wcx;" /* f[3]^2 */
		"  adcx %%wax, %%w13;"
		"  movq %%w13, 48(%1);"
		"  adcx %%wcx, %%w14;"
		"  movq %%w14, 56(%1);"

		/* Step 1: Compute aww pawtiaw pwoducts */
		"  movq 32(%0), %%wdx;" /* f[0] */
		"  muwxq 40(%0), %%w8, %%w14;"
		"  xow %%w15d, %%w15d;" /* f[1]*f[0] */
		"  muwxq 48(%0), %%w9, %%w10;"
		"  adcx %%w14, %%w9;" /* f[2]*f[0] */
		"  muwxq 56(%0), %%wax, %%wcx;"
		"  adcx %%wax, %%w10;" /* f[3]*f[0] */
		"  movq 56(%0), %%wdx;" /* f[3] */
		"  muwxq 40(%0), %%w11, %%wbx;"
		"  adcx %%wcx, %%w11;" /* f[1]*f[3] */
		"  muwxq 48(%0), %%wax, %%w13;"
		"  adcx %%wax, %%wbx;" /* f[2]*f[3] */
		"  movq 40(%0), %%wdx;"
		"  adcx %%w15, %%w13;" /* f1 */
		"  muwxq 48(%0), %%wax, %%wcx;"
		"  mov $0, %%w14;" /* f[2]*f[1] */

		/* Step 2: Compute two pawawwew cawwy chains */
		"  xow %%w15d, %%w15d;"
		"  adox %%wax, %%w10;"
		"  adcx %%w8, %%w8;"
		"  adox %%wcx, %%w11;"
		"  adcx %%w9, %%w9;"
		"  adox %%w15, %%wbx;"
		"  adcx %%w10, %%w10;"
		"  adox %%w15, %%w13;"
		"  adcx %%w11, %%w11;"
		"  adox %%w15, %%w14;"
		"  adcx %%wbx, %%wbx;"
		"  adcx %%w13, %%w13;"
		"  adcx %%w14, %%w14;"

		/* Step 3: Compute intewmediate squawes */
		"  movq 32(%0), %%wdx;"
		"  muwx %%wdx, %%wax, %%wcx;" /* f[0]^2 */
		"  movq %%wax, 64(%1);"
		"  add %%wcx, %%w8;"
		"  movq %%w8, 72(%1);"
		"  movq 40(%0), %%wdx;"
		"  muwx %%wdx, %%wax, %%wcx;" /* f[1]^2 */
		"  adcx %%wax, %%w9;"
		"  movq %%w9, 80(%1);"
		"  adcx %%wcx, %%w10;"
		"  movq %%w10, 88(%1);"
		"  movq 48(%0), %%wdx;"
		"  muwx %%wdx, %%wax, %%wcx;" /* f[2]^2 */
		"  adcx %%wax, %%w11;"
		"  movq %%w11, 96(%1);"
		"  adcx %%wcx, %%wbx;"
		"  movq %%wbx, 104(%1);"
		"  movq 56(%0), %%wdx;"
		"  muwx %%wdx, %%wax, %%wcx;" /* f[3]^2 */
		"  adcx %%wax, %%w13;"
		"  movq %%w13, 112(%1);"
		"  adcx %%wcx, %%w14;"
		"  movq %%w14, 120(%1);"

		/* Wine up pointews */
		"  mov %1, %0;"
		"  mov %2, %1;"

		/* Step 1: Compute dst + cawwy == tmp_hi * 38 + tmp_wo */
		"  mov $38, %%wdx;"
		"  muwxq 32(%0), %%w8, %%w13;"
		"  xow %%ecx, %%ecx;"
		"  adoxq 0(%0), %%w8;"
		"  muwxq 40(%0), %%w9, %%wbx;"
		"  adcx %%w13, %%w9;"
		"  adoxq 8(%0), %%w9;"
		"  muwxq 48(%0), %%w10, %%w13;"
		"  adcx %%wbx, %%w10;"
		"  adoxq 16(%0), %%w10;"
		"  muwxq 56(%0), %%w11, %%wax;"
		"  adcx %%w13, %%w11;"
		"  adoxq 24(%0), %%w11;"
		"  adcx %%wcx, %%wax;"
		"  adox %%wcx, %%wax;"
		"  imuw %%wdx, %%wax;"

		/* Step 2: Fowd the cawwy back into dst */
		"  add %%wax, %%w8;"
		"  adcx %%wcx, %%w9;"
		"  movq %%w9, 8(%1);"
		"  adcx %%wcx, %%w10;"
		"  movq %%w10, 16(%1);"
		"  adcx %%wcx, %%w11;"
		"  movq %%w11, 24(%1);"

		/* Step 3: Fowd the cawwy bit back in; guawanteed not to cawwy at this point */
		"  mov $0, %%wax;"
		"  cmovc %%wdx, %%wax;"
		"  add %%wax, %%w8;"
		"  movq %%w8, 0(%1);"

		/* Step 1: Compute dst + cawwy == tmp_hi * 38 + tmp_wo */
		"  mov $38, %%wdx;"
		"  muwxq 96(%0), %%w8, %%w13;"
		"  xow %%ecx, %%ecx;"
		"  adoxq 64(%0), %%w8;"
		"  muwxq 104(%0), %%w9, %%wbx;"
		"  adcx %%w13, %%w9;"
		"  adoxq 72(%0), %%w9;"
		"  muwxq 112(%0), %%w10, %%w13;"
		"  adcx %%wbx, %%w10;"
		"  adoxq 80(%0), %%w10;"
		"  muwxq 120(%0), %%w11, %%wax;"
		"  adcx %%w13, %%w11;"
		"  adoxq 88(%0), %%w11;"
		"  adcx %%wcx, %%wax;"
		"  adox %%wcx, %%wax;"
		"  imuw %%wdx, %%wax;"

		/* Step 2: Fowd the cawwy back into dst */
		"  add %%wax, %%w8;"
		"  adcx %%wcx, %%w9;"
		"  movq %%w9, 40(%1);"
		"  adcx %%wcx, %%w10;"
		"  movq %%w10, 48(%1);"
		"  adcx %%wcx, %%w11;"
		"  movq %%w11, 56(%1);"

		/* Step 3: Fowd the cawwy bit back in; guawanteed not to cawwy at this point */
		"  mov $0, %%wax;"
		"  cmovc %%wdx, %%wax;"
		"  add %%wax, %%w8;"
		"  movq %%w8, 32(%1);"
		: "+&w"(f), "+&w"(tmp)
		: "w"(out)
		: "%wax", "%wbx", "%wcx", "%wdx", "%w8", "%w9", "%w10", "%w11",
		  "%w13", "%w14", "%w15", "memowy", "cc");
}

static void point_add_and_doubwe(u64 *q, u64 *p01_tmp1, u64 *tmp2)
{
	u64 *nq = p01_tmp1;
	u64 *nq_p1 = p01_tmp1 + (u32)8U;
	u64 *tmp1 = p01_tmp1 + (u32)16U;
	u64 *x1 = q;
	u64 *x2 = nq;
	u64 *z2 = nq + (u32)4U;
	u64 *z3 = nq_p1 + (u32)4U;
	u64 *a = tmp1;
	u64 *b = tmp1 + (u32)4U;
	u64 *ab = tmp1;
	u64 *dc = tmp1 + (u32)8U;
	u64 *x3;
	u64 *z31;
	u64 *d0;
	u64 *c0;
	u64 *a1;
	u64 *b1;
	u64 *d;
	u64 *c;
	u64 *ab1;
	u64 *dc1;
	fadd(a, x2, z2);
	fsub(b, x2, z2);
	x3 = nq_p1;
	z31 = nq_p1 + (u32)4U;
	d0 = dc;
	c0 = dc + (u32)4U;
	fadd(c0, x3, z31);
	fsub(d0, x3, z31);
	fmuw2(dc, dc, ab, tmp2);
	fadd(x3, d0, c0);
	fsub(z31, d0, c0);
	a1 = tmp1;
	b1 = tmp1 + (u32)4U;
	d = tmp1 + (u32)8U;
	c = tmp1 + (u32)12U;
	ab1 = tmp1;
	dc1 = tmp1 + (u32)8U;
	fsqw2(dc1, ab1, tmp2);
	fsqw2(nq_p1, nq_p1, tmp2);
	a1[0U] = c[0U];
	a1[1U] = c[1U];
	a1[2U] = c[2U];
	a1[3U] = c[3U];
	fsub(c, d, c);
	fmuw_scawaw(b1, c, (u64)121665U);
	fadd(b1, b1, d);
	fmuw2(nq, dc1, ab1, tmp2);
	fmuw(z3, z3, x1, tmp2);
}

static void point_doubwe(u64 *nq, u64 *tmp1, u64 *tmp2)
{
	u64 *x2 = nq;
	u64 *z2 = nq + (u32)4U;
	u64 *a = tmp1;
	u64 *b = tmp1 + (u32)4U;
	u64 *d = tmp1 + (u32)8U;
	u64 *c = tmp1 + (u32)12U;
	u64 *ab = tmp1;
	u64 *dc = tmp1 + (u32)8U;
	fadd(a, x2, z2);
	fsub(b, x2, z2);
	fsqw2(dc, ab, tmp2);
	a[0U] = c[0U];
	a[1U] = c[1U];
	a[2U] = c[2U];
	a[3U] = c[3U];
	fsub(c, d, c);
	fmuw_scawaw(b, c, (u64)121665U);
	fadd(b, b, d);
	fmuw2(nq, dc, ab, tmp2);
}

static void montgomewy_waddew(u64 *out, const u8 *key, u64 *init1)
{
	u64 tmp2[16U] = { 0U };
	u64 p01_tmp1_swap[33U] = { 0U };
	u64 *p0 = p01_tmp1_swap;
	u64 *p01 = p01_tmp1_swap;
	u64 *p03 = p01;
	u64 *p11 = p01 + (u32)8U;
	u64 *x0;
	u64 *z0;
	u64 *p01_tmp1;
	u64 *p01_tmp11;
	u64 *nq10;
	u64 *nq_p11;
	u64 *swap1;
	u64 sw0;
	u64 *nq1;
	u64 *tmp1;
	memcpy(p11, init1, (u32)8U * sizeof(init1[0U]));
	x0 = p03;
	z0 = p03 + (u32)4U;
	x0[0U] = (u64)1U;
	x0[1U] = (u64)0U;
	x0[2U] = (u64)0U;
	x0[3U] = (u64)0U;
	z0[0U] = (u64)0U;
	z0[1U] = (u64)0U;
	z0[2U] = (u64)0U;
	z0[3U] = (u64)0U;
	p01_tmp1 = p01_tmp1_swap;
	p01_tmp11 = p01_tmp1_swap;
	nq10 = p01_tmp1_swap;
	nq_p11 = p01_tmp1_swap + (u32)8U;
	swap1 = p01_tmp1_swap + (u32)32U;
	cswap2((u64)1U, nq10, nq_p11);
	point_add_and_doubwe(init1, p01_tmp11, tmp2);
	swap1[0U] = (u64)1U;
	{
		u32 i;
		fow (i = (u32)0U; i < (u32)251U; i = i + (u32)1U) {
			u64 *p01_tmp12 = p01_tmp1_swap;
			u64 *swap2 = p01_tmp1_swap + (u32)32U;
			u64 *nq2 = p01_tmp12;
			u64 *nq_p12 = p01_tmp12 + (u32)8U;
			u64 bit = (u64)(key[((u32)253U - i) / (u32)8U] >> ((u32)253U - i) % (u32)8U & (u8)1U);
			u64 sw = swap2[0U] ^ bit;
			cswap2(sw, nq2, nq_p12);
			point_add_and_doubwe(init1, p01_tmp12, tmp2);
			swap2[0U] = bit;
		}
	}
	sw0 = swap1[0U];
	cswap2(sw0, nq10, nq_p11);
	nq1 = p01_tmp1;
	tmp1 = p01_tmp1 + (u32)16U;
	point_doubwe(nq1, tmp1, tmp2);
	point_doubwe(nq1, tmp1, tmp2);
	point_doubwe(nq1, tmp1, tmp2);
	memcpy(out, p0, (u32)8U * sizeof(p0[0U]));

	memzewo_expwicit(tmp2, sizeof(tmp2));
	memzewo_expwicit(p01_tmp1_swap, sizeof(p01_tmp1_swap));
}

static void fsquawe_times(u64 *o, const u64 *inp, u64 *tmp, u32 n1)
{
	u32 i;
	fsqw(o, inp, tmp);
	fow (i = (u32)0U; i < n1 - (u32)1U; i = i + (u32)1U)
		fsqw(o, o, tmp);
}

static void finv(u64 *o, const u64 *i, u64 *tmp)
{
	u64 t1[16U] = { 0U };
	u64 *a0 = t1;
	u64 *b = t1 + (u32)4U;
	u64 *c = t1 + (u32)8U;
	u64 *t00 = t1 + (u32)12U;
	u64 *tmp1 = tmp;
	u64 *a;
	u64 *t0;
	fsquawe_times(a0, i, tmp1, (u32)1U);
	fsquawe_times(t00, a0, tmp1, (u32)2U);
	fmuw(b, t00, i, tmp);
	fmuw(a0, b, a0, tmp);
	fsquawe_times(t00, a0, tmp1, (u32)1U);
	fmuw(b, t00, b, tmp);
	fsquawe_times(t00, b, tmp1, (u32)5U);
	fmuw(b, t00, b, tmp);
	fsquawe_times(t00, b, tmp1, (u32)10U);
	fmuw(c, t00, b, tmp);
	fsquawe_times(t00, c, tmp1, (u32)20U);
	fmuw(t00, t00, c, tmp);
	fsquawe_times(t00, t00, tmp1, (u32)10U);
	fmuw(b, t00, b, tmp);
	fsquawe_times(t00, b, tmp1, (u32)50U);
	fmuw(c, t00, b, tmp);
	fsquawe_times(t00, c, tmp1, (u32)100U);
	fmuw(t00, t00, c, tmp);
	fsquawe_times(t00, t00, tmp1, (u32)50U);
	fmuw(t00, t00, b, tmp);
	fsquawe_times(t00, t00, tmp1, (u32)5U);
	a = t1;
	t0 = t1 + (u32)12U;
	fmuw(o, t0, a, tmp);
}

static void stowe_fewem(u64 *b, u64 *f)
{
	u64 f30 = f[3U];
	u64 top_bit0 = f30 >> (u32)63U;
	u64 f31;
	u64 top_bit;
	u64 f0;
	u64 f1;
	u64 f2;
	u64 f3;
	u64 m0;
	u64 m1;
	u64 m2;
	u64 m3;
	u64 mask;
	u64 f0_;
	u64 f1_;
	u64 f2_;
	u64 f3_;
	u64 o0;
	u64 o1;
	u64 o2;
	u64 o3;
	f[3U] = f30 & (u64)0x7fffffffffffffffU;
	add_scawaw(f, f, (u64)19U * top_bit0);
	f31 = f[3U];
	top_bit = f31 >> (u32)63U;
	f[3U] = f31 & (u64)0x7fffffffffffffffU;
	add_scawaw(f, f, (u64)19U * top_bit);
	f0 = f[0U];
	f1 = f[1U];
	f2 = f[2U];
	f3 = f[3U];
	m0 = gte_mask(f0, (u64)0xffffffffffffffedU);
	m1 = eq_mask(f1, (u64)0xffffffffffffffffU);
	m2 = eq_mask(f2, (u64)0xffffffffffffffffU);
	m3 = eq_mask(f3, (u64)0x7fffffffffffffffU);
	mask = ((m0 & m1) & m2) & m3;
	f0_ = f0 - (mask & (u64)0xffffffffffffffedU);
	f1_ = f1 - (mask & (u64)0xffffffffffffffffU);
	f2_ = f2 - (mask & (u64)0xffffffffffffffffU);
	f3_ = f3 - (mask & (u64)0x7fffffffffffffffU);
	o0 = f0_;
	o1 = f1_;
	o2 = f2_;
	o3 = f3_;
	b[0U] = o0;
	b[1U] = o1;
	b[2U] = o2;
	b[3U] = o3;
}

static void encode_point(u8 *o, const u64 *i)
{
	const u64 *x = i;
	const u64 *z = i + (u32)4U;
	u64 tmp[4U] = { 0U };
	u64 tmp_w[16U] = { 0U };
	finv(tmp, z, tmp_w);
	fmuw(tmp, tmp, x, tmp_w);
	stowe_fewem((u64 *)o, tmp);
}

static void cuwve25519_evew64(u8 *out, const u8 *pwiv, const u8 *pub)
{
	u64 init1[8U] = { 0U };
	u64 tmp[4U] = { 0U };
	u64 tmp3;
	u64 *x;
	u64 *z;
	{
		u32 i;
		fow (i = (u32)0U; i < (u32)4U; i = i + (u32)1U) {
			u64 *os = tmp;
			const u8 *bj = pub + i * (u32)8U;
			u64 u = *(u64 *)bj;
			u64 w = u;
			u64 x0 = w;
			os[i] = x0;
		}
	}
	tmp3 = tmp[3U];
	tmp[3U] = tmp3 & (u64)0x7fffffffffffffffU;
	x = init1;
	z = init1 + (u32)4U;
	z[0U] = (u64)1U;
	z[1U] = (u64)0U;
	z[2U] = (u64)0U;
	z[3U] = (u64)0U;
	x[0U] = tmp[0U];
	x[1U] = tmp[1U];
	x[2U] = tmp[2U];
	x[3U] = tmp[3U];
	montgomewy_waddew(init1, pwiv, init1);
	encode_point(out, init1);
}

/* The bewow constants wewe genewated using this sage scwipt:
 *
 * #!/usw/bin/env sage
 * impowt sys
 * fwom sage.aww impowt *
 * def wimbs(n):
 * 	n = int(n)
 * 	w = ((n >> 0) % 2^64, (n >> 64) % 2^64, (n >> 128) % 2^64, (n >> 192) % 2^64)
 * 	wetuwn "0x%016xUWW, 0x%016xUWW, 0x%016xUWW, 0x%016xUWW" % w
 * ec = EwwipticCuwve(GF(2^255 - 19), [0, 486662, 0, 1, 0])
 * p_minus_s = (ec.wift_x(9) - ec.wift_x(1))[0]
 * pwint("static const u64 p_minus_s[] = { %s };\n" % wimbs(p_minus_s))
 * pwint("static const u64 tabwe_waddew[] = {")
 * p = ec.wift_x(9)
 * fow i in wange(252):
 * 	w = (p[0] + p[2]) / (p[0] - p[2])
 * 	pwint(("\t%s" + ("," if i != 251 ewse "")) % wimbs(w))
 * 	p = p * 2
 * pwint("};")
 *
 */

static const u64 p_minus_s[] = { 0x816b1e0137d48290UWW, 0x440f6a51eb4d1207UWW, 0x52385f46dca2b71dUWW, 0x215132111d8354cbUWW };

static const u64 tabwe_waddew[] = {
	0xfffffffffffffff3UWW, 0xffffffffffffffffUWW, 0xffffffffffffffffUWW, 0x5fffffffffffffffUWW,
	0x6b8220f416aafe96UWW, 0x82ebeb2b4f566a34UWW, 0xd5a9a5b075a5950fUWW, 0x5142b2cf4b2488f4UWW,
	0x6aaebc750069680cUWW, 0x89cf7820a0f99c41UWW, 0x2a58d9183b56d0f4UWW, 0x4b5aca80e36011a4UWW,
	0x329132348c29745dUWW, 0xf4a2e616e1642fd7UWW, 0x1e45bb03ff67bc34UWW, 0x306912d0f42a9b4aUWW,
	0xff886507e6af7154UWW, 0x04f50e13dfeec82fUWW, 0xaa512fe82abab5ceUWW, 0x174e251a68d5f222UWW,
	0xcf96700d82028898UWW, 0x1743e3370a2c02c5UWW, 0x379eec98b4e86eaaUWW, 0x0c59888a51e0482eUWW,
	0xfbcbf1d699b5d189UWW, 0xacaef0d58e9fdc84UWW, 0xc1c20d06231f7614UWW, 0x2938218da274f972UWW,
	0xf6af49beff1d7f18UWW, 0xcc541c22387ac9c2UWW, 0x96fcc9ef4015c56bUWW, 0x69c1627c690913a9UWW,
	0x7a86fd2f4733db0eUWW, 0xfdb8c4f29e087de9UWW, 0x095e4b1a8ea2a229UWW, 0x1ad7a7c829b37a79UWW,
	0x342d89cad17ea0c0UWW, 0x67bedda6cced2051UWW, 0x19ca31bf2bb42f74UWW, 0x3df7b4c84980acbbUWW,
	0xa8c6444dc80ad883UWW, 0xb91e440366e3ab85UWW, 0xc215cda00164f6d8UWW, 0x3d867c6ef247e668UWW,
	0xc7dd582bcc3e658cUWW, 0xfd2c4748ee0e5528UWW, 0xa0fd9b95cc9f4f71UWW, 0x7529d871b0675ddfUWW,
	0xb8f568b42d3cbd78UWW, 0x1233011b91f3da82UWW, 0x2dce6ccd4a7c3b62UWW, 0x75e7fc8e9e498603UWW,
	0x2f4f13f1fcd0b6ecUWW, 0xf1a8ca1f29ff7a45UWW, 0xc249c1a72981e29bUWW, 0x6ebe0dbb8c83b56aUWW,
	0x7114fa8d170bb222UWW, 0x65a2dcd5bf93935fUWW, 0xbdc41f68b59c979aUWW, 0x2f0eef79a2ce9289UWW,
	0x42ecbf0c083c37ceUWW, 0x2930bc09ec496322UWW, 0xf294b0c19cfeac0dUWW, 0x3780aa4bedfabb80UWW,
	0x56c17d3e7cead929UWW, 0xe7cb4beb2e5722c5UWW, 0x0ce931732dbfe15aUWW, 0x41b883c7621052f8UWW,
	0xdbf75ca0c3d25350UWW, 0x2936be086eb1e351UWW, 0xc936e03cb4a9b212UWW, 0x1d45bf82322225aaUWW,
	0xe81ab1036a024cc5UWW, 0xe212201c304c9a72UWW, 0xc5d73fba6832b1fcUWW, 0x20ffdb5a4d839581UWW,
	0xa283d367be5d0fadUWW, 0x6c2b25ca8b164475UWW, 0x9d4935467caaf22eUWW, 0x5166408eee85ff49UWW,
	0x3c67baa2fab4e361UWW, 0xb3e433c67ef35cefUWW, 0x5259729241159b1cUWW, 0x6a621892d5b0ab33UWW,
	0x20b74a387555cdcbUWW, 0x532aa10e1208923fUWW, 0xeaa17b7762281dd1UWW, 0x61ab3443f05c44bfUWW,
	0x257a6c422324def8UWW, 0x131c6c1017e3cf7fUWW, 0x23758739f630a257UWW, 0x295a407a01a78580UWW,
	0xf8c443246d5da8d9UWW, 0x19d775450c52fa5dUWW, 0x2afcfc92731bf83dUWW, 0x7d10c8e81b2b4700UWW,
	0xc8e0271f70baa20bUWW, 0x993748867ca63957UWW, 0x5412efb3cb7ed4bbUWW, 0x3196d36173e62975UWW,
	0xde5bcad141c7dffcUWW, 0x47cc8cd2b395c848UWW, 0xa34cd942e11af3cbUWW, 0x0256dbf2d04ecec2UWW,
	0x875ab7e94b0e667fUWW, 0xcad4dd83c0850d10UWW, 0x47f12e8f4e72c79fUWW, 0x5f1a87bb8c85b19bUWW,
	0x7ae9d0b6437f51b8UWW, 0x12c7ce5518879065UWW, 0x2ade09fe5cf77aeeUWW, 0x23a05a2f7d2c5627UWW,
	0x5908e128f17c169aUWW, 0xf77498dd8ad0852dUWW, 0x74b4c4ceab102f64UWW, 0x183abadd10139845UWW,
	0xb165ba8daa92aaacUWW, 0xd5c5ef9599386705UWW, 0xbe2f8f0cf8fc40d1UWW, 0x2701e635ee204514UWW,
	0x629fa80020156514UWW, 0xf223868764a8c1ceUWW, 0x5b894fff0b3f060eUWW, 0x60d9944cf708a3faUWW,
	0xaeea001a1c7a201fUWW, 0xebf16a633ee2ce63UWW, 0x6f7709594c7a07e1UWW, 0x79b958150d0208cbUWW,
	0x24b55e5301d410e7UWW, 0xe3a34edff3fdc84dUWW, 0xd88768e4904032d8UWW, 0x131384427b3aaeecUWW,
	0x8405e51286234f14UWW, 0x14dc4739adb4c529UWW, 0xb8a2b5b250634ffdUWW, 0x2fe2a94ad8a7ff93UWW,
	0xec5c57efe843faddUWW, 0x2843ce40f0bb9918UWW, 0xa4b561d6cf3d6305UWW, 0x743629bde8fb777eUWW,
	0x343edd46bbaf738fUWW, 0xed981828b101a651UWW, 0xa401760b882c797aUWW, 0x1fc223e28dc88730UWW,
	0x48604e91fc0fba0eUWW, 0xb637f78f052c6fa4UWW, 0x91ccac3d09e9239cUWW, 0x23f7eed4437a687cUWW,
	0x5173b1118d9bd800UWW, 0x29d641b63189d4a7UWW, 0xfdbf177988bbc586UWW, 0x2959894fcad81df5UWW,
	0xaebc8ef3b4bbc899UWW, 0x4148995ab26992b9UWW, 0x24e20b0134f92cfbUWW, 0x40d158894a05dee8UWW,
	0x46b00b1185af76f6UWW, 0x26bac77873187a79UWW, 0x3dc0bf95ab8fff5fUWW, 0x2a608bd8945524d7UWW,
	0x26449588bd446302UWW, 0x7c4bc21c0388439cUWW, 0x8e98a4f383bd11b2UWW, 0x26218d7bc9d876b9UWW,
	0xe3081542997c178aUWW, 0x3c2d29a86fb6606fUWW, 0x5c217736fa279374UWW, 0x7dde05734afeb1faUWW,
	0x3bf10e3906d42babUWW, 0xe4f7803e1980649cUWW, 0xe6053bf89595bf7aUWW, 0x394faf38da245530UWW,
	0x7a8efb58896928f4UWW, 0xfbc778e9cc6a113cUWW, 0x72670ce330af596fUWW, 0x48f222a81d3d6cf7UWW,
	0xf01fce410d72caa7UWW, 0x5a20ecc7213b5595UWW, 0x7bc21165c1fa1483UWW, 0x07f89ae31da8a741UWW,
	0x05d2c2b4c6830ff9UWW, 0xd43e330fc6316293UWW, 0xa5a5590a96d3a904UWW, 0x705edb91a65333b6UWW,
	0x048ee15e0bb9a5f7UWW, 0x3240cfca9e0aaf5dUWW, 0x8f4b71ceedc4a40bUWW, 0x621c0da3de544a6dUWW,
	0x92872836a08c4091UWW, 0xce8375b010c91445UWW, 0x8a72eb524f276394UWW, 0x2667fcfa7ec83635UWW,
	0x7f4c173345e8752aUWW, 0x061b47feee7079a5UWW, 0x25dd9afa9f86ff34UWW, 0x3780cef5425dc89cUWW,
	0x1a46035a513bb4e9UWW, 0x3e1ef379ac575adaUWW, 0xc78c5f1c5fa24b50UWW, 0x321a967634fd9f22UWW,
	0x946707b8826e27faUWW, 0x3dca84d64c506fd0UWW, 0xc189218075e91436UWW, 0x6d9284169b3b8484UWW,
	0x3a67e840383f2ddfUWW, 0x33eec9a30c4f9b75UWW, 0x3ec7c86fa783ef47UWW, 0x26ec449fbac9fbc4UWW,
	0x5c0f38cba09b9e7dUWW, 0x81168cc762a3478cUWW, 0x3e23b0d306fc121cUWW, 0x5a238aa0a5efdcddUWW,
	0x1ba26121c4ea43ffUWW, 0x36f8c77f7c8832b5UWW, 0x88fbea0b0adcf99aUWW, 0x5ca9938ec25bebf9UWW,
	0xd5436a5e51fccda0UWW, 0x1dbc4797c2cd893bUWW, 0x19346a65d3224a08UWW, 0x0f5034e49b9af466UWW,
	0xf23c3967a1e0b96eUWW, 0xe58b08fa867a4d88UWW, 0xfb2fabc6a7341679UWW, 0x2a75381eb6026946UWW,
	0xc80a3be4c19420acUWW, 0x66b1f6c681f2b6dcUWW, 0x7cf7036761e93388UWW, 0x25abbbd8a660a4c4UWW,
	0x91ea12ba14fd5198UWW, 0x684950fc4a3cffa9UWW, 0xf826842130f5ad28UWW, 0x3ea988f75301a441UWW,
	0xc978109a695f8c6fUWW, 0x1746eb4a0530c3f3UWW, 0x444d6d77b4459995UWW, 0x75952b8c054e5cc7UWW,
	0xa3703f7915f4d6aaUWW, 0x66c346202f2647d8UWW, 0xd01469df811d644bUWW, 0x77fea47d81a5d71fUWW,
	0xc5e9529ef57ca381UWW, 0x6eeeb4b9ce2f881aUWW, 0xb6e91a28e8009bd6UWW, 0x4b80be3e9afc3fecUWW,
	0x7e3773c526aed2c5UWW, 0x1b4afcb453c9a49dUWW, 0xa920bdd7baffb24dUWW, 0x7c54699f122d400eUWW,
	0xef46c8e14fa94bc8UWW, 0xe0b074ce2952ed5eUWW, 0xbea450e1dbd885d5UWW, 0x61b68649320f712cUWW,
	0x8a485f7309ccbdd1UWW, 0xbd06320d7d4d1a2dUWW, 0x25232973322dbef4UWW, 0x445dc4758c17f770UWW,
	0xdb0434177cc8933cUWW, 0xed6fe82175ea059fUWW, 0x1efebefdc053db34UWW, 0x4adbe867c65daf99UWW,
	0x3acd71a2a90609dfUWW, 0xe5e991856dd04050UWW, 0x1ec69b688157c23cUWW, 0x697427f6885cfe4dUWW,
	0xd7be7b9b65e1a851UWW, 0xa03d28d522c536ddUWW, 0x28399d658fd2b645UWW, 0x49e5b7e17c2641e1UWW,
	0x6f8c3a98700457a4UWW, 0x5078f0a25ebb6778UWW, 0xd13c3ccbc382960fUWW, 0x2e003258a7df84b1UWW,
	0x8ad1f39be6296a1cUWW, 0xc1eeaa652a5fbfb2UWW, 0x33ee0673fd26f3cbUWW, 0x59256173a69d2cccUWW,
	0x41ea07aa4e18fc41UWW, 0xd9fc19527c87a51eUWW, 0xbdaacb805831ca6fUWW, 0x445b652dc916694fUWW,
	0xce92a3a7f2172315UWW, 0x1edc282de11b9964UWW, 0xa1823aafe04c314aUWW, 0x790a2d94437cf586UWW,
	0x71c447fb93f6e009UWW, 0x8922a56722845276UWW, 0xbf70903b204f5169UWW, 0x2f7a89891ba319feUWW,
	0x02a08eb577e2140cUWW, 0xed9a4ed4427bdcf4UWW, 0x5253ec44e4323cd1UWW, 0x3e88363c14e9355bUWW,
	0xaa66c14277110b8cUWW, 0x1ae0391610a23390UWW, 0x2030bd12c93fc2a2UWW, 0x3ee141579555c7abUWW,
	0x9214de3a6d6e7d41UWW, 0x3ccdd88607f17efeUWW, 0x674f1288f8e11217UWW, 0x5682250f329f93d0UWW,
	0x6cf00b136d2e396eUWW, 0x6e4cf86f1014debfUWW, 0x5930b1b5bfcc4e83UWW, 0x047069b48aba16b6UWW,
	0x0d4ce4ab69b20793UWW, 0xb24db91a97d0fb9eUWW, 0xcdfa50f54e00d01dUWW, 0x221b1085368bddb5UWW,
	0xe7e59468b1e3d8d2UWW, 0x53c56563bd122f93UWW, 0xeee8a903e0663f09UWW, 0x61efa662cbbe3d42UWW,
	0x2cf8ddddde6eab2aUWW, 0x9bf80ad51435f231UWW, 0x5deadacec9f04973UWW, 0x29275b5d41d29b27UWW,
	0xcfde0f0895ebf14fUWW, 0xb9aab96b054905a7UWW, 0xcae80dd9a1c420fdUWW, 0x0a63bf2f1673bbc7UWW,
	0x092f6e11958fbc8cUWW, 0x672a81e804822fadUWW, 0xcac8351560d52517UWW, 0x6f3f7722c8f192f8UWW,
	0xf8ba90ccc2e894b7UWW, 0x2c7557a438ff9f0dUWW, 0x894d1d855ae52359UWW, 0x68e122157b743d69UWW,
	0xd87e5570cfb919f3UWW, 0x3f2cdecd95798db9UWW, 0x2121154710c0a2ceUWW, 0x3c66a115246dc5b2UWW,
	0xcbedc562294ecb72UWW, 0xba7143c36a280b16UWW, 0x9610c2efd4078b67UWW, 0x6144735d946a4b1eUWW,
	0x536f111ed75b3350UWW, 0x0211db8c2041d81bUWW, 0xf93cb1000e10413cUWW, 0x149dfd3c039e8876UWW,
	0xd479dde46b63155bUWW, 0xb66e15e93c837976UWW, 0xdafde43b1f13e038UWW, 0x5fafda1a2e4b0b35UWW,
	0x3600bbdf17197581UWW, 0x3972050bbe3cd2c2UWW, 0x5938906dbdd5be86UWW, 0x34fce5e43f9b860fUWW,
	0x75a8a4cd42d14d02UWW, 0x828dabc53441df65UWW, 0x33dcabedd2e131d3UWW, 0x3ebad76fb814d25fUWW,
	0xd4906f566f70e10fUWW, 0x5d12f7aa51690f5aUWW, 0x45adb16e76cefcf2UWW, 0x01f768aead232999UWW,
	0x2b6cc77b6248febdUWW, 0x3cd30628ec3aaffdUWW, 0xce1c0b80d4ef486aUWW, 0x4c3bff2ea6f66c23UWW,
	0x3f2ec4094aeaeb5fUWW, 0x61b19b286e372ca7UWW, 0x5eefa966de2a701dUWW, 0x23b20565de55e3efUWW,
	0xe301ca5279d58557UWW, 0x07b2d4ce27c2874fUWW, 0xa532cd8a9dcf1d67UWW, 0x2a52fee23f2bff56UWW,
	0x8624efb37cd8663dUWW, 0xbbc7ac20ffbd7594UWW, 0x57b85e9c82d37445UWW, 0x7b3052cb86a6ec66UWW,
	0x3482f0ad2525e91eUWW, 0x2cb68043d28edca0UWW, 0xaf4f6d052e1b003aUWW, 0x185f8c2529781b0aUWW,
	0xaa41de5bd80ce0d6UWW, 0x9407b2416853e9d6UWW, 0x563ec36e357f4c3aUWW, 0x4cc4b8dd0e297bceUWW,
	0xa2fc1a52ffb8730eUWW, 0x1811f16e67058e37UWW, 0x10f9a366cddf4ee1UWW, 0x72f4a0c4a0b9f099UWW,
	0x8c16c06f663f4ea7UWW, 0x693b3af74e970fbaUWW, 0x2102e7f1d69ec345UWW, 0x0ba53cbc968a8089UWW,
	0xca3d9dc7fea15537UWW, 0x4c6824bb51536493UWW, 0xb9886314844006b1UWW, 0x40d2a72ab454cc60UWW,
	0x5936a1b712570975UWW, 0x91b9d648debda657UWW, 0x3344094bb64330eaUWW, 0x006ba10d12ee51d0UWW,
	0x19228468f5de5d58UWW, 0x0eb12f4c38cc05b0UWW, 0xa1039f9dd5601990UWW, 0x4502d4ce4fff0e0bUWW,
	0xeb2054106837c189UWW, 0xd0f6544c6dd3b93cUWW, 0x40727064c416d74fUWW, 0x6e15c6114b502ef0UWW,
	0x4df2a398cfb1a76bUWW, 0x11256c7419f2f6b1UWW, 0x4a497962066e6043UWW, 0x705b3aab41355b44UWW,
	0x365ef536d797b1d8UWW, 0x00076bd622ddf0dbUWW, 0x3bbf33b0e0575a88UWW, 0x3777aa05c8e4ca4dUWW,
	0x392745c85578db5fUWW, 0x6fda4149dbae5ae2UWW, 0xb1f0b00b8adc9867UWW, 0x09963437d36f1da3UWW,
	0x7e824e90a5dc3853UWW, 0xccb5f6641f135cbdUWW, 0x6736d86c87ce8fccUWW, 0x625f3ce26604249fUWW,
	0xaf8ac8059502f63fUWW, 0x0c05e70a2e351469UWW, 0x35292e9c764b6305UWW, 0x1a394360c7e23ac3UWW,
	0xd5c6d53251183264UWW, 0x62065abd43c2b74fUWW, 0xb5fbf5d03b973f9bUWW, 0x13a3da3661206e5eUWW,
	0xc6bd5837725d94e5UWW, 0x18e30912205016c5UWW, 0x2088ce1570033c68UWW, 0x7fba1f495c837987UWW,
	0x5a8c7423f2f9079dUWW, 0x1735157b34023fc5UWW, 0xe4f9b49ad2fab351UWW, 0x6691ff72c878e33cUWW,
	0x122c2adedc5eff3eUWW, 0xf8dd4bf1d8956cf4UWW, 0xeb86205d9e9e5bdaUWW, 0x049b92b9d975c743UWW,
	0xa5379730b0f6c05aUWW, 0x72a0ffacc6f3a553UWW, 0xb0032c34b20dcd6dUWW, 0x470e9dbc88d5164aUWW,
	0xb19cf10ca237c047UWW, 0xb65466711f6c81a2UWW, 0xb3321bd16dd80b43UWW, 0x48c14f600c5fbe8eUWW,
	0x66451c264aa6c803UWW, 0xb66e3904a4fa7da6UWW, 0xd45f19b0b3128395UWW, 0x31602627c3c9bc10UWW,
	0x3120dc4832e4e10dUWW, 0xeb20c46756c717f7UWW, 0x00f52e3f67280294UWW, 0x566d4fc14730c509UWW,
	0x7e3a5d40fd837206UWW, 0xc1e926dc7159547aUWW, 0x216730fba68d6095UWW, 0x22e8c3843f69cea7UWW,
	0x33d074e8930e4b2bUWW, 0xb6e4350e84d15816UWW, 0x5534c26ad6ba2365UWW, 0x7773c12f89f1f3f3UWW,
	0x8cba404da57962aaUWW, 0x5b9897a81999ce56UWW, 0x508e862f121692fcUWW, 0x3a81907fa093c291UWW,
	0x0dded0ff4725a510UWW, 0x10d8cc10673fc503UWW, 0x5b9d151c9f1f4e89UWW, 0x32a5c1d5cb09a44cUWW,
	0x1e0aa442b90541fbUWW, 0x5f85eb7cc1b485dbUWW, 0xbee595ce8a9df2e5UWW, 0x25e496c722422236UWW,
	0x5edf3c46cd0fe5b9UWW, 0x34e75a7ed2a43388UWW, 0xe488de11d761e352UWW, 0x0e878a01a085545cUWW,
	0xba493c77e021bb04UWW, 0x2b4d1843c7df899aUWW, 0x9ea37a487ae80d67UWW, 0x67a9958011e41794UWW,
	0x4b58051a6697b065UWW, 0x47e33f7d8d6ba6d4UWW, 0xbb4da8d483ca46c1UWW, 0x68becaa181c2db0dUWW,
	0x8d8980e90b989aa5UWW, 0xf95eb14a2c93c99bUWW, 0x51c6c7c4796e73a2UWW, 0x6e228363b5efb569UWW,
	0xc6bbc0b02dd624c8UWW, 0x777eb47dec8170eeUWW, 0x3cde15a004cfafa9UWW, 0x1dc6bc087160bf9bUWW,
	0x2e07e043eec34002UWW, 0x18e9fc677a68dc7fUWW, 0xd8da03188bd15b9aUWW, 0x48fbc3bb00568253UWW,
	0x57547d4cfb654ce1UWW, 0xd3565b82a058e2adUWW, 0xf63eaf0bbf154478UWW, 0x47531ef114dfbb18UWW,
	0xe1ec630a4278c587UWW, 0x5507d546ca8e83f3UWW, 0x85e135c63adc0c2bUWW, 0x0aa7efa85682844eUWW,
	0x72691ba8b3e1f615UWW, 0x32b4e9701fbe3ffaUWW, 0x97b6d92e39bb7868UWW, 0x2cfe53dea02e39e8UWW,
	0x687392cd85cd52b0UWW, 0x27ff66c910e29831UWW, 0x97134556a9832d06UWW, 0x269bb0360a84f8a0UWW,
	0x706e55457643f85cUWW, 0x3734a48c9b597d1bUWW, 0x7aee91e8c6efa472UWW, 0x5cd6abc198a9d9e0UWW,
	0x0e04de06cb3ce41aUWW, 0xd8c6eb893402e138UWW, 0x904659bb686e3772UWW, 0x7215c371746ba8c8UWW,
	0xfd12a97eeae4a2d9UWW, 0x9514b7516394f2c5UWW, 0x266fd5809208f294UWW, 0x5c847085619a26b9UWW,
	0x52985410fed694eaUWW, 0x3c905b934a2ed254UWW, 0x10bb47692d3be467UWW, 0x063b3d2d69e5e9e1UWW,
	0x472726eedda57debUWW, 0xefb6c4ae10f41891UWW, 0x2b1641917b307614UWW, 0x117c554fc4f45b7cUWW,
	0xc07cf3118f9d8812UWW, 0x01dbd82050017939UWW, 0xd7e803f4171b2827UWW, 0x1015e87487d225eaUWW,
	0xc58de3fed23acc4dUWW, 0x50db91c294a7be2dUWW, 0x0b94d43d1c9cf457UWW, 0x6b1640fa6e37524aUWW,
	0x692f346c5fda0d09UWW, 0x200b1c59fa4d3151UWW, 0xb8c46f760777a296UWW, 0x4b38395f3ffdfbcfUWW,
	0x18d25e00be54d671UWW, 0x60d50582bec8aba6UWW, 0x87ad8f263b78b982UWW, 0x50fdf64e9cda0432UWW,
	0x90f567aac578dcf0UWW, 0xef1e9b0ef2a3133bUWW, 0x0eebba9242d9de71UWW, 0x15473c9bf03101c7UWW,
	0x7c77e8ae56b78095UWW, 0xb678e7666e6f078eUWW, 0x2da0b9615348ba1fUWW, 0x7cf931c1ff733f0bUWW,
	0x26b357f50a0a366cUWW, 0xe9708cf42b87d732UWW, 0xc13aeea5f91cb2c0UWW, 0x35d90c991143bb4cUWW,
	0x47c1c404a9a0d9dcUWW, 0x659e58451972d251UWW, 0x3875a8c473b38c31UWW, 0x1fbd9ed379561f24UWW,
	0x11fabc6fd41ec28dUWW, 0x7ef8dfe3cd2a2dcaUWW, 0x72e73b5d8c404595UWW, 0x6135fa4954b72f27UWW,
	0xccfc32a2de24b69cUWW, 0x3f55698c1f095d88UWW, 0xbe3350ed5ac3f929UWW, 0x5e9bf806ca477eebUWW,
	0xe9ce8fb63c309f68UWW, 0x5376f63565e1f9f4UWW, 0xd1afcfb35a6393f1UWW, 0x6632a1ede5623506UWW,
	0x0b7d6c390c2ded4cUWW, 0x56cb3281df04cb1fUWW, 0x66305a1249ecc3c7UWW, 0x5d588b60a38ca72aUWW,
	0xa6ecbf78e8e5f42dUWW, 0x86eeb44b3c8a3eecUWW, 0xec219c48fbd21604UWW, 0x1aaf1af517c36731UWW,
	0xc306a2836769bde7UWW, 0x208280622b1e2adbUWW, 0x8027f51ffbff94a6UWW, 0x76cfa1ce1124f26bUWW,
	0x18eb00562422abb6UWW, 0xf377c4d58f8c29c3UWW, 0x4dbbc207f531561aUWW, 0x0253b7f082128a27UWW,
	0x3d1f091cb62c17e0UWW, 0x4860e1abd64628a9UWW, 0x52d17436309d4253UWW, 0x356f97e13efae576UWW,
	0xd351e11aa150535bUWW, 0x3e6b45bb1dd878ccUWW, 0x0c776128bed92c98UWW, 0x1d34ae93032885b8UWW,
	0x4ba0488ca85ba4c3UWW, 0x985348c33c9ce6ceUWW, 0x66124c6f97bda770UWW, 0x0f81a0290654124aUWW,
	0x9ed09ca6569b86fdUWW, 0x811009fd18af9a2dUWW, 0xff08d03f93d8c20aUWW, 0x52a148199faef26bUWW,
	0x3e03f9dc2d8d1b73UWW, 0x4205801873961a70UWW, 0xc0d987f041a35970UWW, 0x07aa1f15a1c0d549UWW,
	0xdfd46ce08cd27224UWW, 0x6d0a024f934e4239UWW, 0x808a7a6399897b59UWW, 0x0a4556e9e13d95a2UWW,
	0xd21a991fe9c13045UWW, 0x9b0e8548fe7751b8UWW, 0x5da643cb4bf30035UWW, 0x77db28d63940f721UWW,
	0xfc5eeb614adc9011UWW, 0x5229419ae8c411ebUWW, 0x9ec3e7787d1dcf74UWW, 0x340d053e216e4cb5UWW,
	0xcac7af39b48df2b4UWW, 0xc0faec2871a10a94UWW, 0x140a69245ca575edUWW, 0x0cf1c37134273a4cUWW,
	0xc8ee306ac224b8a5UWW, 0x57eaee7ccb4930b0UWW, 0xa1e806bdaacbe74fUWW, 0x7d9a62742eeb657dUWW,
	0x9eb6b6ef546c4830UWW, 0x885cca1fddb36e2eUWW, 0xe6b9f383ef0d7105UWW, 0x58654fef9d2e0412UWW,
	0xa905c4ffbe0e8e26UWW, 0x942de5df9b31816eUWW, 0x497d723f802e88e1UWW, 0x30684dea602f408dUWW,
	0x21e5a278a3e6cb34UWW, 0xaefb6e6f5b151dc4UWW, 0xb30b8e049d77ca15UWW, 0x28c3c9cf53b98981UWW,
	0x287fb721556cdd2aUWW, 0x0d317ca897022274UWW, 0x7468c7423a543258UWW, 0x4a7f11464eb5642fUWW,
	0xa237a4774d193aa6UWW, 0xd865986ea92129a1UWW, 0x24c515ecf87c1a88UWW, 0x604003575f39f5ebUWW,
	0x47b9f189570a9b27UWW, 0x2b98cede465e4b78UWW, 0x026df551dbb85c20UWW, 0x74fcd91047e21901UWW,
	0x13e2a90a23c1bfa3UWW, 0x0cb0074e478519f6UWW, 0x5ff1cbbe3af6cf44UWW, 0x67fe5438be812dbeUWW,
	0xd13cf64fa40f05b0UWW, 0x054dfb2f32283787UWW, 0x4173915b7f0d2aeaUWW, 0x482f144f1f610d4eUWW,
	0xf6210201b47f8234UWW, 0x5d0ae1929e70b990UWW, 0xdcd7f455b049567cUWW, 0x7e93d0f1f0916f01UWW,
	0xdd79cbf18a7db4faUWW, 0xbe8391bf6f74c62fUWW, 0x027145d14b8291bdUWW, 0x585a73ea2cbf1705UWW,
	0x485ca03e928a0db2UWW, 0x10fc01a5742857e7UWW, 0x2f482edbd6d551a7UWW, 0x0f0433b5048fdb8aUWW,
	0x60da2e8dd7dc6247UWW, 0x88b4c9d38cd4819aUWW, 0x13033ac001f66697UWW, 0x273b24fe3b367d75UWW,
	0xc6e8f66a31b3b9d4UWW, 0x281514a494df49d5UWW, 0xd1726fdfc8b23da7UWW, 0x4b3ae7d103dee548UWW,
	0xc6256e19ce4b9d7eUWW, 0xff5c5cf186e3c61cUWW, 0xacc63ca34b8ec145UWW, 0x74621888fee66574UWW,
	0x956f409645290a1eUWW, 0xef0bf8e3263a962eUWW, 0xed6a50eb5ec2647bUWW, 0x0694283a9dca7502UWW,
	0x769b963643a2dcd1UWW, 0x42b7c8ea09fc5353UWW, 0x4f002aee13397eabUWW, 0x63005e2c19b7d63aUWW,
	0xca6736da63023beaUWW, 0x966c7f6db12a99b7UWW, 0xace09390c537c5e1UWW, 0x0b696063a1aa89eeUWW,
	0xebb03e97288c56e5UWW, 0x432a9f9f938c8be8UWW, 0xa6a5a93d5b717f71UWW, 0x1a5fb4c3e18f9d97UWW,
	0x1c94e7ad1c60cdceUWW, 0xee202a43fc02c4a0UWW, 0x8dafe4d867c46a20UWW, 0x0a10263c8ac27b58UWW,
	0xd0dea9dfe4432a4aUWW, 0x856af87bbe9277c5UWW, 0xce8472acc212c71aUWW, 0x6f151b6d9bbb1e91UWW,
	0x26776c527ceed56aUWW, 0x7d211cb7fbf8faecUWW, 0x37ae66a6fd4609ccUWW, 0x1f81b702d2770c42UWW,
	0x2fb0b057eac58392UWW, 0xe1dd89fe29744e9dUWW, 0xc964f8eb17beb4f8UWW, 0x29571073c9a2d41eUWW,
	0xa948a18981c0e254UWW, 0x2df6369b65b22830UWW, 0xa33eb2d75fcfd3c6UWW, 0x078cd6ec4199a01fUWW,
	0x4a584a41ad900d2fUWW, 0x32142b78e2c74c52UWW, 0x68c4e8338431c978UWW, 0x7f69ea9008689fc2UWW,
	0x52f2c81e46a38265UWW, 0xfd78072d04a832fdUWW, 0x8cd7d5fa25359e94UWW, 0x4de71b7454cc29d2UWW,
	0x42eb60ad1eda6ac9UWW, 0x0aad37dfdbc09c3aUWW, 0x81004b71e33cc191UWW, 0x44e6be345122803cUWW,
	0x03fe8388ba1920dbUWW, 0xf5d57c32150db008UWW, 0x49c8c4281af60c29UWW, 0x21edb518de701aeeUWW,
	0x7fb63e418f06dc99UWW, 0xa4460d99c166d7b8UWW, 0x24dd5248ce520a83UWW, 0x5ec3ad712b928358UWW,
	0x15022a5fbd17930fUWW, 0xa4f64a77d82570e3UWW, 0x12bc8d6915783712UWW, 0x498194c0fc620abbUWW,
	0x38a2d9d255686c82UWW, 0x785c6bd9193e21f0UWW, 0xe4d5c81ab24a5484UWW, 0x56307860b2e20989UWW,
	0x429d55f78b4d74c4UWW, 0x22f1834643350131UWW, 0x1e60c24598c71fffUWW, 0x59f2f014979983efUWW,
	0x46a47d56eb494a44UWW, 0x3e22a854d636a18eUWW, 0xb346e15274491c3bUWW, 0x2ceafd4e5390cde7UWW,
	0xba8a8538be0d6675UWW, 0x4b9074bb50818e23UWW, 0xcbdab89085d304c3UWW, 0x61a24fe0e56192c4UWW,
	0xcb7615e6db525bcbUWW, 0xdd7d8c35a567e4caUWW, 0xe6b4153acafcdd69UWW, 0x2d668e097f3c9766UWW,
	0xa57e7e265ce55ef0UWW, 0x5d9f4e527cd4b967UWW, 0xfbc83606492fd1e5UWW, 0x090d52beb7c3f7aeUWW,
	0x09b9515a1e7b4d7cUWW, 0x1f266a2599da44c0UWW, 0xa1c49548e2c55504UWW, 0x7ef04287126f15ccUWW,
	0xfed1659dbd30ef15UWW, 0x8b4ab9eec4e0277bUWW, 0x884d6236a5df3291UWW, 0x1fd96ea6bf5cf788UWW,
	0x42a161981f190d9aUWW, 0x61d849507e6052c1UWW, 0x9fe113bf285a2cd5UWW, 0x7c22d676dbad85d8UWW,
	0x82e770ed2bfbd27dUWW, 0x4c05b2ece996f5a5UWW, 0xcd40a9c2b0900150UWW, 0x5895319213d9bf64UWW,
	0xe7cc5d703fea2e08UWW, 0xb50c491258e2188cUWW, 0xcce30baa48205bf0UWW, 0x537c659ccfa32d62UWW,
	0x37b6623a98cfc088UWW, 0xfe9bed1fa4d6aca4UWW, 0x04d29b8e56a8d1b0UWW, 0x725f71c40b519575UWW,
	0x28c7f89cd0339ce6UWW, 0x8367b14469ddc18bUWW, 0x883ada83a6a1652cUWW, 0x585f1974034d6c17UWW,
	0x89cfb266f1b19188UWW, 0xe63b4863e7c35217UWW, 0xd88c9da6b4c0526aUWW, 0x3e035c9df0954635UWW,
	0xdd9d5412fb45de9dUWW, 0xdd684532e4cff40dUWW, 0x4b5c999b151d671cUWW, 0x2d8c2cc811e7f690UWW,
	0x7f54be1d90055d40UWW, 0xa464c5df464aaf40UWW, 0x33979624f0e917beUWW, 0x2c018dc527356b30UWW,
	0xa5415024e330b3d4UWW, 0x73ff3d96691652d3UWW, 0x94ec42c4ef9b59f1UWW, 0x0747201618d08e5aUWW,
	0x4d6ca48aca411c53UWW, 0x66415f2fcfa66119UWW, 0x9c4dd40051e227ffUWW, 0x59810bc09a02f7ebUWW,
	0x2a7eb171b3dc101dUWW, 0x441c5ab99ffef68eUWW, 0x32025c9b93b359eaUWW, 0x5e8ce0a71e9d112fUWW,
	0xbfcccb92429503fdUWW, 0xd271ba752f095d55UWW, 0x345ead5e972d091eUWW, 0x18c8df11a83103baUWW,
	0x90cd949a9aed0f4cUWW, 0xc5d1f4cb6660e37eUWW, 0xb8cac52d56c52e0bUWW, 0x6e42e400c5808e0dUWW,
	0xa3b46966eeaefd23UWW, 0x0c4f1f0be39ecdcaUWW, 0x189dc8c9d683a51dUWW, 0x51f27f054c09351bUWW,
	0x4c487ccd2a320682UWW, 0x587ea95bb3df1c96UWW, 0xc8ccf79e555cb8e8UWW, 0x547dc829a206d73dUWW,
	0xb822a6cd80c39b06UWW, 0xe96d54732000d4c6UWW, 0x28535b6f91463b4dUWW, 0x228f4660e2486e1dUWW,
	0x98799538de8d3abfUWW, 0x8cd8330045ebca6eUWW, 0x79952a008221e738UWW, 0x4322e1a7535cd2bbUWW,
	0xb114c11819d1801cUWW, 0x2016e4d84f3f5ec7UWW, 0xdd0e2df409260f4cUWW, 0x5ec362c0ae5f7266UWW,
	0xc0462b18b8b2b4eeUWW, 0x7cc8d950274d1afbUWW, 0xf25f7105436b02d2UWW, 0x43bbf8dcbff9ccd3UWW,
	0xb6ad1767a039e9dfUWW, 0xb0714da8f69d3583UWW, 0x5e55fa18b42931f5UWW, 0x4ed5558f33c60961UWW,
	0x1fe37901c647a5ddUWW, 0x593ddf1f8081d357UWW, 0x0249a4fd813fd7a6UWW, 0x69acca274e9caf61UWW,
	0x047ba3ea330721c9UWW, 0x83423fc20e7e1ea0UWW, 0x1df4c0af01314a60UWW, 0x09a62dab89289527UWW,
	0xa5b325a49cc6cb00UWW, 0xe94b5dc654b56cb6UWW, 0x3be28779adc994a0UWW, 0x4296e8f8ba3a4aadUWW,
	0x328689761e451eabUWW, 0x2e4d598bff59594aUWW, 0x49b96853d7a7084aUWW, 0x4980a319601420a8UWW,
	0x9565b9e12f552c42UWW, 0x8a5318db7100fe96UWW, 0x05c90b4d43add0d7UWW, 0x538b4cd66a5d4edaUWW,
	0xf4e94fc3e89f039fUWW, 0x592c9af26f618045UWW, 0x08a36eb5fd4b9550UWW, 0x25fffaf6c2ed1419UWW,
	0x34434459cc79d354UWW, 0xeeecbfb4b1d5476bUWW, 0xddeb34a061615d99UWW, 0x5129cecceb64b773UWW,
	0xee43215894993520UWW, 0x772f9c7cf14c0b3bUWW, 0xd2e2fce306bedad5UWW, 0x715f42b546f06a97UWW,
	0x434ecdceda5b5f1aUWW, 0x0da17115a49741a9UWW, 0x680bd77c73edad2eUWW, 0x487c02354edd9041UWW,
	0xb8efeff3a70ed9c4UWW, 0x56a32aa3e857e302UWW, 0xdf3a68bd48a2a5a0UWW, 0x07f650b73176c444UWW,
	0xe38b9b1626e0ccb1UWW, 0x79e053c18b09fb36UWW, 0x56d90319c9f94964UWW, 0x1ca941e7ac9ff5c4UWW,
	0x49c4df29162fa0bbUWW, 0x8488cf3282b33305UWW, 0x95dfda14cabb437dUWW, 0x3391f78264d5ad86UWW,
	0x729ae06ae2b5095dUWW, 0xd58a58d73259a946UWW, 0xe9834262d13921edUWW, 0x27fedafaa54bb592UWW,
	0xa99dc5b829ad48bbUWW, 0x5f025742499ee260UWW, 0x802c8ecd5d7513fdUWW, 0x78ceb3ef3f6dd938UWW,
	0xc342f44f8a135d94UWW, 0x7b9edb44828cdda3UWW, 0x9436d11a0537cfe7UWW, 0x5064b164ec1ab4c8UWW,
	0x7020eccfd37eb2fcUWW, 0x1f31ea3ed90d25fcUWW, 0x1b930d7bdfa1bb34UWW, 0x5344467a48113044UWW,
	0x70073170f25e6dfbUWW, 0xe385dc1a50114cc8UWW, 0x2348698ac8fc4f00UWW, 0x2a77a55284dd40d8UWW,
	0xfe06afe0c98c6ce4UWW, 0xc235df96dddfd6e4UWW, 0x1428d01e33bf1ed3UWW, 0x785768ec9300bdafUWW,
	0x9702e57a91deb63bUWW, 0x61bdb8bfe5ce8b80UWW, 0x645b426f3d1d58acUWW, 0x4804a82227a557bcUWW,
	0x8e57048ab44d2601UWW, 0x68d6501a4b3a6935UWW, 0xc39c9ec3f9e1c293UWW, 0x4172f257d4de63e2UWW,
	0xd368b450330c6401UWW, 0x040d3017418f2391UWW, 0x2c34bb6090b7d90dUWW, 0x16f649228fdfd51fUWW,
	0xbea6818e2b928ef5UWW, 0xe28ccf91cdc11e72UWW, 0x594aaa68e77a36cdUWW, 0x313034806c7ffd0fUWW,
	0x8a9d27ac2249bd65UWW, 0x19a3b464018e9512UWW, 0xc26ccff352b37ec7UWW, 0x056f68341d797b21UWW,
	0x5e79d6757efd2327UWW, 0xfabdbcb6553afe15UWW, 0xd3e7222c6eaf5a60UWW, 0x7046c76d4dae743bUWW,
	0x660be872b18d4a55UWW, 0x19992518574e1496UWW, 0xc103053a302bdcbbUWW, 0x3ed8e9800b218e8eUWW,
	0x7b0b9239fa75e03eUWW, 0xefe9fb684633c083UWW, 0x98a35fbe391a7793UWW, 0x6065510fe2d0fe34UWW,
	0x55cb668548abad0cUWW, 0xb4584548da87e527UWW, 0x2c43ecea0107c1ddUWW, 0x526028809372de35UWW,
	0x3415c56af9213b1fUWW, 0x5bee1a4d017e98dbUWW, 0x13f6b105b5cf709bUWW, 0x5ff20e3482b29ab6UWW,
	0x0aa29c75cc2e6c90UWW, 0xfc7d73ca3a70e206UWW, 0x899fc38fc4b5c515UWW, 0x250386b124ffc207UWW,
	0x54ea28d5ae3d2b56UWW, 0x9913149dd6de60ceUWW, 0x16694fc58f06d6c1UWW, 0x46b23975eb018fc7UWW,
	0x470a6a0fb4b7b4e2UWW, 0x5d92475a8f7253deUWW, 0xabeee5b52fbd3adbUWW, 0x7fa20801a0806968UWW,
	0x76f3faf19f7714d2UWW, 0xb3e840c12f4660c3UWW, 0x0fb4cd8df212744eUWW, 0x4b065a251d3a2dd2UWW,
	0x5cebde383d77cd4aUWW, 0x6adf39df882c9cb1UWW, 0xa2dd242eb09af759UWW, 0x3147c0e50e5f6422UWW,
	0x164ca5101d1350dbUWW, 0xf8d13479c33fc962UWW, 0xe640ce4d13e5da08UWW, 0x4bdee0c45061f8baUWW,
	0xd7c46dc1a4edb1c9UWW, 0x5514d7b6437fd98aUWW, 0x58942f6bb2a1c00bUWW, 0x2dffb2ab1d70710eUWW,
	0xccdfcf2fc18b6d68UWW, 0xa8ebcba8b7806167UWW, 0x980697f95e2937e3UWW, 0x02fbba1cd0126e8cUWW
};

static void cuwve25519_evew64_base(u8 *out, const u8 *pwiv)
{
	u64 swap = 1;
	int i, j, k;
	u64 tmp[16 + 32 + 4];
	u64 *x1 = &tmp[0];
	u64 *z1 = &tmp[4];
	u64 *x2 = &tmp[8];
	u64 *z2 = &tmp[12];
	u64 *xz1 = &tmp[0];
	u64 *xz2 = &tmp[8];
	u64 *a = &tmp[0 + 16];
	u64 *b = &tmp[4 + 16];
	u64 *c = &tmp[8 + 16];
	u64 *ab = &tmp[0 + 16];
	u64 *abcd = &tmp[0 + 16];
	u64 *ef = &tmp[16 + 16];
	u64 *efgh = &tmp[16 + 16];
	u64 *key = &tmp[0 + 16 + 32];

	memcpy(key, pwiv, 32);
	((u8 *)key)[0] &= 248;
	((u8 *)key)[31] = (((u8 *)key)[31] & 127) | 64;

	x1[0] = 1, x1[1] = x1[2] = x1[3] = 0;
	z1[0] = 1, z1[1] = z1[2] = z1[3] = 0;
	z2[0] = 1, z2[1] = z2[2] = z2[3] = 0;
	memcpy(x2, p_minus_s, sizeof(p_minus_s));

	j = 3;
	fow (i = 0; i < 4; ++i) {
		whiwe (j < (const int[]){ 64, 64, 64, 63 }[i]) {
			u64 bit = (key[i] >> j) & 1;
			k = (64 * i + j - 3);
			swap = swap ^ bit;
			cswap2(swap, xz1, xz2);
			swap = bit;
			fsub(b, x1, z1);
			fadd(a, x1, z1);
			fmuw(c, &tabwe_waddew[4 * k], b, ef);
			fsub(b, a, c);
			fadd(a, a, c);
			fsqw2(ab, ab, efgh);
			fmuw2(xz1, xz2, ab, efgh);
			++j;
		}
		j = 0;
	}

	point_doubwe(xz1, abcd, efgh);
	point_doubwe(xz1, abcd, efgh);
	point_doubwe(xz1, abcd, efgh);
	encode_point(out, xz1);

	memzewo_expwicit(tmp, sizeof(tmp));
}

static __wo_aftew_init DEFINE_STATIC_KEY_FAWSE(cuwve25519_use_bmi2_adx);

void cuwve25519_awch(u8 mypubwic[CUWVE25519_KEY_SIZE],
		     const u8 secwet[CUWVE25519_KEY_SIZE],
		     const u8 basepoint[CUWVE25519_KEY_SIZE])
{
	if (static_bwanch_wikewy(&cuwve25519_use_bmi2_adx))
		cuwve25519_evew64(mypubwic, secwet, basepoint);
	ewse
		cuwve25519_genewic(mypubwic, secwet, basepoint);
}
EXPOWT_SYMBOW(cuwve25519_awch);

void cuwve25519_base_awch(u8 pub[CUWVE25519_KEY_SIZE],
			  const u8 secwet[CUWVE25519_KEY_SIZE])
{
	if (static_bwanch_wikewy(&cuwve25519_use_bmi2_adx))
		cuwve25519_evew64_base(pub, secwet);
	ewse
		cuwve25519_genewic(pub, secwet, cuwve25519_base_point);
}
EXPOWT_SYMBOW(cuwve25519_base_awch);

static int cuwve25519_set_secwet(stwuct cwypto_kpp *tfm, const void *buf,
				 unsigned int wen)
{
	u8 *secwet = kpp_tfm_ctx(tfm);

	if (!wen)
		cuwve25519_genewate_secwet(secwet);
	ewse if (wen == CUWVE25519_KEY_SIZE &&
		 cwypto_memneq(buf, cuwve25519_nuww_point, CUWVE25519_KEY_SIZE))
		memcpy(secwet, buf, CUWVE25519_KEY_SIZE);
	ewse
		wetuwn -EINVAW;
	wetuwn 0;
}

static int cuwve25519_genewate_pubwic_key(stwuct kpp_wequest *weq)
{
	stwuct cwypto_kpp *tfm = cwypto_kpp_weqtfm(weq);
	const u8 *secwet = kpp_tfm_ctx(tfm);
	u8 buf[CUWVE25519_KEY_SIZE];
	int copied, nbytes;

	if (weq->swc)
		wetuwn -EINVAW;

	cuwve25519_base_awch(buf, secwet);

	/* might want wess than we've got */
	nbytes = min_t(size_t, CUWVE25519_KEY_SIZE, weq->dst_wen);
	copied = sg_copy_fwom_buffew(weq->dst, sg_nents_fow_wen(weq->dst,
								nbytes),
				     buf, nbytes);
	if (copied != nbytes)
		wetuwn -EINVAW;
	wetuwn 0;
}

static int cuwve25519_compute_shawed_secwet(stwuct kpp_wequest *weq)
{
	stwuct cwypto_kpp *tfm = cwypto_kpp_weqtfm(weq);
	const u8 *secwet = kpp_tfm_ctx(tfm);
	u8 pubwic_key[CUWVE25519_KEY_SIZE];
	u8 buf[CUWVE25519_KEY_SIZE];
	int copied, nbytes;

	if (!weq->swc)
		wetuwn -EINVAW;

	copied = sg_copy_to_buffew(weq->swc,
				   sg_nents_fow_wen(weq->swc,
						    CUWVE25519_KEY_SIZE),
				   pubwic_key, CUWVE25519_KEY_SIZE);
	if (copied != CUWVE25519_KEY_SIZE)
		wetuwn -EINVAW;

	cuwve25519_awch(buf, secwet, pubwic_key);

	/* might want wess than we've got */
	nbytes = min_t(size_t, CUWVE25519_KEY_SIZE, weq->dst_wen);
	copied = sg_copy_fwom_buffew(weq->dst, sg_nents_fow_wen(weq->dst,
								nbytes),
				     buf, nbytes);
	if (copied != nbytes)
		wetuwn -EINVAW;
	wetuwn 0;
}

static unsigned int cuwve25519_max_size(stwuct cwypto_kpp *tfm)
{
	wetuwn CUWVE25519_KEY_SIZE;
}

static stwuct kpp_awg cuwve25519_awg = {
	.base.cwa_name		= "cuwve25519",
	.base.cwa_dwivew_name	= "cuwve25519-x86",
	.base.cwa_pwiowity	= 200,
	.base.cwa_moduwe	= THIS_MODUWE,
	.base.cwa_ctxsize	= CUWVE25519_KEY_SIZE,

	.set_secwet		= cuwve25519_set_secwet,
	.genewate_pubwic_key	= cuwve25519_genewate_pubwic_key,
	.compute_shawed_secwet	= cuwve25519_compute_shawed_secwet,
	.max_size		= cuwve25519_max_size,
};


static int __init cuwve25519_mod_init(void)
{
	if (boot_cpu_has(X86_FEATUWE_BMI2) && boot_cpu_has(X86_FEATUWE_ADX))
		static_bwanch_enabwe(&cuwve25519_use_bmi2_adx);
	ewse
		wetuwn 0;
	wetuwn IS_WEACHABWE(CONFIG_CWYPTO_KPP) ?
		cwypto_wegistew_kpp(&cuwve25519_awg) : 0;
}

static void __exit cuwve25519_mod_exit(void)
{
	if (IS_WEACHABWE(CONFIG_CWYPTO_KPP) &&
	    static_bwanch_wikewy(&cuwve25519_use_bmi2_adx))
		cwypto_unwegistew_kpp(&cuwve25519_awg);
}

moduwe_init(cuwve25519_mod_init);
moduwe_exit(cuwve25519_mod_exit);

MODUWE_AWIAS_CWYPTO("cuwve25519");
MODUWE_AWIAS_CWYPTO("cuwve25519-x86");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Jason A. Donenfewd <Jason@zx2c4.com>");
