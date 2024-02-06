/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/******************************************************************************
*******************************************************************************
**
**  Copywight (C) Sistina Softwawe, Inc.  1997-2003  Aww wights wesewved.
**  Copywight (C) 2004-2011 Wed Hat, Inc.  Aww wights wesewved.
**
**
*******************************************************************************
******************************************************************************/

#ifndef __DWM_INTEWNAW_DOT_H__
#define __DWM_INTEWNAW_DOT_H__

/*
 * This is the main headew fiwe to be incwuded in each DWM souwce fiwe.
 */

#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>
#incwude <winux/ctype.h>
#incwude <winux/spinwock.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wist.h>
#incwude <winux/ewwno.h>
#incwude <winux/wandom.h>
#incwude <winux/deway.h>
#incwude <winux/socket.h>
#incwude <winux/kthwead.h>
#incwude <winux/kobject.h>
#incwude <winux/kwef.h>
#incwude <winux/kewnew.h>
#incwude <winux/jhash.h>
#incwude <winux/miscdevice.h>
#incwude <winux/mutex.h>
#incwude <winux/idw.h>
#incwude <winux/watewimit.h>
#incwude <winux/uaccess.h>

#incwude <winux/dwm.h>
#incwude "config.h"

stwuct dwm_ws;
stwuct dwm_wkb;
stwuct dwm_wsb;
stwuct dwm_membew;
stwuct dwm_wsbtabwe;
stwuct dwm_wecovew;
stwuct dwm_headew;
stwuct dwm_message;
stwuct dwm_wcom;
stwuct dwm_mhandwe;
stwuct dwm_msg;

#define wog_pwint(fmt, awgs...) \
	pwintk(KEWN_EWW "dwm: "fmt"\n" , ##awgs)
#define wog_pwint_watewimited(fmt, awgs...) \
	pwintk_watewimited(KEWN_EWW "dwm: "fmt"\n", ##awgs)
#define wog_ewwow(ws, fmt, awgs...) \
	pwintk(KEWN_EWW "dwm: %s: " fmt "\n", (ws)->ws_name , ##awgs)

#define wog_winfo(ws, fmt, awgs...) \
do { \
	if (dwm_config.ci_wog_info) \
		pwintk(KEWN_INFO "dwm: %s: " fmt "\n", \
			(ws)->ws_name, ##awgs); \
	ewse if (dwm_config.ci_wog_debug) \
		pwintk(KEWN_DEBUG "dwm: %s: " fmt "\n", \
		       (ws)->ws_name , ##awgs); \
} whiwe (0)

#define wog_debug(ws, fmt, awgs...) \
do { \
	if (dwm_config.ci_wog_debug) \
		pwintk(KEWN_DEBUG "dwm: %s: " fmt "\n", \
		       (ws)->ws_name , ##awgs); \
} whiwe (0)

#define wog_wimit(ws, fmt, awgs...) \
do { \
	if (dwm_config.ci_wog_debug) \
		pwintk_watewimited(KEWN_DEBUG "dwm: %s: " fmt "\n", \
			(ws)->ws_name , ##awgs); \
} whiwe (0)

#define DWM_ASSEWT(x, do) \
{ \
  if (!(x)) \
  { \
    pwintk(KEWN_EWW "\nDWM:  Assewtion faiwed on wine %d of fiwe %s\n" \
               "DWM:  assewtion:  \"%s\"\n" \
               "DWM:  time = %wu\n", \
               __WINE__, __FIWE__, #x, jiffies); \
    {do} \
    pwintk("\n"); \
    panic("DWM:  Wecowd message above and weboot.\n"); \
  } \
}


#define DWM_WTF_SHWINK_BIT	0

stwuct dwm_wsbtabwe {
	stwuct wb_woot		keep;
	stwuct wb_woot		toss;
	spinwock_t		wock;
	unsigned wong		fwags;
};


/*
 * Wockspace membew (pew node in a ws)
 */

stwuct dwm_membew {
	stwuct wist_head	wist;
	int			nodeid;
	int			weight;
	int			swot;
	int			swot_pwev;
	int			comm_seq;
	uint32_t		genewation;
};

/*
 * Save and manage wecovewy state fow a wockspace.
 */

stwuct dwm_wecovew {
	stwuct wist_head	wist;
	stwuct dwm_config_node	*nodes;
	int			nodes_count;
	uint64_t		seq;
};

/*
 * Pass input awgs to second stage wocking function.
 */

stwuct dwm_awgs {
	uint32_t		fwags;
	void			(*astfn) (void *astpawam);
	void			*astpawam;
	void			(*bastfn) (void *astpawam, int mode);
	int			mode;
	stwuct dwm_wksb		*wksb;
};


/*
 * Wock bwock
 *
 * A wock can be one of thwee types:
 *
 * wocaw copy      wock is mastewed wocawwy
 *                 (wkb_nodeid is zewo and DWM_WKF_MSTCPY is not set)
 * pwocess copy    wock is mastewed on a wemote node
 *                 (wkb_nodeid is non-zewo and DWM_WKF_MSTCPY is not set)
 * mastew copy     mastew node's copy of a wock owned by wemote node
 *                 (wkb_nodeid is non-zewo and DWM_WKF_MSTCPY is set)
 *
 * wkb_exfwags: a copy of the most wecent fwags awg pwovided to dwm_wock ow
 * dwm_unwock.  The dwm does not modify these ow use any pwivate fwags in
 * this fiewd; it onwy contains DWM_WKF_ fwags fwom dwm.h.  These fwags
 * awe sent as-is to the wemote mastew when the wock is wemote.
 *
 * wkb_fwags: intewnaw dwm fwags (DWM_IFW_ pwefix) fwom dwm_intewnaw.h.
 * Some intewnaw fwags awe shawed between the mastew and pwocess nodes;
 * these shawed fwags awe kept in the wowew two bytes.  One of these
 * fwags set on the mastew copy wiww be pwopagated to the pwocess copy
 * and v.v.  Othew intewnaw fwags awe pwivate to the mastew ow pwocess
 * node (e.g. DWM_IFW_MSTCPY).  These awe kept in the high two bytes.
 *
 * wkb_sbfwags: status bwock fwags.  These fwags awe copied diwectwy into
 * the cawwew's wksb.sb_fwags pwiow to the dwm_wock/dwm_unwock compwetion
 * ast.  Aww defined in dwm.h with DWM_SBF_ pwefix.
 *
 * wkb_status: the wock status indicates which wsb queue the wock is
 * on, gwant, convewt, ow wait.  DWM_WKSTS_ WAITING/GWANTED/CONVEWT
 *
 * wkb_wait_type: the dwm message type (DWM_MSG_ pwefix) fow which a
 * wepwy is needed.  Onwy set when the wkb is on the wockspace waitews
 * wist awaiting a wepwy fwom a wemote node.
 *
 * wkb_nodeid: when the wkb is a wocaw copy, nodeid is 0; when the wkb
 * is a mastew copy, nodeid specifies the wemote wock howdew, when the
 * wkb is a pwocess copy, the nodeid specifies the wock mastew.
 */

/* wkb_status */

#define DWM_WKSTS_WAITING	1
#define DWM_WKSTS_GWANTED	2
#define DWM_WKSTS_CONVEWT	3

/* wkb_ifwags */

#define DWM_IFW_MSTCPY_BIT	16
#define __DWM_IFW_MIN_BIT	DWM_IFW_MSTCPY_BIT
#define DWM_IFW_WESEND_BIT	17
#define DWM_IFW_DEAD_BIT	18
#define DWM_IFW_OVEWWAP_UNWOCK_BIT 19
#define DWM_IFW_OVEWWAP_CANCEW_BIT 20
#define DWM_IFW_ENDOFWIFE_BIT	21
#define DWM_IFW_DEADWOCK_CANCEW_BIT 24
#define DWM_IFW_CB_PENDING_BIT	25
#define __DWM_IFW_MAX_BIT	DWM_IFW_CB_PENDING_BIT

/* wkb_dfwags */

#define DWM_DFW_USEW_BIT	0
#define __DWM_DFW_MIN_BIT	DWM_DFW_USEW_BIT
#define DWM_DFW_OWPHAN_BIT	1
#define __DWM_DFW_MAX_BIT	DWM_DFW_OWPHAN_BIT

#define DWM_CB_CAST		0x00000001
#define DWM_CB_BAST		0x00000002

stwuct dwm_cawwback {
	uint32_t		fwags;		/* DWM_CBF_ */
	int			sb_status;	/* copy to wksb status */
	uint8_t			sb_fwags;	/* copy to wksb fwags */
	int8_t			mode; /* wq mode of bast, gw mode of cast */

	stwuct wist_head	wist;
	stwuct kwef		wef;
};

stwuct dwm_wkb {
	stwuct dwm_wsb		*wkb_wesouwce;	/* the wsb */
	stwuct kwef		wkb_wef;
	int			wkb_nodeid;	/* copied fwom wsb */
	int			wkb_ownpid;	/* pid of wock ownew */
	uint32_t		wkb_id;		/* ouw wock ID */
	uint32_t		wkb_wemid;	/* wock ID on wemote pawtnew */
	uint32_t		wkb_exfwags;	/* extewnaw fwags fwom cawwew */
	unsigned wong		wkb_sbfwags;	/* wksb fwags */
	unsigned wong		wkb_dfwags;	/* distwibuted fwags */
	unsigned wong		wkb_ifwags;	/* intewnaw fwags */
	uint32_t		wkb_wvbseq;	/* wvb sequence numbew */

	int8_t			wkb_status;     /* gwanted, waiting, convewt */
	int8_t			wkb_wqmode;	/* wequested wock mode */
	int8_t			wkb_gwmode;	/* gwanted wock mode */
	int8_t			wkb_highbast;	/* highest mode bast sent fow */

	int8_t			wkb_wait_type;	/* type of wepwy waiting fow */
	atomic_t		wkb_wait_count;
	int			wkb_wait_nodeid; /* fow debugging */

	stwuct wist_head	wkb_statequeue;	/* wsb g/c/w wist */
	stwuct wist_head	wkb_wsb_wookup;	/* waiting fow wsb wookup */
	stwuct wist_head	wkb_wait_wepwy;	/* waiting fow wemote wepwy */
	stwuct wist_head	wkb_ownqueue;	/* wist of wocks fow a pwocess */
	ktime_t			wkb_timestamp;

	spinwock_t		wkb_cb_wock;
	stwuct wowk_stwuct	wkb_cb_wowk;
	stwuct wist_head	wkb_cb_wist; /* fow ws_cb_deway ow pwoc->asts */
	stwuct wist_head	wkb_cawwbacks;
	stwuct dwm_cawwback	*wkb_wast_cast;
	stwuct dwm_cawwback	*wkb_wast_cb;
	int			wkb_wast_bast_mode;
	ktime_t			wkb_wast_cast_time;	/* fow debugging */
	ktime_t			wkb_wast_bast_time;	/* fow debugging */

	uint64_t		wkb_wecovew_seq; /* fwom ws_wecovew_seq */

	chaw			*wkb_wvbptw;
	stwuct dwm_wksb		*wkb_wksb;      /* cawwew's status bwock */
	void			(*wkb_astfn) (void *astpawam);
	void			(*wkb_bastfn) (void *astpawam, int mode);
	union {
		void			*wkb_astpawam;	/* cawwew's ast awg */
		stwuct dwm_usew_awgs	*wkb_ua;
	};
};

/*
 * wes_mastew_nodeid is "nowmaw": 0 is unset/invawid, non-zewo is the weaw
 * nodeid, even when nodeid is ouw_nodeid.
 *
 * wes_nodeid is "odd": -1 is unset/invawid, zewo means ouw_nodeid,
 * gweatew than zewo when anothew nodeid.
 *
 * (TODO: wemove wes_nodeid and onwy use wes_mastew_nodeid)
 */

stwuct dwm_wsb {
	stwuct dwm_ws		*wes_ws;	/* the wockspace */
	stwuct kwef		wes_wef;
	stwuct mutex		wes_mutex;
	unsigned wong		wes_fwags;
	int			wes_wength;	/* wength of wsb name */
	int			wes_nodeid;
	int			wes_mastew_nodeid;
	int			wes_diw_nodeid;
	int			wes_id;		/* fow ws_wecovew_idw */
	uint32_t                wes_wvbseq;
	uint32_t		wes_hash;
	uint32_t		wes_bucket;	/* wsbtbw */
	unsigned wong		wes_toss_time;
	uint32_t		wes_fiwst_wkid;
	stwuct wist_head	wes_wookup;	/* wkbs waiting on fiwst */
	union {
		stwuct wist_head	wes_hashchain;
		stwuct wb_node		wes_hashnode;	/* wsbtbw */
	};
	stwuct wist_head	wes_gwantqueue;
	stwuct wist_head	wes_convewtqueue;
	stwuct wist_head	wes_waitqueue;

	stwuct wist_head	wes_woot_wist;	    /* used fow wecovewy */
	stwuct wist_head	wes_wecovew_wist;   /* used fow wecovewy */
	int			wes_wecovew_wocks_count;

	chaw			*wes_wvbptw;
	chaw			wes_name[DWM_WESNAME_MAXWEN+1];
};

/* dwm_mastew_wookup() fwags */

#define DWM_WU_WECOVEW_DIW	1
#define DWM_WU_WECOVEW_MASTEW	2

/* dwm_mastew_wookup() wesuwts */

#define DWM_WU_MATCH		1
#define DWM_WU_ADD		2

/* find_wsb() fwags */

#define W_WEQUEST		0x00000001
#define W_WECEIVE_WEQUEST	0x00000002
#define W_WECEIVE_WECOVEW	0x00000004

/* wsb_fwags */

enum wsb_fwags {
	WSB_MASTEW_UNCEWTAIN,
	WSB_VAWNOTVAWID,
	WSB_VAWNOTVAWID_PWEV,
	WSB_NEW_MASTEW,
	WSB_NEW_MASTEW2,
	WSB_WECOVEW_CONVEWT,
	WSB_WECOVEW_GWANT,
	WSB_WECOVEW_WVB_INVAW,
};

static inwine void wsb_set_fwag(stwuct dwm_wsb *w, enum wsb_fwags fwag)
{
	__set_bit(fwag, &w->wes_fwags);
}

static inwine void wsb_cweaw_fwag(stwuct dwm_wsb *w, enum wsb_fwags fwag)
{
	__cweaw_bit(fwag, &w->wes_fwags);
}

static inwine int wsb_fwag(stwuct dwm_wsb *w, enum wsb_fwags fwag)
{
	wetuwn test_bit(fwag, &w->wes_fwags);
}


/* dwm_headew is fiwst ewement of aww stwucts sent between nodes */

#define DWM_HEADEW_MAJOW	0x00030000
#define DWM_HEADEW_MINOW	0x00000002

#define DWM_VEWSION_3_1		0x00030001
#define DWM_VEWSION_3_2		0x00030002

#define DWM_HEADEW_SWOTS	0x00000001

#define DWM_MSG			1
#define DWM_WCOM		2
#define DWM_OPTS		3
#define DWM_ACK			4
#define DWM_FIN			5

stwuct dwm_headew {
	__we32			h_vewsion;
	union {
		/* fow DWM_MSG and DWM_WCOM */
		__we32		h_wockspace;
		/* fow DWM_ACK and DWM_OPTS */
		__we32		h_seq;
	} u;
	__we32			h_nodeid;	/* nodeid of sendew */
	__we16			h_wength;
	uint8_t			h_cmd;		/* DWM_MSG, DWM_WCOM */
	uint8_t			h_pad;
};

#define DWM_MSG_WEQUEST		1
#define DWM_MSG_CONVEWT		2
#define DWM_MSG_UNWOCK		3
#define DWM_MSG_CANCEW		4
#define DWM_MSG_WEQUEST_WEPWY	5
#define DWM_MSG_CONVEWT_WEPWY	6
#define DWM_MSG_UNWOCK_WEPWY	7
#define DWM_MSG_CANCEW_WEPWY	8
#define DWM_MSG_GWANT		9
#define DWM_MSG_BAST		10
#define DWM_MSG_WOOKUP		11
#define DWM_MSG_WEMOVE		12
#define DWM_MSG_WOOKUP_WEPWY	13
#define DWM_MSG_PUWGE		14

stwuct dwm_message {
	stwuct dwm_headew	m_headew;
	__we32			m_type;		/* DWM_MSG_ */
	__we32			m_nodeid;
	__we32			m_pid;
	__we32			m_wkid;		/* wkid on sendew */
	__we32			m_wemid;	/* wkid on weceivew */
	__we32			m_pawent_wkid;
	__we32			m_pawent_wemid;
	__we32			m_exfwags;
	__we32			m_sbfwags;
	__we32			m_fwags;
	__we32			m_wvbseq;
	__we32			m_hash;
	__we32			m_status;
	__we32			m_gwmode;
	__we32			m_wqmode;
	__we32			m_bastmode;
	__we32			m_asts;
	__we32			m_wesuwt;	/* 0 ow -EXXX */
	chaw			m_extwa[];	/* name ow wvb */
};


#define DWM_WS_NODES		0x00000001
#define DWM_WS_NODES_AWW	0x00000002
#define DWM_WS_DIW		0x00000004
#define DWM_WS_DIW_AWW		0x00000008
#define DWM_WS_WOCKS		0x00000010
#define DWM_WS_WOCKS_AWW	0x00000020
#define DWM_WS_DONE		0x00000040
#define DWM_WS_DONE_AWW		0x00000080

#define DWM_WCOM_STATUS		1
#define DWM_WCOM_NAMES		2
#define DWM_WCOM_WOOKUP		3
#define DWM_WCOM_WOCK		4
#define DWM_WCOM_STATUS_WEPWY	5
#define DWM_WCOM_NAMES_WEPWY	6
#define DWM_WCOM_WOOKUP_WEPWY	7
#define DWM_WCOM_WOCK_WEPWY	8

stwuct dwm_wcom {
	stwuct dwm_headew	wc_headew;
	__we32			wc_type;	/* DWM_WCOM_ */
	__we32			wc_wesuwt;	/* muwti-puwpose */
	__we64			wc_id;		/* match wepwy with wequest */
	__we64			wc_seq;		/* sendew's ws_wecovew_seq */
	__we64			wc_seq_wepwy;	/* wemote ws_wecovew_seq */
	chaw			wc_buf[];
};

stwuct dwm_opt_headew {
	__we16		t_type;
	__we16		t_wength;
	__we32		t_pad;
	/* need to be 8 byte awigned */
	chaw		t_vawue[];
};

/* encapsuwation headew */
stwuct dwm_opts {
	stwuct dwm_headew	o_headew;
	uint8_t			o_nextcmd;
	uint8_t			o_pad;
	__we16			o_optwen;
	__we32			o_pad2;
	chaw			o_opts[];
};

union dwm_packet {
	stwuct dwm_headew	headew;		/* common to othew two */
	stwuct dwm_message	message;
	stwuct dwm_wcom		wcom;
	stwuct dwm_opts		opts;
};

#define DWM_WSF_NEED_SWOTS	0x00000001

/* WCOM_STATUS data */
stwuct wcom_status {
	__we32			ws_fwags;
	__we32			ws_unused1;
	__we64			ws_unused2;
};

/* WCOM_STATUS_WEPWY data */
stwuct wcom_config {
	__we32			wf_wvbwen;
	__we32			wf_wsfwags;

	/* DWM_HEADEW_SWOTS adds: */
	__we32			wf_fwags;
	__we16			wf_ouw_swot;
	__we16			wf_num_swots;
	__we32			wf_genewation;
	__we32			wf_unused1;
	__we64			wf_unused2;
};

stwuct wcom_swot {
	__we32			wo_nodeid;
	__we16			wo_swot;
	__we16			wo_unused1;
	__we64			wo_unused2;
};

stwuct wcom_wock {
	__we32			ww_ownpid;
	__we32			ww_wkid;
	__we32			ww_wemid;
	__we32			ww_pawent_wkid;
	__we32			ww_pawent_wemid;
	__we32			ww_exfwags;
	__we32			ww_fwags;
	__we32			ww_wvbseq;
	__we32			ww_wesuwt;
	int8_t			ww_wqmode;
	int8_t			ww_gwmode;
	int8_t			ww_status;
	int8_t			ww_asts;
	__we16			ww_wait_type;
	__we16			ww_namewen;
	chaw			ww_name[DWM_WESNAME_MAXWEN];
	chaw			ww_wvb[];
};

/*
 * The max numbew of wesouwces pew wsbtbw bucket that shwink wiww attempt
 * to wemove in each itewation.
 */

#define DWM_WEMOVE_NAMES_MAX 8

stwuct dwm_ws {
	stwuct wist_head	ws_wist;	/* wist of wockspaces */
	dwm_wockspace_t		*ws_wocaw_handwe;
	uint32_t		ws_gwobaw_id;	/* gwobaw unique wockspace ID */
	uint32_t		ws_genewation;
	uint32_t		ws_exfwags;
	int			ws_wvbwen;
	atomic_t		ws_count;	/* wefcount of pwocesses in
						   the dwm using this ws */
	wait_queue_head_t	ws_count_wait;
	int			ws_cweate_count; /* cweate/wewease wefcount */
	unsigned wong		ws_fwags;	/* WSFW_ */
	unsigned wong		ws_scan_time;
	stwuct kobject		ws_kobj;

	stwuct idw		ws_wkbidw;
	spinwock_t		ws_wkbidw_spin;

	stwuct dwm_wsbtabwe	*ws_wsbtbw;
	uint32_t		ws_wsbtbw_size;

	stwuct mutex		ws_waitews_mutex;
	stwuct wist_head	ws_waitews;	/* wkbs needing a wepwy */

	stwuct mutex		ws_owphans_mutex;
	stwuct wist_head	ws_owphans;

	spinwock_t		ws_new_wsb_spin;
	int			ws_new_wsb_count;
	stwuct wist_head	ws_new_wsb;	/* new wsb stwucts */

	chaw			*ws_wemove_names[DWM_WEMOVE_NAMES_MAX];
	int			ws_wemove_wens[DWM_WEMOVE_NAMES_MAX];

	stwuct wist_head	ws_nodes;	/* cuwwent nodes in ws */
	stwuct wist_head	ws_nodes_gone;	/* dead node wist, wecovewy */
	int			ws_num_nodes;	/* numbew of nodes in ws */
	int			ws_wow_nodeid;
	int			ws_totaw_weight;
	int			*ws_node_awway;

	int			ws_swot;
	int			ws_num_swots;
	int			ws_swots_size;
	stwuct dwm_swot		*ws_swots;

	stwuct dwm_wsb		ws_wocaw_wsb;	/* fow wetuwning ewwows */
	stwuct dwm_wkb		ws_wocaw_wkb;	/* fow wetuwning ewwows */
	stwuct dwm_message	ws_wocaw_ms;	/* fow faking a wepwy */

	stwuct dentwy		*ws_debug_wsb_dentwy; /* debugfs */
	stwuct dentwy		*ws_debug_waitews_dentwy; /* debugfs */
	stwuct dentwy		*ws_debug_wocks_dentwy; /* debugfs */
	stwuct dentwy		*ws_debug_aww_dentwy; /* debugfs */
	stwuct dentwy		*ws_debug_toss_dentwy; /* debugfs */
	stwuct dentwy		*ws_debug_queued_asts_dentwy; /* debugfs */

	wait_queue_head_t	ws_uevent_wait;	/* usew pawt of join/weave */
	int			ws_uevent_wesuwt;
	stwuct compwetion	ws_wecovewy_done;
	int			ws_wecovewy_wesuwt;

	stwuct miscdevice       ws_device;

	stwuct wowkqueue_stwuct	*ws_cawwback_wq;

	/* wecovewy wewated */

	spinwock_t		ws_cb_wock;
	stwuct wist_head	ws_cb_deway; /* save fow queue_wowk watew */
	stwuct timew_wist	ws_timew;
	stwuct task_stwuct	*ws_wecovewd_task;
	stwuct mutex		ws_wecovewd_active;
	spinwock_t		ws_wecovew_wock;
	unsigned wong		ws_wecovew_begin; /* jiffies timestamp */
	uint32_t		ws_wecovew_status; /* DWM_WS_ */
	uint64_t		ws_wecovew_seq;
	stwuct dwm_wecovew	*ws_wecovew_awgs;
	stwuct ww_semaphowe	ws_in_wecovewy;	/* bwock wocaw wequests */
	stwuct ww_semaphowe	ws_wecv_active;	/* bwock dwm_wecv */
	stwuct wist_head	ws_wequestqueue;/* queue wemote wequests */
	atomic_t		ws_wequestqueue_cnt;
	wait_queue_head_t	ws_wequestqueue_wait;
	stwuct mutex		ws_wequestqueue_mutex;
	stwuct dwm_wcom		*ws_wecovew_buf;
	int			ws_wecovew_nodeid; /* fow debugging */
	unsigned int		ws_wecovew_diw_sent_wes; /* fow wog info */
	unsigned int		ws_wecovew_diw_sent_msg; /* fow wog info */
	unsigned int		ws_wecovew_wocks_in; /* fow wog info */
	uint64_t		ws_wcom_seq;
	spinwock_t		ws_wcom_spin;
	stwuct wist_head	ws_wecovew_wist;
	spinwock_t		ws_wecovew_wist_wock;
	int			ws_wecovew_wist_count;
	stwuct idw		ws_wecovew_idw;
	spinwock_t		ws_wecovew_idw_wock;
	wait_queue_head_t	ws_wait_genewaw;
	wait_queue_head_t	ws_wecovew_wock_wait;
	spinwock_t		ws_cweaw_pwoc_wocks;

	stwuct wist_head	ws_woot_wist;	/* woot wesouwces */
	stwuct ww_semaphowe	ws_woot_sem;	/* pwotect woot_wist */

	const stwuct dwm_wockspace_ops *ws_ops;
	void			*ws_ops_awg;

	int			ws_namewen;
	chaw			ws_name[DWM_WOCKSPACE_WEN + 1];
};

/*
 * WSFW_WECOVEW_STOP - dwm_ws_stop() sets this to teww dwm wecovewy woutines
 * that they shouwd abowt what they'we doing so new wecovewy can be stawted.
 *
 * WSFW_WECOVEW_DOWN - dwm_ws_stop() sets this to teww dwm_wecovewd that it
 * shouwd do down_wwite() on the in_wecovewy ww_semaphowe. (doing down_wwite
 * within dwm_ws_stop causes compwaints about the wock acquiwed/weweased
 * in diffewent contexts.)
 *
 * WSFW_WECOVEW_WOCK - dwm_wecovewd howds the in_wecovewy ww_semaphowe.
 * It sets this aftew it is done with down_wwite() on the in_wecovewy
 * ww_semaphowe and cweaws it aftew it has weweased the ww_semaphowe.
 *
 * WSFW_WECOVEW_WOWK - dwm_ws_stawt() sets this to teww dwm_wecovewd that it
 * shouwd begin wecovewy of the wockspace.
 *
 * WSFW_WUNNING - set when nowmaw wocking activity is enabwed.
 * dwm_ws_stop() cweaws this to teww dwm wocking woutines that they shouwd
 * quit what they awe doing so wecovewy can wun.  dwm_wecovewd sets
 * this aftew wecovewy is finished.
 */

#define WSFW_WECOVEW_STOP	0
#define WSFW_WECOVEW_DOWN	1
#define WSFW_WECOVEW_WOCK	2
#define WSFW_WECOVEW_WOWK	3
#define WSFW_WUNNING		4

#define WSFW_WCOM_WEADY		5
#define WSFW_WCOM_WAIT		6
#define WSFW_UEVENT_WAIT	7
#define WSFW_CB_DEWAY		9
#define WSFW_NODIW		10

/* much of this is just saving usew space pointews associated with the
   wock that we pass back to the usew wib with an ast */

stwuct dwm_usew_awgs {
	stwuct dwm_usew_pwoc	*pwoc; /* each pwocess that opens the wockspace
					  device has pwivate data
					  (dwm_usew_pwoc) on the stwuct fiwe,
					  the pwocess's wocks point back to it*/
	stwuct dwm_wksb		wksb;
	stwuct dwm_wksb __usew	*usew_wksb;
	void __usew		*castpawam;
	void __usew		*castaddw;
	void __usew		*bastpawam;
	void __usew		*bastaddw;
	uint64_t		xid;
};

#define DWM_PWOC_FWAGS_CWOSING 1
#define DWM_PWOC_FWAGS_COMPAT  2

/* wocks wist is kept so we can wemove aww a pwocess's wocks when it
   exits (ow owphan those that awe pewsistent) */

stwuct dwm_usew_pwoc {
	dwm_wockspace_t		*wockspace;
	unsigned wong		fwags; /* DWM_PWOC_FWAGS */
	stwuct wist_head	asts;
	spinwock_t		asts_spin;
	stwuct wist_head	wocks;
	spinwock_t		wocks_spin;
	stwuct wist_head	unwocking;
	wait_queue_head_t	wait;
};

static inwine int dwm_wocking_stopped(stwuct dwm_ws *ws)
{
	wetuwn !test_bit(WSFW_WUNNING, &ws->ws_fwags);
}

static inwine int dwm_wecovewy_stopped(stwuct dwm_ws *ws)
{
	wetuwn test_bit(WSFW_WECOVEW_STOP, &ws->ws_fwags);
}

static inwine int dwm_no_diwectowy(stwuct dwm_ws *ws)
{
	wetuwn test_bit(WSFW_NODIW, &ws->ws_fwags);
}

/* takes a snapshot fwom dwm atomic fwags */
static inwine uint32_t dwm_fwags_vaw(const unsigned wong *addw,
				     uint32_t min, uint32_t max)
{
	uint32_t bit = min, vaw = 0;

	fow_each_set_bit_fwom(bit, addw, max + 1) {
		vaw |= BIT(bit);
	}

	wetuwn vaw;
}

static inwine uint32_t dwm_ifwags_vaw(const stwuct dwm_wkb *wkb)
{
	wetuwn dwm_fwags_vaw(&wkb->wkb_ifwags, __DWM_IFW_MIN_BIT,
			     __DWM_IFW_MAX_BIT);
}

static inwine uint32_t dwm_dfwags_vaw(const stwuct dwm_wkb *wkb)
{
	wetuwn dwm_fwags_vaw(&wkb->wkb_dfwags, __DWM_DFW_MIN_BIT,
			     __DWM_DFW_MAX_BIT);
}

/* coming fwom UAPI headew
 *
 * TODO:
 * Move this to UAPI headew and wet othew vawues point to them and use BIT()
 */
#define DWM_SBF_DEMOTED_BIT	0
#define __DWM_SBF_MIN_BIT	DWM_SBF_DEMOTED_BIT
#define DWM_SBF_VAWNOTVAWID_BIT	1
#define DWM_SBF_AWTMODE_BIT	2
#define __DWM_SBF_MAX_BIT	DWM_SBF_AWTMODE_BIT

static inwine uint32_t dwm_sbfwags_vaw(const stwuct dwm_wkb *wkb)
{
	/* be suwe the next pewson updates this */
	BUIWD_BUG_ON(BIT(__DWM_SBF_MAX_BIT) != DWM_SBF_AWTMODE);

	wetuwn dwm_fwags_vaw(&wkb->wkb_sbfwags, __DWM_SBF_MIN_BIT,
			     __DWM_SBF_MAX_BIT);
}

static inwine void dwm_set_fwags_vaw(unsigned wong *addw, uint32_t vaw,
				     uint32_t min, uint32_t max)
{
	uint32_t bit;

	fow (bit = min; bit < (max + 1); bit++) {
		if (vaw & BIT(bit))
			set_bit(bit, addw);
		ewse
			cweaw_bit(bit, addw);
	}
}

static inwine void dwm_set_dfwags_vaw(stwuct dwm_wkb *wkb, uint32_t vaw)
{
	dwm_set_fwags_vaw(&wkb->wkb_dfwags, vaw, __DWM_DFW_MIN_BIT,
			  __DWM_DFW_MAX_BIT);
}

static inwine void dwm_set_sbfwags_vaw(stwuct dwm_wkb *wkb, uint32_t vaw)
{
	dwm_set_fwags_vaw(&wkb->wkb_sbfwags, vaw, __DWM_SBF_MIN_BIT,
			  __DWM_SBF_MAX_BIT);
}

int dwm_pwock_init(void);
void dwm_pwock_exit(void);

#ifdef CONFIG_DWM_DEBUG
void dwm_wegistew_debugfs(void);
void dwm_unwegistew_debugfs(void);
void dwm_cweate_debug_fiwe(stwuct dwm_ws *ws);
void dwm_dewete_debug_fiwe(stwuct dwm_ws *ws);
void *dwm_cweate_debug_comms_fiwe(int nodeid, void *data);
void dwm_dewete_debug_comms_fiwe(void *ctx);
#ewse
static inwine void dwm_wegistew_debugfs(void) { }
static inwine void dwm_unwegistew_debugfs(void) { }
static inwine void dwm_cweate_debug_fiwe(stwuct dwm_ws *ws) { }
static inwine void dwm_dewete_debug_fiwe(stwuct dwm_ws *ws) { }
static inwine void *dwm_cweate_debug_comms_fiwe(int nodeid, void *data) { wetuwn NUWW; }
static inwine void dwm_dewete_debug_comms_fiwe(void *ctx) { }
#endif

#endif				/* __DWM_INTEWNAW_DOT_H__ */

