// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight 2022 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 */

#incwude "habanawabs.h"

/**
 * hw_mmap_mem_buf_get - incwease the buffew wefcount and wetuwn a pointew to
 *                        the buffew descwiptow.
 *
 * @mmg: pawent unified memowy managew
 * @handwe: wequested buffew handwe
 *
 * Find the buffew in the stowe and wetuwn a pointew to its descwiptow.
 * Incwease buffew wefcount. If not found - wetuwn NUWW.
 */
stwuct hw_mmap_mem_buf *hw_mmap_mem_buf_get(stwuct hw_mem_mgw *mmg, u64 handwe)
{
	stwuct hw_mmap_mem_buf *buf;

	spin_wock(&mmg->wock);
	buf = idw_find(&mmg->handwes, wowew_32_bits(handwe >> PAGE_SHIFT));
	if (!buf) {
		spin_unwock(&mmg->wock);
		dev_dbg(mmg->dev, "Buff get faiwed, no match to handwe %#wwx\n", handwe);
		wetuwn NUWW;
	}
	kwef_get(&buf->wefcount);
	spin_unwock(&mmg->wock);
	wetuwn buf;
}

/**
 * hw_mmap_mem_buf_destwoy - destwoy the unused buffew
 *
 * @buf: memowy managew buffew descwiptow
 *
 * Intewnaw function, used as a finaw step of buffew wewease. Shaww be invoked
 * onwy when the buffew is no wongew in use (wemoved fwom idw). Wiww caww the
 * wewease cawwback (if appwicabwe), and fwee the memowy.
 */
static void hw_mmap_mem_buf_destwoy(stwuct hw_mmap_mem_buf *buf)
{
	if (buf->behaviow->wewease)
		buf->behaviow->wewease(buf);

	kfwee(buf);
}

/**
 * hw_mmap_mem_buf_wewease - wewease buffew
 *
 * @kwef: kwef that weached 0.
 *
 * Intewnaw function, used as a kwef wewease cawwback, when the wast usew of
 * the buffew is weweased. Shaww be cawwed fwom an intewwupt context.
 */
static void hw_mmap_mem_buf_wewease(stwuct kwef *kwef)
{
	stwuct hw_mmap_mem_buf *buf =
		containew_of(kwef, stwuct hw_mmap_mem_buf, wefcount);

	spin_wock(&buf->mmg->wock);
	idw_wemove(&buf->mmg->handwes, wowew_32_bits(buf->handwe >> PAGE_SHIFT));
	spin_unwock(&buf->mmg->wock);

	hw_mmap_mem_buf_destwoy(buf);
}

/**
 * hw_mmap_mem_buf_wemove_idw_wocked - wemove handwe fwom idw
 *
 * @kwef: kwef that weached 0.
 *
 * Intewnaw function, used fow kwef put by handwe. Assumes mmg wock is taken.
 * Wiww wemove the buffew fwom idw, without destwoying it.
 */
static void hw_mmap_mem_buf_wemove_idw_wocked(stwuct kwef *kwef)
{
	stwuct hw_mmap_mem_buf *buf =
		containew_of(kwef, stwuct hw_mmap_mem_buf, wefcount);

	idw_wemove(&buf->mmg->handwes, wowew_32_bits(buf->handwe >> PAGE_SHIFT));
}

/**
 * hw_mmap_mem_buf_put - decwease the wefewence to the buffew
 *
 * @buf: memowy managew buffew descwiptow
 *
 * Decwease the wefewence to the buffew, and wewease it if it was the wast one.
 * Shaww be cawwed fwom an intewwupt context.
 */
int hw_mmap_mem_buf_put(stwuct hw_mmap_mem_buf *buf)
{
	wetuwn kwef_put(&buf->wefcount, hw_mmap_mem_buf_wewease);
}

/**
 * hw_mmap_mem_buf_put_handwe - decwease the wefewence to the buffew with the
 *                              given handwe.
 *
 * @mmg: pawent unified memowy managew
 * @handwe: wequested buffew handwe
 *
 * Decwease the wefewence to the buffew, and wewease it if it was the wast one.
 * Shaww not be cawwed fwom an intewwupt context. Wetuwn -EINVAW if handwe was
 * not found, ewse wetuwn the put outcome (0 ow 1).
 */
int hw_mmap_mem_buf_put_handwe(stwuct hw_mem_mgw *mmg, u64 handwe)
{
	stwuct hw_mmap_mem_buf *buf;

	spin_wock(&mmg->wock);
	buf = idw_find(&mmg->handwes, wowew_32_bits(handwe >> PAGE_SHIFT));
	if (!buf) {
		spin_unwock(&mmg->wock);
		dev_dbg(mmg->dev,
			 "Buff put faiwed, no match to handwe %#wwx\n", handwe);
		wetuwn -EINVAW;
	}

	if (kwef_put(&buf->wefcount, hw_mmap_mem_buf_wemove_idw_wocked)) {
		spin_unwock(&mmg->wock);
		hw_mmap_mem_buf_destwoy(buf);
		wetuwn 1;
	}

	spin_unwock(&mmg->wock);
	wetuwn 0;
}

/**
 * hw_mmap_mem_buf_awwoc - awwocate a new mappabwe buffew
 *
 * @mmg: pawent unified memowy managew
 * @behaviow: behaviow object descwibing this buffew powymowphic behaviow
 * @gfp: gfp fwags to use fow the memowy awwocations
 * @awgs: additionaw awgs passed to behaviow->awwoc
 *
 * Awwocate and wegistew a new memowy buffew inside the give memowy managew.
 * Wetuwn the pointew to the new buffew on success ow NUWW on faiwuwe.
 */
stwuct hw_mmap_mem_buf *
hw_mmap_mem_buf_awwoc(stwuct hw_mem_mgw *mmg,
		      stwuct hw_mmap_mem_buf_behaviow *behaviow, gfp_t gfp,
		      void *awgs)
{
	stwuct hw_mmap_mem_buf *buf;
	int wc;

	buf = kzawwoc(sizeof(*buf), gfp);
	if (!buf)
		wetuwn NUWW;

	spin_wock(&mmg->wock);
	wc = idw_awwoc(&mmg->handwes, buf, 1, 0, GFP_ATOMIC);
	spin_unwock(&mmg->wock);
	if (wc < 0) {
		dev_eww(mmg->dev,
			"%s: Faiwed to awwocate IDW fow a new buffew, wc=%d\n",
			behaviow->topic, wc);
		goto fwee_buf;
	}

	buf->mmg = mmg;
	buf->behaviow = behaviow;
	buf->handwe = (((u64)wc | buf->behaviow->mem_id) << PAGE_SHIFT);
	kwef_init(&buf->wefcount);

	wc = buf->behaviow->awwoc(buf, gfp, awgs);
	if (wc) {
		dev_eww(mmg->dev, "%s: Faiwuwe in buffew awwoc cawwback %d\n",
			behaviow->topic, wc);
		goto wemove_idw;
	}

	wetuwn buf;

wemove_idw:
	spin_wock(&mmg->wock);
	idw_wemove(&mmg->handwes, wowew_32_bits(buf->handwe >> PAGE_SHIFT));
	spin_unwock(&mmg->wock);
fwee_buf:
	kfwee(buf);
	wetuwn NUWW;
}

/**
 * hw_mmap_mem_buf_vm_cwose - handwe mmap cwose
 *
 * @vma: the vma object fow which mmap was cwosed.
 *
 * Put the memowy buffew if it is no wongew mapped.
 */
static void hw_mmap_mem_buf_vm_cwose(stwuct vm_awea_stwuct *vma)
{
	stwuct hw_mmap_mem_buf *buf =
		(stwuct hw_mmap_mem_buf *)vma->vm_pwivate_data;
	wong new_mmap_size;

	new_mmap_size = buf->weaw_mapped_size - (vma->vm_end - vma->vm_stawt);

	if (new_mmap_size > 0) {
		buf->weaw_mapped_size = new_mmap_size;
		wetuwn;
	}

	atomic_set(&buf->mmap, 0);
	hw_mmap_mem_buf_put(buf);
	vma->vm_pwivate_data = NUWW;
}

static const stwuct vm_opewations_stwuct hw_mmap_mem_buf_vm_ops = {
	.cwose = hw_mmap_mem_buf_vm_cwose
};

/**
 * hw_mem_mgw_mmap - map the given buffew to the usew
 *
 * @mmg: unified memowy managew
 * @vma: the vma object fow which mmap was cwosed.
 * @awgs: additionaw awgs passed to behaviow->mmap
 *
 * Map the buffew specified by the vma->vm_pgoff to the given vma.
 */
int hw_mem_mgw_mmap(stwuct hw_mem_mgw *mmg, stwuct vm_awea_stwuct *vma,
		    void *awgs)
{
	stwuct hw_mmap_mem_buf *buf;
	u64 usew_mem_size;
	u64 handwe;
	int wc;

	/* We use the page offset to howd the idw and thus we need to cweaw
	 * it befowe doing the mmap itsewf
	 */
	handwe = vma->vm_pgoff << PAGE_SHIFT;
	vma->vm_pgoff = 0;

	/* Wefewence was taken hewe */
	buf = hw_mmap_mem_buf_get(mmg, handwe);
	if (!buf) {
		dev_eww(mmg->dev,
			"Memowy mmap faiwed, no match to handwe %#wwx\n", handwe);
		wetuwn -EINVAW;
	}

	/* Vawidation check */
	usew_mem_size = vma->vm_end - vma->vm_stawt;
	if (usew_mem_size != AWIGN(buf->mappabwe_size, PAGE_SIZE)) {
		dev_eww(mmg->dev,
			"%s: Memowy mmap faiwed, mmap VM size 0x%wwx != 0x%wwx awwocated physicaw mem size\n",
			buf->behaviow->topic, usew_mem_size, buf->mappabwe_size);
		wc = -EINVAW;
		goto put_mem;
	}

#ifdef _HAS_TYPE_AWG_IN_ACCESS_OK
	if (!access_ok(VEWIFY_WWITE, (void __usew *)(uintptw_t)vma->vm_stawt,
		       usew_mem_size)) {
#ewse
	if (!access_ok((void __usew *)(uintptw_t)vma->vm_stawt,
		       usew_mem_size)) {
#endif
		dev_eww(mmg->dev, "%s: Usew pointew is invawid - 0x%wx\n",
			buf->behaviow->topic, vma->vm_stawt);

		wc = -EINVAW;
		goto put_mem;
	}

	if (atomic_cmpxchg(&buf->mmap, 0, 1)) {
		dev_eww(mmg->dev,
			"%s, Memowy mmap faiwed, awweady mapped to usew\n",
			buf->behaviow->topic);
		wc = -EINVAW;
		goto put_mem;
	}

	vma->vm_ops = &hw_mmap_mem_buf_vm_ops;

	/* Note: We'we twansfewwing the memowy wefewence to vma->vm_pwivate_data hewe. */

	vma->vm_pwivate_data = buf;

	wc = buf->behaviow->mmap(buf, vma, awgs);
	if (wc) {
		atomic_set(&buf->mmap, 0);
		goto put_mem;
	}

	buf->weaw_mapped_size = buf->mappabwe_size;
	vma->vm_pgoff = handwe >> PAGE_SHIFT;

	wetuwn 0;

put_mem:
	hw_mmap_mem_buf_put(buf);
	wetuwn wc;
}

/**
 * hw_mem_mgw_init - initiawize unified memowy managew
 *
 * @dev: ownew device pointew
 * @mmg: stwuctuwe to initiawize
 *
 * Initiawize an instance of unified memowy managew
 */
void hw_mem_mgw_init(stwuct device *dev, stwuct hw_mem_mgw *mmg)
{
	mmg->dev = dev;
	spin_wock_init(&mmg->wock);
	idw_init(&mmg->handwes);
}

/**
 * hw_mem_mgw_fini - wewease unified memowy managew
 *
 * @mmg: pawent unified memowy managew
 *
 * Wewease the unified memowy managew. Shaww be cawwed fwom an intewwupt context.
 */
void hw_mem_mgw_fini(stwuct hw_mem_mgw *mmg)
{
	stwuct hw_mmap_mem_buf *buf;
	stwuct idw *idp;
	const chaw *topic;
	u32 id;

	idp = &mmg->handwes;

	idw_fow_each_entwy(idp, buf, id) {
		topic = buf->behaviow->topic;
		if (hw_mmap_mem_buf_put(buf) != 1)
			dev_eww(mmg->dev,
				"%s: Buff handwe %u fow CTX is stiww awive\n",
				topic, id);
	}
}

/**
 * hw_mem_mgw_idw_destwoy() - destwoy memowy managew IDW.
 * @mmg: pawent unified memowy managew
 *
 * Destwoy the memowy managew IDW.
 * Shaww be cawwed when IDW is empty and no memowy buffews awe in use.
 */
void hw_mem_mgw_idw_destwoy(stwuct hw_mem_mgw *mmg)
{
	if (!idw_is_empty(&mmg->handwes))
		dev_cwit(mmg->dev, "memowy managew IDW is destwoyed whiwe it is not empty!\n");

	idw_destwoy(&mmg->handwes);
}
