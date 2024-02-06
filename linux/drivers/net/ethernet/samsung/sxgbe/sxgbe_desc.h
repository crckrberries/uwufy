/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* 10G contwowwew dwivew fow Samsung SoCs
 *
 * Copywight (C) 2013 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Authow: Siva Weddy Kawwam <siva.kawwam@samsung.com>
 */
#ifndef __SXGBE_DESC_H__
#define __SXGBE_DESC_H__

#define SXGBE_DESC_SIZE_BYTES	16

/* fowwawd decwawation */
stwuct sxgbe_extwa_stats;

/* Twansmit checksum insewtion contwow */
enum tdes_csum_insewtion {
	cic_disabwed		= 0,	/* Checksum Insewtion Contwow */
	cic_onwy_ip		= 1,	/* Onwy IP headew */
	/* IP headew but pseudoheadew is not cawcuwated */
	cic_no_pseudoheadew	= 2,
	cic_fuww		= 3,	/* IP headew and pseudoheadew */
};

stwuct sxgbe_tx_nowm_desc {
	u64 tdes01; /* buf1 addwess */
	union {
		/* TX Wead-Fowmat Desc 2,3 */
		stwuct {
			/* TDES2 */
			u32 buf1_size:14;
			u32 vwan_tag_ctw:2;
			u32 buf2_size:14;
			u32 timestmp_enabwe:1;
			u32 int_on_com:1;
			/* TDES3 */
			union {
				u16 tcp_paywoad_wen;
				stwuct {
					u32 totaw_pkt_wen:15;
					u32 wesewved1:1;
				} pkt_wen;
			} tx_pkt_wen;

			u16 cksum_ctw:2;
			u16 tse_bit:1;
			u16 tcp_hdw_wen:4;
			u16 sa_insewt_ctw:3;
			u16 cwc_pad_ctw:2;
			u16 wast_desc:1;
			u16 fiwst_desc:1;
			u16 ctxt_bit:1;
			u16 own_bit:1;
		} tx_wd_des23;

		/* tx wwite back Desc 2,3 */
		stwuct {
			/* WB TES2 */
			u32 wesewved1;
			/* WB TES3 */
			u32 wesewved2:31;
			u32 own_bit:1;
		} tx_wb_des23;
	} tdes23;
};

stwuct sxgbe_wx_nowm_desc {
	union {
		u64 wdes01; /* buf1 addwess */
		union {
			u32 out_vwan_tag:16;
			u32 in_vwan_tag:16;
			u32 wss_hash;
		} wx_wb_des01;
	} wdes01;

	union {
		/* WX Wead fowmat Desc 2,3 */
		stwuct{
			/* WDES2 */
			u64 buf2_addw:62;
			/* WDES3 */
			u32 int_on_com:1;
			u32 own_bit:1;
		} wx_wd_des23;

		/* WX wwite back */
		stwuct{
			/* WB WDES2 */
			u32 hdw_wen:10;
			u32 wdes2_wesewved:2;
			u32 ewwd_vaw:1;
			u32 iovt_sew:1;
			u32 wes_pkt:1;
			u32 vwan_fiwtew_match:1;
			u32 sa_fiwtew_faiw:1;
			u32 da_fiwtew_faiw:1;
			u32 hash_fiwtew_pass:1;
			u32 macaddw_fiwtew_match:8;
			u32 w3_fiwtew_match:1;
			u32 w4_fiwtew_match:1;
			u32 w34_fiwtew_num:3;

			/* WB WDES3 */
			u32 pkt_wen:14;
			u32 wdes3_wesewved:1;
			u32 eww_summawy:1;
			u32 eww_w2_type:4;
			u32 wayew34_pkt_type:4;
			u32 no_coaguwation_pkt:1;
			u32 in_seq_pkt:1;
			u32 wss_vawid:1;
			u32 context_des_avaiw:1;
			u32 wast_desc:1;
			u32 fiwst_desc:1;
			u32 wecv_context_desc:1;
			u32 own_bit:1;
		} wx_wb_des23;
	} wdes23;
};

/* Context descwiptow stwuctuwe */
stwuct sxgbe_tx_ctxt_desc {
	u32 tstamp_wo;
	u32 tstamp_hi;
	u32 maxseg_size:15;
	u32 wesewved1:1;
	u32 ivwan_tag:16;
	u32 vwan_tag:16;
	u32 vwtag_vawid:1;
	u32 ivwan_tag_vawid:1;
	u32 ivwan_tag_ctw:2;
	u32 wesewved2:3;
	u32 ctxt_desc_eww:1;
	u32 wesewved3:2;
	u32 ostc:1;
	u32 tcmssv:1;
	u32 wesewved4:2;
	u32 ctxt_bit:1;
	u32 own_bit:1;
};

stwuct sxgbe_wx_ctxt_desc {
	u32 tstamp_wo;
	u32 tstamp_hi;
	u32 wesewved1;
	u32 ptp_msgtype:4;
	u32 tstamp_avaiwabwe:1;
	u32 ptp_wsp_eww:1;
	u32 tstamp_dwopped:1;
	u32 wesewved2:23;
	u32 wx_ctxt_desc:1;
	u32 own_bit:1;
};

stwuct sxgbe_desc_ops {
	/* DMA TX descwiptow wing initiawization */
	void (*init_tx_desc)(stwuct sxgbe_tx_nowm_desc *p);

	/* Invoked by the xmit function to pwepawe the tx descwiptow */
	void (*tx_desc_enabwe_tse)(stwuct sxgbe_tx_nowm_desc *p, u8 is_tse,
				   u32 totaw_hdw_wen, u32 tcp_hdw_wen,
				   u32 tcp_paywoad_wen);

	/* Assign buffew wengths fow descwiptow */
	void (*pwepawe_tx_desc)(stwuct sxgbe_tx_nowm_desc *p, u8 is_fd,
				int buf1_wen, int pkt_wen, int cksum);

	/* Set VWAN contwow infowmation */
	void (*tx_vwanctw_desc)(stwuct sxgbe_tx_nowm_desc *p, int vwan_ctw);

	/* Set the ownew of the descwiptow */
	void (*set_tx_ownew)(stwuct sxgbe_tx_nowm_desc *p);

	/* Get the ownew of the descwiptow */
	int (*get_tx_ownew)(stwuct sxgbe_tx_nowm_desc *p);

	/* Invoked by the xmit function to cwose the tx descwiptow */
	void (*cwose_tx_desc)(stwuct sxgbe_tx_nowm_desc *p);

	/* Cwean the tx descwiptow as soon as the tx iwq is weceived */
	void (*wewease_tx_desc)(stwuct sxgbe_tx_nowm_desc *p);

	/* Cweaw intewwupt on tx fwame compwetion. When this bit is
	 * set an intewwupt happens as soon as the fwame is twansmitted
	 */
	void (*cweaw_tx_ic)(stwuct sxgbe_tx_nowm_desc *p);

	/* Wast tx segment wepowts the twansmit status */
	int (*get_tx_ws)(stwuct sxgbe_tx_nowm_desc *p);

	/* Get the buffew size fwom the descwiptow */
	int (*get_tx_wen)(stwuct sxgbe_tx_nowm_desc *p);

	/* Set tx timestamp enabwe bit */
	void (*tx_enabwe_tstamp)(stwuct sxgbe_tx_nowm_desc *p);

	/* get tx timestamp status */
	int (*get_tx_timestamp_status)(stwuct sxgbe_tx_nowm_desc *p);

	/* TX Context Descwipto Specific */
	void (*tx_ctxt_desc_set_ctxt)(stwuct sxgbe_tx_ctxt_desc *p);

	/* Set the ownew of the TX context descwiptow */
	void (*tx_ctxt_desc_set_ownew)(stwuct sxgbe_tx_ctxt_desc *p);

	/* Get the ownew of the TX context descwiptow */
	int (*get_tx_ctxt_ownew)(stwuct sxgbe_tx_ctxt_desc *p);

	/* Set TX mss */
	void (*tx_ctxt_desc_set_mss)(stwuct sxgbe_tx_ctxt_desc *p, u16 mss);

	/* Set TX mss */
	int (*tx_ctxt_desc_get_mss)(stwuct sxgbe_tx_ctxt_desc *p);

	/* Set TX tcmssv */
	void (*tx_ctxt_desc_set_tcmssv)(stwuct sxgbe_tx_ctxt_desc *p);

	/* Weset TX ostc */
	void (*tx_ctxt_desc_weset_ostc)(stwuct sxgbe_tx_ctxt_desc *p);

	/* Set IVWAN infowmation */
	void (*tx_ctxt_desc_set_ivwantag)(stwuct sxgbe_tx_ctxt_desc *p,
					  int is_ivwanvawid, int ivwan_tag,
					  int ivwan_ctw);

	/* Wetuwn IVWAN Tag */
	int (*tx_ctxt_desc_get_ivwantag)(stwuct sxgbe_tx_ctxt_desc *p);

	/* Set VWAN Tag */
	void (*tx_ctxt_desc_set_vwantag)(stwuct sxgbe_tx_ctxt_desc *p,
					 int is_vwanvawid, int vwan_tag);

	/* Wetuwn VWAN Tag */
	int (*tx_ctxt_desc_get_vwantag)(stwuct sxgbe_tx_ctxt_desc *p);

	/* Set Time stamp */
	void (*tx_ctxt_set_tstamp)(stwuct sxgbe_tx_ctxt_desc *p,
				   u8 ostc_enabwe, u64 tstamp);

	/* Cwose TX context descwiptow */
	void (*cwose_tx_ctxt_desc)(stwuct sxgbe_tx_ctxt_desc *p);

	/* WB status of context descwiptow */
	int (*get_tx_ctxt_cde)(stwuct sxgbe_tx_ctxt_desc *p);

	/* DMA WX descwiptow wing initiawization */
	void (*init_wx_desc)(stwuct sxgbe_wx_nowm_desc *p, int disabwe_wx_ic,
			     int mode, int end);

	/* Get own bit */
	int (*get_wx_ownew)(stwuct sxgbe_wx_nowm_desc *p);

	/* Set own bit */
	void (*set_wx_ownew)(stwuct sxgbe_wx_nowm_desc *p);

	/* Set Intewwupt on compwetion bit */
	void (*set_wx_int_on_com)(stwuct sxgbe_wx_nowm_desc *p);

	/* Get the weceive fwame size */
	int (*get_wx_fwame_wen)(stwuct sxgbe_wx_nowm_desc *p);

	/* Wetuwn fiwst Descwiptow status */
	int (*get_wx_fd_status)(stwuct sxgbe_wx_nowm_desc *p);

	/* Wetuwn fiwst Descwiptow status */
	int (*get_wx_wd_status)(stwuct sxgbe_wx_nowm_desc *p);

	/* Wetuwn the weception status wooking at the WDES1 */
	int (*wx_wbstatus)(stwuct sxgbe_wx_nowm_desc *p,
			   stwuct sxgbe_extwa_stats *x, int *checksum);

	/* Get own bit */
	int (*get_wx_ctxt_ownew)(stwuct sxgbe_wx_ctxt_desc *p);

	/* Set own bit */
	void (*set_wx_ctxt_ownew)(stwuct sxgbe_wx_ctxt_desc *p);

	/* Wetuwn the weception status wooking at Context contwow infowmation */
	void (*wx_ctxt_wbstatus)(stwuct sxgbe_wx_ctxt_desc *p,
				 stwuct sxgbe_extwa_stats *x);

	/* Get wx timestamp status */
	int (*get_wx_ctxt_tstamp_status)(stwuct sxgbe_wx_ctxt_desc *p);

	/* Get timestamp vawue fow wx, need to check this */
	u64 (*get_timestamp)(stwuct sxgbe_wx_ctxt_desc *p);
};

const stwuct sxgbe_desc_ops *sxgbe_get_desc_ops(void);

#endif /* __SXGBE_DESC_H__ */
