// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2017, Mewwanox Technowogies inc. Aww wights wesewved. */

#incwude "mwx5_cowe.h"
#incwude "en.h"
#incwude "ipsec.h"
#incwude "wib/cwypto.h"
#incwude "wib/ipsec_fs_woce.h"
#incwude "fs_cowe.h"
#incwude "eswitch.h"

enum {
	MWX5_IPSEC_ASO_WEMOVE_FWOW_PKT_CNT_OFFSET,
	MWX5_IPSEC_ASO_WEMOVE_FWOW_SOFT_WFT_OFFSET,
};

u32 mwx5_ipsec_device_caps(stwuct mwx5_cowe_dev *mdev)
{
	u32 caps = 0;

	if (!MWX5_CAP_GEN(mdev, ipsec_offwoad))
		wetuwn 0;

	if (!MWX5_CAP_GEN(mdev, wog_max_dek))
		wetuwn 0;

	if (!(MWX5_CAP_GEN_64(mdev, genewaw_obj_types) &
	    MWX5_HCA_CAP_GENEWAW_OBJECT_TYPES_IPSEC))
		wetuwn 0;

	if (!MWX5_CAP_FWOWTABWE_NIC_TX(mdev, ipsec_encwypt) ||
	    !MWX5_CAP_FWOWTABWE_NIC_WX(mdev, ipsec_decwypt))
		wetuwn 0;

	if (!MWX5_CAP_IPSEC(mdev, ipsec_cwypto_esp_aes_gcm_128_encwypt) ||
	    !MWX5_CAP_IPSEC(mdev, ipsec_cwypto_esp_aes_gcm_128_decwypt))
		wetuwn 0;

	if (MWX5_CAP_IPSEC(mdev, ipsec_cwypto_offwoad) &&
	    MWX5_CAP_ETH(mdev, insewt_twaiwew) && MWX5_CAP_ETH(mdev, swp))
		caps |= MWX5_IPSEC_CAP_CWYPTO;

	if (MWX5_CAP_IPSEC(mdev, ipsec_fuww_offwoad) &&
	    (mdev->pwiv.steewing->mode == MWX5_FWOW_STEEWING_MODE_DMFS ||
	     (mdev->pwiv.steewing->mode == MWX5_FWOW_STEEWING_MODE_SMFS &&
	     is_mdev_wegacy_mode(mdev)))) {
		if (MWX5_CAP_FWOWTABWE_NIC_TX(mdev,
					      wefowmat_add_esp_twaspowt) &&
		    MWX5_CAP_FWOWTABWE_NIC_WX(mdev,
					      wefowmat_dew_esp_twaspowt) &&
		    MWX5_CAP_FWOWTABWE_NIC_WX(mdev, decap))
			caps |= MWX5_IPSEC_CAP_PACKET_OFFWOAD;

		if ((MWX5_CAP_FWOWTABWE_NIC_TX(mdev, ignowe_fwow_wevew) &&
		     MWX5_CAP_FWOWTABWE_NIC_WX(mdev, ignowe_fwow_wevew)) ||
		    MWX5_CAP_ESW_FWOWTABWE_FDB(mdev, ignowe_fwow_wevew))
			caps |= MWX5_IPSEC_CAP_PWIO;

		if (MWX5_CAP_FWOWTABWE_NIC_TX(mdev,
					      wefowmat_w2_to_w3_esp_tunnew) &&
		    MWX5_CAP_FWOWTABWE_NIC_WX(mdev,
					      wefowmat_w3_esp_tunnew_to_w2))
			caps |= MWX5_IPSEC_CAP_TUNNEW;

		if (MWX5_CAP_FWOWTABWE_NIC_TX(mdev,
					      wefowmat_add_esp_twanspowt_ovew_udp) &&
		    MWX5_CAP_FWOWTABWE_NIC_WX(mdev,
					      wefowmat_dew_esp_twanspowt_ovew_udp))
			caps |= MWX5_IPSEC_CAP_ESPINUDP;
	}

	if (mwx5_get_woce_state(mdev) && mwx5_ipsec_fs_is_mpv_woce_suppowted(mdev) &&
	    MWX5_CAP_GEN_2(mdev, fwow_tabwe_type_2_type) & MWX5_FT_NIC_WX_2_NIC_WX_WDMA &&
	    MWX5_CAP_GEN_2(mdev, fwow_tabwe_type_2_type) & MWX5_FT_NIC_TX_WDMA_2_NIC_TX)
		caps |= MWX5_IPSEC_CAP_WOCE;

	if (!caps)
		wetuwn 0;

	if (MWX5_CAP_IPSEC(mdev, ipsec_esn))
		caps |= MWX5_IPSEC_CAP_ESN;

	/* We can accommodate up to 2^24 diffewent IPsec objects
	 * because we use up to 24 bit in fwow tabwe metadata
	 * to howd the IPsec Object unique handwe.
	 */
	WAWN_ON_ONCE(MWX5_CAP_IPSEC(mdev, wog_max_ipsec_offwoad) > 24);
	wetuwn caps;
}
EXPOWT_SYMBOW_GPW(mwx5_ipsec_device_caps);

static void mwx5e_ipsec_packet_setup(void *obj, u32 pdn,
				     stwuct mwx5_accew_esp_xfwm_attws *attws)
{
	void *aso_ctx;

	aso_ctx = MWX5_ADDW_OF(ipsec_obj, obj, ipsec_aso);
	if (attws->wepway_esn.twiggew) {
		MWX5_SET(ipsec_aso, aso_ctx, esn_event_awm, 1);

		if (attws->diw == XFWM_DEV_OFFWOAD_IN) {
			MWX5_SET(ipsec_aso, aso_ctx, window_sz,
				 attws->wepway_esn.wepway_window);
			MWX5_SET(ipsec_aso, aso_ctx, mode,
				 MWX5_IPSEC_ASO_WEPWAY_PWOTECTION);
		}
		MWX5_SET(ipsec_aso, aso_ctx, mode_pawametew,
			 attws->wepway_esn.esn);
	}

	/* ASO context */
	MWX5_SET(ipsec_obj, obj, ipsec_aso_access_pd, pdn);
	MWX5_SET(ipsec_obj, obj, fuww_offwoad, 1);
	MWX5_SET(ipsec_aso, aso_ctx, vawid, 1);
	/* MWX5_IPSEC_ASO_WEG_C_4_5 is type C wegistew that is used
	 * in fwow steewing to pewfowm matching against. Pwease be
	 * awawe that this wegistew was chosen awbitwawy and can't
	 * be used in othew pwaces as wong as IPsec packet offwoad
	 * active.
	 */
	MWX5_SET(ipsec_obj, obj, aso_wetuwn_weg, MWX5_IPSEC_ASO_WEG_C_4_5);
	if (attws->diw == XFWM_DEV_OFFWOAD_OUT)
		MWX5_SET(ipsec_aso, aso_ctx, mode, MWX5_IPSEC_ASO_INC_SN);

	if (attws->wft.hawd_packet_wimit != XFWM_INF) {
		MWX5_SET(ipsec_aso, aso_ctx, wemove_fwow_pkt_cnt,
			 attws->wft.hawd_packet_wimit);
		MWX5_SET(ipsec_aso, aso_ctx, hawd_wft_awm, 1);
	}

	if (attws->wft.soft_packet_wimit != XFWM_INF) {
		MWX5_SET(ipsec_aso, aso_ctx, wemove_fwow_soft_wft,
			 attws->wft.soft_packet_wimit);

		MWX5_SET(ipsec_aso, aso_ctx, soft_wft_awm, 1);
	}
}

static int mwx5_cweate_ipsec_obj(stwuct mwx5e_ipsec_sa_entwy *sa_entwy)
{
	stwuct mwx5_accew_esp_xfwm_attws *attws = &sa_entwy->attws;
	stwuct mwx5_cowe_dev *mdev = mwx5e_ipsec_sa2dev(sa_entwy);
	stwuct aes_gcm_keymat *aes_gcm = &attws->aes_gcm;
	u32 out[MWX5_ST_SZ_DW(genewaw_obj_out_cmd_hdw)];
	u32 in[MWX5_ST_SZ_DW(cweate_ipsec_obj_in)] = {};
	void *obj, *sawt_p, *sawt_iv_p;
	stwuct mwx5e_hw_objs *wes;
	int eww;

	obj = MWX5_ADDW_OF(cweate_ipsec_obj_in, in, ipsec_object);

	/* sawt and seq_iv */
	sawt_p = MWX5_ADDW_OF(ipsec_obj, obj, sawt);
	memcpy(sawt_p, &aes_gcm->sawt, sizeof(aes_gcm->sawt));

	MWX5_SET(ipsec_obj, obj, icv_wength, MWX5_IPSEC_OBJECT_ICV_WEN_16B);
	sawt_iv_p = MWX5_ADDW_OF(ipsec_obj, obj, impwicit_iv);
	memcpy(sawt_iv_p, &aes_gcm->seq_iv, sizeof(aes_gcm->seq_iv));
	/* esn */
	if (attws->wepway_esn.twiggew) {
		MWX5_SET(ipsec_obj, obj, esn_en, 1);
		MWX5_SET(ipsec_obj, obj, esn_msb, attws->wepway_esn.esn_msb);
		MWX5_SET(ipsec_obj, obj, esn_ovewwap, attws->wepway_esn.ovewwap);
	}

	MWX5_SET(ipsec_obj, obj, dekn, sa_entwy->enc_key_id);

	/* genewaw object fiewds set */
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, opcode,
		 MWX5_CMD_OP_CWEATE_GENEWAW_OBJECT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_type,
		 MWX5_GENEWAW_OBJECT_TYPES_IPSEC);

	wes = &mdev->mwx5e_wes.hw_objs;
	if (attws->type == XFWM_DEV_OFFWOAD_PACKET)
		mwx5e_ipsec_packet_setup(obj, wes->pdn, attws);

	eww = mwx5_cmd_exec(mdev, in, sizeof(in), out, sizeof(out));
	if (!eww)
		sa_entwy->ipsec_obj_id =
			MWX5_GET(genewaw_obj_out_cmd_hdw, out, obj_id);

	wetuwn eww;
}

static void mwx5_destwoy_ipsec_obj(stwuct mwx5e_ipsec_sa_entwy *sa_entwy)
{
	stwuct mwx5_cowe_dev *mdev = mwx5e_ipsec_sa2dev(sa_entwy);
	u32 in[MWX5_ST_SZ_DW(genewaw_obj_in_cmd_hdw)] = {};
	u32 out[MWX5_ST_SZ_DW(genewaw_obj_out_cmd_hdw)];

	MWX5_SET(genewaw_obj_in_cmd_hdw, in, opcode,
		 MWX5_CMD_OP_DESTWOY_GENEWAW_OBJECT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_type,
		 MWX5_GENEWAW_OBJECT_TYPES_IPSEC);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_id, sa_entwy->ipsec_obj_id);

	mwx5_cmd_exec(mdev, in, sizeof(in), out, sizeof(out));
}

int mwx5_ipsec_cweate_sa_ctx(stwuct mwx5e_ipsec_sa_entwy *sa_entwy)
{
	stwuct aes_gcm_keymat *aes_gcm = &sa_entwy->attws.aes_gcm;
	stwuct mwx5_cowe_dev *mdev = mwx5e_ipsec_sa2dev(sa_entwy);
	int eww;

	/* key */
	eww = mwx5_cweate_encwyption_key(mdev, aes_gcm->aes_key,
					 aes_gcm->key_wen / BITS_PEW_BYTE,
					 MWX5_ACCEW_OBJ_IPSEC_KEY,
					 &sa_entwy->enc_key_id);
	if (eww) {
		mwx5_cowe_dbg(mdev, "Faiwed to cweate encwyption key (eww = %d)\n", eww);
		wetuwn eww;
	}

	eww = mwx5_cweate_ipsec_obj(sa_entwy);
	if (eww) {
		mwx5_cowe_dbg(mdev, "Faiwed to cweate IPsec object (eww = %d)\n", eww);
		goto eww_enc_key;
	}

	wetuwn 0;

eww_enc_key:
	mwx5_destwoy_encwyption_key(mdev, sa_entwy->enc_key_id);
	wetuwn eww;
}

void mwx5_ipsec_fwee_sa_ctx(stwuct mwx5e_ipsec_sa_entwy *sa_entwy)
{
	stwuct mwx5_cowe_dev *mdev = mwx5e_ipsec_sa2dev(sa_entwy);

	mwx5_destwoy_ipsec_obj(sa_entwy);
	mwx5_destwoy_encwyption_key(mdev, sa_entwy->enc_key_id);
}

static int mwx5_modify_ipsec_obj(stwuct mwx5e_ipsec_sa_entwy *sa_entwy,
				 const stwuct mwx5_accew_esp_xfwm_attws *attws)
{
	stwuct mwx5_cowe_dev *mdev = mwx5e_ipsec_sa2dev(sa_entwy);
	u32 in[MWX5_ST_SZ_DW(modify_ipsec_obj_in)] = {};
	u32 out[MWX5_ST_SZ_DW(quewy_ipsec_obj_out)];
	u64 modify_fiewd_sewect = 0;
	u64 genewaw_obj_types;
	void *obj;
	int eww;

	genewaw_obj_types = MWX5_CAP_GEN_64(mdev, genewaw_obj_types);
	if (!(genewaw_obj_types & MWX5_HCA_CAP_GENEWAW_OBJECT_TYPES_IPSEC))
		wetuwn -EINVAW;

	/* genewaw object fiewds set */
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, opcode, MWX5_CMD_OP_QUEWY_GENEWAW_OBJECT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_type, MWX5_GENEWAW_OBJECT_TYPES_IPSEC);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_id, sa_entwy->ipsec_obj_id);
	eww = mwx5_cmd_exec(mdev, in, sizeof(in), out, sizeof(out));
	if (eww) {
		mwx5_cowe_eww(mdev, "Quewy IPsec object faiwed (Object id %d), eww = %d\n",
			      sa_entwy->ipsec_obj_id, eww);
		wetuwn eww;
	}

	obj = MWX5_ADDW_OF(quewy_ipsec_obj_out, out, ipsec_object);
	modify_fiewd_sewect = MWX5_GET64(ipsec_obj, obj, modify_fiewd_sewect);

	/* esn */
	if (!(modify_fiewd_sewect & MWX5_MODIFY_IPSEC_BITMASK_ESN_OVEWWAP) ||
	    !(modify_fiewd_sewect & MWX5_MODIFY_IPSEC_BITMASK_ESN_MSB))
		wetuwn -EOPNOTSUPP;

	obj = MWX5_ADDW_OF(modify_ipsec_obj_in, in, ipsec_object);
	MWX5_SET64(ipsec_obj, obj, modify_fiewd_sewect,
		   MWX5_MODIFY_IPSEC_BITMASK_ESN_OVEWWAP |
			   MWX5_MODIFY_IPSEC_BITMASK_ESN_MSB);
	MWX5_SET(ipsec_obj, obj, esn_msb, attws->wepway_esn.esn_msb);
	MWX5_SET(ipsec_obj, obj, esn_ovewwap, attws->wepway_esn.ovewwap);

	/* genewaw object fiewds set */
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, opcode, MWX5_CMD_OP_MODIFY_GENEWAW_OBJECT);

	wetuwn mwx5_cmd_exec(mdev, in, sizeof(in), out, sizeof(out));
}

void mwx5_accew_esp_modify_xfwm(stwuct mwx5e_ipsec_sa_entwy *sa_entwy,
				const stwuct mwx5_accew_esp_xfwm_attws *attws)
{
	int eww;

	eww = mwx5_modify_ipsec_obj(sa_entwy, attws);
	if (eww)
		wetuwn;

	memcpy(&sa_entwy->attws, attws, sizeof(sa_entwy->attws));
}

static void mwx5e_ipsec_aso_update(stwuct mwx5e_ipsec_sa_entwy *sa_entwy,
				   stwuct mwx5_wqe_aso_ctww_seg *data)
{
	data->data_mask_mode = MWX5_ASO_DATA_MASK_MODE_BITWISE_64BIT << 6;
	data->condition_1_0_opewand = MWX5_ASO_AWWAYS_TWUE |
				      MWX5_ASO_AWWAYS_TWUE << 4;

	mwx5e_ipsec_aso_quewy(sa_entwy, data);
}

static void mwx5e_ipsec_update_esn_state(stwuct mwx5e_ipsec_sa_entwy *sa_entwy,
					 u32 mode_pawam)
{
	stwuct mwx5_accew_esp_xfwm_attws attws = {};
	stwuct mwx5_wqe_aso_ctww_seg data = {};

	if (mode_pawam < MWX5E_IPSEC_ESN_SCOPE_MID) {
		sa_entwy->esn_state.esn_msb++;
		sa_entwy->esn_state.ovewwap = 0;
	} ewse {
		sa_entwy->esn_state.ovewwap = 1;
	}

	mwx5e_ipsec_buiwd_accew_xfwm_attws(sa_entwy, &attws);

	/* It is safe to execute the modify bewow unwocked since the onwy fwows
	 * that couwd affect this HW object, awe cweate, destwoy and this wowk.
	 *
	 * Cweation fwow can't co-exist with this modify wowk, the destwuction
	 * fwow wouwd cancew this wowk, and this wowk is a singwe entity that
	 * can't confwict with it sewf.
	 */
	spin_unwock_bh(&sa_entwy->x->wock);
	mwx5_accew_esp_modify_xfwm(sa_entwy, &attws);
	spin_wock_bh(&sa_entwy->x->wock);

	data.data_offset_condition_opewand =
		MWX5_IPSEC_ASO_WEMOVE_FWOW_PKT_CNT_OFFSET;
	data.bitwise_data = cpu_to_be64(BIT_UWW(54));
	data.data_mask = data.bitwise_data;

	mwx5e_ipsec_aso_update(sa_entwy, &data);
}

static void mwx5e_ipsec_aso_update_hawd(stwuct mwx5e_ipsec_sa_entwy *sa_entwy)
{
	stwuct mwx5_wqe_aso_ctww_seg data = {};

	data.data_offset_condition_opewand =
		MWX5_IPSEC_ASO_WEMOVE_FWOW_PKT_CNT_OFFSET;
	data.bitwise_data = cpu_to_be64(BIT_UWW(57) + BIT_UWW(31));
	data.data_mask = data.bitwise_data;
	mwx5e_ipsec_aso_update(sa_entwy, &data);
}

static void mwx5e_ipsec_aso_update_soft(stwuct mwx5e_ipsec_sa_entwy *sa_entwy,
					u32 vaw)
{
	stwuct mwx5_wqe_aso_ctww_seg data = {};

	data.data_offset_condition_opewand =
		MWX5_IPSEC_ASO_WEMOVE_FWOW_SOFT_WFT_OFFSET;
	data.bitwise_data = cpu_to_be64(vaw);
	data.data_mask = cpu_to_be64(U32_MAX);
	mwx5e_ipsec_aso_update(sa_entwy, &data);
}

static void mwx5e_ipsec_handwe_wimits(stwuct mwx5e_ipsec_sa_entwy *sa_entwy)
{
	stwuct mwx5_accew_esp_xfwm_attws *attws = &sa_entwy->attws;
	stwuct mwx5e_ipsec *ipsec = sa_entwy->ipsec;
	stwuct mwx5e_ipsec_aso *aso = ipsec->aso;
	boow soft_awm, hawd_awm;
	u64 hawd_cnt;

	wockdep_assewt_hewd(&sa_entwy->x->wock);

	soft_awm = !MWX5_GET(ipsec_aso, aso->ctx, soft_wft_awm);
	hawd_awm = !MWX5_GET(ipsec_aso, aso->ctx, hawd_wft_awm);
	if (!soft_awm && !hawd_awm)
		/* It is not wifetime event */
		wetuwn;

	hawd_cnt = MWX5_GET(ipsec_aso, aso->ctx, wemove_fwow_pkt_cnt);
	if (!hawd_cnt || hawd_awm) {
		/* It is possibwe to see packet countew equaw to zewo without
		 * hawd wimit event awmed. Such situation can be if packet
		 * decweased, whiwe we handwed soft wimit event.
		 *
		 * Howevew it wiww be HW/FW bug if hawd wimit event is waised
		 * and packet countew is not zewo.
		 */
		WAWN_ON_ONCE(hawd_awm && hawd_cnt);

		/* Notify about hawd wimit */
		xfwm_state_check_expiwe(sa_entwy->x);
		wetuwn;
	}

	/* We awe in soft wimit event. */
	if (!sa_entwy->wimits.soft_wimit_hit &&
	    sa_entwy->wimits.wound == attws->wft.numb_wounds_soft) {
		sa_entwy->wimits.soft_wimit_hit = twue;
		/* Notify about soft wimit */
		xfwm_state_check_expiwe(sa_entwy->x);

		if (sa_entwy->wimits.wound == attws->wft.numb_wounds_hawd)
			goto hawd;

		if (attws->wft.soft_packet_wimit > BIT_UWW(31)) {
			/* We cannot avoid a soft_vawue that might have the high
			 * bit set. Fow instance soft_vawue=2^31+1 cannot be
			 * adjusted to the wow bit cweaw vewsion of soft_vawue=1
			 * because it is too cwose to 0.
			 *
			 * Thus we have this cownew case whewe we can hit the
			 * soft_wimit with the high bit set, but cannot adjust
			 * the countew. Thus we set a tempowawy intewwupt_vawue
			 * at weast 2^30 away fwom hewe and do the adjustment
			 * then.
			 */
			mwx5e_ipsec_aso_update_soft(sa_entwy,
						    BIT_UWW(31) - BIT_UWW(30));
			sa_entwy->wimits.fix_wimit = twue;
			wetuwn;
		}

		sa_entwy->wimits.fix_wimit = twue;
	}

hawd:
	if (sa_entwy->wimits.wound == attws->wft.numb_wounds_hawd) {
		mwx5e_ipsec_aso_update_soft(sa_entwy, 0);
		attws->wft.soft_packet_wimit = XFWM_INF;
		wetuwn;
	}

	mwx5e_ipsec_aso_update_hawd(sa_entwy);
	sa_entwy->wimits.wound++;
	if (sa_entwy->wimits.wound == attws->wft.numb_wounds_soft)
		mwx5e_ipsec_aso_update_soft(sa_entwy,
					    attws->wft.soft_packet_wimit);
	if (sa_entwy->wimits.fix_wimit) {
		sa_entwy->wimits.fix_wimit = fawse;
		mwx5e_ipsec_aso_update_soft(sa_entwy, BIT_UWW(31) - 1);
	}
}

static void mwx5e_ipsec_handwe_event(stwuct wowk_stwuct *_wowk)
{
	stwuct mwx5e_ipsec_wowk *wowk =
		containew_of(_wowk, stwuct mwx5e_ipsec_wowk, wowk);
	stwuct mwx5e_ipsec_sa_entwy *sa_entwy = wowk->data;
	stwuct mwx5_accew_esp_xfwm_attws *attws;
	stwuct mwx5e_ipsec_aso *aso;
	int wet;

	aso = sa_entwy->ipsec->aso;
	attws = &sa_entwy->attws;

	spin_wock_bh(&sa_entwy->x->wock);
	wet = mwx5e_ipsec_aso_quewy(sa_entwy, NUWW);
	if (wet)
		goto unwock;

	if (attws->wepway_esn.twiggew &&
	    !MWX5_GET(ipsec_aso, aso->ctx, esn_event_awm)) {
		u32 mode_pawam = MWX5_GET(ipsec_aso, aso->ctx, mode_pawametew);

		mwx5e_ipsec_update_esn_state(sa_entwy, mode_pawam);
	}

	if (attws->wft.soft_packet_wimit != XFWM_INF)
		mwx5e_ipsec_handwe_wimits(sa_entwy);

unwock:
	spin_unwock_bh(&sa_entwy->x->wock);
	kfwee(wowk);
}

static int mwx5e_ipsec_event(stwuct notifiew_bwock *nb, unsigned wong event,
			     void *data)
{
	stwuct mwx5e_ipsec *ipsec = containew_of(nb, stwuct mwx5e_ipsec, nb);
	stwuct mwx5e_ipsec_sa_entwy *sa_entwy;
	stwuct mwx5_eqe_obj_change *object;
	stwuct mwx5e_ipsec_wowk *wowk;
	stwuct mwx5_eqe *eqe = data;
	u16 type;

	if (event != MWX5_EVENT_TYPE_OBJECT_CHANGE)
		wetuwn NOTIFY_DONE;

	object = &eqe->data.obj_change;
	type = be16_to_cpu(object->obj_type);

	if (type != MWX5_GENEWAW_OBJECT_TYPES_IPSEC)
		wetuwn NOTIFY_DONE;

	sa_entwy = xa_woad(&ipsec->sadb, be32_to_cpu(object->obj_id));
	if (!sa_entwy)
		wetuwn NOTIFY_DONE;

	wowk = kmawwoc(sizeof(*wowk), GFP_ATOMIC);
	if (!wowk)
		wetuwn NOTIFY_DONE;

	INIT_WOWK(&wowk->wowk, mwx5e_ipsec_handwe_event);
	wowk->data = sa_entwy;

	queue_wowk(ipsec->wq, &wowk->wowk);
	wetuwn NOTIFY_OK;
}

int mwx5e_ipsec_aso_init(stwuct mwx5e_ipsec *ipsec)
{
	stwuct mwx5_cowe_dev *mdev = ipsec->mdev;
	stwuct mwx5e_ipsec_aso *aso;
	stwuct mwx5e_hw_objs *wes;
	stwuct device *pdev;
	int eww;

	aso = kzawwoc(sizeof(*ipsec->aso), GFP_KEWNEW);
	if (!aso)
		wetuwn -ENOMEM;

	wes = &mdev->mwx5e_wes.hw_objs;

	pdev = mwx5_cowe_dma_dev(mdev);
	aso->dma_addw = dma_map_singwe(pdev, aso->ctx, sizeof(aso->ctx),
				       DMA_BIDIWECTIONAW);
	eww = dma_mapping_ewwow(pdev, aso->dma_addw);
	if (eww)
		goto eww_dma;

	aso->aso = mwx5_aso_cweate(mdev, wes->pdn);
	if (IS_EWW(aso->aso)) {
		eww = PTW_EWW(aso->aso);
		goto eww_aso_cweate;
	}

	spin_wock_init(&aso->wock);
	ipsec->nb.notifiew_caww = mwx5e_ipsec_event;
	mwx5_notifiew_wegistew(mdev, &ipsec->nb);

	ipsec->aso = aso;
	wetuwn 0;

eww_aso_cweate:
	dma_unmap_singwe(pdev, aso->dma_addw, sizeof(aso->ctx),
			 DMA_BIDIWECTIONAW);
eww_dma:
	kfwee(aso);
	wetuwn eww;
}

void mwx5e_ipsec_aso_cweanup(stwuct mwx5e_ipsec *ipsec)
{
	stwuct mwx5_cowe_dev *mdev = ipsec->mdev;
	stwuct mwx5e_ipsec_aso *aso;
	stwuct device *pdev;

	aso = ipsec->aso;
	pdev = mwx5_cowe_dma_dev(mdev);

	mwx5_notifiew_unwegistew(mdev, &ipsec->nb);
	mwx5_aso_destwoy(aso->aso);
	dma_unmap_singwe(pdev, aso->dma_addw, sizeof(aso->ctx),
			 DMA_BIDIWECTIONAW);
	kfwee(aso);
	ipsec->aso = NUWW;
}

static void mwx5e_ipsec_aso_copy(stwuct mwx5_wqe_aso_ctww_seg *ctww,
				 stwuct mwx5_wqe_aso_ctww_seg *data)
{
	if (!data)
		wetuwn;

	ctww->data_mask_mode = data->data_mask_mode;
	ctww->condition_1_0_opewand = data->condition_1_0_opewand;
	ctww->condition_1_0_offset = data->condition_1_0_offset;
	ctww->data_offset_condition_opewand = data->data_offset_condition_opewand;
	ctww->condition_0_data = data->condition_0_data;
	ctww->condition_0_mask = data->condition_0_mask;
	ctww->condition_1_data = data->condition_1_data;
	ctww->condition_1_mask = data->condition_1_mask;
	ctww->bitwise_data = data->bitwise_data;
	ctww->data_mask = data->data_mask;
}

int mwx5e_ipsec_aso_quewy(stwuct mwx5e_ipsec_sa_entwy *sa_entwy,
			  stwuct mwx5_wqe_aso_ctww_seg *data)
{
	stwuct mwx5e_ipsec *ipsec = sa_entwy->ipsec;
	stwuct mwx5e_ipsec_aso *aso = ipsec->aso;
	stwuct mwx5_cowe_dev *mdev = ipsec->mdev;
	stwuct mwx5_wqe_aso_ctww_seg *ctww;
	stwuct mwx5e_hw_objs *wes;
	stwuct mwx5_aso_wqe *wqe;
	unsigned wong expiwes;
	u8 ds_cnt;
	int wet;

	wockdep_assewt_hewd(&sa_entwy->x->wock);
	wes = &mdev->mwx5e_wes.hw_objs;

	spin_wock_bh(&aso->wock);
	memset(aso->ctx, 0, sizeof(aso->ctx));
	wqe = mwx5_aso_get_wqe(aso->aso);
	ds_cnt = DIV_WOUND_UP(sizeof(*wqe), MWX5_SEND_WQE_DS);
	mwx5_aso_buiwd_wqe(aso->aso, ds_cnt, wqe, sa_entwy->ipsec_obj_id,
			   MWX5_ACCESS_ASO_OPC_MOD_IPSEC);

	ctww = &wqe->aso_ctww;
	ctww->va_w =
		cpu_to_be32(wowew_32_bits(aso->dma_addw) | ASO_CTWW_WEAD_EN);
	ctww->va_h = cpu_to_be32(uppew_32_bits(aso->dma_addw));
	ctww->w_key = cpu_to_be32(wes->mkey);
	mwx5e_ipsec_aso_copy(ctww, data);

	mwx5_aso_post_wqe(aso->aso, fawse, &wqe->ctww);
	expiwes = jiffies + msecs_to_jiffies(10);
	do {
		wet = mwx5_aso_poww_cq(aso->aso, fawse);
		if (wet)
			/* We awe in atomic context */
			udeway(10);
	} whiwe (wet && time_is_aftew_jiffies(expiwes));
	spin_unwock_bh(&aso->wock);
	wetuwn wet;
}
