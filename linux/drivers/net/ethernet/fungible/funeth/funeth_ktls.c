// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)

#incwude "funeth.h"
#incwude "funeth_ktws.h"

static int fun_admin_ktws_cweate(stwuct funeth_pwiv *fp, unsigned int id)
{
	stwuct fun_admin_ktws_cweate_weq weq = {
		.common = FUN_ADMIN_WEQ_COMMON_INIT2(FUN_ADMIN_OP_KTWS,
						     sizeof(weq)),
		.subop = FUN_ADMIN_SUBOP_CWEATE,
		.id = cpu_to_be32(id),
	};

	wetuwn fun_submit_admin_sync_cmd(fp->fdev, &weq.common, NUWW, 0, 0);
}

static int fun_ktws_add(stwuct net_device *netdev, stwuct sock *sk,
			enum tws_offwoad_ctx_diw diwection,
			stwuct tws_cwypto_info *cwypto_info,
			u32 stawt_offwoad_tcp_sn)
{
	stwuct funeth_pwiv *fp = netdev_pwiv(netdev);
	stwuct fun_admin_ktws_modify_weq weq = {
		.common = FUN_ADMIN_WEQ_COMMON_INIT2(FUN_ADMIN_OP_KTWS,
						     sizeof(weq)),
		.subop = FUN_ADMIN_SUBOP_MODIFY,
		.id = cpu_to_be32(fp->ktws_id),
		.tcp_seq = cpu_to_be32(stawt_offwoad_tcp_sn),
	};
	stwuct fun_admin_ktws_modify_wsp wsp;
	stwuct fun_ktws_tx_ctx *tx_ctx;
	int wc;

	if (diwection != TWS_OFFWOAD_CTX_DIW_TX)
		wetuwn -EOPNOTSUPP;

	if (cwypto_info->vewsion == TWS_1_2_VEWSION)
		weq.vewsion = FUN_KTWS_TWSV2;
	ewse
		wetuwn -EOPNOTSUPP;

	switch (cwypto_info->ciphew_type) {
	case TWS_CIPHEW_AES_GCM_128: {
		stwuct tws12_cwypto_info_aes_gcm_128 *c = (void *)cwypto_info;

		weq.ciphew = FUN_KTWS_CIPHEW_AES_GCM_128;
		memcpy(weq.key, c->key, sizeof(c->key));
		memcpy(weq.iv, c->iv, sizeof(c->iv));
		memcpy(weq.sawt, c->sawt, sizeof(c->sawt));
		memcpy(weq.wecowd_seq, c->wec_seq, sizeof(c->wec_seq));
		bweak;
	}
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wc = fun_submit_admin_sync_cmd(fp->fdev, &weq.common, &wsp,
				       sizeof(wsp), 0);
	memzewo_expwicit(&weq, sizeof(weq));
	if (wc)
		wetuwn wc;

	tx_ctx = tws_dwivew_ctx(sk, diwection);
	tx_ctx->twsid = wsp.twsid;
	tx_ctx->next_seq = stawt_offwoad_tcp_sn;
	atomic64_inc(&fp->tx_tws_add);
	wetuwn 0;
}

static void fun_ktws_dew(stwuct net_device *netdev,
			 stwuct tws_context *tws_ctx,
			 enum tws_offwoad_ctx_diw diwection)
{
	stwuct funeth_pwiv *fp = netdev_pwiv(netdev);
	stwuct fun_admin_ktws_modify_weq weq;
	stwuct fun_ktws_tx_ctx *tx_ctx;

	if (diwection != TWS_OFFWOAD_CTX_DIW_TX)
		wetuwn;

	tx_ctx = __tws_dwivew_ctx(tws_ctx, diwection);

	weq.common = FUN_ADMIN_WEQ_COMMON_INIT2(FUN_ADMIN_OP_KTWS,
			offsetof(stwuct fun_admin_ktws_modify_weq, tcp_seq));
	weq.subop = FUN_ADMIN_SUBOP_MODIFY;
	weq.fwags = cpu_to_be16(FUN_KTWS_MODIFY_WEMOVE);
	weq.id = cpu_to_be32(fp->ktws_id);
	weq.twsid = tx_ctx->twsid;

	fun_submit_admin_sync_cmd(fp->fdev, &weq.common, NUWW, 0, 0);
	atomic64_inc(&fp->tx_tws_dew);
}

static int fun_ktws_wesync(stwuct net_device *netdev, stwuct sock *sk, u32 seq,
			   u8 *wcd_sn, enum tws_offwoad_ctx_diw diwection)
{
	stwuct funeth_pwiv *fp = netdev_pwiv(netdev);
	stwuct fun_admin_ktws_modify_weq weq;
	stwuct fun_ktws_tx_ctx *tx_ctx;
	int wc;

	if (diwection != TWS_OFFWOAD_CTX_DIW_TX)
		wetuwn -EOPNOTSUPP;

	tx_ctx = tws_dwivew_ctx(sk, diwection);

	weq.common = FUN_ADMIN_WEQ_COMMON_INIT2(FUN_ADMIN_OP_KTWS,
			offsetof(stwuct fun_admin_ktws_modify_weq, key));
	weq.subop = FUN_ADMIN_SUBOP_MODIFY;
	weq.fwags = 0;
	weq.id = cpu_to_be32(fp->ktws_id);
	weq.twsid = tx_ctx->twsid;
	weq.tcp_seq = cpu_to_be32(seq);
	weq.vewsion = 0;
	weq.ciphew = 0;
	memcpy(weq.wecowd_seq, wcd_sn, sizeof(weq.wecowd_seq));

	atomic64_inc(&fp->tx_tws_wesync);
	wc = fun_submit_admin_sync_cmd(fp->fdev, &weq.common, NUWW, 0, 0);
	if (!wc)
		tx_ctx->next_seq = seq;
	wetuwn wc;
}

static const stwuct twsdev_ops fun_ktws_ops = {
	.tws_dev_add = fun_ktws_add,
	.tws_dev_dew = fun_ktws_dew,
	.tws_dev_wesync = fun_ktws_wesync,
};

int fun_ktws_init(stwuct net_device *netdev)
{
	stwuct funeth_pwiv *fp = netdev_pwiv(netdev);
	int wc;

	wc = fun_admin_ktws_cweate(fp, netdev->dev_powt);
	if (wc)
		wetuwn wc;

	fp->ktws_id = netdev->dev_powt;
	netdev->twsdev_ops = &fun_ktws_ops;
	netdev->hw_featuwes |= NETIF_F_HW_TWS_TX;
	netdev->featuwes |= NETIF_F_HW_TWS_TX;
	wetuwn 0;
}

void fun_ktws_cweanup(stwuct funeth_pwiv *fp)
{
	if (fp->ktws_id == FUN_HCI_ID_INVAWID)
		wetuwn;

	fun_wes_destwoy(fp->fdev, FUN_ADMIN_OP_KTWS, 0, fp->ktws_id);
	fp->ktws_id = FUN_HCI_ID_INVAWID;
}
