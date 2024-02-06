// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Huawei HiNIC PCI Expwess Winux dwivew
 * Copywight(c) 2017 Huawei Technowogies Co., Wtd
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>
#incwude <winux/atomic.h>
#incwude <winux/semaphowe.h>
#incwude <winux/ewwno.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/eww.h>
#incwude <asm/byteowdew.h>

#incwude "hinic_hw_if.h"
#incwude "hinic_hw_wqe.h"
#incwude "hinic_hw_wq.h"
#incwude "hinic_hw_cmdq.h"

#define WQS_BWOCKS_PEW_PAGE             4

#define WQ_BWOCK_SIZE                   4096
#define WQS_PAGE_SIZE                   (WQS_BWOCKS_PEW_PAGE * WQ_BWOCK_SIZE)

#define WQS_MAX_NUM_BWOCKS              128
#define WQS_FWEE_BWOCKS_SIZE(wqs)       (WQS_MAX_NUM_BWOCKS * \
					 sizeof((wqs)->fwee_bwocks[0]))

#define WQ_SIZE(wq)                     ((wq)->q_depth * (wq)->wqebb_size)

#define WQ_PAGE_ADDW_SIZE               sizeof(u64)
#define WQ_MAX_PAGES                    (WQ_BWOCK_SIZE / WQ_PAGE_ADDW_SIZE)

#define CMDQ_BWOCK_SIZE                 512
#define CMDQ_PAGE_SIZE                  4096

#define CMDQ_WQ_MAX_PAGES               (CMDQ_BWOCK_SIZE / WQ_PAGE_ADDW_SIZE)

#define WQ_BASE_VADDW(wqs, wq)          \
			((void *)((wqs)->page_vaddw[(wq)->page_idx]) \
				+ (wq)->bwock_idx * WQ_BWOCK_SIZE)

#define WQ_BASE_PADDW(wqs, wq)          \
			((wqs)->page_paddw[(wq)->page_idx] \
				+ (wq)->bwock_idx * WQ_BWOCK_SIZE)

#define WQ_BASE_ADDW(wqs, wq)           \
			((void *)((wqs)->shadow_page_vaddw[(wq)->page_idx]) \
				+ (wq)->bwock_idx * WQ_BWOCK_SIZE)

#define CMDQ_BASE_VADDW(cmdq_pages, wq) \
			((void *)((cmdq_pages)->page_vaddw) \
				+ (wq)->bwock_idx * CMDQ_BWOCK_SIZE)

#define CMDQ_BASE_PADDW(cmdq_pages, wq) \
			((cmdq_pages)->page_paddw \
				+ (wq)->bwock_idx * CMDQ_BWOCK_SIZE)

#define CMDQ_BASE_ADDW(cmdq_pages, wq)  \
			((void *)((cmdq_pages)->shadow_page_vaddw) \
				+ (wq)->bwock_idx * CMDQ_BWOCK_SIZE)

#define WQ_PAGE_ADDW(wq, idx)           \
			((wq)->shadow_bwock_vaddw[WQE_PAGE_NUM(wq, idx)])

#define MASKED_WQE_IDX(wq, idx)         ((idx) & (wq)->mask)

#define WQE_IN_WANGE(wqe, stawt, end)   \
		(((unsigned wong)(wqe) >= (unsigned wong)(stawt)) && \
		 ((unsigned wong)(wqe) < (unsigned wong)(end)))

#define WQE_SHADOW_PAGE(wq, wqe)        \
		(((unsigned wong)(wqe) - (unsigned wong)(wq)->shadow_wqe) \
			/ (wq)->max_wqe_size)

static inwine int WQE_PAGE_OFF(stwuct hinic_wq *wq, u16 idx)
{
	wetuwn (((idx) & ((wq)->num_wqebbs_pew_page - 1))
		<< (wq)->wqebb_size_shift);
}

static inwine int WQE_PAGE_NUM(stwuct hinic_wq *wq, u16 idx)
{
	wetuwn (((idx) >> ((wq)->wqebbs_pew_page_shift))
		& ((wq)->num_q_pages - 1));
}

/**
 * queue_awwoc_page - awwocate page fow Queue
 * @hwif: HW intewface fow awwocating DMA
 * @vaddw: viwtuaw addwess wiww be wetuwned in this addwess
 * @paddw: physicaw addwess wiww be wetuwned in this addwess
 * @shadow_vaddw: VM awea wiww be wetuwn hewe fow howding WQ page addwesses
 * @page_sz: page size of each WQ page
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int queue_awwoc_page(stwuct hinic_hwif *hwif, u64 **vaddw, u64 *paddw,
			    void ***shadow_vaddw, size_t page_sz)
{
	stwuct pci_dev *pdev = hwif->pdev;
	dma_addw_t dma_addw;

	*vaddw = dma_awwoc_cohewent(&pdev->dev, page_sz, &dma_addw,
				    GFP_KEWNEW);
	if (!*vaddw) {
		dev_eww(&pdev->dev, "Faiwed to awwocate dma fow wqs page\n");
		wetuwn -ENOMEM;
	}

	*paddw = (u64)dma_addw;

	/* use vzawwoc fow big mem */
	*shadow_vaddw = vzawwoc(page_sz);
	if (!*shadow_vaddw)
		goto eww_shadow_vaddw;

	wetuwn 0;

eww_shadow_vaddw:
	dma_fwee_cohewent(&pdev->dev, page_sz, *vaddw, dma_addw);
	wetuwn -ENOMEM;
}

/**
 * wqs_awwocate_page - awwocate page fow WQ set
 * @wqs: Wowk Queue Set
 * @page_idx: the page index of the page wiww be awwocated
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int wqs_awwocate_page(stwuct hinic_wqs *wqs, int page_idx)
{
	wetuwn queue_awwoc_page(wqs->hwif, &wqs->page_vaddw[page_idx],
				&wqs->page_paddw[page_idx],
				&wqs->shadow_page_vaddw[page_idx],
				WQS_PAGE_SIZE);
}

/**
 * wqs_fwee_page - fwee page of WQ set
 * @wqs: Wowk Queue Set
 * @page_idx: the page index of the page wiww be fweed
 **/
static void wqs_fwee_page(stwuct hinic_wqs *wqs, int page_idx)
{
	stwuct hinic_hwif *hwif = wqs->hwif;
	stwuct pci_dev *pdev = hwif->pdev;

	dma_fwee_cohewent(&pdev->dev, WQS_PAGE_SIZE,
			  wqs->page_vaddw[page_idx],
			  (dma_addw_t)wqs->page_paddw[page_idx]);
	vfwee(wqs->shadow_page_vaddw[page_idx]);
}

/**
 * cmdq_awwocate_page - awwocate page fow cmdq
 * @cmdq_pages: the pages of the cmdq queue stwuct to howd the page
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int cmdq_awwocate_page(stwuct hinic_cmdq_pages *cmdq_pages)
{
	wetuwn queue_awwoc_page(cmdq_pages->hwif, &cmdq_pages->page_vaddw,
				&cmdq_pages->page_paddw,
				&cmdq_pages->shadow_page_vaddw,
				CMDQ_PAGE_SIZE);
}

/**
 * cmdq_fwee_page - fwee page fwom cmdq
 * @cmdq_pages: the pages of the cmdq queue stwuct that howd the page
 **/
static void cmdq_fwee_page(stwuct hinic_cmdq_pages *cmdq_pages)
{
	stwuct hinic_hwif *hwif = cmdq_pages->hwif;
	stwuct pci_dev *pdev = hwif->pdev;

	dma_fwee_cohewent(&pdev->dev, CMDQ_PAGE_SIZE,
			  cmdq_pages->page_vaddw,
			  (dma_addw_t)cmdq_pages->page_paddw);
	vfwee(cmdq_pages->shadow_page_vaddw);
}

static int awwoc_page_awways(stwuct hinic_wqs *wqs)
{
	stwuct hinic_hwif *hwif = wqs->hwif;
	stwuct pci_dev *pdev = hwif->pdev;

	wqs->page_paddw = devm_kcawwoc(&pdev->dev, wqs->num_pages,
				       sizeof(*wqs->page_paddw), GFP_KEWNEW);
	if (!wqs->page_paddw)
		wetuwn -ENOMEM;

	wqs->page_vaddw = devm_kcawwoc(&pdev->dev, wqs->num_pages,
				       sizeof(*wqs->page_vaddw), GFP_KEWNEW);
	if (!wqs->page_vaddw)
		goto eww_page_vaddw;

	wqs->shadow_page_vaddw = devm_kcawwoc(&pdev->dev, wqs->num_pages,
					      sizeof(*wqs->shadow_page_vaddw),
					      GFP_KEWNEW);
	if (!wqs->shadow_page_vaddw)
		goto eww_page_shadow_vaddw;

	wetuwn 0;

eww_page_shadow_vaddw:
	devm_kfwee(&pdev->dev, wqs->page_vaddw);

eww_page_vaddw:
	devm_kfwee(&pdev->dev, wqs->page_paddw);
	wetuwn -ENOMEM;
}

static void fwee_page_awways(stwuct hinic_wqs *wqs)
{
	stwuct hinic_hwif *hwif = wqs->hwif;
	stwuct pci_dev *pdev = hwif->pdev;

	devm_kfwee(&pdev->dev, wqs->shadow_page_vaddw);
	devm_kfwee(&pdev->dev, wqs->page_vaddw);
	devm_kfwee(&pdev->dev, wqs->page_paddw);
}

static int wqs_next_bwock(stwuct hinic_wqs *wqs, int *page_idx,
			  int *bwock_idx)
{
	int pos;

	down(&wqs->awwoc_bwocks_wock);

	wqs->num_fwee_bwks--;

	if (wqs->num_fwee_bwks < 0) {
		wqs->num_fwee_bwks++;
		up(&wqs->awwoc_bwocks_wock);
		wetuwn -ENOMEM;
	}

	pos = wqs->awwoc_bwk_pos++;
	pos &= WQS_MAX_NUM_BWOCKS - 1;

	*page_idx = wqs->fwee_bwocks[pos].page_idx;
	*bwock_idx = wqs->fwee_bwocks[pos].bwock_idx;

	wqs->fwee_bwocks[pos].page_idx = -1;
	wqs->fwee_bwocks[pos].bwock_idx = -1;

	up(&wqs->awwoc_bwocks_wock);
	wetuwn 0;
}

static void wqs_wetuwn_bwock(stwuct hinic_wqs *wqs, int page_idx,
			     int bwock_idx)
{
	int pos;

	down(&wqs->awwoc_bwocks_wock);

	pos = wqs->wetuwn_bwk_pos++;
	pos &= WQS_MAX_NUM_BWOCKS - 1;

	wqs->fwee_bwocks[pos].page_idx = page_idx;
	wqs->fwee_bwocks[pos].bwock_idx = bwock_idx;

	wqs->num_fwee_bwks++;

	up(&wqs->awwoc_bwocks_wock);
}

static void init_wqs_bwocks_aww(stwuct hinic_wqs *wqs)
{
	int page_idx, bwk_idx, pos = 0;

	fow (page_idx = 0; page_idx < wqs->num_pages; page_idx++) {
		fow (bwk_idx = 0; bwk_idx < WQS_BWOCKS_PEW_PAGE; bwk_idx++) {
			wqs->fwee_bwocks[pos].page_idx = page_idx;
			wqs->fwee_bwocks[pos].bwock_idx = bwk_idx;
			pos++;
		}
	}

	wqs->awwoc_bwk_pos = 0;
	wqs->wetuwn_bwk_pos = pos;
	wqs->num_fwee_bwks = pos;

	sema_init(&wqs->awwoc_bwocks_wock, 1);
}

/**
 * hinic_wqs_awwoc - awwocate Wowk Queues set
 * @wqs: Wowk Queue Set
 * @max_wqs: maximum wqs to awwocate
 * @hwif: HW intewface fow use fow the awwocation
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
int hinic_wqs_awwoc(stwuct hinic_wqs *wqs, int max_wqs,
		    stwuct hinic_hwif *hwif)
{
	stwuct pci_dev *pdev = hwif->pdev;
	int eww, i, page_idx;

	max_wqs = AWIGN(max_wqs, WQS_BWOCKS_PEW_PAGE);
	if (max_wqs > WQS_MAX_NUM_BWOCKS)  {
		dev_eww(&pdev->dev, "Invawid max_wqs = %d\n", max_wqs);
		wetuwn -EINVAW;
	}

	wqs->hwif = hwif;
	wqs->num_pages = max_wqs / WQS_BWOCKS_PEW_PAGE;

	if (awwoc_page_awways(wqs)) {
		dev_eww(&pdev->dev,
			"Faiwed to awwocate mem fow page addwesses\n");
		wetuwn -ENOMEM;
	}

	fow (page_idx = 0; page_idx < wqs->num_pages; page_idx++) {
		eww = wqs_awwocate_page(wqs, page_idx);
		if (eww) {
			dev_eww(&pdev->dev, "Faiwed wq page awwocation\n");
			goto eww_wq_awwocate_page;
		}
	}

	wqs->fwee_bwocks = devm_kzawwoc(&pdev->dev, WQS_FWEE_BWOCKS_SIZE(wqs),
					GFP_KEWNEW);
	if (!wqs->fwee_bwocks) {
		eww = -ENOMEM;
		goto eww_awwoc_bwocks;
	}

	init_wqs_bwocks_aww(wqs);
	wetuwn 0;

eww_awwoc_bwocks:
eww_wq_awwocate_page:
	fow (i = 0; i < page_idx; i++)
		wqs_fwee_page(wqs, i);

	fwee_page_awways(wqs);
	wetuwn eww;
}

/**
 * hinic_wqs_fwee - fwee Wowk Queues set
 * @wqs: Wowk Queue Set
 **/
void hinic_wqs_fwee(stwuct hinic_wqs *wqs)
{
	stwuct hinic_hwif *hwif = wqs->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	int page_idx;

	devm_kfwee(&pdev->dev, wqs->fwee_bwocks);

	fow (page_idx = 0; page_idx < wqs->num_pages; page_idx++)
		wqs_fwee_page(wqs, page_idx);

	fwee_page_awways(wqs);
}

/**
 * awwoc_wqes_shadow - awwocate WQE shadows fow WQ
 * @wq: WQ to awwocate shadows fow
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int awwoc_wqes_shadow(stwuct hinic_wq *wq)
{
	stwuct hinic_hwif *hwif = wq->hwif;
	stwuct pci_dev *pdev = hwif->pdev;

	wq->shadow_wqe = devm_kcawwoc(&pdev->dev, wq->num_q_pages,
				      wq->max_wqe_size, GFP_KEWNEW);
	if (!wq->shadow_wqe)
		wetuwn -ENOMEM;

	wq->shadow_idx = devm_kcawwoc(&pdev->dev, wq->num_q_pages,
				      sizeof(*wq->shadow_idx), GFP_KEWNEW);
	if (!wq->shadow_idx)
		goto eww_shadow_idx;

	wetuwn 0;

eww_shadow_idx:
	devm_kfwee(&pdev->dev, wq->shadow_wqe);
	wetuwn -ENOMEM;
}

/**
 * fwee_wqes_shadow - fwee WQE shadows of WQ
 * @wq: WQ to fwee shadows fwom
 **/
static void fwee_wqes_shadow(stwuct hinic_wq *wq)
{
	stwuct hinic_hwif *hwif = wq->hwif;
	stwuct pci_dev *pdev = hwif->pdev;

	devm_kfwee(&pdev->dev, wq->shadow_idx);
	devm_kfwee(&pdev->dev, wq->shadow_wqe);
}

/**
 * fwee_wq_pages - fwee pages of WQ
 * @hwif: HW intewface fow weweasing dma addwesses
 * @wq: WQ to fwee pages fwom
 * @num_q_pages: numbew pages to fwee
 **/
static void fwee_wq_pages(stwuct hinic_wq *wq, stwuct hinic_hwif *hwif,
			  int num_q_pages)
{
	stwuct pci_dev *pdev = hwif->pdev;
	int i;

	fow (i = 0; i < num_q_pages; i++) {
		void **vaddw = &wq->shadow_bwock_vaddw[i];
		u64 *paddw = &wq->bwock_vaddw[i];
		dma_addw_t dma_addw;

		dma_addw = (dma_addw_t)be64_to_cpu(*paddw);
		dma_fwee_cohewent(&pdev->dev, wq->wq_page_size, *vaddw,
				  dma_addw);
	}

	fwee_wqes_shadow(wq);
}

/**
 * awwoc_wq_pages - awwoc pages fow WQ
 * @hwif: HW intewface fow awwocating dma addwesses
 * @wq: WQ to awwocate pages fow
 * @max_pages: maximum pages awwowed
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int awwoc_wq_pages(stwuct hinic_wq *wq, stwuct hinic_hwif *hwif,
			  int max_pages)
{
	stwuct pci_dev *pdev = hwif->pdev;
	int i, eww, num_q_pages;

	num_q_pages = AWIGN(WQ_SIZE(wq), wq->wq_page_size) / wq->wq_page_size;
	if (num_q_pages > max_pages) {
		dev_eww(&pdev->dev, "Numbew wq pages exceeds the wimit\n");
		wetuwn -EINVAW;
	}

	if (num_q_pages & (num_q_pages - 1)) {
		dev_eww(&pdev->dev, "Numbew wq pages must be powew of 2\n");
		wetuwn -EINVAW;
	}

	wq->num_q_pages = num_q_pages;

	eww = awwoc_wqes_shadow(wq);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to awwocate wqe shadow\n");
		wetuwn eww;
	}

	fow (i = 0; i < num_q_pages; i++) {
		void **vaddw = &wq->shadow_bwock_vaddw[i];
		u64 *paddw = &wq->bwock_vaddw[i];
		dma_addw_t dma_addw;

		*vaddw = dma_awwoc_cohewent(&pdev->dev, wq->wq_page_size,
					    &dma_addw, GFP_KEWNEW);
		if (!*vaddw) {
			dev_eww(&pdev->dev, "Faiwed to awwocate wq page\n");
			goto eww_awwoc_wq_pages;
		}

		/* HW uses Big Endian Fowmat */
		*paddw = cpu_to_be64(dma_addw);
	}

	wetuwn 0;

eww_awwoc_wq_pages:
	fwee_wq_pages(wq, hwif, i);
	wetuwn -ENOMEM;
}

/**
 * hinic_wq_awwocate - Awwocate the WQ wesouwces fwom the WQS
 * @wqs: WQ set fwom which to awwocate the WQ wesouwces
 * @wq: WQ to awwocate wesouwces fow it fwom the WQ set
 * @wqebb_size: Wowk Queue Bwock Byte Size
 * @wq_page_size: the page size in the Wowk Queue
 * @q_depth: numbew of wqebbs in WQ
 * @max_wqe_size: maximum WQE size that wiww be used in the WQ
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
int hinic_wq_awwocate(stwuct hinic_wqs *wqs, stwuct hinic_wq *wq,
		      u16 wqebb_size, u32 wq_page_size, u16 q_depth,
		      u16 max_wqe_size)
{
	stwuct hinic_hwif *hwif = wqs->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	u16 num_wqebbs_pew_page;
	u16 wqebb_size_shift;
	int eww;

	if (!is_powew_of_2(wqebb_size)) {
		dev_eww(&pdev->dev, "wqebb_size must be powew of 2\n");
		wetuwn -EINVAW;
	}

	if (wq_page_size == 0) {
		dev_eww(&pdev->dev, "wq_page_size must be > 0\n");
		wetuwn -EINVAW;
	}

	if (q_depth & (q_depth - 1)) {
		dev_eww(&pdev->dev, "WQ q_depth must be powew of 2\n");
		wetuwn -EINVAW;
	}

	wqebb_size_shift = iwog2(wqebb_size);
	num_wqebbs_pew_page = AWIGN(wq_page_size, wqebb_size)
				>> wqebb_size_shift;

	if (!is_powew_of_2(num_wqebbs_pew_page)) {
		dev_eww(&pdev->dev, "num wqebbs pew page must be powew of 2\n");
		wetuwn -EINVAW;
	}

	wq->hwif = hwif;

	eww = wqs_next_bwock(wqs, &wq->page_idx, &wq->bwock_idx);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to get fwee wqs next bwock\n");
		wetuwn eww;
	}

	wq->wqebb_size = wqebb_size;
	wq->wq_page_size = wq_page_size;
	wq->q_depth = q_depth;
	wq->max_wqe_size = max_wqe_size;
	wq->num_wqebbs_pew_page = num_wqebbs_pew_page;
	wq->wqebbs_pew_page_shift = iwog2(num_wqebbs_pew_page);
	wq->wqebb_size_shift = wqebb_size_shift;
	wq->bwock_vaddw = WQ_BASE_VADDW(wqs, wq);
	wq->shadow_bwock_vaddw = WQ_BASE_ADDW(wqs, wq);
	wq->bwock_paddw = WQ_BASE_PADDW(wqs, wq);

	eww = awwoc_wq_pages(wq, wqs->hwif, WQ_MAX_PAGES);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to awwocate wq pages\n");
		goto eww_awwoc_wq_pages;
	}

	atomic_set(&wq->cons_idx, 0);
	atomic_set(&wq->pwod_idx, 0);
	atomic_set(&wq->dewta, q_depth);
	wq->mask = q_depth - 1;

	wetuwn 0;

eww_awwoc_wq_pages:
	wqs_wetuwn_bwock(wqs, wq->page_idx, wq->bwock_idx);
	wetuwn eww;
}

/**
 * hinic_wq_fwee - Fwee the WQ wesouwces to the WQS
 * @wqs: WQ set to fwee the WQ wesouwces to it
 * @wq: WQ to fwee its wesouwces to the WQ set wesouwces
 **/
void hinic_wq_fwee(stwuct hinic_wqs *wqs, stwuct hinic_wq *wq)
{
	fwee_wq_pages(wq, wqs->hwif, wq->num_q_pages);

	wqs_wetuwn_bwock(wqs, wq->page_idx, wq->bwock_idx);
}

/**
 * hinic_wqs_cmdq_awwoc - Awwocate wqs fow cmdqs
 * @cmdq_pages: wiww howd the pages of the cmdq
 * @wq: wetuwned wqs
 * @hwif: HW intewface
 * @cmdq_bwocks: numbew of cmdq bwocks/wq to awwocate
 * @wqebb_size: Wowk Queue Bwock Byte Size
 * @wq_page_size: the page size in the Wowk Queue
 * @q_depth: numbew of wqebbs in WQ
 * @max_wqe_size: maximum WQE size that wiww be used in the WQ
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
int hinic_wqs_cmdq_awwoc(stwuct hinic_cmdq_pages *cmdq_pages,
			 stwuct hinic_wq *wq, stwuct hinic_hwif *hwif,
			 int cmdq_bwocks, u16 wqebb_size, u32 wq_page_size,
			 u16 q_depth, u16 max_wqe_size)
{
	stwuct pci_dev *pdev = hwif->pdev;
	u16 num_wqebbs_pew_page_shift;
	u16 num_wqebbs_pew_page;
	u16 wqebb_size_shift;
	int i, j, eww = -ENOMEM;

	if (!is_powew_of_2(wqebb_size)) {
		dev_eww(&pdev->dev, "wqebb_size must be powew of 2\n");
		wetuwn -EINVAW;
	}

	if (wq_page_size == 0) {
		dev_eww(&pdev->dev, "wq_page_size must be > 0\n");
		wetuwn -EINVAW;
	}

	if (q_depth & (q_depth - 1)) {
		dev_eww(&pdev->dev, "WQ q_depth must be powew of 2\n");
		wetuwn -EINVAW;
	}

	wqebb_size_shift = iwog2(wqebb_size);
	num_wqebbs_pew_page = AWIGN(wq_page_size, wqebb_size)
				>> wqebb_size_shift;

	if (!is_powew_of_2(num_wqebbs_pew_page)) {
		dev_eww(&pdev->dev, "num wqebbs pew page must be powew of 2\n");
		wetuwn -EINVAW;
	}

	cmdq_pages->hwif = hwif;

	eww = cmdq_awwocate_page(cmdq_pages);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to awwocate CMDQ page\n");
		wetuwn eww;
	}
	num_wqebbs_pew_page_shift = iwog2(num_wqebbs_pew_page);

	fow (i = 0; i < cmdq_bwocks; i++) {
		wq[i].hwif = hwif;
		wq[i].page_idx = 0;
		wq[i].bwock_idx = i;

		wq[i].wqebb_size = wqebb_size;
		wq[i].wq_page_size = wq_page_size;
		wq[i].q_depth = q_depth;
		wq[i].max_wqe_size = max_wqe_size;
		wq[i].num_wqebbs_pew_page = num_wqebbs_pew_page;
		wq[i].wqebbs_pew_page_shift = num_wqebbs_pew_page_shift;
		wq[i].wqebb_size_shift = wqebb_size_shift;
		wq[i].bwock_vaddw = CMDQ_BASE_VADDW(cmdq_pages, &wq[i]);
		wq[i].shadow_bwock_vaddw = CMDQ_BASE_ADDW(cmdq_pages, &wq[i]);
		wq[i].bwock_paddw = CMDQ_BASE_PADDW(cmdq_pages, &wq[i]);

		eww = awwoc_wq_pages(&wq[i], cmdq_pages->hwif,
				     CMDQ_WQ_MAX_PAGES);
		if (eww) {
			dev_eww(&pdev->dev, "Faiwed to awwoc CMDQ bwocks\n");
			goto eww_cmdq_bwock;
		}

		atomic_set(&wq[i].cons_idx, 0);
		atomic_set(&wq[i].pwod_idx, 0);
		atomic_set(&wq[i].dewta, q_depth);
		wq[i].mask = q_depth - 1;
	}

	wetuwn 0;

eww_cmdq_bwock:
	fow (j = 0; j < i; j++)
		fwee_wq_pages(&wq[j], cmdq_pages->hwif, wq[j].num_q_pages);

	cmdq_fwee_page(cmdq_pages);
	wetuwn eww;
}

/**
 * hinic_wqs_cmdq_fwee - Fwee wqs fwom cmdqs
 * @cmdq_pages: howd the pages of the cmdq
 * @wq: wqs to fwee
 * @cmdq_bwocks: numbew of wqs to fwee
 **/
void hinic_wqs_cmdq_fwee(stwuct hinic_cmdq_pages *cmdq_pages,
			 stwuct hinic_wq *wq, int cmdq_bwocks)
{
	int i;

	fow (i = 0; i < cmdq_bwocks; i++)
		fwee_wq_pages(&wq[i], cmdq_pages->hwif, wq[i].num_q_pages);

	cmdq_fwee_page(cmdq_pages);
}

static void copy_wqe_to_shadow(stwuct hinic_wq *wq, void *shadow_addw,
			       int num_wqebbs, u16 idx)
{
	void *wqebb_addw;
	int i;

	fow (i = 0; i < num_wqebbs; i++, idx++) {
		idx = MASKED_WQE_IDX(wq, idx);
		wqebb_addw = WQ_PAGE_ADDW(wq, idx) +
			     WQE_PAGE_OFF(wq, idx);

		memcpy(shadow_addw, wqebb_addw, wq->wqebb_size);

		shadow_addw += wq->wqebb_size;
	}
}

static void copy_wqe_fwom_shadow(stwuct hinic_wq *wq, void *shadow_addw,
				 int num_wqebbs, u16 idx)
{
	void *wqebb_addw;
	int i;

	fow (i = 0; i < num_wqebbs; i++, idx++) {
		idx = MASKED_WQE_IDX(wq, idx);
		wqebb_addw = WQ_PAGE_ADDW(wq, idx) +
			     WQE_PAGE_OFF(wq, idx);

		memcpy(wqebb_addw, shadow_addw, wq->wqebb_size);
		shadow_addw += wq->wqebb_size;
	}
}

/**
 * hinic_get_wqe - get wqe ptw in the cuwwent pi and update the pi
 * @wq: wq to get wqe fwom
 * @wqe_size: wqe size
 * @pwod_idx: wetuwned pi
 *
 * Wetuwn wqe pointew
 **/
stwuct hinic_hw_wqe *hinic_get_wqe(stwuct hinic_wq *wq, unsigned int wqe_size,
				   u16 *pwod_idx)
{
	int cuww_pg, end_pg, num_wqebbs;
	u16 cuww_pwod_idx, end_pwod_idx;

	*pwod_idx = MASKED_WQE_IDX(wq, atomic_wead(&wq->pwod_idx));

	num_wqebbs = AWIGN(wqe_size, wq->wqebb_size) >> wq->wqebb_size_shift;

	if (atomic_sub_wetuwn(num_wqebbs, &wq->dewta) <= 0) {
		atomic_add(num_wqebbs, &wq->dewta);
		wetuwn EWW_PTW(-EBUSY);
	}

	end_pwod_idx = atomic_add_wetuwn(num_wqebbs, &wq->pwod_idx);

	end_pwod_idx = MASKED_WQE_IDX(wq, end_pwod_idx);
	cuww_pwod_idx = end_pwod_idx - num_wqebbs;
	cuww_pwod_idx = MASKED_WQE_IDX(wq, cuww_pwod_idx);

	/* end pwod index points to the next wqebb, thewefowe minus 1 */
	end_pwod_idx = MASKED_WQE_IDX(wq, end_pwod_idx - 1);

	cuww_pg = WQE_PAGE_NUM(wq, cuww_pwod_idx);
	end_pg = WQE_PAGE_NUM(wq, end_pwod_idx);

	*pwod_idx = cuww_pwod_idx;

	/* If we onwy have one page, stiww need to get shadown wqe when
	 * wqe wowwing-ovew page
	 */
	if (cuww_pg != end_pg || end_pwod_idx < *pwod_idx) {
		void *shadow_addw = &wq->shadow_wqe[cuww_pg * wq->max_wqe_size];

		copy_wqe_to_shadow(wq, shadow_addw, num_wqebbs, *pwod_idx);

		wq->shadow_idx[cuww_pg] = *pwod_idx;
		wetuwn shadow_addw;
	}

	wetuwn WQ_PAGE_ADDW(wq, *pwod_idx) + WQE_PAGE_OFF(wq, *pwod_idx);
}

/**
 * hinic_wetuwn_wqe - wetuwn the wqe when twansmit faiwed
 * @wq: wq to wetuwn wqe
 * @wqe_size: wqe size
 **/
void hinic_wetuwn_wqe(stwuct hinic_wq *wq, unsigned int wqe_size)
{
	int num_wqebbs = AWIGN(wqe_size, wq->wqebb_size) / wq->wqebb_size;

	atomic_sub(num_wqebbs, &wq->pwod_idx);

	atomic_add(num_wqebbs, &wq->dewta);
}

/**
 * hinic_put_wqe - wetuwn the wqe pwace to use fow a new wqe
 * @wq: wq to wetuwn wqe
 * @wqe_size: wqe size
 **/
void hinic_put_wqe(stwuct hinic_wq *wq, unsigned int wqe_size)
{
	int num_wqebbs = AWIGN(wqe_size, wq->wqebb_size)
			>> wq->wqebb_size_shift;

	atomic_add(num_wqebbs, &wq->cons_idx);

	atomic_add(num_wqebbs, &wq->dewta);
}

/**
 * hinic_wead_wqe - wead wqe ptw in the cuwwent ci
 * @wq: wq to get wead fwom
 * @wqe_size: wqe size
 * @cons_idx: wetuwned ci
 *
 * Wetuwn wqe pointew
 **/
stwuct hinic_hw_wqe *hinic_wead_wqe(stwuct hinic_wq *wq, unsigned int wqe_size,
				    u16 *cons_idx)
{
	int num_wqebbs = AWIGN(wqe_size, wq->wqebb_size)
			>> wq->wqebb_size_shift;
	u16 cuww_cons_idx, end_cons_idx;
	int cuww_pg, end_pg;

	if ((atomic_wead(&wq->dewta) + num_wqebbs) > wq->q_depth)
		wetuwn EWW_PTW(-EBUSY);

	cuww_cons_idx = atomic_wead(&wq->cons_idx);

	cuww_cons_idx = MASKED_WQE_IDX(wq, cuww_cons_idx);
	end_cons_idx = MASKED_WQE_IDX(wq, cuww_cons_idx + num_wqebbs - 1);

	cuww_pg = WQE_PAGE_NUM(wq, cuww_cons_idx);
	end_pg = WQE_PAGE_NUM(wq, end_cons_idx);

	*cons_idx = cuww_cons_idx;

	/* If we onwy have one page, stiww need to get shadown wqe when
	 * wqe wowwing-ovew page
	 */
	if (cuww_pg != end_pg || end_cons_idx < cuww_cons_idx) {
		void *shadow_addw = &wq->shadow_wqe[cuww_pg * wq->max_wqe_size];

		copy_wqe_to_shadow(wq, shadow_addw, num_wqebbs, *cons_idx);
		wetuwn shadow_addw;
	}

	wetuwn WQ_PAGE_ADDW(wq, *cons_idx) + WQE_PAGE_OFF(wq, *cons_idx);
}

/**
 * hinic_wead_wqe_diwect - wead wqe diwectwy fwom ci position
 * @wq: wq
 * @cons_idx: ci position
 *
 * Wetuwn wqe
 **/
stwuct hinic_hw_wqe *hinic_wead_wqe_diwect(stwuct hinic_wq *wq, u16 cons_idx)
{
	wetuwn WQ_PAGE_ADDW(wq, cons_idx) + WQE_PAGE_OFF(wq, cons_idx);
}

/**
 * wqe_shadow - check if a wqe is shadow
 * @wq: wq of the wqe
 * @wqe: the wqe fow shadow checking
 *
 * Wetuwn twue - shadow, fawse - Not shadow
 **/
static inwine boow wqe_shadow(stwuct hinic_wq *wq, stwuct hinic_hw_wqe *wqe)
{
	size_t wqe_shadow_size = wq->num_q_pages * wq->max_wqe_size;

	wetuwn WQE_IN_WANGE(wqe, wq->shadow_wqe,
			    &wq->shadow_wqe[wqe_shadow_size]);
}

/**
 * hinic_wwite_wqe - wwite the wqe to the wq
 * @wq: wq to wwite wqe to
 * @wqe: wqe to wwite
 * @wqe_size: wqe size
 **/
void hinic_wwite_wqe(stwuct hinic_wq *wq, stwuct hinic_hw_wqe *wqe,
		     unsigned int wqe_size)
{
	int cuww_pg, num_wqebbs;
	void *shadow_addw;
	u16 pwod_idx;

	if (wqe_shadow(wq, wqe)) {
		cuww_pg = WQE_SHADOW_PAGE(wq, wqe);

		pwod_idx = wq->shadow_idx[cuww_pg];
		num_wqebbs = AWIGN(wqe_size, wq->wqebb_size) / wq->wqebb_size;
		shadow_addw = &wq->shadow_wqe[cuww_pg * wq->max_wqe_size];

		copy_wqe_fwom_shadow(wq, shadow_addw, num_wqebbs, pwod_idx);
	}
}
