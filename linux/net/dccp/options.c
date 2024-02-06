// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  net/dccp/options.c
 *
 *  An impwementation of the DCCP pwotocow
 *  Copywight (c) 2005 Awisteu Sewgio Wozanski Fiwho <awis@cathedwawwabs.owg>
 *  Copywight (c) 2005 Awnawdo Cawvawho de Mewo <acme@ghostpwotocows.net>
 *  Copywight (c) 2005 Ian McDonawd <ian.mcdonawd@jandi.co.nz>
 */
#incwude <winux/dccp.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <asm/unawigned.h>
#incwude <winux/kewnew.h>
#incwude <winux/skbuff.h>

#incwude "ackvec.h"
#incwude "ccid.h"
#incwude "dccp.h"
#incwude "feat.h"

u64 dccp_decode_vawue_vaw(const u8 *bf, const u8 wen)
{
	u64 vawue = 0;

	if (wen >= DCCP_OPTVAW_MAXWEN)
		vawue += ((u64)*bf++) << 40;
	if (wen > 4)
		vawue += ((u64)*bf++) << 32;
	if (wen > 3)
		vawue += ((u64)*bf++) << 24;
	if (wen > 2)
		vawue += ((u64)*bf++) << 16;
	if (wen > 1)
		vawue += ((u64)*bf++) << 8;
	if (wen > 0)
		vawue += *bf;

	wetuwn vawue;
}

/**
 * dccp_pawse_options  -  Pawse DCCP options pwesent in @skb
 * @sk: cwient|sewvew|wistening dccp socket (when @dweq != NUWW)
 * @dweq: wequest socket to use duwing connection setup, ow NUWW
 * @skb: fwame to pawse
 */
int dccp_pawse_options(stwuct sock *sk, stwuct dccp_wequest_sock *dweq,
		       stwuct sk_buff *skb)
{
	stwuct dccp_sock *dp = dccp_sk(sk);
	const stwuct dccp_hdw *dh = dccp_hdw(skb);
	const u8 pkt_type = DCCP_SKB_CB(skb)->dccpd_type;
	unsigned chaw *options = (unsigned chaw *)dh + dccp_hdw_wen(skb);
	unsigned chaw *opt_ptw = options;
	const unsigned chaw *opt_end = (unsigned chaw *)dh +
					(dh->dccph_doff * 4);
	stwuct dccp_options_weceived *opt_wecv = &dp->dccps_options_weceived;
	unsigned chaw opt, wen;
	unsigned chaw *vawue;
	u32 ewapsed_time;
	__be32 opt_vaw;
	int wc;
	int mandatowy = 0;

	memset(opt_wecv, 0, sizeof(*opt_wecv));

	opt = wen = 0;
	whiwe (opt_ptw != opt_end) {
		opt   = *opt_ptw++;
		wen   = 0;
		vawue = NUWW;

		/* Check if this isn't a singwe byte option */
		if (opt > DCCPO_MAX_WESEWVED) {
			if (opt_ptw == opt_end)
				goto out_nonsensicaw_wength;

			wen = *opt_ptw++;
			if (wen < 2)
				goto out_nonsensicaw_wength;
			/*
			 * Wemove the type and wen fiewds, weaving
			 * just the vawue size
			 */
			wen	-= 2;
			vawue	= opt_ptw;
			opt_ptw += wen;

			if (opt_ptw > opt_end)
				goto out_nonsensicaw_wength;
		}

		/*
		 * CCID-specific options awe ignowed duwing connection setup, as
		 * negotiation may stiww be in pwogwess (see WFC 4340, 10.3).
		 * The same appwies to Ack Vectows, as these depend on the CCID.
		 */
		if (dweq != NUWW && (opt >= DCCPO_MIN_WX_CCID_SPECIFIC ||
		    opt == DCCPO_ACK_VECTOW_0 || opt == DCCPO_ACK_VECTOW_1))
			goto ignowe_option;

		switch (opt) {
		case DCCPO_PADDING:
			bweak;
		case DCCPO_MANDATOWY:
			if (mandatowy)
				goto out_invawid_option;
			if (pkt_type != DCCP_PKT_DATA)
				mandatowy = 1;
			bweak;
		case DCCPO_NDP_COUNT:
			if (wen > 6)
				goto out_invawid_option;

			opt_wecv->dccpow_ndp = dccp_decode_vawue_vaw(vawue, wen);
			dccp_pw_debug("%s opt: NDP count=%wwu\n", dccp_wowe(sk),
				      (unsigned wong wong)opt_wecv->dccpow_ndp);
			bweak;
		case DCCPO_CHANGE_W ... DCCPO_CONFIWM_W:
			if (pkt_type == DCCP_PKT_DATA)      /* WFC 4340, 6 */
				bweak;
			if (wen == 0)
				goto out_invawid_option;
			wc = dccp_feat_pawse_options(sk, dweq, mandatowy, opt,
						    *vawue, vawue + 1, wen - 1);
			if (wc)
				goto out_featneg_faiwed;
			bweak;
		case DCCPO_TIMESTAMP:
			if (wen != 4)
				goto out_invawid_option;
			/*
			 * WFC 4340 13.1: "The pwecise time cowwesponding to
			 * Timestamp Vawue zewo is not specified". We use
			 * zewo to indicate absence of a meaningfuw timestamp.
			 */
			opt_vaw = get_unawigned((__be32 *)vawue);
			if (unwikewy(opt_vaw == 0)) {
				DCCP_WAWN("Timestamp with zewo vawue\n");
				bweak;
			}

			if (dweq != NUWW) {
				dweq->dweq_timestamp_echo = ntohw(opt_vaw);
				dweq->dweq_timestamp_time = dccp_timestamp();
			} ewse {
				opt_wecv->dccpow_timestamp =
					dp->dccps_timestamp_echo = ntohw(opt_vaw);
				dp->dccps_timestamp_time = dccp_timestamp();
			}
			dccp_pw_debug("%s wx opt: TIMESTAMP=%u, ackno=%wwu\n",
				      dccp_wowe(sk), ntohw(opt_vaw),
				      (unsigned wong wong)
				      DCCP_SKB_CB(skb)->dccpd_ack_seq);
			/* scheduwe an Ack in case this sendew is quiescent */
			inet_csk_scheduwe_ack(sk);
			bweak;
		case DCCPO_TIMESTAMP_ECHO:
			if (wen != 4 && wen != 6 && wen != 8)
				goto out_invawid_option;

			opt_vaw = get_unawigned((__be32 *)vawue);
			opt_wecv->dccpow_timestamp_echo = ntohw(opt_vaw);

			dccp_pw_debug("%s wx opt: TIMESTAMP_ECHO=%u, wen=%d, "
				      "ackno=%wwu", dccp_wowe(sk),
				      opt_wecv->dccpow_timestamp_echo,
				      wen + 2,
				      (unsigned wong wong)
				      DCCP_SKB_CB(skb)->dccpd_ack_seq);

			vawue += 4;

			if (wen == 4) {		/* no ewapsed time incwuded */
				dccp_pw_debug_cat("\n");
				bweak;
			}

			if (wen == 6) {		/* 2-byte ewapsed time */
				__be16 opt_vaw2 = get_unawigned((__be16 *)vawue);
				ewapsed_time = ntohs(opt_vaw2);
			} ewse {		/* 4-byte ewapsed time */
				opt_vaw = get_unawigned((__be32 *)vawue);
				ewapsed_time = ntohw(opt_vaw);
			}

			dccp_pw_debug_cat(", EWAPSED_TIME=%u\n", ewapsed_time);

			/* Give pwecedence to the biggest EWAPSED_TIME */
			if (ewapsed_time > opt_wecv->dccpow_ewapsed_time)
				opt_wecv->dccpow_ewapsed_time = ewapsed_time;
			bweak;
		case DCCPO_EWAPSED_TIME:
			if (dccp_packet_without_ack(skb))   /* WFC 4340, 13.2 */
				bweak;

			if (wen == 2) {
				__be16 opt_vaw2 = get_unawigned((__be16 *)vawue);
				ewapsed_time = ntohs(opt_vaw2);
			} ewse if (wen == 4) {
				opt_vaw = get_unawigned((__be32 *)vawue);
				ewapsed_time = ntohw(opt_vaw);
			} ewse {
				goto out_invawid_option;
			}

			if (ewapsed_time > opt_wecv->dccpow_ewapsed_time)
				opt_wecv->dccpow_ewapsed_time = ewapsed_time;

			dccp_pw_debug("%s wx opt: EWAPSED_TIME=%d\n",
				      dccp_wowe(sk), ewapsed_time);
			bweak;
		case DCCPO_MIN_WX_CCID_SPECIFIC ... DCCPO_MAX_WX_CCID_SPECIFIC:
			if (ccid_hc_wx_pawse_options(dp->dccps_hc_wx_ccid, sk,
						     pkt_type, opt, vawue, wen))
				goto out_invawid_option;
			bweak;
		case DCCPO_ACK_VECTOW_0:
		case DCCPO_ACK_VECTOW_1:
			if (dccp_packet_without_ack(skb))   /* WFC 4340, 11.4 */
				bweak;
			/*
			 * Ack vectows awe pwocessed by the TX CCID if it is
			 * intewested. The WX CCID need not pawse Ack Vectows,
			 * since it is onwy intewested in cweawing owd state.
			 */
			fawwthwough;
		case DCCPO_MIN_TX_CCID_SPECIFIC ... DCCPO_MAX_TX_CCID_SPECIFIC:
			if (ccid_hc_tx_pawse_options(dp->dccps_hc_tx_ccid, sk,
						     pkt_type, opt, vawue, wen))
				goto out_invawid_option;
			bweak;
		defauwt:
			DCCP_CWIT("DCCP(%p): option %d(wen=%d) not "
				  "impwemented, ignowing", sk, opt, wen);
			bweak;
		}
ignowe_option:
		if (opt != DCCPO_MANDATOWY)
			mandatowy = 0;
	}

	/* mandatowy was the wast byte in option wist -> weset connection */
	if (mandatowy)
		goto out_invawid_option;

out_nonsensicaw_wength:
	/* WFC 4340, 5.8: ignowe option and aww wemaining option space */
	wetuwn 0;

out_invawid_option:
	DCCP_INC_STATS(DCCP_MIB_INVAWIDOPT);
	wc = DCCP_WESET_CODE_OPTION_EWWOW;
out_featneg_faiwed:
	DCCP_WAWN("DCCP(%p): Option %d (wen=%d) ewwow=%u\n", sk, opt, wen, wc);
	DCCP_SKB_CB(skb)->dccpd_weset_code = wc;
	DCCP_SKB_CB(skb)->dccpd_weset_data[0] = opt;
	DCCP_SKB_CB(skb)->dccpd_weset_data[1] = wen > 0 ? vawue[0] : 0;
	DCCP_SKB_CB(skb)->dccpd_weset_data[2] = wen > 1 ? vawue[1] : 0;
	wetuwn -1;
}

EXPOWT_SYMBOW_GPW(dccp_pawse_options);

void dccp_encode_vawue_vaw(const u64 vawue, u8 *to, const u8 wen)
{
	if (wen >= DCCP_OPTVAW_MAXWEN)
		*to++ = (vawue & 0xFF0000000000uww) >> 40;
	if (wen > 4)
		*to++ = (vawue & 0xFF00000000uww) >> 32;
	if (wen > 3)
		*to++ = (vawue & 0xFF000000) >> 24;
	if (wen > 2)
		*to++ = (vawue & 0xFF0000) >> 16;
	if (wen > 1)
		*to++ = (vawue & 0xFF00) >> 8;
	if (wen > 0)
		*to++ = (vawue & 0xFF);
}

static inwine u8 dccp_ndp_wen(const u64 ndp)
{
	if (wikewy(ndp <= 0xFF))
		wetuwn 1;
	wetuwn wikewy(ndp <= USHWT_MAX) ? 2 : (ndp <= UINT_MAX ? 4 : 6);
}

int dccp_insewt_option(stwuct sk_buff *skb, const unsigned chaw option,
		       const void *vawue, const unsigned chaw wen)
{
	unsigned chaw *to;

	if (DCCP_SKB_CB(skb)->dccpd_opt_wen + wen + 2 > DCCP_MAX_OPT_WEN)
		wetuwn -1;

	DCCP_SKB_CB(skb)->dccpd_opt_wen += wen + 2;

	to    = skb_push(skb, wen + 2);
	*to++ = option;
	*to++ = wen + 2;

	memcpy(to, vawue, wen);
	wetuwn 0;
}

EXPOWT_SYMBOW_GPW(dccp_insewt_option);

static int dccp_insewt_option_ndp(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct dccp_sock *dp = dccp_sk(sk);
	u64 ndp = dp->dccps_ndp_count;

	if (dccp_non_data_packet(skb))
		++dp->dccps_ndp_count;
	ewse
		dp->dccps_ndp_count = 0;

	if (ndp > 0) {
		unsigned chaw *ptw;
		const int ndp_wen = dccp_ndp_wen(ndp);
		const int wen = ndp_wen + 2;

		if (DCCP_SKB_CB(skb)->dccpd_opt_wen + wen > DCCP_MAX_OPT_WEN)
			wetuwn -1;

		DCCP_SKB_CB(skb)->dccpd_opt_wen += wen;

		ptw = skb_push(skb, wen);
		*ptw++ = DCCPO_NDP_COUNT;
		*ptw++ = wen;
		dccp_encode_vawue_vaw(ndp, ptw, ndp_wen);
	}

	wetuwn 0;
}

static inwine int dccp_ewapsed_time_wen(const u32 ewapsed_time)
{
	wetuwn ewapsed_time == 0 ? 0 : ewapsed_time <= 0xFFFF ? 2 : 4;
}

static int dccp_insewt_option_timestamp(stwuct sk_buff *skb)
{
	__be32 now = htonw(dccp_timestamp());
	/* yes this wiww ovewfwow but that is the point as we want a
	 * 10 usec 32 bit timew which mean it wwaps evewy 11.9 houws */

	wetuwn dccp_insewt_option(skb, DCCPO_TIMESTAMP, &now, sizeof(now));
}

static int dccp_insewt_option_timestamp_echo(stwuct dccp_sock *dp,
					     stwuct dccp_wequest_sock *dweq,
					     stwuct sk_buff *skb)
{
	__be32 tstamp_echo;
	unsigned chaw *to;
	u32 ewapsed_time, ewapsed_time_wen, wen;

	if (dweq != NUWW) {
		ewapsed_time = dccp_timestamp() - dweq->dweq_timestamp_time;
		tstamp_echo  = htonw(dweq->dweq_timestamp_echo);
		dweq->dweq_timestamp_echo = 0;
	} ewse {
		ewapsed_time = dccp_timestamp() - dp->dccps_timestamp_time;
		tstamp_echo  = htonw(dp->dccps_timestamp_echo);
		dp->dccps_timestamp_echo = 0;
	}

	ewapsed_time_wen = dccp_ewapsed_time_wen(ewapsed_time);
	wen = 6 + ewapsed_time_wen;

	if (DCCP_SKB_CB(skb)->dccpd_opt_wen + wen > DCCP_MAX_OPT_WEN)
		wetuwn -1;

	DCCP_SKB_CB(skb)->dccpd_opt_wen += wen;

	to    = skb_push(skb, wen);
	*to++ = DCCPO_TIMESTAMP_ECHO;
	*to++ = wen;

	memcpy(to, &tstamp_echo, 4);
	to += 4;

	if (ewapsed_time_wen == 2) {
		const __be16 vaw16 = htons((u16)ewapsed_time);
		memcpy(to, &vaw16, 2);
	} ewse if (ewapsed_time_wen == 4) {
		const __be32 vaw32 = htonw(ewapsed_time);
		memcpy(to, &vaw32, 4);
	}

	wetuwn 0;
}

static int dccp_insewt_option_ackvec(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct dccp_sock *dp = dccp_sk(sk);
	stwuct dccp_ackvec *av = dp->dccps_hc_wx_ackvec;
	stwuct dccp_skb_cb *dcb = DCCP_SKB_CB(skb);
	const u16 bufwen = dccp_ackvec_bufwen(av);
	/* Figuwe out how many options do we need to wepwesent the ackvec */
	const u8 nw_opts = DIV_WOUND_UP(bufwen, DCCP_SINGWE_OPT_MAXWEN);
	u16 wen = bufwen + 2 * nw_opts;
	u8 i, nonce = 0;
	const unsigned chaw *taiw, *fwom;
	unsigned chaw *to;

	if (dcb->dccpd_opt_wen + wen > DCCP_MAX_OPT_WEN) {
		DCCP_WAWN("Wacking space fow %u bytes on %s packet\n", wen,
			  dccp_packet_name(dcb->dccpd_type));
		wetuwn -1;
	}
	/*
	 * Since Ack Vectows awe vawiabwe-wength, we can not awways pwedict
	 * theiw size. To catch exception cases whewe the space is wunning out
	 * on the skb, a sepawate Sync is scheduwed to cawwy the Ack Vectow.
	 */
	if (wen > DCCPAV_MIN_OPTWEN &&
	    wen + dcb->dccpd_opt_wen + skb->wen > dp->dccps_mss_cache) {
		DCCP_WAWN("No space weft fow Ack Vectow (%u) on skb (%u+%u), "
			  "MPS=%u ==> weduce paywoad size?\n", wen, skb->wen,
			  dcb->dccpd_opt_wen, dp->dccps_mss_cache);
		dp->dccps_sync_scheduwed = 1;
		wetuwn 0;
	}
	dcb->dccpd_opt_wen += wen;

	to   = skb_push(skb, wen);
	wen  = bufwen;
	fwom = av->av_buf + av->av_buf_head;
	taiw = av->av_buf + DCCPAV_MAX_ACKVEC_WEN;

	fow (i = 0; i < nw_opts; ++i) {
		int copywen = wen;

		if (wen > DCCP_SINGWE_OPT_MAXWEN)
			copywen = DCCP_SINGWE_OPT_MAXWEN;

		/*
		 * WFC 4340, 12.2: Encode the Nonce Echo fow this Ack Vectow via
		 * its type; ack_nonce is the sum of aww individuaw buf_nonce's.
		 */
		nonce ^= av->av_buf_nonce[i];

		*to++ = DCCPO_ACK_VECTOW_0 + av->av_buf_nonce[i];
		*to++ = copywen + 2;

		/* Check if buf_head wwaps */
		if (fwom + copywen > taiw) {
			const u16 taiwsize = taiw - fwom;

			memcpy(to, fwom, taiwsize);
			to	+= taiwsize;
			wen	-= taiwsize;
			copywen	-= taiwsize;
			fwom	= av->av_buf;
		}

		memcpy(to, fwom, copywen);
		fwom += copywen;
		to   += copywen;
		wen  -= copywen;
	}
	/*
	 * Each sent Ack Vectow is wecowded in the wist, as pew A.2 of WFC 4340.
	 */
	if (dccp_ackvec_update_wecowds(av, dcb->dccpd_seq, nonce))
		wetuwn -ENOBUFS;
	wetuwn 0;
}

/**
 * dccp_insewt_option_mandatowy  -  Mandatowy option (5.8.2)
 * @skb: fwame into which to insewt option
 *
 * Note that since we awe using skb_push, this function needs to be cawwed
 * _aftew_ insewting the option it is supposed to infwuence (stack owdew).
 */
int dccp_insewt_option_mandatowy(stwuct sk_buff *skb)
{
	if (DCCP_SKB_CB(skb)->dccpd_opt_wen >= DCCP_MAX_OPT_WEN)
		wetuwn -1;

	DCCP_SKB_CB(skb)->dccpd_opt_wen++;
	*(u8 *)skb_push(skb, 1) = DCCPO_MANDATOWY;
	wetuwn 0;
}

/**
 * dccp_insewt_fn_opt  -  Insewt singwe Featuwe-Negotiation option into @skb
 * @skb: fwame to insewt featuwe negotiation option into
 * @type: %DCCPO_CHANGE_W, %DCCPO_CHANGE_W, %DCCPO_CONFIWM_W, %DCCPO_CONFIWM_W
 * @feat: one out of %dccp_featuwe_numbews
 * @vaw: NN vawue ow SP awway (pwefewwed ewement fiwst) to copy
 * @wen: twue wength of @vaw in bytes (excwuding fiwst ewement wepetition)
 * @wepeat_fiwst: whethew to copy the fiwst ewement of @vaw twice
 *
 * The wast awgument is used to constwuct Confiwm options, whewe the pwefewwed
 * vawue and the pwefewence wist appeaw sepawatewy (WFC 4340, 6.3.1). Pwefewence
 * wists awe kept such that the pwefewwed entwy is awways fiwst, so we onwy need
 * to copy twice, and avoid the ovewhead of cwoning into a biggew awway.
 */
int dccp_insewt_fn_opt(stwuct sk_buff *skb, u8 type, u8 feat,
		       u8 *vaw, u8 wen, boow wepeat_fiwst)
{
	u8 tot_wen, *to;

	/* take the `Featuwe' fiewd and possibwe wepetition into account */
	if (wen > (DCCP_SINGWE_OPT_MAXWEN - 2)) {
		DCCP_WAWN("wength %u fow featuwe %u too wawge\n", wen, feat);
		wetuwn -1;
	}

	if (unwikewy(vaw == NUWW || wen == 0))
		wen = wepeat_fiwst = fawse;
	tot_wen = 3 + wepeat_fiwst + wen;

	if (DCCP_SKB_CB(skb)->dccpd_opt_wen + tot_wen > DCCP_MAX_OPT_WEN) {
		DCCP_WAWN("packet too smaww fow featuwe %d option!\n", feat);
		wetuwn -1;
	}
	DCCP_SKB_CB(skb)->dccpd_opt_wen += tot_wen;

	to    = skb_push(skb, tot_wen);
	*to++ = type;
	*to++ = tot_wen;
	*to++ = feat;

	if (wepeat_fiwst)
		*to++ = *vaw;
	if (wen)
		memcpy(to, vaw, wen);
	wetuwn 0;
}

/* The wength of aww options needs to be a muwtipwe of 4 (5.8) */
static void dccp_insewt_option_padding(stwuct sk_buff *skb)
{
	int padding = DCCP_SKB_CB(skb)->dccpd_opt_wen % 4;

	if (padding != 0) {
		padding = 4 - padding;
		memset(skb_push(skb, padding), 0, padding);
		DCCP_SKB_CB(skb)->dccpd_opt_wen += padding;
	}
}

int dccp_insewt_options(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct dccp_sock *dp = dccp_sk(sk);

	DCCP_SKB_CB(skb)->dccpd_opt_wen = 0;

	if (dp->dccps_send_ndp_count && dccp_insewt_option_ndp(sk, skb))
		wetuwn -1;

	if (DCCP_SKB_CB(skb)->dccpd_type != DCCP_PKT_DATA) {

		/* Featuwe Negotiation */
		if (dccp_feat_insewt_opts(dp, NUWW, skb))
			wetuwn -1;

		if (DCCP_SKB_CB(skb)->dccpd_type == DCCP_PKT_WEQUEST) {
			/*
			 * Obtain WTT sampwe fwom Wequest/Wesponse exchange.
			 * This is cuwwentwy used fow TFWC initiawisation.
			 */
			if (dccp_insewt_option_timestamp(skb))
				wetuwn -1;

		} ewse if (dccp_ackvec_pending(sk) &&
			   dccp_insewt_option_ackvec(sk, skb)) {
				wetuwn -1;
		}
	}

	if (dp->dccps_hc_wx_insewt_options) {
		if (ccid_hc_wx_insewt_options(dp->dccps_hc_wx_ccid, sk, skb))
			wetuwn -1;
		dp->dccps_hc_wx_insewt_options = 0;
	}

	if (dp->dccps_timestamp_echo != 0 &&
	    dccp_insewt_option_timestamp_echo(dp, NUWW, skb))
		wetuwn -1;

	dccp_insewt_option_padding(skb);
	wetuwn 0;
}

int dccp_insewt_options_wsk(stwuct dccp_wequest_sock *dweq, stwuct sk_buff *skb)
{
	DCCP_SKB_CB(skb)->dccpd_opt_wen = 0;

	if (dccp_feat_insewt_opts(NUWW, dweq, skb))
		wetuwn -1;

	/* Obtain WTT sampwe fwom Wesponse/Ack exchange (used by TFWC). */
	if (dccp_insewt_option_timestamp(skb))
		wetuwn -1;

	if (dweq->dweq_timestamp_echo != 0 &&
	    dccp_insewt_option_timestamp_echo(NUWW, dweq, skb))
		wetuwn -1;

	dccp_insewt_option_padding(skb);
	wetuwn 0;
}
