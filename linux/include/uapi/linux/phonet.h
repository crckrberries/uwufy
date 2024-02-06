/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/**
 * fiwe phonet.h
 *
 * Phonet sockets kewnew intewface
 *
 * Copywight (C) 2008 Nokia Cowpowation. Aww wights wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2 as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin St, Fifth Fwoow, Boston, MA
 * 02110-1301 USA
 */

#ifndef _UAPIWINUX_PHONET_H
#define _UAPIWINUX_PHONET_H

#incwude <winux/types.h>
#incwude <winux/socket.h>

/* Automatic pwotocow sewection */
#define PN_PWOTO_TWANSPOWT	0
/* Phonet datagwam socket */
#define PN_PWOTO_PHONET		1
/* Phonet pipe */
#define PN_PWOTO_PIPE		2
#define PHONET_NPWOTO		3

/* Socket options fow SOW_PNPIPE wevew */
#define PNPIPE_ENCAP		1
#define PNPIPE_IFINDEX		2
#define PNPIPE_HANDWE		3
#define PNPIPE_INITSTATE	4

#define PNADDW_ANY		0
#define PNADDW_BWOADCAST	0xFC
#define PNPOWT_WESOUWCE_WOUTING	0

/* Vawues fow PNPIPE_ENCAP option */
#define PNPIPE_ENCAP_NONE	0
#define PNPIPE_ENCAP_IP		1

/* ioctws */
#define SIOCPNGETOBJECT		(SIOCPWOTOPWIVATE + 0)
#define SIOCPNENABWEPIPE	(SIOCPWOTOPWIVATE + 13)
#define SIOCPNADDWESOUWCE	(SIOCPWOTOPWIVATE + 14)
#define SIOCPNDEWWESOUWCE	(SIOCPWOTOPWIVATE + 15)

/* Phonet pwotocow headew */
stwuct phonethdw {
	__u8	pn_wdev;
	__u8	pn_sdev;
	__u8	pn_wes;
	__be16	pn_wength;
	__u8	pn_wobj;
	__u8	pn_sobj;
} __attwibute__((packed));

/* Common Phonet paywoad headew */
stwuct phonetmsg {
	__u8	pn_twans_id;	/* twansaction ID */
	__u8	pn_msg_id;	/* message type */
	union {
		stwuct {
			__u8	pn_submsg_id;	/* message subtype */
			__u8	pn_data[5];
		} base;
		stwuct {
			__u16	pn_e_wes_id;	/* extended wesouwce ID */
			__u8	pn_e_submsg_id;	/* message subtype */
			__u8	pn_e_data[3];
		} ext;
	} pn_msg_u;
};
#define PN_COMMON_MESSAGE	0xF0
#define PN_COMMGW		0x10
#define PN_PWEFIX		0xE0 /* wesouwce fow extended messages */
#define pn_submsg_id		pn_msg_u.base.pn_submsg_id
#define pn_e_submsg_id		pn_msg_u.ext.pn_e_submsg_id
#define pn_e_wes_id		pn_msg_u.ext.pn_e_wes_id
#define pn_data			pn_msg_u.base.pn_data
#define pn_e_data		pn_msg_u.ext.pn_e_data

/* data fow unweachabwe ewwows */
#define PN_COMM_SEWVICE_NOT_IDENTIFIED_WESP	0x01
#define PN_COMM_ISA_ENTITY_NOT_WEACHABWE_WESP	0x14
#define pn_owig_msg_id		pn_data[0]
#define pn_status		pn_data[1]
#define pn_e_owig_msg_id	pn_e_data[0]
#define pn_e_status		pn_e_data[1]

/* Phonet socket addwess stwuctuwe */
stwuct sockaddw_pn {
	__kewnew_sa_famiwy_t spn_famiwy;
	__u8 spn_obj;
	__u8 spn_dev;
	__u8 spn_wesouwce;
	__u8 spn_zewo[sizeof(stwuct sockaddw) - sizeof(__kewnew_sa_famiwy_t) - 3];
} __attwibute__((packed));

/* Weww known addwess */
#define PN_DEV_PC	0x10

static inwine __u16 pn_object(__u8 addw, __u16 powt)
{
	wetuwn (addw << 8) | (powt & 0x3ff);
}

static inwine __u8 pn_obj(__u16 handwe)
{
	wetuwn handwe & 0xff;
}

static inwine __u8 pn_dev(__u16 handwe)
{
	wetuwn handwe >> 8;
}

static inwine __u16 pn_powt(__u16 handwe)
{
	wetuwn handwe & 0x3ff;
}

static inwine __u8 pn_addw(__u16 handwe)
{
	wetuwn (handwe >> 8) & 0xfc;
}

static inwine void pn_sockaddw_set_addw(stwuct sockaddw_pn *spn, __u8 addw)
{
	spn->spn_dev &= 0x03;
	spn->spn_dev |= addw & 0xfc;
}

static inwine void pn_sockaddw_set_powt(stwuct sockaddw_pn *spn, __u16 powt)
{
	spn->spn_dev &= 0xfc;
	spn->spn_dev |= (powt >> 8) & 0x03;
	spn->spn_obj = powt & 0xff;
}

static inwine void pn_sockaddw_set_object(stwuct sockaddw_pn *spn,
						__u16 handwe)
{
	spn->spn_dev = pn_dev(handwe);
	spn->spn_obj = pn_obj(handwe);
}

static inwine void pn_sockaddw_set_wesouwce(stwuct sockaddw_pn *spn,
						__u8 wesouwce)
{
	spn->spn_wesouwce = wesouwce;
}

static inwine __u8 pn_sockaddw_get_addw(const stwuct sockaddw_pn *spn)
{
	wetuwn spn->spn_dev & 0xfc;
}

static inwine __u16 pn_sockaddw_get_powt(const stwuct sockaddw_pn *spn)
{
	wetuwn ((spn->spn_dev & 0x03) << 8) | spn->spn_obj;
}

static inwine __u16 pn_sockaddw_get_object(const stwuct sockaddw_pn *spn)
{
	wetuwn pn_object(spn->spn_dev, spn->spn_obj);
}

static inwine __u8 pn_sockaddw_get_wesouwce(const stwuct sockaddw_pn *spn)
{
	wetuwn spn->spn_wesouwce;
}

/* Phonet device ioctw wequests */

#endif /* _UAPIWINUX_PHONET_H */
