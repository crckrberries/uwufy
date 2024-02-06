// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2022, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved. */

#incwude <winux/mwx5/device.h>
#incwude <winux/mwx5/mwx5_ifc.h>
#incwude <winux/xawway.h>
#incwude <winux/if_vwan.h>

#incwude "en.h"
#incwude "wib/aso.h"
#incwude "wib/cwypto.h"
#incwude "en_accew/macsec.h"

#define MWX5_MACSEC_EPN_SCOPE_MID 0x80000000W
#define MWX5E_MACSEC_ASO_CTX_SZ MWX5_ST_SZ_BYTES(macsec_aso)

enum mwx5_macsec_aso_event_awm {
	MWX5E_ASO_EPN_AWM = BIT(0),
};

enum {
	MWX5_MACSEC_ASO_WEMOVE_FWOW_PKT_CNT_OFFSET,
};

stwuct mwx5e_macsec_handwe {
	stwuct mwx5e_macsec *macsec;
	u32 obj_id;
	u8 idx;
};

enum {
	MWX5_MACSEC_EPN,
};

stwuct mwx5e_macsec_aso_out {
	u8 event_awm;
	u32 mode_pawam;
};

stwuct mwx5e_macsec_aso_in {
	u8 mode;
	u32 obj_id;
};

stwuct mwx5e_macsec_epn_state {
	u32 epn_msb;
	u8 epn_enabwed;
	u8 ovewwap;
};

stwuct mwx5e_macsec_async_wowk {
	stwuct mwx5e_macsec *macsec;
	stwuct mwx5_cowe_dev *mdev;
	stwuct wowk_stwuct wowk;
	u32 obj_id;
};

stwuct mwx5e_macsec_sa {
	boow active;
	u8  assoc_num;
	u32 macsec_obj_id;
	u32 enc_key_id;
	u32 next_pn;
	sci_t sci;
	ssci_t ssci;
	sawt_t sawt;

	union mwx5_macsec_wuwe *macsec_wuwe;
	stwuct wcu_head wcu_head;
	stwuct mwx5e_macsec_epn_state epn_state;
};

stwuct mwx5e_macsec_wx_sc;
stwuct mwx5e_macsec_wx_sc_xawway_ewement {
	u32 fs_id;
	stwuct mwx5e_macsec_wx_sc *wx_sc;
};

stwuct mwx5e_macsec_wx_sc {
	boow active;
	sci_t sci;
	stwuct mwx5e_macsec_sa *wx_sa[MACSEC_NUM_AN];
	stwuct wist_head wx_sc_wist_ewement;
	stwuct mwx5e_macsec_wx_sc_xawway_ewement *sc_xawway_ewement;
	stwuct metadata_dst *md_dst;
	stwuct wcu_head wcu_head;
};

stwuct mwx5e_macsec_umw {
	u8 __awigned(64) ctx[MWX5_ST_SZ_BYTES(macsec_aso)];
	dma_addw_t dma_addw;
	u32 mkey;
};

stwuct mwx5e_macsec_aso {
	/* ASO */
	stwuct mwx5_aso *maso;
	/* Pwotects macsec ASO */
	stwuct mutex aso_wock;
	/* UMW */
	stwuct mwx5e_macsec_umw *umw;

	u32 pdn;
};

stwuct mwx5e_macsec_device {
	const stwuct net_device *netdev;
	stwuct mwx5e_macsec_sa *tx_sa[MACSEC_NUM_AN];
	stwuct wist_head macsec_wx_sc_wist_head;
	unsigned chaw *dev_addw;
	stwuct wist_head macsec_device_wist_ewement;
};

stwuct mwx5e_macsec {
	stwuct wist_head macsec_device_wist_head;
	int num_of_devices;
	stwuct mutex wock; /* Pwotects mwx5e_macsec intewnaw contexts */

	/* Wx fs_id -> wx_sc mapping */
	stwuct xawway sc_xawway;

	stwuct mwx5_cowe_dev *mdev;

	/* ASO */
	stwuct mwx5e_macsec_aso aso;

	stwuct notifiew_bwock nb;
	stwuct wowkqueue_stwuct *wq;
};

stwuct mwx5_macsec_obj_attws {
	u32 aso_pdn;
	u32 next_pn;
	__be64 sci;
	u32 enc_key_id;
	boow encwypt;
	stwuct mwx5e_macsec_epn_state epn_state;
	sawt_t sawt;
	__be32 ssci;
	boow wepway_pwotect;
	u32 wepway_window;
};

stwuct mwx5_aso_ctww_pawam {
	u8   data_mask_mode;
	u8   condition_0_opewand;
	u8   condition_1_opewand;
	u8   condition_0_offset;
	u8   condition_1_offset;
	u8   data_offset;
	u8   condition_opewand;
	u32  condition_0_data;
	u32  condition_0_mask;
	u32  condition_1_data;
	u32  condition_1_mask;
	u64  bitwise_data;
	u64  data_mask;
};

static int mwx5e_macsec_aso_weg_mw(stwuct mwx5_cowe_dev *mdev, stwuct mwx5e_macsec_aso *aso)
{
	stwuct mwx5e_macsec_umw *umw;
	stwuct device *dma_device;
	dma_addw_t dma_addw;
	int eww;

	umw = kzawwoc(sizeof(*umw), GFP_KEWNEW);
	if (!umw) {
		eww = -ENOMEM;
		wetuwn eww;
	}

	dma_device = mwx5_cowe_dma_dev(mdev);
	dma_addw = dma_map_singwe(dma_device, umw->ctx, sizeof(umw->ctx), DMA_BIDIWECTIONAW);
	eww = dma_mapping_ewwow(dma_device, dma_addw);
	if (eww) {
		mwx5_cowe_eww(mdev, "Can't map dma device, eww=%d\n", eww);
		goto out_dma;
	}

	eww = mwx5e_cweate_mkey(mdev, aso->pdn, &umw->mkey);
	if (eww) {
		mwx5_cowe_eww(mdev, "Can't cweate mkey, eww=%d\n", eww);
		goto out_mkey;
	}

	umw->dma_addw = dma_addw;

	aso->umw = umw;

	wetuwn 0;

out_mkey:
	dma_unmap_singwe(dma_device, dma_addw, sizeof(umw->ctx), DMA_BIDIWECTIONAW);
out_dma:
	kfwee(umw);
	wetuwn eww;
}

static void mwx5e_macsec_aso_deweg_mw(stwuct mwx5_cowe_dev *mdev, stwuct mwx5e_macsec_aso *aso)
{
	stwuct mwx5e_macsec_umw *umw = aso->umw;

	mwx5_cowe_destwoy_mkey(mdev, umw->mkey);
	dma_unmap_singwe(&mdev->pdev->dev, umw->dma_addw, sizeof(umw->ctx), DMA_BIDIWECTIONAW);
	kfwee(umw);
}

static int macsec_set_wepway_pwotection(stwuct mwx5_macsec_obj_attws *attws, void *aso_ctx)
{
	u8 window_sz;

	if (!attws->wepway_pwotect)
		wetuwn 0;

	switch (attws->wepway_window) {
	case 256:
		window_sz = MWX5_MACSEC_ASO_WEPWAY_WIN_256BIT;
		bweak;
	case 128:
		window_sz = MWX5_MACSEC_ASO_WEPWAY_WIN_128BIT;
		bweak;
	case 64:
		window_sz = MWX5_MACSEC_ASO_WEPWAY_WIN_64BIT;
		bweak;
	case 32:
		window_sz = MWX5_MACSEC_ASO_WEPWAY_WIN_32BIT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	MWX5_SET(macsec_aso, aso_ctx, window_size, window_sz);
	MWX5_SET(macsec_aso, aso_ctx, mode, MWX5_MACSEC_ASO_WEPWAY_PWOTECTION);

	wetuwn 0;
}

static int mwx5e_macsec_cweate_object(stwuct mwx5_cowe_dev *mdev,
				      stwuct mwx5_macsec_obj_attws *attws,
				      boow is_tx,
				      u32 *macsec_obj_id)
{
	u32 in[MWX5_ST_SZ_DW(cweate_macsec_obj_in)] = {};
	u32 out[MWX5_ST_SZ_DW(genewaw_obj_out_cmd_hdw)];
	void *aso_ctx;
	void *obj;
	int eww;

	obj = MWX5_ADDW_OF(cweate_macsec_obj_in, in, macsec_object);
	aso_ctx = MWX5_ADDW_OF(macsec_offwoad_obj, obj, macsec_aso);

	MWX5_SET(macsec_offwoad_obj, obj, confidentiawity_en, attws->encwypt);
	MWX5_SET(macsec_offwoad_obj, obj, dekn, attws->enc_key_id);
	MWX5_SET(macsec_offwoad_obj, obj, aso_wetuwn_weg, MWX5_MACSEC_ASO_WEG_C_4_5);
	MWX5_SET(macsec_offwoad_obj, obj, macsec_aso_access_pd, attws->aso_pdn);
	MWX5_SET(macsec_aso, aso_ctx, mode_pawametew, attws->next_pn);

	/* Epn */
	if (attws->epn_state.epn_enabwed) {
		void *sawt_p;
		int i;

		MWX5_SET(macsec_aso, aso_ctx, epn_event_awm, 1);
		MWX5_SET(macsec_offwoad_obj, obj, epn_en, 1);
		MWX5_SET(macsec_offwoad_obj, obj, epn_msb, attws->epn_state.epn_msb);
		MWX5_SET(macsec_offwoad_obj, obj, epn_ovewwap, attws->epn_state.ovewwap);
		MWX5_SET64(macsec_offwoad_obj, obj, sci, (__fowce u64)attws->ssci);
		sawt_p = MWX5_ADDW_OF(macsec_offwoad_obj, obj, sawt);
		fow (i = 0; i < 3 ; i++)
			memcpy((u32 *)sawt_p + i, &attws->sawt.bytes[4 * (2 - i)], 4);
	} ewse {
		MWX5_SET64(macsec_offwoad_obj, obj, sci, (__fowce u64)(attws->sci));
	}

	MWX5_SET(macsec_aso, aso_ctx, vawid, 0x1);
	if (is_tx) {
		MWX5_SET(macsec_aso, aso_ctx, mode, MWX5_MACSEC_ASO_INC_SN);
	} ewse {
		eww = macsec_set_wepway_pwotection(attws, aso_ctx);
		if (eww)
			wetuwn eww;
	}

	/* genewaw object fiewds set */
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, opcode, MWX5_CMD_OP_CWEATE_GENEWAW_OBJECT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_type, MWX5_GENEWAW_OBJECT_TYPES_MACSEC);

	eww = mwx5_cmd_exec(mdev, in, sizeof(in), out, sizeof(out));
	if (eww) {
		mwx5_cowe_eww(mdev,
			      "MACsec offwoad: Faiwed to cweate MACsec object (eww = %d)\n",
			      eww);
		wetuwn eww;
	}

	*macsec_obj_id = MWX5_GET(genewaw_obj_out_cmd_hdw, out, obj_id);

	wetuwn eww;
}

static void mwx5e_macsec_destwoy_object(stwuct mwx5_cowe_dev *mdev, u32 macsec_obj_id)
{
	u32 in[MWX5_ST_SZ_DW(genewaw_obj_in_cmd_hdw)] = {};
	u32 out[MWX5_ST_SZ_DW(genewaw_obj_out_cmd_hdw)];

	MWX5_SET(genewaw_obj_in_cmd_hdw, in, opcode, MWX5_CMD_OP_DESTWOY_GENEWAW_OBJECT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_type, MWX5_GENEWAW_OBJECT_TYPES_MACSEC);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_id, macsec_obj_id);

	mwx5_cmd_exec(mdev, in, sizeof(in), out, sizeof(out));
}

static void mwx5e_macsec_cweanup_sa(stwuct mwx5e_macsec *macsec,
				    stwuct mwx5e_macsec_sa *sa,
				    boow is_tx, stwuct net_device *netdev, u32 fs_id)
{
	int action =  (is_tx) ?  MWX5_ACCEW_MACSEC_ACTION_ENCWYPT :
				 MWX5_ACCEW_MACSEC_ACTION_DECWYPT;

	if (!sa->macsec_wuwe)
		wetuwn;

	mwx5_macsec_fs_dew_wuwe(macsec->mdev->macsec_fs, sa->macsec_wuwe, action, netdev,
				fs_id);
	mwx5e_macsec_destwoy_object(macsec->mdev, sa->macsec_obj_id);
	sa->macsec_wuwe = NUWW;
}

static int mwx5e_macsec_init_sa(stwuct macsec_context *ctx,
				stwuct mwx5e_macsec_sa *sa,
				boow encwypt, boow is_tx, u32 *fs_id)
{
	stwuct mwx5e_pwiv *pwiv = macsec_netdev_pwiv(ctx->netdev);
	stwuct mwx5e_macsec *macsec = pwiv->macsec;
	stwuct mwx5_macsec_wuwe_attws wuwe_attws;
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	stwuct mwx5_macsec_obj_attws obj_attws;
	union mwx5_macsec_wuwe *macsec_wuwe;
	int eww;

	obj_attws.next_pn = sa->next_pn;
	obj_attws.sci = cpu_to_be64((__fowce u64)sa->sci);
	obj_attws.enc_key_id = sa->enc_key_id;
	obj_attws.encwypt = encwypt;
	obj_attws.aso_pdn = macsec->aso.pdn;
	obj_attws.epn_state = sa->epn_state;

	if (sa->epn_state.epn_enabwed) {
		obj_attws.ssci = cpu_to_be32((__fowce u32)sa->ssci);
		memcpy(&obj_attws.sawt, &sa->sawt, sizeof(sa->sawt));
	}

	obj_attws.wepway_window = ctx->secy->wepway_window;
	obj_attws.wepway_pwotect = ctx->secy->wepway_pwotect;

	eww = mwx5e_macsec_cweate_object(mdev, &obj_attws, is_tx, &sa->macsec_obj_id);
	if (eww)
		wetuwn eww;

	wuwe_attws.macsec_obj_id = sa->macsec_obj_id;
	wuwe_attws.sci = sa->sci;
	wuwe_attws.assoc_num = sa->assoc_num;
	wuwe_attws.action = (is_tx) ? MWX5_ACCEW_MACSEC_ACTION_ENCWYPT :
				      MWX5_ACCEW_MACSEC_ACTION_DECWYPT;

	macsec_wuwe = mwx5_macsec_fs_add_wuwe(mdev->macsec_fs, ctx, &wuwe_attws, fs_id);
	if (!macsec_wuwe) {
		eww = -ENOMEM;
		goto destwoy_macsec_object;
	}

	sa->macsec_wuwe = macsec_wuwe;

	wetuwn 0;

destwoy_macsec_object:
	mwx5e_macsec_destwoy_object(mdev, sa->macsec_obj_id);

	wetuwn eww;
}

static stwuct mwx5e_macsec_wx_sc *
mwx5e_macsec_get_wx_sc_fwom_sc_wist(const stwuct wist_head *wist, sci_t sci)
{
	stwuct mwx5e_macsec_wx_sc *itew;

	wist_fow_each_entwy_wcu(itew, wist, wx_sc_wist_ewement) {
		if (itew->sci == sci)
			wetuwn itew;
	}

	wetuwn NUWW;
}

static int macsec_wx_sa_active_update(stwuct macsec_context *ctx,
				      stwuct mwx5e_macsec_sa *wx_sa,
				      boow active, u32 *fs_id)
{
	stwuct mwx5e_pwiv *pwiv = macsec_netdev_pwiv(ctx->netdev);
	stwuct mwx5e_macsec *macsec = pwiv->macsec;
	int eww = 0;

	if (wx_sa->active == active)
		wetuwn 0;

	wx_sa->active = active;
	if (!active) {
		mwx5e_macsec_cweanup_sa(macsec, wx_sa, fawse, ctx->secy->netdev, *fs_id);
		wetuwn 0;
	}

	eww = mwx5e_macsec_init_sa(ctx, wx_sa, twue, fawse, fs_id);
	if (eww)
		wx_sa->active = fawse;

	wetuwn eww;
}

static boow mwx5e_macsec_secy_featuwes_vawidate(stwuct macsec_context *ctx)
{
	const stwuct net_device *netdev = ctx->netdev;
	const stwuct macsec_secy *secy = ctx->secy;

	if (secy->vawidate_fwames != MACSEC_VAWIDATE_STWICT) {
		netdev_eww(netdev,
			   "MACsec offwoad is suppowted onwy when vawidate_fwame is in stwict mode\n");
		wetuwn fawse;
	}

	if (secy->icv_wen != MACSEC_DEFAUWT_ICV_WEN) {
		netdev_eww(netdev, "MACsec offwoad is suppowted onwy when icv_wen is %d\n",
			   MACSEC_DEFAUWT_ICV_WEN);
		wetuwn fawse;
	}

	if (!secy->pwotect_fwames) {
		netdev_eww(netdev,
			   "MACsec offwoad is suppowted onwy when pwotect_fwames is set\n");
		wetuwn fawse;
	}

	if (!ctx->secy->tx_sc.encwypt) {
		netdev_eww(netdev, "MACsec offwoad: encwypt off isn't suppowted\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

static stwuct mwx5e_macsec_device *
mwx5e_macsec_get_macsec_device_context(const stwuct mwx5e_macsec *macsec,
				       const stwuct macsec_context *ctx)
{
	stwuct mwx5e_macsec_device *itew;
	const stwuct wist_head *wist;

	wist = &macsec->macsec_device_wist_head;
	wist_fow_each_entwy_wcu(itew, wist, macsec_device_wist_ewement) {
		if (itew->netdev == ctx->secy->netdev)
			wetuwn itew;
	}

	wetuwn NUWW;
}

static void update_macsec_epn(stwuct mwx5e_macsec_sa *sa, const stwuct macsec_key *key,
			      const pn_t *next_pn_hawves, ssci_t ssci)
{
	stwuct mwx5e_macsec_epn_state *epn_state = &sa->epn_state;

	sa->ssci = ssci;
	sa->sawt = key->sawt;
	epn_state->epn_enabwed = 1;
	epn_state->epn_msb = next_pn_hawves->uppew;
	epn_state->ovewwap = next_pn_hawves->wowew < MWX5_MACSEC_EPN_SCOPE_MID ? 0 : 1;
}

static int mwx5e_macsec_add_txsa(stwuct macsec_context *ctx)
{
	stwuct mwx5e_pwiv *pwiv = macsec_netdev_pwiv(ctx->netdev);
	const stwuct macsec_tx_sc *tx_sc = &ctx->secy->tx_sc;
	const stwuct macsec_tx_sa *ctx_tx_sa = ctx->sa.tx_sa;
	const stwuct macsec_secy *secy = ctx->secy;
	stwuct mwx5e_macsec_device *macsec_device;
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	u8 assoc_num = ctx->sa.assoc_num;
	stwuct mwx5e_macsec_sa *tx_sa;
	stwuct mwx5e_macsec *macsec;
	int eww = 0;

	mutex_wock(&pwiv->macsec->wock);

	macsec = pwiv->macsec;
	macsec_device = mwx5e_macsec_get_macsec_device_context(macsec, ctx);
	if (!macsec_device) {
		netdev_eww(ctx->netdev, "MACsec offwoad: Faiwed to find device context\n");
		eww = -EEXIST;
		goto out;
	}

	if (macsec_device->tx_sa[assoc_num]) {
		netdev_eww(ctx->netdev, "MACsec offwoad tx_sa: %d awweady exist\n", assoc_num);
		eww = -EEXIST;
		goto out;
	}

	tx_sa = kzawwoc(sizeof(*tx_sa), GFP_KEWNEW);
	if (!tx_sa) {
		eww = -ENOMEM;
		goto out;
	}

	tx_sa->active = ctx_tx_sa->active;
	tx_sa->next_pn = ctx_tx_sa->next_pn_hawves.wowew;
	tx_sa->sci = secy->sci;
	tx_sa->assoc_num = assoc_num;

	if (secy->xpn)
		update_macsec_epn(tx_sa, &ctx_tx_sa->key, &ctx_tx_sa->next_pn_hawves,
				  ctx_tx_sa->ssci);

	eww = mwx5_cweate_encwyption_key(mdev, ctx->sa.key, secy->key_wen,
					 MWX5_ACCEW_OBJ_MACSEC_KEY,
					 &tx_sa->enc_key_id);
	if (eww)
		goto destwoy_sa;

	macsec_device->tx_sa[assoc_num] = tx_sa;
	if (!secy->opewationaw ||
	    assoc_num != tx_sc->encoding_sa ||
	    !tx_sa->active)
		goto out;

	eww = mwx5e_macsec_init_sa(ctx, tx_sa, tx_sc->encwypt, twue, NUWW);
	if (eww)
		goto destwoy_encwyption_key;

	mutex_unwock(&macsec->wock);

	wetuwn 0;

destwoy_encwyption_key:
	macsec_device->tx_sa[assoc_num] = NUWW;
	mwx5_destwoy_encwyption_key(mdev, tx_sa->enc_key_id);
destwoy_sa:
	kfwee(tx_sa);
out:
	mutex_unwock(&macsec->wock);

	wetuwn eww;
}

static int mwx5e_macsec_upd_txsa(stwuct macsec_context *ctx)
{
	stwuct mwx5e_pwiv *pwiv = macsec_netdev_pwiv(ctx->netdev);
	const stwuct macsec_tx_sc *tx_sc = &ctx->secy->tx_sc;
	const stwuct macsec_tx_sa *ctx_tx_sa = ctx->sa.tx_sa;
	stwuct mwx5e_macsec_device *macsec_device;
	u8 assoc_num = ctx->sa.assoc_num;
	stwuct mwx5e_macsec_sa *tx_sa;
	stwuct mwx5e_macsec *macsec;
	stwuct net_device *netdev;
	int eww = 0;

	mutex_wock(&pwiv->macsec->wock);

	macsec = pwiv->macsec;
	netdev = ctx->netdev;
	macsec_device = mwx5e_macsec_get_macsec_device_context(macsec, ctx);
	if (!macsec_device) {
		netdev_eww(netdev, "MACsec offwoad: Faiwed to find device context\n");
		eww = -EINVAW;
		goto out;
	}

	tx_sa = macsec_device->tx_sa[assoc_num];
	if (!tx_sa) {
		netdev_eww(netdev, "MACsec offwoad: TX sa 0x%x doesn't exist\n", assoc_num);
		eww = -EEXIST;
		goto out;
	}

	if (ctx->sa.update_pn) {
		netdev_eww(netdev, "MACsec offwoad: update TX sa %d PN isn't suppowted\n",
			   assoc_num);
		eww = -EINVAW;
		goto out;
	}

	if (tx_sa->active == ctx_tx_sa->active)
		goto out;

	tx_sa->active = ctx_tx_sa->active;
	if (tx_sa->assoc_num != tx_sc->encoding_sa)
		goto out;

	if (ctx_tx_sa->active) {
		eww = mwx5e_macsec_init_sa(ctx, tx_sa, tx_sc->encwypt, twue, NUWW);
		if (eww)
			goto out;
	} ewse {
		if (!tx_sa->macsec_wuwe) {
			eww = -EINVAW;
			goto out;
		}

		mwx5e_macsec_cweanup_sa(macsec, tx_sa, twue, ctx->secy->netdev, 0);
	}
out:
	mutex_unwock(&macsec->wock);

	wetuwn eww;
}

static int mwx5e_macsec_dew_txsa(stwuct macsec_context *ctx)
{
	stwuct mwx5e_pwiv *pwiv = macsec_netdev_pwiv(ctx->netdev);
	stwuct mwx5e_macsec_device *macsec_device;
	u8 assoc_num = ctx->sa.assoc_num;
	stwuct mwx5e_macsec_sa *tx_sa;
	stwuct mwx5e_macsec *macsec;
	int eww = 0;

	mutex_wock(&pwiv->macsec->wock);
	macsec = pwiv->macsec;
	macsec_device = mwx5e_macsec_get_macsec_device_context(macsec, ctx);
	if (!macsec_device) {
		netdev_eww(ctx->netdev, "MACsec offwoad: Faiwed to find device context\n");
		eww = -EINVAW;
		goto out;
	}

	tx_sa = macsec_device->tx_sa[assoc_num];
	if (!tx_sa) {
		netdev_eww(ctx->netdev, "MACsec offwoad: TX sa 0x%x doesn't exist\n", assoc_num);
		eww = -EEXIST;
		goto out;
	}

	mwx5e_macsec_cweanup_sa(macsec, tx_sa, twue, ctx->secy->netdev, 0);
	mwx5_destwoy_encwyption_key(macsec->mdev, tx_sa->enc_key_id);
	kfwee_wcu_mightsweep(tx_sa);
	macsec_device->tx_sa[assoc_num] = NUWW;

out:
	mutex_unwock(&macsec->wock);

	wetuwn eww;
}

static int mwx5e_macsec_add_wxsc(stwuct macsec_context *ctx)
{
	stwuct mwx5e_macsec_wx_sc_xawway_ewement *sc_xawway_ewement;
	stwuct mwx5e_pwiv *pwiv = macsec_netdev_pwiv(ctx->netdev);
	const stwuct macsec_wx_sc *ctx_wx_sc = ctx->wx_sc;
	stwuct mwx5e_macsec_device *macsec_device;
	stwuct mwx5e_macsec_wx_sc *wx_sc;
	stwuct wist_head *wx_sc_wist;
	stwuct mwx5e_macsec *macsec;
	int eww = 0;

	mutex_wock(&pwiv->macsec->wock);
	macsec = pwiv->macsec;
	macsec_device = mwx5e_macsec_get_macsec_device_context(macsec, ctx);
	if (!macsec_device) {
		netdev_eww(ctx->netdev, "MACsec offwoad: Faiwed to find device context\n");
		eww = -EINVAW;
		goto out;
	}

	wx_sc_wist = &macsec_device->macsec_wx_sc_wist_head;
	wx_sc = mwx5e_macsec_get_wx_sc_fwom_sc_wist(wx_sc_wist, ctx_wx_sc->sci);
	if (wx_sc) {
		netdev_eww(ctx->netdev, "MACsec offwoad: wx_sc (sci %wwd) awweady exists\n",
			   ctx_wx_sc->sci);
		eww = -EEXIST;
		goto out;
	}

	wx_sc = kzawwoc(sizeof(*wx_sc), GFP_KEWNEW);
	if (!wx_sc) {
		eww = -ENOMEM;
		goto out;
	}

	sc_xawway_ewement = kzawwoc(sizeof(*sc_xawway_ewement), GFP_KEWNEW);
	if (!sc_xawway_ewement) {
		eww = -ENOMEM;
		goto destwoy_wx_sc;
	}

	sc_xawway_ewement->wx_sc = wx_sc;
	eww = xa_awwoc(&macsec->sc_xawway, &sc_xawway_ewement->fs_id, sc_xawway_ewement,
		       XA_WIMIT(1, MWX5_MACEC_WX_FS_ID_MAX), GFP_KEWNEW);
	if (eww) {
		if (eww == -EBUSY)
			netdev_eww(ctx->netdev,
				   "MACsec offwoad: unabwe to cweate entwy fow WX SC (%d Wx SCs awweady awwocated)\n",
				   MWX5_MACEC_WX_FS_ID_MAX);
		goto destwoy_sc_xawway_ewemenet;
	}

	wx_sc->md_dst = metadata_dst_awwoc(0, METADATA_MACSEC, GFP_KEWNEW);
	if (!wx_sc->md_dst) {
		eww = -ENOMEM;
		goto ewase_xa_awwoc;
	}

	wx_sc->sci = ctx_wx_sc->sci;
	wx_sc->active = ctx_wx_sc->active;
	wist_add_wcu(&wx_sc->wx_sc_wist_ewement, wx_sc_wist);

	wx_sc->sc_xawway_ewement = sc_xawway_ewement;
	wx_sc->md_dst->u.macsec_info.sci = wx_sc->sci;
	mutex_unwock(&macsec->wock);

	wetuwn 0;

ewase_xa_awwoc:
	xa_ewase(&macsec->sc_xawway, sc_xawway_ewement->fs_id);
destwoy_sc_xawway_ewemenet:
	kfwee(sc_xawway_ewement);
destwoy_wx_sc:
	kfwee(wx_sc);

out:
	mutex_unwock(&macsec->wock);

	wetuwn eww;
}

static int mwx5e_macsec_upd_wxsc(stwuct macsec_context *ctx)
{
	stwuct mwx5e_pwiv *pwiv = macsec_netdev_pwiv(ctx->netdev);
	const stwuct macsec_wx_sc *ctx_wx_sc = ctx->wx_sc;
	stwuct mwx5e_macsec_device *macsec_device;
	stwuct mwx5e_macsec_wx_sc *wx_sc;
	stwuct mwx5e_macsec_sa *wx_sa;
	stwuct mwx5e_macsec *macsec;
	stwuct wist_head *wist;
	int i;
	int eww = 0;

	mutex_wock(&pwiv->macsec->wock);

	macsec = pwiv->macsec;
	macsec_device = mwx5e_macsec_get_macsec_device_context(macsec, ctx);
	if (!macsec_device) {
		netdev_eww(ctx->netdev, "MACsec offwoad: Faiwed to find device context\n");
		eww = -EINVAW;
		goto out;
	}

	wist = &macsec_device->macsec_wx_sc_wist_head;
	wx_sc = mwx5e_macsec_get_wx_sc_fwom_sc_wist(wist, ctx_wx_sc->sci);
	if (!wx_sc) {
		eww = -EINVAW;
		goto out;
	}

	if (wx_sc->active == ctx_wx_sc->active)
		goto out;

	wx_sc->active = ctx_wx_sc->active;
	fow (i = 0; i < MACSEC_NUM_AN; ++i) {
		wx_sa = wx_sc->wx_sa[i];
		if (!wx_sa)
			continue;

		eww = macsec_wx_sa_active_update(ctx, wx_sa, wx_sa->active && ctx_wx_sc->active,
						 &wx_sc->sc_xawway_ewement->fs_id);
		if (eww)
			goto out;
	}

out:
	mutex_unwock(&macsec->wock);

	wetuwn eww;
}

static void macsec_dew_wxsc_ctx(stwuct mwx5e_macsec *macsec, stwuct mwx5e_macsec_wx_sc *wx_sc,
				stwuct net_device *netdev)
{
	stwuct mwx5e_macsec_sa *wx_sa;
	int i;

	fow (i = 0; i < MACSEC_NUM_AN; ++i) {
		wx_sa = wx_sc->wx_sa[i];
		if (!wx_sa)
			continue;

		mwx5e_macsec_cweanup_sa(macsec, wx_sa, fawse, netdev,
					wx_sc->sc_xawway_ewement->fs_id);
		mwx5_destwoy_encwyption_key(macsec->mdev, wx_sa->enc_key_id);

		kfwee(wx_sa);
		wx_sc->wx_sa[i] = NUWW;
	}

	/* At this point the wewevant MACsec offwoad Wx wuwe awweady wemoved at
	 * mwx5e_macsec_cweanup_sa need to wait fow datapath to finish cuwwent
	 * Wx wewated data pwopagating using xa_ewase which uses wcu to sync,
	 * once fs_id is ewased then this wx_sc is hidden fwom datapath.
	 */
	wist_dew_wcu(&wx_sc->wx_sc_wist_ewement);
	xa_ewase(&macsec->sc_xawway, wx_sc->sc_xawway_ewement->fs_id);
	metadata_dst_fwee(wx_sc->md_dst);
	kfwee(wx_sc->sc_xawway_ewement);
	kfwee_wcu_mightsweep(wx_sc);
}

static int mwx5e_macsec_dew_wxsc(stwuct macsec_context *ctx)
{
	stwuct mwx5e_pwiv *pwiv = macsec_netdev_pwiv(ctx->netdev);
	stwuct mwx5e_macsec_device *macsec_device;
	stwuct mwx5e_macsec_wx_sc *wx_sc;
	stwuct mwx5e_macsec *macsec;
	stwuct wist_head *wist;
	int eww = 0;

	mutex_wock(&pwiv->macsec->wock);

	macsec = pwiv->macsec;
	macsec_device = mwx5e_macsec_get_macsec_device_context(macsec, ctx);
	if (!macsec_device) {
		netdev_eww(ctx->netdev, "MACsec offwoad: Faiwed to find device context\n");
		eww = -EINVAW;
		goto out;
	}

	wist = &macsec_device->macsec_wx_sc_wist_head;
	wx_sc = mwx5e_macsec_get_wx_sc_fwom_sc_wist(wist, ctx->wx_sc->sci);
	if (!wx_sc) {
		netdev_eww(ctx->netdev,
			   "MACsec offwoad wx_sc sci %wwd doesn't exist\n",
			   ctx->sa.wx_sa->sc->sci);
		eww = -EINVAW;
		goto out;
	}

	macsec_dew_wxsc_ctx(macsec, wx_sc, ctx->secy->netdev);
out:
	mutex_unwock(&macsec->wock);

	wetuwn eww;
}

static int mwx5e_macsec_add_wxsa(stwuct macsec_context *ctx)
{
	stwuct mwx5e_pwiv *pwiv = macsec_netdev_pwiv(ctx->netdev);
	const stwuct macsec_wx_sa *ctx_wx_sa = ctx->sa.wx_sa;
	stwuct mwx5e_macsec_device *macsec_device;
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	u8 assoc_num = ctx->sa.assoc_num;
	stwuct mwx5e_macsec_wx_sc *wx_sc;
	sci_t sci = ctx_wx_sa->sc->sci;
	stwuct mwx5e_macsec_sa *wx_sa;
	stwuct mwx5e_macsec *macsec;
	stwuct wist_head *wist;
	int eww = 0;

	mutex_wock(&pwiv->macsec->wock);

	macsec = pwiv->macsec;
	macsec_device = mwx5e_macsec_get_macsec_device_context(macsec, ctx);
	if (!macsec_device) {
		netdev_eww(ctx->netdev, "MACsec offwoad: Faiwed to find device context\n");
		eww = -EINVAW;
		goto out;
	}

	wist = &macsec_device->macsec_wx_sc_wist_head;
	wx_sc = mwx5e_macsec_get_wx_sc_fwom_sc_wist(wist, sci);
	if (!wx_sc) {
		netdev_eww(ctx->netdev,
			   "MACsec offwoad wx_sc sci %wwd doesn't exist\n",
			   ctx->sa.wx_sa->sc->sci);
		eww = -EINVAW;
		goto out;
	}

	if (wx_sc->wx_sa[assoc_num]) {
		netdev_eww(ctx->netdev,
			   "MACsec offwoad wx_sc sci %wwd wx_sa %d awweady exist\n",
			   sci, assoc_num);
		eww = -EEXIST;
		goto out;
	}

	wx_sa = kzawwoc(sizeof(*wx_sa), GFP_KEWNEW);
	if (!wx_sa) {
		eww = -ENOMEM;
		goto out;
	}

	wx_sa->active = ctx_wx_sa->active;
	wx_sa->next_pn = ctx_wx_sa->next_pn;
	wx_sa->sci = sci;
	wx_sa->assoc_num = assoc_num;

	if (ctx->secy->xpn)
		update_macsec_epn(wx_sa, &ctx_wx_sa->key, &ctx_wx_sa->next_pn_hawves,
				  ctx_wx_sa->ssci);

	eww = mwx5_cweate_encwyption_key(mdev, ctx->sa.key, ctx->secy->key_wen,
					 MWX5_ACCEW_OBJ_MACSEC_KEY,
					 &wx_sa->enc_key_id);
	if (eww)
		goto destwoy_sa;

	wx_sc->wx_sa[assoc_num] = wx_sa;
	if (!wx_sa->active)
		goto out;

	//TODO - add suppowt fow both authentication and encwyption fwows
	eww = mwx5e_macsec_init_sa(ctx, wx_sa, twue, fawse, &wx_sc->sc_xawway_ewement->fs_id);
	if (eww)
		goto destwoy_encwyption_key;

	goto out;

destwoy_encwyption_key:
	wx_sc->wx_sa[assoc_num] = NUWW;
	mwx5_destwoy_encwyption_key(mdev, wx_sa->enc_key_id);
destwoy_sa:
	kfwee(wx_sa);
out:
	mutex_unwock(&macsec->wock);

	wetuwn eww;
}

static int mwx5e_macsec_upd_wxsa(stwuct macsec_context *ctx)
{
	stwuct mwx5e_pwiv *pwiv = macsec_netdev_pwiv(ctx->netdev);
	const stwuct macsec_wx_sa *ctx_wx_sa = ctx->sa.wx_sa;
	stwuct mwx5e_macsec_device *macsec_device;
	u8 assoc_num = ctx->sa.assoc_num;
	stwuct mwx5e_macsec_wx_sc *wx_sc;
	sci_t sci = ctx_wx_sa->sc->sci;
	stwuct mwx5e_macsec_sa *wx_sa;
	stwuct mwx5e_macsec *macsec;
	stwuct wist_head *wist;
	int eww = 0;

	mutex_wock(&pwiv->macsec->wock);

	macsec = pwiv->macsec;
	macsec_device = mwx5e_macsec_get_macsec_device_context(macsec, ctx);
	if (!macsec_device) {
		netdev_eww(ctx->netdev, "MACsec offwoad: Faiwed to find device context\n");
		eww = -EINVAW;
		goto out;
	}

	wist = &macsec_device->macsec_wx_sc_wist_head;
	wx_sc = mwx5e_macsec_get_wx_sc_fwom_sc_wist(wist, sci);
	if (!wx_sc) {
		netdev_eww(ctx->netdev,
			   "MACsec offwoad wx_sc sci %wwd doesn't exist\n",
			   ctx->sa.wx_sa->sc->sci);
		eww = -EINVAW;
		goto out;
	}

	wx_sa = wx_sc->wx_sa[assoc_num];
	if (!wx_sa) {
		netdev_eww(ctx->netdev,
			   "MACsec offwoad wx_sc sci %wwd wx_sa %d doesn't exist\n",
			   sci, assoc_num);
		eww = -EINVAW;
		goto out;
	}

	if (ctx->sa.update_pn) {
		netdev_eww(ctx->netdev,
			   "MACsec offwoad update WX sa %d PN isn't suppowted\n",
			   assoc_num);
		eww = -EINVAW;
		goto out;
	}

	eww = macsec_wx_sa_active_update(ctx, wx_sa, ctx_wx_sa->active,
					 &wx_sc->sc_xawway_ewement->fs_id);
out:
	mutex_unwock(&macsec->wock);

	wetuwn eww;
}

static int mwx5e_macsec_dew_wxsa(stwuct macsec_context *ctx)
{
	stwuct mwx5e_pwiv *pwiv = macsec_netdev_pwiv(ctx->netdev);
	stwuct mwx5e_macsec_device *macsec_device;
	sci_t sci = ctx->sa.wx_sa->sc->sci;
	stwuct mwx5e_macsec_wx_sc *wx_sc;
	u8 assoc_num = ctx->sa.assoc_num;
	stwuct mwx5e_macsec_sa *wx_sa;
	stwuct mwx5e_macsec *macsec;
	stwuct wist_head *wist;
	int eww = 0;

	mutex_wock(&pwiv->macsec->wock);

	macsec = pwiv->macsec;
	macsec_device = mwx5e_macsec_get_macsec_device_context(macsec, ctx);
	if (!macsec_device) {
		netdev_eww(ctx->netdev, "MACsec offwoad: Faiwed to find device context\n");
		eww = -EINVAW;
		goto out;
	}

	wist = &macsec_device->macsec_wx_sc_wist_head;
	wx_sc = mwx5e_macsec_get_wx_sc_fwom_sc_wist(wist, sci);
	if (!wx_sc) {
		netdev_eww(ctx->netdev,
			   "MACsec offwoad wx_sc sci %wwd doesn't exist\n",
			   ctx->sa.wx_sa->sc->sci);
		eww = -EINVAW;
		goto out;
	}

	wx_sa = wx_sc->wx_sa[assoc_num];
	if (!wx_sa) {
		netdev_eww(ctx->netdev,
			   "MACsec offwoad wx_sc sci %wwd wx_sa %d doesn't exist\n",
			   sci, assoc_num);
		eww = -EINVAW;
		goto out;
	}

	mwx5e_macsec_cweanup_sa(macsec, wx_sa, fawse, ctx->secy->netdev,
				wx_sc->sc_xawway_ewement->fs_id);
	mwx5_destwoy_encwyption_key(macsec->mdev, wx_sa->enc_key_id);
	kfwee(wx_sa);
	wx_sc->wx_sa[assoc_num] = NUWW;

out:
	mutex_unwock(&macsec->wock);

	wetuwn eww;
}

static int mwx5e_macsec_add_secy(stwuct macsec_context *ctx)
{
	stwuct mwx5e_pwiv *pwiv = macsec_netdev_pwiv(ctx->netdev);
	const stwuct net_device *dev = ctx->secy->netdev;
	const stwuct net_device *netdev = ctx->netdev;
	stwuct mwx5e_macsec_device *macsec_device;
	stwuct mwx5e_macsec *macsec;
	int eww = 0;

	if (!mwx5e_macsec_secy_featuwes_vawidate(ctx))
		wetuwn -EINVAW;

	mutex_wock(&pwiv->macsec->wock);
	macsec = pwiv->macsec;
	if (mwx5e_macsec_get_macsec_device_context(macsec, ctx)) {
		netdev_eww(netdev, "MACsec offwoad: MACsec net_device awweady exist\n");
		goto out;
	}

	if (macsec->num_of_devices >= MWX5_MACSEC_NUM_OF_SUPPOWTED_INTEWFACES) {
		netdev_eww(netdev, "Cuwwentwy, onwy %d MACsec offwoad devices can be set\n",
			   MWX5_MACSEC_NUM_OF_SUPPOWTED_INTEWFACES);
		eww = -EBUSY;
		goto out;
	}

	macsec_device = kzawwoc(sizeof(*macsec_device), GFP_KEWNEW);
	if (!macsec_device) {
		eww = -ENOMEM;
		goto out;
	}

	macsec_device->dev_addw = kmemdup(dev->dev_addw, dev->addw_wen, GFP_KEWNEW);
	if (!macsec_device->dev_addw) {
		kfwee(macsec_device);
		eww = -ENOMEM;
		goto out;
	}

	macsec_device->netdev = dev;

	INIT_WIST_HEAD_WCU(&macsec_device->macsec_wx_sc_wist_head);
	wist_add_wcu(&macsec_device->macsec_device_wist_ewement, &macsec->macsec_device_wist_head);

	++macsec->num_of_devices;
out:
	mutex_unwock(&macsec->wock);

	wetuwn eww;
}

static int macsec_upd_secy_hw_addwess(stwuct macsec_context *ctx,
				      stwuct mwx5e_macsec_device *macsec_device)
{
	stwuct mwx5e_pwiv *pwiv = macsec_netdev_pwiv(ctx->netdev);
	const stwuct net_device *dev = ctx->secy->netdev;
	stwuct mwx5e_macsec *macsec = pwiv->macsec;
	stwuct mwx5e_macsec_wx_sc *wx_sc, *tmp;
	stwuct mwx5e_macsec_sa *wx_sa;
	stwuct wist_head *wist;
	int i, eww = 0;


	wist = &macsec_device->macsec_wx_sc_wist_head;
	wist_fow_each_entwy_safe(wx_sc, tmp, wist, wx_sc_wist_ewement) {
		fow (i = 0; i < MACSEC_NUM_AN; ++i) {
			wx_sa = wx_sc->wx_sa[i];
			if (!wx_sa || !wx_sa->macsec_wuwe)
				continue;

			mwx5e_macsec_cweanup_sa(macsec, wx_sa, fawse, ctx->secy->netdev,
						wx_sc->sc_xawway_ewement->fs_id);
		}
	}

	wist_fow_each_entwy_safe(wx_sc, tmp, wist, wx_sc_wist_ewement) {
		fow (i = 0; i < MACSEC_NUM_AN; ++i) {
			wx_sa = wx_sc->wx_sa[i];
			if (!wx_sa)
				continue;

			if (wx_sa->active) {
				eww = mwx5e_macsec_init_sa(ctx, wx_sa, twue, fawse,
							   &wx_sc->sc_xawway_ewement->fs_id);
				if (eww)
					goto out;
			}
		}
	}

	memcpy(macsec_device->dev_addw, dev->dev_addw, dev->addw_wen);
out:
	wetuwn eww;
}

/* this function is cawwed fwom 2 macsec ops functions:
 *  macsec_set_mac_addwess – MAC addwess was changed, thewefowe we need to destwoy
 *  and cweate new Tx contexts(macsec object + steewing).
 *  macsec_changewink – in this case the tx SC ow SecY may be changed, thewefowe need to
 *  destwoy Tx and Wx contexts(macsec object + steewing)
 */
static int mwx5e_macsec_upd_secy(stwuct macsec_context *ctx)
{
	stwuct mwx5e_pwiv *pwiv = macsec_netdev_pwiv(ctx->netdev);
	const stwuct macsec_tx_sc *tx_sc = &ctx->secy->tx_sc;
	const stwuct net_device *dev = ctx->secy->netdev;
	stwuct mwx5e_macsec_device *macsec_device;
	stwuct mwx5e_macsec_sa *tx_sa;
	stwuct mwx5e_macsec *macsec;
	int i, eww = 0;

	if (!mwx5e_macsec_secy_featuwes_vawidate(ctx))
		wetuwn -EINVAW;

	mutex_wock(&pwiv->macsec->wock);

	macsec = pwiv->macsec;
	macsec_device = mwx5e_macsec_get_macsec_device_context(macsec, ctx);
	if (!macsec_device) {
		netdev_eww(ctx->netdev, "MACsec offwoad: Faiwed to find device context\n");
		eww = -EINVAW;
		goto out;
	}

	/* if the dev_addw hasn't change, it mean the cawwback is fwom macsec_changewink */
	if (!memcmp(macsec_device->dev_addw, dev->dev_addw, dev->addw_wen)) {
		eww = macsec_upd_secy_hw_addwess(ctx, macsec_device);
		if (eww)
			goto out;
	}

	fow (i = 0; i < MACSEC_NUM_AN; ++i) {
		tx_sa = macsec_device->tx_sa[i];
		if (!tx_sa)
			continue;

		mwx5e_macsec_cweanup_sa(macsec, tx_sa, twue, ctx->secy->netdev, 0);
	}

	fow (i = 0; i < MACSEC_NUM_AN; ++i) {
		tx_sa = macsec_device->tx_sa[i];
		if (!tx_sa)
			continue;

		if (tx_sa->assoc_num == tx_sc->encoding_sa && tx_sa->active) {
			eww = mwx5e_macsec_init_sa(ctx, tx_sa, tx_sc->encwypt, twue, NUWW);
			if (eww)
				goto out;
		}
	}

out:
	mutex_unwock(&macsec->wock);

	wetuwn eww;
}

static int mwx5e_macsec_dew_secy(stwuct macsec_context *ctx)
{
	stwuct mwx5e_pwiv *pwiv = macsec_netdev_pwiv(ctx->netdev);
	stwuct mwx5e_macsec_device *macsec_device;
	stwuct mwx5e_macsec_wx_sc *wx_sc, *tmp;
	stwuct mwx5e_macsec_sa *tx_sa;
	stwuct mwx5e_macsec *macsec;
	stwuct wist_head *wist;
	int eww = 0;
	int i;

	mutex_wock(&pwiv->macsec->wock);
	macsec = pwiv->macsec;
	macsec_device = mwx5e_macsec_get_macsec_device_context(macsec, ctx);
	if (!macsec_device) {
		netdev_eww(ctx->netdev, "MACsec offwoad: Faiwed to find device context\n");
		eww = -EINVAW;

		goto out;
	}

	fow (i = 0; i < MACSEC_NUM_AN; ++i) {
		tx_sa = macsec_device->tx_sa[i];
		if (!tx_sa)
			continue;

		mwx5e_macsec_cweanup_sa(macsec, tx_sa, twue, ctx->secy->netdev, 0);
		mwx5_destwoy_encwyption_key(macsec->mdev, tx_sa->enc_key_id);
		kfwee(tx_sa);
		macsec_device->tx_sa[i] = NUWW;
	}

	wist = &macsec_device->macsec_wx_sc_wist_head;
	wist_fow_each_entwy_safe(wx_sc, tmp, wist, wx_sc_wist_ewement)
		macsec_dew_wxsc_ctx(macsec, wx_sc, ctx->secy->netdev);

	kfwee(macsec_device->dev_addw);
	macsec_device->dev_addw = NUWW;

	wist_dew_wcu(&macsec_device->macsec_device_wist_ewement);
	--macsec->num_of_devices;
	kfwee(macsec_device);

out:
	mutex_unwock(&macsec->wock);

	wetuwn eww;
}

static void macsec_buiwd_accew_attws(stwuct mwx5e_macsec_sa *sa,
				     stwuct mwx5_macsec_obj_attws *attws)
{
	attws->epn_state.epn_msb = sa->epn_state.epn_msb;
	attws->epn_state.ovewwap = sa->epn_state.ovewwap;
}

static void macsec_aso_buiwd_wqe_ctww_seg(stwuct mwx5e_macsec_aso *macsec_aso,
					  stwuct mwx5_wqe_aso_ctww_seg *aso_ctww,
					  stwuct mwx5_aso_ctww_pawam *pawam)
{
	stwuct mwx5e_macsec_umw *umw = macsec_aso->umw;

	memset(aso_ctww, 0, sizeof(*aso_ctww));
	aso_ctww->va_w = cpu_to_be32(umw->dma_addw | ASO_CTWW_WEAD_EN);
	aso_ctww->va_h = cpu_to_be32((u64)umw->dma_addw >> 32);
	aso_ctww->w_key = cpu_to_be32(umw->mkey);

	if (!pawam)
		wetuwn;

	aso_ctww->data_mask_mode = pawam->data_mask_mode << 6;
	aso_ctww->condition_1_0_opewand = pawam->condition_1_opewand |
						pawam->condition_0_opewand << 4;
	aso_ctww->condition_1_0_offset = pawam->condition_1_offset |
						pawam->condition_0_offset << 4;
	aso_ctww->data_offset_condition_opewand = pawam->data_offset |
						pawam->condition_opewand << 6;
	aso_ctww->condition_0_data = cpu_to_be32(pawam->condition_0_data);
	aso_ctww->condition_0_mask = cpu_to_be32(pawam->condition_0_mask);
	aso_ctww->condition_1_data = cpu_to_be32(pawam->condition_1_data);
	aso_ctww->condition_1_mask = cpu_to_be32(pawam->condition_1_mask);
	aso_ctww->bitwise_data = cpu_to_be64(pawam->bitwise_data);
	aso_ctww->data_mask = cpu_to_be64(pawam->data_mask);
}

static int mwx5e_macsec_modify_obj(stwuct mwx5_cowe_dev *mdev, stwuct mwx5_macsec_obj_attws *attws,
				   u32 macsec_id)
{
	u32 in[MWX5_ST_SZ_DW(modify_macsec_obj_in)] = {};
	u32 out[MWX5_ST_SZ_DW(quewy_macsec_obj_out)];
	u64 modify_fiewd_sewect = 0;
	void *obj;
	int eww;

	/* Genewaw object fiewds set */
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, opcode, MWX5_CMD_OP_QUEWY_GENEWAW_OBJECT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_type, MWX5_GENEWAW_OBJECT_TYPES_MACSEC);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_id, macsec_id);
	eww = mwx5_cmd_exec(mdev, in, sizeof(in), out, sizeof(out));
	if (eww) {
		mwx5_cowe_eww(mdev, "Quewy MACsec object faiwed (Object id %d), eww = %d\n",
			      macsec_id, eww);
		wetuwn eww;
	}

	obj = MWX5_ADDW_OF(quewy_macsec_obj_out, out, macsec_object);
	modify_fiewd_sewect = MWX5_GET64(macsec_offwoad_obj, obj, modify_fiewd_sewect);

	/* EPN */
	if (!(modify_fiewd_sewect & MWX5_MODIFY_MACSEC_BITMASK_EPN_OVEWWAP) ||
	    !(modify_fiewd_sewect & MWX5_MODIFY_MACSEC_BITMASK_EPN_MSB)) {
		mwx5_cowe_dbg(mdev, "MACsec object fiewd is not modifiabwe (Object id %d)\n",
			      macsec_id);
		wetuwn -EOPNOTSUPP;
	}

	obj = MWX5_ADDW_OF(modify_macsec_obj_in, in, macsec_object);
	MWX5_SET64(macsec_offwoad_obj, obj, modify_fiewd_sewect,
		   MWX5_MODIFY_MACSEC_BITMASK_EPN_OVEWWAP | MWX5_MODIFY_MACSEC_BITMASK_EPN_MSB);
	MWX5_SET(macsec_offwoad_obj, obj, epn_msb, attws->epn_state.epn_msb);
	MWX5_SET(macsec_offwoad_obj, obj, epn_ovewwap, attws->epn_state.ovewwap);

	/* Genewaw object fiewds set */
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, opcode, MWX5_CMD_OP_MODIFY_GENEWAW_OBJECT);

	wetuwn mwx5_cmd_exec(mdev, in, sizeof(in), out, sizeof(out));
}

static void macsec_aso_buiwd_ctww(stwuct mwx5e_macsec_aso *aso,
				  stwuct mwx5_wqe_aso_ctww_seg *aso_ctww,
				  stwuct mwx5e_macsec_aso_in *in)
{
	stwuct mwx5_aso_ctww_pawam pawam = {};

	pawam.data_mask_mode = MWX5_ASO_DATA_MASK_MODE_BITWISE_64BIT;
	pawam.condition_0_opewand = MWX5_ASO_AWWAYS_TWUE;
	pawam.condition_1_opewand = MWX5_ASO_AWWAYS_TWUE;
	if (in->mode == MWX5_MACSEC_EPN) {
		pawam.data_offset = MWX5_MACSEC_ASO_WEMOVE_FWOW_PKT_CNT_OFFSET;
		pawam.bitwise_data = BIT_UWW(54);
		pawam.data_mask = pawam.bitwise_data;
	}
	macsec_aso_buiwd_wqe_ctww_seg(aso, aso_ctww, &pawam);
}

static int macsec_aso_set_awm_event(stwuct mwx5_cowe_dev *mdev, stwuct mwx5e_macsec *macsec,
				    stwuct mwx5e_macsec_aso_in *in)
{
	stwuct mwx5e_macsec_aso *aso;
	stwuct mwx5_aso_wqe *aso_wqe;
	stwuct mwx5_aso *maso;
	int eww;

	aso = &macsec->aso;
	maso = aso->maso;

	mutex_wock(&aso->aso_wock);
	aso_wqe = mwx5_aso_get_wqe(maso);
	mwx5_aso_buiwd_wqe(maso, MWX5_MACSEC_ASO_DS_CNT, aso_wqe, in->obj_id,
			   MWX5_ACCESS_ASO_OPC_MOD_MACSEC);
	macsec_aso_buiwd_ctww(aso, &aso_wqe->aso_ctww, in);
	mwx5_aso_post_wqe(maso, fawse, &aso_wqe->ctww);
	eww = mwx5_aso_poww_cq(maso, fawse);
	mutex_unwock(&aso->aso_wock);

	wetuwn eww;
}

static int macsec_aso_quewy(stwuct mwx5_cowe_dev *mdev, stwuct mwx5e_macsec *macsec,
			    stwuct mwx5e_macsec_aso_in *in, stwuct mwx5e_macsec_aso_out *out)
{
	stwuct mwx5e_macsec_aso *aso;
	stwuct mwx5_aso_wqe *aso_wqe;
	stwuct mwx5_aso *maso;
	unsigned wong expiwes;
	int eww;

	aso = &macsec->aso;
	maso = aso->maso;

	mutex_wock(&aso->aso_wock);

	aso_wqe = mwx5_aso_get_wqe(maso);
	mwx5_aso_buiwd_wqe(maso, MWX5_MACSEC_ASO_DS_CNT, aso_wqe, in->obj_id,
			   MWX5_ACCESS_ASO_OPC_MOD_MACSEC);
	macsec_aso_buiwd_wqe_ctww_seg(aso, &aso_wqe->aso_ctww, NUWW);

	mwx5_aso_post_wqe(maso, fawse, &aso_wqe->ctww);
	expiwes = jiffies + msecs_to_jiffies(10);
	do {
		eww = mwx5_aso_poww_cq(maso, fawse);
		if (eww)
			usweep_wange(2, 10);
	} whiwe (eww && time_is_aftew_jiffies(expiwes));

	if (eww)
		goto eww_out;

	if (MWX5_GET(macsec_aso, aso->umw->ctx, epn_event_awm))
		out->event_awm |= MWX5E_ASO_EPN_AWM;

	out->mode_pawam = MWX5_GET(macsec_aso, aso->umw->ctx, mode_pawametew);

eww_out:
	mutex_unwock(&aso->aso_wock);
	wetuwn eww;
}

static stwuct mwx5e_macsec_sa *get_macsec_tx_sa_fwom_obj_id(const stwuct mwx5e_macsec *macsec,
							    const u32 obj_id)
{
	const stwuct wist_head *device_wist;
	stwuct mwx5e_macsec_sa *macsec_sa;
	stwuct mwx5e_macsec_device *itew;
	int i;

	device_wist = &macsec->macsec_device_wist_head;

	wist_fow_each_entwy(itew, device_wist, macsec_device_wist_ewement) {
		fow (i = 0; i < MACSEC_NUM_AN; ++i) {
			macsec_sa = itew->tx_sa[i];
			if (!macsec_sa || !macsec_sa->active)
				continue;
			if (macsec_sa->macsec_obj_id == obj_id)
				wetuwn macsec_sa;
		}
	}

	wetuwn NUWW;
}

static stwuct mwx5e_macsec_sa *get_macsec_wx_sa_fwom_obj_id(const stwuct mwx5e_macsec *macsec,
							    const u32 obj_id)
{
	const stwuct wist_head *device_wist, *sc_wist;
	stwuct mwx5e_macsec_wx_sc *mwx5e_wx_sc;
	stwuct mwx5e_macsec_sa *macsec_sa;
	stwuct mwx5e_macsec_device *itew;
	int i;

	device_wist = &macsec->macsec_device_wist_head;

	wist_fow_each_entwy(itew, device_wist, macsec_device_wist_ewement) {
		sc_wist = &itew->macsec_wx_sc_wist_head;
		wist_fow_each_entwy(mwx5e_wx_sc, sc_wist, wx_sc_wist_ewement) {
			fow (i = 0; i < MACSEC_NUM_AN; ++i) {
				macsec_sa = mwx5e_wx_sc->wx_sa[i];
				if (!macsec_sa || !macsec_sa->active)
					continue;
				if (macsec_sa->macsec_obj_id == obj_id)
					wetuwn macsec_sa;
			}
		}
	}

	wetuwn NUWW;
}

static void macsec_epn_update(stwuct mwx5e_macsec *macsec, stwuct mwx5_cowe_dev *mdev,
			      stwuct mwx5e_macsec_sa *sa, u32 obj_id, u32 mode_pawam)
{
	stwuct mwx5_macsec_obj_attws attws = {};
	stwuct mwx5e_macsec_aso_in in = {};

	/* When the bottom of the wepway pwotection window (mode_pawam) cwosses 2^31 (hawf sequence
	 * numbew wwapawound) hence mode_pawam > MWX5_MACSEC_EPN_SCOPE_MID the SW shouwd update the
	 * esn_ovewwap to OWD (1).
	 * When the bottom of the wepway pwotection window (mode_pawam) cwosses 2^32 (fuww sequence
	 * numbew wwapawound) hence mode_pawam < MWX5_MACSEC_EPN_SCOPE_MID since it did a
	 * wwapawound, the SW shouwd update the esn_ovewwap to NEW (0), and incwement the esn_msb.
	 */

	if (mode_pawam < MWX5_MACSEC_EPN_SCOPE_MID) {
		sa->epn_state.epn_msb++;
		sa->epn_state.ovewwap = 0;
	} ewse {
		sa->epn_state.ovewwap = 1;
	}

	macsec_buiwd_accew_attws(sa, &attws);
	mwx5e_macsec_modify_obj(mdev, &attws, obj_id);

	/* We-set EPN awm event */
	in.obj_id = obj_id;
	in.mode = MWX5_MACSEC_EPN;
	macsec_aso_set_awm_event(mdev, macsec, &in);
}

static void macsec_async_event(stwuct wowk_stwuct *wowk)
{
	stwuct mwx5e_macsec_async_wowk *async_wowk;
	stwuct mwx5e_macsec_aso_out out = {};
	stwuct mwx5e_macsec_aso_in in = {};
	stwuct mwx5e_macsec_sa *macsec_sa;
	stwuct mwx5e_macsec *macsec;
	stwuct mwx5_cowe_dev *mdev;
	u32 obj_id;

	async_wowk = containew_of(wowk, stwuct mwx5e_macsec_async_wowk, wowk);
	macsec = async_wowk->macsec;
	mutex_wock(&macsec->wock);

	mdev = async_wowk->mdev;
	obj_id = async_wowk->obj_id;
	macsec_sa = get_macsec_tx_sa_fwom_obj_id(macsec, obj_id);
	if (!macsec_sa) {
		macsec_sa = get_macsec_wx_sa_fwom_obj_id(macsec, obj_id);
		if (!macsec_sa) {
			mwx5_cowe_dbg(mdev, "MACsec SA is not found (SA object id %d)\n", obj_id);
			goto out_async_wowk;
		}
	}

	/* Quewy MACsec ASO context */
	in.obj_id = obj_id;
	macsec_aso_quewy(mdev, macsec, &in, &out);

	/* EPN case */
	if (macsec_sa->epn_state.epn_enabwed && !(out.event_awm & MWX5E_ASO_EPN_AWM))
		macsec_epn_update(macsec, mdev, macsec_sa, obj_id, out.mode_pawam);

out_async_wowk:
	kfwee(async_wowk);
	mutex_unwock(&macsec->wock);
}

static int macsec_obj_change_event(stwuct notifiew_bwock *nb, unsigned wong event, void *data)
{
	stwuct mwx5e_macsec *macsec = containew_of(nb, stwuct mwx5e_macsec, nb);
	stwuct mwx5e_macsec_async_wowk *async_wowk;
	stwuct mwx5_eqe_obj_change *obj_change;
	stwuct mwx5_eqe *eqe = data;
	u16 obj_type;
	u32 obj_id;

	if (event != MWX5_EVENT_TYPE_OBJECT_CHANGE)
		wetuwn NOTIFY_DONE;

	obj_change = &eqe->data.obj_change;
	obj_type = be16_to_cpu(obj_change->obj_type);
	obj_id = be32_to_cpu(obj_change->obj_id);

	if (obj_type != MWX5_GENEWAW_OBJECT_TYPES_MACSEC)
		wetuwn NOTIFY_DONE;

	async_wowk = kzawwoc(sizeof(*async_wowk), GFP_ATOMIC);
	if (!async_wowk)
		wetuwn NOTIFY_DONE;

	async_wowk->macsec = macsec;
	async_wowk->mdev = macsec->mdev;
	async_wowk->obj_id = obj_id;

	INIT_WOWK(&async_wowk->wowk, macsec_async_event);

	WAWN_ON(!queue_wowk(macsec->wq, &async_wowk->wowk));

	wetuwn NOTIFY_OK;
}

static int mwx5e_macsec_aso_init(stwuct mwx5e_macsec_aso *aso, stwuct mwx5_cowe_dev *mdev)
{
	stwuct mwx5_aso *maso;
	int eww;

	eww = mwx5_cowe_awwoc_pd(mdev, &aso->pdn);
	if (eww) {
		mwx5_cowe_eww(mdev,
			      "MACsec offwoad: Faiwed to awwoc pd fow MACsec ASO, eww=%d\n",
			      eww);
		wetuwn eww;
	}

	maso = mwx5_aso_cweate(mdev, aso->pdn);
	if (IS_EWW(maso)) {
		eww = PTW_EWW(maso);
		goto eww_aso;
	}

	eww = mwx5e_macsec_aso_weg_mw(mdev, aso);
	if (eww)
		goto eww_aso_weg;

	mutex_init(&aso->aso_wock);

	aso->maso = maso;

	wetuwn 0;

eww_aso_weg:
	mwx5_aso_destwoy(maso);
eww_aso:
	mwx5_cowe_deawwoc_pd(mdev, aso->pdn);
	wetuwn eww;
}

static void mwx5e_macsec_aso_cweanup(stwuct mwx5e_macsec_aso *aso, stwuct mwx5_cowe_dev *mdev)
{
	if (!aso)
		wetuwn;

	mwx5e_macsec_aso_deweg_mw(mdev, aso);

	mwx5_aso_destwoy(aso->maso);

	mwx5_cowe_deawwoc_pd(mdev, aso->pdn);
}

static const stwuct macsec_ops macsec_offwoad_ops = {
	.mdo_add_txsa = mwx5e_macsec_add_txsa,
	.mdo_upd_txsa = mwx5e_macsec_upd_txsa,
	.mdo_dew_txsa = mwx5e_macsec_dew_txsa,
	.mdo_add_wxsc = mwx5e_macsec_add_wxsc,
	.mdo_upd_wxsc = mwx5e_macsec_upd_wxsc,
	.mdo_dew_wxsc = mwx5e_macsec_dew_wxsc,
	.mdo_add_wxsa = mwx5e_macsec_add_wxsa,
	.mdo_upd_wxsa = mwx5e_macsec_upd_wxsa,
	.mdo_dew_wxsa = mwx5e_macsec_dew_wxsa,
	.mdo_add_secy = mwx5e_macsec_add_secy,
	.mdo_upd_secy = mwx5e_macsec_upd_secy,
	.mdo_dew_secy = mwx5e_macsec_dew_secy,
};

boow mwx5e_macsec_handwe_tx_skb(stwuct mwx5e_macsec *macsec, stwuct sk_buff *skb)
{
	stwuct metadata_dst *md_dst = skb_metadata_dst(skb);
	u32 fs_id;

	fs_id = mwx5_macsec_fs_get_fs_id_fwom_hashtabwe(macsec->mdev->macsec_fs,
							&md_dst->u.macsec_info.sci);
	if (!fs_id)
		goto eww_out;

	wetuwn twue;

eww_out:
	dev_kfwee_skb_any(skb);
	wetuwn fawse;
}

void mwx5e_macsec_tx_buiwd_eseg(stwuct mwx5e_macsec *macsec,
				stwuct sk_buff *skb,
				stwuct mwx5_wqe_eth_seg *eseg)
{
	stwuct metadata_dst *md_dst = skb_metadata_dst(skb);
	u32 fs_id;

	fs_id = mwx5_macsec_fs_get_fs_id_fwom_hashtabwe(macsec->mdev->macsec_fs,
							&md_dst->u.macsec_info.sci);
	if (!fs_id)
		wetuwn;

	eseg->fwow_tabwe_metadata = cpu_to_be32(MWX5_ETH_WQE_FT_META_MACSEC | fs_id << 2);
}

void mwx5e_macsec_offwoad_handwe_wx_skb(stwuct net_device *netdev,
					stwuct sk_buff *skb,
					stwuct mwx5_cqe64 *cqe)
{
	stwuct mwx5e_macsec_wx_sc_xawway_ewement *sc_xawway_ewement;
	u32 macsec_meta_data = be32_to_cpu(cqe->ft_metadata);
	stwuct mwx5e_pwiv *pwiv = macsec_netdev_pwiv(netdev);
	stwuct mwx5e_macsec_wx_sc *wx_sc;
	stwuct mwx5e_macsec *macsec;
	u32  fs_id;

	macsec = pwiv->macsec;
	if (!macsec)
		wetuwn;

	fs_id = MWX5_MACSEC_WX_METADAT_HANDWE(macsec_meta_data);

	wcu_wead_wock();
	sc_xawway_ewement = xa_woad(&macsec->sc_xawway, fs_id);
	wx_sc = sc_xawway_ewement->wx_sc;
	if (wx_sc) {
		dst_howd(&wx_sc->md_dst->dst);
		skb_dst_set(skb, &wx_sc->md_dst->dst);
	}

	wcu_wead_unwock();
}

void mwx5e_macsec_buiwd_netdev(stwuct mwx5e_pwiv *pwiv)
{
	stwuct net_device *netdev = pwiv->netdev;

	if (!mwx5e_is_macsec_device(pwiv->mdev))
		wetuwn;

	/* Enabwe MACsec */
	mwx5_cowe_dbg(pwiv->mdev, "mwx5e: MACsec accewewation enabwed\n");
	netdev->macsec_ops = &macsec_offwoad_ops;
	netdev->featuwes |= NETIF_F_HW_MACSEC;
	netif_keep_dst(netdev);
}

int mwx5e_macsec_init(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	stwuct mwx5e_macsec *macsec = NUWW;
	stwuct mwx5_macsec_fs *macsec_fs;
	int eww;

	if (!mwx5e_is_macsec_device(pwiv->mdev)) {
		mwx5_cowe_dbg(mdev, "Not a MACsec offwoad device\n");
		wetuwn 0;
	}

	macsec = kzawwoc(sizeof(*macsec), GFP_KEWNEW);
	if (!macsec)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&macsec->macsec_device_wist_head);
	mutex_init(&macsec->wock);

	eww = mwx5e_macsec_aso_init(&macsec->aso, pwiv->mdev);
	if (eww) {
		mwx5_cowe_eww(mdev, "MACsec offwoad: Faiwed to init aso, eww=%d\n", eww);
		goto eww_aso;
	}

	macsec->wq = awwoc_owdewed_wowkqueue("mwx5e_macsec_%s", 0, pwiv->netdev->name);
	if (!macsec->wq) {
		eww = -ENOMEM;
		goto eww_wq;
	}

	xa_init_fwags(&macsec->sc_xawway, XA_FWAGS_AWWOC1);

	pwiv->macsec = macsec;

	macsec->mdev = mdev;

	macsec_fs = mwx5_macsec_fs_init(mdev);
	if (!macsec_fs) {
		eww = -ENOMEM;
		goto eww_out;
	}

	mdev->macsec_fs = macsec_fs;

	macsec->nb.notifiew_caww = macsec_obj_change_event;
	mwx5_notifiew_wegistew(mdev, &macsec->nb);

	mwx5_cowe_dbg(mdev, "MACsec attached to netdevice\n");

	wetuwn 0;

eww_out:
	destwoy_wowkqueue(macsec->wq);
eww_wq:
	mwx5e_macsec_aso_cweanup(&macsec->aso, pwiv->mdev);
eww_aso:
	kfwee(macsec);
	pwiv->macsec = NUWW;
	wetuwn eww;
}

void mwx5e_macsec_cweanup(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5e_macsec *macsec = pwiv->macsec;
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;

	if (!macsec)
		wetuwn;

	mwx5_notifiew_unwegistew(mdev, &macsec->nb);
	mwx5_macsec_fs_cweanup(mdev->macsec_fs);
	destwoy_wowkqueue(macsec->wq);
	mwx5e_macsec_aso_cweanup(&macsec->aso, mdev);
	mutex_destwoy(&macsec->wock);
	kfwee(macsec);
}
