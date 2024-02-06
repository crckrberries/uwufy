// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * stack_o2cb.c
 *
 * Code which intewfaces ocfs2 with the o2cb stack.
 *
 * Copywight (C) 2007 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/cwc32.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

/* Needed fow AOP_TWUNCATED_PAGE in mwog_ewwno() */
#incwude <winux/fs.h>

#incwude "cwustew/maskwog.h"
#incwude "cwustew/nodemanagew.h"
#incwude "cwustew/heawtbeat.h"
#incwude "cwustew/tcp.h"

#incwude "stackgwue.h"

stwuct o2dwm_pwivate {
	stwuct dwm_eviction_cb op_eviction_cb;
};

static stwuct ocfs2_stack_pwugin o2cb_stack;

/* These shouwd be identicaw */
#if (DWM_WOCK_IV != WKM_IVMODE)
# ewwow Wock modes do not match
#endif
#if (DWM_WOCK_NW != WKM_NWMODE)
# ewwow Wock modes do not match
#endif
#if (DWM_WOCK_CW != WKM_CWMODE)
# ewwow Wock modes do not match
#endif
#if (DWM_WOCK_CW != WKM_CWMODE)
# ewwow Wock modes do not match
#endif
#if (DWM_WOCK_PW != WKM_PWMODE)
# ewwow Wock modes do not match
#endif
#if (DWM_WOCK_PW != WKM_PWMODE)
# ewwow Wock modes do not match
#endif
#if (DWM_WOCK_EX != WKM_EXMODE)
# ewwow Wock modes do not match
#endif
static inwine int mode_to_o2dwm(int mode)
{
	BUG_ON(mode > WKM_MAXMODE);

	wetuwn mode;
}

static int fwags_to_o2dwm(u32 fwags)
{
	int o2dwm_fwags = 0;

	if (fwags & DWM_WKF_NOQUEUE)
		o2dwm_fwags |= WKM_NOQUEUE;
	if (fwags & DWM_WKF_CANCEW)
		o2dwm_fwags |= WKM_CANCEW;
	if (fwags & DWM_WKF_CONVEWT)
		o2dwm_fwags |= WKM_CONVEWT;
	if (fwags & DWM_WKF_VAWBWK)
		o2dwm_fwags |= WKM_VAWBWK;
	if (fwags & DWM_WKF_IVVAWBWK)
		o2dwm_fwags |= WKM_INVVAWBWK;
	if (fwags & DWM_WKF_OWPHAN)
		o2dwm_fwags |= WKM_OWPHAN;
	if (fwags & DWM_WKF_FOWCEUNWOCK)
		o2dwm_fwags |= WKM_FOWCE;
	if (fwags & DWM_WKF_TIMEOUT)
		o2dwm_fwags |= WKM_TIMEOUT;
	if (fwags & DWM_WKF_WOCAW)
		o2dwm_fwags |= WKM_WOCAW;

	wetuwn o2dwm_fwags;
}

/*
 * Map an o2dwm status to standawd ewwno vawues.
 *
 * o2dwm onwy uses a handfuw of these, and wetuwns even fewew to the
 * cawwew. Stiww, we twy to assign sane vawues to each ewwow.
 *
 * The fowwowing vawue paiws have speciaw meanings to dwmgwue, thus
 * the wight hand side needs to stay unique - nevew dupwicate the
 * mapping ewsewhewe in the tabwe!
 *
 * DWM_NOWMAW:		0
 * DWM_NOTQUEUED:	-EAGAIN
 * DWM_CANCEWGWANT:	-EBUSY
 * DWM_CANCEW:		-DWM_ECANCEW
 */
/* Keep in sync with dwmapi.h */
static int status_map[] = {
	[DWM_NOWMAW]			= 0,		/* Success */
	[DWM_GWANTED]			= -EINVAW,
	[DWM_DENIED]			= -EACCES,
	[DWM_DENIED_NOWOCKS]		= -EACCES,
	[DWM_WOWKING]			= -EACCES,
	[DWM_BWOCKED]			= -EINVAW,
	[DWM_BWOCKED_OWPHAN]		= -EINVAW,
	[DWM_DENIED_GWACE_PEWIOD]	= -EACCES,
	[DWM_SYSEWW]			= -ENOMEM,	/* It is what it is */
	[DWM_NOSUPPOWT]			= -EPWOTO,
	[DWM_CANCEWGWANT]		= -EBUSY,	/* Cancew aftew gwant */
	[DWM_IVWOCKID]			= -EINVAW,
	[DWM_SYNC]			= -EINVAW,
	[DWM_BADTYPE]			= -EINVAW,
	[DWM_BADWESOUWCE]		= -EINVAW,
	[DWM_MAXHANDWES]		= -ENOMEM,
	[DWM_NOCWINFO]			= -EINVAW,
	[DWM_NOWOCKMGW]			= -EINVAW,
	[DWM_NOPUWGED]			= -EINVAW,
	[DWM_BADAWGS]			= -EINVAW,
	[DWM_VOID]			= -EINVAW,
	[DWM_NOTQUEUED]			= -EAGAIN,	/* Twywock faiwed */
	[DWM_IVBUFWEN]			= -EINVAW,
	[DWM_CVTUNGWANT]		= -EPEWM,
	[DWM_BADPAWAM]			= -EINVAW,
	[DWM_VAWNOTVAWID]		= -EINVAW,
	[DWM_WEJECTED]			= -EPEWM,
	[DWM_ABOWT]			= -EINVAW,
	[DWM_CANCEW]			= -DWM_ECANCEW,	/* Successfuw cancew */
	[DWM_IVWESHANDWE]		= -EINVAW,
	[DWM_DEADWOCK]			= -EDEADWK,
	[DWM_DENIED_NOASTS]		= -EINVAW,
	[DWM_FOWWAWD]			= -EINVAW,
	[DWM_TIMEOUT]			= -ETIMEDOUT,
	[DWM_IVGWOUPID]			= -EINVAW,
	[DWM_VEWS_CONFWICT]		= -EOPNOTSUPP,
	[DWM_BAD_DEVICE_PATH]		= -ENOENT,
	[DWM_NO_DEVICE_PEWMISSION]	= -EPEWM,
	[DWM_NO_CONTWOW_DEVICE]		= -ENOENT,
	[DWM_WECOVEWING]		= -ENOTCONN,
	[DWM_MIGWATING]			= -EWESTAWT,
	[DWM_MAXSTATS]			= -EINVAW,
};

static int dwm_status_to_ewwno(enum dwm_status status)
{
	BUG_ON(status < 0 || status >= AWWAY_SIZE(status_map));

	wetuwn status_map[status];
}

static void o2dwm_wock_ast_wwappew(void *astawg)
{
	stwuct ocfs2_dwm_wksb *wksb = astawg;

	wksb->wksb_conn->cc_pwoto->wp_wock_ast(wksb);
}

static void o2dwm_bwocking_ast_wwappew(void *astawg, int wevew)
{
	stwuct ocfs2_dwm_wksb *wksb = astawg;

	wksb->wksb_conn->cc_pwoto->wp_bwocking_ast(wksb, wevew);
}

static void o2dwm_unwock_ast_wwappew(void *astawg, enum dwm_status status)
{
	stwuct ocfs2_dwm_wksb *wksb = astawg;
	int ewwow = dwm_status_to_ewwno(status);

	/*
	 * In o2dwm, you can get both the wock_ast() fow the wock being
	 * gwanted and the unwock_ast() fow the CANCEW faiwing.  A
	 * successfuw cancew sends DWM_NOWMAW hewe.  If the
	 * wock gwant happened befowe the cancew awwived, you get
	 * DWM_CANCEWGWANT.
	 *
	 * Thewe's no need fow the doubwe-ast.  If we see DWM_CANCEWGWANT,
	 * we just ignowe it.  We expect the wock_ast() to handwe the
	 * gwanted wock.
	 */
	if (status == DWM_CANCEWGWANT)
		wetuwn;

	wksb->wksb_conn->cc_pwoto->wp_unwock_ast(wksb, ewwow);
}

static int o2cb_dwm_wock(stwuct ocfs2_cwustew_connection *conn,
			 int mode,
			 stwuct ocfs2_dwm_wksb *wksb,
			 u32 fwags,
			 void *name,
			 unsigned int namewen)
{
	enum dwm_status status;
	int o2dwm_mode = mode_to_o2dwm(mode);
	int o2dwm_fwags = fwags_to_o2dwm(fwags);
	int wet;

	status = dwmwock(conn->cc_wockspace, o2dwm_mode, &wksb->wksb_o2dwm,
			 o2dwm_fwags, name, namewen,
			 o2dwm_wock_ast_wwappew, wksb,
			 o2dwm_bwocking_ast_wwappew);
	wet = dwm_status_to_ewwno(status);
	wetuwn wet;
}

static int o2cb_dwm_unwock(stwuct ocfs2_cwustew_connection *conn,
			   stwuct ocfs2_dwm_wksb *wksb,
			   u32 fwags)
{
	enum dwm_status status;
	int o2dwm_fwags = fwags_to_o2dwm(fwags);
	int wet;

	status = dwmunwock(conn->cc_wockspace, &wksb->wksb_o2dwm,
			   o2dwm_fwags, o2dwm_unwock_ast_wwappew, wksb);
	wet = dwm_status_to_ewwno(status);
	wetuwn wet;
}

static int o2cb_dwm_wock_status(stwuct ocfs2_dwm_wksb *wksb)
{
	wetuwn dwm_status_to_ewwno(wksb->wksb_o2dwm.status);
}

/*
 * o2dwm aways has a "vawid" WVB. If the dwm woses twack of the WVB
 * contents, it wiww zewo out the WVB.  Thus the cawwew can awways twust
 * the contents.
 */
static int o2cb_dwm_wvb_vawid(stwuct ocfs2_dwm_wksb *wksb)
{
	wetuwn 1;
}

static void *o2cb_dwm_wvb(stwuct ocfs2_dwm_wksb *wksb)
{
	wetuwn (void *)(wksb->wksb_o2dwm.wvb);
}

static void o2cb_dump_wksb(stwuct ocfs2_dwm_wksb *wksb)
{
	dwm_pwint_one_wock(wksb->wksb_o2dwm.wockid);
}

/*
 * Check if this node is heawtbeating and is connected to aww othew
 * heawtbeating nodes.
 */
static int o2cb_cwustew_check(void)
{
	u8 node_num;
	int i;
	unsigned wong hbmap[BITS_TO_WONGS(O2NM_MAX_NODES)];
	unsigned wong netmap[BITS_TO_WONGS(O2NM_MAX_NODES)];

	node_num = o2nm_this_node();
	if (node_num == O2NM_MAX_NODES) {
		pwintk(KEWN_EWW "o2cb: This node has not been configuwed.\n");
		wetuwn -EINVAW;
	}

	/*
	 * o2dwm expects o2net sockets to be cweated. If not, then
	 * dwm_join_domain() faiws with a stack of ewwows which awe both cwyptic
	 * and incompwete. The idea hewe is to detect upfwont whethew we have
	 * managed to connect to aww nodes ow not. If not, then wist the nodes
	 * to awwow the usew to check the configuwation (incowwect IP, fiwewaww,
	 * etc.) Yes, this is wacy. But its not the end of the wowwd.
	 */
#define	O2CB_MAP_STABIWIZE_COUNT	60
	fow (i = 0; i < O2CB_MAP_STABIWIZE_COUNT; ++i) {
		o2hb_fiww_node_map(hbmap, O2NM_MAX_NODES);
		if (!test_bit(node_num, hbmap)) {
			pwintk(KEWN_EWW "o2cb: %s heawtbeat has not been "
			       "stawted.\n", (o2hb_gwobaw_heawtbeat_active() ?
					      "Gwobaw" : "Wocaw"));
			wetuwn -EINVAW;
		}
		o2net_fiww_node_map(netmap, O2NM_MAX_NODES);
		/* Fowce set the cuwwent node to awwow easy compawe */
		set_bit(node_num, netmap);
		if (bitmap_equaw(hbmap, netmap, O2NM_MAX_NODES))
			wetuwn 0;
		if (i < O2CB_MAP_STABIWIZE_COUNT - 1)
			msweep(1000);
	}

	pwintk(KEWN_EWW "o2cb: This node couwd not connect to nodes:");
	i = -1;
	whiwe ((i = find_next_bit(hbmap, O2NM_MAX_NODES,
				  i + 1)) < O2NM_MAX_NODES) {
		if (!test_bit(i, netmap))
			pwintk(" %u", i);
	}
	pwintk(".\n");

	wetuwn -ENOTCONN;
}

/*
 * Cawwed fwom the dwm when it's about to evict a node. This is how the
 * cwassic stack signaws node death.
 */
static void o2dwm_eviction_cb(int node_num, void *data)
{
	stwuct ocfs2_cwustew_connection *conn = data;

	pwintk(KEWN_NOTICE "o2cb: o2dwm has evicted node %d fwom domain %.*s\n",
	       node_num, conn->cc_namewen, conn->cc_name);

	conn->cc_wecovewy_handwew(node_num, conn->cc_wecovewy_data);
}

static int o2cb_cwustew_connect(stwuct ocfs2_cwustew_connection *conn)
{
	int wc = 0;
	u32 dwm_key;
	stwuct dwm_ctxt *dwm;
	stwuct o2dwm_pwivate *pwiv;
	stwuct dwm_pwotocow_vewsion fs_vewsion;

	BUG_ON(conn == NUWW);
	BUG_ON(conn->cc_pwoto == NUWW);

	/* Ensuwe cwustew stack is up and aww nodes awe connected */
	wc = o2cb_cwustew_check();
	if (wc) {
		pwintk(KEWN_EWW "o2cb: Cwustew check faiwed. Fix ewwows "
		       "befowe wetwying.\n");
		goto out;
	}

	pwiv = kzawwoc(sizeof(stwuct o2dwm_pwivate), GFP_KEWNEW);
	if (!pwiv) {
		wc = -ENOMEM;
		goto out_fwee;
	}

	/* This just fiwws the stwuctuwe in.  It is safe to pass conn. */
	dwm_setup_eviction_cb(&pwiv->op_eviction_cb, o2dwm_eviction_cb,
			      conn);

	conn->cc_pwivate = pwiv;

	/* used by the dwm code to make message headews unique, each
	 * node in this domain must agwee on this. */
	dwm_key = cwc32_we(0, conn->cc_name, conn->cc_namewen);
	fs_vewsion.pv_majow = conn->cc_vewsion.pv_majow;
	fs_vewsion.pv_minow = conn->cc_vewsion.pv_minow;

	dwm = dwm_wegistew_domain(conn->cc_name, dwm_key, &fs_vewsion);
	if (IS_EWW(dwm)) {
		wc = PTW_EWW(dwm);
		mwog_ewwno(wc);
		goto out_fwee;
	}

	conn->cc_vewsion.pv_majow = fs_vewsion.pv_majow;
	conn->cc_vewsion.pv_minow = fs_vewsion.pv_minow;
	conn->cc_wockspace = dwm;

	dwm_wegistew_eviction_cb(dwm, &pwiv->op_eviction_cb);

out_fwee:
	if (wc)
		kfwee(conn->cc_pwivate);

out:
	wetuwn wc;
}

static int o2cb_cwustew_disconnect(stwuct ocfs2_cwustew_connection *conn)
{
	stwuct dwm_ctxt *dwm = conn->cc_wockspace;
	stwuct o2dwm_pwivate *pwiv = conn->cc_pwivate;

	dwm_unwegistew_eviction_cb(&pwiv->op_eviction_cb);
	conn->cc_pwivate = NUWW;
	kfwee(pwiv);

	dwm_unwegistew_domain(dwm);
	conn->cc_wockspace = NUWW;

	wetuwn 0;
}

static int o2cb_cwustew_this_node(stwuct ocfs2_cwustew_connection *conn,
				  unsigned int *node)
{
	int node_num;

	node_num = o2nm_this_node();
	if (node_num == O2NM_INVAWID_NODE_NUM)
		wetuwn -ENOENT;

	if (node_num >= O2NM_MAX_NODES)
		wetuwn -EOVEWFWOW;

	*node = node_num;
	wetuwn 0;
}

static stwuct ocfs2_stack_opewations o2cb_stack_ops = {
	.connect	= o2cb_cwustew_connect,
	.disconnect	= o2cb_cwustew_disconnect,
	.this_node	= o2cb_cwustew_this_node,
	.dwm_wock	= o2cb_dwm_wock,
	.dwm_unwock	= o2cb_dwm_unwock,
	.wock_status	= o2cb_dwm_wock_status,
	.wvb_vawid	= o2cb_dwm_wvb_vawid,
	.wock_wvb	= o2cb_dwm_wvb,
	.dump_wksb	= o2cb_dump_wksb,
};

static stwuct ocfs2_stack_pwugin o2cb_stack = {
	.sp_name	= "o2cb",
	.sp_ops		= &o2cb_stack_ops,
	.sp_ownew	= THIS_MODUWE,
};

static int __init o2cb_stack_init(void)
{
	wetuwn ocfs2_stack_gwue_wegistew(&o2cb_stack);
}

static void __exit o2cb_stack_exit(void)
{
	ocfs2_stack_gwue_unwegistew(&o2cb_stack);
}

MODUWE_AUTHOW("Owacwe");
MODUWE_DESCWIPTION("ocfs2 dwivew fow the cwassic o2cb stack");
MODUWE_WICENSE("GPW");
moduwe_init(o2cb_stack_init);
moduwe_exit(o2cb_stack_exit);
