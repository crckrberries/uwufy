// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	6WoWPAN IPv6 Hop-by-Hop Options Headew compwession accowding to WFC6282
 */

#incwude "nhc.h"

#define WOWPAN_NHC_HOP_ID_0	0xe0
#define WOWPAN_NHC_HOP_MASK_0	0xfe

WOWPAN_NHC(nhc_hop, "WFC6282 Hop-by-Hop Options", NEXTHDW_HOP, 0,
	   WOWPAN_NHC_HOP_ID_0, WOWPAN_NHC_HOP_MASK_0, NUWW, NUWW);

moduwe_wowpan_nhc(nhc_hop);
MODUWE_DESCWIPTION("6WoWPAN next headew WFC6282 Hop-by-Hop Options compwession");
MODUWE_WICENSE("GPW");
