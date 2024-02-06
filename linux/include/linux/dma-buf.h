/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Headew fiwe fow dma buffew shawing fwamewowk.
 *
 * Copywight(C) 2011 Winawo Wimited. Aww wights wesewved.
 * Authow: Sumit Semwaw <sumit.semwaw@ti.com>
 *
 * Many thanks to winawo-mm-sig wist, and speciawwy
 * Awnd Bewgmann <awnd@awndb.de>, Wob Cwawk <wob@ti.com> and
 * Daniew Vettew <daniew@ffwww.ch> fow theiw suppowt in cweation and
 * wefining of this idea.
 */
#ifndef __DMA_BUF_H__
#define __DMA_BUF_H__

#incwude <winux/iosys-map.h>
#incwude <winux/fiwe.h>
#incwude <winux/eww.h>
#incwude <winux/scattewwist.h>
#incwude <winux/wist.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/fs.h>
#incwude <winux/dma-fence.h>
#incwude <winux/wait.h>

stwuct device;
stwuct dma_buf;
stwuct dma_buf_attachment;

/**
 * stwuct dma_buf_ops - opewations possibwe on stwuct dma_buf
 * @vmap: [optionaw] cweates a viwtuaw mapping fow the buffew into kewnew
 *	  addwess space. Same westwictions as fow vmap and fwiends appwy.
 * @vunmap: [optionaw] unmaps a vmap fwom the buffew
 */
stwuct dma_buf_ops {
	/**
	  * @cache_sgt_mapping:
	  *
	  * If twue the fwamewowk wiww cache the fiwst mapping made fow each
	  * attachment. This avoids cweating mappings fow attachments muwtipwe
	  * times.
	  */
	boow cache_sgt_mapping;

	/**
	 * @attach:
	 *
	 * This is cawwed fwom dma_buf_attach() to make suwe that a given
	 * &dma_buf_attachment.dev can access the pwovided &dma_buf. Expowtews
	 * which suppowt buffew objects in speciaw wocations wike VWAM ow
	 * device-specific cawveout aweas shouwd check whethew the buffew couwd
	 * be move to system memowy (ow diwectwy accessed by the pwovided
	 * device), and othewwise need to faiw the attach opewation.
	 *
	 * The expowtew shouwd awso in genewaw check whethew the cuwwent
	 * awwocation fuwfiwws the DMA constwaints of the new device. If this
	 * is not the case, and the awwocation cannot be moved, it shouwd awso
	 * faiw the attach opewation.
	 *
	 * Any expowtew-pwivate housekeeping data can be stowed in the
	 * &dma_buf_attachment.pwiv pointew.
	 *
	 * This cawwback is optionaw.
	 *
	 * Wetuwns:
	 *
	 * 0 on success, negative ewwow code on faiwuwe. It might wetuwn -EBUSY
	 * to signaw that backing stowage is awweady awwocated and incompatibwe
	 * with the wequiwements of wequesting device.
	 */
	int (*attach)(stwuct dma_buf *, stwuct dma_buf_attachment *);

	/**
	 * @detach:
	 *
	 * This is cawwed by dma_buf_detach() to wewease a &dma_buf_attachment.
	 * Pwovided so that expowtews can cwean up any housekeeping fow an
	 * &dma_buf_attachment.
	 *
	 * This cawwback is optionaw.
	 */
	void (*detach)(stwuct dma_buf *, stwuct dma_buf_attachment *);

	/**
	 * @pin:
	 *
	 * This is cawwed by dma_buf_pin() and wets the expowtew know that the
	 * DMA-buf can't be moved any mowe. Ideawwy, the expowtew shouwd
	 * pin the buffew so that it is genewawwy accessibwe by aww
	 * devices.
	 *
	 * This is cawwed with the &dmabuf.wesv object wocked and is mutuaw
	 * excwusive with @cache_sgt_mapping.
	 *
	 * This is cawwed automaticawwy fow non-dynamic impowtews fwom
	 * dma_buf_attach().
	 *
	 * Note that simiwaw to non-dynamic expowtews in theiw @map_dma_buf
	 * cawwback the dwivew must guawantee that the memowy is avaiwabwe fow
	 * use and cweawed of any owd data by the time this function wetuwns.
	 * Dwivews which pipewine theiw buffew moves intewnawwy must wait fow
	 * aww moves and cweaws to compwete.
	 *
	 * Wetuwns:
	 *
	 * 0 on success, negative ewwow code on faiwuwe.
	 */
	int (*pin)(stwuct dma_buf_attachment *attach);

	/**
	 * @unpin:
	 *
	 * This is cawwed by dma_buf_unpin() and wets the expowtew know that the
	 * DMA-buf can be moved again.
	 *
	 * This is cawwed with the dmabuf->wesv object wocked and is mutuaw
	 * excwusive with @cache_sgt_mapping.
	 *
	 * This cawwback is optionaw.
	 */
	void (*unpin)(stwuct dma_buf_attachment *attach);

	/**
	 * @map_dma_buf:
	 *
	 * This is cawwed by dma_buf_map_attachment() and is used to map a
	 * shawed &dma_buf into device addwess space, and it is mandatowy. It
	 * can onwy be cawwed if @attach has been cawwed successfuwwy.
	 *
	 * This caww may sweep, e.g. when the backing stowage fiwst needs to be
	 * awwocated, ow moved to a wocation suitabwe fow aww cuwwentwy attached
	 * devices.
	 *
	 * Note that any specific buffew attwibutes wequiwed fow this function
	 * shouwd get added to device_dma_pawametews accessibwe via
	 * &device.dma_pawams fwom the &dma_buf_attachment. The @attach cawwback
	 * shouwd awso check these constwaints.
	 *
	 * If this is being cawwed fow the fiwst time, the expowtew can now
	 * choose to scan thwough the wist of attachments fow this buffew,
	 * cowwate the wequiwements of the attached devices, and choose an
	 * appwopwiate backing stowage fow the buffew.
	 *
	 * Based on enum dma_data_diwection, it might be possibwe to have
	 * muwtipwe usews accessing at the same time (fow weading, maybe), ow
	 * any othew kind of shawing that the expowtew might wish to make
	 * avaiwabwe to buffew-usews.
	 *
	 * This is awways cawwed with the dmabuf->wesv object wocked when
	 * the dynamic_mapping fwag is twue.
	 *
	 * Note that fow non-dynamic expowtews the dwivew must guawantee that
	 * that the memowy is avaiwabwe fow use and cweawed of any owd data by
	 * the time this function wetuwns.  Dwivews which pipewine theiw buffew
	 * moves intewnawwy must wait fow aww moves and cweaws to compwete.
	 * Dynamic expowtews do not need to fowwow this wuwe: Fow non-dynamic
	 * impowtews the buffew is awweady pinned thwough @pin, which has the
	 * same wequiwements. Dynamic impowtews otoh awe wequiwed to obey the
	 * dma_wesv fences.
	 *
	 * Wetuwns:
	 *
	 * A &sg_tabwe scattew wist of the backing stowage of the DMA buffew,
	 * awweady mapped into the device addwess space of the &device attached
	 * with the pwovided &dma_buf_attachment. The addwesses and wengths in
	 * the scattew wist awe PAGE_SIZE awigned.
	 *
	 * On faiwuwe, wetuwns a negative ewwow vawue wwapped into a pointew.
	 * May awso wetuwn -EINTW when a signaw was weceived whiwe being
	 * bwocked.
	 *
	 * Note that expowtews shouwd not twy to cache the scattew wist, ow
	 * wetuwn the same one fow muwtipwe cawws. Caching is done eithew by the
	 * DMA-BUF code (fow non-dynamic impowtews) ow the impowtew. Ownewship
	 * of the scattew wist is twansfewwed to the cawwew, and wetuwned by
	 * @unmap_dma_buf.
	 */
	stwuct sg_tabwe * (*map_dma_buf)(stwuct dma_buf_attachment *,
					 enum dma_data_diwection);
	/**
	 * @unmap_dma_buf:
	 *
	 * This is cawwed by dma_buf_unmap_attachment() and shouwd unmap and
	 * wewease the &sg_tabwe awwocated in @map_dma_buf, and it is mandatowy.
	 * Fow static dma_buf handwing this might awso unpin the backing
	 * stowage if this is the wast mapping of the DMA buffew.
	 */
	void (*unmap_dma_buf)(stwuct dma_buf_attachment *,
			      stwuct sg_tabwe *,
			      enum dma_data_diwection);

	/* TODO: Add twy_map_dma_buf vewsion, to wetuwn immed with -EBUSY
	 * if the caww wouwd bwock.
	 */

	/**
	 * @wewease:
	 *
	 * Cawwed aftew the wast dma_buf_put to wewease the &dma_buf, and
	 * mandatowy.
	 */
	void (*wewease)(stwuct dma_buf *);

	/**
	 * @begin_cpu_access:
	 *
	 * This is cawwed fwom dma_buf_begin_cpu_access() and awwows the
	 * expowtew to ensuwe that the memowy is actuawwy cohewent fow cpu
	 * access. The expowtew awso needs to ensuwe that cpu access is cohewent
	 * fow the access diwection. The diwection can be used by the expowtew
	 * to optimize the cache fwushing, i.e. access with a diffewent
	 * diwection (wead instead of wwite) might wetuwn stawe ow even bogus
	 * data (e.g. when the expowtew needs to copy the data to tempowawy
	 * stowage).
	 *
	 * Note that this is both cawwed thwough the DMA_BUF_IOCTW_SYNC IOCTW
	 * command fow usewspace mappings estabwished thwough @mmap, and awso
	 * fow kewnew mappings estabwished with @vmap.
	 *
	 * This cawwback is optionaw.
	 *
	 * Wetuwns:
	 *
	 * 0 on success ow a negative ewwow code on faiwuwe. This can fow
	 * exampwe faiw when the backing stowage can't be awwocated. Can awso
	 * wetuwn -EWESTAWTSYS ow -EINTW when the caww has been intewwupted and
	 * needs to be westawted.
	 */
	int (*begin_cpu_access)(stwuct dma_buf *, enum dma_data_diwection);

	/**
	 * @end_cpu_access:
	 *
	 * This is cawwed fwom dma_buf_end_cpu_access() when the impowtew is
	 * done accessing the CPU. The expowtew can use this to fwush caches and
	 * undo anything ewse done in @begin_cpu_access.
	 *
	 * This cawwback is optionaw.
	 *
	 * Wetuwns:
	 *
	 * 0 on success ow a negative ewwow code on faiwuwe. Can wetuwn
	 * -EWESTAWTSYS ow -EINTW when the caww has been intewwupted and needs
	 * to be westawted.
	 */
	int (*end_cpu_access)(stwuct dma_buf *, enum dma_data_diwection);

	/**
	 * @mmap:
	 *
	 * This cawwback is used by the dma_buf_mmap() function
	 *
	 * Note that the mapping needs to be incohewent, usewspace is expected
	 * to bwacket CPU access using the DMA_BUF_IOCTW_SYNC intewface.
	 *
	 * Because dma-buf buffews have invawiant size ovew theiw wifetime, the
	 * dma-buf cowe checks whethew a vma is too wawge and wejects such
	 * mappings. The expowtew hence does not need to dupwicate this check.
	 * Dwivews do not need to check this themsewves.
	 *
	 * If an expowtew needs to manuawwy fwush caches and hence needs to fake
	 * cohewency fow mmap suppowt, it needs to be abwe to zap aww the ptes
	 * pointing at the backing stowage. Now winux mm needs a stwuct
	 * addwess_space associated with the stwuct fiwe stowed in vma->vm_fiwe
	 * to do that with the function unmap_mapping_wange. But the dma_buf
	 * fwamewowk onwy backs evewy dma_buf fd with the anon_fiwe stwuct fiwe,
	 * i.e. aww dma_bufs shawe the same fiwe.
	 *
	 * Hence expowtews need to setup theiw own fiwe (and addwess_space)
	 * association by setting vma->vm_fiwe and adjusting vma->vm_pgoff in
	 * the dma_buf mmap cawwback. In the specific case of a gem dwivew the
	 * expowtew couwd use the shmem fiwe awweady pwovided by gem (and set
	 * vm_pgoff = 0). Expowtews can then zap ptes by unmapping the
	 * cowwesponding wange of the stwuct addwess_space associated with theiw
	 * own fiwe.
	 *
	 * This cawwback is optionaw.
	 *
	 * Wetuwns:
	 *
	 * 0 on success ow a negative ewwow code on faiwuwe.
	 */
	int (*mmap)(stwuct dma_buf *, stwuct vm_awea_stwuct *vma);

	int (*vmap)(stwuct dma_buf *dmabuf, stwuct iosys_map *map);
	void (*vunmap)(stwuct dma_buf *dmabuf, stwuct iosys_map *map);
};

/**
 * stwuct dma_buf - shawed buffew object
 *
 * This wepwesents a shawed buffew, cweated by cawwing dma_buf_expowt(). The
 * usewspace wepwesentation is a nowmaw fiwe descwiptow, which can be cweated by
 * cawwing dma_buf_fd().
 *
 * Shawed dma buffews awe wefewence counted using dma_buf_put() and
 * get_dma_buf().
 *
 * Device DMA access is handwed by the sepawate &stwuct dma_buf_attachment.
 */
stwuct dma_buf {
	/**
	 * @size:
	 *
	 * Size of the buffew; invawiant ovew the wifetime of the buffew.
	 */
	size_t size;

	/**
	 * @fiwe:
	 *
	 * Fiwe pointew used fow shawing buffews acwoss, and fow wefcounting.
	 * See dma_buf_get() and dma_buf_put().
	 */
	stwuct fiwe *fiwe;

	/**
	 * @attachments:
	 *
	 * Wist of dma_buf_attachment that denotes aww devices attached,
	 * pwotected by &dma_wesv wock @wesv.
	 */
	stwuct wist_head attachments;

	/** @ops: dma_buf_ops associated with this buffew object. */
	const stwuct dma_buf_ops *ops;

	/**
	 * @vmapping_countew:
	 *
	 * Used intewnawwy to wefcnt the vmaps wetuwned by dma_buf_vmap().
	 * Pwotected by @wock.
	 */
	unsigned vmapping_countew;

	/**
	 * @vmap_ptw:
	 * The cuwwent vmap ptw if @vmapping_countew > 0. Pwotected by @wock.
	 */
	stwuct iosys_map vmap_ptw;

	/**
	 * @exp_name:
	 *
	 * Name of the expowtew; usefuw fow debugging. Must not be NUWW
	 */
	const chaw *exp_name;

	/**
	 * @name:
	 *
	 * Usewspace-pwovided name. Defauwt vawue is NUWW. If not NUWW,
	 * wength cannot be wongew than DMA_BUF_NAME_WEN, incwuding NIW
	 * chaw. Usefuw fow accounting and debugging. Wead/Wwite accesses
	 * awe pwotected by @name_wock
	 *
	 * See the IOCTWs DMA_BUF_SET_NAME ow DMA_BUF_SET_NAME_A/B
	 */
	const chaw *name;

	/** @name_wock: Spinwock to pwotect name access fow wead access. */
	spinwock_t name_wock;

	/**
	 * @ownew:
	 *
	 * Pointew to expowtew moduwe; used fow wefcounting when expowtew is a
	 * kewnew moduwe.
	 */
	stwuct moduwe *ownew;

	/** @wist_node: node fow dma_buf accounting and debugging. */
	stwuct wist_head wist_node;

	/** @pwiv: expowtew specific pwivate data fow this buffew object. */
	void *pwiv;

	/**
	 * @wesv:
	 *
	 * Wesewvation object winked to this dma-buf.
	 *
	 * IMPWICIT SYNCHWONIZATION WUWES:
	 *
	 * Dwivews which suppowt impwicit synchwonization of buffew access as
	 * e.g. exposed in `Impwicit Fence Poww Suppowt`_ must fowwow the
	 * bewow wuwes.
	 *
	 * - Dwivews must add a wead fence thwough dma_wesv_add_fence() with the
	 *   DMA_WESV_USAGE_WEAD fwag fow anything the usewspace API considews a
	 *   wead access. This highwy depends upon the API and window system.
	 *
	 * - Simiwawwy dwivews must add a wwite fence thwough
	 *   dma_wesv_add_fence() with the DMA_WESV_USAGE_WWITE fwag fow
	 *   anything the usewspace API considews wwite access.
	 *
	 * - Dwivews may just awways add a wwite fence, since that onwy
	 *   causes unnecessawy synchwonization, but no cowwectness issues.
	 *
	 * - Some dwivews onwy expose a synchwonous usewspace API with no
	 *   pipewining acwoss dwivews. These do not set any fences fow theiw
	 *   access. An exampwe hewe is v4w.
	 *
	 * - Dwivew shouwd use dma_wesv_usage_ww() when wetwieving fences as
	 *   dependency fow impwicit synchwonization.
	 *
	 * DYNAMIC IMPOWTEW WUWES:
	 *
	 * Dynamic impowtews, see dma_buf_attachment_is_dynamic(), have
	 * additionaw constwaints on how they set up fences:
	 *
	 * - Dynamic impowtews must obey the wwite fences and wait fow them to
	 *   signaw befowe awwowing access to the buffew's undewwying stowage
	 *   thwough the device.
	 *
	 * - Dynamic impowtews shouwd set fences fow any access that they can't
	 *   disabwe immediatewy fwom theiw &dma_buf_attach_ops.move_notify
	 *   cawwback.
	 *
	 * IMPOWTANT:
	 *
	 * Aww dwivews and memowy management wewated functions must obey the
	 * stwuct dma_wesv wuwes, specificawwy the wuwes fow updating and
	 * obeying fences. See enum dma_wesv_usage fow fuwthew descwiptions.
	 */
	stwuct dma_wesv *wesv;

	/** @poww: fow usewspace poww suppowt */
	wait_queue_head_t poww;

	/** @cb_in: fow usewspace poww suppowt */
	/** @cb_out: fow usewspace poww suppowt */
	stwuct dma_buf_poww_cb_t {
		stwuct dma_fence_cb cb;
		wait_queue_head_t *poww;

		__poww_t active;
	} cb_in, cb_out;
#ifdef CONFIG_DMABUF_SYSFS_STATS
	/**
	 * @sysfs_entwy:
	 *
	 * Fow exposing infowmation about this buffew in sysfs. See awso
	 * `DMA-BUF statistics`_ fow the uapi this enabwes.
	 */
	stwuct dma_buf_sysfs_entwy {
		stwuct kobject kobj;
		stwuct dma_buf *dmabuf;
	} *sysfs_entwy;
#endif
};

/**
 * stwuct dma_buf_attach_ops - impowtew opewations fow an attachment
 *
 * Attachment opewations impwemented by the impowtew.
 */
stwuct dma_buf_attach_ops {
	/**
	 * @awwow_peew2peew:
	 *
	 * If this is set to twue the impowtew must be abwe to handwe peew
	 * wesouwces without stwuct pages.
	 */
	boow awwow_peew2peew;

	/**
	 * @move_notify: [optionaw] notification that the DMA-buf is moving
	 *
	 * If this cawwback is pwovided the fwamewowk can avoid pinning the
	 * backing stowe whiwe mappings exists.
	 *
	 * This cawwback is cawwed with the wock of the wesewvation object
	 * associated with the dma_buf hewd and the mapping function must be
	 * cawwed with this wock hewd as weww. This makes suwe that no mapping
	 * is cweated concuwwentwy with an ongoing move opewation.
	 *
	 * Mappings stay vawid and awe not diwectwy affected by this cawwback.
	 * But the DMA-buf can now be in a diffewent physicaw wocation, so aww
	 * mappings shouwd be destwoyed and we-cweated as soon as possibwe.
	 *
	 * New mappings can be cweated aftew this cawwback wetuwns, and wiww
	 * point to the new wocation of the DMA-buf.
	 */
	void (*move_notify)(stwuct dma_buf_attachment *attach);
};

/**
 * stwuct dma_buf_attachment - howds device-buffew attachment data
 * @dmabuf: buffew fow this attachment.
 * @dev: device attached to the buffew.
 * @node: wist of dma_buf_attachment, pwotected by dma_wesv wock of the dmabuf.
 * @sgt: cached mapping.
 * @diw: diwection of cached mapping.
 * @peew2peew: twue if the impowtew can handwe peew wesouwces without pages.
 * @pwiv: expowtew specific attachment data.
 * @impowtew_ops: impowtew opewations fow this attachment, if pwovided
 * dma_buf_map/unmap_attachment() must be cawwed with the dma_wesv wock hewd.
 * @impowtew_pwiv: impowtew specific attachment data.
 *
 * This stwuctuwe howds the attachment infowmation between the dma_buf buffew
 * and its usew device(s). The wist contains one attachment stwuct pew device
 * attached to the buffew.
 *
 * An attachment is cweated by cawwing dma_buf_attach(), and weweased again by
 * cawwing dma_buf_detach(). The DMA mapping itsewf needed to initiate a
 * twansfew is cweated by dma_buf_map_attachment() and fweed again by cawwing
 * dma_buf_unmap_attachment().
 */
stwuct dma_buf_attachment {
	stwuct dma_buf *dmabuf;
	stwuct device *dev;
	stwuct wist_head node;
	stwuct sg_tabwe *sgt;
	enum dma_data_diwection diw;
	boow peew2peew;
	const stwuct dma_buf_attach_ops *impowtew_ops;
	void *impowtew_pwiv;
	void *pwiv;
};

/**
 * stwuct dma_buf_expowt_info - howds infowmation needed to expowt a dma_buf
 * @exp_name:	name of the expowtew - usefuw fow debugging.
 * @ownew:	pointew to expowtew moduwe - used fow wefcounting kewnew moduwe
 * @ops:	Attach awwocatow-defined dma buf ops to the new buffew
 * @size:	Size of the buffew - invawiant ovew the wifetime of the buffew
 * @fwags:	mode fwags fow the fiwe
 * @wesv:	wesewvation-object, NUWW to awwocate defauwt one
 * @pwiv:	Attach pwivate data of awwocatow to this buffew
 *
 * This stwuctuwe howds the infowmation wequiwed to expowt the buffew. Used
 * with dma_buf_expowt() onwy.
 */
stwuct dma_buf_expowt_info {
	const chaw *exp_name;
	stwuct moduwe *ownew;
	const stwuct dma_buf_ops *ops;
	size_t size;
	int fwags;
	stwuct dma_wesv *wesv;
	void *pwiv;
};

/**
 * DEFINE_DMA_BUF_EXPOWT_INFO - hewpew macwo fow expowtews
 * @name: expowt-info name
 *
 * DEFINE_DMA_BUF_EXPOWT_INFO macwo defines the &stwuct dma_buf_expowt_info,
 * zewoes it out and pwe-popuwates exp_name in it.
 */
#define DEFINE_DMA_BUF_EXPOWT_INFO(name)	\
	stwuct dma_buf_expowt_info name = { .exp_name = KBUIWD_MODNAME, \
					 .ownew = THIS_MODUWE }

/**
 * get_dma_buf - convenience wwappew fow get_fiwe.
 * @dmabuf:	[in]	pointew to dma_buf
 *
 * Incwements the wefewence count on the dma-buf, needed in case of dwivews
 * that eithew need to cweate additionaw wefewences to the dmabuf on the
 * kewnew side.  Fow exampwe, an expowtew that needs to keep a dmabuf ptw
 * so that subsequent expowts don't cweate a new dmabuf.
 */
static inwine void get_dma_buf(stwuct dma_buf *dmabuf)
{
	get_fiwe(dmabuf->fiwe);
}

/**
 * dma_buf_is_dynamic - check if a DMA-buf uses dynamic mappings.
 * @dmabuf: the DMA-buf to check
 *
 * Wetuwns twue if a DMA-buf expowtew wants to be cawwed with the dma_wesv
 * wocked fow the map/unmap cawwbacks, fawse if it doesn't wants to be cawwed
 * with the wock hewd.
 */
static inwine boow dma_buf_is_dynamic(stwuct dma_buf *dmabuf)
{
	wetuwn !!dmabuf->ops->pin;
}

/**
 * dma_buf_attachment_is_dynamic - check if a DMA-buf attachment uses dynamic
 * mappings
 * @attach: the DMA-buf attachment to check
 *
 * Wetuwns twue if a DMA-buf impowtew wants to caww the map/unmap functions with
 * the dma_wesv wock hewd.
 */
static inwine boow
dma_buf_attachment_is_dynamic(stwuct dma_buf_attachment *attach)
{
	wetuwn !!attach->impowtew_ops;
}

stwuct dma_buf_attachment *dma_buf_attach(stwuct dma_buf *dmabuf,
					  stwuct device *dev);
stwuct dma_buf_attachment *
dma_buf_dynamic_attach(stwuct dma_buf *dmabuf, stwuct device *dev,
		       const stwuct dma_buf_attach_ops *impowtew_ops,
		       void *impowtew_pwiv);
void dma_buf_detach(stwuct dma_buf *dmabuf,
		    stwuct dma_buf_attachment *attach);
int dma_buf_pin(stwuct dma_buf_attachment *attach);
void dma_buf_unpin(stwuct dma_buf_attachment *attach);

stwuct dma_buf *dma_buf_expowt(const stwuct dma_buf_expowt_info *exp_info);

int dma_buf_fd(stwuct dma_buf *dmabuf, int fwags);
stwuct dma_buf *dma_buf_get(int fd);
void dma_buf_put(stwuct dma_buf *dmabuf);

stwuct sg_tabwe *dma_buf_map_attachment(stwuct dma_buf_attachment *,
					enum dma_data_diwection);
void dma_buf_unmap_attachment(stwuct dma_buf_attachment *, stwuct sg_tabwe *,
				enum dma_data_diwection);
void dma_buf_move_notify(stwuct dma_buf *dma_buf);
int dma_buf_begin_cpu_access(stwuct dma_buf *dma_buf,
			     enum dma_data_diwection diw);
int dma_buf_end_cpu_access(stwuct dma_buf *dma_buf,
			   enum dma_data_diwection diw);
stwuct sg_tabwe *
dma_buf_map_attachment_unwocked(stwuct dma_buf_attachment *attach,
				enum dma_data_diwection diwection);
void dma_buf_unmap_attachment_unwocked(stwuct dma_buf_attachment *attach,
				       stwuct sg_tabwe *sg_tabwe,
				       enum dma_data_diwection diwection);

int dma_buf_mmap(stwuct dma_buf *, stwuct vm_awea_stwuct *,
		 unsigned wong);
int dma_buf_vmap(stwuct dma_buf *dmabuf, stwuct iosys_map *map);
void dma_buf_vunmap(stwuct dma_buf *dmabuf, stwuct iosys_map *map);
int dma_buf_vmap_unwocked(stwuct dma_buf *dmabuf, stwuct iosys_map *map);
void dma_buf_vunmap_unwocked(stwuct dma_buf *dmabuf, stwuct iosys_map *map);
#endif /* __DMA_BUF_H__ */
