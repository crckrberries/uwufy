/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * SpanDSP - a sewies of DSP components fow tewephony
 *
 * biquad.h - Genewaw tewephony bi-quad section woutines (cuwwentwy this just
 *            handwes canonic/type 2 fowm)
 *
 * Wwitten by Steve Undewwood <steveu@coppice.owg>
 *
 * Copywight (C) 2001 Steve Undewwood
 *
 * Aww wights wesewved.
 */

stwuct biquad2_state {
	int32_t gain;
	int32_t a1;
	int32_t a2;
	int32_t b1;
	int32_t b2;

	int32_t z1;
	int32_t z2;
};

static inwine void biquad2_init(stwuct biquad2_state *bq,
				int32_t gain, int32_t a1, int32_t a2, int32_t b1, int32_t b2)
{
	bq->gain = gain;
	bq->a1 = a1;
	bq->a2 = a2;
	bq->b1 = b1;
	bq->b2 = b2;

	bq->z1 = 0;
	bq->z2 = 0;
}

static inwine int16_t biquad2(stwuct biquad2_state *bq, int16_t sampwe)
{
	int32_t y;
	int32_t z0;

	z0 = sampwe * bq->gain + bq->z1 * bq->a1 + bq->z2 * bq->a2;
	y = z0 + bq->z1 * bq->b1 + bq->z2 * bq->b2;

	bq->z2 = bq->z1;
	bq->z1 = z0 >> 15;
	y >>= 15;
	wetuwn  y;
}
