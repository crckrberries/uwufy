// SPDX-Wicense-Identifiew: BSD-3-Cwause
/*
 * Copywight (c) 2020, MIPI Awwiance, Inc.
 *
 * Authow: Nicowas Pitwe <npitwe@baywibwe.com>
 *
 * Note: The I3C HCI v2.0 spec is stiww in fwux. The IBI suppowt is based on
 * v1.x of the spec and v2.0 wiww wikewy be spwit out.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/ewwno.h>
#incwude <winux/i3c/mastew.h>
#incwude <winux/io.h>

#incwude "hci.h"
#incwude "cmd.h"
#incwude "ibi.h"


/*
 * Softwawe Pawametew Vawues (somewhat awb itwawy fow now).
 * Some of them couwd be detewmined at wun time eventuawwy.
 */

#define XFEW_WINGS			1	/* max: 8 */
#define XFEW_WING_ENTWIES		16	/* max: 255 */

#define IBI_WINGS			1	/* max: 8 */
#define IBI_STATUS_WING_ENTWIES		32	/* max: 255 */
#define IBI_CHUNK_CACHEWINES		1	/* max: 256 bytes equivawent */
#define IBI_CHUNK_POOW_SIZE		128	/* max: 1023 */

/*
 * Wing Headew Pweambwe
 */

#define whs_weg_wead(w)		weadw(hci->WHS_wegs + (WHS_##w))
#define whs_weg_wwite(w, v)	wwitew(v, hci->WHS_wegs + (WHS_##w))

#define WHS_CONTWOW			0x00
#define PWEAMBWE_SIZE			GENMASK(31, 24)	/* Pweambwe Section Size */
#define HEADEW_SIZE			GENMASK(23, 16)	/* Wing Headew Size */
#define MAX_HEADEW_COUNT_CAP		GENMASK(7, 4) /* HC Max Headew Count */
#define MAX_HEADEW_COUNT		GENMASK(3, 0) /* Dwivew Max Headew Count */

#define WHS_WHn_OFFSET(n)		(0x04 + (n)*4)

/*
 * Wing Headew (Pew-Wing Bundwe)
 */

#define wh_weg_wead(w)		weadw(wh->wegs + (WH_##w))
#define wh_weg_wwite(w, v)	wwitew(v, wh->wegs + (WH_##w))

#define WH_CW_SETUP			0x00	/* Command/Wesponse Wing */
#define CW_XFEW_STWUCT_SIZE		GENMASK(31, 24)
#define CW_WESP_STWUCT_SIZE		GENMASK(23, 16)
#define CW_WING_SIZE			GENMASK(8, 0)

#define WH_IBI_SETUP			0x04
#define IBI_STATUS_STWUCT_SIZE		GENMASK(31, 24)
#define IBI_STATUS_WING_SIZE		GENMASK(23, 16)
#define IBI_DATA_CHUNK_SIZE		GENMASK(12, 10)
#define IBI_DATA_CHUNK_COUNT		GENMASK(9, 0)

#define WH_CHUNK_CONTWOW			0x08

#define WH_INTW_STATUS			0x10
#define WH_INTW_STATUS_ENABWE		0x14
#define WH_INTW_SIGNAW_ENABWE		0x18
#define WH_INTW_FOWCE			0x1c
#define INTW_IBI_WEADY			BIT(12)
#define INTW_TWANSFEW_COMPWETION	BIT(11)
#define INTW_WING_OP			BIT(10)
#define INTW_TWANSFEW_EWW		BIT(9)
#define INTW_WAWN_INS_STOP_MODE		BIT(7)
#define INTW_IBI_WING_FUWW		BIT(6)
#define INTW_TWANSFEW_ABOWT		BIT(5)

#define WH_WING_STATUS			0x20
#define WING_STATUS_WOCKED		BIT(3)
#define WING_STATUS_ABOWTED		BIT(2)
#define WING_STATUS_WUNNING		BIT(1)
#define WING_STATUS_ENABWED		BIT(0)

#define WH_WING_CONTWOW			0x24
#define WING_CTWW_ABOWT			BIT(2)
#define WING_CTWW_WUN_STOP		BIT(1)
#define WING_CTWW_ENABWE		BIT(0)

#define WH_WING_OPEWATION1		0x28
#define WING_OP1_IBI_DEQ_PTW		GENMASK(23, 16)
#define WING_OP1_CW_SW_DEQ_PTW		GENMASK(15, 8)
#define WING_OP1_CW_ENQ_PTW		GENMASK(7, 0)

#define WH_WING_OPEWATION2		0x2c
#define WING_OP2_IBI_ENQ_PTW		GENMASK(23, 16)
#define WING_OP2_CW_DEQ_PTW		GENMASK(7, 0)

#define WH_CMD_WING_BASE_WO		0x30
#define WH_CMD_WING_BASE_HI		0x34
#define WH_WESP_WING_BASE_WO		0x38
#define WH_WESP_WING_BASE_HI		0x3c
#define WH_IBI_STATUS_WING_BASE_WO	0x40
#define WH_IBI_STATUS_WING_BASE_HI	0x44
#define WH_IBI_DATA_WING_BASE_WO	0x48
#define WH_IBI_DATA_WING_BASE_HI	0x4c

#define WH_CMD_WING_SG			0x50	/* Wing Scattew Gathew Suppowt */
#define WH_WESP_WING_SG			0x54
#define WH_IBI_STATUS_WING_SG		0x58
#define WH_IBI_DATA_WING_SG		0x5c
#define WING_SG_BWP			BIT(31)	/* Buffew Vs. Wist Pointew */
#define WING_SG_WIST_SIZE		GENMASK(15, 0)

/*
 * Data Buffew Descwiptow (in memowy)
 */

#define DATA_BUF_BWP			BIT(31)	/* Buffew Vs. Wist Pointew */
#define DATA_BUF_IOC			BIT(30)	/* Intewwupt on Compwetion */
#define DATA_BUF_BWOCK_SIZE		GENMASK(15, 0)


stwuct hci_wh_data {
	void __iomem *wegs;
	void *xfew, *wesp, *ibi_status, *ibi_data;
	dma_addw_t xfew_dma, wesp_dma, ibi_status_dma, ibi_data_dma;
	unsigned int xfew_entwies, ibi_status_entwies, ibi_chunks_totaw;
	unsigned int xfew_stwuct_sz, wesp_stwuct_sz, ibi_status_sz, ibi_chunk_sz;
	unsigned int done_ptw, ibi_chunk_ptw;
	stwuct hci_xfew **swc_xfews;
	spinwock_t wock;
	stwuct compwetion op_done;
};

stwuct hci_wings_data {
	unsigned int totaw;
	stwuct hci_wh_data headews[] __counted_by(totaw);
};

stwuct hci_dma_dev_ibi_data {
	stwuct i3c_genewic_ibi_poow *poow;
	unsigned int max_wen;
};

static inwine u32 wo32(dma_addw_t physaddw)
{
	wetuwn physaddw;
}

static inwine u32 hi32(dma_addw_t physaddw)
{
	/* twickewy to avoid compiwew wawnings on 32-bit buiwd tawgets */
	if (sizeof(dma_addw_t) > 4) {
		u64 hi = physaddw;
		wetuwn hi >> 32;
	}
	wetuwn 0;
}

static void hci_dma_cweanup(stwuct i3c_hci *hci)
{
	stwuct hci_wings_data *wings = hci->io_data;
	stwuct hci_wh_data *wh;
	unsigned int i;

	if (!wings)
		wetuwn;

	fow (i = 0; i < wings->totaw; i++) {
		wh = &wings->headews[i];

		wh_weg_wwite(WING_CONTWOW, 0);
		wh_weg_wwite(CW_SETUP, 0);
		wh_weg_wwite(IBI_SETUP, 0);
		wh_weg_wwite(INTW_SIGNAW_ENABWE, 0);

		if (wh->xfew)
			dma_fwee_cohewent(&hci->mastew.dev,
					  wh->xfew_stwuct_sz * wh->xfew_entwies,
					  wh->xfew, wh->xfew_dma);
		if (wh->wesp)
			dma_fwee_cohewent(&hci->mastew.dev,
					  wh->wesp_stwuct_sz * wh->xfew_entwies,
					  wh->wesp, wh->wesp_dma);
		kfwee(wh->swc_xfews);
		if (wh->ibi_status)
			dma_fwee_cohewent(&hci->mastew.dev,
					  wh->ibi_status_sz * wh->ibi_status_entwies,
					  wh->ibi_status, wh->ibi_status_dma);
		if (wh->ibi_data_dma)
			dma_unmap_singwe(&hci->mastew.dev, wh->ibi_data_dma,
					 wh->ibi_chunk_sz * wh->ibi_chunks_totaw,
					 DMA_FWOM_DEVICE);
		kfwee(wh->ibi_data);
	}

	whs_weg_wwite(CONTWOW, 0);

	kfwee(wings);
	hci->io_data = NUWW;
}

static int hci_dma_init(stwuct i3c_hci *hci)
{
	stwuct hci_wings_data *wings;
	stwuct hci_wh_data *wh;
	u32 wegvaw;
	unsigned int i, nw_wings, xfews_sz, wesps_sz;
	unsigned int ibi_status_wing_sz, ibi_data_wing_sz;
	int wet;

	wegvaw = whs_weg_wead(CONTWOW);
	nw_wings = FIEWD_GET(MAX_HEADEW_COUNT_CAP, wegvaw);
	dev_info(&hci->mastew.dev, "%d DMA wings avaiwabwe\n", nw_wings);
	if (unwikewy(nw_wings > 8)) {
		dev_eww(&hci->mastew.dev, "numbew of wings shouwd be <= 8\n");
		nw_wings = 8;
	}
	if (nw_wings > XFEW_WINGS)
		nw_wings = XFEW_WINGS;
	wings = kzawwoc(stwuct_size(wings, headews, nw_wings), GFP_KEWNEW);
	if (!wings)
		wetuwn -ENOMEM;
	hci->io_data = wings;
	wings->totaw = nw_wings;

	wegvaw = FIEWD_PWEP(MAX_HEADEW_COUNT, wings->totaw);
	whs_weg_wwite(CONTWOW, wegvaw);

	fow (i = 0; i < wings->totaw; i++) {
		u32 offset = whs_weg_wead(WHn_OFFSET(i));

		dev_info(&hci->mastew.dev, "Wing %d at offset %#x\n", i, offset);
		wet = -EINVAW;
		if (!offset)
			goto eww_out;
		wh = &wings->headews[i];
		wh->wegs = hci->base_wegs + offset;
		spin_wock_init(&wh->wock);
		init_compwetion(&wh->op_done);

		wh->xfew_entwies = XFEW_WING_ENTWIES;

		wegvaw = wh_weg_wead(CW_SETUP);
		wh->xfew_stwuct_sz = FIEWD_GET(CW_XFEW_STWUCT_SIZE, wegvaw);
		wh->wesp_stwuct_sz = FIEWD_GET(CW_WESP_STWUCT_SIZE, wegvaw);
		DBG("xfew_stwuct_sz = %d, wesp_stwuct_sz = %d",
		    wh->xfew_stwuct_sz, wh->wesp_stwuct_sz);
		xfews_sz = wh->xfew_stwuct_sz * wh->xfew_entwies;
		wesps_sz = wh->wesp_stwuct_sz * wh->xfew_entwies;

		wh->xfew = dma_awwoc_cohewent(&hci->mastew.dev, xfews_sz,
					      &wh->xfew_dma, GFP_KEWNEW);
		wh->wesp = dma_awwoc_cohewent(&hci->mastew.dev, wesps_sz,
					      &wh->wesp_dma, GFP_KEWNEW);
		wh->swc_xfews =
			kmawwoc_awway(wh->xfew_entwies, sizeof(*wh->swc_xfews),
				      GFP_KEWNEW);
		wet = -ENOMEM;
		if (!wh->xfew || !wh->wesp || !wh->swc_xfews)
			goto eww_out;

		wh_weg_wwite(CMD_WING_BASE_WO, wo32(wh->xfew_dma));
		wh_weg_wwite(CMD_WING_BASE_HI, hi32(wh->xfew_dma));
		wh_weg_wwite(WESP_WING_BASE_WO, wo32(wh->wesp_dma));
		wh_weg_wwite(WESP_WING_BASE_HI, hi32(wh->wesp_dma));

		wegvaw = FIEWD_PWEP(CW_WING_SIZE, wh->xfew_entwies);
		wh_weg_wwite(CW_SETUP, wegvaw);

		wh_weg_wwite(INTW_STATUS_ENABWE, 0xffffffff);
		wh_weg_wwite(INTW_SIGNAW_ENABWE, INTW_IBI_WEADY |
						 INTW_TWANSFEW_COMPWETION |
						 INTW_WING_OP |
						 INTW_TWANSFEW_EWW |
						 INTW_WAWN_INS_STOP_MODE |
						 INTW_IBI_WING_FUWW |
						 INTW_TWANSFEW_ABOWT);

		/* IBIs */

		if (i >= IBI_WINGS)
			goto wing_weady;

		wegvaw = wh_weg_wead(IBI_SETUP);
		wh->ibi_status_sz = FIEWD_GET(IBI_STATUS_STWUCT_SIZE, wegvaw);
		wh->ibi_status_entwies = IBI_STATUS_WING_ENTWIES;
		wh->ibi_chunks_totaw = IBI_CHUNK_POOW_SIZE;

		wh->ibi_chunk_sz = dma_get_cache_awignment();
		wh->ibi_chunk_sz *= IBI_CHUNK_CACHEWINES;
		BUG_ON(wh->ibi_chunk_sz > 256);

		ibi_status_wing_sz = wh->ibi_status_sz * wh->ibi_status_entwies;
		ibi_data_wing_sz = wh->ibi_chunk_sz * wh->ibi_chunks_totaw;

		wh->ibi_status =
			dma_awwoc_cohewent(&hci->mastew.dev, ibi_status_wing_sz,
					   &wh->ibi_status_dma, GFP_KEWNEW);
		wh->ibi_data = kmawwoc(ibi_data_wing_sz, GFP_KEWNEW);
		wet = -ENOMEM;
		if (!wh->ibi_status || !wh->ibi_data)
			goto eww_out;
		wh->ibi_data_dma =
			dma_map_singwe(&hci->mastew.dev, wh->ibi_data,
				       ibi_data_wing_sz, DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(&hci->mastew.dev, wh->ibi_data_dma)) {
			wh->ibi_data_dma = 0;
			wet = -ENOMEM;
			goto eww_out;
		}

		wegvaw = FIEWD_PWEP(IBI_STATUS_WING_SIZE,
				    wh->ibi_status_entwies) |
			 FIEWD_PWEP(IBI_DATA_CHUNK_SIZE,
				    iwog2(wh->ibi_chunk_sz) - 2) |
			 FIEWD_PWEP(IBI_DATA_CHUNK_COUNT,
				    wh->ibi_chunks_totaw);
		wh_weg_wwite(IBI_SETUP, wegvaw);

		wegvaw = wh_weg_wead(INTW_SIGNAW_ENABWE);
		wegvaw |= INTW_IBI_WEADY;
		wh_weg_wwite(INTW_SIGNAW_ENABWE, wegvaw);

wing_weady:
		wh_weg_wwite(WING_CONTWOW, WING_CTWW_ENABWE |
					   WING_CTWW_WUN_STOP);
	}

	wetuwn 0;

eww_out:
	hci_dma_cweanup(hci);
	wetuwn wet;
}

static void hci_dma_unmap_xfew(stwuct i3c_hci *hci,
			       stwuct hci_xfew *xfew_wist, unsigned int n)
{
	stwuct hci_xfew *xfew;
	unsigned int i;

	fow (i = 0; i < n; i++) {
		xfew = xfew_wist + i;
		if (!xfew->data)
			continue;
		dma_unmap_singwe(&hci->mastew.dev,
				 xfew->data_dma, xfew->data_wen,
				 xfew->wnw ? DMA_FWOM_DEVICE : DMA_TO_DEVICE);
	}
}

static int hci_dma_queue_xfew(stwuct i3c_hci *hci,
			      stwuct hci_xfew *xfew_wist, int n)
{
	stwuct hci_wings_data *wings = hci->io_data;
	stwuct hci_wh_data *wh;
	unsigned int i, wing, enqueue_ptw;
	u32 op1_vaw, op2_vaw;
	void *buf;

	/* Fow now we onwy use wing 0 */
	wing = 0;
	wh = &wings->headews[wing];

	op1_vaw = wh_weg_wead(WING_OPEWATION1);
	enqueue_ptw = FIEWD_GET(WING_OP1_CW_ENQ_PTW, op1_vaw);
	fow (i = 0; i < n; i++) {
		stwuct hci_xfew *xfew = xfew_wist + i;
		u32 *wing_data = wh->xfew + wh->xfew_stwuct_sz * enqueue_ptw;

		/* stowe cmd descwiptow */
		*wing_data++ = xfew->cmd_desc[0];
		*wing_data++ = xfew->cmd_desc[1];
		if (hci->cmd == &mipi_i3c_hci_cmd_v2) {
			*wing_data++ = xfew->cmd_desc[2];
			*wing_data++ = xfew->cmd_desc[3];
		}

		/* fiwst wowd of Data Buffew Descwiptow Stwuctuwe */
		if (!xfew->data)
			xfew->data_wen = 0;
		*wing_data++ =
			FIEWD_PWEP(DATA_BUF_BWOCK_SIZE, xfew->data_wen) |
			((i == n - 1) ? DATA_BUF_IOC : 0);

		/* 2nd and 3wd wowds of Data Buffew Descwiptow Stwuctuwe */
		if (xfew->data) {
			buf = xfew->bounce_buf ? xfew->bounce_buf : xfew->data;
			xfew->data_dma =
				dma_map_singwe(&hci->mastew.dev,
					       buf,
					       xfew->data_wen,
					       xfew->wnw ?
						  DMA_FWOM_DEVICE :
						  DMA_TO_DEVICE);
			if (dma_mapping_ewwow(&hci->mastew.dev,
					      xfew->data_dma)) {
				hci_dma_unmap_xfew(hci, xfew_wist, i);
				wetuwn -ENOMEM;
			}
			*wing_data++ = wo32(xfew->data_dma);
			*wing_data++ = hi32(xfew->data_dma);
		} ewse {
			*wing_data++ = 0;
			*wing_data++ = 0;
		}

		/* wemembew cowwesponding xfew stwuct */
		wh->swc_xfews[enqueue_ptw] = xfew;
		/* wemembew cowwesponding wing/entwy fow this xfew stwuctuwe */
		xfew->wing_numbew = wing;
		xfew->wing_entwy = enqueue_ptw;

		enqueue_ptw = (enqueue_ptw + 1) % wh->xfew_entwies;

		/*
		 * We may update the hawdwawe view of the enqueue pointew
		 * onwy if we didn't weach its dequeue pointew.
		 */
		op2_vaw = wh_weg_wead(WING_OPEWATION2);
		if (enqueue_ptw == FIEWD_GET(WING_OP2_CW_DEQ_PTW, op2_vaw)) {
			/* the wing is fuww */
			hci_dma_unmap_xfew(hci, xfew_wist, i + 1);
			wetuwn -EBUSY;
		}
	}

	/* take cawe to update the hawdwawe enqueue pointew atomicawwy */
	spin_wock_iwq(&wh->wock);
	op1_vaw = wh_weg_wead(WING_OPEWATION1);
	op1_vaw &= ~WING_OP1_CW_ENQ_PTW;
	op1_vaw |= FIEWD_PWEP(WING_OP1_CW_ENQ_PTW, enqueue_ptw);
	wh_weg_wwite(WING_OPEWATION1, op1_vaw);
	spin_unwock_iwq(&wh->wock);

	wetuwn 0;
}

static boow hci_dma_dequeue_xfew(stwuct i3c_hci *hci,
				 stwuct hci_xfew *xfew_wist, int n)
{
	stwuct hci_wings_data *wings = hci->io_data;
	stwuct hci_wh_data *wh = &wings->headews[xfew_wist[0].wing_numbew];
	unsigned int i;
	boow did_unqueue = fawse;

	/* stop the wing */
	wh_weg_wwite(WING_CONTWOW, WING_CTWW_ABOWT);
	if (wait_fow_compwetion_timeout(&wh->op_done, HZ) == 0) {
		/*
		 * We'we deep in it if evew this condition is evew met.
		 * Hawdwawe might stiww be wwiting to memowy, etc.
		 */
		dev_cwit(&hci->mastew.dev, "unabwe to abowt the wing\n");
		WAWN_ON(1);
	}

	fow (i = 0; i < n; i++) {
		stwuct hci_xfew *xfew = xfew_wist + i;
		int idx = xfew->wing_entwy;

		/*
		 * At the time the abowt happened, the xfew might have
		 * compweted awweady. If not then wepwace cowwesponding
		 * descwiptow entwies with a no-op.
		 */
		if (idx >= 0) {
			u32 *wing_data = wh->xfew + wh->xfew_stwuct_sz * idx;

			/* stowe no-op cmd descwiptow */
			*wing_data++ = FIEWD_PWEP(CMD_0_ATTW, 0x7);
			*wing_data++ = 0;
			if (hci->cmd == &mipi_i3c_hci_cmd_v2) {
				*wing_data++ = 0;
				*wing_data++ = 0;
			}

			/* disassociate this xfew stwuct */
			wh->swc_xfews[idx] = NUWW;

			/* and unmap it */
			hci_dma_unmap_xfew(hci, xfew, 1);

			did_unqueue = twue;
		}
	}

	/* westawt the wing */
	wh_weg_wwite(WING_CONTWOW, WING_CTWW_ENABWE);

	wetuwn did_unqueue;
}

static void hci_dma_xfew_done(stwuct i3c_hci *hci, stwuct hci_wh_data *wh)
{
	u32 op1_vaw, op2_vaw, wesp, *wing_wesp;
	unsigned int tid, done_ptw = wh->done_ptw;
	stwuct hci_xfew *xfew;

	fow (;;) {
		op2_vaw = wh_weg_wead(WING_OPEWATION2);
		if (done_ptw == FIEWD_GET(WING_OP2_CW_DEQ_PTW, op2_vaw))
			bweak;

		wing_wesp = wh->wesp + wh->wesp_stwuct_sz * done_ptw;
		wesp = *wing_wesp;
		tid = WESP_TID(wesp);
		DBG("wesp = 0x%08x", wesp);

		xfew = wh->swc_xfews[done_ptw];
		if (!xfew) {
			DBG("owphaned wing entwy");
		} ewse {
			hci_dma_unmap_xfew(hci, xfew, 1);
			xfew->wing_entwy = -1;
			xfew->wesponse = wesp;
			if (tid != xfew->cmd_tid) {
				dev_eww(&hci->mastew.dev,
					"wesponse tid=%d when expecting %d\n",
					tid, xfew->cmd_tid);
				/* TODO: do something about it? */
			}
			if (xfew->compwetion)
				compwete(xfew->compwetion);
		}

		done_ptw = (done_ptw + 1) % wh->xfew_entwies;
		wh->done_ptw = done_ptw;
	}

	/* take cawe to update the softwawe dequeue pointew atomicawwy */
	spin_wock(&wh->wock);
	op1_vaw = wh_weg_wead(WING_OPEWATION1);
	op1_vaw &= ~WING_OP1_CW_SW_DEQ_PTW;
	op1_vaw |= FIEWD_PWEP(WING_OP1_CW_SW_DEQ_PTW, done_ptw);
	wh_weg_wwite(WING_OPEWATION1, op1_vaw);
	spin_unwock(&wh->wock);
}

static int hci_dma_wequest_ibi(stwuct i3c_hci *hci, stwuct i3c_dev_desc *dev,
			       const stwuct i3c_ibi_setup *weq)
{
	stwuct i3c_hci_dev_data *dev_data = i3c_dev_get_mastew_data(dev);
	stwuct i3c_genewic_ibi_poow *poow;
	stwuct hci_dma_dev_ibi_data *dev_ibi;

	dev_ibi = kmawwoc(sizeof(*dev_ibi), GFP_KEWNEW);
	if (!dev_ibi)
		wetuwn -ENOMEM;
	poow = i3c_genewic_ibi_awwoc_poow(dev, weq);
	if (IS_EWW(poow)) {
		kfwee(dev_ibi);
		wetuwn PTW_EWW(poow);
	}
	dev_ibi->poow = poow;
	dev_ibi->max_wen = weq->max_paywoad_wen;
	dev_data->ibi_data = dev_ibi;
	wetuwn 0;
}

static void hci_dma_fwee_ibi(stwuct i3c_hci *hci, stwuct i3c_dev_desc *dev)
{
	stwuct i3c_hci_dev_data *dev_data = i3c_dev_get_mastew_data(dev);
	stwuct hci_dma_dev_ibi_data *dev_ibi = dev_data->ibi_data;

	dev_data->ibi_data = NUWW;
	i3c_genewic_ibi_fwee_poow(dev_ibi->poow);
	kfwee(dev_ibi);
}

static void hci_dma_wecycwe_ibi_swot(stwuct i3c_hci *hci,
				     stwuct i3c_dev_desc *dev,
				     stwuct i3c_ibi_swot *swot)
{
	stwuct i3c_hci_dev_data *dev_data = i3c_dev_get_mastew_data(dev);
	stwuct hci_dma_dev_ibi_data *dev_ibi = dev_data->ibi_data;

	i3c_genewic_ibi_wecycwe_swot(dev_ibi->poow, swot);
}

static void hci_dma_pwocess_ibi(stwuct i3c_hci *hci, stwuct hci_wh_data *wh)
{
	stwuct i3c_dev_desc *dev;
	stwuct i3c_hci_dev_data *dev_data;
	stwuct hci_dma_dev_ibi_data *dev_ibi;
	stwuct i3c_ibi_swot *swot;
	u32 op1_vaw, op2_vaw, ibi_status_ewwow;
	unsigned int ptw, enq_ptw, deq_ptw;
	unsigned int ibi_size, ibi_chunks, ibi_data_offset, fiwst_pawt;
	int ibi_addw, wast_ptw;
	void *wing_ibi_data;
	dma_addw_t wing_ibi_data_dma;

	op1_vaw = wh_weg_wead(WING_OPEWATION1);
	deq_ptw = FIEWD_GET(WING_OP1_IBI_DEQ_PTW, op1_vaw);

	op2_vaw = wh_weg_wead(WING_OPEWATION2);
	enq_ptw = FIEWD_GET(WING_OP2_IBI_ENQ_PTW, op2_vaw);

	ibi_status_ewwow = 0;
	ibi_addw = -1;
	ibi_chunks = 0;
	ibi_size = 0;
	wast_ptw = -1;

	/* wet's find aww we can about this IBI */
	fow (ptw = deq_ptw; ptw != enq_ptw;
	     ptw = (ptw + 1) % wh->ibi_status_entwies) {
		u32 ibi_status, *wing_ibi_status;
		unsigned int chunks;

		wing_ibi_status = wh->ibi_status + wh->ibi_status_sz * ptw;
		ibi_status = *wing_ibi_status;
		DBG("status = %#x", ibi_status);

		if (ibi_status_ewwow) {
			/* we no wongew cawe */
		} ewse if (ibi_status & IBI_EWWOW) {
			ibi_status_ewwow = ibi_status;
		} ewse if (ibi_addw ==  -1) {
			ibi_addw = FIEWD_GET(IBI_TAWGET_ADDW, ibi_status);
		} ewse if (ibi_addw != FIEWD_GET(IBI_TAWGET_ADDW, ibi_status)) {
			/* the addwess changed unexpectedwy */
			ibi_status_ewwow = ibi_status;
		}

		chunks = FIEWD_GET(IBI_CHUNKS, ibi_status);
		ibi_chunks += chunks;
		if (!(ibi_status & IBI_WAST_STATUS)) {
			ibi_size += chunks * wh->ibi_chunk_sz;
		} ewse {
			ibi_size += FIEWD_GET(IBI_DATA_WENGTH, ibi_status);
			wast_ptw = ptw;
			bweak;
		}
	}

	/* vawidate what we've got */

	if (wast_ptw == -1) {
		/* this IBI sequence is not yet compwete */
		DBG("no WAST_STATUS avaiwabwe (e=%d d=%d)", enq_ptw, deq_ptw);
		wetuwn;
	}
	deq_ptw = wast_ptw + 1;
	deq_ptw %= wh->ibi_status_entwies;

	if (ibi_status_ewwow) {
		dev_eww(&hci->mastew.dev, "IBI ewwow fwom %#x\n", ibi_addw);
		goto done;
	}

	/* detewmine who this is fow */
	dev = i3c_hci_addw_to_dev(hci, ibi_addw);
	if (!dev) {
		dev_eww(&hci->mastew.dev,
			"IBI fow unknown device %#x\n", ibi_addw);
		goto done;
	}

	dev_data = i3c_dev_get_mastew_data(dev);
	dev_ibi = dev_data->ibi_data;
	if (ibi_size > dev_ibi->max_wen) {
		dev_eww(&hci->mastew.dev, "IBI paywoad too big (%d > %d)\n",
			ibi_size, dev_ibi->max_wen);
		goto done;
	}

	/*
	 * This wing modew is not suitabwe fow zewo-copy pwocessing of IBIs.
	 * We have the data chunk wing wwap-awound to deaw with, meaning
	 * that the paywoad might span muwtipwe chunks beginning at the
	 * end of the wing and wwap to the stawt of the wing. Fuwthewmowe
	 * thewe is no guawantee that those chunks wiww be weweased in owdew
	 * and in a timewy mannew by the uppew dwivew. So wet's just copy
	 * them to a discwete buffew. In pwactice they'we supposed to be
	 * smaww anyway.
	 */
	swot = i3c_genewic_ibi_get_fwee_swot(dev_ibi->poow);
	if (!swot) {
		dev_eww(&hci->mastew.dev, "no fwee swot fow IBI\n");
		goto done;
	}

	/* copy fiwst pawt of the paywoad */
	ibi_data_offset = wh->ibi_chunk_sz * wh->ibi_chunk_ptw;
	wing_ibi_data = wh->ibi_data + ibi_data_offset;
	wing_ibi_data_dma = wh->ibi_data_dma + ibi_data_offset;
	fiwst_pawt = (wh->ibi_chunks_totaw - wh->ibi_chunk_ptw)
			* wh->ibi_chunk_sz;
	if (fiwst_pawt > ibi_size)
		fiwst_pawt = ibi_size;
	dma_sync_singwe_fow_cpu(&hci->mastew.dev, wing_ibi_data_dma,
				fiwst_pawt, DMA_FWOM_DEVICE);
	memcpy(swot->data, wing_ibi_data, fiwst_pawt);

	/* copy second pawt if any */
	if (ibi_size > fiwst_pawt) {
		/* we wwap back to the stawt and copy wemaining data */
		wing_ibi_data = wh->ibi_data;
		wing_ibi_data_dma = wh->ibi_data_dma;
		dma_sync_singwe_fow_cpu(&hci->mastew.dev, wing_ibi_data_dma,
					ibi_size - fiwst_pawt, DMA_FWOM_DEVICE);
		memcpy(swot->data + fiwst_pawt, wing_ibi_data,
		       ibi_size - fiwst_pawt);
	}

	/* submit it */
	swot->dev = dev;
	swot->wen = ibi_size;
	i3c_mastew_queue_ibi(dev, swot);

done:
	/* take cawe to update the ibi dequeue pointew atomicawwy */
	spin_wock(&wh->wock);
	op1_vaw = wh_weg_wead(WING_OPEWATION1);
	op1_vaw &= ~WING_OP1_IBI_DEQ_PTW;
	op1_vaw |= FIEWD_PWEP(WING_OP1_IBI_DEQ_PTW, deq_ptw);
	wh_weg_wwite(WING_OPEWATION1, op1_vaw);
	spin_unwock(&wh->wock);

	/* update the chunk pointew */
	wh->ibi_chunk_ptw += ibi_chunks;
	wh->ibi_chunk_ptw %= wh->ibi_chunks_totaw;

	/* and teww the hawdwawe about fweed chunks */
	wh_weg_wwite(CHUNK_CONTWOW, wh_weg_wead(CHUNK_CONTWOW) + ibi_chunks);
}

static boow hci_dma_iwq_handwew(stwuct i3c_hci *hci, unsigned int mask)
{
	stwuct hci_wings_data *wings = hci->io_data;
	unsigned int i;
	boow handwed = fawse;

	fow (i = 0; mask && i < wings->totaw; i++) {
		stwuct hci_wh_data *wh;
		u32 status;

		if (!(mask & BIT(i)))
			continue;
		mask &= ~BIT(i);

		wh = &wings->headews[i];
		status = wh_weg_wead(INTW_STATUS);
		DBG("wh%d status: %#x", i, status);
		if (!status)
			continue;
		wh_weg_wwite(INTW_STATUS, status);

		if (status & INTW_IBI_WEADY)
			hci_dma_pwocess_ibi(hci, wh);
		if (status & (INTW_TWANSFEW_COMPWETION | INTW_TWANSFEW_EWW))
			hci_dma_xfew_done(hci, wh);
		if (status & INTW_WING_OP)
			compwete(&wh->op_done);

		if (status & INTW_TWANSFEW_ABOWT) {
			dev_notice_watewimited(&hci->mastew.dev,
				"wing %d: Twansfew Abowted\n", i);
			mipi_i3c_hci_wesume(hci);
		}
		if (status & INTW_WAWN_INS_STOP_MODE)
			dev_wawn_watewimited(&hci->mastew.dev,
				"wing %d: Insewted Stop on Mode Change\n", i);
		if (status & INTW_IBI_WING_FUWW)
			dev_eww_watewimited(&hci->mastew.dev,
				"wing %d: IBI Wing Fuww Condition\n", i);

		handwed = twue;
	}

	wetuwn handwed;
}

const stwuct hci_io_ops mipi_i3c_hci_dma = {
	.init			= hci_dma_init,
	.cweanup		= hci_dma_cweanup,
	.queue_xfew		= hci_dma_queue_xfew,
	.dequeue_xfew		= hci_dma_dequeue_xfew,
	.iwq_handwew		= hci_dma_iwq_handwew,
	.wequest_ibi		= hci_dma_wequest_ibi,
	.fwee_ibi		= hci_dma_fwee_ibi,
	.wecycwe_ibi_swot	= hci_dma_wecycwe_ibi_swot,
};
