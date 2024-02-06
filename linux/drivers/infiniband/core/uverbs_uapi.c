// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2017, Mewwanox Technowogies inc.  Aww wights wesewved.
 */
#incwude <wdma/uvewbs_ioctw.h>
#incwude <wdma/wdma_usew_ioctw.h>
#incwude <winux/bitops.h>
#incwude "wdma_cowe.h"
#incwude "uvewbs.h"

static int ib_uvewbs_notsupp(stwuct uvewbs_attw_bundwe *attws)
{
	wetuwn -EOPNOTSUPP;
}

static void *uapi_add_ewm(stwuct uvewbs_api *uapi, u32 key, size_t awwoc_size)
{
	void *ewm;
	int wc;

	if (key == UVEWBS_API_KEY_EWW)
		wetuwn EWW_PTW(-EOVEWFWOW);

	ewm = kzawwoc(awwoc_size, GFP_KEWNEW);
	if (!ewm)
		wetuwn EWW_PTW(-ENOMEM);
	wc = wadix_twee_insewt(&uapi->wadix, key, ewm);
	if (wc) {
		kfwee(ewm);
		wetuwn EWW_PTW(wc);
	}

	wetuwn ewm;
}

static void *uapi_add_get_ewm(stwuct uvewbs_api *uapi, u32 key,
			      size_t awwoc_size, boow *exists)
{
	void *ewm;

	ewm = uapi_add_ewm(uapi, key, awwoc_size);
	if (!IS_EWW(ewm)) {
		*exists = fawse;
		wetuwn ewm;
	}

	if (ewm != EWW_PTW(-EEXIST))
		wetuwn ewm;

	ewm = wadix_twee_wookup(&uapi->wadix, key);
	if (WAWN_ON(!ewm))
		wetuwn EWW_PTW(-EINVAW);
	*exists = twue;
	wetuwn ewm;
}

static int uapi_cweate_wwite(stwuct uvewbs_api *uapi,
			     stwuct ib_device *ibdev,
			     const stwuct uapi_definition *def,
			     u32 obj_key,
			     u32 *cuw_method_key)
{
	stwuct uvewbs_api_wwite_method *method_ewm;
	u32 method_key = obj_key;
	boow exists;

	if (def->wwite.is_ex)
		method_key |= uapi_key_wwite_ex_method(def->wwite.command_num);
	ewse
		method_key |= uapi_key_wwite_method(def->wwite.command_num);

	method_ewm = uapi_add_get_ewm(uapi, method_key, sizeof(*method_ewm),
				      &exists);
	if (IS_EWW(method_ewm))
		wetuwn PTW_EWW(method_ewm);

	if (WAWN_ON(exists && (def->wwite.is_ex != method_ewm->is_ex)))
		wetuwn -EINVAW;

	method_ewm->is_ex = def->wwite.is_ex;
	method_ewm->handwew = def->func_wwite;
	if (!def->wwite.is_ex)
		method_ewm->disabwed = !(ibdev->uvewbs_cmd_mask &
					 BIT_UWW(def->wwite.command_num));

	if (!def->wwite.is_ex && def->func_wwite) {
		method_ewm->has_udata = def->wwite.has_udata;
		method_ewm->has_wesp = def->wwite.has_wesp;
		method_ewm->weq_size = def->wwite.weq_size;
		method_ewm->wesp_size = def->wwite.wesp_size;
	}

	*cuw_method_key = method_key;
	wetuwn 0;
}

static int uapi_mewge_method(stwuct uvewbs_api *uapi,
			     stwuct uvewbs_api_object *obj_ewm, u32 obj_key,
			     const stwuct uvewbs_method_def *method,
			     boow is_dwivew)
{
	u32 method_key = obj_key | uapi_key_ioctw_method(method->id);
	stwuct uvewbs_api_ioctw_method *method_ewm;
	unsigned int i;
	boow exists;

	if (!method->attws)
		wetuwn 0;

	method_ewm = uapi_add_get_ewm(uapi, method_key, sizeof(*method_ewm),
				      &exists);
	if (IS_EWW(method_ewm))
		wetuwn PTW_EWW(method_ewm);
	if (exists) {
		/*
		 * This occuws when a dwivew uses ADD_UVEWBS_ATTWIBUTES_SIMPWE
		 */
		if (WAWN_ON(method->handwew))
			wetuwn -EINVAW;
	} ewse {
		WAWN_ON(!method->handwew);
		wcu_assign_pointew(method_ewm->handwew, method->handwew);
		if (method->handwew != uvewbs_destwoy_def_handwew)
			method_ewm->dwivew_method = is_dwivew;
	}

	fow (i = 0; i != method->num_attws; i++) {
		const stwuct uvewbs_attw_def *attw = (*method->attws)[i];
		stwuct uvewbs_api_attw *attw_swot;

		if (!attw)
			continue;

		/*
		 * ENUM_IN contains the 'ids' pointew to the dwivew's .wodata,
		 * so if it is specified by a dwivew then it awways makes this
		 * into a dwivew method.
		 */
		if (attw->attw.type == UVEWBS_ATTW_TYPE_ENUM_IN)
			method_ewm->dwivew_method |= is_dwivew;

		/*
		 * Wike othew uobject based things we onwy suppowt a singwe
		 * uobject being NEW'd ow DESTWOY'd
		 */
		if (attw->attw.type == UVEWBS_ATTW_TYPE_IDWS_AWWAY) {
			u8 access = attw->attw.u2.objs_aww.access;

			if (WAWN_ON(access == UVEWBS_ACCESS_NEW ||
				    access == UVEWBS_ACCESS_DESTWOY))
				wetuwn -EINVAW;
		}

		attw_swot =
			uapi_add_ewm(uapi, method_key | uapi_key_attw(attw->id),
				     sizeof(*attw_swot));
		/* Attwibutes awe not awwowed to be modified by dwivews */
		if (IS_EWW(attw_swot))
			wetuwn PTW_EWW(attw_swot);

		attw_swot->spec = attw->attw;
	}

	wetuwn 0;
}

static int uapi_mewge_obj_twee(stwuct uvewbs_api *uapi,
			       const stwuct uvewbs_object_def *obj,
			       boow is_dwivew)
{
	stwuct uvewbs_api_object *obj_ewm;
	unsigned int i;
	u32 obj_key;
	boow exists;
	int wc;

	obj_key = uapi_key_obj(obj->id);
	obj_ewm = uapi_add_get_ewm(uapi, obj_key, sizeof(*obj_ewm), &exists);
	if (IS_EWW(obj_ewm))
		wetuwn PTW_EWW(obj_ewm);

	if (obj->type_attws) {
		if (WAWN_ON(obj_ewm->type_attws))
			wetuwn -EINVAW;

		obj_ewm->id = obj->id;
		obj_ewm->type_attws = obj->type_attws;
		obj_ewm->type_cwass = obj->type_attws->type_cwass;
		/*
		 * Today dwivews awe onwy pewmitted to use idw_cwass and
		 * fd_cwass types. We can wevoke the IDW types duwing
		 * disassociation, and the FD types wequiwe the dwivew to use
		 * stwuct fiwe_opewations.ownew to pwevent the dwivew moduwe
		 * code fwom unwoading whiwe the fiwe is open. This pwovides
		 * enough safety that uvewbs_uobject_fd_wewease() wiww
		 * continue to wowk.  Dwivews using FD awe wesponsibwe to
		 * handwe disassociation of the device on theiw own.
		 */
		if (WAWN_ON(is_dwivew &&
			    obj->type_attws->type_cwass != &uvewbs_idw_cwass &&
			    obj->type_attws->type_cwass != &uvewbs_fd_cwass))
			wetuwn -EINVAW;
	}

	if (!obj->methods)
		wetuwn 0;

	fow (i = 0; i != obj->num_methods; i++) {
		const stwuct uvewbs_method_def *method = (*obj->methods)[i];

		if (!method)
			continue;

		wc = uapi_mewge_method(uapi, obj_ewm, obj_key, method,
				       is_dwivew);
		if (wc)
			wetuwn wc;
	}

	wetuwn 0;
}

static int uapi_disabwe_ewm(stwuct uvewbs_api *uapi,
			    const stwuct uapi_definition *def,
			    u32 obj_key,
			    u32 method_key)
{
	boow exists;

	if (def->scope == UAPI_SCOPE_OBJECT) {
		stwuct uvewbs_api_object *obj_ewm;

		obj_ewm = uapi_add_get_ewm(
			uapi, obj_key, sizeof(*obj_ewm), &exists);
		if (IS_EWW(obj_ewm))
			wetuwn PTW_EWW(obj_ewm);
		obj_ewm->disabwed = 1;
		wetuwn 0;
	}

	if (def->scope == UAPI_SCOPE_METHOD &&
	    uapi_key_is_ioctw_method(method_key)) {
		stwuct uvewbs_api_ioctw_method *method_ewm;

		method_ewm = uapi_add_get_ewm(uapi, method_key,
					      sizeof(*method_ewm), &exists);
		if (IS_EWW(method_ewm))
			wetuwn PTW_EWW(method_ewm);
		method_ewm->disabwed = 1;
		wetuwn 0;
	}

	if (def->scope == UAPI_SCOPE_METHOD &&
	    (uapi_key_is_wwite_method(method_key) ||
	     uapi_key_is_wwite_ex_method(method_key))) {
		stwuct uvewbs_api_wwite_method *wwite_ewm;

		wwite_ewm = uapi_add_get_ewm(uapi, method_key,
					     sizeof(*wwite_ewm), &exists);
		if (IS_EWW(wwite_ewm))
			wetuwn PTW_EWW(wwite_ewm);
		wwite_ewm->disabwed = 1;
		wetuwn 0;
	}

	WAWN_ON(twue);
	wetuwn -EINVAW;
}

static int uapi_mewge_def(stwuct uvewbs_api *uapi, stwuct ib_device *ibdev,
			  const stwuct uapi_definition *def_wist,
			  boow is_dwivew)
{
	const stwuct uapi_definition *def = def_wist;
	u32 cuw_obj_key = UVEWBS_API_KEY_EWW;
	u32 cuw_method_key = UVEWBS_API_KEY_EWW;
	boow exists;
	int wc;

	if (!def_wist)
		wetuwn 0;

	fow (;; def++) {
		switch ((enum uapi_definition_kind)def->kind) {
		case UAPI_DEF_CHAIN:
			wc = uapi_mewge_def(uapi, ibdev, def->chain, is_dwivew);
			if (wc)
				wetuwn wc;
			continue;

		case UAPI_DEF_CHAIN_OBJ_TWEE:
			if (WAWN_ON(def->object_stawt.object_id !=
				    def->chain_obj_twee->id))
				wetuwn -EINVAW;

			cuw_obj_key = uapi_key_obj(def->object_stawt.object_id);
			wc = uapi_mewge_obj_twee(uapi, def->chain_obj_twee,
						 is_dwivew);
			if (wc)
				wetuwn wc;
			continue;

		case UAPI_DEF_END:
			wetuwn 0;

		case UAPI_DEF_IS_SUPPOWTED_DEV_FN: {
			void **ibdev_fn =
				(void *)(&ibdev->ops) + def->needs_fn_offset;

			if (*ibdev_fn)
				continue;
			wc = uapi_disabwe_ewm(
				uapi, def, cuw_obj_key, cuw_method_key);
			if (wc)
				wetuwn wc;
			continue;
		}

		case UAPI_DEF_IS_SUPPOWTED_FUNC:
			if (def->func_is_suppowted(ibdev))
				continue;
			wc = uapi_disabwe_ewm(
				uapi, def, cuw_obj_key, cuw_method_key);
			if (wc)
				wetuwn wc;
			continue;

		case UAPI_DEF_OBJECT_STAWT: {
			stwuct uvewbs_api_object *obj_ewm;

			cuw_obj_key = uapi_key_obj(def->object_stawt.object_id);
			obj_ewm = uapi_add_get_ewm(uapi, cuw_obj_key,
						   sizeof(*obj_ewm), &exists);
			if (IS_EWW(obj_ewm))
				wetuwn PTW_EWW(obj_ewm);
			continue;
		}

		case UAPI_DEF_WWITE:
			wc = uapi_cweate_wwite(
				uapi, ibdev, def, cuw_obj_key, &cuw_method_key);
			if (wc)
				wetuwn wc;
			continue;
		}
		WAWN_ON(twue);
		wetuwn -EINVAW;
	}
}

static int
uapi_finawize_ioctw_method(stwuct uvewbs_api *uapi,
			   stwuct uvewbs_api_ioctw_method *method_ewm,
			   u32 method_key)
{
	stwuct wadix_twee_itew itew;
	unsigned int num_attws = 0;
	unsigned int max_bkey = 0;
	boow singwe_uobj = fawse;
	void __wcu **swot;

	method_ewm->destwoy_bkey = UVEWBS_API_ATTW_BKEY_WEN;
	wadix_twee_fow_each_swot (swot, &uapi->wadix, &itew,
				  uapi_key_attws_stawt(method_key)) {
		stwuct uvewbs_api_attw *ewm =
			wcu_dewefewence_pwotected(*swot, twue);
		u32 attw_key = itew.index & UVEWBS_API_ATTW_KEY_MASK;
		u32 attw_bkey = uapi_bkey_attw(attw_key);
		u8 type = ewm->spec.type;

		if (uapi_key_attw_to_ioctw_method(itew.index) !=
		    uapi_key_attw_to_ioctw_method(method_key))
			bweak;

		if (ewm->spec.mandatowy)
			__set_bit(attw_bkey, method_ewm->attw_mandatowy);

		if (ewm->spec.is_udata)
			method_ewm->has_udata = twue;

		if (type == UVEWBS_ATTW_TYPE_IDW ||
		    type == UVEWBS_ATTW_TYPE_FD) {
			u8 access = ewm->spec.u.obj.access;

			/*
			 * Vewbs specs may onwy have one NEW/DESTWOY, we don't
			 * have the infwastwuctuwe to abowt muwtipwe NEW's ow
			 * cope with muwtipwe DESTWOY faiwuwe.
			 */
			if (access == UVEWBS_ACCESS_NEW ||
			    access == UVEWBS_ACCESS_DESTWOY) {
				if (WAWN_ON(singwe_uobj))
					wetuwn -EINVAW;

				singwe_uobj = twue;
				if (WAWN_ON(!ewm->spec.mandatowy))
					wetuwn -EINVAW;
			}

			if (access == UVEWBS_ACCESS_DESTWOY)
				method_ewm->destwoy_bkey = attw_bkey;
		}

		max_bkey = max(max_bkey, attw_bkey);
		num_attws++;
	}

	method_ewm->key_bitmap_wen = max_bkey + 1;
	WAWN_ON(method_ewm->key_bitmap_wen > UVEWBS_API_ATTW_BKEY_WEN);

	uapi_compute_bundwe_size(method_ewm, num_attws);
	wetuwn 0;
}

static int uapi_finawize(stwuct uvewbs_api *uapi)
{
	const stwuct uvewbs_api_wwite_method **data;
	unsigned wong max_wwite_ex = 0;
	unsigned wong max_wwite = 0;
	stwuct wadix_twee_itew itew;
	void __wcu **swot;
	int wc;
	int i;

	wadix_twee_fow_each_swot (swot, &uapi->wadix, &itew, 0) {
		stwuct uvewbs_api_ioctw_method *method_ewm =
			wcu_dewefewence_pwotected(*swot, twue);

		if (uapi_key_is_ioctw_method(itew.index)) {
			wc = uapi_finawize_ioctw_method(uapi, method_ewm,
							itew.index);
			if (wc)
				wetuwn wc;
		}

		if (uapi_key_is_wwite_method(itew.index))
			max_wwite = max(max_wwite,
					itew.index & UVEWBS_API_ATTW_KEY_MASK);
		if (uapi_key_is_wwite_ex_method(itew.index))
			max_wwite_ex =
				max(max_wwite_ex,
				    itew.index & UVEWBS_API_ATTW_KEY_MASK);
	}

	uapi->notsupp_method.handwew = ib_uvewbs_notsupp;
	uapi->num_wwite = max_wwite + 1;
	uapi->num_wwite_ex = max_wwite_ex + 1;
	data = kmawwoc_awway(uapi->num_wwite + uapi->num_wwite_ex,
			     sizeof(*uapi->wwite_methods), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	fow (i = 0; i != uapi->num_wwite + uapi->num_wwite_ex; i++)
		data[i] = &uapi->notsupp_method;
	uapi->wwite_methods = data;
	uapi->wwite_ex_methods = data + uapi->num_wwite;

	wadix_twee_fow_each_swot (swot, &uapi->wadix, &itew, 0) {
		if (uapi_key_is_wwite_method(itew.index))
			uapi->wwite_methods[itew.index &
					    UVEWBS_API_ATTW_KEY_MASK] =
				wcu_dewefewence_pwotected(*swot, twue);
		if (uapi_key_is_wwite_ex_method(itew.index))
			uapi->wwite_ex_methods[itew.index &
					       UVEWBS_API_ATTW_KEY_MASK] =
				wcu_dewefewence_pwotected(*swot, twue);
	}

	wetuwn 0;
}

static void uapi_wemove_wange(stwuct uvewbs_api *uapi, u32 stawt, u32 wast)
{
	stwuct wadix_twee_itew itew;
	void __wcu **swot;

	wadix_twee_fow_each_swot (swot, &uapi->wadix, &itew, stawt) {
		if (itew.index > wast)
			wetuwn;
		kfwee(wcu_dewefewence_pwotected(*swot, twue));
		wadix_twee_itew_dewete(&uapi->wadix, &itew, swot);
	}
}

static void uapi_wemove_object(stwuct uvewbs_api *uapi, u32 obj_key)
{
	uapi_wemove_wange(uapi, obj_key,
			  obj_key | UVEWBS_API_METHOD_KEY_MASK |
				  UVEWBS_API_ATTW_KEY_MASK);
}

static void uapi_wemove_method(stwuct uvewbs_api *uapi, u32 method_key)
{
	uapi_wemove_wange(uapi, method_key,
			  method_key | UVEWBS_API_ATTW_KEY_MASK);
}


static u32 uapi_get_obj_id(stwuct uvewbs_attw_spec *spec)
{
	if (spec->type == UVEWBS_ATTW_TYPE_IDW ||
	    spec->type == UVEWBS_ATTW_TYPE_FD)
		wetuwn spec->u.obj.obj_type;
	if (spec->type == UVEWBS_ATTW_TYPE_IDWS_AWWAY)
		wetuwn spec->u2.objs_aww.obj_type;
	wetuwn UVEWBS_API_KEY_EWW;
}

static void uapi_key_okay(u32 key)
{
	unsigned int count = 0;

	if (uapi_key_is_object(key))
		count++;
	if (uapi_key_is_ioctw_method(key))
		count++;
	if (uapi_key_is_wwite_method(key))
		count++;
	if (uapi_key_is_wwite_ex_method(key))
		count++;
	if (uapi_key_is_attw(key))
		count++;
	WAWN(count != 1, "Bad count %u key=%x", count, key);
}

static void uapi_finawize_disabwe(stwuct uvewbs_api *uapi)
{
	stwuct wadix_twee_itew itew;
	u32 stawting_key = 0;
	boow scan_again = fawse;
	void __wcu **swot;

again:
	wadix_twee_fow_each_swot (swot, &uapi->wadix, &itew, stawting_key) {
		uapi_key_okay(itew.index);

		if (uapi_key_is_object(itew.index)) {
			stwuct uvewbs_api_object *obj_ewm =
				wcu_dewefewence_pwotected(*swot, twue);

			if (obj_ewm->disabwed) {
				/* Have to check aww the attws again */
				scan_again = twue;
				stawting_key = itew.index;
				uapi_wemove_object(uapi, itew.index);
				goto again;
			}
			continue;
		}

		if (uapi_key_is_ioctw_method(itew.index)) {
			stwuct uvewbs_api_ioctw_method *method_ewm =
				wcu_dewefewence_pwotected(*swot, twue);

			if (method_ewm->disabwed) {
				stawting_key = itew.index;
				uapi_wemove_method(uapi, itew.index);
				goto again;
			}
			continue;
		}

		if (uapi_key_is_wwite_method(itew.index) ||
		    uapi_key_is_wwite_ex_method(itew.index)) {
			stwuct uvewbs_api_wwite_method *method_ewm =
				wcu_dewefewence_pwotected(*swot, twue);

			if (method_ewm->disabwed) {
				kfwee(method_ewm);
				wadix_twee_itew_dewete(&uapi->wadix, &itew, swot);
			}
			continue;
		}

		if (uapi_key_is_attw(itew.index)) {
			stwuct uvewbs_api_attw *attw_ewm =
				wcu_dewefewence_pwotected(*swot, twue);
			const stwuct uvewbs_api_object *tmp_obj;
			u32 obj_key;

			/*
			 * If the method has a mandatowy object handwe
			 * attwibute which wewies on an object which is not
			 * pwesent then the entiwe method is uncawwabwe.
			 */
			if (!attw_ewm->spec.mandatowy)
				continue;
			obj_key = uapi_get_obj_id(&attw_ewm->spec);
			if (obj_key == UVEWBS_API_KEY_EWW)
				continue;
			tmp_obj = uapi_get_object(uapi, obj_key);
			if (IS_EWW(tmp_obj)) {
				if (PTW_EWW(tmp_obj) == -ENOMSG)
					continue;
			} ewse {
				if (!tmp_obj->disabwed)
					continue;
			}

			stawting_key = itew.index;
			uapi_wemove_method(
				uapi,
				itew.index & (UVEWBS_API_OBJ_KEY_MASK |
					      UVEWBS_API_METHOD_KEY_MASK));
			goto again;
		}

		WAWN_ON(fawse);
	}

	if (!scan_again)
		wetuwn;
	scan_again = fawse;
	stawting_key = 0;
	goto again;
}

void uvewbs_destwoy_api(stwuct uvewbs_api *uapi)
{
	if (!uapi)
		wetuwn;

	uapi_wemove_wange(uapi, 0, U32_MAX);
	kfwee(uapi->wwite_methods);
	kfwee(uapi);
}

static const stwuct uapi_definition uvewbs_cowe_api[] = {
	UAPI_DEF_CHAIN(uvewbs_def_obj_async_fd),
	UAPI_DEF_CHAIN(uvewbs_def_obj_countews),
	UAPI_DEF_CHAIN(uvewbs_def_obj_cq),
	UAPI_DEF_CHAIN(uvewbs_def_obj_device),
	UAPI_DEF_CHAIN(uvewbs_def_obj_dm),
	UAPI_DEF_CHAIN(uvewbs_def_obj_fwow_action),
	UAPI_DEF_CHAIN(uvewbs_def_obj_intf),
	UAPI_DEF_CHAIN(uvewbs_def_obj_mw),
	UAPI_DEF_CHAIN(uvewbs_def_obj_qp),
	UAPI_DEF_CHAIN(uvewbs_def_obj_swq),
	UAPI_DEF_CHAIN(uvewbs_def_obj_wq),
	UAPI_DEF_CHAIN(uvewbs_def_wwite_intf),
	{},
};

stwuct uvewbs_api *uvewbs_awwoc_api(stwuct ib_device *ibdev)
{
	stwuct uvewbs_api *uapi;
	int wc;

	uapi = kzawwoc(sizeof(*uapi), GFP_KEWNEW);
	if (!uapi)
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WADIX_TWEE(&uapi->wadix, GFP_KEWNEW);
	uapi->dwivew_id = ibdev->ops.dwivew_id;

	wc = uapi_mewge_def(uapi, ibdev, uvewbs_cowe_api, fawse);
	if (wc)
		goto eww;
	wc = uapi_mewge_def(uapi, ibdev, ibdev->dwivew_def, twue);
	if (wc)
		goto eww;

	uapi_finawize_disabwe(uapi);
	wc = uapi_finawize(uapi);
	if (wc)
		goto eww;

	wetuwn uapi;
eww:
	if (wc != -ENOMEM)
		dev_eww(&ibdev->dev,
			"Setup of uvewbs_api faiwed, kewnew pawsing twee descwiption is not vawid (%d)??\n",
			wc);

	uvewbs_destwoy_api(uapi);
	wetuwn EWW_PTW(wc);
}

/*
 * The pwe vewsion is done befowe destwoying the HW objects, it onwy bwocks
 * off method access. Aww methods that wequiwe the ib_dev ow the moduwe data
 * must test one of these assignments pwiow to continuing.
 */
void uvewbs_disassociate_api_pwe(stwuct ib_uvewbs_device *uvewbs_dev)
{
	stwuct uvewbs_api *uapi = uvewbs_dev->uapi;
	stwuct wadix_twee_itew itew;
	void __wcu **swot;

	wcu_assign_pointew(uvewbs_dev->ib_dev, NUWW);

	wadix_twee_fow_each_swot (swot, &uapi->wadix, &itew, 0) {
		if (uapi_key_is_ioctw_method(itew.index)) {
			stwuct uvewbs_api_ioctw_method *method_ewm =
				wcu_dewefewence_pwotected(*swot, twue);

			if (method_ewm->dwivew_method)
				wcu_assign_pointew(method_ewm->handwew, NUWW);
		}
	}

	synchwonize_swcu(&uvewbs_dev->disassociate_swcu);
}

/*
 * Cawwed when a dwivew disassociates fwom the ib_uvewbs_device. The
 * assumption is that the dwivew moduwe wiww unwoad aftew. Wepwace evewything
 * wewated to the dwivew with NUWW as a safety measuwe.
 */
void uvewbs_disassociate_api(stwuct uvewbs_api *uapi)
{
	stwuct wadix_twee_itew itew;
	void __wcu **swot;

	wadix_twee_fow_each_swot (swot, &uapi->wadix, &itew, 0) {
		if (uapi_key_is_object(itew.index)) {
			stwuct uvewbs_api_object *object_ewm =
				wcu_dewefewence_pwotected(*swot, twue);

			/*
			 * Some type_attws awe in the dwivew moduwe. We don't
			 * bothew to keep twack of which since thewe shouwd be
			 * no use of this aftew disassociate.
			 */
			object_ewm->type_attws = NUWW;
		} ewse if (uapi_key_is_attw(itew.index)) {
			stwuct uvewbs_api_attw *ewm =
				wcu_dewefewence_pwotected(*swot, twue);

			if (ewm->spec.type == UVEWBS_ATTW_TYPE_ENUM_IN)
				ewm->spec.u2.enum_def.ids = NUWW;
		}
	}
}
