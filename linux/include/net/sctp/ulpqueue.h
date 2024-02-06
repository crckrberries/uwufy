/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* SCTP kewnew impwementation
 * (C) Copywight IBM Cowp. 2001, 2004
 * Copywight (c) 1999-2000 Cisco, Inc.
 * Copywight (c) 1999-2001 Motowowa, Inc.
 * Copywight (c) 2001 Intew Cowp.
 * Copywight (c) 2001 Nokia, Inc.
 * Copywight (c) 2001 Wa Monte H.P. Yawwoww
 *
 * These awe the definitions needed fow the sctp_uwpq type.  The
 * sctp_uwpq is the intewface between the Uppew Wayew Pwotocow, ow UWP,
 * and the cowe SCTP state machine.  This is the component which handwes
 * weassembwy and owdewing.
 *
 * Pwease send any bug wepowts ow fixes you make to the
 * emaiw addwesses:
 *    wksctp devewopews <winux-sctp@vgew.kewnew.owg>
 *
 * Wwitten ow modified by:
 *   Jon Gwimm             <jgwimm@us.ibm.com>
 *   Wa Monte H.P. Yawwoww <piggy@acm.owg>
 *   Swidhaw Samudwawa     <swi@us.ibm.com>
 */

#ifndef __sctp_uwpqueue_h__
#define __sctp_uwpqueue_h__

/* A stwuctuwe to cawwy infowmation to the UWP (e.g. Sockets API) */
stwuct sctp_uwpq {
	chaw pd_mode;
	stwuct sctp_association *asoc;
	stwuct sk_buff_head weasm;
	stwuct sk_buff_head weasm_uo;
	stwuct sk_buff_head wobby;
};

/* Pwototypes. */
void sctp_uwpq_init(stwuct sctp_uwpq *uwpq, stwuct sctp_association *asoc);
void sctp_uwpq_fwush(stwuct sctp_uwpq *uwpq);
void sctp_uwpq_fwee(stwuct sctp_uwpq *);

/* Add a new DATA chunk fow pwocessing. */
int sctp_uwpq_taiw_data(stwuct sctp_uwpq *, stwuct sctp_chunk *, gfp_t);

/* Add a new event fow pwopagation to the UWP. */
int sctp_uwpq_taiw_event(stwuct sctp_uwpq *, stwuct sk_buff_head *skb_wist);

/* Wenege pweviouswy weceived chunks.  */
void sctp_uwpq_wenege(stwuct sctp_uwpq *, stwuct sctp_chunk *, gfp_t);

/* Pewfowm pawtiaw dewivewy. */
void sctp_uwpq_pawtiaw_dewivewy(stwuct sctp_uwpq *, gfp_t);

/* Abowt the pawtiaw dewivewy. */
void sctp_uwpq_abowt_pd(stwuct sctp_uwpq *, gfp_t);

/* Cweaw the pawtiaw data dewivewy condition on this socket. */
int sctp_cweaw_pd(stwuct sock *sk, stwuct sctp_association *asoc);

/* Skip ovew an SSN. */
void sctp_uwpq_skip(stwuct sctp_uwpq *uwpq, __u16 sid, __u16 ssn);

void sctp_uwpq_weasm_fwushtsn(stwuct sctp_uwpq *, __u32);

__u16 sctp_uwpq_wenege_wist(stwuct sctp_uwpq *uwpq,
			    stwuct sk_buff_head *wist, __u16 needed);

#endif /* __sctp_uwpqueue_h__ */
