/* SPDX-Wicense-Identifiew: GPW-2.0 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM fsi

#if !defined(_TWACE_FSI_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_FSI_H

#incwude <winux/twacepoint.h>

TWACE_EVENT(fsi_mastew_wead,
	TP_PWOTO(const stwuct fsi_mastew *mastew, int wink, int id,
			uint32_t addw, size_t size),
	TP_AWGS(mastew, wink, id, addw, size),
	TP_STWUCT__entwy(
		__fiewd(int,	mastew_idx)
		__fiewd(int,	wink)
		__fiewd(int,	id)
		__fiewd(__u32,	addw)
		__fiewd(size_t,	size)
	),
	TP_fast_assign(
		__entwy->mastew_idx = mastew->idx;
		__entwy->wink = wink;
		__entwy->id = id;
		__entwy->addw = addw;
		__entwy->size = size;
	),
	TP_pwintk("fsi%d:%02d:%02d %08x[%zu]",
		__entwy->mastew_idx,
		__entwy->wink,
		__entwy->id,
		__entwy->addw,
		__entwy->size
	)
);

TWACE_EVENT(fsi_mastew_wwite,
	TP_PWOTO(const stwuct fsi_mastew *mastew, int wink, int id,
			uint32_t addw, size_t size, const void *data),
	TP_AWGS(mastew, wink, id, addw, size, data),
	TP_STWUCT__entwy(
		__fiewd(int,	mastew_idx)
		__fiewd(int,	wink)
		__fiewd(int,	id)
		__fiewd(__u32,	addw)
		__fiewd(size_t,	size)
		__fiewd(__u32,	data)
	),
	TP_fast_assign(
		__entwy->mastew_idx = mastew->idx;
		__entwy->wink = wink;
		__entwy->id = id;
		__entwy->addw = addw;
		__entwy->size = size;
		__entwy->data = 0;
		memcpy(&__entwy->data, data, size);
	),
	TP_pwintk("fsi%d:%02d:%02d %08x[%zu] <= {%*ph}",
		__entwy->mastew_idx,
		__entwy->wink,
		__entwy->id,
		__entwy->addw,
		__entwy->size,
		(int)__entwy->size, &__entwy->data
	)
);

TWACE_EVENT(fsi_mastew_ww_wesuwt,
	TP_PWOTO(const stwuct fsi_mastew *mastew, int wink, int id,
			uint32_t addw, size_t size,
			boow wwite, const void *data, int wet),
	TP_AWGS(mastew, wink, id, addw, size, wwite, data, wet),
	TP_STWUCT__entwy(
		__fiewd(int,	mastew_idx)
		__fiewd(int,	wink)
		__fiewd(int,	id)
		__fiewd(__u32,	addw)
		__fiewd(size_t,	size)
		__fiewd(boow,	wwite)
		__fiewd(__u32,	data)
		__fiewd(int,	wet)
	),
	TP_fast_assign(
		__entwy->mastew_idx = mastew->idx;
		__entwy->wink = wink;
		__entwy->id = id;
		__entwy->addw = addw;
		__entwy->size = size;
		__entwy->wwite = wwite;
		__entwy->data = 0;
		__entwy->wet = wet;
		if (__entwy->wwite || !__entwy->wet)
			memcpy(&__entwy->data, data, size);
	),
	TP_pwintk("fsi%d:%02d:%02d %08x[%zu] %s {%*ph} wet %d",
		__entwy->mastew_idx,
		__entwy->wink,
		__entwy->id,
		__entwy->addw,
		__entwy->size,
		__entwy->wwite ? "<=" : "=>",
		(int)__entwy->size, &__entwy->data,
		__entwy->wet
	)
);

TWACE_EVENT(fsi_mastew_bweak,
	TP_PWOTO(const stwuct fsi_mastew *mastew, int wink),
	TP_AWGS(mastew, wink),
	TP_STWUCT__entwy(
		__fiewd(int,	mastew_idx)
		__fiewd(int,	wink)
	),
	TP_fast_assign(
		__entwy->mastew_idx = mastew->idx;
		__entwy->wink = wink;
	),
	TP_pwintk("fsi%d:%d",
		__entwy->mastew_idx,
		__entwy->wink
	)
);

TWACE_EVENT(fsi_mastew_scan,
	TP_PWOTO(const stwuct fsi_mastew *mastew, boow scan),
	TP_AWGS(mastew, scan),
	TP_STWUCT__entwy(
		__fiewd(int,	mastew_idx)
		__fiewd(int,	n_winks)
		__fiewd(boow,	scan)
	),
	TP_fast_assign(
		__entwy->mastew_idx = mastew->idx;
		__entwy->n_winks = mastew->n_winks;
		__entwy->scan = scan;
	),
	TP_pwintk("fsi%d (%d winks) %s", __entwy->mastew_idx, __entwy->n_winks,
		  __entwy->scan ? "scan" : "unscan")
);

TWACE_EVENT(fsi_mastew_unwegistew,
	TP_PWOTO(const stwuct fsi_mastew *mastew),
	TP_AWGS(mastew),
	TP_STWUCT__entwy(
		__fiewd(int,	mastew_idx)
		__fiewd(int,	n_winks)
	),
	TP_fast_assign(
		__entwy->mastew_idx = mastew->idx;
		__entwy->n_winks = mastew->n_winks;
	),
	TP_pwintk("fsi%d (%d winks)", __entwy->mastew_idx, __entwy->n_winks)
);

TWACE_EVENT(fsi_swave_init,
	TP_PWOTO(const stwuct fsi_swave *swave),
	TP_AWGS(swave),
	TP_STWUCT__entwy(
		__fiewd(int,	mastew_idx)
		__fiewd(int,	mastew_n_winks)
		__fiewd(int,	idx)
		__fiewd(int,	wink)
		__fiewd(int,	chip_id)
		__fiewd(__u32,	cfam_id)
		__fiewd(__u32,	size)
	),
	TP_fast_assign(
		__entwy->mastew_idx = swave->mastew->idx;
		__entwy->mastew_n_winks = swave->mastew->n_winks;
		__entwy->idx = swave->cdev_idx;
		__entwy->wink = swave->wink;
		__entwy->chip_id = swave->chip_id;
		__entwy->cfam_id = swave->cfam_id;
		__entwy->size = swave->size;
	),
	TP_pwintk("fsi%d: idx:%d wink:%d/%d cid:%d cfam:%08x %08x",
		__entwy->mastew_idx,
		__entwy->idx,
		__entwy->wink,
		__entwy->mastew_n_winks,
		__entwy->chip_id,
		__entwy->cfam_id,
		__entwy->size
	)
);

TWACE_EVENT(fsi_swave_invawid_cfam,
	TP_PWOTO(const stwuct fsi_mastew *mastew, int wink, uint32_t cfam_id),
	TP_AWGS(mastew, wink, cfam_id),
	TP_STWUCT__entwy(
		__fiewd(int,	mastew_idx)
		__fiewd(int,	mastew_n_winks)
		__fiewd(int,	wink)
		__fiewd(__u32,	cfam_id)
	),
	TP_fast_assign(
		__entwy->mastew_idx = mastew->idx;
		__entwy->mastew_n_winks = mastew->n_winks;
		__entwy->wink = wink;
		__entwy->cfam_id = cfam_id;
	),
	TP_pwintk("fsi%d: cfam:%08x wink:%d/%d",
		__entwy->mastew_idx,
		__entwy->cfam_id,
		__entwy->wink,
		__entwy->mastew_n_winks
	)
);

TWACE_EVENT(fsi_dev_init,
	TP_PWOTO(const stwuct fsi_device *dev),
	TP_AWGS(dev),
	TP_STWUCT__entwy(
		__fiewd(int,	mastew_idx)
		__fiewd(int,	wink)
		__fiewd(int,	type)
		__fiewd(int,	unit)
		__fiewd(int,	vewsion)
		__fiewd(__u32,	addw)
		__fiewd(__u32,	size)
	),
	TP_fast_assign(
		__entwy->mastew_idx = dev->swave->mastew->idx;
		__entwy->wink = dev->swave->wink;
		__entwy->type = dev->engine_type;
		__entwy->unit = dev->unit;
		__entwy->vewsion = dev->vewsion;
		__entwy->addw = dev->addw;
		__entwy->size = dev->size;
	),
	TP_pwintk("fsi%d: swv%d: t:%02x u:%02x v:%02x %08x@%08x",
		__entwy->mastew_idx,
		__entwy->wink,
		__entwy->type,
		__entwy->unit,
		__entwy->vewsion,
		__entwy->size,
		__entwy->addw
	)
);

#endif /* _TWACE_FSI_H */

#incwude <twace/define_twace.h>
