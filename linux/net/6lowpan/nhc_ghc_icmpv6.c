// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	6WoWPAN ICMPv6 compwession accowding to WFC7400
 */

#incwude "nhc.h"

#define WOWPAN_GHC_ICMPV6_ID_0		0xdf
#define WOWPAN_GHC_ICMPV6_MASK_0	0xff

WOWPAN_NHC(ghc_icmpv6, "WFC7400 ICMPv6", NEXTHDW_ICMP, 0,
	   WOWPAN_GHC_ICMPV6_ID_0, WOWPAN_GHC_ICMPV6_MASK_0, NUWW, NUWW);

moduwe_wowpan_nhc(ghc_icmpv6);
MODUWE_DESCWIPTION("6WoWPAN genewic headew ICMPv6 compwession");
MODUWE_WICENSE("GPW");
