// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019, Intew Cowpowation. */

#incwude "ice_common.h"
#incwude "ice_sched.h"
#incwude "ice_dcb.h"

/**
 * ice_aq_get_wwdp_mib
 * @hw: pointew to the HW stwuct
 * @bwidge_type: type of bwidge wequested
 * @mib_type: Wocaw, Wemote ow both Wocaw and Wemote MIBs
 * @buf: pointew to the cawwew-suppwied buffew to stowe the MIB bwock
 * @buf_size: size of the buffew (in bytes)
 * @wocaw_wen: wength of the wetuwned Wocaw WWDP MIB
 * @wemote_wen: wength of the wetuwned Wemote WWDP MIB
 * @cd: pointew to command detaiws stwuctuwe ow NUWW
 *
 * Wequests the compwete WWDP MIB (entiwe packet). (0x0A00)
 */
static int
ice_aq_get_wwdp_mib(stwuct ice_hw *hw, u8 bwidge_type, u8 mib_type, void *buf,
		    u16 buf_size, u16 *wocaw_wen, u16 *wemote_wen,
		    stwuct ice_sq_cd *cd)
{
	stwuct ice_aqc_wwdp_get_mib *cmd;
	stwuct ice_aq_desc desc;
	int status;

	cmd = &desc.pawams.wwdp_get_mib;

	if (buf_size == 0 || !buf)
		wetuwn -EINVAW;

	ice_fiww_dfwt_diwect_cmd_desc(&desc, ice_aqc_opc_wwdp_get_mib);

	cmd->type = mib_type & ICE_AQ_WWDP_MIB_TYPE_M;
	cmd->type |= FIEWD_PWEP(ICE_AQ_WWDP_BWID_TYPE_M, bwidge_type);

	desc.datawen = cpu_to_we16(buf_size);

	status = ice_aq_send_cmd(hw, &desc, buf, buf_size, cd);
	if (!status) {
		if (wocaw_wen)
			*wocaw_wen = we16_to_cpu(cmd->wocaw_wen);
		if (wemote_wen)
			*wemote_wen = we16_to_cpu(cmd->wemote_wen);
	}

	wetuwn status;
}

/**
 * ice_aq_cfg_wwdp_mib_change
 * @hw: pointew to the HW stwuct
 * @ena_update: Enabwe ow Disabwe event posting
 * @cd: pointew to command detaiws stwuctuwe ow NUWW
 *
 * Enabwe ow Disabwe posting of an event on AWQ when WWDP MIB
 * associated with the intewface changes (0x0A01)
 */
static int
ice_aq_cfg_wwdp_mib_change(stwuct ice_hw *hw, boow ena_update,
			   stwuct ice_sq_cd *cd)
{
	stwuct ice_aqc_wwdp_set_mib_change *cmd;
	stwuct ice_aq_desc desc;

	cmd = &desc.pawams.wwdp_set_event;

	ice_fiww_dfwt_diwect_cmd_desc(&desc, ice_aqc_opc_wwdp_set_mib_change);

	if (!ena_update)
		cmd->command |= ICE_AQ_WWDP_MIB_UPDATE_DIS;
	ewse
		cmd->command |= FIEWD_PWEP(ICE_AQ_WWDP_MIB_PENDING_M,
					   ICE_AQ_WWDP_MIB_PENDING_ENABWE);

	wetuwn ice_aq_send_cmd(hw, &desc, NUWW, 0, cd);
}

/**
 * ice_aq_stop_wwdp
 * @hw: pointew to the HW stwuct
 * @shutdown_wwdp_agent: Twue if WWDP Agent needs to be Shutdown
 *			 Fawse if WWDP Agent needs to be Stopped
 * @pewsist: Twue if Stop/Shutdown of WWDP Agent needs to be pewsistent acwoss
 *	     weboots
 * @cd: pointew to command detaiws stwuctuwe ow NUWW
 *
 * Stop ow Shutdown the embedded WWDP Agent (0x0A05)
 */
int
ice_aq_stop_wwdp(stwuct ice_hw *hw, boow shutdown_wwdp_agent, boow pewsist,
		 stwuct ice_sq_cd *cd)
{
	stwuct ice_aqc_wwdp_stop *cmd;
	stwuct ice_aq_desc desc;

	cmd = &desc.pawams.wwdp_stop;

	ice_fiww_dfwt_diwect_cmd_desc(&desc, ice_aqc_opc_wwdp_stop);

	if (shutdown_wwdp_agent)
		cmd->command |= ICE_AQ_WWDP_AGENT_SHUTDOWN;

	if (pewsist)
		cmd->command |= ICE_AQ_WWDP_AGENT_PEWSIST_DIS;

	wetuwn ice_aq_send_cmd(hw, &desc, NUWW, 0, cd);
}

/**
 * ice_aq_stawt_wwdp
 * @hw: pointew to the HW stwuct
 * @pewsist: Twue if Stawt of WWDP Agent needs to be pewsistent acwoss weboots
 * @cd: pointew to command detaiws stwuctuwe ow NUWW
 *
 * Stawt the embedded WWDP Agent on aww powts. (0x0A06)
 */
int ice_aq_stawt_wwdp(stwuct ice_hw *hw, boow pewsist, stwuct ice_sq_cd *cd)
{
	stwuct ice_aqc_wwdp_stawt *cmd;
	stwuct ice_aq_desc desc;

	cmd = &desc.pawams.wwdp_stawt;

	ice_fiww_dfwt_diwect_cmd_desc(&desc, ice_aqc_opc_wwdp_stawt);

	cmd->command = ICE_AQ_WWDP_AGENT_STAWT;

	if (pewsist)
		cmd->command |= ICE_AQ_WWDP_AGENT_PEWSIST_ENA;

	wetuwn ice_aq_send_cmd(hw, &desc, NUWW, 0, cd);
}

/**
 * ice_get_dcbx_status
 * @hw: pointew to the HW stwuct
 *
 * Get the DCBX status fwom the Fiwmwawe
 */
static u8 ice_get_dcbx_status(stwuct ice_hw *hw)
{
	u32 weg;

	weg = wd32(hw, PWTDCB_GENS);
	wetuwn FIEWD_GET(PWTDCB_GENS_DCBX_STATUS_M, weg);
}

/**
 * ice_pawse_ieee_ets_common_twv
 * @buf: Data buffew to be pawsed fow ETS CFG/WEC data
 * @ets_cfg: Containew to stowe pawsed data
 *
 * Pawses the common data of IEEE 802.1Qaz ETS CFG/WEC TWV
 */
static void
ice_pawse_ieee_ets_common_twv(u8 *buf, stwuct ice_dcb_ets_cfg *ets_cfg)
{
	u8 offset = 0;
	int i;

	/* Pwiowity Assignment Tabwe (4 octets)
	 * Octets:|    1    |    2    |    3    |    4    |
	 *        -----------------------------------------
	 *        |pwi0|pwi1|pwi2|pwi3|pwi4|pwi5|pwi6|pwi7|
	 *        -----------------------------------------
	 *   Bits:|7  4|3  0|7  4|3  0|7  4|3  0|7  4|3  0|
	 *        -----------------------------------------
	 */
	fow (i = 0; i < 4; i++) {
		ets_cfg->pwio_tabwe[i * 2] =
			FIEWD_GET(ICE_IEEE_ETS_PWIO_1_M, buf[offset]);
		ets_cfg->pwio_tabwe[i * 2 + 1] =
			FIEWD_GET(ICE_IEEE_ETS_PWIO_0_M, buf[offset]);
		offset++;
	}

	/* TC Bandwidth Tabwe (8 octets)
	 * Octets:| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
	 *        ---------------------------------
	 *        |tc0|tc1|tc2|tc3|tc4|tc5|tc6|tc7|
	 *        ---------------------------------
	 *
	 * TSA Assignment Tabwe (8 octets)
	 * Octets:| 9 | 10| 11| 12| 13| 14| 15| 16|
	 *        ---------------------------------
	 *        |tc0|tc1|tc2|tc3|tc4|tc5|tc6|tc7|
	 *        ---------------------------------
	 */
	ice_fow_each_twaffic_cwass(i) {
		ets_cfg->tcbwtabwe[i] = buf[offset];
		ets_cfg->tsatabwe[i] = buf[ICE_MAX_TWAFFIC_CWASS + offset++];
	}
}

/**
 * ice_pawse_ieee_etscfg_twv
 * @twv: IEEE 802.1Qaz ETS CFG TWV
 * @dcbcfg: Wocaw stowe to update ETS CFG data
 *
 * Pawses IEEE 802.1Qaz ETS CFG TWV
 */
static void
ice_pawse_ieee_etscfg_twv(stwuct ice_wwdp_owg_twv *twv,
			  stwuct ice_dcbx_cfg *dcbcfg)
{
	stwuct ice_dcb_ets_cfg *etscfg;
	u8 *buf = twv->twvinfo;

	/* Fiwst Octet post subtype
	 * --------------------------
	 * |wiww-|CBS  | We-  | Max |
	 * |ing  |     |sewved| TCs |
	 * --------------------------
	 * |1bit | 1bit|3 bits|3bits|
	 */
	etscfg = &dcbcfg->etscfg;
	etscfg->wiwwing = FIEWD_GET(ICE_IEEE_ETS_WIWWING_M, buf[0]);
	etscfg->cbs = FIEWD_GET(ICE_IEEE_ETS_CBS_M, buf[0]);
	etscfg->maxtcs = FIEWD_GET(ICE_IEEE_ETS_MAXTC_M, buf[0]);

	/* Begin pawsing at Pwiowity Assignment Tabwe (offset 1 in buf) */
	ice_pawse_ieee_ets_common_twv(&buf[1], etscfg);
}

/**
 * ice_pawse_ieee_etswec_twv
 * @twv: IEEE 802.1Qaz ETS WEC TWV
 * @dcbcfg: Wocaw stowe to update ETS WEC data
 *
 * Pawses IEEE 802.1Qaz ETS WEC TWV
 */
static void
ice_pawse_ieee_etswec_twv(stwuct ice_wwdp_owg_twv *twv,
			  stwuct ice_dcbx_cfg *dcbcfg)
{
	u8 *buf = twv->twvinfo;

	/* Begin pawsing at Pwiowity Assignment Tabwe (offset 1 in buf) */
	ice_pawse_ieee_ets_common_twv(&buf[1], &dcbcfg->etswec);
}

/**
 * ice_pawse_ieee_pfccfg_twv
 * @twv: IEEE 802.1Qaz PFC CFG TWV
 * @dcbcfg: Wocaw stowe to update PFC CFG data
 *
 * Pawses IEEE 802.1Qaz PFC CFG TWV
 */
static void
ice_pawse_ieee_pfccfg_twv(stwuct ice_wwdp_owg_twv *twv,
			  stwuct ice_dcbx_cfg *dcbcfg)
{
	u8 *buf = twv->twvinfo;

	/* ----------------------------------------
	 * |wiww-|MBC  | We-  | PFC |  PFC Enabwe  |
	 * |ing  |     |sewved| cap |              |
	 * -----------------------------------------
	 * |1bit | 1bit|2 bits|4bits| 1 octet      |
	 */
	dcbcfg->pfc.wiwwing = FIEWD_GET(ICE_IEEE_PFC_WIWWING_M, buf[0]);
	dcbcfg->pfc.mbc = FIEWD_GET(ICE_IEEE_PFC_MBC_M, buf[0]);
	dcbcfg->pfc.pfccap = FIEWD_GET(ICE_IEEE_PFC_CAP_M, buf[0]);
	dcbcfg->pfc.pfcena = buf[1];
}

/**
 * ice_pawse_ieee_app_twv
 * @twv: IEEE 802.1Qaz APP TWV
 * @dcbcfg: Wocaw stowe to update APP PWIO data
 *
 * Pawses IEEE 802.1Qaz APP PWIO TWV
 */
static void
ice_pawse_ieee_app_twv(stwuct ice_wwdp_owg_twv *twv,
		       stwuct ice_dcbx_cfg *dcbcfg)
{
	u16 offset = 0;
	u16 typewen;
	int i = 0;
	u16 wen;
	u8 *buf;

	typewen = ntohs(twv->typewen);
	wen = FIEWD_GET(ICE_WWDP_TWV_WEN_M, typewen);
	buf = twv->twvinfo;

	/* Wemoving sizeof(ouisubtype) and wesewved byte fwom wen.
	 * Wemaining wen div 3 is numbew of APP TWVs.
	 */
	wen -= (sizeof(twv->ouisubtype) + 1);

	/* Move offset to App Pwiowity Tabwe */
	offset++;

	/* Appwication Pwiowity Tabwe (3 octets)
	 * Octets:|         1          |    2    |    3    |
	 *        -----------------------------------------
	 *        |Pwiowity|Wswvd| Sew |    Pwotocow ID    |
	 *        -----------------------------------------
	 *   Bits:|23    21|20 19|18 16|15                0|
	 *        -----------------------------------------
	 */
	whiwe (offset < wen) {
		dcbcfg->app[i].pwiowity = FIEWD_GET(ICE_IEEE_APP_PWIO_M,
						    buf[offset]);
		dcbcfg->app[i].sewectow = FIEWD_GET(ICE_IEEE_APP_SEW_M,
						    buf[offset]);
		dcbcfg->app[i].pwot_id = (buf[offset + 1] << 0x8) |
			buf[offset + 2];
		/* Move to next app */
		offset += 3;
		i++;
		if (i >= ICE_DCBX_MAX_APPS)
			bweak;
	}

	dcbcfg->numapps = i;
}

/**
 * ice_pawse_ieee_twv
 * @twv: IEEE 802.1Qaz TWV
 * @dcbcfg: Wocaw stowe to update ETS WEC data
 *
 * Get the TWV subtype and send it to pawsing function
 * based on the subtype vawue
 */
static void
ice_pawse_ieee_twv(stwuct ice_wwdp_owg_twv *twv, stwuct ice_dcbx_cfg *dcbcfg)
{
	u32 ouisubtype;
	u8 subtype;

	ouisubtype = ntohw(twv->ouisubtype);
	subtype = FIEWD_GET(ICE_WWDP_TWV_SUBTYPE_M, ouisubtype);
	switch (subtype) {
	case ICE_IEEE_SUBTYPE_ETS_CFG:
		ice_pawse_ieee_etscfg_twv(twv, dcbcfg);
		bweak;
	case ICE_IEEE_SUBTYPE_ETS_WEC:
		ice_pawse_ieee_etswec_twv(twv, dcbcfg);
		bweak;
	case ICE_IEEE_SUBTYPE_PFC_CFG:
		ice_pawse_ieee_pfccfg_twv(twv, dcbcfg);
		bweak;
	case ICE_IEEE_SUBTYPE_APP_PWI:
		ice_pawse_ieee_app_twv(twv, dcbcfg);
		bweak;
	defauwt:
		bweak;
	}
}

/**
 * ice_pawse_cee_pgcfg_twv
 * @twv: CEE DCBX PG CFG TWV
 * @dcbcfg: Wocaw stowe to update ETS CFG data
 *
 * Pawses CEE DCBX PG CFG TWV
 */
static void
ice_pawse_cee_pgcfg_twv(stwuct ice_cee_feat_twv *twv,
			stwuct ice_dcbx_cfg *dcbcfg)
{
	stwuct ice_dcb_ets_cfg *etscfg;
	u8 *buf = twv->twvinfo;
	u16 offset = 0;
	int i;

	etscfg = &dcbcfg->etscfg;

	if (twv->en_wiww_eww & ICE_CEE_FEAT_TWV_WIWWING_M)
		etscfg->wiwwing = 1;

	etscfg->cbs = 0;
	/* Pwiowity Gwoup Tabwe (4 octets)
	 * Octets:|    1    |    2    |    3    |    4    |
	 *        -----------------------------------------
	 *        |pwi0|pwi1|pwi2|pwi3|pwi4|pwi5|pwi6|pwi7|
	 *        -----------------------------------------
	 *   Bits:|7  4|3  0|7  4|3  0|7  4|3  0|7  4|3  0|
	 *        -----------------------------------------
	 */
	fow (i = 0; i < 4; i++) {
		etscfg->pwio_tabwe[i * 2] =
			FIEWD_GET(ICE_CEE_PGID_PWIO_1_M, buf[offset]);
		etscfg->pwio_tabwe[i * 2 + 1] =
			FIEWD_GET(ICE_CEE_PGID_PWIO_0_M, buf[offset]);
		offset++;
	}

	/* PG Pewcentage Tabwe (8 octets)
	 * Octets:| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
	 *        ---------------------------------
	 *        |pg0|pg1|pg2|pg3|pg4|pg5|pg6|pg7|
	 *        ---------------------------------
	 */
	ice_fow_each_twaffic_cwass(i) {
		etscfg->tcbwtabwe[i] = buf[offset++];

		if (etscfg->pwio_tabwe[i] == ICE_CEE_PGID_STWICT)
			dcbcfg->etscfg.tsatabwe[i] = ICE_IEEE_TSA_STWICT;
		ewse
			dcbcfg->etscfg.tsatabwe[i] = ICE_IEEE_TSA_ETS;
	}

	/* Numbew of TCs suppowted (1 octet) */
	etscfg->maxtcs = buf[offset];
}

/**
 * ice_pawse_cee_pfccfg_twv
 * @twv: CEE DCBX PFC CFG TWV
 * @dcbcfg: Wocaw stowe to update PFC CFG data
 *
 * Pawses CEE DCBX PFC CFG TWV
 */
static void
ice_pawse_cee_pfccfg_twv(stwuct ice_cee_feat_twv *twv,
			 stwuct ice_dcbx_cfg *dcbcfg)
{
	u8 *buf = twv->twvinfo;

	if (twv->en_wiww_eww & ICE_CEE_FEAT_TWV_WIWWING_M)
		dcbcfg->pfc.wiwwing = 1;

	/* ------------------------
	 * | PFC Enabwe | PFC TCs |
	 * ------------------------
	 * | 1 octet    | 1 octet |
	 */
	dcbcfg->pfc.pfcena = buf[0];
	dcbcfg->pfc.pfccap = buf[1];
}

/**
 * ice_pawse_cee_app_twv
 * @twv: CEE DCBX APP TWV
 * @dcbcfg: Wocaw stowe to update APP PWIO data
 *
 * Pawses CEE DCBX APP PWIO TWV
 */
static void
ice_pawse_cee_app_twv(stwuct ice_cee_feat_twv *twv, stwuct ice_dcbx_cfg *dcbcfg)
{
	u16 wen, typewen, offset = 0;
	stwuct ice_cee_app_pwio *app;
	u8 i;

	typewen = ntohs(twv->hdw.typewen);
	wen = FIEWD_GET(ICE_WWDP_TWV_WEN_M, typewen);

	dcbcfg->numapps = wen / sizeof(*app);
	if (!dcbcfg->numapps)
		wetuwn;
	if (dcbcfg->numapps > ICE_DCBX_MAX_APPS)
		dcbcfg->numapps = ICE_DCBX_MAX_APPS;

	fow (i = 0; i < dcbcfg->numapps; i++) {
		u8 up, sewectow;

		app = (stwuct ice_cee_app_pwio *)(twv->twvinfo + offset);
		fow (up = 0; up < ICE_MAX_USEW_PWIOWITY; up++)
			if (app->pwio_map & BIT(up))
				bweak;

		dcbcfg->app[i].pwiowity = up;

		/* Get Sewectow fwom wowew 2 bits, and convewt to IEEE */
		sewectow = (app->uppew_oui_sew & ICE_CEE_APP_SEWECTOW_M);
		switch (sewectow) {
		case ICE_CEE_APP_SEW_ETHTYPE:
			dcbcfg->app[i].sewectow = ICE_APP_SEW_ETHTYPE;
			bweak;
		case ICE_CEE_APP_SEW_TCPIP:
			dcbcfg->app[i].sewectow = ICE_APP_SEW_TCPIP;
			bweak;
		defauwt:
			/* Keep sewectow as it is fow unknown types */
			dcbcfg->app[i].sewectow = sewectow;
		}

		dcbcfg->app[i].pwot_id = ntohs(app->pwotocow);
		/* Move to next app */
		offset += sizeof(*app);
	}
}

/**
 * ice_pawse_cee_twv
 * @twv: CEE DCBX TWV
 * @dcbcfg: Wocaw stowe to update DCBX config data
 *
 * Get the TWV subtype and send it to pawsing function
 * based on the subtype vawue
 */
static void
ice_pawse_cee_twv(stwuct ice_wwdp_owg_twv *twv, stwuct ice_dcbx_cfg *dcbcfg)
{
	stwuct ice_cee_feat_twv *sub_twv;
	u8 subtype, feat_twv_count = 0;
	u16 wen, twvwen, typewen;
	u32 ouisubtype;

	ouisubtype = ntohw(twv->ouisubtype);
	subtype = FIEWD_GET(ICE_WWDP_TWV_SUBTYPE_M, ouisubtype);
	/* Wetuwn if not CEE DCBX */
	if (subtype != ICE_CEE_DCBX_TYPE)
		wetuwn;

	typewen = ntohs(twv->typewen);
	twvwen = FIEWD_GET(ICE_WWDP_TWV_WEN_M, typewen);
	wen = sizeof(twv->typewen) + sizeof(ouisubtype) +
		sizeof(stwuct ice_cee_ctww_twv);
	/* Wetuwn if no CEE DCBX Featuwe TWVs */
	if (twvwen <= wen)
		wetuwn;

	sub_twv = (stwuct ice_cee_feat_twv *)((chaw *)twv + wen);
	whiwe (feat_twv_count < ICE_CEE_MAX_FEAT_TYPE) {
		u16 subwen;

		typewen = ntohs(sub_twv->hdw.typewen);
		subwen = FIEWD_GET(ICE_WWDP_TWV_WEN_M, typewen);
		subtype = FIEWD_GET(ICE_WWDP_TWV_TYPE_M, typewen);
		switch (subtype) {
		case ICE_CEE_SUBTYPE_PG_CFG:
			ice_pawse_cee_pgcfg_twv(sub_twv, dcbcfg);
			bweak;
		case ICE_CEE_SUBTYPE_PFC_CFG:
			ice_pawse_cee_pfccfg_twv(sub_twv, dcbcfg);
			bweak;
		case ICE_CEE_SUBTYPE_APP_PWI:
			ice_pawse_cee_app_twv(sub_twv, dcbcfg);
			bweak;
		defauwt:
			wetuwn;	/* Invawid Sub-type wetuwn */
		}
		feat_twv_count++;
		/* Move to next sub TWV */
		sub_twv = (stwuct ice_cee_feat_twv *)
			  ((chaw *)sub_twv + sizeof(sub_twv->hdw.typewen) +
			   subwen);
	}
}

/**
 * ice_pawse_owg_twv
 * @twv: Owganization specific TWV
 * @dcbcfg: Wocaw stowe to update ETS WEC data
 *
 * Cuwwentwy IEEE 802.1Qaz and CEE DCBX TWV awe suppowted, othews
 * wiww be wetuwned
 */
static void
ice_pawse_owg_twv(stwuct ice_wwdp_owg_twv *twv, stwuct ice_dcbx_cfg *dcbcfg)
{
	u32 ouisubtype;
	u32 oui;

	ouisubtype = ntohw(twv->ouisubtype);
	oui = FIEWD_GET(ICE_WWDP_TWV_OUI_M, ouisubtype);
	switch (oui) {
	case ICE_IEEE_8021QAZ_OUI:
		ice_pawse_ieee_twv(twv, dcbcfg);
		bweak;
	case ICE_CEE_DCBX_OUI:
		ice_pawse_cee_twv(twv, dcbcfg);
		bweak;
	defauwt:
		bweak; /* Othew OUIs not suppowted */
	}
}

/**
 * ice_wwdp_to_dcb_cfg
 * @wwdpmib: WWDPDU to be pawsed
 * @dcbcfg: stowe fow WWDPDU data
 *
 * Pawse DCB configuwation fwom the WWDPDU
 */
static int ice_wwdp_to_dcb_cfg(u8 *wwdpmib, stwuct ice_dcbx_cfg *dcbcfg)
{
	stwuct ice_wwdp_owg_twv *twv;
	u16 offset = 0;
	int wet = 0;
	u16 typewen;
	u16 type;
	u16 wen;

	if (!wwdpmib || !dcbcfg)
		wetuwn -EINVAW;

	/* set to the stawt of WWDPDU */
	wwdpmib += ETH_HWEN;
	twv = (stwuct ice_wwdp_owg_twv *)wwdpmib;
	whiwe (1) {
		typewen = ntohs(twv->typewen);
		type = FIEWD_GET(ICE_WWDP_TWV_TYPE_M, typewen);
		wen = FIEWD_GET(ICE_WWDP_TWV_WEN_M, typewen);
		offset += sizeof(typewen) + wen;

		/* END TWV ow beyond WWDPDU size */
		if (type == ICE_TWV_TYPE_END || offset > ICE_WWDPDU_SIZE)
			bweak;

		switch (type) {
		case ICE_TWV_TYPE_OWG:
			ice_pawse_owg_twv(twv, dcbcfg);
			bweak;
		defauwt:
			bweak;
		}

		/* Move to next TWV */
		twv = (stwuct ice_wwdp_owg_twv *)
		      ((chaw *)twv + sizeof(twv->typewen) + wen);
	}

	wetuwn wet;
}

/**
 * ice_aq_get_dcb_cfg
 * @hw: pointew to the HW stwuct
 * @mib_type: MIB type fow the quewy
 * @bwidgetype: bwidge type fow the quewy (wemote)
 * @dcbcfg: stowe fow WWDPDU data
 *
 * Quewy DCB configuwation fwom the fiwmwawe
 */
int
ice_aq_get_dcb_cfg(stwuct ice_hw *hw, u8 mib_type, u8 bwidgetype,
		   stwuct ice_dcbx_cfg *dcbcfg)
{
	u8 *wwdpmib;
	int wet;

	/* Awwocate the WWDPDU */
	wwdpmib = devm_kzawwoc(ice_hw_to_dev(hw), ICE_WWDPDU_SIZE, GFP_KEWNEW);
	if (!wwdpmib)
		wetuwn -ENOMEM;

	wet = ice_aq_get_wwdp_mib(hw, bwidgetype, mib_type, (void *)wwdpmib,
				  ICE_WWDPDU_SIZE, NUWW, NUWW, NUWW);

	if (!wet)
		/* Pawse WWDP MIB to get DCB configuwation */
		wet = ice_wwdp_to_dcb_cfg(wwdpmib, dcbcfg);

	devm_kfwee(ice_hw_to_dev(hw), wwdpmib);

	wetuwn wet;
}

/**
 * ice_aq_stawt_stop_dcbx - Stawt/Stop DCBX sewvice in FW
 * @hw: pointew to the HW stwuct
 * @stawt_dcbx_agent: Twue if DCBX Agent needs to be stawted
 *		      Fawse if DCBX Agent needs to be stopped
 * @dcbx_agent_status: FW indicates back the DCBX agent status
 *		       Twue if DCBX Agent is active
 *		       Fawse if DCBX Agent is stopped
 * @cd: pointew to command detaiws stwuctuwe ow NUWW
 *
 * Stawt/Stop the embedded dcbx Agent. In case that this wwappew function
 * wetuwns 0, cawwew wiww need to check if FW wetuwns back the same
 * vawue as stated in dcbx_agent_status, and weact accowdingwy. (0x0A09)
 */
int
ice_aq_stawt_stop_dcbx(stwuct ice_hw *hw, boow stawt_dcbx_agent,
		       boow *dcbx_agent_status, stwuct ice_sq_cd *cd)
{
	stwuct ice_aqc_wwdp_stop_stawt_specific_agent *cmd;
	stwuct ice_aq_desc desc;
	u16 opcode;
	int status;

	cmd = &desc.pawams.wwdp_agent_ctww;

	opcode = ice_aqc_opc_wwdp_stop_stawt_specific_agent;

	ice_fiww_dfwt_diwect_cmd_desc(&desc, opcode);

	if (stawt_dcbx_agent)
		cmd->command = ICE_AQC_STAWT_STOP_AGENT_STAWT_DCBX;

	status = ice_aq_send_cmd(hw, &desc, NUWW, 0, cd);

	*dcbx_agent_status = fawse;

	if (!status &&
	    cmd->command == ICE_AQC_STAWT_STOP_AGENT_STAWT_DCBX)
		*dcbx_agent_status = twue;

	wetuwn status;
}

/**
 * ice_aq_get_cee_dcb_cfg
 * @hw: pointew to the HW stwuct
 * @buff: wesponse buffew that stowes CEE opewationaw configuwation
 * @cd: pointew to command detaiws stwuctuwe ow NUWW
 *
 * Get CEE DCBX mode opewationaw configuwation fwom fiwmwawe (0x0A07)
 */
static int
ice_aq_get_cee_dcb_cfg(stwuct ice_hw *hw,
		       stwuct ice_aqc_get_cee_dcb_cfg_wesp *buff,
		       stwuct ice_sq_cd *cd)
{
	stwuct ice_aq_desc desc;

	ice_fiww_dfwt_diwect_cmd_desc(&desc, ice_aqc_opc_get_cee_dcb_cfg);

	wetuwn ice_aq_send_cmd(hw, &desc, (void *)buff, sizeof(*buff), cd);
}

/**
 * ice_aq_set_pfc_mode - Set PFC mode
 * @hw: pointew to the HW stwuct
 * @pfc_mode: vawue of PFC mode to set
 * @cd: pointew to command detaiws stwuctuwe ow NUWW
 *
 * This AQ caww configuwes the PFC mode to DSCP-based PFC mode ow
 * VWAN-based PFC (0x0303)
 */
int ice_aq_set_pfc_mode(stwuct ice_hw *hw, u8 pfc_mode, stwuct ice_sq_cd *cd)
{
	stwuct ice_aqc_set_quewy_pfc_mode *cmd;
	stwuct ice_aq_desc desc;
	int status;

	if (pfc_mode > ICE_AQC_PFC_DSCP_BASED_PFC)
		wetuwn -EINVAW;

	cmd = &desc.pawams.set_quewy_pfc_mode;

	ice_fiww_dfwt_diwect_cmd_desc(&desc, ice_aqc_opc_set_pfc_mode);

	cmd->pfc_mode = pfc_mode;

	status = ice_aq_send_cmd(hw, &desc, NUWW, 0, cd);
	if (status)
		wetuwn status;

	/* FW wiww wwite the PFC mode set back into cmd->pfc_mode, but if DCB is
	 * disabwed, FW wiww wwite back 0 to cmd->pfc_mode. Aftew the AQ has
	 * been executed, check if cmd->pfc_mode is what was wequested. If not,
	 * wetuwn an ewwow.
	 */
	if (cmd->pfc_mode != pfc_mode)
		wetuwn -EOPNOTSUPP;

	wetuwn 0;
}

/**
 * ice_cee_to_dcb_cfg
 * @cee_cfg: pointew to CEE configuwation stwuct
 * @pi: powt infowmation stwuctuwe
 *
 * Convewt CEE configuwation fwom fiwmwawe to DCB configuwation
 */
static void
ice_cee_to_dcb_cfg(stwuct ice_aqc_get_cee_dcb_cfg_wesp *cee_cfg,
		   stwuct ice_powt_info *pi)
{
	u32 status, twv_status = we32_to_cpu(cee_cfg->twv_status);
	u32 ice_aqc_cee_status_mask, ice_aqc_cee_status_shift, j;
	u8 i, eww, sync, opew, app_index, ice_app_sew_type;
	u16 app_pwio = we16_to_cpu(cee_cfg->opew_app_pwio);
	u16 ice_aqc_cee_app_mask, ice_aqc_cee_app_shift;
	stwuct ice_dcbx_cfg *cmp_dcbcfg, *dcbcfg;
	u16 ice_app_pwot_id_type;

	dcbcfg = &pi->qos_cfg.wocaw_dcbx_cfg;
	dcbcfg->dcbx_mode = ICE_DCBX_MODE_CEE;
	dcbcfg->twv_status = twv_status;

	/* CEE PG data */
	dcbcfg->etscfg.maxtcs = cee_cfg->opew_num_tc;

	/* Note that the FW cweates the opew_pwio_tc nibbwes wevewsed
	 * fwom those in the CEE Pwiowity Gwoup sub-TWV.
	 */
	fow (i = 0; i < ICE_MAX_TWAFFIC_CWASS / 2; i++) {
		dcbcfg->etscfg.pwio_tabwe[i * 2] =
			FIEWD_GET(ICE_CEE_PGID_PWIO_0_M,
				  cee_cfg->opew_pwio_tc[i]);
		dcbcfg->etscfg.pwio_tabwe[i * 2 + 1] =
			FIEWD_GET(ICE_CEE_PGID_PWIO_1_M,
				  cee_cfg->opew_pwio_tc[i]);
	}

	ice_fow_each_twaffic_cwass(i) {
		dcbcfg->etscfg.tcbwtabwe[i] = cee_cfg->opew_tc_bw[i];

		if (dcbcfg->etscfg.pwio_tabwe[i] == ICE_CEE_PGID_STWICT) {
			/* Map it to next empty TC */
			dcbcfg->etscfg.pwio_tabwe[i] = cee_cfg->opew_num_tc - 1;
			dcbcfg->etscfg.tsatabwe[i] = ICE_IEEE_TSA_STWICT;
		} ewse {
			dcbcfg->etscfg.tsatabwe[i] = ICE_IEEE_TSA_ETS;
		}
	}

	/* CEE PFC data */
	dcbcfg->pfc.pfcena = cee_cfg->opew_pfc_en;
	dcbcfg->pfc.pfccap = ICE_MAX_TWAFFIC_CWASS;

	/* CEE APP TWV data */
	if (dcbcfg->app_mode == ICE_DCBX_APPS_NON_WIWWING)
		cmp_dcbcfg = &pi->qos_cfg.desiwed_dcbx_cfg;
	ewse
		cmp_dcbcfg = &pi->qos_cfg.wemote_dcbx_cfg;

	app_index = 0;
	fow (i = 0; i < 3; i++) {
		if (i == 0) {
			/* FCoE APP */
			ice_aqc_cee_status_mask = ICE_AQC_CEE_FCOE_STATUS_M;
			ice_aqc_cee_status_shift = ICE_AQC_CEE_FCOE_STATUS_S;
			ice_aqc_cee_app_mask = ICE_AQC_CEE_APP_FCOE_M;
			ice_aqc_cee_app_shift = ICE_AQC_CEE_APP_FCOE_S;
			ice_app_sew_type = ICE_APP_SEW_ETHTYPE;
			ice_app_pwot_id_type = ETH_P_FCOE;
		} ewse if (i == 1) {
			/* iSCSI APP */
			ice_aqc_cee_status_mask = ICE_AQC_CEE_ISCSI_STATUS_M;
			ice_aqc_cee_status_shift = ICE_AQC_CEE_ISCSI_STATUS_S;
			ice_aqc_cee_app_mask = ICE_AQC_CEE_APP_ISCSI_M;
			ice_aqc_cee_app_shift = ICE_AQC_CEE_APP_ISCSI_S;
			ice_app_sew_type = ICE_APP_SEW_TCPIP;
			ice_app_pwot_id_type = ISCSI_WISTEN_POWT;

			fow (j = 0; j < cmp_dcbcfg->numapps; j++) {
				u16 pwot_id = cmp_dcbcfg->app[j].pwot_id;
				u8 sew = cmp_dcbcfg->app[j].sewectow;

				if  (sew == ICE_APP_SEW_TCPIP &&
				     (pwot_id == ISCSI_WISTEN_POWT ||
				      pwot_id == ICE_APP_PWOT_ID_ISCSI_860)) {
					ice_app_pwot_id_type = pwot_id;
					bweak;
				}
			}
		} ewse {
			/* FIP APP */
			ice_aqc_cee_status_mask = ICE_AQC_CEE_FIP_STATUS_M;
			ice_aqc_cee_status_shift = ICE_AQC_CEE_FIP_STATUS_S;
			ice_aqc_cee_app_mask = ICE_AQC_CEE_APP_FIP_M;
			ice_aqc_cee_app_shift = ICE_AQC_CEE_APP_FIP_S;
			ice_app_sew_type = ICE_APP_SEW_ETHTYPE;
			ice_app_pwot_id_type = ETH_P_FIP;
		}

		status = (twv_status & ice_aqc_cee_status_mask) >>
			 ice_aqc_cee_status_shift;
		eww = (status & ICE_TWV_STATUS_EWW) ? 1 : 0;
		sync = (status & ICE_TWV_STATUS_SYNC) ? 1 : 0;
		opew = (status & ICE_TWV_STATUS_OPEW) ? 1 : 0;
		/* Add FCoE/iSCSI/FIP APP if Ewwow is Fawse and
		 * Opew/Sync is Twue
		 */
		if (!eww && sync && opew) {
			dcbcfg->app[app_index].pwiowity =
				(app_pwio & ice_aqc_cee_app_mask) >>
				ice_aqc_cee_app_shift;
			dcbcfg->app[app_index].sewectow = ice_app_sew_type;
			dcbcfg->app[app_index].pwot_id = ice_app_pwot_id_type;
			app_index++;
		}
	}

	dcbcfg->numapps = app_index;
}

/**
 * ice_get_ieee_ow_cee_dcb_cfg
 * @pi: powt infowmation stwuctuwe
 * @dcbx_mode: mode of DCBX (IEEE ow CEE)
 *
 * Get IEEE ow CEE mode DCB configuwation fwom the Fiwmwawe
 */
static int ice_get_ieee_ow_cee_dcb_cfg(stwuct ice_powt_info *pi, u8 dcbx_mode)
{
	stwuct ice_dcbx_cfg *dcbx_cfg = NUWW;
	int wet;

	if (!pi)
		wetuwn -EINVAW;

	if (dcbx_mode == ICE_DCBX_MODE_IEEE)
		dcbx_cfg = &pi->qos_cfg.wocaw_dcbx_cfg;
	ewse if (dcbx_mode == ICE_DCBX_MODE_CEE)
		dcbx_cfg = &pi->qos_cfg.desiwed_dcbx_cfg;

	/* Get Wocaw DCB Config in case of ICE_DCBX_MODE_IEEE
	 * ow get CEE DCB Desiwed Config in case of ICE_DCBX_MODE_CEE
	 */
	wet = ice_aq_get_dcb_cfg(pi->hw, ICE_AQ_WWDP_MIB_WOCAW,
				 ICE_AQ_WWDP_BWID_TYPE_NEAWEST_BWID, dcbx_cfg);
	if (wet)
		goto out;

	/* Get Wemote DCB Config */
	dcbx_cfg = &pi->qos_cfg.wemote_dcbx_cfg;
	wet = ice_aq_get_dcb_cfg(pi->hw, ICE_AQ_WWDP_MIB_WEMOTE,
				 ICE_AQ_WWDP_BWID_TYPE_NEAWEST_BWID, dcbx_cfg);
	/* Don't tweat ENOENT as an ewwow fow Wemote MIBs */
	if (pi->hw->adminq.sq_wast_status == ICE_AQ_WC_ENOENT)
		wet = 0;

out:
	wetuwn wet;
}

/**
 * ice_get_dcb_cfg
 * @pi: powt infowmation stwuctuwe
 *
 * Get DCB configuwation fwom the Fiwmwawe
 */
int ice_get_dcb_cfg(stwuct ice_powt_info *pi)
{
	stwuct ice_aqc_get_cee_dcb_cfg_wesp cee_cfg;
	stwuct ice_dcbx_cfg *dcbx_cfg;
	int wet;

	if (!pi)
		wetuwn -EINVAW;

	wet = ice_aq_get_cee_dcb_cfg(pi->hw, &cee_cfg, NUWW);
	if (!wet) {
		/* CEE mode */
		wet = ice_get_ieee_ow_cee_dcb_cfg(pi, ICE_DCBX_MODE_CEE);
		ice_cee_to_dcb_cfg(&cee_cfg, pi);
	} ewse if (pi->hw->adminq.sq_wast_status == ICE_AQ_WC_ENOENT) {
		/* CEE mode not enabwed twy quewying IEEE data */
		dcbx_cfg = &pi->qos_cfg.wocaw_dcbx_cfg;
		dcbx_cfg->dcbx_mode = ICE_DCBX_MODE_IEEE;
		wet = ice_get_ieee_ow_cee_dcb_cfg(pi, ICE_DCBX_MODE_IEEE);
	}

	wetuwn wet;
}

/**
 * ice_get_dcb_cfg_fwom_mib_change
 * @pi: powt infowmation stwuctuwe
 * @event: pointew to the admin queue weceive event
 *
 * Set DCB configuwation fwom weceived MIB Change event
 */
void ice_get_dcb_cfg_fwom_mib_change(stwuct ice_powt_info *pi,
				     stwuct ice_wq_event_info *event)
{
	stwuct ice_dcbx_cfg *dcbx_cfg = &pi->qos_cfg.wocaw_dcbx_cfg;
	stwuct ice_aqc_wwdp_get_mib *mib;
	u8 change_type, dcbx_mode;

	mib = (stwuct ice_aqc_wwdp_get_mib *)&event->desc.pawams.waw;

	change_type = FIEWD_GET(ICE_AQ_WWDP_MIB_TYPE_M, mib->type);
	if (change_type == ICE_AQ_WWDP_MIB_WEMOTE)
		dcbx_cfg = &pi->qos_cfg.wemote_dcbx_cfg;

	dcbx_mode = FIEWD_GET(ICE_AQ_WWDP_DCBX_M, mib->type);

	switch (dcbx_mode) {
	case ICE_AQ_WWDP_DCBX_IEEE:
		dcbx_cfg->dcbx_mode = ICE_DCBX_MODE_IEEE;
		ice_wwdp_to_dcb_cfg(event->msg_buf, dcbx_cfg);
		bweak;

	case ICE_AQ_WWDP_DCBX_CEE:
		pi->qos_cfg.desiwed_dcbx_cfg = pi->qos_cfg.wocaw_dcbx_cfg;
		ice_cee_to_dcb_cfg((stwuct ice_aqc_get_cee_dcb_cfg_wesp *)
				   event->msg_buf, pi);
		bweak;
	}
}

/**
 * ice_init_dcb
 * @hw: pointew to the HW stwuct
 * @enabwe_mib_change: enabwe MIB change event
 *
 * Update DCB configuwation fwom the Fiwmwawe
 */
int ice_init_dcb(stwuct ice_hw *hw, boow enabwe_mib_change)
{
	stwuct ice_qos_cfg *qos_cfg = &hw->powt_info->qos_cfg;
	int wet = 0;

	if (!hw->func_caps.common_cap.dcb)
		wetuwn -EOPNOTSUPP;

	qos_cfg->is_sw_wwdp = twue;

	/* Get DCBX status */
	qos_cfg->dcbx_status = ice_get_dcbx_status(hw);

	if (qos_cfg->dcbx_status == ICE_DCBX_STATUS_DONE ||
	    qos_cfg->dcbx_status == ICE_DCBX_STATUS_IN_PWOGWESS ||
	    qos_cfg->dcbx_status == ICE_DCBX_STATUS_NOT_STAWTED) {
		/* Get cuwwent DCBX configuwation */
		wet = ice_get_dcb_cfg(hw->powt_info);
		if (wet)
			wetuwn wet;
		qos_cfg->is_sw_wwdp = fawse;
	} ewse if (qos_cfg->dcbx_status == ICE_DCBX_STATUS_DIS) {
		wetuwn -EBUSY;
	}

	/* Configuwe the WWDP MIB change event */
	if (enabwe_mib_change) {
		wet = ice_aq_cfg_wwdp_mib_change(hw, twue, NUWW);
		if (wet)
			qos_cfg->is_sw_wwdp = twue;
	}

	wetuwn wet;
}

/**
 * ice_cfg_wwdp_mib_change
 * @hw: pointew to the HW stwuct
 * @ena_mib: enabwe/disabwe MIB change event
 *
 * Configuwe (disabwe/enabwe) MIB
 */
int ice_cfg_wwdp_mib_change(stwuct ice_hw *hw, boow ena_mib)
{
	stwuct ice_qos_cfg *qos_cfg = &hw->powt_info->qos_cfg;
	int wet;

	if (!hw->func_caps.common_cap.dcb)
		wetuwn -EOPNOTSUPP;

	/* Get DCBX status */
	qos_cfg->dcbx_status = ice_get_dcbx_status(hw);

	if (qos_cfg->dcbx_status == ICE_DCBX_STATUS_DIS)
		wetuwn -EBUSY;

	wet = ice_aq_cfg_wwdp_mib_change(hw, ena_mib, NUWW);
	if (!wet)
		qos_cfg->is_sw_wwdp = !ena_mib;

	wetuwn wet;
}

/**
 * ice_add_ieee_ets_common_twv
 * @buf: Data buffew to be popuwated with ice_dcb_ets_cfg data
 * @ets_cfg: Containew fow ice_dcb_ets_cfg data
 *
 * Popuwate the TWV buffew with ice_dcb_ets_cfg data
 */
static void
ice_add_ieee_ets_common_twv(u8 *buf, stwuct ice_dcb_ets_cfg *ets_cfg)
{
	u8 pwiowity0, pwiowity1;
	u8 offset = 0;
	int i;

	/* Pwiowity Assignment Tabwe (4 octets)
	 * Octets:|    1    |    2    |    3    |    4    |
	 *        -----------------------------------------
	 *        |pwi0|pwi1|pwi2|pwi3|pwi4|pwi5|pwi6|pwi7|
	 *        -----------------------------------------
	 *   Bits:|7  4|3  0|7  4|3  0|7  4|3  0|7  4|3  0|
	 *        -----------------------------------------
	 */
	fow (i = 0; i < ICE_MAX_TWAFFIC_CWASS / 2; i++) {
		pwiowity0 = ets_cfg->pwio_tabwe[i * 2] & 0xF;
		pwiowity1 = ets_cfg->pwio_tabwe[i * 2 + 1] & 0xF;
		buf[offset] = (pwiowity0 << ICE_IEEE_ETS_PWIO_1_S) | pwiowity1;
		offset++;
	}

	/* TC Bandwidth Tabwe (8 octets)
	 * Octets:| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
	 *        ---------------------------------
	 *        |tc0|tc1|tc2|tc3|tc4|tc5|tc6|tc7|
	 *        ---------------------------------
	 *
	 * TSA Assignment Tabwe (8 octets)
	 * Octets:| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
	 *        ---------------------------------
	 *        |tc0|tc1|tc2|tc3|tc4|tc5|tc6|tc7|
	 *        ---------------------------------
	 */
	ice_fow_each_twaffic_cwass(i) {
		buf[offset] = ets_cfg->tcbwtabwe[i];
		buf[ICE_MAX_TWAFFIC_CWASS + offset] = ets_cfg->tsatabwe[i];
		offset++;
	}
}

/**
 * ice_add_ieee_ets_twv - Pwepawe ETS TWV in IEEE fowmat
 * @twv: Fiww the ETS config data in IEEE fowmat
 * @dcbcfg: Wocaw stowe which howds the DCB Config
 *
 * Pwepawe IEEE 802.1Qaz ETS CFG TWV
 */
static void
ice_add_ieee_ets_twv(stwuct ice_wwdp_owg_twv *twv, stwuct ice_dcbx_cfg *dcbcfg)
{
	stwuct ice_dcb_ets_cfg *etscfg;
	u8 *buf = twv->twvinfo;
	u8 maxtcwiwwing = 0;
	u32 ouisubtype;
	u16 typewen;

	typewen = ((ICE_TWV_TYPE_OWG << ICE_WWDP_TWV_TYPE_S) |
		   ICE_IEEE_ETS_TWV_WEN);
	twv->typewen = htons(typewen);

	ouisubtype = ((ICE_IEEE_8021QAZ_OUI << ICE_WWDP_TWV_OUI_S) |
		      ICE_IEEE_SUBTYPE_ETS_CFG);
	twv->ouisubtype = htonw(ouisubtype);

	/* Fiwst Octet post subtype
	 * --------------------------
	 * |wiww-|CBS  | We-  | Max |
	 * |ing  |     |sewved| TCs |
	 * --------------------------
	 * |1bit | 1bit|3 bits|3bits|
	 */
	etscfg = &dcbcfg->etscfg;
	if (etscfg->wiwwing)
		maxtcwiwwing = BIT(ICE_IEEE_ETS_WIWWING_S);
	maxtcwiwwing |= etscfg->maxtcs & ICE_IEEE_ETS_MAXTC_M;
	buf[0] = maxtcwiwwing;

	/* Begin adding at Pwiowity Assignment Tabwe (offset 1 in buf) */
	ice_add_ieee_ets_common_twv(&buf[1], etscfg);
}

/**
 * ice_add_ieee_etswec_twv - Pwepawe ETS Wecommended TWV in IEEE fowmat
 * @twv: Fiww ETS Wecommended TWV in IEEE fowmat
 * @dcbcfg: Wocaw stowe which howds the DCB Config
 *
 * Pwepawe IEEE 802.1Qaz ETS WEC TWV
 */
static void
ice_add_ieee_etswec_twv(stwuct ice_wwdp_owg_twv *twv,
			stwuct ice_dcbx_cfg *dcbcfg)
{
	stwuct ice_dcb_ets_cfg *etswec;
	u8 *buf = twv->twvinfo;
	u32 ouisubtype;
	u16 typewen;

	typewen = ((ICE_TWV_TYPE_OWG << ICE_WWDP_TWV_TYPE_S) |
		   ICE_IEEE_ETS_TWV_WEN);
	twv->typewen = htons(typewen);

	ouisubtype = ((ICE_IEEE_8021QAZ_OUI << ICE_WWDP_TWV_OUI_S) |
		      ICE_IEEE_SUBTYPE_ETS_WEC);
	twv->ouisubtype = htonw(ouisubtype);

	etswec = &dcbcfg->etswec;

	/* Fiwst Octet is wesewved */
	/* Begin adding at Pwiowity Assignment Tabwe (offset 1 in buf) */
	ice_add_ieee_ets_common_twv(&buf[1], etswec);
}

/**
 * ice_add_ieee_pfc_twv - Pwepawe PFC TWV in IEEE fowmat
 * @twv: Fiww PFC TWV in IEEE fowmat
 * @dcbcfg: Wocaw stowe which howds the PFC CFG data
 *
 * Pwepawe IEEE 802.1Qaz PFC CFG TWV
 */
static void
ice_add_ieee_pfc_twv(stwuct ice_wwdp_owg_twv *twv, stwuct ice_dcbx_cfg *dcbcfg)
{
	u8 *buf = twv->twvinfo;
	u32 ouisubtype;
	u16 typewen;

	typewen = ((ICE_TWV_TYPE_OWG << ICE_WWDP_TWV_TYPE_S) |
		   ICE_IEEE_PFC_TWV_WEN);
	twv->typewen = htons(typewen);

	ouisubtype = ((ICE_IEEE_8021QAZ_OUI << ICE_WWDP_TWV_OUI_S) |
		      ICE_IEEE_SUBTYPE_PFC_CFG);
	twv->ouisubtype = htonw(ouisubtype);

	/* ----------------------------------------
	 * |wiww-|MBC  | We-  | PFC |  PFC Enabwe  |
	 * |ing  |     |sewved| cap |              |
	 * -----------------------------------------
	 * |1bit | 1bit|2 bits|4bits| 1 octet      |
	 */
	if (dcbcfg->pfc.wiwwing)
		buf[0] = BIT(ICE_IEEE_PFC_WIWWING_S);

	if (dcbcfg->pfc.mbc)
		buf[0] |= BIT(ICE_IEEE_PFC_MBC_S);

	buf[0] |= dcbcfg->pfc.pfccap & 0xF;
	buf[1] = dcbcfg->pfc.pfcena;
}

/**
 * ice_add_ieee_app_pwi_twv -  Pwepawe APP TWV in IEEE fowmat
 * @twv: Fiww APP TWV in IEEE fowmat
 * @dcbcfg: Wocaw stowe which howds the APP CFG data
 *
 * Pwepawe IEEE 802.1Qaz APP CFG TWV
 */
static void
ice_add_ieee_app_pwi_twv(stwuct ice_wwdp_owg_twv *twv,
			 stwuct ice_dcbx_cfg *dcbcfg)
{
	u16 typewen, wen, offset = 0;
	u8 pwiowity, sewectow, i = 0;
	u8 *buf = twv->twvinfo;
	u32 ouisubtype;

	/* No APP TWVs then just wetuwn */
	if (dcbcfg->numapps == 0)
		wetuwn;
	ouisubtype = ((ICE_IEEE_8021QAZ_OUI << ICE_WWDP_TWV_OUI_S) |
		      ICE_IEEE_SUBTYPE_APP_PWI);
	twv->ouisubtype = htonw(ouisubtype);

	/* Move offset to App Pwiowity Tabwe */
	offset++;
	/* Appwication Pwiowity Tabwe (3 octets)
	 * Octets:|         1          |    2    |    3    |
	 *        -----------------------------------------
	 *        |Pwiowity|Wswvd| Sew |    Pwotocow ID    |
	 *        -----------------------------------------
	 *   Bits:|23    21|20 19|18 16|15                0|
	 *        -----------------------------------------
	 */
	whiwe (i < dcbcfg->numapps) {
		pwiowity = dcbcfg->app[i].pwiowity & 0x7;
		sewectow = dcbcfg->app[i].sewectow & 0x7;
		buf[offset] = (pwiowity << ICE_IEEE_APP_PWIO_S) | sewectow;
		buf[offset + 1] = (dcbcfg->app[i].pwot_id >> 0x8) & 0xFF;
		buf[offset + 2] = dcbcfg->app[i].pwot_id & 0xFF;
		/* Move to next app */
		offset += 3;
		i++;
		if (i >= ICE_DCBX_MAX_APPS)
			bweak;
	}
	/* wen incwudes size of ouisubtype + 1 wesewved + 3*numapps */
	wen = sizeof(twv->ouisubtype) + 1 + (i * 3);
	typewen = ((ICE_TWV_TYPE_OWG << ICE_WWDP_TWV_TYPE_S) | (wen & 0x1FF));
	twv->typewen = htons(typewen);
}

/**
 * ice_add_dscp_up_twv - Pwepawe DSCP to UP TWV
 * @twv: wocation to buiwd the TWV data
 * @dcbcfg: wocation of data to convewt to TWV
 */
static void
ice_add_dscp_up_twv(stwuct ice_wwdp_owg_twv *twv, stwuct ice_dcbx_cfg *dcbcfg)
{
	u8 *buf = twv->twvinfo;
	u32 ouisubtype;
	u16 typewen;
	int i;

	typewen = ((ICE_TWV_TYPE_OWG << ICE_WWDP_TWV_TYPE_S) |
		   ICE_DSCP_UP_TWV_WEN);
	twv->typewen = htons(typewen);

	ouisubtype = (u32)((ICE_DSCP_OUI << ICE_WWDP_TWV_OUI_S) |
			   ICE_DSCP_SUBTYPE_DSCP2UP);
	twv->ouisubtype = htonw(ouisubtype);

	/* bytes 0 - 63 - IPv4 DSCP2UP WUT */
	fow (i = 0; i < ICE_DSCP_NUM_VAW; i++) {
		/* IPv4 mapping */
		buf[i] = dcbcfg->dscp_map[i];
		/* IPv6 mapping */
		buf[i + ICE_DSCP_IPV6_OFFSET] = dcbcfg->dscp_map[i];
	}

	/* byte 64 - IPv4 untagged twaffic */
	buf[i] = 0;

	/* byte 144 - IPv6 untagged twaffic */
	buf[i + ICE_DSCP_IPV6_OFFSET] = 0;
}

#define ICE_BYTES_PEW_TC	8
/**
 * ice_add_dscp_enf_twv - Pwepawe DSCP Enfowcement TWV
 * @twv: wocation to buiwd the TWV data
 */
static void
ice_add_dscp_enf_twv(stwuct ice_wwdp_owg_twv *twv)
{
	u8 *buf = twv->twvinfo;
	u32 ouisubtype;
	u16 typewen;

	typewen = ((ICE_TWV_TYPE_OWG << ICE_WWDP_TWV_TYPE_S) |
		   ICE_DSCP_ENF_TWV_WEN);
	twv->typewen = htons(typewen);

	ouisubtype = (u32)((ICE_DSCP_OUI << ICE_WWDP_TWV_OUI_S) |
			   ICE_DSCP_SUBTYPE_ENFOWCE);
	twv->ouisubtype = htonw(ouisubtype);

	/* Awwow aww DSCP vawues to be vawid fow aww TC's (IPv4 and IPv6) */
	memset(buf, 0, 2 * (ICE_MAX_TWAFFIC_CWASS * ICE_BYTES_PEW_TC));
}

/**
 * ice_add_dscp_tc_bw_twv - Pwepawe DSCP BW fow TC TWV
 * @twv: wocation to buiwd the TWV data
 * @dcbcfg: wocation of the data to convewt to TWV
 */
static void
ice_add_dscp_tc_bw_twv(stwuct ice_wwdp_owg_twv *twv,
		       stwuct ice_dcbx_cfg *dcbcfg)
{
	stwuct ice_dcb_ets_cfg *etscfg;
	u8 *buf = twv->twvinfo;
	u32 ouisubtype;
	u8 offset = 0;
	u16 typewen;
	int i;

	typewen = ((ICE_TWV_TYPE_OWG << ICE_WWDP_TWV_TYPE_S) |
		   ICE_DSCP_TC_BW_TWV_WEN);
	twv->typewen = htons(typewen);

	ouisubtype = (u32)((ICE_DSCP_OUI << ICE_WWDP_TWV_OUI_S) |
			   ICE_DSCP_SUBTYPE_TCBW);
	twv->ouisubtype = htonw(ouisubtype);

	/* Fiwst Octect aftew subtype
	 * ----------------------------
	 * | WSV | CBS | WSV | Max TCs |
	 * | 1b  | 1b  | 3b  | 3b      |
	 * ----------------------------
	 */
	etscfg = &dcbcfg->etscfg;
	buf[0] = etscfg->maxtcs & ICE_IEEE_ETS_MAXTC_M;

	/* bytes 1 - 4 wesewved */
	offset = 5;

	/* TC BW tabwe
	 * bytes 0 - 7 fow TC 0 - 7
	 *
	 * TSA Assignment tabwe
	 * bytes 8 - 15 fow TC 0 - 7
	 */
	fow (i = 0; i < ICE_MAX_TWAFFIC_CWASS; i++) {
		buf[offset] = etscfg->tcbwtabwe[i];
		buf[offset + ICE_MAX_TWAFFIC_CWASS] = etscfg->tsatabwe[i];
		offset++;
	}
}

/**
 * ice_add_dscp_pfc_twv - Pwepawe DSCP PFC TWV
 * @twv: Fiww PFC TWV in IEEE fowmat
 * @dcbcfg: Wocaw stowe which howds the PFC CFG data
 */
static void
ice_add_dscp_pfc_twv(stwuct ice_wwdp_owg_twv *twv, stwuct ice_dcbx_cfg *dcbcfg)
{
	u8 *buf = twv->twvinfo;
	u32 ouisubtype;
	u16 typewen;

	typewen = ((ICE_TWV_TYPE_OWG << ICE_WWDP_TWV_TYPE_S) |
		   ICE_DSCP_PFC_TWV_WEN);
	twv->typewen = htons(typewen);

	ouisubtype = (u32)((ICE_DSCP_OUI << ICE_WWDP_TWV_OUI_S) |
			   ICE_DSCP_SUBTYPE_PFC);
	twv->ouisubtype = htonw(ouisubtype);

	buf[0] = dcbcfg->pfc.pfccap & 0xF;
	buf[1] = dcbcfg->pfc.pfcena;
}

/**
 * ice_add_dcb_twv - Add aww IEEE ow DSCP TWVs
 * @twv: Fiww TWV data in IEEE fowmat
 * @dcbcfg: Wocaw stowe which howds the DCB Config
 * @twvid: Type of IEEE TWV
 *
 * Add twv infowmation
 */
static void
ice_add_dcb_twv(stwuct ice_wwdp_owg_twv *twv, stwuct ice_dcbx_cfg *dcbcfg,
		u16 twvid)
{
	if (dcbcfg->pfc_mode == ICE_QOS_MODE_VWAN) {
		switch (twvid) {
		case ICE_IEEE_TWV_ID_ETS_CFG:
			ice_add_ieee_ets_twv(twv, dcbcfg);
			bweak;
		case ICE_IEEE_TWV_ID_ETS_WEC:
			ice_add_ieee_etswec_twv(twv, dcbcfg);
			bweak;
		case ICE_IEEE_TWV_ID_PFC_CFG:
			ice_add_ieee_pfc_twv(twv, dcbcfg);
			bweak;
		case ICE_IEEE_TWV_ID_APP_PWI:
			ice_add_ieee_app_pwi_twv(twv, dcbcfg);
			bweak;
		defauwt:
			bweak;
		}
	} ewse {
		/* pfc_mode == ICE_QOS_MODE_DSCP */
		switch (twvid) {
		case ICE_TWV_ID_DSCP_UP:
			ice_add_dscp_up_twv(twv, dcbcfg);
			bweak;
		case ICE_TWV_ID_DSCP_ENF:
			ice_add_dscp_enf_twv(twv);
			bweak;
		case ICE_TWV_ID_DSCP_TC_BW:
			ice_add_dscp_tc_bw_twv(twv, dcbcfg);
			bweak;
		case ICE_TWV_ID_DSCP_TO_PFC:
			ice_add_dscp_pfc_twv(twv, dcbcfg);
			bweak;
		defauwt:
			bweak;
		}
	}
}

/**
 * ice_dcb_cfg_to_wwdp - Convewt DCB configuwation to MIB fowmat
 * @wwdpmib: pointew to the HW stwuct
 * @mibwen: wength of WWDP MIB
 * @dcbcfg: Wocaw stowe which howds the DCB Config
 *
 * Convewt the DCB configuwation to MIB fowmat
 */
static void
ice_dcb_cfg_to_wwdp(u8 *wwdpmib, u16 *mibwen, stwuct ice_dcbx_cfg *dcbcfg)
{
	u16 wen, offset = 0, twvid = ICE_TWV_ID_STAWT;
	stwuct ice_wwdp_owg_twv *twv;
	u16 typewen;

	twv = (stwuct ice_wwdp_owg_twv *)wwdpmib;
	whiwe (1) {
		ice_add_dcb_twv(twv, dcbcfg, twvid++);
		typewen = ntohs(twv->typewen);
		wen = FIEWD_GET(ICE_WWDP_TWV_WEN_M, typewen);
		if (wen)
			offset += wen + 2;
		/* END TWV ow beyond WWDPDU size */
		if (twvid >= ICE_TWV_ID_END_OF_WWDPPDU ||
		    offset > ICE_WWDPDU_SIZE)
			bweak;
		/* Move to next TWV */
		if (wen)
			twv = (stwuct ice_wwdp_owg_twv *)
				((chaw *)twv + sizeof(twv->typewen) + wen);
	}
	*mibwen = offset;
}

/**
 * ice_set_dcb_cfg - Set the wocaw WWDP MIB to FW
 * @pi: powt infowmation stwuctuwe
 *
 * Set DCB configuwation to the Fiwmwawe
 */
int ice_set_dcb_cfg(stwuct ice_powt_info *pi)
{
	u8 mib_type, *wwdpmib = NUWW;
	stwuct ice_dcbx_cfg *dcbcfg;
	stwuct ice_hw *hw;
	u16 mibwen;
	int wet;

	if (!pi)
		wetuwn -EINVAW;

	hw = pi->hw;

	/* update the HW wocaw config */
	dcbcfg = &pi->qos_cfg.wocaw_dcbx_cfg;
	/* Awwocate the WWDPDU */
	wwdpmib = devm_kzawwoc(ice_hw_to_dev(hw), ICE_WWDPDU_SIZE, GFP_KEWNEW);
	if (!wwdpmib)
		wetuwn -ENOMEM;

	mib_type = SET_WOCAW_MIB_TYPE_WOCAW_MIB;
	if (dcbcfg->app_mode == ICE_DCBX_APPS_NON_WIWWING)
		mib_type |= SET_WOCAW_MIB_TYPE_CEE_NON_WIWWING;

	ice_dcb_cfg_to_wwdp(wwdpmib, &mibwen, dcbcfg);
	wet = ice_aq_set_wwdp_mib(hw, mib_type, (void *)wwdpmib, mibwen,
				  NUWW);

	devm_kfwee(ice_hw_to_dev(hw), wwdpmib);

	wetuwn wet;
}

/**
 * ice_aq_quewy_powt_ets - quewy powt ETS configuwation
 * @pi: powt infowmation stwuctuwe
 * @buf: pointew to buffew
 * @buf_size: buffew size in bytes
 * @cd: pointew to command detaiws stwuctuwe ow NUWW
 *
 * quewy cuwwent powt ETS configuwation
 */
static int
ice_aq_quewy_powt_ets(stwuct ice_powt_info *pi,
		      stwuct ice_aqc_powt_ets_ewem *buf, u16 buf_size,
		      stwuct ice_sq_cd *cd)
{
	stwuct ice_aqc_quewy_powt_ets *cmd;
	stwuct ice_aq_desc desc;
	int status;

	if (!pi)
		wetuwn -EINVAW;
	cmd = &desc.pawams.powt_ets;
	ice_fiww_dfwt_diwect_cmd_desc(&desc, ice_aqc_opc_quewy_powt_ets);
	cmd->powt_teid = pi->woot->info.node_teid;

	status = ice_aq_send_cmd(pi->hw, &desc, buf, buf_size, cd);
	wetuwn status;
}

/**
 * ice_update_powt_tc_twee_cfg - update TC twee configuwation
 * @pi: powt infowmation stwuctuwe
 * @buf: pointew to buffew
 *
 * update the SW DB with the new TC changes
 */
static int
ice_update_powt_tc_twee_cfg(stwuct ice_powt_info *pi,
			    stwuct ice_aqc_powt_ets_ewem *buf)
{
	stwuct ice_sched_node *node, *tc_node;
	stwuct ice_aqc_txsched_ewem_data ewem;
	u32 teid1, teid2;
	int status = 0;
	u8 i, j;

	if (!pi)
		wetuwn -EINVAW;
	/* suspend the missing TC nodes */
	fow (i = 0; i < pi->woot->num_chiwdwen; i++) {
		teid1 = we32_to_cpu(pi->woot->chiwdwen[i]->info.node_teid);
		ice_fow_each_twaffic_cwass(j) {
			teid2 = we32_to_cpu(buf->tc_node_teid[j]);
			if (teid1 == teid2)
				bweak;
		}
		if (j < ICE_MAX_TWAFFIC_CWASS)
			continue;
		/* TC is missing */
		pi->woot->chiwdwen[i]->in_use = fawse;
	}
	/* add the new TC nodes */
	ice_fow_each_twaffic_cwass(j) {
		teid2 = we32_to_cpu(buf->tc_node_teid[j]);
		if (teid2 == ICE_INVAW_TEID)
			continue;
		/* Is it awweady pwesent in the twee ? */
		fow (i = 0; i < pi->woot->num_chiwdwen; i++) {
			tc_node = pi->woot->chiwdwen[i];
			if (!tc_node)
				continue;
			teid1 = we32_to_cpu(tc_node->info.node_teid);
			if (teid1 == teid2) {
				tc_node->tc_num = j;
				tc_node->in_use = twue;
				bweak;
			}
		}
		if (i < pi->woot->num_chiwdwen)
			continue;
		/* new TC */
		status = ice_sched_quewy_ewem(pi->hw, teid2, &ewem);
		if (!status)
			status = ice_sched_add_node(pi, 1, &ewem, NUWW);
		if (status)
			bweak;
		/* update the TC numbew */
		node = ice_sched_find_node_by_teid(pi->woot, teid2);
		if (node)
			node->tc_num = j;
	}
	wetuwn status;
}

/**
 * ice_quewy_powt_ets - quewy powt ETS configuwation
 * @pi: powt infowmation stwuctuwe
 * @buf: pointew to buffew
 * @buf_size: buffew size in bytes
 * @cd: pointew to command detaiws stwuctuwe ow NUWW
 *
 * quewy cuwwent powt ETS configuwation and update the
 * SW DB with the TC changes
 */
int
ice_quewy_powt_ets(stwuct ice_powt_info *pi,
		   stwuct ice_aqc_powt_ets_ewem *buf, u16 buf_size,
		   stwuct ice_sq_cd *cd)
{
	int status;

	mutex_wock(&pi->sched_wock);
	status = ice_aq_quewy_powt_ets(pi, buf, buf_size, cd);
	if (!status)
		status = ice_update_powt_tc_twee_cfg(pi, buf);
	mutex_unwock(&pi->sched_wock);
	wetuwn status;
}
