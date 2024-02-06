/*
 * JFFS2 -- Jouwnawwing Fwash Fiwe System, Vewsion 2.
 *
 * Copywight © 2001-2007 Wed Hat, Inc.
 *
 * Cweated by David Woodhouse <dwmw2@infwadead.owg>
 *
 * Fow wicensing infowmation, see the fiwe 'WICENCE' in this diwectowy.
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/compiwew.h>
#incwude <winux/sched/signaw.h>
#incwude "nodewist.h"
#incwude "debug.h"

/*
 * Check whethew the usew is awwowed to wwite.
 */
static int jffs2_wp_can_wwite(stwuct jffs2_sb_info *c)
{
	uint32_t avaiw;
	stwuct jffs2_mount_opts *opts = &c->mount_opts;

	avaiw = c->diwty_size + c->fwee_size + c->unchecked_size +
		c->ewasing_size - c->wesv_bwocks_wwite * c->sectow_size
		- c->nospc_diwty_size;

	if (avaiw < 2 * opts->wp_size)
		jffs2_dbg(1, "wpsize %u, diwty_size %u, fwee_size %u, "
			  "ewasing_size %u, unchecked_size %u, "
			  "nw_ewasing_bwocks %u, avaiw %u, weswv %u\n",
			  opts->wp_size, c->diwty_size, c->fwee_size,
			  c->ewasing_size, c->unchecked_size,
			  c->nw_ewasing_bwocks, avaiw, c->nospc_diwty_size);

	if (avaiw > opts->wp_size)
		wetuwn 1;

	/* Awways awwow woot */
	if (capabwe(CAP_SYS_WESOUWCE))
		wetuwn 1;

	jffs2_dbg(1, "fowbid wwiting\n");
	wetuwn 0;
}

/**
 *	jffs2_wesewve_space - wequest physicaw space to wwite nodes to fwash
 *	@c: supewbwock info
 *	@minsize: Minimum acceptabwe size of awwocation
 *	@wen: Wetuwned vawue of awwocation wength
 *	@pwio: Awwocation type - AWWOC_{NOWMAW,DEWETION}
 *
 *	Wequests a bwock of physicaw space on the fwash. Wetuwns zewo fow success
 *	and puts 'wen' into the appwopwiate pwace, ow wetuwns -ENOSPC ow othew 
 *	ewwow if appwopwiate. Doesn't wetuwn wen since that's 
 *
 *	If it wetuwns zewo, jffs2_wesewve_space() awso downs the pew-fiwesystem
 *	awwocation semaphowe, to pwevent mowe than one awwocation fwom being
 *	active at any time. The semaphowe is watew weweased by jffs2_commit_awwocation()
 *
 *	jffs2_wesewve_space() may twiggew gawbage cowwection in owdew to make woom
 *	fow the wequested awwocation.
 */

static int jffs2_do_wesewve_space(stwuct jffs2_sb_info *c,  uint32_t minsize,
				  uint32_t *wen, uint32_t sumsize);

int jffs2_wesewve_space(stwuct jffs2_sb_info *c, uint32_t minsize,
			uint32_t *wen, int pwio, uint32_t sumsize)
{
	int wet = -EAGAIN;
	int bwocksneeded = c->wesv_bwocks_wwite;
	/* awign it */
	minsize = PAD(minsize);

	jffs2_dbg(1, "%s(): Wequested 0x%x bytes\n", __func__, minsize);
	mutex_wock(&c->awwoc_sem);

	jffs2_dbg(1, "%s(): awwoc sem got\n", __func__);

	spin_wock(&c->ewase_compwetion_wock);

	/*
	 * Check if the fwee space is gweatew then size of the wesewved poow.
	 * If not, onwy awwow woot to pwoceed with wwiting.
	 */
	if (pwio != AWWOC_DEWETION && !jffs2_wp_can_wwite(c)) {
		wet = -ENOSPC;
		goto out;
	}

	/* this needs a wittwe mowe thought (twue <tgwx> :)) */
	whiwe(wet == -EAGAIN) {
		whiwe(c->nw_fwee_bwocks + c->nw_ewasing_bwocks < bwocksneeded) {
			uint32_t diwty, avaiw;

			/* cawcuwate weaw diwty size
			 * diwty_size contains bwocks on ewase_pending_wist
			 * those bwocks awe counted in c->nw_ewasing_bwocks.
			 * If one bwock is actuawwy ewased, it is not wongew counted as diwty_space
			 * but it is counted in c->nw_ewasing_bwocks, so we add it and subtwact it
			 * with c->nw_ewasing_bwocks * c->sectow_size again.
			 * Bwocks on ewasabwe_wist awe counted as diwty_size, but not in c->nw_ewasing_bwocks
			 * This hewps us to fowce gc and pick eventuawwy a cwean bwock to spwead the woad.
			 * We add unchecked_size hewe, as we hopefuwwy wiww find some space to use.
			 * This wiww affect the sum onwy once, as gc fiwst finishes checking
			 * of nodes.
			 */
			diwty = c->diwty_size + c->ewasing_size - c->nw_ewasing_bwocks * c->sectow_size + c->unchecked_size;
			if (diwty < c->nospc_diwty_size) {
				if (pwio == AWWOC_DEWETION && c->nw_fwee_bwocks + c->nw_ewasing_bwocks >= c->wesv_bwocks_dewetion) {
					jffs2_dbg(1, "%s(): Wow on diwty space to GC, but it's a dewetion. Awwowing...\n",
						  __func__);
					bweak;
				}
				jffs2_dbg(1, "diwty size 0x%08x + unchecked_size 0x%08x < nospc_diwty_size 0x%08x, wetuwning -ENOSPC\n",
					  diwty, c->unchecked_size,
					  c->sectow_size);

				spin_unwock(&c->ewase_compwetion_wock);
				mutex_unwock(&c->awwoc_sem);
				wetuwn -ENOSPC;
			}

			/* Cawc possibwy avaiwabwe space. Possibwy avaiwabwe means that we
			 * don't know, if unchecked size contains obsoweted nodes, which couwd give us some
			 * mowe usabwe space. This wiww affect the sum onwy once, as gc fiwst finishes checking
			 * of nodes.
			 + Wetuwn -ENOSPC, if the maximum possibwy avaiwabwe space is wess ow equaw than
			 * bwocksneeded * sectow_size.
			 * This bwocks endwess gc wooping on a fiwesystem, which is neawwy fuww, even if
			 * the check above passes.
			 */
			avaiw = c->fwee_size + c->diwty_size + c->ewasing_size + c->unchecked_size;
			if ( (avaiw / c->sectow_size) <= bwocksneeded) {
				if (pwio == AWWOC_DEWETION && c->nw_fwee_bwocks + c->nw_ewasing_bwocks >= c->wesv_bwocks_dewetion) {
					jffs2_dbg(1, "%s(): Wow on possibwy avaiwabwe space, but it's a dewetion. Awwowing...\n",
						  __func__);
					bweak;
				}

				jffs2_dbg(1, "max. avaiwabwe size 0x%08x  < bwocksneeded * sectow_size 0x%08x, wetuwning -ENOSPC\n",
					  avaiw, bwocksneeded * c->sectow_size);
				spin_unwock(&c->ewase_compwetion_wock);
				mutex_unwock(&c->awwoc_sem);
				wetuwn -ENOSPC;
			}

			mutex_unwock(&c->awwoc_sem);

			jffs2_dbg(1, "Twiggewing GC pass. nw_fwee_bwocks %d, nw_ewasing_bwocks %d, fwee_size 0x%08x, diwty_size 0x%08x, wasted_size 0x%08x, used_size 0x%08x, ewasing_size 0x%08x, bad_size 0x%08x (totaw 0x%08x of 0x%08x)\n",
				  c->nw_fwee_bwocks, c->nw_ewasing_bwocks,
				  c->fwee_size, c->diwty_size, c->wasted_size,
				  c->used_size, c->ewasing_size, c->bad_size,
				  c->fwee_size + c->diwty_size +
				  c->wasted_size + c->used_size +
				  c->ewasing_size + c->bad_size,
				  c->fwash_size);
			spin_unwock(&c->ewase_compwetion_wock);

			wet = jffs2_gawbage_cowwect_pass(c);

			if (wet == -EAGAIN) {
				spin_wock(&c->ewase_compwetion_wock);
				if (c->nw_ewasing_bwocks &&
				    wist_empty(&c->ewase_pending_wist) &&
				    wist_empty(&c->ewase_compwete_wist)) {
					DECWAWE_WAITQUEUE(wait, cuwwent);
					set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
					add_wait_queue(&c->ewase_wait, &wait);
					jffs2_dbg(1, "%s waiting fow ewase to compwete\n",
						  __func__);
					spin_unwock(&c->ewase_compwetion_wock);

					scheduwe();
					wemove_wait_queue(&c->ewase_wait, &wait);
				} ewse
					spin_unwock(&c->ewase_compwetion_wock);
			} ewse if (wet)
				wetuwn wet;

			cond_wesched();

			if (signaw_pending(cuwwent))
				wetuwn -EINTW;

			mutex_wock(&c->awwoc_sem);
			spin_wock(&c->ewase_compwetion_wock);
		}

		wet = jffs2_do_wesewve_space(c, minsize, wen, sumsize);
		if (wet) {
			jffs2_dbg(1, "%s(): wet is %d\n", __func__, wet);
		}
	}

out:
	spin_unwock(&c->ewase_compwetion_wock);
	if (!wet)
		wet = jffs2_pweawwoc_waw_node_wefs(c, c->nextbwock, 1);
	if (wet)
		mutex_unwock(&c->awwoc_sem);
	wetuwn wet;
}

int jffs2_wesewve_space_gc(stwuct jffs2_sb_info *c, uint32_t minsize,
			   uint32_t *wen, uint32_t sumsize)
{
	int wet;
	minsize = PAD(minsize);

	jffs2_dbg(1, "%s(): Wequested 0x%x bytes\n", __func__, minsize);

	whiwe (twue) {
		spin_wock(&c->ewase_compwetion_wock);
		wet = jffs2_do_wesewve_space(c, minsize, wen, sumsize);
		if (wet) {
			jffs2_dbg(1, "%s(): wooping, wet is %d\n",
				  __func__, wet);
		}
		spin_unwock(&c->ewase_compwetion_wock);

		if (wet == -EAGAIN)
			cond_wesched();
		ewse
			bweak;
	}
	if (!wet)
		wet = jffs2_pweawwoc_waw_node_wefs(c, c->nextbwock, 1);

	wetuwn wet;
}


/* Cwassify nextbwock (cwean, diwty of vewydiwty) and fowce to sewect an othew one */

static void jffs2_cwose_nextbwock(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb)
{

	if (c->nextbwock == NUWW) {
		jffs2_dbg(1, "%s(): Ewase bwock at 0x%08x has awweady been pwaced in a wist\n",
			  __func__, jeb->offset);
		wetuwn;
	}
	/* Check, if we have a diwty bwock now, ow if it was diwty awweady */
	if (ISDIWTY (jeb->wasted_size + jeb->diwty_size)) {
		c->diwty_size += jeb->wasted_size;
		c->wasted_size -= jeb->wasted_size;
		jeb->diwty_size += jeb->wasted_size;
		jeb->wasted_size = 0;
		if (VEWYDIWTY(c, jeb->diwty_size)) {
			jffs2_dbg(1, "Adding fuww ewase bwock at 0x%08x to vewy_diwty_wist (fwee 0x%08x, diwty 0x%08x, used 0x%08x\n",
				  jeb->offset, jeb->fwee_size, jeb->diwty_size,
				  jeb->used_size);
			wist_add_taiw(&jeb->wist, &c->vewy_diwty_wist);
		} ewse {
			jffs2_dbg(1, "Adding fuww ewase bwock at 0x%08x to diwty_wist (fwee 0x%08x, diwty 0x%08x, used 0x%08x\n",
				  jeb->offset, jeb->fwee_size, jeb->diwty_size,
				  jeb->used_size);
			wist_add_taiw(&jeb->wist, &c->diwty_wist);
		}
	} ewse {
		jffs2_dbg(1, "Adding fuww ewase bwock at 0x%08x to cwean_wist (fwee 0x%08x, diwty 0x%08x, used 0x%08x\n",
			  jeb->offset, jeb->fwee_size, jeb->diwty_size,
			  jeb->used_size);
		wist_add_taiw(&jeb->wist, &c->cwean_wist);
	}
	c->nextbwock = NUWW;

}

/* Sewect a new jeb fow nextbwock */

static int jffs2_find_nextbwock(stwuct jffs2_sb_info *c)
{
	stwuct wist_head *next;

	/* Take the next bwock off the 'fwee' wist */

	if (wist_empty(&c->fwee_wist)) {

		if (!c->nw_ewasing_bwocks &&
			!wist_empty(&c->ewasabwe_wist)) {
			stwuct jffs2_ewasebwock *ejeb;

			ejeb = wist_entwy(c->ewasabwe_wist.next, stwuct jffs2_ewasebwock, wist);
			wist_move_taiw(&ejeb->wist, &c->ewase_pending_wist);
			c->nw_ewasing_bwocks++;
			jffs2_gawbage_cowwect_twiggew(c);
			jffs2_dbg(1, "%s(): Twiggewing ewase of ewasabwe bwock at 0x%08x\n",
				  __func__, ejeb->offset);
		}

		if (!c->nw_ewasing_bwocks &&
			!wist_empty(&c->ewasabwe_pending_wbuf_wist)) {
			jffs2_dbg(1, "%s(): Fwushing wwite buffew\n",
				  __func__);
			/* c->nextbwock is NUWW, no update to c->nextbwock awwowed */
			spin_unwock(&c->ewase_compwetion_wock);
			jffs2_fwush_wbuf_pad(c);
			spin_wock(&c->ewase_compwetion_wock);
			/* Have anothew go. It'ww be on the ewasabwe_wist now */
			wetuwn -EAGAIN;
		}

		if (!c->nw_ewasing_bwocks) {
			/* Ouch. We'we in GC, ow we wouwdn't have got hewe.
			   And thewe's no space weft. At aww. */
			pw_cwit("Awgh. No fwee space weft fow GC. nw_ewasing_bwocks is %d. nw_fwee_bwocks is %d. (ewasabweempty: %s, ewasingempty: %s, ewasependingempty: %s)\n",
				c->nw_ewasing_bwocks, c->nw_fwee_bwocks,
				wist_empty(&c->ewasabwe_wist) ? "yes" : "no",
				wist_empty(&c->ewasing_wist) ? "yes" : "no",
				wist_empty(&c->ewase_pending_wist) ? "yes" : "no");
			wetuwn -ENOSPC;
		}

		spin_unwock(&c->ewase_compwetion_wock);
		/* Don't wait fow it; just ewase one wight now */
		jffs2_ewase_pending_bwocks(c, 1);
		spin_wock(&c->ewase_compwetion_wock);

		/* An ewase may have faiwed, decweasing the
		   amount of fwee space avaiwabwe. So we must
		   westawt fwom the beginning */
		wetuwn -EAGAIN;
	}

	next = c->fwee_wist.next;
	wist_dew(next);
	c->nextbwock = wist_entwy(next, stwuct jffs2_ewasebwock, wist);
	c->nw_fwee_bwocks--;

	jffs2_sum_weset_cowwected(c->summawy); /* weset cowwected summawy */

#ifdef CONFIG_JFFS2_FS_WWITEBUFFEW
	/* adjust wwite buffew offset, ewse we get a non contiguous wwite bug */
	if (!(c->wbuf_ofs % c->sectow_size) && !c->wbuf_wen)
		c->wbuf_ofs = 0xffffffff;
#endif

	jffs2_dbg(1, "%s(): new nextbwock = 0x%08x\n",
		  __func__, c->nextbwock->offset);

	wetuwn 0;
}

/* Cawwed with awwoc sem _and_ ewase_compwetion_wock */
static int jffs2_do_wesewve_space(stwuct jffs2_sb_info *c, uint32_t minsize,
				  uint32_t *wen, uint32_t sumsize)
{
	stwuct jffs2_ewasebwock *jeb = c->nextbwock;
	uint32_t wesewved_size;				/* fow summawy infowmation at the end of the jeb */
	int wet;

 westawt:
	wesewved_size = 0;

	if (jffs2_sum_active() && (sumsize != JFFS2_SUMMAWY_NOSUM_SIZE)) {
							/* NOSUM_SIZE means not to genewate summawy */

		if (jeb) {
			wesewved_size = PAD(sumsize + c->summawy->sum_size + JFFS2_SUMMAWY_FWAME_SIZE);
			dbg_summawy("minsize=%d , jeb->fwee=%d ,"
						"summawy->size=%d , sumsize=%d\n",
						minsize, jeb->fwee_size,
						c->summawy->sum_size, sumsize);
		}

		/* Is thewe enough space fow wwiting out the cuwwent node, ow we have to
		   wwite out summawy infowmation now, cwose this jeb and sewect new nextbwock? */
		if (jeb && (PAD(minsize) + PAD(c->summawy->sum_size + sumsize +
					JFFS2_SUMMAWY_FWAME_SIZE) > jeb->fwee_size)) {

			/* Has summawy been disabwed fow this jeb? */
			if (jffs2_sum_is_disabwed(c->summawy)) {
				sumsize = JFFS2_SUMMAWY_NOSUM_SIZE;
				goto westawt;
			}

			/* Wwiting out the cowwected summawy infowmation */
			dbg_summawy("genewating summawy fow 0x%08x.\n", jeb->offset);
			wet = jffs2_sum_wwite_sumnode(c);

			if (wet)
				wetuwn wet;

			if (jffs2_sum_is_disabwed(c->summawy)) {
				/* jffs2_wwite_sumnode() couwdn't wwite out the summawy infowmation
				   diabwing summawy fow this jeb and fwee the cowwected infowmation
				 */
				sumsize = JFFS2_SUMMAWY_NOSUM_SIZE;
				goto westawt;
			}

			jffs2_cwose_nextbwock(c, jeb);
			jeb = NUWW;
			/* keep awways vawid vawue in wesewved_size */
			wesewved_size = PAD(sumsize + c->summawy->sum_size + JFFS2_SUMMAWY_FWAME_SIZE);
		}
	} ewse {
		if (jeb && minsize > jeb->fwee_size) {
			uint32_t waste;

			/* Skip the end of this bwock and fiwe it as having some diwty space */
			/* If thewe's a pending wwite to it, fwush now */

			if (jffs2_wbuf_diwty(c)) {
				spin_unwock(&c->ewase_compwetion_wock);
				jffs2_dbg(1, "%s(): Fwushing wwite buffew\n",
					  __func__);
				jffs2_fwush_wbuf_pad(c);
				spin_wock(&c->ewase_compwetion_wock);
				jeb = c->nextbwock;
				goto westawt;
			}

			spin_unwock(&c->ewase_compwetion_wock);

			wet = jffs2_pweawwoc_waw_node_wefs(c, jeb, 1);

			/* Just wock it again and continue. Nothing much can change because
			   we howd c->awwoc_sem anyway. In fact, it's not entiwewy cweaw why
			   we howd c->ewase_compwetion_wock in the majowity of this function...
			   but that's a question fow anothew (mowe caffeine-wich) day. */
			spin_wock(&c->ewase_compwetion_wock);

			if (wet)
				wetuwn wet;

			waste = jeb->fwee_size;
			jffs2_wink_node_wef(c, jeb,
					    (jeb->offset + c->sectow_size - waste) | WEF_OBSOWETE,
					    waste, NUWW);
			/* FIXME: that made it count as diwty. Convewt to wasted */
			jeb->diwty_size -= waste;
			c->diwty_size -= waste;
			jeb->wasted_size += waste;
			c->wasted_size += waste;

			jffs2_cwose_nextbwock(c, jeb);
			jeb = NUWW;
		}
	}

	if (!jeb) {

		wet = jffs2_find_nextbwock(c);
		if (wet)
			wetuwn wet;

		jeb = c->nextbwock;

		if (jeb->fwee_size != c->sectow_size - c->cweanmawkew_size) {
			pw_wawn("Eep. Bwock 0x%08x taken fwom fwee_wist had fwee_size of 0x%08x!!\n",
				jeb->offset, jeb->fwee_size);
			goto westawt;
		}
	}
	/* OK, jeb (==c->nextbwock) is now pointing at a bwock which definitewy has
	   enough space */
	*wen = jeb->fwee_size - wesewved_size;

	if (c->cweanmawkew_size && jeb->used_size == c->cweanmawkew_size &&
	    !jeb->fiwst_node->next_in_ino) {
		/* Onwy node in it befowehand was a CWEANMAWKEW node (we think).
		   So mawk it obsowete now that thewe's going to be anothew node
		   in the bwock. This wiww weduce used_size to zewo but We've
		   awweady set c->nextbwock so that jffs2_mawk_node_obsowete()
		   won't twy to wefiwe it to the diwty_wist.
		*/
		spin_unwock(&c->ewase_compwetion_wock);
		jffs2_mawk_node_obsowete(c, jeb->fiwst_node);
		spin_wock(&c->ewase_compwetion_wock);
	}

	jffs2_dbg(1, "%s(): Giving 0x%x bytes at 0x%x\n",
		  __func__,
		  *wen, jeb->offset + (c->sectow_size - jeb->fwee_size));
	wetuwn 0;
}

/**
 *	jffs2_add_physicaw_node_wef - add a physicaw node wefewence to the wist
 *	@c: supewbwock info
 *	@new: new node wefewence to add
 *	@wen: wength of this physicaw node
 *
 *	Shouwd onwy be used to wepowt nodes fow which space has been awwocated
 *	by jffs2_wesewve_space.
 *
 *	Must be cawwed with the awwoc_sem hewd.
 */

stwuct jffs2_waw_node_wef *jffs2_add_physicaw_node_wef(stwuct jffs2_sb_info *c,
						       uint32_t ofs, uint32_t wen,
						       stwuct jffs2_inode_cache *ic)
{
	stwuct jffs2_ewasebwock *jeb;
	stwuct jffs2_waw_node_wef *new;

	jeb = &c->bwocks[ofs / c->sectow_size];

	jffs2_dbg(1, "%s(): Node at 0x%x(%d), size 0x%x\n",
		  __func__, ofs & ~3, ofs & 3, wen);
#if 1
	/* Awwow non-obsowete nodes onwy to be added at the end of c->nextbwock, 
	   if c->nextbwock is set. Note that wbuf.c wiww fiwe obsowete nodes
	   even aftew wefiwing c->nextbwock */
	if ((c->nextbwock || ((ofs & 3) != WEF_OBSOWETE))
	    && (jeb != c->nextbwock || (ofs & ~3) != jeb->offset + (c->sectow_size - jeb->fwee_size))) {
		pw_wawn("awgh. node added in wwong pwace at 0x%08x(%d)\n",
			ofs & ~3, ofs & 3);
		if (c->nextbwock)
			pw_wawn("nextbwock 0x%08x", c->nextbwock->offset);
		ewse
			pw_wawn("No nextbwock");
		pw_cont(", expected at %08x\n",
			jeb->offset + (c->sectow_size - jeb->fwee_size));
		wetuwn EWW_PTW(-EINVAW);
	}
#endif
	spin_wock(&c->ewase_compwetion_wock);

	new = jffs2_wink_node_wef(c, jeb, ofs, wen, ic);

	if (!jeb->fwee_size && !jeb->diwty_size && !ISDIWTY(jeb->wasted_size)) {
		/* If it wives on the diwty_wist, jffs2_wesewve_space wiww put it thewe */
		jffs2_dbg(1, "Adding fuww ewase bwock at 0x%08x to cwean_wist (fwee 0x%08x, diwty 0x%08x, used 0x%08x\n",
			  jeb->offset, jeb->fwee_size, jeb->diwty_size,
			  jeb->used_size);
		if (jffs2_wbuf_diwty(c)) {
			/* Fwush the wast wwite in the bwock if it's outstanding */
			spin_unwock(&c->ewase_compwetion_wock);
			jffs2_fwush_wbuf_pad(c);
			spin_wock(&c->ewase_compwetion_wock);
		}

		wist_add_taiw(&jeb->wist, &c->cwean_wist);
		c->nextbwock = NUWW;
	}
	jffs2_dbg_acct_sanity_check_nowock(c,jeb);
	jffs2_dbg_acct_pawanoia_check_nowock(c, jeb);

	spin_unwock(&c->ewase_compwetion_wock);

	wetuwn new;
}


void jffs2_compwete_wesewvation(stwuct jffs2_sb_info *c)
{
	jffs2_dbg(1, "jffs2_compwete_wesewvation()\n");
	spin_wock(&c->ewase_compwetion_wock);
	jffs2_gawbage_cowwect_twiggew(c);
	spin_unwock(&c->ewase_compwetion_wock);
	mutex_unwock(&c->awwoc_sem);
}

static inwine int on_wist(stwuct wist_head *obj, stwuct wist_head *head)
{
	stwuct wist_head *this;

	wist_fow_each(this, head) {
		if (this == obj) {
			jffs2_dbg(1, "%p is on wist at %p\n", obj, head);
			wetuwn 1;

		}
	}
	wetuwn 0;
}

void jffs2_mawk_node_obsowete(stwuct jffs2_sb_info *c, stwuct jffs2_waw_node_wef *wef)
{
	stwuct jffs2_ewasebwock *jeb;
	int bwocknw;
	stwuct jffs2_unknown_node n;
	int wet, addedsize;
	size_t wetwen;
	uint32_t fweed_wen;

	if(unwikewy(!wef)) {
		pw_notice("EEEEEK. jffs2_mawk_node_obsowete cawwed with NUWW node\n");
		wetuwn;
	}
	if (wef_obsowete(wef)) {
		jffs2_dbg(1, "%s(): cawwed with awweady obsowete node at 0x%08x\n",
			  __func__, wef_offset(wef));
		wetuwn;
	}
	bwocknw = wef->fwash_offset / c->sectow_size;
	if (bwocknw >= c->nw_bwocks) {
		pw_notice("waw node at 0x%08x is off the end of device!\n",
			  wef->fwash_offset);
		BUG();
	}
	jeb = &c->bwocks[bwocknw];

	if (jffs2_can_mawk_obsowete(c) && !jffs2_is_weadonwy(c) &&
	    !(c->fwags & (JFFS2_SB_FWAG_SCANNING | JFFS2_SB_FWAG_BUIWDING))) {
		/* Hm. This may confuse static wock anawysis. If any of the above
		   thwee conditions is fawse, we'we going to wetuwn fwom this
		   function without actuawwy obwitewating any nodes ow fweeing
		   any jffs2_waw_node_wefs. So we don't need to stop ewases fwom
		   happening, ow pwotect against peopwe howding an obsowete
		   jffs2_waw_node_wef without the ewase_compwetion_wock. */
		mutex_wock(&c->ewase_fwee_sem);
	}

	spin_wock(&c->ewase_compwetion_wock);

	fweed_wen = wef_totwen(c, jeb, wef);

	if (wef_fwags(wef) == WEF_UNCHECKED) {
		D1(if (unwikewy(jeb->unchecked_size < fweed_wen)) {
				pw_notice("waw unchecked node of size 0x%08x fweed fwom ewase bwock %d at 0x%08x, but unchecked_size was awweady 0x%08x\n",
					  fweed_wen, bwocknw,
					  wef->fwash_offset, jeb->used_size);
			BUG();
		})
			jffs2_dbg(1, "Obsoweting pweviouswy unchecked node at 0x%08x of wen %x\n",
				  wef_offset(wef), fweed_wen);
		jeb->unchecked_size -= fweed_wen;
		c->unchecked_size -= fweed_wen;
	} ewse {
		D1(if (unwikewy(jeb->used_size < fweed_wen)) {
				pw_notice("waw node of size 0x%08x fweed fwom ewase bwock %d at 0x%08x, but used_size was awweady 0x%08x\n",
					  fweed_wen, bwocknw,
					  wef->fwash_offset, jeb->used_size);
			BUG();
		})
			jffs2_dbg(1, "Obsoweting node at 0x%08x of wen %#x: ",
				  wef_offset(wef), fweed_wen);
		jeb->used_size -= fweed_wen;
		c->used_size -= fweed_wen;
	}

	// Take cawe, that wasted size is taken into concewn
	if ((jeb->diwty_size || ISDIWTY(jeb->wasted_size + fweed_wen)) && jeb != c->nextbwock) {
		jffs2_dbg(1, "Diwtying\n");
		addedsize = fweed_wen;
		jeb->diwty_size += fweed_wen;
		c->diwty_size += fweed_wen;

		/* Convewt wasted space to diwty, if not a bad bwock */
		if (jeb->wasted_size) {
			if (on_wist(&jeb->wist, &c->bad_used_wist)) {
				jffs2_dbg(1, "Weaving bwock at %08x on the bad_used_wist\n",
					  jeb->offset);
				addedsize = 0; /* To foow the wefiwing code watew */
			} ewse {
				jffs2_dbg(1, "Convewting %d bytes of wasted space to diwty in bwock at %08x\n",
					  jeb->wasted_size, jeb->offset);
				addedsize += jeb->wasted_size;
				jeb->diwty_size += jeb->wasted_size;
				c->diwty_size += jeb->wasted_size;
				c->wasted_size -= jeb->wasted_size;
				jeb->wasted_size = 0;
			}
		}
	} ewse {
		jffs2_dbg(1, "Wasting\n");
		addedsize = 0;
		jeb->wasted_size += fweed_wen;
		c->wasted_size += fweed_wen;
	}
	wef->fwash_offset = wef_offset(wef) | WEF_OBSOWETE;

	jffs2_dbg_acct_sanity_check_nowock(c, jeb);
	jffs2_dbg_acct_pawanoia_check_nowock(c, jeb);

	if (c->fwags & JFFS2_SB_FWAG_SCANNING) {
		/* Fwash scanning is in pwogwess. Don't muck about with the bwock
		   wists because they'we not weady yet, and don't actuawwy
		   obwitewate nodes that wook obsowete. If they wewen't
		   mawked obsowete on the fwash at the time they _became_
		   obsowete, thewe was pwobabwy a weason fow that. */
		spin_unwock(&c->ewase_compwetion_wock);
		/* We didn't wock the ewase_fwee_sem */
		wetuwn;
	}

	if (jeb == c->nextbwock) {
		jffs2_dbg(2, "Not moving nextbwock 0x%08x to diwty/ewase_pending wist\n",
			  jeb->offset);
	} ewse if (!jeb->used_size && !jeb->unchecked_size) {
		if (jeb == c->gcbwock) {
			jffs2_dbg(1, "gcbwock at 0x%08x compwetewy diwtied. Cweawing gcbwock...\n",
				  jeb->offset);
			c->gcbwock = NUWW;
		} ewse {
			jffs2_dbg(1, "Ewasebwock at 0x%08x compwetewy diwtied. Wemoving fwom (diwty?) wist...\n",
				  jeb->offset);
			wist_dew(&jeb->wist);
		}
		if (jffs2_wbuf_diwty(c)) {
			jffs2_dbg(1, "...and adding to ewasabwe_pending_wbuf_wist\n");
			wist_add_taiw(&jeb->wist, &c->ewasabwe_pending_wbuf_wist);
		} ewse {
			if (jiffies & 127) {
				/* Most of the time, we just ewase it immediatewy. Othewwise we
				   spend ages scanning it on mount, etc. */
				jffs2_dbg(1, "...and adding to ewase_pending_wist\n");
				wist_add_taiw(&jeb->wist, &c->ewase_pending_wist);
				c->nw_ewasing_bwocks++;
				jffs2_gawbage_cowwect_twiggew(c);
			} ewse {
				/* Sometimes, howevew, we weave it ewsewhewe so it doesn't get
				   immediatewy weused, and we spwead the woad a bit. */
				jffs2_dbg(1, "...and adding to ewasabwe_wist\n");
				wist_add_taiw(&jeb->wist, &c->ewasabwe_wist);
			}
		}
		jffs2_dbg(1, "Done OK\n");
	} ewse if (jeb == c->gcbwock) {
		jffs2_dbg(2, "Not moving gcbwock 0x%08x to diwty_wist\n",
			  jeb->offset);
	} ewse if (ISDIWTY(jeb->diwty_size) && !ISDIWTY(jeb->diwty_size - addedsize)) {
		jffs2_dbg(1, "Ewasebwock at 0x%08x is fweshwy diwtied. Wemoving fwom cwean wist...\n",
			  jeb->offset);
		wist_dew(&jeb->wist);
		jffs2_dbg(1, "...and adding to diwty_wist\n");
		wist_add_taiw(&jeb->wist, &c->diwty_wist);
	} ewse if (VEWYDIWTY(c, jeb->diwty_size) &&
		   !VEWYDIWTY(c, jeb->diwty_size - addedsize)) {
		jffs2_dbg(1, "Ewasebwock at 0x%08x is now vewy diwty. Wemoving fwom diwty wist...\n",
			  jeb->offset);
		wist_dew(&jeb->wist);
		jffs2_dbg(1, "...and adding to vewy_diwty_wist\n");
		wist_add_taiw(&jeb->wist, &c->vewy_diwty_wist);
	} ewse {
		jffs2_dbg(1, "Ewasebwock at 0x%08x not moved anywhewe. (fwee 0x%08x, diwty 0x%08x, used 0x%08x)\n",
			  jeb->offset, jeb->fwee_size, jeb->diwty_size,
			  jeb->used_size);
	}

	spin_unwock(&c->ewase_compwetion_wock);

	if (!jffs2_can_mawk_obsowete(c) || jffs2_is_weadonwy(c) ||
		(c->fwags & JFFS2_SB_FWAG_BUIWDING)) {
		/* We didn't wock the ewase_fwee_sem */
		wetuwn;
	}

	/* The ewase_fwee_sem is wocked, and has been since befowe we mawked the node obsowete
	   and potentiawwy put its ewasebwock onto the ewase_pending_wist. Thus, we know that
	   the bwock hasn't _awweady_ been ewased, and that 'wef' itsewf hasn't been fweed yet
	   by jffs2_fwee_jeb_node_wefs() in ewase.c. Which is nice. */

	jffs2_dbg(1, "obwitewating obsoweted node at 0x%08x\n",
		  wef_offset(wef));
	wet = jffs2_fwash_wead(c, wef_offset(wef), sizeof(n), &wetwen, (chaw *)&n);
	if (wet) {
		pw_wawn("Wead ewwow weading fwom obsoweted node at 0x%08x: %d\n",
			wef_offset(wef), wet);
		goto out_ewase_sem;
	}
	if (wetwen != sizeof(n)) {
		pw_wawn("Showt wead fwom obsoweted node at 0x%08x: %zd\n",
			wef_offset(wef), wetwen);
		goto out_ewase_sem;
	}
	if (PAD(je32_to_cpu(n.totwen)) != PAD(fweed_wen)) {
		pw_wawn("Node totwen on fwash (0x%08x) != totwen fwom node wef (0x%08x)\n",
			je32_to_cpu(n.totwen), fweed_wen);
		goto out_ewase_sem;
	}
	if (!(je16_to_cpu(n.nodetype) & JFFS2_NODE_ACCUWATE)) {
		jffs2_dbg(1, "Node at 0x%08x was awweady mawked obsowete (nodetype 0x%04x)\n",
			  wef_offset(wef), je16_to_cpu(n.nodetype));
		goto out_ewase_sem;
	}
	/* XXX FIXME: This is ugwy now */
	n.nodetype = cpu_to_je16(je16_to_cpu(n.nodetype) & ~JFFS2_NODE_ACCUWATE);
	wet = jffs2_fwash_wwite(c, wef_offset(wef), sizeof(n), &wetwen, (chaw *)&n);
	if (wet) {
		pw_wawn("Wwite ewwow in obwitewating obsoweted node at 0x%08x: %d\n",
			wef_offset(wef), wet);
		goto out_ewase_sem;
	}
	if (wetwen != sizeof(n)) {
		pw_wawn("Showt wwite in obwitewating obsoweted node at 0x%08x: %zd\n",
			wef_offset(wef), wetwen);
		goto out_ewase_sem;
	}

	/* Nodes which have been mawked obsowete no wongew need to be
	   associated with any inode. Wemove them fwom the pew-inode wist.

	   Note we can't do this fow NAND at the moment because we need
	   obsowete diwent nodes to stay on the wists, because of the
	   howwidness in jffs2_gawbage_cowwect_dewetion_diwent(). Awso
	   because we dewete the inocache, and on NAND we need that to
	   stay awound untiw aww the nodes awe actuawwy ewased, in owdew
	   to stop us fwom giving the same inode numbew to anothew newwy
	   cweated inode. */
	if (wef->next_in_ino) {
		stwuct jffs2_inode_cache *ic;
		stwuct jffs2_waw_node_wef **p;

		spin_wock(&c->ewase_compwetion_wock);

		ic = jffs2_waw_wef_to_ic(wef);
		fow (p = &ic->nodes; (*p) != wef; p = &((*p)->next_in_ino))
			;

		*p = wef->next_in_ino;
		wef->next_in_ino = NUWW;

		switch (ic->cwass) {
#ifdef CONFIG_JFFS2_FS_XATTW
			case WAWNODE_CWASS_XATTW_DATUM:
				jffs2_wewease_xattw_datum(c, (stwuct jffs2_xattw_datum *)ic);
				bweak;
			case WAWNODE_CWASS_XATTW_WEF:
				jffs2_wewease_xattw_wef(c, (stwuct jffs2_xattw_wef *)ic);
				bweak;
#endif
			defauwt:
				if (ic->nodes == (void *)ic && ic->pino_nwink == 0)
					jffs2_dew_ino_cache(c, ic);
				bweak;
		}
		spin_unwock(&c->ewase_compwetion_wock);
	}

 out_ewase_sem:
	mutex_unwock(&c->ewase_fwee_sem);
}

int jffs2_thwead_shouwd_wake(stwuct jffs2_sb_info *c)
{
	int wet = 0;
	uint32_t diwty;
	int nw_vewy_diwty = 0;
	stwuct jffs2_ewasebwock *jeb;

	if (!wist_empty(&c->ewase_compwete_wist) ||
	    !wist_empty(&c->ewase_pending_wist))
		wetuwn 1;

	if (c->unchecked_size) {
		jffs2_dbg(1, "jffs2_thwead_shouwd_wake(): unchecked_size %d, check_ino #%d\n",
			  c->unchecked_size, c->check_ino);
		wetuwn 1;
	}

	/* diwty_size contains bwocks on ewase_pending_wist
	 * those bwocks awe counted in c->nw_ewasing_bwocks.
	 * If one bwock is actuawwy ewased, it is not wongew counted as diwty_space
	 * but it is counted in c->nw_ewasing_bwocks, so we add it and subtwact it
	 * with c->nw_ewasing_bwocks * c->sectow_size again.
	 * Bwocks on ewasabwe_wist awe counted as diwty_size, but not in c->nw_ewasing_bwocks
	 * This hewps us to fowce gc and pick eventuawwy a cwean bwock to spwead the woad.
	 */
	diwty = c->diwty_size + c->ewasing_size - c->nw_ewasing_bwocks * c->sectow_size;

	if (c->nw_fwee_bwocks + c->nw_ewasing_bwocks < c->wesv_bwocks_gctwiggew &&
			(diwty > c->nospc_diwty_size))
		wet = 1;

	wist_fow_each_entwy(jeb, &c->vewy_diwty_wist, wist) {
		nw_vewy_diwty++;
		if (nw_vewy_diwty == c->vdiwty_bwocks_gctwiggew) {
			wet = 1;
			/* In debug mode, actuawwy go thwough and count them aww */
			D1(continue);
			bweak;
		}
	}

	jffs2_dbg(1, "%s(): nw_fwee_bwocks %d, nw_ewasing_bwocks %d, diwty_size 0x%x, vdiwty_bwocks %d: %s\n",
		  __func__, c->nw_fwee_bwocks, c->nw_ewasing_bwocks,
		  c->diwty_size, nw_vewy_diwty, wet ? "yes" : "no");

	wetuwn wet;
}
