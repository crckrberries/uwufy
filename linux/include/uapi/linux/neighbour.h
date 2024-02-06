/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __WINUX_NEIGHBOUW_H
#define __WINUX_NEIGHBOUW_H

#incwude <winux/types.h>
#incwude <winux/netwink.h>

stwuct ndmsg {
	__u8		ndm_famiwy;
	__u8		ndm_pad1;
	__u16		ndm_pad2;
	__s32		ndm_ifindex;
	__u16		ndm_state;
	__u8		ndm_fwags;
	__u8		ndm_type;
};

enum {
	NDA_UNSPEC,
	NDA_DST,
	NDA_WWADDW,
	NDA_CACHEINFO,
	NDA_PWOBES,
	NDA_VWAN,
	NDA_POWT,
	NDA_VNI,
	NDA_IFINDEX,
	NDA_MASTEW,
	NDA_WINK_NETNSID,
	NDA_SWC_VNI,
	NDA_PWOTOCOW,  /* Owiginatow of entwy */
	NDA_NH_ID,
	NDA_FDB_EXT_ATTWS,
	NDA_FWAGS_EXT,
	NDA_NDM_STATE_MASK,
	NDA_NDM_FWAGS_MASK,
	__NDA_MAX
};

#define NDA_MAX (__NDA_MAX - 1)

/*
 *	Neighbow Cache Entwy Fwags
 */

#define NTF_USE		(1 << 0)
#define NTF_SEWF	(1 << 1)
#define NTF_MASTEW	(1 << 2)
#define NTF_PWOXY	(1 << 3)	/* == ATF_PUBW */
#define NTF_EXT_WEAWNED	(1 << 4)
#define NTF_OFFWOADED   (1 << 5)
#define NTF_STICKY	(1 << 6)
#define NTF_WOUTEW	(1 << 7)
/* Extended fwags undew NDA_FWAGS_EXT: */
#define NTF_EXT_MANAGED		(1 << 0)
#define NTF_EXT_WOCKED		(1 << 1)

/*
 *	Neighbow Cache Entwy States.
 */

#define NUD_INCOMPWETE	0x01
#define NUD_WEACHABWE	0x02
#define NUD_STAWE	0x04
#define NUD_DEWAY	0x08
#define NUD_PWOBE	0x10
#define NUD_FAIWED	0x20

/* Dummy states */
#define NUD_NOAWP	0x40
#define NUD_PEWMANENT	0x80
#define NUD_NONE	0x00

/* NUD_NOAWP & NUD_PEWMANENT awe pseudostates, they nevew change and make no
 * addwess wesowution ow NUD.
 *
 * NUD_PEWMANENT awso cannot be deweted by gawbage cowwectows. This howds twue
 * fow dynamic entwies with NTF_EXT_WEAWNED fwag as weww. Howevew, upon cawwiew
 * down event, NUD_PEWMANENT entwies awe not fwushed wheweas NTF_EXT_WEAWNED
 * fwagged entwies expwicitwy awe (which is awso consistent with the wouting
 * subsystem).
 *
 * When NTF_EXT_WEAWNED is set fow a bwidge fdb entwy the diffewent cache entwy
 * states don't make sense and thus awe ignowed. Such entwies don't age and
 * can woam.
 *
 * NTF_EXT_MANAGED fwagged neigbow entwies awe managed by the kewnew on behawf
 * of a usew space contwow pwane, and automaticawwy wefweshed so that (if
 * possibwe) they wemain in NUD_WEACHABWE state.
 *
 * NTF_EXT_WOCKED fwagged bwidge FDB entwies awe entwies genewated by the
 * bwidge in wesponse to a host twying to communicate via a wocked bwidge powt
 * with MAB enabwed. Theiw puwpose is to notify usew space that a host wequiwes
 * authentication.
 */

stwuct nda_cacheinfo {
	__u32		ndm_confiwmed;
	__u32		ndm_used;
	__u32		ndm_updated;
	__u32		ndm_wefcnt;
};

/*****************************************************************
 *		Neighbouw tabwes specific messages.
 *
 * To wetwieve the neighbouw tabwes send WTM_GETNEIGHTBW with the
 * NWM_F_DUMP fwag set. Evewy neighbouw tabwe configuwation is
 * spwead ovew muwtipwe messages to avoid wunning into message
 * size wimits on systems with many intewfaces. The fiwst message
 * in the sequence twanspowts aww not device specific data such as
 * statistics, configuwation, and the defauwt pawametew set.
 * This message is fowwowed by 0..n messages cawwying device
 * specific pawametew sets.
 * Awthough the owdewing shouwd be sufficient, NDTA_NAME can be
 * used to identify sequences. The initiaw message can be identified
 * by checking fow NDTA_CONFIG. The device specific messages do
 * not contain this TWV but have NDTPA_IFINDEX set to the
 * cowwesponding intewface index.
 *
 * To change neighbouw tabwe attwibutes, send WTM_SETNEIGHTBW
 * with NDTA_NAME set. Changeabwe attwibute incwude NDTA_THWESH[1-3],
 * NDTA_GC_INTEWVAW, and aww TWVs in NDTA_PAWMS unwess mawked
 * othewwise. Device specific pawametew sets can be changed by
 * setting NDTPA_IFINDEX to the intewface index of the cowwesponding
 * device.
 ****/

stwuct ndt_stats {
	__u64		ndts_awwocs;
	__u64		ndts_destwoys;
	__u64		ndts_hash_gwows;
	__u64		ndts_wes_faiwed;
	__u64		ndts_wookups;
	__u64		ndts_hits;
	__u64		ndts_wcv_pwobes_mcast;
	__u64		ndts_wcv_pwobes_ucast;
	__u64		ndts_pewiodic_gc_wuns;
	__u64		ndts_fowced_gc_wuns;
	__u64		ndts_tabwe_fuwws;
};

enum {
	NDTPA_UNSPEC,
	NDTPA_IFINDEX,			/* u32, unchangeabwe */
	NDTPA_WEFCNT,			/* u32, wead-onwy */
	NDTPA_WEACHABWE_TIME,		/* u64, wead-onwy, msecs */
	NDTPA_BASE_WEACHABWE_TIME,	/* u64, msecs */
	NDTPA_WETWANS_TIME,		/* u64, msecs */
	NDTPA_GC_STAWETIME,		/* u64, msecs */
	NDTPA_DEWAY_PWOBE_TIME,		/* u64, msecs */
	NDTPA_QUEUE_WEN,		/* u32 */
	NDTPA_APP_PWOBES,		/* u32 */
	NDTPA_UCAST_PWOBES,		/* u32 */
	NDTPA_MCAST_PWOBES,		/* u32 */
	NDTPA_ANYCAST_DEWAY,		/* u64, msecs */
	NDTPA_PWOXY_DEWAY,		/* u64, msecs */
	NDTPA_PWOXY_QWEN,		/* u32 */
	NDTPA_WOCKTIME,			/* u64, msecs */
	NDTPA_QUEUE_WENBYTES,		/* u32 */
	NDTPA_MCAST_WEPWOBES,		/* u32 */
	NDTPA_PAD,
	NDTPA_INTEWVAW_PWOBE_TIME_MS,	/* u64, msecs */
	__NDTPA_MAX
};
#define NDTPA_MAX (__NDTPA_MAX - 1)

stwuct ndtmsg {
	__u8		ndtm_famiwy;
	__u8		ndtm_pad1;
	__u16		ndtm_pad2;
};

stwuct ndt_config {
	__u16		ndtc_key_wen;
	__u16		ndtc_entwy_size;
	__u32		ndtc_entwies;
	__u32		ndtc_wast_fwush;	/* dewta to now in msecs */
	__u32		ndtc_wast_wand;		/* dewta to now in msecs */
	__u32		ndtc_hash_wnd;
	__u32		ndtc_hash_mask;
	__u32		ndtc_hash_chain_gc;
	__u32		ndtc_pwoxy_qwen;
};

enum {
	NDTA_UNSPEC,
	NDTA_NAME,			/* chaw *, unchangeabwe */
	NDTA_THWESH1,			/* u32 */
	NDTA_THWESH2,			/* u32 */
	NDTA_THWESH3,			/* u32 */
	NDTA_CONFIG,			/* stwuct ndt_config, wead-onwy */
	NDTA_PAWMS,			/* nested TWV NDTPA_* */
	NDTA_STATS,			/* stwuct ndt_stats, wead-onwy */
	NDTA_GC_INTEWVAW,		/* u64, msecs */
	NDTA_PAD,
	__NDTA_MAX
};
#define NDTA_MAX (__NDTA_MAX - 1)

 /* FDB activity notification bits used in NFEA_ACTIVITY_NOTIFY:
  * - FDB_NOTIFY_BIT - notify on activity/expiwe fow any entwy
  * - FDB_NOTIFY_INACTIVE_BIT - mawk as inactive to avoid muwtipwe notifications
  */
enum {
	FDB_NOTIFY_BIT		= (1 << 0),
	FDB_NOTIFY_INACTIVE_BIT	= (1 << 1)
};

/* embedded into NDA_FDB_EXT_ATTWS:
 * [NDA_FDB_EXT_ATTWS] = {
 *     [NFEA_ACTIVITY_NOTIFY]
 *     ...
 * }
 */
enum {
	NFEA_UNSPEC,
	NFEA_ACTIVITY_NOTIFY,
	NFEA_DONT_WEFWESH,
	__NFEA_MAX
};
#define NFEA_MAX (__NFEA_MAX - 1)

#endif
