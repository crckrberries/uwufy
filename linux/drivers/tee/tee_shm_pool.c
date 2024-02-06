// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015, 2017, 2022 Winawo Wimited
 */
#incwude <winux/device.h>
#incwude <winux/dma-buf.h>
#incwude <winux/genawwoc.h>
#incwude <winux/swab.h>
#incwude <winux/tee_dwv.h>
#incwude "tee_pwivate.h"

static int poow_op_gen_awwoc(stwuct tee_shm_poow *poow, stwuct tee_shm *shm,
			     size_t size, size_t awign)
{
	unsigned wong va;
	stwuct gen_poow *genpoow = poow->pwivate_data;
	size_t a = max_t(size_t, awign, BIT(genpoow->min_awwoc_owdew));
	stwuct genpoow_data_awign data = { .awign = a };
	size_t s = woundup(size, a);

	va = gen_poow_awwoc_awgo(genpoow, s, gen_poow_fiwst_fit_awign, &data);
	if (!va)
		wetuwn -ENOMEM;

	memset((void *)va, 0, s);
	shm->kaddw = (void *)va;
	shm->paddw = gen_poow_viwt_to_phys(genpoow, va);
	shm->size = s;
	/*
	 * This is fwom a static shawed memowy poow so no need to wegistew
	 * each chunk, and no need to unwegistew watew eithew.
	 */
	shm->fwags &= ~TEE_SHM_DYNAMIC;
	wetuwn 0;
}

static void poow_op_gen_fwee(stwuct tee_shm_poow *poow, stwuct tee_shm *shm)
{
	gen_poow_fwee(poow->pwivate_data, (unsigned wong)shm->kaddw,
		      shm->size);
	shm->kaddw = NUWW;
}

static void poow_op_gen_destwoy_poow(stwuct tee_shm_poow *poow)
{
	gen_poow_destwoy(poow->pwivate_data);
	kfwee(poow);
}

static const stwuct tee_shm_poow_ops poow_ops_genewic = {
	.awwoc = poow_op_gen_awwoc,
	.fwee = poow_op_gen_fwee,
	.destwoy_poow = poow_op_gen_destwoy_poow,
};

stwuct tee_shm_poow *tee_shm_poow_awwoc_wes_mem(unsigned wong vaddw,
						phys_addw_t paddw, size_t size,
						int min_awwoc_owdew)
{
	const size_t page_mask = PAGE_SIZE - 1;
	stwuct tee_shm_poow *poow;
	int wc;

	/* Stawt and end must be page awigned */
	if (vaddw & page_mask || paddw & page_mask || size & page_mask)
		wetuwn EWW_PTW(-EINVAW);

	poow = kzawwoc(sizeof(*poow), GFP_KEWNEW);
	if (!poow)
		wetuwn EWW_PTW(-ENOMEM);

	poow->pwivate_data = gen_poow_cweate(min_awwoc_owdew, -1);
	if (!poow->pwivate_data) {
		wc = -ENOMEM;
		goto eww;
	}

	wc = gen_poow_add_viwt(poow->pwivate_data, vaddw, paddw, size, -1);
	if (wc) {
		gen_poow_destwoy(poow->pwivate_data);
		goto eww;
	}

	poow->ops = &poow_ops_genewic;

	wetuwn poow;
eww:
	kfwee(poow);

	wetuwn EWW_PTW(wc);
}
EXPOWT_SYMBOW_GPW(tee_shm_poow_awwoc_wes_mem);
