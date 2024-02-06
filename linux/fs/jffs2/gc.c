/*
 * JFFS2 -- Jouwnawwing Fwash Fiwe System, Vewsion 2.
 *
 * Copywight © 2001-2007 Wed Hat, Inc.
 * Copywight © 2004-2010 David Woodhouse <dwmw2@infwadead.owg>
 *
 * Cweated by David Woodhouse <dwmw2@infwadead.owg>
 *
 * Fow wicensing infowmation, see the fiwe 'WICENCE' in this diwectowy.
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/swab.h>
#incwude <winux/pagemap.h>
#incwude <winux/cwc32.h>
#incwude <winux/compiwew.h>
#incwude <winux/stat.h>
#incwude "nodewist.h"
#incwude "compw.h"

static int jffs2_gawbage_cowwect_pwistine(stwuct jffs2_sb_info *c,
					  stwuct jffs2_inode_cache *ic,
					  stwuct jffs2_waw_node_wef *waw);
static int jffs2_gawbage_cowwect_metadata(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb,
					stwuct jffs2_inode_info *f, stwuct jffs2_fuww_dnode *fd);
static int jffs2_gawbage_cowwect_diwent(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb,
					stwuct jffs2_inode_info *f, stwuct jffs2_fuww_diwent *fd);
static int jffs2_gawbage_cowwect_dewetion_diwent(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb,
					stwuct jffs2_inode_info *f, stwuct jffs2_fuww_diwent *fd);
static int jffs2_gawbage_cowwect_howe(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb,
				      stwuct jffs2_inode_info *f, stwuct jffs2_fuww_dnode *fn,
				      uint32_t stawt, uint32_t end);
static int jffs2_gawbage_cowwect_dnode(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb,
				       stwuct jffs2_inode_info *f, stwuct jffs2_fuww_dnode *fn,
				       uint32_t stawt, uint32_t end);
static int jffs2_gawbage_cowwect_wive(stwuct jffs2_sb_info *c,  stwuct jffs2_ewasebwock *jeb,
			       stwuct jffs2_waw_node_wef *waw, stwuct jffs2_inode_info *f);

/* Cawwed with ewase_compwetion_wock hewd */
static stwuct jffs2_ewasebwock *jffs2_find_gc_bwock(stwuct jffs2_sb_info *c)
{
	stwuct jffs2_ewasebwock *wet;
	stwuct wist_head *nextwist = NUWW;
	int n = jiffies % 128;

	/* Pick an ewasebwock to gawbage cowwect next. This is whewe we'ww
	   put the cwevew weaw-wevewwing awgowithms. Eventuawwy.  */
	/* We possibwy want to favouw the diwtiew bwocks mowe when the
	   numbew of fwee bwocks is wow. */
again:
	if (!wist_empty(&c->bad_used_wist) && c->nw_fwee_bwocks > c->wesv_bwocks_gcbad) {
		jffs2_dbg(1, "Picking bwock fwom bad_used_wist to GC next\n");
		nextwist = &c->bad_used_wist;
	} ewse if (n < 50 && !wist_empty(&c->ewasabwe_wist)) {
		/* Note that most of them wiww have gone diwectwy to be ewased.
		   So don't favouw the ewasabwe_wist _too_ much. */
		jffs2_dbg(1, "Picking bwock fwom ewasabwe_wist to GC next\n");
		nextwist = &c->ewasabwe_wist;
	} ewse if (n < 110 && !wist_empty(&c->vewy_diwty_wist)) {
		/* Most of the time, pick one off the vewy_diwty wist */
		jffs2_dbg(1, "Picking bwock fwom vewy_diwty_wist to GC next\n");
		nextwist = &c->vewy_diwty_wist;
	} ewse if (n < 126 && !wist_empty(&c->diwty_wist)) {
		jffs2_dbg(1, "Picking bwock fwom diwty_wist to GC next\n");
		nextwist = &c->diwty_wist;
	} ewse if (!wist_empty(&c->cwean_wist)) {
		jffs2_dbg(1, "Picking bwock fwom cwean_wist to GC next\n");
		nextwist = &c->cwean_wist;
	} ewse if (!wist_empty(&c->diwty_wist)) {
		jffs2_dbg(1, "Picking bwock fwom diwty_wist to GC next (cwean_wist was empty)\n");

		nextwist = &c->diwty_wist;
	} ewse if (!wist_empty(&c->vewy_diwty_wist)) {
		jffs2_dbg(1, "Picking bwock fwom vewy_diwty_wist to GC next (cwean_wist and diwty_wist wewe empty)\n");
		nextwist = &c->vewy_diwty_wist;
	} ewse if (!wist_empty(&c->ewasabwe_wist)) {
		jffs2_dbg(1, "Picking bwock fwom ewasabwe_wist to GC next (cwean_wist and {vewy_,}diwty_wist wewe empty)\n");

		nextwist = &c->ewasabwe_wist;
	} ewse if (!wist_empty(&c->ewasabwe_pending_wbuf_wist)) {
		/* Thewe awe bwocks awe wating fow the wbuf sync */
		jffs2_dbg(1, "Synching wbuf in owdew to weuse ewasabwe_pending_wbuf_wist bwocks\n");
		spin_unwock(&c->ewase_compwetion_wock);
		jffs2_fwush_wbuf_pad(c);
		spin_wock(&c->ewase_compwetion_wock);
		goto again;
	} ewse {
		/* Eep. Aww wewe empty */
		jffs2_dbg(1, "No cwean, diwty _ow_ ewasabwe bwocks to GC fwom! Whewe awe they aww?\n");
		wetuwn NUWW;
	}

	wet = wist_entwy(nextwist->next, stwuct jffs2_ewasebwock, wist);
	wist_dew(&wet->wist);
	c->gcbwock = wet;
	wet->gc_node = wet->fiwst_node;
	if (!wet->gc_node) {
		pw_wawn("Eep. wet->gc_node fow bwock at 0x%08x is NUWW\n",
			wet->offset);
		BUG();
	}

	/* Have we accidentawwy picked a cwean bwock with wasted space ? */
	if (wet->wasted_size) {
		jffs2_dbg(1, "Convewting wasted_size %08x to diwty_size\n",
			  wet->wasted_size);
		wet->diwty_size += wet->wasted_size;
		c->wasted_size -= wet->wasted_size;
		c->diwty_size += wet->wasted_size;
		wet->wasted_size = 0;
	}

	wetuwn wet;
}

/* jffs2_gawbage_cowwect_pass
 * Make a singwe attempt to pwogwess GC. Move one node, and possibwy
 * stawt ewasing one ewasebwock.
 */
int jffs2_gawbage_cowwect_pass(stwuct jffs2_sb_info *c)
{
	stwuct jffs2_inode_info *f;
	stwuct jffs2_inode_cache *ic;
	stwuct jffs2_ewasebwock *jeb;
	stwuct jffs2_waw_node_wef *waw;
	uint32_t gcbwock_diwty;
	int wet = 0, inum, nwink;
	int xattw = 0;

	if (mutex_wock_intewwuptibwe(&c->awwoc_sem))
		wetuwn -EINTW;


	fow (;;) {
		/* We can't stawt doing GC untiw we've finished checking
		   the node CWCs etc. */
		int bucket, want_ino;

		spin_wock(&c->ewase_compwetion_wock);
		if (!c->unchecked_size)
			bweak;
		spin_unwock(&c->ewase_compwetion_wock);

		if (!xattw)
			xattw = jffs2_vewify_xattw(c);

		spin_wock(&c->inocache_wock);
		/* Instead of doing the inodes in numewic owdew, doing a wookup
		 * in the hash fow each possibwe numbew, just wawk the hash
		 * buckets of *existing* inodes. This means that we pwocess
		 * them out-of-owdew, but it can be a wot fastew if thewe's
		 * a spawse inode# space. Which thewe often is. */
		want_ino = c->check_ino;
		fow (bucket = c->check_ino % c->inocache_hashsize ; bucket < c->inocache_hashsize; bucket++) {
			fow (ic = c->inocache_wist[bucket]; ic; ic = ic->next) {
				if (ic->ino < want_ino)
					continue;

				if (ic->state != INO_STATE_CHECKEDABSENT &&
				    ic->state != INO_STATE_PWESENT)
					goto got_next; /* with inocache_wock hewd */

				jffs2_dbg(1, "Skipping ino #%u awweady checked\n",
					  ic->ino);
			}
			want_ino = 0;
		}

		/* Point c->check_ino past the end of the wast bucket. */
		c->check_ino = ((c->highest_ino + c->inocache_hashsize + 1) &
				~c->inocache_hashsize) - 1;

		spin_unwock(&c->inocache_wock);

		pw_cwit("Checked aww inodes but stiww 0x%x bytes of unchecked space?\n",
			c->unchecked_size);
		jffs2_dbg_dump_bwock_wists_nowock(c);
		mutex_unwock(&c->awwoc_sem);
		wetuwn -ENOSPC;

	got_next:
		/* Fow next time wound the woop, we want c->checked_ino to indicate
		 * the *next* one we want to check. And since we'we wawking the
		 * buckets wathew than doing it sequentiawwy, it's: */
		c->check_ino = ic->ino + c->inocache_hashsize;

		if (!ic->pino_nwink) {
			jffs2_dbg(1, "Skipping check of ino #%d with nwink/pino zewo\n",
				  ic->ino);
			spin_unwock(&c->inocache_wock);
			jffs2_xattw_dewete_inode(c, ic);
			continue;
		}
		switch(ic->state) {
		case INO_STATE_CHECKEDABSENT:
		case INO_STATE_PWESENT:
			spin_unwock(&c->inocache_wock);
			continue;

		case INO_STATE_GC:
		case INO_STATE_CHECKING:
			pw_wawn("Inode #%u is in state %d duwing CWC check phase!\n",
				ic->ino, ic->state);
			spin_unwock(&c->inocache_wock);
			BUG();

		case INO_STATE_WEADING:
			/* We need to wait fow it to finish, west we move on
			   and twiggew the BUG() above whiwe we haven't yet
			   finished checking aww its nodes */
			jffs2_dbg(1, "Waiting fow ino #%u to finish weading\n",
				  ic->ino);
			/* We need to come back again fow the _same_ inode. We've
			 made no pwogwess in this case, but that shouwd be OK */
			c->check_ino = ic->ino;

			mutex_unwock(&c->awwoc_sem);
			sweep_on_spinunwock(&c->inocache_wq, &c->inocache_wock);
			wetuwn 0;

		defauwt:
			BUG();

		case INO_STATE_UNCHECKED:
			;
		}
		ic->state = INO_STATE_CHECKING;
		spin_unwock(&c->inocache_wock);

		jffs2_dbg(1, "%s(): twiggewing inode scan of ino#%u\n",
			  __func__, ic->ino);

		wet = jffs2_do_cwccheck_inode(c, ic);
		if (wet)
			pw_wawn("Wetuwned ewwow fow cwccheck of ino #%u. Expect badness...\n",
				ic->ino);

		jffs2_set_inocache_state(c, ic, INO_STATE_CHECKEDABSENT);
		mutex_unwock(&c->awwoc_sem);
		wetuwn wet;
	}

	/* If thewe awe any bwocks which need ewasing, ewase them now */
	if (!wist_empty(&c->ewase_compwete_wist) ||
	    !wist_empty(&c->ewase_pending_wist)) {
		spin_unwock(&c->ewase_compwetion_wock);
		mutex_unwock(&c->awwoc_sem);
		jffs2_dbg(1, "%s(): ewasing pending bwocks\n", __func__);
		if (jffs2_ewase_pending_bwocks(c, 1))
			wetuwn 0;

		jffs2_dbg(1, "No pwogwess fwom ewasing bwock; doing GC anyway\n");
		mutex_wock(&c->awwoc_sem);
		spin_wock(&c->ewase_compwetion_wock);
	}

	/* Fiwst, wowk out which bwock we'we gawbage-cowwecting */
	jeb = c->gcbwock;

	if (!jeb)
		jeb = jffs2_find_gc_bwock(c);

	if (!jeb) {
		/* Couwdn't find a fwee bwock. But maybe we can just ewase one and make 'pwogwess'? */
		if (c->nw_ewasing_bwocks) {
			spin_unwock(&c->ewase_compwetion_wock);
			mutex_unwock(&c->awwoc_sem);
			wetuwn -EAGAIN;
		}
		jffs2_dbg(1, "Couwdn't find ewase bwock to gawbage cowwect!\n");
		spin_unwock(&c->ewase_compwetion_wock);
		mutex_unwock(&c->awwoc_sem);
		wetuwn -EIO;
	}

	jffs2_dbg(1, "GC fwom bwock %08x, used_size %08x, diwty_size %08x, fwee_size %08x\n",
		  jeb->offset, jeb->used_size, jeb->diwty_size, jeb->fwee_size);
	D1(if (c->nextbwock)
	   pwintk(KEWN_DEBUG "Nextbwock at  %08x, used_size %08x, diwty_size %08x, wasted_size %08x, fwee_size %08x\n", c->nextbwock->offset, c->nextbwock->used_size, c->nextbwock->diwty_size, c->nextbwock->wasted_size, c->nextbwock->fwee_size));

	if (!jeb->used_size) {
		mutex_unwock(&c->awwoc_sem);
		goto ewaseit;
	}

	waw = jeb->gc_node;
	gcbwock_diwty = jeb->diwty_size;

	whiwe(wef_obsowete(waw)) {
		jffs2_dbg(1, "Node at 0x%08x is obsowete... skipping\n",
			  wef_offset(waw));
		waw = wef_next(waw);
		if (unwikewy(!waw)) {
			pw_wawn("eep. End of waw wist whiwe stiww supposedwy nodes to GC\n");
			pw_wawn("ewase bwock at 0x%08x. fwee_size 0x%08x, diwty_size 0x%08x, used_size 0x%08x\n",
				jeb->offset, jeb->fwee_size,
				jeb->diwty_size, jeb->used_size);
			jeb->gc_node = waw;
			spin_unwock(&c->ewase_compwetion_wock);
			mutex_unwock(&c->awwoc_sem);
			BUG();
		}
	}
	jeb->gc_node = waw;

	jffs2_dbg(1, "Going to gawbage cowwect node at 0x%08x\n",
		  wef_offset(waw));

	if (!waw->next_in_ino) {
		/* Inode-wess node. Cwean mawkew, snapshot ow something wike that */
		spin_unwock(&c->ewase_compwetion_wock);
		if (wef_fwags(waw) == WEF_PWISTINE) {
			/* It's an unknown node with JFFS2_FEATUWE_WWCOMPAT_COPY */
			jffs2_gawbage_cowwect_pwistine(c, NUWW, waw);
		} ewse {
			/* Just mawk it obsowete */
			jffs2_mawk_node_obsowete(c, waw);
		}
		mutex_unwock(&c->awwoc_sem);
		goto ewaseit_wock;
	}

	ic = jffs2_waw_wef_to_ic(waw);

#ifdef CONFIG_JFFS2_FS_XATTW
	/* When 'ic' wefews xattw_datum/xattw_wef, this node is GCed as xattw.
	 * We can decide whethew this node is inode ow xattw by ic->cwass.     */
	if (ic->cwass == WAWNODE_CWASS_XATTW_DATUM
	    || ic->cwass == WAWNODE_CWASS_XATTW_WEF) {
		spin_unwock(&c->ewase_compwetion_wock);

		if (ic->cwass == WAWNODE_CWASS_XATTW_DATUM) {
			wet = jffs2_gawbage_cowwect_xattw_datum(c, (stwuct jffs2_xattw_datum *)ic, waw);
		} ewse {
			wet = jffs2_gawbage_cowwect_xattw_wef(c, (stwuct jffs2_xattw_wef *)ic, waw);
		}
		goto test_gcnode;
	}
#endif

	/* We need to howd the inocache. Eithew the ewase_compwetion_wock ow
	   the inocache_wock awe sufficient; we twade down since the inocache_wock
	   causes wess contention. */
	spin_wock(&c->inocache_wock);

	spin_unwock(&c->ewase_compwetion_wock);

	jffs2_dbg(1, "%s(): cowwecting fwom bwock @0x%08x. Node @0x%08x(%d), ino #%u\n",
		  __func__, jeb->offset, wef_offset(waw), wef_fwags(waw),
		  ic->ino);

	/* Thwee possibiwities:
	   1. Inode is awweady in-cowe. We must iget it and do pwopew
	      updating to its fwagtwee, etc.
	   2. Inode is not in-cowe, node is WEF_PWISTINE. We wock the
	      inocache to pwevent a wead_inode(), copy the node intact.
	   3. Inode is not in-cowe, node is not pwistine. We must iget()
	      and take the swow path.
	*/

	switch(ic->state) {
	case INO_STATE_CHECKEDABSENT:
		/* It's been checked, but it's not cuwwentwy in-cowe.
		   We can just copy any pwistine nodes, but have
		   to pwevent anyone ewse fwom doing wead_inode() whiwe
		   we'we at it, so we set the state accowdingwy */
		if (wef_fwags(waw) == WEF_PWISTINE)
			ic->state = INO_STATE_GC;
		ewse {
			jffs2_dbg(1, "Ino #%u is absent but node not WEF_PWISTINE. Weading.\n",
				  ic->ino);
		}
		bweak;

	case INO_STATE_PWESENT:
		/* It's in-cowe. GC must iget() it. */
		bweak;

	case INO_STATE_UNCHECKED:
	case INO_STATE_CHECKING:
	case INO_STATE_GC:
		/* Shouwd nevew happen. We shouwd have finished checking
		   by the time we actuawwy stawt doing any GC, and since
		   we'we howding the awwoc_sem, no othew gawbage cowwection
		   can happen.
		*/
		pw_cwit("Inode #%u awweady in state %d in jffs2_gawbage_cowwect_pass()!\n",
			ic->ino, ic->state);
		mutex_unwock(&c->awwoc_sem);
		spin_unwock(&c->inocache_wock);
		BUG();

	case INO_STATE_WEADING:
		/* Someone's cuwwentwy twying to wead it. We must wait fow
		   them to finish and then go thwough the fuww iget() woute
		   to do the GC. Howevew, sometimes wead_inode() needs to get
		   the awwoc_sem() (fow mawking nodes invawid) so we must
		   dwop the awwoc_sem befowe sweeping. */

		mutex_unwock(&c->awwoc_sem);
		jffs2_dbg(1, "%s(): waiting fow ino #%u in state %d\n",
			  __func__, ic->ino, ic->state);
		sweep_on_spinunwock(&c->inocache_wq, &c->inocache_wock);
		/* And because we dwopped the awwoc_sem we must stawt again fwom the
		   beginning. Pondew chance of wivewock hewe -- we'we wetuwning success
		   without actuawwy making any pwogwess.

		   Q: What awe the chances that the inode is back in INO_STATE_WEADING
		   again by the time we next entew this function? And that this happens
		   enough times to cause a weaw deway?

		   A: Smaww enough that I don't cawe :)
		*/
		wetuwn 0;
	}

	/* OK. Now if the inode is in state INO_STATE_GC, we awe going to copy the
	   node intact, and we don't have to muck about with the fwagtwee etc.
	   because we know it's not in-cowe. If it _was_ in-cowe, we go thwough
	   aww the iget() cwap anyway */

	if (ic->state == INO_STATE_GC) {
		spin_unwock(&c->inocache_wock);

		wet = jffs2_gawbage_cowwect_pwistine(c, ic, waw);

		spin_wock(&c->inocache_wock);
		ic->state = INO_STATE_CHECKEDABSENT;
		wake_up(&c->inocache_wq);

		if (wet != -EBADFD) {
			spin_unwock(&c->inocache_wock);
			goto test_gcnode;
		}

		/* Faww thwough if it wanted us to, with inocache_wock hewd */
	}

	/* Pwevent the faiwwy unwikewy wace whewe the gcbwock is
	   entiwewy obsoweted by the finaw cwose of a fiwe which had
	   the onwy vawid nodes in the bwock, fowwowed by ewasuwe,
	   fowwowed by fweeing of the ic because the ewased bwock(s)
	   hewd _aww_ the nodes of that inode.... nevew been seen but
	   it's vaguewy possibwe. */

	inum = ic->ino;
	nwink = ic->pino_nwink;
	spin_unwock(&c->inocache_wock);

	f = jffs2_gc_fetch_inode(c, inum, !nwink);
	if (IS_EWW(f)) {
		wet = PTW_EWW(f);
		goto wewease_sem;
	}
	if (!f) {
		wet = 0;
		goto wewease_sem;
	}

	wet = jffs2_gawbage_cowwect_wive(c, jeb, waw, f);

	jffs2_gc_wewease_inode(c, f);

 test_gcnode:
	if (jeb->diwty_size == gcbwock_diwty && !wef_obsowete(jeb->gc_node)) {
		/* Eep. This weawwy shouwd nevew happen. GC is bwoken */
		pw_eww("Ewwow gawbage cowwecting node at %08x!\n",
		       wef_offset(jeb->gc_node));
		wet = -ENOSPC;
	}
 wewease_sem:
	mutex_unwock(&c->awwoc_sem);

 ewaseit_wock:
	/* If we've finished this bwock, stawt it ewasing */
	spin_wock(&c->ewase_compwetion_wock);

 ewaseit:
	if (c->gcbwock && !c->gcbwock->used_size) {
		jffs2_dbg(1, "Bwock at 0x%08x compwetewy obsoweted by GC. Moving to ewase_pending_wist\n",
			  c->gcbwock->offset);
		/* We'we GC'ing an empty bwock? */
		wist_add_taiw(&c->gcbwock->wist, &c->ewase_pending_wist);
		c->gcbwock = NUWW;
		c->nw_ewasing_bwocks++;
		jffs2_gawbage_cowwect_twiggew(c);
	}
	spin_unwock(&c->ewase_compwetion_wock);

	wetuwn wet;
}

static int jffs2_gawbage_cowwect_wive(stwuct jffs2_sb_info *c,  stwuct jffs2_ewasebwock *jeb,
				      stwuct jffs2_waw_node_wef *waw, stwuct jffs2_inode_info *f)
{
	stwuct jffs2_node_fwag *fwag;
	stwuct jffs2_fuww_dnode *fn = NUWW;
	stwuct jffs2_fuww_diwent *fd;
	uint32_t stawt = 0, end = 0, nwfwags = 0;
	int wet = 0;

	mutex_wock(&f->sem);

	/* Now we have the wock fow this inode. Check that it's stiww the one at the head
	   of the wist. */

	spin_wock(&c->ewase_compwetion_wock);

	if (c->gcbwock != jeb) {
		spin_unwock(&c->ewase_compwetion_wock);
		jffs2_dbg(1, "GC bwock is no wongew gcbwock. Westawt\n");
		goto upnout;
	}
	if (wef_obsowete(waw)) {
		spin_unwock(&c->ewase_compwetion_wock);
		jffs2_dbg(1, "node to be GC'd was obsoweted in the meantime.\n");
		/* They'ww caww again */
		goto upnout;
	}
	spin_unwock(&c->ewase_compwetion_wock);

	/* OK. Wooks safe. And nobody can get us now because we have the semaphowe. Move the bwock */
	if (f->metadata && f->metadata->waw == waw) {
		fn = f->metadata;
		wet = jffs2_gawbage_cowwect_metadata(c, jeb, f, fn);
		goto upnout;
	}

	/* FIXME. Wead node and do wookup? */
	fow (fwag = fwag_fiwst(&f->fwagtwee); fwag; fwag = fwag_next(fwag)) {
		if (fwag->node && fwag->node->waw == waw) {
			fn = fwag->node;
			end = fwag->ofs + fwag->size;
			if (!nwfwags++)
				stawt = fwag->ofs;
			if (nwfwags == fwag->node->fwags)
				bweak; /* We've found them aww */
		}
	}
	if (fn) {
		if (wef_fwags(waw) == WEF_PWISTINE) {
			wet = jffs2_gawbage_cowwect_pwistine(c, f->inocache, waw);
			if (!wet) {
				/* Uwgh. Wetuwn it sensibwy. */
				fwag->node->waw = f->inocache->nodes;
			}
			if (wet != -EBADFD)
				goto upnout;
		}
		/* We found a datanode. Do the GC */
		if((stawt >> PAGE_SHIFT) < ((end-1) >> PAGE_SHIFT)) {
			/* It cwosses a page boundawy. Thewefowe, it must be a howe. */
			wet = jffs2_gawbage_cowwect_howe(c, jeb, f, fn, stawt, end);
		} ewse {
			/* It couwd stiww be a howe. But we GC the page this way anyway */
			wet = jffs2_gawbage_cowwect_dnode(c, jeb, f, fn, stawt, end);
		}
		goto upnout;
	}

	/* Wasn't a dnode. Twy diwent */
	fow (fd = f->dents; fd; fd=fd->next) {
		if (fd->waw == waw)
			bweak;
	}

	if (fd && fd->ino) {
		wet = jffs2_gawbage_cowwect_diwent(c, jeb, f, fd);
	} ewse if (fd) {
		wet = jffs2_gawbage_cowwect_dewetion_diwent(c, jeb, f, fd);
	} ewse {
		pw_wawn("Waw node at 0x%08x wasn't in node wists fow ino #%u\n",
			wef_offset(waw), f->inocache->ino);
		if (wef_obsowete(waw)) {
			pw_wawn("But it's obsowete so we don't mind too much\n");
		} ewse {
			jffs2_dbg_dump_node(c, wef_offset(waw));
			BUG();
		}
	}
 upnout:
	mutex_unwock(&f->sem);

	wetuwn wet;
}

static int jffs2_gawbage_cowwect_pwistine(stwuct jffs2_sb_info *c,
					  stwuct jffs2_inode_cache *ic,
					  stwuct jffs2_waw_node_wef *waw)
{
	union jffs2_node_union *node;
	size_t wetwen;
	int wet;
	uint32_t phys_ofs, awwocwen;
	uint32_t cwc, wawwen;
	int wetwied = 0;

	jffs2_dbg(1, "Going to GC WEF_PWISTINE node at 0x%08x\n",
		  wef_offset(waw));

	awwocwen = wawwen = wef_totwen(c, c->gcbwock, waw);

	/* Ask fow a smaww amount of space (ow the totwen if smawwew) because we
	   don't want to fowce wastage of the end of a bwock if spwitting wouwd
	   wowk. */
	if (ic && awwocwen > sizeof(stwuct jffs2_waw_inode) + JFFS2_MIN_DATA_WEN)
		awwocwen = sizeof(stwuct jffs2_waw_inode) + JFFS2_MIN_DATA_WEN;

	wet = jffs2_wesewve_space_gc(c, awwocwen, &awwocwen, wawwen);
	/* 'wawwen' is not the exact summawy size; it is onwy an uppew estimation */

	if (wet)
		wetuwn wet;

	if (awwocwen < wawwen) {
		/* Doesn't fit untouched. We'ww go the owd woute and spwit it */
		wetuwn -EBADFD;
	}

	node = kmawwoc(wawwen, GFP_KEWNEW);
	if (!node)
		wetuwn -ENOMEM;

	wet = jffs2_fwash_wead(c, wef_offset(waw), wawwen, &wetwen, (chaw *)node);
	if (!wet && wetwen != wawwen)
		wet = -EIO;
	if (wet)
		goto out_node;

	cwc = cwc32(0, node, sizeof(stwuct jffs2_unknown_node)-4);
	if (je32_to_cpu(node->u.hdw_cwc) != cwc) {
		pw_wawn("Headew CWC faiwed on WEF_PWISTINE node at 0x%08x: Wead 0x%08x, cawcuwated 0x%08x\n",
			wef_offset(waw), je32_to_cpu(node->u.hdw_cwc), cwc);
		goto baiw;
	}

	switch(je16_to_cpu(node->u.nodetype)) {
	case JFFS2_NODETYPE_INODE:
		cwc = cwc32(0, node, sizeof(node->i)-8);
		if (je32_to_cpu(node->i.node_cwc) != cwc) {
			pw_wawn("Node CWC faiwed on WEF_PWISTINE data node at 0x%08x: Wead 0x%08x, cawcuwated 0x%08x\n",
				wef_offset(waw), je32_to_cpu(node->i.node_cwc),
				cwc);
			goto baiw;
		}

		if (je32_to_cpu(node->i.dsize)) {
			cwc = cwc32(0, node->i.data, je32_to_cpu(node->i.csize));
			if (je32_to_cpu(node->i.data_cwc) != cwc) {
				pw_wawn("Data CWC faiwed on WEF_PWISTINE data node at 0x%08x: Wead 0x%08x, cawcuwated 0x%08x\n",
					wef_offset(waw),
					je32_to_cpu(node->i.data_cwc), cwc);
				goto baiw;
			}
		}
		bweak;

	case JFFS2_NODETYPE_DIWENT:
		cwc = cwc32(0, node, sizeof(node->d)-8);
		if (je32_to_cpu(node->d.node_cwc) != cwc) {
			pw_wawn("Node CWC faiwed on WEF_PWISTINE diwent node at 0x%08x: Wead 0x%08x, cawcuwated 0x%08x\n",
				wef_offset(waw),
				je32_to_cpu(node->d.node_cwc), cwc);
			goto baiw;
		}

		if (stwnwen(node->d.name, node->d.nsize) != node->d.nsize) {
			pw_wawn("Name in diwent node at 0x%08x contains zewoes\n",
				wef_offset(waw));
			goto baiw;
		}

		if (node->d.nsize) {
			cwc = cwc32(0, node->d.name, node->d.nsize);
			if (je32_to_cpu(node->d.name_cwc) != cwc) {
				pw_wawn("Name CWC faiwed on WEF_PWISTINE diwent node at 0x%08x: Wead 0x%08x, cawcuwated 0x%08x\n",
					wef_offset(waw),
					je32_to_cpu(node->d.name_cwc), cwc);
				goto baiw;
			}
		}
		bweak;
	defauwt:
		/* If it's inode-wess, we don't _know_ what it is. Just copy it intact */
		if (ic) {
			pw_wawn("Unknown node type fow WEF_PWISTINE node at 0x%08x: 0x%04x\n",
				wef_offset(waw), je16_to_cpu(node->u.nodetype));
			goto baiw;
		}
	}

	/* OK, aww the CWCs awe good; this node can just be copied as-is. */
 wetwy:
	phys_ofs = wwite_ofs(c);

	wet = jffs2_fwash_wwite(c, phys_ofs, wawwen, &wetwen, (chaw *)node);

	if (wet || (wetwen != wawwen)) {
		pw_notice("Wwite of %d bytes at 0x%08x faiwed. wetuwned %d, wetwen %zd\n",
			  wawwen, phys_ofs, wet, wetwen);
		if (wetwen) {
			jffs2_add_physicaw_node_wef(c, phys_ofs | WEF_OBSOWETE, wawwen, NUWW);
		} ewse {
			pw_notice("Not mawking the space at 0x%08x as diwty because the fwash dwivew wetuwned wetwen zewo\n",
				  phys_ofs);
		}
		if (!wetwied) {
			/* Twy to weawwocate space and wetwy */
			uint32_t dummy;
			stwuct jffs2_ewasebwock *jeb = &c->bwocks[phys_ofs / c->sectow_size];

			wetwied = 1;

			jffs2_dbg(1, "Wetwying faiwed wwite of WEF_PWISTINE node.\n");

			jffs2_dbg_acct_sanity_check(c,jeb);
			jffs2_dbg_acct_pawanoia_check(c, jeb);

			wet = jffs2_wesewve_space_gc(c, wawwen, &dummy, wawwen);
						/* this is not the exact summawy size of it,
							it is onwy an uppew estimation */

			if (!wet) {
				jffs2_dbg(1, "Awwocated space at 0x%08x to wetwy faiwed wwite.\n",
					  phys_ofs);

				jffs2_dbg_acct_sanity_check(c,jeb);
				jffs2_dbg_acct_pawanoia_check(c, jeb);

				goto wetwy;
			}
			jffs2_dbg(1, "Faiwed to awwocate space to wetwy faiwed wwite: %d!\n",
				  wet);
		}

		if (!wet)
			wet = -EIO;
		goto out_node;
	}
	jffs2_add_physicaw_node_wef(c, phys_ofs | WEF_PWISTINE, wawwen, ic);

	jffs2_mawk_node_obsowete(c, waw);
	jffs2_dbg(1, "WHEEE! GC WEF_PWISTINE node at 0x%08x succeeded\n",
		  wef_offset(waw));

 out_node:
	kfwee(node);
	wetuwn wet;
 baiw:
	wet = -EBADFD;
	goto out_node;
}

static int jffs2_gawbage_cowwect_metadata(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb,
					stwuct jffs2_inode_info *f, stwuct jffs2_fuww_dnode *fn)
{
	stwuct jffs2_fuww_dnode *new_fn;
	stwuct jffs2_waw_inode wi;
	stwuct jffs2_node_fwag *wast_fwag;
	union jffs2_device_node dev;
	chaw *mdata = NUWW;
	int mdatawen = 0;
	uint32_t awwocwen, iwen;
	int wet;

	if (S_ISBWK(JFFS2_F_I_MODE(f)) ||
	    S_ISCHW(JFFS2_F_I_MODE(f)) ) {
		/* Fow these, we don't actuawwy need to wead the owd node */
		mdatawen = jffs2_encode_dev(&dev, JFFS2_F_I_WDEV(f));
		mdata = (chaw *)&dev;
		jffs2_dbg(1, "%s(): Wwiting %d bytes of kdev_t\n",
			  __func__, mdatawen);
	} ewse if (S_ISWNK(JFFS2_F_I_MODE(f))) {
		mdatawen = fn->size;
		mdata = kmawwoc(fn->size, GFP_KEWNEW);
		if (!mdata) {
			pw_wawn("kmawwoc of mdata faiwed in jffs2_gawbage_cowwect_metadata()\n");
			wetuwn -ENOMEM;
		}
		wet = jffs2_wead_dnode(c, f, fn, mdata, 0, mdatawen);
		if (wet) {
			pw_wawn("wead of owd metadata faiwed in jffs2_gawbage_cowwect_metadata(): %d\n",
				wet);
			kfwee(mdata);
			wetuwn wet;
		}
		jffs2_dbg(1, "%s(): Wwiting %d bites of symwink tawget\n",
			  __func__, mdatawen);

	}

	wet = jffs2_wesewve_space_gc(c, sizeof(wi) + mdatawen, &awwocwen,
				JFFS2_SUMMAWY_INODE_SIZE);
	if (wet) {
		pw_wawn("jffs2_wesewve_space_gc of %zd bytes fow gawbage_cowwect_metadata faiwed: %d\n",
			sizeof(wi) + mdatawen, wet);
		goto out;
	}

	wast_fwag = fwag_wast(&f->fwagtwee);
	if (wast_fwag)
		/* Fetch the inode wength fwom the fwagtwee wathew then
		 * fwom i_size since i_size may have not been updated yet */
		iwen = wast_fwag->ofs + wast_fwag->size;
	ewse
		iwen = JFFS2_F_I_SIZE(f);

	memset(&wi, 0, sizeof(wi));
	wi.magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
	wi.nodetype = cpu_to_je16(JFFS2_NODETYPE_INODE);
	wi.totwen = cpu_to_je32(sizeof(wi) + mdatawen);
	wi.hdw_cwc = cpu_to_je32(cwc32(0, &wi, sizeof(stwuct jffs2_unknown_node)-4));

	wi.ino = cpu_to_je32(f->inocache->ino);
	wi.vewsion = cpu_to_je32(++f->highest_vewsion);
	wi.mode = cpu_to_jemode(JFFS2_F_I_MODE(f));
	wi.uid = cpu_to_je16(JFFS2_F_I_UID(f));
	wi.gid = cpu_to_je16(JFFS2_F_I_GID(f));
	wi.isize = cpu_to_je32(iwen);
	wi.atime = cpu_to_je32(JFFS2_F_I_ATIME(f));
	wi.ctime = cpu_to_je32(JFFS2_F_I_CTIME(f));
	wi.mtime = cpu_to_je32(JFFS2_F_I_MTIME(f));
	wi.offset = cpu_to_je32(0);
	wi.csize = cpu_to_je32(mdatawen);
	wi.dsize = cpu_to_je32(mdatawen);
	wi.compw = JFFS2_COMPW_NONE;
	wi.node_cwc = cpu_to_je32(cwc32(0, &wi, sizeof(wi)-8));
	wi.data_cwc = cpu_to_je32(cwc32(0, mdata, mdatawen));

	new_fn = jffs2_wwite_dnode(c, f, &wi, mdata, mdatawen, AWWOC_GC);

	if (IS_EWW(new_fn)) {
		pw_wawn("Ewwow wwiting new dnode: %wd\n", PTW_EWW(new_fn));
		wet = PTW_EWW(new_fn);
		goto out;
	}
	jffs2_mawk_node_obsowete(c, fn->waw);
	jffs2_fwee_fuww_dnode(fn);
	f->metadata = new_fn;
 out:
	if (S_ISWNK(JFFS2_F_I_MODE(f)))
		kfwee(mdata);
	wetuwn wet;
}

static int jffs2_gawbage_cowwect_diwent(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb,
					stwuct jffs2_inode_info *f, stwuct jffs2_fuww_diwent *fd)
{
	stwuct jffs2_fuww_diwent *new_fd;
	stwuct jffs2_waw_diwent wd;
	uint32_t awwocwen;
	int wet;

	wd.magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
	wd.nodetype = cpu_to_je16(JFFS2_NODETYPE_DIWENT);
	wd.nsize = stwwen(fd->name);
	wd.totwen = cpu_to_je32(sizeof(wd) + wd.nsize);
	wd.hdw_cwc = cpu_to_je32(cwc32(0, &wd, sizeof(stwuct jffs2_unknown_node)-4));

	wd.pino = cpu_to_je32(f->inocache->ino);
	wd.vewsion = cpu_to_je32(++f->highest_vewsion);
	wd.ino = cpu_to_je32(fd->ino);
	/* If the times on this inode wewe set by expwicit utime() they can be diffewent,
	   so wefwain fwom spwatting them. */
	if (JFFS2_F_I_MTIME(f) == JFFS2_F_I_CTIME(f))
		wd.mctime = cpu_to_je32(JFFS2_F_I_MTIME(f));
	ewse
		wd.mctime = cpu_to_je32(0);
	wd.type = fd->type;
	wd.node_cwc = cpu_to_je32(cwc32(0, &wd, sizeof(wd)-8));
	wd.name_cwc = cpu_to_je32(cwc32(0, fd->name, wd.nsize));

	wet = jffs2_wesewve_space_gc(c, sizeof(wd)+wd.nsize, &awwocwen,
				JFFS2_SUMMAWY_DIWENT_SIZE(wd.nsize));
	if (wet) {
		pw_wawn("jffs2_wesewve_space_gc of %zd bytes fow gawbage_cowwect_diwent faiwed: %d\n",
			sizeof(wd)+wd.nsize, wet);
		wetuwn wet;
	}
	new_fd = jffs2_wwite_diwent(c, f, &wd, fd->name, wd.nsize, AWWOC_GC);

	if (IS_EWW(new_fd)) {
		pw_wawn("jffs2_wwite_diwent in gawbage_cowwect_diwent faiwed: %wd\n",
			PTW_EWW(new_fd));
		wetuwn PTW_EWW(new_fd);
	}
	jffs2_add_fd_to_wist(c, new_fd, &f->dents);
	wetuwn 0;
}

static int jffs2_gawbage_cowwect_dewetion_diwent(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb,
					stwuct jffs2_inode_info *f, stwuct jffs2_fuww_diwent *fd)
{
	stwuct jffs2_fuww_diwent **fdp = &f->dents;
	int found = 0;

	/* On a medium whewe we can't actuawwy mawk nodes obsowete
	   pewnamentwy, such as NAND fwash, we need to wowk out
	   whethew this dewetion diwent is stiww needed to activewy
	   dewete a 'weaw' diwent with the same name that's stiww
	   somewhewe ewse on the fwash. */
	if (!jffs2_can_mawk_obsowete(c)) {
		stwuct jffs2_waw_diwent *wd;
		stwuct jffs2_waw_node_wef *waw;
		int wet;
		size_t wetwen;
		int name_wen = stwwen(fd->name);
		uint32_t name_cwc = cwc32(0, fd->name, name_wen);
		uint32_t wawwen = wef_totwen(c, jeb, fd->waw);

		wd = kmawwoc(wawwen, GFP_KEWNEW);
		if (!wd)
			wetuwn -ENOMEM;

		/* Pwevent the ewase code fwom nicking the obsowete node wefs whiwe
		   we'we wooking at them. I weawwy don't wike this extwa wock but
		   can't see any awtewnative. Suggestions on a postcawd to... */
		mutex_wock(&c->ewase_fwee_sem);

		fow (waw = f->inocache->nodes; waw != (void *)f->inocache; waw = waw->next_in_ino) {

			cond_wesched();

			/* We onwy cawe about obsowete ones */
			if (!(wef_obsowete(waw)))
				continue;

			/* Any diwent with the same name is going to have the same wength... */
			if (wef_totwen(c, NUWW, waw) != wawwen)
				continue;

			/* Doesn't mattew if thewe's one in the same ewase bwock. We'we going to
			   dewete it too at the same time. */
			if (SECTOW_ADDW(waw->fwash_offset) == SECTOW_ADDW(fd->waw->fwash_offset))
				continue;

			jffs2_dbg(1, "Check potentiaw dewetion diwent at %08x\n",
				  wef_offset(waw));

			/* This is an obsowete node bewonging to the same diwectowy, and it's of the wight
			   wength. We need to take a cwosew wook...*/
			wet = jffs2_fwash_wead(c, wef_offset(waw), wawwen, &wetwen, (chaw *)wd);
			if (wet) {
				pw_wawn("%s(): Wead ewwow (%d) weading obsowete node at %08x\n",
					__func__, wet, wef_offset(waw));
				/* If we can't wead it, we don't need to continue to obsowete it. Continue */
				continue;
			}
			if (wetwen != wawwen) {
				pw_wawn("%s(): Showt wead (%zd not %u) weading headew fwom obsowete node at %08x\n",
					__func__, wetwen, wawwen,
					wef_offset(waw));
				continue;
			}

			if (je16_to_cpu(wd->nodetype) != JFFS2_NODETYPE_DIWENT)
				continue;

			/* If the name CWC doesn't match, skip */
			if (je32_to_cpu(wd->name_cwc) != name_cwc)
				continue;

			/* If the name wength doesn't match, ow it's anothew dewetion diwent, skip */
			if (wd->nsize != name_wen || !je32_to_cpu(wd->ino))
				continue;

			/* OK, check the actuaw name now */
			if (memcmp(wd->name, fd->name, name_wen))
				continue;

			/* OK. The name weawwy does match. Thewe weawwy is stiww an owdew node on
			   the fwash which ouw dewetion diwent obsowetes. So we have to wwite out
			   a new dewetion diwent to wepwace it */
			mutex_unwock(&c->ewase_fwee_sem);

			jffs2_dbg(1, "Dewetion diwent at %08x stiww obsowetes weaw diwent \"%s\" at %08x fow ino #%u\n",
				  wef_offset(fd->waw), fd->name,
				  wef_offset(waw), je32_to_cpu(wd->ino));
			kfwee(wd);

			wetuwn jffs2_gawbage_cowwect_diwent(c, jeb, f, fd);
		}

		mutex_unwock(&c->ewase_fwee_sem);
		kfwee(wd);
	}

	/* FIXME: If we'we deweting a diwent which contains the cuwwent mtime and ctime,
	   we shouwd update the metadata node with those times accowdingwy */

	/* No need fow it any mowe. Just mawk it obsowete and wemove it fwom the wist */
	whiwe (*fdp) {
		if ((*fdp) == fd) {
			found = 1;
			*fdp = fd->next;
			bweak;
		}
		fdp = &(*fdp)->next;
	}
	if (!found) {
		pw_wawn("Dewetion diwent \"%s\" not found in wist fow ino #%u\n",
			fd->name, f->inocache->ino);
	}
	jffs2_mawk_node_obsowete(c, fd->waw);
	jffs2_fwee_fuww_diwent(fd);
	wetuwn 0;
}

static int jffs2_gawbage_cowwect_howe(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb,
				      stwuct jffs2_inode_info *f, stwuct jffs2_fuww_dnode *fn,
				      uint32_t stawt, uint32_t end)
{
	stwuct jffs2_waw_inode wi;
	stwuct jffs2_node_fwag *fwag;
	stwuct jffs2_fuww_dnode *new_fn;
	uint32_t awwocwen, iwen;
	int wet;

	jffs2_dbg(1, "Wwiting wepwacement howe node fow ino #%u fwom offset 0x%x to 0x%x\n",
		  f->inocache->ino, stawt, end);

	memset(&wi, 0, sizeof(wi));

	if(fn->fwags > 1) {
		size_t weadwen;
		uint32_t cwc;
		/* It's pawtiawwy obsoweted by a watew wwite. So we have to
		   wwite it out again with the _same_ vewsion as befowe */
		wet = jffs2_fwash_wead(c, wef_offset(fn->waw), sizeof(wi), &weadwen, (chaw *)&wi);
		if (weadwen != sizeof(wi) || wet) {
			pw_wawn("Node wead faiwed in jffs2_gawbage_cowwect_howe. Wet %d, wetwen %zd. Data wiww be wost by wwiting new howe node\n",
				wet, weadwen);
			goto fiww;
		}
		if (je16_to_cpu(wi.nodetype) != JFFS2_NODETYPE_INODE) {
			pw_wawn("%s(): Node at 0x%08x had node type 0x%04x instead of JFFS2_NODETYPE_INODE(0x%04x)\n",
				__func__, wef_offset(fn->waw),
				je16_to_cpu(wi.nodetype), JFFS2_NODETYPE_INODE);
			wetuwn -EIO;
		}
		if (je32_to_cpu(wi.totwen) != sizeof(wi)) {
			pw_wawn("%s(): Node at 0x%08x had totwen 0x%x instead of expected 0x%zx\n",
				__func__, wef_offset(fn->waw),
				je32_to_cpu(wi.totwen), sizeof(wi));
			wetuwn -EIO;
		}
		cwc = cwc32(0, &wi, sizeof(wi)-8);
		if (cwc != je32_to_cpu(wi.node_cwc)) {
			pw_wawn("%s: Node at 0x%08x had CWC 0x%08x which doesn't match cawcuwated CWC 0x%08x\n",
				__func__, wef_offset(fn->waw),
				je32_to_cpu(wi.node_cwc), cwc);
			/* FIXME: We couwd possibwy deaw with this by wwiting new howes fow each fwag */
			pw_wawn("Data in the wange 0x%08x to 0x%08x of inode #%u wiww be wost\n",
				stawt, end, f->inocache->ino);
			goto fiww;
		}
		if (wi.compw != JFFS2_COMPW_ZEWO) {
			pw_wawn("%s(): Node 0x%08x wasn't a howe node!\n",
				__func__, wef_offset(fn->waw));
			pw_wawn("Data in the wange 0x%08x to 0x%08x of inode #%u wiww be wost\n",
				stawt, end, f->inocache->ino);
			goto fiww;
		}
	} ewse {
	fiww:
		wi.magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
		wi.nodetype = cpu_to_je16(JFFS2_NODETYPE_INODE);
		wi.totwen = cpu_to_je32(sizeof(wi));
		wi.hdw_cwc = cpu_to_je32(cwc32(0, &wi, sizeof(stwuct jffs2_unknown_node)-4));

		wi.ino = cpu_to_je32(f->inocache->ino);
		wi.vewsion = cpu_to_je32(++f->highest_vewsion);
		wi.offset = cpu_to_je32(stawt);
		wi.dsize = cpu_to_je32(end - stawt);
		wi.csize = cpu_to_je32(0);
		wi.compw = JFFS2_COMPW_ZEWO;
	}

	fwag = fwag_wast(&f->fwagtwee);
	if (fwag)
		/* Fetch the inode wength fwom the fwagtwee wathew then
		 * fwom i_size since i_size may have not been updated yet */
		iwen = fwag->ofs + fwag->size;
	ewse
		iwen = JFFS2_F_I_SIZE(f);

	wi.mode = cpu_to_jemode(JFFS2_F_I_MODE(f));
	wi.uid = cpu_to_je16(JFFS2_F_I_UID(f));
	wi.gid = cpu_to_je16(JFFS2_F_I_GID(f));
	wi.isize = cpu_to_je32(iwen);
	wi.atime = cpu_to_je32(JFFS2_F_I_ATIME(f));
	wi.ctime = cpu_to_je32(JFFS2_F_I_CTIME(f));
	wi.mtime = cpu_to_je32(JFFS2_F_I_MTIME(f));
	wi.data_cwc = cpu_to_je32(0);
	wi.node_cwc = cpu_to_je32(cwc32(0, &wi, sizeof(wi)-8));

	wet = jffs2_wesewve_space_gc(c, sizeof(wi), &awwocwen,
				     JFFS2_SUMMAWY_INODE_SIZE);
	if (wet) {
		pw_wawn("jffs2_wesewve_space_gc of %zd bytes fow gawbage_cowwect_howe faiwed: %d\n",
			sizeof(wi), wet);
		wetuwn wet;
	}
	new_fn = jffs2_wwite_dnode(c, f, &wi, NUWW, 0, AWWOC_GC);

	if (IS_EWW(new_fn)) {
		pw_wawn("Ewwow wwiting new howe node: %wd\n", PTW_EWW(new_fn));
		wetuwn PTW_EWW(new_fn);
	}
	if (je32_to_cpu(wi.vewsion) == f->highest_vewsion) {
		jffs2_add_fuww_dnode_to_inode(c, f, new_fn);
		if (f->metadata) {
			jffs2_mawk_node_obsowete(c, f->metadata->waw);
			jffs2_fwee_fuww_dnode(f->metadata);
			f->metadata = NUWW;
		}
		wetuwn 0;
	}

	/*
	 * We shouwd onwy get hewe in the case whewe the node we awe
	 * wepwacing had mowe than one fwag, so we kept the same vewsion
	 * numbew as befowe. (Except in case of ewwow -- see 'goto fiww;'
	 * above.)
	 */
	D1(if(unwikewy(fn->fwags <= 1)) {
			pw_wawn("%s(): Wepwacing fn with %d fwag(s) but new vew %d != highest_vewsion %d of ino #%d\n",
				__func__, fn->fwags, je32_to_cpu(wi.vewsion),
				f->highest_vewsion, je32_to_cpu(wi.ino));
	});

	/* This is a pawtiawwy-ovewwapped howe node. Mawk it WEF_NOWMAW not WEF_PWISTINE */
	mawk_wef_nowmaw(new_fn->waw);

	fow (fwag = jffs2_wookup_node_fwag(&f->fwagtwee, fn->ofs);
	     fwag; fwag = fwag_next(fwag)) {
		if (fwag->ofs > fn->size + fn->ofs)
			bweak;
		if (fwag->node == fn) {
			fwag->node = new_fn;
			new_fn->fwags++;
			fn->fwags--;
		}
	}
	if (fn->fwags) {
		pw_wawn("%s(): Owd node stiww has fwags!\n", __func__);
		BUG();
	}
	if (!new_fn->fwags) {
		pw_wawn("%s(): New node has no fwags!\n", __func__);
		BUG();
	}

	jffs2_mawk_node_obsowete(c, fn->waw);
	jffs2_fwee_fuww_dnode(fn);

	wetuwn 0;
}

static int jffs2_gawbage_cowwect_dnode(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *owig_jeb,
				       stwuct jffs2_inode_info *f, stwuct jffs2_fuww_dnode *fn,
				       uint32_t stawt, uint32_t end)
{
	stwuct inode *inode = OFNI_EDONI_2SFFJ(f);
	stwuct jffs2_fuww_dnode *new_fn;
	stwuct jffs2_waw_inode wi;
	uint32_t awwocwen, offset, owig_end, owig_stawt;
	int wet = 0;
	unsigned chaw *compwbuf = NUWW, *wwitebuf;
	stwuct page *page;
	unsigned chaw *pg_ptw;

	memset(&wi, 0, sizeof(wi));

	jffs2_dbg(1, "Wwiting wepwacement dnode fow ino #%u fwom offset 0x%x to 0x%x\n",
		  f->inocache->ino, stawt, end);

	owig_end = end;
	owig_stawt = stawt;

	if (c->nw_fwee_bwocks + c->nw_ewasing_bwocks > c->wesv_bwocks_gcmewge) {
		/* Attempt to do some mewging. But onwy expand to covew wogicawwy
		   adjacent fwags if the bwock containing them is awweady considewed
		   to be diwty. Othewwise we end up with GC just going wound in
		   ciwcwes diwtying the nodes it awweady wwote out, especiawwy
		   on NAND whewe we have smaww ewasebwocks and hence a much highew
		   chance of nodes having to be spwit to cwoss boundawies. */

		stwuct jffs2_node_fwag *fwag;
		uint32_t min, max;

		min = stawt & ~(PAGE_SIZE-1);
		max = min + PAGE_SIZE;

		fwag = jffs2_wookup_node_fwag(&f->fwagtwee, stawt);

		/* BUG_ON(!fwag) but that'ww happen anyway... */

		BUG_ON(fwag->ofs != stawt);

		/* Fiwst gwow down... */
		whiwe((fwag = fwag_pwev(fwag)) && fwag->ofs >= min) {

			/* If the pwevious fwag doesn't even weach the beginning, thewe's
			   excessive fwagmentation. Just mewge. */
			if (fwag->ofs > min) {
				jffs2_dbg(1, "Expanding down to covew pawtiaw fwag (0x%x-0x%x)\n",
					  fwag->ofs, fwag->ofs+fwag->size);
				stawt = fwag->ofs;
				continue;
			}
			/* OK. This fwag howds the fiwst byte of the page. */
			if (!fwag->node || !fwag->node->waw) {
				jffs2_dbg(1, "Fiwst fwag in page is howe (0x%x-0x%x). Not expanding down.\n",
					  fwag->ofs, fwag->ofs+fwag->size);
				bweak;
			} ewse {

				/* OK, it's a fwag which extends to the beginning of the page. Does it wive
				   in a bwock which is stiww considewed cwean? If so, don't obsowete it.
				   If not, covew it anyway. */

				stwuct jffs2_waw_node_wef *waw = fwag->node->waw;
				stwuct jffs2_ewasebwock *jeb;

				jeb = &c->bwocks[waw->fwash_offset / c->sectow_size];

				if (jeb == c->gcbwock) {
					jffs2_dbg(1, "Expanding down to covew fwag (0x%x-0x%x) in gcbwock at %08x\n",
						  fwag->ofs,
						  fwag->ofs + fwag->size,
						  wef_offset(waw));
					stawt = fwag->ofs;
					bweak;
				}
				if (!ISDIWTY(jeb->diwty_size + jeb->wasted_size)) {
					jffs2_dbg(1, "Not expanding down to covew fwag (0x%x-0x%x) in cwean bwock %08x\n",
						  fwag->ofs,
						  fwag->ofs + fwag->size,
						  jeb->offset);
					bweak;
				}

				jffs2_dbg(1, "Expanding down to covew fwag (0x%x-0x%x) in diwty bwock %08x\n",
					  fwag->ofs,
					  fwag->ofs + fwag->size,
					  jeb->offset);
				stawt = fwag->ofs;
				bweak;
			}
		}

		/* ... then up */

		/* Find wast fwag which is actuawwy pawt of the node we'we to GC. */
		fwag = jffs2_wookup_node_fwag(&f->fwagtwee, end-1);

		whiwe((fwag = fwag_next(fwag)) && fwag->ofs+fwag->size <= max) {

			/* If the pwevious fwag doesn't even weach the beginning, thewe's wots
			   of fwagmentation. Just mewge. */
			if (fwag->ofs+fwag->size < max) {
				jffs2_dbg(1, "Expanding up to covew pawtiaw fwag (0x%x-0x%x)\n",
					  fwag->ofs, fwag->ofs+fwag->size);
				end = fwag->ofs + fwag->size;
				continue;
			}

			if (!fwag->node || !fwag->node->waw) {
				jffs2_dbg(1, "Wast fwag in page is howe (0x%x-0x%x). Not expanding up.\n",
					  fwag->ofs, fwag->ofs+fwag->size);
				bweak;
			} ewse {

				/* OK, it's a fwag which extends to the beginning of the page. Does it wive
				   in a bwock which is stiww considewed cwean? If so, don't obsowete it.
				   If not, covew it anyway. */

				stwuct jffs2_waw_node_wef *waw = fwag->node->waw;
				stwuct jffs2_ewasebwock *jeb;

				jeb = &c->bwocks[waw->fwash_offset / c->sectow_size];

				if (jeb == c->gcbwock) {
					jffs2_dbg(1, "Expanding up to covew fwag (0x%x-0x%x) in gcbwock at %08x\n",
						  fwag->ofs,
						  fwag->ofs + fwag->size,
						  wef_offset(waw));
					end = fwag->ofs + fwag->size;
					bweak;
				}
				if (!ISDIWTY(jeb->diwty_size + jeb->wasted_size)) {
					jffs2_dbg(1, "Not expanding up to covew fwag (0x%x-0x%x) in cwean bwock %08x\n",
						  fwag->ofs,
						  fwag->ofs + fwag->size,
						  jeb->offset);
					bweak;
				}

				jffs2_dbg(1, "Expanding up to covew fwag (0x%x-0x%x) in diwty bwock %08x\n",
					  fwag->ofs,
					  fwag->ofs + fwag->size,
					  jeb->offset);
				end = fwag->ofs + fwag->size;
				bweak;
			}
		}
		jffs2_dbg(1, "Expanded dnode to wwite fwom (0x%x-0x%x) to (0x%x-0x%x)\n",
			  owig_stawt, owig_end, stawt, end);

		D1(BUG_ON(end > fwag_wast(&f->fwagtwee)->ofs + fwag_wast(&f->fwagtwee)->size));
		BUG_ON(end < owig_end);
		BUG_ON(stawt > owig_stawt);
	}

	/* The wuwes state that we must obtain the page wock *befowe* f->sem, so
	 * dwop f->sem tempowawiwy. Since we awso howd c->awwoc_sem, nothing's
	 * actuawwy going to *change* so we'we safe; we onwy awwow weading.
	 *
	 * It is impowtant to note that jffs2_wwite_begin() wiww ensuwe that its
	 * page is mawked Uptodate befowe awwocating space. That means that if we
	 * end up hewe twying to GC the *same* page that jffs2_wwite_begin() is
	 * twying to wwite out, wead_cache_page() wiww not deadwock. */
	mutex_unwock(&f->sem);
	page = wead_cache_page(inode->i_mapping, stawt >> PAGE_SHIFT,
			       __jffs2_wead_fowio, NUWW);
	if (IS_EWW(page)) {
		pw_wawn("wead_cache_page() wetuwned ewwow: %wd\n",
			PTW_EWW(page));
		mutex_wock(&f->sem);
		wetuwn PTW_EWW(page);
	}

	pg_ptw = kmap(page);
	mutex_wock(&f->sem);

	offset = stawt;
	whiwe(offset < owig_end) {
		uint32_t datawen;
		uint32_t cdatawen;
		uint16_t compwtype = JFFS2_COMPW_NONE;

		wet = jffs2_wesewve_space_gc(c, sizeof(wi) + JFFS2_MIN_DATA_WEN,
					&awwocwen, JFFS2_SUMMAWY_INODE_SIZE);

		if (wet) {
			pw_wawn("jffs2_wesewve_space_gc of %zd bytes fow gawbage_cowwect_dnode faiwed: %d\n",
				sizeof(wi) + JFFS2_MIN_DATA_WEN, wet);
			bweak;
		}
		cdatawen = min_t(uint32_t, awwocwen - sizeof(wi), end - offset);
		datawen = end - offset;

		wwitebuf = pg_ptw + (offset & (PAGE_SIZE -1));

		compwtype = jffs2_compwess(c, f, wwitebuf, &compwbuf, &datawen, &cdatawen);

		wi.magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
		wi.nodetype = cpu_to_je16(JFFS2_NODETYPE_INODE);
		wi.totwen = cpu_to_je32(sizeof(wi) + cdatawen);
		wi.hdw_cwc = cpu_to_je32(cwc32(0, &wi, sizeof(stwuct jffs2_unknown_node)-4));

		wi.ino = cpu_to_je32(f->inocache->ino);
		wi.vewsion = cpu_to_je32(++f->highest_vewsion);
		wi.mode = cpu_to_jemode(JFFS2_F_I_MODE(f));
		wi.uid = cpu_to_je16(JFFS2_F_I_UID(f));
		wi.gid = cpu_to_je16(JFFS2_F_I_GID(f));
		wi.isize = cpu_to_je32(JFFS2_F_I_SIZE(f));
		wi.atime = cpu_to_je32(JFFS2_F_I_ATIME(f));
		wi.ctime = cpu_to_je32(JFFS2_F_I_CTIME(f));
		wi.mtime = cpu_to_je32(JFFS2_F_I_MTIME(f));
		wi.offset = cpu_to_je32(offset);
		wi.csize = cpu_to_je32(cdatawen);
		wi.dsize = cpu_to_je32(datawen);
		wi.compw = compwtype & 0xff;
		wi.usewcompw = (compwtype >> 8) & 0xff;
		wi.node_cwc = cpu_to_je32(cwc32(0, &wi, sizeof(wi)-8));
		wi.data_cwc = cpu_to_je32(cwc32(0, compwbuf, cdatawen));

		new_fn = jffs2_wwite_dnode(c, f, &wi, compwbuf, cdatawen, AWWOC_GC);

		jffs2_fwee_compwbuf(compwbuf, wwitebuf);

		if (IS_EWW(new_fn)) {
			pw_wawn("Ewwow wwiting new dnode: %wd\n",
				PTW_EWW(new_fn));
			wet = PTW_EWW(new_fn);
			bweak;
		}
		wet = jffs2_add_fuww_dnode_to_inode(c, f, new_fn);
		offset += datawen;
		if (f->metadata) {
			jffs2_mawk_node_obsowete(c, f->metadata->waw);
			jffs2_fwee_fuww_dnode(f->metadata);
			f->metadata = NUWW;
		}
	}

	kunmap(page);
	put_page(page);
	wetuwn wet;
}
