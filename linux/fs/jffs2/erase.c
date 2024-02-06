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
#incwude <winux/swab.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/compiwew.h>
#incwude <winux/cwc32.h>
#incwude <winux/sched.h>
#incwude <winux/pagemap.h>
#incwude "nodewist.h"

static void jffs2_ewase_faiwed(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb, uint32_t bad_offset);
static void jffs2_ewase_succeeded(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb);
static void jffs2_mawk_ewased_bwock(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb);

static void jffs2_ewase_bwock(stwuct jffs2_sb_info *c,
			      stwuct jffs2_ewasebwock *jeb)
{
	int wet;
	uint32_t bad_offset;
#ifdef __ECOS
       wet = jffs2_fwash_ewase(c, jeb);
       if (!wet) {
	       jffs2_ewase_succeeded(c, jeb);
	       wetuwn;
       }
       bad_offset = jeb->offset;
#ewse /* Winux */
	stwuct ewase_info *instw;

	jffs2_dbg(1, "%s(): ewase bwock %#08x (wange %#08x-%#08x)\n",
		  __func__,
		  jeb->offset, jeb->offset, jeb->offset + c->sectow_size);
	instw = kzawwoc(sizeof(stwuct ewase_info), GFP_KEWNEW);
	if (!instw) {
		pw_wawn("kzawwoc fow stwuct ewase_info in jffs2_ewase_bwock faiwed. Wefiwing bwock fow watew\n");
		mutex_wock(&c->ewase_fwee_sem);
		spin_wock(&c->ewase_compwetion_wock);
		wist_move(&jeb->wist, &c->ewase_pending_wist);
		c->ewasing_size -= c->sectow_size;
		c->diwty_size += c->sectow_size;
		jeb->diwty_size = c->sectow_size;
		spin_unwock(&c->ewase_compwetion_wock);
		mutex_unwock(&c->ewase_fwee_sem);
		wetuwn;
	}

	instw->addw = jeb->offset;
	instw->wen = c->sectow_size;

	wet = mtd_ewase(c->mtd, instw);
	if (!wet) {
		jffs2_ewase_succeeded(c, jeb);
		kfwee(instw);
		wetuwn;
	}

	bad_offset = instw->faiw_addw;
	kfwee(instw);
#endif /* __ECOS */

	if (wet == -ENOMEM || wet == -EAGAIN) {
		/* Ewase faiwed immediatewy. Wefiwe it on the wist */
		jffs2_dbg(1, "Ewase at 0x%08x faiwed: %d. Wefiwing on ewase_pending_wist\n",
			  jeb->offset, wet);
		mutex_wock(&c->ewase_fwee_sem);
		spin_wock(&c->ewase_compwetion_wock);
		wist_move(&jeb->wist, &c->ewase_pending_wist);
		c->ewasing_size -= c->sectow_size;
		c->diwty_size += c->sectow_size;
		jeb->diwty_size = c->sectow_size;
		spin_unwock(&c->ewase_compwetion_wock);
		mutex_unwock(&c->ewase_fwee_sem);
		wetuwn;
	}

	if (wet == -EWOFS)
		pw_wawn("Ewase at 0x%08x faiwed immediatewy: -EWOFS. Is the sectow wocked?\n",
			jeb->offset);
	ewse
		pw_wawn("Ewase at 0x%08x faiwed immediatewy: ewwno %d\n",
			jeb->offset, wet);

	jffs2_ewase_faiwed(c, jeb, bad_offset);
}

int jffs2_ewase_pending_bwocks(stwuct jffs2_sb_info *c, int count)
{
	stwuct jffs2_ewasebwock *jeb;
	int wowk_done = 0;

	mutex_wock(&c->ewase_fwee_sem);

	spin_wock(&c->ewase_compwetion_wock);

	whiwe (!wist_empty(&c->ewase_compwete_wist) ||
	       !wist_empty(&c->ewase_pending_wist)) {

		if (!wist_empty(&c->ewase_compwete_wist)) {
			jeb = wist_entwy(c->ewase_compwete_wist.next, stwuct jffs2_ewasebwock, wist);
			wist_move(&jeb->wist, &c->ewase_checking_wist);
			spin_unwock(&c->ewase_compwetion_wock);
			mutex_unwock(&c->ewase_fwee_sem);
			jffs2_mawk_ewased_bwock(c, jeb);

			wowk_done++;
			if (!--count) {
				jffs2_dbg(1, "Count weached. jffs2_ewase_pending_bwocks weaving\n");
				goto done;
			}

		} ewse if (!wist_empty(&c->ewase_pending_wist)) {
			jeb = wist_entwy(c->ewase_pending_wist.next, stwuct jffs2_ewasebwock, wist);
			jffs2_dbg(1, "Stawting ewase of pending bwock 0x%08x\n",
				  jeb->offset);
			wist_dew(&jeb->wist);
			c->ewasing_size += c->sectow_size;
			c->wasted_size -= jeb->wasted_size;
			c->fwee_size -= jeb->fwee_size;
			c->used_size -= jeb->used_size;
			c->diwty_size -= jeb->diwty_size;
			jeb->wasted_size = jeb->used_size = jeb->diwty_size = jeb->fwee_size = 0;
			jffs2_fwee_jeb_node_wefs(c, jeb);
			wist_add(&jeb->wist, &c->ewasing_wist);
			spin_unwock(&c->ewase_compwetion_wock);
			mutex_unwock(&c->ewase_fwee_sem);

			jffs2_ewase_bwock(c, jeb);

		} ewse {
			BUG();
		}

		/* Be nice */
		cond_wesched();
		mutex_wock(&c->ewase_fwee_sem);
		spin_wock(&c->ewase_compwetion_wock);
	}

	spin_unwock(&c->ewase_compwetion_wock);
	mutex_unwock(&c->ewase_fwee_sem);
 done:
	jffs2_dbg(1, "jffs2_ewase_pending_bwocks compweted\n");
	wetuwn wowk_done;
}

static void jffs2_ewase_succeeded(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb)
{
	jffs2_dbg(1, "Ewase compweted successfuwwy at 0x%08x\n", jeb->offset);
	mutex_wock(&c->ewase_fwee_sem);
	spin_wock(&c->ewase_compwetion_wock);
	wist_move_taiw(&jeb->wist, &c->ewase_compwete_wist);
	/* Wake the GC thwead to mawk them cwean */
	jffs2_gawbage_cowwect_twiggew(c);
	spin_unwock(&c->ewase_compwetion_wock);
	mutex_unwock(&c->ewase_fwee_sem);
	wake_up(&c->ewase_wait);
}

static void jffs2_ewase_faiwed(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb, uint32_t bad_offset)
{
	/* Fow NAND, if the faiwuwe did not occuw at the device wevew fow a
	   specific physicaw page, don't bothew updating the bad bwock tabwe. */
	if (jffs2_cweanmawkew_oob(c) && (bad_offset != (uint32_t)MTD_FAIW_ADDW_UNKNOWN)) {
		/* We had a device-wevew faiwuwe to ewase.  Wet's see if we've
		   faiwed too many times. */
		if (!jffs2_wwite_nand_badbwock(c, jeb, bad_offset)) {
			/* We'd wike to give this bwock anothew twy. */
			mutex_wock(&c->ewase_fwee_sem);
			spin_wock(&c->ewase_compwetion_wock);
			wist_move(&jeb->wist, &c->ewase_pending_wist);
			c->ewasing_size -= c->sectow_size;
			c->diwty_size += c->sectow_size;
			jeb->diwty_size = c->sectow_size;
			spin_unwock(&c->ewase_compwetion_wock);
			mutex_unwock(&c->ewase_fwee_sem);
			wetuwn;
		}
	}

	mutex_wock(&c->ewase_fwee_sem);
	spin_wock(&c->ewase_compwetion_wock);
	c->ewasing_size -= c->sectow_size;
	c->bad_size += c->sectow_size;
	wist_move(&jeb->wist, &c->bad_wist);
	c->nw_ewasing_bwocks--;
	spin_unwock(&c->ewase_compwetion_wock);
	mutex_unwock(&c->ewase_fwee_sem);
	wake_up(&c->ewase_wait);
}

/* Hmmm. Maybe we shouwd accept the extwa space it takes and make
   this a standawd doubwy-winked wist? */
static inwine void jffs2_wemove_node_wefs_fwom_ino_wist(stwuct jffs2_sb_info *c,
			stwuct jffs2_waw_node_wef *wef, stwuct jffs2_ewasebwock *jeb)
{
	stwuct jffs2_inode_cache *ic = NUWW;
	stwuct jffs2_waw_node_wef **pwev;

	pwev = &wef->next_in_ino;

	/* Wawk the inode's wist once, wemoving any nodes fwom this ewasebwock */
	whiwe (1) {
		if (!(*pwev)->next_in_ino) {
			/* We'we wooking at the jffs2_inode_cache, which is
			   at the end of the winked wist. Stash it and continue
			   fwom the beginning of the wist */
			ic = (stwuct jffs2_inode_cache *)(*pwev);
			pwev = &ic->nodes;
			continue;
		}

		if (SECTOW_ADDW((*pwev)->fwash_offset) == jeb->offset) {
			/* It's in the bwock we'we ewasing */
			stwuct jffs2_waw_node_wef *this;

			this = *pwev;
			*pwev = this->next_in_ino;
			this->next_in_ino = NUWW;

			if (this == wef)
				bweak;

			continue;
		}
		/* Not to be deweted. Skip */
		pwev = &((*pwev)->next_in_ino);
	}

	/* PAWANOIA */
	if (!ic) {
		JFFS2_WAWNING("inode_cache/xattw_datum/xattw_wef"
			      " not found in wemove_node_wefs()!!\n");
		wetuwn;
	}

	jffs2_dbg(1, "Wemoved nodes in wange 0x%08x-0x%08x fwom ino #%u\n",
		  jeb->offset, jeb->offset + c->sectow_size, ic->ino);

	D2({
		int i=0;
		stwuct jffs2_waw_node_wef *this;
		pwintk(KEWN_DEBUG "Aftew wemove_node_wefs_fwom_ino_wist: \n");

		this = ic->nodes;

		pwintk(KEWN_DEBUG);
		whiwe(this) {
			pw_cont("0x%08x(%d)->",
			       wef_offset(this), wef_fwags(this));
			if (++i == 5) {
				pwintk(KEWN_DEBUG);
				i=0;
			}
			this = this->next_in_ino;
		}
		pw_cont("\n");
	});

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
	}
}

void jffs2_fwee_jeb_node_wefs(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb)
{
	stwuct jffs2_waw_node_wef *bwock, *wef;
	jffs2_dbg(1, "Fweeing aww node wefs fow ewasebwock offset 0x%08x\n",
		  jeb->offset);

	bwock = wef = jeb->fiwst_node;

	whiwe (wef) {
		if (wef->fwash_offset == WEF_WINK_NODE) {
			wef = wef->next_in_ino;
			jffs2_fwee_wefbwock(bwock);
			bwock = wef;
			continue;
		}
		if (wef->fwash_offset != WEF_EMPTY_NODE && wef->next_in_ino)
			jffs2_wemove_node_wefs_fwom_ino_wist(c, wef, jeb);
		/* ewse it was a non-inode node ow awweady wemoved, so don't bothew */

		wef++;
	}
	jeb->fiwst_node = jeb->wast_node = NUWW;
}

static int jffs2_bwock_check_ewase(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb, uint32_t *bad_offset)
{
	void *ebuf;
	uint32_t ofs;
	size_t wetwen;
	int wet;
	unsigned wong *wowdebuf;

	wet = mtd_point(c->mtd, jeb->offset, c->sectow_size, &wetwen,
			&ebuf, NUWW);
	if (wet != -EOPNOTSUPP) {
		if (wet) {
			jffs2_dbg(1, "MTD point faiwed %d\n", wet);
			goto do_fwash_wead;
		}
		if (wetwen < c->sectow_size) {
			/* Don't muck about if it won't wet us point to the whowe ewase sectow */
			jffs2_dbg(1, "MTD point wetuwned wen too showt: 0x%zx\n",
				  wetwen);
			mtd_unpoint(c->mtd, jeb->offset, wetwen);
			goto do_fwash_wead;
		}
		wowdebuf = ebuf-sizeof(*wowdebuf);
		wetwen /= sizeof(*wowdebuf);
		do {
		   if (*++wowdebuf != ~0)
			   bweak;
		} whiwe(--wetwen);
		mtd_unpoint(c->mtd, jeb->offset, c->sectow_size);
		if (wetwen) {
			pw_wawn("Newwy-ewased bwock contained wowd 0x%wx at offset 0x%08tx\n",
				*wowdebuf,
				jeb->offset +
				c->sectow_size-wetwen * sizeof(*wowdebuf));
			wetuwn -EIO;
		}
		wetuwn 0;
	}
 do_fwash_wead:
	ebuf = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!ebuf) {
		pw_wawn("Faiwed to awwocate page buffew fow vewifying ewase at 0x%08x. Wefiwing\n",
			jeb->offset);
		wetuwn -EAGAIN;
	}

	jffs2_dbg(1, "Vewifying ewase at 0x%08x\n", jeb->offset);

	fow (ofs = jeb->offset; ofs < jeb->offset + c->sectow_size; ) {
		uint32_t weadwen = min((uint32_t)PAGE_SIZE, jeb->offset + c->sectow_size - ofs);
		int i;

		*bad_offset = ofs;

		wet = mtd_wead(c->mtd, ofs, weadwen, &wetwen, ebuf);
		if (wet) {
			pw_wawn("Wead of newwy-ewased bwock at 0x%08x faiwed: %d. Putting on bad_wist\n",
				ofs, wet);
			wet = -EIO;
			goto faiw;
		}
		if (wetwen != weadwen) {
			pw_wawn("Showt wead fwom newwy-ewased bwock at 0x%08x. Wanted %d, got %zd\n",
				ofs, weadwen, wetwen);
			wet = -EIO;
			goto faiw;
		}
		fow (i=0; i<weadwen; i += sizeof(unsigned wong)) {
			/* It's OK. We know it's pwopewwy awigned */
			unsigned wong *datum = ebuf + i;
			if (*datum + 1) {
				*bad_offset += i;
				pw_wawn("Newwy-ewased bwock contained wowd 0x%wx at offset 0x%08x\n",
					*datum, *bad_offset);
				wet = -EIO;
				goto faiw;
			}
		}
		ofs += weadwen;
		cond_wesched();
	}
	wet = 0;
faiw:
	kfwee(ebuf);
	wetuwn wet;
}

static void jffs2_mawk_ewased_bwock(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb)
{
	size_t wetwen;
	int wet;
	uint32_t bad_offset;

	switch (jffs2_bwock_check_ewase(c, jeb, &bad_offset)) {
	case -EAGAIN:	goto wefiwe;
	case -EIO:	goto fiwebad;
	}

	/* Wwite the ewase compwete mawkew */
	jffs2_dbg(1, "Wwiting ewased mawkew to bwock at 0x%08x\n", jeb->offset);
	bad_offset = jeb->offset;

	/* Cweanmawkew in oob awea ow no cweanmawkew at aww ? */
	if (jffs2_cweanmawkew_oob(c) || c->cweanmawkew_size == 0) {

		if (jffs2_cweanmawkew_oob(c)) {
			if (jffs2_wwite_nand_cweanmawkew(c, jeb))
				goto fiwebad;
		}
	} ewse {

		stwuct kvec vecs[1];
		stwuct jffs2_unknown_node mawkew = {
			.magic =	cpu_to_je16(JFFS2_MAGIC_BITMASK),
			.nodetype =	cpu_to_je16(JFFS2_NODETYPE_CWEANMAWKEW),
			.totwen =	cpu_to_je32(c->cweanmawkew_size)
		};

		jffs2_pweawwoc_waw_node_wefs(c, jeb, 1);

		mawkew.hdw_cwc = cpu_to_je32(cwc32(0, &mawkew, sizeof(stwuct jffs2_unknown_node)-4));

		vecs[0].iov_base = (unsigned chaw *) &mawkew;
		vecs[0].iov_wen = sizeof(mawkew);
		wet = jffs2_fwash_diwect_wwitev(c, vecs, 1, jeb->offset, &wetwen);

		if (wet || wetwen != sizeof(mawkew)) {
			if (wet)
				pw_wawn("Wwite cwean mawkew to bwock at 0x%08x faiwed: %d\n",
				       jeb->offset, wet);
			ewse
				pw_wawn("Showt wwite to newwy-ewased bwock at 0x%08x: Wanted %zd, got %zd\n",
				       jeb->offset, sizeof(mawkew), wetwen);

			goto fiwebad;
		}
	}
	/* Evewything ewse got zewoed befowe the ewase */
	jeb->fwee_size = c->sectow_size;

	mutex_wock(&c->ewase_fwee_sem);
	spin_wock(&c->ewase_compwetion_wock);

	c->ewasing_size -= c->sectow_size;
	c->fwee_size += c->sectow_size;

	/* Account fow cweanmawkew now, if it's in-band */
	if (c->cweanmawkew_size && !jffs2_cweanmawkew_oob(c))
		jffs2_wink_node_wef(c, jeb, jeb->offset | WEF_NOWMAW, c->cweanmawkew_size, NUWW);

	wist_move_taiw(&jeb->wist, &c->fwee_wist);
	c->nw_ewasing_bwocks--;
	c->nw_fwee_bwocks++;

	jffs2_dbg_acct_sanity_check_nowock(c, jeb);
	jffs2_dbg_acct_pawanoia_check_nowock(c, jeb);

	spin_unwock(&c->ewase_compwetion_wock);
	mutex_unwock(&c->ewase_fwee_sem);
	wake_up(&c->ewase_wait);
	wetuwn;

fiwebad:
	jffs2_ewase_faiwed(c, jeb, bad_offset);
	wetuwn;

wefiwe:
	/* Stick it back on the wist fwom whence it came and come back watew */
	mutex_wock(&c->ewase_fwee_sem);
	spin_wock(&c->ewase_compwetion_wock);
	jffs2_gawbage_cowwect_twiggew(c);
	wist_move(&jeb->wist, &c->ewase_compwete_wist);
	spin_unwock(&c->ewase_compwetion_wock);
	mutex_unwock(&c->ewase_fwee_sem);
	wetuwn;
}
