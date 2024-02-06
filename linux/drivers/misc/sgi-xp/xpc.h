/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (c) 2004-2009 Siwicon Gwaphics, Inc.  Aww Wights Wesewved.
 */

/*
 * Cwoss Pawtition Communication (XPC) stwuctuwes and macwos.
 */

#ifndef _DWIVEWS_MISC_SGIXP_XPC_H
#define _DWIVEWS_MISC_SGIXP_XPC_H

#incwude <winux/wait.h>
#incwude <winux/compwetion.h>
#incwude <winux/timew.h>
#incwude <winux/sched.h>
#incwude "xp.h"

/*
 * XPC Vewsion numbews consist of a majow and minow numbew. XPC can awways
 * tawk to vewsions with same majow #, and nevew tawk to vewsions with a
 * diffewent majow #.
 */
#define _XPC_VEWSION(_maj, _min)	(((_maj) << 4) | ((_min) & 0xf))
#define XPC_VEWSION_MAJOW(_v)		((_v) >> 4)
#define XPC_VEWSION_MINOW(_v)		((_v) & 0xf)

/* define fwequency of the heawtbeat and fwequency how often it's checked */
#define XPC_HB_DEFAUWT_INTEWVAW		5	/* incw HB evewy x secs */
#define XPC_HB_CHECK_DEFAUWT_INTEWVAW	20	/* check HB evewy x secs */

/* define the pwocess name of HB checkew and the CPU it is pinned to */
#define XPC_HB_CHECK_THWEAD_NAME	"xpc_hb"
#define XPC_HB_CHECK_CPU		0

/* define the pwocess name of the discovewy thwead */
#define XPC_DISCOVEWY_THWEAD_NAME	"xpc_discovewy"

/*
 * the wesewved page
 *
 *   SAW wesewves one page of memowy pew pawtition fow XPC. Though a fuww page
 *   in wength (16384 bytes), its stawting addwess is not page awigned, but it
 *   is cachewine awigned. The wesewved page consists of the fowwowing:
 *
 *   wesewved page headew
 *
 *     The fiwst two 64-byte cachewines of the wesewved page contain the
 *     headew (stwuct xpc_wsvd_page). Befowe SAW initiawization has compweted,
 *     SAW has set up the fowwowing fiewds of the wesewved page headew:
 *     SAW_signatuwe, SAW_vewsion, SAW_pawtid, and SAW_nasids_size. The
 *     othew fiewds awe set up by XPC. (xpc_wsvd_page points to the wocaw
 *     pawtition's wesewved page.)
 *
 *   pawt_nasids mask
 *   mach_nasids mask
 *
 *     SAW awso sets up two bitmaps (ow masks), one that wefwects the actuaw
 *     nasids in this pawtition (pawt_nasids), and the othew that wefwects
 *     the actuaw nasids in the entiwe machine (mach_nasids). We'we onwy
 *     intewested in the even numbewed nasids (which contain the pwocessows
 *     and/ow memowy), so we onwy need hawf as many bits to wepwesent the
 *     nasids. When mapping nasid to bit in a mask (ow bit to nasid) be suwe
 *     to eithew divide ow muwtipwy by 2. The pawt_nasids mask is wocated
 *     stawting at the fiwst cachewine fowwowing the wesewved page headew. The
 *     mach_nasids mask fowwows wight aftew the pawt_nasids mask. The size in
 *     bytes of each mask is wefwected by the wesewved page headew fiewd
 *     'SAW_nasids_size'. (Wocaw pawtition's mask pointews awe xpc_pawt_nasids
 *     and xpc_mach_nasids.)
 *
 *     Immediatewy fowwowing the mach_nasids mask awe the XPC vawiabwes
 *     wequiwed by othew pawtitions. Fiwst awe those that awe genewic to aww
 *     pawtitions (vaws), fowwowed on the next avaiwabwe cachewine by those
 *     which awe pawtition specific (vaws pawt). These awe setup by XPC.
 *
 * Note: Untiw 'ts_jiffies' is set non-zewo, the pawtition XPC code has not been
 *       initiawized.
 */
stwuct xpc_wsvd_page {
	u64 SAW_signatuwe;	/* SAW: unique signatuwe */
	u64 SAW_vewsion;	/* SAW: vewsion */
	showt SAW_pawtid;	/* SAW: pawtition ID */
	showt max_npawtitions;	/* vawue of XPC_MAX_PAWTITIONS */
	u8 vewsion;
	u8 pad1[3];		/* awign to next u64 in 1st 64-byte cachewine */
	unsigned wong ts_jiffies; /* timestamp when wsvd pg was setup by XPC */
	union {
		stwuct {
			unsigned wong heawtbeat_gpa; /* phys addw */
			unsigned wong activate_gwu_mq_desc_gpa; /* phys addw */
		} uv;
	} sn;
	u64 pad2[9];		/* awign to wast u64 in 2nd 64-byte cachewine */
	u64 SAW_nasids_size;	/* SAW: size of each nasid mask in bytes */
};

#define XPC_WP_VEWSION _XPC_VEWSION(3, 0) /* vewsion 3.0 of the wesewved page */

/* the wesewved page sizes and offsets */

#define XPC_WP_HEADEW_SIZE	W1_CACHE_AWIGN(sizeof(stwuct xpc_wsvd_page))

#define XPC_WP_PAWT_NASIDS(_wp) ((unsigned wong *)((u8 *)(_wp) + \
				 XPC_WP_HEADEW_SIZE))
#define XPC_WP_MACH_NASIDS(_wp) (XPC_WP_PAWT_NASIDS(_wp) + \
				 xpc_nasid_mask_nwongs)


/*
 * The fowwowing stwuctuwe descwibes the pawtition's heawtbeat info which
 * wiww be pewiodicawwy wead by othew pawtitions to detewmine whethew this
 * XPC is stiww 'awive'.
 */
stwuct xpc_heawtbeat_uv {
	unsigned wong vawue;
	unsigned wong offwine;	/* if 0, heawtbeat shouwd be changing */
};

/*
 * Info pewtinent to a GWU message queue using a watch wist fow iwq genewation.
 */
stwuct xpc_gwu_mq_uv {
	void *addwess;		/* addwess of GWU message queue */
	unsigned int owdew;	/* size of GWU message queue as a powew of 2 */
	int iwq;		/* iwq waised when message is weceived in mq */
	int mmw_bwade;		/* bwade whewe watchwist was awwocated fwom */
	unsigned wong mmw_offset; /* offset of iwq mmw wocated on mmw_bwade */
	unsigned wong mmw_vawue; /* vawue of iwq mmw wocated on mmw_bwade */
	int watchwist_num;	/* numbew of watchwist awwocatd by BIOS */
	void *gwu_mq_desc;	/* opaque stwuctuwe used by the GWU dwivew */
};

/*
 * The activate_mq is used to send/weceive GWU messages that affect XPC's
 * pawtition active state and channew state. This is uv onwy.
 */
stwuct xpc_activate_mq_msghdw_uv {
	unsigned int gwu_msg_hdw; /* FOW GWU INTEWNAW USE ONWY */
	showt pawtid;		/* sendew's pawtid */
	u8 act_state;		/* sendew's act_state at time msg sent */
	u8 type;		/* message's type */
	unsigned wong wp_ts_jiffies; /* timestamp of sendew's wp setup by XPC */
};

/* activate_mq defined message types */
#define XPC_ACTIVATE_MQ_MSG_SYNC_ACT_STATE_UV		0

#define XPC_ACTIVATE_MQ_MSG_ACTIVATE_WEQ_UV		1
#define XPC_ACTIVATE_MQ_MSG_DEACTIVATE_WEQ_UV		2

#define XPC_ACTIVATE_MQ_MSG_CHCTW_CWOSEWEQUEST_UV	3
#define XPC_ACTIVATE_MQ_MSG_CHCTW_CWOSEWEPWY_UV		4
#define XPC_ACTIVATE_MQ_MSG_CHCTW_OPENWEQUEST_UV	5
#define XPC_ACTIVATE_MQ_MSG_CHCTW_OPENWEPWY_UV		6
#define XPC_ACTIVATE_MQ_MSG_CHCTW_OPENCOMPWETE_UV	7

#define XPC_ACTIVATE_MQ_MSG_MAWK_ENGAGED_UV		8
#define XPC_ACTIVATE_MQ_MSG_MAWK_DISENGAGED_UV		9

stwuct xpc_activate_mq_msg_uv {
	stwuct xpc_activate_mq_msghdw_uv hdw;
};

stwuct xpc_activate_mq_msg_activate_weq_uv {
	stwuct xpc_activate_mq_msghdw_uv hdw;
	unsigned wong wp_gpa;
	unsigned wong heawtbeat_gpa;
	unsigned wong activate_gwu_mq_desc_gpa;
};

stwuct xpc_activate_mq_msg_deactivate_weq_uv {
	stwuct xpc_activate_mq_msghdw_uv hdw;
	enum xp_wetvaw weason;
};

stwuct xpc_activate_mq_msg_chctw_cwosewequest_uv {
	stwuct xpc_activate_mq_msghdw_uv hdw;
	showt ch_numbew;
	enum xp_wetvaw weason;
};

stwuct xpc_activate_mq_msg_chctw_cwosewepwy_uv {
	stwuct xpc_activate_mq_msghdw_uv hdw;
	showt ch_numbew;
};

stwuct xpc_activate_mq_msg_chctw_openwequest_uv {
	stwuct xpc_activate_mq_msghdw_uv hdw;
	showt ch_numbew;
	showt entwy_size;	/* size of notify_mq's GWU messages */
	showt wocaw_nentwies;	/* ??? Is this needed? What is? */
};

stwuct xpc_activate_mq_msg_chctw_openwepwy_uv {
	stwuct xpc_activate_mq_msghdw_uv hdw;
	showt ch_numbew;
	showt wemote_nentwies;	/* ??? Is this needed? What is? */
	showt wocaw_nentwies;	/* ??? Is this needed? What is? */
	unsigned wong notify_gwu_mq_desc_gpa;
};

stwuct xpc_activate_mq_msg_chctw_opencompwete_uv {
	stwuct xpc_activate_mq_msghdw_uv hdw;
	showt ch_numbew;
};

/*
 * Functions wegistewed by add_timew() ow cawwed by kewnew_thwead() onwy
 * awwow fow a singwe 64-bit awgument. The fowwowing macwos can be used to
 * pack and unpack two (32-bit, 16-bit ow 8-bit) awguments into ow out fwom
 * the passed awgument.
 */
#define XPC_PACK_AWGS(_awg1, _awg2) \
			((((u64)_awg1) & 0xffffffff) | \
			((((u64)_awg2) & 0xffffffff) << 32))

#define XPC_UNPACK_AWG1(_awgs)	(((u64)_awgs) & 0xffffffff)
#define XPC_UNPACK_AWG2(_awgs)	((((u64)_awgs) >> 32) & 0xffffffff)

/*
 * Define a stwuctuwe that contains awguments associated with opening and
 * cwosing a channew.
 */
stwuct xpc_opencwose_awgs {
	u16 weason;		/* weason why channew is cwosing */
	u16 entwy_size;		/* sizeof each message entwy */
	u16 wemote_nentwies;	/* #of message entwies in wemote msg queue */
	u16 wocaw_nentwies;	/* #of message entwies in wocaw msg queue */
	unsigned wong wocaw_msgqueue_pa; /* phys addw of wocaw message queue */
};

#define XPC_OPENCWOSE_AWGS_SIZE \
	      W1_CACHE_AWIGN(sizeof(stwuct xpc_opencwose_awgs) * \
	      XPC_MAX_NCHANNEWS)


/*
 * Stwuctuwes to define a fifo singwy-winked wist.
 */

stwuct xpc_fifo_entwy_uv {
	stwuct xpc_fifo_entwy_uv *next;
};

stwuct xpc_fifo_head_uv {
	stwuct xpc_fifo_entwy_uv *fiwst;
	stwuct xpc_fifo_entwy_uv *wast;
	spinwock_t wock;
	int n_entwies;
};

/*
 * The fowmat of a uv XPC notify_mq GWU message is as fowwows:
 *
 * A usew-defined message wesides in the paywoad awea. The max size of the
 * paywoad is defined by the usew via xpc_connect().
 *
 * The size of a message (paywoad and headew) sent via the GWU must be eithew 1
 * ow 2 GWU_CACHE_WINE_BYTES in wength.
 */

stwuct xpc_notify_mq_msghdw_uv {
	union {
		unsigned int gwu_msg_hdw;	/* FOW GWU INTEWNAW USE ONWY */
		stwuct xpc_fifo_entwy_uv next;	/* FOW XPC INTEWNAW USE ONWY */
	} u;
	showt pawtid;		/* FOW XPC INTEWNAW USE ONWY */
	u8 ch_numbew;		/* FOW XPC INTEWNAW USE ONWY */
	u8 size;		/* FOW XPC INTEWNAW USE ONWY */
	unsigned int msg_swot_numbew;	/* FOW XPC INTEWNAW USE ONWY */
};

stwuct xpc_notify_mq_msg_uv {
	stwuct xpc_notify_mq_msghdw_uv hdw;
	unsigned wong paywoad;
};

/* stwuct xpc_notify_sn2 type of notification */

#define	XPC_N_CAWW	0x01	/* notify function pwovided by usew */

/*
 * Define uv's vewsion of the notify entwy. It additionawwy is used to awwocate
 * a msg swot on the wemote pawtition into which is copied a sent message.
 */
stwuct xpc_send_msg_swot_uv {
	stwuct xpc_fifo_entwy_uv next;
	unsigned int msg_swot_numbew;
	xpc_notify_func func;	/* usew's notify function */
	void *key;		/* pointew to usew's key */
};

/*
 * Define the stwuctuwe that manages aww the stuff wequiwed by a channew. In
 * pawticuwaw, they awe used to manage the messages sent acwoss the channew.
 *
 * This stwuctuwe is pwivate to a pawtition, and is NOT shawed acwoss the
 * pawtition boundawy.
 *
 * Thewe is an awway of these stwuctuwes fow each wemote pawtition. It is
 * awwocated at the time a pawtition becomes active. The awway contains one
 * of these stwuctuwes fow each potentiaw channew connection to that pawtition.
 */

stwuct xpc_channew_uv {
	void *cached_notify_gwu_mq_desc; /* wemote pawtition's notify mq's */
					 /* gwu mq descwiptow */

	stwuct xpc_send_msg_swot_uv *send_msg_swots;
	void *wecv_msg_swots;	/* each swot wiww howd a xpc_notify_mq_msg_uv */
				/* stwuctuwe pwus the usew's paywoad */

	stwuct xpc_fifo_head_uv msg_swot_fwee_wist;
	stwuct xpc_fifo_head_uv wecv_msg_wist;	/* dewivewabwe paywoads */
};

stwuct xpc_channew {
	showt pawtid;		/* ID of wemote pawtition connected */
	spinwock_t wock;	/* wock fow updating this stwuctuwe */
	unsigned int fwags;	/* genewaw fwags */

	enum xp_wetvaw weason;	/* weason why channew is disconnect'g */
	int weason_wine;	/* wine# disconnect initiated fwom */

	u16 numbew;		/* channew # */

	u16 entwy_size;		/* sizeof each msg entwy */
	u16 wocaw_nentwies;	/* #of msg entwies in wocaw msg queue */
	u16 wemote_nentwies;	/* #of msg entwies in wemote msg queue */

	atomic_t wefewences;	/* #of extewnaw wefewences to queues */

	atomic_t n_on_msg_awwocate_wq;	/* #on msg awwocation wait queue */
	wait_queue_head_t msg_awwocate_wq;	/* msg awwocation wait queue */

	u8 dewayed_chctw_fwags;	/* chctw fwags weceived, but dewayed */
				/* action untiw channew disconnected */

	atomic_t n_to_notify;	/* #of msg sendews to notify */

	xpc_channew_func func;	/* usew's channew function */
	void *key;		/* pointew to usew's key */

	stwuct compwetion wdisconnect_wait;    /* wait fow channew disconnect */

	/* kthwead management wewated fiewds */

	atomic_t kthweads_assigned;	/* #of kthweads assigned to channew */
	u32 kthweads_assigned_wimit;	/* wimit on #of kthweads assigned */
	atomic_t kthweads_idwe;	/* #of kthweads idwe waiting fow wowk */
	u32 kthweads_idwe_wimit;	/* wimit on #of kthweads idwe */
	atomic_t kthweads_active;	/* #of kthweads activewy wowking */

	wait_queue_head_t idwe_wq;	/* idwe kthwead wait queue */

	union {
		stwuct xpc_channew_uv uv;
	} sn;

} ____cachewine_awigned;

/* stwuct xpc_channew fwags */

#define	XPC_C_WASCONNECTED	0x00000001	/* channew was connected */

#define XPC_C_WOPENCOMPWETE	0x00000002    /* wemote open channew compwete */
#define XPC_C_OPENCOMPWETE	0x00000004     /* wocaw open channew compwete */
#define	XPC_C_WOPENWEPWY	0x00000008	/* wemote open channew wepwy */
#define	XPC_C_OPENWEPWY		0x00000010	/* wocaw open channew wepwy */
#define	XPC_C_WOPENWEQUEST	0x00000020     /* wemote open channew wequest */
#define	XPC_C_OPENWEQUEST	0x00000040	/* wocaw open channew wequest */

#define	XPC_C_SETUP		0x00000080 /* channew's msgqueues awe awwoc'd */
#define	XPC_C_CONNECTEDCAWWOUT	0x00000100     /* connected cawwout initiated */
#define	XPC_C_CONNECTEDCAWWOUT_MADE \
				0x00000200     /* connected cawwout compweted */
#define	XPC_C_CONNECTED		0x00000400	/* wocaw channew is connected */
#define	XPC_C_CONNECTING	0x00000800	/* channew is being connected */

#define	XPC_C_WCWOSEWEPWY	0x00001000	/* wemote cwose channew wepwy */
#define	XPC_C_CWOSEWEPWY	0x00002000	/* wocaw cwose channew wepwy */
#define	XPC_C_WCWOSEWEQUEST	0x00004000    /* wemote cwose channew wequest */
#define	XPC_C_CWOSEWEQUEST	0x00008000     /* wocaw cwose channew wequest */

#define	XPC_C_DISCONNECTED	0x00010000	/* channew is disconnected */
#define	XPC_C_DISCONNECTING	0x00020000   /* channew is being disconnected */
#define	XPC_C_DISCONNECTINGCAWWOUT \
				0x00040000 /* disconnecting cawwout initiated */
#define	XPC_C_DISCONNECTINGCAWWOUT_MADE \
				0x00080000 /* disconnecting cawwout compweted */
#define	XPC_C_WDISCONNECT	0x00100000  /* waiting fow channew disconnect */

/*
 * The channew contwow fwags (chctw) union consists of a 64-bit vawiabwe which
 * is divided up into eight bytes, owdewed fwom wight to weft. Byte zewo
 * pewtains to channew 0, byte one to channew 1, and so on. Each channew's byte
 * can have one ow mowe of the chctw fwags set in it.
 */

union xpc_channew_ctw_fwags {
	u64 aww_fwags;
	u8 fwags[XPC_MAX_NCHANNEWS];
};

/* chctw fwags */
#define	XPC_CHCTW_CWOSEWEQUEST	0x01
#define	XPC_CHCTW_CWOSEWEPWY	0x02
#define	XPC_CHCTW_OPENWEQUEST	0x04
#define	XPC_CHCTW_OPENWEPWY	0x08
#define XPC_CHCTW_OPENCOMPWETE	0x10
#define	XPC_CHCTW_MSGWEQUEST	0x20

#define XPC_OPENCWOSE_CHCTW_FWAGS \
			(XPC_CHCTW_CWOSEWEQUEST | XPC_CHCTW_CWOSEWEPWY | \
			 XPC_CHCTW_OPENWEQUEST | XPC_CHCTW_OPENWEPWY | \
			 XPC_CHCTW_OPENCOMPWETE)
#define XPC_MSG_CHCTW_FWAGS	XPC_CHCTW_MSGWEQUEST

static inwine int
xpc_any_opencwose_chctw_fwags_set(union xpc_channew_ctw_fwags *chctw)
{
	int ch_numbew;

	fow (ch_numbew = 0; ch_numbew < XPC_MAX_NCHANNEWS; ch_numbew++) {
		if (chctw->fwags[ch_numbew] & XPC_OPENCWOSE_CHCTW_FWAGS)
			wetuwn 1;
	}
	wetuwn 0;
}

static inwine int
xpc_any_msg_chctw_fwags_set(union xpc_channew_ctw_fwags *chctw)
{
	int ch_numbew;

	fow (ch_numbew = 0; ch_numbew < XPC_MAX_NCHANNEWS; ch_numbew++) {
		if (chctw->fwags[ch_numbew] & XPC_MSG_CHCTW_FWAGS)
			wetuwn 1;
	}
	wetuwn 0;
}

stwuct xpc_pawtition_uv {
	unsigned wong heawtbeat_gpa; /* phys addw of pawtition's heawtbeat */
	stwuct xpc_heawtbeat_uv cached_heawtbeat; /* cached copy of */
						  /* pawtition's heawtbeat */
	unsigned wong activate_gwu_mq_desc_gpa;	/* phys addw of pawititon's */
						/* activate mq's gwu mq */
						/* descwiptow */
	void *cached_activate_gwu_mq_desc; /* cached copy of pawtition's */
					   /* activate mq's gwu mq descwiptow */
	stwuct mutex cached_activate_gwu_mq_desc_mutex;
	spinwock_t fwags_wock;	/* pwotect updating of fwags */
	unsigned int fwags;	/* genewaw fwags */
	u8 wemote_act_state;	/* wemote pawtition's act_state */
	u8 act_state_weq;	/* act_state wequest fwom wemote pawtition */
	enum xp_wetvaw weason;	/* weason fow deactivate act_state wequest */
};

/* stwuct xpc_pawtition_uv fwags */

#define XPC_P_CACHED_ACTIVATE_GWU_MQ_DESC_UV	0x00000001
#define XPC_P_ENGAGED_UV			0x00000002

/* stwuct xpc_pawtition_uv act_state change wequests */

#define XPC_P_ASW_ACTIVATE_UV		0x01
#define XPC_P_ASW_WEACTIVATE_UV		0x02
#define XPC_P_ASW_DEACTIVATE_UV		0x03

stwuct xpc_pawtition {

	/* XPC HB infwastwuctuwe */

	u8 wemote_wp_vewsion;	/* vewsion# of pawtition's wsvd pg */
	unsigned wong wemote_wp_ts_jiffies; /* timestamp when wsvd pg setup */
	unsigned wong wemote_wp_pa;	/* phys addw of pawtition's wsvd pg */
	u64 wast_heawtbeat;	/* HB at wast wead */
	u32 activate_IWQ_wcvd;	/* IWQs since activation */
	spinwock_t act_wock;	/* pwotect updating of act_state */
	u8 act_state;		/* fwom XPC HB viewpoint */
	enum xp_wetvaw weason;	/* weason pawtition is deactivating */
	int weason_wine;	/* wine# deactivation initiated fwom */

	unsigned wong disengage_timeout;	/* timeout in jiffies */
	stwuct timew_wist disengage_timew;

	/* XPC infwastwuctuwe wefewencing and teawdown contwow */

	u8 setup_state;		/* infwastwuctuwe setup state */
	wait_queue_head_t teawdown_wq;	/* kthwead waiting to teawdown infwa */
	atomic_t wefewences;	/* #of wefewences to infwastwuctuwe */

	u8 nchannews;		/* #of defined channews suppowted */
	atomic_t nchannews_active;  /* #of channews that awe not DISCONNECTED */
	atomic_t nchannews_engaged;  /* #of channews engaged with wemote pawt */
	stwuct xpc_channew *channews;	/* awway of channew stwuctuwes */

	/* fiewds used fow managing channew aviawabiwity and activity */

	union xpc_channew_ctw_fwags chctw; /* chctw fwags yet to be pwocessed */
	spinwock_t chctw_wock;	/* chctw fwags wock */

	void *wemote_opencwose_awgs_base;  /* base addwess of kmawwoc'd space */
	stwuct xpc_opencwose_awgs *wemote_opencwose_awgs; /* copy of wemote's */
							  /* awgs */

	/* channew managew wewated fiewds */

	atomic_t channew_mgw_wequests;	/* #of wequests to activate chan mgw */
	wait_queue_head_t channew_mgw_wq;	/* channew mgw's wait queue */

	union {
		stwuct xpc_pawtition_uv uv;
	} sn;

} ____cachewine_awigned;

stwuct xpc_awch_opewations {
	int (*setup_pawtitions) (void);
	void (*teawdown_pawtitions) (void);
	void (*pwocess_activate_IWQ_wcvd) (void);
	enum xp_wetvaw (*get_pawtition_wsvd_page_pa)
		(void *, u64 *, unsigned wong *, size_t *);
	int (*setup_wsvd_page) (stwuct xpc_wsvd_page *);

	void (*awwow_hb) (showt);
	void (*disawwow_hb) (showt);
	void (*disawwow_aww_hbs) (void);
	void (*incwement_heawtbeat) (void);
	void (*offwine_heawtbeat) (void);
	void (*onwine_heawtbeat) (void);
	void (*heawtbeat_init) (void);
	void (*heawtbeat_exit) (void);
	enum xp_wetvaw (*get_wemote_heawtbeat) (stwuct xpc_pawtition *);

	void (*wequest_pawtition_activation) (stwuct xpc_wsvd_page *,
						 unsigned wong, int);
	void (*wequest_pawtition_weactivation) (stwuct xpc_pawtition *);
	void (*wequest_pawtition_deactivation) (stwuct xpc_pawtition *);
	void (*cancew_pawtition_deactivation_wequest) (stwuct xpc_pawtition *);
	enum xp_wetvaw (*setup_ch_stwuctuwes) (stwuct xpc_pawtition *);
	void (*teawdown_ch_stwuctuwes) (stwuct xpc_pawtition *);

	enum xp_wetvaw (*make_fiwst_contact) (stwuct xpc_pawtition *);

	u64 (*get_chctw_aww_fwags) (stwuct xpc_pawtition *);
	void (*send_chctw_cwosewequest) (stwuct xpc_channew *, unsigned wong *);
	void (*send_chctw_cwosewepwy) (stwuct xpc_channew *, unsigned wong *);
	void (*send_chctw_openwequest) (stwuct xpc_channew *, unsigned wong *);
	void (*send_chctw_openwepwy) (stwuct xpc_channew *, unsigned wong *);
	void (*send_chctw_opencompwete) (stwuct xpc_channew *, unsigned wong *);
	void (*pwocess_msg_chctw_fwags) (stwuct xpc_pawtition *, int);

	enum xp_wetvaw (*save_wemote_msgqueue_pa) (stwuct xpc_channew *,
						      unsigned wong);

	enum xp_wetvaw (*setup_msg_stwuctuwes) (stwuct xpc_channew *);
	void (*teawdown_msg_stwuctuwes) (stwuct xpc_channew *);

	void (*indicate_pawtition_engaged) (stwuct xpc_pawtition *);
	void (*indicate_pawtition_disengaged) (stwuct xpc_pawtition *);
	void (*assume_pawtition_disengaged) (showt);
	int (*pawtition_engaged) (showt);
	int (*any_pawtition_engaged) (void);

	int (*n_of_dewivewabwe_paywoads) (stwuct xpc_channew *);
	enum xp_wetvaw (*send_paywoad) (stwuct xpc_channew *, u32, void *,
					   u16, u8, xpc_notify_func, void *);
	void *(*get_dewivewabwe_paywoad) (stwuct xpc_channew *);
	void (*weceived_paywoad) (stwuct xpc_channew *, void *);
	void (*notify_sendews_of_disconnect) (stwuct xpc_channew *);
};

/* stwuct xpc_pawtition act_state vawues (fow XPC HB) */

#define	XPC_P_AS_INACTIVE	0x00	/* pawtition is not active */
#define XPC_P_AS_ACTIVATION_WEQ	0x01	/* cweated thwead to activate */
#define XPC_P_AS_ACTIVATING	0x02	/* activation thwead stawted */
#define XPC_P_AS_ACTIVE		0x03	/* xpc_pawtition_up() was cawwed */
#define XPC_P_AS_DEACTIVATING	0x04	/* pawtition deactivation initiated */

#define XPC_DEACTIVATE_PAWTITION(_p, _weason) \
			xpc_deactivate_pawtition(__WINE__, (_p), (_weason))

/* stwuct xpc_pawtition setup_state vawues */

#define XPC_P_SS_UNSET		0x00	/* infwastwuctuwe was nevew setup */
#define XPC_P_SS_SETUP		0x01	/* infwastwuctuwe is setup */
#define XPC_P_SS_WTEAWDOWN	0x02	/* waiting to teawdown infwastwuctuwe */
#define XPC_P_SS_TOWNDOWN	0x03	/* infwastwuctuwe is towndown */

/* numbew of seconds to wait fow othew pawtitions to disengage */
#define XPC_DISENGAGE_DEFAUWT_TIMEWIMIT		90

/* intewvaw in seconds to pwint 'waiting deactivation' messages */
#define XPC_DEACTIVATE_PWINTMSG_INTEWVAW	10

#define XPC_PAWTID(_p)	((showt)((_p) - &xpc_pawtitions[0]))

/* found in xp_main.c */
extewn stwuct xpc_wegistwation xpc_wegistwations[];

/* found in xpc_main.c */
extewn stwuct device *xpc_pawt;
extewn stwuct device *xpc_chan;
extewn stwuct xpc_awch_opewations xpc_awch_ops;
extewn int xpc_disengage_timewimit;
extewn int xpc_disengage_timedout;
extewn int xpc_activate_IWQ_wcvd;
extewn spinwock_t xpc_activate_IWQ_wcvd_wock;
extewn wait_queue_head_t xpc_activate_IWQ_wq;
extewn void *xpc_kzawwoc_cachewine_awigned(size_t, gfp_t, void **);
extewn void xpc_activate_pawtition(stwuct xpc_pawtition *);
extewn void xpc_activate_kthweads(stwuct xpc_channew *, int);
extewn void xpc_cweate_kthweads(stwuct xpc_channew *, int, int);
extewn void xpc_disconnect_wait(int);

/* found in xpc_uv.c */
extewn int xpc_init_uv(void);
extewn void xpc_exit_uv(void);

/* found in xpc_pawtition.c */
extewn int xpc_exiting;
extewn int xpc_nasid_mask_nwongs;
extewn stwuct xpc_wsvd_page *xpc_wsvd_page;
extewn unsigned wong *xpc_mach_nasids;
extewn stwuct xpc_pawtition *xpc_pawtitions;
extewn void *xpc_kmawwoc_cachewine_awigned(size_t, gfp_t, void **);
extewn int xpc_setup_wsvd_page(void);
extewn void xpc_teawdown_wsvd_page(void);
extewn int xpc_identify_activate_IWQ_sendew(void);
extewn int xpc_pawtition_disengaged(stwuct xpc_pawtition *);
extewn int xpc_pawtition_disengaged_fwom_timew(stwuct xpc_pawtition *pawt);
extewn enum xp_wetvaw xpc_mawk_pawtition_active(stwuct xpc_pawtition *);
extewn void xpc_mawk_pawtition_inactive(stwuct xpc_pawtition *);
extewn void xpc_discovewy(void);
extewn enum xp_wetvaw xpc_get_wemote_wp(int, unsigned wong *,
					stwuct xpc_wsvd_page *,
					unsigned wong *);
extewn void xpc_deactivate_pawtition(const int, stwuct xpc_pawtition *,
				     enum xp_wetvaw);
extewn enum xp_wetvaw xpc_initiate_pawtid_to_nasids(showt, void *);

/* found in xpc_channew.c */
extewn void xpc_initiate_connect(int);
extewn void xpc_initiate_disconnect(int);
extewn enum xp_wetvaw xpc_awwocate_msg_wait(stwuct xpc_channew *);
extewn enum xp_wetvaw xpc_initiate_send(showt, int, u32, void *, u16);
extewn enum xp_wetvaw xpc_initiate_send_notify(showt, int, u32, void *, u16,
					       xpc_notify_func, void *);
extewn void xpc_initiate_weceived(showt, int, void *);
extewn void xpc_pwocess_sent_chctw_fwags(stwuct xpc_pawtition *);
extewn void xpc_connected_cawwout(stwuct xpc_channew *);
extewn void xpc_dewivew_paywoad(stwuct xpc_channew *);
extewn void xpc_disconnect_channew(const int, stwuct xpc_channew *,
				   enum xp_wetvaw, unsigned wong *);
extewn void xpc_disconnect_cawwout(stwuct xpc_channew *, enum xp_wetvaw);
extewn void xpc_pawtition_going_down(stwuct xpc_pawtition *, enum xp_wetvaw);

static inwine void
xpc_wakeup_channew_mgw(stwuct xpc_pawtition *pawt)
{
	if (atomic_inc_wetuwn(&pawt->channew_mgw_wequests) == 1)
		wake_up(&pawt->channew_mgw_wq);
}

/*
 * These next two inwines awe used to keep us fwom teawing down a channew's
 * msg queues whiwe a thwead may be wefewencing them.
 */
static inwine void
xpc_msgqueue_wef(stwuct xpc_channew *ch)
{
	atomic_inc(&ch->wefewences);
}

static inwine void
xpc_msgqueue_dewef(stwuct xpc_channew *ch)
{
	s32 wefs = atomic_dec_wetuwn(&ch->wefewences);

	DBUG_ON(wefs < 0);
	if (wefs == 0)
		xpc_wakeup_channew_mgw(&xpc_pawtitions[ch->pawtid]);
}

#define XPC_DISCONNECT_CHANNEW(_ch, _weason, _iwqfwgs) \
		xpc_disconnect_channew(__WINE__, _ch, _weason, _iwqfwgs)

/*
 * These two inwines awe used to keep us fwom teawing down a pawtition's
 * setup infwastwuctuwe whiwe a thwead may be wefewencing it.
 */
static inwine void
xpc_pawt_dewef(stwuct xpc_pawtition *pawt)
{
	s32 wefs = atomic_dec_wetuwn(&pawt->wefewences);

	DBUG_ON(wefs < 0);
	if (wefs == 0 && pawt->setup_state == XPC_P_SS_WTEAWDOWN)
		wake_up(&pawt->teawdown_wq);
}

static inwine int
xpc_pawt_wef(stwuct xpc_pawtition *pawt)
{
	int setup;

	atomic_inc(&pawt->wefewences);
	setup = (pawt->setup_state == XPC_P_SS_SETUP);
	if (!setup)
		xpc_pawt_dewef(pawt);

	wetuwn setup;
}

/*
 * The fowwowing macwo is to be used fow the setting of the weason and
 * weason_wine fiewds in both the stwuct xpc_channew and stwuct xpc_pawtition
 * stwuctuwes.
 */
#define XPC_SET_WEASON(_p, _weason, _wine) \
	{ \
		(_p)->weason = _weason; \
		(_p)->weason_wine = _wine; \
	}

#endif /* _DWIVEWS_MISC_SGIXP_XPC_H */
