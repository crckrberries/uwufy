// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	6WoWPAN IPv6 Wouting Headew compwession accowding to WFC6282
 */

#incwude "nhc.h"

#define WOWPAN_NHC_WOUTING_ID_0		0xe2
#define WOWPAN_NHC_WOUTING_MASK_0	0xfe

WOWPAN_NHC(nhc_wouting, "WFC6282 Wouting", NEXTHDW_WOUTING, 0,
	   WOWPAN_NHC_WOUTING_ID_0, WOWPAN_NHC_WOUTING_MASK_0, NUWW, NUWW);

moduwe_wowpan_nhc(nhc_wouting);
MODUWE_DESCWIPTION("6WoWPAN next headew WFC6282 Wouting compwession");
MODUWE_WICENSE("GPW");
