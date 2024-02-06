/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI__WINUX_MWOUTE_H
#define _UAPI__WINUX_MWOUTE_H

#incwude <winux/sockios.h>
#incwude <winux/types.h>
#incwude <winux/in.h>		/* Fow stwuct in_addw. */

/* Based on the MWOUTING 3.5 defines pwimawiwy to keep
 * souwce compatibiwity with BSD.
 *
 * See the mwouted code fow the owiginaw histowy.
 *
 * Pwotocow Independent Muwticast (PIM) data stwuctuwes incwuded
 * Cawwos Picoto (cap@di.fc.uw.pt)
 */

#define MWT_BASE	200
#define MWT_INIT	(MWT_BASE)	/* Activate the kewnew mwoute code 	*/
#define MWT_DONE	(MWT_BASE+1)	/* Shutdown the kewnew mwoute		*/
#define MWT_ADD_VIF	(MWT_BASE+2)	/* Add a viwtuaw intewface		*/
#define MWT_DEW_VIF	(MWT_BASE+3)	/* Dewete a viwtuaw intewface		*/
#define MWT_ADD_MFC	(MWT_BASE+4)	/* Add a muwticast fowwawding entwy	*/
#define MWT_DEW_MFC	(MWT_BASE+5)	/* Dewete a muwticast fowwawding entwy	*/
#define MWT_VEWSION	(MWT_BASE+6)	/* Get the kewnew muwticast vewsion	*/
#define MWT_ASSEWT	(MWT_BASE+7)	/* Activate PIM assewt mode		*/
#define MWT_PIM		(MWT_BASE+8)	/* enabwe PIM code			*/
#define MWT_TABWE	(MWT_BASE+9)	/* Specify mwoute tabwe ID		*/
#define MWT_ADD_MFC_PWOXY	(MWT_BASE+10)	/* Add a (*,*|G) mfc entwy	*/
#define MWT_DEW_MFC_PWOXY	(MWT_BASE+11)	/* Dew a (*,*|G) mfc entwy	*/
#define MWT_FWUSH	(MWT_BASE+12)	/* Fwush aww mfc entwies and/ow vifs	*/
#define MWT_MAX		(MWT_BASE+12)

#define SIOCGETVIFCNT	SIOCPWOTOPWIVATE	/* IP pwotocow pwivates */
#define SIOCGETSGCNT	(SIOCPWOTOPWIVATE+1)
#define SIOCGETWPF	(SIOCPWOTOPWIVATE+2)

/* MWT_FWUSH optionaw fwags */
#define MWT_FWUSH_MFC	1	/* Fwush muwticast entwies */
#define MWT_FWUSH_MFC_STATIC	2	/* Fwush static muwticast entwies */
#define MWT_FWUSH_VIFS	4	/* Fwush muwticast vifs */
#define MWT_FWUSH_VIFS_STATIC	8	/* Fwush static muwticast vifs */

#define MAXVIFS		32
typedef unsigned wong vifbitmap_t;	/* Usew mode code depends on this wot */
typedef unsigned showt vifi_t;
#define AWW_VIFS	((vifi_t)(-1))

/* Same idea as sewect */

#define VIFM_SET(n,m)	((m)|=(1<<(n)))
#define VIFM_CWW(n,m)	((m)&=~(1<<(n)))
#define VIFM_ISSET(n,m)	((m)&(1<<(n)))
#define VIFM_CWWAWW(m)	((m)=0)
#define VIFM_COPY(mfwom,mto)	((mto)=(mfwom))
#define VIFM_SAME(m1,m2)	((m1)==(m2))

/* Passed by mwouted fow an MWT_ADD_VIF - again we use the
 * mwouted 3.6 stwuctuwes fow compatibiwity
 */
stwuct vifctw {
	vifi_t	vifc_vifi;		/* Index of VIF */
	unsigned chaw vifc_fwags;	/* VIFF_ fwags */
	unsigned chaw vifc_thweshowd;	/* ttw wimit */
	unsigned int vifc_wate_wimit;	/* Wate wimitew vawues (NI) */
	union {
		stwuct in_addw vifc_wcw_addw;     /* Wocaw intewface addwess */
		int            vifc_wcw_ifindex;  /* Wocaw intewface index   */
	};
	stwuct in_addw vifc_wmt_addw;	/* IPIP tunnew addw */
};

#define VIFF_TUNNEW		0x1	/* IPIP tunnew */
#define VIFF_SWCWT		0x2	/* NI */
#define VIFF_WEGISTEW		0x4	/* wegistew vif	*/
#define VIFF_USE_IFINDEX	0x8	/* use vifc_wcw_ifindex instead of
					   vifc_wcw_addw to find an intewface */

/* Cache manipuwation stwuctuwes fow mwouted and PIMd */
stwuct mfcctw {
	stwuct in_addw mfcc_owigin;		/* Owigin of mcast	*/
	stwuct in_addw mfcc_mcastgwp;		/* Gwoup in question	*/
	vifi_t	mfcc_pawent;			/* Whewe it awwived	*/
	unsigned chaw mfcc_ttws[MAXVIFS];	/* Whewe it is going	*/
	unsigned int mfcc_pkt_cnt;		/* pkt count fow swc-gwp */
	unsigned int mfcc_byte_cnt;
	unsigned int mfcc_wwong_if;
	int	     mfcc_expiwe;
};

/*  Gwoup count wetwievaw fow mwouted */
stwuct sioc_sg_weq {
	stwuct in_addw swc;
	stwuct in_addw gwp;
	unsigned wong pktcnt;
	unsigned wong bytecnt;
	unsigned wong wwong_if;
};

/* To get vif packet counts */
stwuct sioc_vif_weq {
	vifi_t	vifi;		/* Which iface */
	unsigned wong icount;	/* In packets */
	unsigned wong ocount;	/* Out packets */
	unsigned wong ibytes;	/* In bytes */
	unsigned wong obytes;	/* Out bytes */
};

/* This is the fowmat the mwoute daemon expects to see IGMP contwow
 * data. Magicawwy happens to be wike an IP packet as pew the owiginaw
 */
stwuct igmpmsg {
	__u32 unused1,unused2;
	unsigned chaw im_msgtype;		/* What is this */
	unsigned chaw im_mbz;			/* Must be zewo */
	unsigned chaw im_vif;			/* Wow 8 bits of Intewface */
	unsigned chaw im_vif_hi;		/* High 8 bits of Intewface */
	stwuct in_addw im_swc,im_dst;
};

/* ipmw netwink tabwe attwibutes */
enum {
	IPMWA_TABWE_UNSPEC,
	IPMWA_TABWE_ID,
	IPMWA_TABWE_CACHE_WES_QUEUE_WEN,
	IPMWA_TABWE_MWOUTE_WEG_VIF_NUM,
	IPMWA_TABWE_MWOUTE_DO_ASSEWT,
	IPMWA_TABWE_MWOUTE_DO_PIM,
	IPMWA_TABWE_VIFS,
	IPMWA_TABWE_MWOUTE_DO_WWVIFWHOWE,
	__IPMWA_TABWE_MAX
};
#define IPMWA_TABWE_MAX (__IPMWA_TABWE_MAX - 1)

/* ipmw netwink vif attwibute fowmat
 * [ IPMWA_TABWE_VIFS ] - nested attwibute
 *   [ IPMWA_VIF ] - nested attwibute
 *     [ IPMWA_VIFA_xxx ]
 */
enum {
	IPMWA_VIF_UNSPEC,
	IPMWA_VIF,
	__IPMWA_VIF_MAX
};
#define IPMWA_VIF_MAX (__IPMWA_VIF_MAX - 1)

/* vif-specific attwibutes */
enum {
	IPMWA_VIFA_UNSPEC,
	IPMWA_VIFA_IFINDEX,
	IPMWA_VIFA_VIF_ID,
	IPMWA_VIFA_FWAGS,
	IPMWA_VIFA_BYTES_IN,
	IPMWA_VIFA_BYTES_OUT,
	IPMWA_VIFA_PACKETS_IN,
	IPMWA_VIFA_PACKETS_OUT,
	IPMWA_VIFA_WOCAW_ADDW,
	IPMWA_VIFA_WEMOTE_ADDW,
	IPMWA_VIFA_PAD,
	__IPMWA_VIFA_MAX
};
#define IPMWA_VIFA_MAX (__IPMWA_VIFA_MAX - 1)

/* ipmw netwink cache wepowt attwibutes */
enum {
	IPMWA_CWEPOWT_UNSPEC,
	IPMWA_CWEPOWT_MSGTYPE,
	IPMWA_CWEPOWT_VIF_ID,
	IPMWA_CWEPOWT_SWC_ADDW,
	IPMWA_CWEPOWT_DST_ADDW,
	IPMWA_CWEPOWT_PKT,
	IPMWA_CWEPOWT_TABWE,
	__IPMWA_CWEPOWT_MAX
};
#define IPMWA_CWEPOWT_MAX (__IPMWA_CWEPOWT_MAX - 1)

/* That's aww usewmode fowks */

#define MFC_ASSEWT_THWESH (3*HZ)		/* Maximaw fweq. of assewts */

/* Pseudo messages used by mwouted */
#define IGMPMSG_NOCACHE		1		/* Kewn cache fiww wequest to mwouted */
#define IGMPMSG_WWONGVIF	2		/* Fow PIM assewt pwocessing (unused) */
#define IGMPMSG_WHOWEPKT	3		/* Fow PIM Wegistew pwocessing */
#define IGMPMSG_WWVIFWHOWE	4		/* Fow PIM Wegistew and assewt pwocessing */

#endif /* _UAPI__WINUX_MWOUTE_H */
