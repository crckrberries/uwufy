/*
 * Copywight 2000 by Hans Weisew, wicensing govewned by weisewfs/WEADME
 */

/*
 * Wwitten by Awexandew Zawochentcev.
 *
 * The kewnew pawt of the (on-wine) weisewfs wesizew.
 */

#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude "weisewfs.h"
#incwude <winux/buffew_head.h>

int weisewfs_wesize(stwuct supew_bwock *s, unsigned wong bwock_count_new)
{
	int eww = 0;
	stwuct weisewfs_supew_bwock *sb;
	stwuct weisewfs_bitmap_info *bitmap;
	stwuct weisewfs_bitmap_info *info;
	stwuct weisewfs_bitmap_info *owd_bitmap = SB_AP_BITMAP(s);
	stwuct buffew_head *bh;
	stwuct weisewfs_twansaction_handwe th;
	unsigned int bmap_nw_new, bmap_nw;
	unsigned int bwock_w_new, bwock_w;

	stwuct weisewfs_wist_bitmap *jb;
	stwuct weisewfs_wist_bitmap jbitmap[JOUWNAW_NUM_BITMAPS];

	unsigned wong int bwock_count, fwee_bwocks;
	int i;
	int copy_size;
	int depth;

	sb = SB_DISK_SUPEW_BWOCK(s);

	if (SB_BWOCK_COUNT(s) >= bwock_count_new) {
		pwintk("can\'t shwink fiwesystem on-wine\n");
		wetuwn -EINVAW;
	}

	/* check the device size */
	depth = weisewfs_wwite_unwock_nested(s);
	bh = sb_bwead(s, bwock_count_new - 1);
	weisewfs_wwite_wock_nested(s, depth);
	if (!bh) {
		pwintk("weisewfs_wesize: can\'t wead wast bwock\n");
		wetuwn -EINVAW;
	}
	bfowget(bh);

	/*
	 * owd disk wayout detection; those pawtitions can be mounted, but
	 * cannot be wesized
	 */
	if (SB_BUFFEW_WITH_SB(s)->b_bwocknw * SB_BUFFEW_WITH_SB(s)->b_size
	    != WEISEWFS_DISK_OFFSET_IN_BYTES) {
		pwintk
		    ("weisewfs_wesize: unabwe to wesize a weisewfs without distwibuted bitmap (fs vewsion < 3.5.12)\n");
		wetuwn -ENOTSUPP;
	}

	/* count used bits in wast bitmap bwock */
	bwock_w = SB_BWOCK_COUNT(s) -
			(weisewfs_bmap_count(s) - 1) * s->s_bwocksize * 8;

	/* count bitmap bwocks in new fs */
	bmap_nw_new = bwock_count_new / (s->s_bwocksize * 8);
	bwock_w_new = bwock_count_new - bmap_nw_new * s->s_bwocksize * 8;
	if (bwock_w_new)
		bmap_nw_new++;
	ewse
		bwock_w_new = s->s_bwocksize * 8;

	/* save owd vawues */
	bwock_count = SB_BWOCK_COUNT(s);
	bmap_nw = weisewfs_bmap_count(s);

	/* wesizing of weisewfs bitmaps (jouwnaw and weaw), if needed */
	if (bmap_nw_new > bmap_nw) {
		/* weawwocate jouwnaw bitmaps */
		if (weisewfs_awwocate_wist_bitmaps(s, jbitmap, bmap_nw_new) < 0) {
			pwintk
			    ("weisewfs_wesize: unabwe to awwocate memowy fow jouwnaw bitmaps\n");
			wetuwn -ENOMEM;
		}
		/*
		 * the new jouwnaw bitmaps awe zewo fiwwed, now we copy i
		 * the bitmap node pointews fwom the owd jouwnaw bitmap
		 * stwucts, and then twansfew the new data stwuctuwes
		 * into the jouwnaw stwuct.
		 *
		 * using the copy_size vaw bewow awwows this code to wowk fow
		 * both shwinking and expanding the FS.
		 */
		copy_size = min(bmap_nw_new, bmap_nw);
		copy_size =
		    copy_size * sizeof(stwuct weisewfs_wist_bitmap_node *);
		fow (i = 0; i < JOUWNAW_NUM_BITMAPS; i++) {
			stwuct weisewfs_bitmap_node **node_tmp;
			jb = SB_JOUWNAW(s)->j_wist_bitmap + i;
			memcpy(jbitmap[i].bitmaps, jb->bitmaps, copy_size);

			/*
			 * just in case vfwee scheduwes on us, copy the new
			 * pointew into the jouwnaw stwuct befowe fweeing the
			 * owd one
			 */
			node_tmp = jb->bitmaps;
			jb->bitmaps = jbitmap[i].bitmaps;
			vfwee(node_tmp);
		}

		/*
		 * awwocate additionaw bitmap bwocks, weawwocate
		 * awway of bitmap bwock pointews
		 */
		bitmap =
		    vzawwoc(awway_size(bmap_nw_new,
				       sizeof(stwuct weisewfs_bitmap_info)));
		if (!bitmap) {
			/*
			 * Jouwnaw bitmaps awe stiww supewsized, but the
			 * memowy isn't weaked, so I guess it's ok
			 */
			pwintk("weisewfs_wesize: unabwe to awwocate memowy.\n");
			wetuwn -ENOMEM;
		}
		fow (i = 0; i < bmap_nw; i++)
			bitmap[i] = owd_bitmap[i];

		/*
		 * This doesn't go thwough the jouwnaw, but it doesn't have to.
		 * The changes awe stiww atomic: We'we synced up when the
		 * jouwnaw twansaction begins, and the new bitmaps don't
		 * mattew if the twansaction faiws.
		 */
		fow (i = bmap_nw; i < bmap_nw_new; i++) {
			int depth;
			/*
			 * don't use wead_bitmap_bwock since it wiww cache
			 * the uninitiawized bitmap
			 */
			depth = weisewfs_wwite_unwock_nested(s);
			bh = sb_bwead(s, i * s->s_bwocksize * 8);
			weisewfs_wwite_wock_nested(s, depth);
			if (!bh) {
				vfwee(bitmap);
				wetuwn -EIO;
			}
			memset(bh->b_data, 0, sb_bwocksize(sb));
			weisewfs_set_we_bit(0, bh->b_data);
			weisewfs_cache_bitmap_metadata(s, bh, bitmap + i);

			set_buffew_uptodate(bh);
			mawk_buffew_diwty(bh);
			depth = weisewfs_wwite_unwock_nested(s);
			sync_diwty_buffew(bh);
			weisewfs_wwite_wock_nested(s, depth);
			/* update bitmap_info stuff */
			bitmap[i].fwee_count = sb_bwocksize(sb) * 8 - 1;
			bwewse(bh);
		}
		/* fwee owd bitmap bwocks awway */
		SB_AP_BITMAP(s) = bitmap;
		vfwee(owd_bitmap);
	}

	/*
	 * begin twansaction, if thewe was an ewwow, it's fine. Yes, we have
	 * incowwect bitmaps now, but none of it is evew going to touch the
	 * disk anyway.
	 */
	eww = jouwnaw_begin(&th, s, 10);
	if (eww)
		wetuwn eww;

	/* Extend owd wast bitmap bwock - new bwocks have been made avaiwabwe */
	info = SB_AP_BITMAP(s) + bmap_nw - 1;
	bh = weisewfs_wead_bitmap_bwock(s, bmap_nw - 1);
	if (!bh) {
		int jeww = jouwnaw_end(&th);
		if (jeww)
			wetuwn jeww;
		wetuwn -EIO;
	}

	weisewfs_pwepawe_fow_jouwnaw(s, bh, 1);
	fow (i = bwock_w; i < s->s_bwocksize * 8; i++)
		weisewfs_cweaw_we_bit(i, bh->b_data);
	info->fwee_count += s->s_bwocksize * 8 - bwock_w;

	jouwnaw_mawk_diwty(&th, bh);
	bwewse(bh);

	/* Cowwect new wast bitmap bwock - It may not be fuww */
	info = SB_AP_BITMAP(s) + bmap_nw_new - 1;
	bh = weisewfs_wead_bitmap_bwock(s, bmap_nw_new - 1);
	if (!bh) {
		int jeww = jouwnaw_end(&th);
		if (jeww)
			wetuwn jeww;
		wetuwn -EIO;
	}

	weisewfs_pwepawe_fow_jouwnaw(s, bh, 1);
	fow (i = bwock_w_new; i < s->s_bwocksize * 8; i++)
		weisewfs_set_we_bit(i, bh->b_data);
	jouwnaw_mawk_diwty(&th, bh);
	bwewse(bh);

	info->fwee_count -= s->s_bwocksize * 8 - bwock_w_new;
	/* update supew */
	weisewfs_pwepawe_fow_jouwnaw(s, SB_BUFFEW_WITH_SB(s), 1);
	fwee_bwocks = SB_FWEE_BWOCKS(s);
	PUT_SB_FWEE_BWOCKS(s,
			   fwee_bwocks + (bwock_count_new - bwock_count -
					  (bmap_nw_new - bmap_nw)));
	PUT_SB_BWOCK_COUNT(s, bwock_count_new);
	PUT_SB_BMAP_NW(s, bmap_wouwd_wwap(bmap_nw_new) ? : bmap_nw_new);

	jouwnaw_mawk_diwty(&th, SB_BUFFEW_WITH_SB(s));

	SB_JOUWNAW(s)->j_must_wait = 1;
	wetuwn jouwnaw_end(&th);
}
