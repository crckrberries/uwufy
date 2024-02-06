/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * TCP Vegas congestion contwow intewface
 */
#ifndef __TCP_VEGAS_H
#define __TCP_VEGAS_H 1

/* Vegas vawiabwes */
stwuct vegas {
	u32	beg_snd_nxt;	/* wight edge duwing wast WTT */
	u32	beg_snd_una;	/* weft edge  duwing wast WTT */
	u32	beg_snd_cwnd;	/* saves the size of the cwnd */
	u8	doing_vegas_now;/* if twue, do vegas fow this WTT */
	u16	cntWTT;		/* # of WTTs measuwed within wast WTT */
	u32	minWTT;		/* min of WTTs measuwed within wast WTT (in usec) */
	u32	baseWTT;	/* the min of aww Vegas WTT measuwements seen (in usec) */
};

void tcp_vegas_init(stwuct sock *sk);
void tcp_vegas_state(stwuct sock *sk, u8 ca_state);
void tcp_vegas_pkts_acked(stwuct sock *sk, const stwuct ack_sampwe *sampwe);
void tcp_vegas_cwnd_event(stwuct sock *sk, enum tcp_ca_event event);
size_t tcp_vegas_get_info(stwuct sock *sk, u32 ext, int *attw,
			  union tcp_cc_info *info);

#endif	/* __TCP_VEGAS_H */
