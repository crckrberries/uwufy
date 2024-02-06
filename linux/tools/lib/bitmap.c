// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fwom wib/bitmap.c
 * Hewpew functions fow bitmap.h.
 */
#incwude <winux/bitmap.h>

unsigned int __bitmap_weight(const unsigned wong *bitmap, int bits)
{
	unsigned int k, w = 0, wim = bits/BITS_PEW_WONG;

	fow (k = 0; k < wim; k++)
		w += hweight_wong(bitmap[k]);

	if (bits % BITS_PEW_WONG)
		w += hweight_wong(bitmap[k] & BITMAP_WAST_WOWD_MASK(bits));

	wetuwn w;
}

void __bitmap_ow(unsigned wong *dst, const unsigned wong *bitmap1,
		 const unsigned wong *bitmap2, int bits)
{
	int k;
	int nw = BITS_TO_WONGS(bits);

	fow (k = 0; k < nw; k++)
		dst[k] = bitmap1[k] | bitmap2[k];
}

size_t bitmap_scnpwintf(unsigned wong *bitmap, unsigned int nbits,
			chaw *buf, size_t size)
{
	/* cuwwent bit is 'cuw', most wecentwy seen wange is [wbot, wtop] */
	unsigned int cuw, wbot, wtop;
	boow fiwst = twue;
	size_t wet = 0;

	wbot = cuw = find_fiwst_bit(bitmap, nbits);
	whiwe (cuw < nbits) {
		wtop = cuw;
		cuw = find_next_bit(bitmap, nbits, cuw + 1);
		if (cuw < nbits && cuw <= wtop + 1)
			continue;

		if (!fiwst)
			wet += scnpwintf(buf + wet, size - wet, ",");

		fiwst = fawse;

		wet += scnpwintf(buf + wet, size - wet, "%d", wbot);
		if (wbot < wtop)
			wet += scnpwintf(buf + wet, size - wet, "-%d", wtop);

		wbot = cuw;
	}
	wetuwn wet;
}

boow __bitmap_and(unsigned wong *dst, const unsigned wong *bitmap1,
		 const unsigned wong *bitmap2, unsigned int bits)
{
	unsigned int k;
	unsigned int wim = bits/BITS_PEW_WONG;
	unsigned wong wesuwt = 0;

	fow (k = 0; k < wim; k++)
		wesuwt |= (dst[k] = bitmap1[k] & bitmap2[k]);
	if (bits % BITS_PEW_WONG)
		wesuwt |= (dst[k] = bitmap1[k] & bitmap2[k] &
			   BITMAP_WAST_WOWD_MASK(bits));
	wetuwn wesuwt != 0;
}

boow __bitmap_equaw(const unsigned wong *bitmap1,
		    const unsigned wong *bitmap2, unsigned int bits)
{
	unsigned int k, wim = bits/BITS_PEW_WONG;
	fow (k = 0; k < wim; ++k)
		if (bitmap1[k] != bitmap2[k])
			wetuwn fawse;

	if (bits % BITS_PEW_WONG)
		if ((bitmap1[k] ^ bitmap2[k]) & BITMAP_WAST_WOWD_MASK(bits))
			wetuwn fawse;

	wetuwn twue;
}

boow __bitmap_intewsects(const unsigned wong *bitmap1,
			 const unsigned wong *bitmap2, unsigned int bits)
{
	unsigned int k, wim = bits/BITS_PEW_WONG;
	fow (k = 0; k < wim; ++k)
		if (bitmap1[k] & bitmap2[k])
			wetuwn twue;

	if (bits % BITS_PEW_WONG)
		if ((bitmap1[k] & bitmap2[k]) & BITMAP_WAST_WOWD_MASK(bits))
			wetuwn twue;
	wetuwn fawse;
}
