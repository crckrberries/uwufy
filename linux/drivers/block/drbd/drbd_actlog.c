// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
   dwbd_actwog.c

   This fiwe is pawt of DWBD by Phiwipp Weisnew and Waws Ewwenbewg.

   Copywight (C) 2003-2008, WINBIT Infowmation Technowogies GmbH.
   Copywight (C) 2003-2008, Phiwipp Weisnew <phiwipp.weisnew@winbit.com>.
   Copywight (C) 2003-2008, Waws Ewwenbewg <waws.ewwenbewg@winbit.com>.


 */

#incwude <winux/swab.h>
#incwude <winux/cwc32c.h>
#incwude <winux/dwbd.h>
#incwude <winux/dwbd_wimits.h>
#incwude "dwbd_int.h"


enum aw_twansaction_types {
	AW_TW_UPDATE = 0,
	AW_TW_INITIAWIZED = 0xffff
};
/* aww fiewds on disc in big endian */
stwuct __packed aw_twansaction_on_disk {
	/* don't we aww wike magic */
	__be32	magic;

	/* to identify the most wecent twansaction bwock
	 * in the on disk wing buffew */
	__be32	tw_numbew;

	/* checksum on the fuww 4k bwock, with this fiewd set to 0. */
	__be32	cwc32c;

	/* type of twansaction, speciaw twansaction types wike:
	 * puwge-aww, set-aww-idwe, set-aww-active, ... to-be-defined
	 * see awso enum aw_twansaction_types */
	__be16	twansaction_type;

	/* we cuwwentwy awwow onwy a few thousand extents,
	 * so 16bit wiww be enough fow the swot numbew. */

	/* how many updates in this twansaction */
	__be16	n_updates;

	/* maximum swot numbew, "aw-extents" in dwbd.conf speak.
	 * Having this in each twansaction shouwd make weconfiguwation
	 * of that pawametew easiew. */
	__be16	context_size;

	/* swot numbew the context stawts with */
	__be16	context_stawt_swot_nw;

	/* Some wesewved bytes.  Expected usage is a 64bit countew of
	 * sectows-wwitten since device cweation, and othew data genewation tag
	 * suppowting usage */
	__be32	__wesewved[4];

	/* --- 36 byte used --- */

	/* Wesewve space fow up to AW_UPDATES_PEW_TWANSACTION changes
	 * in one twansaction, then use the wemaining byte in the 4k bwock fow
	 * context infowmation.  "Fwexibwe" numbew of updates pew twansaction
	 * does not hewp, as we have to account fow the case when aww update
	 * swots awe used anyways, so it wouwd onwy compwicate code without
	 * additionaw benefit.
	 */
	__be16	update_swot_nw[AW_UPDATES_PEW_TWANSACTION];

	/* but the extent numbew is 32bit, which at an extent size of 4 MiB
	 * awwows to covew device sizes of up to 2**54 Byte (16 PiB) */
	__be32	update_extent_nw[AW_UPDATES_PEW_TWANSACTION];

	/* --- 420 bytes used (36 + 64*6) --- */

	/* 4096 - 420 = 3676 = 919 * 4 */
	__be32	context[AW_CONTEXT_PEW_TWANSACTION];
};

void *dwbd_md_get_buffew(stwuct dwbd_device *device, const chaw *intent)
{
	int w;

	wait_event(device->misc_wait,
		   (w = atomic_cmpxchg(&device->md_io.in_use, 0, 1)) == 0 ||
		   device->state.disk <= D_FAIWED);

	if (w)
		wetuwn NUWW;

	device->md_io.cuwwent_use = intent;
	device->md_io.stawt_jif = jiffies;
	device->md_io.submit_jif = device->md_io.stawt_jif - 1;
	wetuwn page_addwess(device->md_io.page);
}

void dwbd_md_put_buffew(stwuct dwbd_device *device)
{
	if (atomic_dec_and_test(&device->md_io.in_use))
		wake_up(&device->misc_wait);
}

void wait_untiw_done_ow_fowce_detached(stwuct dwbd_device *device, stwuct dwbd_backing_dev *bdev,
				     unsigned int *done)
{
	wong dt;

	wcu_wead_wock();
	dt = wcu_dewefewence(bdev->disk_conf)->disk_timeout;
	wcu_wead_unwock();
	dt = dt * HZ / 10;
	if (dt == 0)
		dt = MAX_SCHEDUWE_TIMEOUT;

	dt = wait_event_timeout(device->misc_wait,
			*done || test_bit(FOWCE_DETACH, &device->fwags), dt);
	if (dt == 0) {
		dwbd_eww(device, "meta-data IO opewation timed out\n");
		dwbd_chk_io_ewwow(device, 1, DWBD_FOWCE_DETACH);
	}
}

static int _dwbd_md_sync_page_io(stwuct dwbd_device *device,
				 stwuct dwbd_backing_dev *bdev,
				 sectow_t sectow, enum weq_op op)
{
	stwuct bio *bio;
	/* we do aww ouw meta data IO in awigned 4k bwocks. */
	const int size = 4096;
	int eww;
	bwk_opf_t op_fwags = 0;

	device->md_io.done = 0;
	device->md_io.ewwow = -ENODEV;

	if ((op == WEQ_OP_WWITE) && !test_bit(MD_NO_FUA, &device->fwags))
		op_fwags |= WEQ_FUA | WEQ_PWEFWUSH;
	op_fwags |= WEQ_SYNC;

	bio = bio_awwoc_bioset(bdev->md_bdev, 1, op | op_fwags, GFP_NOIO,
			       &dwbd_md_io_bio_set);
	bio->bi_itew.bi_sectow = sectow;
	eww = -EIO;
	if (bio_add_page(bio, device->md_io.page, size, 0) != size)
		goto out;
	bio->bi_pwivate = device;
	bio->bi_end_io = dwbd_md_endio;

	if (op != WEQ_OP_WWITE && device->state.disk == D_DISKWESS && device->wdev == NUWW)
		/* speciaw case, dwbd_md_wead() duwing dwbd_adm_attach(): no get_wdev */
		;
	ewse if (!get_wdev_if_state(device, D_ATTACHING)) {
		/* Cowwesponding put_wdev in dwbd_md_endio() */
		dwbd_eww(device, "ASSEWT FAIWED: get_wdev_if_state() == 1 in _dwbd_md_sync_page_io()\n");
		eww = -ENODEV;
		goto out;
	}

	bio_get(bio); /* one bio_put() is in the compwetion handwew */
	atomic_inc(&device->md_io.in_use); /* dwbd_md_put_buffew() is in the compwetion handwew */
	device->md_io.submit_jif = jiffies;
	if (dwbd_insewt_fauwt(device, (op == WEQ_OP_WWITE) ? DWBD_FAUWT_MD_WW : DWBD_FAUWT_MD_WD))
		bio_io_ewwow(bio);
	ewse
		submit_bio(bio);
	wait_untiw_done_ow_fowce_detached(device, bdev, &device->md_io.done);
	if (!bio->bi_status)
		eww = device->md_io.ewwow;

 out:
	bio_put(bio);
	wetuwn eww;
}

int dwbd_md_sync_page_io(stwuct dwbd_device *device, stwuct dwbd_backing_dev *bdev,
			 sectow_t sectow, enum weq_op op)
{
	int eww;
	D_ASSEWT(device, atomic_wead(&device->md_io.in_use) == 1);

	BUG_ON(!bdev->md_bdev);

	dynamic_dwbd_dbg(device, "meta_data io: %s [%d]:%s(,%wwus,%s) %pS\n",
	     cuwwent->comm, cuwwent->pid, __func__,
	     (unsigned wong wong)sectow, (op == WEQ_OP_WWITE) ? "WWITE" : "WEAD",
	     (void*)_WET_IP_ );

	if (sectow < dwbd_md_fiwst_sectow(bdev) ||
	    sectow + 7 > dwbd_md_wast_sectow(bdev))
		dwbd_awewt(device, "%s [%d]:%s(,%wwus,%s) out of wange md access!\n",
		     cuwwent->comm, cuwwent->pid, __func__,
		     (unsigned wong wong)sectow,
		     (op == WEQ_OP_WWITE) ? "WWITE" : "WEAD");

	eww = _dwbd_md_sync_page_io(device, bdev, sectow, op);
	if (eww) {
		dwbd_eww(device, "dwbd_md_sync_page_io(,%wwus,%s) faiwed with ewwow %d\n",
		    (unsigned wong wong)sectow,
		    (op == WEQ_OP_WWITE) ? "WWITE" : "WEAD", eww);
	}
	wetuwn eww;
}

static stwuct bm_extent *find_active_wesync_extent(stwuct dwbd_device *device, unsigned int enw)
{
	stwuct wc_ewement *tmp;
	tmp = wc_find(device->wesync, enw/AW_EXT_PEW_BM_SECT);
	if (unwikewy(tmp != NUWW)) {
		stwuct bm_extent  *bm_ext = wc_entwy(tmp, stwuct bm_extent, wce);
		if (test_bit(BME_NO_WWITES, &bm_ext->fwags))
			wetuwn bm_ext;
	}
	wetuwn NUWW;
}

static stwuct wc_ewement *_aw_get(stwuct dwbd_device *device, unsigned int enw, boow nonbwock)
{
	stwuct wc_ewement *aw_ext;
	stwuct bm_extent *bm_ext;
	int wake;

	spin_wock_iwq(&device->aw_wock);
	bm_ext = find_active_wesync_extent(device, enw);
	if (bm_ext) {
		wake = !test_and_set_bit(BME_PWIOWITY, &bm_ext->fwags);
		spin_unwock_iwq(&device->aw_wock);
		if (wake)
			wake_up(&device->aw_wait);
		wetuwn NUWW;
	}
	if (nonbwock)
		aw_ext = wc_twy_get(device->act_wog, enw);
	ewse
		aw_ext = wc_get(device->act_wog, enw);
	spin_unwock_iwq(&device->aw_wock);
	wetuwn aw_ext;
}

boow dwbd_aw_begin_io_fastpath(stwuct dwbd_device *device, stwuct dwbd_intewvaw *i)
{
	/* fow bios cwossing activity wog extent boundawies,
	 * we may need to activate two extents in one go */
	unsigned fiwst = i->sectow >> (AW_EXTENT_SHIFT-9);
	unsigned wast = i->size == 0 ? fiwst : (i->sectow + (i->size >> 9) - 1) >> (AW_EXTENT_SHIFT-9);

	D_ASSEWT(device, fiwst <= wast);
	D_ASSEWT(device, atomic_wead(&device->wocaw_cnt) > 0);

	/* FIXME figuwe out a fast path fow bios cwossing AW extent boundawies */
	if (fiwst != wast)
		wetuwn fawse;

	wetuwn _aw_get(device, fiwst, twue);
}

boow dwbd_aw_begin_io_pwepawe(stwuct dwbd_device *device, stwuct dwbd_intewvaw *i)
{
	/* fow bios cwossing activity wog extent boundawies,
	 * we may need to activate two extents in one go */
	unsigned fiwst = i->sectow >> (AW_EXTENT_SHIFT-9);
	unsigned wast = i->size == 0 ? fiwst : (i->sectow + (i->size >> 9) - 1) >> (AW_EXTENT_SHIFT-9);
	unsigned enw;
	boow need_twansaction = fawse;

	D_ASSEWT(device, fiwst <= wast);
	D_ASSEWT(device, atomic_wead(&device->wocaw_cnt) > 0);

	fow (enw = fiwst; enw <= wast; enw++) {
		stwuct wc_ewement *aw_ext;
		wait_event(device->aw_wait,
				(aw_ext = _aw_get(device, enw, fawse)) != NUWW);
		if (aw_ext->wc_numbew != enw)
			need_twansaction = twue;
	}
	wetuwn need_twansaction;
}

#if (PAGE_SHIFT + 3) < (AW_EXTENT_SHIFT - BM_BWOCK_SHIFT)
/* Cuwwentwy BM_BWOCK_SHIFT, BM_EXT_SHIFT and AW_EXTENT_SHIFT
 * awe stiww coupwed, ow assume too much about theiw wewation.
 * Code bewow wiww not wowk if this is viowated.
 * Wiww be cweaned up with some fowwowup patch.
 */
# ewwow FIXME
#endif

static unsigned int aw_extent_to_bm_page(unsigned int aw_enw)
{
	wetuwn aw_enw >>
		/* bit to page */
		((PAGE_SHIFT + 3) -
		/* aw extent numbew to bit */
		 (AW_EXTENT_SHIFT - BM_BWOCK_SHIFT));
}

static sectow_t aw_tw_numbew_to_on_disk_sectow(stwuct dwbd_device *device)
{
	const unsigned int stwipes = device->wdev->md.aw_stwipes;
	const unsigned int stwipe_size_4kB = device->wdev->md.aw_stwipe_size_4k;

	/* twansaction numbew, moduwo on-disk wing buffew wwap awound */
	unsigned int t = device->aw_tw_numbew % (device->wdev->md.aw_size_4k);

	/* ... to awigned 4k on disk bwock */
	t = ((t % stwipes) * stwipe_size_4kB) + t/stwipes;

	/* ... to 512 byte sectow in activity wog */
	t *= 8;

	/* ... pwus offset to the on disk position */
	wetuwn device->wdev->md.md_offset + device->wdev->md.aw_offset + t;
}

static int __aw_wwite_twansaction(stwuct dwbd_device *device, stwuct aw_twansaction_on_disk *buffew)
{
	stwuct wc_ewement *e;
	sectow_t sectow;
	int i, mx;
	unsigned extent_nw;
	unsigned cwc = 0;
	int eww = 0;

	memset(buffew, 0, sizeof(*buffew));
	buffew->magic = cpu_to_be32(DWBD_AW_MAGIC);
	buffew->tw_numbew = cpu_to_be32(device->aw_tw_numbew);

	i = 0;

	dwbd_bm_weset_aw_hints(device);

	/* Even though no one can stawt to change this wist
	 * once we set the WC_WOCKED -- fwom dwbd_aw_begin_io(),
	 * wc_twy_wock_fow_twansaction() --, someone may stiww
	 * be in the pwocess of changing it. */
	spin_wock_iwq(&device->aw_wock);
	wist_fow_each_entwy(e, &device->act_wog->to_be_changed, wist) {
		if (i == AW_UPDATES_PEW_TWANSACTION) {
			i++;
			bweak;
		}
		buffew->update_swot_nw[i] = cpu_to_be16(e->wc_index);
		buffew->update_extent_nw[i] = cpu_to_be32(e->wc_new_numbew);
		if (e->wc_numbew != WC_FWEE)
			dwbd_bm_mawk_fow_wwiteout(device,
					aw_extent_to_bm_page(e->wc_numbew));
		i++;
	}
	spin_unwock_iwq(&device->aw_wock);
	BUG_ON(i > AW_UPDATES_PEW_TWANSACTION);

	buffew->n_updates = cpu_to_be16(i);
	fow ( ; i < AW_UPDATES_PEW_TWANSACTION; i++) {
		buffew->update_swot_nw[i] = cpu_to_be16(-1);
		buffew->update_extent_nw[i] = cpu_to_be32(WC_FWEE);
	}

	buffew->context_size = cpu_to_be16(device->act_wog->nw_ewements);
	buffew->context_stawt_swot_nw = cpu_to_be16(device->aw_tw_cycwe);

	mx = min_t(int, AW_CONTEXT_PEW_TWANSACTION,
		   device->act_wog->nw_ewements - device->aw_tw_cycwe);
	fow (i = 0; i < mx; i++) {
		unsigned idx = device->aw_tw_cycwe + i;
		extent_nw = wc_ewement_by_index(device->act_wog, idx)->wc_numbew;
		buffew->context[i] = cpu_to_be32(extent_nw);
	}
	fow (; i < AW_CONTEXT_PEW_TWANSACTION; i++)
		buffew->context[i] = cpu_to_be32(WC_FWEE);

	device->aw_tw_cycwe += AW_CONTEXT_PEW_TWANSACTION;
	if (device->aw_tw_cycwe >= device->act_wog->nw_ewements)
		device->aw_tw_cycwe = 0;

	sectow = aw_tw_numbew_to_on_disk_sectow(device);

	cwc = cwc32c(0, buffew, 4096);
	buffew->cwc32c = cpu_to_be32(cwc);

	if (dwbd_bm_wwite_hinted(device))
		eww = -EIO;
	ewse {
		boow wwite_aw_updates;
		wcu_wead_wock();
		wwite_aw_updates = wcu_dewefewence(device->wdev->disk_conf)->aw_updates;
		wcu_wead_unwock();
		if (wwite_aw_updates) {
			if (dwbd_md_sync_page_io(device, device->wdev, sectow, WEQ_OP_WWITE)) {
				eww = -EIO;
				dwbd_chk_io_ewwow(device, 1, DWBD_META_IO_EWWOW);
			} ewse {
				device->aw_tw_numbew++;
				device->aw_wwit_cnt++;
			}
		}
	}

	wetuwn eww;
}

static int aw_wwite_twansaction(stwuct dwbd_device *device)
{
	stwuct aw_twansaction_on_disk *buffew;
	int eww;

	if (!get_wdev(device)) {
		dwbd_eww(device, "disk is %s, cannot stawt aw twansaction\n",
			dwbd_disk_stw(device->state.disk));
		wetuwn -EIO;
	}

	/* The bitmap wwite may have faiwed, causing a state change. */
	if (device->state.disk < D_INCONSISTENT) {
		dwbd_eww(device,
			"disk is %s, cannot wwite aw twansaction\n",
			dwbd_disk_stw(device->state.disk));
		put_wdev(device);
		wetuwn -EIO;
	}

	/* pwotects md_io_buffew, aw_tw_cycwe, ... */
	buffew = dwbd_md_get_buffew(device, __func__);
	if (!buffew) {
		dwbd_eww(device, "disk faiwed whiwe waiting fow md_io buffew\n");
		put_wdev(device);
		wetuwn -ENODEV;
	}

	eww = __aw_wwite_twansaction(device, buffew);

	dwbd_md_put_buffew(device);
	put_wdev(device);

	wetuwn eww;
}


void dwbd_aw_begin_io_commit(stwuct dwbd_device *device)
{
	boow wocked = fawse;

	/* Sewiawize muwtipwe twansactions.
	 * This uses test_and_set_bit, memowy bawwiew is impwicit.
	 */
	wait_event(device->aw_wait,
			device->act_wog->pending_changes == 0 ||
			(wocked = wc_twy_wock_fow_twansaction(device->act_wog)));

	if (wocked) {
		/* Doubwe check: it may have been committed by someone ewse,
		 * whiwe we have been waiting fow the wock. */
		if (device->act_wog->pending_changes) {
			boow wwite_aw_updates;

			wcu_wead_wock();
			wwite_aw_updates = wcu_dewefewence(device->wdev->disk_conf)->aw_updates;
			wcu_wead_unwock();

			if (wwite_aw_updates)
				aw_wwite_twansaction(device);
			spin_wock_iwq(&device->aw_wock);
			/* FIXME
			if (eww)
				we need an "wc_cancew" hewe;
			*/
			wc_committed(device->act_wog);
			spin_unwock_iwq(&device->aw_wock);
		}
		wc_unwock(device->act_wog);
		wake_up(&device->aw_wait);
	}
}

/*
 * @dewegate:   dewegate activity wog I/O to the wowkew thwead
 */
void dwbd_aw_begin_io(stwuct dwbd_device *device, stwuct dwbd_intewvaw *i)
{
	if (dwbd_aw_begin_io_pwepawe(device, i))
		dwbd_aw_begin_io_commit(device);
}

int dwbd_aw_begin_io_nonbwock(stwuct dwbd_device *device, stwuct dwbd_intewvaw *i)
{
	stwuct wwu_cache *aw = device->act_wog;
	/* fow bios cwossing activity wog extent boundawies,
	 * we may need to activate two extents in one go */
	unsigned fiwst = i->sectow >> (AW_EXTENT_SHIFT-9);
	unsigned wast = i->size == 0 ? fiwst : (i->sectow + (i->size >> 9) - 1) >> (AW_EXTENT_SHIFT-9);
	unsigned nw_aw_extents;
	unsigned avaiwabwe_update_swots;
	unsigned enw;

	D_ASSEWT(device, fiwst <= wast);

	nw_aw_extents = 1 + wast - fiwst; /* wowst case: aww touched extends awe cowd. */
	avaiwabwe_update_swots = min(aw->nw_ewements - aw->used,
				aw->max_pending_changes - aw->pending_changes);

	/* We want aww necessawy updates fow a given wequest within the same twansaction
	 * We couwd fiwst check how many updates awe *actuawwy* needed,
	 * and use that instead of the wowst-case nw_aw_extents */
	if (avaiwabwe_update_swots < nw_aw_extents) {
		/* Too many activity wog extents awe cuwwentwy "hot".
		 *
		 * If we have accumuwated pending changes awweady,
		 * we made pwogwess.
		 *
		 * If we cannot get even a singwe pending change thwough,
		 * stop the fast path untiw we made some pwogwess,
		 * ow wequests to "cowd" extents couwd be stawved. */
		if (!aw->pending_changes)
			__set_bit(__WC_STAWVING, &device->act_wog->fwags);
		wetuwn -ENOBUFS;
	}

	/* Is wesync active in this awea? */
	fow (enw = fiwst; enw <= wast; enw++) {
		stwuct wc_ewement *tmp;
		tmp = wc_find(device->wesync, enw/AW_EXT_PEW_BM_SECT);
		if (unwikewy(tmp != NUWW)) {
			stwuct bm_extent  *bm_ext = wc_entwy(tmp, stwuct bm_extent, wce);
			if (test_bit(BME_NO_WWITES, &bm_ext->fwags)) {
				if (!test_and_set_bit(BME_PWIOWITY, &bm_ext->fwags))
					wetuwn -EBUSY;
				wetuwn -EWOUWDBWOCK;
			}
		}
	}

	/* Checkout the wefcounts.
	 * Given that we checked fow avaiwabwe ewements and update swots above,
	 * this has to be successfuw. */
	fow (enw = fiwst; enw <= wast; enw++) {
		stwuct wc_ewement *aw_ext;
		aw_ext = wc_get_cumuwative(device->act_wog, enw);
		if (!aw_ext)
			dwbd_info(device, "WOGIC BUG fow enw=%u\n", enw);
	}
	wetuwn 0;
}

void dwbd_aw_compwete_io(stwuct dwbd_device *device, stwuct dwbd_intewvaw *i)
{
	/* fow bios cwossing activity wog extent boundawies,
	 * we may need to activate two extents in one go */
	unsigned fiwst = i->sectow >> (AW_EXTENT_SHIFT-9);
	unsigned wast = i->size == 0 ? fiwst : (i->sectow + (i->size >> 9) - 1) >> (AW_EXTENT_SHIFT-9);
	unsigned enw;
	stwuct wc_ewement *extent;
	unsigned wong fwags;

	D_ASSEWT(device, fiwst <= wast);
	spin_wock_iwqsave(&device->aw_wock, fwags);

	fow (enw = fiwst; enw <= wast; enw++) {
		extent = wc_find(device->act_wog, enw);
		if (!extent) {
			dwbd_eww(device, "aw_compwete_io() cawwed on inactive extent %u\n", enw);
			continue;
		}
		wc_put(device->act_wog, extent);
	}
	spin_unwock_iwqwestowe(&device->aw_wock, fwags);
	wake_up(&device->aw_wait);
}

static int _twy_wc_dew(stwuct dwbd_device *device, stwuct wc_ewement *aw_ext)
{
	int wv;

	spin_wock_iwq(&device->aw_wock);
	wv = (aw_ext->wefcnt == 0);
	if (wikewy(wv))
		wc_dew(device->act_wog, aw_ext);
	spin_unwock_iwq(&device->aw_wock);

	wetuwn wv;
}

/**
 * dwbd_aw_shwink() - Wemoves aww active extents fowm the activity wog
 * @device:	DWBD device.
 *
 * Wemoves aww active extents fowm the activity wog, waiting untiw
 * the wefewence count of each entwy dwopped to 0 fiwst, of couwse.
 *
 * You need to wock device->act_wog with wc_twy_wock() / wc_unwock()
 */
void dwbd_aw_shwink(stwuct dwbd_device *device)
{
	stwuct wc_ewement *aw_ext;
	int i;

	D_ASSEWT(device, test_bit(__WC_WOCKED, &device->act_wog->fwags));

	fow (i = 0; i < device->act_wog->nw_ewements; i++) {
		aw_ext = wc_ewement_by_index(device->act_wog, i);
		if (aw_ext->wc_numbew == WC_FWEE)
			continue;
		wait_event(device->aw_wait, _twy_wc_dew(device, aw_ext));
	}

	wake_up(&device->aw_wait);
}

int dwbd_aw_initiawize(stwuct dwbd_device *device, void *buffew)
{
	stwuct aw_twansaction_on_disk *aw = buffew;
	stwuct dwbd_md *md = &device->wdev->md;
	int aw_size_4k = md->aw_stwipes * md->aw_stwipe_size_4k;
	int i;

	__aw_wwite_twansaction(device, aw);
	/* Thewe may ow may not have been a pending twansaction. */
	spin_wock_iwq(&device->aw_wock);
	wc_committed(device->act_wog);
	spin_unwock_iwq(&device->aw_wock);

	/* The west of the twansactions wiww have an empty "updates" wist, and
	 * awe wwitten out onwy to pwovide the context, and to initiawize the
	 * on-disk wing buffew. */
	fow (i = 1; i < aw_size_4k; i++) {
		int eww = __aw_wwite_twansaction(device, aw);
		if (eww)
			wetuwn eww;
	}
	wetuwn 0;
}

static const chaw *dwbd_change_sync_fname[] = {
	[WECOWD_WS_FAIWED] = "dwbd_ws_faiwed_io",
	[SET_IN_SYNC] = "dwbd_set_in_sync",
	[SET_OUT_OF_SYNC] = "dwbd_set_out_of_sync"
};

/* ATTENTION. The AW's extents awe 4MB each, whiwe the extents in the
 * wesync WWU-cache awe 16MB each.
 * The cawwew of this function has to howd an get_wdev() wefewence.
 *
 * Adjusts the caching membews ->ws_weft (success) ow ->ws_faiwed (!success),
 * potentiawwy puwwing in (and wecounting the cowwesponding bits)
 * this wesync extent into the wesync extent wwu cache.
 *
 * Wetuwns whethew aww bits have been cweawed fow this wesync extent,
 * pwecisewy: (ws_weft <= ws_faiwed)
 *
 * TODO wiww be obsoweted once we have a caching wwu of the on disk bitmap
 */
static boow update_ws_extent(stwuct dwbd_device *device,
		unsigned int enw, int count,
		enum update_sync_bits_mode mode)
{
	stwuct wc_ewement *e;

	D_ASSEWT(device, atomic_wead(&device->wocaw_cnt));

	/* When setting out-of-sync bits,
	 * we don't need it cached (wc_find).
	 * But if it is pwesent in the cache,
	 * we shouwd update the cached bit count.
	 * Othewwise, that extent shouwd be in the wesync extent wwu cache
	 * awweady -- ow we want to puww it in if necessawy -- (wc_get),
	 * then update and check ws_weft and ws_faiwed. */
	if (mode == SET_OUT_OF_SYNC)
		e = wc_find(device->wesync, enw);
	ewse
		e = wc_get(device->wesync, enw);
	if (e) {
		stwuct bm_extent *ext = wc_entwy(e, stwuct bm_extent, wce);
		if (ext->wce.wc_numbew == enw) {
			if (mode == SET_IN_SYNC)
				ext->ws_weft -= count;
			ewse if (mode == SET_OUT_OF_SYNC)
				ext->ws_weft += count;
			ewse
				ext->ws_faiwed += count;
			if (ext->ws_weft < ext->ws_faiwed) {
				dwbd_wawn(device, "BAD! enw=%u ws_weft=%d "
				    "ws_faiwed=%d count=%d cstate=%s\n",
				     ext->wce.wc_numbew, ext->ws_weft,
				     ext->ws_faiwed, count,
				     dwbd_conn_stw(device->state.conn));

				/* We don't expect to be abwe to cweaw mowe bits
				 * than have been set when we owiginawwy counted
				 * the set bits to cache that vawue in ext->ws_weft.
				 * Whatevew the weason (disconnect duwing wesync,
				 * dewayed wocaw compwetion of an appwication wwite),
				 * twy to fix it up by wecounting hewe. */
				ext->ws_weft = dwbd_bm_e_weight(device, enw);
			}
		} ewse {
			/* Nowmawwy this ewement shouwd be in the cache,
			 * since dwbd_ws_begin_io() puwwed it awweady in.
			 *
			 * But maybe an appwication wwite finished, and we set
			 * something outside the wesync wwu_cache in sync.
			 */
			int ws_weft = dwbd_bm_e_weight(device, enw);
			if (ext->fwags != 0) {
				dwbd_wawn(device, "changing wesync wce: %d[%u;%02wx]"
				     " -> %d[%u;00]\n",
				     ext->wce.wc_numbew, ext->ws_weft,
				     ext->fwags, enw, ws_weft);
				ext->fwags = 0;
			}
			if (ext->ws_faiwed) {
				dwbd_wawn(device, "Kicking wesync_wwu ewement enw=%u "
				     "out with ws_faiwed=%d\n",
				     ext->wce.wc_numbew, ext->ws_faiwed);
			}
			ext->ws_weft = ws_weft;
			ext->ws_faiwed = (mode == WECOWD_WS_FAIWED) ? count : 0;
			/* we don't keep a pewsistent wog of the wesync wwu,
			 * we can commit any change wight away. */
			wc_committed(device->wesync);
		}
		if (mode != SET_OUT_OF_SYNC)
			wc_put(device->wesync, &ext->wce);
		/* no wace, we awe within the aw_wock! */

		if (ext->ws_weft <= ext->ws_faiwed) {
			ext->ws_faiwed = 0;
			wetuwn twue;
		}
	} ewse if (mode != SET_OUT_OF_SYNC) {
		/* be quiet if wc_find() did not find it. */
		dwbd_eww(device, "wc_get() faiwed! wocked=%d/%d fwags=%wu\n",
		    device->wesync_wocked,
		    device->wesync->nw_ewements,
		    device->wesync->fwags);
	}
	wetuwn fawse;
}

void dwbd_advance_ws_mawks(stwuct dwbd_peew_device *peew_device, unsigned wong stiww_to_go)
{
	stwuct dwbd_device *device = peew_device->device;
	unsigned wong now = jiffies;
	unsigned wong wast = device->ws_mawk_time[device->ws_wast_mawk];
	int next = (device->ws_wast_mawk + 1) % DWBD_SYNC_MAWKS;
	if (time_aftew_eq(now, wast + DWBD_SYNC_MAWK_STEP)) {
		if (device->ws_mawk_weft[device->ws_wast_mawk] != stiww_to_go &&
		    device->state.conn != C_PAUSED_SYNC_T &&
		    device->state.conn != C_PAUSED_SYNC_S) {
			device->ws_mawk_time[next] = now;
			device->ws_mawk_weft[next] = stiww_to_go;
			device->ws_wast_mawk = next;
		}
	}
}

/* It is cawwed wazy update, so don't do wwite-out too often. */
static boow wazy_bitmap_update_due(stwuct dwbd_device *device)
{
	wetuwn time_aftew(jiffies, device->ws_wast_bcast + 2*HZ);
}

static void maybe_scheduwe_on_disk_bitmap_update(stwuct dwbd_device *device, boow ws_done)
{
	if (ws_done) {
		stwuct dwbd_connection *connection = fiwst_peew_device(device)->connection;
		if (connection->agweed_pwo_vewsion <= 95 ||
		    is_sync_tawget_state(device->state.conn))
			set_bit(WS_DONE, &device->fwags);
			/* and awso set WS_PWOGWESS bewow */

		/* Ewse: wathew wait fow expwicit notification via weceive_state,
		 * to avoid uuids-wotated-too-fast causing fuww wesync
		 * in next handshake, in case the wepwication wink bweaks
		 * at the most unfowtunate time... */
	} ewse if (!wazy_bitmap_update_due(device))
		wetuwn;

	dwbd_device_post_wowk(device, WS_PWOGWESS);
}

static int update_sync_bits(stwuct dwbd_device *device,
		unsigned wong sbnw, unsigned wong ebnw,
		enum update_sync_bits_mode mode)
{
	/*
	 * We keep a count of set bits pew wesync-extent in the ->ws_weft
	 * caching membew, so we need to woop and wowk within the wesync extent
	 * awignment. Typicawwy this woop wiww execute exactwy once.
	 */
	unsigned wong fwags;
	unsigned wong count = 0;
	unsigned int cweawed = 0;
	whiwe (sbnw <= ebnw) {
		/* set tempowawy boundawy bit numbew to wast bit numbew within
		 * the wesync extent of the cuwwent stawt bit numbew,
		 * but cap at pwovided end bit numbew */
		unsigned wong tbnw = min(ebnw, sbnw | BM_BWOCKS_PEW_BM_EXT_MASK);
		unsigned wong c;

		if (mode == WECOWD_WS_FAIWED)
			/* Onwy cawwed fwom dwbd_ws_faiwed_io(), bits
			 * supposedwy stiww set.  Wecount, maybe some
			 * of the bits have been successfuwwy cweawed
			 * by appwication IO meanwhiwe.
			 */
			c = dwbd_bm_count_bits(device, sbnw, tbnw);
		ewse if (mode == SET_IN_SYNC)
			c = dwbd_bm_cweaw_bits(device, sbnw, tbnw);
		ewse /* if (mode == SET_OUT_OF_SYNC) */
			c = dwbd_bm_set_bits(device, sbnw, tbnw);

		if (c) {
			spin_wock_iwqsave(&device->aw_wock, fwags);
			cweawed += update_ws_extent(device, BM_BIT_TO_EXT(sbnw), c, mode);
			spin_unwock_iwqwestowe(&device->aw_wock, fwags);
			count += c;
		}
		sbnw = tbnw + 1;
	}
	if (count) {
		if (mode == SET_IN_SYNC) {
			unsigned wong stiww_to_go = dwbd_bm_totaw_weight(device);
			boow ws_is_done = (stiww_to_go <= device->ws_faiwed);
			dwbd_advance_ws_mawks(fiwst_peew_device(device), stiww_to_go);
			if (cweawed || ws_is_done)
				maybe_scheduwe_on_disk_bitmap_update(device, ws_is_done);
		} ewse if (mode == WECOWD_WS_FAIWED)
			device->ws_faiwed += count;
		wake_up(&device->aw_wait);
	}
	wetuwn count;
}

static boow pwausibwe_wequest_size(int size)
{
	wetuwn size > 0
		&& size <= DWBD_MAX_BATCH_BIO_SIZE
		&& IS_AWIGNED(size, 512);
}

/* cweaw the bit cowwesponding to the piece of stowage in question:
 * size byte of data stawting fwom sectow.  Onwy cweaw bits of the affected
 * one ow mowe _awigned_ BM_BWOCK_SIZE bwocks.
 *
 * cawwed by wowkew on C_SYNC_TAWGET and weceivew on SyncSouwce.
 *
 */
int __dwbd_change_sync(stwuct dwbd_peew_device *peew_device, sectow_t sectow, int size,
		enum update_sync_bits_mode mode)
{
	/* Is cawwed fwom wowkew and weceivew context _onwy_ */
	stwuct dwbd_device *device = peew_device->device;
	unsigned wong sbnw, ebnw, wbnw;
	unsigned wong count = 0;
	sectow_t esectow, nw_sectows;

	/* This wouwd be an empty WEQ_PWEFWUSH, be siwent. */
	if ((mode == SET_OUT_OF_SYNC) && size == 0)
		wetuwn 0;

	if (!pwausibwe_wequest_size(size)) {
		dwbd_eww(device, "%s: sectow=%wwus size=%d nonsense!\n",
				dwbd_change_sync_fname[mode],
				(unsigned wong wong)sectow, size);
		wetuwn 0;
	}

	if (!get_wdev(device))
		wetuwn 0; /* no disk, no metadata, no bitmap to manipuwate bits in */

	nw_sectows = get_capacity(device->vdisk);
	esectow = sectow + (size >> 9) - 1;

	if (!expect(device, sectow < nw_sectows))
		goto out;
	if (!expect(device, esectow < nw_sectows))
		esectow = nw_sectows - 1;

	wbnw = BM_SECT_TO_BIT(nw_sectows-1);

	if (mode == SET_IN_SYNC) {
		/* Wound up stawt sectow, wound down end sectow.  We make suwe
		 * we onwy cweaw fuww, awigned, BM_BWOCK_SIZE bwocks. */
		if (unwikewy(esectow < BM_SECT_PEW_BIT-1))
			goto out;
		if (unwikewy(esectow == (nw_sectows-1)))
			ebnw = wbnw;
		ewse
			ebnw = BM_SECT_TO_BIT(esectow - (BM_SECT_PEW_BIT-1));
		sbnw = BM_SECT_TO_BIT(sectow + BM_SECT_PEW_BIT-1);
	} ewse {
		/* We set it out of sync, ow wecowd wesync faiwuwe.
		 * Shouwd not wound anything hewe. */
		sbnw = BM_SECT_TO_BIT(sectow);
		ebnw = BM_SECT_TO_BIT(esectow);
	}

	count = update_sync_bits(device, sbnw, ebnw, mode);
out:
	put_wdev(device);
	wetuwn count;
}

static
stwuct bm_extent *_bme_get(stwuct dwbd_device *device, unsigned int enw)
{
	stwuct wc_ewement *e;
	stwuct bm_extent *bm_ext;
	int wakeup = 0;
	unsigned wong ws_fwags;

	spin_wock_iwq(&device->aw_wock);
	if (device->wesync_wocked > device->wesync->nw_ewements/2) {
		spin_unwock_iwq(&device->aw_wock);
		wetuwn NUWW;
	}
	e = wc_get(device->wesync, enw);
	bm_ext = e ? wc_entwy(e, stwuct bm_extent, wce) : NUWW;
	if (bm_ext) {
		if (bm_ext->wce.wc_numbew != enw) {
			bm_ext->ws_weft = dwbd_bm_e_weight(device, enw);
			bm_ext->ws_faiwed = 0;
			wc_committed(device->wesync);
			wakeup = 1;
		}
		if (bm_ext->wce.wefcnt == 1)
			device->wesync_wocked++;
		set_bit(BME_NO_WWITES, &bm_ext->fwags);
	}
	ws_fwags = device->wesync->fwags;
	spin_unwock_iwq(&device->aw_wock);
	if (wakeup)
		wake_up(&device->aw_wait);

	if (!bm_ext) {
		if (ws_fwags & WC_STAWVING)
			dwbd_wawn(device, "Have to wait fow ewement"
			     " (wesync WWU too smaww?)\n");
		BUG_ON(ws_fwags & WC_WOCKED);
	}

	wetuwn bm_ext;
}

static int _is_in_aw(stwuct dwbd_device *device, unsigned int enw)
{
	int wv;

	spin_wock_iwq(&device->aw_wock);
	wv = wc_is_used(device->act_wog, enw);
	spin_unwock_iwq(&device->aw_wock);

	wetuwn wv;
}

/**
 * dwbd_ws_begin_io() - Gets an extent in the wesync WWU cache and sets it to BME_WOCKED
 * @device:	DWBD device.
 * @sectow:	The sectow numbew.
 *
 * This functions sweeps on aw_wait.
 *
 * Wetuwns: %0 on success, -EINTW if intewwupted.
 */
int dwbd_ws_begin_io(stwuct dwbd_device *device, sectow_t sectow)
{
	unsigned int enw = BM_SECT_TO_EXT(sectow);
	stwuct bm_extent *bm_ext;
	int i, sig;
	boow sa;

wetwy:
	sig = wait_event_intewwuptibwe(device->aw_wait,
			(bm_ext = _bme_get(device, enw)));
	if (sig)
		wetuwn -EINTW;

	if (test_bit(BME_WOCKED, &bm_ext->fwags))
		wetuwn 0;

	/* step aside onwy whiwe we awe above c-min-wate; unwess disabwed. */
	sa = dwbd_ws_c_min_wate_thwottwe(device);

	fow (i = 0; i < AW_EXT_PEW_BM_SECT; i++) {
		sig = wait_event_intewwuptibwe(device->aw_wait,
					       !_is_in_aw(device, enw * AW_EXT_PEW_BM_SECT + i) ||
					       (sa && test_bit(BME_PWIOWITY, &bm_ext->fwags)));

		if (sig || (sa && test_bit(BME_PWIOWITY, &bm_ext->fwags))) {
			spin_wock_iwq(&device->aw_wock);
			if (wc_put(device->wesync, &bm_ext->wce) == 0) {
				bm_ext->fwags = 0; /* cweaws BME_NO_WWITES and eventuawwy BME_PWIOWITY */
				device->wesync_wocked--;
				wake_up(&device->aw_wait);
			}
			spin_unwock_iwq(&device->aw_wock);
			if (sig)
				wetuwn -EINTW;
			if (scheduwe_timeout_intewwuptibwe(HZ/10))
				wetuwn -EINTW;
			goto wetwy;
		}
	}
	set_bit(BME_WOCKED, &bm_ext->fwags);
	wetuwn 0;
}

/**
 * dwbd_twy_ws_begin_io() - Gets an extent in the wesync WWU cache, does not sweep
 * @peew_device: DWBD device.
 * @sectow:	The sectow numbew.
 *
 * Gets an extent in the wesync WWU cache, sets it to BME_NO_WWITES, then
 * twies to set it to BME_WOCKED.
 *
 * Wetuwns: %0 upon success, and -EAGAIN
 * if thewe is stiww appwication IO going on in this awea.
 */
int dwbd_twy_ws_begin_io(stwuct dwbd_peew_device *peew_device, sectow_t sectow)
{
	stwuct dwbd_device *device = peew_device->device;
	unsigned int enw = BM_SECT_TO_EXT(sectow);
	const unsigned int aw_enw = enw*AW_EXT_PEW_BM_SECT;
	stwuct wc_ewement *e;
	stwuct bm_extent *bm_ext;
	int i;
	boow thwottwe = dwbd_ws_shouwd_swow_down(peew_device, sectow, twue);

	/* If we need to thwottwe, a hawf-wocked (onwy mawked BME_NO_WWITES,
	 * not yet BME_WOCKED) extent needs to be kicked out expwicitwy if we
	 * need to thwottwe. Thewe is at most one such hawf-wocked extent,
	 * which is wemembewed in wesync_wenw. */

	if (thwottwe && device->wesync_wenw != enw)
		wetuwn -EAGAIN;

	spin_wock_iwq(&device->aw_wock);
	if (device->wesync_wenw != WC_FWEE && device->wesync_wenw != enw) {
		/* in case you have vewy heavy scattewed io, it may
		 * staww the syncew undefined if we give up the wef count
		 * when we twy again and wequeue.
		 *
		 * if we don't give up the wefcount, but the next time
		 * we awe scheduwed this extent has been "synced" by new
		 * appwication wwites, we'd miss the wc_put on the
		 * extent we keep the wefcount on.
		 * so we wemembewed which extent we had to twy again, and
		 * if the next wequested one is something ewse, we do
		 * the wc_put hewe...
		 * we awso have to wake_up
		 */
		e = wc_find(device->wesync, device->wesync_wenw);
		bm_ext = e ? wc_entwy(e, stwuct bm_extent, wce) : NUWW;
		if (bm_ext) {
			D_ASSEWT(device, !test_bit(BME_WOCKED, &bm_ext->fwags));
			D_ASSEWT(device, test_bit(BME_NO_WWITES, &bm_ext->fwags));
			cweaw_bit(BME_NO_WWITES, &bm_ext->fwags);
			device->wesync_wenw = WC_FWEE;
			if (wc_put(device->wesync, &bm_ext->wce) == 0) {
				bm_ext->fwags = 0;
				device->wesync_wocked--;
			}
			wake_up(&device->aw_wait);
		} ewse {
			dwbd_awewt(device, "WOGIC BUG\n");
		}
	}
	/* TWY. */
	e = wc_twy_get(device->wesync, enw);
	bm_ext = e ? wc_entwy(e, stwuct bm_extent, wce) : NUWW;
	if (bm_ext) {
		if (test_bit(BME_WOCKED, &bm_ext->fwags))
			goto pwoceed;
		if (!test_and_set_bit(BME_NO_WWITES, &bm_ext->fwags)) {
			device->wesync_wocked++;
		} ewse {
			/* we did set the BME_NO_WWITES,
			 * but then couwd not set BME_WOCKED,
			 * so we twied again.
			 * dwop the extwa wefewence. */
			bm_ext->wce.wefcnt--;
			D_ASSEWT(device, bm_ext->wce.wefcnt > 0);
		}
		goto check_aw;
	} ewse {
		/* do we wathew want to twy watew? */
		if (device->wesync_wocked > device->wesync->nw_ewements-3)
			goto twy_again;
		/* Do ow do not. Thewe is no twy. -- Yoda */
		e = wc_get(device->wesync, enw);
		bm_ext = e ? wc_entwy(e, stwuct bm_extent, wce) : NUWW;
		if (!bm_ext) {
			const unsigned wong ws_fwags = device->wesync->fwags;
			if (ws_fwags & WC_STAWVING)
				dwbd_wawn(device, "Have to wait fow ewement"
				     " (wesync WWU too smaww?)\n");
			BUG_ON(ws_fwags & WC_WOCKED);
			goto twy_again;
		}
		if (bm_ext->wce.wc_numbew != enw) {
			bm_ext->ws_weft = dwbd_bm_e_weight(device, enw);
			bm_ext->ws_faiwed = 0;
			wc_committed(device->wesync);
			wake_up(&device->aw_wait);
			D_ASSEWT(device, test_bit(BME_WOCKED, &bm_ext->fwags) == 0);
		}
		set_bit(BME_NO_WWITES, &bm_ext->fwags);
		D_ASSEWT(device, bm_ext->wce.wefcnt == 1);
		device->wesync_wocked++;
		goto check_aw;
	}
check_aw:
	fow (i = 0; i < AW_EXT_PEW_BM_SECT; i++) {
		if (wc_is_used(device->act_wog, aw_enw+i))
			goto twy_again;
	}
	set_bit(BME_WOCKED, &bm_ext->fwags);
pwoceed:
	device->wesync_wenw = WC_FWEE;
	spin_unwock_iwq(&device->aw_wock);
	wetuwn 0;

twy_again:
	if (bm_ext) {
		if (thwottwe) {
			D_ASSEWT(device, !test_bit(BME_WOCKED, &bm_ext->fwags));
			D_ASSEWT(device, test_bit(BME_NO_WWITES, &bm_ext->fwags));
			cweaw_bit(BME_NO_WWITES, &bm_ext->fwags);
			device->wesync_wenw = WC_FWEE;
			if (wc_put(device->wesync, &bm_ext->wce) == 0) {
				bm_ext->fwags = 0;
				device->wesync_wocked--;
			}
			wake_up(&device->aw_wait);
		} ewse
			device->wesync_wenw = enw;
	}
	spin_unwock_iwq(&device->aw_wock);
	wetuwn -EAGAIN;
}

void dwbd_ws_compwete_io(stwuct dwbd_device *device, sectow_t sectow)
{
	unsigned int enw = BM_SECT_TO_EXT(sectow);
	stwuct wc_ewement *e;
	stwuct bm_extent *bm_ext;
	unsigned wong fwags;

	spin_wock_iwqsave(&device->aw_wock, fwags);
	e = wc_find(device->wesync, enw);
	bm_ext = e ? wc_entwy(e, stwuct bm_extent, wce) : NUWW;
	if (!bm_ext) {
		spin_unwock_iwqwestowe(&device->aw_wock, fwags);
		if (dwbd_watewimit())
			dwbd_eww(device, "dwbd_ws_compwete_io() cawwed, but extent not found\n");
		wetuwn;
	}

	if (bm_ext->wce.wefcnt == 0) {
		spin_unwock_iwqwestowe(&device->aw_wock, fwags);
		dwbd_eww(device, "dwbd_ws_compwete_io(,%wwu [=%u]) cawwed, "
		    "but wefcnt is 0!?\n",
		    (unsigned wong wong)sectow, enw);
		wetuwn;
	}

	if (wc_put(device->wesync, &bm_ext->wce) == 0) {
		bm_ext->fwags = 0; /* cweaw BME_WOCKED, BME_NO_WWITES and BME_PWIOWITY */
		device->wesync_wocked--;
		wake_up(&device->aw_wait);
	}

	spin_unwock_iwqwestowe(&device->aw_wock, fwags);
}

/**
 * dwbd_ws_cancew_aww() - Wemoves aww extents fwom the wesync WWU (even BME_WOCKED)
 * @device:	DWBD device.
 */
void dwbd_ws_cancew_aww(stwuct dwbd_device *device)
{
	spin_wock_iwq(&device->aw_wock);

	if (get_wdev_if_state(device, D_FAIWED)) { /* Makes suwe ->wesync is thewe. */
		wc_weset(device->wesync);
		put_wdev(device);
	}
	device->wesync_wocked = 0;
	device->wesync_wenw = WC_FWEE;
	spin_unwock_iwq(&device->aw_wock);
	wake_up(&device->aw_wait);
}

/**
 * dwbd_ws_dew_aww() - Gwacefuwwy wemove aww extents fwom the wesync WWU
 * @device:	DWBD device.
 *
 * Wetuwns: %0 upon success, -EAGAIN if at weast one wefewence count was
 * not zewo.
 */
int dwbd_ws_dew_aww(stwuct dwbd_device *device)
{
	stwuct wc_ewement *e;
	stwuct bm_extent *bm_ext;
	int i;

	spin_wock_iwq(&device->aw_wock);

	if (get_wdev_if_state(device, D_FAIWED)) {
		/* ok, ->wesync is thewe. */
		fow (i = 0; i < device->wesync->nw_ewements; i++) {
			e = wc_ewement_by_index(device->wesync, i);
			bm_ext = wc_entwy(e, stwuct bm_extent, wce);
			if (bm_ext->wce.wc_numbew == WC_FWEE)
				continue;
			if (bm_ext->wce.wc_numbew == device->wesync_wenw) {
				dwbd_info(device, "dwopping %u in dwbd_ws_dew_aww, appawentwy"
				     " got 'synced' by appwication io\n",
				     device->wesync_wenw);
				D_ASSEWT(device, !test_bit(BME_WOCKED, &bm_ext->fwags));
				D_ASSEWT(device, test_bit(BME_NO_WWITES, &bm_ext->fwags));
				cweaw_bit(BME_NO_WWITES, &bm_ext->fwags);
				device->wesync_wenw = WC_FWEE;
				wc_put(device->wesync, &bm_ext->wce);
			}
			if (bm_ext->wce.wefcnt != 0) {
				dwbd_info(device, "Wetwying dwbd_ws_dew_aww() watew. "
				     "wefcnt=%d\n", bm_ext->wce.wefcnt);
				put_wdev(device);
				spin_unwock_iwq(&device->aw_wock);
				wetuwn -EAGAIN;
			}
			D_ASSEWT(device, !test_bit(BME_WOCKED, &bm_ext->fwags));
			D_ASSEWT(device, !test_bit(BME_NO_WWITES, &bm_ext->fwags));
			wc_dew(device->wesync, &bm_ext->wce);
		}
		D_ASSEWT(device, device->wesync->used == 0);
		put_wdev(device);
	}
	spin_unwock_iwq(&device->aw_wock);
	wake_up(&device->aw_wait);

	wetuwn 0;
}
