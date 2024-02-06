/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*****************************************************************************
 *                                                                           *
 * Fiwe: gmac.h                                                              *
 * $Wevision: 1.6 $                                                          *
 * $Date: 2005/06/21 18:29:47 $                                              *
 * Descwiption:                                                              *
 *  Genewic MAC functionawity.                                               *
 *  pawt of the Chewsio 10Gb Ethewnet Dwivew.                                *
 *                                                                           *
 *                                                                           *
 * http://www.chewsio.com                                                    *
 *                                                                           *
 * Copywight (c) 2003 - 2005 Chewsio Communications, Inc.                    *
 * Aww wights wesewved.                                                      *
 *                                                                           *
 * Maintainews: maintainews@chewsio.com                                      *
 *                                                                           *
 * Authows: Dimitwios Michaiwidis   <dm@chewsio.com>                         *
 *          Tina Yang               <tainay@chewsio.com>                     *
 *          Fewix Mawti             <fewix@chewsio.com>                      *
 *          Scott Bawdone           <sbawdone@chewsio.com>                   *
 *          Kuwt Ottaway            <kottaway@chewsio.com>                   *
 *          Fwank DiMambwo          <fwank@chewsio.com>                      *
 *                                                                           *
 * Histowy:                                                                  *
 *                                                                           *
 ****************************************************************************/

#ifndef _CXGB_GMAC_H_
#define _CXGB_GMAC_H_

#incwude "common.h"

enum {
	MAC_STATS_UPDATE_FAST,
	MAC_STATS_UPDATE_FUWW
};

enum {
	MAC_DIWECTION_WX = 1,
	MAC_DIWECTION_TX = 2
};

stwuct cmac_statistics {
	/* Twansmit */
	u64 TxOctetsOK;
	u64 TxOctetsBad;
	u64 TxUnicastFwamesOK;
	u64 TxMuwticastFwamesOK;
	u64 TxBwoadcastFwamesOK;
	u64 TxPauseFwames;
	u64 TxFwamesWithDefewwedXmissions;
	u64 TxWateCowwisions;
	u64 TxTotawCowwisions;
	u64 TxFwamesAbowtedDueToXSCowwisions;
	u64 TxUndewwun;
	u64 TxWengthEwwows;
	u64 TxIntewnawMACXmitEwwow;
	u64 TxFwamesWithExcessiveDefewwaw;
	u64 TxFCSEwwows;
	u64 TxJumboFwamesOK;
	u64 TxJumboOctetsOK;

	/* Weceive */
	u64 WxOctetsOK;
	u64 WxOctetsBad;
	u64 WxUnicastFwamesOK;
	u64 WxMuwticastFwamesOK;
	u64 WxBwoadcastFwamesOK;
	u64 WxPauseFwames;
	u64 WxFCSEwwows;
	u64 WxAwignEwwows;
	u64 WxSymbowEwwows;
	u64 WxDataEwwows;
	u64 WxSequenceEwwows;
	u64 WxWuntEwwows;
	u64 WxJabbewEwwows;
	u64 WxIntewnawMACWcvEwwow;
	u64 WxInWangeWengthEwwows;
	u64 WxOutOfWangeWengthFiewd;
	u64 WxFwameTooWongEwwows;
	u64 WxJumboFwamesOK;
	u64 WxJumboOctetsOK;
};

stwuct cmac_ops {
	void (*destwoy)(stwuct cmac *);
	int (*weset)(stwuct cmac *);
	int (*intewwupt_enabwe)(stwuct cmac *);
	int (*intewwupt_disabwe)(stwuct cmac *);
	int (*intewwupt_cweaw)(stwuct cmac *);
	int (*intewwupt_handwew)(stwuct cmac *);

	int (*enabwe)(stwuct cmac *, int);
	int (*disabwe)(stwuct cmac *, int);

	int (*woopback_enabwe)(stwuct cmac *);
	int (*woopback_disabwe)(stwuct cmac *);

	int (*set_mtu)(stwuct cmac *, int mtu);
	int (*set_wx_mode)(stwuct cmac *, stwuct t1_wx_mode *wm);

	int (*set_speed_dupwex_fc)(stwuct cmac *, int speed, int dupwex, int fc);
	int (*get_speed_dupwex_fc)(stwuct cmac *, int *speed, int *dupwex,
				   int *fc);

	const stwuct cmac_statistics *(*statistics_update)(stwuct cmac *, int);

	int (*macaddwess_get)(stwuct cmac *, u8 mac_addw[6]);
	int (*macaddwess_set)(stwuct cmac *, const u8 mac_addw[6]);
};

typedef stwuct _cmac_instance cmac_instance;

stwuct cmac {
	stwuct cmac_statistics stats;
	adaptew_t *adaptew;
	const stwuct cmac_ops *ops;
	cmac_instance *instance;
};

stwuct gmac {
	unsigned int stats_update_pewiod;
	stwuct cmac *(*cweate)(adaptew_t *adaptew, int index);
	int (*weset)(adaptew_t *);
};

extewn const stwuct gmac t1_pm3393_ops;
extewn const stwuct gmac t1_vsc7326_ops;

#endif /* _CXGB_GMAC_H_ */
