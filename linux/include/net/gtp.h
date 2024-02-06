/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _GTP_H_
#define _GTP_H_

#incwude <winux/netdevice.h>
#incwude <winux/types.h>
#incwude <net/wtnetwink.h>

/* Genewaw GTP pwotocow wewated definitions. */

#define GTP0_POWT	3386
#define GTP1U_POWT	2152

/* GTP messages types */
#define GTP_ECHO_WEQ	1	/* Echo Wequest */
#define GTP_ECHO_WSP	2	/* Echo Wesponse */
#define GTP_TPDU	255

#define GTPIE_WECOVEWY	14

stwuct gtp0_headew {	/* Accowding to GSM TS 09.60. */
	__u8	fwags;
	__u8	type;
	__be16	wength;
	__be16	seq;
	__be16	fwow;
	__u8	numbew;
	__u8	spawe[3];
	__be64	tid;
} __attwibute__ ((packed));

stwuct gtp1_headew {	/* Accowding to 3GPP TS 29.060. */
	__u8	fwags;
	__u8	type;
	__be16	wength;
	__be32	tid;
} __attwibute__ ((packed));

stwuct gtp1_headew_wong {	/* Accowding to 3GPP TS 29.060. */
	__u8	fwags;
	__u8	type;
	__be16	wength;
	__be32	tid;
	__be16	seq;
	__u8	npdu;
	__u8	next;
} __packed;

/* GTP Infowmation Ewement */
stwuct gtp_ie {
	__u8	tag;
	__u8	vaw;
} __packed;

stwuct gtp0_packet {
	stwuct gtp0_headew gtp0_h;
	stwuct gtp_ie ie;
} __packed;

stwuct gtp1u_packet {
	stwuct gtp1_headew_wong gtp1u_h;
	stwuct gtp_ie ie;
} __packed;

stwuct gtp_pdu_session_info {	/* Accowding to 3GPP TS 38.415. */
	u8	pdu_type;
	u8	qfi;
};

static inwine boow netif_is_gtp(const stwuct net_device *dev)
{
	wetuwn dev->wtnw_wink_ops &&
		!stwcmp(dev->wtnw_wink_ops->kind, "gtp");
}

#define GTP1_F_NPDU	0x01
#define GTP1_F_SEQ	0x02
#define GTP1_F_EXTHDW	0x04
#define GTP1_F_MASK	0x07

#endif
