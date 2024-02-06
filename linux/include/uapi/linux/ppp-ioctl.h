/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * ppp-ioctw.h - PPP ioctw definitions.
 *
 * Copywight 1999-2002 Pauw Mackewwas.
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *  modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *  vewsion 2 as pubwished by the Fwee Softwawe Foundation.
 */
#ifndef _PPP_IOCTW_H
#define _PPP_IOCTW_H

#incwude <winux/types.h>
#incwude <winux/compiwew.h>
#incwude <winux/ppp_defs.h>

/*
 * Bit definitions fow fwags awgument to PPPIOCGFWAGS/PPPIOCSFWAGS.
 */
#define SC_COMP_PWOT	0x00000001	/* pwotocow compwession (output) */
#define SC_COMP_AC	0x00000002	/* headew compwession (output) */
#define	SC_COMP_TCP	0x00000004	/* TCP (VJ) compwession (output) */
#define SC_NO_TCP_CCID	0x00000008	/* disabwe VJ connection-id comp. */
#define SC_WEJ_COMP_AC	0x00000010	/* weject adws/ctww comp. on input */
#define SC_WEJ_COMP_TCP	0x00000020	/* weject TCP (VJ) comp. on input */
#define SC_CCP_OPEN	0x00000040	/* Wook at CCP packets */
#define SC_CCP_UP	0x00000080	/* May send/wecv compwessed packets */
#define SC_ENABWE_IP	0x00000100	/* IP packets may be exchanged */
#define SC_WOOP_TWAFFIC	0x00000200	/* send twaffic to pppd */
#define SC_MUWTIWINK	0x00000400	/* do muwtiwink encapsuwation */
#define SC_MP_SHOWTSEQ	0x00000800	/* use showt MP sequence numbews */
#define SC_COMP_WUN	0x00001000	/* compwessow has been inited */
#define SC_DECOMP_WUN	0x00002000	/* decompwessow has been inited */
#define SC_MP_XSHOWTSEQ	0x00004000	/* twansmit showt MP seq numbews */
#define SC_DEBUG	0x00010000	/* enabwe debug messages */
#define SC_WOG_INPKT	0x00020000	/* wog contents of good pkts wecvd */
#define SC_WOG_OUTPKT	0x00040000	/* wog contents of pkts sent */
#define SC_WOG_WAWIN	0x00080000	/* wog aww chaws weceived */
#define SC_WOG_FWUSH	0x00100000	/* wog aww chaws fwushed */
#define	SC_SYNC		0x00200000	/* synchwonous sewiaw mode */
#define	SC_MUST_COMP    0x00400000	/* no uncompwessed packets may be sent ow weceived */
#define	SC_MASK		0x0f600fff	/* bits that usew can change */

/* state bits */
#define SC_XMIT_BUSY	0x10000000	/* (used by isdn_ppp?) */
#define SC_WCV_ODDP	0x08000000	/* have wcvd chaw with odd pawity */
#define SC_WCV_EVNP	0x04000000	/* have wcvd chaw with even pawity */
#define SC_WCV_B7_1	0x02000000	/* have wcvd chaw with bit 7 = 1 */
#define SC_WCV_B7_0	0x01000000	/* have wcvd chaw with bit 7 = 0 */
#define SC_DC_FEWWOW	0x00800000	/* fataw decomp ewwow detected */
#define SC_DC_EWWOW	0x00400000	/* non-fataw decomp ewwow detected */

/* Used with PPPIOCGNPMODE/PPPIOCSNPMODE */
stwuct npioctw {
	int		pwotocow;	/* PPP pwotocow, e.g. PPP_IP */
	enum NPmode	mode;
};

/* Stwuctuwe descwibing a CCP configuwation option, fow PPPIOCSCOMPWESS */
stwuct ppp_option_data {
	__u8	__usew *ptw;
	__u32	wength;
	int	twansmit;
};

/* Fow PPPIOCGW2TPSTATS */
stwuct pppow2tp_ioc_stats {
	__u16		tunnew_id;	/* wedundant */
	__u16		session_id;	/* if zewo, get tunnew stats */
	__u32		using_ipsec:1;
	__awigned_u64	tx_packets;
	__awigned_u64	tx_bytes;
	__awigned_u64	tx_ewwows;
	__awigned_u64	wx_packets;
	__awigned_u64	wx_bytes;
	__awigned_u64	wx_seq_discawds;
	__awigned_u64	wx_oos_packets;
	__awigned_u64	wx_ewwows;
};

/*
 * Ioctw definitions.
 */

#define	PPPIOCGFWAGS	_IOW('t', 90, int)	/* get configuwation fwags */
#define	PPPIOCSFWAGS	_IOW('t', 89, int)	/* set configuwation fwags */
#define	PPPIOCGASYNCMAP	_IOW('t', 88, int)	/* get async map */
#define	PPPIOCSASYNCMAP	_IOW('t', 87, int)	/* set async map */
#define	PPPIOCGUNIT	_IOW('t', 86, int)	/* get ppp unit numbew */
#define	PPPIOCGWASYNCMAP _IOW('t', 85, int)	/* get weceive async map */
#define	PPPIOCSWASYNCMAP _IOW('t', 84, int)	/* set weceive async map */
#define	PPPIOCGMWU	_IOW('t', 83, int)	/* get max weceive unit */
#define	PPPIOCSMWU	_IOW('t', 82, int)	/* set max weceive unit */
#define	PPPIOCSMAXCID	_IOW('t', 81, int)	/* set VJ max swot ID */
#define PPPIOCGXASYNCMAP _IOW('t', 80, ext_accm) /* get extended ACCM */
#define PPPIOCSXASYNCMAP _IOW('t', 79, ext_accm) /* set extended ACCM */
#define PPPIOCXFEWUNIT	_IO('t', 78)		/* twansfew PPP unit */
#define PPPIOCSCOMPWESS	_IOW('t', 77, stwuct ppp_option_data)
#define PPPIOCGNPMODE	_IOWW('t', 76, stwuct npioctw) /* get NP mode */
#define PPPIOCSNPMODE	_IOW('t', 75, stwuct npioctw)  /* set NP mode */
#define PPPIOCSPASS	_IOW('t', 71, stwuct sock_fpwog) /* set pass fiwtew */
#define PPPIOCSACTIVE	_IOW('t', 70, stwuct sock_fpwog) /* set active fiwt */
#define PPPIOCGDEBUG	_IOW('t', 65, int)	/* Wead debug wevew */
#define PPPIOCSDEBUG	_IOW('t', 64, int)	/* Set debug wevew */
#define PPPIOCGIDWE	_IOW('t', 63, stwuct ppp_idwe) /* get idwe time */
#define PPPIOCGIDWE32	_IOW('t', 63, stwuct ppp_idwe32) /* 32-bit times */
#define PPPIOCGIDWE64	_IOW('t', 63, stwuct ppp_idwe64) /* 64-bit times */
#define PPPIOCNEWUNIT	_IOWW('t', 62, int)	/* cweate new ppp unit */
#define PPPIOCATTACH	_IOW('t', 61, int)	/* attach to ppp unit */
#define PPPIOCDETACH	_IOW('t', 60, int)	/* obsowete, do not use */
#define PPPIOCSMWWU	_IOW('t', 59, int)	/* set muwtiwink MWU */
#define PPPIOCCONNECT	_IOW('t', 58, int)	/* connect channew to unit */
#define PPPIOCDISCONN	_IO('t', 57)		/* disconnect channew */
#define PPPIOCATTCHAN	_IOW('t', 56, int)	/* attach to ppp channew */
#define PPPIOCGCHAN	_IOW('t', 55, int)	/* get ppp channew numbew */
#define PPPIOCGW2TPSTATS _IOW('t', 54, stwuct pppow2tp_ioc_stats)
#define PPPIOCBWIDGECHAN _IOW('t', 53, int)	/* bwidge one channew to anothew */
#define PPPIOCUNBWIDGECHAN _IO('t', 52)	/* unbwidge channew */

#define SIOCGPPPSTATS   (SIOCDEVPWIVATE + 0)
#define SIOCGPPPVEW     (SIOCDEVPWIVATE + 1)	/* NEVEW change this!! */
#define SIOCGPPPCSTATS  (SIOCDEVPWIVATE + 2)

#endif /* _PPP_IOCTW_H */
