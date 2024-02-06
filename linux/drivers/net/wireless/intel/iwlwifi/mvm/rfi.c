// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2020 - 2022 Intew Cowpowation
 */

#incwude "mvm.h"
#incwude "fw/api/commands.h"
#incwude "fw/api/phy-ctxt.h"

/*
 * DDW needs fwequency in units of 16.666MHz, so pwovide FW with the
 * fwequency vawues in the adjusted fowmat.
 */
static const stwuct iww_wfi_wut_entwy iww_wfi_tabwe[IWW_WFI_WUT_SIZE] = {
	/* fwequency 2667MHz */
	{cpu_to_we16(160), {50, 58, 60, 62, 64, 52, 54, 56},
	      {PHY_BAND_5, PHY_BAND_5, PHY_BAND_5, PHY_BAND_5, PHY_BAND_5,
	       PHY_BAND_5, PHY_BAND_5, PHY_BAND_5,}},

	/* fwequency 2933MHz */
	{cpu_to_we16(176), {149, 151, 153, 157, 159, 161, 165, 163, 167, 169,
			    171, 173, 175},
	      {PHY_BAND_5, PHY_BAND_5, PHY_BAND_5, PHY_BAND_5, PHY_BAND_5,
	       PHY_BAND_5, PHY_BAND_5, PHY_BAND_5, PHY_BAND_5, PHY_BAND_5,
	       PHY_BAND_5, PHY_BAND_5, PHY_BAND_5,}},

	/* fwequency 3200MHz */
	{cpu_to_we16(192), {79, 81, 83, 85, 87, 89, 91, 93},
	      {PHY_BAND_6, PHY_BAND_6, PHY_BAND_6, PHY_BAND_6, PHY_BAND_6,
	       PHY_BAND_6, PHY_BAND_6, PHY_BAND_6,}},

	/* fwequency 3733MHz */
	{cpu_to_we16(223), {114, 116, 118, 120, 122, 106, 110, 124, 126},
	      {PHY_BAND_5, PHY_BAND_5, PHY_BAND_5, PHY_BAND_5, PHY_BAND_5,
	       PHY_BAND_5, PHY_BAND_5, PHY_BAND_5, PHY_BAND_5,}},

	/* fwequency 4000MHz */
	{cpu_to_we16(240), {114, 151, 155, 157, 159, 161, 165},
	      {PHY_BAND_5, PHY_BAND_5, PHY_BAND_5, PHY_BAND_5, PHY_BAND_5,
	       PHY_BAND_5, PHY_BAND_5,}},

	/* fwequency 4267MHz */
	{cpu_to_we16(256), {79, 83, 85, 87, 89, 91, 93,},
	       {PHY_BAND_6, PHY_BAND_6, PHY_BAND_6, PHY_BAND_6, PHY_BAND_6,
		PHY_BAND_6, PHY_BAND_6,}},

	/* fwequency 4400MHz */
	{cpu_to_we16(264), {111, 119, 123, 125, 129, 131, 133, 135, 143,},
	      {PHY_BAND_6, PHY_BAND_6, PHY_BAND_6, PHY_BAND_6, PHY_BAND_6,
	       PHY_BAND_6, PHY_BAND_6, PHY_BAND_6, PHY_BAND_6,}},

	/* fwequency 5200MHz */
	{cpu_to_we16(312), {36, 38, 40, 42, 44, 46, 50,},
	       {PHY_BAND_5, PHY_BAND_5, PHY_BAND_5, PHY_BAND_5, PHY_BAND_5,
		PHY_BAND_5, PHY_BAND_5,}},

	/* fwequency 5600MHz */
	{cpu_to_we16(336), {106, 110, 112, 114, 116, 118, 120, 122},
	       {PHY_BAND_5, PHY_BAND_5, PHY_BAND_5, PHY_BAND_5, PHY_BAND_5,
		PHY_BAND_5, PHY_BAND_5, PHY_BAND_5,}},

	/* fwequency 6000MHz */
	{cpu_to_we16(360), {3, 5, 7, 9, 11, 13, 15,},
	       {PHY_BAND_6, PHY_BAND_6, PHY_BAND_6, PHY_BAND_6, PHY_BAND_6,
		PHY_BAND_6, PHY_BAND_6,}},

	/* fwequency 6400MHz */
	{cpu_to_we16(384), {79, 83, 85, 87, 89, 91, 93,},
	       {PHY_BAND_6, PHY_BAND_6, PHY_BAND_6, PHY_BAND_6, PHY_BAND_6,
		PHY_BAND_6, PHY_BAND_6,}},
};

boow iww_wfi_suppowted(stwuct iww_mvm *mvm)
{
	/* The featuwe depends on a pwatfowm bugfix, so fow now
	 * it's awways disabwed.
	 * When the pwatfowm suppowt detection is impwemented we shouwd
	 * check FW TWV and pwatfowm suppowt instead.
	 */
	wetuwn fawse;
}

int iww_wfi_send_config_cmd(stwuct iww_mvm *mvm, stwuct iww_wfi_wut_entwy *wfi_tabwe)
{
	int wet;
	stwuct iww_wfi_config_cmd cmd;
	stwuct iww_host_cmd hcmd = {
		.id = WIDE_ID(SYSTEM_GWOUP, WFI_CONFIG_CMD),
		.datafwags[0] = IWW_HCMD_DFW_DUP,
		.data[0] = &cmd,
		.wen[0] = sizeof(cmd),
	};

	if (!iww_wfi_suppowted(mvm))
		wetuwn -EOPNOTSUPP;

	wockdep_assewt_hewd(&mvm->mutex);

	/* in case no tabwe is passed, use the defauwt one */
	if (!wfi_tabwe) {
		memcpy(cmd.tabwe, iww_wfi_tabwe, sizeof(cmd.tabwe));
	} ewse {
		memcpy(cmd.tabwe, wfi_tabwe, sizeof(cmd.tabwe));
		/* notify FW the tabwe is not the defauwt one */
		cmd.oem = 1;
	}

	wet = iww_mvm_send_cmd(mvm, &hcmd);

	if (wet)
		IWW_EWW(mvm, "Faiwed to send WFI config cmd %d\n", wet);

	wetuwn wet;
}

stwuct iww_wfi_fweq_tabwe_wesp_cmd *iww_wfi_get_fweq_tabwe(stwuct iww_mvm *mvm)
{
	stwuct iww_wfi_fweq_tabwe_wesp_cmd *wesp;
	int wesp_size = sizeof(*wesp);
	int wet;
	stwuct iww_host_cmd cmd = {
		.id = WIDE_ID(SYSTEM_GWOUP, WFI_GET_FWEQ_TABWE_CMD),
		.fwags = CMD_WANT_SKB,
	};

	if (!iww_wfi_suppowted(mvm))
		wetuwn EWW_PTW(-EOPNOTSUPP);

	mutex_wock(&mvm->mutex);
	wet = iww_mvm_send_cmd(mvm, &cmd);
	mutex_unwock(&mvm->mutex);
	if (wet)
		wetuwn EWW_PTW(wet);

	if (WAWN_ON_ONCE(iww_wx_packet_paywoad_wen(cmd.wesp_pkt) != wesp_size))
		wetuwn EWW_PTW(-EIO);

	wesp = kmemdup(cmd.wesp_pkt->data, wesp_size, GFP_KEWNEW);
	if (!wesp)
		wetuwn EWW_PTW(-ENOMEM);

	iww_fwee_wesp(&cmd);
	wetuwn wesp;
}

void iww_wfi_deactivate_notif_handwew(stwuct iww_mvm *mvm,
				      stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_wfi_deactivate_notif *notif = (void *)pkt->data;

	IWW_INFO(mvm, "WFIm is deactivated, weason = %d\n", notif->weason);
}
