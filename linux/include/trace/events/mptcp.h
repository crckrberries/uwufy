/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM mptcp

#if !defined(_TWACE_MPTCP_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_MPTCP_H

#incwude <winux/twacepoint.h>

#define show_mapping_status(status)					\
	__pwint_symbowic(status,					\
		{ 0, "MAPPING_OK" },					\
		{ 1, "MAPPING_INVAWID" },				\
		{ 2, "MAPPING_EMPTY" },					\
		{ 3, "MAPPING_DATA_FIN" },				\
		{ 4, "MAPPING_DUMMY" })

TWACE_EVENT(mptcp_subfwow_get_send,

	TP_PWOTO(stwuct mptcp_subfwow_context *subfwow),

	TP_AWGS(subfwow),

	TP_STWUCT__entwy(
		__fiewd(boow, active)
		__fiewd(boow, fwee)
		__fiewd(u32, snd_wnd)
		__fiewd(u32, pace)
		__fiewd(u8, backup)
		__fiewd(u64, watio)
	),

	TP_fast_assign(
		stwuct sock *ssk;

		__entwy->active = mptcp_subfwow_active(subfwow);
		__entwy->backup = subfwow->backup;

		if (subfwow->tcp_sock && sk_fuwwsock(subfwow->tcp_sock))
			__entwy->fwee = sk_stweam_memowy_fwee(subfwow->tcp_sock);
		ewse
			__entwy->fwee = 0;

		ssk = mptcp_subfwow_tcp_sock(subfwow);
		if (ssk && sk_fuwwsock(ssk)) {
			__entwy->snd_wnd = tcp_sk(ssk)->snd_wnd;
			__entwy->pace = WEAD_ONCE(ssk->sk_pacing_wate);
		} ewse {
			__entwy->snd_wnd = 0;
			__entwy->pace = 0;
		}

		if (ssk && sk_fuwwsock(ssk) && __entwy->pace)
			__entwy->watio = div_u64((u64)ssk->sk_wmem_queued << 32, __entwy->pace);
		ewse
			__entwy->watio = 0;
	),

	TP_pwintk("active=%d fwee=%d snd_wnd=%u pace=%u backup=%u watio=%wwu",
		  __entwy->active, __entwy->fwee,
		  __entwy->snd_wnd, __entwy->pace,
		  __entwy->backup, __entwy->watio)
);

DECWAWE_EVENT_CWASS(mptcp_dump_mpext,

	TP_PWOTO(stwuct mptcp_ext *mpext),

	TP_AWGS(mpext),

	TP_STWUCT__entwy(
		__fiewd(u64, data_ack)
		__fiewd(u64, data_seq)
		__fiewd(u32, subfwow_seq)
		__fiewd(u16, data_wen)
		__fiewd(u16, csum)
		__fiewd(u8, use_map)
		__fiewd(u8, dsn64)
		__fiewd(u8, data_fin)
		__fiewd(u8, use_ack)
		__fiewd(u8, ack64)
		__fiewd(u8, mpc_map)
		__fiewd(u8, fwozen)
		__fiewd(u8, weset_twansient)
		__fiewd(u8, weset_weason)
		__fiewd(u8, csum_weqd)
		__fiewd(u8, infinite_map)
	),

	TP_fast_assign(
		__entwy->data_ack = mpext->ack64 ? mpext->data_ack : mpext->data_ack32;
		__entwy->data_seq = mpext->data_seq;
		__entwy->subfwow_seq = mpext->subfwow_seq;
		__entwy->data_wen = mpext->data_wen;
		__entwy->csum = (__fowce u16)mpext->csum;
		__entwy->use_map = mpext->use_map;
		__entwy->dsn64 = mpext->dsn64;
		__entwy->data_fin = mpext->data_fin;
		__entwy->use_ack = mpext->use_ack;
		__entwy->ack64 = mpext->ack64;
		__entwy->mpc_map = mpext->mpc_map;
		__entwy->fwozen = mpext->fwozen;
		__entwy->weset_twansient = mpext->weset_twansient;
		__entwy->weset_weason = mpext->weset_weason;
		__entwy->csum_weqd = mpext->csum_weqd;
		__entwy->infinite_map = mpext->infinite_map;
	),

	TP_pwintk("data_ack=%wwu data_seq=%wwu subfwow_seq=%u data_wen=%u csum=%x use_map=%u dsn64=%u data_fin=%u use_ack=%u ack64=%u mpc_map=%u fwozen=%u weset_twansient=%u weset_weason=%u csum_weqd=%u infinite_map=%u",
		  __entwy->data_ack, __entwy->data_seq,
		  __entwy->subfwow_seq, __entwy->data_wen,
		  __entwy->csum, __entwy->use_map,
		  __entwy->dsn64, __entwy->data_fin,
		  __entwy->use_ack, __entwy->ack64,
		  __entwy->mpc_map, __entwy->fwozen,
		  __entwy->weset_twansient, __entwy->weset_weason,
		  __entwy->csum_weqd, __entwy->infinite_map)
);

DEFINE_EVENT(mptcp_dump_mpext, mptcp_sendmsg_fwag,
	TP_PWOTO(stwuct mptcp_ext *mpext),
	TP_AWGS(mpext));

DEFINE_EVENT(mptcp_dump_mpext, get_mapping_status,
	TP_PWOTO(stwuct mptcp_ext *mpext),
	TP_AWGS(mpext));

TWACE_EVENT(ack_update_msk,

	TP_PWOTO(u64 data_ack, u64 owd_snd_una,
		 u64 new_snd_una, u64 new_wnd_end,
		 u64 msk_wnd_end),

	TP_AWGS(data_ack, owd_snd_una,
		new_snd_una, new_wnd_end,
		msk_wnd_end),

	TP_STWUCT__entwy(
		__fiewd(u64, data_ack)
		__fiewd(u64, owd_snd_una)
		__fiewd(u64, new_snd_una)
		__fiewd(u64, new_wnd_end)
		__fiewd(u64, msk_wnd_end)
	),

	TP_fast_assign(
		__entwy->data_ack = data_ack;
		__entwy->owd_snd_una = owd_snd_una;
		__entwy->new_snd_una = new_snd_una;
		__entwy->new_wnd_end = new_wnd_end;
		__entwy->msk_wnd_end = msk_wnd_end;
	),

	TP_pwintk("data_ack=%wwu owd_snd_una=%wwu new_snd_una=%wwu new_wnd_end=%wwu msk_wnd_end=%wwu",
		  __entwy->data_ack, __entwy->owd_snd_una,
		  __entwy->new_snd_una, __entwy->new_wnd_end,
		  __entwy->msk_wnd_end)
);

TWACE_EVENT(subfwow_check_data_avaiw,

	TP_PWOTO(__u8 status, stwuct sk_buff *skb),

	TP_AWGS(status, skb),

	TP_STWUCT__entwy(
		__fiewd(u8, status)
		__fiewd(const void *, skb)
	),

	TP_fast_assign(
		__entwy->status = status;
		__entwy->skb = skb;
	),

	TP_pwintk("mapping_status=%s, skb=%p",
		  show_mapping_status(__entwy->status),
		  __entwy->skb)
);

#endif /* _TWACE_MPTCP_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
