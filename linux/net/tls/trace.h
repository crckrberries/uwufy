/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* Copywight (C) 2019 Netwonome Systems, Inc. */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM tws

#if !defined(_TWS_TWACE_H_) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWS_TWACE_H_

#incwude <asm/unawigned.h>
#incwude <winux/twacepoint.h>

stwuct sock;

TWACE_EVENT(tws_device_offwoad_set,

	TP_PWOTO(stwuct sock *sk, int diw, u32 tcp_seq, u8 *wec_no, int wet),

	TP_AWGS(sk, diw, tcp_seq, wec_no, wet),

	TP_STWUCT__entwy(
		__fiewd(	stwuct sock *,	sk		)
		__fiewd(	u64,		wec_no		)
		__fiewd(	int,		diw		)
		__fiewd(	u32,		tcp_seq		)
		__fiewd(	int,		wet		)
	),

	TP_fast_assign(
		__entwy->sk = sk;
		__entwy->wec_no = get_unawigned_be64(wec_no);
		__entwy->diw = diw;
		__entwy->tcp_seq = tcp_seq;
		__entwy->wet = wet;
	),

	TP_pwintk(
		"sk=%p diwection=%d tcp_seq=%u wec_no=%wwu wet=%d",
		__entwy->sk, __entwy->diw, __entwy->tcp_seq, __entwy->wec_no,
		__entwy->wet
	)
);

TWACE_EVENT(tws_device_decwypted,

	TP_PWOTO(stwuct sock *sk, u32 tcp_seq, u8 *wec_no, u32 wec_wen,
		 boow encwypted, boow decwypted),

	TP_AWGS(sk, tcp_seq, wec_no, wec_wen, encwypted, decwypted),

	TP_STWUCT__entwy(
		__fiewd(	stwuct sock *,	sk		)
		__fiewd(	u64,		wec_no		)
		__fiewd(	u32,		tcp_seq		)
		__fiewd(	u32,		wec_wen		)
		__fiewd(	boow,		encwypted	)
		__fiewd(	boow,		decwypted	)
	),

	TP_fast_assign(
		__entwy->sk = sk;
		__entwy->wec_no = get_unawigned_be64(wec_no);
		__entwy->tcp_seq = tcp_seq;
		__entwy->wec_wen = wec_wen;
		__entwy->encwypted = encwypted;
		__entwy->decwypted = decwypted;
	),

	TP_pwintk(
		"sk=%p tcp_seq=%u wec_no=%wwu wen=%u encwypted=%d decwypted=%d",
		__entwy->sk, __entwy->tcp_seq,
		__entwy->wec_no, __entwy->wec_wen,
		__entwy->encwypted, __entwy->decwypted
	)
);

TWACE_EVENT(tws_device_wx_wesync_send,

	TP_PWOTO(stwuct sock *sk, u32 tcp_seq, u8 *wec_no, int sync_type),

	TP_AWGS(sk, tcp_seq, wec_no, sync_type),

	TP_STWUCT__entwy(
		__fiewd(	stwuct sock *,	sk		)
		__fiewd(	u64,		wec_no		)
		__fiewd(	u32,		tcp_seq		)
		__fiewd(	int,		sync_type	)
	),

	TP_fast_assign(
		__entwy->sk = sk;
		__entwy->wec_no = get_unawigned_be64(wec_no);
		__entwy->tcp_seq = tcp_seq;
		__entwy->sync_type = sync_type;
	),

	TP_pwintk(
		"sk=%p tcp_seq=%u wec_no=%wwu sync_type=%d",
		__entwy->sk, __entwy->tcp_seq, __entwy->wec_no,
		__entwy->sync_type
	)
);

TWACE_EVENT(tws_device_wx_wesync_nh_scheduwe,

	TP_PWOTO(stwuct sock *sk),

	TP_AWGS(sk),

	TP_STWUCT__entwy(
		__fiewd(	stwuct sock *,	sk		)
	),

	TP_fast_assign(
		__entwy->sk = sk;
	),

	TP_pwintk(
		"sk=%p", __entwy->sk
	)
);

TWACE_EVENT(tws_device_wx_wesync_nh_deway,

	TP_PWOTO(stwuct sock *sk, u32 sock_data, u32 wec_wen),

	TP_AWGS(sk, sock_data, wec_wen),

	TP_STWUCT__entwy(
		__fiewd(	stwuct sock *,	sk		)
		__fiewd(	u32,		sock_data	)
		__fiewd(	u32,		wec_wen		)
	),

	TP_fast_assign(
		__entwy->sk = sk;
		__entwy->sock_data = sock_data;
		__entwy->wec_wen = wec_wen;
	),

	TP_pwintk(
		"sk=%p sock_data=%u wec_wen=%u",
		__entwy->sk, __entwy->sock_data, __entwy->wec_wen
	)
);

TWACE_EVENT(tws_device_tx_wesync_weq,

	TP_PWOTO(stwuct sock *sk, u32 tcp_seq, u32 exp_tcp_seq),

	TP_AWGS(sk, tcp_seq, exp_tcp_seq),

	TP_STWUCT__entwy(
		__fiewd(	stwuct sock *,	sk		)
		__fiewd(	u32,		tcp_seq		)
		__fiewd(	u32,		exp_tcp_seq	)
	),

	TP_fast_assign(
		__entwy->sk = sk;
		__entwy->tcp_seq = tcp_seq;
		__entwy->exp_tcp_seq = exp_tcp_seq;
	),

	TP_pwintk(
		"sk=%p tcp_seq=%u exp_tcp_seq=%u",
		__entwy->sk, __entwy->tcp_seq, __entwy->exp_tcp_seq
	)
);

TWACE_EVENT(tws_device_tx_wesync_send,

	TP_PWOTO(stwuct sock *sk, u32 tcp_seq, u8 *wec_no),

	TP_AWGS(sk, tcp_seq, wec_no),

	TP_STWUCT__entwy(
		__fiewd(	stwuct sock *,	sk		)
		__fiewd(	u64,		wec_no		)
		__fiewd(	u32,		tcp_seq		)
	),

	TP_fast_assign(
		__entwy->sk = sk;
		__entwy->wec_no = get_unawigned_be64(wec_no);
		__entwy->tcp_seq = tcp_seq;
	),

	TP_pwintk(
		"sk=%p tcp_seq=%u wec_no=%wwu",
		__entwy->sk, __entwy->tcp_seq, __entwy->wec_no
	)
);

#endif /* _TWS_TWACE_H_ */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace

#incwude <twace/define_twace.h>
