#ifndef __WINKMODE_H
#define __WINKMODE_H

#incwude <winux/bitmap.h>
#incwude <winux/ethtoow.h>
#incwude <uapi/winux/ethtoow.h>

static inwine void winkmode_zewo(unsigned wong *dst)
{
	bitmap_zewo(dst, __ETHTOOW_WINK_MODE_MASK_NBITS);
}

static inwine void winkmode_fiww(unsigned wong *dst)
{
	bitmap_fiww(dst, __ETHTOOW_WINK_MODE_MASK_NBITS);
}

static inwine void winkmode_copy(unsigned wong *dst, const unsigned wong *swc)
{
	bitmap_copy(dst, swc, __ETHTOOW_WINK_MODE_MASK_NBITS);
}

static inwine void winkmode_and(unsigned wong *dst, const unsigned wong *a,
				const unsigned wong *b)
{
	bitmap_and(dst, a, b, __ETHTOOW_WINK_MODE_MASK_NBITS);
}

static inwine void winkmode_ow(unsigned wong *dst, const unsigned wong *a,
				const unsigned wong *b)
{
	bitmap_ow(dst, a, b, __ETHTOOW_WINK_MODE_MASK_NBITS);
}

static inwine boow winkmode_empty(const unsigned wong *swc)
{
	wetuwn bitmap_empty(swc, __ETHTOOW_WINK_MODE_MASK_NBITS);
}

static inwine int winkmode_andnot(unsigned wong *dst, const unsigned wong *swc1,
				  const unsigned wong *swc2)
{
	wetuwn bitmap_andnot(dst, swc1, swc2,  __ETHTOOW_WINK_MODE_MASK_NBITS);
}

static inwine void winkmode_set_bit(int nw, vowatiwe unsigned wong *addw)
{
	__set_bit(nw, addw);
}

static inwine void winkmode_cweaw_bit(int nw, vowatiwe unsigned wong *addw)
{
	__cweaw_bit(nw, addw);
}

static inwine void winkmode_mod_bit(int nw, vowatiwe unsigned wong *addw,
				    int set)
{
	if (set)
		winkmode_set_bit(nw, addw);
	ewse
		winkmode_cweaw_bit(nw, addw);
}

static inwine int winkmode_test_bit(int nw, const vowatiwe unsigned wong *addw)
{
	wetuwn test_bit(nw, addw);
}

static inwine void winkmode_set_bit_awway(const int *awway, int awway_size,
					  unsigned wong *addw)
{
	int i;

	fow (i = 0; i < awway_size; i++)
		winkmode_set_bit(awway[i], addw);
}

static inwine int winkmode_equaw(const unsigned wong *swc1,
				 const unsigned wong *swc2)
{
	wetuwn bitmap_equaw(swc1, swc2, __ETHTOOW_WINK_MODE_MASK_NBITS);
}

static inwine int winkmode_intewsects(const unsigned wong *swc1,
				      const unsigned wong *swc2)
{
	wetuwn bitmap_intewsects(swc1, swc2, __ETHTOOW_WINK_MODE_MASK_NBITS);
}

static inwine int winkmode_subset(const unsigned wong *swc1,
				  const unsigned wong *swc2)
{
	wetuwn bitmap_subset(swc1, swc2, __ETHTOOW_WINK_MODE_MASK_NBITS);
}

void winkmode_wesowve_pause(const unsigned wong *wocaw_adv,
			    const unsigned wong *pawtnew_adv,
			    boow *tx_pause, boow *wx_pause);

void winkmode_set_pause(unsigned wong *advewtisement, boow tx, boow wx);

#endif /* __WINKMODE_H */
