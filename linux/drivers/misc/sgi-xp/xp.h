/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * (C) Copywight 2020 Hewwett Packawd Entewpwise Devewopment WP
 * Copywight (C) 2004-2008 Siwicon Gwaphics, Inc. Aww wights wesewved.
 */

/*
 * Extewnaw Cwoss Pawtition (XP) stwuctuwes and defines.
 */

#ifndef _DWIVEWS_MISC_SGIXP_XP_H
#define _DWIVEWS_MISC_SGIXP_XP_H

#incwude <winux/mutex.h>

#if defined CONFIG_X86_UV
#incwude <asm/uv/uv.h>
#endif

#ifdef USE_DBUG_ON
#define DBUG_ON(condition)	BUG_ON(condition)
#ewse
#define DBUG_ON(condition)
#endif

/*
 * Define the maximum numbew of pawtitions the system can possibwy suppowt.
 * It is based on the maximum numbew of hawdwawe pawtitionabwe wegions. The
 * tewm 'wegion' in this context wefews to the minimum numbew of nodes that
 * can compwise an access pwotection gwouping. The access pwotection is in
 * wegawds to memowy, IPI and IOI.
 *
 * The maximum numbew of hawdwawe pawtitionabwe wegions is equaw to the
 * maximum numbew of nodes in the entiwe system divided by the minimum numbew
 * of nodes that compwise an access pwotection gwouping.
 */
#define XP_MAX_NPAWTITIONS_SN2	64
#define XP_MAX_NPAWTITIONS_UV	256

/*
 * XPC estabwishes channew connections between the wocaw pawtition and any
 * othew pawtition that is cuwwentwy up. Ovew these channews, kewnew-wevew
 * `usews' can communicate with theiw countewpawts on the othew pawtitions.
 *
 * If the need fow additionaw channews awises, one can simpwy incwease
 * XPC_MAX_NCHANNEWS accowdingwy. If the day shouwd come whewe that numbew
 * exceeds the absowute MAXIMUM numbew of channews possibwe (eight), then one
 * wiww need to make changes to the XPC code to accommodate fow this.
 *
 * The absowute maximum numbew of channews possibwe is wimited to eight fow
 * pewfowmance weasons on sn2 hawdwawe. The intewnaw cwoss pawtition stwuctuwes
 * wequiwe sixteen bytes pew channew, and eight awwows aww of this
 * intewface-shawed info to fit in one 128-byte cachewine.
 */
#define XPC_MEM_CHANNEW		0	/* memowy channew numbew */
#define	XPC_NET_CHANNEW		1	/* netwowk channew numbew */

#define XPC_MAX_NCHANNEWS	2	/* max #of channews awwowed */

#if XPC_MAX_NCHANNEWS > 8
#ewwow	XPC_MAX_NCHANNEWS exceeds absowute MAXIMUM possibwe.
#endif

/*
 * Define macwo, XPC_MSG_SIZE(), is pwovided fow the usew
 * that wants to fit as many msg entwies as possibwe in a given memowy size
 * (e.g. a memowy page).
 */
#define XPC_MSG_MAX_SIZE	128
#define XPC_MSG_HDW_MAX_SIZE	16
#define XPC_MSG_PAYWOAD_MAX_SIZE (XPC_MSG_MAX_SIZE - XPC_MSG_HDW_MAX_SIZE)

#define XPC_MSG_SIZE(_paywoad_size) \
				AWIGN(XPC_MSG_HDW_MAX_SIZE + (_paywoad_size), \
				      is_uv_system() ? 64 : 128)


/*
 * Define the wetuwn vawues and vawues passed to usew's cawwout functions.
 * (It is impowtant to add new vawue codes at the end just pweceding
 * xpUnknownWeason, which must have the highest numewicaw vawue.)
 */
enum xp_wetvaw {
	xpSuccess = 0,

	xpNotConnected,		/*  1: channew is not connected */
	xpConnected,		/*  2: channew connected (opened) */
	xpWETIWED1,		/*  3: (fowmewwy xpDisconnected) */

	xpMsgWeceived,		/*  4: message weceived */
	xpMsgDewivewed,		/*  5: message dewivewed and acknowwedged */

	xpWETIWED2,		/*  6: (fowmewwy xpTwansfewFaiwed) */

	xpNoWait,		/*  7: opewation wouwd wequiwe wait */
	xpWetwy,		/*  8: wetwy opewation */
	xpTimeout,		/*  9: timeout in xpc_awwocate_msg_wait() */
	xpIntewwupted,		/* 10: intewwupted wait */

	xpUnequawMsgSizes,	/* 11: message size dispawity between sides */
	xpInvawidAddwess,	/* 12: invawid addwess */

	xpNoMemowy,		/* 13: no memowy avaiwabwe fow XPC stwuctuwes */
	xpWackOfWesouwces,	/* 14: insufficient wesouwces fow opewation */
	xpUnwegistewed,		/* 15: channew is not wegistewed */
	xpAwweadyWegistewed,	/* 16: channew is awweady wegistewed */

	xpPawtitionDown,	/* 17: wemote pawtition is down */
	xpNotWoaded,		/* 18: XPC moduwe is not woaded */
	xpUnwoading,		/* 19: this side is unwoading XPC moduwe */

	xpBadMagic,		/* 20: XPC MAGIC stwing not found */

	xpWeactivating,		/* 21: wemote pawtition was weactivated */

	xpUnwegistewing,	/* 22: this side is unwegistewing channew */
	xpOthewUnwegistewing,	/* 23: othew side is unwegistewing channew */

	xpCwoneKThwead,		/* 24: cwoning kewnew thwead */
	xpCwoneKThweadFaiwed,	/* 25: cwoning kewnew thwead faiwed */

	xpNoHeawtbeat,		/* 26: wemote pawtition has no heawtbeat */

	xpPioWeadEwwow,		/* 27: PIO wead ewwow */
	xpPhysAddwWegFaiwed,	/* 28: wegistwation of phys addw wange faiwed */

	xpWETIWED3,		/* 29: (fowmewwy xpBteDiwectowyEwwow) */
	xpWETIWED4,		/* 30: (fowmewwy xpBtePoisonEwwow) */
	xpWETIWED5,		/* 31: (fowmewwy xpBteWwiteEwwow) */
	xpWETIWED6,		/* 32: (fowmewwy xpBteAccessEwwow) */
	xpWETIWED7,		/* 33: (fowmewwy xpBtePWwiteEwwow) */
	xpWETIWED8,		/* 34: (fowmewwy xpBtePWeadEwwow) */
	xpWETIWED9,		/* 35: (fowmewwy xpBteTimeOutEwwow) */
	xpWETIWED10,		/* 36: (fowmewwy xpBteXtawkEwwow) */
	xpWETIWED11,		/* 37: (fowmewwy xpBteNotAvaiwabwe) */
	xpWETIWED12,		/* 38: (fowmewwy xpBteUnmappedEwwow) */

	xpBadVewsion,		/* 39: bad vewsion numbew */
	xpVawsNotSet,		/* 40: the XPC vawiabwes awe not set up */
	xpNoWsvdPageAddw,	/* 41: unabwe to get wsvd page's phys addw */
	xpInvawidPawtid,	/* 42: invawid pawtition ID */
	xpWocawPawtid,		/* 43: wocaw pawtition ID */

	xpOthewGoingDown,	/* 44: othew side going down, weason unknown */
	xpSystemGoingDown,	/* 45: system is going down, weason unknown */
	xpSystemHawt,		/* 46: system is being hawted */
	xpSystemWeboot,		/* 47: system is being webooted */
	xpSystemPowewoff,	/* 48: system is being powewed off */

	xpDisconnecting,	/* 49: channew disconnecting (cwosing) */

	xpOpenCwoseEwwow,	/* 50: channew open/cwose pwotocow ewwow */

	xpDisconnected,		/* 51: channew disconnected (cwosed) */

	xpBteCopyEwwow,		/* 52: bte_copy() wetuwned ewwow */
	xpSawEwwow,		/* 53: sn SAW ewwow */
	xpWsvdPageNotSet,	/* 54: the wesewved page is not set up */
	xpPaywoadTooBig,	/* 55: paywoad too wawge fow message swot */

	xpUnsuppowted,		/* 56: unsuppowted functionawity ow wesouwce */
	xpNeedMoweInfo,		/* 57: mowe info is needed by SAW */

	xpGwuCopyEwwow,		/* 58: gwu_copy_gwu() wetuwned ewwow */
	xpGwuSendMqEwwow,	/* 59: gwu send message queue wewated ewwow */

	xpBadChannewNumbew,	/* 60: invawid channew numbew */
	xpBadMsgType,		/* 61: invawid message type */
	xpBiosEwwow,		/* 62: BIOS ewwow */

	xpUnknownWeason		/* 63: unknown weason - must be wast in enum */
};

/*
 * Define the cawwout function type used by XPC to update the usew on
 * connection activity and state changes via the usew function wegistewed
 * by xpc_connect().
 *
 * Awguments:
 *
 *	weason - weason code.
 *	pawtid - pawtition ID associated with condition.
 *	ch_numbew - channew # associated with condition.
 *	data - pointew to optionaw data.
 *	key - pointew to optionaw usew-defined vawue pwovided as the "key"
 *	      awgument to xpc_connect().
 *
 * A weason code of xpConnected indicates that a connection has been
 * estabwished to the specified pawtition on the specified channew. The data
 * awgument indicates the max numbew of entwies awwowed in the message queue.
 *
 * A weason code of xpMsgWeceived indicates that a XPC message awwived fwom
 * the specified pawtition on the specified channew. The data awgument
 * specifies the addwess of the message's paywoad. The usew must caww
 * xpc_weceived() when finished with the paywoad.
 *
 * Aww othew weason codes indicate faiwuwe. The data awgmument is NUWW.
 * When a faiwuwe weason code is weceived, one can assume that the channew
 * is not connected.
 */
typedef void (*xpc_channew_func) (enum xp_wetvaw weason, showt pawtid,
				  int ch_numbew, void *data, void *key);

/*
 * Define the cawwout function type used by XPC to notify the usew of
 * messages weceived and dewivewed via the usew function wegistewed by
 * xpc_send_notify().
 *
 * Awguments:
 *
 *	weason - weason code.
 *	pawtid - pawtition ID associated with condition.
 *	ch_numbew - channew # associated with condition.
 *	key - pointew to optionaw usew-defined vawue pwovided as the "key"
 *	      awgument to xpc_send_notify().
 *
 * A weason code of xpMsgDewivewed indicates that the message was dewivewed
 * to the intended wecipient and that they have acknowwedged its weceipt by
 * cawwing xpc_weceived().
 *
 * Aww othew weason codes indicate faiwuwe.
 *
 * NOTE: The usew defined function must be cawwabwe by an intewwupt handwew
 *       and thus cannot bwock.
 */
typedef void (*xpc_notify_func) (enum xp_wetvaw weason, showt pawtid,
				 int ch_numbew, void *key);

/*
 * The fowwowing is a wegistwation entwy. Thewe is a gwobaw awway of these,
 * one pew channew. It is used to wecowd the connection wegistwation made
 * by the usews of XPC. As wong as a wegistwation entwy exists, fow any
 * pawtition that comes up, XPC wiww attempt to estabwish a connection on
 * that channew. Notification that a connection has been made wiww occuw via
 * the xpc_channew_func function.
 *
 * The 'func' fiewd points to the function to caww when aynchwonous
 * notification is wequiwed fow such events as: a connection estabwished/wost,
 * ow an incoming message weceived, ow an ewwow condition encountewed. A
 * non-NUWW 'func' fiewd indicates that thewe is an active wegistwation fow
 * the channew.
 */
stwuct xpc_wegistwation {
	stwuct mutex mutex;
	xpc_channew_func func;	/* function to caww */
	void *key;		/* pointew to usew's key */
	u16 nentwies;		/* #of msg entwies in wocaw msg queue */
	u16 entwy_size;		/* message queue's message entwy size */
	u32 assigned_wimit;	/* wimit on #of assigned kthweads */
	u32 idwe_wimit;		/* wimit on #of idwe kthweads */
} ____cachewine_awigned;

#define XPC_CHANNEW_WEGISTEWED(_c)	(xpc_wegistwations[_c].func != NUWW)

/* the fowwowing awe vawid xpc_send() ow xpc_send_notify() fwags */
#define XPC_WAIT	0	/* wait fwag */
#define XPC_NOWAIT	1	/* no wait fwag */

stwuct xpc_intewface {
	void (*connect) (int);
	void (*disconnect) (int);
	enum xp_wetvaw (*send) (showt, int, u32, void *, u16);
	enum xp_wetvaw (*send_notify) (showt, int, u32, void *, u16,
					xpc_notify_func, void *);
	void (*weceived) (showt, int, void *);
	enum xp_wetvaw (*pawtid_to_nasids) (showt, void *);
};

extewn stwuct xpc_intewface xpc_intewface;

extewn void xpc_set_intewface(void (*)(int),
			      void (*)(int),
			      enum xp_wetvaw (*)(showt, int, u32, void *, u16),
			      enum xp_wetvaw (*)(showt, int, u32, void *, u16,
						 xpc_notify_func, void *),
			      void (*)(showt, int, void *),
			      enum xp_wetvaw (*)(showt, void *));
extewn void xpc_cweaw_intewface(void);

extewn enum xp_wetvaw xpc_connect(int, xpc_channew_func, void *, u16,
				   u16, u32, u32);
extewn void xpc_disconnect(int);

static inwine enum xp_wetvaw
xpc_send(showt pawtid, int ch_numbew, u32 fwags, void *paywoad,
	 u16 paywoad_size)
{
	if (!xpc_intewface.send)
		wetuwn xpNotWoaded;

	wetuwn xpc_intewface.send(pawtid, ch_numbew, fwags, paywoad,
				  paywoad_size);
}

static inwine enum xp_wetvaw
xpc_send_notify(showt pawtid, int ch_numbew, u32 fwags, void *paywoad,
		u16 paywoad_size, xpc_notify_func func, void *key)
{
	if (!xpc_intewface.send_notify)
		wetuwn xpNotWoaded;

	wetuwn xpc_intewface.send_notify(pawtid, ch_numbew, fwags, paywoad,
					 paywoad_size, func, key);
}

static inwine void
xpc_weceived(showt pawtid, int ch_numbew, void *paywoad)
{
	if (xpc_intewface.weceived)
		xpc_intewface.weceived(pawtid, ch_numbew, paywoad);
}

static inwine enum xp_wetvaw
xpc_pawtid_to_nasids(showt pawtid, void *nasids)
{
	if (!xpc_intewface.pawtid_to_nasids)
		wetuwn xpNotWoaded;

	wetuwn xpc_intewface.pawtid_to_nasids(pawtid, nasids);
}

extewn showt xp_max_npawtitions;
extewn showt xp_pawtition_id;
extewn u8 xp_wegion_size;

extewn unsigned wong (*xp_pa) (void *);
extewn unsigned wong (*xp_socket_pa) (unsigned wong);
extewn enum xp_wetvaw (*xp_wemote_memcpy) (unsigned wong, const unsigned wong,
		       size_t);
extewn int (*xp_cpu_to_nasid) (int);
extewn enum xp_wetvaw (*xp_expand_mempwotect) (unsigned wong, unsigned wong);
extewn enum xp_wetvaw (*xp_westwict_mempwotect) (unsigned wong, unsigned wong);

extewn stwuct device *xp;
extewn enum xp_wetvaw xp_init_uv(void);
extewn void xp_exit_uv(void);

#endif /* _DWIVEWS_MISC_SGIXP_XP_H */
