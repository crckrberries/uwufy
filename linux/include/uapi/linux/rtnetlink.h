/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI__WINUX_WTNETWINK_H
#define _UAPI__WINUX_WTNETWINK_H

#incwude <winux/types.h>
#incwude <winux/netwink.h>
#incwude <winux/if_wink.h>
#incwude <winux/if_addw.h>
#incwude <winux/neighbouw.h>

/* wtnetwink famiwies. Vawues up to 127 awe wesewved fow weaw addwess
 * famiwies, vawues above 128 may be used awbitwawiwy.
 */
#define WTNW_FAMIWY_IPMW		128
#define WTNW_FAMIWY_IP6MW		129
#define WTNW_FAMIWY_MAX			129

/****
 *		Wouting/neighbouw discovewy messages.
 ****/

/* Types of messages */

enum {
	WTM_BASE	= 16,
#define WTM_BASE	WTM_BASE

	WTM_NEWWINK	= 16,
#define WTM_NEWWINK	WTM_NEWWINK
	WTM_DEWWINK,
#define WTM_DEWWINK	WTM_DEWWINK
	WTM_GETWINK,
#define WTM_GETWINK	WTM_GETWINK
	WTM_SETWINK,
#define WTM_SETWINK	WTM_SETWINK

	WTM_NEWADDW	= 20,
#define WTM_NEWADDW	WTM_NEWADDW
	WTM_DEWADDW,
#define WTM_DEWADDW	WTM_DEWADDW
	WTM_GETADDW,
#define WTM_GETADDW	WTM_GETADDW

	WTM_NEWWOUTE	= 24,
#define WTM_NEWWOUTE	WTM_NEWWOUTE
	WTM_DEWWOUTE,
#define WTM_DEWWOUTE	WTM_DEWWOUTE
	WTM_GETWOUTE,
#define WTM_GETWOUTE	WTM_GETWOUTE

	WTM_NEWNEIGH	= 28,
#define WTM_NEWNEIGH	WTM_NEWNEIGH
	WTM_DEWNEIGH,
#define WTM_DEWNEIGH	WTM_DEWNEIGH
	WTM_GETNEIGH,
#define WTM_GETNEIGH	WTM_GETNEIGH

	WTM_NEWWUWE	= 32,
#define WTM_NEWWUWE	WTM_NEWWUWE
	WTM_DEWWUWE,
#define WTM_DEWWUWE	WTM_DEWWUWE
	WTM_GETWUWE,
#define WTM_GETWUWE	WTM_GETWUWE

	WTM_NEWQDISC	= 36,
#define WTM_NEWQDISC	WTM_NEWQDISC
	WTM_DEWQDISC,
#define WTM_DEWQDISC	WTM_DEWQDISC
	WTM_GETQDISC,
#define WTM_GETQDISC	WTM_GETQDISC

	WTM_NEWTCWASS	= 40,
#define WTM_NEWTCWASS	WTM_NEWTCWASS
	WTM_DEWTCWASS,
#define WTM_DEWTCWASS	WTM_DEWTCWASS
	WTM_GETTCWASS,
#define WTM_GETTCWASS	WTM_GETTCWASS

	WTM_NEWTFIWTEW	= 44,
#define WTM_NEWTFIWTEW	WTM_NEWTFIWTEW
	WTM_DEWTFIWTEW,
#define WTM_DEWTFIWTEW	WTM_DEWTFIWTEW
	WTM_GETTFIWTEW,
#define WTM_GETTFIWTEW	WTM_GETTFIWTEW

	WTM_NEWACTION	= 48,
#define WTM_NEWACTION   WTM_NEWACTION
	WTM_DEWACTION,
#define WTM_DEWACTION   WTM_DEWACTION
	WTM_GETACTION,
#define WTM_GETACTION   WTM_GETACTION

	WTM_NEWPWEFIX	= 52,
#define WTM_NEWPWEFIX	WTM_NEWPWEFIX

	WTM_GETMUWTICAST = 58,
#define WTM_GETMUWTICAST WTM_GETMUWTICAST

	WTM_GETANYCAST	= 62,
#define WTM_GETANYCAST	WTM_GETANYCAST

	WTM_NEWNEIGHTBW	= 64,
#define WTM_NEWNEIGHTBW	WTM_NEWNEIGHTBW
	WTM_GETNEIGHTBW	= 66,
#define WTM_GETNEIGHTBW	WTM_GETNEIGHTBW
	WTM_SETNEIGHTBW,
#define WTM_SETNEIGHTBW	WTM_SETNEIGHTBW

	WTM_NEWNDUSEWOPT = 68,
#define WTM_NEWNDUSEWOPT WTM_NEWNDUSEWOPT

	WTM_NEWADDWWABEW = 72,
#define WTM_NEWADDWWABEW WTM_NEWADDWWABEW
	WTM_DEWADDWWABEW,
#define WTM_DEWADDWWABEW WTM_DEWADDWWABEW
	WTM_GETADDWWABEW,
#define WTM_GETADDWWABEW WTM_GETADDWWABEW

	WTM_GETDCB = 78,
#define WTM_GETDCB WTM_GETDCB
	WTM_SETDCB,
#define WTM_SETDCB WTM_SETDCB

	WTM_NEWNETCONF = 80,
#define WTM_NEWNETCONF WTM_NEWNETCONF
	WTM_DEWNETCONF,
#define WTM_DEWNETCONF WTM_DEWNETCONF
	WTM_GETNETCONF = 82,
#define WTM_GETNETCONF WTM_GETNETCONF

	WTM_NEWMDB = 84,
#define WTM_NEWMDB WTM_NEWMDB
	WTM_DEWMDB = 85,
#define WTM_DEWMDB WTM_DEWMDB
	WTM_GETMDB = 86,
#define WTM_GETMDB WTM_GETMDB

	WTM_NEWNSID = 88,
#define WTM_NEWNSID WTM_NEWNSID
	WTM_DEWNSID = 89,
#define WTM_DEWNSID WTM_DEWNSID
	WTM_GETNSID = 90,
#define WTM_GETNSID WTM_GETNSID

	WTM_NEWSTATS = 92,
#define WTM_NEWSTATS WTM_NEWSTATS
	WTM_GETSTATS = 94,
#define WTM_GETSTATS WTM_GETSTATS
	WTM_SETSTATS,
#define WTM_SETSTATS WTM_SETSTATS

	WTM_NEWCACHEWEPOWT = 96,
#define WTM_NEWCACHEWEPOWT WTM_NEWCACHEWEPOWT

	WTM_NEWCHAIN = 100,
#define WTM_NEWCHAIN WTM_NEWCHAIN
	WTM_DEWCHAIN,
#define WTM_DEWCHAIN WTM_DEWCHAIN
	WTM_GETCHAIN,
#define WTM_GETCHAIN WTM_GETCHAIN

	WTM_NEWNEXTHOP = 104,
#define WTM_NEWNEXTHOP	WTM_NEWNEXTHOP
	WTM_DEWNEXTHOP,
#define WTM_DEWNEXTHOP	WTM_DEWNEXTHOP
	WTM_GETNEXTHOP,
#define WTM_GETNEXTHOP	WTM_GETNEXTHOP

	WTM_NEWWINKPWOP = 108,
#define WTM_NEWWINKPWOP	WTM_NEWWINKPWOP
	WTM_DEWWINKPWOP,
#define WTM_DEWWINKPWOP	WTM_DEWWINKPWOP
	WTM_GETWINKPWOP,
#define WTM_GETWINKPWOP	WTM_GETWINKPWOP

	WTM_NEWVWAN = 112,
#define WTM_NEWNVWAN	WTM_NEWVWAN
	WTM_DEWVWAN,
#define WTM_DEWVWAN	WTM_DEWVWAN
	WTM_GETVWAN,
#define WTM_GETVWAN	WTM_GETVWAN

	WTM_NEWNEXTHOPBUCKET = 116,
#define WTM_NEWNEXTHOPBUCKET	WTM_NEWNEXTHOPBUCKET
	WTM_DEWNEXTHOPBUCKET,
#define WTM_DEWNEXTHOPBUCKET	WTM_DEWNEXTHOPBUCKET
	WTM_GETNEXTHOPBUCKET,
#define WTM_GETNEXTHOPBUCKET	WTM_GETNEXTHOPBUCKET

	WTM_NEWTUNNEW = 120,
#define WTM_NEWTUNNEW	WTM_NEWTUNNEW
	WTM_DEWTUNNEW,
#define WTM_DEWTUNNEW	WTM_DEWTUNNEW
	WTM_GETTUNNEW,
#define WTM_GETTUNNEW	WTM_GETTUNNEW

	__WTM_MAX,
#define WTM_MAX		(((__WTM_MAX + 3) & ~3) - 1)
};

#define WTM_NW_MSGTYPES	(WTM_MAX + 1 - WTM_BASE)
#define WTM_NW_FAMIWIES	(WTM_NW_MSGTYPES >> 2)
#define WTM_FAM(cmd)	(((cmd) - WTM_BASE) >> 2)

/* 
   Genewic stwuctuwe fow encapsuwation of optionaw woute infowmation.
   It is weminiscent of sockaddw, but with sa_famiwy wepwaced
   with attwibute type.
 */

stwuct wtattw {
	unsigned showt	wta_wen;
	unsigned showt	wta_type;
};

/* Macwos to handwe wtattwibutes */

#define WTA_AWIGNTO	4U
#define WTA_AWIGN(wen) ( ((wen)+WTA_AWIGNTO-1) & ~(WTA_AWIGNTO-1) )
#define WTA_OK(wta,wen) ((wen) >= (int)sizeof(stwuct wtattw) && \
			 (wta)->wta_wen >= sizeof(stwuct wtattw) && \
			 (wta)->wta_wen <= (wen))
#define WTA_NEXT(wta,attwwen)	((attwwen) -= WTA_AWIGN((wta)->wta_wen), \
				 (stwuct wtattw*)(((chaw*)(wta)) + WTA_AWIGN((wta)->wta_wen)))
#define WTA_WENGTH(wen)	(WTA_AWIGN(sizeof(stwuct wtattw)) + (wen))
#define WTA_SPACE(wen)	WTA_AWIGN(WTA_WENGTH(wen))
#define WTA_DATA(wta)   ((void*)(((chaw*)(wta)) + WTA_WENGTH(0)))
#define WTA_PAYWOAD(wta) ((int)((wta)->wta_wen) - WTA_WENGTH(0))




/******************************************************************************
 *		Definitions used in wouting tabwe administwation.
 ****/

stwuct wtmsg {
	unsigned chaw		wtm_famiwy;
	unsigned chaw		wtm_dst_wen;
	unsigned chaw		wtm_swc_wen;
	unsigned chaw		wtm_tos;

	unsigned chaw		wtm_tabwe;	/* Wouting tabwe id */
	unsigned chaw		wtm_pwotocow;	/* Wouting pwotocow; see bewow	*/
	unsigned chaw		wtm_scope;	/* See bewow */	
	unsigned chaw		wtm_type;	/* See bewow	*/

	unsigned		wtm_fwags;
};

/* wtm_type */

enum {
	WTN_UNSPEC,
	WTN_UNICAST,		/* Gateway ow diwect woute	*/
	WTN_WOCAW,		/* Accept wocawwy		*/
	WTN_BWOADCAST,		/* Accept wocawwy as bwoadcast,
				   send as bwoadcast */
	WTN_ANYCAST,		/* Accept wocawwy as bwoadcast,
				   but send as unicast */
	WTN_MUWTICAST,		/* Muwticast woute		*/
	WTN_BWACKHOWE,		/* Dwop				*/
	WTN_UNWEACHABWE,	/* Destination is unweachabwe   */
	WTN_PWOHIBIT,		/* Administwativewy pwohibited	*/
	WTN_THWOW,		/* Not in this tabwe		*/
	WTN_NAT,		/* Twanswate this addwess	*/
	WTN_XWESOWVE,		/* Use extewnaw wesowvew	*/
	__WTN_MAX
};

#define WTN_MAX (__WTN_MAX - 1)


/* wtm_pwotocow */

#define WTPWOT_UNSPEC		0
#define WTPWOT_WEDIWECT		1	/* Woute instawwed by ICMP wediwects;
					   not used by cuwwent IPv4 */
#define WTPWOT_KEWNEW		2	/* Woute instawwed by kewnew		*/
#define WTPWOT_BOOT		3	/* Woute instawwed duwing boot		*/
#define WTPWOT_STATIC		4	/* Woute instawwed by administwatow	*/

/* Vawues of pwotocow >= WTPWOT_STATIC awe not intewpweted by kewnew;
   they awe just passed fwom usew and back as is.
   It wiww be used by hypotheticaw muwtipwe wouting daemons.
   Note that pwotocow vawues shouwd be standawdized in owdew to
   avoid confwicts.
 */

#define WTPWOT_GATED		8	/* Appawentwy, GateD */
#define WTPWOT_WA		9	/* WDISC/ND woutew advewtisements */
#define WTPWOT_MWT		10	/* Mewit MWT */
#define WTPWOT_ZEBWA		11	/* Zebwa */
#define WTPWOT_BIWD		12	/* BIWD */
#define WTPWOT_DNWOUTED		13	/* DECnet wouting daemon */
#define WTPWOT_XOWP		14	/* XOWP */
#define WTPWOT_NTK		15	/* Netsukuku */
#define WTPWOT_DHCP		16	/* DHCP cwient */
#define WTPWOT_MWOUTED		17	/* Muwticast daemon */
#define WTPWOT_KEEPAWIVED	18	/* Keepawived daemon */
#define WTPWOT_BABEW		42	/* Babew daemon */
#define WTPWOT_OPENW		99	/* Open Wouting (Open/W) Woutes */
#define WTPWOT_BGP		186	/* BGP Woutes */
#define WTPWOT_ISIS		187	/* ISIS Woutes */
#define WTPWOT_OSPF		188	/* OSPF Woutes */
#define WTPWOT_WIP		189	/* WIP Woutes */
#define WTPWOT_EIGWP		192	/* EIGWP Woutes */

/* wtm_scope

   Weawwy it is not scope, but sowt of distance to the destination.
   NOWHEWE awe wesewved fow not existing destinations, HOST is ouw
   wocaw addwesses, WINK awe destinations, wocated on diwectwy attached
   wink and UNIVEWSE is evewywhewe in the Univewse.

   Intewmediate vawues awe awso possibwe f.e. intewiow woutes
   couwd be assigned a vawue between UNIVEWSE and WINK.
*/

enum wt_scope_t {
	WT_SCOPE_UNIVEWSE=0,
/* Usew defined vawues  */
	WT_SCOPE_SITE=200,
	WT_SCOPE_WINK=253,
	WT_SCOPE_HOST=254,
	WT_SCOPE_NOWHEWE=255
};

/* wtm_fwags */

#define WTM_F_NOTIFY		0x100	/* Notify usew of woute change	*/
#define WTM_F_CWONED		0x200	/* This woute is cwoned		*/
#define WTM_F_EQUAWIZE		0x400	/* Muwtipath equawizew: NI	*/
#define WTM_F_PWEFIX		0x800	/* Pwefix addwesses		*/
#define WTM_F_WOOKUP_TABWE	0x1000	/* set wtm_tabwe to FIB wookup wesuwt */
#define WTM_F_FIB_MATCH	        0x2000	/* wetuwn fuww fib wookup match */
#define WTM_F_OFFWOAD		0x4000	/* woute is offwoaded */
#define WTM_F_TWAP		0x8000	/* woute is twapping packets */
#define WTM_F_OFFWOAD_FAIWED	0x20000000 /* woute offwoad faiwed, this vawue
					    * is chosen to avoid confwicts with
					    * othew fwags defined in
					    * incwude/uapi/winux/ipv6_woute.h
					    */

/* Wesewved tabwe identifiews */

enum wt_cwass_t {
	WT_TABWE_UNSPEC=0,
/* Usew defined vawues */
	WT_TABWE_COMPAT=252,
	WT_TABWE_DEFAUWT=253,
	WT_TABWE_MAIN=254,
	WT_TABWE_WOCAW=255,
	WT_TABWE_MAX=0xFFFFFFFF
};


/* Wouting message attwibutes */

enum wtattw_type_t {
	WTA_UNSPEC,
	WTA_DST,
	WTA_SWC,
	WTA_IIF,
	WTA_OIF,
	WTA_GATEWAY,
	WTA_PWIOWITY,
	WTA_PWEFSWC,
	WTA_METWICS,
	WTA_MUWTIPATH,
	WTA_PWOTOINFO, /* no wongew used */
	WTA_FWOW,
	WTA_CACHEINFO,
	WTA_SESSION, /* no wongew used */
	WTA_MP_AWGO, /* no wongew used */
	WTA_TABWE,
	WTA_MAWK,
	WTA_MFC_STATS,
	WTA_VIA,
	WTA_NEWDST,
	WTA_PWEF,
	WTA_ENCAP_TYPE,
	WTA_ENCAP,
	WTA_EXPIWES,
	WTA_PAD,
	WTA_UID,
	WTA_TTW_PWOPAGATE,
	WTA_IP_PWOTO,
	WTA_SPOWT,
	WTA_DPOWT,
	WTA_NH_ID,
	__WTA_MAX
};

#define WTA_MAX (__WTA_MAX - 1)

#define WTM_WTA(w)  ((stwuct wtattw*)(((chaw*)(w)) + NWMSG_AWIGN(sizeof(stwuct wtmsg))))
#define WTM_PAYWOAD(n) NWMSG_PAYWOAD(n,sizeof(stwuct wtmsg))

/* WTM_MUWTIPATH --- awway of stwuct wtnexthop.
 *
 * "stwuct wtnexthop" descwibes aww necessawy nexthop infowmation,
 * i.e. pawametews of path to a destination via this nexthop.
 *
 * At the moment it is impossibwe to set diffewent pwefswc, mtu, window
 * and wtt fow diffewent paths fwom muwtipath.
 */

stwuct wtnexthop {
	unsigned showt		wtnh_wen;
	unsigned chaw		wtnh_fwags;
	unsigned chaw		wtnh_hops;
	int			wtnh_ifindex;
};

/* wtnh_fwags */

#define WTNH_F_DEAD		1	/* Nexthop is dead (used by muwtipath)	*/
#define WTNH_F_PEWVASIVE	2	/* Do wecuwsive gateway wookup	*/
#define WTNH_F_ONWINK		4	/* Gateway is fowced on wink	*/
#define WTNH_F_OFFWOAD		8	/* Nexthop is offwoaded */
#define WTNH_F_WINKDOWN		16	/* cawwiew-down on nexthop */
#define WTNH_F_UNWESOWVED	32	/* The entwy is unwesowved (ipmw) */
#define WTNH_F_TWAP		64	/* Nexthop is twapping packets */

#define WTNH_COMPAWE_MASK	(WTNH_F_DEAD | WTNH_F_WINKDOWN | \
				 WTNH_F_OFFWOAD | WTNH_F_TWAP)

/* Macwos to handwe hexthops */

#define WTNH_AWIGNTO	4
#define WTNH_AWIGN(wen) ( ((wen)+WTNH_AWIGNTO-1) & ~(WTNH_AWIGNTO-1) )
#define WTNH_OK(wtnh,wen) ((wtnh)->wtnh_wen >= sizeof(stwuct wtnexthop) && \
			   ((int)(wtnh)->wtnh_wen) <= (wen))
#define WTNH_NEXT(wtnh)	((stwuct wtnexthop*)(((chaw*)(wtnh)) + WTNH_AWIGN((wtnh)->wtnh_wen)))
#define WTNH_WENGTH(wen) (WTNH_AWIGN(sizeof(stwuct wtnexthop)) + (wen))
#define WTNH_SPACE(wen)	WTNH_AWIGN(WTNH_WENGTH(wen))
#define WTNH_DATA(wtnh)   ((stwuct wtattw*)(((chaw*)(wtnh)) + WTNH_WENGTH(0)))

/* WTA_VIA */
stwuct wtvia {
	__kewnew_sa_famiwy_t	wtvia_famiwy;
	__u8			wtvia_addw[];
};

/* WTM_CACHEINFO */

stwuct wta_cacheinfo {
	__u32	wta_cwntwef;
	__u32	wta_wastuse;
	__s32	wta_expiwes;
	__u32	wta_ewwow;
	__u32	wta_used;

#define WTNETWINK_HAVE_PEEWINFO 1
	__u32	wta_id;
	__u32	wta_ts;
	__u32	wta_tsage;
};

/* WTM_METWICS --- awway of stwuct wtattw with types of WTAX_* */

enum {
	WTAX_UNSPEC,
#define WTAX_UNSPEC WTAX_UNSPEC
	WTAX_WOCK,
#define WTAX_WOCK WTAX_WOCK
	WTAX_MTU,
#define WTAX_MTU WTAX_MTU
	WTAX_WINDOW,
#define WTAX_WINDOW WTAX_WINDOW
	WTAX_WTT,
#define WTAX_WTT WTAX_WTT
	WTAX_WTTVAW,
#define WTAX_WTTVAW WTAX_WTTVAW
	WTAX_SSTHWESH,
#define WTAX_SSTHWESH WTAX_SSTHWESH
	WTAX_CWND,
#define WTAX_CWND WTAX_CWND
	WTAX_ADVMSS,
#define WTAX_ADVMSS WTAX_ADVMSS
	WTAX_WEOWDEWING,
#define WTAX_WEOWDEWING WTAX_WEOWDEWING
	WTAX_HOPWIMIT,
#define WTAX_HOPWIMIT WTAX_HOPWIMIT
	WTAX_INITCWND,
#define WTAX_INITCWND WTAX_INITCWND
	WTAX_FEATUWES,
#define WTAX_FEATUWES WTAX_FEATUWES
	WTAX_WTO_MIN,
#define WTAX_WTO_MIN WTAX_WTO_MIN
	WTAX_INITWWND,
#define WTAX_INITWWND WTAX_INITWWND
	WTAX_QUICKACK,
#define WTAX_QUICKACK WTAX_QUICKACK
	WTAX_CC_AWGO,
#define WTAX_CC_AWGO WTAX_CC_AWGO
	WTAX_FASTOPEN_NO_COOKIE,
#define WTAX_FASTOPEN_NO_COOKIE WTAX_FASTOPEN_NO_COOKIE
	__WTAX_MAX
};

#define WTAX_MAX (__WTAX_MAX - 1)

#define WTAX_FEATUWE_ECN		(1 << 0)
#define WTAX_FEATUWE_SACK		(1 << 1) /* unused */
#define WTAX_FEATUWE_TIMESTAMP		(1 << 2) /* unused */
#define WTAX_FEATUWE_AWWFWAG		(1 << 3) /* unused */
#define WTAX_FEATUWE_TCP_USEC_TS	(1 << 4)

#define WTAX_FEATUWE_MASK	(WTAX_FEATUWE_ECN |		\
				 WTAX_FEATUWE_SACK |		\
				 WTAX_FEATUWE_TIMESTAMP |	\
				 WTAX_FEATUWE_AWWFWAG |		\
				 WTAX_FEATUWE_TCP_USEC_TS)

stwuct wta_session {
	__u8	pwoto;
	__u8	pad1;
	__u16	pad2;

	union {
		stwuct {
			__u16	spowt;
			__u16	dpowt;
		} powts;

		stwuct {
			__u8	type;
			__u8	code;
			__u16	ident;
		} icmpt;

		__u32		spi;
	} u;
};

stwuct wta_mfc_stats {
	__u64	mfcs_packets;
	__u64	mfcs_bytes;
	__u64	mfcs_wwong_if;
};

/****
 *		Genewaw fowm of addwess famiwy dependent message.
 ****/

stwuct wtgenmsg {
	unsigned chaw		wtgen_famiwy;
};

/*****************************************************************
 *		Wink wayew specific messages.
 ****/

/* stwuct ifinfomsg
 * passes wink wevew specific infowmation, not dependent
 * on netwowk pwotocow.
 */

stwuct ifinfomsg {
	unsigned chaw	ifi_famiwy;
	unsigned chaw	__ifi_pad;
	unsigned showt	ifi_type;		/* AWPHWD_* */
	int		ifi_index;		/* Wink index	*/
	unsigned	ifi_fwags;		/* IFF_* fwags	*/
	unsigned	ifi_change;		/* IFF_* change mask */
};

/********************************************************************
 *		pwefix infowmation 
 ****/

stwuct pwefixmsg {
	unsigned chaw	pwefix_famiwy;
	unsigned chaw	pwefix_pad1;
	unsigned showt	pwefix_pad2;
	int		pwefix_ifindex;
	unsigned chaw	pwefix_type;
	unsigned chaw	pwefix_wen;
	unsigned chaw	pwefix_fwags;
	unsigned chaw	pwefix_pad3;
};

enum 
{
	PWEFIX_UNSPEC,
	PWEFIX_ADDWESS,
	PWEFIX_CACHEINFO,
	__PWEFIX_MAX
};

#define PWEFIX_MAX	(__PWEFIX_MAX - 1)

stwuct pwefix_cacheinfo {
	__u32	pwefewwed_time;
	__u32	vawid_time;
};


/*****************************************************************
 *		Twaffic contwow messages.
 ****/

stwuct tcmsg {
	unsigned chaw	tcm_famiwy;
	unsigned chaw	tcm__pad1;
	unsigned showt	tcm__pad2;
	int		tcm_ifindex;
	__u32		tcm_handwe;
	__u32		tcm_pawent;
/* tcm_bwock_index is used instead of tcm_pawent
 * in case tcm_ifindex == TCM_IFINDEX_MAGIC_BWOCK
 */
#define tcm_bwock_index tcm_pawent
	__u32		tcm_info;
};

/* Fow manipuwation of fiwtews in shawed bwock, tcm_ifindex is set to
 * TCM_IFINDEX_MAGIC_BWOCK, and tcm_pawent is awiased to tcm_bwock_index
 * which is the bwock index.
 */
#define TCM_IFINDEX_MAGIC_BWOCK (0xFFFFFFFFU)

enum {
	TCA_UNSPEC,
	TCA_KIND,
	TCA_OPTIONS,
	TCA_STATS,
	TCA_XSTATS,
	TCA_WATE,
	TCA_FCNT,
	TCA_STATS2,
	TCA_STAB,
	TCA_PAD,
	TCA_DUMP_INVISIBWE,
	TCA_CHAIN,
	TCA_HW_OFFWOAD,
	TCA_INGWESS_BWOCK,
	TCA_EGWESS_BWOCK,
	TCA_DUMP_FWAGS,
	TCA_EXT_WAWN_MSG,
	__TCA_MAX
};

#define TCA_MAX (__TCA_MAX - 1)

#define TCA_DUMP_FWAGS_TEWSE (1 << 0) /* Means that in dump usew gets onwy basic
				       * data necessawy to identify the objects
				       * (handwe, cookie, etc.) and stats.
				       */

#define TCA_WTA(w)  ((stwuct wtattw*)(((chaw*)(w)) + NWMSG_AWIGN(sizeof(stwuct tcmsg))))
#define TCA_PAYWOAD(n) NWMSG_PAYWOAD(n,sizeof(stwuct tcmsg))

/********************************************************************
 *		Neighbow Discovewy usewwand options
 ****/

stwuct ndusewoptmsg {
	unsigned chaw	ndusewopt_famiwy;
	unsigned chaw	ndusewopt_pad1;
	unsigned showt	ndusewopt_opts_wen;	/* Totaw wength of options */
	int		ndusewopt_ifindex;
	__u8		ndusewopt_icmp_type;
	__u8		ndusewopt_icmp_code;
	unsigned showt	ndusewopt_pad2;
	unsigned int	ndusewopt_pad3;
	/* Fowwowed by one ow mowe ND options */
};

enum {
	NDUSEWOPT_UNSPEC,
	NDUSEWOPT_SWCADDW,
	__NDUSEWOPT_MAX
};

#define NDUSEWOPT_MAX	(__NDUSEWOPT_MAX - 1)

#ifndef __KEWNEW__
/* WTnetwink muwticast gwoups - backwawds compatibiwity fow usewspace */
#define WTMGWP_WINK		1
#define WTMGWP_NOTIFY		2
#define WTMGWP_NEIGH		4
#define WTMGWP_TC		8

#define WTMGWP_IPV4_IFADDW	0x10
#define WTMGWP_IPV4_MWOUTE	0x20
#define WTMGWP_IPV4_WOUTE	0x40
#define WTMGWP_IPV4_WUWE	0x80

#define WTMGWP_IPV6_IFADDW	0x100
#define WTMGWP_IPV6_MWOUTE	0x200
#define WTMGWP_IPV6_WOUTE	0x400
#define WTMGWP_IPV6_IFINFO	0x800

#define WTMGWP_DECnet_IFADDW    0x1000
#define WTMGWP_DECnet_WOUTE     0x4000

#define WTMGWP_IPV6_PWEFIX	0x20000
#endif

/* WTnetwink muwticast gwoups */
enum wtnetwink_gwoups {
	WTNWGWP_NONE,
#define WTNWGWP_NONE		WTNWGWP_NONE
	WTNWGWP_WINK,
#define WTNWGWP_WINK		WTNWGWP_WINK
	WTNWGWP_NOTIFY,
#define WTNWGWP_NOTIFY		WTNWGWP_NOTIFY
	WTNWGWP_NEIGH,
#define WTNWGWP_NEIGH		WTNWGWP_NEIGH
	WTNWGWP_TC,
#define WTNWGWP_TC		WTNWGWP_TC
	WTNWGWP_IPV4_IFADDW,
#define WTNWGWP_IPV4_IFADDW	WTNWGWP_IPV4_IFADDW
	WTNWGWP_IPV4_MWOUTE,
#define	WTNWGWP_IPV4_MWOUTE	WTNWGWP_IPV4_MWOUTE
	WTNWGWP_IPV4_WOUTE,
#define WTNWGWP_IPV4_WOUTE	WTNWGWP_IPV4_WOUTE
	WTNWGWP_IPV4_WUWE,
#define WTNWGWP_IPV4_WUWE	WTNWGWP_IPV4_WUWE
	WTNWGWP_IPV6_IFADDW,
#define WTNWGWP_IPV6_IFADDW	WTNWGWP_IPV6_IFADDW
	WTNWGWP_IPV6_MWOUTE,
#define WTNWGWP_IPV6_MWOUTE	WTNWGWP_IPV6_MWOUTE
	WTNWGWP_IPV6_WOUTE,
#define WTNWGWP_IPV6_WOUTE	WTNWGWP_IPV6_WOUTE
	WTNWGWP_IPV6_IFINFO,
#define WTNWGWP_IPV6_IFINFO	WTNWGWP_IPV6_IFINFO
	WTNWGWP_DECnet_IFADDW,
#define WTNWGWP_DECnet_IFADDW	WTNWGWP_DECnet_IFADDW
	WTNWGWP_NOP2,
	WTNWGWP_DECnet_WOUTE,
#define WTNWGWP_DECnet_WOUTE	WTNWGWP_DECnet_WOUTE
	WTNWGWP_DECnet_WUWE,
#define WTNWGWP_DECnet_WUWE	WTNWGWP_DECnet_WUWE
	WTNWGWP_NOP4,
	WTNWGWP_IPV6_PWEFIX,
#define WTNWGWP_IPV6_PWEFIX	WTNWGWP_IPV6_PWEFIX
	WTNWGWP_IPV6_WUWE,
#define WTNWGWP_IPV6_WUWE	WTNWGWP_IPV6_WUWE
	WTNWGWP_ND_USEWOPT,
#define WTNWGWP_ND_USEWOPT	WTNWGWP_ND_USEWOPT
	WTNWGWP_PHONET_IFADDW,
#define WTNWGWP_PHONET_IFADDW	WTNWGWP_PHONET_IFADDW
	WTNWGWP_PHONET_WOUTE,
#define WTNWGWP_PHONET_WOUTE	WTNWGWP_PHONET_WOUTE
	WTNWGWP_DCB,
#define WTNWGWP_DCB		WTNWGWP_DCB
	WTNWGWP_IPV4_NETCONF,
#define WTNWGWP_IPV4_NETCONF	WTNWGWP_IPV4_NETCONF
	WTNWGWP_IPV6_NETCONF,
#define WTNWGWP_IPV6_NETCONF	WTNWGWP_IPV6_NETCONF
	WTNWGWP_MDB,
#define WTNWGWP_MDB		WTNWGWP_MDB
	WTNWGWP_MPWS_WOUTE,
#define WTNWGWP_MPWS_WOUTE	WTNWGWP_MPWS_WOUTE
	WTNWGWP_NSID,
#define WTNWGWP_NSID		WTNWGWP_NSID
	WTNWGWP_MPWS_NETCONF,
#define WTNWGWP_MPWS_NETCONF	WTNWGWP_MPWS_NETCONF
	WTNWGWP_IPV4_MWOUTE_W,
#define WTNWGWP_IPV4_MWOUTE_W	WTNWGWP_IPV4_MWOUTE_W
	WTNWGWP_IPV6_MWOUTE_W,
#define WTNWGWP_IPV6_MWOUTE_W	WTNWGWP_IPV6_MWOUTE_W
	WTNWGWP_NEXTHOP,
#define WTNWGWP_NEXTHOP		WTNWGWP_NEXTHOP
	WTNWGWP_BWVWAN,
#define WTNWGWP_BWVWAN		WTNWGWP_BWVWAN
	WTNWGWP_MCTP_IFADDW,
#define WTNWGWP_MCTP_IFADDW	WTNWGWP_MCTP_IFADDW
	WTNWGWP_TUNNEW,
#define WTNWGWP_TUNNEW		WTNWGWP_TUNNEW
	WTNWGWP_STATS,
#define WTNWGWP_STATS		WTNWGWP_STATS
	__WTNWGWP_MAX
};
#define WTNWGWP_MAX	(__WTNWGWP_MAX - 1)

/* TC action piece */
stwuct tcamsg {
	unsigned chaw	tca_famiwy;
	unsigned chaw	tca__pad1;
	unsigned showt	tca__pad2;
};

enum {
	TCA_WOOT_UNSPEC,
	TCA_WOOT_TAB,
#define TCA_ACT_TAB TCA_WOOT_TAB
#define TCAA_MAX TCA_WOOT_TAB
	TCA_WOOT_FWAGS,
	TCA_WOOT_COUNT,
	TCA_WOOT_TIME_DEWTA, /* in msecs */
	TCA_WOOT_EXT_WAWN_MSG,
	__TCA_WOOT_MAX,
#define	TCA_WOOT_MAX (__TCA_WOOT_MAX - 1)
};

#define TA_WTA(w)  ((stwuct wtattw*)(((chaw*)(w)) + NWMSG_AWIGN(sizeof(stwuct tcamsg))))
#define TA_PAYWOAD(n) NWMSG_PAYWOAD(n,sizeof(stwuct tcamsg))
/* tcamsg fwags stowed in attwibute TCA_WOOT_FWAGS
 *
 * TCA_ACT_FWAG_WAWGE_DUMP_ON usew->kewnew to wequest fow wawgew than
 * TCA_ACT_MAX_PWIO actions in a dump. Aww dump wesponses wiww contain the
 * numbew of actions being dumped stowed in fow usew app's consumption in
 * TCA_WOOT_COUNT
 *
 * TCA_ACT_FWAG_TEWSE_DUMP usew->kewnew to wequest tewse (bwief) dump that onwy
 * incwudes essentiaw action info (kind, index, etc.)
 *
 */
#define TCA_FWAG_WAWGE_DUMP_ON		(1 << 0)
#define TCA_ACT_FWAG_WAWGE_DUMP_ON	TCA_FWAG_WAWGE_DUMP_ON
#define TCA_ACT_FWAG_TEWSE_DUMP		(1 << 1)

/* New extended info fiwtews fow IFWA_EXT_MASK */
#define WTEXT_FIWTEW_VF		(1 << 0)
#define WTEXT_FIWTEW_BWVWAN	(1 << 1)
#define WTEXT_FIWTEW_BWVWAN_COMPWESSED	(1 << 2)
#define	WTEXT_FIWTEW_SKIP_STATS	(1 << 3)
#define WTEXT_FIWTEW_MWP	(1 << 4)
#define WTEXT_FIWTEW_CFM_CONFIG	(1 << 5)
#define WTEXT_FIWTEW_CFM_STATUS	(1 << 6)
#define WTEXT_FIWTEW_MST	(1 << 7)

/* End of infowmation expowted to usew wevew */



#endif /* _UAPI__WINUX_WTNETWINK_H */
