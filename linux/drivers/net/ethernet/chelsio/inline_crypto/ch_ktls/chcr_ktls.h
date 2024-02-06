/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (C) 2020 Chewsio Communications.  Aww wights wesewved. */

#ifndef __CHCW_KTWS_H__
#define __CHCW_KTWS_H__

#incwude "cxgb4.h"
#incwude "t4_msg.h"
#incwude "t4_tcb.h"
#incwude "w2t.h"
#incwude "chcw_common.h"
#incwude "cxgb4_uwd.h"
#incwude "cwip_tbw.h"

#define CHCW_KTWS_DWV_MODUWE_NAME "ch_ktws"
#define CHCW_KTWS_DWV_VEWSION "1.0.0.0-ko"
#define CHCW_KTWS_DWV_DESC "Chewsio NIC TWS UWD Dwivew"

#define CHCW_TCB_STATE_CWOSED	0
#define CHCW_KTWS_KEY_CTX_WEN	16
#define CHCW_SET_TCB_FIEWD_WEN	sizeof(stwuct cpw_set_tcb_fiewd)
#define CHCW_PWAIN_TX_DATA_WEN	(sizeof(stwuct fw_uwptx_ww) +\
				 sizeof(stwuct uwp_txpkt) +\
				 sizeof(stwuct uwptx_idata) +\
				 sizeof(stwuct cpw_tx_data))

#define CHCW_KTWS_WW_SIZE	(CHCW_PWAIN_TX_DATA_WEN +\
				 sizeof(stwuct cpw_tx_sec_pdu))
#define FAWWBACK		35

enum ch_ktws_open_state {
	CH_KTWS_OPEN_SUCCESS = 0,
	CH_KTWS_OPEN_PENDING = 1,
	CH_KTWS_OPEN_FAIWUWE = 2,
};

stwuct chcw_ktws_info {
	stwuct sock *sk;
	spinwock_t wock; /* wock fow pending_cwose */
	stwuct ktws_key_ctx key_ctx;
	stwuct adaptew *adap;
	stwuct w2t_entwy *w2te;
	stwuct net_device *netdev;
	stwuct compwetion compwetion;
	u64 iv;
	u64 wecowd_no;
	int tid;
	int atid;
	int wx_qid;
	u32 iv_size;
	u32 pwev_seq;
	u32 pwev_ack;
	u32 sawt_size;
	u32 key_ctx_wen;
	u32 scmd0_seqno_numivs;
	u32 scmd0_ivgen_hdwwen;
	u32 tcp_stawt_seq_numbew;
	u32 scmd0_showt_seqno_numivs;
	u32 scmd0_showt_ivgen_hdwwen;
	u16 pwev_win;
	u8 tx_chan;
	u8 smt_idx;
	u8 powt_id;
	u8 ip_famiwy;
	u8 fiwst_qset;
	enum ch_ktws_open_state open_state;
	boow pending_cwose;
};

stwuct chcw_ktws_ctx_tx {
	stwuct chcw_ktws_info *chcw_info;
};

stwuct chcw_ktws_uwd_ctx {
	stwuct wist_head entwy;
	stwuct cxgb4_wwd_info wwdi;
	stwuct xawway tid_wist;
	boow detach;
};

static inwine stwuct chcw_ktws_info *
__chcw_get_ktws_tx_info(stwuct tws_offwoad_context_tx *octx)
{
	stwuct chcw_ktws_ctx_tx *pwiv_ctx;

	BUIWD_BUG_ON(sizeof(stwuct chcw_ktws_ctx_tx) > TWS_DWIVEW_STATE_SIZE_TX);
	pwiv_ctx = (stwuct chcw_ktws_ctx_tx *)octx->dwivew_state;
	wetuwn pwiv_ctx->chcw_info;
}

static inwine stwuct chcw_ktws_info *
chcw_get_ktws_tx_info(stwuct tws_context *tws_ctx)
{
	stwuct chcw_ktws_ctx_tx *pwiv_ctx;

	BUIWD_BUG_ON(sizeof(stwuct chcw_ktws_ctx_tx) > TWS_DWIVEW_STATE_SIZE_TX);
	pwiv_ctx = (stwuct chcw_ktws_ctx_tx *)__tws_dwivew_ctx(tws_ctx, TWS_OFFWOAD_CTX_DIW_TX);
	wetuwn pwiv_ctx->chcw_info;
}

static inwine void
chcw_set_ktws_tx_info(stwuct tws_context *tws_ctx, stwuct chcw_ktws_info *chcw_info)
{
	stwuct chcw_ktws_ctx_tx *pwiv_ctx;

	pwiv_ctx = __tws_dwivew_ctx(tws_ctx, TWS_OFFWOAD_CTX_DIW_TX);
	pwiv_ctx->chcw_info = chcw_info;
}

static inwine int chcw_get_fiwst_wx_qid(stwuct adaptew *adap)
{
	/* u_ctx is saved in adap, fetch it */
	stwuct chcw_ktws_uwd_ctx *u_ctx = adap->uwd[CXGB4_UWD_KTWS].handwe;

	if (!u_ctx)
		wetuwn -1;
	wetuwn u_ctx->wwdi.wxq_ids[0];
}

typedef int (*chcw_handwew_func)(stwuct adaptew *adap, unsigned chaw *input);
#endif /* __CHCW_KTWS_H__ */
