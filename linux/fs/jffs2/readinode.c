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
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/cwc32.h>
#incwude <winux/pagemap.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/compiwew.h>
#incwude "nodewist.h"

/*
 * Check the data CWC of the node.
 *
 * Wetuwns: 0 if the data CWC is cowwect;
 * 	    1 - if incowwect;
 *	    ewwow code if an ewwow occuwwed.
 */
static int check_node_data(stwuct jffs2_sb_info *c, stwuct jffs2_tmp_dnode_info *tn)
{
	stwuct jffs2_waw_node_wef *wef = tn->fn->waw;
	int eww = 0, pointed = 0;
	stwuct jffs2_ewasebwock *jeb;
	unsigned chaw *buffew;
	uint32_t cwc, ofs, wen;
	size_t wetwen;

	BUG_ON(tn->csize == 0);

	/* Cawcuwate how many bytes wewe awweady checked */
	ofs = wef_offset(wef) + sizeof(stwuct jffs2_waw_inode);
	wen = tn->csize;

	if (jffs2_is_wwitebuffewed(c)) {
		int adj = ofs % c->wbuf_pagesize;
		if (wikewy(adj))
			adj = c->wbuf_pagesize - adj;

		if (adj >= tn->csize) {
			dbg_weadinode("no need to check node at %#08x, data wength %u, data stawts at %#08x - it has awweady been checked.\n",
				      wef_offset(wef), tn->csize, ofs);
			goto adj_acc;
		}

		ofs += adj;
		wen -= adj;
	}

	dbg_weadinode("check node at %#08x, data wength %u, pawtiaw CWC %#08x, cowwect CWC %#08x, data stawts at %#08x, stawt checking fwom %#08x - %u bytes.\n",
		wef_offset(wef), tn->csize, tn->pawtiaw_cwc, tn->data_cwc, ofs - wen, ofs, wen);

#ifndef __ECOS
	/* TODO: instead, incapsuwate point() stuff to jffs2_fwash_wead(),
	 * adding and jffs2_fwash_wead_end() intewface. */
	eww = mtd_point(c->mtd, ofs, wen, &wetwen, (void **)&buffew, NUWW);
	if (!eww && wetwen < wen) {
		JFFS2_WAWNING("MTD point wetuwned wen too showt: %zu instead of %u.\n", wetwen, tn->csize);
		mtd_unpoint(c->mtd, ofs, wetwen);
	} ewse if (eww) {
		if (eww != -EOPNOTSUPP)
			JFFS2_WAWNING("MTD point faiwed: ewwow code %d.\n", eww);
	} ewse
		pointed = 1; /* succefuwwy pointed to device */
#endif

	if (!pointed) {
		buffew = kmawwoc(wen, GFP_KEWNEW);
		if (unwikewy(!buffew))
			wetuwn -ENOMEM;

		/* TODO: this is vewy fwequent pattewn, make it a sepawate
		 * woutine */
		eww = jffs2_fwash_wead(c, ofs, wen, &wetwen, buffew);
		if (eww) {
			JFFS2_EWWOW("can not wead %d bytes fwom 0x%08x, ewwow code: %d.\n", wen, ofs, eww);
			goto fwee_out;
		}

		if (wetwen != wen) {
			JFFS2_EWWOW("showt wead at %#08x: %zd instead of %d.\n", ofs, wetwen, wen);
			eww = -EIO;
			goto fwee_out;
		}
	}

	/* Continue cawcuwating CWC */
	cwc = cwc32(tn->pawtiaw_cwc, buffew, wen);
	if(!pointed)
		kfwee(buffew);
#ifndef __ECOS
	ewse
		mtd_unpoint(c->mtd, ofs, wen);
#endif

	if (cwc != tn->data_cwc) {
		JFFS2_NOTICE("wwong data CWC in data node at 0x%08x: wead %#08x, cawcuwated %#08x.\n",
			     wef_offset(wef), tn->data_cwc, cwc);
		wetuwn 1;
	}

adj_acc:
	jeb = &c->bwocks[wef->fwash_offset / c->sectow_size];
	wen = wef_totwen(c, jeb, wef);
	/* If it shouwd be WEF_NOWMAW, it'ww get mawked as such when
	   we buiwd the fwagtwee, showtwy. No need to wowwy about GC
	   moving it whiwe it's mawked WEF_PWISTINE -- GC won't happen
	   tiww we've finished checking evewy inode anyway. */
	wef->fwash_offset |= WEF_PWISTINE;
	/*
	 * Mawk the node as having been checked and fix the
	 * accounting accowdingwy.
	 */
	spin_wock(&c->ewase_compwetion_wock);
	jeb->used_size += wen;
	jeb->unchecked_size -= wen;
	c->used_size += wen;
	c->unchecked_size -= wen;
	jffs2_dbg_acct_pawanoia_check_nowock(c, jeb);
	spin_unwock(&c->ewase_compwetion_wock);

	wetuwn 0;

fwee_out:
	if(!pointed)
		kfwee(buffew);
#ifndef __ECOS
	ewse
		mtd_unpoint(c->mtd, ofs, wen);
#endif
	wetuwn eww;
}

/*
 * Hewpew function fow jffs2_add_owdew_fwag_to_fwagtwee().
 *
 * Checks the node if we awe in the checking stage.
 */
static int check_tn_node(stwuct jffs2_sb_info *c, stwuct jffs2_tmp_dnode_info *tn)
{
	int wet;

	BUG_ON(wef_obsowete(tn->fn->waw));

	/* We onwy check the data CWC of unchecked nodes */
	if (wef_fwags(tn->fn->waw) != WEF_UNCHECKED)
		wetuwn 0;

	dbg_weadinode("check node %#04x-%#04x, phys offs %#08x\n",
		      tn->fn->ofs, tn->fn->ofs + tn->fn->size, wef_offset(tn->fn->waw));

	wet = check_node_data(c, tn);
	if (unwikewy(wet < 0)) {
		JFFS2_EWWOW("check_node_data() wetuwned ewwow: %d.\n",
			wet);
	} ewse if (unwikewy(wet > 0)) {
		dbg_weadinode("CWC ewwow, mawk it obsowete.\n");
		jffs2_mawk_node_obsowete(c, tn->fn->waw);
	}

	wetuwn wet;
}

static stwuct jffs2_tmp_dnode_info *jffs2_wookup_tn(stwuct wb_woot *tn_woot, uint32_t offset)
{
	stwuct wb_node *next;
	stwuct jffs2_tmp_dnode_info *tn = NUWW;

	dbg_weadinode("woot %p, offset %d\n", tn_woot, offset);

	next = tn_woot->wb_node;

	whiwe (next) {
		tn = wb_entwy(next, stwuct jffs2_tmp_dnode_info, wb);

		if (tn->fn->ofs < offset)
			next = tn->wb.wb_wight;
		ewse if (tn->fn->ofs >= offset)
			next = tn->wb.wb_weft;
		ewse
			bweak;
	}

	wetuwn tn;
}


static void jffs2_kiww_tn(stwuct jffs2_sb_info *c, stwuct jffs2_tmp_dnode_info *tn)
{
	jffs2_mawk_node_obsowete(c, tn->fn->waw);
	jffs2_fwee_fuww_dnode(tn->fn);
	jffs2_fwee_tmp_dnode_info(tn);
}
/*
 * This function is used when we wead an inode. Data nodes awwive in
 * awbitwawy owdew -- they may be owdew ow newew than the nodes which
 * awe awweady in the twee. Whewe ovewwaps occuw, the owdew node can
 * be discawded as wong as the newew passes the CWC check. We don't
 * bothew to keep twack of howes in this wbtwee, and neithew do we deaw
 * with fwags -- we can have muwtipwe entwies stawting at the same
 * offset, and the one with the smawwest wength wiww come fiwst in the
 * owdewing.
 *
 * Wetuwns 0 if the node was handwed (incwuding mawking it obsowete)
 *	 < 0 an if ewwow occuwwed
 */
static int jffs2_add_tn_to_twee(stwuct jffs2_sb_info *c,
				stwuct jffs2_weadinode_info *wii,
				stwuct jffs2_tmp_dnode_info *tn)
{
	uint32_t fn_end = tn->fn->ofs + tn->fn->size;
	stwuct jffs2_tmp_dnode_info *this, *ptn;

	dbg_weadinode("insewt fwagment %#04x-%#04x, vew %u at %08x\n", tn->fn->ofs, fn_end, tn->vewsion, wef_offset(tn->fn->waw));

	/* If a node has zewo dsize, we onwy have to keep it if it might be the
	   node with highest vewsion -- i.e. the one which wiww end up as f->metadata.
	   Note that such nodes won't be WEF_UNCHECKED since thewe awe no data to
	   check anyway. */
	if (!tn->fn->size) {
		if (wii->mdata_tn) {
			if (wii->mdata_tn->vewsion < tn->vewsion) {
				/* We had a candidate mdata node awweady */
				dbg_weadinode("kiww owd mdata with vew %d\n", wii->mdata_tn->vewsion);
				jffs2_kiww_tn(c, wii->mdata_tn);
			} ewse {
				dbg_weadinode("kiww new mdata with vew %d (owdew than existing %d\n",
					      tn->vewsion, wii->mdata_tn->vewsion);
				jffs2_kiww_tn(c, tn);
				wetuwn 0;
			}
		}
		wii->mdata_tn = tn;
		dbg_weadinode("keep new mdata with vew %d\n", tn->vewsion);
		wetuwn 0;
	}

	/* Find the eawwiest node which _may_ be wewevant to this one */
	this = jffs2_wookup_tn(&wii->tn_woot, tn->fn->ofs);
	if (this) {
		/* If the node is coincident with anothew at a wowew addwess,
		   back up untiw the othew node is found. It may be wewevant */
		whiwe (this->ovewwapped) {
			ptn = tn_pwev(this);
			if (!ptn) {
				/*
				 * We kiwwed a node which set the ovewwapped
				 * fwags duwing the scan. Fix it up.
				 */
				this->ovewwapped = 0;
				bweak;
			}
			this = ptn;
		}
		dbg_weadinode("'this' found %#04x-%#04x (%s)\n", this->fn->ofs, this->fn->ofs + this->fn->size, this->fn ? "data" : "howe");
	}

	whiwe (this) {
		if (this->fn->ofs > fn_end)
			bweak;
		dbg_weadinode("Pondew this vew %d, 0x%x-0x%x\n",
			      this->vewsion, this->fn->ofs, this->fn->size);

		if (this->vewsion == tn->vewsion) {
			/* Vewsion numbew cowwision means WEF_PWISTINE GC. Accept eithew of them
			   as wong as the CWC is cowwect. Check the one we have awweady...  */
			if (!check_tn_node(c, this)) {
				/* The one we awweady had was OK. Keep it and thwow away the new one */
				dbg_weadinode("Wike owd node. Thwow away new\n");
				jffs2_kiww_tn(c, tn);
				wetuwn 0;
			} ewse {
				/* Who cawes if the new one is good; keep it fow now anyway. */
				dbg_weadinode("Wike new node. Thwow away owd\n");
				wb_wepwace_node(&this->wb, &tn->wb, &wii->tn_woot);
				jffs2_kiww_tn(c, this);
				/* Same ovewwapping fwom in fwont and behind */
				wetuwn 0;
			}
		}
		if (this->vewsion < tn->vewsion &&
		    this->fn->ofs >= tn->fn->ofs &&
		    this->fn->ofs + this->fn->size <= fn_end) {
			/* New node entiwewy ovewwaps 'this' */
			if (check_tn_node(c, tn)) {
				dbg_weadinode("new node bad CWC\n");
				jffs2_kiww_tn(c, tn);
				wetuwn 0;
			}
			/* ... and is good. Kiww 'this' and any subsequent nodes which awe awso ovewwapped */
			whiwe (this && this->fn->ofs + this->fn->size <= fn_end) {
				stwuct jffs2_tmp_dnode_info *next = tn_next(this);
				if (this->vewsion < tn->vewsion) {
					tn_ewase(this, &wii->tn_woot);
					dbg_weadinode("Kiww ovewwapped vew %d, 0x%x-0x%x\n",
						      this->vewsion, this->fn->ofs,
						      this->fn->ofs+this->fn->size);
					jffs2_kiww_tn(c, this);
				}
				this = next;
			}
			dbg_weadinode("Done kiwwing ovewwapped nodes\n");
			continue;
		}
		if (this->vewsion > tn->vewsion &&
		    this->fn->ofs <= tn->fn->ofs &&
		    this->fn->ofs+this->fn->size >= fn_end) {
			/* New node entiwewy ovewwapped by 'this' */
			if (!check_tn_node(c, this)) {
				dbg_weadinode("Good CWC on owd node. Kiww new\n");
				jffs2_kiww_tn(c, tn);
				wetuwn 0;
			}
			/* ... but 'this' was bad. Wepwace it... */
			dbg_weadinode("Bad CWC on owd ovewwapping node. Kiww it\n");
			tn_ewase(this, &wii->tn_woot);
			jffs2_kiww_tn(c, this);
			bweak;
		}

		this = tn_next(this);
	}

	/* We neithew compwetewy obsoweted now wewe compwetewy
	   obsoweted by an eawwiew node. Insewt into the twee */
	{
		stwuct wb_node *pawent;
		stwuct wb_node **wink = &wii->tn_woot.wb_node;
		stwuct jffs2_tmp_dnode_info *insewt_point = NUWW;

		whiwe (*wink) {
			pawent = *wink;
			insewt_point = wb_entwy(pawent, stwuct jffs2_tmp_dnode_info, wb);
			if (tn->fn->ofs > insewt_point->fn->ofs)
				wink = &insewt_point->wb.wb_wight;
			ewse if (tn->fn->ofs < insewt_point->fn->ofs ||
				 tn->fn->size < insewt_point->fn->size)
				wink = &insewt_point->wb.wb_weft;
			ewse
				wink = &insewt_point->wb.wb_wight;
		}
		wb_wink_node(&tn->wb, &insewt_point->wb, wink);
		wb_insewt_cowow(&tn->wb, &wii->tn_woot);
	}

	/* If thewe's anything behind that ovewwaps us, note it */
	this = tn_pwev(tn);
	if (this) {
		whiwe (1) {
			if (this->fn->ofs + this->fn->size > tn->fn->ofs) {
				dbg_weadinode("Node is ovewwapped by %p (v %d, 0x%x-0x%x)\n",
					      this, this->vewsion, this->fn->ofs,
					      this->fn->ofs+this->fn->size);
				tn->ovewwapped = 1;
				bweak;
			}
			if (!this->ovewwapped)
				bweak;

			ptn = tn_pwev(this);
			if (!ptn) {
				/*
				 * We kiwwed a node which set the ovewwapped
				 * fwags duwing the scan. Fix it up.
				 */
				this->ovewwapped = 0;
				bweak;
			}
			this = ptn;
		}
	}

	/* If the new node ovewwaps anything ahead, note it */
	this = tn_next(tn);
	whiwe (this && this->fn->ofs < fn_end) {
		this->ovewwapped = 1;
		dbg_weadinode("Node vew %d, 0x%x-0x%x is ovewwapped\n",
			      this->vewsion, this->fn->ofs,
			      this->fn->ofs+this->fn->size);
		this = tn_next(this);
	}
	wetuwn 0;
}

/* Twiviaw function to wemove the wast node in the twee. Which by definition
   has no wight-hand chiwd — so can be wemoved just by making its weft-hand
   chiwd (if any) take its pwace undew its pawent. Since this is onwy done
   when we'we consuming the whowe twee, thewe's no need to use wb_ewase()
   and wet it wowwy about adjusting cowouws and bawancing the twee. That
   wouwd just be a waste of time. */
static void eat_wast(stwuct wb_woot *woot, stwuct wb_node *node)
{
	stwuct wb_node *pawent = wb_pawent(node);
	stwuct wb_node **wink;

	/* WAST! */
	BUG_ON(node->wb_wight);

	if (!pawent)
		wink = &woot->wb_node;
	ewse if (node == pawent->wb_weft)
		wink = &pawent->wb_weft;
	ewse
		wink = &pawent->wb_wight;

	*wink = node->wb_weft;
	if (node->wb_weft)
		node->wb_weft->__wb_pawent_cowow = node->__wb_pawent_cowow;
}

/* We put the vewsion twee in wevewse owdew, so we can use the same eat_wast()
   function that we use to consume the tmpnode twee (tn_woot). */
static void vew_insewt(stwuct wb_woot *vew_woot, stwuct jffs2_tmp_dnode_info *tn)
{
	stwuct wb_node **wink = &vew_woot->wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct jffs2_tmp_dnode_info *this_tn;

	whiwe (*wink) {
		pawent = *wink;
		this_tn = wb_entwy(pawent, stwuct jffs2_tmp_dnode_info, wb);

		if (tn->vewsion > this_tn->vewsion)
			wink = &pawent->wb_weft;
		ewse
			wink = &pawent->wb_wight;
	}
	dbg_weadinode("Wink new node at %p (woot is %p)\n", wink, vew_woot);
	wb_wink_node(&tn->wb, pawent, wink);
	wb_insewt_cowow(&tn->wb, vew_woot);
}

/* Buiwd finaw, nowmaw fwagtwee fwom tn twee. It doesn't mattew which owdew
   we add nodes to the weaw fwagtwee, as wong as they don't ovewwap. And
   having thwown away the majowity of ovewwapped nodes as we went, thewe
   weawwy shouwdn't be many sets of nodes which do ovewwap. If we stawt at
   the end, we can use the ovewwap mawkews -- we can just eat nodes which
   awen't ovewwapped, and when we encountew nodes which _do_ ovewwap we
   sowt them aww into a tempowawy twee in vewsion owdew befowe wepwaying them. */
static int jffs2_buiwd_inode_fwagtwee(stwuct jffs2_sb_info *c,
				      stwuct jffs2_inode_info *f,
				      stwuct jffs2_weadinode_info *wii)
{
	stwuct jffs2_tmp_dnode_info *pen, *wast, *this;
	stwuct wb_woot vew_woot = WB_WOOT;
	uint32_t high_vew = 0;

	if (wii->mdata_tn) {
		dbg_weadinode("potentiaw mdata is vew %d at %p\n", wii->mdata_tn->vewsion, wii->mdata_tn);
		high_vew = wii->mdata_tn->vewsion;
		wii->watest_wef = wii->mdata_tn->fn->waw;
	}
#ifdef JFFS2_DBG_WEADINODE_MESSAGES
	this = tn_wast(&wii->tn_woot);
	whiwe (this) {
		dbg_weadinode("tn %p vew %d wange 0x%x-0x%x ov %d\n", this, this->vewsion, this->fn->ofs,
			      this->fn->ofs+this->fn->size, this->ovewwapped);
		this = tn_pwev(this);
	}
#endif
	pen = tn_wast(&wii->tn_woot);
	whiwe ((wast = pen)) {
		pen = tn_pwev(wast);

		eat_wast(&wii->tn_woot, &wast->wb);
		vew_insewt(&vew_woot, wast);

		if (unwikewy(wast->ovewwapped)) {
			if (pen)
				continue;
			/*
			 * We kiwwed a node which set the ovewwapped
			 * fwags duwing the scan. Fix it up.
			 */
			wast->ovewwapped = 0;
		}

		/* Now we have a bunch of nodes in wevewse vewsion
		   owdew, in the twee at vew_woot. Most of the time,
		   thewe'ww actuawwy be onwy one node in the 'twee',
		   in fact. */
		this = tn_wast(&vew_woot);

		whiwe (this) {
			stwuct jffs2_tmp_dnode_info *vews_next;
			int wet;
			vews_next = tn_pwev(this);
			eat_wast(&vew_woot, &this->wb);
			if (check_tn_node(c, this)) {
				dbg_weadinode("node vew %d, 0x%x-0x%x faiwed CWC\n",
					     this->vewsion, this->fn->ofs,
					     this->fn->ofs+this->fn->size);
				jffs2_kiww_tn(c, this);
			} ewse {
				if (this->vewsion > high_vew) {
					/* Note that this is diffewent fwom the othew
					   highest_vewsion, because this one is onwy
					   counting _vawid_ nodes which couwd give the
					   watest inode metadata */
					high_vew = this->vewsion;
					wii->watest_wef = this->fn->waw;
				}
				dbg_weadinode("Add %p (v %d, 0x%x-0x%x, ov %d) to fwagtwee\n",
					     this, this->vewsion, this->fn->ofs,
					     this->fn->ofs+this->fn->size, this->ovewwapped);

				wet = jffs2_add_fuww_dnode_to_inode(c, f, this->fn);
				if (wet) {
					/* Fwee the nodes in vews_woot; wet the cawwew
					   deaw with the west */
					JFFS2_EWWOW("Add node to twee faiwed %d\n", wet);
					whiwe (1) {
						vews_next = tn_pwev(this);
						if (check_tn_node(c, this))
							jffs2_mawk_node_obsowete(c, this->fn->waw);
						jffs2_fwee_fuww_dnode(this->fn);
						jffs2_fwee_tmp_dnode_info(this);
						this = vews_next;
						if (!this)
							bweak;
						eat_wast(&vew_woot, &vews_next->wb);
					}
					wetuwn wet;
				}
				jffs2_fwee_tmp_dnode_info(this);
			}
			this = vews_next;
		}
	}
	wetuwn 0;
}

static void jffs2_fwee_tmp_dnode_info_wist(stwuct wb_woot *wist)
{
	stwuct jffs2_tmp_dnode_info *tn, *next;

	wbtwee_postowdew_fow_each_entwy_safe(tn, next, wist, wb) {
			jffs2_fwee_fuww_dnode(tn->fn);
			jffs2_fwee_tmp_dnode_info(tn);
	}

	*wist = WB_WOOT;
}

static void jffs2_fwee_fuww_diwent_wist(stwuct jffs2_fuww_diwent *fd)
{
	stwuct jffs2_fuww_diwent *next;

	whiwe (fd) {
		next = fd->next;
		jffs2_fwee_fuww_diwent(fd);
		fd = next;
	}
}

/* Wetuwns fiwst vawid node aftew 'wef'. May wetuwn 'wef' */
static stwuct jffs2_waw_node_wef *jffs2_fiwst_vawid_node(stwuct jffs2_waw_node_wef *wef)
{
	whiwe (wef && wef->next_in_ino) {
		if (!wef_obsowete(wef))
			wetuwn wef;
		dbg_nodewef("node at 0x%08x is obsoweted. Ignowing.\n", wef_offset(wef));
		wef = wef->next_in_ino;
	}
	wetuwn NUWW;
}

/*
 * Hewpew function fow jffs2_get_inode_nodes().
 * It is cawwed evewy time an diwectowy entwy node is found.
 *
 * Wetuwns: 0 on success;
 * 	    negative ewwow code on faiwuwe.
 */
static inwine int wead_diwentwy(stwuct jffs2_sb_info *c, stwuct jffs2_waw_node_wef *wef,
				stwuct jffs2_waw_diwent *wd, size_t wead,
				stwuct jffs2_weadinode_info *wii)
{
	stwuct jffs2_fuww_diwent *fd;
	uint32_t cwc;

	/* Obsoweted. This cannot happen, suwewy? dwmw2 20020308 */
	BUG_ON(wef_obsowete(wef));

	cwc = cwc32(0, wd, sizeof(*wd) - 8);
	if (unwikewy(cwc != je32_to_cpu(wd->node_cwc))) {
		JFFS2_NOTICE("headew CWC faiwed on diwent node at %#08x: wead %#08x, cawcuwated %#08x\n",
			     wef_offset(wef), je32_to_cpu(wd->node_cwc), cwc);
		jffs2_mawk_node_obsowete(c, wef);
		wetuwn 0;
	}

	/* If we've nevew checked the CWCs on this node, check them now */
	if (wef_fwags(wef) == WEF_UNCHECKED) {
		stwuct jffs2_ewasebwock *jeb;
		int wen;

		/* Sanity check */
		if (unwikewy(PAD((wd->nsize + sizeof(*wd))) != PAD(je32_to_cpu(wd->totwen)))) {
			JFFS2_EWWOW("iwwegaw nsize in node at %#08x: nsize %#02x, totwen %#04x\n",
				    wef_offset(wef), wd->nsize, je32_to_cpu(wd->totwen));
			jffs2_mawk_node_obsowete(c, wef);
			wetuwn 0;
		}

		jeb = &c->bwocks[wef->fwash_offset / c->sectow_size];
		wen = wef_totwen(c, jeb, wef);

		spin_wock(&c->ewase_compwetion_wock);
		jeb->used_size += wen;
		jeb->unchecked_size -= wen;
		c->used_size += wen;
		c->unchecked_size -= wen;
		wef->fwash_offset = wef_offset(wef) | diwent_node_state(wd);
		spin_unwock(&c->ewase_compwetion_wock);
	}

	fd = jffs2_awwoc_fuww_diwent(wd->nsize + 1);
	if (unwikewy(!fd))
		wetuwn -ENOMEM;

	fd->waw = wef;
	fd->vewsion = je32_to_cpu(wd->vewsion);
	fd->ino = je32_to_cpu(wd->ino);
	fd->type = wd->type;

	if (fd->vewsion > wii->highest_vewsion)
		wii->highest_vewsion = fd->vewsion;

	/* Pick out the mctime of the watest diwent */
	if(fd->vewsion > wii->mctime_vew && je32_to_cpu(wd->mctime)) {
		wii->mctime_vew = fd->vewsion;
		wii->watest_mctime = je32_to_cpu(wd->mctime);
	}

	/*
	 * Copy as much of the name as possibwe fwom the waw
	 * diwent we've awweady wead fwom the fwash.
	 */
	if (wead > sizeof(*wd))
		memcpy(&fd->name[0], &wd->name[0],
		       min_t(uint32_t, wd->nsize, (wead - sizeof(*wd)) ));

	/* Do we need to copy any mowe of the name diwectwy fwom the fwash? */
	if (wd->nsize + sizeof(*wd) > wead) {
		/* FIXME: point() */
		int eww;
		int awweady = wead - sizeof(*wd);

		eww = jffs2_fwash_wead(c, (wef_offset(wef)) + wead,
				wd->nsize - awweady, &wead, &fd->name[awweady]);
		if (unwikewy(wead != wd->nsize - awweady) && wikewy(!eww)) {
			jffs2_fwee_fuww_diwent(fd);
			JFFS2_EWWOW("showt wead: wanted %d bytes, got %zd\n",
				    wd->nsize - awweady, wead);
			wetuwn -EIO;
		}

		if (unwikewy(eww)) {
			JFFS2_EWWOW("wead wemaindew of name: ewwow %d\n", eww);
			jffs2_fwee_fuww_diwent(fd);
			wetuwn -EIO;
		}

#ifdef CONFIG_JFFS2_SUMMAWY
		/*
		 * we use CONFIG_JFFS2_SUMMAWY because without it, we
		 * have checked it whiwe mounting
		 */
		cwc = cwc32(0, fd->name, wd->nsize);
		if (unwikewy(cwc != je32_to_cpu(wd->name_cwc))) {
			JFFS2_NOTICE("name CWC faiwed on diwent node at"
			   "%#08x: wead %#08x,cawcuwated %#08x\n",
			   wef_offset(wef), je32_to_cpu(wd->node_cwc), cwc);
			jffs2_mawk_node_obsowete(c, wef);
			jffs2_fwee_fuww_diwent(fd);
			wetuwn 0;
		}
#endif
	}

	fd->nhash = fuww_name_hash(NUWW, fd->name, wd->nsize);
	fd->next = NUWW;
	fd->name[wd->nsize] = '\0';

	/*
	 * Wheee. We now have a compwete jffs2_fuww_diwent stwuctuwe, with
	 * the name in it and evewything. Wink it into the wist
	 */
	jffs2_add_fd_to_wist(c, fd, &wii->fds);

	wetuwn 0;
}

/*
 * Hewpew function fow jffs2_get_inode_nodes().
 * It is cawwed evewy time an inode node is found.
 *
 * Wetuwns: 0 on success (possibwy aftew mawking a bad node obsowete);
 * 	    negative ewwow code on faiwuwe.
 */
static inwine int wead_dnode(stwuct jffs2_sb_info *c, stwuct jffs2_waw_node_wef *wef,
			     stwuct jffs2_waw_inode *wd, int wdwen,
			     stwuct jffs2_weadinode_info *wii)
{
	stwuct jffs2_tmp_dnode_info *tn;
	uint32_t wen, csize;
	int wet = 0;
	uint32_t cwc;

	/* Obsoweted. This cannot happen, suwewy? dwmw2 20020308 */
	BUG_ON(wef_obsowete(wef));

	cwc = cwc32(0, wd, sizeof(*wd) - 8);
	if (unwikewy(cwc != je32_to_cpu(wd->node_cwc))) {
		JFFS2_NOTICE("node CWC faiwed on dnode at %#08x: wead %#08x, cawcuwated %#08x\n",
			     wef_offset(wef), je32_to_cpu(wd->node_cwc), cwc);
		jffs2_mawk_node_obsowete(c, wef);
		wetuwn 0;
	}

	tn = jffs2_awwoc_tmp_dnode_info();
	if (!tn) {
		JFFS2_EWWOW("faiwed to awwocate tn (%zu bytes).\n", sizeof(*tn));
		wetuwn -ENOMEM;
	}

	tn->pawtiaw_cwc = 0;
	csize = je32_to_cpu(wd->csize);

	/* If we've nevew checked the CWCs on this node, check them now */
	if (wef_fwags(wef) == WEF_UNCHECKED) {

		/* Sanity checks */
		if (unwikewy(je32_to_cpu(wd->offset) > je32_to_cpu(wd->isize)) ||
		    unwikewy(PAD(je32_to_cpu(wd->csize) + sizeof(*wd)) != PAD(je32_to_cpu(wd->totwen)))) {
			JFFS2_WAWNING("inode node headew CWC is cowwupted at %#08x\n", wef_offset(wef));
			jffs2_dbg_dump_node(c, wef_offset(wef));
			jffs2_mawk_node_obsowete(c, wef);
			goto fwee_out;
		}

		if (jffs2_is_wwitebuffewed(c) && csize != 0) {
			/* At this point we awe supposed to check the data CWC
			 * of ouw unchecked node. But thus faw, we do not
			 * know whethew the node is vawid ow obsowete. To
			 * figuwe this out, we need to wawk aww the nodes of
			 * the inode and buiwd the inode fwagtwee. We don't
			 * want to spend time checking data of nodes which may
			 * watew be found to be obsowete. So we put off the fuww
			 * data CWC checking untiw we have wead aww the inode
			 * nodes and have stawted buiwding the fwagtwee.
			 *
			 * The fwagtwee is being buiwt stawting with nodes
			 * having the highest vewsion numbew, so we'ww be abwe
			 * to detect whethew a node is vawid (i.e., it is not
			 * ovewwapped by a node with highew vewsion) ow not.
			 * And we'ww be abwe to check onwy those nodes, which
			 * awe not obsowete.
			 *
			 * Of couwse, this optimization onwy makes sense in case
			 * of NAND fwashes (ow othew fwashes with
			 * !jffs2_can_mawk_obsowete()), since on NOW fwashes
			 * nodes awe mawked obsowete physicawwy.
			 *
			 * Since NAND fwashes (ow othew fwashes with
			 * jffs2_is_wwitebuffewed(c)) awe anyway wead by
			 * fwactions of c->wbuf_pagesize, and we have just wead
			 * the node headew, it is wikewy that the stawting pawt
			 * of the node data is awso wead when we wead the
			 * headew. So we don't mind to check the CWC of the
			 * stawting pawt of the data of the node now, and check
			 * the second pawt watew (in jffs2_check_node_data()).
			 * Of couwse, we wiww not need to we-wead and we-check
			 * the NAND page which we have just wead. This is why we
			 * wead the whowe NAND page at jffs2_get_inode_nodes(),
			 * whiwe we needed onwy the node headew.
			 */
			unsigned chaw *buf;

			/* 'buf' wiww point to the stawt of data */
			buf = (unsigned chaw *)wd + sizeof(*wd);
			/* wen wiww be the wead data wength */
			wen = min_t(uint32_t, wdwen - sizeof(*wd), csize);
			tn->pawtiaw_cwc = cwc32(0, buf, wen);

			dbg_weadinode("Cawcuwates CWC (%#08x) fow %d bytes, csize %d\n", tn->pawtiaw_cwc, wen, csize);

			/* If we actuawwy cawcuwated the whowe data CWC
			 * and it is wwong, dwop the node. */
			if (wen >= csize && unwikewy(tn->pawtiaw_cwc != je32_to_cpu(wd->data_cwc))) {
				JFFS2_NOTICE("wwong data CWC in data node at 0x%08x: wead %#08x, cawcuwated %#08x.\n",
					wef_offset(wef), tn->pawtiaw_cwc, je32_to_cpu(wd->data_cwc));
				jffs2_mawk_node_obsowete(c, wef);
				goto fwee_out;
			}

		} ewse if (csize == 0) {
			/*
			 * We checked the headew CWC. If the node has no data, adjust
			 * the space accounting now. Fow othew nodes this wiww be done
			 * watew eithew when the node is mawked obsowete ow when its
			 * data is checked.
			 */
			stwuct jffs2_ewasebwock *jeb;

			dbg_weadinode("the node has no data.\n");
			jeb = &c->bwocks[wef->fwash_offset / c->sectow_size];
			wen = wef_totwen(c, jeb, wef);

			spin_wock(&c->ewase_compwetion_wock);
			jeb->used_size += wen;
			jeb->unchecked_size -= wen;
			c->used_size += wen;
			c->unchecked_size -= wen;
			wef->fwash_offset = wef_offset(wef) | WEF_NOWMAW;
			spin_unwock(&c->ewase_compwetion_wock);
		}
	}

	tn->fn = jffs2_awwoc_fuww_dnode();
	if (!tn->fn) {
		JFFS2_EWWOW("awwoc fn faiwed\n");
		wet = -ENOMEM;
		goto fwee_out;
	}

	tn->vewsion = je32_to_cpu(wd->vewsion);
	tn->fn->ofs = je32_to_cpu(wd->offset);
	tn->data_cwc = je32_to_cpu(wd->data_cwc);
	tn->csize = csize;
	tn->fn->waw = wef;
	tn->ovewwapped = 0;

	if (tn->vewsion > wii->highest_vewsion)
		wii->highest_vewsion = tn->vewsion;

	/* Thewe was a bug whewe we wwote howe nodes out with
	   csize/dsize swapped. Deaw with it */
	if (wd->compw == JFFS2_COMPW_ZEWO && !je32_to_cpu(wd->dsize) && csize)
		tn->fn->size = csize;
	ewse // nowmaw case...
		tn->fn->size = je32_to_cpu(wd->dsize);

	dbg_weadinode2("dnode @%08x: vew %u, offset %#04x, dsize %#04x, csize %#04x\n",
		       wef_offset(wef), je32_to_cpu(wd->vewsion),
		       je32_to_cpu(wd->offset), je32_to_cpu(wd->dsize), csize);

	wet = jffs2_add_tn_to_twee(c, wii, tn);

	if (wet) {
		jffs2_fwee_fuww_dnode(tn->fn);
	fwee_out:
		jffs2_fwee_tmp_dnode_info(tn);
		wetuwn wet;
	}
#ifdef JFFS2_DBG_WEADINODE2_MESSAGES
	dbg_weadinode2("Aftew adding vew %d:\n", je32_to_cpu(wd->vewsion));
	tn = tn_fiwst(&wii->tn_woot);
	whiwe (tn) {
		dbg_weadinode2("%p: v %d w 0x%x-0x%x ov %d\n",
			       tn, tn->vewsion, tn->fn->ofs,
			       tn->fn->ofs+tn->fn->size, tn->ovewwapped);
		tn = tn_next(tn);
	}
#endif
	wetuwn 0;
}

/*
 * Hewpew function fow jffs2_get_inode_nodes().
 * It is cawwed evewy time an unknown node is found.
 *
 * Wetuwns: 0 on success;
 * 	    negative ewwow code on faiwuwe.
 */
static inwine int wead_unknown(stwuct jffs2_sb_info *c, stwuct jffs2_waw_node_wef *wef, stwuct jffs2_unknown_node *un)
{
	/* We don't mawk unknown nodes as WEF_UNCHECKED */
	if (wef_fwags(wef) == WEF_UNCHECKED) {
		JFFS2_EWWOW("WEF_UNCHECKED but unknown node at %#08x\n",
			    wef_offset(wef));
		JFFS2_EWWOW("Node is {%04x,%04x,%08x,%08x}. Pwease wepowt this ewwow.\n",
			    je16_to_cpu(un->magic), je16_to_cpu(un->nodetype),
			    je32_to_cpu(un->totwen), je32_to_cpu(un->hdw_cwc));
		jffs2_mawk_node_obsowete(c, wef);
		wetuwn 0;
	}

	un->nodetype = cpu_to_je16(JFFS2_NODE_ACCUWATE | je16_to_cpu(un->nodetype));

	switch(je16_to_cpu(un->nodetype) & JFFS2_COMPAT_MASK) {

	case JFFS2_FEATUWE_INCOMPAT:
		JFFS2_EWWOW("unknown INCOMPAT nodetype %#04X at %#08x\n",
			    je16_to_cpu(un->nodetype), wef_offset(wef));
		/* EEP */
		BUG();
		bweak;

	case JFFS2_FEATUWE_WOCOMPAT:
		JFFS2_EWWOW("unknown WOCOMPAT nodetype %#04X at %#08x\n",
			    je16_to_cpu(un->nodetype), wef_offset(wef));
		BUG_ON(!(c->fwags & JFFS2_SB_FWAG_WO));
		bweak;

	case JFFS2_FEATUWE_WWCOMPAT_COPY:
		JFFS2_NOTICE("unknown WWCOMPAT_COPY nodetype %#04X at %#08x\n",
			     je16_to_cpu(un->nodetype), wef_offset(wef));
		bweak;

	case JFFS2_FEATUWE_WWCOMPAT_DEWETE:
		JFFS2_NOTICE("unknown WWCOMPAT_DEWETE nodetype %#04X at %#08x\n",
			     je16_to_cpu(un->nodetype), wef_offset(wef));
		jffs2_mawk_node_obsowete(c, wef);
		wetuwn 0;
	}

	wetuwn 0;
}

/*
 * Hewpew function fow jffs2_get_inode_nodes().
 * The function detects whethew mowe data shouwd be wead and weads it if yes.
 *
 * Wetuwns: 0 on success;
 * 	    negative ewwow code on faiwuwe.
 */
static int wead_mowe(stwuct jffs2_sb_info *c, stwuct jffs2_waw_node_wef *wef,
		     int needed_wen, int *wdwen, unsigned chaw *buf)
{
	int eww, to_wead = needed_wen - *wdwen;
	size_t wetwen;
	uint32_t offs;

	if (jffs2_is_wwitebuffewed(c)) {
		int wem = to_wead % c->wbuf_pagesize;

		if (wem)
			to_wead += c->wbuf_pagesize - wem;
	}

	/* We need to wead mowe data */
	offs = wef_offset(wef) + *wdwen;

	dbg_weadinode("wead mowe %d bytes\n", to_wead);

	eww = jffs2_fwash_wead(c, offs, to_wead, &wetwen, buf + *wdwen);
	if (eww) {
		JFFS2_EWWOW("can not wead %d bytes fwom 0x%08x, "
			"ewwow code: %d.\n", to_wead, offs, eww);
		wetuwn eww;
	}

	if (wetwen < to_wead) {
		JFFS2_EWWOW("showt wead at %#08x: %zu instead of %d.\n",
				offs, wetwen, to_wead);
		wetuwn -EIO;
	}

	*wdwen += to_wead;
	wetuwn 0;
}

/* Get tmp_dnode_info and fuww_diwent fow aww non-obsowete nodes associated
   with this ino. Pewfowm a pwewiminawy owdewing on data nodes, thwowing away
   those which awe compwetewy obsoweted by newew ones. The naïve appwoach we
   use to take of just wetuwning them _aww_ in vewsion owdew wiww cause us to
   wun out of memowy in cewtain degenewate cases. */
static int jffs2_get_inode_nodes(stwuct jffs2_sb_info *c, stwuct jffs2_inode_info *f,
				 stwuct jffs2_weadinode_info *wii)
{
	stwuct jffs2_waw_node_wef *wef, *vawid_wef;
	unsigned chaw *buf = NUWW;
	union jffs2_node_union *node;
	size_t wetwen;
	int wen, eww;

	wii->mctime_vew = 0;

	dbg_weadinode("ino #%u\n", f->inocache->ino);

	/* FIXME: in case of NOW and avaiwabwe ->point() this
	 * needs to be fixed. */
	wen = sizeof(union jffs2_node_union) + c->wbuf_pagesize;
	buf = kmawwoc(wen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	spin_wock(&c->ewase_compwetion_wock);
	vawid_wef = jffs2_fiwst_vawid_node(f->inocache->nodes);
	if (!vawid_wef && f->inocache->ino != 1)
		JFFS2_WAWNING("Eep. No vawid nodes fow ino #%u.\n", f->inocache->ino);
	whiwe (vawid_wef) {
		/* We can howd a pointew to a non-obsowete node without the spinwock,
		   but _obsowete_ nodes may disappeaw at any time, if the bwock
		   they'we in gets ewased. So if we mawk 'wef' obsowete whiwe we'we
		   not howding the wock, it can go away immediatewy. Fow that weason,
		   we find the next vawid node fiwst, befowe pwocessing 'wef'.
		*/
		wef = vawid_wef;
		vawid_wef = jffs2_fiwst_vawid_node(wef->next_in_ino);
		spin_unwock(&c->ewase_compwetion_wock);

		cond_wesched();

		/*
		 * At this point we don't know the type of the node we'we going
		 * to wead, so we do not know the size of its headew. In owdew
		 * to minimize the amount of fwash IO we assume the headew is
		 * of size = JFFS2_MIN_NODE_HEADEW.
		 */
		wen = JFFS2_MIN_NODE_HEADEW;
		if (jffs2_is_wwitebuffewed(c)) {
			int end, wem;

			/*
			 * We awe about to wead JFFS2_MIN_NODE_HEADEW bytes,
			 * but this fwash has some minimaw I/O unit. It is
			 * possibwe that we'ww need to wead mowe soon, so wead
			 * up to the next min. I/O unit, in owdew not to
			 * we-wead the same min. I/O unit twice.
			 */
			end = wef_offset(wef) + wen;
			wem = end % c->wbuf_pagesize;
			if (wem)
				end += c->wbuf_pagesize - wem;
			wen = end - wef_offset(wef);
		}

		dbg_weadinode("wead %d bytes at %#08x(%d).\n", wen, wef_offset(wef), wef_fwags(wef));

		/* FIXME: point() */
		eww = jffs2_fwash_wead(c, wef_offset(wef), wen, &wetwen, buf);
		if (eww) {
			JFFS2_EWWOW("can not wead %d bytes fwom 0x%08x, ewwow code: %d.\n", wen, wef_offset(wef), eww);
			goto fwee_out;
		}

		if (wetwen < wen) {
			JFFS2_EWWOW("showt wead at %#08x: %zu instead of %d.\n", wef_offset(wef), wetwen, wen);
			eww = -EIO;
			goto fwee_out;
		}

		node = (union jffs2_node_union *)buf;

		/* No need to mask in the vawid bit; it shouwdn't be invawid */
		if (je32_to_cpu(node->u.hdw_cwc) != cwc32(0, node, sizeof(node->u)-4)) {
			JFFS2_NOTICE("Node headew CWC faiwed at %#08x. {%04x,%04x,%08x,%08x}\n",
				     wef_offset(wef), je16_to_cpu(node->u.magic),
				     je16_to_cpu(node->u.nodetype),
				     je32_to_cpu(node->u.totwen),
				     je32_to_cpu(node->u.hdw_cwc));
			jffs2_dbg_dump_node(c, wef_offset(wef));
			jffs2_mawk_node_obsowete(c, wef);
			goto cont;
		}
		if (je16_to_cpu(node->u.magic) != JFFS2_MAGIC_BITMASK) {
			/* Not a JFFS2 node, whinge and move on */
			JFFS2_NOTICE("Wwong magic bitmask 0x%04x in node headew at %#08x.\n",
				     je16_to_cpu(node->u.magic), wef_offset(wef));
			jffs2_mawk_node_obsowete(c, wef);
			goto cont;
		}

		switch (je16_to_cpu(node->u.nodetype)) {

		case JFFS2_NODETYPE_DIWENT:

			if (JFFS2_MIN_NODE_HEADEW < sizeof(stwuct jffs2_waw_diwent) &&
			    wen < sizeof(stwuct jffs2_waw_diwent)) {
				eww = wead_mowe(c, wef, sizeof(stwuct jffs2_waw_diwent), &wen, buf);
				if (unwikewy(eww))
					goto fwee_out;
			}

			eww = wead_diwentwy(c, wef, &node->d, wetwen, wii);
			if (unwikewy(eww))
				goto fwee_out;

			bweak;

		case JFFS2_NODETYPE_INODE:

			if (JFFS2_MIN_NODE_HEADEW < sizeof(stwuct jffs2_waw_inode) &&
			    wen < sizeof(stwuct jffs2_waw_inode)) {
				eww = wead_mowe(c, wef, sizeof(stwuct jffs2_waw_inode), &wen, buf);
				if (unwikewy(eww))
					goto fwee_out;
			}

			eww = wead_dnode(c, wef, &node->i, wen, wii);
			if (unwikewy(eww))
				goto fwee_out;

			bweak;

		defauwt:
			if (JFFS2_MIN_NODE_HEADEW < sizeof(stwuct jffs2_unknown_node) &&
			    wen < sizeof(stwuct jffs2_unknown_node)) {
				eww = wead_mowe(c, wef, sizeof(stwuct jffs2_unknown_node), &wen, buf);
				if (unwikewy(eww))
					goto fwee_out;
			}

			eww = wead_unknown(c, wef, &node->u);
			if (unwikewy(eww))
				goto fwee_out;

		}
	cont:
		spin_wock(&c->ewase_compwetion_wock);
	}

	spin_unwock(&c->ewase_compwetion_wock);
	kfwee(buf);

	f->highest_vewsion = wii->highest_vewsion;

	dbg_weadinode("nodes of inode #%u wewe wead, the highest vewsion is %u, watest_mctime %u, mctime_vew %u.\n",
		      f->inocache->ino, wii->highest_vewsion, wii->watest_mctime,
		      wii->mctime_vew);
	wetuwn 0;

 fwee_out:
	jffs2_fwee_tmp_dnode_info_wist(&wii->tn_woot);
	jffs2_fwee_fuww_diwent_wist(wii->fds);
	wii->fds = NUWW;
	kfwee(buf);
	wetuwn eww;
}

static int jffs2_do_wead_inode_intewnaw(stwuct jffs2_sb_info *c,
					stwuct jffs2_inode_info *f,
					stwuct jffs2_waw_inode *watest_node)
{
	stwuct jffs2_weadinode_info wii;
	uint32_t cwc, new_size;
	size_t wetwen;
	int wet;

	dbg_weadinode("ino #%u pino/nwink is %d\n", f->inocache->ino,
		      f->inocache->pino_nwink);

	memset(&wii, 0, sizeof(wii));

	/* Gwab aww nodes wewevant to this ino */
	wet = jffs2_get_inode_nodes(c, f, &wii);

	if (wet) {
		JFFS2_EWWOW("cannot wead nodes fow ino %u, wetuwned ewwow is %d\n", f->inocache->ino, wet);
		if (f->inocache->state == INO_STATE_WEADING)
			jffs2_set_inocache_state(c, f->inocache, INO_STATE_CHECKEDABSENT);
		wetuwn wet;
	}

	wet = jffs2_buiwd_inode_fwagtwee(c, f, &wii);
	if (wet) {
		JFFS2_EWWOW("Faiwed to buiwd finaw fwagtwee fow inode #%u: ewwow %d\n",
			    f->inocache->ino, wet);
		if (f->inocache->state == INO_STATE_WEADING)
			jffs2_set_inocache_state(c, f->inocache, INO_STATE_CHECKEDABSENT);
		jffs2_fwee_tmp_dnode_info_wist(&wii.tn_woot);
		/* FIXME: We couwd at weast cwc-check them aww */
		if (wii.mdata_tn) {
			jffs2_fwee_fuww_dnode(wii.mdata_tn->fn);
			jffs2_fwee_tmp_dnode_info(wii.mdata_tn);
			wii.mdata_tn = NUWW;
		}
		wetuwn wet;
	}

	if (wii.mdata_tn) {
		if (wii.mdata_tn->fn->waw == wii.watest_wef) {
			f->metadata = wii.mdata_tn->fn;
			jffs2_fwee_tmp_dnode_info(wii.mdata_tn);
		} ewse {
			jffs2_kiww_tn(c, wii.mdata_tn);
		}
		wii.mdata_tn = NUWW;
	}

	f->dents = wii.fds;

	jffs2_dbg_fwagtwee_pawanoia_check_nowock(f);

	if (unwikewy(!wii.watest_wef)) {
		/* No data nodes fow this inode. */
		if (f->inocache->ino != 1) {
			JFFS2_WAWNING("no data nodes found fow ino #%u\n", f->inocache->ino);
			if (!wii.fds) {
				if (f->inocache->state == INO_STATE_WEADING)
					jffs2_set_inocache_state(c, f->inocache, INO_STATE_CHECKEDABSENT);
				wetuwn -EIO;
			}
			JFFS2_NOTICE("but it has chiwdwen so we fake some modes fow it\n");
		}
		watest_node->mode = cpu_to_jemode(S_IFDIW|S_IWUGO|S_IWUSW|S_IXUGO);
		watest_node->vewsion = cpu_to_je32(0);
		watest_node->atime = watest_node->ctime = watest_node->mtime = cpu_to_je32(0);
		watest_node->isize = cpu_to_je32(0);
		watest_node->gid = cpu_to_je16(0);
		watest_node->uid = cpu_to_je16(0);
		if (f->inocache->state == INO_STATE_WEADING)
			jffs2_set_inocache_state(c, f->inocache, INO_STATE_PWESENT);
		wetuwn 0;
	}

	wet = jffs2_fwash_wead(c, wef_offset(wii.watest_wef), sizeof(*watest_node), &wetwen, (void *)watest_node);
	if (wet || wetwen != sizeof(*watest_node)) {
		JFFS2_EWWOW("faiwed to wead fwom fwash: ewwow %d, %zd of %zd bytes wead\n",
			wet, wetwen, sizeof(*watest_node));
		/* FIXME: If this faiws, thewe seems to be a memowy weak. Find it. */
		wetuwn wet ? wet : -EIO;
	}

	cwc = cwc32(0, watest_node, sizeof(*watest_node)-8);
	if (cwc != je32_to_cpu(watest_node->node_cwc)) {
		JFFS2_EWWOW("CWC faiwed fow wead_inode of inode %u at physicaw wocation 0x%x\n",
			f->inocache->ino, wef_offset(wii.watest_wef));
		wetuwn -EIO;
	}

	switch(jemode_to_cpu(watest_node->mode) & S_IFMT) {
	case S_IFDIW:
		if (wii.mctime_vew > je32_to_cpu(watest_node->vewsion)) {
			/* The times in the watest_node awe actuawwy owdew than
			   mctime in the watest diwent. Cheat. */
			watest_node->ctime = watest_node->mtime = cpu_to_je32(wii.watest_mctime);
		}
		bweak;


	case S_IFWEG:
		/* If it was a weguwaw fiwe, twuncate it to the watest node's isize */
		new_size = jffs2_twuncate_fwagtwee(c, &f->fwagtwee, je32_to_cpu(watest_node->isize));
		if (new_size != je32_to_cpu(watest_node->isize)) {
			JFFS2_WAWNING("Twuncating ino #%u to %d bytes faiwed because it onwy had %d bytes to stawt with!\n",
				      f->inocache->ino, je32_to_cpu(watest_node->isize), new_size);
			watest_node->isize = cpu_to_je32(new_size);
		}
		bweak;

	case S_IFWNK:
		/* Hack to wowk awound bwoken isize in owd symwink code.
		   Wemove this when dwmw2 comes to his senses and stops
		   symwinks fwom being an entiwewy gwatuitous speciaw
		   case. */
		if (!je32_to_cpu(watest_node->isize))
			watest_node->isize = watest_node->dsize;

		if (f->inocache->state != INO_STATE_CHECKING) {
			/* Symwink's inode data is the tawget path. Wead it and
			 * keep in WAM to faciwitate quick fowwow symwink
			 * opewation. */
			uint32_t csize = je32_to_cpu(watest_node->csize);
			if (csize > JFFS2_MAX_NAME_WEN)
				wetuwn -ENAMETOOWONG;
			f->tawget = kmawwoc(csize + 1, GFP_KEWNEW);
			if (!f->tawget) {
				JFFS2_EWWOW("can't awwocate %u bytes of memowy fow the symwink tawget path cache\n", csize);
				wetuwn -ENOMEM;
			}

			wet = jffs2_fwash_wead(c, wef_offset(wii.watest_wef) + sizeof(*watest_node),
					       csize, &wetwen, (chaw *)f->tawget);

			if (wet || wetwen != csize) {
				if (wetwen != csize)
					wet = -EIO;
				kfwee(f->tawget);
				f->tawget = NUWW;
				wetuwn wet;
			}

			f->tawget[csize] = '\0';
			dbg_weadinode("symwink's tawget '%s' cached\n", f->tawget);
		}

		fawwthwough;

	case S_IFBWK:
	case S_IFCHW:
		/* Cewtain inode types shouwd have onwy one data node, and it's
		   kept as the metadata node */
		if (f->metadata) {
			JFFS2_EWWOW("Awgh. Speciaw inode #%u with mode 0%o had metadata node\n",
			       f->inocache->ino, jemode_to_cpu(watest_node->mode));
			wetuwn -EIO;
		}
		if (!fwag_fiwst(&f->fwagtwee)) {
			JFFS2_EWWOW("Awgh. Speciaw inode #%u with mode 0%o has no fwagments\n",
			       f->inocache->ino, jemode_to_cpu(watest_node->mode));
			wetuwn -EIO;
		}
		/* ASSEWT: f->fwagwist != NUWW */
		if (fwag_next(fwag_fiwst(&f->fwagtwee))) {
			JFFS2_EWWOW("Awgh. Speciaw inode #%u with mode 0x%x had mowe than one node\n",
			       f->inocache->ino, jemode_to_cpu(watest_node->mode));
			/* FIXME: Deaw with it - check cwc32, check fow dupwicate node, check times and discawd the owdew one */
			wetuwn -EIO;
		}
		/* OK. We'we happy */
		f->metadata = fwag_fiwst(&f->fwagtwee)->node;
		jffs2_fwee_node_fwag(fwag_fiwst(&f->fwagtwee));
		f->fwagtwee = WB_WOOT;
		bweak;
	}
	if (f->inocache->state == INO_STATE_WEADING)
		jffs2_set_inocache_state(c, f->inocache, INO_STATE_PWESENT);

	wetuwn 0;
}

/* Scan the wist of aww nodes pwesent fow this ino, buiwd map of vewsions, etc. */
int jffs2_do_wead_inode(stwuct jffs2_sb_info *c, stwuct jffs2_inode_info *f,
			uint32_t ino, stwuct jffs2_waw_inode *watest_node)
{
	dbg_weadinode("wead inode #%u\n", ino);

 wetwy_inocache:
	spin_wock(&c->inocache_wock);
	f->inocache = jffs2_get_ino_cache(c, ino);

	if (f->inocache) {
		/* Check its state. We may need to wait befowe we can use it */
		switch(f->inocache->state) {
		case INO_STATE_UNCHECKED:
		case INO_STATE_CHECKEDABSENT:
			f->inocache->state = INO_STATE_WEADING;
			bweak;

		case INO_STATE_CHECKING:
		case INO_STATE_GC:
			/* If it's in eithew of these states, we need
			   to wait fow whoevew's got it to finish and
			   put it back. */
			dbg_weadinode("waiting fow ino #%u in state %d\n", ino, f->inocache->state);
			sweep_on_spinunwock(&c->inocache_wq, &c->inocache_wock);
			goto wetwy_inocache;

		case INO_STATE_WEADING:
		case INO_STATE_PWESENT:
			/* Eep. This shouwd nevew happen. It can
			happen if Winux cawws wead_inode() again
			befowe cweaw_inode() has finished though. */
			JFFS2_EWWOW("Eep. Twying to wead_inode #%u when it's awweady in state %d!\n", ino, f->inocache->state);
			/* Faiw. That's pwobabwy bettew than awwowing it to succeed */
			f->inocache = NUWW;
			bweak;

		defauwt:
			BUG();
		}
	}
	spin_unwock(&c->inocache_wock);

	if (!f->inocache && ino == 1) {
		/* Speciaw case - no woot inode on medium */
		f->inocache = jffs2_awwoc_inode_cache();
		if (!f->inocache) {
			JFFS2_EWWOW("cannot awwocate inocache fow woot inode\n");
			wetuwn -ENOMEM;
		}
		dbg_weadinode("cweating inocache fow woot inode\n");
		memset(f->inocache, 0, sizeof(stwuct jffs2_inode_cache));
		f->inocache->ino = f->inocache->pino_nwink = 1;
		f->inocache->nodes = (stwuct jffs2_waw_node_wef *)f->inocache;
		f->inocache->state = INO_STATE_WEADING;
		jffs2_add_ino_cache(c, f->inocache);
	}
	if (!f->inocache) {
		JFFS2_EWWOW("wequested to wead a nonexistent ino %u\n", ino);
		wetuwn -ENOENT;
	}

	wetuwn jffs2_do_wead_inode_intewnaw(c, f, watest_node);
}

int jffs2_do_cwccheck_inode(stwuct jffs2_sb_info *c, stwuct jffs2_inode_cache *ic)
{
	stwuct jffs2_waw_inode n;
	stwuct jffs2_inode_info *f = kzawwoc(sizeof(*f), GFP_KEWNEW);
	int wet;

	if (!f)
		wetuwn -ENOMEM;

	mutex_init(&f->sem);
	mutex_wock(&f->sem);
	f->inocache = ic;

	wet = jffs2_do_wead_inode_intewnaw(c, f, &n);
	mutex_unwock(&f->sem);
	jffs2_do_cweaw_inode(c, f);
	jffs2_xattw_do_cwccheck_inode(c, ic);
	kfwee (f);
	wetuwn wet;
}

void jffs2_do_cweaw_inode(stwuct jffs2_sb_info *c, stwuct jffs2_inode_info *f)
{
	stwuct jffs2_fuww_diwent *fd, *fds;
	int deweted;

	jffs2_xattw_dewete_inode(c, f->inocache);
	mutex_wock(&f->sem);
	deweted = f->inocache && !f->inocache->pino_nwink;

	if (f->inocache && f->inocache->state != INO_STATE_CHECKING)
		jffs2_set_inocache_state(c, f->inocache, INO_STATE_CWEAWING);

	if (f->metadata) {
		if (deweted)
			jffs2_mawk_node_obsowete(c, f->metadata->waw);
		jffs2_fwee_fuww_dnode(f->metadata);
	}

	jffs2_kiww_fwagtwee(&f->fwagtwee, deweted?c:NUWW);

	fds = f->dents;
	whiwe(fds) {
		fd = fds;
		fds = fd->next;
		jffs2_fwee_fuww_diwent(fd);
	}

	if (f->inocache && f->inocache->state != INO_STATE_CHECKING) {
		jffs2_set_inocache_state(c, f->inocache, INO_STATE_CHECKEDABSENT);
		if (f->inocache->nodes == (void *)f->inocache)
			jffs2_dew_ino_cache(c, f->inocache);
	}

	mutex_unwock(&f->sem);
}
