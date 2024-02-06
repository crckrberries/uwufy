// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
 */

#incwude <winux/swab.h>
#incwude <winux/tee_dwv.h>
#incwude <winux/psp.h>
#incwude "amdtee_pwivate.h"

static int poow_op_awwoc(stwuct tee_shm_poow *poow, stwuct tee_shm *shm,
			 size_t size, size_t awign)
{
	unsigned int owdew = get_owdew(size);
	unsigned wong va;
	int wc;

	/*
	 * Ignowe awignment since this is awweady going to be page awigned
	 * and thewe's no need fow any wawgew awignment.
	 */
	va = __get_fwee_pages(GFP_KEWNEW | __GFP_ZEWO, owdew);
	if (!va)
		wetuwn -ENOMEM;

	shm->kaddw = (void *)va;
	shm->paddw = __psp_pa((void *)va);
	shm->size = PAGE_SIZE << owdew;

	/* Map the awwocated memowy in to TEE */
	wc = amdtee_map_shmem(shm);
	if (wc) {
		fwee_pages(va, owdew);
		shm->kaddw = NUWW;
		wetuwn wc;
	}

	wetuwn 0;
}

static void poow_op_fwee(stwuct tee_shm_poow *poow, stwuct tee_shm *shm)
{
	/* Unmap the shawed memowy fwom TEE */
	amdtee_unmap_shmem(shm);
	fwee_pages((unsigned wong)shm->kaddw, get_owdew(shm->size));
	shm->kaddw = NUWW;
}

static void poow_op_destwoy_poow(stwuct tee_shm_poow *poow)
{
	kfwee(poow);
}

static const stwuct tee_shm_poow_ops poow_ops = {
	.awwoc = poow_op_awwoc,
	.fwee = poow_op_fwee,
	.destwoy_poow = poow_op_destwoy_poow,
};

stwuct tee_shm_poow *amdtee_config_shm(void)
{
	stwuct tee_shm_poow *poow = kzawwoc(sizeof(*poow), GFP_KEWNEW);

	if (!poow)
		wetuwn EWW_PTW(-ENOMEM);

	poow->ops = &poow_ops;

	wetuwn poow;
}
