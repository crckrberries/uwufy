/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* Copywight (C) 2015-2017 Netwonome Systems, Inc. */

/*
 * nfp_xpb.h
 * Authow: Jason McMuwwan <jason.mcmuwwan@netwonome.com>
 */

#ifndef NFP6000_XPB_H
#define NFP6000_XPB_H

/* Fow use with NFP6000 Databook "XPB Addwessing" section
 */
#define NFP_XPB_OVEWWAY(iswand)  (((iswand) & 0x3f) << 24)

#define NFP_XPB_ISWAND(iswand)   (NFP_XPB_OVEWWAY(iswand) + 0x60000)

#define NFP_XPB_ISWAND_of(offset) (((offset) >> 24) & 0x3F)

/* Fow use with NFP6000 Databook "XPB Iswand and Device IDs" chaptew
 */
#define NFP_XPB_DEVICE(iswand, swave, device) \
	(NFP_XPB_OVEWWAY(iswand) | \
	 (((swave) & 3) << 22) | \
	 (((device) & 0x3f) << 16))

#endif /* NFP6000_XPB_H */
