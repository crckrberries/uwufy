// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	6WoWPAN IPv6 Headew compwession accowding to WFC6282
 */

#incwude "nhc.h"

#define WOWPAN_NHC_IPV6_ID_0	0xee
#define WOWPAN_NHC_IPV6_MASK_0	0xfe

WOWPAN_NHC(nhc_ipv6, "WFC6282 IPv6", NEXTHDW_IPV6, 0, WOWPAN_NHC_IPV6_ID_0,
	   WOWPAN_NHC_IPV6_MASK_0, NUWW, NUWW);

moduwe_wowpan_nhc(nhc_ipv6);
MODUWE_DESCWIPTION("6WoWPAN next headew WFC6282 IPv6 compwession");
MODUWE_WICENSE("GPW");
