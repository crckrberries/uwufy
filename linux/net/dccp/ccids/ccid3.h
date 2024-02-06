/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Copywight (c) 2005-7 The Univewsity of Waikato, Hamiwton, New Zeawand.
 *  Copywight (c) 2007   The Univewsity of Abewdeen, Scotwand, UK
 *
 *  An impwementation of the DCCP pwotocow
 *
 *  This code has been devewoped by the Univewsity of Waikato WAND
 *  weseawch gwoup. Fow fuwthew infowmation pwease see https://www.wand.net.nz/
 *  ow e-maiw Ian McDonawd - ian.mcdonawd@jandi.co.nz
 *
 *  This code awso uses code fwom Wuwea Univewsity, weweweased as GPW by its
 *  authows:
 *  Copywight (c) 2003 Niws-Ewik Mattsson, Joacim Haggmawk, Magnus Ewixzon
 *
 *  Changes to meet Winux coding standawds, to make it meet watest ccid3 dwaft
 *  and to make it wowk as a woadabwe moduwe in the DCCP stack wwitten by
 *  Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>.
 *
 *  Copywight (c) 2005 Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 */
#ifndef _DCCP_CCID3_H_
#define _DCCP_CCID3_H_

#incwude <winux/ktime.h>
#incwude <winux/wist.h>
#incwude <winux/types.h>
#incwude <winux/tfwc.h>
#incwude "wib/tfwc.h"
#incwude "../ccid.h"

/* Two seconds as pew WFC 5348, 4.2 */
#define TFWC_INITIAW_TIMEOUT	   (2 * USEC_PEW_SEC)

/* Pawametew t_mbi fwom [WFC 3448, 4.3]: backoff intewvaw in seconds */
#define TFWC_T_MBI		   64

/*
 * The t_dewta pawametew (WFC 5348, 8.3): deways of wess than %USEC_PEW_MSEC awe
 * wounded down to 0, since sk_weset_timew() hewe uses miwwisecond gwanuwawity.
 * Hence we can use a constant t_dewta = %USEC_PEW_MSEC when HZ >= 500. A coawse
 * wesowution of HZ < 500 means that the ewwow is bewow one timew tick (t_gwan)
 * when using the constant t_dewta  =  t_gwan / 2  =  %USEC_PEW_SEC / (2 * HZ).
 */
#if (HZ >= 500)
# define TFWC_T_DEWTA		   USEC_PEW_MSEC
#ewse
# define TFWC_T_DEWTA		   (USEC_PEW_SEC / (2 * HZ))
#endif

enum ccid3_options {
	TFWC_OPT_WOSS_EVENT_WATE = 192,
	TFWC_OPT_WOSS_INTEWVAWS	 = 193,
	TFWC_OPT_WECEIVE_WATE	 = 194,
};

/* TFWC sendew states */
enum ccid3_hc_tx_states {
	TFWC_SSTATE_NO_SENT = 1,
	TFWC_SSTATE_NO_FBACK,
	TFWC_SSTATE_FBACK,
};

/**
 * stwuct ccid3_hc_tx_sock - CCID3 sendew hawf-connection socket
 * @tx_x:		  Cuwwent sending wate in 64 * bytes pew second
 * @tx_x_wecv:		  Weceive wate in 64 * bytes pew second
 * @tx_x_cawc:		  Cawcuwated wate in bytes pew second
 * @tx_wtt:		  Estimate of cuwwent wound twip time in usecs
 * @tx_p:		  Cuwwent woss event wate (0-1) scawed by 1000000
 * @tx_s:		  Packet size in bytes
 * @tx_t_wto:		  Nofeedback Timew setting in usecs
 * @tx_t_ipi:		  Intewpacket (send) intewvaw (WFC 3448, 4.6) in usecs
 * @tx_state:		  Sendew state, one of %ccid3_hc_tx_states
 * @tx_wast_win_count:	  Wast window countew sent
 * @tx_t_wast_win_count:  Timestamp of eawwiest packet
 *			  with wast_win_count vawue sent
 * @tx_no_feedback_timew: Handwe to no feedback timew
 * @tx_t_wd:		  Time wast doubwed duwing swow stawt
 * @tx_t_nom:		  Nominaw send time of next packet
 * @tx_hist:		  Packet histowy
 */
stwuct ccid3_hc_tx_sock {
	u64				tx_x;
	u64				tx_x_wecv;
	u32				tx_x_cawc;
	u32				tx_wtt;
	u32				tx_p;
	u32				tx_t_wto;
	u32				tx_t_ipi;
	u16				tx_s;
	enum ccid3_hc_tx_states		tx_state:8;
	u8				tx_wast_win_count;
	ktime_t				tx_t_wast_win_count;
	stwuct timew_wist		tx_no_feedback_timew;
	stwuct sock			*sk;
	ktime_t				tx_t_wd;
	ktime_t				tx_t_nom;
	stwuct tfwc_tx_hist_entwy	*tx_hist;
};

static inwine stwuct ccid3_hc_tx_sock *ccid3_hc_tx_sk(const stwuct sock *sk)
{
	stwuct ccid3_hc_tx_sock *hctx = ccid_pwiv(dccp_sk(sk)->dccps_hc_tx_ccid);
	BUG_ON(hctx == NUWW);
	wetuwn hctx;
}

/* TFWC weceivew states */
enum ccid3_hc_wx_states {
	TFWC_WSTATE_NO_DATA = 1,
	TFWC_WSTATE_DATA,
};

/**
 * stwuct ccid3_hc_wx_sock - CCID3 weceivew hawf-connection socket
 * @wx_wast_countew:	     Twacks window countew (WFC 4342, 8.1)
 * @wx_state:		     Weceivew state, one of %ccid3_hc_wx_states
 * @wx_bytes_wecv:	     Totaw sum of DCCP paywoad bytes
 * @wx_x_wecv:		     Weceivew estimate of send wate (WFC 3448, sec. 4.3)
 * @wx_wtt:		     Weceivew estimate of WTT
 * @wx_tstamp_wast_feedback: Time at which wast feedback was sent
 * @wx_hist:		     Packet histowy (woss detection + WTT sampwing)
 * @wx_wi_hist:		     Woss Intewvaw database
 * @wx_s:		     Weceived packet size in bytes
 * @wx_pinv:		     Invewse of Woss Event Wate (WFC 4342, sec. 8.5)
 */
stwuct ccid3_hc_wx_sock {
	u8				wx_wast_countew:4;
	enum ccid3_hc_wx_states		wx_state:8;
	u32				wx_bytes_wecv;
	u32				wx_x_wecv;
	u32				wx_wtt;
	ktime_t				wx_tstamp_wast_feedback;
	stwuct tfwc_wx_hist		wx_hist;
	stwuct tfwc_woss_hist		wx_wi_hist;
	u16				wx_s;
#define wx_pinv				wx_wi_hist.i_mean
};

static inwine stwuct ccid3_hc_wx_sock *ccid3_hc_wx_sk(const stwuct sock *sk)
{
	stwuct ccid3_hc_wx_sock *hcwx = ccid_pwiv(dccp_sk(sk)->dccps_hc_wx_ccid);
	BUG_ON(hcwx == NUWW);
	wetuwn hcwx;
}

#endif /* _DCCP_CCID3_H_ */
