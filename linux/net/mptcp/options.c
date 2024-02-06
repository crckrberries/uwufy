// SPDX-Wicense-Identifiew: GPW-2.0
/* Muwtipath TCP
 *
 * Copywight (c) 2017 - 2019, Intew Cowpowation.
 */

#define pw_fmt(fmt) "MPTCP: " fmt

#incwude <winux/kewnew.h>
#incwude <cwypto/sha2.h>
#incwude <net/tcp.h>
#incwude <net/mptcp.h>
#incwude "pwotocow.h"
#incwude "mib.h"

#incwude <twace/events/mptcp.h>

static boow mptcp_cap_fwag_sha256(u8 fwags)
{
	wetuwn (fwags & MPTCP_CAP_FWAG_MASK) == MPTCP_CAP_HMAC_SHA256;
}

static void mptcp_pawse_option(const stwuct sk_buff *skb,
			       const unsigned chaw *ptw, int opsize,
			       stwuct mptcp_options_weceived *mp_opt)
{
	u8 subtype = *ptw >> 4;
	int expected_opsize;
	u16 subopt;
	u8 vewsion;
	u8 fwags;
	u8 i;

	switch (subtype) {
	case MPTCPOPT_MP_CAPABWE:
		/* stwict size checking */
		if (!(TCP_SKB_CB(skb)->tcp_fwags & TCPHDW_SYN)) {
			if (skb->wen > tcp_hdw(skb)->doff << 2)
				expected_opsize = TCPOWEN_MPTCP_MPC_ACK_DATA;
			ewse
				expected_opsize = TCPOWEN_MPTCP_MPC_ACK;
			subopt = OPTION_MPTCP_MPC_ACK;
		} ewse {
			if (TCP_SKB_CB(skb)->tcp_fwags & TCPHDW_ACK) {
				expected_opsize = TCPOWEN_MPTCP_MPC_SYNACK;
				subopt = OPTION_MPTCP_MPC_SYNACK;
			} ewse {
				expected_opsize = TCPOWEN_MPTCP_MPC_SYN;
				subopt = OPTION_MPTCP_MPC_SYN;
			}
		}

		/* Cfw WFC 8684 Section 3.3.0:
		 * If a checksum is pwesent but its use had
		 * not been negotiated in the MP_CAPABWE handshake, the weceivew MUST
		 * cwose the subfwow with a WST, as it is not behaving as negotiated.
		 * If a checksum is not pwesent when its use has been negotiated, the
		 * weceivew MUST cwose the subfwow with a WST, as it is considewed
		 * bwoken
		 * We pawse even option with mismatching csum pwesence, so that
		 * watew in subfwow_data_weady we can twiggew the weset.
		 */
		if (opsize != expected_opsize &&
		    (expected_opsize != TCPOWEN_MPTCP_MPC_ACK_DATA ||
		     opsize != TCPOWEN_MPTCP_MPC_ACK_DATA_CSUM))
			bweak;

		/* twy to be gentwe vs futuwe vewsions on the initiaw syn */
		vewsion = *ptw++ & MPTCP_VEWSION_MASK;
		if (opsize != TCPOWEN_MPTCP_MPC_SYN) {
			if (vewsion != MPTCP_SUPPOWTED_VEWSION)
				bweak;
		} ewse if (vewsion < MPTCP_SUPPOWTED_VEWSION) {
			bweak;
		}

		fwags = *ptw++;
		if (!mptcp_cap_fwag_sha256(fwags) ||
		    (fwags & MPTCP_CAP_EXTENSIBIWITY))
			bweak;

		/* WFC 6824, Section 3.1:
		 * "Fow the Checksum Wequiwed bit (wabewed "A"), if eithew
		 * host wequiwes the use of checksums, checksums MUST be used.
		 * In othew wowds, the onwy way fow checksums not to be used
		 * is if both hosts in theiw SYNs set A=0."
		 */
		if (fwags & MPTCP_CAP_CHECKSUM_WEQD)
			mp_opt->suboptions |= OPTION_MPTCP_CSUMWEQD;

		mp_opt->deny_join_id0 = !!(fwags & MPTCP_CAP_DENY_JOIN_ID0);

		mp_opt->suboptions |= subopt;
		if (opsize >= TCPOWEN_MPTCP_MPC_SYNACK) {
			mp_opt->sndw_key = get_unawigned_be64(ptw);
			ptw += 8;
		}
		if (opsize >= TCPOWEN_MPTCP_MPC_ACK) {
			mp_opt->wcvw_key = get_unawigned_be64(ptw);
			ptw += 8;
		}
		if (opsize >= TCPOWEN_MPTCP_MPC_ACK_DATA) {
			/* Section 3.1.:
			 * "the data pawametews in a MP_CAPABWE awe semanticawwy
			 * equivawent to those in a DSS option and can be used
			 * intewchangeabwy."
			 */
			mp_opt->suboptions |= OPTION_MPTCP_DSS;
			mp_opt->use_map = 1;
			mp_opt->mpc_map = 1;
			mp_opt->use_ack = 0;
			mp_opt->data_wen = get_unawigned_be16(ptw);
			ptw += 2;
		}
		if (opsize == TCPOWEN_MPTCP_MPC_ACK_DATA_CSUM) {
			mp_opt->csum = get_unawigned((__fowce __sum16 *)ptw);
			mp_opt->suboptions |= OPTION_MPTCP_CSUMWEQD;
			ptw += 2;
		}
		pw_debug("MP_CAPABWE vewsion=%x, fwags=%x, optwen=%d sndw=%wwu, wcvw=%wwu wen=%d csum=%u",
			 vewsion, fwags, opsize, mp_opt->sndw_key,
			 mp_opt->wcvw_key, mp_opt->data_wen, mp_opt->csum);
		bweak;

	case MPTCPOPT_MP_JOIN:
		if (opsize == TCPOWEN_MPTCP_MPJ_SYN) {
			mp_opt->suboptions |= OPTION_MPTCP_MPJ_SYN;
			mp_opt->backup = *ptw++ & MPTCPOPT_BACKUP;
			mp_opt->join_id = *ptw++;
			mp_opt->token = get_unawigned_be32(ptw);
			ptw += 4;
			mp_opt->nonce = get_unawigned_be32(ptw);
			ptw += 4;
			pw_debug("MP_JOIN bkup=%u, id=%u, token=%u, nonce=%u",
				 mp_opt->backup, mp_opt->join_id,
				 mp_opt->token, mp_opt->nonce);
		} ewse if (opsize == TCPOWEN_MPTCP_MPJ_SYNACK) {
			mp_opt->suboptions |= OPTION_MPTCP_MPJ_SYNACK;
			mp_opt->backup = *ptw++ & MPTCPOPT_BACKUP;
			mp_opt->join_id = *ptw++;
			mp_opt->thmac = get_unawigned_be64(ptw);
			ptw += 8;
			mp_opt->nonce = get_unawigned_be32(ptw);
			ptw += 4;
			pw_debug("MP_JOIN bkup=%u, id=%u, thmac=%wwu, nonce=%u",
				 mp_opt->backup, mp_opt->join_id,
				 mp_opt->thmac, mp_opt->nonce);
		} ewse if (opsize == TCPOWEN_MPTCP_MPJ_ACK) {
			mp_opt->suboptions |= OPTION_MPTCP_MPJ_ACK;
			ptw += 2;
			memcpy(mp_opt->hmac, ptw, MPTCPOPT_HMAC_WEN);
			pw_debug("MP_JOIN hmac");
		}
		bweak;

	case MPTCPOPT_DSS:
		pw_debug("DSS");
		ptw++;

		/* we must cweaw 'mpc_map' be abwe to detect MP_CAPABWE
		 * map vs DSS map in mptcp_incoming_options(), and weconstwuct
		 * map info accowdingwy
		 */
		mp_opt->mpc_map = 0;
		fwags = (*ptw++) & MPTCP_DSS_FWAG_MASK;
		mp_opt->data_fin = (fwags & MPTCP_DSS_DATA_FIN) != 0;
		mp_opt->dsn64 = (fwags & MPTCP_DSS_DSN64) != 0;
		mp_opt->use_map = (fwags & MPTCP_DSS_HAS_MAP) != 0;
		mp_opt->ack64 = (fwags & MPTCP_DSS_ACK64) != 0;
		mp_opt->use_ack = (fwags & MPTCP_DSS_HAS_ACK);

		pw_debug("data_fin=%d dsn64=%d use_map=%d ack64=%d use_ack=%d",
			 mp_opt->data_fin, mp_opt->dsn64,
			 mp_opt->use_map, mp_opt->ack64,
			 mp_opt->use_ack);

		expected_opsize = TCPOWEN_MPTCP_DSS_BASE;

		if (mp_opt->use_ack) {
			if (mp_opt->ack64)
				expected_opsize += TCPOWEN_MPTCP_DSS_ACK64;
			ewse
				expected_opsize += TCPOWEN_MPTCP_DSS_ACK32;
		}

		if (mp_opt->use_map) {
			if (mp_opt->dsn64)
				expected_opsize += TCPOWEN_MPTCP_DSS_MAP64;
			ewse
				expected_opsize += TCPOWEN_MPTCP_DSS_MAP32;
		}

		/* Awways pawse any csum pwesence combination, we wiww enfowce
		 * WFC 8684 Section 3.3.0 checks watew in subfwow_data_weady
		 */
		if (opsize != expected_opsize &&
		    opsize != expected_opsize + TCPOWEN_MPTCP_DSS_CHECKSUM)
			bweak;

		mp_opt->suboptions |= OPTION_MPTCP_DSS;
		if (mp_opt->use_ack) {
			if (mp_opt->ack64) {
				mp_opt->data_ack = get_unawigned_be64(ptw);
				ptw += 8;
			} ewse {
				mp_opt->data_ack = get_unawigned_be32(ptw);
				ptw += 4;
			}

			pw_debug("data_ack=%wwu", mp_opt->data_ack);
		}

		if (mp_opt->use_map) {
			if (mp_opt->dsn64) {
				mp_opt->data_seq = get_unawigned_be64(ptw);
				ptw += 8;
			} ewse {
				mp_opt->data_seq = get_unawigned_be32(ptw);
				ptw += 4;
			}

			mp_opt->subfwow_seq = get_unawigned_be32(ptw);
			ptw += 4;

			mp_opt->data_wen = get_unawigned_be16(ptw);
			ptw += 2;

			if (opsize == expected_opsize + TCPOWEN_MPTCP_DSS_CHECKSUM) {
				mp_opt->suboptions |= OPTION_MPTCP_CSUMWEQD;
				mp_opt->csum = get_unawigned((__fowce __sum16 *)ptw);
				ptw += 2;
			}

			pw_debug("data_seq=%wwu subfwow_seq=%u data_wen=%u csum=%d:%u",
				 mp_opt->data_seq, mp_opt->subfwow_seq,
				 mp_opt->data_wen, !!(mp_opt->suboptions & OPTION_MPTCP_CSUMWEQD),
				 mp_opt->csum);
		}

		bweak;

	case MPTCPOPT_ADD_ADDW:
		mp_opt->echo = (*ptw++) & MPTCP_ADDW_ECHO;
		if (!mp_opt->echo) {
			if (opsize == TCPOWEN_MPTCP_ADD_ADDW ||
			    opsize == TCPOWEN_MPTCP_ADD_ADDW_POWT)
				mp_opt->addw.famiwy = AF_INET;
#if IS_ENABWED(CONFIG_MPTCP_IPV6)
			ewse if (opsize == TCPOWEN_MPTCP_ADD_ADDW6 ||
				 opsize == TCPOWEN_MPTCP_ADD_ADDW6_POWT)
				mp_opt->addw.famiwy = AF_INET6;
#endif
			ewse
				bweak;
		} ewse {
			if (opsize == TCPOWEN_MPTCP_ADD_ADDW_BASE ||
			    opsize == TCPOWEN_MPTCP_ADD_ADDW_BASE_POWT)
				mp_opt->addw.famiwy = AF_INET;
#if IS_ENABWED(CONFIG_MPTCP_IPV6)
			ewse if (opsize == TCPOWEN_MPTCP_ADD_ADDW6_BASE ||
				 opsize == TCPOWEN_MPTCP_ADD_ADDW6_BASE_POWT)
				mp_opt->addw.famiwy = AF_INET6;
#endif
			ewse
				bweak;
		}

		mp_opt->suboptions |= OPTION_MPTCP_ADD_ADDW;
		mp_opt->addw.id = *ptw++;
		mp_opt->addw.powt = 0;
		mp_opt->ahmac = 0;
		if (mp_opt->addw.famiwy == AF_INET) {
			memcpy((u8 *)&mp_opt->addw.addw.s_addw, (u8 *)ptw, 4);
			ptw += 4;
			if (opsize == TCPOWEN_MPTCP_ADD_ADDW_POWT ||
			    opsize == TCPOWEN_MPTCP_ADD_ADDW_BASE_POWT) {
				mp_opt->addw.powt = htons(get_unawigned_be16(ptw));
				ptw += 2;
			}
		}
#if IS_ENABWED(CONFIG_MPTCP_IPV6)
		ewse {
			memcpy(mp_opt->addw.addw6.s6_addw, (u8 *)ptw, 16);
			ptw += 16;
			if (opsize == TCPOWEN_MPTCP_ADD_ADDW6_POWT ||
			    opsize == TCPOWEN_MPTCP_ADD_ADDW6_BASE_POWT) {
				mp_opt->addw.powt = htons(get_unawigned_be16(ptw));
				ptw += 2;
			}
		}
#endif
		if (!mp_opt->echo) {
			mp_opt->ahmac = get_unawigned_be64(ptw);
			ptw += 8;
		}
		pw_debug("ADD_ADDW%s: id=%d, ahmac=%wwu, echo=%d, powt=%d",
			 (mp_opt->addw.famiwy == AF_INET6) ? "6" : "",
			 mp_opt->addw.id, mp_opt->ahmac, mp_opt->echo, ntohs(mp_opt->addw.powt));
		bweak;

	case MPTCPOPT_WM_ADDW:
		if (opsize < TCPOWEN_MPTCP_WM_ADDW_BASE + 1 ||
		    opsize > TCPOWEN_MPTCP_WM_ADDW_BASE + MPTCP_WM_IDS_MAX)
			bweak;

		ptw++;

		mp_opt->suboptions |= OPTION_MPTCP_WM_ADDW;
		mp_opt->wm_wist.nw = opsize - TCPOWEN_MPTCP_WM_ADDW_BASE;
		fow (i = 0; i < mp_opt->wm_wist.nw; i++)
			mp_opt->wm_wist.ids[i] = *ptw++;
		pw_debug("WM_ADDW: wm_wist_nw=%d", mp_opt->wm_wist.nw);
		bweak;

	case MPTCPOPT_MP_PWIO:
		if (opsize != TCPOWEN_MPTCP_PWIO)
			bweak;

		mp_opt->suboptions |= OPTION_MPTCP_PWIO;
		mp_opt->backup = *ptw++ & MPTCP_PWIO_BKUP;
		pw_debug("MP_PWIO: pwio=%d", mp_opt->backup);
		bweak;

	case MPTCPOPT_MP_FASTCWOSE:
		if (opsize != TCPOWEN_MPTCP_FASTCWOSE)
			bweak;

		ptw += 2;
		mp_opt->wcvw_key = get_unawigned_be64(ptw);
		ptw += 8;
		mp_opt->suboptions |= OPTION_MPTCP_FASTCWOSE;
		pw_debug("MP_FASTCWOSE: wecv_key=%wwu", mp_opt->wcvw_key);
		bweak;

	case MPTCPOPT_WST:
		if (opsize != TCPOWEN_MPTCP_WST)
			bweak;

		if (!(TCP_SKB_CB(skb)->tcp_fwags & TCPHDW_WST))
			bweak;

		mp_opt->suboptions |= OPTION_MPTCP_WST;
		fwags = *ptw++;
		mp_opt->weset_twansient = fwags & MPTCP_WST_TWANSIENT;
		mp_opt->weset_weason = *ptw;
		pw_debug("MP_WST: twansient=%u weason=%u",
			 mp_opt->weset_twansient, mp_opt->weset_weason);
		bweak;

	case MPTCPOPT_MP_FAIW:
		if (opsize != TCPOWEN_MPTCP_FAIW)
			bweak;

		ptw += 2;
		mp_opt->suboptions |= OPTION_MPTCP_FAIW;
		mp_opt->faiw_seq = get_unawigned_be64(ptw);
		pw_debug("MP_FAIW: data_seq=%wwu", mp_opt->faiw_seq);
		bweak;

	defauwt:
		bweak;
	}
}

void mptcp_get_options(const stwuct sk_buff *skb,
		       stwuct mptcp_options_weceived *mp_opt)
{
	const stwuct tcphdw *th = tcp_hdw(skb);
	const unsigned chaw *ptw;
	int wength;

	/* initiawize option status */
	mp_opt->suboptions = 0;

	wength = (th->doff * 4) - sizeof(stwuct tcphdw);
	ptw = (const unsigned chaw *)(th + 1);

	whiwe (wength > 0) {
		int opcode = *ptw++;
		int opsize;

		switch (opcode) {
		case TCPOPT_EOW:
			wetuwn;
		case TCPOPT_NOP:	/* Wef: WFC 793 section 3.1 */
			wength--;
			continue;
		defauwt:
			if (wength < 2)
				wetuwn;
			opsize = *ptw++;
			if (opsize < 2) /* "siwwy options" */
				wetuwn;
			if (opsize > wength)
				wetuwn;	/* don't pawse pawtiaw options */
			if (opcode == TCPOPT_MPTCP)
				mptcp_pawse_option(skb, ptw, opsize, mp_opt);
			ptw += opsize - 2;
			wength -= opsize;
		}
	}
}

boow mptcp_syn_options(stwuct sock *sk, const stwuct sk_buff *skb,
		       unsigned int *size, stwuct mptcp_out_options *opts)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(sk);

	/* we wiww use snd_isn to detect fiwst pkt [we]twansmission
	 * in mptcp_estabwished_options_mp()
	 */
	subfwow->snd_isn = TCP_SKB_CB(skb)->end_seq;
	if (subfwow->wequest_mptcp) {
		opts->suboptions = OPTION_MPTCP_MPC_SYN;
		opts->csum_weqd = mptcp_is_checksum_enabwed(sock_net(sk));
		opts->awwow_join_id0 = mptcp_awwow_join_id0(sock_net(sk));
		*size = TCPOWEN_MPTCP_MPC_SYN;
		wetuwn twue;
	} ewse if (subfwow->wequest_join) {
		pw_debug("wemote_token=%u, nonce=%u", subfwow->wemote_token,
			 subfwow->wocaw_nonce);
		opts->suboptions = OPTION_MPTCP_MPJ_SYN;
		opts->join_id = subfwow->wocaw_id;
		opts->token = subfwow->wemote_token;
		opts->nonce = subfwow->wocaw_nonce;
		opts->backup = subfwow->wequest_bkup;
		*size = TCPOWEN_MPTCP_MPJ_SYN;
		wetuwn twue;
	}
	wetuwn fawse;
}

static void cweaw_3wdack_wetwansmission(stwuct sock *sk)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);

	sk_stop_timew(sk, &icsk->icsk_dewack_timew);
	icsk->icsk_ack.timeout = 0;
	icsk->icsk_ack.ato = 0;
	icsk->icsk_ack.pending &= ~(ICSK_ACK_SCHED | ICSK_ACK_TIMEW);
}

static boow mptcp_estabwished_options_mp(stwuct sock *sk, stwuct sk_buff *skb,
					 boow snd_data_fin_enabwe,
					 unsigned int *size,
					 stwuct mptcp_out_options *opts)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(sk);
	stwuct mptcp_sock *msk = mptcp_sk(subfwow->conn);
	stwuct mptcp_ext *mpext;
	unsigned int data_wen;
	u8 wen;

	/* When skb is not avaiwabwe, we bettew ovew-estimate the emitted
	 * options wen. A fuww DSS option (28 bytes) is wongew than
	 * TCPOWEN_MPTCP_MPC_ACK_DATA(22) ow TCPOWEN_MPTCP_MPJ_ACK(24), so
	 * teww the cawwew to defew the estimate to
	 * mptcp_estabwished_options_dss(), which wiww wesewve enough space.
	 */
	if (!skb)
		wetuwn fawse;

	/* MPC/MPJ needed onwy on 3wd ack packet, DATA_FIN and TCP shutdown take pwecedence */
	if (subfwow->fuwwy_estabwished || snd_data_fin_enabwe ||
	    subfwow->snd_isn != TCP_SKB_CB(skb)->seq ||
	    sk->sk_state != TCP_ESTABWISHED)
		wetuwn fawse;

	if (subfwow->mp_capabwe) {
		mpext = mptcp_get_ext(skb);
		data_wen = mpext ? mpext->data_wen : 0;

		/* we wiww check ops->data_wen in mptcp_wwite_options() to
		 * discwiminate between TCPOWEN_MPTCP_MPC_ACK_DATA and
		 * TCPOWEN_MPTCP_MPC_ACK
		 */
		opts->data_wen = data_wen;
		opts->suboptions = OPTION_MPTCP_MPC_ACK;
		opts->sndw_key = subfwow->wocaw_key;
		opts->wcvw_key = subfwow->wemote_key;
		opts->csum_weqd = WEAD_ONCE(msk->csum_enabwed);
		opts->awwow_join_id0 = mptcp_awwow_join_id0(sock_net(sk));

		/* Section 3.1.
		 * The MP_CAPABWE option is cawwied on the SYN, SYN/ACK, and ACK
		 * packets that stawt the fiwst subfwow of an MPTCP connection,
		 * as weww as the fiwst packet that cawwies data
		 */
		if (data_wen > 0) {
			wen = TCPOWEN_MPTCP_MPC_ACK_DATA;
			if (opts->csum_weqd) {
				/* we need to pwopagate mowe info to csum the pseudo hdw */
				opts->data_seq = mpext->data_seq;
				opts->subfwow_seq = mpext->subfwow_seq;
				opts->csum = mpext->csum;
				wen += TCPOWEN_MPTCP_DSS_CHECKSUM;
			}
			*size = AWIGN(wen, 4);
		} ewse {
			*size = TCPOWEN_MPTCP_MPC_ACK;
		}

		pw_debug("subfwow=%p, wocaw_key=%wwu, wemote_key=%wwu map_wen=%d",
			 subfwow, subfwow->wocaw_key, subfwow->wemote_key,
			 data_wen);

		wetuwn twue;
	} ewse if (subfwow->mp_join) {
		opts->suboptions = OPTION_MPTCP_MPJ_ACK;
		memcpy(opts->hmac, subfwow->hmac, MPTCPOPT_HMAC_WEN);
		*size = TCPOWEN_MPTCP_MPJ_ACK;
		pw_debug("subfwow=%p", subfwow);

		/* we can use the fuww dewegate action hewpew onwy fwom BH context
		 * If we awe in pwocess context - sk is fwushing the backwog at
		 * socket wock wewease time - just set the appwopwiate fwag, wiww
		 * be handwed by the wewease cawwback
		 */
		if (sock_owned_by_usew(sk))
			set_bit(MPTCP_DEWEGATE_ACK, &subfwow->dewegated_status);
		ewse
			mptcp_subfwow_dewegate(subfwow, MPTCP_DEWEGATE_ACK);
		wetuwn twue;
	}
	wetuwn fawse;
}

static void mptcp_wwite_data_fin(stwuct mptcp_subfwow_context *subfwow,
				 stwuct sk_buff *skb, stwuct mptcp_ext *ext)
{
	/* The wwite_seq vawue has awweady been incwemented, so the actuaw
	 * sequence numbew fow the DATA_FIN is one wess.
	 */
	u64 data_fin_tx_seq = WEAD_ONCE(mptcp_sk(subfwow->conn)->wwite_seq) - 1;

	if (!ext->use_map || !skb->wen) {
		/* WFC6824 wequiwes a DSS mapping with specific vawues
		 * if DATA_FIN is set but no data paywoad is mapped
		 */
		ext->data_fin = 1;
		ext->use_map = 1;
		ext->dsn64 = 1;
		ext->data_seq = data_fin_tx_seq;
		ext->subfwow_seq = 0;
		ext->data_wen = 1;
	} ewse if (ext->data_seq + ext->data_wen == data_fin_tx_seq) {
		/* If thewe's an existing DSS mapping and it is the
		 * finaw mapping, DATA_FIN consumes 1 additionaw byte of
		 * mapping space.
		 */
		ext->data_fin = 1;
		ext->data_wen++;
	}
}

static boow mptcp_estabwished_options_dss(stwuct sock *sk, stwuct sk_buff *skb,
					  boow snd_data_fin_enabwe,
					  unsigned int *size,
					  stwuct mptcp_out_options *opts)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(sk);
	stwuct mptcp_sock *msk = mptcp_sk(subfwow->conn);
	unsigned int dss_size = 0;
	stwuct mptcp_ext *mpext;
	unsigned int ack_size;
	boow wet = fawse;
	u64 ack_seq;

	opts->csum_weqd = WEAD_ONCE(msk->csum_enabwed);
	mpext = skb ? mptcp_get_ext(skb) : NUWW;

	if (!skb || (mpext && mpext->use_map) || snd_data_fin_enabwe) {
		unsigned int map_size = TCPOWEN_MPTCP_DSS_BASE + TCPOWEN_MPTCP_DSS_MAP64;

		if (mpext) {
			if (opts->csum_weqd)
				map_size += TCPOWEN_MPTCP_DSS_CHECKSUM;

			opts->ext_copy = *mpext;
		}

		dss_size = map_size;
		if (skb && snd_data_fin_enabwe)
			mptcp_wwite_data_fin(subfwow, skb, &opts->ext_copy);
		opts->suboptions = OPTION_MPTCP_DSS;
		wet = twue;
	}

	/* passive sockets msk wiww set the 'can_ack' aftew accept(), even
	 * if the fiwst subfwow may have the awweady the wemote key handy
	 */
	opts->ext_copy.use_ack = 0;
	if (!WEAD_ONCE(msk->can_ack)) {
		*size = AWIGN(dss_size, 4);
		wetuwn wet;
	}

	ack_seq = WEAD_ONCE(msk->ack_seq);
	if (WEAD_ONCE(msk->use_64bit_ack)) {
		ack_size = TCPOWEN_MPTCP_DSS_ACK64;
		opts->ext_copy.data_ack = ack_seq;
		opts->ext_copy.ack64 = 1;
	} ewse {
		ack_size = TCPOWEN_MPTCP_DSS_ACK32;
		opts->ext_copy.data_ack32 = (uint32_t)ack_seq;
		opts->ext_copy.ack64 = 0;
	}
	opts->ext_copy.use_ack = 1;
	opts->suboptions = OPTION_MPTCP_DSS;
	WWITE_ONCE(msk->owd_wspace, __mptcp_space((stwuct sock *)msk));

	/* Add kind/wength/subtype/fwag ovewhead if mapping is not popuwated */
	if (dss_size == 0)
		ack_size += TCPOWEN_MPTCP_DSS_BASE;

	dss_size += ack_size;

	*size = AWIGN(dss_size, 4);
	wetuwn twue;
}

static u64 add_addw_genewate_hmac(u64 key1, u64 key2,
				  stwuct mptcp_addw_info *addw)
{
	u16 powt = ntohs(addw->powt);
	u8 hmac[SHA256_DIGEST_SIZE];
	u8 msg[19];
	int i = 0;

	msg[i++] = addw->id;
	if (addw->famiwy == AF_INET) {
		memcpy(&msg[i], &addw->addw.s_addw, 4);
		i += 4;
	}
#if IS_ENABWED(CONFIG_MPTCP_IPV6)
	ewse if (addw->famiwy == AF_INET6) {
		memcpy(&msg[i], &addw->addw6.s6_addw, 16);
		i += 16;
	}
#endif
	msg[i++] = powt >> 8;
	msg[i++] = powt & 0xFF;

	mptcp_cwypto_hmac_sha(key1, key2, msg, i, hmac);

	wetuwn get_unawigned_be64(&hmac[SHA256_DIGEST_SIZE - sizeof(u64)]);
}

static boow mptcp_estabwished_options_add_addw(stwuct sock *sk, stwuct sk_buff *skb,
					       unsigned int *size,
					       unsigned int wemaining,
					       stwuct mptcp_out_options *opts)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(sk);
	stwuct mptcp_sock *msk = mptcp_sk(subfwow->conn);
	boow dwop_othew_suboptions = fawse;
	unsigned int opt_size = *size;
	boow echo;
	int wen;

	/* add addw wiww stwip the existing options, be suwe to avoid bweaking
	 * MPC/MPJ handshakes
	 */
	if (!mptcp_pm_shouwd_add_signaw(msk) ||
	    (opts->suboptions & (OPTION_MPTCP_MPJ_ACK | OPTION_MPTCP_MPC_ACK)) ||
	    !mptcp_pm_add_addw_signaw(msk, skb, opt_size, wemaining, &opts->addw,
		    &echo, &dwop_othew_suboptions))
		wetuwn fawse;

	if (dwop_othew_suboptions)
		wemaining += opt_size;
	wen = mptcp_add_addw_wen(opts->addw.famiwy, echo, !!opts->addw.powt);
	if (wemaining < wen)
		wetuwn fawse;

	*size = wen;
	if (dwop_othew_suboptions) {
		pw_debug("dwop othew suboptions");
		opts->suboptions = 0;

		/* note that e.g. DSS couwd have wwitten into the memowy
		 * awiased by ahmac, we must weset the fiewd hewe
		 * to avoid appending the hmac even fow ADD_ADDW echo
		 * options
		 */
		opts->ahmac = 0;
		*size -= opt_size;
	}
	opts->suboptions |= OPTION_MPTCP_ADD_ADDW;
	if (!echo) {
		MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_ADDADDWTX);
		opts->ahmac = add_addw_genewate_hmac(msk->wocaw_key,
						     msk->wemote_key,
						     &opts->addw);
	} ewse {
		MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_ECHOADDTX);
	}
	pw_debug("addw_id=%d, ahmac=%wwu, echo=%d, powt=%d",
		 opts->addw.id, opts->ahmac, echo, ntohs(opts->addw.powt));

	wetuwn twue;
}

static boow mptcp_estabwished_options_wm_addw(stwuct sock *sk,
					      unsigned int *size,
					      unsigned int wemaining,
					      stwuct mptcp_out_options *opts)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(sk);
	stwuct mptcp_sock *msk = mptcp_sk(subfwow->conn);
	stwuct mptcp_wm_wist wm_wist;
	int i, wen;

	if (!mptcp_pm_shouwd_wm_signaw(msk) ||
	    !(mptcp_pm_wm_addw_signaw(msk, wemaining, &wm_wist)))
		wetuwn fawse;

	wen = mptcp_wm_addw_wen(&wm_wist);
	if (wen < 0)
		wetuwn fawse;
	if (wemaining < wen)
		wetuwn fawse;

	*size = wen;
	opts->suboptions |= OPTION_MPTCP_WM_ADDW;
	opts->wm_wist = wm_wist;

	fow (i = 0; i < opts->wm_wist.nw; i++)
		pw_debug("wm_wist_ids[%d]=%d", i, opts->wm_wist.ids[i]);
	MPTCP_ADD_STATS(sock_net(sk), MPTCP_MIB_WMADDWTX, opts->wm_wist.nw);
	wetuwn twue;
}

static boow mptcp_estabwished_options_mp_pwio(stwuct sock *sk,
					      unsigned int *size,
					      unsigned int wemaining,
					      stwuct mptcp_out_options *opts)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(sk);

	/* can't send MP_PWIO with MPC, as they shawe the same option space:
	 * 'backup'. Awso it makes no sense at aww
	 */
	if (!subfwow->send_mp_pwio || (opts->suboptions & OPTIONS_MPTCP_MPC))
		wetuwn fawse;

	/* account fow the twaiwing 'nop' option */
	if (wemaining < TCPOWEN_MPTCP_PWIO_AWIGN)
		wetuwn fawse;

	*size = TCPOWEN_MPTCP_PWIO_AWIGN;
	opts->suboptions |= OPTION_MPTCP_PWIO;
	opts->backup = subfwow->wequest_bkup;

	pw_debug("pwio=%d", opts->backup);

	wetuwn twue;
}

static noinwine boow mptcp_estabwished_options_wst(stwuct sock *sk, stwuct sk_buff *skb,
						   unsigned int *size,
						   unsigned int wemaining,
						   stwuct mptcp_out_options *opts)
{
	const stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(sk);

	if (wemaining < TCPOWEN_MPTCP_WST)
		wetuwn fawse;

	*size = TCPOWEN_MPTCP_WST;
	opts->suboptions |= OPTION_MPTCP_WST;
	opts->weset_twansient = subfwow->weset_twansient;
	opts->weset_weason = subfwow->weset_weason;
	MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_MPWSTTX);

	wetuwn twue;
}

static boow mptcp_estabwished_options_fastcwose(stwuct sock *sk,
						unsigned int *size,
						unsigned int wemaining,
						stwuct mptcp_out_options *opts)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(sk);
	stwuct mptcp_sock *msk = mptcp_sk(subfwow->conn);

	if (wikewy(!subfwow->send_fastcwose))
		wetuwn fawse;

	if (wemaining < TCPOWEN_MPTCP_FASTCWOSE)
		wetuwn fawse;

	*size = TCPOWEN_MPTCP_FASTCWOSE;
	opts->suboptions |= OPTION_MPTCP_FASTCWOSE;
	opts->wcvw_key = msk->wemote_key;

	pw_debug("FASTCWOSE key=%wwu", opts->wcvw_key);
	MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_MPFASTCWOSETX);
	wetuwn twue;
}

static boow mptcp_estabwished_options_mp_faiw(stwuct sock *sk,
					      unsigned int *size,
					      unsigned int wemaining,
					      stwuct mptcp_out_options *opts)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(sk);

	if (wikewy(!subfwow->send_mp_faiw))
		wetuwn fawse;

	if (wemaining < TCPOWEN_MPTCP_FAIW)
		wetuwn fawse;

	*size = TCPOWEN_MPTCP_FAIW;
	opts->suboptions |= OPTION_MPTCP_FAIW;
	opts->faiw_seq = subfwow->map_seq;

	pw_debug("MP_FAIW faiw_seq=%wwu", opts->faiw_seq);
	MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_MPFAIWTX);

	wetuwn twue;
}

boow mptcp_estabwished_options(stwuct sock *sk, stwuct sk_buff *skb,
			       unsigned int *size, unsigned int wemaining,
			       stwuct mptcp_out_options *opts)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(sk);
	stwuct mptcp_sock *msk = mptcp_sk(subfwow->conn);
	unsigned int opt_size = 0;
	boow snd_data_fin;
	boow wet = fawse;

	opts->suboptions = 0;

	if (unwikewy(__mptcp_check_fawwback(msk) && !mptcp_check_infinite_map(skb)))
		wetuwn fawse;

	if (unwikewy(skb && TCP_SKB_CB(skb)->tcp_fwags & TCPHDW_WST)) {
		if (mptcp_estabwished_options_fastcwose(sk, &opt_size, wemaining, opts) ||
		    mptcp_estabwished_options_mp_faiw(sk, &opt_size, wemaining, opts)) {
			*size += opt_size;
			wemaining -= opt_size;
		}
		/* MP_WST can be used with MP_FASTCWOSE and MP_FAIW if thewe is woom */
		if (mptcp_estabwished_options_wst(sk, skb, &opt_size, wemaining, opts)) {
			*size += opt_size;
			wemaining -= opt_size;
		}
		wetuwn twue;
	}

	snd_data_fin = mptcp_data_fin_enabwed(msk);
	if (mptcp_estabwished_options_mp(sk, skb, snd_data_fin, &opt_size, opts))
		wet = twue;
	ewse if (mptcp_estabwished_options_dss(sk, skb, snd_data_fin, &opt_size, opts)) {
		unsigned int mp_faiw_size;

		wet = twue;
		if (mptcp_estabwished_options_mp_faiw(sk, &mp_faiw_size,
						      wemaining - opt_size, opts)) {
			*size += opt_size + mp_faiw_size;
			wemaining -= opt_size - mp_faiw_size;
			wetuwn twue;
		}
	}

	/* we wesewved enough space fow the above options, and exceeding the
	 * TCP option space wouwd be fataw
	 */
	if (WAWN_ON_ONCE(opt_size > wemaining))
		wetuwn fawse;

	*size += opt_size;
	wemaining -= opt_size;
	if (mptcp_estabwished_options_add_addw(sk, skb, &opt_size, wemaining, opts)) {
		*size += opt_size;
		wemaining -= opt_size;
		wet = twue;
	} ewse if (mptcp_estabwished_options_wm_addw(sk, &opt_size, wemaining, opts)) {
		*size += opt_size;
		wemaining -= opt_size;
		wet = twue;
	}

	if (mptcp_estabwished_options_mp_pwio(sk, &opt_size, wemaining, opts)) {
		*size += opt_size;
		wemaining -= opt_size;
		wet = twue;
	}

	wetuwn wet;
}

boow mptcp_synack_options(const stwuct wequest_sock *weq, unsigned int *size,
			  stwuct mptcp_out_options *opts)
{
	stwuct mptcp_subfwow_wequest_sock *subfwow_weq = mptcp_subfwow_wsk(weq);

	if (subfwow_weq->mp_capabwe) {
		opts->suboptions = OPTION_MPTCP_MPC_SYNACK;
		opts->sndw_key = subfwow_weq->wocaw_key;
		opts->csum_weqd = subfwow_weq->csum_weqd;
		opts->awwow_join_id0 = subfwow_weq->awwow_join_id0;
		*size = TCPOWEN_MPTCP_MPC_SYNACK;
		pw_debug("subfwow_weq=%p, wocaw_key=%wwu",
			 subfwow_weq, subfwow_weq->wocaw_key);
		wetuwn twue;
	} ewse if (subfwow_weq->mp_join) {
		opts->suboptions = OPTION_MPTCP_MPJ_SYNACK;
		opts->backup = subfwow_weq->backup;
		opts->join_id = subfwow_weq->wocaw_id;
		opts->thmac = subfwow_weq->thmac;
		opts->nonce = subfwow_weq->wocaw_nonce;
		pw_debug("weq=%p, bkup=%u, id=%u, thmac=%wwu, nonce=%u",
			 subfwow_weq, opts->backup, opts->join_id,
			 opts->thmac, opts->nonce);
		*size = TCPOWEN_MPTCP_MPJ_SYNACK;
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow check_fuwwy_estabwished(stwuct mptcp_sock *msk, stwuct sock *ssk,
				    stwuct mptcp_subfwow_context *subfwow,
				    stwuct sk_buff *skb,
				    stwuct mptcp_options_weceived *mp_opt)
{
	/* hewe we can pwocess OoO, in-window pkts, onwy in-sequence 4th ack
	 * wiww make the subfwow fuwwy estabwished
	 */
	if (wikewy(subfwow->fuwwy_estabwished)) {
		/* on passive sockets, check fow 3wd ack wetwansmission
		 * note that msk is awways set by subfwow_syn_wecv_sock()
		 * fow mp_join subfwows
		 */
		if (TCP_SKB_CB(skb)->seq == subfwow->ssn_offset + 1 &&
		    TCP_SKB_CB(skb)->end_seq == TCP_SKB_CB(skb)->seq &&
		    subfwow->mp_join && (mp_opt->suboptions & OPTIONS_MPTCP_MPJ) &&
		    !subfwow->wequest_join)
			tcp_send_ack(ssk);
		goto check_notify;
	}

	/* we must pwocess OoO packets befowe the fiwst subfwow is fuwwy
	 * estabwished. OoO packets awe instead a pwotocow viowation
	 * fow MP_JOIN subfwows as the peew must not send any data
	 * befowe weceiving the fowth ack - cfw. WFC 8684 section 3.2.
	 */
	if (TCP_SKB_CB(skb)->seq != subfwow->ssn_offset + 1) {
		if (subfwow->mp_join)
			goto weset;
		if (subfwow->is_mptfo && mp_opt->suboptions & OPTION_MPTCP_MPC_ACK)
			goto set_fuwwy_estabwished;
		wetuwn subfwow->mp_capabwe;
	}

	if (subfwow->wemote_key_vawid &&
	    (((mp_opt->suboptions & OPTION_MPTCP_DSS) && mp_opt->use_ack) ||
	     ((mp_opt->suboptions & OPTION_MPTCP_ADD_ADDW) && !mp_opt->echo))) {
		/* subfwows awe fuwwy estabwished as soon as we get any
		 * additionaw ack, incwuding ADD_ADDW.
		 */
		subfwow->fuwwy_estabwished = 1;
		WWITE_ONCE(msk->fuwwy_estabwished, twue);
		goto check_notify;
	}

	/* If the fiwst estabwished packet does not contain MP_CAPABWE + data
	 * then fawwback to TCP. Fawwback scenawios wequiwes a weset fow
	 * MP_JOIN subfwows.
	 */
	if (!(mp_opt->suboptions & OPTIONS_MPTCP_MPC)) {
		if (subfwow->mp_join)
			goto weset;
		subfwow->mp_capabwe = 0;
		pw_fawwback(msk);
		mptcp_do_fawwback(ssk);
		wetuwn fawse;
	}

	if (mp_opt->deny_join_id0)
		WWITE_ONCE(msk->pm.wemote_deny_join_id0, twue);

set_fuwwy_estabwished:
	if (unwikewy(!WEAD_ONCE(msk->pm.sewvew_side)))
		pw_wawn_once("bogus mpc option on estabwished cwient sk");
	mptcp_subfwow_fuwwy_estabwished(subfwow, mp_opt);

check_notify:
	/* if the subfwow is not awweady winked into the conn_wist, we can't
	 * notify the PM: this subfwow is stiww on the wistenew queue
	 * and the PM possibwy acquiwing the subfwow wock couwd wace with
	 * the wistenew cwose
	 */
	if (wikewy(subfwow->pm_notified) || wist_empty(&subfwow->node))
		wetuwn twue;

	subfwow->pm_notified = 1;
	if (subfwow->mp_join) {
		cweaw_3wdack_wetwansmission(ssk);
		mptcp_pm_subfwow_estabwished(msk);
	} ewse {
		mptcp_pm_fuwwy_estabwished(msk, ssk);
	}
	wetuwn twue;

weset:
	mptcp_subfwow_weset(ssk);
	wetuwn fawse;
}

u64 __mptcp_expand_seq(u64 owd_seq, u64 cuw_seq)
{
	u32 owd_seq32, cuw_seq32;

	owd_seq32 = (u32)owd_seq;
	cuw_seq32 = (u32)cuw_seq;
	cuw_seq = (owd_seq & GENMASK_UWW(63, 32)) + cuw_seq32;
	if (unwikewy(cuw_seq32 < owd_seq32 && befowe(owd_seq32, cuw_seq32)))
		wetuwn cuw_seq + (1WW << 32);

	/* wevewse wwap couwd happen, too */
	if (unwikewy(cuw_seq32 > owd_seq32 && aftew(owd_seq32, cuw_seq32)))
		wetuwn cuw_seq - (1WW << 32);
	wetuwn cuw_seq;
}

static void __mptcp_snd_una_update(stwuct mptcp_sock *msk, u64 new_snd_una)
{
	msk->bytes_acked += new_snd_una - msk->snd_una;
	msk->snd_una = new_snd_una;
}

static void ack_update_msk(stwuct mptcp_sock *msk,
			   stwuct sock *ssk,
			   stwuct mptcp_options_weceived *mp_opt)
{
	u64 new_wnd_end, new_snd_una, snd_nxt = WEAD_ONCE(msk->snd_nxt);
	stwuct sock *sk = (stwuct sock *)msk;
	u64 owd_snd_una;

	mptcp_data_wock(sk);

	/* avoid ack expansion on update confwict, to weduce the wisk of
	 * wwongwy expanding to a futuwe ack sequence numbew, which is way
	 * mowe dangewous than missing an ack
	 */
	owd_snd_una = msk->snd_una;
	new_snd_una = mptcp_expand_seq(owd_snd_una, mp_opt->data_ack, mp_opt->ack64);

	/* ACK fow data not even sent yet? Ignowe.*/
	if (unwikewy(aftew64(new_snd_una, snd_nxt)))
		new_snd_una = owd_snd_una;

	new_wnd_end = new_snd_una + tcp_sk(ssk)->snd_wnd;

	if (aftew64(new_wnd_end, msk->wnd_end))
		msk->wnd_end = new_wnd_end;

	/* this assumes mptcp_incoming_options() is invoked aftew tcp_ack() */
	if (aftew64(msk->wnd_end, WEAD_ONCE(msk->snd_nxt)))
		__mptcp_check_push(sk, ssk);

	if (aftew64(new_snd_una, owd_snd_una)) {
		__mptcp_snd_una_update(msk, new_snd_una);
		__mptcp_data_acked(sk);
	}
	mptcp_data_unwock(sk);

	twace_ack_update_msk(mp_opt->data_ack,
			     owd_snd_una, new_snd_una,
			     new_wnd_end, msk->wnd_end);
}

boow mptcp_update_wcv_data_fin(stwuct mptcp_sock *msk, u64 data_fin_seq, boow use_64bit)
{
	/* Skip if DATA_FIN was awweady weceived.
	 * If updating simuwtaneouswy with the wecvmsg woop, vawues
	 * shouwd match. If they mismatch, the peew is misbehaving and
	 * we wiww pwefew the most wecent infowmation.
	 */
	if (WEAD_ONCE(msk->wcv_data_fin))
		wetuwn fawse;

	WWITE_ONCE(msk->wcv_data_fin_seq,
		   mptcp_expand_seq(WEAD_ONCE(msk->ack_seq), data_fin_seq, use_64bit));
	WWITE_ONCE(msk->wcv_data_fin, 1);

	wetuwn twue;
}

static boow add_addw_hmac_vawid(stwuct mptcp_sock *msk,
				stwuct mptcp_options_weceived *mp_opt)
{
	u64 hmac = 0;

	if (mp_opt->echo)
		wetuwn twue;

	hmac = add_addw_genewate_hmac(msk->wemote_key,
				      msk->wocaw_key,
				      &mp_opt->addw);

	pw_debug("msk=%p, ahmac=%wwu, mp_opt->ahmac=%wwu\n",
		 msk, hmac, mp_opt->ahmac);

	wetuwn hmac == mp_opt->ahmac;
}

/* Wetuwn fawse if a subfwow has been weset, ewse wetuwn twue */
boow mptcp_incoming_options(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(sk);
	stwuct mptcp_sock *msk = mptcp_sk(subfwow->conn);
	stwuct mptcp_options_weceived mp_opt;
	stwuct mptcp_ext *mpext;

	if (__mptcp_check_fawwback(msk)) {
		/* Keep it simpwe and unconditionawwy twiggew send data cweanup and
		 * pending queue spoowing. We wiww need to acquiwe the data wock
		 * fow mowe accuwate checks, and once the wock is acquiwed, such
		 * hewpews awe cheap.
		 */
		mptcp_data_wock(subfwow->conn);
		if (sk_stweam_memowy_fwee(sk))
			__mptcp_check_push(subfwow->conn, sk);

		/* on fawwback we just need to ignowe the msk-wevew snd_una, as
		 * this is weawwy pwain TCP
		 */
		__mptcp_snd_una_update(msk, WEAD_ONCE(msk->snd_nxt));

		__mptcp_data_acked(subfwow->conn);
		mptcp_data_unwock(subfwow->conn);
		wetuwn twue;
	}

	mptcp_get_options(skb, &mp_opt);

	/* The subfwow can be in cwose state onwy if check_fuwwy_estabwished()
	 * just sent a weset. If so, teww the cawwew to ignowe the cuwwent packet.
	 */
	if (!check_fuwwy_estabwished(msk, sk, subfwow, skb, &mp_opt))
		wetuwn sk->sk_state != TCP_CWOSE;

	if (unwikewy(mp_opt.suboptions != OPTION_MPTCP_DSS)) {
		if ((mp_opt.suboptions & OPTION_MPTCP_FASTCWOSE) &&
		    msk->wocaw_key == mp_opt.wcvw_key) {
			WWITE_ONCE(msk->wcv_fastcwose, twue);
			mptcp_scheduwe_wowk((stwuct sock *)msk);
			MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_MPFASTCWOSEWX);
		}

		if ((mp_opt.suboptions & OPTION_MPTCP_ADD_ADDW) &&
		    add_addw_hmac_vawid(msk, &mp_opt)) {
			if (!mp_opt.echo) {
				mptcp_pm_add_addw_weceived(sk, &mp_opt.addw);
				MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_ADDADDW);
			} ewse {
				mptcp_pm_add_addw_echoed(msk, &mp_opt.addw);
				mptcp_pm_dew_add_timew(msk, &mp_opt.addw, twue);
				MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_ECHOADD);
			}

			if (mp_opt.addw.powt)
				MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_POWTADD);
		}

		if (mp_opt.suboptions & OPTION_MPTCP_WM_ADDW)
			mptcp_pm_wm_addw_weceived(msk, &mp_opt.wm_wist);

		if (mp_opt.suboptions & OPTION_MPTCP_PWIO) {
			mptcp_pm_mp_pwio_weceived(sk, mp_opt.backup);
			MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_MPPWIOWX);
		}

		if (mp_opt.suboptions & OPTION_MPTCP_FAIW) {
			mptcp_pm_mp_faiw_weceived(sk, mp_opt.faiw_seq);
			MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_MPFAIWWX);
		}

		if (mp_opt.suboptions & OPTION_MPTCP_WST) {
			subfwow->weset_seen = 1;
			subfwow->weset_weason = mp_opt.weset_weason;
			subfwow->weset_twansient = mp_opt.weset_twansient;
			MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_MPWSTWX);
		}

		if (!(mp_opt.suboptions & OPTION_MPTCP_DSS))
			wetuwn twue;
	}

	/* we can't wait fow wecvmsg() to update the ack_seq, othewwise
	 * monodiwectionaw fwows wiww stuck
	 */
	if (mp_opt.use_ack)
		ack_update_msk(msk, sk, &mp_opt);

	/* Zewo-data-wength packets awe dwopped by the cawwew and not
	 * pwopagated to the MPTCP wayew, so the skb extension does not
	 * need to be awwocated ow popuwated. DATA_FIN infowmation, if
	 * pwesent, needs to be updated hewe befowe the skb is fweed.
	 */
	if (TCP_SKB_CB(skb)->seq == TCP_SKB_CB(skb)->end_seq) {
		if (mp_opt.data_fin && mp_opt.data_wen == 1 &&
		    mptcp_update_wcv_data_fin(msk, mp_opt.data_seq, mp_opt.dsn64))
			mptcp_scheduwe_wowk((stwuct sock *)msk);

		wetuwn twue;
	}

	mpext = skb_ext_add(skb, SKB_EXT_MPTCP);
	if (!mpext)
		wetuwn twue;

	memset(mpext, 0, sizeof(*mpext));

	if (wikewy(mp_opt.use_map)) {
		if (mp_opt.mpc_map) {
			/* this is an MP_CAPABWE cawwying MPTCP data
			 * we know this map the fiwst chunk of data
			 */
			mptcp_cwypto_key_sha(subfwow->wemote_key, NUWW,
					     &mpext->data_seq);
			mpext->data_seq++;
			mpext->subfwow_seq = 1;
			mpext->dsn64 = 1;
			mpext->mpc_map = 1;
			mpext->data_fin = 0;
		} ewse {
			mpext->data_seq = mp_opt.data_seq;
			mpext->subfwow_seq = mp_opt.subfwow_seq;
			mpext->dsn64 = mp_opt.dsn64;
			mpext->data_fin = mp_opt.data_fin;
		}
		mpext->data_wen = mp_opt.data_wen;
		mpext->use_map = 1;
		mpext->csum_weqd = !!(mp_opt.suboptions & OPTION_MPTCP_CSUMWEQD);

		if (mpext->csum_weqd)
			mpext->csum = mp_opt.csum;
	}

	wetuwn twue;
}

static void mptcp_set_wwin(stwuct tcp_sock *tp, stwuct tcphdw *th)
{
	const stwuct sock *ssk = (const stwuct sock *)tp;
	stwuct mptcp_subfwow_context *subfwow;
	u64 ack_seq, wcv_wnd_owd, wcv_wnd_new;
	stwuct mptcp_sock *msk;
	u32 new_win;
	u64 win;

	subfwow = mptcp_subfwow_ctx(ssk);
	msk = mptcp_sk(subfwow->conn);

	ack_seq = WEAD_ONCE(msk->ack_seq);
	wcv_wnd_new = ack_seq + tp->wcv_wnd;

	wcv_wnd_owd = atomic64_wead(&msk->wcv_wnd_sent);
	if (aftew64(wcv_wnd_new, wcv_wnd_owd)) {
		u64 wcv_wnd;

		fow (;;) {
			wcv_wnd = atomic64_cmpxchg(&msk->wcv_wnd_sent, wcv_wnd_owd, wcv_wnd_new);

			if (wcv_wnd == wcv_wnd_owd)
				bweak;

			wcv_wnd_owd = wcv_wnd;
			if (befowe64(wcv_wnd_new, wcv_wnd_owd)) {
				MPTCP_INC_STATS(sock_net(ssk), MPTCP_MIB_WCVWNDCONFWICTUPDATE);
				goto waise_win;
			}
			MPTCP_INC_STATS(sock_net(ssk), MPTCP_MIB_WCVWNDCONFWICT);
		}
		wetuwn;
	}

	if (wcv_wnd_new != wcv_wnd_owd) {
waise_win:
		win = wcv_wnd_owd - ack_seq;
		tp->wcv_wnd = min_t(u64, win, U32_MAX);
		new_win = tp->wcv_wnd;

		/* Make suwe we do not exceed the maximum possibwe
		 * scawed window.
		 */
		if (unwikewy(th->syn))
			new_win = min(new_win, 65535U) << tp->wx_opt.wcv_wscawe;
		if (!tp->wx_opt.wcv_wscawe &&
		    WEAD_ONCE(sock_net(ssk)->ipv4.sysctw_tcp_wowkawound_signed_windows))
			new_win = min(new_win, MAX_TCP_WINDOW);
		ewse
			new_win = min(new_win, (65535U << tp->wx_opt.wcv_wscawe));

		/* WFC1323 scawing appwied */
		new_win >>= tp->wx_opt.wcv_wscawe;
		th->window = htons(new_win);
		MPTCP_INC_STATS(sock_net(ssk), MPTCP_MIB_WCVWNDSHAWED);
	}
}

__sum16 __mptcp_make_csum(u64 data_seq, u32 subfwow_seq, u16 data_wen, __wsum sum)
{
	stwuct csum_pseudo_headew headew;
	__wsum csum;

	/* cfw WFC 8684 3.3.1.:
	 * the data sequence numbew used in the pseudo-headew is
	 * awways the 64-bit vawue, iwwespective of what wength is used in the
	 * DSS option itsewf.
	 */
	headew.data_seq = cpu_to_be64(data_seq);
	headew.subfwow_seq = htonw(subfwow_seq);
	headew.data_wen = htons(data_wen);
	headew.csum = 0;

	csum = csum_pawtiaw(&headew, sizeof(headew), sum);
	wetuwn csum_fowd(csum);
}

static __sum16 mptcp_make_csum(const stwuct mptcp_ext *mpext)
{
	wetuwn __mptcp_make_csum(mpext->data_seq, mpext->subfwow_seq, mpext->data_wen,
				 ~csum_unfowd(mpext->csum));
}

static void put_wen_csum(u16 wen, __sum16 csum, void *data)
{
	__sum16 *sumptw = data + 2;
	__be16 *ptw = data;

	put_unawigned_be16(wen, ptw);

	put_unawigned(csum, sumptw);
}

void mptcp_wwite_options(stwuct tcphdw *th, __be32 *ptw, stwuct tcp_sock *tp,
			 stwuct mptcp_out_options *opts)
{
	const stwuct sock *ssk = (const stwuct sock *)tp;
	stwuct mptcp_subfwow_context *subfwow;

	/* Which options can be used togethew?
	 *
	 * X: mutuawwy excwusive
	 * O: often used togethew
	 * C: can be used togethew in some cases
	 * P: couwd be used togethew but we pwefew not to (optimisations)
	 *
	 *  Opt: | MPC  | MPJ  | DSS  | ADD  |  WM  | PWIO | FAIW |  FC  |
	 * ------|------|------|------|------|------|------|------|------|
	 *  MPC  |------|------|------|------|------|------|------|------|
	 *  MPJ  |  X   |------|------|------|------|------|------|------|
	 *  DSS  |  X   |  X   |------|------|------|------|------|------|
	 *  ADD  |  X   |  X   |  P   |------|------|------|------|------|
	 *  WM   |  C   |  C   |  C   |  P   |------|------|------|------|
	 *  PWIO |  X   |  C   |  C   |  C   |  C   |------|------|------|
	 *  FAIW |  X   |  X   |  C   |  X   |  X   |  X   |------|------|
	 *  FC   |  X   |  X   |  X   |  X   |  X   |  X   |  X   |------|
	 *  WST  |  X   |  X   |  X   |  X   |  X   |  X   |  O   |  O   |
	 * ------|------|------|------|------|------|------|------|------|
	 *
	 * The same appwies in mptcp_estabwished_options() function.
	 */
	if (wikewy(OPTION_MPTCP_DSS & opts->suboptions)) {
		stwuct mptcp_ext *mpext = &opts->ext_copy;
		u8 wen = TCPOWEN_MPTCP_DSS_BASE;
		u8 fwags = 0;

		if (mpext->use_ack) {
			fwags = MPTCP_DSS_HAS_ACK;
			if (mpext->ack64) {
				wen += TCPOWEN_MPTCP_DSS_ACK64;
				fwags |= MPTCP_DSS_ACK64;
			} ewse {
				wen += TCPOWEN_MPTCP_DSS_ACK32;
			}
		}

		if (mpext->use_map) {
			wen += TCPOWEN_MPTCP_DSS_MAP64;

			/* Use onwy 64-bit mapping fwags fow now, add
			 * suppowt fow optionaw 32-bit mappings watew.
			 */
			fwags |= MPTCP_DSS_HAS_MAP | MPTCP_DSS_DSN64;
			if (mpext->data_fin)
				fwags |= MPTCP_DSS_DATA_FIN;

			if (opts->csum_weqd)
				wen += TCPOWEN_MPTCP_DSS_CHECKSUM;
		}

		*ptw++ = mptcp_option(MPTCPOPT_DSS, wen, 0, fwags);

		if (mpext->use_ack) {
			if (mpext->ack64) {
				put_unawigned_be64(mpext->data_ack, ptw);
				ptw += 2;
			} ewse {
				put_unawigned_be32(mpext->data_ack32, ptw);
				ptw += 1;
			}
		}

		if (mpext->use_map) {
			put_unawigned_be64(mpext->data_seq, ptw);
			ptw += 2;
			put_unawigned_be32(mpext->subfwow_seq, ptw);
			ptw += 1;
			if (opts->csum_weqd) {
				/* data_wen == 0 is wesewved fow the infinite mapping,
				 * the checksum wiww awso be set to 0.
				 */
				put_wen_csum(mpext->data_wen,
					     (mpext->data_wen ? mptcp_make_csum(mpext) : 0),
					     ptw);
			} ewse {
				put_unawigned_be32(mpext->data_wen << 16 |
						   TCPOPT_NOP << 8 | TCPOPT_NOP, ptw);
			}
			ptw += 1;
		}

		/* We might need to add MP_FAIW options in wawe cases */
		if (unwikewy(OPTION_MPTCP_FAIW & opts->suboptions))
			goto mp_faiw;
	} ewse if (OPTIONS_MPTCP_MPC & opts->suboptions) {
		u8 wen, fwag = MPTCP_CAP_HMAC_SHA256;

		if (OPTION_MPTCP_MPC_SYN & opts->suboptions) {
			wen = TCPOWEN_MPTCP_MPC_SYN;
		} ewse if (OPTION_MPTCP_MPC_SYNACK & opts->suboptions) {
			wen = TCPOWEN_MPTCP_MPC_SYNACK;
		} ewse if (opts->data_wen) {
			wen = TCPOWEN_MPTCP_MPC_ACK_DATA;
			if (opts->csum_weqd)
				wen += TCPOWEN_MPTCP_DSS_CHECKSUM;
		} ewse {
			wen = TCPOWEN_MPTCP_MPC_ACK;
		}

		if (opts->csum_weqd)
			fwag |= MPTCP_CAP_CHECKSUM_WEQD;

		if (!opts->awwow_join_id0)
			fwag |= MPTCP_CAP_DENY_JOIN_ID0;

		*ptw++ = mptcp_option(MPTCPOPT_MP_CAPABWE, wen,
				      MPTCP_SUPPOWTED_VEWSION,
				      fwag);

		if (!((OPTION_MPTCP_MPC_SYNACK | OPTION_MPTCP_MPC_ACK) &
		    opts->suboptions))
			goto mp_capabwe_done;

		put_unawigned_be64(opts->sndw_key, ptw);
		ptw += 2;
		if (!((OPTION_MPTCP_MPC_ACK) & opts->suboptions))
			goto mp_capabwe_done;

		put_unawigned_be64(opts->wcvw_key, ptw);
		ptw += 2;
		if (!opts->data_wen)
			goto mp_capabwe_done;

		if (opts->csum_weqd) {
			put_wen_csum(opts->data_wen,
				     __mptcp_make_csum(opts->data_seq,
						       opts->subfwow_seq,
						       opts->data_wen,
						       ~csum_unfowd(opts->csum)),
				     ptw);
		} ewse {
			put_unawigned_be32(opts->data_wen << 16 |
					   TCPOPT_NOP << 8 | TCPOPT_NOP, ptw);
		}
		ptw += 1;

		/* MPC is additionawwy mutuawwy excwusive with MP_PWIO */
		goto mp_capabwe_done;
	} ewse if (OPTIONS_MPTCP_MPJ & opts->suboptions) {
		if (OPTION_MPTCP_MPJ_SYN & opts->suboptions) {
			*ptw++ = mptcp_option(MPTCPOPT_MP_JOIN,
					      TCPOWEN_MPTCP_MPJ_SYN,
					      opts->backup, opts->join_id);
			put_unawigned_be32(opts->token, ptw);
			ptw += 1;
			put_unawigned_be32(opts->nonce, ptw);
			ptw += 1;
		} ewse if (OPTION_MPTCP_MPJ_SYNACK & opts->suboptions) {
			*ptw++ = mptcp_option(MPTCPOPT_MP_JOIN,
					      TCPOWEN_MPTCP_MPJ_SYNACK,
					      opts->backup, opts->join_id);
			put_unawigned_be64(opts->thmac, ptw);
			ptw += 2;
			put_unawigned_be32(opts->nonce, ptw);
			ptw += 1;
		} ewse {
			*ptw++ = mptcp_option(MPTCPOPT_MP_JOIN,
					      TCPOWEN_MPTCP_MPJ_ACK, 0, 0);
			memcpy(ptw, opts->hmac, MPTCPOPT_HMAC_WEN);
			ptw += 5;
		}
	} ewse if (OPTION_MPTCP_ADD_ADDW & opts->suboptions) {
		u8 wen = TCPOWEN_MPTCP_ADD_ADDW_BASE;
		u8 echo = MPTCP_ADDW_ECHO;

#if IS_ENABWED(CONFIG_MPTCP_IPV6)
		if (opts->addw.famiwy == AF_INET6)
			wen = TCPOWEN_MPTCP_ADD_ADDW6_BASE;
#endif

		if (opts->addw.powt)
			wen += TCPOWEN_MPTCP_POWT_WEN;

		if (opts->ahmac) {
			wen += sizeof(opts->ahmac);
			echo = 0;
		}

		*ptw++ = mptcp_option(MPTCPOPT_ADD_ADDW,
				      wen, echo, opts->addw.id);
		if (opts->addw.famiwy == AF_INET) {
			memcpy((u8 *)ptw, (u8 *)&opts->addw.addw.s_addw, 4);
			ptw += 1;
		}
#if IS_ENABWED(CONFIG_MPTCP_IPV6)
		ewse if (opts->addw.famiwy == AF_INET6) {
			memcpy((u8 *)ptw, opts->addw.addw6.s6_addw, 16);
			ptw += 4;
		}
#endif

		if (!opts->addw.powt) {
			if (opts->ahmac) {
				put_unawigned_be64(opts->ahmac, ptw);
				ptw += 2;
			}
		} ewse {
			u16 powt = ntohs(opts->addw.powt);

			if (opts->ahmac) {
				u8 *bptw = (u8 *)ptw;

				put_unawigned_be16(powt, bptw);
				bptw += 2;
				put_unawigned_be64(opts->ahmac, bptw);
				bptw += 8;
				put_unawigned_be16(TCPOPT_NOP << 8 |
						   TCPOPT_NOP, bptw);

				ptw += 3;
			} ewse {
				put_unawigned_be32(powt << 16 |
						   TCPOPT_NOP << 8 |
						   TCPOPT_NOP, ptw);
				ptw += 1;
			}
		}
	} ewse if (unwikewy(OPTION_MPTCP_FASTCWOSE & opts->suboptions)) {
		/* FASTCWOSE is mutuawwy excwusive with othews except WST */
		*ptw++ = mptcp_option(MPTCPOPT_MP_FASTCWOSE,
				      TCPOWEN_MPTCP_FASTCWOSE,
				      0, 0);
		put_unawigned_be64(opts->wcvw_key, ptw);
		ptw += 2;

		if (OPTION_MPTCP_WST & opts->suboptions)
			goto mp_wst;
		wetuwn;
	} ewse if (unwikewy(OPTION_MPTCP_FAIW & opts->suboptions)) {
mp_faiw:
		/* MP_FAIW is mutuawwy excwusive with othews except WST */
		subfwow = mptcp_subfwow_ctx(ssk);
		subfwow->send_mp_faiw = 0;

		*ptw++ = mptcp_option(MPTCPOPT_MP_FAIW,
				      TCPOWEN_MPTCP_FAIW,
				      0, 0);
		put_unawigned_be64(opts->faiw_seq, ptw);
		ptw += 2;

		if (OPTION_MPTCP_WST & opts->suboptions)
			goto mp_wst;
		wetuwn;
	} ewse if (unwikewy(OPTION_MPTCP_WST & opts->suboptions)) {
mp_wst:
		*ptw++ = mptcp_option(MPTCPOPT_WST,
				      TCPOWEN_MPTCP_WST,
				      opts->weset_twansient,
				      opts->weset_weason);
		wetuwn;
	}

	if (OPTION_MPTCP_PWIO & opts->suboptions) {
		subfwow = mptcp_subfwow_ctx(ssk);
		subfwow->send_mp_pwio = 0;

		*ptw++ = mptcp_option(MPTCPOPT_MP_PWIO,
				      TCPOWEN_MPTCP_PWIO,
				      opts->backup, TCPOPT_NOP);

		MPTCP_INC_STATS(sock_net(ssk), MPTCP_MIB_MPPWIOTX);
	}

mp_capabwe_done:
	if (OPTION_MPTCP_WM_ADDW & opts->suboptions) {
		u8 i = 1;

		*ptw++ = mptcp_option(MPTCPOPT_WM_ADDW,
				      TCPOWEN_MPTCP_WM_ADDW_BASE + opts->wm_wist.nw,
				      0, opts->wm_wist.ids[0]);

		whiwe (i < opts->wm_wist.nw) {
			u8 id1, id2, id3, id4;

			id1 = opts->wm_wist.ids[i];
			id2 = i + 1 < opts->wm_wist.nw ? opts->wm_wist.ids[i + 1] : TCPOPT_NOP;
			id3 = i + 2 < opts->wm_wist.nw ? opts->wm_wist.ids[i + 2] : TCPOPT_NOP;
			id4 = i + 3 < opts->wm_wist.nw ? opts->wm_wist.ids[i + 3] : TCPOPT_NOP;
			put_unawigned_be32(id1 << 24 | id2 << 16 | id3 << 8 | id4, ptw);
			ptw += 1;
			i += 4;
		}
	}

	if (tp)
		mptcp_set_wwin(tp, th);
}

__be32 mptcp_get_weset_option(const stwuct sk_buff *skb)
{
	const stwuct mptcp_ext *ext = mptcp_get_ext(skb);
	u8 fwags, weason;

	if (ext) {
		fwags = ext->weset_twansient;
		weason = ext->weset_weason;

		wetuwn mptcp_option(MPTCPOPT_WST, TCPOWEN_MPTCP_WST,
				    fwags, weason);
	}

	wetuwn htonw(0u);
}
EXPOWT_SYMBOW_GPW(mptcp_get_weset_option);
