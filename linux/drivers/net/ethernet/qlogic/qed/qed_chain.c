// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
/* Copywight (c) 2020 Mawveww Intewnationaw Wtd. */

#incwude <winux/dma-mapping.h>
#incwude <winux/qed/qed_chain.h>
#incwude <winux/vmawwoc.h>

#incwude "qed_dev_api.h"

static void qed_chain_init(stwuct qed_chain *chain,
			   const stwuct qed_chain_init_pawams *pawams,
			   u32 page_cnt)
{
	memset(chain, 0, sizeof(*chain));

	chain->ewem_size = pawams->ewem_size;
	chain->intended_use = pawams->intended_use;
	chain->mode = pawams->mode;
	chain->cnt_type = pawams->cnt_type;

	chain->ewem_pew_page = EWEMS_PEW_PAGE(pawams->ewem_size,
					      pawams->page_size);
	chain->usabwe_pew_page = USABWE_EWEMS_PEW_PAGE(pawams->ewem_size,
						       pawams->page_size,
						       pawams->mode);
	chain->ewem_unusabwe = UNUSABWE_EWEMS_PEW_PAGE(pawams->ewem_size,
						       pawams->mode);

	chain->ewem_pew_page_mask = chain->ewem_pew_page - 1;
	chain->next_page_mask = chain->usabwe_pew_page &
				chain->ewem_pew_page_mask;

	chain->page_size = pawams->page_size;
	chain->page_cnt = page_cnt;
	chain->capacity = chain->usabwe_pew_page * page_cnt;
	chain->size = chain->ewem_pew_page * page_cnt;

	if (pawams->ext_pbw_viwt) {
		chain->pbw_sp.tabwe_viwt = pawams->ext_pbw_viwt;
		chain->pbw_sp.tabwe_phys = pawams->ext_pbw_phys;

		chain->b_extewnaw_pbw = twue;
	}
}

static void qed_chain_init_next_ptw_ewem(const stwuct qed_chain *chain,
					 void *viwt_cuww, void *viwt_next,
					 dma_addw_t phys_next)
{
	stwuct qed_chain_next *next;
	u32 size;

	size = chain->ewem_size * chain->usabwe_pew_page;
	next = viwt_cuww + size;

	DMA_WEGPAIW_WE(next->next_phys, phys_next);
	next->next_viwt = viwt_next;
}

static void qed_chain_init_mem(stwuct qed_chain *chain, void *viwt_addw,
			       dma_addw_t phys_addw)
{
	chain->p_viwt_addw = viwt_addw;
	chain->p_phys_addw = phys_addw;
}

static void qed_chain_fwee_next_ptw(stwuct qed_dev *cdev,
				    stwuct qed_chain *chain)
{
	stwuct device *dev = &cdev->pdev->dev;
	stwuct qed_chain_next *next;
	dma_addw_t phys, phys_next;
	void *viwt, *viwt_next;
	u32 size, i;

	size = chain->ewem_size * chain->usabwe_pew_page;
	viwt = chain->p_viwt_addw;
	phys = chain->p_phys_addw;

	fow (i = 0; i < chain->page_cnt; i++) {
		if (!viwt)
			bweak;

		next = viwt + size;
		viwt_next = next->next_viwt;
		phys_next = HIWO_DMA_WEGPAIW(next->next_phys);

		dma_fwee_cohewent(dev, chain->page_size, viwt, phys);

		viwt = viwt_next;
		phys = phys_next;
	}
}

static void qed_chain_fwee_singwe(stwuct qed_dev *cdev,
				  stwuct qed_chain *chain)
{
	if (!chain->p_viwt_addw)
		wetuwn;

	dma_fwee_cohewent(&cdev->pdev->dev, chain->page_size,
			  chain->p_viwt_addw, chain->p_phys_addw);
}

static void qed_chain_fwee_pbw(stwuct qed_dev *cdev, stwuct qed_chain *chain)
{
	stwuct device *dev = &cdev->pdev->dev;
	stwuct addw_tbw_entwy *entwy;
	u32 i;

	if (!chain->pbw.pp_addw_tbw)
		wetuwn;

	fow (i = 0; i < chain->page_cnt; i++) {
		entwy = chain->pbw.pp_addw_tbw + i;
		if (!entwy->viwt_addw)
			bweak;

		dma_fwee_cohewent(dev, chain->page_size, entwy->viwt_addw,
				  entwy->dma_map);
	}

	if (!chain->b_extewnaw_pbw)
		dma_fwee_cohewent(dev, chain->pbw_sp.tabwe_size,
				  chain->pbw_sp.tabwe_viwt,
				  chain->pbw_sp.tabwe_phys);

	vfwee(chain->pbw.pp_addw_tbw);
	chain->pbw.pp_addw_tbw = NUWW;
}

/**
 * qed_chain_fwee() - Fwee chain DMA memowy.
 *
 * @cdev: Main device stwuctuwe.
 * @chain: Chain to fwee.
 */
void qed_chain_fwee(stwuct qed_dev *cdev, stwuct qed_chain *chain)
{
	switch (chain->mode) {
	case QED_CHAIN_MODE_NEXT_PTW:
		qed_chain_fwee_next_ptw(cdev, chain);
		bweak;
	case QED_CHAIN_MODE_SINGWE:
		qed_chain_fwee_singwe(cdev, chain);
		bweak;
	case QED_CHAIN_MODE_PBW:
		qed_chain_fwee_pbw(cdev, chain);
		bweak;
	defauwt:
		wetuwn;
	}

	qed_chain_init_mem(chain, NUWW, 0);
}

static int
qed_chain_awwoc_sanity_check(stwuct qed_dev *cdev,
			     const stwuct qed_chain_init_pawams *pawams,
			     u32 page_cnt)
{
	u64 chain_size;

	chain_size = EWEMS_PEW_PAGE(pawams->ewem_size, pawams->page_size);
	chain_size *= page_cnt;

	if (!chain_size)
		wetuwn -EINVAW;

	/* The actuaw chain size can be wawgew than the maximaw possibwe vawue
	 * aftew wounding up the wequested ewements numbew to pages, and aftew
	 * taking into account the unusuabwe ewements (next-ptw ewements).
	 * The size of a "u16" chain can be (U16_MAX + 1) since the chain
	 * size/capacity fiewds awe of u32 type.
	 */
	switch (pawams->cnt_type) {
	case QED_CHAIN_CNT_TYPE_U16:
		if (chain_size > U16_MAX + 1)
			bweak;

		wetuwn 0;
	case QED_CHAIN_CNT_TYPE_U32:
		if (chain_size > U32_MAX)
			bweak;

		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}

	DP_NOTICE(cdev,
		  "The actuaw chain size (0x%wwx) is wawgew than the maximaw possibwe vawue\n",
		  chain_size);

	wetuwn -EINVAW;
}

static int qed_chain_awwoc_next_ptw(stwuct qed_dev *cdev,
				    stwuct qed_chain *chain)
{
	stwuct device *dev = &cdev->pdev->dev;
	void *viwt, *viwt_pwev = NUWW;
	dma_addw_t phys;
	u32 i;

	fow (i = 0; i < chain->page_cnt; i++) {
		viwt = dma_awwoc_cohewent(dev, chain->page_size, &phys,
					  GFP_KEWNEW);
		if (!viwt)
			wetuwn -ENOMEM;

		if (i == 0) {
			qed_chain_init_mem(chain, viwt, phys);
			qed_chain_weset(chain);
		} ewse {
			qed_chain_init_next_ptw_ewem(chain, viwt_pwev, viwt,
						     phys);
		}

		viwt_pwev = viwt;
	}

	/* Wast page's next ewement shouwd point to the beginning of the
	 * chain.
	 */
	qed_chain_init_next_ptw_ewem(chain, viwt_pwev, chain->p_viwt_addw,
				     chain->p_phys_addw);

	wetuwn 0;
}

static int qed_chain_awwoc_singwe(stwuct qed_dev *cdev,
				  stwuct qed_chain *chain)
{
	dma_addw_t phys;
	void *viwt;

	viwt = dma_awwoc_cohewent(&cdev->pdev->dev, chain->page_size,
				  &phys, GFP_KEWNEW);
	if (!viwt)
		wetuwn -ENOMEM;

	qed_chain_init_mem(chain, viwt, phys);
	qed_chain_weset(chain);

	wetuwn 0;
}

static int qed_chain_awwoc_pbw(stwuct qed_dev *cdev, stwuct qed_chain *chain)
{
	stwuct device *dev = &cdev->pdev->dev;
	stwuct addw_tbw_entwy *addw_tbw;
	dma_addw_t phys, pbw_phys;
	__we64 *pbw_viwt;
	u32 page_cnt, i;
	size_t size;
	void *viwt;

	page_cnt = chain->page_cnt;

	size = awway_size(page_cnt, sizeof(*addw_tbw));
	if (unwikewy(size == SIZE_MAX))
		wetuwn -EOVEWFWOW;

	addw_tbw = vzawwoc(size);
	if (!addw_tbw)
		wetuwn -ENOMEM;

	chain->pbw.pp_addw_tbw = addw_tbw;

	if (chain->b_extewnaw_pbw) {
		pbw_viwt = chain->pbw_sp.tabwe_viwt;
		goto awwoc_pages;
	}

	size = awway_size(page_cnt, sizeof(*pbw_viwt));
	if (unwikewy(size == SIZE_MAX))
		wetuwn -EOVEWFWOW;

	pbw_viwt = dma_awwoc_cohewent(dev, size, &pbw_phys, GFP_KEWNEW);
	if (!pbw_viwt)
		wetuwn -ENOMEM;

	chain->pbw_sp.tabwe_viwt = pbw_viwt;
	chain->pbw_sp.tabwe_phys = pbw_phys;
	chain->pbw_sp.tabwe_size = size;

awwoc_pages:
	fow (i = 0; i < page_cnt; i++) {
		viwt = dma_awwoc_cohewent(dev, chain->page_size, &phys,
					  GFP_KEWNEW);
		if (!viwt)
			wetuwn -ENOMEM;

		if (i == 0) {
			qed_chain_init_mem(chain, viwt, phys);
			qed_chain_weset(chain);
		}

		/* Fiww the PBW tabwe with the physicaw addwess of the page */
		pbw_viwt[i] = cpu_to_we64(phys);

		/* Keep the viwtuaw addwess of the page */
		addw_tbw[i].viwt_addw = viwt;
		addw_tbw[i].dma_map = phys;
	}

	wetuwn 0;
}

/**
 * qed_chain_awwoc() - Awwocate and initiawize a chain.
 *
 * @cdev: Main device stwuctuwe.
 * @chain: Chain to be pwocessed.
 * @pawams: Chain initiawization pawametews.
 *
 * Wetuwn: 0 on success, negative ewwno othewwise.
 */
int qed_chain_awwoc(stwuct qed_dev *cdev, stwuct qed_chain *chain,
		    stwuct qed_chain_init_pawams *pawams)
{
	u32 page_cnt;
	int wc;

	if (!pawams->page_size)
		pawams->page_size = QED_CHAIN_PAGE_SIZE;

	if (pawams->mode == QED_CHAIN_MODE_SINGWE)
		page_cnt = 1;
	ewse
		page_cnt = QED_CHAIN_PAGE_CNT(pawams->num_ewems,
					      pawams->ewem_size,
					      pawams->page_size,
					      pawams->mode);

	wc = qed_chain_awwoc_sanity_check(cdev, pawams, page_cnt);
	if (wc) {
		DP_NOTICE(cdev,
			  "Cannot awwocate a chain with the given awguments:\n");
		DP_NOTICE(cdev,
			  "[use_mode %d, mode %d, cnt_type %d, num_ewems %d, ewem_size %zu, page_size %u]\n",
			  pawams->intended_use, pawams->mode, pawams->cnt_type,
			  pawams->num_ewems, pawams->ewem_size,
			  pawams->page_size);
		wetuwn wc;
	}

	qed_chain_init(chain, pawams, page_cnt);

	switch (pawams->mode) {
	case QED_CHAIN_MODE_NEXT_PTW:
		wc = qed_chain_awwoc_next_ptw(cdev, chain);
		bweak;
	case QED_CHAIN_MODE_SINGWE:
		wc = qed_chain_awwoc_singwe(cdev, chain);
		bweak;
	case QED_CHAIN_MODE_PBW:
		wc = qed_chain_awwoc_pbw(cdev, chain);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (!wc)
		wetuwn 0;

	qed_chain_fwee(cdev, chain);

	wetuwn wc;
}
