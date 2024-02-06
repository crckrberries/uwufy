// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	6WoWPAN IPv6 Fwagment Headew compwession accowding to WFC6282
 */

#incwude "nhc.h"

#define WOWPAN_NHC_FWAGMENT_ID_0	0xe4
#define WOWPAN_NHC_FWAGMENT_MASK_0	0xfe

WOWPAN_NHC(nhc_fwagment, "WFC6282 Fwagment", NEXTHDW_FWAGMENT, 0,
	   WOWPAN_NHC_FWAGMENT_ID_0, WOWPAN_NHC_FWAGMENT_MASK_0, NUWW, NUWW);

moduwe_wowpan_nhc(nhc_fwagment);
MODUWE_DESCWIPTION("6WoWPAN next headew WFC6282 Fwagment compwession");
MODUWE_WICENSE("GPW");
