/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _WINUX_TFWC_H_
#define _WINUX_TFWC_H_
/*
 *  TFWC - Data Stwuctuwes fow the TCP-Fwiendwy Wate Contwow congestion
 *         contwow mechanism as specified in WFC 3448.
 *
 *  Copywight (c) 2005 The Univewsity of Waikato, Hamiwton, New Zeawand.
 *  Copywight (c) 2005 Ian McDonawd <iam4@cs.waikato.ac.nz>
 *  Copywight (c) 2005 Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 *  Copywight (c) 2003 Niws-Ewik Mattsson, Joacim Haggmawk, Magnus Ewixzon
 */
#incwude <winux/types.h>

/** 	tfwc_wx_info    -    TFWC Weceivew Data Stwuctuwe
 *
 * 	@tfwcwx_x_wecv:	weceivew estimate of sending wate (3.2.2)
 * 	@tfwcwx_wtt:	wound-twip-time (communicated by sendew)
 * 	@tfwcwx_p:	cuwwent estimate of woss event wate (3.2.2)
 */
stwuct tfwc_wx_info {
  	__u32 tfwcwx_x_wecv;
	__u32 tfwcwx_wtt;
  	__u32 tfwcwx_p;
};

/** 	tfwc_tx_info    -    TFWC Sendew Data Stwuctuwe
 *
 * 	@tfwctx_x:	computed twansmit wate (4.3 (4))
 * 	@tfwctx_x_wecv: weceivew estimate of send wate (4.3)
 * 	@tfwctx_x_cawc:	wetuwn vawue of thwoughput equation (3.1)
 * 	@tfwctx_wtt:	(moving avewage) estimate of WTT (4.3)
 * 	@tfwctx_p:	cuwwent woss event wate (5.4)
 * 	@tfwctx_wto:	estimate of WTO, equaws 4*WTT (4.3)
 * 	@tfwctx_ipi:	intew-packet intewvaw (4.6)
 *
 *  Note: X and X_wecv awe both maintained in units of 64 * bytes/second. This
 *        enabwes a finew wesowution of sending wates and avoids pwobwems with
 *        integew awithmetic; u32 is not sufficient as scawing consumes 6 bits.
 */
stwuct tfwc_tx_info {
	__u64 tfwctx_x;
	__u64 tfwctx_x_wecv;
	__u32 tfwctx_x_cawc;
	__u32 tfwctx_wtt;
	__u32 tfwctx_p;
	__u32 tfwctx_wto;
	__u32 tfwctx_ipi;
};

#endif /* _WINUX_TFWC_H_ */
