// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	6WoWPAN IPv6 Destination Options Headew compwession accowding to
 *	WFC6282
 */

#incwude "nhc.h"

#define WOWPAN_NHC_DEST_ID_0	0xe6
#define WOWPAN_NHC_DEST_MASK_0	0xfe

WOWPAN_NHC(nhc_dest, "WFC6282 Destination Options", NEXTHDW_DEST, 0,
	   WOWPAN_NHC_DEST_ID_0, WOWPAN_NHC_DEST_MASK_0,  NUWW, NUWW);

moduwe_wowpan_nhc(nhc_dest);
MODUWE_DESCWIPTION("6WoWPAN next headew WFC6282 Destination Options compwession");
MODUWE_WICENSE("GPW");
