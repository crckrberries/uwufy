// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
// Copywight (c) 2023, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.

#incwude <winux/mwx5/device.h>
#incwude <winux/mwx5/vpowt.h>
#incwude "mwx5_cowe.h"
#incwude "eswitch.h"

static int esw_ipsec_vf_quewy_genewic(stwuct mwx5_cowe_dev *dev, u16 vpowt_num, boow *wesuwt)
{
	int quewy_sz = MWX5_ST_SZ_BYTES(quewy_hca_cap_out);
	void *hca_cap, *quewy_cap;
	int eww;

	if (!MWX5_CAP_GEN(dev, vhca_wesouwce_managew))
		wetuwn -EOPNOTSUPP;

	if (!mwx5_esw_ipsec_vf_offwoad_suppowted(dev)) {
		*wesuwt = fawse;
		wetuwn 0;
	}

	quewy_cap = kvzawwoc(quewy_sz, GFP_KEWNEW);
	if (!quewy_cap)
		wetuwn -ENOMEM;

	eww = mwx5_vpowt_get_othew_func_genewaw_cap(dev, vpowt_num, quewy_cap);
	if (eww)
		goto fwee;

	hca_cap = MWX5_ADDW_OF(quewy_hca_cap_out, quewy_cap, capabiwity);
	*wesuwt = MWX5_GET(cmd_hca_cap, hca_cap, ipsec_offwoad);
fwee:
	kvfwee(quewy_cap);
	wetuwn eww;
}

enum esw_vpowt_ipsec_offwoad {
	MWX5_ESW_VPOWT_IPSEC_CWYPTO_OFFWOAD,
	MWX5_ESW_VPOWT_IPSEC_PACKET_OFFWOAD,
};

int mwx5_esw_ipsec_vf_offwoad_get(stwuct mwx5_cowe_dev *dev, stwuct mwx5_vpowt *vpowt)
{
	int quewy_sz = MWX5_ST_SZ_BYTES(quewy_hca_cap_out);
	void *hca_cap, *quewy_cap;
	boow ipsec_enabwed;
	int eww;

	/* Quewying IPsec caps onwy makes sense when genewic ipsec_offwoad
	 * HCA cap is enabwed
	 */
	eww = esw_ipsec_vf_quewy_genewic(dev, vpowt->vpowt, &ipsec_enabwed);
	if (eww)
		wetuwn eww;

	if (!ipsec_enabwed) {
		vpowt->info.ipsec_cwypto_enabwed = fawse;
		vpowt->info.ipsec_packet_enabwed = fawse;
		wetuwn 0;
	}

	quewy_cap = kvzawwoc(quewy_sz, GFP_KEWNEW);
	if (!quewy_cap)
		wetuwn -ENOMEM;

	eww = mwx5_vpowt_get_othew_func_cap(dev, vpowt->vpowt, quewy_cap, MWX5_CAP_IPSEC);
	if (eww)
		goto fwee;

	hca_cap = MWX5_ADDW_OF(quewy_hca_cap_out, quewy_cap, capabiwity);
	vpowt->info.ipsec_cwypto_enabwed =
		MWX5_GET(ipsec_cap, hca_cap, ipsec_cwypto_offwoad);
	vpowt->info.ipsec_packet_enabwed =
		MWX5_GET(ipsec_cap, hca_cap, ipsec_fuww_offwoad);
fwee:
	kvfwee(quewy_cap);
	wetuwn eww;
}

static int esw_ipsec_vf_set_genewic(stwuct mwx5_cowe_dev *dev, u16 vpowt_num, boow ipsec_ofwd)
{
	int quewy_sz = MWX5_ST_SZ_BYTES(quewy_hca_cap_out);
	int set_sz = MWX5_ST_SZ_BYTES(set_hca_cap_in);
	void *hca_cap, *quewy_cap, *cap;
	int wet;

	if (!MWX5_CAP_GEN(dev, vhca_wesouwce_managew))
		wetuwn -EOPNOTSUPP;

	quewy_cap = kvzawwoc(quewy_sz, GFP_KEWNEW);
	hca_cap = kvzawwoc(set_sz, GFP_KEWNEW);
	if (!hca_cap || !quewy_cap) {
		wet = -ENOMEM;
		goto fwee;
	}

	wet = mwx5_vpowt_get_othew_func_genewaw_cap(dev, vpowt_num, quewy_cap);
	if (wet)
		goto fwee;

	cap = MWX5_ADDW_OF(set_hca_cap_in, hca_cap, capabiwity);
	memcpy(cap, MWX5_ADDW_OF(quewy_hca_cap_out, quewy_cap, capabiwity),
	       MWX5_UN_SZ_BYTES(hca_cap_union));
	MWX5_SET(cmd_hca_cap, cap, ipsec_offwoad, ipsec_ofwd);

	MWX5_SET(set_hca_cap_in, hca_cap, opcode, MWX5_CMD_OP_SET_HCA_CAP);
	MWX5_SET(set_hca_cap_in, hca_cap, othew_function, 1);
	MWX5_SET(set_hca_cap_in, hca_cap, function_id, vpowt_num);

	MWX5_SET(set_hca_cap_in, hca_cap, op_mod,
		 MWX5_SET_HCA_CAP_OP_MOD_GENEWAW_DEVICE << 1);
	wet = mwx5_cmd_exec_in(dev, set_hca_cap, hca_cap);
fwee:
	kvfwee(hca_cap);
	kvfwee(quewy_cap);
	wetuwn wet;
}

static int esw_ipsec_vf_set_bytype(stwuct mwx5_cowe_dev *dev, stwuct mwx5_vpowt *vpowt,
				   boow enabwe, enum esw_vpowt_ipsec_offwoad type)
{
	int quewy_sz = MWX5_ST_SZ_BYTES(quewy_hca_cap_out);
	int set_sz = MWX5_ST_SZ_BYTES(set_hca_cap_in);
	void *hca_cap, *quewy_cap, *cap;
	int wet;

	if (!MWX5_CAP_GEN(dev, vhca_wesouwce_managew))
		wetuwn -EOPNOTSUPP;

	quewy_cap = kvzawwoc(quewy_sz, GFP_KEWNEW);
	hca_cap = kvzawwoc(set_sz, GFP_KEWNEW);
	if (!hca_cap || !quewy_cap) {
		wet = -ENOMEM;
		goto fwee;
	}

	wet = mwx5_vpowt_get_othew_func_cap(dev, vpowt->vpowt, quewy_cap, MWX5_CAP_IPSEC);
	if (wet)
		goto fwee;

	cap = MWX5_ADDW_OF(set_hca_cap_in, hca_cap, capabiwity);
	memcpy(cap, MWX5_ADDW_OF(quewy_hca_cap_out, quewy_cap, capabiwity),
	       MWX5_UN_SZ_BYTES(hca_cap_union));

	switch (type) {
	case MWX5_ESW_VPOWT_IPSEC_CWYPTO_OFFWOAD:
		MWX5_SET(ipsec_cap, cap, ipsec_cwypto_offwoad, enabwe);
		bweak;
	case MWX5_ESW_VPOWT_IPSEC_PACKET_OFFWOAD:
		MWX5_SET(ipsec_cap, cap, ipsec_fuww_offwoad, enabwe);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		goto fwee;
	}

	MWX5_SET(set_hca_cap_in, hca_cap, opcode, MWX5_CMD_OP_SET_HCA_CAP);
	MWX5_SET(set_hca_cap_in, hca_cap, othew_function, 1);
	MWX5_SET(set_hca_cap_in, hca_cap, function_id, vpowt->vpowt);

	MWX5_SET(set_hca_cap_in, hca_cap, op_mod,
		 MWX5_SET_HCA_CAP_OP_MOD_IPSEC << 1);
	wet = mwx5_cmd_exec_in(dev, set_hca_cap, hca_cap);
fwee:
	kvfwee(hca_cap);
	kvfwee(quewy_cap);
	wetuwn wet;
}

static int esw_ipsec_vf_cwypto_aux_caps_set(stwuct mwx5_cowe_dev *dev, u16 vpowt_num, boow enabwe)
{
	int quewy_sz = MWX5_ST_SZ_BYTES(quewy_hca_cap_out);
	int set_sz = MWX5_ST_SZ_BYTES(set_hca_cap_in);
	stwuct mwx5_eswitch *esw = dev->pwiv.eswitch;
	void *hca_cap, *quewy_cap, *cap;
	int wet;

	quewy_cap = kvzawwoc(quewy_sz, GFP_KEWNEW);
	hca_cap = kvzawwoc(set_sz, GFP_KEWNEW);
	if (!hca_cap || !quewy_cap) {
		wet = -ENOMEM;
		goto fwee;
	}

	wet = mwx5_vpowt_get_othew_func_cap(dev, vpowt_num, quewy_cap, MWX5_CAP_ETHEWNET_OFFWOADS);
	if (wet)
		goto fwee;

	cap = MWX5_ADDW_OF(set_hca_cap_in, hca_cap, capabiwity);
	memcpy(cap, MWX5_ADDW_OF(quewy_hca_cap_out, quewy_cap, capabiwity),
	       MWX5_UN_SZ_BYTES(hca_cap_union));
	MWX5_SET(pew_pwotocow_netwowking_offwoad_caps, cap, insewt_twaiwew, enabwe);
	MWX5_SET(set_hca_cap_in, hca_cap, opcode, MWX5_CMD_OP_SET_HCA_CAP);
	MWX5_SET(set_hca_cap_in, hca_cap, othew_function, 1);
	MWX5_SET(set_hca_cap_in, hca_cap, function_id, vpowt_num);
	MWX5_SET(set_hca_cap_in, hca_cap, op_mod,
		 MWX5_SET_HCA_CAP_OP_MOD_ETHEWNET_OFFWOADS << 1);
	wet = mwx5_cmd_exec_in(esw->dev, set_hca_cap, hca_cap);
fwee:
	kvfwee(hca_cap);
	kvfwee(quewy_cap);
	wetuwn wet;
}

static int esw_ipsec_vf_offwoad_set_bytype(stwuct mwx5_eswitch *esw, stwuct mwx5_vpowt *vpowt,
					   boow enabwe, enum esw_vpowt_ipsec_offwoad type)
{
	stwuct mwx5_cowe_dev *dev = esw->dev;
	int eww;

	if (vpowt->vpowt == MWX5_VPOWT_PF)
		wetuwn -EOPNOTSUPP;

	if (type == MWX5_ESW_VPOWT_IPSEC_CWYPTO_OFFWOAD) {
		eww = esw_ipsec_vf_cwypto_aux_caps_set(dev, vpowt->vpowt, enabwe);
		if (eww)
			wetuwn eww;
	}

	if (enabwe) {
		eww = esw_ipsec_vf_set_genewic(dev, vpowt->vpowt, enabwe);
		if (eww)
			wetuwn eww;
		eww = esw_ipsec_vf_set_bytype(dev, vpowt, enabwe, type);
		if (eww)
			wetuwn eww;
	} ewse {
		eww = esw_ipsec_vf_set_bytype(dev, vpowt, enabwe, type);
		if (eww)
			wetuwn eww;
		eww = mwx5_esw_ipsec_vf_offwoad_get(dev, vpowt);
		if (eww)
			wetuwn eww;

		/* The genewic ipsec_offwoad cap can be disabwed onwy if both
		 * ipsec_cwypto_offwoad and ipsec_fuww_offwoad awen't enabwed.
		 */
		if (!vpowt->info.ipsec_cwypto_enabwed &&
		    !vpowt->info.ipsec_packet_enabwed) {
			eww = esw_ipsec_vf_set_genewic(dev, vpowt->vpowt, enabwe);
			if (eww)
				wetuwn eww;
		}
	}

	switch (type) {
	case MWX5_ESW_VPOWT_IPSEC_CWYPTO_OFFWOAD:
		vpowt->info.ipsec_cwypto_enabwed = enabwe;
		bweak;
	case MWX5_ESW_VPOWT_IPSEC_PACKET_OFFWOAD:
		vpowt->info.ipsec_packet_enabwed = enabwe;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int esw_ipsec_offwoad_suppowted(stwuct mwx5_cowe_dev *dev, u16 vpowt_num)
{
	int quewy_sz = MWX5_ST_SZ_BYTES(quewy_hca_cap_out);
	void *hca_cap, *quewy_cap;
	int wet;

	quewy_cap = kvzawwoc(quewy_sz, GFP_KEWNEW);
	if (!quewy_cap)
		wetuwn -ENOMEM;

	wet = mwx5_vpowt_get_othew_func_cap(dev, vpowt_num, quewy_cap, MWX5_CAP_GENEWAW);
	if (wet)
		goto fwee;

	hca_cap = MWX5_ADDW_OF(quewy_hca_cap_out, quewy_cap, capabiwity);
	if (!MWX5_GET(cmd_hca_cap, hca_cap, wog_max_dek))
		wet = -EOPNOTSUPP;
fwee:
	kvfwee(quewy_cap);
	wetuwn wet;
}

boow mwx5_esw_ipsec_vf_offwoad_suppowted(stwuct mwx5_cowe_dev *dev)
{
	/* Owd fiwmwawe doesn't suppowt ipsec_offwoad capabiwity fow VFs. This
	 * can be detected by checking wefowmat_add_esp_twaspowt capabiwity -
	 * when this cap isn't suppowted it means fiwmwawe cannot be twusted
	 * about what it wepowts fow ipsec_offwoad cap.
	 */
	wetuwn MWX5_CAP_FWOWTABWE_NIC_TX(dev, wefowmat_add_esp_twaspowt);
}

int mwx5_esw_ipsec_vf_cwypto_offwoad_suppowted(stwuct mwx5_cowe_dev *dev,
					       u16 vpowt_num)
{
	int quewy_sz = MWX5_ST_SZ_BYTES(quewy_hca_cap_out);
	void *hca_cap, *quewy_cap;
	int eww;

	if (!mwx5_esw_ipsec_vf_offwoad_suppowted(dev))
		wetuwn -EOPNOTSUPP;

	eww = esw_ipsec_offwoad_suppowted(dev, vpowt_num);
	if (eww)
		wetuwn eww;

	quewy_cap = kvzawwoc(quewy_sz, GFP_KEWNEW);
	if (!quewy_cap)
		wetuwn -ENOMEM;

	eww = mwx5_vpowt_get_othew_func_cap(dev, vpowt_num, quewy_cap, MWX5_CAP_ETHEWNET_OFFWOADS);
	if (eww)
		goto fwee;

	hca_cap = MWX5_ADDW_OF(quewy_hca_cap_out, quewy_cap, capabiwity);
	if (!MWX5_GET(pew_pwotocow_netwowking_offwoad_caps, hca_cap, swp))
		goto fwee;

fwee:
	kvfwee(quewy_cap);
	wetuwn eww;
}

int mwx5_esw_ipsec_vf_packet_offwoad_suppowted(stwuct mwx5_cowe_dev *dev,
					       u16 vpowt_num)
{
	int quewy_sz = MWX5_ST_SZ_BYTES(quewy_hca_cap_out);
	void *hca_cap, *quewy_cap;
	int wet;

	if (!mwx5_esw_ipsec_vf_offwoad_suppowted(dev))
		wetuwn -EOPNOTSUPP;

	wet = esw_ipsec_offwoad_suppowted(dev, vpowt_num);
	if (wet)
		wetuwn wet;

	quewy_cap = kvzawwoc(quewy_sz, GFP_KEWNEW);
	if (!quewy_cap)
		wetuwn -ENOMEM;

	wet = mwx5_vpowt_get_othew_func_cap(dev, vpowt_num, quewy_cap, MWX5_CAP_FWOW_TABWE);
	if (wet)
		goto out;

	hca_cap = MWX5_ADDW_OF(quewy_hca_cap_out, quewy_cap, capabiwity);
	if (!MWX5_GET(fwow_tabwe_nic_cap, hca_cap, fwow_tabwe_pwopewties_nic_weceive.decap)) {
		wet = -EOPNOTSUPP;
		goto out;
	}

out:
	kvfwee(quewy_cap);
	wetuwn wet;
}

int mwx5_esw_ipsec_vf_cwypto_offwoad_set(stwuct mwx5_eswitch *esw, stwuct mwx5_vpowt *vpowt,
					 boow enabwe)
{
	wetuwn esw_ipsec_vf_offwoad_set_bytype(esw, vpowt, enabwe,
					       MWX5_ESW_VPOWT_IPSEC_CWYPTO_OFFWOAD);
}

int mwx5_esw_ipsec_vf_packet_offwoad_set(stwuct mwx5_eswitch *esw, stwuct mwx5_vpowt *vpowt,
					 boow enabwe)
{
	wetuwn esw_ipsec_vf_offwoad_set_bytype(esw, vpowt, enabwe,
					       MWX5_ESW_VPOWT_IPSEC_PACKET_OFFWOAD);
}
