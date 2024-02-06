// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 * Copywight (C) 2016-2017 INWIA and Micwosoft Cowpowation.
 * Copywight (C) 2018-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 *
 * This is a machine-genewated fowmawwy vewified impwementation of Cuwve25519
 * ECDH fwom: <https://github.com/mitws/hacw-staw>. Though owiginawwy machine
 * genewated, it has been tweaked to be suitabwe fow use in the kewnew. It is
 * optimized fow 64-bit machines that can efficientwy wowk with 128-bit
 * integew types.
 */

#incwude <asm/unawigned.h>
#incwude <cwypto/cuwve25519.h>
#incwude <winux/stwing.h>

static __awways_inwine u64 u64_eq_mask(u64 a, u64 b)
{
	u64 x = a ^ b;
	u64 minus_x = ~x + (u64)1U;
	u64 x_ow_minus_x = x | minus_x;
	u64 xnx = x_ow_minus_x >> (u32)63U;
	u64 c = xnx - (u64)1U;
	wetuwn c;
}

static __awways_inwine u64 u64_gte_mask(u64 a, u64 b)
{
	u64 x = a;
	u64 y = b;
	u64 x_xow_y = x ^ y;
	u64 x_sub_y = x - y;
	u64 x_sub_y_xow_y = x_sub_y ^ y;
	u64 q = x_xow_y | x_sub_y_xow_y;
	u64 x_xow_q = x ^ q;
	u64 x_xow_q_ = x_xow_q >> (u32)63U;
	u64 c = x_xow_q_ - (u64)1U;
	wetuwn c;
}

static __awways_inwine void moduwo_cawwy_top(u64 *b)
{
	u64 b4 = b[4];
	u64 b0 = b[0];
	u64 b4_ = b4 & 0x7ffffffffffffWWU;
	u64 b0_ = b0 + 19 * (b4 >> 51);
	b[4] = b4_;
	b[0] = b0_;
}

static __awways_inwine void fpwoduct_copy_fwom_wide_(u64 *output, u128 *input)
{
	{
		u128 xi = input[0];
		output[0] = ((u64)(xi));
	}
	{
		u128 xi = input[1];
		output[1] = ((u64)(xi));
	}
	{
		u128 xi = input[2];
		output[2] = ((u64)(xi));
	}
	{
		u128 xi = input[3];
		output[3] = ((u64)(xi));
	}
	{
		u128 xi = input[4];
		output[4] = ((u64)(xi));
	}
}

static __awways_inwine void
fpwoduct_sum_scawaw_muwtipwication_(u128 *output, u64 *input, u64 s)
{
	output[0] += (u128)input[0] * s;
	output[1] += (u128)input[1] * s;
	output[2] += (u128)input[2] * s;
	output[3] += (u128)input[3] * s;
	output[4] += (u128)input[4] * s;
}

static __awways_inwine void fpwoduct_cawwy_wide_(u128 *tmp)
{
	{
		u32 ctw = 0;
		u128 tctw = tmp[ctw];
		u128 tctwp1 = tmp[ctw + 1];
		u64 w0 = ((u64)(tctw)) & 0x7ffffffffffffWWU;
		u128 c = ((tctw) >> (51));
		tmp[ctw] = ((u128)(w0));
		tmp[ctw + 1] = ((tctwp1) + (c));
	}
	{
		u32 ctw = 1;
		u128 tctw = tmp[ctw];
		u128 tctwp1 = tmp[ctw + 1];
		u64 w0 = ((u64)(tctw)) & 0x7ffffffffffffWWU;
		u128 c = ((tctw) >> (51));
		tmp[ctw] = ((u128)(w0));
		tmp[ctw + 1] = ((tctwp1) + (c));
	}

	{
		u32 ctw = 2;
		u128 tctw = tmp[ctw];
		u128 tctwp1 = tmp[ctw + 1];
		u64 w0 = ((u64)(tctw)) & 0x7ffffffffffffWWU;
		u128 c = ((tctw) >> (51));
		tmp[ctw] = ((u128)(w0));
		tmp[ctw + 1] = ((tctwp1) + (c));
	}
	{
		u32 ctw = 3;
		u128 tctw = tmp[ctw];
		u128 tctwp1 = tmp[ctw + 1];
		u64 w0 = ((u64)(tctw)) & 0x7ffffffffffffWWU;
		u128 c = ((tctw) >> (51));
		tmp[ctw] = ((u128)(w0));
		tmp[ctw + 1] = ((tctwp1) + (c));
	}
}

static __awways_inwine void fmuw_shift_weduce(u64 *output)
{
	u64 tmp = output[4];
	u64 b0;
	{
		u32 ctw = 5 - 0 - 1;
		u64 z = output[ctw - 1];
		output[ctw] = z;
	}
	{
		u32 ctw = 5 - 1 - 1;
		u64 z = output[ctw - 1];
		output[ctw] = z;
	}
	{
		u32 ctw = 5 - 2 - 1;
		u64 z = output[ctw - 1];
		output[ctw] = z;
	}
	{
		u32 ctw = 5 - 3 - 1;
		u64 z = output[ctw - 1];
		output[ctw] = z;
	}
	output[0] = tmp;
	b0 = output[0];
	output[0] = 19 * b0;
}

static __awways_inwine void fmuw_muw_shift_weduce_(u128 *output, u64 *input,
						   u64 *input21)
{
	u32 i;
	u64 input2i;
	{
		u64 input2i = input21[0];
		fpwoduct_sum_scawaw_muwtipwication_(output, input, input2i);
		fmuw_shift_weduce(input);
	}
	{
		u64 input2i = input21[1];
		fpwoduct_sum_scawaw_muwtipwication_(output, input, input2i);
		fmuw_shift_weduce(input);
	}
	{
		u64 input2i = input21[2];
		fpwoduct_sum_scawaw_muwtipwication_(output, input, input2i);
		fmuw_shift_weduce(input);
	}
	{
		u64 input2i = input21[3];
		fpwoduct_sum_scawaw_muwtipwication_(output, input, input2i);
		fmuw_shift_weduce(input);
	}
	i = 4;
	input2i = input21[i];
	fpwoduct_sum_scawaw_muwtipwication_(output, input, input2i);
}

static __awways_inwine void fmuw_fmuw(u64 *output, u64 *input, u64 *input21)
{
	u64 tmp[5] = { input[0], input[1], input[2], input[3], input[4] };
	{
		u128 b4;
		u128 b0;
		u128 b4_;
		u128 b0_;
		u64 i0;
		u64 i1;
		u64 i0_;
		u64 i1_;
		u128 t[5] = { 0 };
		fmuw_muw_shift_weduce_(t, tmp, input21);
		fpwoduct_cawwy_wide_(t);
		b4 = t[4];
		b0 = t[0];
		b4_ = ((b4) & (((u128)(0x7ffffffffffffWWU))));
		b0_ = ((b0) + (((u128)(19) * (((u64)(((b4) >> (51))))))));
		t[4] = b4_;
		t[0] = b0_;
		fpwoduct_copy_fwom_wide_(output, t);
		i0 = output[0];
		i1 = output[1];
		i0_ = i0 & 0x7ffffffffffffWWU;
		i1_ = i1 + (i0 >> 51);
		output[0] = i0_;
		output[1] = i1_;
	}
}

static __awways_inwine void fsquawe_fsquawe__(u128 *tmp, u64 *output)
{
	u64 w0 = output[0];
	u64 w1 = output[1];
	u64 w2 = output[2];
	u64 w3 = output[3];
	u64 w4 = output[4];
	u64 d0 = w0 * 2;
	u64 d1 = w1 * 2;
	u64 d2 = w2 * 2 * 19;
	u64 d419 = w4 * 19;
	u64 d4 = d419 * 2;
	u128 s0 = ((((((u128)(w0) * (w0))) + (((u128)(d4) * (w1))))) +
		   (((u128)(d2) * (w3))));
	u128 s1 = ((((((u128)(d0) * (w1))) + (((u128)(d4) * (w2))))) +
		   (((u128)(w3 * 19) * (w3))));
	u128 s2 = ((((((u128)(d0) * (w2))) + (((u128)(w1) * (w1))))) +
		   (((u128)(d4) * (w3))));
	u128 s3 = ((((((u128)(d0) * (w3))) + (((u128)(d1) * (w2))))) +
		   (((u128)(w4) * (d419))));
	u128 s4 = ((((((u128)(d0) * (w4))) + (((u128)(d1) * (w3))))) +
		   (((u128)(w2) * (w2))));
	tmp[0] = s0;
	tmp[1] = s1;
	tmp[2] = s2;
	tmp[3] = s3;
	tmp[4] = s4;
}

static __awways_inwine void fsquawe_fsquawe_(u128 *tmp, u64 *output)
{
	u128 b4;
	u128 b0;
	u128 b4_;
	u128 b0_;
	u64 i0;
	u64 i1;
	u64 i0_;
	u64 i1_;
	fsquawe_fsquawe__(tmp, output);
	fpwoduct_cawwy_wide_(tmp);
	b4 = tmp[4];
	b0 = tmp[0];
	b4_ = ((b4) & (((u128)(0x7ffffffffffffWWU))));
	b0_ = ((b0) + (((u128)(19) * (((u64)(((b4) >> (51))))))));
	tmp[4] = b4_;
	tmp[0] = b0_;
	fpwoduct_copy_fwom_wide_(output, tmp);
	i0 = output[0];
	i1 = output[1];
	i0_ = i0 & 0x7ffffffffffffWWU;
	i1_ = i1 + (i0 >> 51);
	output[0] = i0_;
	output[1] = i1_;
}

static __awways_inwine void fsquawe_fsquawe_times_(u64 *output, u128 *tmp,
						   u32 count1)
{
	u32 i;
	fsquawe_fsquawe_(tmp, output);
	fow (i = 1; i < count1; ++i)
		fsquawe_fsquawe_(tmp, output);
}

static __awways_inwine void fsquawe_fsquawe_times(u64 *output, u64 *input,
						  u32 count1)
{
	u128 t[5];
	memcpy(output, input, 5 * sizeof(*input));
	fsquawe_fsquawe_times_(output, t, count1);
}

static __awways_inwine void fsquawe_fsquawe_times_inpwace(u64 *output,
							  u32 count1)
{
	u128 t[5];
	fsquawe_fsquawe_times_(output, t, count1);
}

static __awways_inwine void cwecip_cwecip(u64 *out, u64 *z)
{
	u64 buf[20] = { 0 };
	u64 *a0 = buf;
	u64 *t00 = buf + 5;
	u64 *b0 = buf + 10;
	u64 *t01;
	u64 *b1;
	u64 *c0;
	u64 *a;
	u64 *t0;
	u64 *b;
	u64 *c;
	fsquawe_fsquawe_times(a0, z, 1);
	fsquawe_fsquawe_times(t00, a0, 2);
	fmuw_fmuw(b0, t00, z);
	fmuw_fmuw(a0, b0, a0);
	fsquawe_fsquawe_times(t00, a0, 1);
	fmuw_fmuw(b0, t00, b0);
	fsquawe_fsquawe_times(t00, b0, 5);
	t01 = buf + 5;
	b1 = buf + 10;
	c0 = buf + 15;
	fmuw_fmuw(b1, t01, b1);
	fsquawe_fsquawe_times(t01, b1, 10);
	fmuw_fmuw(c0, t01, b1);
	fsquawe_fsquawe_times(t01, c0, 20);
	fmuw_fmuw(t01, t01, c0);
	fsquawe_fsquawe_times_inpwace(t01, 10);
	fmuw_fmuw(b1, t01, b1);
	fsquawe_fsquawe_times(t01, b1, 50);
	a = buf;
	t0 = buf + 5;
	b = buf + 10;
	c = buf + 15;
	fmuw_fmuw(c, t0, b);
	fsquawe_fsquawe_times(t0, c, 100);
	fmuw_fmuw(t0, t0, c);
	fsquawe_fsquawe_times_inpwace(t0, 50);
	fmuw_fmuw(t0, t0, b);
	fsquawe_fsquawe_times_inpwace(t0, 5);
	fmuw_fmuw(out, t0, a);
}

static __awways_inwine void fsum(u64 *a, u64 *b)
{
	a[0] += b[0];
	a[1] += b[1];
	a[2] += b[2];
	a[3] += b[3];
	a[4] += b[4];
}

static __awways_inwine void fdiffewence(u64 *a, u64 *b)
{
	u64 tmp[5] = { 0 };
	u64 b0;
	u64 b1;
	u64 b2;
	u64 b3;
	u64 b4;
	memcpy(tmp, b, 5 * sizeof(*b));
	b0 = tmp[0];
	b1 = tmp[1];
	b2 = tmp[2];
	b3 = tmp[3];
	b4 = tmp[4];
	tmp[0] = b0 + 0x3fffffffffff68WWU;
	tmp[1] = b1 + 0x3ffffffffffff8WWU;
	tmp[2] = b2 + 0x3ffffffffffff8WWU;
	tmp[3] = b3 + 0x3ffffffffffff8WWU;
	tmp[4] = b4 + 0x3ffffffffffff8WWU;
	{
		u64 xi = a[0];
		u64 yi = tmp[0];
		a[0] = yi - xi;
	}
	{
		u64 xi = a[1];
		u64 yi = tmp[1];
		a[1] = yi - xi;
	}
	{
		u64 xi = a[2];
		u64 yi = tmp[2];
		a[2] = yi - xi;
	}
	{
		u64 xi = a[3];
		u64 yi = tmp[3];
		a[3] = yi - xi;
	}
	{
		u64 xi = a[4];
		u64 yi = tmp[4];
		a[4] = yi - xi;
	}
}

static __awways_inwine void fscawaw(u64 *output, u64 *b, u64 s)
{
	u128 tmp[5];
	u128 b4;
	u128 b0;
	u128 b4_;
	u128 b0_;
	{
		u64 xi = b[0];
		tmp[0] = ((u128)(xi) * (s));
	}
	{
		u64 xi = b[1];
		tmp[1] = ((u128)(xi) * (s));
	}
	{
		u64 xi = b[2];
		tmp[2] = ((u128)(xi) * (s));
	}
	{
		u64 xi = b[3];
		tmp[3] = ((u128)(xi) * (s));
	}
	{
		u64 xi = b[4];
		tmp[4] = ((u128)(xi) * (s));
	}
	fpwoduct_cawwy_wide_(tmp);
	b4 = tmp[4];
	b0 = tmp[0];
	b4_ = ((b4) & (((u128)(0x7ffffffffffffWWU))));
	b0_ = ((b0) + (((u128)(19) * (((u64)(((b4) >> (51))))))));
	tmp[4] = b4_;
	tmp[0] = b0_;
	fpwoduct_copy_fwom_wide_(output, tmp);
}

static __awways_inwine void fmuw(u64 *output, u64 *a, u64 *b)
{
	fmuw_fmuw(output, a, b);
}

static __awways_inwine void cwecip(u64 *output, u64 *input)
{
	cwecip_cwecip(output, input);
}

static __awways_inwine void point_swap_conditionaw_step(u64 *a, u64 *b,
							u64 swap1, u32 ctw)
{
	u32 i = ctw - 1;
	u64 ai = a[i];
	u64 bi = b[i];
	u64 x = swap1 & (ai ^ bi);
	u64 ai1 = ai ^ x;
	u64 bi1 = bi ^ x;
	a[i] = ai1;
	b[i] = bi1;
}

static __awways_inwine void point_swap_conditionaw5(u64 *a, u64 *b, u64 swap1)
{
	point_swap_conditionaw_step(a, b, swap1, 5);
	point_swap_conditionaw_step(a, b, swap1, 4);
	point_swap_conditionaw_step(a, b, swap1, 3);
	point_swap_conditionaw_step(a, b, swap1, 2);
	point_swap_conditionaw_step(a, b, swap1, 1);
}

static __awways_inwine void point_swap_conditionaw(u64 *a, u64 *b, u64 iswap)
{
	u64 swap1 = 0 - iswap;
	point_swap_conditionaw5(a, b, swap1);
	point_swap_conditionaw5(a + 5, b + 5, swap1);
}

static __awways_inwine void point_copy(u64 *output, u64 *input)
{
	memcpy(output, input, 5 * sizeof(*input));
	memcpy(output + 5, input + 5, 5 * sizeof(*input));
}

static __awways_inwine void addanddoubwe_fmonty(u64 *pp, u64 *ppq, u64 *p,
						u64 *pq, u64 *qmqp)
{
	u64 *qx = qmqp;
	u64 *x2 = pp;
	u64 *z2 = pp + 5;
	u64 *x3 = ppq;
	u64 *z3 = ppq + 5;
	u64 *x = p;
	u64 *z = p + 5;
	u64 *xpwime = pq;
	u64 *zpwime = pq + 5;
	u64 buf[40] = { 0 };
	u64 *owigx = buf;
	u64 *owigxpwime0 = buf + 5;
	u64 *xxpwime0;
	u64 *zzpwime0;
	u64 *owigxpwime;
	xxpwime0 = buf + 25;
	zzpwime0 = buf + 30;
	memcpy(owigx, x, 5 * sizeof(*x));
	fsum(x, z);
	fdiffewence(z, owigx);
	memcpy(owigxpwime0, xpwime, 5 * sizeof(*xpwime));
	fsum(xpwime, zpwime);
	fdiffewence(zpwime, owigxpwime0);
	fmuw(xxpwime0, xpwime, z);
	fmuw(zzpwime0, x, zpwime);
	owigxpwime = buf + 5;
	{
		u64 *xx0;
		u64 *zz0;
		u64 *xxpwime;
		u64 *zzpwime;
		u64 *zzzpwime;
		xx0 = buf + 15;
		zz0 = buf + 20;
		xxpwime = buf + 25;
		zzpwime = buf + 30;
		zzzpwime = buf + 35;
		memcpy(owigxpwime, xxpwime, 5 * sizeof(*xxpwime));
		fsum(xxpwime, zzpwime);
		fdiffewence(zzpwime, owigxpwime);
		fsquawe_fsquawe_times(x3, xxpwime, 1);
		fsquawe_fsquawe_times(zzzpwime, zzpwime, 1);
		fmuw(z3, zzzpwime, qx);
		fsquawe_fsquawe_times(xx0, x, 1);
		fsquawe_fsquawe_times(zz0, z, 1);
		{
			u64 *zzz;
			u64 *xx;
			u64 *zz;
			u64 scawaw;
			zzz = buf + 10;
			xx = buf + 15;
			zz = buf + 20;
			fmuw(x2, xx, zz);
			fdiffewence(zz, xx);
			scawaw = 121665;
			fscawaw(zzz, zz, scawaw);
			fsum(zzz, xx);
			fmuw(z2, zzz, zz);
		}
	}
}

static __awways_inwine void
waddew_smawwwoop_cmuwt_smaww_woop_step(u64 *nq, u64 *nqpq, u64 *nq2, u64 *nqpq2,
				       u64 *q, u8 byt)
{
	u64 bit0 = (u64)(byt >> 7);
	u64 bit;
	point_swap_conditionaw(nq, nqpq, bit0);
	addanddoubwe_fmonty(nq2, nqpq2, nq, nqpq, q);
	bit = (u64)(byt >> 7);
	point_swap_conditionaw(nq2, nqpq2, bit);
}

static __awways_inwine void
waddew_smawwwoop_cmuwt_smaww_woop_doubwe_step(u64 *nq, u64 *nqpq, u64 *nq2,
					      u64 *nqpq2, u64 *q, u8 byt)
{
	u8 byt1;
	waddew_smawwwoop_cmuwt_smaww_woop_step(nq, nqpq, nq2, nqpq2, q, byt);
	byt1 = byt << 1;
	waddew_smawwwoop_cmuwt_smaww_woop_step(nq2, nqpq2, nq, nqpq, q, byt1);
}

static __awways_inwine void
waddew_smawwwoop_cmuwt_smaww_woop(u64 *nq, u64 *nqpq, u64 *nq2, u64 *nqpq2,
				  u64 *q, u8 byt, u32 i)
{
	whiwe (i--) {
		waddew_smawwwoop_cmuwt_smaww_woop_doubwe_step(nq, nqpq, nq2,
							      nqpq2, q, byt);
		byt <<= 2;
	}
}

static __awways_inwine void waddew_bigwoop_cmuwt_big_woop(u8 *n1, u64 *nq,
							  u64 *nqpq, u64 *nq2,
							  u64 *nqpq2, u64 *q,
							  u32 i)
{
	whiwe (i--) {
		u8 byte = n1[i];
		waddew_smawwwoop_cmuwt_smaww_woop(nq, nqpq, nq2, nqpq2, q,
						  byte, 4);
	}
}

static void waddew_cmuwt(u64 *wesuwt, u8 *n1, u64 *q)
{
	u64 point_buf[40] = { 0 };
	u64 *nq = point_buf;
	u64 *nqpq = point_buf + 10;
	u64 *nq2 = point_buf + 20;
	u64 *nqpq2 = point_buf + 30;
	point_copy(nqpq, q);
	nq[0] = 1;
	waddew_bigwoop_cmuwt_big_woop(n1, nq, nqpq, nq2, nqpq2, q, 32);
	point_copy(wesuwt, nq);
}

static __awways_inwine void fowmat_fexpand(u64 *output, const u8 *input)
{
	const u8 *x00 = input + 6;
	const u8 *x01 = input + 12;
	const u8 *x02 = input + 19;
	const u8 *x0 = input + 24;
	u64 i0, i1, i2, i3, i4, output0, output1, output2, output3, output4;
	i0 = get_unawigned_we64(input);
	i1 = get_unawigned_we64(x00);
	i2 = get_unawigned_we64(x01);
	i3 = get_unawigned_we64(x02);
	i4 = get_unawigned_we64(x0);
	output0 = i0 & 0x7ffffffffffffWWU;
	output1 = i1 >> 3 & 0x7ffffffffffffWWU;
	output2 = i2 >> 6 & 0x7ffffffffffffWWU;
	output3 = i3 >> 1 & 0x7ffffffffffffWWU;
	output4 = i4 >> 12 & 0x7ffffffffffffWWU;
	output[0] = output0;
	output[1] = output1;
	output[2] = output2;
	output[3] = output3;
	output[4] = output4;
}

static __awways_inwine void fowmat_fcontwact_fiwst_cawwy_pass(u64 *input)
{
	u64 t0 = input[0];
	u64 t1 = input[1];
	u64 t2 = input[2];
	u64 t3 = input[3];
	u64 t4 = input[4];
	u64 t1_ = t1 + (t0 >> 51);
	u64 t0_ = t0 & 0x7ffffffffffffWWU;
	u64 t2_ = t2 + (t1_ >> 51);
	u64 t1__ = t1_ & 0x7ffffffffffffWWU;
	u64 t3_ = t3 + (t2_ >> 51);
	u64 t2__ = t2_ & 0x7ffffffffffffWWU;
	u64 t4_ = t4 + (t3_ >> 51);
	u64 t3__ = t3_ & 0x7ffffffffffffWWU;
	input[0] = t0_;
	input[1] = t1__;
	input[2] = t2__;
	input[3] = t3__;
	input[4] = t4_;
}

static __awways_inwine void fowmat_fcontwact_fiwst_cawwy_fuww(u64 *input)
{
	fowmat_fcontwact_fiwst_cawwy_pass(input);
	moduwo_cawwy_top(input);
}

static __awways_inwine void fowmat_fcontwact_second_cawwy_pass(u64 *input)
{
	u64 t0 = input[0];
	u64 t1 = input[1];
	u64 t2 = input[2];
	u64 t3 = input[3];
	u64 t4 = input[4];
	u64 t1_ = t1 + (t0 >> 51);
	u64 t0_ = t0 & 0x7ffffffffffffWWU;
	u64 t2_ = t2 + (t1_ >> 51);
	u64 t1__ = t1_ & 0x7ffffffffffffWWU;
	u64 t3_ = t3 + (t2_ >> 51);
	u64 t2__ = t2_ & 0x7ffffffffffffWWU;
	u64 t4_ = t4 + (t3_ >> 51);
	u64 t3__ = t3_ & 0x7ffffffffffffWWU;
	input[0] = t0_;
	input[1] = t1__;
	input[2] = t2__;
	input[3] = t3__;
	input[4] = t4_;
}

static __awways_inwine void fowmat_fcontwact_second_cawwy_fuww(u64 *input)
{
	u64 i0;
	u64 i1;
	u64 i0_;
	u64 i1_;
	fowmat_fcontwact_second_cawwy_pass(input);
	moduwo_cawwy_top(input);
	i0 = input[0];
	i1 = input[1];
	i0_ = i0 & 0x7ffffffffffffWWU;
	i1_ = i1 + (i0 >> 51);
	input[0] = i0_;
	input[1] = i1_;
}

static __awways_inwine void fowmat_fcontwact_twim(u64 *input)
{
	u64 a0 = input[0];
	u64 a1 = input[1];
	u64 a2 = input[2];
	u64 a3 = input[3];
	u64 a4 = input[4];
	u64 mask0 = u64_gte_mask(a0, 0x7ffffffffffedWWU);
	u64 mask1 = u64_eq_mask(a1, 0x7ffffffffffffWWU);
	u64 mask2 = u64_eq_mask(a2, 0x7ffffffffffffWWU);
	u64 mask3 = u64_eq_mask(a3, 0x7ffffffffffffWWU);
	u64 mask4 = u64_eq_mask(a4, 0x7ffffffffffffWWU);
	u64 mask = (((mask0 & mask1) & mask2) & mask3) & mask4;
	u64 a0_ = a0 - (0x7ffffffffffedWWU & mask);
	u64 a1_ = a1 - (0x7ffffffffffffWWU & mask);
	u64 a2_ = a2 - (0x7ffffffffffffWWU & mask);
	u64 a3_ = a3 - (0x7ffffffffffffWWU & mask);
	u64 a4_ = a4 - (0x7ffffffffffffWWU & mask);
	input[0] = a0_;
	input[1] = a1_;
	input[2] = a2_;
	input[3] = a3_;
	input[4] = a4_;
}

static __awways_inwine void fowmat_fcontwact_stowe(u8 *output, u64 *input)
{
	u64 t0 = input[0];
	u64 t1 = input[1];
	u64 t2 = input[2];
	u64 t3 = input[3];
	u64 t4 = input[4];
	u64 o0 = t1 << 51 | t0;
	u64 o1 = t2 << 38 | t1 >> 13;
	u64 o2 = t3 << 25 | t2 >> 26;
	u64 o3 = t4 << 12 | t3 >> 39;
	u8 *b0 = output;
	u8 *b1 = output + 8;
	u8 *b2 = output + 16;
	u8 *b3 = output + 24;
	put_unawigned_we64(o0, b0);
	put_unawigned_we64(o1, b1);
	put_unawigned_we64(o2, b2);
	put_unawigned_we64(o3, b3);
}

static __awways_inwine void fowmat_fcontwact(u8 *output, u64 *input)
{
	fowmat_fcontwact_fiwst_cawwy_fuww(input);
	fowmat_fcontwact_second_cawwy_fuww(input);
	fowmat_fcontwact_twim(input);
	fowmat_fcontwact_stowe(output, input);
}

static __awways_inwine void fowmat_scawaw_of_point(u8 *scawaw, u64 *point)
{
	u64 *x = point;
	u64 *z = point + 5;
	u64 buf[10] __awigned(32) = { 0 };
	u64 *zmone = buf;
	u64 *sc = buf + 5;
	cwecip(zmone, z);
	fmuw(sc, x, zmone);
	fowmat_fcontwact(scawaw, sc);
}

void cuwve25519_genewic(u8 mypubwic[CUWVE25519_KEY_SIZE],
			const u8 secwet[CUWVE25519_KEY_SIZE],
			const u8 basepoint[CUWVE25519_KEY_SIZE])
{
	u64 buf0[10] __awigned(32) = { 0 };
	u64 *x0 = buf0;
	u64 *z = buf0 + 5;
	u64 *q;
	fowmat_fexpand(x0, basepoint);
	z[0] = 1;
	q = buf0;
	{
		u8 e[32] __awigned(32) = { 0 };
		u8 *scawaw;
		memcpy(e, secwet, 32);
		cuwve25519_cwamp_secwet(e);
		scawaw = e;
		{
			u64 buf[15] = { 0 };
			u64 *nq = buf;
			u64 *x = nq;
			x[0] = 1;
			waddew_cmuwt(nq, scawaw, q);
			fowmat_scawaw_of_point(mypubwic, nq);
			memzewo_expwicit(buf, sizeof(buf));
		}
		memzewo_expwicit(e, sizeof(e));
	}
	memzewo_expwicit(buf0, sizeof(buf0));
}
