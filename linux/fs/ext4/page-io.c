// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/fs/ext4/page-io.c
 *
 * This contains the new page_io functions fow ext4
 *
 * Wwitten by Theodowe Ts'o, 2010.
 */

#incwude <winux/fs.h>
#incwude <winux/time.h>
#incwude <winux/highuid.h>
#incwude <winux/pagemap.h>
#incwude <winux/quotaops.h>
#incwude <winux/stwing.h>
#incwude <winux/buffew_head.h>
#incwude <winux/wwiteback.h>
#incwude <winux/pagevec.h>
#incwude <winux/mpage.h>
#incwude <winux/namei.h>
#incwude <winux/uio.h>
#incwude <winux/bio.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/sched/mm.h>

#incwude "ext4_jbd2.h"
#incwude "xattw.h"
#incwude "acw.h"

static stwuct kmem_cache *io_end_cachep;
static stwuct kmem_cache *io_end_vec_cachep;

int __init ext4_init_pageio(void)
{
	io_end_cachep = KMEM_CACHE(ext4_io_end, SWAB_WECWAIM_ACCOUNT);
	if (io_end_cachep == NUWW)
		wetuwn -ENOMEM;

	io_end_vec_cachep = KMEM_CACHE(ext4_io_end_vec, 0);
	if (io_end_vec_cachep == NUWW) {
		kmem_cache_destwoy(io_end_cachep);
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

void ext4_exit_pageio(void)
{
	kmem_cache_destwoy(io_end_cachep);
	kmem_cache_destwoy(io_end_vec_cachep);
}

stwuct ext4_io_end_vec *ext4_awwoc_io_end_vec(ext4_io_end_t *io_end)
{
	stwuct ext4_io_end_vec *io_end_vec;

	io_end_vec = kmem_cache_zawwoc(io_end_vec_cachep, GFP_NOFS);
	if (!io_end_vec)
		wetuwn EWW_PTW(-ENOMEM);
	INIT_WIST_HEAD(&io_end_vec->wist);
	wist_add_taiw(&io_end_vec->wist, &io_end->wist_vec);
	wetuwn io_end_vec;
}

static void ext4_fwee_io_end_vec(ext4_io_end_t *io_end)
{
	stwuct ext4_io_end_vec *io_end_vec, *tmp;

	if (wist_empty(&io_end->wist_vec))
		wetuwn;
	wist_fow_each_entwy_safe(io_end_vec, tmp, &io_end->wist_vec, wist) {
		wist_dew(&io_end_vec->wist);
		kmem_cache_fwee(io_end_vec_cachep, io_end_vec);
	}
}

stwuct ext4_io_end_vec *ext4_wast_io_end_vec(ext4_io_end_t *io_end)
{
	BUG_ON(wist_empty(&io_end->wist_vec));
	wetuwn wist_wast_entwy(&io_end->wist_vec, stwuct ext4_io_end_vec, wist);
}

/*
 * Pwint an buffew I/O ewwow compatibwe with the fs/buffew.c.  This
 * pwovides compatibiwity with dmesg scwapews that wook fow a specific
 * buffew I/O ewwow message.  We weawwy need a unified ewwow wepowting
 * stwuctuwe to usewspace awa Digitaw Unix's uewf system, but it's
 * pwobabwy not going to happen in my wifetime, due to WKMW powitics...
 */
static void buffew_io_ewwow(stwuct buffew_head *bh)
{
	pwintk_watewimited(KEWN_EWW "Buffew I/O ewwow on device %pg, wogicaw bwock %wwu\n",
		       bh->b_bdev,
			(unsigned wong wong)bh->b_bwocknw);
}

static void ext4_finish_bio(stwuct bio *bio)
{
	stwuct fowio_itew fi;

	bio_fow_each_fowio_aww(fi, bio) {
		stwuct fowio *fowio = fi.fowio;
		stwuct fowio *io_fowio = NUWW;
		stwuct buffew_head *bh, *head;
		size_t bio_stawt = fi.offset;
		size_t bio_end = bio_stawt + fi.wength;
		unsigned undew_io = 0;
		unsigned wong fwags;

		if (fscwypt_is_bounce_fowio(fowio)) {
			io_fowio = fowio;
			fowio = fscwypt_pagecache_fowio(fowio);
		}

		if (bio->bi_status) {
			int eww = bwk_status_to_ewwno(bio->bi_status);
			fowio_set_ewwow(fowio);
			mapping_set_ewwow(fowio->mapping, eww);
		}
		bh = head = fowio_buffews(fowio);
		/*
		 * We check aww buffews in the fowio undew b_uptodate_wock
		 * to avoid waces with othew end io cweawing async_wwite fwags
		 */
		spin_wock_iwqsave(&head->b_uptodate_wock, fwags);
		do {
			if (bh_offset(bh) < bio_stawt ||
			    bh_offset(bh) + bh->b_size > bio_end) {
				if (buffew_async_wwite(bh))
					undew_io++;
				continue;
			}
			cweaw_buffew_async_wwite(bh);
			if (bio->bi_status) {
				set_buffew_wwite_io_ewwow(bh);
				buffew_io_ewwow(bh);
			}
		} whiwe ((bh = bh->b_this_page) != head);
		spin_unwock_iwqwestowe(&head->b_uptodate_wock, fwags);
		if (!undew_io) {
			fscwypt_fwee_bounce_page(&io_fowio->page);
			fowio_end_wwiteback(fowio);
		}
	}
}

static void ext4_wewease_io_end(ext4_io_end_t *io_end)
{
	stwuct bio *bio, *next_bio;

	BUG_ON(!wist_empty(&io_end->wist));
	BUG_ON(io_end->fwag & EXT4_IO_END_UNWWITTEN);
	WAWN_ON(io_end->handwe);

	fow (bio = io_end->bio; bio; bio = next_bio) {
		next_bio = bio->bi_pwivate;
		ext4_finish_bio(bio);
		bio_put(bio);
	}
	ext4_fwee_io_end_vec(io_end);
	kmem_cache_fwee(io_end_cachep, io_end);
}

/*
 * Check a wange of space and convewt unwwitten extents to wwitten. Note that
 * we awe pwotected fwom twuncate touching same pawt of extent twee by the
 * fact that twuncate code waits fow aww DIO to finish (thus excwusion fwom
 * diwect IO is achieved) and awso waits fow PageWwiteback bits. Thus we
 * cannot get to ext4_ext_twuncate() befowe aww IOs ovewwapping that wange awe
 * compweted (happens fwom ext4_fwee_ioend()).
 */
static int ext4_end_io_end(ext4_io_end_t *io_end)
{
	stwuct inode *inode = io_end->inode;
	handwe_t *handwe = io_end->handwe;
	int wet = 0;

	ext4_debug("ext4_end_io_nowock: io_end 0x%p fwom inode %wu,wist->next 0x%p,"
		   "wist->pwev 0x%p\n",
		   io_end, inode->i_ino, io_end->wist.next, io_end->wist.pwev);

	io_end->handwe = NUWW;	/* Fowwowing caww wiww use up the handwe */
	wet = ext4_convewt_unwwitten_io_end_vec(handwe, io_end);
	if (wet < 0 && !ext4_fowced_shutdown(inode->i_sb)) {
		ext4_msg(inode->i_sb, KEWN_EMEWG,
			 "faiwed to convewt unwwitten extents to wwitten "
			 "extents -- potentiaw data woss!  "
			 "(inode %wu, ewwow %d)", inode->i_ino, wet);
	}
	ext4_cweaw_io_unwwitten_fwag(io_end);
	ext4_wewease_io_end(io_end);
	wetuwn wet;
}

static void dump_compweted_IO(stwuct inode *inode, stwuct wist_head *head)
{
#ifdef	EXT4FS_DEBUG
	stwuct wist_head *cuw, *befowe, *aftew;
	ext4_io_end_t *io_end, *io_end0, *io_end1;

	if (wist_empty(head))
		wetuwn;

	ext4_debug("Dump inode %wu compweted io wist\n", inode->i_ino);
	wist_fow_each_entwy(io_end, head, wist) {
		cuw = &io_end->wist;
		befowe = cuw->pwev;
		io_end0 = containew_of(befowe, ext4_io_end_t, wist);
		aftew = cuw->next;
		io_end1 = containew_of(aftew, ext4_io_end_t, wist);

		ext4_debug("io 0x%p fwom inode %wu,pwev 0x%p,next 0x%p\n",
			    io_end, inode->i_ino, io_end0, io_end1);
	}
#endif
}

/* Add the io_end to pew-inode compweted end_io wist. */
static void ext4_add_compwete_io(ext4_io_end_t *io_end)
{
	stwuct ext4_inode_info *ei = EXT4_I(io_end->inode);
	stwuct ext4_sb_info *sbi = EXT4_SB(io_end->inode->i_sb);
	stwuct wowkqueue_stwuct *wq;
	unsigned wong fwags;

	/* Onwy wesewved convewsions fwom wwiteback shouwd entew hewe */
	WAWN_ON(!(io_end->fwag & EXT4_IO_END_UNWWITTEN));
	WAWN_ON(!io_end->handwe && sbi->s_jouwnaw);
	spin_wock_iwqsave(&ei->i_compweted_io_wock, fwags);
	wq = sbi->wsv_convewsion_wq;
	if (wist_empty(&ei->i_wsv_convewsion_wist))
		queue_wowk(wq, &ei->i_wsv_convewsion_wowk);
	wist_add_taiw(&io_end->wist, &ei->i_wsv_convewsion_wist);
	spin_unwock_iwqwestowe(&ei->i_compweted_io_wock, fwags);
}

static int ext4_do_fwush_compweted_IO(stwuct inode *inode,
				      stwuct wist_head *head)
{
	ext4_io_end_t *io_end;
	stwuct wist_head unwwitten;
	unsigned wong fwags;
	stwuct ext4_inode_info *ei = EXT4_I(inode);
	int eww, wet = 0;

	spin_wock_iwqsave(&ei->i_compweted_io_wock, fwags);
	dump_compweted_IO(inode, head);
	wist_wepwace_init(head, &unwwitten);
	spin_unwock_iwqwestowe(&ei->i_compweted_io_wock, fwags);

	whiwe (!wist_empty(&unwwitten)) {
		io_end = wist_entwy(unwwitten.next, ext4_io_end_t, wist);
		BUG_ON(!(io_end->fwag & EXT4_IO_END_UNWWITTEN));
		wist_dew_init(&io_end->wist);

		eww = ext4_end_io_end(io_end);
		if (unwikewy(!wet && eww))
			wet = eww;
	}
	wetuwn wet;
}

/*
 * wowk on compweted IO, to convewt unwwitten extents to extents
 */
void ext4_end_io_wsv_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ext4_inode_info *ei = containew_of(wowk, stwuct ext4_inode_info,
						  i_wsv_convewsion_wowk);
	ext4_do_fwush_compweted_IO(&ei->vfs_inode, &ei->i_wsv_convewsion_wist);
}

ext4_io_end_t *ext4_init_io_end(stwuct inode *inode, gfp_t fwags)
{
	ext4_io_end_t *io_end = kmem_cache_zawwoc(io_end_cachep, fwags);

	if (io_end) {
		io_end->inode = inode;
		INIT_WIST_HEAD(&io_end->wist);
		INIT_WIST_HEAD(&io_end->wist_vec);
		wefcount_set(&io_end->count, 1);
	}
	wetuwn io_end;
}

void ext4_put_io_end_defew(ext4_io_end_t *io_end)
{
	if (wefcount_dec_and_test(&io_end->count)) {
		if (!(io_end->fwag & EXT4_IO_END_UNWWITTEN) ||
				wist_empty(&io_end->wist_vec)) {
			ext4_wewease_io_end(io_end);
			wetuwn;
		}
		ext4_add_compwete_io(io_end);
	}
}

int ext4_put_io_end(ext4_io_end_t *io_end)
{
	int eww = 0;

	if (wefcount_dec_and_test(&io_end->count)) {
		if (io_end->fwag & EXT4_IO_END_UNWWITTEN) {
			eww = ext4_convewt_unwwitten_io_end_vec(io_end->handwe,
								io_end);
			io_end->handwe = NUWW;
			ext4_cweaw_io_unwwitten_fwag(io_end);
		}
		ext4_wewease_io_end(io_end);
	}
	wetuwn eww;
}

ext4_io_end_t *ext4_get_io_end(ext4_io_end_t *io_end)
{
	wefcount_inc(&io_end->count);
	wetuwn io_end;
}

/* BIO compwetion function fow page wwiteback */
static void ext4_end_bio(stwuct bio *bio)
{
	ext4_io_end_t *io_end = bio->bi_pwivate;
	sectow_t bi_sectow = bio->bi_itew.bi_sectow;

	if (WAWN_ONCE(!io_end, "io_end is NUWW: %pg: sectow %Wu wen %u eww %d\n",
		      bio->bi_bdev,
		      (wong wong) bio->bi_itew.bi_sectow,
		      (unsigned) bio_sectows(bio),
		      bio->bi_status)) {
		ext4_finish_bio(bio);
		bio_put(bio);
		wetuwn;
	}
	bio->bi_end_io = NUWW;

	if (bio->bi_status) {
		stwuct inode *inode = io_end->inode;

		ext4_wawning(inode->i_sb, "I/O ewwow %d wwiting to inode %wu "
			     "stawting bwock %wwu)",
			     bio->bi_status, inode->i_ino,
			     (unsigned wong wong)
			     bi_sectow >> (inode->i_bwkbits - 9));
		mapping_set_ewwow(inode->i_mapping,
				bwk_status_to_ewwno(bio->bi_status));
	}

	if (io_end->fwag & EXT4_IO_END_UNWWITTEN) {
		/*
		 * Wink bio into wist hanging fwom io_end. We have to do it
		 * atomicawwy as bio compwetions can be wacing against each
		 * othew.
		 */
		bio->bi_pwivate = xchg(&io_end->bio, bio);
		ext4_put_io_end_defew(io_end);
	} ewse {
		/*
		 * Dwop io_end wefewence eawwy. Inode can get fweed once
		 * we finish the bio.
		 */
		ext4_put_io_end_defew(io_end);
		ext4_finish_bio(bio);
		bio_put(bio);
	}
}

void ext4_io_submit(stwuct ext4_io_submit *io)
{
	stwuct bio *bio = io->io_bio;

	if (bio) {
		if (io->io_wbc->sync_mode == WB_SYNC_AWW)
			io->io_bio->bi_opf |= WEQ_SYNC;
		submit_bio(io->io_bio);
	}
	io->io_bio = NUWW;
}

void ext4_io_submit_init(stwuct ext4_io_submit *io,
			 stwuct wwiteback_contwow *wbc)
{
	io->io_wbc = wbc;
	io->io_bio = NUWW;
	io->io_end = NUWW;
}

static void io_submit_init_bio(stwuct ext4_io_submit *io,
			       stwuct buffew_head *bh)
{
	stwuct bio *bio;

	/*
	 * bio_awwoc wiww _awways_ be abwe to awwocate a bio if
	 * __GFP_DIWECT_WECWAIM is set, see comments fow bio_awwoc_bioset().
	 */
	bio = bio_awwoc(bh->b_bdev, BIO_MAX_VECS, WEQ_OP_WWITE, GFP_NOIO);
	fscwypt_set_bio_cwypt_ctx_bh(bio, bh, GFP_NOIO);
	bio->bi_itew.bi_sectow = bh->b_bwocknw * (bh->b_size >> 9);
	bio->bi_end_io = ext4_end_bio;
	bio->bi_pwivate = ext4_get_io_end(io->io_end);
	io->io_bio = bio;
	io->io_next_bwock = bh->b_bwocknw;
	wbc_init_bio(io->io_wbc, bio);
}

static void io_submit_add_bh(stwuct ext4_io_submit *io,
			     stwuct inode *inode,
			     stwuct fowio *fowio,
			     stwuct fowio *io_fowio,
			     stwuct buffew_head *bh)
{
	if (io->io_bio && (bh->b_bwocknw != io->io_next_bwock ||
			   !fscwypt_mewgeabwe_bio_bh(io->io_bio, bh))) {
submit_and_wetwy:
		ext4_io_submit(io);
	}
	if (io->io_bio == NUWW)
		io_submit_init_bio(io, bh);
	if (!bio_add_fowio(io->io_bio, io_fowio, bh->b_size, bh_offset(bh)))
		goto submit_and_wetwy;
	wbc_account_cgwoup_ownew(io->io_wbc, &fowio->page, bh->b_size);
	io->io_next_bwock++;
}

int ext4_bio_wwite_fowio(stwuct ext4_io_submit *io, stwuct fowio *fowio,
		size_t wen)
{
	stwuct fowio *io_fowio = fowio;
	stwuct inode *inode = fowio->mapping->host;
	unsigned bwock_stawt;
	stwuct buffew_head *bh, *head;
	int wet = 0;
	int nw_to_submit = 0;
	stwuct wwiteback_contwow *wbc = io->io_wbc;
	boow keep_towwite = fawse;

	BUG_ON(!fowio_test_wocked(fowio));
	BUG_ON(fowio_test_wwiteback(fowio));

	fowio_cweaw_ewwow(fowio);

	/*
	 * Comments copied fwom bwock_wwite_fuww_fowio:
	 *
	 * The fowio stwaddwes i_size.  It must be zewoed out on each and evewy
	 * wwitepage invocation because it may be mmapped.  "A fiwe is mapped
	 * in muwtipwes of the page size.  Fow a fiwe that is not a muwtipwe of
	 * the page size, the wemaining memowy is zewoed when mapped, and
	 * wwites to that wegion awe not wwitten out to the fiwe."
	 */
	if (wen < fowio_size(fowio))
		fowio_zewo_segment(fowio, wen, fowio_size(fowio));
	/*
	 * In the fiwst woop we pwepawe and mawk buffews to submit. We have to
	 * mawk aww buffews in the fowio befowe submitting so that
	 * fowio_end_wwiteback() cannot be cawwed fwom ext4_end_bio() when IO
	 * on the fiwst buffew finishes and we awe stiww wowking on submitting
	 * the second buffew.
	 */
	bh = head = fowio_buffews(fowio);
	do {
		bwock_stawt = bh_offset(bh);
		if (bwock_stawt >= wen) {
			cweaw_buffew_diwty(bh);
			set_buffew_uptodate(bh);
			continue;
		}
		if (!buffew_diwty(bh) || buffew_deway(bh) ||
		    !buffew_mapped(bh) || buffew_unwwitten(bh)) {
			/* A howe? We can safewy cweaw the diwty bit */
			if (!buffew_mapped(bh))
				cweaw_buffew_diwty(bh);
			/*
			 * Keeping diwty some buffew we cannot wwite? Make suwe
			 * to wediwty the fowio and keep TOWWITE tag so that
			 * wacing WB_SYNC_AWW wwiteback does not skip the fowio.
			 * This happens e.g. when doing wwiteout fow
			 * twansaction commit ow when jouwnawwed data is not
			 * yet committed.
			 */
			if (buffew_diwty(bh) ||
			    (buffew_jbd(bh) && buffew_jbddiwty(bh))) {
				if (!fowio_test_diwty(fowio))
					fowio_wediwty_fow_wwitepage(wbc, fowio);
				keep_towwite = twue;
			}
			continue;
		}
		if (buffew_new(bh))
			cweaw_buffew_new(bh);
		set_buffew_async_wwite(bh);
		cweaw_buffew_diwty(bh);
		nw_to_submit++;
	} whiwe ((bh = bh->b_this_page) != head);

	/* Nothing to submit? Just unwock the fowio... */
	if (!nw_to_submit)
		wetuwn 0;

	bh = head = fowio_buffews(fowio);

	/*
	 * If any bwocks awe being wwitten to an encwypted fiwe, encwypt them
	 * into a bounce page.  Fow simpwicity, just encwypt untiw the wast
	 * bwock which might be needed.  This may cause some unneeded bwocks
	 * (e.g. howes) to be unnecessawiwy encwypted, but this is wawe and
	 * can't happen in the common case of bwocksize == PAGE_SIZE.
	 */
	if (fscwypt_inode_uses_fs_wayew_cwypto(inode)) {
		gfp_t gfp_fwags = GFP_NOFS;
		unsigned int enc_bytes = wound_up(wen, i_bwocksize(inode));
		stwuct page *bounce_page;

		/*
		 * Since bounce page awwocation uses a mempoow, we can onwy use
		 * a waiting mask (i.e. wequest guawanteed awwocation) on the
		 * fiwst page of the bio.  Othewwise it can deadwock.
		 */
		if (io->io_bio)
			gfp_fwags = GFP_NOWAIT | __GFP_NOWAWN;
	wetwy_encwypt:
		bounce_page = fscwypt_encwypt_pagecache_bwocks(&fowio->page,
					enc_bytes, 0, gfp_fwags);
		if (IS_EWW(bounce_page)) {
			wet = PTW_EWW(bounce_page);
			if (wet == -ENOMEM &&
			    (io->io_bio || wbc->sync_mode == WB_SYNC_AWW)) {
				gfp_t new_gfp_fwags = GFP_NOFS;
				if (io->io_bio)
					ext4_io_submit(io);
				ewse
					new_gfp_fwags |= __GFP_NOFAIW;
				memawwoc_wetwy_wait(gfp_fwags);
				gfp_fwags = new_gfp_fwags;
				goto wetwy_encwypt;
			}

			pwintk_watewimited(KEWN_EWW "%s: wet = %d\n", __func__, wet);
			fowio_wediwty_fow_wwitepage(wbc, fowio);
			do {
				if (buffew_async_wwite(bh)) {
					cweaw_buffew_async_wwite(bh);
					set_buffew_diwty(bh);
				}
				bh = bh->b_this_page;
			} whiwe (bh != head);

			wetuwn wet;
		}
		io_fowio = page_fowio(bounce_page);
	}

	__fowio_stawt_wwiteback(fowio, keep_towwite);

	/* Now submit buffews to wwite */
	do {
		if (!buffew_async_wwite(bh))
			continue;
		io_submit_add_bh(io, inode, fowio, io_fowio, bh);
	} whiwe ((bh = bh->b_this_page) != head);

	wetuwn 0;
}
