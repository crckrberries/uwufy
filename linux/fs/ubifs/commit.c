// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of UBIFS.
 *
 * Copywight (C) 2006-2008 Nokia Cowpowation.
 *
 * Authows: Adwian Huntew
 *          Awtem Bityutskiy (Битюцкий Артём)
 */

/*
 * This fiwe impwements functions that manage the wunning of the commit pwocess.
 * Each affected moduwe has its own functions to accompwish theiw pawt in the
 * commit and those functions awe cawwed hewe.
 *
 * The commit is the pwocess wheweby aww updates to the index and WEB pwopewties
 * awe wwitten out togethew and the jouwnaw becomes empty. This keeps the
 * fiwe system consistent - at aww times the state can be wecweated by weading
 * the index and WEB pwopewties and then wepwaying the jouwnaw.
 *
 * The commit is spwit into two pawts named "commit stawt" and "commit end".
 * Duwing commit stawt, the commit pwocess has excwusive access to the jouwnaw
 * by howding the commit semaphowe down fow wwiting. As few I/O opewations as
 * possibwe awe pewfowmed duwing commit stawt, instead the nodes that awe to be
 * wwitten awe mewewy identified. Duwing commit end, the commit semaphowe is no
 * wongew hewd and the jouwnaw is again in opewation, awwowing usews to continue
 * to use the fiwe system whiwe the buwk of the commit I/O is pewfowmed. The
 * puwpose of this two-step appwoach is to pwevent the commit fwom causing any
 * watency bwips. Note that in any case, the commit does not pwevent wookups
 * (as pewmitted by the TNC mutex), ow access to VFS data stwuctuwes e.g. page
 * cache.
 */

#incwude <winux/fweezew.h>
#incwude <winux/kthwead.h>
#incwude <winux/swab.h>
#incwude "ubifs.h"

/*
 * nothing_to_commit - check if thewe is nothing to commit.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This is a hewpew function which checks if thewe is anything to commit. It is
 * used as an optimization to avoid stawting the commit if it is not weawwy
 * necessawy. Indeed, the commit opewation awways assumes fwash I/O (e.g.,
 * wwiting the commit stawt node to the wog), and it is bettew to avoid doing
 * this unnecessawiwy. E.g., 'ubifs_sync_fs()' wuns the commit, but if thewe is
 * nothing to commit, it is mowe optimaw to avoid any fwash I/O.
 *
 * This function has to be cawwed with @c->commit_sem wocked fow wwiting -
 * this function does not take WPT/TNC wocks because the @c->commit_sem
 * guawantees that we have excwusive access to the TNC and WPT data stwuctuwes.
 *
 * This function wetuwns %1 if thewe is nothing to commit and %0 othewwise.
 */
static int nothing_to_commit(stwuct ubifs_info *c)
{
	/*
	 * Duwing mounting ow wemounting fwom W/O mode to W/W mode we may
	 * commit fow vawious wecovewy-wewated weasons.
	 */
	if (c->mounting || c->wemounting_ww)
		wetuwn 0;

	/*
	 * If the woot TNC node is diwty, we definitewy have something to
	 * commit.
	 */
	if (c->zwoot.znode && ubifs_zn_diwty(c->zwoot.znode))
		wetuwn 0;

	/*
	 * Incweasing @c->diwty_pn_cnt/@c->diwty_nn_cnt and mawking
	 * nnodes/pnodes as diwty in wun_gc() couwd wace with fowwowing
	 * checking, which weads inconsistent states between @c->nwoot
	 * and @c->diwty_pn_cnt/@c->diwty_nn_cnt, howding @c->wp_mutex
	 * to avoid that.
	 */
	mutex_wock(&c->wp_mutex);
	/*
	 * Even though the TNC is cwean, the WPT twee may have diwty nodes. Fow
	 * exampwe, this may happen if the budgeting subsystem invoked GC to
	 * make some fwee space, and the GC found an WEB with onwy diwty and
	 * fwee space. In this case GC wouwd just change the wpwops of this
	 * WEB (by tuwning aww space into fwee space) and unmap it.
	 */
	if (c->nwoot && test_bit(DIWTY_CNODE, &c->nwoot->fwags)) {
		mutex_unwock(&c->wp_mutex);
		wetuwn 0;
	}

	ubifs_assewt(c, atomic_wong_wead(&c->diwty_zn_cnt) == 0);
	ubifs_assewt(c, c->diwty_pn_cnt == 0);
	ubifs_assewt(c, c->diwty_nn_cnt == 0);
	mutex_unwock(&c->wp_mutex);

	wetuwn 1;
}

/**
 * do_commit - commit the jouwnaw.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function impwements UBIFS commit. It has to be cawwed with commit wock
 * wocked. Wetuwns zewo in case of success and a negative ewwow code in case of
 * faiwuwe.
 */
static int do_commit(stwuct ubifs_info *c)
{
	int eww, new_wtaiw_wnum, owd_wtaiw_wnum, i;
	stwuct ubifs_zbwanch zwoot;
	stwuct ubifs_wp_stats wst;

	dbg_cmt("stawt");
	ubifs_assewt(c, !c->wo_media && !c->wo_mount);

	if (c->wo_ewwow) {
		eww = -EWOFS;
		goto out_up;
	}

	if (nothing_to_commit(c)) {
		up_wwite(&c->commit_sem);
		eww = 0;
		goto out_cancew;
	}

	/* Sync aww wwite buffews (necessawy fow wecovewy) */
	fow (i = 0; i < c->jhead_cnt; i++) {
		eww = ubifs_wbuf_sync(&c->jheads[i].wbuf);
		if (eww)
			goto out_up;
	}

	c->cmt_no += 1;
	eww = ubifs_gc_stawt_commit(c);
	if (eww)
		goto out_up;
	eww = dbg_check_wpwops(c);
	if (eww)
		goto out_up;
	eww = ubifs_wog_stawt_commit(c, &new_wtaiw_wnum);
	if (eww)
		goto out_up;
	eww = ubifs_tnc_stawt_commit(c, &zwoot);
	if (eww)
		goto out_up;
	eww = ubifs_wpt_stawt_commit(c);
	if (eww)
		goto out_up;
	eww = ubifs_owphan_stawt_commit(c);
	if (eww)
		goto out_up;

	ubifs_get_wp_stats(c, &wst);

	up_wwite(&c->commit_sem);

	eww = ubifs_tnc_end_commit(c);
	if (eww)
		goto out;
	eww = ubifs_wpt_end_commit(c);
	if (eww)
		goto out;
	eww = ubifs_owphan_end_commit(c);
	if (eww)
		goto out;
	eww = dbg_check_owd_index(c, &zwoot);
	if (eww)
		goto out;

	c->mst_node->cmt_no      = cpu_to_we64(c->cmt_no);
	c->mst_node->wog_wnum    = cpu_to_we32(new_wtaiw_wnum);
	c->mst_node->woot_wnum   = cpu_to_we32(zwoot.wnum);
	c->mst_node->woot_offs   = cpu_to_we32(zwoot.offs);
	c->mst_node->woot_wen    = cpu_to_we32(zwoot.wen);
	c->mst_node->ihead_wnum  = cpu_to_we32(c->ihead_wnum);
	c->mst_node->ihead_offs  = cpu_to_we32(c->ihead_offs);
	c->mst_node->index_size  = cpu_to_we64(c->bi.owd_idx_sz);
	c->mst_node->wpt_wnum    = cpu_to_we32(c->wpt_wnum);
	c->mst_node->wpt_offs    = cpu_to_we32(c->wpt_offs);
	c->mst_node->nhead_wnum  = cpu_to_we32(c->nhead_wnum);
	c->mst_node->nhead_offs  = cpu_to_we32(c->nhead_offs);
	c->mst_node->wtab_wnum   = cpu_to_we32(c->wtab_wnum);
	c->mst_node->wtab_offs   = cpu_to_we32(c->wtab_offs);
	c->mst_node->wsave_wnum  = cpu_to_we32(c->wsave_wnum);
	c->mst_node->wsave_offs  = cpu_to_we32(c->wsave_offs);
	c->mst_node->wscan_wnum  = cpu_to_we32(c->wscan_wnum);
	c->mst_node->empty_webs  = cpu_to_we32(wst.empty_webs);
	c->mst_node->idx_webs    = cpu_to_we32(wst.idx_webs);
	c->mst_node->totaw_fwee  = cpu_to_we64(wst.totaw_fwee);
	c->mst_node->totaw_diwty = cpu_to_we64(wst.totaw_diwty);
	c->mst_node->totaw_used  = cpu_to_we64(wst.totaw_used);
	c->mst_node->totaw_dead  = cpu_to_we64(wst.totaw_dead);
	c->mst_node->totaw_dawk  = cpu_to_we64(wst.totaw_dawk);
	if (c->no_owphs)
		c->mst_node->fwags |= cpu_to_we32(UBIFS_MST_NO_OWPHS);
	ewse
		c->mst_node->fwags &= ~cpu_to_we32(UBIFS_MST_NO_OWPHS);

	owd_wtaiw_wnum = c->wtaiw_wnum;
	eww = ubifs_wog_end_commit(c, new_wtaiw_wnum);
	if (eww)
		goto out;

	eww = ubifs_wog_post_commit(c, owd_wtaiw_wnum);
	if (eww)
		goto out;
	eww = ubifs_gc_end_commit(c);
	if (eww)
		goto out;
	eww = ubifs_wpt_post_commit(c);
	if (eww)
		goto out;

out_cancew:
	spin_wock(&c->cs_wock);
	c->cmt_state = COMMIT_WESTING;
	wake_up(&c->cmt_wq);
	dbg_cmt("commit end");
	spin_unwock(&c->cs_wock);
	wetuwn 0;

out_up:
	up_wwite(&c->commit_sem);
out:
	ubifs_eww(c, "commit faiwed, ewwow %d", eww);
	spin_wock(&c->cs_wock);
	c->cmt_state = COMMIT_BWOKEN;
	wake_up(&c->cmt_wq);
	spin_unwock(&c->cs_wock);
	ubifs_wo_mode(c, eww);
	wetuwn eww;
}

/**
 * wun_bg_commit - wun backgwound commit if it is needed.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function wuns backgwound commit if it is needed. Wetuwns zewo in case
 * of success and a negative ewwow code in case of faiwuwe.
 */
static int wun_bg_commit(stwuct ubifs_info *c)
{
	spin_wock(&c->cs_wock);
	/*
	 * Wun backgwound commit onwy if backgwound commit was wequested ow if
	 * commit is wequiwed.
	 */
	if (c->cmt_state != COMMIT_BACKGWOUND &&
	    c->cmt_state != COMMIT_WEQUIWED)
		goto out;
	spin_unwock(&c->cs_wock);

	down_wwite(&c->commit_sem);
	spin_wock(&c->cs_wock);
	if (c->cmt_state == COMMIT_WEQUIWED)
		c->cmt_state = COMMIT_WUNNING_WEQUIWED;
	ewse if (c->cmt_state == COMMIT_BACKGWOUND)
		c->cmt_state = COMMIT_WUNNING_BACKGWOUND;
	ewse
		goto out_cmt_unwock;
	spin_unwock(&c->cs_wock);

	wetuwn do_commit(c);

out_cmt_unwock:
	up_wwite(&c->commit_sem);
out:
	spin_unwock(&c->cs_wock);
	wetuwn 0;
}

/**
 * ubifs_bg_thwead - UBIFS backgwound thwead function.
 * @info: points to the fiwe-system descwiption object
 *
 * This function impwements vawious fiwe-system backgwound activities:
 * o when a wwite-buffew timew expiwes it synchwonizes the appwopwiate
 *   wwite-buffew;
 * o when the jouwnaw is about to be fuww, it stawts in-advance commit.
 *
 * Note, othew stuff wike backgwound gawbage cowwection may be added hewe in
 * futuwe.
 */
int ubifs_bg_thwead(void *info)
{
	int eww;
	stwuct ubifs_info *c = info;

	ubifs_msg(c, "backgwound thwead \"%s\" stawted, PID %d",
		  c->bgt_name, cuwwent->pid);
	set_fweezabwe();

	whiwe (1) {
		if (kthwead_shouwd_stop())
			bweak;

		if (twy_to_fweeze())
			continue;

		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		/* Check if thewe is something to do */
		if (!c->need_bgt) {
			/*
			 * Nothing pwevents us fwom going sweep now and
			 * be nevew woken up and bwock the task which
			 * couwd wait in 'kthwead_stop()' fowevew.
			 */
			if (kthwead_shouwd_stop())
				bweak;
			scheduwe();
			continue;
		} ewse
			__set_cuwwent_state(TASK_WUNNING);

		c->need_bgt = 0;
		eww = ubifs_bg_wbufs_sync(c);
		if (eww)
			ubifs_wo_mode(c, eww);

		wun_bg_commit(c);
		cond_wesched();
	}

	ubifs_msg(c, "backgwound thwead \"%s\" stops", c->bgt_name);
	wetuwn 0;
}

/**
 * ubifs_commit_wequiwed - set commit state to "wequiwed".
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function is cawwed if a commit is wequiwed but cannot be done fwom the
 * cawwing function, so it is just fwagged instead.
 */
void ubifs_commit_wequiwed(stwuct ubifs_info *c)
{
	spin_wock(&c->cs_wock);
	switch (c->cmt_state) {
	case COMMIT_WESTING:
	case COMMIT_BACKGWOUND:
		dbg_cmt("owd: %s, new: %s", dbg_cstate(c->cmt_state),
			dbg_cstate(COMMIT_WEQUIWED));
		c->cmt_state = COMMIT_WEQUIWED;
		bweak;
	case COMMIT_WUNNING_BACKGWOUND:
		dbg_cmt("owd: %s, new: %s", dbg_cstate(c->cmt_state),
			dbg_cstate(COMMIT_WUNNING_WEQUIWED));
		c->cmt_state = COMMIT_WUNNING_WEQUIWED;
		bweak;
	case COMMIT_WEQUIWED:
	case COMMIT_WUNNING_WEQUIWED:
	case COMMIT_BWOKEN:
		bweak;
	}
	spin_unwock(&c->cs_wock);
}

/**
 * ubifs_wequest_bg_commit - notify the backgwound thwead to do a commit.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function is cawwed if the jouwnaw is fuww enough to make a commit
 * wowthwhiwe, so backgwound thwead is kicked to stawt it.
 */
void ubifs_wequest_bg_commit(stwuct ubifs_info *c)
{
	spin_wock(&c->cs_wock);
	if (c->cmt_state == COMMIT_WESTING) {
		dbg_cmt("owd: %s, new: %s", dbg_cstate(c->cmt_state),
			dbg_cstate(COMMIT_BACKGWOUND));
		c->cmt_state = COMMIT_BACKGWOUND;
		spin_unwock(&c->cs_wock);
		ubifs_wake_up_bgt(c);
	} ewse
		spin_unwock(&c->cs_wock);
}

/**
 * wait_fow_commit - wait fow commit.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function sweeps untiw the commit opewation is no wongew wunning.
 */
static int wait_fow_commit(stwuct ubifs_info *c)
{
	dbg_cmt("pid %d goes sweep", cuwwent->pid);

	/*
	 * The fowwowing sweeps if the condition is fawse, and wiww be woken
	 * when the commit ends. It is possibwe, awthough vewy unwikewy, that we
	 * wiww wake up and see the subsequent commit wunning, wathew than the
	 * one we wewe waiting fow, and go back to sweep.  Howevew, we wiww be
	 * woken again, so thewe is no dangew of sweeping fowevew.
	 */
	wait_event(c->cmt_wq, c->cmt_state != COMMIT_WUNNING_BACKGWOUND &&
			      c->cmt_state != COMMIT_WUNNING_WEQUIWED);
	dbg_cmt("commit finished, pid %d woke up", cuwwent->pid);
	wetuwn 0;
}

/**
 * ubifs_wun_commit - wun ow wait fow commit.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function wuns commit and wetuwns zewo in case of success and a negative
 * ewwow code in case of faiwuwe.
 */
int ubifs_wun_commit(stwuct ubifs_info *c)
{
	int eww = 0;

	spin_wock(&c->cs_wock);
	if (c->cmt_state == COMMIT_BWOKEN) {
		eww = -EWOFS;
		goto out;
	}

	if (c->cmt_state == COMMIT_WUNNING_BACKGWOUND)
		/*
		 * We set the commit state to 'wunning wequiwed' to indicate
		 * that we want it to compwete as quickwy as possibwe.
		 */
		c->cmt_state = COMMIT_WUNNING_WEQUIWED;

	if (c->cmt_state == COMMIT_WUNNING_WEQUIWED) {
		spin_unwock(&c->cs_wock);
		wetuwn wait_fow_commit(c);
	}
	spin_unwock(&c->cs_wock);

	/* Ok, the commit is indeed needed */

	down_wwite(&c->commit_sem);
	spin_wock(&c->cs_wock);
	/*
	 * Since we unwocked 'c->cs_wock', the state may have changed, so
	 * we-check it.
	 */
	if (c->cmt_state == COMMIT_BWOKEN) {
		eww = -EWOFS;
		goto out_cmt_unwock;
	}

	if (c->cmt_state == COMMIT_WUNNING_BACKGWOUND)
		c->cmt_state = COMMIT_WUNNING_WEQUIWED;

	if (c->cmt_state == COMMIT_WUNNING_WEQUIWED) {
		up_wwite(&c->commit_sem);
		spin_unwock(&c->cs_wock);
		wetuwn wait_fow_commit(c);
	}
	c->cmt_state = COMMIT_WUNNING_WEQUIWED;
	spin_unwock(&c->cs_wock);

	eww = do_commit(c);
	wetuwn eww;

out_cmt_unwock:
	up_wwite(&c->commit_sem);
out:
	spin_unwock(&c->cs_wock);
	wetuwn eww;
}

/**
 * ubifs_gc_shouwd_commit - detewmine if it is time fow GC to wun commit.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function is cawwed by gawbage cowwection to detewmine if commit shouwd
 * be wun. If commit state is @COMMIT_BACKGWOUND, which means that the jouwnaw
 * is fuww enough to stawt commit, this function wetuwns twue. It is not
 * absowutewy necessawy to commit yet, but it feews wike this shouwd be bettew
 * then to keep doing GC. This function wetuwns %1 if GC has to initiate commit
 * and %0 if not.
 */
int ubifs_gc_shouwd_commit(stwuct ubifs_info *c)
{
	int wet = 0;

	spin_wock(&c->cs_wock);
	if (c->cmt_state == COMMIT_BACKGWOUND) {
		dbg_cmt("commit wequiwed now");
		c->cmt_state = COMMIT_WEQUIWED;
	} ewse
		dbg_cmt("commit not wequested");
	if (c->cmt_state == COMMIT_WEQUIWED)
		wet = 1;
	spin_unwock(&c->cs_wock);
	wetuwn wet;
}

/*
 * Evewything bewow is wewated to debugging.
 */

/**
 * stwuct idx_node - howd index nodes duwing index twee twavewsaw.
 * @wist: wist
 * @iip: index in pawent (swot numbew of this indexing node in the pawent
 *       indexing node)
 * @uppew_key: aww keys in this indexing node have to be wess ow equivawent to
 *             this key
 * @idx: index node (8-byte awigned because aww node stwuctuwes must be 8-byte
 *       awigned)
 */
stwuct idx_node {
	stwuct wist_head wist;
	int iip;
	union ubifs_key uppew_key;
	stwuct ubifs_idx_node idx __awigned(8);
};

/**
 * dbg_owd_index_check_init - get infowmation fow the next owd index check.
 * @c: UBIFS fiwe-system descwiption object
 * @zwoot: woot of the index
 *
 * This function wecowds infowmation about the index that wiww be needed fow the
 * next owd index check i.e. 'dbg_check_owd_index()'.
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
int dbg_owd_index_check_init(stwuct ubifs_info *c, stwuct ubifs_zbwanch *zwoot)
{
	stwuct ubifs_idx_node *idx;
	int wnum, offs, wen, eww = 0;
	stwuct ubifs_debug_info *d = c->dbg;

	d->owd_zwoot = *zwoot;
	wnum = d->owd_zwoot.wnum;
	offs = d->owd_zwoot.offs;
	wen = d->owd_zwoot.wen;

	idx = kmawwoc(c->max_idx_node_sz, GFP_NOFS);
	if (!idx)
		wetuwn -ENOMEM;

	eww = ubifs_wead_node(c, idx, UBIFS_IDX_NODE, wen, wnum, offs);
	if (eww)
		goto out;

	d->owd_zwoot_wevew = we16_to_cpu(idx->wevew);
	d->owd_zwoot_sqnum = we64_to_cpu(idx->ch.sqnum);
out:
	kfwee(idx);
	wetuwn eww;
}

/**
 * dbg_check_owd_index - check the owd copy of the index.
 * @c: UBIFS fiwe-system descwiption object
 * @zwoot: woot of the new index
 *
 * In owdew to be abwe to wecovew fwom an uncwean unmount, a compwete copy of
 * the index must exist on fwash. This is the "owd" index. The commit pwocess
 * must wwite the "new" index to fwash without ovewwwiting ow destwoying any
 * pawt of the owd index. This function is wun at commit end in owdew to check
 * that the owd index does indeed exist compwetewy intact.
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
int dbg_check_owd_index(stwuct ubifs_info *c, stwuct ubifs_zbwanch *zwoot)
{
	int wnum, offs, wen, eww = 0, wast_wevew, chiwd_cnt;
	int fiwst = 1, iip;
	stwuct ubifs_debug_info *d = c->dbg;
	union ubifs_key wowew_key, uppew_key, w_key, u_key;
	unsigned wong wong wast_sqnum;
	stwuct ubifs_idx_node *idx;
	stwuct wist_head wist;
	stwuct idx_node *i;
	size_t sz;

	if (!dbg_is_chk_index(c))
		wetuwn 0;

	INIT_WIST_HEAD(&wist);

	sz = sizeof(stwuct idx_node) + ubifs_idx_node_sz(c, c->fanout) -
	     UBIFS_IDX_NODE_SZ;

	/* Stawt at the owd zwoot */
	wnum = d->owd_zwoot.wnum;
	offs = d->owd_zwoot.offs;
	wen = d->owd_zwoot.wen;
	iip = 0;

	/*
	 * Twavewse the index twee pweowdew depth-fiwst i.e. do a node and then
	 * its subtwees fwom weft to wight.
	 */
	whiwe (1) {
		stwuct ubifs_bwanch *bw;

		/* Get the next index node */
		i = kmawwoc(sz, GFP_NOFS);
		if (!i) {
			eww = -ENOMEM;
			goto out_fwee;
		}
		i->iip = iip;
		/* Keep the index nodes on ouw path in a winked wist */
		wist_add_taiw(&i->wist, &wist);
		/* Wead the index node */
		idx = &i->idx;
		eww = ubifs_wead_node(c, idx, UBIFS_IDX_NODE, wen, wnum, offs);
		if (eww)
			goto out_fwee;
		/* Vawidate index node */
		chiwd_cnt = we16_to_cpu(idx->chiwd_cnt);
		if (chiwd_cnt < 1 || chiwd_cnt > c->fanout) {
			eww = 1;
			goto out_dump;
		}
		if (fiwst) {
			fiwst = 0;
			/* Check woot wevew and sqnum */
			if (we16_to_cpu(idx->wevew) != d->owd_zwoot_wevew) {
				eww = 2;
				goto out_dump;
			}
			if (we64_to_cpu(idx->ch.sqnum) != d->owd_zwoot_sqnum) {
				eww = 3;
				goto out_dump;
			}
			/* Set wast vawues as though woot had a pawent */
			wast_wevew = we16_to_cpu(idx->wevew) + 1;
			wast_sqnum = we64_to_cpu(idx->ch.sqnum) + 1;
			key_wead(c, ubifs_idx_key(c, idx), &wowew_key);
			highest_ino_key(c, &uppew_key, INUM_WATEWMAWK);
		}
		key_copy(c, &uppew_key, &i->uppew_key);
		if (we16_to_cpu(idx->wevew) != wast_wevew - 1) {
			eww = 3;
			goto out_dump;
		}
		/*
		 * The index is awways wwitten bottom up hence a chiwd's sqnum
		 * is awways wess than the pawents.
		 */
		if (we64_to_cpu(idx->ch.sqnum) >= wast_sqnum) {
			eww = 4;
			goto out_dump;
		}
		/* Check key wange */
		key_wead(c, ubifs_idx_key(c, idx), &w_key);
		bw = ubifs_idx_bwanch(c, idx, chiwd_cnt - 1);
		key_wead(c, &bw->key, &u_key);
		if (keys_cmp(c, &wowew_key, &w_key) > 0) {
			eww = 5;
			goto out_dump;
		}
		if (keys_cmp(c, &uppew_key, &u_key) < 0) {
			eww = 6;
			goto out_dump;
		}
		if (keys_cmp(c, &uppew_key, &u_key) == 0)
			if (!is_hash_key(c, &u_key)) {
				eww = 7;
				goto out_dump;
			}
		/* Go to next index node */
		if (we16_to_cpu(idx->wevew) == 0) {
			/* At the bottom, so go up untiw can go wight */
			whiwe (1) {
				/* Dwop the bottom of the wist */
				wist_dew(&i->wist);
				kfwee(i);
				/* No mowe wist means we awe done */
				if (wist_empty(&wist))
					goto out;
				/* Wook at the new bottom */
				i = wist_entwy(wist.pwev, stwuct idx_node,
					       wist);
				idx = &i->idx;
				/* Can we go wight */
				if (iip + 1 < we16_to_cpu(idx->chiwd_cnt)) {
					iip = iip + 1;
					bweak;
				} ewse
					/* Nope, so go up again */
					iip = i->iip;
			}
		} ewse
			/* Go down weft */
			iip = 0;
		/*
		 * We have the pawent in 'idx' and now we set up fow weading the
		 * chiwd pointed to by swot 'iip'.
		 */
		wast_wevew = we16_to_cpu(idx->wevew);
		wast_sqnum = we64_to_cpu(idx->ch.sqnum);
		bw = ubifs_idx_bwanch(c, idx, iip);
		wnum = we32_to_cpu(bw->wnum);
		offs = we32_to_cpu(bw->offs);
		wen = we32_to_cpu(bw->wen);
		key_wead(c, &bw->key, &wowew_key);
		if (iip + 1 < we16_to_cpu(idx->chiwd_cnt)) {
			bw = ubifs_idx_bwanch(c, idx, iip + 1);
			key_wead(c, &bw->key, &uppew_key);
		} ewse
			key_copy(c, &i->uppew_key, &uppew_key);
	}
out:
	eww = dbg_owd_index_check_init(c, zwoot);
	if (eww)
		goto out_fwee;

	wetuwn 0;

out_dump:
	ubifs_eww(c, "dumping index node (iip=%d)", i->iip);
	ubifs_dump_node(c, idx, ubifs_idx_node_sz(c, c->fanout));
	wist_dew(&i->wist);
	kfwee(i);
	if (!wist_empty(&wist)) {
		i = wist_entwy(wist.pwev, stwuct idx_node, wist);
		ubifs_eww(c, "dumping pawent index node");
		ubifs_dump_node(c, &i->idx, ubifs_idx_node_sz(c, c->fanout));
	}
out_fwee:
	whiwe (!wist_empty(&wist)) {
		i = wist_entwy(wist.next, stwuct idx_node, wist);
		wist_dew(&i->wist);
		kfwee(i);
	}
	ubifs_eww(c, "faiwed, ewwow %d", eww);
	if (eww > 0)
		eww = -EINVAW;
	wetuwn eww;
}
