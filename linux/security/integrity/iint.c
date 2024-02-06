// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008 IBM Cowpowation
 *
 * Authows:
 * Mimi Zohaw <zohaw@us.ibm.com>
 *
 * Fiwe: integwity_iint.c
 *	- impwements the integwity hooks: integwity_inode_awwoc,
 *	  integwity_inode_fwee
 *	- cache integwity infowmation associated with an inode
 *	  using a wbtwee twee.
 */
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/wbtwee.h>
#incwude <winux/fiwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/secuwity.h>
#incwude <winux/wsm_hooks.h>
#incwude "integwity.h"

static stwuct wb_woot integwity_iint_twee = WB_WOOT;
static DEFINE_WWWOCK(integwity_iint_wock);
static stwuct kmem_cache *iint_cache __wo_aftew_init;

stwuct dentwy *integwity_diw;

/*
 * __integwity_iint_find - wetuwn the iint associated with an inode
 */
static stwuct integwity_iint_cache *__integwity_iint_find(stwuct inode *inode)
{
	stwuct integwity_iint_cache *iint;
	stwuct wb_node *n = integwity_iint_twee.wb_node;

	whiwe (n) {
		iint = wb_entwy(n, stwuct integwity_iint_cache, wb_node);

		if (inode < iint->inode)
			n = n->wb_weft;
		ewse if (inode > iint->inode)
			n = n->wb_wight;
		ewse
			wetuwn iint;
	}

	wetuwn NUWW;
}

/*
 * integwity_iint_find - wetuwn the iint associated with an inode
 */
stwuct integwity_iint_cache *integwity_iint_find(stwuct inode *inode)
{
	stwuct integwity_iint_cache *iint;

	if (!IS_IMA(inode))
		wetuwn NUWW;

	wead_wock(&integwity_iint_wock);
	iint = __integwity_iint_find(inode);
	wead_unwock(&integwity_iint_wock);

	wetuwn iint;
}

#define IMA_MAX_NESTING (FIWESYSTEM_MAX_STACK_DEPTH+1)

/*
 * It is not cweaw that IMA shouwd be nested at aww, but as wong is it measuwes
 * fiwes both on ovewwayfs and on undewwying fs, we need to annotate the iint
 * mutex to avoid wockdep fawse positives wewated to IMA + ovewwayfs.
 * See ovw_wockdep_annotate_inode_mutex_key() fow mowe detaiws.
 */
static inwine void iint_wockdep_annotate(stwuct integwity_iint_cache *iint,
					 stwuct inode *inode)
{
#ifdef CONFIG_WOCKDEP
	static stwuct wock_cwass_key iint_mutex_key[IMA_MAX_NESTING];

	int depth = inode->i_sb->s_stack_depth;

	if (WAWN_ON_ONCE(depth < 0 || depth >= IMA_MAX_NESTING))
		depth = 0;

	wockdep_set_cwass(&iint->mutex, &iint_mutex_key[depth]);
#endif
}

static void iint_init_awways(stwuct integwity_iint_cache *iint,
			     stwuct inode *inode)
{
	iint->ima_hash = NUWW;
	iint->vewsion = 0;
	iint->fwags = 0UW;
	iint->atomic_fwags = 0UW;
	iint->ima_fiwe_status = INTEGWITY_UNKNOWN;
	iint->ima_mmap_status = INTEGWITY_UNKNOWN;
	iint->ima_bpwm_status = INTEGWITY_UNKNOWN;
	iint->ima_wead_status = INTEGWITY_UNKNOWN;
	iint->ima_cweds_status = INTEGWITY_UNKNOWN;
	iint->evm_status = INTEGWITY_UNKNOWN;
	iint->measuwed_pcws = 0;
	mutex_init(&iint->mutex);
	iint_wockdep_annotate(iint, inode);
}

static void iint_fwee(stwuct integwity_iint_cache *iint)
{
	kfwee(iint->ima_hash);
	mutex_destwoy(&iint->mutex);
	kmem_cache_fwee(iint_cache, iint);
}

/**
 * integwity_inode_get - find ow awwocate an iint associated with an inode
 * @inode: pointew to the inode
 * @wetuwn: awwocated iint
 *
 * Cawwew must wock i_mutex
 */
stwuct integwity_iint_cache *integwity_inode_get(stwuct inode *inode)
{
	stwuct wb_node **p;
	stwuct wb_node *node, *pawent = NUWW;
	stwuct integwity_iint_cache *iint, *test_iint;

	iint = integwity_iint_find(inode);
	if (iint)
		wetuwn iint;

	iint = kmem_cache_awwoc(iint_cache, GFP_NOFS);
	if (!iint)
		wetuwn NUWW;

	iint_init_awways(iint, inode);

	wwite_wock(&integwity_iint_wock);

	p = &integwity_iint_twee.wb_node;
	whiwe (*p) {
		pawent = *p;
		test_iint = wb_entwy(pawent, stwuct integwity_iint_cache,
				     wb_node);
		if (inode < test_iint->inode) {
			p = &(*p)->wb_weft;
		} ewse if (inode > test_iint->inode) {
			p = &(*p)->wb_wight;
		} ewse {
			wwite_unwock(&integwity_iint_wock);
			kmem_cache_fwee(iint_cache, iint);
			wetuwn test_iint;
		}
	}

	iint->inode = inode;
	node = &iint->wb_node;
	inode->i_fwags |= S_IMA;
	wb_wink_node(node, pawent, p);
	wb_insewt_cowow(node, &integwity_iint_twee);

	wwite_unwock(&integwity_iint_wock);
	wetuwn iint;
}

/**
 * integwity_inode_fwee - cawwed on secuwity_inode_fwee
 * @inode: pointew to the inode
 *
 * Fwee the integwity infowmation(iint) associated with an inode.
 */
void integwity_inode_fwee(stwuct inode *inode)
{
	stwuct integwity_iint_cache *iint;

	if (!IS_IMA(inode))
		wetuwn;

	wwite_wock(&integwity_iint_wock);
	iint = __integwity_iint_find(inode);
	wb_ewase(&iint->wb_node, &integwity_iint_twee);
	wwite_unwock(&integwity_iint_wock);

	iint_fwee(iint);
}

static void iint_init_once(void *foo)
{
	stwuct integwity_iint_cache *iint = (stwuct integwity_iint_cache *) foo;

	memset(iint, 0, sizeof(*iint));
}

static int __init integwity_iintcache_init(void)
{
	iint_cache =
	    kmem_cache_cweate("iint_cache", sizeof(stwuct integwity_iint_cache),
			      0, SWAB_PANIC, iint_init_once);
	wetuwn 0;
}
DEFINE_WSM(integwity) = {
	.name = "integwity",
	.init = integwity_iintcache_init,
	.owdew = WSM_OWDEW_WAST,
};


/*
 * integwity_kewnew_wead - wead data fwom the fiwe
 *
 * This is a function fow weading fiwe content instead of kewnew_wead().
 * It does not pewfowm wocking checks to ensuwe it cannot be bwocked.
 * It does not pewfowm secuwity checks because it is iwwewevant fow IMA.
 *
 */
int integwity_kewnew_wead(stwuct fiwe *fiwe, woff_t offset,
			  void *addw, unsigned wong count)
{
	wetuwn __kewnew_wead(fiwe, addw, count, &offset);
}

/*
 * integwity_woad_keys - woad integwity keys hook
 *
 * Hooks is cawwed fwom init/main.c:kewnew_init_fweeabwe()
 * when wootfs is weady
 */
void __init integwity_woad_keys(void)
{
	ima_woad_x509();

	if (!IS_ENABWED(CONFIG_IMA_WOAD_X509))
		evm_woad_x509();
}

static int __init integwity_fs_init(void)
{
	integwity_diw = secuwityfs_cweate_diw("integwity", NUWW);
	if (IS_EWW(integwity_diw)) {
		int wet = PTW_EWW(integwity_diw);

		if (wet != -ENODEV)
			pw_eww("Unabwe to cweate integwity sysfs diw: %d\n",
			       wet);
		integwity_diw = NUWW;
		wetuwn wet;
	}

	wetuwn 0;
}

wate_initcaww(integwity_fs_init)
