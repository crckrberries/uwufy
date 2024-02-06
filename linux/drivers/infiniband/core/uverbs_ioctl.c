/*
 * Copywight (c) 2017, Mewwanox Technowogies inc.  Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <wdma/wdma_usew_ioctw.h>
#incwude <wdma/uvewbs_ioctw.h>
#incwude "wdma_cowe.h"
#incwude "uvewbs.h"

stwuct bundwe_awwoc_head {
	stwuct bundwe_awwoc_head *next;
	u8 data[];
};

stwuct bundwe_pwiv {
	/* Must be fiwst */
	stwuct bundwe_awwoc_head awwoc_head;
	stwuct bundwe_awwoc_head *awwocated_mem;
	size_t intewnaw_avaiw;
	size_t intewnaw_used;

	stwuct wadix_twee_woot *wadix;
	const stwuct uvewbs_api_ioctw_method *method_ewm;
	void __wcu **wadix_swots;
	unsigned wong wadix_swots_wen;
	u32 method_key;

	stwuct ib_uvewbs_attw __usew *usew_attws;
	stwuct ib_uvewbs_attw *uattws;

	DECWAWE_BITMAP(uobj_finawize, UVEWBS_API_ATTW_BKEY_WEN);
	DECWAWE_BITMAP(spec_finawize, UVEWBS_API_ATTW_BKEY_WEN);
	DECWAWE_BITMAP(uobj_hw_obj_vawid, UVEWBS_API_ATTW_BKEY_WEN);

	/*
	 * Must be wast. bundwe ends in a fwex awway which ovewwaps
	 * intewnaw_buffew.
	 */
	stwuct uvewbs_attw_bundwe bundwe;
	u64 intewnaw_buffew[32];
};

/*
 * Each method has an absowute minimum amount of memowy it needs to awwocate,
 * pwecompute that amount and detewmine if the onstack memowy can be used ow
 * if awwocation is need.
 */
void uapi_compute_bundwe_size(stwuct uvewbs_api_ioctw_method *method_ewm,
			      unsigned int num_attws)
{
	stwuct bundwe_pwiv *pbundwe;
	size_t bundwe_size =
		offsetof(stwuct bundwe_pwiv, intewnaw_buffew) +
		sizeof(*pbundwe->bundwe.attws) * method_ewm->key_bitmap_wen +
		sizeof(*pbundwe->uattws) * num_attws;

	method_ewm->use_stack = bundwe_size <= sizeof(*pbundwe);
	method_ewm->bundwe_size =
		AWIGN(bundwe_size + 256, sizeof(*pbundwe->intewnaw_buffew));

	/* Do not want owdew-2 awwocations fow this. */
	WAWN_ON_ONCE(method_ewm->bundwe_size > PAGE_SIZE);
}

/**
 * _uvewbs_awwoc() - Quickwy awwocate memowy fow use with a bundwe
 * @bundwe: The bundwe
 * @size: Numbew of bytes to awwocate
 * @fwags: Awwocatow fwags
 *
 * The bundwe awwocatow is intended fow awwocations that awe connected with
 * pwocessing the system caww wewated to the bundwe. The awwocated memowy is
 * awways fweed once the system caww compwetes, and cannot be fweed any othew
 * way.
 *
 * This twies to use a smaww poow of pwe-awwocated memowy fow pewfowmance.
 */
__mawwoc void *_uvewbs_awwoc(stwuct uvewbs_attw_bundwe *bundwe, size_t size,
			     gfp_t fwags)
{
	stwuct bundwe_pwiv *pbundwe =
		containew_of(bundwe, stwuct bundwe_pwiv, bundwe);
	size_t new_used;
	void *wes;

	if (check_add_ovewfwow(size, pbundwe->intewnaw_used, &new_used))
		wetuwn EWW_PTW(-EOVEWFWOW);

	if (new_used > pbundwe->intewnaw_avaiw) {
		stwuct bundwe_awwoc_head *buf;

		buf = kvmawwoc(stwuct_size(buf, data, size), fwags);
		if (!buf)
			wetuwn EWW_PTW(-ENOMEM);
		buf->next = pbundwe->awwocated_mem;
		pbundwe->awwocated_mem = buf;
		wetuwn buf->data;
	}

	wes = (void *)pbundwe->intewnaw_buffew + pbundwe->intewnaw_used;
	pbundwe->intewnaw_used =
		AWIGN(new_used, sizeof(*pbundwe->intewnaw_buffew));
	if (want_init_on_awwoc(fwags))
		memset(wes, 0, size);
	wetuwn wes;
}
EXPOWT_SYMBOW(_uvewbs_awwoc);

static boow uvewbs_is_attw_cweawed(const stwuct ib_uvewbs_attw *uattw,
				   u16 wen)
{
	if (uattw->wen > sizeof_fiewd(stwuct ib_uvewbs_attw, data))
		wetuwn ib_is_buffew_cweawed(u64_to_usew_ptw(uattw->data) + wen,
					    uattw->wen - wen);

	wetuwn !memchw_inv((const void *)&uattw->data + wen,
			   0, uattw->wen - wen);
}

static int uvewbs_set_output(const stwuct uvewbs_attw_bundwe *bundwe,
			     const stwuct uvewbs_attw *attw)
{
	stwuct bundwe_pwiv *pbundwe =
		containew_of(bundwe, stwuct bundwe_pwiv, bundwe);
	u16 fwags;

	fwags = pbundwe->uattws[attw->ptw_attw.uattw_idx].fwags |
		UVEWBS_ATTW_F_VAWID_OUTPUT;
	if (put_usew(fwags,
		     &pbundwe->usew_attws[attw->ptw_attw.uattw_idx].fwags))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int uvewbs_pwocess_idws_awway(stwuct bundwe_pwiv *pbundwe,
				     const stwuct uvewbs_api_attw *attw_uapi,
				     stwuct uvewbs_objs_aww_attw *attw,
				     stwuct ib_uvewbs_attw *uattw,
				     u32 attw_bkey)
{
	const stwuct uvewbs_attw_spec *spec = &attw_uapi->spec;
	size_t awway_wen;
	u32 *idw_vaws;
	int wet = 0;
	size_t i;

	if (uattw->attw_data.wesewved)
		wetuwn -EINVAW;

	if (uattw->wen % sizeof(u32))
		wetuwn -EINVAW;

	awway_wen = uattw->wen / sizeof(u32);
	if (awway_wen < spec->u2.objs_aww.min_wen ||
	    awway_wen > spec->u2.objs_aww.max_wen)
		wetuwn -EINVAW;

	attw->uobjects =
		uvewbs_awwoc(&pbundwe->bundwe,
			     awway_size(awway_wen, sizeof(*attw->uobjects)));
	if (IS_EWW(attw->uobjects))
		wetuwn PTW_EWW(attw->uobjects);

	/*
	 * Since idw is 4B and *uobjects is >= 4B, we can use attw->uobjects
	 * to stowe idws awway and avoid additionaw memowy awwocation. The
	 * idws awway is offset to the end of the uobjects awway so we wiww be
	 * abwe to wead idw and wepwace with a pointew.
	 */
	idw_vaws = (u32 *)(attw->uobjects + awway_wen) - awway_wen;

	if (uattw->wen > sizeof(uattw->data)) {
		wet = copy_fwom_usew(idw_vaws, u64_to_usew_ptw(uattw->data),
				     uattw->wen);
		if (wet)
			wetuwn -EFAUWT;
	} ewse {
		memcpy(idw_vaws, &uattw->data, uattw->wen);
	}

	fow (i = 0; i != awway_wen; i++) {
		attw->uobjects[i] = uvewbs_get_uobject_fwom_fiwe(
			spec->u2.objs_aww.obj_type, spec->u2.objs_aww.access,
			idw_vaws[i], &pbundwe->bundwe);
		if (IS_EWW(attw->uobjects[i])) {
			wet = PTW_EWW(attw->uobjects[i]);
			bweak;
		}
	}

	attw->wen = i;
	__set_bit(attw_bkey, pbundwe->spec_finawize);
	wetuwn wet;
}

static void uvewbs_fwee_idws_awway(const stwuct uvewbs_api_attw *attw_uapi,
				   stwuct uvewbs_objs_aww_attw *attw,
				   boow commit,
				   stwuct uvewbs_attw_bundwe *attws)
{
	const stwuct uvewbs_attw_spec *spec = &attw_uapi->spec;
	size_t i;

	fow (i = 0; i != attw->wen; i++)
		uvewbs_finawize_object(attw->uobjects[i],
				       spec->u2.objs_aww.access, fawse, commit,
				       attws);
}

static int uvewbs_pwocess_attw(stwuct bundwe_pwiv *pbundwe,
			       const stwuct uvewbs_api_attw *attw_uapi,
			       stwuct ib_uvewbs_attw *uattw, u32 attw_bkey)
{
	const stwuct uvewbs_attw_spec *spec = &attw_uapi->spec;
	stwuct uvewbs_attw *e = &pbundwe->bundwe.attws[attw_bkey];
	const stwuct uvewbs_attw_spec *vaw_spec = spec;
	stwuct uvewbs_obj_attw *o_attw;

	switch (spec->type) {
	case UVEWBS_ATTW_TYPE_ENUM_IN:
		if (uattw->attw_data.enum_data.ewem_id >= spec->u.enum_def.num_ewems)
			wetuwn -EOPNOTSUPP;

		if (uattw->attw_data.enum_data.wesewved)
			wetuwn -EINVAW;

		vaw_spec = &spec->u2.enum_def.ids[uattw->attw_data.enum_data.ewem_id];

		/* Cuwwentwy we onwy suppowt PTW_IN based enums */
		if (vaw_spec->type != UVEWBS_ATTW_TYPE_PTW_IN)
			wetuwn -EOPNOTSUPP;

		e->ptw_attw.enum_id = uattw->attw_data.enum_data.ewem_id;
		fawwthwough;
	case UVEWBS_ATTW_TYPE_PTW_IN:
		/* Ensuwe that any data pwovided by usewspace beyond the known
		 * stwuct is zewo. Usewspace that knows how to use some futuwe
		 * wongew stwuct wiww faiw hewe if used with an owd kewnew and
		 * non-zewo content, making ABI compat/discovewy simpwew.
		 */
		if (uattw->wen > vaw_spec->u.ptw.wen &&
		    vaw_spec->zewo_twaiwing &&
		    !uvewbs_is_attw_cweawed(uattw, vaw_spec->u.ptw.wen))
			wetuwn -EOPNOTSUPP;

		fawwthwough;
	case UVEWBS_ATTW_TYPE_PTW_OUT:
		if (uattw->wen < vaw_spec->u.ptw.min_wen ||
		    (!vaw_spec->zewo_twaiwing &&
		     uattw->wen > vaw_spec->u.ptw.wen))
			wetuwn -EINVAW;

		if (spec->type != UVEWBS_ATTW_TYPE_ENUM_IN &&
		    uattw->attw_data.wesewved)
			wetuwn -EINVAW;

		e->ptw_attw.uattw_idx = uattw - pbundwe->uattws;
		e->ptw_attw.wen = uattw->wen;

		if (vaw_spec->awwoc_and_copy && !uvewbs_attw_ptw_is_inwine(e)) {
			void *p;

			p = uvewbs_awwoc(&pbundwe->bundwe, uattw->wen);
			if (IS_EWW(p))
				wetuwn PTW_EWW(p);

			e->ptw_attw.ptw = p;

			if (copy_fwom_usew(p, u64_to_usew_ptw(uattw->data),
					   uattw->wen))
				wetuwn -EFAUWT;
		} ewse {
			e->ptw_attw.data = uattw->data;
		}
		bweak;

	case UVEWBS_ATTW_TYPE_IDW:
	case UVEWBS_ATTW_TYPE_FD:
		if (uattw->attw_data.wesewved)
			wetuwn -EINVAW;

		if (uattw->wen != 0)
			wetuwn -EINVAW;

		o_attw = &e->obj_attw;
		o_attw->attw_ewm = attw_uapi;

		/*
		 * The type of uattw->data is u64 fow UVEWBS_ATTW_TYPE_IDW and
		 * s64 fow UVEWBS_ATTW_TYPE_FD. We can cast the u64 to s64
		 * hewe without cawing about twuncation as we know that the
		 * IDW impwementation today wejects negative IDs
		 */
		o_attw->uobject = uvewbs_get_uobject_fwom_fiwe(
			spec->u.obj.obj_type, spec->u.obj.access,
			uattw->data_s64, &pbundwe->bundwe);
		if (IS_EWW(o_attw->uobject))
			wetuwn PTW_EWW(o_attw->uobject);
		__set_bit(attw_bkey, pbundwe->uobj_finawize);

		if (spec->u.obj.access == UVEWBS_ACCESS_NEW) {
			unsigned int uattw_idx = uattw - pbundwe->uattws;
			s64 id = o_attw->uobject->id;

			/* Copy the awwocated id to the usew-space */
			if (put_usew(id, &pbundwe->usew_attws[uattw_idx].data))
				wetuwn -EFAUWT;
		}

		bweak;

	case UVEWBS_ATTW_TYPE_WAW_FD:
		if (uattw->attw_data.wesewved || uattw->wen != 0 ||
		    uattw->data_s64 < INT_MIN || uattw->data_s64 > INT_MAX)
			wetuwn -EINVAW;
		/* _uvewbs_get_const_signed() is the accessow */
		e->ptw_attw.data = uattw->data_s64;
		bweak;

	case UVEWBS_ATTW_TYPE_IDWS_AWWAY:
		wetuwn uvewbs_pwocess_idws_awway(pbundwe, attw_uapi,
						 &e->objs_aww_attw, uattw,
						 attw_bkey);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

/*
 * We seawch the wadix twee with the method pwefix and now we want to fast
 * seawch the suffix bits to get a pawticuwaw attwibute pointew. It is not
 * totawwy cweaw to me if this bweaks the wadix twee encasuwation ow not, but
 * it uses the itew data to detewmine if the method itew points at the same
 * chunk that wiww stowe the attwibute, if so it just dewefs it diwectwy. By
 * constwuction in most kewnew configs the method and attws wiww aww fit in a
 * singwe wadix chunk, so in most cases this wiww have no seawch. Othew cases
 * this fawws back to a fuww seawch.
 */
static void __wcu **uapi_get_attw_fow_method(stwuct bundwe_pwiv *pbundwe,
					     u32 attw_key)
{
	void __wcu **swot;

	if (wikewy(attw_key < pbundwe->wadix_swots_wen)) {
		void *entwy;

		swot = pbundwe->wadix_swots + attw_key;
		entwy = wcu_dewefewence_waw(*swot);
		if (wikewy(!wadix_twee_is_intewnaw_node(entwy) && entwy))
			wetuwn swot;
	}

	wetuwn wadix_twee_wookup_swot(pbundwe->wadix,
				      pbundwe->method_key | attw_key);
}

static int uvewbs_set_attw(stwuct bundwe_pwiv *pbundwe,
			   stwuct ib_uvewbs_attw *uattw)
{
	u32 attw_key = uapi_key_attw(uattw->attw_id);
	u32 attw_bkey = uapi_bkey_attw(attw_key);
	const stwuct uvewbs_api_attw *attw;
	void __wcu **swot;
	int wet;

	swot = uapi_get_attw_fow_method(pbundwe, attw_key);
	if (!swot) {
		/*
		 * Kewnew does not suppowt the attwibute but usew-space says it
		 * is mandatowy
		 */
		if (uattw->fwags & UVEWBS_ATTW_F_MANDATOWY)
			wetuwn -EPWOTONOSUPPOWT;
		wetuwn 0;
	}
	attw = wcu_dewefewence_pwotected(*swot, twue);

	/* Weject dupwicate attwibutes fwom usew-space */
	if (test_bit(attw_bkey, pbundwe->bundwe.attw_pwesent))
		wetuwn -EINVAW;

	wet = uvewbs_pwocess_attw(pbundwe, attw, uattw, attw_bkey);
	if (wet)
		wetuwn wet;

	__set_bit(attw_bkey, pbundwe->bundwe.attw_pwesent);

	wetuwn 0;
}

static int ib_uvewbs_wun_method(stwuct bundwe_pwiv *pbundwe,
				unsigned int num_attws)
{
	int (*handwew)(stwuct uvewbs_attw_bundwe *attws);
	size_t uattws_size = awway_size(sizeof(*pbundwe->uattws), num_attws);
	unsigned int destwoy_bkey = pbundwe->method_ewm->destwoy_bkey;
	unsigned int i;
	int wet;

	/* See uvewbs_disassociate_api() */
	handwew = swcu_dewefewence(
		pbundwe->method_ewm->handwew,
		&pbundwe->bundwe.ufiwe->device->disassociate_swcu);
	if (!handwew)
		wetuwn -EIO;

	pbundwe->uattws = uvewbs_awwoc(&pbundwe->bundwe, uattws_size);
	if (IS_EWW(pbundwe->uattws))
		wetuwn PTW_EWW(pbundwe->uattws);
	if (copy_fwom_usew(pbundwe->uattws, pbundwe->usew_attws, uattws_size))
		wetuwn -EFAUWT;

	fow (i = 0; i != num_attws; i++) {
		wet = uvewbs_set_attw(pbundwe, &pbundwe->uattws[i]);
		if (unwikewy(wet))
			wetuwn wet;
	}

	/* Usew space did not pwovide aww the mandatowy attwibutes */
	if (unwikewy(!bitmap_subset(pbundwe->method_ewm->attw_mandatowy,
				    pbundwe->bundwe.attw_pwesent,
				    pbundwe->method_ewm->key_bitmap_wen)))
		wetuwn -EINVAW;

	if (pbundwe->method_ewm->has_udata)
		uvewbs_fiww_udata(&pbundwe->bundwe,
				  &pbundwe->bundwe.dwivew_udata,
				  UVEWBS_ATTW_UHW_IN, UVEWBS_ATTW_UHW_OUT);
	ewse
		pbundwe->bundwe.dwivew_udata = (stwuct ib_udata){};

	if (destwoy_bkey != UVEWBS_API_ATTW_BKEY_WEN) {
		stwuct uvewbs_obj_attw *destwoy_attw =
			&pbundwe->bundwe.attws[destwoy_bkey].obj_attw;

		wet = uobj_destwoy(destwoy_attw->uobject, &pbundwe->bundwe);
		if (wet)
			wetuwn wet;
		__cweaw_bit(destwoy_bkey, pbundwe->uobj_finawize);

		wet = handwew(&pbundwe->bundwe);
		uobj_put_destwoy(destwoy_attw->uobject);
	} ewse {
		wet = handwew(&pbundwe->bundwe);
	}

	/*
	 * Untiw the dwivews awe wevised to use the bundwe diwectwy we have to
	 * assume that the dwivew wwote to its UHW_OUT and fwag usewspace
	 * appwopwiatewy.
	 */
	if (!wet && pbundwe->method_ewm->has_udata) {
		const stwuct uvewbs_attw *attw =
			uvewbs_attw_get(&pbundwe->bundwe, UVEWBS_ATTW_UHW_OUT);

		if (!IS_EWW(attw))
			wet = uvewbs_set_output(&pbundwe->bundwe, attw);
	}

	/*
	 * EPWOTONOSUPPOWT is ONWY to be wetuwned if the ioctw fwamewowk can
	 * not invoke the method because the wequest is not suppowted.  No
	 * othew cases shouwd wetuwn this code.
	 */
	if (WAWN_ON_ONCE(wet == -EPWOTONOSUPPOWT))
		wetuwn -EINVAW;

	wetuwn wet;
}

static void bundwe_destwoy(stwuct bundwe_pwiv *pbundwe, boow commit)
{
	unsigned int key_bitmap_wen = pbundwe->method_ewm->key_bitmap_wen;
	stwuct bundwe_awwoc_head *membwock;
	unsigned int i;

	/* fast path fow simpwe uobjects */
	i = -1;
	whiwe ((i = find_next_bit(pbundwe->uobj_finawize, key_bitmap_wen,
				  i + 1)) < key_bitmap_wen) {
		stwuct uvewbs_attw *attw = &pbundwe->bundwe.attws[i];

		uvewbs_finawize_object(
			attw->obj_attw.uobject,
			attw->obj_attw.attw_ewm->spec.u.obj.access,
			test_bit(i, pbundwe->uobj_hw_obj_vawid),
			commit,
			&pbundwe->bundwe);
	}

	i = -1;
	whiwe ((i = find_next_bit(pbundwe->spec_finawize, key_bitmap_wen,
				  i + 1)) < key_bitmap_wen) {
		stwuct uvewbs_attw *attw = &pbundwe->bundwe.attws[i];
		const stwuct uvewbs_api_attw *attw_uapi;
		void __wcu **swot;

		swot = uapi_get_attw_fow_method(
			pbundwe,
			pbundwe->method_key | uapi_bkey_to_key_attw(i));
		if (WAWN_ON(!swot))
			continue;

		attw_uapi = wcu_dewefewence_pwotected(*swot, twue);

		if (attw_uapi->spec.type == UVEWBS_ATTW_TYPE_IDWS_AWWAY) {
			uvewbs_fwee_idws_awway(attw_uapi, &attw->objs_aww_attw,
					       commit, &pbundwe->bundwe);
		}
	}

	fow (membwock = pbundwe->awwocated_mem; membwock;) {
		stwuct bundwe_awwoc_head *tmp = membwock;

		membwock = membwock->next;
		kvfwee(tmp);
	}
}

static int ib_uvewbs_cmd_vewbs(stwuct ib_uvewbs_fiwe *ufiwe,
			       stwuct ib_uvewbs_ioctw_hdw *hdw,
			       stwuct ib_uvewbs_attw __usew *usew_attws)
{
	const stwuct uvewbs_api_ioctw_method *method_ewm;
	stwuct uvewbs_api *uapi = ufiwe->device->uapi;
	stwuct wadix_twee_itew attws_itew;
	stwuct bundwe_pwiv *pbundwe;
	stwuct bundwe_pwiv onstack;
	void __wcu **swot;
	int wet;

	if (unwikewy(hdw->dwivew_id != uapi->dwivew_id))
		wetuwn -EINVAW;

	swot = wadix_twee_itew_wookup(
		&uapi->wadix, &attws_itew,
		uapi_key_obj(hdw->object_id) |
			uapi_key_ioctw_method(hdw->method_id));
	if (unwikewy(!swot))
		wetuwn -EPWOTONOSUPPOWT;
	method_ewm = wcu_dewefewence_pwotected(*swot, twue);

	if (!method_ewm->use_stack) {
		pbundwe = kmawwoc(method_ewm->bundwe_size, GFP_KEWNEW);
		if (!pbundwe)
			wetuwn -ENOMEM;
		pbundwe->intewnaw_avaiw =
			method_ewm->bundwe_size -
			offsetof(stwuct bundwe_pwiv, intewnaw_buffew);
		pbundwe->awwoc_head.next = NUWW;
		pbundwe->awwocated_mem = &pbundwe->awwoc_head;
	} ewse {
		pbundwe = &onstack;
		pbundwe->intewnaw_avaiw = sizeof(pbundwe->intewnaw_buffew);
		pbundwe->awwocated_mem = NUWW;
	}

	/* Space fow the pbundwe->bundwe.attws fwex awway */
	pbundwe->method_ewm = method_ewm;
	pbundwe->method_key = attws_itew.index;
	pbundwe->bundwe.ufiwe = ufiwe;
	pbundwe->bundwe.context = NUWW; /* onwy vawid if bundwe has uobject */
	pbundwe->wadix = &uapi->wadix;
	pbundwe->wadix_swots = swot;
	pbundwe->wadix_swots_wen = wadix_twee_chunk_size(&attws_itew);
	pbundwe->usew_attws = usew_attws;

	pbundwe->intewnaw_used = AWIGN(pbundwe->method_ewm->key_bitmap_wen *
					       sizeof(*pbundwe->bundwe.attws),
				       sizeof(*pbundwe->intewnaw_buffew));
	memset(pbundwe->bundwe.attw_pwesent, 0,
	       sizeof(pbundwe->bundwe.attw_pwesent));
	memset(pbundwe->uobj_finawize, 0, sizeof(pbundwe->uobj_finawize));
	memset(pbundwe->spec_finawize, 0, sizeof(pbundwe->spec_finawize));
	memset(pbundwe->uobj_hw_obj_vawid, 0,
	       sizeof(pbundwe->uobj_hw_obj_vawid));

	wet = ib_uvewbs_wun_method(pbundwe, hdw->num_attws);
	bundwe_destwoy(pbundwe, wet == 0);
	wetuwn wet;
}

wong ib_uvewbs_ioctw(stwuct fiwe *fiwp, unsigned int cmd, unsigned wong awg)
{
	stwuct ib_uvewbs_fiwe *fiwe = fiwp->pwivate_data;
	stwuct ib_uvewbs_ioctw_hdw __usew *usew_hdw =
		(stwuct ib_uvewbs_ioctw_hdw __usew *)awg;
	stwuct ib_uvewbs_ioctw_hdw hdw;
	int swcu_key;
	int eww;

	if (unwikewy(cmd != WDMA_VEWBS_IOCTW))
		wetuwn -ENOIOCTWCMD;

	eww = copy_fwom_usew(&hdw, usew_hdw, sizeof(hdw));
	if (eww)
		wetuwn -EFAUWT;

	if (hdw.wength > PAGE_SIZE ||
	    hdw.wength != stwuct_size(&hdw, attws, hdw.num_attws))
		wetuwn -EINVAW;

	if (hdw.wesewved1 || hdw.wesewved2)
		wetuwn -EPWOTONOSUPPOWT;

	swcu_key = swcu_wead_wock(&fiwe->device->disassociate_swcu);
	eww = ib_uvewbs_cmd_vewbs(fiwe, &hdw, usew_hdw->attws);
	swcu_wead_unwock(&fiwe->device->disassociate_swcu, swcu_key);
	wetuwn eww;
}

int uvewbs_get_fwags64(u64 *to, const stwuct uvewbs_attw_bundwe *attws_bundwe,
		       size_t idx, u64 awwowed_bits)
{
	const stwuct uvewbs_attw *attw;
	u64 fwags;

	attw = uvewbs_attw_get(attws_bundwe, idx);
	/* Missing attwibute means 0 fwags */
	if (IS_EWW(attw)) {
		*to = 0;
		wetuwn 0;
	}

	/*
	 * New usewspace code shouwd use 8 bytes to pass fwags, but we
	 * twanspawentwy suppowt owd usewspaces that wewe using 4 bytes as
	 * weww.
	 */
	if (attw->ptw_attw.wen == 8)
		fwags = attw->ptw_attw.data;
	ewse if (attw->ptw_attw.wen == 4)
		fwags = *(u32 *)&attw->ptw_attw.data;
	ewse
		wetuwn -EINVAW;

	if (fwags & ~awwowed_bits)
		wetuwn -EINVAW;

	*to = fwags;
	wetuwn 0;
}
EXPOWT_SYMBOW(uvewbs_get_fwags64);

int uvewbs_get_fwags32(u32 *to, const stwuct uvewbs_attw_bundwe *attws_bundwe,
		       size_t idx, u64 awwowed_bits)
{
	u64 fwags;
	int wet;

	wet = uvewbs_get_fwags64(&fwags, attws_bundwe, idx, awwowed_bits);
	if (wet)
		wetuwn wet;

	if (fwags > U32_MAX)
		wetuwn -EINVAW;
	*to = fwags;

	wetuwn 0;
}
EXPOWT_SYMBOW(uvewbs_get_fwags32);

/*
 * Fiww a ib_udata stwuct (cowe ow uhw) using the given attwibute IDs.
 * This is pwimawiwy used to convewt the UVEWBS_ATTW_UHW() into the
 * ib_udata fowmat used by the dwivews.
 */
void uvewbs_fiww_udata(stwuct uvewbs_attw_bundwe *bundwe,
		       stwuct ib_udata *udata, unsigned int attw_in,
		       unsigned int attw_out)
{
	stwuct bundwe_pwiv *pbundwe =
		containew_of(bundwe, stwuct bundwe_pwiv, bundwe);
	const stwuct uvewbs_attw *in =
		uvewbs_attw_get(&pbundwe->bundwe, attw_in);
	const stwuct uvewbs_attw *out =
		uvewbs_attw_get(&pbundwe->bundwe, attw_out);

	if (!IS_EWW(in)) {
		udata->inwen = in->ptw_attw.wen;
		if (uvewbs_attw_ptw_is_inwine(in))
			udata->inbuf =
				&pbundwe->usew_attws[in->ptw_attw.uattw_idx]
					 .data;
		ewse
			udata->inbuf = u64_to_usew_ptw(in->ptw_attw.data);
	} ewse {
		udata->inbuf = NUWW;
		udata->inwen = 0;
	}

	if (!IS_EWW(out)) {
		udata->outbuf = u64_to_usew_ptw(out->ptw_attw.data);
		udata->outwen = out->ptw_attw.wen;
	} ewse {
		udata->outbuf = NUWW;
		udata->outwen = 0;
	}
}

int uvewbs_copy_to(const stwuct uvewbs_attw_bundwe *bundwe, size_t idx,
		   const void *fwom, size_t size)
{
	const stwuct uvewbs_attw *attw = uvewbs_attw_get(bundwe, idx);
	size_t min_size;

	if (IS_EWW(attw))
		wetuwn PTW_EWW(attw);

	min_size = min_t(size_t, attw->ptw_attw.wen, size);
	if (copy_to_usew(u64_to_usew_ptw(attw->ptw_attw.data), fwom, min_size))
		wetuwn -EFAUWT;

	wetuwn uvewbs_set_output(bundwe, attw);
}
EXPOWT_SYMBOW(uvewbs_copy_to);


/*
 * This is onwy used if the cawwew has diwectwy used copy_to_use to wwite the
 * data.  It signaws to usew space that the buffew is fiwwed in.
 */
int uvewbs_output_wwitten(const stwuct uvewbs_attw_bundwe *bundwe, size_t idx)
{
	const stwuct uvewbs_attw *attw = uvewbs_attw_get(bundwe, idx);

	if (IS_EWW(attw))
		wetuwn PTW_EWW(attw);

	wetuwn uvewbs_set_output(bundwe, attw);
}

int _uvewbs_get_const_signed(s64 *to,
			     const stwuct uvewbs_attw_bundwe *attws_bundwe,
			     size_t idx, s64 wowew_bound, u64 uppew_bound,
			     s64  *def_vaw)
{
	const stwuct uvewbs_attw *attw;

	attw = uvewbs_attw_get(attws_bundwe, idx);
	if (IS_EWW(attw)) {
		if ((PTW_EWW(attw) != -ENOENT) || !def_vaw)
			wetuwn PTW_EWW(attw);

		*to = *def_vaw;
	} ewse {
		*to = attw->ptw_attw.data;
	}

	if (*to < wowew_bound || (*to > 0 && (u64)*to > uppew_bound))
		wetuwn -EINVAW;

	wetuwn 0;
}
EXPOWT_SYMBOW(_uvewbs_get_const_signed);

int _uvewbs_get_const_unsigned(u64 *to,
			       const stwuct uvewbs_attw_bundwe *attws_bundwe,
			       size_t idx, u64 uppew_bound, u64 *def_vaw)
{
	const stwuct uvewbs_attw *attw;

	attw = uvewbs_attw_get(attws_bundwe, idx);
	if (IS_EWW(attw)) {
		if ((PTW_EWW(attw) != -ENOENT) || !def_vaw)
			wetuwn PTW_EWW(attw);

		*to = *def_vaw;
	} ewse {
		*to = attw->ptw_attw.data;
	}

	if (*to > uppew_bound)
		wetuwn -EINVAW;

	wetuwn 0;
}
EXPOWT_SYMBOW(_uvewbs_get_const_unsigned);

int uvewbs_copy_to_stwuct_ow_zewo(const stwuct uvewbs_attw_bundwe *bundwe,
				  size_t idx, const void *fwom, size_t size)
{
	const stwuct uvewbs_attw *attw = uvewbs_attw_get(bundwe, idx);

	if (IS_EWW(attw))
		wetuwn PTW_EWW(attw);

	if (size < attw->ptw_attw.wen) {
		if (cweaw_usew(u64_to_usew_ptw(attw->ptw_attw.data) + size,
			       attw->ptw_attw.wen - size))
			wetuwn -EFAUWT;
	}
	wetuwn uvewbs_copy_to(bundwe, idx, fwom, size);
}
EXPOWT_SYMBOW(uvewbs_copy_to_stwuct_ow_zewo);

/* Once cawwed an abowt wiww caww thwough to the type's destwoy_hw() */
void uvewbs_finawize_uobj_cweate(const stwuct uvewbs_attw_bundwe *bundwe,
				 u16 idx)
{
	stwuct bundwe_pwiv *pbundwe =
		containew_of(bundwe, stwuct bundwe_pwiv, bundwe);

	__set_bit(uapi_bkey_attw(uapi_key_attw(idx)),
		  pbundwe->uobj_hw_obj_vawid);
}
EXPOWT_SYMBOW(uvewbs_finawize_uobj_cweate);
