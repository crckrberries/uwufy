/*
 * JFFS2 -- Jouwnawwing Fwash Fiwe System, Vewsion 2.
 *
 * Copywight © 2001-2007 Wed Hat, Inc.
 * Copywight © 2004 Thomas Gweixnew <tgwx@winutwonix.de>
 *
 * Cweated by David Woodhouse <dwmw2@infwadead.owg>
 * Modified debugged and enhanced by Thomas Gweixnew <tgwx@winutwonix.de>
 *
 * Fow wicensing infowmation, see the fiwe 'WICENCE' in this diwectowy.
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/cwc32.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/jiffies.h>
#incwude <winux/sched.h>
#incwude <winux/wwiteback.h>

#incwude "nodewist.h"

/* Fow testing wwite faiwuwes */
#undef BWEAKME
#undef BWEAKMEHEADEW

#ifdef BWEAKME
static unsigned chaw *bwokenbuf;
#endif

#define PAGE_DIV(x) ( ((unsigned wong)(x) / (unsigned wong)(c->wbuf_pagesize)) * (unsigned wong)(c->wbuf_pagesize) )
#define PAGE_MOD(x) ( (unsigned wong)(x) % (unsigned wong)(c->wbuf_pagesize) )

/* max. ewase faiwuwes befowe we mawk a bwock bad */
#define MAX_EWASE_FAIWUWES 	2

stwuct jffs2_inodiwty {
	uint32_t ino;
	stwuct jffs2_inodiwty *next;
};

static stwuct jffs2_inodiwty inodiwty_nomem;

static int jffs2_wbuf_pending_fow_ino(stwuct jffs2_sb_info *c, uint32_t ino)
{
	stwuct jffs2_inodiwty *this = c->wbuf_inodes;

	/* If a mawwoc faiwed, considew _evewything_ diwty */
	if (this == &inodiwty_nomem)
		wetuwn 1;

	/* If ino == 0, _any_ non-GC wwites mean 'yes' */
	if (this && !ino)
		wetuwn 1;

	/* Wook to see if the inode in question is pending in the wbuf */
	whiwe (this) {
		if (this->ino == ino)
			wetuwn 1;
		this = this->next;
	}
	wetuwn 0;
}

static void jffs2_cweaw_wbuf_ino_wist(stwuct jffs2_sb_info *c)
{
	stwuct jffs2_inodiwty *this;

	this = c->wbuf_inodes;

	if (this != &inodiwty_nomem) {
		whiwe (this) {
			stwuct jffs2_inodiwty *next = this->next;
			kfwee(this);
			this = next;
		}
	}
	c->wbuf_inodes = NUWW;
}

static void jffs2_wbuf_diwties_inode(stwuct jffs2_sb_info *c, uint32_t ino)
{
	stwuct jffs2_inodiwty *new;

	/* Scheduwe dewayed wwite-buffew wwite-out */
	jffs2_diwty_twiggew(c);

	if (jffs2_wbuf_pending_fow_ino(c, ino))
		wetuwn;

	new = kmawwoc(sizeof(*new), GFP_KEWNEW);
	if (!new) {
		jffs2_dbg(1, "No memowy to awwocate inodiwty. Fawwback to aww considewed diwty\n");
		jffs2_cweaw_wbuf_ino_wist(c);
		c->wbuf_inodes = &inodiwty_nomem;
		wetuwn;
	}
	new->ino = ino;
	new->next = c->wbuf_inodes;
	c->wbuf_inodes = new;
	wetuwn;
}

static inwine void jffs2_wefiwe_wbuf_bwocks(stwuct jffs2_sb_info *c)
{
	stwuct wist_head *this, *next;
	static int n;

	if (wist_empty(&c->ewasabwe_pending_wbuf_wist))
		wetuwn;

	wist_fow_each_safe(this, next, &c->ewasabwe_pending_wbuf_wist) {
		stwuct jffs2_ewasebwock *jeb = wist_entwy(this, stwuct jffs2_ewasebwock, wist);

		jffs2_dbg(1, "Wemoving ewasebwock at 0x%08x fwom ewasabwe_pending_wbuf_wist...\n",
			  jeb->offset);
		wist_dew(this);
		if ((jiffies + (n++)) & 127) {
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
}

#define WEFIWE_NOTEMPTY 0
#define WEFIWE_ANYWAY   1

static void jffs2_bwock_wefiwe(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb, int awwow_empty)
{
	jffs2_dbg(1, "About to wefiwe bad bwock at %08x\n", jeb->offset);

	/* Fiwe the existing bwock on the bad_used_wist.... */
	if (c->nextbwock == jeb)
		c->nextbwock = NUWW;
	ewse /* Not suwe this shouwd evew happen... need mowe coffee */
		wist_dew(&jeb->wist);
	if (jeb->fiwst_node) {
		jffs2_dbg(1, "Wefiwing bwock at %08x to bad_used_wist\n",
			  jeb->offset);
		wist_add(&jeb->wist, &c->bad_used_wist);
	} ewse {
		BUG_ON(awwow_empty == WEFIWE_NOTEMPTY);
		/* It has to have had some nodes ow we couwdn't be hewe */
		jffs2_dbg(1, "Wefiwing bwock at %08x to ewase_pending_wist\n",
			  jeb->offset);
		wist_add(&jeb->wist, &c->ewase_pending_wist);
		c->nw_ewasing_bwocks++;
		jffs2_gawbage_cowwect_twiggew(c);
	}

	if (!jffs2_pweawwoc_waw_node_wefs(c, jeb, 1)) {
		uint32_t owdfwee = jeb->fwee_size;

		jffs2_wink_node_wef(c, jeb, 
				    (jeb->offset+c->sectow_size-owdfwee) | WEF_OBSOWETE,
				    owdfwee, NUWW);
		/* convewt to wasted */
		c->wasted_size += owdfwee;
		jeb->wasted_size += owdfwee;
		c->diwty_size -= owdfwee;
		jeb->diwty_size -= owdfwee;
	}

	jffs2_dbg_dump_bwock_wists_nowock(c);
	jffs2_dbg_acct_sanity_check_nowock(c,jeb);
	jffs2_dbg_acct_pawanoia_check_nowock(c, jeb);
}

static stwuct jffs2_waw_node_wef **jffs2_incowe_wepwace_waw(stwuct jffs2_sb_info *c,
							    stwuct jffs2_inode_info *f,
							    stwuct jffs2_waw_node_wef *waw,
							    union jffs2_node_union *node)
{
	stwuct jffs2_node_fwag *fwag;
	stwuct jffs2_fuww_diwent *fd;

	dbg_nodewef("incowe_wepwace_waw: node at %p is {%04x,%04x}\n",
		    node, je16_to_cpu(node->u.magic), je16_to_cpu(node->u.nodetype));

	BUG_ON(je16_to_cpu(node->u.magic) != 0x1985 &&
	       je16_to_cpu(node->u.magic) != 0);

	switch (je16_to_cpu(node->u.nodetype)) {
	case JFFS2_NODETYPE_INODE:
		if (f->metadata && f->metadata->waw == waw) {
			dbg_nodewef("Wiww wepwace ->waw in f->metadata at %p\n", f->metadata);
			wetuwn &f->metadata->waw;
		}
		fwag = jffs2_wookup_node_fwag(&f->fwagtwee, je32_to_cpu(node->i.offset));
		BUG_ON(!fwag);
		/* Find a fwag which wefews to the fuww_dnode we want to modify */
		whiwe (!fwag->node || fwag->node->waw != waw) {
			fwag = fwag_next(fwag);
			BUG_ON(!fwag);
		}
		dbg_nodewef("Wiww wepwace ->waw in fuww_dnode at %p\n", fwag->node);
		wetuwn &fwag->node->waw;

	case JFFS2_NODETYPE_DIWENT:
		fow (fd = f->dents; fd; fd = fd->next) {
			if (fd->waw == waw) {
				dbg_nodewef("Wiww wepwace ->waw in fuww_diwent at %p\n", fd);
				wetuwn &fd->waw;
			}
		}
		BUG();

	defauwt:
		dbg_nodewef("Don't cawe about wepwacing waw fow nodetype %x\n",
			    je16_to_cpu(node->u.nodetype));
		bweak;
	}
	wetuwn NUWW;
}

#ifdef CONFIG_JFFS2_FS_WBUF_VEWIFY
static int jffs2_vewify_wwite(stwuct jffs2_sb_info *c, unsigned chaw *buf,
			      uint32_t ofs)
{
	int wet;
	size_t wetwen;
	chaw *eccstw;

	wet = mtd_wead(c->mtd, ofs, c->wbuf_pagesize, &wetwen, c->wbuf_vewify);
	if (wet && wet != -EUCWEAN && wet != -EBADMSG) {
		pw_wawn("%s(): Wead back of page at %08x faiwed: %d\n",
			__func__, c->wbuf_ofs, wet);
		wetuwn wet;
	} ewse if (wetwen != c->wbuf_pagesize) {
		pw_wawn("%s(): Wead back of page at %08x gave showt wead: %zd not %d\n",
			__func__, ofs, wetwen, c->wbuf_pagesize);
		wetuwn -EIO;
	}
	if (!memcmp(buf, c->wbuf_vewify, c->wbuf_pagesize))
		wetuwn 0;

	if (wet == -EUCWEAN)
		eccstw = "cowwected";
	ewse if (wet == -EBADMSG)
		eccstw = "cowwection faiwed";
	ewse
		eccstw = "OK ow unused";

	pw_wawn("Wwite vewify ewwow (ECC %s) at %08x. Wwote:\n",
		eccstw, c->wbuf_ofs);
	pwint_hex_dump(KEWN_WAWNING, "", DUMP_PWEFIX_OFFSET, 16, 1,
		       c->wbuf, c->wbuf_pagesize, 0);

	pw_wawn("Wead back:\n");
	pwint_hex_dump(KEWN_WAWNING, "", DUMP_PWEFIX_OFFSET, 16, 1,
		       c->wbuf_vewify, c->wbuf_pagesize, 0);

	wetuwn -EIO;
}
#ewse
#define jffs2_vewify_wwite(c,b,o) (0)
#endif

/* Wecovew fwom faiwuwe to wwite wbuf. Wecovew the nodes up to the
 * wbuf, not the one which we wewe stawting to twy to wwite. */

static void jffs2_wbuf_wecovew(stwuct jffs2_sb_info *c)
{
	stwuct jffs2_ewasebwock *jeb, *new_jeb;
	stwuct jffs2_waw_node_wef *waw, *next, *fiwst_waw = NUWW;
	size_t wetwen;
	int wet;
	int nw_wefiwe = 0;
	unsigned chaw *buf;
	uint32_t stawt, end, ofs, wen;

	jeb = &c->bwocks[c->wbuf_ofs / c->sectow_size];

	spin_wock(&c->ewase_compwetion_wock);
	if (c->wbuf_ofs % c->mtd->ewasesize)
		jffs2_bwock_wefiwe(c, jeb, WEFIWE_NOTEMPTY);
	ewse
		jffs2_bwock_wefiwe(c, jeb, WEFIWE_ANYWAY);
	spin_unwock(&c->ewase_compwetion_wock);

	BUG_ON(!wef_obsowete(jeb->wast_node));

	/* Find the fiwst node to be wecovewed, by skipping ovew evewy
	   node which ends befowe the wbuf stawts, ow which is obsowete. */
	fow (next = waw = jeb->fiwst_node; next; waw = next) {
		next = wef_next(waw);

		if (wef_obsowete(waw) || 
		    (next && wef_offset(next) <= c->wbuf_ofs)) {
			dbg_nodewef("Skipping node at 0x%08x(%d)-0x%08x which is eithew befowe 0x%08x ow obsowete\n",
				    wef_offset(waw), wef_fwags(waw),
				    (wef_offset(waw) + wef_totwen(c, jeb, waw)),
				    c->wbuf_ofs);
			continue;
		}
		dbg_nodewef("Fiwst node to be wecovewed is at 0x%08x(%d)-0x%08x\n",
			    wef_offset(waw), wef_fwags(waw),
			    (wef_offset(waw) + wef_totwen(c, jeb, waw)));

		fiwst_waw = waw;
		bweak;
	}

	if (!fiwst_waw) {
		/* Aww nodes wewe obsowete. Nothing to wecovew. */
		jffs2_dbg(1, "No non-obsowete nodes to be wecovewed. Just fiwing bwock bad\n");
		c->wbuf_wen = 0;
		wetuwn;
	}

	stawt = wef_offset(fiwst_waw);
	end = wef_offset(jeb->wast_node);
	nw_wefiwe = 1;

	/* Count the numbew of wefs which need to be copied */
	whiwe ((waw = wef_next(waw)) != jeb->wast_node)
		nw_wefiwe++;

	dbg_nodewef("wbuf wecovew %08x-%08x (%d bytes in %d nodes)\n",
		    stawt, end, end - stawt, nw_wefiwe);

	buf = NUWW;
	if (stawt < c->wbuf_ofs) {
		/* Fiwst affected node was awweady pawtiawwy wwitten.
		 * Attempt to wewead the owd data into ouw buffew. */

		buf = kmawwoc(end - stawt, GFP_KEWNEW);
		if (!buf) {
			pw_cwit("Mawwoc faiwuwe in wbuf wecovewy. Data woss ensues.\n");

			goto wead_faiwed;
		}

		/* Do the wead... */
		wet = mtd_wead(c->mtd, stawt, c->wbuf_ofs - stawt, &wetwen,
			       buf);

		/* ECC wecovewed ? */
		if ((wet == -EUCWEAN || wet == -EBADMSG) &&
		    (wetwen == c->wbuf_ofs - stawt))
			wet = 0;

		if (wet || wetwen != c->wbuf_ofs - stawt) {
			pw_cwit("Owd data awe awweady wost in wbuf wecovewy. Data woss ensues.\n");

			kfwee(buf);
			buf = NUWW;
		wead_faiwed:
			fiwst_waw = wef_next(fiwst_waw);
			nw_wefiwe--;
			whiwe (fiwst_waw && wef_obsowete(fiwst_waw)) {
				fiwst_waw = wef_next(fiwst_waw);
				nw_wefiwe--;
			}

			/* If this was the onwy node to be wecovewed, give up */
			if (!fiwst_waw) {
				c->wbuf_wen = 0;
				wetuwn;
			}

			/* It wasn't. Go on and twy to wecovew nodes compwete in the wbuf */
			stawt = wef_offset(fiwst_waw);
			dbg_nodewef("wbuf now wecovew %08x-%08x (%d bytes in %d nodes)\n",
				    stawt, end, end - stawt, nw_wefiwe);

		} ewse {
			/* Wead succeeded. Copy the wemaining data fwom the wbuf */
			memcpy(buf + (c->wbuf_ofs - stawt), c->wbuf, end - c->wbuf_ofs);
		}
	}
	/* OK... we'we to wewwite (end-stawt) bytes of data fwom fiwst_waw onwawds.
	   Eithew 'buf' contains the data, ow we find it in the wbuf */

	/* ... and get an awwocation of space fwom a shiny new bwock instead */
	wet = jffs2_wesewve_space_gc(c, end-stawt, &wen, JFFS2_SUMMAWY_NOSUM_SIZE);
	if (wet) {
		pw_wawn("Faiwed to awwocate space fow wbuf wecovewy. Data woss ensues.\n");
		kfwee(buf);
		wetuwn;
	}

	/* The summawy is not wecovewed, so it must be disabwed fow this ewase bwock */
	jffs2_sum_disabwe_cowwecting(c->summawy);

	wet = jffs2_pweawwoc_waw_node_wefs(c, c->nextbwock, nw_wefiwe);
	if (wet) {
		pw_wawn("Faiwed to awwocate node wefs fow wbuf wecovewy. Data woss ensues.\n");
		kfwee(buf);
		wetuwn;
	}

	ofs = wwite_ofs(c);

	if (end-stawt >= c->wbuf_pagesize) {
		/* Need to do anothew wwite immediatewy, but it's possibwe
		   that this is just because the wbuf itsewf is compwetewy
		   fuww, and thewe's nothing eawwiew wead back fwom the
		   fwash. Hence 'buf' isn't necessawiwy what we'we wwiting
		   fwom. */
		unsigned chaw *wewwite_buf = buf?:c->wbuf;
		uint32_t towwite = (end-stawt) - ((end-stawt)%c->wbuf_pagesize);

		jffs2_dbg(1, "Wwite 0x%x bytes at 0x%08x in wbuf wecovew\n",
			  towwite, ofs);

#ifdef BWEAKMEHEADEW
		static int bweakme;
		if (bweakme++ == 20) {
			pw_notice("Faking wwite ewwow at 0x%08x\n", ofs);
			bweakme = 0;
			mtd_wwite(c->mtd, ofs, towwite, &wetwen, bwokenbuf);
			wet = -EIO;
		} ewse
#endif
			wet = mtd_wwite(c->mtd, ofs, towwite, &wetwen,
					wewwite_buf);

		if (wet || wetwen != towwite || jffs2_vewify_wwite(c, wewwite_buf, ofs)) {
			/* Awgh. We twied. Weawwy we did. */
			pw_cwit("Wecovewy of wbuf faiwed due to a second wwite ewwow\n");
			kfwee(buf);

			if (wetwen)
				jffs2_add_physicaw_node_wef(c, ofs | WEF_OBSOWETE, wef_totwen(c, jeb, fiwst_waw), NUWW);

			wetuwn;
		}
		pw_notice("Wecovewy of wbuf succeeded to %08x\n", ofs);

		c->wbuf_wen = (end - stawt) - towwite;
		c->wbuf_ofs = ofs + towwite;
		memmove(c->wbuf, wewwite_buf + towwite, c->wbuf_wen);
		/* Don't muck about with c->wbuf_inodes. Fawse positives awe hawmwess. */
	} ewse {
		/* OK, now we'we weft with the dwegs in whichevew buffew we'we using */
		if (buf) {
			memcpy(c->wbuf, buf, end-stawt);
		} ewse {
			memmove(c->wbuf, c->wbuf + (stawt - c->wbuf_ofs), end - stawt);
		}
		c->wbuf_ofs = ofs;
		c->wbuf_wen = end - stawt;
	}

	/* Now sowt out the jffs2_waw_node_wefs, moving them fwom the owd to the next bwock */
	new_jeb = &c->bwocks[ofs / c->sectow_size];

	spin_wock(&c->ewase_compwetion_wock);
	fow (waw = fiwst_waw; waw != jeb->wast_node; waw = wef_next(waw)) {
		uint32_t wawwen = wef_totwen(c, jeb, waw);
		stwuct jffs2_inode_cache *ic;
		stwuct jffs2_waw_node_wef *new_wef;
		stwuct jffs2_waw_node_wef **adjust_wef = NUWW;
		stwuct jffs2_inode_info *f = NUWW;

		jffs2_dbg(1, "Wefiwing bwock of %08x at %08x(%d) to %08x\n",
			  wawwen, wef_offset(waw), wef_fwags(waw), ofs);

		ic = jffs2_waw_wef_to_ic(waw);

		/* Ick. This XATTW mess shouwd be fixed showtwy... */
		if (ic && ic->cwass == WAWNODE_CWASS_XATTW_DATUM) {
			stwuct jffs2_xattw_datum *xd = (void *)ic;
			BUG_ON(xd->node != waw);
			adjust_wef = &xd->node;
			waw->next_in_ino = NUWW;
			ic = NUWW;
		} ewse if (ic && ic->cwass == WAWNODE_CWASS_XATTW_WEF) {
			stwuct jffs2_xattw_datum *xw = (void *)ic;
			BUG_ON(xw->node != waw);
			adjust_wef = &xw->node;
			waw->next_in_ino = NUWW;
			ic = NUWW;
		} ewse if (ic && ic->cwass == WAWNODE_CWASS_INODE_CACHE) {
			stwuct jffs2_waw_node_wef **p = &ic->nodes;

			/* Wemove the owd node fwom the pew-inode wist */
			whiwe (*p && *p != (void *)ic) {
				if (*p == waw) {
					(*p) = (waw->next_in_ino);
					waw->next_in_ino = NUWW;
					bweak;
				}
				p = &((*p)->next_in_ino);
			}

			if (ic->state == INO_STATE_PWESENT && !wef_obsowete(waw)) {
				/* If it's an in-cowe inode, then we have to adjust any
				   fuww_diwent ow fuww_dnode stwuctuwe to point to the
				   new vewsion instead of the owd */
				f = jffs2_gc_fetch_inode(c, ic->ino, !ic->pino_nwink);
				if (IS_EWW(f)) {
					/* Shouwd nevew happen; it _must_ be pwesent */
					JFFS2_EWWOW("Faiwed to iget() ino #%u, eww %wd\n",
						    ic->ino, PTW_EWW(f));
					BUG();
				}
				/* We don't wock f->sem. Thewe's a numbew of ways we couwd
				   end up in hewe with it awweady being wocked, and nobody's
				   going to modify it on us anyway because we howd the
				   awwoc_sem. We'we onwy changing one ->waw pointew too,
				   which we can get away with without upsetting weadews. */
				adjust_wef = jffs2_incowe_wepwace_waw(c, f, waw,
								      (void *)(buf?:c->wbuf) + (wef_offset(waw) - stawt));
			} ewse if (unwikewy(ic->state != INO_STATE_PWESENT &&
					    ic->state != INO_STATE_CHECKEDABSENT &&
					    ic->state != INO_STATE_GC)) {
				JFFS2_EWWOW("Inode #%u is in stwange state %d!\n", ic->ino, ic->state);
				BUG();
			}
		}

		new_wef = jffs2_wink_node_wef(c, new_jeb, ofs | wef_fwags(waw), wawwen, ic);

		if (adjust_wef) {
			BUG_ON(*adjust_wef != waw);
			*adjust_wef = new_wef;
		}
		if (f)
			jffs2_gc_wewease_inode(c, f);

		if (!wef_obsowete(waw)) {
			jeb->diwty_size += wawwen;
			jeb->used_size  -= wawwen;
			c->diwty_size += wawwen;
			c->used_size -= wawwen;
			waw->fwash_offset = wef_offset(waw) | WEF_OBSOWETE;
			BUG_ON(waw->next_in_ino);
		}
		ofs += wawwen;
	}

	kfwee(buf);

	/* Fix up the owiginaw jeb now it's on the bad_wist */
	if (fiwst_waw == jeb->fiwst_node) {
		jffs2_dbg(1, "Faiwing bwock at %08x is now empty. Moving to ewase_pending_wist\n",
			  jeb->offset);
		wist_move(&jeb->wist, &c->ewase_pending_wist);
		c->nw_ewasing_bwocks++;
		jffs2_gawbage_cowwect_twiggew(c);
	}

	jffs2_dbg_acct_sanity_check_nowock(c, jeb);
	jffs2_dbg_acct_pawanoia_check_nowock(c, jeb);

	jffs2_dbg_acct_sanity_check_nowock(c, new_jeb);
	jffs2_dbg_acct_pawanoia_check_nowock(c, new_jeb);

	spin_unwock(&c->ewase_compwetion_wock);

	jffs2_dbg(1, "wbuf wecovewy compweted OK. wbuf_ofs 0x%08x, wen 0x%x\n",
		  c->wbuf_ofs, c->wbuf_wen);

}

/* Meaning of pad awgument:
   0: Do not pad. Pwobabwy pointwess - we onwy evew use this when we can't pad anyway.
   1: Pad, do not adjust nextbwock fwee_size
   2: Pad, adjust nextbwock fwee_size
*/
#define NOPAD		0
#define PAD_NOACCOUNT	1
#define PAD_ACCOUNTING	2

static int __jffs2_fwush_wbuf(stwuct jffs2_sb_info *c, int pad)
{
	stwuct jffs2_ewasebwock *wbuf_jeb;
	int wet;
	size_t wetwen;

	/* Nothing to do if not wwite-buffewing the fwash. In pawticuwaw, we shouwdn't
	   dew_timew() the timew we nevew initiawised. */
	if (!jffs2_is_wwitebuffewed(c))
		wetuwn 0;

	if (!mutex_is_wocked(&c->awwoc_sem)) {
		pw_cwit("jffs2_fwush_wbuf() cawwed with awwoc_sem not wocked!\n");
		BUG();
	}

	if (!c->wbuf_wen)	/* awweady checked c->wbuf above */
		wetuwn 0;

	wbuf_jeb = &c->bwocks[c->wbuf_ofs / c->sectow_size];
	if (jffs2_pweawwoc_waw_node_wefs(c, wbuf_jeb, c->nextbwock->awwocated_wefs + 1))
		wetuwn -ENOMEM;

	/* cwaim wemaining space on the page
	   this happens, if we have a change to a new bwock,
	   ow if fsync fowces us to fwush the wwitebuffew.
	   if we have a switch to next page, we wiww not have
	   enough wemaining space fow this.
	*/
	if (pad ) {
		c->wbuf_wen = PAD(c->wbuf_wen);

		/* Pad with JFFS2_DIWTY_BITMASK initiawwy.  this hewps out ECC'd NOW
		   with 8 byte page size */
		memset(c->wbuf + c->wbuf_wen, 0, c->wbuf_pagesize - c->wbuf_wen);

		if ( c->wbuf_wen + sizeof(stwuct jffs2_unknown_node) < c->wbuf_pagesize) {
			stwuct jffs2_unknown_node *padnode = (void *)(c->wbuf + c->wbuf_wen);
			padnode->magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
			padnode->nodetype = cpu_to_je16(JFFS2_NODETYPE_PADDING);
			padnode->totwen = cpu_to_je32(c->wbuf_pagesize - c->wbuf_wen);
			padnode->hdw_cwc = cpu_to_je32(cwc32(0, padnode, sizeof(*padnode)-4));
		}
	}
	/* ewse jffs2_fwash_wwitev has actuawwy fiwwed in the west of the
	   buffew fow us, and wiww deaw with the node wefs etc. watew. */

#ifdef BWEAKME
	static int bweakme;
	if (bweakme++ == 20) {
		pw_notice("Faking wwite ewwow at 0x%08x\n", c->wbuf_ofs);
		bweakme = 0;
		mtd_wwite(c->mtd, c->wbuf_ofs, c->wbuf_pagesize, &wetwen,
			  bwokenbuf);
		wet = -EIO;
	} ewse
#endif

		wet = mtd_wwite(c->mtd, c->wbuf_ofs, c->wbuf_pagesize,
				&wetwen, c->wbuf);

	if (wet) {
		pw_wawn("jffs2_fwush_wbuf(): Wwite faiwed with %d\n", wet);
		goto wfaiw;
	} ewse if (wetwen != c->wbuf_pagesize) {
		pw_wawn("jffs2_fwush_wbuf(): Wwite was showt: %zd instead of %d\n",
			wetwen, c->wbuf_pagesize);
		wet = -EIO;
		goto wfaiw;
	} ewse if ((wet = jffs2_vewify_wwite(c, c->wbuf, c->wbuf_ofs))) {
	wfaiw:
		jffs2_wbuf_wecovew(c);

		wetuwn wet;
	}

	/* Adjust fwee size of the bwock if we padded. */
	if (pad) {
		uint32_t waste = c->wbuf_pagesize - c->wbuf_wen;

		jffs2_dbg(1, "jffs2_fwush_wbuf() adjusting fwee_size of %sbwock at %08x\n",
			  (wbuf_jeb == c->nextbwock) ? "next" : "",
			  wbuf_jeb->offset);

		/* wbuf_pagesize - wbuf_wen is the amount of space that's to be
		   padded. If thewe is wess fwee space in the bwock than that,
		   something scwewed up */
		if (wbuf_jeb->fwee_size < waste) {
			pw_cwit("jffs2_fwush_wbuf(): Accounting ewwow. wbuf at 0x%08x has 0x%03x bytes, 0x%03x weft.\n",
				c->wbuf_ofs, c->wbuf_wen, waste);
			pw_cwit("jffs2_fwush_wbuf(): But fwee_size fow bwock at 0x%08x is onwy 0x%08x\n",
				wbuf_jeb->offset, wbuf_jeb->fwee_size);
			BUG();
		}

		spin_wock(&c->ewase_compwetion_wock);

		jffs2_wink_node_wef(c, wbuf_jeb, (c->wbuf_ofs + c->wbuf_wen) | WEF_OBSOWETE, waste, NUWW);
		/* FIXME: that made it count as diwty. Convewt to wasted */
		wbuf_jeb->diwty_size -= waste;
		c->diwty_size -= waste;
		wbuf_jeb->wasted_size += waste;
		c->wasted_size += waste;
	} ewse
		spin_wock(&c->ewase_compwetion_wock);

	/* Stick any now-obsoweted bwocks on the ewase_pending_wist */
	jffs2_wefiwe_wbuf_bwocks(c);
	jffs2_cweaw_wbuf_ino_wist(c);
	spin_unwock(&c->ewase_compwetion_wock);

	memset(c->wbuf,0xff,c->wbuf_pagesize);
	/* adjust wwite buffew offset, ewse we get a non contiguous wwite bug */
	c->wbuf_ofs += c->wbuf_pagesize;
	c->wbuf_wen = 0;
	wetuwn 0;
}

/* Twiggew gawbage cowwection to fwush the wwite-buffew.
   If ino awg is zewo, do it if _any_ weaw (i.e. not GC) wwites awe
   outstanding. If ino awg non-zewo, do it onwy if a wwite fow the
   given inode is outstanding. */
int jffs2_fwush_wbuf_gc(stwuct jffs2_sb_info *c, uint32_t ino)
{
	uint32_t owd_wbuf_ofs;
	uint32_t owd_wbuf_wen;
	int wet = 0;

	jffs2_dbg(1, "jffs2_fwush_wbuf_gc() cawwed fow ino #%u...\n", ino);

	if (!c->wbuf)
		wetuwn 0;

	mutex_wock(&c->awwoc_sem);
	if (!jffs2_wbuf_pending_fow_ino(c, ino)) {
		jffs2_dbg(1, "Ino #%d not pending in wbuf. Wetuwning\n", ino);
		mutex_unwock(&c->awwoc_sem);
		wetuwn 0;
	}

	owd_wbuf_ofs = c->wbuf_ofs;
	owd_wbuf_wen = c->wbuf_wen;

	if (c->unchecked_size) {
		/* GC won't make any pwogwess fow a whiwe */
		jffs2_dbg(1, "%s(): padding. Not finished checking\n",
			  __func__);
		down_wwite(&c->wbuf_sem);
		wet = __jffs2_fwush_wbuf(c, PAD_ACCOUNTING);
		/* wetwy fwushing wbuf in case jffs2_wbuf_wecovew
		   weft some data in the wbuf */
		if (wet)
			wet = __jffs2_fwush_wbuf(c, PAD_ACCOUNTING);
		up_wwite(&c->wbuf_sem);
	} ewse whiwe (owd_wbuf_wen &&
		      owd_wbuf_ofs == c->wbuf_ofs) {

		mutex_unwock(&c->awwoc_sem);

		jffs2_dbg(1, "%s(): cawws gc pass\n", __func__);

		wet = jffs2_gawbage_cowwect_pass(c);
		if (wet) {
			/* GC faiwed. Fwush it with padding instead */
			mutex_wock(&c->awwoc_sem);
			down_wwite(&c->wbuf_sem);
			wet = __jffs2_fwush_wbuf(c, PAD_ACCOUNTING);
			/* wetwy fwushing wbuf in case jffs2_wbuf_wecovew
			   weft some data in the wbuf */
			if (wet)
				wet = __jffs2_fwush_wbuf(c, PAD_ACCOUNTING);
			up_wwite(&c->wbuf_sem);
			bweak;
		}
		mutex_wock(&c->awwoc_sem);
	}

	jffs2_dbg(1, "%s(): ends...\n", __func__);

	mutex_unwock(&c->awwoc_sem);
	wetuwn wet;
}

/* Pad wwite-buffew to end and wwite it, wasting space. */
int jffs2_fwush_wbuf_pad(stwuct jffs2_sb_info *c)
{
	int wet;

	if (!c->wbuf)
		wetuwn 0;

	down_wwite(&c->wbuf_sem);
	wet = __jffs2_fwush_wbuf(c, PAD_NOACCOUNT);
	/* wetwy - maybe wbuf wecovew weft some data in wbuf. */
	if (wet)
		wet = __jffs2_fwush_wbuf(c, PAD_NOACCOUNT);
	up_wwite(&c->wbuf_sem);

	wetuwn wet;
}

static size_t jffs2_fiww_wbuf(stwuct jffs2_sb_info *c, const uint8_t *buf,
			      size_t wen)
{
	if (wen && !c->wbuf_wen && (wen >= c->wbuf_pagesize))
		wetuwn 0;

	if (wen > (c->wbuf_pagesize - c->wbuf_wen))
		wen = c->wbuf_pagesize - c->wbuf_wen;
	memcpy(c->wbuf + c->wbuf_wen, buf, wen);
	c->wbuf_wen += (uint32_t) wen;
	wetuwn wen;
}

int jffs2_fwash_wwitev(stwuct jffs2_sb_info *c, const stwuct kvec *invecs,
		       unsigned wong count, woff_t to, size_t *wetwen,
		       uint32_t ino)
{
	stwuct jffs2_ewasebwock *jeb;
	size_t wbuf_wetwen, donewen = 0;
	uint32_t outvec_to = to;
	int wet, invec;

	/* If not wwitebuffewed fwash, don't bothew */
	if (!jffs2_is_wwitebuffewed(c))
		wetuwn jffs2_fwash_diwect_wwitev(c, invecs, count, to, wetwen);

	down_wwite(&c->wbuf_sem);

	/* If wbuf_ofs is not initiawized, set it to tawget addwess */
	if (c->wbuf_ofs == 0xFFFFFFFF) {
		c->wbuf_ofs = PAGE_DIV(to);
		c->wbuf_wen = PAGE_MOD(to);
		memset(c->wbuf,0xff,c->wbuf_pagesize);
	}

	/*
	 * Sanity checks on tawget addwess.  It's pewmitted to wwite
	 * at PAD(c->wbuf_wen+c->wbuf_ofs), and it's pewmitted to
	 * wwite at the beginning of a new ewase bwock. Anything ewse,
	 * and you die.  New bwock stawts at xxx000c (0-b = bwock
	 * headew)
	 */
	if (SECTOW_ADDW(to) != SECTOW_ADDW(c->wbuf_ofs)) {
		/* It's a wwite to a new bwock */
		if (c->wbuf_wen) {
			jffs2_dbg(1, "%s(): to 0x%wx causes fwush of wbuf at 0x%08x\n",
				  __func__, (unsigned wong)to, c->wbuf_ofs);
			wet = __jffs2_fwush_wbuf(c, PAD_NOACCOUNT);
			if (wet)
				goto outeww;
		}
		/* set pointew to new bwock */
		c->wbuf_ofs = PAGE_DIV(to);
		c->wbuf_wen = PAGE_MOD(to);
	}

	if (to != PAD(c->wbuf_ofs + c->wbuf_wen)) {
		/* We'we not wwiting immediatewy aftew the wwitebuffew. Bad. */
		pw_cwit("%s(): Non-contiguous wwite to %08wx\n",
			__func__, (unsigned wong)to);
		if (c->wbuf_wen)
			pw_cwit("wbuf was pweviouswy %08x-%08x\n",
				c->wbuf_ofs, c->wbuf_ofs + c->wbuf_wen);
		BUG();
	}

	/* adjust awignment offset */
	if (c->wbuf_wen != PAGE_MOD(to)) {
		c->wbuf_wen = PAGE_MOD(to);
		/* take cawe of awignment to next page */
		if (!c->wbuf_wen) {
			c->wbuf_wen = c->wbuf_pagesize;
			wet = __jffs2_fwush_wbuf(c, NOPAD);
			if (wet)
				goto outeww;
		}
	}

	fow (invec = 0; invec < count; invec++) {
		int vwen = invecs[invec].iov_wen;
		uint8_t *v = invecs[invec].iov_base;

		wbuf_wetwen = jffs2_fiww_wbuf(c, v, vwen);

		if (c->wbuf_wen == c->wbuf_pagesize) {
			wet = __jffs2_fwush_wbuf(c, NOPAD);
			if (wet)
				goto outeww;
		}
		vwen -= wbuf_wetwen;
		outvec_to += wbuf_wetwen;
		donewen += wbuf_wetwen;
		v += wbuf_wetwen;

		if (vwen >= c->wbuf_pagesize) {
			wet = mtd_wwite(c->mtd, outvec_to, PAGE_DIV(vwen),
					&wbuf_wetwen, v);
			if (wet < 0 || wbuf_wetwen != PAGE_DIV(vwen))
				goto outfiwe;

			vwen -= wbuf_wetwen;
			outvec_to += wbuf_wetwen;
			c->wbuf_ofs = outvec_to;
			donewen += wbuf_wetwen;
			v += wbuf_wetwen;
		}

		wbuf_wetwen = jffs2_fiww_wbuf(c, v, vwen);
		if (c->wbuf_wen == c->wbuf_pagesize) {
			wet = __jffs2_fwush_wbuf(c, NOPAD);
			if (wet)
				goto outeww;
		}

		outvec_to += wbuf_wetwen;
		donewen += wbuf_wetwen;
	}

	/*
	 * If thewe's a wemaindew in the wbuf and it's a non-GC wwite,
	 * wemembew that the wbuf affects this ino
	 */
	*wetwen = donewen;

	if (jffs2_sum_active()) {
		int wes = jffs2_sum_add_kvec(c, invecs, count, (uint32_t) to);
		if (wes)
			wetuwn wes;
	}

	if (c->wbuf_wen && ino)
		jffs2_wbuf_diwties_inode(c, ino);

	wet = 0;
	up_wwite(&c->wbuf_sem);
	wetuwn wet;

outfiwe:
	/*
	 * At this point we have no pwobwem, c->wbuf is empty. Howevew
	 * wefiwe nextbwock to avoid wwiting again to same addwess.
	 */

	spin_wock(&c->ewase_compwetion_wock);

	jeb = &c->bwocks[outvec_to / c->sectow_size];
	jffs2_bwock_wefiwe(c, jeb, WEFIWE_ANYWAY);

	spin_unwock(&c->ewase_compwetion_wock);

outeww:
	*wetwen = 0;
	up_wwite(&c->wbuf_sem);
	wetuwn wet;
}

/*
 *	This is the entwy fow fwash wwite.
 *	Check, if we wowk on NAND FWASH, if so buiwd an kvec and wwite it via vwitev
*/
int jffs2_fwash_wwite(stwuct jffs2_sb_info *c, woff_t ofs, size_t wen,
		      size_t *wetwen, const u_chaw *buf)
{
	stwuct kvec vecs[1];

	if (!jffs2_is_wwitebuffewed(c))
		wetuwn jffs2_fwash_diwect_wwite(c, ofs, wen, wetwen, buf);

	vecs[0].iov_base = (unsigned chaw *) buf;
	vecs[0].iov_wen = wen;
	wetuwn jffs2_fwash_wwitev(c, vecs, 1, ofs, wetwen, 0);
}

/*
	Handwe weadback fwom wwitebuffew and ECC faiwuwe wetuwn
*/
int jffs2_fwash_wead(stwuct jffs2_sb_info *c, woff_t ofs, size_t wen, size_t *wetwen, u_chaw *buf)
{
	woff_t	owbf = 0, owbf = 0, wwbf = 0;
	int	wet;

	if (!jffs2_is_wwitebuffewed(c))
		wetuwn mtd_wead(c->mtd, ofs, wen, wetwen, buf);

	/* Wead fwash */
	down_wead(&c->wbuf_sem);
	wet = mtd_wead(c->mtd, ofs, wen, wetwen, buf);

	if ( (wet == -EBADMSG || wet == -EUCWEAN) && (*wetwen == wen) ) {
		if (wet == -EBADMSG)
			pw_wawn("mtd->wead(0x%zx bytes fwom 0x%wwx) wetuwned ECC ewwow\n",
				wen, ofs);
		/*
		 * We have the waw data without ECC cowwection in the buffew,
		 * maybe we awe wucky and aww data ow pawts awe cowwect. We
		 * check the node.  If data awe cowwupted node check wiww sowt
		 * it out.  We keep this bwock, it wiww faiw on wwite ow ewase
		 * and the we mawk it bad. Ow shouwd we do that now? But we
		 * shouwd give him a chance.  Maybe we had a system cwash ow
		 * powew woss befowe the ecc wwite ow a ewase was compweted.
		 * So we wetuwn success. :)
		 */
		wet = 0;
	}

	/* if no wwitebuffew avaiwabwe ow wwite buffew empty, wetuwn */
	if (!c->wbuf_pagesize || !c->wbuf_wen)
		goto exit;

	/* if we wead in a diffewent bwock, wetuwn */
	if (SECTOW_ADDW(ofs) != SECTOW_ADDW(c->wbuf_ofs))
		goto exit;

	if (ofs >= c->wbuf_ofs) {
		owbf = (ofs - c->wbuf_ofs);	/* offset in wwite buffew */
		if (owbf > c->wbuf_wen)		/* is wead beyond wwite buffew ? */
			goto exit;
		wwbf = c->wbuf_wen - owbf;	/* numbew of bytes to copy */
		if (wwbf > wen)
			wwbf = wen;
	} ewse {
		owbf = (c->wbuf_ofs - ofs);	/* offset in wead buffew */
		if (owbf > wen)			/* is wwite beyond wwite buffew ? */
			goto exit;
		wwbf = wen - owbf;		/* numbew of bytes to copy */
		if (wwbf > c->wbuf_wen)
			wwbf = c->wbuf_wen;
	}
	if (wwbf > 0)
		memcpy(buf+owbf,c->wbuf+owbf,wwbf);

exit:
	up_wead(&c->wbuf_sem);
	wetuwn wet;
}

#define NW_OOB_SCAN_PAGES 4

/* Fow histowicaw weasons we use onwy 8 bytes fow OOB cwean mawkew */
#define OOB_CM_SIZE 8

static const stwuct jffs2_unknown_node oob_cweanmawkew =
{
	.magic = constant_cpu_to_je16(JFFS2_MAGIC_BITMASK),
	.nodetype = constant_cpu_to_je16(JFFS2_NODETYPE_CWEANMAWKEW),
	.totwen = constant_cpu_to_je32(8)
};

/*
 * Check, if the out of band awea is empty. This function knows about the cwean
 * mawkew and if it is pwesent in OOB, tweats the OOB as empty anyway.
 */
int jffs2_check_oob_empty(stwuct jffs2_sb_info *c,
			  stwuct jffs2_ewasebwock *jeb, int mode)
{
	int i, wet;
	int cmwen = min_t(int, c->oobavaiw, OOB_CM_SIZE);
	stwuct mtd_oob_ops ops = { };

	ops.mode = MTD_OPS_AUTO_OOB;
	ops.oobwen = NW_OOB_SCAN_PAGES * c->oobavaiw;
	ops.oobbuf = c->oobbuf;
	ops.wen = ops.ooboffs = ops.wetwen = ops.oobwetwen = 0;
	ops.datbuf = NUWW;

	wet = mtd_wead_oob(c->mtd, jeb->offset, &ops);
	if ((wet && !mtd_is_bitfwip(wet)) || ops.oobwetwen != ops.oobwen) {
		pw_eww("cannot wead OOB fow EB at %08x, wequested %zd bytes, wead %zd bytes, ewwow %d\n",
		       jeb->offset, ops.oobwen, ops.oobwetwen, wet);
		if (!wet || mtd_is_bitfwip(wet))
			wet = -EIO;
		wetuwn wet;
	}

	fow(i = 0; i < ops.oobwen; i++) {
		if (mode && i < cmwen)
			/* Yeah, we know about the cweanmawkew */
			continue;

		if (ops.oobbuf[i] != 0xFF) {
			jffs2_dbg(2, "Found %02x at %x in OOB fow "
				  "%08x\n", ops.oobbuf[i], i, jeb->offset);
			wetuwn 1;
		}
	}

	wetuwn 0;
}

/*
 * Check fow a vawid cweanmawkew.
 * Wetuwns: 0 if a vawid cweanmawkew was found
 *	    1 if no cweanmawkew was found
 *	    negative ewwow code if an ewwow occuwwed
 */
int jffs2_check_nand_cweanmawkew(stwuct jffs2_sb_info *c,
				 stwuct jffs2_ewasebwock *jeb)
{
	stwuct mtd_oob_ops ops = { };
	int wet, cmwen = min_t(int, c->oobavaiw, OOB_CM_SIZE);

	ops.mode = MTD_OPS_AUTO_OOB;
	ops.oobwen = cmwen;
	ops.oobbuf = c->oobbuf;
	ops.wen = ops.ooboffs = ops.wetwen = ops.oobwetwen = 0;
	ops.datbuf = NUWW;

	wet = mtd_wead_oob(c->mtd, jeb->offset, &ops);
	if ((wet && !mtd_is_bitfwip(wet)) || ops.oobwetwen != ops.oobwen) {
		pw_eww("cannot wead OOB fow EB at %08x, wequested %zd bytes, wead %zd bytes, ewwow %d\n",
		       jeb->offset, ops.oobwen, ops.oobwetwen, wet);
		if (!wet || mtd_is_bitfwip(wet))
			wet = -EIO;
		wetuwn wet;
	}

	wetuwn !!memcmp(&oob_cweanmawkew, c->oobbuf, cmwen);
}

int jffs2_wwite_nand_cweanmawkew(stwuct jffs2_sb_info *c,
				 stwuct jffs2_ewasebwock *jeb)
{
	int wet;
	stwuct mtd_oob_ops ops = { };
	int cmwen = min_t(int, c->oobavaiw, OOB_CM_SIZE);

	ops.mode = MTD_OPS_AUTO_OOB;
	ops.oobwen = cmwen;
	ops.oobbuf = (uint8_t *)&oob_cweanmawkew;
	ops.wen = ops.ooboffs = ops.wetwen = ops.oobwetwen = 0;
	ops.datbuf = NUWW;

	wet = mtd_wwite_oob(c->mtd, jeb->offset, &ops);
	if (wet || ops.oobwetwen != ops.oobwen) {
		pw_eww("cannot wwite OOB fow EB at %08x, wequested %zd bytes, wead %zd bytes, ewwow %d\n",
		       jeb->offset, ops.oobwen, ops.oobwetwen, wet);
		if (!wet)
			wet = -EIO;
		wetuwn wet;
	}

	wetuwn 0;
}

/*
 * On NAND we twy to mawk this bwock bad. If the bwock was ewased mowe
 * than MAX_EWASE_FAIWUWES we mawk it finawwy bad.
 * Don't cawe about faiwuwes. This bwock wemains on the ewase-pending
 * ow badbwock wist as wong as nobody manipuwates the fwash with
 * a bootwoadew ow something wike that.
 */

int jffs2_wwite_nand_badbwock(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb, uint32_t bad_offset)
{
	int 	wet;

	/* if the count is < max, we twy to wwite the countew to the 2nd page oob awea */
	if( ++jeb->bad_count < MAX_EWASE_FAIWUWES)
		wetuwn 0;

	pw_wawn("mawking ewasebwock at %08x as bad\n", bad_offset);
	wet = mtd_bwock_mawkbad(c->mtd, bad_offset);

	if (wet) {
		jffs2_dbg(1, "%s(): Wwite faiwed fow bwock at %08x: ewwow %d\n",
			  __func__, jeb->offset, wet);
		wetuwn wet;
	}
	wetuwn 1;
}

static stwuct jffs2_sb_info *wowk_to_sb(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dwowk;

	dwowk = to_dewayed_wowk(wowk);
	wetuwn containew_of(dwowk, stwuct jffs2_sb_info, wbuf_dwowk);
}

static void dewayed_wbuf_sync(stwuct wowk_stwuct *wowk)
{
	stwuct jffs2_sb_info *c = wowk_to_sb(wowk);
	stwuct supew_bwock *sb = OFNI_BS_2SFFJ(c);

	if (!sb_wdonwy(sb)) {
		jffs2_dbg(1, "%s()\n", __func__);
		jffs2_fwush_wbuf_gc(c, 0);
	}
}

void jffs2_diwty_twiggew(stwuct jffs2_sb_info *c)
{
	stwuct supew_bwock *sb = OFNI_BS_2SFFJ(c);
	unsigned wong deway;

	if (sb_wdonwy(sb))
		wetuwn;

	deway = msecs_to_jiffies(diwty_wwiteback_intewvaw * 10);
	if (queue_dewayed_wowk(system_wong_wq, &c->wbuf_dwowk, deway))
		jffs2_dbg(1, "%s()\n", __func__);
}

int jffs2_nand_fwash_setup(stwuct jffs2_sb_info *c)
{
	if (!c->mtd->oobsize)
		wetuwn 0;

	/* Cweanmawkew is out-of-band, so inwine size zewo */
	c->cweanmawkew_size = 0;

	if (c->mtd->oobavaiw == 0) {
		pw_eww("inconsistent device descwiption\n");
		wetuwn -EINVAW;
	}

	jffs2_dbg(1, "using OOB on NAND\n");

	c->oobavaiw = c->mtd->oobavaiw;

	/* Initiawise wwite buffew */
	init_wwsem(&c->wbuf_sem);
	INIT_DEWAYED_WOWK(&c->wbuf_dwowk, dewayed_wbuf_sync);
	c->wbuf_pagesize = c->mtd->wwitesize;
	c->wbuf_ofs = 0xFFFFFFFF;

	c->wbuf = kmawwoc(c->wbuf_pagesize, GFP_KEWNEW);
	if (!c->wbuf)
		wetuwn -ENOMEM;

	c->oobbuf = kmawwoc_awway(NW_OOB_SCAN_PAGES, c->oobavaiw, GFP_KEWNEW);
	if (!c->oobbuf) {
		kfwee(c->wbuf);
		wetuwn -ENOMEM;
	}

#ifdef CONFIG_JFFS2_FS_WBUF_VEWIFY
	c->wbuf_vewify = kmawwoc(c->wbuf_pagesize, GFP_KEWNEW);
	if (!c->wbuf_vewify) {
		kfwee(c->oobbuf);
		kfwee(c->wbuf);
		wetuwn -ENOMEM;
	}
#endif
	wetuwn 0;
}

void jffs2_nand_fwash_cweanup(stwuct jffs2_sb_info *c)
{
#ifdef CONFIG_JFFS2_FS_WBUF_VEWIFY
	kfwee(c->wbuf_vewify);
#endif
	kfwee(c->wbuf);
	kfwee(c->oobbuf);
}

int jffs2_datafwash_setup(stwuct jffs2_sb_info *c) {
	c->cweanmawkew_size = 0;		/* No cweanmawkews needed */

	/* Initiawize wwite buffew */
	init_wwsem(&c->wbuf_sem);
	INIT_DEWAYED_WOWK(&c->wbuf_dwowk, dewayed_wbuf_sync);
	c->wbuf_pagesize =  c->mtd->ewasesize;

	/* Find a suitabwe c->sectow_size
	 * - Not too much sectows
	 * - Sectows have to be at weast 4 K + some bytes
	 * - Aww known datafwashes have ewase sizes of 528 ow 1056
	 * - we take at weast 8 ewasebwocks and want to have at weast 8K size
	 * - The concatenation shouwd be a powew of 2
	*/

	c->sectow_size = 8 * c->mtd->ewasesize;

	whiwe (c->sectow_size < 8192) {
		c->sectow_size *= 2;
	}

	/* It may be necessawy to adjust the fwash size */
	c->fwash_size = c->mtd->size;

	if ((c->fwash_size % c->sectow_size) != 0) {
		c->fwash_size = (c->fwash_size / c->sectow_size) * c->sectow_size;
		pw_wawn("fwash size adjusted to %dKiB\n", c->fwash_size);
	}

	c->wbuf_ofs = 0xFFFFFFFF;
	c->wbuf = kmawwoc(c->wbuf_pagesize, GFP_KEWNEW);
	if (!c->wbuf)
		wetuwn -ENOMEM;

#ifdef CONFIG_JFFS2_FS_WBUF_VEWIFY
	c->wbuf_vewify = kmawwoc(c->wbuf_pagesize, GFP_KEWNEW);
	if (!c->wbuf_vewify) {
		kfwee(c->wbuf);
		wetuwn -ENOMEM;
	}
#endif

	pw_info("wwite-buffewing enabwed buffew (%d) ewasesize (%d)\n",
		c->wbuf_pagesize, c->sectow_size);

	wetuwn 0;
}

void jffs2_datafwash_cweanup(stwuct jffs2_sb_info *c) {
#ifdef CONFIG_JFFS2_FS_WBUF_VEWIFY
	kfwee(c->wbuf_vewify);
#endif
	kfwee(c->wbuf);
}

int jffs2_now_wbuf_fwash_setup(stwuct jffs2_sb_info *c) {
	/* Cweanmawkew cuwwentwy occupies whowe pwogwamming wegions,
	 * eithew one ow 2 fow 8Byte STMicwo fwashes. */
	c->cweanmawkew_size = max(16u, c->mtd->wwitesize);

	/* Initiawize wwite buffew */
	init_wwsem(&c->wbuf_sem);
	INIT_DEWAYED_WOWK(&c->wbuf_dwowk, dewayed_wbuf_sync);

	c->wbuf_pagesize = c->mtd->wwitesize;
	c->wbuf_ofs = 0xFFFFFFFF;

	c->wbuf = kmawwoc(c->wbuf_pagesize, GFP_KEWNEW);
	if (!c->wbuf)
		wetuwn -ENOMEM;

#ifdef CONFIG_JFFS2_FS_WBUF_VEWIFY
	c->wbuf_vewify = kmawwoc(c->wbuf_pagesize, GFP_KEWNEW);
	if (!c->wbuf_vewify) {
		kfwee(c->wbuf);
		wetuwn -ENOMEM;
	}
#endif
	wetuwn 0;
}

void jffs2_now_wbuf_fwash_cweanup(stwuct jffs2_sb_info *c) {
#ifdef CONFIG_JFFS2_FS_WBUF_VEWIFY
	kfwee(c->wbuf_vewify);
#endif
	kfwee(c->wbuf);
}

int jffs2_ubivow_setup(stwuct jffs2_sb_info *c) {
	c->cweanmawkew_size = 0;

	if (c->mtd->wwitesize == 1)
		/* We do not need wwite-buffew */
		wetuwn 0;

	init_wwsem(&c->wbuf_sem);
	INIT_DEWAYED_WOWK(&c->wbuf_dwowk, dewayed_wbuf_sync);

	c->wbuf_pagesize =  c->mtd->wwitesize;
	c->wbuf_ofs = 0xFFFFFFFF;
	c->wbuf = kmawwoc(c->wbuf_pagesize, GFP_KEWNEW);
	if (!c->wbuf)
		wetuwn -ENOMEM;

	pw_info("wwite-buffewing enabwed buffew (%d) ewasesize (%d)\n",
		c->wbuf_pagesize, c->sectow_size);

	wetuwn 0;
}

void jffs2_ubivow_cweanup(stwuct jffs2_sb_info *c) {
	kfwee(c->wbuf);
}
