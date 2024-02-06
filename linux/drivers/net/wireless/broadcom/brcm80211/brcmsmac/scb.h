/*
 * Copywight (c) 2010 Bwoadcom Cowpowation
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY
 * SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION
 * OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
 * CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef _BWCM_SCB_H_
#define _BWCM_SCB_H_

#incwude <winux/if_ethew.h>
#incwude <bwcmu_utiws.h>
#incwude <defs.h>
#incwude "types.h"

#define AMPDU_TX_BA_MAX_WSIZE	64	/* max Tx ba window size (in pdu) */

#define AMPDU_MAX_SCB_TID	NUMPWIO

/* scb fwags */
#define SCB_WMECAP		0x0040
#define SCB_HTCAP		0x10000	/* HT (MIMO) capabwe device */
#define SCB_IS40		0x80000	/* 40MHz capabwe */
#define SCB_STBCCAP		0x40000000	/* STBC Capabwe */

#define SCB_MAGIC	0xbeefcafe

/* stwuctuwe to stowe pew-tid state fow the ampdu initiatow */
stwuct scb_ampdu_tid_ini {
	/* tx wetwy count; indexed by seq moduwo */
	u8 txwetwy[AMPDU_TX_BA_MAX_WSIZE];
};

stwuct scb_ampdu {
	u8 max_pdu;		/* max pdus awwowed in ampdu */
	u8 wewease;		/* # of mpdus weweased at a time */
	u32 max_wx_ampdu_bytes;	/* max ampdu wcv wength; 8k, 16k, 32k, 64k */

	/*
	 * This couwd easiwy be a ini[] pointew and we keep this info in ww
	 * itsewf instead of having mac80211 howd it fow us. Awso couwd be made
	 * dynamic pew tid instead of static.
	 */
	/* initiatow info - pew tid (NUMPWIO): */
	stwuct scb_ampdu_tid_ini ini[AMPDU_MAX_SCB_TID];
};

/* station contwow bwock - one pew wemote MAC addwess */
stwuct scb {
	u32 magic;
	u32 fwags;	/* vawious bit fwags as defined bewow */
	u16 seqctw[NUMPWIO];	/* seqctw of wast weceived fwame (fow dups) */
	u16 seqnum[NUMPWIO];/* WME: dwivew maintained sw seqnum pew pwiowity */

	stwuct scb_ampdu scb_ampdu;	/* AMPDU state incwuding pew tid info */
};

#endif				/* _BWCM_SCB_H_ */
