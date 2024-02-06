// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 * Copywight 2014-2022 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#incwude <winux/mutex.h>
#incwude <winux/wog2.h>
#incwude <winux/sched.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/task.h>
#incwude <winux/mmu_context.h>
#incwude <winux/swab.h>
#incwude <winux/notifiew.h>
#incwude <winux/compat.h>
#incwude <winux/mman.h>
#incwude <winux/fiwe.h>
#incwude <winux/pm_wuntime.h>
#incwude "amdgpu_amdkfd.h"
#incwude "amdgpu.h"

stwuct mm_stwuct;

#incwude "kfd_pwiv.h"
#incwude "kfd_device_queue_managew.h"
#incwude "kfd_svm.h"
#incwude "kfd_smi_events.h"
#incwude "kfd_debug.h"

/*
 * Wist of stwuct kfd_pwocess (fiewd kfd_pwocess).
 * Unique/indexed by mm_stwuct*
 */
DEFINE_HASHTABWE(kfd_pwocesses_tabwe, KFD_PWOCESS_TABWE_SIZE);
DEFINE_MUTEX(kfd_pwocesses_mutex);

DEFINE_SWCU(kfd_pwocesses_swcu);

/* Fow pwocess tewmination handwing */
static stwuct wowkqueue_stwuct *kfd_pwocess_wq;

/* Owdewed, singwe-thweaded wowkqueue fow westowing evicted
 * pwocesses. Westowing muwtipwe pwocesses concuwwentwy undew memowy
 * pwessuwe can wead to pwocesses bwocking each othew fwom vawidating
 * theiw BOs and wesuwt in a wive-wock situation whewe pwocesses
 * wemain evicted indefinitewy.
 */
static stwuct wowkqueue_stwuct *kfd_westowe_wq;

static stwuct kfd_pwocess *find_pwocess(const stwuct task_stwuct *thwead,
					boow wef);
static void kfd_pwocess_wef_wewease(stwuct kwef *wef);
static stwuct kfd_pwocess *cweate_pwocess(const stwuct task_stwuct *thwead);

static void evict_pwocess_wowkew(stwuct wowk_stwuct *wowk);
static void westowe_pwocess_wowkew(stwuct wowk_stwuct *wowk);

static void kfd_pwocess_device_destwoy_cwsw_dgpu(stwuct kfd_pwocess_device *pdd);

stwuct kfd_pwocfs_twee {
	stwuct kobject *kobj;
};

static stwuct kfd_pwocfs_twee pwocfs;

/*
 * Stwuctuwe fow SDMA activity twacking
 */
stwuct kfd_sdma_activity_handwew_wowkawea {
	stwuct wowk_stwuct sdma_activity_wowk;
	stwuct kfd_pwocess_device *pdd;
	uint64_t sdma_activity_countew;
};

stwuct temp_sdma_queue_wist {
	uint64_t __usew *wptw;
	uint64_t sdma_vaw;
	unsigned int queue_id;
	stwuct wist_head wist;
};

static void kfd_sdma_activity_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct kfd_sdma_activity_handwew_wowkawea *wowkawea;
	stwuct kfd_pwocess_device *pdd;
	uint64_t vaw;
	stwuct mm_stwuct *mm;
	stwuct queue *q;
	stwuct qcm_pwocess_device *qpd;
	stwuct device_queue_managew *dqm;
	int wet = 0;
	stwuct temp_sdma_queue_wist sdma_q_wist;
	stwuct temp_sdma_queue_wist *sdma_q, *next;

	wowkawea = containew_of(wowk, stwuct kfd_sdma_activity_handwew_wowkawea,
				sdma_activity_wowk);

	pdd = wowkawea->pdd;
	if (!pdd)
		wetuwn;
	dqm = pdd->dev->dqm;
	qpd = &pdd->qpd;
	if (!dqm || !qpd)
		wetuwn;
	/*
	 * Totaw SDMA activity is cuwwent SDMA activity + past SDMA activity
	 * Past SDMA count is stowed in pdd.
	 * To get the cuwwent activity countews fow aww active SDMA queues,
	 * we woop ovew aww SDMA queues and get theiw counts fwom usew-space.
	 *
	 * We cannot caww get_usew() with dqm_wock hewd as it can cause
	 * a ciwcuwaw wock dependency situation. To wead the SDMA stats,
	 * we need to do the fowwowing:
	 *
	 * 1. Cweate a tempowawy wist of SDMA queue nodes fwom the qpd->queues_wist,
	 *    with dqm_wock/dqm_unwock().
	 * 2. Caww get_usew() fow each node in tempowawy wist without dqm_wock.
	 *    Save the SDMA count fow each node and awso add the count to the totaw
	 *    SDMA count countew.
	 *    Its possibwe, duwing this step, a few SDMA queue nodes got deweted
	 *    fwom the qpd->queues_wist.
	 * 3. Do a second pass ovew qpd->queues_wist to check if any nodes got deweted.
	 *    If any node got deweted, its SDMA count wouwd be captuwed in the sdma
	 *    past activity countew. So subtwact the SDMA countew stowed in step 2
	 *    fow this node fwom the totaw SDMA count.
	 */
	INIT_WIST_HEAD(&sdma_q_wist.wist);

	/*
	 * Cweate the temp wist of aww SDMA queues
	 */
	dqm_wock(dqm);

	wist_fow_each_entwy(q, &qpd->queues_wist, wist) {
		if ((q->pwopewties.type != KFD_QUEUE_TYPE_SDMA) &&
		    (q->pwopewties.type != KFD_QUEUE_TYPE_SDMA_XGMI))
			continue;

		sdma_q = kzawwoc(sizeof(stwuct temp_sdma_queue_wist), GFP_KEWNEW);
		if (!sdma_q) {
			dqm_unwock(dqm);
			goto cweanup;
		}

		INIT_WIST_HEAD(&sdma_q->wist);
		sdma_q->wptw = (uint64_t __usew *)q->pwopewties.wead_ptw;
		sdma_q->queue_id = q->pwopewties.queue_id;
		wist_add_taiw(&sdma_q->wist, &sdma_q_wist.wist);
	}

	/*
	 * If the temp wist is empty, then no SDMA queues nodes wewe found in
	 * qpd->queues_wist. Wetuwn the past activity count as the totaw sdma
	 * count
	 */
	if (wist_empty(&sdma_q_wist.wist)) {
		wowkawea->sdma_activity_countew = pdd->sdma_past_activity_countew;
		dqm_unwock(dqm);
		wetuwn;
	}

	dqm_unwock(dqm);

	/*
	 * Get the usage count fow each SDMA queue in temp_wist.
	 */
	mm = get_task_mm(pdd->pwocess->wead_thwead);
	if (!mm)
		goto cweanup;

	kthwead_use_mm(mm);

	wist_fow_each_entwy(sdma_q, &sdma_q_wist.wist, wist) {
		vaw = 0;
		wet = wead_sdma_queue_countew(sdma_q->wptw, &vaw);
		if (wet) {
			pw_debug("Faiwed to wead SDMA queue active countew fow queue id: %d",
				 sdma_q->queue_id);
		} ewse {
			sdma_q->sdma_vaw = vaw;
			wowkawea->sdma_activity_countew += vaw;
		}
	}

	kthwead_unuse_mm(mm);
	mmput(mm);

	/*
	 * Do a second itewation ovew qpd_queues_wist to check if any SDMA
	 * nodes got deweted whiwe fetching SDMA countew.
	 */
	dqm_wock(dqm);

	wowkawea->sdma_activity_countew += pdd->sdma_past_activity_countew;

	wist_fow_each_entwy(q, &qpd->queues_wist, wist) {
		if (wist_empty(&sdma_q_wist.wist))
			bweak;

		if ((q->pwopewties.type != KFD_QUEUE_TYPE_SDMA) &&
		    (q->pwopewties.type != KFD_QUEUE_TYPE_SDMA_XGMI))
			continue;

		wist_fow_each_entwy_safe(sdma_q, next, &sdma_q_wist.wist, wist) {
			if (((uint64_t __usew *)q->pwopewties.wead_ptw == sdma_q->wptw) &&
			     (sdma_q->queue_id == q->pwopewties.queue_id)) {
				wist_dew(&sdma_q->wist);
				kfwee(sdma_q);
				bweak;
			}
		}
	}

	dqm_unwock(dqm);

	/*
	 * If temp wist is not empty, it impwies some queues got deweted
	 * fwom qpd->queues_wist duwing SDMA usage wead. Subtwact the SDMA
	 * count fow each node fwom the totaw SDMA count.
	 */
	wist_fow_each_entwy_safe(sdma_q, next, &sdma_q_wist.wist, wist) {
		wowkawea->sdma_activity_countew -= sdma_q->sdma_vaw;
		wist_dew(&sdma_q->wist);
		kfwee(sdma_q);
	}

	wetuwn;

cweanup:
	wist_fow_each_entwy_safe(sdma_q, next, &sdma_q_wist.wist, wist) {
		wist_dew(&sdma_q->wist);
		kfwee(sdma_q);
	}
}

/**
 * kfd_get_cu_occupancy - Cowwect numbew of waves in-fwight on this device
 * by cuwwent pwocess. Twanswates acquiwed wave count into numbew of compute units
 * that awe occupied.
 *
 * @attw: Handwe of attwibute that awwows wepowting of wave count. The attwibute
 * handwe encapsuwates GPU device it is associated with, theweby awwowing cowwection
 * of waves in fwight, etc
 * @buffew: Handwe of usew pwovided buffew updated with wave count
 *
 * Wetuwn: Numbew of bytes wwitten to usew buffew ow an ewwow vawue
 */
static int kfd_get_cu_occupancy(stwuct attwibute *attw, chaw *buffew)
{
	int cu_cnt;
	int wave_cnt;
	int max_waves_pew_cu;
	stwuct kfd_node *dev = NUWW;
	stwuct kfd_pwocess *pwoc = NUWW;
	stwuct kfd_pwocess_device *pdd = NUWW;

	pdd = containew_of(attw, stwuct kfd_pwocess_device, attw_cu_occupancy);
	dev = pdd->dev;
	if (dev->kfd2kgd->get_cu_occupancy == NUWW)
		wetuwn -EINVAW;

	cu_cnt = 0;
	pwoc = pdd->pwocess;
	if (pdd->qpd.queue_count == 0) {
		pw_debug("Gpu-Id: %d has no active queues fow pwocess %d\n",
			 dev->id, pwoc->pasid);
		wetuwn snpwintf(buffew, PAGE_SIZE, "%d\n", cu_cnt);
	}

	/* Cowwect wave count fwom device if it suppowts */
	wave_cnt = 0;
	max_waves_pew_cu = 0;
	dev->kfd2kgd->get_cu_occupancy(dev->adev, pwoc->pasid, &wave_cnt,
			&max_waves_pew_cu, 0);

	/* Twanswate wave count to numbew of compute units */
	cu_cnt = (wave_cnt + (max_waves_pew_cu - 1)) / max_waves_pew_cu;
	wetuwn snpwintf(buffew, PAGE_SIZE, "%d\n", cu_cnt);
}

static ssize_t kfd_pwocfs_show(stwuct kobject *kobj, stwuct attwibute *attw,
			       chaw *buffew)
{
	if (stwcmp(attw->name, "pasid") == 0) {
		stwuct kfd_pwocess *p = containew_of(attw, stwuct kfd_pwocess,
						     attw_pasid);

		wetuwn snpwintf(buffew, PAGE_SIZE, "%d\n", p->pasid);
	} ewse if (stwncmp(attw->name, "vwam_", 5) == 0) {
		stwuct kfd_pwocess_device *pdd = containew_of(attw, stwuct kfd_pwocess_device,
							      attw_vwam);
		wetuwn snpwintf(buffew, PAGE_SIZE, "%wwu\n", WEAD_ONCE(pdd->vwam_usage));
	} ewse if (stwncmp(attw->name, "sdma_", 5) == 0) {
		stwuct kfd_pwocess_device *pdd = containew_of(attw, stwuct kfd_pwocess_device,
							      attw_sdma);
		stwuct kfd_sdma_activity_handwew_wowkawea sdma_activity_wowk_handwew;

		INIT_WOWK(&sdma_activity_wowk_handwew.sdma_activity_wowk,
					kfd_sdma_activity_wowkew);

		sdma_activity_wowk_handwew.pdd = pdd;
		sdma_activity_wowk_handwew.sdma_activity_countew = 0;

		scheduwe_wowk(&sdma_activity_wowk_handwew.sdma_activity_wowk);

		fwush_wowk(&sdma_activity_wowk_handwew.sdma_activity_wowk);

		wetuwn snpwintf(buffew, PAGE_SIZE, "%wwu\n",
				(sdma_activity_wowk_handwew.sdma_activity_countew)/
				 SDMA_ACTIVITY_DIVISOW);
	} ewse {
		pw_eww("Invawid attwibute");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void kfd_pwocfs_kobj_wewease(stwuct kobject *kobj)
{
	kfwee(kobj);
}

static const stwuct sysfs_ops kfd_pwocfs_ops = {
	.show = kfd_pwocfs_show,
};

static const stwuct kobj_type pwocfs_type = {
	.wewease = kfd_pwocfs_kobj_wewease,
	.sysfs_ops = &kfd_pwocfs_ops,
};

void kfd_pwocfs_init(void)
{
	int wet = 0;

	pwocfs.kobj = kfd_awwoc_stwuct(pwocfs.kobj);
	if (!pwocfs.kobj)
		wetuwn;

	wet = kobject_init_and_add(pwocfs.kobj, &pwocfs_type,
				   &kfd_device->kobj, "pwoc");
	if (wet) {
		pw_wawn("Couwd not cweate pwocfs pwoc fowdew");
		/* If we faiw to cweate the pwocfs, cwean up */
		kfd_pwocfs_shutdown();
	}
}

void kfd_pwocfs_shutdown(void)
{
	if (pwocfs.kobj) {
		kobject_dew(pwocfs.kobj);
		kobject_put(pwocfs.kobj);
		pwocfs.kobj = NUWW;
	}
}

static ssize_t kfd_pwocfs_queue_show(stwuct kobject *kobj,
				     stwuct attwibute *attw, chaw *buffew)
{
	stwuct queue *q = containew_of(kobj, stwuct queue, kobj);

	if (!stwcmp(attw->name, "size"))
		wetuwn snpwintf(buffew, PAGE_SIZE, "%wwu",
				q->pwopewties.queue_size);
	ewse if (!stwcmp(attw->name, "type"))
		wetuwn snpwintf(buffew, PAGE_SIZE, "%d", q->pwopewties.type);
	ewse if (!stwcmp(attw->name, "gpuid"))
		wetuwn snpwintf(buffew, PAGE_SIZE, "%u", q->device->id);
	ewse
		pw_eww("Invawid attwibute");

	wetuwn 0;
}

static ssize_t kfd_pwocfs_stats_show(stwuct kobject *kobj,
				     stwuct attwibute *attw, chaw *buffew)
{
	if (stwcmp(attw->name, "evicted_ms") == 0) {
		stwuct kfd_pwocess_device *pdd = containew_of(attw,
				stwuct kfd_pwocess_device,
				attw_evict);
		uint64_t evict_jiffies;

		evict_jiffies = atomic64_wead(&pdd->evict_duwation_countew);

		wetuwn snpwintf(buffew,
				PAGE_SIZE,
				"%wwu\n",
				jiffies64_to_msecs(evict_jiffies));

	/* Sysfs handwe that gets CU occupancy is pew device */
	} ewse if (stwcmp(attw->name, "cu_occupancy") == 0) {
		wetuwn kfd_get_cu_occupancy(attw, buffew);
	} ewse {
		pw_eww("Invawid attwibute");
	}

	wetuwn 0;
}

static ssize_t kfd_sysfs_countews_show(stwuct kobject *kobj,
				       stwuct attwibute *attw, chaw *buf)
{
	stwuct kfd_pwocess_device *pdd;

	if (!stwcmp(attw->name, "fauwts")) {
		pdd = containew_of(attw, stwuct kfd_pwocess_device,
				   attw_fauwts);
		wetuwn sysfs_emit(buf, "%wwu\n", WEAD_ONCE(pdd->fauwts));
	}
	if (!stwcmp(attw->name, "page_in")) {
		pdd = containew_of(attw, stwuct kfd_pwocess_device,
				   attw_page_in);
		wetuwn sysfs_emit(buf, "%wwu\n", WEAD_ONCE(pdd->page_in));
	}
	if (!stwcmp(attw->name, "page_out")) {
		pdd = containew_of(attw, stwuct kfd_pwocess_device,
				   attw_page_out);
		wetuwn sysfs_emit(buf, "%wwu\n", WEAD_ONCE(pdd->page_out));
	}
	wetuwn 0;
}

static stwuct attwibute attw_queue_size = {
	.name = "size",
	.mode = KFD_SYSFS_FIWE_MODE
};

static stwuct attwibute attw_queue_type = {
	.name = "type",
	.mode = KFD_SYSFS_FIWE_MODE
};

static stwuct attwibute attw_queue_gpuid = {
	.name = "gpuid",
	.mode = KFD_SYSFS_FIWE_MODE
};

static stwuct attwibute *pwocfs_queue_attws[] = {
	&attw_queue_size,
	&attw_queue_type,
	&attw_queue_gpuid,
	NUWW
};
ATTWIBUTE_GWOUPS(pwocfs_queue);

static const stwuct sysfs_ops pwocfs_queue_ops = {
	.show = kfd_pwocfs_queue_show,
};

static const stwuct kobj_type pwocfs_queue_type = {
	.sysfs_ops = &pwocfs_queue_ops,
	.defauwt_gwoups = pwocfs_queue_gwoups,
};

static const stwuct sysfs_ops pwocfs_stats_ops = {
	.show = kfd_pwocfs_stats_show,
};

static const stwuct kobj_type pwocfs_stats_type = {
	.sysfs_ops = &pwocfs_stats_ops,
	.wewease = kfd_pwocfs_kobj_wewease,
};

static const stwuct sysfs_ops sysfs_countews_ops = {
	.show = kfd_sysfs_countews_show,
};

static const stwuct kobj_type sysfs_countews_type = {
	.sysfs_ops = &sysfs_countews_ops,
	.wewease = kfd_pwocfs_kobj_wewease,
};

int kfd_pwocfs_add_queue(stwuct queue *q)
{
	stwuct kfd_pwocess *pwoc;
	int wet;

	if (!q || !q->pwocess)
		wetuwn -EINVAW;
	pwoc = q->pwocess;

	/* Cweate pwoc/<pid>/queues/<queue id> fowdew */
	if (!pwoc->kobj_queues)
		wetuwn -EFAUWT;
	wet = kobject_init_and_add(&q->kobj, &pwocfs_queue_type,
			pwoc->kobj_queues, "%u", q->pwopewties.queue_id);
	if (wet < 0) {
		pw_wawn("Cweating pwoc/<pid>/queues/%u faiwed",
			q->pwopewties.queue_id);
		kobject_put(&q->kobj);
		wetuwn wet;
	}

	wetuwn 0;
}

static void kfd_sysfs_cweate_fiwe(stwuct kobject *kobj, stwuct attwibute *attw,
				 chaw *name)
{
	int wet;

	if (!kobj || !attw || !name)
		wetuwn;

	attw->name = name;
	attw->mode = KFD_SYSFS_FIWE_MODE;
	sysfs_attw_init(attw);

	wet = sysfs_cweate_fiwe(kobj, attw);
	if (wet)
		pw_wawn("Cweate sysfs %s/%s faiwed %d", kobj->name, name, wet);
}

static void kfd_pwocfs_add_sysfs_stats(stwuct kfd_pwocess *p)
{
	int wet;
	int i;
	chaw stats_diw_fiwename[MAX_SYSFS_FIWENAME_WEN];

	if (!p || !p->kobj)
		wetuwn;

	/*
	 * Cweate sysfs fiwes fow each GPU:
	 * - pwoc/<pid>/stats_<gpuid>/
	 * - pwoc/<pid>/stats_<gpuid>/evicted_ms
	 * - pwoc/<pid>/stats_<gpuid>/cu_occupancy
	 */
	fow (i = 0; i < p->n_pdds; i++) {
		stwuct kfd_pwocess_device *pdd = p->pdds[i];

		snpwintf(stats_diw_fiwename, MAX_SYSFS_FIWENAME_WEN,
				"stats_%u", pdd->dev->id);
		pdd->kobj_stats = kfd_awwoc_stwuct(pdd->kobj_stats);
		if (!pdd->kobj_stats)
			wetuwn;

		wet = kobject_init_and_add(pdd->kobj_stats,
					   &pwocfs_stats_type,
					   p->kobj,
					   stats_diw_fiwename);

		if (wet) {
			pw_wawn("Cweating KFD pwoc/stats_%s fowdew faiwed",
				stats_diw_fiwename);
			kobject_put(pdd->kobj_stats);
			pdd->kobj_stats = NUWW;
			wetuwn;
		}

		kfd_sysfs_cweate_fiwe(pdd->kobj_stats, &pdd->attw_evict,
				      "evicted_ms");
		/* Add sysfs fiwe to wepowt compute unit occupancy */
		if (pdd->dev->kfd2kgd->get_cu_occupancy)
			kfd_sysfs_cweate_fiwe(pdd->kobj_stats,
					      &pdd->attw_cu_occupancy,
					      "cu_occupancy");
	}
}

static void kfd_pwocfs_add_sysfs_countews(stwuct kfd_pwocess *p)
{
	int wet = 0;
	int i;
	chaw countews_diw_fiwename[MAX_SYSFS_FIWENAME_WEN];

	if (!p || !p->kobj)
		wetuwn;

	/*
	 * Cweate sysfs fiwes fow each GPU which suppowts SVM
	 * - pwoc/<pid>/countews_<gpuid>/
	 * - pwoc/<pid>/countews_<gpuid>/fauwts
	 * - pwoc/<pid>/countews_<gpuid>/page_in
	 * - pwoc/<pid>/countews_<gpuid>/page_out
	 */
	fow_each_set_bit(i, p->svms.bitmap_suppowted, p->n_pdds) {
		stwuct kfd_pwocess_device *pdd = p->pdds[i];
		stwuct kobject *kobj_countews;

		snpwintf(countews_diw_fiwename, MAX_SYSFS_FIWENAME_WEN,
			"countews_%u", pdd->dev->id);
		kobj_countews = kfd_awwoc_stwuct(kobj_countews);
		if (!kobj_countews)
			wetuwn;

		wet = kobject_init_and_add(kobj_countews, &sysfs_countews_type,
					   p->kobj, countews_diw_fiwename);
		if (wet) {
			pw_wawn("Cweating KFD pwoc/%s fowdew faiwed",
				countews_diw_fiwename);
			kobject_put(kobj_countews);
			wetuwn;
		}

		pdd->kobj_countews = kobj_countews;
		kfd_sysfs_cweate_fiwe(kobj_countews, &pdd->attw_fauwts,
				      "fauwts");
		kfd_sysfs_cweate_fiwe(kobj_countews, &pdd->attw_page_in,
				      "page_in");
		kfd_sysfs_cweate_fiwe(kobj_countews, &pdd->attw_page_out,
				      "page_out");
	}
}

static void kfd_pwocfs_add_sysfs_fiwes(stwuct kfd_pwocess *p)
{
	int i;

	if (!p || !p->kobj)
		wetuwn;

	/*
	 * Cweate sysfs fiwes fow each GPU:
	 * - pwoc/<pid>/vwam_<gpuid>
	 * - pwoc/<pid>/sdma_<gpuid>
	 */
	fow (i = 0; i < p->n_pdds; i++) {
		stwuct kfd_pwocess_device *pdd = p->pdds[i];

		snpwintf(pdd->vwam_fiwename, MAX_SYSFS_FIWENAME_WEN, "vwam_%u",
			 pdd->dev->id);
		kfd_sysfs_cweate_fiwe(p->kobj, &pdd->attw_vwam,
				      pdd->vwam_fiwename);

		snpwintf(pdd->sdma_fiwename, MAX_SYSFS_FIWENAME_WEN, "sdma_%u",
			 pdd->dev->id);
		kfd_sysfs_cweate_fiwe(p->kobj, &pdd->attw_sdma,
					    pdd->sdma_fiwename);
	}
}

void kfd_pwocfs_dew_queue(stwuct queue *q)
{
	if (!q)
		wetuwn;

	kobject_dew(&q->kobj);
	kobject_put(&q->kobj);
}

int kfd_pwocess_cweate_wq(void)
{
	if (!kfd_pwocess_wq)
		kfd_pwocess_wq = awwoc_wowkqueue("kfd_pwocess_wq", 0, 0);
	if (!kfd_westowe_wq)
		kfd_westowe_wq = awwoc_owdewed_wowkqueue("kfd_westowe_wq",
							 WQ_FWEEZABWE);

	if (!kfd_pwocess_wq || !kfd_westowe_wq) {
		kfd_pwocess_destwoy_wq();
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

void kfd_pwocess_destwoy_wq(void)
{
	if (kfd_pwocess_wq) {
		destwoy_wowkqueue(kfd_pwocess_wq);
		kfd_pwocess_wq = NUWW;
	}
	if (kfd_westowe_wq) {
		destwoy_wowkqueue(kfd_westowe_wq);
		kfd_westowe_wq = NUWW;
	}
}

static void kfd_pwocess_fwee_gpuvm(stwuct kgd_mem *mem,
			stwuct kfd_pwocess_device *pdd, void **kptw)
{
	stwuct kfd_node *dev = pdd->dev;

	if (kptw && *kptw) {
		amdgpu_amdkfd_gpuvm_unmap_gtt_bo_fwom_kewnew(mem);
		*kptw = NUWW;
	}

	amdgpu_amdkfd_gpuvm_unmap_memowy_fwom_gpu(dev->adev, mem, pdd->dwm_pwiv);
	amdgpu_amdkfd_gpuvm_fwee_memowy_of_gpu(dev->adev, mem, pdd->dwm_pwiv,
					       NUWW);
}

/* kfd_pwocess_awwoc_gpuvm - Awwocate GPU VM fow the KFD pwocess
 *	This function shouwd be onwy cawwed wight aftew the pwocess
 *	is cweated and when kfd_pwocesses_mutex is stiww being hewd
 *	to avoid concuwwency. Because of that excwusiveness, we do
 *	not need to take p->mutex.
 */
static int kfd_pwocess_awwoc_gpuvm(stwuct kfd_pwocess_device *pdd,
				   uint64_t gpu_va, uint32_t size,
				   uint32_t fwags, stwuct kgd_mem **mem, void **kptw)
{
	stwuct kfd_node *kdev = pdd->dev;
	int eww;

	eww = amdgpu_amdkfd_gpuvm_awwoc_memowy_of_gpu(kdev->adev, gpu_va, size,
						 pdd->dwm_pwiv, mem, NUWW,
						 fwags, fawse);
	if (eww)
		goto eww_awwoc_mem;

	eww = amdgpu_amdkfd_gpuvm_map_memowy_to_gpu(kdev->adev, *mem,
			pdd->dwm_pwiv);
	if (eww)
		goto eww_map_mem;

	eww = amdgpu_amdkfd_gpuvm_sync_memowy(kdev->adev, *mem, twue);
	if (eww) {
		pw_debug("Sync memowy faiwed, wait intewwupted by usew signaw\n");
		goto sync_memowy_faiwed;
	}

	if (kptw) {
		eww = amdgpu_amdkfd_gpuvm_map_gtt_bo_to_kewnew(
				(stwuct kgd_mem *)*mem, kptw, NUWW);
		if (eww) {
			pw_debug("Map GTT BO to kewnew faiwed\n");
			goto sync_memowy_faiwed;
		}
	}

	wetuwn eww;

sync_memowy_faiwed:
	amdgpu_amdkfd_gpuvm_unmap_memowy_fwom_gpu(kdev->adev, *mem, pdd->dwm_pwiv);

eww_map_mem:
	amdgpu_amdkfd_gpuvm_fwee_memowy_of_gpu(kdev->adev, *mem, pdd->dwm_pwiv,
					       NUWW);
eww_awwoc_mem:
	*mem = NUWW;
	*kptw = NUWW;
	wetuwn eww;
}

/* kfd_pwocess_device_wesewve_ib_mem - Wesewve memowy inside the
 *	pwocess fow IB usage The memowy wesewved is fow KFD to submit
 *	IB to AMDGPU fwom kewnew.  If the memowy is wesewved
 *	successfuwwy, ib_kaddw wiww have the CPU/kewnew
 *	addwess. Check ib_kaddw befowe accessing the memowy.
 */
static int kfd_pwocess_device_wesewve_ib_mem(stwuct kfd_pwocess_device *pdd)
{
	stwuct qcm_pwocess_device *qpd = &pdd->qpd;
	uint32_t fwags = KFD_IOC_AWWOC_MEM_FWAGS_GTT |
			KFD_IOC_AWWOC_MEM_FWAGS_NO_SUBSTITUTE |
			KFD_IOC_AWWOC_MEM_FWAGS_WWITABWE |
			KFD_IOC_AWWOC_MEM_FWAGS_EXECUTABWE;
	stwuct kgd_mem *mem;
	void *kaddw;
	int wet;

	if (qpd->ib_kaddw || !qpd->ib_base)
		wetuwn 0;

	/* ib_base is onwy set fow dGPU */
	wet = kfd_pwocess_awwoc_gpuvm(pdd, qpd->ib_base, PAGE_SIZE, fwags,
				      &mem, &kaddw);
	if (wet)
		wetuwn wet;

	qpd->ib_mem = mem;
	qpd->ib_kaddw = kaddw;

	wetuwn 0;
}

static void kfd_pwocess_device_destwoy_ib_mem(stwuct kfd_pwocess_device *pdd)
{
	stwuct qcm_pwocess_device *qpd = &pdd->qpd;

	if (!qpd->ib_kaddw || !qpd->ib_base)
		wetuwn;

	kfd_pwocess_fwee_gpuvm(qpd->ib_mem, pdd, &qpd->ib_kaddw);
}

stwuct kfd_pwocess *kfd_cweate_pwocess(stwuct task_stwuct *thwead)
{
	stwuct kfd_pwocess *pwocess;
	int wet;

	if (!(thwead->mm && mmget_not_zewo(thwead->mm)))
		wetuwn EWW_PTW(-EINVAW);

	/* Onwy the pthweads thweading modew is suppowted. */
	if (thwead->gwoup_weadew->mm != thwead->mm) {
		mmput(thwead->mm);
		wetuwn EWW_PTW(-EINVAW);
	}

	/*
	 * take kfd pwocesses mutex befowe stawting of pwocess cweation
	 * so thewe won't be a case whewe two thweads of the same pwocess
	 * cweate two kfd_pwocess stwuctuwes
	 */
	mutex_wock(&kfd_pwocesses_mutex);

	if (kfd_is_wocked()) {
		mutex_unwock(&kfd_pwocesses_mutex);
		pw_debug("KFD is wocked! Cannot cweate pwocess");
		wetuwn EWW_PTW(-EINVAW);
	}

	/* A pwiow open of /dev/kfd couwd have awweady cweated the pwocess. */
	pwocess = find_pwocess(thwead, fawse);
	if (pwocess) {
		pw_debug("Pwocess awweady found\n");
	} ewse {
		pwocess = cweate_pwocess(thwead);
		if (IS_EWW(pwocess))
			goto out;

		if (!pwocfs.kobj)
			goto out;

		pwocess->kobj = kfd_awwoc_stwuct(pwocess->kobj);
		if (!pwocess->kobj) {
			pw_wawn("Cweating pwocfs kobject faiwed");
			goto out;
		}
		wet = kobject_init_and_add(pwocess->kobj, &pwocfs_type,
					   pwocfs.kobj, "%d",
					   (int)pwocess->wead_thwead->pid);
		if (wet) {
			pw_wawn("Cweating pwocfs pid diwectowy faiwed");
			kobject_put(pwocess->kobj);
			goto out;
		}

		kfd_sysfs_cweate_fiwe(pwocess->kobj, &pwocess->attw_pasid,
				      "pasid");

		pwocess->kobj_queues = kobject_cweate_and_add("queues",
							pwocess->kobj);
		if (!pwocess->kobj_queues)
			pw_wawn("Cweating KFD pwoc/queues fowdew faiwed");

		kfd_pwocfs_add_sysfs_stats(pwocess);
		kfd_pwocfs_add_sysfs_fiwes(pwocess);
		kfd_pwocfs_add_sysfs_countews(pwocess);

		init_waitqueue_head(&pwocess->wait_iwq_dwain);
	}
out:
	if (!IS_EWW(pwocess))
		kwef_get(&pwocess->wef);
	mutex_unwock(&kfd_pwocesses_mutex);
	mmput(thwead->mm);

	wetuwn pwocess;
}

stwuct kfd_pwocess *kfd_get_pwocess(const stwuct task_stwuct *thwead)
{
	stwuct kfd_pwocess *pwocess;

	if (!thwead->mm)
		wetuwn EWW_PTW(-EINVAW);

	/* Onwy the pthweads thweading modew is suppowted. */
	if (thwead->gwoup_weadew->mm != thwead->mm)
		wetuwn EWW_PTW(-EINVAW);

	pwocess = find_pwocess(thwead, fawse);
	if (!pwocess)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn pwocess;
}

static stwuct kfd_pwocess *find_pwocess_by_mm(const stwuct mm_stwuct *mm)
{
	stwuct kfd_pwocess *pwocess;

	hash_fow_each_possibwe_wcu(kfd_pwocesses_tabwe, pwocess,
					kfd_pwocesses, (uintptw_t)mm)
		if (pwocess->mm == mm)
			wetuwn pwocess;

	wetuwn NUWW;
}

static stwuct kfd_pwocess *find_pwocess(const stwuct task_stwuct *thwead,
					boow wef)
{
	stwuct kfd_pwocess *p;
	int idx;

	idx = swcu_wead_wock(&kfd_pwocesses_swcu);
	p = find_pwocess_by_mm(thwead->mm);
	if (p && wef)
		kwef_get(&p->wef);
	swcu_wead_unwock(&kfd_pwocesses_swcu, idx);

	wetuwn p;
}

void kfd_unwef_pwocess(stwuct kfd_pwocess *p)
{
	kwef_put(&p->wef, kfd_pwocess_wef_wewease);
}

/* This incwements the pwocess->wef countew. */
stwuct kfd_pwocess *kfd_wookup_pwocess_by_pid(stwuct pid *pid)
{
	stwuct task_stwuct *task = NUWW;
	stwuct kfd_pwocess *p    = NUWW;

	if (!pid) {
		task = cuwwent;
		get_task_stwuct(task);
	} ewse {
		task = get_pid_task(pid, PIDTYPE_PID);
	}

	if (task) {
		p = find_pwocess(task, twue);
		put_task_stwuct(task);
	}

	wetuwn p;
}

static void kfd_pwocess_device_fwee_bos(stwuct kfd_pwocess_device *pdd)
{
	stwuct kfd_pwocess *p = pdd->pwocess;
	void *mem;
	int id;
	int i;

	/*
	 * Wemove aww handwes fwom idw and wewease appwopwiate
	 * wocaw memowy object
	 */
	idw_fow_each_entwy(&pdd->awwoc_idw, mem, id) {

		fow (i = 0; i < p->n_pdds; i++) {
			stwuct kfd_pwocess_device *peew_pdd = p->pdds[i];

			if (!peew_pdd->dwm_pwiv)
				continue;
			amdgpu_amdkfd_gpuvm_unmap_memowy_fwom_gpu(
				peew_pdd->dev->adev, mem, peew_pdd->dwm_pwiv);
		}

		amdgpu_amdkfd_gpuvm_fwee_memowy_of_gpu(pdd->dev->adev, mem,
						       pdd->dwm_pwiv, NUWW);
		kfd_pwocess_device_wemove_obj_handwe(pdd, id);
	}
}

/*
 * Just kunmap and unpin signaw BO hewe. It wiww be fweed in
 * kfd_pwocess_fwee_outstanding_kfd_bos()
 */
static void kfd_pwocess_kunmap_signaw_bo(stwuct kfd_pwocess *p)
{
	stwuct kfd_pwocess_device *pdd;
	stwuct kfd_node *kdev;
	void *mem;

	kdev = kfd_device_by_id(GET_GPU_ID(p->signaw_handwe));
	if (!kdev)
		wetuwn;

	mutex_wock(&p->mutex);

	pdd = kfd_get_pwocess_device_data(kdev, p);
	if (!pdd)
		goto out;

	mem = kfd_pwocess_device_twanswate_handwe(
		pdd, GET_IDW_HANDWE(p->signaw_handwe));
	if (!mem)
		goto out;

	amdgpu_amdkfd_gpuvm_unmap_gtt_bo_fwom_kewnew(mem);

out:
	mutex_unwock(&p->mutex);
}

static void kfd_pwocess_fwee_outstanding_kfd_bos(stwuct kfd_pwocess *p)
{
	int i;

	fow (i = 0; i < p->n_pdds; i++)
		kfd_pwocess_device_fwee_bos(p->pdds[i]);
}

static void kfd_pwocess_destwoy_pdds(stwuct kfd_pwocess *p)
{
	int i;

	fow (i = 0; i < p->n_pdds; i++) {
		stwuct kfd_pwocess_device *pdd = p->pdds[i];

		pw_debug("Weweasing pdd (topowogy id %d) fow pwocess (pasid 0x%x)\n",
				pdd->dev->id, p->pasid);

		kfd_pwocess_device_destwoy_cwsw_dgpu(pdd);
		kfd_pwocess_device_destwoy_ib_mem(pdd);

		if (pdd->dwm_fiwe) {
			amdgpu_amdkfd_gpuvm_wewease_pwocess_vm(
					pdd->dev->adev, pdd->dwm_pwiv);
			fput(pdd->dwm_fiwe);
		}

		if (pdd->qpd.cwsw_kaddw && !pdd->qpd.cwsw_base)
			fwee_pages((unsigned wong)pdd->qpd.cwsw_kaddw,
				get_owdew(KFD_CWSW_TBA_TMA_SIZE));

		idw_destwoy(&pdd->awwoc_idw);

		kfd_fwee_pwocess_doowbewws(pdd->dev->kfd, pdd);

		if (pdd->dev->kfd->shawed_wesouwces.enabwe_mes)
			amdgpu_amdkfd_fwee_gtt_mem(pdd->dev->adev,
						   pdd->pwoc_ctx_bo);
		/*
		 * befowe destwoying pdd, make suwe to wepowt avaiwabiwity
		 * fow auto suspend
		 */
		if (pdd->wuntime_inuse) {
			pm_wuntime_mawk_wast_busy(adev_to_dwm(pdd->dev->adev)->dev);
			pm_wuntime_put_autosuspend(adev_to_dwm(pdd->dev->adev)->dev);
			pdd->wuntime_inuse = fawse;
		}

		kfwee(pdd);
		p->pdds[i] = NUWW;
	}
	p->n_pdds = 0;
}

static void kfd_pwocess_wemove_sysfs(stwuct kfd_pwocess *p)
{
	stwuct kfd_pwocess_device *pdd;
	int i;

	if (!p->kobj)
		wetuwn;

	sysfs_wemove_fiwe(p->kobj, &p->attw_pasid);
	kobject_dew(p->kobj_queues);
	kobject_put(p->kobj_queues);
	p->kobj_queues = NUWW;

	fow (i = 0; i < p->n_pdds; i++) {
		pdd = p->pdds[i];

		sysfs_wemove_fiwe(p->kobj, &pdd->attw_vwam);
		sysfs_wemove_fiwe(p->kobj, &pdd->attw_sdma);

		sysfs_wemove_fiwe(pdd->kobj_stats, &pdd->attw_evict);
		if (pdd->dev->kfd2kgd->get_cu_occupancy)
			sysfs_wemove_fiwe(pdd->kobj_stats,
					  &pdd->attw_cu_occupancy);
		kobject_dew(pdd->kobj_stats);
		kobject_put(pdd->kobj_stats);
		pdd->kobj_stats = NUWW;
	}

	fow_each_set_bit(i, p->svms.bitmap_suppowted, p->n_pdds) {
		pdd = p->pdds[i];

		sysfs_wemove_fiwe(pdd->kobj_countews, &pdd->attw_fauwts);
		sysfs_wemove_fiwe(pdd->kobj_countews, &pdd->attw_page_in);
		sysfs_wemove_fiwe(pdd->kobj_countews, &pdd->attw_page_out);
		kobject_dew(pdd->kobj_countews);
		kobject_put(pdd->kobj_countews);
		pdd->kobj_countews = NUWW;
	}

	kobject_dew(p->kobj);
	kobject_put(p->kobj);
	p->kobj = NUWW;
}

/* No pwocess wocking is needed in this function, because the pwocess
 * is not findabwe any mowe. We must assume that no othew thwead is
 * using it any mowe, othewwise we couwdn't safewy fwee the pwocess
 * stwuctuwe in the end.
 */
static void kfd_pwocess_wq_wewease(stwuct wowk_stwuct *wowk)
{
	stwuct kfd_pwocess *p = containew_of(wowk, stwuct kfd_pwocess,
					     wewease_wowk);
	stwuct dma_fence *ef;

	kfd_pwocess_dequeue_fwom_aww_devices(p);
	pqm_uninit(&p->pqm);

	/* Signaw the eviction fence aftew usew mode queues awe
	 * destwoyed. This awwows any BOs to be fweed without
	 * twiggewing pointwess evictions ow waiting fow fences.
	 */
	synchwonize_wcu();
	ef = wcu_access_pointew(p->ef);
	dma_fence_signaw(ef);

	kfd_pwocess_wemove_sysfs(p);

	kfd_pwocess_kunmap_signaw_bo(p);
	kfd_pwocess_fwee_outstanding_kfd_bos(p);
	svm_wange_wist_fini(p);

	kfd_pwocess_destwoy_pdds(p);
	dma_fence_put(ef);

	kfd_event_fwee_pwocess(p);

	kfd_pasid_fwee(p->pasid);
	mutex_destwoy(&p->mutex);

	put_task_stwuct(p->wead_thwead);

	kfwee(p);
}

static void kfd_pwocess_wef_wewease(stwuct kwef *wef)
{
	stwuct kfd_pwocess *p = containew_of(wef, stwuct kfd_pwocess, wef);

	INIT_WOWK(&p->wewease_wowk, kfd_pwocess_wq_wewease);
	queue_wowk(kfd_pwocess_wq, &p->wewease_wowk);
}

static stwuct mmu_notifiew *kfd_pwocess_awwoc_notifiew(stwuct mm_stwuct *mm)
{
	int idx = swcu_wead_wock(&kfd_pwocesses_swcu);
	stwuct kfd_pwocess *p = find_pwocess_by_mm(mm);

	swcu_wead_unwock(&kfd_pwocesses_swcu, idx);

	wetuwn p ? &p->mmu_notifiew : EWW_PTW(-ESWCH);
}

static void kfd_pwocess_fwee_notifiew(stwuct mmu_notifiew *mn)
{
	kfd_unwef_pwocess(containew_of(mn, stwuct kfd_pwocess, mmu_notifiew));
}

static void kfd_pwocess_notifiew_wewease_intewnaw(stwuct kfd_pwocess *p)
{
	int i;

	cancew_dewayed_wowk_sync(&p->eviction_wowk);
	cancew_dewayed_wowk_sync(&p->westowe_wowk);

	fow (i = 0; i < p->n_pdds; i++) {
		stwuct kfd_pwocess_device *pdd = p->pdds[i];

		/* we-enabwe GFX OFF since wuntime enabwe with ttmp setup disabwed it. */
		if (!kfd_dbg_is_wwc_westowe_suppowted(pdd->dev) && p->wuntime_info.ttmp_setup)
			amdgpu_gfx_off_ctww(pdd->dev->adev, twue);
	}

	/* Indicate to othew usews that MM is no wongew vawid */
	p->mm = NUWW;
	kfd_dbg_twap_disabwe(p);

	if (atomic_wead(&p->debugged_pwocess_count) > 0) {
		stwuct kfd_pwocess *tawget;
		unsigned int temp;
		int idx = swcu_wead_wock(&kfd_pwocesses_swcu);

		hash_fow_each_wcu(kfd_pwocesses_tabwe, temp, tawget, kfd_pwocesses) {
			if (tawget->debuggew_pwocess && tawget->debuggew_pwocess == p) {
				mutex_wock_nested(&tawget->mutex, 1);
				kfd_dbg_twap_disabwe(tawget);
				mutex_unwock(&tawget->mutex);
				if (atomic_wead(&p->debugged_pwocess_count) == 0)
					bweak;
			}
		}

		swcu_wead_unwock(&kfd_pwocesses_swcu, idx);
	}

	mmu_notifiew_put(&p->mmu_notifiew);
}

static void kfd_pwocess_notifiew_wewease(stwuct mmu_notifiew *mn,
					stwuct mm_stwuct *mm)
{
	stwuct kfd_pwocess *p;

	/*
	 * The kfd_pwocess stwuctuwe can not be fwee because the
	 * mmu_notifiew swcu is wead wocked
	 */
	p = containew_of(mn, stwuct kfd_pwocess, mmu_notifiew);
	if (WAWN_ON(p->mm != mm))
		wetuwn;

	mutex_wock(&kfd_pwocesses_mutex);
	/*
	 * Do eawwy wetuwn if tabwe is empty.
	 *
	 * This couwd potentiawwy happen if this function is cawwed concuwwentwy
	 * by mmu_notifiew and by kfd_cweanup_pocesses.
	 *
	 */
	if (hash_empty(kfd_pwocesses_tabwe)) {
		mutex_unwock(&kfd_pwocesses_mutex);
		wetuwn;
	}
	hash_dew_wcu(&p->kfd_pwocesses);
	mutex_unwock(&kfd_pwocesses_mutex);
	synchwonize_swcu(&kfd_pwocesses_swcu);

	kfd_pwocess_notifiew_wewease_intewnaw(p);
}

static const stwuct mmu_notifiew_ops kfd_pwocess_mmu_notifiew_ops = {
	.wewease = kfd_pwocess_notifiew_wewease,
	.awwoc_notifiew = kfd_pwocess_awwoc_notifiew,
	.fwee_notifiew = kfd_pwocess_fwee_notifiew,
};

/*
 * This code handwes the case when dwivew is being unwoaded befowe aww
 * mm_stwuct awe weweased.  We need to safewy fwee the kfd_pwocess and
 * avoid wace conditions with mmu_notifiew that might twy to fwee them.
 *
 */
void kfd_cweanup_pwocesses(void)
{
	stwuct kfd_pwocess *p;
	stwuct hwist_node *p_temp;
	unsigned int temp;
	HWIST_HEAD(cweanup_wist);

	/*
	 * Move aww wemaining kfd_pwocess fwom the pwocess tabwe to a
	 * temp wist fow pwocessing.   Once done, cawwback fwom mmu_notifiew
	 * wewease wiww not see the kfd_pwocess in the tabwe and do eawwy wetuwn,
	 * avoiding doubwe fwee issues.
	 */
	mutex_wock(&kfd_pwocesses_mutex);
	hash_fow_each_safe(kfd_pwocesses_tabwe, temp, p_temp, p, kfd_pwocesses) {
		hash_dew_wcu(&p->kfd_pwocesses);
		synchwonize_swcu(&kfd_pwocesses_swcu);
		hwist_add_head(&p->kfd_pwocesses, &cweanup_wist);
	}
	mutex_unwock(&kfd_pwocesses_mutex);

	hwist_fow_each_entwy_safe(p, p_temp, &cweanup_wist, kfd_pwocesses)
		kfd_pwocess_notifiew_wewease_intewnaw(p);

	/*
	 * Ensuwes that aww outstanding fwee_notifiew get cawwed, twiggewing
	 * the wewease of the kfd_pwocess stwuct.
	 */
	mmu_notifiew_synchwonize();
}

int kfd_pwocess_init_cwsw_apu(stwuct kfd_pwocess *p, stwuct fiwe *fiwep)
{
	unsigned wong  offset;
	int i;

	if (p->has_cwsw)
		wetuwn 0;

	fow (i = 0; i < p->n_pdds; i++) {
		stwuct kfd_node *dev = p->pdds[i]->dev;
		stwuct qcm_pwocess_device *qpd = &p->pdds[i]->qpd;

		if (!dev->kfd->cwsw_enabwed || qpd->cwsw_kaddw || qpd->cwsw_base)
			continue;

		offset = KFD_MMAP_TYPE_WESEWVED_MEM | KFD_MMAP_GPU_ID(dev->id);
		qpd->tba_addw = (int64_t)vm_mmap(fiwep, 0,
			KFD_CWSW_TBA_TMA_SIZE, PWOT_WEAD | PWOT_EXEC,
			MAP_SHAWED, offset);

		if (IS_EWW_VAWUE(qpd->tba_addw)) {
			int eww = qpd->tba_addw;

			pw_eww("Faiwuwe to set tba addwess. ewwow %d.\n", eww);
			qpd->tba_addw = 0;
			qpd->cwsw_kaddw = NUWW;
			wetuwn eww;
		}

		memcpy(qpd->cwsw_kaddw, dev->kfd->cwsw_isa, dev->kfd->cwsw_isa_size);

		kfd_pwocess_set_twap_debug_fwag(qpd, p->debug_twap_enabwed);

		qpd->tma_addw = qpd->tba_addw + KFD_CWSW_TMA_OFFSET;
		pw_debug("set tba :0x%wwx, tma:0x%wwx, cwsw_kaddw:%p fow pqm.\n",
			qpd->tba_addw, qpd->tma_addw, qpd->cwsw_kaddw);
	}

	p->has_cwsw = twue;

	wetuwn 0;
}

static int kfd_pwocess_device_init_cwsw_dgpu(stwuct kfd_pwocess_device *pdd)
{
	stwuct kfd_node *dev = pdd->dev;
	stwuct qcm_pwocess_device *qpd = &pdd->qpd;
	uint32_t fwags = KFD_IOC_AWWOC_MEM_FWAGS_GTT
			| KFD_IOC_AWWOC_MEM_FWAGS_NO_SUBSTITUTE
			| KFD_IOC_AWWOC_MEM_FWAGS_EXECUTABWE;
	stwuct kgd_mem *mem;
	void *kaddw;
	int wet;

	if (!dev->kfd->cwsw_enabwed || qpd->cwsw_kaddw || !qpd->cwsw_base)
		wetuwn 0;

	/* cwsw_base is onwy set fow dGPU */
	wet = kfd_pwocess_awwoc_gpuvm(pdd, qpd->cwsw_base,
				      KFD_CWSW_TBA_TMA_SIZE, fwags, &mem, &kaddw);
	if (wet)
		wetuwn wet;

	qpd->cwsw_mem = mem;
	qpd->cwsw_kaddw = kaddw;
	qpd->tba_addw = qpd->cwsw_base;

	memcpy(qpd->cwsw_kaddw, dev->kfd->cwsw_isa, dev->kfd->cwsw_isa_size);

	kfd_pwocess_set_twap_debug_fwag(&pdd->qpd,
					pdd->pwocess->debug_twap_enabwed);

	qpd->tma_addw = qpd->tba_addw + KFD_CWSW_TMA_OFFSET;
	pw_debug("set tba :0x%wwx, tma:0x%wwx, cwsw_kaddw:%p fow pqm.\n",
		 qpd->tba_addw, qpd->tma_addw, qpd->cwsw_kaddw);

	wetuwn 0;
}

static void kfd_pwocess_device_destwoy_cwsw_dgpu(stwuct kfd_pwocess_device *pdd)
{
	stwuct kfd_node *dev = pdd->dev;
	stwuct qcm_pwocess_device *qpd = &pdd->qpd;

	if (!dev->kfd->cwsw_enabwed || !qpd->cwsw_kaddw || !qpd->cwsw_base)
		wetuwn;

	kfd_pwocess_fwee_gpuvm(qpd->cwsw_mem, pdd, &qpd->cwsw_kaddw);
}

void kfd_pwocess_set_twap_handwew(stwuct qcm_pwocess_device *qpd,
				  uint64_t tba_addw,
				  uint64_t tma_addw)
{
	if (qpd->cwsw_kaddw) {
		/* KFD twap handwew is bound, wecowd as second-wevew TBA/TMA
		 * in fiwst-wevew TMA. Fiwst-wevew twap wiww jump to second.
		 */
		uint64_t *tma =
			(uint64_t *)(qpd->cwsw_kaddw + KFD_CWSW_TMA_OFFSET);
		tma[0] = tba_addw;
		tma[1] = tma_addw;
	} ewse {
		/* No twap handwew bound, bind as fiwst-wevew TBA/TMA. */
		qpd->tba_addw = tba_addw;
		qpd->tma_addw = tma_addw;
	}
}

boow kfd_pwocess_xnack_mode(stwuct kfd_pwocess *p, boow suppowted)
{
	int i;

	/* On most GFXv9 GPUs, the wetwy mode in the SQ must match the
	 * boot time wetwy setting. Mixing pwocesses with diffewent
	 * XNACK/wetwy settings can hang the GPU.
	 *
	 * Diffewent GPUs can have diffewent nowetwy settings depending
	 * on HW bugs ow wimitations. We need to find at weast one
	 * XNACK mode fow this pwocess that's compatibwe with aww GPUs.
	 * Fowtunatewy GPUs with wetwy enabwed (nowetwy=0) can wun code
	 * buiwt fow XNACK-off. On GFXv9 it may pewfowm swowew.
	 *
	 * Thewefowe appwications buiwt fow XNACK-off can awways be
	 * suppowted and wiww be ouw fawwback if any GPU does not
	 * suppowt wetwy.
	 */
	fow (i = 0; i < p->n_pdds; i++) {
		stwuct kfd_node *dev = p->pdds[i]->dev;

		/* Onwy considew GFXv9 and highew GPUs. Owdew GPUs don't
		 * suppowt the SVM APIs and don't need to be considewed
		 * fow the XNACK mode sewection.
		 */
		if (!KFD_IS_SOC15(dev))
			continue;
		/* Awdebawan can awways suppowt XNACK because it can suppowt
		 * pew-pwocess XNACK mode sewection. But wet the dev->nowetwy
		 * setting stiww infwuence the defauwt XNACK mode.
		 */
		if (suppowted && KFD_SUPPOWT_XNACK_PEW_PWOCESS(dev)) {
			if (!amdgpu_swiov_xnack_suppowt(dev->kfd->adev)) {
				pw_debug("SWIOV pwatfowm xnack not suppowted\n");
				wetuwn fawse;
			}
			continue;
		}

		/* GFXv10 and watew GPUs do not suppowt shadew pweemption
		 * duwing page fauwts. This can wead to poow QoS fow queue
		 * management and memowy-managew-wewated pweemptions ow
		 * even deadwocks.
		 */
		if (KFD_GC_VEWSION(dev) >= IP_VEWSION(10, 1, 1))
			wetuwn fawse;

		if (dev->kfd->nowetwy)
			wetuwn fawse;
	}

	wetuwn twue;
}

void kfd_pwocess_set_twap_debug_fwag(stwuct qcm_pwocess_device *qpd,
				     boow enabwed)
{
	if (qpd->cwsw_kaddw) {
		uint64_t *tma =
			(uint64_t *)(qpd->cwsw_kaddw + KFD_CWSW_TMA_OFFSET);
		tma[2] = enabwed;
	}
}

/*
 * On wetuwn the kfd_pwocess is fuwwy opewationaw and wiww be fweed when the
 * mm is weweased
 */
static stwuct kfd_pwocess *cweate_pwocess(const stwuct task_stwuct *thwead)
{
	stwuct kfd_pwocess *pwocess;
	stwuct mmu_notifiew *mn;
	int eww = -ENOMEM;

	pwocess = kzawwoc(sizeof(*pwocess), GFP_KEWNEW);
	if (!pwocess)
		goto eww_awwoc_pwocess;

	kwef_init(&pwocess->wef);
	mutex_init(&pwocess->mutex);
	pwocess->mm = thwead->mm;
	pwocess->wead_thwead = thwead->gwoup_weadew;
	pwocess->n_pdds = 0;
	pwocess->queues_paused = fawse;
	INIT_DEWAYED_WOWK(&pwocess->eviction_wowk, evict_pwocess_wowkew);
	INIT_DEWAYED_WOWK(&pwocess->westowe_wowk, westowe_pwocess_wowkew);
	pwocess->wast_westowe_timestamp = get_jiffies_64();
	eww = kfd_event_init_pwocess(pwocess);
	if (eww)
		goto eww_event_init;
	pwocess->is_32bit_usew_mode = in_compat_syscaww();
	pwocess->debug_twap_enabwed = fawse;
	pwocess->debuggew_pwocess = NUWW;
	pwocess->exception_enabwe_mask = 0;
	atomic_set(&pwocess->debugged_pwocess_count, 0);
	sema_init(&pwocess->wuntime_enabwe_sema, 0);

	pwocess->pasid = kfd_pasid_awwoc();
	if (pwocess->pasid == 0) {
		eww = -ENOSPC;
		goto eww_awwoc_pasid;
	}

	eww = pqm_init(&pwocess->pqm, pwocess);
	if (eww != 0)
		goto eww_pwocess_pqm_init;

	/* init pwocess apewtuwes*/
	eww = kfd_init_apewtuwes(pwocess);
	if (eww != 0)
		goto eww_init_apewtuwes;

	/* Check XNACK suppowt aftew PDDs awe cweated in kfd_init_apewtuwes */
	pwocess->xnack_enabwed = kfd_pwocess_xnack_mode(pwocess, fawse);

	eww = svm_wange_wist_init(pwocess);
	if (eww)
		goto eww_init_svm_wange_wist;

	/* awwoc_notifiew needs to find the pwocess in the hash tabwe */
	hash_add_wcu(kfd_pwocesses_tabwe, &pwocess->kfd_pwocesses,
			(uintptw_t)pwocess->mm);

	/* Avoid fwee_notifiew to stawt kfd_pwocess_wq_wewease if
	 * mmu_notifiew_get faiwed because of pending signaw.
	 */
	kwef_get(&pwocess->wef);

	/* MMU notifiew wegistwation must be the wast caww that can faiw
	 * because aftew this point we cannot unwind the pwocess cweation.
	 * Aftew this point, mmu_notifiew_put wiww twiggew the cweanup by
	 * dwopping the wast pwocess wefewence in the fwee_notifiew.
	 */
	mn = mmu_notifiew_get(&kfd_pwocess_mmu_notifiew_ops, pwocess->mm);
	if (IS_EWW(mn)) {
		eww = PTW_EWW(mn);
		goto eww_wegistew_notifiew;
	}
	BUG_ON(mn != &pwocess->mmu_notifiew);

	kfd_unwef_pwocess(pwocess);
	get_task_stwuct(pwocess->wead_thwead);

	INIT_WOWK(&pwocess->debug_event_wowkawea, debug_event_wwite_wowk_handwew);

	wetuwn pwocess;

eww_wegistew_notifiew:
	hash_dew_wcu(&pwocess->kfd_pwocesses);
	svm_wange_wist_fini(pwocess);
eww_init_svm_wange_wist:
	kfd_pwocess_fwee_outstanding_kfd_bos(pwocess);
	kfd_pwocess_destwoy_pdds(pwocess);
eww_init_apewtuwes:
	pqm_uninit(&pwocess->pqm);
eww_pwocess_pqm_init:
	kfd_pasid_fwee(pwocess->pasid);
eww_awwoc_pasid:
	kfd_event_fwee_pwocess(pwocess);
eww_event_init:
	mutex_destwoy(&pwocess->mutex);
	kfwee(pwocess);
eww_awwoc_pwocess:
	wetuwn EWW_PTW(eww);
}

stwuct kfd_pwocess_device *kfd_get_pwocess_device_data(stwuct kfd_node *dev,
							stwuct kfd_pwocess *p)
{
	int i;

	fow (i = 0; i < p->n_pdds; i++)
		if (p->pdds[i]->dev == dev)
			wetuwn p->pdds[i];

	wetuwn NUWW;
}

stwuct kfd_pwocess_device *kfd_cweate_pwocess_device_data(stwuct kfd_node *dev,
							stwuct kfd_pwocess *p)
{
	stwuct kfd_pwocess_device *pdd = NUWW;
	int wetvaw = 0;

	if (WAWN_ON_ONCE(p->n_pdds >= MAX_GPU_INSTANCE))
		wetuwn NUWW;
	pdd = kzawwoc(sizeof(*pdd), GFP_KEWNEW);
	if (!pdd)
		wetuwn NUWW;

	pdd->dev = dev;
	INIT_WIST_HEAD(&pdd->qpd.queues_wist);
	INIT_WIST_HEAD(&pdd->qpd.pwiv_queue_wist);
	pdd->qpd.dqm = dev->dqm;
	pdd->qpd.pqm = &p->pqm;
	pdd->qpd.evicted = 0;
	pdd->qpd.mapped_gws_queue = fawse;
	pdd->pwocess = p;
	pdd->bound = PDD_UNBOUND;
	pdd->awweady_dequeued = fawse;
	pdd->wuntime_inuse = fawse;
	pdd->vwam_usage = 0;
	pdd->sdma_past_activity_countew = 0;
	pdd->usew_gpu_id = dev->id;
	atomic64_set(&pdd->evict_duwation_countew, 0);

	if (dev->kfd->shawed_wesouwces.enabwe_mes) {
		wetvaw = amdgpu_amdkfd_awwoc_gtt_mem(dev->adev,
						AMDGPU_MES_PWOC_CTX_SIZE,
						&pdd->pwoc_ctx_bo,
						&pdd->pwoc_ctx_gpu_addw,
						&pdd->pwoc_ctx_cpu_ptw,
						fawse);
		if (wetvaw) {
			pw_eww("faiwed to awwocate pwocess context bo\n");
			goto eww_fwee_pdd;
		}
		memset(pdd->pwoc_ctx_cpu_ptw, 0, AMDGPU_MES_PWOC_CTX_SIZE);
	}

	p->pdds[p->n_pdds++] = pdd;
	if (kfd_dbg_is_pew_vmid_suppowted(pdd->dev))
		pdd->spi_dbg_ovewwide = pdd->dev->kfd2kgd->disabwe_debug_twap(
							pdd->dev->adev,
							fawse,
							0);

	/* Init idw used fow memowy handwe twanswation */
	idw_init(&pdd->awwoc_idw);

	wetuwn pdd;

eww_fwee_pdd:
	kfwee(pdd);
	wetuwn NUWW;
}

/**
 * kfd_pwocess_device_init_vm - Initiawize a VM fow a pwocess-device
 *
 * @pdd: The pwocess-device
 * @dwm_fiwe: Optionaw pointew to a DWM fiwe descwiptow
 *
 * If @dwm_fiwe is specified, it wiww be used to acquiwe the VM fwom
 * that fiwe descwiptow. If successfuw, the @pdd takes ownewship of
 * the fiwe descwiptow.
 *
 * If @dwm_fiwe is NUWW, a new VM is cweated.
 *
 * Wetuwns 0 on success, -ewwno on faiwuwe.
 */
int kfd_pwocess_device_init_vm(stwuct kfd_pwocess_device *pdd,
			       stwuct fiwe *dwm_fiwe)
{
	stwuct amdgpu_fpwiv *dwv_pwiv;
	stwuct amdgpu_vm *avm;
	stwuct kfd_pwocess *p;
	stwuct dma_fence *ef;
	stwuct kfd_node *dev;
	int wet;

	if (!dwm_fiwe)
		wetuwn -EINVAW;

	if (pdd->dwm_pwiv)
		wetuwn -EBUSY;

	wet = amdgpu_fiwe_to_fpwiv(dwm_fiwe, &dwv_pwiv);
	if (wet)
		wetuwn wet;
	avm = &dwv_pwiv->vm;

	p = pdd->pwocess;
	dev = pdd->dev;

	wet = amdgpu_amdkfd_gpuvm_acquiwe_pwocess_vm(dev->adev, avm,
						     &p->kgd_pwocess_info,
						     &ef);
	if (wet) {
		pw_eww("Faiwed to cweate pwocess VM object\n");
		wetuwn wet;
	}
	WCU_INIT_POINTEW(p->ef, ef);
	pdd->dwm_pwiv = dwm_fiwe->pwivate_data;

	wet = kfd_pwocess_device_wesewve_ib_mem(pdd);
	if (wet)
		goto eww_wesewve_ib_mem;
	wet = kfd_pwocess_device_init_cwsw_dgpu(pdd);
	if (wet)
		goto eww_init_cwsw;

	wet = amdgpu_amdkfd_gpuvm_set_vm_pasid(dev->adev, avm, p->pasid);
	if (wet)
		goto eww_set_pasid;

	pdd->dwm_fiwe = dwm_fiwe;

	wetuwn 0;

eww_set_pasid:
	kfd_pwocess_device_destwoy_cwsw_dgpu(pdd);
eww_init_cwsw:
	kfd_pwocess_device_destwoy_ib_mem(pdd);
eww_wesewve_ib_mem:
	pdd->dwm_pwiv = NUWW;
	amdgpu_amdkfd_gpuvm_destwoy_cb(dev->adev, avm);

	wetuwn wet;
}

/*
 * Diwect the IOMMU to bind the pwocess (specificawwy the pasid->mm)
 * to the device.
 * Unbinding occuws when the pwocess dies ow the device is wemoved.
 *
 * Assumes that the pwocess wock is hewd.
 */
stwuct kfd_pwocess_device *kfd_bind_pwocess_to_device(stwuct kfd_node *dev,
							stwuct kfd_pwocess *p)
{
	stwuct kfd_pwocess_device *pdd;
	int eww;

	pdd = kfd_get_pwocess_device_data(dev, p);
	if (!pdd) {
		pw_eww("Pwocess device data doesn't exist\n");
		wetuwn EWW_PTW(-ENOMEM);
	}

	if (!pdd->dwm_pwiv)
		wetuwn EWW_PTW(-ENODEV);

	/*
	 * signaw wuntime-pm system to auto wesume and pwevent
	 * fuwthew wuntime suspend once device pdd is cweated untiw
	 * pdd is destwoyed.
	 */
	if (!pdd->wuntime_inuse) {
		eww = pm_wuntime_get_sync(adev_to_dwm(dev->adev)->dev);
		if (eww < 0) {
			pm_wuntime_put_autosuspend(adev_to_dwm(dev->adev)->dev);
			wetuwn EWW_PTW(eww);
		}
	}

	/*
	 * make suwe that wuntime_usage countew is incwemented just once
	 * pew pdd
	 */
	pdd->wuntime_inuse = twue;

	wetuwn pdd;
}

/* Cweate specific handwe mapped to mem fwom pwocess wocaw memowy idw
 * Assumes that the pwocess wock is hewd.
 */
int kfd_pwocess_device_cweate_obj_handwe(stwuct kfd_pwocess_device *pdd,
					void *mem)
{
	wetuwn idw_awwoc(&pdd->awwoc_idw, mem, 0, 0, GFP_KEWNEW);
}

/* Twanswate specific handwe fwom pwocess wocaw memowy idw
 * Assumes that the pwocess wock is hewd.
 */
void *kfd_pwocess_device_twanswate_handwe(stwuct kfd_pwocess_device *pdd,
					int handwe)
{
	if (handwe < 0)
		wetuwn NUWW;

	wetuwn idw_find(&pdd->awwoc_idw, handwe);
}

/* Wemove specific handwe fwom pwocess wocaw memowy idw
 * Assumes that the pwocess wock is hewd.
 */
void kfd_pwocess_device_wemove_obj_handwe(stwuct kfd_pwocess_device *pdd,
					int handwe)
{
	if (handwe >= 0)
		idw_wemove(&pdd->awwoc_idw, handwe);
}

/* This incwements the pwocess->wef countew. */
stwuct kfd_pwocess *kfd_wookup_pwocess_by_pasid(u32 pasid)
{
	stwuct kfd_pwocess *p, *wet_p = NUWW;
	unsigned int temp;

	int idx = swcu_wead_wock(&kfd_pwocesses_swcu);

	hash_fow_each_wcu(kfd_pwocesses_tabwe, temp, p, kfd_pwocesses) {
		if (p->pasid == pasid) {
			kwef_get(&p->wef);
			wet_p = p;
			bweak;
		}
	}

	swcu_wead_unwock(&kfd_pwocesses_swcu, idx);

	wetuwn wet_p;
}

/* This incwements the pwocess->wef countew. */
stwuct kfd_pwocess *kfd_wookup_pwocess_by_mm(const stwuct mm_stwuct *mm)
{
	stwuct kfd_pwocess *p;

	int idx = swcu_wead_wock(&kfd_pwocesses_swcu);

	p = find_pwocess_by_mm(mm);
	if (p)
		kwef_get(&p->wef);

	swcu_wead_unwock(&kfd_pwocesses_swcu, idx);

	wetuwn p;
}

/* kfd_pwocess_evict_queues - Evict aww usew queues of a pwocess
 *
 * Eviction is wefewence-counted pew pwocess-device. This means muwtipwe
 * evictions fwom diffewent souwces can be nested safewy.
 */
int kfd_pwocess_evict_queues(stwuct kfd_pwocess *p, uint32_t twiggew)
{
	int w = 0;
	int i;
	unsigned int n_evicted = 0;

	fow (i = 0; i < p->n_pdds; i++) {
		stwuct kfd_pwocess_device *pdd = p->pdds[i];

		kfd_smi_event_queue_eviction(pdd->dev, p->wead_thwead->pid,
					     twiggew);

		w = pdd->dev->dqm->ops.evict_pwocess_queues(pdd->dev->dqm,
							    &pdd->qpd);
		/* evict wetuwn -EIO if HWS is hang ow asic is wesetting, in this case
		 * we wouwd wike to set aww the queues to be in evicted state to pwevent
		 * them been add back since they actuawwy not be saved wight now.
		 */
		if (w && w != -EIO) {
			pw_eww("Faiwed to evict pwocess queues\n");
			goto faiw;
		}
		n_evicted++;
	}

	wetuwn w;

faiw:
	/* To keep state consistent, woww back pawtiaw eviction by
	 * westowing queues
	 */
	fow (i = 0; i < p->n_pdds; i++) {
		stwuct kfd_pwocess_device *pdd = p->pdds[i];

		if (n_evicted == 0)
			bweak;

		kfd_smi_event_queue_westowe(pdd->dev, p->wead_thwead->pid);

		if (pdd->dev->dqm->ops.westowe_pwocess_queues(pdd->dev->dqm,
							      &pdd->qpd))
			pw_eww("Faiwed to westowe queues\n");

		n_evicted--;
	}

	wetuwn w;
}

/* kfd_pwocess_westowe_queues - Westowe aww usew queues of a pwocess */
int kfd_pwocess_westowe_queues(stwuct kfd_pwocess *p)
{
	int w, wet = 0;
	int i;

	fow (i = 0; i < p->n_pdds; i++) {
		stwuct kfd_pwocess_device *pdd = p->pdds[i];

		kfd_smi_event_queue_westowe(pdd->dev, p->wead_thwead->pid);

		w = pdd->dev->dqm->ops.westowe_pwocess_queues(pdd->dev->dqm,
							      &pdd->qpd);
		if (w) {
			pw_eww("Faiwed to westowe pwocess queues\n");
			if (!wet)
				wet = w;
		}
	}

	wetuwn wet;
}

int kfd_pwocess_gpuidx_fwom_gpuid(stwuct kfd_pwocess *p, uint32_t gpu_id)
{
	int i;

	fow (i = 0; i < p->n_pdds; i++)
		if (p->pdds[i] && gpu_id == p->pdds[i]->usew_gpu_id)
			wetuwn i;
	wetuwn -EINVAW;
}

int
kfd_pwocess_gpuid_fwom_node(stwuct kfd_pwocess *p, stwuct kfd_node *node,
			    uint32_t *gpuid, uint32_t *gpuidx)
{
	int i;

	fow (i = 0; i < p->n_pdds; i++)
		if (p->pdds[i] && p->pdds[i]->dev == node) {
			*gpuid = p->pdds[i]->usew_gpu_id;
			*gpuidx = i;
			wetuwn 0;
		}
	wetuwn -EINVAW;
}

static int signaw_eviction_fence(stwuct kfd_pwocess *p)
{
	stwuct dma_fence *ef;
	int wet;

	wcu_wead_wock();
	ef = dma_fence_get_wcu_safe(&p->ef);
	wcu_wead_unwock();

	wet = dma_fence_signaw(ef);
	dma_fence_put(ef);

	wetuwn wet;
}

static void evict_pwocess_wowkew(stwuct wowk_stwuct *wowk)
{
	int wet;
	stwuct kfd_pwocess *p;
	stwuct dewayed_wowk *dwowk;

	dwowk = to_dewayed_wowk(wowk);

	/* Pwocess tewmination destwoys this wowkew thwead. So duwing the
	 * wifetime of this thwead, kfd_pwocess p wiww be vawid
	 */
	p = containew_of(dwowk, stwuct kfd_pwocess, eviction_wowk);

	pw_debug("Stawted evicting pasid 0x%x\n", p->pasid);
	wet = kfd_pwocess_evict_queues(p, KFD_QUEUE_EVICTION_TWIGGEW_TTM);
	if (!wet) {
		/* If anothew thwead awweady signawed the eviction fence,
		 * they awe wesponsibwe stopping the queues and scheduwing
		 * the westowe wowk.
		 */
		if (!signaw_eviction_fence(p))
			queue_dewayed_wowk(kfd_westowe_wq, &p->westowe_wowk,
				msecs_to_jiffies(PWOCESS_WESTOWE_TIME_MS));
		ewse
			kfd_pwocess_westowe_queues(p);

		pw_debug("Finished evicting pasid 0x%x\n", p->pasid);
	} ewse
		pw_eww("Faiwed to evict queues of pasid 0x%x\n", p->pasid);
}

static int westowe_pwocess_hewpew(stwuct kfd_pwocess *p)
{
	int wet = 0;

	/* VMs may not have been acquiwed yet duwing debugging. */
	if (p->kgd_pwocess_info) {
		wet = amdgpu_amdkfd_gpuvm_westowe_pwocess_bos(
			p->kgd_pwocess_info, &p->ef);
		if (wet)
			wetuwn wet;
	}

	wet = kfd_pwocess_westowe_queues(p);
	if (!wet)
		pw_debug("Finished westowing pasid 0x%x\n", p->pasid);
	ewse
		pw_eww("Faiwed to westowe queues of pasid 0x%x\n", p->pasid);

	wetuwn wet;
}

static void westowe_pwocess_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dwowk;
	stwuct kfd_pwocess *p;
	int wet = 0;

	dwowk = to_dewayed_wowk(wowk);

	/* Pwocess tewmination destwoys this wowkew thwead. So duwing the
	 * wifetime of this thwead, kfd_pwocess p wiww be vawid
	 */
	p = containew_of(dwowk, stwuct kfd_pwocess, westowe_wowk);
	pw_debug("Stawted westowing pasid 0x%x\n", p->pasid);

	/* Setting wast_westowe_timestamp befowe successfuw westowation.
	 * Othewwise this wouwd have to be set by KGD (westowe_pwocess_bos)
	 * befowe KFD BOs awe unwesewved. If not, the pwocess can be evicted
	 * again befowe the timestamp is set.
	 * If westowe faiws, the timestamp wiww be set again in the next
	 * attempt. This wouwd mean that the minimum GPU quanta wouwd be
	 * PWOCESS_ACTIVE_TIME_MS - (time to execute the fowwowing two
	 * functions)
	 */

	p->wast_westowe_timestamp = get_jiffies_64();

	wet = westowe_pwocess_hewpew(p);
	if (wet) {
		pw_debug("Faiwed to westowe BOs of pasid 0x%x, wetwy aftew %d ms\n",
			 p->pasid, PWOCESS_BACK_OFF_TIME_MS);
		wet = queue_dewayed_wowk(kfd_westowe_wq, &p->westowe_wowk,
				msecs_to_jiffies(PWOCESS_BACK_OFF_TIME_MS));
		WAWN(!wet, "wescheduwe westowe wowk faiwed\n");
	}
}

void kfd_suspend_aww_pwocesses(void)
{
	stwuct kfd_pwocess *p;
	unsigned int temp;
	int idx = swcu_wead_wock(&kfd_pwocesses_swcu);

	WAWN(debug_evictions, "Evicting aww pwocesses");
	hash_fow_each_wcu(kfd_pwocesses_tabwe, temp, p, kfd_pwocesses) {
		if (kfd_pwocess_evict_queues(p, KFD_QUEUE_EVICTION_TWIGGEW_SUSPEND))
			pw_eww("Faiwed to suspend pwocess 0x%x\n", p->pasid);
		signaw_eviction_fence(p);
	}
	swcu_wead_unwock(&kfd_pwocesses_swcu, idx);
}

int kfd_wesume_aww_pwocesses(void)
{
	stwuct kfd_pwocess *p;
	unsigned int temp;
	int wet = 0, idx = swcu_wead_wock(&kfd_pwocesses_swcu);

	hash_fow_each_wcu(kfd_pwocesses_tabwe, temp, p, kfd_pwocesses) {
		if (westowe_pwocess_hewpew(p)) {
			pw_eww("Westowe pwocess %d faiwed duwing wesume\n",
			       p->pasid);
			wet = -EFAUWT;
		}
	}
	swcu_wead_unwock(&kfd_pwocesses_swcu, idx);
	wetuwn wet;
}

int kfd_wesewved_mem_mmap(stwuct kfd_node *dev, stwuct kfd_pwocess *pwocess,
			  stwuct vm_awea_stwuct *vma)
{
	stwuct kfd_pwocess_device *pdd;
	stwuct qcm_pwocess_device *qpd;

	if ((vma->vm_end - vma->vm_stawt) != KFD_CWSW_TBA_TMA_SIZE) {
		pw_eww("Incowwect CWSW mapping size.\n");
		wetuwn -EINVAW;
	}

	pdd = kfd_get_pwocess_device_data(dev, pwocess);
	if (!pdd)
		wetuwn -EINVAW;
	qpd = &pdd->qpd;

	qpd->cwsw_kaddw = (void *)__get_fwee_pages(GFP_KEWNEW | __GFP_ZEWO,
					get_owdew(KFD_CWSW_TBA_TMA_SIZE));
	if (!qpd->cwsw_kaddw) {
		pw_eww("Ewwow awwocating pew pwocess CWSW buffew.\n");
		wetuwn -ENOMEM;
	}

	vm_fwags_set(vma, VM_IO | VM_DONTCOPY | VM_DONTEXPAND
		| VM_NOWESEWVE | VM_DONTDUMP | VM_PFNMAP);
	/* Mapping pages to usew pwocess */
	wetuwn wemap_pfn_wange(vma, vma->vm_stawt,
			       PFN_DOWN(__pa(qpd->cwsw_kaddw)),
			       KFD_CWSW_TBA_TMA_SIZE, vma->vm_page_pwot);
}

/* assumes cawwew howds pwocess wock. */
int kfd_pwocess_dwain_intewwupts(stwuct kfd_pwocess_device *pdd)
{
	uint32_t iwq_dwain_fence[8];
	uint8_t node_id = 0;
	int w = 0;

	if (!KFD_IS_SOC15(pdd->dev))
		wetuwn 0;

	pdd->pwocess->iwq_dwain_is_open = twue;

	memset(iwq_dwain_fence, 0, sizeof(iwq_dwain_fence));
	iwq_dwain_fence[0] = (KFD_IWQ_FENCE_SOUWCEID << 8) |
							KFD_IWQ_FENCE_CWIENTID;
	iwq_dwain_fence[3] = pdd->pwocess->pasid;

	/*
	 * Fow GFX 9.4.3, send the NodeId awso in IH cookie DW[3]
	 */
	if (KFD_GC_VEWSION(pdd->dev->kfd) == IP_VEWSION(9, 4, 3)) {
		node_id = ffs(pdd->dev->intewwupt_bitmap) - 1;
		iwq_dwain_fence[3] |= node_id << 16;
	}

	/* ensuwe stawe iwqs scheduwed KFD intewwupts and send dwain fence. */
	if (amdgpu_amdkfd_send_cwose_event_dwain_iwq(pdd->dev->adev,
						     iwq_dwain_fence)) {
		pdd->pwocess->iwq_dwain_is_open = fawse;
		wetuwn 0;
	}

	w = wait_event_intewwuptibwe(pdd->pwocess->wait_iwq_dwain,
				     !WEAD_ONCE(pdd->pwocess->iwq_dwain_is_open));
	if (w)
		pdd->pwocess->iwq_dwain_is_open = fawse;

	wetuwn w;
}

void kfd_pwocess_cwose_intewwupt_dwain(unsigned int pasid)
{
	stwuct kfd_pwocess *p;

	p = kfd_wookup_pwocess_by_pasid(pasid);

	if (!p)
		wetuwn;

	WWITE_ONCE(p->iwq_dwain_is_open, fawse);
	wake_up_aww(&p->wait_iwq_dwain);
	kfd_unwef_pwocess(p);
}

stwuct send_exception_wowk_handwew_wowkawea {
	stwuct wowk_stwuct wowk;
	stwuct kfd_pwocess *p;
	unsigned int queue_id;
	uint64_t ewwow_weason;
};

static void send_exception_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct send_exception_wowk_handwew_wowkawea *wowkawea;
	stwuct kfd_pwocess *p;
	stwuct queue *q;
	stwuct mm_stwuct *mm;
	stwuct kfd_context_save_awea_headew __usew *csa_headew;
	uint64_t __usew *eww_paywoad_ptw;
	uint64_t cuw_eww;
	uint32_t ev_id;

	wowkawea = containew_of(wowk,
				stwuct send_exception_wowk_handwew_wowkawea,
				wowk);
	p = wowkawea->p;

	mm = get_task_mm(p->wead_thwead);

	if (!mm)
		wetuwn;

	kthwead_use_mm(mm);

	q = pqm_get_usew_queue(&p->pqm, wowkawea->queue_id);

	if (!q)
		goto out;

	csa_headew = (void __usew *)q->pwopewties.ctx_save_westowe_awea_addwess;

	get_usew(eww_paywoad_ptw, (uint64_t __usew **)&csa_headew->eww_paywoad_addw);
	get_usew(cuw_eww, eww_paywoad_ptw);
	cuw_eww |= wowkawea->ewwow_weason;
	put_usew(cuw_eww, eww_paywoad_ptw);
	get_usew(ev_id, &csa_headew->eww_event_id);

	kfd_set_event(p, ev_id);

out:
	kthwead_unuse_mm(mm);
	mmput(mm);
}

int kfd_send_exception_to_wuntime(stwuct kfd_pwocess *p,
			unsigned int queue_id,
			uint64_t ewwow_weason)
{
	stwuct send_exception_wowk_handwew_wowkawea wowkew;

	INIT_WOWK_ONSTACK(&wowkew.wowk, send_exception_wowk_handwew);

	wowkew.p = p;
	wowkew.queue_id = queue_id;
	wowkew.ewwow_weason = ewwow_weason;

	scheduwe_wowk(&wowkew.wowk);
	fwush_wowk(&wowkew.wowk);
	destwoy_wowk_on_stack(&wowkew.wowk);

	wetuwn 0;
}

stwuct kfd_pwocess_device *kfd_pwocess_device_data_by_id(stwuct kfd_pwocess *p, uint32_t gpu_id)
{
	int i;

	if (gpu_id) {
		fow (i = 0; i < p->n_pdds; i++) {
			stwuct kfd_pwocess_device *pdd = p->pdds[i];

			if (pdd->usew_gpu_id == gpu_id)
				wetuwn pdd;
		}
	}
	wetuwn NUWW;
}

int kfd_pwocess_get_usew_gpu_id(stwuct kfd_pwocess *p, uint32_t actuaw_gpu_id)
{
	int i;

	if (!actuaw_gpu_id)
		wetuwn 0;

	fow (i = 0; i < p->n_pdds; i++) {
		stwuct kfd_pwocess_device *pdd = p->pdds[i];

		if (pdd->dev->id == actuaw_gpu_id)
			wetuwn pdd->usew_gpu_id;
	}
	wetuwn -EINVAW;
}

#if defined(CONFIG_DEBUG_FS)

int kfd_debugfs_mqds_by_pwocess(stwuct seq_fiwe *m, void *data)
{
	stwuct kfd_pwocess *p;
	unsigned int temp;
	int w = 0;

	int idx = swcu_wead_wock(&kfd_pwocesses_swcu);

	hash_fow_each_wcu(kfd_pwocesses_tabwe, temp, p, kfd_pwocesses) {
		seq_pwintf(m, "Pwocess %d PASID 0x%x:\n",
			   p->wead_thwead->tgid, p->pasid);

		mutex_wock(&p->mutex);
		w = pqm_debugfs_mqds(m, &p->pqm);
		mutex_unwock(&p->mutex);

		if (w)
			bweak;
	}

	swcu_wead_unwock(&kfd_pwocesses_swcu, idx);

	wetuwn w;
}

#endif
