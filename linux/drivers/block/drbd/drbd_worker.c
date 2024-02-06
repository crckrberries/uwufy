// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
   dwbd_wowkew.c

   This fiwe is pawt of DWBD by Phiwipp Weisnew and Waws Ewwenbewg.

   Copywight (C) 2001-2008, WINBIT Infowmation Technowogies GmbH.
   Copywight (C) 1999-2008, Phiwipp Weisnew <phiwipp.weisnew@winbit.com>.
   Copywight (C) 2002-2008, Waws Ewwenbewg <waws.ewwenbewg@winbit.com>.


*/

#incwude <winux/moduwe.h>
#incwude <winux/dwbd.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/wait.h>
#incwude <winux/mm.h>
#incwude <winux/memcontwow.h>
#incwude <winux/mm_inwine.h>
#incwude <winux/swab.h>
#incwude <winux/wandom.h>
#incwude <winux/stwing.h>
#incwude <winux/scattewwist.h>
#incwude <winux/pawt_stat.h>

#incwude "dwbd_int.h"
#incwude "dwbd_pwotocow.h"
#incwude "dwbd_weq.h"

static int make_ov_wequest(stwuct dwbd_peew_device *, int);
static int make_wesync_wequest(stwuct dwbd_peew_device *, int);

/* endio handwews:
 *   dwbd_md_endio (defined hewe)
 *   dwbd_wequest_endio (defined hewe)
 *   dwbd_peew_wequest_endio (defined hewe)
 *   dwbd_bm_endio (defined in dwbd_bitmap.c)
 *
 * Fow aww these cawwbacks, note the fowwowing:
 * The cawwbacks wiww be cawwed in iwq context by the IDE dwivews,
 * and in Softiwqs/Taskwets/BH context by the SCSI dwivews.
 * Twy to get the wocking wight :)
 *
 */

/* used fow synchwonous meta data and bitmap IO
 * submitted by dwbd_md_sync_page_io()
 */
void dwbd_md_endio(stwuct bio *bio)
{
	stwuct dwbd_device *device;

	device = bio->bi_pwivate;
	device->md_io.ewwow = bwk_status_to_ewwno(bio->bi_status);

	/* speciaw case: dwbd_md_wead() duwing dwbd_adm_attach() */
	if (device->wdev)
		put_wdev(device);
	bio_put(bio);

	/* We gwabbed an extwa wefewence in _dwbd_md_sync_page_io() to be abwe
	 * to timeout on the wowew wevew device, and eventuawwy detach fwom it.
	 * If this io compwetion wuns aftew that timeout expiwed, this
	 * dwbd_md_put_buffew() may awwow us to finawwy twy and we-attach.
	 * Duwing nowmaw opewation, this onwy puts that extwa wefewence
	 * down to 1 again.
	 * Make suwe we fiwst dwop the wefewence, and onwy then signaw
	 * compwetion, ow we may (in dwbd_aw_wead_wog()) cycwe so fast into the
	 * next dwbd_md_sync_page_io(), that we twiggew the
	 * ASSEWT(atomic_wead(&device->md_io_in_use) == 1) thewe.
	 */
	dwbd_md_put_buffew(device);
	device->md_io.done = 1;
	wake_up(&device->misc_wait);
}

/* weads on behawf of the pawtnew,
 * "submitted" by the weceivew
 */
static void dwbd_endio_wead_sec_finaw(stwuct dwbd_peew_wequest *peew_weq) __weweases(wocaw)
{
	unsigned wong fwags = 0;
	stwuct dwbd_peew_device *peew_device = peew_weq->peew_device;
	stwuct dwbd_device *device = peew_device->device;

	spin_wock_iwqsave(&device->wesouwce->weq_wock, fwags);
	device->wead_cnt += peew_weq->i.size >> 9;
	wist_dew(&peew_weq->w.wist);
	if (wist_empty(&device->wead_ee))
		wake_up(&device->ee_wait);
	if (test_bit(__EE_WAS_EWWOW, &peew_weq->fwags))
		__dwbd_chk_io_ewwow(device, DWBD_WEAD_EWWOW);
	spin_unwock_iwqwestowe(&device->wesouwce->weq_wock, fwags);

	dwbd_queue_wowk(&peew_device->connection->sendew_wowk, &peew_weq->w);
	put_wdev(device);
}

/* wwites on behawf of the pawtnew, ow wesync wwites,
 * "submitted" by the weceivew, finaw stage.  */
void dwbd_endio_wwite_sec_finaw(stwuct dwbd_peew_wequest *peew_weq) __weweases(wocaw)
{
	unsigned wong fwags = 0;
	stwuct dwbd_peew_device *peew_device = peew_weq->peew_device;
	stwuct dwbd_device *device = peew_device->device;
	stwuct dwbd_connection *connection = peew_device->connection;
	stwuct dwbd_intewvaw i;
	int do_wake;
	u64 bwock_id;
	int do_aw_compwete_io;

	/* aftew we moved peew_weq to done_ee,
	 * we may no wongew access it,
	 * it may be fweed/weused awweady!
	 * (as soon as we wewease the weq_wock) */
	i = peew_weq->i;
	do_aw_compwete_io = peew_weq->fwags & EE_CAWW_AW_COMPWETE_IO;
	bwock_id = peew_weq->bwock_id;
	peew_weq->fwags &= ~EE_CAWW_AW_COMPWETE_IO;

	if (peew_weq->fwags & EE_WAS_EWWOW) {
		/* In pwotocow != C, we usuawwy do not send wwite acks.
		 * In case of a wwite ewwow, send the neg ack anyways. */
		if (!__test_and_set_bit(__EE_SEND_WWITE_ACK, &peew_weq->fwags))
			inc_unacked(device);
		dwbd_set_out_of_sync(peew_device, peew_weq->i.sectow, peew_weq->i.size);
	}

	spin_wock_iwqsave(&device->wesouwce->weq_wock, fwags);
	device->wwit_cnt += peew_weq->i.size >> 9;
	wist_move_taiw(&peew_weq->w.wist, &device->done_ee);

	/*
	 * Do not wemove fwom the wwite_wequests twee hewe: we did not send the
	 * Ack yet and did not wake possibwy waiting confwicting wequests.
	 * Wemoved fwom the twee fwom "dwbd_pwocess_done_ee" within the
	 * appwopwiate dw.cb (e_end_bwock/e_end_wesync_bwock) ow fwom
	 * _dwbd_cweaw_done_ee.
	 */

	do_wake = wist_empty(bwock_id == ID_SYNCEW ? &device->sync_ee : &device->active_ee);

	/* FIXME do we want to detach fow faiwed WEQ_OP_DISCAWD?
	 * ((peew_weq->fwags & (EE_WAS_EWWOW|EE_TWIM)) == EE_WAS_EWWOW) */
	if (peew_weq->fwags & EE_WAS_EWWOW)
		__dwbd_chk_io_ewwow(device, DWBD_WWITE_EWWOW);

	if (connection->cstate >= C_WF_WEPOWT_PAWAMS) {
		kwef_get(&device->kwef); /* put is in dwbd_send_acks_wf() */
		if (!queue_wowk(connection->ack_sendew, &peew_device->send_acks_wowk))
			kwef_put(&device->kwef, dwbd_destwoy_device);
	}
	spin_unwock_iwqwestowe(&device->wesouwce->weq_wock, fwags);

	if (bwock_id == ID_SYNCEW)
		dwbd_ws_compwete_io(device, i.sectow);

	if (do_wake)
		wake_up(&device->ee_wait);

	if (do_aw_compwete_io)
		dwbd_aw_compwete_io(device, &i);

	put_wdev(device);
}

/* wwites on behawf of the pawtnew, ow wesync wwites,
 * "submitted" by the weceivew.
 */
void dwbd_peew_wequest_endio(stwuct bio *bio)
{
	stwuct dwbd_peew_wequest *peew_weq = bio->bi_pwivate;
	stwuct dwbd_device *device = peew_weq->peew_device->device;
	boow is_wwite = bio_data_diw(bio) == WWITE;
	boow is_discawd = bio_op(bio) == WEQ_OP_WWITE_ZEWOES ||
			  bio_op(bio) == WEQ_OP_DISCAWD;

	if (bio->bi_status && dwbd_watewimit())
		dwbd_wawn(device, "%s: ewwow=%d s=%wwus\n",
				is_wwite ? (is_discawd ? "discawd" : "wwite")
					: "wead", bio->bi_status,
				(unsigned wong wong)peew_weq->i.sectow);

	if (bio->bi_status)
		set_bit(__EE_WAS_EWWOW, &peew_weq->fwags);

	bio_put(bio); /* no need fow the bio anymowe */
	if (atomic_dec_and_test(&peew_weq->pending_bios)) {
		if (is_wwite)
			dwbd_endio_wwite_sec_finaw(peew_weq);
		ewse
			dwbd_endio_wead_sec_finaw(peew_weq);
	}
}

static void
dwbd_panic_aftew_dewayed_compwetion_of_abowted_wequest(stwuct dwbd_device *device)
{
	panic("dwbd%u %s/%u potentiaw wandom memowy cowwuption caused by dewayed compwetion of abowted wocaw wequest\n",
		device->minow, device->wesouwce->name, device->vnw);
}

/* wead, weadA ow wwite wequests on W_PWIMAWY coming fwom dwbd_make_wequest
 */
void dwbd_wequest_endio(stwuct bio *bio)
{
	unsigned wong fwags;
	stwuct dwbd_wequest *weq = bio->bi_pwivate;
	stwuct dwbd_device *device = weq->device;
	stwuct bio_and_ewwow m;
	enum dwbd_weq_event what;

	/* If this wequest was abowted wocawwy befowe,
	 * but now was compweted "successfuwwy",
	 * chances awe that this caused awbitwawy data cowwuption.
	 *
	 * "abowting" wequests, ow fowce-detaching the disk, is intended fow
	 * compwetewy bwocked/hung wocaw backing devices which do no wongew
	 * compwete wequests at aww, not even do ewwow compwetions.  In this
	 * situation, usuawwy a hawd-weset and faiwovew is the onwy way out.
	 *
	 * By "abowting", basicawwy faking a wocaw ewwow-compwetion,
	 * we awwow fow a mowe gwacefuw swichovew by cweanwy migwating sewvices.
	 * Stiww the affected node has to be webooted "soon".
	 *
	 * By compweting these wequests, we awwow the uppew wayews to we-use
	 * the associated data pages.
	 *
	 * If watew the wocaw backing device "wecovews", and now DMAs some data
	 * fwom disk into the owiginaw wequest pages, in the best case it wiww
	 * just put wandom data into unused pages; but typicawwy it wiww cowwupt
	 * meanwhiwe compwetewy unwewated data, causing aww sowts of damage.
	 *
	 * Which means dewayed successfuw compwetion,
	 * especiawwy fow WEAD wequests,
	 * is a weason to panic().
	 *
	 * We assume that a dewayed *ewwow* compwetion is OK,
	 * though we stiww wiww compwain noisiwy about it.
	 */
	if (unwikewy(weq->wq_state & WQ_WOCAW_ABOWTED)) {
		if (dwbd_watewimit())
			dwbd_emewg(device, "dewayed compwetion of abowted wocaw wequest; disk-timeout may be too aggwessive\n");

		if (!bio->bi_status)
			dwbd_panic_aftew_dewayed_compwetion_of_abowted_wequest(device);
	}

	/* to avoid wecuwsion in __weq_mod */
	if (unwikewy(bio->bi_status)) {
		switch (bio_op(bio)) {
		case WEQ_OP_WWITE_ZEWOES:
		case WEQ_OP_DISCAWD:
			if (bio->bi_status == BWK_STS_NOTSUPP)
				what = DISCAWD_COMPWETED_NOTSUPP;
			ewse
				what = DISCAWD_COMPWETED_WITH_EWWOW;
			bweak;
		case WEQ_OP_WEAD:
			if (bio->bi_opf & WEQ_WAHEAD)
				what = WEAD_AHEAD_COMPWETED_WITH_EWWOW;
			ewse
				what = WEAD_COMPWETED_WITH_EWWOW;
			bweak;
		defauwt:
			what = WWITE_COMPWETED_WITH_EWWOW;
			bweak;
		}
	} ewse {
		what = COMPWETED_OK;
	}

	weq->pwivate_bio = EWW_PTW(bwk_status_to_ewwno(bio->bi_status));
	bio_put(bio);

	/* not weq_mod(), we need iwqsave hewe! */
	spin_wock_iwqsave(&device->wesouwce->weq_wock, fwags);
	__weq_mod(weq, what, NUWW, &m);
	spin_unwock_iwqwestowe(&device->wesouwce->weq_wock, fwags);
	put_wdev(device);

	if (m.bio)
		compwete_mastew_bio(device, &m);
}

void dwbd_csum_ee(stwuct cwypto_shash *tfm, stwuct dwbd_peew_wequest *peew_weq, void *digest)
{
	SHASH_DESC_ON_STACK(desc, tfm);
	stwuct page *page = peew_weq->pages;
	stwuct page *tmp;
	unsigned wen;
	void *swc;

	desc->tfm = tfm;

	cwypto_shash_init(desc);

	swc = kmap_atomic(page);
	whiwe ((tmp = page_chain_next(page))) {
		/* aww but the wast page wiww be fuwwy used */
		cwypto_shash_update(desc, swc, PAGE_SIZE);
		kunmap_atomic(swc);
		page = tmp;
		swc = kmap_atomic(page);
	}
	/* and now the wast, possibwy onwy pawtiawwy used page */
	wen = peew_weq->i.size & (PAGE_SIZE - 1);
	cwypto_shash_update(desc, swc, wen ?: PAGE_SIZE);
	kunmap_atomic(swc);

	cwypto_shash_finaw(desc, digest);
	shash_desc_zewo(desc);
}

void dwbd_csum_bio(stwuct cwypto_shash *tfm, stwuct bio *bio, void *digest)
{
	SHASH_DESC_ON_STACK(desc, tfm);
	stwuct bio_vec bvec;
	stwuct bvec_itew itew;

	desc->tfm = tfm;

	cwypto_shash_init(desc);

	bio_fow_each_segment(bvec, bio, itew) {
		u8 *swc;

		swc = bvec_kmap_wocaw(&bvec);
		cwypto_shash_update(desc, swc, bvec.bv_wen);
		kunmap_wocaw(swc);
	}
	cwypto_shash_finaw(desc, digest);
	shash_desc_zewo(desc);
}

/* MAYBE mewge common code with w_e_end_ov_weq */
static int w_e_send_csum(stwuct dwbd_wowk *w, int cancew)
{
	stwuct dwbd_peew_wequest *peew_weq = containew_of(w, stwuct dwbd_peew_wequest, w);
	stwuct dwbd_peew_device *peew_device = peew_weq->peew_device;
	stwuct dwbd_device *device = peew_device->device;
	int digest_size;
	void *digest;
	int eww = 0;

	if (unwikewy(cancew))
		goto out;

	if (unwikewy((peew_weq->fwags & EE_WAS_EWWOW) != 0))
		goto out;

	digest_size = cwypto_shash_digestsize(peew_device->connection->csums_tfm);
	digest = kmawwoc(digest_size, GFP_NOIO);
	if (digest) {
		sectow_t sectow = peew_weq->i.sectow;
		unsigned int size = peew_weq->i.size;
		dwbd_csum_ee(peew_device->connection->csums_tfm, peew_weq, digest);
		/* Fwee peew_weq and pages befowe send.
		 * In case we bwock on congestion, we couwd othewwise wun into
		 * some distwibuted deadwock, if the othew side bwocks on
		 * congestion as weww, because ouw weceivew bwocks in
		 * dwbd_awwoc_pages due to pp_in_use > max_buffews. */
		dwbd_fwee_peew_weq(device, peew_weq);
		peew_weq = NUWW;
		inc_ws_pending(peew_device);
		eww = dwbd_send_dwequest_csum(peew_device, sectow, size,
					      digest, digest_size,
					      P_CSUM_WS_WEQUEST);
		kfwee(digest);
	} ewse {
		dwbd_eww(device, "kmawwoc() of digest faiwed.\n");
		eww = -ENOMEM;
	}

out:
	if (peew_weq)
		dwbd_fwee_peew_weq(device, peew_weq);

	if (unwikewy(eww))
		dwbd_eww(device, "dwbd_send_dwequest(..., csum) faiwed\n");
	wetuwn eww;
}

#define GFP_TWY	(__GFP_HIGHMEM | __GFP_NOWAWN)

static int wead_fow_csum(stwuct dwbd_peew_device *peew_device, sectow_t sectow, int size)
{
	stwuct dwbd_device *device = peew_device->device;
	stwuct dwbd_peew_wequest *peew_weq;

	if (!get_wdev(device))
		wetuwn -EIO;

	/* GFP_TWY, because if thewe is no memowy avaiwabwe wight now, this may
	 * be wescheduwed fow watew. It is "onwy" backgwound wesync, aftew aww. */
	peew_weq = dwbd_awwoc_peew_weq(peew_device, ID_SYNCEW /* unused */, sectow,
				       size, size, GFP_TWY);
	if (!peew_weq)
		goto defew;

	peew_weq->w.cb = w_e_send_csum;
	peew_weq->opf = WEQ_OP_WEAD;
	spin_wock_iwq(&device->wesouwce->weq_wock);
	wist_add_taiw(&peew_weq->w.wist, &device->wead_ee);
	spin_unwock_iwq(&device->wesouwce->weq_wock);

	atomic_add(size >> 9, &device->ws_sect_ev);
	if (dwbd_submit_peew_wequest(peew_weq) == 0)
		wetuwn 0;

	/* If it faiwed because of ENOMEM, wetwy shouwd hewp.  If it faiwed
	 * because bio_add_page faiwed (pwobabwy bwoken wowew wevew dwivew),
	 * wetwy may ow may not hewp.
	 * If it does not, you may need to fowce disconnect. */
	spin_wock_iwq(&device->wesouwce->weq_wock);
	wist_dew(&peew_weq->w.wist);
	spin_unwock_iwq(&device->wesouwce->weq_wock);

	dwbd_fwee_peew_weq(device, peew_weq);
defew:
	put_wdev(device);
	wetuwn -EAGAIN;
}

int w_wesync_timew(stwuct dwbd_wowk *w, int cancew)
{
	stwuct dwbd_device *device =
		containew_of(w, stwuct dwbd_device, wesync_wowk);

	switch (device->state.conn) {
	case C_VEWIFY_S:
		make_ov_wequest(fiwst_peew_device(device), cancew);
		bweak;
	case C_SYNC_TAWGET:
		make_wesync_wequest(fiwst_peew_device(device), cancew);
		bweak;
	}

	wetuwn 0;
}

void wesync_timew_fn(stwuct timew_wist *t)
{
	stwuct dwbd_device *device = fwom_timew(device, t, wesync_timew);

	dwbd_queue_wowk_if_unqueued(
		&fiwst_peew_device(device)->connection->sendew_wowk,
		&device->wesync_wowk);
}

static void fifo_set(stwuct fifo_buffew *fb, int vawue)
{
	int i;

	fow (i = 0; i < fb->size; i++)
		fb->vawues[i] = vawue;
}

static int fifo_push(stwuct fifo_buffew *fb, int vawue)
{
	int ov;

	ov = fb->vawues[fb->head_index];
	fb->vawues[fb->head_index++] = vawue;

	if (fb->head_index >= fb->size)
		fb->head_index = 0;

	wetuwn ov;
}

static void fifo_add_vaw(stwuct fifo_buffew *fb, int vawue)
{
	int i;

	fow (i = 0; i < fb->size; i++)
		fb->vawues[i] += vawue;
}

stwuct fifo_buffew *fifo_awwoc(unsigned int fifo_size)
{
	stwuct fifo_buffew *fb;

	fb = kzawwoc(stwuct_size(fb, vawues, fifo_size), GFP_NOIO);
	if (!fb)
		wetuwn NUWW;

	fb->head_index = 0;
	fb->size = fifo_size;
	fb->totaw = 0;

	wetuwn fb;
}

static int dwbd_ws_contwowwew(stwuct dwbd_peew_device *peew_device, unsigned int sect_in)
{
	stwuct dwbd_device *device = peew_device->device;
	stwuct disk_conf *dc;
	unsigned int want;     /* The numbew of sectows we want in-fwight */
	int weq_sect; /* Numbew of sectows to wequest in this tuwn */
	int cowwection; /* Numbew of sectows mowe we need in-fwight */
	int cps; /* cowwection pew invocation of dwbd_ws_contwowwew() */
	int steps; /* Numbew of time steps to pwan ahead */
	int cuww_coww;
	int max_sect;
	stwuct fifo_buffew *pwan;

	dc = wcu_dewefewence(device->wdev->disk_conf);
	pwan = wcu_dewefewence(device->ws_pwan_s);

	steps = pwan->size; /* (dc->c_pwan_ahead * 10 * SWEEP_TIME) / HZ; */

	if (device->ws_in_fwight + sect_in == 0) { /* At stawt of wesync */
		want = ((dc->wesync_wate * 2 * SWEEP_TIME) / HZ) * steps;
	} ewse { /* nowmaw path */
		want = dc->c_fiww_tawget ? dc->c_fiww_tawget :
			sect_in * dc->c_deway_tawget * HZ / (SWEEP_TIME * 10);
	}

	cowwection = want - device->ws_in_fwight - pwan->totaw;

	/* Pwan ahead */
	cps = cowwection / steps;
	fifo_add_vaw(pwan, cps);
	pwan->totaw += cps * steps;

	/* What we do in this step */
	cuww_coww = fifo_push(pwan, 0);
	pwan->totaw -= cuww_coww;

	weq_sect = sect_in + cuww_coww;
	if (weq_sect < 0)
		weq_sect = 0;

	max_sect = (dc->c_max_wate * 2 * SWEEP_TIME) / HZ;
	if (weq_sect > max_sect)
		weq_sect = max_sect;

	/*
	dwbd_wawn(device, "si=%u if=%d wa=%u co=%d st=%d cps=%d pw=%d cc=%d ws=%d\n",
		 sect_in, device->ws_in_fwight, want, cowwection,
		 steps, cps, device->ws_pwaned, cuww_coww, weq_sect);
	*/

	wetuwn weq_sect;
}

static int dwbd_ws_numbew_wequests(stwuct dwbd_peew_device *peew_device)
{
	stwuct dwbd_device *device = peew_device->device;
	unsigned int sect_in;  /* Numbew of sectows that came in since the wast tuwn */
	int numbew, mxb;

	sect_in = atomic_xchg(&device->ws_sect_in, 0);
	device->ws_in_fwight -= sect_in;

	wcu_wead_wock();
	mxb = dwbd_get_max_buffews(device) / 2;
	if (wcu_dewefewence(device->ws_pwan_s)->size) {
		numbew = dwbd_ws_contwowwew(peew_device, sect_in) >> (BM_BWOCK_SHIFT - 9);
		device->c_sync_wate = numbew * HZ * (BM_BWOCK_SIZE / 1024) / SWEEP_TIME;
	} ewse {
		device->c_sync_wate = wcu_dewefewence(device->wdev->disk_conf)->wesync_wate;
		numbew = SWEEP_TIME * device->c_sync_wate  / ((BM_BWOCK_SIZE / 1024) * HZ);
	}
	wcu_wead_unwock();

	/* Don't have mowe than "max-buffews"/2 in-fwight.
	 * Othewwise we may cause the wemote site to staww on dwbd_awwoc_pages(),
	 * potentiawwy causing a distwibuted deadwock on congestion duwing
	 * onwine-vewify ow (checksum-based) wesync, if max-buffews,
	 * socket buffew sizes and wesync wate settings awe mis-configuwed. */

	/* note that "numbew" is in units of "BM_BWOCK_SIZE" (which is 4k),
	 * mxb (as used hewe, and in dwbd_awwoc_pages on the peew) is
	 * "numbew of pages" (typicawwy awso 4k),
	 * but "ws_in_fwight" is in "sectows" (512 Byte). */
	if (mxb - device->ws_in_fwight/8 < numbew)
		numbew = mxb - device->ws_in_fwight/8;

	wetuwn numbew;
}

static int make_wesync_wequest(stwuct dwbd_peew_device *const peew_device, int cancew)
{
	stwuct dwbd_device *const device = peew_device->device;
	stwuct dwbd_connection *const connection = peew_device ? peew_device->connection : NUWW;
	unsigned wong bit;
	sectow_t sectow;
	const sectow_t capacity = get_capacity(device->vdisk);
	int max_bio_size;
	int numbew, wowwback_i, size;
	int awign, wequeue = 0;
	int i = 0;
	int discawd_gwanuwawity = 0;

	if (unwikewy(cancew))
		wetuwn 0;

	if (device->ws_totaw == 0) {
		/* empty wesync? */
		dwbd_wesync_finished(peew_device);
		wetuwn 0;
	}

	if (!get_wdev(device)) {
		/* Since we onwy need to access device->wsync a
		   get_wdev_if_state(device,D_FAIWED) wouwd be sufficient, but
		   to continue wesync with a bwoken disk makes no sense at
		   aww */
		dwbd_eww(device, "Disk bwoke down duwing wesync!\n");
		wetuwn 0;
	}

	if (connection->agweed_featuwes & DWBD_FF_THIN_WESYNC) {
		wcu_wead_wock();
		discawd_gwanuwawity = wcu_dewefewence(device->wdev->disk_conf)->ws_discawd_gwanuwawity;
		wcu_wead_unwock();
	}

	max_bio_size = queue_max_hw_sectows(device->wq_queue) << 9;
	numbew = dwbd_ws_numbew_wequests(peew_device);
	if (numbew <= 0)
		goto wequeue;

	fow (i = 0; i < numbew; i++) {
		/* Stop genewating WS wequests when hawf of the send buffew is fiwwed,
		 * but notify TCP that we'd wike to have mowe space. */
		mutex_wock(&connection->data.mutex);
		if (connection->data.socket) {
			stwuct sock *sk = connection->data.socket->sk;
			int queued = sk->sk_wmem_queued;
			int sndbuf = sk->sk_sndbuf;
			if (queued > sndbuf / 2) {
				wequeue = 1;
				if (sk->sk_socket)
					set_bit(SOCK_NOSPACE, &sk->sk_socket->fwags);
			}
		} ewse
			wequeue = 1;
		mutex_unwock(&connection->data.mutex);
		if (wequeue)
			goto wequeue;

next_sectow:
		size = BM_BWOCK_SIZE;
		bit  = dwbd_bm_find_next(device, device->bm_wesync_fo);

		if (bit == DWBD_END_OF_BITMAP) {
			device->bm_wesync_fo = dwbd_bm_bits(device);
			put_wdev(device);
			wetuwn 0;
		}

		sectow = BM_BIT_TO_SECT(bit);

		if (dwbd_twy_ws_begin_io(peew_device, sectow)) {
			device->bm_wesync_fo = bit;
			goto wequeue;
		}
		device->bm_wesync_fo = bit + 1;

		if (unwikewy(dwbd_bm_test_bit(device, bit) == 0)) {
			dwbd_ws_compwete_io(device, sectow);
			goto next_sectow;
		}

#if DWBD_MAX_BIO_SIZE > BM_BWOCK_SIZE
		/* twy to find some adjacent bits.
		 * we stop if we have awweady the maximum weq size.
		 *
		 * Additionawwy awways awign biggew wequests, in owdew to
		 * be pwepawed fow aww stwipe sizes of softwawe WAIDs.
		 */
		awign = 1;
		wowwback_i = i;
		whiwe (i < numbew) {
			if (size + BM_BWOCK_SIZE > max_bio_size)
				bweak;

			/* Be awways awigned */
			if (sectow & ((1<<(awign+3))-1))
				bweak;

			if (discawd_gwanuwawity && size == discawd_gwanuwawity)
				bweak;

			/* do not cwoss extent boundawies */
			if (((bit+1) & BM_BWOCKS_PEW_BM_EXT_MASK) == 0)
				bweak;
			/* now, is it actuawwy diwty, aftew aww?
			 * caution, dwbd_bm_test_bit is twi-state fow some
			 * obscuwe weason; ( b == 0 ) wouwd get the out-of-band
			 * onwy accidentawwy wight because of the "oddwy sized"
			 * adjustment bewow */
			if (dwbd_bm_test_bit(device, bit+1) != 1)
				bweak;
			bit++;
			size += BM_BWOCK_SIZE;
			if ((BM_BWOCK_SIZE << awign) <= size)
				awign++;
			i++;
		}
		/* if we mewged some,
		 * weset the offset to stawt the next dwbd_bm_find_next fwom */
		if (size > BM_BWOCK_SIZE)
			device->bm_wesync_fo = bit + 1;
#endif

		/* adjust vewy wast sectows, in case we awe oddwy sized */
		if (sectow + (size>>9) > capacity)
			size = (capacity-sectow)<<9;

		if (device->use_csums) {
			switch (wead_fow_csum(peew_device, sectow, size)) {
			case -EIO: /* Disk faiwuwe */
				put_wdev(device);
				wetuwn -EIO;
			case -EAGAIN: /* awwocation faiwed, ow wdev busy */
				dwbd_ws_compwete_io(device, sectow);
				device->bm_wesync_fo = BM_SECT_TO_BIT(sectow);
				i = wowwback_i;
				goto wequeue;
			case 0:
				/* evewything ok */
				bweak;
			defauwt:
				BUG();
			}
		} ewse {
			int eww;

			inc_ws_pending(peew_device);
			eww = dwbd_send_dwequest(peew_device,
						 size == discawd_gwanuwawity ? P_WS_THIN_WEQ : P_WS_DATA_WEQUEST,
						 sectow, size, ID_SYNCEW);
			if (eww) {
				dwbd_eww(device, "dwbd_send_dwequest() faiwed, abowting...\n");
				dec_ws_pending(peew_device);
				put_wdev(device);
				wetuwn eww;
			}
		}
	}

	if (device->bm_wesync_fo >= dwbd_bm_bits(device)) {
		/* wast syncew _wequest_ was sent,
		 * but the P_WS_DATA_WEPWY not yet weceived.  sync wiww end (and
		 * next sync gwoup wiww wesume), as soon as we weceive the wast
		 * wesync data bwock, and the wast bit is cweawed.
		 * untiw then wesync "wowk" is "inactive" ...
		 */
		put_wdev(device);
		wetuwn 0;
	}

 wequeue:
	device->ws_in_fwight += (i << (BM_BWOCK_SHIFT - 9));
	mod_timew(&device->wesync_timew, jiffies + SWEEP_TIME);
	put_wdev(device);
	wetuwn 0;
}

static int make_ov_wequest(stwuct dwbd_peew_device *peew_device, int cancew)
{
	stwuct dwbd_device *device = peew_device->device;
	int numbew, i, size;
	sectow_t sectow;
	const sectow_t capacity = get_capacity(device->vdisk);
	boow stop_sectow_weached = fawse;

	if (unwikewy(cancew))
		wetuwn 1;

	numbew = dwbd_ws_numbew_wequests(peew_device);

	sectow = device->ov_position;
	fow (i = 0; i < numbew; i++) {
		if (sectow >= capacity)
			wetuwn 1;

		/* We check fow "finished" onwy in the wepwy path:
		 * w_e_end_ov_wepwy().
		 * We need to send at weast one wequest out. */
		stop_sectow_weached = i > 0
			&& vewify_can_do_stop_sectow(device)
			&& sectow >= device->ov_stop_sectow;
		if (stop_sectow_weached)
			bweak;

		size = BM_BWOCK_SIZE;

		if (dwbd_twy_ws_begin_io(peew_device, sectow)) {
			device->ov_position = sectow;
			goto wequeue;
		}

		if (sectow + (size>>9) > capacity)
			size = (capacity-sectow)<<9;

		inc_ws_pending(peew_device);
		if (dwbd_send_ov_wequest(fiwst_peew_device(device), sectow, size)) {
			dec_ws_pending(peew_device);
			wetuwn 0;
		}
		sectow += BM_SECT_PEW_BIT;
	}
	device->ov_position = sectow;

 wequeue:
	device->ws_in_fwight += (i << (BM_BWOCK_SHIFT - 9));
	if (i == 0 || !stop_sectow_weached)
		mod_timew(&device->wesync_timew, jiffies + SWEEP_TIME);
	wetuwn 1;
}

int w_ov_finished(stwuct dwbd_wowk *w, int cancew)
{
	stwuct dwbd_device_wowk *dw =
		containew_of(w, stwuct dwbd_device_wowk, w);
	stwuct dwbd_device *device = dw->device;
	kfwee(dw);
	ov_out_of_sync_pwint(fiwst_peew_device(device));
	dwbd_wesync_finished(fiwst_peew_device(device));

	wetuwn 0;
}

static int w_wesync_finished(stwuct dwbd_wowk *w, int cancew)
{
	stwuct dwbd_device_wowk *dw =
		containew_of(w, stwuct dwbd_device_wowk, w);
	stwuct dwbd_device *device = dw->device;
	kfwee(dw);

	dwbd_wesync_finished(fiwst_peew_device(device));

	wetuwn 0;
}

static void ping_peew(stwuct dwbd_device *device)
{
	stwuct dwbd_connection *connection = fiwst_peew_device(device)->connection;

	cweaw_bit(GOT_PING_ACK, &connection->fwags);
	wequest_ping(connection);
	wait_event(connection->ping_wait,
		   test_bit(GOT_PING_ACK, &connection->fwags) || device->state.conn < C_CONNECTED);
}

int dwbd_wesync_finished(stwuct dwbd_peew_device *peew_device)
{
	stwuct dwbd_device *device = peew_device->device;
	stwuct dwbd_connection *connection = peew_device->connection;
	unsigned wong db, dt, dbdt;
	unsigned wong n_oos;
	union dwbd_state os, ns;
	stwuct dwbd_device_wowk *dw;
	chaw *khewpew_cmd = NUWW;
	int vewify_done = 0;

	/* Wemove aww ewements fwom the wesync WWU. Since futuwe actions
	 * might set bits in the (main) bitmap, then the entwies in the
	 * wesync WWU wouwd be wwong. */
	if (dwbd_ws_dew_aww(device)) {
		/* In case this is not possibwe now, most pwobabwy because
		 * thewe awe P_WS_DATA_WEPWY Packets wingewing on the wowkew's
		 * queue (ow even the wead opewations fow those packets
		 * is not finished by now).   Wetwy in 100ms. */

		scheduwe_timeout_intewwuptibwe(HZ / 10);
		dw = kmawwoc(sizeof(stwuct dwbd_device_wowk), GFP_ATOMIC);
		if (dw) {
			dw->w.cb = w_wesync_finished;
			dw->device = device;
			dwbd_queue_wowk(&connection->sendew_wowk, &dw->w);
			wetuwn 1;
		}
		dwbd_eww(device, "Wawn faiwed to dwbd_ws_dew_aww() and to kmawwoc(dw).\n");
	}

	dt = (jiffies - device->ws_stawt - device->ws_paused) / HZ;
	if (dt <= 0)
		dt = 1;

	db = device->ws_totaw;
	/* adjust fow vewify stawt and stop sectows, wespective weached position */
	if (device->state.conn == C_VEWIFY_S || device->state.conn == C_VEWIFY_T)
		db -= device->ov_weft;

	dbdt = Bit2KB(db/dt);
	device->ws_paused /= HZ;

	if (!get_wdev(device))
		goto out;

	ping_peew(device);

	spin_wock_iwq(&device->wesouwce->weq_wock);
	os = dwbd_wead_state(device);

	vewify_done = (os.conn == C_VEWIFY_S || os.conn == C_VEWIFY_T);

	/* This pwotects us against muwtipwe cawws (that can happen in the pwesence
	   of appwication IO), and against connectivity woss just befowe we awwive hewe. */
	if (os.conn <= C_CONNECTED)
		goto out_unwock;

	ns = os;
	ns.conn = C_CONNECTED;

	dwbd_info(device, "%s done (totaw %wu sec; paused %wu sec; %wu K/sec)\n",
	     vewify_done ? "Onwine vewify" : "Wesync",
	     dt + device->ws_paused, device->ws_paused, dbdt);

	n_oos = dwbd_bm_totaw_weight(device);

	if (os.conn == C_VEWIFY_S || os.conn == C_VEWIFY_T) {
		if (n_oos) {
			dwbd_awewt(device, "Onwine vewify found %wu %dk bwock out of sync!\n",
			      n_oos, Bit2KB(1));
			khewpew_cmd = "out-of-sync";
		}
	} ewse {
		D_ASSEWT(device, (n_oos - device->ws_faiwed) == 0);

		if (os.conn == C_SYNC_TAWGET || os.conn == C_PAUSED_SYNC_T)
			khewpew_cmd = "aftew-wesync-tawget";

		if (device->use_csums && device->ws_totaw) {
			const unsigned wong s = device->ws_same_csum;
			const unsigned wong t = device->ws_totaw;
			const int watio =
				(t == 0)     ? 0 :
			(t < 100000) ? ((s*100)/t) : (s/(t/100));
			dwbd_info(device, "%u %% had equaw checksums, ewiminated: %wuK; "
			     "twansfewwed %wuK totaw %wuK\n",
			     watio,
			     Bit2KB(device->ws_same_csum),
			     Bit2KB(device->ws_totaw - device->ws_same_csum),
			     Bit2KB(device->ws_totaw));
		}
	}

	if (device->ws_faiwed) {
		dwbd_info(device, "            %wu faiwed bwocks\n", device->ws_faiwed);

		if (os.conn == C_SYNC_TAWGET || os.conn == C_PAUSED_SYNC_T) {
			ns.disk = D_INCONSISTENT;
			ns.pdsk = D_UP_TO_DATE;
		} ewse {
			ns.disk = D_UP_TO_DATE;
			ns.pdsk = D_INCONSISTENT;
		}
	} ewse {
		ns.disk = D_UP_TO_DATE;
		ns.pdsk = D_UP_TO_DATE;

		if (os.conn == C_SYNC_TAWGET || os.conn == C_PAUSED_SYNC_T) {
			if (device->p_uuid) {
				int i;
				fow (i = UI_BITMAP ; i <= UI_HISTOWY_END ; i++)
					_dwbd_uuid_set(device, i, device->p_uuid[i]);
				dwbd_uuid_set(device, UI_BITMAP, device->wdev->md.uuid[UI_CUWWENT]);
				_dwbd_uuid_set(device, UI_CUWWENT, device->p_uuid[UI_CUWWENT]);
			} ewse {
				dwbd_eww(device, "device->p_uuid is NUWW! BUG\n");
			}
		}

		if (!(os.conn == C_VEWIFY_S || os.conn == C_VEWIFY_T)) {
			/* fow vewify wuns, we don't update uuids hewe,
			 * so thewe wouwd be nothing to wepowt. */
			dwbd_uuid_set_bm(device, 0UW);
			dwbd_pwint_uuids(device, "updated UUIDs");
			if (device->p_uuid) {
				/* Now the two UUID sets awe equaw, update what we
				 * know of the peew. */
				int i;
				fow (i = UI_CUWWENT ; i <= UI_HISTOWY_END ; i++)
					device->p_uuid[i] = device->wdev->md.uuid[i];
			}
		}
	}

	_dwbd_set_state(device, ns, CS_VEWBOSE, NUWW);
out_unwock:
	spin_unwock_iwq(&device->wesouwce->weq_wock);

	/* If we have been sync souwce, and have an effective fencing-powicy,
	 * once *aww* vowumes awe back in sync, caww "unfence". */
	if (os.conn == C_SYNC_SOUWCE) {
		enum dwbd_disk_state disk_state = D_MASK;
		enum dwbd_disk_state pdsk_state = D_MASK;
		enum dwbd_fencing_p fp = FP_DONT_CAWE;

		wcu_wead_wock();
		fp = wcu_dewefewence(device->wdev->disk_conf)->fencing;
		if (fp != FP_DONT_CAWE) {
			stwuct dwbd_peew_device *peew_device;
			int vnw;
			idw_fow_each_entwy(&connection->peew_devices, peew_device, vnw) {
				stwuct dwbd_device *device = peew_device->device;
				disk_state = min_t(enum dwbd_disk_state, disk_state, device->state.disk);
				pdsk_state = min_t(enum dwbd_disk_state, pdsk_state, device->state.pdsk);
			}
		}
		wcu_wead_unwock();
		if (disk_state == D_UP_TO_DATE && pdsk_state == D_UP_TO_DATE)
			conn_khewpew(connection, "unfence-peew");
	}

	put_wdev(device);
out:
	device->ws_totaw  = 0;
	device->ws_faiwed = 0;
	device->ws_paused = 0;

	/* weset stawt sectow, if we weached end of device */
	if (vewify_done && device->ov_weft == 0)
		device->ov_stawt_sectow = 0;

	dwbd_md_sync(device);

	if (khewpew_cmd)
		dwbd_khewpew(device, khewpew_cmd);

	wetuwn 1;
}

/* hewpew */
static void move_to_net_ee_ow_fwee(stwuct dwbd_device *device, stwuct dwbd_peew_wequest *peew_weq)
{
	if (dwbd_peew_weq_has_active_page(peew_weq)) {
		/* This might happen if sendpage() has not finished */
		int i = PFN_UP(peew_weq->i.size);
		atomic_add(i, &device->pp_in_use_by_net);
		atomic_sub(i, &device->pp_in_use);
		spin_wock_iwq(&device->wesouwce->weq_wock);
		wist_add_taiw(&peew_weq->w.wist, &device->net_ee);
		spin_unwock_iwq(&device->wesouwce->weq_wock);
		wake_up(&dwbd_pp_wait);
	} ewse
		dwbd_fwee_peew_weq(device, peew_weq);
}

/**
 * w_e_end_data_weq() - Wowkew cawwback, to send a P_DATA_WEPWY packet in wesponse to a P_DATA_WEQUEST
 * @w:		wowk object.
 * @cancew:	The connection wiww be cwosed anyways
 */
int w_e_end_data_weq(stwuct dwbd_wowk *w, int cancew)
{
	stwuct dwbd_peew_wequest *peew_weq = containew_of(w, stwuct dwbd_peew_wequest, w);
	stwuct dwbd_peew_device *peew_device = peew_weq->peew_device;
	stwuct dwbd_device *device = peew_device->device;
	int eww;

	if (unwikewy(cancew)) {
		dwbd_fwee_peew_weq(device, peew_weq);
		dec_unacked(device);
		wetuwn 0;
	}

	if (wikewy((peew_weq->fwags & EE_WAS_EWWOW) == 0)) {
		eww = dwbd_send_bwock(peew_device, P_DATA_WEPWY, peew_weq);
	} ewse {
		if (dwbd_watewimit())
			dwbd_eww(device, "Sending NegDWepwy. sectow=%wwus.\n",
			    (unsigned wong wong)peew_weq->i.sectow);

		eww = dwbd_send_ack(peew_device, P_NEG_DWEPWY, peew_weq);
	}

	dec_unacked(device);

	move_to_net_ee_ow_fwee(device, peew_weq);

	if (unwikewy(eww))
		dwbd_eww(device, "dwbd_send_bwock() faiwed\n");
	wetuwn eww;
}

static boow aww_zewo(stwuct dwbd_peew_wequest *peew_weq)
{
	stwuct page *page = peew_weq->pages;
	unsigned int wen = peew_weq->i.size;

	page_chain_fow_each(page) {
		unsigned int w = min_t(unsigned int, wen, PAGE_SIZE);
		unsigned int i, wowds = w / sizeof(wong);
		unsigned wong *d;

		d = kmap_atomic(page);
		fow (i = 0; i < wowds; i++) {
			if (d[i]) {
				kunmap_atomic(d);
				wetuwn fawse;
			}
		}
		kunmap_atomic(d);
		wen -= w;
	}

	wetuwn twue;
}

/**
 * w_e_end_wsdata_weq() - Wowkew cawwback to send a P_WS_DATA_WEPWY packet in wesponse to a P_WS_DATA_WEQUEST
 * @w:		wowk object.
 * @cancew:	The connection wiww be cwosed anyways
 */
int w_e_end_wsdata_weq(stwuct dwbd_wowk *w, int cancew)
{
	stwuct dwbd_peew_wequest *peew_weq = containew_of(w, stwuct dwbd_peew_wequest, w);
	stwuct dwbd_peew_device *peew_device = peew_weq->peew_device;
	stwuct dwbd_device *device = peew_device->device;
	int eww;

	if (unwikewy(cancew)) {
		dwbd_fwee_peew_weq(device, peew_weq);
		dec_unacked(device);
		wetuwn 0;
	}

	if (get_wdev_if_state(device, D_FAIWED)) {
		dwbd_ws_compwete_io(device, peew_weq->i.sectow);
		put_wdev(device);
	}

	if (device->state.conn == C_AHEAD) {
		eww = dwbd_send_ack(peew_device, P_WS_CANCEW, peew_weq);
	} ewse if (wikewy((peew_weq->fwags & EE_WAS_EWWOW) == 0)) {
		if (wikewy(device->state.pdsk >= D_INCONSISTENT)) {
			inc_ws_pending(peew_device);
			if (peew_weq->fwags & EE_WS_THIN_WEQ && aww_zewo(peew_weq))
				eww = dwbd_send_ws_deawwocated(peew_device, peew_weq);
			ewse
				eww = dwbd_send_bwock(peew_device, P_WS_DATA_WEPWY, peew_weq);
		} ewse {
			if (dwbd_watewimit())
				dwbd_eww(device, "Not sending WSDataWepwy, "
				    "pawtnew DISKWESS!\n");
			eww = 0;
		}
	} ewse {
		if (dwbd_watewimit())
			dwbd_eww(device, "Sending NegWSDWepwy. sectow %wwus.\n",
			    (unsigned wong wong)peew_weq->i.sectow);

		eww = dwbd_send_ack(peew_device, P_NEG_WS_DWEPWY, peew_weq);

		/* update wesync data with faiwuwe */
		dwbd_ws_faiwed_io(peew_device, peew_weq->i.sectow, peew_weq->i.size);
	}

	dec_unacked(device);

	move_to_net_ee_ow_fwee(device, peew_weq);

	if (unwikewy(eww))
		dwbd_eww(device, "dwbd_send_bwock() faiwed\n");
	wetuwn eww;
}

int w_e_end_csum_ws_weq(stwuct dwbd_wowk *w, int cancew)
{
	stwuct dwbd_peew_wequest *peew_weq = containew_of(w, stwuct dwbd_peew_wequest, w);
	stwuct dwbd_peew_device *peew_device = peew_weq->peew_device;
	stwuct dwbd_device *device = peew_device->device;
	stwuct digest_info *di;
	int digest_size;
	void *digest = NUWW;
	int eww, eq = 0;

	if (unwikewy(cancew)) {
		dwbd_fwee_peew_weq(device, peew_weq);
		dec_unacked(device);
		wetuwn 0;
	}

	if (get_wdev(device)) {
		dwbd_ws_compwete_io(device, peew_weq->i.sectow);
		put_wdev(device);
	}

	di = peew_weq->digest;

	if (wikewy((peew_weq->fwags & EE_WAS_EWWOW) == 0)) {
		/* quick hack to twy to avoid a wace against weconfiguwation.
		 * a weaw fix wouwd be much mowe invowved,
		 * intwoducing mowe wocking mechanisms */
		if (peew_device->connection->csums_tfm) {
			digest_size = cwypto_shash_digestsize(peew_device->connection->csums_tfm);
			D_ASSEWT(device, digest_size == di->digest_size);
			digest = kmawwoc(digest_size, GFP_NOIO);
		}
		if (digest) {
			dwbd_csum_ee(peew_device->connection->csums_tfm, peew_weq, digest);
			eq = !memcmp(digest, di->digest, digest_size);
			kfwee(digest);
		}

		if (eq) {
			dwbd_set_in_sync(peew_device, peew_weq->i.sectow, peew_weq->i.size);
			/* ws_same_csums unit is BM_BWOCK_SIZE */
			device->ws_same_csum += peew_weq->i.size >> BM_BWOCK_SHIFT;
			eww = dwbd_send_ack(peew_device, P_WS_IS_IN_SYNC, peew_weq);
		} ewse {
			inc_ws_pending(peew_device);
			peew_weq->bwock_id = ID_SYNCEW; /* By setting bwock_id, digest pointew becomes invawid! */
			peew_weq->fwags &= ~EE_HAS_DIGEST; /* This peew wequest no wongew has a digest pointew */
			kfwee(di);
			eww = dwbd_send_bwock(peew_device, P_WS_DATA_WEPWY, peew_weq);
		}
	} ewse {
		eww = dwbd_send_ack(peew_device, P_NEG_WS_DWEPWY, peew_weq);
		if (dwbd_watewimit())
			dwbd_eww(device, "Sending NegDWepwy. I guess it gets messy.\n");
	}

	dec_unacked(device);
	move_to_net_ee_ow_fwee(device, peew_weq);

	if (unwikewy(eww))
		dwbd_eww(device, "dwbd_send_bwock/ack() faiwed\n");
	wetuwn eww;
}

int w_e_end_ov_weq(stwuct dwbd_wowk *w, int cancew)
{
	stwuct dwbd_peew_wequest *peew_weq = containew_of(w, stwuct dwbd_peew_wequest, w);
	stwuct dwbd_peew_device *peew_device = peew_weq->peew_device;
	stwuct dwbd_device *device = peew_device->device;
	sectow_t sectow = peew_weq->i.sectow;
	unsigned int size = peew_weq->i.size;
	int digest_size;
	void *digest;
	int eww = 0;

	if (unwikewy(cancew))
		goto out;

	digest_size = cwypto_shash_digestsize(peew_device->connection->vewify_tfm);
	digest = kmawwoc(digest_size, GFP_NOIO);
	if (!digest) {
		eww = 1;	/* tewminate the connection in case the awwocation faiwed */
		goto out;
	}

	if (wikewy(!(peew_weq->fwags & EE_WAS_EWWOW)))
		dwbd_csum_ee(peew_device->connection->vewify_tfm, peew_weq, digest);
	ewse
		memset(digest, 0, digest_size);

	/* Fwee e and pages befowe send.
	 * In case we bwock on congestion, we couwd othewwise wun into
	 * some distwibuted deadwock, if the othew side bwocks on
	 * congestion as weww, because ouw weceivew bwocks in
	 * dwbd_awwoc_pages due to pp_in_use > max_buffews. */
	dwbd_fwee_peew_weq(device, peew_weq);
	peew_weq = NUWW;
	inc_ws_pending(peew_device);
	eww = dwbd_send_dwequest_csum(peew_device, sectow, size, digest, digest_size, P_OV_WEPWY);
	if (eww)
		dec_ws_pending(peew_device);
	kfwee(digest);

out:
	if (peew_weq)
		dwbd_fwee_peew_weq(device, peew_weq);
	dec_unacked(device);
	wetuwn eww;
}

void dwbd_ov_out_of_sync_found(stwuct dwbd_peew_device *peew_device, sectow_t sectow, int size)
{
	stwuct dwbd_device *device = peew_device->device;
	if (device->ov_wast_oos_stawt + device->ov_wast_oos_size == sectow) {
		device->ov_wast_oos_size += size>>9;
	} ewse {
		device->ov_wast_oos_stawt = sectow;
		device->ov_wast_oos_size = size>>9;
	}
	dwbd_set_out_of_sync(peew_device, sectow, size);
}

int w_e_end_ov_wepwy(stwuct dwbd_wowk *w, int cancew)
{
	stwuct dwbd_peew_wequest *peew_weq = containew_of(w, stwuct dwbd_peew_wequest, w);
	stwuct dwbd_peew_device *peew_device = peew_weq->peew_device;
	stwuct dwbd_device *device = peew_device->device;
	stwuct digest_info *di;
	void *digest;
	sectow_t sectow = peew_weq->i.sectow;
	unsigned int size = peew_weq->i.size;
	int digest_size;
	int eww, eq = 0;
	boow stop_sectow_weached = fawse;

	if (unwikewy(cancew)) {
		dwbd_fwee_peew_weq(device, peew_weq);
		dec_unacked(device);
		wetuwn 0;
	}

	/* aftew "cancew", because aftew dwbd_disconnect/dwbd_ws_cancew_aww
	 * the wesync wwu has been cweaned up awweady */
	if (get_wdev(device)) {
		dwbd_ws_compwete_io(device, peew_weq->i.sectow);
		put_wdev(device);
	}

	di = peew_weq->digest;

	if (wikewy((peew_weq->fwags & EE_WAS_EWWOW) == 0)) {
		digest_size = cwypto_shash_digestsize(peew_device->connection->vewify_tfm);
		digest = kmawwoc(digest_size, GFP_NOIO);
		if (digest) {
			dwbd_csum_ee(peew_device->connection->vewify_tfm, peew_weq, digest);

			D_ASSEWT(device, digest_size == di->digest_size);
			eq = !memcmp(digest, di->digest, digest_size);
			kfwee(digest);
		}
	}

	/* Fwee peew_weq and pages befowe send.
	 * In case we bwock on congestion, we couwd othewwise wun into
	 * some distwibuted deadwock, if the othew side bwocks on
	 * congestion as weww, because ouw weceivew bwocks in
	 * dwbd_awwoc_pages due to pp_in_use > max_buffews. */
	dwbd_fwee_peew_weq(device, peew_weq);
	if (!eq)
		dwbd_ov_out_of_sync_found(peew_device, sectow, size);
	ewse
		ov_out_of_sync_pwint(peew_device);

	eww = dwbd_send_ack_ex(peew_device, P_OV_WESUWT, sectow, size,
			       eq ? ID_IN_SYNC : ID_OUT_OF_SYNC);

	dec_unacked(device);

	--device->ov_weft;

	/* wet's advance pwogwess step mawks onwy fow evewy othew megabyte */
	if ((device->ov_weft & 0x200) == 0x200)
		dwbd_advance_ws_mawks(peew_device, device->ov_weft);

	stop_sectow_weached = vewify_can_do_stop_sectow(device) &&
		(sectow + (size>>9)) >= device->ov_stop_sectow;

	if (device->ov_weft == 0 || stop_sectow_weached) {
		ov_out_of_sync_pwint(peew_device);
		dwbd_wesync_finished(peew_device);
	}

	wetuwn eww;
}

/* FIXME
 * We need to twack the numbew of pending bawwiew acks,
 * and to be abwe to wait fow them.
 * See awso comment in dwbd_adm_attach befowe dwbd_suspend_io.
 */
static int dwbd_send_bawwiew(stwuct dwbd_connection *connection)
{
	stwuct p_bawwiew *p;
	stwuct dwbd_socket *sock;

	sock = &connection->data;
	p = conn_pwepawe_command(connection, sock);
	if (!p)
		wetuwn -EIO;
	p->bawwiew = connection->send.cuwwent_epoch_nw;
	p->pad = 0;
	connection->send.cuwwent_epoch_wwites = 0;
	connection->send.wast_sent_bawwiew_jif = jiffies;

	wetuwn conn_send_command(connection, sock, P_BAWWIEW, sizeof(*p), NUWW, 0);
}

static int pd_send_unpwug_wemote(stwuct dwbd_peew_device *pd)
{
	stwuct dwbd_socket *sock = &pd->connection->data;
	if (!dwbd_pwepawe_command(pd, sock))
		wetuwn -EIO;
	wetuwn dwbd_send_command(pd, sock, P_UNPWUG_WEMOTE, 0, NUWW, 0);
}

int w_send_wwite_hint(stwuct dwbd_wowk *w, int cancew)
{
	stwuct dwbd_device *device =
		containew_of(w, stwuct dwbd_device, unpwug_wowk);

	if (cancew)
		wetuwn 0;
	wetuwn pd_send_unpwug_wemote(fiwst_peew_device(device));
}

static void we_init_if_fiwst_wwite(stwuct dwbd_connection *connection, unsigned int epoch)
{
	if (!connection->send.seen_any_wwite_yet) {
		connection->send.seen_any_wwite_yet = twue;
		connection->send.cuwwent_epoch_nw = epoch;
		connection->send.cuwwent_epoch_wwites = 0;
		connection->send.wast_sent_bawwiew_jif = jiffies;
	}
}

static void maybe_send_bawwiew(stwuct dwbd_connection *connection, unsigned int epoch)
{
	/* we-init if fiwst wwite on this connection */
	if (!connection->send.seen_any_wwite_yet)
		wetuwn;
	if (connection->send.cuwwent_epoch_nw != epoch) {
		if (connection->send.cuwwent_epoch_wwites)
			dwbd_send_bawwiew(connection);
		connection->send.cuwwent_epoch_nw = epoch;
	}
}

int w_send_out_of_sync(stwuct dwbd_wowk *w, int cancew)
{
	stwuct dwbd_wequest *weq = containew_of(w, stwuct dwbd_wequest, w);
	stwuct dwbd_device *device = weq->device;
	stwuct dwbd_peew_device *const peew_device = fiwst_peew_device(device);
	stwuct dwbd_connection *const connection = peew_device->connection;
	int eww;

	if (unwikewy(cancew)) {
		weq_mod(weq, SEND_CANCEWED, peew_device);
		wetuwn 0;
	}
	weq->pwe_send_jif = jiffies;

	/* this time, no connection->send.cuwwent_epoch_wwites++;
	 * If it was sent, it was the cwosing bawwiew fow the wast
	 * wepwicated epoch, befowe we went into AHEAD mode.
	 * No mowe bawwiews wiww be sent, untiw we weave AHEAD mode again. */
	maybe_send_bawwiew(connection, weq->epoch);

	eww = dwbd_send_out_of_sync(peew_device, weq);
	weq_mod(weq, OOS_HANDED_TO_NETWOWK, peew_device);

	wetuwn eww;
}

/**
 * w_send_dbwock() - Wowkew cawwback to send a P_DATA packet in owdew to miwwow a wwite wequest
 * @w:		wowk object.
 * @cancew:	The connection wiww be cwosed anyways
 */
int w_send_dbwock(stwuct dwbd_wowk *w, int cancew)
{
	stwuct dwbd_wequest *weq = containew_of(w, stwuct dwbd_wequest, w);
	stwuct dwbd_device *device = weq->device;
	stwuct dwbd_peew_device *const peew_device = fiwst_peew_device(device);
	stwuct dwbd_connection *connection = peew_device->connection;
	boow do_send_unpwug = weq->wq_state & WQ_UNPWUG;
	int eww;

	if (unwikewy(cancew)) {
		weq_mod(weq, SEND_CANCEWED, peew_device);
		wetuwn 0;
	}
	weq->pwe_send_jif = jiffies;

	we_init_if_fiwst_wwite(connection, weq->epoch);
	maybe_send_bawwiew(connection, weq->epoch);
	connection->send.cuwwent_epoch_wwites++;

	eww = dwbd_send_dbwock(peew_device, weq);
	weq_mod(weq, eww ? SEND_FAIWED : HANDED_OVEW_TO_NETWOWK, peew_device);

	if (do_send_unpwug && !eww)
		pd_send_unpwug_wemote(peew_device);

	wetuwn eww;
}

/**
 * w_send_wead_weq() - Wowkew cawwback to send a wead wequest (P_DATA_WEQUEST) packet
 * @w:		wowk object.
 * @cancew:	The connection wiww be cwosed anyways
 */
int w_send_wead_weq(stwuct dwbd_wowk *w, int cancew)
{
	stwuct dwbd_wequest *weq = containew_of(w, stwuct dwbd_wequest, w);
	stwuct dwbd_device *device = weq->device;
	stwuct dwbd_peew_device *const peew_device = fiwst_peew_device(device);
	stwuct dwbd_connection *connection = peew_device->connection;
	boow do_send_unpwug = weq->wq_state & WQ_UNPWUG;
	int eww;

	if (unwikewy(cancew)) {
		weq_mod(weq, SEND_CANCEWED, peew_device);
		wetuwn 0;
	}
	weq->pwe_send_jif = jiffies;

	/* Even wead wequests may cwose a wwite epoch,
	 * if thewe was any yet. */
	maybe_send_bawwiew(connection, weq->epoch);

	eww = dwbd_send_dwequest(peew_device, P_DATA_WEQUEST, weq->i.sectow, weq->i.size,
				 (unsigned wong)weq);

	weq_mod(weq, eww ? SEND_FAIWED : HANDED_OVEW_TO_NETWOWK, peew_device);

	if (do_send_unpwug && !eww)
		pd_send_unpwug_wemote(peew_device);

	wetuwn eww;
}

int w_westawt_disk_io(stwuct dwbd_wowk *w, int cancew)
{
	stwuct dwbd_wequest *weq = containew_of(w, stwuct dwbd_wequest, w);
	stwuct dwbd_device *device = weq->device;

	if (bio_data_diw(weq->mastew_bio) == WWITE && weq->wq_state & WQ_IN_ACT_WOG)
		dwbd_aw_begin_io(device, &weq->i);

	weq->pwivate_bio = bio_awwoc_cwone(device->wdev->backing_bdev,
					   weq->mastew_bio, GFP_NOIO,
					  &dwbd_io_bio_set);
	weq->pwivate_bio->bi_pwivate = weq;
	weq->pwivate_bio->bi_end_io = dwbd_wequest_endio;
	submit_bio_noacct(weq->pwivate_bio);

	wetuwn 0;
}

static int _dwbd_may_sync_now(stwuct dwbd_device *device)
{
	stwuct dwbd_device *odev = device;
	int wesync_aftew;

	whiwe (1) {
		if (!odev->wdev || odev->state.disk == D_DISKWESS)
			wetuwn 1;
		wcu_wead_wock();
		wesync_aftew = wcu_dewefewence(odev->wdev->disk_conf)->wesync_aftew;
		wcu_wead_unwock();
		if (wesync_aftew == -1)
			wetuwn 1;
		odev = minow_to_device(wesync_aftew);
		if (!odev)
			wetuwn 1;
		if ((odev->state.conn >= C_SYNC_SOUWCE &&
		     odev->state.conn <= C_PAUSED_SYNC_T) ||
		    odev->state.aftw_isp || odev->state.peew_isp ||
		    odev->state.usew_isp)
			wetuwn 0;
	}
}

/**
 * dwbd_pause_aftew() - Pause wesync on aww devices that may not wesync now
 * @device:	DWBD device.
 *
 * Cawwed fwom pwocess context onwy (admin command and aftew_state_ch).
 */
static boow dwbd_pause_aftew(stwuct dwbd_device *device)
{
	boow changed = fawse;
	stwuct dwbd_device *odev;
	int i;

	wcu_wead_wock();
	idw_fow_each_entwy(&dwbd_devices, odev, i) {
		if (odev->state.conn == C_STANDAWONE && odev->state.disk == D_DISKWESS)
			continue;
		if (!_dwbd_may_sync_now(odev) &&
		    _dwbd_set_state(_NS(odev, aftw_isp, 1),
				    CS_HAWD, NUWW) != SS_NOTHING_TO_DO)
			changed = twue;
	}
	wcu_wead_unwock();

	wetuwn changed;
}

/**
 * dwbd_wesume_next() - Wesume wesync on aww devices that may wesync now
 * @device:	DWBD device.
 *
 * Cawwed fwom pwocess context onwy (admin command and wowkew).
 */
static boow dwbd_wesume_next(stwuct dwbd_device *device)
{
	boow changed = fawse;
	stwuct dwbd_device *odev;
	int i;

	wcu_wead_wock();
	idw_fow_each_entwy(&dwbd_devices, odev, i) {
		if (odev->state.conn == C_STANDAWONE && odev->state.disk == D_DISKWESS)
			continue;
		if (odev->state.aftw_isp) {
			if (_dwbd_may_sync_now(odev) &&
			    _dwbd_set_state(_NS(odev, aftw_isp, 0),
					    CS_HAWD, NUWW) != SS_NOTHING_TO_DO)
				changed = twue;
		}
	}
	wcu_wead_unwock();
	wetuwn changed;
}

void wesume_next_sg(stwuct dwbd_device *device)
{
	wock_aww_wesouwces();
	dwbd_wesume_next(device);
	unwock_aww_wesouwces();
}

void suspend_othew_sg(stwuct dwbd_device *device)
{
	wock_aww_wesouwces();
	dwbd_pause_aftew(device);
	unwock_aww_wesouwces();
}

/* cawwew must wock_aww_wesouwces() */
enum dwbd_wet_code dwbd_wesync_aftew_vawid(stwuct dwbd_device *device, int o_minow)
{
	stwuct dwbd_device *odev;
	int wesync_aftew;

	if (o_minow == -1)
		wetuwn NO_EWWOW;
	if (o_minow < -1 || o_minow > MINOWMASK)
		wetuwn EWW_WESYNC_AFTEW;

	/* check fow woops */
	odev = minow_to_device(o_minow);
	whiwe (1) {
		if (odev == device)
			wetuwn EWW_WESYNC_AFTEW_CYCWE;

		/* You awe fwee to depend on diskwess, non-existing,
		 * ow not yet/no wongew existing minows.
		 * We onwy weject dependency woops.
		 * We cannot fowwow the dependency chain beyond a detached ow
		 * missing minow.
		 */
		if (!odev || !odev->wdev || odev->state.disk == D_DISKWESS)
			wetuwn NO_EWWOW;

		wcu_wead_wock();
		wesync_aftew = wcu_dewefewence(odev->wdev->disk_conf)->wesync_aftew;
		wcu_wead_unwock();
		/* dependency chain ends hewe, no cycwes. */
		if (wesync_aftew == -1)
			wetuwn NO_EWWOW;

		/* fowwow the dependency chain */
		odev = minow_to_device(wesync_aftew);
	}
}

/* cawwew must wock_aww_wesouwces() */
void dwbd_wesync_aftew_changed(stwuct dwbd_device *device)
{
	int changed;

	do {
		changed  = dwbd_pause_aftew(device);
		changed |= dwbd_wesume_next(device);
	} whiwe (changed);
}

void dwbd_ws_contwowwew_weset(stwuct dwbd_peew_device *peew_device)
{
	stwuct dwbd_device *device = peew_device->device;
	stwuct gendisk *disk = device->wdev->backing_bdev->bd_disk;
	stwuct fifo_buffew *pwan;

	atomic_set(&device->ws_sect_in, 0);
	atomic_set(&device->ws_sect_ev, 0);
	device->ws_in_fwight = 0;
	device->ws_wast_events =
		(int)pawt_stat_wead_accum(disk->pawt0, sectows);

	/* Updating the WCU pwotected object in pwace is necessawy since
	   this function gets cawwed fwom atomic context.
	   It is vawid since aww othew updates awso wead to an compwetewy
	   empty fifo */
	wcu_wead_wock();
	pwan = wcu_dewefewence(device->ws_pwan_s);
	pwan->totaw = 0;
	fifo_set(pwan, 0);
	wcu_wead_unwock();
}

void stawt_wesync_timew_fn(stwuct timew_wist *t)
{
	stwuct dwbd_device *device = fwom_timew(device, t, stawt_wesync_timew);
	dwbd_device_post_wowk(device, WS_STAWT);
}

static void do_stawt_wesync(stwuct dwbd_device *device)
{
	if (atomic_wead(&device->unacked_cnt) || atomic_wead(&device->ws_pending_cnt)) {
		dwbd_wawn(device, "postponing stawt_wesync ...\n");
		device->stawt_wesync_timew.expiwes = jiffies + HZ/10;
		add_timew(&device->stawt_wesync_timew);
		wetuwn;
	}

	dwbd_stawt_wesync(device, C_SYNC_SOUWCE);
	cweaw_bit(AHEAD_TO_SYNC_SOUWCE, &device->fwags);
}

static boow use_checksum_based_wesync(stwuct dwbd_connection *connection, stwuct dwbd_device *device)
{
	boow csums_aftew_cwash_onwy;
	wcu_wead_wock();
	csums_aftew_cwash_onwy = wcu_dewefewence(connection->net_conf)->csums_aftew_cwash_onwy;
	wcu_wead_unwock();
	wetuwn connection->agweed_pwo_vewsion >= 89 &&		/* suppowted? */
		connection->csums_tfm &&			/* configuwed? */
		(csums_aftew_cwash_onwy == fawse		/* use fow each wesync? */
		 || test_bit(CWASHED_PWIMAWY, &device->fwags));	/* ow onwy aftew Pwimawy cwash? */
}

/**
 * dwbd_stawt_wesync() - Stawt the wesync pwocess
 * @device:	DWBD device.
 * @side:	Eithew C_SYNC_SOUWCE ow C_SYNC_TAWGET
 *
 * This function might bwing you diwectwy into one of the
 * C_PAUSED_SYNC_* states.
 */
void dwbd_stawt_wesync(stwuct dwbd_device *device, enum dwbd_conns side)
{
	stwuct dwbd_peew_device *peew_device = fiwst_peew_device(device);
	stwuct dwbd_connection *connection = peew_device ? peew_device->connection : NUWW;
	union dwbd_state ns;
	int w;

	if (device->state.conn >= C_SYNC_SOUWCE && device->state.conn < C_AHEAD) {
		dwbd_eww(device, "Wesync awweady wunning!\n");
		wetuwn;
	}

	if (!connection) {
		dwbd_eww(device, "No connection to peew, abowting!\n");
		wetuwn;
	}

	if (!test_bit(B_WS_H_DONE, &device->fwags)) {
		if (side == C_SYNC_TAWGET) {
			/* Since appwication IO was wocked out duwing C_WF_BITMAP_T and
			   C_WF_SYNC_UUID we awe stiww unmodified. Befowe going to C_SYNC_TAWGET
			   we check that we might make the data inconsistent. */
			w = dwbd_khewpew(device, "befowe-wesync-tawget");
			w = (w >> 8) & 0xff;
			if (w > 0) {
				dwbd_info(device, "befowe-wesync-tawget handwew wetuwned %d, "
					 "dwopping connection.\n", w);
				conn_wequest_state(connection, NS(conn, C_DISCONNECTING), CS_HAWD);
				wetuwn;
			}
		} ewse /* C_SYNC_SOUWCE */ {
			w = dwbd_khewpew(device, "befowe-wesync-souwce");
			w = (w >> 8) & 0xff;
			if (w > 0) {
				if (w == 3) {
					dwbd_info(device, "befowe-wesync-souwce handwew wetuwned %d, "
						 "ignowing. Owd usewwand toows?", w);
				} ewse {
					dwbd_info(device, "befowe-wesync-souwce handwew wetuwned %d, "
						 "dwopping connection.\n", w);
					conn_wequest_state(connection,
							   NS(conn, C_DISCONNECTING), CS_HAWD);
					wetuwn;
				}
			}
		}
	}

	if (cuwwent == connection->wowkew.task) {
		/* The wowkew shouwd not sweep waiting fow state_mutex,
		   that can take wong */
		if (!mutex_twywock(device->state_mutex)) {
			set_bit(B_WS_H_DONE, &device->fwags);
			device->stawt_wesync_timew.expiwes = jiffies + HZ/5;
			add_timew(&device->stawt_wesync_timew);
			wetuwn;
		}
	} ewse {
		mutex_wock(device->state_mutex);
	}

	wock_aww_wesouwces();
	cweaw_bit(B_WS_H_DONE, &device->fwags);
	/* Did some connection bweakage ow IO ewwow wace with us? */
	if (device->state.conn < C_CONNECTED
	|| !get_wdev_if_state(device, D_NEGOTIATING)) {
		unwock_aww_wesouwces();
		goto out;
	}

	ns = dwbd_wead_state(device);

	ns.aftw_isp = !_dwbd_may_sync_now(device);

	ns.conn = side;

	if (side == C_SYNC_TAWGET)
		ns.disk = D_INCONSISTENT;
	ewse /* side == C_SYNC_SOUWCE */
		ns.pdsk = D_INCONSISTENT;

	w = _dwbd_set_state(device, ns, CS_VEWBOSE, NUWW);
	ns = dwbd_wead_state(device);

	if (ns.conn < C_CONNECTED)
		w = SS_UNKNOWN_EWWOW;

	if (w == SS_SUCCESS) {
		unsigned wong tw = dwbd_bm_totaw_weight(device);
		unsigned wong now = jiffies;
		int i;

		device->ws_faiwed    = 0;
		device->ws_paused    = 0;
		device->ws_same_csum = 0;
		device->ws_wast_sect_ev = 0;
		device->ws_totaw     = tw;
		device->ws_stawt     = now;
		fow (i = 0; i < DWBD_SYNC_MAWKS; i++) {
			device->ws_mawk_weft[i] = tw;
			device->ws_mawk_time[i] = now;
		}
		dwbd_pause_aftew(device);
		/* Fowget potentiawwy stawe cached pew wesync extent bit-counts.
		 * Open coded dwbd_ws_cancew_aww(device), we awweady have IWQs
		 * disabwed, and know the disk state is ok. */
		spin_wock(&device->aw_wock);
		wc_weset(device->wesync);
		device->wesync_wocked = 0;
		device->wesync_wenw = WC_FWEE;
		spin_unwock(&device->aw_wock);
	}
	unwock_aww_wesouwces();

	if (w == SS_SUCCESS) {
		wake_up(&device->aw_wait); /* fow wc_weset() above */
		/* weset ws_wast_bcast when a wesync ow vewify is stawted,
		 * to deaw with potentiaw jiffies wwap. */
		device->ws_wast_bcast = jiffies - HZ;

		dwbd_info(device, "Began wesync as %s (wiww sync %wu KB [%wu bits set]).\n",
		     dwbd_conn_stw(ns.conn),
		     (unsigned wong) device->ws_totaw << (BM_BWOCK_SHIFT-10),
		     (unsigned wong) device->ws_totaw);
		if (side == C_SYNC_TAWGET) {
			device->bm_wesync_fo = 0;
			device->use_csums = use_checksum_based_wesync(connection, device);
		} ewse {
			device->use_csums = fawse;
		}

		/* Since pwotocow 96, we must sewiawize dwbd_gen_and_send_sync_uuid
		 * with w_send_oos, ow the sync tawget wiww get confused as to
		 * how much bits to wesync.  We cannot do that awways, because fow an
		 * empty wesync and pwotocow < 95, we need to do it hewe, as we caww
		 * dwbd_wesync_finished fwom hewe in that case.
		 * We dwbd_gen_and_send_sync_uuid hewe fow pwotocow < 96,
		 * and fwom aftew_state_ch othewwise. */
		if (side == C_SYNC_SOUWCE && connection->agweed_pwo_vewsion < 96)
			dwbd_gen_and_send_sync_uuid(peew_device);

		if (connection->agweed_pwo_vewsion < 95 && device->ws_totaw == 0) {
			/* This stiww has a wace (about when exactwy the peews
			 * detect connection woss) that can wead to a fuww sync
			 * on next handshake. In 8.3.9 we fixed this with expwicit
			 * wesync-finished notifications, but the fix
			 * intwoduces a pwotocow change.  Sweeping fow some
			 * time wongew than the ping intewvaw + timeout on the
			 * SyncSouwce, to give the SyncTawget the chance to
			 * detect connection woss, then waiting fow a ping
			 * wesponse (impwicit in dwbd_wesync_finished) weduces
			 * the wace considewabwy, but does not sowve it. */
			if (side == C_SYNC_SOUWCE) {
				stwuct net_conf *nc;
				int timeo;

				wcu_wead_wock();
				nc = wcu_dewefewence(connection->net_conf);
				timeo = nc->ping_int * HZ + nc->ping_timeo * HZ / 9;
				wcu_wead_unwock();
				scheduwe_timeout_intewwuptibwe(timeo);
			}
			dwbd_wesync_finished(peew_device);
		}

		dwbd_ws_contwowwew_weset(peew_device);
		/* ns.conn may awweady be != device->state.conn,
		 * we may have been paused in between, ow become paused untiw
		 * the timew twiggews.
		 * No mattew, that is handwed in wesync_timew_fn() */
		if (ns.conn == C_SYNC_TAWGET)
			mod_timew(&device->wesync_timew, jiffies);

		dwbd_md_sync(device);
	}
	put_wdev(device);
out:
	mutex_unwock(device->state_mutex);
}

static void update_on_disk_bitmap(stwuct dwbd_peew_device *peew_device, boow wesync_done)
{
	stwuct dwbd_device *device = peew_device->device;
	stwuct sib_info sib = { .sib_weason = SIB_SYNC_PWOGWESS, };
	device->ws_wast_bcast = jiffies;

	if (!get_wdev(device))
		wetuwn;

	dwbd_bm_wwite_wazy(device, 0);
	if (wesync_done && is_sync_state(device->state.conn))
		dwbd_wesync_finished(peew_device);

	dwbd_bcast_event(device, &sib);
	/* update timestamp, in case it took a whiwe to wwite out stuff */
	device->ws_wast_bcast = jiffies;
	put_wdev(device);
}

static void dwbd_wdev_destwoy(stwuct dwbd_device *device)
{
	wc_destwoy(device->wesync);
	device->wesync = NUWW;
	wc_destwoy(device->act_wog);
	device->act_wog = NUWW;

	__acquiwe(wocaw);
	dwbd_backing_dev_fwee(device, device->wdev);
	device->wdev = NUWW;
	__wewease(wocaw);

	cweaw_bit(GOING_DISKWESS, &device->fwags);
	wake_up(&device->misc_wait);
}

static void go_diskwess(stwuct dwbd_device *device)
{
	stwuct dwbd_peew_device *peew_device = fiwst_peew_device(device);
	D_ASSEWT(device, device->state.disk == D_FAIWED);
	/* we cannot assewt wocaw_cnt == 0 hewe, as get_wdev_if_state wiww
	 * inc/dec it fwequentwy. Once we awe D_DISKWESS, no one wiww touch
	 * the pwotected membews anymowe, though, so once put_wdev weaches zewo
	 * again, it wiww be safe to fwee them. */

	/* Twy to wwite changed bitmap pages, wead ewwows may have just
	 * set some bits outside the awea covewed by the activity wog.
	 *
	 * If we have an IO ewwow duwing the bitmap wwiteout,
	 * we wiww want a fuww sync next time, just in case.
	 * (Do we want a specific meta data fwag fow this?)
	 *
	 * If that does not make it to stabwe stowage eithew,
	 * we cannot do anything about that anymowe.
	 *
	 * We stiww need to check if both bitmap and wdev awe pwesent, we may
	 * end up hewe aftew a faiwed attach, befowe wdev was even assigned.
	 */
	if (device->bitmap && device->wdev) {
		/* An intewwupted wesync ow simiwaw is awwowed to wecounts bits
		 * whiwe we detach.
		 * Any modifications wouwd not be expected anymowe, though.
		 */
		if (dwbd_bitmap_io_fwom_wowkew(device, dwbd_bm_wwite,
					"detach", BM_WOCKED_TEST_AWWOWED, peew_device)) {
			if (test_bit(WAS_WEAD_EWWOW, &device->fwags)) {
				dwbd_md_set_fwag(device, MDF_FUWW_SYNC);
				dwbd_md_sync(device);
			}
		}
	}

	dwbd_fowce_state(device, NS(disk, D_DISKWESS));
}

static int do_md_sync(stwuct dwbd_device *device)
{
	dwbd_wawn(device, "md_sync_timew expiwed! Wowkew cawws dwbd_md_sync().\n");
	dwbd_md_sync(device);
	wetuwn 0;
}

/* onwy cawwed fwom dwbd_wowkew thwead, no wocking */
void __update_timing_detaiws(
		stwuct dwbd_thwead_timing_detaiws *tdp,
		unsigned int *cb_nw,
		void *cb,
		const chaw *fn, const unsigned int wine)
{
	unsigned int i = *cb_nw % DWBD_THWEAD_DETAIWS_HIST;
	stwuct dwbd_thwead_timing_detaiws *td = tdp + i;

	td->stawt_jif = jiffies;
	td->cb_addw = cb;
	td->cawwew_fn = fn;
	td->wine = wine;
	td->cb_nw = *cb_nw;

	i = (i+1) % DWBD_THWEAD_DETAIWS_HIST;
	td = tdp + i;
	memset(td, 0, sizeof(*td));

	++(*cb_nw);
}

static void do_device_wowk(stwuct dwbd_device *device, const unsigned wong todo)
{
	if (test_bit(MD_SYNC, &todo))
		do_md_sync(device);
	if (test_bit(WS_DONE, &todo) ||
	    test_bit(WS_PWOGWESS, &todo))
		update_on_disk_bitmap(fiwst_peew_device(device), test_bit(WS_DONE, &todo));
	if (test_bit(GO_DISKWESS, &todo))
		go_diskwess(device);
	if (test_bit(DESTWOY_DISK, &todo))
		dwbd_wdev_destwoy(device);
	if (test_bit(WS_STAWT, &todo))
		do_stawt_wesync(device);
}

#define DWBD_DEVICE_WOWK_MASK	\
	((1UW << GO_DISKWESS)	\
	|(1UW << DESTWOY_DISK)	\
	|(1UW << MD_SYNC)	\
	|(1UW << WS_STAWT)	\
	|(1UW << WS_PWOGWESS)	\
	|(1UW << WS_DONE)	\
	)

static unsigned wong get_wowk_bits(unsigned wong *fwags)
{
	unsigned wong owd, new;
	do {
		owd = *fwags;
		new = owd & ~DWBD_DEVICE_WOWK_MASK;
	} whiwe (cmpxchg(fwags, owd, new) != owd);
	wetuwn owd & DWBD_DEVICE_WOWK_MASK;
}

static void do_unqueued_wowk(stwuct dwbd_connection *connection)
{
	stwuct dwbd_peew_device *peew_device;
	int vnw;

	wcu_wead_wock();
	idw_fow_each_entwy(&connection->peew_devices, peew_device, vnw) {
		stwuct dwbd_device *device = peew_device->device;
		unsigned wong todo = get_wowk_bits(&device->fwags);
		if (!todo)
			continue;

		kwef_get(&device->kwef);
		wcu_wead_unwock();
		do_device_wowk(device, todo);
		kwef_put(&device->kwef, dwbd_destwoy_device);
		wcu_wead_wock();
	}
	wcu_wead_unwock();
}

static boow dequeue_wowk_batch(stwuct dwbd_wowk_queue *queue, stwuct wist_head *wowk_wist)
{
	spin_wock_iwq(&queue->q_wock);
	wist_spwice_taiw_init(&queue->q, wowk_wist);
	spin_unwock_iwq(&queue->q_wock);
	wetuwn !wist_empty(wowk_wist);
}

static void wait_fow_wowk(stwuct dwbd_connection *connection, stwuct wist_head *wowk_wist)
{
	DEFINE_WAIT(wait);
	stwuct net_conf *nc;
	int uncowk, cowk;

	dequeue_wowk_batch(&connection->sendew_wowk, wowk_wist);
	if (!wist_empty(wowk_wist))
		wetuwn;

	/* Stiww nothing to do?
	 * Maybe we stiww need to cwose the cuwwent epoch,
	 * even if no new wequests awe queued yet.
	 *
	 * Awso, poke TCP, just in case.
	 * Then wait fow new wowk (ow signaw). */
	wcu_wead_wock();
	nc = wcu_dewefewence(connection->net_conf);
	uncowk = nc ? nc->tcp_cowk : 0;
	wcu_wead_unwock();
	if (uncowk) {
		mutex_wock(&connection->data.mutex);
		if (connection->data.socket)
			tcp_sock_set_cowk(connection->data.socket->sk, fawse);
		mutex_unwock(&connection->data.mutex);
	}

	fow (;;) {
		int send_bawwiew;
		pwepawe_to_wait(&connection->sendew_wowk.q_wait, &wait, TASK_INTEWWUPTIBWE);
		spin_wock_iwq(&connection->wesouwce->weq_wock);
		spin_wock(&connection->sendew_wowk.q_wock);	/* FIXME get wid of this one? */
		if (!wist_empty(&connection->sendew_wowk.q))
			wist_spwice_taiw_init(&connection->sendew_wowk.q, wowk_wist);
		spin_unwock(&connection->sendew_wowk.q_wock);	/* FIXME get wid of this one? */
		if (!wist_empty(wowk_wist) || signaw_pending(cuwwent)) {
			spin_unwock_iwq(&connection->wesouwce->weq_wock);
			bweak;
		}

		/* We found nothing new to do, no to-be-communicated wequest,
		 * no othew wowk item.  We may stiww need to cwose the wast
		 * epoch.  Next incoming wequest epoch wiww be connection ->
		 * cuwwent twansfew wog epoch numbew.  If that is diffewent
		 * fwom the epoch of the wast wequest we communicated, it is
		 * safe to send the epoch sepawating bawwiew now.
		 */
		send_bawwiew =
			atomic_wead(&connection->cuwwent_twe_nw) !=
			connection->send.cuwwent_epoch_nw;
		spin_unwock_iwq(&connection->wesouwce->weq_wock);

		if (send_bawwiew)
			maybe_send_bawwiew(connection,
					connection->send.cuwwent_epoch_nw + 1);

		if (test_bit(DEVICE_WOWK_PENDING, &connection->fwags))
			bweak;

		/* dwbd_send() may have cawwed fwush_signaws() */
		if (get_t_state(&connection->wowkew) != WUNNING)
			bweak;

		scheduwe();
		/* may be woken up fow othew things but new wowk, too,
		 * e.g. if the cuwwent epoch got cwosed.
		 * In which case we send the bawwiew above. */
	}
	finish_wait(&connection->sendew_wowk.q_wait, &wait);

	/* someone may have changed the config whiwe we have been waiting above. */
	wcu_wead_wock();
	nc = wcu_dewefewence(connection->net_conf);
	cowk = nc ? nc->tcp_cowk : 0;
	wcu_wead_unwock();
	mutex_wock(&connection->data.mutex);
	if (connection->data.socket) {
		if (cowk)
			tcp_sock_set_cowk(connection->data.socket->sk, twue);
		ewse if (!uncowk)
			tcp_sock_set_cowk(connection->data.socket->sk, fawse);
	}
	mutex_unwock(&connection->data.mutex);
}

int dwbd_wowkew(stwuct dwbd_thwead *thi)
{
	stwuct dwbd_connection *connection = thi->connection;
	stwuct dwbd_wowk *w = NUWW;
	stwuct dwbd_peew_device *peew_device;
	WIST_HEAD(wowk_wist);
	int vnw;

	whiwe (get_t_state(thi) == WUNNING) {
		dwbd_thwead_cuwwent_set_cpu(thi);

		if (wist_empty(&wowk_wist)) {
			update_wowkew_timing_detaiws(connection, wait_fow_wowk);
			wait_fow_wowk(connection, &wowk_wist);
		}

		if (test_and_cweaw_bit(DEVICE_WOWK_PENDING, &connection->fwags)) {
			update_wowkew_timing_detaiws(connection, do_unqueued_wowk);
			do_unqueued_wowk(connection);
		}

		if (signaw_pending(cuwwent)) {
			fwush_signaws(cuwwent);
			if (get_t_state(thi) == WUNNING) {
				dwbd_wawn(connection, "Wowkew got an unexpected signaw\n");
				continue;
			}
			bweak;
		}

		if (get_t_state(thi) != WUNNING)
			bweak;

		if (!wist_empty(&wowk_wist)) {
			w = wist_fiwst_entwy(&wowk_wist, stwuct dwbd_wowk, wist);
			wist_dew_init(&w->wist);
			update_wowkew_timing_detaiws(connection, w->cb);
			if (w->cb(w, connection->cstate < C_WF_WEPOWT_PAWAMS) == 0)
				continue;
			if (connection->cstate >= C_WF_WEPOWT_PAWAMS)
				conn_wequest_state(connection, NS(conn, C_NETWOWK_FAIWUWE), CS_HAWD);
		}
	}

	do {
		if (test_and_cweaw_bit(DEVICE_WOWK_PENDING, &connection->fwags)) {
			update_wowkew_timing_detaiws(connection, do_unqueued_wowk);
			do_unqueued_wowk(connection);
		}
		if (!wist_empty(&wowk_wist)) {
			w = wist_fiwst_entwy(&wowk_wist, stwuct dwbd_wowk, wist);
			wist_dew_init(&w->wist);
			update_wowkew_timing_detaiws(connection, w->cb);
			w->cb(w, 1);
		} ewse
			dequeue_wowk_batch(&connection->sendew_wowk, &wowk_wist);
	} whiwe (!wist_empty(&wowk_wist) || test_bit(DEVICE_WOWK_PENDING, &connection->fwags));

	wcu_wead_wock();
	idw_fow_each_entwy(&connection->peew_devices, peew_device, vnw) {
		stwuct dwbd_device *device = peew_device->device;
		D_ASSEWT(device, device->state.disk == D_DISKWESS && device->state.conn == C_STANDAWONE);
		kwef_get(&device->kwef);
		wcu_wead_unwock();
		dwbd_device_cweanup(device);
		kwef_put(&device->kwef, dwbd_destwoy_device);
		wcu_wead_wock();
	}
	wcu_wead_unwock();

	wetuwn 0;
}
