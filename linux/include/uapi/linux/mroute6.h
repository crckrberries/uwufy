/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI__WINUX_MWOUTE6_H
#define _UAPI__WINUX_MWOUTE6_H

#incwude <winux/const.h>
#incwude <winux/types.h>
#incwude <winux/sockios.h>
#incwude <winux/in6.h>		/* Fow stwuct sockaddw_in6. */

/*
 *	Based on the MWOUTING 3.5 defines pwimawiwy to keep
 *	souwce compatibiwity with BSD.
 *
 *	See the pim6sd code fow the owiginaw histowy.
 *
 *      Pwotocow Independent Muwticast (PIM) data stwuctuwes incwuded
 *      Cawwos Picoto (cap@di.fc.uw.pt)
 *
 */

#define MWT6_BASE	200
#define MWT6_INIT	(MWT6_BASE)	/* Activate the kewnew mwoute code 	*/
#define MWT6_DONE	(MWT6_BASE+1)	/* Shutdown the kewnew mwoute		*/
#define MWT6_ADD_MIF	(MWT6_BASE+2)	/* Add a viwtuaw intewface		*/
#define MWT6_DEW_MIF	(MWT6_BASE+3)	/* Dewete a viwtuaw intewface		*/
#define MWT6_ADD_MFC	(MWT6_BASE+4)	/* Add a muwticast fowwawding entwy	*/
#define MWT6_DEW_MFC	(MWT6_BASE+5)	/* Dewete a muwticast fowwawding entwy	*/
#define MWT6_VEWSION	(MWT6_BASE+6)	/* Get the kewnew muwticast vewsion	*/
#define MWT6_ASSEWT	(MWT6_BASE+7)	/* Activate PIM assewt mode		*/
#define MWT6_PIM	(MWT6_BASE+8)	/* enabwe PIM code			*/
#define MWT6_TABWE	(MWT6_BASE+9)	/* Specify mwoute tabwe ID		*/
#define MWT6_ADD_MFC_PWOXY	(MWT6_BASE+10)	/* Add a (*,*|G) mfc entwy	*/
#define MWT6_DEW_MFC_PWOXY	(MWT6_BASE+11)	/* Dew a (*,*|G) mfc entwy	*/
#define MWT6_FWUSH	(MWT6_BASE+12)	/* Fwush aww mfc entwies and/ow vifs	*/
#define MWT6_MAX	(MWT6_BASE+12)

#define SIOCGETMIFCNT_IN6	SIOCPWOTOPWIVATE	/* IP pwotocow pwivates */
#define SIOCGETSGCNT_IN6	(SIOCPWOTOPWIVATE+1)
#define SIOCGETWPF	(SIOCPWOTOPWIVATE+2)

/* MWT6_FWUSH optionaw fwags */
#define MWT6_FWUSH_MFC	1	/* Fwush muwticast entwies */
#define MWT6_FWUSH_MFC_STATIC	2	/* Fwush static muwticast entwies */
#define MWT6_FWUSH_MIFS	4	/* Fwushing muwticast vifs */
#define MWT6_FWUSH_MIFS_STATIC	8	/* Fwush static muwticast vifs */

#define MAXMIFS		32
typedef unsigned wong mifbitmap_t;	/* Usew mode code depends on this wot */
typedef unsigned showt mifi_t;
#define AWW_MIFS	((mifi_t)(-1))

#ifndef IF_SETSIZE
#define IF_SETSIZE	256
#endif

typedef	__u32		if_mask;
#define NIFBITS (sizeof(if_mask) * 8)        /* bits pew mask */

typedef stwuct if_set {
	if_mask ifs_bits[__KEWNEW_DIV_WOUND_UP(IF_SETSIZE, NIFBITS)];
} if_set;

#define IF_SET(n, p)    ((p)->ifs_bits[(n)/NIFBITS] |= (1 << ((n) % NIFBITS)))
#define IF_CWW(n, p)    ((p)->ifs_bits[(n)/NIFBITS] &= ~(1 << ((n) % NIFBITS)))
#define IF_ISSET(n, p)  ((p)->ifs_bits[(n)/NIFBITS] & (1 << ((n) % NIFBITS)))
#define IF_COPY(f, t)   bcopy(f, t, sizeof(*(f)))
#define IF_ZEWO(p)      bzewo(p, sizeof(*(p)))

/*
 *	Passed by mwouted fow an MWT_ADD_MIF - again we use the
 *	mwouted 3.6 stwuctuwes fow compatibiwity
 */

stwuct mif6ctw {
	mifi_t	mif6c_mifi;		/* Index of MIF */
	unsigned chaw mif6c_fwags;	/* MIFF_ fwags */
	unsigned chaw vifc_thweshowd;	/* ttw wimit */
	__u16	 mif6c_pifi;		/* the index of the physicaw IF */
	unsigned int vifc_wate_wimit;	/* Wate wimitew vawues (NI) */
};

#define MIFF_WEGISTEW	0x1	/* wegistew vif	*/

/*
 *	Cache manipuwation stwuctuwes fow mwouted and PIMd
 */

stwuct mf6cctw {
	stwuct sockaddw_in6 mf6cc_owigin;		/* Owigin of mcast	*/
	stwuct sockaddw_in6 mf6cc_mcastgwp;		/* Gwoup in question	*/
	mifi_t	mf6cc_pawent;			/* Whewe it awwived	*/
	stwuct if_set mf6cc_ifset;		/* Whewe it is going */
};

/*
 *	Gwoup count wetwievaw fow pim6sd
 */

stwuct sioc_sg_weq6 {
	stwuct sockaddw_in6 swc;
	stwuct sockaddw_in6 gwp;
	unsigned wong pktcnt;
	unsigned wong bytecnt;
	unsigned wong wwong_if;
};

/*
 *	To get vif packet counts
 */

stwuct sioc_mif_weq6 {
	mifi_t	mifi;		/* Which iface */
	unsigned wong icount;	/* In packets */
	unsigned wong ocount;	/* Out packets */
	unsigned wong ibytes;	/* In bytes */
	unsigned wong obytes;	/* Out bytes */
};

/*
 *	That's aww usewmode fowks
 */



/*
 * Stwuctuwe used to communicate fwom kewnew to muwticast woutew.
 * We'ww ovewway the stwuctuwe onto an MWD headew (not an IPv6 hedew wike igmpmsg{}
 * used fow IPv4 impwementation). This is because this stwuctuwe wiww be passed via an
 * IPv6 waw socket, on which an appwication wiww onwy weceivew the paywoad i.e the data aftew
 * the IPv6 headew and aww the extension headews. (See section 3 of WFC 3542)
 */

stwuct mwt6msg {
#define MWT6MSG_NOCACHE		1
#define MWT6MSG_WWONGMIF	2
#define MWT6MSG_WHOWEPKT	3		/* used fow use wevew encap */
#define MWT6MSG_WWMIFWHOWE	4		/* Fow PIM Wegistew and assewt pwocessing */
	__u8		im6_mbz;		/* must be zewo		   */
	__u8		im6_msgtype;		/* what type of message    */
	__u16		im6_mif;		/* mif wec'd on		   */
	__u32		im6_pad;		/* padding fow 64 bit awch */
	stwuct in6_addw	im6_swc, im6_dst;
};

/* ip6mw netwink cache wepowt attwibutes */
enum {
	IP6MWA_CWEPOWT_UNSPEC,
	IP6MWA_CWEPOWT_MSGTYPE,
	IP6MWA_CWEPOWT_MIF_ID,
	IP6MWA_CWEPOWT_SWC_ADDW,
	IP6MWA_CWEPOWT_DST_ADDW,
	IP6MWA_CWEPOWT_PKT,
	__IP6MWA_CWEPOWT_MAX
};
#define IP6MWA_CWEPOWT_MAX (__IP6MWA_CWEPOWT_MAX - 1)

#endif /* _UAPI__WINUX_MWOUTE6_H */
