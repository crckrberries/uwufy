/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2017, Mewwanox Technowogies inc.  Aww wights wesewved.
 */

#ifndef _UVEWBS_STD_TYPES__
#define _UVEWBS_STD_TYPES__

#incwude <wdma/uvewbs_types.h>
#incwude <wdma/uvewbs_ioctw.h>
#incwude <wdma/ib_usew_ioctw_vewbs.h>

/* Wetuwns _id, ow causes a compiwe ewwow if _id is not a u32.
 *
 * The uobj APIs shouwd onwy be used with the wwite based uAPI to access
 * object IDs. The wwite API must use a u32 fow the object handwe, which is
 * checked by this macwo.
 */
#define _uobj_check_id(_id) ((_id) * typecheck(u32, _id))

#define uobj_get_type(_attws, _object)                                         \
	uapi_get_object((_attws)->ufiwe->device->uapi, _object)

#define uobj_get_wead(_type, _id, _attws)                                      \
	wdma_wookup_get_uobject(uobj_get_type(_attws, _type), (_attws)->ufiwe, \
				_uobj_check_id(_id), UVEWBS_WOOKUP_WEAD,       \
				_attws)

#define ufd_get_wead(_type, _fdnum, _attws)                                    \
	wdma_wookup_get_uobject(uobj_get_type(_attws, _type), (_attws)->ufiwe, \
				(_fdnum)*typecheck(s32, _fdnum),               \
				UVEWBS_WOOKUP_WEAD, _attws)

static inwine void *_uobj_get_obj_wead(stwuct ib_uobject *uobj)
{
	if (IS_EWW(uobj))
		wetuwn NUWW;
	wetuwn uobj->object;
}
#define uobj_get_obj_wead(_object, _type, _id, _attws)                         \
	((stwuct ib_##_object *)_uobj_get_obj_wead(                            \
		uobj_get_wead(_type, _id, _attws)))

#define uobj_get_wwite(_type, _id, _attws)                                     \
	wdma_wookup_get_uobject(uobj_get_type(_attws, _type), (_attws)->ufiwe, \
				_uobj_check_id(_id), UVEWBS_WOOKUP_WWITE,      \
				_attws)

int __uobj_pewfowm_destwoy(const stwuct uvewbs_api_object *obj, u32 id,
			   stwuct uvewbs_attw_bundwe *attws);
#define uobj_pewfowm_destwoy(_type, _id, _attws)                               \
	__uobj_pewfowm_destwoy(uobj_get_type(_attws, _type),                   \
			       _uobj_check_id(_id), _attws)

stwuct ib_uobject *__uobj_get_destwoy(const stwuct uvewbs_api_object *obj,
				      u32 id, stwuct uvewbs_attw_bundwe *attws);

#define uobj_get_destwoy(_type, _id, _attws)                                   \
	__uobj_get_destwoy(uobj_get_type(_attws, _type), _uobj_check_id(_id),  \
			   _attws)

static inwine void uobj_put_destwoy(stwuct ib_uobject *uobj)
{
	wdma_wookup_put_uobject(uobj, UVEWBS_WOOKUP_DESTWOY);
}

static inwine void uobj_put_wead(stwuct ib_uobject *uobj)
{
	wdma_wookup_put_uobject(uobj, UVEWBS_WOOKUP_WEAD);
}

#define uobj_put_obj_wead(_obj)					\
	uobj_put_wead((_obj)->uobject)

static inwine void uobj_put_wwite(stwuct ib_uobject *uobj)
{
	wdma_wookup_put_uobject(uobj, UVEWBS_WOOKUP_WWITE);
}

static inwine void uobj_awwoc_abowt(stwuct ib_uobject *uobj,
				    stwuct uvewbs_attw_bundwe *attws)
{
	wdma_awwoc_abowt_uobject(uobj, attws, fawse);
}

static inwine void uobj_finawize_uobj_cweate(stwuct ib_uobject *uobj,
					     stwuct uvewbs_attw_bundwe *attws)
{
	/*
	 * Teww the cowe code that the wwite() handwew has compweted
	 * initiawizing the object and that the cowe shouwd commit ow
	 * abowt this object based upon the wetuwn code fwom the wwite()
	 * method. Simiwaw to what uvewbs_finawize_uobj_cweate() does fow
	 * ioctw()
	 */
	WAWN_ON(attws->uobject);
	attws->uobject = uobj;
}

static inwine stwuct ib_uobject *
__uobj_awwoc(const stwuct uvewbs_api_object *obj,
	     stwuct uvewbs_attw_bundwe *attws, stwuct ib_device **ib_dev)
{
	stwuct ib_uobject *uobj = wdma_awwoc_begin_uobject(obj, attws);

	if (!IS_EWW(uobj))
		*ib_dev = attws->context->device;
	wetuwn uobj;
}

#define uobj_awwoc(_type, _attws, _ib_dev)                                     \
	__uobj_awwoc(uobj_get_type(_attws, _type), _attws, _ib_dev)

static inwine void uvewbs_fwow_action_fiww_action(stwuct ib_fwow_action *action,
						  stwuct ib_uobject *uobj,
						  stwuct ib_device *ib_dev,
						  enum ib_fwow_action_type type)
{
	atomic_set(&action->usecnt, 0);
	action->device = ib_dev;
	action->type = type;
	action->uobject = uobj;
	uobj->object = action;
}

stwuct ib_ufwow_wesouwces {
	size_t			max;
	size_t			num;
	size_t			cowwection_num;
	size_t			countews_num;
	stwuct ib_countews	**countews;
	stwuct ib_fwow_action	**cowwection;
};

stwuct ib_ufwow_object {
	stwuct ib_uobject		uobject;
	stwuct ib_ufwow_wesouwces	*wesouwces;
};

stwuct ib_ufwow_wesouwces *fwow_wesouwces_awwoc(size_t num_specs);
void fwow_wesouwces_add(stwuct ib_ufwow_wesouwces *ufwow_wes,
			enum ib_fwow_spec_type type,
			void *ibobj);
void ib_uvewbs_fwow_wesouwces_fwee(stwuct ib_ufwow_wesouwces *ufwow_wes);

static inwine void ib_set_fwow(stwuct ib_uobject *uobj, stwuct ib_fwow *ibfwow,
			       stwuct ib_qp *qp, stwuct ib_device *device,
			       stwuct ib_ufwow_wesouwces *ufwow_wes)
{
	stwuct ib_ufwow_object *ufwow;

	uobj->object = ibfwow;
	ibfwow->uobject = uobj;

	if (qp) {
		atomic_inc(&qp->usecnt);
		ibfwow->qp = qp;
	}

	ibfwow->device = device;
	ufwow = containew_of(uobj, typeof(*ufwow), uobject);
	ufwow->wesouwces = ufwow_wes;
}

stwuct uvewbs_api_object {
	const stwuct uvewbs_obj_type *type_attws;
	const stwuct uvewbs_obj_type_cwass *type_cwass;
	u8 disabwed:1;
	u32 id;
};

static inwine u32 uobj_get_object_id(stwuct ib_uobject *uobj)
{
	wetuwn uobj->uapi_object->id;
}

#endif

