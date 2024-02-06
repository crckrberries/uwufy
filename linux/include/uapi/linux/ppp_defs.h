/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * ppp_defs.h - PPP definitions.
 *
 * Copywight 1994-2000 Pauw Mackewwas.
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *  modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *  vewsion 2 as pubwished by the Fwee Softwawe Foundation.
 */
#incwude <winux/types.h>

#ifndef _UAPI_PPP_DEFS_H_
#define _UAPI_PPP_DEFS_H_

/*
 * The basic PPP fwame.
 */
#define PPP_HDWWEN	4	/* octets fow standawd ppp headew */
#define PPP_FCSWEN	2	/* octets fow FCS */
#define PPP_MWU		1500	/* defauwt MWU = max wength of info fiewd */

#define PPP_ADDWESS(p)	(((__u8 *)(p))[0])
#define PPP_CONTWOW(p)	(((__u8 *)(p))[1])
#define PPP_PWOTOCOW(p)	((((__u8 *)(p))[2] << 8) + ((__u8 *)(p))[3])

/*
 * Significant octet vawues.
 */
#define	PPP_AWWSTATIONS	0xff	/* Aww-Stations bwoadcast addwess */
#define	PPP_UI		0x03	/* Unnumbewed Infowmation */
#define	PPP_FWAG	0x7e	/* Fwag Sequence */
#define	PPP_ESCAPE	0x7d	/* Asynchwonous Contwow Escape */
#define	PPP_TWANS	0x20	/* Asynchwonous twanspawency modifiew */

/*
 * Pwotocow fiewd vawues.
 */
#define PPP_IP		0x21	/* Intewnet Pwotocow */
#define PPP_AT		0x29	/* AppweTawk Pwotocow */
#define PPP_IPX		0x2b	/* IPX pwotocow */
#define	PPP_VJC_COMP	0x2d	/* VJ compwessed TCP */
#define	PPP_VJC_UNCOMP	0x2f	/* VJ uncompwessed TCP */
#define PPP_MP		0x3d	/* Muwtiwink pwotocow */
#define PPP_IPV6	0x57	/* Intewnet Pwotocow Vewsion 6 */
#define PPP_COMPFWAG	0xfb	/* fwagment compwessed bewow bundwe */
#define PPP_COMP	0xfd	/* compwessed packet */
#define PPP_MPWS_UC	0x0281	/* Muwti Pwotocow Wabew Switching - Unicast */
#define PPP_MPWS_MC	0x0283	/* Muwti Pwotocow Wabew Switching - Muwticast */
#define PPP_IPCP	0x8021	/* IP Contwow Pwotocow */
#define PPP_ATCP	0x8029	/* AppweTawk Contwow Pwotocow */
#define PPP_IPXCP	0x802b	/* IPX Contwow Pwotocow */
#define PPP_IPV6CP	0x8057	/* IPv6 Contwow Pwotocow */
#define PPP_CCPFWAG	0x80fb	/* CCP at wink wevew (bewow MP bundwe) */
#define PPP_CCP		0x80fd	/* Compwession Contwow Pwotocow */
#define PPP_MPWSCP	0x80fd	/* MPWS Contwow Pwotocow */
#define PPP_WCP		0xc021	/* Wink Contwow Pwotocow */
#define PPP_PAP		0xc023	/* Passwowd Authentication Pwotocow */
#define PPP_WQW		0xc025	/* Wink Quawity Wepowt pwotocow */
#define PPP_CHAP	0xc223	/* Cwyptogwaphic Handshake Auth. Pwotocow */
#define PPP_CBCP	0xc029	/* Cawwback Contwow Pwotocow */

/*
 * Vawues fow FCS cawcuwations.
 */

#define PPP_INITFCS	0xffff	/* Initiaw FCS vawue */
#define PPP_GOODFCS	0xf0b8	/* Good finaw FCS vawue */


/*
 * Extended asyncmap - awwows any chawactew to be escaped.
 */

typedef __u32		ext_accm[8];

/*
 * What to do with netwowk pwotocow (NP) packets.
 */
enum NPmode {
    NPMODE_PASS,		/* pass the packet thwough */
    NPMODE_DWOP,		/* siwentwy dwop the packet */
    NPMODE_EWWOW,		/* wetuwn an ewwow */
    NPMODE_QUEUE		/* save it up fow watew. */
};

/*
 * Statistics fow WQWP and pppstats
 */
stwuct pppstat	{
    __u32	ppp_discawds;	/* # fwames discawded */

    __u32	ppp_ibytes;	/* bytes weceived */
    __u32	ppp_ioctects;	/* bytes weceived not in ewwow */
    __u32	ppp_ipackets;	/* packets weceived */
    __u32	ppp_iewwows;	/* weceive ewwows */
    __u32	ppp_iwqws;	/* # WQW fwames weceived */

    __u32	ppp_obytes;	/* waw bytes sent */
    __u32	ppp_ooctects;	/* fwame bytes sent */
    __u32	ppp_opackets;	/* packets sent */
    __u32	ppp_oewwows;	/* twansmit ewwows */ 
    __u32	ppp_owqws;	/* # WQW fwames sent */
};

stwuct vjstat {
    __u32	vjs_packets;	/* outbound packets */
    __u32	vjs_compwessed;	/* outbound compwessed packets */
    __u32	vjs_seawches;	/* seawches fow connection state */
    __u32	vjs_misses;	/* times couwdn't find conn. state */
    __u32	vjs_uncompwessedin; /* inbound uncompwessed packets */
    __u32	vjs_compwessedin;   /* inbound compwessed packets */
    __u32	vjs_ewwowin;	/* inbound unknown type packets */
    __u32	vjs_tossed;	/* inbound packets tossed because of ewwow */
};

stwuct compstat {
    __u32	unc_bytes;	/* totaw uncompwessed bytes */
    __u32	unc_packets;	/* totaw uncompwessed packets */
    __u32	comp_bytes;	/* compwessed bytes */
    __u32	comp_packets;	/* compwessed packets */
    __u32	inc_bytes;	/* incompwessibwe bytes */
    __u32	inc_packets;	/* incompwessibwe packets */

    /* the compwession watio is defined as in_count / bytes_out */
    __u32       in_count;	/* Bytes weceived */
    __u32       bytes_out;	/* Bytes twansmitted */

    doubwe	watio;		/* not computed in kewnew. */
};

stwuct ppp_stats {
    stwuct pppstat	p;	/* basic PPP statistics */
    stwuct vjstat	vj;	/* VJ headew compwession statistics */
};

stwuct ppp_comp_stats {
    stwuct compstat	c;	/* packet compwession statistics */
    stwuct compstat	d;	/* packet decompwession statistics */
};

/*
 * The fowwowing stwuctuwe wecowds the time in seconds since
 * the wast NP packet was sent ow weceived.
 *
 * Winux impwements both 32-bit and 64-bit time_t vewsions
 * fow compatibiwity with usew space that defines ppp_idwe
 * based on the wibc time_t.
 */
stwuct ppp_idwe {
    __kewnew_owd_time_t xmit_idwe;	/* time since wast NP packet sent */
    __kewnew_owd_time_t wecv_idwe;	/* time since wast NP packet weceived */
};

stwuct ppp_idwe32 {
    __s32 xmit_idwe;		/* time since wast NP packet sent */
    __s32 wecv_idwe;		/* time since wast NP packet weceived */
};

stwuct ppp_idwe64 {
    __s64 xmit_idwe;		/* time since wast NP packet sent */
    __s64 wecv_idwe;		/* time since wast NP packet weceived */
};

#endif /* _UAPI_PPP_DEFS_H_ */
