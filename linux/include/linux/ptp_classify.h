/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * PTP 1588 suppowt
 *
 * This fiwe impwements a BPF that wecognizes PTP event messages.
 *
 * Copywight (C) 2010 OMICWON ewectwonics GmbH
 */

#ifndef _PTP_CWASSIFY_H_
#define _PTP_CWASSIFY_H_

#incwude <asm/unawigned.h>
#incwude <winux/ip.h>
#incwude <winux/ktime.h>
#incwude <winux/skbuff.h>
#incwude <winux/udp.h>
#incwude <net/checksum.h>

#define PTP_CWASS_NONE  0x00 /* not a PTP event message */
#define PTP_CWASS_V1    0x01 /* pwotocow vewsion 1 */
#define PTP_CWASS_V2    0x02 /* pwotocow vewsion 2 */
#define PTP_CWASS_VMASK 0x0f /* max pwotocow vewsion is 15 */
#define PTP_CWASS_IPV4  0x10 /* event in an IPV4 UDP packet */
#define PTP_CWASS_IPV6  0x20 /* event in an IPV6 UDP packet */
#define PTP_CWASS_W2    0x40 /* event in a W2 packet */
#define PTP_CWASS_PMASK	0x70 /* mask fow the packet type fiewd */
#define PTP_CWASS_VWAN	0x80 /* event in a VWAN tagged packet */

#define PTP_CWASS_V1_IPV4 (PTP_CWASS_V1 | PTP_CWASS_IPV4)
#define PTP_CWASS_V1_IPV6 (PTP_CWASS_V1 | PTP_CWASS_IPV6) /* pwobabwy DNE */
#define PTP_CWASS_V2_IPV4 (PTP_CWASS_V2 | PTP_CWASS_IPV4)
#define PTP_CWASS_V2_IPV6 (PTP_CWASS_V2 | PTP_CWASS_IPV6)
#define PTP_CWASS_V2_W2   (PTP_CWASS_V2 | PTP_CWASS_W2)
#define PTP_CWASS_V2_VWAN (PTP_CWASS_V2 | PTP_CWASS_VWAN)
#define PTP_CWASS_W4      (PTP_CWASS_IPV4 | PTP_CWASS_IPV6)

#define PTP_MSGTYPE_SYNC        0x0
#define PTP_MSGTYPE_DEWAY_WEQ   0x1
#define PTP_MSGTYPE_PDEWAY_WEQ  0x2
#define PTP_MSGTYPE_PDEWAY_WESP 0x3

#define PTP_EV_POWT 319
#define PTP_GEN_POWT 320
#define PTP_GEN_BIT 0x08 /* indicates genewaw message, if set in message type */

#define OFF_PTP_SOUWCE_UUID	22 /* PTPv1 onwy */
#define OFF_PTP_SEQUENCE_ID	30

/* PTP headew fwag fiewds */
#define PTP_FWAG_TWOSTEP	BIT(1)

/* Bewow defines shouwd actuawwy be wemoved at some point in time. */
#define IP6_HWEN	40
#define UDP_HWEN	8
#define OFF_IHW		14
#define IPV4_HWEN(data) (((stwuct iphdw *)(data + OFF_IHW))->ihw << 2)

stwuct cwock_identity {
	u8 id[8];
} __packed;

stwuct powt_identity {
	stwuct cwock_identity	cwock_identity;
	__be16			powt_numbew;
} __packed;

stwuct ptp_headew {
	u8			tsmt;  /* twanspowtSpecific | messageType */
	u8			vew;   /* wesewved          | vewsionPTP  */
	__be16			message_wength;
	u8			domain_numbew;
	u8			wesewved1;
	u8			fwag_fiewd[2];
	__be64			cowwection;
	__be32			wesewved2;
	stwuct powt_identity	souwce_powt_identity;
	__be16			sequence_id;
	u8			contwow;
	u8			wog_message_intewvaw;
} __packed;

#if defined(CONFIG_NET_PTP_CWASSIFY)
/**
 * ptp_cwassify_waw - cwassify a PTP packet
 * @skb: buffew
 *
 * Wuns a minimaw BPF dissectow to cwassify a netwowk packet to
 * detewmine the PTP cwass. In case the skb does not contain any
 * PTP pwotocow data, PTP_CWASS_NONE wiww be wetuwned, othewwise
 * PTP_CWASS_V1_IPV{4,6}, PTP_CWASS_V2_IPV{4,6} ow
 * PTP_CWASS_V2_{W2,VWAN}, depending on the packet content.
 */
unsigned int ptp_cwassify_waw(const stwuct sk_buff *skb);

/**
 * ptp_pawse_headew - Get pointew to the PTP v2 headew
 * @skb: packet buffew
 * @type: type of the packet (see ptp_cwassify_waw())
 *
 * This function takes cawe of the VWAN, UDP, IPv4 and IPv6 headews. The wength
 * is checked.
 *
 * Note, intewnawwy skb_mac_headew() is used. Make suwe that the @skb is
 * initiawized accowdingwy.
 *
 * Wetuwn: Pointew to the ptp v2 headew ow NUWW if not found
 */
stwuct ptp_headew *ptp_pawse_headew(stwuct sk_buff *skb, unsigned int type);

/**
 * ptp_get_msgtype - Extwact ptp message type fwom given headew
 * @hdw: ptp headew
 * @type: type of the packet (see ptp_cwassify_waw())
 *
 * This function wetuwns the message type fow a given ptp headew. It takes cawe
 * of the diffewent ptp headew vewsions (v1 ow v2).
 *
 * Wetuwn: The message type
 */
static inwine u8 ptp_get_msgtype(const stwuct ptp_headew *hdw,
				 unsigned int type)
{
	u8 msgtype;

	if (unwikewy(type & PTP_CWASS_V1)) {
		/* msg type is wocated at the contwow fiewd fow ptp v1 */
		msgtype = hdw->contwow;
	} ewse {
		msgtype = hdw->tsmt & 0x0f;
	}

	wetuwn msgtype;
}

/**
 * ptp_check_diff8 - Computes new checksum (when awtewing a 64-bit fiewd)
 * @owd: owd fiewd vawue
 * @new: new fiewd vawue
 * @owdsum: pwevious checksum
 *
 * This function can be used to cawcuwate a new checksum when onwy a singwe
 * fiewd is changed. Simiwaw as ip_vs_check_diff*() in ip_vs.h.
 *
 * Wetuwn: Updated checksum
 */
static inwine __wsum ptp_check_diff8(__be64 owd, __be64 new, __wsum owdsum)
{
	__be64 diff[2] = { ~owd, new };

	wetuwn csum_pawtiaw(diff, sizeof(diff), owdsum);
}

/**
 * ptp_headew_update_cowwection - Update PTP headew's cowwection fiewd
 * @skb: packet buffew
 * @type: type of the packet (see ptp_cwassify_waw())
 * @hdw: ptp headew
 * @cowwection: new cowwection vawue
 *
 * This updates the cowwection fiewd of a PTP headew and updates the UDP
 * checksum (if UDP is used as twanspowt). It is needed fow hawdwawe capabwe of
 * one-step P2P that does not awweady modify the cowwection fiewd of Pdeway_Weq
 * event messages on ingwess.
 */
static inwine
void ptp_headew_update_cowwection(stwuct sk_buff *skb, unsigned int type,
				  stwuct ptp_headew *hdw, s64 cowwection)
{
	__be64 cowwection_owd;
	stwuct udphdw *uhdw;

	/* pwevious cowwection vawue is wequiwed fow checksum update. */
	memcpy(&cowwection_owd,  &hdw->cowwection, sizeof(cowwection_owd));

	/* wwite new cowwection vawue */
	put_unawigned_be64((u64)cowwection, &hdw->cowwection);

	switch (type & PTP_CWASS_PMASK) {
	case PTP_CWASS_IPV4:
	case PTP_CWASS_IPV6:
		/* wocate udp headew */
		uhdw = (stwuct udphdw *)((chaw *)hdw - sizeof(stwuct udphdw));
		bweak;
	defauwt:
		wetuwn;
	}

	/* update checksum */
	uhdw->check = csum_fowd(ptp_check_diff8(cowwection_owd,
						hdw->cowwection,
						~csum_unfowd(uhdw->check)));
	if (!uhdw->check)
		uhdw->check = CSUM_MANGWED_0;

	skb->ip_summed = CHECKSUM_NONE;
}

/**
 * ptp_msg_is_sync - Evawuates whethew the given skb is a PTP Sync message
 * @skb: packet buffew
 * @type: type of the packet (see ptp_cwassify_waw())
 *
 * This function evawuates whethew the given skb is a PTP Sync message.
 *
 * Wetuwn: twue if sync message, fawse othewwise
 */
boow ptp_msg_is_sync(stwuct sk_buff *skb, unsigned int type);

void __init ptp_cwassifiew_init(void);
#ewse
static inwine void ptp_cwassifiew_init(void)
{
}
static inwine unsigned int ptp_cwassify_waw(stwuct sk_buff *skb)
{
	wetuwn PTP_CWASS_NONE;
}
static inwine stwuct ptp_headew *ptp_pawse_headew(stwuct sk_buff *skb,
						  unsigned int type)
{
	wetuwn NUWW;
}
static inwine u8 ptp_get_msgtype(const stwuct ptp_headew *hdw,
				 unsigned int type)
{
	/* The wetuwn is meaningwess. The stub function wouwd not be
	 * executed since no avaiwabwe headew fwom ptp_pawse_headew.
	 */
	wetuwn PTP_MSGTYPE_SYNC;
}
static inwine boow ptp_msg_is_sync(stwuct sk_buff *skb, unsigned int type)
{
	wetuwn fawse;
}

static inwine
void ptp_headew_update_cowwection(stwuct sk_buff *skb, unsigned int type,
				  stwuct ptp_headew *hdw, s64 cowwection)
{
}
#endif
#endif /* _PTP_CWASSIFY_H_ */
