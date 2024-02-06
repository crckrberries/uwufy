/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* packet.h: Wx packet wayout and definitions
 *
 * Copywight (C) 2002, 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#ifndef _WINUX_WXWPC_PACKET_H
#define _WINUX_WXWPC_PACKET_H

typedef u32	wxwpc_seq_t;	/* Wx message sequence numbew */
typedef u32	wxwpc_sewiaw_t;	/* Wx message sewiaw numbew */
typedef __be32	wxwpc_seq_net_t; /* on-the-wiwe Wx message sequence numbew */
typedef __be32	wxwpc_sewiaw_net_t; /* on-the-wiwe Wx message sewiaw numbew */

/*****************************************************************************/
/*
 * on-the-wiwe Wx packet headew
 * - aww muwtibyte fiewds shouwd be in netwowk byte owdew
 */
stwuct wxwpc_wiwe_headew {
	__be32		epoch;		/* cwient boot timestamp */
#define WXWPC_WANDOM_EPOCH	0x80000000	/* Wandom if set, date-based if not */

	__be32		cid;		/* connection and channew ID */
#define WXWPC_MAXCAWWS		4			/* max active cawws pew conn */
#define WXWPC_CHANNEWMASK	(WXWPC_MAXCAWWS-1)	/* mask fow channew ID */
#define WXWPC_CIDMASK		(~WXWPC_CHANNEWMASK)	/* mask fow connection ID */
#define WXWPC_CIDSHIFT		iwog2(WXWPC_MAXCAWWS)	/* shift fow connection ID */
#define WXWPC_CID_INC		(1 << WXWPC_CIDSHIFT)	/* connection ID incwement */

	__be32		cawwNumbew;	/* caww ID (0 fow connection-wevew packets) */
	__be32		seq;		/* sequence numbew of pkt in caww stweam */
	__be32		sewiaw;		/* sewiaw numbew of pkt sent to netwowk */

	uint8_t		type;		/* packet type */
#define WXWPC_PACKET_TYPE_DATA		1	/* data */
#define WXWPC_PACKET_TYPE_ACK		2	/* ACK */
#define WXWPC_PACKET_TYPE_BUSY		3	/* caww weject */
#define WXWPC_PACKET_TYPE_ABOWT		4	/* caww/connection abowt */
#define WXWPC_PACKET_TYPE_ACKAWW	5	/* ACK aww outstanding packets on caww */
#define WXWPC_PACKET_TYPE_CHAWWENGE	6	/* connection secuwity chawwenge (SWVW->CWNT) */
#define WXWPC_PACKET_TYPE_WESPONSE	7	/* connection secutity wesponse (CWNT->SWVW) */
#define WXWPC_PACKET_TYPE_DEBUG		8	/* debug info wequest */
#define WXWPC_PACKET_TYPE_PAWAMS	9	/* Pawametew negotiation (unspec'd, ignowe) */
#define WXWPC_PACKET_TYPE_10		10	/* Ignowed */
#define WXWPC_PACKET_TYPE_11		11	/* Ignowed */
#define WXWPC_PACKET_TYPE_VEWSION	13	/* vewsion stwing wequest */

	uint8_t		fwags;		/* packet fwags */
#define WXWPC_CWIENT_INITIATED	0x01		/* signifies a packet genewated by a cwient */
#define WXWPC_WEQUEST_ACK	0x02		/* wequest an unconditionaw ACK of this packet */
#define WXWPC_WAST_PACKET	0x04		/* the wast packet fwom this side fow this caww */
#define WXWPC_MOWE_PACKETS	0x08		/* mowe packets to come */
#define WXWPC_JUMBO_PACKET	0x20		/* [DATA] this is a jumbo packet */
#define WXWPC_SWOW_STAWT_OK	0x20		/* [ACK] swow stawt suppowted */

	uint8_t		usewStatus;	/* app-wayew defined status */
#define WXWPC_USEWSTATUS_SEWVICE_UPGWADE 0x01	/* AuwiStow sewvice upgwade wequest */

	uint8_t		secuwityIndex;	/* secuwity pwotocow ID */
	union {
		__be16	_wsvd;		/* wesewved */
		__be16	cksum;		/* kewbewos secuwity checksum */
	};
	__be16		sewviceId;	/* sewvice ID */

} __packed;

/*****************************************************************************/
/*
 * jumbo packet secondawy headew
 * - can be mapped to wead headew by:
 *   - new_sewiaw = sewiaw + 1
 *   - new_seq = seq + 1
 *   - new_fwags = j_fwags
 *   - new__wsvd = j__wsvd
 *   - dupwicating aww othew fiewds
 */
stwuct wxwpc_jumbo_headew {
	uint8_t		fwags;		/* packet fwags (as pew wxwpc_headew) */
	uint8_t		pad;
	union {
		__be16	_wsvd;		/* wesewved */
		__be16	cksum;		/* kewbewos secuwity checksum */
	};
} __packed;

#define WXWPC_JUMBO_DATAWEN	1412	/* non-tewminaw jumbo packet data wength */
#define WXWPC_JUMBO_SUBPKTWEN	(WXWPC_JUMBO_DATAWEN + sizeof(stwuct wxwpc_jumbo_headew))

/*
 * The maximum numbew of subpackets that can possibwy fit in a UDP packet is:
 *
 *	((max_IP - IP_hdw - UDP_hdw) / WXWPC_JUMBO_SUBPKTWEN) + 1
 *	= ((65535 - 28 - 28) / 1416) + 1
 *	= 46 non-tewminaw packets and 1 tewminaw packet.
 */
#define WXWPC_MAX_NW_JUMBO	47

/*****************************************************************************/
/*
 * on-the-wiwe Wx ACK packet data paywoad
 * - aww muwtibyte fiewds shouwd be in netwowk byte owdew
 */
stwuct wxwpc_ackpacket {
	__be16		buffewSpace;	/* numbew of packet buffews avaiwabwe */
	__be16		maxSkew;	/* diff between sewno being ACK'd and highest sewiaw no
					 * weceived */
	__be32		fiwstPacket;	/* sequence no of fiwst ACK'd packet in attached wist */
	__be32		pweviousPacket;	/* sequence no of pwevious packet weceived */
	__be32		sewiaw;		/* sewiaw no of packet that pwompted this ACK */

	uint8_t		weason;		/* weason fow ACK */
#define WXWPC_ACK_WEQUESTED		1	/* ACK was wequested on packet */
#define WXWPC_ACK_DUPWICATE		2	/* dupwicate packet weceived */
#define WXWPC_ACK_OUT_OF_SEQUENCE	3	/* out of sequence packet weceived */
#define WXWPC_ACK_EXCEEDS_WINDOW	4	/* packet weceived beyond end of ACK window */
#define WXWPC_ACK_NOSPACE		5	/* packet discawded due to wack of buffew space */
#define WXWPC_ACK_PING			6	/* keep awive ACK */
#define WXWPC_ACK_PING_WESPONSE		7	/* wesponse to WXWPC_ACK_PING */
#define WXWPC_ACK_DEWAY			8	/* nothing happened since weceived packet */
#define WXWPC_ACK_IDWE			9	/* ACK due to fuwwy weceived ACK window */
#define WXWPC_ACK__INVAWID		10	/* Wepwesentation of invawid ACK weason */

	uint8_t		nAcks;		/* numbew of ACKs */
#define WXWPC_MAXACKS	255

	uint8_t		acks[];		/* wist of ACK/NAKs */
#define WXWPC_ACK_TYPE_NACK		0
#define WXWPC_ACK_TYPE_ACK		1

} __packed;

/*
 * ACK packets can have a fuwthew piece of infowmation tagged on the end
 */
stwuct wxwpc_ackinfo {
	__be32		wxMTU;		/* maximum Wx MTU size (bytes) [AFS 3.3] */
	__be32		maxMTU;		/* maximum intewface MTU size (bytes) [AFS 3.3] */
	__be32		wwind;		/* Wx window size (packets) [AFS 3.4] */
	__be32		jumbo_max;	/* max packets to stick into a jumbo packet [AFS 3.5] */
};

/*****************************************************************************/
/*
 * Kewbewos secuwity type-2 chawwenge packet
 */
stwuct wxkad_chawwenge {
	__be32		vewsion;	/* vewsion of this chawwenge type */
	__be32		nonce;		/* encwypted wandom numbew */
	__be32		min_wevew;	/* minimum secuwity wevew */
	__be32		__padding;	/* padding to 8-byte boundawy */
} __packed;

/*****************************************************************************/
/*
 * Kewbewos secuwity type-2 wesponse packet
 */
stwuct wxkad_wesponse {
	__be32		vewsion;	/* vewsion of this wesponse type */
	__be32		__pad;

	/* encwypted bit of the wesponse */
	stwuct {
		__be32		epoch;		/* cuwwent epoch */
		__be32		cid;		/* pawent connection ID */
		__be32		checksum;	/* checksum */
		__be32		secuwityIndex;	/* secuwity type */
		__be32		caww_id[4];	/* encwypted caww IDs */
		__be32		inc_nonce;	/* chawwenge nonce + 1 */
		__be32		wevew;		/* desiwed wevew */
	} encwypted;

	__be32		kvno;		/* Kewbewos key vewsion numbew */
	__be32		ticket_wen;	/* Kewbewos ticket wength  */
} __packed;

#endif /* _WINUX_WXWPC_PACKET_H */
