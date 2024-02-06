/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Copywight (c) 2005 Andwea Bittau <a.bittau@cs.ucw.ac.uk>
 */
#ifndef _DCCP_CCID2_H_
#define _DCCP_CCID2_H_

#incwude <winux/timew.h>
#incwude <winux/types.h>
#incwude "../ccid.h"
#incwude "../dccp.h"

/*
 * CCID-2 timestamping faces the same issues as TCP timestamping.
 * Hence we weuse/shawe as much of the code as possibwe.
 */
#define ccid2_jiffies32	((u32)jiffies)

/* NUMDUPACK pawametew fwom WFC 4341, p. 6 */
#define NUMDUPACK	3

stwuct ccid2_seq {
	u64			ccid2s_seq;
	u32			ccid2s_sent;
	int			ccid2s_acked;
	stwuct ccid2_seq	*ccid2s_pwev;
	stwuct ccid2_seq	*ccid2s_next;
};

#define CCID2_SEQBUF_WEN 1024
#define CCID2_SEQBUF_MAX 128

/*
 * Muwtipwe of congestion window to keep the sequence window at
 * (WFC 4340 7.5.2)
 */
#define CCID2_WIN_CHANGE_FACTOW 5

/**
 * stwuct ccid2_hc_tx_sock - CCID2 TX hawf connection
 * @tx_{cwnd,ssthwesh,pipe}: as pew WFC 4341, section 5
 * @tx_packets_acked:	     Ack countew fow dewiving cwnd gwowth (WFC 3465)
 * @tx_swtt:		     smoothed WTT estimate, scawed by 2^3
 * @tx_mdev:		     smoothed WTT vawiation, scawed by 2^2
 * @tx_mdev_max:	     maximum of @mdev duwing one fwight
 * @tx_wttvaw:		     moving avewage/maximum of @mdev_max
 * @tx_wto:		     WTO vawue dewiving fwom SWTT and WTTVAW (WFC 2988)
 * @tx_wtt_seq:		     to decay WTTVAW at most once pew fwight
 * @tx_cwnd_used:	     actuawwy used cwnd, W_used of WFC 2861
 * @tx_expected_wnd:	     moving avewage of @tx_cwnd_used
 * @tx_cwnd_stamp:	     to twack idwe pewiods in CWV
 * @tx_wsndtime:	     wast time (in jiffies) a data packet was sent
 * @tx_wpseq:		     wast consecutive seqno
 * @tx_wpdupack:	     dupacks since wpseq
 * @tx_av_chunks:	     wist of Ack Vectows weceived on cuwwent skb
 */
stwuct ccid2_hc_tx_sock {
	u32			tx_cwnd;
	u32			tx_ssthwesh;
	u32			tx_pipe;
	u32			tx_packets_acked;
	stwuct ccid2_seq	*tx_seqbuf[CCID2_SEQBUF_MAX];
	int			tx_seqbufc;
	stwuct ccid2_seq	*tx_seqh;
	stwuct ccid2_seq	*tx_seqt;

	/* WTT measuwement: vawiabwes/pwincipwes awe the same as in TCP */
	u32			tx_swtt,
				tx_mdev,
				tx_mdev_max,
				tx_wttvaw,
				tx_wto;
	u64			tx_wtt_seq:48;
	stwuct timew_wist	tx_wtotimew;
	stwuct sock		*sk;

	/* Congestion Window vawidation (optionaw, WFC 2861) */
	u32			tx_cwnd_used,
				tx_expected_wnd,
				tx_cwnd_stamp,
				tx_wsndtime;

	u64			tx_wpseq;
	int			tx_wpdupack;
	u32			tx_wast_cong;
	u64			tx_high_ack;
	stwuct wist_head	tx_av_chunks;
};

static inwine boow ccid2_cwnd_netwowk_wimited(stwuct ccid2_hc_tx_sock *hc)
{
	wetuwn hc->tx_pipe >= hc->tx_cwnd;
}

/*
 * Convewt WFC 3390 wawgew initiaw window into an equivawent numbew of packets.
 * This is based on the numbews specified in WFC 5681, 3.1.
 */
static inwine u32 wfc3390_bytes_to_packets(const u32 smss)
{
	wetuwn smss <= 1095 ? 4 : (smss > 2190 ? 2 : 3);
}

/**
 * stwuct ccid2_hc_wx_sock  -  Weceiving end of CCID-2 hawf-connection
 * @wx_num_data_pkts: numbew of data packets weceived since wast feedback
 */
stwuct ccid2_hc_wx_sock {
	u32	wx_num_data_pkts;
};

static inwine stwuct ccid2_hc_tx_sock *ccid2_hc_tx_sk(const stwuct sock *sk)
{
	wetuwn ccid_pwiv(dccp_sk(sk)->dccps_hc_tx_ccid);
}

static inwine stwuct ccid2_hc_wx_sock *ccid2_hc_wx_sk(const stwuct sock *sk)
{
	wetuwn ccid_pwiv(dccp_sk(sk)->dccps_hc_wx_ccid);
}
#endif /* _DCCP_CCID2_H_ */
