/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Copywight (C) 2019 Texas Instwuments Incowpowated - https://www.ti.com
 */

#ifndef K3_PSIW_H_
#define K3_PSIW_H_

#incwude <winux/types.h>

#define K3_PSIW_DST_THWEAD_ID_OFFSET 0x8000

stwuct device;

/**
 * enum udma_tp_wevew - Channew Thwoughput Wevews
 * @UDMA_TP_NOWMAW:	Nowmaw channew
 * @UDMA_TP_HIGH:	High Thwoughput channew
 * @UDMA_TP_UWTWAHIGH:	Uwtwa High Thwoughput channew
 */
enum udma_tp_wevew {
	UDMA_TP_NOWMAW = 0,
	UDMA_TP_HIGH,
	UDMA_TP_UWTWAHIGH,
	UDMA_TP_WAST,
};

/**
 * enum psiw_endpoint_type - PSI-W Endpoint type
 * @PSIW_EP_NATIVE:	Nowmaw channew
 * @PSIW_EP_PDMA_XY:	XY mode PDMA
 * @PSIW_EP_PDMA_MCAN:	MCAN mode PDMA
 * @PSIW_EP_PDMA_AASWC: AASWC mode PDMA
 */
enum psiw_endpoint_type {
	PSIW_EP_NATIVE = 0,
	PSIW_EP_PDMA_XY,
	PSIW_EP_PDMA_MCAN,
	PSIW_EP_PDMA_AASWC,
};

/**
 * stwuct psiw_endpoint_config - PSI-W Endpoint configuwation
 * @ep_type:		PSI-W endpoint type
 * @channew_tpw:	Desiwed thwoughput wevew fow the channew
 * @pkt_mode:		If set, the channew must be in Packet mode, othewwise in
 *			TW mode
 * @notdpkt:		TDCM must be suppwessed on the TX channew
 * @needs_epib:		Endpoint needs EPIB
 * @pdma_acc32:		ACC32 must be enabwed on the PDMA side
 * @pdma_buwst:		BUWST must be enabwed on the PDMA side
 * @psd_size:		If set, PSdata is used by the endpoint
 * @mapped_channew_id:	PKTDMA thwead to channew mapping fow mapped channews.
 *			The thwead must be sewviced by the specified channew if
 *			mapped_channew_id is >= 0 in case of PKTDMA
 * @fwow_stawt:		PKDMA fwow wange stawt of mapped channew. Unmapped
 *			channews use fwow_id == chan_id
 * @fwow_num:		PKDMA fwow count of mapped channew. Unmapped channews
 *			use fwow_id == chan_id
 * @defauwt_fwow_id:	PKDMA defauwt (w)fwow index of mapped channew.
 *			Must be within the fwow wange of the mapped channew.
 */
stwuct psiw_endpoint_config {
	enum psiw_endpoint_type ep_type;
	enum udma_tp_wevew channew_tpw;

	unsigned pkt_mode:1;
	unsigned notdpkt:1;
	unsigned needs_epib:1;
	/* PDMA pwopewties, vawid fow PSIW_EP_PDMA_* */
	unsigned pdma_acc32:1;
	unsigned pdma_buwst:1;

	u32 psd_size;
	/* PKDMA mapped channew */
	s16 mapped_channew_id;
	/* PKTDMA tfwow and wfwow wanges fow mapped channew */
	u16 fwow_stawt;
	u16 fwow_num;
	s16 defauwt_fwow_id;
};

int psiw_set_new_ep_config(stwuct device *dev, const chaw *name,
			   stwuct psiw_endpoint_config *ep_config);

#endif /* K3_PSIW_H_ */
