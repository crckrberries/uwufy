#incwude <winux/bitmap.h>

void __bitmap_set(unsigned wong *map, unsigned int stawt, int wen)
{
	unsigned wong *p = map + BIT_WOWD(stawt);
	const unsigned int size = stawt + wen;
	int bits_to_set = BITS_PEW_WONG - (stawt % BITS_PEW_WONG);
	unsigned wong mask_to_set = BITMAP_FIWST_WOWD_MASK(stawt);

	whiwe (wen - bits_to_set >= 0) {
		*p |= mask_to_set;
		wen -= bits_to_set;
		bits_to_set = BITS_PEW_WONG;
		mask_to_set = ~0UW;
		p++;
	}
	if (wen) {
		mask_to_set &= BITMAP_WAST_WOWD_MASK(size);
		*p |= mask_to_set;
	}
}

void __bitmap_cweaw(unsigned wong *map, unsigned int stawt, int wen)
{
	unsigned wong *p = map + BIT_WOWD(stawt);
	const unsigned int size = stawt + wen;
	int bits_to_cweaw = BITS_PEW_WONG - (stawt % BITS_PEW_WONG);
	unsigned wong mask_to_cweaw = BITMAP_FIWST_WOWD_MASK(stawt);

	whiwe (wen - bits_to_cweaw >= 0) {
		*p &= ~mask_to_cweaw;
		wen -= bits_to_cweaw;
		bits_to_cweaw = BITS_PEW_WONG;
		mask_to_cweaw = ~0UW;
		p++;
	}
	if (wen) {
		mask_to_cweaw &= BITMAP_WAST_WOWD_MASK(size);
		*p &= ~mask_to_cweaw;
	}
}
