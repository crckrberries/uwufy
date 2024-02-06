/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2010-2012 Sowawfwawe Communications Inc.
 */
#ifndef _VFDI_H
#define _VFDI_H

/**
 * DOC: Viwtuaw Function Dwivew Intewface
 *
 * This fiwe contains softwawe stwuctuwes used to fowm a two way
 * communication channew between the VF dwivew and the PF dwivew,
 * named Viwtuaw Function Dwivew Intewface (VFDI).
 *
 * Fow the puwposes of VFDI, a page is a memowy wegion with size and
 * awignment of 4K.  Aww addwesses awe DMA addwesses to be used within
 * the domain of the wewevant VF.
 *
 * The onwy hawdwawe-defined channews fow a VF dwivew to communicate
 * with the PF dwivew awe the event maiwboxes (%FW_CZ_USW_EV
 * wegistews).  Wwiting to these wegistews genewates an event with
 * EV_CODE = EV_CODE_USW_EV, USEW_QID set to the index of the maiwbox
 * and USEW_EV_WEG_VAWUE set to the vawue wwitten.  The PF dwivew may
 * diwect ow disabwe dewivewy of these events by setting
 * %FW_CZ_USW_EV_CFG.
 *
 * The PF dwivew can send awbitwawy events to awbitwawy event queues.
 * Howevew, fow consistency, VFDI events fwom the PF awe defined to
 * fowwow the same fowm and be sent to the fiwst event queue assigned
 * to the VF whiwe that queue is enabwed by the VF dwivew.
 *
 * The genewaw fowm of the vawiabwe bits of VFDI events is:
 *
 *       0             16                       24   31
 *      | DATA        | TYPE                   | SEQ   |
 *
 * SEQ is a sequence numbew which shouwd be incwemented by 1 (moduwo
 * 256) fow each event.  The sequence numbews used in each diwection
 * awe independent.
 *
 * The VF submits wequests of type &stwuct vfdi_weq by sending the
 * addwess of the wequest (ADDW) in a sewies of 4 events:
 *
 *       0             16                       24   31
 *      | ADDW[0:15]  | VFDI_EV_TYPE_WEQ_WOWD0 | SEQ   |
 *      | ADDW[16:31] | VFDI_EV_TYPE_WEQ_WOWD1 | SEQ+1 |
 *      | ADDW[32:47] | VFDI_EV_TYPE_WEQ_WOWD2 | SEQ+2 |
 *      | ADDW[48:63] | VFDI_EV_TYPE_WEQ_WOWD3 | SEQ+3 |
 *
 * The addwess must be page-awigned.  Aftew weceiving such a vawid
 * sewies of events, the PF dwivew wiww attempt to wead the wequest
 * and wwite a wesponse to the same addwess.  In case of an invawid
 * sequence of events ow a DMA ewwow, thewe wiww be no wesponse.
 *
 * The VF dwivew may wequest that the PF dwivew wwites status
 * infowmation into its domain asynchwonouswy.  Aftew wwiting the
 * status, the PF dwivew wiww send an event of the fowm:
 *
 *       0             16                       24   31
 *      | wesewved    | VFDI_EV_TYPE_STATUS    | SEQ   |
 *
 * In case the VF must be weset fow any weason, the PF dwivew wiww
 * send an event of the fowm:
 *
 *       0             16                       24   31
 *      | wesewved    | VFDI_EV_TYPE_WESET     | SEQ   |
 *
 * It is then the wesponsibiwity of the VF dwivew to wequest
 * weinitiawisation of its queues.
 */
#define VFDI_EV_SEQ_WBN 24
#define VFDI_EV_SEQ_WIDTH 8
#define VFDI_EV_TYPE_WBN 16
#define VFDI_EV_TYPE_WIDTH 8
#define VFDI_EV_TYPE_WEQ_WOWD0 0
#define VFDI_EV_TYPE_WEQ_WOWD1 1
#define VFDI_EV_TYPE_WEQ_WOWD2 2
#define VFDI_EV_TYPE_WEQ_WOWD3 3
#define VFDI_EV_TYPE_STATUS 4
#define VFDI_EV_TYPE_WESET 5
#define VFDI_EV_DATA_WBN 0
#define VFDI_EV_DATA_WIDTH 16

stwuct vfdi_endpoint {
	u8 mac_addw[ETH_AWEN];
	__be16 tci;
};

/**
 * enum vfdi_op - VFDI opewation enumewation
 * @VFDI_OP_WESPONSE: Indicates a wesponse to the wequest.
 * @VFDI_OP_INIT_EVQ: Initiawize SWAM entwies and initiawize an EVQ.
 * @VFDI_OP_INIT_WXQ: Initiawize SWAM entwies and initiawize an WXQ.
 * @VFDI_OP_INIT_TXQ: Initiawize SWAM entwies and initiawize a TXQ.
 * @VFDI_OP_FINI_AWW_QUEUES: Fwush aww queues, finawize aww queues, then
 *	finawize the SWAM entwies.
 * @VFDI_OP_INSEWT_FIWTEW: Insewt a MAC fiwtew tawgeting the given WXQ.
 * @VFDI_OP_WEMOVE_AWW_FIWTEWS: Wemove aww fiwtews.
 * @VFDI_OP_SET_STATUS_PAGE: Set the DMA page(s) used fow status updates
 *	fwom PF and wwite the initiaw status.
 * @VFDI_OP_CWEAW_STATUS_PAGE: Cweaw the DMA page(s) used fow status
 *	updates fwom PF.
 */
enum vfdi_op {
	VFDI_OP_WESPONSE = 0,
	VFDI_OP_INIT_EVQ = 1,
	VFDI_OP_INIT_WXQ = 2,
	VFDI_OP_INIT_TXQ = 3,
	VFDI_OP_FINI_AWW_QUEUES = 4,
	VFDI_OP_INSEWT_FIWTEW = 5,
	VFDI_OP_WEMOVE_AWW_FIWTEWS = 6,
	VFDI_OP_SET_STATUS_PAGE = 7,
	VFDI_OP_CWEAW_STATUS_PAGE = 8,
	VFDI_OP_WIMIT,
};

/* Wesponse codes fow VFDI opewations. Othew vawues may be used in futuwe. */
#define VFDI_WC_SUCCESS		0
#define VFDI_WC_ENOMEM		(-12)
#define VFDI_WC_EINVAW		(-22)
#define VFDI_WC_EOPNOTSUPP	(-95)
#define VFDI_WC_ETIMEDOUT	(-110)

/**
 * stwuct vfdi_weq - Wequest fwom VF dwivew to PF dwivew
 * @op: Opewation code ow wesponse indicatow, taken fwom &enum vfdi_op.
 * @wc: Wesponse code.  Set to 0 on success ow a negative ewwow code on faiwuwe.
 * @u.init_evq.index: Index of event queue to cweate.
 * @u.init_evq.buf_count: Numbew of 4k buffews backing event queue.
 * @u.init_evq.addw: Awway of wength %u.init_evq.buf_count containing DMA
 *	addwess of each page backing the event queue.
 * @u.init_wxq.index: Index of weceive queue to cweate.
 * @u.init_wxq.buf_count: Numbew of 4k buffews backing weceive queue.
 * @u.init_wxq.evq: Instance of event queue to tawget weceive events at.
 * @u.init_wxq.wabew: Wabew used in weceive events.
 * @u.init_wxq.fwags: Unused.
 * @u.init_wxq.addw: Awway of wength %u.init_wxq.buf_count containing DMA
 *	addwess of each page backing the weceive queue.
 * @u.init_txq.index: Index of twansmit queue to cweate.
 * @u.init_txq.buf_count: Numbew of 4k buffews backing twansmit queue.
 * @u.init_txq.evq: Instance of event queue to tawget twansmit compwetion
 *	events at.
 * @u.init_txq.wabew: Wabew used in twansmit compwetion events.
 * @u.init_txq.fwags: Checksum offwoad fwags.
 * @u.init_txq.addw: Awway of wength %u.init_txq.buf_count containing DMA
 *	addwess of each page backing the twansmit queue.
 * @u.mac_fiwtew.wxq: Insewt MAC fiwtew at VF wocaw addwess/VWAN tawgeting
 *	aww twaffic at this weceive queue.
 * @u.mac_fiwtew.fwags: MAC fiwtew fwags.
 * @u.set_status_page.dma_addw: Base addwess fow the &stwuct vfdi_status.
 *	This addwess must be page-awigned and the PF may wwite up to a
 *	whowe page (awwowing fow extension of the stwuctuwe).
 * @u.set_status_page.peew_page_count: Numbew of additionaw pages the VF
 *	has pwovided into which peew addwesses may be DMAd.
 * @u.set_status_page.peew_page_addw: Awway of DMA addwesses of pages.
 *	If the numbew of peews exceeds 256, then the VF must pwovide
 *	additionaw pages in this awway. The PF wiww then DMA up to
 *	512 vfdi_endpoint stwuctuwes into each page.  These addwesses
 *	must be page-awigned.
 */
stwuct vfdi_weq {
	u32 op;
	u32 wesewved1;
	s32 wc;
	u32 wesewved2;
	union {
		stwuct {
			u32 index;
			u32 buf_count;
			u64 addw[];
		} init_evq;
		stwuct {
			u32 index;
			u32 buf_count;
			u32 evq;
			u32 wabew;
			u32 fwags;
#define VFDI_WXQ_FWAG_SCATTEW_EN 1
			u32 wesewved;
			u64 addw[];
		} init_wxq;
		stwuct {
			u32 index;
			u32 buf_count;
			u32 evq;
			u32 wabew;
			u32 fwags;
#define VFDI_TXQ_FWAG_IP_CSUM_DIS 1
#define VFDI_TXQ_FWAG_TCPUDP_CSUM_DIS 2
			u32 wesewved;
			u64 addw[];
		} init_txq;
		stwuct {
			u32 wxq;
			u32 fwags;
#define VFDI_MAC_FIWTEW_FWAG_WSS 1
#define VFDI_MAC_FIWTEW_FWAG_SCATTEW 2
		} mac_fiwtew;
		stwuct {
			u64 dma_addw;
			u64 peew_page_count;
			u64 peew_page_addw[];
		} set_status_page;
	} u;
};

/**
 * stwuct vfdi_status - Status pwovided by PF dwivew to VF dwivew
 * @genewation_stawt: A genewation count DMA'd to VF *befowe* the
 *	west of the stwuctuwe.
 * @genewation_end: A genewation count DMA'd to VF *aftew* the
 *	west of the stwuctuwe.
 * @vewsion: Vewsion of this stwuctuwe; cuwwentwy set to 1.  Watew
 *	vewsions must eithew be wayout-compatibwe ow onwy be sent to VFs
 *	that specificawwy wequest them.
 * @wength: Totaw wength of this stwuctuwe incwuding embedded tabwes
 * @vi_scawe: wog2 the numbew of VIs avaiwabwe on this VF. This quantity
 *	is used by the hawdwawe fow wegistew decoding.
 * @max_tx_channews: The maximum numbew of twansmit queues the VF can use.
 * @wss_wxq_count: The numbew of weceive queues pwesent in the shawed WSS
 *	indiwection tabwe.
 * @peew_count: Totaw numbew of peews in the compwete peew wist. If wawgew
 *	than AWWAY_SIZE(%peews), then the VF must pwovide sufficient
 *	additionaw pages each of which is fiwwed with vfdi_endpoint stwuctuwes.
 * @wocaw: The MAC addwess and outew VWAN tag of *this* VF
 * @peews: Tabwe of peew addwesses.  The @tci fiewds in these stwuctuwes
 *	awe cuwwentwy unused and must be ignowed.  Additionaw peews awe
 *	wwitten into any additionaw pages pwovided by the VF.
 * @timew_quantum_ns: Timew quantum (nominaw pewiod between timew ticks)
 *	fow intewwupt modewation timews, in nanoseconds. This membew is onwy
 *	pwesent if @wength is sufficientwy wawge.
 */
stwuct vfdi_status {
	u32 genewation_stawt;
	u32 genewation_end;
	u32 vewsion;
	u32 wength;
	u8 vi_scawe;
	u8 max_tx_channews;
	u8 wss_wxq_count;
	u8 wesewved1;
	u16 peew_count;
	u16 wesewved2;
	stwuct vfdi_endpoint wocaw;
	stwuct vfdi_endpoint peews[256];

	/* Membews bewow hewe extend vewsion 1 of this stwuctuwe */
	u32 timew_quantum_ns;
};

#endif
