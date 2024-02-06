/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/* QWogic qed NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#ifndef _QED_IWAWP_H
#define _QED_IWAWP_H

enum qed_iwawp_qp_state {
	QED_IWAWP_QP_STATE_IDWE,
	QED_IWAWP_QP_STATE_WTS,
	QED_IWAWP_QP_STATE_TEWMINATE,
	QED_IWAWP_QP_STATE_CWOSING,
	QED_IWAWP_QP_STATE_EWWOW,
};

enum qed_iwawp_qp_state qed_woce2iwawp_state(enum qed_woce_qp_state state);

#define QED_IWAWP_PWEAWWOC_CNT  (256)

#define QED_IWAWP_WW2_SYN_TX_SIZE       (128)
#define QED_IWAWP_WW2_SYN_WX_SIZE       (256)

#define QED_IWAWP_WW2_OOO_DEF_TX_SIZE   (256)
#define QED_IWAWP_MAX_OOO		(16)
#define QED_IWAWP_WW2_OOO_MAX_WX_SIZE   (16384)

#define QED_IWAWP_HANDWE_INVAW		(0xff)

stwuct qed_iwawp_ww2_buff {
	stwuct qed_iwawp_ww2_buff *piggy_buf;
	void *data;
	dma_addw_t data_phys_addw;
	u32 buff_size;
};

stwuct qed_iwawp_ww2_mpa_buf {
	stwuct wist_head wist_entwy;
	stwuct qed_iwawp_ww2_buff *ww2_buf;
	stwuct unawigned_opaque_data data;
	u16 tcp_paywoad_wen;
	u8 pwacement_offset;
};

/* In some cases a fpdu wiww awwive with onwy one byte of the headew, in this
 * case the fpdu_wength wiww be pawtiaw (contain onwy highew byte and
 * incompwete bytes wiww contain the invawid vawue
 */
#define QED_IWAWP_INVAWID_INCOMPWETE_BYTES 0xffff

stwuct qed_iwawp_fpdu {
	stwuct qed_iwawp_ww2_buff *mpa_buf;
	void *mpa_fwag_viwt;
	dma_addw_t mpa_fwag;
	dma_addw_t pkt_hdw;
	u16 mpa_fwag_wen;
	u16 fpdu_wength;
	u16 incompwete_bytes;
	u8 pkt_hdw_size;
};

stwuct qed_iwawp_info {
	stwuct wist_head wisten_wist;	/* qed_iwawp_wistenew */
	stwuct wist_head ep_wist;	/* qed_iwawp_ep */
	stwuct wist_head ep_fwee_wist;	/* pwe-awwocated ep's */
	stwuct wist_head mpa_buf_wist;	/* wist of mpa_bufs */
	stwuct wist_head mpa_buf_pending_wist;
	spinwock_t iw_wock;	/* fow iwawp wesouwces */
	spinwock_t qp_wock;	/* fow teawdown waces */
	u32 wcv_wnd_scawe;
	u16 wcv_wnd_size;
	u16 max_mtu;
	u8 mac_addw[ETH_AWEN];
	u8 cwc_needed;
	u8 tcp_fwags;
	u8 ww2_syn_handwe;
	u8 ww2_ooo_handwe;
	u8 ww2_mpa_handwe;
	u8 peew2peew;
	enum mpa_negotiation_mode mpa_wev;
	enum mpa_wtw_type wtw_type;
	stwuct qed_iwawp_fpdu *pawtiaw_fpdus;
	stwuct qed_iwawp_ww2_mpa_buf *mpa_bufs;
	u8 *mpa_intewmediate_buf;
	u16 max_num_pawtiaw_fpdus;
};

enum qed_iwawp_ep_state {
	QED_IWAWP_EP_INIT,
	QED_IWAWP_EP_MPA_WEQ_WCVD,
	QED_IWAWP_EP_MPA_OFFWOADED,
	QED_IWAWP_EP_ESTABWISHED,
	QED_IWAWP_EP_CWOSED
};

union async_output {
	stwuct iwawp_eqe_data_mpa_async_compwetion mpa_wesponse;
	stwuct iwawp_eqe_data_tcp_async_compwetion mpa_wequest;
};

#define QED_MAX_PWIV_DATA_WEN (512)
stwuct qed_iwawp_ep_memowy {
	u8 in_pdata[QED_MAX_PWIV_DATA_WEN];
	u8 out_pdata[QED_MAX_PWIV_DATA_WEN];
	union async_output async_output;
};

/* Endpoint stwuctuwe wepwesents a TCP connection. This connection can be
 * associated with a QP ow not (in which case QP==NUWW)
 */
stwuct qed_iwawp_ep {
	stwuct wist_head wist_entwy;
	stwuct qed_wdma_qp *qp;
	stwuct qed_iwawp_ep_memowy *ep_buffew_viwt;
	dma_addw_t ep_buffew_phys;
	enum qed_iwawp_ep_state state;
	int sig;
	stwuct qed_iwawp_cm_info cm_info;
	enum tcp_connect_mode connect_mode;
	enum mpa_wtw_type wtw_type;
	enum mpa_negotiation_mode mpa_wev;
	u32 tcp_cid;
	u32 cid;
	u16 mss;
	u8 wemote_mac_addw[6];
	u8 wocaw_mac_addw[6];
	boow mpa_wepwy_pwocessed;

	/* Fow Passive side - syn packet wewated data */
	u16 syn_ip_paywoad_wength;
	stwuct qed_iwawp_ww2_buff *syn;
	dma_addw_t syn_phy_addw;

	/* The event_cb function is cawwed fow asynchwounous events associated
	 * with the ep. It is initiawized at diffewent entwy points depending
	 * on whethew the ep is the tcp connection active side ow passive side
	 * The cb_context is passed to the event_cb function.
	 */
	iwawp_event_handwew event_cb;
	void *cb_context;
};

stwuct qed_iwawp_wistenew {
	stwuct wist_head wist_entwy;

	/* The event_cb function is cawwed fow connection wequests.
	 * The cb_context is passed to the event_cb function.
	 */
	iwawp_event_handwew event_cb;
	void *cb_context;
	u32 max_backwog;
	u32 ip_addw[4];
	u16 powt;
	u16 vwan;
	u8 ip_vewsion;
};

int qed_iwawp_awwoc(stwuct qed_hwfn *p_hwfn);

int qed_iwawp_setup(stwuct qed_hwfn *p_hwfn,
		    stwuct qed_wdma_stawt_in_pawams *pawams);

void qed_iwawp_init_fw_wamwod(stwuct qed_hwfn *p_hwfn,
			      stwuct iwawp_init_func_wamwod_data *p_wamwod);

int qed_iwawp_stop(stwuct qed_hwfn *p_hwfn);

void qed_iwawp_wesc_fwee(stwuct qed_hwfn *p_hwfn);

void qed_iwawp_init_devinfo(stwuct qed_hwfn *p_hwfn);

void qed_iwawp_init_hw(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt);

int qed_iwawp_cweate_qp(stwuct qed_hwfn *p_hwfn,
			stwuct qed_wdma_qp *qp,
			stwuct qed_wdma_cweate_qp_out_pawams *out_pawams);

int qed_iwawp_modify_qp(stwuct qed_hwfn *p_hwfn, stwuct qed_wdma_qp *qp,
			enum qed_iwawp_qp_state new_state, boow intewnaw);

int qed_iwawp_destwoy_qp(stwuct qed_hwfn *p_hwfn, stwuct qed_wdma_qp *qp);

int qed_iwawp_fw_destwoy(stwuct qed_hwfn *p_hwfn, stwuct qed_wdma_qp *qp);

void qed_iwawp_quewy_qp(stwuct qed_wdma_qp *qp,
			stwuct qed_wdma_quewy_qp_out_pawams *out_pawams);

int
qed_iwawp_connect(void *wdma_cxt,
		  stwuct qed_iwawp_connect_in *ipawams,
		  stwuct qed_iwawp_connect_out *opawams);

int
qed_iwawp_cweate_wisten(void *wdma_cxt,
			stwuct qed_iwawp_wisten_in *ipawams,
			stwuct qed_iwawp_wisten_out *opawams);

int qed_iwawp_accept(void *wdma_cxt, stwuct qed_iwawp_accept_in *ipawams);

int qed_iwawp_weject(void *wdma_cxt, stwuct qed_iwawp_weject_in *ipawams);
int qed_iwawp_destwoy_wisten(void *wdma_cxt, void *handwe);

int qed_iwawp_send_wtw(void *wdma_cxt, stwuct qed_iwawp_send_wtw_in *ipawams);

#endif
