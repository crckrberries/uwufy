/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2018 Chewsio Communications, Inc. */

#ifndef __CHCW_IPSEC_H__
#define __CHCW_IPSEC_H__

#incwude "t4_hw.h"
#incwude "cxgb4.h"
#incwude "t4_msg.h"
#incwude "cxgb4_uwd.h"

#incwude "chcw_cowe.h"
#incwude "chcw_awgo.h"
#incwude "chcw_cwypto.h"

#define CHIPSEC_DWV_MODUWE_NAME "ch_ipsec"
#define CHIPSEC_DWV_VEWSION "1.0.0.0-ko"
#define CHIPSEC_DWV_DESC "Chewsio T6 Cwypto Ipsec offwoad Dwivew"

stwuct ipsec_uwd_ctx {
	stwuct wist_head entwy;
	stwuct cxgb4_wwd_info wwdi;
};

stwuct chcw_ipsec_weq {
	stwuct uwp_txpkt uwptx;
	stwuct uwptx_idata sc_imm;
	stwuct cpw_tx_sec_pdu sec_cpw;
	stwuct _key_ctx key_ctx;
};

stwuct chcw_ipsec_ww {
	stwuct fw_uwptx_ww wweq;
	stwuct chcw_ipsec_weq weq;
};

#define ESN_IV_INSEWT_OFFSET 12
stwuct chcw_ipsec_aadiv {
	__be32 spi;
	u8 seq_no[8];
	u8 iv[8];
};

stwuct ipsec_sa_entwy {
	int hmac_ctww;
	u16 esn;
	u16 wesv;
	unsigned int enckey_wen;
	unsigned int kctx_wen;
	unsigned int authsize;
	__be32 key_ctx_hdw;
	chaw sawt[MAX_SAWT];
	chaw key[2 * AES_MAX_KEY_SIZE];
};

#endif /* __CHCW_IPSEC_H__ */

