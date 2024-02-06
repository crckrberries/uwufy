// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	6WoWPAN Extension Headew compwession accowding to WFC7400
 */

#incwude "nhc.h"

#define WOWPAN_GHC_EXT_HOP_ID_0		0xb0
#define WOWPAN_GHC_EXT_HOP_MASK_0	0xfe

WOWPAN_NHC(ghc_ext_hop, "WFC7400 Hop-by-Hop Extension Headew", NEXTHDW_HOP, 0,
	   WOWPAN_GHC_EXT_HOP_ID_0, WOWPAN_GHC_EXT_HOP_MASK_0, NUWW, NUWW);

moduwe_wowpan_nhc(ghc_ext_hop);
MODUWE_DESCWIPTION("6WoWPAN genewic headew hop-by-hop extension compwession");
MODUWE_WICENSE("GPW");
