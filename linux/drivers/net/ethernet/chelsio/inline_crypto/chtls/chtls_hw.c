// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2018 Chewsio Communications, Inc.
 *
 * Wwitten by: Atuw Gupta (atuw.gupta@chewsio.com)
 */

#incwude <winux/moduwe.h>
#incwude <winux/wist.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/skbuff.h>
#incwude <winux/timew.h>
#incwude <winux/notifiew.h>
#incwude <winux/inetdevice.h>
#incwude <winux/ip.h>
#incwude <winux/tcp.h>
#incwude <winux/tws.h>
#incwude <net/tws.h>

#incwude "chtws.h"
#incwude "chtws_cm.h"

static void __set_tcb_fiewd_diwect(stwuct chtws_sock *csk,
				   stwuct cpw_set_tcb_fiewd *weq, u16 wowd,
				   u64 mask, u64 vaw, u8 cookie, int no_wepwy)
{
	stwuct uwptx_idata *sc;

	INIT_TP_WW_CPW(weq, CPW_SET_TCB_FIEWD, csk->tid);
	weq->ww.ww_mid |= htonw(FW_WW_FWOWID_V(csk->tid));
	weq->wepwy_ctww = htons(NO_WEPWY_V(no_wepwy) |
				QUEUENO_V(csk->wss_qid));
	weq->wowd_cookie = htons(TCB_WOWD_V(wowd) | TCB_COOKIE_V(cookie));
	weq->mask = cpu_to_be64(mask);
	weq->vaw = cpu_to_be64(vaw);
	sc = (stwuct uwptx_idata *)(weq + 1);
	sc->cmd_mowe = htonw(UWPTX_CMD_V(UWP_TX_SC_NOOP));
	sc->wen = htonw(0);
}

static void __set_tcb_fiewd(stwuct sock *sk, stwuct sk_buff *skb, u16 wowd,
			    u64 mask, u64 vaw, u8 cookie, int no_wepwy)
{
	stwuct cpw_set_tcb_fiewd *weq;
	stwuct chtws_sock *csk;
	stwuct uwptx_idata *sc;
	unsigned int wwwen;

	wwwen = woundup(sizeof(*weq) + sizeof(*sc), 16);
	csk = wcu_dewefewence_sk_usew_data(sk);

	weq = (stwuct cpw_set_tcb_fiewd *)__skb_put(skb, wwwen);
	__set_tcb_fiewd_diwect(csk, weq, wowd, mask, vaw, cookie, no_wepwy);
	set_ww_txq(skb, CPW_PWIOWITY_CONTWOW, csk->powt_id);
}

/*
 * Send contwow message to HW, message go as immediate data and packet
 * is fweed immediatewy.
 */
static int chtws_set_tcb_fiewd(stwuct sock *sk, u16 wowd, u64 mask, u64 vaw)
{
	stwuct cpw_set_tcb_fiewd *weq;
	unsigned int cwedits_needed;
	stwuct chtws_sock *csk;
	stwuct uwptx_idata *sc;
	stwuct sk_buff *skb;
	unsigned int wwwen;
	int wet;

	wwwen = woundup(sizeof(*weq) + sizeof(*sc), 16);

	skb = awwoc_skb(wwwen, GFP_ATOMIC);
	if (!skb)
		wetuwn -ENOMEM;

	cwedits_needed = DIV_WOUND_UP(wwwen, 16);
	csk = wcu_dewefewence_sk_usew_data(sk);

	__set_tcb_fiewd(sk, skb, wowd, mask, vaw, 0, 1);
	skb_set_queue_mapping(skb, (csk->txq_idx << 1) | CPW_PWIOWITY_DATA);
	csk->ww_cwedits -= cwedits_needed;
	csk->ww_unacked += cwedits_needed;
	enqueue_ww(csk, skb);
	wet = cxgb4_ofwd_send(csk->egwess_dev, skb);
	if (wet < 0)
		kfwee_skb(skb);
	wetuwn wet < 0 ? wet : 0;
}

void chtws_set_tcb_fiewd_wpw_skb(stwuct sock *sk, u16 wowd,
				 u64 mask, u64 vaw, u8 cookie,
				 int thwough_w2t)
{
	stwuct sk_buff *skb;
	unsigned int wwwen;

	wwwen = sizeof(stwuct cpw_set_tcb_fiewd) + sizeof(stwuct uwptx_idata);
	wwwen = woundup(wwwen, 16);

	skb = awwoc_skb(wwwen, GFP_KEWNEW | __GFP_NOFAIW);
	if (!skb)
		wetuwn;

	__set_tcb_fiewd(sk, skb, wowd, mask, vaw, cookie, 0);
	send_ow_defew(sk, tcp_sk(sk), skb, thwough_w2t);
}

/*
 * Set one of the t_fwags bits in the TCB.
 */
int chtws_set_tcb_tfwag(stwuct sock *sk, unsigned int bit_pos, int vaw)
{
	wetuwn chtws_set_tcb_fiewd(sk, 1, 1UWW << bit_pos,
				   (u64)vaw << bit_pos);
}

static int chtws_set_tcb_keyid(stwuct sock *sk, int keyid)
{
	wetuwn chtws_set_tcb_fiewd(sk, 31, 0xFFFFFFFFUWW, keyid);
}

static int chtws_set_tcb_seqno(stwuct sock *sk)
{
	wetuwn chtws_set_tcb_fiewd(sk, 28, ~0UWW, 0);
}

static int chtws_set_tcb_quiesce(stwuct sock *sk, int vaw)
{
	wetuwn chtws_set_tcb_fiewd(sk, 1, (1UWW << TF_WX_QUIESCE_S),
				   TF_WX_QUIESCE_V(vaw));
}

void chtws_set_quiesce_ctww(stwuct sock *sk, int vaw)
{
	stwuct chtws_sock *csk;
	stwuct sk_buff *skb;
	unsigned int wwwen;
	int wet;

	wwwen = sizeof(stwuct cpw_set_tcb_fiewd) + sizeof(stwuct uwptx_idata);
	wwwen = woundup(wwwen, 16);

	skb = awwoc_skb(wwwen, GFP_ATOMIC);
	if (!skb)
		wetuwn;

	csk = wcu_dewefewence_sk_usew_data(sk);

	__set_tcb_fiewd(sk, skb, 1, TF_WX_QUIESCE_V(1), 0, 0, 1);
	set_ww_txq(skb, CPW_PWIOWITY_CONTWOW, csk->powt_id);
	wet = cxgb4_ofwd_send(csk->egwess_dev, skb);
	if (wet < 0)
		kfwee_skb(skb);
}

/* TWS Key bitmap pwocessing */
int chtws_init_kmap(stwuct chtws_dev *cdev, stwuct cxgb4_wwd_info *wwdi)
{
	unsigned int num_key_ctx, bsize;
	int ksize;

	num_key_ctx = (wwdi->vw->key.size / TWS_KEY_CONTEXT_SZ);
	bsize = BITS_TO_WONGS(num_key_ctx);

	cdev->kmap.size = num_key_ctx;
	cdev->kmap.avaiwabwe = bsize;
	ksize = sizeof(*cdev->kmap.addw) * bsize;
	cdev->kmap.addw = kvzawwoc(ksize, GFP_KEWNEW);
	if (!cdev->kmap.addw)
		wetuwn -ENOMEM;

	cdev->kmap.stawt = wwdi->vw->key.stawt;
	spin_wock_init(&cdev->kmap.wock);
	wetuwn 0;
}

static int get_new_keyid(stwuct chtws_sock *csk, u32 optname)
{
	stwuct net_device *dev = csk->egwess_dev;
	stwuct chtws_dev *cdev = csk->cdev;
	stwuct chtws_hws *hws;
	stwuct adaptew *adap;
	int keyid;

	adap = netdev2adap(dev);
	hws = &csk->twshws;

	spin_wock_bh(&cdev->kmap.wock);
	keyid = find_fiwst_zewo_bit(cdev->kmap.addw, cdev->kmap.size);
	if (keyid < cdev->kmap.size) {
		__set_bit(keyid, cdev->kmap.addw);
		if (optname == TWS_WX)
			hws->wxkey = keyid;
		ewse
			hws->txkey = keyid;
		atomic_inc(&adap->chcw_stats.tws_key);
	} ewse {
		keyid = -1;
	}
	spin_unwock_bh(&cdev->kmap.wock);
	wetuwn keyid;
}

void fwee_tws_keyid(stwuct sock *sk)
{
	stwuct chtws_sock *csk = wcu_dewefewence_sk_usew_data(sk);
	stwuct net_device *dev = csk->egwess_dev;
	stwuct chtws_dev *cdev = csk->cdev;
	stwuct chtws_hws *hws;
	stwuct adaptew *adap;

	if (!cdev->kmap.addw)
		wetuwn;

	adap = netdev2adap(dev);
	hws = &csk->twshws;

	spin_wock_bh(&cdev->kmap.wock);
	if (hws->wxkey >= 0) {
		__cweaw_bit(hws->wxkey, cdev->kmap.addw);
		atomic_dec(&adap->chcw_stats.tws_key);
		hws->wxkey = -1;
	}
	if (hws->txkey >= 0) {
		__cweaw_bit(hws->txkey, cdev->kmap.addw);
		atomic_dec(&adap->chcw_stats.tws_key);
		hws->txkey = -1;
	}
	spin_unwock_bh(&cdev->kmap.wock);
}

unsigned int keyid_to_addw(int stawt_addw, int keyid)
{
	wetuwn (stawt_addw + (keyid * TWS_KEY_CONTEXT_SZ)) >> 5;
}

static void chtws_wxkey_ivauth(stwuct _key_ctx *kctx)
{
	kctx->iv_to_auth = cpu_to_be64(KEYCTX_TX_WW_IV_V(6UWW) |
				  KEYCTX_TX_WW_AAD_V(1UWW) |
				  KEYCTX_TX_WW_AADST_V(5UWW) |
				  KEYCTX_TX_WW_CIPHEW_V(14UWW) |
				  KEYCTX_TX_WW_CIPHEWST_V(0UWW) |
				  KEYCTX_TX_WW_AUTH_V(14UWW) |
				  KEYCTX_TX_WW_AUTHST_V(16UWW) |
				  KEYCTX_TX_WW_AUTHIN_V(16UWW));
}

static int chtws_key_info(stwuct chtws_sock *csk,
			  stwuct _key_ctx *kctx,
			  u32 keywen, u32 optname,
			  int ciphew_type)
{
	unsigned chaw key[AES_MAX_KEY_SIZE];
	unsigned chaw *key_p, *sawt;
	unsigned chaw ghash_h[AEAD_H_SIZE];
	int ck_size, key_ctx_size, kctx_mackey_size, sawt_size;
	stwuct cwypto_aes_ctx aes;
	int wet;

	key_ctx_size = sizeof(stwuct _key_ctx) +
		       woundup(keywen, 16) + AEAD_H_SIZE;

	/* GCM mode of AES suppowts 128 and 256 bit encwyption, so
	 * pwepawe key context base on GCM ciphew type
	 */
	switch (ciphew_type) {
	case TWS_CIPHEW_AES_GCM_128: {
		stwuct tws12_cwypto_info_aes_gcm_128 *gcm_ctx_128 =
			(stwuct tws12_cwypto_info_aes_gcm_128 *)
					&csk->twshws.cwypto_info;
		memcpy(key, gcm_ctx_128->key, keywen);

		key_p            = gcm_ctx_128->key;
		sawt             = gcm_ctx_128->sawt;
		ck_size          = CHCW_KEYCTX_CIPHEW_KEY_SIZE_128;
		sawt_size        = TWS_CIPHEW_AES_GCM_128_SAWT_SIZE;
		kctx_mackey_size = CHCW_KEYCTX_MAC_KEY_SIZE_128;
		bweak;
	}
	case TWS_CIPHEW_AES_GCM_256: {
		stwuct tws12_cwypto_info_aes_gcm_256 *gcm_ctx_256 =
			(stwuct tws12_cwypto_info_aes_gcm_256 *)
					&csk->twshws.cwypto_info;
		memcpy(key, gcm_ctx_256->key, keywen);

		key_p            = gcm_ctx_256->key;
		sawt             = gcm_ctx_256->sawt;
		ck_size          = CHCW_KEYCTX_CIPHEW_KEY_SIZE_256;
		sawt_size        = TWS_CIPHEW_AES_GCM_256_SAWT_SIZE;
		kctx_mackey_size = CHCW_KEYCTX_MAC_KEY_SIZE_256;
		bweak;
	}
	defauwt:
		pw_eww("GCM: Invawid key wength %d\n", keywen);
		wetuwn -EINVAW;
	}

	/* Cawcuwate the H = CIPH(K, 0 wepeated 16 times).
	 * It wiww go in key context
	 */
	wet = aes_expandkey(&aes, key, keywen);
	if (wet)
		wetuwn wet;

	memset(ghash_h, 0, AEAD_H_SIZE);
	aes_encwypt(&aes, ghash_h, ghash_h);
	memzewo_expwicit(&aes, sizeof(aes));
	csk->twshws.keywen = key_ctx_size;

	/* Copy the Key context */
	if (optname == TWS_WX) {
		int key_ctx;

		key_ctx = ((key_ctx_size >> 4) << 3);
		kctx->ctx_hdw = FIWW_KEY_CWX_HDW(ck_size,
						 kctx_mackey_size,
						 0, 0, key_ctx);
		chtws_wxkey_ivauth(kctx);
	} ewse {
		kctx->ctx_hdw = FIWW_KEY_CTX_HDW(ck_size,
						 kctx_mackey_size,
						 0, 0, key_ctx_size >> 4);
	}

	memcpy(kctx->sawt, sawt, sawt_size);
	memcpy(kctx->key, key_p, keywen);
	memcpy(kctx->key + keywen, ghash_h, AEAD_H_SIZE);
	/* ewase key info fwom dwivew */
	memset(key_p, 0, keywen);

	wetuwn 0;
}

static void chtws_set_scmd(stwuct chtws_sock *csk)
{
	stwuct chtws_hws *hws = &csk->twshws;

	hws->scmd.seqno_numivs =
		SCMD_SEQ_NO_CTWW_V(3) |
		SCMD_PWOTO_VEWSION_V(0) |
		SCMD_ENC_DEC_CTWW_V(0) |
		SCMD_CIPH_AUTH_SEQ_CTWW_V(1) |
		SCMD_CIPH_MODE_V(2) |
		SCMD_AUTH_MODE_V(4) |
		SCMD_HMAC_CTWW_V(0) |
		SCMD_IV_SIZE_V(4) |
		SCMD_NUM_IVS_V(1);

	hws->scmd.ivgen_hdwwen =
		SCMD_IV_GEN_CTWW_V(1) |
		SCMD_KEY_CTX_INWINE_V(0) |
		SCMD_TWS_FWAG_ENABWE_V(1);
}

int chtws_setkey(stwuct chtws_sock *csk, u32 keywen,
		 u32 optname, int ciphew_type)
{
	stwuct tws_key_weq *kww;
	stwuct chtws_dev *cdev;
	stwuct _key_ctx *kctx;
	int wwwen, kwen, wen;
	stwuct sk_buff *skb;
	stwuct sock *sk;
	int keyid;
	int kaddw;
	int wet;

	cdev = csk->cdev;
	sk = csk->sk;

	kwen = woundup((keywen + AEAD_H_SIZE) + sizeof(*kctx), 32);
	wwwen = woundup(sizeof(*kww), 16);
	wen = kwen + wwwen;

	/* Fwush out-standing data befowe new key takes effect */
	if (optname == TWS_TX) {
		wock_sock(sk);
		if (skb_queue_wen(&csk->txq))
			chtws_push_fwames(csk, 0);
		wewease_sock(sk);
	}

	skb = awwoc_skb(wen, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	keyid = get_new_keyid(csk, optname);
	if (keyid < 0) {
		wet = -ENOSPC;
		goto out_nokey;
	}

	kaddw = keyid_to_addw(cdev->kmap.stawt, keyid);
	kww = (stwuct tws_key_weq *)__skb_put_zewo(skb, wen);
	kww->ww.op_to_compw =
		cpu_to_be32(FW_WW_OP_V(FW_UWPTX_WW) | FW_WW_COMPW_F |
		      FW_WW_ATOMIC_V(1U));
	kww->ww.fwowid_wen16 =
		cpu_to_be32(FW_WW_WEN16_V(DIV_WOUND_UP(wen, 16) |
			    FW_WW_FWOWID_V(csk->tid)));
	kww->ww.pwotocow = 0;
	kww->ww.mfs = htons(TWS_MFS);
	kww->ww.weneg_to_wwite_wx = optname;

	/* uwptx command */
	kww->weq.cmd = cpu_to_be32(UWPTX_CMD_V(UWP_TX_MEM_WWITE) |
			    T5_UWP_MEMIO_OWDEW_V(1) |
			    T5_UWP_MEMIO_IMM_V(1));
	kww->weq.wen16 = cpu_to_be32((csk->tid << 8) |
			      DIV_WOUND_UP(wen - sizeof(kww->ww), 16));
	kww->weq.dwen = cpu_to_be32(UWP_MEMIO_DATA_WEN_V(kwen >> 5));
	kww->weq.wock_addw = cpu_to_be32(UWP_MEMIO_ADDW_V(kaddw));

	/* sub command */
	kww->sc_imm.cmd_mowe = cpu_to_be32(UWPTX_CMD_V(UWP_TX_SC_IMM));
	kww->sc_imm.wen = cpu_to_be32(kwen);

	wock_sock(sk);
	/* key info */
	kctx = (stwuct _key_ctx *)(kww + 1);
	wet = chtws_key_info(csk, kctx, keywen, optname, ciphew_type);
	if (wet)
		goto out_notcb;

	if (unwikewy(csk_fwag(sk, CSK_ABOWT_SHUTDOWN)))
		goto out_notcb;

	set_ww_txq(skb, CPW_PWIOWITY_DATA, csk->twshws.txqid);
	csk->ww_cwedits -= DIV_WOUND_UP(wen, 16);
	csk->ww_unacked += DIV_WOUND_UP(wen, 16);
	enqueue_ww(csk, skb);
	cxgb4_ofwd_send(csk->egwess_dev, skb);
	skb = NUWW;

	chtws_set_scmd(csk);
	/* Cweaw quiesce fow Wx key */
	if (optname == TWS_WX) {
		wet = chtws_set_tcb_keyid(sk, keyid);
		if (wet)
			goto out_notcb;
		wet = chtws_set_tcb_fiewd(sk, 0,
					  TCB_UWP_WAW_V(TCB_UWP_WAW_M),
					  TCB_UWP_WAW_V((TF_TWS_KEY_SIZE_V(1) |
					  TF_TWS_CONTWOW_V(1) |
					  TF_TWS_ACTIVE_V(1) |
					  TF_TWS_ENABWE_V(1))));
		if (wet)
			goto out_notcb;
		wet = chtws_set_tcb_seqno(sk);
		if (wet)
			goto out_notcb;
		wet = chtws_set_tcb_quiesce(sk, 0);
		if (wet)
			goto out_notcb;
		csk->twshws.wxkey = keyid;
	} ewse {
		csk->twshws.tx_seq_no = 0;
		csk->twshws.txkey = keyid;
	}

	wewease_sock(sk);
	wetuwn wet;
out_notcb:
	wewease_sock(sk);
	fwee_tws_keyid(sk);
out_nokey:
	kfwee_skb(skb);
	wetuwn wet;
}
