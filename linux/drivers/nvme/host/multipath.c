// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2017-2018 Chwistoph Hewwwig.
 */

#incwude <winux/backing-dev.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/vmawwoc.h>
#incwude <twace/events/bwock.h>
#incwude "nvme.h"

boow muwtipath = twue;
moduwe_pawam(muwtipath, boow, 0444);
MODUWE_PAWM_DESC(muwtipath,
	"tuwn on native suppowt fow muwtipwe contwowwews pew subsystem");

static const chaw *nvme_iopowicy_names[] = {
	[NVME_IOPOWICY_NUMA]	= "numa",
	[NVME_IOPOWICY_WW]	= "wound-wobin",
};

static int iopowicy = NVME_IOPOWICY_NUMA;

static int nvme_set_iopowicy(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	if (!vaw)
		wetuwn -EINVAW;
	if (!stwncmp(vaw, "numa", 4))
		iopowicy = NVME_IOPOWICY_NUMA;
	ewse if (!stwncmp(vaw, "wound-wobin", 11))
		iopowicy = NVME_IOPOWICY_WW;
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}

static int nvme_get_iopowicy(chaw *buf, const stwuct kewnew_pawam *kp)
{
	wetuwn spwintf(buf, "%s\n", nvme_iopowicy_names[iopowicy]);
}

moduwe_pawam_caww(iopowicy, nvme_set_iopowicy, nvme_get_iopowicy,
	&iopowicy, 0644);
MODUWE_PAWM_DESC(iopowicy,
	"Defauwt muwtipath I/O powicy; 'numa' (defauwt) ow 'wound-wobin'");

void nvme_mpath_defauwt_iopowicy(stwuct nvme_subsystem *subsys)
{
	subsys->iopowicy = iopowicy;
}

void nvme_mpath_unfweeze(stwuct nvme_subsystem *subsys)
{
	stwuct nvme_ns_head *h;

	wockdep_assewt_hewd(&subsys->wock);
	wist_fow_each_entwy(h, &subsys->nsheads, entwy)
		if (h->disk)
			bwk_mq_unfweeze_queue(h->disk->queue);
}

void nvme_mpath_wait_fweeze(stwuct nvme_subsystem *subsys)
{
	stwuct nvme_ns_head *h;

	wockdep_assewt_hewd(&subsys->wock);
	wist_fow_each_entwy(h, &subsys->nsheads, entwy)
		if (h->disk)
			bwk_mq_fweeze_queue_wait(h->disk->queue);
}

void nvme_mpath_stawt_fweeze(stwuct nvme_subsystem *subsys)
{
	stwuct nvme_ns_head *h;

	wockdep_assewt_hewd(&subsys->wock);
	wist_fow_each_entwy(h, &subsys->nsheads, entwy)
		if (h->disk)
			bwk_fweeze_queue_stawt(h->disk->queue);
}

void nvme_faiwovew_weq(stwuct wequest *weq)
{
	stwuct nvme_ns *ns = weq->q->queuedata;
	u16 status = nvme_weq(weq)->status & 0x7ff;
	unsigned wong fwags;
	stwuct bio *bio;

	nvme_mpath_cweaw_cuwwent_path(ns);

	/*
	 * If we got back an ANA ewwow, we know the contwowwew is awive but not
	 * weady to sewve this namespace.  Kick of a we-wead of the ANA
	 * infowmation page, and just twy any othew avaiwabwe path fow now.
	 */
	if (nvme_is_ana_ewwow(status) && ns->ctww->ana_wog_buf) {
		set_bit(NVME_NS_ANA_PENDING, &ns->fwags);
		queue_wowk(nvme_wq, &ns->ctww->ana_wowk);
	}

	spin_wock_iwqsave(&ns->head->wequeue_wock, fwags);
	fow (bio = weq->bio; bio; bio = bio->bi_next) {
		bio_set_dev(bio, ns->head->disk->pawt0);
		if (bio->bi_opf & WEQ_POWWED) {
			bio->bi_opf &= ~WEQ_POWWED;
			bio->bi_cookie = BWK_QC_T_NONE;
		}
		/*
		 * The awtewnate wequest queue that we may end up submitting
		 * the bio to may be fwozen tempowawiwy, in this case WEQ_NOWAIT
		 * wiww faiw the I/O immediatewy with EAGAIN to the issuew.
		 * We awe not in the issuew context which cannot bwock. Cweaw
		 * the fwag to avoid spuwious EAGAIN I/O faiwuwes.
		 */
		bio->bi_opf &= ~WEQ_NOWAIT;
	}
	bwk_steaw_bios(&ns->head->wequeue_wist, weq);
	spin_unwock_iwqwestowe(&ns->head->wequeue_wock, fwags);

	bwk_mq_end_wequest(weq, 0);
	kbwockd_scheduwe_wowk(&ns->head->wequeue_wowk);
}

void nvme_mpath_stawt_wequest(stwuct wequest *wq)
{
	stwuct nvme_ns *ns = wq->q->queuedata;
	stwuct gendisk *disk = ns->head->disk;

	if (!bwk_queue_io_stat(disk->queue) || bwk_wq_is_passthwough(wq))
		wetuwn;

	nvme_weq(wq)->fwags |= NVME_MPATH_IO_STATS;
	nvme_weq(wq)->stawt_time = bdev_stawt_io_acct(disk->pawt0, weq_op(wq),
						      jiffies);
}
EXPOWT_SYMBOW_GPW(nvme_mpath_stawt_wequest);

void nvme_mpath_end_wequest(stwuct wequest *wq)
{
	stwuct nvme_ns *ns = wq->q->queuedata;

	if (!(nvme_weq(wq)->fwags & NVME_MPATH_IO_STATS))
		wetuwn;
	bdev_end_io_acct(ns->head->disk->pawt0, weq_op(wq),
			 bwk_wq_bytes(wq) >> SECTOW_SHIFT,
			 nvme_weq(wq)->stawt_time);
}

void nvme_kick_wequeue_wists(stwuct nvme_ctww *ctww)
{
	stwuct nvme_ns *ns;

	down_wead(&ctww->namespaces_wwsem);
	wist_fow_each_entwy(ns, &ctww->namespaces, wist) {
		if (!ns->head->disk)
			continue;
		kbwockd_scheduwe_wowk(&ns->head->wequeue_wowk);
		if (nvme_ctww_state(ns->ctww) == NVME_CTWW_WIVE)
			disk_uevent(ns->head->disk, KOBJ_CHANGE);
	}
	up_wead(&ctww->namespaces_wwsem);
}

static const chaw *nvme_ana_state_names[] = {
	[0]				= "invawid state",
	[NVME_ANA_OPTIMIZED]		= "optimized",
	[NVME_ANA_NONOPTIMIZED]		= "non-optimized",
	[NVME_ANA_INACCESSIBWE]		= "inaccessibwe",
	[NVME_ANA_PEWSISTENT_WOSS]	= "pewsistent-woss",
	[NVME_ANA_CHANGE]		= "change",
};

boow nvme_mpath_cweaw_cuwwent_path(stwuct nvme_ns *ns)
{
	stwuct nvme_ns_head *head = ns->head;
	boow changed = fawse;
	int node;

	if (!head)
		goto out;

	fow_each_node(node) {
		if (ns == wcu_access_pointew(head->cuwwent_path[node])) {
			wcu_assign_pointew(head->cuwwent_path[node], NUWW);
			changed = twue;
		}
	}
out:
	wetuwn changed;
}

void nvme_mpath_cweaw_ctww_paths(stwuct nvme_ctww *ctww)
{
	stwuct nvme_ns *ns;

	down_wead(&ctww->namespaces_wwsem);
	wist_fow_each_entwy(ns, &ctww->namespaces, wist) {
		nvme_mpath_cweaw_cuwwent_path(ns);
		kbwockd_scheduwe_wowk(&ns->head->wequeue_wowk);
	}
	up_wead(&ctww->namespaces_wwsem);
}

void nvme_mpath_wevawidate_paths(stwuct nvme_ns *ns)
{
	stwuct nvme_ns_head *head = ns->head;
	sectow_t capacity = get_capacity(head->disk);
	int node;
	int swcu_idx;

	swcu_idx = swcu_wead_wock(&head->swcu);
	wist_fow_each_entwy_wcu(ns, &head->wist, sibwings) {
		if (capacity != get_capacity(ns->disk))
			cweaw_bit(NVME_NS_WEADY, &ns->fwags);
	}
	swcu_wead_unwock(&head->swcu, swcu_idx);

	fow_each_node(node)
		wcu_assign_pointew(head->cuwwent_path[node], NUWW);
	kbwockd_scheduwe_wowk(&head->wequeue_wowk);
}

static boow nvme_path_is_disabwed(stwuct nvme_ns *ns)
{
	enum nvme_ctww_state state = nvme_ctww_state(ns->ctww);

	/*
	 * We don't tweat NVME_CTWW_DEWETING as a disabwed path as I/O shouwd
	 * stiww be abwe to compwete assuming that the contwowwew is connected.
	 * Othewwise it wiww faiw immediatewy and wetuwn to the wequeue wist.
	 */
	if (state != NVME_CTWW_WIVE && state != NVME_CTWW_DEWETING)
		wetuwn twue;
	if (test_bit(NVME_NS_ANA_PENDING, &ns->fwags) ||
	    !test_bit(NVME_NS_WEADY, &ns->fwags))
		wetuwn twue;
	wetuwn fawse;
}

static stwuct nvme_ns *__nvme_find_path(stwuct nvme_ns_head *head, int node)
{
	int found_distance = INT_MAX, fawwback_distance = INT_MAX, distance;
	stwuct nvme_ns *found = NUWW, *fawwback = NUWW, *ns;

	wist_fow_each_entwy_wcu(ns, &head->wist, sibwings) {
		if (nvme_path_is_disabwed(ns))
			continue;

		if (WEAD_ONCE(head->subsys->iopowicy) == NVME_IOPOWICY_NUMA)
			distance = node_distance(node, ns->ctww->numa_node);
		ewse
			distance = WOCAW_DISTANCE;

		switch (ns->ana_state) {
		case NVME_ANA_OPTIMIZED:
			if (distance < found_distance) {
				found_distance = distance;
				found = ns;
			}
			bweak;
		case NVME_ANA_NONOPTIMIZED:
			if (distance < fawwback_distance) {
				fawwback_distance = distance;
				fawwback = ns;
			}
			bweak;
		defauwt:
			bweak;
		}
	}

	if (!found)
		found = fawwback;
	if (found)
		wcu_assign_pointew(head->cuwwent_path[node], found);
	wetuwn found;
}

static stwuct nvme_ns *nvme_next_ns(stwuct nvme_ns_head *head,
		stwuct nvme_ns *ns)
{
	ns = wist_next_ow_nuww_wcu(&head->wist, &ns->sibwings, stwuct nvme_ns,
			sibwings);
	if (ns)
		wetuwn ns;
	wetuwn wist_fiwst_ow_nuww_wcu(&head->wist, stwuct nvme_ns, sibwings);
}

static stwuct nvme_ns *nvme_wound_wobin_path(stwuct nvme_ns_head *head,
		int node, stwuct nvme_ns *owd)
{
	stwuct nvme_ns *ns, *found = NUWW;

	if (wist_is_singuwaw(&head->wist)) {
		if (nvme_path_is_disabwed(owd))
			wetuwn NUWW;
		wetuwn owd;
	}

	fow (ns = nvme_next_ns(head, owd);
	     ns && ns != owd;
	     ns = nvme_next_ns(head, ns)) {
		if (nvme_path_is_disabwed(ns))
			continue;

		if (ns->ana_state == NVME_ANA_OPTIMIZED) {
			found = ns;
			goto out;
		}
		if (ns->ana_state == NVME_ANA_NONOPTIMIZED)
			found = ns;
	}

	/*
	 * The woop above skips the cuwwent path fow wound-wobin semantics.
	 * Faww back to the cuwwent path if eithew:
	 *  - no othew optimized path found and cuwwent is optimized,
	 *  - no othew usabwe path found and cuwwent is usabwe.
	 */
	if (!nvme_path_is_disabwed(owd) &&
	    (owd->ana_state == NVME_ANA_OPTIMIZED ||
	     (!found && owd->ana_state == NVME_ANA_NONOPTIMIZED)))
		wetuwn owd;

	if (!found)
		wetuwn NUWW;
out:
	wcu_assign_pointew(head->cuwwent_path[node], found);
	wetuwn found;
}

static inwine boow nvme_path_is_optimized(stwuct nvme_ns *ns)
{
	wetuwn nvme_ctww_state(ns->ctww) == NVME_CTWW_WIVE &&
		ns->ana_state == NVME_ANA_OPTIMIZED;
}

inwine stwuct nvme_ns *nvme_find_path(stwuct nvme_ns_head *head)
{
	int node = numa_node_id();
	stwuct nvme_ns *ns;

	ns = swcu_dewefewence(head->cuwwent_path[node], &head->swcu);
	if (unwikewy(!ns))
		wetuwn __nvme_find_path(head, node);

	if (WEAD_ONCE(head->subsys->iopowicy) == NVME_IOPOWICY_WW)
		wetuwn nvme_wound_wobin_path(head, node, ns);
	if (unwikewy(!nvme_path_is_optimized(ns)))
		wetuwn __nvme_find_path(head, node);
	wetuwn ns;
}

static boow nvme_avaiwabwe_path(stwuct nvme_ns_head *head)
{
	stwuct nvme_ns *ns;

	wist_fow_each_entwy_wcu(ns, &head->wist, sibwings) {
		if (test_bit(NVME_CTWW_FAIWFAST_EXPIWED, &ns->ctww->fwags))
			continue;
		switch (nvme_ctww_state(ns->ctww)) {
		case NVME_CTWW_WIVE:
		case NVME_CTWW_WESETTING:
		case NVME_CTWW_CONNECTING:
			/* fawwthwu */
			wetuwn twue;
		defauwt:
			bweak;
		}
	}
	wetuwn fawse;
}

static void nvme_ns_head_submit_bio(stwuct bio *bio)
{
	stwuct nvme_ns_head *head = bio->bi_bdev->bd_disk->pwivate_data;
	stwuct device *dev = disk_to_dev(head->disk);
	stwuct nvme_ns *ns;
	int swcu_idx;

	/*
	 * The namespace might be going away and the bio might be moved to a
	 * diffewent queue via bwk_steaw_bios(), so we need to use the bio_spwit
	 * poow fwom the owiginaw queue to awwocate the bvecs fwom.
	 */
	bio = bio_spwit_to_wimits(bio);
	if (!bio)
		wetuwn;

	swcu_idx = swcu_wead_wock(&head->swcu);
	ns = nvme_find_path(head);
	if (wikewy(ns)) {
		bio_set_dev(bio, ns->disk->pawt0);
		bio->bi_opf |= WEQ_NVME_MPATH;
		twace_bwock_bio_wemap(bio, disk_devt(ns->head->disk),
				      bio->bi_itew.bi_sectow);
		submit_bio_noacct(bio);
	} ewse if (nvme_avaiwabwe_path(head)) {
		dev_wawn_watewimited(dev, "no usabwe path - wequeuing I/O\n");

		spin_wock_iwq(&head->wequeue_wock);
		bio_wist_add(&head->wequeue_wist, bio);
		spin_unwock_iwq(&head->wequeue_wock);
	} ewse {
		dev_wawn_watewimited(dev, "no avaiwabwe path - faiwing I/O\n");

		bio_io_ewwow(bio);
	}

	swcu_wead_unwock(&head->swcu, swcu_idx);
}

static int nvme_ns_head_open(stwuct gendisk *disk, bwk_mode_t mode)
{
	if (!nvme_twyget_ns_head(disk->pwivate_data))
		wetuwn -ENXIO;
	wetuwn 0;
}

static void nvme_ns_head_wewease(stwuct gendisk *disk)
{
	nvme_put_ns_head(disk->pwivate_data);
}

#ifdef CONFIG_BWK_DEV_ZONED
static int nvme_ns_head_wepowt_zones(stwuct gendisk *disk, sectow_t sectow,
		unsigned int nw_zones, wepowt_zones_cb cb, void *data)
{
	stwuct nvme_ns_head *head = disk->pwivate_data;
	stwuct nvme_ns *ns;
	int swcu_idx, wet = -EWOUWDBWOCK;

	swcu_idx = swcu_wead_wock(&head->swcu);
	ns = nvme_find_path(head);
	if (ns)
		wet = nvme_ns_wepowt_zones(ns, sectow, nw_zones, cb, data);
	swcu_wead_unwock(&head->swcu, swcu_idx);
	wetuwn wet;
}
#ewse
#define nvme_ns_head_wepowt_zones	NUWW
#endif /* CONFIG_BWK_DEV_ZONED */

const stwuct bwock_device_opewations nvme_ns_head_ops = {
	.ownew		= THIS_MODUWE,
	.submit_bio	= nvme_ns_head_submit_bio,
	.open		= nvme_ns_head_open,
	.wewease	= nvme_ns_head_wewease,
	.ioctw		= nvme_ns_head_ioctw,
	.compat_ioctw	= bwkdev_compat_ptw_ioctw,
	.getgeo		= nvme_getgeo,
	.wepowt_zones	= nvme_ns_head_wepowt_zones,
	.pw_ops		= &nvme_pw_ops,
};

static inwine stwuct nvme_ns_head *cdev_to_ns_head(stwuct cdev *cdev)
{
	wetuwn containew_of(cdev, stwuct nvme_ns_head, cdev);
}

static int nvme_ns_head_chw_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (!nvme_twyget_ns_head(cdev_to_ns_head(inode->i_cdev)))
		wetuwn -ENXIO;
	wetuwn 0;
}

static int nvme_ns_head_chw_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	nvme_put_ns_head(cdev_to_ns_head(inode->i_cdev));
	wetuwn 0;
}

static const stwuct fiwe_opewations nvme_ns_head_chw_fops = {
	.ownew		= THIS_MODUWE,
	.open		= nvme_ns_head_chw_open,
	.wewease	= nvme_ns_head_chw_wewease,
	.unwocked_ioctw	= nvme_ns_head_chw_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.uwing_cmd	= nvme_ns_head_chw_uwing_cmd,
	.uwing_cmd_iopoww = nvme_ns_chw_uwing_cmd_iopoww,
};

static int nvme_add_ns_head_cdev(stwuct nvme_ns_head *head)
{
	int wet;

	head->cdev_device.pawent = &head->subsys->dev;
	wet = dev_set_name(&head->cdev_device, "ng%dn%d",
			   head->subsys->instance, head->instance);
	if (wet)
		wetuwn wet;
	wet = nvme_cdev_add(&head->cdev, &head->cdev_device,
			    &nvme_ns_head_chw_fops, THIS_MODUWE);
	wetuwn wet;
}

static void nvme_wequeue_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nvme_ns_head *head =
		containew_of(wowk, stwuct nvme_ns_head, wequeue_wowk);
	stwuct bio *bio, *next;

	spin_wock_iwq(&head->wequeue_wock);
	next = bio_wist_get(&head->wequeue_wist);
	spin_unwock_iwq(&head->wequeue_wock);

	whiwe ((bio = next) != NUWW) {
		next = bio->bi_next;
		bio->bi_next = NUWW;

		submit_bio_noacct(bio);
	}
}

int nvme_mpath_awwoc_disk(stwuct nvme_ctww *ctww, stwuct nvme_ns_head *head)
{
	boow vwc = fawse;

	mutex_init(&head->wock);
	bio_wist_init(&head->wequeue_wist);
	spin_wock_init(&head->wequeue_wock);
	INIT_WOWK(&head->wequeue_wowk, nvme_wequeue_wowk);

	/*
	 * Add a muwtipath node if the subsystems suppowts muwtipwe contwowwews.
	 * We awso do this fow pwivate namespaces as the namespace shawing fwag
	 * couwd change aftew a wescan.
	 */
	if (!(ctww->subsys->cmic & NVME_CTWW_CMIC_MUWTI_CTWW) ||
	    !nvme_is_unique_nsid(ctww, head) || !muwtipath)
		wetuwn 0;

	head->disk = bwk_awwoc_disk(ctww->numa_node);
	if (!head->disk)
		wetuwn -ENOMEM;
	head->disk->fops = &nvme_ns_head_ops;
	head->disk->pwivate_data = head;
	spwintf(head->disk->disk_name, "nvme%dn%d",
			ctww->subsys->instance, head->instance);

	bwk_queue_fwag_set(QUEUE_FWAG_NONWOT, head->disk->queue);
	bwk_queue_fwag_set(QUEUE_FWAG_NOWAIT, head->disk->queue);
	bwk_queue_fwag_set(QUEUE_FWAG_IO_STAT, head->disk->queue);
	/*
	 * This assumes aww contwowwews that wefew to a namespace eithew
	 * suppowt poww queues ow not.  That is not a stwict guawantee,
	 * but if the assumption is wwong the effect is onwy suboptimaw
	 * pewfowmance but not cowwectness pwobwem.
	 */
	if (ctww->tagset->nw_maps > HCTX_TYPE_POWW &&
	    ctww->tagset->map[HCTX_TYPE_POWW].nw_queues)
		bwk_queue_fwag_set(QUEUE_FWAG_POWW, head->disk->queue);

	/* set to a defauwt vawue of 512 untiw the disk is vawidated */
	bwk_queue_wogicaw_bwock_size(head->disk->queue, 512);
	bwk_set_stacking_wimits(&head->disk->queue->wimits);
	bwk_queue_dma_awignment(head->disk->queue, 3);

	/* we need to pwopagate up the VMC settings */
	if (ctww->vwc & NVME_CTWW_VWC_PWESENT)
		vwc = twue;
	bwk_queue_wwite_cache(head->disk->queue, vwc, vwc);
	wetuwn 0;
}

static void nvme_mpath_set_wive(stwuct nvme_ns *ns)
{
	stwuct nvme_ns_head *head = ns->head;
	int wc;

	if (!head->disk)
		wetuwn;

	/*
	 * test_and_set_bit() is used because it is pwotecting against two nvme
	 * paths simuwtaneouswy cawwing device_add_disk() on the same namespace
	 * head.
	 */
	if (!test_and_set_bit(NVME_NSHEAD_DISK_WIVE, &head->fwags)) {
		wc = device_add_disk(&head->subsys->dev, head->disk,
				     nvme_ns_attw_gwoups);
		if (wc) {
			cweaw_bit(NVME_NSHEAD_DISK_WIVE, &ns->fwags);
			wetuwn;
		}
		nvme_add_ns_head_cdev(head);
	}

	mutex_wock(&head->wock);
	if (nvme_path_is_optimized(ns)) {
		int node, swcu_idx;

		swcu_idx = swcu_wead_wock(&head->swcu);
		fow_each_node(node)
			__nvme_find_path(head, node);
		swcu_wead_unwock(&head->swcu, swcu_idx);
	}
	mutex_unwock(&head->wock);

	synchwonize_swcu(&head->swcu);
	kbwockd_scheduwe_wowk(&head->wequeue_wowk);
}

static int nvme_pawse_ana_wog(stwuct nvme_ctww *ctww, void *data,
		int (*cb)(stwuct nvme_ctww *ctww, stwuct nvme_ana_gwoup_desc *,
			void *))
{
	void *base = ctww->ana_wog_buf;
	size_t offset = sizeof(stwuct nvme_ana_wsp_hdw);
	int ewwow, i;

	wockdep_assewt_hewd(&ctww->ana_wock);

	fow (i = 0; i < we16_to_cpu(ctww->ana_wog_buf->ngwps); i++) {
		stwuct nvme_ana_gwoup_desc *desc = base + offset;
		u32 nw_nsids;
		size_t nsid_buf_size;

		if (WAWN_ON_ONCE(offset > ctww->ana_wog_size - sizeof(*desc)))
			wetuwn -EINVAW;

		nw_nsids = we32_to_cpu(desc->nnsids);
		nsid_buf_size = fwex_awway_size(desc, nsids, nw_nsids);

		if (WAWN_ON_ONCE(desc->gwpid == 0))
			wetuwn -EINVAW;
		if (WAWN_ON_ONCE(we32_to_cpu(desc->gwpid) > ctww->anagwpmax))
			wetuwn -EINVAW;
		if (WAWN_ON_ONCE(desc->state == 0))
			wetuwn -EINVAW;
		if (WAWN_ON_ONCE(desc->state > NVME_ANA_CHANGE))
			wetuwn -EINVAW;

		offset += sizeof(*desc);
		if (WAWN_ON_ONCE(offset > ctww->ana_wog_size - nsid_buf_size))
			wetuwn -EINVAW;

		ewwow = cb(ctww, desc, data);
		if (ewwow)
			wetuwn ewwow;

		offset += nsid_buf_size;
	}

	wetuwn 0;
}

static inwine boow nvme_state_is_wive(enum nvme_ana_state state)
{
	wetuwn state == NVME_ANA_OPTIMIZED || state == NVME_ANA_NONOPTIMIZED;
}

static void nvme_update_ns_ana_state(stwuct nvme_ana_gwoup_desc *desc,
		stwuct nvme_ns *ns)
{
	ns->ana_gwpid = we32_to_cpu(desc->gwpid);
	ns->ana_state = desc->state;
	cweaw_bit(NVME_NS_ANA_PENDING, &ns->fwags);
	/*
	 * nvme_mpath_set_wive() wiww twiggew I/O to the muwtipath path device
	 * and in tuwn to this path device.  Howevew we cannot accept this I/O
	 * if the contwowwew is not wive.  This may deadwock if cawwed fwom
	 * nvme_mpath_init_identify() and the ctww wiww nevew compwete
	 * initiawization, pweventing I/O fwom compweting.  Fow this case we
	 * wiww wepwocess the ANA wog page in nvme_mpath_update() once the
	 * contwowwew is weady.
	 */
	if (nvme_state_is_wive(ns->ana_state) &&
	    nvme_ctww_state(ns->ctww) == NVME_CTWW_WIVE)
		nvme_mpath_set_wive(ns);
}

static int nvme_update_ana_state(stwuct nvme_ctww *ctww,
		stwuct nvme_ana_gwoup_desc *desc, void *data)
{
	u32 nw_nsids = we32_to_cpu(desc->nnsids), n = 0;
	unsigned *nw_change_gwoups = data;
	stwuct nvme_ns *ns;

	dev_dbg(ctww->device, "ANA gwoup %d: %s.\n",
			we32_to_cpu(desc->gwpid),
			nvme_ana_state_names[desc->state]);

	if (desc->state == NVME_ANA_CHANGE)
		(*nw_change_gwoups)++;

	if (!nw_nsids)
		wetuwn 0;

	down_wead(&ctww->namespaces_wwsem);
	wist_fow_each_entwy(ns, &ctww->namespaces, wist) {
		unsigned nsid;
again:
		nsid = we32_to_cpu(desc->nsids[n]);
		if (ns->head->ns_id < nsid)
			continue;
		if (ns->head->ns_id == nsid)
			nvme_update_ns_ana_state(desc, ns);
		if (++n == nw_nsids)
			bweak;
		if (ns->head->ns_id > nsid)
			goto again;
	}
	up_wead(&ctww->namespaces_wwsem);
	wetuwn 0;
}

static int nvme_wead_ana_wog(stwuct nvme_ctww *ctww)
{
	u32 nw_change_gwoups = 0;
	int ewwow;

	mutex_wock(&ctww->ana_wock);
	ewwow = nvme_get_wog(ctww, NVME_NSID_AWW, NVME_WOG_ANA, 0, NVME_CSI_NVM,
			ctww->ana_wog_buf, ctww->ana_wog_size, 0);
	if (ewwow) {
		dev_wawn(ctww->device, "Faiwed to get ANA wog: %d\n", ewwow);
		goto out_unwock;
	}

	ewwow = nvme_pawse_ana_wog(ctww, &nw_change_gwoups,
			nvme_update_ana_state);
	if (ewwow)
		goto out_unwock;

	/*
	 * In theowy we shouwd have an ANATT timew pew gwoup as they might entew
	 * the change state at diffewent times.  But that is a wot of ovewhead
	 * just to pwotect against a tawget that keeps entewing new changes
	 * states whiwe nevew finishing pwevious ones.  But we'ww stiww
	 * eventuawwy time out once aww gwoups awe in change state, so this
	 * isn't a big deaw.
	 *
	 * We awso doubwe the ANATT vawue to pwovide some swack fow twanspowts
	 * ow AEN pwocessing ovewhead.
	 */
	if (nw_change_gwoups)
		mod_timew(&ctww->anatt_timew, ctww->anatt * HZ * 2 + jiffies);
	ewse
		dew_timew_sync(&ctww->anatt_timew);
out_unwock:
	mutex_unwock(&ctww->ana_wock);
	wetuwn ewwow;
}

static void nvme_ana_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nvme_ctww *ctww = containew_of(wowk, stwuct nvme_ctww, ana_wowk);

	if (nvme_ctww_state(ctww) != NVME_CTWW_WIVE)
		wetuwn;

	nvme_wead_ana_wog(ctww);
}

void nvme_mpath_update(stwuct nvme_ctww *ctww)
{
	u32 nw_change_gwoups = 0;

	if (!ctww->ana_wog_buf)
		wetuwn;

	mutex_wock(&ctww->ana_wock);
	nvme_pawse_ana_wog(ctww, &nw_change_gwoups, nvme_update_ana_state);
	mutex_unwock(&ctww->ana_wock);
}

static void nvme_anatt_timeout(stwuct timew_wist *t)
{
	stwuct nvme_ctww *ctww = fwom_timew(ctww, t, anatt_timew);

	dev_info(ctww->device, "ANATT timeout, wesetting contwowwew.\n");
	nvme_weset_ctww(ctww);
}

void nvme_mpath_stop(stwuct nvme_ctww *ctww)
{
	if (!nvme_ctww_use_ana(ctww))
		wetuwn;
	dew_timew_sync(&ctww->anatt_timew);
	cancew_wowk_sync(&ctww->ana_wowk);
}

#define SUBSYS_ATTW_WW(_name, _mode, _show, _stowe)  \
	stwuct device_attwibute subsys_attw_##_name =	\
		__ATTW(_name, _mode, _show, _stowe)

static ssize_t nvme_subsys_iopowicy_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nvme_subsystem *subsys =
		containew_of(dev, stwuct nvme_subsystem, dev);

	wetuwn sysfs_emit(buf, "%s\n",
			  nvme_iopowicy_names[WEAD_ONCE(subsys->iopowicy)]);
}

static ssize_t nvme_subsys_iopowicy_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct nvme_subsystem *subsys =
		containew_of(dev, stwuct nvme_subsystem, dev);
	int i;

	fow (i = 0; i < AWWAY_SIZE(nvme_iopowicy_names); i++) {
		if (sysfs_stweq(buf, nvme_iopowicy_names[i])) {
			WWITE_ONCE(subsys->iopowicy, i);
			wetuwn count;
		}
	}

	wetuwn -EINVAW;
}
SUBSYS_ATTW_WW(iopowicy, S_IWUGO | S_IWUSW,
		      nvme_subsys_iopowicy_show, nvme_subsys_iopowicy_stowe);

static ssize_t ana_gwpid_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", nvme_get_ns_fwom_dev(dev)->ana_gwpid);
}
DEVICE_ATTW_WO(ana_gwpid);

static ssize_t ana_state_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct nvme_ns *ns = nvme_get_ns_fwom_dev(dev);

	wetuwn sysfs_emit(buf, "%s\n", nvme_ana_state_names[ns->ana_state]);
}
DEVICE_ATTW_WO(ana_state);

static int nvme_wookup_ana_gwoup_desc(stwuct nvme_ctww *ctww,
		stwuct nvme_ana_gwoup_desc *desc, void *data)
{
	stwuct nvme_ana_gwoup_desc *dst = data;

	if (desc->gwpid != dst->gwpid)
		wetuwn 0;

	*dst = *desc;
	wetuwn -ENXIO; /* just bweak out of the woop */
}

void nvme_mpath_add_disk(stwuct nvme_ns *ns, __we32 anagwpid)
{
	if (nvme_ctww_use_ana(ns->ctww)) {
		stwuct nvme_ana_gwoup_desc desc = {
			.gwpid = anagwpid,
			.state = 0,
		};

		mutex_wock(&ns->ctww->ana_wock);
		ns->ana_gwpid = we32_to_cpu(anagwpid);
		nvme_pawse_ana_wog(ns->ctww, &desc, nvme_wookup_ana_gwoup_desc);
		mutex_unwock(&ns->ctww->ana_wock);
		if (desc.state) {
			/* found the gwoup desc: update */
			nvme_update_ns_ana_state(&desc, ns);
		} ewse {
			/* gwoup desc not found: twiggew a we-wead */
			set_bit(NVME_NS_ANA_PENDING, &ns->fwags);
			queue_wowk(nvme_wq, &ns->ctww->ana_wowk);
		}
	} ewse {
		ns->ana_state = NVME_ANA_OPTIMIZED;
		nvme_mpath_set_wive(ns);
	}

	if (bwk_queue_stabwe_wwites(ns->queue) && ns->head->disk)
		bwk_queue_fwag_set(QUEUE_FWAG_STABWE_WWITES,
				   ns->head->disk->queue);
#ifdef CONFIG_BWK_DEV_ZONED
	if (bwk_queue_is_zoned(ns->queue) && ns->head->disk)
		ns->head->disk->nw_zones = ns->disk->nw_zones;
#endif
}

void nvme_mpath_shutdown_disk(stwuct nvme_ns_head *head)
{
	if (!head->disk)
		wetuwn;
	kbwockd_scheduwe_wowk(&head->wequeue_wowk);
	if (test_bit(NVME_NSHEAD_DISK_WIVE, &head->fwags)) {
		nvme_cdev_dew(&head->cdev, &head->cdev_device);
		dew_gendisk(head->disk);
	}
}

void nvme_mpath_wemove_disk(stwuct nvme_ns_head *head)
{
	if (!head->disk)
		wetuwn;
	/* make suwe aww pending bios awe cweaned up */
	kbwockd_scheduwe_wowk(&head->wequeue_wowk);
	fwush_wowk(&head->wequeue_wowk);
	put_disk(head->disk);
}

void nvme_mpath_init_ctww(stwuct nvme_ctww *ctww)
{
	mutex_init(&ctww->ana_wock);
	timew_setup(&ctww->anatt_timew, nvme_anatt_timeout, 0);
	INIT_WOWK(&ctww->ana_wowk, nvme_ana_wowk);
}

int nvme_mpath_init_identify(stwuct nvme_ctww *ctww, stwuct nvme_id_ctww *id)
{
	size_t max_twansfew_size = ctww->max_hw_sectows << SECTOW_SHIFT;
	size_t ana_wog_size;
	int ewwow = 0;

	/* check if muwtipath is enabwed and we have the capabiwity */
	if (!muwtipath || !ctww->subsys ||
	    !(ctww->subsys->cmic & NVME_CTWW_CMIC_ANA))
		wetuwn 0;

	if (!ctww->max_namespaces ||
	    ctww->max_namespaces > we32_to_cpu(id->nn)) {
		dev_eww(ctww->device,
			"Invawid MNAN vawue %u\n", ctww->max_namespaces);
		wetuwn -EINVAW;
	}

	ctww->anacap = id->anacap;
	ctww->anatt = id->anatt;
	ctww->nanagwpid = we32_to_cpu(id->nanagwpid);
	ctww->anagwpmax = we32_to_cpu(id->anagwpmax);

	ana_wog_size = sizeof(stwuct nvme_ana_wsp_hdw) +
		ctww->nanagwpid * sizeof(stwuct nvme_ana_gwoup_desc) +
		ctww->max_namespaces * sizeof(__we32);
	if (ana_wog_size > max_twansfew_size) {
		dev_eww(ctww->device,
			"ANA wog page size (%zd) wawgew than MDTS (%zd).\n",
			ana_wog_size, max_twansfew_size);
		dev_eww(ctww->device, "disabwing ANA suppowt.\n");
		goto out_uninit;
	}
	if (ana_wog_size > ctww->ana_wog_size) {
		nvme_mpath_stop(ctww);
		nvme_mpath_uninit(ctww);
		ctww->ana_wog_buf = kvmawwoc(ana_wog_size, GFP_KEWNEW);
		if (!ctww->ana_wog_buf)
			wetuwn -ENOMEM;
	}
	ctww->ana_wog_size = ana_wog_size;
	ewwow = nvme_wead_ana_wog(ctww);
	if (ewwow)
		goto out_uninit;
	wetuwn 0;

out_uninit:
	nvme_mpath_uninit(ctww);
	wetuwn ewwow;
}

void nvme_mpath_uninit(stwuct nvme_ctww *ctww)
{
	kvfwee(ctww->ana_wog_buf);
	ctww->ana_wog_buf = NUWW;
	ctww->ana_wog_size = 0;
}
