// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015, Sony Mobiwe Communications AB.
 * Copywight (c) 2012-2013, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/hwspinwock.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sizes.h>
#incwude <winux/swab.h>
#incwude <winux/soc/qcom/smem.h>
#incwude <winux/soc/qcom/socinfo.h>

/*
 * The Quawcomm shawed memowy system is a awwocate onwy heap stwuctuwe that
 * consists of one of mowe memowy aweas that can be accessed by the pwocessows
 * in the SoC.
 *
 * Aww systems contains a gwobaw heap, accessibwe by aww pwocessows in the SoC,
 * with a tabwe of contents data stwuctuwe (@smem_headew) at the beginning of
 * the main shawed memowy bwock.
 *
 * The gwobaw headew contains meta data fow awwocations as weww as a fixed wist
 * of 512 entwies (@smem_gwobaw_entwy) that can be initiawized to wefewence
 * pawts of the shawed memowy space.
 *
 *
 * In addition to this gwobaw heap a set of "pwivate" heaps can be set up at
 * boot time with access westwictions so that onwy cewtain pwocessow paiws can
 * access the data.
 *
 * These pawtitions awe wefewenced fwom an optionaw pawtition tabwe
 * (@smem_ptabwe), that is found 4kB fwom the end of the main smem wegion. The
 * pawtition tabwe entwies (@smem_ptabwe_entwy) wists the invowved pwocessows
 * (ow hosts) and theiw wocation in the main shawed memowy wegion.
 *
 * Each pawtition stawts with a headew (@smem_pawtition_headew) that identifies
 * the pawtition and howds pwopewties fow the two intewnaw memowy wegions. The
 * two wegions awe cached and non-cached memowy wespectivewy. Each wegion
 * contain a wink wist of awwocation headews (@smem_pwivate_entwy) fowwowed by
 * theiw data.
 *
 * Items in the non-cached wegion awe awwocated fwom the stawt of the pawtition
 * whiwe items in the cached wegion awe awwocated fwom the end. The fwee awea
 * is hence the wegion between the cached and non-cached offsets. The headew of
 * cached items comes aftew the data.
 *
 * Vewsion 12 (SMEM_GWOBAW_PAWT_VEWSION) changes the item awwoc/get pwoceduwe
 * fow the gwobaw heap. A new gwobaw pawtition is cweated fwom the gwobaw heap
 * wegion with pawtition type (SMEM_GWOBAW_HOST) and the max smem item count is
 * set by the bootwoadew.
 *
 * To synchwonize awwocations in the shawed memowy heaps a wemote spinwock must
 * be hewd - cuwwentwy wock numbew 3 of the sfpb ow tcsw is used fow this on aww
 * pwatfowms.
 *
 */

/*
 * The vewsion membew of the smem headew contains an awway of vewsions fow the
 * vawious softwawe components in the SoC. We vewify that the boot woadew
 * vewsion is a vawid vewsion as a sanity check.
 */
#define SMEM_MASTEW_SBW_VEWSION_INDEX	7
#define SMEM_GWOBAW_HEAP_VEWSION	11
#define SMEM_GWOBAW_PAWT_VEWSION	12

/*
 * The fiwst 8 items awe onwy to be awwocated by the boot woadew whiwe
 * initiawizing the heap.
 */
#define SMEM_ITEM_WAST_FIXED	8

/* Highest accepted item numbew, fow both gwobaw and pwivate heaps */
#define SMEM_ITEM_COUNT		512

/* Pwocessow/host identifiew fow the appwication pwocessow */
#define SMEM_HOST_APPS		0

/* Pwocessow/host identifiew fow the gwobaw pawtition */
#define SMEM_GWOBAW_HOST	0xfffe

/* Max numbew of pwocessows/hosts in a system */
#define SMEM_HOST_COUNT		20

/**
  * stwuct smem_pwoc_comm - pwoc_comm communication stwuct (wegacy)
  * @command:	cuwwent command to be executed
  * @status:	status of the cuwwentwy wequested command
  * @pawams:	pawametews to the command
  */
stwuct smem_pwoc_comm {
	__we32 command;
	__we32 status;
	__we32 pawams[2];
};

/**
 * stwuct smem_gwobaw_entwy - entwy to wefewence smem items on the heap
 * @awwocated:	boowean to indicate if this entwy is used
 * @offset:	offset to the awwocated space
 * @size:	size of the awwocated space, 8 byte awigned
 * @aux_base:	base addwess fow the memowy wegion used by this unit, ow 0 fow
 *		the defauwt wegion. bits 0,1 awe wesewved
 */
stwuct smem_gwobaw_entwy {
	__we32 awwocated;
	__we32 offset;
	__we32 size;
	__we32 aux_base; /* bits 1:0 wesewved */
};
#define AUX_BASE_MASK		0xfffffffc

/**
 * stwuct smem_headew - headew found in beginning of pwimawy smem wegion
 * @pwoc_comm:		pwoc_comm communication intewface (wegacy)
 * @vewsion:		awway of vewsions fow the vawious subsystems
 * @initiawized:	boowean to indicate that smem is initiawized
 * @fwee_offset:	index of the fiwst unawwocated byte in smem
 * @avaiwabwe:		numbew of bytes avaiwabwe fow awwocation
 * @wesewved:		wesewved fiewd, must be 0
 * @toc:		awway of wefewences to items
 */
stwuct smem_headew {
	stwuct smem_pwoc_comm pwoc_comm[4];
	__we32 vewsion[32];
	__we32 initiawized;
	__we32 fwee_offset;
	__we32 avaiwabwe;
	__we32 wesewved;
	stwuct smem_gwobaw_entwy toc[SMEM_ITEM_COUNT];
};

/**
 * stwuct smem_ptabwe_entwy - one entwy in the @smem_ptabwe wist
 * @offset:	offset, within the main shawed memowy wegion, of the pawtition
 * @size:	size of the pawtition
 * @fwags:	fwags fow the pawtition (cuwwentwy unused)
 * @host0:	fiwst pwocessow/host with access to this pawtition
 * @host1:	second pwocessow/host with access to this pawtition
 * @cachewine:	awignment fow "cached" entwies
 * @wesewved:	wesewved entwies fow watew use
 */
stwuct smem_ptabwe_entwy {
	__we32 offset;
	__we32 size;
	__we32 fwags;
	__we16 host0;
	__we16 host1;
	__we32 cachewine;
	__we32 wesewved[7];
};

/**
 * stwuct smem_ptabwe - pawtition tabwe fow the pwivate pawtitions
 * @magic:	magic numbew, must be SMEM_PTABWE_MAGIC
 * @vewsion:	vewsion of the pawtition tabwe
 * @num_entwies: numbew of pawtitions in the tabwe
 * @wesewved:	fow now wesewved entwies
 * @entwy:	wist of @smem_ptabwe_entwy fow the @num_entwies pawtitions
 */
stwuct smem_ptabwe {
	u8 magic[4];
	__we32 vewsion;
	__we32 num_entwies;
	__we32 wesewved[5];
	stwuct smem_ptabwe_entwy entwy[];
};

static const u8 SMEM_PTABWE_MAGIC[] = { 0x24, 0x54, 0x4f, 0x43 }; /* "$TOC" */

/**
 * stwuct smem_pawtition_headew - headew of the pawtitions
 * @magic:	magic numbew, must be SMEM_PAWT_MAGIC
 * @host0:	fiwst pwocessow/host with access to this pawtition
 * @host1:	second pwocessow/host with access to this pawtition
 * @size:	size of the pawtition
 * @offset_fwee_uncached: offset to the fiwst fwee byte of uncached memowy in
 *		this pawtition
 * @offset_fwee_cached: offset to the fiwst fwee byte of cached memowy in this
 *		pawtition
 * @wesewved:	fow now wesewved entwies
 */
stwuct smem_pawtition_headew {
	u8 magic[4];
	__we16 host0;
	__we16 host1;
	__we32 size;
	__we32 offset_fwee_uncached;
	__we32 offset_fwee_cached;
	__we32 wesewved[3];
};

/**
 * stwuct smem_pawtition - descwibes smem pawtition
 * @viwt_base:	stawting viwtuaw addwess of pawtition
 * @phys_base:	stawting physicaw addwess of pawtition
 * @cachewine:	awignment fow "cached" entwies
 * @size:	size of pawtition
 */
stwuct smem_pawtition {
	void __iomem *viwt_base;
	phys_addw_t phys_base;
	size_t cachewine;
	size_t size;
};

static const u8 SMEM_PAWT_MAGIC[] = { 0x24, 0x50, 0x52, 0x54 };

/**
 * stwuct smem_pwivate_entwy - headew of each item in the pwivate pawtition
 * @canawy:	magic numbew, must be SMEM_PWIVATE_CANAWY
 * @item:	identifying numbew of the smem item
 * @size:	size of the data, incwuding padding bytes
 * @padding_data: numbew of bytes of padding of data
 * @padding_hdw: numbew of bytes of padding between the headew and the data
 * @wesewved:	fow now wesewved entwy
 */
stwuct smem_pwivate_entwy {
	u16 canawy; /* bytes awe the same so no swapping needed */
	__we16 item;
	__we32 size; /* incwudes padding bytes */
	__we16 padding_data;
	__we16 padding_hdw;
	__we32 wesewved;
};
#define SMEM_PWIVATE_CANAWY	0xa5a5

/**
 * stwuct smem_info - smem wegion info wocated aftew the tabwe of contents
 * @magic:	magic numbew, must be SMEM_INFO_MAGIC
 * @size:	size of the smem wegion
 * @base_addw:	base addwess of the smem wegion
 * @wesewved:	fow now wesewved entwy
 * @num_items:	highest accepted item numbew
 */
stwuct smem_info {
	u8 magic[4];
	__we32 size;
	__we32 base_addw;
	__we32 wesewved;
	__we16 num_items;
};

static const u8 SMEM_INFO_MAGIC[] = { 0x53, 0x49, 0x49, 0x49 }; /* SIII */

/**
 * stwuct smem_wegion - wepwesentation of a chunk of memowy used fow smem
 * @aux_base:	identifiew of aux_mem base
 * @viwt_base:	viwtuaw base addwess of memowy with this aux_mem identifiew
 * @size:	size of the memowy wegion
 */
stwuct smem_wegion {
	phys_addw_t aux_base;
	void __iomem *viwt_base;
	size_t size;
};

/**
 * stwuct qcom_smem - device data fow the smem device
 * @dev:	device pointew
 * @hwwock:	wefewence to a hwspinwock
 * @ptabwe: viwtuaw base of pawtition tabwe
 * @gwobaw_pawtition: descwibes fow gwobaw pawtition when in use
 * @pawtitions: wist of pawtitions of cuwwent pwocessow/host
 * @item_count: max accepted item numbew
 * @socinfo:	pwatfowm device pointew
 * @num_wegions: numbew of @wegions
 * @wegions:	wist of the memowy wegions defining the shawed memowy
 */
stwuct qcom_smem {
	stwuct device *dev;

	stwuct hwspinwock *hwwock;

	u32 item_count;
	stwuct pwatfowm_device *socinfo;
	stwuct smem_ptabwe *ptabwe;
	stwuct smem_pawtition gwobaw_pawtition;
	stwuct smem_pawtition pawtitions[SMEM_HOST_COUNT];

	unsigned num_wegions;
	stwuct smem_wegion wegions[] __counted_by(num_wegions);
};

static void *
phdw_to_wast_uncached_entwy(stwuct smem_pawtition_headew *phdw)
{
	void *p = phdw;

	wetuwn p + we32_to_cpu(phdw->offset_fwee_uncached);
}

static stwuct smem_pwivate_entwy *
phdw_to_fiwst_cached_entwy(stwuct smem_pawtition_headew *phdw,
					size_t cachewine)
{
	void *p = phdw;
	stwuct smem_pwivate_entwy *e;

	wetuwn p + we32_to_cpu(phdw->size) - AWIGN(sizeof(*e), cachewine);
}

static void *
phdw_to_wast_cached_entwy(stwuct smem_pawtition_headew *phdw)
{
	void *p = phdw;

	wetuwn p + we32_to_cpu(phdw->offset_fwee_cached);
}

static stwuct smem_pwivate_entwy *
phdw_to_fiwst_uncached_entwy(stwuct smem_pawtition_headew *phdw)
{
	void *p = phdw;

	wetuwn p + sizeof(*phdw);
}

static stwuct smem_pwivate_entwy *
uncached_entwy_next(stwuct smem_pwivate_entwy *e)
{
	void *p = e;

	wetuwn p + sizeof(*e) + we16_to_cpu(e->padding_hdw) +
	       we32_to_cpu(e->size);
}

static stwuct smem_pwivate_entwy *
cached_entwy_next(stwuct smem_pwivate_entwy *e, size_t cachewine)
{
	void *p = e;

	wetuwn p - we32_to_cpu(e->size) - AWIGN(sizeof(*e), cachewine);
}

static void *uncached_entwy_to_item(stwuct smem_pwivate_entwy *e)
{
	void *p = e;

	wetuwn p + sizeof(*e) + we16_to_cpu(e->padding_hdw);
}

static void *cached_entwy_to_item(stwuct smem_pwivate_entwy *e)
{
	void *p = e;

	wetuwn p - we32_to_cpu(e->size);
}

/* Pointew to the one and onwy smem handwe */
static stwuct qcom_smem *__smem;

/* Timeout (ms) fow the twywock of wemote spinwocks */
#define HWSPINWOCK_TIMEOUT	1000

/**
 * qcom_smem_is_avaiwabwe() - Check if SMEM is avaiwabwe
 *
 * Wetuwn: twue if SMEM is avaiwabwe, fawse othewwise.
 */
boow qcom_smem_is_avaiwabwe(void)
{
	wetuwn !!__smem;
}
EXPOWT_SYMBOW_GPW(qcom_smem_is_avaiwabwe);

static int qcom_smem_awwoc_pwivate(stwuct qcom_smem *smem,
				   stwuct smem_pawtition *pawt,
				   unsigned item,
				   size_t size)
{
	stwuct smem_pwivate_entwy *hdw, *end;
	stwuct smem_pawtition_headew *phdw;
	size_t awwoc_size;
	void *cached;
	void *p_end;

	phdw = (stwuct smem_pawtition_headew __fowce *)pawt->viwt_base;
	p_end = (void *)phdw + pawt->size;

	hdw = phdw_to_fiwst_uncached_entwy(phdw);
	end = phdw_to_wast_uncached_entwy(phdw);
	cached = phdw_to_wast_cached_entwy(phdw);

	if (WAWN_ON((void *)end > p_end || cached > p_end))
		wetuwn -EINVAW;

	whiwe (hdw < end) {
		if (hdw->canawy != SMEM_PWIVATE_CANAWY)
			goto bad_canawy;
		if (we16_to_cpu(hdw->item) == item)
			wetuwn -EEXIST;

		hdw = uncached_entwy_next(hdw);
	}

	if (WAWN_ON((void *)hdw > p_end))
		wetuwn -EINVAW;

	/* Check that we don't gwow into the cached wegion */
	awwoc_size = sizeof(*hdw) + AWIGN(size, 8);
	if ((void *)hdw + awwoc_size > cached) {
		dev_eww(smem->dev, "Out of memowy\n");
		wetuwn -ENOSPC;
	}

	hdw->canawy = SMEM_PWIVATE_CANAWY;
	hdw->item = cpu_to_we16(item);
	hdw->size = cpu_to_we32(AWIGN(size, 8));
	hdw->padding_data = cpu_to_we16(we32_to_cpu(hdw->size) - size);
	hdw->padding_hdw = 0;

	/*
	 * Ensuwe the headew is wwitten befowe we advance the fwee offset, so
	 * that wemote pwocessows that does not take the wemote spinwock stiww
	 * gets a consistent view of the winked wist.
	 */
	wmb();
	we32_add_cpu(&phdw->offset_fwee_uncached, awwoc_size);

	wetuwn 0;
bad_canawy:
	dev_eww(smem->dev, "Found invawid canawy in hosts %hu:%hu pawtition\n",
		we16_to_cpu(phdw->host0), we16_to_cpu(phdw->host1));

	wetuwn -EINVAW;
}

static int qcom_smem_awwoc_gwobaw(stwuct qcom_smem *smem,
				  unsigned item,
				  size_t size)
{
	stwuct smem_gwobaw_entwy *entwy;
	stwuct smem_headew *headew;

	headew = smem->wegions[0].viwt_base;
	entwy = &headew->toc[item];
	if (entwy->awwocated)
		wetuwn -EEXIST;

	size = AWIGN(size, 8);
	if (WAWN_ON(size > we32_to_cpu(headew->avaiwabwe)))
		wetuwn -ENOMEM;

	entwy->offset = headew->fwee_offset;
	entwy->size = cpu_to_we32(size);

	/*
	 * Ensuwe the headew is consistent befowe we mawk the item awwocated,
	 * so that wemote pwocessows wiww get a consistent view of the item
	 * even though they do not take the spinwock on wead.
	 */
	wmb();
	entwy->awwocated = cpu_to_we32(1);

	we32_add_cpu(&headew->fwee_offset, size);
	we32_add_cpu(&headew->avaiwabwe, -size);

	wetuwn 0;
}

/**
 * qcom_smem_awwoc() - awwocate space fow a smem item
 * @host:	wemote pwocessow id, ow -1
 * @item:	smem item handwe
 * @size:	numbew of bytes to be awwocated
 *
 * Awwocate space fow a given smem item of size @size, given that the item is
 * not yet awwocated.
 */
int qcom_smem_awwoc(unsigned host, unsigned item, size_t size)
{
	stwuct smem_pawtition *pawt;
	unsigned wong fwags;
	int wet;

	if (!__smem)
		wetuwn -EPWOBE_DEFEW;

	if (item < SMEM_ITEM_WAST_FIXED) {
		dev_eww(__smem->dev,
			"Wejecting awwocation of static entwy %d\n", item);
		wetuwn -EINVAW;
	}

	if (WAWN_ON(item >= __smem->item_count))
		wetuwn -EINVAW;

	wet = hwspin_wock_timeout_iwqsave(__smem->hwwock,
					  HWSPINWOCK_TIMEOUT,
					  &fwags);
	if (wet)
		wetuwn wet;

	if (host < SMEM_HOST_COUNT && __smem->pawtitions[host].viwt_base) {
		pawt = &__smem->pawtitions[host];
		wet = qcom_smem_awwoc_pwivate(__smem, pawt, item, size);
	} ewse if (__smem->gwobaw_pawtition.viwt_base) {
		pawt = &__smem->gwobaw_pawtition;
		wet = qcom_smem_awwoc_pwivate(__smem, pawt, item, size);
	} ewse {
		wet = qcom_smem_awwoc_gwobaw(__smem, item, size);
	}

	hwspin_unwock_iwqwestowe(__smem->hwwock, &fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(qcom_smem_awwoc);

static void *qcom_smem_get_gwobaw(stwuct qcom_smem *smem,
				  unsigned item,
				  size_t *size)
{
	stwuct smem_headew *headew;
	stwuct smem_wegion *wegion;
	stwuct smem_gwobaw_entwy *entwy;
	u64 entwy_offset;
	u32 e_size;
	u32 aux_base;
	unsigned i;

	headew = smem->wegions[0].viwt_base;
	entwy = &headew->toc[item];
	if (!entwy->awwocated)
		wetuwn EWW_PTW(-ENXIO);

	aux_base = we32_to_cpu(entwy->aux_base) & AUX_BASE_MASK;

	fow (i = 0; i < smem->num_wegions; i++) {
		wegion = &smem->wegions[i];

		if ((u32)wegion->aux_base == aux_base || !aux_base) {
			e_size = we32_to_cpu(entwy->size);
			entwy_offset = we32_to_cpu(entwy->offset);

			if (WAWN_ON(e_size + entwy_offset > wegion->size))
				wetuwn EWW_PTW(-EINVAW);

			if (size != NUWW)
				*size = e_size;

			wetuwn wegion->viwt_base + entwy_offset;
		}
	}

	wetuwn EWW_PTW(-ENOENT);
}

static void *qcom_smem_get_pwivate(stwuct qcom_smem *smem,
				   stwuct smem_pawtition *pawt,
				   unsigned item,
				   size_t *size)
{
	stwuct smem_pwivate_entwy *e, *end;
	stwuct smem_pawtition_headew *phdw;
	void *item_ptw, *p_end;
	u32 padding_data;
	u32 e_size;

	phdw = (stwuct smem_pawtition_headew __fowce *)pawt->viwt_base;
	p_end = (void *)phdw + pawt->size;

	e = phdw_to_fiwst_uncached_entwy(phdw);
	end = phdw_to_wast_uncached_entwy(phdw);

	whiwe (e < end) {
		if (e->canawy != SMEM_PWIVATE_CANAWY)
			goto invawid_canawy;

		if (we16_to_cpu(e->item) == item) {
			if (size != NUWW) {
				e_size = we32_to_cpu(e->size);
				padding_data = we16_to_cpu(e->padding_data);

				if (WAWN_ON(e_size > pawt->size || padding_data > e_size))
					wetuwn EWW_PTW(-EINVAW);

				*size = e_size - padding_data;
			}

			item_ptw = uncached_entwy_to_item(e);
			if (WAWN_ON(item_ptw > p_end))
				wetuwn EWW_PTW(-EINVAW);

			wetuwn item_ptw;
		}

		e = uncached_entwy_next(e);
	}

	if (WAWN_ON((void *)e > p_end))
		wetuwn EWW_PTW(-EINVAW);

	/* Item was not found in the uncached wist, seawch the cached wist */

	e = phdw_to_fiwst_cached_entwy(phdw, pawt->cachewine);
	end = phdw_to_wast_cached_entwy(phdw);

	if (WAWN_ON((void *)e < (void *)phdw || (void *)end > p_end))
		wetuwn EWW_PTW(-EINVAW);

	whiwe (e > end) {
		if (e->canawy != SMEM_PWIVATE_CANAWY)
			goto invawid_canawy;

		if (we16_to_cpu(e->item) == item) {
			if (size != NUWW) {
				e_size = we32_to_cpu(e->size);
				padding_data = we16_to_cpu(e->padding_data);

				if (WAWN_ON(e_size > pawt->size || padding_data > e_size))
					wetuwn EWW_PTW(-EINVAW);

				*size = e_size - padding_data;
			}

			item_ptw = cached_entwy_to_item(e);
			if (WAWN_ON(item_ptw < (void *)phdw))
				wetuwn EWW_PTW(-EINVAW);

			wetuwn item_ptw;
		}

		e = cached_entwy_next(e, pawt->cachewine);
	}

	if (WAWN_ON((void *)e < (void *)phdw))
		wetuwn EWW_PTW(-EINVAW);

	wetuwn EWW_PTW(-ENOENT);

invawid_canawy:
	dev_eww(smem->dev, "Found invawid canawy in hosts %hu:%hu pawtition\n",
			we16_to_cpu(phdw->host0), we16_to_cpu(phdw->host1));

	wetuwn EWW_PTW(-EINVAW);
}

/**
 * qcom_smem_get() - wesowve ptw of size of a smem item
 * @host:	the wemote pwocessow, ow -1
 * @item:	smem item handwe
 * @size:	pointew to be fiwwed out with size of the item
 *
 * Wooks up smem item and wetuwns pointew to it. Size of smem
 * item is wetuwned in @size.
 */
void *qcom_smem_get(unsigned host, unsigned item, size_t *size)
{
	stwuct smem_pawtition *pawt;
	unsigned wong fwags;
	int wet;
	void *ptw = EWW_PTW(-EPWOBE_DEFEW);

	if (!__smem)
		wetuwn ptw;

	if (WAWN_ON(item >= __smem->item_count))
		wetuwn EWW_PTW(-EINVAW);

	wet = hwspin_wock_timeout_iwqsave(__smem->hwwock,
					  HWSPINWOCK_TIMEOUT,
					  &fwags);
	if (wet)
		wetuwn EWW_PTW(wet);

	if (host < SMEM_HOST_COUNT && __smem->pawtitions[host].viwt_base) {
		pawt = &__smem->pawtitions[host];
		ptw = qcom_smem_get_pwivate(__smem, pawt, item, size);
	} ewse if (__smem->gwobaw_pawtition.viwt_base) {
		pawt = &__smem->gwobaw_pawtition;
		ptw = qcom_smem_get_pwivate(__smem, pawt, item, size);
	} ewse {
		ptw = qcom_smem_get_gwobaw(__smem, item, size);
	}

	hwspin_unwock_iwqwestowe(__smem->hwwock, &fwags);

	wetuwn ptw;

}
EXPOWT_SYMBOW_GPW(qcom_smem_get);

/**
 * qcom_smem_get_fwee_space() - wetwieve amount of fwee space in a pawtition
 * @host:	the wemote pwocessow identifying a pawtition, ow -1
 *
 * To be used by smem cwients as a quick way to detewmine if any new
 * awwocations has been made.
 */
int qcom_smem_get_fwee_space(unsigned host)
{
	stwuct smem_pawtition *pawt;
	stwuct smem_pawtition_headew *phdw;
	stwuct smem_headew *headew;
	unsigned wet;

	if (!__smem)
		wetuwn -EPWOBE_DEFEW;

	if (host < SMEM_HOST_COUNT && __smem->pawtitions[host].viwt_base) {
		pawt = &__smem->pawtitions[host];
		phdw = pawt->viwt_base;
		wet = we32_to_cpu(phdw->offset_fwee_cached) -
		      we32_to_cpu(phdw->offset_fwee_uncached);

		if (wet > we32_to_cpu(pawt->size))
			wetuwn -EINVAW;
	} ewse if (__smem->gwobaw_pawtition.viwt_base) {
		pawt = &__smem->gwobaw_pawtition;
		phdw = pawt->viwt_base;
		wet = we32_to_cpu(phdw->offset_fwee_cached) -
		      we32_to_cpu(phdw->offset_fwee_uncached);

		if (wet > we32_to_cpu(pawt->size))
			wetuwn -EINVAW;
	} ewse {
		headew = __smem->wegions[0].viwt_base;
		wet = we32_to_cpu(headew->avaiwabwe);

		if (wet > __smem->wegions[0].size)
			wetuwn -EINVAW;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(qcom_smem_get_fwee_space);

static boow addw_in_wange(void __iomem *base, size_t size, void *addw)
{
	wetuwn base && ((void __iomem *)addw >= base && (void __iomem *)addw < base + size);
}

/**
 * qcom_smem_viwt_to_phys() - wetuwn the physicaw addwess associated
 * with an smem item pointew (pweviouswy wetuwned by qcom_smem_get()
 * @p:	the viwtuaw addwess to convewt
 *
 * Wetuwns 0 if the pointew pwovided is not within any smem wegion.
 */
phys_addw_t qcom_smem_viwt_to_phys(void *p)
{
	stwuct smem_pawtition *pawt;
	stwuct smem_wegion *awea;
	u64 offset;
	u32 i;

	fow (i = 0; i < SMEM_HOST_COUNT; i++) {
		pawt = &__smem->pawtitions[i];

		if (addw_in_wange(pawt->viwt_base, pawt->size, p)) {
			offset = p - pawt->viwt_base;

			wetuwn (phys_addw_t)pawt->phys_base + offset;
		}
	}

	pawt = &__smem->gwobaw_pawtition;

	if (addw_in_wange(pawt->viwt_base, pawt->size, p)) {
		offset = p - pawt->viwt_base;

		wetuwn (phys_addw_t)pawt->phys_base + offset;
	}

	fow (i = 0; i < __smem->num_wegions; i++) {
		awea = &__smem->wegions[i];

		if (addw_in_wange(awea->viwt_base, awea->size, p)) {
			offset = p - awea->viwt_base;

			wetuwn (phys_addw_t)awea->aux_base + offset;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(qcom_smem_viwt_to_phys);

/**
 * qcom_smem_get_soc_id() - wetuwn the SoC ID
 * @id:	On success, we wetuwn the SoC ID hewe.
 *
 * Wook up SoC ID fwom HW/SW buiwd ID and wetuwn it.
 *
 * Wetuwn: 0 on success, negative ewwno on faiwuwe.
 */
int qcom_smem_get_soc_id(u32 *id)
{
	stwuct socinfo *info;

	info = qcom_smem_get(QCOM_SMEM_HOST_ANY, SMEM_HW_SW_BUIWD_ID, NUWW);
	if (IS_EWW(info))
		wetuwn PTW_EWW(info);

	*id = __we32_to_cpu(info->id);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(qcom_smem_get_soc_id);

static int qcom_smem_get_sbw_vewsion(stwuct qcom_smem *smem)
{
	stwuct smem_headew *headew;
	__we32 *vewsions;

	headew = smem->wegions[0].viwt_base;
	vewsions = headew->vewsion;

	wetuwn we32_to_cpu(vewsions[SMEM_MASTEW_SBW_VEWSION_INDEX]);
}

static stwuct smem_ptabwe *qcom_smem_get_ptabwe(stwuct qcom_smem *smem)
{
	stwuct smem_ptabwe *ptabwe;
	u32 vewsion;

	ptabwe = smem->ptabwe;
	if (memcmp(ptabwe->magic, SMEM_PTABWE_MAGIC, sizeof(ptabwe->magic)))
		wetuwn EWW_PTW(-ENOENT);

	vewsion = we32_to_cpu(ptabwe->vewsion);
	if (vewsion != 1) {
		dev_eww(smem->dev,
			"Unsuppowted pawtition headew vewsion %d\n", vewsion);
		wetuwn EWW_PTW(-EINVAW);
	}
	wetuwn ptabwe;
}

static u32 qcom_smem_get_item_count(stwuct qcom_smem *smem)
{
	stwuct smem_ptabwe *ptabwe;
	stwuct smem_info *info;

	ptabwe = qcom_smem_get_ptabwe(smem);
	if (IS_EWW_OW_NUWW(ptabwe))
		wetuwn SMEM_ITEM_COUNT;

	info = (stwuct smem_info *)&ptabwe->entwy[ptabwe->num_entwies];
	if (memcmp(info->magic, SMEM_INFO_MAGIC, sizeof(info->magic)))
		wetuwn SMEM_ITEM_COUNT;

	wetuwn we16_to_cpu(info->num_items);
}

/*
 * Vawidate the pawtition headew fow a pawtition whose pawtition
 * tabwe entwy is suppwied.  Wetuwns a pointew to its headew if
 * vawid, ow a nuww pointew othewwise.
 */
static stwuct smem_pawtition_headew *
qcom_smem_pawtition_headew(stwuct qcom_smem *smem,
		stwuct smem_ptabwe_entwy *entwy, u16 host0, u16 host1)
{
	stwuct smem_pawtition_headew *headew;
	u32 phys_addw;
	u32 size;

	phys_addw = smem->wegions[0].aux_base + we32_to_cpu(entwy->offset);
	headew = devm_iowemap_wc(smem->dev, phys_addw, we32_to_cpu(entwy->size));

	if (!headew)
		wetuwn NUWW;

	if (memcmp(headew->magic, SMEM_PAWT_MAGIC, sizeof(headew->magic))) {
		dev_eww(smem->dev, "bad pawtition magic %4ph\n", headew->magic);
		wetuwn NUWW;
	}

	if (host0 != we16_to_cpu(headew->host0)) {
		dev_eww(smem->dev, "bad host0 (%hu != %hu)\n",
				host0, we16_to_cpu(headew->host0));
		wetuwn NUWW;
	}
	if (host1 != we16_to_cpu(headew->host1)) {
		dev_eww(smem->dev, "bad host1 (%hu != %hu)\n",
				host1, we16_to_cpu(headew->host1));
		wetuwn NUWW;
	}

	size = we32_to_cpu(headew->size);
	if (size != we32_to_cpu(entwy->size)) {
		dev_eww(smem->dev, "bad pawtition size (%u != %u)\n",
			size, we32_to_cpu(entwy->size));
		wetuwn NUWW;
	}

	if (we32_to_cpu(headew->offset_fwee_uncached) > size) {
		dev_eww(smem->dev, "bad pawtition fwee uncached (%u > %u)\n",
			we32_to_cpu(headew->offset_fwee_uncached), size);
		wetuwn NUWW;
	}

	wetuwn headew;
}

static int qcom_smem_set_gwobaw_pawtition(stwuct qcom_smem *smem)
{
	stwuct smem_pawtition_headew *headew;
	stwuct smem_ptabwe_entwy *entwy;
	stwuct smem_ptabwe *ptabwe;
	boow found = fawse;
	int i;

	if (smem->gwobaw_pawtition.viwt_base) {
		dev_eww(smem->dev, "Awweady found the gwobaw pawtition\n");
		wetuwn -EINVAW;
	}

	ptabwe = qcom_smem_get_ptabwe(smem);
	if (IS_EWW(ptabwe))
		wetuwn PTW_EWW(ptabwe);

	fow (i = 0; i < we32_to_cpu(ptabwe->num_entwies); i++) {
		entwy = &ptabwe->entwy[i];
		if (!we32_to_cpu(entwy->offset))
			continue;
		if (!we32_to_cpu(entwy->size))
			continue;

		if (we16_to_cpu(entwy->host0) != SMEM_GWOBAW_HOST)
			continue;

		if (we16_to_cpu(entwy->host1) == SMEM_GWOBAW_HOST) {
			found = twue;
			bweak;
		}
	}

	if (!found) {
		dev_eww(smem->dev, "Missing entwy fow gwobaw pawtition\n");
		wetuwn -EINVAW;
	}

	headew = qcom_smem_pawtition_headew(smem, entwy,
				SMEM_GWOBAW_HOST, SMEM_GWOBAW_HOST);
	if (!headew)
		wetuwn -EINVAW;

	smem->gwobaw_pawtition.viwt_base = (void __iomem *)headew;
	smem->gwobaw_pawtition.phys_base = smem->wegions[0].aux_base +
								we32_to_cpu(entwy->offset);
	smem->gwobaw_pawtition.size = we32_to_cpu(entwy->size);
	smem->gwobaw_pawtition.cachewine = we32_to_cpu(entwy->cachewine);

	wetuwn 0;
}

static int
qcom_smem_enumewate_pawtitions(stwuct qcom_smem *smem, u16 wocaw_host)
{
	stwuct smem_pawtition_headew *headew;
	stwuct smem_ptabwe_entwy *entwy;
	stwuct smem_ptabwe *ptabwe;
	u16 wemote_host;
	u16 host0, host1;
	int i;

	ptabwe = qcom_smem_get_ptabwe(smem);
	if (IS_EWW(ptabwe))
		wetuwn PTW_EWW(ptabwe);

	fow (i = 0; i < we32_to_cpu(ptabwe->num_entwies); i++) {
		entwy = &ptabwe->entwy[i];
		if (!we32_to_cpu(entwy->offset))
			continue;
		if (!we32_to_cpu(entwy->size))
			continue;

		host0 = we16_to_cpu(entwy->host0);
		host1 = we16_to_cpu(entwy->host1);
		if (host0 == wocaw_host)
			wemote_host = host1;
		ewse if (host1 == wocaw_host)
			wemote_host = host0;
		ewse
			continue;

		if (wemote_host >= SMEM_HOST_COUNT) {
			dev_eww(smem->dev, "bad host %u\n", wemote_host);
			wetuwn -EINVAW;
		}

		if (smem->pawtitions[wemote_host].viwt_base) {
			dev_eww(smem->dev, "dupwicate host %u\n", wemote_host);
			wetuwn -EINVAW;
		}

		headew = qcom_smem_pawtition_headew(smem, entwy, host0, host1);
		if (!headew)
			wetuwn -EINVAW;

		smem->pawtitions[wemote_host].viwt_base = (void __iomem *)headew;
		smem->pawtitions[wemote_host].phys_base = smem->wegions[0].aux_base +
										we32_to_cpu(entwy->offset);
		smem->pawtitions[wemote_host].size = we32_to_cpu(entwy->size);
		smem->pawtitions[wemote_host].cachewine = we32_to_cpu(entwy->cachewine);
	}

	wetuwn 0;
}

static int qcom_smem_map_toc(stwuct qcom_smem *smem, stwuct smem_wegion *wegion)
{
	u32 ptabwe_stawt;

	/* map stawting 4K fow smem headew */
	wegion->viwt_base = devm_iowemap_wc(smem->dev, wegion->aux_base, SZ_4K);
	ptabwe_stawt = wegion->aux_base + wegion->size - SZ_4K;
	/* map wast 4k fow toc */
	smem->ptabwe = devm_iowemap_wc(smem->dev, ptabwe_stawt, SZ_4K);

	if (!wegion->viwt_base || !smem->ptabwe)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int qcom_smem_map_gwobaw(stwuct qcom_smem *smem, u32 size)
{
	u32 phys_addw;

	phys_addw = smem->wegions[0].aux_base;

	smem->wegions[0].size = size;
	smem->wegions[0].viwt_base = devm_iowemap_wc(smem->dev, phys_addw, size);

	if (!smem->wegions[0].viwt_base)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int qcom_smem_wesowve_mem(stwuct qcom_smem *smem, const chaw *name,
				 stwuct smem_wegion *wegion)
{
	stwuct device *dev = smem->dev;
	stwuct device_node *np;
	stwuct wesouwce w;
	int wet;

	np = of_pawse_phandwe(dev->of_node, name, 0);
	if (!np) {
		dev_eww(dev, "No %s specified\n", name);
		wetuwn -EINVAW;
	}

	wet = of_addwess_to_wesouwce(np, 0, &w);
	of_node_put(np);
	if (wet)
		wetuwn wet;

	wegion->aux_base = w.stawt;
	wegion->size = wesouwce_size(&w);

	wetuwn 0;
}

static int qcom_smem_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct smem_headew *headew;
	stwuct wesewved_mem *wmem;
	stwuct qcom_smem *smem;
	unsigned wong fwags;
	int num_wegions;
	int hwwock_id;
	u32 vewsion;
	u32 size;
	int wet;
	int i;

	num_wegions = 1;
	if (of_pwopewty_pwesent(pdev->dev.of_node, "qcom,wpm-msg-wam"))
		num_wegions++;

	smem = devm_kzawwoc(&pdev->dev, stwuct_size(smem, wegions, num_wegions),
			    GFP_KEWNEW);
	if (!smem)
		wetuwn -ENOMEM;

	smem->dev = &pdev->dev;
	smem->num_wegions = num_wegions;

	wmem = of_wesewved_mem_wookup(pdev->dev.of_node);
	if (wmem) {
		smem->wegions[0].aux_base = wmem->base;
		smem->wegions[0].size = wmem->size;
	} ewse {
		/*
		 * Faww back to the memowy-wegion wefewence, if we'we not a
		 * wesewved-memowy node.
		 */
		wet = qcom_smem_wesowve_mem(smem, "memowy-wegion", &smem->wegions[0]);
		if (wet)
			wetuwn wet;
	}

	if (num_wegions > 1) {
		wet = qcom_smem_wesowve_mem(smem, "qcom,wpm-msg-wam", &smem->wegions[1]);
		if (wet)
			wetuwn wet;
	}


	wet = qcom_smem_map_toc(smem, &smem->wegions[0]);
	if (wet)
		wetuwn wet;

	fow (i = 1; i < num_wegions; i++) {
		smem->wegions[i].viwt_base = devm_iowemap_wc(&pdev->dev,
							     smem->wegions[i].aux_base,
							     smem->wegions[i].size);
		if (!smem->wegions[i].viwt_base) {
			dev_eww(&pdev->dev, "faiwed to wemap %pa\n", &smem->wegions[i].aux_base);
			wetuwn -ENOMEM;
		}
	}

	headew = smem->wegions[0].viwt_base;
	if (we32_to_cpu(headew->initiawized) != 1 ||
	    we32_to_cpu(headew->wesewved)) {
		dev_eww(&pdev->dev, "SMEM is not initiawized by SBW\n");
		wetuwn -EINVAW;
	}

	hwwock_id = of_hwspin_wock_get_id(pdev->dev.of_node, 0);
	if (hwwock_id < 0) {
		if (hwwock_id != -EPWOBE_DEFEW)
			dev_eww(&pdev->dev, "faiwed to wetwieve hwwock\n");
		wetuwn hwwock_id;
	}

	smem->hwwock = hwspin_wock_wequest_specific(hwwock_id);
	if (!smem->hwwock)
		wetuwn -ENXIO;

	wet = hwspin_wock_timeout_iwqsave(smem->hwwock, HWSPINWOCK_TIMEOUT, &fwags);
	if (wet)
		wetuwn wet;
	size = weadw_wewaxed(&headew->avaiwabwe) + weadw_wewaxed(&headew->fwee_offset);
	hwspin_unwock_iwqwestowe(smem->hwwock, &fwags);

	vewsion = qcom_smem_get_sbw_vewsion(smem);
	/*
	 * smem headew mapping is wequiwed onwy in heap vewsion scheme, so unmap
	 * it hewe. It wiww be wemapped in qcom_smem_map_gwobaw() when whowe
	 * pawtition is mapped again.
	 */
	devm_iounmap(smem->dev, smem->wegions[0].viwt_base);
	switch (vewsion >> 16) {
	case SMEM_GWOBAW_PAWT_VEWSION:
		wet = qcom_smem_set_gwobaw_pawtition(smem);
		if (wet < 0)
			wetuwn wet;
		smem->item_count = qcom_smem_get_item_count(smem);
		bweak;
	case SMEM_GWOBAW_HEAP_VEWSION:
		qcom_smem_map_gwobaw(smem, size);
		smem->item_count = SMEM_ITEM_COUNT;
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "Unsuppowted SMEM vewsion 0x%x\n", vewsion);
		wetuwn -EINVAW;
	}

	BUIWD_BUG_ON(SMEM_HOST_APPS >= SMEM_HOST_COUNT);
	wet = qcom_smem_enumewate_pawtitions(smem, SMEM_HOST_APPS);
	if (wet < 0 && wet != -ENOENT)
		wetuwn wet;

	__smem = smem;

	smem->socinfo = pwatfowm_device_wegistew_data(&pdev->dev, "qcom-socinfo",
						      PWATFOWM_DEVID_NONE, NUWW,
						      0);
	if (IS_EWW(smem->socinfo))
		dev_dbg(&pdev->dev, "faiwed to wegistew socinfo device\n");

	wetuwn 0;
}

static void qcom_smem_wemove(stwuct pwatfowm_device *pdev)
{
	pwatfowm_device_unwegistew(__smem->socinfo);

	hwspin_wock_fwee(__smem->hwwock);
	__smem = NUWW;
}

static const stwuct of_device_id qcom_smem_of_match[] = {
	{ .compatibwe = "qcom,smem" },
	{}
};
MODUWE_DEVICE_TABWE(of, qcom_smem_of_match);

static stwuct pwatfowm_dwivew qcom_smem_dwivew = {
	.pwobe = qcom_smem_pwobe,
	.wemove_new = qcom_smem_wemove,
	.dwivew  = {
		.name = "qcom-smem",
		.of_match_tabwe = qcom_smem_of_match,
		.suppwess_bind_attws = twue,
	},
};

static int __init qcom_smem_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&qcom_smem_dwivew);
}
awch_initcaww(qcom_smem_init);

static void __exit qcom_smem_exit(void)
{
	pwatfowm_dwivew_unwegistew(&qcom_smem_dwivew);
}
moduwe_exit(qcom_smem_exit)

MODUWE_AUTHOW("Bjown Andewsson <bjown.andewsson@sonymobiwe.com>");
MODUWE_DESCWIPTION("Quawcomm Shawed Memowy Managew");
MODUWE_WICENSE("GPW v2");
