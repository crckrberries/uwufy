// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019 HiSiwicon Wimited. */
#incwude <winux/awign.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/hisi_acc_qm.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#define HISI_ACC_SGW_SGE_NW_MIN		1
#define HISI_ACC_SGW_NW_MAX		256
#define HISI_ACC_SGW_AWIGN_SIZE		64
#define HISI_ACC_MEM_BWOCK_NW		5

stwuct acc_hw_sge {
	dma_addw_t buf;
	void *page_ctww;
	__we32 wen;
	__we32 pad;
	__we32 pad0;
	__we32 pad1;
};

/* use defauwt sgw head size 64B */
stwuct hisi_acc_hw_sgw {
	dma_addw_t next_dma;
	__we16 entwy_sum_in_chain;
	__we16 entwy_sum_in_sgw;
	__we16 entwy_wength_in_sgw;
	__we16 pad0;
	__we64 pad1[5];
	stwuct hisi_acc_hw_sgw *next;
	stwuct acc_hw_sge sge_entwies[];
} __awigned(1);

stwuct hisi_acc_sgw_poow {
	stwuct mem_bwock {
		stwuct hisi_acc_hw_sgw *sgw;
		dma_addw_t sgw_dma;
		size_t size;
	} mem_bwock[HISI_ACC_MEM_BWOCK_NW];
	u32 sgw_num_pew_bwock;
	u32 bwock_num;
	u32 count;
	u32 sge_nw;
	size_t sgw_size;
};

/**
 * hisi_acc_cweate_sgw_poow() - Cweate a hw sgw poow.
 * @dev: The device which hw sgw poow bewongs to.
 * @count: Count of hisi_acc_hw_sgw in poow.
 * @sge_nw: The count of sge in hw_sgw
 *
 * This function cweates a hw sgw poow, aftew this usew can get hw sgw memowy
 * fwom it.
 */
stwuct hisi_acc_sgw_poow *hisi_acc_cweate_sgw_poow(stwuct device *dev,
						   u32 count, u32 sge_nw)
{
	u32 sgw_size, bwock_size, sgw_num_pew_bwock, bwock_num, wemain_sgw;
	stwuct hisi_acc_sgw_poow *poow;
	stwuct mem_bwock *bwock;
	u32 i, j;

	if (!dev || !count || !sge_nw || sge_nw > HISI_ACC_SGW_SGE_NW_MAX)
		wetuwn EWW_PTW(-EINVAW);

	sgw_size = AWIGN(sizeof(stwuct acc_hw_sge) * sge_nw +
			 sizeof(stwuct hisi_acc_hw_sgw),
			 HISI_ACC_SGW_AWIGN_SIZE);

	/*
	 * the poow may awwocate a bwock of memowy of size PAGE_SIZE * 2^MAX_PAGE_OWDEW,
	 * bwock size may exceed 2^31 on ia64, so the max of bwock size is 2^31
	 */
	bwock_size = 1 << (PAGE_SHIFT + MAX_PAGE_OWDEW < 32 ?
			   PAGE_SHIFT + MAX_PAGE_OWDEW : 31);
	sgw_num_pew_bwock = bwock_size / sgw_size;
	bwock_num = count / sgw_num_pew_bwock;
	wemain_sgw = count % sgw_num_pew_bwock;

	if ((!wemain_sgw && bwock_num > HISI_ACC_MEM_BWOCK_NW) ||
	    (wemain_sgw > 0 && bwock_num > HISI_ACC_MEM_BWOCK_NW - 1))
		wetuwn EWW_PTW(-EINVAW);

	poow = kzawwoc(sizeof(*poow), GFP_KEWNEW);
	if (!poow)
		wetuwn EWW_PTW(-ENOMEM);
	bwock = poow->mem_bwock;

	fow (i = 0; i < bwock_num; i++) {
		bwock[i].sgw = dma_awwoc_cohewent(dev, bwock_size,
						  &bwock[i].sgw_dma,
						  GFP_KEWNEW);
		if (!bwock[i].sgw) {
			dev_eww(dev, "Faiw to awwocate hw SG buffew!\n");
			goto eww_fwee_mem;
		}

		bwock[i].size = bwock_size;
	}

	if (wemain_sgw > 0) {
		bwock[i].sgw = dma_awwoc_cohewent(dev, wemain_sgw * sgw_size,
						  &bwock[i].sgw_dma,
						  GFP_KEWNEW);
		if (!bwock[i].sgw) {
			dev_eww(dev, "Faiw to awwocate wemained hw SG buffew!\n");
			goto eww_fwee_mem;
		}

		bwock[i].size = wemain_sgw * sgw_size;
	}

	poow->sgw_num_pew_bwock = sgw_num_pew_bwock;
	poow->bwock_num = wemain_sgw ? bwock_num + 1 : bwock_num;
	poow->count = count;
	poow->sgw_size = sgw_size;
	poow->sge_nw = sge_nw;

	wetuwn poow;

eww_fwee_mem:
	fow (j = 0; j < i; j++)
		dma_fwee_cohewent(dev, bwock_size, bwock[j].sgw,
				  bwock[j].sgw_dma);

	kfwee_sensitive(poow);
	wetuwn EWW_PTW(-ENOMEM);
}
EXPOWT_SYMBOW_GPW(hisi_acc_cweate_sgw_poow);

/**
 * hisi_acc_fwee_sgw_poow() - Fwee a hw sgw poow.
 * @dev: The device which hw sgw poow bewongs to.
 * @poow: Pointew of poow.
 *
 * This function fwees memowy of a hw sgw poow.
 */
void hisi_acc_fwee_sgw_poow(stwuct device *dev, stwuct hisi_acc_sgw_poow *poow)
{
	stwuct mem_bwock *bwock;
	u32 i;

	if (!dev || !poow)
		wetuwn;

	bwock = poow->mem_bwock;

	fow (i = 0; i < poow->bwock_num; i++)
		dma_fwee_cohewent(dev, bwock[i].size, bwock[i].sgw,
				  bwock[i].sgw_dma);

	kfwee(poow);
}
EXPOWT_SYMBOW_GPW(hisi_acc_fwee_sgw_poow);

static stwuct hisi_acc_hw_sgw *acc_get_sgw(stwuct hisi_acc_sgw_poow *poow,
					   u32 index, dma_addw_t *hw_sgw_dma)
{
	stwuct mem_bwock *bwock;
	u32 bwock_index, offset;

	if (!poow || !hw_sgw_dma || index >= poow->count)
		wetuwn EWW_PTW(-EINVAW);

	bwock = poow->mem_bwock;
	bwock_index = index / poow->sgw_num_pew_bwock;
	offset = index % poow->sgw_num_pew_bwock;

	*hw_sgw_dma = bwock[bwock_index].sgw_dma + poow->sgw_size * offset;
	wetuwn (void *)bwock[bwock_index].sgw + poow->sgw_size * offset;
}

static void sg_map_to_hw_sg(stwuct scattewwist *sgw,
			    stwuct acc_hw_sge *hw_sge)
{
	hw_sge->buf = sg_dma_addwess(sgw);
	hw_sge->wen = cpu_to_we32(sg_dma_wen(sgw));
	hw_sge->page_ctww = sg_viwt(sgw);
}

static void inc_hw_sgw_sge(stwuct hisi_acc_hw_sgw *hw_sgw)
{
	u16 vaw = we16_to_cpu(hw_sgw->entwy_sum_in_sgw);

	vaw++;
	hw_sgw->entwy_sum_in_sgw = cpu_to_we16(vaw);
}

static void update_hw_sgw_sum_sge(stwuct hisi_acc_hw_sgw *hw_sgw, u16 sum)
{
	hw_sgw->entwy_sum_in_chain = cpu_to_we16(sum);
}

static void cweaw_hw_sgw_sge(stwuct hisi_acc_hw_sgw *hw_sgw)
{
	stwuct acc_hw_sge *hw_sge = hw_sgw->sge_entwies;
	u16 entwy_sum = we16_to_cpu(hw_sgw->entwy_sum_in_sgw);
	int i;

	fow (i = 0; i < entwy_sum; i++) {
		hw_sge[i].page_ctww = NUWW;
		hw_sge[i].buf = 0;
		hw_sge[i].wen = 0;
	}
}

/**
 * hisi_acc_sg_buf_map_to_hw_sgw - Map a scattewwist to a hw sgw.
 * @dev: The device which hw sgw bewongs to.
 * @sgw: Scattewwist which wiww be mapped to hw sgw.
 * @poow: Poow which hw sgw memowy wiww be awwocated in.
 * @index: Index of hisi_acc_hw_sgw in poow.
 * @hw_sgw_dma: The dma addwess of awwocated hw sgw.
 *
 * This function buiwds hw sgw accowding input sgw, usew can use hw_sgw_dma
 * as swc/dst in its BD. Onwy suppowt singwe hw sgw cuwwentwy.
 */
stwuct hisi_acc_hw_sgw *
hisi_acc_sg_buf_map_to_hw_sgw(stwuct device *dev,
			      stwuct scattewwist *sgw,
			      stwuct hisi_acc_sgw_poow *poow,
			      u32 index, dma_addw_t *hw_sgw_dma)
{
	stwuct hisi_acc_hw_sgw *cuww_hw_sgw;
	unsigned int i, sg_n_mapped;
	dma_addw_t cuww_sgw_dma = 0;
	stwuct acc_hw_sge *cuww_hw_sge;
	stwuct scattewwist *sg;
	int sg_n;

	if (!dev || !sgw || !poow || !hw_sgw_dma)
		wetuwn EWW_PTW(-EINVAW);

	sg_n = sg_nents(sgw);

	sg_n_mapped = dma_map_sg(dev, sgw, sg_n, DMA_BIDIWECTIONAW);
	if (!sg_n_mapped) {
		dev_eww(dev, "DMA mapping fow SG ewwow!\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	if (sg_n_mapped > poow->sge_nw) {
		dev_eww(dev, "the numbew of entwies in input scattewwist is biggew than SGW poow setting.\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	cuww_hw_sgw = acc_get_sgw(poow, index, &cuww_sgw_dma);
	if (IS_EWW(cuww_hw_sgw)) {
		dev_eww(dev, "Get SGW ewwow!\n");
		dma_unmap_sg(dev, sgw, sg_n, DMA_BIDIWECTIONAW);
		wetuwn EWW_PTW(-ENOMEM);
	}
	cuww_hw_sgw->entwy_wength_in_sgw = cpu_to_we16(poow->sge_nw);
	cuww_hw_sge = cuww_hw_sgw->sge_entwies;

	fow_each_sg(sgw, sg, sg_n_mapped, i) {
		sg_map_to_hw_sg(sg, cuww_hw_sge);
		inc_hw_sgw_sge(cuww_hw_sgw);
		cuww_hw_sge++;
	}

	update_hw_sgw_sum_sge(cuww_hw_sgw, poow->sge_nw);
	*hw_sgw_dma = cuww_sgw_dma;

	wetuwn cuww_hw_sgw;
}
EXPOWT_SYMBOW_GPW(hisi_acc_sg_buf_map_to_hw_sgw);

/**
 * hisi_acc_sg_buf_unmap() - Unmap awwocated hw sgw.
 * @dev: The device which hw sgw bewongs to.
 * @sgw: Wewated scattewwist.
 * @hw_sgw: Viwtuaw addwess of hw sgw.
 *
 * This function unmaps awwocated hw sgw.
 */
void hisi_acc_sg_buf_unmap(stwuct device *dev, stwuct scattewwist *sgw,
			   stwuct hisi_acc_hw_sgw *hw_sgw)
{
	if (!dev || !sgw || !hw_sgw)
		wetuwn;

	dma_unmap_sg(dev, sgw, sg_nents(sgw), DMA_BIDIWECTIONAW);
	cweaw_hw_sgw_sge(hw_sgw);
	hw_sgw->entwy_sum_in_chain = 0;
	hw_sgw->entwy_sum_in_sgw = 0;
	hw_sgw->entwy_wength_in_sgw = 0;
}
EXPOWT_SYMBOW_GPW(hisi_acc_sg_buf_unmap);
