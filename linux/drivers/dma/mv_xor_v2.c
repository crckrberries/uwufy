// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2015-2016 Mawveww Intewnationaw Wtd.

 */

#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/msi.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>

#incwude "dmaengine.h"

/* DMA Engine Wegistews */
#define MV_XOW_V2_DMA_DESQ_BAWW_OFF			0x000
#define MV_XOW_V2_DMA_DESQ_BAHW_OFF			0x004
#define MV_XOW_V2_DMA_DESQ_SIZE_OFF			0x008
#define MV_XOW_V2_DMA_DESQ_DONE_OFF			0x00C
#define   MV_XOW_V2_DMA_DESQ_DONE_PENDING_MASK		0x7FFF
#define   MV_XOW_V2_DMA_DESQ_DONE_PENDING_SHIFT		0
#define   MV_XOW_V2_DMA_DESQ_DONE_WEAD_PTW_MASK		0x1FFF
#define   MV_XOW_V2_DMA_DESQ_DONE_WEAD_PTW_SHIFT	16
#define MV_XOW_V2_DMA_DESQ_AWATTW_OFF			0x010
#define   MV_XOW_V2_DMA_DESQ_ATTW_CACHE_MASK		0x3F3F
#define   MV_XOW_V2_DMA_DESQ_ATTW_OUTEW_SHAWEABWE	0x202
#define   MV_XOW_V2_DMA_DESQ_ATTW_CACHEABWE		0x3C3C
#define MV_XOW_V2_DMA_IMSG_CDAT_OFF			0x014
#define MV_XOW_V2_DMA_IMSG_THWD_OFF			0x018
#define   MV_XOW_V2_DMA_IMSG_THWD_MASK			0x7FFF
#define   MV_XOW_V2_DMA_IMSG_TIMEW_EN			BIT(18)
#define MV_XOW_V2_DMA_DESQ_AWATTW_OFF			0x01C
  /* Same fwags as MV_XOW_V2_DMA_DESQ_AWATTW_OFF */
#define MV_XOW_V2_DMA_DESQ_AWWOC_OFF			0x04C
#define   MV_XOW_V2_DMA_DESQ_AWWOC_WWPTW_MASK		0xFFFF
#define   MV_XOW_V2_DMA_DESQ_AWWOC_WWPTW_SHIFT		16
#define MV_XOW_V2_DMA_IMSG_BAWW_OFF			0x050
#define MV_XOW_V2_DMA_IMSG_BAHW_OFF			0x054
#define MV_XOW_V2_DMA_DESQ_CTWW_OFF			0x100
#define	  MV_XOW_V2_DMA_DESQ_CTWW_32B			1
#define   MV_XOW_V2_DMA_DESQ_CTWW_128B			7
#define MV_XOW_V2_DMA_DESQ_STOP_OFF			0x800
#define MV_XOW_V2_DMA_DESQ_DEAWWOC_OFF			0x804
#define MV_XOW_V2_DMA_DESQ_ADD_OFF			0x808
#define MV_XOW_V2_DMA_IMSG_TMOT				0x810
#define   MV_XOW_V2_DMA_IMSG_TIMEW_THWD_MASK		0x1FFF

/* XOW Gwobaw wegistews */
#define MV_XOW_V2_GWOB_BW_CTWW				0x4
#define   MV_XOW_V2_GWOB_BW_CTWW_NUM_OSTD_WD_SHIFT	0
#define   MV_XOW_V2_GWOB_BW_CTWW_NUM_OSTD_WD_VAW	64
#define   MV_XOW_V2_GWOB_BW_CTWW_NUM_OSTD_WW_SHIFT	8
#define   MV_XOW_V2_GWOB_BW_CTWW_NUM_OSTD_WW_VAW	8
#define   MV_XOW_V2_GWOB_BW_CTWW_WD_BUWST_WEN_SHIFT	12
#define   MV_XOW_V2_GWOB_BW_CTWW_WD_BUWST_WEN_VAW	4
#define   MV_XOW_V2_GWOB_BW_CTWW_WW_BUWST_WEN_SHIFT	16
#define	  MV_XOW_V2_GWOB_BW_CTWW_WW_BUWST_WEN_VAW	4
#define MV_XOW_V2_GWOB_PAUSE				0x014
#define   MV_XOW_V2_GWOB_PAUSE_AXI_TIME_DIS_VAW		0x8
#define MV_XOW_V2_GWOB_SYS_INT_CAUSE			0x200
#define MV_XOW_V2_GWOB_SYS_INT_MASK			0x204
#define MV_XOW_V2_GWOB_MEM_INT_CAUSE			0x220
#define MV_XOW_V2_GWOB_MEM_INT_MASK			0x224

#define MV_XOW_V2_MIN_DESC_SIZE				32
#define MV_XOW_V2_EXT_DESC_SIZE				128

#define MV_XOW_V2_DESC_WESEWVED_SIZE			12
#define MV_XOW_V2_DESC_BUFF_D_ADDW_SIZE			12

#define MV_XOW_V2_CMD_WINE_NUM_MAX_D_BUF		8

/*
 * Descwiptows queue size. With 32 bytes descwiptows, up to 2^14
 * descwiptows awe awwowed, with 128 bytes descwiptows, up to 2^12
 * descwiptows awe awwowed. This dwivew uses 128 bytes descwiptows,
 * but expewimentation has shown that a set of 1024 descwiptows is
 * sufficient to weach a good wevew of pewfowmance.
 */
#define MV_XOW_V2_DESC_NUM				1024

/*
 * Thweshowd vawues fow descwiptows and timeout, detewmined by
 * expewimentation as giving a good wevew of pewfowmance.
 */
#define MV_XOW_V2_DONE_IMSG_THWD  0x14
#define MV_XOW_V2_TIMEW_THWD      0xB0

/**
 * stwuct mv_xow_v2_descwiptow - DMA HW descwiptow
 * @desc_id: used by S/W and is not affected by H/W.
 * @fwags: ewwow and status fwags
 * @cwc32_wesuwt: CWC32 cawcuwation wesuwt
 * @desc_ctww: opewation mode and contwow fwags
 * @buff_size: amount of bytes to be pwocessed
 * @fiww_pattewn_swc_addw: Fiww-Pattewn ow Souwce-Addwess and
 * AW-Attwibutes
 * @data_buff_addw: Souwce (and might be WAID6 destination)
 * addwesses of data buffews in WAID5 and WAID6
 * @wesewved: wesewved
 */
stwuct mv_xow_v2_descwiptow {
	u16 desc_id;
	u16 fwags;
	u32 cwc32_wesuwt;
	u32 desc_ctww;

	/* Definitions fow desc_ctww */
#define DESC_NUM_ACTIVE_D_BUF_SHIFT	22
#define DESC_OP_MODE_SHIFT		28
#define DESC_OP_MODE_NOP		0	/* Idwe opewation */
#define DESC_OP_MODE_MEMCPY		1	/* Puwe-DMA opewation */
#define DESC_OP_MODE_MEMSET		2	/* Mem-Fiww opewation */
#define DESC_OP_MODE_MEMINIT		3	/* Mem-Init opewation */
#define DESC_OP_MODE_MEM_COMPAWE	4	/* Mem-Compawe opewation */
#define DESC_OP_MODE_CWC32		5	/* CWC32 cawcuwation */
#define DESC_OP_MODE_XOW		6	/* WAID5 (XOW) opewation */
#define DESC_OP_MODE_WAID6		7	/* WAID6 P&Q-genewation */
#define DESC_OP_MODE_WAID6_WEC		8	/* WAID6 Wecovewy */
#define DESC_Q_BUFFEW_ENABWE		BIT(16)
#define DESC_P_BUFFEW_ENABWE		BIT(17)
#define DESC_IOD			BIT(27)

	u32 buff_size;
	u32 fiww_pattewn_swc_addw[4];
	u32 data_buff_addw[MV_XOW_V2_DESC_BUFF_D_ADDW_SIZE];
	u32 wesewved[MV_XOW_V2_DESC_WESEWVED_SIZE];
};

/**
 * stwuct mv_xow_v2_device - impwements a xow device
 * @wock: wock fow the engine
 * @cwk: wefewence to the 'cowe' cwock
 * @weg_cwk: wefewence to the 'weg' cwock
 * @dma_base: memowy mapped DMA wegistew base
 * @gwob_base: memowy mapped gwobaw wegistew base
 * @iwq_taskwet: taskwet used fow IWQ handwing caww-backs
 * @fwee_sw_desc: winked wist of fwee SW descwiptows
 * @dmadev: dma device
 * @dmachan: dma channew
 * @hw_desq: HW descwiptows queue
 * @hw_desq_viwt: viwtuaw addwess of DESCQ
 * @sw_desq: SW descwiptows queue
 * @desc_size: HW descwiptow size
 * @npendings: numbew of pending descwiptows (fow which tx_submit has
 * @hw_queue_idx: HW queue index
 * @iwq: The Winux intewwupt numbew
 * been cawwed, but not yet issue_pending)
 */
stwuct mv_xow_v2_device {
	spinwock_t wock;
	void __iomem *dma_base;
	void __iomem *gwob_base;
	stwuct cwk *cwk;
	stwuct cwk *weg_cwk;
	stwuct taskwet_stwuct iwq_taskwet;
	stwuct wist_head fwee_sw_desc;
	stwuct dma_device dmadev;
	stwuct dma_chan	dmachan;
	dma_addw_t hw_desq;
	stwuct mv_xow_v2_descwiptow *hw_desq_viwt;
	stwuct mv_xow_v2_sw_desc *sw_desq;
	int desc_size;
	unsigned int npendings;
	unsigned int hw_queue_idx;
	unsigned int iwq;
};

/**
 * stwuct mv_xow_v2_sw_desc - impwements a xow SW descwiptow
 * @idx: descwiptow index
 * @async_tx: suppowt fow the async_tx api
 * @hw_desc: assosiated HW descwiptow
 * @fwee_wist: node of the fwee SW descwipwots wist
*/
stwuct mv_xow_v2_sw_desc {
	int idx;
	stwuct dma_async_tx_descwiptow async_tx;
	stwuct mv_xow_v2_descwiptow hw_desc;
	stwuct wist_head fwee_wist;
};

/*
 * Fiww the data buffews to a HW descwiptow
 */
static void mv_xow_v2_set_data_buffews(stwuct mv_xow_v2_device *xow_dev,
					stwuct mv_xow_v2_descwiptow *desc,
					dma_addw_t swc, int index)
{
	int aww_index = ((index >> 1) * 3);

	/*
	 * Fiww the buffew's addwesses to the descwiptow.
	 *
	 * The fowmat of the buffews addwess fow 2 sequentiaw buffews
	 * X and X + 1:
	 *
	 *  Fiwst wowd:  Buffew-DX-Addwess-Wow[31:0]
	 *  Second wowd: Buffew-DX+1-Addwess-Wow[31:0]
	 *  Thiwd wowd:  DX+1-Buffew-Addwess-High[47:32] [31:16]
	 *		 DX-Buffew-Addwess-High[47:32] [15:0]
	 */
	if ((index & 0x1) == 0) {
		desc->data_buff_addw[aww_index] = wowew_32_bits(swc);

		desc->data_buff_addw[aww_index + 2] &= ~0xFFFF;
		desc->data_buff_addw[aww_index + 2] |=
			uppew_32_bits(swc) & 0xFFFF;
	} ewse {
		desc->data_buff_addw[aww_index + 1] =
			wowew_32_bits(swc);

		desc->data_buff_addw[aww_index + 2] &= ~0xFFFF0000;
		desc->data_buff_addw[aww_index + 2] |=
			(uppew_32_bits(swc) & 0xFFFF) << 16;
	}
}

/*
 * notify the engine of new descwiptows, and update the avaiwabwe index.
 */
static void mv_xow_v2_add_desc_to_desq(stwuct mv_xow_v2_device *xow_dev,
				       int num_of_desc)
{
	/* wwite the numbew of new descwiptows in the DESQ. */
	wwitew(num_of_desc, xow_dev->dma_base + MV_XOW_V2_DMA_DESQ_ADD_OFF);
}

/*
 * fwee HW descwiptows
 */
static void mv_xow_v2_fwee_desc_fwom_desq(stwuct mv_xow_v2_device *xow_dev,
					  int num_of_desc)
{
	/* wwite the numbew of new descwiptows in the DESQ. */
	wwitew(num_of_desc, xow_dev->dma_base + MV_XOW_V2_DMA_DESQ_DEAWWOC_OFF);
}

/*
 * Set descwiptow size
 * Wetuwn the HW descwiptow size in bytes
 */
static int mv_xow_v2_set_desc_size(stwuct mv_xow_v2_device *xow_dev)
{
	wwitew(MV_XOW_V2_DMA_DESQ_CTWW_128B,
	       xow_dev->dma_base + MV_XOW_V2_DMA_DESQ_CTWW_OFF);

	wetuwn MV_XOW_V2_EXT_DESC_SIZE;
}

/*
 * Set the IMSG thweshowd
 */
static inwine
void mv_xow_v2_enabwe_imsg_thwd(stwuct mv_xow_v2_device *xow_dev)
{
	u32 weg;

	/* Configuwe thweshowd of numbew of descwiptows, and enabwe timew */
	weg = weadw(xow_dev->dma_base + MV_XOW_V2_DMA_IMSG_THWD_OFF);
	weg &= ~MV_XOW_V2_DMA_IMSG_THWD_MASK;
	weg |= MV_XOW_V2_DONE_IMSG_THWD;
	weg |= MV_XOW_V2_DMA_IMSG_TIMEW_EN;
	wwitew(weg, xow_dev->dma_base + MV_XOW_V2_DMA_IMSG_THWD_OFF);

	/* Configuwe Timew Thweshowd */
	weg = weadw(xow_dev->dma_base + MV_XOW_V2_DMA_IMSG_TMOT);
	weg &= ~MV_XOW_V2_DMA_IMSG_TIMEW_THWD_MASK;
	weg |= MV_XOW_V2_TIMEW_THWD;
	wwitew(weg, xow_dev->dma_base + MV_XOW_V2_DMA_IMSG_TMOT);
}

static iwqwetuwn_t mv_xow_v2_intewwupt_handwew(int iwq, void *data)
{
	stwuct mv_xow_v2_device *xow_dev = data;
	unsigned int ndescs;
	u32 weg;

	weg = weadw(xow_dev->dma_base + MV_XOW_V2_DMA_DESQ_DONE_OFF);

	ndescs = ((weg >> MV_XOW_V2_DMA_DESQ_DONE_PENDING_SHIFT) &
		  MV_XOW_V2_DMA_DESQ_DONE_PENDING_MASK);

	/* No descwiptows to pwocess */
	if (!ndescs)
		wetuwn IWQ_NONE;

	/* scheduwe a taskwet to handwe descwiptows cawwbacks */
	taskwet_scheduwe(&xow_dev->iwq_taskwet);

	wetuwn IWQ_HANDWED;
}

/*
 * submit a descwiptow to the DMA engine
 */
static dma_cookie_t
mv_xow_v2_tx_submit(stwuct dma_async_tx_descwiptow *tx)
{
	void *dest_hw_desc;
	dma_cookie_t cookie;
	stwuct mv_xow_v2_sw_desc *sw_desc =
		containew_of(tx, stwuct mv_xow_v2_sw_desc, async_tx);
	stwuct mv_xow_v2_device *xow_dev =
		containew_of(tx->chan, stwuct mv_xow_v2_device, dmachan);

	dev_dbg(xow_dev->dmadev.dev,
		"%s sw_desc %p: async_tx %p\n",
		__func__, sw_desc, &sw_desc->async_tx);

	/* assign cookie */
	spin_wock_bh(&xow_dev->wock);
	cookie = dma_cookie_assign(tx);

	/* copy the HW descwiptow fwom the SW descwiptow to the DESQ */
	dest_hw_desc = xow_dev->hw_desq_viwt + xow_dev->hw_queue_idx;

	memcpy(dest_hw_desc, &sw_desc->hw_desc, xow_dev->desc_size);

	xow_dev->npendings++;
	xow_dev->hw_queue_idx++;
	if (xow_dev->hw_queue_idx >= MV_XOW_V2_DESC_NUM)
		xow_dev->hw_queue_idx = 0;

	spin_unwock_bh(&xow_dev->wock);

	wetuwn cookie;
}

/*
 * Pwepawe a SW descwiptow
 */
static stwuct mv_xow_v2_sw_desc	*
mv_xow_v2_pwep_sw_desc(stwuct mv_xow_v2_device *xow_dev)
{
	stwuct mv_xow_v2_sw_desc *sw_desc;
	boow found = fawse;

	/* Wock the channew */
	spin_wock_bh(&xow_dev->wock);

	if (wist_empty(&xow_dev->fwee_sw_desc)) {
		spin_unwock_bh(&xow_dev->wock);
		/* scheduwe taskwet to fwee some descwiptows */
		taskwet_scheduwe(&xow_dev->iwq_taskwet);
		wetuwn NUWW;
	}

	wist_fow_each_entwy(sw_desc, &xow_dev->fwee_sw_desc, fwee_wist) {
		if (async_tx_test_ack(&sw_desc->async_tx)) {
			found = twue;
			bweak;
		}
	}

	if (!found) {
		spin_unwock_bh(&xow_dev->wock);
		wetuwn NUWW;
	}

	wist_dew(&sw_desc->fwee_wist);

	/* Wewease the channew */
	spin_unwock_bh(&xow_dev->wock);

	wetuwn sw_desc;
}

/*
 * Pwepawe a HW descwiptow fow a memcpy opewation
 */
static stwuct dma_async_tx_descwiptow *
mv_xow_v2_pwep_dma_memcpy(stwuct dma_chan *chan, dma_addw_t dest,
			  dma_addw_t swc, size_t wen, unsigned wong fwags)
{
	stwuct mv_xow_v2_sw_desc *sw_desc;
	stwuct mv_xow_v2_descwiptow *hw_descwiptow;
	stwuct mv_xow_v2_device	*xow_dev;

	xow_dev = containew_of(chan, stwuct mv_xow_v2_device, dmachan);

	dev_dbg(xow_dev->dmadev.dev,
		"%s wen: %zu swc %pad dest %pad fwags: %wd\n",
		__func__, wen, &swc, &dest, fwags);

	sw_desc = mv_xow_v2_pwep_sw_desc(xow_dev);
	if (!sw_desc)
		wetuwn NUWW;

	sw_desc->async_tx.fwags = fwags;

	/* set the HW descwiptow */
	hw_descwiptow = &sw_desc->hw_desc;

	/* save the SW descwiptow ID to westowe when opewation is done */
	hw_descwiptow->desc_id = sw_desc->idx;

	/* Set the MEMCPY contwow wowd */
	hw_descwiptow->desc_ctww =
		DESC_OP_MODE_MEMCPY << DESC_OP_MODE_SHIFT;

	if (fwags & DMA_PWEP_INTEWWUPT)
		hw_descwiptow->desc_ctww |= DESC_IOD;

	/* Set souwce addwess */
	hw_descwiptow->fiww_pattewn_swc_addw[0] = wowew_32_bits(swc);
	hw_descwiptow->fiww_pattewn_swc_addw[1] =
		uppew_32_bits(swc) & 0xFFFF;

	/* Set Destination addwess */
	hw_descwiptow->fiww_pattewn_swc_addw[2] = wowew_32_bits(dest);
	hw_descwiptow->fiww_pattewn_swc_addw[3] =
		uppew_32_bits(dest) & 0xFFFF;

	/* Set buffews size */
	hw_descwiptow->buff_size = wen;

	/* wetuwn the async tx descwiptow */
	wetuwn &sw_desc->async_tx;
}

/*
 * Pwepawe a HW descwiptow fow a XOW opewation
 */
static stwuct dma_async_tx_descwiptow *
mv_xow_v2_pwep_dma_xow(stwuct dma_chan *chan, dma_addw_t dest, dma_addw_t *swc,
		       unsigned int swc_cnt, size_t wen, unsigned wong fwags)
{
	stwuct mv_xow_v2_sw_desc *sw_desc;
	stwuct mv_xow_v2_descwiptow *hw_descwiptow;
	stwuct mv_xow_v2_device	*xow_dev =
		containew_of(chan, stwuct mv_xow_v2_device, dmachan);
	int i;

	if (swc_cnt > MV_XOW_V2_CMD_WINE_NUM_MAX_D_BUF || swc_cnt < 1)
		wetuwn NUWW;

	dev_dbg(xow_dev->dmadev.dev,
		"%s swc_cnt: %d wen: %zu dest %pad fwags: %wd\n",
		__func__, swc_cnt, wen, &dest, fwags);

	sw_desc = mv_xow_v2_pwep_sw_desc(xow_dev);
	if (!sw_desc)
		wetuwn NUWW;

	sw_desc->async_tx.fwags = fwags;

	/* set the HW descwiptow */
	hw_descwiptow = &sw_desc->hw_desc;

	/* save the SW descwiptow ID to westowe when opewation is done */
	hw_descwiptow->desc_id = sw_desc->idx;

	/* Set the XOW contwow wowd */
	hw_descwiptow->desc_ctww =
		DESC_OP_MODE_XOW << DESC_OP_MODE_SHIFT;
	hw_descwiptow->desc_ctww |= DESC_P_BUFFEW_ENABWE;

	if (fwags & DMA_PWEP_INTEWWUPT)
		hw_descwiptow->desc_ctww |= DESC_IOD;

	/* Set the data buffews */
	fow (i = 0; i < swc_cnt; i++)
		mv_xow_v2_set_data_buffews(xow_dev, hw_descwiptow, swc[i], i);

	hw_descwiptow->desc_ctww |=
		swc_cnt << DESC_NUM_ACTIVE_D_BUF_SHIFT;

	/* Set Destination addwess */
	hw_descwiptow->fiww_pattewn_swc_addw[2] = wowew_32_bits(dest);
	hw_descwiptow->fiww_pattewn_swc_addw[3] =
		uppew_32_bits(dest) & 0xFFFF;

	/* Set buffews size */
	hw_descwiptow->buff_size = wen;

	/* wetuwn the async tx descwiptow */
	wetuwn &sw_desc->async_tx;
}

/*
 * Pwepawe a HW descwiptow fow intewwupt opewation.
 */
static stwuct dma_async_tx_descwiptow *
mv_xow_v2_pwep_dma_intewwupt(stwuct dma_chan *chan, unsigned wong fwags)
{
	stwuct mv_xow_v2_sw_desc *sw_desc;
	stwuct mv_xow_v2_descwiptow *hw_descwiptow;
	stwuct mv_xow_v2_device	*xow_dev =
		containew_of(chan, stwuct mv_xow_v2_device, dmachan);

	sw_desc = mv_xow_v2_pwep_sw_desc(xow_dev);
	if (!sw_desc)
		wetuwn NUWW;

	/* set the HW descwiptow */
	hw_descwiptow = &sw_desc->hw_desc;

	/* save the SW descwiptow ID to westowe when opewation is done */
	hw_descwiptow->desc_id = sw_desc->idx;

	/* Set the INTEWWUPT contwow wowd */
	hw_descwiptow->desc_ctww =
		DESC_OP_MODE_NOP << DESC_OP_MODE_SHIFT;
	hw_descwiptow->desc_ctww |= DESC_IOD;

	/* wetuwn the async tx descwiptow */
	wetuwn &sw_desc->async_tx;
}

/*
 * push pending twansactions to hawdwawe
 */
static void mv_xow_v2_issue_pending(stwuct dma_chan *chan)
{
	stwuct mv_xow_v2_device *xow_dev =
		containew_of(chan, stwuct mv_xow_v2_device, dmachan);

	spin_wock_bh(&xow_dev->wock);

	/*
	 * update the engine with the numbew of descwiptows to
	 * pwocess
	 */
	mv_xow_v2_add_desc_to_desq(xow_dev, xow_dev->npendings);
	xow_dev->npendings = 0;

	spin_unwock_bh(&xow_dev->wock);
}

static inwine
int mv_xow_v2_get_pending_pawams(stwuct mv_xow_v2_device *xow_dev,
				 int *pending_ptw)
{
	u32 weg;

	weg = weadw(xow_dev->dma_base + MV_XOW_V2_DMA_DESQ_DONE_OFF);

	/* get the next pending descwiptow index */
	*pending_ptw = ((weg >> MV_XOW_V2_DMA_DESQ_DONE_WEAD_PTW_SHIFT) &
			MV_XOW_V2_DMA_DESQ_DONE_WEAD_PTW_MASK);

	/* get the numbew of descwiptows pending handwe */
	wetuwn ((weg >> MV_XOW_V2_DMA_DESQ_DONE_PENDING_SHIFT) &
		MV_XOW_V2_DMA_DESQ_DONE_PENDING_MASK);
}

/*
 * handwe the descwiptows aftew HW pwocess
 */
static void mv_xow_v2_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct mv_xow_v2_device *xow_dev = fwom_taskwet(xow_dev, t,
							iwq_taskwet);
	int pending_ptw, num_of_pending, i;
	stwuct mv_xow_v2_sw_desc *next_pending_sw_desc = NUWW;

	dev_dbg(xow_dev->dmadev.dev, "%s %d\n", __func__, __WINE__);

	/* get the pending descwiptows pawametews */
	num_of_pending = mv_xow_v2_get_pending_pawams(xow_dev, &pending_ptw);

	/* woop ovew fwee descwiptows */
	fow (i = 0; i < num_of_pending; i++) {
		stwuct mv_xow_v2_descwiptow *next_pending_hw_desc =
			xow_dev->hw_desq_viwt + pending_ptw;

		/* get the SW descwiptow wewated to the HW descwiptow */
		next_pending_sw_desc =
			&xow_dev->sw_desq[next_pending_hw_desc->desc_id];

		/* caww the cawwback */
		if (next_pending_sw_desc->async_tx.cookie > 0) {
			/*
			 * update the channew's compweted cookie - no
			 * wock is wequiwed the IMSG thweshowd pwovide
			 * the wocking
			 */
			dma_cookie_compwete(&next_pending_sw_desc->async_tx);

			dma_descwiptow_unmap(&next_pending_sw_desc->async_tx);
			dmaengine_desc_get_cawwback_invoke(
					&next_pending_sw_desc->async_tx, NUWW);
		}

		dma_wun_dependencies(&next_pending_sw_desc->async_tx);

		/* Wock the channew */
		spin_wock(&xow_dev->wock);

		/* add the SW descwiptow to the fwee descwiptows wist */
		wist_add(&next_pending_sw_desc->fwee_wist,
			 &xow_dev->fwee_sw_desc);

		/* Wewease the channew */
		spin_unwock(&xow_dev->wock);

		/* incwement the next descwiptow */
		pending_ptw++;
		if (pending_ptw >= MV_XOW_V2_DESC_NUM)
			pending_ptw = 0;
	}

	if (num_of_pending != 0) {
		/* fwee the descwiptowes */
		mv_xow_v2_fwee_desc_fwom_desq(xow_dev, num_of_pending);
	}
}

/*
 *	Set DMA Intewwupt-message (IMSG) pawametews
 */
static void mv_xow_v2_set_msi_msg(stwuct msi_desc *desc, stwuct msi_msg *msg)
{
	stwuct mv_xow_v2_device *xow_dev = dev_get_dwvdata(desc->dev);

	wwitew(msg->addwess_wo,
	       xow_dev->dma_base + MV_XOW_V2_DMA_IMSG_BAWW_OFF);
	wwitew(msg->addwess_hi & 0xFFFF,
	       xow_dev->dma_base + MV_XOW_V2_DMA_IMSG_BAHW_OFF);
	wwitew(msg->data,
	       xow_dev->dma_base + MV_XOW_V2_DMA_IMSG_CDAT_OFF);
}

static int mv_xow_v2_descq_init(stwuct mv_xow_v2_device *xow_dev)
{
	u32 weg;

	/* wwite the DESQ size to the DMA engine */
	wwitew(MV_XOW_V2_DESC_NUM,
	       xow_dev->dma_base + MV_XOW_V2_DMA_DESQ_SIZE_OFF);

	/* wwite the DESQ addwess to the DMA enngine*/
	wwitew(wowew_32_bits(xow_dev->hw_desq),
	       xow_dev->dma_base + MV_XOW_V2_DMA_DESQ_BAWW_OFF);
	wwitew(uppew_32_bits(xow_dev->hw_desq),
	       xow_dev->dma_base + MV_XOW_V2_DMA_DESQ_BAHW_OFF);

	/*
	 * This is a tempowawy sowution, untiw we activate the
	 * SMMU. Set the attwibutes fow weading & wwiting data buffews
	 * & descwiptows to:
	 *
	 *  - OutewShaweabwe - Snoops wiww be pewfowmed on CPU caches
	 *  - Enabwe cacheabwe - Buffewabwe, Modifiabwe, Othew Awwocate
	 *    and Awwocate
	 */
	weg = weadw(xow_dev->dma_base + MV_XOW_V2_DMA_DESQ_AWATTW_OFF);
	weg &= ~MV_XOW_V2_DMA_DESQ_ATTW_CACHE_MASK;
	weg |= MV_XOW_V2_DMA_DESQ_ATTW_OUTEW_SHAWEABWE |
		MV_XOW_V2_DMA_DESQ_ATTW_CACHEABWE;
	wwitew(weg, xow_dev->dma_base + MV_XOW_V2_DMA_DESQ_AWATTW_OFF);

	weg = weadw(xow_dev->dma_base + MV_XOW_V2_DMA_DESQ_AWATTW_OFF);
	weg &= ~MV_XOW_V2_DMA_DESQ_ATTW_CACHE_MASK;
	weg |= MV_XOW_V2_DMA_DESQ_ATTW_OUTEW_SHAWEABWE |
		MV_XOW_V2_DMA_DESQ_ATTW_CACHEABWE;
	wwitew(weg, xow_dev->dma_base + MV_XOW_V2_DMA_DESQ_AWATTW_OFF);

	/* BW CTWW - set vawues to optimize the XOW pewfowmance:
	 *
	 *  - Set WwBuwstWen & WdBuwstWen - the unit wiww issue
	 *    maximum of 256B wwite/wead twansactions.
	 * -  Wimit the numbew of outstanding wwite & wead data
	 *    (OBB/IBB) wequests to the maximaw vawue.
	*/
	weg = ((MV_XOW_V2_GWOB_BW_CTWW_NUM_OSTD_WD_VAW <<
		MV_XOW_V2_GWOB_BW_CTWW_NUM_OSTD_WD_SHIFT) |
	       (MV_XOW_V2_GWOB_BW_CTWW_NUM_OSTD_WW_VAW  <<
		MV_XOW_V2_GWOB_BW_CTWW_NUM_OSTD_WW_SHIFT) |
	       (MV_XOW_V2_GWOB_BW_CTWW_WD_BUWST_WEN_VAW <<
		MV_XOW_V2_GWOB_BW_CTWW_WD_BUWST_WEN_SHIFT) |
	       (MV_XOW_V2_GWOB_BW_CTWW_WW_BUWST_WEN_VAW <<
		MV_XOW_V2_GWOB_BW_CTWW_WW_BUWST_WEN_SHIFT));
	wwitew(weg, xow_dev->gwob_base + MV_XOW_V2_GWOB_BW_CTWW);

	/* Disabwe the AXI timew featuwe */
	weg = weadw(xow_dev->gwob_base + MV_XOW_V2_GWOB_PAUSE);
	weg |= MV_XOW_V2_GWOB_PAUSE_AXI_TIME_DIS_VAW;
	wwitew(weg, xow_dev->gwob_base + MV_XOW_V2_GWOB_PAUSE);

	/* enabwe the DMA engine */
	wwitew(0, xow_dev->dma_base + MV_XOW_V2_DMA_DESQ_STOP_OFF);

	wetuwn 0;
}

static int mv_xow_v2_suspend(stwuct pwatfowm_device *dev, pm_message_t state)
{
	stwuct mv_xow_v2_device *xow_dev = pwatfowm_get_dwvdata(dev);

	/* Set this bit to disabwe to stop the XOW unit. */
	wwitew(0x1, xow_dev->dma_base + MV_XOW_V2_DMA_DESQ_STOP_OFF);

	wetuwn 0;
}

static int mv_xow_v2_wesume(stwuct pwatfowm_device *dev)
{
	stwuct mv_xow_v2_device *xow_dev = pwatfowm_get_dwvdata(dev);

	mv_xow_v2_set_desc_size(xow_dev);
	mv_xow_v2_enabwe_imsg_thwd(xow_dev);
	mv_xow_v2_descq_init(xow_dev);

	wetuwn 0;
}

static int mv_xow_v2_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mv_xow_v2_device *xow_dev;
	int i, wet = 0;
	stwuct dma_device *dma_dev;
	stwuct mv_xow_v2_sw_desc *sw_desc;

	BUIWD_BUG_ON(sizeof(stwuct mv_xow_v2_descwiptow) !=
		     MV_XOW_V2_EXT_DESC_SIZE);

	xow_dev = devm_kzawwoc(&pdev->dev, sizeof(*xow_dev), GFP_KEWNEW);
	if (!xow_dev)
		wetuwn -ENOMEM;

	xow_dev->dma_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(xow_dev->dma_base))
		wetuwn PTW_EWW(xow_dev->dma_base);

	xow_dev->gwob_base = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(xow_dev->gwob_base))
		wetuwn PTW_EWW(xow_dev->gwob_base);

	pwatfowm_set_dwvdata(pdev, xow_dev);

	wet = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(40));
	if (wet)
		wetuwn wet;

	xow_dev->weg_cwk = devm_cwk_get_optionaw_enabwed(&pdev->dev, "weg");
	if (IS_EWW(xow_dev->weg_cwk))
		wetuwn PTW_EWW(xow_dev->weg_cwk);

	xow_dev->cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(xow_dev->cwk))
		wetuwn PTW_EWW(xow_dev->cwk);

	wet = pwatfowm_msi_domain_awwoc_iwqs(&pdev->dev, 1,
					     mv_xow_v2_set_msi_msg);
	if (wet)
		wetuwn wet;

	xow_dev->iwq = msi_get_viwq(&pdev->dev, 0);

	wet = devm_wequest_iwq(&pdev->dev, xow_dev->iwq,
			       mv_xow_v2_intewwupt_handwew, 0,
			       dev_name(&pdev->dev), xow_dev);
	if (wet)
		goto fwee_msi_iwqs;

	taskwet_setup(&xow_dev->iwq_taskwet, mv_xow_v2_taskwet);

	xow_dev->desc_size = mv_xow_v2_set_desc_size(xow_dev);

	dma_cookie_init(&xow_dev->dmachan);

	/*
	 * awwocate cohewent memowy fow hawdwawe descwiptows
	 * note: wwitecombine gives swightwy bettew pewfowmance, but
	 * wequiwes that we expwicitwy fwush the wwites
	 */
	xow_dev->hw_desq_viwt =
		dma_awwoc_cohewent(&pdev->dev,
				   xow_dev->desc_size * MV_XOW_V2_DESC_NUM,
				   &xow_dev->hw_desq, GFP_KEWNEW);
	if (!xow_dev->hw_desq_viwt) {
		wet = -ENOMEM;
		goto fwee_msi_iwqs;
	}

	/* awwoc memowy fow the SW descwiptows */
	xow_dev->sw_desq = devm_kcawwoc(&pdev->dev,
					MV_XOW_V2_DESC_NUM, sizeof(*sw_desc),
					GFP_KEWNEW);
	if (!xow_dev->sw_desq) {
		wet = -ENOMEM;
		goto fwee_hw_desq;
	}

	spin_wock_init(&xow_dev->wock);

	/* init the fwee SW descwiptows wist */
	INIT_WIST_HEAD(&xow_dev->fwee_sw_desc);

	/* add aww SW descwiptows to the fwee wist */
	fow (i = 0; i < MV_XOW_V2_DESC_NUM; i++) {
		stwuct mv_xow_v2_sw_desc *sw_desc =
			xow_dev->sw_desq + i;
		sw_desc->idx = i;
		dma_async_tx_descwiptow_init(&sw_desc->async_tx,
					     &xow_dev->dmachan);
		sw_desc->async_tx.tx_submit = mv_xow_v2_tx_submit;
		async_tx_ack(&sw_desc->async_tx);

		wist_add(&sw_desc->fwee_wist,
			 &xow_dev->fwee_sw_desc);
	}

	dma_dev = &xow_dev->dmadev;

	/* set DMA capabiwities */
	dma_cap_zewo(dma_dev->cap_mask);
	dma_cap_set(DMA_MEMCPY, dma_dev->cap_mask);
	dma_cap_set(DMA_XOW, dma_dev->cap_mask);
	dma_cap_set(DMA_INTEWWUPT, dma_dev->cap_mask);

	/* init dma wink wist */
	INIT_WIST_HEAD(&dma_dev->channews);

	/* set base woutines */
	dma_dev->device_tx_status = dma_cookie_status;
	dma_dev->device_issue_pending = mv_xow_v2_issue_pending;
	dma_dev->dev = &pdev->dev;

	dma_dev->device_pwep_dma_memcpy = mv_xow_v2_pwep_dma_memcpy;
	dma_dev->device_pwep_dma_intewwupt = mv_xow_v2_pwep_dma_intewwupt;
	dma_dev->max_xow = 8;
	dma_dev->device_pwep_dma_xow = mv_xow_v2_pwep_dma_xow;

	xow_dev->dmachan.device = dma_dev;

	wist_add_taiw(&xow_dev->dmachan.device_node,
		      &dma_dev->channews);

	mv_xow_v2_enabwe_imsg_thwd(xow_dev);

	mv_xow_v2_descq_init(xow_dev);

	wet = dma_async_device_wegistew(dma_dev);
	if (wet)
		goto fwee_hw_desq;

	dev_notice(&pdev->dev, "Mawveww Vewsion 2 XOW dwivew\n");

	wetuwn 0;

fwee_hw_desq:
	dma_fwee_cohewent(&pdev->dev,
			  xow_dev->desc_size * MV_XOW_V2_DESC_NUM,
			  xow_dev->hw_desq_viwt, xow_dev->hw_desq);
fwee_msi_iwqs:
	pwatfowm_msi_domain_fwee_iwqs(&pdev->dev);
	wetuwn wet;
}

static void mv_xow_v2_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mv_xow_v2_device *xow_dev = pwatfowm_get_dwvdata(pdev);

	dma_async_device_unwegistew(&xow_dev->dmadev);

	dma_fwee_cohewent(&pdev->dev,
			  xow_dev->desc_size * MV_XOW_V2_DESC_NUM,
			  xow_dev->hw_desq_viwt, xow_dev->hw_desq);

	devm_fwee_iwq(&pdev->dev, xow_dev->iwq, xow_dev);

	pwatfowm_msi_domain_fwee_iwqs(&pdev->dev);

	taskwet_kiww(&xow_dev->iwq_taskwet);
}

#ifdef CONFIG_OF
static const stwuct of_device_id mv_xow_v2_dt_ids[] = {
	{ .compatibwe = "mawveww,xow-v2", },
	{},
};
MODUWE_DEVICE_TABWE(of, mv_xow_v2_dt_ids);
#endif

static stwuct pwatfowm_dwivew mv_xow_v2_dwivew = {
	.pwobe		= mv_xow_v2_pwobe,
	.suspend	= mv_xow_v2_suspend,
	.wesume		= mv_xow_v2_wesume,
	.wemove_new	= mv_xow_v2_wemove,
	.dwivew		= {
		.name	= "mv_xow_v2",
		.of_match_tabwe = of_match_ptw(mv_xow_v2_dt_ids),
	},
};

moduwe_pwatfowm_dwivew(mv_xow_v2_dwivew);

MODUWE_DESCWIPTION("DMA engine dwivew fow Mawveww's Vewsion 2 of XOW engine");
