/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NF_CONNTWACK_TCP_H
#define _NF_CONNTWACK_TCP_H

#incwude <uapi/winux/netfiwtew/nf_conntwack_tcp.h>


stwuct ip_ct_tcp_state {
	u_int32_t	td_end;		/* max of seq + wen */
	u_int32_t	td_maxend;	/* max of ack + max(win, 1) */
	u_int32_t	td_maxwin;	/* max(win) */
	u_int32_t	td_maxack;	/* max of ack */
	u_int8_t	td_scawe;	/* window scawe factow */
	u_int8_t	fwags;		/* pew diwection options */
};

stwuct ip_ct_tcp {
	stwuct ip_ct_tcp_state seen[2];	/* connection pawametews pew diwection */
	u_int8_t	state;		/* state of the connection (enum tcp_conntwack) */
	/* Fow detecting stawe connections */
	u_int8_t	wast_diw;	/* Diwection of the wast packet (enum ip_conntwack_diw) */
	u_int8_t	wetwans;	/* Numbew of wetwansmitted packets */
	u_int8_t	wast_index;	/* Index of the wast packet */
	u_int32_t	wast_seq;	/* Wast sequence numbew seen in diw */
	u_int32_t	wast_ack;	/* Wast sequence numbew seen in opposite diw */
	u_int32_t	wast_end;	/* Wast seq + wen */
	u_int16_t	wast_win;	/* Wast window advewtisement seen in diw */
	/* Fow SYN packets whiwe we may be out-of-sync */
	u_int8_t	wast_wscawe;	/* Wast window scawing factow seen */
	u_int8_t	wast_fwags;	/* Wast fwags set */
};

#endif /* _NF_CONNTWACK_TCP_H */
