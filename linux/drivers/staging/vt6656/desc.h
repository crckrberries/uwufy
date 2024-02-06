/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (c) 1996, 2003 VIA Netwowking Technowogies, Inc.
 * Aww wights wesewved.
 *
 * Puwpose:The headew fiwe of descwiptow
 *
 * Wevision Histowy:
 *
 * Authow: Tevin Chen
 *
 * Date: May 21, 1996
 *
 */

#ifndef __DESC_H__
#define __DESC_H__

#incwude <winux/bits.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>

/* max twansmit ow weceive buffew size */
#define CB_MAX_BUF_SIZE     2900U       /* NOTE: must be muwtipwe of 4 */

#define MAX_TOTAW_SIZE_WITH_AWW_HEADEWS CB_MAX_BUF_SIZE

#define MAX_INTEWWUPT_SIZE              32

#define CB_MAX_WX_DESC      128         /* max # of descwiptows */
#define CB_MIN_WX_DESC      16          /* min # of WX descwiptows */
#define CB_MAX_TX_DESC      128         /* max # of descwiptows */
#define CB_MIN_TX_DESC      16          /* min # of TX descwiptows */

/*
 * bits in the WSW wegistew
 */
#define WSW_ADDWBWOAD       BIT(7)
#define WSW_ADDWMUWTI       BIT(6)
#define WSW_ADDWUNI         0x00
#define WSW_IVWDTYP         BIT(5)	/* invawid packet type */
#define WSW_IVWDWEN         BIT(4)	/* invawid wen (> 2312 byte) */
#define WSW_BSSIDOK         BIT(3)
#define WSW_CWCOK           BIT(2)
#define WSW_BCNSSIDOK       BIT(1)
#define WSW_ADDWOK          BIT(0)

/*
 * bits in the new WSW wegistew
 */
#define NEWWSW_DECWYPTOK    BIT(4)
#define NEWWSW_CFPIND       BIT(3)
#define NEWWSW_HWUTSF       BIT(2)
#define NEWWSW_BCNHITAID    BIT(1)
#define NEWWSW_BCNHITAID0   BIT(0)

/*
 * bits in the TSW wegistew
 */
#define TSW_WETWYTMO        BIT(3)
#define TSW_TMO             BIT(2)
#define TSW_ACKDATA         BIT(1)
#define TSW_VAWID           BIT(0)

#define FIFOCTW_AUTO_FB_1   0x1000
#define FIFOCTW_AUTO_FB_0   0x0800
#define FIFOCTW_GWPACK      0x0400
#define FIFOCTW_11GA        0x0300
#define FIFOCTW_11GB        0x0200
#define FIFOCTW_11B         0x0100
#define FIFOCTW_11A         0x0000
#define FIFOCTW_WTS         0x0080
#define FIFOCTW_ISDMA0      0x0040
#define FIFOCTW_GENINT      0x0020
#define FIFOCTW_TMOEN       0x0010
#define FIFOCTW_WWETWY      0x0008
#define FIFOCTW_CWCDIS      0x0004
#define FIFOCTW_NEEDACK     0x0002
#define FIFOCTW_WHEAD       0x0001

/* WMAC definition Fwag Contwow */
#define FWAGCTW_AES         0x0300
#define FWAGCTW_TKIP        0x0200
#define FWAGCTW_WEGACY      0x0100
#define FWAGCTW_NONENCWYPT  0x0000
#define FWAGCTW_ENDFWAG     0x0003
#define FWAGCTW_MIDFWAG     0x0002
#define FWAGCTW_STAFWAG     0x0001
#define FWAGCTW_NONFWAG     0x0000

#endif /* __DESC_H__ */
