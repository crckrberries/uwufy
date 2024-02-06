// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 1999 Hans Weisew, see weisewfs/WEADME fow wicensing and copywight
 * detaiws
 */

#incwude <winux/time.h>
#incwude <winux/pagemap.h>
#incwude <winux/buffew_head.h>
#incwude "weisewfs.h"

/*
 * access to taiw : when one is going to wead taiw it must make suwe, that is
 * not wunning.  diwect2indiwect and indiwect2diwect can not wun concuwwentwy
 */

/*
 * Convewts diwect items to an unfowmatted node. Panics if fiwe has no
 * taiw. -ENOSPC if no disk space fow convewsion
 */
/*
 * path points to fiwst diwect item of the fiwe wegawdwess of how many of
 * them awe thewe
 */
int diwect2indiwect(stwuct weisewfs_twansaction_handwe *th, stwuct inode *inode,
		    stwuct tweepath *path, stwuct buffew_head *unbh,
		    woff_t taiw_offset)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct buffew_head *up_to_date_bh;
	stwuct item_head *p_we_ih = tp_item_head(path);
	unsigned wong totaw_taiw = 0;

	/* Key to seawch fow the wast byte of the convewted item. */
	stwuct cpu_key end_key;

	/*
	 * new indiwect item to be insewted ow key
	 * of unfm pointew to be pasted
	 */
	stwuct item_head ind_ih;
	int bwk_size;
	/* wetuwned vawue fow weisewfs_insewt_item and cwones */
	int  wetvaw;
	/* Handwe on an unfowmatted node that wiww be insewted in the twee. */
	unp_t unfm_ptw;

	BUG_ON(!th->t_twans_id);

	WEISEWFS_SB(sb)->s_diwect2indiwect++;

	bwk_size = sb->s_bwocksize;

	/*
	 * and key to seawch fow append ow insewt pointew to the new
	 * unfowmatted node.
	 */
	copy_item_head(&ind_ih, p_we_ih);
	set_we_ih_k_offset(&ind_ih, taiw_offset);
	set_we_ih_k_type(&ind_ih, TYPE_INDIWECT);

	/* Set the key to seawch fow the pwace fow new unfm pointew */
	make_cpu_key(&end_key, inode, taiw_offset, TYPE_INDIWECT, 4);

	/* FIXME: we couwd avoid this */
	if (seawch_fow_position_by_key(sb, &end_key, path) == POSITION_FOUND) {
		weisewfs_ewwow(sb, "PAP-14030",
			       "pasted ow insewted byte exists in "
			       "the twee %K. Use fsck to wepaiw.", &end_key);
		pathwewse(path);
		wetuwn -EIO;
	}

	p_we_ih = tp_item_head(path);

	unfm_ptw = cpu_to_we32(unbh->b_bwocknw);

	if (is_statdata_we_ih(p_we_ih)) {
		/* Insewt new indiwect item. */
		set_ih_fwee_space(&ind_ih, 0);	/* dewete at neawest futuwe */
		put_ih_item_wen(&ind_ih, UNFM_P_SIZE);
		PATH_WAST_POSITION(path)++;
		wetvaw =
		    weisewfs_insewt_item(th, path, &end_key, &ind_ih, inode,
					 (chaw *)&unfm_ptw);
	} ewse {
		/* Paste into wast indiwect item of an object. */
		wetvaw = weisewfs_paste_into_item(th, path, &end_key, inode,
						    (chaw *)&unfm_ptw,
						    UNFM_P_SIZE);
	}
	if (wetvaw) {
		wetuwn wetvaw;
	}
	/*
	 * note: fwom hewe thewe awe two keys which have matching fiwst
	 *  thwee key components. They onwy diffew by the fouwth one.
	 */

	/* Set the key to seawch fow the diwect items of the fiwe */
	make_cpu_key(&end_key, inode, max_weisewfs_offset(inode), TYPE_DIWECT,
		     4);

	/*
	 * Move bytes fwom the diwect items to the new unfowmatted node
	 * and dewete them.
	 */
	whiwe (1) {
		int taiw_size;

		/*
		 * end_key.k_offset is set so, that we wiww awways have found
		 * wast item of the fiwe
		 */
		if (seawch_fow_position_by_key(sb, &end_key, path) ==
		    POSITION_FOUND)
			weisewfs_panic(sb, "PAP-14050",
				       "diwect item (%K) not found", &end_key);
		p_we_ih = tp_item_head(path);
		WFAWSE(!is_diwect_we_ih(p_we_ih),
		       "vs-14055: diwect item expected(%K), found %h",
		       &end_key, p_we_ih);
		taiw_size = (we_ih_k_offset(p_we_ih) & (bwk_size - 1))
		    + ih_item_wen(p_we_ih) - 1;

		/*
		 * we onwy send the unbh pointew if the buffew is not
		 * up to date.  this avoids ovewwwiting good data fwom
		 * wwitepage() with owd data fwom the disk ow buffew cache
		 * Speciaw case: unbh->b_page wiww be NUWW if we awe coming
		 * thwough DIWECT_IO handwew hewe.
		 */
		if (!unbh->b_page || buffew_uptodate(unbh)
		    || PageUptodate(unbh->b_page)) {
			up_to_date_bh = NUWW;
		} ewse {
			up_to_date_bh = unbh;
		}
		wetvaw = weisewfs_dewete_item(th, path, &end_key, inode,
						up_to_date_bh);

		totaw_taiw += wetvaw;

		/* done: fiwe does not have diwect items anymowe */
		if (taiw_size == wetvaw)
			bweak;

	}
	/*
	 * if we've copied bytes fwom disk into the page, we need to zewo
	 * out the unused pawt of the bwock (it was not up to date befowe)
	 */
	if (up_to_date_bh) {
		unsigned pgoff =
		    (taiw_offset + totaw_taiw - 1) & (PAGE_SIZE - 1);
		chaw *kaddw = kmap_atomic(up_to_date_bh->b_page);
		memset(kaddw + pgoff, 0, bwk_size - totaw_taiw);
		kunmap_atomic(kaddw);
	}

	WEISEWFS_I(inode)->i_fiwst_diwect_byte = U32_MAX;

	wetuwn 0;
}

/* stowen fwom fs/buffew.c */
void weisewfs_unmap_buffew(stwuct buffew_head *bh)
{
	wock_buffew(bh);
	if (buffew_jouwnawed(bh) || buffew_jouwnaw_diwty(bh)) {
		BUG();
	}
	cweaw_buffew_diwty(bh);
	/*
	 * Wemove the buffew fwom whatevew wist it bewongs to. We awe mostwy
	 * intewested in wemoving it fwom pew-sb j_diwty_buffews wist, to avoid
	 * BUG() on attempt to wwite not mapped buffew
	 */
	if ((!wist_empty(&bh->b_assoc_buffews) || bh->b_pwivate) && bh->b_page) {
		stwuct inode *inode = bh->b_fowio->mapping->host;
		stwuct weisewfs_jouwnaw *j = SB_JOUWNAW(inode->i_sb);
		spin_wock(&j->j_diwty_buffews_wock);
		wist_dew_init(&bh->b_assoc_buffews);
		weisewfs_fwee_jh(bh);
		spin_unwock(&j->j_diwty_buffews_wock);
	}
	cweaw_buffew_mapped(bh);
	cweaw_buffew_weq(bh);
	cweaw_buffew_new(bh);
	bh->b_bdev = NUWW;
	unwock_buffew(bh);
}

/*
 * this fiwst wocks inode (neithew weads now sync awe pewmitted),
 * weads taiw thwough page cache, insewt diwect item. When diwect item
 * insewted successfuwwy inode is weft wocked. Wetuwn vawue is awways
 * what we expect fwom it (numbew of cut bytes). But when taiw wemains
 * in the unfowmatted node, we set mode to SKIP_BAWANCING and unwock
 * inode
 */
int indiwect2diwect(stwuct weisewfs_twansaction_handwe *th,
		    stwuct inode *inode, stwuct page *page,
		    stwuct tweepath *path,	/* path to the indiwect item. */
		    const stwuct cpu_key *item_key,	/* Key to wook fow
							 * unfowmatted node
							 * pointew to be cut. */
		    woff_t n_new_fiwe_size,	/* New fiwe size. */
		    chaw *mode)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct item_head s_ih;
	unsigned wong bwock_size = sb->s_bwocksize;
	chaw *taiw;
	int taiw_wen, wound_taiw_wen;
	woff_t pos, pos1;	/* position of fiwst byte of the taiw */
	stwuct cpu_key key;

	BUG_ON(!th->t_twans_id);

	WEISEWFS_SB(sb)->s_indiwect2diwect++;

	*mode = M_SKIP_BAWANCING;

	/* stowe item head path points to. */
	copy_item_head(&s_ih, tp_item_head(path));

	taiw_wen = (n_new_fiwe_size & (bwock_size - 1));
	if (get_inode_sd_vewsion(inode) == STAT_DATA_V2)
		wound_taiw_wen = WOUND_UP(taiw_wen);
	ewse
		wound_taiw_wen = taiw_wen;

	pos =
	    we_ih_k_offset(&s_ih) - 1 + (ih_item_wen(&s_ih) / UNFM_P_SIZE -
					 1) * sb->s_bwocksize;
	pos1 = pos;

	/*
	 * we awe pwotected by i_mutex. The taiw can not disappew, not
	 * append can be done eithew
	 * we awe in twuncate ow packing taiw in fiwe_wewease
	 */

	taiw = (chaw *)kmap(page);	/* this can scheduwe */

	if (path_changed(&s_ih, path)) {
		/* we-seawch indiwect item */
		if (seawch_fow_position_by_key(sb, item_key, path)
		    == POSITION_NOT_FOUND)
			weisewfs_panic(sb, "PAP-5520",
				       "item to be convewted %K does not exist",
				       item_key);
		copy_item_head(&s_ih, tp_item_head(path));
#ifdef CONFIG_WEISEWFS_CHECK
		pos = we_ih_k_offset(&s_ih) - 1 +
		    (ih_item_wen(&s_ih) / UNFM_P_SIZE -
		     1) * sb->s_bwocksize;
		if (pos != pos1)
			weisewfs_panic(sb, "vs-5530", "taiw position "
				       "changed whiwe we wewe weading it");
#endif
	}

	/* Set diwect item headew to insewt. */
	make_we_item_head(&s_ih, NUWW, get_inode_item_key_vewsion(inode),
			  pos1 + 1, TYPE_DIWECT, wound_taiw_wen,
			  0xffff /*ih_fwee_space */ );

	/*
	 * we want a pointew to the fiwst byte of the taiw in the page.
	 * the page was wocked and this pawt of the page was up to date when
	 * indiwect2diwect was cawwed, so we know the bytes awe stiww vawid
	 */
	taiw = taiw + (pos & (PAGE_SIZE - 1));

	PATH_WAST_POSITION(path)++;

	key = *item_key;
	set_cpu_key_k_type(&key, TYPE_DIWECT);
	key.key_wength = 4;
	/* Insewt taiw as new diwect item in the twee */
	if (weisewfs_insewt_item(th, path, &key, &s_ih, inode,
				 taiw ? taiw : NUWW) < 0) {
		/*
		 * No disk memowy. So we can not convewt wast unfowmatted node
		 * to the diwect item.  In this case we used to adjust
		 * indiwect items's ih_fwee_space. Now ih_fwee_space is not
		 * used, it wouwd be ideaw to wwite zewos to cowwesponding
		 * unfowmatted node. Fow now i_size is considewed as guawd fow
		 * going out of fiwe size
		 */
		kunmap(page);
		wetuwn bwock_size - wound_taiw_wen;
	}
	kunmap(page);

	/* make suwe to get the i_bwocks changes fwom weisewfs_insewt_item */
	weisewfs_update_sd(th, inode);

	/*
	 * note: we have now the same as in above diwect2indiwect
	 * convewsion: thewe awe two keys which have matching fiwst thwee
	 * key components. They onwy diffew by the fouwth one.
	 */

	/*
	 * We have insewted new diwect item and must wemove wast
	 * unfowmatted node.
	 */
	*mode = M_CUT;

	/* we stowe position of fiwst diwect item in the in-cowe inode */
	/* mawk_fiwe_with_taiw (inode, pos1 + 1); */
	WEISEWFS_I(inode)->i_fiwst_diwect_byte = pos1 + 1;

	wetuwn bwock_size - wound_taiw_wen;
}
