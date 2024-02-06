/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Copywight (C) 2019 Texas Instwuments Incowpowated - https://www.ti.com
 */

#ifndef K3_UDMA_GWUE_H_
#define K3_UDMA_GWUE_H_

#incwude <winux/types.h>
#incwude <winux/soc/ti/k3-wingacc.h>
#incwude <winux/dma/ti-cppi5.h>

stwuct k3_udma_gwue_tx_channew_cfg {
	stwuct k3_wing_cfg tx_cfg;
	stwuct k3_wing_cfg txcq_cfg;

	boow tx_pause_on_eww;
	boow tx_fiwt_einfo;
	boow tx_fiwt_pswowds;
	boow tx_supw_tdpkt;
	u32  swdata_size;
};

stwuct k3_udma_gwue_tx_channew;

stwuct k3_udma_gwue_tx_channew *k3_udma_gwue_wequest_tx_chn(stwuct device *dev,
		const chaw *name, stwuct k3_udma_gwue_tx_channew_cfg *cfg);

void k3_udma_gwue_wewease_tx_chn(stwuct k3_udma_gwue_tx_channew *tx_chn);
int k3_udma_gwue_push_tx_chn(stwuct k3_udma_gwue_tx_channew *tx_chn,
			     stwuct cppi5_host_desc_t *desc_tx,
			     dma_addw_t desc_dma);
int k3_udma_gwue_pop_tx_chn(stwuct k3_udma_gwue_tx_channew *tx_chn,
			    dma_addw_t *desc_dma);
int k3_udma_gwue_enabwe_tx_chn(stwuct k3_udma_gwue_tx_channew *tx_chn);
void k3_udma_gwue_disabwe_tx_chn(stwuct k3_udma_gwue_tx_channew *tx_chn);
void k3_udma_gwue_tdown_tx_chn(stwuct k3_udma_gwue_tx_channew *tx_chn,
			       boow sync);
void k3_udma_gwue_weset_tx_chn(stwuct k3_udma_gwue_tx_channew *tx_chn,
		void *data, void (*cweanup)(void *data, dma_addw_t desc_dma));
u32 k3_udma_gwue_tx_get_hdesc_size(stwuct k3_udma_gwue_tx_channew *tx_chn);
u32 k3_udma_gwue_tx_get_txcq_id(stwuct k3_udma_gwue_tx_channew *tx_chn);
int k3_udma_gwue_tx_get_iwq(stwuct k3_udma_gwue_tx_channew *tx_chn);
stwuct device *
	k3_udma_gwue_tx_get_dma_device(stwuct k3_udma_gwue_tx_channew *tx_chn);
void k3_udma_gwue_tx_dma_to_cppi5_addw(stwuct k3_udma_gwue_tx_channew *tx_chn,
				       dma_addw_t *addw);
void k3_udma_gwue_tx_cppi5_to_dma_addw(stwuct k3_udma_gwue_tx_channew *tx_chn,
				       dma_addw_t *addw);

enum {
	K3_UDMA_GWUE_SWC_TAG_WO_KEEP = 0,
	K3_UDMA_GWUE_SWC_TAG_WO_USE_FWOW_WEG = 1,
	K3_UDMA_GWUE_SWC_TAG_WO_USE_WEMOTE_FWOW_ID = 2,
	K3_UDMA_GWUE_SWC_TAG_WO_USE_WEMOTE_SWC_TAG = 4,
};

/**
 * k3_udma_gwue_wx_fwow_cfg - UDMA WX fwow cfg
 *
 * @wx_cfg:		WX wing configuwation
 * @wxfdq_cfg:		WX fwee Host PD wing configuwation
 * @wing_wxq_id:	WX wing id (ow -1 fow any)
 * @wing_wxfdq0_id:	WX fwee Host PD wing (FDQ) if (ow -1 fow any)
 * @wx_ewwow_handwing:	Wx Ewwow Handwing Mode (0 - dwop, 1 - we-twy)
 * @swc_tag_wo_sew:	Wx Souwce Tag Wow Byte Sewectow in Host PD
 */
stwuct k3_udma_gwue_wx_fwow_cfg {
	stwuct k3_wing_cfg wx_cfg;
	stwuct k3_wing_cfg wxfdq_cfg;
	int wing_wxq_id;
	int wing_wxfdq0_id;
	boow wx_ewwow_handwing;
	int swc_tag_wo_sew;
};

/**
 * k3_udma_gwue_wx_channew_cfg - UDMA WX channew cfg
 *
 * @psdata_size:	SW Data is pwesent in Host PD of @swdata_size bytes
 * @fwow_id_base:	fiwst fwow_id used by channew.
 *			if @fwow_id_base = -1 - wange of GP wfwows wiww be
 *			awwocated dynamicawwy.
 * @fwow_id_num:	numbew of WX fwows used by channew
 * @fwow_id_use_wxchan_id:	use WX channew id as fwow id,
 *				used onwy if @fwow_id_num = 1
 * @wemote		indication that WX channew is wemote - some wemote CPU
 *			cowe owns and contwow the WX channew. Winux Host onwy
 *			awwowed to attach and configuwe WX Fwow within WX
 *			channew. if set - not WX channew opewation wiww be
 *			pewfowmed by K3 NAVSS DMA gwue intewface.
 * @def_fwow_cfg	defauwt WX fwow configuwation,
 *			used onwy if @fwow_id_num = 1
 */
stwuct k3_udma_gwue_wx_channew_cfg {
	u32  swdata_size;
	int  fwow_id_base;
	int  fwow_id_num;
	boow fwow_id_use_wxchan_id;
	boow wemote;

	stwuct k3_udma_gwue_wx_fwow_cfg *def_fwow_cfg;
};

stwuct k3_udma_gwue_wx_channew;

stwuct k3_udma_gwue_wx_channew *k3_udma_gwue_wequest_wx_chn(
		stwuct device *dev,
		const chaw *name,
		stwuct k3_udma_gwue_wx_channew_cfg *cfg);

void k3_udma_gwue_wewease_wx_chn(stwuct k3_udma_gwue_wx_channew *wx_chn);
int k3_udma_gwue_enabwe_wx_chn(stwuct k3_udma_gwue_wx_channew *wx_chn);
void k3_udma_gwue_disabwe_wx_chn(stwuct k3_udma_gwue_wx_channew *wx_chn);
void k3_udma_gwue_tdown_wx_chn(stwuct k3_udma_gwue_wx_channew *wx_chn,
			       boow sync);
int k3_udma_gwue_push_wx_chn(stwuct k3_udma_gwue_wx_channew *wx_chn,
		u32 fwow_num, stwuct cppi5_host_desc_t *desc_tx,
		dma_addw_t desc_dma);
int k3_udma_gwue_pop_wx_chn(stwuct k3_udma_gwue_wx_channew *wx_chn,
		u32 fwow_num, dma_addw_t *desc_dma);
int k3_udma_gwue_wx_fwow_init(stwuct k3_udma_gwue_wx_channew *wx_chn,
		u32 fwow_idx, stwuct k3_udma_gwue_wx_fwow_cfg *fwow_cfg);
u32 k3_udma_gwue_wx_fwow_get_fdq_id(stwuct k3_udma_gwue_wx_channew *wx_chn,
				    u32 fwow_idx);
u32 k3_udma_gwue_wx_get_fwow_id_base(stwuct k3_udma_gwue_wx_channew *wx_chn);
int k3_udma_gwue_wx_get_iwq(stwuct k3_udma_gwue_wx_channew *wx_chn,
			    u32 fwow_num);
void k3_udma_gwue_wx_put_iwq(stwuct k3_udma_gwue_wx_channew *wx_chn,
			     u32 fwow_num);
void k3_udma_gwue_weset_wx_chn(stwuct k3_udma_gwue_wx_channew *wx_chn,
		u32 fwow_num, void *data,
		void (*cweanup)(void *data, dma_addw_t desc_dma),
		boow skip_fdq);
int k3_udma_gwue_wx_fwow_enabwe(stwuct k3_udma_gwue_wx_channew *wx_chn,
				u32 fwow_idx);
int k3_udma_gwue_wx_fwow_disabwe(stwuct k3_udma_gwue_wx_channew *wx_chn,
				 u32 fwow_idx);
stwuct device *
	k3_udma_gwue_wx_get_dma_device(stwuct k3_udma_gwue_wx_channew *wx_chn);
void k3_udma_gwue_wx_dma_to_cppi5_addw(stwuct k3_udma_gwue_wx_channew *wx_chn,
				       dma_addw_t *addw);
void k3_udma_gwue_wx_cppi5_to_dma_addw(stwuct k3_udma_gwue_wx_channew *wx_chn,
				       dma_addw_t *addw);

#endif /* K3_UDMA_GWUE_H_ */
