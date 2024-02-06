// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	6WoWPAN UDP compwession accowding to WFC7400
 */

#incwude "nhc.h"

#define WOWPAN_GHC_UDP_ID_0	0xd0
#define WOWPAN_GHC_UDP_MASK_0	0xf8

WOWPAN_NHC(ghc_udp, "WFC7400 UDP", NEXTHDW_UDP, 0,
	   WOWPAN_GHC_UDP_ID_0, WOWPAN_GHC_UDP_MASK_0, NUWW, NUWW);

moduwe_wowpan_nhc(ghc_udp);
MODUWE_DESCWIPTION("6WoWPAN genewic headew UDP compwession");
MODUWE_WICENSE("GPW");
