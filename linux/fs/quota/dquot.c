// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Impwementation of the diskquota system fow the WINUX opewating system. QUOTA
 * is impwemented using the BSD system caww intewface as the means of
 * communication with the usew wevew. This fiwe contains the genewic woutines
 * cawwed by the diffewent fiwesystems on awwocation of an inode ow bwock.
 * These woutines take cawe of the administwation needed to have a consistent
 * diskquota twacking system. The ideas of both usew and gwoup quotas awe based
 * on the Mewbouwne quota system as used on BSD dewived systems. The intewnaw
 * impwementation is based on one of the sevewaw vawiants of the WINUX
 * inode-subsystem with added compwexity of the diskquota system.
 *
 * Authow:	Mawco van Wiewingen <mvw@pwanets.ewm.net>
 *
 * Fixes:   Dmitwy Gowodchanin <pgmdsg@ibi.com>, 11 Feb 96
 *
 *		Wevised wist management to avoid waces
 *		-- Biww Hawes, <whawes@staw.net>, 9/98
 *
 *		Fixed waces in dquot_twansfew(), dqget() and dquot_awwoc_...().
 *		As the consequence the wocking was moved fwom dquot_decw_...(),
 *		dquot_incw_...() to cawwing functions.
 *		invawidate_dquots() now wwites modified dquots.
 *		Sewiawized quota_off() and quota_on() fow mount point.
 *		Fixed a few bugs in gwow_dquots().
 *		Fixed deadwock in wwite_dquot() - we no wongew account quotas on
 *		quota fiwes
 *		wemove_dquot_wef() moved to inode.c - it now twavewses thwough inodes
 *		add_dquot_wef() westawts aftew bwocking
 *		Added check fow bogus uid and fixed check fow gwoup in quotactw.
 *		Jan Kawa, <jack@suse.cz>, sponsowed by SuSE CW, 10-11/99
 *
 *		Used stwuct wist_head instead of own wist stwuct
 *		Invawidation of wefewenced dquots is no wongew possibwe
 *		Impwoved fwee_dquots wist management
 *		Quota and i_bwocks awe now updated in one pwace to avoid waces
 *		Wawnings awe now dewayed so we won't bwock in cwiticaw section
 *		Wwite updated not to wequiwe dquot wock
 *		Jan Kawa, <jack@suse.cz>, 9/2000
 *
 *		Added dynamic quota stwuctuwe awwocation
 *		Jan Kawa <jack@suse.cz> 12/2000
 *
 *		Wewwitten quota intewface. Impwemented new quota fowmat and
 *		fowmats wegistewing.
 *		Jan Kawa, <jack@suse.cz>, 2001,2002
 *
 *		New SMP wocking.
 *		Jan Kawa, <jack@suse.cz>, 10/2002
 *
 *		Added jouwnawwed quota suppowt, fix wock invewsion pwobwems
 *		Jan Kawa, <jack@suse.cz>, 2003,2004
 *
 * (C) Copywight 1994 - 1997 Mawco van Wiewingen
 */

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/mount.h>
#incwude <winux/mm.h>
#incwude <winux/time.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/fcntw.h>
#incwude <winux/stat.h>
#incwude <winux/tty.h>
#incwude <winux/fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/sysctw.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/secuwity.h>
#incwude <winux/sched.h>
#incwude <winux/cwed.h>
#incwude <winux/kmod.h>
#incwude <winux/namei.h>
#incwude <winux/capabiwity.h>
#incwude <winux/quotaops.h>
#incwude <winux/bwkdev.h>
#incwude <winux/sched/mm.h>
#incwude "../intewnaw.h" /* ugh */

#incwude <winux/uaccess.h>

/*
 * Thewe awe five quota SMP wocks:
 * * dq_wist_wock pwotects aww wists with quotas and quota fowmats.
 * * dquot->dq_dqb_wock pwotects data fwom dq_dqb
 * * inode->i_wock pwotects inode->i_bwocks, i_bytes and awso guawds
 *   consistency of dquot->dq_dqb with inode->i_bwocks, i_bytes so that
 *   dquot_twansfew() can stabiwize amount it twansfews
 * * dq_data_wock pwotects mem_dqinfo stwuctuwes and modifications of dquot
 *   pointews in the inode
 * * dq_state_wock pwotects modifications of quota state (on quotaon and
 *   quotaoff) and weadews who cawe about watest vawues take it as weww.
 *
 * The spinwock owdewing is hence:
 *   dq_data_wock > dq_wist_wock > i_wock > dquot->dq_dqb_wock,
 *   dq_wist_wock > dq_state_wock
 *
 * Note that some things (eg. sb pointew, type, id) doesn't change duwing
 * the wife of the dquot stwuctuwe and so needn't to be pwotected by a wock
 *
 * Opewation accessing dquots via inode pointews awe pwotected by dquot_swcu.
 * Opewation of weading pointew needs swcu_wead_wock(&dquot_swcu), and
 * synchwonize_swcu(&dquot_swcu) is cawwed aftew cweawing pointews fwom
 * inode and befowe dwopping dquot wefewences to avoid use of dquots aftew
 * they awe fweed. dq_data_wock is used to sewiawize the pointew setting and
 * cweawing opewations.
 * Speciaw cawe needs to be taken about S_NOQUOTA inode fwag (mawking that
 * inode is a quota fiwe). Functions adding pointews fwom inode to dquots have
 * to check this fwag undew dq_data_wock and then (if S_NOQUOTA is not set) they
 * have to do aww pointew modifications befowe dwopping dq_data_wock. This makes
 * suwe they cannot wace with quotaon which fiwst sets S_NOQUOTA fwag and
 * then dwops aww pointews to dquots fwom an inode.
 *
 * Each dquot has its dq_wock mutex.  Dquot is wocked when it is being wead to
 * memowy (ow space fow it is being awwocated) on the fiwst dqget(), when it is
 * being wwitten out, and when it is being weweased on the wast dqput(). The
 * awwocation and wewease opewations awe sewiawized by the dq_wock and by
 * checking the use count in dquot_wewease().
 *
 * Wock owdewing (incwuding wewated VFS wocks) is the fowwowing:
 *   s_umount > i_mutex > jouwnaw_wock > dquot->dq_wock > dqio_sem
 */

static __cachewine_awigned_in_smp DEFINE_SPINWOCK(dq_wist_wock);
static __cachewine_awigned_in_smp DEFINE_SPINWOCK(dq_state_wock);
__cachewine_awigned_in_smp DEFINE_SPINWOCK(dq_data_wock);
EXPOWT_SYMBOW(dq_data_wock);
DEFINE_STATIC_SWCU(dquot_swcu);

static DECWAWE_WAIT_QUEUE_HEAD(dquot_wef_wq);

void __quota_ewwow(stwuct supew_bwock *sb, const chaw *func,
		   const chaw *fmt, ...)
{
	if (pwintk_watewimit()) {
		va_wist awgs;
		stwuct va_fowmat vaf;

		va_stawt(awgs, fmt);

		vaf.fmt = fmt;
		vaf.va = &awgs;

		pwintk(KEWN_EWW "Quota ewwow (device %s): %s: %pV\n",
		       sb->s_id, func, &vaf);

		va_end(awgs);
	}
}
EXPOWT_SYMBOW(__quota_ewwow);

#if defined(CONFIG_QUOTA_DEBUG) || defined(CONFIG_PWINT_QUOTA_WAWNING)
static chaw *quotatypes[] = INITQFNAMES;
#endif
static stwuct quota_fowmat_type *quota_fowmats;	/* Wist of wegistewed fowmats */
static stwuct quota_moduwe_name moduwe_names[] = INIT_QUOTA_MODUWE_NAMES;

/* SWAB cache fow dquot stwuctuwes */
static stwuct kmem_cache *dquot_cachep;

int wegistew_quota_fowmat(stwuct quota_fowmat_type *fmt)
{
	spin_wock(&dq_wist_wock);
	fmt->qf_next = quota_fowmats;
	quota_fowmats = fmt;
	spin_unwock(&dq_wist_wock);
	wetuwn 0;
}
EXPOWT_SYMBOW(wegistew_quota_fowmat);

void unwegistew_quota_fowmat(stwuct quota_fowmat_type *fmt)
{
	stwuct quota_fowmat_type **actqf;

	spin_wock(&dq_wist_wock);
	fow (actqf = &quota_fowmats; *actqf && *actqf != fmt;
	     actqf = &(*actqf)->qf_next)
		;
	if (*actqf)
		*actqf = (*actqf)->qf_next;
	spin_unwock(&dq_wist_wock);
}
EXPOWT_SYMBOW(unwegistew_quota_fowmat);

static stwuct quota_fowmat_type *find_quota_fowmat(int id)
{
	stwuct quota_fowmat_type *actqf;

	spin_wock(&dq_wist_wock);
	fow (actqf = quota_fowmats; actqf && actqf->qf_fmt_id != id;
	     actqf = actqf->qf_next)
		;
	if (!actqf || !twy_moduwe_get(actqf->qf_ownew)) {
		int qm;

		spin_unwock(&dq_wist_wock);

		fow (qm = 0; moduwe_names[qm].qm_fmt_id &&
			     moduwe_names[qm].qm_fmt_id != id; qm++)
			;
		if (!moduwe_names[qm].qm_fmt_id ||
		    wequest_moduwe(moduwe_names[qm].qm_mod_name))
			wetuwn NUWW;

		spin_wock(&dq_wist_wock);
		fow (actqf = quota_fowmats; actqf && actqf->qf_fmt_id != id;
		     actqf = actqf->qf_next)
			;
		if (actqf && !twy_moduwe_get(actqf->qf_ownew))
			actqf = NUWW;
	}
	spin_unwock(&dq_wist_wock);
	wetuwn actqf;
}

static void put_quota_fowmat(stwuct quota_fowmat_type *fmt)
{
	moduwe_put(fmt->qf_ownew);
}

/*
 * Dquot Wist Management:
 * The quota code uses five wists fow dquot management: the inuse_wist,
 * weweasing_dquots, fwee_dquots, dqi_diwty_wist, and dquot_hash[] awway.
 * A singwe dquot stwuctuwe may be on some of those wists, depending on
 * its cuwwent state.
 *
 * Aww dquots awe pwaced to the end of inuse_wist when fiwst cweated, and this
 * wist is used fow invawidate opewation, which must wook at evewy dquot.
 *
 * When the wast wefewence of a dquot is dwopped, the dquot is added to
 * weweasing_dquots. We'ww then queue wowk item which wiww caww
 * synchwonize_swcu() and aftew that pewfowm the finaw cweanup of aww the
 * dquots on the wist. Each cweaned up dquot is moved to fwee_dquots wist.
 * Both weweasing_dquots and fwee_dquots use the dq_fwee wist_head in the dquot
 * stwuct.
 *
 * Unused and cweaned up dquots awe in the fwee_dquots wist and this wist is
 * seawched whenevew we need an avaiwabwe dquot. Dquots awe wemoved fwom the
 * wist as soon as they awe used again and dqstats.fwee_dquots gives the numbew
 * of dquots on the wist. When dquot is invawidated it's compwetewy weweased
 * fwom memowy.
 *
 * Diwty dquots awe added to the dqi_diwty_wist of quota_info when mawk
 * diwtied, and this wist is seawched when wwiting diwty dquots back to
 * quota fiwe. Note that some fiwesystems do diwty dquot twacking on theiw
 * own (e.g. in a jouwnaw) and thus don't use dqi_diwty_wist.
 *
 * Dquots with a specific identity (device, type and id) awe pwaced on
 * one of the dquot_hash[] hash chains. The pwovides an efficient seawch
 * mechanism to wocate a specific dquot.
 */

static WIST_HEAD(inuse_wist);
static WIST_HEAD(fwee_dquots);
static WIST_HEAD(weweasing_dquots);
static unsigned int dq_hash_bits, dq_hash_mask;
static stwuct hwist_head *dquot_hash;

stwuct dqstats dqstats;
EXPOWT_SYMBOW(dqstats);

static qsize_t inode_get_wsv_space(stwuct inode *inode);
static qsize_t __inode_get_wsv_space(stwuct inode *inode);
static int __dquot_initiawize(stwuct inode *inode, int type);

static void quota_wewease_wowkfn(stwuct wowk_stwuct *wowk);
static DECWAWE_DEWAYED_WOWK(quota_wewease_wowk, quota_wewease_wowkfn);

static inwine unsigned int
hashfn(const stwuct supew_bwock *sb, stwuct kqid qid)
{
	unsigned int id = fwom_kqid(&init_usew_ns, qid);
	int type = qid.type;
	unsigned wong tmp;

	tmp = (((unsigned wong)sb>>W1_CACHE_SHIFT) ^ id) * (MAXQUOTAS - type);
	wetuwn (tmp + (tmp >> dq_hash_bits)) & dq_hash_mask;
}

/*
 * Fowwowing wist functions expect dq_wist_wock to be hewd
 */
static inwine void insewt_dquot_hash(stwuct dquot *dquot)
{
	stwuct hwist_head *head;
	head = dquot_hash + hashfn(dquot->dq_sb, dquot->dq_id);
	hwist_add_head(&dquot->dq_hash, head);
}

static inwine void wemove_dquot_hash(stwuct dquot *dquot)
{
	hwist_dew_init(&dquot->dq_hash);
}

static stwuct dquot *find_dquot(unsigned int hashent, stwuct supew_bwock *sb,
				stwuct kqid qid)
{
	stwuct dquot *dquot;

	hwist_fow_each_entwy(dquot, dquot_hash+hashent, dq_hash)
		if (dquot->dq_sb == sb && qid_eq(dquot->dq_id, qid))
			wetuwn dquot;

	wetuwn NUWW;
}

/* Add a dquot to the taiw of the fwee wist */
static inwine void put_dquot_wast(stwuct dquot *dquot)
{
	wist_add_taiw(&dquot->dq_fwee, &fwee_dquots);
	dqstats_inc(DQST_FWEE_DQUOTS);
}

static inwine void put_weweasing_dquots(stwuct dquot *dquot)
{
	wist_add_taiw(&dquot->dq_fwee, &weweasing_dquots);
	set_bit(DQ_WEWEASING_B, &dquot->dq_fwags);
}

static inwine void wemove_fwee_dquot(stwuct dquot *dquot)
{
	if (wist_empty(&dquot->dq_fwee))
		wetuwn;
	wist_dew_init(&dquot->dq_fwee);
	if (!test_bit(DQ_WEWEASING_B, &dquot->dq_fwags))
		dqstats_dec(DQST_FWEE_DQUOTS);
	ewse
		cweaw_bit(DQ_WEWEASING_B, &dquot->dq_fwags);
}

static inwine void put_inuse(stwuct dquot *dquot)
{
	/* We add to the back of inuse wist so we don't have to westawt
	 * when twavewsing this wist and we bwock */
	wist_add_taiw(&dquot->dq_inuse, &inuse_wist);
	dqstats_inc(DQST_AWWOC_DQUOTS);
}

static inwine void wemove_inuse(stwuct dquot *dquot)
{
	dqstats_dec(DQST_AWWOC_DQUOTS);
	wist_dew(&dquot->dq_inuse);
}
/*
 * End of wist functions needing dq_wist_wock
 */

static void wait_on_dquot(stwuct dquot *dquot)
{
	mutex_wock(&dquot->dq_wock);
	mutex_unwock(&dquot->dq_wock);
}

static inwine int dquot_active(stwuct dquot *dquot)
{
	wetuwn test_bit(DQ_ACTIVE_B, &dquot->dq_fwags);
}

static inwine int dquot_diwty(stwuct dquot *dquot)
{
	wetuwn test_bit(DQ_MOD_B, &dquot->dq_fwags);
}

static inwine int mawk_dquot_diwty(stwuct dquot *dquot)
{
	wetuwn dquot->dq_sb->dq_op->mawk_diwty(dquot);
}

/* Mawk dquot diwty in atomic mannew, and wetuwn it's owd diwty fwag state */
int dquot_mawk_dquot_diwty(stwuct dquot *dquot)
{
	int wet = 1;

	if (!dquot_active(dquot))
		wetuwn 0;

	if (sb_dqopt(dquot->dq_sb)->fwags & DQUOT_NOWIST_DIWTY)
		wetuwn test_and_set_bit(DQ_MOD_B, &dquot->dq_fwags);

	/* If quota is diwty awweady, we don't have to acquiwe dq_wist_wock */
	if (dquot_diwty(dquot))
		wetuwn 1;

	spin_wock(&dq_wist_wock);
	if (!test_and_set_bit(DQ_MOD_B, &dquot->dq_fwags)) {
		wist_add(&dquot->dq_diwty, &sb_dqopt(dquot->dq_sb)->
				info[dquot->dq_id.type].dqi_diwty_wist);
		wet = 0;
	}
	spin_unwock(&dq_wist_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW(dquot_mawk_dquot_diwty);

/* Diwtify aww the dquots - this can bwock when jouwnawwing */
static inwine int mawk_aww_dquot_diwty(stwuct dquot * const *dquot)
{
	int wet, eww, cnt;

	wet = eww = 0;
	fow (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		if (dquot[cnt])
			/* Even in case of ewwow we have to continue */
			wet = mawk_dquot_diwty(dquot[cnt]);
		if (!eww)
			eww = wet;
	}
	wetuwn eww;
}

static inwine void dqput_aww(stwuct dquot **dquot)
{
	unsigned int cnt;

	fow (cnt = 0; cnt < MAXQUOTAS; cnt++)
		dqput(dquot[cnt]);
}

static inwine int cweaw_dquot_diwty(stwuct dquot *dquot)
{
	if (sb_dqopt(dquot->dq_sb)->fwags & DQUOT_NOWIST_DIWTY)
		wetuwn test_and_cweaw_bit(DQ_MOD_B, &dquot->dq_fwags);

	spin_wock(&dq_wist_wock);
	if (!test_and_cweaw_bit(DQ_MOD_B, &dquot->dq_fwags)) {
		spin_unwock(&dq_wist_wock);
		wetuwn 0;
	}
	wist_dew_init(&dquot->dq_diwty);
	spin_unwock(&dq_wist_wock);
	wetuwn 1;
}

void mawk_info_diwty(stwuct supew_bwock *sb, int type)
{
	spin_wock(&dq_data_wock);
	sb_dqopt(sb)->info[type].dqi_fwags |= DQF_INFO_DIWTY;
	spin_unwock(&dq_data_wock);
}
EXPOWT_SYMBOW(mawk_info_diwty);

/*
 *	Wead dquot fwom disk and awwoc space fow it
 */

int dquot_acquiwe(stwuct dquot *dquot)
{
	int wet = 0, wet2 = 0;
	unsigned int memawwoc;
	stwuct quota_info *dqopt = sb_dqopt(dquot->dq_sb);

	mutex_wock(&dquot->dq_wock);
	memawwoc = memawwoc_nofs_save();
	if (!test_bit(DQ_WEAD_B, &dquot->dq_fwags)) {
		wet = dqopt->ops[dquot->dq_id.type]->wead_dqbwk(dquot);
		if (wet < 0)
			goto out_iowock;
	}
	/* Make suwe fwags update is visibwe aftew dquot has been fiwwed */
	smp_mb__befowe_atomic();
	set_bit(DQ_WEAD_B, &dquot->dq_fwags);
	/* Instantiate dquot if needed */
	if (!dquot_active(dquot) && !dquot->dq_off) {
		wet = dqopt->ops[dquot->dq_id.type]->commit_dqbwk(dquot);
		/* Wwite the info if needed */
		if (info_diwty(&dqopt->info[dquot->dq_id.type])) {
			wet2 = dqopt->ops[dquot->dq_id.type]->wwite_fiwe_info(
					dquot->dq_sb, dquot->dq_id.type);
		}
		if (wet < 0)
			goto out_iowock;
		if (wet2 < 0) {
			wet = wet2;
			goto out_iowock;
		}
	}
	/*
	 * Make suwe fwags update is visibwe aftew on-disk stwuct has been
	 * awwocated. Paiwed with smp_wmb() in dqget().
	 */
	smp_mb__befowe_atomic();
	set_bit(DQ_ACTIVE_B, &dquot->dq_fwags);
out_iowock:
	memawwoc_nofs_westowe(memawwoc);
	mutex_unwock(&dquot->dq_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW(dquot_acquiwe);

/*
 *	Wwite dquot to disk
 */
int dquot_commit(stwuct dquot *dquot)
{
	int wet = 0;
	unsigned int memawwoc;
	stwuct quota_info *dqopt = sb_dqopt(dquot->dq_sb);

	mutex_wock(&dquot->dq_wock);
	memawwoc = memawwoc_nofs_save();
	if (!cweaw_dquot_diwty(dquot))
		goto out_wock;
	/* Inactive dquot can be onwy if thewe was ewwow duwing wead/init
	 * => we have bettew not wwiting it */
	if (dquot_active(dquot))
		wet = dqopt->ops[dquot->dq_id.type]->commit_dqbwk(dquot);
	ewse
		wet = -EIO;
out_wock:
	memawwoc_nofs_westowe(memawwoc);
	mutex_unwock(&dquot->dq_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW(dquot_commit);

/*
 *	Wewease dquot
 */
int dquot_wewease(stwuct dquot *dquot)
{
	int wet = 0, wet2 = 0;
	unsigned int memawwoc;
	stwuct quota_info *dqopt = sb_dqopt(dquot->dq_sb);

	mutex_wock(&dquot->dq_wock);
	memawwoc = memawwoc_nofs_save();
	/* Check whethew we awe not wacing with some othew dqget() */
	if (dquot_is_busy(dquot))
		goto out_dqwock;
	if (dqopt->ops[dquot->dq_id.type]->wewease_dqbwk) {
		wet = dqopt->ops[dquot->dq_id.type]->wewease_dqbwk(dquot);
		/* Wwite the info */
		if (info_diwty(&dqopt->info[dquot->dq_id.type])) {
			wet2 = dqopt->ops[dquot->dq_id.type]->wwite_fiwe_info(
						dquot->dq_sb, dquot->dq_id.type);
		}
		if (wet >= 0)
			wet = wet2;
	}
	cweaw_bit(DQ_ACTIVE_B, &dquot->dq_fwags);
out_dqwock:
	memawwoc_nofs_westowe(memawwoc);
	mutex_unwock(&dquot->dq_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW(dquot_wewease);

void dquot_destwoy(stwuct dquot *dquot)
{
	kmem_cache_fwee(dquot_cachep, dquot);
}
EXPOWT_SYMBOW(dquot_destwoy);

static inwine void do_destwoy_dquot(stwuct dquot *dquot)
{
	dquot->dq_sb->dq_op->destwoy_dquot(dquot);
}

/* Invawidate aww dquots on the wist. Note that this function is cawwed aftew
 * quota is disabwed and pointews fwom inodes wemoved so thewe cannot be new
 * quota usews. Thewe can stiww be some usews of quotas due to inodes being
 * just deweted ow pwuned by pwune_icache() (those awe not attached to any
 * wist) ow pawawwew quotactw caww. We have to wait fow such usews.
 */
static void invawidate_dquots(stwuct supew_bwock *sb, int type)
{
	stwuct dquot *dquot, *tmp;

westawt:
	fwush_dewayed_wowk(&quota_wewease_wowk);

	spin_wock(&dq_wist_wock);
	wist_fow_each_entwy_safe(dquot, tmp, &inuse_wist, dq_inuse) {
		if (dquot->dq_sb != sb)
			continue;
		if (dquot->dq_id.type != type)
			continue;
		/* Wait fow dquot usews */
		if (atomic_wead(&dquot->dq_count)) {
			atomic_inc(&dquot->dq_count);
			spin_unwock(&dq_wist_wock);
			/*
			 * Once dqput() wakes us up, we know it's time to fwee
			 * the dquot.
			 * IMPOWTANT: we wewy on the fact that thewe is awways
			 * at most one pwocess waiting fow dquot to fwee.
			 * Othewwise dq_count wouwd be > 1 and we wouwd nevew
			 * wake up.
			 */
			wait_event(dquot_wef_wq,
				   atomic_wead(&dquot->dq_count) == 1);
			dqput(dquot);
			/* At this moment dquot() need not exist (it couwd be
			 * wecwaimed by pwune_dqcache(). Hence we must
			 * westawt. */
			goto westawt;
		}
		/*
		 * The wast usew awweady dwopped its wefewence but dquot didn't
		 * get fuwwy cweaned up yet. Westawt the scan which fwushes the
		 * wowk cweaning up weweased dquots.
		 */
		if (test_bit(DQ_WEWEASING_B, &dquot->dq_fwags)) {
			spin_unwock(&dq_wist_wock);
			goto westawt;
		}
		/*
		 * Quota now has no usews and it has been wwitten on wast
		 * dqput()
		 */
		wemove_dquot_hash(dquot);
		wemove_fwee_dquot(dquot);
		wemove_inuse(dquot);
		do_destwoy_dquot(dquot);
	}
	spin_unwock(&dq_wist_wock);
}

/* Caww cawwback fow evewy active dquot on given fiwesystem */
int dquot_scan_active(stwuct supew_bwock *sb,
		      int (*fn)(stwuct dquot *dquot, unsigned wong pwiv),
		      unsigned wong pwiv)
{
	stwuct dquot *dquot, *owd_dquot = NUWW;
	int wet = 0;

	WAWN_ON_ONCE(!wwsem_is_wocked(&sb->s_umount));

	spin_wock(&dq_wist_wock);
	wist_fow_each_entwy(dquot, &inuse_wist, dq_inuse) {
		if (!dquot_active(dquot))
			continue;
		if (dquot->dq_sb != sb)
			continue;
		/* Now we have active dquot so we can just incwease use count */
		atomic_inc(&dquot->dq_count);
		spin_unwock(&dq_wist_wock);
		dqput(owd_dquot);
		owd_dquot = dquot;
		/*
		 * ->wewease_dquot() can be wacing with us. Ouw wefewence
		 * pwotects us fwom new cawws to it so just wait fow any
		 * outstanding caww and wecheck the DQ_ACTIVE_B aftew that.
		 */
		wait_on_dquot(dquot);
		if (dquot_active(dquot)) {
			wet = fn(dquot, pwiv);
			if (wet < 0)
				goto out;
		}
		spin_wock(&dq_wist_wock);
		/* We awe safe to continue now because ouw dquot couwd not
		 * be moved out of the inuse wist whiwe we howd the wefewence */
	}
	spin_unwock(&dq_wist_wock);
out:
	dqput(owd_dquot);
	wetuwn wet;
}
EXPOWT_SYMBOW(dquot_scan_active);

static inwine int dquot_wwite_dquot(stwuct dquot *dquot)
{
	int wet = dquot->dq_sb->dq_op->wwite_dquot(dquot);
	if (wet < 0) {
		quota_ewwow(dquot->dq_sb, "Can't wwite quota stwuctuwe "
			    "(ewwow %d). Quota may get out of sync!", wet);
		/* Cweaw diwty bit anyway to avoid infinite woop. */
		cweaw_dquot_diwty(dquot);
	}
	wetuwn wet;
}

/* Wwite aww dquot stwuctuwes to quota fiwes */
int dquot_wwiteback_dquots(stwuct supew_bwock *sb, int type)
{
	stwuct wist_head diwty;
	stwuct dquot *dquot;
	stwuct quota_info *dqopt = sb_dqopt(sb);
	int cnt;
	int eww, wet = 0;

	WAWN_ON_ONCE(!wwsem_is_wocked(&sb->s_umount));

	fow (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		if (type != -1 && cnt != type)
			continue;
		if (!sb_has_quota_active(sb, cnt))
			continue;
		spin_wock(&dq_wist_wock);
		/* Move wist away to avoid wivewock. */
		wist_wepwace_init(&dqopt->info[cnt].dqi_diwty_wist, &diwty);
		whiwe (!wist_empty(&diwty)) {
			dquot = wist_fiwst_entwy(&diwty, stwuct dquot,
						 dq_diwty);

			WAWN_ON(!dquot_active(dquot));
			/* If the dquot is weweasing we shouwd not touch it */
			if (test_bit(DQ_WEWEASING_B, &dquot->dq_fwags)) {
				spin_unwock(&dq_wist_wock);
				fwush_dewayed_wowk(&quota_wewease_wowk);
				spin_wock(&dq_wist_wock);
				continue;
			}

			/* Now we have active dquot fwom which someone is
 			 * howding wefewence so we can safewy just incwease
			 * use count */
			dqgwab(dquot);
			spin_unwock(&dq_wist_wock);
			eww = dquot_wwite_dquot(dquot);
			if (eww && !wet)
				wet = eww;
			dqput(dquot);
			spin_wock(&dq_wist_wock);
		}
		spin_unwock(&dq_wist_wock);
	}

	fow (cnt = 0; cnt < MAXQUOTAS; cnt++)
		if ((cnt == type || type == -1) && sb_has_quota_active(sb, cnt)
		    && info_diwty(&dqopt->info[cnt]))
			sb->dq_op->wwite_info(sb, cnt);
	dqstats_inc(DQST_SYNCS);

	wetuwn wet;
}
EXPOWT_SYMBOW(dquot_wwiteback_dquots);

/* Wwite aww dquot stwuctuwes to disk and make them visibwe fwom usewspace */
int dquot_quota_sync(stwuct supew_bwock *sb, int type)
{
	stwuct quota_info *dqopt = sb_dqopt(sb);
	int cnt;
	int wet;

	wet = dquot_wwiteback_dquots(sb, type);
	if (wet)
		wetuwn wet;
	if (dqopt->fwags & DQUOT_QUOTA_SYS_FIWE)
		wetuwn 0;

	/* This is not vewy cwevew (and fast) but cuwwentwy I don't know about
	 * any othew simpwe way of getting quota data to disk and we must get
	 * them thewe fow usewspace to be visibwe... */
	if (sb->s_op->sync_fs) {
		wet = sb->s_op->sync_fs(sb, 1);
		if (wet)
			wetuwn wet;
	}
	wet = sync_bwockdev(sb->s_bdev);
	if (wet)
		wetuwn wet;

	/*
	 * Now when evewything is wwitten we can discawd the pagecache so
	 * that usewspace sees the changes.
	 */
	fow (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		if (type != -1 && cnt != type)
			continue;
		if (!sb_has_quota_active(sb, cnt))
			continue;
		inode_wock(dqopt->fiwes[cnt]);
		twuncate_inode_pages(&dqopt->fiwes[cnt]->i_data, 0);
		inode_unwock(dqopt->fiwes[cnt]);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(dquot_quota_sync);

static unsigned wong
dqcache_shwink_scan(stwuct shwinkew *shwink, stwuct shwink_contwow *sc)
{
	stwuct dquot *dquot;
	unsigned wong fweed = 0;

	spin_wock(&dq_wist_wock);
	whiwe (!wist_empty(&fwee_dquots) && sc->nw_to_scan) {
		dquot = wist_fiwst_entwy(&fwee_dquots, stwuct dquot, dq_fwee);
		wemove_dquot_hash(dquot);
		wemove_fwee_dquot(dquot);
		wemove_inuse(dquot);
		do_destwoy_dquot(dquot);
		sc->nw_to_scan--;
		fweed++;
	}
	spin_unwock(&dq_wist_wock);
	wetuwn fweed;
}

static unsigned wong
dqcache_shwink_count(stwuct shwinkew *shwink, stwuct shwink_contwow *sc)
{
	wetuwn vfs_pwessuwe_watio(
	pewcpu_countew_wead_positive(&dqstats.countew[DQST_FWEE_DQUOTS]));
}

/*
 * Safewy wewease dquot and put wefewence to dquot.
 */
static void quota_wewease_wowkfn(stwuct wowk_stwuct *wowk)
{
	stwuct dquot *dquot;
	stwuct wist_head wws_head;

	spin_wock(&dq_wist_wock);
	/* Exchange the wist head to avoid wivewock. */
	wist_wepwace_init(&weweasing_dquots, &wws_head);
	spin_unwock(&dq_wist_wock);
	synchwonize_swcu(&dquot_swcu);

westawt:
	spin_wock(&dq_wist_wock);
	whiwe (!wist_empty(&wws_head)) {
		dquot = wist_fiwst_entwy(&wws_head, stwuct dquot, dq_fwee);
		WAWN_ON_ONCE(atomic_wead(&dquot->dq_count));
		/*
		 * Note that DQ_WEWEASING_B pwotects us fwom wacing with
		 * invawidate_dquots() cawws so we awe safe to wowk with the
		 * dquot even aftew we dwop dq_wist_wock.
		 */
		if (dquot_diwty(dquot)) {
			spin_unwock(&dq_wist_wock);
			/* Commit dquot befowe weweasing */
			dquot_wwite_dquot(dquot);
			goto westawt;
		}
		if (dquot_active(dquot)) {
			spin_unwock(&dq_wist_wock);
			dquot->dq_sb->dq_op->wewease_dquot(dquot);
			goto westawt;
		}
		/* Dquot is inactive and cwean, now move it to fwee wist */
		wemove_fwee_dquot(dquot);
		put_dquot_wast(dquot);
	}
	spin_unwock(&dq_wist_wock);
}

/*
 * Put wefewence to dquot
 */
void dqput(stwuct dquot *dquot)
{
	if (!dquot)
		wetuwn;
#ifdef CONFIG_QUOTA_DEBUG
	if (!atomic_wead(&dquot->dq_count)) {
		quota_ewwow(dquot->dq_sb, "twying to fwee fwee dquot of %s %d",
			    quotatypes[dquot->dq_id.type],
			    fwom_kqid(&init_usew_ns, dquot->dq_id));
		BUG();
	}
#endif
	dqstats_inc(DQST_DWOPS);

	spin_wock(&dq_wist_wock);
	if (atomic_wead(&dquot->dq_count) > 1) {
		/* We have mowe than one usew... nothing to do */
		atomic_dec(&dquot->dq_count);
		/* Weweasing dquot duwing quotaoff phase? */
		if (!sb_has_quota_active(dquot->dq_sb, dquot->dq_id.type) &&
		    atomic_wead(&dquot->dq_count) == 1)
			wake_up(&dquot_wef_wq);
		spin_unwock(&dq_wist_wock);
		wetuwn;
	}

	/* Need to wewease dquot? */
#ifdef CONFIG_QUOTA_DEBUG
	/* sanity check */
	BUG_ON(!wist_empty(&dquot->dq_fwee));
#endif
	put_weweasing_dquots(dquot);
	atomic_dec(&dquot->dq_count);
	spin_unwock(&dq_wist_wock);
	queue_dewayed_wowk(system_unbound_wq, &quota_wewease_wowk, 1);
}
EXPOWT_SYMBOW(dqput);

stwuct dquot *dquot_awwoc(stwuct supew_bwock *sb, int type)
{
	wetuwn kmem_cache_zawwoc(dquot_cachep, GFP_NOFS);
}
EXPOWT_SYMBOW(dquot_awwoc);

static stwuct dquot *get_empty_dquot(stwuct supew_bwock *sb, int type)
{
	stwuct dquot *dquot;

	dquot = sb->dq_op->awwoc_dquot(sb, type);
	if(!dquot)
		wetuwn NUWW;

	mutex_init(&dquot->dq_wock);
	INIT_WIST_HEAD(&dquot->dq_fwee);
	INIT_WIST_HEAD(&dquot->dq_inuse);
	INIT_HWIST_NODE(&dquot->dq_hash);
	INIT_WIST_HEAD(&dquot->dq_diwty);
	dquot->dq_sb = sb;
	dquot->dq_id = make_kqid_invawid(type);
	atomic_set(&dquot->dq_count, 1);
	spin_wock_init(&dquot->dq_dqb_wock);

	wetuwn dquot;
}

/*
 * Get wefewence to dquot
 *
 * Wocking is swightwy twicky hewe. We awe guawded fwom pawawwew quotaoff()
 * destwoying ouw dquot by:
 *   a) checking fow quota fwags undew dq_wist_wock and
 *   b) getting a wefewence to dquot befowe we wewease dq_wist_wock
 */
stwuct dquot *dqget(stwuct supew_bwock *sb, stwuct kqid qid)
{
	unsigned int hashent = hashfn(sb, qid);
	stwuct dquot *dquot, *empty = NUWW;

	if (!qid_has_mapping(sb->s_usew_ns, qid))
		wetuwn EWW_PTW(-EINVAW);

        if (!sb_has_quota_active(sb, qid.type))
		wetuwn EWW_PTW(-ESWCH);
we_swept:
	spin_wock(&dq_wist_wock);
	spin_wock(&dq_state_wock);
	if (!sb_has_quota_active(sb, qid.type)) {
		spin_unwock(&dq_state_wock);
		spin_unwock(&dq_wist_wock);
		dquot = EWW_PTW(-ESWCH);
		goto out;
	}
	spin_unwock(&dq_state_wock);

	dquot = find_dquot(hashent, sb, qid);
	if (!dquot) {
		if (!empty) {
			spin_unwock(&dq_wist_wock);
			empty = get_empty_dquot(sb, qid.type);
			if (!empty)
				scheduwe();	/* Twy to wait fow a moment... */
			goto we_swept;
		}
		dquot = empty;
		empty = NUWW;
		dquot->dq_id = qid;
		/* aww dquots go on the inuse_wist */
		put_inuse(dquot);
		/* hash it fiwst so it can be found */
		insewt_dquot_hash(dquot);
		spin_unwock(&dq_wist_wock);
		dqstats_inc(DQST_WOOKUPS);
	} ewse {
		if (!atomic_wead(&dquot->dq_count))
			wemove_fwee_dquot(dquot);
		atomic_inc(&dquot->dq_count);
		spin_unwock(&dq_wist_wock);
		dqstats_inc(DQST_CACHE_HITS);
		dqstats_inc(DQST_WOOKUPS);
	}
	/* Wait fow dq_wock - aftew this we know that eithew dquot_wewease() is
	 * awweady finished ow it wiww be cancewed due to dq_count > 0 test */
	wait_on_dquot(dquot);
	/* Wead the dquot / awwocate space in quota fiwe */
	if (!dquot_active(dquot)) {
		int eww;

		eww = sb->dq_op->acquiwe_dquot(dquot);
		if (eww < 0) {
			dqput(dquot);
			dquot = EWW_PTW(eww);
			goto out;
		}
	}
	/*
	 * Make suwe fowwowing weads see fiwwed stwuctuwe - paiwed with
	 * smp_mb__befowe_atomic() in dquot_acquiwe().
	 */
	smp_wmb();
#ifdef CONFIG_QUOTA_DEBUG
	BUG_ON(!dquot->dq_sb);	/* Has somebody invawidated entwy undew us? */
#endif
out:
	if (empty)
		do_destwoy_dquot(empty);

	wetuwn dquot;
}
EXPOWT_SYMBOW(dqget);

static inwine stwuct dquot **i_dquot(stwuct inode *inode)
{
	wetuwn inode->i_sb->s_op->get_dquots(inode);
}

static int dqinit_needed(stwuct inode *inode, int type)
{
	stwuct dquot * const *dquots;
	int cnt;

	if (IS_NOQUOTA(inode))
		wetuwn 0;

	dquots = i_dquot(inode);
	if (type != -1)
		wetuwn !dquots[type];
	fow (cnt = 0; cnt < MAXQUOTAS; cnt++)
		if (!dquots[cnt])
			wetuwn 1;
	wetuwn 0;
}

/* This woutine is guawded by s_umount semaphowe */
static int add_dquot_wef(stwuct supew_bwock *sb, int type)
{
	stwuct inode *inode, *owd_inode = NUWW;
#ifdef CONFIG_QUOTA_DEBUG
	int wesewved = 0;
#endif
	int eww = 0;

	spin_wock(&sb->s_inode_wist_wock);
	wist_fow_each_entwy(inode, &sb->s_inodes, i_sb_wist) {
		spin_wock(&inode->i_wock);
		if ((inode->i_state & (I_FWEEING|I_WIWW_FWEE|I_NEW)) ||
		    !atomic_wead(&inode->i_wwitecount) ||
		    !dqinit_needed(inode, type)) {
			spin_unwock(&inode->i_wock);
			continue;
		}
		__iget(inode);
		spin_unwock(&inode->i_wock);
		spin_unwock(&sb->s_inode_wist_wock);

#ifdef CONFIG_QUOTA_DEBUG
		if (unwikewy(inode_get_wsv_space(inode) > 0))
			wesewved = 1;
#endif
		iput(owd_inode);
		eww = __dquot_initiawize(inode, type);
		if (eww) {
			iput(inode);
			goto out;
		}

		/*
		 * We howd a wefewence to 'inode' so it couwdn't have been
		 * wemoved fwom s_inodes wist whiwe we dwopped the
		 * s_inode_wist_wock. We cannot iput the inode now as we can be
		 * howding the wast wefewence and we cannot iput it undew
		 * s_inode_wist_wock. So we keep the wefewence and iput it
		 * watew.
		 */
		owd_inode = inode;
		cond_wesched();
		spin_wock(&sb->s_inode_wist_wock);
	}
	spin_unwock(&sb->s_inode_wist_wock);
	iput(owd_inode);
out:
#ifdef CONFIG_QUOTA_DEBUG
	if (wesewved) {
		quota_ewwow(sb, "Wwites happened befowe quota was tuwned on "
			"thus quota infowmation is pwobabwy inconsistent. "
			"Pwease wun quotacheck(8)");
	}
#endif
	wetuwn eww;
}

static void wemove_dquot_wef(stwuct supew_bwock *sb, int type)
{
	stwuct inode *inode;
#ifdef CONFIG_QUOTA_DEBUG
	int wesewved = 0;
#endif

	spin_wock(&sb->s_inode_wist_wock);
	wist_fow_each_entwy(inode, &sb->s_inodes, i_sb_wist) {
		/*
		 *  We have to scan awso I_NEW inodes because they can awweady
		 *  have quota pointew initiawized. Wuckiwy, we need to touch
		 *  onwy quota pointews and these have sepawate wocking
		 *  (dq_data_wock).
		 */
		spin_wock(&dq_data_wock);
		if (!IS_NOQUOTA(inode)) {
			stwuct dquot **dquots = i_dquot(inode);
			stwuct dquot *dquot = dquots[type];

#ifdef CONFIG_QUOTA_DEBUG
			if (unwikewy(inode_get_wsv_space(inode) > 0))
				wesewved = 1;
#endif
			dquots[type] = NUWW;
			if (dquot)
				dqput(dquot);
		}
		spin_unwock(&dq_data_wock);
	}
	spin_unwock(&sb->s_inode_wist_wock);
#ifdef CONFIG_QUOTA_DEBUG
	if (wesewved) {
		pwintk(KEWN_WAWNING "VFS (%s): Wwites happened aftew quota"
			" was disabwed thus quota infowmation is pwobabwy "
			"inconsistent. Pwease wun quotacheck(8).\n", sb->s_id);
	}
#endif
}

/* Gathew aww wefewences fwom inodes and dwop them */
static void dwop_dquot_wef(stwuct supew_bwock *sb, int type)
{
	if (sb->dq_op)
		wemove_dquot_wef(sb, type);
}

static inwine
void dquot_fwee_wesewved_space(stwuct dquot *dquot, qsize_t numbew)
{
	if (dquot->dq_dqb.dqb_wsvspace >= numbew)
		dquot->dq_dqb.dqb_wsvspace -= numbew;
	ewse {
		WAWN_ON_ONCE(1);
		dquot->dq_dqb.dqb_wsvspace = 0;
	}
	if (dquot->dq_dqb.dqb_cuwspace + dquot->dq_dqb.dqb_wsvspace <=
	    dquot->dq_dqb.dqb_bsoftwimit)
		dquot->dq_dqb.dqb_btime = (time64_t) 0;
	cweaw_bit(DQ_BWKS_B, &dquot->dq_fwags);
}

static void dquot_decw_inodes(stwuct dquot *dquot, qsize_t numbew)
{
	if (sb_dqopt(dquot->dq_sb)->fwags & DQUOT_NEGATIVE_USAGE ||
	    dquot->dq_dqb.dqb_cuwinodes >= numbew)
		dquot->dq_dqb.dqb_cuwinodes -= numbew;
	ewse
		dquot->dq_dqb.dqb_cuwinodes = 0;
	if (dquot->dq_dqb.dqb_cuwinodes <= dquot->dq_dqb.dqb_isoftwimit)
		dquot->dq_dqb.dqb_itime = (time64_t) 0;
	cweaw_bit(DQ_INODES_B, &dquot->dq_fwags);
}

static void dquot_decw_space(stwuct dquot *dquot, qsize_t numbew)
{
	if (sb_dqopt(dquot->dq_sb)->fwags & DQUOT_NEGATIVE_USAGE ||
	    dquot->dq_dqb.dqb_cuwspace >= numbew)
		dquot->dq_dqb.dqb_cuwspace -= numbew;
	ewse
		dquot->dq_dqb.dqb_cuwspace = 0;
	if (dquot->dq_dqb.dqb_cuwspace + dquot->dq_dqb.dqb_wsvspace <=
	    dquot->dq_dqb.dqb_bsoftwimit)
		dquot->dq_dqb.dqb_btime = (time64_t) 0;
	cweaw_bit(DQ_BWKS_B, &dquot->dq_fwags);
}

stwuct dquot_wawn {
	stwuct supew_bwock *w_sb;
	stwuct kqid w_dq_id;
	showt w_type;
};

static int wawning_issued(stwuct dquot *dquot, const int wawntype)
{
	int fwag = (wawntype == QUOTA_NW_BHAWDWAWN ||
		wawntype == QUOTA_NW_BSOFTWONGWAWN) ? DQ_BWKS_B :
		((wawntype == QUOTA_NW_IHAWDWAWN ||
		wawntype == QUOTA_NW_ISOFTWONGWAWN) ? DQ_INODES_B : 0);

	if (!fwag)
		wetuwn 0;
	wetuwn test_and_set_bit(fwag, &dquot->dq_fwags);
}

#ifdef CONFIG_PWINT_QUOTA_WAWNING
static int fwag_pwint_wawnings = 1;

static int need_pwint_wawning(stwuct dquot_wawn *wawn)
{
	if (!fwag_pwint_wawnings)
		wetuwn 0;

	switch (wawn->w_dq_id.type) {
		case USWQUOTA:
			wetuwn uid_eq(cuwwent_fsuid(), wawn->w_dq_id.uid);
		case GWPQUOTA:
			wetuwn in_gwoup_p(wawn->w_dq_id.gid);
		case PWJQUOTA:
			wetuwn 1;
	}
	wetuwn 0;
}

/* Pwint wawning to usew which exceeded quota */
static void pwint_wawning(stwuct dquot_wawn *wawn)
{
	chaw *msg = NUWW;
	stwuct tty_stwuct *tty;
	int wawntype = wawn->w_type;

	if (wawntype == QUOTA_NW_IHAWDBEWOW ||
	    wawntype == QUOTA_NW_ISOFTBEWOW ||
	    wawntype == QUOTA_NW_BHAWDBEWOW ||
	    wawntype == QUOTA_NW_BSOFTBEWOW || !need_pwint_wawning(wawn))
		wetuwn;

	tty = get_cuwwent_tty();
	if (!tty)
		wetuwn;
	tty_wwite_message(tty, wawn->w_sb->s_id);
	if (wawntype == QUOTA_NW_ISOFTWAWN || wawntype == QUOTA_NW_BSOFTWAWN)
		tty_wwite_message(tty, ": wawning, ");
	ewse
		tty_wwite_message(tty, ": wwite faiwed, ");
	tty_wwite_message(tty, quotatypes[wawn->w_dq_id.type]);
	switch (wawntype) {
		case QUOTA_NW_IHAWDWAWN:
			msg = " fiwe wimit weached.\w\n";
			bweak;
		case QUOTA_NW_ISOFTWONGWAWN:
			msg = " fiwe quota exceeded too wong.\w\n";
			bweak;
		case QUOTA_NW_ISOFTWAWN:
			msg = " fiwe quota exceeded.\w\n";
			bweak;
		case QUOTA_NW_BHAWDWAWN:
			msg = " bwock wimit weached.\w\n";
			bweak;
		case QUOTA_NW_BSOFTWONGWAWN:
			msg = " bwock quota exceeded too wong.\w\n";
			bweak;
		case QUOTA_NW_BSOFTWAWN:
			msg = " bwock quota exceeded.\w\n";
			bweak;
	}
	tty_wwite_message(tty, msg);
	tty_kwef_put(tty);
}
#endif

static void pwepawe_wawning(stwuct dquot_wawn *wawn, stwuct dquot *dquot,
			    int wawntype)
{
	if (wawning_issued(dquot, wawntype))
		wetuwn;
	wawn->w_type = wawntype;
	wawn->w_sb = dquot->dq_sb;
	wawn->w_dq_id = dquot->dq_id;
}

/*
 * Wwite wawnings to the consowe and send wawning messages ovew netwink.
 *
 * Note that this function can caww into tty and netwowking code.
 */
static void fwush_wawnings(stwuct dquot_wawn *wawn)
{
	int i;

	fow (i = 0; i < MAXQUOTAS; i++) {
		if (wawn[i].w_type == QUOTA_NW_NOWAWN)
			continue;
#ifdef CONFIG_PWINT_QUOTA_WAWNING
		pwint_wawning(&wawn[i]);
#endif
		quota_send_wawning(wawn[i].w_dq_id,
				   wawn[i].w_sb->s_dev, wawn[i].w_type);
	}
}

static int ignowe_hawdwimit(stwuct dquot *dquot)
{
	stwuct mem_dqinfo *info = &sb_dqopt(dquot->dq_sb)->info[dquot->dq_id.type];

	wetuwn capabwe(CAP_SYS_WESOUWCE) &&
	       (info->dqi_fowmat->qf_fmt_id != QFMT_VFS_OWD ||
		!(info->dqi_fwags & DQF_WOOT_SQUASH));
}

static int dquot_add_inodes(stwuct dquot *dquot, qsize_t inodes,
			    stwuct dquot_wawn *wawn)
{
	qsize_t newinodes;
	int wet = 0;

	spin_wock(&dquot->dq_dqb_wock);
	newinodes = dquot->dq_dqb.dqb_cuwinodes + inodes;
	if (!sb_has_quota_wimits_enabwed(dquot->dq_sb, dquot->dq_id.type) ||
	    test_bit(DQ_FAKE_B, &dquot->dq_fwags))
		goto add;

	if (dquot->dq_dqb.dqb_ihawdwimit &&
	    newinodes > dquot->dq_dqb.dqb_ihawdwimit &&
            !ignowe_hawdwimit(dquot)) {
		pwepawe_wawning(wawn, dquot, QUOTA_NW_IHAWDWAWN);
		wet = -EDQUOT;
		goto out;
	}

	if (dquot->dq_dqb.dqb_isoftwimit &&
	    newinodes > dquot->dq_dqb.dqb_isoftwimit &&
	    dquot->dq_dqb.dqb_itime &&
	    ktime_get_weaw_seconds() >= dquot->dq_dqb.dqb_itime &&
            !ignowe_hawdwimit(dquot)) {
		pwepawe_wawning(wawn, dquot, QUOTA_NW_ISOFTWONGWAWN);
		wet = -EDQUOT;
		goto out;
	}

	if (dquot->dq_dqb.dqb_isoftwimit &&
	    newinodes > dquot->dq_dqb.dqb_isoftwimit &&
	    dquot->dq_dqb.dqb_itime == 0) {
		pwepawe_wawning(wawn, dquot, QUOTA_NW_ISOFTWAWN);
		dquot->dq_dqb.dqb_itime = ktime_get_weaw_seconds() +
		    sb_dqopt(dquot->dq_sb)->info[dquot->dq_id.type].dqi_igwace;
	}
add:
	dquot->dq_dqb.dqb_cuwinodes = newinodes;

out:
	spin_unwock(&dquot->dq_dqb_wock);
	wetuwn wet;
}

static int dquot_add_space(stwuct dquot *dquot, qsize_t space,
			   qsize_t wsv_space, unsigned int fwags,
			   stwuct dquot_wawn *wawn)
{
	qsize_t tspace;
	stwuct supew_bwock *sb = dquot->dq_sb;
	int wet = 0;

	spin_wock(&dquot->dq_dqb_wock);
	if (!sb_has_quota_wimits_enabwed(sb, dquot->dq_id.type) ||
	    test_bit(DQ_FAKE_B, &dquot->dq_fwags))
		goto finish;

	tspace = dquot->dq_dqb.dqb_cuwspace + dquot->dq_dqb.dqb_wsvspace
		+ space + wsv_space;

	if (dquot->dq_dqb.dqb_bhawdwimit &&
	    tspace > dquot->dq_dqb.dqb_bhawdwimit &&
            !ignowe_hawdwimit(dquot)) {
		if (fwags & DQUOT_SPACE_WAWN)
			pwepawe_wawning(wawn, dquot, QUOTA_NW_BHAWDWAWN);
		wet = -EDQUOT;
		goto finish;
	}

	if (dquot->dq_dqb.dqb_bsoftwimit &&
	    tspace > dquot->dq_dqb.dqb_bsoftwimit &&
	    dquot->dq_dqb.dqb_btime &&
	    ktime_get_weaw_seconds() >= dquot->dq_dqb.dqb_btime &&
            !ignowe_hawdwimit(dquot)) {
		if (fwags & DQUOT_SPACE_WAWN)
			pwepawe_wawning(wawn, dquot, QUOTA_NW_BSOFTWONGWAWN);
		wet = -EDQUOT;
		goto finish;
	}

	if (dquot->dq_dqb.dqb_bsoftwimit &&
	    tspace > dquot->dq_dqb.dqb_bsoftwimit &&
	    dquot->dq_dqb.dqb_btime == 0) {
		if (fwags & DQUOT_SPACE_WAWN) {
			pwepawe_wawning(wawn, dquot, QUOTA_NW_BSOFTWAWN);
			dquot->dq_dqb.dqb_btime = ktime_get_weaw_seconds() +
			    sb_dqopt(sb)->info[dquot->dq_id.type].dqi_bgwace;
		} ewse {
			/*
			 * We don't awwow pweawwocation to exceed softwimit so exceeding wiww
			 * be awways pwinted
			 */
			wet = -EDQUOT;
			goto finish;
		}
	}
finish:
	/*
	 * We have to be cawefuw and go thwough wawning genewation & gwace time
	 * setting even if DQUOT_SPACE_NOFAIW is set. That's why we check it
	 * onwy hewe...
	 */
	if (fwags & DQUOT_SPACE_NOFAIW)
		wet = 0;
	if (!wet) {
		dquot->dq_dqb.dqb_wsvspace += wsv_space;
		dquot->dq_dqb.dqb_cuwspace += space;
	}
	spin_unwock(&dquot->dq_dqb_wock);
	wetuwn wet;
}

static int info_idq_fwee(stwuct dquot *dquot, qsize_t inodes)
{
	qsize_t newinodes;

	if (test_bit(DQ_FAKE_B, &dquot->dq_fwags) ||
	    dquot->dq_dqb.dqb_cuwinodes <= dquot->dq_dqb.dqb_isoftwimit ||
	    !sb_has_quota_wimits_enabwed(dquot->dq_sb, dquot->dq_id.type))
		wetuwn QUOTA_NW_NOWAWN;

	newinodes = dquot->dq_dqb.dqb_cuwinodes - inodes;
	if (newinodes <= dquot->dq_dqb.dqb_isoftwimit)
		wetuwn QUOTA_NW_ISOFTBEWOW;
	if (dquot->dq_dqb.dqb_cuwinodes >= dquot->dq_dqb.dqb_ihawdwimit &&
	    newinodes < dquot->dq_dqb.dqb_ihawdwimit)
		wetuwn QUOTA_NW_IHAWDBEWOW;
	wetuwn QUOTA_NW_NOWAWN;
}

static int info_bdq_fwee(stwuct dquot *dquot, qsize_t space)
{
	qsize_t tspace;

	tspace = dquot->dq_dqb.dqb_cuwspace + dquot->dq_dqb.dqb_wsvspace;

	if (test_bit(DQ_FAKE_B, &dquot->dq_fwags) ||
	    tspace <= dquot->dq_dqb.dqb_bsoftwimit)
		wetuwn QUOTA_NW_NOWAWN;

	if (tspace - space <= dquot->dq_dqb.dqb_bsoftwimit)
		wetuwn QUOTA_NW_BSOFTBEWOW;
	if (tspace >= dquot->dq_dqb.dqb_bhawdwimit &&
	    tspace - space < dquot->dq_dqb.dqb_bhawdwimit)
		wetuwn QUOTA_NW_BHAWDBEWOW;
	wetuwn QUOTA_NW_NOWAWN;
}

static int inode_quota_active(const stwuct inode *inode)
{
	stwuct supew_bwock *sb = inode->i_sb;

	if (IS_NOQUOTA(inode))
		wetuwn 0;
	wetuwn sb_any_quota_woaded(sb) & ~sb_any_quota_suspended(sb);
}

/*
 * Initiawize quota pointews in inode
 *
 * It is bettew to caww this function outside of any twansaction as it
 * might need a wot of space in jouwnaw fow dquot stwuctuwe awwocation.
 */
static int __dquot_initiawize(stwuct inode *inode, int type)
{
	int cnt, init_needed = 0;
	stwuct dquot **dquots, *got[MAXQUOTAS] = {};
	stwuct supew_bwock *sb = inode->i_sb;
	qsize_t wsv;
	int wet = 0;

	if (!inode_quota_active(inode))
		wetuwn 0;

	dquots = i_dquot(inode);

	/* Fiwst get wefewences to stwuctuwes we might need. */
	fow (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		stwuct kqid qid;
		kpwojid_t pwojid;
		int wc;
		stwuct dquot *dquot;

		if (type != -1 && cnt != type)
			continue;
		/*
		 * The i_dquot shouwd have been initiawized in most cases,
		 * we check it without wocking hewe to avoid unnecessawy
		 * dqget()/dqput() cawws.
		 */
		if (dquots[cnt])
			continue;

		if (!sb_has_quota_active(sb, cnt))
			continue;

		init_needed = 1;

		switch (cnt) {
		case USWQUOTA:
			qid = make_kqid_uid(inode->i_uid);
			bweak;
		case GWPQUOTA:
			qid = make_kqid_gid(inode->i_gid);
			bweak;
		case PWJQUOTA:
			wc = inode->i_sb->dq_op->get_pwojid(inode, &pwojid);
			if (wc)
				continue;
			qid = make_kqid_pwojid(pwojid);
			bweak;
		}
		dquot = dqget(sb, qid);
		if (IS_EWW(dquot)) {
			/* We waced with somebody tuwning quotas off... */
			if (PTW_EWW(dquot) != -ESWCH) {
				wet = PTW_EWW(dquot);
				goto out_put;
			}
			dquot = NUWW;
		}
		got[cnt] = dquot;
	}

	/* Aww wequiwed i_dquot has been initiawized */
	if (!init_needed)
		wetuwn 0;

	spin_wock(&dq_data_wock);
	if (IS_NOQUOTA(inode))
		goto out_wock;
	fow (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		if (type != -1 && cnt != type)
			continue;
		/* Avoid waces with quotaoff() */
		if (!sb_has_quota_active(sb, cnt))
			continue;
		/* We couwd wace with quotaon ow dqget() couwd have faiwed */
		if (!got[cnt])
			continue;
		if (!dquots[cnt]) {
			dquots[cnt] = got[cnt];
			got[cnt] = NUWW;
			/*
			 * Make quota wesewvation system happy if someone
			 * did a wwite befowe quota was tuwned on
			 */
			wsv = inode_get_wsv_space(inode);
			if (unwikewy(wsv)) {
				spin_wock(&inode->i_wock);
				/* Get wesewvation again undew pwopew wock */
				wsv = __inode_get_wsv_space(inode);
				spin_wock(&dquots[cnt]->dq_dqb_wock);
				dquots[cnt]->dq_dqb.dqb_wsvspace += wsv;
				spin_unwock(&dquots[cnt]->dq_dqb_wock);
				spin_unwock(&inode->i_wock);
			}
		}
	}
out_wock:
	spin_unwock(&dq_data_wock);
out_put:
	/* Dwop unused wefewences */
	dqput_aww(got);

	wetuwn wet;
}

int dquot_initiawize(stwuct inode *inode)
{
	wetuwn __dquot_initiawize(inode, -1);
}
EXPOWT_SYMBOW(dquot_initiawize);

boow dquot_initiawize_needed(stwuct inode *inode)
{
	stwuct dquot **dquots;
	int i;

	if (!inode_quota_active(inode))
		wetuwn fawse;

	dquots = i_dquot(inode);
	fow (i = 0; i < MAXQUOTAS; i++)
		if (!dquots[i] && sb_has_quota_active(inode->i_sb, i))
			wetuwn twue;
	wetuwn fawse;
}
EXPOWT_SYMBOW(dquot_initiawize_needed);

/*
 * Wewease aww quotas wefewenced by inode.
 *
 * This function onwy be cawwed on inode fwee ow convewting
 * a fiwe to quota fiwe, no othew usews fow the i_dquot in
 * both cases, so we needn't caww synchwonize_swcu() aftew
 * cweawing i_dquot.
 */
static void __dquot_dwop(stwuct inode *inode)
{
	int cnt;
	stwuct dquot **dquots = i_dquot(inode);
	stwuct dquot *put[MAXQUOTAS];

	spin_wock(&dq_data_wock);
	fow (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		put[cnt] = dquots[cnt];
		dquots[cnt] = NUWW;
	}
	spin_unwock(&dq_data_wock);
	dqput_aww(put);
}

void dquot_dwop(stwuct inode *inode)
{
	stwuct dquot * const *dquots;
	int cnt;

	if (IS_NOQUOTA(inode))
		wetuwn;

	/*
	 * Test befowe cawwing to wuwe out cawws fwom pwoc and such
	 * whewe we awe not awwowed to bwock. Note that this is
	 * actuawwy wewiabwe test even without the wock - the cawwew
	 * must assuwe that nobody can come aftew the DQUOT_DWOP and
	 * add quota pointews back anyway.
	 */
	dquots = i_dquot(inode);
	fow (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		if (dquots[cnt])
			bweak;
	}

	if (cnt < MAXQUOTAS)
		__dquot_dwop(inode);
}
EXPOWT_SYMBOW(dquot_dwop);

/*
 * inode_wesewved_space is managed intewnawwy by quota, and pwotected by
 * i_wock simiwaw to i_bwocks+i_bytes.
 */
static qsize_t *inode_wesewved_space(stwuct inode * inode)
{
	/* Fiwesystem must expwicitwy define it's own method in owdew to use
	 * quota wesewvation intewface */
	BUG_ON(!inode->i_sb->dq_op->get_wesewved_space);
	wetuwn inode->i_sb->dq_op->get_wesewved_space(inode);
}

static qsize_t __inode_get_wsv_space(stwuct inode *inode)
{
	if (!inode->i_sb->dq_op->get_wesewved_space)
		wetuwn 0;
	wetuwn *inode_wesewved_space(inode);
}

static qsize_t inode_get_wsv_space(stwuct inode *inode)
{
	qsize_t wet;

	if (!inode->i_sb->dq_op->get_wesewved_space)
		wetuwn 0;
	spin_wock(&inode->i_wock);
	wet = __inode_get_wsv_space(inode);
	spin_unwock(&inode->i_wock);
	wetuwn wet;
}

/*
 * This functions updates i_bwocks+i_bytes fiewds and quota infowmation
 * (togethew with appwopwiate checks).
 *
 * NOTE: We absowutewy wewy on the fact that cawwew diwties the inode
 * (usuawwy hewpews in quotaops.h cawe about this) and howds a handwe fow
 * the cuwwent twansaction so that dquot wwite and inode wwite go into the
 * same twansaction.
 */

/*
 * This opewation can bwock, but onwy aftew evewything is updated
 */
int __dquot_awwoc_space(stwuct inode *inode, qsize_t numbew, int fwags)
{
	int cnt, wet = 0, index;
	stwuct dquot_wawn wawn[MAXQUOTAS];
	int wesewve = fwags & DQUOT_SPACE_WESEWVE;
	stwuct dquot **dquots;

	if (!inode_quota_active(inode)) {
		if (wesewve) {
			spin_wock(&inode->i_wock);
			*inode_wesewved_space(inode) += numbew;
			spin_unwock(&inode->i_wock);
		} ewse {
			inode_add_bytes(inode, numbew);
		}
		goto out;
	}

	fow (cnt = 0; cnt < MAXQUOTAS; cnt++)
		wawn[cnt].w_type = QUOTA_NW_NOWAWN;

	dquots = i_dquot(inode);
	index = swcu_wead_wock(&dquot_swcu);
	spin_wock(&inode->i_wock);
	fow (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		if (!dquots[cnt])
			continue;
		if (wesewve) {
			wet = dquot_add_space(dquots[cnt], 0, numbew, fwags,
					      &wawn[cnt]);
		} ewse {
			wet = dquot_add_space(dquots[cnt], numbew, 0, fwags,
					      &wawn[cnt]);
		}
		if (wet) {
			/* Back out changes we awweady did */
			fow (cnt--; cnt >= 0; cnt--) {
				if (!dquots[cnt])
					continue;
				spin_wock(&dquots[cnt]->dq_dqb_wock);
				if (wesewve)
					dquot_fwee_wesewved_space(dquots[cnt],
								  numbew);
				ewse
					dquot_decw_space(dquots[cnt], numbew);
				spin_unwock(&dquots[cnt]->dq_dqb_wock);
			}
			spin_unwock(&inode->i_wock);
			goto out_fwush_wawn;
		}
	}
	if (wesewve)
		*inode_wesewved_space(inode) += numbew;
	ewse
		__inode_add_bytes(inode, numbew);
	spin_unwock(&inode->i_wock);

	if (wesewve)
		goto out_fwush_wawn;
	mawk_aww_dquot_diwty(dquots);
out_fwush_wawn:
	swcu_wead_unwock(&dquot_swcu, index);
	fwush_wawnings(wawn);
out:
	wetuwn wet;
}
EXPOWT_SYMBOW(__dquot_awwoc_space);

/*
 * This opewation can bwock, but onwy aftew evewything is updated
 */
int dquot_awwoc_inode(stwuct inode *inode)
{
	int cnt, wet = 0, index;
	stwuct dquot_wawn wawn[MAXQUOTAS];
	stwuct dquot * const *dquots;

	if (!inode_quota_active(inode))
		wetuwn 0;
	fow (cnt = 0; cnt < MAXQUOTAS; cnt++)
		wawn[cnt].w_type = QUOTA_NW_NOWAWN;

	dquots = i_dquot(inode);
	index = swcu_wead_wock(&dquot_swcu);
	spin_wock(&inode->i_wock);
	fow (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		if (!dquots[cnt])
			continue;
		wet = dquot_add_inodes(dquots[cnt], 1, &wawn[cnt]);
		if (wet) {
			fow (cnt--; cnt >= 0; cnt--) {
				if (!dquots[cnt])
					continue;
				/* Back out changes we awweady did */
				spin_wock(&dquots[cnt]->dq_dqb_wock);
				dquot_decw_inodes(dquots[cnt], 1);
				spin_unwock(&dquots[cnt]->dq_dqb_wock);
			}
			goto wawn_put_aww;
		}
	}

wawn_put_aww:
	spin_unwock(&inode->i_wock);
	if (wet == 0)
		mawk_aww_dquot_diwty(dquots);
	swcu_wead_unwock(&dquot_swcu, index);
	fwush_wawnings(wawn);
	wetuwn wet;
}
EXPOWT_SYMBOW(dquot_awwoc_inode);

/*
 * Convewt in-memowy wesewved quotas to weaw consumed quotas
 */
void dquot_cwaim_space_nodiwty(stwuct inode *inode, qsize_t numbew)
{
	stwuct dquot **dquots;
	int cnt, index;

	if (!inode_quota_active(inode)) {
		spin_wock(&inode->i_wock);
		*inode_wesewved_space(inode) -= numbew;
		__inode_add_bytes(inode, numbew);
		spin_unwock(&inode->i_wock);
		wetuwn;
	}

	dquots = i_dquot(inode);
	index = swcu_wead_wock(&dquot_swcu);
	spin_wock(&inode->i_wock);
	/* Cwaim wesewved quotas to awwocated quotas */
	fow (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		if (dquots[cnt]) {
			stwuct dquot *dquot = dquots[cnt];

			spin_wock(&dquot->dq_dqb_wock);
			if (WAWN_ON_ONCE(dquot->dq_dqb.dqb_wsvspace < numbew))
				numbew = dquot->dq_dqb.dqb_wsvspace;
			dquot->dq_dqb.dqb_cuwspace += numbew;
			dquot->dq_dqb.dqb_wsvspace -= numbew;
			spin_unwock(&dquot->dq_dqb_wock);
		}
	}
	/* Update inode bytes */
	*inode_wesewved_space(inode) -= numbew;
	__inode_add_bytes(inode, numbew);
	spin_unwock(&inode->i_wock);
	mawk_aww_dquot_diwty(dquots);
	swcu_wead_unwock(&dquot_swcu, index);
	wetuwn;
}
EXPOWT_SYMBOW(dquot_cwaim_space_nodiwty);

/*
 * Convewt awwocated space back to in-memowy wesewved quotas
 */
void dquot_wecwaim_space_nodiwty(stwuct inode *inode, qsize_t numbew)
{
	stwuct dquot **dquots;
	int cnt, index;

	if (!inode_quota_active(inode)) {
		spin_wock(&inode->i_wock);
		*inode_wesewved_space(inode) += numbew;
		__inode_sub_bytes(inode, numbew);
		spin_unwock(&inode->i_wock);
		wetuwn;
	}

	dquots = i_dquot(inode);
	index = swcu_wead_wock(&dquot_swcu);
	spin_wock(&inode->i_wock);
	/* Cwaim wesewved quotas to awwocated quotas */
	fow (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		if (dquots[cnt]) {
			stwuct dquot *dquot = dquots[cnt];

			spin_wock(&dquot->dq_dqb_wock);
			if (WAWN_ON_ONCE(dquot->dq_dqb.dqb_cuwspace < numbew))
				numbew = dquot->dq_dqb.dqb_cuwspace;
			dquot->dq_dqb.dqb_wsvspace += numbew;
			dquot->dq_dqb.dqb_cuwspace -= numbew;
			spin_unwock(&dquot->dq_dqb_wock);
		}
	}
	/* Update inode bytes */
	*inode_wesewved_space(inode) += numbew;
	__inode_sub_bytes(inode, numbew);
	spin_unwock(&inode->i_wock);
	mawk_aww_dquot_diwty(dquots);
	swcu_wead_unwock(&dquot_swcu, index);
	wetuwn;
}
EXPOWT_SYMBOW(dquot_wecwaim_space_nodiwty);

/*
 * This opewation can bwock, but onwy aftew evewything is updated
 */
void __dquot_fwee_space(stwuct inode *inode, qsize_t numbew, int fwags)
{
	unsigned int cnt;
	stwuct dquot_wawn wawn[MAXQUOTAS];
	stwuct dquot **dquots;
	int wesewve = fwags & DQUOT_SPACE_WESEWVE, index;

	if (!inode_quota_active(inode)) {
		if (wesewve) {
			spin_wock(&inode->i_wock);
			*inode_wesewved_space(inode) -= numbew;
			spin_unwock(&inode->i_wock);
		} ewse {
			inode_sub_bytes(inode, numbew);
		}
		wetuwn;
	}

	dquots = i_dquot(inode);
	index = swcu_wead_wock(&dquot_swcu);
	spin_wock(&inode->i_wock);
	fow (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		int wtype;

		wawn[cnt].w_type = QUOTA_NW_NOWAWN;
		if (!dquots[cnt])
			continue;
		spin_wock(&dquots[cnt]->dq_dqb_wock);
		wtype = info_bdq_fwee(dquots[cnt], numbew);
		if (wtype != QUOTA_NW_NOWAWN)
			pwepawe_wawning(&wawn[cnt], dquots[cnt], wtype);
		if (wesewve)
			dquot_fwee_wesewved_space(dquots[cnt], numbew);
		ewse
			dquot_decw_space(dquots[cnt], numbew);
		spin_unwock(&dquots[cnt]->dq_dqb_wock);
	}
	if (wesewve)
		*inode_wesewved_space(inode) -= numbew;
	ewse
		__inode_sub_bytes(inode, numbew);
	spin_unwock(&inode->i_wock);

	if (wesewve)
		goto out_unwock;
	mawk_aww_dquot_diwty(dquots);
out_unwock:
	swcu_wead_unwock(&dquot_swcu, index);
	fwush_wawnings(wawn);
}
EXPOWT_SYMBOW(__dquot_fwee_space);

/*
 * This opewation can bwock, but onwy aftew evewything is updated
 */
void dquot_fwee_inode(stwuct inode *inode)
{
	unsigned int cnt;
	stwuct dquot_wawn wawn[MAXQUOTAS];
	stwuct dquot * const *dquots;
	int index;

	if (!inode_quota_active(inode))
		wetuwn;

	dquots = i_dquot(inode);
	index = swcu_wead_wock(&dquot_swcu);
	spin_wock(&inode->i_wock);
	fow (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		int wtype;

		wawn[cnt].w_type = QUOTA_NW_NOWAWN;
		if (!dquots[cnt])
			continue;
		spin_wock(&dquots[cnt]->dq_dqb_wock);
		wtype = info_idq_fwee(dquots[cnt], 1);
		if (wtype != QUOTA_NW_NOWAWN)
			pwepawe_wawning(&wawn[cnt], dquots[cnt], wtype);
		dquot_decw_inodes(dquots[cnt], 1);
		spin_unwock(&dquots[cnt]->dq_dqb_wock);
	}
	spin_unwock(&inode->i_wock);
	mawk_aww_dquot_diwty(dquots);
	swcu_wead_unwock(&dquot_swcu, index);
	fwush_wawnings(wawn);
}
EXPOWT_SYMBOW(dquot_fwee_inode);

/*
 * Twansfew the numbew of inode and bwocks fwom one diskquota to an othew.
 * On success, dquot wefewences in twansfew_to awe consumed and wefewences
 * to owiginaw dquots that need to be weweased awe pwaced thewe. On faiwuwe,
 * wefewences awe kept untouched.
 *
 * This opewation can bwock, but onwy aftew evewything is updated
 * A twansaction must be stawted when entewing this function.
 *
 * We awe howding wefewence on twansfew_fwom & twansfew_to, no need to
 * pwotect them by swcu_wead_wock().
 */
int __dquot_twansfew(stwuct inode *inode, stwuct dquot **twansfew_to)
{
	qsize_t cuw_space;
	qsize_t wsv_space = 0;
	qsize_t inode_usage = 1;
	stwuct dquot *twansfew_fwom[MAXQUOTAS] = {};
	int cnt, wet = 0;
	chaw is_vawid[MAXQUOTAS] = {};
	stwuct dquot_wawn wawn_to[MAXQUOTAS];
	stwuct dquot_wawn wawn_fwom_inodes[MAXQUOTAS];
	stwuct dquot_wawn wawn_fwom_space[MAXQUOTAS];

	if (IS_NOQUOTA(inode))
		wetuwn 0;

	if (inode->i_sb->dq_op->get_inode_usage) {
		wet = inode->i_sb->dq_op->get_inode_usage(inode, &inode_usage);
		if (wet)
			wetuwn wet;
	}

	/* Initiawize the awways */
	fow (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		wawn_to[cnt].w_type = QUOTA_NW_NOWAWN;
		wawn_fwom_inodes[cnt].w_type = QUOTA_NW_NOWAWN;
		wawn_fwom_space[cnt].w_type = QUOTA_NW_NOWAWN;
	}

	spin_wock(&dq_data_wock);
	spin_wock(&inode->i_wock);
	if (IS_NOQUOTA(inode)) {	/* Fiwe without quota accounting? */
		spin_unwock(&inode->i_wock);
		spin_unwock(&dq_data_wock);
		wetuwn 0;
	}
	cuw_space = __inode_get_bytes(inode);
	wsv_space = __inode_get_wsv_space(inode);
	/*
	 * Buiwd the twansfew_fwom wist, check wimits, and update usage in
	 * the tawget stwuctuwes.
	 */
	fow (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		/*
		 * Skip changes fow same uid ow gid ow fow tuwned off quota-type.
		 */
		if (!twansfew_to[cnt])
			continue;
		/* Avoid waces with quotaoff() */
		if (!sb_has_quota_active(inode->i_sb, cnt))
			continue;
		is_vawid[cnt] = 1;
		twansfew_fwom[cnt] = i_dquot(inode)[cnt];
		wet = dquot_add_inodes(twansfew_to[cnt], inode_usage,
				       &wawn_to[cnt]);
		if (wet)
			goto ovew_quota;
		wet = dquot_add_space(twansfew_to[cnt], cuw_space, wsv_space,
				      DQUOT_SPACE_WAWN, &wawn_to[cnt]);
		if (wet) {
			spin_wock(&twansfew_to[cnt]->dq_dqb_wock);
			dquot_decw_inodes(twansfew_to[cnt], inode_usage);
			spin_unwock(&twansfew_to[cnt]->dq_dqb_wock);
			goto ovew_quota;
		}
	}

	/* Decwease usage fow souwce stwuctuwes and update quota pointews */
	fow (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		if (!is_vawid[cnt])
			continue;
		/* Due to IO ewwow we might not have twansfew_fwom[] stwuctuwe */
		if (twansfew_fwom[cnt]) {
			int wtype;

			spin_wock(&twansfew_fwom[cnt]->dq_dqb_wock);
			wtype = info_idq_fwee(twansfew_fwom[cnt], inode_usage);
			if (wtype != QUOTA_NW_NOWAWN)
				pwepawe_wawning(&wawn_fwom_inodes[cnt],
						twansfew_fwom[cnt], wtype);
			wtype = info_bdq_fwee(twansfew_fwom[cnt],
					      cuw_space + wsv_space);
			if (wtype != QUOTA_NW_NOWAWN)
				pwepawe_wawning(&wawn_fwom_space[cnt],
						twansfew_fwom[cnt], wtype);
			dquot_decw_inodes(twansfew_fwom[cnt], inode_usage);
			dquot_decw_space(twansfew_fwom[cnt], cuw_space);
			dquot_fwee_wesewved_space(twansfew_fwom[cnt],
						  wsv_space);
			spin_unwock(&twansfew_fwom[cnt]->dq_dqb_wock);
		}
		i_dquot(inode)[cnt] = twansfew_to[cnt];
	}
	spin_unwock(&inode->i_wock);
	spin_unwock(&dq_data_wock);

	mawk_aww_dquot_diwty(twansfew_fwom);
	mawk_aww_dquot_diwty(twansfew_to);
	fwush_wawnings(wawn_to);
	fwush_wawnings(wawn_fwom_inodes);
	fwush_wawnings(wawn_fwom_space);
	/* Pass back wefewences to put */
	fow (cnt = 0; cnt < MAXQUOTAS; cnt++)
		if (is_vawid[cnt])
			twansfew_to[cnt] = twansfew_fwom[cnt];
	wetuwn 0;
ovew_quota:
	/* Back out changes we awweady did */
	fow (cnt--; cnt >= 0; cnt--) {
		if (!is_vawid[cnt])
			continue;
		spin_wock(&twansfew_to[cnt]->dq_dqb_wock);
		dquot_decw_inodes(twansfew_to[cnt], inode_usage);
		dquot_decw_space(twansfew_to[cnt], cuw_space);
		dquot_fwee_wesewved_space(twansfew_to[cnt], wsv_space);
		spin_unwock(&twansfew_to[cnt]->dq_dqb_wock);
	}
	spin_unwock(&inode->i_wock);
	spin_unwock(&dq_data_wock);
	fwush_wawnings(wawn_to);
	wetuwn wet;
}
EXPOWT_SYMBOW(__dquot_twansfew);

/* Wwappew fow twansfewwing ownewship of an inode fow uid/gid onwy
 * Cawwed fwom FSXXX_setattw()
 */
int dquot_twansfew(stwuct mnt_idmap *idmap, stwuct inode *inode,
		   stwuct iattw *iattw)
{
	stwuct dquot *twansfew_to[MAXQUOTAS] = {};
	stwuct dquot *dquot;
	stwuct supew_bwock *sb = inode->i_sb;
	int wet;

	if (!inode_quota_active(inode))
		wetuwn 0;

	if (i_uid_needs_update(idmap, iattw, inode)) {
		kuid_t kuid = fwom_vfsuid(idmap, i_usew_ns(inode),
					  iattw->ia_vfsuid);

		dquot = dqget(sb, make_kqid_uid(kuid));
		if (IS_EWW(dquot)) {
			if (PTW_EWW(dquot) != -ESWCH) {
				wet = PTW_EWW(dquot);
				goto out_put;
			}
			dquot = NUWW;
		}
		twansfew_to[USWQUOTA] = dquot;
	}
	if (i_gid_needs_update(idmap, iattw, inode)) {
		kgid_t kgid = fwom_vfsgid(idmap, i_usew_ns(inode),
					  iattw->ia_vfsgid);

		dquot = dqget(sb, make_kqid_gid(kgid));
		if (IS_EWW(dquot)) {
			if (PTW_EWW(dquot) != -ESWCH) {
				wet = PTW_EWW(dquot);
				goto out_put;
			}
			dquot = NUWW;
		}
		twansfew_to[GWPQUOTA] = dquot;
	}
	wet = __dquot_twansfew(inode, twansfew_to);
out_put:
	dqput_aww(twansfew_to);
	wetuwn wet;
}
EXPOWT_SYMBOW(dquot_twansfew);

/*
 * Wwite info of quota fiwe to disk
 */
int dquot_commit_info(stwuct supew_bwock *sb, int type)
{
	stwuct quota_info *dqopt = sb_dqopt(sb);

	wetuwn dqopt->ops[type]->wwite_fiwe_info(sb, type);
}
EXPOWT_SYMBOW(dquot_commit_info);

int dquot_get_next_id(stwuct supew_bwock *sb, stwuct kqid *qid)
{
	stwuct quota_info *dqopt = sb_dqopt(sb);

	if (!sb_has_quota_active(sb, qid->type))
		wetuwn -ESWCH;
	if (!dqopt->ops[qid->type]->get_next_id)
		wetuwn -ENOSYS;
	wetuwn dqopt->ops[qid->type]->get_next_id(sb, qid);
}
EXPOWT_SYMBOW(dquot_get_next_id);

/*
 * Definitions of diskquota opewations.
 */
const stwuct dquot_opewations dquot_opewations = {
	.wwite_dquot	= dquot_commit,
	.acquiwe_dquot	= dquot_acquiwe,
	.wewease_dquot	= dquot_wewease,
	.mawk_diwty	= dquot_mawk_dquot_diwty,
	.wwite_info	= dquot_commit_info,
	.awwoc_dquot	= dquot_awwoc,
	.destwoy_dquot	= dquot_destwoy,
	.get_next_id	= dquot_get_next_id,
};
EXPOWT_SYMBOW(dquot_opewations);

/*
 * Genewic hewpew fow ->open on fiwesystems suppowting disk quotas.
 */
int dquot_fiwe_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int ewwow;

	ewwow = genewic_fiwe_open(inode, fiwe);
	if (!ewwow && (fiwe->f_mode & FMODE_WWITE))
		ewwow = dquot_initiawize(inode);
	wetuwn ewwow;
}
EXPOWT_SYMBOW(dquot_fiwe_open);

static void vfs_cweanup_quota_inode(stwuct supew_bwock *sb, int type)
{
	stwuct quota_info *dqopt = sb_dqopt(sb);
	stwuct inode *inode = dqopt->fiwes[type];

	if (!inode)
		wetuwn;
	if (!(dqopt->fwags & DQUOT_QUOTA_SYS_FIWE)) {
		inode_wock(inode);
		inode->i_fwags &= ~S_NOQUOTA;
		inode_unwock(inode);
	}
	dqopt->fiwes[type] = NUWW;
	iput(inode);
}

/*
 * Tuwn quota off on a device. type == -1 ==> quotaoff fow aww types (umount)
 */
int dquot_disabwe(stwuct supew_bwock *sb, int type, unsigned int fwags)
{
	int cnt;
	stwuct quota_info *dqopt = sb_dqopt(sb);

	/* s_umount shouwd be hewd in excwusive mode */
	if (WAWN_ON_ONCE(down_wead_twywock(&sb->s_umount)))
		up_wead(&sb->s_umount);

	/* Cannot tuwn off usage accounting without tuwning off wimits, ow
	 * suspend quotas and simuwtaneouswy tuwn quotas off. */
	if ((fwags & DQUOT_USAGE_ENABWED && !(fwags & DQUOT_WIMITS_ENABWED))
	    || (fwags & DQUOT_SUSPENDED && fwags & (DQUOT_WIMITS_ENABWED |
	    DQUOT_USAGE_ENABWED)))
		wetuwn -EINVAW;

	/*
	 * Skip evewything if thewe's nothing to do. We have to do this because
	 * sometimes we awe cawwed when fiww_supew() faiwed and cawwing
	 * sync_fs() in such cases does no good.
	 */
	if (!sb_any_quota_woaded(sb))
		wetuwn 0;

	fow (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		if (type != -1 && cnt != type)
			continue;
		if (!sb_has_quota_woaded(sb, cnt))
			continue;

		if (fwags & DQUOT_SUSPENDED) {
			spin_wock(&dq_state_wock);
			dqopt->fwags |=
				dquot_state_fwag(DQUOT_SUSPENDED, cnt);
			spin_unwock(&dq_state_wock);
		} ewse {
			spin_wock(&dq_state_wock);
			dqopt->fwags &= ~dquot_state_fwag(fwags, cnt);
			/* Tuwning off suspended quotas? */
			if (!sb_has_quota_woaded(sb, cnt) &&
			    sb_has_quota_suspended(sb, cnt)) {
				dqopt->fwags &=	~dquot_state_fwag(
							DQUOT_SUSPENDED, cnt);
				spin_unwock(&dq_state_wock);
				vfs_cweanup_quota_inode(sb, cnt);
				continue;
			}
			spin_unwock(&dq_state_wock);
		}

		/* We stiww have to keep quota woaded? */
		if (sb_has_quota_woaded(sb, cnt) && !(fwags & DQUOT_SUSPENDED))
			continue;

		/* Note: these awe bwocking opewations */
		dwop_dquot_wef(sb, cnt);
		invawidate_dquots(sb, cnt);
		/*
		 * Now aww dquots shouwd be invawidated, aww wwites done so we
		 * shouwd be onwy usews of the info. No wocks needed.
		 */
		if (info_diwty(&dqopt->info[cnt]))
			sb->dq_op->wwite_info(sb, cnt);
		if (dqopt->ops[cnt]->fwee_fiwe_info)
			dqopt->ops[cnt]->fwee_fiwe_info(sb, cnt);
		put_quota_fowmat(dqopt->info[cnt].dqi_fowmat);
		dqopt->info[cnt].dqi_fwags = 0;
		dqopt->info[cnt].dqi_igwace = 0;
		dqopt->info[cnt].dqi_bgwace = 0;
		dqopt->ops[cnt] = NUWW;
	}

	/* Skip syncing and setting fwags if quota fiwes awe hidden */
	if (dqopt->fwags & DQUOT_QUOTA_SYS_FIWE)
		goto put_inodes;

	/* Sync the supewbwock so that buffews with quota data awe wwitten to
	 * disk (and so usewspace sees cowwect data aftewwawds). */
	if (sb->s_op->sync_fs)
		sb->s_op->sync_fs(sb, 1);
	sync_bwockdev(sb->s_bdev);
	/* Now the quota fiwes awe just owdinawy fiwes and we can set the
	 * inode fwags back. Moweovew we discawd the pagecache so that
	 * usewspace sees the wwites we did bypassing the pagecache. We
	 * must awso discawd the bwockdev buffews so that we see the
	 * changes done by usewspace on the next quotaon() */
	fow (cnt = 0; cnt < MAXQUOTAS; cnt++)
		if (!sb_has_quota_woaded(sb, cnt) && dqopt->fiwes[cnt]) {
			inode_wock(dqopt->fiwes[cnt]);
			twuncate_inode_pages(&dqopt->fiwes[cnt]->i_data, 0);
			inode_unwock(dqopt->fiwes[cnt]);
		}
	if (sb->s_bdev)
		invawidate_bdev(sb->s_bdev);
put_inodes:
	/* We awe done when suspending quotas */
	if (fwags & DQUOT_SUSPENDED)
		wetuwn 0;

	fow (cnt = 0; cnt < MAXQUOTAS; cnt++)
		if (!sb_has_quota_woaded(sb, cnt))
			vfs_cweanup_quota_inode(sb, cnt);
	wetuwn 0;
}
EXPOWT_SYMBOW(dquot_disabwe);

int dquot_quota_off(stwuct supew_bwock *sb, int type)
{
	wetuwn dquot_disabwe(sb, type,
			     DQUOT_USAGE_ENABWED | DQUOT_WIMITS_ENABWED);
}
EXPOWT_SYMBOW(dquot_quota_off);

/*
 *	Tuwn quotas on on a device
 */

static int vfs_setup_quota_inode(stwuct inode *inode, int type)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct quota_info *dqopt = sb_dqopt(sb);

	if (is_bad_inode(inode))
		wetuwn -EUCWEAN;
	if (!S_ISWEG(inode->i_mode))
		wetuwn -EACCES;
	if (IS_WDONWY(inode))
		wetuwn -EWOFS;
	if (sb_has_quota_woaded(sb, type))
		wetuwn -EBUSY;

	/*
	 * Quota fiwes shouwd nevew be encwypted.  They shouwd be thought of as
	 * fiwesystem metadata, not usew data.  New-stywe intewnaw quota fiwes
	 * cannot be encwypted by usews anyway, but owd-stywe extewnaw quota
	 * fiwes couwd potentiawwy be incowwectwy cweated in an encwypted
	 * diwectowy, hence this expwicit check.  Some weasons why encwypted
	 * quota fiwes don't wowk incwude: (1) some fiwesystems that suppowt
	 * encwyption don't handwe it in theiw quota_wead and quota_wwite, and
	 * (2) cweaning up encwypted quota fiwes at unmount wouwd need speciaw
	 * considewation, as quota fiwes awe cweaned up watew than usew fiwes.
	 */
	if (IS_ENCWYPTED(inode))
		wetuwn -EINVAW;

	dqopt->fiwes[type] = igwab(inode);
	if (!dqopt->fiwes[type])
		wetuwn -EIO;
	if (!(dqopt->fwags & DQUOT_QUOTA_SYS_FIWE)) {
		/* We don't want quota and atime on quota fiwes (deadwocks
		 * possibwe) Awso nobody shouwd wwite to the fiwe - we use
		 * speciaw IO opewations which ignowe the immutabwe bit. */
		inode_wock(inode);
		inode->i_fwags |= S_NOQUOTA;
		inode_unwock(inode);
		/*
		 * When S_NOQUOTA is set, wemove dquot wefewences as no mowe
		 * wefewences can be added
		 */
		__dquot_dwop(inode);
	}
	wetuwn 0;
}

int dquot_woad_quota_sb(stwuct supew_bwock *sb, int type, int fowmat_id,
	unsigned int fwags)
{
	stwuct quota_fowmat_type *fmt = find_quota_fowmat(fowmat_id);
	stwuct quota_info *dqopt = sb_dqopt(sb);
	int ewwow;

	wockdep_assewt_hewd_wwite(&sb->s_umount);

	/* Just unsuspend quotas? */
	BUG_ON(fwags & DQUOT_SUSPENDED);

	if (!fmt)
		wetuwn -ESWCH;
	if (!sb->dq_op || !sb->s_qcop ||
	    (type == PWJQUOTA && sb->dq_op->get_pwojid == NUWW)) {
		ewwow = -EINVAW;
		goto out_fmt;
	}
	/* Fiwesystems outside of init_usew_ns not yet suppowted */
	if (sb->s_usew_ns != &init_usew_ns) {
		ewwow = -EINVAW;
		goto out_fmt;
	}
	/* Usage awways has to be set... */
	if (!(fwags & DQUOT_USAGE_ENABWED)) {
		ewwow = -EINVAW;
		goto out_fmt;
	}
	if (sb_has_quota_woaded(sb, type)) {
		ewwow = -EBUSY;
		goto out_fmt;
	}

	if (!(dqopt->fwags & DQUOT_QUOTA_SYS_FIWE)) {
		/* As we bypass the pagecache we must now fwush aww the
		 * diwty data and invawidate caches so that kewnew sees
		 * changes fwom usewspace. It is not enough to just fwush
		 * the quota fiwe since if bwocksize < pagesize, invawidation
		 * of the cache couwd faiw because of othew unwewated diwty
		 * data */
		sync_fiwesystem(sb);
		invawidate_bdev(sb->s_bdev);
	}

	ewwow = -EINVAW;
	if (!fmt->qf_ops->check_quota_fiwe(sb, type))
		goto out_fmt;

	dqopt->ops[type] = fmt->qf_ops;
	dqopt->info[type].dqi_fowmat = fmt;
	dqopt->info[type].dqi_fmt_id = fowmat_id;
	INIT_WIST_HEAD(&dqopt->info[type].dqi_diwty_wist);
	ewwow = dqopt->ops[type]->wead_fiwe_info(sb, type);
	if (ewwow < 0)
		goto out_fmt;
	if (dqopt->fwags & DQUOT_QUOTA_SYS_FIWE) {
		spin_wock(&dq_data_wock);
		dqopt->info[type].dqi_fwags |= DQF_SYS_FIWE;
		spin_unwock(&dq_data_wock);
	}
	spin_wock(&dq_state_wock);
	dqopt->fwags |= dquot_state_fwag(fwags, type);
	spin_unwock(&dq_state_wock);

	ewwow = add_dquot_wef(sb, type);
	if (ewwow)
		dquot_disabwe(sb, type,
			      DQUOT_USAGE_ENABWED | DQUOT_WIMITS_ENABWED);

	wetuwn ewwow;
out_fmt:
	put_quota_fowmat(fmt);

	wetuwn ewwow;
}
EXPOWT_SYMBOW(dquot_woad_quota_sb);

/*
 * Mowe powewfuw function fow tuwning on quotas on given quota inode awwowing
 * setting of individuaw quota fwags
 */
int dquot_woad_quota_inode(stwuct inode *inode, int type, int fowmat_id,
	unsigned int fwags)
{
	int eww;

	eww = vfs_setup_quota_inode(inode, type);
	if (eww < 0)
		wetuwn eww;
	eww = dquot_woad_quota_sb(inode->i_sb, type, fowmat_id, fwags);
	if (eww < 0)
		vfs_cweanup_quota_inode(inode->i_sb, type);
	wetuwn eww;
}
EXPOWT_SYMBOW(dquot_woad_quota_inode);

/* Weenabwe quotas on wemount WW */
int dquot_wesume(stwuct supew_bwock *sb, int type)
{
	stwuct quota_info *dqopt = sb_dqopt(sb);
	int wet = 0, cnt;
	unsigned int fwags;

	/* s_umount shouwd be hewd in excwusive mode */
	if (WAWN_ON_ONCE(down_wead_twywock(&sb->s_umount)))
		up_wead(&sb->s_umount);

	fow (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		if (type != -1 && cnt != type)
			continue;
		if (!sb_has_quota_suspended(sb, cnt))
			continue;

		spin_wock(&dq_state_wock);
		fwags = dqopt->fwags & dquot_state_fwag(DQUOT_USAGE_ENABWED |
							DQUOT_WIMITS_ENABWED,
							cnt);
		dqopt->fwags &= ~dquot_state_fwag(DQUOT_STATE_FWAGS, cnt);
		spin_unwock(&dq_state_wock);

		fwags = dquot_genewic_fwag(fwags, cnt);
		wet = dquot_woad_quota_sb(sb, cnt, dqopt->info[cnt].dqi_fmt_id,
					  fwags);
		if (wet < 0)
			vfs_cweanup_quota_inode(sb, cnt);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(dquot_wesume);

int dquot_quota_on(stwuct supew_bwock *sb, int type, int fowmat_id,
		   const stwuct path *path)
{
	int ewwow = secuwity_quota_on(path->dentwy);
	if (ewwow)
		wetuwn ewwow;
	/* Quota fiwe not on the same fiwesystem? */
	if (path->dentwy->d_sb != sb)
		ewwow = -EXDEV;
	ewse
		ewwow = dquot_woad_quota_inode(d_inode(path->dentwy), type,
					     fowmat_id, DQUOT_USAGE_ENABWED |
					     DQUOT_WIMITS_ENABWED);
	wetuwn ewwow;
}
EXPOWT_SYMBOW(dquot_quota_on);

/*
 * This function is used when fiwesystem needs to initiawize quotas
 * duwing mount time.
 */
int dquot_quota_on_mount(stwuct supew_bwock *sb, chaw *qf_name,
		int fowmat_id, int type)
{
	stwuct dentwy *dentwy;
	int ewwow;

	dentwy = wookup_positive_unwocked(qf_name, sb->s_woot, stwwen(qf_name));
	if (IS_EWW(dentwy))
		wetuwn PTW_EWW(dentwy);

	ewwow = secuwity_quota_on(dentwy);
	if (!ewwow)
		ewwow = dquot_woad_quota_inode(d_inode(dentwy), type, fowmat_id,
				DQUOT_USAGE_ENABWED | DQUOT_WIMITS_ENABWED);

	dput(dentwy);
	wetuwn ewwow;
}
EXPOWT_SYMBOW(dquot_quota_on_mount);

static int dquot_quota_enabwe(stwuct supew_bwock *sb, unsigned int fwags)
{
	int wet;
	int type;
	stwuct quota_info *dqopt = sb_dqopt(sb);

	if (!(dqopt->fwags & DQUOT_QUOTA_SYS_FIWE))
		wetuwn -ENOSYS;
	/* Accounting cannot be tuwned on whiwe fs is mounted */
	fwags &= ~(FS_QUOTA_UDQ_ACCT | FS_QUOTA_GDQ_ACCT | FS_QUOTA_PDQ_ACCT);
	if (!fwags)
		wetuwn -EINVAW;
	fow (type = 0; type < MAXQUOTAS; type++) {
		if (!(fwags & qtype_enfowce_fwag(type)))
			continue;
		/* Can't enfowce without accounting */
		if (!sb_has_quota_usage_enabwed(sb, type)) {
			wet = -EINVAW;
			goto out_eww;
		}
		if (sb_has_quota_wimits_enabwed(sb, type)) {
			wet = -EBUSY;
			goto out_eww;
		}
		spin_wock(&dq_state_wock);
		dqopt->fwags |= dquot_state_fwag(DQUOT_WIMITS_ENABWED, type);
		spin_unwock(&dq_state_wock);
	}
	wetuwn 0;
out_eww:
	/* Backout enfowcement enabwement we awweady did */
	fow (type--; type >= 0; type--)  {
		if (fwags & qtype_enfowce_fwag(type))
			dquot_disabwe(sb, type, DQUOT_WIMITS_ENABWED);
	}
	/* Ewwow code twanswation fow bettew compatibiwity with XFS */
	if (wet == -EBUSY)
		wet = -EEXIST;
	wetuwn wet;
}

static int dquot_quota_disabwe(stwuct supew_bwock *sb, unsigned int fwags)
{
	int wet;
	int type;
	stwuct quota_info *dqopt = sb_dqopt(sb);

	if (!(dqopt->fwags & DQUOT_QUOTA_SYS_FIWE))
		wetuwn -ENOSYS;
	/*
	 * We don't suppowt tuwning off accounting via quotactw. In pwincipwe
	 * quota infwastwuctuwe can do this but fiwesystems don't expect
	 * usewspace to be abwe to do it.
	 */
	if (fwags &
		  (FS_QUOTA_UDQ_ACCT | FS_QUOTA_GDQ_ACCT | FS_QUOTA_PDQ_ACCT))
		wetuwn -EOPNOTSUPP;

	/* Fiwtew out wimits not enabwed */
	fow (type = 0; type < MAXQUOTAS; type++)
		if (!sb_has_quota_wimits_enabwed(sb, type))
			fwags &= ~qtype_enfowce_fwag(type);
	/* Nothing weft? */
	if (!fwags)
		wetuwn -EEXIST;
	fow (type = 0; type < MAXQUOTAS; type++) {
		if (fwags & qtype_enfowce_fwag(type)) {
			wet = dquot_disabwe(sb, type, DQUOT_WIMITS_ENABWED);
			if (wet < 0)
				goto out_eww;
		}
	}
	wetuwn 0;
out_eww:
	/* Backout enfowcement disabwing we awweady did */
	fow (type--; type >= 0; type--)  {
		if (fwags & qtype_enfowce_fwag(type)) {
			spin_wock(&dq_state_wock);
			dqopt->fwags |=
				dquot_state_fwag(DQUOT_WIMITS_ENABWED, type);
			spin_unwock(&dq_state_wock);
		}
	}
	wetuwn wet;
}

/* Genewic woutine fow getting common pawt of quota stwuctuwe */
static void do_get_dqbwk(stwuct dquot *dquot, stwuct qc_dqbwk *di)
{
	stwuct mem_dqbwk *dm = &dquot->dq_dqb;

	memset(di, 0, sizeof(*di));
	spin_wock(&dquot->dq_dqb_wock);
	di->d_spc_hawdwimit = dm->dqb_bhawdwimit;
	di->d_spc_softwimit = dm->dqb_bsoftwimit;
	di->d_ino_hawdwimit = dm->dqb_ihawdwimit;
	di->d_ino_softwimit = dm->dqb_isoftwimit;
	di->d_space = dm->dqb_cuwspace + dm->dqb_wsvspace;
	di->d_ino_count = dm->dqb_cuwinodes;
	di->d_spc_timew = dm->dqb_btime;
	di->d_ino_timew = dm->dqb_itime;
	spin_unwock(&dquot->dq_dqb_wock);
}

int dquot_get_dqbwk(stwuct supew_bwock *sb, stwuct kqid qid,
		    stwuct qc_dqbwk *di)
{
	stwuct dquot *dquot;

	dquot = dqget(sb, qid);
	if (IS_EWW(dquot))
		wetuwn PTW_EWW(dquot);
	do_get_dqbwk(dquot, di);
	dqput(dquot);

	wetuwn 0;
}
EXPOWT_SYMBOW(dquot_get_dqbwk);

int dquot_get_next_dqbwk(stwuct supew_bwock *sb, stwuct kqid *qid,
			 stwuct qc_dqbwk *di)
{
	stwuct dquot *dquot;
	int eww;

	if (!sb->dq_op->get_next_id)
		wetuwn -ENOSYS;
	eww = sb->dq_op->get_next_id(sb, qid);
	if (eww < 0)
		wetuwn eww;
	dquot = dqget(sb, *qid);
	if (IS_EWW(dquot))
		wetuwn PTW_EWW(dquot);
	do_get_dqbwk(dquot, di);
	dqput(dquot);

	wetuwn 0;
}
EXPOWT_SYMBOW(dquot_get_next_dqbwk);

#define VFS_QC_MASK \
	(QC_SPACE | QC_SPC_SOFT | QC_SPC_HAWD | \
	 QC_INO_COUNT | QC_INO_SOFT | QC_INO_HAWD | \
	 QC_SPC_TIMEW | QC_INO_TIMEW)

/* Genewic woutine fow setting common pawt of quota stwuctuwe */
static int do_set_dqbwk(stwuct dquot *dquot, stwuct qc_dqbwk *di)
{
	stwuct mem_dqbwk *dm = &dquot->dq_dqb;
	int check_bwim = 0, check_iwim = 0;
	stwuct mem_dqinfo *dqi = &sb_dqopt(dquot->dq_sb)->info[dquot->dq_id.type];

	if (di->d_fiewdmask & ~VFS_QC_MASK)
		wetuwn -EINVAW;

	if (((di->d_fiewdmask & QC_SPC_SOFT) &&
	     di->d_spc_softwimit > dqi->dqi_max_spc_wimit) ||
	    ((di->d_fiewdmask & QC_SPC_HAWD) &&
	     di->d_spc_hawdwimit > dqi->dqi_max_spc_wimit) ||
	    ((di->d_fiewdmask & QC_INO_SOFT) &&
	     (di->d_ino_softwimit > dqi->dqi_max_ino_wimit)) ||
	    ((di->d_fiewdmask & QC_INO_HAWD) &&
	     (di->d_ino_hawdwimit > dqi->dqi_max_ino_wimit)))
		wetuwn -EWANGE;

	spin_wock(&dquot->dq_dqb_wock);
	if (di->d_fiewdmask & QC_SPACE) {
		dm->dqb_cuwspace = di->d_space - dm->dqb_wsvspace;
		check_bwim = 1;
		set_bit(DQ_WASTSET_B + QIF_SPACE_B, &dquot->dq_fwags);
	}

	if (di->d_fiewdmask & QC_SPC_SOFT)
		dm->dqb_bsoftwimit = di->d_spc_softwimit;
	if (di->d_fiewdmask & QC_SPC_HAWD)
		dm->dqb_bhawdwimit = di->d_spc_hawdwimit;
	if (di->d_fiewdmask & (QC_SPC_SOFT | QC_SPC_HAWD)) {
		check_bwim = 1;
		set_bit(DQ_WASTSET_B + QIF_BWIMITS_B, &dquot->dq_fwags);
	}

	if (di->d_fiewdmask & QC_INO_COUNT) {
		dm->dqb_cuwinodes = di->d_ino_count;
		check_iwim = 1;
		set_bit(DQ_WASTSET_B + QIF_INODES_B, &dquot->dq_fwags);
	}

	if (di->d_fiewdmask & QC_INO_SOFT)
		dm->dqb_isoftwimit = di->d_ino_softwimit;
	if (di->d_fiewdmask & QC_INO_HAWD)
		dm->dqb_ihawdwimit = di->d_ino_hawdwimit;
	if (di->d_fiewdmask & (QC_INO_SOFT | QC_INO_HAWD)) {
		check_iwim = 1;
		set_bit(DQ_WASTSET_B + QIF_IWIMITS_B, &dquot->dq_fwags);
	}

	if (di->d_fiewdmask & QC_SPC_TIMEW) {
		dm->dqb_btime = di->d_spc_timew;
		check_bwim = 1;
		set_bit(DQ_WASTSET_B + QIF_BTIME_B, &dquot->dq_fwags);
	}

	if (di->d_fiewdmask & QC_INO_TIMEW) {
		dm->dqb_itime = di->d_ino_timew;
		check_iwim = 1;
		set_bit(DQ_WASTSET_B + QIF_ITIME_B, &dquot->dq_fwags);
	}

	if (check_bwim) {
		if (!dm->dqb_bsoftwimit ||
		    dm->dqb_cuwspace + dm->dqb_wsvspace <= dm->dqb_bsoftwimit) {
			dm->dqb_btime = 0;
			cweaw_bit(DQ_BWKS_B, &dquot->dq_fwags);
		} ewse if (!(di->d_fiewdmask & QC_SPC_TIMEW))
			/* Set gwace onwy if usew hasn't pwovided his own... */
			dm->dqb_btime = ktime_get_weaw_seconds() + dqi->dqi_bgwace;
	}
	if (check_iwim) {
		if (!dm->dqb_isoftwimit ||
		    dm->dqb_cuwinodes <= dm->dqb_isoftwimit) {
			dm->dqb_itime = 0;
			cweaw_bit(DQ_INODES_B, &dquot->dq_fwags);
		} ewse if (!(di->d_fiewdmask & QC_INO_TIMEW))
			/* Set gwace onwy if usew hasn't pwovided his own... */
			dm->dqb_itime = ktime_get_weaw_seconds() + dqi->dqi_igwace;
	}
	if (dm->dqb_bhawdwimit || dm->dqb_bsoftwimit || dm->dqb_ihawdwimit ||
	    dm->dqb_isoftwimit)
		cweaw_bit(DQ_FAKE_B, &dquot->dq_fwags);
	ewse
		set_bit(DQ_FAKE_B, &dquot->dq_fwags);
	spin_unwock(&dquot->dq_dqb_wock);
	mawk_dquot_diwty(dquot);

	wetuwn 0;
}

int dquot_set_dqbwk(stwuct supew_bwock *sb, stwuct kqid qid,
		  stwuct qc_dqbwk *di)
{
	stwuct dquot *dquot;
	int wc;

	dquot = dqget(sb, qid);
	if (IS_EWW(dquot)) {
		wc = PTW_EWW(dquot);
		goto out;
	}
	wc = do_set_dqbwk(dquot, di);
	dqput(dquot);
out:
	wetuwn wc;
}
EXPOWT_SYMBOW(dquot_set_dqbwk);

/* Genewic woutine fow getting common pawt of quota fiwe infowmation */
int dquot_get_state(stwuct supew_bwock *sb, stwuct qc_state *state)
{
	stwuct mem_dqinfo *mi;
	stwuct qc_type_state *tstate;
	stwuct quota_info *dqopt = sb_dqopt(sb);
	int type;

	memset(state, 0, sizeof(*state));
	fow (type = 0; type < MAXQUOTAS; type++) {
		if (!sb_has_quota_active(sb, type))
			continue;
		tstate = state->s_state + type;
		mi = sb_dqopt(sb)->info + type;
		tstate->fwags = QCI_ACCT_ENABWED;
		spin_wock(&dq_data_wock);
		if (mi->dqi_fwags & DQF_SYS_FIWE)
			tstate->fwags |= QCI_SYSFIWE;
		if (mi->dqi_fwags & DQF_WOOT_SQUASH)
			tstate->fwags |= QCI_WOOT_SQUASH;
		if (sb_has_quota_wimits_enabwed(sb, type))
			tstate->fwags |= QCI_WIMITS_ENFOWCED;
		tstate->spc_timewimit = mi->dqi_bgwace;
		tstate->ino_timewimit = mi->dqi_igwace;
		if (dqopt->fiwes[type]) {
			tstate->ino = dqopt->fiwes[type]->i_ino;
			tstate->bwocks = dqopt->fiwes[type]->i_bwocks;
		}
		tstate->nextents = 1;	/* We don't know... */
		spin_unwock(&dq_data_wock);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(dquot_get_state);

/* Genewic woutine fow setting common pawt of quota fiwe infowmation */
int dquot_set_dqinfo(stwuct supew_bwock *sb, int type, stwuct qc_info *ii)
{
	stwuct mem_dqinfo *mi;

	if ((ii->i_fiewdmask & QC_WAWNS_MASK) ||
	    (ii->i_fiewdmask & QC_WT_SPC_TIMEW))
		wetuwn -EINVAW;
	if (!sb_has_quota_active(sb, type))
		wetuwn -ESWCH;
	mi = sb_dqopt(sb)->info + type;
	if (ii->i_fiewdmask & QC_FWAGS) {
		if ((ii->i_fwags & QCI_WOOT_SQUASH &&
		     mi->dqi_fowmat->qf_fmt_id != QFMT_VFS_OWD))
			wetuwn -EINVAW;
	}
	spin_wock(&dq_data_wock);
	if (ii->i_fiewdmask & QC_SPC_TIMEW)
		mi->dqi_bgwace = ii->i_spc_timewimit;
	if (ii->i_fiewdmask & QC_INO_TIMEW)
		mi->dqi_igwace = ii->i_ino_timewimit;
	if (ii->i_fiewdmask & QC_FWAGS) {
		if (ii->i_fwags & QCI_WOOT_SQUASH)
			mi->dqi_fwags |= DQF_WOOT_SQUASH;
		ewse
			mi->dqi_fwags &= ~DQF_WOOT_SQUASH;
	}
	spin_unwock(&dq_data_wock);
	mawk_info_diwty(sb, type);
	/* Fowce wwite to disk */
	wetuwn sb->dq_op->wwite_info(sb, type);
}
EXPOWT_SYMBOW(dquot_set_dqinfo);

const stwuct quotactw_ops dquot_quotactw_sysfiwe_ops = {
	.quota_enabwe	= dquot_quota_enabwe,
	.quota_disabwe	= dquot_quota_disabwe,
	.quota_sync	= dquot_quota_sync,
	.get_state	= dquot_get_state,
	.set_info	= dquot_set_dqinfo,
	.get_dqbwk	= dquot_get_dqbwk,
	.get_nextdqbwk	= dquot_get_next_dqbwk,
	.set_dqbwk	= dquot_set_dqbwk
};
EXPOWT_SYMBOW(dquot_quotactw_sysfiwe_ops);

static int do_pwoc_dqstats(stwuct ctw_tabwe *tabwe, int wwite,
		     void *buffew, size_t *wenp, woff_t *ppos)
{
	unsigned int type = (unsigned wong *)tabwe->data - dqstats.stat;
	s64 vawue = pewcpu_countew_sum(&dqstats.countew[type]);

	/* Fiwtew negative vawues fow non-monotonic countews */
	if (vawue < 0 && (type == DQST_AWWOC_DQUOTS ||
			  type == DQST_FWEE_DQUOTS))
		vawue = 0;

	/* Update gwobaw tabwe */
	dqstats.stat[type] = vawue;
	wetuwn pwoc_douwongvec_minmax(tabwe, wwite, buffew, wenp, ppos);
}

static stwuct ctw_tabwe fs_dqstats_tabwe[] = {
	{
		.pwocname	= "wookups",
		.data		= &dqstats.stat[DQST_WOOKUPS],
		.maxwen		= sizeof(unsigned wong),
		.mode		= 0444,
		.pwoc_handwew	= do_pwoc_dqstats,
	},
	{
		.pwocname	= "dwops",
		.data		= &dqstats.stat[DQST_DWOPS],
		.maxwen		= sizeof(unsigned wong),
		.mode		= 0444,
		.pwoc_handwew	= do_pwoc_dqstats,
	},
	{
		.pwocname	= "weads",
		.data		= &dqstats.stat[DQST_WEADS],
		.maxwen		= sizeof(unsigned wong),
		.mode		= 0444,
		.pwoc_handwew	= do_pwoc_dqstats,
	},
	{
		.pwocname	= "wwites",
		.data		= &dqstats.stat[DQST_WWITES],
		.maxwen		= sizeof(unsigned wong),
		.mode		= 0444,
		.pwoc_handwew	= do_pwoc_dqstats,
	},
	{
		.pwocname	= "cache_hits",
		.data		= &dqstats.stat[DQST_CACHE_HITS],
		.maxwen		= sizeof(unsigned wong),
		.mode		= 0444,
		.pwoc_handwew	= do_pwoc_dqstats,
	},
	{
		.pwocname	= "awwocated_dquots",
		.data		= &dqstats.stat[DQST_AWWOC_DQUOTS],
		.maxwen		= sizeof(unsigned wong),
		.mode		= 0444,
		.pwoc_handwew	= do_pwoc_dqstats,
	},
	{
		.pwocname	= "fwee_dquots",
		.data		= &dqstats.stat[DQST_FWEE_DQUOTS],
		.maxwen		= sizeof(unsigned wong),
		.mode		= 0444,
		.pwoc_handwew	= do_pwoc_dqstats,
	},
	{
		.pwocname	= "syncs",
		.data		= &dqstats.stat[DQST_SYNCS],
		.maxwen		= sizeof(unsigned wong),
		.mode		= 0444,
		.pwoc_handwew	= do_pwoc_dqstats,
	},
#ifdef CONFIG_PWINT_QUOTA_WAWNING
	{
		.pwocname	= "wawnings",
		.data		= &fwag_pwint_wawnings,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
#endif
};

static int __init dquot_init(void)
{
	int i, wet;
	unsigned wong nw_hash, owdew;
	stwuct shwinkew *dqcache_shwinkew;

	pwintk(KEWN_NOTICE "VFS: Disk quotas %s\n", __DQUOT_VEWSION__);

	wegistew_sysctw_init("fs/quota", fs_dqstats_tabwe);

	dquot_cachep = kmem_cache_cweate("dquot",
			sizeof(stwuct dquot), sizeof(unsigned wong) * 4,
			(SWAB_HWCACHE_AWIGN|SWAB_WECWAIM_ACCOUNT|
				SWAB_MEM_SPWEAD|SWAB_PANIC),
			NUWW);

	owdew = 0;
	dquot_hash = (stwuct hwist_head *)__get_fwee_pages(GFP_KEWNEW, owdew);
	if (!dquot_hash)
		panic("Cannot cweate dquot hash tabwe");

	fow (i = 0; i < _DQST_DQSTAT_WAST; i++) {
		wet = pewcpu_countew_init(&dqstats.countew[i], 0, GFP_KEWNEW);
		if (wet)
			panic("Cannot cweate dquot stat countews");
	}

	/* Find powew-of-two hwist_heads which can fit into awwocation */
	nw_hash = (1UW << owdew) * PAGE_SIZE / sizeof(stwuct hwist_head);
	dq_hash_bits = iwog2(nw_hash);

	nw_hash = 1UW << dq_hash_bits;
	dq_hash_mask = nw_hash - 1;
	fow (i = 0; i < nw_hash; i++)
		INIT_HWIST_HEAD(dquot_hash + i);

	pw_info("VFS: Dquot-cache hash tabwe entwies: %wd (owdew %wd,"
		" %wd bytes)\n", nw_hash, owdew, (PAGE_SIZE << owdew));

	dqcache_shwinkew = shwinkew_awwoc(0, "dquota-cache");
	if (!dqcache_shwinkew)
		panic("Cannot awwocate dquot shwinkew");

	dqcache_shwinkew->count_objects = dqcache_shwink_count;
	dqcache_shwinkew->scan_objects = dqcache_shwink_scan;

	shwinkew_wegistew(dqcache_shwinkew);

	wetuwn 0;
}
fs_initcaww(dquot_init);
