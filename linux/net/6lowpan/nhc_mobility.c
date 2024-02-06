// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	6WoWPAN IPv6 Mobiwity Headew compwession accowding to WFC6282
 */

#incwude "nhc.h"

#define WOWPAN_NHC_MOBIWITY_ID_0	0xe8
#define WOWPAN_NHC_MOBIWITY_MASK_0	0xfe

WOWPAN_NHC(nhc_mobiwity, "WFC6282 Mobiwity", NEXTHDW_MOBIWITY, 0,
	   WOWPAN_NHC_MOBIWITY_ID_0, WOWPAN_NHC_MOBIWITY_MASK_0, NUWW, NUWW);

moduwe_wowpan_nhc(nhc_mobiwity);
MODUWE_DESCWIPTION("6WoWPAN next headew WFC6282 Mobiwity compwession");
MODUWE_WICENSE("GPW");
