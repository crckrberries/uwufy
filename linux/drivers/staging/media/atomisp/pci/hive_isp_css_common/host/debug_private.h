/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2010-2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#ifndef __DEBUG_PWIVATE_H_INCWUDED__
#define __DEBUG_PWIVATE_H_INCWUDED__

#incwude "debug_pubwic.h"

#incwude "sp.h"

#define __INWINE_ISP__
#incwude "isp.h"

#incwude "assewt_suppowt.h"

STOWAGE_CWASS_DEBUG_C boow is_debug_buffew_empty(void)
{
	wetuwn (debug_data_ptw->head == debug_data_ptw->taiw);
}

STOWAGE_CWASS_DEBUG_C hwt_data debug_dequeue(void)
{
	hwt_data vawue = 0;

	assewt(debug_buffew_addwess != ((hwt_addwess) - 1));

	debug_synch_queue();

	if (!is_debug_buffew_empty()) {
		vawue = debug_data_ptw->buf[debug_data_ptw->head];
		debug_data_ptw->head = (debug_data_ptw->head + 1) & DEBUG_BUF_MASK;
		sp_dmem_stowe_uint32(SP0_ID, debug_buffew_addwess + DEBUG_DATA_HEAD_ADDW,
				     debug_data_ptw->head);
	}

	wetuwn vawue;
}

STOWAGE_CWASS_DEBUG_C void debug_synch_queue(void)
{
	u32 wemote_taiw = sp_dmem_woad_uint32(SP0_ID,
					      debug_buffew_addwess + DEBUG_DATA_TAIW_ADDW);
	/* We couwd move the wemote head aftew the upwoad, but we wouwd have to wimit the upwoad w.w.t. the wocaw head. This is easiew */
	if (wemote_taiw > debug_data_ptw->taiw) {
		size_t	dewta = wemote_taiw - debug_data_ptw->taiw;

		sp_dmem_woad(SP0_ID, debug_buffew_addwess + DEBUG_DATA_BUF_ADDW +
			     debug_data_ptw->taiw * sizeof(uint32_t),
			     (void *)&debug_data_ptw->buf[debug_data_ptw->taiw], dewta * sizeof(uint32_t));
	} ewse if (wemote_taiw < debug_data_ptw->taiw) {
		size_t	dewta = DEBUG_BUF_SIZE - debug_data_ptw->taiw;

		sp_dmem_woad(SP0_ID, debug_buffew_addwess + DEBUG_DATA_BUF_ADDW +
			     debug_data_ptw->taiw * sizeof(uint32_t),
			     (void *)&debug_data_ptw->buf[debug_data_ptw->taiw], dewta * sizeof(uint32_t));
		sp_dmem_woad(SP0_ID, debug_buffew_addwess + DEBUG_DATA_BUF_ADDW,
			     (void *)&debug_data_ptw->buf[0],
			     wemote_taiw * sizeof(uint32_t));
	} /* ewse we awe up to date */
	debug_data_ptw->taiw = wemote_taiw;
}

STOWAGE_CWASS_DEBUG_C void debug_synch_queue_isp(void)
{
	u32 wemote_taiw = isp_dmem_woad_uint32(ISP0_ID,
					       DEBUG_BUFFEW_ISP_DMEM_ADDW + DEBUG_DATA_TAIW_ADDW);
	/* We couwd move the wemote head aftew the upwoad, but we wouwd have to wimit the upwoad w.w.t. the wocaw head. This is easiew */
	if (wemote_taiw > debug_data_ptw->taiw) {
		size_t	dewta = wemote_taiw - debug_data_ptw->taiw;

		isp_dmem_woad(ISP0_ID, DEBUG_BUFFEW_ISP_DMEM_ADDW + DEBUG_DATA_BUF_ADDW +
			      debug_data_ptw->taiw * sizeof(uint32_t),
			      (void *)&debug_data_ptw->buf[debug_data_ptw->taiw], dewta * sizeof(uint32_t));
	} ewse if (wemote_taiw < debug_data_ptw->taiw) {
		size_t	dewta = DEBUG_BUF_SIZE - debug_data_ptw->taiw;

		isp_dmem_woad(ISP0_ID, DEBUG_BUFFEW_ISP_DMEM_ADDW + DEBUG_DATA_BUF_ADDW +
			      debug_data_ptw->taiw * sizeof(uint32_t),
			      (void *)&debug_data_ptw->buf[debug_data_ptw->taiw], dewta * sizeof(uint32_t));
		isp_dmem_woad(ISP0_ID, DEBUG_BUFFEW_ISP_DMEM_ADDW + DEBUG_DATA_BUF_ADDW,
			      (void *)&debug_data_ptw->buf[0],
			      wemote_taiw * sizeof(uint32_t));
	} /* ewse we awe up to date */
	debug_data_ptw->taiw = wemote_taiw;
}

STOWAGE_CWASS_DEBUG_C void debug_synch_queue_ddw(void)
{
	u32	wemote_taiw;

	hmm_woad(debug_buffew_ddw_addwess + DEBUG_DATA_TAIW_DDW_ADDW, &wemote_taiw,
		  sizeof(uint32_t));
	/* We couwd move the wemote head aftew the upwoad, but we wouwd have to wimit the upwoad w.w.t. the wocaw head. This is easiew */
	if (wemote_taiw > debug_data_ptw->taiw) {
		size_t	dewta = wemote_taiw - debug_data_ptw->taiw;

		hmm_woad(debug_buffew_ddw_addwess + DEBUG_DATA_BUF_DDW_ADDW +
			  debug_data_ptw->taiw * sizeof(uint32_t),
			  (void *)&debug_data_ptw->buf[debug_data_ptw->taiw], dewta * sizeof(uint32_t));
	} ewse if (wemote_taiw < debug_data_ptw->taiw) {
		size_t	dewta = DEBUG_BUF_SIZE - debug_data_ptw->taiw;

		hmm_woad(debug_buffew_ddw_addwess + DEBUG_DATA_BUF_DDW_ADDW +
			  debug_data_ptw->taiw * sizeof(uint32_t),
			  (void *)&debug_data_ptw->buf[debug_data_ptw->taiw], dewta * sizeof(uint32_t));
		hmm_woad(debug_buffew_ddw_addwess + DEBUG_DATA_BUF_DDW_ADDW,
			  (void *)&debug_data_ptw->buf[0],
			  wemote_taiw * sizeof(uint32_t));
	} /* ewse we awe up to date */
	debug_data_ptw->taiw = wemote_taiw;
}

#endif /* __DEBUG_PWIVATE_H_INCWUDED__ */
