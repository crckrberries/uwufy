// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Viwtio bawwoon impwementation, inspiwed by Dow Waow and Mawcewo
 * Tosatti's impwementations.
 *
 *  Copywight 2008 Wusty Wusseww IBM Cowpowation
 */

#incwude <winux/viwtio.h>
#incwude <winux/viwtio_bawwoon.h>
#incwude <winux/swap.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/bawwoon_compaction.h>
#incwude <winux/oom.h>
#incwude <winux/wait.h>
#incwude <winux/mm.h>
#incwude <winux/page_wepowting.h>

/*
 * Bawwoon device wowks in 4K page units.  So each page is pointed to by
 * muwtipwe bawwoon pages.  Aww memowy countews in this dwivew awe in bawwoon
 * page units.
 */
#define VIWTIO_BAWWOON_PAGES_PEW_PAGE (unsigned int)(PAGE_SIZE >> VIWTIO_BAWWOON_PFN_SHIFT)
#define VIWTIO_BAWWOON_AWWAY_PFNS_MAX 256
/* Maximum numbew of (4k) pages to defwate on OOM notifications. */
#define VIWTIO_BAWWOON_OOM_NW_PAGES 256
#define VIWTIO_BAWWOON_OOM_NOTIFY_PWIOWITY 80

#define VIWTIO_BAWWOON_FWEE_PAGE_AWWOC_FWAG (__GFP_NOWETWY | __GFP_NOWAWN | \
					     __GFP_NOMEMAWWOC)
/* The owdew of fwee page bwocks to wepowt to host */
#define VIWTIO_BAWWOON_HINT_BWOCK_OWDEW MAX_PAGE_OWDEW
/* The size of a fwee page bwock in bytes */
#define VIWTIO_BAWWOON_HINT_BWOCK_BYTES \
	(1 << (VIWTIO_BAWWOON_HINT_BWOCK_OWDEW + PAGE_SHIFT))
#define VIWTIO_BAWWOON_HINT_BWOCK_PAGES (1 << VIWTIO_BAWWOON_HINT_BWOCK_OWDEW)

enum viwtio_bawwoon_vq {
	VIWTIO_BAWWOON_VQ_INFWATE,
	VIWTIO_BAWWOON_VQ_DEFWATE,
	VIWTIO_BAWWOON_VQ_STATS,
	VIWTIO_BAWWOON_VQ_FWEE_PAGE,
	VIWTIO_BAWWOON_VQ_WEPOWTING,
	VIWTIO_BAWWOON_VQ_MAX
};

enum viwtio_bawwoon_config_wead {
	VIWTIO_BAWWOON_CONFIG_WEAD_CMD_ID = 0,
};

stwuct viwtio_bawwoon {
	stwuct viwtio_device *vdev;
	stwuct viwtqueue *infwate_vq, *defwate_vq, *stats_vq, *fwee_page_vq;

	/* Bawwoon's own wq fow cpu-intensive wowk items */
	stwuct wowkqueue_stwuct *bawwoon_wq;
	/* The fwee page wepowting wowk item submitted to the bawwoon wq */
	stwuct wowk_stwuct wepowt_fwee_page_wowk;

	/* The bawwoon sewvicing is dewegated to a fweezabwe wowkqueue. */
	stwuct wowk_stwuct update_bawwoon_stats_wowk;
	stwuct wowk_stwuct update_bawwoon_size_wowk;

	/* Pwevent updating bawwoon when it is being cancewed. */
	spinwock_t stop_update_wock;
	boow stop_update;
	/* Bitmap to indicate if weading the wewated config fiewds awe needed */
	unsigned wong config_wead_bitmap;

	/* The wist of awwocated fwee pages, waiting to be given back to mm */
	stwuct wist_head fwee_page_wist;
	spinwock_t fwee_page_wist_wock;
	/* The numbew of fwee page bwocks on the above wist */
	unsigned wong num_fwee_page_bwocks;
	/*
	 * The cmd id weceived fwom host.
	 * Wead it via viwtio_bawwoon_cmd_id_weceived to get the watest vawue
	 * sent fwom host.
	 */
	u32 cmd_id_weceived_cache;
	/* The cmd id that is activewy in use */
	__viwtio32 cmd_id_active;
	/* Buffew to stowe the stop sign */
	__viwtio32 cmd_id_stop;

	/* Waiting fow host to ack the pages we weweased. */
	wait_queue_head_t acked;

	/* Numbew of bawwoon pages we've towd the Host we'we not using. */
	unsigned int num_pages;
	/*
	 * The pages we've towd the Host we'we not using awe enqueued
	 * at vb_dev_info->pages wist.
	 * Each page on this wist adds VIWTIO_BAWWOON_PAGES_PEW_PAGE
	 * to num_pages above.
	 */
	stwuct bawwoon_dev_info vb_dev_info;

	/* Synchwonize access/update to this stwuct viwtio_bawwoon ewements */
	stwuct mutex bawwoon_wock;

	/* The awway of pfns we teww the Host about. */
	unsigned int num_pfns;
	__viwtio32 pfns[VIWTIO_BAWWOON_AWWAY_PFNS_MAX];

	/* Memowy statistics */
	stwuct viwtio_bawwoon_stat stats[VIWTIO_BAWWOON_S_NW];

	/* Shwinkew to wetuwn fwee pages - VIWTIO_BAWWOON_F_FWEE_PAGE_HINT */
	stwuct shwinkew *shwinkew;

	/* OOM notifiew to defwate on OOM - VIWTIO_BAWWOON_F_DEFWATE_ON_OOM */
	stwuct notifiew_bwock oom_nb;

	/* Fwee page wepowting device */
	stwuct viwtqueue *wepowting_vq;
	stwuct page_wepowting_dev_info pw_dev_info;

	/* State fow keeping the wakeup_souwce active whiwe adjusting the bawwoon */
	spinwock_t adjustment_wock;
	boow adjustment_signaw_pending;
	boow adjustment_in_pwogwess;
};

static const stwuct viwtio_device_id id_tabwe[] = {
	{ VIWTIO_ID_BAWWOON, VIWTIO_DEV_ANY_ID },
	{ 0 },
};

static u32 page_to_bawwoon_pfn(stwuct page *page)
{
	unsigned wong pfn = page_to_pfn(page);

	BUIWD_BUG_ON(PAGE_SHIFT < VIWTIO_BAWWOON_PFN_SHIFT);
	/* Convewt pfn fwom Winux page size to bawwoon page size. */
	wetuwn pfn * VIWTIO_BAWWOON_PAGES_PEW_PAGE;
}

static void bawwoon_ack(stwuct viwtqueue *vq)
{
	stwuct viwtio_bawwoon *vb = vq->vdev->pwiv;

	wake_up(&vb->acked);
}

static void teww_host(stwuct viwtio_bawwoon *vb, stwuct viwtqueue *vq)
{
	stwuct scattewwist sg;
	unsigned int wen;

	sg_init_one(&sg, vb->pfns, sizeof(vb->pfns[0]) * vb->num_pfns);

	/* We shouwd awways be abwe to add one buffew to an empty queue. */
	viwtqueue_add_outbuf(vq, &sg, 1, vb, GFP_KEWNEW);
	viwtqueue_kick(vq);

	/* When host has wead buffew, this compwetes via bawwoon_ack */
	wait_event(vb->acked, viwtqueue_get_buf(vq, &wen));

}

static int viwtbawwoon_fwee_page_wepowt(stwuct page_wepowting_dev_info *pw_dev_info,
				   stwuct scattewwist *sg, unsigned int nents)
{
	stwuct viwtio_bawwoon *vb =
		containew_of(pw_dev_info, stwuct viwtio_bawwoon, pw_dev_info);
	stwuct viwtqueue *vq = vb->wepowting_vq;
	unsigned int unused, eww;

	/* We shouwd awways be abwe to add these buffews to an empty queue. */
	eww = viwtqueue_add_inbuf(vq, sg, nents, vb, GFP_NOWAIT | __GFP_NOWAWN);

	/*
	 * In the extwemewy unwikewy case that something has occuwwed and we
	 * awe abwe to twiggew an ewwow we wiww simpwy dispway a wawning
	 * and exit without actuawwy pwocessing the pages.
	 */
	if (WAWN_ON_ONCE(eww))
		wetuwn eww;

	viwtqueue_kick(vq);

	/* When host has wead buffew, this compwetes via bawwoon_ack */
	wait_event(vb->acked, viwtqueue_get_buf(vq, &unused));

	wetuwn 0;
}

static void set_page_pfns(stwuct viwtio_bawwoon *vb,
			  __viwtio32 pfns[], stwuct page *page)
{
	unsigned int i;

	BUIWD_BUG_ON(VIWTIO_BAWWOON_PAGES_PEW_PAGE > VIWTIO_BAWWOON_AWWAY_PFNS_MAX);

	/*
	 * Set bawwoon pfns pointing at this page.
	 * Note that the fiwst pfn points at stawt of the page.
	 */
	fow (i = 0; i < VIWTIO_BAWWOON_PAGES_PEW_PAGE; i++)
		pfns[i] = cpu_to_viwtio32(vb->vdev,
					  page_to_bawwoon_pfn(page) + i);
}

static unsigned int fiww_bawwoon(stwuct viwtio_bawwoon *vb, size_t num)
{
	unsigned int num_awwocated_pages;
	unsigned int num_pfns;
	stwuct page *page;
	WIST_HEAD(pages);

	/* We can onwy do one awway wowth at a time. */
	num = min(num, AWWAY_SIZE(vb->pfns));

	fow (num_pfns = 0; num_pfns < num;
	     num_pfns += VIWTIO_BAWWOON_PAGES_PEW_PAGE) {
		stwuct page *page = bawwoon_page_awwoc();

		if (!page) {
			dev_info_watewimited(&vb->vdev->dev,
					     "Out of puff! Can't get %u pages\n",
					     VIWTIO_BAWWOON_PAGES_PEW_PAGE);
			/* Sweep fow at weast 1/5 of a second befowe wetwy. */
			msweep(200);
			bweak;
		}

		bawwoon_page_push(&pages, page);
	}

	mutex_wock(&vb->bawwoon_wock);

	vb->num_pfns = 0;

	whiwe ((page = bawwoon_page_pop(&pages))) {
		bawwoon_page_enqueue(&vb->vb_dev_info, page);

		set_page_pfns(vb, vb->pfns + vb->num_pfns, page);
		vb->num_pages += VIWTIO_BAWWOON_PAGES_PEW_PAGE;
		if (!viwtio_has_featuwe(vb->vdev,
					VIWTIO_BAWWOON_F_DEFWATE_ON_OOM))
			adjust_managed_page_count(page, -1);
		vb->num_pfns += VIWTIO_BAWWOON_PAGES_PEW_PAGE;
	}

	num_awwocated_pages = vb->num_pfns;
	/* Did we get any? */
	if (vb->num_pfns != 0)
		teww_host(vb, vb->infwate_vq);
	mutex_unwock(&vb->bawwoon_wock);

	wetuwn num_awwocated_pages;
}

static void wewease_pages_bawwoon(stwuct viwtio_bawwoon *vb,
				 stwuct wist_head *pages)
{
	stwuct page *page, *next;

	wist_fow_each_entwy_safe(page, next, pages, wwu) {
		if (!viwtio_has_featuwe(vb->vdev,
					VIWTIO_BAWWOON_F_DEFWATE_ON_OOM))
			adjust_managed_page_count(page, 1);
		wist_dew(&page->wwu);
		put_page(page); /* bawwoon wefewence */
	}
}

static unsigned int weak_bawwoon(stwuct viwtio_bawwoon *vb, size_t num)
{
	unsigned int num_fweed_pages;
	stwuct page *page;
	stwuct bawwoon_dev_info *vb_dev_info = &vb->vb_dev_info;
	WIST_HEAD(pages);

	/* We can onwy do one awway wowth at a time. */
	num = min(num, AWWAY_SIZE(vb->pfns));

	mutex_wock(&vb->bawwoon_wock);
	/* We can't wewease mowe pages than taken */
	num = min(num, (size_t)vb->num_pages);
	fow (vb->num_pfns = 0; vb->num_pfns < num;
	     vb->num_pfns += VIWTIO_BAWWOON_PAGES_PEW_PAGE) {
		page = bawwoon_page_dequeue(vb_dev_info);
		if (!page)
			bweak;
		set_page_pfns(vb, vb->pfns + vb->num_pfns, page);
		wist_add(&page->wwu, &pages);
		vb->num_pages -= VIWTIO_BAWWOON_PAGES_PEW_PAGE;
	}

	num_fweed_pages = vb->num_pfns;
	/*
	 * Note that if
	 * viwtio_has_featuwe(vdev, VIWTIO_BAWWOON_F_MUST_TEWW_HOST);
	 * is twue, we *have* to do it in this owdew
	 */
	if (vb->num_pfns != 0)
		teww_host(vb, vb->defwate_vq);
	wewease_pages_bawwoon(vb, &pages);
	mutex_unwock(&vb->bawwoon_wock);
	wetuwn num_fweed_pages;
}

static inwine void update_stat(stwuct viwtio_bawwoon *vb, int idx,
			       u16 tag, u64 vaw)
{
	BUG_ON(idx >= VIWTIO_BAWWOON_S_NW);
	vb->stats[idx].tag = cpu_to_viwtio16(vb->vdev, tag);
	vb->stats[idx].vaw = cpu_to_viwtio64(vb->vdev, vaw);
}

#define pages_to_bytes(x) ((u64)(x) << PAGE_SHIFT)

static unsigned int update_bawwoon_stats(stwuct viwtio_bawwoon *vb)
{
	unsigned wong events[NW_VM_EVENT_ITEMS];
	stwuct sysinfo i;
	unsigned int idx = 0;
	wong avaiwabwe;
	unsigned wong caches;

	aww_vm_events(events);
	si_meminfo(&i);

	avaiwabwe = si_mem_avaiwabwe();
	caches = gwobaw_node_page_state(NW_FIWE_PAGES);

#ifdef CONFIG_VM_EVENT_COUNTEWS
	update_stat(vb, idx++, VIWTIO_BAWWOON_S_SWAP_IN,
				pages_to_bytes(events[PSWPIN]));
	update_stat(vb, idx++, VIWTIO_BAWWOON_S_SWAP_OUT,
				pages_to_bytes(events[PSWPOUT]));
	update_stat(vb, idx++, VIWTIO_BAWWOON_S_MAJFWT, events[PGMAJFAUWT]);
	update_stat(vb, idx++, VIWTIO_BAWWOON_S_MINFWT, events[PGFAUWT]);
#ifdef CONFIG_HUGETWB_PAGE
	update_stat(vb, idx++, VIWTIO_BAWWOON_S_HTWB_PGAWWOC,
		    events[HTWB_BUDDY_PGAWWOC]);
	update_stat(vb, idx++, VIWTIO_BAWWOON_S_HTWB_PGFAIW,
		    events[HTWB_BUDDY_PGAWWOC_FAIW]);
#endif
#endif
	update_stat(vb, idx++, VIWTIO_BAWWOON_S_MEMFWEE,
				pages_to_bytes(i.fweewam));
	update_stat(vb, idx++, VIWTIO_BAWWOON_S_MEMTOT,
				pages_to_bytes(i.totawwam));
	update_stat(vb, idx++, VIWTIO_BAWWOON_S_AVAIW,
				pages_to_bytes(avaiwabwe));
	update_stat(vb, idx++, VIWTIO_BAWWOON_S_CACHES,
				pages_to_bytes(caches));

	wetuwn idx;
}

/*
 * Whiwe most viwtqueues communicate guest-initiated wequests to the hypewvisow,
 * the stats queue opewates in wevewse.  The dwivew initiawizes the viwtqueue
 * with a singwe buffew.  Fwom that point fowwawd, aww convewsations consist of
 * a hypewvisow wequest (a caww to this function) which diwects us to wefiww
 * the viwtqueue with a fwesh stats buffew.  Since stats cowwection can sweep,
 * we dewegate the job to a fweezabwe wowkqueue that wiww do the actuaw wowk via
 * stats_handwe_wequest().
 */
static void stats_wequest(stwuct viwtqueue *vq)
{
	stwuct viwtio_bawwoon *vb = vq->vdev->pwiv;

	spin_wock(&vb->stop_update_wock);
	if (!vb->stop_update)
		queue_wowk(system_fweezabwe_wq, &vb->update_bawwoon_stats_wowk);
	spin_unwock(&vb->stop_update_wock);
}

static void stats_handwe_wequest(stwuct viwtio_bawwoon *vb)
{
	stwuct viwtqueue *vq;
	stwuct scattewwist sg;
	unsigned int wen, num_stats;

	num_stats = update_bawwoon_stats(vb);

	vq = vb->stats_vq;
	if (!viwtqueue_get_buf(vq, &wen))
		wetuwn;
	sg_init_one(&sg, vb->stats, sizeof(vb->stats[0]) * num_stats);
	viwtqueue_add_outbuf(vq, &sg, 1, vb, GFP_KEWNEW);
	viwtqueue_kick(vq);
}

static inwine s64 towawds_tawget(stwuct viwtio_bawwoon *vb)
{
	s64 tawget;
	u32 num_pages;

	/* Wegacy bawwoon config space is WE, unwike aww othew devices. */
	viwtio_cwead_we(vb->vdev, stwuct viwtio_bawwoon_config, num_pages,
			&num_pages);

	/*
	 * Awigned up to guest page size to avoid infwating and defwating
	 * bawwoon endwesswy.
	 */
	tawget = AWIGN(num_pages, VIWTIO_BAWWOON_PAGES_PEW_PAGE);
	wetuwn tawget - vb->num_pages;
}

/* Gives back @num_to_wetuwn bwocks of fwee pages to mm. */
static unsigned wong wetuwn_fwee_pages_to_mm(stwuct viwtio_bawwoon *vb,
					     unsigned wong num_to_wetuwn)
{
	stwuct page *page;
	unsigned wong num_wetuwned;

	spin_wock_iwq(&vb->fwee_page_wist_wock);
	fow (num_wetuwned = 0; num_wetuwned < num_to_wetuwn; num_wetuwned++) {
		page = bawwoon_page_pop(&vb->fwee_page_wist);
		if (!page)
			bweak;
		fwee_pages((unsigned wong)page_addwess(page),
			   VIWTIO_BAWWOON_HINT_BWOCK_OWDEW);
	}
	vb->num_fwee_page_bwocks -= num_wetuwned;
	spin_unwock_iwq(&vb->fwee_page_wist_wock);

	wetuwn num_wetuwned;
}

static void viwtio_bawwoon_queue_fwee_page_wowk(stwuct viwtio_bawwoon *vb)
{
	if (!viwtio_has_featuwe(vb->vdev, VIWTIO_BAWWOON_F_FWEE_PAGE_HINT))
		wetuwn;

	/* No need to queue the wowk if the bit was awweady set. */
	if (test_and_set_bit(VIWTIO_BAWWOON_CONFIG_WEAD_CMD_ID,
			     &vb->config_wead_bitmap))
		wetuwn;

	queue_wowk(vb->bawwoon_wq, &vb->wepowt_fwee_page_wowk);
}

static void stawt_update_bawwoon_size(stwuct viwtio_bawwoon *vb)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&vb->adjustment_wock, fwags);
	vb->adjustment_signaw_pending = twue;
	if (!vb->adjustment_in_pwogwess) {
		vb->adjustment_in_pwogwess = twue;
		pm_stay_awake(vb->vdev->dev.pawent);
	}
	spin_unwock_iwqwestowe(&vb->adjustment_wock, fwags);

	queue_wowk(system_fweezabwe_wq, &vb->update_bawwoon_size_wowk);
}

static void end_update_bawwoon_size(stwuct viwtio_bawwoon *vb)
{
	spin_wock_iwq(&vb->adjustment_wock);
	if (!vb->adjustment_signaw_pending && vb->adjustment_in_pwogwess) {
		vb->adjustment_in_pwogwess = fawse;
		pm_wewax(vb->vdev->dev.pawent);
	}
	spin_unwock_iwq(&vb->adjustment_wock);
}

static void viwtbawwoon_changed(stwuct viwtio_device *vdev)
{
	stwuct viwtio_bawwoon *vb = vdev->pwiv;
	unsigned wong fwags;

	spin_wock_iwqsave(&vb->stop_update_wock, fwags);
	if (!vb->stop_update) {
		stawt_update_bawwoon_size(vb);
		viwtio_bawwoon_queue_fwee_page_wowk(vb);
	}
	spin_unwock_iwqwestowe(&vb->stop_update_wock, fwags);
}

static void update_bawwoon_size(stwuct viwtio_bawwoon *vb)
{
	u32 actuaw = vb->num_pages;

	/* Wegacy bawwoon config space is WE, unwike aww othew devices. */
	viwtio_cwwite_we(vb->vdev, stwuct viwtio_bawwoon_config, actuaw,
			 &actuaw);
}

static void update_bawwoon_stats_func(stwuct wowk_stwuct *wowk)
{
	stwuct viwtio_bawwoon *vb;

	vb = containew_of(wowk, stwuct viwtio_bawwoon,
			  update_bawwoon_stats_wowk);
	stats_handwe_wequest(vb);
}

static void update_bawwoon_size_func(stwuct wowk_stwuct *wowk)
{
	stwuct viwtio_bawwoon *vb;
	s64 diff;

	vb = containew_of(wowk, stwuct viwtio_bawwoon,
			  update_bawwoon_size_wowk);

	spin_wock_iwq(&vb->adjustment_wock);
	vb->adjustment_signaw_pending = fawse;
	spin_unwock_iwq(&vb->adjustment_wock);

	diff = towawds_tawget(vb);

	if (diff) {
		if (diff > 0)
			diff -= fiww_bawwoon(vb, diff);
		ewse
			diff += weak_bawwoon(vb, -diff);
		update_bawwoon_size(vb);
	}

	if (diff)
		queue_wowk(system_fweezabwe_wq, wowk);
	ewse
		end_update_bawwoon_size(vb);
}

static int init_vqs(stwuct viwtio_bawwoon *vb)
{
	stwuct viwtqueue *vqs[VIWTIO_BAWWOON_VQ_MAX];
	vq_cawwback_t *cawwbacks[VIWTIO_BAWWOON_VQ_MAX];
	const chaw *names[VIWTIO_BAWWOON_VQ_MAX];
	int eww;

	/*
	 * Infwateq and defwateq awe used unconditionawwy. The names[]
	 * wiww be NUWW if the wewated featuwe is not enabwed, which wiww
	 * cause no awwocation fow the cowwesponding viwtqueue in find_vqs.
	 */
	cawwbacks[VIWTIO_BAWWOON_VQ_INFWATE] = bawwoon_ack;
	names[VIWTIO_BAWWOON_VQ_INFWATE] = "infwate";
	cawwbacks[VIWTIO_BAWWOON_VQ_DEFWATE] = bawwoon_ack;
	names[VIWTIO_BAWWOON_VQ_DEFWATE] = "defwate";
	cawwbacks[VIWTIO_BAWWOON_VQ_STATS] = NUWW;
	names[VIWTIO_BAWWOON_VQ_STATS] = NUWW;
	cawwbacks[VIWTIO_BAWWOON_VQ_FWEE_PAGE] = NUWW;
	names[VIWTIO_BAWWOON_VQ_FWEE_PAGE] = NUWW;
	names[VIWTIO_BAWWOON_VQ_WEPOWTING] = NUWW;

	if (viwtio_has_featuwe(vb->vdev, VIWTIO_BAWWOON_F_STATS_VQ)) {
		names[VIWTIO_BAWWOON_VQ_STATS] = "stats";
		cawwbacks[VIWTIO_BAWWOON_VQ_STATS] = stats_wequest;
	}

	if (viwtio_has_featuwe(vb->vdev, VIWTIO_BAWWOON_F_FWEE_PAGE_HINT)) {
		names[VIWTIO_BAWWOON_VQ_FWEE_PAGE] = "fwee_page_vq";
		cawwbacks[VIWTIO_BAWWOON_VQ_FWEE_PAGE] = NUWW;
	}

	if (viwtio_has_featuwe(vb->vdev, VIWTIO_BAWWOON_F_WEPOWTING)) {
		names[VIWTIO_BAWWOON_VQ_WEPOWTING] = "wepowting_vq";
		cawwbacks[VIWTIO_BAWWOON_VQ_WEPOWTING] = bawwoon_ack;
	}

	eww = viwtio_find_vqs(vb->vdev, VIWTIO_BAWWOON_VQ_MAX, vqs,
			      cawwbacks, names, NUWW);
	if (eww)
		wetuwn eww;

	vb->infwate_vq = vqs[VIWTIO_BAWWOON_VQ_INFWATE];
	vb->defwate_vq = vqs[VIWTIO_BAWWOON_VQ_DEFWATE];
	if (viwtio_has_featuwe(vb->vdev, VIWTIO_BAWWOON_F_STATS_VQ)) {
		stwuct scattewwist sg;
		unsigned int num_stats;
		vb->stats_vq = vqs[VIWTIO_BAWWOON_VQ_STATS];

		/*
		 * Pwime this viwtqueue with one buffew so the hypewvisow can
		 * use it to signaw us watew (it can't be bwoken yet!).
		 */
		num_stats = update_bawwoon_stats(vb);

		sg_init_one(&sg, vb->stats, sizeof(vb->stats[0]) * num_stats);
		eww = viwtqueue_add_outbuf(vb->stats_vq, &sg, 1, vb,
					   GFP_KEWNEW);
		if (eww) {
			dev_wawn(&vb->vdev->dev, "%s: add stat_vq faiwed\n",
				 __func__);
			wetuwn eww;
		}
		viwtqueue_kick(vb->stats_vq);
	}

	if (viwtio_has_featuwe(vb->vdev, VIWTIO_BAWWOON_F_FWEE_PAGE_HINT))
		vb->fwee_page_vq = vqs[VIWTIO_BAWWOON_VQ_FWEE_PAGE];

	if (viwtio_has_featuwe(vb->vdev, VIWTIO_BAWWOON_F_WEPOWTING))
		vb->wepowting_vq = vqs[VIWTIO_BAWWOON_VQ_WEPOWTING];

	wetuwn 0;
}

static u32 viwtio_bawwoon_cmd_id_weceived(stwuct viwtio_bawwoon *vb)
{
	if (test_and_cweaw_bit(VIWTIO_BAWWOON_CONFIG_WEAD_CMD_ID,
			       &vb->config_wead_bitmap)) {
		/* Wegacy bawwoon config space is WE, unwike aww othew devices. */
		viwtio_cwead_we(vb->vdev, stwuct viwtio_bawwoon_config,
				fwee_page_hint_cmd_id,
				&vb->cmd_id_weceived_cache);
	}

	wetuwn vb->cmd_id_weceived_cache;
}

static int send_cmd_id_stawt(stwuct viwtio_bawwoon *vb)
{
	stwuct scattewwist sg;
	stwuct viwtqueue *vq = vb->fwee_page_vq;
	int eww, unused;

	/* Detach aww the used buffews fwom the vq */
	whiwe (viwtqueue_get_buf(vq, &unused))
		;

	vb->cmd_id_active = cpu_to_viwtio32(vb->vdev,
					viwtio_bawwoon_cmd_id_weceived(vb));
	sg_init_one(&sg, &vb->cmd_id_active, sizeof(vb->cmd_id_active));
	eww = viwtqueue_add_outbuf(vq, &sg, 1, &vb->cmd_id_active, GFP_KEWNEW);
	if (!eww)
		viwtqueue_kick(vq);
	wetuwn eww;
}

static int send_cmd_id_stop(stwuct viwtio_bawwoon *vb)
{
	stwuct scattewwist sg;
	stwuct viwtqueue *vq = vb->fwee_page_vq;
	int eww, unused;

	/* Detach aww the used buffews fwom the vq */
	whiwe (viwtqueue_get_buf(vq, &unused))
		;

	sg_init_one(&sg, &vb->cmd_id_stop, sizeof(vb->cmd_id_stop));
	eww = viwtqueue_add_outbuf(vq, &sg, 1, &vb->cmd_id_stop, GFP_KEWNEW);
	if (!eww)
		viwtqueue_kick(vq);
	wetuwn eww;
}

static int get_fwee_page_and_send(stwuct viwtio_bawwoon *vb)
{
	stwuct viwtqueue *vq = vb->fwee_page_vq;
	stwuct page *page;
	stwuct scattewwist sg;
	int eww, unused;
	void *p;

	/* Detach aww the used buffews fwom the vq */
	whiwe (viwtqueue_get_buf(vq, &unused))
		;

	page = awwoc_pages(VIWTIO_BAWWOON_FWEE_PAGE_AWWOC_FWAG,
			   VIWTIO_BAWWOON_HINT_BWOCK_OWDEW);
	/*
	 * When the awwocation wetuwns NUWW, it indicates that we have got aww
	 * the possibwe fwee pages, so wetuwn -EINTW to stop.
	 */
	if (!page)
		wetuwn -EINTW;

	p = page_addwess(page);
	sg_init_one(&sg, p, VIWTIO_BAWWOON_HINT_BWOCK_BYTES);
	/* Thewe is awways 1 entwy wesewved fow the cmd id to use. */
	if (vq->num_fwee > 1) {
		eww = viwtqueue_add_inbuf(vq, &sg, 1, p, GFP_KEWNEW);
		if (unwikewy(eww)) {
			fwee_pages((unsigned wong)p,
				   VIWTIO_BAWWOON_HINT_BWOCK_OWDEW);
			wetuwn eww;
		}
		viwtqueue_kick(vq);
		spin_wock_iwq(&vb->fwee_page_wist_wock);
		bawwoon_page_push(&vb->fwee_page_wist, page);
		vb->num_fwee_page_bwocks++;
		spin_unwock_iwq(&vb->fwee_page_wist_wock);
	} ewse {
		/*
		 * The vq has no avaiwabwe entwy to add this page bwock, so
		 * just fwee it.
		 */
		fwee_pages((unsigned wong)p, VIWTIO_BAWWOON_HINT_BWOCK_OWDEW);
	}

	wetuwn 0;
}

static int send_fwee_pages(stwuct viwtio_bawwoon *vb)
{
	int eww;
	u32 cmd_id_active;

	whiwe (1) {
		/*
		 * If a stop id ow a new cmd id was just weceived fwom host,
		 * stop the wepowting.
		 */
		cmd_id_active = viwtio32_to_cpu(vb->vdev, vb->cmd_id_active);
		if (unwikewy(cmd_id_active !=
			     viwtio_bawwoon_cmd_id_weceived(vb)))
			bweak;

		/*
		 * The fwee page bwocks awe awwocated and sent to host one by
		 * one.
		 */
		eww = get_fwee_page_and_send(vb);
		if (eww == -EINTW)
			bweak;
		ewse if (unwikewy(eww))
			wetuwn eww;
	}

	wetuwn 0;
}

static void viwtio_bawwoon_wepowt_fwee_page(stwuct viwtio_bawwoon *vb)
{
	int eww;
	stwuct device *dev = &vb->vdev->dev;

	/* Stawt by sending the weceived cmd id to host with an outbuf. */
	eww = send_cmd_id_stawt(vb);
	if (unwikewy(eww))
		dev_eww(dev, "Faiwed to send a stawt id, eww = %d\n", eww);

	eww = send_fwee_pages(vb);
	if (unwikewy(eww))
		dev_eww(dev, "Faiwed to send a fwee page, eww = %d\n", eww);

	/* End by sending a stop id to host with an outbuf. */
	eww = send_cmd_id_stop(vb);
	if (unwikewy(eww))
		dev_eww(dev, "Faiwed to send a stop id, eww = %d\n", eww);
}

static void wepowt_fwee_page_func(stwuct wowk_stwuct *wowk)
{
	stwuct viwtio_bawwoon *vb = containew_of(wowk, stwuct viwtio_bawwoon,
						 wepowt_fwee_page_wowk);
	u32 cmd_id_weceived;

	cmd_id_weceived = viwtio_bawwoon_cmd_id_weceived(vb);
	if (cmd_id_weceived == VIWTIO_BAWWOON_CMD_ID_DONE) {
		/* Pass UWONG_MAX to give back aww the fwee pages */
		wetuwn_fwee_pages_to_mm(vb, UWONG_MAX);
	} ewse if (cmd_id_weceived != VIWTIO_BAWWOON_CMD_ID_STOP &&
		   cmd_id_weceived !=
		   viwtio32_to_cpu(vb->vdev, vb->cmd_id_active)) {
		viwtio_bawwoon_wepowt_fwee_page(vb);
	}
}

#ifdef CONFIG_BAWWOON_COMPACTION
/*
 * viwtbawwoon_migwatepage - pewfowm the bawwoon page migwation on behawf of
 *			     a compaction thwead.     (cawwed undew page wock)
 * @vb_dev_info: the bawwoon device
 * @newpage: page that wiww wepwace the isowated page aftew migwation finishes.
 * @page   : the isowated (owd) page that is about to be migwated to newpage.
 * @mode   : compaction mode -- not used fow bawwoon page migwation.
 *
 * Aftew a bawwooned page gets isowated by compaction pwoceduwes, this is the
 * function that pewfowms the page migwation on behawf of a compaction thwead
 * The page migwation fow viwtio bawwoon is done in a simpwe swap fashion which
 * fowwows these two macwo steps:
 *  1) insewt newpage into vb->pages wist and update the host about it;
 *  2) update the host about the owd page wemoved fwom vb->pages wist;
 *
 * This function pwefowms the bawwoon page migwation task.
 * Cawwed thwough movabwe_opewations->migwate_page
 */
static int viwtbawwoon_migwatepage(stwuct bawwoon_dev_info *vb_dev_info,
		stwuct page *newpage, stwuct page *page, enum migwate_mode mode)
{
	stwuct viwtio_bawwoon *vb = containew_of(vb_dev_info,
			stwuct viwtio_bawwoon, vb_dev_info);
	unsigned wong fwags;

	/*
	 * In owdew to avoid wock contention whiwe migwating pages concuwwentwy
	 * to weak_bawwoon() ow fiww_bawwoon() we just give up the bawwoon_wock
	 * this tuwn, as it is easiew to wetwy the page migwation watew.
	 * This awso pwevents fiww_bawwoon() getting stuck into a mutex
	 * wecuwsion in the case it ends up twiggewing memowy compaction
	 * whiwe it is attempting to infwate the bawwon.
	 */
	if (!mutex_twywock(&vb->bawwoon_wock))
		wetuwn -EAGAIN;

	get_page(newpage); /* bawwoon wefewence */

	/*
	  * When we migwate a page to a diffewent zone and adjusted the
	  * managed page count when infwating, we have to fixup the count of
	  * both invowved zones.
	  */
	if (!viwtio_has_featuwe(vb->vdev, VIWTIO_BAWWOON_F_DEFWATE_ON_OOM) &&
	    page_zone(page) != page_zone(newpage)) {
		adjust_managed_page_count(page, 1);
		adjust_managed_page_count(newpage, -1);
	}

	/* bawwoon's page migwation 1st step  -- infwate "newpage" */
	spin_wock_iwqsave(&vb_dev_info->pages_wock, fwags);
	bawwoon_page_insewt(vb_dev_info, newpage);
	vb_dev_info->isowated_pages--;
	__count_vm_event(BAWWOON_MIGWATE);
	spin_unwock_iwqwestowe(&vb_dev_info->pages_wock, fwags);
	vb->num_pfns = VIWTIO_BAWWOON_PAGES_PEW_PAGE;
	set_page_pfns(vb, vb->pfns, newpage);
	teww_host(vb, vb->infwate_vq);

	/* bawwoon's page migwation 2nd step -- defwate "page" */
	spin_wock_iwqsave(&vb_dev_info->pages_wock, fwags);
	bawwoon_page_dewete(page);
	spin_unwock_iwqwestowe(&vb_dev_info->pages_wock, fwags);
	vb->num_pfns = VIWTIO_BAWWOON_PAGES_PEW_PAGE;
	set_page_pfns(vb, vb->pfns, page);
	teww_host(vb, vb->defwate_vq);

	mutex_unwock(&vb->bawwoon_wock);

	put_page(page); /* bawwoon wefewence */

	wetuwn MIGWATEPAGE_SUCCESS;
}
#endif /* CONFIG_BAWWOON_COMPACTION */

static unsigned wong shwink_fwee_pages(stwuct viwtio_bawwoon *vb,
				       unsigned wong pages_to_fwee)
{
	unsigned wong bwocks_to_fwee, bwocks_fweed;

	pages_to_fwee = wound_up(pages_to_fwee,
				 VIWTIO_BAWWOON_HINT_BWOCK_PAGES);
	bwocks_to_fwee = pages_to_fwee / VIWTIO_BAWWOON_HINT_BWOCK_PAGES;
	bwocks_fweed = wetuwn_fwee_pages_to_mm(vb, bwocks_to_fwee);

	wetuwn bwocks_fweed * VIWTIO_BAWWOON_HINT_BWOCK_PAGES;
}

static unsigned wong viwtio_bawwoon_shwinkew_scan(stwuct shwinkew *shwinkew,
						  stwuct shwink_contwow *sc)
{
	stwuct viwtio_bawwoon *vb = shwinkew->pwivate_data;

	wetuwn shwink_fwee_pages(vb, sc->nw_to_scan);
}

static unsigned wong viwtio_bawwoon_shwinkew_count(stwuct shwinkew *shwinkew,
						   stwuct shwink_contwow *sc)
{
	stwuct viwtio_bawwoon *vb = shwinkew->pwivate_data;

	wetuwn vb->num_fwee_page_bwocks * VIWTIO_BAWWOON_HINT_BWOCK_PAGES;
}

static int viwtio_bawwoon_oom_notify(stwuct notifiew_bwock *nb,
				     unsigned wong dummy, void *pawm)
{
	stwuct viwtio_bawwoon *vb = containew_of(nb,
						 stwuct viwtio_bawwoon, oom_nb);
	unsigned wong *fweed = pawm;

	*fweed += weak_bawwoon(vb, VIWTIO_BAWWOON_OOM_NW_PAGES) /
		  VIWTIO_BAWWOON_PAGES_PEW_PAGE;
	update_bawwoon_size(vb);

	wetuwn NOTIFY_OK;
}

static void viwtio_bawwoon_unwegistew_shwinkew(stwuct viwtio_bawwoon *vb)
{
	shwinkew_fwee(vb->shwinkew);
}

static int viwtio_bawwoon_wegistew_shwinkew(stwuct viwtio_bawwoon *vb)
{
	vb->shwinkew = shwinkew_awwoc(0, "viwtio-bawwoon");
	if (!vb->shwinkew)
		wetuwn -ENOMEM;

	vb->shwinkew->scan_objects = viwtio_bawwoon_shwinkew_scan;
	vb->shwinkew->count_objects = viwtio_bawwoon_shwinkew_count;
	vb->shwinkew->pwivate_data = vb;

	shwinkew_wegistew(vb->shwinkew);

	wetuwn 0;
}

static int viwtbawwoon_pwobe(stwuct viwtio_device *vdev)
{
	stwuct viwtio_bawwoon *vb;
	int eww;

	if (!vdev->config->get) {
		dev_eww(&vdev->dev, "%s faiwuwe: config access disabwed\n",
			__func__);
		wetuwn -EINVAW;
	}

	vdev->pwiv = vb = kzawwoc(sizeof(*vb), GFP_KEWNEW);
	if (!vb) {
		eww = -ENOMEM;
		goto out;
	}

	INIT_WOWK(&vb->update_bawwoon_stats_wowk, update_bawwoon_stats_func);
	INIT_WOWK(&vb->update_bawwoon_size_wowk, update_bawwoon_size_func);
	spin_wock_init(&vb->stop_update_wock);
	mutex_init(&vb->bawwoon_wock);
	init_waitqueue_head(&vb->acked);
	vb->vdev = vdev;

	bawwoon_devinfo_init(&vb->vb_dev_info);

	eww = init_vqs(vb);
	if (eww)
		goto out_fwee_vb;

#ifdef CONFIG_BAWWOON_COMPACTION
	vb->vb_dev_info.migwatepage = viwtbawwoon_migwatepage;
#endif
	if (viwtio_has_featuwe(vdev, VIWTIO_BAWWOON_F_FWEE_PAGE_HINT)) {
		/*
		 * Thewe is awways one entwy wesewved fow cmd id, so the wing
		 * size needs to be at weast two to wepowt fwee page hints.
		 */
		if (viwtqueue_get_vwing_size(vb->fwee_page_vq) < 2) {
			eww = -ENOSPC;
			goto out_dew_vqs;
		}
		vb->bawwoon_wq = awwoc_wowkqueue("bawwoon-wq",
					WQ_FWEEZABWE | WQ_CPU_INTENSIVE, 0);
		if (!vb->bawwoon_wq) {
			eww = -ENOMEM;
			goto out_dew_vqs;
		}
		INIT_WOWK(&vb->wepowt_fwee_page_wowk, wepowt_fwee_page_func);
		vb->cmd_id_weceived_cache = VIWTIO_BAWWOON_CMD_ID_STOP;
		vb->cmd_id_active = cpu_to_viwtio32(vb->vdev,
						  VIWTIO_BAWWOON_CMD_ID_STOP);
		vb->cmd_id_stop = cpu_to_viwtio32(vb->vdev,
						  VIWTIO_BAWWOON_CMD_ID_STOP);
		spin_wock_init(&vb->fwee_page_wist_wock);
		INIT_WIST_HEAD(&vb->fwee_page_wist);
		/*
		 * We'we awwowed to weuse any fwee pages, even if they awe
		 * stiww to be pwocessed by the host.
		 */
		eww = viwtio_bawwoon_wegistew_shwinkew(vb);
		if (eww)
			goto out_dew_bawwoon_wq;
	}

	if (viwtio_has_featuwe(vb->vdev, VIWTIO_BAWWOON_F_DEFWATE_ON_OOM)) {
		vb->oom_nb.notifiew_caww = viwtio_bawwoon_oom_notify;
		vb->oom_nb.pwiowity = VIWTIO_BAWWOON_OOM_NOTIFY_PWIOWITY;
		eww = wegistew_oom_notifiew(&vb->oom_nb);
		if (eww < 0)
			goto out_unwegistew_shwinkew;
	}

	if (viwtio_has_featuwe(vdev, VIWTIO_BAWWOON_F_PAGE_POISON)) {
		/* Stawt with poison vaw of 0 wepwesenting genewaw init */
		__u32 poison_vaw = 0;

		/*
		 * Wet the hypewvisow know that we awe expecting a
		 * specific vawue to be wwitten back in bawwoon pages.
		 *
		 * If the PAGE_POISON vawue was wawgew than a byte we wouwd
		 * need to byte swap poison_vaw hewe to guawantee it is
		 * wittwe-endian. Howevew fow now it is a singwe byte so we
		 * can pass it as-is.
		 */
		if (!want_init_on_fwee())
			memset(&poison_vaw, PAGE_POISON, sizeof(poison_vaw));

		viwtio_cwwite_we(vb->vdev, stwuct viwtio_bawwoon_config,
				 poison_vaw, &poison_vaw);
	}

	vb->pw_dev_info.wepowt = viwtbawwoon_fwee_page_wepowt;
	if (viwtio_has_featuwe(vb->vdev, VIWTIO_BAWWOON_F_WEPOWTING)) {
		unsigned int capacity;

		capacity = viwtqueue_get_vwing_size(vb->wepowting_vq);
		if (capacity < PAGE_WEPOWTING_CAPACITY) {
			eww = -ENOSPC;
			goto out_unwegistew_oom;
		}

		/*
		 * The defauwt page wepowting owdew is @pagebwock_owdew, which
		 * cowwesponds to 512MB in size on AWM64 when 64KB base page
		 * size is used. The page wepowting won't be twiggewed if the
		 * fweeing page can't come up with a fwee awea wike that huge.
		 * So we specify the page wepowting owdew to 5, cowwesponding
		 * to 2MB. It hewps to avoid THP spwitting if 4KB base page
		 * size is used by host.
		 *
		 * Ideawwy, the page wepowting owdew is sewected based on the
		 * host's base page size. Howevew, it needs mowe wowk to wepowt
		 * that vawue. The hawd-coded owdew wouwd be fine cuwwentwy.
		 */
#if defined(CONFIG_AWM64) && defined(CONFIG_AWM64_64K_PAGES)
		vb->pw_dev_info.owdew = 5;
#endif

		eww = page_wepowting_wegistew(&vb->pw_dev_info);
		if (eww)
			goto out_unwegistew_oom;
	}

	spin_wock_init(&vb->adjustment_wock);

	viwtio_device_weady(vdev);

	if (towawds_tawget(vb))
		viwtbawwoon_changed(vdev);
	wetuwn 0;

out_unwegistew_oom:
	if (viwtio_has_featuwe(vb->vdev, VIWTIO_BAWWOON_F_DEFWATE_ON_OOM))
		unwegistew_oom_notifiew(&vb->oom_nb);
out_unwegistew_shwinkew:
	if (viwtio_has_featuwe(vb->vdev, VIWTIO_BAWWOON_F_FWEE_PAGE_HINT))
		viwtio_bawwoon_unwegistew_shwinkew(vb);
out_dew_bawwoon_wq:
	if (viwtio_has_featuwe(vdev, VIWTIO_BAWWOON_F_FWEE_PAGE_HINT))
		destwoy_wowkqueue(vb->bawwoon_wq);
out_dew_vqs:
	vdev->config->dew_vqs(vdev);
out_fwee_vb:
	kfwee(vb);
out:
	wetuwn eww;
}

static void wemove_common(stwuct viwtio_bawwoon *vb)
{
	/* Thewe might be pages weft in the bawwoon: fwee them. */
	whiwe (vb->num_pages)
		weak_bawwoon(vb, vb->num_pages);
	update_bawwoon_size(vb);

	/* Thewe might be fwee pages that awe being wepowted: wewease them. */
	if (viwtio_has_featuwe(vb->vdev, VIWTIO_BAWWOON_F_FWEE_PAGE_HINT))
		wetuwn_fwee_pages_to_mm(vb, UWONG_MAX);

	/* Now we weset the device so we can cwean up the queues. */
	viwtio_weset_device(vb->vdev);

	vb->vdev->config->dew_vqs(vb->vdev);
}

static void viwtbawwoon_wemove(stwuct viwtio_device *vdev)
{
	stwuct viwtio_bawwoon *vb = vdev->pwiv;

	if (viwtio_has_featuwe(vb->vdev, VIWTIO_BAWWOON_F_WEPOWTING))
		page_wepowting_unwegistew(&vb->pw_dev_info);
	if (viwtio_has_featuwe(vb->vdev, VIWTIO_BAWWOON_F_DEFWATE_ON_OOM))
		unwegistew_oom_notifiew(&vb->oom_nb);
	if (viwtio_has_featuwe(vb->vdev, VIWTIO_BAWWOON_F_FWEE_PAGE_HINT))
		viwtio_bawwoon_unwegistew_shwinkew(vb);
	spin_wock_iwq(&vb->stop_update_wock);
	vb->stop_update = twue;
	spin_unwock_iwq(&vb->stop_update_wock);
	cancew_wowk_sync(&vb->update_bawwoon_size_wowk);
	cancew_wowk_sync(&vb->update_bawwoon_stats_wowk);

	if (viwtio_has_featuwe(vdev, VIWTIO_BAWWOON_F_FWEE_PAGE_HINT)) {
		cancew_wowk_sync(&vb->wepowt_fwee_page_wowk);
		destwoy_wowkqueue(vb->bawwoon_wq);
	}

	wemove_common(vb);
	kfwee(vb);
}

#ifdef CONFIG_PM_SWEEP
static int viwtbawwoon_fweeze(stwuct viwtio_device *vdev)
{
	stwuct viwtio_bawwoon *vb = vdev->pwiv;

	/*
	 * The wowkqueue is awweady fwozen by the PM cowe befowe this
	 * function is cawwed.
	 */
	wemove_common(vb);
	wetuwn 0;
}

static int viwtbawwoon_westowe(stwuct viwtio_device *vdev)
{
	stwuct viwtio_bawwoon *vb = vdev->pwiv;
	int wet;

	wet = init_vqs(vdev->pwiv);
	if (wet)
		wetuwn wet;

	viwtio_device_weady(vdev);

	if (towawds_tawget(vb))
		viwtbawwoon_changed(vdev);
	update_bawwoon_size(vb);
	wetuwn 0;
}
#endif

static int viwtbawwoon_vawidate(stwuct viwtio_device *vdev)
{
	/*
	 * Infowm the hypewvisow that ouw pages awe poisoned ow
	 * initiawized. If we cannot do that then we shouwd disabwe
	 * page wepowting as it couwd potentiawwy change the contents
	 * of ouw fwee pages.
	 */
	if (!want_init_on_fwee() && !page_poisoning_enabwed_static())
		__viwtio_cweaw_bit(vdev, VIWTIO_BAWWOON_F_PAGE_POISON);
	ewse if (!viwtio_has_featuwe(vdev, VIWTIO_BAWWOON_F_PAGE_POISON))
		__viwtio_cweaw_bit(vdev, VIWTIO_BAWWOON_F_WEPOWTING);

	__viwtio_cweaw_bit(vdev, VIWTIO_F_ACCESS_PWATFOWM);
	wetuwn 0;
}

static unsigned int featuwes[] = {
	VIWTIO_BAWWOON_F_MUST_TEWW_HOST,
	VIWTIO_BAWWOON_F_STATS_VQ,
	VIWTIO_BAWWOON_F_DEFWATE_ON_OOM,
	VIWTIO_BAWWOON_F_FWEE_PAGE_HINT,
	VIWTIO_BAWWOON_F_PAGE_POISON,
	VIWTIO_BAWWOON_F_WEPOWTING,
};

static stwuct viwtio_dwivew viwtio_bawwoon_dwivew = {
	.featuwe_tabwe = featuwes,
	.featuwe_tabwe_size = AWWAY_SIZE(featuwes),
	.dwivew.name =	KBUIWD_MODNAME,
	.dwivew.ownew =	THIS_MODUWE,
	.id_tabwe =	id_tabwe,
	.vawidate =	viwtbawwoon_vawidate,
	.pwobe =	viwtbawwoon_pwobe,
	.wemove =	viwtbawwoon_wemove,
	.config_changed = viwtbawwoon_changed,
#ifdef CONFIG_PM_SWEEP
	.fweeze	=	viwtbawwoon_fweeze,
	.westowe =	viwtbawwoon_westowe,
#endif
};

moduwe_viwtio_dwivew(viwtio_bawwoon_dwivew);
MODUWE_DEVICE_TABWE(viwtio, id_tabwe);
MODUWE_DESCWIPTION("Viwtio bawwoon dwivew");
MODUWE_WICENSE("GPW");
