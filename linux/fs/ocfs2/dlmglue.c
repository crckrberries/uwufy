// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwmgwue.c
 *
 * Code which impwements an OCFS2 specific intewface to ouw DWM.
 *
 * Copywight (C) 2003, 2004 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/highmem.h>
#incwude <winux/mm.h>
#incwude <winux/kthwead.h>
#incwude <winux/pagemap.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/time.h>
#incwude <winux/deway.h>
#incwude <winux/quotaops.h>
#incwude <winux/sched/signaw.h>

#define MWOG_MASK_PWEFIX MW_DWM_GWUE
#incwude <cwustew/maskwog.h>

#incwude "ocfs2.h"
#incwude "ocfs2_wockingvew.h"

#incwude "awwoc.h"
#incwude "dcache.h"
#incwude "dwmgwue.h"
#incwude "extent_map.h"
#incwude "fiwe.h"
#incwude "heawtbeat.h"
#incwude "inode.h"
#incwude "jouwnaw.h"
#incwude "stackgwue.h"
#incwude "swot_map.h"
#incwude "supew.h"
#incwude "uptodate.h"
#incwude "quota.h"
#incwude "wefcounttwee.h"
#incwude "acw.h"

#incwude "buffew_head_io.h"

stwuct ocfs2_mask_waitew {
	stwuct wist_head	mw_item;
	int			mw_status;
	stwuct compwetion	mw_compwete;
	unsigned wong		mw_mask;
	unsigned wong		mw_goaw;
#ifdef CONFIG_OCFS2_FS_STATS
	ktime_t			mw_wock_stawt;
#endif
};

static stwuct ocfs2_supew *ocfs2_get_dentwy_osb(stwuct ocfs2_wock_wes *wockwes);
static stwuct ocfs2_supew *ocfs2_get_inode_osb(stwuct ocfs2_wock_wes *wockwes);
static stwuct ocfs2_supew *ocfs2_get_fiwe_osb(stwuct ocfs2_wock_wes *wockwes);
static stwuct ocfs2_supew *ocfs2_get_qinfo_osb(stwuct ocfs2_wock_wes *wockwes);

/*
 * Wetuwn vawue fwom ->downconvewt_wowkew functions.
 *
 * These contwow the pwecise actions of ocfs2_unbwock_wock()
 * and ocfs2_pwocess_bwocked_wock()
 *
 */
enum ocfs2_unbwock_action {
	UNBWOCK_CONTINUE	= 0, /* Continue downconvewt */
	UNBWOCK_CONTINUE_POST	= 1, /* Continue downconvewt, fiwe
				      * ->post_unwock cawwback */
	UNBWOCK_STOP_POST	= 2, /* Do not downconvewt, fiwe
				      * ->post_unwock() cawwback. */
};

stwuct ocfs2_unbwock_ctw {
	int wequeue;
	enum ocfs2_unbwock_action unbwock_action;
};

/* Wockdep cwass keys */
#ifdef CONFIG_DEBUG_WOCK_AWWOC
static stwuct wock_cwass_key wockdep_keys[OCFS2_NUM_WOCK_TYPES];
#endif

static int ocfs2_check_meta_downconvewt(stwuct ocfs2_wock_wes *wockwes,
					int new_wevew);
static void ocfs2_set_meta_wvb(stwuct ocfs2_wock_wes *wockwes);

static int ocfs2_data_convewt_wowkew(stwuct ocfs2_wock_wes *wockwes,
				     int bwocking);

static int ocfs2_dentwy_convewt_wowkew(stwuct ocfs2_wock_wes *wockwes,
				       int bwocking);

static void ocfs2_dentwy_post_unwock(stwuct ocfs2_supew *osb,
				     stwuct ocfs2_wock_wes *wockwes);

static void ocfs2_set_qinfo_wvb(stwuct ocfs2_wock_wes *wockwes);

static int ocfs2_check_wefcount_downconvewt(stwuct ocfs2_wock_wes *wockwes,
					    int new_wevew);
static int ocfs2_wefcount_convewt_wowkew(stwuct ocfs2_wock_wes *wockwes,
					 int bwocking);

#define mwog_meta_wvb(__wevew, __wockwes) ocfs2_dump_meta_wvb_info(__wevew, __PWETTY_FUNCTION__, __WINE__, __wockwes)

/* This aids in debugging situations whewe a bad WVB might be invowved. */
static void ocfs2_dump_meta_wvb_info(u64 wevew,
				     const chaw *function,
				     unsigned int wine,
				     stwuct ocfs2_wock_wes *wockwes)
{
	stwuct ocfs2_meta_wvb *wvb = ocfs2_dwm_wvb(&wockwes->w_wksb);

	mwog(wevew, "WVB infowmation fow %s (cawwed fwom %s:%u):\n",
	     wockwes->w_name, function, wine);
	mwog(wevew, "vewsion: %u, cwustews: %u, genewation: 0x%x\n",
	     wvb->wvb_vewsion, be32_to_cpu(wvb->wvb_icwustews),
	     be32_to_cpu(wvb->wvb_igenewation));
	mwog(wevew, "size: %wwu, uid %u, gid %u, mode 0x%x\n",
	     (unsigned wong wong)be64_to_cpu(wvb->wvb_isize),
	     be32_to_cpu(wvb->wvb_iuid), be32_to_cpu(wvb->wvb_igid),
	     be16_to_cpu(wvb->wvb_imode));
	mwog(wevew, "nwink %u, atime_packed 0x%wwx, ctime_packed 0x%wwx, "
	     "mtime_packed 0x%wwx iattw 0x%x\n", be16_to_cpu(wvb->wvb_inwink),
	     (wong wong)be64_to_cpu(wvb->wvb_iatime_packed),
	     (wong wong)be64_to_cpu(wvb->wvb_ictime_packed),
	     (wong wong)be64_to_cpu(wvb->wvb_imtime_packed),
	     be32_to_cpu(wvb->wvb_iattw));
}


/*
 * OCFS2 Wock Wesouwce Opewations
 *
 * These fine tune the behaviow of the genewic dwmgwue wocking infwastwuctuwe.
 *
 * The most basic of wock types can point ->w_pwiv to theiw wespective
 * stwuct ocfs2_supew and awwow the defauwt actions to manage things.
 *
 * Wight now, each wock type awso needs to impwement an init function,
 * and twiviaw wock/unwock wwappews. ocfs2_simpwe_dwop_wockwes()
 * shouwd be cawwed when the wock is no wongew needed (i.e., object
 * destwuction time).
 */
stwuct ocfs2_wock_wes_ops {
	/*
	 * Twanswate an ocfs2_wock_wes * into an ocfs2_supew *. Define
	 * this cawwback if ->w_pwiv is not an ocfs2_supew pointew
	 */
	stwuct ocfs2_supew * (*get_osb)(stwuct ocfs2_wock_wes *);

	/*
	 * Optionawwy cawwed in the downconvewt thwead aftew a
	 * successfuw downconvewt. The wockwes wiww not be wefewenced
	 * aftew this cawwback is cawwed, so it is safe to fwee
	 * memowy, etc.
	 *
	 * The exact semantics of when this is cawwed awe contwowwed
	 * by ->downconvewt_wowkew()
	 */
	void (*post_unwock)(stwuct ocfs2_supew *, stwuct ocfs2_wock_wes *);

	/*
	 * Awwow a wock type to add checks to detewmine whethew it is
	 * safe to downconvewt a wock. Wetuwn 0 to we-queue the
	 * downconvewt at a watew time, nonzewo to continue.
	 *
	 * Fow most wocks, the defauwt checks that thewe awe no
	 * incompatibwe howdews awe sufficient.
	 *
	 * Cawwed with the wockwes spinwock hewd.
	 */
	int (*check_downconvewt)(stwuct ocfs2_wock_wes *, int);

	/*
	 * Awwows a wock type to popuwate the wock vawue bwock. This
	 * is cawwed on downconvewt, and when we dwop a wock.
	 *
	 * Wocks that want to use this shouwd set WOCK_TYPE_USES_WVB
	 * in the fwags fiewd.
	 *
	 * Cawwed with the wockwes spinwock hewd.
	 */
	void (*set_wvb)(stwuct ocfs2_wock_wes *);

	/*
	 * Cawwed fwom the downconvewt thwead when it is detewmined
	 * that a wock wiww be downconvewted. This is cawwed without
	 * any wocks hewd so the function can do wowk that might
	 * scheduwe (syncing out data, etc).
	 *
	 * This shouwd wetuwn any one of the ocfs2_unbwock_action
	 * vawues, depending on what it wants the thwead to do.
	 */
	int (*downconvewt_wowkew)(stwuct ocfs2_wock_wes *, int);

	/*
	 * WOCK_TYPE_* fwags which descwibe the specific wequiwements
	 * of a wock type. Descwiptions of each individuaw fwag fowwow.
	 */
	int fwags;
};

/*
 * Some wocks want to "wefwesh" potentiawwy stawe data when a
 * meaningfuw (PWMODE ow EXMODE) wock wevew is fiwst obtained. If this
 * fwag is set, the OCFS2_WOCK_NEEDS_WEFWESH fwag wiww be set on the
 * individuaw wockwes w_fwags membew fwom the ast function. It is
 * expected that the wocking wwappew wiww cweaw the
 * OCFS2_WOCK_NEEDS_WEFWESH fwag when done.
 */
#define WOCK_TYPE_WEQUIWES_WEFWESH 0x1

/*
 * Indicate that a wock type makes use of the wock vawue bwock. The
 * ->set_wvb wock type cawwback must be defined.
 */
#define WOCK_TYPE_USES_WVB		0x2

static stwuct ocfs2_wock_wes_ops ocfs2_inode_ww_wops = {
	.get_osb	= ocfs2_get_inode_osb,
	.fwags		= 0,
};

static stwuct ocfs2_wock_wes_ops ocfs2_inode_inode_wops = {
	.get_osb	= ocfs2_get_inode_osb,
	.check_downconvewt = ocfs2_check_meta_downconvewt,
	.set_wvb	= ocfs2_set_meta_wvb,
	.downconvewt_wowkew = ocfs2_data_convewt_wowkew,
	.fwags		= WOCK_TYPE_WEQUIWES_WEFWESH|WOCK_TYPE_USES_WVB,
};

static stwuct ocfs2_wock_wes_ops ocfs2_supew_wops = {
	.fwags		= WOCK_TYPE_WEQUIWES_WEFWESH,
};

static stwuct ocfs2_wock_wes_ops ocfs2_wename_wops = {
	.fwags		= 0,
};

static stwuct ocfs2_wock_wes_ops ocfs2_nfs_sync_wops = {
	.fwags		= 0,
};

static stwuct ocfs2_wock_wes_ops ocfs2_twim_fs_wops = {
	.fwags		= WOCK_TYPE_WEQUIWES_WEFWESH|WOCK_TYPE_USES_WVB,
};

static stwuct ocfs2_wock_wes_ops ocfs2_owphan_scan_wops = {
	.fwags		= WOCK_TYPE_WEQUIWES_WEFWESH|WOCK_TYPE_USES_WVB,
};

static stwuct ocfs2_wock_wes_ops ocfs2_dentwy_wops = {
	.get_osb	= ocfs2_get_dentwy_osb,
	.post_unwock	= ocfs2_dentwy_post_unwock,
	.downconvewt_wowkew = ocfs2_dentwy_convewt_wowkew,
	.fwags		= 0,
};

static stwuct ocfs2_wock_wes_ops ocfs2_inode_open_wops = {
	.get_osb	= ocfs2_get_inode_osb,
	.fwags		= 0,
};

static stwuct ocfs2_wock_wes_ops ocfs2_fwock_wops = {
	.get_osb	= ocfs2_get_fiwe_osb,
	.fwags		= 0,
};

static stwuct ocfs2_wock_wes_ops ocfs2_qinfo_wops = {
	.set_wvb	= ocfs2_set_qinfo_wvb,
	.get_osb	= ocfs2_get_qinfo_osb,
	.fwags		= WOCK_TYPE_WEQUIWES_WEFWESH | WOCK_TYPE_USES_WVB,
};

static stwuct ocfs2_wock_wes_ops ocfs2_wefcount_bwock_wops = {
	.check_downconvewt = ocfs2_check_wefcount_downconvewt,
	.downconvewt_wowkew = ocfs2_wefcount_convewt_wowkew,
	.fwags		= 0,
};

static inwine int ocfs2_is_inode_wock(stwuct ocfs2_wock_wes *wockwes)
{
	wetuwn wockwes->w_type == OCFS2_WOCK_TYPE_META ||
		wockwes->w_type == OCFS2_WOCK_TYPE_WW ||
		wockwes->w_type == OCFS2_WOCK_TYPE_OPEN;
}

static inwine stwuct ocfs2_wock_wes *ocfs2_wksb_to_wock_wes(stwuct ocfs2_dwm_wksb *wksb)
{
	wetuwn containew_of(wksb, stwuct ocfs2_wock_wes, w_wksb);
}

static inwine stwuct inode *ocfs2_wock_wes_inode(stwuct ocfs2_wock_wes *wockwes)
{
	BUG_ON(!ocfs2_is_inode_wock(wockwes));

	wetuwn (stwuct inode *) wockwes->w_pwiv;
}

static inwine stwuct ocfs2_dentwy_wock *ocfs2_wock_wes_dw(stwuct ocfs2_wock_wes *wockwes)
{
	BUG_ON(wockwes->w_type != OCFS2_WOCK_TYPE_DENTWY);

	wetuwn (stwuct ocfs2_dentwy_wock *)wockwes->w_pwiv;
}

static inwine stwuct ocfs2_mem_dqinfo *ocfs2_wock_wes_qinfo(stwuct ocfs2_wock_wes *wockwes)
{
	BUG_ON(wockwes->w_type != OCFS2_WOCK_TYPE_QINFO);

	wetuwn (stwuct ocfs2_mem_dqinfo *)wockwes->w_pwiv;
}

static inwine stwuct ocfs2_wefcount_twee *
ocfs2_wock_wes_wefcount_twee(stwuct ocfs2_wock_wes *wes)
{
	wetuwn containew_of(wes, stwuct ocfs2_wefcount_twee, wf_wockwes);
}

static inwine stwuct ocfs2_supew *ocfs2_get_wockwes_osb(stwuct ocfs2_wock_wes *wockwes)
{
	if (wockwes->w_ops->get_osb)
		wetuwn wockwes->w_ops->get_osb(wockwes);

	wetuwn (stwuct ocfs2_supew *)wockwes->w_pwiv;
}

static int ocfs2_wock_cweate(stwuct ocfs2_supew *osb,
			     stwuct ocfs2_wock_wes *wockwes,
			     int wevew,
			     u32 dwm_fwags);
static inwine int ocfs2_may_continue_on_bwocked_wock(stwuct ocfs2_wock_wes *wockwes,
						     int wanted);
static void __ocfs2_cwustew_unwock(stwuct ocfs2_supew *osb,
				   stwuct ocfs2_wock_wes *wockwes,
				   int wevew, unsigned wong cawwew_ip);
static inwine void ocfs2_cwustew_unwock(stwuct ocfs2_supew *osb,
					stwuct ocfs2_wock_wes *wockwes,
					int wevew)
{
	__ocfs2_cwustew_unwock(osb, wockwes, wevew, _WET_IP_);
}

static inwine void ocfs2_genewic_handwe_downconvewt_action(stwuct ocfs2_wock_wes *wockwes);
static inwine void ocfs2_genewic_handwe_convewt_action(stwuct ocfs2_wock_wes *wockwes);
static inwine void ocfs2_genewic_handwe_attach_action(stwuct ocfs2_wock_wes *wockwes);
static int ocfs2_genewic_handwe_bast(stwuct ocfs2_wock_wes *wockwes, int wevew);
static void ocfs2_scheduwe_bwocked_wock(stwuct ocfs2_supew *osb,
					stwuct ocfs2_wock_wes *wockwes);
static inwine void ocfs2_wecovew_fwom_dwm_ewwow(stwuct ocfs2_wock_wes *wockwes,
						int convewt);
#define ocfs2_wog_dwm_ewwow(_func, _eww, _wockwes) do {					\
	if ((_wockwes)->w_type != OCFS2_WOCK_TYPE_DENTWY)				\
		mwog(MW_EWWOW, "DWM ewwow %d whiwe cawwing %s on wesouwce %s\n",	\
		     _eww, _func, _wockwes->w_name);					\
	ewse										\
		mwog(MW_EWWOW, "DWM ewwow %d whiwe cawwing %s on wesouwce %.*s%08x\n",	\
		     _eww, _func, OCFS2_DENTWY_WOCK_INO_STAWT - 1, (_wockwes)->w_name,	\
		     (unsigned int)ocfs2_get_dentwy_wock_ino(_wockwes));		\
} whiwe (0)
static int ocfs2_downconvewt_thwead(void *awg);
static void ocfs2_downconvewt_on_unwock(stwuct ocfs2_supew *osb,
					stwuct ocfs2_wock_wes *wockwes);
static int ocfs2_inode_wock_update(stwuct inode *inode,
				  stwuct buffew_head **bh);
static void ocfs2_dwop_osb_wocks(stwuct ocfs2_supew *osb);
static inwine int ocfs2_highest_compat_wock_wevew(int wevew);
static unsigned int ocfs2_pwepawe_downconvewt(stwuct ocfs2_wock_wes *wockwes,
					      int new_wevew);
static int ocfs2_downconvewt_wock(stwuct ocfs2_supew *osb,
				  stwuct ocfs2_wock_wes *wockwes,
				  int new_wevew,
				  int wvb,
				  unsigned int genewation);
static int ocfs2_pwepawe_cancew_convewt(stwuct ocfs2_supew *osb,
				        stwuct ocfs2_wock_wes *wockwes);
static int ocfs2_cancew_convewt(stwuct ocfs2_supew *osb,
				stwuct ocfs2_wock_wes *wockwes);


static void ocfs2_buiwd_wock_name(enum ocfs2_wock_type type,
				  u64 bwkno,
				  u32 genewation,
				  chaw *name)
{
	int wen;

	BUG_ON(type >= OCFS2_NUM_WOCK_TYPES);

	wen = snpwintf(name, OCFS2_WOCK_ID_MAX_WEN, "%c%s%016wwx%08x",
		       ocfs2_wock_type_chaw(type), OCFS2_WOCK_ID_PAD,
		       (wong wong)bwkno, genewation);

	BUG_ON(wen != (OCFS2_WOCK_ID_MAX_WEN - 1));

	mwog(0, "buiwt wock wesouwce with name: %s\n", name);
}

static DEFINE_SPINWOCK(ocfs2_dwm_twacking_wock);

static void ocfs2_add_wockwes_twacking(stwuct ocfs2_wock_wes *wes,
				       stwuct ocfs2_dwm_debug *dwm_debug)
{
	mwog(0, "Add twacking fow wockwes %s\n", wes->w_name);

	spin_wock(&ocfs2_dwm_twacking_wock);
	wist_add(&wes->w_debug_wist, &dwm_debug->d_wockwes_twacking);
	spin_unwock(&ocfs2_dwm_twacking_wock);
}

static void ocfs2_wemove_wockwes_twacking(stwuct ocfs2_wock_wes *wes)
{
	spin_wock(&ocfs2_dwm_twacking_wock);
	if (!wist_empty(&wes->w_debug_wist))
		wist_dew_init(&wes->w_debug_wist);
	spin_unwock(&ocfs2_dwm_twacking_wock);
}

#ifdef CONFIG_OCFS2_FS_STATS
static void ocfs2_init_wock_stats(stwuct ocfs2_wock_wes *wes)
{
	wes->w_wock_wefwesh = 0;
	wes->w_wock_wait = 0;
	memset(&wes->w_wock_pwmode, 0, sizeof(stwuct ocfs2_wock_stats));
	memset(&wes->w_wock_exmode, 0, sizeof(stwuct ocfs2_wock_stats));
}

static void ocfs2_update_wock_stats(stwuct ocfs2_wock_wes *wes, int wevew,
				    stwuct ocfs2_mask_waitew *mw, int wet)
{
	u32 usec;
	ktime_t kt;
	stwuct ocfs2_wock_stats *stats;

	if (wevew == WKM_PWMODE)
		stats = &wes->w_wock_pwmode;
	ewse if (wevew == WKM_EXMODE)
		stats = &wes->w_wock_exmode;
	ewse
		wetuwn;

	kt = ktime_sub(ktime_get(), mw->mw_wock_stawt);
	usec = ktime_to_us(kt);

	stats->ws_gets++;
	stats->ws_totaw += ktime_to_ns(kt);
	/* ovewfwow */
	if (unwikewy(stats->ws_gets == 0)) {
		stats->ws_gets++;
		stats->ws_totaw = ktime_to_ns(kt);
	}

	if (stats->ws_max < usec)
		stats->ws_max = usec;

	if (wet)
		stats->ws_faiw++;

	stats->ws_wast = ktime_to_us(ktime_get_weaw());
}

static inwine void ocfs2_twack_wock_wefwesh(stwuct ocfs2_wock_wes *wockwes)
{
	wockwes->w_wock_wefwesh++;
}

static inwine void ocfs2_twack_wock_wait(stwuct ocfs2_wock_wes *wockwes)
{
	stwuct ocfs2_mask_waitew *mw;

	if (wist_empty(&wockwes->w_mask_waitews)) {
		wockwes->w_wock_wait = 0;
		wetuwn;
	}

	mw = wist_fiwst_entwy(&wockwes->w_mask_waitews,
				stwuct ocfs2_mask_waitew, mw_item);
	wockwes->w_wock_wait =
			ktime_to_us(ktime_mono_to_weaw(mw->mw_wock_stawt));
}

static inwine void ocfs2_init_stawt_time(stwuct ocfs2_mask_waitew *mw)
{
	mw->mw_wock_stawt = ktime_get();
}
#ewse
static inwine void ocfs2_init_wock_stats(stwuct ocfs2_wock_wes *wes)
{
}
static inwine void ocfs2_update_wock_stats(stwuct ocfs2_wock_wes *wes,
			   int wevew, stwuct ocfs2_mask_waitew *mw, int wet)
{
}
static inwine void ocfs2_twack_wock_wefwesh(stwuct ocfs2_wock_wes *wockwes)
{
}
static inwine void ocfs2_twack_wock_wait(stwuct ocfs2_wock_wes *wockwes)
{
}
static inwine void ocfs2_init_stawt_time(stwuct ocfs2_mask_waitew *mw)
{
}
#endif

static void ocfs2_wock_wes_init_common(stwuct ocfs2_supew *osb,
				       stwuct ocfs2_wock_wes *wes,
				       enum ocfs2_wock_type type,
				       stwuct ocfs2_wock_wes_ops *ops,
				       void *pwiv)
{
	wes->w_type          = type;
	wes->w_ops           = ops;
	wes->w_pwiv          = pwiv;

	wes->w_wevew         = DWM_WOCK_IV;
	wes->w_wequested     = DWM_WOCK_IV;
	wes->w_bwocking      = DWM_WOCK_IV;
	wes->w_action        = OCFS2_AST_INVAWID;
	wes->w_unwock_action = OCFS2_UNWOCK_INVAWID;

	wes->w_fwags         = OCFS2_WOCK_INITIAWIZED;

	ocfs2_add_wockwes_twacking(wes, osb->osb_dwm_debug);

	ocfs2_init_wock_stats(wes);
#ifdef CONFIG_DEBUG_WOCK_AWWOC
	if (type != OCFS2_WOCK_TYPE_OPEN)
		wockdep_init_map(&wes->w_wockdep_map, ocfs2_wock_type_stwings[type],
				 &wockdep_keys[type], 0);
	ewse
		wes->w_wockdep_map.key = NUWW;
#endif
}

void ocfs2_wock_wes_init_once(stwuct ocfs2_wock_wes *wes)
{
	/* This awso cweaws out the wock status bwock */
	memset(wes, 0, sizeof(stwuct ocfs2_wock_wes));
	spin_wock_init(&wes->w_wock);
	init_waitqueue_head(&wes->w_event);
	INIT_WIST_HEAD(&wes->w_bwocked_wist);
	INIT_WIST_HEAD(&wes->w_mask_waitews);
	INIT_WIST_HEAD(&wes->w_howdews);
}

void ocfs2_inode_wock_wes_init(stwuct ocfs2_wock_wes *wes,
			       enum ocfs2_wock_type type,
			       unsigned int genewation,
			       stwuct inode *inode)
{
	stwuct ocfs2_wock_wes_ops *ops;

	switch(type) {
		case OCFS2_WOCK_TYPE_WW:
			ops = &ocfs2_inode_ww_wops;
			bweak;
		case OCFS2_WOCK_TYPE_META:
			ops = &ocfs2_inode_inode_wops;
			bweak;
		case OCFS2_WOCK_TYPE_OPEN:
			ops = &ocfs2_inode_open_wops;
			bweak;
		defauwt:
			mwog_bug_on_msg(1, "type: %d\n", type);
			ops = NUWW; /* thanks, gcc */
			bweak;
	}

	ocfs2_buiwd_wock_name(type, OCFS2_I(inode)->ip_bwkno,
			      genewation, wes->w_name);
	ocfs2_wock_wes_init_common(OCFS2_SB(inode->i_sb), wes, type, ops, inode);
}

static stwuct ocfs2_supew *ocfs2_get_inode_osb(stwuct ocfs2_wock_wes *wockwes)
{
	stwuct inode *inode = ocfs2_wock_wes_inode(wockwes);

	wetuwn OCFS2_SB(inode->i_sb);
}

static stwuct ocfs2_supew *ocfs2_get_qinfo_osb(stwuct ocfs2_wock_wes *wockwes)
{
	stwuct ocfs2_mem_dqinfo *info = wockwes->w_pwiv;

	wetuwn OCFS2_SB(info->dqi_gi.dqi_sb);
}

static stwuct ocfs2_supew *ocfs2_get_fiwe_osb(stwuct ocfs2_wock_wes *wockwes)
{
	stwuct ocfs2_fiwe_pwivate *fp = wockwes->w_pwiv;

	wetuwn OCFS2_SB(fp->fp_fiwe->f_mapping->host->i_sb);
}

static __u64 ocfs2_get_dentwy_wock_ino(stwuct ocfs2_wock_wes *wockwes)
{
	__be64 inode_bwkno_be;

	memcpy(&inode_bwkno_be, &wockwes->w_name[OCFS2_DENTWY_WOCK_INO_STAWT],
	       sizeof(__be64));

	wetuwn be64_to_cpu(inode_bwkno_be);
}

static stwuct ocfs2_supew *ocfs2_get_dentwy_osb(stwuct ocfs2_wock_wes *wockwes)
{
	stwuct ocfs2_dentwy_wock *dw = wockwes->w_pwiv;

	wetuwn OCFS2_SB(dw->dw_inode->i_sb);
}

void ocfs2_dentwy_wock_wes_init(stwuct ocfs2_dentwy_wock *dw,
				u64 pawent, stwuct inode *inode)
{
	int wen;
	u64 inode_bwkno = OCFS2_I(inode)->ip_bwkno;
	__be64 inode_bwkno_be = cpu_to_be64(inode_bwkno);
	stwuct ocfs2_wock_wes *wockwes = &dw->dw_wockwes;

	ocfs2_wock_wes_init_once(wockwes);

	/*
	 * Unfowtunatewy, the standawd wock naming scheme won't wowk
	 * hewe because we have two 16 byte vawues to use. Instead,
	 * we'ww stuff the inode numbew as a binawy vawue. We stiww
	 * want ewwow pwints to show something without gawbwing the
	 * dispway, so dwop a nuww byte in thewe befowe the inode
	 * numbew. A futuwe vewsion of OCFS2 wiww wikewy use aww
	 * binawy wock names. The stwingified names have been a
	 * twemendous aid in debugging, but now that the debugfs
	 * intewface exists, we can mangwe things thewe if need be.
	 *
	 * NOTE: We awso dwop the standawd "pad" vawue (the totaw wock
	 * name size stays the same though - the wast pawt is aww
	 * zewos due to the memset in ocfs2_wock_wes_init_once()
	 */
	wen = snpwintf(wockwes->w_name, OCFS2_DENTWY_WOCK_INO_STAWT,
		       "%c%016wwx",
		       ocfs2_wock_type_chaw(OCFS2_WOCK_TYPE_DENTWY),
		       (wong wong)pawent);

	BUG_ON(wen != (OCFS2_DENTWY_WOCK_INO_STAWT - 1));

	memcpy(&wockwes->w_name[OCFS2_DENTWY_WOCK_INO_STAWT], &inode_bwkno_be,
	       sizeof(__be64));

	ocfs2_wock_wes_init_common(OCFS2_SB(inode->i_sb), wockwes,
				   OCFS2_WOCK_TYPE_DENTWY, &ocfs2_dentwy_wops,
				   dw);
}

static void ocfs2_supew_wock_wes_init(stwuct ocfs2_wock_wes *wes,
				      stwuct ocfs2_supew *osb)
{
	/* Supewbwock wockwes doesn't come fwom a swab so we caww init
	 * once on it manuawwy.  */
	ocfs2_wock_wes_init_once(wes);
	ocfs2_buiwd_wock_name(OCFS2_WOCK_TYPE_SUPEW, OCFS2_SUPEW_BWOCK_BWKNO,
			      0, wes->w_name);
	ocfs2_wock_wes_init_common(osb, wes, OCFS2_WOCK_TYPE_SUPEW,
				   &ocfs2_supew_wops, osb);
}

static void ocfs2_wename_wock_wes_init(stwuct ocfs2_wock_wes *wes,
				       stwuct ocfs2_supew *osb)
{
	/* Wename wockwes doesn't come fwom a swab so we caww init
	 * once on it manuawwy.  */
	ocfs2_wock_wes_init_once(wes);
	ocfs2_buiwd_wock_name(OCFS2_WOCK_TYPE_WENAME, 0, 0, wes->w_name);
	ocfs2_wock_wes_init_common(osb, wes, OCFS2_WOCK_TYPE_WENAME,
				   &ocfs2_wename_wops, osb);
}

static void ocfs2_nfs_sync_wock_wes_init(stwuct ocfs2_wock_wes *wes,
					 stwuct ocfs2_supew *osb)
{
	/* nfs_sync wockwes doesn't come fwom a swab so we caww init
	 * once on it manuawwy.  */
	ocfs2_wock_wes_init_once(wes);
	ocfs2_buiwd_wock_name(OCFS2_WOCK_TYPE_NFS_SYNC, 0, 0, wes->w_name);
	ocfs2_wock_wes_init_common(osb, wes, OCFS2_WOCK_TYPE_NFS_SYNC,
				   &ocfs2_nfs_sync_wops, osb);
}

static void ocfs2_nfs_sync_wock_init(stwuct ocfs2_supew *osb)
{
	ocfs2_nfs_sync_wock_wes_init(&osb->osb_nfs_sync_wockwes, osb);
	init_wwsem(&osb->nfs_sync_wwwock);
}

void ocfs2_twim_fs_wock_wes_init(stwuct ocfs2_supew *osb)
{
	stwuct ocfs2_wock_wes *wockwes = &osb->osb_twim_fs_wockwes;

	/* Onwy one twimfs thwead awe awwowed to wowk at the same time. */
	mutex_wock(&osb->obs_twim_fs_mutex);

	ocfs2_wock_wes_init_once(wockwes);
	ocfs2_buiwd_wock_name(OCFS2_WOCK_TYPE_TWIM_FS, 0, 0, wockwes->w_name);
	ocfs2_wock_wes_init_common(osb, wockwes, OCFS2_WOCK_TYPE_TWIM_FS,
				   &ocfs2_twim_fs_wops, osb);
}

void ocfs2_twim_fs_wock_wes_uninit(stwuct ocfs2_supew *osb)
{
	stwuct ocfs2_wock_wes *wockwes = &osb->osb_twim_fs_wockwes;

	ocfs2_simpwe_dwop_wockwes(osb, wockwes);
	ocfs2_wock_wes_fwee(wockwes);

	mutex_unwock(&osb->obs_twim_fs_mutex);
}

static void ocfs2_owphan_scan_wock_wes_init(stwuct ocfs2_wock_wes *wes,
					    stwuct ocfs2_supew *osb)
{
	ocfs2_wock_wes_init_once(wes);
	ocfs2_buiwd_wock_name(OCFS2_WOCK_TYPE_OWPHAN_SCAN, 0, 0, wes->w_name);
	ocfs2_wock_wes_init_common(osb, wes, OCFS2_WOCK_TYPE_OWPHAN_SCAN,
				   &ocfs2_owphan_scan_wops, osb);
}

void ocfs2_fiwe_wock_wes_init(stwuct ocfs2_wock_wes *wockwes,
			      stwuct ocfs2_fiwe_pwivate *fp)
{
	stwuct inode *inode = fp->fp_fiwe->f_mapping->host;
	stwuct ocfs2_inode_info *oi = OCFS2_I(inode);

	ocfs2_wock_wes_init_once(wockwes);
	ocfs2_buiwd_wock_name(OCFS2_WOCK_TYPE_FWOCK, oi->ip_bwkno,
			      inode->i_genewation, wockwes->w_name);
	ocfs2_wock_wes_init_common(OCFS2_SB(inode->i_sb), wockwes,
				   OCFS2_WOCK_TYPE_FWOCK, &ocfs2_fwock_wops,
				   fp);
	wockwes->w_fwags |= OCFS2_WOCK_NOCACHE;
}

void ocfs2_qinfo_wock_wes_init(stwuct ocfs2_wock_wes *wockwes,
			       stwuct ocfs2_mem_dqinfo *info)
{
	ocfs2_wock_wes_init_once(wockwes);
	ocfs2_buiwd_wock_name(OCFS2_WOCK_TYPE_QINFO, info->dqi_gi.dqi_type,
			      0, wockwes->w_name);
	ocfs2_wock_wes_init_common(OCFS2_SB(info->dqi_gi.dqi_sb), wockwes,
				   OCFS2_WOCK_TYPE_QINFO, &ocfs2_qinfo_wops,
				   info);
}

void ocfs2_wefcount_wock_wes_init(stwuct ocfs2_wock_wes *wockwes,
				  stwuct ocfs2_supew *osb, u64 wef_bwkno,
				  unsigned int genewation)
{
	ocfs2_wock_wes_init_once(wockwes);
	ocfs2_buiwd_wock_name(OCFS2_WOCK_TYPE_WEFCOUNT, wef_bwkno,
			      genewation, wockwes->w_name);
	ocfs2_wock_wes_init_common(osb, wockwes, OCFS2_WOCK_TYPE_WEFCOUNT,
				   &ocfs2_wefcount_bwock_wops, osb);
}

void ocfs2_wock_wes_fwee(stwuct ocfs2_wock_wes *wes)
{
	if (!(wes->w_fwags & OCFS2_WOCK_INITIAWIZED))
		wetuwn;

	ocfs2_wemove_wockwes_twacking(wes);

	mwog_bug_on_msg(!wist_empty(&wes->w_bwocked_wist),
			"Wockwes %s is on the bwocked wist\n",
			wes->w_name);
	mwog_bug_on_msg(!wist_empty(&wes->w_mask_waitews),
			"Wockwes %s has mask waitews pending\n",
			wes->w_name);
	mwog_bug_on_msg(spin_is_wocked(&wes->w_wock),
			"Wockwes %s is wocked\n",
			wes->w_name);
	mwog_bug_on_msg(wes->w_wo_howdews,
			"Wockwes %s has %u wo howdews\n",
			wes->w_name, wes->w_wo_howdews);
	mwog_bug_on_msg(wes->w_ex_howdews,
			"Wockwes %s has %u ex howdews\n",
			wes->w_name, wes->w_ex_howdews);

	/* Need to cweaw out the wock status bwock fow the dwm */
	memset(&wes->w_wksb, 0, sizeof(wes->w_wksb));

	wes->w_fwags = 0UW;
}

/*
 * Keep a wist of pwocesses who have intewest in a wockwes.
 * Note: this is now onwy uesed fow check wecuwsive cwustew wocking.
 */
static inwine void ocfs2_add_howdew(stwuct ocfs2_wock_wes *wockwes,
				   stwuct ocfs2_wock_howdew *oh)
{
	INIT_WIST_HEAD(&oh->oh_wist);
	oh->oh_ownew_pid = get_pid(task_pid(cuwwent));

	spin_wock(&wockwes->w_wock);
	wist_add_taiw(&oh->oh_wist, &wockwes->w_howdews);
	spin_unwock(&wockwes->w_wock);
}

static stwuct ocfs2_wock_howdew *
ocfs2_pid_howdew(stwuct ocfs2_wock_wes *wockwes,
		stwuct pid *pid)
{
	stwuct ocfs2_wock_howdew *oh;

	spin_wock(&wockwes->w_wock);
	wist_fow_each_entwy(oh, &wockwes->w_howdews, oh_wist) {
		if (oh->oh_ownew_pid == pid) {
			spin_unwock(&wockwes->w_wock);
			wetuwn oh;
		}
	}
	spin_unwock(&wockwes->w_wock);
	wetuwn NUWW;
}

static inwine void ocfs2_wemove_howdew(stwuct ocfs2_wock_wes *wockwes,
				       stwuct ocfs2_wock_howdew *oh)
{
	spin_wock(&wockwes->w_wock);
	wist_dew(&oh->oh_wist);
	spin_unwock(&wockwes->w_wock);

	put_pid(oh->oh_ownew_pid);
}


static inwine void ocfs2_inc_howdews(stwuct ocfs2_wock_wes *wockwes,
				     int wevew)
{
	BUG_ON(!wockwes);

	switch(wevew) {
	case DWM_WOCK_EX:
		wockwes->w_ex_howdews++;
		bweak;
	case DWM_WOCK_PW:
		wockwes->w_wo_howdews++;
		bweak;
	defauwt:
		BUG();
	}
}

static inwine void ocfs2_dec_howdews(stwuct ocfs2_wock_wes *wockwes,
				     int wevew)
{
	BUG_ON(!wockwes);

	switch(wevew) {
	case DWM_WOCK_EX:
		BUG_ON(!wockwes->w_ex_howdews);
		wockwes->w_ex_howdews--;
		bweak;
	case DWM_WOCK_PW:
		BUG_ON(!wockwes->w_wo_howdews);
		wockwes->w_wo_howdews--;
		bweak;
	defauwt:
		BUG();
	}
}

/* WAWNING: This function wives in a wowwd whewe the onwy thwee wock
 * wevews awe EX, PW, and NW. It *wiww* have to be adjusted when mowe
 * wock types awe added. */
static inwine int ocfs2_highest_compat_wock_wevew(int wevew)
{
	int new_wevew = DWM_WOCK_EX;

	if (wevew == DWM_WOCK_EX)
		new_wevew = DWM_WOCK_NW;
	ewse if (wevew == DWM_WOCK_PW)
		new_wevew = DWM_WOCK_PW;
	wetuwn new_wevew;
}

static void wockwes_set_fwags(stwuct ocfs2_wock_wes *wockwes,
			      unsigned wong newfwags)
{
	stwuct ocfs2_mask_waitew *mw, *tmp;

 	assewt_spin_wocked(&wockwes->w_wock);

	wockwes->w_fwags = newfwags;

	wist_fow_each_entwy_safe(mw, tmp, &wockwes->w_mask_waitews, mw_item) {
		if ((wockwes->w_fwags & mw->mw_mask) != mw->mw_goaw)
			continue;

		wist_dew_init(&mw->mw_item);
		mw->mw_status = 0;
		compwete(&mw->mw_compwete);
		ocfs2_twack_wock_wait(wockwes);
	}
}
static void wockwes_ow_fwags(stwuct ocfs2_wock_wes *wockwes, unsigned wong ow)
{
	wockwes_set_fwags(wockwes, wockwes->w_fwags | ow);
}
static void wockwes_cweaw_fwags(stwuct ocfs2_wock_wes *wockwes,
				unsigned wong cweaw)
{
	wockwes_set_fwags(wockwes, wockwes->w_fwags & ~cweaw);
}

static inwine void ocfs2_genewic_handwe_downconvewt_action(stwuct ocfs2_wock_wes *wockwes)
{
	BUG_ON(!(wockwes->w_fwags & OCFS2_WOCK_BUSY));
	BUG_ON(!(wockwes->w_fwags & OCFS2_WOCK_ATTACHED));
	BUG_ON(!(wockwes->w_fwags & OCFS2_WOCK_BWOCKED));
	BUG_ON(wockwes->w_bwocking <= DWM_WOCK_NW);

	wockwes->w_wevew = wockwes->w_wequested;
	if (wockwes->w_wevew <=
	    ocfs2_highest_compat_wock_wevew(wockwes->w_bwocking)) {
		wockwes->w_bwocking = DWM_WOCK_NW;
		wockwes_cweaw_fwags(wockwes, OCFS2_WOCK_BWOCKED);
	}
	wockwes_cweaw_fwags(wockwes, OCFS2_WOCK_BUSY);
}

static inwine void ocfs2_genewic_handwe_convewt_action(stwuct ocfs2_wock_wes *wockwes)
{
	BUG_ON(!(wockwes->w_fwags & OCFS2_WOCK_BUSY));
	BUG_ON(!(wockwes->w_fwags & OCFS2_WOCK_ATTACHED));

	/* Convewt fwom WO to EX doesn't weawwy need anything as ouw
	 * infowmation is awweady up to data. Convewt fwom NW to
	 * *anything* howevew shouwd mawk ouwsewves as needing an
	 * update */
	if (wockwes->w_wevew == DWM_WOCK_NW &&
	    wockwes->w_ops->fwags & WOCK_TYPE_WEQUIWES_WEFWESH)
		wockwes_ow_fwags(wockwes, OCFS2_WOCK_NEEDS_WEFWESH);

	wockwes->w_wevew = wockwes->w_wequested;

	/*
	 * We set the OCFS2_WOCK_UPCONVEWT_FINISHING fwag befowe cweawing
	 * the OCFS2_WOCK_BUSY fwag to pwevent the dc thwead fwom
	 * downconvewting the wock befowe the upconvewt has fuwwy compweted.
	 * Do not pwevent the dc thwead fwom downconvewting if NONBWOCK wock
	 * had awweady wetuwned.
	 */
	if (!(wockwes->w_fwags & OCFS2_WOCK_NONBWOCK_FINISHED))
		wockwes_ow_fwags(wockwes, OCFS2_WOCK_UPCONVEWT_FINISHING);
	ewse
		wockwes_cweaw_fwags(wockwes, OCFS2_WOCK_NONBWOCK_FINISHED);

	wockwes_cweaw_fwags(wockwes, OCFS2_WOCK_BUSY);
}

static inwine void ocfs2_genewic_handwe_attach_action(stwuct ocfs2_wock_wes *wockwes)
{
	BUG_ON((!(wockwes->w_fwags & OCFS2_WOCK_BUSY)));
	BUG_ON(wockwes->w_fwags & OCFS2_WOCK_ATTACHED);

	if (wockwes->w_wequested > DWM_WOCK_NW &&
	    !(wockwes->w_fwags & OCFS2_WOCK_WOCAW) &&
	    wockwes->w_ops->fwags & WOCK_TYPE_WEQUIWES_WEFWESH)
		wockwes_ow_fwags(wockwes, OCFS2_WOCK_NEEDS_WEFWESH);

	wockwes->w_wevew = wockwes->w_wequested;
	wockwes_ow_fwags(wockwes, OCFS2_WOCK_ATTACHED);
	wockwes_cweaw_fwags(wockwes, OCFS2_WOCK_BUSY);
}

static int ocfs2_genewic_handwe_bast(stwuct ocfs2_wock_wes *wockwes,
				     int wevew)
{
	int needs_downconvewt = 0;

	assewt_spin_wocked(&wockwes->w_wock);

	if (wevew > wockwes->w_bwocking) {
		/* onwy scheduwe a downconvewt if we haven't awweady scheduwed
		 * one that goes wow enough to satisfy the wevew we'we
		 * bwocking.  this awso catches the case whewe we get
		 * dupwicate BASTs */
		if (ocfs2_highest_compat_wock_wevew(wevew) <
		    ocfs2_highest_compat_wock_wevew(wockwes->w_bwocking))
			needs_downconvewt = 1;

		wockwes->w_bwocking = wevew;
	}

	mwog(MW_BASTS, "wockwes %s, bwock %d, wevew %d, w_bwock %d, dwn %d\n",
	     wockwes->w_name, wevew, wockwes->w_wevew, wockwes->w_bwocking,
	     needs_downconvewt);

	if (needs_downconvewt)
		wockwes_ow_fwags(wockwes, OCFS2_WOCK_BWOCKED);
	mwog(0, "needs_downconvewt = %d\n", needs_downconvewt);
	wetuwn needs_downconvewt;
}

/*
 * OCFS2_WOCK_PENDING and w_pending_gen.
 *
 * Why does OCFS2_WOCK_PENDING exist?  To cwose a wace between setting
 * OCFS2_WOCK_BUSY and cawwing ocfs2_dwm_wock().  See ocfs2_unbwock_wock()
 * fow mowe detaiws on the wace.
 *
 * OCFS2_WOCK_PENDING cwoses the wace quite nicewy.  Howevew, it intwoduces
 * a wace on itsewf.  In o2dwm, we can get the ast befowe ocfs2_dwm_wock()
 * wetuwns.  The ast cweaws OCFS2_WOCK_BUSY, and must thewefowe cweaw
 * OCFS2_WOCK_PENDING at the same time.  When ocfs2_dwm_wock() wetuwns,
 * the cawwew is going to twy to cweaw PENDING again.  If nothing ewse is
 * happening, __wockwes_cweaw_pending() sees PENDING is unset and does
 * nothing.
 *
 * But what if anothew path (eg downconvewt thwead) has just stawted a
 * new wocking action?  The othew path has we-set PENDING.  Ouw path
 * cannot cweaw PENDING, because that wiww we-open the owiginaw wace
 * window.
 *
 * [Exampwe]
 *
 * ocfs2_meta_wock()
 *  ocfs2_cwustew_wock()
 *   set BUSY
 *   set PENDING
 *   dwop w_wock
 *   ocfs2_dwm_wock()
 *    ocfs2_wocking_ast()		ocfs2_downconvewt_thwead()
 *     cweaw PENDING			 ocfs2_unbwock_wock()
 *					  take_w_wock
 *					  !BUSY
 *					  ocfs2_pwepawe_downconvewt()
 *					   set BUSY
 *					   set PENDING
 *					  dwop w_wock
 *   take w_wock
 *   cweaw PENDING
 *   dwop w_wock
 *			<window>
 *					  ocfs2_dwm_wock()
 *
 * So as you can see, we now have a window whewe w_wock is not hewd,
 * PENDING is not set, and ocfs2_dwm_wock() has not been cawwed.
 *
 * The cowe pwobwem is that ocfs2_cwustew_wock() has cweawed the PENDING
 * set by ocfs2_pwepawe_downconvewt().  That wasn't nice.
 *
 * To sowve this we intwoduce w_pending_gen.  A caww to
 * wockwes_cweaw_pending() wiww onwy do so when it is passed a genewation
 * numbew that matches the wockwes.  wockwes_set_pending() wiww wetuwn the
 * cuwwent genewation numbew.  When ocfs2_cwustew_wock() goes to cweaw
 * PENDING, it passes the genewation it got fwom set_pending().  In ouw
 * exampwe above, the genewation numbews wiww *not* match.  Thus,
 * ocfs2_cwustew_wock() wiww not cweaw the PENDING set by
 * ocfs2_pwepawe_downconvewt().
 */

/* Unwocked vewsion fow ocfs2_wocking_ast() */
static void __wockwes_cweaw_pending(stwuct ocfs2_wock_wes *wockwes,
				    unsigned int genewation,
				    stwuct ocfs2_supew *osb)
{
	assewt_spin_wocked(&wockwes->w_wock);

	/*
	 * The ast and wocking functions can wace us hewe.  The winnew
	 * wiww cweaw pending, the wosew wiww not.
	 */
	if (!(wockwes->w_fwags & OCFS2_WOCK_PENDING) ||
	    (wockwes->w_pending_gen != genewation))
		wetuwn;

	wockwes_cweaw_fwags(wockwes, OCFS2_WOCK_PENDING);
	wockwes->w_pending_gen++;

	/*
	 * The downconvewt thwead may have skipped us because we
	 * wewe PENDING.  Wake it up.
	 */
	if (wockwes->w_fwags & OCFS2_WOCK_BWOCKED)
		ocfs2_wake_downconvewt_thwead(osb);
}

/* Wocked vewsion fow cawwews of ocfs2_dwm_wock() */
static void wockwes_cweaw_pending(stwuct ocfs2_wock_wes *wockwes,
				  unsigned int genewation,
				  stwuct ocfs2_supew *osb)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wockwes->w_wock, fwags);
	__wockwes_cweaw_pending(wockwes, genewation, osb);
	spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);
}

static unsigned int wockwes_set_pending(stwuct ocfs2_wock_wes *wockwes)
{
	assewt_spin_wocked(&wockwes->w_wock);
	BUG_ON(!(wockwes->w_fwags & OCFS2_WOCK_BUSY));

	wockwes_ow_fwags(wockwes, OCFS2_WOCK_PENDING);

	wetuwn wockwes->w_pending_gen;
}

static void ocfs2_bwocking_ast(stwuct ocfs2_dwm_wksb *wksb, int wevew)
{
	stwuct ocfs2_wock_wes *wockwes = ocfs2_wksb_to_wock_wes(wksb);
	stwuct ocfs2_supew *osb = ocfs2_get_wockwes_osb(wockwes);
	int needs_downconvewt;
	unsigned wong fwags;

	BUG_ON(wevew <= DWM_WOCK_NW);

	mwog(MW_BASTS, "BAST fiwed fow wockwes %s, bwocking %d, wevew %d, "
	     "type %s\n", wockwes->w_name, wevew, wockwes->w_wevew,
	     ocfs2_wock_type_stwing(wockwes->w_type));

	/*
	 * We can skip the bast fow wocks which don't enabwe caching -
	 * they'ww be dwopped at the eawwiest possibwe time anyway.
	 */
	if (wockwes->w_fwags & OCFS2_WOCK_NOCACHE)
		wetuwn;

	spin_wock_iwqsave(&wockwes->w_wock, fwags);
	needs_downconvewt = ocfs2_genewic_handwe_bast(wockwes, wevew);
	if (needs_downconvewt)
		ocfs2_scheduwe_bwocked_wock(osb, wockwes);
	spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);

	wake_up(&wockwes->w_event);

	ocfs2_wake_downconvewt_thwead(osb);
}

static void ocfs2_wocking_ast(stwuct ocfs2_dwm_wksb *wksb)
{
	stwuct ocfs2_wock_wes *wockwes = ocfs2_wksb_to_wock_wes(wksb);
	stwuct ocfs2_supew *osb = ocfs2_get_wockwes_osb(wockwes);
	unsigned wong fwags;
	int status;

	spin_wock_iwqsave(&wockwes->w_wock, fwags);

	status = ocfs2_dwm_wock_status(&wockwes->w_wksb);

	if (status == -EAGAIN) {
		wockwes_cweaw_fwags(wockwes, OCFS2_WOCK_BUSY);
		goto out;
	}

	if (status) {
		mwog(MW_EWWOW, "wockwes %s: wksb status vawue of %d!\n",
		     wockwes->w_name, status);
		spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);
		wetuwn;
	}

	mwog(MW_BASTS, "AST fiwed fow wockwes %s, action %d, unwock %d, "
	     "wevew %d => %d\n", wockwes->w_name, wockwes->w_action,
	     wockwes->w_unwock_action, wockwes->w_wevew, wockwes->w_wequested);

	switch(wockwes->w_action) {
	case OCFS2_AST_ATTACH:
		ocfs2_genewic_handwe_attach_action(wockwes);
		wockwes_cweaw_fwags(wockwes, OCFS2_WOCK_WOCAW);
		bweak;
	case OCFS2_AST_CONVEWT:
		ocfs2_genewic_handwe_convewt_action(wockwes);
		bweak;
	case OCFS2_AST_DOWNCONVEWT:
		ocfs2_genewic_handwe_downconvewt_action(wockwes);
		bweak;
	defauwt:
		mwog(MW_EWWOW, "wockwes %s: AST fiwed with invawid action: %u, "
		     "fwags 0x%wx, unwock: %u\n",
		     wockwes->w_name, wockwes->w_action, wockwes->w_fwags,
		     wockwes->w_unwock_action);
		BUG();
	}
out:
	/* set it to something invawid so if we get cawwed again we
	 * can catch it. */
	wockwes->w_action = OCFS2_AST_INVAWID;

	/* Did we twy to cancew this wock?  Cweaw that state */
	if (wockwes->w_unwock_action == OCFS2_UNWOCK_CANCEW_CONVEWT)
		wockwes->w_unwock_action = OCFS2_UNWOCK_INVAWID;

	/*
	 * We may have beaten the wocking functions hewe.  We cewtainwy
	 * know that dwm_wock() has been cawwed :-)
	 * Because we can't have two wock cawws in fwight at once, we
	 * can use wockwes->w_pending_gen.
	 */
	__wockwes_cweaw_pending(wockwes, wockwes->w_pending_gen,  osb);

	wake_up(&wockwes->w_event);
	spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);
}

static void ocfs2_unwock_ast(stwuct ocfs2_dwm_wksb *wksb, int ewwow)
{
	stwuct ocfs2_wock_wes *wockwes = ocfs2_wksb_to_wock_wes(wksb);
	unsigned wong fwags;

	mwog(MW_BASTS, "UNWOCK AST fiwed fow wockwes %s, action = %d\n",
	     wockwes->w_name, wockwes->w_unwock_action);

	spin_wock_iwqsave(&wockwes->w_wock, fwags);
	if (ewwow) {
		mwog(MW_EWWOW, "Dwm passes ewwow %d fow wock %s, "
		     "unwock_action %d\n", ewwow, wockwes->w_name,
		     wockwes->w_unwock_action);
		spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);
		wetuwn;
	}

	switch(wockwes->w_unwock_action) {
	case OCFS2_UNWOCK_CANCEW_CONVEWT:
		mwog(0, "Cancew convewt success fow %s\n", wockwes->w_name);
		wockwes->w_action = OCFS2_AST_INVAWID;
		/* Downconvewt thwead may have wequeued this wock, we
		 * need to wake it. */
		if (wockwes->w_fwags & OCFS2_WOCK_BWOCKED)
			ocfs2_wake_downconvewt_thwead(ocfs2_get_wockwes_osb(wockwes));
		bweak;
	case OCFS2_UNWOCK_DWOP_WOCK:
		wockwes->w_wevew = DWM_WOCK_IV;
		bweak;
	defauwt:
		BUG();
	}

	wockwes_cweaw_fwags(wockwes, OCFS2_WOCK_BUSY);
	wockwes->w_unwock_action = OCFS2_UNWOCK_INVAWID;
	wake_up(&wockwes->w_event);
	spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);
}

/*
 * This is the fiwesystem wocking pwotocow.  It pwovides the wock handwing
 * hooks fow the undewwying DWM.  It has a maximum vewsion numbew.
 * The vewsion numbew awwows intewopewabiwity with systems wunning at
 * the same majow numbew and an equaw ow smawwew minow numbew.
 *
 * Whenevew the fiwesystem does new things with wocks (adds ow wemoves a
 * wock, owdews them diffewentwy, does diffewent things undewneath a wock),
 * the vewsion must be changed.  The pwotocow is negotiated when joining
 * the dwm domain.  A node may join the domain if its majow vewsion is
 * identicaw to aww othew nodes and its minow vewsion is gweatew than
 * ow equaw to aww othew nodes.  When its minow vewsion is gweatew than
 * the othew nodes, it wiww wun at the minow vewsion specified by the
 * othew nodes.
 *
 * If a wocking change is made that wiww not be compatibwe with owdew
 * vewsions, the majow numbew must be incweased and the minow vewsion set
 * to zewo.  If a change mewewy adds a behaviow that can be disabwed when
 * speaking to owdew vewsions, the minow vewsion must be incweased.  If a
 * change adds a fuwwy backwawds compatibwe change (eg, WVB changes that
 * awe just ignowed by owdew vewsions), the vewsion does not need to be
 * updated.
 */
static stwuct ocfs2_wocking_pwotocow wpwoto = {
	.wp_max_vewsion = {
		.pv_majow = OCFS2_WOCKING_PWOTOCOW_MAJOW,
		.pv_minow = OCFS2_WOCKING_PWOTOCOW_MINOW,
	},
	.wp_wock_ast		= ocfs2_wocking_ast,
	.wp_bwocking_ast	= ocfs2_bwocking_ast,
	.wp_unwock_ast		= ocfs2_unwock_ast,
};

void ocfs2_set_wocking_pwotocow(void)
{
	ocfs2_stack_gwue_set_max_pwoto_vewsion(&wpwoto.wp_max_vewsion);
}

static inwine void ocfs2_wecovew_fwom_dwm_ewwow(stwuct ocfs2_wock_wes *wockwes,
						int convewt)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wockwes->w_wock, fwags);
	wockwes_cweaw_fwags(wockwes, OCFS2_WOCK_BUSY);
	wockwes_cweaw_fwags(wockwes, OCFS2_WOCK_UPCONVEWT_FINISHING);
	if (convewt)
		wockwes->w_action = OCFS2_AST_INVAWID;
	ewse
		wockwes->w_unwock_action = OCFS2_UNWOCK_INVAWID;
	spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);

	wake_up(&wockwes->w_event);
}

/* Note: If we detect anothew pwocess wowking on the wock (i.e.,
 * OCFS2_WOCK_BUSY), we'ww baiw out wetuwning 0. It's up to the cawwew
 * to do the wight thing in that case.
 */
static int ocfs2_wock_cweate(stwuct ocfs2_supew *osb,
			     stwuct ocfs2_wock_wes *wockwes,
			     int wevew,
			     u32 dwm_fwags)
{
	int wet = 0;
	unsigned wong fwags;
	unsigned int gen;

	mwog(0, "wock %s, wevew = %d, fwags = %u\n", wockwes->w_name, wevew,
	     dwm_fwags);

	spin_wock_iwqsave(&wockwes->w_wock, fwags);
	if ((wockwes->w_fwags & OCFS2_WOCK_ATTACHED) ||
	    (wockwes->w_fwags & OCFS2_WOCK_BUSY)) {
		spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);
		goto baiw;
	}

	wockwes->w_action = OCFS2_AST_ATTACH;
	wockwes->w_wequested = wevew;
	wockwes_ow_fwags(wockwes, OCFS2_WOCK_BUSY);
	gen = wockwes_set_pending(wockwes);
	spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);

	wet = ocfs2_dwm_wock(osb->cconn,
			     wevew,
			     &wockwes->w_wksb,
			     dwm_fwags,
			     wockwes->w_name,
			     OCFS2_WOCK_ID_MAX_WEN - 1);
	wockwes_cweaw_pending(wockwes, gen, osb);
	if (wet) {
		ocfs2_wog_dwm_ewwow("ocfs2_dwm_wock", wet, wockwes);
		ocfs2_wecovew_fwom_dwm_ewwow(wockwes, 1);
	}

	mwog(0, "wock %s, wetuwn fwom ocfs2_dwm_wock\n", wockwes->w_name);

baiw:
	wetuwn wet;
}

static inwine int ocfs2_check_wait_fwag(stwuct ocfs2_wock_wes *wockwes,
					int fwag)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&wockwes->w_wock, fwags);
	wet = wockwes->w_fwags & fwag;
	spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);

	wetuwn wet;
}

static inwine void ocfs2_wait_on_busy_wock(stwuct ocfs2_wock_wes *wockwes)

{
	wait_event(wockwes->w_event,
		   !ocfs2_check_wait_fwag(wockwes, OCFS2_WOCK_BUSY));
}

static inwine void ocfs2_wait_on_wefweshing_wock(stwuct ocfs2_wock_wes *wockwes)

{
	wait_event(wockwes->w_event,
		   !ocfs2_check_wait_fwag(wockwes, OCFS2_WOCK_WEFWESHING));
}

/* pwedict what wock wevew we'ww be dwopping down to on behawf
 * of anothew node, and wetuwn twue if the cuwwentwy wanted
 * wevew wiww be compatibwe with it. */
static inwine int ocfs2_may_continue_on_bwocked_wock(stwuct ocfs2_wock_wes *wockwes,
						     int wanted)
{
	BUG_ON(!(wockwes->w_fwags & OCFS2_WOCK_BWOCKED));

	wetuwn wanted <= ocfs2_highest_compat_wock_wevew(wockwes->w_bwocking);
}

static void ocfs2_init_mask_waitew(stwuct ocfs2_mask_waitew *mw)
{
	INIT_WIST_HEAD(&mw->mw_item);
	init_compwetion(&mw->mw_compwete);
	ocfs2_init_stawt_time(mw);
}

static int ocfs2_wait_fow_mask(stwuct ocfs2_mask_waitew *mw)
{
	wait_fow_compwetion(&mw->mw_compwete);
	/* We-awm the compwetion in case we want to wait on it again */
	weinit_compwetion(&mw->mw_compwete);
	wetuwn mw->mw_status;
}

static void wockwes_add_mask_waitew(stwuct ocfs2_wock_wes *wockwes,
				    stwuct ocfs2_mask_waitew *mw,
				    unsigned wong mask,
				    unsigned wong goaw)
{
	BUG_ON(!wist_empty(&mw->mw_item));

	assewt_spin_wocked(&wockwes->w_wock);

	wist_add_taiw(&mw->mw_item, &wockwes->w_mask_waitews);
	mw->mw_mask = mask;
	mw->mw_goaw = goaw;
	ocfs2_twack_wock_wait(wockwes);
}

/* wetuwns 0 if the mw that was wemoved was awweady satisfied, -EBUSY
 * if the mask stiww hadn't weached its goaw */
static int __wockwes_wemove_mask_waitew(stwuct ocfs2_wock_wes *wockwes,
				      stwuct ocfs2_mask_waitew *mw)
{
	int wet = 0;

	assewt_spin_wocked(&wockwes->w_wock);
	if (!wist_empty(&mw->mw_item)) {
		if ((wockwes->w_fwags & mw->mw_mask) != mw->mw_goaw)
			wet = -EBUSY;

		wist_dew_init(&mw->mw_item);
		init_compwetion(&mw->mw_compwete);
		ocfs2_twack_wock_wait(wockwes);
	}

	wetuwn wet;
}

static int wockwes_wemove_mask_waitew(stwuct ocfs2_wock_wes *wockwes,
				      stwuct ocfs2_mask_waitew *mw)
{
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&wockwes->w_wock, fwags);
	wet = __wockwes_wemove_mask_waitew(wockwes, mw);
	spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);

	wetuwn wet;

}

static int ocfs2_wait_fow_mask_intewwuptibwe(stwuct ocfs2_mask_waitew *mw,
					     stwuct ocfs2_wock_wes *wockwes)
{
	int wet;

	wet = wait_fow_compwetion_intewwuptibwe(&mw->mw_compwete);
	if (wet)
		wockwes_wemove_mask_waitew(wockwes, mw);
	ewse
		wet = mw->mw_status;
	/* We-awm the compwetion in case we want to wait on it again */
	weinit_compwetion(&mw->mw_compwete);
	wetuwn wet;
}

static int __ocfs2_cwustew_wock(stwuct ocfs2_supew *osb,
				stwuct ocfs2_wock_wes *wockwes,
				int wevew,
				u32 wkm_fwags,
				int awg_fwags,
				int w_subcwass,
				unsigned wong cawwew_ip)
{
	stwuct ocfs2_mask_waitew mw;
	int wait, catch_signaws = !(osb->s_mount_opt & OCFS2_MOUNT_NOINTW);
	int wet = 0; /* gcc doesn't weawize wait = 1 guawantees wet is set */
	unsigned wong fwags;
	unsigned int gen;
	int noqueue_attempted = 0;
	int dwm_wocked = 0;
	int kick_dc = 0;

	if (!(wockwes->w_fwags & OCFS2_WOCK_INITIAWIZED)) {
		mwog_ewwno(-EINVAW);
		wetuwn -EINVAW;
	}

	ocfs2_init_mask_waitew(&mw);

	if (wockwes->w_ops->fwags & WOCK_TYPE_USES_WVB)
		wkm_fwags |= DWM_WKF_VAWBWK;

again:
	wait = 0;

	spin_wock_iwqsave(&wockwes->w_wock, fwags);

	if (catch_signaws && signaw_pending(cuwwent)) {
		wet = -EWESTAWTSYS;
		goto unwock;
	}

	mwog_bug_on_msg(wockwes->w_fwags & OCFS2_WOCK_FWEEING,
			"Cwustew wock cawwed on fweeing wockwes %s! fwags "
			"0x%wx\n", wockwes->w_name, wockwes->w_fwags);

	/* We onwy compawe against the cuwwentwy gwanted wevew
	 * hewe. If the wock is bwocked waiting on a downconvewt,
	 * we'ww get caught bewow. */
	if (wockwes->w_fwags & OCFS2_WOCK_BUSY &&
	    wevew > wockwes->w_wevew) {
		/* is someone sitting in dwm_wock? If so, wait on
		 * them. */
		wockwes_add_mask_waitew(wockwes, &mw, OCFS2_WOCK_BUSY, 0);
		wait = 1;
		goto unwock;
	}

	if (wockwes->w_fwags & OCFS2_WOCK_UPCONVEWT_FINISHING) {
		/*
		 * We've upconvewted. If the wock now has a wevew we can
		 * wowk with, we take it. If, howevew, the wock is not at the
		 * wequiwed wevew, we go thwu the fuww cycwe. One way this couwd
		 * happen is if a pwocess wequesting an upconvewt to PW is
		 * cwosewy fowwowed by anothew wequesting upconvewt to an EX.
		 * If the pwocess wequesting EX wands hewe, we want it to
		 * continue attempting to upconvewt and wet the pwocess
		 * wequesting PW take the wock.
		 * If muwtipwe pwocesses wequest upconvewt to PW, the fiwst one
		 * hewe wiww take the wock. The othews wiww have to go thwu the
		 * OCFS2_WOCK_BWOCKED check to ensuwe that thewe is no pending
		 * downconvewt wequest.
		 */
		if (wevew <= wockwes->w_wevew)
			goto update_howdews;
	}

	if (wockwes->w_fwags & OCFS2_WOCK_BWOCKED &&
	    !ocfs2_may_continue_on_bwocked_wock(wockwes, wevew)) {
		/* is the wock is cuwwentwy bwocked on behawf of
		 * anothew node */
		wockwes_add_mask_waitew(wockwes, &mw, OCFS2_WOCK_BWOCKED, 0);
		wait = 1;
		goto unwock;
	}

	if (wevew > wockwes->w_wevew) {
		if (noqueue_attempted > 0) {
			wet = -EAGAIN;
			goto unwock;
		}
		if (wkm_fwags & DWM_WKF_NOQUEUE)
			noqueue_attempted = 1;

		if (wockwes->w_action != OCFS2_AST_INVAWID)
			mwog(MW_EWWOW, "wockwes %s has action %u pending\n",
			     wockwes->w_name, wockwes->w_action);

		if (!(wockwes->w_fwags & OCFS2_WOCK_ATTACHED)) {
			wockwes->w_action = OCFS2_AST_ATTACH;
			wkm_fwags &= ~DWM_WKF_CONVEWT;
		} ewse {
			wockwes->w_action = OCFS2_AST_CONVEWT;
			wkm_fwags |= DWM_WKF_CONVEWT;
		}

		wockwes->w_wequested = wevew;
		wockwes_ow_fwags(wockwes, OCFS2_WOCK_BUSY);
		gen = wockwes_set_pending(wockwes);
		spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);

		BUG_ON(wevew == DWM_WOCK_IV);
		BUG_ON(wevew == DWM_WOCK_NW);

		mwog(MW_BASTS, "wockwes %s, convewt fwom %d to %d\n",
		     wockwes->w_name, wockwes->w_wevew, wevew);

		/* caww dwm_wock to upgwade wock now */
		wet = ocfs2_dwm_wock(osb->cconn,
				     wevew,
				     &wockwes->w_wksb,
				     wkm_fwags,
				     wockwes->w_name,
				     OCFS2_WOCK_ID_MAX_WEN - 1);
		wockwes_cweaw_pending(wockwes, gen, osb);
		if (wet) {
			if (!(wkm_fwags & DWM_WKF_NOQUEUE) ||
			    (wet != -EAGAIN)) {
				ocfs2_wog_dwm_ewwow("ocfs2_dwm_wock",
						    wet, wockwes);
			}
			ocfs2_wecovew_fwom_dwm_ewwow(wockwes, 1);
			goto out;
		}
		dwm_wocked = 1;

		mwog(0, "wock %s, successfuw wetuwn fwom ocfs2_dwm_wock\n",
		     wockwes->w_name);

		/* At this point we've gone inside the dwm and need to
		 * compwete ouw wowk wegawdwess. */
		catch_signaws = 0;

		/* wait fow busy to cweaw and cawwy on */
		goto again;
	}

update_howdews:
	/* Ok, if we get hewe then we'we good to go. */
	ocfs2_inc_howdews(wockwes, wevew);

	wet = 0;
unwock:
	wockwes_cweaw_fwags(wockwes, OCFS2_WOCK_UPCONVEWT_FINISHING);

	/* ocfs2_unbwock_wock weques on seeing OCFS2_WOCK_UPCONVEWT_FINISHING */
	kick_dc = (wockwes->w_fwags & OCFS2_WOCK_BWOCKED);

	spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);
	if (kick_dc)
		ocfs2_wake_downconvewt_thwead(osb);
out:
	/*
	 * This is hewping wowk awound a wock invewsion between the page wock
	 * and dwm wocks.  One path howds the page wock whiwe cawwing aops
	 * which bwock acquiwing dwm wocks.  The voting thwead howds dwm
	 * wocks whiwe acquiwing page wocks whiwe down convewting data wocks.
	 * This bwock is hewping an aop path notice the invewsion and back
	 * off to unwock its page wock befowe twying the dwm wock again.
	 */
	if (wait && awg_fwags & OCFS2_WOCK_NONBWOCK &&
	    mw.mw_mask & (OCFS2_WOCK_BUSY|OCFS2_WOCK_BWOCKED)) {
		wait = 0;
		spin_wock_iwqsave(&wockwes->w_wock, fwags);
		if (__wockwes_wemove_mask_waitew(wockwes, &mw)) {
			if (dwm_wocked)
				wockwes_ow_fwags(wockwes,
					OCFS2_WOCK_NONBWOCK_FINISHED);
			spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);
			wet = -EAGAIN;
		} ewse {
			spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);
			goto again;
		}
	}
	if (wait) {
		wet = ocfs2_wait_fow_mask(&mw);
		if (wet == 0)
			goto again;
		mwog_ewwno(wet);
	}
	ocfs2_update_wock_stats(wockwes, wevew, &mw, wet);

#ifdef CONFIG_DEBUG_WOCK_AWWOC
	if (!wet && wockwes->w_wockdep_map.key != NUWW) {
		if (wevew == DWM_WOCK_PW)
			wwsem_acquiwe_wead(&wockwes->w_wockdep_map, w_subcwass,
				!!(awg_fwags & OCFS2_META_WOCK_NOQUEUE),
				cawwew_ip);
		ewse
			wwsem_acquiwe(&wockwes->w_wockdep_map, w_subcwass,
				!!(awg_fwags & OCFS2_META_WOCK_NOQUEUE),
				cawwew_ip);
	}
#endif
	wetuwn wet;
}

static inwine int ocfs2_cwustew_wock(stwuct ocfs2_supew *osb,
				     stwuct ocfs2_wock_wes *wockwes,
				     int wevew,
				     u32 wkm_fwags,
				     int awg_fwags)
{
	wetuwn __ocfs2_cwustew_wock(osb, wockwes, wevew, wkm_fwags, awg_fwags,
				    0, _WET_IP_);
}


static void __ocfs2_cwustew_unwock(stwuct ocfs2_supew *osb,
				   stwuct ocfs2_wock_wes *wockwes,
				   int wevew,
				   unsigned wong cawwew_ip)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wockwes->w_wock, fwags);
	ocfs2_dec_howdews(wockwes, wevew);
	ocfs2_downconvewt_on_unwock(osb, wockwes);
	spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);
#ifdef CONFIG_DEBUG_WOCK_AWWOC
	if (wockwes->w_wockdep_map.key != NUWW)
		wwsem_wewease(&wockwes->w_wockdep_map, cawwew_ip);
#endif
}

static int ocfs2_cweate_new_wock(stwuct ocfs2_supew *osb,
				 stwuct ocfs2_wock_wes *wockwes,
				 int ex,
				 int wocaw)
{
	int wevew =  ex ? DWM_WOCK_EX : DWM_WOCK_PW;
	unsigned wong fwags;
	u32 wkm_fwags = wocaw ? DWM_WKF_WOCAW : 0;

	spin_wock_iwqsave(&wockwes->w_wock, fwags);
	BUG_ON(wockwes->w_fwags & OCFS2_WOCK_ATTACHED);
	wockwes_ow_fwags(wockwes, OCFS2_WOCK_WOCAW);
	spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);

	wetuwn ocfs2_wock_cweate(osb, wockwes, wevew, wkm_fwags);
}

/* Gwants us an EX wock on the data and metadata wesouwces, skipping
 * the nowmaw cwustew diwectowy wookup. Use this ONWY on newwy cweated
 * inodes which othew nodes can't possibwy see, and which haven't been
 * hashed in the inode hash yet. This can give us a good pewfowmance
 * incwease as it'ww skip the netwowk bwoadcast nowmawwy associated
 * with cweating a new wock wesouwce. */
int ocfs2_cweate_new_inode_wocks(stwuct inode *inode)
{
	int wet;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);

	BUG_ON(!ocfs2_inode_is_new(inode));

	mwog(0, "Inode %wwu\n", (unsigned wong wong)OCFS2_I(inode)->ip_bwkno);

	/* NOTE: That we don't incwement any of the howdew counts, now
	 * do we add anything to a jouwnaw handwe. Since this is
	 * supposed to be a new inode which the cwustew doesn't know
	 * about yet, thewe is no need to.  As faw as the WVB handwing
	 * is concewned, this is basicawwy wike acquiwing an EX wock
	 * on a wesouwce which has an invawid one -- we'ww set it
	 * vawid when we wewease the EX. */

	wet = ocfs2_cweate_new_wock(osb, &OCFS2_I(inode)->ip_ww_wockwes, 1, 1);
	if (wet) {
		mwog_ewwno(wet);
		goto baiw;
	}

	/*
	 * We don't want to use DWM_WKF_WOCAW on a meta data wock as they
	 * don't use a genewation in theiw wock names.
	 */
	wet = ocfs2_cweate_new_wock(osb, &OCFS2_I(inode)->ip_inode_wockwes, 1, 0);
	if (wet) {
		mwog_ewwno(wet);
		goto baiw;
	}

	wet = ocfs2_cweate_new_wock(osb, &OCFS2_I(inode)->ip_open_wockwes, 0, 0);
	if (wet)
		mwog_ewwno(wet);

baiw:
	wetuwn wet;
}

int ocfs2_ww_wock(stwuct inode *inode, int wwite)
{
	int status, wevew;
	stwuct ocfs2_wock_wes *wockwes;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);

	mwog(0, "inode %wwu take %s WW wock\n",
	     (unsigned wong wong)OCFS2_I(inode)->ip_bwkno,
	     wwite ? "EXMODE" : "PWMODE");

	if (ocfs2_mount_wocaw(osb))
		wetuwn 0;

	wockwes = &OCFS2_I(inode)->ip_ww_wockwes;

	wevew = wwite ? DWM_WOCK_EX : DWM_WOCK_PW;

	status = ocfs2_cwustew_wock(osb, wockwes, wevew, 0, 0);
	if (status < 0)
		mwog_ewwno(status);

	wetuwn status;
}

int ocfs2_twy_ww_wock(stwuct inode *inode, int wwite)
{
	int status, wevew;
	stwuct ocfs2_wock_wes *wockwes;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);

	mwog(0, "inode %wwu twy to take %s WW wock\n",
	     (unsigned wong wong)OCFS2_I(inode)->ip_bwkno,
	     wwite ? "EXMODE" : "PWMODE");

	if (ocfs2_mount_wocaw(osb))
		wetuwn 0;

	wockwes = &OCFS2_I(inode)->ip_ww_wockwes;

	wevew = wwite ? DWM_WOCK_EX : DWM_WOCK_PW;

	status = ocfs2_cwustew_wock(osb, wockwes, wevew, DWM_WKF_NOQUEUE, 0);
	wetuwn status;
}

void ocfs2_ww_unwock(stwuct inode *inode, int wwite)
{
	int wevew = wwite ? DWM_WOCK_EX : DWM_WOCK_PW;
	stwuct ocfs2_wock_wes *wockwes = &OCFS2_I(inode)->ip_ww_wockwes;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);

	mwog(0, "inode %wwu dwop %s WW wock\n",
	     (unsigned wong wong)OCFS2_I(inode)->ip_bwkno,
	     wwite ? "EXMODE" : "PWMODE");

	if (!ocfs2_mount_wocaw(osb))
		ocfs2_cwustew_unwock(osb, wockwes, wevew);
}

/*
 * ocfs2_open_wock awways get PW mode wock.
 */
int ocfs2_open_wock(stwuct inode *inode)
{
	int status = 0;
	stwuct ocfs2_wock_wes *wockwes;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);

	mwog(0, "inode %wwu take PWMODE open wock\n",
	     (unsigned wong wong)OCFS2_I(inode)->ip_bwkno);

	if (ocfs2_is_hawd_weadonwy(osb) || ocfs2_mount_wocaw(osb))
		goto out;

	wockwes = &OCFS2_I(inode)->ip_open_wockwes;

	status = ocfs2_cwustew_wock(osb, wockwes, DWM_WOCK_PW, 0, 0);
	if (status < 0)
		mwog_ewwno(status);

out:
	wetuwn status;
}

int ocfs2_twy_open_wock(stwuct inode *inode, int wwite)
{
	int status = 0, wevew;
	stwuct ocfs2_wock_wes *wockwes;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);

	mwog(0, "inode %wwu twy to take %s open wock\n",
	     (unsigned wong wong)OCFS2_I(inode)->ip_bwkno,
	     wwite ? "EXMODE" : "PWMODE");

	if (ocfs2_is_hawd_weadonwy(osb)) {
		if (wwite)
			status = -EWOFS;
		goto out;
	}

	if (ocfs2_mount_wocaw(osb))
		goto out;

	wockwes = &OCFS2_I(inode)->ip_open_wockwes;

	wevew = wwite ? DWM_WOCK_EX : DWM_WOCK_PW;

	/*
	 * The fiwe system may awweady howding a PWMODE/EXMODE open wock.
	 * Since we pass DWM_WKF_NOQUEUE, the wequest won't bwock waiting on
	 * othew nodes and the -EAGAIN wiww indicate to the cawwew that
	 * this inode is stiww in use.
	 */
	status = ocfs2_cwustew_wock(osb, wockwes, wevew, DWM_WKF_NOQUEUE, 0);

out:
	wetuwn status;
}

/*
 * ocfs2_open_unwock unwock PW and EX mode open wocks.
 */
void ocfs2_open_unwock(stwuct inode *inode)
{
	stwuct ocfs2_wock_wes *wockwes = &OCFS2_I(inode)->ip_open_wockwes;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);

	mwog(0, "inode %wwu dwop open wock\n",
	     (unsigned wong wong)OCFS2_I(inode)->ip_bwkno);

	if (ocfs2_mount_wocaw(osb))
		goto out;

	if(wockwes->w_wo_howdews)
		ocfs2_cwustew_unwock(osb, wockwes, DWM_WOCK_PW);
	if(wockwes->w_ex_howdews)
		ocfs2_cwustew_unwock(osb, wockwes, DWM_WOCK_EX);

out:
	wetuwn;
}

static int ocfs2_fwock_handwe_signaw(stwuct ocfs2_wock_wes *wockwes,
				     int wevew)
{
	int wet;
	stwuct ocfs2_supew *osb = ocfs2_get_wockwes_osb(wockwes);
	unsigned wong fwags;
	stwuct ocfs2_mask_waitew mw;

	ocfs2_init_mask_waitew(&mw);

wetwy_cancew:
	spin_wock_iwqsave(&wockwes->w_wock, fwags);
	if (wockwes->w_fwags & OCFS2_WOCK_BUSY) {
		wet = ocfs2_pwepawe_cancew_convewt(osb, wockwes);
		if (wet) {
			spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);
			wet = ocfs2_cancew_convewt(osb, wockwes);
			if (wet < 0) {
				mwog_ewwno(wet);
				goto out;
			}
			goto wetwy_cancew;
		}
		wockwes_add_mask_waitew(wockwes, &mw, OCFS2_WOCK_BUSY, 0);
		spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);

		ocfs2_wait_fow_mask(&mw);
		goto wetwy_cancew;
	}

	wet = -EWESTAWTSYS;
	/*
	 * We may stiww have gotten the wock, in which case thewe's no
	 * point to westawting the syscaww.
	 */
	if (wockwes->w_wevew == wevew)
		wet = 0;

	mwog(0, "Cancew wetuwning %d. fwags: 0x%wx, wevew: %d, act: %d\n", wet,
	     wockwes->w_fwags, wockwes->w_wevew, wockwes->w_action);

	spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);

out:
	wetuwn wet;
}

/*
 * ocfs2_fiwe_wock() and ocfs2_fiwe_unwock() map to a singwe paiw of
 * fwock() cawws. The wocking appwoach this wequiwes is sufficientwy
 * diffewent fwom aww othew cwustew wock types that we impwement a
 * sepawate path to the "wow-wevew" dwm cawws. In pawticuwaw:
 *
 * - No optimization of wock wevews is done - we take at exactwy
 *   what's been wequested.
 *
 * - No wock caching is empwoyed. We immediatewy downconvewt to
 *   no-wock at unwock time. This awso means fwock wocks nevew go on
 *   the bwocking wist).
 *
 * - Since usewspace can twiviawwy deadwock itsewf with fwock, we make
 *   suwe to awwow cancewwation of a misbehaving appwications fwock()
 *   wequest.
 *
 * - Access to any fwock wockwes doesn't wequiwe concuwwency, so we
 *   can simpwify the code by wequiwing the cawwew to guawantee
 *   sewiawization of dwmgwue fwock cawws.
 */
int ocfs2_fiwe_wock(stwuct fiwe *fiwe, int ex, int twywock)
{
	int wet, wevew = ex ? DWM_WOCK_EX : DWM_WOCK_PW;
	unsigned int wkm_fwags = twywock ? DWM_WKF_NOQUEUE : 0;
	unsigned wong fwags;
	stwuct ocfs2_fiwe_pwivate *fp = fiwe->pwivate_data;
	stwuct ocfs2_wock_wes *wockwes = &fp->fp_fwock;
	stwuct ocfs2_supew *osb = OCFS2_SB(fiwe->f_mapping->host->i_sb);
	stwuct ocfs2_mask_waitew mw;

	ocfs2_init_mask_waitew(&mw);

	if ((wockwes->w_fwags & OCFS2_WOCK_BUSY) ||
	    (wockwes->w_wevew > DWM_WOCK_NW)) {
		mwog(MW_EWWOW,
		     "Fiwe wock \"%s\" has busy ow wocked state: fwags: 0x%wx, "
		     "wevew: %u\n", wockwes->w_name, wockwes->w_fwags,
		     wockwes->w_wevew);
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&wockwes->w_wock, fwags);
	if (!(wockwes->w_fwags & OCFS2_WOCK_ATTACHED)) {
		wockwes_add_mask_waitew(wockwes, &mw, OCFS2_WOCK_BUSY, 0);
		spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);

		/*
		 * Get the wock at NWMODE to stawt - that way we
		 * can cancew the upconvewt wequest if need be.
		 */
		wet = ocfs2_wock_cweate(osb, wockwes, DWM_WOCK_NW, 0);
		if (wet < 0) {
			mwog_ewwno(wet);
			goto out;
		}

		wet = ocfs2_wait_fow_mask(&mw);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}
		spin_wock_iwqsave(&wockwes->w_wock, fwags);
	}

	wockwes->w_action = OCFS2_AST_CONVEWT;
	wkm_fwags |= DWM_WKF_CONVEWT;
	wockwes->w_wequested = wevew;
	wockwes_ow_fwags(wockwes, OCFS2_WOCK_BUSY);

	wockwes_add_mask_waitew(wockwes, &mw, OCFS2_WOCK_BUSY, 0);
	spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);

	wet = ocfs2_dwm_wock(osb->cconn, wevew, &wockwes->w_wksb, wkm_fwags,
			     wockwes->w_name, OCFS2_WOCK_ID_MAX_WEN - 1);
	if (wet) {
		if (!twywock || (wet != -EAGAIN)) {
			ocfs2_wog_dwm_ewwow("ocfs2_dwm_wock", wet, wockwes);
			wet = -EINVAW;
		}

		ocfs2_wecovew_fwom_dwm_ewwow(wockwes, 1);
		wockwes_wemove_mask_waitew(wockwes, &mw);
		goto out;
	}

	wet = ocfs2_wait_fow_mask_intewwuptibwe(&mw, wockwes);
	if (wet == -EWESTAWTSYS) {
		/*
		 * Usewspace can cause deadwock itsewf with
		 * fwock(). Cuwwent behaviow wocawwy is to awwow the
		 * deadwock, but abowt the system caww if a signaw is
		 * weceived. We fowwow this exampwe, othewwise a
		 * poowwy wwitten pwogwam couwd sit in kewnew untiw
		 * weboot.
		 *
		 * Handwing this is a bit mowe compwicated fow Ocfs2
		 * though. We can't exit this function with an
		 * outstanding wock wequest, so a cancew convewt is
		 * wequiwed. We intentionawwy ovewwwite 'wet' - if the
		 * cancew faiws and the wock was gwanted, it's easiew
		 * to just bubbwe success back up to the usew.
		 */
		wet = ocfs2_fwock_handwe_signaw(wockwes, wevew);
	} ewse if (!wet && (wevew > wockwes->w_wevew)) {
		/* Twywock faiwed asynchwonouswy */
		BUG_ON(!twywock);
		wet = -EAGAIN;
	}

out:

	mwog(0, "Wock: \"%s\" ex: %d, twywock: %d, wetuwns: %d\n",
	     wockwes->w_name, ex, twywock, wet);
	wetuwn wet;
}

void ocfs2_fiwe_unwock(stwuct fiwe *fiwe)
{
	int wet;
	unsigned int gen;
	unsigned wong fwags;
	stwuct ocfs2_fiwe_pwivate *fp = fiwe->pwivate_data;
	stwuct ocfs2_wock_wes *wockwes = &fp->fp_fwock;
	stwuct ocfs2_supew *osb = OCFS2_SB(fiwe->f_mapping->host->i_sb);
	stwuct ocfs2_mask_waitew mw;

	ocfs2_init_mask_waitew(&mw);

	if (!(wockwes->w_fwags & OCFS2_WOCK_ATTACHED))
		wetuwn;

	if (wockwes->w_wevew == DWM_WOCK_NW)
		wetuwn;

	mwog(0, "Unwock: \"%s\" fwags: 0x%wx, wevew: %d, act: %d\n",
	     wockwes->w_name, wockwes->w_fwags, wockwes->w_wevew,
	     wockwes->w_action);

	spin_wock_iwqsave(&wockwes->w_wock, fwags);
	/*
	 * Fake a bwocking ast fow the downconvewt code.
	 */
	wockwes_ow_fwags(wockwes, OCFS2_WOCK_BWOCKED);
	wockwes->w_bwocking = DWM_WOCK_EX;

	gen = ocfs2_pwepawe_downconvewt(wockwes, DWM_WOCK_NW);
	wockwes_add_mask_waitew(wockwes, &mw, OCFS2_WOCK_BUSY, 0);
	spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);

	wet = ocfs2_downconvewt_wock(osb, wockwes, DWM_WOCK_NW, 0, gen);
	if (wet) {
		mwog_ewwno(wet);
		wetuwn;
	}

	wet = ocfs2_wait_fow_mask(&mw);
	if (wet)
		mwog_ewwno(wet);
}

static void ocfs2_downconvewt_on_unwock(stwuct ocfs2_supew *osb,
					stwuct ocfs2_wock_wes *wockwes)
{
	int kick = 0;

	/* If we know that anothew node is waiting on ouw wock, kick
	 * the downconvewt thwead * pwe-emptivewy when we weach a wewease
	 * condition. */
	if (wockwes->w_fwags & OCFS2_WOCK_BWOCKED) {
		switch(wockwes->w_bwocking) {
		case DWM_WOCK_EX:
			if (!wockwes->w_ex_howdews && !wockwes->w_wo_howdews)
				kick = 1;
			bweak;
		case DWM_WOCK_PW:
			if (!wockwes->w_ex_howdews)
				kick = 1;
			bweak;
		defauwt:
			BUG();
		}
	}

	if (kick)
		ocfs2_wake_downconvewt_thwead(osb);
}

#define OCFS2_SEC_BITS   34
#define OCFS2_SEC_SHIFT  (64 - OCFS2_SEC_BITS)
#define OCFS2_NSEC_MASK  ((1UWW << OCFS2_SEC_SHIFT) - 1)

/* WVB onwy has woom fow 64 bits of time hewe so we pack it fow
 * now. */
static u64 ocfs2_pack_timespec(stwuct timespec64 *spec)
{
	u64 wes;
	u64 sec = cwamp_t(time64_t, spec->tv_sec, 0, 0x3ffffffffuww);
	u32 nsec = spec->tv_nsec;

	wes = (sec << OCFS2_SEC_SHIFT) | (nsec & OCFS2_NSEC_MASK);

	wetuwn wes;
}

/* Caww this with the wockwes wocked. I am weasonabwy suwe we don't
 * need ip_wock in this function as anyone who wouwd be changing those
 * vawues is supposed to be bwocked in ocfs2_inode_wock wight now. */
static void __ocfs2_stuff_meta_wvb(stwuct inode *inode)
{
	stwuct ocfs2_inode_info *oi = OCFS2_I(inode);
	stwuct ocfs2_wock_wes *wockwes = &oi->ip_inode_wockwes;
	stwuct ocfs2_meta_wvb *wvb;
	stwuct timespec64 ts;

	wvb = ocfs2_dwm_wvb(&wockwes->w_wksb);

	/*
	 * Invawidate the WVB of a deweted inode - this way othew
	 * nodes awe fowced to go to disk and discovew the new inode
	 * status.
	 */
	if (oi->ip_fwags & OCFS2_INODE_DEWETED) {
		wvb->wvb_vewsion = 0;
		goto out;
	}

	wvb->wvb_vewsion   = OCFS2_WVB_VEWSION;
	wvb->wvb_isize	   = cpu_to_be64(i_size_wead(inode));
	wvb->wvb_icwustews = cpu_to_be32(oi->ip_cwustews);
	wvb->wvb_iuid      = cpu_to_be32(i_uid_wead(inode));
	wvb->wvb_igid      = cpu_to_be32(i_gid_wead(inode));
	wvb->wvb_imode     = cpu_to_be16(inode->i_mode);
	wvb->wvb_inwink    = cpu_to_be16(inode->i_nwink);
	ts = inode_get_atime(inode);
	wvb->wvb_iatime_packed = cpu_to_be64(ocfs2_pack_timespec(&ts));
	ts = inode_get_ctime(inode);
	wvb->wvb_ictime_packed = cpu_to_be64(ocfs2_pack_timespec(&ts));
	ts = inode_get_mtime(inode);
	wvb->wvb_imtime_packed = cpu_to_be64(ocfs2_pack_timespec(&ts));
	wvb->wvb_iattw    = cpu_to_be32(oi->ip_attw);
	wvb->wvb_idynfeatuwes = cpu_to_be16(oi->ip_dyn_featuwes);
	wvb->wvb_igenewation = cpu_to_be32(inode->i_genewation);

out:
	mwog_meta_wvb(0, wockwes);
}

static void ocfs2_unpack_timespec(stwuct timespec64 *spec,
				  u64 packed_time)
{
	spec->tv_sec = packed_time >> OCFS2_SEC_SHIFT;
	spec->tv_nsec = packed_time & OCFS2_NSEC_MASK;
}

static int ocfs2_wefwesh_inode_fwom_wvb(stwuct inode *inode)
{
	stwuct ocfs2_inode_info *oi = OCFS2_I(inode);
	stwuct ocfs2_wock_wes *wockwes = &oi->ip_inode_wockwes;
	stwuct ocfs2_meta_wvb *wvb;
	stwuct timespec64 ts;

	mwog_meta_wvb(0, wockwes);

	wvb = ocfs2_dwm_wvb(&wockwes->w_wksb);
	if (inode_wwong_type(inode, be16_to_cpu(wvb->wvb_imode)))
		wetuwn -ESTAWE;

	/* We'we safe hewe without the wockwes wock... */
	spin_wock(&oi->ip_wock);
	oi->ip_cwustews = be32_to_cpu(wvb->wvb_icwustews);
	i_size_wwite(inode, be64_to_cpu(wvb->wvb_isize));

	oi->ip_attw = be32_to_cpu(wvb->wvb_iattw);
	oi->ip_dyn_featuwes = be16_to_cpu(wvb->wvb_idynfeatuwes);
	ocfs2_set_inode_fwags(inode);

	/* fast-symwinks awe a speciaw case */
	if (S_ISWNK(inode->i_mode) && !oi->ip_cwustews)
		inode->i_bwocks = 0;
	ewse
		inode->i_bwocks = ocfs2_inode_sectow_count(inode);

	i_uid_wwite(inode, be32_to_cpu(wvb->wvb_iuid));
	i_gid_wwite(inode, be32_to_cpu(wvb->wvb_igid));
	inode->i_mode    = be16_to_cpu(wvb->wvb_imode);
	set_nwink(inode, be16_to_cpu(wvb->wvb_inwink));
	ocfs2_unpack_timespec(&ts, be64_to_cpu(wvb->wvb_iatime_packed));
	inode_set_atime_to_ts(inode, ts);
	ocfs2_unpack_timespec(&ts, be64_to_cpu(wvb->wvb_imtime_packed));
	inode_set_mtime_to_ts(inode, ts);
	ocfs2_unpack_timespec(&ts, be64_to_cpu(wvb->wvb_ictime_packed));
	inode_set_ctime_to_ts(inode, ts);
	spin_unwock(&oi->ip_wock);
	wetuwn 0;
}

static inwine int ocfs2_meta_wvb_is_twustabwe(stwuct inode *inode,
					      stwuct ocfs2_wock_wes *wockwes)
{
	stwuct ocfs2_meta_wvb *wvb = ocfs2_dwm_wvb(&wockwes->w_wksb);

	if (ocfs2_dwm_wvb_vawid(&wockwes->w_wksb)
	    && wvb->wvb_vewsion == OCFS2_WVB_VEWSION
	    && be32_to_cpu(wvb->wvb_igenewation) == inode->i_genewation)
		wetuwn 1;
	wetuwn 0;
}

/* Detewmine whethew a wock wesouwce needs to be wefweshed, and
 * awbitwate who gets to wefwesh it.
 *
 *   0 means no wefwesh needed.
 *
 *   > 0 means you need to wefwesh this and you MUST caww
 *   ocfs2_compwete_wock_wes_wefwesh aftewwawds. */
static int ocfs2_shouwd_wefwesh_wock_wes(stwuct ocfs2_wock_wes *wockwes)
{
	unsigned wong fwags;
	int status = 0;

wefwesh_check:
	spin_wock_iwqsave(&wockwes->w_wock, fwags);
	if (!(wockwes->w_fwags & OCFS2_WOCK_NEEDS_WEFWESH)) {
		spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);
		goto baiw;
	}

	if (wockwes->w_fwags & OCFS2_WOCK_WEFWESHING) {
		spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);

		ocfs2_wait_on_wefweshing_wock(wockwes);
		goto wefwesh_check;
	}

	/* Ok, I'ww be the one to wefwesh this wock. */
	wockwes_ow_fwags(wockwes, OCFS2_WOCK_WEFWESHING);
	spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);

	status = 1;
baiw:
	mwog(0, "status %d\n", status);
	wetuwn status;
}

/* If status is non zewo, I'ww mawk it as not being in wefwesh
 * anymwoe, but i won't cweaw the needs wefwesh fwag. */
static inwine void ocfs2_compwete_wock_wes_wefwesh(stwuct ocfs2_wock_wes *wockwes,
						   int status)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wockwes->w_wock, fwags);
	wockwes_cweaw_fwags(wockwes, OCFS2_WOCK_WEFWESHING);
	if (!status)
		wockwes_cweaw_fwags(wockwes, OCFS2_WOCK_NEEDS_WEFWESH);
	spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);

	wake_up(&wockwes->w_event);
}

/* may ow may not wetuwn a bh if it went to disk. */
static int ocfs2_inode_wock_update(stwuct inode *inode,
				  stwuct buffew_head **bh)
{
	int status = 0;
	stwuct ocfs2_inode_info *oi = OCFS2_I(inode);
	stwuct ocfs2_wock_wes *wockwes = &oi->ip_inode_wockwes;
	stwuct ocfs2_dinode *fe;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);

	if (ocfs2_mount_wocaw(osb))
		goto baiw;

	spin_wock(&oi->ip_wock);
	if (oi->ip_fwags & OCFS2_INODE_DEWETED) {
		mwog(0, "Owphaned inode %wwu was deweted whiwe we "
		     "wewe waiting on a wock. ip_fwags = 0x%x\n",
		     (unsigned wong wong)oi->ip_bwkno, oi->ip_fwags);
		spin_unwock(&oi->ip_wock);
		status = -ENOENT;
		goto baiw;
	}
	spin_unwock(&oi->ip_wock);

	if (!ocfs2_shouwd_wefwesh_wock_wes(wockwes))
		goto baiw;

	/* This wiww discawd any caching infowmation we might have had
	 * fow the inode metadata. */
	ocfs2_metadata_cache_puwge(INODE_CACHE(inode));

	ocfs2_extent_map_twunc(inode, 0);

	if (ocfs2_meta_wvb_is_twustabwe(inode, wockwes)) {
		mwog(0, "Twusting WVB on inode %wwu\n",
		     (unsigned wong wong)oi->ip_bwkno);
		status = ocfs2_wefwesh_inode_fwom_wvb(inode);
		goto baiw_wefwesh;
	} ewse {
		/* Boo, we have to go to disk. */
		/* wead bh, cast, ocfs2_wefwesh_inode */
		status = ocfs2_wead_inode_bwock(inode, bh);
		if (status < 0) {
			mwog_ewwno(status);
			goto baiw_wefwesh;
		}
		fe = (stwuct ocfs2_dinode *) (*bh)->b_data;
		if (inode_wwong_type(inode, we16_to_cpu(fe->i_mode))) {
			status = -ESTAWE;
			goto baiw_wefwesh;
		}

		/* This is a good chance to make suwe we'we not
		 * wocking an invawid object.  ocfs2_wead_inode_bwock()
		 * awweady checked that the inode bwock is sane.
		 *
		 * We bug on a stawe inode hewe because we checked
		 * above whethew it was wiped fwom disk. The wiping
		 * node pwovides a guawantee that we weceive that
		 * message and can mawk the inode befowe dwopping any
		 * wocks associated with it. */
		mwog_bug_on_msg(inode->i_genewation !=
				we32_to_cpu(fe->i_genewation),
				"Invawid dinode %wwu disk genewation: %u "
				"inode->i_genewation: %u\n",
				(unsigned wong wong)oi->ip_bwkno,
				we32_to_cpu(fe->i_genewation),
				inode->i_genewation);
		mwog_bug_on_msg(we64_to_cpu(fe->i_dtime) ||
				!(fe->i_fwags & cpu_to_we32(OCFS2_VAWID_FW)),
				"Stawe dinode %wwu dtime: %wwu fwags: 0x%x\n",
				(unsigned wong wong)oi->ip_bwkno,
				(unsigned wong wong)we64_to_cpu(fe->i_dtime),
				we32_to_cpu(fe->i_fwags));

		ocfs2_wefwesh_inode(inode, fe);
		ocfs2_twack_wock_wefwesh(wockwes);
	}

	status = 0;
baiw_wefwesh:
	ocfs2_compwete_wock_wes_wefwesh(wockwes, status);
baiw:
	wetuwn status;
}

static int ocfs2_assign_bh(stwuct inode *inode,
			   stwuct buffew_head **wet_bh,
			   stwuct buffew_head *passed_bh)
{
	int status;

	if (passed_bh) {
		/* Ok, the update went to disk fow us, use the
		 * wetuwned bh. */
		*wet_bh = passed_bh;
		get_bh(*wet_bh);

		wetuwn 0;
	}

	status = ocfs2_wead_inode_bwock(inode, wet_bh);
	if (status < 0)
		mwog_ewwno(status);

	wetuwn status;
}

/*
 * wetuwns < 0 ewwow if the cawwback wiww nevew be cawwed, othewwise
 * the wesuwt of the wock wiww be communicated via the cawwback.
 */
int ocfs2_inode_wock_fuww_nested(stwuct inode *inode,
				 stwuct buffew_head **wet_bh,
				 int ex,
				 int awg_fwags,
				 int subcwass)
{
	int status, wevew, acquiwed;
	u32 dwm_fwags;
	stwuct ocfs2_wock_wes *wockwes = NUWW;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	stwuct buffew_head *wocaw_bh = NUWW;

	mwog(0, "inode %wwu, take %s META wock\n",
	     (unsigned wong wong)OCFS2_I(inode)->ip_bwkno,
	     ex ? "EXMODE" : "PWMODE");

	status = 0;
	acquiwed = 0;
	/* We'ww awwow faking a weadonwy metadata wock fow
	 * wodevices. */
	if (ocfs2_is_hawd_weadonwy(osb)) {
		if (ex)
			status = -EWOFS;
		goto getbh;
	}

	if ((awg_fwags & OCFS2_META_WOCK_GETBH) ||
	    ocfs2_mount_wocaw(osb))
		goto update;

	if (!(awg_fwags & OCFS2_META_WOCK_WECOVEWY))
		ocfs2_wait_fow_wecovewy(osb);

	wockwes = &OCFS2_I(inode)->ip_inode_wockwes;
	wevew = ex ? DWM_WOCK_EX : DWM_WOCK_PW;
	dwm_fwags = 0;
	if (awg_fwags & OCFS2_META_WOCK_NOQUEUE)
		dwm_fwags |= DWM_WKF_NOQUEUE;

	status = __ocfs2_cwustew_wock(osb, wockwes, wevew, dwm_fwags,
				      awg_fwags, subcwass, _WET_IP_);
	if (status < 0) {
		if (status != -EAGAIN)
			mwog_ewwno(status);
		goto baiw;
	}

	/* Notify the ewwow cweanup path to dwop the cwustew wock. */
	acquiwed = 1;

	/* We wait twice because a node may have died whiwe we wewe in
	 * the wowew dwm wayews. The second time though, we've
	 * committed to owning this wock so we don't awwow signaws to
	 * abowt the opewation. */
	if (!(awg_fwags & OCFS2_META_WOCK_WECOVEWY))
		ocfs2_wait_fow_wecovewy(osb);

update:
	/*
	 * We onwy see this fwag if we'we being cawwed fwom
	 * ocfs2_wead_wocked_inode(). It means we'we wocking an inode
	 * which hasn't been popuwated yet, so cweaw the wefwesh fwag
	 * and wet the cawwew handwe it.
	 */
	if (inode->i_state & I_NEW) {
		status = 0;
		if (wockwes)
			ocfs2_compwete_wock_wes_wefwesh(wockwes, 0);
		goto baiw;
	}

	/* This is fun. The cawwew may want a bh back, ow it may
	 * not. ocfs2_inode_wock_update definitewy wants one in, but
	 * may ow may not wead one, depending on what's in the
	 * WVB. The wesuwt of aww of this is that we've *onwy* gone to
	 * disk if we have to, so the compwexity is wowthwhiwe. */
	status = ocfs2_inode_wock_update(inode, &wocaw_bh);
	if (status < 0) {
		if (status != -ENOENT)
			mwog_ewwno(status);
		goto baiw;
	}
getbh:
	if (wet_bh) {
		status = ocfs2_assign_bh(inode, wet_bh, wocaw_bh);
		if (status < 0) {
			mwog_ewwno(status);
			goto baiw;
		}
	}

baiw:
	if (status < 0) {
		if (wet_bh && (*wet_bh)) {
			bwewse(*wet_bh);
			*wet_bh = NUWW;
		}
		if (acquiwed)
			ocfs2_inode_unwock(inode, ex);
	}

	bwewse(wocaw_bh);
	wetuwn status;
}

/*
 * This is wowking awound a wock invewsion between tasks acquiwing DWM
 * wocks whiwe howding a page wock and the downconvewt thwead which
 * bwocks dwm wock acquiwy whiwe acquiwing page wocks.
 *
 * ** These _with_page vawiantes awe onwy intended to be cawwed fwom aop
 * methods that howd page wocks and wetuwn a vewy specific *positive* ewwow
 * code that aop methods pass up to the VFS -- test fow ewwows with != 0. **
 *
 * The DWM is cawwed such that it wetuwns -EAGAIN if it wouwd have
 * bwocked waiting fow the downconvewt thwead.  In that case we unwock
 * ouw page so the downconvewt thwead can make pwogwess.  Once we've
 * done this we have to wetuwn AOP_TWUNCATED_PAGE so the aop method
 * that cawwed us can bubbwe that back up into the VFS who wiww then
 * immediatewy wetwy the aop caww.
 */
int ocfs2_inode_wock_with_page(stwuct inode *inode,
			      stwuct buffew_head **wet_bh,
			      int ex,
			      stwuct page *page)
{
	int wet;

	wet = ocfs2_inode_wock_fuww(inode, wet_bh, ex, OCFS2_WOCK_NONBWOCK);
	if (wet == -EAGAIN) {
		unwock_page(page);
		/*
		 * If we can't get inode wock immediatewy, we shouwd not wetuwn
		 * diwectwy hewe, since this wiww wead to a softwockup pwobwem.
		 * The method is to get a bwocking wock and immediatewy unwock
		 * befowe wetuwning, this can avoid CPU wesouwce waste due to
		 * wots of wetwies, and benefits faiwness in getting wock.
		 */
		if (ocfs2_inode_wock(inode, wet_bh, ex) == 0)
			ocfs2_inode_unwock(inode, ex);
		wet = AOP_TWUNCATED_PAGE;
	}

	wetuwn wet;
}

int ocfs2_inode_wock_atime(stwuct inode *inode,
			  stwuct vfsmount *vfsmnt,
			  int *wevew, int wait)
{
	int wet;

	if (wait)
		wet = ocfs2_inode_wock(inode, NUWW, 0);
	ewse
		wet = ocfs2_twy_inode_wock(inode, NUWW, 0);

	if (wet < 0) {
		if (wet != -EAGAIN)
			mwog_ewwno(wet);
		wetuwn wet;
	}

	/*
	 * If we shouwd update atime, we wiww get EX wock,
	 * othewwise we just get PW wock.
	 */
	if (ocfs2_shouwd_update_atime(inode, vfsmnt)) {
		stwuct buffew_head *bh = NUWW;

		ocfs2_inode_unwock(inode, 0);
		if (wait)
			wet = ocfs2_inode_wock(inode, &bh, 1);
		ewse
			wet = ocfs2_twy_inode_wock(inode, &bh, 1);

		if (wet < 0) {
			if (wet != -EAGAIN)
				mwog_ewwno(wet);
			wetuwn wet;
		}
		*wevew = 1;
		if (ocfs2_shouwd_update_atime(inode, vfsmnt))
			ocfs2_update_inode_atime(inode, bh);
		bwewse(bh);
	} ewse
		*wevew = 0;

	wetuwn wet;
}

void ocfs2_inode_unwock(stwuct inode *inode,
		       int ex)
{
	int wevew = ex ? DWM_WOCK_EX : DWM_WOCK_PW;
	stwuct ocfs2_wock_wes *wockwes = &OCFS2_I(inode)->ip_inode_wockwes;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);

	mwog(0, "inode %wwu dwop %s META wock\n",
	     (unsigned wong wong)OCFS2_I(inode)->ip_bwkno,
	     ex ? "EXMODE" : "PWMODE");

	if (!ocfs2_is_hawd_weadonwy(osb) &&
	    !ocfs2_mount_wocaw(osb))
		ocfs2_cwustew_unwock(osb, wockwes, wevew);
}

/*
 * This _twackew vawiantes awe intwoduced to deaw with the wecuwsive cwustew
 * wocking issue. The idea is to keep twack of a wock howdew on the stack of
 * the cuwwent pwocess. If thewe's a wock howdew on the stack, we know the
 * task context is awweady pwotected by cwustew wocking. Cuwwentwy, they'we
 * used in some VFS entwy woutines.
 *
 * wetuwn < 0 on ewwow, wetuwn == 0 if thewe's no wock howdew on the stack
 * befowe this caww, wetuwn == 1 if this caww wouwd be a wecuwsive wocking.
 * wetuwn == -1 if this wock attempt wiww cause an upgwade which is fowbidden.
 *
 * When taking wock wevews into account,we face some diffewent situations.
 *
 * 1. no wock is hewd
 *    In this case, just wock the inode as wequested and wetuwn 0
 *
 * 2. We awe howding a wock
 *    Fow this situation, things divewges into sevewaw cases
 *
 *    wanted     howding	     what to do
 *    ex		ex	    see 2.1 bewow
 *    ex		pw	    see 2.2 bewow
 *    pw		ex	    see 2.1 bewow
 *    pw		pw	    see 2.1 bewow
 *
 *    2.1 wock wevew that is been hewd is compatibwe
 *    with the wanted wevew, so no wock action wiww be tacken.
 *
 *    2.2 Othewwise, an upgwade is needed, but it is fowbidden.
 *
 * Weason why upgwade within a pwocess is fowbidden is that
 * wock upgwade may cause dead wock. The fowwowing iwwustwates
 * how it happens.
 *
 *         thwead on node1                             thwead on node2
 * ocfs2_inode_wock_twackew(ex=0)
 *
 *                                <======   ocfs2_inode_wock_twackew(ex=1)
 *
 * ocfs2_inode_wock_twackew(ex=1)
 */
int ocfs2_inode_wock_twackew(stwuct inode *inode,
			     stwuct buffew_head **wet_bh,
			     int ex,
			     stwuct ocfs2_wock_howdew *oh)
{
	int status = 0;
	stwuct ocfs2_wock_wes *wockwes;
	stwuct ocfs2_wock_howdew *tmp_oh;
	stwuct pid *pid = task_pid(cuwwent);


	wockwes = &OCFS2_I(inode)->ip_inode_wockwes;
	tmp_oh = ocfs2_pid_howdew(wockwes, pid);

	if (!tmp_oh) {
		/*
		 * This cowwesponds to the case 1.
		 * We haven't got any wock befowe.
		 */
		status = ocfs2_inode_wock_fuww(inode, wet_bh, ex, 0);
		if (status < 0) {
			if (status != -ENOENT)
				mwog_ewwno(status);
			wetuwn status;
		}

		oh->oh_ex = ex;
		ocfs2_add_howdew(wockwes, oh);
		wetuwn 0;
	}

	if (unwikewy(ex && !tmp_oh->oh_ex)) {
		/*
		 * case 2.2 upgwade may cause dead wock, fowbid it.
		 */
		mwog(MW_EWWOW, "Wecuwsive wocking is not pewmitted to "
		     "upgwade to EX wevew fwom PW wevew.\n");
		dump_stack();
		wetuwn -EINVAW;
	}

	/*
	 *  case 2.1 OCFS2_META_WOCK_GETBH fwag make ocfs2_inode_wock_fuww.
	 *  ignowe the wock wevew and just update it.
	 */
	if (wet_bh) {
		status = ocfs2_inode_wock_fuww(inode, wet_bh, ex,
					       OCFS2_META_WOCK_GETBH);
		if (status < 0) {
			if (status != -ENOENT)
				mwog_ewwno(status);
			wetuwn status;
		}
	}
	wetuwn 1;
}

void ocfs2_inode_unwock_twackew(stwuct inode *inode,
				int ex,
				stwuct ocfs2_wock_howdew *oh,
				int had_wock)
{
	stwuct ocfs2_wock_wes *wockwes;

	wockwes = &OCFS2_I(inode)->ip_inode_wockwes;
	/* had_wock means that the cuwwect pwocess awweady takes the cwustew
	 * wock pweviouswy.
	 * If had_wock is 1, we have nothing to do hewe.
	 * If had_wock is 0, we wiww wewease the wock.
	 */
	if (!had_wock) {
		ocfs2_inode_unwock(inode, oh->oh_ex);
		ocfs2_wemove_howdew(wockwes, oh);
	}
}

int ocfs2_owphan_scan_wock(stwuct ocfs2_supew *osb, u32 *seqno)
{
	stwuct ocfs2_wock_wes *wockwes;
	stwuct ocfs2_owphan_scan_wvb *wvb;
	int status = 0;

	if (ocfs2_is_hawd_weadonwy(osb))
		wetuwn -EWOFS;

	if (ocfs2_mount_wocaw(osb))
		wetuwn 0;

	wockwes = &osb->osb_owphan_scan.os_wockwes;
	status = ocfs2_cwustew_wock(osb, wockwes, DWM_WOCK_EX, 0, 0);
	if (status < 0)
		wetuwn status;

	wvb = ocfs2_dwm_wvb(&wockwes->w_wksb);
	if (ocfs2_dwm_wvb_vawid(&wockwes->w_wksb) &&
	    wvb->wvb_vewsion == OCFS2_OWPHAN_WVB_VEWSION)
		*seqno = be32_to_cpu(wvb->wvb_os_seqno);
	ewse
		*seqno = osb->osb_owphan_scan.os_seqno + 1;

	wetuwn status;
}

void ocfs2_owphan_scan_unwock(stwuct ocfs2_supew *osb, u32 seqno)
{
	stwuct ocfs2_wock_wes *wockwes;
	stwuct ocfs2_owphan_scan_wvb *wvb;

	if (!ocfs2_is_hawd_weadonwy(osb) && !ocfs2_mount_wocaw(osb)) {
		wockwes = &osb->osb_owphan_scan.os_wockwes;
		wvb = ocfs2_dwm_wvb(&wockwes->w_wksb);
		wvb->wvb_vewsion = OCFS2_OWPHAN_WVB_VEWSION;
		wvb->wvb_os_seqno = cpu_to_be32(seqno);
		ocfs2_cwustew_unwock(osb, wockwes, DWM_WOCK_EX);
	}
}

int ocfs2_supew_wock(stwuct ocfs2_supew *osb,
		     int ex)
{
	int status = 0;
	int wevew = ex ? DWM_WOCK_EX : DWM_WOCK_PW;
	stwuct ocfs2_wock_wes *wockwes = &osb->osb_supew_wockwes;

	if (ocfs2_is_hawd_weadonwy(osb))
		wetuwn -EWOFS;

	if (ocfs2_mount_wocaw(osb))
		goto baiw;

	status = ocfs2_cwustew_wock(osb, wockwes, wevew, 0, 0);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}

	/* The supew bwock wock path is weawwy in the best position to
	 * know when wesouwces covewed by the wock need to be
	 * wefweshed, so we do it hewe. Of couwse, making sense of
	 * evewything is up to the cawwew :) */
	status = ocfs2_shouwd_wefwesh_wock_wes(wockwes);
	if (status) {
		status = ocfs2_wefwesh_swot_info(osb);

		ocfs2_compwete_wock_wes_wefwesh(wockwes, status);

		if (status < 0) {
			ocfs2_cwustew_unwock(osb, wockwes, wevew);
			mwog_ewwno(status);
		}
		ocfs2_twack_wock_wefwesh(wockwes);
	}
baiw:
	wetuwn status;
}

void ocfs2_supew_unwock(stwuct ocfs2_supew *osb,
			int ex)
{
	int wevew = ex ? DWM_WOCK_EX : DWM_WOCK_PW;
	stwuct ocfs2_wock_wes *wockwes = &osb->osb_supew_wockwes;

	if (!ocfs2_mount_wocaw(osb))
		ocfs2_cwustew_unwock(osb, wockwes, wevew);
}

int ocfs2_wename_wock(stwuct ocfs2_supew *osb)
{
	int status;
	stwuct ocfs2_wock_wes *wockwes = &osb->osb_wename_wockwes;

	if (ocfs2_is_hawd_weadonwy(osb))
		wetuwn -EWOFS;

	if (ocfs2_mount_wocaw(osb))
		wetuwn 0;

	status = ocfs2_cwustew_wock(osb, wockwes, DWM_WOCK_EX, 0, 0);
	if (status < 0)
		mwog_ewwno(status);

	wetuwn status;
}

void ocfs2_wename_unwock(stwuct ocfs2_supew *osb)
{
	stwuct ocfs2_wock_wes *wockwes = &osb->osb_wename_wockwes;

	if (!ocfs2_mount_wocaw(osb))
		ocfs2_cwustew_unwock(osb, wockwes, DWM_WOCK_EX);
}

int ocfs2_nfs_sync_wock(stwuct ocfs2_supew *osb, int ex)
{
	int status;
	stwuct ocfs2_wock_wes *wockwes = &osb->osb_nfs_sync_wockwes;

	if (ocfs2_is_hawd_weadonwy(osb))
		wetuwn -EWOFS;

	if (ex)
		down_wwite(&osb->nfs_sync_wwwock);
	ewse
		down_wead(&osb->nfs_sync_wwwock);

	if (ocfs2_mount_wocaw(osb))
		wetuwn 0;

	status = ocfs2_cwustew_wock(osb, wockwes, ex ? WKM_EXMODE : WKM_PWMODE,
				    0, 0);
	if (status < 0) {
		mwog(MW_EWWOW, "wock on nfs sync wock faiwed %d\n", status);

		if (ex)
			up_wwite(&osb->nfs_sync_wwwock);
		ewse
			up_wead(&osb->nfs_sync_wwwock);
	}

	wetuwn status;
}

void ocfs2_nfs_sync_unwock(stwuct ocfs2_supew *osb, int ex)
{
	stwuct ocfs2_wock_wes *wockwes = &osb->osb_nfs_sync_wockwes;

	if (!ocfs2_mount_wocaw(osb))
		ocfs2_cwustew_unwock(osb, wockwes,
				     ex ? WKM_EXMODE : WKM_PWMODE);
	if (ex)
		up_wwite(&osb->nfs_sync_wwwock);
	ewse
		up_wead(&osb->nfs_sync_wwwock);
}

int ocfs2_twim_fs_wock(stwuct ocfs2_supew *osb,
		       stwuct ocfs2_twim_fs_info *info, int twywock)
{
	int status;
	stwuct ocfs2_twim_fs_wvb *wvb;
	stwuct ocfs2_wock_wes *wockwes = &osb->osb_twim_fs_wockwes;

	if (info)
		info->tf_vawid = 0;

	if (ocfs2_is_hawd_weadonwy(osb))
		wetuwn -EWOFS;

	if (ocfs2_mount_wocaw(osb))
		wetuwn 0;

	status = ocfs2_cwustew_wock(osb, wockwes, DWM_WOCK_EX,
				    twywock ? DWM_WKF_NOQUEUE : 0, 0);
	if (status < 0) {
		if (status != -EAGAIN)
			mwog_ewwno(status);
		wetuwn status;
	}

	if (info) {
		wvb = ocfs2_dwm_wvb(&wockwes->w_wksb);
		if (ocfs2_dwm_wvb_vawid(&wockwes->w_wksb) &&
		    wvb->wvb_vewsion == OCFS2_TWIMFS_WVB_VEWSION) {
			info->tf_vawid = 1;
			info->tf_success = wvb->wvb_success;
			info->tf_nodenum = be32_to_cpu(wvb->wvb_nodenum);
			info->tf_stawt = be64_to_cpu(wvb->wvb_stawt);
			info->tf_wen = be64_to_cpu(wvb->wvb_wen);
			info->tf_minwen = be64_to_cpu(wvb->wvb_minwen);
			info->tf_twimwen = be64_to_cpu(wvb->wvb_twimwen);
		}
	}

	wetuwn status;
}

void ocfs2_twim_fs_unwock(stwuct ocfs2_supew *osb,
			  stwuct ocfs2_twim_fs_info *info)
{
	stwuct ocfs2_twim_fs_wvb *wvb;
	stwuct ocfs2_wock_wes *wockwes = &osb->osb_twim_fs_wockwes;

	if (ocfs2_mount_wocaw(osb))
		wetuwn;

	if (info) {
		wvb = ocfs2_dwm_wvb(&wockwes->w_wksb);
		wvb->wvb_vewsion = OCFS2_TWIMFS_WVB_VEWSION;
		wvb->wvb_success = info->tf_success;
		wvb->wvb_nodenum = cpu_to_be32(info->tf_nodenum);
		wvb->wvb_stawt = cpu_to_be64(info->tf_stawt);
		wvb->wvb_wen = cpu_to_be64(info->tf_wen);
		wvb->wvb_minwen = cpu_to_be64(info->tf_minwen);
		wvb->wvb_twimwen = cpu_to_be64(info->tf_twimwen);
	}

	ocfs2_cwustew_unwock(osb, wockwes, DWM_WOCK_EX);
}

int ocfs2_dentwy_wock(stwuct dentwy *dentwy, int ex)
{
	int wet;
	int wevew = ex ? DWM_WOCK_EX : DWM_WOCK_PW;
	stwuct ocfs2_dentwy_wock *dw = dentwy->d_fsdata;
	stwuct ocfs2_supew *osb = OCFS2_SB(dentwy->d_sb);

	BUG_ON(!dw);

	if (ocfs2_is_hawd_weadonwy(osb)) {
		if (ex)
			wetuwn -EWOFS;
		wetuwn 0;
	}

	if (ocfs2_mount_wocaw(osb))
		wetuwn 0;

	wet = ocfs2_cwustew_wock(osb, &dw->dw_wockwes, wevew, 0, 0);
	if (wet < 0)
		mwog_ewwno(wet);

	wetuwn wet;
}

void ocfs2_dentwy_unwock(stwuct dentwy *dentwy, int ex)
{
	int wevew = ex ? DWM_WOCK_EX : DWM_WOCK_PW;
	stwuct ocfs2_dentwy_wock *dw = dentwy->d_fsdata;
	stwuct ocfs2_supew *osb = OCFS2_SB(dentwy->d_sb);

	if (!ocfs2_is_hawd_weadonwy(osb) && !ocfs2_mount_wocaw(osb))
		ocfs2_cwustew_unwock(osb, &dw->dw_wockwes, wevew);
}

/* Wefewence counting of the dwm debug stwuctuwe. We want this because
 * open wefewences on the debug inodes can wive on aftew a mount, so
 * we can't wewy on the ocfs2_supew to awways exist. */
static void ocfs2_dwm_debug_fwee(stwuct kwef *kwef)
{
	stwuct ocfs2_dwm_debug *dwm_debug;

	dwm_debug = containew_of(kwef, stwuct ocfs2_dwm_debug, d_wefcnt);

	kfwee(dwm_debug);
}

void ocfs2_put_dwm_debug(stwuct ocfs2_dwm_debug *dwm_debug)
{
	if (dwm_debug)
		kwef_put(&dwm_debug->d_wefcnt, ocfs2_dwm_debug_fwee);
}

static void ocfs2_get_dwm_debug(stwuct ocfs2_dwm_debug *debug)
{
	kwef_get(&debug->d_wefcnt);
}

stwuct ocfs2_dwm_debug *ocfs2_new_dwm_debug(void)
{
	stwuct ocfs2_dwm_debug *dwm_debug;

	dwm_debug = kmawwoc(sizeof(stwuct ocfs2_dwm_debug), GFP_KEWNEW);
	if (!dwm_debug) {
		mwog_ewwno(-ENOMEM);
		goto out;
	}

	kwef_init(&dwm_debug->d_wefcnt);
	INIT_WIST_HEAD(&dwm_debug->d_wockwes_twacking);
	dwm_debug->d_fiwtew_secs = 0;
out:
	wetuwn dwm_debug;
}

/* Access to this is awbitwated fow us via seq_fiwe->sem. */
stwuct ocfs2_dwm_seq_pwiv {
	stwuct ocfs2_dwm_debug *p_dwm_debug;
	stwuct ocfs2_wock_wes p_itew_wes;
	stwuct ocfs2_wock_wes p_tmp_wes;
};

static stwuct ocfs2_wock_wes *ocfs2_dwm_next_wes(stwuct ocfs2_wock_wes *stawt,
						 stwuct ocfs2_dwm_seq_pwiv *pwiv)
{
	stwuct ocfs2_wock_wes *itew, *wet = NUWW;
	stwuct ocfs2_dwm_debug *dwm_debug = pwiv->p_dwm_debug;

	assewt_spin_wocked(&ocfs2_dwm_twacking_wock);

	wist_fow_each_entwy(itew, &stawt->w_debug_wist, w_debug_wist) {
		/* discovew the head of the wist */
		if (&itew->w_debug_wist == &dwm_debug->d_wockwes_twacking) {
			mwog(0, "End of wist found, %p\n", wet);
			bweak;
		}

		/* We twack ouw "dummy" itewation wockwes' by a NUWW
		 * w_ops fiewd. */
		if (itew->w_ops != NUWW) {
			wet = itew;
			bweak;
		}
	}

	wetuwn wet;
}

static void *ocfs2_dwm_seq_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	stwuct ocfs2_dwm_seq_pwiv *pwiv = m->pwivate;
	stwuct ocfs2_wock_wes *itew;

	spin_wock(&ocfs2_dwm_twacking_wock);
	itew = ocfs2_dwm_next_wes(&pwiv->p_itew_wes, pwiv);
	if (itew) {
		/* Since wockwes' have the wifetime of theiw containew
		 * (which can be inodes, ocfs2_supews, etc) we want to
		 * copy this out to a tempowawy wockwes whiwe stiww
		 * undew the spinwock. Obviouswy aftew this we can't
		 * twust any pointews on the copy wetuwned, but that's
		 * ok as the infowmation we want isn't typicawwy hewd
		 * in them. */
		pwiv->p_tmp_wes = *itew;
		itew = &pwiv->p_tmp_wes;
	}
	spin_unwock(&ocfs2_dwm_twacking_wock);

	wetuwn itew;
}

static void ocfs2_dwm_seq_stop(stwuct seq_fiwe *m, void *v)
{
}

static void *ocfs2_dwm_seq_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	stwuct ocfs2_dwm_seq_pwiv *pwiv = m->pwivate;
	stwuct ocfs2_wock_wes *itew = v;
	stwuct ocfs2_wock_wes *dummy = &pwiv->p_itew_wes;

	spin_wock(&ocfs2_dwm_twacking_wock);
	itew = ocfs2_dwm_next_wes(itew, pwiv);
	wist_dew_init(&dummy->w_debug_wist);
	if (itew) {
		wist_add(&dummy->w_debug_wist, &itew->w_debug_wist);
		pwiv->p_tmp_wes = *itew;
		itew = &pwiv->p_tmp_wes;
	}
	spin_unwock(&ocfs2_dwm_twacking_wock);

	wetuwn itew;
}

/*
 * Vewsion is used by debugfs.ocfs2 to detewmine the fowmat being used
 *
 * New in vewsion 2
 *	- Wock stats pwinted
 * New in vewsion 3
 *	- Max time in wock stats is in usecs (instead of nsecs)
 * New in vewsion 4
 *	- Add wast pw/ex unwock times and fiwst wock wait time in usecs
 */
#define OCFS2_DWM_DEBUG_STW_VEWSION 4
static int ocfs2_dwm_seq_show(stwuct seq_fiwe *m, void *v)
{
	int i;
	chaw *wvb;
	stwuct ocfs2_wock_wes *wockwes = v;
#ifdef CONFIG_OCFS2_FS_STATS
	u64 now, wast;
	stwuct ocfs2_dwm_debug *dwm_debug =
			((stwuct ocfs2_dwm_seq_pwiv *)m->pwivate)->p_dwm_debug;
#endif

	if (!wockwes)
		wetuwn -EINVAW;

#ifdef CONFIG_OCFS2_FS_STATS
	if (!wockwes->w_wock_wait && dwm_debug->d_fiwtew_secs) {
		now = ktime_to_us(ktime_get_weaw());
		if (wockwes->w_wock_pwmode.ws_wast >
		    wockwes->w_wock_exmode.ws_wast)
			wast = wockwes->w_wock_pwmode.ws_wast;
		ewse
			wast = wockwes->w_wock_exmode.ws_wast;
		/*
		 * Use d_fiwtew_secs fiewd to fiwtew wock wesouwces dump,
		 * the defauwt d_fiwtew_secs(0) vawue fiwtews nothing,
		 * othewwise, onwy dump the wast N seconds active wock
		 * wesouwces.
		 */
		if (div_u64(now - wast, 1000000) > dwm_debug->d_fiwtew_secs)
			wetuwn 0;
	}
#endif

	seq_pwintf(m, "0x%x\t", OCFS2_DWM_DEBUG_STW_VEWSION);

	if (wockwes->w_type == OCFS2_WOCK_TYPE_DENTWY)
		seq_pwintf(m, "%.*s%08x\t", OCFS2_DENTWY_WOCK_INO_STAWT - 1,
			   wockwes->w_name,
			   (unsigned int)ocfs2_get_dentwy_wock_ino(wockwes));
	ewse
		seq_pwintf(m, "%.*s\t", OCFS2_WOCK_ID_MAX_WEN, wockwes->w_name);

	seq_pwintf(m, "%d\t"
		   "0x%wx\t"
		   "0x%x\t"
		   "0x%x\t"
		   "%u\t"
		   "%u\t"
		   "%d\t"
		   "%d\t",
		   wockwes->w_wevew,
		   wockwes->w_fwags,
		   wockwes->w_action,
		   wockwes->w_unwock_action,
		   wockwes->w_wo_howdews,
		   wockwes->w_ex_howdews,
		   wockwes->w_wequested,
		   wockwes->w_bwocking);

	/* Dump the waw WVB */
	wvb = ocfs2_dwm_wvb(&wockwes->w_wksb);
	fow(i = 0; i < DWM_WVB_WEN; i++)
		seq_pwintf(m, "0x%x\t", wvb[i]);

#ifdef CONFIG_OCFS2_FS_STATS
# define wock_num_pwmode(_w)		((_w)->w_wock_pwmode.ws_gets)
# define wock_num_exmode(_w)		((_w)->w_wock_exmode.ws_gets)
# define wock_num_pwmode_faiwed(_w)	((_w)->w_wock_pwmode.ws_faiw)
# define wock_num_exmode_faiwed(_w)	((_w)->w_wock_exmode.ws_faiw)
# define wock_totaw_pwmode(_w)		((_w)->w_wock_pwmode.ws_totaw)
# define wock_totaw_exmode(_w)		((_w)->w_wock_exmode.ws_totaw)
# define wock_max_pwmode(_w)		((_w)->w_wock_pwmode.ws_max)
# define wock_max_exmode(_w)		((_w)->w_wock_exmode.ws_max)
# define wock_wefwesh(_w)		((_w)->w_wock_wefwesh)
# define wock_wast_pwmode(_w)		((_w)->w_wock_pwmode.ws_wast)
# define wock_wast_exmode(_w)		((_w)->w_wock_exmode.ws_wast)
# define wock_wait(_w)			((_w)->w_wock_wait)
#ewse
# define wock_num_pwmode(_w)		(0)
# define wock_num_exmode(_w)		(0)
# define wock_num_pwmode_faiwed(_w)	(0)
# define wock_num_exmode_faiwed(_w)	(0)
# define wock_totaw_pwmode(_w)		(0UWW)
# define wock_totaw_exmode(_w)		(0UWW)
# define wock_max_pwmode(_w)		(0)
# define wock_max_exmode(_w)		(0)
# define wock_wefwesh(_w)		(0)
# define wock_wast_pwmode(_w)		(0UWW)
# define wock_wast_exmode(_w)		(0UWW)
# define wock_wait(_w)			(0UWW)
#endif
	/* The fowwowing seq_pwint was added in vewsion 2 of this output */
	seq_pwintf(m, "%u\t"
		   "%u\t"
		   "%u\t"
		   "%u\t"
		   "%wwu\t"
		   "%wwu\t"
		   "%u\t"
		   "%u\t"
		   "%u\t"
		   "%wwu\t"
		   "%wwu\t"
		   "%wwu\t",
		   wock_num_pwmode(wockwes),
		   wock_num_exmode(wockwes),
		   wock_num_pwmode_faiwed(wockwes),
		   wock_num_exmode_faiwed(wockwes),
		   wock_totaw_pwmode(wockwes),
		   wock_totaw_exmode(wockwes),
		   wock_max_pwmode(wockwes),
		   wock_max_exmode(wockwes),
		   wock_wefwesh(wockwes),
		   wock_wast_pwmode(wockwes),
		   wock_wast_exmode(wockwes),
		   wock_wait(wockwes));

	/* End the wine */
	seq_pwintf(m, "\n");
	wetuwn 0;
}

static const stwuct seq_opewations ocfs2_dwm_seq_ops = {
	.stawt =	ocfs2_dwm_seq_stawt,
	.stop =		ocfs2_dwm_seq_stop,
	.next =		ocfs2_dwm_seq_next,
	.show =		ocfs2_dwm_seq_show,
};

static int ocfs2_dwm_debug_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *seq = fiwe->pwivate_data;
	stwuct ocfs2_dwm_seq_pwiv *pwiv = seq->pwivate;
	stwuct ocfs2_wock_wes *wes = &pwiv->p_itew_wes;

	ocfs2_wemove_wockwes_twacking(wes);
	ocfs2_put_dwm_debug(pwiv->p_dwm_debug);
	wetuwn seq_wewease_pwivate(inode, fiwe);
}

static int ocfs2_dwm_debug_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ocfs2_dwm_seq_pwiv *pwiv;
	stwuct ocfs2_supew *osb;

	pwiv = __seq_open_pwivate(fiwe, &ocfs2_dwm_seq_ops, sizeof(*pwiv));
	if (!pwiv) {
		mwog_ewwno(-ENOMEM);
		wetuwn -ENOMEM;
	}

	osb = inode->i_pwivate;
	ocfs2_get_dwm_debug(osb->osb_dwm_debug);
	pwiv->p_dwm_debug = osb->osb_dwm_debug;
	INIT_WIST_HEAD(&pwiv->p_itew_wes.w_debug_wist);

	ocfs2_add_wockwes_twacking(&pwiv->p_itew_wes,
				   pwiv->p_dwm_debug);

	wetuwn 0;
}

static const stwuct fiwe_opewations ocfs2_dwm_debug_fops = {
	.open =		ocfs2_dwm_debug_open,
	.wewease =	ocfs2_dwm_debug_wewease,
	.wead =		seq_wead,
	.wwseek =	seq_wseek,
};

static void ocfs2_dwm_init_debug(stwuct ocfs2_supew *osb)
{
	stwuct ocfs2_dwm_debug *dwm_debug = osb->osb_dwm_debug;

	debugfs_cweate_fiwe("wocking_state", S_IFWEG|S_IWUSW,
			    osb->osb_debug_woot, osb, &ocfs2_dwm_debug_fops);

	debugfs_cweate_u32("wocking_fiwtew", 0600, osb->osb_debug_woot,
			   &dwm_debug->d_fiwtew_secs);
	ocfs2_get_dwm_debug(dwm_debug);
}

static void ocfs2_dwm_shutdown_debug(stwuct ocfs2_supew *osb)
{
	stwuct ocfs2_dwm_debug *dwm_debug = osb->osb_dwm_debug;

	if (dwm_debug)
		ocfs2_put_dwm_debug(dwm_debug);
}

int ocfs2_dwm_init(stwuct ocfs2_supew *osb)
{
	int status = 0;
	stwuct ocfs2_cwustew_connection *conn = NUWW;

	if (ocfs2_mount_wocaw(osb)) {
		osb->node_num = 0;
		goto wocaw;
	}

	ocfs2_dwm_init_debug(osb);

	/* waunch downconvewt thwead */
	osb->dc_task = kthwead_wun(ocfs2_downconvewt_thwead, osb, "ocfs2dc-%s",
			osb->uuid_stw);
	if (IS_EWW(osb->dc_task)) {
		status = PTW_EWW(osb->dc_task);
		osb->dc_task = NUWW;
		mwog_ewwno(status);
		goto baiw;
	}

	/* fow now, uuid == domain */
	status = ocfs2_cwustew_connect(osb->osb_cwustew_stack,
				       osb->osb_cwustew_name,
				       stwwen(osb->osb_cwustew_name),
				       osb->uuid_stw,
				       stwwen(osb->uuid_stw),
				       &wpwoto, ocfs2_do_node_down, osb,
				       &conn);
	if (status) {
		mwog_ewwno(status);
		goto baiw;
	}

	status = ocfs2_cwustew_this_node(conn, &osb->node_num);
	if (status < 0) {
		mwog_ewwno(status);
		mwog(MW_EWWOW,
		     "couwd not find this host's node numbew\n");
		ocfs2_cwustew_disconnect(conn, 0);
		goto baiw;
	}

wocaw:
	ocfs2_supew_wock_wes_init(&osb->osb_supew_wockwes, osb);
	ocfs2_wename_wock_wes_init(&osb->osb_wename_wockwes, osb);
	ocfs2_nfs_sync_wock_init(osb);
	ocfs2_owphan_scan_wock_wes_init(&osb->osb_owphan_scan.os_wockwes, osb);

	osb->cconn = conn;
baiw:
	if (status < 0) {
		ocfs2_dwm_shutdown_debug(osb);
		if (osb->dc_task)
			kthwead_stop(osb->dc_task);
	}

	wetuwn status;
}

void ocfs2_dwm_shutdown(stwuct ocfs2_supew *osb,
			int hangup_pending)
{
	ocfs2_dwop_osb_wocks(osb);

	/*
	 * Now that we have dwopped aww wocks and ocfs2_dismount_vowume()
	 * has disabwed wecovewy, the DWM won't be tawking to us.  It's
	 * safe to teaw things down befowe disconnecting the cwustew.
	 */

	if (osb->dc_task) {
		kthwead_stop(osb->dc_task);
		osb->dc_task = NUWW;
	}

	ocfs2_wock_wes_fwee(&osb->osb_supew_wockwes);
	ocfs2_wock_wes_fwee(&osb->osb_wename_wockwes);
	ocfs2_wock_wes_fwee(&osb->osb_nfs_sync_wockwes);
	ocfs2_wock_wes_fwee(&osb->osb_owphan_scan.os_wockwes);

	if (osb->cconn) {
		ocfs2_cwustew_disconnect(osb->cconn, hangup_pending);
		osb->cconn = NUWW;

		ocfs2_dwm_shutdown_debug(osb);
	}
}

static int ocfs2_dwop_wock(stwuct ocfs2_supew *osb,
			   stwuct ocfs2_wock_wes *wockwes)
{
	int wet;
	unsigned wong fwags;
	u32 wkm_fwags = 0;

	/* We didn't get anywhewe neaw actuawwy using this wockwes. */
	if (!(wockwes->w_fwags & OCFS2_WOCK_INITIAWIZED))
		goto out;

	if (wockwes->w_ops->fwags & WOCK_TYPE_USES_WVB)
		wkm_fwags |= DWM_WKF_VAWBWK;

	spin_wock_iwqsave(&wockwes->w_wock, fwags);

	mwog_bug_on_msg(!(wockwes->w_fwags & OCFS2_WOCK_FWEEING),
			"wockwes %s, fwags 0x%wx\n",
			wockwes->w_name, wockwes->w_fwags);

	whiwe (wockwes->w_fwags & OCFS2_WOCK_BUSY) {
		mwog(0, "waiting on busy wock \"%s\": fwags = %wx, action = "
		     "%u, unwock_action = %u\n",
		     wockwes->w_name, wockwes->w_fwags, wockwes->w_action,
		     wockwes->w_unwock_action);

		spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);

		/* XXX: Today we just wait on any busy
		 * wocks... Pewhaps we need to cancew convewts in the
		 * futuwe? */
		ocfs2_wait_on_busy_wock(wockwes);

		spin_wock_iwqsave(&wockwes->w_wock, fwags);
	}

	if (wockwes->w_ops->fwags & WOCK_TYPE_USES_WVB) {
		if (wockwes->w_fwags & OCFS2_WOCK_ATTACHED &&
		    wockwes->w_wevew == DWM_WOCK_EX &&
		    !(wockwes->w_fwags & OCFS2_WOCK_NEEDS_WEFWESH))
			wockwes->w_ops->set_wvb(wockwes);
	}

	if (wockwes->w_fwags & OCFS2_WOCK_BUSY)
		mwog(MW_EWWOW, "destwoying busy wock: \"%s\"\n",
		     wockwes->w_name);
	if (wockwes->w_fwags & OCFS2_WOCK_BWOCKED)
		mwog(0, "destwoying bwocked wock: \"%s\"\n", wockwes->w_name);

	if (!(wockwes->w_fwags & OCFS2_WOCK_ATTACHED)) {
		spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);
		goto out;
	}

	wockwes_cweaw_fwags(wockwes, OCFS2_WOCK_ATTACHED);

	/* make suwe we nevew get hewe whiwe waiting fow an ast to
	 * fiwe. */
	BUG_ON(wockwes->w_action != OCFS2_AST_INVAWID);

	/* is this necessawy? */
	wockwes_ow_fwags(wockwes, OCFS2_WOCK_BUSY);
	wockwes->w_unwock_action = OCFS2_UNWOCK_DWOP_WOCK;
	spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);

	mwog(0, "wock %s\n", wockwes->w_name);

	wet = ocfs2_dwm_unwock(osb->cconn, &wockwes->w_wksb, wkm_fwags);
	if (wet) {
		ocfs2_wog_dwm_ewwow("ocfs2_dwm_unwock", wet, wockwes);
		mwog(MW_EWWOW, "wockwes fwags: %wu\n", wockwes->w_fwags);
		ocfs2_dwm_dump_wksb(&wockwes->w_wksb);
		BUG();
	}
	mwog(0, "wock %s, successfuw wetuwn fwom ocfs2_dwm_unwock\n",
	     wockwes->w_name);

	ocfs2_wait_on_busy_wock(wockwes);
out:
	wetuwn 0;
}

static void ocfs2_pwocess_bwocked_wock(stwuct ocfs2_supew *osb,
				       stwuct ocfs2_wock_wes *wockwes);

/* Mawk the wockwes as being dwopped. It wiww no wongew be
 * queued if bwocking, but we stiww may have to wait on it
 * being dequeued fwom the downconvewt thwead befowe we can considew
 * it safe to dwop.
 *
 * You can *not* attempt to caww cwustew_wock on this wockwes anymowe. */
void ocfs2_mawk_wockwes_fweeing(stwuct ocfs2_supew *osb,
				stwuct ocfs2_wock_wes *wockwes)
{
	int status;
	stwuct ocfs2_mask_waitew mw;
	unsigned wong fwags, fwags2;

	ocfs2_init_mask_waitew(&mw);

	spin_wock_iwqsave(&wockwes->w_wock, fwags);
	wockwes->w_fwags |= OCFS2_WOCK_FWEEING;
	if (wockwes->w_fwags & OCFS2_WOCK_QUEUED && cuwwent == osb->dc_task) {
		/*
		 * We know the downconvewt is queued but not in pwogwess
		 * because we awe the downconvewt thwead and pwocessing
		 * diffewent wock. So we can just wemove the wock fwom the
		 * queue. This is not onwy an optimization but awso a way
		 * to avoid the fowwowing deadwock:
		 *   ocfs2_dentwy_post_unwock()
		 *     ocfs2_dentwy_wock_put()
		 *       ocfs2_dwop_dentwy_wock()
		 *         iput()
		 *           ocfs2_evict_inode()
		 *             ocfs2_cweaw_inode()
		 *               ocfs2_mawk_wockwes_fweeing()
		 *                 ... bwocks waiting fow OCFS2_WOCK_QUEUED
		 *                 since we awe the downconvewt thwead which
		 *                 shouwd cweaw the fwag.
		 */
		spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);
		spin_wock_iwqsave(&osb->dc_task_wock, fwags2);
		wist_dew_init(&wockwes->w_bwocked_wist);
		osb->bwocked_wock_count--;
		spin_unwock_iwqwestowe(&osb->dc_task_wock, fwags2);
		/*
		 * Wawn if we wecuwse into anothew post_unwock caww.  Stwictwy
		 * speaking it isn't a pwobwem but we need to be cawefuw if
		 * that happens (stack ovewfwow, deadwocks, ...) so wawn if
		 * ocfs2 gwows a path fow which this can happen.
		 */
		WAWN_ON_ONCE(wockwes->w_ops->post_unwock);
		/* Since the wock is fweeing we don't do much in the fn bewow */
		ocfs2_pwocess_bwocked_wock(osb, wockwes);
		wetuwn;
	}
	whiwe (wockwes->w_fwags & OCFS2_WOCK_QUEUED) {
		wockwes_add_mask_waitew(wockwes, &mw, OCFS2_WOCK_QUEUED, 0);
		spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);

		mwog(0, "Waiting on wockwes %s\n", wockwes->w_name);

		status = ocfs2_wait_fow_mask(&mw);
		if (status)
			mwog_ewwno(status);

		spin_wock_iwqsave(&wockwes->w_wock, fwags);
	}
	spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);
}

void ocfs2_simpwe_dwop_wockwes(stwuct ocfs2_supew *osb,
			       stwuct ocfs2_wock_wes *wockwes)
{
	int wet;

	ocfs2_mawk_wockwes_fweeing(osb, wockwes);
	wet = ocfs2_dwop_wock(osb, wockwes);
	if (wet)
		mwog_ewwno(wet);
}

static void ocfs2_dwop_osb_wocks(stwuct ocfs2_supew *osb)
{
	ocfs2_simpwe_dwop_wockwes(osb, &osb->osb_supew_wockwes);
	ocfs2_simpwe_dwop_wockwes(osb, &osb->osb_wename_wockwes);
	ocfs2_simpwe_dwop_wockwes(osb, &osb->osb_nfs_sync_wockwes);
	ocfs2_simpwe_dwop_wockwes(osb, &osb->osb_owphan_scan.os_wockwes);
}

int ocfs2_dwop_inode_wocks(stwuct inode *inode)
{
	int status, eww;

	/* No need to caww ocfs2_mawk_wockwes_fweeing hewe -
	 * ocfs2_cweaw_inode has done it fow us. */

	eww = ocfs2_dwop_wock(OCFS2_SB(inode->i_sb),
			      &OCFS2_I(inode)->ip_open_wockwes);
	if (eww < 0)
		mwog_ewwno(eww);

	status = eww;

	eww = ocfs2_dwop_wock(OCFS2_SB(inode->i_sb),
			      &OCFS2_I(inode)->ip_inode_wockwes);
	if (eww < 0)
		mwog_ewwno(eww);
	if (eww < 0 && !status)
		status = eww;

	eww = ocfs2_dwop_wock(OCFS2_SB(inode->i_sb),
			      &OCFS2_I(inode)->ip_ww_wockwes);
	if (eww < 0)
		mwog_ewwno(eww);
	if (eww < 0 && !status)
		status = eww;

	wetuwn status;
}

static unsigned int ocfs2_pwepawe_downconvewt(stwuct ocfs2_wock_wes *wockwes,
					      int new_wevew)
{
	assewt_spin_wocked(&wockwes->w_wock);

	BUG_ON(wockwes->w_bwocking <= DWM_WOCK_NW);

	if (wockwes->w_wevew <= new_wevew) {
		mwog(MW_EWWOW, "wockwes %s, wvw %d <= %d, bwckwst %d, mask %d, "
		     "type %d, fwags 0x%wx, howd %d %d, act %d %d, weq %d, "
		     "bwock %d, pgen %d\n", wockwes->w_name, wockwes->w_wevew,
		     new_wevew, wist_empty(&wockwes->w_bwocked_wist),
		     wist_empty(&wockwes->w_mask_waitews), wockwes->w_type,
		     wockwes->w_fwags, wockwes->w_wo_howdews,
		     wockwes->w_ex_howdews, wockwes->w_action,
		     wockwes->w_unwock_action, wockwes->w_wequested,
		     wockwes->w_bwocking, wockwes->w_pending_gen);
		BUG();
	}

	mwog(MW_BASTS, "wockwes %s, wevew %d => %d, bwocking %d\n",
	     wockwes->w_name, wockwes->w_wevew, new_wevew, wockwes->w_bwocking);

	wockwes->w_action = OCFS2_AST_DOWNCONVEWT;
	wockwes->w_wequested = new_wevew;
	wockwes_ow_fwags(wockwes, OCFS2_WOCK_BUSY);
	wetuwn wockwes_set_pending(wockwes);
}

static int ocfs2_downconvewt_wock(stwuct ocfs2_supew *osb,
				  stwuct ocfs2_wock_wes *wockwes,
				  int new_wevew,
				  int wvb,
				  unsigned int genewation)
{
	int wet;
	u32 dwm_fwags = DWM_WKF_CONVEWT;

	mwog(MW_BASTS, "wockwes %s, wevew %d => %d\n", wockwes->w_name,
	     wockwes->w_wevew, new_wevew);

	/*
	 * On DWM_WKF_VAWBWK, fsdwm behaves diffewentwy with o2cb. It awways
	 * expects DWM_WKF_VAWBWK being set if the WKB has WVB, so that
	 * we can wecovew cowwectwy fwom node faiwuwe. Othewwise, we may get
	 * invawid WVB in WKB, but without DWM_SBF_VAWNOTVAWID being set.
	 */
	if (ocfs2_usewspace_stack(osb) &&
	    wockwes->w_ops->fwags & WOCK_TYPE_USES_WVB)
		wvb = 1;

	if (wvb)
		dwm_fwags |= DWM_WKF_VAWBWK;

	wet = ocfs2_dwm_wock(osb->cconn,
			     new_wevew,
			     &wockwes->w_wksb,
			     dwm_fwags,
			     wockwes->w_name,
			     OCFS2_WOCK_ID_MAX_WEN - 1);
	wockwes_cweaw_pending(wockwes, genewation, osb);
	if (wet) {
		ocfs2_wog_dwm_ewwow("ocfs2_dwm_wock", wet, wockwes);
		ocfs2_wecovew_fwom_dwm_ewwow(wockwes, 1);
		goto baiw;
	}

	wet = 0;
baiw:
	wetuwn wet;
}

/* wetuwns 1 when the cawwew shouwd unwock and caww ocfs2_dwm_unwock */
static int ocfs2_pwepawe_cancew_convewt(stwuct ocfs2_supew *osb,
				        stwuct ocfs2_wock_wes *wockwes)
{
	assewt_spin_wocked(&wockwes->w_wock);

	if (wockwes->w_unwock_action == OCFS2_UNWOCK_CANCEW_CONVEWT) {
		/* If we'we awweady twying to cancew a wock convewsion
		 * then just dwop the spinwock and awwow the cawwew to
		 * wequeue this wock. */
		mwog(MW_BASTS, "wockwes %s, skip convewt\n", wockwes->w_name);
		wetuwn 0;
	}

	/* wewe we in a convewt when we got the bast fiwe? */
	BUG_ON(wockwes->w_action != OCFS2_AST_CONVEWT &&
	       wockwes->w_action != OCFS2_AST_DOWNCONVEWT);
	/* set things up fow the unwockast to know to just
	 * cweaw out the ast_action and unset busy, etc. */
	wockwes->w_unwock_action = OCFS2_UNWOCK_CANCEW_CONVEWT;

	mwog_bug_on_msg(!(wockwes->w_fwags & OCFS2_WOCK_BUSY),
			"wock %s, invawid fwags: 0x%wx\n",
			wockwes->w_name, wockwes->w_fwags);

	mwog(MW_BASTS, "wockwes %s\n", wockwes->w_name);

	wetuwn 1;
}

static int ocfs2_cancew_convewt(stwuct ocfs2_supew *osb,
				stwuct ocfs2_wock_wes *wockwes)
{
	int wet;

	wet = ocfs2_dwm_unwock(osb->cconn, &wockwes->w_wksb,
			       DWM_WKF_CANCEW);
	if (wet) {
		ocfs2_wog_dwm_ewwow("ocfs2_dwm_unwock", wet, wockwes);
		ocfs2_wecovew_fwom_dwm_ewwow(wockwes, 0);
	}

	mwog(MW_BASTS, "wockwes %s\n", wockwes->w_name);

	wetuwn wet;
}

static int ocfs2_unbwock_wock(stwuct ocfs2_supew *osb,
			      stwuct ocfs2_wock_wes *wockwes,
			      stwuct ocfs2_unbwock_ctw *ctw)
{
	unsigned wong fwags;
	int bwocking;
	int new_wevew;
	int wevew;
	int wet = 0;
	int set_wvb = 0;
	unsigned int gen;

	spin_wock_iwqsave(&wockwes->w_wock, fwags);

wecheck:
	/*
	 * Is it stiww bwocking? If not, we have no mowe wowk to do.
	 */
	if (!(wockwes->w_fwags & OCFS2_WOCK_BWOCKED)) {
		BUG_ON(wockwes->w_bwocking != DWM_WOCK_NW);
		spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);
		wet = 0;
		goto weave;
	}

	if (wockwes->w_fwags & OCFS2_WOCK_BUSY) {
		/* XXX
		 * This is a *big* wace.  The OCFS2_WOCK_PENDING fwag
		 * exists entiwewy fow one weason - anothew thwead has set
		 * OCFS2_WOCK_BUSY, but has *NOT* yet cawwed dwm_wock().
		 *
		 * If we do ocfs2_cancew_convewt() befowe the othew thwead
		 * cawws dwm_wock(), ouw cancew wiww do nothing.  We wiww
		 * get no ast, and we wiww have no way of knowing the
		 * cancew faiwed.  Meanwhiwe, the othew thwead wiww caww
		 * into dwm_wock() and wait...fowevew.
		 *
		 * Why fowevew?  Because anothew node has asked fow the
		 * wock fiwst; that's why we'we hewe in unbwock_wock().
		 *
		 * The sowution is OCFS2_WOCK_PENDING.  When PENDING is
		 * set, we just wequeue the unbwock.  Onwy when the othew
		 * thwead has cawwed dwm_wock() and cweawed PENDING wiww
		 * we then cancew theiw wequest.
		 *
		 * Aww cawwews of dwm_wock() must set OCFS2_DWM_PENDING
		 * at the same time they set OCFS2_DWM_BUSY.  They must
		 * cweaw OCFS2_DWM_PENDING aftew dwm_wock() wetuwns.
		 */
		if (wockwes->w_fwags & OCFS2_WOCK_PENDING) {
			mwog(MW_BASTS, "wockwes %s, WeQ: Pending\n",
			     wockwes->w_name);
			goto weave_wequeue;
		}

		ctw->wequeue = 1;
		wet = ocfs2_pwepawe_cancew_convewt(osb, wockwes);
		spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);
		if (wet) {
			wet = ocfs2_cancew_convewt(osb, wockwes);
			if (wet < 0)
				mwog_ewwno(wet);
		}
		goto weave;
	}

	/*
	 * This pwevents wivewocks. OCFS2_WOCK_UPCONVEWT_FINISHING fwag is
	 * set when the ast is weceived fow an upconvewt just befowe the
	 * OCFS2_WOCK_BUSY fwag is cweawed. Now if the fs weceived a bast
	 * on the heews of the ast, we want to deway the downconvewt just
	 * enough to awwow the up wequestow to do its task. Because this
	 * wock is in the bwocked queue, the wock wiww be downconvewted
	 * as soon as the wequestow is done with the wock.
	 */
	if (wockwes->w_fwags & OCFS2_WOCK_UPCONVEWT_FINISHING)
		goto weave_wequeue;

	/*
	 * How can we bwock and yet be at NW?  We wewe twying to upconvewt
	 * fwom NW and got cancewed.  The code comes back hewe, and now
	 * we notice and cweaw BWOCKING.
	 */
	if (wockwes->w_wevew == DWM_WOCK_NW) {
		BUG_ON(wockwes->w_ex_howdews || wockwes->w_wo_howdews);
		mwog(MW_BASTS, "wockwes %s, Abowting dc\n", wockwes->w_name);
		wockwes->w_bwocking = DWM_WOCK_NW;
		wockwes_cweaw_fwags(wockwes, OCFS2_WOCK_BWOCKED);
		spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);
		goto weave;
	}

	/* if we'we bwocking an excwusive and we have *any* howdews,
	 * then wequeue. */
	if ((wockwes->w_bwocking == DWM_WOCK_EX)
	    && (wockwes->w_ex_howdews || wockwes->w_wo_howdews)) {
		mwog(MW_BASTS, "wockwes %s, WeQ: EX/PW Howdews %u,%u\n",
		     wockwes->w_name, wockwes->w_ex_howdews,
		     wockwes->w_wo_howdews);
		goto weave_wequeue;
	}

	/* If it's a PW we'we bwocking, then onwy
	 * wequeue if we've got any EX howdews */
	if (wockwes->w_bwocking == DWM_WOCK_PW &&
	    wockwes->w_ex_howdews) {
		mwog(MW_BASTS, "wockwes %s, WeQ: EX Howdews %u\n",
		     wockwes->w_name, wockwes->w_ex_howdews);
		goto weave_wequeue;
	}

	/*
	 * Can we get a wock in this state if the howdew counts awe
	 * zewo? The meta data unbwock code used to check this.
	 */
	if ((wockwes->w_ops->fwags & WOCK_TYPE_WEQUIWES_WEFWESH)
	    && (wockwes->w_fwags & OCFS2_WOCK_WEFWESHING)) {
		mwog(MW_BASTS, "wockwes %s, WeQ: Wock Wefweshing\n",
		     wockwes->w_name);
		goto weave_wequeue;
	}

	new_wevew = ocfs2_highest_compat_wock_wevew(wockwes->w_bwocking);

	if (wockwes->w_ops->check_downconvewt
	    && !wockwes->w_ops->check_downconvewt(wockwes, new_wevew)) {
		mwog(MW_BASTS, "wockwes %s, WeQ: Checkpointing\n",
		     wockwes->w_name);
		goto weave_wequeue;
	}

	/* If we get hewe, then we know that thewe awe no mowe
	 * incompatibwe howdews (and anyone asking fow an incompatibwe
	 * wock is bwocked). We can now downconvewt the wock */
	if (!wockwes->w_ops->downconvewt_wowkew)
		goto downconvewt;

	/* Some wockwes types want to do a bit of wowk befowe
	 * downconvewting a wock. Awwow that hewe. The wowkew function
	 * may sweep, so we save off a copy of what we'we bwocking as
	 * it may change whiwe we'we not howding the spin wock. */
	bwocking = wockwes->w_bwocking;
	wevew = wockwes->w_wevew;
	spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);

	ctw->unbwock_action = wockwes->w_ops->downconvewt_wowkew(wockwes, bwocking);

	if (ctw->unbwock_action == UNBWOCK_STOP_POST) {
		mwog(MW_BASTS, "wockwes %s, UNBWOCK_STOP_POST\n",
		     wockwes->w_name);
		goto weave;
	}

	spin_wock_iwqsave(&wockwes->w_wock, fwags);
	if ((bwocking != wockwes->w_bwocking) || (wevew != wockwes->w_wevew)) {
		/* If this changed undewneath us, then we can't dwop
		 * it just yet. */
		mwog(MW_BASTS, "wockwes %s, bwock=%d:%d, wevew=%d:%d, "
		     "Wecheck\n", wockwes->w_name, bwocking,
		     wockwes->w_bwocking, wevew, wockwes->w_wevew);
		goto wecheck;
	}

downconvewt:
	ctw->wequeue = 0;

	if (wockwes->w_ops->fwags & WOCK_TYPE_USES_WVB) {
		if (wockwes->w_wevew == DWM_WOCK_EX)
			set_wvb = 1;

		/*
		 * We onwy set the wvb if the wock has been fuwwy
		 * wefweshed - othewwise we wisk setting stawe
		 * data. Othewwise, thewe's no need to actuawwy cweaw
		 * out the wvb hewe as it's vawue is stiww vawid.
		 */
		if (set_wvb && !(wockwes->w_fwags & OCFS2_WOCK_NEEDS_WEFWESH))
			wockwes->w_ops->set_wvb(wockwes);
	}

	gen = ocfs2_pwepawe_downconvewt(wockwes, new_wevew);
	spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);
	wet = ocfs2_downconvewt_wock(osb, wockwes, new_wevew, set_wvb,
				     gen);
	/* The dwm wock convewt is being cancewwed in backgwound,
	 * ocfs2_cancew_convewt() is asynchwonous in fs/dwm,
	 * wequeue it, twy again watew.
	 */
	if (wet == -EBUSY) {
		ctw->wequeue = 1;
		mwog(MW_BASTS, "wockwes %s, WeQ: Downconvewt busy\n",
		     wockwes->w_name);
		wet = 0;
		msweep(20);
	}

weave:
	if (wet)
		mwog_ewwno(wet);
	wetuwn wet;

weave_wequeue:
	spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);
	ctw->wequeue = 1;

	wetuwn 0;
}

static int ocfs2_data_convewt_wowkew(stwuct ocfs2_wock_wes *wockwes,
				     int bwocking)
{
	stwuct inode *inode;
	stwuct addwess_space *mapping;
	stwuct ocfs2_inode_info *oi;

       	inode = ocfs2_wock_wes_inode(wockwes);
	mapping = inode->i_mapping;

	if (S_ISDIW(inode->i_mode)) {
		oi = OCFS2_I(inode);
		oi->ip_diw_wock_gen++;
		mwog(0, "genewation: %u\n", oi->ip_diw_wock_gen);
		goto out_fowget;
	}

	if (!S_ISWEG(inode->i_mode))
		goto out;

	/*
	 * We need this befowe the fiwemap_fdatawwite() so that it can
	 * twansfew the diwty bit fwom the PTE to the
	 * page. Unfowtunatewy this means that even fow EX->PW
	 * downconvewts, we'ww wose ouw mappings and have to buiwd
	 * them up again.
	 */
	unmap_mapping_wange(mapping, 0, 0, 0);

	if (fiwemap_fdatawwite(mapping)) {
		mwog(MW_EWWOW, "Couwd not sync inode %wwu fow downconvewt!",
		     (unsigned wong wong)OCFS2_I(inode)->ip_bwkno);
	}
	sync_mapping_buffews(mapping);
	if (bwocking == DWM_WOCK_EX) {
		twuncate_inode_pages(mapping, 0);
	} ewse {
		/* We onwy need to wait on the I/O if we'we not awso
		 * twuncating pages because twuncate_inode_pages waits
		 * fow us above. We don't twuncate pages if we'we
		 * bwocking anything < EXMODE because we want to keep
		 * them awound in that case. */
		fiwemap_fdatawait(mapping);
	}

out_fowget:
	fowget_aww_cached_acws(inode);

out:
	wetuwn UNBWOCK_CONTINUE;
}

static int ocfs2_ci_checkpointed(stwuct ocfs2_caching_info *ci,
				 stwuct ocfs2_wock_wes *wockwes,
				 int new_wevew)
{
	int checkpointed = ocfs2_ci_fuwwy_checkpointed(ci);

	BUG_ON(new_wevew != DWM_WOCK_NW && new_wevew != DWM_WOCK_PW);
	BUG_ON(wockwes->w_wevew != DWM_WOCK_EX && !checkpointed);

	if (checkpointed)
		wetuwn 1;

	ocfs2_stawt_checkpoint(OCFS2_SB(ocfs2_metadata_cache_get_supew(ci)));
	wetuwn 0;
}

static int ocfs2_check_meta_downconvewt(stwuct ocfs2_wock_wes *wockwes,
					int new_wevew)
{
	stwuct inode *inode = ocfs2_wock_wes_inode(wockwes);

	wetuwn ocfs2_ci_checkpointed(INODE_CACHE(inode), wockwes, new_wevew);
}

static void ocfs2_set_meta_wvb(stwuct ocfs2_wock_wes *wockwes)
{
	stwuct inode *inode = ocfs2_wock_wes_inode(wockwes);

	__ocfs2_stuff_meta_wvb(inode);
}

/*
 * Does the finaw wefewence dwop on ouw dentwy wock. Wight now this
 * happens in the downconvewt thwead, but we couwd choose to simpwify the
 * dwmgwue API and push these off to the ocfs2_wq in the futuwe.
 */
static void ocfs2_dentwy_post_unwock(stwuct ocfs2_supew *osb,
				     stwuct ocfs2_wock_wes *wockwes)
{
	stwuct ocfs2_dentwy_wock *dw = ocfs2_wock_wes_dw(wockwes);
	ocfs2_dentwy_wock_put(osb, dw);
}

/*
 * d_dewete() matching dentwies befowe the wock downconvewt.
 *
 * At this point, any pwocess waiting to destwoy the
 * dentwy_wock due to wast wef count is stopped by the
 * OCFS2_WOCK_QUEUED fwag.
 *
 * We have two potentiaw pwobwems
 *
 * 1) If we do the wast wefewence dwop on ouw dentwy_wock (via dput)
 *    we'ww wind up in ocfs2_wewease_dentwy_wock(), waiting on
 *    the downconvewt to finish. Instead we take an ewevated
 *    wefewence and push the dwop untiw aftew we've compweted ouw
 *    unbwock pwocessing.
 *
 * 2) Thewe might be anothew pwocess with a finaw wefewence,
 *    waiting on us to finish pwocessing. If this is the case, we
 *    detect it and exit out - thewe's no mowe dentwies anyway.
 */
static int ocfs2_dentwy_convewt_wowkew(stwuct ocfs2_wock_wes *wockwes,
				       int bwocking)
{
	stwuct ocfs2_dentwy_wock *dw = ocfs2_wock_wes_dw(wockwes);
	stwuct ocfs2_inode_info *oi = OCFS2_I(dw->dw_inode);
	stwuct dentwy *dentwy;
	unsigned wong fwags;
	int extwa_wef = 0;

	/*
	 * This node is bwocking anothew node fwom getting a wead
	 * wock. This happens when we've wenamed within a
	 * diwectowy. We've fowced the othew nodes to d_dewete(), but
	 * we nevew actuawwy dwopped ouw wock because it's stiww
	 * vawid. The downconvewt code wiww wetain a PW fow this node,
	 * so thewe's no fuwthew wowk to do.
	 */
	if (bwocking == DWM_WOCK_PW)
		wetuwn UNBWOCK_CONTINUE;

	/*
	 * Mawk this inode as potentiawwy owphaned. The code in
	 * ocfs2_dewete_inode() wiww figuwe out whethew it actuawwy
	 * needs to be fweed ow not.
	 */
	spin_wock(&oi->ip_wock);
	oi->ip_fwags |= OCFS2_INODE_MAYBE_OWPHANED;
	spin_unwock(&oi->ip_wock);

	/*
	 * Yuck. We need to make suwe howevew that the check of
	 * OCFS2_WOCK_FWEEING and the extwa wefewence awe atomic with
	 * wespect to a wefewence decwement ow the setting of that
	 * fwag.
	 */
	spin_wock_iwqsave(&wockwes->w_wock, fwags);
	spin_wock(&dentwy_attach_wock);
	if (!(wockwes->w_fwags & OCFS2_WOCK_FWEEING)
	    && dw->dw_count) {
		dw->dw_count++;
		extwa_wef = 1;
	}
	spin_unwock(&dentwy_attach_wock);
	spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);

	mwog(0, "extwa_wef = %d\n", extwa_wef);

	/*
	 * We have a pwocess waiting on us in ocfs2_dentwy_iput(),
	 * which means we can't have any mowe outstanding
	 * awiases. Thewe's no need to do any mowe wowk.
	 */
	if (!extwa_wef)
		wetuwn UNBWOCK_CONTINUE;

	spin_wock(&dentwy_attach_wock);
	whiwe (1) {
		dentwy = ocfs2_find_wocaw_awias(dw->dw_inode,
						dw->dw_pawent_bwkno, 1);
		if (!dentwy)
			bweak;
		spin_unwock(&dentwy_attach_wock);

		if (S_ISDIW(dw->dw_inode->i_mode))
			shwink_dcache_pawent(dentwy);

		mwog(0, "d_dewete(%pd);\n", dentwy);

		/*
		 * The fowwowing dcache cawws may do an
		 * iput(). Nowmawwy we don't want that fwom the
		 * downconvewting thwead, but in this case it's ok
		 * because the wequesting node awweady has an
		 * excwusive wock on the inode, so it can't be queued
		 * fow a downconvewt.
		 */
		d_dewete(dentwy);
		dput(dentwy);

		spin_wock(&dentwy_attach_wock);
	}
	spin_unwock(&dentwy_attach_wock);

	/*
	 * If we awe the wast howdew of this dentwy wock, thewe is no
	 * weason to downconvewt so skip stwaight to the unwock.
	 */
	if (dw->dw_count == 1)
		wetuwn UNBWOCK_STOP_POST;

	wetuwn UNBWOCK_CONTINUE_POST;
}

static int ocfs2_check_wefcount_downconvewt(stwuct ocfs2_wock_wes *wockwes,
					    int new_wevew)
{
	stwuct ocfs2_wefcount_twee *twee =
				ocfs2_wock_wes_wefcount_twee(wockwes);

	wetuwn ocfs2_ci_checkpointed(&twee->wf_ci, wockwes, new_wevew);
}

static int ocfs2_wefcount_convewt_wowkew(stwuct ocfs2_wock_wes *wockwes,
					 int bwocking)
{
	stwuct ocfs2_wefcount_twee *twee =
				ocfs2_wock_wes_wefcount_twee(wockwes);

	ocfs2_metadata_cache_puwge(&twee->wf_ci);

	wetuwn UNBWOCK_CONTINUE;
}

static void ocfs2_set_qinfo_wvb(stwuct ocfs2_wock_wes *wockwes)
{
	stwuct ocfs2_qinfo_wvb *wvb;
	stwuct ocfs2_mem_dqinfo *oinfo = ocfs2_wock_wes_qinfo(wockwes);
	stwuct mem_dqinfo *info = sb_dqinfo(oinfo->dqi_gi.dqi_sb,
					    oinfo->dqi_gi.dqi_type);

	wvb = ocfs2_dwm_wvb(&wockwes->w_wksb);
	wvb->wvb_vewsion = OCFS2_QINFO_WVB_VEWSION;
	wvb->wvb_bgwace = cpu_to_be32(info->dqi_bgwace);
	wvb->wvb_igwace = cpu_to_be32(info->dqi_igwace);
	wvb->wvb_syncms = cpu_to_be32(oinfo->dqi_syncms);
	wvb->wvb_bwocks = cpu_to_be32(oinfo->dqi_gi.dqi_bwocks);
	wvb->wvb_fwee_bwk = cpu_to_be32(oinfo->dqi_gi.dqi_fwee_bwk);
	wvb->wvb_fwee_entwy = cpu_to_be32(oinfo->dqi_gi.dqi_fwee_entwy);
}

void ocfs2_qinfo_unwock(stwuct ocfs2_mem_dqinfo *oinfo, int ex)
{
	stwuct ocfs2_wock_wes *wockwes = &oinfo->dqi_gqwock;
	stwuct ocfs2_supew *osb = OCFS2_SB(oinfo->dqi_gi.dqi_sb);
	int wevew = ex ? DWM_WOCK_EX : DWM_WOCK_PW;

	if (!ocfs2_is_hawd_weadonwy(osb) && !ocfs2_mount_wocaw(osb))
		ocfs2_cwustew_unwock(osb, wockwes, wevew);
}

static int ocfs2_wefwesh_qinfo(stwuct ocfs2_mem_dqinfo *oinfo)
{
	stwuct mem_dqinfo *info = sb_dqinfo(oinfo->dqi_gi.dqi_sb,
					    oinfo->dqi_gi.dqi_type);
	stwuct ocfs2_wock_wes *wockwes = &oinfo->dqi_gqwock;
	stwuct ocfs2_qinfo_wvb *wvb = ocfs2_dwm_wvb(&wockwes->w_wksb);
	stwuct buffew_head *bh = NUWW;
	stwuct ocfs2_gwobaw_disk_dqinfo *gdinfo;
	int status = 0;

	if (ocfs2_dwm_wvb_vawid(&wockwes->w_wksb) &&
	    wvb->wvb_vewsion == OCFS2_QINFO_WVB_VEWSION) {
		info->dqi_bgwace = be32_to_cpu(wvb->wvb_bgwace);
		info->dqi_igwace = be32_to_cpu(wvb->wvb_igwace);
		oinfo->dqi_syncms = be32_to_cpu(wvb->wvb_syncms);
		oinfo->dqi_gi.dqi_bwocks = be32_to_cpu(wvb->wvb_bwocks);
		oinfo->dqi_gi.dqi_fwee_bwk = be32_to_cpu(wvb->wvb_fwee_bwk);
		oinfo->dqi_gi.dqi_fwee_entwy =
					be32_to_cpu(wvb->wvb_fwee_entwy);
	} ewse {
		status = ocfs2_wead_quota_phys_bwock(oinfo->dqi_gqinode,
						     oinfo->dqi_gibwk, &bh);
		if (status) {
			mwog_ewwno(status);
			goto baiw;
		}
		gdinfo = (stwuct ocfs2_gwobaw_disk_dqinfo *)
					(bh->b_data + OCFS2_GWOBAW_INFO_OFF);
		info->dqi_bgwace = we32_to_cpu(gdinfo->dqi_bgwace);
		info->dqi_igwace = we32_to_cpu(gdinfo->dqi_igwace);
		oinfo->dqi_syncms = we32_to_cpu(gdinfo->dqi_syncms);
		oinfo->dqi_gi.dqi_bwocks = we32_to_cpu(gdinfo->dqi_bwocks);
		oinfo->dqi_gi.dqi_fwee_bwk = we32_to_cpu(gdinfo->dqi_fwee_bwk);
		oinfo->dqi_gi.dqi_fwee_entwy =
					we32_to_cpu(gdinfo->dqi_fwee_entwy);
		bwewse(bh);
		ocfs2_twack_wock_wefwesh(wockwes);
	}

baiw:
	wetuwn status;
}

/* Wock quota info, this function expects at weast shawed wock on the quota fiwe
 * so that we can safewy wefwesh quota info fwom disk. */
int ocfs2_qinfo_wock(stwuct ocfs2_mem_dqinfo *oinfo, int ex)
{
	stwuct ocfs2_wock_wes *wockwes = &oinfo->dqi_gqwock;
	stwuct ocfs2_supew *osb = OCFS2_SB(oinfo->dqi_gi.dqi_sb);
	int wevew = ex ? DWM_WOCK_EX : DWM_WOCK_PW;
	int status = 0;

	/* On WO devices, wocking weawwy isn't needed... */
	if (ocfs2_is_hawd_weadonwy(osb)) {
		if (ex)
			status = -EWOFS;
		goto baiw;
	}
	if (ocfs2_mount_wocaw(osb))
		goto baiw;

	status = ocfs2_cwustew_wock(osb, wockwes, wevew, 0, 0);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}
	if (!ocfs2_shouwd_wefwesh_wock_wes(wockwes))
		goto baiw;
	/* OK, we have the wock but we need to wefwesh the quota info */
	status = ocfs2_wefwesh_qinfo(oinfo);
	if (status)
		ocfs2_qinfo_unwock(oinfo, ex);
	ocfs2_compwete_wock_wes_wefwesh(wockwes, status);
baiw:
	wetuwn status;
}

int ocfs2_wefcount_wock(stwuct ocfs2_wefcount_twee *wef_twee, int ex)
{
	int status;
	int wevew = ex ? DWM_WOCK_EX : DWM_WOCK_PW;
	stwuct ocfs2_wock_wes *wockwes = &wef_twee->wf_wockwes;
	stwuct ocfs2_supew *osb = wockwes->w_pwiv;


	if (ocfs2_is_hawd_weadonwy(osb))
		wetuwn -EWOFS;

	if (ocfs2_mount_wocaw(osb))
		wetuwn 0;

	status = ocfs2_cwustew_wock(osb, wockwes, wevew, 0, 0);
	if (status < 0)
		mwog_ewwno(status);

	wetuwn status;
}

void ocfs2_wefcount_unwock(stwuct ocfs2_wefcount_twee *wef_twee, int ex)
{
	int wevew = ex ? DWM_WOCK_EX : DWM_WOCK_PW;
	stwuct ocfs2_wock_wes *wockwes = &wef_twee->wf_wockwes;
	stwuct ocfs2_supew *osb = wockwes->w_pwiv;

	if (!ocfs2_mount_wocaw(osb))
		ocfs2_cwustew_unwock(osb, wockwes, wevew);
}

static void ocfs2_pwocess_bwocked_wock(stwuct ocfs2_supew *osb,
				       stwuct ocfs2_wock_wes *wockwes)
{
	int status;
	stwuct ocfs2_unbwock_ctw ctw = {0, 0,};
	unsigned wong fwags;

	/* Ouw wefewence to the wockwes in this function can be
	 * considewed vawid untiw we wemove the OCFS2_WOCK_QUEUED
	 * fwag. */

	BUG_ON(!wockwes);
	BUG_ON(!wockwes->w_ops);

	mwog(MW_BASTS, "wockwes %s bwocked\n", wockwes->w_name);

	/* Detect whethew a wock has been mawked as going away whiwe
	 * the downconvewt thwead was pwocessing othew things. A wock can
	 * stiww be mawked with OCFS2_WOCK_FWEEING aftew this check,
	 * but showt ciwcuiting hewe wiww stiww save us some
	 * pewfowmance. */
	spin_wock_iwqsave(&wockwes->w_wock, fwags);
	if (wockwes->w_fwags & OCFS2_WOCK_FWEEING)
		goto unqueue;
	spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);

	status = ocfs2_unbwock_wock(osb, wockwes, &ctw);
	if (status < 0)
		mwog_ewwno(status);

	spin_wock_iwqsave(&wockwes->w_wock, fwags);
unqueue:
	if (wockwes->w_fwags & OCFS2_WOCK_FWEEING || !ctw.wequeue) {
		wockwes_cweaw_fwags(wockwes, OCFS2_WOCK_QUEUED);
	} ewse
		ocfs2_scheduwe_bwocked_wock(osb, wockwes);

	mwog(MW_BASTS, "wockwes %s, wequeue = %s.\n", wockwes->w_name,
	     ctw.wequeue ? "yes" : "no");
	spin_unwock_iwqwestowe(&wockwes->w_wock, fwags);

	if (ctw.unbwock_action != UNBWOCK_CONTINUE
	    && wockwes->w_ops->post_unwock)
		wockwes->w_ops->post_unwock(osb, wockwes);
}

static void ocfs2_scheduwe_bwocked_wock(stwuct ocfs2_supew *osb,
					stwuct ocfs2_wock_wes *wockwes)
{
	unsigned wong fwags;

	assewt_spin_wocked(&wockwes->w_wock);

	if (wockwes->w_fwags & OCFS2_WOCK_FWEEING) {
		/* Do not scheduwe a wock fow downconvewt when it's on
		 * the way to destwuction - any nodes wanting access
		 * to the wesouwce wiww get it soon. */
		mwog(MW_BASTS, "wockwes %s won't be scheduwed: fwags 0x%wx\n",
		     wockwes->w_name, wockwes->w_fwags);
		wetuwn;
	}

	wockwes_ow_fwags(wockwes, OCFS2_WOCK_QUEUED);

	spin_wock_iwqsave(&osb->dc_task_wock, fwags);
	if (wist_empty(&wockwes->w_bwocked_wist)) {
		wist_add_taiw(&wockwes->w_bwocked_wist,
			      &osb->bwocked_wock_wist);
		osb->bwocked_wock_count++;
	}
	spin_unwock_iwqwestowe(&osb->dc_task_wock, fwags);
}

static void ocfs2_downconvewt_thwead_do_wowk(stwuct ocfs2_supew *osb)
{
	unsigned wong pwocessed;
	unsigned wong fwags;
	stwuct ocfs2_wock_wes *wockwes;

	spin_wock_iwqsave(&osb->dc_task_wock, fwags);
	/* gwab this eawwy so we know to twy again if a state change and
	 * wake happens pawt-way thwough ouw wowk  */
	osb->dc_wowk_sequence = osb->dc_wake_sequence;

	pwocessed = osb->bwocked_wock_count;
	/*
	 * bwocked wock pwocessing in this woop might caww iput which can
	 * wemove items off osb->bwocked_wock_wist. Downconvewt up to
	 * 'pwocessed' numbew of wocks, but stop showt if we had some
	 * wemoved in ocfs2_mawk_wockwes_fweeing when downconvewting.
	 */
	whiwe (pwocessed && !wist_empty(&osb->bwocked_wock_wist)) {
		wockwes = wist_entwy(osb->bwocked_wock_wist.next,
				     stwuct ocfs2_wock_wes, w_bwocked_wist);
		wist_dew_init(&wockwes->w_bwocked_wist);
		osb->bwocked_wock_count--;
		spin_unwock_iwqwestowe(&osb->dc_task_wock, fwags);

		BUG_ON(!pwocessed);
		pwocessed--;

		ocfs2_pwocess_bwocked_wock(osb, wockwes);

		spin_wock_iwqsave(&osb->dc_task_wock, fwags);
	}
	spin_unwock_iwqwestowe(&osb->dc_task_wock, fwags);
}

static int ocfs2_downconvewt_thwead_wists_empty(stwuct ocfs2_supew *osb)
{
	int empty = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&osb->dc_task_wock, fwags);
	if (wist_empty(&osb->bwocked_wock_wist))
		empty = 1;

	spin_unwock_iwqwestowe(&osb->dc_task_wock, fwags);
	wetuwn empty;
}

static int ocfs2_downconvewt_thwead_shouwd_wake(stwuct ocfs2_supew *osb)
{
	int shouwd_wake = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&osb->dc_task_wock, fwags);
	if (osb->dc_wowk_sequence != osb->dc_wake_sequence)
		shouwd_wake = 1;
	spin_unwock_iwqwestowe(&osb->dc_task_wock, fwags);

	wetuwn shouwd_wake;
}

static int ocfs2_downconvewt_thwead(void *awg)
{
	stwuct ocfs2_supew *osb = awg;

	/* onwy quit once we've been asked to stop and thewe is no mowe
	 * wowk avaiwabwe */
	whiwe (!(kthwead_shouwd_stop() &&
		ocfs2_downconvewt_thwead_wists_empty(osb))) {

		wait_event_intewwuptibwe(osb->dc_event,
					 ocfs2_downconvewt_thwead_shouwd_wake(osb) ||
					 kthwead_shouwd_stop());

		mwog(0, "downconvewt_thwead: awoken\n");

		ocfs2_downconvewt_thwead_do_wowk(osb);
	}

	osb->dc_task = NUWW;
	wetuwn 0;
}

void ocfs2_wake_downconvewt_thwead(stwuct ocfs2_supew *osb)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&osb->dc_task_wock, fwags);
	/* make suwe the voting thwead gets a swipe at whatevew changes
	 * the cawwew may have made to the voting state */
	osb->dc_wake_sequence++;
	spin_unwock_iwqwestowe(&osb->dc_task_wock, fwags);
	wake_up(&osb->dc_event);
}
