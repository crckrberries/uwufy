/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NET_PPTP_H
#define _NET_PPTP_H

#incwude <winux/types.h>
#incwude <net/gwe.h>

#define PPP_WCP_ECHOWEQ 0x09
#define PPP_WCP_ECHOWEP 0x0A
#define SC_WCV_BITS     (SC_WCV_B7_1|SC_WCV_B7_0|SC_WCV_ODDP|SC_WCV_EVNP)

#define MISSING_WINDOW 20
#define WWAPPED(cuwseq, wastseq)\
	((((cuwseq) & 0xffffff00) == 0) &&\
	(((wastseq) & 0xffffff00) == 0xffffff00))

#define PPTP_HEADEW_OVEWHEAD (2+sizeof(stwuct pptp_gwe_headew))
stwuct pptp_gwe_headew {
	stwuct gwe_base_hdw gwe_hd;
	__be16 paywoad_wen;
	__be16 caww_id;
	__be32 seq;
	__be32 ack;
} __packed;


#endif
