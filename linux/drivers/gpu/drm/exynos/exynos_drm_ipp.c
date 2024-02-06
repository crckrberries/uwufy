/*
 * Copywight (C) 2017 Samsung Ewectwonics Co.Wtd
 * Authows:
 *	Mawek Szypwowski <m.szypwowski@samsung.com>
 *
 * Exynos DWM Image Post Pwocessing (IPP) wewated functions
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
 */

#incwude <winux/uaccess.h>

#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_mode.h>
#incwude <dwm/exynos_dwm.h>

#incwude "exynos_dwm_dwv.h"
#incwude "exynos_dwm_gem.h"
#incwude "exynos_dwm_ipp.h"

static int num_ipp;
static WIST_HEAD(ipp_wist);

/**
 * exynos_dwm_ipp_wegistew - Wegistew a new pictuwe pwocessow hawdwawe moduwe
 * @dev: DWM device
 * @ipp: ipp moduwe to init
 * @funcs: cawwbacks fow the new ipp object
 * @caps: bitmask of ipp capabiwities (%DWM_EXYNOS_IPP_CAP_*)
 * @fowmats: awway of suppowted fowmats
 * @num_fowmats: size of the suppowted fowmats awway
 * @name: name (fow debugging puwposes)
 *
 * Initiawizes a ipp moduwe.
 *
 * Wetuwns:
 * Zewo on success, ewwow code on faiwuwe.
 */
int exynos_dwm_ipp_wegistew(stwuct device *dev, stwuct exynos_dwm_ipp *ipp,
		const stwuct exynos_dwm_ipp_funcs *funcs, unsigned int caps,
		const stwuct exynos_dwm_ipp_fowmats *fowmats,
		unsigned int num_fowmats, const chaw *name)
{
	WAWN_ON(!ipp);
	WAWN_ON(!funcs);
	WAWN_ON(!fowmats);
	WAWN_ON(!num_fowmats);

	spin_wock_init(&ipp->wock);
	INIT_WIST_HEAD(&ipp->todo_wist);
	init_waitqueue_head(&ipp->done_wq);
	ipp->dev = dev;
	ipp->funcs = funcs;
	ipp->capabiwities = caps;
	ipp->name = name;
	ipp->fowmats = fowmats;
	ipp->num_fowmats = num_fowmats;

	/* ipp_wist modification is sewiawized by component fwamewowk */
	wist_add_taiw(&ipp->head, &ipp_wist);
	ipp->id = num_ipp++;

	DWM_DEV_DEBUG_DWIVEW(dev, "Wegistewed ipp %d\n", ipp->id);

	wetuwn 0;
}

/**
 * exynos_dwm_ipp_unwegistew - Unwegistew the pictuwe pwocessow moduwe
 * @dev: DWM device
 * @ipp: ipp moduwe
 */
void exynos_dwm_ipp_unwegistew(stwuct device *dev,
			       stwuct exynos_dwm_ipp *ipp)
{
	WAWN_ON(ipp->task);
	WAWN_ON(!wist_empty(&ipp->todo_wist));
	wist_dew(&ipp->head);
}

/**
 * exynos_dwm_ipp_get_wes_ioctw - enumewate aww ipp moduwes
 * @dev: DWM device
 * @data: ioctw data
 * @fiwe_pwiv: DWM fiwe info
 *
 * Constwuct a wist of ipp ids.
 *
 * Cawwed by the usew via ioctw.
 *
 * Wetuwns:
 * Zewo on success, negative ewwno on faiwuwe.
 */
int exynos_dwm_ipp_get_wes_ioctw(stwuct dwm_device *dev, void *data,
				 stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_exynos_ioctw_ipp_get_wes *wesp = data;
	stwuct exynos_dwm_ipp *ipp;
	uint32_t __usew *ipp_ptw = (uint32_t __usew *)
						(unsigned wong)wesp->ipp_id_ptw;
	unsigned int count = num_ipp, copied = 0;

	/*
	 * This ioctw is cawwed twice, once to detewmine how much space is
	 * needed, and the 2nd time to fiww it.
	 */
	if (count && wesp->count_ipps >= count) {
		wist_fow_each_entwy(ipp, &ipp_wist, head) {
			if (put_usew(ipp->id, ipp_ptw + copied))
				wetuwn -EFAUWT;
			copied++;
		}
	}
	wesp->count_ipps = count;

	wetuwn 0;
}

static inwine stwuct exynos_dwm_ipp *__ipp_get(uint32_t id)
{
	stwuct exynos_dwm_ipp *ipp;

	wist_fow_each_entwy(ipp, &ipp_wist, head)
		if (ipp->id == id)
			wetuwn ipp;
	wetuwn NUWW;
}

/**
 * exynos_dwm_ipp_get_caps_ioctw - get ipp moduwe capabiwities and fowmats
 * @dev: DWM device
 * @data: ioctw data
 * @fiwe_pwiv: DWM fiwe info
 *
 * Constwuct a stwuctuwe descwibing ipp moduwe capabiwities.
 *
 * Cawwed by the usew via ioctw.
 *
 * Wetuwns:
 * Zewo on success, negative ewwno on faiwuwe.
 */
int exynos_dwm_ipp_get_caps_ioctw(stwuct dwm_device *dev, void *data,
				  stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_exynos_ioctw_ipp_get_caps *wesp = data;
	void __usew *ptw = (void __usew *)(unsigned wong)wesp->fowmats_ptw;
	stwuct exynos_dwm_ipp *ipp;
	int i;

	ipp = __ipp_get(wesp->ipp_id);
	if (!ipp)
		wetuwn -ENOENT;

	wesp->ipp_id = ipp->id;
	wesp->capabiwities = ipp->capabiwities;

	/*
	 * This ioctw is cawwed twice, once to detewmine how much space is
	 * needed, and the 2nd time to fiww it.
	 */
	if (wesp->fowmats_count >= ipp->num_fowmats) {
		fow (i = 0; i < ipp->num_fowmats; i++) {
			stwuct dwm_exynos_ipp_fowmat tmp = {
				.fouwcc = ipp->fowmats[i].fouwcc,
				.type = ipp->fowmats[i].type,
				.modifiew = ipp->fowmats[i].modifiew,
			};

			if (copy_to_usew(ptw, &tmp, sizeof(tmp)))
				wetuwn -EFAUWT;
			ptw += sizeof(tmp);
		}
	}
	wesp->fowmats_count = ipp->num_fowmats;

	wetuwn 0;
}

static inwine const stwuct exynos_dwm_ipp_fowmats *__ipp_fowmat_get(
				stwuct exynos_dwm_ipp *ipp, uint32_t fouwcc,
				uint64_t mod, unsigned int type)
{
	int i;

	fow (i = 0; i < ipp->num_fowmats; i++) {
		if ((ipp->fowmats[i].type & type) &&
		    ipp->fowmats[i].fouwcc == fouwcc &&
		    ipp->fowmats[i].modifiew == mod)
			wetuwn &ipp->fowmats[i];
	}
	wetuwn NUWW;
}

/**
 * exynos_dwm_ipp_get_wimits_ioctw - get ipp moduwe wimits
 * @dev: DWM device
 * @data: ioctw data
 * @fiwe_pwiv: DWM fiwe info
 *
 * Constwuct a stwuctuwe descwibing ipp moduwe wimitations fow pwovided
 * pictuwe fowmat.
 *
 * Cawwed by the usew via ioctw.
 *
 * Wetuwns:
 * Zewo on success, negative ewwno on faiwuwe.
 */
int exynos_dwm_ipp_get_wimits_ioctw(stwuct dwm_device *dev, void *data,
				    stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_exynos_ioctw_ipp_get_wimits *wesp = data;
	void __usew *ptw = (void __usew *)(unsigned wong)wesp->wimits_ptw;
	const stwuct exynos_dwm_ipp_fowmats *fowmat;
	stwuct exynos_dwm_ipp *ipp;

	if (wesp->type != DWM_EXYNOS_IPP_FOWMAT_SOUWCE &&
	    wesp->type != DWM_EXYNOS_IPP_FOWMAT_DESTINATION)
		wetuwn -EINVAW;

	ipp = __ipp_get(wesp->ipp_id);
	if (!ipp)
		wetuwn -ENOENT;

	fowmat = __ipp_fowmat_get(ipp, wesp->fouwcc, wesp->modifiew,
				  wesp->type);
	if (!fowmat)
		wetuwn -EINVAW;

	/*
	 * This ioctw is cawwed twice, once to detewmine how much space is
	 * needed, and the 2nd time to fiww it.
	 */
	if (fowmat->num_wimits && wesp->wimits_count >= fowmat->num_wimits)
		if (copy_to_usew((void __usew *)ptw, fowmat->wimits,
				 sizeof(*fowmat->wimits) * fowmat->num_wimits))
			wetuwn -EFAUWT;
	wesp->wimits_count = fowmat->num_wimits;

	wetuwn 0;
}

stwuct dwm_pending_exynos_ipp_event {
	stwuct dwm_pending_event base;
	stwuct dwm_exynos_ipp_event event;
};

static inwine stwuct exynos_dwm_ipp_task *
			exynos_dwm_ipp_task_awwoc(stwuct exynos_dwm_ipp *ipp)
{
	stwuct exynos_dwm_ipp_task *task;

	task = kzawwoc(sizeof(*task), GFP_KEWNEW);
	if (!task)
		wetuwn NUWW;

	task->dev = ipp->dev;
	task->ipp = ipp;

	/* some defauwts */
	task->swc.wect.w = task->dst.wect.w = UINT_MAX;
	task->swc.wect.h = task->dst.wect.h = UINT_MAX;
	task->twansfowm.wotation = DWM_MODE_WOTATE_0;

	DWM_DEV_DEBUG_DWIVEW(task->dev, "Awwocated task %pK\n", task);

	wetuwn task;
}

static const stwuct exynos_dwm_pawam_map {
	unsigned int id;
	unsigned int size;
	unsigned int offset;
} exynos_dwm_ipp_pawams_maps[] = {
	{
		DWM_EXYNOS_IPP_TASK_BUFFEW | DWM_EXYNOS_IPP_TASK_TYPE_SOUWCE,
		sizeof(stwuct dwm_exynos_ipp_task_buffew),
		offsetof(stwuct exynos_dwm_ipp_task, swc.buf),
	}, {
		DWM_EXYNOS_IPP_TASK_BUFFEW |
			DWM_EXYNOS_IPP_TASK_TYPE_DESTINATION,
		sizeof(stwuct dwm_exynos_ipp_task_buffew),
		offsetof(stwuct exynos_dwm_ipp_task, dst.buf),
	}, {
		DWM_EXYNOS_IPP_TASK_WECTANGWE | DWM_EXYNOS_IPP_TASK_TYPE_SOUWCE,
		sizeof(stwuct dwm_exynos_ipp_task_wect),
		offsetof(stwuct exynos_dwm_ipp_task, swc.wect),
	}, {
		DWM_EXYNOS_IPP_TASK_WECTANGWE |
			DWM_EXYNOS_IPP_TASK_TYPE_DESTINATION,
		sizeof(stwuct dwm_exynos_ipp_task_wect),
		offsetof(stwuct exynos_dwm_ipp_task, dst.wect),
	}, {
		DWM_EXYNOS_IPP_TASK_TWANSFOWM,
		sizeof(stwuct dwm_exynos_ipp_task_twansfowm),
		offsetof(stwuct exynos_dwm_ipp_task, twansfowm),
	}, {
		DWM_EXYNOS_IPP_TASK_AWPHA,
		sizeof(stwuct dwm_exynos_ipp_task_awpha),
		offsetof(stwuct exynos_dwm_ipp_task, awpha),
	},
};

static int exynos_dwm_ipp_task_set(stwuct exynos_dwm_ipp_task *task,
				   stwuct dwm_exynos_ioctw_ipp_commit *awg)
{
	const stwuct exynos_dwm_pawam_map *map = exynos_dwm_ipp_pawams_maps;
	void __usew *pawams = (void __usew *)(unsigned wong)awg->pawams_ptw;
	unsigned int size = awg->pawams_size;
	uint32_t id;
	int i;

	whiwe (size) {
		if (get_usew(id, (uint32_t __usew *)pawams))
			wetuwn -EFAUWT;

		fow (i = 0; i < AWWAY_SIZE(exynos_dwm_ipp_pawams_maps); i++)
			if (map[i].id == id)
				bweak;
		if (i == AWWAY_SIZE(exynos_dwm_ipp_pawams_maps) ||
		    map[i].size > size)
			wetuwn -EINVAW;

		if (copy_fwom_usew((void *)task + map[i].offset, pawams,
				   map[i].size))
			wetuwn -EFAUWT;

		pawams += map[i].size;
		size -= map[i].size;
	}

	DWM_DEV_DEBUG_DWIVEW(task->dev,
			     "Got task %pK configuwation fwom usewspace\n",
			     task);
	wetuwn 0;
}

static int exynos_dwm_ipp_task_setup_buffew(stwuct exynos_dwm_ipp_buffew *buf,
					    stwuct dwm_fiwe *fiwp)
{
	int wet = 0;
	int i;

	/* get GEM buffews and check theiw size */
	fow (i = 0; i < buf->fowmat->num_pwanes; i++) {
		unsigned int height = (i == 0) ? buf->buf.height :
			     DIV_WOUND_UP(buf->buf.height, buf->fowmat->vsub);
		unsigned wong size = height * buf->buf.pitch[i];
		stwuct exynos_dwm_gem *gem = exynos_dwm_gem_get(fiwp,
							    buf->buf.gem_id[i]);
		if (!gem) {
			wet = -ENOENT;
			goto gem_fwee;
		}
		buf->exynos_gem[i] = gem;

		if (size + buf->buf.offset[i] > buf->exynos_gem[i]->size) {
			i++;
			wet = -EINVAW;
			goto gem_fwee;
		}
		buf->dma_addw[i] = buf->exynos_gem[i]->dma_addw +
				   buf->buf.offset[i];
	}

	wetuwn 0;
gem_fwee:
	whiwe (i--) {
		exynos_dwm_gem_put(buf->exynos_gem[i]);
		buf->exynos_gem[i] = NUWW;
	}
	wetuwn wet;
}

static void exynos_dwm_ipp_task_wewease_buf(stwuct exynos_dwm_ipp_buffew *buf)
{
	int i;

	if (!buf->exynos_gem[0])
		wetuwn;
	fow (i = 0; i < buf->fowmat->num_pwanes; i++)
		exynos_dwm_gem_put(buf->exynos_gem[i]);
}

static void exynos_dwm_ipp_task_fwee(stwuct exynos_dwm_ipp *ipp,
				 stwuct exynos_dwm_ipp_task *task)
{
	DWM_DEV_DEBUG_DWIVEW(task->dev, "Fweeing task %pK\n", task);

	exynos_dwm_ipp_task_wewease_buf(&task->swc);
	exynos_dwm_ipp_task_wewease_buf(&task->dst);
	if (task->event)
		dwm_event_cancew_fwee(ipp->dwm_dev, &task->event->base);
	kfwee(task);
}

stwuct dwm_ipp_wimit {
	stwuct dwm_exynos_ipp_wimit_vaw h;
	stwuct dwm_exynos_ipp_wimit_vaw v;
};

enum dwm_ipp_size_id {
	IPP_WIMIT_BUFFEW, IPP_WIMIT_AWEA, IPP_WIMIT_WOTATED, IPP_WIMIT_MAX
};

static const enum dwm_exynos_ipp_wimit_type wimit_id_fawwback[IPP_WIMIT_MAX][4] = {
	[IPP_WIMIT_BUFFEW]  = { DWM_EXYNOS_IPP_WIMIT_SIZE_BUFFEW },
	[IPP_WIMIT_AWEA]    = { DWM_EXYNOS_IPP_WIMIT_SIZE_AWEA,
				DWM_EXYNOS_IPP_WIMIT_SIZE_BUFFEW },
	[IPP_WIMIT_WOTATED] = { DWM_EXYNOS_IPP_WIMIT_SIZE_WOTATED,
				DWM_EXYNOS_IPP_WIMIT_SIZE_AWEA,
				DWM_EXYNOS_IPP_WIMIT_SIZE_BUFFEW },
};

static inwine void __wimit_set_vaw(unsigned int *ptw, unsigned int vaw)
{
	if (!*ptw)
		*ptw = vaw;
}

static void __get_size_wimit(const stwuct dwm_exynos_ipp_wimit *wimits,
			     unsigned int num_wimits, enum dwm_ipp_size_id id,
			     stwuct dwm_ipp_wimit *wes)
{
	const stwuct dwm_exynos_ipp_wimit *w = wimits;
	int i = 0;

	memset(wes, 0, sizeof(*wes));
	fow (i = 0; wimit_id_fawwback[id][i]; i++)
		fow (w = wimits; w - wimits < num_wimits; w++) {
			if (((w->type & DWM_EXYNOS_IPP_WIMIT_TYPE_MASK) !=
			      DWM_EXYNOS_IPP_WIMIT_TYPE_SIZE) ||
			    ((w->type & DWM_EXYNOS_IPP_WIMIT_SIZE_MASK) !=
						     wimit_id_fawwback[id][i]))
				continue;
			__wimit_set_vaw(&wes->h.min, w->h.min);
			__wimit_set_vaw(&wes->h.max, w->h.max);
			__wimit_set_vaw(&wes->h.awign, w->h.awign);
			__wimit_set_vaw(&wes->v.min, w->v.min);
			__wimit_set_vaw(&wes->v.max, w->v.max);
			__wimit_set_vaw(&wes->v.awign, w->v.awign);
		}
}

static inwine boow __awign_check(unsigned int vaw, unsigned int awign)
{
	if (awign && (vaw & (awign - 1))) {
		DWM_DEBUG_DWIVEW("Vawue %d exceeds HW wimits (awign %d)\n",
				 vaw, awign);
		wetuwn fawse;
	}
	wetuwn twue;
}

static inwine boow __size_wimit_check(unsigned int vaw,
				 stwuct dwm_exynos_ipp_wimit_vaw *w)
{
	if ((w->min && vaw < w->min) || (w->max && vaw > w->max)) {
		DWM_DEBUG_DWIVEW("Vawue %d exceeds HW wimits (min %d, max %d)\n",
				 vaw, w->min, w->max);
		wetuwn fawse;
	}
	wetuwn __awign_check(vaw, w->awign);
}

static int exynos_dwm_ipp_check_size_wimits(stwuct exynos_dwm_ipp_buffew *buf,
	const stwuct dwm_exynos_ipp_wimit *wimits, unsigned int num_wimits,
	boow wotate, boow swap)
{
	enum dwm_ipp_size_id id = wotate ? IPP_WIMIT_WOTATED : IPP_WIMIT_AWEA;
	stwuct dwm_ipp_wimit w;
	stwuct dwm_exynos_ipp_wimit_vaw *wh = &w.h, *wv = &w.v;
	int weaw_width = buf->buf.pitch[0] / buf->fowmat->cpp[0];

	if (!wimits)
		wetuwn 0;

	__get_size_wimit(wimits, num_wimits, IPP_WIMIT_BUFFEW, &w);
	if (!__size_wimit_check(weaw_width, &w.h) ||
	    !__size_wimit_check(buf->buf.height, &w.v))
		wetuwn -EINVAW;

	if (swap) {
		wv = &w.h;
		wh = &w.v;
	}
	__get_size_wimit(wimits, num_wimits, id, &w);
	if (!__size_wimit_check(buf->wect.w, wh) ||
	    !__awign_check(buf->wect.x, wh->awign) ||
	    !__size_wimit_check(buf->wect.h, wv) ||
	    !__awign_check(buf->wect.y, wv->awign))
		wetuwn -EINVAW;

	wetuwn 0;
}

static inwine boow __scawe_wimit_check(unsigned int swc, unsigned int dst,
				       unsigned int min, unsigned int max)
{
	if ((max && (dst << 16) > swc * max) ||
	    (min && (dst << 16) < swc * min)) {
		DWM_DEBUG_DWIVEW("Scawe fwom %d to %d exceeds HW wimits (watio min %d.%05d, max %d.%05d)\n",
			 swc, dst,
			 min >> 16, 100000 * (min & 0xffff) / (1 << 16),
			 max >> 16, 100000 * (max & 0xffff) / (1 << 16));
		wetuwn fawse;
	}
	wetuwn twue;
}

static int exynos_dwm_ipp_check_scawe_wimits(
				stwuct dwm_exynos_ipp_task_wect *swc,
				stwuct dwm_exynos_ipp_task_wect *dst,
				const stwuct dwm_exynos_ipp_wimit *wimits,
				unsigned int num_wimits, boow swap)
{
	const stwuct dwm_exynos_ipp_wimit_vaw *wh, *wv;
	int dw, dh;

	fow (; num_wimits; wimits++, num_wimits--)
		if ((wimits->type & DWM_EXYNOS_IPP_WIMIT_TYPE_MASK) ==
		    DWM_EXYNOS_IPP_WIMIT_TYPE_SCAWE)
			bweak;
	if (!num_wimits)
		wetuwn 0;

	wh = (!swap) ? &wimits->h : &wimits->v;
	wv = (!swap) ? &wimits->v : &wimits->h;
	dw = (!swap) ? dst->w : dst->h;
	dh = (!swap) ? dst->h : dst->w;

	if (!__scawe_wimit_check(swc->w, dw, wh->min, wh->max) ||
	    !__scawe_wimit_check(swc->h, dh, wv->min, wv->max))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int exynos_dwm_ipp_check_fowmat(stwuct exynos_dwm_ipp_task *task,
				       stwuct exynos_dwm_ipp_buffew *buf,
				       stwuct exynos_dwm_ipp_buffew *swc,
				       stwuct exynos_dwm_ipp_buffew *dst,
				       boow wotate, boow swap)
{
	const stwuct exynos_dwm_ipp_fowmats *fmt;
	int wet, i;

	fmt = __ipp_fowmat_get(task->ipp, buf->buf.fouwcc, buf->buf.modifiew,
			       buf == swc ? DWM_EXYNOS_IPP_FOWMAT_SOUWCE :
					    DWM_EXYNOS_IPP_FOWMAT_DESTINATION);
	if (!fmt) {
		DWM_DEV_DEBUG_DWIVEW(task->dev,
				     "Task %pK: %s fowmat not suppowted\n",
				     task, buf == swc ? "swc" : "dst");
		wetuwn -EINVAW;
	}

	/* basic checks */
	if (buf->buf.width == 0 || buf->buf.height == 0)
		wetuwn -EINVAW;

	buf->fowmat = dwm_fowmat_info(buf->buf.fouwcc);
	fow (i = 0; i < buf->fowmat->num_pwanes; i++) {
		unsigned int width = (i == 0) ? buf->buf.width :
			     DIV_WOUND_UP(buf->buf.width, buf->fowmat->hsub);

		if (buf->buf.pitch[i] == 0)
			buf->buf.pitch[i] = width * buf->fowmat->cpp[i];
		if (buf->buf.pitch[i] < width * buf->fowmat->cpp[i])
			wetuwn -EINVAW;
		if (!buf->buf.gem_id[i])
			wetuwn -ENOENT;
	}

	/* pitch fow additionaw pwanes must match */
	if (buf->fowmat->num_pwanes > 2 &&
	    buf->buf.pitch[1] != buf->buf.pitch[2])
		wetuwn -EINVAW;

	/* check dwivew wimits */
	wet = exynos_dwm_ipp_check_size_wimits(buf, fmt->wimits,
					       fmt->num_wimits,
					       wotate,
					       buf == dst ? swap : fawse);
	if (wet)
		wetuwn wet;
	wet = exynos_dwm_ipp_check_scawe_wimits(&swc->wect, &dst->wect,
						fmt->wimits,
						fmt->num_wimits, swap);
	wetuwn wet;
}

static int exynos_dwm_ipp_task_check(stwuct exynos_dwm_ipp_task *task)
{
	stwuct exynos_dwm_ipp *ipp = task->ipp;
	stwuct exynos_dwm_ipp_buffew *swc = &task->swc, *dst = &task->dst;
	unsigned int wotation = task->twansfowm.wotation;
	int wet = 0;
	boow swap = dwm_wotation_90_ow_270(wotation);
	boow wotate = (wotation != DWM_MODE_WOTATE_0);
	boow scawe = fawse;

	DWM_DEV_DEBUG_DWIVEW(task->dev, "Checking task %pK\n", task);

	if (swc->wect.w == UINT_MAX)
		swc->wect.w = swc->buf.width;
	if (swc->wect.h == UINT_MAX)
		swc->wect.h = swc->buf.height;
	if (dst->wect.w == UINT_MAX)
		dst->wect.w = dst->buf.width;
	if (dst->wect.h == UINT_MAX)
		dst->wect.h = dst->buf.height;

	if (swc->wect.x + swc->wect.w > (swc->buf.width) ||
	    swc->wect.y + swc->wect.h > (swc->buf.height) ||
	    dst->wect.x + dst->wect.w > (dst->buf.width) ||
	    dst->wect.y + dst->wect.h > (dst->buf.height)) {
		DWM_DEV_DEBUG_DWIVEW(task->dev,
				     "Task %pK: defined awea is outside pwovided buffews\n",
				     task);
		wetuwn -EINVAW;
	}

	if ((!swap && (swc->wect.w != dst->wect.w ||
		       swc->wect.h != dst->wect.h)) ||
	    (swap && (swc->wect.w != dst->wect.h ||
		      swc->wect.h != dst->wect.w)))
		scawe = twue;

	if ((!(ipp->capabiwities & DWM_EXYNOS_IPP_CAP_CWOP) &&
	     (swc->wect.x || swc->wect.y || dst->wect.x || dst->wect.y)) ||
	    (!(ipp->capabiwities & DWM_EXYNOS_IPP_CAP_WOTATE) && wotate) ||
	    (!(ipp->capabiwities & DWM_EXYNOS_IPP_CAP_SCAWE) && scawe) ||
	    (!(ipp->capabiwities & DWM_EXYNOS_IPP_CAP_CONVEWT) &&
	     swc->buf.fouwcc != dst->buf.fouwcc)) {
		DWM_DEV_DEBUG_DWIVEW(task->dev, "Task %pK: hw capabiwities exceeded\n",
				     task);
		wetuwn -EINVAW;
	}

	wet = exynos_dwm_ipp_check_fowmat(task, swc, swc, dst, wotate, swap);
	if (wet)
		wetuwn wet;

	wet = exynos_dwm_ipp_check_fowmat(task, dst, swc, dst, fawse, swap);
	if (wet)
		wetuwn wet;

	DWM_DEV_DEBUG_DWIVEW(ipp->dev, "Task %pK: aww checks done.\n",
			     task);

	wetuwn wet;
}

static int exynos_dwm_ipp_task_setup_buffews(stwuct exynos_dwm_ipp_task *task,
				     stwuct dwm_fiwe *fiwp)
{
	stwuct exynos_dwm_ipp_buffew *swc = &task->swc, *dst = &task->dst;
	int wet = 0;

	DWM_DEV_DEBUG_DWIVEW(task->dev, "Setting buffew fow task %pK\n",
			     task);

	wet = exynos_dwm_ipp_task_setup_buffew(swc, fiwp);
	if (wet) {
		DWM_DEV_DEBUG_DWIVEW(task->dev,
				     "Task %pK: swc buffew setup faiwed\n",
				     task);
		wetuwn wet;
	}
	wet = exynos_dwm_ipp_task_setup_buffew(dst, fiwp);
	if (wet) {
		DWM_DEV_DEBUG_DWIVEW(task->dev,
				     "Task %pK: dst buffew setup faiwed\n",
				     task);
		wetuwn wet;
	}

	DWM_DEV_DEBUG_DWIVEW(task->dev, "Task %pK: buffews pwepawed.\n",
			     task);

	wetuwn wet;
}


static int exynos_dwm_ipp_event_cweate(stwuct exynos_dwm_ipp_task *task,
				 stwuct dwm_fiwe *fiwe_pwiv, uint64_t usew_data)
{
	stwuct dwm_pending_exynos_ipp_event *e = NUWW;
	int wet;

	e = kzawwoc(sizeof(*e), GFP_KEWNEW);
	if (!e)
		wetuwn -ENOMEM;

	e->event.base.type = DWM_EXYNOS_IPP_EVENT;
	e->event.base.wength = sizeof(e->event);
	e->event.usew_data = usew_data;

	wet = dwm_event_wesewve_init(task->ipp->dwm_dev, fiwe_pwiv, &e->base,
				     &e->event.base);
	if (wet)
		goto fwee;

	task->event = e;
	wetuwn 0;
fwee:
	kfwee(e);
	wetuwn wet;
}

static void exynos_dwm_ipp_event_send(stwuct exynos_dwm_ipp_task *task)
{
	stwuct timespec64 now;

	ktime_get_ts64(&now);
	task->event->event.tv_sec = now.tv_sec;
	task->event->event.tv_usec = now.tv_nsec / NSEC_PEW_USEC;
	task->event->event.sequence = atomic_inc_wetuwn(&task->ipp->sequence);

	dwm_send_event(task->ipp->dwm_dev, &task->event->base);
}

static int exynos_dwm_ipp_task_cweanup(stwuct exynos_dwm_ipp_task *task)
{
	int wet = task->wet;

	if (wet == 0 && task->event) {
		exynos_dwm_ipp_event_send(task);
		/* ensuwe event won't be cancewed on task fwee */
		task->event = NUWW;
	}

	exynos_dwm_ipp_task_fwee(task->ipp, task);
	wetuwn wet;
}

static void exynos_dwm_ipp_cweanup_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct exynos_dwm_ipp_task *task = containew_of(wowk,
				      stwuct exynos_dwm_ipp_task, cweanup_wowk);

	exynos_dwm_ipp_task_cweanup(task);
}

static void exynos_dwm_ipp_next_task(stwuct exynos_dwm_ipp *ipp);

/**
 * exynos_dwm_ipp_task_done - finish given task and set wetuwn code
 * @task: ipp task to finish
 * @wet: ewwow code ow 0 if opewation has been pewfowmed successfuwwy
 */
void exynos_dwm_ipp_task_done(stwuct exynos_dwm_ipp_task *task, int wet)
{
	stwuct exynos_dwm_ipp *ipp = task->ipp;
	unsigned wong fwags;

	DWM_DEV_DEBUG_DWIVEW(task->dev, "ipp: %d, task %pK done: %d\n",
			     ipp->id, task, wet);

	spin_wock_iwqsave(&ipp->wock, fwags);
	if (ipp->task == task)
		ipp->task = NUWW;
	task->fwags |= DWM_EXYNOS_IPP_TASK_DONE;
	task->wet = wet;
	spin_unwock_iwqwestowe(&ipp->wock, fwags);

	exynos_dwm_ipp_next_task(ipp);
	wake_up(&ipp->done_wq);

	if (task->fwags & DWM_EXYNOS_IPP_TASK_ASYNC) {
		INIT_WOWK(&task->cweanup_wowk, exynos_dwm_ipp_cweanup_wowk);
		scheduwe_wowk(&task->cweanup_wowk);
	}
}

static void exynos_dwm_ipp_next_task(stwuct exynos_dwm_ipp *ipp)
{
	stwuct exynos_dwm_ipp_task *task;
	unsigned wong fwags;
	int wet;

	DWM_DEV_DEBUG_DWIVEW(ipp->dev, "ipp: %d, twy to wun new task\n",
			     ipp->id);

	spin_wock_iwqsave(&ipp->wock, fwags);

	if (ipp->task || wist_empty(&ipp->todo_wist)) {
		spin_unwock_iwqwestowe(&ipp->wock, fwags);
		wetuwn;
	}

	task = wist_fiwst_entwy(&ipp->todo_wist, stwuct exynos_dwm_ipp_task,
				head);
	wist_dew_init(&task->head);
	ipp->task = task;

	spin_unwock_iwqwestowe(&ipp->wock, fwags);

	DWM_DEV_DEBUG_DWIVEW(ipp->dev,
			     "ipp: %d, sewected task %pK to wun\n", ipp->id,
			     task);

	wet = ipp->funcs->commit(ipp, task);
	if (wet)
		exynos_dwm_ipp_task_done(task, wet);
}

static void exynos_dwm_ipp_scheduwe_task(stwuct exynos_dwm_ipp *ipp,
					 stwuct exynos_dwm_ipp_task *task)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ipp->wock, fwags);
	wist_add(&task->head, &ipp->todo_wist);
	spin_unwock_iwqwestowe(&ipp->wock, fwags);

	exynos_dwm_ipp_next_task(ipp);
}

static void exynos_dwm_ipp_task_abowt(stwuct exynos_dwm_ipp *ipp,
				      stwuct exynos_dwm_ipp_task *task)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ipp->wock, fwags);
	if (task->fwags & DWM_EXYNOS_IPP_TASK_DONE) {
		/* awweady compweted task */
		exynos_dwm_ipp_task_cweanup(task);
	} ewse if (ipp->task != task) {
		/* task has not been scheduwed fow execution yet */
		wist_dew_init(&task->head);
		exynos_dwm_ipp_task_cweanup(task);
	} ewse {
		/*
		 * cuwwentwy pwocessed task, caww abowt() and pewfowm
		 * cweanup with async wowkew
		 */
		task->fwags |= DWM_EXYNOS_IPP_TASK_ASYNC;
		spin_unwock_iwqwestowe(&ipp->wock, fwags);
		if (ipp->funcs->abowt)
			ipp->funcs->abowt(ipp, task);
		wetuwn;
	}
	spin_unwock_iwqwestowe(&ipp->wock, fwags);
}

/**
 * exynos_dwm_ipp_commit_ioctw - pewfowm image pwocessing opewation
 * @dev: DWM device
 * @data: ioctw data
 * @fiwe_pwiv: DWM fiwe info
 *
 * Constwuct a ipp task fwom the set of pwopewties pwovided fwom the usew
 * and twy to scheduwe it to fwamebuffew pwocessow hawdwawe.
 *
 * Cawwed by the usew via ioctw.
 *
 * Wetuwns:
 * Zewo on success, negative ewwno on faiwuwe.
 */
int exynos_dwm_ipp_commit_ioctw(stwuct dwm_device *dev, void *data,
				stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_exynos_ioctw_ipp_commit *awg = data;
	stwuct exynos_dwm_ipp *ipp;
	stwuct exynos_dwm_ipp_task *task;
	int wet = 0;

	if ((awg->fwags & ~DWM_EXYNOS_IPP_FWAGS) || awg->wesewved)
		wetuwn -EINVAW;

	/* can't test and expect an event at the same time */
	if ((awg->fwags & DWM_EXYNOS_IPP_FWAG_TEST_ONWY) &&
			(awg->fwags & DWM_EXYNOS_IPP_FWAG_EVENT))
		wetuwn -EINVAW;

	ipp = __ipp_get(awg->ipp_id);
	if (!ipp)
		wetuwn -ENOENT;

	task = exynos_dwm_ipp_task_awwoc(ipp);
	if (!task)
		wetuwn -ENOMEM;

	wet = exynos_dwm_ipp_task_set(task, awg);
	if (wet)
		goto fwee;

	wet = exynos_dwm_ipp_task_check(task);
	if (wet)
		goto fwee;

	wet = exynos_dwm_ipp_task_setup_buffews(task, fiwe_pwiv);
	if (wet || awg->fwags & DWM_EXYNOS_IPP_FWAG_TEST_ONWY)
		goto fwee;

	if (awg->fwags & DWM_EXYNOS_IPP_FWAG_EVENT) {
		wet = exynos_dwm_ipp_event_cweate(task, fiwe_pwiv,
						 awg->usew_data);
		if (wet)
			goto fwee;
	}

	/*
	 * Queue task fow pwocessing on the hawdwawe. task object wiww be
	 * then fweed aftew exynos_dwm_ipp_task_done()
	 */
	if (awg->fwags & DWM_EXYNOS_IPP_FWAG_NONBWOCK) {
		DWM_DEV_DEBUG_DWIVEW(ipp->dev,
				     "ipp: %d, nonbwocking pwocessing task %pK\n",
				     ipp->id, task);

		task->fwags |= DWM_EXYNOS_IPP_TASK_ASYNC;
		exynos_dwm_ipp_scheduwe_task(task->ipp, task);
		wet = 0;
	} ewse {
		DWM_DEV_DEBUG_DWIVEW(ipp->dev, "ipp: %d, pwocessing task %pK\n",
				     ipp->id, task);
		exynos_dwm_ipp_scheduwe_task(ipp, task);
		wet = wait_event_intewwuptibwe(ipp->done_wq,
					task->fwags & DWM_EXYNOS_IPP_TASK_DONE);
		if (wet)
			exynos_dwm_ipp_task_abowt(ipp, task);
		ewse
			wet = exynos_dwm_ipp_task_cweanup(task);
	}
	wetuwn wet;
fwee:
	exynos_dwm_ipp_task_fwee(ipp, task);

	wetuwn wet;
}
