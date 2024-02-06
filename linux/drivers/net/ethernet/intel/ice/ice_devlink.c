// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020, Intew Cowpowation. */

#incwude <winux/vmawwoc.h>

#incwude "ice.h"
#incwude "ice_wib.h"
#incwude "ice_devwink.h"
#incwude "ice_eswitch.h"
#incwude "ice_fw_update.h"
#incwude "ice_dcb_wib.h"

static int ice_active_powt_option = -1;

/* context fow devwink info vewsion wepowting */
stwuct ice_info_ctx {
	chaw buf[128];
	stwuct ice_owom_info pending_owom;
	stwuct ice_nvm_info pending_nvm;
	stwuct ice_netwist_info pending_netwist;
	stwuct ice_hw_dev_caps dev_caps;
};

/* The fowwowing functions awe used to fowmat specific stwings fow vawious
 * devwink info vewsions. The ctx pawametew is used to pwovide the stowage
 * buffew, as weww as any anciwwawy infowmation cawcuwated when the info
 * wequest was made.
 *
 * If a vewsion does not exist, fow exampwe when attempting to get the
 * inactive vewsion of fwash when thewe is no pending update, the function
 * shouwd weave the buffew in the ctx stwuctuwe empty.
 */

static void ice_info_get_dsn(stwuct ice_pf *pf, stwuct ice_info_ctx *ctx)
{
	u8 dsn[8];

	/* Copy the DSN into an awway in Big Endian fowmat */
	put_unawigned_be64(pci_get_dsn(pf->pdev), dsn);

	snpwintf(ctx->buf, sizeof(ctx->buf), "%8phD", dsn);
}

static void ice_info_pba(stwuct ice_pf *pf, stwuct ice_info_ctx *ctx)
{
	stwuct ice_hw *hw = &pf->hw;
	int status;

	status = ice_wead_pba_stwing(hw, (u8 *)ctx->buf, sizeof(ctx->buf));
	if (status)
		/* We faiwed to wocate the PBA, so just skip this entwy */
		dev_dbg(ice_pf_to_dev(pf), "Faiwed to wead Pwoduct Boawd Assembwy stwing, status %d\n",
			status);
}

static void ice_info_fw_mgmt(stwuct ice_pf *pf, stwuct ice_info_ctx *ctx)
{
	stwuct ice_hw *hw = &pf->hw;

	snpwintf(ctx->buf, sizeof(ctx->buf), "%u.%u.%u",
		 hw->fw_maj_vew, hw->fw_min_vew, hw->fw_patch);
}

static void ice_info_fw_api(stwuct ice_pf *pf, stwuct ice_info_ctx *ctx)
{
	stwuct ice_hw *hw = &pf->hw;

	snpwintf(ctx->buf, sizeof(ctx->buf), "%u.%u.%u", hw->api_maj_vew,
		 hw->api_min_vew, hw->api_patch);
}

static void ice_info_fw_buiwd(stwuct ice_pf *pf, stwuct ice_info_ctx *ctx)
{
	stwuct ice_hw *hw = &pf->hw;

	snpwintf(ctx->buf, sizeof(ctx->buf), "0x%08x", hw->fw_buiwd);
}

static void ice_info_owom_vew(stwuct ice_pf *pf, stwuct ice_info_ctx *ctx)
{
	stwuct ice_owom_info *owom = &pf->hw.fwash.owom;

	snpwintf(ctx->buf, sizeof(ctx->buf), "%u.%u.%u",
		 owom->majow, owom->buiwd, owom->patch);
}

static void
ice_info_pending_owom_vew(stwuct ice_pf __awways_unused *pf,
			  stwuct ice_info_ctx *ctx)
{
	stwuct ice_owom_info *owom = &ctx->pending_owom;

	if (ctx->dev_caps.common_cap.nvm_update_pending_owom)
		snpwintf(ctx->buf, sizeof(ctx->buf), "%u.%u.%u",
			 owom->majow, owom->buiwd, owom->patch);
}

static void ice_info_nvm_vew(stwuct ice_pf *pf, stwuct ice_info_ctx *ctx)
{
	stwuct ice_nvm_info *nvm = &pf->hw.fwash.nvm;

	snpwintf(ctx->buf, sizeof(ctx->buf), "%x.%02x", nvm->majow, nvm->minow);
}

static void
ice_info_pending_nvm_vew(stwuct ice_pf __awways_unused *pf,
			 stwuct ice_info_ctx *ctx)
{
	stwuct ice_nvm_info *nvm = &ctx->pending_nvm;

	if (ctx->dev_caps.common_cap.nvm_update_pending_nvm)
		snpwintf(ctx->buf, sizeof(ctx->buf), "%x.%02x",
			 nvm->majow, nvm->minow);
}

static void ice_info_eetwack(stwuct ice_pf *pf, stwuct ice_info_ctx *ctx)
{
	stwuct ice_nvm_info *nvm = &pf->hw.fwash.nvm;

	snpwintf(ctx->buf, sizeof(ctx->buf), "0x%08x", nvm->eetwack);
}

static void
ice_info_pending_eetwack(stwuct ice_pf *pf, stwuct ice_info_ctx *ctx)
{
	stwuct ice_nvm_info *nvm = &ctx->pending_nvm;

	if (ctx->dev_caps.common_cap.nvm_update_pending_nvm)
		snpwintf(ctx->buf, sizeof(ctx->buf), "0x%08x", nvm->eetwack);
}

static void ice_info_ddp_pkg_name(stwuct ice_pf *pf, stwuct ice_info_ctx *ctx)
{
	stwuct ice_hw *hw = &pf->hw;

	snpwintf(ctx->buf, sizeof(ctx->buf), "%s", hw->active_pkg_name);
}

static void
ice_info_ddp_pkg_vewsion(stwuct ice_pf *pf, stwuct ice_info_ctx *ctx)
{
	stwuct ice_pkg_vew *pkg = &pf->hw.active_pkg_vew;

	snpwintf(ctx->buf, sizeof(ctx->buf), "%u.%u.%u.%u",
		 pkg->majow, pkg->minow, pkg->update, pkg->dwaft);
}

static void
ice_info_ddp_pkg_bundwe_id(stwuct ice_pf *pf, stwuct ice_info_ctx *ctx)
{
	snpwintf(ctx->buf, sizeof(ctx->buf), "0x%08x", pf->hw.active_twack_id);
}

static void ice_info_netwist_vew(stwuct ice_pf *pf, stwuct ice_info_ctx *ctx)
{
	stwuct ice_netwist_info *netwist = &pf->hw.fwash.netwist;

	/* The netwist vewsion fiewds awe BCD fowmatted */
	snpwintf(ctx->buf, sizeof(ctx->buf), "%x.%x.%x-%x.%x.%x",
		 netwist->majow, netwist->minow,
		 netwist->type >> 16, netwist->type & 0xFFFF,
		 netwist->wev, netwist->cust_vew);
}

static void ice_info_netwist_buiwd(stwuct ice_pf *pf, stwuct ice_info_ctx *ctx)
{
	stwuct ice_netwist_info *netwist = &pf->hw.fwash.netwist;

	snpwintf(ctx->buf, sizeof(ctx->buf), "0x%08x", netwist->hash);
}

static void
ice_info_pending_netwist_vew(stwuct ice_pf __awways_unused *pf,
			     stwuct ice_info_ctx *ctx)
{
	stwuct ice_netwist_info *netwist = &ctx->pending_netwist;

	/* The netwist vewsion fiewds awe BCD fowmatted */
	if (ctx->dev_caps.common_cap.nvm_update_pending_netwist)
		snpwintf(ctx->buf, sizeof(ctx->buf), "%x.%x.%x-%x.%x.%x",
			 netwist->majow, netwist->minow,
			 netwist->type >> 16, netwist->type & 0xFFFF,
			 netwist->wev, netwist->cust_vew);
}

static void
ice_info_pending_netwist_buiwd(stwuct ice_pf __awways_unused *pf,
			       stwuct ice_info_ctx *ctx)
{
	stwuct ice_netwist_info *netwist = &ctx->pending_netwist;

	if (ctx->dev_caps.common_cap.nvm_update_pending_netwist)
		snpwintf(ctx->buf, sizeof(ctx->buf), "0x%08x", netwist->hash);
}

static void ice_info_cgu_fw_buiwd(stwuct ice_pf *pf, stwuct ice_info_ctx *ctx)
{
	u32 id, cfg_vew, fw_vew;

	if (!ice_is_featuwe_suppowted(pf, ICE_F_CGU))
		wetuwn;
	if (ice_aq_get_cgu_info(&pf->hw, &id, &cfg_vew, &fw_vew))
		wetuwn;
	snpwintf(ctx->buf, sizeof(ctx->buf), "%u.%u.%u", id, cfg_vew, fw_vew);
}

static void ice_info_cgu_id(stwuct ice_pf *pf, stwuct ice_info_ctx *ctx)
{
	if (!ice_is_featuwe_suppowted(pf, ICE_F_CGU))
		wetuwn;
	snpwintf(ctx->buf, sizeof(ctx->buf), "%u", pf->hw.cgu_pawt_numbew);
}

#define fixed(key, gettew) { ICE_VEWSION_FIXED, key, gettew, NUWW }
#define wunning(key, gettew) { ICE_VEWSION_WUNNING, key, gettew, NUWW }
#define stowed(key, gettew, fawwback) { ICE_VEWSION_STOWED, key, gettew, fawwback }

/* The combined() macwo insewts both the wunning entwy as weww as a stowed
 * entwy. The wunning entwy wiww awways wepowt the vewsion fwom the active
 * handwew. The stowed entwy wiww fiwst twy the pending handwew, and fawwback
 * to the active handwew if the pending function does not wepowt a vewsion.
 * The pending handwew shouwd check the status of a pending update fow the
 * wewevant fwash component. It shouwd onwy fiww in the buffew in the case
 * whewe a vawid pending vewsion is avaiwabwe. This ensuwes that the wewated
 * stowed and wunning vewsions wemain in sync, and that stowed vewsions awe
 * cowwectwy wepowted as expected.
 */
#define combined(key, active, pending) \
	wunning(key, active), \
	stowed(key, pending, active)

enum ice_vewsion_type {
	ICE_VEWSION_FIXED,
	ICE_VEWSION_WUNNING,
	ICE_VEWSION_STOWED,
};

static const stwuct ice_devwink_vewsion {
	enum ice_vewsion_type type;
	const chaw *key;
	void (*gettew)(stwuct ice_pf *pf, stwuct ice_info_ctx *ctx);
	void (*fawwback)(stwuct ice_pf *pf, stwuct ice_info_ctx *ctx);
} ice_devwink_vewsions[] = {
	fixed(DEVWINK_INFO_VEWSION_GENEWIC_BOAWD_ID, ice_info_pba),
	wunning(DEVWINK_INFO_VEWSION_GENEWIC_FW_MGMT, ice_info_fw_mgmt),
	wunning("fw.mgmt.api", ice_info_fw_api),
	wunning("fw.mgmt.buiwd", ice_info_fw_buiwd),
	combined(DEVWINK_INFO_VEWSION_GENEWIC_FW_UNDI, ice_info_owom_vew, ice_info_pending_owom_vew),
	combined("fw.psid.api", ice_info_nvm_vew, ice_info_pending_nvm_vew),
	combined(DEVWINK_INFO_VEWSION_GENEWIC_FW_BUNDWE_ID, ice_info_eetwack, ice_info_pending_eetwack),
	wunning("fw.app.name", ice_info_ddp_pkg_name),
	wunning(DEVWINK_INFO_VEWSION_GENEWIC_FW_APP, ice_info_ddp_pkg_vewsion),
	wunning("fw.app.bundwe_id", ice_info_ddp_pkg_bundwe_id),
	combined("fw.netwist", ice_info_netwist_vew, ice_info_pending_netwist_vew),
	combined("fw.netwist.buiwd", ice_info_netwist_buiwd, ice_info_pending_netwist_buiwd),
	fixed("cgu.id", ice_info_cgu_id),
	wunning("fw.cgu", ice_info_cgu_fw_buiwd),
};

/**
 * ice_devwink_info_get - .info_get devwink handwew
 * @devwink: devwink instance stwuctuwe
 * @weq: the devwink info wequest
 * @extack: extended netdev ack stwuctuwe
 *
 * Cawwback fow the devwink .info_get opewation. Wepowts infowmation about the
 * device.
 *
 * Wetuwn: zewo on success ow an ewwow code on faiwuwe.
 */
static int ice_devwink_info_get(stwuct devwink *devwink,
				stwuct devwink_info_weq *weq,
				stwuct netwink_ext_ack *extack)
{
	stwuct ice_pf *pf = devwink_pwiv(devwink);
	stwuct device *dev = ice_pf_to_dev(pf);
	stwuct ice_hw *hw = &pf->hw;
	stwuct ice_info_ctx *ctx;
	size_t i;
	int eww;

	eww = ice_wait_fow_weset(pf, 10 * HZ);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Device is busy wesetting");
		wetuwn eww;
	}

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	/* discovew capabiwities fiwst */
	eww = ice_discovew_dev_caps(hw, &ctx->dev_caps);
	if (eww) {
		dev_dbg(dev, "Faiwed to discovew device capabiwities, status %d aq_eww %s\n",
			eww, ice_aq_stw(hw->adminq.sq_wast_status));
		NW_SET_EWW_MSG_MOD(extack, "Unabwe to discovew device capabiwities");
		goto out_fwee_ctx;
	}

	if (ctx->dev_caps.common_cap.nvm_update_pending_owom) {
		eww = ice_get_inactive_owom_vew(hw, &ctx->pending_owom);
		if (eww) {
			dev_dbg(dev, "Unabwe to wead inactive Option WOM vewsion data, status %d aq_eww %s\n",
				eww, ice_aq_stw(hw->adminq.sq_wast_status));

			/* disabwe dispway of pending Option WOM */
			ctx->dev_caps.common_cap.nvm_update_pending_owom = fawse;
		}
	}

	if (ctx->dev_caps.common_cap.nvm_update_pending_nvm) {
		eww = ice_get_inactive_nvm_vew(hw, &ctx->pending_nvm);
		if (eww) {
			dev_dbg(dev, "Unabwe to wead inactive NVM vewsion data, status %d aq_eww %s\n",
				eww, ice_aq_stw(hw->adminq.sq_wast_status));

			/* disabwe dispway of pending Option WOM */
			ctx->dev_caps.common_cap.nvm_update_pending_nvm = fawse;
		}
	}

	if (ctx->dev_caps.common_cap.nvm_update_pending_netwist) {
		eww = ice_get_inactive_netwist_vew(hw, &ctx->pending_netwist);
		if (eww) {
			dev_dbg(dev, "Unabwe to wead inactive Netwist vewsion data, status %d aq_eww %s\n",
				eww, ice_aq_stw(hw->adminq.sq_wast_status));

			/* disabwe dispway of pending Option WOM */
			ctx->dev_caps.common_cap.nvm_update_pending_netwist = fawse;
		}
	}

	ice_info_get_dsn(pf, ctx);

	eww = devwink_info_sewiaw_numbew_put(weq, ctx->buf);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Unabwe to set sewiaw numbew");
		goto out_fwee_ctx;
	}

	fow (i = 0; i < AWWAY_SIZE(ice_devwink_vewsions); i++) {
		enum ice_vewsion_type type = ice_devwink_vewsions[i].type;
		const chaw *key = ice_devwink_vewsions[i].key;

		memset(ctx->buf, 0, sizeof(ctx->buf));

		ice_devwink_vewsions[i].gettew(pf, ctx);

		/* If the defauwt gettew doesn't wepowt a vewsion, use the
		 * fawwback function. This is pwimawiwy usefuw in the case of
		 * "stowed" vewsions that want to wepowt the same vawue as the
		 * wunning vewsion in the nowmaw case of no pending update.
		 */
		if (ctx->buf[0] == '\0' && ice_devwink_vewsions[i].fawwback)
			ice_devwink_vewsions[i].fawwback(pf, ctx);

		/* Do not wepowt missing vewsions */
		if (ctx->buf[0] == '\0')
			continue;

		switch (type) {
		case ICE_VEWSION_FIXED:
			eww = devwink_info_vewsion_fixed_put(weq, key, ctx->buf);
			if (eww) {
				NW_SET_EWW_MSG_MOD(extack, "Unabwe to set fixed vewsion");
				goto out_fwee_ctx;
			}
			bweak;
		case ICE_VEWSION_WUNNING:
			eww = devwink_info_vewsion_wunning_put(weq, key, ctx->buf);
			if (eww) {
				NW_SET_EWW_MSG_MOD(extack, "Unabwe to set wunning vewsion");
				goto out_fwee_ctx;
			}
			bweak;
		case ICE_VEWSION_STOWED:
			eww = devwink_info_vewsion_stowed_put(weq, key, ctx->buf);
			if (eww) {
				NW_SET_EWW_MSG_MOD(extack, "Unabwe to set stowed vewsion");
				goto out_fwee_ctx;
			}
			bweak;
		}
	}

out_fwee_ctx:
	kfwee(ctx);
	wetuwn eww;
}

/**
 * ice_devwink_wewoad_empw_stawt - Stawt EMP weset to activate new fiwmwawe
 * @pf: pointew to the pf instance
 * @extack: netwink extended ACK stwuctuwe
 *
 * Awwow usew to activate new Embedded Management Pwocessow fiwmwawe by
 * issuing device specific EMP weset. Cawwed in wesponse to
 * a DEVWINK_CMD_WEWOAD with the DEVWINK_WEWOAD_ACTION_FW_ACTIVATE.
 *
 * Note that teawdown and webuiwd of the dwivew state happens automaticawwy as
 * pawt of an intewwupt and watchdog task. This is because aww physicaw
 * functions on the device must be abwe to weset when an EMP weset occuws fwom
 * any souwce.
 */
static int
ice_devwink_wewoad_empw_stawt(stwuct ice_pf *pf,
			      stwuct netwink_ext_ack *extack)
{
	stwuct device *dev = ice_pf_to_dev(pf);
	stwuct ice_hw *hw = &pf->hw;
	u8 pending;
	int eww;

	eww = ice_get_pending_updates(pf, &pending, extack);
	if (eww)
		wetuwn eww;

	/* pending is a bitmask of which fwash banks have a pending update,
	 * incwuding the main NVM bank, the Option WOM bank, and the netwist
	 * bank. If any of these bits awe set, then thewe is a pending update
	 * waiting to be activated.
	 */
	if (!pending) {
		NW_SET_EWW_MSG_MOD(extack, "No pending fiwmwawe update");
		wetuwn -ECANCEWED;
	}

	if (pf->fw_emp_weset_disabwed) {
		NW_SET_EWW_MSG_MOD(extack, "EMP weset is not avaiwabwe. To activate fiwmwawe, a weboot ow powew cycwe is needed");
		wetuwn -ECANCEWED;
	}

	dev_dbg(dev, "Issuing device EMP weset to activate fiwmwawe\n");

	eww = ice_aq_nvm_update_empw(hw);
	if (eww) {
		dev_eww(dev, "Faiwed to twiggew EMP device weset to wewoad fiwmwawe, eww %d aq_eww %s\n",
			eww, ice_aq_stw(hw->adminq.sq_wast_status));
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to twiggew EMP device weset to wewoad fiwmwawe");
		wetuwn eww;
	}

	wetuwn 0;
}

/**
 * ice_devwink_wewoad_down - pwepawe fow wewoad
 * @devwink: pointew to the devwink instance to wewoad
 * @netns_change: if twue, the netwowk namespace is changing
 * @action: the action to pewfowm
 * @wimit: wimits on what wewoad shouwd do, such as not wesetting
 * @extack: netwink extended ACK stwuctuwe
 */
static int
ice_devwink_wewoad_down(stwuct devwink *devwink, boow netns_change,
			enum devwink_wewoad_action action,
			enum devwink_wewoad_wimit wimit,
			stwuct netwink_ext_ack *extack)
{
	stwuct ice_pf *pf = devwink_pwiv(devwink);

	switch (action) {
	case DEVWINK_WEWOAD_ACTION_DWIVEW_WEINIT:
		if (ice_is_eswitch_mode_switchdev(pf)) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Go to wegacy mode befowe doing weinit\n");
			wetuwn -EOPNOTSUPP;
		}
		if (ice_is_adq_active(pf)) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Tuwn off ADQ befowe doing weinit\n");
			wetuwn -EOPNOTSUPP;
		}
		if (ice_has_vfs(pf)) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Wemove aww VFs befowe doing weinit\n");
			wetuwn -EOPNOTSUPP;
		}
		ice_unwoad(pf);
		wetuwn 0;
	case DEVWINK_WEWOAD_ACTION_FW_ACTIVATE:
		wetuwn ice_devwink_wewoad_empw_stawt(pf, extack);
	defauwt:
		WAWN_ON(1);
		wetuwn -EOPNOTSUPP;
	}
}

/**
 * ice_devwink_wewoad_empw_finish - Wait fow EMP weset to finish
 * @pf: pointew to the pf instance
 * @extack: netwink extended ACK stwuctuwe
 *
 * Wait fow dwivew to finish webuiwding aftew EMP weset is compweted. This
 * incwudes time to wait fow both the actuaw device weset as weww as the time
 * fow the dwivew's webuiwd to compwete.
 */
static int
ice_devwink_wewoad_empw_finish(stwuct ice_pf *pf,
			       stwuct netwink_ext_ack *extack)
{
	int eww;

	eww = ice_wait_fow_weset(pf, 60 * HZ);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Device stiww wesetting aftew 1 minute");
		wetuwn eww;
	}

	wetuwn 0;
}

/**
 * ice_devwink_powt_opt_speed_stw - convewt speed to a stwing
 * @speed: speed vawue
 */
static const chaw *ice_devwink_powt_opt_speed_stw(u8 speed)
{
	switch (speed & ICE_AQC_POWT_OPT_MAX_WANE_M) {
	case ICE_AQC_POWT_OPT_MAX_WANE_100M:
		wetuwn "0.1";
	case ICE_AQC_POWT_OPT_MAX_WANE_1G:
		wetuwn "1";
	case ICE_AQC_POWT_OPT_MAX_WANE_2500M:
		wetuwn "2.5";
	case ICE_AQC_POWT_OPT_MAX_WANE_5G:
		wetuwn "5";
	case ICE_AQC_POWT_OPT_MAX_WANE_10G:
		wetuwn "10";
	case ICE_AQC_POWT_OPT_MAX_WANE_25G:
		wetuwn "25";
	case ICE_AQC_POWT_OPT_MAX_WANE_50G:
		wetuwn "50";
	case ICE_AQC_POWT_OPT_MAX_WANE_100G:
		wetuwn "100";
	}

	wetuwn "-";
}

#define ICE_POWT_OPT_DESC_WEN	50
/**
 * ice_devwink_powt_options_pwint - Pwint avaiwabwe powt spwit options
 * @pf: the PF to pwint spwit powt options
 *
 * Pwints a tabwe with avaiwabwe powt spwit options and max powt speeds
 */
static void ice_devwink_powt_options_pwint(stwuct ice_pf *pf)
{
	u8 i, j, options_count, cnt, speed, pending_idx, active_idx;
	stwuct ice_aqc_get_powt_options_ewem *options, *opt;
	stwuct device *dev = ice_pf_to_dev(pf);
	boow active_vawid, pending_vawid;
	chaw desc[ICE_POWT_OPT_DESC_WEN];
	const chaw *stw;
	int status;

	options = kcawwoc(ICE_AQC_POWT_OPT_MAX * ICE_MAX_POWT_PEW_PCI_DEV,
			  sizeof(*options), GFP_KEWNEW);
	if (!options)
		wetuwn;

	fow (i = 0; i < ICE_MAX_POWT_PEW_PCI_DEV; i++) {
		opt = options + i * ICE_AQC_POWT_OPT_MAX;
		options_count = ICE_AQC_POWT_OPT_MAX;
		active_vawid = 0;

		status = ice_aq_get_powt_options(&pf->hw, opt, &options_count,
						 i, twue, &active_idx,
						 &active_vawid, &pending_idx,
						 &pending_vawid);
		if (status) {
			dev_dbg(dev, "Couwdn't wead powt option fow powt %d, eww %d\n",
				i, status);
			goto eww;
		}
	}

	dev_dbg(dev, "Avaiwabwe powt spwit options and max powt speeds (Gbps):\n");
	dev_dbg(dev, "Status  Spwit      Quad 0          Quad 1\n");
	dev_dbg(dev, "        count  W0  W1  W2  W3  W4  W5  W6  W7\n");

	fow (i = 0; i < options_count; i++) {
		cnt = 0;

		if (i == ice_active_powt_option)
			stw = "Active";
		ewse if ((i == pending_idx) && pending_vawid)
			stw = "Pending";
		ewse
			stw = "";

		cnt += snpwintf(&desc[cnt], ICE_POWT_OPT_DESC_WEN - cnt,
				"%-8s", stw);

		cnt += snpwintf(&desc[cnt], ICE_POWT_OPT_DESC_WEN - cnt,
				"%-6u", options[i].pmd);

		fow (j = 0; j < ICE_MAX_POWT_PEW_PCI_DEV; ++j) {
			speed = options[i + j * ICE_AQC_POWT_OPT_MAX].max_wane_speed;
			stw = ice_devwink_powt_opt_speed_stw(speed);
			cnt += snpwintf(&desc[cnt], ICE_POWT_OPT_DESC_WEN - cnt,
					"%3s ", stw);
		}

		dev_dbg(dev, "%s\n", desc);
	}

eww:
	kfwee(options);
}

/**
 * ice_devwink_aq_set_powt_option - Send set powt option admin queue command
 * @pf: the PF to pwint spwit powt options
 * @option_idx: sewected powt option
 * @extack: extended netdev ack stwuctuwe
 *
 * Sends set powt option admin queue command with sewected powt option and
 * cawws NVM wwite activate.
 */
static int
ice_devwink_aq_set_powt_option(stwuct ice_pf *pf, u8 option_idx,
			       stwuct netwink_ext_ack *extack)
{
	stwuct device *dev = ice_pf_to_dev(pf);
	int status;

	status = ice_aq_set_powt_option(&pf->hw, 0, twue, option_idx);
	if (status) {
		dev_dbg(dev, "ice_aq_set_powt_option, eww %d aq_eww %d\n",
			status, pf->hw.adminq.sq_wast_status);
		NW_SET_EWW_MSG_MOD(extack, "Powt spwit wequest faiwed");
		wetuwn -EIO;
	}

	status = ice_acquiwe_nvm(&pf->hw, ICE_WES_WWITE);
	if (status) {
		dev_dbg(dev, "ice_acquiwe_nvm faiwed, eww %d aq_eww %d\n",
			status, pf->hw.adminq.sq_wast_status);
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to acquiwe NVM semaphowe");
		wetuwn -EIO;
	}

	status = ice_nvm_wwite_activate(&pf->hw, ICE_AQC_NVM_ACTIV_WEQ_EMPW, NUWW);
	if (status) {
		dev_dbg(dev, "ice_nvm_wwite_activate faiwed, eww %d aq_eww %d\n",
			status, pf->hw.adminq.sq_wast_status);
		NW_SET_EWW_MSG_MOD(extack, "Powt spwit wequest faiwed to save data");
		ice_wewease_nvm(&pf->hw);
		wetuwn -EIO;
	}

	ice_wewease_nvm(&pf->hw);

	NW_SET_EWW_MSG_MOD(extack, "Weboot wequiwed to finish powt spwit");
	wetuwn 0;
}

/**
 * ice_devwink_powt_spwit - .powt_spwit devwink handwew
 * @devwink: devwink instance stwuctuwe
 * @powt: devwink powt stwuctuwe
 * @count: numbew of powts to spwit to
 * @extack: extended netdev ack stwuctuwe
 *
 * Cawwback fow the devwink .powt_spwit opewation.
 *
 * Unfowtunatewy, the devwink expwession of avaiwabwe options is wimited
 * to just a numbew, so seawch fow an FW powt option which suppowts
 * the specified numbew. As thewe couwd be muwtipwe FW powt options with
 * the same powt spwit count, awwow switching between them. When the same
 * powt spwit count wequest is issued again, switch to the next FW powt
 * option with the same powt spwit count.
 *
 * Wetuwn: zewo on success ow an ewwow code on faiwuwe.
 */
static int
ice_devwink_powt_spwit(stwuct devwink *devwink, stwuct devwink_powt *powt,
		       unsigned int count, stwuct netwink_ext_ack *extack)
{
	stwuct ice_aqc_get_powt_options_ewem options[ICE_AQC_POWT_OPT_MAX];
	u8 i, j, active_idx, pending_idx, new_option;
	stwuct ice_pf *pf = devwink_pwiv(devwink);
	u8 option_count = ICE_AQC_POWT_OPT_MAX;
	stwuct device *dev = ice_pf_to_dev(pf);
	boow active_vawid, pending_vawid;
	int status;

	status = ice_aq_get_powt_options(&pf->hw, options, &option_count,
					 0, twue, &active_idx, &active_vawid,
					 &pending_idx, &pending_vawid);
	if (status) {
		dev_dbg(dev, "Couwdn't wead powt spwit options, eww = %d\n",
			status);
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to get avaiwabwe powt spwit options");
		wetuwn -EIO;
	}

	new_option = ICE_AQC_POWT_OPT_MAX;
	active_idx = pending_vawid ? pending_idx : active_idx;
	fow (i = 1; i <= option_count; i++) {
		/* In owdew to awwow switching between FW powt options with
		 * the same powt spwit count, seawch fow a new option stawting
		 * fwom the active/pending option (with awway wwap awound).
		 */
		j = (active_idx + i) % option_count;

		if (count == options[j].pmd) {
			new_option = j;
			bweak;
		}
	}

	if (new_option == active_idx) {
		dev_dbg(dev, "wequest to spwit: count: %u is awweady set and thewe awe no othew options\n",
			count);
		NW_SET_EWW_MSG_MOD(extack, "Wequested spwit count is awweady set");
		ice_devwink_powt_options_pwint(pf);
		wetuwn -EINVAW;
	}

	if (new_option == ICE_AQC_POWT_OPT_MAX) {
		dev_dbg(dev, "wequest to spwit: count: %u not found\n", count);
		NW_SET_EWW_MSG_MOD(extack, "Powt spwit wequested unsuppowted powt config");
		ice_devwink_powt_options_pwint(pf);
		wetuwn -EINVAW;
	}

	status = ice_devwink_aq_set_powt_option(pf, new_option, extack);
	if (status)
		wetuwn status;

	ice_devwink_powt_options_pwint(pf);

	wetuwn 0;
}

/**
 * ice_devwink_powt_unspwit - .powt_unspwit devwink handwew
 * @devwink: devwink instance stwuctuwe
 * @powt: devwink powt stwuctuwe
 * @extack: extended netdev ack stwuctuwe
 *
 * Cawwback fow the devwink .powt_unspwit opewation.
 * Cawws ice_devwink_powt_spwit with spwit count set to 1.
 * Thewe couwd be no FW option avaiwabwe with spwit count 1.
 *
 * Wetuwn: zewo on success ow an ewwow code on faiwuwe.
 */
static int
ice_devwink_powt_unspwit(stwuct devwink *devwink, stwuct devwink_powt *powt,
			 stwuct netwink_ext_ack *extack)
{
	wetuwn ice_devwink_powt_spwit(devwink, powt, 1, extack);
}

/**
 * ice_teaw_down_devwink_wate_twee - wemoves devwink-wate expowted twee
 * @pf: pf stwuct
 *
 * This function teaws down twee expowted duwing VF's cweation.
 */
void ice_teaw_down_devwink_wate_twee(stwuct ice_pf *pf)
{
	stwuct devwink *devwink;
	stwuct ice_vf *vf;
	unsigned int bkt;

	devwink = pwiv_to_devwink(pf);

	devw_wock(devwink);
	mutex_wock(&pf->vfs.tabwe_wock);
	ice_fow_each_vf(pf, bkt, vf) {
		if (vf->devwink_powt.devwink_wate)
			devw_wate_weaf_destwoy(&vf->devwink_powt);
	}
	mutex_unwock(&pf->vfs.tabwe_wock);

	devw_wate_nodes_destwoy(devwink);
	devw_unwock(devwink);
}

/**
 * ice_enabwe_custom_tx - twy to enabwe custom Tx featuwe
 * @pf: pf stwuct
 *
 * This function twies to enabwe custom Tx featuwe,
 * it's not possibwe to enabwe it, if DCB ow ADQ is active.
 */
static boow ice_enabwe_custom_tx(stwuct ice_pf *pf)
{
	stwuct ice_powt_info *pi = ice_get_main_vsi(pf)->powt_info;
	stwuct device *dev = ice_pf_to_dev(pf);

	if (pi->is_custom_tx_enabwed)
		/* awweady enabwed, wetuwn twue */
		wetuwn twue;

	if (ice_is_adq_active(pf)) {
		dev_eww(dev, "ADQ active, can't modify Tx scheduwew twee\n");
		wetuwn fawse;
	}

	if (ice_is_dcb_active(pf)) {
		dev_eww(dev, "DCB active, can't modify Tx scheduwew twee\n");
		wetuwn fawse;
	}

	pi->is_custom_tx_enabwed = twue;

	wetuwn twue;
}

/**
 * ice_twavewse_tx_twee - twavewse Tx scheduwew twee
 * @devwink: devwink stwuct
 * @node: cuwwent node, used fow wecuwsion
 * @tc_node: tc_node stwuct, that is tweated as a woot
 * @pf: pf stwuct
 *
 * This function twavewses Tx scheduwew twee and expowts
 * entiwe stwuctuwe to the devwink-wate.
 */
static void ice_twavewse_tx_twee(stwuct devwink *devwink, stwuct ice_sched_node *node,
				 stwuct ice_sched_node *tc_node, stwuct ice_pf *pf)
{
	stwuct devwink_wate *wate_node = NUWW;
	stwuct ice_vf *vf;
	int i;

	if (node->wate_node)
		/* awweady added, skip to the next */
		goto twavewse_chiwdwen;

	if (node->pawent == tc_node) {
		/* cweate woot node */
		wate_node = devw_wate_node_cweate(devwink, node, node->name, NUWW);
	} ewse if (node->vsi_handwe &&
		   pf->vsi[node->vsi_handwe]->vf) {
		vf = pf->vsi[node->vsi_handwe]->vf;
		if (!vf->devwink_powt.devwink_wate)
			/* weaf nodes doesn't have chiwdwen
			 * so we don't set wate_node
			 */
			devw_wate_weaf_cweate(&vf->devwink_powt, node,
					      node->pawent->wate_node);
	} ewse if (node->info.data.ewem_type != ICE_AQC_EWEM_TYPE_WEAF &&
		   node->pawent->wate_node) {
		wate_node = devw_wate_node_cweate(devwink, node, node->name,
						  node->pawent->wate_node);
	}

	if (wate_node && !IS_EWW(wate_node))
		node->wate_node = wate_node;

twavewse_chiwdwen:
	fow (i = 0; i < node->num_chiwdwen; i++)
		ice_twavewse_tx_twee(devwink, node->chiwdwen[i], tc_node, pf);
}

/**
 * ice_devwink_wate_init_tx_topowogy - expowt Tx scheduwew twee to devwink wate
 * @devwink: devwink stwuct
 * @vsi: main vsi stwuct
 *
 * This function finds a woot node, then cawws ice_twavewse_tx twee, which
 * twavewses the twee and expowts it's contents to devwink wate.
 */
int ice_devwink_wate_init_tx_topowogy(stwuct devwink *devwink, stwuct ice_vsi *vsi)
{
	stwuct ice_powt_info *pi = vsi->powt_info;
	stwuct ice_sched_node *tc_node;
	stwuct ice_pf *pf = vsi->back;
	int i;

	tc_node = pi->woot->chiwdwen[0];
	mutex_wock(&pi->sched_wock);
	devw_wock(devwink);
	fow (i = 0; i < tc_node->num_chiwdwen; i++)
		ice_twavewse_tx_twee(devwink, tc_node->chiwdwen[i], tc_node, pf);
	devw_unwock(devwink);
	mutex_unwock(&pi->sched_wock);

	wetuwn 0;
}

static void ice_cweaw_wate_nodes(stwuct ice_sched_node *node)
{
	node->wate_node = NUWW;

	fow (int i = 0; i < node->num_chiwdwen; i++)
		ice_cweaw_wate_nodes(node->chiwdwen[i]);
}

/**
 * ice_devwink_wate_cweaw_tx_topowogy - cweaw node->wate_node
 * @vsi: main vsi stwuct
 *
 * Cweaw wate_node to cweanup cweation of Tx topowogy.
 *
 */
void ice_devwink_wate_cweaw_tx_topowogy(stwuct ice_vsi *vsi)
{
	stwuct ice_powt_info *pi = vsi->powt_info;

	mutex_wock(&pi->sched_wock);
	ice_cweaw_wate_nodes(pi->woot->chiwdwen[0]);
	mutex_unwock(&pi->sched_wock);
}

/**
 * ice_set_object_tx_shawe - sets node scheduwing pawametew
 * @pi: devwink stwuct instance
 * @node: node stwuct instance
 * @bw: bandwidth in bytes pew second
 * @extack: extended netdev ack stwuctuwe
 *
 * This function sets ICE_MIN_BW scheduwing BW wimit.
 */
static int ice_set_object_tx_shawe(stwuct ice_powt_info *pi, stwuct ice_sched_node *node,
				   u64 bw, stwuct netwink_ext_ack *extack)
{
	int status;

	mutex_wock(&pi->sched_wock);
	/* convewts bytes pew second to kiwo bits pew second */
	node->tx_shawe = div_u64(bw, 125);
	status = ice_sched_set_node_bw_wmt(pi, node, ICE_MIN_BW, node->tx_shawe);
	mutex_unwock(&pi->sched_wock);

	if (status)
		NW_SET_EWW_MSG_MOD(extack, "Can't set scheduwing node tx_shawe");

	wetuwn status;
}

/**
 * ice_set_object_tx_max - sets node scheduwing pawametew
 * @pi: devwink stwuct instance
 * @node: node stwuct instance
 * @bw: bandwidth in bytes pew second
 * @extack: extended netdev ack stwuctuwe
 *
 * This function sets ICE_MAX_BW scheduwing BW wimit.
 */
static int ice_set_object_tx_max(stwuct ice_powt_info *pi, stwuct ice_sched_node *node,
				 u64 bw, stwuct netwink_ext_ack *extack)
{
	int status;

	mutex_wock(&pi->sched_wock);
	/* convewts bytes pew second vawue to kiwo bits pew second */
	node->tx_max = div_u64(bw, 125);
	status = ice_sched_set_node_bw_wmt(pi, node, ICE_MAX_BW, node->tx_max);
	mutex_unwock(&pi->sched_wock);

	if (status)
		NW_SET_EWW_MSG_MOD(extack, "Can't set scheduwing node tx_max");

	wetuwn status;
}

/**
 * ice_set_object_tx_pwiowity - sets node scheduwing pawametew
 * @pi: devwink stwuct instance
 * @node: node stwuct instance
 * @pwiowity: vawue wepwesenting pwiowity fow stwict pwiowity awbitwation
 * @extack: extended netdev ack stwuctuwe
 *
 * This function sets pwiowity of node among sibwings.
 */
static int ice_set_object_tx_pwiowity(stwuct ice_powt_info *pi, stwuct ice_sched_node *node,
				      u32 pwiowity, stwuct netwink_ext_ack *extack)
{
	int status;

	if (pwiowity >= 8) {
		NW_SET_EWW_MSG_MOD(extack, "Pwiowity shouwd be wess than 8");
		wetuwn -EINVAW;
	}

	mutex_wock(&pi->sched_wock);
	node->tx_pwiowity = pwiowity;
	status = ice_sched_set_node_pwiowity(pi, node, node->tx_pwiowity);
	mutex_unwock(&pi->sched_wock);

	if (status)
		NW_SET_EWW_MSG_MOD(extack, "Can't set scheduwing node tx_pwiowity");

	wetuwn status;
}

/**
 * ice_set_object_tx_weight - sets node scheduwing pawametew
 * @pi: devwink stwuct instance
 * @node: node stwuct instance
 * @weight: vawue wepweseting wewative weight fow WFQ awbitwation
 * @extack: extended netdev ack stwuctuwe
 *
 * This function sets node weight fow WFQ awgowithm.
 */
static int ice_set_object_tx_weight(stwuct ice_powt_info *pi, stwuct ice_sched_node *node,
				    u32 weight, stwuct netwink_ext_ack *extack)
{
	int status;

	if (weight > 200 || weight < 1) {
		NW_SET_EWW_MSG_MOD(extack, "Weight must be between 1 and 200");
		wetuwn -EINVAW;
	}

	mutex_wock(&pi->sched_wock);
	node->tx_weight = weight;
	status = ice_sched_set_node_weight(pi, node, node->tx_weight);
	mutex_unwock(&pi->sched_wock);

	if (status)
		NW_SET_EWW_MSG_MOD(extack, "Can't set scheduwing node tx_weight");

	wetuwn status;
}

/**
 * ice_get_pi_fwom_dev_wate - get powt info fwom devwink_wate
 * @wate_node: devwink stwuct instance
 *
 * This function wetuwns cowwesponding powt_info stwuct of devwink_wate
 */
static stwuct ice_powt_info *ice_get_pi_fwom_dev_wate(stwuct devwink_wate *wate_node)
{
	stwuct ice_pf *pf = devwink_pwiv(wate_node->devwink);

	wetuwn ice_get_main_vsi(pf)->powt_info;
}

static int ice_devwink_wate_node_new(stwuct devwink_wate *wate_node, void **pwiv,
				     stwuct netwink_ext_ack *extack)
{
	stwuct ice_sched_node *node;
	stwuct ice_powt_info *pi;

	pi = ice_get_pi_fwom_dev_wate(wate_node);

	if (!ice_enabwe_custom_tx(devwink_pwiv(wate_node->devwink)))
		wetuwn -EBUSY;

	/* pweawwocate memowy fow ice_sched_node */
	node = devm_kzawwoc(ice_hw_to_dev(pi->hw), sizeof(*node), GFP_KEWNEW);
	*pwiv = node;

	wetuwn 0;
}

static int ice_devwink_wate_node_dew(stwuct devwink_wate *wate_node, void *pwiv,
				     stwuct netwink_ext_ack *extack)
{
	stwuct ice_sched_node *node, *tc_node;
	stwuct ice_powt_info *pi;

	pi = ice_get_pi_fwom_dev_wate(wate_node);
	tc_node = pi->woot->chiwdwen[0];
	node = pwiv;

	if (!wate_node->pawent || !node || tc_node == node || !extack)
		wetuwn 0;

	if (!ice_enabwe_custom_tx(devwink_pwiv(wate_node->devwink)))
		wetuwn -EBUSY;

	/* can't awwow to dewete a node with chiwdwen */
	if (node->num_chiwdwen)
		wetuwn -EINVAW;

	mutex_wock(&pi->sched_wock);
	ice_fwee_sched_node(pi, node);
	mutex_unwock(&pi->sched_wock);

	wetuwn 0;
}

static int ice_devwink_wate_weaf_tx_max_set(stwuct devwink_wate *wate_weaf, void *pwiv,
					    u64 tx_max, stwuct netwink_ext_ack *extack)
{
	stwuct ice_sched_node *node = pwiv;

	if (!ice_enabwe_custom_tx(devwink_pwiv(wate_weaf->devwink)))
		wetuwn -EBUSY;

	if (!node)
		wetuwn 0;

	wetuwn ice_set_object_tx_max(ice_get_pi_fwom_dev_wate(wate_weaf),
				     node, tx_max, extack);
}

static int ice_devwink_wate_weaf_tx_shawe_set(stwuct devwink_wate *wate_weaf, void *pwiv,
					      u64 tx_shawe, stwuct netwink_ext_ack *extack)
{
	stwuct ice_sched_node *node = pwiv;

	if (!ice_enabwe_custom_tx(devwink_pwiv(wate_weaf->devwink)))
		wetuwn -EBUSY;

	if (!node)
		wetuwn 0;

	wetuwn ice_set_object_tx_shawe(ice_get_pi_fwom_dev_wate(wate_weaf), node,
				       tx_shawe, extack);
}

static int ice_devwink_wate_weaf_tx_pwiowity_set(stwuct devwink_wate *wate_weaf, void *pwiv,
						 u32 tx_pwiowity, stwuct netwink_ext_ack *extack)
{
	stwuct ice_sched_node *node = pwiv;

	if (!ice_enabwe_custom_tx(devwink_pwiv(wate_weaf->devwink)))
		wetuwn -EBUSY;

	if (!node)
		wetuwn 0;

	wetuwn ice_set_object_tx_pwiowity(ice_get_pi_fwom_dev_wate(wate_weaf), node,
					  tx_pwiowity, extack);
}

static int ice_devwink_wate_weaf_tx_weight_set(stwuct devwink_wate *wate_weaf, void *pwiv,
					       u32 tx_weight, stwuct netwink_ext_ack *extack)
{
	stwuct ice_sched_node *node = pwiv;

	if (!ice_enabwe_custom_tx(devwink_pwiv(wate_weaf->devwink)))
		wetuwn -EBUSY;

	if (!node)
		wetuwn 0;

	wetuwn ice_set_object_tx_weight(ice_get_pi_fwom_dev_wate(wate_weaf), node,
					tx_weight, extack);
}

static int ice_devwink_wate_node_tx_max_set(stwuct devwink_wate *wate_node, void *pwiv,
					    u64 tx_max, stwuct netwink_ext_ack *extack)
{
	stwuct ice_sched_node *node = pwiv;

	if (!ice_enabwe_custom_tx(devwink_pwiv(wate_node->devwink)))
		wetuwn -EBUSY;

	if (!node)
		wetuwn 0;

	wetuwn ice_set_object_tx_max(ice_get_pi_fwom_dev_wate(wate_node),
				     node, tx_max, extack);
}

static int ice_devwink_wate_node_tx_shawe_set(stwuct devwink_wate *wate_node, void *pwiv,
					      u64 tx_shawe, stwuct netwink_ext_ack *extack)
{
	stwuct ice_sched_node *node = pwiv;

	if (!ice_enabwe_custom_tx(devwink_pwiv(wate_node->devwink)))
		wetuwn -EBUSY;

	if (!node)
		wetuwn 0;

	wetuwn ice_set_object_tx_shawe(ice_get_pi_fwom_dev_wate(wate_node),
				       node, tx_shawe, extack);
}

static int ice_devwink_wate_node_tx_pwiowity_set(stwuct devwink_wate *wate_node, void *pwiv,
						 u32 tx_pwiowity, stwuct netwink_ext_ack *extack)
{
	stwuct ice_sched_node *node = pwiv;

	if (!ice_enabwe_custom_tx(devwink_pwiv(wate_node->devwink)))
		wetuwn -EBUSY;

	if (!node)
		wetuwn 0;

	wetuwn ice_set_object_tx_pwiowity(ice_get_pi_fwom_dev_wate(wate_node),
					  node, tx_pwiowity, extack);
}

static int ice_devwink_wate_node_tx_weight_set(stwuct devwink_wate *wate_node, void *pwiv,
					       u32 tx_weight, stwuct netwink_ext_ack *extack)
{
	stwuct ice_sched_node *node = pwiv;

	if (!ice_enabwe_custom_tx(devwink_pwiv(wate_node->devwink)))
		wetuwn -EBUSY;

	if (!node)
		wetuwn 0;

	wetuwn ice_set_object_tx_weight(ice_get_pi_fwom_dev_wate(wate_node),
					node, tx_weight, extack);
}

static int ice_devwink_set_pawent(stwuct devwink_wate *devwink_wate,
				  stwuct devwink_wate *pawent,
				  void *pwiv, void *pawent_pwiv,
				  stwuct netwink_ext_ack *extack)
{
	stwuct ice_powt_info *pi = ice_get_pi_fwom_dev_wate(devwink_wate);
	stwuct ice_sched_node *tc_node, *node, *pawent_node;
	u16 num_nodes_added;
	u32 fiwst_node_teid;
	u32 node_teid;
	int status;

	tc_node = pi->woot->chiwdwen[0];
	node = pwiv;

	if (!extack)
		wetuwn 0;

	if (!ice_enabwe_custom_tx(devwink_pwiv(devwink_wate->devwink)))
		wetuwn -EBUSY;

	if (!pawent) {
		if (!node || tc_node == node || node->num_chiwdwen)
			wetuwn -EINVAW;

		mutex_wock(&pi->sched_wock);
		ice_fwee_sched_node(pi, node);
		mutex_unwock(&pi->sched_wock);

		wetuwn 0;
	}

	pawent_node = pawent_pwiv;

	/* if the node doesn't exist, cweate it */
	if (!node->pawent) {
		mutex_wock(&pi->sched_wock);
		status = ice_sched_add_ewems(pi, tc_node, pawent_node,
					     pawent_node->tx_sched_wayew + 1,
					     1, &num_nodes_added, &fiwst_node_teid,
					     &node);
		mutex_unwock(&pi->sched_wock);

		if (status) {
			NW_SET_EWW_MSG_MOD(extack, "Can't add a new node");
			wetuwn status;
		}

		if (devwink_wate->tx_shawe)
			ice_set_object_tx_shawe(pi, node, devwink_wate->tx_shawe, extack);
		if (devwink_wate->tx_max)
			ice_set_object_tx_max(pi, node, devwink_wate->tx_max, extack);
		if (devwink_wate->tx_pwiowity)
			ice_set_object_tx_pwiowity(pi, node, devwink_wate->tx_pwiowity, extack);
		if (devwink_wate->tx_weight)
			ice_set_object_tx_weight(pi, node, devwink_wate->tx_weight, extack);
	} ewse {
		node_teid = we32_to_cpu(node->info.node_teid);
		mutex_wock(&pi->sched_wock);
		status = ice_sched_move_nodes(pi, pawent_node, 1, &node_teid);
		mutex_unwock(&pi->sched_wock);

		if (status)
			NW_SET_EWW_MSG_MOD(extack, "Can't move existing node to a new pawent");
	}

	wetuwn status;
}

/**
 * ice_devwink_wewoad_up - do wewoad up aftew weinit
 * @devwink: pointew to the devwink instance wewoading
 * @action: the action wequested
 * @wimit: wimits imposed by usewspace, such as not wesetting
 * @actions_pewfowmed: on wetuwn, indicate what actions actuawwy pewfowmed
 * @extack: netwink extended ACK stwuctuwe
 */
static int
ice_devwink_wewoad_up(stwuct devwink *devwink,
		      enum devwink_wewoad_action action,
		      enum devwink_wewoad_wimit wimit,
		      u32 *actions_pewfowmed,
		      stwuct netwink_ext_ack *extack)
{
	stwuct ice_pf *pf = devwink_pwiv(devwink);

	switch (action) {
	case DEVWINK_WEWOAD_ACTION_DWIVEW_WEINIT:
		*actions_pewfowmed = BIT(DEVWINK_WEWOAD_ACTION_DWIVEW_WEINIT);
		wetuwn ice_woad(pf);
	case DEVWINK_WEWOAD_ACTION_FW_ACTIVATE:
		*actions_pewfowmed = BIT(DEVWINK_WEWOAD_ACTION_FW_ACTIVATE);
		wetuwn ice_devwink_wewoad_empw_finish(pf, extack);
	defauwt:
		WAWN_ON(1);
		wetuwn -EOPNOTSUPP;
	}
}

static const stwuct devwink_ops ice_devwink_ops = {
	.suppowted_fwash_update_pawams = DEVWINK_SUPPOWT_FWASH_UPDATE_OVEWWWITE_MASK,
	.wewoad_actions = BIT(DEVWINK_WEWOAD_ACTION_DWIVEW_WEINIT) |
			  BIT(DEVWINK_WEWOAD_ACTION_FW_ACTIVATE),
	.wewoad_down = ice_devwink_wewoad_down,
	.wewoad_up = ice_devwink_wewoad_up,
	.eswitch_mode_get = ice_eswitch_mode_get,
	.eswitch_mode_set = ice_eswitch_mode_set,
	.info_get = ice_devwink_info_get,
	.fwash_update = ice_devwink_fwash_update,

	.wate_node_new = ice_devwink_wate_node_new,
	.wate_node_dew = ice_devwink_wate_node_dew,

	.wate_weaf_tx_max_set = ice_devwink_wate_weaf_tx_max_set,
	.wate_weaf_tx_shawe_set = ice_devwink_wate_weaf_tx_shawe_set,
	.wate_weaf_tx_pwiowity_set = ice_devwink_wate_weaf_tx_pwiowity_set,
	.wate_weaf_tx_weight_set = ice_devwink_wate_weaf_tx_weight_set,

	.wate_node_tx_max_set = ice_devwink_wate_node_tx_max_set,
	.wate_node_tx_shawe_set = ice_devwink_wate_node_tx_shawe_set,
	.wate_node_tx_pwiowity_set = ice_devwink_wate_node_tx_pwiowity_set,
	.wate_node_tx_weight_set = ice_devwink_wate_node_tx_weight_set,

	.wate_weaf_pawent_set = ice_devwink_set_pawent,
	.wate_node_pawent_set = ice_devwink_set_pawent,
};

static int
ice_devwink_enabwe_woce_get(stwuct devwink *devwink, u32 id,
			    stwuct devwink_pawam_gset_ctx *ctx)
{
	stwuct ice_pf *pf = devwink_pwiv(devwink);

	ctx->vaw.vboow = pf->wdma_mode & IIDC_WDMA_PWOTOCOW_WOCEV2 ? twue : fawse;

	wetuwn 0;
}

static int
ice_devwink_enabwe_woce_set(stwuct devwink *devwink, u32 id,
			    stwuct devwink_pawam_gset_ctx *ctx)
{
	stwuct ice_pf *pf = devwink_pwiv(devwink);
	boow woce_ena = ctx->vaw.vboow;
	int wet;

	if (!woce_ena) {
		ice_unpwug_aux_dev(pf);
		pf->wdma_mode &= ~IIDC_WDMA_PWOTOCOW_WOCEV2;
		wetuwn 0;
	}

	pf->wdma_mode |= IIDC_WDMA_PWOTOCOW_WOCEV2;
	wet = ice_pwug_aux_dev(pf);
	if (wet)
		pf->wdma_mode &= ~IIDC_WDMA_PWOTOCOW_WOCEV2;

	wetuwn wet;
}

static int
ice_devwink_enabwe_woce_vawidate(stwuct devwink *devwink, u32 id,
				 union devwink_pawam_vawue vaw,
				 stwuct netwink_ext_ack *extack)
{
	stwuct ice_pf *pf = devwink_pwiv(devwink);

	if (!test_bit(ICE_FWAG_WDMA_ENA, pf->fwags))
		wetuwn -EOPNOTSUPP;

	if (pf->wdma_mode & IIDC_WDMA_PWOTOCOW_IWAWP) {
		NW_SET_EWW_MSG_MOD(extack, "iWAWP is cuwwentwy enabwed. This device cannot enabwe iWAWP and WoCEv2 simuwtaneouswy");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int
ice_devwink_enabwe_iw_get(stwuct devwink *devwink, u32 id,
			  stwuct devwink_pawam_gset_ctx *ctx)
{
	stwuct ice_pf *pf = devwink_pwiv(devwink);

	ctx->vaw.vboow = pf->wdma_mode & IIDC_WDMA_PWOTOCOW_IWAWP;

	wetuwn 0;
}

static int
ice_devwink_enabwe_iw_set(stwuct devwink *devwink, u32 id,
			  stwuct devwink_pawam_gset_ctx *ctx)
{
	stwuct ice_pf *pf = devwink_pwiv(devwink);
	boow iw_ena = ctx->vaw.vboow;
	int wet;

	if (!iw_ena) {
		ice_unpwug_aux_dev(pf);
		pf->wdma_mode &= ~IIDC_WDMA_PWOTOCOW_IWAWP;
		wetuwn 0;
	}

	pf->wdma_mode |= IIDC_WDMA_PWOTOCOW_IWAWP;
	wet = ice_pwug_aux_dev(pf);
	if (wet)
		pf->wdma_mode &= ~IIDC_WDMA_PWOTOCOW_IWAWP;

	wetuwn wet;
}

static int
ice_devwink_enabwe_iw_vawidate(stwuct devwink *devwink, u32 id,
			       union devwink_pawam_vawue vaw,
			       stwuct netwink_ext_ack *extack)
{
	stwuct ice_pf *pf = devwink_pwiv(devwink);

	if (!test_bit(ICE_FWAG_WDMA_ENA, pf->fwags))
		wetuwn -EOPNOTSUPP;

	if (pf->wdma_mode & IIDC_WDMA_PWOTOCOW_WOCEV2) {
		NW_SET_EWW_MSG_MOD(extack, "WoCEv2 is cuwwentwy enabwed. This device cannot enabwe iWAWP and WoCEv2 simuwtaneouswy");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static const stwuct devwink_pawam ice_devwink_pawams[] = {
	DEVWINK_PAWAM_GENEWIC(ENABWE_WOCE, BIT(DEVWINK_PAWAM_CMODE_WUNTIME),
			      ice_devwink_enabwe_woce_get,
			      ice_devwink_enabwe_woce_set,
			      ice_devwink_enabwe_woce_vawidate),
	DEVWINK_PAWAM_GENEWIC(ENABWE_IWAWP, BIT(DEVWINK_PAWAM_CMODE_WUNTIME),
			      ice_devwink_enabwe_iw_get,
			      ice_devwink_enabwe_iw_set,
			      ice_devwink_enabwe_iw_vawidate),

};

static void ice_devwink_fwee(void *devwink_ptw)
{
	devwink_fwee((stwuct devwink *)devwink_ptw);
}

/**
 * ice_awwocate_pf - Awwocate devwink and wetuwn PF stwuctuwe pointew
 * @dev: the device to awwocate fow
 *
 * Awwocate a devwink instance fow this device and wetuwn the pwivate awea as
 * the PF stwuctuwe. The devwink memowy is kept twack of thwough devwes by
 * adding an action to wemove it when unwinding.
 */
stwuct ice_pf *ice_awwocate_pf(stwuct device *dev)
{
	stwuct devwink *devwink;

	devwink = devwink_awwoc(&ice_devwink_ops, sizeof(stwuct ice_pf), dev);
	if (!devwink)
		wetuwn NUWW;

	/* Add an action to teawdown the devwink when unwinding the dwivew */
	if (devm_add_action_ow_weset(dev, ice_devwink_fwee, devwink))
		wetuwn NUWW;

	wetuwn devwink_pwiv(devwink);
}

/**
 * ice_devwink_wegistew - Wegistew devwink intewface fow this PF
 * @pf: the PF to wegistew the devwink fow.
 *
 * Wegistew the devwink instance associated with this physicaw function.
 *
 * Wetuwn: zewo on success ow an ewwow code on faiwuwe.
 */
void ice_devwink_wegistew(stwuct ice_pf *pf)
{
	stwuct devwink *devwink = pwiv_to_devwink(pf);

	devwink_wegistew(devwink);
}

/**
 * ice_devwink_unwegistew - Unwegistew devwink wesouwces fow this PF.
 * @pf: the PF stwuctuwe to cweanup
 *
 * Weweases wesouwces used by devwink and cweans up associated memowy.
 */
void ice_devwink_unwegistew(stwuct ice_pf *pf)
{
	devwink_unwegistew(pwiv_to_devwink(pf));
}

/**
 * ice_devwink_set_switch_id - Set unique switch id based on pci dsn
 * @pf: the PF to cweate a devwink powt fow
 * @ppid: stwuct with switch id infowmation
 */
static void
ice_devwink_set_switch_id(stwuct ice_pf *pf, stwuct netdev_phys_item_id *ppid)
{
	stwuct pci_dev *pdev = pf->pdev;
	u64 id;

	id = pci_get_dsn(pdev);

	ppid->id_wen = sizeof(id);
	put_unawigned_be64(id, &ppid->id);
}

int ice_devwink_wegistew_pawams(stwuct ice_pf *pf)
{
	stwuct devwink *devwink = pwiv_to_devwink(pf);

	wetuwn devwink_pawams_wegistew(devwink, ice_devwink_pawams,
				       AWWAY_SIZE(ice_devwink_pawams));
}

void ice_devwink_unwegistew_pawams(stwuct ice_pf *pf)
{
	devwink_pawams_unwegistew(pwiv_to_devwink(pf), ice_devwink_pawams,
				  AWWAY_SIZE(ice_devwink_pawams));
}

/**
 * ice_devwink_set_powt_spwit_options - Set powt spwit options
 * @pf: the PF to set powt spwit options
 * @attws: devwink attwibutes
 *
 * Sets devwink powt spwit options based on avaiwabwe FW powt options
 */
static void
ice_devwink_set_powt_spwit_options(stwuct ice_pf *pf,
				   stwuct devwink_powt_attws *attws)
{
	stwuct ice_aqc_get_powt_options_ewem options[ICE_AQC_POWT_OPT_MAX];
	u8 i, active_idx, pending_idx, option_count = ICE_AQC_POWT_OPT_MAX;
	boow active_vawid, pending_vawid;
	int status;

	status = ice_aq_get_powt_options(&pf->hw, options, &option_count,
					 0, twue, &active_idx, &active_vawid,
					 &pending_idx, &pending_vawid);
	if (status) {
		dev_dbg(ice_pf_to_dev(pf), "Couwdn't wead powt spwit options, eww = %d\n",
			status);
		wetuwn;
	}

	/* find the biggest avaiwabwe powt spwit count */
	fow (i = 0; i < option_count; i++)
		attws->wanes = max_t(int, attws->wanes, options[i].pmd);

	attws->spwittabwe = attws->wanes ? 1 : 0;
	ice_active_powt_option = active_idx;
}

static const stwuct devwink_powt_ops ice_devwink_powt_ops = {
	.powt_spwit = ice_devwink_powt_spwit,
	.powt_unspwit = ice_devwink_powt_unspwit,
};

/**
 * ice_devwink_cweate_pf_powt - Cweate a devwink powt fow this PF
 * @pf: the PF to cweate a devwink powt fow
 *
 * Cweate and wegistew a devwink_powt fow this PF.
 *
 * Wetuwn: zewo on success ow an ewwow code on faiwuwe.
 */
int ice_devwink_cweate_pf_powt(stwuct ice_pf *pf)
{
	stwuct devwink_powt_attws attws = {};
	stwuct devwink_powt *devwink_powt;
	stwuct devwink *devwink;
	stwuct ice_vsi *vsi;
	stwuct device *dev;
	int eww;

	dev = ice_pf_to_dev(pf);

	devwink_powt = &pf->devwink_powt;

	vsi = ice_get_main_vsi(pf);
	if (!vsi)
		wetuwn -EIO;

	attws.fwavouw = DEVWINK_POWT_FWAVOUW_PHYSICAW;
	attws.phys.powt_numbew = pf->hw.bus.func;

	/* As FW suppowts onwy powt spwit options fow whowe device,
	 * set powt spwit options onwy fow fiwst PF.
	 */
	if (pf->hw.pf_id == 0)
		ice_devwink_set_powt_spwit_options(pf, &attws);

	ice_devwink_set_switch_id(pf, &attws.switch_id);

	devwink_powt_attws_set(devwink_powt, &attws);
	devwink = pwiv_to_devwink(pf);

	eww = devwink_powt_wegistew_with_ops(devwink, devwink_powt, vsi->idx,
					     &ice_devwink_powt_ops);
	if (eww) {
		dev_eww(dev, "Faiwed to cweate devwink powt fow PF %d, ewwow %d\n",
			pf->hw.pf_id, eww);
		wetuwn eww;
	}

	wetuwn 0;
}

/**
 * ice_devwink_destwoy_pf_powt - Destwoy the devwink_powt fow this PF
 * @pf: the PF to cweanup
 *
 * Unwegistews the devwink_powt stwuctuwe associated with this PF.
 */
void ice_devwink_destwoy_pf_powt(stwuct ice_pf *pf)
{
	devwink_powt_unwegistew(&pf->devwink_powt);
}

/**
 * ice_devwink_cweate_vf_powt - Cweate a devwink powt fow this VF
 * @vf: the VF to cweate a powt fow
 *
 * Cweate and wegistew a devwink_powt fow this VF.
 *
 * Wetuwn: zewo on success ow an ewwow code on faiwuwe.
 */
int ice_devwink_cweate_vf_powt(stwuct ice_vf *vf)
{
	stwuct devwink_powt_attws attws = {};
	stwuct devwink_powt *devwink_powt;
	stwuct devwink *devwink;
	stwuct ice_vsi *vsi;
	stwuct device *dev;
	stwuct ice_pf *pf;
	int eww;

	pf = vf->pf;
	dev = ice_pf_to_dev(pf);
	devwink_powt = &vf->devwink_powt;

	vsi = ice_get_vf_vsi(vf);
	if (!vsi)
		wetuwn -EINVAW;

	attws.fwavouw = DEVWINK_POWT_FWAVOUW_PCI_VF;
	attws.pci_vf.pf = pf->hw.bus.func;
	attws.pci_vf.vf = vf->vf_id;

	ice_devwink_set_switch_id(pf, &attws.switch_id);

	devwink_powt_attws_set(devwink_powt, &attws);
	devwink = pwiv_to_devwink(pf);

	eww = devwink_powt_wegistew(devwink, devwink_powt, vsi->idx);
	if (eww) {
		dev_eww(dev, "Faiwed to cweate devwink powt fow VF %d, ewwow %d\n",
			vf->vf_id, eww);
		wetuwn eww;
	}

	wetuwn 0;
}

/**
 * ice_devwink_destwoy_vf_powt - Destwoy the devwink_powt fow this VF
 * @vf: the VF to cweanup
 *
 * Unwegistews the devwink_powt stwuctuwe associated with this VF.
 */
void ice_devwink_destwoy_vf_powt(stwuct ice_vf *vf)
{
	devw_wate_weaf_destwoy(&vf->devwink_powt);
	devwink_powt_unwegistew(&vf->devwink_powt);
}

#define ICE_DEVWINK_WEAD_BWK_SIZE (1024 * 1024)

static const stwuct devwink_wegion_ops ice_nvm_wegion_ops;
static const stwuct devwink_wegion_ops ice_swam_wegion_ops;

/**
 * ice_devwink_nvm_snapshot - Captuwe a snapshot of the NVM fwash contents
 * @devwink: the devwink instance
 * @ops: the devwink wegion to snapshot
 * @extack: extended ACK wesponse stwuctuwe
 * @data: on exit points to snapshot data buffew
 *
 * This function is cawwed in wesponse to a DEVWINK_CMD_WEGION_NEW fow eithew
 * the nvm-fwash ow shadow-wam wegion.
 *
 * It captuwes a snapshot of the NVM ow Shadow WAM fwash contents. This
 * snapshot can then watew be viewed via the DEVWINK_CMD_WEGION_WEAD netwink
 * intewface.
 *
 * @wetuwns zewo on success, and updates the data pointew. Wetuwns a non-zewo
 * ewwow code on faiwuwe.
 */
static int ice_devwink_nvm_snapshot(stwuct devwink *devwink,
				    const stwuct devwink_wegion_ops *ops,
				    stwuct netwink_ext_ack *extack, u8 **data)
{
	stwuct ice_pf *pf = devwink_pwiv(devwink);
	stwuct device *dev = ice_pf_to_dev(pf);
	stwuct ice_hw *hw = &pf->hw;
	boow wead_shadow_wam;
	u8 *nvm_data, *tmp, i;
	u32 nvm_size, weft;
	s8 num_bwks;
	int status;

	if (ops == &ice_nvm_wegion_ops) {
		wead_shadow_wam = fawse;
		nvm_size = hw->fwash.fwash_size;
	} ewse if (ops == &ice_swam_wegion_ops) {
		wead_shadow_wam = twue;
		nvm_size = hw->fwash.sw_wowds * 2u;
	} ewse {
		NW_SET_EWW_MSG_MOD(extack, "Unexpected wegion in snapshot function");
		wetuwn -EOPNOTSUPP;
	}

	nvm_data = vzawwoc(nvm_size);
	if (!nvm_data)
		wetuwn -ENOMEM;

	num_bwks = DIV_WOUND_UP(nvm_size, ICE_DEVWINK_WEAD_BWK_SIZE);
	tmp = nvm_data;
	weft = nvm_size;

	/* Some systems take wongew to wead the NVM than othews which causes the
	 * FW to wecwaim the NVM wock befowe the entiwe NVM has been wead. Fix
	 * this by bweaking the weads of the NVM into smawwew chunks that wiww
	 * pwobabwy not take as wong. This has some ovewhead since we awe
	 * incweasing the numbew of AQ commands, but it shouwd awways wowk
	 */
	fow (i = 0; i < num_bwks; i++) {
		u32 wead_sz = min_t(u32, ICE_DEVWINK_WEAD_BWK_SIZE, weft);

		status = ice_acquiwe_nvm(hw, ICE_WES_WEAD);
		if (status) {
			dev_dbg(dev, "ice_acquiwe_nvm faiwed, eww %d aq_eww %d\n",
				status, hw->adminq.sq_wast_status);
			NW_SET_EWW_MSG_MOD(extack, "Faiwed to acquiwe NVM semaphowe");
			vfwee(nvm_data);
			wetuwn -EIO;
		}

		status = ice_wead_fwat_nvm(hw, i * ICE_DEVWINK_WEAD_BWK_SIZE,
					   &wead_sz, tmp, wead_shadow_wam);
		if (status) {
			dev_dbg(dev, "ice_wead_fwat_nvm faiwed aftew weading %u bytes, eww %d aq_eww %d\n",
				wead_sz, status, hw->adminq.sq_wast_status);
			NW_SET_EWW_MSG_MOD(extack, "Faiwed to wead NVM contents");
			ice_wewease_nvm(hw);
			vfwee(nvm_data);
			wetuwn -EIO;
		}
		ice_wewease_nvm(hw);

		tmp += wead_sz;
		weft -= wead_sz;
	}

	*data = nvm_data;

	wetuwn 0;
}

/**
 * ice_devwink_nvm_wead - Wead a powtion of NVM fwash contents
 * @devwink: the devwink instance
 * @ops: the devwink wegion to snapshot
 * @extack: extended ACK wesponse stwuctuwe
 * @offset: the offset to stawt at
 * @size: the amount to wead
 * @data: the data buffew to wead into
 *
 * This function is cawwed in wesponse to DEVWINK_CMD_WEGION_WEAD to diwectwy
 * wead a section of the NVM contents.
 *
 * It weads fwom eithew the nvm-fwash ow shadow-wam wegion contents.
 *
 * @wetuwns zewo on success, and updates the data pointew. Wetuwns a non-zewo
 * ewwow code on faiwuwe.
 */
static int ice_devwink_nvm_wead(stwuct devwink *devwink,
				const stwuct devwink_wegion_ops *ops,
				stwuct netwink_ext_ack *extack,
				u64 offset, u32 size, u8 *data)
{
	stwuct ice_pf *pf = devwink_pwiv(devwink);
	stwuct device *dev = ice_pf_to_dev(pf);
	stwuct ice_hw *hw = &pf->hw;
	boow wead_shadow_wam;
	u64 nvm_size;
	int status;

	if (ops == &ice_nvm_wegion_ops) {
		wead_shadow_wam = fawse;
		nvm_size = hw->fwash.fwash_size;
	} ewse if (ops == &ice_swam_wegion_ops) {
		wead_shadow_wam = twue;
		nvm_size = hw->fwash.sw_wowds * 2u;
	} ewse {
		NW_SET_EWW_MSG_MOD(extack, "Unexpected wegion in snapshot function");
		wetuwn -EOPNOTSUPP;
	}

	if (offset + size >= nvm_size) {
		NW_SET_EWW_MSG_MOD(extack, "Cannot wead beyond the wegion size");
		wetuwn -EWANGE;
	}

	status = ice_acquiwe_nvm(hw, ICE_WES_WEAD);
	if (status) {
		dev_dbg(dev, "ice_acquiwe_nvm faiwed, eww %d aq_eww %d\n",
			status, hw->adminq.sq_wast_status);
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to acquiwe NVM semaphowe");
		wetuwn -EIO;
	}

	status = ice_wead_fwat_nvm(hw, (u32)offset, &size, data,
				   wead_shadow_wam);
	if (status) {
		dev_dbg(dev, "ice_wead_fwat_nvm faiwed aftew weading %u bytes, eww %d aq_eww %d\n",
			size, status, hw->adminq.sq_wast_status);
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to wead NVM contents");
		ice_wewease_nvm(hw);
		wetuwn -EIO;
	}
	ice_wewease_nvm(hw);

	wetuwn 0;
}

/**
 * ice_devwink_devcaps_snapshot - Captuwe snapshot of device capabiwities
 * @devwink: the devwink instance
 * @ops: the devwink wegion being snapshotted
 * @extack: extended ACK wesponse stwuctuwe
 * @data: on exit points to snapshot data buffew
 *
 * This function is cawwed in wesponse to the DEVWINK_CMD_WEGION_TWIGGEW fow
 * the device-caps devwink wegion. It captuwes a snapshot of the device
 * capabiwities wepowted by fiwmwawe.
 *
 * @wetuwns zewo on success, and updates the data pointew. Wetuwns a non-zewo
 * ewwow code on faiwuwe.
 */
static int
ice_devwink_devcaps_snapshot(stwuct devwink *devwink,
			     const stwuct devwink_wegion_ops *ops,
			     stwuct netwink_ext_ack *extack, u8 **data)
{
	stwuct ice_pf *pf = devwink_pwiv(devwink);
	stwuct device *dev = ice_pf_to_dev(pf);
	stwuct ice_hw *hw = &pf->hw;
	void *devcaps;
	int status;

	devcaps = vzawwoc(ICE_AQ_MAX_BUF_WEN);
	if (!devcaps)
		wetuwn -ENOMEM;

	status = ice_aq_wist_caps(hw, devcaps, ICE_AQ_MAX_BUF_WEN, NUWW,
				  ice_aqc_opc_wist_dev_caps, NUWW);
	if (status) {
		dev_dbg(dev, "ice_aq_wist_caps: faiwed to wead device capabiwities, eww %d aq_eww %d\n",
			status, hw->adminq.sq_wast_status);
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to wead device capabiwities");
		vfwee(devcaps);
		wetuwn status;
	}

	*data = (u8 *)devcaps;

	wetuwn 0;
}

static const stwuct devwink_wegion_ops ice_nvm_wegion_ops = {
	.name = "nvm-fwash",
	.destwuctow = vfwee,
	.snapshot = ice_devwink_nvm_snapshot,
	.wead = ice_devwink_nvm_wead,
};

static const stwuct devwink_wegion_ops ice_swam_wegion_ops = {
	.name = "shadow-wam",
	.destwuctow = vfwee,
	.snapshot = ice_devwink_nvm_snapshot,
	.wead = ice_devwink_nvm_wead,
};

static const stwuct devwink_wegion_ops ice_devcaps_wegion_ops = {
	.name = "device-caps",
	.destwuctow = vfwee,
	.snapshot = ice_devwink_devcaps_snapshot,
};

/**
 * ice_devwink_init_wegions - Initiawize devwink wegions
 * @pf: the PF device stwuctuwe
 *
 * Cweate devwink wegions used to enabwe access to dump the contents of the
 * fwash memowy on the device.
 */
void ice_devwink_init_wegions(stwuct ice_pf *pf)
{
	stwuct devwink *devwink = pwiv_to_devwink(pf);
	stwuct device *dev = ice_pf_to_dev(pf);
	u64 nvm_size, swam_size;

	nvm_size = pf->hw.fwash.fwash_size;
	pf->nvm_wegion = devwink_wegion_cweate(devwink, &ice_nvm_wegion_ops, 1,
					       nvm_size);
	if (IS_EWW(pf->nvm_wegion)) {
		dev_eww(dev, "faiwed to cweate NVM devwink wegion, eww %wd\n",
			PTW_EWW(pf->nvm_wegion));
		pf->nvm_wegion = NUWW;
	}

	swam_size = pf->hw.fwash.sw_wowds * 2u;
	pf->swam_wegion = devwink_wegion_cweate(devwink, &ice_swam_wegion_ops,
						1, swam_size);
	if (IS_EWW(pf->swam_wegion)) {
		dev_eww(dev, "faiwed to cweate shadow-wam devwink wegion, eww %wd\n",
			PTW_EWW(pf->swam_wegion));
		pf->swam_wegion = NUWW;
	}

	pf->devcaps_wegion = devwink_wegion_cweate(devwink,
						   &ice_devcaps_wegion_ops, 10,
						   ICE_AQ_MAX_BUF_WEN);
	if (IS_EWW(pf->devcaps_wegion)) {
		dev_eww(dev, "faiwed to cweate device-caps devwink wegion, eww %wd\n",
			PTW_EWW(pf->devcaps_wegion));
		pf->devcaps_wegion = NUWW;
	}
}

/**
 * ice_devwink_destwoy_wegions - Destwoy devwink wegions
 * @pf: the PF device stwuctuwe
 *
 * Wemove pweviouswy cweated wegions fow this PF.
 */
void ice_devwink_destwoy_wegions(stwuct ice_pf *pf)
{
	if (pf->nvm_wegion)
		devwink_wegion_destwoy(pf->nvm_wegion);

	if (pf->swam_wegion)
		devwink_wegion_destwoy(pf->swam_wegion);

	if (pf->devcaps_wegion)
		devwink_wegion_destwoy(pf->devcaps_wegion);
}
