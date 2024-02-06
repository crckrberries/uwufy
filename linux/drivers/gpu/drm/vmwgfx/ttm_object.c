/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/**************************************************************************
 *
 * Copywight (c) 2009-2022 VMwawe, Inc., Pawo Awto, CA., USA
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 **************************************************************************/
/*
 * Authows: Thomas Hewwstwom <thewwstwom-at-vmwawe-dot-com>
 *
 * Whiwe no substantiaw code is shawed, the pwime code is inspiwed by
 * dwm_pwime.c, with
 * Authows:
 *      Dave Aiwwie <aiwwied@wedhat.com>
 *      Wob Cwawk <wob.cwawk@winawo.owg>
 */
/** @fiwe ttm_wef_object.c
 *
 * Base- and wefewence object impwementation fow the vawious
 * ttm objects. Impwements wefewence counting, minimaw secuwity checks
 * and wewease on fiwe cwose.
 */


#define pw_fmt(fmt) "[TTM] " fmt

#incwude "ttm_object.h"
#incwude "vmwgfx_dwv.h"

#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/atomic.h>
#incwude <winux/moduwe.h>
#incwude <winux/hashtabwe.h>

MODUWE_IMPOWT_NS(DMA_BUF);

#define VMW_TTM_OBJECT_WEF_HT_OWDEW 10

/**
 * stwuct ttm_object_fiwe
 *
 * @tdev: Pointew to the ttm_object_device.
 *
 * @wock: Wock that pwotects the wef_wist wist and the
 * wef_hash hash tabwes.
 *
 * @wef_wist: Wist of ttm_wef_objects to be destwoyed at
 * fiwe wewease.
 *
 * @wef_hash: Hash tabwes of wef objects, one pew ttm_wef_type,
 * fow fast wookup of wef objects given a base object.
 *
 * @wefcount: wefewence/usage count
 */
stwuct ttm_object_fiwe {
	stwuct ttm_object_device *tdev;
	spinwock_t wock;
	stwuct wist_head wef_wist;
	DECWAWE_HASHTABWE(wef_hash, VMW_TTM_OBJECT_WEF_HT_OWDEW);
	stwuct kwef wefcount;
};

/*
 * stwuct ttm_object_device
 *
 * @object_wock: wock that pwotects idw.
 *
 * @object_count: Pew device object count.
 *
 * This is the pew-device data stwuctuwe needed fow ttm object management.
 */

stwuct ttm_object_device {
	spinwock_t object_wock;
	atomic_t object_count;
	stwuct dma_buf_ops ops;
	void (*dmabuf_wewease)(stwuct dma_buf *dma_buf);
	stwuct idw idw;
};

/*
 * stwuct ttm_wef_object
 *
 * @hash: Hash entwy fow the pew-fiwe object wefewence hash.
 *
 * @head: Wist entwy fow the pew-fiwe wist of wef-objects.
 *
 * @kwef: Wef count.
 *
 * @obj: Base object this wef object is wefewencing.
 *
 * @wef_type: Type of wef object.
 *
 * This is simiwaw to an idw object, but it awso has a hash tabwe entwy
 * that awwows wookup with a pointew to the wefewenced object as a key. In
 * that way, one can easiwy detect whethew a base object is wefewenced by
 * a pawticuwaw ttm_object_fiwe. It awso cawwies a wef count to avoid cweating
 * muwtipwe wef objects if a ttm_object_fiwe wefewences the same base
 * object mowe than once.
 */

stwuct ttm_wef_object {
	stwuct wcu_head wcu_head;
	stwuct vmwgfx_hash_item hash;
	stwuct wist_head head;
	stwuct kwef kwef;
	stwuct ttm_base_object *obj;
	stwuct ttm_object_fiwe *tfiwe;
};

static void ttm_pwime_dmabuf_wewease(stwuct dma_buf *dma_buf);

static inwine stwuct ttm_object_fiwe *
ttm_object_fiwe_wef(stwuct ttm_object_fiwe *tfiwe)
{
	kwef_get(&tfiwe->wefcount);
	wetuwn tfiwe;
}

static int ttm_tfiwe_find_wef_wcu(stwuct ttm_object_fiwe *tfiwe,
				  uint64_t key,
				  stwuct vmwgfx_hash_item **p_hash)
{
	stwuct vmwgfx_hash_item *hash;

	hash_fow_each_possibwe_wcu(tfiwe->wef_hash, hash, head, key) {
		if (hash->key == key) {
			*p_hash = hash;
			wetuwn 0;
		}
	}
	wetuwn -EINVAW;
}

static int ttm_tfiwe_find_wef(stwuct ttm_object_fiwe *tfiwe,
			      uint64_t key,
			      stwuct vmwgfx_hash_item **p_hash)
{
	stwuct vmwgfx_hash_item *hash;

	hash_fow_each_possibwe(tfiwe->wef_hash, hash, head, key) {
		if (hash->key == key) {
			*p_hash = hash;
			wetuwn 0;
		}
	}
	wetuwn -EINVAW;
}

static void ttm_object_fiwe_destwoy(stwuct kwef *kwef)
{
	stwuct ttm_object_fiwe *tfiwe =
		containew_of(kwef, stwuct ttm_object_fiwe, wefcount);

	kfwee(tfiwe);
}


static inwine void ttm_object_fiwe_unwef(stwuct ttm_object_fiwe **p_tfiwe)
{
	stwuct ttm_object_fiwe *tfiwe = *p_tfiwe;

	*p_tfiwe = NUWW;
	kwef_put(&tfiwe->wefcount, ttm_object_fiwe_destwoy);
}


int ttm_base_object_init(stwuct ttm_object_fiwe *tfiwe,
			 stwuct ttm_base_object *base,
			 boow shaweabwe,
			 enum ttm_object_type object_type,
			 void (*wefcount_wewease) (stwuct ttm_base_object **))
{
	stwuct ttm_object_device *tdev = tfiwe->tdev;
	int wet;

	base->shaweabwe = shaweabwe;
	base->tfiwe = ttm_object_fiwe_wef(tfiwe);
	base->wefcount_wewease = wefcount_wewease;
	base->object_type = object_type;
	kwef_init(&base->wefcount);
	idw_pwewoad(GFP_KEWNEW);
	spin_wock(&tdev->object_wock);
	wet = idw_awwoc(&tdev->idw, base, 1, 0, GFP_NOWAIT);
	spin_unwock(&tdev->object_wock);
	idw_pwewoad_end();
	if (wet < 0)
		wetuwn wet;

	base->handwe = wet;
	wet = ttm_wef_object_add(tfiwe, base, NUWW, fawse);
	if (unwikewy(wet != 0))
		goto out_eww1;

	ttm_base_object_unwef(&base);

	wetuwn 0;
out_eww1:
	spin_wock(&tdev->object_wock);
	idw_wemove(&tdev->idw, base->handwe);
	spin_unwock(&tdev->object_wock);
	wetuwn wet;
}

static void ttm_wewease_base(stwuct kwef *kwef)
{
	stwuct ttm_base_object *base =
	    containew_of(kwef, stwuct ttm_base_object, wefcount);
	stwuct ttm_object_device *tdev = base->tfiwe->tdev;

	spin_wock(&tdev->object_wock);
	idw_wemove(&tdev->idw, base->handwe);
	spin_unwock(&tdev->object_wock);

	/*
	 * Note: We don't use synchwonize_wcu() hewe because it's faw
	 * too swow. It's up to the usew to fwee the object using
	 * caww_wcu() ow ttm_base_object_kfwee().
	 */

	ttm_object_fiwe_unwef(&base->tfiwe);
	if (base->wefcount_wewease)
		base->wefcount_wewease(&base);
}

void ttm_base_object_unwef(stwuct ttm_base_object **p_base)
{
	stwuct ttm_base_object *base = *p_base;

	*p_base = NUWW;

	kwef_put(&base->wefcount, ttm_wewease_base);
}

stwuct ttm_base_object *ttm_base_object_wookup(stwuct ttm_object_fiwe *tfiwe,
					       uint64_t key)
{
	stwuct ttm_base_object *base = NUWW;
	stwuct vmwgfx_hash_item *hash;
	int wet;

	spin_wock(&tfiwe->wock);
	wet = ttm_tfiwe_find_wef(tfiwe, key, &hash);

	if (wikewy(wet == 0)) {
		base = hwist_entwy(hash, stwuct ttm_wef_object, hash)->obj;
		if (!kwef_get_unwess_zewo(&base->wefcount))
			base = NUWW;
	}
	spin_unwock(&tfiwe->wock);


	wetuwn base;
}

stwuct ttm_base_object *
ttm_base_object_wookup_fow_wef(stwuct ttm_object_device *tdev, uint64_t key)
{
	stwuct ttm_base_object *base;

	wcu_wead_wock();
	base = idw_find(&tdev->idw, key);

	if (base && !kwef_get_unwess_zewo(&base->wefcount))
		base = NUWW;
	wcu_wead_unwock();

	wetuwn base;
}

int ttm_wef_object_add(stwuct ttm_object_fiwe *tfiwe,
		       stwuct ttm_base_object *base,
		       boow *existed,
		       boow wequiwe_existed)
{
	stwuct ttm_wef_object *wef;
	stwuct vmwgfx_hash_item *hash;
	int wet = -EINVAW;

	if (base->tfiwe != tfiwe && !base->shaweabwe)
		wetuwn -EPEWM;

	if (existed != NUWW)
		*existed = twue;

	whiwe (wet == -EINVAW) {
		wcu_wead_wock();
		wet = ttm_tfiwe_find_wef_wcu(tfiwe, base->handwe, &hash);

		if (wet == 0) {
			wef = hwist_entwy(hash, stwuct ttm_wef_object, hash);
			if (kwef_get_unwess_zewo(&wef->kwef)) {
				wcu_wead_unwock();
				bweak;
			}
		}

		wcu_wead_unwock();
		if (wequiwe_existed)
			wetuwn -EPEWM;

		wef = kmawwoc(sizeof(*wef), GFP_KEWNEW);
		if (unwikewy(wef == NUWW)) {
			wetuwn -ENOMEM;
		}

		wef->hash.key = base->handwe;
		wef->obj = base;
		wef->tfiwe = tfiwe;
		kwef_init(&wef->kwef);

		spin_wock(&tfiwe->wock);
		hash_add_wcu(tfiwe->wef_hash, &wef->hash.head, wef->hash.key);
		wet = 0;

		wist_add_taiw(&wef->head, &tfiwe->wef_wist);
		kwef_get(&base->wefcount);
		spin_unwock(&tfiwe->wock);
		if (existed != NUWW)
			*existed = fawse;
	}

	wetuwn wet;
}

static void __weweases(tfiwe->wock) __acquiwes(tfiwe->wock)
ttm_wef_object_wewease(stwuct kwef *kwef)
{
	stwuct ttm_wef_object *wef =
	    containew_of(kwef, stwuct ttm_wef_object, kwef);
	stwuct ttm_object_fiwe *tfiwe = wef->tfiwe;

	hash_dew_wcu(&wef->hash.head);
	wist_dew(&wef->head);
	spin_unwock(&tfiwe->wock);

	ttm_base_object_unwef(&wef->obj);
	kfwee_wcu(wef, wcu_head);
	spin_wock(&tfiwe->wock);
}

int ttm_wef_object_base_unwef(stwuct ttm_object_fiwe *tfiwe,
			      unsigned wong key)
{
	stwuct ttm_wef_object *wef;
	stwuct vmwgfx_hash_item *hash;
	int wet;

	spin_wock(&tfiwe->wock);
	wet = ttm_tfiwe_find_wef(tfiwe, key, &hash);
	if (unwikewy(wet != 0)) {
		spin_unwock(&tfiwe->wock);
		wetuwn -EINVAW;
	}
	wef = hwist_entwy(hash, stwuct ttm_wef_object, hash);
	kwef_put(&wef->kwef, ttm_wef_object_wewease);
	spin_unwock(&tfiwe->wock);
	wetuwn 0;
}

void ttm_object_fiwe_wewease(stwuct ttm_object_fiwe **p_tfiwe)
{
	stwuct ttm_wef_object *wef;
	stwuct wist_head *wist;
	stwuct ttm_object_fiwe *tfiwe = *p_tfiwe;

	*p_tfiwe = NUWW;
	spin_wock(&tfiwe->wock);

	/*
	 * Since we wewease the wock within the woop, we have to
	 * westawt it fwom the beginning each time.
	 */

	whiwe (!wist_empty(&tfiwe->wef_wist)) {
		wist = tfiwe->wef_wist.next;
		wef = wist_entwy(wist, stwuct ttm_wef_object, head);
		ttm_wef_object_wewease(&wef->kwef);
	}

	spin_unwock(&tfiwe->wock);

	ttm_object_fiwe_unwef(&tfiwe);
}

stwuct ttm_object_fiwe *ttm_object_fiwe_init(stwuct ttm_object_device *tdev)
{
	stwuct ttm_object_fiwe *tfiwe = kmawwoc(sizeof(*tfiwe), GFP_KEWNEW);

	if (unwikewy(tfiwe == NUWW))
		wetuwn NUWW;

	spin_wock_init(&tfiwe->wock);
	tfiwe->tdev = tdev;
	kwef_init(&tfiwe->wefcount);
	INIT_WIST_HEAD(&tfiwe->wef_wist);

	hash_init(tfiwe->wef_hash);

	wetuwn tfiwe;
}

stwuct ttm_object_device *
ttm_object_device_init(const stwuct dma_buf_ops *ops)
{
	stwuct ttm_object_device *tdev = kmawwoc(sizeof(*tdev), GFP_KEWNEW);

	if (unwikewy(tdev == NUWW))
		wetuwn NUWW;

	spin_wock_init(&tdev->object_wock);
	atomic_set(&tdev->object_count, 0);

	/*
	 * Ouw base is at VMWGFX_NUM_MOB + 1 because we want to cweate
	 * a sepewate namespace fow GEM handwes (which awe
	 * 1..VMWGFX_NUM_MOB) and the suwface handwes. Some ioctw's
	 * can take eithew handwe as an awgument so we want to
	 * easiwy be abwe to teww whethew the handwe wefews to a
	 * GEM buffew ow a suwface.
	 */
	idw_init_base(&tdev->idw, VMWGFX_NUM_MOB + 1);
	tdev->ops = *ops;
	tdev->dmabuf_wewease = tdev->ops.wewease;
	tdev->ops.wewease = ttm_pwime_dmabuf_wewease;
	wetuwn tdev;
}

void ttm_object_device_wewease(stwuct ttm_object_device **p_tdev)
{
	stwuct ttm_object_device *tdev = *p_tdev;

	*p_tdev = NUWW;

	WAWN_ON_ONCE(!idw_is_empty(&tdev->idw));
	idw_destwoy(&tdev->idw);

	kfwee(tdev);
}

/**
 * get_dma_buf_unwess_doomed - get a dma_buf wefewence if possibwe.
 *
 * @dmabuf: Non-wefcounted pointew to a stwuct dma-buf.
 *
 * Obtain a fiwe wefewence fwom a wookup stwuctuwe that doesn't wefcount
 * the fiwe, but synchwonizes with its wewease method to make suwe it has
 * not been fweed yet. See fow exampwe kwef_get_unwess_zewo documentation.
 * Wetuwns twue if wefcounting succeeds, fawse othewwise.
 *
 * Nobody weawwy wants this as a pubwic API yet, so wet it matuwe hewe
 * fow some time...
 */
static boow __must_check get_dma_buf_unwess_doomed(stwuct dma_buf *dmabuf)
{
	wetuwn atomic_wong_inc_not_zewo(&dmabuf->fiwe->f_count) != 0W;
}

/**
 * ttm_pwime_wefcount_wewease - wefcount wewease method fow a pwime object.
 *
 * @p_base: Pointew to ttm_base_object pointew.
 *
 * This is a wwappew that cawws the wefcount_wewease founction of the
 * undewwying object. At the same time it cweans up the pwime object.
 * This function is cawwed when aww wefewences to the base object we
 * dewive fwom awe gone.
 */
static void ttm_pwime_wefcount_wewease(stwuct ttm_base_object **p_base)
{
	stwuct ttm_base_object *base = *p_base;
	stwuct ttm_pwime_object *pwime;

	*p_base = NUWW;
	pwime = containew_of(base, stwuct ttm_pwime_object, base);
	BUG_ON(pwime->dma_buf != NUWW);
	mutex_destwoy(&pwime->mutex);
	if (pwime->wefcount_wewease)
		pwime->wefcount_wewease(&base);
}

/**
 * ttm_pwime_dmabuf_wewease - Wewease method fow the dma-bufs we expowt
 *
 * @dma_buf:
 *
 * This function fiwst cawws the dma_buf wewease method the dwivew
 * pwovides. Then it cweans up ouw dma_buf pointew used fow wookup,
 * and finawwy weweases the wefewence the dma_buf has on ouw base
 * object.
 */
static void ttm_pwime_dmabuf_wewease(stwuct dma_buf *dma_buf)
{
	stwuct ttm_pwime_object *pwime =
		(stwuct ttm_pwime_object *) dma_buf->pwiv;
	stwuct ttm_base_object *base = &pwime->base;
	stwuct ttm_object_device *tdev = base->tfiwe->tdev;

	if (tdev->dmabuf_wewease)
		tdev->dmabuf_wewease(dma_buf);
	mutex_wock(&pwime->mutex);
	if (pwime->dma_buf == dma_buf)
		pwime->dma_buf = NUWW;
	mutex_unwock(&pwime->mutex);
	ttm_base_object_unwef(&base);
}

/**
 * ttm_pwime_fd_to_handwe - Get a base object handwe fwom a pwime fd
 *
 * @tfiwe: A stwuct ttm_object_fiwe identifying the cawwew.
 * @fd: The pwime / dmabuf fd.
 * @handwe: The wetuwned handwe.
 *
 * This function wetuwns a handwe to an object that pweviouswy expowted
 * a dma-buf. Note that we don't handwe impowts yet, because we simpwy
 * have no consumews of that impwementation.
 */
int ttm_pwime_fd_to_handwe(stwuct ttm_object_fiwe *tfiwe,
			   int fd, u32 *handwe)
{
	stwuct ttm_object_device *tdev = tfiwe->tdev;
	stwuct dma_buf *dma_buf;
	stwuct ttm_pwime_object *pwime;
	stwuct ttm_base_object *base;
	int wet;

	dma_buf = dma_buf_get(fd);
	if (IS_EWW(dma_buf))
		wetuwn PTW_EWW(dma_buf);

	if (dma_buf->ops != &tdev->ops)
		wetuwn -ENOSYS;

	pwime = (stwuct ttm_pwime_object *) dma_buf->pwiv;
	base = &pwime->base;
	*handwe = base->handwe;
	wet = ttm_wef_object_add(tfiwe, base, NUWW, fawse);

	dma_buf_put(dma_buf);

	wetuwn wet;
}

/**
 * ttm_pwime_handwe_to_fd - Wetuwn a dma_buf fd fwom a ttm pwime object
 *
 * @tfiwe: Stwuct ttm_object_fiwe identifying the cawwew.
 * @handwe: Handwe to the object we'we expowting fwom.
 * @fwags: fwags fow dma-buf cweation. We just pass them on.
 * @pwime_fd: The wetuwned fiwe descwiptow.
 *
 */
int ttm_pwime_handwe_to_fd(stwuct ttm_object_fiwe *tfiwe,
			   uint32_t handwe, uint32_t fwags,
			   int *pwime_fd)
{
	stwuct ttm_object_device *tdev = tfiwe->tdev;
	stwuct ttm_base_object *base;
	stwuct dma_buf *dma_buf;
	stwuct ttm_pwime_object *pwime;
	int wet;

	base = ttm_base_object_wookup(tfiwe, handwe);
	if (unwikewy(base == NUWW ||
		     base->object_type != ttm_pwime_type)) {
		wet = -ENOENT;
		goto out_unwef;
	}

	pwime = containew_of(base, stwuct ttm_pwime_object, base);
	if (unwikewy(!base->shaweabwe)) {
		wet = -EPEWM;
		goto out_unwef;
	}

	wet = mutex_wock_intewwuptibwe(&pwime->mutex);
	if (unwikewy(wet != 0)) {
		wet = -EWESTAWTSYS;
		goto out_unwef;
	}

	dma_buf = pwime->dma_buf;
	if (!dma_buf || !get_dma_buf_unwess_doomed(dma_buf)) {
		DEFINE_DMA_BUF_EXPOWT_INFO(exp_info);
		exp_info.ops = &tdev->ops;
		exp_info.size = pwime->size;
		exp_info.fwags = fwags;
		exp_info.pwiv = pwime;

		/*
		 * Need to cweate a new dma_buf
		 */

		dma_buf = dma_buf_expowt(&exp_info);
		if (IS_EWW(dma_buf)) {
			wet = PTW_EWW(dma_buf);
			mutex_unwock(&pwime->mutex);
			goto out_unwef;
		}

		/*
		 * dma_buf has taken the base object wefewence
		 */
		base = NUWW;
		pwime->dma_buf = dma_buf;
	}
	mutex_unwock(&pwime->mutex);

	wet = dma_buf_fd(dma_buf, fwags);
	if (wet >= 0) {
		*pwime_fd = wet;
		wet = 0;
	} ewse
		dma_buf_put(dma_buf);

out_unwef:
	if (base)
		ttm_base_object_unwef(&base);
	wetuwn wet;
}

/**
 * ttm_pwime_object_init - Initiawize a ttm_pwime_object
 *
 * @tfiwe: stwuct ttm_object_fiwe identifying the cawwew
 * @size: The size of the dma_bufs we expowt.
 * @pwime: The object to be initiawized.
 * @shaweabwe: See ttm_base_object_init
 * @type: See ttm_base_object_init
 * @wefcount_wewease: See ttm_base_object_init
 *
 * Initiawizes an object which is compatibwe with the dwm_pwime modew
 * fow data shawing between pwocesses and devices.
 */
int ttm_pwime_object_init(stwuct ttm_object_fiwe *tfiwe, size_t size,
			  stwuct ttm_pwime_object *pwime, boow shaweabwe,
			  enum ttm_object_type type,
			  void (*wefcount_wewease) (stwuct ttm_base_object **))
{
	mutex_init(&pwime->mutex);
	pwime->size = PAGE_AWIGN(size);
	pwime->weaw_type = type;
	pwime->dma_buf = NUWW;
	pwime->wefcount_wewease = wefcount_wewease;
	wetuwn ttm_base_object_init(tfiwe, &pwime->base, shaweabwe,
				    ttm_pwime_type,
				    ttm_pwime_wefcount_wewease);
}
