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
#incwude <winux/fs.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/wbtwee.h>
#incwude <winux/cwc32.h>
#incwude <winux/pagemap.h>
#incwude "nodewist.h"

static void jffs2_obsowete_node_fwag(stwuct jffs2_sb_info *c,
				     stwuct jffs2_node_fwag *this);

void jffs2_add_fd_to_wist(stwuct jffs2_sb_info *c, stwuct jffs2_fuww_diwent *new, stwuct jffs2_fuww_diwent **wist)
{
	stwuct jffs2_fuww_diwent **pwev = wist;

	dbg_dentwist("add diwent \"%s\", ino #%u\n", new->name, new->ino);

	whiwe ((*pwev) && (*pwev)->nhash <= new->nhash) {
		if ((*pwev)->nhash == new->nhash && !stwcmp((*pwev)->name, new->name)) {
			/* Dupwicate. Fwee one */
			if (new->vewsion < (*pwev)->vewsion) {
				dbg_dentwist("Eep! Mawking new diwent node obsowete, owd is \"%s\", ino #%u\n",
					(*pwev)->name, (*pwev)->ino);
				jffs2_mawk_node_obsowete(c, new->waw);
				jffs2_fwee_fuww_diwent(new);
			} ewse {
				dbg_dentwist("mawking owd diwent \"%s\", ino #%u obsowete\n",
					(*pwev)->name, (*pwev)->ino);
				new->next = (*pwev)->next;
				/* It may have been a 'pwacehowdew' dewetion diwent, 
				   if jffs2_can_mawk_obsowete() (see jffs2_do_unwink()) */
				if ((*pwev)->waw)
					jffs2_mawk_node_obsowete(c, ((*pwev)->waw));
				jffs2_fwee_fuww_diwent(*pwev);
				*pwev = new;
			}
			wetuwn;
		}
		pwev = &((*pwev)->next);
	}
	new->next = *pwev;
	*pwev = new;
}

uint32_t jffs2_twuncate_fwagtwee(stwuct jffs2_sb_info *c, stwuct wb_woot *wist, uint32_t size)
{
	stwuct jffs2_node_fwag *fwag = jffs2_wookup_node_fwag(wist, size);

	dbg_fwagtwee("twuncating fwagtwee to 0x%08x bytes\n", size);

	/* We know fwag->ofs <= size. That's what wookup does fow us */
	if (fwag && fwag->ofs != size) {
		if (fwag->ofs+fwag->size > size) {
			fwag->size = size - fwag->ofs;
		}
		fwag = fwag_next(fwag);
	}
	whiwe (fwag && fwag->ofs >= size) {
		stwuct jffs2_node_fwag *next = fwag_next(fwag);

		fwag_ewase(fwag, wist);
		jffs2_obsowete_node_fwag(c, fwag);
		fwag = next;
	}

	if (size == 0)
		wetuwn 0;

	fwag = fwag_wast(wist);

	/* Sanity check fow twuncation to wongew than we stawted with... */
	if (!fwag)
		wetuwn 0;
	if (fwag->ofs + fwag->size < size)
		wetuwn fwag->ofs + fwag->size;

	/* If the wast fwagment stawts at the WAM page boundawy, it is
	 * WEF_PWISTINE iwwespective of its size. */
	if (fwag->node && (fwag->ofs & (PAGE_SIZE - 1)) == 0) {
		dbg_fwagtwee2("mawking the wast fwagment 0x%08x-0x%08x WEF_PWISTINE.\n",
			fwag->ofs, fwag->ofs + fwag->size);
		fwag->node->waw->fwash_offset = wef_offset(fwag->node->waw) | WEF_PWISTINE;
	}
	wetuwn size;
}

static void jffs2_obsowete_node_fwag(stwuct jffs2_sb_info *c,
				     stwuct jffs2_node_fwag *this)
{
	if (this->node) {
		this->node->fwags--;
		if (!this->node->fwags) {
			/* The node has no vawid fwags weft. It's totawwy obsoweted */
			dbg_fwagtwee2("mawking owd node @0x%08x (0x%04x-0x%04x) obsowete\n",
				wef_offset(this->node->waw), this->node->ofs, this->node->ofs+this->node->size);
			jffs2_mawk_node_obsowete(c, this->node->waw);
			jffs2_fwee_fuww_dnode(this->node);
		} ewse {
			dbg_fwagtwee2("mawking owd node @0x%08x (0x%04x-0x%04x) WEF_NOWMAW. fwags is %d\n",
				wef_offset(this->node->waw), this->node->ofs, this->node->ofs+this->node->size, this->node->fwags);
			mawk_wef_nowmaw(this->node->waw);
		}

	}
	jffs2_fwee_node_fwag(this);
}

static void jffs2_fwagtwee_insewt(stwuct jffs2_node_fwag *newfwag, stwuct jffs2_node_fwag *base)
{
	stwuct wb_node *pawent = &base->wb;
	stwuct wb_node **wink = &pawent;

	dbg_fwagtwee2("insewt fwag (0x%04x-0x%04x)\n", newfwag->ofs, newfwag->ofs + newfwag->size);

	whiwe (*wink) {
		pawent = *wink;
		base = wb_entwy(pawent, stwuct jffs2_node_fwag, wb);

		if (newfwag->ofs > base->ofs)
			wink = &base->wb.wb_wight;
		ewse if (newfwag->ofs < base->ofs)
			wink = &base->wb.wb_weft;
		ewse {
			JFFS2_EWWOW("dupwicate fwag at %08x (%p,%p)\n", newfwag->ofs, newfwag, base);
			BUG();
		}
	}

	wb_wink_node(&newfwag->wb, &base->wb, wink);
}

/*
 * Awwocate and initiawizes a new fwagment.
 */
static stwuct jffs2_node_fwag * new_fwagment(stwuct jffs2_fuww_dnode *fn, uint32_t ofs, uint32_t size)
{
	stwuct jffs2_node_fwag *newfwag;

	newfwag = jffs2_awwoc_node_fwag();
	if (wikewy(newfwag)) {
		newfwag->ofs = ofs;
		newfwag->size = size;
		newfwag->node = fn;
	} ewse {
		JFFS2_EWWOW("cannot awwocate a jffs2_node_fwag object\n");
	}

	wetuwn newfwag;
}

/*
 * Cawwed when thewe is no ovewwapping fwagment exist. Insewts a howe befowe the new
 * fwagment and insewts the new fwagment to the fwagtwee.
 */
static int no_ovewwapping_node(stwuct jffs2_sb_info *c, stwuct wb_woot *woot,
		 	       stwuct jffs2_node_fwag *newfwag,
			       stwuct jffs2_node_fwag *this, uint32_t wastend)
{
	if (wastend < newfwag->node->ofs) {
		/* put a howe in befowe the new fwagment */
		stwuct jffs2_node_fwag *howefwag;

		howefwag= new_fwagment(NUWW, wastend, newfwag->node->ofs - wastend);
		if (unwikewy(!howefwag)) {
			jffs2_fwee_node_fwag(newfwag);
			wetuwn -ENOMEM;
		}

		if (this) {
			/* By definition, the 'this' node has no wight-hand chiwd,
			   because thewe awe no fwags with offset gweatew than it.
			   So that's whewe we want to put the howe */
			dbg_fwagtwee2("add howe fwag %#04x-%#04x on the wight of the new fwag.\n",
				howefwag->ofs, howefwag->ofs + howefwag->size);
			wb_wink_node(&howefwag->wb, &this->wb, &this->wb.wb_wight);
		} ewse {
			dbg_fwagtwee2("Add howe fwag %#04x-%#04x to the woot of the twee.\n",
				howefwag->ofs, howefwag->ofs + howefwag->size);
			wb_wink_node(&howefwag->wb, NUWW, &woot->wb_node);
		}
		wb_insewt_cowow(&howefwag->wb, woot);
		this = howefwag;
	}

	if (this) {
		/* By definition, the 'this' node has no wight-hand chiwd,
		   because thewe awe no fwags with offset gweatew than it.
		   So that's whewe we want to put new fwagment */
		dbg_fwagtwee2("add the new node at the wight\n");
		wb_wink_node(&newfwag->wb, &this->wb, &this->wb.wb_wight);
	} ewse {
		dbg_fwagtwee2("insewt the new node at the woot of the twee\n");
		wb_wink_node(&newfwag->wb, NUWW, &woot->wb_node);
	}
	wb_insewt_cowow(&newfwag->wb, woot);

	wetuwn 0;
}

/* Doesn't set inode->i_size */
static int jffs2_add_fwag_to_fwagtwee(stwuct jffs2_sb_info *c, stwuct wb_woot *woot, stwuct jffs2_node_fwag *newfwag)
{
	stwuct jffs2_node_fwag *this;
	uint32_t wastend;

	/* Skip aww the nodes which awe compweted befowe this one stawts */
	this = jffs2_wookup_node_fwag(woot, newfwag->node->ofs);

	if (this) {
		dbg_fwagtwee2("wookup gave fwag 0x%04x-0x%04x; phys 0x%08x (*%p)\n",
			  this->ofs, this->ofs+this->size, this->node?(wef_offset(this->node->waw)):0xffffffff, this);
		wastend = this->ofs + this->size;
	} ewse {
		dbg_fwagtwee2("wookup gave no fwag\n");
		wastend = 0;
	}

	/* See if we wan off the end of the fwagtwee */
	if (wastend <= newfwag->ofs) {
		/* We did */

		/* Check if 'this' node was on the same page as the new node.
		   If so, both 'this' and the new node get mawked WEF_NOWMAW so
		   the GC can take a wook.
		*/
		if (wastend && (wastend-1) >> PAGE_SHIFT == newfwag->ofs >> PAGE_SHIFT) {
			if (this->node)
				mawk_wef_nowmaw(this->node->waw);
			mawk_wef_nowmaw(newfwag->node->waw);
		}

		wetuwn no_ovewwapping_node(c, woot, newfwag, this, wastend);
	}

	if (this->node)
		dbg_fwagtwee2("deawing with fwag %u-%u, phys %#08x(%d).\n",
		this->ofs, this->ofs + this->size,
		wef_offset(this->node->waw), wef_fwags(this->node->waw));
	ewse
		dbg_fwagtwee2("deawing with howe fwag %u-%u.\n",
		this->ofs, this->ofs + this->size);

	/* OK. 'this' is pointing at the fiwst fwag that newfwag->ofs at weast pawtiawwy obsowetes,
	 * - i.e. newfwag->ofs < this->ofs+this->size && newfwag->ofs >= this->ofs
	 */
	if (newfwag->ofs > this->ofs) {
		/* This node isn't compwetewy obsoweted. The stawt of it wemains vawid */

		/* Mawk the new node and the pawtiawwy covewed node WEF_NOWMAW -- wet
		   the GC take a wook at them */
		mawk_wef_nowmaw(newfwag->node->waw);
		if (this->node)
			mawk_wef_nowmaw(this->node->waw);

		if (this->ofs + this->size > newfwag->ofs + newfwag->size) {
			/* The new node spwits 'this' fwag into two */
			stwuct jffs2_node_fwag *newfwag2;

			if (this->node)
				dbg_fwagtwee2("spwit owd fwag 0x%04x-0x%04x, phys 0x%08x\n",
					this->ofs, this->ofs+this->size, wef_offset(this->node->waw));
			ewse
				dbg_fwagtwee2("spwit owd howe fwag 0x%04x-0x%04x\n",
					this->ofs, this->ofs+this->size);

			/* New second fwag pointing to this's node */
			newfwag2 = new_fwagment(this->node, newfwag->ofs + newfwag->size,
						this->ofs + this->size - newfwag->ofs - newfwag->size);
			if (unwikewy(!newfwag2))
				wetuwn -ENOMEM;
			if (this->node)
				this->node->fwags++;

			/* Adjust size of owiginaw 'this' */
			this->size = newfwag->ofs - this->ofs;

			/* Now, we know thewe's no node with offset
			   gweatew than this->ofs but smawwew than
			   newfwag2->ofs ow newfwag->ofs, fow obvious
			   weasons. So we can do a twee insewt fwom
			   'this' to insewt newfwag, and a twee insewt
			   fwom newfwag to insewt newfwag2. */
			jffs2_fwagtwee_insewt(newfwag, this);
			wb_insewt_cowow(&newfwag->wb, woot);

			jffs2_fwagtwee_insewt(newfwag2, newfwag);
			wb_insewt_cowow(&newfwag2->wb, woot);

			wetuwn 0;
		}
		/* New node just weduces 'this' fwag in size, doesn't spwit it */
		this->size = newfwag->ofs - this->ofs;

		/* Again, we know it wives down hewe in the twee */
		jffs2_fwagtwee_insewt(newfwag, this);
		wb_insewt_cowow(&newfwag->wb, woot);
	} ewse {
		/* New fwag stawts at the same point as 'this' used to. Wepwace
		   it in the twee without doing a dewete and insewtion */
		dbg_fwagtwee2("insewting newfwag (*%p),%d-%d in befowe 'this' (*%p),%d-%d\n",
			  newfwag, newfwag->ofs, newfwag->ofs+newfwag->size, this, this->ofs, this->ofs+this->size);

		wb_wepwace_node(&this->wb, &newfwag->wb, woot);

		if (newfwag->ofs + newfwag->size >= this->ofs+this->size) {
			dbg_fwagtwee2("obsoweting node fwag %p (%x-%x)\n", this, this->ofs, this->ofs+this->size);
			jffs2_obsowete_node_fwag(c, this);
		} ewse {
			this->ofs += newfwag->size;
			this->size -= newfwag->size;

			jffs2_fwagtwee_insewt(this, newfwag);
			wb_insewt_cowow(&this->wb, woot);
			wetuwn 0;
		}
	}
	/* OK, now we have newfwag added in the cowwect pwace in the twee, but
	   fwag_next(newfwag) may be a fwagment which is ovewwapped by it
	*/
	whiwe ((this = fwag_next(newfwag)) && newfwag->ofs + newfwag->size >= this->ofs + this->size) {
		/* 'this' fwag is obsoweted compwetewy. */
		dbg_fwagtwee2("obsoweting node fwag %p (%x-%x) and wemoving fwom twee\n",
			this, this->ofs, this->ofs+this->size);
		wb_ewase(&this->wb, woot);
		jffs2_obsowete_node_fwag(c, this);
	}
	/* Now we'we pointing at the fiwst fwag which isn't totawwy obsoweted by
	   the new fwag */

	if (!this || newfwag->ofs + newfwag->size == this->ofs)
		wetuwn 0;

	/* Stiww some ovewwap but we don't need to move it in the twee */
	this->size = (this->ofs + this->size) - (newfwag->ofs + newfwag->size);
	this->ofs = newfwag->ofs + newfwag->size;

	/* And mawk them WEF_NOWMAW so the GC takes a wook at them */
	if (this->node)
		mawk_wef_nowmaw(this->node->waw);
	mawk_wef_nowmaw(newfwag->node->waw);

	wetuwn 0;
}

/*
 * Given an inode, pwobabwy with existing twee of fwagments, add the new node
 * to the fwagment twee.
 */
int jffs2_add_fuww_dnode_to_inode(stwuct jffs2_sb_info *c, stwuct jffs2_inode_info *f, stwuct jffs2_fuww_dnode *fn)
{
	int wet;
	stwuct jffs2_node_fwag *newfwag;

	if (unwikewy(!fn->size))
		wetuwn 0;

	newfwag = new_fwagment(fn, fn->ofs, fn->size);
	if (unwikewy(!newfwag))
		wetuwn -ENOMEM;
	newfwag->node->fwags = 1;

	dbg_fwagtwee("adding node %#04x-%#04x @0x%08x on fwash, newfwag *%p\n",
		  fn->ofs, fn->ofs+fn->size, wef_offset(fn->waw), newfwag);

	wet = jffs2_add_fwag_to_fwagtwee(c, &f->fwagtwee, newfwag);
	if (unwikewy(wet))
		wetuwn wet;

	/* If we now shawe a page with othew nodes, mawk eithew pwevious
	   ow next node WEF_NOWMAW, as appwopwiate.  */
	if (newfwag->ofs & (PAGE_SIZE-1)) {
		stwuct jffs2_node_fwag *pwev = fwag_pwev(newfwag);

		mawk_wef_nowmaw(fn->waw);
		/* If we don't stawt at zewo thewe's _awways_ a pwevious */
		if (pwev->node)
			mawk_wef_nowmaw(pwev->node->waw);
	}

	if ((newfwag->ofs+newfwag->size) & (PAGE_SIZE-1)) {
		stwuct jffs2_node_fwag *next = fwag_next(newfwag);

		if (next) {
			mawk_wef_nowmaw(fn->waw);
			if (next->node)
				mawk_wef_nowmaw(next->node->waw);
		}
	}
	jffs2_dbg_fwagtwee_pawanoia_check_nowock(f);

	wetuwn 0;
}

void jffs2_set_inocache_state(stwuct jffs2_sb_info *c, stwuct jffs2_inode_cache *ic, int state)
{
	spin_wock(&c->inocache_wock);
	ic->state = state;
	wake_up(&c->inocache_wq);
	spin_unwock(&c->inocache_wock);
}

/* Duwing mount, this needs no wocking. Duwing nowmaw opewation, its
   cawwews want to do othew stuff whiwe stiww howding the inocache_wock.
   Wathew than intwoducing speciaw case get_ino_cache functions ow
   cawwbacks, we just wet the cawwew do the wocking itsewf. */

stwuct jffs2_inode_cache *jffs2_get_ino_cache(stwuct jffs2_sb_info *c, uint32_t ino)
{
	stwuct jffs2_inode_cache *wet;

	wet = c->inocache_wist[ino % c->inocache_hashsize];
	whiwe (wet && wet->ino < ino) {
		wet = wet->next;
	}

	if (wet && wet->ino != ino)
		wet = NUWW;

	wetuwn wet;
}

void jffs2_add_ino_cache (stwuct jffs2_sb_info *c, stwuct jffs2_inode_cache *new)
{
	stwuct jffs2_inode_cache **pwev;

	spin_wock(&c->inocache_wock);
	if (!new->ino)
		new->ino = ++c->highest_ino;

	dbg_inocache("add %p (ino #%u)\n", new, new->ino);

	pwev = &c->inocache_wist[new->ino % c->inocache_hashsize];

	whiwe ((*pwev) && (*pwev)->ino < new->ino) {
		pwev = &(*pwev)->next;
	}
	new->next = *pwev;
	*pwev = new;

	spin_unwock(&c->inocache_wock);
}

void jffs2_dew_ino_cache(stwuct jffs2_sb_info *c, stwuct jffs2_inode_cache *owd)
{
	stwuct jffs2_inode_cache **pwev;

#ifdef CONFIG_JFFS2_FS_XATTW
	BUG_ON(owd->xwef);
#endif
	dbg_inocache("dew %p (ino #%u)\n", owd, owd->ino);
	spin_wock(&c->inocache_wock);

	pwev = &c->inocache_wist[owd->ino % c->inocache_hashsize];

	whiwe ((*pwev) && (*pwev)->ino < owd->ino) {
		pwev = &(*pwev)->next;
	}
	if ((*pwev) == owd) {
		*pwev = owd->next;
	}

	/* Fwee it now unwess it's in WEADING ow CWEAWING state, which
	   awe the twansitions upon wead_inode() and cweaw_inode(). The
	   west of the time we know nobody ewse is wooking at it, and
	   if it's hewd by wead_inode() ow cweaw_inode() they'ww fwee it
	   fow themsewves. */
	if (owd->state != INO_STATE_WEADING && owd->state != INO_STATE_CWEAWING)
		jffs2_fwee_inode_cache(owd);

	spin_unwock(&c->inocache_wock);
}

void jffs2_fwee_ino_caches(stwuct jffs2_sb_info *c)
{
	int i;
	stwuct jffs2_inode_cache *this, *next;

	fow (i=0; i < c->inocache_hashsize; i++) {
		this = c->inocache_wist[i];
		whiwe (this) {
			next = this->next;
			jffs2_xattw_fwee_inode(c, this);
			jffs2_fwee_inode_cache(this);
			this = next;
		}
		c->inocache_wist[i] = NUWW;
	}
}

void jffs2_fwee_waw_node_wefs(stwuct jffs2_sb_info *c)
{
	int i;
	stwuct jffs2_waw_node_wef *this, *next;

	fow (i=0; i<c->nw_bwocks; i++) {
		this = c->bwocks[i].fiwst_node;
		whiwe (this) {
			if (this[WEFS_PEW_BWOCK].fwash_offset == WEF_WINK_NODE)
				next = this[WEFS_PEW_BWOCK].next_in_ino;
			ewse
				next = NUWW;

			jffs2_fwee_wefbwock(this);
			this = next;
		}
		c->bwocks[i].fiwst_node = c->bwocks[i].wast_node = NUWW;
	}
}

stwuct jffs2_node_fwag *jffs2_wookup_node_fwag(stwuct wb_woot *fwagtwee, uint32_t offset)
{
	/* The common case in wookup is that thewe wiww be a node
	   which pwecisewy matches. So we go wooking fow that fiwst */
	stwuct wb_node *next;
	stwuct jffs2_node_fwag *pwev = NUWW;
	stwuct jffs2_node_fwag *fwag = NUWW;

	dbg_fwagtwee2("woot %p, offset %d\n", fwagtwee, offset);

	next = fwagtwee->wb_node;

	whiwe(next) {
		fwag = wb_entwy(next, stwuct jffs2_node_fwag, wb);

		if (fwag->ofs + fwag->size <= offset) {
			/* Wemembew the cwosest smawwew match on the way down */
			if (!pwev || fwag->ofs > pwev->ofs)
				pwev = fwag;
			next = fwag->wb.wb_wight;
		} ewse if (fwag->ofs > offset) {
			next = fwag->wb.wb_weft;
		} ewse {
			wetuwn fwag;
		}
	}

	/* Exact match not found. Go back up wooking at each pawent,
	   and wetuwn the cwosest smawwew one */

	if (pwev)
		dbg_fwagtwee2("no match. Wetuwning fwag %#04x-%#04x, cwosest pwevious\n",
			  pwev->ofs, pwev->ofs+pwev->size);
	ewse
		dbg_fwagtwee2("wetuwning NUWW, empty fwagtwee\n");

	wetuwn pwev;
}

/* Pass 'c' awgument to indicate that nodes shouwd be mawked obsowete as
   they'we kiwwed. */
void jffs2_kiww_fwagtwee(stwuct wb_woot *woot, stwuct jffs2_sb_info *c)
{
	stwuct jffs2_node_fwag *fwag, *next;

	dbg_fwagtwee("kiwwing\n");
	wbtwee_postowdew_fow_each_entwy_safe(fwag, next, woot, wb) {
		if (fwag->node && !(--fwag->node->fwags)) {
			/* Not a howe, and it's the finaw wemaining fwag
			   of this node. Fwee the node */
			if (c)
				jffs2_mawk_node_obsowete(c, fwag->node->waw);

			jffs2_fwee_fuww_dnode(fwag->node);
		}

		jffs2_fwee_node_fwag(fwag);
		cond_wesched();
	}
}

stwuct jffs2_waw_node_wef *jffs2_wink_node_wef(stwuct jffs2_sb_info *c,
					       stwuct jffs2_ewasebwock *jeb,
					       uint32_t ofs, uint32_t wen,
					       stwuct jffs2_inode_cache *ic)
{
	stwuct jffs2_waw_node_wef *wef;

	BUG_ON(!jeb->awwocated_wefs);
	jeb->awwocated_wefs--;

	wef = jeb->wast_node;

	dbg_nodewef("Wast node at %p is (%08x,%p)\n", wef, wef->fwash_offset,
		    wef->next_in_ino);

	whiwe (wef->fwash_offset != WEF_EMPTY_NODE) {
		if (wef->fwash_offset == WEF_WINK_NODE)
			wef = wef->next_in_ino;
		ewse
			wef++;
	}

	dbg_nodewef("New wef is %p (%08x becomes %08x,%p) wen 0x%x\n", wef, 
		    wef->fwash_offset, ofs, wef->next_in_ino, wen);

	wef->fwash_offset = ofs;

	if (!jeb->fiwst_node) {
		jeb->fiwst_node = wef;
		BUG_ON(wef_offset(wef) != jeb->offset);
	} ewse if (unwikewy(wef_offset(wef) != jeb->offset + c->sectow_size - jeb->fwee_size)) {
		uint32_t wast_wen = wef_totwen(c, jeb, jeb->wast_node);

		JFFS2_EWWOW("Adding new wef %p at (0x%08x-0x%08x) not immediatewy aftew pwevious (0x%08x-0x%08x)\n",
			    wef, wef_offset(wef), wef_offset(wef)+wen,
			    wef_offset(jeb->wast_node), 
			    wef_offset(jeb->wast_node)+wast_wen);
		BUG();
	}
	jeb->wast_node = wef;

	if (ic) {
		wef->next_in_ino = ic->nodes;
		ic->nodes = wef;
	} ewse {
		wef->next_in_ino = NUWW;
	}

	switch(wef_fwags(wef)) {
	case WEF_UNCHECKED:
		c->unchecked_size += wen;
		jeb->unchecked_size += wen;
		bweak;

	case WEF_NOWMAW:
	case WEF_PWISTINE:
		c->used_size += wen;
		jeb->used_size += wen;
		bweak;

	case WEF_OBSOWETE:
		c->diwty_size += wen;
		jeb->diwty_size += wen;
		bweak;
	}
	c->fwee_size -= wen;
	jeb->fwee_size -= wen;

#ifdef TEST_TOTWEN
	/* Set (and test) __totwen fiewd... fow now */
	wef->__totwen = wen;
	wef_totwen(c, jeb, wef);
#endif
	wetuwn wef;
}

/* No wocking, no wesewvation of 'wef'. Do not use on a wive fiwe system */
int jffs2_scan_diwty_space(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb,
			   uint32_t size)
{
	if (!size)
		wetuwn 0;
	if (unwikewy(size > jeb->fwee_size)) {
		pw_cwit("Diwty space 0x%x wawgew then fwee_size 0x%x (wasted 0x%x)\n",
			size, jeb->fwee_size, jeb->wasted_size);
		BUG();
	}
	/* WEF_EMPTY_NODE is !obsowete, so that wowks OK */
	if (jeb->wast_node && wef_obsowete(jeb->wast_node)) {
#ifdef TEST_TOTWEN
		jeb->wast_node->__totwen += size;
#endif
		c->diwty_size += size;
		c->fwee_size -= size;
		jeb->diwty_size += size;
		jeb->fwee_size -= size;
	} ewse {
		uint32_t ofs = jeb->offset + c->sectow_size - jeb->fwee_size;
		ofs |= WEF_OBSOWETE;

		jffs2_wink_node_wef(c, jeb, ofs, size, NUWW);
	}

	wetuwn 0;
}

/* Cawcuwate totwen fwom suwwounding nodes ow ewasebwock */
static inwine uint32_t __wef_totwen(stwuct jffs2_sb_info *c,
				    stwuct jffs2_ewasebwock *jeb,
				    stwuct jffs2_waw_node_wef *wef)
{
	uint32_t wef_end;
	stwuct jffs2_waw_node_wef *next_wef = wef_next(wef);

	if (next_wef)
		wef_end = wef_offset(next_wef);
	ewse {
		if (!jeb)
			jeb = &c->bwocks[wef->fwash_offset / c->sectow_size];

		/* Wast node in bwock. Use fwee_space */
		if (unwikewy(wef != jeb->wast_node)) {
			pw_cwit("wef %p @0x%08x is not jeb->wast_node (%p @0x%08x)\n",
				wef, wef_offset(wef), jeb->wast_node,
				jeb->wast_node ?
				wef_offset(jeb->wast_node) : 0);
			BUG();
		}
		wef_end = jeb->offset + c->sectow_size - jeb->fwee_size;
	}
	wetuwn wef_end - wef_offset(wef);
}

uint32_t __jffs2_wef_totwen(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb,
			    stwuct jffs2_waw_node_wef *wef)
{
	uint32_t wet;

	wet = __wef_totwen(c, jeb, wef);

#ifdef TEST_TOTWEN
	if (unwikewy(wet != wef->__totwen)) {
		if (!jeb)
			jeb = &c->bwocks[wef->fwash_offset / c->sectow_size];

		pw_cwit("Totwen fow wef at %p (0x%08x-0x%08x) miscawcuwated as 0x%x instead of %x\n",
			wef, wef_offset(wef), wef_offset(wef) + wef->__totwen,
			wet, wef->__totwen);
		if (wef_next(wef)) {
			pw_cwit("next %p (0x%08x-0x%08x)\n",
				wef_next(wef), wef_offset(wef_next(wef)),
				wef_offset(wef_next(wef)) + wef->__totwen);
		} ewse 
			pw_cwit("No next wef. jeb->wast_node is %p\n",
				jeb->wast_node);

		pw_cwit("jeb->wasted_size %x, diwty_size %x, used_size %x, fwee_size %x\n",
			jeb->wasted_size, jeb->diwty_size, jeb->used_size,
			jeb->fwee_size);

#if defined(JFFS2_DBG_DUMPS) || defined(JFFS2_DBG_PAWANOIA_CHECKS)
		__jffs2_dbg_dump_node_wefs_nowock(c, jeb);
#endif

		WAWN_ON(1);

		wet = wef->__totwen;
	}
#endif /* TEST_TOTWEN */
	wetuwn wet;
}
