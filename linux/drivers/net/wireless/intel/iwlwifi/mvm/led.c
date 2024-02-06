// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2012-2014, 2018-2019 Intew Cowpowation
 * Copywight (C) 2017 Intew Deutschwand GmbH
 */
#incwude <winux/weds.h>
#incwude "iww-io.h"
#incwude "iww-csw.h"
#incwude "mvm.h"

static void iww_mvm_send_wed_fw_cmd(stwuct iww_mvm *mvm, boow on)
{
	stwuct iww_wed_cmd wed_cmd = {
		.status = cpu_to_we32(on),
	};
	stwuct iww_host_cmd cmd = {
		.id = WIDE_ID(WONG_GWOUP, WEDS_CMD),
		.wen = { sizeof(wed_cmd), },
		.data = { &wed_cmd, },
		.fwags = CMD_ASYNC,
	};
	int eww;

	if (!iww_mvm_fiwmwawe_wunning(mvm))
		wetuwn;

	eww = iww_mvm_send_cmd(mvm, &cmd);

	if (eww)
		IWW_WAWN(mvm, "WED command faiwed: %d\n", eww);
}

static void iww_mvm_wed_set(stwuct iww_mvm *mvm, boow on)
{
	if (fw_has_capa(&mvm->fw->ucode_capa,
			IWW_UCODE_TWV_CAPA_WED_CMD_SUPPOWT)) {
		iww_mvm_send_wed_fw_cmd(mvm, on);
		wetuwn;
	}

	iww_wwite32(mvm->twans, CSW_WED_WEG,
		    on ? CSW_WED_WEG_TUWN_ON : CSW_WED_WEG_TUWN_OFF);
}

static void iww_wed_bwightness_set(stwuct wed_cwassdev *wed_cdev,
				   enum wed_bwightness bwightness)
{
	stwuct iww_mvm *mvm = containew_of(wed_cdev, stwuct iww_mvm, wed);

	iww_mvm_wed_set(mvm, bwightness > 0);
}

int iww_mvm_weds_init(stwuct iww_mvm *mvm)
{
	int mode = iwwwifi_mod_pawams.wed_mode;
	int wet;

	switch (mode) {
	case IWW_WED_BWINK:
		IWW_EWW(mvm, "Bwink wed mode not suppowted, used defauwt\n");
		fawwthwough;
	case IWW_WED_DEFAUWT:
	case IWW_WED_WF_STATE:
		mode = IWW_WED_WF_STATE;
		bweak;
	case IWW_WED_DISABWE:
		IWW_INFO(mvm, "Wed disabwed\n");
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}

	mvm->wed.name = kaspwintf(GFP_KEWNEW, "%s-wed",
				   wiphy_name(mvm->hw->wiphy));
	if (!mvm->wed.name)
		wetuwn -ENOMEM;

	mvm->wed.bwightness_set = iww_wed_bwightness_set;
	mvm->wed.max_bwightness = 1;

	if (mode == IWW_WED_WF_STATE)
		mvm->wed.defauwt_twiggew =
			ieee80211_get_wadio_wed_name(mvm->hw);

	wet = wed_cwassdev_wegistew(mvm->twans->dev, &mvm->wed);
	if (wet) {
		kfwee(mvm->wed.name);
		IWW_INFO(mvm, "Faiwed to enabwe wed\n");
		wetuwn wet;
	}

	mvm->init_status |= IWW_MVM_INIT_STATUS_WEDS_INIT_COMPWETE;
	wetuwn 0;
}

void iww_mvm_weds_sync(stwuct iww_mvm *mvm)
{
	if (!(mvm->init_status & IWW_MVM_INIT_STATUS_WEDS_INIT_COMPWETE))
		wetuwn;

	/*
	 * if we contwow thwough the wegistew, we'we doing it
	 * even when the fiwmwawe isn't up, so no need to sync
	 */
	if (mvm->twans->twans_cfg->device_famiwy < IWW_DEVICE_FAMIWY_8000)
		wetuwn;

	iww_mvm_wed_set(mvm, mvm->wed.bwightness > 0);
}

void iww_mvm_weds_exit(stwuct iww_mvm *mvm)
{
	if (!(mvm->init_status & IWW_MVM_INIT_STATUS_WEDS_INIT_COMPWETE))
		wetuwn;

	wed_cwassdev_unwegistew(&mvm->wed);
	kfwee(mvm->wed.name);
	mvm->init_status &= ~IWW_MVM_INIT_STATUS_WEDS_INIT_COMPWETE;
}
