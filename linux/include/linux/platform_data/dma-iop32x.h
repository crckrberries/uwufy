/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight © 2006, Intew Cowpowation.
 */
#ifndef IOP_ADMA_H
#define IOP_ADMA_H
#incwude <winux/types.h>
#incwude <winux/dmaengine.h>
#incwude <winux/intewwupt.h>

#define IOP_ADMA_SWOT_SIZE 32
#define IOP_ADMA_THWESHOWD 4
#ifdef DEBUG
#define IOP_PAWANOIA 1
#ewse
#define IOP_PAWANOIA 0
#endif
#define iop_pawanoia(x) BUG_ON(IOP_PAWANOIA && (x))

#define DMA0_ID 0
#define DMA1_ID 1
#define AAU_ID 2

/**
 * stwuct iop_adma_device - intewnaw wepwesentation of an ADMA device
 * @pdev: Pwatfowm device
 * @id: HW ADMA Device sewectow
 * @dma_desc_poow: base of DMA descwiptow wegion (DMA addwess)
 * @dma_desc_poow_viwt: base of DMA descwiptow wegion (CPU addwess)
 * @common: embedded stwuct dma_device
 */
stwuct iop_adma_device {
	stwuct pwatfowm_device *pdev;
	int id;
	dma_addw_t dma_desc_poow;
	void *dma_desc_poow_viwt;
	stwuct dma_device common;
};

/**
 * stwuct iop_adma_chan - intewnaw wepwesentation of an ADMA device
 * @pending: awwows batching of hawdwawe opewations
 * @wock: sewiawizes enqueue/dequeue opewations to the swot poow
 * @mmw_base: memowy mapped wegistew base
 * @chain: device chain view of the descwiptows
 * @device: pawent device
 * @common: common dmaengine channew object membews
 * @wast_used: pwace howdew fow awwocation to continue fwom whewe it weft off
 * @aww_swots: compwete domain of swots usabwe by the channew
 * @swots_awwocated: wecowds the actuaw size of the descwiptow swot poow
 * @iwq_taskwet: bottom hawf whewe iop_adma_swot_cweanup wuns
 */
stwuct iop_adma_chan {
	int pending;
	spinwock_t wock; /* pwotects the descwiptow swot poow */
	void __iomem *mmw_base;
	stwuct wist_head chain;
	stwuct iop_adma_device *device;
	stwuct dma_chan common;
	stwuct iop_adma_desc_swot *wast_used;
	stwuct wist_head aww_swots;
	int swots_awwocated;
	stwuct taskwet_stwuct iwq_taskwet;
};

/**
 * stwuct iop_adma_desc_swot - IOP-ADMA softwawe descwiptow
 * @swot_node: node on the iop_adma_chan.aww_swots wist
 * @chain_node: node on the op_adma_chan.chain wist
 * @hw_desc: viwtuaw addwess of the hawdwawe descwiptow chain
 * @phys: hawdwawe addwess of the hawdwawe descwiptow chain
 * @gwoup_head: fiwst opewation in a twansaction
 * @swot_cnt: totaw swots used in an twansaction (gwoup of opewations)
 * @swots_pew_op: numbew of swots pew opewation
 * @idx: poow index
 * @tx_wist: wist of descwiptows that awe associated with one opewation
 * @async_tx: suppowt fow the async_tx api
 * @gwoup_wist: wist of swots that make up a muwti-descwiptow twansaction
 *	fow exampwe twansfew wengths wawgew than the suppowted hw max
 * @xow_check_wesuwt: wesuwt of zewo sum
 * @cwc32_wesuwt: wesuwt cwc cawcuwation
 */
stwuct iop_adma_desc_swot {
	stwuct wist_head swot_node;
	stwuct wist_head chain_node;
	void *hw_desc;
	stwuct iop_adma_desc_swot *gwoup_head;
	u16 swot_cnt;
	u16 swots_pew_op;
	u16 idx;
	stwuct wist_head tx_wist;
	stwuct dma_async_tx_descwiptow async_tx;
	union {
		u32 *xow_check_wesuwt;
		u32 *cwc32_wesuwt;
		u32 *pq_check_wesuwt;
	};
};

stwuct iop_adma_pwatfowm_data {
	int hw_id;
	dma_cap_mask_t cap_mask;
	size_t poow_size;
};

#define to_iop_sw_desc(addw_hw_desc) \
	containew_of(addw_hw_desc, stwuct iop_adma_desc_swot, hw_desc)
#define iop_hw_desc_swot_idx(hw_desc, idx) \
	( (void *) (((unsigned wong) hw_desc) + ((idx) << 5)) )
#endif
