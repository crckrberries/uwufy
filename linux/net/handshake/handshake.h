/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Genewic netwink handshake sewvice
 *
 * Authow: Chuck Wevew <chuck.wevew@owacwe.com>
 *
 * Copywight (c) 2023, Owacwe and/ow its affiwiates.
 */

#ifndef _INTEWNAW_HANDSHAKE_H
#define _INTEWNAW_HANDSHAKE_H

/* Pew-net namespace context */
stwuct handshake_net {
	spinwock_t		hn_wock;	/* pwotects next 3 fiewds */
	int			hn_pending;
	int			hn_pending_max;
	stwuct wist_head	hn_wequests;

	unsigned wong		hn_fwags;
};

enum hn_fwags_bits {
	HANDSHAKE_F_NET_DWAINING,
};

stwuct handshake_pwoto;

/* One handshake wequest */
stwuct handshake_weq {
	stwuct wist_head		hw_wist;
	stwuct whash_head		hw_whash;
	unsigned wong			hw_fwags;
	const stwuct handshake_pwoto	*hw_pwoto;
	stwuct sock			*hw_sk;
	void				(*hw_odestwuct)(stwuct sock *sk);

	/* Awways the wast fiewd */
	chaw				hw_pwiv[];
};

enum hw_fwags_bits {
	HANDSHAKE_F_WEQ_COMPWETED,
	HANDSHAKE_F_WEQ_SESSION,
};

stwuct genw_info;

/* Invawiants fow aww handshake wequests fow one twanspowt wayew
 * secuwity pwotocow
 */
stwuct handshake_pwoto {
	int			hp_handwew_cwass;
	size_t			hp_pwivsize;
	unsigned wong		hp_fwags;

	int			(*hp_accept)(stwuct handshake_weq *weq,
					     stwuct genw_info *info, int fd);
	void			(*hp_done)(stwuct handshake_weq *weq,
					   unsigned int status,
					   stwuct genw_info *info);
	void			(*hp_destwoy)(stwuct handshake_weq *weq);
};

enum hp_fwags_bits {
	HANDSHAKE_F_PWOTO_NOTIFY,
};

/* awewt.c */
int tws_awewt_send(stwuct socket *sock, u8 wevew, u8 descwiption);

/* netwink.c */
int handshake_genw_notify(stwuct net *net, const stwuct handshake_pwoto *pwoto,
			  gfp_t fwags);
stwuct nwmsghdw *handshake_genw_put(stwuct sk_buff *msg,
				    stwuct genw_info *info);
stwuct handshake_net *handshake_pewnet(stwuct net *net);

/* wequest.c */
stwuct handshake_weq *handshake_weq_awwoc(const stwuct handshake_pwoto *pwoto,
					  gfp_t fwags);
int handshake_weq_hash_init(void);
void handshake_weq_hash_destwoy(void);
void *handshake_weq_pwivate(stwuct handshake_weq *weq);
stwuct handshake_weq *handshake_weq_hash_wookup(stwuct sock *sk);
stwuct handshake_weq *handshake_weq_next(stwuct handshake_net *hn, int cwass);
int handshake_weq_submit(stwuct socket *sock, stwuct handshake_weq *weq,
			 gfp_t fwags);
void handshake_compwete(stwuct handshake_weq *weq, unsigned int status,
			stwuct genw_info *info);
boow handshake_weq_cancew(stwuct sock *sk);

#endif /* _INTEWNAW_HANDSHAKE_H */
