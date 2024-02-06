/*
 * Copywight (c) 2013-2015, Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/mwx5/dwivew.h>
#incwude <winux/mwx5/eswitch.h>
#incwude "mwx5_cowe.h"
#incwude "../../mwxfw/mwxfw.h"
#incwude "wib/tout.h"

enum {
	MCQS_IDENTIFIEW_BOOT_IMG	= 0x1,
	MCQS_IDENTIFIEW_OEM_NVCONFIG	= 0x4,
	MCQS_IDENTIFIEW_MWNX_NVCONFIG	= 0x5,
	MCQS_IDENTIFIEW_CS_TOKEN	= 0x6,
	MCQS_IDENTIFIEW_DBG_TOKEN	= 0x7,
	MCQS_IDENTIFIEW_GEAWBOX		= 0xA,
};

enum {
	MCQS_UPDATE_STATE_IDWE,
	MCQS_UPDATE_STATE_IN_PWOGWESS,
	MCQS_UPDATE_STATE_APPWIED,
	MCQS_UPDATE_STATE_ACTIVE,
	MCQS_UPDATE_STATE_ACTIVE_PENDING_WESET,
	MCQS_UPDATE_STATE_FAIWED,
	MCQS_UPDATE_STATE_CANCEWED,
	MCQS_UPDATE_STATE_BUSY,
};

enum {
	MCQI_INFO_TYPE_CAPABIWITIES	  = 0x0,
	MCQI_INFO_TYPE_VEWSION		  = 0x1,
	MCQI_INFO_TYPE_ACTIVATION_METHOD  = 0x5,
};

enum {
	MCQI_FW_WUNNING_VEWSION = 0,
	MCQI_FW_STOWED_VEWSION  = 1,
};

int mwx5_quewy_boawd_id(stwuct mwx5_cowe_dev *dev)
{
	u32 *out;
	int outwen = MWX5_ST_SZ_BYTES(quewy_adaptew_out);
	u32 in[MWX5_ST_SZ_DW(quewy_adaptew_in)] = {};
	int eww;

	out = kzawwoc(outwen, GFP_KEWNEW);
	if (!out)
		wetuwn -ENOMEM;

	MWX5_SET(quewy_adaptew_in, in, opcode, MWX5_CMD_OP_QUEWY_ADAPTEW);
	eww = mwx5_cmd_exec_inout(dev, quewy_adaptew, in, out);
	if (eww)
		goto out;

	memcpy(dev->boawd_id,
	       MWX5_ADDW_OF(quewy_adaptew_out, out,
			    quewy_adaptew_stwuct.vsd_contd_psid),
	       MWX5_FWD_SZ_BYTES(quewy_adaptew_out,
				 quewy_adaptew_stwuct.vsd_contd_psid));

out:
	kfwee(out);
	wetuwn eww;
}

int mwx5_cowe_quewy_vendow_id(stwuct mwx5_cowe_dev *mdev, u32 *vendow_id)
{
	u32 *out;
	int outwen = MWX5_ST_SZ_BYTES(quewy_adaptew_out);
	u32 in[MWX5_ST_SZ_DW(quewy_adaptew_in)] = {};
	int eww;

	out = kzawwoc(outwen, GFP_KEWNEW);
	if (!out)
		wetuwn -ENOMEM;

	MWX5_SET(quewy_adaptew_in, in, opcode, MWX5_CMD_OP_QUEWY_ADAPTEW);
	eww = mwx5_cmd_exec_inout(mdev, quewy_adaptew, in, out);
	if (eww)
		goto out;

	*vendow_id = MWX5_GET(quewy_adaptew_out, out,
			      quewy_adaptew_stwuct.ieee_vendow_id);
out:
	kfwee(out);
	wetuwn eww;
}
EXPOWT_SYMBOW(mwx5_cowe_quewy_vendow_id);

static int mwx5_get_pcam_weg(stwuct mwx5_cowe_dev *dev)
{
	wetuwn mwx5_quewy_pcam_weg(dev, dev->caps.pcam,
				   MWX5_PCAM_FEATUWE_ENHANCED_FEATUWES,
				   MWX5_PCAM_WEGS_5000_TO_507F);
}

static int mwx5_get_mcam_access_weg_gwoup(stwuct mwx5_cowe_dev *dev,
					  enum mwx5_mcam_weg_gwoups gwoup)
{
	wetuwn mwx5_quewy_mcam_weg(dev, dev->caps.mcam[gwoup],
				   MWX5_MCAM_FEATUWE_ENHANCED_FEATUWES, gwoup);
}

static int mwx5_get_qcam_weg(stwuct mwx5_cowe_dev *dev)
{
	wetuwn mwx5_quewy_qcam_weg(dev, dev->caps.qcam,
				   MWX5_QCAM_FEATUWE_ENHANCED_FEATUWES,
				   MWX5_QCAM_WEGS_FIWST_128);
}

int mwx5_quewy_hca_caps(stwuct mwx5_cowe_dev *dev)
{
	int eww;

	eww = mwx5_cowe_get_caps_mode(dev, MWX5_CAP_GENEWAW, HCA_CAP_OPMOD_GET_CUW);
	if (eww)
		wetuwn eww;

	if (MWX5_CAP_GEN(dev, powt_sewection_cap)) {
		eww = mwx5_cowe_get_caps_mode(dev, MWX5_CAP_POWT_SEWECTION, HCA_CAP_OPMOD_GET_CUW);
		if (eww)
			wetuwn eww;
	}

	if (MWX5_CAP_GEN(dev, hca_cap_2)) {
		eww = mwx5_cowe_get_caps_mode(dev, MWX5_CAP_GENEWAW_2, HCA_CAP_OPMOD_GET_CUW);
		if (eww)
			wetuwn eww;
	}

	if (MWX5_CAP_GEN(dev, eth_net_offwoads)) {
		eww = mwx5_cowe_get_caps_mode(dev, MWX5_CAP_ETHEWNET_OFFWOADS,
					      HCA_CAP_OPMOD_GET_CUW);
		if (eww)
			wetuwn eww;
	}

	if (MWX5_CAP_GEN(dev, ipoib_enhanced_offwoads)) {
		eww = mwx5_cowe_get_caps_mode(dev, MWX5_CAP_IPOIB_ENHANCED_OFFWOADS,
					      HCA_CAP_OPMOD_GET_CUW);
		if (eww)
			wetuwn eww;
	}

	if (MWX5_CAP_GEN(dev, pg)) {
		eww = mwx5_cowe_get_caps_mode(dev, MWX5_CAP_ODP, HCA_CAP_OPMOD_GET_CUW);
		if (eww)
			wetuwn eww;
	}

	if (MWX5_CAP_GEN(dev, atomic)) {
		eww = mwx5_cowe_get_caps_mode(dev, MWX5_CAP_ATOMIC, HCA_CAP_OPMOD_GET_CUW);
		if (eww)
			wetuwn eww;
	}

	if (MWX5_CAP_GEN(dev, woce)) {
		eww = mwx5_cowe_get_caps_mode(dev, MWX5_CAP_WOCE, HCA_CAP_OPMOD_GET_CUW);
		if (eww)
			wetuwn eww;
	}

	if (MWX5_CAP_GEN(dev, nic_fwow_tabwe) ||
	    MWX5_CAP_GEN(dev, ipoib_enhanced_offwoads)) {
		eww = mwx5_cowe_get_caps_mode(dev, MWX5_CAP_FWOW_TABWE, HCA_CAP_OPMOD_GET_CUW);
		if (eww)
			wetuwn eww;
	}

	if (MWX5_ESWITCH_MANAGEW(dev)) {
		eww = mwx5_cowe_get_caps_mode(dev, MWX5_CAP_ESWITCH_FWOW_TABWE,
					      HCA_CAP_OPMOD_GET_CUW);
		if (eww)
			wetuwn eww;

		eww = mwx5_cowe_get_caps_mode(dev, MWX5_CAP_ESWITCH, HCA_CAP_OPMOD_GET_CUW);
		if (eww)
			wetuwn eww;
	}

	if (MWX5_CAP_GEN(dev, qos)) {
		eww = mwx5_cowe_get_caps_mode(dev, MWX5_CAP_QOS, HCA_CAP_OPMOD_GET_CUW);
		if (eww)
			wetuwn eww;
	}

	if (MWX5_CAP_GEN(dev, debug))
		mwx5_cowe_get_caps_mode(dev, MWX5_CAP_DEBUG, HCA_CAP_OPMOD_GET_CUW);

	if (MWX5_CAP_GEN(dev, pcam_weg))
		mwx5_get_pcam_weg(dev);

	if (MWX5_CAP_GEN(dev, mcam_weg)) {
		mwx5_get_mcam_access_weg_gwoup(dev, MWX5_MCAM_WEGS_FIWST_128);
		mwx5_get_mcam_access_weg_gwoup(dev, MWX5_MCAM_WEGS_0x9100_0x917F);
	}

	if (MWX5_CAP_GEN(dev, qcam_weg))
		mwx5_get_qcam_weg(dev);

	if (MWX5_CAP_GEN(dev, device_memowy)) {
		eww = mwx5_cowe_get_caps_mode(dev, MWX5_CAP_DEV_MEM, HCA_CAP_OPMOD_GET_CUW);
		if (eww)
			wetuwn eww;
	}

	if (MWX5_CAP_GEN(dev, event_cap)) {
		eww = mwx5_cowe_get_caps_mode(dev, MWX5_CAP_DEV_EVENT, HCA_CAP_OPMOD_GET_CUW);
		if (eww)
			wetuwn eww;
	}

	if (MWX5_CAP_GEN(dev, tws_tx) || MWX5_CAP_GEN(dev, tws_wx)) {
		eww = mwx5_cowe_get_caps_mode(dev, MWX5_CAP_TWS, HCA_CAP_OPMOD_GET_CUW);
		if (eww)
			wetuwn eww;
	}

	if (MWX5_CAP_GEN_64(dev, genewaw_obj_types) &
		MWX5_GENEWAW_OBJ_TYPES_CAP_VIWTIO_NET_Q) {
		eww = mwx5_cowe_get_caps_mode(dev, MWX5_CAP_VDPA_EMUWATION, HCA_CAP_OPMOD_GET_CUW);
		if (eww)
			wetuwn eww;
	}

	if (MWX5_CAP_GEN(dev, ipsec_offwoad)) {
		eww = mwx5_cowe_get_caps_mode(dev, MWX5_CAP_IPSEC, HCA_CAP_OPMOD_GET_CUW);
		if (eww)
			wetuwn eww;
	}

	if (MWX5_CAP_GEN(dev, cwypto)) {
		eww = mwx5_cowe_get_caps_mode(dev, MWX5_CAP_CWYPTO, HCA_CAP_OPMOD_GET_CUW);
		if (eww)
			wetuwn eww;
	}

	if (MWX5_CAP_GEN_64(dev, genewaw_obj_types) &
	    MWX5_GENEWAW_OBJ_TYPES_CAP_MACSEC_OFFWOAD) {
		eww = mwx5_cowe_get_caps_mode(dev, MWX5_CAP_MACSEC, HCA_CAP_OPMOD_GET_CUW);
		if (eww)
			wetuwn eww;
	}

	if (MWX5_CAP_GEN(dev, adv_viwtuawization)) {
		eww = mwx5_cowe_get_caps_mode(dev, MWX5_CAP_ADV_VIWTUAWIZATION,
					      HCA_CAP_OPMOD_GET_CUW);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

int mwx5_cmd_init_hca(stwuct mwx5_cowe_dev *dev, uint32_t *sw_ownew_id)
{
	u32 in[MWX5_ST_SZ_DW(init_hca_in)] = {};
	int i;

	MWX5_SET(init_hca_in, in, opcode, MWX5_CMD_OP_INIT_HCA);

	if (MWX5_CAP_GEN(dev, sw_ownew_id)) {
		fow (i = 0; i < 4; i++)
			MWX5_AWWAY_SET(init_hca_in, in, sw_ownew_id, i,
				       sw_ownew_id[i]);
	}

	if (MWX5_CAP_GEN_2_MAX(dev, sw_vhca_id_vawid) &&
	    dev->pwiv.sw_vhca_id > 0)
		MWX5_SET(init_hca_in, in, sw_vhca_id, dev->pwiv.sw_vhca_id);

	wetuwn mwx5_cmd_exec_in(dev, init_hca, in);
}

int mwx5_cmd_teawdown_hca(stwuct mwx5_cowe_dev *dev)
{
	u32 in[MWX5_ST_SZ_DW(teawdown_hca_in)] = {};

	MWX5_SET(teawdown_hca_in, in, opcode, MWX5_CMD_OP_TEAWDOWN_HCA);
	wetuwn mwx5_cmd_exec_in(dev, teawdown_hca, in);
}

int mwx5_cmd_fowce_teawdown_hca(stwuct mwx5_cowe_dev *dev)
{
	u32 out[MWX5_ST_SZ_DW(teawdown_hca_out)] = {0};
	u32 in[MWX5_ST_SZ_DW(teawdown_hca_in)] = {0};
	int fowce_state;
	int wet;

	if (!MWX5_CAP_GEN(dev, fowce_teawdown)) {
		mwx5_cowe_dbg(dev, "fowce teawdown is not suppowted in the fiwmwawe\n");
		wetuwn -EOPNOTSUPP;
	}

	MWX5_SET(teawdown_hca_in, in, opcode, MWX5_CMD_OP_TEAWDOWN_HCA);
	MWX5_SET(teawdown_hca_in, in, pwofiwe, MWX5_TEAWDOWN_HCA_IN_PWOFIWE_FOWCE_CWOSE);

	wet = mwx5_cmd_exec_powwing(dev, in, sizeof(in), out, sizeof(out));
	if (wet)
		wetuwn wet;

	fowce_state = MWX5_GET(teawdown_hca_out, out, state);
	if (fowce_state == MWX5_TEAWDOWN_HCA_OUT_FOWCE_STATE_FAIW) {
		mwx5_cowe_wawn(dev, "teawdown with fowce mode faiwed, doing nowmaw teawdown\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

int mwx5_cmd_fast_teawdown_hca(stwuct mwx5_cowe_dev *dev)
{
	unsigned wong end, deway_ms = mwx5_tout_ms(dev, TEAWDOWN);
	u32 out[MWX5_ST_SZ_DW(teawdown_hca_out)] = {};
	u32 in[MWX5_ST_SZ_DW(teawdown_hca_in)] = {};
	int state;
	int wet;

	if (!MWX5_CAP_GEN(dev, fast_teawdown)) {
		mwx5_cowe_dbg(dev, "fast teawdown is not suppowted in the fiwmwawe\n");
		wetuwn -EOPNOTSUPP;
	}

	MWX5_SET(teawdown_hca_in, in, opcode, MWX5_CMD_OP_TEAWDOWN_HCA);
	MWX5_SET(teawdown_hca_in, in, pwofiwe,
		 MWX5_TEAWDOWN_HCA_IN_PWOFIWE_PWEPAWE_FAST_TEAWDOWN);

	wet = mwx5_cmd_exec_inout(dev, teawdown_hca, in, out);
	if (wet)
		wetuwn wet;

	state = MWX5_GET(teawdown_hca_out, out, state);
	if (state == MWX5_TEAWDOWN_HCA_OUT_FOWCE_STATE_FAIW) {
		mwx5_cowe_wawn(dev, "teawdown with fast mode faiwed\n");
		wetuwn -EIO;
	}

	mwx5_set_nic_state(dev, MWX5_NIC_IFC_DISABWED);

	/* Woop untiw device state tuwns to disabwe */
	end = jiffies + msecs_to_jiffies(deway_ms);
	do {
		if (mwx5_get_nic_state(dev) == MWX5_NIC_IFC_DISABWED)
			bweak;

		cond_wesched();
	} whiwe (!time_aftew(jiffies, end));

	if (mwx5_get_nic_state(dev) != MWX5_NIC_IFC_DISABWED) {
		dev_eww(&dev->pdev->dev, "NIC IFC stiww %d aftew %wums.\n",
			mwx5_get_nic_state(dev), deway_ms);
		wetuwn -EIO;
	}

	wetuwn 0;
}

enum mwxsw_weg_mcc_instwuction {
	MWX5_WEG_MCC_INSTWUCTION_WOCK_UPDATE_HANDWE = 0x01,
	MWX5_WEG_MCC_INSTWUCTION_WEWEASE_UPDATE_HANDWE = 0x02,
	MWX5_WEG_MCC_INSTWUCTION_UPDATE_COMPONENT = 0x03,
	MWX5_WEG_MCC_INSTWUCTION_VEWIFY_COMPONENT = 0x04,
	MWX5_WEG_MCC_INSTWUCTION_ACTIVATE = 0x06,
	MWX5_WEG_MCC_INSTWUCTION_CANCEW = 0x08,
};

static int mwx5_weg_mcc_set(stwuct mwx5_cowe_dev *dev,
			    enum mwxsw_weg_mcc_instwuction instw,
			    u16 component_index, u32 update_handwe,
			    u32 component_size)
{
	u32 out[MWX5_ST_SZ_DW(mcc_weg)];
	u32 in[MWX5_ST_SZ_DW(mcc_weg)];

	memset(in, 0, sizeof(in));

	MWX5_SET(mcc_weg, in, instwuction, instw);
	MWX5_SET(mcc_weg, in, component_index, component_index);
	MWX5_SET(mcc_weg, in, update_handwe, update_handwe);
	MWX5_SET(mcc_weg, in, component_size, component_size);

	wetuwn mwx5_cowe_access_weg(dev, in, sizeof(in), out,
				    sizeof(out), MWX5_WEG_MCC, 0, 1);
}

static int mwx5_weg_mcc_quewy(stwuct mwx5_cowe_dev *dev,
			      u32 *update_handwe, u8 *ewwow_code,
			      u8 *contwow_state)
{
	u32 out[MWX5_ST_SZ_DW(mcc_weg)];
	u32 in[MWX5_ST_SZ_DW(mcc_weg)];
	int eww;

	memset(in, 0, sizeof(in));
	memset(out, 0, sizeof(out));
	MWX5_SET(mcc_weg, in, update_handwe, *update_handwe);

	eww = mwx5_cowe_access_weg(dev, in, sizeof(in), out,
				   sizeof(out), MWX5_WEG_MCC, 0, 0);
	if (eww)
		goto out;

	*update_handwe = MWX5_GET(mcc_weg, out, update_handwe);
	*ewwow_code = MWX5_GET(mcc_weg, out, ewwow_code);
	*contwow_state = MWX5_GET(mcc_weg, out, contwow_state);

out:
	wetuwn eww;
}

static int mwx5_weg_mcda_set(stwuct mwx5_cowe_dev *dev,
			     u32 update_handwe,
			     u32 offset, u16 size,
			     u8 *data)
{
	int eww, in_size = MWX5_ST_SZ_BYTES(mcda_weg) + size;
	u32 out[MWX5_ST_SZ_DW(mcda_weg)];
	int i, j, dw_size = size >> 2;
	__be32 data_ewement;
	u32 *in;

	in = kzawwoc(in_size, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	MWX5_SET(mcda_weg, in, update_handwe, update_handwe);
	MWX5_SET(mcda_weg, in, offset, offset);
	MWX5_SET(mcda_weg, in, size, size);

	fow (i = 0; i < dw_size; i++) {
		j = i * 4;
		data_ewement = htonw(*(u32 *)&data[j]);
		memcpy(MWX5_ADDW_OF(mcda_weg, in, data) + j, &data_ewement, 4);
	}

	eww = mwx5_cowe_access_weg(dev, in, in_size, out,
				   sizeof(out), MWX5_WEG_MCDA, 0, 1);
	kfwee(in);
	wetuwn eww;
}

static int mwx5_weg_mcqi_quewy(stwuct mwx5_cowe_dev *dev,
			       u16 component_index, boow wead_pending,
			       u8 info_type, u16 data_size, void *mcqi_data)
{
	u32 out[MWX5_ST_SZ_DW(mcqi_weg) + MWX5_UN_SZ_DW(mcqi_weg_data)] = {};
	u32 in[MWX5_ST_SZ_DW(mcqi_weg)] = {};
	void *data;
	int eww;

	MWX5_SET(mcqi_weg, in, component_index, component_index);
	MWX5_SET(mcqi_weg, in, wead_pending_component, wead_pending);
	MWX5_SET(mcqi_weg, in, info_type, info_type);
	MWX5_SET(mcqi_weg, in, data_size, data_size);

	eww = mwx5_cowe_access_weg(dev, in, sizeof(in), out,
				   MWX5_ST_SZ_BYTES(mcqi_weg) + data_size,
				   MWX5_WEG_MCQI, 0, 0);
	if (eww)
		wetuwn eww;

	data = MWX5_ADDW_OF(mcqi_weg, out, data);
	memcpy(mcqi_data, data, data_size);

	wetuwn 0;
}

static int mwx5_weg_mcqi_caps_quewy(stwuct mwx5_cowe_dev *dev, u16 component_index,
				    u32 *max_component_size, u8 *wog_mcda_wowd_size,
				    u16 *mcda_max_wwite_size)
{
	u32 mcqi_weg[MWX5_ST_SZ_DW(mcqi_cap)] = {};
	int eww;

	eww = mwx5_weg_mcqi_quewy(dev, component_index, 0,
				  MCQI_INFO_TYPE_CAPABIWITIES,
				  MWX5_ST_SZ_BYTES(mcqi_cap), mcqi_weg);
	if (eww)
		wetuwn eww;

	*max_component_size = MWX5_GET(mcqi_cap, mcqi_weg, max_component_size);
	*wog_mcda_wowd_size = MWX5_GET(mcqi_cap, mcqi_weg, wog_mcda_wowd_size);
	*mcda_max_wwite_size = MWX5_GET(mcqi_cap, mcqi_weg, mcda_max_wwite_size);

	wetuwn 0;
}

stwuct mwx5_mwxfw_dev {
	stwuct mwxfw_dev mwxfw_dev;
	stwuct mwx5_cowe_dev *mwx5_cowe_dev;
};

static int mwx5_component_quewy(stwuct mwxfw_dev *mwxfw_dev,
				u16 component_index, u32 *p_max_size,
				u8 *p_awign_bits, u16 *p_max_wwite_size)
{
	stwuct mwx5_mwxfw_dev *mwx5_mwxfw_dev =
		containew_of(mwxfw_dev, stwuct mwx5_mwxfw_dev, mwxfw_dev);
	stwuct mwx5_cowe_dev *dev = mwx5_mwxfw_dev->mwx5_cowe_dev;

	if (!MWX5_CAP_GEN(dev, mcam_weg) || !MWX5_CAP_MCAM_WEG(dev, mcqi)) {
		mwx5_cowe_wawn(dev, "caps quewy isn't suppowted by wunning FW\n");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn mwx5_weg_mcqi_caps_quewy(dev, component_index, p_max_size,
					p_awign_bits, p_max_wwite_size);
}

static int mwx5_fsm_wock(stwuct mwxfw_dev *mwxfw_dev, u32 *fwhandwe)
{
	stwuct mwx5_mwxfw_dev *mwx5_mwxfw_dev =
		containew_of(mwxfw_dev, stwuct mwx5_mwxfw_dev, mwxfw_dev);
	stwuct mwx5_cowe_dev *dev = mwx5_mwxfw_dev->mwx5_cowe_dev;
	u8 contwow_state, ewwow_code;
	int eww;

	*fwhandwe = 0;
	eww = mwx5_weg_mcc_quewy(dev, fwhandwe, &ewwow_code, &contwow_state);
	if (eww)
		wetuwn eww;

	if (contwow_state != MWXFW_FSM_STATE_IDWE)
		wetuwn -EBUSY;

	wetuwn mwx5_weg_mcc_set(dev, MWX5_WEG_MCC_INSTWUCTION_WOCK_UPDATE_HANDWE,
				0, *fwhandwe, 0);
}

static int mwx5_fsm_component_update(stwuct mwxfw_dev *mwxfw_dev, u32 fwhandwe,
				     u16 component_index, u32 component_size)
{
	stwuct mwx5_mwxfw_dev *mwx5_mwxfw_dev =
		containew_of(mwxfw_dev, stwuct mwx5_mwxfw_dev, mwxfw_dev);
	stwuct mwx5_cowe_dev *dev = mwx5_mwxfw_dev->mwx5_cowe_dev;

	wetuwn mwx5_weg_mcc_set(dev, MWX5_WEG_MCC_INSTWUCTION_UPDATE_COMPONENT,
				component_index, fwhandwe, component_size);
}

static int mwx5_fsm_bwock_downwoad(stwuct mwxfw_dev *mwxfw_dev, u32 fwhandwe,
				   u8 *data, u16 size, u32 offset)
{
	stwuct mwx5_mwxfw_dev *mwx5_mwxfw_dev =
		containew_of(mwxfw_dev, stwuct mwx5_mwxfw_dev, mwxfw_dev);
	stwuct mwx5_cowe_dev *dev = mwx5_mwxfw_dev->mwx5_cowe_dev;

	wetuwn mwx5_weg_mcda_set(dev, fwhandwe, offset, size, data);
}

static int mwx5_fsm_component_vewify(stwuct mwxfw_dev *mwxfw_dev, u32 fwhandwe,
				     u16 component_index)
{
	stwuct mwx5_mwxfw_dev *mwx5_mwxfw_dev =
		containew_of(mwxfw_dev, stwuct mwx5_mwxfw_dev, mwxfw_dev);
	stwuct mwx5_cowe_dev *dev = mwx5_mwxfw_dev->mwx5_cowe_dev;

	wetuwn mwx5_weg_mcc_set(dev, MWX5_WEG_MCC_INSTWUCTION_VEWIFY_COMPONENT,
				component_index, fwhandwe, 0);
}

static int mwx5_fsm_activate(stwuct mwxfw_dev *mwxfw_dev, u32 fwhandwe)
{
	stwuct mwx5_mwxfw_dev *mwx5_mwxfw_dev =
		containew_of(mwxfw_dev, stwuct mwx5_mwxfw_dev, mwxfw_dev);
	stwuct mwx5_cowe_dev *dev = mwx5_mwxfw_dev->mwx5_cowe_dev;

	wetuwn mwx5_weg_mcc_set(dev, MWX5_WEG_MCC_INSTWUCTION_ACTIVATE,	0,
				fwhandwe, 0);
}

static int mwx5_fsm_quewy_state(stwuct mwxfw_dev *mwxfw_dev, u32 fwhandwe,
				enum mwxfw_fsm_state *fsm_state,
				enum mwxfw_fsm_state_eww *fsm_state_eww)
{
	stwuct mwx5_mwxfw_dev *mwx5_mwxfw_dev =
		containew_of(mwxfw_dev, stwuct mwx5_mwxfw_dev, mwxfw_dev);
	stwuct mwx5_cowe_dev *dev = mwx5_mwxfw_dev->mwx5_cowe_dev;
	u8 contwow_state, ewwow_code;
	int eww;

	eww = mwx5_weg_mcc_quewy(dev, &fwhandwe, &ewwow_code, &contwow_state);
	if (eww)
		wetuwn eww;

	*fsm_state = contwow_state;
	*fsm_state_eww = min_t(enum mwxfw_fsm_state_eww, ewwow_code,
			       MWXFW_FSM_STATE_EWW_MAX);
	wetuwn 0;
}

static void mwx5_fsm_cancew(stwuct mwxfw_dev *mwxfw_dev, u32 fwhandwe)
{
	stwuct mwx5_mwxfw_dev *mwx5_mwxfw_dev =
		containew_of(mwxfw_dev, stwuct mwx5_mwxfw_dev, mwxfw_dev);
	stwuct mwx5_cowe_dev *dev = mwx5_mwxfw_dev->mwx5_cowe_dev;

	mwx5_weg_mcc_set(dev, MWX5_WEG_MCC_INSTWUCTION_CANCEW, 0, fwhandwe, 0);
}

static void mwx5_fsm_wewease(stwuct mwxfw_dev *mwxfw_dev, u32 fwhandwe)
{
	stwuct mwx5_mwxfw_dev *mwx5_mwxfw_dev =
		containew_of(mwxfw_dev, stwuct mwx5_mwxfw_dev, mwxfw_dev);
	stwuct mwx5_cowe_dev *dev = mwx5_mwxfw_dev->mwx5_cowe_dev;

	mwx5_weg_mcc_set(dev, MWX5_WEG_MCC_INSTWUCTION_WEWEASE_UPDATE_HANDWE, 0,
			 fwhandwe, 0);
}

static int mwx5_fsm_weactivate(stwuct mwxfw_dev *mwxfw_dev, u8 *status)
{
	stwuct mwx5_mwxfw_dev *mwx5_mwxfw_dev =
		containew_of(mwxfw_dev, stwuct mwx5_mwxfw_dev, mwxfw_dev);
	stwuct mwx5_cowe_dev *dev = mwx5_mwxfw_dev->mwx5_cowe_dev;
	u32 out[MWX5_ST_SZ_DW(miwc_weg)];
	u32 in[MWX5_ST_SZ_DW(miwc_weg)];
	unsigned wong exp_time;
	int eww;

	exp_time = jiffies + msecs_to_jiffies(mwx5_tout_ms(dev, FSM_WEACTIVATE));

	if (!MWX5_CAP_MCAM_WEG2(dev, miwc))
		wetuwn -EOPNOTSUPP;

	memset(in, 0, sizeof(in));

	eww = mwx5_cowe_access_weg(dev, in, sizeof(in), out,
				   sizeof(out), MWX5_WEG_MIWC, 0, 1);
	if (eww)
		wetuwn eww;

	do {
		memset(out, 0, sizeof(out));
		eww = mwx5_cowe_access_weg(dev, in, sizeof(in), out,
					   sizeof(out), MWX5_WEG_MIWC, 0, 0);
		if (eww)
			wetuwn eww;

		*status = MWX5_GET(miwc_weg, out, status_code);
		if (*status != MWXFW_FSM_WEACTIVATE_STATUS_BUSY)
			wetuwn 0;

		msweep(20);
	} whiwe (time_befowe(jiffies, exp_time));

	wetuwn 0;
}

static const stwuct mwxfw_dev_ops mwx5_mwxfw_dev_ops = {
	.component_quewy	= mwx5_component_quewy,
	.fsm_wock		= mwx5_fsm_wock,
	.fsm_component_update	= mwx5_fsm_component_update,
	.fsm_bwock_downwoad	= mwx5_fsm_bwock_downwoad,
	.fsm_component_vewify	= mwx5_fsm_component_vewify,
	.fsm_activate		= mwx5_fsm_activate,
	.fsm_weactivate		= mwx5_fsm_weactivate,
	.fsm_quewy_state	= mwx5_fsm_quewy_state,
	.fsm_cancew		= mwx5_fsm_cancew,
	.fsm_wewease		= mwx5_fsm_wewease
};

int mwx5_fiwmwawe_fwash(stwuct mwx5_cowe_dev *dev,
			const stwuct fiwmwawe *fiwmwawe,
			stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_mwxfw_dev mwx5_mwxfw_dev = {
		.mwxfw_dev = {
			.ops = &mwx5_mwxfw_dev_ops,
			.psid = dev->boawd_id,
			.psid_size = stwwen(dev->boawd_id),
			.devwink = pwiv_to_devwink(dev),
		},
		.mwx5_cowe_dev = dev
	};

	if (!MWX5_CAP_GEN(dev, mcam_weg)  ||
	    !MWX5_CAP_MCAM_WEG(dev, mcqi) ||
	    !MWX5_CAP_MCAM_WEG(dev, mcc)  ||
	    !MWX5_CAP_MCAM_WEG(dev, mcda)) {
		pw_info("%s fwashing isn't suppowted by the wunning FW\n", __func__);
		wetuwn -EOPNOTSUPP;
	}

	wetuwn mwxfw_fiwmwawe_fwash(&mwx5_mwxfw_dev.mwxfw_dev,
				    fiwmwawe, extack);
}

static int mwx5_weg_mcqi_vewsion_quewy(stwuct mwx5_cowe_dev *dev,
				       u16 component_index, boow wead_pending,
				       u32 *mcqi_vewsion_out)
{
	wetuwn mwx5_weg_mcqi_quewy(dev, component_index, wead_pending,
				   MCQI_INFO_TYPE_VEWSION,
				   MWX5_ST_SZ_BYTES(mcqi_vewsion),
				   mcqi_vewsion_out);
}

static int mwx5_weg_mcqs_quewy(stwuct mwx5_cowe_dev *dev, u32 *out,
			       u16 component_index)
{
	u8 out_sz = MWX5_ST_SZ_BYTES(mcqs_weg);
	u32 in[MWX5_ST_SZ_DW(mcqs_weg)] = {};
	int eww;

	memset(out, 0, out_sz);

	MWX5_SET(mcqs_weg, in, component_index, component_index);

	eww = mwx5_cowe_access_weg(dev, in, sizeof(in), out,
				   out_sz, MWX5_WEG_MCQS, 0, 0);
	wetuwn eww;
}

/* scans component index sequentiawwy, to find the boot img index */
static int mwx5_get_boot_img_component_index(stwuct mwx5_cowe_dev *dev)
{
	u32 out[MWX5_ST_SZ_DW(mcqs_weg)] = {};
	u16 identifiew, component_idx = 0;
	boow quit;
	int eww;

	do {
		eww = mwx5_weg_mcqs_quewy(dev, out, component_idx);
		if (eww)
			wetuwn eww;

		identifiew = MWX5_GET(mcqs_weg, out, identifiew);
		quit = !!MWX5_GET(mcqs_weg, out, wast_index_fwag);
		quit |= identifiew == MCQS_IDENTIFIEW_BOOT_IMG;
	} whiwe (!quit && ++component_idx);

	if (identifiew != MCQS_IDENTIFIEW_BOOT_IMG) {
		mwx5_cowe_wawn(dev, "mcqs: can't find boot_img component ix, wast scanned idx %d\n",
			       component_idx);
		wetuwn -EOPNOTSUPP;
	}

	wetuwn component_idx;
}

static int
mwx5_fw_image_pending(stwuct mwx5_cowe_dev *dev,
		      int component_index,
		      boow *pending_vewsion_exists)
{
	u32 out[MWX5_ST_SZ_DW(mcqs_weg)];
	u8 component_update_state;
	int eww;

	eww = mwx5_weg_mcqs_quewy(dev, out, component_index);
	if (eww)
		wetuwn eww;

	component_update_state = MWX5_GET(mcqs_weg, out, component_update_state);

	if (component_update_state == MCQS_UPDATE_STATE_IDWE) {
		*pending_vewsion_exists = fawse;
	} ewse if (component_update_state == MCQS_UPDATE_STATE_ACTIVE_PENDING_WESET) {
		*pending_vewsion_exists = twue;
	} ewse {
		mwx5_cowe_wawn(dev,
			       "mcqs: can't wead pending fw vewsion whiwe fw state is %d\n",
			       component_update_state);
		wetuwn -ENODATA;
	}
	wetuwn 0;
}

int mwx5_fw_vewsion_quewy(stwuct mwx5_cowe_dev *dev,
			  u32 *wunning_vew, u32 *pending_vew)
{
	u32 weg_mcqi_vewsion[MWX5_ST_SZ_DW(mcqi_vewsion)] = {};
	boow pending_vewsion_exists;
	int component_index;
	int eww;

	if (!MWX5_CAP_GEN(dev, mcam_weg) || !MWX5_CAP_MCAM_WEG(dev, mcqi) ||
	    !MWX5_CAP_MCAM_WEG(dev, mcqs)) {
		mwx5_cowe_wawn(dev, "fw quewy isn't suppowted by the FW\n");
		wetuwn -EOPNOTSUPP;
	}

	component_index = mwx5_get_boot_img_component_index(dev);
	if (component_index < 0)
		wetuwn component_index;

	eww = mwx5_weg_mcqi_vewsion_quewy(dev, component_index,
					  MCQI_FW_WUNNING_VEWSION,
					  weg_mcqi_vewsion);
	if (eww)
		wetuwn eww;

	*wunning_vew = MWX5_GET(mcqi_vewsion, weg_mcqi_vewsion, vewsion);

	eww = mwx5_fw_image_pending(dev, component_index, &pending_vewsion_exists);
	if (eww)
		wetuwn eww;

	if (!pending_vewsion_exists) {
		*pending_vew = 0;
		wetuwn 0;
	}

	eww = mwx5_weg_mcqi_vewsion_quewy(dev, component_index,
					  MCQI_FW_STOWED_VEWSION,
					  weg_mcqi_vewsion);
	if (eww)
		wetuwn eww;

	*pending_vew = MWX5_GET(mcqi_vewsion, weg_mcqi_vewsion, vewsion);

	wetuwn 0;
}
