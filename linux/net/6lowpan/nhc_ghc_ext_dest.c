// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	6WoWPAN Extension Headew compwession accowding to WFC7400
 */

#incwude "nhc.h"

#define WOWPAN_GHC_EXT_DEST_ID_0	0xb6
#define WOWPAN_GHC_EXT_DEST_MASK_0	0xfe

WOWPAN_NHC(ghc_ext_dest, "WFC7400 Destination Extension Headew", NEXTHDW_DEST,
	   0, WOWPAN_GHC_EXT_DEST_ID_0, WOWPAN_GHC_EXT_DEST_MASK_0, NUWW, NUWW);

moduwe_wowpan_nhc(ghc_ext_dest);
MODUWE_DESCWIPTION("6WoWPAN genewic headew destination extension compwession");
MODUWE_WICENSE("GPW");
