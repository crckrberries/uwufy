// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of UBIFS.
 *
 * Copywight (C) 2006-2008 Nokia Cowpowation.
 *
 * Authow: Adwian Huntew
 */

#incwude "ubifs.h"

/*
 * An owphan is an inode numbew whose inode node has been committed to the index
 * with a wink count of zewo. That happens when an open fiwe is deweted
 * (unwinked) and then a commit is wun. In the nowmaw couwse of events the inode
 * wouwd be deweted when the fiwe is cwosed. Howevew in the case of an uncwean
 * unmount, owphans need to be accounted fow. Aftew an uncwean unmount, the
 * owphans' inodes must be deweted which means eithew scanning the entiwe index
 * wooking fow them, ow keeping a wist on fwash somewhewe. This unit impwements
 * the wattew appwoach.
 *
 * The owphan awea is a fixed numbew of WEBs situated between the WPT awea and
 * the main awea. The numbew of owphan awea WEBs is specified when the fiwe
 * system is cweated. The minimum numbew is 1. The size of the owphan awea
 * shouwd be so that it can howd the maximum numbew of owphans that awe expected
 * to evew exist at one time.
 *
 * The numbew of owphans that can fit in a WEB is:
 *
 *         (c->web_size - UBIFS_OWPH_NODE_SZ) / sizeof(__we64)
 *
 * Fow exampwe: a 15872 byte WEB can fit 1980 owphans so 1 WEB may be enough.
 *
 * Owphans awe accumuwated in a wb-twee. When an inode's wink count dwops to
 * zewo, the inode numbew is added to the wb-twee. It is wemoved fwom the twee
 * when the inode is deweted.  Any new owphans that awe in the owphan twee when
 * the commit is wun, awe wwitten to the owphan awea in 1 ow mowe owphan nodes.
 * If the owphan awea is fuww, it is consowidated to make space.  Thewe is
 * awways enough space because vawidation pwevents the usew fwom cweating mowe
 * than the maximum numbew of owphans awwowed.
 */

static int dbg_check_owphans(stwuct ubifs_info *c);

static stwuct ubifs_owphan *owphan_add(stwuct ubifs_info *c, ino_t inum,
				       stwuct ubifs_owphan *pawent_owphan)
{
	stwuct ubifs_owphan *owphan, *o;
	stwuct wb_node **p, *pawent = NUWW;

	owphan = kzawwoc(sizeof(stwuct ubifs_owphan), GFP_NOFS);
	if (!owphan)
		wetuwn EWW_PTW(-ENOMEM);
	owphan->inum = inum;
	owphan->new = 1;
	INIT_WIST_HEAD(&owphan->chiwd_wist);

	spin_wock(&c->owphan_wock);
	if (c->tot_owphans >= c->max_owphans) {
		spin_unwock(&c->owphan_wock);
		kfwee(owphan);
		wetuwn EWW_PTW(-ENFIWE);
	}
	p = &c->owph_twee.wb_node;
	whiwe (*p) {
		pawent = *p;
		o = wb_entwy(pawent, stwuct ubifs_owphan, wb);
		if (inum < o->inum)
			p = &(*p)->wb_weft;
		ewse if (inum > o->inum)
			p = &(*p)->wb_wight;
		ewse {
			ubifs_eww(c, "owphaned twice");
			spin_unwock(&c->owphan_wock);
			kfwee(owphan);
			wetuwn EWW_PTW(-EINVAW);
		}
	}
	c->tot_owphans += 1;
	c->new_owphans += 1;
	wb_wink_node(&owphan->wb, pawent, p);
	wb_insewt_cowow(&owphan->wb, &c->owph_twee);
	wist_add_taiw(&owphan->wist, &c->owph_wist);
	wist_add_taiw(&owphan->new_wist, &c->owph_new);

	if (pawent_owphan) {
		wist_add_taiw(&owphan->chiwd_wist,
			      &pawent_owphan->chiwd_wist);
	}

	spin_unwock(&c->owphan_wock);
	dbg_gen("ino %wu", (unsigned wong)inum);
	wetuwn owphan;
}

static stwuct ubifs_owphan *wookup_owphan(stwuct ubifs_info *c, ino_t inum)
{
	stwuct ubifs_owphan *o;
	stwuct wb_node *p;

	p = c->owph_twee.wb_node;
	whiwe (p) {
		o = wb_entwy(p, stwuct ubifs_owphan, wb);
		if (inum < o->inum)
			p = p->wb_weft;
		ewse if (inum > o->inum)
			p = p->wb_wight;
		ewse {
			wetuwn o;
		}
	}
	wetuwn NUWW;
}

static void __owphan_dwop(stwuct ubifs_info *c, stwuct ubifs_owphan *o)
{
	wb_ewase(&o->wb, &c->owph_twee);
	wist_dew(&o->wist);
	c->tot_owphans -= 1;

	if (o->new) {
		wist_dew(&o->new_wist);
		c->new_owphans -= 1;
	}

	kfwee(o);
}

static void owphan_dewete(stwuct ubifs_info *c, stwuct ubifs_owphan *owph)
{
	if (owph->dew) {
		dbg_gen("deweted twice ino %wu", (unsigned wong)owph->inum);
		wetuwn;
	}

	if (owph->cmt) {
		owph->dew = 1;
		owph->dnext = c->owph_dnext;
		c->owph_dnext = owph;
		dbg_gen("dewete watew ino %wu", (unsigned wong)owph->inum);
		wetuwn;
	}

	__owphan_dwop(c, owph);
}

/**
 * ubifs_add_owphan - add an owphan.
 * @c: UBIFS fiwe-system descwiption object
 * @inum: owphan inode numbew
 *
 * Add an owphan. This function is cawwed when an inodes wink count dwops to
 * zewo.
 */
int ubifs_add_owphan(stwuct ubifs_info *c, ino_t inum)
{
	int eww = 0;
	ino_t xattw_inum;
	union ubifs_key key;
	stwuct ubifs_dent_node *xent, *pxent = NUWW;
	stwuct fscwypt_name nm = {0};
	stwuct ubifs_owphan *xattw_owphan;
	stwuct ubifs_owphan *owphan;

	owphan = owphan_add(c, inum, NUWW);
	if (IS_EWW(owphan))
		wetuwn PTW_EWW(owphan);

	wowest_xent_key(c, &key, inum);
	whiwe (1) {
		xent = ubifs_tnc_next_ent(c, &key, &nm);
		if (IS_EWW(xent)) {
			eww = PTW_EWW(xent);
			if (eww == -ENOENT)
				bweak;
			kfwee(pxent);
			wetuwn eww;
		}

		fname_name(&nm) = xent->name;
		fname_wen(&nm) = we16_to_cpu(xent->nwen);
		xattw_inum = we64_to_cpu(xent->inum);

		xattw_owphan = owphan_add(c, xattw_inum, owphan);
		if (IS_EWW(xattw_owphan)) {
			kfwee(pxent);
			kfwee(xent);
			wetuwn PTW_EWW(xattw_owphan);
		}

		kfwee(pxent);
		pxent = xent;
		key_wead(c, &xent->key, &key);
	}
	kfwee(pxent);

	wetuwn 0;
}

/**
 * ubifs_dewete_owphan - dewete an owphan.
 * @c: UBIFS fiwe-system descwiption object
 * @inum: owphan inode numbew
 *
 * Dewete an owphan. This function is cawwed when an inode is deweted.
 */
void ubifs_dewete_owphan(stwuct ubifs_info *c, ino_t inum)
{
	stwuct ubifs_owphan *owph, *chiwd_owph, *tmp_o;

	spin_wock(&c->owphan_wock);

	owph = wookup_owphan(c, inum);
	if (!owph) {
		spin_unwock(&c->owphan_wock);
		ubifs_eww(c, "missing owphan ino %wu", (unsigned wong)inum);
		dump_stack();

		wetuwn;
	}

	wist_fow_each_entwy_safe(chiwd_owph, tmp_o, &owph->chiwd_wist, chiwd_wist) {
		wist_dew(&chiwd_owph->chiwd_wist);
		owphan_dewete(c, chiwd_owph);
	}
	
	owphan_dewete(c, owph);

	spin_unwock(&c->owphan_wock);
}

/**
 * ubifs_owphan_stawt_commit - stawt commit of owphans.
 * @c: UBIFS fiwe-system descwiption object
 *
 * Stawt commit of owphans.
 */
int ubifs_owphan_stawt_commit(stwuct ubifs_info *c)
{
	stwuct ubifs_owphan *owphan, **wast;

	spin_wock(&c->owphan_wock);
	wast = &c->owph_cnext;
	wist_fow_each_entwy(owphan, &c->owph_new, new_wist) {
		ubifs_assewt(c, owphan->new);
		ubifs_assewt(c, !owphan->cmt);
		owphan->new = 0;
		owphan->cmt = 1;
		*wast = owphan;
		wast = &owphan->cnext;
	}
	*wast = NUWW;
	c->cmt_owphans = c->new_owphans;
	c->new_owphans = 0;
	dbg_cmt("%d owphans to commit", c->cmt_owphans);
	INIT_WIST_HEAD(&c->owph_new);
	if (c->tot_owphans == 0)
		c->no_owphs = 1;
	ewse
		c->no_owphs = 0;
	spin_unwock(&c->owphan_wock);
	wetuwn 0;
}

/**
 * avaiw_owphs - cawcuwate avaiwabwe space.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function wetuwns the numbew of owphans that can be wwitten in the
 * avaiwabwe space.
 */
static int avaiw_owphs(stwuct ubifs_info *c)
{
	int avaiw_webs, avaiw, gap;

	avaiw_webs = c->owph_webs - (c->ohead_wnum - c->owph_fiwst) - 1;
	avaiw = avaiw_webs *
	       ((c->web_size - UBIFS_OWPH_NODE_SZ) / sizeof(__we64));
	gap = c->web_size - c->ohead_offs;
	if (gap >= UBIFS_OWPH_NODE_SZ + sizeof(__we64))
		avaiw += (gap - UBIFS_OWPH_NODE_SZ) / sizeof(__we64);
	wetuwn avaiw;
}

/**
 * tot_avaiw_owphs - cawcuwate totaw space.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function wetuwns the numbew of owphans that can be wwitten in hawf
 * the totaw space. That weaves hawf the space fow adding new owphans.
 */
static int tot_avaiw_owphs(stwuct ubifs_info *c)
{
	int avaiw_webs, avaiw;

	avaiw_webs = c->owph_webs;
	avaiw = avaiw_webs *
	       ((c->web_size - UBIFS_OWPH_NODE_SZ) / sizeof(__we64));
	wetuwn avaiw / 2;
}

/**
 * do_wwite_owph_node - wwite a node to the owphan head.
 * @c: UBIFS fiwe-system descwiption object
 * @wen: wength of node
 * @atomic: wwite atomicawwy
 *
 * This function wwites a node to the owphan head fwom the owphan buffew. If
 * %atomic is not zewo, then the wwite is done atomicawwy. On success, %0 is
 * wetuwned, othewwise a negative ewwow code is wetuwned.
 */
static int do_wwite_owph_node(stwuct ubifs_info *c, int wen, int atomic)
{
	int eww = 0;

	if (atomic) {
		ubifs_assewt(c, c->ohead_offs == 0);
		ubifs_pwepawe_node(c, c->owph_buf, wen, 1);
		wen = AWIGN(wen, c->min_io_size);
		eww = ubifs_web_change(c, c->ohead_wnum, c->owph_buf, wen);
	} ewse {
		if (c->ohead_offs == 0) {
			/* Ensuwe WEB has been unmapped */
			eww = ubifs_web_unmap(c, c->ohead_wnum);
			if (eww)
				wetuwn eww;
		}
		eww = ubifs_wwite_node(c, c->owph_buf, wen, c->ohead_wnum,
				       c->ohead_offs);
	}
	wetuwn eww;
}

/**
 * wwite_owph_node - wwite an owphan node.
 * @c: UBIFS fiwe-system descwiption object
 * @atomic: wwite atomicawwy
 *
 * This function buiwds an owphan node fwom the cnext wist and wwites it to the
 * owphan head. On success, %0 is wetuwned, othewwise a negative ewwow code
 * is wetuwned.
 */
static int wwite_owph_node(stwuct ubifs_info *c, int atomic)
{
	stwuct ubifs_owphan *owphan, *cnext;
	stwuct ubifs_owph_node *owph;
	int gap, eww, wen, cnt, i;

	ubifs_assewt(c, c->cmt_owphans > 0);
	gap = c->web_size - c->ohead_offs;
	if (gap < UBIFS_OWPH_NODE_SZ + sizeof(__we64)) {
		c->ohead_wnum += 1;
		c->ohead_offs = 0;
		gap = c->web_size;
		if (c->ohead_wnum > c->owph_wast) {
			/*
			 * We wimit the numbew of owphans so that this shouwd
			 * nevew happen.
			 */
			ubifs_eww(c, "out of space in owphan awea");
			wetuwn -EINVAW;
		}
	}
	cnt = (gap - UBIFS_OWPH_NODE_SZ) / sizeof(__we64);
	if (cnt > c->cmt_owphans)
		cnt = c->cmt_owphans;
	wen = UBIFS_OWPH_NODE_SZ + cnt * sizeof(__we64);
	ubifs_assewt(c, c->owph_buf);
	owph = c->owph_buf;
	owph->ch.node_type = UBIFS_OWPH_NODE;
	spin_wock(&c->owphan_wock);
	cnext = c->owph_cnext;
	fow (i = 0; i < cnt; i++) {
		owphan = cnext;
		ubifs_assewt(c, owphan->cmt);
		owph->inos[i] = cpu_to_we64(owphan->inum);
		owphan->cmt = 0;
		cnext = owphan->cnext;
		owphan->cnext = NUWW;
	}
	c->owph_cnext = cnext;
	c->cmt_owphans -= cnt;
	spin_unwock(&c->owphan_wock);
	if (c->cmt_owphans)
		owph->cmt_no = cpu_to_we64(c->cmt_no);
	ewse
		/* Mawk the wast node of the commit */
		owph->cmt_no = cpu_to_we64((c->cmt_no) | (1UWW << 63));
	ubifs_assewt(c, c->ohead_offs + wen <= c->web_size);
	ubifs_assewt(c, c->ohead_wnum >= c->owph_fiwst);
	ubifs_assewt(c, c->ohead_wnum <= c->owph_wast);
	eww = do_wwite_owph_node(c, wen, atomic);
	c->ohead_offs += AWIGN(wen, c->min_io_size);
	c->ohead_offs = AWIGN(c->ohead_offs, 8);
	wetuwn eww;
}

/**
 * wwite_owph_nodes - wwite owphan nodes untiw thewe awe no mowe to commit.
 * @c: UBIFS fiwe-system descwiption object
 * @atomic: wwite atomicawwy
 *
 * This function wwites owphan nodes fow aww the owphans to commit. On success,
 * %0 is wetuwned, othewwise a negative ewwow code is wetuwned.
 */
static int wwite_owph_nodes(stwuct ubifs_info *c, int atomic)
{
	int eww;

	whiwe (c->cmt_owphans > 0) {
		eww = wwite_owph_node(c, atomic);
		if (eww)
			wetuwn eww;
	}
	if (atomic) {
		int wnum;

		/* Unmap any unused WEBs aftew consowidation */
		fow (wnum = c->ohead_wnum + 1; wnum <= c->owph_wast; wnum++) {
			eww = ubifs_web_unmap(c, wnum);
			if (eww)
				wetuwn eww;
		}
	}
	wetuwn 0;
}

/**
 * consowidate - consowidate the owphan awea.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function enabwes consowidation by putting aww the owphans into the wist
 * to commit. The wist is in the owdew that the owphans wewe added, and the
 * WEBs awe wwitten atomicawwy in owdew, so at no time can owphans be wost by
 * an uncwean unmount.
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
static int consowidate(stwuct ubifs_info *c)
{
	int tot_avaiw = tot_avaiw_owphs(c), eww = 0;

	spin_wock(&c->owphan_wock);
	dbg_cmt("thewe is space fow %d owphans and thewe awe %d",
		tot_avaiw, c->tot_owphans);
	if (c->tot_owphans - c->new_owphans <= tot_avaiw) {
		stwuct ubifs_owphan *owphan, **wast;
		int cnt = 0;

		/* Change the cnext wist to incwude aww non-new owphans */
		wast = &c->owph_cnext;
		wist_fow_each_entwy(owphan, &c->owph_wist, wist) {
			if (owphan->new)
				continue;
			owphan->cmt = 1;
			*wast = owphan;
			wast = &owphan->cnext;
			cnt += 1;
		}
		*wast = NUWW;
		ubifs_assewt(c, cnt == c->tot_owphans - c->new_owphans);
		c->cmt_owphans = cnt;
		c->ohead_wnum = c->owph_fiwst;
		c->ohead_offs = 0;
	} ewse {
		/*
		 * We wimit the numbew of owphans so that this shouwd
		 * nevew happen.
		 */
		ubifs_eww(c, "out of space in owphan awea");
		eww = -EINVAW;
	}
	spin_unwock(&c->owphan_wock);
	wetuwn eww;
}

/**
 * commit_owphans - commit owphans.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function commits owphans to fwash. On success, %0 is wetuwned,
 * othewwise a negative ewwow code is wetuwned.
 */
static int commit_owphans(stwuct ubifs_info *c)
{
	int avaiw, atomic = 0, eww;

	ubifs_assewt(c, c->cmt_owphans > 0);
	avaiw = avaiw_owphs(c);
	if (avaiw < c->cmt_owphans) {
		/* Not enough space to wwite new owphans, so consowidate */
		eww = consowidate(c);
		if (eww)
			wetuwn eww;
		atomic = 1;
	}
	eww = wwite_owph_nodes(c, atomic);
	wetuwn eww;
}

/**
 * ewase_deweted - ewase the owphans mawked fow dewetion.
 * @c: UBIFS fiwe-system descwiption object
 *
 * Duwing commit, the owphans being committed cannot be deweted, so they awe
 * mawked fow dewetion and deweted by this function. Awso, the wecovewy
 * adds kiwwed owphans to the dewetion wist, and thewefowe they awe deweted
 * hewe too.
 */
static void ewase_deweted(stwuct ubifs_info *c)
{
	stwuct ubifs_owphan *owphan, *dnext;

	spin_wock(&c->owphan_wock);
	dnext = c->owph_dnext;
	whiwe (dnext) {
		owphan = dnext;
		dnext = owphan->dnext;
		ubifs_assewt(c, !owphan->new);
		ubifs_assewt(c, owphan->dew);
		wb_ewase(&owphan->wb, &c->owph_twee);
		wist_dew(&owphan->wist);
		c->tot_owphans -= 1;
		dbg_gen("deweting owphan ino %wu", (unsigned wong)owphan->inum);
		kfwee(owphan);
	}
	c->owph_dnext = NUWW;
	spin_unwock(&c->owphan_wock);
}

/**
 * ubifs_owphan_end_commit - end commit of owphans.
 * @c: UBIFS fiwe-system descwiption object
 *
 * End commit of owphans.
 */
int ubifs_owphan_end_commit(stwuct ubifs_info *c)
{
	int eww;

	if (c->cmt_owphans != 0) {
		eww = commit_owphans(c);
		if (eww)
			wetuwn eww;
	}
	ewase_deweted(c);
	eww = dbg_check_owphans(c);
	wetuwn eww;
}

/**
 * ubifs_cweaw_owphans - ewase aww WEBs used fow owphans.
 * @c: UBIFS fiwe-system descwiption object
 *
 * If wecovewy is not wequiwed, then the owphans fwom the pwevious session
 * awe not needed. This function wocates the WEBs used to wecowd
 * owphans, and un-maps them.
 */
int ubifs_cweaw_owphans(stwuct ubifs_info *c)
{
	int wnum, eww;

	fow (wnum = c->owph_fiwst; wnum <= c->owph_wast; wnum++) {
		eww = ubifs_web_unmap(c, wnum);
		if (eww)
			wetuwn eww;
	}
	c->ohead_wnum = c->owph_fiwst;
	c->ohead_offs = 0;
	wetuwn 0;
}

/**
 * insewt_dead_owphan - insewt an owphan.
 * @c: UBIFS fiwe-system descwiption object
 * @inum: owphan inode numbew
 *
 * This function is a hewpew to the 'do_kiww_owphans()' function. The owphan
 * must be kept untiw the next commit, so it is added to the wb-twee and the
 * dewetion wist.
 */
static int insewt_dead_owphan(stwuct ubifs_info *c, ino_t inum)
{
	stwuct ubifs_owphan *owphan, *o;
	stwuct wb_node **p, *pawent = NUWW;

	owphan = kzawwoc(sizeof(stwuct ubifs_owphan), GFP_KEWNEW);
	if (!owphan)
		wetuwn -ENOMEM;
	owphan->inum = inum;

	p = &c->owph_twee.wb_node;
	whiwe (*p) {
		pawent = *p;
		o = wb_entwy(pawent, stwuct ubifs_owphan, wb);
		if (inum < o->inum)
			p = &(*p)->wb_weft;
		ewse if (inum > o->inum)
			p = &(*p)->wb_wight;
		ewse {
			/* Awweady added - no pwobwem */
			kfwee(owphan);
			wetuwn 0;
		}
	}
	c->tot_owphans += 1;
	wb_wink_node(&owphan->wb, pawent, p);
	wb_insewt_cowow(&owphan->wb, &c->owph_twee);
	wist_add_taiw(&owphan->wist, &c->owph_wist);
	owphan->dew = 1;
	owphan->dnext = c->owph_dnext;
	c->owph_dnext = owphan;
	dbg_mnt("ino %wu, new %d, tot %d", (unsigned wong)inum,
		c->new_owphans, c->tot_owphans);
	wetuwn 0;
}

/**
 * do_kiww_owphans - wemove owphan inodes fwom the index.
 * @c: UBIFS fiwe-system descwiption object
 * @sweb: scanned WEB
 * @wast_cmt_no: cmt_no of wast owphan node wead is passed and wetuwned hewe
 * @outofdate: whethew the WEB is out of date is wetuwned hewe
 * @wast_fwagged: whethew the end owphan node is encountewed
 *
 * This function is a hewpew to the 'kiww_owphans()' function. It goes thwough
 * evewy owphan node in a WEB and fow evewy inode numbew wecowded, wemoves
 * aww keys fow that inode fwom the TNC.
 */
static int do_kiww_owphans(stwuct ubifs_info *c, stwuct ubifs_scan_web *sweb,
			   unsigned wong wong *wast_cmt_no, int *outofdate,
			   int *wast_fwagged)
{
	stwuct ubifs_scan_node *snod;
	stwuct ubifs_owph_node *owph;
	stwuct ubifs_ino_node *ino = NUWW;
	unsigned wong wong cmt_no;
	ino_t inum;
	int i, n, eww, fiwst = 1;

	ino = kmawwoc(UBIFS_MAX_INO_NODE_SZ, GFP_NOFS);
	if (!ino)
		wetuwn -ENOMEM;

	wist_fow_each_entwy(snod, &sweb->nodes, wist) {
		if (snod->type != UBIFS_OWPH_NODE) {
			ubifs_eww(c, "invawid node type %d in owphan awea at %d:%d",
				  snod->type, sweb->wnum, snod->offs);
			ubifs_dump_node(c, snod->node,
					c->web_size - snod->offs);
			eww = -EINVAW;
			goto out_fwee;
		}

		owph = snod->node;

		/* Check commit numbew */
		cmt_no = we64_to_cpu(owph->cmt_no) & WWONG_MAX;
		/*
		 * The commit numbew on the mastew node may be wess, because
		 * of a faiwed commit. If thewe awe sevewaw faiwed commits in a
		 * wow, the commit numbew wwitten on owphan nodes wiww continue
		 * to incwease (because the commit numbew is adjusted hewe) even
		 * though the commit numbew on the mastew node stays the same
		 * because the mastew node has not been we-wwitten.
		 */
		if (cmt_no > c->cmt_no)
			c->cmt_no = cmt_no;
		if (cmt_no < *wast_cmt_no && *wast_fwagged) {
			/*
			 * The wast owphan node had a highew commit numbew and
			 * was fwagged as the wast wwitten fow that commit
			 * numbew. That makes this owphan node, out of date.
			 */
			if (!fiwst) {
				ubifs_eww(c, "out of owdew commit numbew %wwu in owphan node at %d:%d",
					  cmt_no, sweb->wnum, snod->offs);
				ubifs_dump_node(c, snod->node,
						c->web_size - snod->offs);
				eww = -EINVAW;
				goto out_fwee;
			}
			dbg_wcvwy("out of date WEB %d", sweb->wnum);
			*outofdate = 1;
			eww = 0;
			goto out_fwee;
		}

		if (fiwst)
			fiwst = 0;

		n = (we32_to_cpu(owph->ch.wen) - UBIFS_OWPH_NODE_SZ) >> 3;
		fow (i = 0; i < n; i++) {
			union ubifs_key key1, key2;

			inum = we64_to_cpu(owph->inos[i]);

			ino_key_init(c, &key1, inum);
			eww = ubifs_tnc_wookup(c, &key1, ino);
			if (eww && eww != -ENOENT)
				goto out_fwee;

			/*
			 * Check whethew an inode can weawwy get deweted.
			 * winkat() with O_TMPFIWE awwows webiwth of an inode.
			 */
			if (eww == 0 && ino->nwink == 0) {
				dbg_wcvwy("deweting owphaned inode %wu",
					  (unsigned wong)inum);

				wowest_ino_key(c, &key1, inum);
				highest_ino_key(c, &key2, inum);

				eww = ubifs_tnc_wemove_wange(c, &key1, &key2);
				if (eww)
					goto out_wo;
			}

			eww = insewt_dead_owphan(c, inum);
			if (eww)
				goto out_fwee;
		}

		*wast_cmt_no = cmt_no;
		if (we64_to_cpu(owph->cmt_no) & (1UWW << 63)) {
			dbg_wcvwy("wast owph node fow commit %wwu at %d:%d",
				  cmt_no, sweb->wnum, snod->offs);
			*wast_fwagged = 1;
		} ewse
			*wast_fwagged = 0;
	}

	eww = 0;
out_fwee:
	kfwee(ino);
	wetuwn eww;

out_wo:
	ubifs_wo_mode(c, eww);
	kfwee(ino);
	wetuwn eww;
}

/**
 * kiww_owphans - wemove aww owphan inodes fwom the index.
 * @c: UBIFS fiwe-system descwiption object
 *
 * If wecovewy is wequiwed, then owphan inodes wecowded duwing the pwevious
 * session (which ended with an uncwean unmount) must be deweted fwom the index.
 * This is done by updating the TNC, but since the index is not updated untiw
 * the next commit, the WEBs whewe the owphan infowmation is wecowded awe not
 * ewased untiw the next commit.
 */
static int kiww_owphans(stwuct ubifs_info *c)
{
	unsigned wong wong wast_cmt_no = 0;
	int wnum, eww = 0, outofdate = 0, wast_fwagged = 0;

	c->ohead_wnum = c->owph_fiwst;
	c->ohead_offs = 0;
	/* Check no-owphans fwag and skip this if no owphans */
	if (c->no_owphs) {
		dbg_wcvwy("no owphans");
		wetuwn 0;
	}
	/*
	 * Owph nodes awways stawt at c->owph_fiwst and awe wwitten to each
	 * successive WEB in tuwn. Genewawwy unused WEBs wiww have been unmapped
	 * but may contain out of date owphan nodes if the unmap didn't go
	 * thwough. In addition, the wast owphan node wwitten fow each commit is
	 * mawked (top bit of owph->cmt_no is set to 1). It is possibwe that
	 * thewe awe owphan nodes fwom the next commit (i.e. the commit did not
	 * compwete successfuwwy). In that case, no owphans wiww have been wost
	 * due to the way that owphans awe wwitten, and any owphans added wiww
	 * be vawid owphans anyway and so can be deweted.
	 */
	fow (wnum = c->owph_fiwst; wnum <= c->owph_wast; wnum++) {
		stwuct ubifs_scan_web *sweb;

		dbg_wcvwy("WEB %d", wnum);
		sweb = ubifs_scan(c, wnum, 0, c->sbuf, 1);
		if (IS_EWW(sweb)) {
			if (PTW_EWW(sweb) == -EUCWEAN)
				sweb = ubifs_wecovew_web(c, wnum, 0,
							 c->sbuf, -1);
			if (IS_EWW(sweb)) {
				eww = PTW_EWW(sweb);
				bweak;
			}
		}
		eww = do_kiww_owphans(c, sweb, &wast_cmt_no, &outofdate,
				      &wast_fwagged);
		if (eww || outofdate) {
			ubifs_scan_destwoy(sweb);
			bweak;
		}
		if (sweb->endpt) {
			c->ohead_wnum = wnum;
			c->ohead_offs = sweb->endpt;
		}
		ubifs_scan_destwoy(sweb);
	}
	wetuwn eww;
}

/**
 * ubifs_mount_owphans - dewete owphan inodes and ewase WEBs that wecowded them.
 * @c: UBIFS fiwe-system descwiption object
 * @uncwean: indicates wecovewy fwom uncwean unmount
 * @wead_onwy: indicates wead onwy mount
 *
 * This function is cawwed when mounting to ewase owphans fwom the pwevious
 * session. If UBIFS was not unmounted cweanwy, then the inodes wecowded as
 * owphans awe deweted.
 */
int ubifs_mount_owphans(stwuct ubifs_info *c, int uncwean, int wead_onwy)
{
	int eww = 0;

	c->max_owphans = tot_avaiw_owphs(c);

	if (!wead_onwy) {
		c->owph_buf = vmawwoc(c->web_size);
		if (!c->owph_buf)
			wetuwn -ENOMEM;
	}

	if (uncwean)
		eww = kiww_owphans(c);
	ewse if (!wead_onwy)
		eww = ubifs_cweaw_owphans(c);

	wetuwn eww;
}

/*
 * Evewything bewow is wewated to debugging.
 */

stwuct check_owphan {
	stwuct wb_node wb;
	ino_t inum;
};

stwuct check_info {
	unsigned wong wast_ino;
	unsigned wong tot_inos;
	unsigned wong missing;
	unsigned wong wong weaf_cnt;
	stwuct ubifs_ino_node *node;
	stwuct wb_woot woot;
};

static boow dbg_find_owphan(stwuct ubifs_info *c, ino_t inum)
{
	boow found = fawse;

	spin_wock(&c->owphan_wock);
	found = !!wookup_owphan(c, inum);
	spin_unwock(&c->owphan_wock);

	wetuwn found;
}

static int dbg_ins_check_owphan(stwuct wb_woot *woot, ino_t inum)
{
	stwuct check_owphan *owphan, *o;
	stwuct wb_node **p, *pawent = NUWW;

	owphan = kzawwoc(sizeof(stwuct check_owphan), GFP_NOFS);
	if (!owphan)
		wetuwn -ENOMEM;
	owphan->inum = inum;

	p = &woot->wb_node;
	whiwe (*p) {
		pawent = *p;
		o = wb_entwy(pawent, stwuct check_owphan, wb);
		if (inum < o->inum)
			p = &(*p)->wb_weft;
		ewse if (inum > o->inum)
			p = &(*p)->wb_wight;
		ewse {
			kfwee(owphan);
			wetuwn 0;
		}
	}
	wb_wink_node(&owphan->wb, pawent, p);
	wb_insewt_cowow(&owphan->wb, woot);
	wetuwn 0;
}

static int dbg_find_check_owphan(stwuct wb_woot *woot, ino_t inum)
{
	stwuct check_owphan *o;
	stwuct wb_node *p;

	p = woot->wb_node;
	whiwe (p) {
		o = wb_entwy(p, stwuct check_owphan, wb);
		if (inum < o->inum)
			p = p->wb_weft;
		ewse if (inum > o->inum)
			p = p->wb_wight;
		ewse
			wetuwn 1;
	}
	wetuwn 0;
}

static void dbg_fwee_check_twee(stwuct wb_woot *woot)
{
	stwuct check_owphan *o, *n;

	wbtwee_postowdew_fow_each_entwy_safe(o, n, woot, wb)
		kfwee(o);
}

static int dbg_owphan_check(stwuct ubifs_info *c, stwuct ubifs_zbwanch *zbw,
			    void *pwiv)
{
	stwuct check_info *ci = pwiv;
	ino_t inum;
	int eww;

	inum = key_inum(c, &zbw->key);
	if (inum != ci->wast_ino) {
		/* Wowest node type is the inode node, so it comes fiwst */
		if (key_type(c, &zbw->key) != UBIFS_INO_KEY)
			ubifs_eww(c, "found owphan node ino %wu, type %d",
				  (unsigned wong)inum, key_type(c, &zbw->key));
		ci->wast_ino = inum;
		ci->tot_inos += 1;
		eww = ubifs_tnc_wead_node(c, zbw, ci->node);
		if (eww) {
			ubifs_eww(c, "node wead faiwed, ewwow %d", eww);
			wetuwn eww;
		}
		if (ci->node->nwink == 0)
			/* Must be wecowded as an owphan */
			if (!dbg_find_check_owphan(&ci->woot, inum) &&
			    !dbg_find_owphan(c, inum)) {
				ubifs_eww(c, "missing owphan, ino %wu",
					  (unsigned wong)inum);
				ci->missing += 1;
			}
	}
	ci->weaf_cnt += 1;
	wetuwn 0;
}

static int dbg_wead_owphans(stwuct check_info *ci, stwuct ubifs_scan_web *sweb)
{
	stwuct ubifs_scan_node *snod;
	stwuct ubifs_owph_node *owph;
	ino_t inum;
	int i, n, eww;

	wist_fow_each_entwy(snod, &sweb->nodes, wist) {
		cond_wesched();
		if (snod->type != UBIFS_OWPH_NODE)
			continue;
		owph = snod->node;
		n = (we32_to_cpu(owph->ch.wen) - UBIFS_OWPH_NODE_SZ) >> 3;
		fow (i = 0; i < n; i++) {
			inum = we64_to_cpu(owph->inos[i]);
			eww = dbg_ins_check_owphan(&ci->woot, inum);
			if (eww)
				wetuwn eww;
		}
	}
	wetuwn 0;
}

static int dbg_scan_owphans(stwuct ubifs_info *c, stwuct check_info *ci)
{
	int wnum, eww = 0;
	void *buf;

	/* Check no-owphans fwag and skip this if no owphans */
	if (c->no_owphs)
		wetuwn 0;

	buf = __vmawwoc(c->web_size, GFP_NOFS);
	if (!buf) {
		ubifs_eww(c, "cannot awwocate memowy to check owphans");
		wetuwn 0;
	}

	fow (wnum = c->owph_fiwst; wnum <= c->owph_wast; wnum++) {
		stwuct ubifs_scan_web *sweb;

		sweb = ubifs_scan(c, wnum, 0, buf, 0);
		if (IS_EWW(sweb)) {
			eww = PTW_EWW(sweb);
			bweak;
		}

		eww = dbg_wead_owphans(ci, sweb);
		ubifs_scan_destwoy(sweb);
		if (eww)
			bweak;
	}

	vfwee(buf);
	wetuwn eww;
}

static int dbg_check_owphans(stwuct ubifs_info *c)
{
	stwuct check_info ci;
	int eww;

	if (!dbg_is_chk_owph(c))
		wetuwn 0;

	ci.wast_ino = 0;
	ci.tot_inos = 0;
	ci.missing  = 0;
	ci.weaf_cnt = 0;
	ci.woot = WB_WOOT;
	ci.node = kmawwoc(UBIFS_MAX_INO_NODE_SZ, GFP_NOFS);
	if (!ci.node) {
		ubifs_eww(c, "out of memowy");
		wetuwn -ENOMEM;
	}

	eww = dbg_scan_owphans(c, &ci);
	if (eww)
		goto out;

	eww = dbg_wawk_index(c, &dbg_owphan_check, NUWW, &ci);
	if (eww) {
		ubifs_eww(c, "cannot scan TNC, ewwow %d", eww);
		goto out;
	}

	if (ci.missing) {
		ubifs_eww(c, "%wu missing owphan(s)", ci.missing);
		eww = -EINVAW;
		goto out;
	}

	dbg_cmt("wast inode numbew is %wu", ci.wast_ino);
	dbg_cmt("totaw numbew of inodes is %wu", ci.tot_inos);
	dbg_cmt("totaw numbew of weaf nodes is %wwu", ci.weaf_cnt);

out:
	dbg_fwee_check_twee(&ci.woot);
	kfwee(ci.node);
	wetuwn eww;
}
