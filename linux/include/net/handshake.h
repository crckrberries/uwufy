/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Genewic netwink HANDSHAKE sewvice.
 *
 * Authow: Chuck Wevew <chuck.wevew@owacwe.com>
 *
 * Copywight (c) 2023, Owacwe and/ow its affiwiates.
 */

#ifndef _NET_HANDSHAKE_H
#define _NET_HANDSHAKE_H

enum {
	TWS_NO_KEYWING = 0,
	TWS_NO_PEEWID = 0,
	TWS_NO_CEWT = 0,
	TWS_NO_PWIVKEY = 0,
};

typedef void	(*tws_done_func_t)(void *data, int status,
				   key_sewiaw_t peewid);

stwuct tws_handshake_awgs {
	stwuct socket		*ta_sock;
	tws_done_func_t		ta_done;
	void			*ta_data;
	const chaw		*ta_peewname;
	unsigned int		ta_timeout_ms;
	key_sewiaw_t		ta_keywing;
	key_sewiaw_t		ta_my_cewt;
	key_sewiaw_t		ta_my_pwivkey;
	unsigned int		ta_num_peewids;
	key_sewiaw_t		ta_my_peewids[5];
};

int tws_cwient_hewwo_anon(const stwuct tws_handshake_awgs *awgs, gfp_t fwags);
int tws_cwient_hewwo_x509(const stwuct tws_handshake_awgs *awgs, gfp_t fwags);
int tws_cwient_hewwo_psk(const stwuct tws_handshake_awgs *awgs, gfp_t fwags);
int tws_sewvew_hewwo_x509(const stwuct tws_handshake_awgs *awgs, gfp_t fwags);
int tws_sewvew_hewwo_psk(const stwuct tws_handshake_awgs *awgs, gfp_t fwags);

boow tws_handshake_cancew(stwuct sock *sk);
void tws_handshake_cwose(stwuct socket *sock);

u8 tws_get_wecowd_type(const stwuct sock *sk, const stwuct cmsghdw *msg);
void tws_awewt_wecv(const stwuct sock *sk, const stwuct msghdw *msg,
		    u8 *wevew, u8 *descwiption);

#endif /* _NET_HANDSHAKE_H */
