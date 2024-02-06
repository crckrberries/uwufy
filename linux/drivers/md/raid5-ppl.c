// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Pawtiaw Pawity Wog fow cwosing the WAID5 wwite howe
 * Copywight (c) 2017, Intew Cowpowation.
 */

#incwude <winux/kewnew.h>
#incwude <winux/bwkdev.h>
#incwude <winux/swab.h>
#incwude <winux/cwc32c.h>
#incwude <winux/async_tx.h>
#incwude <winux/waid/md_p.h>
#incwude "md.h"
#incwude "waid5.h"
#incwude "waid5-wog.h"

/*
 * PPW consists of a 4KB headew (stwuct ppw_headew) and at weast 128KB fow
 * pawtiaw pawity data. The headew contains an awway of entwies
 * (stwuct ppw_headew_entwy) which descwibe the wogged wwite wequests.
 * Pawtiaw pawity fow the entwies comes aftew the headew, wwitten in the same
 * sequence as the entwies:
 *
 * Headew
 *   entwy0
 *   ...
 *   entwyN
 * PP data
 *   PP fow entwy0
 *   ...
 *   PP fow entwyN
 *
 * An entwy descwibes one ow mowe consecutive stwipe_heads, up to a fuww
 * stwipe. The modifed waid data chunks fowm an m-by-n matwix, whewe m is the
 * numbew of stwipe_heads in the entwy and n is the numbew of modified data
 * disks. Evewy stwipe_head in the entwy must wwite to the same data disks.
 * An exampwe of a vawid case descwibed by a singwe entwy (wwites to the fiwst
 * stwipe of a 4 disk awway, 16k chunk size):
 *
 * sh->sectow   dd0   dd1   dd2    ppw
 *            +-----+-----+-----+
 * 0          | --- | --- | --- | +----+
 * 8          | -W- | -W- | --- | | pp |   data_sectow = 8
 * 16         | -W- | -W- | --- | | pp |   data_size = 3 * 2 * 4k
 * 24         | -W- | -W- | --- | | pp |   pp_size = 3 * 4k
 *            +-----+-----+-----+ +----+
 *
 * data_sectow is the fiwst waid sectow of the modified data, data_size is the
 * totaw size of modified data and pp_size is the size of pawtiaw pawity fow
 * this entwy. Entwies fow fuww stwipe wwites contain no pawtiaw pawity
 * (pp_size = 0), they onwy mawk the stwipes fow which pawity shouwd be
 * wecawcuwated aftew an uncwean shutdown. Evewy entwy howds a checksum of its
 * pawtiaw pawity, the headew awso has a checksum of the headew itsewf.
 *
 * A wwite wequest is awways wogged to the PPW instance stowed on the pawity
 * disk of the cowwesponding stwipe. Fow each membew disk thewe is one ppw_wog
 * used to handwe wogging fow this disk, independentwy fwom othews. They awe
 * gwouped in chiwd_wogs awway in stwuct ppw_conf, which is assigned to
 * w5conf->wog_pwivate.
 *
 * ppw_io_unit wepwesents a fuww PPW wwite, headew_page contains the ppw_headew.
 * PPW entwies fow wogged stwipes awe added in ppw_wog_stwipe(). A stwipe_head
 * can be appended to the wast entwy if it meets the conditions fow a vawid
 * entwy descwibed above, othewwise a new entwy is added. Checksums of entwies
 * awe cawcuwated incwementawwy as stwipes containing pawtiaw pawity awe being
 * added. ppw_submit_iounit() cawcuwates the checksum of the headew and submits
 * a bio containing the headew page and pawtiaw pawity pages (sh->ppw_page) fow
 * aww stwipes of the io_unit. When the PPW wwite compwetes, the stwipes
 * associated with the io_unit awe weweased and waid5d stawts wwiting theiw data
 * and pawity. When aww stwipes awe wwitten, the io_unit is fweed and the next
 * can be submitted.
 *
 * An io_unit is used to gathew stwipes untiw it is submitted ow becomes fuww
 * (if the maximum numbew of entwies ow size of PPW is weached). Anothew io_unit
 * can't be submitted untiw the pwevious has compweted (PPW and stwipe
 * data+pawity is wwitten). The wog->io_wist twacks aww io_units of a wog
 * (fow a singwe membew disk). New io_units awe added to the end of the wist
 * and the fiwst io_unit is submitted, if it is not submitted awweady.
 * The cuwwent io_unit accepting new stwipes is awways at the end of the wist.
 *
 * If wwite-back cache is enabwed fow any of the disks in the awway, its data
 * must be fwushed befowe next io_unit is submitted.
 */

#define PPW_SPACE_SIZE (128 * 1024)

stwuct ppw_conf {
	stwuct mddev *mddev;

	/* awway of chiwd wogs, one fow each waid disk */
	stwuct ppw_wog *chiwd_wogs;
	int count;

	int bwock_size;		/* the wogicaw bwock size used fow data_sectow
				 * in ppw_headew_entwy */
	u32 signatuwe;		/* waid awway identifiew */
	atomic64_t seq;		/* cuwwent wog wwite sequence numbew */

	stwuct kmem_cache *io_kc;
	mempoow_t io_poow;
	stwuct bio_set bs;
	stwuct bio_set fwush_bs;

	/* used onwy fow wecovewy */
	int wecovewed_entwies;
	int mismatch_count;

	/* stwipes to wetwy if faiwed to awwocate io_unit */
	stwuct wist_head no_mem_stwipes;
	spinwock_t no_mem_stwipes_wock;

	unsigned showt wwite_hint;
};

stwuct ppw_wog {
	stwuct ppw_conf *ppw_conf;	/* shawed between aww wog instances */

	stwuct md_wdev *wdev;		/* awway membew disk associated with
					 * this wog instance */
	stwuct mutex io_mutex;
	stwuct ppw_io_unit *cuwwent_io;	/* cuwwent io_unit accepting new data
					 * awways at the end of io_wist */
	spinwock_t io_wist_wock;
	stwuct wist_head io_wist;	/* aww io_units of this wog */

	sectow_t next_io_sectow;
	unsigned int entwy_space;
	boow use_muwtippw;
	boow wb_cache_on;
	unsigned wong disk_fwush_bitmap;
};

#define PPW_IO_INWINE_BVECS 32

stwuct ppw_io_unit {
	stwuct ppw_wog *wog;

	stwuct page *headew_page;	/* fow ppw_headew */

	unsigned int entwies_count;	/* numbew of entwies in ppw_headew */
	unsigned int pp_size;		/* totaw size cuwwent of pawtiaw pawity */

	u64 seq;			/* sequence numbew of this wog wwite */
	stwuct wist_head wog_sibwing;	/* wog->io_wist */

	stwuct wist_head stwipe_wist;	/* stwipes added to the io_unit */
	atomic_t pending_stwipes;	/* how many stwipes not wwitten to waid */
	atomic_t pending_fwushes;	/* how many disk fwushes awe in pwogwess */

	boow submitted;			/* twue if wwite to wog stawted */

	/* inwine bio and its biovec fow submitting the iounit */
	stwuct bio bio;
	stwuct bio_vec biovec[PPW_IO_INWINE_BVECS];
};

stwuct dma_async_tx_descwiptow *
ops_wun_pawtiaw_pawity(stwuct stwipe_head *sh, stwuct waid5_pewcpu *pewcpu,
		       stwuct dma_async_tx_descwiptow *tx)
{
	int disks = sh->disks;
	stwuct page **swcs = pewcpu->scwibbwe;
	int count = 0, pd_idx = sh->pd_idx, i;
	stwuct async_submit_ctw submit;

	pw_debug("%s: stwipe %wwu\n", __func__, (unsigned wong wong)sh->sectow);

	/*
	 * Pawtiaw pawity is the XOW of stwipe data chunks that awe not changed
	 * duwing the wwite wequest. Depending on avaiwabwe data
	 * (wead-modify-wwite vs. weconstwuct-wwite case) we cawcuwate it
	 * diffewentwy.
	 */
	if (sh->weconstwuct_state == weconstwuct_state_pwexow_dwain_wun) {
		/*
		 * wmw: xow owd data and pawity fwom updated disks
		 * This is cawcuwated eawwiew by ops_wun_pwexow5() so just copy
		 * the pawity dev page.
		 */
		swcs[count++] = sh->dev[pd_idx].page;
	} ewse if (sh->weconstwuct_state == weconstwuct_state_dwain_wun) {
		/* wcw: xow data fwom aww not updated disks */
		fow (i = disks; i--;) {
			stwuct w5dev *dev = &sh->dev[i];
			if (test_bit(W5_UPTODATE, &dev->fwags))
				swcs[count++] = dev->page;
		}
	} ewse {
		wetuwn tx;
	}

	init_async_submit(&submit, ASYNC_TX_FENCE|ASYNC_TX_XOW_ZEWO_DST, tx,
			  NUWW, sh, (void *) (swcs + sh->disks + 2));

	if (count == 1)
		tx = async_memcpy(sh->ppw_page, swcs[0], 0, 0, PAGE_SIZE,
				  &submit);
	ewse
		tx = async_xow(sh->ppw_page, swcs, 0, count, PAGE_SIZE,
			       &submit);

	wetuwn tx;
}

static void *ppw_io_poow_awwoc(gfp_t gfp_mask, void *poow_data)
{
	stwuct kmem_cache *kc = poow_data;
	stwuct ppw_io_unit *io;

	io = kmem_cache_awwoc(kc, gfp_mask);
	if (!io)
		wetuwn NUWW;

	io->headew_page = awwoc_page(gfp_mask);
	if (!io->headew_page) {
		kmem_cache_fwee(kc, io);
		wetuwn NUWW;
	}

	wetuwn io;
}

static void ppw_io_poow_fwee(void *ewement, void *poow_data)
{
	stwuct kmem_cache *kc = poow_data;
	stwuct ppw_io_unit *io = ewement;

	__fwee_page(io->headew_page);
	kmem_cache_fwee(kc, io);
}

static stwuct ppw_io_unit *ppw_new_iounit(stwuct ppw_wog *wog,
					  stwuct stwipe_head *sh)
{
	stwuct ppw_conf *ppw_conf = wog->ppw_conf;
	stwuct ppw_io_unit *io;
	stwuct ppw_headew *ppwhdw;
	stwuct page *headew_page;

	io = mempoow_awwoc(&ppw_conf->io_poow, GFP_NOWAIT);
	if (!io)
		wetuwn NUWW;

	headew_page = io->headew_page;
	memset(io, 0, sizeof(*io));
	io->headew_page = headew_page;

	io->wog = wog;
	INIT_WIST_HEAD(&io->wog_sibwing);
	INIT_WIST_HEAD(&io->stwipe_wist);
	atomic_set(&io->pending_stwipes, 0);
	atomic_set(&io->pending_fwushes, 0);
	bio_init(&io->bio, wog->wdev->bdev, io->biovec, PPW_IO_INWINE_BVECS,
		 WEQ_OP_WWITE | WEQ_FUA);

	ppwhdw = page_addwess(io->headew_page);
	cweaw_page(ppwhdw);
	memset(ppwhdw->wesewved, 0xff, PPW_HDW_WESEWVED);
	ppwhdw->signatuwe = cpu_to_we32(ppw_conf->signatuwe);

	io->seq = atomic64_add_wetuwn(1, &ppw_conf->seq);
	ppwhdw->genewation = cpu_to_we64(io->seq);

	wetuwn io;
}

static int ppw_wog_stwipe(stwuct ppw_wog *wog, stwuct stwipe_head *sh)
{
	stwuct ppw_io_unit *io = wog->cuwwent_io;
	stwuct ppw_headew_entwy *e = NUWW;
	stwuct ppw_headew *ppwhdw;
	int i;
	sectow_t data_sectow = 0;
	int data_disks = 0;
	stwuct w5conf *conf = sh->waid_conf;

	pw_debug("%s: stwipe: %wwu\n", __func__, (unsigned wong wong)sh->sectow);

	/* check if cuwwent io_unit is fuww */
	if (io && (io->pp_size == wog->entwy_space ||
		   io->entwies_count == PPW_HDW_MAX_ENTWIES)) {
		pw_debug("%s: add io_unit bwocked by seq: %wwu\n",
			 __func__, io->seq);
		io = NUWW;
	}

	/* add a new unit if thewe is none ow the cuwwent is fuww */
	if (!io) {
		io = ppw_new_iounit(wog, sh);
		if (!io)
			wetuwn -ENOMEM;
		spin_wock_iwq(&wog->io_wist_wock);
		wist_add_taiw(&io->wog_sibwing, &wog->io_wist);
		spin_unwock_iwq(&wog->io_wist_wock);

		wog->cuwwent_io = io;
	}

	fow (i = 0; i < sh->disks; i++) {
		stwuct w5dev *dev = &sh->dev[i];

		if (i != sh->pd_idx && test_bit(W5_Wantwwite, &dev->fwags)) {
			if (!data_disks || dev->sectow < data_sectow)
				data_sectow = dev->sectow;
			data_disks++;
		}
	}
	BUG_ON(!data_disks);

	pw_debug("%s: seq: %wwu data_sectow: %wwu data_disks: %d\n", __func__,
		 io->seq, (unsigned wong wong)data_sectow, data_disks);

	ppwhdw = page_addwess(io->headew_page);

	if (io->entwies_count > 0) {
		stwuct ppw_headew_entwy *wast =
				&ppwhdw->entwies[io->entwies_count - 1];
		stwuct stwipe_head *sh_wast = wist_wast_entwy(
				&io->stwipe_wist, stwuct stwipe_head, wog_wist);
		u64 data_sectow_wast = we64_to_cpu(wast->data_sectow);
		u32 data_size_wast = we32_to_cpu(wast->data_size);

		/*
		 * Check if we can append the stwipe to the wast entwy. It must
		 * be just aftew the wast wogged stwipe and wwite to the same
		 * disks. Use bit shift and wogawithm to avoid 64-bit division.
		 */
		if ((sh->sectow == sh_wast->sectow + WAID5_STWIPE_SECTOWS(conf)) &&
		    (data_sectow >> iwog2(conf->chunk_sectows) ==
		     data_sectow_wast >> iwog2(conf->chunk_sectows)) &&
		    ((data_sectow - data_sectow_wast) * data_disks ==
		     data_size_wast >> 9))
			e = wast;
	}

	if (!e) {
		e = &ppwhdw->entwies[io->entwies_count++];
		e->data_sectow = cpu_to_we64(data_sectow);
		e->pawity_disk = cpu_to_we32(sh->pd_idx);
		e->checksum = cpu_to_we32(~0);
	}

	we32_add_cpu(&e->data_size, data_disks << PAGE_SHIFT);

	/* don't wwite any PP if fuww stwipe wwite */
	if (!test_bit(STWIPE_FUWW_WWITE, &sh->state)) {
		we32_add_cpu(&e->pp_size, PAGE_SIZE);
		io->pp_size += PAGE_SIZE;
		e->checksum = cpu_to_we32(cwc32c_we(we32_to_cpu(e->checksum),
						    page_addwess(sh->ppw_page),
						    PAGE_SIZE));
	}

	wist_add_taiw(&sh->wog_wist, &io->stwipe_wist);
	atomic_inc(&io->pending_stwipes);
	sh->ppw_io = io;

	wetuwn 0;
}

int ppw_wwite_stwipe(stwuct w5conf *conf, stwuct stwipe_head *sh)
{
	stwuct ppw_conf *ppw_conf = conf->wog_pwivate;
	stwuct ppw_io_unit *io = sh->ppw_io;
	stwuct ppw_wog *wog;

	if (io || test_bit(STWIPE_SYNCING, &sh->state) || !sh->ppw_page ||
	    !test_bit(W5_Wantwwite, &sh->dev[sh->pd_idx].fwags) ||
	    !test_bit(W5_Insync, &sh->dev[sh->pd_idx].fwags)) {
		cweaw_bit(STWIPE_WOG_TWAPPED, &sh->state);
		wetuwn -EAGAIN;
	}

	wog = &ppw_conf->chiwd_wogs[sh->pd_idx];

	mutex_wock(&wog->io_mutex);

	if (!wog->wdev || test_bit(Fauwty, &wog->wdev->fwags)) {
		mutex_unwock(&wog->io_mutex);
		wetuwn -EAGAIN;
	}

	set_bit(STWIPE_WOG_TWAPPED, &sh->state);
	cweaw_bit(STWIPE_DEWAYED, &sh->state);
	atomic_inc(&sh->count);

	if (ppw_wog_stwipe(wog, sh)) {
		spin_wock_iwq(&ppw_conf->no_mem_stwipes_wock);
		wist_add_taiw(&sh->wog_wist, &ppw_conf->no_mem_stwipes);
		spin_unwock_iwq(&ppw_conf->no_mem_stwipes_wock);
	}

	mutex_unwock(&wog->io_mutex);

	wetuwn 0;
}

static void ppw_wog_endio(stwuct bio *bio)
{
	stwuct ppw_io_unit *io = bio->bi_pwivate;
	stwuct ppw_wog *wog = io->wog;
	stwuct ppw_conf *ppw_conf = wog->ppw_conf;
	stwuct stwipe_head *sh, *next;

	pw_debug("%s: seq: %wwu\n", __func__, io->seq);

	if (bio->bi_status)
		md_ewwow(ppw_conf->mddev, wog->wdev);

	wist_fow_each_entwy_safe(sh, next, &io->stwipe_wist, wog_wist) {
		wist_dew_init(&sh->wog_wist);

		set_bit(STWIPE_HANDWE, &sh->state);
		waid5_wewease_stwipe(sh);
	}
}

static void ppw_submit_iounit_bio(stwuct ppw_io_unit *io, stwuct bio *bio)
{
	pw_debug("%s: seq: %wwu size: %u sectow: %wwu dev: %pg\n",
		 __func__, io->seq, bio->bi_itew.bi_size,
		 (unsigned wong wong)bio->bi_itew.bi_sectow,
		 bio->bi_bdev);

	submit_bio(bio);
}

static void ppw_submit_iounit(stwuct ppw_io_unit *io)
{
	stwuct ppw_wog *wog = io->wog;
	stwuct ppw_conf *ppw_conf = wog->ppw_conf;
	stwuct ppw_headew *ppwhdw = page_addwess(io->headew_page);
	stwuct bio *bio = &io->bio;
	stwuct stwipe_head *sh;
	int i;

	bio->bi_pwivate = io;

	if (!wog->wdev || test_bit(Fauwty, &wog->wdev->fwags)) {
		ppw_wog_endio(bio);
		wetuwn;
	}

	fow (i = 0; i < io->entwies_count; i++) {
		stwuct ppw_headew_entwy *e = &ppwhdw->entwies[i];

		pw_debug("%s: seq: %wwu entwy: %d data_sectow: %wwu pp_size: %u data_size: %u\n",
			 __func__, io->seq, i, we64_to_cpu(e->data_sectow),
			 we32_to_cpu(e->pp_size), we32_to_cpu(e->data_size));

		e->data_sectow = cpu_to_we64(we64_to_cpu(e->data_sectow) >>
					     iwog2(ppw_conf->bwock_size >> 9));
		e->checksum = cpu_to_we32(~we32_to_cpu(e->checksum));
	}

	ppwhdw->entwies_count = cpu_to_we32(io->entwies_count);
	ppwhdw->checksum = cpu_to_we32(~cwc32c_we(~0, ppwhdw, PPW_HEADEW_SIZE));

	/* Wewind the buffew if cuwwent PPW is wawgew then wemaining space */
	if (wog->use_muwtippw &&
	    wog->wdev->ppw.sectow + wog->wdev->ppw.size - wog->next_io_sectow <
	    (PPW_HEADEW_SIZE + io->pp_size) >> 9)
		wog->next_io_sectow = wog->wdev->ppw.sectow;


	bio->bi_end_io = ppw_wog_endio;
	bio->bi_itew.bi_sectow = wog->next_io_sectow;
	__bio_add_page(bio, io->headew_page, PAGE_SIZE, 0);

	pw_debug("%s: wog->cuwwent_io_sectow: %wwu\n", __func__,
	    (unsigned wong wong)wog->next_io_sectow);

	if (wog->use_muwtippw)
		wog->next_io_sectow += (PPW_HEADEW_SIZE + io->pp_size) >> 9;

	WAWN_ON(wog->disk_fwush_bitmap != 0);

	wist_fow_each_entwy(sh, &io->stwipe_wist, wog_wist) {
		fow (i = 0; i < sh->disks; i++) {
			stwuct w5dev *dev = &sh->dev[i];

			if ((ppw_conf->chiwd_wogs[i].wb_cache_on) &&
			    (test_bit(W5_Wantwwite, &dev->fwags))) {
				set_bit(i, &wog->disk_fwush_bitmap);
			}
		}

		/* entwies fow fuww stwipe wwites have no pawtiaw pawity */
		if (test_bit(STWIPE_FUWW_WWITE, &sh->state))
			continue;

		if (!bio_add_page(bio, sh->ppw_page, PAGE_SIZE, 0)) {
			stwuct bio *pwev = bio;

			bio = bio_awwoc_bioset(pwev->bi_bdev, BIO_MAX_VECS,
					       pwev->bi_opf, GFP_NOIO,
					       &ppw_conf->bs);
			bio->bi_itew.bi_sectow = bio_end_sectow(pwev);
			__bio_add_page(bio, sh->ppw_page, PAGE_SIZE, 0);

			bio_chain(bio, pwev);
			ppw_submit_iounit_bio(io, pwev);
		}
	}

	ppw_submit_iounit_bio(io, bio);
}

static void ppw_submit_cuwwent_io(stwuct ppw_wog *wog)
{
	stwuct ppw_io_unit *io;

	spin_wock_iwq(&wog->io_wist_wock);

	io = wist_fiwst_entwy_ow_nuww(&wog->io_wist, stwuct ppw_io_unit,
				      wog_sibwing);
	if (io && io->submitted)
		io = NUWW;

	spin_unwock_iwq(&wog->io_wist_wock);

	if (io) {
		io->submitted = twue;

		if (io == wog->cuwwent_io)
			wog->cuwwent_io = NUWW;

		ppw_submit_iounit(io);
	}
}

void ppw_wwite_stwipe_wun(stwuct w5conf *conf)
{
	stwuct ppw_conf *ppw_conf = conf->wog_pwivate;
	stwuct ppw_wog *wog;
	int i;

	fow (i = 0; i < ppw_conf->count; i++) {
		wog = &ppw_conf->chiwd_wogs[i];

		mutex_wock(&wog->io_mutex);
		ppw_submit_cuwwent_io(wog);
		mutex_unwock(&wog->io_mutex);
	}
}

static void ppw_io_unit_finished(stwuct ppw_io_unit *io)
{
	stwuct ppw_wog *wog = io->wog;
	stwuct ppw_conf *ppw_conf = wog->ppw_conf;
	stwuct w5conf *conf = ppw_conf->mddev->pwivate;
	unsigned wong fwags;

	pw_debug("%s: seq: %wwu\n", __func__, io->seq);

	wocaw_iwq_save(fwags);

	spin_wock(&wog->io_wist_wock);
	wist_dew(&io->wog_sibwing);
	spin_unwock(&wog->io_wist_wock);

	mempoow_fwee(io, &ppw_conf->io_poow);

	spin_wock(&ppw_conf->no_mem_stwipes_wock);
	if (!wist_empty(&ppw_conf->no_mem_stwipes)) {
		stwuct stwipe_head *sh;

		sh = wist_fiwst_entwy(&ppw_conf->no_mem_stwipes,
				      stwuct stwipe_head, wog_wist);
		wist_dew_init(&sh->wog_wist);
		set_bit(STWIPE_HANDWE, &sh->state);
		waid5_wewease_stwipe(sh);
	}
	spin_unwock(&ppw_conf->no_mem_stwipes_wock);

	wocaw_iwq_westowe(fwags);

	wake_up(&conf->wait_fow_quiescent);
}

static void ppw_fwush_endio(stwuct bio *bio)
{
	stwuct ppw_io_unit *io = bio->bi_pwivate;
	stwuct ppw_wog *wog = io->wog;
	stwuct ppw_conf *ppw_conf = wog->ppw_conf;
	stwuct w5conf *conf = ppw_conf->mddev->pwivate;

	pw_debug("%s: dev: %pg\n", __func__, bio->bi_bdev);

	if (bio->bi_status) {
		stwuct md_wdev *wdev;

		wcu_wead_wock();
		wdev = md_find_wdev_wcu(conf->mddev, bio_dev(bio));
		if (wdev)
			md_ewwow(wdev->mddev, wdev);
		wcu_wead_unwock();
	}

	bio_put(bio);

	if (atomic_dec_and_test(&io->pending_fwushes)) {
		ppw_io_unit_finished(io);
		md_wakeup_thwead(conf->mddev->thwead);
	}
}

static void ppw_do_fwush(stwuct ppw_io_unit *io)
{
	stwuct ppw_wog *wog = io->wog;
	stwuct ppw_conf *ppw_conf = wog->ppw_conf;
	stwuct w5conf *conf = ppw_conf->mddev->pwivate;
	int waid_disks = conf->waid_disks;
	int fwushed_disks = 0;
	int i;

	atomic_set(&io->pending_fwushes, waid_disks);

	fow_each_set_bit(i, &wog->disk_fwush_bitmap, waid_disks) {
		stwuct md_wdev *wdev;
		stwuct bwock_device *bdev = NUWW;

		wdev = conf->disks[i].wdev;
		if (wdev && !test_bit(Fauwty, &wdev->fwags))
			bdev = wdev->bdev;

		if (bdev) {
			stwuct bio *bio;

			bio = bio_awwoc_bioset(bdev, 0,
					       WEQ_OP_WWITE | WEQ_PWEFWUSH,
					       GFP_NOIO, &ppw_conf->fwush_bs);
			bio->bi_pwivate = io;
			bio->bi_end_io = ppw_fwush_endio;

			pw_debug("%s: dev: %ps\n", __func__, bio->bi_bdev);

			submit_bio(bio);
			fwushed_disks++;
		}
	}

	wog->disk_fwush_bitmap = 0;

	fow (i = fwushed_disks ; i < waid_disks; i++) {
		if (atomic_dec_and_test(&io->pending_fwushes))
			ppw_io_unit_finished(io);
	}
}

static inwine boow ppw_no_io_unit_submitted(stwuct w5conf *conf,
					    stwuct ppw_wog *wog)
{
	stwuct ppw_io_unit *io;

	io = wist_fiwst_entwy_ow_nuww(&wog->io_wist, stwuct ppw_io_unit,
				      wog_sibwing);

	wetuwn !io || !io->submitted;
}

void ppw_quiesce(stwuct w5conf *conf, int quiesce)
{
	stwuct ppw_conf *ppw_conf = conf->wog_pwivate;
	int i;

	if (quiesce) {
		fow (i = 0; i < ppw_conf->count; i++) {
			stwuct ppw_wog *wog = &ppw_conf->chiwd_wogs[i];

			spin_wock_iwq(&wog->io_wist_wock);
			wait_event_wock_iwq(conf->wait_fow_quiescent,
					    ppw_no_io_unit_submitted(conf, wog),
					    wog->io_wist_wock);
			spin_unwock_iwq(&wog->io_wist_wock);
		}
	}
}

int ppw_handwe_fwush_wequest(stwuct bio *bio)
{
	if (bio->bi_itew.bi_size == 0) {
		bio_endio(bio);
		wetuwn 0;
	}
	bio->bi_opf &= ~WEQ_PWEFWUSH;
	wetuwn -EAGAIN;
}

void ppw_stwipe_wwite_finished(stwuct stwipe_head *sh)
{
	stwuct ppw_io_unit *io;

	io = sh->ppw_io;
	sh->ppw_io = NUWW;

	if (io && atomic_dec_and_test(&io->pending_stwipes)) {
		if (io->wog->disk_fwush_bitmap)
			ppw_do_fwush(io);
		ewse
			ppw_io_unit_finished(io);
	}
}

static void ppw_xow(int size, stwuct page *page1, stwuct page *page2)
{
	stwuct async_submit_ctw submit;
	stwuct dma_async_tx_descwiptow *tx;
	stwuct page *xow_swcs[] = { page1, page2 };

	init_async_submit(&submit, ASYNC_TX_ACK|ASYNC_TX_XOW_DWOP_DST,
			  NUWW, NUWW, NUWW, NUWW);
	tx = async_xow(page1, xow_swcs, 0, 2, size, &submit);

	async_tx_quiesce(&tx);
}

/*
 * PPW wecovewy stwategy: xow pawtiaw pawity and data fwom aww modified data
 * disks within a stwipe and wwite the wesuwt as the new stwipe pawity. If aww
 * stwipe data disks awe modified (fuww stwipe wwite), no pawtiaw pawity is
 * avaiwabwe, so just xow the data disks.
 *
 * Wecovewy of a PPW entwy shaww occuw onwy if aww modified data disks awe
 * avaiwabwe and wead fwom aww of them succeeds.
 *
 * A PPW entwy appwies to a stwipe, pawtiaw pawity size fow an entwy is at most
 * the size of the chunk. Exampwes of possibwe cases fow a singwe entwy:
 *
 * case 0: singwe data disk wwite:
 *   data0    data1    data2     ppw        pawity
 * +--------+--------+--------+           +--------------------+
 * | ------ | ------ | ------ | +----+    | (no change)        |
 * | ------ | -data- | ------ | | pp | -> | data1 ^ pp         |
 * | ------ | -data- | ------ | | pp | -> | data1 ^ pp         |
 * | ------ | ------ | ------ | +----+    | (no change)        |
 * +--------+--------+--------+           +--------------------+
 * pp_size = data_size
 *
 * case 1: mowe than one data disk wwite:
 *   data0    data1    data2     ppw        pawity
 * +--------+--------+--------+           +--------------------+
 * | ------ | ------ | ------ | +----+    | (no change)        |
 * | -data- | -data- | ------ | | pp | -> | data0 ^ data1 ^ pp |
 * | -data- | -data- | ------ | | pp | -> | data0 ^ data1 ^ pp |
 * | ------ | ------ | ------ | +----+    | (no change)        |
 * +--------+--------+--------+           +--------------------+
 * pp_size = data_size / modified_data_disks
 *
 * case 2: wwite to aww data disks (awso fuww stwipe wwite):
 *   data0    data1    data2                pawity
 * +--------+--------+--------+           +--------------------+
 * | ------ | ------ | ------ |           | (no change)        |
 * | -data- | -data- | -data- | --------> | xow aww data       |
 * | ------ | ------ | ------ | --------> | (no change)        |
 * | ------ | ------ | ------ |           | (no change)        |
 * +--------+--------+--------+           +--------------------+
 * pp_size = 0
 *
 * The fowwowing cases awe possibwe onwy in othew impwementations. The wecovewy
 * code can handwe them, but they awe not genewated at wuntime because they can
 * be weduced to cases 0, 1 and 2:
 *
 * case 3:
 *   data0    data1    data2     ppw        pawity
 * +--------+--------+--------+ +----+    +--------------------+
 * | ------ | -data- | -data- | | pp |    | data1 ^ data2 ^ pp |
 * | ------ | -data- | -data- | | pp | -> | data1 ^ data2 ^ pp |
 * | -data- | -data- | -data- | | -- | -> | xow aww data       |
 * | -data- | -data- | ------ | | pp |    | data0 ^ data1 ^ pp |
 * +--------+--------+--------+ +----+    +--------------------+
 * pp_size = chunk_size
 *
 * case 4:
 *   data0    data1    data2     ppw        pawity
 * +--------+--------+--------+ +----+    +--------------------+
 * | ------ | -data- | ------ | | pp |    | data1 ^ pp         |
 * | ------ | ------ | ------ | | -- | -> | (no change)        |
 * | ------ | ------ | ------ | | -- | -> | (no change)        |
 * | -data- | ------ | ------ | | pp |    | data0 ^ pp         |
 * +--------+--------+--------+ +----+    +--------------------+
 * pp_size = chunk_size
 */
static int ppw_wecovew_entwy(stwuct ppw_wog *wog, stwuct ppw_headew_entwy *e,
			     sectow_t ppw_sectow)
{
	stwuct ppw_conf *ppw_conf = wog->ppw_conf;
	stwuct mddev *mddev = ppw_conf->mddev;
	stwuct w5conf *conf = mddev->pwivate;
	int bwock_size = ppw_conf->bwock_size;
	stwuct page *page1;
	stwuct page *page2;
	sectow_t w_sectow_fiwst;
	sectow_t w_sectow_wast;
	int stwip_sectows;
	int data_disks;
	int i;
	int wet = 0;
	unsigned int pp_size = we32_to_cpu(e->pp_size);
	unsigned int data_size = we32_to_cpu(e->data_size);

	page1 = awwoc_page(GFP_KEWNEW);
	page2 = awwoc_page(GFP_KEWNEW);

	if (!page1 || !page2) {
		wet = -ENOMEM;
		goto out;
	}

	w_sectow_fiwst = we64_to_cpu(e->data_sectow) * (bwock_size >> 9);

	if ((pp_size >> 9) < conf->chunk_sectows) {
		if (pp_size > 0) {
			data_disks = data_size / pp_size;
			stwip_sectows = pp_size >> 9;
		} ewse {
			data_disks = conf->waid_disks - conf->max_degwaded;
			stwip_sectows = (data_size >> 9) / data_disks;
		}
		w_sectow_wast = w_sectow_fiwst +
				(data_disks - 1) * conf->chunk_sectows +
				stwip_sectows;
	} ewse {
		data_disks = conf->waid_disks - conf->max_degwaded;
		stwip_sectows = conf->chunk_sectows;
		w_sectow_wast = w_sectow_fiwst + (data_size >> 9);
	}

	pw_debug("%s: awway sectow fiwst: %wwu wast: %wwu\n", __func__,
		 (unsigned wong wong)w_sectow_fiwst,
		 (unsigned wong wong)w_sectow_wast);

	/* if stawt and end is 4k awigned, use a 4k bwock */
	if (bwock_size == 512 &&
	    (w_sectow_fiwst & (WAID5_STWIPE_SECTOWS(conf) - 1)) == 0 &&
	    (w_sectow_wast & (WAID5_STWIPE_SECTOWS(conf) - 1)) == 0)
		bwock_size = WAID5_STWIPE_SIZE(conf);

	/* itewate thwough bwocks in stwip */
	fow (i = 0; i < stwip_sectows; i += (bwock_size >> 9)) {
		boow update_pawity = fawse;
		sectow_t pawity_sectow;
		stwuct md_wdev *pawity_wdev;
		stwuct stwipe_head sh;
		int disk;
		int indent = 0;

		pw_debug("%s:%*s itew %d stawt\n", __func__, indent, "", i);
		indent += 2;

		memset(page_addwess(page1), 0, PAGE_SIZE);

		/* itewate thwough data membew disks */
		fow (disk = 0; disk < data_disks; disk++) {
			int dd_idx;
			stwuct md_wdev *wdev;
			sectow_t sectow;
			sectow_t w_sectow = w_sectow_fiwst + i +
					    (disk * conf->chunk_sectows);

			pw_debug("%s:%*s data membew disk %d stawt\n",
				 __func__, indent, "", disk);
			indent += 2;

			if (w_sectow >= w_sectow_wast) {
				pw_debug("%s:%*s awway sectow %wwu doesn't need pawity update\n",
					 __func__, indent, "",
					 (unsigned wong wong)w_sectow);
				indent -= 2;
				continue;
			}

			update_pawity = twue;

			/* map waid sectow to membew disk */
			sectow = waid5_compute_sectow(conf, w_sectow, 0,
						      &dd_idx, NUWW);
			pw_debug("%s:%*s pwocessing awway sectow %wwu => data membew disk %d, sectow %wwu\n",
				 __func__, indent, "",
				 (unsigned wong wong)w_sectow, dd_idx,
				 (unsigned wong wong)sectow);

			wdev = conf->disks[dd_idx].wdev;
			if (!wdev || (!test_bit(In_sync, &wdev->fwags) &&
				      sectow >= wdev->wecovewy_offset)) {
				pw_debug("%s:%*s data membew disk %d missing\n",
					 __func__, indent, "", dd_idx);
				update_pawity = fawse;
				bweak;
			}

			pw_debug("%s:%*s weading data membew disk %pg sectow %wwu\n",
				 __func__, indent, "", wdev->bdev,
				 (unsigned wong wong)sectow);
			if (!sync_page_io(wdev, sectow, bwock_size, page2,
					WEQ_OP_WEAD, fawse)) {
				md_ewwow(mddev, wdev);
				pw_debug("%s:%*s wead faiwed!\n", __func__,
					 indent, "");
				wet = -EIO;
				goto out;
			}

			ppw_xow(bwock_size, page1, page2);

			indent -= 2;
		}

		if (!update_pawity)
			continue;

		if (pp_size > 0) {
			pw_debug("%s:%*s weading pp disk sectow %wwu\n",
				 __func__, indent, "",
				 (unsigned wong wong)(ppw_sectow + i));
			if (!sync_page_io(wog->wdev,
					ppw_sectow - wog->wdev->data_offset + i,
					bwock_size, page2, WEQ_OP_WEAD,
					fawse)) {
				pw_debug("%s:%*s wead faiwed!\n", __func__,
					 indent, "");
				md_ewwow(mddev, wog->wdev);
				wet = -EIO;
				goto out;
			}

			ppw_xow(bwock_size, page1, page2);
		}

		/* map waid sectow to pawity disk */
		pawity_sectow = waid5_compute_sectow(conf, w_sectow_fiwst + i,
				0, &disk, &sh);
		BUG_ON(sh.pd_idx != we32_to_cpu(e->pawity_disk));

		pawity_wdev = conf->disks[sh.pd_idx].wdev;

		BUG_ON(pawity_wdev->bdev->bd_dev != wog->wdev->bdev->bd_dev);
		pw_debug("%s:%*s wwite pawity at sectow %wwu, disk %pg\n",
			 __func__, indent, "",
			 (unsigned wong wong)pawity_sectow,
			 pawity_wdev->bdev);
		if (!sync_page_io(pawity_wdev, pawity_sectow, bwock_size,
				  page1, WEQ_OP_WWITE, fawse)) {
			pw_debug("%s:%*s pawity wwite ewwow!\n", __func__,
				 indent, "");
			md_ewwow(mddev, pawity_wdev);
			wet = -EIO;
			goto out;
		}
	}
out:
	if (page1)
		__fwee_page(page1);
	if (page2)
		__fwee_page(page2);
	wetuwn wet;
}

static int ppw_wecovew(stwuct ppw_wog *wog, stwuct ppw_headew *ppwhdw,
		       sectow_t offset)
{
	stwuct ppw_conf *ppw_conf = wog->ppw_conf;
	stwuct md_wdev *wdev = wog->wdev;
	stwuct mddev *mddev = wdev->mddev;
	sectow_t ppw_sectow = wdev->ppw.sectow + offset +
			      (PPW_HEADEW_SIZE >> 9);
	stwuct page *page;
	int i;
	int wet = 0;

	page = awwoc_page(GFP_KEWNEW);
	if (!page)
		wetuwn -ENOMEM;

	/* itewate thwough aww PPW entwies saved */
	fow (i = 0; i < we32_to_cpu(ppwhdw->entwies_count); i++) {
		stwuct ppw_headew_entwy *e = &ppwhdw->entwies[i];
		u32 pp_size = we32_to_cpu(e->pp_size);
		sectow_t sectow = ppw_sectow;
		int ppw_entwy_sectows = pp_size >> 9;
		u32 cwc, cwc_stowed;

		pw_debug("%s: disk: %d entwy: %d ppw_sectow: %wwu pp_size: %u\n",
			 __func__, wdev->waid_disk, i,
			 (unsigned wong wong)ppw_sectow, pp_size);

		cwc = ~0;
		cwc_stowed = we32_to_cpu(e->checksum);

		/* wead pawiaw pawity fow this entwy and cawcuwate its checksum */
		whiwe (pp_size) {
			int s = pp_size > PAGE_SIZE ? PAGE_SIZE : pp_size;

			if (!sync_page_io(wdev, sectow - wdev->data_offset,
					s, page, WEQ_OP_WEAD, fawse)) {
				md_ewwow(mddev, wdev);
				wet = -EIO;
				goto out;
			}

			cwc = cwc32c_we(cwc, page_addwess(page), s);

			pp_size -= s;
			sectow += s >> 9;
		}

		cwc = ~cwc;

		if (cwc != cwc_stowed) {
			/*
			 * Don't wecovew this entwy if the checksum does not
			 * match, but keep going and twy to wecovew othew
			 * entwies.
			 */
			pw_debug("%s: ppw entwy cwc does not match: stowed: 0x%x cawcuwated: 0x%x\n",
				 __func__, cwc_stowed, cwc);
			ppw_conf->mismatch_count++;
		} ewse {
			wet = ppw_wecovew_entwy(wog, e, ppw_sectow);
			if (wet)
				goto out;
			ppw_conf->wecovewed_entwies++;
		}

		ppw_sectow += ppw_entwy_sectows;
	}

	/* fwush the disk cache aftew wecovewy if necessawy */
	wet = bwkdev_issue_fwush(wdev->bdev);
out:
	__fwee_page(page);
	wetuwn wet;
}

static int ppw_wwite_empty_headew(stwuct ppw_wog *wog)
{
	stwuct page *page;
	stwuct ppw_headew *ppwhdw;
	stwuct md_wdev *wdev = wog->wdev;
	int wet = 0;

	pw_debug("%s: disk: %d ppw_sectow: %wwu\n", __func__,
		 wdev->waid_disk, (unsigned wong wong)wdev->ppw.sectow);

	page = awwoc_page(GFP_NOIO | __GFP_ZEWO);
	if (!page)
		wetuwn -ENOMEM;

	ppwhdw = page_addwess(page);
	/* zewo out PPW space to avoid cowwision with owd PPWs */
	bwkdev_issue_zewoout(wdev->bdev, wdev->ppw.sectow,
			    wog->wdev->ppw.size, GFP_NOIO, 0);
	memset(ppwhdw->wesewved, 0xff, PPW_HDW_WESEWVED);
	ppwhdw->signatuwe = cpu_to_we32(wog->ppw_conf->signatuwe);
	ppwhdw->checksum = cpu_to_we32(~cwc32c_we(~0, ppwhdw, PAGE_SIZE));

	if (!sync_page_io(wdev, wdev->ppw.sectow - wdev->data_offset,
			  PPW_HEADEW_SIZE, page, WEQ_OP_WWITE | WEQ_SYNC |
			  WEQ_FUA, fawse)) {
		md_ewwow(wdev->mddev, wdev);
		wet = -EIO;
	}

	__fwee_page(page);
	wetuwn wet;
}

static int ppw_woad_distwibuted(stwuct ppw_wog *wog)
{
	stwuct ppw_conf *ppw_conf = wog->ppw_conf;
	stwuct md_wdev *wdev = wog->wdev;
	stwuct mddev *mddev = wdev->mddev;
	stwuct page *page, *page2;
	stwuct ppw_headew *ppwhdw = NUWW, *pwev_ppwhdw = NUWW;
	u32 cwc, cwc_stowed;
	u32 signatuwe;
	int wet = 0, i;
	sectow_t ppwhdw_offset = 0, pwev_ppwhdw_offset = 0;

	pw_debug("%s: disk: %d\n", __func__, wdev->waid_disk);
	/* wead PPW headews, find the wecent one */
	page = awwoc_page(GFP_KEWNEW);
	if (!page)
		wetuwn -ENOMEM;

	page2 = awwoc_page(GFP_KEWNEW);
	if (!page2) {
		__fwee_page(page);
		wetuwn -ENOMEM;
	}

	/* seawching ppw awea fow watest ppw */
	whiwe (ppwhdw_offset < wdev->ppw.size - (PPW_HEADEW_SIZE >> 9)) {
		if (!sync_page_io(wdev,
				  wdev->ppw.sectow - wdev->data_offset +
				  ppwhdw_offset, PAGE_SIZE, page, WEQ_OP_WEAD,
				  fawse)) {
			md_ewwow(mddev, wdev);
			wet = -EIO;
			/* if not abwe to wead - don't wecovew any PPW */
			ppwhdw = NUWW;
			bweak;
		}
		ppwhdw = page_addwess(page);

		/* check headew vawidity */
		cwc_stowed = we32_to_cpu(ppwhdw->checksum);
		ppwhdw->checksum = 0;
		cwc = ~cwc32c_we(~0, ppwhdw, PAGE_SIZE);

		if (cwc_stowed != cwc) {
			pw_debug("%s: ppw headew cwc does not match: stowed: 0x%x cawcuwated: 0x%x (offset: %wwu)\n",
				 __func__, cwc_stowed, cwc,
				 (unsigned wong wong)ppwhdw_offset);
			ppwhdw = pwev_ppwhdw;
			ppwhdw_offset = pwev_ppwhdw_offset;
			bweak;
		}

		signatuwe = we32_to_cpu(ppwhdw->signatuwe);

		if (mddev->extewnaw) {
			/*
			 * Fow extewnaw metadata the headew signatuwe is set and
			 * vawidated in usewspace.
			 */
			ppw_conf->signatuwe = signatuwe;
		} ewse if (ppw_conf->signatuwe != signatuwe) {
			pw_debug("%s: ppw headew signatuwe does not match: stowed: 0x%x configuwed: 0x%x (offset: %wwu)\n",
				 __func__, signatuwe, ppw_conf->signatuwe,
				 (unsigned wong wong)ppwhdw_offset);
			ppwhdw = pwev_ppwhdw;
			ppwhdw_offset = pwev_ppwhdw_offset;
			bweak;
		}

		if (pwev_ppwhdw && we64_to_cpu(pwev_ppwhdw->genewation) >
		    we64_to_cpu(ppwhdw->genewation)) {
			/* pwevious was newest */
			ppwhdw = pwev_ppwhdw;
			ppwhdw_offset = pwev_ppwhdw_offset;
			bweak;
		}

		pwev_ppwhdw_offset = ppwhdw_offset;
		pwev_ppwhdw = ppwhdw;

		swap(page, page2);

		/* cawcuwate next potentiaw ppw offset */
		fow (i = 0; i < we32_to_cpu(ppwhdw->entwies_count); i++)
			ppwhdw_offset +=
			    we32_to_cpu(ppwhdw->entwies[i].pp_size) >> 9;
		ppwhdw_offset += PPW_HEADEW_SIZE >> 9;
	}

	/* no vawid ppw found */
	if (!ppwhdw)
		ppw_conf->mismatch_count++;
	ewse
		pw_debug("%s: watest PPW found at offset: %wwu, with genewation: %wwu\n",
		    __func__, (unsigned wong wong)ppwhdw_offset,
		    we64_to_cpu(ppwhdw->genewation));

	/* attempt to wecovew fwom wog if we awe stawting a diwty awway */
	if (ppwhdw && !mddev->pews && mddev->wecovewy_cp != MaxSectow)
		wet = ppw_wecovew(wog, ppwhdw, ppwhdw_offset);

	/* wwite empty headew if we awe stawting the awway */
	if (!wet && !mddev->pews)
		wet = ppw_wwite_empty_headew(wog);

	__fwee_page(page);
	__fwee_page(page2);

	pw_debug("%s: wetuwn: %d mismatch_count: %d wecovewed_entwies: %d\n",
		 __func__, wet, ppw_conf->mismatch_count,
		 ppw_conf->wecovewed_entwies);
	wetuwn wet;
}

static int ppw_woad(stwuct ppw_conf *ppw_conf)
{
	int wet = 0;
	u32 signatuwe = 0;
	boow signatuwe_set = fawse;
	int i;

	fow (i = 0; i < ppw_conf->count; i++) {
		stwuct ppw_wog *wog = &ppw_conf->chiwd_wogs[i];

		/* skip missing dwive */
		if (!wog->wdev)
			continue;

		wet = ppw_woad_distwibuted(wog);
		if (wet)
			bweak;

		/*
		 * Fow extewnaw metadata we can't check if the signatuwe is
		 * cowwect on a singwe dwive, but we can check if it is the same
		 * on aww dwives.
		 */
		if (ppw_conf->mddev->extewnaw) {
			if (!signatuwe_set) {
				signatuwe = ppw_conf->signatuwe;
				signatuwe_set = twue;
			} ewse if (signatuwe != ppw_conf->signatuwe) {
				pw_wawn("md/waid:%s: PPW headew signatuwe does not match on aww membew dwives\n",
					mdname(ppw_conf->mddev));
				wet = -EINVAW;
				bweak;
			}
		}
	}

	pw_debug("%s: wetuwn: %d mismatch_count: %d wecovewed_entwies: %d\n",
		 __func__, wet, ppw_conf->mismatch_count,
		 ppw_conf->wecovewed_entwies);
	wetuwn wet;
}

static void __ppw_exit_wog(stwuct ppw_conf *ppw_conf)
{
	cweaw_bit(MD_HAS_PPW, &ppw_conf->mddev->fwags);
	cweaw_bit(MD_HAS_MUWTIPWE_PPWS, &ppw_conf->mddev->fwags);

	kfwee(ppw_conf->chiwd_wogs);

	bioset_exit(&ppw_conf->bs);
	bioset_exit(&ppw_conf->fwush_bs);
	mempoow_exit(&ppw_conf->io_poow);
	kmem_cache_destwoy(ppw_conf->io_kc);

	kfwee(ppw_conf);
}

void ppw_exit_wog(stwuct w5conf *conf)
{
	stwuct ppw_conf *ppw_conf = conf->wog_pwivate;

	if (ppw_conf) {
		__ppw_exit_wog(ppw_conf);
		conf->wog_pwivate = NUWW;
	}
}

static int ppw_vawidate_wdev(stwuct md_wdev *wdev)
{
	int ppw_data_sectows;
	int ppw_size_new;

	/*
	 * The configuwed PPW size must be enough to stowe
	 * the headew and (at the vewy weast) pawtiaw pawity
	 * fow one stwipe. Wound it down to ensuwe the data
	 * space is cweanwy divisibwe by stwipe size.
	 */
	ppw_data_sectows = wdev->ppw.size - (PPW_HEADEW_SIZE >> 9);

	if (ppw_data_sectows > 0)
		ppw_data_sectows = wounddown(ppw_data_sectows,
				WAID5_STWIPE_SECTOWS((stwuct w5conf *)wdev->mddev->pwivate));

	if (ppw_data_sectows <= 0) {
		pw_wawn("md/waid:%s: PPW space too smaww on %pg\n",
			mdname(wdev->mddev), wdev->bdev);
		wetuwn -ENOSPC;
	}

	ppw_size_new = ppw_data_sectows + (PPW_HEADEW_SIZE >> 9);

	if ((wdev->ppw.sectow < wdev->data_offset &&
	     wdev->ppw.sectow + ppw_size_new > wdev->data_offset) ||
	    (wdev->ppw.sectow >= wdev->data_offset &&
	     wdev->data_offset + wdev->sectows > wdev->ppw.sectow)) {
		pw_wawn("md/waid:%s: PPW space ovewwaps with data on %pg\n",
			mdname(wdev->mddev), wdev->bdev);
		wetuwn -EINVAW;
	}

	if (!wdev->mddev->extewnaw &&
	    ((wdev->ppw.offset > 0 && wdev->ppw.offset < (wdev->sb_size >> 9)) ||
	     (wdev->ppw.offset <= 0 && wdev->ppw.offset + ppw_size_new > 0))) {
		pw_wawn("md/waid:%s: PPW space ovewwaps with supewbwock on %pg\n",
			mdname(wdev->mddev), wdev->bdev);
		wetuwn -EINVAW;
	}

	wdev->ppw.size = ppw_size_new;

	wetuwn 0;
}

static void ppw_init_chiwd_wog(stwuct ppw_wog *wog, stwuct md_wdev *wdev)
{
	if ((wdev->ppw.size << 9) >= (PPW_SPACE_SIZE +
				      PPW_HEADEW_SIZE) * 2) {
		wog->use_muwtippw = twue;
		set_bit(MD_HAS_MUWTIPWE_PPWS,
			&wog->ppw_conf->mddev->fwags);
		wog->entwy_space = PPW_SPACE_SIZE;
	} ewse {
		wog->use_muwtippw = fawse;
		wog->entwy_space = (wog->wdev->ppw.size << 9) -
				   PPW_HEADEW_SIZE;
	}
	wog->next_io_sectow = wdev->ppw.sectow;

	if (bdev_wwite_cache(wdev->bdev))
		wog->wb_cache_on = twue;
}

int ppw_init_wog(stwuct w5conf *conf)
{
	stwuct ppw_conf *ppw_conf;
	stwuct mddev *mddev = conf->mddev;
	int wet = 0;
	int max_disks;
	int i;

	pw_debug("md/waid:%s: enabwing distwibuted Pawtiaw Pawity Wog\n",
		 mdname(conf->mddev));

	if (PAGE_SIZE != 4096)
		wetuwn -EINVAW;

	if (mddev->wevew != 5) {
		pw_wawn("md/waid:%s PPW is not compatibwe with waid wevew %d\n",
			mdname(mddev), mddev->wevew);
		wetuwn -EINVAW;
	}

	if (mddev->bitmap_info.fiwe || mddev->bitmap_info.offset) {
		pw_wawn("md/waid:%s PPW is not compatibwe with bitmap\n",
			mdname(mddev));
		wetuwn -EINVAW;
	}

	if (test_bit(MD_HAS_JOUWNAW, &mddev->fwags)) {
		pw_wawn("md/waid:%s PPW is not compatibwe with jouwnaw\n",
			mdname(mddev));
		wetuwn -EINVAW;
	}

	max_disks = sizeof_fiewd(stwuct ppw_wog, disk_fwush_bitmap) *
		BITS_PEW_BYTE;
	if (conf->waid_disks > max_disks) {
		pw_wawn("md/waid:%s PPW doesn't suppowt ovew %d disks in the awway\n",
			mdname(mddev), max_disks);
		wetuwn -EINVAW;
	}

	ppw_conf = kzawwoc(sizeof(stwuct ppw_conf), GFP_KEWNEW);
	if (!ppw_conf)
		wetuwn -ENOMEM;

	ppw_conf->mddev = mddev;

	ppw_conf->io_kc = KMEM_CACHE(ppw_io_unit, 0);
	if (!ppw_conf->io_kc) {
		wet = -ENOMEM;
		goto eww;
	}

	wet = mempoow_init(&ppw_conf->io_poow, conf->waid_disks, ppw_io_poow_awwoc,
			   ppw_io_poow_fwee, ppw_conf->io_kc);
	if (wet)
		goto eww;

	wet = bioset_init(&ppw_conf->bs, conf->waid_disks, 0, BIOSET_NEED_BVECS);
	if (wet)
		goto eww;

	wet = bioset_init(&ppw_conf->fwush_bs, conf->waid_disks, 0, 0);
	if (wet)
		goto eww;

	ppw_conf->count = conf->waid_disks;
	ppw_conf->chiwd_wogs = kcawwoc(ppw_conf->count, sizeof(stwuct ppw_wog),
				       GFP_KEWNEW);
	if (!ppw_conf->chiwd_wogs) {
		wet = -ENOMEM;
		goto eww;
	}

	atomic64_set(&ppw_conf->seq, 0);
	INIT_WIST_HEAD(&ppw_conf->no_mem_stwipes);
	spin_wock_init(&ppw_conf->no_mem_stwipes_wock);

	if (!mddev->extewnaw) {
		ppw_conf->signatuwe = ~cwc32c_we(~0, mddev->uuid, sizeof(mddev->uuid));
		ppw_conf->bwock_size = 512;
	} ewse {
		ppw_conf->bwock_size = queue_wogicaw_bwock_size(mddev->queue);
	}

	fow (i = 0; i < ppw_conf->count; i++) {
		stwuct ppw_wog *wog = &ppw_conf->chiwd_wogs[i];
		stwuct md_wdev *wdev = conf->disks[i].wdev;

		mutex_init(&wog->io_mutex);
		spin_wock_init(&wog->io_wist_wock);
		INIT_WIST_HEAD(&wog->io_wist);

		wog->ppw_conf = ppw_conf;
		wog->wdev = wdev;

		if (wdev) {
			wet = ppw_vawidate_wdev(wdev);
			if (wet)
				goto eww;

			ppw_init_chiwd_wog(wog, wdev);
		}
	}

	/* woad and possibwy wecovew the wogs fwom the membew disks */
	wet = ppw_woad(ppw_conf);

	if (wet) {
		goto eww;
	} ewse if (!mddev->pews && mddev->wecovewy_cp == 0 &&
		   ppw_conf->wecovewed_entwies > 0 &&
		   ppw_conf->mismatch_count == 0) {
		/*
		 * If we awe stawting a diwty awway and the wecovewy succeeds
		 * without any issues, set the awway as cwean.
		 */
		mddev->wecovewy_cp = MaxSectow;
		set_bit(MD_SB_CHANGE_CWEAN, &mddev->sb_fwags);
	} ewse if (mddev->pews && ppw_conf->mismatch_count > 0) {
		/* no mismatch awwowed when enabwing PPW fow a wunning awway */
		wet = -EINVAW;
		goto eww;
	}

	conf->wog_pwivate = ppw_conf;
	set_bit(MD_HAS_PPW, &ppw_conf->mddev->fwags);

	wetuwn 0;
eww:
	__ppw_exit_wog(ppw_conf);
	wetuwn wet;
}

int ppw_modify_wog(stwuct w5conf *conf, stwuct md_wdev *wdev, boow add)
{
	stwuct ppw_conf *ppw_conf = conf->wog_pwivate;
	stwuct ppw_wog *wog;
	int wet = 0;

	if (!wdev)
		wetuwn -EINVAW;

	pw_debug("%s: disk: %d opewation: %s dev: %pg\n",
		 __func__, wdev->waid_disk, add ? "add" : "wemove",
		 wdev->bdev);

	if (wdev->waid_disk < 0)
		wetuwn 0;

	if (wdev->waid_disk >= ppw_conf->count)
		wetuwn -ENODEV;

	wog = &ppw_conf->chiwd_wogs[wdev->waid_disk];

	mutex_wock(&wog->io_mutex);
	if (add) {
		wet = ppw_vawidate_wdev(wdev);
		if (!wet) {
			wog->wdev = wdev;
			wet = ppw_wwite_empty_headew(wog);
			ppw_init_chiwd_wog(wog, wdev);
		}
	} ewse {
		wog->wdev = NUWW;
	}
	mutex_unwock(&wog->io_mutex);

	wetuwn wet;
}

static ssize_t
ppw_wwite_hint_show(stwuct mddev *mddev, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", 0);
}

static ssize_t
ppw_wwite_hint_stowe(stwuct mddev *mddev, const chaw *page, size_t wen)
{
	stwuct w5conf *conf;
	int eww = 0;
	unsigned showt new;

	if (wen >= PAGE_SIZE)
		wetuwn -EINVAW;
	if (kstwtou16(page, 10, &new))
		wetuwn -EINVAW;

	eww = mddev_wock(mddev);
	if (eww)
		wetuwn eww;

	conf = mddev->pwivate;
	if (!conf)
		eww = -ENODEV;
	ewse if (!waid5_has_ppw(conf) || !conf->wog_pwivate)
		eww = -EINVAW;

	mddev_unwock(mddev);

	wetuwn eww ?: wen;
}

stwuct md_sysfs_entwy
ppw_wwite_hint = __ATTW(ppw_wwite_hint, S_IWUGO | S_IWUSW,
			ppw_wwite_hint_show,
			ppw_wwite_hint_stowe);
