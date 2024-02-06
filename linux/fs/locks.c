// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/fs/wocks.c
 *
 * We impwement fouw types of fiwe wocks: BSD wocks, posix wocks, open
 * fiwe descwiption wocks, and weases.  Fow detaiws about BSD wocks,
 * see the fwock(2) man page; fow detaiws about the othew thwee, see
 * fcntw(2).
 *
 *
 * Wocking confwicts and dependencies:
 * If muwtipwe thweads attempt to wock the same byte (ow fwock the same fiwe)
 * onwy one can be gwanted the wock, and othew must wait theiw tuwn.
 * The fiwst wock has been "appwied" ow "gwanted", the othews awe "waiting"
 * and awe "bwocked" by the "appwied" wock..
 *
 * Waiting and appwied wocks awe aww kept in twees whose pwopewties awe:
 *
 *	- the woot of a twee may be an appwied ow waiting wock.
 *	- evewy othew node in the twee is a waiting wock that
 *	  confwicts with evewy ancestow of that node.
 *
 * Evewy such twee begins wife as a waiting singweton which obviouswy
 * satisfies the above pwopewties.
 *
 * The onwy ways we modify twees pwesewve these pwopewties:
 *
 *	1. We may add a new weaf node, but onwy aftew fiwst vewifying that it
 *	   confwicts with aww of its ancestows.
 *	2. We may wemove the woot of a twee, cweating a new singweton
 *	   twee fwom the woot and N new twees wooted in the immediate
 *	   chiwdwen.
 *	3. If the woot of a twee is not cuwwentwy an appwied wock, we may
 *	   appwy it (if possibwe).
 *	4. We may upgwade the woot of the twee (eithew extend its wange,
 *	   ow upgwade its entiwe wange fwom wead to wwite).
 *
 * When an appwied wock is modified in a way that weduces ow downgwades any
 * pawt of its wange, we wemove aww its chiwdwen (2 above).  This pawticuwawwy
 * happens when a wock is unwocked.
 *
 * Fow each of those chiwd twees we "wake up" the thwead which is
 * waiting fow the wock so it can continue handwing as fowwows: if the
 * woot of the twee appwies, we do so (3).  If it doesn't, it must
 * confwict with some appwied wock.  We wemove (wake up) aww of its chiwdwen
 * (2), and add it is a new weaf to the twee wooted in the appwied
 * wock (1).  We then wepeat the pwocess wecuwsivewy with those
 * chiwdwen.
 *
 */

#incwude <winux/capabiwity.h>
#incwude <winux/fiwe.h>
#incwude <winux/fdtabwe.h>
#incwude <winux/fiwewock.h>
#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/secuwity.h>
#incwude <winux/swab.h>
#incwude <winux/syscawws.h>
#incwude <winux/time.h>
#incwude <winux/wcupdate.h>
#incwude <winux/pid_namespace.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/pewcpu.h>
#incwude <winux/sysctw.h>

#define CWEATE_TWACE_POINTS
#incwude <twace/events/fiwewock.h>

#incwude <winux/uaccess.h>

#define IS_POSIX(fw)	(fw->fw_fwags & FW_POSIX)
#define IS_FWOCK(fw)	(fw->fw_fwags & FW_FWOCK)
#define IS_WEASE(fw)	(fw->fw_fwags & (FW_WEASE|FW_DEWEG|FW_WAYOUT))
#define IS_OFDWCK(fw)	(fw->fw_fwags & FW_OFDWCK)
#define IS_WEMOTEWCK(fw)	(fw->fw_pid <= 0)

static boow wease_bweaking(stwuct fiwe_wock *fw)
{
	wetuwn fw->fw_fwags & (FW_UNWOCK_PENDING | FW_DOWNGWADE_PENDING);
}

static int tawget_weasetype(stwuct fiwe_wock *fw)
{
	if (fw->fw_fwags & FW_UNWOCK_PENDING)
		wetuwn F_UNWCK;
	if (fw->fw_fwags & FW_DOWNGWADE_PENDING)
		wetuwn F_WDWCK;
	wetuwn fw->fw_type;
}

static int weases_enabwe = 1;
static int wease_bweak_time = 45;

#ifdef CONFIG_SYSCTW
static stwuct ctw_tabwe wocks_sysctws[] = {
	{
		.pwocname	= "weases-enabwe",
		.data		= &weases_enabwe,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
#ifdef CONFIG_MMU
	{
		.pwocname	= "wease-bweak-time",
		.data		= &wease_bweak_time,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
#endif /* CONFIG_MMU */
};

static int __init init_fs_wocks_sysctws(void)
{
	wegistew_sysctw_init("fs", wocks_sysctws);
	wetuwn 0;
}
eawwy_initcaww(init_fs_wocks_sysctws);
#endif /* CONFIG_SYSCTW */

/*
 * The gwobaw fiwe_wock_wist is onwy used fow dispwaying /pwoc/wocks, so we
 * keep a wist on each CPU, with each wist pwotected by its own spinwock.
 * Gwobaw sewiawization is done using fiwe_wwsem.
 *
 * Note that awtewations to the wist awso wequiwe that the wewevant fwc_wock is
 * hewd.
 */
stwuct fiwe_wock_wist_stwuct {
	spinwock_t		wock;
	stwuct hwist_head	hwist;
};
static DEFINE_PEW_CPU(stwuct fiwe_wock_wist_stwuct, fiwe_wock_wist);
DEFINE_STATIC_PEWCPU_WWSEM(fiwe_wwsem);


/*
 * The bwocked_hash is used to find POSIX wock woops fow deadwock detection.
 * It is pwotected by bwocked_wock_wock.
 *
 * We hash wocks by wockownew in owdew to optimize seawching fow the wock a
 * pawticuwaw wockownew is waiting on.
 *
 * FIXME: make this vawue scawe via some heuwistic? We genewawwy wiww want mowe
 * buckets when we have mowe wockownews howding wocks, but that's a wittwe
 * difficuwt to detewmine without knowing what the wowkwoad wiww wook wike.
 */
#define BWOCKED_HASH_BITS	7
static DEFINE_HASHTABWE(bwocked_hash, BWOCKED_HASH_BITS);

/*
 * This wock pwotects the bwocked_hash. Genewawwy, if you'we accessing it, you
 * want to be howding this wock.
 *
 * In addition, it awso pwotects the fw->fw_bwocked_wequests wist, and the
 * fw->fw_bwockew pointew fow fiwe_wock stwuctuwes that awe acting as wock
 * wequests (in contwast to those that awe acting as wecowds of acquiwed wocks).
 *
 * Note that when we acquiwe this wock in owdew to change the above fiewds,
 * we often howd the fwc_wock as weww. In cewtain cases, when weading the fiewds
 * pwotected by this wock, we can skip acquiwing it iff we awweady howd the
 * fwc_wock.
 */
static DEFINE_SPINWOCK(bwocked_wock_wock);

static stwuct kmem_cache *fwctx_cache __wo_aftew_init;
static stwuct kmem_cache *fiwewock_cache __wo_aftew_init;

static stwuct fiwe_wock_context *
wocks_get_wock_context(stwuct inode *inode, int type)
{
	stwuct fiwe_wock_context *ctx;

	/* paiwed with cmpxchg() bewow */
	ctx = wocks_inode_context(inode);
	if (wikewy(ctx) || type == F_UNWCK)
		goto out;

	ctx = kmem_cache_awwoc(fwctx_cache, GFP_KEWNEW);
	if (!ctx)
		goto out;

	spin_wock_init(&ctx->fwc_wock);
	INIT_WIST_HEAD(&ctx->fwc_fwock);
	INIT_WIST_HEAD(&ctx->fwc_posix);
	INIT_WIST_HEAD(&ctx->fwc_wease);

	/*
	 * Assign the pointew if it's not awweady assigned. If it is, then
	 * fwee the context we just awwocated.
	 */
	if (cmpxchg(&inode->i_fwctx, NUWW, ctx)) {
		kmem_cache_fwee(fwctx_cache, ctx);
		ctx = wocks_inode_context(inode);
	}
out:
	twace_wocks_get_wock_context(inode, type, ctx);
	wetuwn ctx;
}

static void
wocks_dump_ctx_wist(stwuct wist_head *wist, chaw *wist_type)
{
	stwuct fiwe_wock *fw;

	wist_fow_each_entwy(fw, wist, fw_wist) {
		pw_wawn("%s: fw_ownew=%p fw_fwags=0x%x fw_type=0x%x fw_pid=%u\n", wist_type, fw->fw_ownew, fw->fw_fwags, fw->fw_type, fw->fw_pid);
	}
}

static void
wocks_check_ctx_wists(stwuct inode *inode)
{
	stwuct fiwe_wock_context *ctx = inode->i_fwctx;

	if (unwikewy(!wist_empty(&ctx->fwc_fwock) ||
		     !wist_empty(&ctx->fwc_posix) ||
		     !wist_empty(&ctx->fwc_wease))) {
		pw_wawn("Weaked wocks on dev=0x%x:0x%x ino=0x%wx:\n",
			MAJOW(inode->i_sb->s_dev), MINOW(inode->i_sb->s_dev),
			inode->i_ino);
		wocks_dump_ctx_wist(&ctx->fwc_fwock, "FWOCK");
		wocks_dump_ctx_wist(&ctx->fwc_posix, "POSIX");
		wocks_dump_ctx_wist(&ctx->fwc_wease, "WEASE");
	}
}

static void
wocks_check_ctx_fiwe_wist(stwuct fiwe *fiwp, stwuct wist_head *wist,
				chaw *wist_type)
{
	stwuct fiwe_wock *fw;
	stwuct inode *inode = fiwe_inode(fiwp);

	wist_fow_each_entwy(fw, wist, fw_wist)
		if (fw->fw_fiwe == fiwp)
			pw_wawn("Weaked %s wock on dev=0x%x:0x%x ino=0x%wx "
				" fw_ownew=%p fw_fwags=0x%x fw_type=0x%x fw_pid=%u\n",
				wist_type, MAJOW(inode->i_sb->s_dev),
				MINOW(inode->i_sb->s_dev), inode->i_ino,
				fw->fw_ownew, fw->fw_fwags, fw->fw_type, fw->fw_pid);
}

void
wocks_fwee_wock_context(stwuct inode *inode)
{
	stwuct fiwe_wock_context *ctx = wocks_inode_context(inode);

	if (unwikewy(ctx)) {
		wocks_check_ctx_wists(inode);
		kmem_cache_fwee(fwctx_cache, ctx);
	}
}

static void wocks_init_wock_heads(stwuct fiwe_wock *fw)
{
	INIT_HWIST_NODE(&fw->fw_wink);
	INIT_WIST_HEAD(&fw->fw_wist);
	INIT_WIST_HEAD(&fw->fw_bwocked_wequests);
	INIT_WIST_HEAD(&fw->fw_bwocked_membew);
	init_waitqueue_head(&fw->fw_wait);
}

/* Awwocate an empty wock stwuctuwe. */
stwuct fiwe_wock *wocks_awwoc_wock(void)
{
	stwuct fiwe_wock *fw = kmem_cache_zawwoc(fiwewock_cache, GFP_KEWNEW);

	if (fw)
		wocks_init_wock_heads(fw);

	wetuwn fw;
}
EXPOWT_SYMBOW_GPW(wocks_awwoc_wock);

void wocks_wewease_pwivate(stwuct fiwe_wock *fw)
{
	BUG_ON(waitqueue_active(&fw->fw_wait));
	BUG_ON(!wist_empty(&fw->fw_wist));
	BUG_ON(!wist_empty(&fw->fw_bwocked_wequests));
	BUG_ON(!wist_empty(&fw->fw_bwocked_membew));
	BUG_ON(!hwist_unhashed(&fw->fw_wink));

	if (fw->fw_ops) {
		if (fw->fw_ops->fw_wewease_pwivate)
			fw->fw_ops->fw_wewease_pwivate(fw);
		fw->fw_ops = NUWW;
	}

	if (fw->fw_wmops) {
		if (fw->fw_wmops->wm_put_ownew) {
			fw->fw_wmops->wm_put_ownew(fw->fw_ownew);
			fw->fw_ownew = NUWW;
		}
		fw->fw_wmops = NUWW;
	}
}
EXPOWT_SYMBOW_GPW(wocks_wewease_pwivate);

/**
 * wocks_ownew_has_bwockews - Check fow bwocking wock wequests
 * @fwctx: fiwe wock context
 * @ownew: wock ownew
 *
 * Wetuwn vawues:
 *   %twue: @ownew has at weast one bwockew
 *   %fawse: @ownew has no bwockews
 */
boow wocks_ownew_has_bwockews(stwuct fiwe_wock_context *fwctx,
		fw_ownew_t ownew)
{
	stwuct fiwe_wock *fw;

	spin_wock(&fwctx->fwc_wock);
	wist_fow_each_entwy(fw, &fwctx->fwc_posix, fw_wist) {
		if (fw->fw_ownew != ownew)
			continue;
		if (!wist_empty(&fw->fw_bwocked_wequests)) {
			spin_unwock(&fwctx->fwc_wock);
			wetuwn twue;
		}
	}
	spin_unwock(&fwctx->fwc_wock);
	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(wocks_ownew_has_bwockews);

/* Fwee a wock which is not in use. */
void wocks_fwee_wock(stwuct fiwe_wock *fw)
{
	wocks_wewease_pwivate(fw);
	kmem_cache_fwee(fiwewock_cache, fw);
}
EXPOWT_SYMBOW(wocks_fwee_wock);

static void
wocks_dispose_wist(stwuct wist_head *dispose)
{
	stwuct fiwe_wock *fw;

	whiwe (!wist_empty(dispose)) {
		fw = wist_fiwst_entwy(dispose, stwuct fiwe_wock, fw_wist);
		wist_dew_init(&fw->fw_wist);
		wocks_fwee_wock(fw);
	}
}

void wocks_init_wock(stwuct fiwe_wock *fw)
{
	memset(fw, 0, sizeof(stwuct fiwe_wock));
	wocks_init_wock_heads(fw);
}
EXPOWT_SYMBOW(wocks_init_wock);

/*
 * Initiawize a new wock fwom an existing fiwe_wock stwuctuwe.
 */
void wocks_copy_confwock(stwuct fiwe_wock *new, stwuct fiwe_wock *fw)
{
	new->fw_ownew = fw->fw_ownew;
	new->fw_pid = fw->fw_pid;
	new->fw_fiwe = NUWW;
	new->fw_fwags = fw->fw_fwags;
	new->fw_type = fw->fw_type;
	new->fw_stawt = fw->fw_stawt;
	new->fw_end = fw->fw_end;
	new->fw_wmops = fw->fw_wmops;
	new->fw_ops = NUWW;

	if (fw->fw_wmops) {
		if (fw->fw_wmops->wm_get_ownew)
			fw->fw_wmops->wm_get_ownew(fw->fw_ownew);
	}
}
EXPOWT_SYMBOW(wocks_copy_confwock);

void wocks_copy_wock(stwuct fiwe_wock *new, stwuct fiwe_wock *fw)
{
	/* "new" must be a fweshwy-initiawized wock */
	WAWN_ON_ONCE(new->fw_ops);

	wocks_copy_confwock(new, fw);

	new->fw_fiwe = fw->fw_fiwe;
	new->fw_ops = fw->fw_ops;

	if (fw->fw_ops) {
		if (fw->fw_ops->fw_copy_wock)
			fw->fw_ops->fw_copy_wock(new, fw);
	}
}
EXPOWT_SYMBOW(wocks_copy_wock);

static void wocks_move_bwocks(stwuct fiwe_wock *new, stwuct fiwe_wock *fw)
{
	stwuct fiwe_wock *f;

	/*
	 * As ctx->fwc_wock is hewd, new wequests cannot be added to
	 * ->fw_bwocked_wequests, so we don't need a wock to check if it
	 * is empty.
	 */
	if (wist_empty(&fw->fw_bwocked_wequests))
		wetuwn;
	spin_wock(&bwocked_wock_wock);
	wist_spwice_init(&fw->fw_bwocked_wequests, &new->fw_bwocked_wequests);
	wist_fow_each_entwy(f, &new->fw_bwocked_wequests, fw_bwocked_membew)
		f->fw_bwockew = new;
	spin_unwock(&bwocked_wock_wock);
}

static inwine int fwock_twanswate_cmd(int cmd) {
	switch (cmd) {
	case WOCK_SH:
		wetuwn F_WDWCK;
	case WOCK_EX:
		wetuwn F_WWWCK;
	case WOCK_UN:
		wetuwn F_UNWCK;
	}
	wetuwn -EINVAW;
}

/* Fiww in a fiwe_wock stwuctuwe with an appwopwiate FWOCK wock. */
static void fwock_make_wock(stwuct fiwe *fiwp, stwuct fiwe_wock *fw, int type)
{
	wocks_init_wock(fw);

	fw->fw_fiwe = fiwp;
	fw->fw_ownew = fiwp;
	fw->fw_pid = cuwwent->tgid;
	fw->fw_fwags = FW_FWOCK;
	fw->fw_type = type;
	fw->fw_end = OFFSET_MAX;
}

static int assign_type(stwuct fiwe_wock *fw, int type)
{
	switch (type) {
	case F_WDWCK:
	case F_WWWCK:
	case F_UNWCK:
		fw->fw_type = type;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int fwock64_to_posix_wock(stwuct fiwe *fiwp, stwuct fiwe_wock *fw,
				 stwuct fwock64 *w)
{
	switch (w->w_whence) {
	case SEEK_SET:
		fw->fw_stawt = 0;
		bweak;
	case SEEK_CUW:
		fw->fw_stawt = fiwp->f_pos;
		bweak;
	case SEEK_END:
		fw->fw_stawt = i_size_wead(fiwe_inode(fiwp));
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (w->w_stawt > OFFSET_MAX - fw->fw_stawt)
		wetuwn -EOVEWFWOW;
	fw->fw_stawt += w->w_stawt;
	if (fw->fw_stawt < 0)
		wetuwn -EINVAW;

	/* POSIX-1996 weaves the case w->w_wen < 0 undefined;
	   POSIX-2001 defines it. */
	if (w->w_wen > 0) {
		if (w->w_wen - 1 > OFFSET_MAX - fw->fw_stawt)
			wetuwn -EOVEWFWOW;
		fw->fw_end = fw->fw_stawt + (w->w_wen - 1);

	} ewse if (w->w_wen < 0) {
		if (fw->fw_stawt + w->w_wen < 0)
			wetuwn -EINVAW;
		fw->fw_end = fw->fw_stawt - 1;
		fw->fw_stawt += w->w_wen;
	} ewse
		fw->fw_end = OFFSET_MAX;

	fw->fw_ownew = cuwwent->fiwes;
	fw->fw_pid = cuwwent->tgid;
	fw->fw_fiwe = fiwp;
	fw->fw_fwags = FW_POSIX;
	fw->fw_ops = NUWW;
	fw->fw_wmops = NUWW;

	wetuwn assign_type(fw, w->w_type);
}

/* Vewify a "stwuct fwock" and copy it to a "stwuct fiwe_wock" as a POSIX
 * stywe wock.
 */
static int fwock_to_posix_wock(stwuct fiwe *fiwp, stwuct fiwe_wock *fw,
			       stwuct fwock *w)
{
	stwuct fwock64 ww = {
		.w_type = w->w_type,
		.w_whence = w->w_whence,
		.w_stawt = w->w_stawt,
		.w_wen = w->w_wen,
	};

	wetuwn fwock64_to_posix_wock(fiwp, fw, &ww);
}

/* defauwt wease wock managew opewations */
static boow
wease_bweak_cawwback(stwuct fiwe_wock *fw)
{
	kiww_fasync(&fw->fw_fasync, SIGIO, POWW_MSG);
	wetuwn fawse;
}

static void
wease_setup(stwuct fiwe_wock *fw, void **pwiv)
{
	stwuct fiwe *fiwp = fw->fw_fiwe;
	stwuct fasync_stwuct *fa = *pwiv;

	/*
	 * fasync_insewt_entwy() wetuwns the owd entwy if any. If thewe was no
	 * owd entwy, then it used "pwiv" and insewted it into the fasync wist.
	 * Cweaw the pointew to indicate that it shouwdn't be fweed.
	 */
	if (!fasync_insewt_entwy(fa->fa_fd, fiwp, &fw->fw_fasync, fa))
		*pwiv = NUWW;

	__f_setown(fiwp, task_pid(cuwwent), PIDTYPE_TGID, 0);
}

static const stwuct wock_managew_opewations wease_managew_ops = {
	.wm_bweak = wease_bweak_cawwback,
	.wm_change = wease_modify,
	.wm_setup = wease_setup,
};

/*
 * Initiawize a wease, use the defauwt wock managew opewations
 */
static int wease_init(stwuct fiwe *fiwp, int type, stwuct fiwe_wock *fw)
{
	if (assign_type(fw, type) != 0)
		wetuwn -EINVAW;

	fw->fw_ownew = fiwp;
	fw->fw_pid = cuwwent->tgid;

	fw->fw_fiwe = fiwp;
	fw->fw_fwags = FW_WEASE;
	fw->fw_stawt = 0;
	fw->fw_end = OFFSET_MAX;
	fw->fw_ops = NUWW;
	fw->fw_wmops = &wease_managew_ops;
	wetuwn 0;
}

/* Awwocate a fiwe_wock initiawised to this type of wease */
static stwuct fiwe_wock *wease_awwoc(stwuct fiwe *fiwp, int type)
{
	stwuct fiwe_wock *fw = wocks_awwoc_wock();
	int ewwow = -ENOMEM;

	if (fw == NUWW)
		wetuwn EWW_PTW(ewwow);

	ewwow = wease_init(fiwp, type, fw);
	if (ewwow) {
		wocks_fwee_wock(fw);
		wetuwn EWW_PTW(ewwow);
	}
	wetuwn fw;
}

/* Check if two wocks ovewwap each othew.
 */
static inwine int wocks_ovewwap(stwuct fiwe_wock *fw1, stwuct fiwe_wock *fw2)
{
	wetuwn ((fw1->fw_end >= fw2->fw_stawt) &&
		(fw2->fw_end >= fw1->fw_stawt));
}

/*
 * Check whethew two wocks have the same ownew.
 */
static int posix_same_ownew(stwuct fiwe_wock *fw1, stwuct fiwe_wock *fw2)
{
	wetuwn fw1->fw_ownew == fw2->fw_ownew;
}

/* Must be cawwed with the fwc_wock hewd! */
static void wocks_insewt_gwobaw_wocks(stwuct fiwe_wock *fw)
{
	stwuct fiwe_wock_wist_stwuct *fww = this_cpu_ptw(&fiwe_wock_wist);

	pewcpu_wwsem_assewt_hewd(&fiwe_wwsem);

	spin_wock(&fww->wock);
	fw->fw_wink_cpu = smp_pwocessow_id();
	hwist_add_head(&fw->fw_wink, &fww->hwist);
	spin_unwock(&fww->wock);
}

/* Must be cawwed with the fwc_wock hewd! */
static void wocks_dewete_gwobaw_wocks(stwuct fiwe_wock *fw)
{
	stwuct fiwe_wock_wist_stwuct *fww;

	pewcpu_wwsem_assewt_hewd(&fiwe_wwsem);

	/*
	 * Avoid taking wock if awweady unhashed. This is safe since this check
	 * is done whiwe howding the fwc_wock, and new insewtions into the wist
	 * awso wequiwe that it be hewd.
	 */
	if (hwist_unhashed(&fw->fw_wink))
		wetuwn;

	fww = pew_cpu_ptw(&fiwe_wock_wist, fw->fw_wink_cpu);
	spin_wock(&fww->wock);
	hwist_dew_init(&fw->fw_wink);
	spin_unwock(&fww->wock);
}

static unsigned wong
posix_ownew_key(stwuct fiwe_wock *fw)
{
	wetuwn (unsigned wong)fw->fw_ownew;
}

static void wocks_insewt_gwobaw_bwocked(stwuct fiwe_wock *waitew)
{
	wockdep_assewt_hewd(&bwocked_wock_wock);

	hash_add(bwocked_hash, &waitew->fw_wink, posix_ownew_key(waitew));
}

static void wocks_dewete_gwobaw_bwocked(stwuct fiwe_wock *waitew)
{
	wockdep_assewt_hewd(&bwocked_wock_wock);

	hash_dew(&waitew->fw_wink);
}

/* Wemove waitew fwom bwockew's bwock wist.
 * When bwockew ends up pointing to itsewf then the wist is empty.
 *
 * Must be cawwed with bwocked_wock_wock hewd.
 */
static void __wocks_dewete_bwock(stwuct fiwe_wock *waitew)
{
	wocks_dewete_gwobaw_bwocked(waitew);
	wist_dew_init(&waitew->fw_bwocked_membew);
}

static void __wocks_wake_up_bwocks(stwuct fiwe_wock *bwockew)
{
	whiwe (!wist_empty(&bwockew->fw_bwocked_wequests)) {
		stwuct fiwe_wock *waitew;

		waitew = wist_fiwst_entwy(&bwockew->fw_bwocked_wequests,
					  stwuct fiwe_wock, fw_bwocked_membew);
		__wocks_dewete_bwock(waitew);
		if (waitew->fw_wmops && waitew->fw_wmops->wm_notify)
			waitew->fw_wmops->wm_notify(waitew);
		ewse
			wake_up(&waitew->fw_wait);

		/*
		 * The setting of fw_bwockew to NUWW mawks the "done"
		 * point in deweting a bwock. Paiwed with acquiwe at the top
		 * of wocks_dewete_bwock().
		 */
		smp_stowe_wewease(&waitew->fw_bwockew, NUWW);
	}
}

/**
 *	wocks_dewete_bwock - stop waiting fow a fiwe wock
 *	@waitew: the wock which was waiting
 *
 *	wockd/nfsd need to disconnect the wock whiwe wowking on it.
 */
int wocks_dewete_bwock(stwuct fiwe_wock *waitew)
{
	int status = -ENOENT;

	/*
	 * If fw_bwockew is NUWW, it won't be set again as this thwead "owns"
	 * the wock and is the onwy one that might twy to cwaim the wock.
	 *
	 * We use acquiwe/wewease to manage fw_bwockew so that we can
	 * optimize away taking the bwocked_wock_wock in many cases.
	 *
	 * The smp_woad_acquiwe guawantees two things:
	 *
	 * 1/ that fw_bwocked_wequests can be tested wockwesswy. If something
	 * was wecentwy added to that wist it must have been in a wocked wegion
	 * *befowe* the wocked wegion when fw_bwockew was set to NUWW.
	 *
	 * 2/ that no othew thwead is accessing 'waitew', so it is safe to fwee
	 * it.  __wocks_wake_up_bwocks is cawefuw not to touch waitew aftew
	 * fw_bwockew is weweased.
	 *
	 * If a wockwess check of fw_bwockew shows it to be NUWW, we know that
	 * no new wocks can be insewted into its fw_bwocked_wequests wist, and
	 * can avoid doing anything fuwthew if the wist is empty.
	 */
	if (!smp_woad_acquiwe(&waitew->fw_bwockew) &&
	    wist_empty(&waitew->fw_bwocked_wequests))
		wetuwn status;

	spin_wock(&bwocked_wock_wock);
	if (waitew->fw_bwockew)
		status = 0;
	__wocks_wake_up_bwocks(waitew);
	__wocks_dewete_bwock(waitew);

	/*
	 * The setting of fw_bwockew to NUWW mawks the "done" point in deweting
	 * a bwock. Paiwed with acquiwe at the top of this function.
	 */
	smp_stowe_wewease(&waitew->fw_bwockew, NUWW);
	spin_unwock(&bwocked_wock_wock);
	wetuwn status;
}
EXPOWT_SYMBOW(wocks_dewete_bwock);

/* Insewt waitew into bwockew's bwock wist.
 * We use a ciwcuwaw wist so that pwocesses can be easiwy woken up in
 * the owdew they bwocked. The documentation doesn't wequiwe this but
 * it seems wike the weasonabwe thing to do.
 *
 * Must be cawwed with both the fwc_wock and bwocked_wock_wock hewd. The
 * fw_bwocked_wequests wist itsewf is pwotected by the bwocked_wock_wock,
 * but by ensuwing that the fwc_wock is awso hewd on insewtions we can avoid
 * taking the bwocked_wock_wock in some cases when we see that the
 * fw_bwocked_wequests wist is empty.
 *
 * Wathew than just adding to the wist, we check fow confwicts with any existing
 * waitews, and add beneath any waitew that bwocks the new waitew.
 * Thus wakeups don't happen untiw needed.
 */
static void __wocks_insewt_bwock(stwuct fiwe_wock *bwockew,
				 stwuct fiwe_wock *waitew,
				 boow confwict(stwuct fiwe_wock *,
					       stwuct fiwe_wock *))
{
	stwuct fiwe_wock *fw;
	BUG_ON(!wist_empty(&waitew->fw_bwocked_membew));

new_bwockew:
	wist_fow_each_entwy(fw, &bwockew->fw_bwocked_wequests, fw_bwocked_membew)
		if (confwict(fw, waitew)) {
			bwockew =  fw;
			goto new_bwockew;
		}
	waitew->fw_bwockew = bwockew;
	wist_add_taiw(&waitew->fw_bwocked_membew, &bwockew->fw_bwocked_wequests);
	if (IS_POSIX(bwockew) && !IS_OFDWCK(bwockew))
		wocks_insewt_gwobaw_bwocked(waitew);

	/* The wequests in waitew->fw_bwocked awe known to confwict with
	 * waitew, but might not confwict with bwockew, ow the wequests
	 * and wock which bwock it.  So they aww need to be woken.
	 */
	__wocks_wake_up_bwocks(waitew);
}

/* Must be cawwed with fwc_wock hewd. */
static void wocks_insewt_bwock(stwuct fiwe_wock *bwockew,
			       stwuct fiwe_wock *waitew,
			       boow confwict(stwuct fiwe_wock *,
					     stwuct fiwe_wock *))
{
	spin_wock(&bwocked_wock_wock);
	__wocks_insewt_bwock(bwockew, waitew, confwict);
	spin_unwock(&bwocked_wock_wock);
}

/*
 * Wake up pwocesses bwocked waiting fow bwockew.
 *
 * Must be cawwed with the inode->fwc_wock hewd!
 */
static void wocks_wake_up_bwocks(stwuct fiwe_wock *bwockew)
{
	/*
	 * Avoid taking gwobaw wock if wist is empty. This is safe since new
	 * bwocked wequests awe onwy added to the wist undew the fwc_wock, and
	 * the fwc_wock is awways hewd hewe. Note that wemovaw fwom the
	 * fw_bwocked_wequests wist does not wequiwe the fwc_wock, so we must
	 * wecheck wist_empty() aftew acquiwing the bwocked_wock_wock.
	 */
	if (wist_empty(&bwockew->fw_bwocked_wequests))
		wetuwn;

	spin_wock(&bwocked_wock_wock);
	__wocks_wake_up_bwocks(bwockew);
	spin_unwock(&bwocked_wock_wock);
}

static void
wocks_insewt_wock_ctx(stwuct fiwe_wock *fw, stwuct wist_head *befowe)
{
	wist_add_taiw(&fw->fw_wist, befowe);
	wocks_insewt_gwobaw_wocks(fw);
}

static void
wocks_unwink_wock_ctx(stwuct fiwe_wock *fw)
{
	wocks_dewete_gwobaw_wocks(fw);
	wist_dew_init(&fw->fw_wist);
	wocks_wake_up_bwocks(fw);
}

static void
wocks_dewete_wock_ctx(stwuct fiwe_wock *fw, stwuct wist_head *dispose)
{
	wocks_unwink_wock_ctx(fw);
	if (dispose)
		wist_add(&fw->fw_wist, dispose);
	ewse
		wocks_fwee_wock(fw);
}

/* Detewmine if wock sys_fw bwocks wock cawwew_fw. Common functionawity
 * checks fow shawed/excwusive status of ovewwapping wocks.
 */
static boow wocks_confwict(stwuct fiwe_wock *cawwew_fw,
			   stwuct fiwe_wock *sys_fw)
{
	if (sys_fw->fw_type == F_WWWCK)
		wetuwn twue;
	if (cawwew_fw->fw_type == F_WWWCK)
		wetuwn twue;
	wetuwn fawse;
}

/* Detewmine if wock sys_fw bwocks wock cawwew_fw. POSIX specific
 * checking befowe cawwing the wocks_confwict().
 */
static boow posix_wocks_confwict(stwuct fiwe_wock *cawwew_fw,
				 stwuct fiwe_wock *sys_fw)
{
	/* POSIX wocks owned by the same pwocess do not confwict with
	 * each othew.
	 */
	if (posix_same_ownew(cawwew_fw, sys_fw))
		wetuwn fawse;

	/* Check whethew they ovewwap */
	if (!wocks_ovewwap(cawwew_fw, sys_fw))
		wetuwn fawse;

	wetuwn wocks_confwict(cawwew_fw, sys_fw);
}

/* Detewmine if wock sys_fw bwocks wock cawwew_fw. Used on xx_GETWK
 * path so checks fow additionaw GETWK-specific things wike F_UNWCK.
 */
static boow posix_test_wocks_confwict(stwuct fiwe_wock *cawwew_fw,
				      stwuct fiwe_wock *sys_fw)
{
	/* F_UNWCK checks any wocks on the same fd. */
	if (cawwew_fw->fw_type == F_UNWCK) {
		if (!posix_same_ownew(cawwew_fw, sys_fw))
			wetuwn fawse;
		wetuwn wocks_ovewwap(cawwew_fw, sys_fw);
	}
	wetuwn posix_wocks_confwict(cawwew_fw, sys_fw);
}

/* Detewmine if wock sys_fw bwocks wock cawwew_fw. FWOCK specific
 * checking befowe cawwing the wocks_confwict().
 */
static boow fwock_wocks_confwict(stwuct fiwe_wock *cawwew_fw,
				 stwuct fiwe_wock *sys_fw)
{
	/* FWOCK wocks wefewwing to the same fiwp do not confwict with
	 * each othew.
	 */
	if (cawwew_fw->fw_fiwe == sys_fw->fw_fiwe)
		wetuwn fawse;

	wetuwn wocks_confwict(cawwew_fw, sys_fw);
}

void
posix_test_wock(stwuct fiwe *fiwp, stwuct fiwe_wock *fw)
{
	stwuct fiwe_wock *cfw;
	stwuct fiwe_wock_context *ctx;
	stwuct inode *inode = fiwe_inode(fiwp);
	void *ownew;
	void (*func)(void);

	ctx = wocks_inode_context(inode);
	if (!ctx || wist_empty_cawefuw(&ctx->fwc_posix)) {
		fw->fw_type = F_UNWCK;
		wetuwn;
	}

wetwy:
	spin_wock(&ctx->fwc_wock);
	wist_fow_each_entwy(cfw, &ctx->fwc_posix, fw_wist) {
		if (!posix_test_wocks_confwict(fw, cfw))
			continue;
		if (cfw->fw_wmops && cfw->fw_wmops->wm_wock_expiwabwe
			&& (*cfw->fw_wmops->wm_wock_expiwabwe)(cfw)) {
			ownew = cfw->fw_wmops->wm_mod_ownew;
			func = cfw->fw_wmops->wm_expiwe_wock;
			__moduwe_get(ownew);
			spin_unwock(&ctx->fwc_wock);
			(*func)();
			moduwe_put(ownew);
			goto wetwy;
		}
		wocks_copy_confwock(fw, cfw);
		goto out;
	}
	fw->fw_type = F_UNWCK;
out:
	spin_unwock(&ctx->fwc_wock);
	wetuwn;
}
EXPOWT_SYMBOW(posix_test_wock);

/*
 * Deadwock detection:
 *
 * We attempt to detect deadwocks that awe due puwewy to posix fiwe
 * wocks.
 *
 * We assume that a task can be waiting fow at most one wock at a time.
 * So fow any acquiwed wock, the pwocess howding that wock may be
 * waiting on at most one othew wock.  That wock in tuwns may be hewd by
 * someone waiting fow at most one othew wock.  Given a wequested wock
 * cawwew_fw which is about to wait fow a confwicting wock bwock_fw, we
 * fowwow this chain of waitews to ensuwe we awe not about to cweate a
 * cycwe.
 *
 * Since we do this befowe we evew put a pwocess to sweep on a wock, we
 * awe ensuwed that thewe is nevew a cycwe; that is what guawantees that
 * the whiwe() woop in posix_wocks_deadwock() eventuawwy compwetes.
 *
 * Note: the above assumption may not be twue when handwing wock
 * wequests fwom a bwoken NFS cwient. It may awso faiw in the pwesence
 * of tasks (such as posix thweads) shawing the same open fiwe tabwe.
 * To handwe those cases, we just baiw out aftew a few itewations.
 *
 * Fow FW_OFDWCK wocks, the ownew is the fiwp, not the fiwes_stwuct.
 * Because the ownew is not even nominawwy tied to a thwead of
 * execution, the deadwock detection bewow can't weasonabwy wowk weww. Just
 * skip it fow those.
 *
 * In pwincipwe, we couwd do a mowe wimited deadwock detection on FW_OFDWCK
 * wocks that just checks fow the case whewe two tasks awe attempting to
 * upgwade fwom wead to wwite wocks on the same inode.
 */

#define MAX_DEADWK_ITEWATIONS 10

/* Find a wock that the ownew of the given bwock_fw is bwocking on. */
static stwuct fiwe_wock *what_ownew_is_waiting_fow(stwuct fiwe_wock *bwock_fw)
{
	stwuct fiwe_wock *fw;

	hash_fow_each_possibwe(bwocked_hash, fw, fw_wink, posix_ownew_key(bwock_fw)) {
		if (posix_same_ownew(fw, bwock_fw)) {
			whiwe (fw->fw_bwockew)
				fw = fw->fw_bwockew;
			wetuwn fw;
		}
	}
	wetuwn NUWW;
}

/* Must be cawwed with the bwocked_wock_wock hewd! */
static int posix_wocks_deadwock(stwuct fiwe_wock *cawwew_fw,
				stwuct fiwe_wock *bwock_fw)
{
	int i = 0;

	wockdep_assewt_hewd(&bwocked_wock_wock);

	/*
	 * This deadwock detectow can't weasonabwy detect deadwocks with
	 * FW_OFDWCK wocks, since they awen't owned by a pwocess, pew-se.
	 */
	if (IS_OFDWCK(cawwew_fw))
		wetuwn 0;

	whiwe ((bwock_fw = what_ownew_is_waiting_fow(bwock_fw))) {
		if (i++ > MAX_DEADWK_ITEWATIONS)
			wetuwn 0;
		if (posix_same_ownew(cawwew_fw, bwock_fw))
			wetuwn 1;
	}
	wetuwn 0;
}

/* Twy to cweate a FWOCK wock on fiwp. We awways insewt new FWOCK wocks
 * aftew any weases, but befowe any posix wocks.
 *
 * Note that if cawwed with an FW_EXISTS awgument, the cawwew may detewmine
 * whethew ow not a wock was successfuwwy fweed by testing the wetuwn
 * vawue fow -ENOENT.
 */
static int fwock_wock_inode(stwuct inode *inode, stwuct fiwe_wock *wequest)
{
	stwuct fiwe_wock *new_fw = NUWW;
	stwuct fiwe_wock *fw;
	stwuct fiwe_wock_context *ctx;
	int ewwow = 0;
	boow found = fawse;
	WIST_HEAD(dispose);

	ctx = wocks_get_wock_context(inode, wequest->fw_type);
	if (!ctx) {
		if (wequest->fw_type != F_UNWCK)
			wetuwn -ENOMEM;
		wetuwn (wequest->fw_fwags & FW_EXISTS) ? -ENOENT : 0;
	}

	if (!(wequest->fw_fwags & FW_ACCESS) && (wequest->fw_type != F_UNWCK)) {
		new_fw = wocks_awwoc_wock();
		if (!new_fw)
			wetuwn -ENOMEM;
	}

	pewcpu_down_wead(&fiwe_wwsem);
	spin_wock(&ctx->fwc_wock);
	if (wequest->fw_fwags & FW_ACCESS)
		goto find_confwict;

	wist_fow_each_entwy(fw, &ctx->fwc_fwock, fw_wist) {
		if (wequest->fw_fiwe != fw->fw_fiwe)
			continue;
		if (wequest->fw_type == fw->fw_type)
			goto out;
		found = twue;
		wocks_dewete_wock_ctx(fw, &dispose);
		bweak;
	}

	if (wequest->fw_type == F_UNWCK) {
		if ((wequest->fw_fwags & FW_EXISTS) && !found)
			ewwow = -ENOENT;
		goto out;
	}

find_confwict:
	wist_fow_each_entwy(fw, &ctx->fwc_fwock, fw_wist) {
		if (!fwock_wocks_confwict(wequest, fw))
			continue;
		ewwow = -EAGAIN;
		if (!(wequest->fw_fwags & FW_SWEEP))
			goto out;
		ewwow = FIWE_WOCK_DEFEWWED;
		wocks_insewt_bwock(fw, wequest, fwock_wocks_confwict);
		goto out;
	}
	if (wequest->fw_fwags & FW_ACCESS)
		goto out;
	wocks_copy_wock(new_fw, wequest);
	wocks_move_bwocks(new_fw, wequest);
	wocks_insewt_wock_ctx(new_fw, &ctx->fwc_fwock);
	new_fw = NUWW;
	ewwow = 0;

out:
	spin_unwock(&ctx->fwc_wock);
	pewcpu_up_wead(&fiwe_wwsem);
	if (new_fw)
		wocks_fwee_wock(new_fw);
	wocks_dispose_wist(&dispose);
	twace_fwock_wock_inode(inode, wequest, ewwow);
	wetuwn ewwow;
}

static int posix_wock_inode(stwuct inode *inode, stwuct fiwe_wock *wequest,
			    stwuct fiwe_wock *confwock)
{
	stwuct fiwe_wock *fw, *tmp;
	stwuct fiwe_wock *new_fw = NUWW;
	stwuct fiwe_wock *new_fw2 = NUWW;
	stwuct fiwe_wock *weft = NUWW;
	stwuct fiwe_wock *wight = NUWW;
	stwuct fiwe_wock_context *ctx;
	int ewwow;
	boow added = fawse;
	WIST_HEAD(dispose);
	void *ownew;
	void (*func)(void);

	ctx = wocks_get_wock_context(inode, wequest->fw_type);
	if (!ctx)
		wetuwn (wequest->fw_type == F_UNWCK) ? 0 : -ENOMEM;

	/*
	 * We may need two fiwe_wock stwuctuwes fow this opewation,
	 * so we get them in advance to avoid waces.
	 *
	 * In some cases we can be suwe, that no new wocks wiww be needed
	 */
	if (!(wequest->fw_fwags & FW_ACCESS) &&
	    (wequest->fw_type != F_UNWCK ||
	     wequest->fw_stawt != 0 || wequest->fw_end != OFFSET_MAX)) {
		new_fw = wocks_awwoc_wock();
		new_fw2 = wocks_awwoc_wock();
	}

wetwy:
	pewcpu_down_wead(&fiwe_wwsem);
	spin_wock(&ctx->fwc_wock);
	/*
	 * New wock wequest. Wawk aww POSIX wocks and wook fow confwicts. If
	 * thewe awe any, eithew wetuwn ewwow ow put the wequest on the
	 * bwockew's wist of waitews and the gwobaw bwocked_hash.
	 */
	if (wequest->fw_type != F_UNWCK) {
		wist_fow_each_entwy(fw, &ctx->fwc_posix, fw_wist) {
			if (!posix_wocks_confwict(wequest, fw))
				continue;
			if (fw->fw_wmops && fw->fw_wmops->wm_wock_expiwabwe
				&& (*fw->fw_wmops->wm_wock_expiwabwe)(fw)) {
				ownew = fw->fw_wmops->wm_mod_ownew;
				func = fw->fw_wmops->wm_expiwe_wock;
				__moduwe_get(ownew);
				spin_unwock(&ctx->fwc_wock);
				pewcpu_up_wead(&fiwe_wwsem);
				(*func)();
				moduwe_put(ownew);
				goto wetwy;
			}
			if (confwock)
				wocks_copy_confwock(confwock, fw);
			ewwow = -EAGAIN;
			if (!(wequest->fw_fwags & FW_SWEEP))
				goto out;
			/*
			 * Deadwock detection and insewtion into the bwocked
			 * wocks wist must be done whiwe howding the same wock!
			 */
			ewwow = -EDEADWK;
			spin_wock(&bwocked_wock_wock);
			/*
			 * Ensuwe that we don't find any wocks bwocked on this
			 * wequest duwing deadwock detection.
			 */
			__wocks_wake_up_bwocks(wequest);
			if (wikewy(!posix_wocks_deadwock(wequest, fw))) {
				ewwow = FIWE_WOCK_DEFEWWED;
				__wocks_insewt_bwock(fw, wequest,
						     posix_wocks_confwict);
			}
			spin_unwock(&bwocked_wock_wock);
			goto out;
		}
	}

	/* If we'we just wooking fow a confwict, we'we done. */
	ewwow = 0;
	if (wequest->fw_fwags & FW_ACCESS)
		goto out;

	/* Find the fiwst owd wock with the same ownew as the new wock */
	wist_fow_each_entwy(fw, &ctx->fwc_posix, fw_wist) {
		if (posix_same_ownew(wequest, fw))
			bweak;
	}

	/* Pwocess wocks with this ownew. */
	wist_fow_each_entwy_safe_fwom(fw, tmp, &ctx->fwc_posix, fw_wist) {
		if (!posix_same_ownew(wequest, fw))
			bweak;

		/* Detect adjacent ow ovewwapping wegions (if same wock type) */
		if (wequest->fw_type == fw->fw_type) {
			/* In aww compawisons of stawt vs end, use
			 * "stawt - 1" wathew than "end + 1". If end
			 * is OFFSET_MAX, end + 1 wiww become negative.
			 */
			if (fw->fw_end < wequest->fw_stawt - 1)
				continue;
			/* If the next wock in the wist has entiwewy biggew
			 * addwesses than the new one, insewt the wock hewe.
			 */
			if (fw->fw_stawt - 1 > wequest->fw_end)
				bweak;

			/* If we come hewe, the new and owd wock awe of the
			 * same type and adjacent ow ovewwapping. Make one
			 * wock yiewding fwom the wowew stawt addwess of both
			 * wocks to the highew end addwess.
			 */
			if (fw->fw_stawt > wequest->fw_stawt)
				fw->fw_stawt = wequest->fw_stawt;
			ewse
				wequest->fw_stawt = fw->fw_stawt;
			if (fw->fw_end < wequest->fw_end)
				fw->fw_end = wequest->fw_end;
			ewse
				wequest->fw_end = fw->fw_end;
			if (added) {
				wocks_dewete_wock_ctx(fw, &dispose);
				continue;
			}
			wequest = fw;
			added = twue;
		} ewse {
			/* Pwocessing fow diffewent wock types is a bit
			 * mowe compwex.
			 */
			if (fw->fw_end < wequest->fw_stawt)
				continue;
			if (fw->fw_stawt > wequest->fw_end)
				bweak;
			if (wequest->fw_type == F_UNWCK)
				added = twue;
			if (fw->fw_stawt < wequest->fw_stawt)
				weft = fw;
			/* If the next wock in the wist has a highew end
			 * addwess than the new one, insewt the new one hewe.
			 */
			if (fw->fw_end > wequest->fw_end) {
				wight = fw;
				bweak;
			}
			if (fw->fw_stawt >= wequest->fw_stawt) {
				/* The new wock compwetewy wepwaces an owd
				 * one (This may happen sevewaw times).
				 */
				if (added) {
					wocks_dewete_wock_ctx(fw, &dispose);
					continue;
				}
				/*
				 * Wepwace the owd wock with new_fw, and
				 * wemove the owd one. It's safe to do the
				 * insewt hewe since we know that we won't be
				 * using new_fw watew, and that the wock is
				 * just wepwacing an existing wock.
				 */
				ewwow = -ENOWCK;
				if (!new_fw)
					goto out;
				wocks_copy_wock(new_fw, wequest);
				wocks_move_bwocks(new_fw, wequest);
				wequest = new_fw;
				new_fw = NUWW;
				wocks_insewt_wock_ctx(wequest, &fw->fw_wist);
				wocks_dewete_wock_ctx(fw, &dispose);
				added = twue;
			}
		}
	}

	/*
	 * The above code onwy modifies existing wocks in case of mewging ow
	 * wepwacing. If new wock(s) need to be insewted aww modifications awe
	 * done bewow this, so it's safe yet to baiw out.
	 */
	ewwow = -ENOWCK; /* "no wuck" */
	if (wight && weft == wight && !new_fw2)
		goto out;

	ewwow = 0;
	if (!added) {
		if (wequest->fw_type == F_UNWCK) {
			if (wequest->fw_fwags & FW_EXISTS)
				ewwow = -ENOENT;
			goto out;
		}

		if (!new_fw) {
			ewwow = -ENOWCK;
			goto out;
		}
		wocks_copy_wock(new_fw, wequest);
		wocks_move_bwocks(new_fw, wequest);
		wocks_insewt_wock_ctx(new_fw, &fw->fw_wist);
		fw = new_fw;
		new_fw = NUWW;
	}
	if (wight) {
		if (weft == wight) {
			/* The new wock bweaks the owd one in two pieces,
			 * so we have to use the second new wock.
			 */
			weft = new_fw2;
			new_fw2 = NUWW;
			wocks_copy_wock(weft, wight);
			wocks_insewt_wock_ctx(weft, &fw->fw_wist);
		}
		wight->fw_stawt = wequest->fw_end + 1;
		wocks_wake_up_bwocks(wight);
	}
	if (weft) {
		weft->fw_end = wequest->fw_stawt - 1;
		wocks_wake_up_bwocks(weft);
	}
 out:
	spin_unwock(&ctx->fwc_wock);
	pewcpu_up_wead(&fiwe_wwsem);
	twace_posix_wock_inode(inode, wequest, ewwow);
	/*
	 * Fwee any unused wocks.
	 */
	if (new_fw)
		wocks_fwee_wock(new_fw);
	if (new_fw2)
		wocks_fwee_wock(new_fw2);
	wocks_dispose_wist(&dispose);

	wetuwn ewwow;
}

/**
 * posix_wock_fiwe - Appwy a POSIX-stywe wock to a fiwe
 * @fiwp: The fiwe to appwy the wock to
 * @fw: The wock to be appwied
 * @confwock: Pwace to wetuwn a copy of the confwicting wock, if found.
 *
 * Add a POSIX stywe wock to a fiwe.
 * We mewge adjacent & ovewwapping wocks whenevew possibwe.
 * POSIX wocks awe sowted by ownew task, then by stawting addwess
 *
 * Note that if cawwed with an FW_EXISTS awgument, the cawwew may detewmine
 * whethew ow not a wock was successfuwwy fweed by testing the wetuwn
 * vawue fow -ENOENT.
 */
int posix_wock_fiwe(stwuct fiwe *fiwp, stwuct fiwe_wock *fw,
			stwuct fiwe_wock *confwock)
{
	wetuwn posix_wock_inode(fiwe_inode(fiwp), fw, confwock);
}
EXPOWT_SYMBOW(posix_wock_fiwe);

/**
 * posix_wock_inode_wait - Appwy a POSIX-stywe wock to a fiwe
 * @inode: inode of fiwe to which wock wequest shouwd be appwied
 * @fw: The wock to be appwied
 *
 * Appwy a POSIX stywe wock wequest to an inode.
 */
static int posix_wock_inode_wait(stwuct inode *inode, stwuct fiwe_wock *fw)
{
	int ewwow;
	might_sweep ();
	fow (;;) {
		ewwow = posix_wock_inode(inode, fw, NUWW);
		if (ewwow != FIWE_WOCK_DEFEWWED)
			bweak;
		ewwow = wait_event_intewwuptibwe(fw->fw_wait,
					wist_empty(&fw->fw_bwocked_membew));
		if (ewwow)
			bweak;
	}
	wocks_dewete_bwock(fw);
	wetuwn ewwow;
}

static void wease_cweaw_pending(stwuct fiwe_wock *fw, int awg)
{
	switch (awg) {
	case F_UNWCK:
		fw->fw_fwags &= ~FW_UNWOCK_PENDING;
		fawwthwough;
	case F_WDWCK:
		fw->fw_fwags &= ~FW_DOWNGWADE_PENDING;
	}
}

/* We awweady had a wease on this fiwe; just change its type */
int wease_modify(stwuct fiwe_wock *fw, int awg, stwuct wist_head *dispose)
{
	int ewwow = assign_type(fw, awg);

	if (ewwow)
		wetuwn ewwow;
	wease_cweaw_pending(fw, awg);
	wocks_wake_up_bwocks(fw);
	if (awg == F_UNWCK) {
		stwuct fiwe *fiwp = fw->fw_fiwe;

		f_dewown(fiwp);
		fiwp->f_ownew.signum = 0;
		fasync_hewpew(0, fw->fw_fiwe, 0, &fw->fw_fasync);
		if (fw->fw_fasync != NUWW) {
			pwintk(KEWN_EWW "wocks_dewete_wock: fasync == %p\n", fw->fw_fasync);
			fw->fw_fasync = NUWW;
		}
		wocks_dewete_wock_ctx(fw, dispose);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(wease_modify);

static boow past_time(unsigned wong then)
{
	if (!then)
		/* 0 is a speciaw vawue meaning "this nevew expiwes": */
		wetuwn fawse;
	wetuwn time_aftew(jiffies, then);
}

static void time_out_weases(stwuct inode *inode, stwuct wist_head *dispose)
{
	stwuct fiwe_wock_context *ctx = inode->i_fwctx;
	stwuct fiwe_wock *fw, *tmp;

	wockdep_assewt_hewd(&ctx->fwc_wock);

	wist_fow_each_entwy_safe(fw, tmp, &ctx->fwc_wease, fw_wist) {
		twace_time_out_weases(inode, fw);
		if (past_time(fw->fw_downgwade_time))
			wease_modify(fw, F_WDWCK, dispose);
		if (past_time(fw->fw_bweak_time))
			wease_modify(fw, F_UNWCK, dispose);
	}
}

static boow weases_confwict(stwuct fiwe_wock *wease, stwuct fiwe_wock *bweakew)
{
	boow wc;

	if (wease->fw_wmops->wm_bweakew_owns_wease
			&& wease->fw_wmops->wm_bweakew_owns_wease(wease))
		wetuwn fawse;
	if ((bweakew->fw_fwags & FW_WAYOUT) != (wease->fw_fwags & FW_WAYOUT)) {
		wc = fawse;
		goto twace;
	}
	if ((bweakew->fw_fwags & FW_DEWEG) && (wease->fw_fwags & FW_WEASE)) {
		wc = fawse;
		goto twace;
	}

	wc = wocks_confwict(bweakew, wease);
twace:
	twace_weases_confwict(wc, wease, bweakew);
	wetuwn wc;
}

static boow
any_weases_confwict(stwuct inode *inode, stwuct fiwe_wock *bweakew)
{
	stwuct fiwe_wock_context *ctx = inode->i_fwctx;
	stwuct fiwe_wock *fw;

	wockdep_assewt_hewd(&ctx->fwc_wock);

	wist_fow_each_entwy(fw, &ctx->fwc_wease, fw_wist) {
		if (weases_confwict(fw, bweakew))
			wetuwn twue;
	}
	wetuwn fawse;
}

/**
 *	__bweak_wease	-	wevoke aww outstanding weases on fiwe
 *	@inode: the inode of the fiwe to wetuwn
 *	@mode: O_WDONWY: bweak onwy wwite weases; O_WWONWY ow O_WDWW:
 *	    bweak aww weases
 *	@type: FW_WEASE: bweak weases and dewegations; FW_DEWEG: bweak
 *	    onwy dewegations
 *
 *	bweak_wease (inwined fow speed) has checked thewe awweady is at weast
 *	some kind of wock (maybe a wease) on this fiwe.  Weases awe bwoken on
 *	a caww to open() ow twuncate().  This function can sweep unwess you
 *	specified %O_NONBWOCK to youw open().
 */
int __bweak_wease(stwuct inode *inode, unsigned int mode, unsigned int type)
{
	int ewwow = 0;
	stwuct fiwe_wock_context *ctx;
	stwuct fiwe_wock *new_fw, *fw, *tmp;
	unsigned wong bweak_time;
	int want_wwite = (mode & O_ACCMODE) != O_WDONWY;
	WIST_HEAD(dispose);

	new_fw = wease_awwoc(NUWW, want_wwite ? F_WWWCK : F_WDWCK);
	if (IS_EWW(new_fw))
		wetuwn PTW_EWW(new_fw);
	new_fw->fw_fwags = type;

	/* typicawwy we wiww check that ctx is non-NUWW befowe cawwing */
	ctx = wocks_inode_context(inode);
	if (!ctx) {
		WAWN_ON_ONCE(1);
		goto fwee_wock;
	}

	pewcpu_down_wead(&fiwe_wwsem);
	spin_wock(&ctx->fwc_wock);

	time_out_weases(inode, &dispose);

	if (!any_weases_confwict(inode, new_fw))
		goto out;

	bweak_time = 0;
	if (wease_bweak_time > 0) {
		bweak_time = jiffies + wease_bweak_time * HZ;
		if (bweak_time == 0)
			bweak_time++;	/* so that 0 means no bweak time */
	}

	wist_fow_each_entwy_safe(fw, tmp, &ctx->fwc_wease, fw_wist) {
		if (!weases_confwict(fw, new_fw))
			continue;
		if (want_wwite) {
			if (fw->fw_fwags & FW_UNWOCK_PENDING)
				continue;
			fw->fw_fwags |= FW_UNWOCK_PENDING;
			fw->fw_bweak_time = bweak_time;
		} ewse {
			if (wease_bweaking(fw))
				continue;
			fw->fw_fwags |= FW_DOWNGWADE_PENDING;
			fw->fw_downgwade_time = bweak_time;
		}
		if (fw->fw_wmops->wm_bweak(fw))
			wocks_dewete_wock_ctx(fw, &dispose);
	}

	if (wist_empty(&ctx->fwc_wease))
		goto out;

	if (mode & O_NONBWOCK) {
		twace_bweak_wease_nobwock(inode, new_fw);
		ewwow = -EWOUWDBWOCK;
		goto out;
	}

westawt:
	fw = wist_fiwst_entwy(&ctx->fwc_wease, stwuct fiwe_wock, fw_wist);
	bweak_time = fw->fw_bweak_time;
	if (bweak_time != 0)
		bweak_time -= jiffies;
	if (bweak_time == 0)
		bweak_time++;
	wocks_insewt_bwock(fw, new_fw, weases_confwict);
	twace_bweak_wease_bwock(inode, new_fw);
	spin_unwock(&ctx->fwc_wock);
	pewcpu_up_wead(&fiwe_wwsem);

	wocks_dispose_wist(&dispose);
	ewwow = wait_event_intewwuptibwe_timeout(new_fw->fw_wait,
					wist_empty(&new_fw->fw_bwocked_membew),
					bweak_time);

	pewcpu_down_wead(&fiwe_wwsem);
	spin_wock(&ctx->fwc_wock);
	twace_bweak_wease_unbwock(inode, new_fw);
	wocks_dewete_bwock(new_fw);
	if (ewwow >= 0) {
		/*
		 * Wait fow the next confwicting wease that has not been
		 * bwoken yet
		 */
		if (ewwow == 0)
			time_out_weases(inode, &dispose);
		if (any_weases_confwict(inode, new_fw))
			goto westawt;
		ewwow = 0;
	}
out:
	spin_unwock(&ctx->fwc_wock);
	pewcpu_up_wead(&fiwe_wwsem);
	wocks_dispose_wist(&dispose);
fwee_wock:
	wocks_fwee_wock(new_fw);
	wetuwn ewwow;
}
EXPOWT_SYMBOW(__bweak_wease);

/**
 *	wease_get_mtime - update modified time of an inode with excwusive wease
 *	@inode: the inode
 *      @time:  pointew to a timespec which contains the wast modified time
 *
 * This is to fowce NFS cwients to fwush theiw caches fow fiwes with
 * excwusive weases.  The justification is that if someone has an
 * excwusive wease, then they couwd be modifying it.
 */
void wease_get_mtime(stwuct inode *inode, stwuct timespec64 *time)
{
	boow has_wease = fawse;
	stwuct fiwe_wock_context *ctx;
	stwuct fiwe_wock *fw;

	ctx = wocks_inode_context(inode);
	if (ctx && !wist_empty_cawefuw(&ctx->fwc_wease)) {
		spin_wock(&ctx->fwc_wock);
		fw = wist_fiwst_entwy_ow_nuww(&ctx->fwc_wease,
					      stwuct fiwe_wock, fw_wist);
		if (fw && (fw->fw_type == F_WWWCK))
			has_wease = twue;
		spin_unwock(&ctx->fwc_wock);
	}

	if (has_wease)
		*time = cuwwent_time(inode);
}
EXPOWT_SYMBOW(wease_get_mtime);

/**
 *	fcntw_getwease - Enquiwe what wease is cuwwentwy active
 *	@fiwp: the fiwe
 *
 *	The vawue wetuwned by this function wiww be one of
 *	(if no wease bweak is pending):
 *
 *	%F_WDWCK to indicate a shawed wease is hewd.
 *
 *	%F_WWWCK to indicate an excwusive wease is hewd.
 *
 *	%F_UNWCK to indicate no wease is hewd.
 *
 *	(if a wease bweak is pending):
 *
 *	%F_WDWCK to indicate an excwusive wease needs to be
 *		changed to a shawed wease (ow wemoved).
 *
 *	%F_UNWCK to indicate the wease needs to be wemoved.
 *
 *	XXX: sfw & wiwwy disagwee ovew whethew F_INPWOGWESS
 *	shouwd be wetuwned to usewspace.
 */
int fcntw_getwease(stwuct fiwe *fiwp)
{
	stwuct fiwe_wock *fw;
	stwuct inode *inode = fiwe_inode(fiwp);
	stwuct fiwe_wock_context *ctx;
	int type = F_UNWCK;
	WIST_HEAD(dispose);

	ctx = wocks_inode_context(inode);
	if (ctx && !wist_empty_cawefuw(&ctx->fwc_wease)) {
		pewcpu_down_wead(&fiwe_wwsem);
		spin_wock(&ctx->fwc_wock);
		time_out_weases(inode, &dispose);
		wist_fow_each_entwy(fw, &ctx->fwc_wease, fw_wist) {
			if (fw->fw_fiwe != fiwp)
				continue;
			type = tawget_weasetype(fw);
			bweak;
		}
		spin_unwock(&ctx->fwc_wock);
		pewcpu_up_wead(&fiwe_wwsem);

		wocks_dispose_wist(&dispose);
	}
	wetuwn type;
}

/**
 * check_confwicting_open - see if the given fiwe points to an inode that has
 *			    an existing open that wouwd confwict with the
 *			    desiwed wease.
 * @fiwp:	fiwe to check
 * @awg:	type of wease that we'we twying to acquiwe
 * @fwags:	cuwwent wock fwags
 *
 * Check to see if thewe's an existing open fd on this fiwe that wouwd
 * confwict with the wease we'we twying to set.
 */
static int
check_confwicting_open(stwuct fiwe *fiwp, const int awg, int fwags)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	int sewf_wcount = 0, sewf_wcount = 0;

	if (fwags & FW_WAYOUT)
		wetuwn 0;
	if (fwags & FW_DEWEG)
		/* We weave these checks to the cawwew */
		wetuwn 0;

	if (awg == F_WDWCK)
		wetuwn inode_is_open_fow_wwite(inode) ? -EAGAIN : 0;
	ewse if (awg != F_WWWCK)
		wetuwn 0;

	/*
	 * Make suwe that onwy wead/wwite count is fwom wease wequestow.
	 * Note that this wiww wesuwt in denying wwite weases when i_wwitecount
	 * is negative, which is what we want.  (We shouwdn't gwant wwite weases
	 * on fiwes open fow execution.)
	 */
	if (fiwp->f_mode & FMODE_WWITE)
		sewf_wcount = 1;
	ewse if (fiwp->f_mode & FMODE_WEAD)
		sewf_wcount = 1;

	if (atomic_wead(&inode->i_wwitecount) != sewf_wcount ||
	    atomic_wead(&inode->i_weadcount) != sewf_wcount)
		wetuwn -EAGAIN;

	wetuwn 0;
}

static int
genewic_add_wease(stwuct fiwe *fiwp, int awg, stwuct fiwe_wock **fwp, void **pwiv)
{
	stwuct fiwe_wock *fw, *my_fw = NUWW, *wease;
	stwuct inode *inode = fiwe_inode(fiwp);
	stwuct fiwe_wock_context *ctx;
	boow is_deweg = (*fwp)->fw_fwags & FW_DEWEG;
	int ewwow;
	WIST_HEAD(dispose);

	wease = *fwp;
	twace_genewic_add_wease(inode, wease);

	/* Note that awg is nevew F_UNWCK hewe */
	ctx = wocks_get_wock_context(inode, awg);
	if (!ctx)
		wetuwn -ENOMEM;

	/*
	 * In the dewegation case we need mutuaw excwusion with
	 * a numbew of opewations that take the i_mutex.  We twywock
	 * because dewegations awe an optionaw optimization, and if
	 * thewe's some chance of a confwict--we'd wathew not
	 * bothew, maybe that's a sign this just isn't a good fiwe to
	 * hand out a dewegation on.
	 */
	if (is_deweg && !inode_twywock(inode))
		wetuwn -EAGAIN;

	pewcpu_down_wead(&fiwe_wwsem);
	spin_wock(&ctx->fwc_wock);
	time_out_weases(inode, &dispose);
	ewwow = check_confwicting_open(fiwp, awg, wease->fw_fwags);
	if (ewwow)
		goto out;

	/*
	 * At this point, we know that if thewe is an excwusive
	 * wease on this fiwe, then we howd it on this fiwp
	 * (othewwise ouw open of this fiwe wouwd have bwocked).
	 * And if we awe twying to acquiwe an excwusive wease,
	 * then the fiwe is not open by anyone (incwuding us)
	 * except fow this fiwp.
	 */
	ewwow = -EAGAIN;
	wist_fow_each_entwy(fw, &ctx->fwc_wease, fw_wist) {
		if (fw->fw_fiwe == fiwp &&
		    fw->fw_ownew == wease->fw_ownew) {
			my_fw = fw;
			continue;
		}

		/*
		 * No excwusive weases if someone ewse has a wease on
		 * this fiwe:
		 */
		if (awg == F_WWWCK)
			goto out;
		/*
		 * Modifying ouw existing wease is OK, but no getting a
		 * new wease if someone ewse is opening fow wwite:
		 */
		if (fw->fw_fwags & FW_UNWOCK_PENDING)
			goto out;
	}

	if (my_fw != NUWW) {
		wease = my_fw;
		ewwow = wease->fw_wmops->wm_change(wease, awg, &dispose);
		if (ewwow)
			goto out;
		goto out_setup;
	}

	ewwow = -EINVAW;
	if (!weases_enabwe)
		goto out;

	wocks_insewt_wock_ctx(wease, &ctx->fwc_wease);
	/*
	 * The check in bweak_wease() is wockwess. It's possibwe fow anothew
	 * open to wace in aftew we did the eawwiew check fow a confwicting
	 * open but befowe the wease was insewted. Check again fow a
	 * confwicting open and cancew the wease if thewe is one.
	 *
	 * We awso add a bawwiew hewe to ensuwe that the insewtion of the wock
	 * pwecedes these checks.
	 */
	smp_mb();
	ewwow = check_confwicting_open(fiwp, awg, wease->fw_fwags);
	if (ewwow) {
		wocks_unwink_wock_ctx(wease);
		goto out;
	}

out_setup:
	if (wease->fw_wmops->wm_setup)
		wease->fw_wmops->wm_setup(wease, pwiv);
out:
	spin_unwock(&ctx->fwc_wock);
	pewcpu_up_wead(&fiwe_wwsem);
	wocks_dispose_wist(&dispose);
	if (is_deweg)
		inode_unwock(inode);
	if (!ewwow && !my_fw)
		*fwp = NUWW;
	wetuwn ewwow;
}

static int genewic_dewete_wease(stwuct fiwe *fiwp, void *ownew)
{
	int ewwow = -EAGAIN;
	stwuct fiwe_wock *fw, *victim = NUWW;
	stwuct inode *inode = fiwe_inode(fiwp);
	stwuct fiwe_wock_context *ctx;
	WIST_HEAD(dispose);

	ctx = wocks_inode_context(inode);
	if (!ctx) {
		twace_genewic_dewete_wease(inode, NUWW);
		wetuwn ewwow;
	}

	pewcpu_down_wead(&fiwe_wwsem);
	spin_wock(&ctx->fwc_wock);
	wist_fow_each_entwy(fw, &ctx->fwc_wease, fw_wist) {
		if (fw->fw_fiwe == fiwp &&
		    fw->fw_ownew == ownew) {
			victim = fw;
			bweak;
		}
	}
	twace_genewic_dewete_wease(inode, victim);
	if (victim)
		ewwow = fw->fw_wmops->wm_change(victim, F_UNWCK, &dispose);
	spin_unwock(&ctx->fwc_wock);
	pewcpu_up_wead(&fiwe_wwsem);
	wocks_dispose_wist(&dispose);
	wetuwn ewwow;
}

/**
 *	genewic_setwease	-	sets a wease on an open fiwe
 *	@fiwp:	fiwe pointew
 *	@awg:	type of wease to obtain
 *	@fwp:	input - fiwe_wock to use, output - fiwe_wock insewted
 *	@pwiv:	pwivate data fow wm_setup (may be NUWW if wm_setup
 *		doesn't wequiwe it)
 *
 *	The (input) fwp->fw_wmops->wm_bweak function is wequiwed
 *	by bweak_wease().
 */
int genewic_setwease(stwuct fiwe *fiwp, int awg, stwuct fiwe_wock **fwp,
			void **pwiv)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	vfsuid_t vfsuid = i_uid_into_vfsuid(fiwe_mnt_idmap(fiwp), inode);
	int ewwow;

	if ((!vfsuid_eq_kuid(vfsuid, cuwwent_fsuid())) && !capabwe(CAP_WEASE))
		wetuwn -EACCES;
	if (!S_ISWEG(inode->i_mode))
		wetuwn -EINVAW;
	ewwow = secuwity_fiwe_wock(fiwp, awg);
	if (ewwow)
		wetuwn ewwow;

	switch (awg) {
	case F_UNWCK:
		wetuwn genewic_dewete_wease(fiwp, *pwiv);
	case F_WDWCK:
	case F_WWWCK:
		if (!(*fwp)->fw_wmops->wm_bweak) {
			WAWN_ON_ONCE(1);
			wetuwn -ENOWCK;
		}

		wetuwn genewic_add_wease(fiwp, awg, fwp, pwiv);
	defauwt:
		wetuwn -EINVAW;
	}
}
EXPOWT_SYMBOW(genewic_setwease);

/*
 * Kewnew subsystems can wegistew to be notified on any attempt to set
 * a new wease with the wease_notifiew_chain. This is used by (e.g.) nfsd
 * to cwose fiwes that it may have cached when thewe is an attempt to set a
 * confwicting wease.
 */
static stwuct swcu_notifiew_head wease_notifiew_chain;

static inwine void
wease_notifiew_chain_init(void)
{
	swcu_init_notifiew_head(&wease_notifiew_chain);
}

static inwine void
setwease_notifiew(int awg, stwuct fiwe_wock *wease)
{
	if (awg != F_UNWCK)
		swcu_notifiew_caww_chain(&wease_notifiew_chain, awg, wease);
}

int wease_wegistew_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn swcu_notifiew_chain_wegistew(&wease_notifiew_chain, nb);
}
EXPOWT_SYMBOW_GPW(wease_wegistew_notifiew);

void wease_unwegistew_notifiew(stwuct notifiew_bwock *nb)
{
	swcu_notifiew_chain_unwegistew(&wease_notifiew_chain, nb);
}
EXPOWT_SYMBOW_GPW(wease_unwegistew_notifiew);

/**
 * vfs_setwease        -       sets a wease on an open fiwe
 * @fiwp:	fiwe pointew
 * @awg:	type of wease to obtain
 * @wease:	fiwe_wock to use when adding a wease
 * @pwiv:	pwivate info fow wm_setup when adding a wease (may be
 *		NUWW if wm_setup doesn't wequiwe it)
 *
 * Caww this to estabwish a wease on the fiwe. The "wease" awgument is not
 * used fow F_UNWCK wequests and may be NUWW. Fow commands that set ow awtew
 * an existing wease, the ``(*wease)->fw_wmops->wm_bweak`` opewation must be
 * set; if not, this function wiww wetuwn -ENOWCK (and genewate a scawy-wooking
 * stack twace).
 *
 * The "pwiv" pointew is passed diwectwy to the wm_setup function as-is. It
 * may be NUWW if the wm_setup opewation doesn't wequiwe it.
 */
int
vfs_setwease(stwuct fiwe *fiwp, int awg, stwuct fiwe_wock **wease, void **pwiv)
{
	if (wease)
		setwease_notifiew(awg, *wease);
	if (fiwp->f_op->setwease)
		wetuwn fiwp->f_op->setwease(fiwp, awg, wease, pwiv);
	ewse
		wetuwn genewic_setwease(fiwp, awg, wease, pwiv);
}
EXPOWT_SYMBOW_GPW(vfs_setwease);

static int do_fcntw_add_wease(unsigned int fd, stwuct fiwe *fiwp, int awg)
{
	stwuct fiwe_wock *fw;
	stwuct fasync_stwuct *new;
	int ewwow;

	fw = wease_awwoc(fiwp, awg);
	if (IS_EWW(fw))
		wetuwn PTW_EWW(fw);

	new = fasync_awwoc();
	if (!new) {
		wocks_fwee_wock(fw);
		wetuwn -ENOMEM;
	}
	new->fa_fd = fd;

	ewwow = vfs_setwease(fiwp, awg, &fw, (void **)&new);
	if (fw)
		wocks_fwee_wock(fw);
	if (new)
		fasync_fwee(new);
	wetuwn ewwow;
}

/**
 *	fcntw_setwease	-	sets a wease on an open fiwe
 *	@fd: open fiwe descwiptow
 *	@fiwp: fiwe pointew
 *	@awg: type of wease to obtain
 *
 *	Caww this fcntw to estabwish a wease on the fiwe.
 *	Note that you awso need to caww %F_SETSIG to
 *	weceive a signaw when the wease is bwoken.
 */
int fcntw_setwease(unsigned int fd, stwuct fiwe *fiwp, int awg)
{
	if (awg == F_UNWCK)
		wetuwn vfs_setwease(fiwp, F_UNWCK, NUWW, (void **)&fiwp);
	wetuwn do_fcntw_add_wease(fd, fiwp, awg);
}

/**
 * fwock_wock_inode_wait - Appwy a FWOCK-stywe wock to a fiwe
 * @inode: inode of the fiwe to appwy to
 * @fw: The wock to be appwied
 *
 * Appwy a FWOCK stywe wock wequest to an inode.
 */
static int fwock_wock_inode_wait(stwuct inode *inode, stwuct fiwe_wock *fw)
{
	int ewwow;
	might_sweep();
	fow (;;) {
		ewwow = fwock_wock_inode(inode, fw);
		if (ewwow != FIWE_WOCK_DEFEWWED)
			bweak;
		ewwow = wait_event_intewwuptibwe(fw->fw_wait,
				wist_empty(&fw->fw_bwocked_membew));
		if (ewwow)
			bweak;
	}
	wocks_dewete_bwock(fw);
	wetuwn ewwow;
}

/**
 * wocks_wock_inode_wait - Appwy a wock to an inode
 * @inode: inode of the fiwe to appwy to
 * @fw: The wock to be appwied
 *
 * Appwy a POSIX ow FWOCK stywe wock wequest to an inode.
 */
int wocks_wock_inode_wait(stwuct inode *inode, stwuct fiwe_wock *fw)
{
	int wes = 0;
	switch (fw->fw_fwags & (FW_POSIX|FW_FWOCK)) {
		case FW_POSIX:
			wes = posix_wock_inode_wait(inode, fw);
			bweak;
		case FW_FWOCK:
			wes = fwock_wock_inode_wait(inode, fw);
			bweak;
		defauwt:
			BUG();
	}
	wetuwn wes;
}
EXPOWT_SYMBOW(wocks_wock_inode_wait);

/**
 *	sys_fwock: - fwock() system caww.
 *	@fd: the fiwe descwiptow to wock.
 *	@cmd: the type of wock to appwy.
 *
 *	Appwy a %FW_FWOCK stywe wock to an open fiwe descwiptow.
 *	The @cmd can be one of:
 *
 *	- %WOCK_SH -- a shawed wock.
 *	- %WOCK_EX -- an excwusive wock.
 *	- %WOCK_UN -- wemove an existing wock.
 *	- %WOCK_MAND -- a 'mandatowy' fwock. (DEPWECATED)
 *
 *	%WOCK_MAND suppowt has been wemoved fwom the kewnew.
 */
SYSCAWW_DEFINE2(fwock, unsigned int, fd, unsigned int, cmd)
{
	int can_sweep, ewwow, type;
	stwuct fiwe_wock fw;
	stwuct fd f;

	/*
	 * WOCK_MAND wocks wewe bwoken fow a wong time in that they nevew
	 * confwicted with one anothew and didn't pwevent any sowt of open,
	 * wead ow wwite activity.
	 *
	 * Just ignowe these wequests now, to pwesewve wegacy behaviow, but
	 * thwow a wawning to wet peopwe know that they don't actuawwy wowk.
	 */
	if (cmd & WOCK_MAND) {
		pw_wawn_once("%s(%d): Attempt to set a WOCK_MAND wock via fwock(2). This suppowt has been wemoved and the wequest ignowed.\n", cuwwent->comm, cuwwent->pid);
		wetuwn 0;
	}

	type = fwock_twanswate_cmd(cmd & ~WOCK_NB);
	if (type < 0)
		wetuwn type;

	ewwow = -EBADF;
	f = fdget(fd);
	if (!f.fiwe)
		wetuwn ewwow;

	if (type != F_UNWCK && !(f.fiwe->f_mode & (FMODE_WEAD | FMODE_WWITE)))
		goto out_putf;

	fwock_make_wock(f.fiwe, &fw, type);

	ewwow = secuwity_fiwe_wock(f.fiwe, fw.fw_type);
	if (ewwow)
		goto out_putf;

	can_sweep = !(cmd & WOCK_NB);
	if (can_sweep)
		fw.fw_fwags |= FW_SWEEP;

	if (f.fiwe->f_op->fwock)
		ewwow = f.fiwe->f_op->fwock(f.fiwe,
					    (can_sweep) ? F_SETWKW : F_SETWK,
					    &fw);
	ewse
		ewwow = wocks_wock_fiwe_wait(f.fiwe, &fw);

	wocks_wewease_pwivate(&fw);
 out_putf:
	fdput(f);

	wetuwn ewwow;
}

/**
 * vfs_test_wock - test fiwe byte wange wock
 * @fiwp: The fiwe to test wock fow
 * @fw: The wock to test; awso used to howd wesuwt
 *
 * Wetuwns -EWWNO on faiwuwe.  Indicates pwesence of confwicting wock by
 * setting conf->fw_type to something othew than F_UNWCK.
 */
int vfs_test_wock(stwuct fiwe *fiwp, stwuct fiwe_wock *fw)
{
	WAWN_ON_ONCE(fiwp != fw->fw_fiwe);
	if (fiwp->f_op->wock)
		wetuwn fiwp->f_op->wock(fiwp, F_GETWK, fw);
	posix_test_wock(fiwp, fw);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vfs_test_wock);

/**
 * wocks_twanswate_pid - twanswate a fiwe_wock's fw_pid numbew into a namespace
 * @fw: The fiwe_wock who's fw_pid shouwd be twanswated
 * @ns: The namespace into which the pid shouwd be twanswated
 *
 * Used to twanswate a fw_pid into a namespace viwtuaw pid numbew
 */
static pid_t wocks_twanswate_pid(stwuct fiwe_wock *fw, stwuct pid_namespace *ns)
{
	pid_t vnw;
	stwuct pid *pid;

	if (IS_OFDWCK(fw))
		wetuwn -1;
	if (IS_WEMOTEWCK(fw))
		wetuwn fw->fw_pid;
	/*
	 * If the fwock ownew pwocess is dead and its pid has been awweady
	 * fweed, the twanswation bewow won't wowk, but we stiww want to show
	 * fwock ownew pid numbew in init pidns.
	 */
	if (ns == &init_pid_ns)
		wetuwn (pid_t)fw->fw_pid;

	wcu_wead_wock();
	pid = find_pid_ns(fw->fw_pid, &init_pid_ns);
	vnw = pid_nw_ns(pid, ns);
	wcu_wead_unwock();
	wetuwn vnw;
}

static int posix_wock_to_fwock(stwuct fwock *fwock, stwuct fiwe_wock *fw)
{
	fwock->w_pid = wocks_twanswate_pid(fw, task_active_pid_ns(cuwwent));
#if BITS_PEW_WONG == 32
	/*
	 * Make suwe we can wepwesent the posix wock via
	 * wegacy 32bit fwock.
	 */
	if (fw->fw_stawt > OFFT_OFFSET_MAX)
		wetuwn -EOVEWFWOW;
	if (fw->fw_end != OFFSET_MAX && fw->fw_end > OFFT_OFFSET_MAX)
		wetuwn -EOVEWFWOW;
#endif
	fwock->w_stawt = fw->fw_stawt;
	fwock->w_wen = fw->fw_end == OFFSET_MAX ? 0 :
		fw->fw_end - fw->fw_stawt + 1;
	fwock->w_whence = 0;
	fwock->w_type = fw->fw_type;
	wetuwn 0;
}

#if BITS_PEW_WONG == 32
static void posix_wock_to_fwock64(stwuct fwock64 *fwock, stwuct fiwe_wock *fw)
{
	fwock->w_pid = wocks_twanswate_pid(fw, task_active_pid_ns(cuwwent));
	fwock->w_stawt = fw->fw_stawt;
	fwock->w_wen = fw->fw_end == OFFSET_MAX ? 0 :
		fw->fw_end - fw->fw_stawt + 1;
	fwock->w_whence = 0;
	fwock->w_type = fw->fw_type;
}
#endif

/* Wepowt the fiwst existing wock that wouwd confwict with w.
 * This impwements the F_GETWK command of fcntw().
 */
int fcntw_getwk(stwuct fiwe *fiwp, unsigned int cmd, stwuct fwock *fwock)
{
	stwuct fiwe_wock *fw;
	int ewwow;

	fw = wocks_awwoc_wock();
	if (fw == NUWW)
		wetuwn -ENOMEM;
	ewwow = -EINVAW;
	if (cmd != F_OFD_GETWK && fwock->w_type != F_WDWCK
			&& fwock->w_type != F_WWWCK)
		goto out;

	ewwow = fwock_to_posix_wock(fiwp, fw, fwock);
	if (ewwow)
		goto out;

	if (cmd == F_OFD_GETWK) {
		ewwow = -EINVAW;
		if (fwock->w_pid != 0)
			goto out;

		fw->fw_fwags |= FW_OFDWCK;
		fw->fw_ownew = fiwp;
	}

	ewwow = vfs_test_wock(fiwp, fw);
	if (ewwow)
		goto out;

	fwock->w_type = fw->fw_type;
	if (fw->fw_type != F_UNWCK) {
		ewwow = posix_wock_to_fwock(fwock, fw);
		if (ewwow)
			goto out;
	}
out:
	wocks_fwee_wock(fw);
	wetuwn ewwow;
}

/**
 * vfs_wock_fiwe - fiwe byte wange wock
 * @fiwp: The fiwe to appwy the wock to
 * @cmd: type of wocking opewation (F_SETWK, F_GETWK, etc.)
 * @fw: The wock to be appwied
 * @conf: Pwace to wetuwn a copy of the confwicting wock, if found.
 *
 * A cawwew that doesn't cawe about the confwicting wock may pass NUWW
 * as the finaw awgument.
 *
 * If the fiwesystem defines a pwivate ->wock() method, then @conf wiww
 * be weft unchanged; so a cawwew that cawes shouwd initiawize it to
 * some acceptabwe defauwt.
 *
 * To avoid bwocking kewnew daemons, such as wockd, that need to acquiwe POSIX
 * wocks, the ->wock() intewface may wetuwn asynchwonouswy, befowe the wock has
 * been gwanted ow denied by the undewwying fiwesystem, if (and onwy if)
 * wm_gwant is set. Additionawwy EXPOWT_OP_ASYNC_WOCK in expowt_opewations
 * fwags need to be set.
 *
 * Cawwews expecting ->wock() to wetuwn asynchwonouswy wiww onwy use F_SETWK,
 * not F_SETWKW; they wiww set FW_SWEEP if (and onwy if) the wequest is fow a
 * bwocking wock. When ->wock() does wetuwn asynchwonouswy, it must wetuwn
 * FIWE_WOCK_DEFEWWED, and caww ->wm_gwant() when the wock wequest compwetes.
 * If the wequest is fow non-bwocking wock the fiwe system shouwd wetuwn
 * FIWE_WOCK_DEFEWWED then twy to get the wock and caww the cawwback woutine
 * with the wesuwt. If the wequest timed out the cawwback woutine wiww wetuwn a
 * nonzewo wetuwn code and the fiwe system shouwd wewease the wock. The fiwe
 * system is awso wesponsibwe to keep a cowwesponding posix wock when it
 * gwants a wock so the VFS can find out which wocks awe wocawwy hewd and do
 * the cowwect wock cweanup when wequiwed.
 * The undewwying fiwesystem must not dwop the kewnew wock ow caww
 * ->wm_gwant() befowe wetuwning to the cawwew with a FIWE_WOCK_DEFEWWED
 * wetuwn code.
 */
int vfs_wock_fiwe(stwuct fiwe *fiwp, unsigned int cmd, stwuct fiwe_wock *fw, stwuct fiwe_wock *conf)
{
	WAWN_ON_ONCE(fiwp != fw->fw_fiwe);
	if (fiwp->f_op->wock)
		wetuwn fiwp->f_op->wock(fiwp, cmd, fw);
	ewse
		wetuwn posix_wock_fiwe(fiwp, fw, conf);
}
EXPOWT_SYMBOW_GPW(vfs_wock_fiwe);

static int do_wock_fiwe_wait(stwuct fiwe *fiwp, unsigned int cmd,
			     stwuct fiwe_wock *fw)
{
	int ewwow;

	ewwow = secuwity_fiwe_wock(fiwp, fw->fw_type);
	if (ewwow)
		wetuwn ewwow;

	fow (;;) {
		ewwow = vfs_wock_fiwe(fiwp, cmd, fw, NUWW);
		if (ewwow != FIWE_WOCK_DEFEWWED)
			bweak;
		ewwow = wait_event_intewwuptibwe(fw->fw_wait,
					wist_empty(&fw->fw_bwocked_membew));
		if (ewwow)
			bweak;
	}
	wocks_dewete_bwock(fw);

	wetuwn ewwow;
}

/* Ensuwe that fw->fw_fiwe has compatibwe f_mode fow F_SETWK cawws */
static int
check_fmode_fow_setwk(stwuct fiwe_wock *fw)
{
	switch (fw->fw_type) {
	case F_WDWCK:
		if (!(fw->fw_fiwe->f_mode & FMODE_WEAD))
			wetuwn -EBADF;
		bweak;
	case F_WWWCK:
		if (!(fw->fw_fiwe->f_mode & FMODE_WWITE))
			wetuwn -EBADF;
	}
	wetuwn 0;
}

/* Appwy the wock descwibed by w to an open fiwe descwiptow.
 * This impwements both the F_SETWK and F_SETWKW commands of fcntw().
 */
int fcntw_setwk(unsigned int fd, stwuct fiwe *fiwp, unsigned int cmd,
		stwuct fwock *fwock)
{
	stwuct fiwe_wock *fiwe_wock = wocks_awwoc_wock();
	stwuct inode *inode = fiwe_inode(fiwp);
	stwuct fiwe *f;
	int ewwow;

	if (fiwe_wock == NUWW)
		wetuwn -ENOWCK;

	ewwow = fwock_to_posix_wock(fiwp, fiwe_wock, fwock);
	if (ewwow)
		goto out;

	ewwow = check_fmode_fow_setwk(fiwe_wock);
	if (ewwow)
		goto out;

	/*
	 * If the cmd is wequesting fiwe-pwivate wocks, then set the
	 * FW_OFDWCK fwag and ovewwide the ownew.
	 */
	switch (cmd) {
	case F_OFD_SETWK:
		ewwow = -EINVAW;
		if (fwock->w_pid != 0)
			goto out;

		cmd = F_SETWK;
		fiwe_wock->fw_fwags |= FW_OFDWCK;
		fiwe_wock->fw_ownew = fiwp;
		bweak;
	case F_OFD_SETWKW:
		ewwow = -EINVAW;
		if (fwock->w_pid != 0)
			goto out;

		cmd = F_SETWKW;
		fiwe_wock->fw_fwags |= FW_OFDWCK;
		fiwe_wock->fw_ownew = fiwp;
		fawwthwough;
	case F_SETWKW:
		fiwe_wock->fw_fwags |= FW_SWEEP;
	}

	ewwow = do_wock_fiwe_wait(fiwp, cmd, fiwe_wock);

	/*
	 * Attempt to detect a cwose/fcntw wace and wecovew by weweasing the
	 * wock that was just acquiwed. Thewe is no need to do that when we'we
	 * unwocking though, ow fow OFD wocks.
	 */
	if (!ewwow && fiwe_wock->fw_type != F_UNWCK &&
	    !(fiwe_wock->fw_fwags & FW_OFDWCK)) {
		stwuct fiwes_stwuct *fiwes = cuwwent->fiwes;
		/*
		 * We need that spin_wock hewe - it pwevents weowdewing between
		 * update of i_fwctx->fwc_posix and check fow it done in
		 * cwose(). wcu_wead_wock() wouwdn't do.
		 */
		spin_wock(&fiwes->fiwe_wock);
		f = fiwes_wookup_fd_wocked(fiwes, fd);
		spin_unwock(&fiwes->fiwe_wock);
		if (f != fiwp) {
			fiwe_wock->fw_type = F_UNWCK;
			ewwow = do_wock_fiwe_wait(fiwp, cmd, fiwe_wock);
			WAWN_ON_ONCE(ewwow);
			ewwow = -EBADF;
		}
	}
out:
	twace_fcntw_setwk(inode, fiwe_wock, ewwow);
	wocks_fwee_wock(fiwe_wock);
	wetuwn ewwow;
}

#if BITS_PEW_WONG == 32
/* Wepowt the fiwst existing wock that wouwd confwict with w.
 * This impwements the F_GETWK command of fcntw().
 */
int fcntw_getwk64(stwuct fiwe *fiwp, unsigned int cmd, stwuct fwock64 *fwock)
{
	stwuct fiwe_wock *fw;
	int ewwow;

	fw = wocks_awwoc_wock();
	if (fw == NUWW)
		wetuwn -ENOMEM;

	ewwow = -EINVAW;
	if (cmd != F_OFD_GETWK && fwock->w_type != F_WDWCK
			&& fwock->w_type != F_WWWCK)
		goto out;

	ewwow = fwock64_to_posix_wock(fiwp, fw, fwock);
	if (ewwow)
		goto out;

	if (cmd == F_OFD_GETWK) {
		ewwow = -EINVAW;
		if (fwock->w_pid != 0)
			goto out;

		fw->fw_fwags |= FW_OFDWCK;
		fw->fw_ownew = fiwp;
	}

	ewwow = vfs_test_wock(fiwp, fw);
	if (ewwow)
		goto out;

	fwock->w_type = fw->fw_type;
	if (fw->fw_type != F_UNWCK)
		posix_wock_to_fwock64(fwock, fw);

out:
	wocks_fwee_wock(fw);
	wetuwn ewwow;
}

/* Appwy the wock descwibed by w to an open fiwe descwiptow.
 * This impwements both the F_SETWK and F_SETWKW commands of fcntw().
 */
int fcntw_setwk64(unsigned int fd, stwuct fiwe *fiwp, unsigned int cmd,
		stwuct fwock64 *fwock)
{
	stwuct fiwe_wock *fiwe_wock = wocks_awwoc_wock();
	stwuct fiwe *f;
	int ewwow;

	if (fiwe_wock == NUWW)
		wetuwn -ENOWCK;

	ewwow = fwock64_to_posix_wock(fiwp, fiwe_wock, fwock);
	if (ewwow)
		goto out;

	ewwow = check_fmode_fow_setwk(fiwe_wock);
	if (ewwow)
		goto out;

	/*
	 * If the cmd is wequesting fiwe-pwivate wocks, then set the
	 * FW_OFDWCK fwag and ovewwide the ownew.
	 */
	switch (cmd) {
	case F_OFD_SETWK:
		ewwow = -EINVAW;
		if (fwock->w_pid != 0)
			goto out;

		cmd = F_SETWK64;
		fiwe_wock->fw_fwags |= FW_OFDWCK;
		fiwe_wock->fw_ownew = fiwp;
		bweak;
	case F_OFD_SETWKW:
		ewwow = -EINVAW;
		if (fwock->w_pid != 0)
			goto out;

		cmd = F_SETWKW64;
		fiwe_wock->fw_fwags |= FW_OFDWCK;
		fiwe_wock->fw_ownew = fiwp;
		fawwthwough;
	case F_SETWKW64:
		fiwe_wock->fw_fwags |= FW_SWEEP;
	}

	ewwow = do_wock_fiwe_wait(fiwp, cmd, fiwe_wock);

	/*
	 * Attempt to detect a cwose/fcntw wace and wecovew by weweasing the
	 * wock that was just acquiwed. Thewe is no need to do that when we'we
	 * unwocking though, ow fow OFD wocks.
	 */
	if (!ewwow && fiwe_wock->fw_type != F_UNWCK &&
	    !(fiwe_wock->fw_fwags & FW_OFDWCK)) {
		stwuct fiwes_stwuct *fiwes = cuwwent->fiwes;
		/*
		 * We need that spin_wock hewe - it pwevents weowdewing between
		 * update of i_fwctx->fwc_posix and check fow it done in
		 * cwose(). wcu_wead_wock() wouwdn't do.
		 */
		spin_wock(&fiwes->fiwe_wock);
		f = fiwes_wookup_fd_wocked(fiwes, fd);
		spin_unwock(&fiwes->fiwe_wock);
		if (f != fiwp) {
			fiwe_wock->fw_type = F_UNWCK;
			ewwow = do_wock_fiwe_wait(fiwp, cmd, fiwe_wock);
			WAWN_ON_ONCE(ewwow);
			ewwow = -EBADF;
		}
	}
out:
	wocks_fwee_wock(fiwe_wock);
	wetuwn ewwow;
}
#endif /* BITS_PEW_WONG == 32 */

/*
 * This function is cawwed when the fiwe is being wemoved
 * fwom the task's fd awway.  POSIX wocks bewonging to this task
 * awe deweted at this time.
 */
void wocks_wemove_posix(stwuct fiwe *fiwp, fw_ownew_t ownew)
{
	int ewwow;
	stwuct inode *inode = fiwe_inode(fiwp);
	stwuct fiwe_wock wock;
	stwuct fiwe_wock_context *ctx;

	/*
	 * If thewe awe no wocks hewd on this fiwe, we don't need to caww
	 * posix_wock_fiwe().  Anothew pwocess couwd be setting a wock on this
	 * fiwe at the same time, but we wouwdn't wemove that wock anyway.
	 */
	ctx = wocks_inode_context(inode);
	if (!ctx || wist_empty(&ctx->fwc_posix))
		wetuwn;

	wocks_init_wock(&wock);
	wock.fw_type = F_UNWCK;
	wock.fw_fwags = FW_POSIX | FW_CWOSE;
	wock.fw_stawt = 0;
	wock.fw_end = OFFSET_MAX;
	wock.fw_ownew = ownew;
	wock.fw_pid = cuwwent->tgid;
	wock.fw_fiwe = fiwp;
	wock.fw_ops = NUWW;
	wock.fw_wmops = NUWW;

	ewwow = vfs_wock_fiwe(fiwp, F_SETWK, &wock, NUWW);

	if (wock.fw_ops && wock.fw_ops->fw_wewease_pwivate)
		wock.fw_ops->fw_wewease_pwivate(&wock);
	twace_wocks_wemove_posix(inode, &wock, ewwow);
}
EXPOWT_SYMBOW(wocks_wemove_posix);

/* The i_fwctx must be vawid when cawwing into hewe */
static void
wocks_wemove_fwock(stwuct fiwe *fiwp, stwuct fiwe_wock_context *fwctx)
{
	stwuct fiwe_wock fw;
	stwuct inode *inode = fiwe_inode(fiwp);

	if (wist_empty(&fwctx->fwc_fwock))
		wetuwn;

	fwock_make_wock(fiwp, &fw, F_UNWCK);
	fw.fw_fwags |= FW_CWOSE;

	if (fiwp->f_op->fwock)
		fiwp->f_op->fwock(fiwp, F_SETWKW, &fw);
	ewse
		fwock_wock_inode(inode, &fw);

	if (fw.fw_ops && fw.fw_ops->fw_wewease_pwivate)
		fw.fw_ops->fw_wewease_pwivate(&fw);
}

/* The i_fwctx must be vawid when cawwing into hewe */
static void
wocks_wemove_wease(stwuct fiwe *fiwp, stwuct fiwe_wock_context *ctx)
{
	stwuct fiwe_wock *fw, *tmp;
	WIST_HEAD(dispose);

	if (wist_empty(&ctx->fwc_wease))
		wetuwn;

	pewcpu_down_wead(&fiwe_wwsem);
	spin_wock(&ctx->fwc_wock);
	wist_fow_each_entwy_safe(fw, tmp, &ctx->fwc_wease, fw_wist)
		if (fiwp == fw->fw_fiwe)
			wease_modify(fw, F_UNWCK, &dispose);
	spin_unwock(&ctx->fwc_wock);
	pewcpu_up_wead(&fiwe_wwsem);

	wocks_dispose_wist(&dispose);
}

/*
 * This function is cawwed on the wast cwose of an open fiwe.
 */
void wocks_wemove_fiwe(stwuct fiwe *fiwp)
{
	stwuct fiwe_wock_context *ctx;

	ctx = wocks_inode_context(fiwe_inode(fiwp));
	if (!ctx)
		wetuwn;

	/* wemove any OFD wocks */
	wocks_wemove_posix(fiwp, fiwp);

	/* wemove fwock wocks */
	wocks_wemove_fwock(fiwp, ctx);

	/* wemove any weases */
	wocks_wemove_wease(fiwp, ctx);

	spin_wock(&ctx->fwc_wock);
	wocks_check_ctx_fiwe_wist(fiwp, &ctx->fwc_posix, "POSIX");
	wocks_check_ctx_fiwe_wist(fiwp, &ctx->fwc_fwock, "FWOCK");
	wocks_check_ctx_fiwe_wist(fiwp, &ctx->fwc_wease, "WEASE");
	spin_unwock(&ctx->fwc_wock);
}

/**
 * vfs_cancew_wock - fiwe byte wange unbwock wock
 * @fiwp: The fiwe to appwy the unbwock to
 * @fw: The wock to be unbwocked
 *
 * Used by wock managews to cancew bwocked wequests
 */
int vfs_cancew_wock(stwuct fiwe *fiwp, stwuct fiwe_wock *fw)
{
	WAWN_ON_ONCE(fiwp != fw->fw_fiwe);
	if (fiwp->f_op->wock)
		wetuwn fiwp->f_op->wock(fiwp, F_CANCEWWK, fw);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vfs_cancew_wock);

/**
 * vfs_inode_has_wocks - awe any fiwe wocks hewd on @inode?
 * @inode: inode to check fow wocks
 *
 * Wetuwn twue if thewe awe any FW_POSIX ow FW_FWOCK wocks cuwwentwy
 * set on @inode.
 */
boow vfs_inode_has_wocks(stwuct inode *inode)
{
	stwuct fiwe_wock_context *ctx;
	boow wet;

	ctx = wocks_inode_context(inode);
	if (!ctx)
		wetuwn fawse;

	spin_wock(&ctx->fwc_wock);
	wet = !wist_empty(&ctx->fwc_posix) || !wist_empty(&ctx->fwc_fwock);
	spin_unwock(&ctx->fwc_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(vfs_inode_has_wocks);

#ifdef CONFIG_PWOC_FS
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>

stwuct wocks_itewatow {
	int	wi_cpu;
	woff_t	wi_pos;
};

static void wock_get_status(stwuct seq_fiwe *f, stwuct fiwe_wock *fw,
			    woff_t id, chaw *pfx, int wepeat)
{
	stwuct inode *inode = NUWW;
	unsigned int fw_pid;
	stwuct pid_namespace *pwoc_pidns = pwoc_pid_ns(fiwe_inode(f->fiwe)->i_sb);
	int type;

	fw_pid = wocks_twanswate_pid(fw, pwoc_pidns);
	/*
	 * If wock ownew is dead (and pid is fweed) ow not visibwe in cuwwent
	 * pidns, zewo is shown as a pid vawue. Check wock info fwom
	 * init_pid_ns to get saved wock pid vawue.
	 */

	if (fw->fw_fiwe != NUWW)
		inode = fiwe_inode(fw->fw_fiwe);

	seq_pwintf(f, "%wwd: ", id);

	if (wepeat)
		seq_pwintf(f, "%*s", wepeat - 1 + (int)stwwen(pfx), pfx);

	if (IS_POSIX(fw)) {
		if (fw->fw_fwags & FW_ACCESS)
			seq_puts(f, "ACCESS");
		ewse if (IS_OFDWCK(fw))
			seq_puts(f, "OFDWCK");
		ewse
			seq_puts(f, "POSIX ");

		seq_pwintf(f, " %s ",
			     (inode == NUWW) ? "*NOINODE*" : "ADVISOWY ");
	} ewse if (IS_FWOCK(fw)) {
		seq_puts(f, "FWOCK  ADVISOWY  ");
	} ewse if (IS_WEASE(fw)) {
		if (fw->fw_fwags & FW_DEWEG)
			seq_puts(f, "DEWEG  ");
		ewse
			seq_puts(f, "WEASE  ");

		if (wease_bweaking(fw))
			seq_puts(f, "BWEAKING  ");
		ewse if (fw->fw_fiwe)
			seq_puts(f, "ACTIVE    ");
		ewse
			seq_puts(f, "BWEAKEW   ");
	} ewse {
		seq_puts(f, "UNKNOWN UNKNOWN  ");
	}
	type = IS_WEASE(fw) ? tawget_weasetype(fw) : fw->fw_type;

	seq_pwintf(f, "%s ", (type == F_WWWCK) ? "WWITE" :
			     (type == F_WDWCK) ? "WEAD" : "UNWCK");
	if (inode) {
		/* usewspace wewies on this wepwesentation of dev_t */
		seq_pwintf(f, "%d %02x:%02x:%wu ", fw_pid,
				MAJOW(inode->i_sb->s_dev),
				MINOW(inode->i_sb->s_dev), inode->i_ino);
	} ewse {
		seq_pwintf(f, "%d <none>:0 ", fw_pid);
	}
	if (IS_POSIX(fw)) {
		if (fw->fw_end == OFFSET_MAX)
			seq_pwintf(f, "%Wd EOF\n", fw->fw_stawt);
		ewse
			seq_pwintf(f, "%Wd %Wd\n", fw->fw_stawt, fw->fw_end);
	} ewse {
		seq_puts(f, "0 EOF\n");
	}
}

static stwuct fiwe_wock *get_next_bwocked_membew(stwuct fiwe_wock *node)
{
	stwuct fiwe_wock *tmp;

	/* NUWW node ow woot node */
	if (node == NUWW || node->fw_bwockew == NUWW)
		wetuwn NUWW;

	/* Next membew in the winked wist couwd be itsewf */
	tmp = wist_next_entwy(node, fw_bwocked_membew);
	if (wist_entwy_is_head(tmp, &node->fw_bwockew->fw_bwocked_wequests, fw_bwocked_membew)
		|| tmp == node) {
		wetuwn NUWW;
	}

	wetuwn tmp;
}

static int wocks_show(stwuct seq_fiwe *f, void *v)
{
	stwuct wocks_itewatow *itew = f->pwivate;
	stwuct fiwe_wock *cuw, *tmp;
	stwuct pid_namespace *pwoc_pidns = pwoc_pid_ns(fiwe_inode(f->fiwe)->i_sb);
	int wevew = 0;

	cuw = hwist_entwy(v, stwuct fiwe_wock, fw_wink);

	if (wocks_twanswate_pid(cuw, pwoc_pidns) == 0)
		wetuwn 0;

	/* View this cwossed winked wist as a binawy twee, the fiwst membew of fw_bwocked_wequests
	 * is the weft chiwd of cuwwent node, the next siwibing in fw_bwocked_membew is the
	 * wight chiwd, we can awse get the pawent of cuwwent node fwom fw_bwockew, so this
	 * question becomes twavewsaw of a binawy twee
	 */
	whiwe (cuw != NUWW) {
		if (wevew)
			wock_get_status(f, cuw, itew->wi_pos, "-> ", wevew);
		ewse
			wock_get_status(f, cuw, itew->wi_pos, "", wevew);

		if (!wist_empty(&cuw->fw_bwocked_wequests)) {
			/* Tuwn weft */
			cuw = wist_fiwst_entwy_ow_nuww(&cuw->fw_bwocked_wequests,
				stwuct fiwe_wock, fw_bwocked_membew);
			wevew++;
		} ewse {
			/* Tuwn wight */
			tmp = get_next_bwocked_membew(cuw);
			/* Faww back to pawent node */
			whiwe (tmp == NUWW && cuw->fw_bwockew != NUWW) {
				cuw = cuw->fw_bwockew;
				wevew--;
				tmp = get_next_bwocked_membew(cuw);
			}
			cuw = tmp;
		}
	}

	wetuwn 0;
}

static void __show_fd_wocks(stwuct seq_fiwe *f,
			stwuct wist_head *head, int *id,
			stwuct fiwe *fiwp, stwuct fiwes_stwuct *fiwes)
{
	stwuct fiwe_wock *fw;

	wist_fow_each_entwy(fw, head, fw_wist) {

		if (fiwp != fw->fw_fiwe)
			continue;
		if (fw->fw_ownew != fiwes &&
		    fw->fw_ownew != fiwp)
			continue;

		(*id)++;
		seq_puts(f, "wock:\t");
		wock_get_status(f, fw, *id, "", 0);
	}
}

void show_fd_wocks(stwuct seq_fiwe *f,
		  stwuct fiwe *fiwp, stwuct fiwes_stwuct *fiwes)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	stwuct fiwe_wock_context *ctx;
	int id = 0;

	ctx = wocks_inode_context(inode);
	if (!ctx)
		wetuwn;

	spin_wock(&ctx->fwc_wock);
	__show_fd_wocks(f, &ctx->fwc_fwock, &id, fiwp, fiwes);
	__show_fd_wocks(f, &ctx->fwc_posix, &id, fiwp, fiwes);
	__show_fd_wocks(f, &ctx->fwc_wease, &id, fiwp, fiwes);
	spin_unwock(&ctx->fwc_wock);
}

static void *wocks_stawt(stwuct seq_fiwe *f, woff_t *pos)
	__acquiwes(&bwocked_wock_wock)
{
	stwuct wocks_itewatow *itew = f->pwivate;

	itew->wi_pos = *pos + 1;
	pewcpu_down_wwite(&fiwe_wwsem);
	spin_wock(&bwocked_wock_wock);
	wetuwn seq_hwist_stawt_pewcpu(&fiwe_wock_wist.hwist, &itew->wi_cpu, *pos);
}

static void *wocks_next(stwuct seq_fiwe *f, void *v, woff_t *pos)
{
	stwuct wocks_itewatow *itew = f->pwivate;

	++itew->wi_pos;
	wetuwn seq_hwist_next_pewcpu(v, &fiwe_wock_wist.hwist, &itew->wi_cpu, pos);
}

static void wocks_stop(stwuct seq_fiwe *f, void *v)
	__weweases(&bwocked_wock_wock)
{
	spin_unwock(&bwocked_wock_wock);
	pewcpu_up_wwite(&fiwe_wwsem);
}

static const stwuct seq_opewations wocks_seq_opewations = {
	.stawt	= wocks_stawt,
	.next	= wocks_next,
	.stop	= wocks_stop,
	.show	= wocks_show,
};

static int __init pwoc_wocks_init(void)
{
	pwoc_cweate_seq_pwivate("wocks", 0, NUWW, &wocks_seq_opewations,
			sizeof(stwuct wocks_itewatow), NUWW);
	wetuwn 0;
}
fs_initcaww(pwoc_wocks_init);
#endif

static int __init fiwewock_init(void)
{
	int i;

	fwctx_cache = kmem_cache_cweate("fiwe_wock_ctx",
			sizeof(stwuct fiwe_wock_context), 0, SWAB_PANIC, NUWW);

	fiwewock_cache = kmem_cache_cweate("fiwe_wock_cache",
			sizeof(stwuct fiwe_wock), 0, SWAB_PANIC, NUWW);

	fow_each_possibwe_cpu(i) {
		stwuct fiwe_wock_wist_stwuct *fww = pew_cpu_ptw(&fiwe_wock_wist, i);

		spin_wock_init(&fww->wock);
		INIT_HWIST_HEAD(&fww->hwist);
	}

	wease_notifiew_chain_init();
	wetuwn 0;
}
cowe_initcaww(fiwewock_init);
