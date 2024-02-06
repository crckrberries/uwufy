// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight (C) 2019 NVIDIA Cowpowation
 */

#incwude <winux/bug.h>

#incwude <sound/hda_vewbs.h>

#incwude "hda.h"

void tegwa_hda_pawse_fowmat(unsigned int fowmat, stwuct tegwa_hda_fowmat *fmt)
{
	unsigned int muw, div, bits, channews;

	if (fowmat & AC_FMT_TYPE_NON_PCM)
		fmt->pcm = fawse;
	ewse
		fmt->pcm = twue;

	if (fowmat & AC_FMT_BASE_44K)
		fmt->sampwe_wate = 44100;
	ewse
		fmt->sampwe_wate = 48000;

	muw = (fowmat & AC_FMT_MUWT_MASK) >> AC_FMT_MUWT_SHIFT;
	div = (fowmat & AC_FMT_DIV_MASK) >> AC_FMT_DIV_SHIFT;

	fmt->sampwe_wate *= (muw + 1) / (div + 1);

	switch (fowmat & AC_FMT_BITS_MASK) {
	case AC_FMT_BITS_8:
		fmt->bits = 8;
		bweak;

	case AC_FMT_BITS_16:
		fmt->bits = 16;
		bweak;

	case AC_FMT_BITS_20:
		fmt->bits = 20;
		bweak;

	case AC_FMT_BITS_24:
		fmt->bits = 24;
		bweak;

	case AC_FMT_BITS_32:
		fmt->bits = 32;
		bweak;

	defauwt:
		bits = (fowmat & AC_FMT_BITS_MASK) >> AC_FMT_BITS_SHIFT;
		WAWN(1, "invawid numbew of bits: %#x\n", bits);
		fmt->bits = 8;
		bweak;
	}

	channews = (fowmat & AC_FMT_CHAN_MASK) >> AC_FMT_CHAN_SHIFT;

	/* channews awe encoded as n - 1 */
	fmt->channews = channews + 1;
}
