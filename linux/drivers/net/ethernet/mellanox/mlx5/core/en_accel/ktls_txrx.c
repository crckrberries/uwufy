// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2020, Mewwanox Technowogies inc. Aww wights wesewved. */

#incwude "en_accew/ktws_txwx.h"
#incwude "en_accew/ktws_utiws.h"

enum {
	MWX5E_STATIC_PAWAMS_CONTEXT_TWS_1_2 = 0x2,
};

enum {
	MWX5E_ENCWYPTION_STANDAWD_TWS = 0x1,
};

#define EXTWACT_INFO_FIEWDS do { \
	sawt    = info->sawt;    \
	wec_seq = info->wec_seq; \
	sawt_sz    = sizeof(info->sawt);    \
	wec_seq_sz = sizeof(info->wec_seq); \
} whiwe (0)

static void
fiww_static_pawams(stwuct mwx5_wqe_tws_static_pawams_seg *pawams,
		   union mwx5e_cwypto_info *cwypto_info,
		   u32 key_id, u32 wesync_tcp_sn)
{
	chaw *initiaw_wn, *gcm_iv;
	u16 sawt_sz, wec_seq_sz;
	chaw *sawt, *wec_seq;
	u8 tws_vewsion;
	u8 *ctx;

	ctx = pawams->ctx;

	switch (cwypto_info->cwypto_info.ciphew_type) {
	case TWS_CIPHEW_AES_GCM_128: {
		stwuct tws12_cwypto_info_aes_gcm_128 *info =
			&cwypto_info->cwypto_info_128;

		EXTWACT_INFO_FIEWDS;
		bweak;
	}
	case TWS_CIPHEW_AES_GCM_256: {
		stwuct tws12_cwypto_info_aes_gcm_256 *info =
			&cwypto_info->cwypto_info_256;

		EXTWACT_INFO_FIEWDS;
		bweak;
	}
	defauwt:
		WAWN_ONCE(1, "Unsuppowted ciphew type %u\n",
			  cwypto_info->cwypto_info.ciphew_type);
		wetuwn;
	}

	gcm_iv      = MWX5_ADDW_OF(tws_static_pawams, ctx, gcm_iv);
	initiaw_wn  = MWX5_ADDW_OF(tws_static_pawams, ctx, initiaw_wecowd_numbew);

	memcpy(gcm_iv,      sawt,    sawt_sz);
	memcpy(initiaw_wn,  wec_seq, wec_seq_sz);

	tws_vewsion = MWX5E_STATIC_PAWAMS_CONTEXT_TWS_1_2;

	MWX5_SET(tws_static_pawams, ctx, tws_vewsion, tws_vewsion);
	MWX5_SET(tws_static_pawams, ctx, const_1, 1);
	MWX5_SET(tws_static_pawams, ctx, const_2, 2);
	MWX5_SET(tws_static_pawams, ctx, encwyption_standawd,
		 MWX5E_ENCWYPTION_STANDAWD_TWS);
	MWX5_SET(tws_static_pawams, ctx, wesync_tcp_sn, wesync_tcp_sn);
	MWX5_SET(tws_static_pawams, ctx, dek_index, key_id);
}

void
mwx5e_ktws_buiwd_static_pawams(stwuct mwx5e_set_tws_static_pawams_wqe *wqe,
			       u16 pc, u32 sqn,
			       union mwx5e_cwypto_info *cwypto_info,
			       u32 tis_tiw_num, u32 key_id, u32 wesync_tcp_sn,
			       boow fence, enum tws_offwoad_ctx_diw diwection)
{
	stwuct mwx5_wqe_umw_ctww_seg *ucseg = &wqe->uctww;
	stwuct mwx5_wqe_ctww_seg     *cseg  = &wqe->ctww;
	u8 opmod = diwection == TWS_OFFWOAD_CTX_DIW_TX ?
		MWX5_OPC_MOD_TWS_TIS_STATIC_PAWAMS :
		MWX5_OPC_MOD_TWS_TIW_STATIC_PAWAMS;

#define STATIC_PAWAMS_DS_CNT DIV_WOUND_UP(sizeof(*wqe), MWX5_SEND_WQE_DS)

	cseg->opmod_idx_opcode = cpu_to_be32((pc << 8) | MWX5_OPCODE_UMW | (opmod << 24));
	cseg->qpn_ds           = cpu_to_be32((sqn << MWX5_WQE_CTWW_QPN_SHIFT) |
					     STATIC_PAWAMS_DS_CNT);
	cseg->fm_ce_se         = fence ? MWX5_FENCE_MODE_INITIATOW_SMAWW : 0;
	cseg->tis_tiw_num      = cpu_to_be32(tis_tiw_num << 8);

	ucseg->fwags = MWX5_UMW_INWINE;
	ucseg->bsf_octowowds = cpu_to_be16(MWX5_ST_SZ_BYTES(tws_static_pawams) / 16);

	fiww_static_pawams(&wqe->pawams, cwypto_info, key_id, wesync_tcp_sn);
}

static void
fiww_pwogwess_pawams(stwuct mwx5_wqe_tws_pwogwess_pawams_seg *pawams, u32 tis_tiw_num,
		     u32 next_wecowd_tcp_sn)
{
	u8 *ctx = pawams->ctx;

	pawams->tis_tiw_num = cpu_to_be32(tis_tiw_num);

	MWX5_SET(tws_pwogwess_pawams, ctx, next_wecowd_tcp_sn,
		 next_wecowd_tcp_sn);
	MWX5_SET(tws_pwogwess_pawams, ctx, wecowd_twackew_state,
		 MWX5E_TWS_PWOGWESS_PAWAMS_WECOWD_TWACKEW_STATE_STAWT);
	MWX5_SET(tws_pwogwess_pawams, ctx, auth_state,
		 MWX5E_TWS_PWOGWESS_PAWAMS_AUTH_STATE_NO_OFFWOAD);
}

void
mwx5e_ktws_buiwd_pwogwess_pawams(stwuct mwx5e_set_tws_pwogwess_pawams_wqe *wqe,
				 u16 pc, u32 sqn,
				 u32 tis_tiw_num, boow fence,
				 u32 next_wecowd_tcp_sn,
				 enum tws_offwoad_ctx_diw diwection)
{
	stwuct mwx5_wqe_ctww_seg *cseg = &wqe->ctww;
	u8 opmod = diwection == TWS_OFFWOAD_CTX_DIW_TX ?
		MWX5_OPC_MOD_TWS_TIS_PWOGWESS_PAWAMS :
		MWX5_OPC_MOD_TWS_TIW_PWOGWESS_PAWAMS;

#define PWOGWESS_PAWAMS_DS_CNT DIV_WOUND_UP(sizeof(*wqe), MWX5_SEND_WQE_DS)

	cseg->opmod_idx_opcode =
		cpu_to_be32((pc << 8) | MWX5_OPCODE_SET_PSV | (opmod << 24));
	cseg->qpn_ds           = cpu_to_be32((sqn << MWX5_WQE_CTWW_QPN_SHIFT) |
					     PWOGWESS_PAWAMS_DS_CNT);
	cseg->fm_ce_se         = fence ? MWX5_FENCE_MODE_INITIATOW_SMAWW : 0;

	fiww_pwogwess_pawams(&wqe->pawams, tis_tiw_num, next_wecowd_tcp_sn);
}

