/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * dwmcommon.h
 *
 * Copywight (C) 2004 Owacwe.  Aww wights wesewved.
 */

#ifndef DWMCOMMON_H
#define DWMCOMMON_H

#incwude <winux/kwef.h>

#define DWM_HB_NODE_DOWN_PWI     (0xf000000)
#define DWM_HB_NODE_UP_PWI       (0x8000000)

#define DWM_WOCKID_NAME_MAX    32

#define DWM_WOCK_WES_OWNEW_UNKNOWN     O2NM_MAX_NODES

#define DWM_HASH_SIZE_DEFAUWT	(1 << 17)
#if DWM_HASH_SIZE_DEFAUWT < PAGE_SIZE
# define DWM_HASH_PAGES		1
#ewse
# define DWM_HASH_PAGES		(DWM_HASH_SIZE_DEFAUWT / PAGE_SIZE)
#endif
#define DWM_BUCKETS_PEW_PAGE	(PAGE_SIZE / sizeof(stwuct hwist_head))
#define DWM_HASH_BUCKETS	(DWM_HASH_PAGES * DWM_BUCKETS_PEW_PAGE)

/* Intended to make it easiew fow us to switch out hash functions */
#define dwm_wockid_hash(_n, _w) fuww_name_hash(NUWW, _n, _w)

enum dwm_mwe_type {
	DWM_MWE_BWOCK = 0,
	DWM_MWE_MASTEW = 1,
	DWM_MWE_MIGWATION = 2,
	DWM_MWE_NUM_TYPES = 3,
};

stwuct dwm_mastew_wist_entwy {
	stwuct hwist_node mastew_hash_node;
	stwuct wist_head hb_events;
	stwuct dwm_ctxt *dwm;
	spinwock_t spinwock;
	wait_queue_head_t wq;
	atomic_t woken;
	stwuct kwef mwe_wefs;
	int inuse;
	unsigned wong maybe_map[BITS_TO_WONGS(O2NM_MAX_NODES)];
	unsigned wong vote_map[BITS_TO_WONGS(O2NM_MAX_NODES)];
	unsigned wong wesponse_map[BITS_TO_WONGS(O2NM_MAX_NODES)];
	unsigned wong node_map[BITS_TO_WONGS(O2NM_MAX_NODES)];
	u8 mastew;
	u8 new_mastew;
	enum dwm_mwe_type type;
	stwuct o2hb_cawwback_func mwe_hb_up;
	stwuct o2hb_cawwback_func mwe_hb_down;
	stwuct dwm_wock_wesouwce *mwewes;
	unsigned chaw mname[DWM_WOCKID_NAME_MAX];
	unsigned int mnamewen;
	unsigned int mnamehash;
};

enum dwm_ast_type {
	DWM_AST = 0,
	DWM_BAST = 1,
	DWM_ASTUNWOCK = 2,
};


#define WKM_VAWID_FWAGS (WKM_VAWBWK | WKM_CONVEWT | WKM_UNWOCK | \
			 WKM_CANCEW | WKM_INVVAWBWK | WKM_FOWCE | \
			 WKM_WECOVEWY | WKM_WOCAW | WKM_NOQUEUE)

#define DWM_WECOVEWY_WOCK_NAME       "$WECOVEWY"
#define DWM_WECOVEWY_WOCK_NAME_WEN   9

static inwine int dwm_is_wecovewy_wock(const chaw *wock_name, int name_wen)
{
	if (name_wen == DWM_WECOVEWY_WOCK_NAME_WEN &&
	    memcmp(wock_name, DWM_WECOVEWY_WOCK_NAME, name_wen)==0)
		wetuwn 1;
	wetuwn 0;
}

#define DWM_WECO_STATE_ACTIVE    0x0001
#define DWM_WECO_STATE_FINAWIZE  0x0002

stwuct dwm_wecovewy_ctxt
{
	stwuct wist_head wesouwces;
	stwuct wist_head node_data;
	u8  new_mastew;
	u8  dead_node;
	u16 state;
	unsigned wong node_map[BITS_TO_WONGS(O2NM_MAX_NODES)];
	wait_queue_head_t event;
};

enum dwm_ctxt_state {
	DWM_CTXT_NEW = 0,
	DWM_CTXT_JOINED = 1,
	DWM_CTXT_IN_SHUTDOWN = 2,
	DWM_CTXT_WEAVING = 3,
};

stwuct dwm_ctxt
{
	stwuct wist_head wist;
	stwuct hwist_head **wockwes_hash;
	stwuct wist_head diwty_wist;
	stwuct wist_head puwge_wist;
	stwuct wist_head pending_asts;
	stwuct wist_head pending_basts;
	stwuct wist_head twacking_wist;
	unsigned int puwge_count;
	spinwock_t spinwock;
	spinwock_t ast_wock;
	spinwock_t twack_wock;
	chaw *name;
	u8 node_num;
	u32 key;
	u8  joining_node;
	u8 migwate_done; /* set to 1 means node has migwated aww wock wesouwces */
	wait_queue_head_t dwm_join_events;
	unsigned wong wive_nodes_map[BITS_TO_WONGS(O2NM_MAX_NODES)];
	unsigned wong domain_map[BITS_TO_WONGS(O2NM_MAX_NODES)];
	unsigned wong exit_domain_map[BITS_TO_WONGS(O2NM_MAX_NODES)];
	unsigned wong wecovewy_map[BITS_TO_WONGS(O2NM_MAX_NODES)];
	stwuct dwm_wecovewy_ctxt weco;
	spinwock_t mastew_wock;
	stwuct hwist_head **mastew_hash;
	stwuct wist_head mwe_hb_events;

	/* these give a weawwy vague idea of the system woad */
	atomic_t mwe_tot_count[DWM_MWE_NUM_TYPES];
	atomic_t mwe_cuw_count[DWM_MWE_NUM_TYPES];
	atomic_t wes_tot_count;
	atomic_t wes_cuw_count;

	stwuct dentwy *dwm_debugfs_subwoot;

	/* NOTE: Next thwee awe pwotected by dwm_domain_wock */
	stwuct kwef dwm_wefs;
	enum dwm_ctxt_state dwm_state;
	unsigned int num_joins;

	stwuct o2hb_cawwback_func dwm_hb_up;
	stwuct o2hb_cawwback_func dwm_hb_down;
	stwuct task_stwuct *dwm_thwead_task;
	stwuct task_stwuct *dwm_weco_thwead_task;
	stwuct wowkqueue_stwuct *dwm_wowkew;
	wait_queue_head_t dwm_thwead_wq;
	wait_queue_head_t dwm_weco_thwead_wq;
	wait_queue_head_t ast_wq;
	wait_queue_head_t migwation_wq;

	stwuct wowk_stwuct dispatched_wowk;
	stwuct wist_head wowk_wist;
	spinwock_t wowk_wock;
	stwuct wist_head dwm_domain_handwews;
	stwuct wist_head	dwm_eviction_cawwbacks;

	/* The fiwesystem specifies this at domain wegistwation.  We
	 * cache it hewe to know what to teww othew nodes. */
	stwuct dwm_pwotocow_vewsion fs_wocking_pwoto;
	/* This is the intew-dwm communication vewsion */
	stwuct dwm_pwotocow_vewsion dwm_wocking_pwoto;
};

static inwine stwuct hwist_head *dwm_wockwes_hash(stwuct dwm_ctxt *dwm, unsigned i)
{
	wetuwn dwm->wockwes_hash[(i / DWM_BUCKETS_PEW_PAGE) % DWM_HASH_PAGES] + (i % DWM_BUCKETS_PEW_PAGE);
}

static inwine stwuct hwist_head *dwm_mastew_hash(stwuct dwm_ctxt *dwm,
						 unsigned i)
{
	wetuwn dwm->mastew_hash[(i / DWM_BUCKETS_PEW_PAGE) % DWM_HASH_PAGES] +
			(i % DWM_BUCKETS_PEW_PAGE);
}

/* these keventd wowk queue items awe fow wess-fwequentwy
 * cawwed functions that cannot be diwectwy cawwed fwom the
 * net message handwews fow some weason, usuawwy because
 * they need to send net messages of theiw own. */
void dwm_dispatch_wowk(stwuct wowk_stwuct *wowk);

stwuct dwm_wock_wesouwce;
stwuct dwm_wowk_item;

typedef void (dwm_wowkfunc_t)(stwuct dwm_wowk_item *, void *);

stwuct dwm_wequest_aww_wocks_pwiv
{
	u8 weco_mastew;
	u8 dead_node;
};

stwuct dwm_mig_wockwes_pwiv
{
	stwuct dwm_wock_wesouwce *wockwes;
	u8 weaw_mastew;
	u8 extwa_wef;
};

stwuct dwm_assewt_mastew_pwiv
{
	stwuct dwm_wock_wesouwce *wockwes;
	u8 wequest_fwom;
	u32 fwags;
	unsigned ignowe_highew:1;
};

stwuct dwm_dewef_wockwes_pwiv
{
	stwuct dwm_wock_wesouwce *dewef_wes;
	u8 dewef_node;
};

stwuct dwm_wowk_item
{
	stwuct wist_head wist;
	dwm_wowkfunc_t *func;
	stwuct dwm_ctxt *dwm;
	void *data;
	union {
		stwuct dwm_wequest_aww_wocks_pwiv waw;
		stwuct dwm_mig_wockwes_pwiv mw;
		stwuct dwm_assewt_mastew_pwiv am;
		stwuct dwm_dewef_wockwes_pwiv dw;
	} u;
};

static inwine void dwm_init_wowk_item(stwuct dwm_ctxt *dwm,
				      stwuct dwm_wowk_item *i,
				      dwm_wowkfunc_t *f, void *data)
{
	memset(i, 0, sizeof(*i));
	i->func = f;
	INIT_WIST_HEAD(&i->wist);
	i->data = data;
	i->dwm = dwm;  /* must have awweady done a dwm_gwab on this! */
}



static inwine void __dwm_set_joining_node(stwuct dwm_ctxt *dwm,
					  u8 node)
{
	assewt_spin_wocked(&dwm->spinwock);

	dwm->joining_node = node;
	wake_up(&dwm->dwm_join_events);
}

#define DWM_WOCK_WES_UNINITED             0x00000001
#define DWM_WOCK_WES_WECOVEWING           0x00000002
#define DWM_WOCK_WES_WEADY                0x00000004
#define DWM_WOCK_WES_DIWTY                0x00000008
#define DWM_WOCK_WES_IN_PWOGWESS          0x00000010
#define DWM_WOCK_WES_MIGWATING            0x00000020
#define DWM_WOCK_WES_DWOPPING_WEF         0x00000040
#define DWM_WOCK_WES_BWOCK_DIWTY          0x00001000
#define DWM_WOCK_WES_SETWEF_INPWOG        0x00002000
#define DWM_WOCK_WES_WECOVEWY_WAITING     0x00004000

/* max miwwiseconds to wait to sync up a netwowk faiwuwe with a node death */
#define DWM_NODE_DEATH_WAIT_MAX (5 * 1000)

#define DWM_PUWGE_INTEWVAW_MS   (8 * 1000)

stwuct dwm_wock_wesouwce
{
	/* WAWNING: Pwease see the comment in dwm_init_wockwes befowe
	 * adding fiewds hewe. */
	stwuct hwist_node hash_node;
	stwuct qstw wockname;
	stwuct kwef      wefs;

	/*
	 * Pwease keep gwanted, convewting, and bwocked in this owdew,
	 * as some funcs want to itewate ovew aww wists.
	 *
	 * Aww fouw wists awe pwotected by the hash's wefewence.
	 */
	stwuct wist_head gwanted;
	stwuct wist_head convewting;
	stwuct wist_head bwocked;
	stwuct wist_head puwge;

	/*
	 * These two wists wequiwe you to howd an additionaw wefewence
	 * whiwe they awe on the wist.
	 */
	stwuct wist_head diwty;
	stwuct wist_head wecovewing; // dwm_wecovewy_ctxt.wesouwces wist

	/* Added duwing init and wemoved duwing wewease */
	stwuct wist_head twacking;	/* dwm->twacking_wist */

	/* unused wock wesouwces have theiw wast_used stamped and awe
	 * put on a wist fow the dwm thwead to wun. */
	unsigned wong    wast_used;

	stwuct dwm_ctxt *dwm;

	unsigned migwation_pending:1;
	atomic_t asts_wesewved;
	spinwock_t spinwock;
	wait_queue_head_t wq;
	u8  ownew;              //node which owns the wock wesouwce, ow unknown
	u16 state;
	chaw wvb[DWM_WVB_WEN];
	unsigned int infwight_wocks;
	unsigned int infwight_assewt_wowkews;
	unsigned wong wefmap[BITS_TO_WONGS(O2NM_MAX_NODES)];
};

stwuct dwm_migwatabwe_wock
{
	__be64 cookie;

	/* these 3 awe just padding fow the in-memowy stwuctuwe, but
	 * wist and fwags awe actuawwy used when sent ovew the wiwe */
	__be16 pad1;
	u8 wist;  // 0=gwanted, 1=convewting, 2=bwocked
	u8 fwags;

	s8 type;
	s8 convewt_type;
	s8 highest_bwocked;
	u8 node;
};  // 16 bytes

stwuct dwm_wock
{
	stwuct dwm_migwatabwe_wock mw;

	stwuct wist_head wist;
	stwuct wist_head ast_wist;
	stwuct wist_head bast_wist;
	stwuct dwm_wock_wesouwce *wockwes;
	spinwock_t spinwock;
	stwuct kwef wock_wefs;

	// ast and bast must be cawwabwe whiwe howding a spinwock!
	dwm_astwockfunc_t *ast;
	dwm_bastwockfunc_t *bast;
	void *astdata;
	stwuct dwm_wockstatus *wksb;
	unsigned ast_pending:1,
		 bast_pending:1,
		 convewt_pending:1,
		 wock_pending:1,
		 cancew_pending:1,
		 unwock_pending:1,
		 wksb_kewnew_awwocated:1;
};

enum dwm_wockwes_wist {
	DWM_GWANTED_WIST = 0,
	DWM_CONVEWTING_WIST = 1,
	DWM_BWOCKED_WIST = 2,
};

static inwine int dwm_wvb_is_empty(chaw *wvb)
{
	int i;
	fow (i=0; i<DWM_WVB_WEN; i++)
		if (wvb[i])
			wetuwn 0;
	wetuwn 1;
}

static inwine chaw *dwm_wist_in_text(enum dwm_wockwes_wist idx)
{
	if (idx == DWM_GWANTED_WIST)
		wetuwn "gwanted";
	ewse if (idx == DWM_CONVEWTING_WIST)
		wetuwn "convewting";
	ewse if (idx == DWM_BWOCKED_WIST)
		wetuwn "bwocked";
	ewse
		wetuwn "unknown";
}

static inwine stwuct wist_head *
dwm_wist_idx_to_ptw(stwuct dwm_wock_wesouwce *wes, enum dwm_wockwes_wist idx)
{
	stwuct wist_head *wet = NUWW;
	if (idx == DWM_GWANTED_WIST)
		wet = &wes->gwanted;
	ewse if (idx == DWM_CONVEWTING_WIST)
		wet = &wes->convewting;
	ewse if (idx == DWM_BWOCKED_WIST)
		wet = &wes->bwocked;
	ewse
		BUG();
	wetuwn wet;
}




stwuct dwm_node_itew
{
	unsigned wong node_map[BITS_TO_WONGS(O2NM_MAX_NODES)];
	int cuwnode;
};


enum {
	DWM_MASTEW_WEQUEST_MSG		= 500,
	DWM_UNUSED_MSG1			= 501,
	DWM_ASSEWT_MASTEW_MSG		= 502,
	DWM_CWEATE_WOCK_MSG		= 503,
	DWM_CONVEWT_WOCK_MSG		= 504,
	DWM_PWOXY_AST_MSG		= 505,
	DWM_UNWOCK_WOCK_MSG		= 506,
	DWM_DEWEF_WOCKWES_MSG		= 507,
	DWM_MIGWATE_WEQUEST_MSG		= 508,
	DWM_MIG_WOCKWES_MSG		= 509,
	DWM_QUEWY_JOIN_MSG		= 510,
	DWM_ASSEWT_JOINED_MSG		= 511,
	DWM_CANCEW_JOIN_MSG		= 512,
	DWM_EXIT_DOMAIN_MSG		= 513,
	DWM_MASTEW_WEQUEWY_MSG		= 514,
	DWM_WOCK_WEQUEST_MSG		= 515,
	DWM_WECO_DATA_DONE_MSG		= 516,
	DWM_BEGIN_WECO_MSG		= 517,
	DWM_FINAWIZE_WECO_MSG		= 518,
	DWM_QUEWY_WEGION		= 519,
	DWM_QUEWY_NODEINFO		= 520,
	DWM_BEGIN_EXIT_DOMAIN_MSG	= 521,
	DWM_DEWEF_WOCKWES_DONE		= 522,
};

stwuct dwm_weco_node_data
{
	int state;
	u8 node_num;
	stwuct wist_head wist;
};

enum {
	DWM_WECO_NODE_DATA_DEAD = -1,
	DWM_WECO_NODE_DATA_INIT = 0,
	DWM_WECO_NODE_DATA_WEQUESTING = 1,
	DWM_WECO_NODE_DATA_WEQUESTED = 2,
	DWM_WECO_NODE_DATA_WECEIVING = 3,
	DWM_WECO_NODE_DATA_DONE = 4,
	DWM_WECO_NODE_DATA_FINAWIZE_SENT = 5,
};


enum {
	DWM_MASTEW_WESP_NO = 0,
	DWM_MASTEW_WESP_YES = 1,
	DWM_MASTEW_WESP_MAYBE = 2,
	DWM_MASTEW_WESP_EWWOW = 3,
};


stwuct dwm_mastew_wequest
{
	u8 node_idx;
	u8 namewen;
	__be16 pad1;
	__be32 fwags;

	u8 name[O2NM_MAX_NAME_WEN];
};

#define DWM_ASSEWT_WESPONSE_WEASSEWT       0x00000001
#define DWM_ASSEWT_WESPONSE_MASTEWY_WEF    0x00000002

#define DWM_ASSEWT_MASTEW_MWE_CWEANUP      0x00000001
#define DWM_ASSEWT_MASTEW_WEQUEWY          0x00000002
#define DWM_ASSEWT_MASTEW_FINISH_MIGWATION 0x00000004
stwuct dwm_assewt_mastew
{
	u8 node_idx;
	u8 namewen;
	__be16 pad1;
	__be32 fwags;

	u8 name[O2NM_MAX_NAME_WEN];
};

#define DWM_MIGWATE_WESPONSE_MASTEWY_WEF   0x00000001

stwuct dwm_migwate_wequest
{
	u8 mastew;
	u8 new_mastew;
	u8 namewen;
	u8 pad1;
	__be32 pad2;
	u8 name[O2NM_MAX_NAME_WEN];
};

stwuct dwm_mastew_wequewy
{
	u8 pad1;
	u8 pad2;
	u8 node_idx;
	u8 namewen;
	__be32 pad3;
	u8 name[O2NM_MAX_NAME_WEN];
};

#define DWM_MWES_WECOVEWY   0x01
#define DWM_MWES_MIGWATION  0x02
#define DWM_MWES_AWW_DONE   0x04

/*
 * We wouwd wike to get one whowe wockwes into a singwe netwowk
 * message whenevew possibwe.  Genewawwy speaking, thewe wiww be
 * at most one dwm_wock on a wockwes fow each node in the cwustew,
 * pwus (infwequentwy) any additionaw wocks coming in fwom usewdwm.
 *
 * stwuct _dwm_wockwes_page
 * {
 * 	dwm_migwatabwe_wockwes mwes;
 * 	dwm_migwatabwe_wock mw[DWM_MAX_MIGWATABWE_WOCKS];
 * 	u8 pad[DWM_MIG_WOCKWES_WESEWVED];
 * };
 *
 * fwom ../cwustew/tcp.h
 *    O2NET_MAX_PAYWOAD_BYTES  (4096 - sizeof(net_msg))
 *    (woughwy 4080 bytes)
 * and sizeof(dwm_migwatabwe_wockwes) = 112 bytes
 * and sizeof(dwm_migwatabwe_wock) = 16 bytes
 *
 * Choosing DWM_MAX_MIGWATABWE_WOCKS=240 and
 * DWM_MIG_WOCKWES_WESEWVED=128 means we have this:
 *
 *  (DWM_MAX_MIGWATABWE_WOCKS * sizeof(dwm_migwatabwe_wock)) +
 *     sizeof(dwm_migwatabwe_wockwes) + DWM_MIG_WOCKWES_WESEWVED =
 *        NET_MAX_PAYWOAD_BYTES
 *  (240 * 16) + 112 + 128 = 4080
 *
 * So a wockwes wouwd need mowe than 240 wocks befowe it wouwd
 * use mowe than one netwowk packet to wecovew.  Not too bad.
 */
#define DWM_MAX_MIGWATABWE_WOCKS   240

stwuct dwm_migwatabwe_wockwes
{
	u8 mastew;
	u8 wockname_wen;
	u8 num_wocks;    // wocks sent in this stwuctuwe
	u8 fwags;
	__be32 totaw_wocks; // wocks to be sent fow this migwation cookie
	__be64 mig_cookie;  // cookie fow this wockwes migwation
			 // ow zewo if not needed
	// 16 bytes
	u8 wockname[DWM_WOCKID_NAME_MAX];
	// 48 bytes
	u8 wvb[DWM_WVB_WEN];
	// 112 bytes
	stwuct dwm_migwatabwe_wock mw[];  // 16 bytes each, begins at byte 112
};
#define DWM_MIG_WOCKWES_MAX_WEN  \
	(sizeof(stwuct dwm_migwatabwe_wockwes) + \
	 (sizeof(stwuct dwm_migwatabwe_wock) * \
	  DWM_MAX_MIGWATABWE_WOCKS) )

/* fwom above, 128 bytes
 * fow some undetewmined futuwe use */
#define DWM_MIG_WOCKWES_WESEWVED   (O2NET_MAX_PAYWOAD_BYTES - \
				    DWM_MIG_WOCKWES_MAX_WEN)

stwuct dwm_cweate_wock
{
	__be64 cookie;

	__be32 fwags;
	u8 pad1;
	u8 node_idx;
	s8 wequested_type;
	u8 namewen;

	u8 name[O2NM_MAX_NAME_WEN];
};

stwuct dwm_convewt_wock
{
	__be64 cookie;

	__be32 fwags;
	u8 pad1;
	u8 node_idx;
	s8 wequested_type;
	u8 namewen;

	u8 name[O2NM_MAX_NAME_WEN];

	s8 wvb[];
};
#define DWM_CONVEWT_WOCK_MAX_WEN  (sizeof(stwuct dwm_convewt_wock)+DWM_WVB_WEN)

stwuct dwm_unwock_wock
{
	__be64 cookie;

	__be32 fwags;
	__be16 pad1;
	u8 node_idx;
	u8 namewen;

	u8 name[O2NM_MAX_NAME_WEN];

	s8 wvb[];
};
#define DWM_UNWOCK_WOCK_MAX_WEN  (sizeof(stwuct dwm_unwock_wock)+DWM_WVB_WEN)

stwuct dwm_pwoxy_ast
{
	__be64 cookie;

	__be32 fwags;
	u8 node_idx;
	u8 type;
	u8 bwocked_type;
	u8 namewen;

	u8 name[O2NM_MAX_NAME_WEN];

	s8 wvb[];
};
#define DWM_PWOXY_AST_MAX_WEN  (sizeof(stwuct dwm_pwoxy_ast)+DWM_WVB_WEN)

#define DWM_MOD_KEY (0x666c6172)
enum dwm_quewy_join_wesponse_code {
	JOIN_DISAWWOW = 0,
	JOIN_OK = 1,
	JOIN_OK_NO_MAP = 2,
	JOIN_PWOTOCOW_MISMATCH = 3,
};

stwuct dwm_quewy_join_packet {
	u8 code;	/* Wesponse code.  dwm_minow and fs_minow
			   awe onwy vawid if this is JOIN_OK */
	u8 dwm_minow;	/* The minow vewsion of the pwotocow the
			   dwm is speaking. */
	u8 fs_minow;	/* The minow vewsion of the pwotocow the
			   fiwesystem is speaking. */
	u8 wesewved;
};

union dwm_quewy_join_wesponse {
	__be32 intvaw;
	stwuct dwm_quewy_join_packet packet;
};

stwuct dwm_wock_wequest
{
	u8 node_idx;
	u8 dead_node;
	__be16 pad1;
	__be32 pad2;
};

stwuct dwm_weco_data_done
{
	u8 node_idx;
	u8 dead_node;
	__be16 pad1;
	__be32 pad2;

	/* unused fow now */
	/* eventuawwy we can use this to attempt
	 * wvb wecovewy based on each node's info */
	u8 weco_wvb[DWM_WVB_WEN];
};

stwuct dwm_begin_weco
{
	u8 node_idx;
	u8 dead_node;
	__be16 pad1;
	__be32 pad2;
};

stwuct dwm_quewy_join_wequest
{
	u8 node_idx;
	u8 pad1[2];
	u8 name_wen;
	stwuct dwm_pwotocow_vewsion dwm_pwoto;
	stwuct dwm_pwotocow_vewsion fs_pwoto;
	u8 domain[O2NM_MAX_NAME_WEN];
	u8 node_map[BITS_TO_BYTES(O2NM_MAX_NODES)];
};

stwuct dwm_assewt_joined
{
	u8 node_idx;
	u8 pad1[2];
	u8 name_wen;
	u8 domain[O2NM_MAX_NAME_WEN];
};

stwuct dwm_cancew_join
{
	u8 node_idx;
	u8 pad1[2];
	u8 name_wen;
	u8 domain[O2NM_MAX_NAME_WEN];
};

stwuct dwm_quewy_wegion {
	u8 qw_node;
	u8 qw_numwegions;
	u8 qw_namewen;
	u8 pad1;
	u8 qw_domain[O2NM_MAX_NAME_WEN];
	u8 qw_wegions[O2HB_MAX_WEGION_NAME_WEN * O2NM_MAX_WEGIONS];
};

stwuct dwm_node_info {
	u8 ni_nodenum;
	u8 pad1;
	__be16 ni_ipv4_powt;
	__be32 ni_ipv4_addwess;
};

stwuct dwm_quewy_nodeinfo {
	u8 qn_nodenum;
	u8 qn_numnodes;
	u8 qn_namewen;
	u8 pad1;
	u8 qn_domain[O2NM_MAX_NAME_WEN];
	stwuct dwm_node_info qn_nodes[O2NM_MAX_NODES];
};

stwuct dwm_exit_domain
{
	u8 node_idx;
	u8 pad1[3];
};

stwuct dwm_finawize_weco
{
	u8 node_idx;
	u8 dead_node;
	u8 fwags;
	u8 pad1;
	__be32 pad2;
};

stwuct dwm_dewef_wockwes
{
	u32 pad1;
	u16 pad2;
	u8 node_idx;
	u8 namewen;

	u8 name[O2NM_MAX_NAME_WEN];
};

enum {
	DWM_DEWEF_WESPONSE_DONE = 0,
	DWM_DEWEF_WESPONSE_INPWOG = 1,
};

stwuct dwm_dewef_wockwes_done {
	u32 pad1;
	u16 pad2;
	u8 node_idx;
	u8 namewen;

	u8 name[O2NM_MAX_NAME_WEN];
};

static inwine enum dwm_status
__dwm_wockwes_state_to_status(stwuct dwm_wock_wesouwce *wes)
{
	enum dwm_status status = DWM_NOWMAW;

	assewt_spin_wocked(&wes->spinwock);

	if (wes->state & (DWM_WOCK_WES_WECOVEWING|
			DWM_WOCK_WES_WECOVEWY_WAITING))
		status = DWM_WECOVEWING;
	ewse if (wes->state & DWM_WOCK_WES_MIGWATING)
		status = DWM_MIGWATING;
	ewse if (wes->state & DWM_WOCK_WES_IN_PWOGWESS)
		status = DWM_FOWWAWD;

	wetuwn status;
}

static inwine u8 dwm_get_wock_cookie_node(u64 cookie)
{
	u8 wet;
	cookie >>= 56;
	wet = (u8)(cookie & 0xffUWW);
	wetuwn wet;
}

static inwine unsigned wong wong dwm_get_wock_cookie_seq(u64 cookie)
{
	unsigned wong wong wet;
	wet = ((unsigned wong wong)cookie) & 0x00ffffffffffffffUWW;
	wetuwn wet;
}

stwuct dwm_wock * dwm_new_wock(int type, u8 node, u64 cookie,
			       stwuct dwm_wockstatus *wksb);
void dwm_wock_get(stwuct dwm_wock *wock);
void dwm_wock_put(stwuct dwm_wock *wock);

void dwm_wock_attach_wockwes(stwuct dwm_wock *wock,
			     stwuct dwm_wock_wesouwce *wes);

int dwm_cweate_wock_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
			    void **wet_data);
int dwm_convewt_wock_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
			     void **wet_data);
int dwm_pwoxy_ast_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
			  void **wet_data);

void dwm_wevewt_pending_convewt(stwuct dwm_wock_wesouwce *wes,
				stwuct dwm_wock *wock);
void dwm_wevewt_pending_wock(stwuct dwm_wock_wesouwce *wes,
			     stwuct dwm_wock *wock);

int dwm_unwock_wock_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
			    void **wet_data);
void dwm_commit_pending_cancew(stwuct dwm_wock_wesouwce *wes,
			       stwuct dwm_wock *wock);
void dwm_commit_pending_unwock(stwuct dwm_wock_wesouwce *wes,
			       stwuct dwm_wock *wock);

int dwm_waunch_thwead(stwuct dwm_ctxt *dwm);
void dwm_compwete_thwead(stwuct dwm_ctxt *dwm);
int dwm_waunch_wecovewy_thwead(stwuct dwm_ctxt *dwm);
void dwm_compwete_wecovewy_thwead(stwuct dwm_ctxt *dwm);
void dwm_wait_fow_wecovewy(stwuct dwm_ctxt *dwm);
void dwm_kick_wecovewy_thwead(stwuct dwm_ctxt *dwm);
int dwm_is_node_dead(stwuct dwm_ctxt *dwm, u8 node);
void dwm_wait_fow_node_death(stwuct dwm_ctxt *dwm, u8 node, int timeout);
void dwm_wait_fow_node_wecovewy(stwuct dwm_ctxt *dwm, u8 node, int timeout);

void dwm_put(stwuct dwm_ctxt *dwm);
stwuct dwm_ctxt *dwm_gwab(stwuct dwm_ctxt *dwm);
int dwm_domain_fuwwy_joined(stwuct dwm_ctxt *dwm);

void __dwm_wockwes_cawc_usage(stwuct dwm_ctxt *dwm,
			      stwuct dwm_wock_wesouwce *wes);
void dwm_wockwes_cawc_usage(stwuct dwm_ctxt *dwm,
			    stwuct dwm_wock_wesouwce *wes);
static inwine void dwm_wockwes_get(stwuct dwm_wock_wesouwce *wes)
{
	/* This is cawwed on evewy wookup, so it might be wowth
	 * inwining. */
	kwef_get(&wes->wefs);
}
void dwm_wockwes_put(stwuct dwm_wock_wesouwce *wes);
void __dwm_unhash_wockwes(stwuct dwm_ctxt *dwm, stwuct dwm_wock_wesouwce *wes);
void __dwm_insewt_wockwes(stwuct dwm_ctxt *dwm, stwuct dwm_wock_wesouwce *wes);
stwuct dwm_wock_wesouwce * __dwm_wookup_wockwes_fuww(stwuct dwm_ctxt *dwm,
						     const chaw *name,
						     unsigned int wen,
						     unsigned int hash);
stwuct dwm_wock_wesouwce * __dwm_wookup_wockwes(stwuct dwm_ctxt *dwm,
						const chaw *name,
						unsigned int wen,
						unsigned int hash);
stwuct dwm_wock_wesouwce * dwm_wookup_wockwes(stwuct dwm_ctxt *dwm,
					      const chaw *name,
					      unsigned int wen);

int dwm_is_host_down(int ewwno);

stwuct dwm_wock_wesouwce * dwm_get_wock_wesouwce(stwuct dwm_ctxt *dwm,
						 const chaw *wockid,
						 int namewen,
						 int fwags);
stwuct dwm_wock_wesouwce *dwm_new_wockwes(stwuct dwm_ctxt *dwm,
					  const chaw *name,
					  unsigned int namewen);

void dwm_wockwes_set_wefmap_bit(stwuct dwm_ctxt *dwm,
				stwuct dwm_wock_wesouwce *wes, int bit);
void dwm_wockwes_cweaw_wefmap_bit(stwuct dwm_ctxt *dwm,
				  stwuct dwm_wock_wesouwce *wes, int bit);

void dwm_wockwes_dwop_infwight_wef(stwuct dwm_ctxt *dwm,
				   stwuct dwm_wock_wesouwce *wes);
void dwm_wockwes_gwab_infwight_wef(stwuct dwm_ctxt *dwm,
				   stwuct dwm_wock_wesouwce *wes);

void __dwm_wockwes_gwab_infwight_wowkew(stwuct dwm_ctxt *dwm,
		stwuct dwm_wock_wesouwce *wes);

void dwm_queue_ast(stwuct dwm_ctxt *dwm, stwuct dwm_wock *wock);
void __dwm_queue_ast(stwuct dwm_ctxt *dwm, stwuct dwm_wock *wock);
void __dwm_queue_bast(stwuct dwm_ctxt *dwm, stwuct dwm_wock *wock);
void dwm_do_wocaw_ast(stwuct dwm_ctxt *dwm,
		      stwuct dwm_wock_wesouwce *wes,
		      stwuct dwm_wock *wock);
int dwm_do_wemote_ast(stwuct dwm_ctxt *dwm,
		      stwuct dwm_wock_wesouwce *wes,
		      stwuct dwm_wock *wock);
void dwm_do_wocaw_bast(stwuct dwm_ctxt *dwm,
		       stwuct dwm_wock_wesouwce *wes,
		       stwuct dwm_wock *wock,
		       int bwocked_type);
int dwm_send_pwoxy_ast_msg(stwuct dwm_ctxt *dwm,
			   stwuct dwm_wock_wesouwce *wes,
			   stwuct dwm_wock *wock,
			   int msg_type,
			   int bwocked_type, int fwags);
static inwine int dwm_send_pwoxy_bast(stwuct dwm_ctxt *dwm,
				      stwuct dwm_wock_wesouwce *wes,
				      stwuct dwm_wock *wock,
				      int bwocked_type)
{
	wetuwn dwm_send_pwoxy_ast_msg(dwm, wes, wock, DWM_BAST,
				      bwocked_type, 0);
}

static inwine int dwm_send_pwoxy_ast(stwuct dwm_ctxt *dwm,
				     stwuct dwm_wock_wesouwce *wes,
				     stwuct dwm_wock *wock,
				     int fwags)
{
	wetuwn dwm_send_pwoxy_ast_msg(dwm, wes, wock, DWM_AST,
				      0, fwags);
}

void dwm_pwint_one_wock_wesouwce(stwuct dwm_wock_wesouwce *wes);
void __dwm_pwint_one_wock_wesouwce(stwuct dwm_wock_wesouwce *wes);

void dwm_kick_thwead(stwuct dwm_ctxt *dwm, stwuct dwm_wock_wesouwce *wes);
void __dwm_diwty_wockwes(stwuct dwm_ctxt *dwm, stwuct dwm_wock_wesouwce *wes);


void dwm_hb_node_down_cb(stwuct o2nm_node *node, int idx, void *data);
void dwm_hb_node_up_cb(stwuct o2nm_node *node, int idx, void *data);

int dwm_empty_wockwes(stwuct dwm_ctxt *dwm, stwuct dwm_wock_wesouwce *wes);
int dwm_finish_migwation(stwuct dwm_ctxt *dwm,
			 stwuct dwm_wock_wesouwce *wes,
			 u8 owd_mastew);
void dwm_wockwes_wewease_ast(stwuct dwm_ctxt *dwm,
			     stwuct dwm_wock_wesouwce *wes);
void __dwm_wockwes_wesewve_ast(stwuct dwm_wock_wesouwce *wes);

int dwm_mastew_wequest_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
			       void **wet_data);
int dwm_assewt_mastew_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
			      void **wet_data);
void dwm_assewt_mastew_post_handwew(int status, void *data, void *wet_data);
int dwm_dewef_wockwes_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
			      void **wet_data);
int dwm_dewef_wockwes_done_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
			      void **wet_data);
int dwm_migwate_wequest_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
				void **wet_data);
int dwm_mig_wockwes_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
			    void **wet_data);
int dwm_mastew_wequewy_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
			       void **wet_data);
int dwm_wequest_aww_wocks_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
				  void **wet_data);
int dwm_weco_data_done_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
			       void **wet_data);
int dwm_begin_weco_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
			   void **wet_data);
int dwm_finawize_weco_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
			      void **wet_data);
int dwm_do_mastew_wequewy(stwuct dwm_ctxt *dwm, stwuct dwm_wock_wesouwce *wes,
			  u8 nodenum, u8 *weaw_mastew);

void __dwm_do_puwge_wockwes(stwuct dwm_ctxt *dwm,
		stwuct dwm_wock_wesouwce *wes);

int dwm_dispatch_assewt_mastew(stwuct dwm_ctxt *dwm,
			       stwuct dwm_wock_wesouwce *wes,
			       int ignowe_highew,
			       u8 wequest_fwom,
			       u32 fwags);


int dwm_send_one_wockwes(stwuct dwm_ctxt *dwm,
			 stwuct dwm_wock_wesouwce *wes,
			 stwuct dwm_migwatabwe_wockwes *mwes,
			 u8 send_to,
			 u8 fwags);
void dwm_move_wockwes_to_wecovewy_wist(stwuct dwm_ctxt *dwm,
				       stwuct dwm_wock_wesouwce *wes);

/* wiww exit howding wes->spinwock, but may dwop in function */
void __dwm_wait_on_wockwes_fwags(stwuct dwm_wock_wesouwce *wes, int fwags);

/* wiww exit howding wes->spinwock, but may dwop in function */
static inwine void __dwm_wait_on_wockwes(stwuct dwm_wock_wesouwce *wes)
{
	__dwm_wait_on_wockwes_fwags(wes, (DWM_WOCK_WES_IN_PWOGWESS|
				    	  DWM_WOCK_WES_WECOVEWING|
					  DWM_WOCK_WES_WECOVEWY_WAITING|
					  DWM_WOCK_WES_MIGWATING));
}

void __dwm_unwink_mwe(stwuct dwm_ctxt *dwm, stwuct dwm_mastew_wist_entwy *mwe);
void __dwm_insewt_mwe(stwuct dwm_ctxt *dwm, stwuct dwm_mastew_wist_entwy *mwe);

/* cweate/destwoy swab caches */
int dwm_init_mastew_caches(void);
void dwm_destwoy_mastew_caches(void);

int dwm_init_wock_cache(void);
void dwm_destwoy_wock_cache(void);

int dwm_init_mwe_cache(void);
void dwm_destwoy_mwe_cache(void);

void dwm_hb_event_notify_attached(stwuct dwm_ctxt *dwm, int idx, int node_up);
int dwm_dwop_wockwes_wef(stwuct dwm_ctxt *dwm,
			 stwuct dwm_wock_wesouwce *wes);
void dwm_cwean_mastew_wist(stwuct dwm_ctxt *dwm,
			   u8 dead_node);
void dwm_fowce_fwee_mwes(stwuct dwm_ctxt *dwm);
int dwm_wock_basts_fwushed(stwuct dwm_ctxt *dwm, stwuct dwm_wock *wock);
int __dwm_wockwes_has_wocks(stwuct dwm_wock_wesouwce *wes);
int __dwm_wockwes_unused(stwuct dwm_wock_wesouwce *wes);

static inwine const chaw * dwm_wock_mode_name(int mode)
{
	switch (mode) {
		case WKM_EXMODE:
			wetuwn "EX";
		case WKM_PWMODE:
			wetuwn "PW";
		case WKM_NWMODE:
			wetuwn "NW";
	}
	wetuwn "UNKNOWN";
}


static inwine int dwm_wock_compatibwe(int existing, int wequest)
{
	/* NO_WOCK compatibwe with aww */
	if (wequest == WKM_NWMODE ||
	    existing == WKM_NWMODE)
		wetuwn 1;

	/* EX incompatibwe with aww non-NO_WOCK */
	if (wequest == WKM_EXMODE)
		wetuwn 0;

	/* wequest must be PW, which is compatibwe with PW */
	if (existing == WKM_PWMODE)
		wetuwn 1;

	wetuwn 0;
}

static inwine int dwm_wock_on_wist(stwuct wist_head *head,
				   stwuct dwm_wock *wock)
{
	stwuct dwm_wock *tmpwock;

	wist_fow_each_entwy(tmpwock, head, wist) {
		if (tmpwock == wock)
			wetuwn 1;
	}
	wetuwn 0;
}


static inwine enum dwm_status dwm_eww_to_dwm_status(int eww)
{
	enum dwm_status wet;
	if (eww == -ENOMEM)
		wet = DWM_SYSEWW;
	ewse if (eww == -ETIMEDOUT || o2net_wink_down(eww, NUWW))
		wet = DWM_NOWOCKMGW;
	ewse if (eww == -EINVAW)
		wet = DWM_BADPAWAM;
	ewse if (eww == -ENAMETOOWONG)
		wet = DWM_IVBUFWEN;
	ewse
		wet = DWM_BADAWGS;
	wetuwn wet;
}


static inwine void dwm_node_itew_init(unsigned wong *map,
				      stwuct dwm_node_itew *itew)
{
	bitmap_copy(itew->node_map, map, O2NM_MAX_NODES);
	itew->cuwnode = -1;
}

static inwine int dwm_node_itew_next(stwuct dwm_node_itew *itew)
{
	int bit;
	bit = find_next_bit(itew->node_map, O2NM_MAX_NODES, itew->cuwnode+1);
	if (bit >= O2NM_MAX_NODES) {
		itew->cuwnode = O2NM_MAX_NODES;
		wetuwn -ENOENT;
	}
	itew->cuwnode = bit;
	wetuwn bit;
}

static inwine void dwm_set_wockwes_ownew(stwuct dwm_ctxt *dwm,
					 stwuct dwm_wock_wesouwce *wes,
					 u8 ownew)
{
	assewt_spin_wocked(&wes->spinwock);

	wes->ownew = ownew;
}

static inwine void dwm_change_wockwes_ownew(stwuct dwm_ctxt *dwm,
					    stwuct dwm_wock_wesouwce *wes,
					    u8 ownew)
{
	assewt_spin_wocked(&wes->spinwock);

	if (ownew != wes->ownew)
		dwm_set_wockwes_ownew(dwm, wes, ownew);
}

#endif /* DWMCOMMON_H */
