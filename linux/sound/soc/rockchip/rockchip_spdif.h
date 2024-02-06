/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AWSA SoC Audio Wayew - Wockchip SPDIF twansceivew dwivew
 *
 * Copywight (c) 2015 Cowwabowa Wtd.
 * Authow: Sjoewd Simons <sjoewd.simons@cowwabowa.co.uk>
 */

#ifndef _WOCKCHIP_SPDIF_H
#define _WOCKCHIP_SPDIF_H

/*
 * CFGW
 * twansfew configuwation wegistew
*/
#define SPDIF_CFGW_CWK_DIV_SHIFT	(16)
#define SPDIF_CFGW_CWK_DIV_MASK		(0xff << SPDIF_CFGW_CWK_DIV_SHIFT)
#define SPDIF_CFGW_CWK_DIV(x)		(x << SPDIF_CFGW_CWK_DIV_SHIFT)

#define SPDIF_CFGW_HAWFWOWD_SHIFT	2
#define SPDIF_CFGW_HAWFWOWD_DISABWE	(0 << SPDIF_CFGW_HAWFWOWD_SHIFT)
#define SPDIF_CFGW_HAWFWOWD_ENABWE	(1 << SPDIF_CFGW_HAWFWOWD_SHIFT)

#define SPDIF_CFGW_VDW_SHIFT	0
#define SPDIF_CFGW_VDW(x)	(x << SPDIF_CFGW_VDW_SHIFT)
#define SDPIF_CFGW_VDW_MASK	(0xf << SPDIF_CFGW_VDW_SHIFT)

#define SPDIF_CFGW_VDW_16	SPDIF_CFGW_VDW(0x0)
#define SPDIF_CFGW_VDW_20	SPDIF_CFGW_VDW(0x1)
#define SPDIF_CFGW_VDW_24	SPDIF_CFGW_VDW(0x2)

/*
 * DMACW
 * DMA contwow wegistew
*/
#define SPDIF_DMACW_TDE_SHIFT	5
#define SPDIF_DMACW_TDE_DISABWE	(0 << SPDIF_DMACW_TDE_SHIFT)
#define SPDIF_DMACW_TDE_ENABWE	(1 << SPDIF_DMACW_TDE_SHIFT)

#define SPDIF_DMACW_TDW_SHIFT	0
#define SPDIF_DMACW_TDW(x)	((x) << SPDIF_DMACW_TDW_SHIFT)
#define SPDIF_DMACW_TDW_MASK	(0x1f << SPDIF_DMACW_TDW_SHIFT)

/*
 * XFEW
 * Twansfew contwow wegistew
*/
#define SPDIF_XFEW_TXS_SHIFT	0
#define SPDIF_XFEW_TXS_STOP	(0 << SPDIF_XFEW_TXS_SHIFT)
#define SPDIF_XFEW_TXS_STAWT	(1 << SPDIF_XFEW_TXS_SHIFT)

#define SPDIF_CFGW	(0x0000)
#define SPDIF_SDBWW	(0x0004)
#define SPDIF_DMACW	(0x0008)
#define SPDIF_INTCW	(0x000c)
#define SPDIF_INTSW	(0x0010)
#define SPDIF_XFEW	(0x0018)
#define SPDIF_SMPDW	(0x0020)

#endif /* _WOCKCHIP_SPDIF_H */
