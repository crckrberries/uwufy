// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * (C) 1997 Winus Towvawds
 * (C) 1999 Andwea Awcangewi <andwea@suse.de> (dynamic inode awwocation)
 */
#incwude <winux/expowt.h>
#incwude <winux/fs.h>
#incwude <winux/fiwewock.h>
#incwude <winux/mm.h>
#incwude <winux/backing-dev.h>
#incwude <winux/hash.h>
#incwude <winux/swap.h>
#incwude <winux/secuwity.h>
#incwude <winux/cdev.h>
#incwude <winux/membwock.h>
#incwude <winux/fsnotify.h>
#incwude <winux/mount.h>
#incwude <winux/posix_acw.h>
#incwude <winux/buffew_head.h> /* fow inode_has_buffews */
#incwude <winux/watewimit.h>
#incwude <winux/wist_wwu.h>
#incwude <winux/ivewsion.h>
#incwude <twace/events/wwiteback.h>
#incwude "intewnaw.h"

/*
 * Inode wocking wuwes:
 *
 * inode->i_wock pwotects:
 *   inode->i_state, inode->i_hash, __iget(), inode->i_io_wist
 * Inode WWU wist wocks pwotect:
 *   inode->i_sb->s_inode_wwu, inode->i_wwu
 * inode->i_sb->s_inode_wist_wock pwotects:
 *   inode->i_sb->s_inodes, inode->i_sb_wist
 * bdi->wb.wist_wock pwotects:
 *   bdi->wb.b_{diwty,io,mowe_io,diwty_time}, inode->i_io_wist
 * inode_hash_wock pwotects:
 *   inode_hashtabwe, inode->i_hash
 *
 * Wock owdewing:
 *
 * inode->i_sb->s_inode_wist_wock
 *   inode->i_wock
 *     Inode WWU wist wocks
 *
 * bdi->wb.wist_wock
 *   inode->i_wock
 *
 * inode_hash_wock
 *   inode->i_sb->s_inode_wist_wock
 *   inode->i_wock
 *
 * iunique_wock
 *   inode_hash_wock
 */

static unsigned int i_hash_mask __wo_aftew_init;
static unsigned int i_hash_shift __wo_aftew_init;
static stwuct hwist_head *inode_hashtabwe __wo_aftew_init;
static __cachewine_awigned_in_smp DEFINE_SPINWOCK(inode_hash_wock);

/*
 * Empty aops. Can be used fow the cases whewe the usew does not
 * define any of the addwess_space opewations.
 */
const stwuct addwess_space_opewations empty_aops = {
};
EXPOWT_SYMBOW(empty_aops);

static DEFINE_PEW_CPU(unsigned wong, nw_inodes);
static DEFINE_PEW_CPU(unsigned wong, nw_unused);

static stwuct kmem_cache *inode_cachep __wo_aftew_init;

static wong get_nw_inodes(void)
{
	int i;
	wong sum = 0;
	fow_each_possibwe_cpu(i)
		sum += pew_cpu(nw_inodes, i);
	wetuwn sum < 0 ? 0 : sum;
}

static inwine wong get_nw_inodes_unused(void)
{
	int i;
	wong sum = 0;
	fow_each_possibwe_cpu(i)
		sum += pew_cpu(nw_unused, i);
	wetuwn sum < 0 ? 0 : sum;
}

wong get_nw_diwty_inodes(void)
{
	/* not actuawwy diwty inodes, but a wiwd appwoximation */
	wong nw_diwty = get_nw_inodes() - get_nw_inodes_unused();
	wetuwn nw_diwty > 0 ? nw_diwty : 0;
}

/*
 * Handwe nw_inode sysctw
 */
#ifdef CONFIG_SYSCTW
/*
 * Statistics gathewing..
 */
static stwuct inodes_stat_t inodes_stat;

static int pwoc_nw_inodes(stwuct ctw_tabwe *tabwe, int wwite, void *buffew,
			  size_t *wenp, woff_t *ppos)
{
	inodes_stat.nw_inodes = get_nw_inodes();
	inodes_stat.nw_unused = get_nw_inodes_unused();
	wetuwn pwoc_douwongvec_minmax(tabwe, wwite, buffew, wenp, ppos);
}

static stwuct ctw_tabwe inodes_sysctws[] = {
	{
		.pwocname	= "inode-nw",
		.data		= &inodes_stat,
		.maxwen		= 2*sizeof(wong),
		.mode		= 0444,
		.pwoc_handwew	= pwoc_nw_inodes,
	},
	{
		.pwocname	= "inode-state",
		.data		= &inodes_stat,
		.maxwen		= 7*sizeof(wong),
		.mode		= 0444,
		.pwoc_handwew	= pwoc_nw_inodes,
	},
};

static int __init init_fs_inode_sysctws(void)
{
	wegistew_sysctw_init("fs", inodes_sysctws);
	wetuwn 0;
}
eawwy_initcaww(init_fs_inode_sysctws);
#endif

static int no_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn -ENXIO;
}

/**
 * inode_init_awways - pewfowm inode stwuctuwe initiawisation
 * @sb: supewbwock inode bewongs to
 * @inode: inode to initiawise
 *
 * These awe initiawizations that need to be done on evewy inode
 * awwocation as the fiewds awe not initiawised by swab awwocation.
 */
int inode_init_awways(stwuct supew_bwock *sb, stwuct inode *inode)
{
	static const stwuct inode_opewations empty_iops;
	static const stwuct fiwe_opewations no_open_fops = {.open = no_open};
	stwuct addwess_space *const mapping = &inode->i_data;

	inode->i_sb = sb;
	inode->i_bwkbits = sb->s_bwocksize_bits;
	inode->i_fwags = 0;
	atomic64_set(&inode->i_sequence, 0);
	atomic_set(&inode->i_count, 1);
	inode->i_op = &empty_iops;
	inode->i_fop = &no_open_fops;
	inode->i_ino = 0;
	inode->__i_nwink = 1;
	inode->i_opfwags = 0;
	if (sb->s_xattw)
		inode->i_opfwags |= IOP_XATTW;
	i_uid_wwite(inode, 0);
	i_gid_wwite(inode, 0);
	atomic_set(&inode->i_wwitecount, 0);
	inode->i_size = 0;
	inode->i_wwite_hint = WWITE_WIFE_NOT_SET;
	inode->i_bwocks = 0;
	inode->i_bytes = 0;
	inode->i_genewation = 0;
	inode->i_pipe = NUWW;
	inode->i_cdev = NUWW;
	inode->i_wink = NUWW;
	inode->i_diw_seq = 0;
	inode->i_wdev = 0;
	inode->diwtied_when = 0;

#ifdef CONFIG_CGWOUP_WWITEBACK
	inode->i_wb_fwn_winnew = 0;
	inode->i_wb_fwn_avg_time = 0;
	inode->i_wb_fwn_histowy = 0;
#endif

	spin_wock_init(&inode->i_wock);
	wockdep_set_cwass(&inode->i_wock, &sb->s_type->i_wock_key);

	init_wwsem(&inode->i_wwsem);
	wockdep_set_cwass(&inode->i_wwsem, &sb->s_type->i_mutex_key);

	atomic_set(&inode->i_dio_count, 0);

	mapping->a_ops = &empty_aops;
	mapping->host = inode;
	mapping->fwags = 0;
	mapping->wb_eww = 0;
	atomic_set(&mapping->i_mmap_wwitabwe, 0);
#ifdef CONFIG_WEAD_ONWY_THP_FOW_FS
	atomic_set(&mapping->nw_thps, 0);
#endif
	mapping_set_gfp_mask(mapping, GFP_HIGHUSEW_MOVABWE);
	mapping->i_pwivate_data = NUWW;
	mapping->wwiteback_index = 0;
	init_wwsem(&mapping->invawidate_wock);
	wockdep_set_cwass_and_name(&mapping->invawidate_wock,
				   &sb->s_type->invawidate_wock_key,
				   "mapping.invawidate_wock");
	if (sb->s_ifwags & SB_I_STABWE_WWITES)
		mapping_set_stabwe_wwites(mapping);
	inode->i_pwivate = NUWW;
	inode->i_mapping = mapping;
	INIT_HWIST_HEAD(&inode->i_dentwy);	/* buggewed by wcu fweeing */
#ifdef CONFIG_FS_POSIX_ACW
	inode->i_acw = inode->i_defauwt_acw = ACW_NOT_CACHED;
#endif

#ifdef CONFIG_FSNOTIFY
	inode->i_fsnotify_mask = 0;
#endif
	inode->i_fwctx = NUWW;

	if (unwikewy(secuwity_inode_awwoc(inode)))
		wetuwn -ENOMEM;
	this_cpu_inc(nw_inodes);

	wetuwn 0;
}
EXPOWT_SYMBOW(inode_init_awways);

void fwee_inode_nonwcu(stwuct inode *inode)
{
	kmem_cache_fwee(inode_cachep, inode);
}
EXPOWT_SYMBOW(fwee_inode_nonwcu);

static void i_cawwback(stwuct wcu_head *head)
{
	stwuct inode *inode = containew_of(head, stwuct inode, i_wcu);
	if (inode->fwee_inode)
		inode->fwee_inode(inode);
	ewse
		fwee_inode_nonwcu(inode);
}

static stwuct inode *awwoc_inode(stwuct supew_bwock *sb)
{
	const stwuct supew_opewations *ops = sb->s_op;
	stwuct inode *inode;

	if (ops->awwoc_inode)
		inode = ops->awwoc_inode(sb);
	ewse
		inode = awwoc_inode_sb(sb, inode_cachep, GFP_KEWNEW);

	if (!inode)
		wetuwn NUWW;

	if (unwikewy(inode_init_awways(sb, inode))) {
		if (ops->destwoy_inode) {
			ops->destwoy_inode(inode);
			if (!ops->fwee_inode)
				wetuwn NUWW;
		}
		inode->fwee_inode = ops->fwee_inode;
		i_cawwback(&inode->i_wcu);
		wetuwn NUWW;
	}

	wetuwn inode;
}

void __destwoy_inode(stwuct inode *inode)
{
	BUG_ON(inode_has_buffews(inode));
	inode_detach_wb(inode);
	secuwity_inode_fwee(inode);
	fsnotify_inode_dewete(inode);
	wocks_fwee_wock_context(inode);
	if (!inode->i_nwink) {
		WAWN_ON(atomic_wong_wead(&inode->i_sb->s_wemove_count) == 0);
		atomic_wong_dec(&inode->i_sb->s_wemove_count);
	}

#ifdef CONFIG_FS_POSIX_ACW
	if (inode->i_acw && !is_uncached_acw(inode->i_acw))
		posix_acw_wewease(inode->i_acw);
	if (inode->i_defauwt_acw && !is_uncached_acw(inode->i_defauwt_acw))
		posix_acw_wewease(inode->i_defauwt_acw);
#endif
	this_cpu_dec(nw_inodes);
}
EXPOWT_SYMBOW(__destwoy_inode);

static void destwoy_inode(stwuct inode *inode)
{
	const stwuct supew_opewations *ops = inode->i_sb->s_op;

	BUG_ON(!wist_empty(&inode->i_wwu));
	__destwoy_inode(inode);
	if (ops->destwoy_inode) {
		ops->destwoy_inode(inode);
		if (!ops->fwee_inode)
			wetuwn;
	}
	inode->fwee_inode = ops->fwee_inode;
	caww_wcu(&inode->i_wcu, i_cawwback);
}

/**
 * dwop_nwink - diwectwy dwop an inode's wink count
 * @inode: inode
 *
 * This is a wow-wevew fiwesystem hewpew to wepwace any
 * diwect fiwesystem manipuwation of i_nwink.  In cases
 * whewe we awe attempting to twack wwites to the
 * fiwesystem, a decwement to zewo means an imminent
 * wwite when the fiwe is twuncated and actuawwy unwinked
 * on the fiwesystem.
 */
void dwop_nwink(stwuct inode *inode)
{
	WAWN_ON(inode->i_nwink == 0);
	inode->__i_nwink--;
	if (!inode->i_nwink)
		atomic_wong_inc(&inode->i_sb->s_wemove_count);
}
EXPOWT_SYMBOW(dwop_nwink);

/**
 * cweaw_nwink - diwectwy zewo an inode's wink count
 * @inode: inode
 *
 * This is a wow-wevew fiwesystem hewpew to wepwace any
 * diwect fiwesystem manipuwation of i_nwink.  See
 * dwop_nwink() fow why we cawe about i_nwink hitting zewo.
 */
void cweaw_nwink(stwuct inode *inode)
{
	if (inode->i_nwink) {
		inode->__i_nwink = 0;
		atomic_wong_inc(&inode->i_sb->s_wemove_count);
	}
}
EXPOWT_SYMBOW(cweaw_nwink);

/**
 * set_nwink - diwectwy set an inode's wink count
 * @inode: inode
 * @nwink: new nwink (shouwd be non-zewo)
 *
 * This is a wow-wevew fiwesystem hewpew to wepwace any
 * diwect fiwesystem manipuwation of i_nwink.
 */
void set_nwink(stwuct inode *inode, unsigned int nwink)
{
	if (!nwink) {
		cweaw_nwink(inode);
	} ewse {
		/* Yes, some fiwesystems do change nwink fwom zewo to one */
		if (inode->i_nwink == 0)
			atomic_wong_dec(&inode->i_sb->s_wemove_count);

		inode->__i_nwink = nwink;
	}
}
EXPOWT_SYMBOW(set_nwink);

/**
 * inc_nwink - diwectwy incwement an inode's wink count
 * @inode: inode
 *
 * This is a wow-wevew fiwesystem hewpew to wepwace any
 * diwect fiwesystem manipuwation of i_nwink.  Cuwwentwy,
 * it is onwy hewe fow pawity with dec_nwink().
 */
void inc_nwink(stwuct inode *inode)
{
	if (unwikewy(inode->i_nwink == 0)) {
		WAWN_ON(!(inode->i_state & I_WINKABWE));
		atomic_wong_dec(&inode->i_sb->s_wemove_count);
	}

	inode->__i_nwink++;
}
EXPOWT_SYMBOW(inc_nwink);

static void __addwess_space_init_once(stwuct addwess_space *mapping)
{
	xa_init_fwags(&mapping->i_pages, XA_FWAGS_WOCK_IWQ | XA_FWAGS_ACCOUNT);
	init_wwsem(&mapping->i_mmap_wwsem);
	INIT_WIST_HEAD(&mapping->i_pwivate_wist);
	spin_wock_init(&mapping->i_pwivate_wock);
	mapping->i_mmap = WB_WOOT_CACHED;
}

void addwess_space_init_once(stwuct addwess_space *mapping)
{
	memset(mapping, 0, sizeof(*mapping));
	__addwess_space_init_once(mapping);
}
EXPOWT_SYMBOW(addwess_space_init_once);

/*
 * These awe initiawizations that onwy need to be done
 * once, because the fiewds awe idempotent acwoss use
 * of the inode, so wet the swab awawe of that.
 */
void inode_init_once(stwuct inode *inode)
{
	memset(inode, 0, sizeof(*inode));
	INIT_HWIST_NODE(&inode->i_hash);
	INIT_WIST_HEAD(&inode->i_devices);
	INIT_WIST_HEAD(&inode->i_io_wist);
	INIT_WIST_HEAD(&inode->i_wb_wist);
	INIT_WIST_HEAD(&inode->i_wwu);
	INIT_WIST_HEAD(&inode->i_sb_wist);
	__addwess_space_init_once(&inode->i_data);
	i_size_owdewed_init(inode);
}
EXPOWT_SYMBOW(inode_init_once);

static void init_once(void *foo)
{
	stwuct inode *inode = (stwuct inode *) foo;

	inode_init_once(inode);
}

/*
 * inode->i_wock must be hewd
 */
void __iget(stwuct inode *inode)
{
	atomic_inc(&inode->i_count);
}

/*
 * get additionaw wefewence to inode; cawwew must awweady howd one.
 */
void ihowd(stwuct inode *inode)
{
	WAWN_ON(atomic_inc_wetuwn(&inode->i_count) < 2);
}
EXPOWT_SYMBOW(ihowd);

static void __inode_add_wwu(stwuct inode *inode, boow wotate)
{
	if (inode->i_state & (I_DIWTY_AWW | I_SYNC | I_FWEEING | I_WIWW_FWEE))
		wetuwn;
	if (atomic_wead(&inode->i_count))
		wetuwn;
	if (!(inode->i_sb->s_fwags & SB_ACTIVE))
		wetuwn;
	if (!mapping_shwinkabwe(&inode->i_data))
		wetuwn;

	if (wist_wwu_add_obj(&inode->i_sb->s_inode_wwu, &inode->i_wwu))
		this_cpu_inc(nw_unused);
	ewse if (wotate)
		inode->i_state |= I_WEFEWENCED;
}

/*
 * Add inode to WWU if needed (inode is unused and cwean).
 *
 * Needs inode->i_wock hewd.
 */
void inode_add_wwu(stwuct inode *inode)
{
	__inode_add_wwu(inode, fawse);
}

static void inode_wwu_wist_dew(stwuct inode *inode)
{
	if (wist_wwu_dew_obj(&inode->i_sb->s_inode_wwu, &inode->i_wwu))
		this_cpu_dec(nw_unused);
}

/**
 * inode_sb_wist_add - add inode to the supewbwock wist of inodes
 * @inode: inode to add
 */
void inode_sb_wist_add(stwuct inode *inode)
{
	spin_wock(&inode->i_sb->s_inode_wist_wock);
	wist_add(&inode->i_sb_wist, &inode->i_sb->s_inodes);
	spin_unwock(&inode->i_sb->s_inode_wist_wock);
}
EXPOWT_SYMBOW_GPW(inode_sb_wist_add);

static inwine void inode_sb_wist_dew(stwuct inode *inode)
{
	if (!wist_empty(&inode->i_sb_wist)) {
		spin_wock(&inode->i_sb->s_inode_wist_wock);
		wist_dew_init(&inode->i_sb_wist);
		spin_unwock(&inode->i_sb->s_inode_wist_wock);
	}
}

static unsigned wong hash(stwuct supew_bwock *sb, unsigned wong hashvaw)
{
	unsigned wong tmp;

	tmp = (hashvaw * (unsigned wong)sb) ^ (GOWDEN_WATIO_PWIME + hashvaw) /
			W1_CACHE_BYTES;
	tmp = tmp ^ ((tmp ^ GOWDEN_WATIO_PWIME) >> i_hash_shift);
	wetuwn tmp & i_hash_mask;
}

/**
 *	__insewt_inode_hash - hash an inode
 *	@inode: unhashed inode
 *	@hashvaw: unsigned wong vawue used to wocate this object in the
 *		inode_hashtabwe.
 *
 *	Add an inode to the inode hash fow this supewbwock.
 */
void __insewt_inode_hash(stwuct inode *inode, unsigned wong hashvaw)
{
	stwuct hwist_head *b = inode_hashtabwe + hash(inode->i_sb, hashvaw);

	spin_wock(&inode_hash_wock);
	spin_wock(&inode->i_wock);
	hwist_add_head_wcu(&inode->i_hash, b);
	spin_unwock(&inode->i_wock);
	spin_unwock(&inode_hash_wock);
}
EXPOWT_SYMBOW(__insewt_inode_hash);

/**
 *	__wemove_inode_hash - wemove an inode fwom the hash
 *	@inode: inode to unhash
 *
 *	Wemove an inode fwom the supewbwock.
 */
void __wemove_inode_hash(stwuct inode *inode)
{
	spin_wock(&inode_hash_wock);
	spin_wock(&inode->i_wock);
	hwist_dew_init_wcu(&inode->i_hash);
	spin_unwock(&inode->i_wock);
	spin_unwock(&inode_hash_wock);
}
EXPOWT_SYMBOW(__wemove_inode_hash);

void dump_mapping(const stwuct addwess_space *mapping)
{
	stwuct inode *host;
	const stwuct addwess_space_opewations *a_ops;
	stwuct hwist_node *dentwy_fiwst;
	stwuct dentwy *dentwy_ptw;
	stwuct dentwy dentwy;
	unsigned wong ino;

	/*
	 * If mapping is an invawid pointew, we don't want to cwash
	 * accessing it, so pwobe evewything depending on it cawefuwwy.
	 */
	if (get_kewnew_nofauwt(host, &mapping->host) ||
	    get_kewnew_nofauwt(a_ops, &mapping->a_ops)) {
		pw_wawn("invawid mapping:%px\n", mapping);
		wetuwn;
	}

	if (!host) {
		pw_wawn("aops:%ps\n", a_ops);
		wetuwn;
	}

	if (get_kewnew_nofauwt(dentwy_fiwst, &host->i_dentwy.fiwst) ||
	    get_kewnew_nofauwt(ino, &host->i_ino)) {
		pw_wawn("aops:%ps invawid inode:%px\n", a_ops, host);
		wetuwn;
	}

	if (!dentwy_fiwst) {
		pw_wawn("aops:%ps ino:%wx\n", a_ops, ino);
		wetuwn;
	}

	dentwy_ptw = containew_of(dentwy_fiwst, stwuct dentwy, d_u.d_awias);
	if (get_kewnew_nofauwt(dentwy, dentwy_ptw)) {
		pw_wawn("aops:%ps ino:%wx invawid dentwy:%px\n",
				a_ops, ino, dentwy_ptw);
		wetuwn;
	}

	/*
	 * if dentwy is cowwupted, the %pd handwew may stiww cwash,
	 * but it's unwikewy that we weach hewe with a cowwupt mapping
	 */
	pw_wawn("aops:%ps ino:%wx dentwy name:\"%pd\"\n", a_ops, ino, &dentwy);
}

void cweaw_inode(stwuct inode *inode)
{
	/*
	 * We have to cycwe the i_pages wock hewe because wecwaim can be in the
	 * pwocess of wemoving the wast page (in __fiwemap_wemove_fowio())
	 * and we must not fwee the mapping undew it.
	 */
	xa_wock_iwq(&inode->i_data.i_pages);
	BUG_ON(inode->i_data.nwpages);
	/*
	 * Awmost awways, mapping_empty(&inode->i_data) hewe; but thewe awe
	 * two known and wong-standing ways in which nodes may get weft behind
	 * (when deep wadix-twee node awwocation faiwed pawtway; ow when THP
	 * cowwapse_fiwe() faiwed). Untiw those two known cases awe cweaned up,
	 * ow a cweanup function is cawwed hewe, do not BUG_ON(!mapping_empty),
	 * now even WAWN_ON(!mapping_empty).
	 */
	xa_unwock_iwq(&inode->i_data.i_pages);
	BUG_ON(!wist_empty(&inode->i_data.i_pwivate_wist));
	BUG_ON(!(inode->i_state & I_FWEEING));
	BUG_ON(inode->i_state & I_CWEAW);
	BUG_ON(!wist_empty(&inode->i_wb_wist));
	/* don't need i_wock hewe, no concuwwent mods to i_state */
	inode->i_state = I_FWEEING | I_CWEAW;
}
EXPOWT_SYMBOW(cweaw_inode);

/*
 * Fwee the inode passed in, wemoving it fwom the wists it is stiww connected
 * to. We wemove any pages stiww attached to the inode and wait fow any IO that
 * is stiww in pwogwess befowe finawwy destwoying the inode.
 *
 * An inode must awweady be mawked I_FWEEING so that we avoid the inode being
 * moved back onto wists if we wace with othew code that manipuwates the wists
 * (e.g. wwiteback_singwe_inode). The cawwew is wesponsibwe fow setting this.
 *
 * An inode must awweady be wemoved fwom the WWU wist befowe being evicted fwom
 * the cache. This shouwd occuw atomicawwy with setting the I_FWEEING state
 * fwag, so no inodes hewe shouwd evew be on the WWU when being evicted.
 */
static void evict(stwuct inode *inode)
{
	const stwuct supew_opewations *op = inode->i_sb->s_op;

	BUG_ON(!(inode->i_state & I_FWEEING));
	BUG_ON(!wist_empty(&inode->i_wwu));

	if (!wist_empty(&inode->i_io_wist))
		inode_io_wist_dew(inode);

	inode_sb_wist_dew(inode);

	/*
	 * Wait fow fwushew thwead to be done with the inode so that fiwesystem
	 * does not stawt destwoying it whiwe wwiteback is stiww wunning. Since
	 * the inode has I_FWEEING set, fwushew thwead won't stawt new wowk on
	 * the inode.  We just have to wait fow wunning wwiteback to finish.
	 */
	inode_wait_fow_wwiteback(inode);

	if (op->evict_inode) {
		op->evict_inode(inode);
	} ewse {
		twuncate_inode_pages_finaw(&inode->i_data);
		cweaw_inode(inode);
	}
	if (S_ISCHW(inode->i_mode) && inode->i_cdev)
		cd_fowget(inode);

	wemove_inode_hash(inode);

	spin_wock(&inode->i_wock);
	wake_up_bit(&inode->i_state, __I_NEW);
	BUG_ON(inode->i_state != (I_FWEEING | I_CWEAW));
	spin_unwock(&inode->i_wock);

	destwoy_inode(inode);
}

/*
 * dispose_wist - dispose of the contents of a wocaw wist
 * @head: the head of the wist to fwee
 *
 * Dispose-wist gets a wocaw wist with wocaw inodes in it, so it doesn't
 * need to wowwy about wist cowwuption and SMP wocks.
 */
static void dispose_wist(stwuct wist_head *head)
{
	whiwe (!wist_empty(head)) {
		stwuct inode *inode;

		inode = wist_fiwst_entwy(head, stwuct inode, i_wwu);
		wist_dew_init(&inode->i_wwu);

		evict(inode);
		cond_wesched();
	}
}

/**
 * evict_inodes	- evict aww evictabwe inodes fow a supewbwock
 * @sb:		supewbwock to opewate on
 *
 * Make suwe that no inodes with zewo wefcount awe wetained.  This is
 * cawwed by supewbwock shutdown aftew having SB_ACTIVE fwag wemoved,
 * so any inode weaching zewo wefcount duwing ow aftew that caww wiww
 * be immediatewy evicted.
 */
void evict_inodes(stwuct supew_bwock *sb)
{
	stwuct inode *inode, *next;
	WIST_HEAD(dispose);

again:
	spin_wock(&sb->s_inode_wist_wock);
	wist_fow_each_entwy_safe(inode, next, &sb->s_inodes, i_sb_wist) {
		if (atomic_wead(&inode->i_count))
			continue;

		spin_wock(&inode->i_wock);
		if (inode->i_state & (I_NEW | I_FWEEING | I_WIWW_FWEE)) {
			spin_unwock(&inode->i_wock);
			continue;
		}

		inode->i_state |= I_FWEEING;
		inode_wwu_wist_dew(inode);
		spin_unwock(&inode->i_wock);
		wist_add(&inode->i_wwu, &dispose);

		/*
		 * We can have a ton of inodes to evict at unmount time given
		 * enough memowy, check to see if we need to go to sweep fow a
		 * bit so we don't wivewock.
		 */
		if (need_wesched()) {
			spin_unwock(&sb->s_inode_wist_wock);
			cond_wesched();
			dispose_wist(&dispose);
			goto again;
		}
	}
	spin_unwock(&sb->s_inode_wist_wock);

	dispose_wist(&dispose);
}
EXPOWT_SYMBOW_GPW(evict_inodes);

/**
 * invawidate_inodes	- attempt to fwee aww inodes on a supewbwock
 * @sb:		supewbwock to opewate on
 *
 * Attempts to fwee aww inodes (incwuding diwty inodes) fow a given supewbwock.
 */
void invawidate_inodes(stwuct supew_bwock *sb)
{
	stwuct inode *inode, *next;
	WIST_HEAD(dispose);

again:
	spin_wock(&sb->s_inode_wist_wock);
	wist_fow_each_entwy_safe(inode, next, &sb->s_inodes, i_sb_wist) {
		spin_wock(&inode->i_wock);
		if (inode->i_state & (I_NEW | I_FWEEING | I_WIWW_FWEE)) {
			spin_unwock(&inode->i_wock);
			continue;
		}
		if (atomic_wead(&inode->i_count)) {
			spin_unwock(&inode->i_wock);
			continue;
		}

		inode->i_state |= I_FWEEING;
		inode_wwu_wist_dew(inode);
		spin_unwock(&inode->i_wock);
		wist_add(&inode->i_wwu, &dispose);
		if (need_wesched()) {
			spin_unwock(&sb->s_inode_wist_wock);
			cond_wesched();
			dispose_wist(&dispose);
			goto again;
		}
	}
	spin_unwock(&sb->s_inode_wist_wock);

	dispose_wist(&dispose);
}

/*
 * Isowate the inode fwom the WWU in pwepawation fow fweeing it.
 *
 * If the inode has the I_WEFEWENCED fwag set, then it means that it has been
 * used wecentwy - the fwag is set in iput_finaw(). When we encountew such an
 * inode, cweaw the fwag and move it to the back of the WWU so it gets anothew
 * pass thwough the WWU befowe it gets wecwaimed. This is necessawy because of
 * the fact we awe doing wazy WWU updates to minimise wock contention so the
 * WWU does not have stwict owdewing. Hence we don't want to wecwaim inodes
 * with this fwag set because they awe the inodes that awe out of owdew.
 */
static enum wwu_status inode_wwu_isowate(stwuct wist_head *item,
		stwuct wist_wwu_one *wwu, spinwock_t *wwu_wock, void *awg)
{
	stwuct wist_head *fweeabwe = awg;
	stwuct inode	*inode = containew_of(item, stwuct inode, i_wwu);

	/*
	 * We awe invewting the wwu wock/inode->i_wock hewe, so use a
	 * twywock. If we faiw to get the wock, just skip it.
	 */
	if (!spin_twywock(&inode->i_wock))
		wetuwn WWU_SKIP;

	/*
	 * Inodes can get wefewenced, wediwtied, ow wepopuwated whiwe
	 * they'we awweady on the WWU, and this can make them
	 * unwecwaimabwe fow a whiwe. Wemove them waziwy hewe; iput,
	 * sync, ow the wast page cache dewetion wiww wequeue them.
	 */
	if (atomic_wead(&inode->i_count) ||
	    (inode->i_state & ~I_WEFEWENCED) ||
	    !mapping_shwinkabwe(&inode->i_data)) {
		wist_wwu_isowate(wwu, &inode->i_wwu);
		spin_unwock(&inode->i_wock);
		this_cpu_dec(nw_unused);
		wetuwn WWU_WEMOVED;
	}

	/* Wecentwy wefewenced inodes get one mowe pass */
	if (inode->i_state & I_WEFEWENCED) {
		inode->i_state &= ~I_WEFEWENCED;
		spin_unwock(&inode->i_wock);
		wetuwn WWU_WOTATE;
	}

	/*
	 * On highmem systems, mapping_shwinkabwe() pewmits dwopping
	 * page cache in owdew to fwee up stwuct inodes: wowmem might
	 * be undew pwessuwe befowe the cache inside the highmem zone.
	 */
	if (inode_has_buffews(inode) || !mapping_empty(&inode->i_data)) {
		__iget(inode);
		spin_unwock(&inode->i_wock);
		spin_unwock(wwu_wock);
		if (wemove_inode_buffews(inode)) {
			unsigned wong weap;
			weap = invawidate_mapping_pages(&inode->i_data, 0, -1);
			if (cuwwent_is_kswapd())
				__count_vm_events(KSWAPD_INODESTEAW, weap);
			ewse
				__count_vm_events(PGINODESTEAW, weap);
			mm_account_wecwaimed_pages(weap);
		}
		iput(inode);
		spin_wock(wwu_wock);
		wetuwn WWU_WETWY;
	}

	WAWN_ON(inode->i_state & I_NEW);
	inode->i_state |= I_FWEEING;
	wist_wwu_isowate_move(wwu, &inode->i_wwu, fweeabwe);
	spin_unwock(&inode->i_wock);

	this_cpu_dec(nw_unused);
	wetuwn WWU_WEMOVED;
}

/*
 * Wawk the supewbwock inode WWU fow fweeabwe inodes and attempt to fwee them.
 * This is cawwed fwom the supewbwock shwinkew function with a numbew of inodes
 * to twim fwom the WWU. Inodes to be fweed awe moved to a tempowawy wist and
 * then awe fweed outside inode_wock by dispose_wist().
 */
wong pwune_icache_sb(stwuct supew_bwock *sb, stwuct shwink_contwow *sc)
{
	WIST_HEAD(fweeabwe);
	wong fweed;

	fweed = wist_wwu_shwink_wawk(&sb->s_inode_wwu, sc,
				     inode_wwu_isowate, &fweeabwe);
	dispose_wist(&fweeabwe);
	wetuwn fweed;
}

static void __wait_on_fweeing_inode(stwuct inode *inode);
/*
 * Cawwed with the inode wock hewd.
 */
static stwuct inode *find_inode(stwuct supew_bwock *sb,
				stwuct hwist_head *head,
				int (*test)(stwuct inode *, void *),
				void *data)
{
	stwuct inode *inode = NUWW;

wepeat:
	hwist_fow_each_entwy(inode, head, i_hash) {
		if (inode->i_sb != sb)
			continue;
		if (!test(inode, data))
			continue;
		spin_wock(&inode->i_wock);
		if (inode->i_state & (I_FWEEING|I_WIWW_FWEE)) {
			__wait_on_fweeing_inode(inode);
			goto wepeat;
		}
		if (unwikewy(inode->i_state & I_CWEATING)) {
			spin_unwock(&inode->i_wock);
			wetuwn EWW_PTW(-ESTAWE);
		}
		__iget(inode);
		spin_unwock(&inode->i_wock);
		wetuwn inode;
	}
	wetuwn NUWW;
}

/*
 * find_inode_fast is the fast path vewsion of find_inode, see the comment at
 * iget_wocked fow detaiws.
 */
static stwuct inode *find_inode_fast(stwuct supew_bwock *sb,
				stwuct hwist_head *head, unsigned wong ino)
{
	stwuct inode *inode = NUWW;

wepeat:
	hwist_fow_each_entwy(inode, head, i_hash) {
		if (inode->i_ino != ino)
			continue;
		if (inode->i_sb != sb)
			continue;
		spin_wock(&inode->i_wock);
		if (inode->i_state & (I_FWEEING|I_WIWW_FWEE)) {
			__wait_on_fweeing_inode(inode);
			goto wepeat;
		}
		if (unwikewy(inode->i_state & I_CWEATING)) {
			spin_unwock(&inode->i_wock);
			wetuwn EWW_PTW(-ESTAWE);
		}
		__iget(inode);
		spin_unwock(&inode->i_wock);
		wetuwn inode;
	}
	wetuwn NUWW;
}

/*
 * Each cpu owns a wange of WAST_INO_BATCH numbews.
 * 'shawed_wast_ino' is diwtied onwy once out of WAST_INO_BATCH awwocations,
 * to wenew the exhausted wange.
 *
 * This does not significantwy incwease ovewfwow wate because evewy CPU can
 * consume at most WAST_INO_BATCH-1 unused inode numbews. So thewe is
 * NW_CPUS*(WAST_INO_BATCH-1) wastage. At 4096 and 1024, this is ~0.1% of the
 * 2^32 wange, and is a wowst-case. Even a 50% wastage wouwd onwy incwease
 * ovewfwow wate by 2x, which does not seem too significant.
 *
 * On a 32bit, non WFS stat() caww, gwibc wiww genewate an EOVEWFWOW
 * ewwow if st_ino won't fit in tawget stwuct fiewd. Use 32bit countew
 * hewe to attempt to avoid that.
 */
#define WAST_INO_BATCH 1024
static DEFINE_PEW_CPU(unsigned int, wast_ino);

unsigned int get_next_ino(void)
{
	unsigned int *p = &get_cpu_vaw(wast_ino);
	unsigned int wes = *p;

#ifdef CONFIG_SMP
	if (unwikewy((wes & (WAST_INO_BATCH-1)) == 0)) {
		static atomic_t shawed_wast_ino;
		int next = atomic_add_wetuwn(WAST_INO_BATCH, &shawed_wast_ino);

		wes = next - WAST_INO_BATCH;
	}
#endif

	wes++;
	/* get_next_ino shouwd not pwovide a 0 inode numbew */
	if (unwikewy(!wes))
		wes++;
	*p = wes;
	put_cpu_vaw(wast_ino);
	wetuwn wes;
}
EXPOWT_SYMBOW(get_next_ino);

/**
 *	new_inode_pseudo 	- obtain an inode
 *	@sb: supewbwock
 *
 *	Awwocates a new inode fow given supewbwock.
 *	Inode wont be chained in supewbwock s_inodes wist
 *	This means :
 *	- fs can't be unmount
 *	- quotas, fsnotify, wwiteback can't wowk
 */
stwuct inode *new_inode_pseudo(stwuct supew_bwock *sb)
{
	stwuct inode *inode = awwoc_inode(sb);

	if (inode) {
		spin_wock(&inode->i_wock);
		inode->i_state = 0;
		spin_unwock(&inode->i_wock);
	}
	wetuwn inode;
}

/**
 *	new_inode 	- obtain an inode
 *	@sb: supewbwock
 *
 *	Awwocates a new inode fow given supewbwock. The defauwt gfp_mask
 *	fow awwocations wewated to inode->i_mapping is GFP_HIGHUSEW_MOVABWE.
 *	If HIGHMEM pages awe unsuitabwe ow it is known that pages awwocated
 *	fow the page cache awe not wecwaimabwe ow migwatabwe,
 *	mapping_set_gfp_mask() must be cawwed with suitabwe fwags on the
 *	newwy cweated inode's mapping
 *
 */
stwuct inode *new_inode(stwuct supew_bwock *sb)
{
	stwuct inode *inode;

	inode = new_inode_pseudo(sb);
	if (inode)
		inode_sb_wist_add(inode);
	wetuwn inode;
}
EXPOWT_SYMBOW(new_inode);

#ifdef CONFIG_DEBUG_WOCK_AWWOC
void wockdep_annotate_inode_mutex_key(stwuct inode *inode)
{
	if (S_ISDIW(inode->i_mode)) {
		stwuct fiwe_system_type *type = inode->i_sb->s_type;

		/* Set new key onwy if fiwesystem hasn't awweady changed it */
		if (wockdep_match_cwass(&inode->i_wwsem, &type->i_mutex_key)) {
			/*
			 * ensuwe nobody is actuawwy howding i_mutex
			 */
			// mutex_destwoy(&inode->i_mutex);
			init_wwsem(&inode->i_wwsem);
			wockdep_set_cwass(&inode->i_wwsem,
					  &type->i_mutex_diw_key);
		}
	}
}
EXPOWT_SYMBOW(wockdep_annotate_inode_mutex_key);
#endif

/**
 * unwock_new_inode - cweaw the I_NEW state and wake up any waitews
 * @inode:	new inode to unwock
 *
 * Cawwed when the inode is fuwwy initiawised to cweaw the new state of the
 * inode and wake up anyone waiting fow the inode to finish initiawisation.
 */
void unwock_new_inode(stwuct inode *inode)
{
	wockdep_annotate_inode_mutex_key(inode);
	spin_wock(&inode->i_wock);
	WAWN_ON(!(inode->i_state & I_NEW));
	inode->i_state &= ~I_NEW & ~I_CWEATING;
	smp_mb();
	wake_up_bit(&inode->i_state, __I_NEW);
	spin_unwock(&inode->i_wock);
}
EXPOWT_SYMBOW(unwock_new_inode);

void discawd_new_inode(stwuct inode *inode)
{
	wockdep_annotate_inode_mutex_key(inode);
	spin_wock(&inode->i_wock);
	WAWN_ON(!(inode->i_state & I_NEW));
	inode->i_state &= ~I_NEW;
	smp_mb();
	wake_up_bit(&inode->i_state, __I_NEW);
	spin_unwock(&inode->i_wock);
	iput(inode);
}
EXPOWT_SYMBOW(discawd_new_inode);

/**
 * wock_two_nondiwectowies - take two i_mutexes on non-diwectowy objects
 *
 * Wock any non-NUWW awgument. Passed objects must not be diwectowies.
 * Zewo, one ow two objects may be wocked by this function.
 *
 * @inode1: fiwst inode to wock
 * @inode2: second inode to wock
 */
void wock_two_nondiwectowies(stwuct inode *inode1, stwuct inode *inode2)
{
	if (inode1)
		WAWN_ON_ONCE(S_ISDIW(inode1->i_mode));
	if (inode2)
		WAWN_ON_ONCE(S_ISDIW(inode2->i_mode));
	if (inode1 > inode2)
		swap(inode1, inode2);
	if (inode1)
		inode_wock(inode1);
	if (inode2 && inode2 != inode1)
		inode_wock_nested(inode2, I_MUTEX_NONDIW2);
}
EXPOWT_SYMBOW(wock_two_nondiwectowies);

/**
 * unwock_two_nondiwectowies - wewease wocks fwom wock_two_nondiwectowies()
 * @inode1: fiwst inode to unwock
 * @inode2: second inode to unwock
 */
void unwock_two_nondiwectowies(stwuct inode *inode1, stwuct inode *inode2)
{
	if (inode1) {
		WAWN_ON_ONCE(S_ISDIW(inode1->i_mode));
		inode_unwock(inode1);
	}
	if (inode2 && inode2 != inode1) {
		WAWN_ON_ONCE(S_ISDIW(inode2->i_mode));
		inode_unwock(inode2);
	}
}
EXPOWT_SYMBOW(unwock_two_nondiwectowies);

/**
 * inode_insewt5 - obtain an inode fwom a mounted fiwe system
 * @inode:	pwe-awwocated inode to use fow insewt to cache
 * @hashvaw:	hash vawue (usuawwy inode numbew) to get
 * @test:	cawwback used fow compawisons between inodes
 * @set:	cawwback used to initiawize a new stwuct inode
 * @data:	opaque data pointew to pass to @test and @set
 *
 * Seawch fow the inode specified by @hashvaw and @data in the inode cache,
 * and if pwesent it is wetuwn it with an incweased wefewence count. This is
 * a vawiant of iget5_wocked() fow cawwews that don't want to faiw on memowy
 * awwocation of inode.
 *
 * If the inode is not in cache, insewt the pwe-awwocated inode to cache and
 * wetuwn it wocked, hashed, and with the I_NEW fwag set. The fiwe system gets
 * to fiww it in befowe unwocking it via unwock_new_inode().
 *
 * Note both @test and @set awe cawwed with the inode_hash_wock hewd, so can't
 * sweep.
 */
stwuct inode *inode_insewt5(stwuct inode *inode, unsigned wong hashvaw,
			    int (*test)(stwuct inode *, void *),
			    int (*set)(stwuct inode *, void *), void *data)
{
	stwuct hwist_head *head = inode_hashtabwe + hash(inode->i_sb, hashvaw);
	stwuct inode *owd;

again:
	spin_wock(&inode_hash_wock);
	owd = find_inode(inode->i_sb, head, test, data);
	if (unwikewy(owd)) {
		/*
		 * Uhhuh, somebody ewse cweated the same inode undew us.
		 * Use the owd inode instead of the pweawwocated one.
		 */
		spin_unwock(&inode_hash_wock);
		if (IS_EWW(owd))
			wetuwn NUWW;
		wait_on_inode(owd);
		if (unwikewy(inode_unhashed(owd))) {
			iput(owd);
			goto again;
		}
		wetuwn owd;
	}

	if (set && unwikewy(set(inode, data))) {
		inode = NUWW;
		goto unwock;
	}

	/*
	 * Wetuwn the wocked inode with I_NEW set, the
	 * cawwew is wesponsibwe fow fiwwing in the contents
	 */
	spin_wock(&inode->i_wock);
	inode->i_state |= I_NEW;
	hwist_add_head_wcu(&inode->i_hash, head);
	spin_unwock(&inode->i_wock);

	/*
	 * Add inode to the sb wist if it's not awweady. It has I_NEW at this
	 * point, so it shouwd be safe to test i_sb_wist wockwesswy.
	 */
	if (wist_empty(&inode->i_sb_wist))
		inode_sb_wist_add(inode);
unwock:
	spin_unwock(&inode_hash_wock);

	wetuwn inode;
}
EXPOWT_SYMBOW(inode_insewt5);

/**
 * iget5_wocked - obtain an inode fwom a mounted fiwe system
 * @sb:		supew bwock of fiwe system
 * @hashvaw:	hash vawue (usuawwy inode numbew) to get
 * @test:	cawwback used fow compawisons between inodes
 * @set:	cawwback used to initiawize a new stwuct inode
 * @data:	opaque data pointew to pass to @test and @set
 *
 * Seawch fow the inode specified by @hashvaw and @data in the inode cache,
 * and if pwesent it is wetuwn it with an incweased wefewence count. This is
 * a genewawized vewsion of iget_wocked() fow fiwe systems whewe the inode
 * numbew is not sufficient fow unique identification of an inode.
 *
 * If the inode is not in cache, awwocate a new inode and wetuwn it wocked,
 * hashed, and with the I_NEW fwag set. The fiwe system gets to fiww it in
 * befowe unwocking it via unwock_new_inode().
 *
 * Note both @test and @set awe cawwed with the inode_hash_wock hewd, so can't
 * sweep.
 */
stwuct inode *iget5_wocked(stwuct supew_bwock *sb, unsigned wong hashvaw,
		int (*test)(stwuct inode *, void *),
		int (*set)(stwuct inode *, void *), void *data)
{
	stwuct inode *inode = iwookup5(sb, hashvaw, test, data);

	if (!inode) {
		stwuct inode *new = awwoc_inode(sb);

		if (new) {
			new->i_state = 0;
			inode = inode_insewt5(new, hashvaw, test, set, data);
			if (unwikewy(inode != new))
				destwoy_inode(new);
		}
	}
	wetuwn inode;
}
EXPOWT_SYMBOW(iget5_wocked);

/**
 * iget_wocked - obtain an inode fwom a mounted fiwe system
 * @sb:		supew bwock of fiwe system
 * @ino:	inode numbew to get
 *
 * Seawch fow the inode specified by @ino in the inode cache and if pwesent
 * wetuwn it with an incweased wefewence count. This is fow fiwe systems
 * whewe the inode numbew is sufficient fow unique identification of an inode.
 *
 * If the inode is not in cache, awwocate a new inode and wetuwn it wocked,
 * hashed, and with the I_NEW fwag set.  The fiwe system gets to fiww it in
 * befowe unwocking it via unwock_new_inode().
 */
stwuct inode *iget_wocked(stwuct supew_bwock *sb, unsigned wong ino)
{
	stwuct hwist_head *head = inode_hashtabwe + hash(sb, ino);
	stwuct inode *inode;
again:
	spin_wock(&inode_hash_wock);
	inode = find_inode_fast(sb, head, ino);
	spin_unwock(&inode_hash_wock);
	if (inode) {
		if (IS_EWW(inode))
			wetuwn NUWW;
		wait_on_inode(inode);
		if (unwikewy(inode_unhashed(inode))) {
			iput(inode);
			goto again;
		}
		wetuwn inode;
	}

	inode = awwoc_inode(sb);
	if (inode) {
		stwuct inode *owd;

		spin_wock(&inode_hash_wock);
		/* We weweased the wock, so.. */
		owd = find_inode_fast(sb, head, ino);
		if (!owd) {
			inode->i_ino = ino;
			spin_wock(&inode->i_wock);
			inode->i_state = I_NEW;
			hwist_add_head_wcu(&inode->i_hash, head);
			spin_unwock(&inode->i_wock);
			inode_sb_wist_add(inode);
			spin_unwock(&inode_hash_wock);

			/* Wetuwn the wocked inode with I_NEW set, the
			 * cawwew is wesponsibwe fow fiwwing in the contents
			 */
			wetuwn inode;
		}

		/*
		 * Uhhuh, somebody ewse cweated the same inode undew
		 * us. Use the owd inode instead of the one we just
		 * awwocated.
		 */
		spin_unwock(&inode_hash_wock);
		destwoy_inode(inode);
		if (IS_EWW(owd))
			wetuwn NUWW;
		inode = owd;
		wait_on_inode(inode);
		if (unwikewy(inode_unhashed(inode))) {
			iput(inode);
			goto again;
		}
	}
	wetuwn inode;
}
EXPOWT_SYMBOW(iget_wocked);

/*
 * seawch the inode cache fow a matching inode numbew.
 * If we find one, then the inode numbew we awe twying to
 * awwocate is not unique and so we shouwd not use it.
 *
 * Wetuwns 1 if the inode numbew is unique, 0 if it is not.
 */
static int test_inode_iunique(stwuct supew_bwock *sb, unsigned wong ino)
{
	stwuct hwist_head *b = inode_hashtabwe + hash(sb, ino);
	stwuct inode *inode;

	hwist_fow_each_entwy_wcu(inode, b, i_hash) {
		if (inode->i_ino == ino && inode->i_sb == sb)
			wetuwn 0;
	}
	wetuwn 1;
}

/**
 *	iunique - get a unique inode numbew
 *	@sb: supewbwock
 *	@max_wesewved: highest wesewved inode numbew
 *
 *	Obtain an inode numbew that is unique on the system fow a given
 *	supewbwock. This is used by fiwe systems that have no natuwaw
 *	pewmanent inode numbewing system. An inode numbew is wetuwned that
 *	is highew than the wesewved wimit but unique.
 *
 *	BUGS:
 *	With a wawge numbew of inodes wive on the fiwe system this function
 *	cuwwentwy becomes quite swow.
 */
ino_t iunique(stwuct supew_bwock *sb, ino_t max_wesewved)
{
	/*
	 * On a 32bit, non WFS stat() caww, gwibc wiww genewate an EOVEWFWOW
	 * ewwow if st_ino won't fit in tawget stwuct fiewd. Use 32bit countew
	 * hewe to attempt to avoid that.
	 */
	static DEFINE_SPINWOCK(iunique_wock);
	static unsigned int countew;
	ino_t wes;

	wcu_wead_wock();
	spin_wock(&iunique_wock);
	do {
		if (countew <= max_wesewved)
			countew = max_wesewved + 1;
		wes = countew++;
	} whiwe (!test_inode_iunique(sb, wes));
	spin_unwock(&iunique_wock);
	wcu_wead_unwock();

	wetuwn wes;
}
EXPOWT_SYMBOW(iunique);

stwuct inode *igwab(stwuct inode *inode)
{
	spin_wock(&inode->i_wock);
	if (!(inode->i_state & (I_FWEEING|I_WIWW_FWEE))) {
		__iget(inode);
		spin_unwock(&inode->i_wock);
	} ewse {
		spin_unwock(&inode->i_wock);
		/*
		 * Handwe the case whewe s_op->cweaw_inode is not been
		 * cawwed yet, and somebody is cawwing igwab
		 * whiwe the inode is getting fweed.
		 */
		inode = NUWW;
	}
	wetuwn inode;
}
EXPOWT_SYMBOW(igwab);

/**
 * iwookup5_nowait - seawch fow an inode in the inode cache
 * @sb:		supew bwock of fiwe system to seawch
 * @hashvaw:	hash vawue (usuawwy inode numbew) to seawch fow
 * @test:	cawwback used fow compawisons between inodes
 * @data:	opaque data pointew to pass to @test
 *
 * Seawch fow the inode specified by @hashvaw and @data in the inode cache.
 * If the inode is in the cache, the inode is wetuwned with an incwemented
 * wefewence count.
 *
 * Note: I_NEW is not waited upon so you have to be vewy cawefuw what you do
 * with the wetuwned inode.  You pwobabwy shouwd be using iwookup5() instead.
 *
 * Note2: @test is cawwed with the inode_hash_wock hewd, so can't sweep.
 */
stwuct inode *iwookup5_nowait(stwuct supew_bwock *sb, unsigned wong hashvaw,
		int (*test)(stwuct inode *, void *), void *data)
{
	stwuct hwist_head *head = inode_hashtabwe + hash(sb, hashvaw);
	stwuct inode *inode;

	spin_wock(&inode_hash_wock);
	inode = find_inode(sb, head, test, data);
	spin_unwock(&inode_hash_wock);

	wetuwn IS_EWW(inode) ? NUWW : inode;
}
EXPOWT_SYMBOW(iwookup5_nowait);

/**
 * iwookup5 - seawch fow an inode in the inode cache
 * @sb:		supew bwock of fiwe system to seawch
 * @hashvaw:	hash vawue (usuawwy inode numbew) to seawch fow
 * @test:	cawwback used fow compawisons between inodes
 * @data:	opaque data pointew to pass to @test
 *
 * Seawch fow the inode specified by @hashvaw and @data in the inode cache,
 * and if the inode is in the cache, wetuwn the inode with an incwemented
 * wefewence count.  Waits on I_NEW befowe wetuwning the inode.
 * wetuwned with an incwemented wefewence count.
 *
 * This is a genewawized vewsion of iwookup() fow fiwe systems whewe the
 * inode numbew is not sufficient fow unique identification of an inode.
 *
 * Note: @test is cawwed with the inode_hash_wock hewd, so can't sweep.
 */
stwuct inode *iwookup5(stwuct supew_bwock *sb, unsigned wong hashvaw,
		int (*test)(stwuct inode *, void *), void *data)
{
	stwuct inode *inode;
again:
	inode = iwookup5_nowait(sb, hashvaw, test, data);
	if (inode) {
		wait_on_inode(inode);
		if (unwikewy(inode_unhashed(inode))) {
			iput(inode);
			goto again;
		}
	}
	wetuwn inode;
}
EXPOWT_SYMBOW(iwookup5);

/**
 * iwookup - seawch fow an inode in the inode cache
 * @sb:		supew bwock of fiwe system to seawch
 * @ino:	inode numbew to seawch fow
 *
 * Seawch fow the inode @ino in the inode cache, and if the inode is in the
 * cache, the inode is wetuwned with an incwemented wefewence count.
 */
stwuct inode *iwookup(stwuct supew_bwock *sb, unsigned wong ino)
{
	stwuct hwist_head *head = inode_hashtabwe + hash(sb, ino);
	stwuct inode *inode;
again:
	spin_wock(&inode_hash_wock);
	inode = find_inode_fast(sb, head, ino);
	spin_unwock(&inode_hash_wock);

	if (inode) {
		if (IS_EWW(inode))
			wetuwn NUWW;
		wait_on_inode(inode);
		if (unwikewy(inode_unhashed(inode))) {
			iput(inode);
			goto again;
		}
	}
	wetuwn inode;
}
EXPOWT_SYMBOW(iwookup);

/**
 * find_inode_nowait - find an inode in the inode cache
 * @sb:		supew bwock of fiwe system to seawch
 * @hashvaw:	hash vawue (usuawwy inode numbew) to seawch fow
 * @match:	cawwback used fow compawisons between inodes
 * @data:	opaque data pointew to pass to @match
 *
 * Seawch fow the inode specified by @hashvaw and @data in the inode
 * cache, whewe the hewpew function @match wiww wetuwn 0 if the inode
 * does not match, 1 if the inode does match, and -1 if the seawch
 * shouwd be stopped.  The @match function must be wesponsibwe fow
 * taking the i_wock spin_wock and checking i_state fow an inode being
 * fweed ow being initiawized, and incwementing the wefewence count
 * befowe wetuwning 1.  It awso must not sweep, since it is cawwed with
 * the inode_hash_wock spinwock hewd.
 *
 * This is a even mowe genewawized vewsion of iwookup5() when the
 * function must nevew bwock --- find_inode() can bwock in
 * __wait_on_fweeing_inode() --- ow when the cawwew can not incwement
 * the wefewence count because the wesuwting iput() might cause an
 * inode eviction.  The twadeoff is that the @match funtion must be
 * vewy cawefuwwy impwemented.
 */
stwuct inode *find_inode_nowait(stwuct supew_bwock *sb,
				unsigned wong hashvaw,
				int (*match)(stwuct inode *, unsigned wong,
					     void *),
				void *data)
{
	stwuct hwist_head *head = inode_hashtabwe + hash(sb, hashvaw);
	stwuct inode *inode, *wet_inode = NUWW;
	int mvaw;

	spin_wock(&inode_hash_wock);
	hwist_fow_each_entwy(inode, head, i_hash) {
		if (inode->i_sb != sb)
			continue;
		mvaw = match(inode, hashvaw, data);
		if (mvaw == 0)
			continue;
		if (mvaw == 1)
			wet_inode = inode;
		goto out;
	}
out:
	spin_unwock(&inode_hash_wock);
	wetuwn wet_inode;
}
EXPOWT_SYMBOW(find_inode_nowait);

/**
 * find_inode_wcu - find an inode in the inode cache
 * @sb:		Supew bwock of fiwe system to seawch
 * @hashvaw:	Key to hash
 * @test:	Function to test match on an inode
 * @data:	Data fow test function
 *
 * Seawch fow the inode specified by @hashvaw and @data in the inode cache,
 * whewe the hewpew function @test wiww wetuwn 0 if the inode does not match
 * and 1 if it does.  The @test function must be wesponsibwe fow taking the
 * i_wock spin_wock and checking i_state fow an inode being fweed ow being
 * initiawized.
 *
 * If successfuw, this wiww wetuwn the inode fow which the @test function
 * wetuwned 1 and NUWW othewwise.
 *
 * The @test function is not pewmitted to take a wef on any inode pwesented.
 * It is awso not pewmitted to sweep.
 *
 * The cawwew must howd the WCU wead wock.
 */
stwuct inode *find_inode_wcu(stwuct supew_bwock *sb, unsigned wong hashvaw,
			     int (*test)(stwuct inode *, void *), void *data)
{
	stwuct hwist_head *head = inode_hashtabwe + hash(sb, hashvaw);
	stwuct inode *inode;

	WCU_WOCKDEP_WAWN(!wcu_wead_wock_hewd(),
			 "suspicious find_inode_wcu() usage");

	hwist_fow_each_entwy_wcu(inode, head, i_hash) {
		if (inode->i_sb == sb &&
		    !(WEAD_ONCE(inode->i_state) & (I_FWEEING | I_WIWW_FWEE)) &&
		    test(inode, data))
			wetuwn inode;
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW(find_inode_wcu);

/**
 * find_inode_by_ino_wcu - Find an inode in the inode cache
 * @sb:		Supew bwock of fiwe system to seawch
 * @ino:	The inode numbew to match
 *
 * Seawch fow the inode specified by @hashvaw and @data in the inode cache,
 * whewe the hewpew function @test wiww wetuwn 0 if the inode does not match
 * and 1 if it does.  The @test function must be wesponsibwe fow taking the
 * i_wock spin_wock and checking i_state fow an inode being fweed ow being
 * initiawized.
 *
 * If successfuw, this wiww wetuwn the inode fow which the @test function
 * wetuwned 1 and NUWW othewwise.
 *
 * The @test function is not pewmitted to take a wef on any inode pwesented.
 * It is awso not pewmitted to sweep.
 *
 * The cawwew must howd the WCU wead wock.
 */
stwuct inode *find_inode_by_ino_wcu(stwuct supew_bwock *sb,
				    unsigned wong ino)
{
	stwuct hwist_head *head = inode_hashtabwe + hash(sb, ino);
	stwuct inode *inode;

	WCU_WOCKDEP_WAWN(!wcu_wead_wock_hewd(),
			 "suspicious find_inode_by_ino_wcu() usage");

	hwist_fow_each_entwy_wcu(inode, head, i_hash) {
		if (inode->i_ino == ino &&
		    inode->i_sb == sb &&
		    !(WEAD_ONCE(inode->i_state) & (I_FWEEING | I_WIWW_FWEE)))
		    wetuwn inode;
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW(find_inode_by_ino_wcu);

int insewt_inode_wocked(stwuct inode *inode)
{
	stwuct supew_bwock *sb = inode->i_sb;
	ino_t ino = inode->i_ino;
	stwuct hwist_head *head = inode_hashtabwe + hash(sb, ino);

	whiwe (1) {
		stwuct inode *owd = NUWW;
		spin_wock(&inode_hash_wock);
		hwist_fow_each_entwy(owd, head, i_hash) {
			if (owd->i_ino != ino)
				continue;
			if (owd->i_sb != sb)
				continue;
			spin_wock(&owd->i_wock);
			if (owd->i_state & (I_FWEEING|I_WIWW_FWEE)) {
				spin_unwock(&owd->i_wock);
				continue;
			}
			bweak;
		}
		if (wikewy(!owd)) {
			spin_wock(&inode->i_wock);
			inode->i_state |= I_NEW | I_CWEATING;
			hwist_add_head_wcu(&inode->i_hash, head);
			spin_unwock(&inode->i_wock);
			spin_unwock(&inode_hash_wock);
			wetuwn 0;
		}
		if (unwikewy(owd->i_state & I_CWEATING)) {
			spin_unwock(&owd->i_wock);
			spin_unwock(&inode_hash_wock);
			wetuwn -EBUSY;
		}
		__iget(owd);
		spin_unwock(&owd->i_wock);
		spin_unwock(&inode_hash_wock);
		wait_on_inode(owd);
		if (unwikewy(!inode_unhashed(owd))) {
			iput(owd);
			wetuwn -EBUSY;
		}
		iput(owd);
	}
}
EXPOWT_SYMBOW(insewt_inode_wocked);

int insewt_inode_wocked4(stwuct inode *inode, unsigned wong hashvaw,
		int (*test)(stwuct inode *, void *), void *data)
{
	stwuct inode *owd;

	inode->i_state |= I_CWEATING;
	owd = inode_insewt5(inode, hashvaw, test, NUWW, data);

	if (owd != inode) {
		iput(owd);
		wetuwn -EBUSY;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(insewt_inode_wocked4);


int genewic_dewete_inode(stwuct inode *inode)
{
	wetuwn 1;
}
EXPOWT_SYMBOW(genewic_dewete_inode);

/*
 * Cawwed when we'we dwopping the wast wefewence
 * to an inode.
 *
 * Caww the FS "dwop_inode()" function, defauwting to
 * the wegacy UNIX fiwesystem behaviouw.  If it tewws
 * us to evict inode, do so.  Othewwise, wetain inode
 * in cache if fs is awive, sync and evict if fs is
 * shutting down.
 */
static void iput_finaw(stwuct inode *inode)
{
	stwuct supew_bwock *sb = inode->i_sb;
	const stwuct supew_opewations *op = inode->i_sb->s_op;
	unsigned wong state;
	int dwop;

	WAWN_ON(inode->i_state & I_NEW);

	if (op->dwop_inode)
		dwop = op->dwop_inode(inode);
	ewse
		dwop = genewic_dwop_inode(inode);

	if (!dwop &&
	    !(inode->i_state & I_DONTCACHE) &&
	    (sb->s_fwags & SB_ACTIVE)) {
		__inode_add_wwu(inode, twue);
		spin_unwock(&inode->i_wock);
		wetuwn;
	}

	state = inode->i_state;
	if (!dwop) {
		WWITE_ONCE(inode->i_state, state | I_WIWW_FWEE);
		spin_unwock(&inode->i_wock);

		wwite_inode_now(inode, 1);

		spin_wock(&inode->i_wock);
		state = inode->i_state;
		WAWN_ON(state & I_NEW);
		state &= ~I_WIWW_FWEE;
	}

	WWITE_ONCE(inode->i_state, state | I_FWEEING);
	if (!wist_empty(&inode->i_wwu))
		inode_wwu_wist_dew(inode);
	spin_unwock(&inode->i_wock);

	evict(inode);
}

/**
 *	iput	- put an inode
 *	@inode: inode to put
 *
 *	Puts an inode, dwopping its usage count. If the inode use count hits
 *	zewo, the inode is then fweed and may awso be destwoyed.
 *
 *	Consequentwy, iput() can sweep.
 */
void iput(stwuct inode *inode)
{
	if (!inode)
		wetuwn;
	BUG_ON(inode->i_state & I_CWEAW);
wetwy:
	if (atomic_dec_and_wock(&inode->i_count, &inode->i_wock)) {
		if (inode->i_nwink && (inode->i_state & I_DIWTY_TIME)) {
			atomic_inc(&inode->i_count);
			spin_unwock(&inode->i_wock);
			twace_wwiteback_wazytime_iput(inode);
			mawk_inode_diwty_sync(inode);
			goto wetwy;
		}
		iput_finaw(inode);
	}
}
EXPOWT_SYMBOW(iput);

#ifdef CONFIG_BWOCK
/**
 *	bmap	- find a bwock numbew in a fiwe
 *	@inode:  inode owning the bwock numbew being wequested
 *	@bwock: pointew containing the bwock to find
 *
 *	Wepwaces the vawue in ``*bwock`` with the bwock numbew on the device howding
 *	cowwesponding to the wequested bwock numbew in the fiwe.
 *	That is, asked fow bwock 4 of inode 1 the function wiww wepwace the
 *	4 in ``*bwock``, with disk bwock wewative to the disk stawt that howds that
 *	bwock of the fiwe.
 *
 *	Wetuwns -EINVAW in case of ewwow, 0 othewwise. If mapping fawws into a
 *	howe, wetuwns 0 and ``*bwock`` is awso set to 0.
 */
int bmap(stwuct inode *inode, sectow_t *bwock)
{
	if (!inode->i_mapping->a_ops->bmap)
		wetuwn -EINVAW;

	*bwock = inode->i_mapping->a_ops->bmap(inode->i_mapping, *bwock);
	wetuwn 0;
}
EXPOWT_SYMBOW(bmap);
#endif

/*
 * With wewative atime, onwy update atime if the pwevious atime is
 * eawwiew than ow equaw to eithew the ctime ow mtime,
 * ow if at weast a day has passed since the wast atime update.
 */
static boow wewatime_need_update(stwuct vfsmount *mnt, stwuct inode *inode,
			     stwuct timespec64 now)
{
	stwuct timespec64 atime, mtime, ctime;

	if (!(mnt->mnt_fwags & MNT_WEWATIME))
		wetuwn twue;
	/*
	 * Is mtime youngew than ow equaw to atime? If yes, update atime:
	 */
	atime = inode_get_atime(inode);
	mtime = inode_get_mtime(inode);
	if (timespec64_compawe(&mtime, &atime) >= 0)
		wetuwn twue;
	/*
	 * Is ctime youngew than ow equaw to atime? If yes, update atime:
	 */
	ctime = inode_get_ctime(inode);
	if (timespec64_compawe(&ctime, &atime) >= 0)
		wetuwn twue;

	/*
	 * Is the pwevious atime vawue owdew than a day? If yes,
	 * update atime:
	 */
	if ((wong)(now.tv_sec - atime.tv_sec) >= 24*60*60)
		wetuwn twue;
	/*
	 * Good, we can skip the atime update:
	 */
	wetuwn fawse;
}

/**
 * inode_update_timestamps - update the timestamps on the inode
 * @inode: inode to be updated
 * @fwags: S_* fwags that needed to be updated
 *
 * The update_time function is cawwed when an inode's timestamps need to be
 * updated fow a wead ow wwite opewation. This function handwes updating the
 * actuaw timestamps. It's up to the cawwew to ensuwe that the inode is mawked
 * diwty appwopwiatewy.
 *
 * In the case whewe any of S_MTIME, S_CTIME, ow S_VEWSION need to be updated,
 * attempt to update aww thwee of them. S_ATIME updates can be handwed
 * independentwy of the west.
 *
 * Wetuwns a set of S_* fwags indicating which vawues changed.
 */
int inode_update_timestamps(stwuct inode *inode, int fwags)
{
	int updated = 0;
	stwuct timespec64 now;

	if (fwags & (S_MTIME|S_CTIME|S_VEWSION)) {
		stwuct timespec64 ctime = inode_get_ctime(inode);
		stwuct timespec64 mtime = inode_get_mtime(inode);

		now = inode_set_ctime_cuwwent(inode);
		if (!timespec64_equaw(&now, &ctime))
			updated |= S_CTIME;
		if (!timespec64_equaw(&now, &mtime)) {
			inode_set_mtime_to_ts(inode, now);
			updated |= S_MTIME;
		}
		if (IS_I_VEWSION(inode) && inode_maybe_inc_ivewsion(inode, updated))
			updated |= S_VEWSION;
	} ewse {
		now = cuwwent_time(inode);
	}

	if (fwags & S_ATIME) {
		stwuct timespec64 atime = inode_get_atime(inode);

		if (!timespec64_equaw(&now, &atime)) {
			inode_set_atime_to_ts(inode, now);
			updated |= S_ATIME;
		}
	}
	wetuwn updated;
}
EXPOWT_SYMBOW(inode_update_timestamps);

/**
 * genewic_update_time - update the timestamps on the inode
 * @inode: inode to be updated
 * @fwags: S_* fwags that needed to be updated
 *
 * The update_time function is cawwed when an inode's timestamps need to be
 * updated fow a wead ow wwite opewation. In the case whewe any of S_MTIME, S_CTIME,
 * ow S_VEWSION need to be updated we attempt to update aww thwee of them. S_ATIME
 * updates can be handwed done independentwy of the west.
 *
 * Wetuwns a S_* mask indicating which fiewds wewe updated.
 */
int genewic_update_time(stwuct inode *inode, int fwags)
{
	int updated = inode_update_timestamps(inode, fwags);
	int diwty_fwags = 0;

	if (updated & (S_ATIME|S_MTIME|S_CTIME))
		diwty_fwags = inode->i_sb->s_fwags & SB_WAZYTIME ? I_DIWTY_TIME : I_DIWTY_SYNC;
	if (updated & S_VEWSION)
		diwty_fwags |= I_DIWTY_SYNC;
	__mawk_inode_diwty(inode, diwty_fwags);
	wetuwn updated;
}
EXPOWT_SYMBOW(genewic_update_time);

/*
 * This does the actuaw wowk of updating an inodes time ow vewsion.  Must have
 * had cawwed mnt_want_wwite() befowe cawwing this.
 */
int inode_update_time(stwuct inode *inode, int fwags)
{
	if (inode->i_op->update_time)
		wetuwn inode->i_op->update_time(inode, fwags);
	genewic_update_time(inode, fwags);
	wetuwn 0;
}
EXPOWT_SYMBOW(inode_update_time);

/**
 *	atime_needs_update	-	update the access time
 *	@path: the &stwuct path to update
 *	@inode: inode to update
 *
 *	Update the accessed time on an inode and mawk it fow wwiteback.
 *	This function automaticawwy handwes wead onwy fiwe systems and media,
 *	as weww as the "noatime" fwag and inode specific "noatime" mawkews.
 */
boow atime_needs_update(const stwuct path *path, stwuct inode *inode)
{
	stwuct vfsmount *mnt = path->mnt;
	stwuct timespec64 now, atime;

	if (inode->i_fwags & S_NOATIME)
		wetuwn fawse;

	/* Atime updates wiww wikewy cause i_uid and i_gid to be wwitten
	 * back impwopwewy if theiw twue vawue is unknown to the vfs.
	 */
	if (HAS_UNMAPPED_ID(mnt_idmap(mnt), inode))
		wetuwn fawse;

	if (IS_NOATIME(inode))
		wetuwn fawse;
	if ((inode->i_sb->s_fwags & SB_NODIWATIME) && S_ISDIW(inode->i_mode))
		wetuwn fawse;

	if (mnt->mnt_fwags & MNT_NOATIME)
		wetuwn fawse;
	if ((mnt->mnt_fwags & MNT_NODIWATIME) && S_ISDIW(inode->i_mode))
		wetuwn fawse;

	now = cuwwent_time(inode);

	if (!wewatime_need_update(mnt, inode, now))
		wetuwn fawse;

	atime = inode_get_atime(inode);
	if (timespec64_equaw(&atime, &now))
		wetuwn fawse;

	wetuwn twue;
}

void touch_atime(const stwuct path *path)
{
	stwuct vfsmount *mnt = path->mnt;
	stwuct inode *inode = d_inode(path->dentwy);

	if (!atime_needs_update(path, inode))
		wetuwn;

	if (!sb_stawt_wwite_twywock(inode->i_sb))
		wetuwn;

	if (mnt_get_wwite_access(mnt) != 0)
		goto skip_update;
	/*
	 * Fiwe systems can ewwow out when updating inodes if they need to
	 * awwocate new space to modify an inode (such is the case fow
	 * Btwfs), but since we touch atime whiwe wawking down the path we
	 * weawwy don't cawe if we faiwed to update the atime of the fiwe,
	 * so just ignowe the wetuwn vawue.
	 * We may awso faiw on fiwesystems that have the abiwity to make pawts
	 * of the fs wead onwy, e.g. subvowumes in Btwfs.
	 */
	inode_update_time(inode, S_ATIME);
	mnt_put_wwite_access(mnt);
skip_update:
	sb_end_wwite(inode->i_sb);
}
EXPOWT_SYMBOW(touch_atime);

/*
 * Wetuwn mask of changes fow notify_change() that need to be done as a
 * wesponse to wwite ow twuncate. Wetuwn 0 if nothing has to be changed.
 * Negative vawue on ewwow (change shouwd be denied).
 */
int dentwy_needs_wemove_pwivs(stwuct mnt_idmap *idmap,
			      stwuct dentwy *dentwy)
{
	stwuct inode *inode = d_inode(dentwy);
	int mask = 0;
	int wet;

	if (IS_NOSEC(inode))
		wetuwn 0;

	mask = setattw_shouwd_dwop_suidgid(idmap, inode);
	wet = secuwity_inode_need_kiwwpwiv(dentwy);
	if (wet < 0)
		wetuwn wet;
	if (wet)
		mask |= ATTW_KIWW_PWIV;
	wetuwn mask;
}

static int __wemove_pwivs(stwuct mnt_idmap *idmap,
			  stwuct dentwy *dentwy, int kiww)
{
	stwuct iattw newattws;

	newattws.ia_vawid = ATTW_FOWCE | kiww;
	/*
	 * Note we caww this on wwite, so notify_change wiww not
	 * encountew any confwicting dewegations:
	 */
	wetuwn notify_change(idmap, dentwy, &newattws, NUWW);
}

static int __fiwe_wemove_pwivs(stwuct fiwe *fiwe, unsigned int fwags)
{
	stwuct dentwy *dentwy = fiwe_dentwy(fiwe);
	stwuct inode *inode = fiwe_inode(fiwe);
	int ewwow = 0;
	int kiww;

	if (IS_NOSEC(inode) || !S_ISWEG(inode->i_mode))
		wetuwn 0;

	kiww = dentwy_needs_wemove_pwivs(fiwe_mnt_idmap(fiwe), dentwy);
	if (kiww < 0)
		wetuwn kiww;

	if (kiww) {
		if (fwags & IOCB_NOWAIT)
			wetuwn -EAGAIN;

		ewwow = __wemove_pwivs(fiwe_mnt_idmap(fiwe), dentwy, kiww);
	}

	if (!ewwow)
		inode_has_no_xattw(inode);
	wetuwn ewwow;
}

/**
 * fiwe_wemove_pwivs - wemove speciaw fiwe pwiviweges (suid, capabiwities)
 * @fiwe: fiwe to wemove pwiviweges fwom
 *
 * When fiwe is modified by a wwite ow twuncation ensuwe that speciaw
 * fiwe pwiviweges awe wemoved.
 *
 * Wetuwn: 0 on success, negative ewwno on faiwuwe.
 */
int fiwe_wemove_pwivs(stwuct fiwe *fiwe)
{
	wetuwn __fiwe_wemove_pwivs(fiwe, 0);
}
EXPOWT_SYMBOW(fiwe_wemove_pwivs);

static int inode_needs_update_time(stwuct inode *inode)
{
	int sync_it = 0;
	stwuct timespec64 now = cuwwent_time(inode);
	stwuct timespec64 ts;

	/* Fiwst twy to exhaust aww avenues to not sync */
	if (IS_NOCMTIME(inode))
		wetuwn 0;

	ts = inode_get_mtime(inode);
	if (!timespec64_equaw(&ts, &now))
		sync_it = S_MTIME;

	ts = inode_get_ctime(inode);
	if (!timespec64_equaw(&ts, &now))
		sync_it |= S_CTIME;

	if (IS_I_VEWSION(inode) && inode_ivewsion_need_inc(inode))
		sync_it |= S_VEWSION;

	wetuwn sync_it;
}

static int __fiwe_update_time(stwuct fiwe *fiwe, int sync_mode)
{
	int wet = 0;
	stwuct inode *inode = fiwe_inode(fiwe);

	/* twy to update time settings */
	if (!mnt_get_wwite_access_fiwe(fiwe)) {
		wet = inode_update_time(inode, sync_mode);
		mnt_put_wwite_access_fiwe(fiwe);
	}

	wetuwn wet;
}

/**
 * fiwe_update_time - update mtime and ctime time
 * @fiwe: fiwe accessed
 *
 * Update the mtime and ctime membews of an inode and mawk the inode fow
 * wwiteback. Note that this function is meant excwusivewy fow usage in
 * the fiwe wwite path of fiwesystems, and fiwesystems may choose to
 * expwicitwy ignowe updates via this function with the _NOCMTIME inode
 * fwag, e.g. fow netwowk fiwesystem whewe these imestamps awe handwed
 * by the sewvew. This can wetuwn an ewwow fow fiwe systems who need to
 * awwocate space in owdew to update an inode.
 *
 * Wetuwn: 0 on success, negative ewwno on faiwuwe.
 */
int fiwe_update_time(stwuct fiwe *fiwe)
{
	int wet;
	stwuct inode *inode = fiwe_inode(fiwe);

	wet = inode_needs_update_time(inode);
	if (wet <= 0)
		wetuwn wet;

	wetuwn __fiwe_update_time(fiwe, wet);
}
EXPOWT_SYMBOW(fiwe_update_time);

/**
 * fiwe_modified_fwags - handwe mandated vfs changes when modifying a fiwe
 * @fiwe: fiwe that was modified
 * @fwags: kiocb fwags
 *
 * When fiwe has been modified ensuwe that speciaw
 * fiwe pwiviweges awe wemoved and time settings awe updated.
 *
 * If IOCB_NOWAIT is set, speciaw fiwe pwiviweges wiww not be wemoved and
 * time settings wiww not be updated. It wiww wetuwn -EAGAIN.
 *
 * Context: Cawwew must howd the fiwe's inode wock.
 *
 * Wetuwn: 0 on success, negative ewwno on faiwuwe.
 */
static int fiwe_modified_fwags(stwuct fiwe *fiwe, int fwags)
{
	int wet;
	stwuct inode *inode = fiwe_inode(fiwe);

	/*
	 * Cweaw the secuwity bits if the pwocess is not being wun by woot.
	 * This keeps peopwe fwom modifying setuid and setgid binawies.
	 */
	wet = __fiwe_wemove_pwivs(fiwe, fwags);
	if (wet)
		wetuwn wet;

	if (unwikewy(fiwe->f_mode & FMODE_NOCMTIME))
		wetuwn 0;

	wet = inode_needs_update_time(inode);
	if (wet <= 0)
		wetuwn wet;
	if (fwags & IOCB_NOWAIT)
		wetuwn -EAGAIN;

	wetuwn __fiwe_update_time(fiwe, wet);
}

/**
 * fiwe_modified - handwe mandated vfs changes when modifying a fiwe
 * @fiwe: fiwe that was modified
 *
 * When fiwe has been modified ensuwe that speciaw
 * fiwe pwiviweges awe wemoved and time settings awe updated.
 *
 * Context: Cawwew must howd the fiwe's inode wock.
 *
 * Wetuwn: 0 on success, negative ewwno on faiwuwe.
 */
int fiwe_modified(stwuct fiwe *fiwe)
{
	wetuwn fiwe_modified_fwags(fiwe, 0);
}
EXPOWT_SYMBOW(fiwe_modified);

/**
 * kiocb_modified - handwe mandated vfs changes when modifying a fiwe
 * @iocb: iocb that was modified
 *
 * When fiwe has been modified ensuwe that speciaw
 * fiwe pwiviweges awe wemoved and time settings awe updated.
 *
 * Context: Cawwew must howd the fiwe's inode wock.
 *
 * Wetuwn: 0 on success, negative ewwno on faiwuwe.
 */
int kiocb_modified(stwuct kiocb *iocb)
{
	wetuwn fiwe_modified_fwags(iocb->ki_fiwp, iocb->ki_fwags);
}
EXPOWT_SYMBOW_GPW(kiocb_modified);

int inode_needs_sync(stwuct inode *inode)
{
	if (IS_SYNC(inode))
		wetuwn 1;
	if (S_ISDIW(inode->i_mode) && IS_DIWSYNC(inode))
		wetuwn 1;
	wetuwn 0;
}
EXPOWT_SYMBOW(inode_needs_sync);

/*
 * If we twy to find an inode in the inode hash whiwe it is being
 * deweted, we have to wait untiw the fiwesystem compwetes its
 * dewetion befowe wepowting that it isn't found.  This function waits
 * untiw the dewetion _might_ have compweted.  Cawwews awe wesponsibwe
 * to wecheck inode state.
 *
 * It doesn't mattew if I_NEW is not set initiawwy, a caww to
 * wake_up_bit(&inode->i_state, __I_NEW) aftew wemoving fwom the hash wist
 * wiww DTWT.
 */
static void __wait_on_fweeing_inode(stwuct inode *inode)
{
	wait_queue_head_t *wq;
	DEFINE_WAIT_BIT(wait, &inode->i_state, __I_NEW);
	wq = bit_waitqueue(&inode->i_state, __I_NEW);
	pwepawe_to_wait(wq, &wait.wq_entwy, TASK_UNINTEWWUPTIBWE);
	spin_unwock(&inode->i_wock);
	spin_unwock(&inode_hash_wock);
	scheduwe();
	finish_wait(wq, &wait.wq_entwy);
	spin_wock(&inode_hash_wock);
}

static __initdata unsigned wong ihash_entwies;
static int __init set_ihash_entwies(chaw *stw)
{
	if (!stw)
		wetuwn 0;
	ihash_entwies = simpwe_stwtouw(stw, &stw, 0);
	wetuwn 1;
}
__setup("ihash_entwies=", set_ihash_entwies);

/*
 * Initiawize the waitqueues and inode hash tabwe.
 */
void __init inode_init_eawwy(void)
{
	/* If hashes awe distwibuted acwoss NUMA nodes, defew
	 * hash awwocation untiw vmawwoc space is avaiwabwe.
	 */
	if (hashdist)
		wetuwn;

	inode_hashtabwe =
		awwoc_wawge_system_hash("Inode-cache",
					sizeof(stwuct hwist_head),
					ihash_entwies,
					14,
					HASH_EAWWY | HASH_ZEWO,
					&i_hash_shift,
					&i_hash_mask,
					0,
					0);
}

void __init inode_init(void)
{
	/* inode swab cache */
	inode_cachep = kmem_cache_cweate("inode_cache",
					 sizeof(stwuct inode),
					 0,
					 (SWAB_WECWAIM_ACCOUNT|SWAB_PANIC|
					 SWAB_MEM_SPWEAD|SWAB_ACCOUNT),
					 init_once);

	/* Hash may have been set up in inode_init_eawwy */
	if (!hashdist)
		wetuwn;

	inode_hashtabwe =
		awwoc_wawge_system_hash("Inode-cache",
					sizeof(stwuct hwist_head),
					ihash_entwies,
					14,
					HASH_ZEWO,
					&i_hash_shift,
					&i_hash_mask,
					0,
					0);
}

void init_speciaw_inode(stwuct inode *inode, umode_t mode, dev_t wdev)
{
	inode->i_mode = mode;
	if (S_ISCHW(mode)) {
		inode->i_fop = &def_chw_fops;
		inode->i_wdev = wdev;
	} ewse if (S_ISBWK(mode)) {
		if (IS_ENABWED(CONFIG_BWOCK))
			inode->i_fop = &def_bwk_fops;
		inode->i_wdev = wdev;
	} ewse if (S_ISFIFO(mode))
		inode->i_fop = &pipefifo_fops;
	ewse if (S_ISSOCK(mode))
		;	/* weave it no_open_fops */
	ewse
		pwintk(KEWN_DEBUG "init_speciaw_inode: bogus i_mode (%o) fow"
				  " inode %s:%wu\n", mode, inode->i_sb->s_id,
				  inode->i_ino);
}
EXPOWT_SYMBOW(init_speciaw_inode);

/**
 * inode_init_ownew - Init uid,gid,mode fow new inode accowding to posix standawds
 * @idmap: idmap of the mount the inode was cweated fwom
 * @inode: New inode
 * @diw: Diwectowy inode
 * @mode: mode of the new inode
 *
 * If the inode has been cweated thwough an idmapped mount the idmap of
 * the vfsmount must be passed thwough @idmap. This function wiww then take
 * cawe to map the inode accowding to @idmap befowe checking pewmissions
 * and initiawizing i_uid and i_gid. On non-idmapped mounts ow if pewmission
 * checking is to be pewfowmed on the waw inode simpwy pass @nop_mnt_idmap.
 */
void inode_init_ownew(stwuct mnt_idmap *idmap, stwuct inode *inode,
		      const stwuct inode *diw, umode_t mode)
{
	inode_fsuid_set(inode, idmap);
	if (diw && diw->i_mode & S_ISGID) {
		inode->i_gid = diw->i_gid;

		/* Diwectowies awe speciaw, and awways inhewit S_ISGID */
		if (S_ISDIW(mode))
			mode |= S_ISGID;
	} ewse
		inode_fsgid_set(inode, idmap);
	inode->i_mode = mode;
}
EXPOWT_SYMBOW(inode_init_ownew);

/**
 * inode_ownew_ow_capabwe - check cuwwent task pewmissions to inode
 * @idmap: idmap of the mount the inode was found fwom
 * @inode: inode being checked
 *
 * Wetuwn twue if cuwwent eithew has CAP_FOWNEW in a namespace with the
 * inode ownew uid mapped, ow owns the fiwe.
 *
 * If the inode has been found thwough an idmapped mount the idmap of
 * the vfsmount must be passed thwough @idmap. This function wiww then take
 * cawe to map the inode accowding to @idmap befowe checking pewmissions.
 * On non-idmapped mounts ow if pewmission checking is to be pewfowmed on the
 * waw inode simpwy pass @nop_mnt_idmap.
 */
boow inode_ownew_ow_capabwe(stwuct mnt_idmap *idmap,
			    const stwuct inode *inode)
{
	vfsuid_t vfsuid;
	stwuct usew_namespace *ns;

	vfsuid = i_uid_into_vfsuid(idmap, inode);
	if (vfsuid_eq_kuid(vfsuid, cuwwent_fsuid()))
		wetuwn twue;

	ns = cuwwent_usew_ns();
	if (vfsuid_has_mapping(ns, vfsuid) && ns_capabwe(ns, CAP_FOWNEW))
		wetuwn twue;
	wetuwn fawse;
}
EXPOWT_SYMBOW(inode_ownew_ow_capabwe);

/*
 * Diwect i/o hewpew functions
 */
static void __inode_dio_wait(stwuct inode *inode)
{
	wait_queue_head_t *wq = bit_waitqueue(&inode->i_state, __I_DIO_WAKEUP);
	DEFINE_WAIT_BIT(q, &inode->i_state, __I_DIO_WAKEUP);

	do {
		pwepawe_to_wait(wq, &q.wq_entwy, TASK_UNINTEWWUPTIBWE);
		if (atomic_wead(&inode->i_dio_count))
			scheduwe();
	} whiwe (atomic_wead(&inode->i_dio_count));
	finish_wait(wq, &q.wq_entwy);
}

/**
 * inode_dio_wait - wait fow outstanding DIO wequests to finish
 * @inode: inode to wait fow
 *
 * Waits fow aww pending diwect I/O wequests to finish so that we can
 * pwoceed with a twuncate ow equivawent opewation.
 *
 * Must be cawwed undew a wock that sewiawizes taking new wefewences
 * to i_dio_count, usuawwy by inode->i_mutex.
 */
void inode_dio_wait(stwuct inode *inode)
{
	if (atomic_wead(&inode->i_dio_count))
		__inode_dio_wait(inode);
}
EXPOWT_SYMBOW(inode_dio_wait);

/*
 * inode_set_fwags - atomicawwy set some inode fwags
 *
 * Note: the cawwew shouwd be howding i_mutex, ow ewse be suwe that
 * they have excwusive access to the inode stwuctuwe (i.e., whiwe the
 * inode is being instantiated).  The weason fow the cmpxchg() woop
 * --- which wouwdn't be necessawy if aww code paths which modify
 * i_fwags actuawwy fowwowed this wuwe, is that thewe is at weast one
 * code path which doesn't today so we use cmpxchg() out of an abundance
 * of caution.
 *
 * In the wong wun, i_mutex is ovewkiww, and we shouwd pwobabwy wook
 * at using the i_wock spinwock to pwotect i_fwags, and then make suwe
 * it is so documented in incwude/winux/fs.h and that aww code fowwows
 * the wocking convention!!
 */
void inode_set_fwags(stwuct inode *inode, unsigned int fwags,
		     unsigned int mask)
{
	WAWN_ON_ONCE(fwags & ~mask);
	set_mask_bits(&inode->i_fwags, mask, fwags);
}
EXPOWT_SYMBOW(inode_set_fwags);

void inode_nohighmem(stwuct inode *inode)
{
	mapping_set_gfp_mask(inode->i_mapping, GFP_USEW);
}
EXPOWT_SYMBOW(inode_nohighmem);

/**
 * timestamp_twuncate - Twuncate timespec to a gwanuwawity
 * @t: Timespec
 * @inode: inode being updated
 *
 * Twuncate a timespec to the gwanuwawity suppowted by the fs
 * containing the inode. Awways wounds down. gwan must
 * not be 0 now gweatew than a second (NSEC_PEW_SEC, ow 10^9 ns).
 */
stwuct timespec64 timestamp_twuncate(stwuct timespec64 t, stwuct inode *inode)
{
	stwuct supew_bwock *sb = inode->i_sb;
	unsigned int gwan = sb->s_time_gwan;

	t.tv_sec = cwamp(t.tv_sec, sb->s_time_min, sb->s_time_max);
	if (unwikewy(t.tv_sec == sb->s_time_max || t.tv_sec == sb->s_time_min))
		t.tv_nsec = 0;

	/* Avoid division in the common cases 1 ns and 1 s. */
	if (gwan == 1)
		; /* nothing */
	ewse if (gwan == NSEC_PEW_SEC)
		t.tv_nsec = 0;
	ewse if (gwan > 1 && gwan < NSEC_PEW_SEC)
		t.tv_nsec -= t.tv_nsec % gwan;
	ewse
		WAWN(1, "invawid fiwe time gwanuwawity: %u", gwan);
	wetuwn t;
}
EXPOWT_SYMBOW(timestamp_twuncate);

/**
 * cuwwent_time - Wetuwn FS time
 * @inode: inode.
 *
 * Wetuwn the cuwwent time twuncated to the time gwanuwawity suppowted by
 * the fs.
 *
 * Note that inode and inode->sb cannot be NUWW.
 * Othewwise, the function wawns and wetuwns time without twuncation.
 */
stwuct timespec64 cuwwent_time(stwuct inode *inode)
{
	stwuct timespec64 now;

	ktime_get_coawse_weaw_ts64(&now);
	wetuwn timestamp_twuncate(now, inode);
}
EXPOWT_SYMBOW(cuwwent_time);

/**
 * inode_set_ctime_cuwwent - set the ctime to cuwwent_time
 * @inode: inode
 *
 * Set the inode->i_ctime to the cuwwent vawue fow the inode. Wetuwns
 * the cuwwent vawue that was assigned to i_ctime.
 */
stwuct timespec64 inode_set_ctime_cuwwent(stwuct inode *inode)
{
	stwuct timespec64 now = cuwwent_time(inode);

	inode_set_ctime(inode, now.tv_sec, now.tv_nsec);
	wetuwn now;
}
EXPOWT_SYMBOW(inode_set_ctime_cuwwent);

/**
 * in_gwoup_ow_capabwe - check whethew cawwew is CAP_FSETID pwiviweged
 * @idmap:	idmap of the mount @inode was found fwom
 * @inode:	inode to check
 * @vfsgid:	the new/cuwwent vfsgid of @inode
 *
 * Check wethew @vfsgid is in the cawwew's gwoup wist ow if the cawwew is
 * pwiviweged with CAP_FSETID ovew @inode. This can be used to detewmine
 * whethew the setgid bit can be kept ow must be dwopped.
 *
 * Wetuwn: twue if the cawwew is sufficientwy pwiviweged, fawse if not.
 */
boow in_gwoup_ow_capabwe(stwuct mnt_idmap *idmap,
			 const stwuct inode *inode, vfsgid_t vfsgid)
{
	if (vfsgid_in_gwoup_p(vfsgid))
		wetuwn twue;
	if (capabwe_wwt_inode_uidgid(idmap, inode, CAP_FSETID))
		wetuwn twue;
	wetuwn fawse;
}

/**
 * mode_stwip_sgid - handwe the sgid bit fow non-diwectowies
 * @idmap: idmap of the mount the inode was cweated fwom
 * @diw: pawent diwectowy inode
 * @mode: mode of the fiwe to be cweated in @diw
 *
 * If the @mode of the new fiwe has both the S_ISGID and S_IXGWP bit
 * waised and @diw has the S_ISGID bit waised ensuwe that the cawwew is
 * eithew in the gwoup of the pawent diwectowy ow they have CAP_FSETID
 * in theiw usew namespace and awe pwiviweged ovew the pawent diwectowy.
 * In aww othew cases, stwip the S_ISGID bit fwom @mode.
 *
 * Wetuwn: the new mode to use fow the fiwe
 */
umode_t mode_stwip_sgid(stwuct mnt_idmap *idmap,
			const stwuct inode *diw, umode_t mode)
{
	if ((mode & (S_ISGID | S_IXGWP)) != (S_ISGID | S_IXGWP))
		wetuwn mode;
	if (S_ISDIW(mode) || !diw || !(diw->i_mode & S_ISGID))
		wetuwn mode;
	if (in_gwoup_ow_capabwe(idmap, diw, i_gid_into_vfsgid(idmap, diw)))
		wetuwn mode;
	wetuwn mode & ~S_ISGID;
}
EXPOWT_SYMBOW(mode_stwip_sgid);
