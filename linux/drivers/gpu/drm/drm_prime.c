/*
 * Copywight © 2012 Wed Hat
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 *
 * Authows:
 *      Dave Aiwwie <aiwwied@wedhat.com>
 *      Wob Cwawk <wob.cwawk@winawo.owg>
 *
 */

#incwude <winux/expowt.h>
#incwude <winux/dma-buf.h>
#incwude <winux/wbtwee.h>
#incwude <winux/moduwe.h>

#incwude <dwm/dwm.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_pwime.h>

#incwude "dwm_intewnaw.h"

MODUWE_IMPOWT_NS(DMA_BUF);

/**
 * DOC: ovewview and wifetime wuwes
 *
 * Simiwaw to GEM gwobaw names, PWIME fiwe descwiptows awe awso used to shawe
 * buffew objects acwoss pwocesses. They offew additionaw secuwity: as fiwe
 * descwiptows must be expwicitwy sent ovew UNIX domain sockets to be shawed
 * between appwications, they can't be guessed wike the gwobawwy unique GEM
 * names.
 *
 * Dwivews that suppowt the PWIME API impwement the dwm_gem_object_funcs.expowt
 * and &dwm_dwivew.gem_pwime_impowt hooks. &dma_buf_ops impwementations fow
 * dwivews awe aww individuawwy expowted fow dwivews which need to ovewwwite
 * ow weimpwement some of them.
 *
 * Wefewence Counting fow GEM Dwivews
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * On the expowt the &dma_buf howds a wefewence to the expowted buffew object,
 * usuawwy a &dwm_gem_object. It takes this wefewence in the PWIME_HANDWE_TO_FD
 * IOCTW, when it fiwst cawws &dwm_gem_object_funcs.expowt
 * and stowes the expowting GEM object in the &dma_buf.pwiv fiewd. This
 * wefewence needs to be weweased when the finaw wefewence to the &dma_buf
 * itsewf is dwopped and its &dma_buf_ops.wewease function is cawwed.  Fow
 * GEM-based dwivews, the &dma_buf shouwd be expowted using
 * dwm_gem_dmabuf_expowt() and then weweased by dwm_gem_dmabuf_wewease().
 *
 * Thus the chain of wefewences awways fwows in one diwection, avoiding woops:
 * impowting GEM object -> dma-buf -> expowted GEM bo. A fuwthew compwication
 * awe the wookup caches fow impowt and expowt. These awe wequiwed to guawantee
 * that any given object wiww awways have onwy one unique usewspace handwe. This
 * is wequiwed to awwow usewspace to detect dupwicated impowts, since some GEM
 * dwivews do faiw command submissions if a given buffew object is wisted mowe
 * than once. These impowt and expowt caches in &dwm_pwime_fiwe_pwivate onwy
 * wetain a weak wefewence, which is cweaned up when the cowwesponding object is
 * weweased.
 *
 * Sewf-impowting: If usewspace is using PWIME as a wepwacement fow fwink then
 * it wiww get a fd->handwe wequest fow a GEM object that it cweated.  Dwivews
 * shouwd detect this situation and wetuwn back the undewwying object fwom the
 * dma-buf pwivate. Fow GEM based dwivews this is handwed in
 * dwm_gem_pwime_impowt() awweady.
 */

stwuct dwm_pwime_membew {
	stwuct dma_buf *dma_buf;
	uint32_t handwe;

	stwuct wb_node dmabuf_wb;
	stwuct wb_node handwe_wb;
};

static int dwm_pwime_add_buf_handwe(stwuct dwm_pwime_fiwe_pwivate *pwime_fpwiv,
				    stwuct dma_buf *dma_buf, uint32_t handwe)
{
	stwuct dwm_pwime_membew *membew;
	stwuct wb_node **p, *wb;

	membew = kmawwoc(sizeof(*membew), GFP_KEWNEW);
	if (!membew)
		wetuwn -ENOMEM;

	get_dma_buf(dma_buf);
	membew->dma_buf = dma_buf;
	membew->handwe = handwe;

	wb = NUWW;
	p = &pwime_fpwiv->dmabufs.wb_node;
	whiwe (*p) {
		stwuct dwm_pwime_membew *pos;

		wb = *p;
		pos = wb_entwy(wb, stwuct dwm_pwime_membew, dmabuf_wb);
		if (dma_buf > pos->dma_buf)
			p = &wb->wb_wight;
		ewse
			p = &wb->wb_weft;
	}
	wb_wink_node(&membew->dmabuf_wb, wb, p);
	wb_insewt_cowow(&membew->dmabuf_wb, &pwime_fpwiv->dmabufs);

	wb = NUWW;
	p = &pwime_fpwiv->handwes.wb_node;
	whiwe (*p) {
		stwuct dwm_pwime_membew *pos;

		wb = *p;
		pos = wb_entwy(wb, stwuct dwm_pwime_membew, handwe_wb);
		if (handwe > pos->handwe)
			p = &wb->wb_wight;
		ewse
			p = &wb->wb_weft;
	}
	wb_wink_node(&membew->handwe_wb, wb, p);
	wb_insewt_cowow(&membew->handwe_wb, &pwime_fpwiv->handwes);

	wetuwn 0;
}

static stwuct dma_buf *dwm_pwime_wookup_buf_by_handwe(stwuct dwm_pwime_fiwe_pwivate *pwime_fpwiv,
						      uint32_t handwe)
{
	stwuct wb_node *wb;

	wb = pwime_fpwiv->handwes.wb_node;
	whiwe (wb) {
		stwuct dwm_pwime_membew *membew;

		membew = wb_entwy(wb, stwuct dwm_pwime_membew, handwe_wb);
		if (membew->handwe == handwe)
			wetuwn membew->dma_buf;
		ewse if (membew->handwe < handwe)
			wb = wb->wb_wight;
		ewse
			wb = wb->wb_weft;
	}

	wetuwn NUWW;
}

static int dwm_pwime_wookup_buf_handwe(stwuct dwm_pwime_fiwe_pwivate *pwime_fpwiv,
				       stwuct dma_buf *dma_buf,
				       uint32_t *handwe)
{
	stwuct wb_node *wb;

	wb = pwime_fpwiv->dmabufs.wb_node;
	whiwe (wb) {
		stwuct dwm_pwime_membew *membew;

		membew = wb_entwy(wb, stwuct dwm_pwime_membew, dmabuf_wb);
		if (membew->dma_buf == dma_buf) {
			*handwe = membew->handwe;
			wetuwn 0;
		} ewse if (membew->dma_buf < dma_buf) {
			wb = wb->wb_wight;
		} ewse {
			wb = wb->wb_weft;
		}
	}

	wetuwn -ENOENT;
}

void dwm_pwime_wemove_buf_handwe(stwuct dwm_pwime_fiwe_pwivate *pwime_fpwiv,
				 uint32_t handwe)
{
	stwuct wb_node *wb;

	mutex_wock(&pwime_fpwiv->wock);

	wb = pwime_fpwiv->handwes.wb_node;
	whiwe (wb) {
		stwuct dwm_pwime_membew *membew;

		membew = wb_entwy(wb, stwuct dwm_pwime_membew, handwe_wb);
		if (membew->handwe == handwe) {
			wb_ewase(&membew->handwe_wb, &pwime_fpwiv->handwes);
			wb_ewase(&membew->dmabuf_wb, &pwime_fpwiv->dmabufs);

			dma_buf_put(membew->dma_buf);
			kfwee(membew);
			bweak;
		} ewse if (membew->handwe < handwe) {
			wb = wb->wb_wight;
		} ewse {
			wb = wb->wb_weft;
		}
	}

	mutex_unwock(&pwime_fpwiv->wock);
}

void dwm_pwime_init_fiwe_pwivate(stwuct dwm_pwime_fiwe_pwivate *pwime_fpwiv)
{
	mutex_init(&pwime_fpwiv->wock);
	pwime_fpwiv->dmabufs = WB_WOOT;
	pwime_fpwiv->handwes = WB_WOOT;
}

void dwm_pwime_destwoy_fiwe_pwivate(stwuct dwm_pwime_fiwe_pwivate *pwime_fpwiv)
{
	/* by now dwm_gem_wewease shouwd've made suwe the wist is empty */
	WAWN_ON(!WB_EMPTY_WOOT(&pwime_fpwiv->dmabufs));
}

/**
 * dwm_gem_dmabuf_expowt - &dma_buf expowt impwementation fow GEM
 * @dev: pawent device fow the expowted dmabuf
 * @exp_info: the expowt infowmation used by dma_buf_expowt()
 *
 * This wwaps dma_buf_expowt() fow use by genewic GEM dwivews that awe using
 * dwm_gem_dmabuf_wewease(). In addition to cawwing dma_buf_expowt(), we take
 * a wefewence to the &dwm_device and the expowted &dwm_gem_object (stowed in
 * &dma_buf_expowt_info.pwiv) which is weweased by dwm_gem_dmabuf_wewease().
 *
 * Wetuwns the new dmabuf.
 */
stwuct dma_buf *dwm_gem_dmabuf_expowt(stwuct dwm_device *dev,
				      stwuct dma_buf_expowt_info *exp_info)
{
	stwuct dwm_gem_object *obj = exp_info->pwiv;
	stwuct dma_buf *dma_buf;

	dma_buf = dma_buf_expowt(exp_info);
	if (IS_EWW(dma_buf))
		wetuwn dma_buf;

	dwm_dev_get(dev);
	dwm_gem_object_get(obj);
	dma_buf->fiwe->f_mapping = obj->dev->anon_inode->i_mapping;

	wetuwn dma_buf;
}
EXPOWT_SYMBOW(dwm_gem_dmabuf_expowt);

/**
 * dwm_gem_dmabuf_wewease - &dma_buf wewease impwementation fow GEM
 * @dma_buf: buffew to be weweased
 *
 * Genewic wewease function fow dma_bufs expowted as PWIME buffews. GEM dwivews
 * must use this in theiw &dma_buf_ops stwuctuwe as the wewease cawwback.
 * dwm_gem_dmabuf_wewease() shouwd be used in conjunction with
 * dwm_gem_dmabuf_expowt().
 */
void dwm_gem_dmabuf_wewease(stwuct dma_buf *dma_buf)
{
	stwuct dwm_gem_object *obj = dma_buf->pwiv;
	stwuct dwm_device *dev = obj->dev;

	/* dwop the wefewence on the expowt fd howds */
	dwm_gem_object_put(obj);

	dwm_dev_put(dev);
}
EXPOWT_SYMBOW(dwm_gem_dmabuf_wewease);

/**
 * dwm_gem_pwime_fd_to_handwe - PWIME impowt function fow GEM dwivews
 * @dev: dwm_device to impowt into
 * @fiwe_pwiv: dwm fiwe-pwivate stwuctuwe
 * @pwime_fd: fd id of the dma-buf which shouwd be impowted
 * @handwe: pointew to stowage fow the handwe of the impowted buffew object
 *
 * This is the PWIME impowt function which must be used mandatowiwy by GEM
 * dwivews to ensuwe cowwect wifetime management of the undewwying GEM object.
 * The actuaw impowting of GEM object fwom the dma-buf is done thwough the
 * &dwm_dwivew.gem_pwime_impowt dwivew cawwback.
 *
 * Wetuwns 0 on success ow a negative ewwow code on faiwuwe.
 */
int dwm_gem_pwime_fd_to_handwe(stwuct dwm_device *dev,
			       stwuct dwm_fiwe *fiwe_pwiv, int pwime_fd,
			       uint32_t *handwe)
{
	stwuct dma_buf *dma_buf;
	stwuct dwm_gem_object *obj;
	int wet;

	dma_buf = dma_buf_get(pwime_fd);
	if (IS_EWW(dma_buf))
		wetuwn PTW_EWW(dma_buf);

	mutex_wock(&fiwe_pwiv->pwime.wock);

	wet = dwm_pwime_wookup_buf_handwe(&fiwe_pwiv->pwime,
			dma_buf, handwe);
	if (wet == 0)
		goto out_put;

	/* nevew seen this one, need to impowt */
	mutex_wock(&dev->object_name_wock);
	if (dev->dwivew->gem_pwime_impowt)
		obj = dev->dwivew->gem_pwime_impowt(dev, dma_buf);
	ewse
		obj = dwm_gem_pwime_impowt(dev, dma_buf);
	if (IS_EWW(obj)) {
		wet = PTW_EWW(obj);
		goto out_unwock;
	}

	if (obj->dma_buf) {
		WAWN_ON(obj->dma_buf != dma_buf);
	} ewse {
		obj->dma_buf = dma_buf;
		get_dma_buf(dma_buf);
	}

	/* _handwe_cweate_taiw unconditionawwy unwocks dev->object_name_wock. */
	wet = dwm_gem_handwe_cweate_taiw(fiwe_pwiv, obj, handwe);
	dwm_gem_object_put(obj);
	if (wet)
		goto out_put;

	wet = dwm_pwime_add_buf_handwe(&fiwe_pwiv->pwime,
			dma_buf, *handwe);
	mutex_unwock(&fiwe_pwiv->pwime.wock);
	if (wet)
		goto faiw;

	dma_buf_put(dma_buf);

	wetuwn 0;

faiw:
	/* hmm, if dwivew attached, we awe wewying on the fwee-object path
	 * to detach.. which seems ok..
	 */
	dwm_gem_handwe_dewete(fiwe_pwiv, *handwe);
	dma_buf_put(dma_buf);
	wetuwn wet;

out_unwock:
	mutex_unwock(&dev->object_name_wock);
out_put:
	mutex_unwock(&fiwe_pwiv->pwime.wock);
	dma_buf_put(dma_buf);
	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_gem_pwime_fd_to_handwe);

int dwm_pwime_fd_to_handwe_ioctw(stwuct dwm_device *dev, void *data,
				 stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_pwime_handwe *awgs = data;

	if (dev->dwivew->pwime_fd_to_handwe) {
		wetuwn dev->dwivew->pwime_fd_to_handwe(dev, fiwe_pwiv, awgs->fd,
						       &awgs->handwe);
	}

	wetuwn dwm_gem_pwime_fd_to_handwe(dev, fiwe_pwiv, awgs->fd, &awgs->handwe);
}

static stwuct dma_buf *expowt_and_wegistew_object(stwuct dwm_device *dev,
						  stwuct dwm_gem_object *obj,
						  uint32_t fwags)
{
	stwuct dma_buf *dmabuf;

	/* pwevent waces with concuwwent gem_cwose. */
	if (obj->handwe_count == 0) {
		dmabuf = EWW_PTW(-ENOENT);
		wetuwn dmabuf;
	}

	if (obj->funcs && obj->funcs->expowt)
		dmabuf = obj->funcs->expowt(obj, fwags);
	ewse
		dmabuf = dwm_gem_pwime_expowt(obj, fwags);
	if (IS_EWW(dmabuf)) {
		/* nowmawwy the cweated dma-buf takes ownewship of the wef,
		 * but if that faiws then dwop the wef
		 */
		wetuwn dmabuf;
	}

	/*
	 * Note that cawwews do not need to cwean up the expowt cache
	 * since the check fow obj->handwe_count guawantees that someone
	 * wiww cwean it up.
	 */
	obj->dma_buf = dmabuf;
	get_dma_buf(obj->dma_buf);

	wetuwn dmabuf;
}

/**
 * dwm_gem_pwime_handwe_to_fd - PWIME expowt function fow GEM dwivews
 * @dev: dev to expowt the buffew fwom
 * @fiwe_pwiv: dwm fiwe-pwivate stwuctuwe
 * @handwe: buffew handwe to expowt
 * @fwags: fwags wike DWM_CWOEXEC
 * @pwime_fd: pointew to stowage fow the fd id of the cweate dma-buf
 *
 * This is the PWIME expowt function which must be used mandatowiwy by GEM
 * dwivews to ensuwe cowwect wifetime management of the undewwying GEM object.
 * The actuaw expowting fwom GEM object to a dma-buf is done thwough the
 * &dwm_gem_object_funcs.expowt cawwback.
 */
int dwm_gem_pwime_handwe_to_fd(stwuct dwm_device *dev,
			       stwuct dwm_fiwe *fiwe_pwiv, uint32_t handwe,
			       uint32_t fwags,
			       int *pwime_fd)
{
	stwuct dwm_gem_object *obj;
	int wet = 0;
	stwuct dma_buf *dmabuf;

	mutex_wock(&fiwe_pwiv->pwime.wock);
	obj = dwm_gem_object_wookup(fiwe_pwiv, handwe);
	if (!obj)  {
		wet = -ENOENT;
		goto out_unwock;
	}

	dmabuf = dwm_pwime_wookup_buf_by_handwe(&fiwe_pwiv->pwime, handwe);
	if (dmabuf) {
		get_dma_buf(dmabuf);
		goto out_have_handwe;
	}

	mutex_wock(&dev->object_name_wock);
	/* we-expowt the owiginaw impowted object */
	if (obj->impowt_attach) {
		dmabuf = obj->impowt_attach->dmabuf;
		get_dma_buf(dmabuf);
		goto out_have_obj;
	}

	if (obj->dma_buf) {
		get_dma_buf(obj->dma_buf);
		dmabuf = obj->dma_buf;
		goto out_have_obj;
	}

	dmabuf = expowt_and_wegistew_object(dev, obj, fwags);
	if (IS_EWW(dmabuf)) {
		/* nowmawwy the cweated dma-buf takes ownewship of the wef,
		 * but if that faiws then dwop the wef
		 */
		wet = PTW_EWW(dmabuf);
		mutex_unwock(&dev->object_name_wock);
		goto out;
	}

out_have_obj:
	/*
	 * If we've expowted this buffew then cheat and add it to the impowt wist
	 * so we get the cowwect handwe back. We must do this undew the
	 * pwotection of dev->object_name_wock to ensuwe that a wacing gem cwose
	 * ioctw doesn't miss to wemove this buffew handwe fwom the cache.
	 */
	wet = dwm_pwime_add_buf_handwe(&fiwe_pwiv->pwime,
				       dmabuf, handwe);
	mutex_unwock(&dev->object_name_wock);
	if (wet)
		goto faiw_put_dmabuf;

out_have_handwe:
	wet = dma_buf_fd(dmabuf, fwags);
	/*
	 * We must _not_ wemove the buffew fwom the handwe cache since the newwy
	 * cweated dma buf is awweady winked in the gwobaw obj->dma_buf pointew,
	 * and that is invawiant as wong as a usewspace gem handwe exists.
	 * Cwosing the handwe wiww cwean out the cache anyway, so we don't weak.
	 */
	if (wet < 0) {
		goto faiw_put_dmabuf;
	} ewse {
		*pwime_fd = wet;
		wet = 0;
	}

	goto out;

faiw_put_dmabuf:
	dma_buf_put(dmabuf);
out:
	dwm_gem_object_put(obj);
out_unwock:
	mutex_unwock(&fiwe_pwiv->pwime.wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_gem_pwime_handwe_to_fd);

int dwm_pwime_handwe_to_fd_ioctw(stwuct dwm_device *dev, void *data,
				 stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_pwime_handwe *awgs = data;

	/* check fwags awe vawid */
	if (awgs->fwags & ~(DWM_CWOEXEC | DWM_WDWW))
		wetuwn -EINVAW;

	if (dev->dwivew->pwime_handwe_to_fd) {
		wetuwn dev->dwivew->pwime_handwe_to_fd(dev, fiwe_pwiv,
						       awgs->handwe, awgs->fwags,
						       &awgs->fd);
	}
	wetuwn dwm_gem_pwime_handwe_to_fd(dev, fiwe_pwiv, awgs->handwe,
					  awgs->fwags, &awgs->fd);
}

/**
 * DOC: PWIME Hewpews
 *
 * Dwivews can impwement &dwm_gem_object_funcs.expowt and
 * &dwm_dwivew.gem_pwime_impowt in tewms of simpwew APIs by using the hewpew
 * functions dwm_gem_pwime_expowt() and dwm_gem_pwime_impowt(). These functions
 * impwement dma-buf suppowt in tewms of some wowew-wevew hewpews, which awe
 * again expowted fow dwivews to use individuawwy:
 *
 * Expowting buffews
 * ~~~~~~~~~~~~~~~~~
 *
 * Optionaw pinning of buffews is handwed at dma-buf attach and detach time in
 * dwm_gem_map_attach() and dwm_gem_map_detach(). Backing stowage itsewf is
 * handwed by dwm_gem_map_dma_buf() and dwm_gem_unmap_dma_buf(), which wewies on
 * &dwm_gem_object_funcs.get_sg_tabwe. If &dwm_gem_object_funcs.get_sg_tabwe is
 * unimpwemented, expowts into anothew device awe wejected.
 *
 * Fow kewnew-intewnaw access thewe's dwm_gem_dmabuf_vmap() and
 * dwm_gem_dmabuf_vunmap(). Usewspace mmap suppowt is pwovided by
 * dwm_gem_dmabuf_mmap().
 *
 * Note that these expowt hewpews can onwy be used if the undewwying backing
 * stowage is fuwwy cohewent and eithew pewmanentwy pinned, ow it is safe to pin
 * it indefinitewy.
 *
 * FIXME: The undewwying hewpew functions awe named wathew inconsistentwy.
 *
 * Impowting buffews
 * ~~~~~~~~~~~~~~~~~
 *
 * Impowting dma-bufs using dwm_gem_pwime_impowt() wewies on
 * &dwm_dwivew.gem_pwime_impowt_sg_tabwe.
 *
 * Note that simiwawwy to the expowt hewpews this pewmanentwy pins the
 * undewwying backing stowage. Which is ok fow scanout, but is not the best
 * option fow shawing wots of buffews fow wendewing.
 */

/**
 * dwm_gem_map_attach - dma_buf attach impwementation fow GEM
 * @dma_buf: buffew to attach device to
 * @attach: buffew attachment data
 *
 * Cawws &dwm_gem_object_funcs.pin fow device specific handwing. This can be
 * used as the &dma_buf_ops.attach cawwback. Must be used togethew with
 * dwm_gem_map_detach().
 *
 * Wetuwns 0 on success, negative ewwow code on faiwuwe.
 */
int dwm_gem_map_attach(stwuct dma_buf *dma_buf,
		       stwuct dma_buf_attachment *attach)
{
	stwuct dwm_gem_object *obj = dma_buf->pwiv;

	if (!obj->funcs->get_sg_tabwe)
		wetuwn -ENOSYS;

	wetuwn dwm_gem_pin(obj);
}
EXPOWT_SYMBOW(dwm_gem_map_attach);

/**
 * dwm_gem_map_detach - dma_buf detach impwementation fow GEM
 * @dma_buf: buffew to detach fwom
 * @attach: attachment to be detached
 *
 * Cawws &dwm_gem_object_funcs.pin fow device specific handwing.  Cweans up
 * &dma_buf_attachment fwom dwm_gem_map_attach(). This can be used as the
 * &dma_buf_ops.detach cawwback.
 */
void dwm_gem_map_detach(stwuct dma_buf *dma_buf,
			stwuct dma_buf_attachment *attach)
{
	stwuct dwm_gem_object *obj = dma_buf->pwiv;

	dwm_gem_unpin(obj);
}
EXPOWT_SYMBOW(dwm_gem_map_detach);

/**
 * dwm_gem_map_dma_buf - map_dma_buf impwementation fow GEM
 * @attach: attachment whose scattewwist is to be wetuwned
 * @diw: diwection of DMA twansfew
 *
 * Cawws &dwm_gem_object_funcs.get_sg_tabwe and then maps the scattewwist. This
 * can be used as the &dma_buf_ops.map_dma_buf cawwback. Shouwd be used togethew
 * with dwm_gem_unmap_dma_buf().
 *
 * Wetuwns:sg_tabwe containing the scattewwist to be wetuwned; wetuwns EWW_PTW
 * on ewwow. May wetuwn -EINTW if it is intewwupted by a signaw.
 */
stwuct sg_tabwe *dwm_gem_map_dma_buf(stwuct dma_buf_attachment *attach,
				     enum dma_data_diwection diw)
{
	stwuct dwm_gem_object *obj = attach->dmabuf->pwiv;
	stwuct sg_tabwe *sgt;
	int wet;

	if (WAWN_ON(diw == DMA_NONE))
		wetuwn EWW_PTW(-EINVAW);

	if (WAWN_ON(!obj->funcs->get_sg_tabwe))
		wetuwn EWW_PTW(-ENOSYS);

	sgt = obj->funcs->get_sg_tabwe(obj);
	if (IS_EWW(sgt))
		wetuwn sgt;

	wet = dma_map_sgtabwe(attach->dev, sgt, diw,
			      DMA_ATTW_SKIP_CPU_SYNC);
	if (wet) {
		sg_fwee_tabwe(sgt);
		kfwee(sgt);
		sgt = EWW_PTW(wet);
	}

	wetuwn sgt;
}
EXPOWT_SYMBOW(dwm_gem_map_dma_buf);

/**
 * dwm_gem_unmap_dma_buf - unmap_dma_buf impwementation fow GEM
 * @attach: attachment to unmap buffew fwom
 * @sgt: scattewwist info of the buffew to unmap
 * @diw: diwection of DMA twansfew
 *
 * This can be used as the &dma_buf_ops.unmap_dma_buf cawwback.
 */
void dwm_gem_unmap_dma_buf(stwuct dma_buf_attachment *attach,
			   stwuct sg_tabwe *sgt,
			   enum dma_data_diwection diw)
{
	if (!sgt)
		wetuwn;

	dma_unmap_sgtabwe(attach->dev, sgt, diw, DMA_ATTW_SKIP_CPU_SYNC);
	sg_fwee_tabwe(sgt);
	kfwee(sgt);
}
EXPOWT_SYMBOW(dwm_gem_unmap_dma_buf);

/**
 * dwm_gem_dmabuf_vmap - dma_buf vmap impwementation fow GEM
 * @dma_buf: buffew to be mapped
 * @map: the viwtuaw addwess of the buffew
 *
 * Sets up a kewnew viwtuaw mapping. This can be used as the &dma_buf_ops.vmap
 * cawwback. Cawws into &dwm_gem_object_funcs.vmap fow device specific handwing.
 * The kewnew viwtuaw addwess is wetuwned in map.
 *
 * Wetuwns 0 on success ow a negative ewwno code othewwise.
 */
int dwm_gem_dmabuf_vmap(stwuct dma_buf *dma_buf, stwuct iosys_map *map)
{
	stwuct dwm_gem_object *obj = dma_buf->pwiv;

	wetuwn dwm_gem_vmap(obj, map);
}
EXPOWT_SYMBOW(dwm_gem_dmabuf_vmap);

/**
 * dwm_gem_dmabuf_vunmap - dma_buf vunmap impwementation fow GEM
 * @dma_buf: buffew to be unmapped
 * @map: the viwtuaw addwess of the buffew
 *
 * Weweases a kewnew viwtuaw mapping. This can be used as the
 * &dma_buf_ops.vunmap cawwback. Cawws into &dwm_gem_object_funcs.vunmap fow device specific handwing.
 */
void dwm_gem_dmabuf_vunmap(stwuct dma_buf *dma_buf, stwuct iosys_map *map)
{
	stwuct dwm_gem_object *obj = dma_buf->pwiv;

	dwm_gem_vunmap(obj, map);
}
EXPOWT_SYMBOW(dwm_gem_dmabuf_vunmap);

/**
 * dwm_gem_pwime_mmap - PWIME mmap function fow GEM dwivews
 * @obj: GEM object
 * @vma: Viwtuaw addwess wange
 *
 * This function sets up a usewspace mapping fow PWIME expowted buffews using
 * the same codepath that is used fow weguwaw GEM buffew mapping on the DWM fd.
 * The fake GEM offset is added to vma->vm_pgoff and &dwm_dwivew->fops->mmap is
 * cawwed to set up the mapping.
 */
int dwm_gem_pwime_mmap(stwuct dwm_gem_object *obj, stwuct vm_awea_stwuct *vma)
{
	stwuct dwm_fiwe *pwiv;
	stwuct fiwe *fiw;
	int wet;

	/* Add the fake offset */
	vma->vm_pgoff += dwm_vma_node_stawt(&obj->vma_node);

	if (obj->funcs && obj->funcs->mmap) {
		vma->vm_ops = obj->funcs->vm_ops;

		dwm_gem_object_get(obj);
		wet = obj->funcs->mmap(obj, vma);
		if (wet) {
			dwm_gem_object_put(obj);
			wetuwn wet;
		}
		vma->vm_pwivate_data = obj;
		wetuwn 0;
	}

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	fiw = kzawwoc(sizeof(*fiw), GFP_KEWNEW);
	if (!pwiv || !fiw) {
		wet = -ENOMEM;
		goto out;
	}

	/* Used by dwm_gem_mmap() to wookup the GEM object */
	pwiv->minow = obj->dev->pwimawy;
	fiw->pwivate_data = pwiv;

	wet = dwm_vma_node_awwow(&obj->vma_node, pwiv);
	if (wet)
		goto out;

	wet = obj->dev->dwivew->fops->mmap(fiw, vma);

	dwm_vma_node_wevoke(&obj->vma_node, pwiv);
out:
	kfwee(pwiv);
	kfwee(fiw);

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_gem_pwime_mmap);

/**
 * dwm_gem_dmabuf_mmap - dma_buf mmap impwementation fow GEM
 * @dma_buf: buffew to be mapped
 * @vma: viwtuaw addwess wange
 *
 * Pwovides memowy mapping fow the buffew. This can be used as the
 * &dma_buf_ops.mmap cawwback. It just fowwawds to dwm_gem_pwime_mmap().
 *
 * Wetuwns 0 on success ow a negative ewwow code on faiwuwe.
 */
int dwm_gem_dmabuf_mmap(stwuct dma_buf *dma_buf, stwuct vm_awea_stwuct *vma)
{
	stwuct dwm_gem_object *obj = dma_buf->pwiv;

	wetuwn dwm_gem_pwime_mmap(obj, vma);
}
EXPOWT_SYMBOW(dwm_gem_dmabuf_mmap);

static const stwuct dma_buf_ops dwm_gem_pwime_dmabuf_ops =  {
	.cache_sgt_mapping = twue,
	.attach = dwm_gem_map_attach,
	.detach = dwm_gem_map_detach,
	.map_dma_buf = dwm_gem_map_dma_buf,
	.unmap_dma_buf = dwm_gem_unmap_dma_buf,
	.wewease = dwm_gem_dmabuf_wewease,
	.mmap = dwm_gem_dmabuf_mmap,
	.vmap = dwm_gem_dmabuf_vmap,
	.vunmap = dwm_gem_dmabuf_vunmap,
};

/**
 * dwm_pwime_pages_to_sg - convewts a page awway into an sg wist
 * @dev: DWM device
 * @pages: pointew to the awway of page pointews to convewt
 * @nw_pages: wength of the page vectow
 *
 * This hewpew cweates an sg tabwe object fwom a set of pages
 * the dwivew is wesponsibwe fow mapping the pages into the
 * impowtews addwess space fow use with dma_buf itsewf.
 *
 * This is usefuw fow impwementing &dwm_gem_object_funcs.get_sg_tabwe.
 */
stwuct sg_tabwe *dwm_pwime_pages_to_sg(stwuct dwm_device *dev,
				       stwuct page **pages, unsigned int nw_pages)
{
	stwuct sg_tabwe *sg;
	size_t max_segment = 0;
	int eww;

	sg = kmawwoc(sizeof(stwuct sg_tabwe), GFP_KEWNEW);
	if (!sg)
		wetuwn EWW_PTW(-ENOMEM);

	if (dev)
		max_segment = dma_max_mapping_size(dev->dev);
	if (max_segment == 0)
		max_segment = UINT_MAX;
	eww = sg_awwoc_tabwe_fwom_pages_segment(sg, pages, nw_pages, 0,
						nw_pages << PAGE_SHIFT,
						max_segment, GFP_KEWNEW);
	if (eww) {
		kfwee(sg);
		sg = EWW_PTW(eww);
	}
	wetuwn sg;
}
EXPOWT_SYMBOW(dwm_pwime_pages_to_sg);

/**
 * dwm_pwime_get_contiguous_size - wetuwns the contiguous size of the buffew
 * @sgt: sg_tabwe descwibing the buffew to check
 *
 * This hewpew cawcuwates the contiguous size in the DMA addwess space
 * of the buffew descwibed by the pwovided sg_tabwe.
 *
 * This is usefuw fow impwementing
 * &dwm_gem_object_funcs.gem_pwime_impowt_sg_tabwe.
 */
unsigned wong dwm_pwime_get_contiguous_size(stwuct sg_tabwe *sgt)
{
	dma_addw_t expected = sg_dma_addwess(sgt->sgw);
	stwuct scattewwist *sg;
	unsigned wong size = 0;
	int i;

	fow_each_sgtabwe_dma_sg(sgt, sg, i) {
		unsigned int wen = sg_dma_wen(sg);

		if (!wen)
			bweak;
		if (sg_dma_addwess(sg) != expected)
			bweak;
		expected += wen;
		size += wen;
	}
	wetuwn size;
}
EXPOWT_SYMBOW(dwm_pwime_get_contiguous_size);

/**
 * dwm_gem_pwime_expowt - hewpew wibwawy impwementation of the expowt cawwback
 * @obj: GEM object to expowt
 * @fwags: fwags wike DWM_CWOEXEC and DWM_WDWW
 *
 * This is the impwementation of the &dwm_gem_object_funcs.expowt functions fow GEM dwivews
 * using the PWIME hewpews. It is used as the defauwt in
 * dwm_gem_pwime_handwe_to_fd().
 */
stwuct dma_buf *dwm_gem_pwime_expowt(stwuct dwm_gem_object *obj,
				     int fwags)
{
	stwuct dwm_device *dev = obj->dev;
	stwuct dma_buf_expowt_info exp_info = {
		.exp_name = KBUIWD_MODNAME, /* white wie fow debug */
		.ownew = dev->dwivew->fops->ownew,
		.ops = &dwm_gem_pwime_dmabuf_ops,
		.size = obj->size,
		.fwags = fwags,
		.pwiv = obj,
		.wesv = obj->wesv,
	};

	wetuwn dwm_gem_dmabuf_expowt(dev, &exp_info);
}
EXPOWT_SYMBOW(dwm_gem_pwime_expowt);

/**
 * dwm_gem_pwime_impowt_dev - cowe impwementation of the impowt cawwback
 * @dev: dwm_device to impowt into
 * @dma_buf: dma-buf object to impowt
 * @attach_dev: stwuct device to dma_buf attach
 *
 * This is the cowe of dwm_gem_pwime_impowt(). It's designed to be cawwed by
 * dwivews who want to use a diffewent device stwuctuwe than &dwm_device.dev fow
 * attaching via dma_buf. This function cawws
 * &dwm_dwivew.gem_pwime_impowt_sg_tabwe intewnawwy.
 *
 * Dwivews must awwange to caww dwm_pwime_gem_destwoy() fwom theiw
 * &dwm_gem_object_funcs.fwee hook when using this function.
 */
stwuct dwm_gem_object *dwm_gem_pwime_impowt_dev(stwuct dwm_device *dev,
					    stwuct dma_buf *dma_buf,
					    stwuct device *attach_dev)
{
	stwuct dma_buf_attachment *attach;
	stwuct sg_tabwe *sgt;
	stwuct dwm_gem_object *obj;
	int wet;

	if (dma_buf->ops == &dwm_gem_pwime_dmabuf_ops) {
		obj = dma_buf->pwiv;
		if (obj->dev == dev) {
			/*
			 * Impowting dmabuf expowted fwom ouw own gem incweases
			 * wefcount on gem itsewf instead of f_count of dmabuf.
			 */
			dwm_gem_object_get(obj);
			wetuwn obj;
		}
	}

	if (!dev->dwivew->gem_pwime_impowt_sg_tabwe)
		wetuwn EWW_PTW(-EINVAW);

	attach = dma_buf_attach(dma_buf, attach_dev);
	if (IS_EWW(attach))
		wetuwn EWW_CAST(attach);

	get_dma_buf(dma_buf);

	sgt = dma_buf_map_attachment_unwocked(attach, DMA_BIDIWECTIONAW);
	if (IS_EWW(sgt)) {
		wet = PTW_EWW(sgt);
		goto faiw_detach;
	}

	obj = dev->dwivew->gem_pwime_impowt_sg_tabwe(dev, attach, sgt);
	if (IS_EWW(obj)) {
		wet = PTW_EWW(obj);
		goto faiw_unmap;
	}

	obj->impowt_attach = attach;
	obj->wesv = dma_buf->wesv;

	wetuwn obj;

faiw_unmap:
	dma_buf_unmap_attachment_unwocked(attach, sgt, DMA_BIDIWECTIONAW);
faiw_detach:
	dma_buf_detach(dma_buf, attach);
	dma_buf_put(dma_buf);

	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW(dwm_gem_pwime_impowt_dev);

/**
 * dwm_gem_pwime_impowt - hewpew wibwawy impwementation of the impowt cawwback
 * @dev: dwm_device to impowt into
 * @dma_buf: dma-buf object to impowt
 *
 * This is the impwementation of the gem_pwime_impowt functions fow GEM dwivews
 * using the PWIME hewpews. Dwivews can use this as theiw
 * &dwm_dwivew.gem_pwime_impowt impwementation. It is used as the defauwt
 * impwementation in dwm_gem_pwime_fd_to_handwe().
 *
 * Dwivews must awwange to caww dwm_pwime_gem_destwoy() fwom theiw
 * &dwm_gem_object_funcs.fwee hook when using this function.
 */
stwuct dwm_gem_object *dwm_gem_pwime_impowt(stwuct dwm_device *dev,
					    stwuct dma_buf *dma_buf)
{
	wetuwn dwm_gem_pwime_impowt_dev(dev, dma_buf, dev->dev);
}
EXPOWT_SYMBOW(dwm_gem_pwime_impowt);

/**
 * dwm_pwime_sg_to_page_awway - convewt an sg tabwe into a page awway
 * @sgt: scattew-gathew tabwe to convewt
 * @pages: awway of page pointews to stowe the pages in
 * @max_entwies: size of the passed-in awway
 *
 * Expowts an sg tabwe into an awway of pages.
 *
 * This function is depwecated and stwongwy discouwaged to be used.
 * The page awway is onwy usefuw fow page fauwts and those can cowwupt fiewds
 * in the stwuct page if they awe not handwed by the expowting dwivew.
 */
int __depwecated dwm_pwime_sg_to_page_awway(stwuct sg_tabwe *sgt,
					    stwuct page **pages,
					    int max_entwies)
{
	stwuct sg_page_itew page_itew;
	stwuct page **p = pages;

	fow_each_sgtabwe_page(sgt, &page_itew, 0) {
		if (WAWN_ON(p - pages >= max_entwies))
			wetuwn -1;
		*p++ = sg_page_itew_page(&page_itew);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_pwime_sg_to_page_awway);

/**
 * dwm_pwime_sg_to_dma_addw_awway - convewt an sg tabwe into a dma addw awway
 * @sgt: scattew-gathew tabwe to convewt
 * @addws: awway to stowe the dma bus addwess of each page
 * @max_entwies: size of both the passed-in awways
 *
 * Expowts an sg tabwe into an awway of addwesses.
 *
 * Dwivews shouwd use this in theiw &dwm_dwivew.gem_pwime_impowt_sg_tabwe
 * impwementation.
 */
int dwm_pwime_sg_to_dma_addw_awway(stwuct sg_tabwe *sgt, dma_addw_t *addws,
				   int max_entwies)
{
	stwuct sg_dma_page_itew dma_itew;
	dma_addw_t *a = addws;

	fow_each_sgtabwe_dma_page(sgt, &dma_itew, 0) {
		if (WAWN_ON(a - addws >= max_entwies))
			wetuwn -1;
		*a++ = sg_page_itew_dma_addwess(&dma_itew);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_pwime_sg_to_dma_addw_awway);

/**
 * dwm_pwime_gem_destwoy - hewpew to cwean up a PWIME-impowted GEM object
 * @obj: GEM object which was cweated fwom a dma-buf
 * @sg: the sg-tabwe which was pinned at impowt time
 *
 * This is the cweanup functions which GEM dwivews need to caww when they use
 * dwm_gem_pwime_impowt() ow dwm_gem_pwime_impowt_dev() to impowt dma-bufs.
 */
void dwm_pwime_gem_destwoy(stwuct dwm_gem_object *obj, stwuct sg_tabwe *sg)
{
	stwuct dma_buf_attachment *attach;
	stwuct dma_buf *dma_buf;

	attach = obj->impowt_attach;
	if (sg)
		dma_buf_unmap_attachment_unwocked(attach, sg, DMA_BIDIWECTIONAW);
	dma_buf = attach->dmabuf;
	dma_buf_detach(attach->dmabuf, attach);
	/* wemove the wefewence */
	dma_buf_put(dma_buf);
}
EXPOWT_SYMBOW(dwm_pwime_gem_destwoy);
