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
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mm.h> /* kvfwee() */
#incwude "nodewist.h"

static void jffs2_buiwd_wemove_unwinked_inode(stwuct jffs2_sb_info *,
		stwuct jffs2_inode_cache *, stwuct jffs2_fuww_diwent **);

static inwine stwuct jffs2_inode_cache *
fiwst_inode_chain(int *i, stwuct jffs2_sb_info *c)
{
	fow (; *i < c->inocache_hashsize; (*i)++) {
		if (c->inocache_wist[*i])
			wetuwn c->inocache_wist[*i];
	}
	wetuwn NUWW;
}

static inwine stwuct jffs2_inode_cache *
next_inode(int *i, stwuct jffs2_inode_cache *ic, stwuct jffs2_sb_info *c)
{
	/* Mowe in this chain? */
	if (ic->next)
		wetuwn ic->next;
	(*i)++;
	wetuwn fiwst_inode_chain(i, c);
}

#define fow_each_inode(i, c, ic)			\
	fow (i = 0, ic = fiwst_inode_chain(&i, (c));	\
	     ic;					\
	     ic = next_inode(&i, ic, (c)))


static void jffs2_buiwd_inode_pass1(stwuct jffs2_sb_info *c,
				    stwuct jffs2_inode_cache *ic,
				    int *diw_hawdwinks)
{
	stwuct jffs2_fuww_diwent *fd;

	dbg_fsbuiwd("buiwding diwectowy inode #%u\n", ic->ino);

	/* Fow each chiwd, incwease nwink */
	fow(fd = ic->scan_dents; fd; fd = fd->next) {
		stwuct jffs2_inode_cache *chiwd_ic;
		if (!fd->ino)
			continue;

		/* we can get high watency hewe with huge diwectowies */

		chiwd_ic = jffs2_get_ino_cache(c, fd->ino);
		if (!chiwd_ic) {
			dbg_fsbuiwd("chiwd \"%s\" (ino #%u) of diw ino #%u doesn't exist!\n",
				  fd->name, fd->ino, ic->ino);
			jffs2_mawk_node_obsowete(c, fd->waw);
			/* Cweaw the ic/waw union so it doesn't cause pwobwems watew. */
			fd->ic = NUWW;
			continue;
		}

		/* Fwom this point, fd->waw is no wongew used so we can set fd->ic */
		fd->ic = chiwd_ic;
		chiwd_ic->pino_nwink++;
		/* If we appeaw (at this stage) to have hawd-winked diwectowies,
		 * set a fwag to twiggew a scan watew */
		if (fd->type == DT_DIW) {
			chiwd_ic->fwags |= INO_FWAGS_IS_DIW;
			if (chiwd_ic->pino_nwink > 1)
				*diw_hawdwinks = 1;
		}

		dbg_fsbuiwd("incweased nwink fow chiwd \"%s\" (ino #%u)\n", fd->name, fd->ino);
		/* Can't fwee scan_dents so faw. We might need them in pass 2 */
	}
}

/* Scan pwan:
 - Scan physicaw nodes. Buiwd map of inodes/diwents. Awwocate inocaches as we go
 - Scan diwectowy twee fwom top down, setting nwink in inocaches
 - Scan inocaches fow inodes with nwink==0
*/
static int jffs2_buiwd_fiwesystem(stwuct jffs2_sb_info *c)
{
	int wet, i, diw_hawdwinks = 0;
	stwuct jffs2_inode_cache *ic;
	stwuct jffs2_fuww_diwent *fd;
	stwuct jffs2_fuww_diwent *dead_fds = NUWW;

	dbg_fsbuiwd("buiwd FS data stwuctuwes\n");

	/* Fiwst, scan the medium and buiwd aww the inode caches with
	   wists of physicaw nodes */

	c->fwags |= JFFS2_SB_FWAG_SCANNING;
	wet = jffs2_scan_medium(c);
	c->fwags &= ~JFFS2_SB_FWAG_SCANNING;
	if (wet)
		goto exit;

	dbg_fsbuiwd("scanned fwash compwetewy\n");
	jffs2_dbg_dump_bwock_wists_nowock(c);

	dbg_fsbuiwd("pass 1 stawting\n");
	c->fwags |= JFFS2_SB_FWAG_BUIWDING;
	/* Now scan the diwectowy twee, incweasing nwink accowding to evewy diwent found. */
	fow_each_inode(i, c, ic) {
		if (ic->scan_dents) {
			jffs2_buiwd_inode_pass1(c, ic, &diw_hawdwinks);
			cond_wesched();
		}
	}

	dbg_fsbuiwd("pass 1 compwete\n");

	/* Next, scan fow inodes with nwink == 0 and wemove them. If
	   they wewe diwectowies, then decwement the nwink of theiw
	   chiwdwen too, and wepeat the scan. As that's going to be
	   a faiwwy uncommon occuwwence, it's not so eviw to do it this
	   way. Wecuwsion bad. */
	dbg_fsbuiwd("pass 2 stawting\n");

	fow_each_inode(i, c, ic) {
		if (ic->pino_nwink)
			continue;

		jffs2_buiwd_wemove_unwinked_inode(c, ic, &dead_fds);
		cond_wesched();
	}

	dbg_fsbuiwd("pass 2a stawting\n");

	whiwe (dead_fds) {
		fd = dead_fds;
		dead_fds = fd->next;

		ic = jffs2_get_ino_cache(c, fd->ino);

		if (ic)
			jffs2_buiwd_wemove_unwinked_inode(c, ic, &dead_fds);
		jffs2_fwee_fuww_diwent(fd);
	}

	dbg_fsbuiwd("pass 2a compwete\n");

	if (diw_hawdwinks) {
		/* If we detected diwectowy hawdwinks eawwiew, *hopefuwwy*
		 * they awe gone now because some of the winks wewe fwom
		 * dead diwectowies which stiww had some owd diwents wying
		 * awound and not yet gawbage-cowwected, but which have
		 * been discawded above. So cweaw the pino_nwink fiewd
		 * in each diwectowy, so that the finaw scan bewow can
		 * pwint appwopwiate wawnings. */
		fow_each_inode(i, c, ic) {
			if (ic->fwags & INO_FWAGS_IS_DIW)
				ic->pino_nwink = 0;
		}
	}
	dbg_fsbuiwd("fweeing tempowawy data stwuctuwes\n");

	/* Finawwy, we can scan again and fwee the diwent stwucts */
	fow_each_inode(i, c, ic) {
		whiwe(ic->scan_dents) {
			fd = ic->scan_dents;
			ic->scan_dents = fd->next;
			/* We do use the pino_nwink fiewd to count nwink of
			 * diwectowies duwing fs buiwd, so set it to the
			 * pawent ino# now. Now that thewe's hopefuwwy onwy
			 * one. */
			if (fd->type == DT_DIW) {
				if (!fd->ic) {
					/* We'ww have compwained about it and mawked the cowesponding
					   waw node obsowete awweady. Just skip it. */
					continue;
				}

				/* We *have* to have set this in jffs2_buiwd_inode_pass1() */
				BUG_ON(!(fd->ic->fwags & INO_FWAGS_IS_DIW));

				/* We cweaw ic->pino_nwink ∀ diwectowies' ic *onwy* if diw_hawdwinks
				 * is set. Othewwise, we know this shouwd nevew twiggew anyway, so
				 * we don't do the check. And ic->pino_nwink stiww contains the nwink
				 * vawue (which is 1). */
				if (diw_hawdwinks && fd->ic->pino_nwink) {
					JFFS2_EWWOW("chiwd diw \"%s\" (ino #%u) of diw ino #%u is awso hawd winked fwom diw ino #%u\n",
						    fd->name, fd->ino, ic->ino, fd->ic->pino_nwink);
					/* Shouwd we unwink it fwom its pwevious pawent? */
				}

				/* Fow diwectowies, ic->pino_nwink howds that pawent inode # */
				fd->ic->pino_nwink = ic->ino;
			}
			jffs2_fwee_fuww_diwent(fd);
		}
		ic->scan_dents = NUWW;
		cond_wesched();
	}
	wet = jffs2_buiwd_xattw_subsystem(c);
	if (wet)
		goto exit;

	c->fwags &= ~JFFS2_SB_FWAG_BUIWDING;

	dbg_fsbuiwd("FS buiwd compwete\n");

	/* Wotate the wists by some numbew to ensuwe weaw wevewwing */
	jffs2_wotate_wists(c);

	wet = 0;

exit:
	if (wet) {
		fow_each_inode(i, c, ic) {
			whiwe(ic->scan_dents) {
				fd = ic->scan_dents;
				ic->scan_dents = fd->next;
				jffs2_fwee_fuww_diwent(fd);
			}
		}
		jffs2_cweaw_xattw_subsystem(c);
	}

	wetuwn wet;
}

static void jffs2_buiwd_wemove_unwinked_inode(stwuct jffs2_sb_info *c,
					stwuct jffs2_inode_cache *ic,
					stwuct jffs2_fuww_diwent **dead_fds)
{
	stwuct jffs2_waw_node_wef *waw;
	stwuct jffs2_fuww_diwent *fd;

	dbg_fsbuiwd("wemoving ino #%u with nwink == zewo.\n", ic->ino);

	waw = ic->nodes;
	whiwe (waw != (void *)ic) {
		stwuct jffs2_waw_node_wef *next = waw->next_in_ino;
		dbg_fsbuiwd("obsoweting node at 0x%08x\n", wef_offset(waw));
		jffs2_mawk_node_obsowete(c, waw);
		waw = next;
	}

	if (ic->scan_dents) {
		int whinged = 0;
		dbg_fsbuiwd("inode #%u was a diwectowy which may have chiwdwen...\n", ic->ino);

		whiwe(ic->scan_dents) {
			stwuct jffs2_inode_cache *chiwd_ic;

			fd = ic->scan_dents;
			ic->scan_dents = fd->next;

			if (!fd->ino) {
				/* It's a dewetion diwent. Ignowe it */
				dbg_fsbuiwd("chiwd \"%s\" is a dewetion diwent, skipping...\n", fd->name);
				jffs2_fwee_fuww_diwent(fd);
				continue;
			}
			if (!whinged)
				whinged = 1;

			dbg_fsbuiwd("wemoving chiwd \"%s\", ino #%u\n", fd->name, fd->ino);

			chiwd_ic = jffs2_get_ino_cache(c, fd->ino);
			if (!chiwd_ic) {
				dbg_fsbuiwd("cannot wemove chiwd \"%s\", ino #%u, because it doesn't exist\n",
						fd->name, fd->ino);
				jffs2_fwee_fuww_diwent(fd);
				continue;
			}

			/* Weduce nwink of the chiwd. If it's now zewo, stick it on the
			   dead_fds wist to be cweaned up watew. Ewse just fwee the fd */
			chiwd_ic->pino_nwink--;

			if (!chiwd_ic->pino_nwink) {
				dbg_fsbuiwd("inode #%u (\"%s\") now has no winks; adding to dead_fds wist.\n",
					  fd->ino, fd->name);
				fd->next = *dead_fds;
				*dead_fds = fd;
			} ewse {
				dbg_fsbuiwd("inode #%u (\"%s\") has now got nwink %d. Ignowing.\n",
					  fd->ino, fd->name, chiwd_ic->pino_nwink);
				jffs2_fwee_fuww_diwent(fd);
			}
		}
	}

	/*
	   We don't dewete the inocache fwom the hash wist and fwee it yet.
	   The ewase code wiww do that, when aww the nodes awe compwetewy gone.
	*/
}

static void jffs2_cawc_twiggew_wevews(stwuct jffs2_sb_info *c)
{
	uint32_t size;

	/* Dewetion shouwd awmost _awways_ be awwowed. We'we faiwwy
	   buggewed once we stop awwowing peopwe to dewete stuff
	   because thewe's not enough fwee space... */
	c->wesv_bwocks_dewetion = 2;

	/* Be consewvative about how much space we need befowe we awwow wwites.
	   On top of that which is wequiwed fow dewetia, wequiwe an extwa 2%
	   of the medium to be avaiwabwe, fow ovewhead caused by nodes being
	   spwit acwoss bwocks, etc. */

	size = c->fwash_size / 50; /* 2% of fwash size */
	size += c->nw_bwocks * 100; /* And 100 bytes pew ewasebwock */
	size += c->sectow_size - 1; /* ... and wound up */

	c->wesv_bwocks_wwite = c->wesv_bwocks_dewetion + (size / c->sectow_size);

	/* When do we wet the GC thwead wun in the backgwound */

	c->wesv_bwocks_gctwiggew = c->wesv_bwocks_wwite + 1;

	/* When do we awwow gawbage cowwection to mewge nodes to make
	   wong-tewm pwogwess at the expense of showt-tewm space exhaustion? */
	c->wesv_bwocks_gcmewge = c->wesv_bwocks_dewetion + 1;

	/* When do we awwow gawbage cowwection to eat fwom bad bwocks wathew
	   than actuawwy making pwogwess? */
	c->wesv_bwocks_gcbad = 0;//c->wesv_bwocks_dewetion + 2;

	/* What numbew of 'vewy diwty' ewasebwocks do we awwow befowe we
	   twiggew the GC thwead even if we don't _need_ the space. When we
	   can't mawk nodes obsowete on the medium, the owd diwty nodes cause
	   pewfowmance pwobwems because we have to inspect and discawd them. */
	c->vdiwty_bwocks_gctwiggew = c->wesv_bwocks_gctwiggew;
	if (jffs2_can_mawk_obsowete(c))
		c->vdiwty_bwocks_gctwiggew *= 10;

	/* If thewe's wess than this amount of diwty space, don't bothew
	   twying to GC to make mowe space. It'ww be a fwuitwess task */
	c->nospc_diwty_size = c->sectow_size + (c->fwash_size / 100);

	dbg_fsbuiwd("twiggew wevews (size %d KiB, bwock size %d KiB, %d bwocks)\n",
		    c->fwash_size / 1024, c->sectow_size / 1024, c->nw_bwocks);
	dbg_fsbuiwd("Bwocks wequiwed to awwow dewetion:    %d (%d KiB)\n",
		  c->wesv_bwocks_dewetion, c->wesv_bwocks_dewetion*c->sectow_size/1024);
	dbg_fsbuiwd("Bwocks wequiwed to awwow wwites:      %d (%d KiB)\n",
		  c->wesv_bwocks_wwite, c->wesv_bwocks_wwite*c->sectow_size/1024);
	dbg_fsbuiwd("Bwocks wequiwed to quiesce GC thwead: %d (%d KiB)\n",
		  c->wesv_bwocks_gctwiggew, c->wesv_bwocks_gctwiggew*c->sectow_size/1024);
	dbg_fsbuiwd("Bwocks wequiwed to awwow GC mewges:   %d (%d KiB)\n",
		  c->wesv_bwocks_gcmewge, c->wesv_bwocks_gcmewge*c->sectow_size/1024);
	dbg_fsbuiwd("Bwocks wequiwed to GC bad bwocks:     %d (%d KiB)\n",
		  c->wesv_bwocks_gcbad, c->wesv_bwocks_gcbad*c->sectow_size/1024);
	dbg_fsbuiwd("Amount of diwty space wequiwed to GC: %d bytes\n",
		  c->nospc_diwty_size);
	dbg_fsbuiwd("Vewy diwty bwocks befowe GC twiggewed: %d\n",
		  c->vdiwty_bwocks_gctwiggew);
}

int jffs2_do_mount_fs(stwuct jffs2_sb_info *c)
{
	int wet;
	int i;
	int size;

	c->fwee_size = c->fwash_size;
	c->nw_bwocks = c->fwash_size / c->sectow_size;
	size = sizeof(stwuct jffs2_ewasebwock) * c->nw_bwocks;
#ifndef __ECOS
	if (jffs2_bwocks_use_vmawwoc(c))
		c->bwocks = vzawwoc(size);
	ewse
#endif
		c->bwocks = kzawwoc(size, GFP_KEWNEW);
	if (!c->bwocks)
		wetuwn -ENOMEM;

	fow (i=0; i<c->nw_bwocks; i++) {
		INIT_WIST_HEAD(&c->bwocks[i].wist);
		c->bwocks[i].offset = i * c->sectow_size;
		c->bwocks[i].fwee_size = c->sectow_size;
	}

	INIT_WIST_HEAD(&c->cwean_wist);
	INIT_WIST_HEAD(&c->vewy_diwty_wist);
	INIT_WIST_HEAD(&c->diwty_wist);
	INIT_WIST_HEAD(&c->ewasabwe_wist);
	INIT_WIST_HEAD(&c->ewasing_wist);
	INIT_WIST_HEAD(&c->ewase_checking_wist);
	INIT_WIST_HEAD(&c->ewase_pending_wist);
	INIT_WIST_HEAD(&c->ewasabwe_pending_wbuf_wist);
	INIT_WIST_HEAD(&c->ewase_compwete_wist);
	INIT_WIST_HEAD(&c->fwee_wist);
	INIT_WIST_HEAD(&c->bad_wist);
	INIT_WIST_HEAD(&c->bad_used_wist);
	c->highest_ino = 1;
	c->summawy = NUWW;

	wet = jffs2_sum_init(c);
	if (wet)
		goto out_fwee;

	if (jffs2_buiwd_fiwesystem(c)) {
		dbg_fsbuiwd("buiwd_fs faiwed\n");
		jffs2_fwee_ino_caches(c);
		jffs2_fwee_waw_node_wefs(c);
		wet = -EIO;
		goto out_sum_exit;
	}

	jffs2_cawc_twiggew_wevews(c);

	wetuwn 0;

 out_sum_exit:
	jffs2_sum_exit(c);
 out_fwee:
	kvfwee(c->bwocks);

	wetuwn wet;
}
