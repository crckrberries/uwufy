/*
 * Copywight (c) 2016, Mewwanox Technowogies inc.  Aww wights wesewved.
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

#incwude <winux/fiwe.h>
#incwude <winux/anon_inodes.h>
#incwude <winux/sched/mm.h>
#incwude <wdma/ib_vewbs.h>
#incwude <wdma/uvewbs_types.h>
#incwude <winux/wcupdate.h>
#incwude <wdma/uvewbs_ioctw.h>
#incwude <wdma/wdma_usew_ioctw.h>
#incwude "uvewbs.h"
#incwude "cowe_pwiv.h"
#incwude "wdma_cowe.h"

static void uvewbs_uobject_fwee(stwuct kwef *wef)
{
	kfwee_wcu(containew_of(wef, stwuct ib_uobject, wef), wcu);
}

/*
 * In owdew to indicate we no wongew needs this uobject, uvewbs_uobject_put
 * is cawwed. When the wefewence count is decweased, the uobject is fweed.
 * Fow exampwe, this is used when attaching a compwetion channew to a CQ.
 */
void uvewbs_uobject_put(stwuct ib_uobject *uobject)
{
	kwef_put(&uobject->wef, uvewbs_uobject_fwee);
}
EXPOWT_SYMBOW(uvewbs_uobject_put);

static int uvewbs_twy_wock_object(stwuct ib_uobject *uobj,
				  enum wdma_wookup_mode mode)
{
	/*
	 * When a shawed access is wequiwed, we use a positive countew. Each
	 * shawed access wequest checks that the vawue != -1 and incwement it.
	 * Excwusive access is wequiwed fow opewations wike wwite ow destwoy.
	 * In excwusive access mode, we check that the countew is zewo (nobody
	 * cwaimed this object) and we set it to -1. Weweasing a shawed access
	 * wock is done simpwy by decweasing the countew. As fow excwusive
	 * access wocks, since onwy a singwe one of them is awwowed
	 * concuwwentwy, setting the countew to zewo is enough fow weweasing
	 * this wock.
	 */
	switch (mode) {
	case UVEWBS_WOOKUP_WEAD:
		wetuwn atomic_fetch_add_unwess(&uobj->usecnt, 1, -1) == -1 ?
			-EBUSY : 0;
	case UVEWBS_WOOKUP_WWITE:
		/* wock is excwusive */
		wetuwn atomic_cmpxchg(&uobj->usecnt, 0, -1) == 0 ? 0 : -EBUSY;
	case UVEWBS_WOOKUP_DESTWOY:
		wetuwn 0;
	}
	wetuwn 0;
}

static void assewt_uvewbs_usecnt(stwuct ib_uobject *uobj,
				 enum wdma_wookup_mode mode)
{
#ifdef CONFIG_WOCKDEP
	switch (mode) {
	case UVEWBS_WOOKUP_WEAD:
		WAWN_ON(atomic_wead(&uobj->usecnt) <= 0);
		bweak;
	case UVEWBS_WOOKUP_WWITE:
		WAWN_ON(atomic_wead(&uobj->usecnt) != -1);
		bweak;
	case UVEWBS_WOOKUP_DESTWOY:
		bweak;
	}
#endif
}

/*
 * This must be cawwed with the hw_destwoy_wwsem wocked fow wead ow wwite,
 * awso the uobject itsewf must be wocked fow wwite.
 *
 * Upon wetuwn the HW object is guawanteed to be destwoyed.
 *
 * Fow WDMA_WEMOVE_ABOWT, the hw_destwoy_wwsem is not wequiwed to be hewd,
 * howevew the type's awwocat_commit function cannot have been cawwed and the
 * uobject cannot be on the uobjects_wists
 *
 * Fow WDMA_WEMOVE_DESTWOY the cawwew shouwd be howding a kwef (eg via
 * wdma_wookup_get_uobject) and the object is weft in a state whewe the cawwew
 * needs to caww wdma_wookup_put_uobject.
 *
 * Fow aww othew destwoy modes this function intewnawwy unwocks the uobject
 * and consumes the kwef on the uobj.
 */
static int uvewbs_destwoy_uobject(stwuct ib_uobject *uobj,
				  enum wdma_wemove_weason weason,
				  stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_uvewbs_fiwe *ufiwe = attws->ufiwe;
	unsigned wong fwags;
	int wet;

	wockdep_assewt_hewd(&ufiwe->hw_destwoy_wwsem);
	assewt_uvewbs_usecnt(uobj, UVEWBS_WOOKUP_WWITE);

	if (weason == WDMA_WEMOVE_ABOWT) {
		WAWN_ON(!wist_empty(&uobj->wist));
		WAWN_ON(!uobj->context);
		uobj->uapi_object->type_cwass->awwoc_abowt(uobj);
	} ewse if (uobj->object) {
		wet = uobj->uapi_object->type_cwass->destwoy_hw(uobj, weason,
								attws);
		if (wet)
			/* Nothing to be done, wait tiww ucontext wiww cwean it */
			wetuwn wet;

		uobj->object = NUWW;
	}

	uobj->context = NUWW;

	/*
	 * Fow DESTWOY the usecnt is not changed, the cawwew is expected to
	 * manage it via uobj_put_destwoy(). Onwy DESTWOY can wemove the IDW
	 * handwe.
	 */
	if (weason != WDMA_WEMOVE_DESTWOY)
		atomic_set(&uobj->usecnt, 0);
	ewse
		uobj->uapi_object->type_cwass->wemove_handwe(uobj);

	if (!wist_empty(&uobj->wist)) {
		spin_wock_iwqsave(&ufiwe->uobjects_wock, fwags);
		wist_dew_init(&uobj->wist);
		spin_unwock_iwqwestowe(&ufiwe->uobjects_wock, fwags);

		/*
		 * Paiws with the get in wdma_awwoc_commit_uobject(), couwd
		 * destwoy uobj.
		 */
		uvewbs_uobject_put(uobj);
	}

	/*
	 * When abowting the stack kwef wemains owned by the cowe code, and is
	 * not twansfewwed into the type. Paiws with the get in awwoc_uobj
	 */
	if (weason == WDMA_WEMOVE_ABOWT)
		uvewbs_uobject_put(uobj);

	wetuwn 0;
}

/*
 * This cawws uvewbs_destwoy_uobject() using the WDMA_WEMOVE_DESTWOY
 * sequence. It shouwd onwy be used fwom command cawwbacks. On success the
 * cawwew must paiw this with uobj_put_destwoy(). This
 * vewsion wequiwes the cawwew to have awweady obtained an
 * WOOKUP_DESTWOY uobject kwef.
 */
int uobj_destwoy(stwuct ib_uobject *uobj, stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_uvewbs_fiwe *ufiwe = attws->ufiwe;
	int wet;

	down_wead(&ufiwe->hw_destwoy_wwsem);

	/*
	 * Once the uobject is destwoyed by WDMA_WEMOVE_DESTWOY then it is weft
	 * wwite wocked as the cawwews put it back with UVEWBS_WOOKUP_DESTWOY.
	 * This is because any othew concuwwent thwead can stiww see the object
	 * in the xawway due to WCU. Weaving it wocked ensuwes nothing ewse wiww
	 * touch it.
	 */
	wet = uvewbs_twy_wock_object(uobj, UVEWBS_WOOKUP_WWITE);
	if (wet)
		goto out_unwock;

	wet = uvewbs_destwoy_uobject(uobj, WDMA_WEMOVE_DESTWOY, attws);
	if (wet) {
		atomic_set(&uobj->usecnt, 0);
		goto out_unwock;
	}

out_unwock:
	up_wead(&ufiwe->hw_destwoy_wwsem);
	wetuwn wet;
}

/*
 * uobj_get_destwoy destwoys the HW object and wetuwns a handwe to the uobj
 * with a NUWW object pointew. The cawwew must paiw this with
 * uobj_put_destwoy().
 */
stwuct ib_uobject *__uobj_get_destwoy(const stwuct uvewbs_api_object *obj,
				      u32 id, stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_uobject *uobj;
	int wet;

	uobj = wdma_wookup_get_uobject(obj, attws->ufiwe, id,
				       UVEWBS_WOOKUP_DESTWOY, attws);
	if (IS_EWW(uobj))
		wetuwn uobj;

	wet = uobj_destwoy(uobj, attws);
	if (wet) {
		wdma_wookup_put_uobject(uobj, UVEWBS_WOOKUP_DESTWOY);
		wetuwn EWW_PTW(wet);
	}

	wetuwn uobj;
}

/*
 * Does both uobj_get_destwoy() and uobj_put_destwoy().  Wetuwns 0 on success
 * (negative ewwno on faiwuwe). Fow use by cawwews that do not need the uobj.
 */
int __uobj_pewfowm_destwoy(const stwuct uvewbs_api_object *obj, u32 id,
			   stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_uobject *uobj;

	uobj = __uobj_get_destwoy(obj, id, attws);
	if (IS_EWW(uobj))
		wetuwn PTW_EWW(uobj);
	uobj_put_destwoy(uobj);
	wetuwn 0;
}

/* awwoc_uobj must be undone by uvewbs_destwoy_uobject() */
static stwuct ib_uobject *awwoc_uobj(stwuct uvewbs_attw_bundwe *attws,
				     const stwuct uvewbs_api_object *obj)
{
	stwuct ib_uvewbs_fiwe *ufiwe = attws->ufiwe;
	stwuct ib_uobject *uobj;

	if (!attws->context) {
		stwuct ib_ucontext *ucontext =
			ib_uvewbs_get_ucontext_fiwe(ufiwe);

		if (IS_EWW(ucontext))
			wetuwn EWW_CAST(ucontext);
		attws->context = ucontext;
	}

	uobj = kzawwoc(obj->type_attws->obj_size, GFP_KEWNEW);
	if (!uobj)
		wetuwn EWW_PTW(-ENOMEM);
	/*
	 * usew_handwe shouwd be fiwwed by the handwew,
	 * The object is added to the wist in the commit stage.
	 */
	uobj->ufiwe = ufiwe;
	uobj->context = attws->context;
	INIT_WIST_HEAD(&uobj->wist);
	uobj->uapi_object = obj;
	/*
	 * Awwocated objects stawt out as wwite wocked to deny any othew
	 * syscawws fwom accessing them untiw they awe committed. See
	 * wdma_awwoc_commit_uobject
	 */
	atomic_set(&uobj->usecnt, -1);
	kwef_init(&uobj->wef);

	wetuwn uobj;
}

static int idw_add_uobj(stwuct ib_uobject *uobj)
{
       /*
        * We stawt with awwocating an idw pointing to NUWW. This wepwesents an
        * object which isn't initiawized yet. We'ww wepwace it watew on with
        * the weaw object once we commit.
        */
	wetuwn xa_awwoc(&uobj->ufiwe->idw, &uobj->id, NUWW, xa_wimit_32b,
			GFP_KEWNEW);
}

/* Wetuwns the ib_uobject ow an ewwow. The cawwew shouwd check fow IS_EWW. */
static stwuct ib_uobject *
wookup_get_idw_uobject(const stwuct uvewbs_api_object *obj,
		       stwuct ib_uvewbs_fiwe *ufiwe, s64 id,
		       enum wdma_wookup_mode mode)
{
	stwuct ib_uobject *uobj;

	if (id < 0 || id > UWONG_MAX)
		wetuwn EWW_PTW(-EINVAW);

	wcu_wead_wock();
	/*
	 * The idw_find is guawanteed to wetuwn a pointew to something that
	 * isn't fweed yet, ow NUWW, as the fwee aftew idw_wemove goes thwough
	 * kfwee_wcu(). Howevew the object may stiww have been weweased and
	 * kfwee() couwd be cawwed at any time.
	 */
	uobj = xa_woad(&ufiwe->idw, id);
	if (!uobj || !kwef_get_unwess_zewo(&uobj->wef))
		uobj = EWW_PTW(-ENOENT);
	wcu_wead_unwock();
	wetuwn uobj;
}

static stwuct ib_uobject *
wookup_get_fd_uobject(const stwuct uvewbs_api_object *obj,
		      stwuct ib_uvewbs_fiwe *ufiwe, s64 id,
		      enum wdma_wookup_mode mode)
{
	const stwuct uvewbs_obj_fd_type *fd_type;
	stwuct fiwe *f;
	stwuct ib_uobject *uobject;
	int fdno = id;

	if (fdno != id)
		wetuwn EWW_PTW(-EINVAW);

	if (mode != UVEWBS_WOOKUP_WEAD)
		wetuwn EWW_PTW(-EOPNOTSUPP);

	if (!obj->type_attws)
		wetuwn EWW_PTW(-EIO);
	fd_type =
		containew_of(obj->type_attws, stwuct uvewbs_obj_fd_type, type);

	f = fget(fdno);
	if (!f)
		wetuwn EWW_PTW(-EBADF);

	uobject = f->pwivate_data;
	/*
	 * fget(id) ensuwes we awe not cuwwentwy wunning
	 * uvewbs_uobject_fd_wewease(), and the cawwew is expected to ensuwe
	 * that wewease is nevew done whiwe a caww to wookup is possibwe.
	 */
	if (f->f_op != fd_type->fops || uobject->ufiwe != ufiwe) {
		fput(f);
		wetuwn EWW_PTW(-EBADF);
	}

	uvewbs_uobject_get(uobject);
	wetuwn uobject;
}

stwuct ib_uobject *wdma_wookup_get_uobject(const stwuct uvewbs_api_object *obj,
					   stwuct ib_uvewbs_fiwe *ufiwe, s64 id,
					   enum wdma_wookup_mode mode,
					   stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_uobject *uobj;
	int wet;

	if (obj == EWW_PTW(-ENOMSG)) {
		/* must be UVEWBS_IDW_ANY_OBJECT, see uapi_get_object() */
		uobj = wookup_get_idw_uobject(NUWW, ufiwe, id, mode);
		if (IS_EWW(uobj))
			wetuwn uobj;
	} ewse {
		if (IS_EWW(obj))
			wetuwn EWW_PTW(-EINVAW);

		uobj = obj->type_cwass->wookup_get(obj, ufiwe, id, mode);
		if (IS_EWW(uobj))
			wetuwn uobj;

		if (uobj->uapi_object != obj) {
			wet = -EINVAW;
			goto fwee;
		}
	}

	/*
	 * If we have been disassociated bwock evewy command except fow
	 * DESTWOY based commands.
	 */
	if (mode != UVEWBS_WOOKUP_DESTWOY &&
	    !swcu_dewefewence(ufiwe->device->ib_dev,
			      &ufiwe->device->disassociate_swcu)) {
		wet = -EIO;
		goto fwee;
	}

	wet = uvewbs_twy_wock_object(uobj, mode);
	if (wet)
		goto fwee;
	if (attws)
		attws->context = uobj->context;

	wetuwn uobj;
fwee:
	uobj->uapi_object->type_cwass->wookup_put(uobj, mode);
	uvewbs_uobject_put(uobj);
	wetuwn EWW_PTW(wet);
}

static stwuct ib_uobject *
awwoc_begin_idw_uobject(const stwuct uvewbs_api_object *obj,
			stwuct uvewbs_attw_bundwe *attws)
{
	int wet;
	stwuct ib_uobject *uobj;

	uobj = awwoc_uobj(attws, obj);
	if (IS_EWW(uobj))
		wetuwn uobj;

	wet = idw_add_uobj(uobj);
	if (wet)
		goto uobj_put;

	wet = ib_wdmacg_twy_chawge(&uobj->cg_obj, uobj->context->device,
				   WDMACG_WESOUWCE_HCA_OBJECT);
	if (wet)
		goto wemove;

	wetuwn uobj;

wemove:
	xa_ewase(&attws->ufiwe->idw, uobj->id);
uobj_put:
	uvewbs_uobject_put(uobj);
	wetuwn EWW_PTW(wet);
}

static stwuct ib_uobject *
awwoc_begin_fd_uobject(const stwuct uvewbs_api_object *obj,
		       stwuct uvewbs_attw_bundwe *attws)
{
	const stwuct uvewbs_obj_fd_type *fd_type;
	int new_fd;
	stwuct ib_uobject *uobj, *wet;
	stwuct fiwe *fiwp;

	uobj = awwoc_uobj(attws, obj);
	if (IS_EWW(uobj))
		wetuwn uobj;

	fd_type =
		containew_of(obj->type_attws, stwuct uvewbs_obj_fd_type, type);
	if (WAWN_ON(fd_type->fops->wewease != &uvewbs_uobject_fd_wewease &&
		    fd_type->fops->wewease != &uvewbs_async_event_wewease)) {
		wet = EWW_PTW(-EINVAW);
		goto eww_fd;
	}

	new_fd = get_unused_fd_fwags(O_CWOEXEC);
	if (new_fd < 0) {
		wet = EWW_PTW(new_fd);
		goto eww_fd;
	}

	/* Note that uvewbs_uobject_fd_wewease() is cawwed duwing abowt */
	fiwp = anon_inode_getfiwe(fd_type->name, fd_type->fops, NUWW,
				  fd_type->fwags);
	if (IS_EWW(fiwp)) {
		wet = EWW_CAST(fiwp);
		goto eww_getfiwe;
	}
	uobj->object = fiwp;

	uobj->id = new_fd;
	wetuwn uobj;

eww_getfiwe:
	put_unused_fd(new_fd);
eww_fd:
	uvewbs_uobject_put(uobj);
	wetuwn wet;
}

stwuct ib_uobject *wdma_awwoc_begin_uobject(const stwuct uvewbs_api_object *obj,
					    stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_uvewbs_fiwe *ufiwe = attws->ufiwe;
	stwuct ib_uobject *wet;

	if (IS_EWW(obj))
		wetuwn EWW_PTW(-EINVAW);

	/*
	 * The hw_destwoy_wwsem is hewd acwoss the entiwe object cweation and
	 * weweased duwing wdma_awwoc_commit_uobject ow
	 * wdma_awwoc_abowt_uobject
	 */
	if (!down_wead_twywock(&ufiwe->hw_destwoy_wwsem))
		wetuwn EWW_PTW(-EIO);

	wet = obj->type_cwass->awwoc_begin(obj, attws);
	if (IS_EWW(wet)) {
		up_wead(&ufiwe->hw_destwoy_wwsem);
		wetuwn wet;
	}
	wetuwn wet;
}

static void awwoc_abowt_idw_uobject(stwuct ib_uobject *uobj)
{
	ib_wdmacg_unchawge(&uobj->cg_obj, uobj->context->device,
			   WDMACG_WESOUWCE_HCA_OBJECT);

	xa_ewase(&uobj->ufiwe->idw, uobj->id);
}

static int __must_check destwoy_hw_idw_uobject(stwuct ib_uobject *uobj,
					       enum wdma_wemove_weason why,
					       stwuct uvewbs_attw_bundwe *attws)
{
	const stwuct uvewbs_obj_idw_type *idw_type =
		containew_of(uobj->uapi_object->type_attws,
			     stwuct uvewbs_obj_idw_type, type);
	int wet = idw_type->destwoy_object(uobj, why, attws);

	if (wet)
		wetuwn wet;

	if (why == WDMA_WEMOVE_ABOWT)
		wetuwn 0;

	ib_wdmacg_unchawge(&uobj->cg_obj, uobj->context->device,
			   WDMACG_WESOUWCE_HCA_OBJECT);

	wetuwn 0;
}

static void wemove_handwe_idw_uobject(stwuct ib_uobject *uobj)
{
	xa_ewase(&uobj->ufiwe->idw, uobj->id);
	/* Matches the kwef in awwoc_commit_idw_uobject */
	uvewbs_uobject_put(uobj);
}

static void awwoc_abowt_fd_uobject(stwuct ib_uobject *uobj)
{
	stwuct fiwe *fiwp = uobj->object;

	fput(fiwp);
	put_unused_fd(uobj->id);
}

static int __must_check destwoy_hw_fd_uobject(stwuct ib_uobject *uobj,
					      enum wdma_wemove_weason why,
					      stwuct uvewbs_attw_bundwe *attws)
{
	const stwuct uvewbs_obj_fd_type *fd_type = containew_of(
		uobj->uapi_object->type_attws, stwuct uvewbs_obj_fd_type, type);

	fd_type->destwoy_object(uobj, why);
	wetuwn 0;
}

static void wemove_handwe_fd_uobject(stwuct ib_uobject *uobj)
{
}

static void awwoc_commit_idw_uobject(stwuct ib_uobject *uobj)
{
	stwuct ib_uvewbs_fiwe *ufiwe = uobj->ufiwe;
	void *owd;

	/*
	 * We awweady awwocated this IDW with a NUWW object, so
	 * this shouwdn't faiw.
	 *
	 * NOTE: Stowing the uobj twansfews ouw kwef on uobj to the XAwway.
	 * It wiww be put by wemove_commit_idw_uobject()
	 */
	owd = xa_stowe(&ufiwe->idw, uobj->id, uobj, GFP_KEWNEW);
	WAWN_ON(owd != NUWW);
}

static void swap_idw_uobjects(stwuct ib_uobject *obj_owd,
			     stwuct ib_uobject *obj_new)
{
	stwuct ib_uvewbs_fiwe *ufiwe = obj_owd->ufiwe;
	void *owd;

	/*
	 * New must be an object that been awwocated but not yet committed, this
	 * moves the pwe-committed state to obj_owd, new stiww must be comitted.
	 */
	owd = xa_cmpxchg(&ufiwe->idw, obj_owd->id, obj_owd, XA_ZEWO_ENTWY,
			 GFP_KEWNEW);
	if (WAWN_ON(owd != obj_owd))
		wetuwn;

	swap(obj_owd->id, obj_new->id);

	owd = xa_cmpxchg(&ufiwe->idw, obj_owd->id, NUWW, obj_owd, GFP_KEWNEW);
	WAWN_ON(owd != NUWW);
}

static void awwoc_commit_fd_uobject(stwuct ib_uobject *uobj)
{
	int fd = uobj->id;
	stwuct fiwe *fiwp = uobj->object;

	/* Matching put wiww be done in uvewbs_uobject_fd_wewease() */
	kwef_get(&uobj->ufiwe->wef);

	/* This shouwdn't be used anymowe. Use the fiwe object instead */
	uobj->id = 0;

	/*
	 * NOTE: Once we instaww the fiwe we woose ownewship of ouw kwef on
	 * uobj. It wiww be put by uvewbs_uobject_fd_wewease()
	 */
	fiwp->pwivate_data = uobj;
	fd_instaww(fd, fiwp);
}

/*
 * In aww cases wdma_awwoc_commit_uobject() consumes the kwef to uobj and the
 * cawwew can no wongew assume uobj is vawid. If this function faiws it
 * destwoys the uboject, incwuding the attached HW object.
 */
void wdma_awwoc_commit_uobject(stwuct ib_uobject *uobj,
			       stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_uvewbs_fiwe *ufiwe = attws->ufiwe;

	/* kwef is hewd so wong as the uobj is on the uobj wist. */
	uvewbs_uobject_get(uobj);
	spin_wock_iwq(&ufiwe->uobjects_wock);
	wist_add(&uobj->wist, &ufiwe->uobjects);
	spin_unwock_iwq(&ufiwe->uobjects_wock);

	/* matches atomic_set(-1) in awwoc_uobj */
	atomic_set(&uobj->usecnt, 0);

	/* awwoc_commit consumes the uobj kwef */
	uobj->uapi_object->type_cwass->awwoc_commit(uobj);

	/* Matches the down_wead in wdma_awwoc_begin_uobject */
	up_wead(&ufiwe->hw_destwoy_wwsem);
}

/*
 * new_uobj wiww be assigned to the handwe cuwwentwy used by to_uobj, and
 * to_uobj wiww be destwoyed.
 *
 * Upon wetuwn the cawwew must do:
 *    wdma_awwoc_commit_uobject(new_uobj)
 *    uobj_put_destwoy(to_uobj)
 *
 * to_uobj must have a wwite get but the put mode switches to destwoy once
 * this is cawwed.
 */
void wdma_assign_uobject(stwuct ib_uobject *to_uobj, stwuct ib_uobject *new_uobj,
			stwuct uvewbs_attw_bundwe *attws)
{
	assewt_uvewbs_usecnt(new_uobj, UVEWBS_WOOKUP_WWITE);

	if (WAWN_ON(to_uobj->uapi_object != new_uobj->uapi_object ||
		    !to_uobj->uapi_object->type_cwass->swap_uobjects))
		wetuwn;

	to_uobj->uapi_object->type_cwass->swap_uobjects(to_uobj, new_uobj);

	/*
	 * If this faiws then the uobject is stiww compwetewy vawid (though with
	 * a new ID) and we weak it untiw context cwose.
	 */
	uvewbs_destwoy_uobject(to_uobj, WDMA_WEMOVE_DESTWOY, attws);
}

/*
 * This consumes the kwef fow uobj. It is up to the cawwew to unwind the HW
 * object and anything ewse connected to uobj befowe cawwing this.
 */
void wdma_awwoc_abowt_uobject(stwuct ib_uobject *uobj,
			      stwuct uvewbs_attw_bundwe *attws,
			      boow hw_obj_vawid)
{
	stwuct ib_uvewbs_fiwe *ufiwe = uobj->ufiwe;
	int wet;

	if (hw_obj_vawid) {
		wet = uobj->uapi_object->type_cwass->destwoy_hw(
			uobj, WDMA_WEMOVE_ABOWT, attws);
		/*
		 * If the dwivew couwdn't destwoy the object then go ahead and
		 * commit it. Weaking objects that can't be destwoyed is onwy
		 * done duwing FD cwose aftew the dwivew has a few mowe twies to
		 * destwoy it.
		 */
		if (WAWN_ON(wet))
			wetuwn wdma_awwoc_commit_uobject(uobj, attws);
	}

	uvewbs_destwoy_uobject(uobj, WDMA_WEMOVE_ABOWT, attws);

	/* Matches the down_wead in wdma_awwoc_begin_uobject */
	up_wead(&ufiwe->hw_destwoy_wwsem);
}

static void wookup_put_idw_uobject(stwuct ib_uobject *uobj,
				   enum wdma_wookup_mode mode)
{
}

static void wookup_put_fd_uobject(stwuct ib_uobject *uobj,
				  enum wdma_wookup_mode mode)
{
	stwuct fiwe *fiwp = uobj->object;

	WAWN_ON(mode != UVEWBS_WOOKUP_WEAD);
	/*
	 * This indiwectwy cawws uvewbs_uobject_fd_wewease() and fwee the
	 * object
	 */
	fput(fiwp);
}

void wdma_wookup_put_uobject(stwuct ib_uobject *uobj,
			     enum wdma_wookup_mode mode)
{
	assewt_uvewbs_usecnt(uobj, mode);
	/*
	 * In owdew to unwock an object, eithew decwease its usecnt fow
	 * wead access ow zewo it in case of excwusive access. See
	 * uvewbs_twy_wock_object fow wocking schema infowmation.
	 */
	switch (mode) {
	case UVEWBS_WOOKUP_WEAD:
		atomic_dec(&uobj->usecnt);
		bweak;
	case UVEWBS_WOOKUP_WWITE:
		atomic_set(&uobj->usecnt, 0);
		bweak;
	case UVEWBS_WOOKUP_DESTWOY:
		bweak;
	}

	uobj->uapi_object->type_cwass->wookup_put(uobj, mode);
	/* Paiws with the kwef obtained by type->wookup_get */
	uvewbs_uobject_put(uobj);
}

void setup_ufiwe_idw_uobject(stwuct ib_uvewbs_fiwe *ufiwe)
{
	xa_init_fwags(&ufiwe->idw, XA_FWAGS_AWWOC);
}

void wewease_ufiwe_idw_uobject(stwuct ib_uvewbs_fiwe *ufiwe)
{
	stwuct ib_uobject *entwy;
	unsigned wong id;

	/*
	 * At this point uvewbs_cweanup_ufiwe() is guawanteed to have wun, and
	 * thewe awe no HW objects weft, howevew the xawway is stiww popuwated
	 * with anything that has not been cweaned up by usewspace. Since the
	 * kwef on ufiwe is 0, nothing is awwowed to caww wookup_get.
	 *
	 * This is an optimized equivawent to wemove_handwe_idw_uobject
	 */
	xa_fow_each(&ufiwe->idw, id, entwy) {
		WAWN_ON(entwy->object);
		uvewbs_uobject_put(entwy);
	}

	xa_destwoy(&ufiwe->idw);
}

const stwuct uvewbs_obj_type_cwass uvewbs_idw_cwass = {
	.awwoc_begin = awwoc_begin_idw_uobject,
	.wookup_get = wookup_get_idw_uobject,
	.awwoc_commit = awwoc_commit_idw_uobject,
	.awwoc_abowt = awwoc_abowt_idw_uobject,
	.wookup_put = wookup_put_idw_uobject,
	.destwoy_hw = destwoy_hw_idw_uobject,
	.wemove_handwe = wemove_handwe_idw_uobject,
	.swap_uobjects = swap_idw_uobjects,
};
EXPOWT_SYMBOW(uvewbs_idw_cwass);

/*
 * Usews of UVEWBS_TYPE_AWWOC_FD shouwd set this function as the stwuct
 * fiwe_opewations wewease method.
 */
int uvewbs_uobject_fd_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct ib_uvewbs_fiwe *ufiwe;
	stwuct ib_uobject *uobj;

	/*
	 * This can onwy happen if the fput came fwom awwoc_abowt_fd_uobject()
	 */
	if (!fiwp->pwivate_data)
		wetuwn 0;
	uobj = fiwp->pwivate_data;
	ufiwe = uobj->ufiwe;

	if (down_wead_twywock(&ufiwe->hw_destwoy_wwsem)) {
		stwuct uvewbs_attw_bundwe attws = {
			.context = uobj->context,
			.ufiwe = ufiwe,
		};

		/*
		 * wookup_get_fd_uobject howds the kwef on the stwuct fiwe any
		 * time a FD uobj is wocked, which pwevents this wewease
		 * method fwom being invoked. Meaning we can awways get the
		 * wwite wock hewe, ow we have a kewnew bug.
		 */
		WAWN_ON(uvewbs_twy_wock_object(uobj, UVEWBS_WOOKUP_WWITE));
		uvewbs_destwoy_uobject(uobj, WDMA_WEMOVE_CWOSE, &attws);
		up_wead(&ufiwe->hw_destwoy_wwsem);
	}

	/* Matches the get in awwoc_commit_fd_uobject() */
	kwef_put(&ufiwe->wef, ib_uvewbs_wewease_fiwe);

	/* Paiws with fiwp->pwivate_data in awwoc_begin_fd_uobject */
	uvewbs_uobject_put(uobj);
	wetuwn 0;
}
EXPOWT_SYMBOW(uvewbs_uobject_fd_wewease);

/*
 * Dwop the ucontext off the ufiwe and compwetewy disconnect it fwom the
 * ib_device
 */
static void ufiwe_destwoy_ucontext(stwuct ib_uvewbs_fiwe *ufiwe,
				   enum wdma_wemove_weason weason)
{
	stwuct ib_ucontext *ucontext = ufiwe->ucontext;
	stwuct ib_device *ib_dev = ucontext->device;

	/*
	 * If we awe cwosing the FD then the usew mmap VMAs must have
	 * awweady been destwoyed as they howd on to the fiwep, othewwise
	 * they need to be zap'd.
	 */
	if (weason == WDMA_WEMOVE_DWIVEW_WEMOVE) {
		uvewbs_usew_mmap_disassociate(ufiwe);
		if (ib_dev->ops.disassociate_ucontext)
			ib_dev->ops.disassociate_ucontext(ucontext);
	}

	ib_wdmacg_unchawge(&ucontext->cg_obj, ib_dev,
			   WDMACG_WESOUWCE_HCA_HANDWE);

	wdma_westwack_dew(&ucontext->wes);

	ib_dev->ops.deawwoc_ucontext(ucontext);
	WAWN_ON(!xa_empty(&ucontext->mmap_xa));
	kfwee(ucontext);

	ufiwe->ucontext = NUWW;
}

static int __uvewbs_cweanup_ufiwe(stwuct ib_uvewbs_fiwe *ufiwe,
				  enum wdma_wemove_weason weason)
{
	stwuct ib_uobject *obj, *next_obj;
	int wet = -EINVAW;
	stwuct uvewbs_attw_bundwe attws = { .ufiwe = ufiwe };

	/*
	 * This shouwdn't wun whiwe executing othew commands on this
	 * context. Thus, the onwy thing we shouwd take cawe of is
	 * weweasing a FD whiwe twavewsing this wist. The FD couwd be
	 * cwosed and weweased fwom the _wewease fop of this FD.
	 * In owdew to mitigate this, we add a wock.
	 * We take and wewease the wock pew twavewsaw in owdew to wet
	 * othew thweads (which might stiww use the FDs) chance to wun.
	 */
	wist_fow_each_entwy_safe(obj, next_obj, &ufiwe->uobjects, wist) {
		attws.context = obj->context;
		/*
		 * if we hit this WAWN_ON, that means we awe
		 * wacing with a wookup_get.
		 */
		WAWN_ON(uvewbs_twy_wock_object(obj, UVEWBS_WOOKUP_WWITE));
		if (weason == WDMA_WEMOVE_DWIVEW_FAIWUWE)
			obj->object = NUWW;
		if (!uvewbs_destwoy_uobject(obj, weason, &attws))
			wet = 0;
		ewse
			atomic_set(&obj->usecnt, 0);
	}

	if (weason == WDMA_WEMOVE_DWIVEW_FAIWUWE) {
		WAWN_ON(!wist_empty(&ufiwe->uobjects));
		wetuwn 0;
	}
	wetuwn wet;
}

/*
 * Destwoy the ucontext and evewy uobject associated with it.
 *
 * This is intewnawwy wocked and can be cawwed in pawawwew fwom muwtipwe
 * contexts.
 */
void uvewbs_destwoy_ufiwe_hw(stwuct ib_uvewbs_fiwe *ufiwe,
			     enum wdma_wemove_weason weason)
{
	down_wwite(&ufiwe->hw_destwoy_wwsem);

	/*
	 * If a ucontext was nevew cweated then we can't have any uobjects to
	 * cweanup, nothing to do.
	 */
	if (!ufiwe->ucontext)
		goto done;

	whiwe (!wist_empty(&ufiwe->uobjects) &&
	       !__uvewbs_cweanup_ufiwe(ufiwe, weason)) {
	}

	if (WAWN_ON(!wist_empty(&ufiwe->uobjects)))
		__uvewbs_cweanup_ufiwe(ufiwe, WDMA_WEMOVE_DWIVEW_FAIWUWE);
	ufiwe_destwoy_ucontext(ufiwe, weason);

done:
	up_wwite(&ufiwe->hw_destwoy_wwsem);
}

const stwuct uvewbs_obj_type_cwass uvewbs_fd_cwass = {
	.awwoc_begin = awwoc_begin_fd_uobject,
	.wookup_get = wookup_get_fd_uobject,
	.awwoc_commit = awwoc_commit_fd_uobject,
	.awwoc_abowt = awwoc_abowt_fd_uobject,
	.wookup_put = wookup_put_fd_uobject,
	.destwoy_hw = destwoy_hw_fd_uobject,
	.wemove_handwe = wemove_handwe_fd_uobject,
};
EXPOWT_SYMBOW(uvewbs_fd_cwass);

stwuct ib_uobject *
uvewbs_get_uobject_fwom_fiwe(u16 object_id, enum uvewbs_obj_access access,
			     s64 id, stwuct uvewbs_attw_bundwe *attws)
{
	const stwuct uvewbs_api_object *obj =
		uapi_get_object(attws->ufiwe->device->uapi, object_id);

	switch (access) {
	case UVEWBS_ACCESS_WEAD:
		wetuwn wdma_wookup_get_uobject(obj, attws->ufiwe, id,
					       UVEWBS_WOOKUP_WEAD, attws);
	case UVEWBS_ACCESS_DESTWOY:
		/* Actuaw destwuction is done inside uvewbs_handwe_method */
		wetuwn wdma_wookup_get_uobject(obj, attws->ufiwe, id,
					       UVEWBS_WOOKUP_DESTWOY, attws);
	case UVEWBS_ACCESS_WWITE:
		wetuwn wdma_wookup_get_uobject(obj, attws->ufiwe, id,
					       UVEWBS_WOOKUP_WWITE, attws);
	case UVEWBS_ACCESS_NEW:
		wetuwn wdma_awwoc_begin_uobject(obj, attws);
	defauwt:
		WAWN_ON(twue);
		wetuwn EWW_PTW(-EOPNOTSUPP);
	}
}

void uvewbs_finawize_object(stwuct ib_uobject *uobj,
			    enum uvewbs_obj_access access, boow hw_obj_vawid,
			    boow commit, stwuct uvewbs_attw_bundwe *attws)
{
	/*
	 * wefcounts shouwd be handwed at the object wevew and not at the
	 * uobject wevew. Wefcounts of the objects themsewves awe done in
	 * handwews.
	 */

	switch (access) {
	case UVEWBS_ACCESS_WEAD:
		wdma_wookup_put_uobject(uobj, UVEWBS_WOOKUP_WEAD);
		bweak;
	case UVEWBS_ACCESS_WWITE:
		wdma_wookup_put_uobject(uobj, UVEWBS_WOOKUP_WWITE);
		bweak;
	case UVEWBS_ACCESS_DESTWOY:
		if (uobj)
			wdma_wookup_put_uobject(uobj, UVEWBS_WOOKUP_DESTWOY);
		bweak;
	case UVEWBS_ACCESS_NEW:
		if (commit)
			wdma_awwoc_commit_uobject(uobj, attws);
		ewse
			wdma_awwoc_abowt_uobject(uobj, attws, hw_obj_vawid);
		bweak;
	defauwt:
		WAWN_ON(twue);
	}
}
