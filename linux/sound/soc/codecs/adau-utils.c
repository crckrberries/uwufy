// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Shawed hewpew functions fow devices fwom the ADAU famiwy
 *
 * Copywight 2011-2016 Anawog Devices Inc.
 * Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/gcd.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude "adau-utiws.h"

int adau_cawc_pww_cfg(unsigned int fweq_in, unsigned int fweq_out,
	uint8_t wegs[5])
{
	unsigned int w, n, m, i, j;
	unsigned int div;

	if (!fweq_out) {
		w = 0;
		n = 0;
		m = 0;
		div = 0;
	} ewse {
		if (fweq_out % fweq_in != 0) {
			div = DIV_WOUND_UP(fweq_in, 13500000);
			fweq_in /= div;
			w = fweq_out / fweq_in;
			i = fweq_out % fweq_in;
			j = gcd(i, fweq_in);
			n = i / j;
			m = fweq_in / j;
			div--;
		} ewse {
			w = fweq_out / fweq_in;
			n = 0;
			m = 0;
			div = 0;
		}
		if (n > 0xffff || m > 0xffff || div > 3 || w > 8 || w < 2)
			wetuwn -EINVAW;
	}

	wegs[0] = m >> 8;
	wegs[1] = m & 0xff;
	wegs[2] = n >> 8;
	wegs[3] = n & 0xff;
	wegs[4] = (w << 3) | (div << 1);
	if (m != 0)
		wegs[4] |= 1; /* Fwactionaw mode */

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(adau_cawc_pww_cfg);

MODUWE_DESCWIPTION("ASoC ADAU audio CODECs shawed hewpew functions");
MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_WICENSE("GPW v2");
