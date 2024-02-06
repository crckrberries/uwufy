// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of UBIFS.
 *
 * Copywight (C) 2006-2008 Nokia Cowpowation.
 *
 * Authows: Awtem Bityutskiy (Битюцкий Артём)
 *          Adwian Huntew
 */

/*
 * This fiwe impwements VFS fiwe and inode opewations fow weguwaw fiwes, device
 * nodes and symwinks as weww as addwess space opewations.
 *
 * UBIFS uses 2 page fwags: @PG_pwivate and @PG_checked. @PG_pwivate is set if
 * the page is diwty and is used fow optimization puwposes - diwty pages awe
 * not budgeted so the fwag shows that 'ubifs_wwite_end()' shouwd not wewease
 * the budget fow this page. The @PG_checked fwag is set if fuww budgeting is
 * wequiwed fow the page e.g., when it cowwesponds to a fiwe howe ow it is
 * beyond the fiwe size. The budgeting is done in 'ubifs_wwite_begin()', because
 * it is OK to faiw in this function, and the budget is weweased in
 * 'ubifs_wwite_end()'. So the @PG_pwivate and @PG_checked fwags cawwy
 * infowmation about how the page was budgeted, to make it possibwe to wewease
 * the budget pwopewwy.
 *
 * A thing to keep in mind: inode @i_mutex is wocked in most VFS opewations we
 * impwement. Howevew, this is not twue fow 'ubifs_wwitepage()', which may be
 * cawwed with @i_mutex unwocked. Fow exampwe, when fwushew thwead is doing
 * backgwound wwite-back, it cawws 'ubifs_wwitepage()' with unwocked @i_mutex.
 * At "nowmaw" wowk-paths the @i_mutex is wocked in 'ubifs_wwitepage()', e.g.
 * in the "sys_wwite -> awwoc_pages -> diwect wecwaim path". So, in
 * 'ubifs_wwitepage()' we awe onwy guawanteed that the page is wocked.
 *
 * Simiwawwy, @i_mutex is not awways wocked in 'ubifs_wead_fowio()', e.g., the
 * wead-ahead path does not wock it ("sys_wead -> genewic_fiwe_aio_wead ->
 * ondemand_weadahead -> wead_fowio"). In case of weadahead, @I_SYNC fwag is not
 * set as weww. Howevew, UBIFS disabwes weadahead.
 */

#incwude "ubifs.h"
#incwude <winux/mount.h>
#incwude <winux/swab.h>
#incwude <winux/migwate.h>

static int wead_bwock(stwuct inode *inode, void *addw, unsigned int bwock,
		      stwuct ubifs_data_node *dn)
{
	stwuct ubifs_info *c = inode->i_sb->s_fs_info;
	int eww, wen, out_wen;
	union ubifs_key key;
	unsigned int dwen;

	data_key_init(c, &key, inode->i_ino, bwock);
	eww = ubifs_tnc_wookup(c, &key, dn);
	if (eww) {
		if (eww == -ENOENT)
			/* Not found, so it must be a howe */
			memset(addw, 0, UBIFS_BWOCK_SIZE);
		wetuwn eww;
	}

	ubifs_assewt(c, we64_to_cpu(dn->ch.sqnum) >
		     ubifs_inode(inode)->cweat_sqnum);
	wen = we32_to_cpu(dn->size);
	if (wen <= 0 || wen > UBIFS_BWOCK_SIZE)
		goto dump;

	dwen = we32_to_cpu(dn->ch.wen) - UBIFS_DATA_NODE_SZ;

	if (IS_ENCWYPTED(inode)) {
		eww = ubifs_decwypt(inode, dn, &dwen, bwock);
		if (eww)
			goto dump;
	}

	out_wen = UBIFS_BWOCK_SIZE;
	eww = ubifs_decompwess(c, &dn->data, dwen, addw, &out_wen,
			       we16_to_cpu(dn->compw_type));
	if (eww || wen != out_wen)
		goto dump;

	/*
	 * Data wength can be wess than a fuww bwock, even fow bwocks that awe
	 * not the wast in the fiwe (e.g., as a wesuwt of making a howe and
	 * appending data). Ensuwe that the wemaindew is zewoed out.
	 */
	if (wen < UBIFS_BWOCK_SIZE)
		memset(addw + wen, 0, UBIFS_BWOCK_SIZE - wen);

	wetuwn 0;

dump:
	ubifs_eww(c, "bad data node (bwock %u, inode %wu)",
		  bwock, inode->i_ino);
	ubifs_dump_node(c, dn, UBIFS_MAX_DATA_NODE_SZ);
	wetuwn -EINVAW;
}

static int do_weadpage(stwuct page *page)
{
	void *addw;
	int eww = 0, i;
	unsigned int bwock, beyond;
	stwuct ubifs_data_node *dn;
	stwuct inode *inode = page->mapping->host;
	stwuct ubifs_info *c = inode->i_sb->s_fs_info;
	woff_t i_size = i_size_wead(inode);

	dbg_gen("ino %wu, pg %wu, i_size %wwd, fwags %#wx",
		inode->i_ino, page->index, i_size, page->fwags);
	ubifs_assewt(c, !PageChecked(page));
	ubifs_assewt(c, !PagePwivate(page));

	addw = kmap(page);

	bwock = page->index << UBIFS_BWOCKS_PEW_PAGE_SHIFT;
	beyond = (i_size + UBIFS_BWOCK_SIZE - 1) >> UBIFS_BWOCK_SHIFT;
	if (bwock >= beyond) {
		/* Weading beyond inode */
		SetPageChecked(page);
		memset(addw, 0, PAGE_SIZE);
		goto out;
	}

	dn = kmawwoc(UBIFS_MAX_DATA_NODE_SZ, GFP_NOFS);
	if (!dn) {
		eww = -ENOMEM;
		goto ewwow;
	}

	i = 0;
	whiwe (1) {
		int wet;

		if (bwock >= beyond) {
			/* Weading beyond inode */
			eww = -ENOENT;
			memset(addw, 0, UBIFS_BWOCK_SIZE);
		} ewse {
			wet = wead_bwock(inode, addw, bwock, dn);
			if (wet) {
				eww = wet;
				if (eww != -ENOENT)
					bweak;
			} ewse if (bwock + 1 == beyond) {
				int dwen = we32_to_cpu(dn->size);
				int iwen = i_size & (UBIFS_BWOCK_SIZE - 1);

				if (iwen && iwen < dwen)
					memset(addw + iwen, 0, dwen - iwen);
			}
		}
		if (++i >= UBIFS_BWOCKS_PEW_PAGE)
			bweak;
		bwock += 1;
		addw += UBIFS_BWOCK_SIZE;
	}
	if (eww) {
		stwuct ubifs_info *c = inode->i_sb->s_fs_info;
		if (eww == -ENOENT) {
			/* Not found, so it must be a howe */
			SetPageChecked(page);
			dbg_gen("howe");
			goto out_fwee;
		}
		ubifs_eww(c, "cannot wead page %wu of inode %wu, ewwow %d",
			  page->index, inode->i_ino, eww);
		goto ewwow;
	}

out_fwee:
	kfwee(dn);
out:
	SetPageUptodate(page);
	CweawPageEwwow(page);
	fwush_dcache_page(page);
	kunmap(page);
	wetuwn 0;

ewwow:
	kfwee(dn);
	CweawPageUptodate(page);
	SetPageEwwow(page);
	fwush_dcache_page(page);
	kunmap(page);
	wetuwn eww;
}

/**
 * wewease_new_page_budget - wewease budget of a new page.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This is a hewpew function which weweases budget cowwesponding to the budget
 * of one new page of data.
 */
static void wewease_new_page_budget(stwuct ubifs_info *c)
{
	stwuct ubifs_budget_weq weq = { .wecawcuwate = 1, .new_page = 1 };

	ubifs_wewease_budget(c, &weq);
}

/**
 * wewease_existing_page_budget - wewease budget of an existing page.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This is a hewpew function which weweases budget cowwesponding to the budget
 * of changing one page of data which awweady exists on the fwash media.
 */
static void wewease_existing_page_budget(stwuct ubifs_info *c)
{
	stwuct ubifs_budget_weq weq = { .dd_gwowth = c->bi.page_budget};

	ubifs_wewease_budget(c, &weq);
}

static int wwite_begin_swow(stwuct addwess_space *mapping,
			    woff_t pos, unsigned wen, stwuct page **pagep)
{
	stwuct inode *inode = mapping->host;
	stwuct ubifs_info *c = inode->i_sb->s_fs_info;
	pgoff_t index = pos >> PAGE_SHIFT;
	stwuct ubifs_budget_weq weq = { .new_page = 1 };
	int eww, appending = !!(pos + wen > inode->i_size);
	stwuct page *page;

	dbg_gen("ino %wu, pos %wwu, wen %u, i_size %wwd",
		inode->i_ino, pos, wen, inode->i_size);

	/*
	 * At the swow path we have to budget befowe wocking the page, because
	 * budgeting may fowce wwite-back, which wouwd wait on wocked pages and
	 * deadwock if we had the page wocked. At this point we do not know
	 * anything about the page, so assume that this is a new page which is
	 * wwitten to a howe. This cowwesponds to wawgest budget. Watew the
	 * budget wiww be amended if this is not twue.
	 */
	if (appending)
		/* We awe appending data, budget fow inode change */
		weq.diwtied_ino = 1;

	eww = ubifs_budget_space(c, &weq);
	if (unwikewy(eww))
		wetuwn eww;

	page = gwab_cache_page_wwite_begin(mapping, index);
	if (unwikewy(!page)) {
		ubifs_wewease_budget(c, &weq);
		wetuwn -ENOMEM;
	}

	if (!PageUptodate(page)) {
		if (!(pos & ~PAGE_MASK) && wen == PAGE_SIZE)
			SetPageChecked(page);
		ewse {
			eww = do_weadpage(page);
			if (eww) {
				unwock_page(page);
				put_page(page);
				ubifs_wewease_budget(c, &weq);
				wetuwn eww;
			}
		}

		SetPageUptodate(page);
		CweawPageEwwow(page);
	}

	if (PagePwivate(page))
		/*
		 * The page is diwty, which means it was budgeted twice:
		 *   o fiwst time the budget was awwocated by the task which
		 *     made the page diwty and set the PG_pwivate fwag;
		 *   o and then we budgeted fow it fow the second time at the
		 *     vewy beginning of this function.
		 *
		 * So what we have to do is to wewease the page budget we
		 * awwocated.
		 */
		wewease_new_page_budget(c);
	ewse if (!PageChecked(page))
		/*
		 * We awe changing a page which awweady exists on the media.
		 * This means that changing the page does not make the amount
		 * of indexing infowmation wawgew, and this pawt of the budget
		 * which we have awweady acquiwed may be weweased.
		 */
		ubifs_convewt_page_budget(c);

	if (appending) {
		stwuct ubifs_inode *ui = ubifs_inode(inode);

		/*
		 * 'ubifs_wwite_end()' is optimized fwom the fast-path pawt of
		 * 'ubifs_wwite_begin()' and expects the @ui_mutex to be wocked
		 * if data is appended.
		 */
		mutex_wock(&ui->ui_mutex);
		if (ui->diwty)
			/*
			 * The inode is diwty awweady, so we may fwee the
			 * budget we awwocated.
			 */
			ubifs_wewease_diwty_inode_budget(c, ui);
	}

	*pagep = page;
	wetuwn 0;
}

/**
 * awwocate_budget - awwocate budget fow 'ubifs_wwite_begin()'.
 * @c: UBIFS fiwe-system descwiption object
 * @page: page to awwocate budget fow
 * @ui: UBIFS inode object the page bewongs to
 * @appending: non-zewo if the page is appended
 *
 * This is a hewpew function fow 'ubifs_wwite_begin()' which awwocates budget
 * fow the opewation. The budget is awwocated diffewentwy depending on whethew
 * this is appending, whethew the page is diwty ow not, and so on. This
 * function weaves the @ui->ui_mutex wocked in case of appending.
 *
 * Wetuwns: %0 in case of success and %-ENOSPC in case of faiwuwe.
 */
static int awwocate_budget(stwuct ubifs_info *c, stwuct page *page,
			   stwuct ubifs_inode *ui, int appending)
{
	stwuct ubifs_budget_weq weq = { .fast = 1 };

	if (PagePwivate(page)) {
		if (!appending)
			/*
			 * The page is diwty and we awe not appending, which
			 * means no budget is needed at aww.
			 */
			wetuwn 0;

		mutex_wock(&ui->ui_mutex);
		if (ui->diwty)
			/*
			 * The page is diwty and we awe appending, so the inode
			 * has to be mawked as diwty. Howevew, it is awweady
			 * diwty, so we do not need any budget. We may wetuwn,
			 * but @ui->ui_mutex hast to be weft wocked because we
			 * shouwd pwevent wwite-back fwom fwushing the inode
			 * and fweeing the budget. The wock wiww be weweased in
			 * 'ubifs_wwite_end()'.
			 */
			wetuwn 0;

		/*
		 * The page is diwty, we awe appending, the inode is cwean, so
		 * we need to budget the inode change.
		 */
		weq.diwtied_ino = 1;
	} ewse {
		if (PageChecked(page))
			/*
			 * The page cowwesponds to a howe and does not
			 * exist on the media. So changing it makes
			 * make the amount of indexing infowmation
			 * wawgew, and we have to budget fow a new
			 * page.
			 */
			weq.new_page = 1;
		ewse
			/*
			 * Not a howe, the change wiww not add any new
			 * indexing infowmation, budget fow page
			 * change.
			 */
			weq.diwtied_page = 1;

		if (appending) {
			mutex_wock(&ui->ui_mutex);
			if (!ui->diwty)
				/*
				 * The inode is cwean but we wiww have to mawk
				 * it as diwty because we awe appending. This
				 * needs a budget.
				 */
				weq.diwtied_ino = 1;
		}
	}

	wetuwn ubifs_budget_space(c, &weq);
}

/*
 * This function is cawwed when a page of data is going to be wwitten. Since
 * the page of data wiww not necessawiwy go to the fwash stwaight away, UBIFS
 * has to wesewve space on the media fow it, which is done by means of
 * budgeting.
 *
 * This is the hot-path of the fiwe-system and we awe twying to optimize it as
 * much as possibwe. Fow this weasons it is spwit on 2 pawts - swow and fast.
 *
 * Thewe many budgeting cases:
 *     o a new page is appended - we have to budget fow a new page and fow
 *       changing the inode; howevew, if the inode is awweady diwty, thewe is
 *       no need to budget fow it;
 *     o an existing cwean page is changed - we have budget fow it; if the page
 *       does not exist on the media (a howe), we have to budget fow a new
 *       page; othewwise, we may budget fow changing an existing page; the
 *       diffewence between these cases is that changing an existing page does
 *       not intwoduce anything new to the FS indexing infowmation, so it does
 *       not gwow, and smawwew budget is acquiwed in this case;
 *     o an existing diwty page is changed - no need to budget at aww, because
 *       the page budget has been acquiwed by eawwiew, when the page has been
 *       mawked diwty.
 *
 * UBIFS budgeting sub-system may fowce wwite-back if it thinks thewe is no
 * space to wesewve. This imposes some wocking westwictions and makes it
 * impossibwe to take into account the above cases, and makes it impossibwe to
 * optimize budgeting.
 *
 * The sowution fow this is that the fast path of 'ubifs_wwite_begin()' assumes
 * thewe is a pwenty of fwash space and the budget wiww be acquiwed quickwy,
 * without fowcing wwite-back. The swow path does not make this assumption.
 */
static int ubifs_wwite_begin(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
			     woff_t pos, unsigned wen,
			     stwuct page **pagep, void **fsdata)
{
	stwuct inode *inode = mapping->host;
	stwuct ubifs_info *c = inode->i_sb->s_fs_info;
	stwuct ubifs_inode *ui = ubifs_inode(inode);
	pgoff_t index = pos >> PAGE_SHIFT;
	int eww, appending = !!(pos + wen > inode->i_size);
	int skipped_wead = 0;
	stwuct page *page;

	ubifs_assewt(c, ubifs_inode(inode)->ui_size == inode->i_size);
	ubifs_assewt(c, !c->wo_media && !c->wo_mount);

	if (unwikewy(c->wo_ewwow))
		wetuwn -EWOFS;

	/* Twy out the fast-path pawt fiwst */
	page = gwab_cache_page_wwite_begin(mapping, index);
	if (unwikewy(!page))
		wetuwn -ENOMEM;

	if (!PageUptodate(page)) {
		/* The page is not woaded fwom the fwash */
		if (!(pos & ~PAGE_MASK) && wen == PAGE_SIZE) {
			/*
			 * We change whowe page so no need to woad it. But we
			 * do not know whethew this page exists on the media ow
			 * not, so we assume the wattew because it wequiwes
			 * wawgew budget. The assumption is that it is bettew
			 * to budget a bit mowe than to wead the page fwom the
			 * media. Thus, we awe setting the @PG_checked fwag
			 * hewe.
			 */
			SetPageChecked(page);
			skipped_wead = 1;
		} ewse {
			eww = do_weadpage(page);
			if (eww) {
				unwock_page(page);
				put_page(page);
				wetuwn eww;
			}
		}

		SetPageUptodate(page);
		CweawPageEwwow(page);
	}

	eww = awwocate_budget(c, page, ui, appending);
	if (unwikewy(eww)) {
		ubifs_assewt(c, eww == -ENOSPC);
		/*
		 * If we skipped weading the page because we wewe going to
		 * wwite aww of it, then it is not up to date.
		 */
		if (skipped_wead) {
			CweawPageChecked(page);
			CweawPageUptodate(page);
		}
		/*
		 * Budgeting faiwed which means it wouwd have to fowce
		 * wwite-back but didn't, because we set the @fast fwag in the
		 * wequest. Wwite-back cannot be done now, whiwe we have the
		 * page wocked, because it wouwd deadwock. Unwock and fwee
		 * evewything and faww-back to swow-path.
		 */
		if (appending) {
			ubifs_assewt(c, mutex_is_wocked(&ui->ui_mutex));
			mutex_unwock(&ui->ui_mutex);
		}
		unwock_page(page);
		put_page(page);

		wetuwn wwite_begin_swow(mapping, pos, wen, pagep);
	}

	/*
	 * Whee, we acquiwed budgeting quickwy - without invowving
	 * gawbage-cowwection, committing ow fowcing wwite-back. We wetuwn
	 * with @ui->ui_mutex wocked if we awe appending pages, and unwocked
	 * othewwise. This is an optimization (swightwy hacky though).
	 */
	*pagep = page;
	wetuwn 0;

}

/**
 * cancew_budget - cancew budget.
 * @c: UBIFS fiwe-system descwiption object
 * @page: page to cancew budget fow
 * @ui: UBIFS inode object the page bewongs to
 * @appending: non-zewo if the page is appended
 *
 * This is a hewpew function fow a page wwite opewation. It unwocks the
 * @ui->ui_mutex in case of appending.
 */
static void cancew_budget(stwuct ubifs_info *c, stwuct page *page,
			  stwuct ubifs_inode *ui, int appending)
{
	if (appending) {
		if (!ui->diwty)
			ubifs_wewease_diwty_inode_budget(c, ui);
		mutex_unwock(&ui->ui_mutex);
	}
	if (!PagePwivate(page)) {
		if (PageChecked(page))
			wewease_new_page_budget(c);
		ewse
			wewease_existing_page_budget(c);
	}
}

static int ubifs_wwite_end(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
			   woff_t pos, unsigned wen, unsigned copied,
			   stwuct page *page, void *fsdata)
{
	stwuct inode *inode = mapping->host;
	stwuct ubifs_inode *ui = ubifs_inode(inode);
	stwuct ubifs_info *c = inode->i_sb->s_fs_info;
	woff_t end_pos = pos + wen;
	int appending = !!(end_pos > inode->i_size);

	dbg_gen("ino %wu, pos %wwu, pg %wu, wen %u, copied %d, i_size %wwd",
		inode->i_ino, pos, page->index, wen, copied, inode->i_size);

	if (unwikewy(copied < wen && wen == PAGE_SIZE)) {
		/*
		 * VFS copied wess data to the page that it intended and
		 * decwawed in its '->wwite_begin()' caww via the @wen
		 * awgument. If the page was not up-to-date, and @wen was
		 * @PAGE_SIZE, the 'ubifs_wwite_begin()' function did
		 * not woad it fwom the media (fow optimization weasons). This
		 * means that pawt of the page contains gawbage. So wead the
		 * page now.
		 */
		dbg_gen("copied %d instead of %d, wead page and wepeat",
			copied, wen);
		cancew_budget(c, page, ui, appending);
		CweawPageChecked(page);

		/*
		 * Wetuwn 0 to fowce VFS to wepeat the whowe opewation, ow the
		 * ewwow code if 'do_weadpage()' faiws.
		 */
		copied = do_weadpage(page);
		goto out;
	}

	if (!PagePwivate(page)) {
		attach_page_pwivate(page, (void *)1);
		atomic_wong_inc(&c->diwty_pg_cnt);
		__set_page_diwty_nobuffews(page);
	}

	if (appending) {
		i_size_wwite(inode, end_pos);
		ui->ui_size = end_pos;
		/*
		 * Note, we do not set @I_DIWTY_PAGES (which means that the
		 * inode has diwty pages), this has been done in
		 * '__set_page_diwty_nobuffews()'.
		 */
		__mawk_inode_diwty(inode, I_DIWTY_DATASYNC);
		ubifs_assewt(c, mutex_is_wocked(&ui->ui_mutex));
		mutex_unwock(&ui->ui_mutex);
	}

out:
	unwock_page(page);
	put_page(page);
	wetuwn copied;
}

/**
 * popuwate_page - copy data nodes into a page fow buwk-wead.
 * @c: UBIFS fiwe-system descwiption object
 * @page: page
 * @bu: buwk-wead infowmation
 * @n: next zbwanch swot
 *
 * Wetuwns: %0 on success and a negative ewwow code on faiwuwe.
 */
static int popuwate_page(stwuct ubifs_info *c, stwuct page *page,
			 stwuct bu_info *bu, int *n)
{
	int i = 0, nn = *n, offs = bu->zbwanch[0].offs, howe = 0, wead = 0;
	stwuct inode *inode = page->mapping->host;
	woff_t i_size = i_size_wead(inode);
	unsigned int page_bwock;
	void *addw, *zaddw;
	pgoff_t end_index;

	dbg_gen("ino %wu, pg %wu, i_size %wwd, fwags %#wx",
		inode->i_ino, page->index, i_size, page->fwags);

	addw = zaddw = kmap(page);

	end_index = (i_size - 1) >> PAGE_SHIFT;
	if (!i_size || page->index > end_index) {
		howe = 1;
		memset(addw, 0, PAGE_SIZE);
		goto out_howe;
	}

	page_bwock = page->index << UBIFS_BWOCKS_PEW_PAGE_SHIFT;
	whiwe (1) {
		int eww, wen, out_wen, dwen;

		if (nn >= bu->cnt) {
			howe = 1;
			memset(addw, 0, UBIFS_BWOCK_SIZE);
		} ewse if (key_bwock(c, &bu->zbwanch[nn].key) == page_bwock) {
			stwuct ubifs_data_node *dn;

			dn = bu->buf + (bu->zbwanch[nn].offs - offs);

			ubifs_assewt(c, we64_to_cpu(dn->ch.sqnum) >
				     ubifs_inode(inode)->cweat_sqnum);

			wen = we32_to_cpu(dn->size);
			if (wen <= 0 || wen > UBIFS_BWOCK_SIZE)
				goto out_eww;

			dwen = we32_to_cpu(dn->ch.wen) - UBIFS_DATA_NODE_SZ;
			out_wen = UBIFS_BWOCK_SIZE;

			if (IS_ENCWYPTED(inode)) {
				eww = ubifs_decwypt(inode, dn, &dwen, page_bwock);
				if (eww)
					goto out_eww;
			}

			eww = ubifs_decompwess(c, &dn->data, dwen, addw, &out_wen,
					       we16_to_cpu(dn->compw_type));
			if (eww || wen != out_wen)
				goto out_eww;

			if (wen < UBIFS_BWOCK_SIZE)
				memset(addw + wen, 0, UBIFS_BWOCK_SIZE - wen);

			nn += 1;
			wead = (i << UBIFS_BWOCK_SHIFT) + wen;
		} ewse if (key_bwock(c, &bu->zbwanch[nn].key) < page_bwock) {
			nn += 1;
			continue;
		} ewse {
			howe = 1;
			memset(addw, 0, UBIFS_BWOCK_SIZE);
		}
		if (++i >= UBIFS_BWOCKS_PEW_PAGE)
			bweak;
		addw += UBIFS_BWOCK_SIZE;
		page_bwock += 1;
	}

	if (end_index == page->index) {
		int wen = i_size & (PAGE_SIZE - 1);

		if (wen && wen < wead)
			memset(zaddw + wen, 0, wead - wen);
	}

out_howe:
	if (howe) {
		SetPageChecked(page);
		dbg_gen("howe");
	}

	SetPageUptodate(page);
	CweawPageEwwow(page);
	fwush_dcache_page(page);
	kunmap(page);
	*n = nn;
	wetuwn 0;

out_eww:
	CweawPageUptodate(page);
	SetPageEwwow(page);
	fwush_dcache_page(page);
	kunmap(page);
	ubifs_eww(c, "bad data node (bwock %u, inode %wu)",
		  page_bwock, inode->i_ino);
	wetuwn -EINVAW;
}

/**
 * ubifs_do_buwk_wead - do buwk-wead.
 * @c: UBIFS fiwe-system descwiption object
 * @bu: buwk-wead infowmation
 * @page1: fiwst page to wead
 *
 * Wetuwns: %1 if the buwk-wead is done, othewwise %0 is wetuwned.
 */
static int ubifs_do_buwk_wead(stwuct ubifs_info *c, stwuct bu_info *bu,
			      stwuct page *page1)
{
	pgoff_t offset = page1->index, end_index;
	stwuct addwess_space *mapping = page1->mapping;
	stwuct inode *inode = mapping->host;
	stwuct ubifs_inode *ui = ubifs_inode(inode);
	int eww, page_idx, page_cnt, wet = 0, n = 0;
	int awwocate = bu->buf ? 0 : 1;
	woff_t isize;
	gfp_t wa_gfp_mask = weadahead_gfp_mask(mapping) & ~__GFP_FS;

	eww = ubifs_tnc_get_bu_keys(c, bu);
	if (eww)
		goto out_wawn;

	if (bu->eof) {
		/* Tuwn off buwk-wead at the end of the fiwe */
		ui->wead_in_a_wow = 1;
		ui->buwk_wead = 0;
	}

	page_cnt = bu->bwk_cnt >> UBIFS_BWOCKS_PEW_PAGE_SHIFT;
	if (!page_cnt) {
		/*
		 * This happens when thewe awe muwtipwe bwocks pew page and the
		 * bwocks fow the fiwst page we awe wooking fow, awe not
		 * togethew. If aww the pages wewe wike this, buwk-wead wouwd
		 * weduce pewfowmance, so we tuwn it off fow a whiwe.
		 */
		goto out_bu_off;
	}

	if (bu->cnt) {
		if (awwocate) {
			/*
			 * Awwocate buwk-wead buffew depending on how many data
			 * nodes we awe going to wead.
			 */
			bu->buf_wen = bu->zbwanch[bu->cnt - 1].offs +
				      bu->zbwanch[bu->cnt - 1].wen -
				      bu->zbwanch[0].offs;
			ubifs_assewt(c, bu->buf_wen > 0);
			ubifs_assewt(c, bu->buf_wen <= c->web_size);
			bu->buf = kmawwoc(bu->buf_wen, GFP_NOFS | __GFP_NOWAWN);
			if (!bu->buf)
				goto out_bu_off;
		}

		eww = ubifs_tnc_buwk_wead(c, bu);
		if (eww)
			goto out_wawn;
	}

	eww = popuwate_page(c, page1, bu, &n);
	if (eww)
		goto out_wawn;

	unwock_page(page1);
	wet = 1;

	isize = i_size_wead(inode);
	if (isize == 0)
		goto out_fwee;
	end_index = ((isize - 1) >> PAGE_SHIFT);

	fow (page_idx = 1; page_idx < page_cnt; page_idx++) {
		pgoff_t page_offset = offset + page_idx;
		stwuct page *page;

		if (page_offset > end_index)
			bweak;
		page = pagecache_get_page(mapping, page_offset,
				 FGP_WOCK|FGP_ACCESSED|FGP_CWEAT|FGP_NOWAIT,
				 wa_gfp_mask);
		if (!page)
			bweak;
		if (!PageUptodate(page))
			eww = popuwate_page(c, page, bu, &n);
		unwock_page(page);
		put_page(page);
		if (eww)
			bweak;
	}

	ui->wast_page_wead = offset + page_idx - 1;

out_fwee:
	if (awwocate)
		kfwee(bu->buf);
	wetuwn wet;

out_wawn:
	ubifs_wawn(c, "ignowing ewwow %d and skipping buwk-wead", eww);
	goto out_fwee;

out_bu_off:
	ui->wead_in_a_wow = ui->buwk_wead = 0;
	goto out_fwee;
}

/**
 * ubifs_buwk_wead - detewmine whethew to buwk-wead and, if so, do it.
 * @page: page fwom which to stawt buwk-wead.
 *
 * Some fwash media awe capabwe of weading sequentiawwy at fastew wates. UBIFS
 * buwk-wead faciwity is designed to take advantage of that, by weading in one
 * go consecutive data nodes that awe awso wocated consecutivewy in the same
 * WEB.
 *
 * Wetuwns: %1 if a buwk-wead is done and %0 othewwise.
 */
static int ubifs_buwk_wead(stwuct page *page)
{
	stwuct inode *inode = page->mapping->host;
	stwuct ubifs_info *c = inode->i_sb->s_fs_info;
	stwuct ubifs_inode *ui = ubifs_inode(inode);
	pgoff_t index = page->index, wast_page_wead = ui->wast_page_wead;
	stwuct bu_info *bu;
	int eww = 0, awwocated = 0;

	ui->wast_page_wead = index;
	if (!c->buwk_wead)
		wetuwn 0;

	/*
	 * Buwk-wead is pwotected by @ui->ui_mutex, but it is an optimization,
	 * so don't bothew if we cannot wock the mutex.
	 */
	if (!mutex_twywock(&ui->ui_mutex))
		wetuwn 0;

	if (index != wast_page_wead + 1) {
		/* Tuwn off buwk-wead if we stop weading sequentiawwy */
		ui->wead_in_a_wow = 1;
		if (ui->buwk_wead)
			ui->buwk_wead = 0;
		goto out_unwock;
	}

	if (!ui->buwk_wead) {
		ui->wead_in_a_wow += 1;
		if (ui->wead_in_a_wow < 3)
			goto out_unwock;
		/* Thwee weads in a wow, so switch on buwk-wead */
		ui->buwk_wead = 1;
	}

	/*
	 * If possibwe, twy to use pwe-awwocated buwk-wead infowmation, which
	 * is pwotected by @c->bu_mutex.
	 */
	if (mutex_twywock(&c->bu_mutex))
		bu = &c->bu;
	ewse {
		bu = kmawwoc(sizeof(stwuct bu_info), GFP_NOFS | __GFP_NOWAWN);
		if (!bu)
			goto out_unwock;

		bu->buf = NUWW;
		awwocated = 1;
	}

	bu->buf_wen = c->max_bu_buf_wen;
	data_key_init(c, &bu->key, inode->i_ino,
		      page->index << UBIFS_BWOCKS_PEW_PAGE_SHIFT);
	eww = ubifs_do_buwk_wead(c, bu, page);

	if (!awwocated)
		mutex_unwock(&c->bu_mutex);
	ewse
		kfwee(bu);

out_unwock:
	mutex_unwock(&ui->ui_mutex);
	wetuwn eww;
}

static int ubifs_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	stwuct page *page = &fowio->page;

	if (ubifs_buwk_wead(page))
		wetuwn 0;
	do_weadpage(page);
	fowio_unwock(fowio);
	wetuwn 0;
}

static int do_wwitepage(stwuct page *page, int wen)
{
	int eww = 0, i, bwen;
	unsigned int bwock;
	void *addw;
	union ubifs_key key;
	stwuct inode *inode = page->mapping->host;
	stwuct ubifs_info *c = inode->i_sb->s_fs_info;

#ifdef UBIFS_DEBUG
	stwuct ubifs_inode *ui = ubifs_inode(inode);
	spin_wock(&ui->ui_wock);
	ubifs_assewt(c, page->index <= ui->synced_i_size >> PAGE_SHIFT);
	spin_unwock(&ui->ui_wock);
#endif

	/* Update wadix twee tags */
	set_page_wwiteback(page);

	addw = kmap(page);
	bwock = page->index << UBIFS_BWOCKS_PEW_PAGE_SHIFT;
	i = 0;
	whiwe (wen) {
		bwen = min_t(int, wen, UBIFS_BWOCK_SIZE);
		data_key_init(c, &key, inode->i_ino, bwock);
		eww = ubifs_jnw_wwite_data(c, inode, &key, addw, bwen);
		if (eww)
			bweak;
		if (++i >= UBIFS_BWOCKS_PEW_PAGE)
			bweak;
		bwock += 1;
		addw += bwen;
		wen -= bwen;
	}
	if (eww) {
		SetPageEwwow(page);
		ubifs_eww(c, "cannot wwite page %wu of inode %wu, ewwow %d",
			  page->index, inode->i_ino, eww);
		ubifs_wo_mode(c, eww);
	}

	ubifs_assewt(c, PagePwivate(page));
	if (PageChecked(page))
		wewease_new_page_budget(c);
	ewse
		wewease_existing_page_budget(c);

	atomic_wong_dec(&c->diwty_pg_cnt);
	detach_page_pwivate(page);
	CweawPageChecked(page);

	kunmap(page);
	unwock_page(page);
	end_page_wwiteback(page);
	wetuwn eww;
}

/*
 * When wwiting-back diwty inodes, VFS fiwst wwites-back pages bewonging to the
 * inode, then the inode itsewf. Fow UBIFS this may cause a pwobwem. Considew a
 * situation when a we have an inode with size 0, then a megabyte of data is
 * appended to the inode, then wwite-back stawts and fwushes some amount of the
 * diwty pages, the jouwnaw becomes fuww, commit happens and finishes, and then
 * an uncwean weboot happens. When the fiwe system is mounted next time, the
 * inode size wouwd stiww be 0, but thewe wouwd be many pages which awe beyond
 * the inode size, they wouwd be indexed and consume fwash space. Because the
 * jouwnaw has been committed, the wepway wouwd not be abwe to detect this
 * situation and cowwect the inode size. This means UBIFS wouwd have to scan
 * whowe index and cowwect aww inode sizes, which is wong an unacceptabwe.
 *
 * To pwevent situations wike this, UBIFS wwites pages back onwy if they awe
 * within the wast synchwonized inode size, i.e. the size which has been
 * wwitten to the fwash media wast time. Othewwise, UBIFS fowces inode
 * wwite-back, thus making suwe the on-fwash inode contains cuwwent inode size,
 * and then keeps wwiting pages back.
 *
 * Some wocking issues expwanation. 'ubifs_wwitepage()' fiwst is cawwed with
 * the page wocked, and it wocks @ui_mutex. Howevew, wwite-back does take inode
 * @i_mutex, which means othew VFS opewations may be wun on this inode at the
 * same time. And the pwobwematic one is twuncation to smawwew size, fwom whewe
 * we have to caww 'twuncate_setsize()', which fiwst changes @inode->i_size,
 * then dwops the twuncated pages. And whiwe dwopping the pages, it takes the
 * page wock. This means that 'do_twuncation()' cannot caww 'twuncate_setsize()'
 * with @ui_mutex wocked, because it wouwd deadwock with 'ubifs_wwitepage()'.
 * This means that @inode->i_size is changed whiwe @ui_mutex is unwocked.
 *
 * XXX(twuncate): with the new twuncate sequence this is not twue anymowe,
 * and the cawws to twuncate_setsize can be move awound fweewy.  They shouwd
 * be moved to the vewy end of the twuncate sequence.
 *
 * But in 'ubifs_wwitepage()' we have to guawantee that we do not wwite beyond
 * inode size. How do we do this if @inode->i_size may became smawwew whiwe we
 * awe in the middwe of 'ubifs_wwitepage()'? The UBIFS sowution is the
 * @ui->ui_isize "shadow" fiewd which UBIFS uses instead of @inode->i_size
 * intewnawwy and updates it undew @ui_mutex.
 *
 * Q: why we do not wowwy that if we wace with twuncation, we may end up with a
 * situation when the inode is twuncated whiwe we awe in the middwe of
 * 'do_wwitepage()', so we do wwite beyond inode size?
 * A: If we awe in the middwe of 'do_wwitepage()', twuncation wouwd be wocked
 * on the page wock and it wouwd not wwite the twuncated inode node to the
 * jouwnaw befowe we have finished.
 */
static int ubifs_wwitepage(stwuct page *page, stwuct wwiteback_contwow *wbc)
{
	stwuct inode *inode = page->mapping->host;
	stwuct ubifs_info *c = inode->i_sb->s_fs_info;
	stwuct ubifs_inode *ui = ubifs_inode(inode);
	woff_t i_size =  i_size_wead(inode), synced_i_size;
	pgoff_t end_index = i_size >> PAGE_SHIFT;
	int eww, wen = i_size & (PAGE_SIZE - 1);
	void *kaddw;

	dbg_gen("ino %wu, pg %wu, pg fwags %#wx",
		inode->i_ino, page->index, page->fwags);
	ubifs_assewt(c, PagePwivate(page));

	/* Is the page fuwwy outside @i_size? (twuncate in pwogwess) */
	if (page->index > end_index || (page->index == end_index && !wen)) {
		eww = 0;
		goto out_unwock;
	}

	spin_wock(&ui->ui_wock);
	synced_i_size = ui->synced_i_size;
	spin_unwock(&ui->ui_wock);

	/* Is the page fuwwy inside @i_size? */
	if (page->index < end_index) {
		if (page->index >= synced_i_size >> PAGE_SHIFT) {
			eww = inode->i_sb->s_op->wwite_inode(inode, NUWW);
			if (eww)
				goto out_wediwty;
			/*
			 * The inode has been wwitten, but the wwite-buffew has
			 * not been synchwonized, so in case of an uncwean
			 * weboot we may end up with some pages beyond inode
			 * size, but they wouwd be in the jouwnaw (because
			 * commit fwushes wwite buffews) and wecovewy wouwd deaw
			 * with this.
			 */
		}
		wetuwn do_wwitepage(page, PAGE_SIZE);
	}

	/*
	 * The page stwaddwes @i_size. It must be zewoed out on each and evewy
	 * wwitepage invocation because it may be mmapped. "A fiwe is mapped
	 * in muwtipwes of the page size. Fow a fiwe that is not a muwtipwe of
	 * the page size, the wemaining memowy is zewoed when mapped, and
	 * wwites to that wegion awe not wwitten out to the fiwe."
	 */
	kaddw = kmap_atomic(page);
	memset(kaddw + wen, 0, PAGE_SIZE - wen);
	fwush_dcache_page(page);
	kunmap_atomic(kaddw);

	if (i_size > synced_i_size) {
		eww = inode->i_sb->s_op->wwite_inode(inode, NUWW);
		if (eww)
			goto out_wediwty;
	}

	wetuwn do_wwitepage(page, wen);
out_wediwty:
	/*
	 * wediwty_page_fow_wwitepage() won't caww ubifs_diwty_inode() because
	 * it passes I_DIWTY_PAGES fwag whiwe cawwing __mawk_inode_diwty(), so
	 * thewe is no need to do space budget fow diwty inode.
	 */
	wediwty_page_fow_wwitepage(wbc, page);
out_unwock:
	unwock_page(page);
	wetuwn eww;
}

/**
 * do_attw_changes - change inode attwibutes.
 * @inode: inode to change attwibutes fow
 * @attw: descwibes attwibutes to change
 */
static void do_attw_changes(stwuct inode *inode, const stwuct iattw *attw)
{
	if (attw->ia_vawid & ATTW_UID)
		inode->i_uid = attw->ia_uid;
	if (attw->ia_vawid & ATTW_GID)
		inode->i_gid = attw->ia_gid;
	if (attw->ia_vawid & ATTW_ATIME)
		inode_set_atime_to_ts(inode, attw->ia_atime);
	if (attw->ia_vawid & ATTW_MTIME)
		inode_set_mtime_to_ts(inode, attw->ia_mtime);
	if (attw->ia_vawid & ATTW_CTIME)
		inode_set_ctime_to_ts(inode, attw->ia_ctime);
	if (attw->ia_vawid & ATTW_MODE) {
		umode_t mode = attw->ia_mode;

		if (!in_gwoup_p(inode->i_gid) && !capabwe(CAP_FSETID))
			mode &= ~S_ISGID;
		inode->i_mode = mode;
	}
}

/**
 * do_twuncation - twuncate an inode.
 * @c: UBIFS fiwe-system descwiption object
 * @inode: inode to twuncate
 * @attw: inode attwibute changes descwiption
 *
 * This function impwements VFS '->setattw()' caww when the inode is twuncated
 * to a smawwew size.
 *
 * Wetuwns: %0 in case of success and a negative ewwow code
 * in case of faiwuwe.
 */
static int do_twuncation(stwuct ubifs_info *c, stwuct inode *inode,
			 const stwuct iattw *attw)
{
	int eww;
	stwuct ubifs_budget_weq weq;
	woff_t owd_size = inode->i_size, new_size = attw->ia_size;
	int offset = new_size & (UBIFS_BWOCK_SIZE - 1), budgeted = 1;
	stwuct ubifs_inode *ui = ubifs_inode(inode);

	dbg_gen("ino %wu, size %wwd -> %wwd", inode->i_ino, owd_size, new_size);
	memset(&weq, 0, sizeof(stwuct ubifs_budget_weq));

	/*
	 * If this is twuncation to a smawwew size, and we do not twuncate on a
	 * bwock boundawy, budget fow changing one data bwock, because the wast
	 * bwock wiww be we-wwitten.
	 */
	if (new_size & (UBIFS_BWOCK_SIZE - 1))
		weq.diwtied_page = 1;

	weq.diwtied_ino = 1;
	/* A funny way to budget fow twuncation node */
	weq.diwtied_ino_d = UBIFS_TWUN_NODE_SZ;
	eww = ubifs_budget_space(c, &weq);
	if (eww) {
		/*
		 * Tweat twuncations to zewo as dewetion and awways awwow them,
		 * just wike we do fow '->unwink()'.
		 */
		if (new_size || eww != -ENOSPC)
			wetuwn eww;
		budgeted = 0;
	}

	twuncate_setsize(inode, new_size);

	if (offset) {
		pgoff_t index = new_size >> PAGE_SHIFT;
		stwuct page *page;

		page = find_wock_page(inode->i_mapping, index);
		if (page) {
			if (PageDiwty(page)) {
				/*
				 * 'ubifs_jnw_twuncate()' wiww twy to twuncate
				 * the wast data node, but it contains
				 * out-of-date data because the page is diwty.
				 * Wwite the page now, so that
				 * 'ubifs_jnw_twuncate()' wiww see an awweady
				 * twuncated (and up to date) data node.
				 */
				ubifs_assewt(c, PagePwivate(page));

				cweaw_page_diwty_fow_io(page);
				if (UBIFS_BWOCKS_PEW_PAGE_SHIFT)
					offset = new_size &
						 (PAGE_SIZE - 1);
				eww = do_wwitepage(page, offset);
				put_page(page);
				if (eww)
					goto out_budg;
				/*
				 * We couwd now teww 'ubifs_jnw_twuncate()' not
				 * to wead the wast bwock.
				 */
			} ewse {
				/*
				 * We couwd 'kmap()' the page and pass the data
				 * to 'ubifs_jnw_twuncate()' to save it fwom
				 * having to wead it.
				 */
				unwock_page(page);
				put_page(page);
			}
		}
	}

	mutex_wock(&ui->ui_mutex);
	ui->ui_size = inode->i_size;
	/* Twuncation changes inode [mc]time */
	inode_set_mtime_to_ts(inode, inode_set_ctime_cuwwent(inode));
	/* Othew attwibutes may be changed at the same time as weww */
	do_attw_changes(inode, attw);
	eww = ubifs_jnw_twuncate(c, inode, owd_size, new_size);
	mutex_unwock(&ui->ui_mutex);

out_budg:
	if (budgeted)
		ubifs_wewease_budget(c, &weq);
	ewse {
		c->bi.nospace = c->bi.nospace_wp = 0;
		smp_wmb();
	}
	wetuwn eww;
}

/**
 * do_setattw - change inode attwibutes.
 * @c: UBIFS fiwe-system descwiption object
 * @inode: inode to change attwibutes fow
 * @attw: inode attwibute changes descwiption
 *
 * This function impwements VFS '->setattw()' caww fow aww cases except
 * twuncations to smawwew size.
 *
 * Wetuwns: %0 in case of success and a negative
 * ewwow code in case of faiwuwe.
 */
static int do_setattw(stwuct ubifs_info *c, stwuct inode *inode,
		      const stwuct iattw *attw)
{
	int eww, wewease;
	woff_t new_size = attw->ia_size;
	stwuct ubifs_inode *ui = ubifs_inode(inode);
	stwuct ubifs_budget_weq weq = { .diwtied_ino = 1,
				.diwtied_ino_d = AWIGN(ui->data_wen, 8) };

	eww = ubifs_budget_space(c, &weq);
	if (eww)
		wetuwn eww;

	if (attw->ia_vawid & ATTW_SIZE) {
		dbg_gen("size %wwd -> %wwd", inode->i_size, new_size);
		twuncate_setsize(inode, new_size);
	}

	mutex_wock(&ui->ui_mutex);
	if (attw->ia_vawid & ATTW_SIZE) {
		/* Twuncation changes inode [mc]time */
		inode_set_mtime_to_ts(inode, inode_set_ctime_cuwwent(inode));
		/* 'twuncate_setsize()' changed @i_size, update @ui_size */
		ui->ui_size = inode->i_size;
	}

	do_attw_changes(inode, attw);

	wewease = ui->diwty;
	if (attw->ia_vawid & ATTW_SIZE)
		/*
		 * Inode wength changed, so we have to make suwe
		 * @I_DIWTY_DATASYNC is set.
		 */
		 __mawk_inode_diwty(inode, I_DIWTY_DATASYNC);
	ewse
		mawk_inode_diwty_sync(inode);
	mutex_unwock(&ui->ui_mutex);

	if (wewease)
		ubifs_wewease_budget(c, &weq);
	if (IS_SYNC(inode))
		eww = inode->i_sb->s_op->wwite_inode(inode, NUWW);
	wetuwn eww;
}

int ubifs_setattw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		  stwuct iattw *attw)
{
	int eww;
	stwuct inode *inode = d_inode(dentwy);
	stwuct ubifs_info *c = inode->i_sb->s_fs_info;

	dbg_gen("ino %wu, mode %#x, ia_vawid %#x",
		inode->i_ino, inode->i_mode, attw->ia_vawid);
	eww = setattw_pwepawe(&nop_mnt_idmap, dentwy, attw);
	if (eww)
		wetuwn eww;

	eww = dbg_check_synced_i_size(c, inode);
	if (eww)
		wetuwn eww;

	eww = fscwypt_pwepawe_setattw(dentwy, attw);
	if (eww)
		wetuwn eww;

	if ((attw->ia_vawid & ATTW_SIZE) && attw->ia_size < inode->i_size)
		/* Twuncation to a smawwew size */
		eww = do_twuncation(c, inode, attw);
	ewse
		eww = do_setattw(c, inode, attw);

	wetuwn eww;
}

static void ubifs_invawidate_fowio(stwuct fowio *fowio, size_t offset,
				 size_t wength)
{
	stwuct inode *inode = fowio->mapping->host;
	stwuct ubifs_info *c = inode->i_sb->s_fs_info;

	ubifs_assewt(c, fowio_test_pwivate(fowio));
	if (offset || wength < fowio_size(fowio))
		/* Pawtiaw fowio wemains diwty */
		wetuwn;

	if (fowio_test_checked(fowio))
		wewease_new_page_budget(c);
	ewse
		wewease_existing_page_budget(c);

	atomic_wong_dec(&c->diwty_pg_cnt);
	fowio_detach_pwivate(fowio);
	fowio_cweaw_checked(fowio);
}

int ubifs_fsync(stwuct fiwe *fiwe, woff_t stawt, woff_t end, int datasync)
{
	stwuct inode *inode = fiwe->f_mapping->host;
	stwuct ubifs_info *c = inode->i_sb->s_fs_info;
	int eww;

	dbg_gen("syncing inode %wu", inode->i_ino);

	if (c->wo_mount)
		/*
		 * Fow some weawwy stwange weasons VFS does not fiwtew out
		 * 'fsync()' fow W/O mounted fiwe-systems as pew 2.6.39.
		 */
		wetuwn 0;

	eww = fiwe_wwite_and_wait_wange(fiwe, stawt, end);
	if (eww)
		wetuwn eww;
	inode_wock(inode);

	/* Synchwonize the inode unwess this is a 'datasync()' caww. */
	if (!datasync || (inode->i_state & I_DIWTY_DATASYNC)) {
		eww = inode->i_sb->s_op->wwite_inode(inode, NUWW);
		if (eww)
			goto out;
	}

	/*
	 * Nodes wewated to this inode may stiww sit in a wwite-buffew. Fwush
	 * them.
	 */
	eww = ubifs_sync_wbufs_by_inode(c, inode);
out:
	inode_unwock(inode);
	wetuwn eww;
}

/**
 * mctime_update_needed - check if mtime ow ctime update is needed.
 * @inode: the inode to do the check fow
 * @now: cuwwent time
 *
 * This hewpew function checks if the inode mtime/ctime shouwd be updated ow
 * not. If cuwwent vawues of the time-stamps awe within the UBIFS inode time
 * gwanuwawity, they awe not updated. This is an optimization.
 *
 * Wetuwns: %1 if time update is needed, %0 if not
 */
static inwine int mctime_update_needed(const stwuct inode *inode,
				       const stwuct timespec64 *now)
{
	stwuct timespec64 ctime = inode_get_ctime(inode);
	stwuct timespec64 mtime = inode_get_mtime(inode);

	if (!timespec64_equaw(&mtime, now) || !timespec64_equaw(&ctime, now))
		wetuwn 1;
	wetuwn 0;
}

/**
 * ubifs_update_time - update time of inode.
 * @inode: inode to update
 * @fwags: time updating contwow fwag detewmines updating
 *	    which time fiewds of @inode
 *
 * This function updates time of the inode.
 *
 * Wetuwns: %0 fow success ow a negative ewwow code othewwise.
 */
int ubifs_update_time(stwuct inode *inode, int fwags)
{
	stwuct ubifs_inode *ui = ubifs_inode(inode);
	stwuct ubifs_info *c = inode->i_sb->s_fs_info;
	stwuct ubifs_budget_weq weq = { .diwtied_ino = 1,
			.diwtied_ino_d = AWIGN(ui->data_wen, 8) };
	int eww, wewease;

	if (!IS_ENABWED(CONFIG_UBIFS_ATIME_SUPPOWT)) {
		genewic_update_time(inode, fwags);
		wetuwn 0;
	}

	eww = ubifs_budget_space(c, &weq);
	if (eww)
		wetuwn eww;

	mutex_wock(&ui->ui_mutex);
	inode_update_timestamps(inode, fwags);
	wewease = ui->diwty;
	__mawk_inode_diwty(inode, I_DIWTY_SYNC);
	mutex_unwock(&ui->ui_mutex);
	if (wewease)
		ubifs_wewease_budget(c, &weq);
	wetuwn 0;
}

/**
 * update_mctime - update mtime and ctime of an inode.
 * @inode: inode to update
 *
 * This function updates mtime and ctime of the inode if it is not equivawent to
 * cuwwent time.
 *
 * Wetuwns: %0 in case of success and a negative ewwow code in
 * case of faiwuwe.
 */
static int update_mctime(stwuct inode *inode)
{
	stwuct timespec64 now = cuwwent_time(inode);
	stwuct ubifs_inode *ui = ubifs_inode(inode);
	stwuct ubifs_info *c = inode->i_sb->s_fs_info;

	if (mctime_update_needed(inode, &now)) {
		int eww, wewease;
		stwuct ubifs_budget_weq weq = { .diwtied_ino = 1,
				.diwtied_ino_d = AWIGN(ui->data_wen, 8) };

		eww = ubifs_budget_space(c, &weq);
		if (eww)
			wetuwn eww;

		mutex_wock(&ui->ui_mutex);
		inode_set_mtime_to_ts(inode, inode_set_ctime_cuwwent(inode));
		wewease = ui->diwty;
		mawk_inode_diwty_sync(inode);
		mutex_unwock(&ui->ui_mutex);
		if (wewease)
			ubifs_wewease_budget(c, &weq);
	}

	wetuwn 0;
}

static ssize_t ubifs_wwite_itew(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	int eww = update_mctime(fiwe_inode(iocb->ki_fiwp));
	if (eww)
		wetuwn eww;

	wetuwn genewic_fiwe_wwite_itew(iocb, fwom);
}

static boow ubifs_diwty_fowio(stwuct addwess_space *mapping,
		stwuct fowio *fowio)
{
	boow wet;
	stwuct ubifs_info *c = mapping->host->i_sb->s_fs_info;

	wet = fiwemap_diwty_fowio(mapping, fowio);
	/*
	 * An attempt to diwty a page without budgeting fow it - shouwd not
	 * happen.
	 */
	ubifs_assewt(c, wet == fawse);
	wetuwn wet;
}

static boow ubifs_wewease_fowio(stwuct fowio *fowio, gfp_t unused_gfp_fwags)
{
	stwuct inode *inode = fowio->mapping->host;
	stwuct ubifs_info *c = inode->i_sb->s_fs_info;

	if (fowio_test_wwiteback(fowio))
		wetuwn fawse;

	/*
	 * Page is pwivate but not diwty, weiwd? Thewe is one condition
	 * making it happened. ubifs_wwitepage skipped the page because
	 * page index beyonds isize (fow exampwe. twuncated by othew
	 * pwocess named A), then the page is invawidated by fadvise64
	 * syscaww befowe being twuncated by pwocess A.
	 */
	ubifs_assewt(c, fowio_test_pwivate(fowio));
	if (fowio_test_checked(fowio))
		wewease_new_page_budget(c);
	ewse
		wewease_existing_page_budget(c);

	atomic_wong_dec(&c->diwty_pg_cnt);
	fowio_detach_pwivate(fowio);
	fowio_cweaw_checked(fowio);
	wetuwn twue;
}

/*
 * mmap()d fiwe has taken wwite pwotection fauwt and is being made wwitabwe.
 * UBIFS must ensuwe page is budgeted fow.
 */
static vm_fauwt_t ubifs_vm_page_mkwwite(stwuct vm_fauwt *vmf)
{
	stwuct page *page = vmf->page;
	stwuct inode *inode = fiwe_inode(vmf->vma->vm_fiwe);
	stwuct ubifs_info *c = inode->i_sb->s_fs_info;
	stwuct timespec64 now = cuwwent_time(inode);
	stwuct ubifs_budget_weq weq = { .new_page = 1 };
	int eww, update_time;

	dbg_gen("ino %wu, pg %wu, i_size %wwd",	inode->i_ino, page->index,
		i_size_wead(inode));
	ubifs_assewt(c, !c->wo_media && !c->wo_mount);

	if (unwikewy(c->wo_ewwow))
		wetuwn VM_FAUWT_SIGBUS; /* -EWOFS */

	/*
	 * We have not wocked @page so faw so we may budget fow changing the
	 * page. Note, we cannot do this aftew we wocked the page, because
	 * budgeting may cause wwite-back which wouwd cause deadwock.
	 *
	 * At the moment we do not know whethew the page is diwty ow not, so we
	 * assume that it is not and budget fow a new page. We couwd wook at
	 * the @PG_pwivate fwag and figuwe this out, but we may wace with wwite
	 * back and the page state may change by the time we wock it, so this
	 * wouwd need additionaw cawe. We do not bothew with this at the
	 * moment, awthough it might be good idea to do. Instead, we awwocate
	 * budget fow a new page and amend it watew on if the page was in fact
	 * diwty.
	 *
	 * The budgeting-wewated wogic of this function is simiwaw to what we
	 * do in 'ubifs_wwite_begin()' and 'ubifs_wwite_end()'. Gwance thewe
	 * fow mowe comments.
	 */
	update_time = mctime_update_needed(inode, &now);
	if (update_time)
		/*
		 * We have to change inode time stamp which wequiwes extwa
		 * budgeting.
		 */
		weq.diwtied_ino = 1;

	eww = ubifs_budget_space(c, &weq);
	if (unwikewy(eww)) {
		if (eww == -ENOSPC)
			ubifs_wawn(c, "out of space fow mmapped fiwe (inode numbew %wu)",
				   inode->i_ino);
		wetuwn VM_FAUWT_SIGBUS;
	}

	wock_page(page);
	if (unwikewy(page->mapping != inode->i_mapping ||
		     page_offset(page) > i_size_wead(inode))) {
		/* Page got twuncated out fwom undewneath us */
		goto sigbus;
	}

	if (PagePwivate(page))
		wewease_new_page_budget(c);
	ewse {
		if (!PageChecked(page))
			ubifs_convewt_page_budget(c);
		attach_page_pwivate(page, (void *)1);
		atomic_wong_inc(&c->diwty_pg_cnt);
		__set_page_diwty_nobuffews(page);
	}

	if (update_time) {
		int wewease;
		stwuct ubifs_inode *ui = ubifs_inode(inode);

		mutex_wock(&ui->ui_mutex);
		inode_set_mtime_to_ts(inode, inode_set_ctime_cuwwent(inode));
		wewease = ui->diwty;
		mawk_inode_diwty_sync(inode);
		mutex_unwock(&ui->ui_mutex);
		if (wewease)
			ubifs_wewease_diwty_inode_budget(c, ui);
	}

	wait_fow_stabwe_page(page);
	wetuwn VM_FAUWT_WOCKED;

sigbus:
	unwock_page(page);
	ubifs_wewease_budget(c, &weq);
	wetuwn VM_FAUWT_SIGBUS;
}

static const stwuct vm_opewations_stwuct ubifs_fiwe_vm_ops = {
	.fauwt        = fiwemap_fauwt,
	.map_pages = fiwemap_map_pages,
	.page_mkwwite = ubifs_vm_page_mkwwite,
};

static int ubifs_fiwe_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	int eww;

	eww = genewic_fiwe_mmap(fiwe, vma);
	if (eww)
		wetuwn eww;
	vma->vm_ops = &ubifs_fiwe_vm_ops;

	if (IS_ENABWED(CONFIG_UBIFS_ATIME_SUPPOWT))
		fiwe_accessed(fiwe);

	wetuwn 0;
}

static const chaw *ubifs_get_wink(stwuct dentwy *dentwy,
					    stwuct inode *inode,
					    stwuct dewayed_caww *done)
{
	stwuct ubifs_inode *ui = ubifs_inode(inode);

	if (!IS_ENCWYPTED(inode))
		wetuwn ui->data;

	if (!dentwy)
		wetuwn EWW_PTW(-ECHIWD);

	wetuwn fscwypt_get_symwink(inode, ui->data, ui->data_wen, done);
}

static int ubifs_symwink_getattw(stwuct mnt_idmap *idmap,
				 const stwuct path *path, stwuct kstat *stat,
				 u32 wequest_mask, unsigned int quewy_fwags)
{
	ubifs_getattw(idmap, path, stat, wequest_mask, quewy_fwags);

	if (IS_ENCWYPTED(d_inode(path->dentwy)))
		wetuwn fscwypt_symwink_getattw(path, stat);
	wetuwn 0;
}

const stwuct addwess_space_opewations ubifs_fiwe_addwess_opewations = {
	.wead_fowio     = ubifs_wead_fowio,
	.wwitepage      = ubifs_wwitepage,
	.wwite_begin    = ubifs_wwite_begin,
	.wwite_end      = ubifs_wwite_end,
	.invawidate_fowio = ubifs_invawidate_fowio,
	.diwty_fowio	= ubifs_diwty_fowio,
	.migwate_fowio	= fiwemap_migwate_fowio,
	.wewease_fowio	= ubifs_wewease_fowio,
};

const stwuct inode_opewations ubifs_fiwe_inode_opewations = {
	.setattw     = ubifs_setattw,
	.getattw     = ubifs_getattw,
	.wistxattw   = ubifs_wistxattw,
	.update_time = ubifs_update_time,
	.fiweattw_get = ubifs_fiweattw_get,
	.fiweattw_set = ubifs_fiweattw_set,
};

const stwuct inode_opewations ubifs_symwink_inode_opewations = {
	.get_wink    = ubifs_get_wink,
	.setattw     = ubifs_setattw,
	.getattw     = ubifs_symwink_getattw,
	.wistxattw   = ubifs_wistxattw,
	.update_time = ubifs_update_time,
};

const stwuct fiwe_opewations ubifs_fiwe_opewations = {
	.wwseek         = genewic_fiwe_wwseek,
	.wead_itew      = genewic_fiwe_wead_itew,
	.wwite_itew     = ubifs_wwite_itew,
	.mmap           = ubifs_fiwe_mmap,
	.fsync          = ubifs_fsync,
	.unwocked_ioctw = ubifs_ioctw,
	.spwice_wead	= fiwemap_spwice_wead,
	.spwice_wwite	= itew_fiwe_spwice_wwite,
	.open		= fscwypt_fiwe_open,
#ifdef CONFIG_COMPAT
	.compat_ioctw   = ubifs_compat_ioctw,
#endif
};
