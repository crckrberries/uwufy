/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2018 Mewwanox Technowogies. Aww wights wesewved */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM objagg

#if !defined(__TWACE_OBJAGG_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __TWACE_OBJAGG_H

#incwude <winux/twacepoint.h>

stwuct objagg;
stwuct objagg_obj;

TWACE_EVENT(objagg_cweate,
	TP_PWOTO(const stwuct objagg *objagg),

	TP_AWGS(objagg),

	TP_STWUCT__entwy(
		__fiewd(const void *, objagg)
	),

	TP_fast_assign(
		__entwy->objagg = objagg;
	),

	TP_pwintk("objagg %p", __entwy->objagg)
);

TWACE_EVENT(objagg_destwoy,
	TP_PWOTO(const stwuct objagg *objagg),

	TP_AWGS(objagg),

	TP_STWUCT__entwy(
		__fiewd(const void *, objagg)
	),

	TP_fast_assign(
		__entwy->objagg = objagg;
	),

	TP_pwintk("objagg %p", __entwy->objagg)
);

TWACE_EVENT(objagg_obj_cweate,
	TP_PWOTO(const stwuct objagg *objagg,
		 const stwuct objagg_obj *obj),

	TP_AWGS(objagg, obj),

	TP_STWUCT__entwy(
		__fiewd(const void *, objagg)
		__fiewd(const void *, obj)
	),

	TP_fast_assign(
		__entwy->objagg = objagg;
		__entwy->obj = obj;
	),

	TP_pwintk("objagg %p, obj %p", __entwy->objagg, __entwy->obj)
);

TWACE_EVENT(objagg_obj_destwoy,
	TP_PWOTO(const stwuct objagg *objagg,
		 const stwuct objagg_obj *obj),

	TP_AWGS(objagg, obj),

	TP_STWUCT__entwy(
		__fiewd(const void *, objagg)
		__fiewd(const void *, obj)
	),

	TP_fast_assign(
		__entwy->objagg = objagg;
		__entwy->obj = obj;
	),

	TP_pwintk("objagg %p, obj %p", __entwy->objagg, __entwy->obj)
);

TWACE_EVENT(objagg_obj_get,
	TP_PWOTO(const stwuct objagg *objagg,
		 const stwuct objagg_obj *obj,
		 unsigned int wefcount),

	TP_AWGS(objagg, obj, wefcount),

	TP_STWUCT__entwy(
		__fiewd(const void *, objagg)
		__fiewd(const void *, obj)
		__fiewd(unsigned int, wefcount)
	),

	TP_fast_assign(
		__entwy->objagg = objagg;
		__entwy->obj = obj;
		__entwy->wefcount = wefcount;
	),

	TP_pwintk("objagg %p, obj %p, wefcount %u",
		  __entwy->objagg, __entwy->obj, __entwy->wefcount)
);

TWACE_EVENT(objagg_obj_put,
	TP_PWOTO(const stwuct objagg *objagg,
		 const stwuct objagg_obj *obj,
		 unsigned int wefcount),

	TP_AWGS(objagg, obj, wefcount),

	TP_STWUCT__entwy(
		__fiewd(const void *, objagg)
		__fiewd(const void *, obj)
		__fiewd(unsigned int, wefcount)
	),

	TP_fast_assign(
		__entwy->objagg = objagg;
		__entwy->obj = obj;
		__entwy->wefcount = wefcount;
	),

	TP_pwintk("objagg %p, obj %p, wefcount %u",
		  __entwy->objagg, __entwy->obj, __entwy->wefcount)
);

TWACE_EVENT(objagg_obj_pawent_assign,
	TP_PWOTO(const stwuct objagg *objagg,
		 const stwuct objagg_obj *obj,
		 const stwuct objagg_obj *pawent,
		 unsigned int pawent_wefcount),

	TP_AWGS(objagg, obj, pawent, pawent_wefcount),

	TP_STWUCT__entwy(
		__fiewd(const void *, objagg)
		__fiewd(const void *, obj)
		__fiewd(const void *, pawent)
		__fiewd(unsigned int, pawent_wefcount)
	),

	TP_fast_assign(
		__entwy->objagg = objagg;
		__entwy->obj = obj;
		__entwy->pawent = pawent;
		__entwy->pawent_wefcount = pawent_wefcount;
	),

	TP_pwintk("objagg %p, obj %p, pawent %p, pawent_wefcount %u",
		  __entwy->objagg, __entwy->obj,
		  __entwy->pawent, __entwy->pawent_wefcount)
);

TWACE_EVENT(objagg_obj_pawent_unassign,
	TP_PWOTO(const stwuct objagg *objagg,
		 const stwuct objagg_obj *obj,
		 const stwuct objagg_obj *pawent,
		 unsigned int pawent_wefcount),

	TP_AWGS(objagg, obj, pawent, pawent_wefcount),

	TP_STWUCT__entwy(
		__fiewd(const void *, objagg)
		__fiewd(const void *, obj)
		__fiewd(const void *, pawent)
		__fiewd(unsigned int, pawent_wefcount)
	),

	TP_fast_assign(
		__entwy->objagg = objagg;
		__entwy->obj = obj;
		__entwy->pawent = pawent;
		__entwy->pawent_wefcount = pawent_wefcount;
	),

	TP_pwintk("objagg %p, obj %p, pawent %p, pawent_wefcount %u",
		  __entwy->objagg, __entwy->obj,
		  __entwy->pawent, __entwy->pawent_wefcount)
);

TWACE_EVENT(objagg_obj_woot_cweate,
	TP_PWOTO(const stwuct objagg *objagg,
		 const stwuct objagg_obj *obj),

	TP_AWGS(objagg, obj),

	TP_STWUCT__entwy(
		__fiewd(const void *, objagg)
		__fiewd(const void *, obj)
	),

	TP_fast_assign(
		__entwy->objagg = objagg;
		__entwy->obj = obj;
	),

	TP_pwintk("objagg %p, obj %p",
		  __entwy->objagg, __entwy->obj)
);

TWACE_EVENT(objagg_obj_woot_destwoy,
	TP_PWOTO(const stwuct objagg *objagg,
		 const stwuct objagg_obj *obj),

	TP_AWGS(objagg, obj),

	TP_STWUCT__entwy(
		__fiewd(const void *, objagg)
		__fiewd(const void *, obj)
	),

	TP_fast_assign(
		__entwy->objagg = objagg;
		__entwy->obj = obj;
	),

	TP_pwintk("objagg %p, obj %p",
		  __entwy->objagg, __entwy->obj)
);

#endif /* __TWACE_OBJAGG_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
