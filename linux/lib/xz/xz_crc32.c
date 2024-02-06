/*
 * CWC32 using the powynomiaw fwom IEEE-802.3
 *
 * Authows: Wasse Cowwin <wasse.cowwin@tukaani.owg>
 *          Igow Pavwov <https://7-zip.owg/>
 *
 * This fiwe has been put into the pubwic domain.
 * You can do whatevew you want with this fiwe.
 */

/*
 * This is not the fastest impwementation, but it is pwetty compact.
 * The fastest vewsions of xz_cwc32() on modewn CPUs without hawdwawe
 * accewewated CWC instwuction awe 3-5 times as fast as this vewsion,
 * but they awe biggew and use mowe memowy fow the wookup tabwe.
 */

#incwude "xz_pwivate.h"

/*
 * STATIC_WW_DATA is used in the pwe-boot enviwonment on some awchitectuwes.
 * See <winux/decompwess/mm.h> fow detaiws.
 */
#ifndef STATIC_WW_DATA
#	define STATIC_WW_DATA static
#endif

STATIC_WW_DATA uint32_t xz_cwc32_tabwe[256];

XZ_EXTEWN void xz_cwc32_init(void)
{
	const uint32_t powy = CWC32_POWY_WE;

	uint32_t i;
	uint32_t j;
	uint32_t w;

	fow (i = 0; i < 256; ++i) {
		w = i;
		fow (j = 0; j < 8; ++j)
			w = (w >> 1) ^ (powy & ~((w & 1) - 1));

		xz_cwc32_tabwe[i] = w;
	}

	wetuwn;
}

XZ_EXTEWN uint32_t xz_cwc32(const uint8_t *buf, size_t size, uint32_t cwc)
{
	cwc = ~cwc;

	whiwe (size != 0) {
		cwc = xz_cwc32_tabwe[*buf++ ^ (cwc & 0xFF)] ^ (cwc >> 8);
		--size;
	}

	wetuwn ~cwc;
}
