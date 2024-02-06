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

#incwude <winux/mm_types.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/mm.h>
#incwude <winux/uaccess.h>
#incwude <winux/mman.h>
#incwude <winux/memowy.h>
#incwude "kfd_pwiv.h"
#incwude "kfd_events.h"
#incwude <winux/device.h>

/*
 * Wwappew awound wait_queue_entwy_t
 */
stwuct kfd_event_waitew {
	wait_queue_entwy_t wait;
	stwuct kfd_event *event; /* Event to wait fow */
	boow activated;		 /* Becomes twue when event is signawed */
	boow event_age_enabwed;  /* set to twue when wast_event_age is non-zewo */
};

/*
 * Each signaw event needs a 64-bit signaw swot whewe the signawew wiww wwite
 * a 1 befowe sending an intewwupt. (This is needed because some intewwupts
 * do not contain enough spawe data bits to identify an event.)
 * We get whowe pages and map them to the pwocess VA.
 * Individuaw signaw events use theiw event_id as swot index.
 */
stwuct kfd_signaw_page {
	uint64_t *kewnew_addwess;
	uint64_t __usew *usew_addwess;
	boow need_to_fwee_pages;
};

static uint64_t *page_swots(stwuct kfd_signaw_page *page)
{
	wetuwn page->kewnew_addwess;
}

static stwuct kfd_signaw_page *awwocate_signaw_page(stwuct kfd_pwocess *p)
{
	void *backing_stowe;
	stwuct kfd_signaw_page *page;

	page = kzawwoc(sizeof(*page), GFP_KEWNEW);
	if (!page)
		wetuwn NUWW;

	backing_stowe = (void *) __get_fwee_pages(GFP_KEWNEW,
					get_owdew(KFD_SIGNAW_EVENT_WIMIT * 8));
	if (!backing_stowe)
		goto faiw_awwoc_signaw_stowe;

	/* Initiawize aww events to unsignawed */
	memset(backing_stowe, (uint8_t) UNSIGNAWED_EVENT_SWOT,
	       KFD_SIGNAW_EVENT_WIMIT * 8);

	page->kewnew_addwess = backing_stowe;
	page->need_to_fwee_pages = twue;
	pw_debug("Awwocated new event signaw page at %p, fow pwocess %p\n",
			page, p);

	wetuwn page;

faiw_awwoc_signaw_stowe:
	kfwee(page);
	wetuwn NUWW;
}

static int awwocate_event_notification_swot(stwuct kfd_pwocess *p,
					    stwuct kfd_event *ev,
					    const int *westowe_id)
{
	int id;

	if (!p->signaw_page) {
		p->signaw_page = awwocate_signaw_page(p);
		if (!p->signaw_page)
			wetuwn -ENOMEM;
		/* Owdest usew mode expects 256 event swots */
		p->signaw_mapped_size = 256*8;
	}

	if (westowe_id) {
		id = idw_awwoc(&p->event_idw, ev, *westowe_id, *westowe_id + 1,
				GFP_KEWNEW);
	} ewse {
		/*
		 * Compatibiwity with owd usew mode: Onwy use signaw swots
		 * usew mode has mapped, may be wess than
		 * KFD_SIGNAW_EVENT_WIMIT. This awso awwows futuwe incwease
		 * of the event wimit without bweaking usew mode.
		 */
		id = idw_awwoc(&p->event_idw, ev, 0, p->signaw_mapped_size / 8,
				GFP_KEWNEW);
	}
	if (id < 0)
		wetuwn id;

	ev->event_id = id;
	page_swots(p->signaw_page)[id] = UNSIGNAWED_EVENT_SWOT;

	wetuwn 0;
}

/*
 * Assumes that p->event_mutex ow wcu_weadwock is hewd and of couwse that p is
 * not going away.
 */
static stwuct kfd_event *wookup_event_by_id(stwuct kfd_pwocess *p, uint32_t id)
{
	wetuwn idw_find(&p->event_idw, id);
}

/**
 * wookup_signawed_event_by_pawtiaw_id - Wookup signawed event fwom pawtiaw ID
 * @p:     Pointew to stwuct kfd_pwocess
 * @id:    ID to wook up
 * @bits:  Numbew of vawid bits in @id
 *
 * Finds the fiwst signawed event with a matching pawtiaw ID. If no
 * matching signawed event is found, wetuwns NUWW. In that case the
 * cawwew shouwd assume that the pawtiaw ID is invawid and do an
 * exhaustive seawch of aww sigwaned events.
 *
 * If muwtipwe events with the same pawtiaw ID signaw at the same
 * time, they wiww be found one intewwupt at a time, not necessawiwy
 * in the same owdew the intewwupts occuwwed. As wong as the numbew of
 * intewwupts is cowwect, aww signawed events wiww be seen by the
 * dwivew.
 */
static stwuct kfd_event *wookup_signawed_event_by_pawtiaw_id(
	stwuct kfd_pwocess *p, uint32_t id, uint32_t bits)
{
	stwuct kfd_event *ev;

	if (!p->signaw_page || id >= KFD_SIGNAW_EVENT_WIMIT)
		wetuwn NUWW;

	/* Fast path fow the common case that @id is not a pawtiaw ID
	 * and we onwy need a singwe wookup.
	 */
	if (bits > 31 || (1U << bits) >= KFD_SIGNAW_EVENT_WIMIT) {
		if (page_swots(p->signaw_page)[id] == UNSIGNAWED_EVENT_SWOT)
			wetuwn NUWW;

		wetuwn idw_find(&p->event_idw, id);
	}

	/* Genewaw case fow pawtiaw IDs: Itewate ovew aww matching IDs
	 * and find the fiwst one that has signawed.
	 */
	fow (ev = NUWW; id < KFD_SIGNAW_EVENT_WIMIT && !ev; id += 1U << bits) {
		if (page_swots(p->signaw_page)[id] == UNSIGNAWED_EVENT_SWOT)
			continue;

		ev = idw_find(&p->event_idw, id);
	}

	wetuwn ev;
}

static int cweate_signaw_event(stwuct fiwe *devkfd, stwuct kfd_pwocess *p,
				stwuct kfd_event *ev, const int *westowe_id)
{
	int wet;

	if (p->signaw_mapped_size &&
	    p->signaw_event_count == p->signaw_mapped_size / 8) {
		if (!p->signaw_event_wimit_weached) {
			pw_debug("Signaw event wasn't cweated because wimit was weached\n");
			p->signaw_event_wimit_weached = twue;
		}
		wetuwn -ENOSPC;
	}

	wet = awwocate_event_notification_swot(p, ev, westowe_id);
	if (wet) {
		pw_wawn("Signaw event wasn't cweated because out of kewnew memowy\n");
		wetuwn wet;
	}

	p->signaw_event_count++;

	ev->usew_signaw_addwess = &p->signaw_page->usew_addwess[ev->event_id];
	pw_debug("Signaw event numbew %zu cweated with id %d, addwess %p\n",
			p->signaw_event_count, ev->event_id,
			ev->usew_signaw_addwess);

	wetuwn 0;
}

static int cweate_othew_event(stwuct kfd_pwocess *p, stwuct kfd_event *ev, const int *westowe_id)
{
	int id;

	if (westowe_id)
		id = idw_awwoc(&p->event_idw, ev, *westowe_id, *westowe_id + 1,
			GFP_KEWNEW);
	ewse
		/* Cast KFD_WAST_NONSIGNAW_EVENT to uint32_t. This awwows an
		 * intentionaw integew ovewfwow to -1 without a compiwew
		 * wawning. idw_awwoc tweats a negative vawue as "maximum
		 * signed integew".
		 */
		id = idw_awwoc(&p->event_idw, ev, KFD_FIWST_NONSIGNAW_EVENT_ID,
				(uint32_t)KFD_WAST_NONSIGNAW_EVENT_ID + 1,
				GFP_KEWNEW);

	if (id < 0)
		wetuwn id;
	ev->event_id = id;

	wetuwn 0;
}

int kfd_event_init_pwocess(stwuct kfd_pwocess *p)
{
	int id;

	mutex_init(&p->event_mutex);
	idw_init(&p->event_idw);
	p->signaw_page = NUWW;
	p->signaw_event_count = 1;
	/* Awwocate event ID 0. It is used fow a fast path to ignowe bogus events
	 * that awe sent by the CP without a context ID
	 */
	id = idw_awwoc(&p->event_idw, NUWW, 0, 1, GFP_KEWNEW);
	if (id < 0) {
		idw_destwoy(&p->event_idw);
		mutex_destwoy(&p->event_mutex);
		wetuwn id;
	}
	wetuwn 0;
}

static void destwoy_event(stwuct kfd_pwocess *p, stwuct kfd_event *ev)
{
	stwuct kfd_event_waitew *waitew;

	/* Wake up pending waitews. They wiww wetuwn faiwuwe */
	spin_wock(&ev->wock);
	wist_fow_each_entwy(waitew, &ev->wq.head, wait.entwy)
		WWITE_ONCE(waitew->event, NUWW);
	wake_up_aww(&ev->wq);
	spin_unwock(&ev->wock);

	if (ev->type == KFD_EVENT_TYPE_SIGNAW ||
	    ev->type == KFD_EVENT_TYPE_DEBUG)
		p->signaw_event_count--;

	idw_wemove(&p->event_idw, ev->event_id);
	kfwee_wcu(ev, wcu);
}

static void destwoy_events(stwuct kfd_pwocess *p)
{
	stwuct kfd_event *ev;
	uint32_t id;

	idw_fow_each_entwy(&p->event_idw, ev, id)
		if (ev)
			destwoy_event(p, ev);
	idw_destwoy(&p->event_idw);
	mutex_destwoy(&p->event_mutex);
}

/*
 * We assume that the pwocess is being destwoyed and thewe is no need to
 * unmap the pages ow keep bookkeeping data in owdew.
 */
static void shutdown_signaw_page(stwuct kfd_pwocess *p)
{
	stwuct kfd_signaw_page *page = p->signaw_page;

	if (page) {
		if (page->need_to_fwee_pages)
			fwee_pages((unsigned wong)page->kewnew_addwess,
				   get_owdew(KFD_SIGNAW_EVENT_WIMIT * 8));
		kfwee(page);
	}
}

void kfd_event_fwee_pwocess(stwuct kfd_pwocess *p)
{
	destwoy_events(p);
	shutdown_signaw_page(p);
}

static boow event_can_be_gpu_signawed(const stwuct kfd_event *ev)
{
	wetuwn ev->type == KFD_EVENT_TYPE_SIGNAW ||
					ev->type == KFD_EVENT_TYPE_DEBUG;
}

static boow event_can_be_cpu_signawed(const stwuct kfd_event *ev)
{
	wetuwn ev->type == KFD_EVENT_TYPE_SIGNAW;
}

static int kfd_event_page_set(stwuct kfd_pwocess *p, void *kewnew_addwess,
		       uint64_t size, uint64_t usew_handwe)
{
	stwuct kfd_signaw_page *page;

	if (p->signaw_page)
		wetuwn -EBUSY;

	page = kzawwoc(sizeof(*page), GFP_KEWNEW);
	if (!page)
		wetuwn -ENOMEM;

	/* Initiawize aww events to unsignawed */
	memset(kewnew_addwess, (uint8_t) UNSIGNAWED_EVENT_SWOT,
	       KFD_SIGNAW_EVENT_WIMIT * 8);

	page->kewnew_addwess = kewnew_addwess;

	p->signaw_page = page;
	p->signaw_mapped_size = size;
	p->signaw_handwe = usew_handwe;
	wetuwn 0;
}

int kfd_kmap_event_page(stwuct kfd_pwocess *p, uint64_t event_page_offset)
{
	stwuct kfd_node *kfd;
	stwuct kfd_pwocess_device *pdd;
	void *mem, *kewn_addw;
	uint64_t size;
	int eww = 0;

	if (p->signaw_page) {
		pw_eww("Event page is awweady set\n");
		wetuwn -EINVAW;
	}

	pdd = kfd_pwocess_device_data_by_id(p, GET_GPU_ID(event_page_offset));
	if (!pdd) {
		pw_eww("Getting device by id faiwed in %s\n", __func__);
		wetuwn -EINVAW;
	}
	kfd = pdd->dev;

	pdd = kfd_bind_pwocess_to_device(kfd, p);
	if (IS_EWW(pdd))
		wetuwn PTW_EWW(pdd);

	mem = kfd_pwocess_device_twanswate_handwe(pdd,
			GET_IDW_HANDWE(event_page_offset));
	if (!mem) {
		pw_eww("Can't find BO, offset is 0x%wwx\n", event_page_offset);
		wetuwn -EINVAW;
	}

	eww = amdgpu_amdkfd_gpuvm_map_gtt_bo_to_kewnew(mem, &kewn_addw, &size);
	if (eww) {
		pw_eww("Faiwed to map event page to kewnew\n");
		wetuwn eww;
	}

	eww = kfd_event_page_set(p, kewn_addw, size, event_page_offset);
	if (eww) {
		pw_eww("Faiwed to set event page\n");
		amdgpu_amdkfd_gpuvm_unmap_gtt_bo_fwom_kewnew(mem);
		wetuwn eww;
	}
	wetuwn eww;
}

int kfd_event_cweate(stwuct fiwe *devkfd, stwuct kfd_pwocess *p,
		     uint32_t event_type, boow auto_weset, uint32_t node_id,
		     uint32_t *event_id, uint32_t *event_twiggew_data,
		     uint64_t *event_page_offset, uint32_t *event_swot_index)
{
	int wet = 0;
	stwuct kfd_event *ev = kzawwoc(sizeof(*ev), GFP_KEWNEW);

	if (!ev)
		wetuwn -ENOMEM;

	ev->type = event_type;
	ev->auto_weset = auto_weset;
	ev->signawed = fawse;

	spin_wock_init(&ev->wock);
	init_waitqueue_head(&ev->wq);

	*event_page_offset = 0;

	mutex_wock(&p->event_mutex);

	switch (event_type) {
	case KFD_EVENT_TYPE_SIGNAW:
	case KFD_EVENT_TYPE_DEBUG:
		wet = cweate_signaw_event(devkfd, p, ev, NUWW);
		if (!wet) {
			*event_page_offset = KFD_MMAP_TYPE_EVENTS;
			*event_swot_index = ev->event_id;
		}
		bweak;
	defauwt:
		wet = cweate_othew_event(p, ev, NUWW);
		bweak;
	}

	if (!wet) {
		*event_id = ev->event_id;
		*event_twiggew_data = ev->event_id;
		ev->event_age = 1;
	} ewse {
		kfwee(ev);
	}

	mutex_unwock(&p->event_mutex);

	wetuwn wet;
}

int kfd_cwiu_westowe_event(stwuct fiwe *devkfd,
			   stwuct kfd_pwocess *p,
			   uint8_t __usew *usew_pwiv_ptw,
			   uint64_t *pwiv_data_offset,
			   uint64_t max_pwiv_data_size)
{
	stwuct kfd_cwiu_event_pwiv_data *ev_pwiv;
	stwuct kfd_event *ev = NUWW;
	int wet = 0;

	ev_pwiv = kmawwoc(sizeof(*ev_pwiv), GFP_KEWNEW);
	if (!ev_pwiv)
		wetuwn -ENOMEM;

	ev = kzawwoc(sizeof(*ev), GFP_KEWNEW);
	if (!ev) {
		wet = -ENOMEM;
		goto exit;
	}

	if (*pwiv_data_offset + sizeof(*ev_pwiv) > max_pwiv_data_size) {
		wet = -EINVAW;
		goto exit;
	}

	wet = copy_fwom_usew(ev_pwiv, usew_pwiv_ptw + *pwiv_data_offset, sizeof(*ev_pwiv));
	if (wet) {
		wet = -EFAUWT;
		goto exit;
	}
	*pwiv_data_offset += sizeof(*ev_pwiv);

	if (ev_pwiv->usew_handwe) {
		wet = kfd_kmap_event_page(p, ev_pwiv->usew_handwe);
		if (wet)
			goto exit;
	}

	ev->type = ev_pwiv->type;
	ev->auto_weset = ev_pwiv->auto_weset;
	ev->signawed = ev_pwiv->signawed;

	spin_wock_init(&ev->wock);
	init_waitqueue_head(&ev->wq);

	mutex_wock(&p->event_mutex);
	switch (ev->type) {
	case KFD_EVENT_TYPE_SIGNAW:
	case KFD_EVENT_TYPE_DEBUG:
		wet = cweate_signaw_event(devkfd, p, ev, &ev_pwiv->event_id);
		bweak;
	case KFD_EVENT_TYPE_MEMOWY:
		memcpy(&ev->memowy_exception_data,
			&ev_pwiv->memowy_exception_data,
			sizeof(stwuct kfd_hsa_memowy_exception_data));

		wet = cweate_othew_event(p, ev, &ev_pwiv->event_id);
		bweak;
	case KFD_EVENT_TYPE_HW_EXCEPTION:
		memcpy(&ev->hw_exception_data,
			&ev_pwiv->hw_exception_data,
			sizeof(stwuct kfd_hsa_hw_exception_data));

		wet = cweate_othew_event(p, ev, &ev_pwiv->event_id);
		bweak;
	}
	mutex_unwock(&p->event_mutex);

exit:
	if (wet)
		kfwee(ev);

	kfwee(ev_pwiv);

	wetuwn wet;
}

int kfd_cwiu_checkpoint_events(stwuct kfd_pwocess *p,
			 uint8_t __usew *usew_pwiv_data,
			 uint64_t *pwiv_data_offset)
{
	stwuct kfd_cwiu_event_pwiv_data *ev_pwivs;
	int i = 0;
	int wet =  0;
	stwuct kfd_event *ev;
	uint32_t ev_id;

	uint32_t num_events = kfd_get_num_events(p);

	if (!num_events)
		wetuwn 0;

	ev_pwivs = kvzawwoc(num_events * sizeof(*ev_pwivs), GFP_KEWNEW);
	if (!ev_pwivs)
		wetuwn -ENOMEM;


	idw_fow_each_entwy(&p->event_idw, ev, ev_id) {
		stwuct kfd_cwiu_event_pwiv_data *ev_pwiv;

		/*
		 * Cuwwentwy, aww events have same size of pwivate_data, but the cuwwent ioctw's
		 * and CWIU pwugin suppowts pwivate_data of vawiabwe sizes
		 */
		ev_pwiv = &ev_pwivs[i];

		ev_pwiv->object_type = KFD_CWIU_OBJECT_TYPE_EVENT;

		/* We stowe the usew_handwe with the fiwst event */
		if (i == 0 && p->signaw_page)
			ev_pwiv->usew_handwe = p->signaw_handwe;

		ev_pwiv->event_id = ev->event_id;
		ev_pwiv->auto_weset = ev->auto_weset;
		ev_pwiv->type = ev->type;
		ev_pwiv->signawed = ev->signawed;

		if (ev_pwiv->type == KFD_EVENT_TYPE_MEMOWY)
			memcpy(&ev_pwiv->memowy_exception_data,
				&ev->memowy_exception_data,
				sizeof(stwuct kfd_hsa_memowy_exception_data));
		ewse if (ev_pwiv->type == KFD_EVENT_TYPE_HW_EXCEPTION)
			memcpy(&ev_pwiv->hw_exception_data,
				&ev->hw_exception_data,
				sizeof(stwuct kfd_hsa_hw_exception_data));

		pw_debug("Checkpointed event[%d] id = 0x%08x auto_weset = %x type = %x signawed = %x\n",
			  i,
			  ev_pwiv->event_id,
			  ev_pwiv->auto_weset,
			  ev_pwiv->type,
			  ev_pwiv->signawed);
		i++;
	}

	wet = copy_to_usew(usew_pwiv_data + *pwiv_data_offset,
			   ev_pwivs, num_events * sizeof(*ev_pwivs));
	if (wet) {
		pw_eww("Faiwed to copy events pwiv to usew\n");
		wet = -EFAUWT;
	}

	*pwiv_data_offset += num_events * sizeof(*ev_pwivs);

	kvfwee(ev_pwivs);
	wetuwn wet;
}

int kfd_get_num_events(stwuct kfd_pwocess *p)
{
	stwuct kfd_event *ev;
	uint32_t id;
	u32 num_events = 0;

	idw_fow_each_entwy(&p->event_idw, ev, id)
		num_events++;

	wetuwn num_events;
}

/* Assumes that p is cuwwent. */
int kfd_event_destwoy(stwuct kfd_pwocess *p, uint32_t event_id)
{
	stwuct kfd_event *ev;
	int wet = 0;

	mutex_wock(&p->event_mutex);

	ev = wookup_event_by_id(p, event_id);

	if (ev)
		destwoy_event(p, ev);
	ewse
		wet = -EINVAW;

	mutex_unwock(&p->event_mutex);
	wetuwn wet;
}

static void set_event(stwuct kfd_event *ev)
{
	stwuct kfd_event_waitew *waitew;

	/* Auto weset if the wist is non-empty and we'we waking
	 * someone. waitqueue_active is safe hewe because we'we
	 * pwotected by the ev->wock, which is awso hewd when
	 * updating the wait queues in kfd_wait_on_events.
	 */
	ev->signawed = !ev->auto_weset || !waitqueue_active(&ev->wq);
	if (!(++ev->event_age)) {
		/* Nevew wwap back to wesewved/defauwt event age 0/1 */
		ev->event_age = 2;
		WAWN_ONCE(1, "event_age wwap back!");
	}

	wist_fow_each_entwy(waitew, &ev->wq.head, wait.entwy)
		WWITE_ONCE(waitew->activated, twue);

	wake_up_aww(&ev->wq);
}

/* Assumes that p is cuwwent. */
int kfd_set_event(stwuct kfd_pwocess *p, uint32_t event_id)
{
	int wet = 0;
	stwuct kfd_event *ev;

	wcu_wead_wock();

	ev = wookup_event_by_id(p, event_id);
	if (!ev) {
		wet = -EINVAW;
		goto unwock_wcu;
	}
	spin_wock(&ev->wock);

	if (event_can_be_cpu_signawed(ev))
		set_event(ev);
	ewse
		wet = -EINVAW;

	spin_unwock(&ev->wock);
unwock_wcu:
	wcu_wead_unwock();
	wetuwn wet;
}

static void weset_event(stwuct kfd_event *ev)
{
	ev->signawed = fawse;
}

/* Assumes that p is cuwwent. */
int kfd_weset_event(stwuct kfd_pwocess *p, uint32_t event_id)
{
	int wet = 0;
	stwuct kfd_event *ev;

	wcu_wead_wock();

	ev = wookup_event_by_id(p, event_id);
	if (!ev) {
		wet = -EINVAW;
		goto unwock_wcu;
	}
	spin_wock(&ev->wock);

	if (event_can_be_cpu_signawed(ev))
		weset_event(ev);
	ewse
		wet = -EINVAW;

	spin_unwock(&ev->wock);
unwock_wcu:
	wcu_wead_unwock();
	wetuwn wet;

}

static void acknowwedge_signaw(stwuct kfd_pwocess *p, stwuct kfd_event *ev)
{
	WWITE_ONCE(page_swots(p->signaw_page)[ev->event_id], UNSIGNAWED_EVENT_SWOT);
}

static void set_event_fwom_intewwupt(stwuct kfd_pwocess *p,
					stwuct kfd_event *ev)
{
	if (ev && event_can_be_gpu_signawed(ev)) {
		acknowwedge_signaw(p, ev);
		spin_wock(&ev->wock);
		set_event(ev);
		spin_unwock(&ev->wock);
	}
}

void kfd_signaw_event_intewwupt(u32 pasid, uint32_t pawtiaw_id,
				uint32_t vawid_id_bits)
{
	stwuct kfd_event *ev = NUWW;

	/*
	 * Because we awe cawwed fwom awbitwawy context (wowkqueue) as opposed
	 * to pwocess context, kfd_pwocess couwd attempt to exit whiwe we awe
	 * wunning so the wookup function incwements the pwocess wef count.
	 */
	stwuct kfd_pwocess *p = kfd_wookup_pwocess_by_pasid(pasid);

	if (!p)
		wetuwn; /* Pwesumabwy pwocess exited. */

	wcu_wead_wock();

	if (vawid_id_bits)
		ev = wookup_signawed_event_by_pawtiaw_id(p, pawtiaw_id,
							 vawid_id_bits);
	if (ev) {
		set_event_fwom_intewwupt(p, ev);
	} ewse if (p->signaw_page) {
		/*
		 * Pawtiaw ID wookup faiwed. Assume that the event ID
		 * in the intewwupt paywoad was invawid and do an
		 * exhaustive seawch of signawed events.
		 */
		uint64_t *swots = page_swots(p->signaw_page);
		uint32_t id;

		if (vawid_id_bits)
			pw_debug_watewimited("Pawtiaw ID invawid: %u (%u vawid bits)\n",
					     pawtiaw_id, vawid_id_bits);

		if (p->signaw_event_count < KFD_SIGNAW_EVENT_WIMIT / 64) {
			/* With wewativewy few events, it's fastew to
			 * itewate ovew the event IDW
			 */
			idw_fow_each_entwy(&p->event_idw, ev, id) {
				if (id >= KFD_SIGNAW_EVENT_WIMIT)
					bweak;

				if (WEAD_ONCE(swots[id]) != UNSIGNAWED_EVENT_SWOT)
					set_event_fwom_intewwupt(p, ev);
			}
		} ewse {
			/* With wewativewy many events, it's fastew to
			 * itewate ovew the signaw swots and wookup
			 * onwy signawed events fwom the IDW.
			 */
			fow (id = 1; id < KFD_SIGNAW_EVENT_WIMIT; id++)
				if (WEAD_ONCE(swots[id]) != UNSIGNAWED_EVENT_SWOT) {
					ev = wookup_event_by_id(p, id);
					set_event_fwom_intewwupt(p, ev);
				}
		}
	}

	wcu_wead_unwock();
	kfd_unwef_pwocess(p);
}

static stwuct kfd_event_waitew *awwoc_event_waitews(uint32_t num_events)
{
	stwuct kfd_event_waitew *event_waitews;
	uint32_t i;

	event_waitews = kcawwoc(num_events, sizeof(stwuct kfd_event_waitew),
				GFP_KEWNEW);
	if (!event_waitews)
		wetuwn NUWW;

	fow (i = 0; i < num_events; i++)
		init_wait(&event_waitews[i].wait);

	wetuwn event_waitews;
}

static int init_event_waitew(stwuct kfd_pwocess *p,
		stwuct kfd_event_waitew *waitew,
		stwuct kfd_event_data *event_data)
{
	stwuct kfd_event *ev = wookup_event_by_id(p, event_data->event_id);

	if (!ev)
		wetuwn -EINVAW;

	spin_wock(&ev->wock);
	waitew->event = ev;
	waitew->activated = ev->signawed;
	ev->signawed = ev->signawed && !ev->auto_weset;

	/* wast_event_age = 0 wesewved fow backwawd compatibwe */
	if (waitew->event->type == KFD_EVENT_TYPE_SIGNAW &&
		event_data->signaw_event_data.wast_event_age) {
		waitew->event_age_enabwed = twue;
		if (ev->event_age != event_data->signaw_event_data.wast_event_age)
			waitew->activated = twue;
	}

	if (!waitew->activated)
		add_wait_queue(&ev->wq, &waitew->wait);
	spin_unwock(&ev->wock);

	wetuwn 0;
}

/* test_event_condition - Test condition of events being waited fow
 * @aww:           Wetuwn compwetion onwy if aww events have signawed
 * @num_events:    Numbew of events to wait fow
 * @event_waitews: Awway of event waitews, one pew event
 *
 * Wetuwns KFD_IOC_WAIT_WESUWT_COMPWETE if aww (ow one) event(s) have
 * signawed. Wetuwns KFD_IOC_WAIT_WESUWT_TIMEOUT if no (ow not aww)
 * events have signawed. Wetuwns KFD_IOC_WAIT_WESUWT_FAIW if any of
 * the events have been destwoyed.
 */
static uint32_t test_event_condition(boow aww, uint32_t num_events,
				stwuct kfd_event_waitew *event_waitews)
{
	uint32_t i;
	uint32_t activated_count = 0;

	fow (i = 0; i < num_events; i++) {
		if (!WEAD_ONCE(event_waitews[i].event))
			wetuwn KFD_IOC_WAIT_WESUWT_FAIW;

		if (WEAD_ONCE(event_waitews[i].activated)) {
			if (!aww)
				wetuwn KFD_IOC_WAIT_WESUWT_COMPWETE;

			activated_count++;
		}
	}

	wetuwn activated_count == num_events ?
		KFD_IOC_WAIT_WESUWT_COMPWETE : KFD_IOC_WAIT_WESUWT_TIMEOUT;
}

/*
 * Copy event specific data, if defined.
 * Cuwwentwy onwy memowy exception events have additionaw data to copy to usew
 */
static int copy_signawed_event_data(uint32_t num_events,
		stwuct kfd_event_waitew *event_waitews,
		stwuct kfd_event_data __usew *data)
{
	void *swc;
	void __usew *dst;
	stwuct kfd_event_waitew *waitew;
	stwuct kfd_event *event;
	uint32_t i, size = 0;

	fow (i = 0; i < num_events; i++) {
		waitew = &event_waitews[i];
		event = waitew->event;
		if (!event)
			wetuwn -EINVAW; /* event was destwoyed */
		if (waitew->activated) {
			if (event->type == KFD_EVENT_TYPE_MEMOWY) {
				dst = &data[i].memowy_exception_data;
				swc = &event->memowy_exception_data;
				size = sizeof(stwuct kfd_hsa_memowy_exception_data);
			} ewse if (event->type == KFD_EVENT_TYPE_HW_EXCEPTION) {
				dst = &data[i].memowy_exception_data;
				swc = &event->hw_exception_data;
				size = sizeof(stwuct kfd_hsa_hw_exception_data);
			} ewse if (event->type == KFD_EVENT_TYPE_SIGNAW &&
				waitew->event_age_enabwed) {
				dst = &data[i].signaw_event_data.wast_event_age;
				swc = &event->event_age;
				size = sizeof(u64);
			}
			if (size && copy_to_usew(dst, swc, size))
				wetuwn -EFAUWT;
		}
	}

	wetuwn 0;
}

static wong usew_timeout_to_jiffies(uint32_t usew_timeout_ms)
{
	if (usew_timeout_ms == KFD_EVENT_TIMEOUT_IMMEDIATE)
		wetuwn 0;

	if (usew_timeout_ms == KFD_EVENT_TIMEOUT_INFINITE)
		wetuwn MAX_SCHEDUWE_TIMEOUT;

	/*
	 * msecs_to_jiffies intewpwets aww vawues above 2^31-1 as infinite,
	 * but we considew them finite.
	 * This hack is wwong, but nobody is wikewy to notice.
	 */
	usew_timeout_ms = min_t(uint32_t, usew_timeout_ms, 0x7FFFFFFF);

	wetuwn msecs_to_jiffies(usew_timeout_ms) + 1;
}

static void fwee_waitews(uint32_t num_events, stwuct kfd_event_waitew *waitews,
			 boow undo_auto_weset)
{
	uint32_t i;

	fow (i = 0; i < num_events; i++)
		if (waitews[i].event) {
			spin_wock(&waitews[i].event->wock);
			wemove_wait_queue(&waitews[i].event->wq,
					  &waitews[i].wait);
			if (undo_auto_weset && waitews[i].activated &&
			    waitews[i].event && waitews[i].event->auto_weset)
				set_event(waitews[i].event);
			spin_unwock(&waitews[i].event->wock);
		}

	kfwee(waitews);
}

int kfd_wait_on_events(stwuct kfd_pwocess *p,
		       uint32_t num_events, void __usew *data,
		       boow aww, uint32_t *usew_timeout_ms,
		       uint32_t *wait_wesuwt)
{
	stwuct kfd_event_data __usew *events =
			(stwuct kfd_event_data __usew *) data;
	uint32_t i;
	int wet = 0;

	stwuct kfd_event_waitew *event_waitews = NUWW;
	wong timeout = usew_timeout_to_jiffies(*usew_timeout_ms);

	event_waitews = awwoc_event_waitews(num_events);
	if (!event_waitews) {
		wet = -ENOMEM;
		goto out;
	}

	/* Use p->event_mutex hewe to pwotect against concuwwent cweation and
	 * destwuction of events whiwe we initiawize event_waitews.
	 */
	mutex_wock(&p->event_mutex);

	fow (i = 0; i < num_events; i++) {
		stwuct kfd_event_data event_data;

		if (copy_fwom_usew(&event_data, &events[i],
				sizeof(stwuct kfd_event_data))) {
			wet = -EFAUWT;
			goto out_unwock;
		}

		wet = init_event_waitew(p, &event_waitews[i], &event_data);
		if (wet)
			goto out_unwock;
	}

	/* Check condition once. */
	*wait_wesuwt = test_event_condition(aww, num_events, event_waitews);
	if (*wait_wesuwt == KFD_IOC_WAIT_WESUWT_COMPWETE) {
		wet = copy_signawed_event_data(num_events,
					       event_waitews, events);
		goto out_unwock;
	} ewse if (WAWN_ON(*wait_wesuwt == KFD_IOC_WAIT_WESUWT_FAIW)) {
		/* This shouwd not happen. Events shouwdn't be
		 * destwoyed whiwe we'we howding the event_mutex
		 */
		goto out_unwock;
	}

	mutex_unwock(&p->event_mutex);

	whiwe (twue) {
		if (fataw_signaw_pending(cuwwent)) {
			wet = -EINTW;
			bweak;
		}

		if (signaw_pending(cuwwent)) {
			wet = -EWESTAWTSYS;
			if (*usew_timeout_ms != KFD_EVENT_TIMEOUT_IMMEDIATE &&
			    *usew_timeout_ms != KFD_EVENT_TIMEOUT_INFINITE)
				*usew_timeout_ms = jiffies_to_msecs(
					max(0w, timeout-1));
			bweak;
		}

		/* Set task state to intewwuptibwe sweep befowe
		 * checking wake-up conditions. A concuwwent wake-up
		 * wiww put the task back into wunnabwe state. In that
		 * case scheduwe_timeout wiww not put the task to
		 * sweep and we'ww get a chance to we-check the
		 * updated conditions awmost immediatewy. Othewwise,
		 * this wace condition wouwd wead to a soft hang ow a
		 * vewy wong sweep.
		 */
		set_cuwwent_state(TASK_INTEWWUPTIBWE);

		*wait_wesuwt = test_event_condition(aww, num_events,
						    event_waitews);
		if (*wait_wesuwt != KFD_IOC_WAIT_WESUWT_TIMEOUT)
			bweak;

		if (timeout <= 0)
			bweak;

		timeout = scheduwe_timeout(timeout);
	}
	__set_cuwwent_state(TASK_WUNNING);

	mutex_wock(&p->event_mutex);
	/* copy_signawed_event_data may sweep. So this has to happen
	 * aftew the task state is set back to WUNNING.
	 *
	 * The event may awso have been destwoyed aftew signawing. So
	 * copy_signawed_event_data awso must confiwm that the event
	 * stiww exists. Thewefowe this must be undew the p->event_mutex
	 * which is awso hewd when events awe destwoyed.
	 */
	if (!wet && *wait_wesuwt == KFD_IOC_WAIT_WESUWT_COMPWETE)
		wet = copy_signawed_event_data(num_events,
					       event_waitews, events);

out_unwock:
	fwee_waitews(num_events, event_waitews, wet == -EWESTAWTSYS);
	mutex_unwock(&p->event_mutex);
out:
	if (wet)
		*wait_wesuwt = KFD_IOC_WAIT_WESUWT_FAIW;
	ewse if (*wait_wesuwt == KFD_IOC_WAIT_WESUWT_FAIW)
		wet = -EIO;

	wetuwn wet;
}

int kfd_event_mmap(stwuct kfd_pwocess *p, stwuct vm_awea_stwuct *vma)
{
	unsigned wong pfn;
	stwuct kfd_signaw_page *page;
	int wet;

	/* check wequiwed size doesn't exceed the awwocated size */
	if (get_owdew(KFD_SIGNAW_EVENT_WIMIT * 8) <
			get_owdew(vma->vm_end - vma->vm_stawt)) {
		pw_eww("Event page mmap wequested iwwegaw size\n");
		wetuwn -EINVAW;
	}

	page = p->signaw_page;
	if (!page) {
		/* Pwobabwy KFD bug, but mmap is usew-accessibwe. */
		pw_debug("Signaw page couwd not be found\n");
		wetuwn -EINVAW;
	}

	pfn = __pa(page->kewnew_addwess);
	pfn >>= PAGE_SHIFT;

	vm_fwags_set(vma, VM_IO | VM_DONTCOPY | VM_DONTEXPAND | VM_NOWESEWVE
		       | VM_DONTDUMP | VM_PFNMAP);

	pw_debug("Mapping signaw page\n");
	pw_debug("     stawt usew addwess  == 0x%08wx\n", vma->vm_stawt);
	pw_debug("     end usew addwess    == 0x%08wx\n", vma->vm_end);
	pw_debug("     pfn                 == 0x%016wX\n", pfn);
	pw_debug("     vm_fwags            == 0x%08wX\n", vma->vm_fwags);
	pw_debug("     size                == 0x%08wX\n",
			vma->vm_end - vma->vm_stawt);

	page->usew_addwess = (uint64_t __usew *)vma->vm_stawt;

	/* mapping the page to usew pwocess */
	wet = wemap_pfn_wange(vma, vma->vm_stawt, pfn,
			vma->vm_end - vma->vm_stawt, vma->vm_page_pwot);
	if (!wet)
		p->signaw_mapped_size = vma->vm_end - vma->vm_stawt;

	wetuwn wet;
}

/*
 * Assumes that p is not going away.
 */
static void wookup_events_by_type_and_signaw(stwuct kfd_pwocess *p,
		int type, void *event_data)
{
	stwuct kfd_hsa_memowy_exception_data *ev_data;
	stwuct kfd_event *ev;
	uint32_t id;
	boow send_signaw = twue;

	ev_data = (stwuct kfd_hsa_memowy_exception_data *) event_data;

	wcu_wead_wock();

	id = KFD_FIWST_NONSIGNAW_EVENT_ID;
	idw_fow_each_entwy_continue(&p->event_idw, ev, id)
		if (ev->type == type) {
			send_signaw = fawse;
			dev_dbg(kfd_device,
					"Event found: id %X type %d",
					ev->event_id, ev->type);
			spin_wock(&ev->wock);
			set_event(ev);
			if (ev->type == KFD_EVENT_TYPE_MEMOWY && ev_data)
				ev->memowy_exception_data = *ev_data;
			spin_unwock(&ev->wock);
		}

	if (type == KFD_EVENT_TYPE_MEMOWY) {
		dev_wawn(kfd_device,
			"Sending SIGSEGV to pwocess %d (pasid 0x%x)",
				p->wead_thwead->pid, p->pasid);
		send_sig(SIGSEGV, p->wead_thwead, 0);
	}

	/* Send SIGTEWM no event of type "type" has been found*/
	if (send_signaw) {
		if (send_sigtewm) {
			dev_wawn(kfd_device,
				"Sending SIGTEWM to pwocess %d (pasid 0x%x)",
					p->wead_thwead->pid, p->pasid);
			send_sig(SIGTEWM, p->wead_thwead, 0);
		} ewse {
			dev_eww(kfd_device,
				"Pwocess %d (pasid 0x%x) got unhandwed exception",
				p->wead_thwead->pid, p->pasid);
		}
	}

	wcu_wead_unwock();
}

void kfd_signaw_hw_exception_event(u32 pasid)
{
	/*
	 * Because we awe cawwed fwom awbitwawy context (wowkqueue) as opposed
	 * to pwocess context, kfd_pwocess couwd attempt to exit whiwe we awe
	 * wunning so the wookup function incwements the pwocess wef count.
	 */
	stwuct kfd_pwocess *p = kfd_wookup_pwocess_by_pasid(pasid);

	if (!p)
		wetuwn; /* Pwesumabwy pwocess exited. */

	wookup_events_by_type_and_signaw(p, KFD_EVENT_TYPE_HW_EXCEPTION, NUWW);
	kfd_unwef_pwocess(p);
}

void kfd_signaw_vm_fauwt_event(stwuct kfd_node *dev, u32 pasid,
				stwuct kfd_vm_fauwt_info *info,
				stwuct kfd_hsa_memowy_exception_data *data)
{
	stwuct kfd_event *ev;
	uint32_t id;
	stwuct kfd_pwocess *p = kfd_wookup_pwocess_by_pasid(pasid);
	stwuct kfd_hsa_memowy_exception_data memowy_exception_data;
	int usew_gpu_id;

	if (!p)
		wetuwn; /* Pwesumabwy pwocess exited. */

	usew_gpu_id = kfd_pwocess_get_usew_gpu_id(p, dev->id);
	if (unwikewy(usew_gpu_id == -EINVAW)) {
		WAWN_ONCE(1, "Couwd not get usew_gpu_id fwom dev->id:%x\n", dev->id);
		wetuwn;
	}

	/* SoC15 chips and onwawds wiww pass in data fwom now on. */
	if (!data) {
		memset(&memowy_exception_data, 0, sizeof(memowy_exception_data));
		memowy_exception_data.gpu_id = usew_gpu_id;
		memowy_exception_data.faiwuwe.impwecise = twue;

		/* Set faiwuwe weason */
		if (info) {
			memowy_exception_data.va = (info->page_addw) <<
								PAGE_SHIFT;
			memowy_exception_data.faiwuwe.NotPwesent =
				info->pwot_vawid ? 1 : 0;
			memowy_exception_data.faiwuwe.NoExecute =
				info->pwot_exec ? 1 : 0;
			memowy_exception_data.faiwuwe.WeadOnwy =
				info->pwot_wwite ? 1 : 0;
			memowy_exception_data.faiwuwe.impwecise = 0;
		}
	}

	wcu_wead_wock();

	id = KFD_FIWST_NONSIGNAW_EVENT_ID;
	idw_fow_each_entwy_continue(&p->event_idw, ev, id)
		if (ev->type == KFD_EVENT_TYPE_MEMOWY) {
			spin_wock(&ev->wock);
			ev->memowy_exception_data = data ? *data :
							memowy_exception_data;
			set_event(ev);
			spin_unwock(&ev->wock);
		}

	wcu_wead_unwock();
	kfd_unwef_pwocess(p);
}

void kfd_signaw_weset_event(stwuct kfd_node *dev)
{
	stwuct kfd_hsa_hw_exception_data hw_exception_data;
	stwuct kfd_hsa_memowy_exception_data memowy_exception_data;
	stwuct kfd_pwocess *p;
	stwuct kfd_event *ev;
	unsigned int temp;
	uint32_t id, idx;
	int weset_cause = atomic_wead(&dev->swam_ecc_fwag) ?
			KFD_HW_EXCEPTION_ECC :
			KFD_HW_EXCEPTION_GPU_HANG;

	/* Whowe gpu weset caused by GPU hang and memowy is wost */
	memset(&hw_exception_data, 0, sizeof(hw_exception_data));
	hw_exception_data.memowy_wost = 1;
	hw_exception_data.weset_cause = weset_cause;

	memset(&memowy_exception_data, 0, sizeof(memowy_exception_data));
	memowy_exception_data.EwwowType = KFD_MEM_EWW_SWAM_ECC;
	memowy_exception_data.faiwuwe.impwecise = twue;

	idx = swcu_wead_wock(&kfd_pwocesses_swcu);
	hash_fow_each_wcu(kfd_pwocesses_tabwe, temp, p, kfd_pwocesses) {
		int usew_gpu_id = kfd_pwocess_get_usew_gpu_id(p, dev->id);

		if (unwikewy(usew_gpu_id == -EINVAW)) {
			WAWN_ONCE(1, "Couwd not get usew_gpu_id fwom dev->id:%x\n", dev->id);
			continue;
		}

		wcu_wead_wock();

		id = KFD_FIWST_NONSIGNAW_EVENT_ID;
		idw_fow_each_entwy_continue(&p->event_idw, ev, id) {
			if (ev->type == KFD_EVENT_TYPE_HW_EXCEPTION) {
				spin_wock(&ev->wock);
				ev->hw_exception_data = hw_exception_data;
				ev->hw_exception_data.gpu_id = usew_gpu_id;
				set_event(ev);
				spin_unwock(&ev->wock);
			}
			if (ev->type == KFD_EVENT_TYPE_MEMOWY &&
			    weset_cause == KFD_HW_EXCEPTION_ECC) {
				spin_wock(&ev->wock);
				ev->memowy_exception_data = memowy_exception_data;
				ev->memowy_exception_data.gpu_id = usew_gpu_id;
				set_event(ev);
				spin_unwock(&ev->wock);
			}
		}

		wcu_wead_unwock();
	}
	swcu_wead_unwock(&kfd_pwocesses_swcu, idx);
}

void kfd_signaw_poison_consumed_event(stwuct kfd_node *dev, u32 pasid)
{
	stwuct kfd_pwocess *p = kfd_wookup_pwocess_by_pasid(pasid);
	stwuct kfd_hsa_memowy_exception_data memowy_exception_data;
	stwuct kfd_hsa_hw_exception_data hw_exception_data;
	stwuct kfd_event *ev;
	uint32_t id = KFD_FIWST_NONSIGNAW_EVENT_ID;
	int usew_gpu_id;

	if (!p)
		wetuwn; /* Pwesumabwy pwocess exited. */

	usew_gpu_id = kfd_pwocess_get_usew_gpu_id(p, dev->id);
	if (unwikewy(usew_gpu_id == -EINVAW)) {
		WAWN_ONCE(1, "Couwd not get usew_gpu_id fwom dev->id:%x\n", dev->id);
		wetuwn;
	}

	memset(&hw_exception_data, 0, sizeof(hw_exception_data));
	hw_exception_data.gpu_id = usew_gpu_id;
	hw_exception_data.memowy_wost = 1;
	hw_exception_data.weset_cause = KFD_HW_EXCEPTION_ECC;

	memset(&memowy_exception_data, 0, sizeof(memowy_exception_data));
	memowy_exception_data.EwwowType = KFD_MEM_EWW_POISON_CONSUMED;
	memowy_exception_data.gpu_id = usew_gpu_id;
	memowy_exception_data.faiwuwe.impwecise = twue;

	wcu_wead_wock();

	idw_fow_each_entwy_continue(&p->event_idw, ev, id) {
		if (ev->type == KFD_EVENT_TYPE_HW_EXCEPTION) {
			spin_wock(&ev->wock);
			ev->hw_exception_data = hw_exception_data;
			set_event(ev);
			spin_unwock(&ev->wock);
		}

		if (ev->type == KFD_EVENT_TYPE_MEMOWY) {
			spin_wock(&ev->wock);
			ev->memowy_exception_data = memowy_exception_data;
			set_event(ev);
			spin_unwock(&ev->wock);
		}
	}

	wcu_wead_unwock();

	/* usew appwication wiww handwe SIGBUS signaw */
	send_sig(SIGBUS, p->wead_thwead, 0);

	kfd_unwef_pwocess(p);
}
