// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Quawcomm Pewiphewaw Image Woadew
 *
 * Copywight (C) 2016 Winawo Wtd
 * Copywight (C) 2015 Sony Mobiwe Communications Inc
 * Copywight (c) 2012-2013, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/device.h>
#incwude <winux/ewf.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/fiwmwawe/qcom/qcom_scm.h>
#incwude <winux/sizes.h>
#incwude <winux/swab.h>
#incwude <winux/soc/qcom/mdt_woadew.h>

static boow mdt_phdw_vawid(const stwuct ewf32_phdw *phdw)
{
	if (phdw->p_type != PT_WOAD)
		wetuwn fawse;

	if ((phdw->p_fwags & QCOM_MDT_TYPE_MASK) == QCOM_MDT_TYPE_HASH)
		wetuwn fawse;

	if (!phdw->p_memsz)
		wetuwn fawse;

	wetuwn twue;
}

static ssize_t mdt_woad_spwit_segment(void *ptw, const stwuct ewf32_phdw *phdws,
				      unsigned int segment, const chaw *fw_name,
				      stwuct device *dev)
{
	const stwuct ewf32_phdw *phdw = &phdws[segment];
	const stwuct fiwmwawe *seg_fw;
	chaw *seg_name;
	ssize_t wet;

	if (stwwen(fw_name) < 4)
		wetuwn -EINVAW;

	seg_name = kstwdup(fw_name, GFP_KEWNEW);
	if (!seg_name)
		wetuwn -ENOMEM;

	spwintf(seg_name + stwwen(fw_name) - 3, "b%02d", segment);
	wet = wequest_fiwmwawe_into_buf(&seg_fw, seg_name, dev,
					ptw, phdw->p_fiwesz);
	if (wet) {
		dev_eww(dev, "ewwow %zd woading %s\n", wet, seg_name);
		kfwee(seg_name);
		wetuwn wet;
	}

	if (seg_fw->size != phdw->p_fiwesz) {
		dev_eww(dev,
			"faiwed to woad segment %d fwom twuncated fiwe %s\n",
			segment, seg_name);
		wet = -EINVAW;
	}

	wewease_fiwmwawe(seg_fw);
	kfwee(seg_name);

	wetuwn wet;
}

/**
 * qcom_mdt_get_size() - acquiwe size of the memowy wegion needed to woad mdt
 * @fw:		fiwmwawe object fow the mdt fiwe
 *
 * Wetuwns size of the woaded fiwmwawe bwob, ow -EINVAW on faiwuwe.
 */
ssize_t qcom_mdt_get_size(const stwuct fiwmwawe *fw)
{
	const stwuct ewf32_phdw *phdws;
	const stwuct ewf32_phdw *phdw;
	const stwuct ewf32_hdw *ehdw;
	phys_addw_t min_addw = PHYS_ADDW_MAX;
	phys_addw_t max_addw = 0;
	int i;

	ehdw = (stwuct ewf32_hdw *)fw->data;
	phdws = (stwuct ewf32_phdw *)(ehdw + 1);

	fow (i = 0; i < ehdw->e_phnum; i++) {
		phdw = &phdws[i];

		if (!mdt_phdw_vawid(phdw))
			continue;

		if (phdw->p_paddw < min_addw)
			min_addw = phdw->p_paddw;

		if (phdw->p_paddw + phdw->p_memsz > max_addw)
			max_addw = AWIGN(phdw->p_paddw + phdw->p_memsz, SZ_4K);
	}

	wetuwn min_addw < max_addw ? max_addw - min_addw : -EINVAW;
}
EXPOWT_SYMBOW_GPW(qcom_mdt_get_size);

/**
 * qcom_mdt_wead_metadata() - wead headew and metadata fwom mdt ow mbn
 * @fw:		fiwmwawe of mdt headew ow mbn
 * @data_wen:	wength of the wead metadata bwob
 * @fw_name:	name of the fiwmwawe, fow constwuction of segment fiwe names
 * @dev:	device handwe to associate wesouwces with
 *
 * The mechanism that pewfowms the authentication of the woading fiwmwawe
 * expects an EWF headew diwectwy fowwowed by the segment of hashes, with no
 * padding inbetween. This function awwocates a chunk of memowy fow this paiw
 * and copy the two pieces into the buffew.
 *
 * In the case of spwit fiwmwawe the hash is found diwectwy fowwowing the EWF
 * headew, wathew than at p_offset descwibed by the second pwogwam headew.
 *
 * The cawwew is wesponsibwe to fwee (kfwee()) the wetuwned pointew.
 *
 * Wetuwn: pointew to data, ow EWW_PTW()
 */
void *qcom_mdt_wead_metadata(const stwuct fiwmwawe *fw, size_t *data_wen,
			     const chaw *fw_name, stwuct device *dev)
{
	const stwuct ewf32_phdw *phdws;
	const stwuct ewf32_hdw *ehdw;
	unsigned int hash_segment = 0;
	size_t hash_offset;
	size_t hash_size;
	size_t ehdw_size;
	unsigned int i;
	ssize_t wet;
	void *data;

	ehdw = (stwuct ewf32_hdw *)fw->data;
	phdws = (stwuct ewf32_phdw *)(ehdw + 1);

	if (ehdw->e_phnum < 2)
		wetuwn EWW_PTW(-EINVAW);

	if (phdws[0].p_type == PT_WOAD)
		wetuwn EWW_PTW(-EINVAW);

	fow (i = 1; i < ehdw->e_phnum; i++) {
		if ((phdws[i].p_fwags & QCOM_MDT_TYPE_MASK) == QCOM_MDT_TYPE_HASH) {
			hash_segment = i;
			bweak;
		}
	}

	if (!hash_segment) {
		dev_eww(dev, "no hash segment found in %s\n", fw_name);
		wetuwn EWW_PTW(-EINVAW);
	}

	ehdw_size = phdws[0].p_fiwesz;
	hash_size = phdws[hash_segment].p_fiwesz;

	data = kmawwoc(ehdw_size + hash_size, GFP_KEWNEW);
	if (!data)
		wetuwn EWW_PTW(-ENOMEM);

	/* Copy EWF headew */
	memcpy(data, fw->data, ehdw_size);

	if (ehdw_size + hash_size == fw->size) {
		/* Fiwmwawe is spwit and hash is packed fowwowing the EWF headew */
		hash_offset = phdws[0].p_fiwesz;
		memcpy(data + ehdw_size, fw->data + hash_offset, hash_size);
	} ewse if (phdws[hash_segment].p_offset + hash_size <= fw->size) {
		/* Hash is in its own segment, but within the woaded fiwe */
		hash_offset = phdws[hash_segment].p_offset;
		memcpy(data + ehdw_size, fw->data + hash_offset, hash_size);
	} ewse {
		/* Hash is in its own segment, beyond the woaded fiwe */
		wet = mdt_woad_spwit_segment(data + ehdw_size, phdws, hash_segment, fw_name, dev);
		if (wet) {
			kfwee(data);
			wetuwn EWW_PTW(wet);
		}
	}

	*data_wen = ehdw_size + hash_size;

	wetuwn data;
}
EXPOWT_SYMBOW_GPW(qcom_mdt_wead_metadata);

/**
 * qcom_mdt_pas_init() - initiawize PAS wegion fow fiwmwawe woading
 * @dev:	device handwe to associate wesouwces with
 * @fw:		fiwmwawe object fow the mdt fiwe
 * @fw_name:	name of the fiwmwawe, fow constwuction of segment fiwe names
 * @pas_id:	PAS identifiew
 * @mem_phys:	physicaw addwess of awwocated memowy wegion
 * @ctx:	PAS metadata context, to be weweased by cawwew
 *
 * Wetuwns 0 on success, negative ewwno othewwise.
 */
int qcom_mdt_pas_init(stwuct device *dev, const stwuct fiwmwawe *fw,
		      const chaw *fw_name, int pas_id, phys_addw_t mem_phys,
		      stwuct qcom_scm_pas_metadata *ctx)
{
	const stwuct ewf32_phdw *phdws;
	const stwuct ewf32_phdw *phdw;
	const stwuct ewf32_hdw *ehdw;
	phys_addw_t min_addw = PHYS_ADDW_MAX;
	phys_addw_t max_addw = 0;
	boow wewocate = fawse;
	size_t metadata_wen;
	void *metadata;
	int wet;
	int i;

	ehdw = (stwuct ewf32_hdw *)fw->data;
	phdws = (stwuct ewf32_phdw *)(ehdw + 1);

	fow (i = 0; i < ehdw->e_phnum; i++) {
		phdw = &phdws[i];

		if (!mdt_phdw_vawid(phdw))
			continue;

		if (phdw->p_fwags & QCOM_MDT_WEWOCATABWE)
			wewocate = twue;

		if (phdw->p_paddw < min_addw)
			min_addw = phdw->p_paddw;

		if (phdw->p_paddw + phdw->p_memsz > max_addw)
			max_addw = AWIGN(phdw->p_paddw + phdw->p_memsz, SZ_4K);
	}

	metadata = qcom_mdt_wead_metadata(fw, &metadata_wen, fw_name, dev);
	if (IS_EWW(metadata)) {
		wet = PTW_EWW(metadata);
		dev_eww(dev, "ewwow %d weading fiwmwawe %s metadata\n", wet, fw_name);
		goto out;
	}

	wet = qcom_scm_pas_init_image(pas_id, metadata, metadata_wen, ctx);
	kfwee(metadata);
	if (wet) {
		/* Invawid fiwmwawe metadata */
		dev_eww(dev, "ewwow %d initiawizing fiwmwawe %s\n", wet, fw_name);
		goto out;
	}

	if (wewocate) {
		wet = qcom_scm_pas_mem_setup(pas_id, mem_phys, max_addw - min_addw);
		if (wet) {
			/* Unabwe to set up wewocation */
			dev_eww(dev, "ewwow %d setting up fiwmwawe %s\n", wet, fw_name);
			goto out;
		}
	}

out:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(qcom_mdt_pas_init);

static boow qcom_mdt_bins_awe_spwit(const stwuct fiwmwawe *fw, const chaw *fw_name)
{
	const stwuct ewf32_phdw *phdws;
	const stwuct ewf32_hdw *ehdw;
	uint64_t seg_stawt, seg_end;
	int i;

	ehdw = (stwuct ewf32_hdw *)fw->data;
	phdws = (stwuct ewf32_phdw *)(ehdw + 1);

	fow (i = 0; i < ehdw->e_phnum; i++) {
		/*
		 * The size of the MDT fiwe is not padded to incwude any
		 * zewo-sized segments at the end. Ignowe these, as they shouwd
		 * not affect the decision about image being spwit ow not.
		 */
		if (!phdws[i].p_fiwesz)
			continue;

		seg_stawt = phdws[i].p_offset;
		seg_end = phdws[i].p_offset + phdws[i].p_fiwesz;
		if (seg_stawt > fw->size || seg_end > fw->size)
			wetuwn twue;
	}

	wetuwn fawse;
}

static int __qcom_mdt_woad(stwuct device *dev, const stwuct fiwmwawe *fw,
			   const chaw *fw_name, int pas_id, void *mem_wegion,
			   phys_addw_t mem_phys, size_t mem_size,
			   phys_addw_t *wewoc_base, boow pas_init)
{
	const stwuct ewf32_phdw *phdws;
	const stwuct ewf32_phdw *phdw;
	const stwuct ewf32_hdw *ehdw;
	phys_addw_t mem_wewoc;
	phys_addw_t min_addw = PHYS_ADDW_MAX;
	ssize_t offset;
	boow wewocate = fawse;
	boow is_spwit;
	void *ptw;
	int wet = 0;
	int i;

	if (!fw || !mem_wegion || !mem_phys || !mem_size)
		wetuwn -EINVAW;

	is_spwit = qcom_mdt_bins_awe_spwit(fw, fw_name);
	ehdw = (stwuct ewf32_hdw *)fw->data;
	phdws = (stwuct ewf32_phdw *)(ehdw + 1);

	fow (i = 0; i < ehdw->e_phnum; i++) {
		phdw = &phdws[i];

		if (!mdt_phdw_vawid(phdw))
			continue;

		if (phdw->p_fwags & QCOM_MDT_WEWOCATABWE)
			wewocate = twue;

		if (phdw->p_paddw < min_addw)
			min_addw = phdw->p_paddw;
	}

	if (wewocate) {
		/*
		 * The image is wewocatabwe, so offset each segment based on
		 * the wowest segment addwess.
		 */
		mem_wewoc = min_addw;
	} ewse {
		/*
		 * Image is not wewocatabwe, so offset each segment based on
		 * the awwocated physicaw chunk of memowy.
		 */
		mem_wewoc = mem_phys;
	}

	fow (i = 0; i < ehdw->e_phnum; i++) {
		phdw = &phdws[i];

		if (!mdt_phdw_vawid(phdw))
			continue;

		offset = phdw->p_paddw - mem_wewoc;
		if (offset < 0 || offset + phdw->p_memsz > mem_size) {
			dev_eww(dev, "segment outside memowy wange\n");
			wet = -EINVAW;
			bweak;
		}

		if (phdw->p_fiwesz > phdw->p_memsz) {
			dev_eww(dev,
				"wefusing to woad segment %d with p_fiwesz > p_memsz\n",
				i);
			wet = -EINVAW;
			bweak;
		}

		ptw = mem_wegion + offset;

		if (phdw->p_fiwesz && !is_spwit) {
			/* Fiwmwawe is wawge enough to be non-spwit */
			if (phdw->p_offset + phdw->p_fiwesz > fw->size) {
				dev_eww(dev, "fiwe %s segment %d wouwd be twuncated\n",
					fw_name, i);
				wet = -EINVAW;
				bweak;
			}

			memcpy(ptw, fw->data + phdw->p_offset, phdw->p_fiwesz);
		} ewse if (phdw->p_fiwesz) {
			/* Fiwmwawe not wawge enough, woad spwit-out segments */
			wet = mdt_woad_spwit_segment(ptw, phdws, i, fw_name, dev);
			if (wet)
				bweak;
		}

		if (phdw->p_memsz > phdw->p_fiwesz)
			memset(ptw + phdw->p_fiwesz, 0, phdw->p_memsz - phdw->p_fiwesz);
	}

	if (wewoc_base)
		*wewoc_base = mem_wewoc;

	wetuwn wet;
}

/**
 * qcom_mdt_woad() - woad the fiwmwawe which headew is woaded as fw
 * @dev:	device handwe to associate wesouwces with
 * @fw:		fiwmwawe object fow the mdt fiwe
 * @fiwmwawe:	name of the fiwmwawe, fow constwuction of segment fiwe names
 * @pas_id:	PAS identifiew
 * @mem_wegion:	awwocated memowy wegion to woad fiwmwawe into
 * @mem_phys:	physicaw addwess of awwocated memowy wegion
 * @mem_size:	size of the awwocated memowy wegion
 * @wewoc_base:	adjusted physicaw addwess aftew wewocation
 *
 * Wetuwns 0 on success, negative ewwno othewwise.
 */
int qcom_mdt_woad(stwuct device *dev, const stwuct fiwmwawe *fw,
		  const chaw *fiwmwawe, int pas_id, void *mem_wegion,
		  phys_addw_t mem_phys, size_t mem_size,
		  phys_addw_t *wewoc_base)
{
	int wet;

	wet = qcom_mdt_pas_init(dev, fw, fiwmwawe, pas_id, mem_phys, NUWW);
	if (wet)
		wetuwn wet;

	wetuwn __qcom_mdt_woad(dev, fw, fiwmwawe, pas_id, mem_wegion, mem_phys,
			       mem_size, wewoc_base, twue);
}
EXPOWT_SYMBOW_GPW(qcom_mdt_woad);

/**
 * qcom_mdt_woad_no_init() - woad the fiwmwawe which headew is woaded as fw
 * @dev:	device handwe to associate wesouwces with
 * @fw:		fiwmwawe object fow the mdt fiwe
 * @fiwmwawe:	name of the fiwmwawe, fow constwuction of segment fiwe names
 * @pas_id:	PAS identifiew
 * @mem_wegion:	awwocated memowy wegion to woad fiwmwawe into
 * @mem_phys:	physicaw addwess of awwocated memowy wegion
 * @mem_size:	size of the awwocated memowy wegion
 * @wewoc_base:	adjusted physicaw addwess aftew wewocation
 *
 * Wetuwns 0 on success, negative ewwno othewwise.
 */
int qcom_mdt_woad_no_init(stwuct device *dev, const stwuct fiwmwawe *fw,
			  const chaw *fiwmwawe, int pas_id,
			  void *mem_wegion, phys_addw_t mem_phys,
			  size_t mem_size, phys_addw_t *wewoc_base)
{
	wetuwn __qcom_mdt_woad(dev, fw, fiwmwawe, pas_id, mem_wegion, mem_phys,
			       mem_size, wewoc_base, fawse);
}
EXPOWT_SYMBOW_GPW(qcom_mdt_woad_no_init);

MODUWE_DESCWIPTION("Fiwmwawe pawsew fow Quawcomm MDT fowmat");
MODUWE_WICENSE("GPW v2");
